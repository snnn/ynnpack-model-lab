// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
//! Owned, stateless tensor invocation, without token or vocabulary assumptions.
use super::{PreparationStats, PreparedProgram};
use crate::{
    ffi,
    plan::{Command, ValidatedPlan},
    Error, Result,
};
use serde::{Deserialize, Serialize};
use std::collections::{BTreeMap, BTreeSet};

#[derive(Clone, Serialize, Deserialize, PartialEq)]
#[serde(deny_unknown_fields)]
pub struct TensorBinding {
    pub name: String,
    pub dtype: String,
    pub shape: Vec<usize>,
}
#[derive(Clone, Serialize, Deserialize, PartialEq)]
#[serde(deny_unknown_fields)]
pub struct TensorPhase {
    pub inputs: Vec<TensorBinding>,
    pub outputs: Vec<TensorBinding>,
}
#[derive(Clone, Serialize, Deserialize, PartialEq)]
#[serde(deny_unknown_fields)]
pub struct TensorExecutionSpec {
    pub format: String,
    pub version: u32,
    pub graphs: BTreeMap<String, TensorPhase>,
}
impl TensorBinding {
    fn bytes(&self) -> Result<usize> {
        let bits = match self.dtype.as_str() {
            "fp32" | "int32" => 32,
            "bf16" | "fp16" => 16,
            "int8" | "uint8" => 8,
            _ => return Err(Error::invalid("Unsupported tensor binding dtype")),
        };
        super::execution::count(&self.shape)?
            .checked_mul(bits)
            .and_then(|n| n.checked_add(7))
            .map(|n| n / 8)
            .ok_or_else(|| Error::invalid("Tensor binding size overflow"))
    }
}
impl TensorExecutionSpec {
    pub(crate) fn validate(&self, plans: &BTreeMap<String, ValidatedPlan>) -> Result<()> {
        if self.format != "ynn-tensor-execution"
            || self.version != 1
            || self.graphs.is_empty()
            || self.graphs.keys().ne(plans.keys())
        {
            return Err(Error::invalid("Invalid tensor execution contract"));
        }
        for (phase, spec) in &self.graphs {
            let plan = &plans[phase];
            let mut names = BTreeSet::new();
            for (bindings, flags) in [(&spec.inputs, 1), (&spec.outputs, 2)] {
                for b in bindings {
                    b.bytes()?;
                    if b.name.is_empty() || !names.insert(b.name.as_str()) {
                        return Err(Error::invalid("Duplicate tensor binding"));
                    }
                    plan.require_tensor(
                        &b.name,
                        &b.dtype,
                        &b.shape.iter().map(|&n| Some(n as i64)).collect::<Vec<_>>(),
                        flags,
                    )?;
                }
            }
            if !plan.scalar_names().is_empty() {
                return Err(Error::invalid(
                    "Stateless tensor session has unbound scalars",
                ));
            }
            for c in plan.commands() {
                match c {
                    Command::Tensor { name, flags, .. }
                    | Command::PackedTensor { name, flags, .. }
                        if flags & 3 != 0 && !names.contains(name.as_str()) =>
                    {
                        return Err(Error::invalid(format!("Unbound tensor: {name}")))
                    }
                    Command::Resource { .. } => {
                        return Err(Error::invalid(
                            "Persistent resources require a stateful session",
                        ))
                    }
                    _ => (),
                }
            }
        }
        Ok(())
    }
}
struct Storage {
    spec: TensorBinding,
    data: ffi::Buffer<u64>,
    bytes: usize,
    input: bool,
}
pub struct TensorSession {
    // The graphs and asset mappings are dropped before bound allocations.
    prepared: PreparedProgram,
    storage: BTreeMap<(String, String), Storage>,
    failed: bool,
}
impl TensorSession {
    pub fn from_prepared(prepared: PreparedProgram) -> Result<Self> {
        let spec = prepared
            .tensors
            .as_ref()
            .ok_or_else(|| Error::invalid("Missing validated tensor contract"))?;
        let mut storage = BTreeMap::new();
        for (phase, g) in &spec.graphs {
            for (bindings, input) in [(&g.inputs, true), (&g.outputs, false)] {
                for b in bindings {
                    let bytes = b.bytes()?;
                    storage.insert(
                        (phase.clone(), b.name.clone()),
                        Storage {
                            spec: b.clone(),
                            data: ffi::Buffer::new(bytes.div_ceil(8), 0),
                            bytes,
                            input,
                        },
                    );
                }
            }
        }
        let mut session = Self {
            prepared,
            storage,
            failed: false,
        };
        for ((phase, name), b) in &session.storage {
            // Stable aligned allocations; no resizing or concurrent invocation.
            unsafe {
                session.prepared.graphs.get_mut(phase).unwrap().bind_bytes(
                    &ffi::string(name)?,
                    &b.data,
                    b.bytes,
                    if b.input { &b.spec.shape } else { &[] },
                    false,
                )?;
            }
        }
        Ok(session)
    }
    pub fn input_mut(&mut self, phase: &str, name: &str) -> Result<&mut [u8]> {
        let b = self
            .storage
            .get_mut(&(phase.into(), name.into()))
            .filter(|b| b.input)
            .ok_or_else(|| Error::invalid("Unknown input"))?;
        Ok(unsafe { std::slice::from_raw_parts_mut(b.data.as_mut_ptr().cast(), b.bytes) })
    }
    pub fn output(&self, phase: &str, name: &str) -> Result<&[u8]> {
        let b = self
            .storage
            .get(&(phase.into(), name.into()))
            .filter(|b| !b.input)
            .ok_or_else(|| Error::invalid("Unknown output"))?;
        Ok(unsafe { std::slice::from_raw_parts(b.data.as_ptr().cast(), b.bytes) })
    }
    pub fn input_f32_mut(&mut self, phase: &str, name: &str) -> Result<&mut [f32]> {
        let b = self
            .storage
            .get_mut(&(phase.into(), name.into()))
            .filter(|b| b.input && b.spec.dtype == "fp32")
            .ok_or_else(|| Error::invalid("Unknown FP32 input"))?;
        Ok(unsafe { std::slice::from_raw_parts_mut(b.data.as_mut_ptr().cast(), b.bytes / 4) })
    }
    pub fn output_f32(&self, phase: &str, name: &str) -> Result<&[f32]> {
        let b = self
            .storage
            .get(&(phase.into(), name.into()))
            .filter(|b| !b.input && b.spec.dtype == "fp32")
            .ok_or_else(|| Error::invalid("Unknown FP32 output"))?;
        Ok(unsafe { std::slice::from_raw_parts(b.data.as_ptr().cast(), b.bytes / 4) })
    }
    pub fn invoke(&mut self, phase: &str) -> Result<()> {
        if self.failed {
            return Err(Error::invalid("Failed tensor session must be discarded"));
        }
        let graph = self
            .prepared
            .graphs
            .get_mut(phase)
            .ok_or_else(|| Error::invalid("Unknown phase"))?;
        self.failed = true;
        graph.run()?;
        self.failed = false;
        Ok(())
    }
    pub fn preparation(&self) -> &PreparationStats {
        &self.prepared.stats
    }
}
