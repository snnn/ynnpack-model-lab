// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
#![cfg_attr(feature = "native-tests", allow(dead_code))]
use crate::{ffi, io, Error, Result};
use serde::Deserialize;
use serde_json::json;
use sha2::{Digest, Sha256};
use std::path::Path;
use std::time::Instant;

#[derive(Deserialize)]
struct Contract {
    model: String,
    dtype: String,
    input_name: String,
    output_name: String,
    input_shape: Vec<usize>,
    output_shape: Vec<usize>,
    execution: Execution,
}
#[derive(Deserialize)]
#[serde(deny_unknown_fields)]
struct Execution {
    format: String,
    version: u32,
    graph: GraphArtifact,
}
#[derive(Deserialize)]
#[serde(deny_unknown_fields)]
struct GraphArtifact {
    file: String,
    sha256: String,
}
fn elements(shape: &[usize]) -> Result<usize> {
    if shape.is_empty() || shape.len() > 8 {
        return Err(Error::invalid("Invalid tensor rank"));
    }
    shape.iter().try_fold(1usize, |n, &d| {
        n.checked_mul(d)
            .filter(|&v| d > 0 && v <= isize::MAX as usize / 4)
            .ok_or_else(|| Error::invalid("Invalid/overflowing tensor dimensions"))
    })
}

/// Construction is separate from preparation, which consumes the builder.
/// ```compile_fail
/// use ynnpack_lab::vision::VisionBuilder;
/// let builder = VisionBuilder::load(std::path::Path::new("model")).unwrap();
/// let first = builder.prepare(1).unwrap();
/// let second = builder.prepare(1).unwrap(); // builder was consumed
/// ```
pub struct VisionBuilder {
    graph: ffi::GraphBuilder,
    contract: Contract,
}
impl VisionBuilder {
    pub fn load(model_dir: &Path) -> Result<Self> {
        Self::load_with_plan(model_dir, None)
    }
    pub fn load_with_plan(model_dir: &Path, plan: Option<&Path>) -> Result<Self> {
        let contract: Contract = serde_json::from_slice(&io::read_limited(
            &model_dir.join("model.json"),
            16 * 1024 * 1024,
        )?)?;
        if contract.model.is_empty() || contract.dtype != "float32" {
            return Err(Error::invalid(
                "Metadata must describe an FP32 vision model",
            ));
        }
        elements(&contract.input_shape)?;
        elements(&contract.output_shape)?;
        ffi::string(&contract.input_name)?;
        ffi::string(&contract.output_name)?;
        if contract.execution.format != "vision-execution"
            || contract.execution.version != 1
            || contract.execution.graph.file != "graph.ynn"
        {
            return Err(Error::invalid("Unsupported vision execution metadata"));
        }
        let graph_path = model_dir.join(&contract.execution.graph.file);
        let bytes = io::read_limited(plan.unwrap_or(&graph_path), 128 * 1024 * 1024)?;
        if format!("{:x}", Sha256::digest(&bytes)) != contract.execution.graph.sha256 {
            return Err(Error::invalid("Vision plan identity differs from metadata"));
        }
        let plan = crate::plan::ValidatedPlan::from_bytes(&bytes)?;
        plan.require_tensor(
            &contract.input_name,
            "fp32",
            &contract
                .input_shape
                .iter()
                .map(|&d| Some(d as i64))
                .collect::<Vec<_>>(),
            1,
        )?;
        plan.require_tensor(
            &contract.output_name,
            "fp32",
            &contract
                .output_shape
                .iter()
                .map(|&d| Some(d as i64))
                .collect::<Vec<_>>(),
            2,
        )?;
        let assets = ffi::Assets::open(Path::new(""), &model_dir.join("parameters"))?;
        Ok(Self {
            graph: ffi::GraphBuilder::from_validated_plan(assets, plan)?,
            contract,
        })
    }
    pub fn prepare(self, threads: usize) -> Result<VisionSession> {
        let mut session = VisionSession {
            graph: self.graph.prepare(threads)?,
            input: ffi::Buffer::new(elements(&self.contract.input_shape)?, 0.0),
            output: ffi::Buffer::new(elements(&self.contract.output_shape)?, 0.0),
            failed: false,
        };
        // SAFETY: owned boxed allocations never resize. Graph is the first field
        // and is destroyed before buffers, including on partial binding failure.
        unsafe {
            session.graph.bind(
                &ffi::string(&self.contract.input_name)?,
                &mut session.input,
                &self.contract.input_shape,
                false,
            )?;
            session.graph.bind(
                &ffi::string(&self.contract.output_name)?,
                &mut session.output,
                &[],
                false,
            )?;
        }
        Ok(session)
    }
}

/// Owns graph, mappings and stable tensor allocations. Output borrows prevent
/// another invocation or input mutation while a caller is still using logits.
/// ```compile_fail
/// use ynnpack_lab::vision::VisionSession;
/// fn invalid(session: &mut VisionSession) {
///     let output = session.run().unwrap();
///     session.run().unwrap();
///     println!("{}", output[0]);
/// }
/// ```
/// ```compile_fail
/// use ynnpack_lab::vision::VisionSession;
/// fn assert_send<T: Send>() {}
/// assert_send::<VisionSession>();
/// ```
pub struct VisionSession {
    // Field order is part of the FFI lifetime contract. Drop native graph first.
    graph: ffi::PreparedGraph,
    input: ffi::Buffer<f32>,
    output: ffi::Buffer<f32>,
    failed: bool,
}
impl VisionSession {
    pub fn input_mut(&mut self) -> &mut [f32] {
        &mut self.input
    }
    pub fn output(&self) -> &[f32] {
        &self.output
    }
    pub fn run(&mut self) -> Result<&[f32]> {
        if self.failed {
            return Err(Error::invalid("Failed session must be discarded"));
        }
        if let Err(e) = self.graph.run() {
            self.failed = true;
            return Err(e);
        }
        Ok(&self.output)
    }
}

pub(crate) fn main(args: &[String]) -> Result<()> {
    if args.iter().any(|s| s == "--help" || s == "-h") {
        println!("Rust YNNPACK vision runner\n--model_dir=DIR --input_file=FILE [repeat] --output_dir=NEW_DIR\n--graph_file=PLAN (default: MODEL_DIR/graph.ynn)\n--num_threads=1 --warmup_runs=3 --measured_runs=30 --dump_outputs");
        return Ok(());
    }
    let mut options = io::Arguments::parse(args, &["--input_file"], &["--dump_outputs"])?;
    let model = options.take("--model_dir", None)?;
    let output = options.take("--output_dir", None)?;
    let plan = options.values.remove("--graph_file").map(|v| v[0].clone());
    let inputs = options
        .values
        .remove("--input_file")
        .ok_or_else(|| Error::invalid("Missing --input_file"))?;
    let threads = options.number("--num_threads", "1", 1, 256)?;
    let warmup = options.number("--warmup_runs", "3", 1, i32::MAX as usize)?;
    let runs = options.number("--measured_runs", "30", 1, i32::MAX as usize)?;
    let dump = options.boolean("--dump_outputs")?;
    options.finish()?;
    let output = Path::new(&output);
    io::new_directory(output)?;
    let base_rss = ffi::rss();
    let start = Instant::now();
    let builder = VisionBuilder::load_with_plan(Path::new(&model), plan.as_deref().map(Path::new))?;
    let model_name = builder.contract.model.clone();
    let construction_ms = start.elapsed().as_secs_f64() * 1000.0;
    let compile_start = Instant::now();
    let mut session = builder.prepare(threads)?;
    let compile_ms = compile_start.elapsed().as_secs_f64() * 1000.0;
    let setup_ms = start.elapsed().as_secs_f64() * 1000.0;
    let prepared_rss = ffi::rss();
    let mut cases = Vec::new();
    for (case, input) in inputs.iter().enumerate() {
        let values = io::read_f32(Path::new(input), session.input.len())?;
        session.input_mut().copy_from_slice(&values);
        let mut first_ms = 0.0;
        for i in 0..warmup {
            let start = Instant::now();
            session.run()?;
            if i == 0 {
                first_ms = start.elapsed().as_secs_f64() * 1000.0;
            }
        }
        let mut times = Vec::with_capacity(runs);
        for _ in 0..runs {
            let start = Instant::now();
            session.run()?;
            times.push(start.elapsed().as_secs_f64() * 1000.0);
        }
        if !session.output().iter().all(|v| v.is_finite()) {
            return Err(Error::invalid("Non-finite output"));
        }
        cases.push(
            json!({"first_invoke_ms":first_ms, "inference_ms":times, "rss_bytes":ffi::rss()}),
        );
        if dump {
            io::write_f32(&output.join(format!("output_{case}.bin")), session.output())?;
        }
    }
    io::json(
        &output.join("measurements.json"),
        &json!({
            "engine":"ynnpack", "runner":"rust", "model":model_name, "graph_file":plan, "threads":threads,
            "construction_ms":construction_ms, "compile_ms":compile_ms, "setup_ms":setup_ms,
            "base_rss_bytes":base_rss, "prepared_rss_bytes":prepared_rss,
            "cases":cases, "peak_rss_bytes":ffi::peak_rss(),
        }),
    )?;
    println!("Completed {} cases, setup {setup_ms:.3} ms", inputs.len());
    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn invalid_dimensions() {
        for shape in [vec![], vec![0, 3], vec![usize::MAX, 2], vec![1; 9]] {
            assert!(elements(&shape).is_err());
        }
        assert_eq!(elements(&[1, 3, 224, 224]).unwrap(), 150528);
    }
}
