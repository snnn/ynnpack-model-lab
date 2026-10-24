// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
//! Versioned construction data. Validation happens before any native mutation.
#![allow(dead_code)]
use crate::{Error, Result};
use serde::{Serialize, Deserialize};
use std::collections::{HashMap, HashSet};
use std::path::{Component, Path};
mod commands;
mod encoding;
pub(crate) use encoding::Encoding;
#[cfg(test)]
mod tests;
mod types;
pub(crate) use commands::{Command, Op};

pub(crate) const INVALID: i64 = u32::MAX as i64;
pub(crate) const MAX_VALUES: usize = 100_000;
pub(crate) const MAX_COMMANDS: usize = 500_000;
pub(crate) const MAX_FILE: u64 = 128 * 1024 * 1024;

#[derive(Debug, Clone, PartialEq, Eq, Hash, Serialize, Deserialize)]
#[serde(rename_all = "snake_case")]
pub enum Expr {
    Known(i64),
    Symbol(u32),
    Add(Vec<Expr>),
    Mul(Vec<Expr>),
    Min(Vec<Expr>),
    Max(Vec<Expr>),
    FloorDiv(Vec<Expr>),
    CeilDiv(Vec<Expr>),
}
#[derive(Debug, Clone, PartialEq, Eq, Serialize)]
pub(crate) struct Data {
    pub path: String,
    pub bytes: usize,
    pub sha256: String,
}
#[derive(Debug, Clone, PartialEq, Eq, Serialize)]
#[serde(rename_all = "snake_case")]
pub(crate) enum Arg {
    Int(i64),
    Native(i64),
    Text(String),
    Bool(bool),
    Float(String),
    Ints(Vec<i64>),
    Texts(Vec<String>),
    Floats(Vec<String>),
    Dtype(String),
    Binary(String),
    Unary(String),
    Reduce(String),
    Expr(Expr),
    Exprs(Vec<Expr>),
    Data(Option<Data>),
    Encoding(Encoding),
}
#[derive(Debug, Clone, PartialEq, Eq, Serialize)]
pub(crate) struct RawCommand {
    pub op: Op,
    pub args: Vec<Arg>,
}
#[derive(Debug, Clone, PartialEq, Eq, Serialize)]
pub(crate) struct Plan {
    pub format: String,
    pub version: u32,
    pub resource_contract: u32,
    pub completion_contract: u32,
    pub value_count: usize,
    pub commands: Vec<RawCommand>,
}
/// Source frontends can attach a location without parsing an error message.
pub(crate) struct ValidationError {
    pub command: Option<usize>,
    pub error: Error,
}
impl From<Error> for ValidationError {
    fn from(error: Error) -> Self {
        Self {
            command: None,
            error,
        }
    }
}
/// Only validation can create a plan accepted by native construction.
pub(crate) struct ValidatedPlan {
    value_count: usize,
    commands: Vec<Command>,
}
impl ValidatedPlan {
    pub(crate) fn from_bytes(bytes: &[u8]) -> Result<Self> {
        require(
            bytes.len() as u64 <= MAX_FILE,
            "Graph artifact exceeds size limit",
        )?;
        let source =
            std::str::from_utf8(bytes).map_err(|_| invalid("Graph source must be UTF-8"))?;
        crate::plan_text::parse(source)?.into_validated()
    }
    #[cfg(feature = "native-tests")]
    pub(crate) fn read(path: &Path) -> Result<Self> {
        Plan::read(path)?.into_validated()
    }
    pub(crate) fn value_count(&self) -> usize {
        self.value_count
    }
    pub(crate) fn commands(&self) -> &[Command] {
        &self.commands
    }
    pub(crate) fn scalar_names(&self) -> std::collections::BTreeSet<&str> {
        use types::SymbolSource;
        self.commands.iter().filter_map(|c|match c {
            Command::Symbol{source:SymbolSource::Parameter{name,..},..}=>Some(name.as_str()),
            Command::Symbol{source:SymbolSource::InstanceParameter{name,lower,upper},..} if lower!=upper=>Some(name.as_str()),
            Command::BindScalarParameter{name,..}=>Some(name.as_str()),_=>None,
        }).collect()
    }
    pub(crate) fn require_tensor(
        &self,
        name: &str,
        dtype: &str,
        dims: &[Option<i64>],
        flags: i64,
    ) -> Result<()> {
        use types::{Dtype, Wire};
        let expected_type = if matches!(dtype, "int2" | "int4") { None }
            else { Some(Dtype::decode(Arg::Dtype(dtype.into()))?) };
        for command in &self.commands {
            let (tensor, actual_name, shape, actual_flags, matches_type) = match command {
                Command::Tensor { id, name, dtype: actual, dims, flags, .. } =>
                    (id, name, dims, flags, Some(*actual) == expected_type),
                Command::PackedTensor { id, name, bits, dims, flags, .. } =>
                    (id, name, dims, flags, dtype == format!("int{bits}")),
                _ => continue,
            };
            if actual_name == name {
                return require(matches_type && actual_flags & flags == flags
                    && dims.len() == shape.len()
                    && dims.iter().zip(shape).enumerate().all(|(axis, (want, &got))| want.is_none_or(|d| {
                        if d < 0 { return false; }
                        if d as usize == got { return true; }
                        // Zero is the native placeholder for a dynamic input axis.
                        // Accept a declared input-axis symbol within its checked bounds.
                        got == 0 && self.commands.iter().any(|c| match c {
                            Command::InputShape { tensor: id, shape } if id == tensor => {
                                if let Some(Expr::Symbol(symbol)) = shape.get(axis) {
                                    self.commands.iter().any(|c| matches!(c,
                                        Command::Symbol { id, lower, upper, source: types::SymbolSource::Axis { .. } }
                                        if id.0 == *symbol && *lower <= d && d <= *upper))
                                } else { false }
                            }, _ => false,
                        })
                    })),
                    &format!("Plan tensor contract mismatch: {name}"));
            }
        }
        Err(invalid(format!("Missing model tensor: {name}")))
    }
}
#[derive(Clone)]
struct Value {
    dtype: String,
    dims: Vec<i64>,
    flags: i64,
    ready: bool,
    name: String,
    packed: bool,
}
fn invalid(message: impl Into<String>) -> Error {
    Error::invalid(message)
}
fn require(ok: bool, message: &str) -> Result<()> {
    if ok {
        Ok(())
    } else {
        Err(invalid(message))
    }
}
pub(crate) fn float(bits: &str) -> Result<f64> {
    require(
        bits.len() == 16 && bits.bytes().all(|x| x.is_ascii_hexdigit()),
        "Invalid float bit pattern",
    )?;
    let n = u64::from_str_radix(bits, 16).map_err(|_| invalid("Invalid float bits"))?;
    let n = f64::from_bits(n);
    require(n.is_finite(), "Nonfinite numeric attribute")?;
    Ok(n)
}
fn text_ok(s: &str) -> Result<()> {
    require(
        s.len() <= 16_384 && !s.contains('\0'),
        "Invalid/oversized text",
    )
}
impl Arg {
    pub fn int(&self) -> i64 {
        if let Self::Int(x) | Self::Native(x) = self {
            *x
        } else {
            unreachable!()
        }
    }
    pub fn text(&self) -> &str {
        if let Self::Text(x) = self {
            x
        } else {
            unreachable!()
        }
    }
    pub fn ints(&self) -> &[i64] {
        if let Self::Ints(x) = self {
            x
        } else {
            unreachable!()
        }
    }
    pub fn texts(&self) -> &[String] {
        if let Self::Texts(x) = self {
            x
        } else {
            unreachable!()
        }
    }
    pub(crate) fn check(
        &self,
        kind: &str,
        symbols: &HashMap<u32, (i64, i64)>,
        protected: &HashSet<Expr>,
    ) -> Result<()> {
        match (kind, self) {
            ("int", Self::Int(_)) => {}
            ("id" | "optional" | "operand", Self::Int(x)) | ("operand", Self::Native(x)) => {
                require((0..=INVALID).contains(x), "Invalid value ID")?
            }
            ("size", Self::Int(x)) => require(*x >= 0, "Negative size")?,
            ("text", Self::Text(x)) => text_ok(x)?,
            ("bool", Self::Bool(_)) => {}
            ("float", Self::Float(x)) => {
                float(x)?;
            }
            ("ints" | "ids" | "sizes", Self::Ints(xs)) => {
                require(xs.len() <= 1024, "Oversized integer vector")?;
                for &x in xs {
                    if kind != "ints" {
                        require(
                            x >= 0 && (kind != "ids" || x <= INVALID),
                            "Invalid unsigned vector",
                        )?;
                    }
                }
            }
            ("texts", Self::Texts(xs)) => {
                require(xs.len() <= 1024, "Oversized string vector")?;
                for x in xs {
                    text_ok(x)?;
                }
            }
            ("floats", Self::Floats(xs)) => {
                require(
                    !xs.is_empty() && xs.len() <= 1024,
                    "Invalid coefficient vector",
                )?;
                for x in xs {
                    float(x)?;
                }
            }
            ("dtype", Self::Dtype(x)) => require(
                [
                    "bf16", "fp32", "fp16", "int2", "int4", "int8", "uint8", "int32", "fp64",
                ]
                .contains(&x.as_str()),
                "Unsupported dtype",
            )?,
            ("binary", Self::Binary(x)) => require(
                [
                    "add",
                    "multiply",
                    "subtract",
                    "divide",
                    "max",
                    "min",
                    "pow",
                    "leaky_relu",
                ]
                .contains(&x.as_str()),
                "Unsupported binary operator",
            )?,
            ("unary", Self::Unary(x)) => require(
                [
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
                .contains(&x.as_str()),
                "Unsupported unary operator",
            )?,
            ("reduce", Self::Reduce(x)) => require(
                ["sum", "max", "min", "min_max", "sum_squared"].contains(&x.as_str()),
                "Unsupported reduction",
            )?,
            ("expr", Self::Expr(e)) => {
                e.bounds_in(symbols, &mut 4096, 0, protected, false)?;
            }
            ("exprs" | "elements", Self::Exprs(xs)) => {
                let limit = if kind == "elements" { 1024 } else { 8 };
                require(xs.len() <= limit, "Invalid expression vector length")?;
                for e in xs {
                    e.bounds_in(symbols, &mut 4096, 0, protected, false)?;
                }
            }
            ("encoding", Self::Encoding(e)) => e.validate()?,
            ("data", Self::Data(data)) => {
                if let Some(d) = data {
                    text_ok(&d.path)?;
                    require(
                        d.bytes > 0 && d.bytes <= isize::MAX as usize,
                        "Invalid constant size",
                    )?;
                    require(
                        d.sha256.len() == 64
                            && d.sha256
                                .bytes()
                                .all(|x| x.is_ascii_digit() || (b'a'..=b'f').contains(&x)),
                        "Invalid SHA-256",
                    )?;
                    let path = d.path.strip_prefix("@parameters/").unwrap_or(&d.path);
                    require(
                        !path.is_empty()
                            && Path::new(path)
                                .components()
                                .all(|c| matches!(c, Component::Normal(_))),
                        "Constant path must be relative without traversal",
                    )?;
                }
            }
            _ => return Err(invalid(format!("Expected {kind}, got {self:?}"))),
        }
        Ok(())
    }
}
impl Expr {
    // Conservative interval checking also proves that divisors remain positive.
    // Overflow in ordinary Slinky expressions is rejected, never wrapped.
    fn bounds(
        &self,
        syms: &HashMap<u32, (i64, i64)>,
        budget: &mut usize,
        depth: usize,
    ) -> Result<(i64, i64)> {
        self.bounds_in(syms, budget, depth, &HashSet::new(), false)
    }
    pub(crate) fn checked_subexpressions(
        &self,
        result: &mut HashSet<Expr>,
        budget: &mut usize,
        depth: usize,
    ) -> Result<()> {
        require(*budget > 0 && depth <= 64, "Expression budget exceeded")?;
        *budget -= 1;
        result.insert(self.clone());
        match self {
            Self::Known(_) | Self::Symbol(_) => {}
            Self::Add(xs)
            | Self::Mul(xs)
            | Self::Min(xs)
            | Self::Max(xs)
            | Self::FloorDiv(xs)
            | Self::CeilDiv(xs) => {
                for x in xs {
                    x.checked_subexpressions(result, budget, depth + 1)?;
                }
            }
        }
        Ok(())
    }
    pub(crate) fn bounds_in(
        &self,
        syms: &HashMap<u32, (i64, i64)>,
        budget: &mut usize,
        depth: usize,
        protected: &HashSet<Expr>,
        checked: bool,
    ) -> Result<(i64, i64)> {
        // Native checked guards evaluate all operands before forward shapes,
        // execution, or state mutation. Their subexpressions are safe only
        // after those guards pass; retain strict checks everywhere else.
        let checked = checked || protected.contains(self);
        require(*budget > 0 && depth <= 64, "Expression budget exceeded")?;
        *budget -= 1;
        match self {
            Self::Known(x) => Ok((*x, *x)),
            Self::Symbol(x) => syms
                .get(x)
                .copied()
                .ok_or_else(|| invalid("Unbound symbol")),
            Self::Add(xs)
            | Self::Mul(xs)
            | Self::Min(xs)
            | Self::Max(xs)
            | Self::FloorDiv(xs)
            | Self::CeilDiv(xs) => {
                require(!xs.is_empty(), "Empty expression")?;
                let ranges = xs
                    .iter()
                    .map(|x| x.bounds_in(syms, budget, depth + 1, protected, checked))
                    .collect::<Result<Vec<_>>>()?;
                let mut range = ranges[0];
                if matches!(self, Self::FloorDiv(_) | Self::CeilDiv(_)) {
                    require(
                        ranges.len() == 2 && ranges[1].0 > 0,
                        "Division requires positive divisor",
                    )?;
                    let ceil = matches!(self, Self::CeilDiv(_));
                    let mut q = Vec::new();
                    for n in [range.0, range.1] {
                        for d in [ranges[1].0, ranges[1].1] {
                            q.push(n.div_euclid(d) + i64::from(ceil && n.rem_euclid(d) != 0));
                        }
                    }
                    return Ok((*q.iter().min().unwrap(), *q.iter().max().unwrap()));
                }
                for &(lo, hi) in &ranges[1..] {
                    let pair = match self {
                        Self::Add(_) => {
                            (range.0 as i128 + lo as i128, range.1 as i128 + hi as i128)
                        }
                        Self::Mul(_) => {
                            let p = [
                                range.0 as i128 * lo as i128,
                                range.0 as i128 * hi as i128,
                                range.1 as i128 * lo as i128,
                                range.1 as i128 * hi as i128,
                            ];
                            (*p.iter().min().unwrap(), *p.iter().max().unwrap())
                        }
                        Self::Min(_) => (range.0.min(lo) as i128, range.1.min(hi) as i128),
                        Self::Max(_) => (range.0.max(lo) as i128, range.1.max(hi) as i128),
                        _ => unreachable!(),
                    };
                    require(
                        pair.0 <= i64::MAX as i128 && pair.1 >= i64::MIN as i128,
                        "Expression always overflows",
                    )?;
                    range = if checked {
                        (
                            pair.0.clamp(i64::MIN as i128, i64::MAX as i128) as i64,
                            pair.1.clamp(i64::MIN as i128, i64::MAX as i128) as i64,
                        )
                    } else {
                        (
                            i64::try_from(pair.0)
                                .map_err(|_| invalid("Expression may overflow"))?,
                            i64::try_from(pair.1)
                                .map_err(|_| invalid("Expression may overflow"))?,
                        )
                    };
                }
                Ok(range)
            }
        }
    }
}
impl Plan {
    fn into_validated(self) -> Result<ValidatedPlan> {
        self.validate()?;
        Ok(ValidatedPlan {
            value_count: self.value_count,
            commands: self
                .commands
                .into_iter()
                .map(Command::decode)
                .collect::<Result<_>>()?,
        })
    }
    #[cfg(feature = "native-tests")]
    fn read(path: &Path) -> Result<Self> {
        use std::io::Read;
        let file = std::fs::File::open(path)?;
        let mut bytes = Vec::new();
        file.take(MAX_FILE + 1).read_to_end(&mut bytes)?;
        require(
            bytes.len() as u64 <= MAX_FILE,
            "Graph artifact exceeds size limit",
        )?;
        let source =
            std::str::from_utf8(&bytes).map_err(|_| invalid("Graph source must be UTF-8"))?;
        crate::plan_text::parse(source).map_err(|e| invalid(format!("{}:{e}", path.display())))
    }
    pub fn validate(&self) -> Result<()> {
        self.validate_with_location().map_err(|e| e.error)
    }
    pub(crate) fn validate_with_location(&self) -> std::result::Result<(), ValidationError> {
        require(
            self.format == "ynnpack-construction-plan" && self.version == 1,
            "Unsupported graph format/version",
        )?;
        require(
            self.resource_contract == 1 && self.completion_contract == 1,
            "Unsupported native contract",
        )?;
        require(
            self.value_count > 0
                && self.value_count <= MAX_VALUES
                && self.commands.len() <= MAX_COMMANDS,
            "Graph size limit exceeded",
        )?;
        let mut values: Vec<Value> = Vec::new();
        let mut names = HashSet::new();
        let mut syms = HashMap::new();
        let mut resources = HashSet::new();
        let mut completions = HashSet::new();
        let mut profile = false;
        let mut operation = false;
        let mut protected = HashSet::new();
        for (index, c) in self.commands.iter().enumerate() {
            if c.op == Op::Guard
                && c.args.len() == 5
                && matches!(&c.args[4], Arg::Text(t) if t == "checked")
            {
                for arg in &c.args[..2] {
                    if let Arg::Expr(e) = arg {
                        e.checked_subexpressions(&mut protected, &mut 4096, 0)
                            .map_err(|error| ValidationError {
                                command: Some(index),
                                error,
                            })?;
                    }
                }
            }
        }
        for (index, c) in self.commands.iter().enumerate() {
            self.validate_command(
                c,
                &mut values,
                &mut names,
                &mut syms,
                &mut resources,
                &mut completions,
                &mut profile,
                &mut operation,
                &protected,
            )
            .map_err(|e| ValidationError {
                command: Some(index),
                error: invalid(format!("Command {index} ({}): {}", c.op.name(), e)),
            })?;
        }
        require(
            values.len() == self.value_count && !profile && !operation,
            "Incomplete construction stream",
        )?;
        require(
            values.iter().all(|v| v.flags & 2 == 0 || v.ready),
            "Missing graph output producer",
        )?;
        Ok(())
    }
    #[allow(clippy::too_many_arguments)]
    fn validate_command(
        &self,
        c: &RawCommand,
        values: &mut Vec<Value>,
        names: &mut HashSet<String>,
        syms: &mut HashMap<u32, (i64, i64)>,
        resources: &mut HashSet<i64>,
        completions: &mut HashSet<String>,
        profile: &mut bool,
        operation: &mut bool,
        protected: &HashSet<Expr>,
    ) -> Result<()> {
        use Op::*;
        let a = &c.args;
        if c.op == Symbol {
            require(a.len() >= 6, "Incomplete symbol declaration")?;
            for (arg, kind) in a[..4].iter().zip(["id", "text", "int", "int"]) {
                arg.check(kind, syms, protected)?;
            }
            let id = u32::try_from(a[0].int()).map_err(|_| invalid("Invalid symbol ID"))?;
            let (lo, hi) = (a[2].int(), a[3].int());
            require(
                lo <= hi && !syms.contains_key(&id),
                "Duplicate symbol/invalid bounds",
            )?;
            match a[1].text() {
                "Axis" => {
                    require(a.len() == 6, "Invalid axis binding")?;
                    a[4].check("id", syms, protected)?;
                    a[5].check("size", syms, protected)?;
                    let v = values
                        .get(a[4].int() as usize)
                        .ok_or_else(|| invalid("Undeclared axis tensor"))?;
                    require(
                        v.flags & 1 != 0 && a[5].int() < (v.dims.len() as i64) && lo >= 0,
                        "Invalid input axis source",
                    )?;
                }
                "Parameter" | "InstanceParameter" => {
                    require(a.len() == 7, "Invalid scalar binding")?;
                    a[4].check("text", syms, protected)?;
                    a[5].check("int", syms, protected)?;
                    a[6].check("int", syms, protected)?;
                    require(
                        a[5].int() == lo && a[6].int() == hi,
                        "Scalar bounds mismatch",
                    )?;
                }
                _ => return Err(invalid("Unsupported symbol source")),
            }
            syms.insert(id, (lo, hi));
            return Ok(());
        }
        let signature = c.op.signature();
        require(
            a.len() == signature.len(),
            "Incorrect command argument count",
        )?;
        for (arg, kind) in a.iter().zip(signature) {
            let kind = if c.op == ShapeTensor && *kind == "exprs" { "elements" } else { kind };
            arg.check(kind, syms, protected)?;
        }
        if matches!(
            c.op,
            Tensor | ConstantOutput | PackedTensor | PackedConstantOutput
        ) {
            require(
                values.len() < self.value_count && a[0].int() == values.len() as i64,
                "Tensor IDs must be dense and declared once",
            )?;
            let packed = matches!(c.op, PackedTensor | PackedConstantOutput);
            let dtype = if packed {
                match a[2].int() {
                    2 => "int2",
                    4 => "int4",
                    _ => return Err(invalid("Invalid packed width")),
                }
            } else if let Arg::Dtype(x) = &a[2] {
                x.as_str()
            } else {
                unreachable!()
            };
            let dims = a[3].ints();
            require(dims.len() <= 8, "Tensor rank exceeds adapter limit")?;
            let count = dims
                .iter()
                .try_fold(1u64, |n, &d| n.checked_mul(d as u64))
                .ok_or_else(|| invalid("Tensor extent product overflow"))?;
            let bits = match dtype {
                "int2" => 2,
                "int4" => 4,
                "int8" | "uint8" => 8,
                "fp16" | "bf16" => 16,
                "fp32" | "int32" => 32,
                "fp64" => 64,
                _ => unreachable!(),
            };
            let bytes = count
                .checked_mul(bits)
                .and_then(|n| n.checked_add(7))
                .map(|n| n / 8)
                .ok_or_else(|| invalid("Tensor byte size overflow"))?;
            require(bytes <= isize::MAX as u64, "Tensor is too large")?;
            let (flags, data) = if matches!(c.op, Tensor | PackedTensor) {
                (a[4].int(), &a[5])
            } else {
                (2, &a[4])
            };
            require(
                (0..=3).contains(&flags) && names.insert(a[1].text().to_owned()),
                "Invalid flags or duplicate tensor name",
            )?;
            let data = if let Arg::Data(d) = data {
                d
            } else {
                unreachable!()
            };
            if let Some(d) = data {
                require(
                    d.bytes as u64 == bytes.max(1),
                    "Constant storage size does not match shape",
                )?;
            }
            if matches!(c.op, ConstantOutput | PackedConstantOutput) {
                require(data.is_some(), "Constant output without storage")?;
            }
            values.push(Value {
                dtype: dtype.to_owned(),
                dims: dims.to_vec(),
                flags,
                ready: flags & 1 != 0 || data.is_some(),
                name: a[1].text().to_owned(),
                packed,
            });
            return Ok(());
        }
        require(
            values.len() == self.value_count,
            "All tensors must precede construction",
        )?;
        for (arg, kind) in a.iter().zip(signature) {
            let ids: Vec<i64> = match *kind {
                "id" | "operand" => vec![arg.int()],
                "optional" => {
                    if arg.int() == INVALID {
                        vec![]
                    } else {
                        vec![arg.int()]
                    }
                }
                "ids" => arg.ints().to_vec(),
                _ => vec![],
            };
            require(
                ids.iter()
                    .all(|&id| id >= 0 && (id as usize) < values.len()),
                "Undeclared tensor reference",
            )?;
            if matches!(arg, Arg::Native(_)) {
                require(
                    values[arg.int() as usize].packed,
                    "Native conversion requires packed carrier",
                )?;
            }
        }
        let (inputs, outputs): (Vec<i64>, Vec<i64>) = match c.op {
            Binary | Compare => (vec![a[1].int(), a[2].int()], vec![a[3].int()]),
            Unary | Reduce => (vec![a[1].int()], vec![a[2].int()]),
            Matmul
            | BroadcastLike
            | SliceLike
            | ParameterExpand
            | Gather
            | DynamicallyQuantizedMatmul => (vec![a[0].int(), a[1].int()], vec![a[2].int()]),
            Dot | Conv2D => (vec![a[0].int(), a[1].int(), a[2].int()], vec![a[3].int()]),
            QuantizeTensor | DequantizeTensor | MappedDequantize | Select => {
                (vec![a[0].int(), a[1].int(), a[2].int()], vec![a[3].int()])
            }
            DynamicQuantization => (vec![a[0].int()], vec![a[1].int(), a[2].int()]),
            Append => (vec![a[0].int(), a[1].int()], vec![a[2].int()]),
            Concat | Stack => (a[0].ints().to_vec(), vec![a[1].int()]),
            Split => (vec![a[0].int()], a[1].ints().to_vec()),
            PackedRoute => (a[1].ints().to_vec(), vec![a[2].int()]),
            ShapeTensor => (vec![], vec![a[0].int()]),
            GatedDeltaRule => (a[..7].iter().map(Arg::int).collect(), vec![a[7].int(), a[8].int()]),
            CausalDepthwiseConv => (a[..3].iter().map(Arg::int).collect(), vec![a[3].int(), a[4].int()]),
            Sdpa | WeightOnlyLinear | BlockwiseFullyConnected => (a[..4].iter().map(Arg::int).collect(), vec![a[4].int()]),
            Pad => (vec![a[0].int(), a[1].int()], vec![a[2].int()]),
            Quantize | Dequantize | FuseDims | SplitDim | ShapeProduct | Polynomial | Softmax
            | Reshape | Transpose | Slice | View | Mask | Pool2D | Copy | ExpandDims | Squeeze
            | Broadcast | SymbolicBroadcast | SymbolicReshape | SymbolicSlice | Convert | Mean
            | Gelu | Reverse | Tile => (vec![a[0].int()], vec![a[1].int()]),
            _ => (vec![], vec![]),
        };
        for &id in &inputs {
            if id != INVALID {
                require(
                    values[id as usize].ready,
                    "Operand has no preceding producer",
                )?;
            }
        }
        let mut unique = HashSet::new();
        for &id in &outputs {
            require(
                unique.insert(id) && !values[id as usize].ready,
                "Duplicate result producer",
            )?;
        }
        let rank = |id: i64| values[id as usize].dims.len();
        let axis_ok = |axis: i64, r: usize| axis >= -(r as i64) && axis < r as i64;
        match c.op {
            PackedStrides => {
                require(resources.contains(&a[0].int()), "Packed strides need a resource")?;
                let Arg::Exprs(xs) = &a[1] else { unreachable!() };
                require(xs.len() == rank(a[0].int()), "Packed stride rank mismatch")?;
            }
            InputShape | ResultShape => {
                if let Arg::Exprs(xs) = &a[1] {
                    require(xs.len() == rank(a[0].int()), "Shape rank mismatch")?;
                }
                if c.op == InputShape {
                    require(
                        values[a[0].int() as usize].flags & 1 != 0,
                        "Input shape on non-input",
                    )?;
                }
                if c.op == ResultShape {
                    require(
                        values[a[0].int() as usize].ready,
                        "Result shape before producer",
                    )?;
                }
            }
            Resource => {
                require(
                    resources.insert(a[0].int())
                        && values[a[0].int() as usize].flags & 1 != 0
                        && axis_ok(a[2].int(), rank(a[0].int())),
                    "Invalid resource owner/axis",
                )?;
                let Arg::Encoding(encoding) = &a[4] else {
                    unreachable!()
                };
                require(
                    encoding.dtype == values[a[0].int() as usize].dtype,
                    "Resource encoding dtype differs from storage",
                )?;
                if let Some(axis) = encoding.axis {
                    require(axis_ok(axis, rank(a[0].int())), "Invalid quantization axis")?;
                }
            }
            BindScalarParameter => require(
                values[a[0].int() as usize].flags & 1 != 0
                    && rank(a[0].int()) == 0
                    && values[a[0].int() as usize].dtype == "int32",
                "Invalid scalar tensor",
            )?,
            Guard => require(
                ["eq", "le"].contains(&a[2].text())
                    && ["bounds", "ordinary", "checked"].contains(&a[4].text()),
                "Unsupported guard relation/mode",
            )?,
            BeginProfileOperation => {
                require(!*profile, "Nested profile operation")?;
                require(
                    a[2].ints().len() == a[4].texts().len(),
                    "Profile input names mismatch",
                )?;
                *profile = true;
            }
            EndProfileOperation => {
                require(*profile && !*operation, "Unbalanced profile operation")?;
                *profile = false;
            }
            BeginOperation => {
                require(
                    !*operation && a[0].texts().iter().all(|s| completions.contains(s)),
                    "Missing completion dependency/nested operation",
                )?;
                *operation = true;
            }
            EndOperation => {
                require(
                    *operation && a[1].ints().iter().all(|&id| values[id as usize].ready),
                    "Incomplete operation results",
                )?;
                for s in a[0].texts() {
                    require(completions.insert(s.clone()), "Duplicate completion")?;
                }
                *operation = false;
            }
            CompletionOutput => {
                let tokens = a[0].texts();
                let unique: HashSet<_> = tokens.iter().collect();
                require(!*operation && !tokens.is_empty()
                    && unique.len() == tokens.len()
                    && tokens.iter().all(|s| completions.contains(s)),
                    "Invalid public completion roots")?;
            }
            Transpose => {
                let xs = a[2].ints();
                let r = rank(a[0].int());
                let unique: HashSet<_> = xs.iter().collect();
                require(
                    xs.len() == r
                        && unique.len() == r
                        && xs.iter().all(|&n| n >= 0 && n < r as i64),
                    "Invalid permutation",
                )?;
            }
            Slice => require(
                a[2].ints().len() == rank(a[0].int())
                    && a[3].ints().len() == rank(a[0].int())
                    && a[2].ints().iter().all(|&n| n >= 0)
                    && a[3].ints().iter().all(|&n| n >= -1),
                "Invalid slice vectors",
            )?,
            SplitDim => require(
                axis_ok(a[2].int(), rank(a[0].int()))
                    && !a[3].ints().is_empty()
                    && a[3].ints().len() <= 8
                    && a[3].ints().iter().filter(|&&n| n == 0).count() <= 1,
                "Invalid split dimensions",
            )?,
            FuseDims => require(
                a[2].int() >= 0
                    && a[3].int() > 0
                    && a[2].int() <= rank(a[0].int()) as i64
                    && a[3].int() <= rank(a[0].int()) as i64 - a[2].int(),
                "Invalid fused axes",
            )?,
            ShapeProduct | Mean | Squeeze | Reverse => require(
                a[2].ints().iter().all(|&n| axis_ok(n, rank(a[0].int()))),
                "Invalid axes",
            )?,
            Reduce => require(
                a[3].ints().iter().all(|&n| axis_ok(n, rank(a[1].int()))),
                "Invalid reduction axes",
            )?,
            Reshape => require(
                a[2].ints().len() <= 8 && a[2].ints().iter().filter(|&&n| n == 0).count() <= 1,
                "Invalid reshape",
            )?,
            Dot => require(
                a[4].int() > 0
                    && a[4].int() <= rank(a[0].int()) as i64
                    && a[4].int() <= rank(a[1].int()) as i64,
                "Invalid contraction rank",
            )?,
            Matmul => require(
                rank(a[0].int()) >= 2 && rank(a[1].int()) >= 2,
                "Matrix rank below two",
            )?,
            Conv2D | Pool2D => {
                let start = if c.op == Conv2D { 4 } else { 2 };
                for arg in &a[start..start + if c.op == Conv2D { 3 } else { 2 }] {
                    require(
                        arg.ints().len() == 2 && arg.ints().iter().all(|&n| n > 0),
                        "Invalid spatial kernel/stride/dilation",
                    )?;
                }
                require(
                    rank(a[0].int()) == 4 && values[a[0].int() as usize].dtype == "fp32",
                    "Spatial operations require rank-four FP32",
                )?;
                if c.op == Conv2D {
                    require(
                        rank(a[1].int()) == 4
                            && values[a[1].int() as usize].dtype == "fp32"
                            && a[9].int() > 0
                            && a[10].int() > 0,
                        "Invalid convolution filter/channels",
                    )?;
                }
            }
            Quantize | Dequantize => {
                if let Arg::Float(s) = &a[2] {
                    require(
                        float(s)? > 0.0 && i32::try_from(a[3].int()).is_ok(),
                        "Invalid quantization attributes",
                    )?;
                }
            }
            View => require(axis_ok(a[2].int(), rank(a[0].int())), "Invalid view axis")?,
            Append => require(
                axis_ok(a[3].int(), rank(a[0].int())) && rank(a[0].int()) == rank(a[1].int()),
                "Invalid append axis/rank",
            )?,
            Concat => require(
                !a[0].ints().is_empty() && axis_ok(a[2].int(), rank(a[0].ints()[0])),
                "Invalid concat",
            )?,
            Stack => require(
                !a[0].ints().is_empty() && axis_ok(a[2].int(), rank(a[1].int())),
                "Invalid stack axis/inputs",
            )?,
            Split => require(
                !a[1].ints().is_empty() && axis_ok(a[2].int(), rank(a[0].int())),
                "Invalid split axis/results",
            )?,
            Gather => require(
                axis_ok(a[3].int(), rank(a[0].int()))
                    && values[a[1].int() as usize].dtype == "int32",
                "Gather needs a valid axis and INT32 indices",
            )?,
            Tile => require(a[2].ints().len() == rank(a[0].int()), "Tile rank mismatch")?,
            Compare => {
                let out = a[3].int();
                require(
                    values[a[1].int() as usize].dtype == "fp32"
                        && values[a[2].int() as usize].dtype == "fp32"
                        && values[out as usize].dtype == "uint8"
                        && rank(a[1].int()) <= rank(out)
                        && rank(a[2].int()) <= rank(out),
                    "Comparison requires FP32 inputs and a broadcast byte-boolean result",
                )?;
                if let Arg::Exprs(xs) = &a[4] {
                    require(xs.len() == rank(out), "Comparison rank mismatch")?;
                }
            }
            Select | ShapeTensor => {
                let (out, shape) = if c.op == Select {
                    (a[3].int(), &a[4])
                } else {
                    (a[0].int(), &a[1])
                };
                if let Arg::Exprs(xs) = shape {
                    if c.op == Select {
                        require(xs.len() == rank(out), "Select rank mismatch")?;
                    } else {
                        require(
                            values[out as usize].dtype == "int32",
                            "Shape tensor must be INT32",
                        )?;
                        let scalar = matches!(a[2], Arg::Bool(true));
                        require(
                            if scalar { rank(out) == 0 && xs.len() == 1 }
                            else { rank(out) == 1 && values[out as usize].dims[0] == xs.len() as i64 },
                            "Shape tensor element count mismatch",
                        )?;
                    }
                }
            }
            ParameterExpand | MappedDequantize => {
                let at = if c.op == ParameterExpand { 3 } else { 4 };
                let source = if c.op == ParameterExpand {
                    a[1].int()
                } else {
                    a[0].int()
                };
                require(
                    a[at].ints().len() == a[at + 1].ints().len()
                        && a[at]
                            .ints()
                            .iter()
                            .all(|&axis| axis >= 0 && axis < rank(source) as i64)
                        && a[at + 1].ints().iter().all(|&block| block > 0),
                    "Invalid parameter map",
                )?;
            }
            CausalDepthwiseConv => {
                let shape = |slot: usize| &values[a[slot].int() as usize].dims;
                require(a[..5].iter().all(|id| values[id.int() as usize].dtype == "fp32")
                    && rank(a[0].int())==3 && rank(a[1].int())==4 && rank(a[2].int())==3,
                    "Causal convolution requires FP32 BTC/history/filter")?;
                let (x,w,h)=(shape(0),shape(1),shape(2));
                require(x.iter().all(|&d| d>0) && w[1]>=2 && w==&[1,h[1]+1,1,x[2]]
                    && h==&[x[0],w[1]-1,x[2]] && shape(3)==&[x[0],x[1],1,x[2]]
                    && shape(4)==h,"Causal convolution shape mismatch")?;
            },
            GatedDeltaRule => {
                require(a[..6].iter().all(|id| values[id.int() as usize].dtype == "fp32")
                    && rank(a[0].int()) == 4 && rank(a[1].int()) == 4
                    && rank(a[2].int()) == 4 && rank(a[3].int()) == 3
                    && rank(a[4].int()) == 3 && rank(a[5].int()) == 4
                    && rank(a[6].int()) == 0 && values[a[6].int() as usize].dtype == "int32"
                    && !a[9].ints().is_empty() && a[9].ints().iter().all(|&h| h>=0),
                    "Invalid gated delta contract")?;
                let shape = |slot: usize| &values[a[slot].int() as usize].dims;
                let (q, v) = (shape(0), shape(2));
                require(q == shape(1) && q.iter().chain(v).all(|&d| d>0)
                    && q[0]==v[0] && q[1]==v[1]
                    && shape(3)==&v[..3] && shape(4)==shape(3)
                    && shape(5)==&[v[0],v[2],q[3],v[3]]
                    && shape(7)==v && shape(8)==shape(5)
                    && values[a[7].int() as usize].dtype=="fp32"
                    && values[a[8].int() as usize].dtype=="fp32"
                    && a[9].ints().len()==v[2] as usize
                    && a[9].ints().iter().all(|&h| h<q[2]), "Gated delta shape/head map mismatch")?;
                if let Arg::Float(bits)=&a[10] {
                    require(float(bits)?>0.0, "Invalid gated delta scale")?;
                }
            },
            WeightOnlyLinear => require(
                a[5].int() > 0 && rank(a[0].int()) == 2 && rank(a[1].int()) == 2,
                "Invalid weight-only linear shape/group",
            )?,
            BlockwiseFullyConnected => {
                let x = &values[a[0].int() as usize];
                let w = &values[a[1].int() as usize];
                let s = &values[a[2].int() as usize];
                let z = &values[a[3].int() as usize];
                let y = &values[a[4].int() as usize];
                require(a[5].int() == 32 && x.dims.len() == 2 && w.dims.len() == 2
                    && w.dims[1] > 0 && w.dims[1] % 32 == 0 && w.dims[0] > 0
                    && x.dims[1] == w.dims[1] && x.dtype == "fp32" && w.dtype == "int4"
                    && s.dtype == "fp32" && s.dims == vec![w.dims[0], w.dims[1] / 32]
                    && z.dtype == "int32" && z.dims == vec![1,1]
                    && y.dtype == "fp32" && y.dims == vec![x.dims[0],w.dims[0]],
                    "Invalid grouped hybrid FC contract")?;
            },
            DynamicallyQuantizedMatmul => {
                require(
                    rank(a[0].int()) >= 2
                        && rank(a[1].int()) >= 2
                        && values[a[0].int() as usize].dtype == "fp32"
                        && values[a[1].int() as usize].dtype == "int8"
                        && a[5].int() >= -1,
                    "Invalid dynamic matmul contract",
                )?;
                if let Arg::Float(bits) = &a[3] {
                    require(float(bits)? > 0.0, "Invalid RHS scale")?;
                }
            }
            Sdpa => require(
                a[..3]
                    .iter()
                    .all(|id| rank(id.int()) == 4 && values[id.int() as usize].dtype == "fp32")
                    && (0..=2).contains(&a[7].int())
                    && (a[7].int() == 0) == (a[3].int() == INVALID)
                    && a[9].int() >= 0,
                "Invalid SDPA contract",
            )?,
            PackedRoute => {
                require(
                    !a[1].ints().is_empty() && (0..=2).contains(&a[7].int()),
                    "Invalid packed route",
                )?;
                if let Arg::Exprs(xs) = &a[3] {
                    require(xs.len() == rank(a[2].int()), "Packed output rank mismatch")?;
                }
            }
            Pad => {
                require((0..=2).contains(&a[5].int()), "Invalid pad mode")?;
                for arg in &a[3..5] {
                    if let Arg::Exprs(xs) = arg {
                        require(xs.len() == rank(a[0].int()), "Invalid pad rank")?;
                    }
                }
            }
            _ => {}
        }
        for id in outputs {
            values[id as usize].ready = true;
        }
        Ok(())
    }
}
