// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
//! Typed construction commands. Positional arguments exist only at the wire boundary.
use super::types::*;
use super::{invalid, Arg, Data, Encoding, Expr, RawCommand, Result};
use serde::Serialize;

macro_rules! commands {
    ($($op:ident { $($field:ident : $ty:ty => $kind:literal),* $(,)? }),* $(,)?) => {
        #[derive(Debug, Clone, Copy, PartialEq, Eq, Serialize)]
        pub(crate) enum Op { $($op,)* Symbol }
        impl Op {
            pub(crate) fn all() -> &'static [Self] { &[$(Self::$op,)* Self::Symbol] }
            pub(crate) fn name(self) -> &'static str { match self { $(Self::$op => stringify!($op),)* Self::Symbol => "Symbol" } }
            pub(crate) fn signature(self) -> &'static [&'static str] { match self { $(Self::$op => &[$($kind),*],)* Self::Symbol => &[] } }
            pub(crate) fn fields(self) -> &'static [&'static str] { match self { $(Self::$op => &[$(stringify!($field)),*],)* Self::Symbol => &[] } }
            pub(crate) fn from_name(name: &str) -> Option<Self> {
                match name { $(stringify!($op) => Some(Self::$op),)* "Symbol" => Some(Self::Symbol), _ => None }
            }
            pub(crate) fn declares_tensor(self) -> bool {
                matches!(self, Self::Tensor | Self::ConstantOutput | Self::PackedTensor | Self::PackedConstantOutput)
            }
        }
        #[derive(Debug)]
        pub(crate) enum Command {
            $($op { $($field: $ty),* },)*
            Symbol { id: SymbolId, lower: i64, upper: i64, source: SymbolSource },
        }
        impl Command {
            pub(super) fn decode(raw: RawCommand) -> Result<Self> {
                let mut args = raw.args.into_iter();
                let mut next = || args.next().ok_or_else(|| invalid("Missing command argument"));
                let command = match raw.op {
                    $(Op::$op => Self::$op { $($field: <$ty>::decode(next()?)?),* },)*
                    Op::Symbol => {
                        let id = SymbolId(u32::try_from(i64::decode(next()?)?).map_err(|_| invalid("Invalid symbol ID"))?);
                        let kind = String::decode(next()?)?;
                        let lower = i64::decode(next()?)?;
                        let upper = i64::decode(next()?)?;
                        let source = match kind.as_str() {
                            "Axis" => SymbolSource::Axis { tensor: ValueId::decode(next()?)?, axis: usize::decode(next()?)? },
                            "Parameter" => SymbolSource::Parameter { name: String::decode(next()?)?, lower: i64::decode(next()?)?, upper: i64::decode(next()?)? },
                            "InstanceParameter" => SymbolSource::InstanceParameter { name: String::decode(next()?)?, lower: i64::decode(next()?)?, upper: i64::decode(next()?)? },
                            _ => return Err(invalid("Unknown symbol source")),
                        };
                        Self::Symbol { id, lower, upper, source }
                    }
                };
                if args.next().is_some() { return Err(invalid("Extra command arguments")); }
                Ok(command)
            }
            // C ABI marshaling retains the version-1 wire vocabulary. Callers
            // cannot construct this stream without consuming a validated plan.
            pub(crate) fn wire(&self) -> RawCommand {
                match self {
                    $(Self::$op { $($field),* } => RawCommand { op: Op::$op, args: vec![$($field.encode()),*] },)*
                    Self::Symbol { id, lower, upper, source } => {
                        let (kind, mut tail) = match source {
                            SymbolSource::Axis { tensor, axis } => ("Axis", vec![tensor.encode(), axis.encode()]),
                            SymbolSource::Parameter { name, lower, upper } => ("Parameter", vec![name.encode(), lower.encode(), upper.encode()]),
                            SymbolSource::InstanceParameter { name, lower, upper } => ("InstanceParameter", vec![name.encode(), lower.encode(), upper.encode()]),
                        };
                        let mut args = vec![Arg::Int(id.0.into()), Arg::Text(kind.into()), lower.encode(), upper.encode()];
                        args.append(&mut tail);
                        RawCommand { op: Op::Symbol, args }
                    }
                }
            }
        }
    };
}

commands! {
    Tensor { id: ValueId => "id", name: String => "text", dtype: Dtype => "dtype", dims: Vec<usize> => "sizes", flags: i64 => "int", data: Option<Data> => "data" },
    ConstantOutput { id: ValueId => "id", name: String => "text", dtype: Dtype => "dtype", dims: Vec<usize> => "sizes", data: Option<Data> => "data" },
    PackedTensor { id: ValueId => "id", name: String => "text", bits: usize => "size", dims: Vec<usize> => "sizes", flags: i64 => "int", data: Option<Data> => "data" },
    PackedConstantOutput { id: ValueId => "id", name: String => "text", bits: usize => "size", dims: Vec<usize> => "sizes", data: Option<Data> => "data" },
    PackedRoute { route: Route => "text", inputs: Vec<ValueId> => "ids", output: ValueId => "id", shape: Vec<Expr> => "exprs", attributes: Vec<i64> => "ints", starts: Vec<Expr> => "exprs", axis: i64 => "int", mode: i64 => "int" },
    ParameterExpand { input: ValueId => "id", like: ValueId => "id", output: ValueId => "id", axes: Vec<i64> => "ints", blocks: Vec<i64> => "ints" },
    MappedDequantize { input: ValueId => "id", scale: ValueId => "id", zero: ValueId => "id", output: ValueId => "id", axes: Vec<i64> => "ints", blocks: Vec<i64> => "ints" },
    Sdpa { query: ValueId => "id", key: ValueId => "id", value: ValueId => "id", mask: Option<ValueId> => "optional", output: ValueId => "id", head_map: Vec<i64> => "ints", scale: f64 => "float", mask_kind: i64 => "int", causal: bool => "bool", window: i64 => "int", query_position: Expr => "expr", key_position: Expr => "expr", queries: Expr => "expr", keys: Expr => "expr", all_masked_nan: bool => "bool" },
    GatedDeltaRule { query: ValueId => "id", key: ValueId => "id", value: ValueId => "id", log_decay: ValueId => "id", beta: ValueId => "id", state: ValueId => "id", valid_rows: ValueId => "id", output: ValueId => "id", next_state: ValueId => "id", head_map: Vec<i64> => "ints", scale: f64 => "float" },
    CausalDepthwiseConv { input: ValueId => "id", filter: ValueId => "id", history: ValueId => "id", output: ValueId => "id", next_history: ValueId => "id", valid_rows: Expr => "expr", silu: bool => "bool" },
    WeightOnlyLinear { input: ValueId => "id", weight: ValueId => "id", scales: ValueId => "id", zero: ValueId => "id", output: ValueId => "id", group: usize => "size" },
    BlockwiseFullyConnected { input: ValueId => "id", weight: ValueId => "id", scales: ValueId => "id", zero: ValueId => "id", output: ValueId => "id", group: usize => "size" },
    Reverse { input: ValueId => "id", output: ValueId => "id", axes: Vec<i64> => "ints" },
    Tile { input: ValueId => "id", output: ValueId => "id", multiples: Vec<usize> => "sizes" },
    Select { condition: ValueId => "id", yes: ValueId => "id", no: ValueId => "id", output: ValueId => "id", shape: Vec<Expr> => "exprs" },
    Compare { operator: Comparison => "text", lhs: ValueId => "id", rhs: ValueId => "id", output: ValueId => "id", shape: Vec<Expr> => "exprs" },
    Gather { input: ValueId => "id", indices: ValueId => "id", output: ValueId => "id", axis: i64 => "int" },
    Stack { inputs: Vec<ValueId> => "ids", output: ValueId => "id", axis: i64 => "int" },
    Split { input: ValueId => "id", outputs: Vec<ValueId> => "ids", axis: i64 => "int", unstack: bool => "bool" },
    DynamicallyQuantizedMatmul { lhs: ValueId => "id", rhs: ValueId => "id", output: ValueId => "id", scale: f64 => "float", adjoint_rhs: bool => "bool", head: i64 => "int" },
    ShapeTensor { output: ValueId => "id", elements: Vec<Expr> => "exprs", scalar: bool => "bool" },
    BindScalarParameter { tensor: ValueId => "id", name: String => "text" },
    InputShape { tensor: ValueId => "id", shape: Vec<Expr> => "exprs" },
    ResultShape { tensor: ValueId => "id", shape: Vec<Expr> => "exprs" },
    PackedStrides { value: ValueId => "id", strides: Vec<Expr> => "exprs" },
    Resource { owner: ValueId => "id", name: String => "text", axis: i64 => "int", entry_extent: Expr => "expr", encoding: Encoding => "encoding" },
    BeginProfileOperation { name: String => "text", kind: String => "text", inputs: Vec<ValueId> => "ids", outputs: Vec<ValueId> => "ids", input_names: Vec<String> => "texts" },
    EndProfileOperation {  },
    BeginOperation { waits: Vec<String> => "texts" },
    EndOperation { defines: Vec<String> => "texts", outputs: Vec<ValueId> => "ids" },
    CompletionOutput { tokens: Vec<String> => "texts" },
    Binary { operator: Binary => "binary", lhs: ValueId => "id", rhs: ValueId => "id", output: ValueId => "id" },
    Unary { operator: Unary => "unary", input: ValueId => "id", output: ValueId => "id" },
    Matmul { lhs: ValueId => "id", rhs: ValueId => "id", output: ValueId => "id", adjoint_lhs: bool => "bool", adjoint_rhs: bool => "bool" },
    Dot { lhs: Operand => "operand", rhs: Operand => "operand", bias: Option<ValueId> => "optional", output: ValueId => "id", contraction_dims: usize => "size" },
    Quantize { input: ValueId => "id", output: ValueId => "id", scale: f64 => "float", zero: i64 => "int" },
    Dequantize { input: Operand => "operand", output: ValueId => "id", scale: f64 => "float", zero: i64 => "int" },
    QuantizeTensor { input: ValueId => "id", zero: Option<ValueId> => "optional", scale: ValueId => "id", output: ValueId => "id" },
    DequantizeTensor { input: ValueId => "id", zero: Option<ValueId> => "optional", scale: ValueId => "id", output: ValueId => "id" },
    DynamicQuantization { input: ValueId => "id", output: ValueId => "id", scale: ValueId => "id" },
    FuseDims { input: ValueId => "id", output: ValueId => "id", axis: i64 => "int", count: i64 => "int" },
    SplitDim { input: ValueId => "id", output: ValueId => "id", axis: i64 => "int", dims: Vec<usize> => "sizes" },
    ShapeProduct { input: ValueId => "id", output: ValueId => "id", axes: Vec<i64> => "ints" },
    Polynomial { input: ValueId => "id", output: ValueId => "id", coefficients: Vec<f64> => "floats" },
    Reduce { operator: Reduce => "reduce", input: ValueId => "id", output: ValueId => "id", axes: Vec<i64> => "ints", keep_dims: bool => "bool" },
    Softmax { input: ValueId => "id", output: ValueId => "id", beta: f64 => "float" },
    Reshape { input: ValueId => "id", output: ValueId => "id", dims: Vec<usize> => "sizes" },
    Transpose { input: ValueId => "id", output: ValueId => "id", permutation: Vec<i64> => "ints" },
    Slice { input: ValueId => "id", output: ValueId => "id", starts: Vec<i64> => "ints", sizes: Vec<i64> => "ints" },
    Concat { inputs: Vec<ValueId> => "ids", output: ValueId => "id", axis: i64 => "int" },
    View { input: ValueId => "id", output: ValueId => "id", axis: i64 => "int", begin: Expr => "expr", end: Expr => "expr" },
    Append { owner: ValueId => "id", input: ValueId => "id", output: ValueId => "id", axis: i64 => "int", position: Expr => "expr", rows: Expr => "expr" },
    Mask { input: ValueId => "id", output: ValueId => "id", position: Expr => "expr", begin: Expr => "expr", window: i64 => "int", scheduled: bool => "bool" },
    Conv2D { input: ValueId => "id", filter: ValueId => "id", bias: Option<ValueId> => "optional", output: ValueId => "id", kernel: Vec<usize> => "sizes", strides: Vec<usize> => "sizes", dilations: Vec<usize> => "sizes", same: bool => "bool", depthwise: bool => "bool", input_channels: usize => "size", multiplier: usize => "size" },
    Pool2D { input: ValueId => "id", output: ValueId => "id", kernel: Vec<usize> => "sizes", strides: Vec<usize> => "sizes", same: bool => "bool", average: bool => "bool" },
    Pad { input: ValueId => "id", fill: Option<ValueId> => "optional", output: ValueId => "id", before: Vec<Expr> => "exprs", after: Vec<Expr> => "exprs", mode: i64 => "int" },
    Copy { input: ValueId => "id", output: ValueId => "id" },
    ExpandDims { input: ValueId => "id", output: ValueId => "id", axes: Vec<i64> => "ints" },
    Squeeze { input: ValueId => "id", output: ValueId => "id", axes: Vec<i64> => "ints" },
    Broadcast { input: ValueId => "id", output: ValueId => "id", dims: Vec<usize> => "sizes" },
    SymbolicBroadcast { input: ValueId => "id", output: ValueId => "id", shape: Vec<Expr> => "exprs" },
    SymbolicReshape { input: ValueId => "id", output: ValueId => "id", shape: Vec<Expr> => "exprs" },
    SymbolicSlice { input: ValueId => "id", output: ValueId => "id", starts: Vec<Expr> => "exprs", lengths: Vec<Expr> => "exprs" },
    BroadcastLike { input: ValueId => "id", like: ValueId => "id", output: ValueId => "id", axes: Vec<i64> => "ints" },
    SliceLike { input: ValueId => "id", like: ValueId => "id", output: ValueId => "id", axes: Vec<i64> => "ints" },
    Convert { input: ValueId => "id", output: ValueId => "id" },
    Mean { input: ValueId => "id", output: ValueId => "id", axes: Vec<i64> => "ints", keep_dims: bool => "bool" },
    Gelu { input: ValueId => "id", output: ValueId => "id", approximate: bool => "bool" },
    Guard { lhs: Expr => "expr", rhs: Expr => "expr", relation: Relation => "text", message: String => "text", mode: GuardMode => "text" },
}
