// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
use super::*;
use std::collections::{HashMap, HashSet};
impl Lowerer {
    fn reshape_heads(&mut self, x: &str, kv: Expr, group: i64, small: bool) -> Result<String> {
        let split = self.temp(
            Op::SplitDim,
            &[x.into()],
            "groups",
            Attributes {
                axis: 1,
                shape: vec![kv, Expr::Known(group)],
                ..Attributes::default()
            },
        )?;
        if small {
            self.temp(
                Op::FuseDims,
                &[split],
                "group_rows",
                Attributes {
                    axis: 2,
                    integers: vec![2],
                    ..Attributes::default()
                },
            )
        } else {
            Ok(split)
        }
    }
    fn canonical_heads(&mut self, x: &str, group: i64, rows: Expr, small: bool) -> Result<String> {
        let x = if small {
            self.temp(
                Op::SplitDim,
                &[x.into()],
                "head_rows",
                Attributes {
                    axis: 2,
                    shape: vec![Expr::Known(group), rows],
                    ..Attributes::default()
                },
            )?
        } else {
            x.into()
        };
        self.temp(
            Op::FuseDims,
            &[x],
            "heads",
            Attributes {
                axis: 1,
                integers: vec![2],
                ..Attributes::default()
            },
        )
    }
    fn transpose_attention(&mut self, x: &str) -> Result<String> {
        self.temp(
            Op::Transpose,
            &[x.into()],
            "transpose",
            Attributes {
                integers: vec![0, 1, 3, 2],
                ..Attributes::default()
            },
        )
    }
    fn expand_attention(&mut self, x: &str) -> Result<String> {
        self.temp(
            Op::ExpandDims,
            &[x.into()],
            "expand",
            Attributes {
                axes: vec![2],
                ..Attributes::default()
            },
        )
    }
    fn attention_dot(&mut self, x: &str, y: &str, adj_y: bool) -> Result<String> {
        self.temp(
            Op::Matmul,
            &[x.into(), y.into()],
            "dot",
            Attributes {
                adj_y,
                ..Attributes::default()
            },
        )
    }
    fn attention_mask(
        &mut self,
        mut scores: String,
        mask: Option<String>,
        a: &Attention,
    ) -> Result<String> {
        if let Some(mask) = mask {
            scores = if a.mask == 1 {
                let excluded = self.f(f32::NEG_INFINITY);
                self.temp(
                    Op::Select,
                    &[mask, scores, excluded],
                    "masked",
                    Attributes::default(),
                )?
            } else {
                self.binary(Op::Add, &scores, &mask)?
            };
        }
        if a.causal {
            scores = self.temp(
                Op::CausalMask,
                &[scores],
                "causal",
                Attributes {
                    position: a.query_position.clone(),
                    begin: a.key_position.clone(),
                    window: a.window,
                    ..Attributes::default()
                },
            )?;
        }
        let probs = self.value("probabilities");
        self.softmax(&Node {
            op: Op::Softmax,
            inputs: vec![scores],
            outputs: vec![probs.clone()],
            attributes: Attributes::default(),
            waits: vec![],
            completes: vec![],
            scope: self.scope.clone(),
        })?;
        Ok(probs)
    }
    pub(super) fn attention(&mut self, n: &Node) -> Result<()> {
        let a = n
            .attributes
            .attention
            .as_ref()
            .ok_or_else(|| Error::invalid("Missing attention contract"))?;
        let qs = self.g.shape(&n.inputs[0])?;
        let ks = self.g.shape(&n.inputs[1])?;
        if qs.len() != 4
            || ks.len() != 4
            || !a.fp32
            || self.g.values[&n.inputs[0]].tensor.dtype != Dtype::F32
        {
            return Err(Error::invalid(
                "SDPA requires FP32 rank-four operands/intermediates",
            ));
        }
        let syms = self
            .g
            .symbols
            .iter()
            .map(|s| (s.id, (s.lower, s.upper)))
            .collect::<HashMap<_, _>>();
        let lower = ks[2]
            .bounds_in(&syms, &mut 4096, 0, &HashSet::new(), false)
            .ok()
            .map(|r| r.0)
            .unwrap_or(0);
        if !n.waits.is_empty()
            || !n.completes.is_empty()
            || !a.reassociate
            || !a.reorder_reduction
            || !a.masked_nonfinite
            || !a.all_masked_nan
            || (a.causal && qs[0] != Expr::Known(1))
            || lower <= 0
            || a.query_length.as_ref().is_some_and(|x| *x != qs[2])
            || a.key_length.as_ref().is_some_and(|x| *x != ks[2])
        {
            self.g.nodes.push(n.clone());
            return Ok(());
        }
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
        if group == 0 {
            return self.sliced_attention(n, a);
        }
        let small = qs[2]
            .literal()
            .is_some_and(|r| r > 0 && group <= 8 && r <= 8 / group);
        let (mut q, mut k, mut v) = (
            n.inputs[0].clone(),
            n.inputs[1].clone(),
            n.inputs[2].clone(),
        );
        if group > 1 {
            q = self.reshape_heads(&q, ks[1].clone(), group, small)?;
            if !small {
                k = self.expand_attention(&k)?;
            }
        }
        let scale = self.f(a.scale.get() as f32);
        q = self.binary(Op::Mul, &q, &scale)?;
        let mut mask = if a.mask != 0 {
            Some(n.inputs[3].clone())
        } else {
            None
        };
        let mut grouped = group > 1 && !small && !a.causal;
        if grouped {
            if let Some(m) = mask.clone() {
                let ms = self.g.shape(&m)?;
                if ms.len() >= 3 {
                    let ax = ms.len() - 3;
                    match ms[ax].literal() {
                        None => grouped = false,
                        Some(1) => {
                            if ms.len() == 4 {
                                mask = Some(self.expand_attention(&m)?);
                            }
                        }
                        Some(_) => {
                            mask = Some(self.temp(
                                Op::SplitDim,
                                &[m],
                                "mask_groups",
                                Attributes {
                                    axis: ax as i64,
                                    shape: vec![ks[1].clone(), Expr::Known(group)],
                                    ..Attributes::default()
                                },
                            )?);
                        }
                    }
                }
            }
        }
        let mut scores = if small {
            let t = self.attention_dot(&k, &q, true)?;
            self.transpose_attention(&t)?
        } else {
            self.attention_dot(&q, &k, true)?
        };
        if group > 1 && !grouped {
            scores = self.canonical_heads(&scores, group, qs[2].clone(), small)?;
        }
        let mut p = self.attention_mask(scores, mask, a)?;
        if group > 1 && !grouped {
            p = self.reshape_heads(&p, ks[1].clone(), group, small)?;
        }
        let mut transposed = false;
        for producer in &self.g.nodes {
            if producer.op == Op::Transpose
                && producer.outputs == [v.clone()]
                && producer.waits.is_empty()
                && producer.completes.is_empty()
                && producer.attributes.integers == [0, 1, 3, 2]
            {
                v = producer.inputs[0].clone();
                transposed = true;
                break;
            }
        }
        let context = if small {
            if !transposed {
                v = self.transpose_attention(&v)?;
            }
            let c = self.attention_dot(&v, &p, true)?;
            self.transpose_attention(&c)?
        } else {
            if group > 1 {
                v = self.expand_attention(&v)?;
            }
            self.attention_dot(&p, &v, transposed)?
        };
        let context = if group > 1 {
            self.canonical_heads(&context, group, qs[2].clone(), small)?
        } else {
            context
        };
        self.copy(&context, &n.outputs[0])
    }
    fn sliced_attention(&mut self, n: &Node, a: &Attention) -> Result<()> {
        let mut contexts = vec![];
        let scale = self.f(a.scale.get() as f32);
        let mut head = 0;
        while head < a.heads.len() {
            let first = head;
            let kv = a.heads[head];
            while head < a.heads.len() && a.heads[head] == kv {
                head += 1;
            }
            let mut inputs = vec![];
            for (i, (start, count)) in [(first as i64, (head - first) as i64), (kv, 1), (kv, 1)]
                .into_iter()
                .enumerate()
            {
                let mut shape = self.g.shape(&n.inputs[i])?;
                shape[1] = Expr::Known(count);
                let mut starts = vec![Expr::Known(0); 4];
                starts[1] = Expr::Known(start);
                inputs.push(self.temp(
                    Op::Slice,
                    &[n.inputs[i].clone()],
                    "head_slice",
                    Attributes {
                        starts,
                        lengths: shape,
                        ..Attributes::default()
                    },
                )?);
            }
            let dot = self.attention_dot(&inputs[0], &inputs[1], true)?;
            let scores = self.binary(Op::Mul, &dot, &scale)?;
            let mask = if a.mask == 0 {
                None
            } else {
                let m = n.inputs[3].clone();
                let mut shape = self.g.shape(&m)?;
                if shape.len() >= 3 && shape[shape.len() - 3] != Expr::Known(1) {
                    let ax = shape.len() - 3;
                    let mut starts = vec![Expr::Known(0); shape.len()];
                    starts[ax] = Expr::Known(first as i64);
                    shape[ax] = Expr::Known((head - first) as i64);
                    Some(self.temp(
                        Op::Slice,
                        &[m],
                        "mask_slice",
                        Attributes {
                            starts,
                            lengths: shape,
                            ..Attributes::default()
                        },
                    )?)
                } else {
                    Some(m)
                }
            };
            let p = self.attention_mask(scores, mask, a)?;
            contexts.push(self.attention_dot(&p, &inputs[2], false)?);
        }
        self.emit(
            Op::Concat,
            &contexts,
            &n.outputs[0],
            Attributes {
                axis: 1,
                ..Attributes::default()
            },
        )?;
        Ok(())
    }
}
