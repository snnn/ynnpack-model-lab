// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
use super::parser::{Call, Value, ValueKind};
use super::{diagnostic, Span};
use crate::plan::{self, Arg, Data, Encoding, Expr, INVALID};
use crate::{Error, Result};
use std::collections::HashMap;

pub(super) struct Resolver<'a> {
    pub source: &'a str,
    pub tensors: HashMap<String, i64>,
    pub symbols: HashMap<String, u32>,
    pub aliases: HashMap<String, Expr>,
    pub assets: HashMap<String, Data>,
}
impl<'a> Resolver<'a> {
    pub fn new(source: &'a str) -> Self {
        Self {
            source,
            tensors: HashMap::new(),
            symbols: HashMap::new(),
            aliases: HashMap::new(),
            assets: HashMap::new(),
        }
    }
    pub fn tensor_count(&self) -> usize {
        self.tensors.len()
    }
    pub fn error(&self, span: Span, message: impl std::fmt::Display) -> Error {
        diagnostic(self.source, span, message)
    }
    pub fn fields<'b, 's>(&self, call: &'b Call<'s>, names: &[&str]) -> Result<Vec<&'b Value<'s>>> {
        let mut values = vec![None; names.len()];
        for a in &call.arguments {
            let Some(name) = a.name else {
                return Err(self.error(a.span, "Expected a named argument"));
            };
            let Some(i) = names.iter().position(|&n| n == name) else {
                return Err(self.error(a.span, format!("Unknown field {name} for {}", call.name)));
            };
            if values[i].replace(&a.value).is_some() {
                return Err(self.error(a.span, format!("Duplicate field {name}")));
            }
        }
        values
            .into_iter()
            .zip(names)
            .map(|(v, name)| {
                v.ok_or_else(|| {
                    self.error(call.span, format!("Missing field {name} for {}", call.name))
                })
            })
            .collect()
    }
    pub fn positional<'b, 's>(
        &self,
        call: &'b Call<'s>,
        count: Option<usize>,
    ) -> Result<Vec<&'b Value<'s>>> {
        if call.arguments.iter().any(|a| a.name.is_some())
            || count.is_some_and(|n| n != call.arguments.len())
        {
            return Err(self.error(call.span, format!("Invalid arguments for {}", call.name)));
        }
        Ok(call.arguments.iter().map(|a| &a.value).collect())
    }
    pub fn int(&self, v: &Value<'_>) -> Result<i64> {
        let result = match &v.kind {
            ValueKind::Number(s) => s.parse::<i128>().ok(),
            ValueKind::Unary(sign, x) => match &x.kind {
                ValueKind::Number(s) => s.parse::<i128>().ok().and_then(|n| {
                    if *sign == b'-' {
                        n.checked_neg()
                    } else {
                        Some(n)
                    }
                }),
                _ => None,
            },
            _ => None,
        };
        if let Some(n) = result.and_then(|n| i64::try_from(n).ok()) {
            return Ok(n);
        }
        Err(self.error(v.span, "Expected a signed 64-bit integer"))
    }
    pub fn string(&self, v: &Value<'_>) -> Result<String> {
        if let ValueKind::String(s) = &v.kind {
            return Ok(s.clone());
        }
        Err(self.error(v.span, "Expected a quoted string"))
    }
    pub fn name(&self, v: &Value<'_>) -> Result<String> {
        if let ValueKind::Name(s) = v.kind {
            return Ok(s.into());
        }
        Err(self.error(v.span, "Expected an enumeration name"))
    }
    pub fn tensor(&self, v: &Value<'_>) -> Result<i64> {
        if let ValueKind::Tensor(s) | ValueKind::Name(s) = v.kind {
            return self
                .tensors
                .get(s)
                .copied()
                .ok_or_else(|| self.error(v.span, format!("Unknown tensor {s}")));
        }
        Err(self.error(v.span, "Expected a tensor reference"))
    }
    pub fn list<'b, 's>(&self, v: &'b Value<'s>) -> Result<&'b [Value<'s>]> {
        if let ValueKind::List(xs) = &v.kind {
            return Ok(xs);
        }
        Err(self.error(v.span, "Expected a list"))
    }
    pub fn float(&self, v: &Value<'_>) -> Result<String> {
        if let ValueKind::Call(c) = &v.kind {
            if c.name == "bits" {
                let a = self.positional(c, Some(1))?;
                let bits = self.string(a[0])?;
                plan::float(&bits).map_err(|e| self.error(v.span, e))?;
                return Ok(bits);
            }
        }
        let n = match &v.kind {
            ValueKind::Number(s) => s.parse::<f64>().ok(),
            ValueKind::Unary(sign, x) => match &x.kind {
                ValueKind::Number(s) => {
                    s.parse::<f64>()
                        .ok()
                        .map(|n| if *sign == b'-' { -n } else { n })
                }
                _ => None,
            },
            _ => None,
        };
        if let Some(n) = n.filter(|n| n.is_finite()) {
            return Ok(format!("{:016x}", n.to_bits()));
        }
        Err(self.error(
            v.span,
            "Expected a finite binary64 literal or bits(\"16 hex digits\")",
        ))
    }
    pub fn expr(&self, v: &Value<'_>) -> Result<Expr> {
        fn budget(e: &Expr, depth: usize, nodes: &mut usize) -> bool {
            *nodes += 1;
            if depth > 64 || *nodes > 4096 {
                return false;
            }
            match e {
                Expr::Known(_) | Expr::Symbol(_) => true,
                Expr::Add(xs)
                | Expr::Mul(xs)
                | Expr::Min(xs)
                | Expr::Max(xs)
                | Expr::FloorDiv(xs)
                | Expr::CeilDiv(xs) => xs.iter().all(|x| budget(x, depth + 1, nodes)),
            }
        }
        let e = match &v.kind {
            ValueKind::Number(_) => Expr::Known(self.int(v)?),
            ValueKind::Unary(sign, x) => {
                if matches!(x.kind, ValueKind::Number(_)) {
                    Expr::Known(self.int(v)?)
                } else if *sign == b'+' {
                    self.expr(x)?
                } else {
                    Expr::Mul(vec![Expr::Known(-1), self.expr(x)?])
                }
            }
            ValueKind::Name(s) | ValueKind::Symbol(s) => {
                if let Some(e) = self.aliases.get(*s) {
                    e.clone()
                } else {
                    Expr::Symbol(
                        *self
                            .symbols
                            .get(*s)
                            .ok_or_else(|| self.error(v.span, format!("Unknown dimension {s}")))?,
                    )
                }
            }
            ValueKind::Binary(op, a, b) => {
                let (a, b) = (self.expr(a)?, self.expr(b)?);
                match *op {
                    "add" => Expr::Add(vec![a, b]),
                    "sub" => Expr::Add(vec![a, Expr::Mul(vec![Expr::Known(-1), b])]),
                    "mul" => Expr::Mul(vec![a, b]),
                    "floor_div" => Expr::FloorDiv(vec![a, b]),
                    _ => unreachable!(),
                }
            }
            ValueKind::Call(c) => {
                let build = match c.name {
                    "add" => Expr::Add,
                    "mul" => Expr::Mul,
                    "min" => Expr::Min,
                    "max" => Expr::Max,
                    "floor_div" => Expr::FloorDiv,
                    "ceil_div" => Expr::CeilDiv,
                    _ => return Err(self.error(c.span, format!("Unknown expression {}", c.name))),
                };
                build(
                    self.positional(c, None)?
                        .into_iter()
                        .map(|v| self.expr(v))
                        .collect::<Result<_>>()?,
                )
            }
            ValueKind::Unknown => {
                return Err(self.error(
                    v.span,
                    "Unknown dimension ? must be resolved before assembly",
                ))
            }
            _ => return Err(self.error(v.span, "Expected a dimension expression")),
        };
        if !budget(&e, 0, &mut 0) {
            return Err(self.error(v.span, "Expression nesting/node budget exceeded"));
        }
        Ok(e)
    }
    pub fn arg(&self, kind: &str, field: &str, v: &Value<'_>) -> Result<Arg> {
        Ok(match kind {
            "int" if field == "flags" && matches!(v.kind, ValueKind::List(_)) => {
                let mut flags = 0;
                for flag in self.list(v)? {
                    let bit = match self.name(flag)?.as_str() {
                        "input" => 1,
                        "output" => 2,
                        _ => return Err(self.error(flag.span, "Unknown tensor flag")),
                    };
                    if flags & bit != 0 {
                        return Err(self.error(flag.span, "Duplicate tensor flag"));
                    }
                    flags |= bit;
                }
                Arg::Int(flags)
            }
            "int" | "size" => Arg::Int(self.int(v)?),
            "optional" if matches!(v.kind, ValueKind::Name("none")) => Arg::Int(INVALID),
            "operand" if matches!(v.kind, ValueKind::Call(_)) => {
                let ValueKind::Call(c) = &v.kind else {
                    unreachable!()
                };
                if c.name != "native" {
                    return Err(self.error(c.span, "Expected native(%tensor)"));
                }
                Arg::Native(self.tensor(self.positional(c, Some(1))?[0])?)
            }
            "id" | "optional" | "operand" => Arg::Int(self.tensor(v)?),
            "text" => Arg::Text(self.string(v)?),
            "dtype" => Arg::Dtype(self.name(v)?),
            "binary" => Arg::Binary(self.name(v)?),
            "unary" => Arg::Unary(self.name(v)?),
            "reduce" => Arg::Reduce(self.name(v)?),
            "bool" => Arg::Bool(match v.kind {
                ValueKind::Name("true") => true,
                ValueKind::Name("false") => false,
                _ => return Err(self.error(v.span, "Expected true or false")),
            }),
            "float" => Arg::Float(self.float(v)?),
            "ints" | "sizes" => Arg::Ints(
                self.list(v)?
                    .iter()
                    .map(|v| self.int(v))
                    .collect::<Result<_>>()?,
            ),
            "ids" => Arg::Ints(
                self.list(v)?
                    .iter()
                    .map(|v| self.tensor(v))
                    .collect::<Result<_>>()?,
            ),
            "texts" => Arg::Texts(
                self.list(v)?
                    .iter()
                    .map(|v| self.string(v))
                    .collect::<Result<_>>()?,
            ),
            "floats" => Arg::Floats(
                self.list(v)?
                    .iter()
                    .map(|v| self.float(v))
                    .collect::<Result<_>>()?,
            ),
            "expr" => Arg::Expr(self.expr(v)?),
            "exprs" => Arg::Exprs(
                self.list(v)?
                    .iter()
                    .map(|v| self.expr(v))
                    .collect::<Result<_>>()?,
            ),
            "encoding" => {
                let ValueKind::Call(c) = &v.kind else {
                    return Err(self.error(v.span, "Expected structured encoding(...)"));
                };
                if c.name != "encoding" {
                    return Err(self.error(c.span, "Expected encoding(...)"));
                }
                let a = self.fields(c, &["dtype", "axis", "scales", "zero_points"])?;
                Arg::Encoding(Encoding {
                    dtype: self.name(a[0])?,
                    axis: if matches!(a[1].kind, ValueKind::Name("none")) {
                        None
                    } else {
                        Some(self.int(a[1])?)
                    },
                    scales: self
                        .list(a[2])?
                        .iter()
                        .map(|x| self.float(x))
                        .collect::<Result<_>>()?,
                    zero_points: self
                        .list(a[3])?
                        .iter()
                        .map(|x| self.int(x))
                        .collect::<Result<_>>()?,
                })
            }
            "data" if matches!(v.kind, ValueKind::Name("none")) => Arg::Data(None),
            "data" => {
                let ValueKind::Call(c) = &v.kind else {
                    return Err(self.error(v.span, "Expected asset(...) or none"));
                };
                if c.name != "asset" {
                    return Err(self.error(c.span, "Expected asset(...)"));
                }
                if c.arguments.len() == 1 && c.arguments[0].name.is_none() {
                    let name = self.name(&c.arguments[0].value)?;
                    return self
                        .assets
                        .get(&name)
                        .cloned()
                        .map(|d| Arg::Data(Some(d)))
                        .ok_or_else(|| self.error(c.span, format!("Unknown asset {name}")));
                }
                let a = self.fields(c, &["path", "bytes", "sha256"])?;
                let bytes = usize::try_from(self.int(a[1])?)
                    .map_err(|_| self.error(a[1].span, "Invalid byte count"))?;
                Arg::Data(Some(Data {
                    path: self.string(a[0])?,
                    bytes,
                    sha256: self.string(a[2])?,
                }))
            }
            _ => return Err(self.error(v.span, format!("Unsupported argument kind {kind}"))),
        })
    }
}
