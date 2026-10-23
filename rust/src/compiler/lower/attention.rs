// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
use super::*;
use std::collections::{HashMap, HashSet};
pub(super) struct Facts {
    pub query: Vec<Expr>,
    pub key: Vec<Expr>,
    pub eligible: bool,
    pub group: i64,
    pub small: bool,
    pub grouped: bool,
    pub value_source: String,
    pub transposed_value: bool,
}
impl Facts {
    pub fn new(g: &Graph, n: &Node) -> Result<Self> {
        let a = n
            .attributes
            .attention
            .as_ref()
            .ok_or_else(|| Error::invalid("Missing attention contract"))?;
        let qs = g.shape(&n.inputs[0])?;
        let ks = g.shape(&n.inputs[1])?;
        if qs.len() != 4
            || ks.len() != 4
            || !a.fp32
            || g.values[&n.inputs[0]].tensor.dtype != Dtype::F32
        {
            return Err(Error::invalid(
                "SDPA requires FP32 rank-four operands/intermediates",
            ));
        }
        let syms = g
            .symbols
            .iter()
            .map(|s| (s.id, (s.lower, s.upper)))
            .collect::<HashMap<_, _>>();
        let lower = ks[2]
            .bounds_in(&syms, &mut 4096, 0, &HashSet::new(), false)
            .ok()
            .map(|r| r.0)
            .unwrap_or(0);
        let eligible = n.waits.is_empty()
            && n.completes.is_empty()
            && a.reassociate
            && a.reorder_reduction
            && a.masked_nonfinite
            && a.all_masked_nan
            && (!a.causal || qs[0] == Expr::Known(1))
            && lower > 0
            && !a.query_length.as_ref().is_some_and(|x| *x != qs[2])
            && !a.key_length.as_ref().is_some_and(|x| *x != ks[2]);
        let group = match (qs[1].literal(), ks[1].literal()) {
            (Some(q), Some(k))
                if k > 0
                    && q > 0
                    && q % k == 0
                    && a.heads
                        .iter()
                        .enumerate()
                        .all(|(h, v)| *v == h as i64 / (q / k)) =>
            {
                q / k
            }
            _ => 0,
        };
        let small = qs[2]
            .literal()
            .is_some_and(|r| r > 0 && group <= 8 && r <= 8 / group.max(1));
        let mut grouped = group > 1 && !small && !a.causal;
        if grouped && a.mask != 0 {
            let ms = g.shape(&n.inputs[3])?;
            if ms.len() >= 3 && ms[ms.len() - 3].literal().is_none() {
                grouped = false;
            }
        }
        let mut value_source = n.inputs[2].clone();
        let mut transposed_value = false;
        for producer in &g.nodes {
            if producer.op == Op::Transpose
                && producer.outputs == [value_source.clone()]
                && producer.waits.is_empty()
                && producer.completes.is_empty()
                && producer.attributes.integers == [0, 1, 3, 2]
            {
                value_source = producer.inputs[0].clone();
                transposed_value = true;
                break;
            }
        }
        Ok(Self {
            query: qs,
            key: ks,
            eligible,
            group,
            small,
            grouped,
            value_source,
            transposed_value,
        })
    }
}
