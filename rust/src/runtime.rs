// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
//! Experimental preparation of semantic programs in the invoking process.
//! Compilation happens once here; invocation only uses prepared native graphs.
pub mod execution;
pub use execution::ExecutionSpec;
use crate::{compiler, ffi, plan::{Arg, ValidatedPlan}, Error, Result};
use serde::Serialize;
use std::{collections::BTreeMap, path::{Path, PathBuf}, rc::Rc, time::Instant};

/// Immutable mapped source assets plus owned, aligned generated constants.
/// Handles deliberately remain !Send and !Sync, like the native graphs.
pub struct AssetStore { pub(crate) assets: Rc<ffi::Assets> }
impl AssetStore {
    pub fn open(bundle: &Path, parameters: &Path) -> Result<Self> {
        Ok(Self { assets: ffi::Assets::open(bundle, parameters)? })
    }
}

pub struct PrepareOptions<'a> {
    pub threads: usize,
    pub execution: Option<&'a ExecutionSpec>,
    pub trace_plan: Option<PathBuf>,
    pub profile_execution: &'a str,
    pub output_dir: PathBuf,
}
impl Default for PrepareOptions<'_> {
    fn default() -> Self {
        Self { threads: 4, execution: None, trace_plan: None,
            profile_execution: "none", output_dir: PathBuf::new() }
    }
}

#[derive(Default, Clone, Debug, Serialize)]
pub struct PreparationStats {
    pub compiler: compiler::CompileTimings,
    pub parse_ms: f64,
    pub interface_ms: f64,
    pub assets_ms: f64,
    pub native_construct_ms: f64,
    pub native_compile_ms: f64,
    pub total_ms: f64,
    pub generated_constant_bytes: usize,
    pub plan_text_bytes: usize,
    pub compiler_calls: usize,
    pub prepared_phases: usize,
}

pub struct PreparedProgram {
    // Fields are destroyed in declaration order: graphs before their storage.
    pub(crate) graphs: BTreeMap<String, ffi::PreparedGraph>,
    pub(crate) assets: Rc<ffi::Assets>,
    pub(crate) execution: Option<ExecutionSpec>,
    pub(crate) trace_output: Option<PathBuf>,
    pub stats: PreparationStats,
}

pub fn prepare(program: &compiler::Program, mut assets: AssetStore,
               options: PrepareOptions<'_>) -> Result<PreparedProgram> {
    let start = Instant::now();
    let (mut compiled, compiler) = compiler::compile_measured(program)?;
    let mut stats = PreparationStats { compiler, compiler_calls: 1, ..Default::default() };
    let at = Instant::now();
    stats.generated_constant_bytes = Rc::get_mut(&mut assets.assets)
        .ok_or_else(|| Error::invalid("Asset store was shared before preparation"))?
        .add_generated(std::mem::take(&mut compiled.assets))?;
    stats.assets_ms = at.elapsed().as_secs_f64() * 1000.0;
    let at = Instant::now();
    stats.plan_text_bytes = compiled.plans.values().map(String::len).sum();
    let plans = compiled.plans.iter().map(|(name, text)|
        Ok((name.clone(), ValidatedPlan::from_bytes(text.as_bytes())?)))
        .collect::<Result<BTreeMap<_, _>>>()?;
    stats.parse_ms = at.elapsed().as_secs_f64() * 1000.0;
    // Do not retain semantic clones, emitted text, reports or constant Vecs.
    drop(compiled);
    let mut prepared = prepare_plans(plans, assets, options, stats)?;
    prepared.stats.total_ms = start.elapsed().as_secs_f64() * 1000.0;
    Ok(prepared)
}

pub(crate) fn prepare_plans(plans: BTreeMap<String, ValidatedPlan>, assets: AssetStore,
                           options: PrepareOptions<'_>, mut stats: PreparationStats) -> Result<PreparedProgram> {
    if !(1..=256).contains(&options.threads)
        || !["none", "prefill", "decode", "all"].contains(&options.profile_execution) {
        return Err(Error::invalid("Invalid preparation options"));
    }
    let start = Instant::now();
    let at = Instant::now();
    if let Some(spec) = options.execution {
        spec.validate()?;
        if spec.graphs.keys().ne(plans.keys()) {
            return Err(Error::invalid("Execution phases differ from program"));
        }
        for (phase, plan) in &plans { spec.validate_plan(phase, plan)?; }
    }
    stats.interface_ms += at.elapsed().as_secs_f64() * 1000.0;
    let at = Instant::now();
    // Validate all phase assets before native graph construction starts.
    for plan in plans.values() {
        for command in plan.commands() {
            for arg in command.wire().args {
                if let Arg::Data(Some(data)) = arg { assets.assets.verify(&data)?; }
            }
        }
    }
    if let Some(spec) = options.execution {
        for embedding in spec.embeddings.values() {
            for asset in &embedding.assets {
                assets.assets.verify(&crate::plan::Data {
                    path: asset.path.clone(), bytes: asset.bytes, sha256: asset.sha256.clone() })?;
            }
        }
    }
    stats.assets_ms += at.elapsed().as_secs_f64() * 1000.0;
    let mut graphs = BTreeMap::new();
    let mut plans = plans.into_iter().collect::<Vec<_>>();
    plans.sort_by_key(|(phase, _)| (phase != "prefill", phase.clone()));
    for (phase, plan) in plans {
        let at = Instant::now();
        let mut builder = ffi::GraphBuilder::from_validated_plan(assets.assets.clone(), plan)?;
        if let Some(path) = &options.trace_plan { builder.trace(&path.join(format!("{phase}.tsv")))?; }
        let profile = options.profile_execution == "all" || options.profile_execution == phase;
        if profile { builder.profile(&options.output_dir.join(format!("{phase}_execution_profile.jsonl")))?; }
        stats.native_construct_ms += at.elapsed().as_secs_f64() * 1000.0;
        let at = Instant::now();
        let mut graph = builder.prepare(options.threads)?;
        if profile { graph.profile_step("", 0, 0, 0, 0)?; }
        stats.native_compile_ms += at.elapsed().as_secs_f64() * 1000.0;
        graphs.insert(phase, graph);
    }
    stats.prepared_phases = graphs.len();
    stats.total_ms = start.elapsed().as_secs_f64() * 1000.0;
    Ok(PreparedProgram { graphs, assets: assets.assets, execution: options.execution.cloned(),
        trace_output: options.trace_plan.map(|_| options.output_dir.join("trace")), stats })
}

#[cfg(feature = "llm")]
pub use crate::llm::session::Session;
