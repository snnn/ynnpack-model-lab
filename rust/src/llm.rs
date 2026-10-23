// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
//! Model-independent execution. All tensor roles and state bindings come from data.
use crate::frontend::{Frontend, Options};
use crate::{ffi, io, Error, Result};

use serde_json::json;



use std::fs::{self, File};
use std::io::{BufWriter, Write};
use std::path::Path;
pub(crate) mod package;
pub(crate) mod session;
use package::Package;
use session::Session;
use std::time::Instant;

// Optional Linux CPU bandwidth window. A missing reader fails instead of hanging.
struct DecodeTrace(Option<File>);
impl DecodeTrace {
    fn open() -> Result<Self> {
        let Some(path) = std::env::var_os("YNN_REPLAY_TRACE_FIFO").or_else(||std::env::var_os("QWEN_REPLAY_TRACE_FIFO")) else { return Ok(Self(None)); };
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

#[cfg(feature="llm-tests")]
pub(crate) fn main(args: &[String]) -> Result<()> { tests::run(args) }

#[cfg(not(feature="llm-tests"))]
pub(crate) fn main(args: &[String]) -> Result<()> {
    if let Some(path)=args.iter().find_map(|s|s.strip_prefix("--check_package=")) {
        if args.len()!=2 {return Err(Error::invalid("--check_package requires only a package directory"));}
        crate::runtime::package::ModelPackage::read(Path::new(path))?.validate()?;
        println!("Package graphs and interfaces verified");return Ok(());
    }
    // Diagnostic chunking changes only valid rows, never the prepared shape.
    let mut arguments = args.to_vec();
    let score_tokens = if let Some(i) = arguments.iter().position(|s| s == "--score_tokens") {
        arguments.remove(i); true
    } else { false };
    let dump_state_steps = if let Some(i) = arguments.iter().position(|s| s == "--dump_state_steps") {
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
    fn take_option(args: &mut Vec<String>, name: &str) -> Result<Option<String>> {
        let mut result = None;
        let mut i = 1;
        while i < args.len() {
            let value = if args[i] == name {
                args.remove(i);
                if i == args.len() { return Err(Error::invalid(format!("Missing value for {name}"))); }
                Some(args.remove(i))
            } else if args[i].starts_with(&format!("{name}=")) {
                Some(args.remove(i).split_once('=').unwrap().1.to_owned())
            } else { None };
            if let Some(value) = value {
                if value.is_empty() || result.replace(value).is_some() {
                    return Err(Error::invalid(format!("Empty/repeated {name}")));
                }
            } else { i += 1; }
        }
        Ok(result)
    }
    let prepare_drop = take_option(&mut arguments, "--prepare-drop")?
        .map(|s| s.parse::<usize>().ok().filter(|n| (1..=16).contains(n))
            .ok_or_else(|| Error::invalid("--prepare-drop must be 1..16"))).transpose()?;
    let program_path = take_option(&mut arguments, "--program")?;
    let qwen_assets = take_option(&mut arguments, "--qwen-assets")?;
    let execution_path = take_option(&mut arguments, "--execution")?;
    if (program_path.is_some() && qwen_assets.is_some()) ||
        (execution_path.is_some() && program_path.is_none()) {
        return Err(Error::invalid("Choose --program with --execution, or --qwen-assets"));
    }
    if arguments.iter().any(|s| s == "--help" || s == "-h") {
        println!("Semantic preparation: --program=FILE [--execution=FILE] or --qwen-assets=FILE; mutually exclusive with --model_dir");
        println!("--dump_state_steps adds per-decode state snapshots to --dump_outputs (potentially large)");
    }
    if arguments.iter().any(|s| s.starts_with("--graph_dir")) {
        return Err(Error::invalid("Offline graph loading is retired; use --model_dir with a semantic package"));
    }
    if program_path.is_none() && qwen_assets.is_none() && !arguments.iter().any(|s| s.starts_with("--model_dir")) {
        let name = Path::new(&arguments[0]).file_stem().and_then(|s| s.to_str()).unwrap_or("");
        if ["gemma4_e2b", "gemma4_e4b"].contains(&name) {
            arguments.push(format!("--model_dir=models/{name}/generated"));
        }
    }
    let Some(mut o) = Options::parse(&arguments, true)? else {
        return Ok(());
    };
    if dump_state_steps && !o.dump_outputs {
        return Err(Error::invalid("--dump_state_steps requires --dump_outputs"));
    }
    if score_tokens && (o.warmup_runs != 0 || o.measured_runs != 1 ||
        o.profile_execution != "none" || o.report_memory || o.dump_outputs ||
        !o.trace_plan.is_empty() || o.dump_pipeline) {
        return Err(Error::invalid("Scoring requires zero warmups, one repetition and no diagnostics"));
    }
    let root = Path::new(o.model_dir.as_deref().unwrap_or(&o.bundle_dir));
    if o.model_dir.is_some() && (program_path.is_some() || qwen_assets.is_some()) {
        return Err(Error::invalid("Runtime program input and --model_dir are mutually exclusive"));
    }
    let load_start = Instant::now();
    let mut metadata = serde_json::Value::Null;
    let (program, package, source) = if let Some(path) = &program_path {
        let program = serde_json::from_slice::<crate::compiler::Program>(&io::read_limited(Path::new(path), 128*1024*1024)?)?;
        let default = Path::new(path).with_file_name("execution.json");
        let spec = execution_path.as_ref().map(Path::new).unwrap_or(&default);
        let spec: crate::runtime::ExecutionSpec = serde_json::from_slice(&io::read_limited(spec,16*1024*1024)?)?;
        spec.validate()?;
        (program, spec, "program")
    } else if let Some(path) = &qwen_assets {
        let assets: crate::models::qwen3::Assets = serde_json::from_slice(&io::read_limited(Path::new(path),128*1024*1024)?)?;
        let p = assets.program(o.cache_capacity as i64, o.prefill_rows as i64)?;
        let spec = assets.execution(&p, o.cache_capacity as i64, o.prefill_rows as i64)?;
        (p, spec, "qwen-assets")
    } else {
        let p = Package::read(root)?;
        let spec = p.spec.clone();
        metadata = p.metadata;
        (p.program, spec, "semantic-package")
    };
    let load_ms = load_start.elapsed().as_secs_f64()*1000.0;
    if !arguments.iter().any(|a| a.starts_with("--cache_capacity=")) {
        o.cache_capacity = package.capacity;
    }
    if !arguments.iter().any(|a| a.starts_with("--prefill_rows=")) {
        o.prefill_rows = package.prefill_rows;
    }
    let package = package.with_capacity(o.cache_capacity)?;
    if o.prefill_rows != package.prefill_rows {
        return Err(Error::invalid("Prefill rows differ from package; use --prefill_chunk_size to select smaller chunks"));
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
    if !metadata.is_null() { io::json(&output.join("model.json"), &metadata)?; }
    let mut trace = DecodeTrace::open()?;
    if trace.0.is_some() && (score_tokens || o.profile_execution != "none" || o.report_memory || o.dump_outputs ||
                            !o.trace_plan.is_empty() || o.dump_pipeline) {
        return Err(Error::invalid("Bandwidth tracing requires a run without diagnostics"));
    }
    io::json(
        &output.join("run.json"),
        &json!({
            "runner": "ynn-llm", "model_dir": root, "threads": o.num_threads,
            "preparation_source": source, "program": program_path, "qwen_assets": qwen_assets,
            "package_identity": metadata["package"],
            "profile": metadata["profile"].as_str().or_else(|| metadata["execution"]["profile"].as_str()),
            "source_identity": metadata["source_identity"].as_str().or_else(|| metadata["execution"]["source_identity"].as_str()),
            "cache_capacity": package.capacity, "prefill_rows": package.prefill_rows, "prefill_chunk_size": chunk_size,
            "warmups": o.warmup_runs, "repetitions": o.measured_runs,
            "ynn_math": ffi::math_mode()?,
            "profile_execution": o.profile_execution, "trace_plan": o.trace_plan,
            "timings_valid_for_benchmark": prepare_drop.is_none() && !score_tokens && o.profile_execution == "none"
                && !o.report_memory && !o.dump_outputs && !o.dump_pipeline && o.trace_plan.is_empty(),
        }),
    )?;
    if let Some(repetitions) = prepare_drop {
        let mut records = Vec::new();
        for repetition in 0..repetitions {
            let before = ffi::allocator_bytes();
            let start = Instant::now();
            let assets = session::open_assets(Path::new(&o.bundle_dir),Path::new(&o.parameter_dir), &o, &metadata)?;
            let prepared = crate::runtime::prepare(&program,assets,session::prepare_options(&o,&package))?;
            let session = Session::from_prepared(prepared,package.clone())?;
            let mut record = json!({"repetition":repetition,"prepare_ms":start.elapsed().as_secs_f64()*1000.0,
                "before_allocator":before,"prepared_rss":ffi::rss(),"prepared_allocator":ffi::allocator_bytes(),
                "preparation":session.preparation});
            drop(session);
            record["after_drop_rss"] = json!(ffi::rss());
            record["after_drop_allocator"] = json!(ffi::allocator_bytes());
            records.push(record);
            io::json(&output.join("preparation_lifecycle.json"),&records)?;
        }
        io::json(&output.join("completion.json"),&json!({"status":"completed","prepare_drop":repetitions}))?;
        return Ok(());
    }
    let start = Instant::now();
    let assets = session::open_assets(Path::new(&o.bundle_dir), Path::new(&o.parameter_dir), &o, &metadata)?;
    let prepared = crate::runtime::prepare(&program, assets, session::prepare_options(&o, &package))?;
    drop(program);
    let mut session = Session::from_prepared(prepared, package)?;
    io::json(
        &output.join("setup.json"),
        &json!({"model":session.package.model,
        "setup_ms":load_ms+start.elapsed().as_secs_f64()*1000.0,"threads":o.num_threads,
        "model_load_or_author_ms":load_ms,"preparation":session.preparation,
        "allocator_bytes":ffi::allocator_bytes(),
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
    let mut memory = if o.report_memory {
        Some(BufWriter::new(File::create(output.join("memory.jsonl"))?))
    } else { None };
    if let Some(out) = &mut memory { memory_record(&session, "setup", out)?; }
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
            if let Some(out) = &mut memory {
                memory_record(&session, &format!("{}/{rep}/prefix", case.name), out)?;
            }
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
                let argmax = greedy_argmax(&session.logits);
                let token_ms = start.elapsed().as_secs_f64() * 1000.0;
                if step == 0 {
                    if let Some(out) = &mut memory {
                        memory_record(&session, &format!("{}/{rep}/first_decode", case.name), out)?;
                    }
                }
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
                        if dump_state_steps {
                            dump_state(&session, output, &format!("{}_r{rep}_s{step}",case.name))?;
                        }
                    }
                }
            }
            if rep >= 0 && trace.0.is_some() && !case.continuation.is_empty() {
                trace.mark(false)?;
                writeln!(windows, "{}", json!({"case":case.name,"rep":rep,
                    "tokens":case.continuation.len(),"elapsed_ms":trace_start.elapsed().as_secs_f64()*1000.0}))?;
            }
            if rep >= 0 && o.dump_outputs {
                dump_state(&session, output, &format!("{}_r{rep}",case.name))?;
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
    if let Some(out) = &mut memory { out.flush()?; }
    timings.flush()?;
    windows.flush()?;
    io::json(&output.join("completion.json"), &json!({"status":"completed","cases":frontend.cases.len()}))?;
    Ok(())
}

#[cfg(feature="llm-tests")]
mod tests;

fn dump_state(session: &Session, output: &Path, prefix: &str) -> Result<()> {
    for state in &session.states {
        io::write_f32(&output.join(format!("{prefix}_{}.bin",state.input.to_string_lossy())), &state.current)?;
    }
    for (name, cache) in &session.caches {
        let data = cache.data();
        let bytes = unsafe { std::slice::from_raw_parts(data.as_ptr().cast::<u8>(), data.len()) };
        fs::write(output.join(format!("{prefix}_{}.bin",name.to_string_lossy())),bytes)?;
    }
    Ok(())
}

fn greedy_argmax(logits: &[f32]) -> usize {
    // Equal logits select the lowest token ID, including signed-zero ties.
    let mut best = 0;
    for (index, &value) in logits.iter().enumerate() {
        if value > logits[best] { best = index; }
    }
    best
}

fn memory_record(session: &Session, phase: &str, out: &mut impl Write) -> Result<()> {
    let mut record =
        json!({"phase":phase, "rss_kib":ffi::rss()/1024, "peak_rss_kib":ffi::peak_rss()/1024});
    for (i, name) in ["prefill", "decode"].iter().enumerate() {
        let m = session.graphs[i].memory()?;
        for (field, value) in [
            ("root_scratch_bytes", m.root),
            ("scratch_live_bytes", m.live),
            ("scratch_peak_bytes", m.peak),
            ("scratch_allocated_bytes", m.allocated),
            ("scratch_allocation_calls", m.allocations),
        ] {
            record[format!("{name}_{field}")] = value.into();
        }
    }
    if let Some(values) = ffi::allocator_bytes() {
        for (key, value) in [
            "libc_allocated_arena_bytes",
            "libc_free_arena_bytes",
            "libc_mmap_bytes",
        ]
        .iter()
        .zip(values)
        {
            record[*key] = value.into();
        }
    }
    if let Ok(smaps) = fs::read_to_string("/proc/self/smaps_rollup") {
        for line in smaps.lines() {
            let parts: Vec<_> = line.split_whitespace().collect();
            if parts.len() == 3
                && parts[2] == "kB"
                && [
                    "Anonymous:",
                    "Private_Dirty:",
                    "Private_Clean:",
                    "Shared_Clean:",
                    "Swap:",
                ]
                .contains(&parts[0])
            {
                if let Ok(value) = parts[1].parse::<u64>() {
                    record[format!("{}_kib", parts[0].trim_end_matches(':'))] = value.into();
                }
            }
        }
    }
    writeln!(out, "{}", record)?;
    Ok(())
}
