// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
//! Deferred, source-independent model authoring and YNNPACK compilation.
//! This module owns target choices. The runtime consumes only its validated plans.
mod builder;
mod emit;
mod lower;
mod model;
#[cfg(test)]
mod tests;
mod validate;
use crate::{Error, Result};
pub use builder::*;
pub use model::*;
use serde::Serialize;
use std::{collections::BTreeMap, path::Path};

#[derive(Debug, Serialize)]
pub struct CompiledPackage {
    pub plans: BTreeMap<String, String>,
    pub graphs: BTreeMap<String, Graph>,
    pub report: BTreeMap<String, serde_json::Value>,
    #[serde(skip)]
    pub assets: BTreeMap<String, Vec<u8>>,
}

#[derive(Default, Clone, Debug, Serialize)]
pub struct CompileTimings {
    pub validate_ms: f64,
    pub lower_ms: f64,
    pub emit_ms: f64,
    pub plan_check_ms: f64,
}
pub fn compile(program: &Program) -> Result<CompiledPackage> {
    compile_measured(program).map(|(package, _)| package)
}
pub fn compile_measured(program: &Program) -> Result<(CompiledPackage, CompileTimings)> {
    use std::time::Instant;
    let mut timings = CompileTimings::default();
    if program.version != 1 || program.phases.is_empty() || program.phase_options.keys().any(|name| !program.phases.contains_key(name)) {
        return Err(Error::invalid("Unsupported compiler request version"));
    }
    let mut result = CompiledPackage {
        plans: BTreeMap::new(),
        graphs: BTreeMap::new(),
        report: BTreeMap::new(),
        assets: BTreeMap::new(),
    };
    let mut resources = BTreeMap::new();
    for (phase, source) in &program.phases {
        let start = Instant::now();
        validate::graph(source, 0)?;
        if phase.is_empty()
            || !phase
                .bytes()
                .all(|c| c.is_ascii_alphanumeric() || c == b'_')
        {
            return Err(Error::invalid("Invalid phase name"));
        }
        for resource in &source.resources {
            let tensor = &source.values[&resource.owner].tensor;
            let normalized = |e: &Expr| -> Result<serde_json::Value> {
                fn bindings(value: &mut serde_json::Value, g: &Graph) -> Result<()> {
                    if let Some(id) = value.get("symbol").and_then(|x| x.as_u64()) {
                        let symbol = g
                            .symbols
                            .iter()
                            .find(|s| s.id == id as u32)
                            .ok_or_else(|| Error::invalid("Undefined resource symbol"))?;
                        *value = serde_json::json!({"binding":symbol.binding,"lower":symbol.lower,"upper":symbol.upper});
                    } else if let Some(object) = value.as_object_mut() {
                        for value in object.values_mut() {
                            bindings(value, g)?;
                        }
                    } else if let Some(array) = value.as_array_mut() {
                        for value in array {
                            bindings(value, g)?;
                        }
                    }
                    Ok(())
                }
                let mut value = serde_json::from_str(&geometry(e))?;
                bindings(&mut value, source)?;
                Ok(value)
            };
            let shape = tensor
                .shape
                .iter()
                .map(normalized)
                .collect::<Result<Vec<_>>>()?;
            let strides = resolved_strides(resource, tensor)
                .iter()
                .map(normalized)
                .collect::<Result<Vec<_>>>()?;
            let key = serde_json::to_string(&(
                tensor.dtype,
                &tensor.quant,
                axis(resource.axis, tensor.shape.len())?,
                shape,
                strides,
            ))?;
            if let Some(previous) = resources.insert(resource.name.clone(), key.clone()) {
                if previous != key {
                    return Err(Error::invalid("Incompatible cross-phase resource geometry"));
                }
            }
        }
        timings.validate_ms += start.elapsed().as_secs_f64() * 1000.0;
        let start = Instant::now();
        let mut source = source.clone();
        // Runtime-selected quantization parameters are part of an output's ABI.
        // Keep their tensors observable even when only the codes were authored
        // as a result; callers cannot interpret the codes without them.
        let mut companions = BTreeMap::new();
        for name in source.outputs.clone() {
            if let Some(p) = source.values[&name]
                .tensor
                .quant
                .as_ref()
                .and_then(|q| q.parameters.as_ref())
            {
                let parameters = vec![p.scales.clone(), p.zeros.clone()];
                for parameter in &parameters {
                    if !source.outputs.contains(parameter) {
                        source.outputs.push(parameter.clone());
                    }
                }
                companions.insert(name, parameters);
            }
        }
        let options = program.phase_options.get(phase).unwrap_or(&program.options);
        let graph = lower::lower(&source, options)?;
        timings.lower_ms += start.elapsed().as_secs_f64() * 1000.0;
        let start = Instant::now();
        let (text, assets, report) = emit::emit(&graph, options)?;
        let mut report = report;
        report["quantization_companion_outputs"] = serde_json::to_value(companions)?;
        timings.emit_ms += start.elapsed().as_secs_f64() * 1000.0;
        let start = Instant::now();
        crate::plan_text::check(&text)?;
        timings.plan_check_ms += start.elapsed().as_secs_f64() * 1000.0;
        result.plans.insert(phase.clone(), text);
        result.assets.extend(assets);
        result.report.insert(phase.clone(), report);
        result.graphs.insert(phase.clone(), graph);
    }
    Ok((result, timings))
}

impl CompiledPackage {
    /// Publish only after every phase has compiled and validated successfully.
    pub fn write(&self, output: &Path) -> Result<()> {
        if output.exists() {
            return Err(Error::invalid("Compiler output directory already exists"));
        }
        use std::sync::atomic::{AtomicU64, Ordering};
        static SERIAL: AtomicU64 = AtomicU64::new(0);
        let parent = output
            .parent()
            .filter(|p| !p.as_os_str().is_empty())
            .unwrap_or(Path::new("."));
        std::fs::create_dir_all(parent)?;
        let stage = loop {
            let path = parent.join(format!(
                ".ynn-package-{}-{}",
                std::process::id(),
                SERIAL.fetch_add(1, Ordering::Relaxed)
            ));
            match std::fs::create_dir(&path) {
                Ok(()) => break path,
                Err(e) if e.kind() == std::io::ErrorKind::AlreadyExists => continue,
                Err(e) => return Err(e.into()),
            }
        };
        struct Cleanup(std::path::PathBuf);
        impl Drop for Cleanup {
            fn drop(&mut self) {
                let _ = std::fs::remove_dir_all(&self.0);
            }
        }
        let _cleanup = Cleanup(stage.clone());
        std::fs::create_dir(stage.join("parameters"))?;
        for (name, bytes) in &self.assets {
            if name.len() != 68
                || !name.ends_with(".bin")
                || !name[..64].bytes().all(|b| b.is_ascii_hexdigit())
            {
                return Err(Error::invalid("Invalid generated asset name"));
            }
            std::fs::write(stage.join("parameters").join(name), bytes)?;
        }
        for (name, text) in &self.plans {
            if name.is_empty() || !name.bytes().all(|b| b.is_ascii_alphanumeric() || b == b'_') {
                return Err(Error::invalid("Invalid artifact name"));
            }
            std::fs::write(stage.join(format!("{name}.ynn")), text)?;
        }
        std::fs::write(
            stage.join("compile-report.json"),
            serde_json::to_vec_pretty(&self.report)?,
        )?;
        if output.exists() {
            return Err(Error::invalid(
                "Compiler output appeared during compilation",
            ));
        }
        std::fs::rename(stage, output)?;
        Ok(())
    }
}
