// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
use super::model::*;
use crate::{Error, Result};
use sha2::{Digest, Sha256};
use std::collections::{BTreeMap, BTreeSet};
use std::fmt::Write;
fn quote(x: &str) -> String {
    serde_json::to_string(x).unwrap()
}
fn list(xs: impl IntoIterator<Item = String>) -> String {
    format!("[{}]", xs.into_iter().collect::<Vec<_>>().join(", "))
}
fn ints(xs: &[i64]) -> String {
    list(xs.iter().map(ToString::to_string))
}
fn exprs(xs: &[Expr]) -> String {
    list(xs.iter().map(Expr::render))
}
fn real(x: Real) -> String {
    format!("bits(\"{:016X}\")", x.0)
}
fn native(name: &str, args: Vec<String>) -> Result<String> {
    let op = crate::plan::Op::from_name(name)
        .ok_or_else(|| Error::invalid(format!("Unknown native command {name}")))?;
    if args.len() != op.fields().len() {
        return Err(Error::invalid(format!(
            "Compiler argument count for {name}: {} != {}",
            args.len(),
            op.fields().len()
        )));
    }
    Ok(format!(
        "{}({});\n",
        name,
        op.fields()
            .iter()
            .zip(args)
            .map(|(k, v)| format!("{k}={v}"))
            .collect::<Vec<_>>()
            .join(", ")
    ))
}
/// Packed representation is one interprocedural constraint, including all call sites.
#[derive(Default, Clone, PartialEq, Eq)]
struct PackedTree {
    values: BTreeSet<String>,
    functions: BTreeMap<String, PackedTree>,
}
fn packed(g: &Graph, options: &CompileOptions, seed: &PackedTree) -> PackedTree {
    let names = g
        .values
        .iter()
        .filter(|(_, v)| v.tensor.dtype.bits() < 8)
        .map(|(n, _)| n.clone())
        .collect::<BTreeSet<_>>();
    let mut tree = seed.clone();
    tree.values.retain(|n| names.contains(n));
    tree.values.extend(
        g.values
            .iter()
            .filter(|(n, v)| {
                names.contains(*n)
                    && (options.packed_adapter
                        || v.tensor
                            .shape
                            .last()
                            .and_then(Expr::literal)
                            .is_none_or(|d| d % (8 / v.tensor.dtype.bits()) as i64 != 0))
            })
            .map(|(n, _)| n.clone()),
    );
    for n in &g.nodes {
        if matches!(
            n.op,
            Op::Reverse
                | Op::Tile
                | Op::Pad
                | Op::Select
                | Op::Gather
                | Op::QuantizationCodes
                | Op::WithQuantization
                | Op::Dequantize
                | Op::NativeWeightOnlyLinear
                | Op::BlockwiseFullyConnected
                | Op::ResourceAppend
                | Op::ResourceView
        ) {
            tree.values.extend(
                n.inputs
                    .iter()
                    .chain(&n.outputs)
                    .filter(|x| names.contains(*x))
                    .cloned(),
            );
        }
    }
    loop {
        let previous = tree.clone();
        for n in &g.nodes {
            if is_route(n.op) {
                let related = n
                    .inputs
                    .iter()
                    .chain(&n.outputs)
                    .filter(|x| names.contains(*x))
                    .cloned()
                    .collect::<BTreeSet<_>>();
                if !tree.values.is_disjoint(&related) {
                    tree.values.extend(related);
                }
            }
            if let Some(c) = &n.attributes.call {
                let body = &g.functions[&c.function];
                let child = tree.functions.entry(c.function.clone()).or_default();
                for (actual, formal) in n
                    .inputs
                    .iter()
                    .zip(&body.inputs)
                    .chain(n.outputs.iter().zip(&body.outputs))
                {
                    if tree.values.contains(actual) {
                        child.values.insert(formal.clone());
                    }
                    if child.values.contains(formal) && names.contains(actual) {
                        tree.values.insert(actual.clone());
                    }
                }
            }
        }
        for (name, body) in &g.functions {
            let child = packed(
                body,
                options,
                tree.functions.get(name).unwrap_or(&PackedTree::default()),
            );
            tree.functions.insert(name.clone(), child);
        }
        if tree == previous {
            break;
        }
    }
    tree
}
fn is_route(op: Op) -> bool {
    matches!(
        op,
        Op::Copy
            | Op::Transpose
            | Op::Reshape
            | Op::Squeeze
            | Op::ExpandDims
            | Op::Reverse
            | Op::Slice
            | Op::Tile
            | Op::Pad
            | Op::Select
            | Op::Gather
            | Op::Concat
            | Op::Stack
            | Op::BroadcastTo
            | Op::SliceLike
            | Op::BroadcastLike
            | Op::FuseDims
            | Op::SplitDim
            | Op::EvenSplit
            | Op::Unstack
            | Op::QuantizationCodes
            | Op::WithQuantization
    )
}
struct Emitter<'a> {
    g: &'a Graph,
    options: &'a CompileOptions,
    names: BTreeMap<String, String>,
    packed: BTreeSet<String>,
    assets: BTreeMap<String, Vec<u8>>,
    function_names: BTreeMap<String, String>,
}
impl<'a> Emitter<'a> {
    fn name(&self, n: &str) -> Result<String> {
        if n.is_empty() {
            return Ok("none".into());
        }
        self.names
            .get(n)
            .cloned()
            .ok_or_else(|| Error::invalid(format!("Undeclared value {n}")))
    }
    fn operand(&self, n: &str) -> Result<String> {
        let x = self.name(n)?;
        Ok(if self.packed.contains(n) {
            format!("native({x})")
        } else {
            x
        })
    }
    fn ty(&self, n: &str, owner: bool) -> String {
        let v = &self.g.values[n];
        let dtype = if self.packed.contains(n) {
            format!("packed_i{}", v.tensor.dtype.bits())
        } else {
            v.tensor.dtype.native().into()
        };
        format!(
            "{}<{}{}>",
            if owner { "owner" } else { "storage" },
            dtype,
            list(
                v.tensor
                    .shape
                    .iter()
                    .map(|d| d.literal().unwrap_or(0).to_string())
            )
        )
    }
    fn asset(&mut self, v: &Value) -> Result<Option<Asset>> {
        if let Some(a) = &v.data {
            if a.bytes != 0 {
                return Ok(Some(a.clone()));
            }
        }
        if !v.constant {
            return Ok(None);
        }
        let bytes = literal_bytes(v)?;
        let sha = format!("{:x}", Sha256::digest(&bytes));
        let file = format!("{sha}.bin");
        let data = Asset {
            path: format!("@parameters/{file}"),
            bytes: bytes.len(),
            sha256: sha,
        };
        self.assets.insert(file, bytes);
        Ok(Some(data))
    }
    fn node(&self, n: &Node) -> Result<String> {
        use Op::*;
        let a = &n.attributes;
        let ins = n
            .inputs
            .iter()
            .map(|x| self.name(x))
            .collect::<Result<Vec<_>>>()?;
        let outs = n
            .outputs
            .iter()
            .map(|x| self.name(x))
            .collect::<Result<Vec<_>>>()?;
        let out = outs[0].clone();
        let x = ins.first().cloned().unwrap_or_default();
        let y = ins.get(1).cloned().unwrap_or_default();
        let shape = &self.g.values[&n.outputs[0]].tensor.shape;
        if let Some(call) = &a.call {
            let body = &self.g.functions[&call.function];
            let mut args = ins.clone();
            for s in &body.symbols {
                args.push(
                    call.indices
                        .get(&s.id)
                        .ok_or_else(|| Error::invalid("Missing function index binding"))?
                        .render(),
                );
            }
            return Ok(format!(
                "@scope(name={}) invoke {}({}) -> ({});\n",
                quote(&n.scope),
                self.function_names[&call.function],
                args.join(", "),
                outs.join(", ")
            ));
        }
        if is_route(n.op) && self.packed.contains(&n.outputs[0]) {
            let route = if matches!(n.op, QuantizationCodes | WithQuantization) {
                "copy".into()
            } else {
                n.op.name()
            };
            let input = if matches!(n.op, QuantizationCodes | WithQuantization) {
                vec![x]
            } else {
                ins.clone()
            };
            let attrs = if n.op == Reverse {
                &a.axes
            } else {
                &a.integers
            };
            if matches!(n.op, EvenSplit | Unstack) {
                let mut result = String::new();
                for (i, o) in outs.iter().enumerate() {
                    result += &native(
                        "PackedRoute",
                        vec![
                            quote(&route),
                            list([ins[0].clone()]),
                            o.clone(),
                            exprs(&self.g.values[&n.outputs[i]].tensor.shape),
                            ints(&[i as i64]),
                            "[]".into(),
                            a.axis.to_string(),
                            "0".into(),
                        ],
                    )?;
                }
                return Ok(result);
            }
            return native(
                "PackedRoute",
                vec![
                    quote(&route),
                    list(input),
                    out,
                    exprs(shape),
                    ints(attrs),
                    exprs(&a.starts),
                    a.axis.to_string(),
                    a.pad_mode.to_string(),
                ],
            );
        }
        let command = match n.op {
            Add | Sub | Mul | Div | Maximum | Minimum | Pow | Prelu => {
                let op = match n.op {
                    Add => "add",
                    Sub => "subtract",
                    Mul => "multiply",
                    Div => "divide",
                    Maximum => "max",
                    Minimum => "min",
                    Pow => "pow",
                    _ => "leaky_relu",
                };
                ("Binary", vec![op.into(), x, y, out])
            }
            Exp | Erf | Abs | Log | Logistic | Tanh | Neg | Sin | Cos | Sqrt | Rsqrt | Square
            | Round | HardSwish => {
                let op = match n.op {
                    Logistic => "sigmoid".into(),
                    Neg => "negate".into(),
                    HardSwish => "hardswish".into(),
                    _ => n.op.name(),
                };
                ("Unary", vec![op, x, out])
            }
            Copy | QuantizationCodes | WithQuantization => ("Copy", vec![x, out]),
            Cast => ("Convert", vec![x, out]),
            Matmul => (
                "Matmul",
                vec![x, y, out, a.adj_x.to_string(), a.adj_y.to_string()],
            ),
            Dot => (
                "Dot",
                vec![
                    self.operand(&n.inputs[0])?,
                    self.operand(&n.inputs[1])?,
                    ins.get(2).cloned().unwrap_or("none".into()),
                    out,
                    a.contraction_dims.to_string(),
                ],
            ),
            NativeWeightOnlyLinear | BlockwiseFullyConnected => (
                if n.op == NativeWeightOnlyLinear {
                    "WeightOnlyLinear"
                } else {
                    "BlockwiseFullyConnected"
                },
                vec![
                    x,
                    y,
                    ins[2].clone(),
                    ins[3].clone(),
                    out,
                    a.integers[0].to_string(),
                ],
            ),
            QuantizeTensor | DequantizeTensor => {
                let (z, s) = if ins.len() == 3 {
                    (ins[1].clone(), ins[2].clone())
                } else {
                    ("none".into(), ins[1].clone())
                };
                (
                    if n.op == QuantizeTensor {
                        "QuantizeTensor"
                    } else {
                        "DequantizeTensor"
                    },
                    vec![x, z, s, out],
                )
            }
            DynamicQuantization => ("DynamicQuantization", vec![x, out, outs[1].clone()]),
            QuantizationParameters => (
                "ParameterExpand",
                vec![x, y, out, ints(&a.axes), ints(&a.integers)],
            ),
            Quantize | Dequantize => {
                let q = self.g.values[if n.op == Quantize {
                    &n.outputs[0]
                } else {
                    &n.inputs[0]
                }]
                .tensor
                .quant
                .as_ref()
                .ok_or_else(|| Error::invalid("Missing quantization"))?;
                if let Some(p) = &q.parameters {
                    if n.op != Dequantize {
                        return Err(Error::invalid("Mapped quantization needs explicit tensors"));
                    }
                    (
                        "MappedDequantize",
                        vec![
                            x,
                            self.name(&p.scales)?,
                            self.name(&p.zeros)?,
                            out,
                            ints(&p.axes),
                            ints(&p.blocks),
                        ],
                    )
                } else {
                    if q.scales.len() != 1 || q.zeros.len() != 1 {
                        return Err(Error::invalid(
                            "Per-axis dequantization needs explicit parameter tensors",
                        ));
                    }
                    (
                        if n.op == Quantize {
                            "Quantize"
                        } else {
                            "Dequantize"
                        },
                        vec![
                            if n.op == Dequantize {
                                self.operand(&n.inputs[0])?
                            } else {
                                x
                            },
                            out,
                            real(q.scales[0]),
                            q.zeros[0].to_string(),
                        ],
                    )
                }
            }
            ReduceSum | ReduceMax | ReduceMin | ReduceMinMax | ReduceSumSquared => (
                "Reduce",
                vec![
                    n.op.name().trim_start_matches("reduce_").into(),
                    x,
                    out,
                    ints(&a.axes),
                    a.keep_dims.to_string(),
                ],
            ),
            GetShape => ("ShapeProduct", vec![x, out, ints(&a.axes)]),
            Polynomial => (
                "Polynomial",
                vec![x, out, list(a.coefficients.iter().copied().map(real))],
            ),
            ResourceAppend => {
                let rows =
                    self.g.values[&n.inputs[1]].tensor.shape[axis(a.axis, shape.len())?].render();
                (
                    "Append",
                    vec![x, y, out, a.axis.to_string(), a.position.render(), rows],
                )
            }
            ResourceView => (
                "View",
                vec![x, out, a.axis.to_string(), a.begin.render(), a.end.render()],
            ),
            CausalMask | ScheduledMask => (
                "Mask",
                vec![
                    x,
                    out,
                    a.position.render(),
                    a.begin.render(),
                    a.window.to_string(),
                    (n.op == ScheduledMask).to_string(),
                ],
            ),
            Sdpa => {
                let s = a.attention.as_ref().unwrap();
                let q = s
                    .query_length
                    .clone()
                    .unwrap_or(self.g.values[&n.inputs[0]].tensor.shape[2].clone());
                let k = s
                    .key_length
                    .clone()
                    .unwrap_or(self.g.values[&n.inputs[1]].tensor.shape[2].clone());
                (
                    "Sdpa",
                    vec![
                        x,
                        y,
                        ins[2].clone(),
                        ins.get(3).cloned().unwrap_or("none".into()),
                        out,
                        ints(&s.heads),
                        real(s.scale),
                        s.mask.to_string(),
                        s.causal.to_string(),
                        s.window.to_string(),
                        s.query_position.render(),
                        s.key_position.render(),
                        q.render(),
                        k.render(),
                        s.all_masked_nan.to_string(),
                    ],
                )
            }
            DynamicMatmul => {
                let q = self.g.values[&n.inputs[1]]
                    .tensor
                    .quant
                    .as_ref()
                    .ok_or_else(|| Error::invalid("Dynamic matmul requires quantized RHS"))?;
                if q.scales.len() != 1 || q.zeros != [0] {
                    return Err(Error::invalid(
                        "Dynamic matmul requires symmetric per-tensor RHS",
                    ));
                }
                (
                    "DynamicallyQuantizedMatmul",
                    vec![
                        x,
                        y,
                        out,
                        real(q.scales[0]),
                        a.adj_y.to_string(),
                        a.integers.first().copied().unwrap_or(-1).to_string(),
                    ],
                )
            }
            FuseDims => (
                "FuseDims",
                vec![x, out, a.axis.to_string(), a.integers[0].to_string()],
            ),
            SplitDim => {
                let ds = a
                    .shape
                    .iter()
                    .map(|d| d.literal().unwrap_or(0))
                    .collect::<Vec<_>>();
                if ds.iter().filter(|x| **x == 0).count() > 1 {
                    return Err(Error::invalid("Split dimension allows one inferred extent"));
                }
                ("SplitDim", vec![x, out, a.axis.to_string(), ints(&ds)])
            }
            ShapeTensor => (
                "ShapeTensor",
                vec![out, exprs(&a.shape), (!a.keep_dims).to_string()],
            ),
            Transpose => ("Transpose", vec![x, out, ints(&a.integers)]),
            Reshape => {
                let input = &self.g.values[&n.inputs[0]].tensor.shape;
                let (mut matched, mut axes) = (0, vec![]);
                let mut expanded = true;
                for (i, d) in shape.iter().enumerate() {
                    if input.get(matched) == Some(d) {
                        matched += 1;
                    } else if *d == Expr::Known(1) {
                        axes.push(i as i64);
                    } else {
                        expanded = false;
                        break;
                    }
                }
                if expanded && matched == input.len() && !axes.is_empty() {
                    ("ExpandDims", vec![x, out, ints(&axes)])
                } else {
                    let dims = shape
                        .iter()
                        .map(|d| d.literal().unwrap_or(-1))
                        .collect::<Vec<_>>();
                    if dims.contains(&0) || dims.iter().filter(|x| **x < 0).count() > 1 {
                        if self.g.values[&n.inputs[0]].resource.is_some() {
                            return Err(Error::invalid(
                                "Symbolic reshape requires ordinary storage",
                            ));
                        }
                        ("SymbolicReshape", vec![x, out, exprs(shape)])
                    } else {
                        (
                            "Reshape",
                            vec![
                                x,
                                out,
                                ints(&dims.iter().map(|x| (*x).max(0)).collect::<Vec<_>>()),
                            ],
                        )
                    }
                }
            }
            Squeeze | ExpandDims => {
                let input = &self.g.values[&n.inputs[0]].tensor.shape;
                let rank = if n.op == Squeeze {
                    input.len()
                } else {
                    shape.len()
                };
                let mut axes = if n.op == Squeeze && a.axes.is_empty() {
                    input
                        .iter()
                        .enumerate()
                        .filter_map(|(i, x)| (*x == Expr::Known(1)).then_some(i as i64))
                        .collect::<Vec<_>>()
                } else {
                    a.axes
                        .iter()
                        .map(|x| axis(*x, rank).map(|a| a as i64))
                        .collect::<Result<Vec<_>>>()?
                };
                axes.sort();
                (
                    if n.op == Squeeze {
                        "Squeeze"
                    } else {
                        "ExpandDims"
                    },
                    vec![x, out, ints(&axes)],
                )
            }
            BroadcastTo => {
                if self.g.outputs.contains(&n.outputs[0])
                    || shape.iter().any(|d| d.literal().is_none_or(|x| x == 0))
                {
                    ("SymbolicBroadcast", vec![x, out, exprs(shape)])
                } else {
                    (
                        "Broadcast",
                        vec![
                            x,
                            out,
                            ints(
                                &shape
                                    .iter()
                                    .map(|d| d.literal().unwrap())
                                    .collect::<Vec<_>>(),
                            ),
                        ],
                    )
                }
            }
            BroadcastLike | SliceLike => (
                if n.op == BroadcastLike {
                    "BroadcastLike"
                } else {
                    "SliceLike"
                },
                vec![x, y, out, ints(&a.axes)],
            ),
            Slice => {
                let input = &self.g.values[&n.inputs[0]].tensor.shape;
                if input.is_empty() {
                    ("Copy", vec![x, out])
                } else {
                    let starts = if a.starts.is_empty() {
                        a.integers
                            .iter()
                            .map(|x| Expr::Known(*x))
                            .collect::<Vec<_>>()
                    } else {
                        a.starts.clone()
                    };
                    let mut sizes = vec![];
                    for ((start, len), extent) in starts.iter().zip(shape).zip(input) {
                        if *start == Expr::Known(0) && len == extent {
                            sizes.push(-1);
                        } else if start.literal().is_some() && len.literal().is_some_and(|x| x > 0)
                        {
                            sizes.push(len.literal().unwrap());
                        } else {
                            break;
                        }
                    }
                    if sizes.len() == shape.len() {
                        (
                            "Slice",
                            vec![
                                x,
                                out,
                                ints(
                                    &starts
                                        .iter()
                                        .map(|x| x.literal().unwrap())
                                        .collect::<Vec<_>>(),
                                ),
                                ints(&sizes),
                            ],
                        )
                    } else {
                        ("SymbolicSlice", vec![x, out, exprs(&starts), exprs(shape)])
                    }
                }
            }
            Concat => ("Concat", vec![list(ins), out, a.axis.to_string()]),
            Stack => ("Stack", vec![list(ins), out, a.axis.to_string()]),
            EvenSplit | Unstack => (
                "Split",
                vec![
                    x,
                    list(outs),
                    axis(a.axis, self.g.values[&n.inputs[0]].tensor.shape.len())?.to_string(),
                    (n.op == Unstack).to_string(),
                ],
            ),
            Reverse => ("Reverse", vec![x, out, ints(&a.axes)]),
            Tile => ("Tile", vec![x, out, ints(&a.integers)]),
            Pad => (
                "Pad",
                vec![
                    x,
                    if a.pad_mode == 0 { y } else { "none".into() },
                    out,
                    exprs(&a.starts),
                    exprs(&a.lengths),
                    a.pad_mode.to_string(),
                ],
            ),
            Select => ("Select", vec![x, y, ins[2].clone(), out, exprs(shape)]),
            Less | LessEqual | Greater | GreaterEqual | Equal | NotEqual => (
                "Compare",
                vec![quote(&n.op.name()), x, y, out, exprs(shape)],
            ),
            Gather => {
                if n.inputs.iter().any(|x| {
                    self.g.values[x]
                        .tensor
                        .quant
                        .as_ref()
                        .is_some_and(|q| q.parameters.is_some())
                }) {
                    (
                        "PackedRoute",
                        vec![
                            quote("gather"),
                            list(ins),
                            out,
                            exprs(shape),
                            "[]".into(),
                            "[]".into(),
                            a.axis.to_string(),
                            "0".into(),
                        ],
                    )
                } else {
                    ("Gather", vec![x, y, out, a.axis.to_string()])
                }
            }
            Conv2D | DepthwiseConv2D | AveragePool2D | MaxPool2D => {
                let s = a
                    .spatial
                    .as_ref()
                    .ok_or_else(|| Error::invalid("Missing spatial attributes"))?;
                let input = &self.g.values[&n.inputs[0]].tensor.shape;
                if input.len() != 4
                    || shape.len() != 4
                    || input[1..]
                        .iter()
                        .chain(&shape[1..])
                        .any(|d| d.literal().is_none_or(|n| n <= 0))
                {
                    return Err(Error::invalid(
                        "Spatial operations require positive static spatial/channel dimensions",
                    ));
                }
                if matches!(n.op, Conv2D | DepthwiseConv2D) {
                    let f = &self.g.values[&n.inputs[1]].tensor.shape;
                    let kernel = f[1..3]
                        .iter()
                        .map(|x| {
                            x.literal()
                                .ok_or_else(|| Error::invalid("Static filter required"))
                        })
                        .collect::<Result<Vec<_>>>()?;
                    (
                        "Conv2D",
                        vec![
                            x,
                            y,
                            ins.get(2).cloned().unwrap_or("none".into()),
                            out,
                            ints(&kernel),
                            ints(&s.strides),
                            ints(&s.dilations),
                            s.same.to_string(),
                            (n.op == DepthwiseConv2D).to_string(),
                            input[3].literal().unwrap().to_string(),
                            s.multiplier.to_string(),
                        ],
                    )
                } else {
                    (
                        "Pool2D",
                        vec![
                            x,
                            out,
                            ints(&s.kernel),
                            ints(&s.strides),
                            s.same.to_string(),
                            (n.op == AveragePool2D).to_string(),
                        ],
                    )
                }
            }
            GatedDeltaRule => {
                let mut args = ins;
                args.extend(outs);
                args.push(ints(&a.integers));
                args.push(real(a.beta));
                ("GatedDeltaRule", args)
            }
            CausalDepthwiseConv => (
                "CausalDepthwiseConv",
                vec![
                    x,
                    y,
                    ins[2].clone(),
                    out,
                    outs[1].clone(),
                    a.position.render(),
                    a.approximate.to_string(),
                ],
            ),
            _ => {
                return Err(Error::invalid(format!(
                    "Unlowered semantic operation {:?}",
                    n.op
                )))
            }
        };
        native(command.0, command.1)
    }
    fn body(&mut self, function: bool) -> Result<String> {
        let mut text = String::new();
        let outputs = self.g.outputs.iter().cloned().collect::<BTreeSet<_>>();
        let state_outputs = state_outputs(self.g);
        for (name, v) in &self.g.values {
            if function && (self.g.inputs.contains(name) || outputs.contains(name)) {
                continue;
            }
            let value = self.name(name)?;
            let data = self.asset(v)?;
            let role = if data.is_some() {
                "weight"
            } else if !function && self.g.inputs.contains(name) {
                "input"
            } else {
                "value"
            };
            write!(text, "{role} {value}: {}", self.ty(name, false)).unwrap();
            if let Some(d) = data {
                write!(
                    text,
                    " = asset(path={}, bytes={}, sha256={})",
                    quote(&d.path),
                    d.bytes,
                    quote(&d.sha256)
                )
                .unwrap();
            }
            text.push_str(";\n");
            if !function && (outputs.contains(name) || state_outputs.contains(name)) {
                writeln!(text, "output {value};").unwrap();
            }
        }
        if !function {
            for s in &self.g.symbols {
                let src = match &s.binding {
                    SymbolSource::Axis { value, axis } => {
                        format!("axis({}, {axis})", self.name(value)?)
                    }
                    SymbolSource::Parameter { name, .. } => format!("parameter({})", quote(name)),
                    SymbolSource::Instance { name } => format!("instance({})", quote(name)),
                };
                writeln!(text, "dim s{} = {src} in {}..={};", s.id, s.lower, s.upper).unwrap();
                if let SymbolSource::Parameter { name, value } = &s.binding {
                    if !value.is_empty() {
                        text +=
                            &native("BindScalarParameter", vec![self.name(value)?, quote(name)])?;
                    }
                }
            }
        }
        for name in &self.g.inputs {
            text += &native(
                if function {
                    "ResultShape"
                } else {
                    "InputShape"
                },
                vec![self.name(name)?, exprs(&self.g.values[name].tensor.shape)],
            )?;
        }
        for r in &self.g.resources {
            let t = &self.g.values[&r.owner].tensor;
            let encoding = if let Some(q) = &t.quant {
                format!(
                    "encoding(dtype={}, axis={}, scales={}, zero_points={})",
                    t.dtype.native(),
                    q.axis,
                    list(q.scales.iter().copied().map(real)),
                    ints(&q.zeros)
                )
            } else {
                format!(
                    "encoding(dtype={}, axis=none, scales=[], zero_points=[])",
                    t.dtype.native()
                )
            };
            text += &native(
                "Resource",
                vec![
                    self.name(&r.owner)?,
                    quote(&r.name),
                    r.axis.to_string(),
                    r.entry.render(),
                    encoding,
                ],
            )?;
            if t.dtype.bits() < 8 && !r.strides.is_empty() {
                text += &native(
                    "PackedStrides",
                    vec![self.name(&r.owner)?, exprs(&r.strides)],
                )?;
            }
        }
        for g in &self.g.guards {
            writeln!(
                text,
                "@guard(message={}, mode={}) require {} {} {};",
                quote(&g.reason),
                quote(&g.mode),
                g.lhs.render(),
                if g.relation == "eq" {
                    "=="
                } else if g.relation == "le" {
                    "<="
                } else {
                    return Err(Error::invalid("Unsupported guard relation"));
                },
                g.rhs.render()
            )
            .unwrap();
        }
        for n in &self.g.nodes {
            let ins = n
                .inputs
                .iter()
                .filter(|s| !s.is_empty())
                .map(|x| self.name(x))
                .collect::<Result<Vec<_>>>()?;
            let outs = n
                .outputs
                .iter()
                .map(|x| self.name(x))
                .collect::<Result<Vec<_>>>()?;
            if n.op != Op::Call {
                text += &native(
                    "BeginProfileOperation",
                    vec![
                        quote(&n.scope),
                        quote(&n.op.name()),
                        list(ins),
                        list(outs.clone()),
                        list(n.inputs.iter().filter(|s| !s.is_empty()).map(|s| quote(s))),
                    ],
                )?;
            }
            if !n.waits.is_empty() || !n.completes.is_empty() {
                text += &native(
                    "BeginOperation",
                    vec![list(n.waits.iter().map(|x| quote(x)))],
                )?;
            }
            text += &self.node(n)?;
            if !n.waits.is_empty() || !n.completes.is_empty() {
                text += &native(
                    "EndOperation",
                    vec![list(n.completes.iter().map(|x| quote(x))), list(outs)],
                )?;
            }
            if n.op != Op::Call {
                text += &native("EndProfileOperation", vec![])?;
            }
            for y in &n.outputs {
                if self.options.check_shapes || outputs.contains(y) {
                    text += &native(
                        "ResultShape",
                        vec![self.name(y)?, exprs(&self.g.values[y].tensor.shape)],
                    )?;
                }
            }
        }
        if !self.g.completions.is_empty() {
            text += &native(
                "CompletionOutput",
                vec![list(self.g.completions.iter().map(|x| quote(x)))],
            )?;
        }
        if !function {
            text.push_str("metadata {\n");
            for (name, alias) in &self.names {
                writeln!(text, "name {alias} = {};", quote(name)).unwrap();
                if self.g.values[name].constant && outputs.contains(name) {
                    writeln!(
                        text,
                        "declaration {alias} = {};",
                        if self.packed.contains(name) {
                            "PackedConstantOutput"
                        } else {
                            "ConstantOutput"
                        }
                    )
                    .unwrap();
                }
            }
            text.push_str("}\n");
        } else {
            writeln!(
                text,
                "return({});",
                self.g
                    .outputs
                    .iter()
                    .map(|x| self.name(x))
                    .collect::<Result<Vec<_>>>()?
                    .join(", ")
            )
            .unwrap();
        }
        Ok(text)
    }
}
fn graph_source(
    g: &Graph,
    options: &CompileOptions,
    prefix: &str,
    is_function: bool,
    representation: &PackedTree,
) -> Result<(String, String, BTreeMap<String, Vec<u8>>, BTreeSet<String>)> {
    let names = g
        .values
        .keys()
        .enumerate()
        .map(|(i, n)| (n.clone(), format!("v{i}")))
        .collect::<BTreeMap<_, _>>();
    let function_names = g
        .functions
        .keys()
        .enumerate()
        .map(|(i, n)| (n.clone(), format!("{prefix}f{i}")))
        .collect::<BTreeMap<_, _>>();
    let mut e = Emitter {
        g,
        options,
        names,
        packed: representation.values.clone(),
        assets: BTreeMap::new(),
        function_names,
    };
    let mut definitions = String::new();
    for (name, body) in &g.functions {
        let fn_name = e.function_names[name].clone();
        let (nested, text, assets, _) = graph_source(
            body,
            options,
            &(fn_name + "_"),
            true,
            &representation.functions[name],
        )?;
        definitions += &nested;
        definitions += &format!("fn {}{text}\n", e.function_names[name]);
        e.assets.extend(assets);
    }
    let text = if is_function {
        let binding = |n: &String| {
            format!(
                "{}: {}",
                e.names[n],
                e.ty(n, g.values[n].resource.as_ref().is_some_and(|r| r.owner))
            )
        };
        let mut args = g.inputs.iter().map(binding).collect::<Vec<_>>();
        args.extend(g.symbols.iter().map(|s| format!("s{}: index", s.id)));
        let header = format!(
            "({}) -> ({}) {{\n",
            args.join(", "),
            g.outputs.iter().map(binding).collect::<Vec<_>>().join(", ")
        );
        header + &e.body(true)? + "}\n"
    } else {
        e.body(false)?
    };
    Ok((definitions, text, e.assets, e.packed))
}
pub(super) fn emit(
    g: &Graph,
    options: &CompileOptions,
) -> Result<(String, BTreeMap<String, Vec<u8>>, serde_json::Value)> {
    let (definitions, body, assets, packed) = graph_source(
        g,
        options,
        "",
        false,
        &packed(g, options, &PackedTree::default()),
    )?;
    let source=format!("ynn 1 resource_contract=1 completion_contract=1 profiling=explicit {{\n{definitions}{body}}}\n");
    let interned = crate::plan_text::intern(&source)?;
    let formatted = crate::plan_text::format(&interned)
        .map_err(|e| Error::invalid(format!("Generated construction source: {e}")))?;
    let packed_storage = packed
        .into_iter()
        .map(|name| {
            let v = &g.values[&name];
            (
                name,
                serde_json::json!({"bits":v.tensor.dtype.bits(),"dtype":v.tensor.dtype.native()}),
            )
        })
        .collect::<BTreeMap<_, _>>();
    let report = serde_json::json!({"owner":"public_rust_compiler","adapter_contract":"resource-state-v1","completion_contract":"completion-v1","completion_outputs":g.completions,"operations":g.nodes.len(),"values":g.values.len(),"functions":g.functions.len(),"packed_storage":packed_storage,"emission_supported":true,"inputs":g.inputs.iter().map(|n|serde_json::json!({"name":n,"tensor":g.values[n].tensor})).collect::<Vec<_>>(),"outputs":g.outputs.iter().map(|n|serde_json::json!({"name":n,"tensor":g.values[n].tensor})).collect::<Vec<_>>(),"resources":g.resources,"state_outputs":state_outputs(g),"resolved_resources":g.resources.iter().map(|r|serde_json::json!({"name":r.name,"binding":r.owner,"axis":r.axis,"tensor":g.values[&r.owner].tensor,"element_strides":resolved_strides(r,&g.values[&r.owner].tensor),"layout":if g.values[&r.owner].tensor.dtype.bits()<8 {"packed"}else{"dense"}})).collect::<Vec<_>>()});
    Ok((formatted, assets, report))
}

fn state_outputs(g: &Graph) -> BTreeSet<String> {
    g.nodes
        .iter()
        .flat_map(|n| &n.outputs)
        .filter(|n| g.values[*n].resource.as_ref().is_some_and(|r| r.owner))
        .cloned()
        .collect()
}
