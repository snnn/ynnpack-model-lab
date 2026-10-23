// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
use super::package::{self, Recipe};
#[cfg(feature = "llm-tests")]
use super::package::Package;
use crate::{ffi, runtime::{AssetStore, ExecutionSpec, PreparedProgram, PrepareOptions, PreparationStats}, Error, Result};
use crate::frontend::Options;
use std::collections::BTreeMap;
use std::ffi::CString;
use std::path::{Path, PathBuf};
use std::time::Instant;

pub(super) struct StateBuffers {
    pub input: CString,
    output: CString,
    shape: Vec<usize>,
    pub current: ffi::Buffer<f32>,
    next: ffi::Buffer<f32>,
}
enum Buffer { Float(ffi::Buffer<f32>), Int(ffi::Buffer<i32>), Bf16(ffi::Buffer<u16>) }
struct Input { spec: package::Input, name: CString, buffer: Buffer }
pub struct Session {
    // Native graphs retain storage pointers. Always destroy them first.
    pub(super) graphs: [ffi::PreparedGraph;2],
    pub(crate) caches: Vec<(CString, ffi::Resource)>,
    pub(super) states: Vec<StateBuffers>,
    inputs: [Vec<Input>;2],
    embeddings: BTreeMap<String,ffi::Embedding>,
    pub(crate) logits: ffi::Buffer<f32>,
    pub(crate) score_logits: Option<ffi::Buffer<f32>>,
    pub(crate) package: ExecutionSpec,
    pub(crate) position: usize,
    pub preparation: PreparationStats,
    failed: bool,
    decoded: bool,
    trace_output: Option<PathBuf>,
    trace_call: usize,
}
impl Session {
    #[cfg(feature = "llm-tests")]
    pub(crate) fn load(root:&Path, bundle:&Path, parameters:&Path, package:Package, options:&Options) -> Result<Self> {
        let _ = root;
        let assets = open_assets(bundle, parameters, options, &package.metadata)?;
        let prepared = crate::runtime::prepare(&package.program, assets, prepare_options(options, &package.spec))?;
        Self::from_prepared(prepared, package.spec)
    }
    /// Consume the fully prepared phase set. No compilation or file loading occurs here.
    pub fn from_prepared(mut prepared: PreparedProgram, package: ExecutionSpec) -> Result<Self> {
        if prepared.execution.as_ref() != Some(&package) {
            return Err(Error::invalid("Session requires the execution contract validated during preparation"));
        }
        let prefill = prepared.graphs.remove("prefill").ok_or_else(|| Error::invalid("Missing prefill"))?;
        let decode = prepared.graphs.remove("decode").ok_or_else(|| Error::invalid("Missing decode"))?;
        let graphs = [prefill, decode];
        let embeddings = package.embeddings.iter().map(|(k,e)|
            Ok((k.clone(),ffi::Embedding::new(prepared.assets.clone(),e,package.vocabulary)?)))
            .collect::<Result<BTreeMap<_,_>>>()?;
        let mut inputs = [Vec::new(), Vec::new()];
        for (i, phase) in ["prefill", "decode"].iter().enumerate() {
            for spec in &package.graphs[*phase].inputs {
                let n=package::count(&spec.dimensions(if i==0{package.prefill_rows}else{1},package.capacity)?)?;
                inputs[i].push(Input{spec:spec.clone(),name:ffi::string(&spec.name)?,buffer:
                    if spec.dtype=="int32"{Buffer::Int(ffi::Buffer::new(n,0))}else if spec.dtype=="bf16"{Buffer::Bf16(ffi::Buffer::new(n,0))}else{Buffer::Float(ffi::Buffer::new(n,0.0))}});
            }
        }
        let mut caches=Vec::new();
        for r in &package.resources {
            let shape=r.shape.iter().map(|d|d.value(1,package.capacity)).collect::<Result<Vec<_>>>()?;
            let bytes=match r.dtype.as_str(){"int8"=>1,"bf16"=>2,_=>4};
            let name=ffi::string(&r.name)?;
            let resource = match r.dtype.as_str() {
                "int2" => ffi::Resource::new_packed(&graphs[0],&name,&shape,2)?,
                "int4" => ffi::Resource::new_packed(&graphs[0],&name,&shape,4)?,
                _ => ffi::Resource::new_typed(&graphs[0],&name,&shape,bytes)?,
            };
            caches.push((name.clone(),resource));
        }
        let mut states=Vec::new();
        for s in &package.fixed_states {
            let n=package::count(&s.shape)?;
            states.push(StateBuffers{input:ffi::string(&s.input)?,output:ffi::string(&s.output)?,shape:s.shape.clone(),
                current:ffi::Buffer::new(n,0.0),next:ffi::Buffer::new(n,0.0)});
        }
        Ok(Self{graphs,caches,states,inputs,embeddings,
            logits:ffi::Buffer::new(package.vocabulary,0.0),
            score_logits:package.graphs["prefill"].logits.as_ref().map(|_|ffi::Buffer::new(package.prefill_rows*package.vocabulary,0.0)),
            package,position:0,failed:false,decoded:false,
            trace_output:prepared.trace_output,trace_call:0,preparation:prepared.stats})
    }
    pub fn logits(&self) -> &[f32] { &self.logits }
    pub fn position(&self) -> usize { self.position }
    /// Explicitly install a prepared larger variant of the same program.
    /// Prepare all replacement phases before this call. Invoke never grows capacity.
    pub fn reserve_capacity(&mut self, mut next: Self) -> Result<()> {
        if self.failed || next.failed || next.position != 0 || next.package.capacity <= self.package.capacity {
            return Err(Error::invalid("Invalid capacity replacement"));
        }
        self.package.validate_capacity_variant(&next.package)?;
        ffi::Resource::migrate_set(&mut self.caches, &mut next.caches, next.package.capacity)?;
        // From publication onward, only infallible moves remain. Fixed state
        // and its backing allocations survive unchanged across both phases.
        std::mem::swap(&mut self.states, &mut next.states);
        std::mem::swap(&mut self.logits, &mut next.logits);
        std::mem::swap(&mut self.score_logits, &mut next.score_logits);
        next.position = self.position;
        next.decoded = self.decoded;
        next.trace_output = self.trace_output.take();
        next.trace_call = self.trace_call;
        std::mem::swap(self, &mut next);
        Ok(())
    }
    pub fn reset(&mut self)->Result<()> {
        self.failed=true;
        for (_,r) in &mut self.caches{r.reset()?;}
        for s in &mut self.states{s.current.fill(0.0);s.next.fill(0.0);}
        self.position=0; self.decoded=false; self.failed=false; Ok(())
    }
    pub fn invoke(&mut self,tokens:&[i32],decode:bool,profile:Option<(&str,i32,usize)>)->Result<f64> {
        let valid=tokens.len();
        let phase=if decode{"decode"}else{"prefill"};
        let g=&self.package.graphs[phase];
        let bound=if decode{1}else{self.package.prefill_rows};
        if self.failed || valid==0 || valid>bound || self.position+valid>self.package.capacity
            || (!decode && self.decoded && !self.package.prefill_after_decode)
            || tokens.iter().any(|&t|t<0||t as usize>=self.package.vocabulary) {
            return Err(Error::invalid("Invalid request or poisoned session"));
        }
        let rows=if g.row_policy=="valid"{valid}else{bound};
        let capacity=self.package.capacity;
        // Input preparation may fail, but cannot mutate persistent graph state.
        for x in &mut self.inputs[usize::from(decode)] {
            match (&x.spec.recipe,&mut x.buffer) {
                (Recipe::Tokens,Buffer::Int(b))=>{b.fill(0);b[..valid].copy_from_slice(tokens);},
                (Recipe::Positions,Buffer::Int(b))=>{for (i,v) in b[..rows].iter_mut().enumerate(){*v=(self.position+i)as i32;}},
                (Recipe::Positions,Buffer::Float(b))=>{for (i,v) in b[..rows].iter_mut().enumerate(){*v=(self.position+i)as f32;}},
                (Recipe::Controls{values},Buffer::Int(b))=>{for (v,c) in b.iter_mut().zip(values){*v=c.value(self.position,valid)as i32;}},
                (Recipe::Mask{window,masked},Buffer::Float(b))=>{
                    let no=if masked=="finite_min"{f32::MIN}else{f32::NEG_INFINITY};
                    for i in 0..rows{for j in 0..capacity{
                        b[i*capacity+j]=if j<=self.position+i && j<self.position+valid
                            && window.is_none_or(|w|j>=(self.position+i+1).saturating_sub(w)){0.0}else{no};
                    }}
                },
                (Recipe::Embedding{table,begin,columns},Buffer::Float(b))=>{
                    b.fill(0.0);self.embeddings[table].lookup(tokens,*begin,*columns,b)?;
                },
                (Recipe::Embedding{table,begin,columns},Buffer::Bf16(b))=>{
                    b.fill(0);self.embeddings[table].lookup_bf16(tokens,*begin,*columns,b)?;
                },
                _=>return Err(Error::invalid("Input recipe type mismatch")),
            }
        }
        let graph=&mut self.graphs[usize::from(decode)];
        for (name,value) in &g.scalars{graph.scalar(&ffi::string(name)?,value.value(self.position,valid)as i64)?;}
        // All stable allocations are session-owned; run is synchronous and
        // exclusive. Bind every declared interface, never an optional name guess.
        unsafe {
            for x in &self.inputs[usize::from(decode)]{
                let dims=x.spec.dimensions(rows,capacity)?;let bytes=package::count(&dims)?*4;
                match &x.buffer{
                    Buffer::Int(b)=>graph.bind_bytes(&x.name,b,bytes,&dims,false)?,
                    Buffer::Float(b)=>graph.bind_bytes(&x.name,b,bytes,&dims,false)?,
                    Buffer::Bf16(b)=>graph.bind_bytes(&x.name,b,bytes/2,&dims,false)?,
                }
            }
            for s in &self.states{graph.bind(&s.input,&s.current,&s.shape,false)?;graph.bind(&s.output,&s.next,&[],false)?;}
            if let Some(name)=&g.logits{
                graph.bind(&ffi::string(name)?,if decode{&self.logits}else{self.score_logits.as_ref().unwrap()},&[],false)?;
            }
            for (name,cache) in &mut self.caches{graph.resource(name,cache)?;}
        }
        if let Some((name,rep,step))=profile{graph.profile_step_rows(name,rep,step,self.position,valid,!decode,1)?;}
        self.failed=true;
        let start=Instant::now();graph.run()?;let elapsed=start.elapsed().as_secs_f64()*1000.0;
        if let Some(root)=&self.trace_output{graph.save_trace(&root.join(format!("call_{:04}",self.trace_call)))?;self.trace_call+=1;}
        if decode && self.logits.iter().any(|x|!x.is_finite()){return Err(Error::invalid("Nonfinite logits"));}
        if let Some((name,rep,step))=profile{graph.profile_step_rows(name,rep,step,self.position,valid,!decode,2)?;}
        for s in &mut self.states{std::mem::swap(&mut s.current,&mut s.next);}
        self.position+=valid;self.decoded|=decode;self.failed=false;Ok(elapsed)
    }
}

pub(crate) fn prepare_options<'a>(options: &'a Options, execution: &'a ExecutionSpec) -> PrepareOptions<'a> {
    PrepareOptions { threads: options.num_threads, execution: Some(execution),
        trace_plan: (!options.trace_plan.is_empty()).then(|| PathBuf::from(&options.trace_plan)),
        profile_execution: &options.profile_execution, output_dir: PathBuf::from(&options.output_dir), tensors: None }
}

pub(crate) fn open_assets(bundle: &Path, parameters: &Path, options: &Options,
                          metadata: &serde_json::Value) -> Result<AssetStore> {
    if options.hf_model_dir.is_empty() {
        if metadata["execution"]["asset_source"] == "hf" {
            return Err(Error::invalid("HF package requires source, manifest and cache options"));
        }
        AssetStore::open(bundle, parameters)
    } else {
        let e = &metadata["execution"];
        if e["asset_source"] != "hf" {
            return Err(Error::invalid("HF assets require a matching HF package"));
        }
        AssetStore::open_hf(Path::new(&options.hf_model_dir), Path::new(&options.asset_manifest),
            Path::new(&options.cache_dir), parameters,
            e["source_identity"].as_str().ok_or_else(|| Error::invalid("Missing HF identity"))?,
            e["activation_dtype"] == "bf16")
    }
}
