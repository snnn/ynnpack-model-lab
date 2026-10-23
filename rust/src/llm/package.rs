// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
//! Compatibility reader for offline packages. ExecutionSpec has no file identity.
use crate::{io, Error, Result};
pub use crate::runtime::execution::*;
use std::{collections::BTreeMap, path::Path};

pub struct PlanFile { pub file: String, pub sha256: String }
pub struct Package {
    pub spec: ExecutionSpec,
    pub files: BTreeMap<String, PlanFile>,
}
impl std::ops::Deref for Package {
    type Target = ExecutionSpec;
    fn deref(&self) -> &ExecutionSpec { &self.spec }
}
impl Package {
    pub fn read(root: &Path) -> Result<Self> {
        let value: serde_json::Value = serde_json::from_slice(&io::read_limited(
            &root.join("model.json"), 16 * 1024 * 1024)?)?;
        let mut runner = value.get("runner").cloned()
            .ok_or_else(|| Error::invalid("Package has no generic runner interface"))?;
        let phases = runner.get_mut("graphs").and_then(|x| x.as_object_mut())
            .ok_or_else(|| Error::invalid("Package has no phases"))?;
        let mut files = BTreeMap::new();
        for (name, phase) in phases {
            let phase = phase.as_object_mut().ok_or_else(|| Error::invalid("Invalid phase"))?;
            let mut take = |key| phase.remove(key).and_then(|x| x.as_str().map(str::to_owned))
                .ok_or_else(|| Error::invalid("Missing phase identity"));
            let file = take("file")?;
            let sha256 = take("sha256")?;
            if !relative(&file) || sha256.len() != 64 || !sha256.bytes().all(|c| c.is_ascii_hexdigit()) {
                return Err(Error::invalid("Invalid phase identity"));
            }
            files.insert(name.clone(), PlanFile { file, sha256 });
        }
        let spec: ExecutionSpec = serde_json::from_value(runner)?;
        spec.validate()?;
        Ok(Self { spec, files })
    }
    pub(crate) fn plans(&self, root: &Path) -> Result<BTreeMap<String, crate::plan::ValidatedPlan>> {
        use sha2::{Digest, Sha256};
        self.files.iter().map(|(phase, file)| {
            let bytes = io::read_limited(&root.join(&file.file), 128 * 1024 * 1024)?;
            if format!("{:x}", Sha256::digest(&bytes)) != file.sha256 {
                return Err(Error::invalid("Phase hash mismatch"));
            }
            let plan = crate::plan::ValidatedPlan::from_bytes(&bytes)?;
            self.spec.validate_plan(phase, &plan)?;
            Ok((phase.clone(), plan))
        }).collect()
    }
    pub fn validate_files(&self, root: &Path) -> Result<()> { self.plans(root).map(|_| ()) }
}
