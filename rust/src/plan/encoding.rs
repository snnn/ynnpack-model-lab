// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
use super::{float, require, Arg, Result};
use serde::Serialize;
use std::collections::{HashMap, HashSet};

/// Storage identity shared by graphs attaching to the same persistent resource.
/// Scale bits are retained exactly, just like other numeric plan attributes.
#[derive(Debug, Clone, PartialEq, Eq, Serialize)]
pub(crate) struct Encoding {
    pub dtype: String,
    pub axis: Option<i64>,
    pub scales: Vec<String>,
    pub zero_points: Vec<i64>,
}
impl Encoding {
    pub fn validate(&self) -> Result<()> {
        Arg::Dtype(self.dtype.clone()).check("dtype", &HashMap::new(), &HashSet::new())?;
        require(self.scales.len() <= 1024, "Oversized resource encoding")?;
        require(
            self.scales.len() == self.zero_points.len()
                && self.axis.is_some() == !self.scales.is_empty(),
            "Quantized encoding requires an axis and matching scales/zero_points",
        )?;
        for bits in &self.scales {
            require(float(bits)? > 0.0, "Resource scale must be positive")?;
        }
        if !self.scales.is_empty() {
            let range = match self.dtype.as_str() {
                "int2" => -2..=1,
                "int4" => -8..=7,
                "int8" => -128..=127,
                "uint8" => 0..=255,
                "int32" => i32::MIN as i64..=i32::MAX as i64,
                _ => {
                    return Err(super::invalid(
                        "Quantized resource requires integer storage",
                    ))
                }
            };
            require(
                self.zero_points.iter().all(|z| range.contains(z)),
                "Resource zero point outside storage range",
            )?;
        }
        Ok(())
    }
    /// The native adapter treats this as an opaque equality token, never JSON.
    pub fn token(&self) -> String {
        format!(
            "encoding-v1:{}:{}:{}:{}",
            self.dtype,
            self.axis.map_or("none".into(), |a| a.to_string()),
            self.scales
                .iter()
                .map(|s| s.to_ascii_lowercase())
                .collect::<Vec<_>>()
                .join(","),
            self.zero_points
                .iter()
                .map(ToString::to_string)
                .collect::<Vec<_>>()
                .join(",")
        )
    }
}
