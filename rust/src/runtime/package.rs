// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
//! Serialized semantic input. Compiled plans are never deployment artifacts.
use crate::{compiler::Program, Error, Result};
use serde::de::DeserializeOwned;
use sha2::{Digest, Sha256};
use std::path::Path;

pub struct ModelPackage {
    pub program: Program,
    pub execution: serde_json::Value,
    pub metadata: serde_json::Value,
}
impl ModelPackage {
    pub fn read(root: &Path) -> Result<Self> {
        fn read(path: &Path, limit: u64) -> Result<Vec<u8>> {
            use std::io::Read;
            let mut bytes = Vec::new();
            std::fs::File::open(path)?
                .take(limit + 1)
                .read_to_end(&mut bytes)?;
            if bytes.len() as u64 > limit {
                return Err(Error::invalid("Oversized semantic package"));
            }
            Ok(bytes)
        }
        let metadata: serde_json::Value =
            serde_json::from_slice(&read(&root.join("model.json"), 16 << 20)?)?;
        let identity = &metadata["package"];
        if identity["format"] != "ynn-semantic-package" || identity["version"] != 1 {
            return Err(Error::invalid("Expected a semantic package; regenerate this model with program.json and execution.json. Offline .ynn loading is retired."));
        }
        let mut files = Vec::new();
        for (name, limit) in [("program.json", 128 << 20), ("execution.json", 16 << 20)] {
            let file = identity[name]["file"].as_str().unwrap_or(name);
            if file != name && !(name == "program.json" && file == "program.json.gz") {
                return Err(Error::invalid("Invalid semantic artifact filename"));
            }
            let bytes = read(&root.join(file), limit)?;
            if identity[name]["sha256"].as_str()
                != Some(format!("{:x}", Sha256::digest(&bytes)).as_str())
                || identity[name]["bytes"].as_u64() != Some(bytes.len() as u64)
            {
                return Err(Error::invalid(format!(
                    "Semantic artifact identity mismatch: {name}"
                )));
            }
            if file.ends_with(".gz") {
                use std::io::Read;
                let mut decoder = flate2::bufread::GzDecoder::new(bytes.as_slice());
                let mut decoded = Vec::new();
                decoder.by_ref().take(limit + 1).read_to_end(&mut decoded)?;
                if decoded.len() as u64 > limit || !decoder.into_inner().is_empty() {
                    return Err(Error::invalid(
                        "Oversized or trailing compressed semantic data",
                    ));
                }
                files.push(decoded);
            } else {
                files.push(bytes);
            }
        }
        Ok(Self {
            program: serde_json::from_slice(&files[0])?,
            execution: serde_json::from_slice(&files[1])?,
            metadata,
        })
    }
    pub fn execution<T: DeserializeOwned>(&self) -> Result<T> {
        Ok(serde_json::from_value(self.execution.clone())?)
    }

    /// Check lowering and the complete interface without loading model weights.
    /// Native preparation additionally verifies source payloads and capabilities.
    pub fn validate(&self) -> Result<()> {
        let compiled = crate::compiler::compile(&self.program)?;
        let plans = compiled
            .plans
            .iter()
            .map(|(phase, text)| {
                Ok((
                    phase.clone(),
                    crate::plan::ValidatedPlan::from_bytes(text.as_bytes())?,
                ))
            })
            .collect::<Result<std::collections::BTreeMap<_, _>>>()?;
        match self.execution["format"].as_str() {
            Some("ynn-llm-execution") => {
                let spec: super::ExecutionSpec = self.execution()?;
                spec.validate()?;
                if spec.graphs.keys().ne(plans.keys()) {
                    return Err(Error::invalid("Execution phases differ from program"));
                }
                for (phase, plan) in &plans {
                    spec.validate_plan(phase, plan)?;
                }
                Ok(())
            }
            Some("ynn-tensor-execution") => self
                .execution::<super::tensor::TensorExecutionSpec>()?
                .validate(&plans),
            _ => Err(Error::invalid("Unknown execution contract")),
        }
    }
}
