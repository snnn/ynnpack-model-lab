// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
//! Types used after decoding the positional wire format.
use super::{float, invalid, Arg, Data, Encoding, Expr, Result, INVALID};

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub(crate) struct ValueId(pub u32);
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub(crate) struct SymbolId(pub u32);
#[derive(Debug, Clone)]
pub(crate) enum Operand {
    Value(ValueId),
    PackedNative(ValueId),
}

pub(super) trait Wire: Sized {
    fn decode(arg: Arg) -> Result<Self>;
    fn encode(&self) -> Arg;
}
macro_rules! direct {
    ($ty:ty, $variant:ident) => {
        impl Wire for $ty {
            fn decode(arg: Arg) -> Result<Self> {
                if let Arg::$variant(v) = arg {
                    Ok(v)
                } else {
                    Err(invalid(concat!("Expected ", stringify!($variant))))
                }
            }
            fn encode(&self) -> Arg {
                Arg::$variant(self.clone())
            }
        }
    };
}
direct!(i64, Int);
direct!(String, Text);
direct!(bool, Bool);
direct!(Vec<i64>, Ints);
direct!(Vec<String>, Texts);
direct!(Expr, Expr);
direct!(Vec<Expr>, Exprs);
direct!(Option<Data>, Data);
direct!(Encoding, Encoding);

impl Wire for ValueId {
    fn decode(arg: Arg) -> Result<Self> {
        let n = i64::decode(arg)?;
        if n < 0 || n >= INVALID {
            return Err(invalid("Invalid value ID"));
        }
        Ok(Self(n as u32))
    }
    fn encode(&self) -> Arg {
        Arg::Int(self.0.into())
    }
}
impl Wire for Option<ValueId> {
    fn decode(arg: Arg) -> Result<Self> {
        if matches!(arg, Arg::Int(INVALID)) {
            Ok(None)
        } else {
            ValueId::decode(arg).map(Some)
        }
    }
    fn encode(&self) -> Arg {
        Arg::Int(self.map_or(INVALID, |id| id.0.into()))
    }
}
impl Wire for Operand {
    fn decode(arg: Arg) -> Result<Self> {
        match arg {
            Arg::Native(n) => ValueId::decode(Arg::Int(n)).map(Self::PackedNative),
            a => ValueId::decode(a).map(Self::Value),
        }
    }
    fn encode(&self) -> Arg {
        match self {
            Self::Value(v) => v.encode(),
            Self::PackedNative(v) => Arg::Native(v.0.into()),
        }
    }
}
impl Wire for usize {
    fn decode(arg: Arg) -> Result<Self> {
        usize::try_from(i64::decode(arg)?).map_err(|_| invalid("Size overflow"))
    }
    fn encode(&self) -> Arg {
        Arg::Int(*self as i64)
    }
}
impl Wire for Vec<ValueId> {
    fn decode(arg: Arg) -> Result<Self> {
        Vec::<i64>::decode(arg)?
            .into_iter()
            .map(|v| ValueId::decode(Arg::Int(v)))
            .collect()
    }
    fn encode(&self) -> Arg {
        Arg::Ints(self.iter().map(|v| v.0.into()).collect())
    }
}
impl Wire for Vec<usize> {
    fn decode(arg: Arg) -> Result<Self> {
        Vec::<i64>::decode(arg)?
            .into_iter()
            .map(|v| usize::try_from(v).map_err(|_| invalid("Size overflow")))
            .collect()
    }
    fn encode(&self) -> Arg {
        Arg::Ints(self.iter().map(|&v| v as i64).collect())
    }
}
impl Wire for f64 {
    fn decode(arg: Arg) -> Result<Self> {
        if let Arg::Float(bits) = arg {
            float(&bits)
        } else {
            Err(invalid("Expected float"))
        }
    }
    fn encode(&self) -> Arg {
        Arg::Float(format!("{:016x}", self.to_bits()))
    }
}
impl Wire for Vec<f64> {
    fn decode(arg: Arg) -> Result<Self> {
        if let Arg::Floats(bits) = arg {
            bits.iter().map(|v| float(v)).collect()
        } else {
            Err(invalid("Expected float vector"))
        }
    }
    fn encode(&self) -> Arg {
        Arg::Floats(
            self.iter()
                .map(|v| format!("{:016x}", v.to_bits()))
                .collect(),
        )
    }
}

macro_rules! enumeration {
    ($name:ident, $arg:ident, {$($variant:ident => $wire:literal),* $(,)?}) => {
        #[derive(Debug, Clone, Copy, PartialEq, Eq)]
        pub(crate) enum $name { $($variant),* }
        impl Wire for $name {
            fn decode(arg: Arg) -> Result<Self> {
                if let Arg::$arg(s) = arg {
                    match s.as_str() { $($wire => Ok(Self::$variant),)* _ => Err(invalid(concat!("Unknown ", stringify!($name)))) }
                } else { Err(invalid(concat!("Expected ", stringify!($name)))) }
            }
            fn encode(&self) -> Arg { Arg::$arg(match self { $(Self::$variant => $wire,)* }.into()) }
        }
    }
}
enumeration!(Dtype, Dtype, { Bf16 => "bf16", Fp16 => "fp16", Fp32 => "fp32", Fp64 => "fp64", Int2 => "int2", Int4 => "int4", Int8 => "int8", Uint8 => "uint8", Int32 => "int32" });
enumeration!(Binary, Binary, { Add => "add", Subtract => "subtract", Multiply => "multiply", Divide => "divide", Max => "max", Min => "min", Pow => "pow", LeakyRelu => "leaky_relu" });
enumeration!(Comparison, Text, { Less => "less", LessEqual => "less_equal", Greater => "greater", GreaterEqual => "greater_equal", Equal => "equal", NotEqual => "not_equal" });
enumeration!(Unary, Unary, { Abs => "abs", Exp => "exp", Erf => "erf", Tanh => "tanh", Sin => "sin", Cos => "cos", Sqrt => "sqrt", Rsqrt => "rsqrt", Square => "square", Negate => "negate", Round => "round", Hardswish => "hardswish" });
enumeration!(Reduce, Reduce, { Sum => "sum", Max => "max", Min => "min", MinMax => "min_max", SumSquared => "sum_squared" });
enumeration!(Relation, Text, { Equal => "eq", LessEqual => "le" });
enumeration!(GuardMode, Text, { Bounds => "bounds", Ordinary => "ordinary", Checked => "checked" });
enumeration!(Route, Text, { Copy => "copy", Transpose => "transpose", Reshape => "reshape", Squeeze => "squeeze", ExpandDims => "expand_dims", Reverse => "reverse", Slice => "slice", Tile => "tile", Pad => "pad", Select => "select", Gather => "gather", Concat => "concat", Stack => "stack", BroadcastTo => "broadcast_to", SliceLike => "slice_like", BroadcastLike => "broadcast_like", FuseDims => "fuse_dims", SplitDim => "split_dim", EvenSplit => "even_split", Unstack => "unstack" });

#[derive(Debug)]
pub(crate) enum SymbolSource {
    Axis {
        tensor: ValueId,
        axis: usize,
    },
    Parameter {
        name: String,
        lower: i64,
        upper: i64,
    },
    InstanceParameter {
        name: String,
        lower: i64,
        upper: i64,
    },
}
