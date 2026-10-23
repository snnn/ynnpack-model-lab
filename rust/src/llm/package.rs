// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
//! LLM view of a verified semantic package.
use crate::{compiler, runtime::package::ModelPackage, Result};
pub use crate::runtime::execution::*;
use std::path::Path;
pub struct Package {
    pub spec: ExecutionSpec,
    pub program: compiler::Program,
    pub metadata: serde_json::Value,
}
impl std::ops::Deref for Package {
    type Target = ExecutionSpec;
    fn deref(&self) -> &ExecutionSpec { &self.spec }
}
impl Package {
    pub fn read(root: &Path) -> Result<Self> {
        let p = ModelPackage::read(root)?;
        let spec: ExecutionSpec = p.execution()?;
        spec.validate()?;
        Ok(Self { spec, program: p.program, metadata: p.metadata })
    }
}
