// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
#![cfg_attr(feature = "native-tests", allow(dead_code))]
use crate::{ffi, io, Error, Result};
use serde::Deserialize;
use serde_json::json;
use std::path::Path;
use std::time::Instant;

#[derive(Deserialize)]
struct Contract {
    model: String, dtype: String, input_name: String, output_name: String,
    input_shape: Vec<usize>, output_shape: Vec<usize>,
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
    package: crate::runtime::package::ModelPackage,
    root: std::path::PathBuf,
    contract: Contract,
}
impl VisionBuilder {
    pub fn load(model_dir: &Path) -> Result<Self> {
        let package = crate::runtime::package::ModelPackage::read(model_dir)?;
        let contract: Contract = serde_json::from_value(package.metadata.clone())?;
        if contract.model.is_empty() || contract.dtype != "float32" {
            return Err(Error::invalid("Metadata must describe an FP32 vision model"));
        }
        elements(&contract.input_shape)?; elements(&contract.output_shape)?;
        Ok(Self { package, contract, root: model_dir.into() })
    }
    pub fn prepare(self, threads: usize) -> Result<VisionSession> {
        let spec: crate::runtime::tensor::TensorExecutionSpec = self.package.execution()?;
        let expected = crate::runtime::tensor::TensorPhase {
            inputs: vec![crate::runtime::tensor::TensorBinding { name: self.contract.input_name.clone(), dtype: "fp32".into(), shape: self.contract.input_shape.clone() }],
            outputs: vec![crate::runtime::tensor::TensorBinding { name: self.contract.output_name.clone(), dtype: "fp32".into(), shape: self.contract.output_shape.clone() }],
        };
        if spec.graphs.get("model") != Some(&expected) { return Err(Error::invalid("Vision metadata differs from tensor contract")); }
        let prepared = crate::runtime::prepare(&self.package.program,
            crate::runtime::AssetStore::open(Path::new(""), &self.root.join("parameters"))?,
            crate::runtime::PrepareOptions { threads, tensors: Some(&spec), ..Default::default() })?;
        let session = crate::runtime::tensor::TensorSession::from_prepared(prepared)?;
        Ok(VisionSession { session, contract: self.contract })
    }
}
/// Owned tensor storage and exclusive invocation. Output borrows exclude mutation.
pub struct VisionSession {
    session: crate::runtime::tensor::TensorSession,
    contract: Contract,
}
impl VisionSession {
    pub fn input_mut(&mut self) -> &mut [f32] {
        self.session.input_f32_mut("model", &self.contract.input_name).expect("validated input")
    }
    pub fn output(&self) -> &[f32] {
        self.session.output_f32("model", &self.contract.output_name).expect("validated output")
    }
    pub fn run(&mut self) -> Result<&[f32]> {
        self.session.invoke("model")?; Ok(self.output())
    }
}

pub(crate) fn main(args: &[String]) -> Result<()> {
    if args.iter().any(|s| s == "--help" || s == "-h") {
        println!("Rust YNNPACK vision runner\n--model_dir=DIR --input_file=FILE [repeat] --output_dir=NEW_DIR\n--num_threads=1 --warmup_runs=3 --measured_runs=30 --dump_outputs");
        return Ok(());
    }
    let mut options = io::Arguments::parse(args, &["--input_file"], &["--dump_outputs"])?;
    let model = options.take("--model_dir", None)?;
    let output = options.take("--output_dir", None)?;
    if options.values.contains_key("--graph_file") { return Err(Error::invalid("Offline graph files are retired; use --model_dir with a semantic package")); }
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
    let builder = VisionBuilder::load(Path::new(&model))?;
    let model_name = builder.contract.model.clone();
    let construction_ms = start.elapsed().as_secs_f64() * 1000.0;
    let compile_start = Instant::now();
    let mut session = builder.prepare(threads)?;
    let compile_ms = compile_start.elapsed().as_secs_f64() * 1000.0;
    let setup_ms = start.elapsed().as_secs_f64() * 1000.0;
    let prepared_rss = ffi::rss();
    let mut cases = Vec::new();
    for (case, input) in inputs.iter().enumerate() {
        let values = io::read_f32(Path::new(input), session.input_mut().len())?;
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
            "engine":"ynnpack", "runner":"rust", "model":model_name, "model_dir":model, "preparation":session.session.preparation(), "threads":threads,
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
