// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
use crate::{ffi, plan::ValidatedPlan, Error, Result};
use serde::Deserialize;
use sha2::{Digest, Sha256};
use std::collections::BTreeMap;
use std::path::{Component, Path};

#[derive(Deserialize)]
pub(super) struct Package {
    pub execution: Execution,
    architecture: Architecture,
}
#[derive(Deserialize)]
struct Architecture {
    variant: String,
    vocab_size: u32,
    embed_dim: u32,
    num_layers: u32,
    per_layer_input_dim: u32,
    num_kv_owners: u32,
    num_kv_heads: u32,
    head_dim: u32,
    global_key_size: u32,
    attention_pattern_size: u32,
}
#[derive(Deserialize)]
#[serde(deny_unknown_fields)]
pub(super) struct Execution {
    format: String,
    version: u32,
    pub variant: String,
    pub profile: String,
    pub asset_source: String,
    pub source_identity: String,
    pub activation_dtype: String,
    logits_dtype: String,
    pub kv_dtype: String,
    pub kv_element_bytes: usize,
    pub prefill_rows: usize,
    pub prefill_attention_profile: String,
    pub decode_attention_profile: String,
    phases: BTreeMap<String, Phase>,
}
#[derive(Deserialize)]
#[serde(deny_unknown_fields)]
struct Phase {
    file: String,
    sha256: String,
}

impl Package {
    pub fn vocab_size(&self) -> usize {
        self.architecture.vocab_size as usize
    }
    pub fn read(root: &Path) -> Result<Self> {
        let bytes = crate::io::read_limited(&root.join("model.json"), 16 * 1024 * 1024)?;
        if bytes.len() > 16 * 1024 * 1024 {
            return Err(Error::invalid("Oversized model metadata"));
        }
        let p: Self = serde_json::from_slice(&bytes)?;
        let e = &p.execution;
        if p.architecture.vocab_size == 0
            || p.architecture.vocab_size > i32::MAX as u32
            || e.format != "gemma4-execution"
            || e.version != 1
            || e.variant != p.architecture.variant
            || format!("gemma4_{}", e.variant) != ffi::model_name()
            || !["fp32", "bf16"].contains(&e.activation_dtype.as_str())
            || e.logits_dtype != "fp32"
            || !["int8", "bf16"].contains(&e.kv_dtype.as_str())
            || e.kv_element_bytes != if e.kv_dtype == "bf16" { 2 } else { 1 }
            || !(1..=128).contains(&e.prefill_rows)
            || e.phases.len() != 2
            || !e.phases.contains_key("prefill")
            || !e.phases.contains_key("decode")
            || !["published", "hf"].contains(&e.asset_source.as_str())
            || e.profile.is_empty()
        {
            return Err(Error::invalid(
                "Unsupported/inconsistent Gemma execution metadata",
            ));
        }
        if e.asset_source == "published" && (e.activation_dtype != "fp32" || e.kv_dtype != "int8") {
            return Err(Error::invalid(
                "Published assets require FP32 activations and INT8 KV",
            ));
        }
        if e.asset_source == "hf"
            && (e.variant != "e2b"
                || e.source_identity.len() != 64
                || !e.source_identity.bytes().all(|b| b.is_ascii_hexdigit()))
        {
            return Err(Error::invalid("Invalid safetensors source identity"));
        }
        Ok(p)
    }
    pub fn check_assets(&self, assets: &ffi::Assets) -> Result<ffi::Config> {
        let c = assets.config()?;
        let a = &self.architecture;
        if (c.vocab, c.width, c.layers, c.ple_width, c.owners)
            != (
                a.vocab_size,
                a.embed_dim,
                a.num_layers,
                a.per_layer_input_dim,
                a.num_kv_owners,
            )
            || a.attention_pattern_size == 0
        {
            return Err(Error::invalid("Model architecture does not match assets"));
        }
        for i in 0..c.owners {
            let owner = assets.owner(i as usize)?;
            let width = if (i + 1) % a.attention_pattern_size == 0 {
                a.global_key_size
            } else {
                a.head_dim
            };
            if owner.owner != i || owner.heads != a.num_kv_heads || owner.width != width {
                return Err(Error::invalid("Model KV geometry does not match assets"));
            }
        }
        Ok(c)
    }
    pub fn plan(&self, root: &Path, phase: &str) -> Result<ValidatedPlan> {
        let entry = self
            .execution
            .phases
            .get(phase)
            .ok_or_else(|| Error::invalid("Missing phase"))?;
        let path = Path::new(&entry.file);
        if path.components().count() != 1
            || !matches!(path.components().next(), Some(Component::Normal(_)))
        {
            return Err(Error::invalid(
                "Phase plan must be a package-local filename",
            ));
        }
        let bytes = crate::io::read_limited(&root.join(path), 128 * 1024 * 1024)?;
        if format!("{:x}", Sha256::digest(&bytes)) != entry.sha256 {
            return Err(Error::invalid(format!("Phase plan hash mismatch: {phase}")));
        }
        // Parse the verified bytes, avoiding a second filesystem read.
        let plan = ValidatedPlan::from_bytes(&bytes)?;
        let a = &self.architecture;
        let rows = if phase == "decode" { Some(1) } else { None };
        plan.require_tensor(
            "embedded_input",
            &self.execution.activation_dtype,
            &[Some(1), rows, Some(a.embed_dim as i64)],
            1,
        )?;
        plan.require_tensor("positions", "fp32", &[Some(1), Some(1), rows, Some(1)], 1)?;
        for i in 0..a.num_kv_owners {
            let width = if (i + 1) % a.attention_pattern_size == 0 {
                a.global_key_size
            } else {
                a.head_dim
            };
            for side in ["key", "value"] {
                plan.require_tensor(
                    &format!("cache_{side}_{i}"),
                    &self.execution.kv_dtype,
                    &[
                        Some(1),
                        Some(a.num_kv_heads as i64),
                        None,
                        Some(width as i64),
                    ],
                    1,
                )?;
            }
        }
        if phase == "decode" {
            plan.require_tensor(
                "logits",
                "fp32",
                &[Some(1), Some(1), Some(a.vocab_size as i64)],
                2,
            )?;
        }
        Ok(plan)
    }
}
