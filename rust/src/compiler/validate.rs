// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
//! Validate the public boundary before target code can index the program.
use super::model::*;
use crate::{Error, Result};
use sha2::{Digest, Sha256};
use std::collections::BTreeSet;
fn require(ok: bool, text: impl Into<String>) -> Result<()> {
    if ok {
        Ok(())
    } else {
        Err(Error::invalid(text))
    }
}
fn expr(e: &Expr, symbols: &BTreeSet<u32>, depth: usize) -> Result<()> {
    require(depth < 64, "Dimension expression nesting limit")?;
    match e {
        Expr::Known(_) => Ok(()),
        Expr::Symbol(s) => require(symbols.contains(s), format!("Undefined dimension s{s}")),
        Expr::Add(xs)
        | Expr::Mul(xs)
        | Expr::Min(xs)
        | Expr::Max(xs)
        | Expr::FloorDiv(xs)
        | Expr::CeilDiv(xs) => {
            require(!xs.is_empty(), "Empty dimension expression")?;
            if matches!(e, Expr::FloorDiv(_) | Expr::CeilDiv(_)) {
                require(xs.len() == 2, "Division dimension needs two operands")?;
                require(xs[1].literal() != Some(0), "Zero dimension divisor")?;
            }
            for x in xs {
                expr(x, symbols, depth + 1)?;
            }
            Ok(())
        }
    }
}
pub(super) fn graph(g: &Graph, depth: usize) -> Result<()> {
    require(depth < 32, "Function nesting limit")?;
    require(
        g.values.len() <= 100_000 && g.nodes.len() <= 500_000,
        "Program size limit",
    )?;
    let mut symbols = BTreeSet::new();
    for s in &g.symbols {
        require(
            symbols.insert(s.id) && s.lower <= s.upper,
            "Duplicate symbol or invalid bounds",
        )?;
        match &s.binding {
            SymbolSource::Axis { value, axis } => {
                require(
                    g.inputs.contains(value),
                    "Dimension axis must bind a graph input",
                )?;
                require(
                    g.values
                        .get(value)
                        .is_some_and(|v| *axis < v.tensor.shape.len()),
                    "Invalid input dimension axis",
                )?;
            }
            SymbolSource::Parameter { value, .. } if !value.is_empty() => {
                require(
                    g.inputs.contains(value)
                        && g.values.get(value).is_some_and(|v| {
                            v.tensor.dtype == Dtype::I32 && v.tensor.shape.is_empty()
                        }),
                    "Runtime scalar requires an INT32 scalar input",
                )?;
            }
            _ => {}
        }
    }
    for (name, v) in &g.values {
        require(
            !name.is_empty() && !name.contains('\0'),
            "Invalid value identity",
        )?;
        require(
            v.tensor.shape.len() <= 6,
            "Tensor rank exceeds backend limit",
        )?;
        for d in &v.tensor.shape {
            expr(d, &symbols, 0)?;
            require(d.literal().is_none_or(|x| x >= 0), "Negative tensor extent")?;
        }
        if let Some(q) = &v.tensor.quant {
            require(
                q.scales
                    .iter()
                    .all(|s| s.get().is_finite() && s.get() > 0.0),
                "Quantization scale must be finite and positive",
            )?;
            require(
                q.scales.len() == q.zeros.len() || q.zeros.len() == 1,
                "Quantization scale/zero count mismatch",
            )?;
            if let Some(p) = &q.parameters {
                require(
                    g.values.contains_key(&p.scales) && g.values.contains_key(&p.zeros),
                    "Missing quantization parameter value",
                )?;
                require(
                    p.axes.len() == p.blocks.len() && p.blocks.iter().all(|b| *b > 0),
                    "Invalid quantization parameter geometry",
                )?;
                for a in &p.axes {
                    axis(*a, v.tensor.shape.len())?;
                }
            }
        }
        require(
            v.constant || v.data.is_none() && v.integers.is_empty() && v.floats.is_empty(),
            "Nonconstant value has literal data",
        )?;
        if v.constant {
            let count = v
                .tensor
                .shape
                .iter()
                .try_fold(1usize, |n, d| {
                    usize::try_from(d.literal()?)
                        .ok()
                        .and_then(|d| n.checked_mul(d))
                })
                .ok_or_else(|| Error::invalid("Constant requires finite concrete storage"))?;
            let bytes = count
                .checked_mul(v.tensor.dtype.bits())
                .and_then(|n| n.checked_add(7))
                .ok_or_else(|| Error::invalid("Constant storage size overflow"))?
                / 8;
            if let Some(a) = &v.data {
                require(
                    a.bytes == bytes || bytes == 0 && a.bytes == 1,
                    "Constant asset byte count mismatch",
                )?;
                require(
                    a.sha256.len() == 64 && a.sha256.bytes().all(|b| b.is_ascii_hexdigit()),
                    "Asset requires SHA256",
                )?;
                if !v.integers.is_empty() || !v.floats.is_empty() {
                    require(
                        v.integers.len() + v.floats.len() == count,
                        "Constant hint count mismatch",
                    )?;
                    let literal = literal_bytes(v)?;
                    require(
                        literal.len() == a.bytes
                            && format!("{:x}", Sha256::digest(&literal))
                                == a.sha256.to_ascii_lowercase(),
                        "Constant literal hints disagree with asset digest",
                    )?;
                }
            } else {
                require(
                    v.integers.len() + v.floats.len() == count,
                    "Constant literal element count mismatch",
                )?;
            }
        }
    }
    for q in &g.guards {
        expr(&q.lhs, &symbols, 0)?;
        expr(&q.rhs, &symbols, 0)?;
        require(
            matches!(q.relation.as_str(), "eq" | "le"),
            "Unsupported guard relation",
        )?;
    }
    for r in &g.resources {
        let v = g
            .values
            .get(&r.owner)
            .ok_or_else(|| Error::invalid("Resource owner is missing"))?;
        axis(r.axis, v.tensor.shape.len())?;
        expr(&r.entry, &symbols, 0)?;
        require(
            r.strides.is_empty() || r.strides.len() == v.tensor.shape.len(),
            "Resource stride rank mismatch",
        )?;
        for s in &r.strides {
            expr(s, &symbols, 0)?;
        }
    }
    let mut available = BTreeSet::new();
    for x in &g.inputs {
        require(
            g.values.contains_key(x) && available.insert(x.clone()),
            "Missing or duplicate graph input",
        )?;
    }
    available.extend(
        g.values
            .iter()
            .filter(|(_, v)| v.constant)
            .map(|(n, _)| n.clone()),
    );
    let mut tokens = BTreeSet::new();
    for n in &g.nodes {
        use Op::*;
        operands(n)?;
        for (i, x) in n.inputs.iter().enumerate() {
            require(
                !x.is_empty()
                    || matches!(
                        (n.op, i),
                        (Op::Dot, 2) | (Op::Conv2D, 2) | (Op::DepthwiseConv2D, 2) | (Op::Pad, 1)
                    ),
                "Missing required tensor operand",
            )?;
        }
        for x in n.inputs.iter().filter(|n| !n.is_empty()) {
            require(
                available.contains(x),
                format!("Operand {x} used before definition"),
            )?;
        }
        for t in &n.waits {
            require(
                tokens.contains(t),
                format!("Completion {t} used before definition"),
            )?;
        }
        for t in &n.completes {
            require(
                !t.is_empty() && !g.values.contains_key(t) && tokens.insert(t.clone()),
                "Duplicate or invalid completion identity",
            )?;
        }
        for y in &n.outputs {
            require(
                g.values.contains_key(y) && available.insert(y.clone()),
                format!("Missing or duplicate result {y}"),
            )?;
        }
        let a = &n.attributes;
        for e in
            a.shape
                .iter()
                .chain(&a.starts)
                .chain(&a.lengths)
                .chain([&a.begin, &a.end, &a.position])
        {
            expr(e, &symbols, 0)?;
        }
        require(
            a.contraction_dims <= 6,
            "Invalid contraction dimension count",
        )?;
        let rank = n
            .inputs
            .first()
            .and_then(|x| g.values.get(x))
            .map_or(0, |v| v.tensor.shape.len());
        match n.op {
            Prelu | HardSwish => require(
                g.values[&n.inputs[0]].tensor.dtype == Dtype::F32,
                "Extended activation requires FP32",
            )?,
            Cast if g.values[&n.outputs[0]].tensor.dtype == Dtype::Bool
                && g.values[&n.inputs[0]].tensor.dtype != Dtype::Bool =>
            {
                let input = &g.values[&n.inputs[0]];
                require(
                    input.constant
                        && a.fold_constants
                        && (!input.floats.is_empty() || !input.integers.is_empty()),
                    "BOOL supports routing only; numeric conversion requires explicit comparison",
                )?;
            }
            Call => {
                let c = a
                    .call
                    .as_ref()
                    .ok_or_else(|| Error::invalid("Missing call contract"))?;
                let f = g
                    .functions
                    .get(&c.function)
                    .ok_or_else(|| Error::invalid("Missing function body"))?;
                require(
                    n.inputs.len() == f.inputs.len() && n.outputs.len() == f.outputs.len(),
                    "Function argument/result count mismatch",
                )?;
                for s in &f.symbols {
                    expr(
                        c.indices
                            .get(&s.id)
                            .ok_or_else(|| Error::invalid("Missing function index"))?,
                        &symbols,
                        0,
                    )?;
                }
            }
            Matmul | Dot | DynamicMatmul => {
                let k = if n.op == Dot { a.contraction_dims } else { 1 };
                require(
                    k > 0 && rank > k && g.values[&n.inputs[1]].tensor.shape.len() > k,
                    "Invalid matrix contraction ranks",
                )?;
            }
            NativeWeightOnlyLinear | BlockwiseFullyConnected => {
                require(
                    rank > 0
                        && g.values[&n.inputs[1]].tensor.shape.len() == 2
                        && a.integers.first().is_some_and(|x| *x > 0),
                    "Invalid quantized linear geometry",
                )?;
                let weight = &g.values[&n.inputs[1]].tensor;
                let group = a.integers[0];
                if let Some(p) = weight.quant.as_ref().and_then(|q| q.parameters.as_ref()) {
                    require(
                        p.blocks == [1, group]
                            && n.inputs.get(2) == Some(&p.scales)
                            && n.inputs.get(3) == Some(&p.zeros),
                        "Native linear group size or parameter identity disagrees with quantization",
                    )?;
                } else {
                    require(
                        n.op == NativeWeightOnlyLinear && weight.shape[1].literal() == Some(group),
                        "Native linear group size disagrees with per-row quantization",
                    )?;
                }
            }
            FullyConnected | WeightOnlyLinear => require(
                rank > 0 && g.values[&n.inputs[1]].tensor.shape.len() == 2,
                "Invalid linear ranks",
            )?,
            Transpose => {
                require(
                    a.integers.len() == rank
                        && a.integers.iter().copied().collect::<BTreeSet<_>>()
                            == (0..rank as i64).collect(),
                    "Invalid transpose permutation",
                )?;
            }
            Slice => require(
                a.lengths.len() == rank && (a.starts.len() == rank || a.integers.len() == rank),
                "Slice start rank mismatch",
            )?,
            Split => {
                axis(a.axis, rank)?;
                require(
                    a.lengths.len() == n.outputs.len(),
                    "Split result length mismatch",
                )?;
            }
            FuseDims => {
                axis(a.axis, rank)?;
                require(
                    a.integers
                        .first()
                        .is_some_and(|v| *v > 0 && *v <= rank as i64),
                    "Invalid fused dimension count",
                )?;
            }
            SplitDim => {
                axis(a.axis, rank)?;
                require(!a.shape.is_empty(), "Missing split dimensions")?;
            }
            Concat | Stack => {
                axis(a.axis, rank + usize::from(n.op == Stack))?;
                require(
                    n.inputs
                        .iter()
                        .all(|x| g.values[x].tensor.shape.len() == rank),
                    "Concat/stack rank mismatch",
                )?;
            }
            ExpandDims => {
                let new_rank = rank + a.axes.len();
                let axes = a
                    .axes
                    .iter()
                    .map(|x| axis(*x, new_rank))
                    .collect::<Result<BTreeSet<_>>>()?;
                require(axes.len() == a.axes.len(), "Duplicate inserted axis")?;
            }
            BroadcastLike | SliceLike => {
                for ax in &a.axes {
                    axis(*ax, rank)?;
                    axis(*ax, g.values[&n.inputs[1]].tensor.shape.len())?;
                }
            }
            Gather | Unstack | EvenSplit | ResourceAppend | ResourceView => {
                axis(a.axis, rank)?;
            }
            Sdpa => {
                let s = a
                    .attention
                    .as_ref()
                    .ok_or_else(|| Error::invalid("Missing attention contract"))?;
                require(
                    rank == 4
                        && n.inputs[..3]
                            .iter()
                            .all(|x| g.values[x].tensor.shape.len() == 4),
                    "Attention requires rank four",
                )?;
                require(s.mask == 0 || n.inputs.len() == 4, "Attention mask missing")?;
                require((0..=2).contains(&s.mask), "Invalid attention mask kind")?;
                let q = &g.values[&n.inputs[0]].tensor.shape;
                let k = &g.values[&n.inputs[1]].tensor.shape;
                require(
                    q[1].literal() == Some(s.heads.len() as i64)
                        && s.heads
                            .iter()
                            .all(|h| *h >= 0 && k[1].literal().is_some_and(|k| *h < k)),
                    "Invalid attention head map",
                )?;
            }
            Conv2D | DepthwiseConv2D | AveragePool2D | MaxPool2D => {
                let s = a
                    .spatial
                    .as_ref()
                    .ok_or_else(|| Error::invalid("Missing spatial contract"))?;
                require(
                    rank == 4
                        && s.strides.len() == 2
                        && s.dilations.len() == 2
                        && s.strides.iter().chain(&s.dilations).all(|x| *x > 0),
                    "Invalid spatial geometry",
                )?;
            }
            _ => {}
        }
        let inferred = g.infer(n)?;
        for (name, tensor) in n.outputs.iter().zip(inferred) {
            let actual = &g.values[name].tensor;
            require(
                actual.dtype == tensor.dtype
                    && actual.shape.len() == tensor.shape.len()
                    && !actual.shape.iter().zip(&tensor.shape).any(
                        |(a, b)| matches!((a.literal(),b.literal()),(Some(x),Some(y)) if x!=y),
                    ),
                format!("Invalid result contract for {:?}: {name}", n.op),
            )?;
        }
    }
    for x in &g.outputs {
        require(
            available.contains(x),
            format!("Unproduced graph output {x}"),
        )?;
    }
    for x in &g.completions {
        require(tokens.contains(x), "Undefined public completion")?;
    }
    for f in g.functions.values() {
        graph(f, depth + 1)?;
    }
    Ok(())
}

pub(super) fn operands(n: &Node) -> Result<()> {
    use Op::*;
    let min = match n.op {
        ShapeTensor => 0,
        Call => 0,
        Concat | Stack => 1,
        Select => 3,
        GatedDeltaRule => 7,
        CausalDepthwiseConv => 3,
        NativeWeightOnlyLinear | BlockwiseFullyConnected => 4,
        Sdpa => 3,
        Add
        | Sub
        | Mul
        | Div
        | Minimum
        | Maximum
        | Pow
        | Prelu
        | Less
        | LessEqual
        | Greater
        | GreaterEqual
        | Equal
        | NotEqual
        | Matmul
        | Dot
        | DynamicMatmul
        | FullyConnected
        | WeightOnlyLinear
        | Gather
        | ResourceAppend
        | QuantizeTensor
        | DequantizeTensor
        | QuantizationParameters
        | WithQuantization
        | BroadcastLike
        | SliceLike
        | Conv2D
        | DepthwiseConv2D => 2,
        _ => 1,
    };
    require(
        n.inputs.len() >= min,
        format!("Missing operand for {:?}", n.op),
    )?;
    require(!n.outputs.is_empty(), "Operation has no result")?;
    if matches!(
        n.op,
        DynamicQuantization | GatedDeltaRule | CausalDepthwiseConv
    ) {
        require(n.outputs.len() == 2, "Operation needs two results")?;
    }
    Ok(())
}
