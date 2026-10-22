// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
//! The surface vocabulary shares argument kinds with the validated wire schema.
use crate::plan::{Arg, Op, RawCommand, INVALID};

pub(super) fn snake(name: &str) -> String {
    let bytes = name.as_bytes();
    let mut out = String::new();
    for (i, &b) in bytes.iter().enumerate() {
        if b.is_ascii_uppercase()
            && i > 0
            && !bytes[i - 1].is_ascii_digit()
            && (bytes[i - 1].is_ascii_lowercase()
                || bytes.get(i + 1).is_some_and(u8::is_ascii_lowercase))
        {
            out.push('_');
        }
        out.push((b as char).to_ascii_lowercase());
    }
    out
}
pub(super) fn output(op: Op, field: &str) -> bool {
    !op.declares_tensor()
        && (field == "output"
            || op == Op::Split && field == "outputs"
            || op == Op::DynamicQuantization && field == "scale")
        || op == Op::CausalDepthwiseConv && field == "next_history"
}
pub(super) fn results(c: &RawCommand) -> Vec<i64> {
    c.op.fields()
        .iter()
        .zip(&c.args)
        .filter(|(f, _)| output(c.op, f))
        .flat_map(|(_, a)| match a {
            Arg::Int(n) => vec![*n],
            Arg::Ints(ns) => ns.clone(),
            _ => vec![],
        })
        .collect()
}
pub(super) fn inputs(c: &RawCommand) -> Vec<i64> {
    c.op.fields()
        .iter()
        .zip(c.op.signature())
        .zip(&c.args)
        .filter(|((f, _), _)| !output(c.op, f))
        .flat_map(|((_, k), a)| match (*k, a) {
            ("id" | "operand" | "optional", Arg::Int(n) | Arg::Native(n)) if *n != INVALID => {
                vec![*n]
            }
            ("ids", Arg::Ints(ns)) => ns.clone(),
            _ => vec![],
        })
        .collect()
}
pub(super) fn surface(c: &RawCommand) -> String {
    match c.op {
        Op::Binary => match &c.args[0] {
            Arg::Binary(s) => match s.as_str() {
                "multiply" => "mul".into(),
                "subtract" => "sub".into(),
                "divide" => "div".into(),
                "max" => "maximum".into(),
                "min" => "minimum".into(),
                _ => s.clone(),
            },
            _ => unreachable!(),
        },
        Op::Compare => match &c.args[0] {
            Arg::Text(s) => s.clone(),
            _ => unreachable!(),
        },
        Op::Unary => match &c.args[0] {
            Arg::Unary(s) => s.clone(),
            _ => unreachable!(),
        },
        Op::Reduce => match &c.args[0] {
            Arg::Reduce(s) => format!("reduce_{s}"),
            _ => unreachable!(),
        },
        _ => snake(c.op.name()),
    }
}
pub(super) fn lookup(name: &str) -> Option<(Op, Option<Arg>)> {
    let binary = match name {
        "add" => Some("add"),
        "mul" | "multiply" => Some("multiply"),
        "sub" | "subtract" => Some("subtract"),
        "div" | "divide" => Some("divide"),
        "maximum" => Some("max"),
        "minimum" => Some("min"),
        "pow" => Some("pow"),
        "leaky_relu" => Some("leaky_relu"),
        _ => None,
    };
    if let Some(s) = binary {
        return Some((Op::Binary, Some(Arg::Binary(s.into()))));
    }
    if ["less", "less_equal", "greater", "greater_equal", "equal", "not_equal"]
        .contains(&name)
    {
        return Some((Op::Compare, Some(Arg::Text(name.into()))));
    }
    if [
        "abs",
        "log",
        "exp",
        "erf",
        "tanh",
        "sin",
        "cos",
        "sqrt",
        "rsqrt",
        "square",
        "negate",
        "round",
        "hardswish",
        "sigmoid",
    ]
    .contains(&name)
    {
        return Some((Op::Unary, Some(Arg::Unary(name.into()))));
    }
    if let Some(s) = name.strip_prefix("reduce_") {
        if ["sum", "max", "min", "min_max", "sum_squared"].contains(&s) {
            return Some((Op::Reduce, Some(Arg::Reduce(s.into()))));
        }
    }
    Op::all()
        .iter()
        .find(|op| name == op.name() || name == snake(op.name()))
        .map(|op| (*op, None))
}
pub(super) fn profile(c: &RawCommand, names: &[String]) -> Vec<Arg> {
    let operation = surface(c);
    let kind = match c.op {
        Op::Binary => match operation.as_str() {
            "maximum" => "core.maximum".into(),
            "minimum" => "core.minimum".into(),
            _ => format!("core.{operation}"),
        },
        Op::Unary => format!(
            "core.{}",
            if operation == "negate" {
                "neg"
            } else {
                &operation
            }
        ),
        Op::Reduce => format!("ynn.{operation}"),
        Op::Dot => "ynn.dot".into(),
        Op::DequantizeTensor => "ynn.dequantize".into(),
        Op::QuantizeTensor => "ynn.quantize".into(),
        Op::SplitDim
        | Op::FuseDims
        | Op::Append
        | Op::View
        | Op::Polynomial
        | Op::DynamicQuantization => format!("ynn.{operation}"),
        Op::ShapeProduct => "ynn.get_shape".into(),
        Op::Mask => "ynn.scheduled_mask".into(),
        Op::ExpandDims | Op::Squeeze | Op::Reshape => "core.reshape".into(),
        Op::DynamicallyQuantizedMatmul => "ynn.dynamic_matmul".into(),
        Op::Convert => "core.cast".into(),
        Op::Conv2D => if matches!(c.args[8], Arg::Bool(true)) {
            "core.depthwise_conv2d"
        } else {
            "core.conv2d"
        }
        .into(),
        Op::Pool2D => if matches!(c.args[5], Arg::Bool(true)) {
            "core.average_pool2d"
        } else {
            "core.max_pool2d"
        }
        .into(),
        _ => format!("core.{operation}"),
    };
    let ins = inputs(c);
    let input_names = ins.iter().map(|n| names[*n as usize].clone()).collect();
    vec![
        Arg::Text("Compute".into()),
        Arg::Text(kind),
        Arg::Ints(ins),
        Arg::Ints(results(c)),
        Arg::Texts(input_names),
    ]
}
