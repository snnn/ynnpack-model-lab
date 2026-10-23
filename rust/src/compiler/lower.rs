// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
use super::model::*;
use crate::{Error, Result};
use std::collections::BTreeSet;
mod attention;
mod constants;
mod optimize;
mod regions;
mod rules;
struct Lowerer {
    g: Graph,
    scope: String,
    counter: usize,
}
impl Lowerer {
    fn value(&mut self, base: &str) -> String {
        self.counter += 1;
        self.g.fresh(&format!("__ynn/{}/{base}", self.counter))
    }
    fn emit(&mut self, op: Op, inputs: &[String], output: &str, a: Attributes) -> Result<String> {
        let n = Node {
            op,
            inputs: inputs.into(),
            outputs: vec![output.into()],
            attributes: a,
            waits: vec![],
            completes: vec![],
            scope: self.scope.clone(),
        };
        self.g.emit(n)?;
        Ok(output.into())
    }
    fn temp(&mut self, op: Op, inputs: &[String], base: &str, a: Attributes) -> Result<String> {
        let out = self.value(base);
        self.emit(op, inputs, &out, a)
    }
    fn f(&mut self, x: f32) -> String {
        self.g.literal("__ynn/constant", &[x])
    }
    fn unary(&mut self, op: Op, x: &str) -> Result<String> {
        self.temp(op, &[x.into()], &op.name(), Attributes::default())
    }
    fn binary(&mut self, op: Op, x: &str, y: &str) -> Result<String> {
        self.temp(op, &[x.into(), y.into()], &op.name(), Attributes::default())
    }
    fn copy(&mut self, x: &str, y: &str) -> Result<()> {
        if x.starts_with("__ynn/")
            && !self.g.outputs.iter().any(|v| v == x)
            && !self.g.nodes.iter().any(|n| n.inputs.iter().any(|v| v == x))
        {
            if let Some(i) = self.g.nodes.iter().rposition(|n| {
                n.outputs == [x.to_string()] && n.waits.is_empty() && n.completes.is_empty()
            }) {
                self.g.nodes[i].outputs = vec![y.into()];
                if !self.g.values.contains_key(y) {
                    let v = self.g.values[x].clone();
                    self.g.values.insert(y.into(), v);
                }
                self.g.values.remove(x);
                return Ok(());
            }
        }
        self.emit(Op::Copy, &[x.into()], y, Attributes::default())?;
        Ok(())
    }
    fn reduce(&mut self, op: Op, x: &str, axes: Vec<i64>, keep_dims: bool) -> Result<String> {
        self.temp(
            op,
            &[x.into()],
            &op.name(),
            Attributes {
                axes,
                keep_dims,
                ..Attributes::default()
            },
        )
    }
    fn activation(&mut self, n: &Node) -> Result<()> {
        use Op::*;
        let x = &n.inputs[0];
        let y = &n.outputs[0];
        let a = &n.attributes;
        if self.g.values[x].tensor.dtype != Dtype::F32 {
            return Err(Error::invalid("Extended activation requires FP32"));
        }
        let out = match n.op {
            Relu | Relu6 | ReluN1To1 | Relu0To1 => {
                let lo = self.f(if n.op == ReluN1To1 { -1.0 } else { 0.0 });
                let pos = self.binary(Maximum, x, &lo)?;
                if n.op == Relu {
                    pos
                } else {
                    let hi = self.f(if n.op == Relu6 { 6.0 } else { 1.0 });
                    self.binary(Minimum, &pos, &hi)?
                }
            }
            LeakyRelu => {
                if !(a.beta.get() as f32).is_finite() {
                    return Err(Error::invalid("Leaky-ReLU coefficient exceeds FP32"));
                }
                let alpha = self.f(a.beta.get() as f32);
                self.binary(Prelu, x, &alpha)?
            }
            Elu => {
                let z = self.f(0.0);
                let one = self.f(1.0);
                let neg = self.binary(Minimum, x, &z)?;
                let exp = self.unary(Exp, &neg)?;
                let off = self.binary(Sub, &exp, &one)?;
                let pos = self.binary(Maximum, x, &z)?;
                self.binary(Add, &pos, &off)?
            }
            L2Normalization => {
                let sq = self.unary(Square, x)?;
                let sum = self.reduce(ReduceSum, &sq, vec![-1], true)?;
                let half = self.f(0.5);
                let norm = self.binary(Pow, &sum, &half)?;
                let eps = self.f(1e-6);
                let denom = self.binary(Maximum, &norm, &eps)?;
                self.binary(Div, x, &denom)?
            }
            L2NormEpsilon => {
                let sq = self.unary(Square, x)?;
                let sum = self.reduce(ReduceSum, &sq, a.axes.clone(), true)?;
                let eps = self.f(a.beta.get() as f32);
                let adjusted = self.binary(Add, &sum, &eps)?;
                let inv = self.unary(Rsqrt, &adjusted)?;
                self.binary(Mul, x, &inv)?
            }
            Gelu => {
                let half = self.f(0.5);
                if a.approximate {
                    let c = (2.0 / std::f64::consts::PI).sqrt();
                    let p = self.temp(
                        Polynomial,
                        &[x.clone()],
                        "polynomial",
                        Attributes {
                            coefficients: vec![
                                0.0.into(),
                                c.into(),
                                0.0.into(),
                                (c * 0.044715).into(),
                            ],
                            ..Attributes::default()
                        },
                    )?;
                    let t = self.unary(Tanh, &p)?;
                    let one = self.f(1.0);
                    let factor = self.binary(Add, &t, &one)?;
                    let h = self.binary(Mul, x, &half)?;
                    self.binary(Mul, &h, &factor)?
                } else {
                    let c = self.f(2f32.sqrt() / 2.0);
                    let s = self.binary(Mul, x, &c)?;
                    let e = self.unary(Erf, &s)?;
                    let h = self.binary(Mul, &e, &half)?;
                    let f = self.binary(Add, &h, &half)?;
                    self.binary(Mul, x, &f)?
                }
            }
            _ => unreachable!(),
        };
        self.copy(&out, y)
    }

}
pub(super) fn lower(source: &Graph, options: &CompileOptions) -> Result<Graph> {
    lower_graph(source, options, false)
}
fn lower_graph(source: &Graph, options: &CompileOptions, function: bool) -> Result<Graph> {
    let mut fused = source.clone();
    regions::causal_conv(&mut fused);
    let source = &fused;
    let mut l = Lowerer {
        g: source.clone(),
        scope: String::new(),
        counter: 0,
    };
    l.g.nodes.clear();
    for (name, body) in &source.functions {
        l.g.functions
            .insert(name.clone(), lower_graph(body, options, true)?);
    }
    let mut completion_names: BTreeSet<String> = source
        .values
        .keys()
        .cloned()
        .chain(
            source
                .nodes
                .iter()
                .flat_map(|n| n.completes.iter().cloned()),
        )
        .collect();
    for (operation, n) in source.nodes.iter().enumerate() {
        l.scope = n.scope.clone();
        let first = l.g.nodes.len();
        use Op::*;
        match n.op {
            Softmax => l.softmax(n)?,
            FullyConnected | WeightOnlyLinear => l.linear(n)?,
            Relu | Relu6 | ReluN1To1 | Relu0To1 | LeakyRelu | Elu | L2Normalization
            | L2NormEpsilon | Gelu => l.activation(n)?,
            Sdpa => l.attention(n)?,
            Mean => {
                let mut axes = n.attributes.axes.clone();
                if axes.is_empty() && n.inputs.len() > 1 {
                    axes = l.g.values[&n.inputs[1]].integers.clone();
                }
                if axes.is_empty() {
                    l.copy(&n.inputs[0], &n.outputs[0])?;
                } else {
                    let sum = l.reduce(
                        ReduceSum,
                        &n.inputs[0],
                        axes.clone(),
                        n.attributes.keep_dims,
                    )?;
                    let shape = l.temp(
                        GetShape,
                        &[n.inputs[0].clone()],
                        "divisor",
                        Attributes {
                            axes,
                            ..Attributes::default()
                        },
                    )?;
                    l.emit(Div, &[sum, shape], &n.outputs[0], Attributes::default())?;
                }
            }
            Split => {
                let shape = l.g.shape(&n.inputs[0])?;
                let ax = axis(n.attributes.axis, shape.len())?;
                let mut begin = Expr::Known(0);
                for (i, y) in n.outputs.iter().enumerate() {
                    let mut starts = vec![Expr::Known(0); shape.len()];
                    starts[ax] = begin.clone();
                    let mut lengths = shape.clone();
                    lengths[ax] = n.attributes.lengths[i].clone();
                    l.emit(
                        Slice,
                        &n.inputs,
                        y,
                        Attributes {
                            starts,
                            lengths,
                            ..Attributes::default()
                        },
                    )?;
                    begin = Expr::sum([begin, n.attributes.lengths[i].clone()]);
                }
            }
            Copy if n.outputs.len() > 1 => {
                for (x, y) in n.inputs.iter().zip(&n.outputs) {
                    l.copy(x, y)?;
                }
            }
            _ => {
                l.g.nodes.push(n.clone());
            }
        }
        if !n.waits.is_empty() || !n.completes.is_empty() {
            let end = l.g.nodes.len();
            if end == first {
                return Err(Error::invalid("Completion lost during lowering"));
            }
            let mut branches = vec![];
            for i in first..end {
                let step = &mut l.g.nodes[i];
                step.waits = n.waits.clone();
                step.completes.clear();
                if i + 1 == end {
                    step.waits.extend(branches.clone());
                    step.completes = n.completes.clone();
                } else if !n.completes.is_empty() {
                    let mut token = format!("__ynn/completion/{operation}/{}", i - first);
                    while !completion_names.insert(token.clone()) {
                        token.push('_');
                    }
                    step.completes.push(token.clone());
                    branches.push(token);
                }
            }
        }
    }
    if options.group_decode_rows {
        regions::decode_rows(&mut l.g)?;
    }
    constants::fold(&mut l.g);
    let mut result = optimize::run(l.g, options, function)?;
    if let Some(keep) = &options.keep_views {
        if keep != "fuse" && keep != "split" {
            return Err(Error::invalid("Unknown view ablation"));
        }
        for n in &mut result.nodes {
            if (keep == "fuse" && n.op == Op::SplitDim) || (keep == "split" && n.op == Op::FuseDims)
            {
                n.op = Op::Reshape;
                n.attributes = Attributes {
                    shape: result.values[&n.outputs[0]].tensor.shape.clone(),
                    ..Attributes::default()
                };
            }
        }
    }
    if function {
        for i in 0..result.outputs.len() {
            let old = result.outputs[i].clone();
            if result.inputs.contains(&old) || result.values[&old].constant {
                let new = result.fresh(&format!("{old}/result"));
                let mut value = result.values[&old].clone();
                value.constant = false;
                value.data = None;
                value.floats.clear();
                value.integers.clear();
                result.values.insert(new.clone(), value);
                result.nodes.push(Node {
                    op: Op::Copy,
                    inputs: vec![old],
                    outputs: vec![new.clone()],
                    attributes: Attributes::default(),
                    waits: vec![],
                    completes: vec![],
                    scope: String::new(),
                });
                result.outputs[i] = new;
            }
        }
    }
    Ok(result)
}
