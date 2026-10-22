// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
use super::package::{self, Package, Recipe};
use crate::{ffi, io, Error, Result};
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
enum Buffer { Float(ffi::Buffer<f32>), Int(ffi::Buffer<i32>) }
struct Input { spec: package::Input, name: CString, buffer: Buffer }
pub(super) struct Session {
    // Native graphs retain storage pointers. Always destroy them first.
    pub graphs: [ffi::PreparedGraph;2],
    pub caches: Vec<(CString, ffi::Resource)>,
    pub states: Vec<StateBuffers>,
    inputs: [Vec<Input>;2],
    embeddings: BTreeMap<String,ffi::Embedding>,
    pub logits: ffi::Buffer<f32>,
    pub score_logits: Option<ffi::Buffer<f32>>,
    pub package: Package,
    pub position: usize,
    failed: bool,
    decoded: bool,
    trace_output: Option<PathBuf>,
    trace_call: usize,
}
impl Session {
    pub fn load(root:&Path, bundle:&Path, parameters:&Path, package:Package, options:&Options) -> Result<Self> {
        package.validate()?;
        package.validate_files(root)?;
        let assets=ffi::Assets::open(bundle,parameters)?;
        let embeddings=package.embeddings.iter().map(|(k,e)| Ok((k.clone(),ffi::Embedding::new(assets.clone(),e,package.vocabulary)?)))
            .collect::<Result<BTreeMap<_,_>>>()?;
        let mut gs=Vec::new();
        let mut inputs=[Vec::new(),Vec::new()];
        for (i,phase) in ["prefill","decode"].iter().enumerate() {
            let g=&package.graphs[*phase];
            let mut builder=ffi::GraphBuilder::from_plan(assets.clone(),&root.join(&g.file))?;
            if !options.trace_plan.is_empty(){builder.trace(&Path::new(&options.trace_plan).join(format!("{phase}.tsv")))?;}
            if options.profile_execution==*phase || options.profile_execution=="all" {
                builder.profile(&Path::new(&options.output_dir).join(format!("{phase}_execution_profile.jsonl")))?;
            }
            let mut graph=builder.prepare(options.num_threads)?;
            if options.profile_execution==*phase || options.profile_execution=="all" {
                graph.profile_step("",0,0,0,0)?;
            }
            gs.push(graph);
            for spec in &g.inputs {
                let n=package::count(&spec.dimensions(if i==0{package.prefill_rows}else{1},package.capacity)?)?;
                inputs[i].push(Input{spec:spec.clone(),name:ffi::string(&spec.name)?,buffer:
                    if spec.dtype=="int32"{Buffer::Int(ffi::Buffer::new(n,0))}else{Buffer::Float(ffi::Buffer::new(n,0.0))}});
            }
        }
        let graphs:[ffi::PreparedGraph;2]=gs.try_into().map_err(|_|Error::invalid("Phase count"))?;
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
            trace_output:(!options.trace_plan.is_empty()).then(||Path::new(&options.output_dir).join("trace")),trace_call:0})
    }
    /// Explicitly install a prepared larger variant of the same program.
    /// `load` prepares all phases before this call. It never grows on invoke.
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
