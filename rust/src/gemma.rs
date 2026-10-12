// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
use crate::frontend::{Frontend, Options};
use crate::{ffi, io, Error, Result};
use serde_json::json;
use std::ffi::CString;
use std::fs::{self, File};
use std::io::{BufWriter, Write};
use std::path::{Path, PathBuf};
use std::rc::Rc;
use std::time::Instant;
mod package;
use package::Package;

struct Cache {
    spec: ffi::KvSpec,
    key_name: CString,
    value_name: CString,
    key: ffi::Resource,
    value: ffi::Resource,
}

/// One exclusive request session owns both prepared phases and their KV storage.
/// Native resource epochs/publication remain authoritative. A failed native
/// invocation invalidates the session; constructing a fresh session is required.
/// ```compile_fail
/// use ynnpack_lab::gemma::GemmaSession;
/// fn invalid(session: &mut GemmaSession) {
///     let logits = session.decode(1).unwrap();
///     session.reset().unwrap();
///     println!("{}", logits[0]);
/// }
/// ```
pub struct GemmaSession {
    // Native graphs MUST drop before every allocation/Resource they reference.
    graphs: [ffi::PreparedGraph; 2],
    caches: Vec<Cache>,
    assets: Rc<ffi::Assets>,
    embedded: ffi::ActivationBuffer,
    positions: ffi::Buffer<f32>,
    ple: Vec<ffi::ActivationBuffer>,
    ple_names: Vec<CString>,
    logits: ffi::Buffer<f32>,
    config: ffi::Config,
    capacity: usize,
    max_rows: usize,
    position: usize,
    failed: bool,
    kv_element_bytes: usize,
    kv_dtype: String,
    trace_output: Option<PathBuf>,
    trace_call: usize,
}
impl GemmaSession {
    pub fn load(
        bundle: &Path,
        parameters: &Path,
        capacity: usize,
        max_rows: usize,
        threads: usize,
    ) -> Result<Self> {
        Self::create(bundle, parameters, capacity, max_rows, threads, None, None)
    }
    pub fn load_with_plans(
        bundle: &Path,
        parameters: &Path,
        plans: &Path,
        capacity: usize,
        max_rows: usize,
        threads: usize,
    ) -> Result<Self> {
        Self::create(
            bundle,
            parameters,
            capacity,
            max_rows,
            threads,
            None,
            Some(plans),
        )
    }
    fn create(
        bundle: &Path,
        parameters: &Path,
        capacity: usize,
        max_rows: usize,
        threads: usize,
        diagnostics: Option<&Options>,
        plans: Option<&Path>,
    ) -> Result<Self> {
        if !(1..=32768).contains(&capacity)
            || !(1..=128).contains(&max_rows)
            || !(1..=256).contains(&threads)
        {
            return Err(Error::invalid("Invalid capacity/rows/threads"));
        }
        let default_plans = PathBuf::from("models")
            .join(ffi::model_name())
            .join("generated");
        let plans = plans.unwrap_or(&default_plans);
        let package = Package::read(plans)?;
        let metadata = &package.execution;
        if max_rows > metadata.prefill_rows {
            return Err(Error::invalid("Prefill rows exceed model contract"));
        }
        let bf16 = metadata.activation_dtype == "bf16";
        let assets = if metadata.asset_source == "hf" {
            let o = diagnostics.ok_or_else(|| {
                Error::invalid("Safetensors model needs source/manifest/cache options")
            })?;
            if o.hf_model_dir.is_empty() || o.asset_manifest.is_empty() || o.cache_dir.is_empty() {
                return Err(Error::invalid(
                    "Safetensors model needs --hf_model_dir, --asset_manifest and --cache_dir",
                ));
            }
            ffi::Assets::open_hf(
                Path::new(&o.hf_model_dir),
                Path::new(&o.asset_manifest),
                Path::new(&o.cache_dir),
                parameters,
                &metadata.source_identity,
                bf16,
            )?
        } else {
            if diagnostics.is_some_and(|o| !o.hf_model_dir.is_empty()) {
                return Err(Error::invalid("HF assets require an HF model package"));
            }
            ffi::Assets::open(bundle, parameters)?
        };
        let config = package.check_assets(&assets)?;
        let mut graphs = Vec::new();
        for (phase, name) in ["prefill", "decode"].iter().enumerate() {
            let start = Instant::now();
            eprintln!("Authoring {name}");
            let mut builder =
                ffi::GraphBuilder::from_validated_plan(assets.clone(), package.plan(plans, name)?)?;
            eprintln!("Preparing {phase} author_ms={:.3}", ms(start));
            if let Some(o) = diagnostics {
                if !o.trace_plan.is_empty() {
                    builder.trace(&Path::new(&o.trace_plan).join(format!("{name}.tsv")))?;
                }
                if o.profile_execution == *name || o.profile_execution == "all" {
                    let filename = if phase == 0 {
                        "prefill_execution_profile.jsonl"
                    } else {
                        "execution_profile.jsonl"
                    };
                    builder.profile(&Path::new(&o.output_dir).join(filename))?;
                }
            }
            let mut graph = builder.prepare(threads)?;
            if let Some(o) = diagnostics {
                let pipeline = o
                    .dump_pipeline
                    .then(|| Path::new(&o.output_dir).join(format!("{name}.ir.txt")));
                graph.diagnostics(pipeline.as_deref(), o.report_memory)?;
                if o.profile_execution == *name || o.profile_execution == "all" {
                    graph.profile_step("", 0, 0, 0, 0)?;
                }
            }
            eprintln!(
                "Prepared {phase} ms={:.3} rss_kib={} peak={}",
                ms(start),
                ffi::rss() / 1024,
                ffi::peak_rss() / 1024
            );
            graphs.push(graph);
        }
        let graphs: [ffi::PreparedGraph; 2] = graphs.try_into().ok().unwrap();
        let mut caches = Vec::new();
        for i in 0..config.owners as usize {
            let spec = assets.owner(i)?;
            let key_name = ffi::string(&format!("cache_key_{}", spec.owner))?;
            let value_name = ffi::string(&format!("cache_value_{}", spec.owner))?;
            let shape = [1, spec.heads as usize, capacity, spec.width as usize];
            let key =
                ffi::Resource::new_typed(&graphs[0], &key_name, &shape, metadata.kv_element_bytes)?;
            let value = ffi::Resource::new_typed(
                &graphs[0],
                &value_name,
                &shape,
                metadata.kv_element_bytes,
            )?;
            caches.push(Cache {
                spec,
                key_name,
                value_name,
                key,
                value,
            });
        }
        Ok(Self {
            graphs,
            caches,
            assets,
            embedded: ffi::ActivationBuffer::new(max_rows * config.width as usize, bf16),
            positions: ffi::Buffer::new(max_rows, 0.0),
            ple: (0..config.layers)
                .map(|_| ffi::ActivationBuffer::new(max_rows * config.ple_width as usize, bf16))
                .collect(),
            ple_names: (0..config.layers)
                .map(|i| ffi::string(&format!("per_layer_token_embedding_{i}")))
                .collect::<Result<_>>()?,
            logits: ffi::Buffer::new(config.vocab as usize + 16, 0.0),
            config,
            capacity,
            max_rows,
            position: 0,
            failed: false,
            kv_element_bytes: metadata.kv_element_bytes,
            kv_dtype: metadata.kv_dtype.clone(),
            trace_output: diagnostics
                .filter(|o| !o.trace_plan.is_empty())
                .map(|o| Path::new(&o.output_dir).join("trace")),
            trace_call: 0,
        })
    }
    fn check_live(&self) -> Result<()> {
        if self.failed {
            Err(Error::invalid("Failed session must be discarded"))
        } else {
            Ok(())
        }
    }
    pub fn position(&self) -> usize {
        self.position
    }
    pub fn reset(&mut self) -> Result<()> {
        self.check_live()?;
        // Mark unusable until all native states have successfully reset.
        self.failed = true;
        for cache in &mut self.caches {
            cache.key.reset()?;
            cache.value.reset()?;
        }
        self.position = 0;
        self.failed = false;
        Ok(())
    }
    /// Process all but the last prompt token; decode that token for first logits.
    pub fn prefix(&mut self, prompt: &[i32]) -> Result<()> {
        self.prefix_with_profile(prompt, None)
    }
    fn prefix_with_profile(&mut self, prompt: &[i32], profile: Option<(&str, i32)>) -> Result<()> {
        self.check_live()?;
        if prompt.is_empty() {
            return Err(Error::invalid("Empty prompt"));
        }
        self.validate_tokens(prompt)?;
        for (step, chunk) in prompt[..prompt.len() - 1].chunks(self.max_rows).enumerate() {
            if let Some((name, rep)) = profile {
                self.graphs[0].profile_step_rows(
                    name,
                    rep,
                    step,
                    self.position,
                    chunk.len(),
                    true,
                    1,
                )?;
            }
            let result = self.chunk(chunk, false);
            if profile.is_some() {
                self.graphs[0].profile_step("", 0, 0, 0, if result.is_ok() { 2 } else { 3 })?;
            }
            result?;
        }
        Ok(())
    }
    pub fn decode(&mut self, token: i32) -> Result<&[f32]> {
        self.chunk(&[token], true)?;
        Ok(&self.logits[..self.config.vocab as usize])
    }
    fn validate_tokens(&self, tokens: &[i32]) -> Result<()> {
        if self
            .position
            .checked_add(tokens.len())
            .is_none_or(|end| end > self.capacity)
        {
            return Err(Error::invalid("Context capacity exceeded"));
        }
        if tokens
            .iter()
            .any(|&t| t < 0 || t as u32 >= self.config.vocab)
        {
            return Err(Error::invalid("Invalid token"));
        }
        Ok(())
    }
    fn chunk(&mut self, tokens: &[i32], decode: bool) -> Result<()> {
        self.check_live()?;
        self.validate_tokens(tokens)?;
        let count = tokens.len();
        if count == 0 || count > self.max_rows || (decode && count != 1) {
            return Err(Error::invalid("Invalid chunk length"));
        }
        // Every native failure requires discarding this session, including a
        // partial append. Host position advances only after successful publish.
        self.failed = true;
        self.assets
            .embed(tokens, &mut self.embedded, &mut self.ple)?;
        for (i, value) in self.positions[..count].iter_mut().enumerate() {
            *value = (self.position + i) as f32;
        }
        let g = &mut self.graphs[usize::from(decode)];
        g.scalar(c"position", self.position as i64)?;
        // SAFETY: Session owns stable buffers and resources, native graphs drop
        // first, and &mut self excludes access during synchronous execution.
        unsafe {
            self.embedded.bind(
                g,
                c"embedded_input",
                &[1, count, self.config.width as usize],
                false,
            )?;
            g.bind(c"positions", &self.positions, &[1, 1, count, 1], false)?;
            for (name, buffer) in self.ple_names.iter().zip(&mut self.ple) {
                buffer.bind(g, name, &[1, count, self.config.ple_width as usize], true)?;
            }
            for cache in &mut self.caches {
                g.resource(&cache.key_name, &mut cache.key)?;
                g.resource(&cache.value_name, &mut cache.value)?;
            }
            if decode {
                g.bind(c"logits", &mut self.logits, &[], false)?;
            }
        }
        let expected_bytes: u64 = self
            .caches
            .iter()
            .map(|c| {
                self.kv_element_bytes as u64
                    * 2
                    * count as u64
                    * u64::from(c.spec.heads)
                    * u64::from(c.spec.width)
            })
            .sum();
        let before = g.counters()?;
        g.run()?;
        if let Some(root) = &self.trace_output {
            let phase = if decode { "decode" } else { "prefill" };
            g.save_trace(&root.join(format!(
                "{}-{phase}-p{}-q{count}",
                self.trace_call, self.position
            )))?;
            self.trace_call += 1;
        }
        let after = g.counters()?;
        if after.append_bytes.checked_sub(before.append_bytes) != Some(expected_bytes)
            || after.append_calls.checked_sub(before.append_calls)
                != Some(2 * self.caches.len() as u64)
            || after.view_copy_bytes != 0
        {
            return Err(Error::invalid("Append/view copy contract violated"));
        }
        self.position += count;
        self.failed = false;
        Ok(())
    }
    fn counters(&self) -> Result<ffi::Counters> {
        let a = self.graphs[0].counters()?;
        let b = self.graphs[1].counters()?;
        Ok(ffi::Counters {
            append_calls: a.append_calls + b.append_calls,
            append_bytes: a.append_bytes + b.append_bytes,
            view_copy_bytes: a.view_copy_bytes + b.view_copy_bytes,
        })
    }
    fn save(&self, path: &Path) -> Result<()> {
        self.check_live()?;
        io::write_f32(path, &self.logits[..self.config.vocab as usize])?;
        for cache in &self.caches {
            for head in 0..cache.spec.heads as usize {
                let mut prefix = format!("{}.owner{}", path.display(), cache.spec.owner);
                if cache.spec.heads > 1 {
                    prefix.push_str(&format!(".head{head}"));
                }
                let offset =
                    head * self.capacity * cache.spec.width as usize * self.kv_element_bytes;
                let length = self.position * cache.spec.width as usize * self.kv_element_bytes;
                for (kind, resource) in [("k", &cache.key), ("v", &cache.value)] {
                    let bytes: Vec<u8> = resource.data()[offset..offset + length]
                        .iter()
                        .map(|&v| v as u8)
                        .collect();
                    let dtype = if self.kv_dtype == "bf16" {
                        "bf16"
                    } else {
                        "i8"
                    };
                    fs::write(format!("{prefix}.{kind}.{dtype}"), bytes)?;
                }
            }
        }
        Ok(())
    }
    fn memory(&self, phase: &str, out: &mut impl Write) -> Result<()> {
        let mut record =
            json!({"phase":phase, "rss_kib":ffi::rss()/1024, "peak_rss_kib":ffi::peak_rss()/1024});
        for (i, name) in ["prefill", "decode"].iter().enumerate() {
            let m = self.graphs[i].memory()?;
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
        write_record(out, &record)
    }
}

fn ms(start: Instant) -> f64 {
    start.elapsed().as_secs_f64() * 1000.0
}
fn write_record(out: &mut impl Write, value: &serde_json::Value) -> Result<()> {
    serde_json::to_writer(&mut *out, value)?;
    out.write_all(b"\n")?;
    out.flush()?;
    Ok(())
}
pub(crate) fn main(args: &[String]) -> Result<()> {
    let Some(o) = Options::parse(args, true)? else {
        return Ok(());
    };
    let default_plans = format!("models/{}/generated", ffi::model_name());
    let plans = o.graph_dir.as_deref().unwrap_or(&default_plans);
    let package = Package::read(Path::new(plans))?;
    let frontend = Frontend::resolve(&o, Some(package.vocab_size()))?;
    let metadata = &package.execution;
    let output = Path::new(&o.output_dir);
    io::new_directory(output)?;
    frontend.save(output)?;
    io::json(
        &output.join("run.json"),
        &json!({
            "runner":"rust", "graph_dir":plans, "profile":metadata.profile,
            "kv_element_bytes":metadata.kv_element_bytes, "cache_capacity":o.cache_capacity, "prefill_rows":o.prefill_rows,
            "decode_attention_profile":metadata.decode_attention_profile, "prefill_attention_profile":metadata.prefill_attention_profile,
            "threads":o.num_threads, "warmups":o.warmup_runs, "repetitions":o.measured_runs,
            "profile_execution":o.profile_execution, "report_memory":o.report_memory,
            "trace_plan":o.trace_plan,
            "timings_valid_for_benchmark":o.profile_execution == "none" && !o.report_memory && !o.dump_outputs && o.trace_plan.is_empty(),
        }),
    )?;
    let start = Instant::now();
    let mut session = GemmaSession::create(
        Path::new(&o.bundle_dir),
        Path::new(&o.parameter_dir),
        o.cache_capacity,
        o.prefill_rows,
        o.num_threads,
        Some(&o),
        Some(Path::new(plans)),
    )?;
    let setup_ms = ms(start);
    let setup_rss = ffi::rss() / 1024;
    let mut timings = BufWriter::new(File::create(output.join("timings.jsonl"))?);
    let mut memory = if o.report_memory {
        Some(BufWriter::new(File::create(output.join("memory.jsonl"))?))
    } else {
        None
    };
    if let Some(out) = &mut memory {
        session.memory("setup", out)?;
    }
    for case in &frontend.cases {
        // Validate whole request before mutation, including forced continuation.
        if case
            .prompt
            .len()
            .checked_add(case.continuation.len())
            .is_none_or(|n| n > o.cache_capacity)
        {
            return Err(Error::invalid("Case exceeds context capacity"));
        }
        for rep in -o.warmup_runs..o.measured_runs {
            session.reset()?;
            let start = Instant::now();
            let profile_prefix =
                rep >= 0 && (o.profile_execution == "prefill" || o.profile_execution == "all");
            session.prefix_with_profile(
                &case.prompt,
                profile_prefix.then_some((case.name.as_str(), rep)),
            )?;
            let prefix_ms = ms(start);
            let request = format!("{}/{rep}", case.name);
            if let Some(out) = &mut memory {
                session.memory(&format!("{request}/prefix"), out)?;
            }
            for (step, &token) in case
                .prompt
                .last()
                .into_iter()
                .chain(case.continuation.iter())
                .enumerate()
            {
                let collect = (o.profile_execution == "decode" || o.profile_execution == "all")
                    && rep >= 0
                    && step > 0;
                if collect {
                    session.graphs[1].profile_step(&case.name, rep, step, session.position, 1)?;
                }
                let start = Instant::now();
                let result = session.decode(token);
                let decode_ms = ms(start);
                let logits = match result {
                    Ok(logits) => logits,
                    Err(e) => {
                        if collect {
                            let _ = session.graphs[1].profile_step("", 0, 0, 0, 3);
                        }
                        return Err(e);
                    }
                };
                let mut argmax = 0;
                for (i, &value) in logits.iter().enumerate() {
                    if !value.is_finite() {
                        if collect {
                            let _ = session.graphs[1].profile_step("", 0, 0, 0, 3);
                        }
                        return Err(Error::invalid("Nonfinite logits"));
                    }
                    if value > logits[argmax] {
                        argmax = i;
                    }
                }
                let token_ms = ms(start);
                if collect {
                    session.graphs[1].profile_step("", 0, 0, 0, 2)?;
                }
                let counters = session.counters()?;
                write_record(
                    &mut timings,
                    &json!({
                        "case":case.name, "repetition":rep, "step":step, "setup_ms":setup_ms,
                        "setup_rss_kib":setup_rss, "prefix_ms":prefix_ms, "decode_ms":decode_ms,
                        "token_ms":token_ms, "context":session.position, "argmax":argmax,
                        "peak_rss_kib":ffi::peak_rss()/1024, "rss_kib":ffi::rss()/1024,
                        "append_bytes":counters.append_bytes, "view_copy_bytes":counters.view_copy_bytes,
                    }),
                )?;
                if let Some(out) = &mut memory {
                    if step == 0 {
                        session.memory(&format!("{request}/first_decode"), out)?;
                    }
                }
                if rep == 0 && o.dump_outputs {
                    let suffix = if step == 0 {
                        ".prefill.f32".into()
                    } else {
                        format!(".decode_{step:04}.f32")
                    };
                    session.save(&output.join(format!("{}{suffix}", case.name)))?;
                }
            }
            eprintln!("{} rep={rep} prefix_ms={prefix_ms:.3}", case.name);
        }
    }
    Ok(())
}
