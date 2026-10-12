// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
//! Small data-driven host harness. Independent numerical oracles live in the caller.
use crate::{ffi, Error, ErrorKind, Result};
use serde::Deserialize;
use serde_json::json;
use std::collections::BTreeMap;
use std::path::{Path, PathBuf};

#[derive(Deserialize)]
#[serde(deny_unknown_fields)]
struct Fixture {
    version: u32,
    graphs: BTreeMap<String, PathBuf>,
    #[serde(default = "one")]
    threads: usize,
    #[serde(default)]
    bundle: PathBuf,
    #[serde(default = "parameters")]
    parameters: PathBuf,
    #[serde(default)]
    memory: bool,
    buffers: Vec<BufferSpec>,
    steps: Vec<Step>,
}
fn one() -> usize {
    1
}
fn parameters() -> PathBuf {
    "parameters".into()
}
#[derive(Deserialize)]
#[serde(deny_unknown_fields)]
struct BufferSpec {
    name: String,
    dtype: String,
    shape: Vec<usize>,
    #[serde(default)]
    file: Option<PathBuf>,
    /// Names the graph declaring this persistent resource owner.
    #[serde(default)]
    resource: Option<String>,
    #[serde(default)]
    initialized_extent: usize,
    #[serde(default)]
    append_axis: Option<usize>,
}
#[derive(Deserialize)]
#[serde(deny_unknown_fields)]
struct Step {
    graph: String,
    #[serde(default)]
    reset: Vec<String>,
    #[serde(default)]
    import: BTreeMap<String, usize>,
    #[serde(default)]
    bindings: Vec<Binding>,
    #[serde(default)]
    scalars: BTreeMap<String, i64>,
    #[serde(default)]
    outputs: BTreeMap<String, PathBuf>,
    #[serde(default)]
    expect_error: Option<String>,
    #[serde(default)]
    expect_unchanged: bool,
    #[serde(default)]
    before_appends: Option<Vec<BTreeMap<String, PathBuf>>>,
    #[serde(default)]
    fail_after_appends: Option<usize>,
    #[serde(default)]
    expect_poisoned: Vec<String>,
    #[serde(default)]
    warmup_runs: usize,
    #[serde(default = "one")]
    measured_runs: usize,
}
#[derive(Deserialize)]
#[serde(deny_unknown_fields)]
struct Binding {
    name: String,
    #[serde(default)]
    shape: Option<Vec<usize>>,
    #[serde(default)]
    file: Option<PathBuf>,
    #[serde(default)]
    bytes: Option<usize>,
}
struct Storage {
    buffer: ffi::Buffer<u64>,
    shape: Vec<usize>,
    bytes: usize,
    active_bytes: usize,
}
struct Session {
    // Graphs release retained pointers before resource handles or allocations.
    graphs: BTreeMap<String, ffi::PreparedGraph>,
    resources: BTreeMap<String, ffi::Resource>,
    buffers: BTreeMap<String, Storage>,
    append_regions: BTreeMap<String, (usize, usize)>,
}
fn size(dtype: &str, shape: &[usize]) -> Result<usize> {
    let bits = match dtype {
        "fp32" | "int32" => 32,
        "fp64" => 64,
        "bf16" | "fp16" => 16,
        "int8" | "uint8" => 8,
        "int4" => 4,
        "int2" => 2,
        _ => return Err(Error::invalid("Unknown fixture dtype")),
    };
    shape
        .iter()
        .try_fold(bits, |n: usize, &d| n.checked_mul(d))
        .and_then(|n| n.checked_add(7))
        .map(|n| n / 8)
        .filter(|&n| n <= 1024 * 1024 * 1024)
        .ok_or_else(|| Error::invalid("Fixture buffer size overflow/limit"))
}
fn load(buffer: &mut Storage, path: &Path) -> Result<()> {
    let bytes = std::fs::read(path)?;
    if bytes.len() > buffer.bytes {
        return Err(Error::invalid("Input exceeds fixture buffer"));
    }
    // SAFETY: the initialized u64 allocation provides alignment for all scalar
    // dtypes, remains stable, and is accessed only between synchronous calls.
    let target = unsafe {
        std::slice::from_raw_parts_mut(buffer.buffer.as_mut_ptr().cast::<u8>(), buffer.bytes)
    };
    target[..bytes.len()].copy_from_slice(&bytes);
    Ok(())
}
pub(crate) fn main(args: &[String]) -> Result<()> {
    if args.len() != 2 {
        return Err(Error::invalid("usage: plan_fixture fixture.json"));
    }
    let path = Path::new(&args[1]);
    let root = path.parent().unwrap_or(Path::new("."));
    let fixture: Fixture = serde_json::from_slice(&std::fs::read(path)?)?;
    if fixture.version != 1 || fixture.graphs.is_empty() {
        return Err(Error::invalid("Unsupported/empty fixture"));
    }
    let assets = ffi::Assets::open(&root.join(fixture.bundle), &root.join(fixture.parameters))?;
    let mut session = Session {
        graphs: BTreeMap::new(),
        resources: BTreeMap::new(),
        buffers: BTreeMap::new(),
        append_regions: BTreeMap::new(),
    };
    let mut setup_ms = BTreeMap::new();
    for (name, plan) in fixture.graphs {
        let start = std::time::Instant::now();
        let builder = ffi::GraphBuilder::from_plan(assets.clone(), &root.join(plan))?;
        let construction = start.elapsed().as_secs_f64() * 1000.0;
        let start = std::time::Instant::now();
        let mut graph = builder.prepare(fixture.threads)?;
        setup_ms.insert(
            name.clone(),
            [construction, start.elapsed().as_secs_f64() * 1000.0],
        );
        graph.diagnostics(None, fixture.memory)?;
        session.graphs.insert(name, graph);
    }
    for spec in fixture.buffers {
        if session.buffers.contains_key(&spec.name) || session.resources.contains_key(&spec.name) {
            return Err(Error::invalid("Duplicate fixture buffer"));
        }
        let bytes = size(&spec.dtype, &spec.shape)?;
        if let Some(graph) = spec.resource {
            let graph = session
                .graphs
                .get(&graph)
                .ok_or_else(|| Error::invalid("Unknown resource graph"))?;
            let width = size(&spec.dtype, &[])?;
            if ["int2", "int4"].contains(&spec.dtype.as_str()) {
                return Err(Error::invalid("Packed persistent resource unsupported"));
            }
            let mut resource =
                ffi::Resource::new_typed(graph, &ffi::string(&spec.name)?, &spec.shape, width)?;
            if let Some(axis) = spec.append_axis {
                if axis >= spec.shape.len() {
                    return Err(Error::invalid("Invalid fixture append axis"));
                }
                let stride = spec.shape[axis + 1..].iter().product::<usize>() * width;
                session
                    .append_regions
                    .insert(spec.name.clone(), (spec.shape[axis], stride));
            }
            if let Some(file) = spec.file {
                resource.initialize(&std::fs::read(root.join(file))?, spec.initialized_extent)?;
            } else if spec.initialized_extent != 0 {
                return Err(Error::invalid(
                    "An imported resource requires its complete capacity payload",
                ));
            }
            session.resources.insert(spec.name, resource);
        } else {
            let mut buffer = Storage {
                buffer: ffi::Buffer::new(bytes.div_ceil(8) + 8, 0),
                shape: spec.shape,
                bytes,
                active_bytes: bytes,
            };
            if let Some(file) = spec.file {
                load(&mut buffer, &root.join(file))?;
            }
            session.buffers.insert(spec.name, buffer);
        }
    }
    let mut records = Vec::new();
    let step_count = fixture.steps.len();
    for (index, step) in fixture.steps.into_iter().enumerate() {
        if step.measured_runs == 0
            || step.measured_runs > 10000
            || step.warmup_runs > 10000
            || (!session.resources.is_empty() && (step.warmup_runs != 0 || step.measured_runs != 1))
        {
            return Err(Error::invalid(
                "Invalid fixture repetitions; stateful invocations must be explicit steps",
            ));
        }
        for name in &step.reset {
            session
                .resources
                .get_mut(name)
                .ok_or_else(|| Error::invalid("Unknown reset resource"))?
                .reset()?;
        }
        for (name, extent) in &step.import {
            session
                .resources
                .get_mut(name)
                .ok_or_else(|| Error::invalid("Unknown imported resource"))?
                .import(*extent)?;
        }
        for b in &step.bindings {
            let buffer = session
                .buffers
                .get_mut(&b.name)
                .ok_or_else(|| Error::invalid("Unknown binding"))?;
            if let Some(shape) = &b.shape {
                buffer.shape = shape.clone();
            }
            if let Some(bytes) = b.bytes {
                if bytes > buffer.bytes {
                    return Err(Error::invalid("Active binding exceeds buffer"));
                }
                buffer.active_bytes = bytes;
            }
            if let Some(file) = &b.file {
                load(buffer, &root.join(file))?;
            }
        }
        let graph = session
            .graphs
            .get_mut(&step.graph)
            .ok_or_else(|| Error::invalid("Unknown step graph"))?;
        for buffer in session.buffers.values_mut() {
            let bytes = unsafe {
                std::slice::from_raw_parts_mut(
                    buffer.buffer.as_mut_ptr().cast::<u8>(),
                    buffer.buffer.len() * 8,
                )
            };
            bytes[buffer.active_bytes..].fill(0xa5);
        }
        let before: BTreeMap<_, _> = if step.expect_unchanged {
            session
                .resources
                .iter()
                .map(|(name, resource)| {
                    Ok((name.clone(), (resource.data().to_vec(), resource.status()?)))
                })
                .collect::<Result<_>>()?
        } else {
            BTreeMap::new()
        };
        let before_buffers: BTreeMap<_, _> = if step.expect_unchanged {
            session
                .buffers
                .iter()
                .map(|(name, buffer)| {
                    (
                        name.clone(),
                        unsafe {
                            std::slice::from_raw_parts(
                                buffer.buffer.as_ptr().cast::<u8>(),
                                buffer.buffer.len() * 8,
                            )
                        }
                        .to_vec(),
                    )
                })
                .collect()
        } else {
            BTreeMap::new()
        };
        let before_appends: BTreeMap<_, _> = session
            .append_regions
            .keys()
            .map(|name| {
                let resource = &session.resources[name];
                Ok((
                    name.clone(),
                    (resource.data().to_vec(), resource.status()?[0] as usize),
                ))
            })
            .collect::<Result<_>>()?;
        let mut run_ms = Vec::new();
        let mut observations = Vec::new();
        if let Some(appends) = &step.before_appends {
            for (append, expected) in appends.iter().enumerate() {
                for (name, file) in expected {
                    let bytes = std::fs::read(root.join(file))?;
                    let buffer = session
                        .buffers
                        .get(name)
                        .ok_or_else(|| Error::invalid("Unknown append observation buffer"))?;
                    if bytes.len() > buffer.active_bytes {
                        return Err(Error::invalid("Append observation exceeds buffer"));
                    }
                    observations.push((append, name, bytes));
                }
            }
        } else if step.fail_after_appends.is_some() {
            return Err(Error::invalid(
                "Failure injection requires an append schedule",
            ));
        }
        let result = (|| -> Result<()> {
            // SAFETY: Session owns all storage, graphs drop first, and execution
            // is synchronous with no overlapping Rust buffer borrows.
            for (name, buffer) in &session.buffers {
                unsafe {
                    graph.bind_bytes(
                        &ffi::string(name)?,
                        &buffer.buffer,
                        buffer.active_bytes,
                        &buffer.shape,
                        true,
                    )?;
                }
            }
            for (name, resource) in &mut session.resources {
                unsafe {
                    graph.resource(&ffi::string(name)?, resource)?;
                }
            }
            for round in 0..step.warmup_runs + step.measured_runs {
                for (name, value) in &step.scalars {
                    graph.scalar(&ffi::string(name)?, *value)?;
                }
                let start = std::time::Instant::now();
                if let Some(appends) = &step.before_appends {
                    let checks: Vec<_> = observations
                        .iter()
                        .map(|(append, name, bytes)| ffi::AppendCheck {
                            append: *append,
                            actual: session.buffers[*name].buffer.as_ptr().cast(),
                            expected: bytes.as_ptr(),
                            bytes: bytes.len(),
                        })
                        .collect();
                    // SAFETY: Session owns aligned actual storage; observations
                    // owns expected bytes. Native checks borrow only for this call.
                    unsafe {
                        graph.run_observed(&checks, appends.len(), step.fail_after_appends)?;
                    }
                } else {
                    graph.run()?;
                }
                if round >= step.warmup_runs {
                    run_ms.push(start.elapsed().as_secs_f64() * 1000.0);
                }
            }
            Ok(())
        })();
        for (name, (bytes, status)) in before {
            let resource = &session.resources[&name];
            if resource.data() != bytes || resource.status()? != status {
                return Err(Error::invalid("Rejected fixture mutated resource state"));
            }
        }
        for (name, bytes) in before_buffers {
            let buffer = &session.buffers[&name];
            let now = unsafe {
                std::slice::from_raw_parts(
                    buffer.buffer.as_ptr().cast::<u8>(),
                    buffer.buffer.len() * 8,
                )
            };
            if now != bytes {
                return Err(Error::invalid("Rejected fixture mutated a buffer"));
            }
        }
        for resource in session.resources.values() {
            resource.check_canary()?;
        }
        for name in &step.expect_poisoned {
            if session
                .resources
                .get(name)
                .ok_or_else(|| Error::invalid("Unknown poisoned resource"))?
                .status()?[2]
                != 1
            {
                return Err(Error::invalid("Late failure did not poison state"));
            }
        }
        match (result, step.expect_error) {
            (Err(e), Some(expected)) if e.to_string().contains(&expected) => {
                let resources: BTreeMap<_, _> = session
                    .resources
                    .iter()
                    .map(|(name, value)| Ok((name, value.status()?)))
                    .collect::<Result<_>>()?;
                records.push(
                    json!({"step":index,"expected_error":e.to_string(),"resources":resources}),
                );
                // A checked rejection can be followed by fresh bindings on the
                // same graph. Backend/injected failures still terminate the
                // fixture; native failure poisoning is never cleared here.
                let rejected_without_writes = e.kind == ErrorKind::Invalid
                    && step.expect_unchanged
                    && step.fail_after_appends.is_none()
                    && step.before_appends.is_none();
                if index + 1 != step_count && !rejected_without_writes {
                    return Err(Error::invalid(
                        "Only an unchanged validation rejection may precede another step",
                    ));
                }
                continue;
            }
            (Err(e), _) => return Err(e),
            (Ok(()), Some(_)) => {
                return Err(Error::invalid("Expected invocation failure did not occur"))
            }
            (Ok(()), None) => {}
        }
        for (name, (before, begin)) in before_appends {
            let resource = &session.resources[&name];
            let end = resource.status()?[0] as usize;
            let (capacity, stride) = session.append_regions[&name];
            for (offset, (&old, &now)) in before.iter().zip(resource.data()).enumerate() {
                let row = (offset / stride) % capacity;
                if (row < begin || row >= end) && old != now {
                    return Err(Error::invalid(
                        "Append changed prefix or capacity suffix bytes",
                    ));
                }
            }
        }
        for buffer in session.buffers.values() {
            let bytes = unsafe {
                std::slice::from_raw_parts(
                    buffer.buffer.as_ptr().cast::<u8>(),
                    buffer.buffer.len() * 8,
                )
            };
            if bytes[buffer.active_bytes..].iter().any(|&b| b != 0xa5) {
                return Err(Error::invalid("Fixture buffer canary overwritten"));
            }
        }
        let mut shapes = BTreeMap::new();
        let mut resource_status = BTreeMap::new();
        for (name, resource) in &session.resources {
            resource_status.insert(name.clone(), resource.status()?);
        }
        for (name, file) in step.outputs {
            let file = root.join(file);
            if let Some(parent) = file.parent() {
                std::fs::create_dir_all(parent)?;
            }
            if let Some(buffer) = session.buffers.get(&name) {
                let bytes = unsafe {
                    std::slice::from_raw_parts(
                        buffer.buffer.as_ptr().cast::<u8>(),
                        buffer.active_bytes,
                    )
                };
                std::fs::write(file, bytes)?;
                shapes.insert(name.clone(), graph.shape(&ffi::string(&name)?)?);
            } else if let Some(resource) = session.resources.get(&name) {
                let bytes: Vec<_> = resource.data().iter().map(|&v| v as u8).collect();
                std::fs::write(file, bytes)?;
                // The physical capacity shape is part of the fixture contract.
                shapes.insert(name.clone(), graph.shape(&ffi::string(&name)?)?);
            } else {
                return Err(Error::invalid("Unknown output buffer"));
            }
        }
        let counts = graph.counters()?;
        records.push(json!({"step":index, "append_bytes":counts.append_bytes,
            "append_calls":counts.append_calls,"view_copy_bytes":counts.view_copy_bytes,"shapes":shapes,
            "weight_only_statistics":graph.weight_stats()?}));
        records.last_mut().unwrap()["resources"] = json!(resource_status);
        let record = records.last_mut().unwrap();
        record["run_ms"] = json!(run_ms);
        record["setup_ms"] = json!(setup_ms[&step.graph]);
        if fixture.memory {
            record["scratch_peak_bytes"] = json!(graph.memory()?.peak);
        }
    }
    println!("{}", serde_json::to_string(&records)?);
    Ok(())
}
