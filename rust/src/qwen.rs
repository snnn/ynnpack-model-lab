// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
//! Config-driven Qwen execution. Architecture and weights belong to the plans.
use crate::frontend::{Frontend, Options};
use crate::{ffi, io, Error, Result};
use serde::Deserialize;
use serde_json::json;
use sha2::{Digest, Sha256};
use std::collections::BTreeMap;
use std::ffi::CString;
use std::fs::{self, File};
use std::io::{BufWriter, Write};
use std::path::{Path, PathBuf};
use std::time::Instant;

// Optional Linux CPU bandwidth window. A missing reader fails instead of hanging.
struct DecodeTrace(Option<File>);
impl DecodeTrace {
    fn open() -> Result<Self> {
        let Some(path) = std::env::var_os("QWEN_REPLAY_TRACE_FIFO") else { return Ok(Self(None)); };
        #[cfg(target_os = "linux")]
        {
            use std::os::unix::fs::{FileTypeExt, OpenOptionsExt};
            let file = fs::OpenOptions::new().write(true).custom_flags(0o4000).open(path)?;
            if !file.metadata()?.file_type().is_fifo() { return Err(Error::invalid("Trace path must be a FIFO")); }
            Ok(Self(Some(file)))
        }
        #[cfg(not(target_os = "linux"))]
        { let _ = path; Err(Error::invalid("Decode bandwidth tracing requires Linux")) }
    }
    fn mark(&mut self, begin: bool) -> Result<()> {
        if let Some(file) = &mut self.0 {
            file.write_all(if begin { b"section_begin decode\n" } else { b"section_end decode\n" })?;
        }
        Ok(())
    }
}

#[derive(Deserialize)]
struct Graph {
    file: String,
    sha256: String,
    logits: Option<String>,
}
#[derive(Deserialize)]
struct Cache {
    name: String,
    shape: Vec<usize>,
    axis: usize,
}
#[derive(Deserialize)]
struct FixedState {
    input: String,
    output: String,
    shape: Vec<usize>,
}
struct StateBuffers {
    input: CString,
    output: CString,
    shape: Vec<usize>,
    current: ffi::Buffer<f32>,
    next: ffi::Buffer<f32>,
}
#[derive(Deserialize)]
struct Package {
    format: String,
    model: String,
    capacity: usize,
    prefill_rows: usize,
    vocabulary: usize,
    graphs: BTreeMap<String, Graph>,
    resources: Vec<Cache>,
    #[serde(default)]
    fixed_states: Vec<FixedState>,
}
struct Session {
    // Graphs drop before every allocation whose pointer they retain.
    graphs: [ffi::PreparedGraph; 2],
    caches: Vec<(CString, ffi::Resource)>,
    states: Vec<StateBuffers>,
    tokens: ffi::Buffer<i32>,
    positions: ffi::Buffer<i32>,
    params: ffi::Buffer<i32>,
    mask: ffi::Buffer<f32>,
    logits: ffi::Buffer<f32>,
    score_logits: Option<ffi::Buffer<f32>>,
    logits_name: CString,
    package: Package,
    position: usize,
    failed: bool,
    trace_output: Option<PathBuf>,
    trace_call: usize,
}
impl Session {
    fn load(root: &Path, parameters: &Path, package: Package, options: &Options) -> Result<Self> {
        if package.format != "qwen3-execution"
            || package.vocabulary == 0
            || package.vocabulary > 2_097_152
            || !matches!(package.model.as_str(), "qwen3" | "qwen3_5")
            || package.capacity == 0
            || package.capacity > 32768
            || package.prefill_rows == 0
            || package.prefill_rows > 128
            || (package.resources.is_empty() && package.fixed_states.is_empty())
            || package.fixed_states.len() > 512
            || package.resources.len() > 512
            || package.graphs.len() != 2
        {
            return Err(Error::invalid("Invalid Qwen package geometry"));
        }
        let assets = ffi::Assets::open(root, parameters)?;
        let mut graphs = Vec::new();
        for phase in ["prefill", "decode"] {
            let spec = package
                .graphs
                .get(phase)
                .ok_or_else(|| Error::invalid("Missing Qwen phase"))?;
            if Path::new(&spec.file).components().count() != 1 {
                return Err(Error::invalid("Invalid plan path"));
            }
            let path = root.join(&spec.file);
            let bytes = io::read_limited(&path, 256 * 1024 * 1024)?;
            if format!("{:x}", Sha256::digest(&bytes)) != spec.sha256 {
                return Err(Error::invalid("Qwen plan identity mismatch"));
            }
            let mut builder = ffi::GraphBuilder::from_plan(assets.clone(), &path)
                .map_err(|e| Error::invalid(format!("{phase} construction: {e}")))?;
            if !options.trace_plan.is_empty() {
                builder.trace(&Path::new(&options.trace_plan).join(format!("{phase}.tsv")))?;
            }
            let profile = options.profile_execution == phase || options.profile_execution == "all";
            if profile {
                builder.profile(
                    &Path::new(&options.output_dir)
                        .join(format!("{phase}_execution_profile.jsonl")),
                )?;
            }
            let mut graph = builder
                .prepare(options.num_threads)
                .map_err(|e| Error::invalid(format!("{phase} preparation: {e}")))?;
            if profile {
                graph.profile_step("", 0, 0, 0, 0)?;
            }
            graphs.push(graph);
        }
        let graphs: [ffi::PreparedGraph; 2] = graphs
            .try_into()
            .map_err(|_| Error::invalid("Phase count"))?;
        let mut caches: Vec<(CString, ffi::Resource)> = Vec::new();
        for spec in &package.resources {
            let name = ffi::string(&spec.name)?;
            if spec.shape.len() != 4
                || spec.axis >= 4
                || spec.shape[spec.axis] != package.capacity
                || spec.shape.iter().any(|&x| x == 0)
                || spec.shape[0] != 1
                || spec.shape[1] > 1024
                || !matches!(spec.axis, 2 | 3)
                || spec.shape[5 - spec.axis] > 4096
                || caches.iter().any(|(n, _)| n == &name)
            {
                return Err(Error::invalid("Invalid Qwen resource"));
            }
            caches.push((
                name.clone(),
                ffi::Resource::new_typed(&graphs[0], &name, &spec.shape, 4)?,
            ));
        }
        let mut states: Vec<StateBuffers> = Vec::new();
        for spec in &package.fixed_states {
            let count = spec.shape.iter().try_fold(1usize, |n, &d| n.checked_mul(d));
            if spec.shape.is_empty()
                || spec.shape.len() > 4
                || spec.shape.contains(&0)
                || count.is_none_or(|n| n > 16_777_216)
                || spec.input == spec.output
                || states.iter().any(|s| {
                    s.input.to_bytes() == spec.input.as_bytes()
                        || s.output.to_bytes() == spec.output.as_bytes()
                })
            {
                return Err(Error::invalid("Invalid fixed state contract"));
            }
            states.push(StateBuffers {
                input: ffi::string(&spec.input)?,
                output: ffi::string(&spec.output)?,
                shape: spec.shape.clone(),
                current: ffi::Buffer::new(count.unwrap(), 0.0),
                next: ffi::Buffer::new(count.unwrap(), 0.0),
            });
        }
        let logits_name = ffi::string(
            package.graphs["decode"]
                .logits
                .as_deref()
                .ok_or_else(|| Error::invalid("Missing logits output"))?,
        )?;
        let rows = package.prefill_rows;
        Ok(Self {
            graphs,
            caches,
            states,
            tokens: ffi::Buffer::new(rows, 0),
            positions: ffi::Buffer::new(rows, 0),
            params: ffi::Buffer::new(7, 0),
            mask: ffi::Buffer::new(rows * package.capacity, 0.0),
            logits: ffi::Buffer::new(package.vocabulary, 0.0),
            score_logits: package.graphs["prefill"].logits.as_ref().map(|_| ffi::Buffer::new(rows * package.vocabulary, 0.0)),
            logits_name,
            package,
            position: 0,
            failed: false,
            trace_output: (!options.trace_plan.is_empty())
                .then(|| Path::new(&options.output_dir).join("trace")),
            trace_call: 0,
        })
    }
    fn reset(&mut self) -> Result<()> {
        self.failed = true;
        for (_, cache) in &mut self.caches {
            cache.reset()?;
        }
        for state in &mut self.states {
            state.current.fill(0.0);
            state.next.fill(0.0);
        }
        self.position = 0;
        self.failed = false;
        Ok(())
    }
    fn invoke(
        &mut self,
        tokens: &[i32],
        decode: bool,
        profile: Option<(&str, i32, usize)>,
    ) -> Result<f64> {
        let valid = tokens.len();
        let rows = if decode { 1 } else { self.package.prefill_rows };
        if self.failed
            || valid == 0
            || valid > rows
            || self.position + valid > self.package.capacity
            || tokens
                .iter()
                .any(|&x| x < 0 || x as usize >= self.package.vocabulary)
        {
            return Err(Error::invalid("Invalid Qwen request or poisoned session"));
        }
        self.tokens[..rows].fill(0);
        self.tokens[..valid].copy_from_slice(tokens);
        for (i, p) in self.positions[..rows].iter_mut().enumerate() {
            *p = (self.position + i) as i32;
        }
        self.params.fill(0);
        self.params[0] = self.position as i32;
        self.params[1] = (self.position + valid) as i32;
        self.params[2] = self.params[1];
        let capacity = self.package.capacity;
        for i in 0..rows {
            for j in 0..capacity {
                self.mask[i * capacity + j] = if j <= self.position + i && j < self.position + valid
                {
                    0.0
                } else {
                    f32::MIN
                };
            }
        }
        let graph = &mut self.graphs[usize::from(decode)];
        graph.scalar(c"position", self.position as i64)?;
        graph.scalar(c"valid_rows", valid as i64)?;
        // Allocations remain stable and exclusively owned until synchronous
        // run() returns. Both phases bind the same resource handles.
        unsafe {
            graph.bind_bytes(c"token_ids", &self.tokens, rows * 4, &[1, rows], true)?;
            graph.bind_bytes(c"input_pos", &self.positions, rows * 4, &[rows], true)?;
            graph.bind(c"param_tensor", &self.params, &[1, 1, 1, 7], true)?;
            graph.bind_bytes(
                c"mask",
                &self.mask,
                rows * capacity * 4,
                &[1, 1, rows, capacity],
                true,
            )?;
            for state in &self.states {
                graph.bind(&state.input, &state.current, &state.shape, true)?;
                graph.bind(&state.output, &state.next, &[], false)?;
            }
            if decode {
                graph.bind(&self.logits_name, &self.logits, &[], false)?;
            } else if let Some(logits) = &self.score_logits {
                graph.bind(&ffi::string(self.package.graphs["prefill"].logits.as_deref().unwrap())?, logits, &[], false)?;
            }
            for (name, cache) in &mut self.caches {
                graph.resource(name, cache)?;
            }
        }
        if let Some((name, rep, step)) = profile {
            graph.profile_step_rows(name, rep, step, self.position, valid, !decode, 1)?;
        }
        let start = Instant::now();
        self.failed = true;
        graph.run()?;
        let elapsed = start.elapsed().as_secs_f64() * 1000.0;
        if let Some(output) = &self.trace_output {
            graph.save_trace(&output.join(format!("call_{:04}", self.trace_call)))?;
            self.trace_call += 1;
        }
        // Commit replacement state only after the synchronous invocation and
        // trace writes succeed. A late failure still poisons the KV session.
        for state in &mut self.states {
            std::mem::swap(&mut state.current, &mut state.next);
        }
        self.position += valid;
        self.failed = false;
        if let Some((name, rep, step)) = profile {
            graph.profile_step_rows(name, rep, step, self.position - valid, valid, !decode, 2)?;
        }
        if decode && self.logits.iter().any(|x| !x.is_finite()) {
            self.failed = true;
            return Err(Error::invalid("Nonfinite Qwen logits"));
        }
        Ok(elapsed)
    }
}
pub(crate) fn main(args: &[String]) -> Result<()> {
    // Diagnostic chunking changes only valid rows, never the prepared shape.
    let mut arguments = args.to_vec();
    let score_tokens = if let Some(i) = arguments.iter().position(|s| s == "--score_tokens") {
        arguments.remove(i); true
    } else { false };
    let chunk_size = if let Some(i) = arguments
        .iter()
        .position(|s| s.starts_with("--prefill_chunk_size="))
    {
        let value = arguments.remove(i);
        Some(
            value.split_once('=').unwrap().1.parse::<usize>()
                .map_err(|_| Error::invalid("Invalid prefill chunk size"))?,
        )
    } else {
        None
    };
    let Some(o) = Options::parse(&arguments, true)? else {
        return Ok(());
    };
    if score_tokens && (o.warmup_runs != 0 || o.measured_runs != 1 ||
        o.profile_execution != "none" || o.report_memory || o.dump_outputs ||
        !o.trace_plan.is_empty() || o.dump_pipeline) {
        return Err(Error::invalid("Scoring requires zero warmups, one repetition and no diagnostics"));
    }
    let root = Path::new(o.graph_dir.as_deref().unwrap_or(&o.bundle_dir));
    let package: Package = serde_json::from_slice(&io::read_limited(
        &root.join("model.json"),
        4 * 1024 * 1024,
    )?)?;
    if o.cache_capacity != package.capacity || o.prefill_rows != package.prefill_rows {
        return Err(Error::invalid("Capacity/prefill rows differ from package"));
    }
    let chunk_size = chunk_size.unwrap_or(package.prefill_rows);
    if score_tokens != package.graphs.get("prefill").is_some_and(|g| g.logits.is_some()) {
        return Err(Error::invalid("Scoring requires a scoring package; benchmark packages omit prefill logits"));
    }
    if chunk_size == 0 || chunk_size > package.prefill_rows {
        return Err(Error::invalid("Prefill chunk size exceeds prepared rows"));
    }
    let frontend = Frontend::resolve(&o, Some(package.vocabulary))?;
    let output = Path::new(&o.output_dir);
    io::new_directory(output)?;
    frontend.save(output)?;
    let mut trace = DecodeTrace::open()?;
    if trace.0.is_some() && (score_tokens || o.profile_execution != "none" || o.report_memory || o.dump_outputs ||
                            !o.trace_plan.is_empty() || o.dump_pipeline) {
        return Err(Error::invalid("Bandwidth tracing requires a run without diagnostics"));
    }
    io::json(
        &output.join("run.json"),
        &json!({
            "runner": "qwen3", "graph_dir": root, "threads": o.num_threads,
            "cache_capacity": package.capacity, "prefill_rows": package.prefill_rows, "prefill_chunk_size": chunk_size,
            "warmups": o.warmup_runs, "repetitions": o.measured_runs,
            "ynn_math": ffi::math_mode()?,
            "profile_execution": o.profile_execution, "trace_plan": o.trace_plan,
            "timings_valid_for_benchmark": !score_tokens && o.profile_execution == "none"
                && !o.report_memory && !o.dump_outputs && o.trace_plan.is_empty(),
        }),
    )?;
    let start = Instant::now();
    let mut session = Session::load(root, Path::new(&o.parameter_dir), package, &o)?;
    io::json(
        &output.join("setup.json"),
        &json!({"model":session.package.model,
        "setup_ms":start.elapsed().as_secs_f64()*1000.0,"threads":o.num_threads,
        "rss_bytes":ffi::rss(),"peak_rss_bytes":ffi::peak_rss()}),
    )?;
    if score_tokens {
        let mut records = Vec::new();
        let (mut nll, mut tokens) = (0.0f64, 0usize);
        for case in &frontend.cases {
            let ids = [&case.prompt[..], &case.continuation[..]].concat();
            if ids.len() < 2 || ids.len() > session.package.capacity { return Err(Error::invalid("Invalid scoring sequence")); }
            session.reset()?;
            let mut loss = 0.0;
            for (step, chunk) in ids[..ids.len()-1].chunks(chunk_size).enumerate() {
                session.invoke(chunk, false, None)?;
                let logits = session.score_logits.as_ref().unwrap();
                let vocabulary = session.package.vocabulary;
                for row in 0..chunk.len() {
                    let values = &logits[row*vocabulary..(row+1)*vocabulary];
                    if values.iter().any(|x| !x.is_finite()) { return Err(Error::invalid("Nonfinite scoring logits")); }
                    let max = values.iter().copied().fold(f32::NEG_INFINITY, f32::max) as f64;
                    let normalizer = values.iter().map(|&x| (x as f64 - max).exp()).sum::<f64>().ln() + max;
                    let position = step*chunk_size+row;
                    loss += normalizer - values[ids[position+1] as usize] as f64;
                    if [127,1023,2031].contains(&position) {
                        io::write_f32(&output.join(format!("{}_position{position}.logits.bin",case.name)), values)?;
                    }
                }
            }
            nll += loss; tokens += ids.len()-1;
            records.push(json!({"case":case.name,"tokens":ids.len()-1,"nll":loss,"mean_loss":loss/(ids.len()-1) as f64}));
            io::json(&output.join("progress.json"), &records)?;
        }
        io::json(&output.join("quality.json"), &json!({"cases":records,"tokens":tokens,"mean_loss":nll/tokens as f64,"perplexity":(nll/tokens as f64).exp()}))?;
        io::json(&output.join("completion.json"), &json!({"status":"completed","cases":frontend.cases.len()}))?;
        return Ok(());
    }
    if o.dump_pipeline || o.report_memory {
        for (i, g) in session.graphs.iter_mut().enumerate() {
            let path = output.join(if i == 0 {
                "prefill.pipeline"
            } else {
                "decode.pipeline"
            });
            g.diagnostics(o.dump_pipeline.then_some(path.as_path()), o.report_memory)?;
        }
    }
    let mut timings = BufWriter::new(File::create(output.join("timings.jsonl"))?);
    let mut windows = BufWriter::new(File::create(output.join("trace.jsonl"))?);
    for case in &frontend.cases {
        if case.prompt.len() + case.continuation.len() > session.package.capacity {
            return Err(Error::invalid("Case exceeds context capacity"));
        }
        for rep in -o.warmup_runs..o.measured_runs {
            session.reset()?;
            let start = Instant::now();
            let mut prefix_graph_ms = 0.0;
            for (step, chunk) in case.prompt[..case.prompt.len() - 1]
                .chunks(chunk_size)
                .enumerate()
            {
                let profile = (rep >= 0
                    && ["all", "prefill"].contains(&o.profile_execution.as_str()))
                .then_some((case.name.as_str(), rep, step));
                prefix_graph_ms += session.invoke(chunk, false, profile)?;
            }
            let prefix_ms = start.elapsed().as_secs_f64() * 1000.0;
            let mut trace_start = Instant::now();
            for (step, token) in case
                .prompt
                .last()
                .into_iter()
                .chain(&case.continuation)
                .enumerate()
            {
                if step == 1 && rep >= 0 && trace.0.is_some() {
                    trace.mark(true)?;
                    trace_start = Instant::now();
                }
                let start = Instant::now();
                let profile = (rep >= 0
                    && ["all", "decode"].contains(&o.profile_execution.as_str()))
                .then_some((case.name.as_str(), rep, step));
                let decode_ms = session.invoke(&[*token], true, profile)?;
                let argmax = session
                    .logits
                    .iter()
                    .enumerate()
                    .max_by(|a, b| a.1.total_cmp(b.1))
                    .unwrap()
                    .0;
                let token_ms = start.elapsed().as_secs_f64() * 1000.0;
                if rep >= 0 {
                    writeln!(
                        timings,
                        "{}",
                        json!({"case":case.name,"rep":rep,"step":step,"prompt_tokens":case.prompt.len(),
                        "prefix_ms":prefix_ms,"prefix_graph_ms":prefix_graph_ms,
                        "decode_ms":decode_ms,"token_ms":token_ms,"argmax":argmax,"position":session.position})
                    )?;
                    if o.dump_outputs {
                        io::write_f32(
                            &output.join(format!("{}_r{rep}_s{step}.logits.bin", case.name)),
                            &session.logits,
                        )?;
                    }
                }
            }
            if rep >= 0 && trace.0.is_some() && !case.continuation.is_empty() {
                trace.mark(false)?;
                writeln!(windows, "{}", json!({"case":case.name,"rep":rep,
                    "tokens":case.continuation.len(),"elapsed_ms":trace_start.elapsed().as_secs_f64()*1000.0}))?;
            }
            if rep >= 0 && o.dump_outputs {
                for state in &session.states {
                    io::write_f32(
                        &output.join(format!(
                            "{}_r{rep}_{}.bin", case.name, state.input.to_string_lossy()
                        )),
                        &state.current,
                    )?;
                }
                for (name, cache) in &session.caches {
                    let data = cache.data();
                    // The resource exposes signed bytes; this changes only their
                    // view, with the same allocation, alignment and length.
                    let bytes = unsafe {
                        std::slice::from_raw_parts(data.as_ptr().cast::<u8>(), data.len())
                    };
                    fs::write(
                        output.join(format!(
                            "{}_r{rep}_{}.bin",
                            case.name,
                            name.to_string_lossy()
                        )),
                        bytes,
                    )?;
                }
            }
        }
    }
    let counters = session
        .graphs
        .iter()
        .map(|g| g.counters())
        .collect::<Result<Vec<_>>>()?;
    io::json(&output.join("counters.json"),&counters.iter().map(|c|json!({
        "append_bytes":c.append_bytes,"view_copy_bytes":c.view_copy_bytes,"append_calls":c.append_calls})).collect::<Vec<_>>())?;
    io::json(
        &output.join("memory.json"),
        &json!({"rss_bytes":ffi::rss(),"peak_rss_bytes":ffi::peak_rss()}),
    )?;
    timings.flush()?;
    windows.flush()?;
    io::json(&output.join("completion.json"), &json!({"status":"completed","cases":frontend.cases.len()}))?;
    Ok(())
}
