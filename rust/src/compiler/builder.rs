// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
use super::model::*;
use crate::{Error, Result};
use std::collections::BTreeSet;

/// A model author supplies semantics; no native construction commands are exposed.
#[derive(Default)]
pub struct GraphBuilder {
    pub graph: Graph,
}
impl GraphBuilder {
    /// Outline an explicitly authored region. Constants remain immutable captures;
    /// the compiler later lifts them into shared native construction templates.
    /// Resource successors must be listed among the region's results.
    pub fn outline(
        &mut self,
        first: usize,
        results: &[String],
        name: &str,
        scope: &str,
    ) -> Result<()> {
        if first >= self.graph.nodes.len() || self.graph.functions.contains_key(name) {
            return Err(Error::invalid("Invalid function region"));
        }
        let nodes = self.graph.nodes[first..].to_vec();
        if nodes
            .iter()
            .any(|n| !n.waits.is_empty() || !n.completes.is_empty())
        {
            return Err(Error::invalid(
                "Outline completion-bearing regions with an explicit function contract",
            ));
        }
        let produced = nodes
            .iter()
            .flat_map(|n| n.outputs.iter().cloned())
            .collect::<BTreeSet<_>>();
        let mut inputs = vec![];
        let mut needed = produced.clone();
        for n in &nodes {
            for x in &n.inputs {
                if x.is_empty() {
                    continue;
                }
                needed.insert(x.clone());
                if !produced.contains(x) && !self.graph.values[x].constant && !inputs.contains(x) {
                    inputs.push(x.clone());
                }
            }
        }
        loop {
            let count = needed.len();
            for n in needed.clone() {
                if let Some(p) = self.graph.values[&n]
                    .tensor
                    .quant
                    .as_ref()
                    .and_then(|q| q.parameters.as_ref())
                {
                    needed.insert(p.scales.clone());
                    needed.insert(p.zeros.clone());
                }
            }
            if needed.len() == count {
                break;
            }
        }
        for n in &needed {
            if !produced.contains(n) && !self.graph.values[n].constant && !inputs.contains(n) {
                inputs.push(n.clone());
            }
        }
        if results.iter().any(|x| !needed.contains(x)) {
            return Err(Error::invalid("Unknown function result"));
        }
        let mut body = Graph {
            values: self
                .graph
                .values
                .iter()
                .filter(|(n, _)| needed.contains(*n))
                .map(|(n, v)| (n.clone(), v.clone()))
                .collect(),
            inputs: inputs.clone(),
            outputs: results.into(),
            nodes,
            symbols: self.graph.symbols.clone(),
            guards: self.graph.guards.clone(),
            resources: self
                .graph
                .resources
                .iter()
                .filter(|r| inputs.contains(&r.owner))
                .cloned()
                .collect(),
            ..Graph::default()
        };
        for n in &mut body.nodes {
            n.scope = n
                .scope
                .strip_prefix(scope)
                .unwrap_or(&n.scope)
                .trim_start_matches('/')
                .into();
        }
        for n in &body.nodes {
            if let Some(c) = &n.attributes.call {
                body.functions.insert(
                    c.function.clone(),
                    self.graph.functions[&c.function].clone(),
                );
            }
        }
        let indices = body
            .symbols
            .iter()
            .map(|s| (s.id, Expr::Symbol(s.id)))
            .collect();
        self.graph.nodes.truncate(first);
        self.graph.nodes.push(Node {
            op: Op::Call,
            inputs,
            outputs: results.into(),
            attributes: Attributes {
                call: Some(Call {
                    function: name.into(),
                    indices,
                }),
                ..Attributes::default()
            },
            scope: scope.into(),
            waits: vec![],
            completes: vec![],
        });
        self.graph.functions.insert(name.into(), body);
        Ok(())
    }
    pub fn input(&mut self, name: &str, tensor: TensorType) -> Result<String> {
        self.value(
            name,
            Value {
                tensor,
                ..Value::default()
            },
        )?;
        self.graph.inputs.push(name.into());
        Ok(name.into())
    }
    pub fn constant(&mut self, name: &str, tensor: TensorType, data: Asset) -> Result<String> {
        self.value(
            name,
            Value {
                tensor,
                data: Some(data),
                constant: true,
                ..Value::default()
            },
        )?;
        Ok(name.into())
    }
    pub fn value(&mut self, name: &str, value: Value) -> Result<()> {
        if self.graph.values.contains_key(name) {
            return Err(Error::invalid("Duplicate value"));
        }
        self.graph.values.insert(name.into(), value);
        Ok(())
    }
    pub fn operation(
        &mut self,
        op: Op,
        inputs: &[&str],
        output: &str,
        attributes: Attributes,
    ) -> Result<String> {
        let n = Node {
            op,
            inputs: inputs.iter().map(|s| s.to_string()).collect(),
            outputs: vec![output.into()],
            attributes,
            waits: vec![],
            completes: vec![],
            scope: String::new(),
        };
        self.graph.emit(n)?;
        Ok(output.into())
    }
    pub fn finish(mut self, outputs: &[&str]) -> Graph {
        self.graph.outputs = outputs.iter().map(|x| x.to_string()).collect();
        self.graph
    }
}
#[derive(Default)]
pub struct ProgramBuilder {
    program: Program,
}
impl ProgramBuilder {
    pub fn phase(&mut self, name: &str, graph: Graph) -> Result<()> {
        if self.program.phases.contains_key(name) {
            return Err(Error::invalid("Duplicate phase"));
        }
        self.program.phases.insert(name.into(), graph);
        Ok(())
    }
    pub fn finish(self) -> Program {
        self.program
    }
}
fn broadcast(a: &[Expr], b: &[Expr]) -> Result<Vec<Expr>> {
    let rank = a.len().max(b.len());
    let mut out = vec![Expr::Known(1); rank];
    for i in 0..rank {
        let x = a
            .len()
            .checked_sub(i + 1)
            .map(|j| &a[j])
            .cloned()
            .unwrap_or(Expr::Known(1));
        let y = b
            .len()
            .checked_sub(i + 1)
            .map(|j| &b[j])
            .cloned()
            .unwrap_or(Expr::Known(1));
        out[rank - 1 - i] = if x == y || y == Expr::Known(1) {
            x
        } else if x == Expr::Known(1) {
            y
        } else if x.literal().is_some() && y.literal().is_some() {
            return Err(Error::invalid("Incompatible broadcast extents"));
        } else {
            Expr::Max(vec![x, y])
        };
    }
    Ok(out)
}
impl Graph {
    pub(crate) fn shape(&self, name: &str) -> Result<Vec<Expr>> {
        Ok(self
            .values
            .get(name)
            .ok_or_else(|| Error::invalid(format!("Unknown value {name}")))?
            .tensor
            .shape
            .clone())
    }
    pub(crate) fn fresh(&self, base: &str) -> String {
        let mut n = base.to_owned();
        while self.values.contains_key(&n) {
            n.push('_');
        }
        n
    }
    pub(crate) fn literal(&mut self, base: &str, data: &[f32]) -> String {
        let name = self.fresh(base);
        self.values.insert(
            name.clone(),
            Value {
                tensor: TensorType {
                    shape: vec![Expr::Known(data.len() as i64)],
                    ..TensorType::default()
                },
                floats: data.iter().map(|x| (*x as f64).into()).collect(),
                constant: true,
                ..Value::default()
            },
        );
        name
    }
    pub(crate) fn integer(&mut self, base: &str, data: &[i64], shape: Vec<Expr>) -> String {
        let name = self.fresh(base);
        self.values.insert(
            name.clone(),
            Value {
                tensor: TensorType {
                    dtype: Dtype::I32,
                    shape,
                    quant: None,
                },
                integers: data.into(),
                constant: true,
                ..Value::default()
            },
        );
        name
    }
    pub(crate) fn emit(&mut self, node: Node) -> Result<()> {
        super::validate::operands(&node)?;
        for name in &node.inputs {
            if !name.is_empty() && !self.values.contains_key(name) {
                return Err(Error::invalid(format!("Missing operand {name}")));
            }
        }
        let inferred = self.infer(&node)?;
        for (name, ty) in node.outputs.iter().zip(inferred) {
            if let Some(value) = self.values.get(name) {
                if value.tensor.dtype != ty.dtype
                    || value.tensor.shape.len() != ty.shape.len()
                    || value
                        .tensor
                        .shape
                        .iter()
                        .zip(&ty.shape)
                        .any(|(a, b)| matches!((a.literal(),b.literal()),(Some(x),Some(y)) if x!=y))
                {
                    return Err(Error::invalid(format!(
                        "Result contract disagrees with {:?} inference: {name}",
                        node.op
                    )));
                }
            } else {
                self.values.insert(
                    name.clone(),
                    Value {
                        tensor: ty,
                        ..Value::default()
                    },
                );
            }
        }
        self.nodes.push(node);
        Ok(())
    }
    pub(super) fn infer(&self, n: &Node) -> Result<Vec<TensorType>> {
        let a = &n.attributes;
        let mut t = n
            .inputs
            .first()
            .and_then(|x| self.values.get(x))
            .map(|x| x.tensor.clone())
            .unwrap_or_default();
        let get = |i: usize| -> Result<Vec<Expr>> {
            self.shape(
                n.inputs
                    .get(i)
                    .ok_or_else(|| Error::invalid("Missing operand"))?,
            )
        };
        use Op::*;
        match n.op {
            Add | Sub | Mul | Div | Minimum | Maximum | Pow | Prelu | Less | LessEqual
            | Greater | GreaterEqual | Equal | NotEqual => {
                t.shape = broadcast(&get(0)?, &get(1)?)?;
                t.quant = None;
                if matches!(
                    n.op,
                    Less | LessEqual | Greater | GreaterEqual | Equal | NotEqual
                ) {
                    t.dtype = Dtype::Bool;
                }
            }
            Select => {
                t = self.values[&n.inputs[1]].tensor.clone();
                t.shape = broadcast(&get(0)?, &broadcast(&get(1)?, &get(2)?)?)?;
            }
            Matmul | Dot | DynamicMatmul => {
                let (mut x, mut y) = (get(0)?, get(1)?);
                if n.op == DynamicMatmul {
                    let rhs = &self.values[&n.inputs[1]].tensor;
                    let valid_quant = rhs.quant.as_ref().is_some_and(|q| {
                        !q.blockwise
                            && q.parameters.is_none()
                            && q.scales.len() == 1
                            && q.scales[0].get().is_finite()
                            && q.scales[0].get() > 0.0
                            && q.zeros == [0]
                    });
                    if t.dtype != Dtype::F32
                        || t.quant.is_some()
                        || rhs.dtype != Dtype::I8
                        || !valid_quant
                        || a.adj_x
                    {
                        return Err(Error::invalid(
                            "Dynamic matmul requires FP32 lhs and symmetric per-tensor INT8 rhs",
                        ));
                    }
                    if !a.integers.is_empty() {
                        if y.len() != 4
                            || a.integers.len() != 1
                            || a.integers[0] < 0
                            || !y[1].literal().is_some_and(|heads| a.integers[0] < heads)
                        {
                            return Err(Error::invalid("Dynamic matmul RHS head selection bounds"));
                        }
                        y[1] = Expr::Known(1);
                    }
                }
                let k = if n.op == Dot { a.contraction_dims } else { 1 };
                if x.len() < k + 1 || y.len() < k + 1 {
                    return Err(Error::invalid("Invalid contraction rank"));
                }
                let (nx, ny) = (x.len(), y.len());
                if a.adj_x {
                    x.swap(nx - 1, nx - 2);
                }
                if a.adj_y {
                    y.swap(ny - 1, ny - 2);
                }
                t.shape = broadcast(&x[..nx - k - 1], &y[..ny - k - 1])?;
                t.shape.push(x[nx - k - 1].clone());
                t.shape.push(y[ny - 1].clone());
                t.quant = None;
            }
            FullyConnected
            | WeightOnlyLinear
            | NativeWeightOnlyLinear
            | BlockwiseFullyConnected => {
                let w = get(1)?;
                if w.len() != 2 || t.shape.is_empty() {
                    return Err(Error::invalid("Invalid linear rank"));
                }
                *t.shape.last_mut().unwrap() = w[0].clone();
                t.quant = None;
            }
            Reshape => {
                t.shape = if !a.shape.is_empty() {
                    a.shape.clone()
                } else {
                    a.integers.iter().map(|x| Expr::Known(*x)).collect()
                };
            }
            Transpose => {
                let x = get(0)?;
                t.shape = a
                    .integers
                    .iter()
                    .map(|i| {
                        x.get(*i as usize)
                            .cloned()
                            .ok_or_else(|| Error::invalid("Invalid permutation"))
                    })
                    .collect::<Result<_>>()?;
                if let Some(q) = &mut t.quant {
                    if let Some(p) = &mut q.parameters {
                        for x in &mut p.axes {
                            *x = a
                                .integers
                                .iter()
                                .position(|v| v == x)
                                .ok_or_else(|| Error::invalid("Quantized axis missing"))?
                                as i64;
                        }
                    } else {
                        q.axis = a
                            .integers
                            .iter()
                            .position(|x| *x == q.axis)
                            .ok_or_else(|| Error::invalid("Quantized axis missing"))?
                            as i64;
                    }
                }
            }
            Slice => {
                t.shape = a.lengths.clone();
            }
            BroadcastTo => {
                t.shape = a.shape.clone();
            }
            BroadcastLike | SliceLike => {
                let y = get(1)?;
                for d in &a.axes {
                    let i = axis(*d, t.shape.len())?;
                    t.shape[i] = y
                        .get(i)
                        .cloned()
                        .ok_or_else(|| Error::invalid("Reference rank mismatch"))?;
                }
            }
            ExpandDims => {
                let rank = t.shape.len() + a.axes.len();
                let mut axes = a
                    .axes
                    .iter()
                    .map(|x| axis(*x, rank))
                    .collect::<Result<Vec<_>>>()?;
                axes.sort();
                if axes.windows(2).any(|w| w[0] == w[1]) {
                    return Err(Error::invalid("Duplicate inserted axis"));
                }
                for x in axes {
                    t.shape.insert(x, Expr::Known(1));
                }
            }
            Squeeze => {
                let rank = t.shape.len();
                let axes = if a.axes.is_empty() {
                    t.shape
                        .iter()
                        .enumerate()
                        .filter_map(|(i, d)| (*d == Expr::Known(1)).then_some(i))
                        .collect::<BTreeSet<_>>()
                } else {
                    a.axes
                        .iter()
                        .map(|x| axis(*x, rank))
                        .collect::<Result<_>>()?
                };
                t.shape = t
                    .shape
                    .into_iter()
                    .enumerate()
                    .filter_map(|(i, x)| (!axes.contains(&i)).then_some(x))
                    .collect();
            }
            FuseDims => {
                let ax = axis(a.axis, t.shape.len())?;
                let count = *a.integers.first().unwrap_or(&2) as usize;
                if count == 0 || ax + count > t.shape.len() {
                    return Err(Error::invalid("Invalid fuse extent"));
                }
                let p = Expr::product(t.shape[ax..ax + count].to_vec());
                t.shape.splice(ax..ax + count, [p]);
            }
            SplitDim => {
                let ax = axis(a.axis, t.shape.len())?;
                t.shape.splice(ax..ax + 1, a.shape.clone());
            }
            ReduceSum | ReduceMax | ReduceMin | ReduceMinMax | ReduceSumSquared | Mean => {
                let rank = t.shape.len();
                let axes = a
                    .axes
                    .iter()
                    .map(|x| axis(*x, rank))
                    .collect::<Result<BTreeSet<_>>>()?;
                t.shape = t
                    .shape
                    .into_iter()
                    .enumerate()
                    .filter_map(|(i, d)| {
                        if axes.contains(&i) {
                            a.keep_dims.then_some(Expr::Known(1))
                        } else {
                            Some(d)
                        }
                    })
                    .collect();
                if n.op == ReduceMinMax {
                    t.shape.insert(0, Expr::Known(2));
                }
                t.quant = None;
            }
            GetShape => {
                t.shape.clear();
                t.dtype = Dtype::F32;
                t.quant = None;
            }
            DynamicQuantization => {
                if t.shape.first() != Some(&Expr::Known(2)) {
                    return Err(Error::invalid(
                        "Dynamic quantization requires min/max pairs",
                    ));
                }
                t.shape.remove(0);
                t.quant = None;
                let mut z = t.clone();
                z.dtype = Dtype::I32;
                t.dtype = Dtype::F32;
                return Ok(vec![z, t]);
            }
            Concat => {
                let ax = axis(a.axis, t.shape.len())?;
                let shapes = n
                    .inputs
                    .iter()
                    .map(|x| self.shape(x))
                    .collect::<Result<Vec<_>>>()?;
                if shapes.iter().any(|s| s.len() != t.shape.len()) {
                    return Err(Error::invalid("Concat rank mismatch"));
                }
                t.shape[ax] = Expr::sum(shapes.into_iter().map(|s| s[ax].clone()));
            }
            ShapeTensor => {
                t = TensorType {
                    dtype: Dtype::I32,
                    shape: if a.keep_dims {
                        vec![Expr::Known(a.shape.len() as i64)]
                    } else {
                        vec![]
                    },
                    quant: None,
                };
            }
            QuantizeTensor | DequantizeTensor => {
                t.quant = None;
                t.dtype = if n.op == QuantizeTensor {
                    Dtype::I8
                } else {
                    Dtype::F32
                };
            }
            Gather => {
                let ax = axis(a.axis, t.shape.len())?;
                t.shape.splice(ax..ax + 1, get(1)?);
            }
            Copy | Cast | Exp | Erf | Abs | Log | Logistic | Tanh | Neg | Sin | Cos | Sqrt
            | Rsqrt | Square | Round | HardSwish | LeakyRelu | Elu | Relu | Relu6 | ReluN1To1
            | Relu0To1 | L2Normalization | L2NormEpsilon | Gelu | Polynomial | Softmax
            | CausalMask | ScheduledMask => {}
            _ => {
                return n
                    .outputs
                    .iter()
                    .map(|name| {
                        self.values
                            .get(name)
                            .map(|v| v.tensor.clone())
                            .ok_or_else(|| {
                                Error::invalid(format!(
                                    "Explicit result contract required for {:?}",
                                    n.op
                                ))
                            })
                    })
                    .collect();
            }
        }
        if let Some(dtype) = a.result_dtype {
            t.dtype = dtype;
        }
        Ok(n.outputs.iter().map(|_| t.clone()).collect())
    }
}
