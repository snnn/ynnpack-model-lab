// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
//! ISLE matching uses immutable graph facts. Construction owns a temporary graph
//! for the lowering pass; errors discard that graph before it can be published.
use super::*;
use Op::*;
#[allow(
    dead_code,
    unused_imports,
    unused_variables,
    unused_mut,
    non_snake_case,
    unreachable_patterns,
    irrefutable_let_patterns
)]
mod generated {
    extern crate alloc;
    use super::*;
    include!(concat!(env!("OUT_DIR"), "/lower.rs"));
}
struct Context<'a> {
    l: &'a mut Lowerer,
    n: &'a Node,
    values: Vec<String>,
    error: Option<Error>,
    attention: Option<attention::Facts>,
}
impl<'a> Context<'a> {
    fn new(l: &'a mut Lowerer, n: &'a Node) -> Self {
        Self {
            l,
            n,
            values: n.inputs.clone(),
            error: None,
            attention: None,
        }
    }
    fn attn(&self) -> &attention::Facts {
        self.attention.as_ref().expect("attention facts")
    }
    fn contract(&self) -> &Attention {
        self.n
            .attributes
            .attention
            .as_ref()
            .expect("attention contract")
    }
    fn mask_shape(&self) -> &[Expr] {
        &self.l.g.values[&self.n.inputs[3]].tensor.shape
    }
    fn name(&self, v: usize) -> String {
        self.values[v].clone()
    }
    fn value(&mut self, f: impl FnOnce(&mut Self) -> Result<String>) -> usize {
        if self.error.is_some() {
            return 0;
        }
        match f(self) {
            Ok(s) => {
                let v = self.values.len();
                self.values.push(s);
                v
            }
            Err(e) => {
                self.error = Some(e);
                0
            }
        }
    }
    fn effect(&mut self, f: impl FnOnce(&mut Self) -> Result<()>) -> u8 {
        if self.error.is_none() {
            if let Err(e) = f(self) {
                self.error = Some(e);
            }
        }
        0
    }
    fn finish_result(self) -> Result<()> {
        self.error.map_or(Ok(()), Err)
    }
    fn weight(&self) -> &TensorType {
        &self.l.g.values[&self.n.inputs[1]].tensor
    }
    fn input_ty(&self) -> &TensorType {
        &self.l.g.values[&self.n.inputs[0]].tensor
    }
    fn output_ty(&self) -> &TensorType {
        &self.l.g.values[&self.n.outputs[0]].tensor
    }
    fn row(&self) -> Option<&super::super::model::QuantizationParameters> {
        self.weight()
            .quant
            .as_ref()
            .and_then(|q| q.parameters.as_ref())
            .filter(|p| self.weight().dtype == Dtype::I8 && p.axes == [0] && p.blocks == [1])
    }
}
impl Lowerer {
    pub(super) fn attention(&mut self, n: &Node) -> Result<()> {
        let facts = attention::Facts::new(&self.g, n)?;
        let mut cx = Context::new(self, n);
        cx.attention = Some(facts);
        generated::constructor_attention(&mut cx);
        cx.finish_result()
    }
    pub(super) fn linear(&mut self, n: &Node) -> Result<()> {
        let weight = self.g.values[&n.inputs[1]].tensor.clone();
        if weight.shape.len() != 2 {
            return Err(Error::invalid("Linear weights require rank two"));
        }
        let _channels = weight.shape[0]
            .literal()
            .ok_or_else(|| Error::invalid("Linear channels require static shape"))?;
        let _width = weight.shape[1]
            .literal()
            .ok_or_else(|| Error::invalid("Linear width requires static shape"))?;

        if n.op != Op::WeightOnlyLinear {
            let row = weight
                .quant
                .as_ref()
                .and_then(|q| q.parameters.as_ref())
                .filter(|p| weight.dtype == Dtype::I8 && p.axes == [0] && p.blocks == [1]);
            if let Some(p) = row {
                let z = &self.g.values[&p.zeros];
                if !z.constant || z.integers.is_empty() || z.integers.iter().any(|x| *x != 0) {
                    return Err(Error::invalid(
                        "Per-row hybrid FC requires known symmetric zero",
                    ));
                }
            }
        }
        let mut cx = Context::new(self, n);
        generated::constructor_linear(&mut cx);
        cx.finish_result()
    }
    pub(super) fn softmax(&mut self, n: &Node) -> Result<()> {
        let mut cx = Context::new(self, n);
        generated::constructor_softmax(&mut cx, 0);
        cx.finish_result()
    }
}
pub(super) fn decode(l: &mut Lowerer, n: &Node) -> Result<()> {
    let mut cx = Context::new(l, n);
    generated::constructor_decode_rows(&mut cx);
    cx.finish_result()
}
impl generated::Context for Context<'_> {
    fn input(&mut self, i: i64) -> usize {
        i as usize
    }
    fn scalar(&mut self, v: i64) -> usize {
        self.value(|cx| Ok(cx.l.f(v as f32)))
    }
    fn unary(&mut self, op: Op, v: usize) -> usize {
        self.value(|cx| cx.l.unary(op, &cx.name(v)))
    }
    fn binary(&mut self, op: Op, x: usize, y: usize) -> usize {
        self.value(|cx| cx.l.binary(op, &cx.name(x), &cx.name(y)))
    }
    fn reduction(&mut self, op: Op, x: usize) -> usize {
        self.value(|cx| cx.l.reduce(op, &cx.name(x), vec![-1], true))
    }
    fn finish(&mut self, x: usize) -> u8 {
        self.effect(|cx| cx.l.copy(&cx.name(x), &cx.n.outputs[0]))
    }
    fn output_mul(&mut self, x: usize, y: usize) -> u8 {
        self.effect(|cx| {
            cx.l.emit(
                Op::Mul,
                &[cx.name(x), cx.name(y)],
                &cx.n.outputs[0],
                Attributes::default(),
            )?;
            Ok(())
        })
    }
    fn weight_only(&mut self) -> u8 {
        (self.n.op == Op::WeightOnlyLinear) as u8
    }
    fn blockwise(&mut self) -> u8 {
        (self.input_ty().quant.is_none()
            && self.output_ty().quant.is_none()
            && self
                .weight()
                .quant
                .as_ref()
                .is_some_and(|q| q.parameters.is_some())
            && self.row().is_none()) as u8
    }
    fn float_linear(&mut self) -> u8 {
        (self.input_ty().quant.is_none()
            && self.output_ty().quant.is_none()
            && self.weight().quant.is_none()) as u8
    }
    fn vector_input(&mut self) -> u8 {
        (self.input_ty().shape.len() == 1) as u8
    }
    fn has_bias(&mut self) -> u8 {
        (self.n.inputs.len() == 3) as u8
    }
    fn static_input(&mut self) -> u8 {
        self.input_ty().quant.is_some() as u8
    }
    fn quant_output(&mut self) -> u8 {
        self.output_ty().quant.is_some() as u8
    }
    fn native_weight_only(&mut self) -> u8 {
        self.effect(|cx| {
            let n = cx.n;
            let x = &n.inputs[0];
            let w = &n.inputs[1];
            let y = &n.outputs[0];
            let weight = cx.weight().clone();
            let channels = weight.shape[0].literal().unwrap();
            let width = weight.shape[1].literal().unwrap();
            let q = weight
                .quant
                .as_ref()
                .ok_or_else(|| Error::invalid("Weight-only linear requires quantization"))?;
            let (scale, zero, group) = if let Some(p) = &q.parameters {
                if p.blocks.len() != 2 {
                    return Err(Error::invalid("Weight-only parameter geometry"));
                }
                (p.scales.clone(), p.zeros.clone(), p.blocks[1])
            } else {
                let s = cx.l.g.literal(
                    "__ynn/weight_scale",
                    &q.scales.iter().map(|x| x.get() as f32).collect::<Vec<_>>(),
                );
                cx.l.g.values.get_mut(&s).unwrap().tensor.shape =
                    vec![Expr::Known(channels), Expr::Known(1)];
                let z =
                    cx.l.g
                        .integer("__ynn/zero", &[0], vec![Expr::Known(1), Expr::Known(1)]);
                (s, z, width)
            };
            cx.l.emit(
                NativeWeightOnlyLinear,
                &[x.clone(), w.clone(), scale, zero],
                y,
                Attributes {
                    integers: vec![group],
                    ..n.attributes.clone()
                },
            )?;
            Ok(())
        })
    }
    fn native_blockwise(&mut self) -> u8 {
        self.effect(|cx| {
            let n = cx.n;
            let x = &n.inputs[0];
            let w = &n.inputs[1];
            let y = &n.outputs[0];
            let weight = cx.weight().clone();
            let width = weight.shape[1].literal().unwrap();
            let p = weight.quant.as_ref().unwrap().parameters.as_ref().unwrap();
            if weight.dtype != Dtype::I4 || p.blocks != [1, 32] || width % 32 != 0 {
                return Err(Error::invalid(
                    "Grouped hybrid FC requires INT4 groups of 32",
                ));
            }
            cx.l.emit(
                Op::BlockwiseFullyConnected,
                &[x.clone(), w.clone(), p.scales.clone(), p.zeros.clone()],
                y,
                Attributes {
                    integers: vec![32],
                    ..Attributes::default()
                },
            )?;
            Ok(())
        })
    }
    fn weight_transpose(&mut self, x: usize) -> usize {
        self.value(|cx| {
            cx.l.temp(
                Transpose,
                &[cx.name(x)],
                "weight_transpose",
                Attributes {
                    integers: vec![1, 0],
                    ..Attributes::default()
                },
            )
        })
    }
    fn matrix_input(&mut self, x: usize) -> usize {
        self.value(|cx| {
            cx.l.temp(
                Reshape,
                &[cx.name(x)],
                "matrix_input",
                Attributes {
                    shape: vec![Expr::Known(1), cx.input_ty().shape[0].clone()],
                    ..Attributes::default()
                },
            )
        })
    }
    fn vector_output(&mut self, x: usize) -> u8 {
        self.effect(|cx| {
            cx.l.emit(
                Reshape,
                &[cx.name(x)],
                &cx.n.outputs[0],
                Attributes {
                    shape: vec![cx.weight().shape[0].clone()],
                    ..Attributes::default()
                },
            )?;
            Ok(())
        })
    }
    fn weight_scale(&mut self) -> usize {
        self.value(|cx| {
            let n = cx.n;
            let input = cx.input_ty().clone();
            let output = cx.output_ty().clone();
            let weight = cx.weight().clone();
            let channels = weight.shape[0].literal().unwrap();
            let row = weight
                .quant
                .as_ref()
                .and_then(|q| q.parameters.as_ref())
                .filter(|p| weight.dtype == Dtype::I8 && p.axes == [0] && p.blocks == [1]);
            if n.inputs.len() != 2 {
                return Err(Error::invalid("Quantized FC bias lowering unsupported"));
            }
            let q = weight
                .quant
                .as_ref()
                .ok_or_else(|| Error::invalid("Hybrid FC requires quantized weights"))?;
            if q.blockwise
                || (row.is_none() && (q.axis != 0 || q.parameters.is_some()))
                || q.zeros.iter().any(|x| *x != 0)
            {
                return Err(Error::invalid(
                    "FC requires symmetric per-output-channel weights",
                ));
            }
            for q in [&input.quant, &output.quant].into_iter().flatten() {
                if q.scales.len() != 1
                    || q.zeros != [0]
                    || !q.scales[0].get().is_finite()
                    || q.scales[0].get() <= 0.0
                {
                    return Err(Error::invalid(
                        "FC requires symmetric per-tensor activation scales",
                    ));
                }
            }
            let ws = if let Some(p) = row {
                p.scales.clone()
            } else {
                if q.scales.len() != 1 && q.scales.len() != channels as usize {
                    return Err(Error::invalid("FC channel scale count"));
                }
                cx.l.g.literal(
                    "__ynn/weight_scale",
                    &q.scales.iter().map(|x| x.get() as f32).collect::<Vec<_>>(),
                )
            };
            Ok(ws)
        })
    }
    fn zero(&mut self) -> usize {
        self.value(|cx| Ok(cx.l.g.integer("__ynn/zero", &[0], vec![Expr::Known(1)])))
    }
    fn static_scale(&mut self) -> usize {
        self.value(|cx| {
            let scales = cx
                .input_ty()
                .quant
                .as_ref()
                .unwrap()
                .scales
                .iter()
                .map(|x| x.get() as f32)
                .collect::<Vec<_>>();
            Ok(cx.l.g.literal("__ynn/input_scale", &scales))
        })
    }
    fn fresh_zero(&mut self) -> usize {
        self.value(|cx| Ok(cx.l.value("input_zero")))
    }
    fn fresh_scale(&mut self) -> usize {
        self.value(|cx| Ok(cx.l.value("input_scale")))
    }
    fn dynamic_parameters(&mut self, mm: usize, az: usize, scale: usize) -> u8 {
        self.effect(|cx| {
            cx.l.g.emit(Node {
                op: DynamicQuantization,
                inputs: vec![cx.name(mm)],
                outputs: vec![cx.name(az), cx.name(scale)],
                scope: cx.l.scope.clone(),
                attributes: Attributes::default(),
                waits: vec![],
                completes: vec![],
            })
        })
    }
    fn quantize_input(&mut self, x: usize, az: usize, scale: usize) -> usize {
        self.value(|cx| {
            cx.l.temp(
                QuantizeTensor,
                &[cx.name(x), cx.name(az), cx.name(scale)],
                "input_codes",
                Attributes {
                    result_dtype: Some(Dtype::I8),
                    ..Attributes::default()
                },
            )
        })
    }
    fn accumulator_scale(&mut self, a: usize, b: usize) -> usize {
        self.value(|cx| {
            cx.l.temp(
                Mul,
                &[cx.name(a), cx.name(b)],
                "accumulator_scale",
                Attributes {
                    fold_constants: false,
                    result_dtype: Some(Dtype::F32),
                    ..Attributes::default()
                },
            )
        })
    }
    fn weight_sum(&mut self, w: usize) -> usize {
        self.value(|cx| {
            cx.l.temp(
                ReduceSum,
                &[cx.name(w)],
                "weight_sum",
                Attributes {
                    axes: vec![0],
                    keep_dims: true,
                    result_dtype: Some(Dtype::I32),
                    ..Attributes::default()
                },
            )
        })
    }
    fn correction(&mut self, a: usize, b: usize) -> usize {
        self.value(|cx| {
            cx.l.temp(
                Mul,
                &[cx.name(a), cx.name(b)],
                "correction",
                Attributes {
                    result_dtype: Some(Dtype::I32),
                    ..Attributes::default()
                },
            )
        })
    }
    fn dot(&mut self, x: usize, w: usize) -> usize {
        self.value(|cx| {
            cx.l.temp(
                Dot,
                &[cx.name(x), cx.name(w)],
                "accumulator",
                Attributes {
                    result_dtype: Some(Dtype::I32),
                    ..Attributes::default()
                },
            )
        })
    }
    fn biased_dot(&mut self, x: usize, w: usize, b: usize) -> usize {
        self.value(|cx| {
            cx.l.temp(
                Dot,
                &[cx.name(x), cx.name(w), cx.name(b)],
                "accumulator",
                Attributes {
                    result_dtype: Some(Dtype::I32),
                    ..Attributes::default()
                },
            )
        })
    }
    fn dequantize(&mut self, x: usize, s: usize) -> usize {
        self.value(|cx| {
            cx.l.temp(
                DequantizeTensor,
                &[cx.name(x), cx.name(s)],
                "float",
                Attributes {
                    result_dtype: Some(Dtype::F32),
                    ..Attributes::default()
                },
            )
        })
    }
    fn quantize_output(&mut self, x: usize, z: usize) -> u8 {
        self.effect(|cx| {
            let output = cx.output_ty().clone();
            let scales = output
                .quant
                .as_ref()
                .unwrap()
                .scales
                .iter()
                .map(|x| x.get() as f32)
                .collect::<Vec<_>>();
            let s = cx.l.g.literal("__ynn/output_scale", &scales);
            cx.l.emit(
                QuantizeTensor,
                &[cx.name(x), cx.name(z), s],
                &cx.n.outputs[0],
                Attributes {
                    result_dtype: Some(output.dtype),
                    ..Attributes::default()
                },
            )?;
            Ok(())
        })
    }
    fn beta_is_one(&mut self) -> u8 {
        (self.n.attributes.beta.get() as f32 == 1.0) as u8
    }
    fn beta(&mut self) -> usize {
        self.value(|cx| Ok(cx.l.f(cx.n.attributes.beta.get() as f32)))
    }

    fn keep_node(&mut self) -> u8 {
        self.effect(|cx| {
            cx.l.g.nodes.push(cx.n.clone());
            Ok(())
        })
    }
    fn decode_eligible(&mut self) -> u8 {
        let n = self.n;
        let g = &self.l.g;
        if n.op != Matmul
            || n.attributes.adj_x
            || n.inputs.len() != 2
            || n.outputs.len() != 1
            || !n.waits.is_empty()
            || !n.completes.is_empty()
        {
            return 0;
        }
        let a = &g.values[&n.inputs[0]].tensor;
        let b = &g.values[&n.inputs[1]].tensor;
        let out = &g.values[&n.outputs[0]].tensor;
        ([a, b, out]
            .iter()
            .all(|t| t.dtype == Dtype::F32 && t.quant.is_none() && t.shape.len() == 4)
            && a.shape[2] == Expr::Known(1)
            && b.shape[1] == Expr::Known(1)
            && a.shape[1].literal().is_some_and(|h| h > 1)) as u8
    }
    fn decode_reshape(&mut self, x: usize) -> usize {
        self.value(|cx| {
            let mut shape = cx.l.g.values[&cx.name(x)].tensor.shape.clone();
            shape.swap(1, 2);
            let row = cx.l.g.fresh(&(cx.n.outputs[0].clone() + "/rows"));
            cx.l.g.emit(Node {
                op: Reshape,
                inputs: vec![cx.name(x)],
                outputs: vec![row.clone()],
                attributes: Attributes {
                    shape,
                    ..Attributes::default()
                },
                ..cx.n.clone()
            })?;
            Ok(row)
        })
    }
    fn decode_dot(&mut self, x: usize, y: usize) -> usize {
        self.value(|cx| {
            let dot = cx.l.g.fresh(&(cx.n.outputs[0].clone() + "/dot"));
            cx.l.g.emit(Node {
                inputs: vec![cx.name(x), cx.name(y)],
                outputs: vec![dot.clone()],
                ..cx.n.clone()
            })?;
            Ok(dot)
        })
    }
    fn decode_result(&mut self, x: usize) -> u8 {
        self.effect(|cx| {
            let shape = cx.l.g.values[&cx.n.outputs[0]].tensor.shape.clone();
            cx.l.g.emit(Node {
                op: Reshape,
                inputs: vec![cx.name(x)],
                attributes: Attributes {
                    shape,
                    ..Attributes::default()
                },
                ..cx.n.clone()
            })
        })
    }

    fn attention_eligible(&mut self) -> u8 {
        self.attn().eligible as u8
    }
    fn head_group(&mut self) -> i64 {
        self.attn().group
    }
    fn multiple_heads(&mut self) -> u8 {
        (self.attn().group > 1) as u8
    }
    fn small_query(&mut self) -> u8 {
        self.attn().small as u8
    }
    fn grouped_scores(&mut self) -> u8 {
        self.attn().grouped as u8
    }
    fn has_mask(&mut self) -> u8 {
        (self.contract().mask != 0) as u8
    }
    fn boolean_mask(&mut self) -> u8 {
        (self.contract().mask == 1) as u8
    }
    fn causal(&mut self) -> u8 {
        self.contract().causal as u8
    }
    fn mask_expand(&mut self) -> u8 {
        let s = self.mask_shape();
        (s.len() == 4 && s[1].literal() == Some(1)) as u8
    }
    fn mask_split(&mut self) -> u8 {
        let s = self.mask_shape();
        (s.len() >= 3 && s[s.len() - 3].literal().is_some_and(|v| v != 1)) as u8
    }
    fn value_transposed(&mut self) -> u8 {
        self.attn().transposed_value as u8
    }
    fn mask_needs_slice(&mut self) -> u8 {
        let s = self.mask_shape();
        (s.len() >= 3 && s[s.len() - 3] != Expr::Known(1)) as u8
    }
    fn attention_scale(&mut self) -> usize {
        self.value(|cx| Ok(cx.l.f(cx.contract().scale.get() as f32)))
    }
    fn split_heads(&mut self, x: usize) -> usize {
        self.value(|cx| {
            cx.l.temp(
                SplitDim,
                &[cx.name(x)],
                "groups",
                Attributes {
                    axis: 1,
                    shape: vec![cx.attn().key[1].clone(), Expr::Known(cx.attn().group)],
                    ..Attributes::default()
                },
            )
        })
    }
    fn fuse_group_rows(&mut self, x: usize) -> usize {
        self.value(|cx| {
            cx.l.temp(
                FuseDims,
                &[cx.name(x)],
                "group_rows",
                Attributes {
                    axis: 2,
                    integers: vec![2],
                    ..Attributes::default()
                },
            )
        })
    }
    fn split_head_rows(&mut self, x: usize) -> usize {
        self.value(|cx| {
            cx.l.temp(
                SplitDim,
                &[cx.name(x)],
                "head_rows",
                Attributes {
                    axis: 2,
                    shape: vec![Expr::Known(cx.attn().group), cx.attn().query[2].clone()],
                    ..Attributes::default()
                },
            )
        })
    }
    fn fuse_heads(&mut self, x: usize) -> usize {
        self.value(|cx| {
            cx.l.temp(
                FuseDims,
                &[cx.name(x)],
                "heads",
                Attributes {
                    axis: 1,
                    integers: vec![2],
                    ..Attributes::default()
                },
            )
        })
    }
    fn transpose_attention(&mut self, x: usize) -> usize {
        self.value(|cx| {
            cx.l.temp(
                Transpose,
                &[cx.name(x)],
                "transpose",
                Attributes {
                    integers: vec![0, 1, 3, 2],
                    ..Attributes::default()
                },
            )
        })
    }
    fn expand_attention(&mut self, x: usize) -> usize {
        self.value(|cx| {
            cx.l.temp(
                ExpandDims,
                &[cx.name(x)],
                "expand",
                Attributes {
                    axes: vec![2],
                    ..Attributes::default()
                },
            )
        })
    }
    fn attention_dot(&mut self, x: usize, y: usize, adj: u8) -> usize {
        self.value(|cx| {
            cx.l.temp(
                Matmul,
                &[cx.name(x), cx.name(y)],
                "dot",
                Attributes {
                    adj_y: adj != 0,
                    ..Attributes::default()
                },
            )
        })
    }
    fn split_mask(&mut self, x: usize) -> usize {
        self.value(|cx| {
            cx.l.temp(
                SplitDim,
                &[cx.name(x)],
                "mask_groups",
                Attributes {
                    axis: (cx.mask_shape().len() - 3) as i64,
                    shape: vec![cx.attn().key[1].clone(), Expr::Known(cx.attn().group)],
                    ..Attributes::default()
                },
            )
        })
    }
    fn attention_value(&mut self) -> usize {
        self.value(|cx| Ok(cx.attn().value_source.clone()))
    }
    fn negative_infinity(&mut self) -> usize {
        self.value(|cx| Ok(cx.l.f(f32::NEG_INFINITY)))
    }
    fn select_mask(&mut self, m: usize, x: usize, z: usize) -> usize {
        self.value(|cx| {
            cx.l.temp(
                Select,
                &[cx.name(m), cx.name(x), cx.name(z)],
                "masked",
                Attributes::default(),
            )
        })
    }
    fn causal_mask(&mut self, x: usize) -> usize {
        self.value(|cx| {
            cx.l.temp(
                CausalMask,
                &[cx.name(x)],
                "causal",
                Attributes {
                    position: cx.contract().query_position.clone(),
                    begin: cx.contract().key_position.clone(),
                    window: cx.contract().window,
                    ..Attributes::default()
                },
            )
        })
    }
    fn probabilities(&mut self, x: usize) -> usize {
        self.value(|cx| {
            let out = cx.l.value("probabilities");
            cx.l.softmax(&Node {
                op: Softmax,
                inputs: vec![cx.name(x)],
                outputs: vec![out.clone()],
                attributes: Attributes::default(),
                waits: vec![],
                completes: vec![],
                scope: cx.l.scope.clone(),
            })?;
            Ok(out)
        })
    }
    fn slice_all(&mut self, scale: usize) -> u8 {
        self.effect(|cx| {
            let heads = cx.contract().heads.clone();
            let mut contexts = vec![];
            let mut head = 0;
            while head < heads.len() {
                let first = head;
                let kv = heads[head];
                while head < heads.len() && heads[head] == kv {
                    head += 1;
                }
                let v = generated::constructor_attention_slice(
                    cx,
                    first as i64,
                    (head - first) as i64,
                    kv,
                    scale,
                );
                if let Some(e) = cx.error.take() {
                    return Err(e);
                }
                contexts.push(cx.name(v));
            }
            cx.l.emit(
                Concat,
                &contexts,
                &cx.n.outputs[0],
                Attributes {
                    axis: 1,
                    ..Attributes::default()
                },
            )?;
            Ok(())
        })
    }
    fn slice_input(&mut self, index: i64, start: i64, count: i64) -> usize {
        self.value(|cx| {
            let input = cx.n.inputs[index as usize].clone();
            let mut shape = cx.l.g.shape(&input)?;
            shape[1] = Expr::Known(count);
            let mut starts = vec![Expr::Known(0); 4];
            starts[1] = Expr::Known(start);
            cx.l.temp(
                Slice,
                &[input],
                "head_slice",
                Attributes {
                    starts,
                    lengths: shape,
                    ..Attributes::default()
                },
            )
        })
    }
    fn head_mask(&mut self, start: i64, count: i64) -> usize {
        self.value(|cx| {
            let m = cx.n.inputs[3].clone();
            let mut shape = cx.l.g.shape(&m)?;
            let ax = shape.len() - 3;
            let mut starts = vec![Expr::Known(0); shape.len()];
            starts[ax] = Expr::Known(start);
            shape[ax] = Expr::Known(count);
            cx.l.temp(
                Slice,
                &[m],
                "mask_slice",
                Attributes {
                    starts,
                    lengths: shape,
                    ..Attributes::default()
                },
            )
        })
    }
}
