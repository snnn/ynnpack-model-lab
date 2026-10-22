// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
use crate::{Error, Result};
use serde::{Deserialize, Serialize};
use std::collections::{BTreeMap, BTreeSet};
use std::path::{Component, Path};

#[derive(Clone, Serialize, Debug, Deserialize, PartialEq)]
#[serde(untagged)]
pub enum Dim {
    Fixed(usize),
    Parameter(String),
}
impl Dim {
    pub fn value(&self, rows: usize, capacity: usize) -> Result<usize> {
        match self {
            Self::Fixed(n) if *n > 0 => Ok(*n),
            Self::Parameter(s) if s == "rows" => Ok(rows),
            Self::Parameter(s) if s == "capacity" => Ok(capacity),
            _ => Err(Error::invalid("Invalid interface dimension")),
        }
    }
}
#[derive(Clone, Serialize, Debug, Deserialize, PartialEq)]
#[serde(rename_all = "snake_case")]
pub enum Control {
    Position,
    End,
    ValidRows,
    Zero,
}
impl Control {
    pub fn value(&self, position: usize, valid: usize) -> usize {
        match self {
            Self::Position => position,
            Self::End => position + valid,
            Self::ValidRows => valid,
            Self::Zero => 0,
        }
    }
}
#[derive(Clone, Serialize, Debug, Deserialize, PartialEq)]
#[serde(tag = "kind", rename_all = "snake_case", deny_unknown_fields)]
pub enum Recipe {
    Tokens,
    Positions,
    Controls {
        values: Vec<Control>,
    },
    Mask {
        window: Option<usize>,
        masked: String,
    },
    Embedding {
        table: String,
        begin: usize,
        columns: usize,
    },
}
#[derive(Clone, Serialize, Debug, Deserialize, PartialEq)]
#[serde(deny_unknown_fields)]
pub struct Input {
    pub name: String,
    pub dtype: String,
    pub shape: Vec<Dim>,
    pub recipe: Recipe,
}
impl Input {
    pub fn dimensions(&self, rows: usize, capacity: usize) -> Result<Vec<usize>> {
        self.shape.iter().map(|d| d.value(rows, capacity)).collect()
    }
}
#[derive(Clone, Serialize, Deserialize, PartialEq)]
#[serde(deny_unknown_fields)]
pub struct PhaseSpec {
    pub logits: Option<String>,
    pub row_policy: String,
    pub inputs: Vec<Input>,
    pub scalars: BTreeMap<String, Control>,
}
#[derive(Clone, Serialize, Deserialize, PartialEq)]
#[serde(deny_unknown_fields)]
pub struct Cache {
    pub name: String,
    pub shape: Vec<Dim>,
    pub axis: usize,
    pub dtype: String,
}
#[derive(Clone, Serialize, Deserialize, PartialEq)]
#[serde(deny_unknown_fields)]
pub struct FixedState {
    pub input: String,
    pub output: String,
    pub shape: Vec<usize>,
}
#[derive(Clone, Serialize, Deserialize, PartialEq)]
#[serde(deny_unknown_fields)]
pub struct Asset {
    pub path: String,
    pub bytes: usize,
    pub sha256: String,
}
#[derive(Clone, Serialize, Deserialize, PartialEq)]
#[serde(deny_unknown_fields)]
pub struct Embedding {
    pub record: serde_json::Value,
    pub width: usize,
    pub bits: usize,
    pub block: usize,
    pub assets: Vec<Asset>,
}
#[derive(Clone, Serialize, Deserialize, PartialEq)]
#[serde(deny_unknown_fields)]
pub struct Compatibility {
    pub backend: String,
    pub backend_api: u32,
    pub artifact_abi: String,
    pub parameter_encoding: String,
    pub required_features: Vec<String>,
}
fn legacy_contract() -> u32 {
    1
}
#[derive(Clone, Serialize, Deserialize, PartialEq)]
#[serde(deny_unknown_fields)]
pub struct ExecutionSpec {
    pub format: String,
    #[serde(default = "legacy_contract")]
    pub contract: u32,
    pub compatibility: Option<Compatibility>,
    pub model: String, // Descriptive only; never selects execution behavior.
    pub capacity: usize,
    pub prefill_rows: usize,
    pub vocabulary: usize,
    pub prefill_after_decode: bool,
    pub graphs: BTreeMap<String, PhaseSpec>,
    pub resources: Vec<Cache>,
    pub fixed_states: Vec<FixedState>,
    pub embeddings: BTreeMap<String, Embedding>,
}
pub fn count(dims: &[usize]) -> Result<usize> {
    if dims.is_empty() || dims.len() > 6 || dims.contains(&0) {
        return Err(Error::invalid("Invalid interface shape"));
    }
    dims.iter()
        .try_fold(1usize, |a, b| a.checked_mul(*b))
        .filter(|&n| n <= 1usize << 30)
        .ok_or_else(|| Error::invalid("Interface shape exceeds allocation limit"))
}
fn hash(s: &str) -> bool {
    s.len() == 64 && s.bytes().all(|c| c.is_ascii_hexdigit())
}
pub fn relative(s: &str) -> bool {
    !s.is_empty()
        && Path::new(s)
            .components()
            .all(|p| matches!(p, Component::Normal(_)))
}
impl ExecutionSpec {
    // Interface validation is structural. The supplied variant must implement
    // the same logical program; model exporters own that semantic guarantee.
    pub fn validate_capacity_variant(&self, next: &Self) -> Result<()> {
        if self.format != next.format
            || self.contract != next.contract
            || self.compatibility != next.compatibility
            || self.model != next.model
            || self.prefill_rows != next.prefill_rows
            || self.vocabulary != next.vocabulary
            || self.prefill_after_decode != next.prefill_after_decode
            || self.fixed_states != next.fixed_states
            || self.embeddings != next.embeddings
            || self.resources != next.resources
            || self.graphs.len() != next.graphs.len()
        {
            return Err(Error::invalid(
                "Capacity variant changed the execution contract",
            ));
        }
        for (name, old) in &self.graphs {
            let new = next
                .graphs
                .get(name)
                .ok_or_else(|| Error::invalid("Missing capacity phase"))?;
            if old.logits != new.logits
                || old.row_policy != new.row_policy
                || old.inputs != new.inputs
                || old.scalars != new.scalars
            {
                return Err(Error::invalid("Capacity variant changed a phase interface"));
            }
        }
        Ok(())
    }
    pub(crate) fn validate_plan(
        &self,
        phase: &str,
        plan: &crate::plan::ValidatedPlan,
    ) -> Result<()> {
        use crate::plan::Command;
        let g = &self.graphs[phase];
        let rows = if phase == "prefill" {
            self.prefill_rows
        } else {
            1
        };
        let mut expected = BTreeSet::new();
        for input in &g.inputs {
            let dims = input
                .shape
                .iter()
                .map(|d| match d {
                    Dim::Fixed(n) => Some(*n as i64),
                    Dim::Parameter(s) if s == "capacity" => Some(self.capacity as i64),
                    Dim::Parameter(s) if s == "rows" => Some(rows as i64),
                    _ => None,
                })
                .collect::<Vec<_>>();
            plan.require_tensor(&input.name, &input.dtype, &dims, 1)?;
            expected.insert(input.name.as_str());
            count(&input.dimensions(rows, self.capacity)?)?;
        }
        for state in &self.fixed_states {
            let shape = state
                .shape
                .iter()
                .map(|&n| Some(n as i64))
                .collect::<Vec<_>>();
            plan.require_tensor(&state.input, "fp32", &shape, 1)?;
            plan.require_tensor(&state.output, "fp32", &shape, 2)?;
            expected.insert(state.input.as_str());
        }
        for state in &self.resources {
            let dims = state
                .shape
                .iter()
                .map(|d| match d {
                    Dim::Fixed(n) => Some(*n as i64),
                    Dim::Parameter(s) if s == "capacity" => Some(self.capacity as i64),
                    _ => None,
                })
                .collect::<Vec<_>>();
            plan.require_tensor(&state.name, &state.dtype, &dims, 1)?;
            expected.insert(state.name.as_str());
            let owner = plan.commands().iter().find_map(|c| match c {
                Command::Tensor { id, name, .. } if name == &state.name => Some(id),
                _ => None,
            });
            if !plan.commands().iter().any(|c|matches!(c,Command::Resource{owner:id,axis,..} if Some(id)==owner&&*axis==state.axis as i64)) {
                return Err(Error::invalid("Resource binding contract mismatch"));
            }
        }
        if let Some(name) = &g.logits {
            // A logits output may have a static or live leading row dimension.
            let c = plan
                .commands()
                .iter()
                .find(|c| matches!(c,Command::Tensor{name:n,..} if n==name))
                .ok_or_else(|| Error::invalid("Missing logits output"))?;
            if let Command::Tensor { dims, .. } = c {
                if dims.last() != Some(&self.vocabulary) {
                    return Err(Error::invalid("Logits vocabulary mismatch"));
                }
                let mut shape = vec![None; dims.len()];
                *shape.last_mut().unwrap() = Some(self.vocabulary as i64);
                plan.require_tensor(name, "fp32", &shape, 2)?;
            }
        }
        let scalars = plan
            .commands()
            .iter()
            .filter_map(|c| {
                if let Command::BindScalarParameter { tensor, name } = c {
                    Some((*tensor, name))
                } else {
                    None
                }
            })
            .collect::<Vec<_>>();
        if plan.scalar_names() != g.scalars.keys().map(String::as_str).collect() {
            return Err(Error::invalid("Scalar recipe coverage mismatch"));
        }
        let outputs = self
            .resources
            .iter()
            .map(|r| r.name.as_str())
            .chain(self.fixed_states.iter().map(|r| r.output.as_str()))
            .chain(g.logits.as_deref())
            .collect::<BTreeSet<_>>();
        for c in plan.commands() {
            if let Command::Tensor {
                id, name, flags, ..
            } = c
            {
                if flags & 2 != 0 && !outputs.contains(name.as_str()) {
                    return Err(Error::invalid(format!("Unbound plan output: {name}")));
                }
                if flags & 1 != 0
                    && !expected.contains(name.as_str())
                    && !scalars.iter().any(|(t, _)| t == id)
                {
                    return Err(Error::invalid(format!("Unbound plan input: {name}")));
                }
            }
            if let Command::Resource { owner, .. } = c {
                let name = plan.commands().iter().find_map(|c| match c {
                    Command::Tensor { id, name, .. } if id == owner => Some(name),
                    _ => None,
                });
                if !self.resources.iter().any(|r| Some(&r.name) == name) {
                    return Err(Error::invalid("Unbound plan resource"));
                }
            }
        }
        Ok(())
    }
    pub fn validate(&self) -> Result<()> {
        if !cfg!(target_endian = "little") {
            return Err(Error::invalid(
                "Runtime requires little-endian IEEE FP32 parameters",
            ));
        }
        match (self.contract, &self.compatibility) {
            (1, None) => {} // Qualified legacy packages retain their original semantics.
            (2, Some(c)) => {
                if c.backend != "ynnpack" || c.backend_api != 1 {
                    return Err(Error::invalid("Unsupported backend API contract"));
                }
                if c.artifact_abi != "data-only-v1"
                    || c.parameter_encoding != "little-endian-typed-v1"
                {
                    return Err(Error::invalid(
                        "Unsupported artifact ABI or parameter encoding",
                    ));
                }
                let supported = BTreeSet::from([
                    "shape-preflight-v1",
                    "resource-state-v1",
                    "completion-v1",
                    "fixed-state-v1",
                ]);
                let mut requested = BTreeSet::new();
                for feature in &c.required_features {
                    if !supported.contains(feature.as_str()) {
                        return Err(Error::invalid(format!(
                            "Unsupported required backend feature: {feature}"
                        )));
                    }
                    if !requested.insert(feature.as_str()) {
                        return Err(Error::invalid("Duplicate required backend feature"));
                    }
                }
                if requested != supported {
                    return Err(Error::invalid("Incomplete package feature declaration"));
                }
            }
            _ => return Err(Error::invalid("Unsupported model/runtime contract")),
        }
        if self.format != "ynn-llm-execution"
            || !(1..=32768).contains(&self.capacity)
            || !(1..=2048).contains(&self.prefill_rows)
            || self.prefill_rows > self.capacity
            || !(1..=2_097_152).contains(&self.vocabulary)
            || self.graphs.len() != 2
            || !self.graphs.contains_key("prefill")
            || !self.graphs.contains_key("decode")
            || self.graphs["decode"].logits.is_none()
            || self.resources.len() > 512
            || self.fixed_states.len() > 512
            || self.embeddings.len() > 16
        {
            return Err(Error::invalid("Invalid execution package"));
        }
        let mut state_names = BTreeSet::new();
        for r in &self.resources {
            let dims = r
                .shape
                .iter()
                .map(|d| d.value(1, self.capacity))
                .collect::<Result<Vec<_>>>()?;
            count(&dims)?;
            if r.axis >= dims.len()
                || dims[r.axis] != self.capacity
                || !["int2", "int4", "int8", "fp32", "bf16"].contains(&r.dtype.as_str())
                || !state_names.insert(r.name.clone())
            {
                return Err(Error::invalid("Invalid resource contract"));
            }
        }
        for r in &self.fixed_states {
            if count(&r.shape)? > 16_777_216
                || !state_names.insert(r.input.clone())
                || !state_names.insert(r.output.clone())
            {
                return Err(Error::invalid("Invalid fixed state contract"));
            }
        }
        for e in self.embeddings.values() {
            if ![2, 4, 8].contains(&e.bits)
                || e.block == 0
                || e.width == 0
                || e.width % e.block != 0
                || e.width % (8 / e.bits) != 0
                || e.assets.len() != 2
            {
                return Err(Error::invalid("Invalid packed embedding"));
            }
            for a in &e.assets {
                if !relative(a.path.strip_prefix("@parameters/").unwrap_or(&a.path))
                    || a.bytes == 0
                    || !hash(&a.sha256)
                {
                    return Err(Error::invalid("Invalid embedding asset"));
                }
            }
            // All files used by the native record must be hash-verified first.
            for (file, bytes) in [
                (&e.record["file"], &e.record["bytes"]),
                (
                    &e.record["quantization"]["scales_file"],
                    &e.record["quantization"]["scales_bytes"],
                ),
            ] {
                if !e.assets.iter().any(|a| {
                    Some(a.path.as_str()) == file.as_str() && Some(a.bytes as u64) == bytes.as_u64()
                }) {
                    return Err(Error::invalid(
                        "Embedding record references an unchecked asset",
                    ));
                }
            }
        }
        for (phase, g) in &self.graphs {
            let rows = if phase == "prefill" {
                self.prefill_rows
            } else {
                1
            };
            if !["valid", "padded"].contains(&g.row_policy.as_str())
                || g.inputs.len() > 1024
                || g.scalars.len() > 32
            {
                return Err(Error::invalid("Invalid phase contract"));
            }
            let mut names = state_names.clone();
            for x in &g.inputs {
                if x.name.is_empty()
                    || !names.insert(x.name.clone())
                    || !["fp32", "int32"].contains(&x.dtype.as_str())
                {
                    return Err(Error::invalid("Invalid input binding"));
                }
                let n = count(&x.dimensions(rows, self.capacity)?)?;
                let valid = match &x.recipe {
                    Recipe::Tokens => x.dtype == "int32" && n == rows,
                    Recipe::Positions => n == rows,
                    Recipe::Controls { values } => x.dtype == "int32" && n == values.len(),
                    Recipe::Mask { window, masked } => {
                        x.dtype == "fp32"
                            && n == rows * self.capacity
                            && window.is_none_or(|w| w > 0)
                            && ["finite_min", "negative_infinity"].contains(&masked.as_str())
                    }
                    Recipe::Embedding {
                        table,
                        begin,
                        columns,
                    } => {
                        x.dtype == "fp32"
                            && *columns > 0
                            && self.embeddings.get(table).is_some_and(|e| {
                                begin.checked_add(*columns).is_some_and(|n| n <= e.width)
                            })
                            && n == rows * columns
                    }
                };
                if !valid {
                    return Err(Error::invalid(format!("Invalid input recipe: {}", x.name)));
                }
            }
        }
        Ok(())
    }
}
