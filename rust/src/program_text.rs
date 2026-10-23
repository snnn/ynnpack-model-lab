// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
//! Lossless semantic source format. This module performs no target lowering.
use crate::compiler::{
    Attributes, CompileOptions, Dtype, Expr, Graph, Node, Program, Quantization, TensorType, Value,
};
use crate::plan_text::{
    diagnostic,
    lexer::{Kind, Lexer, Token},
};
use crate::{Error, Result};
use serde::{de::DeserializeOwned, Serialize};
use serde_json::{json, Value as Json};
use sha2::{Digest, Sha256};
use std::{
    collections::{BTreeMap, HashMap},
    fmt::Write as _,
    io::{Read, Write},
    path::Path,
};

pub const MAX_TEXT: usize = 32 << 20;
pub const CHUNK_BYTES: usize = 8 << 20;
const MAX_POOL: usize = 128 << 20;
const MAX_SCALARS: usize = 16_000_000;

struct HashWriter(Sha256);
impl Write for HashWriter {
    fn write(&mut self, bytes: &[u8]) -> std::io::Result<usize> {
        self.0.update(bytes);
        Ok(bytes.len())
    }
    fn flush(&mut self) -> std::io::Result<()> {
        Ok(())
    }
}
/// Canonical typed identity, independent of the source spelling or storage.
pub fn semantic_digest(value: &impl Serialize) -> Result<String> {
    let mut writer = HashWriter(Sha256::new());
    serde_json::to_writer(&mut writer, value)?;
    Ok(format!("{:x}", writer.0.finalize()))
}
fn quoted(s: &str) -> String {
    serde_json::to_string(s).unwrap()
}
fn names(xs: &[String]) -> String {
    xs.iter().map(|s| quoted(s)).collect::<Vec<_>>().join(", ")
}
fn sparse<T: Serialize>(value: &T, default: &T) -> Result<Json> {
    let mut value = serde_json::to_value(value)?;
    let default = serde_json::to_value(default)?;
    value
        .as_object_mut()
        .unwrap()
        .retain(|key, value| default.get(key) != Some(value));
    Ok(value)
}
fn expression(e: &Expr) -> String {
    let (name, xs) = match e {
        Expr::Known(n) => return n.to_string(),
        Expr::Symbol(n) => return format!("s{n}"),
        Expr::Add(xs) => ("add", xs),
        Expr::Mul(xs) => ("mul", xs),
        Expr::Min(xs) => ("min", xs),
        Expr::Max(xs) => ("max", xs),
        Expr::FloorDiv(xs) => ("floor_div", xs),
        Expr::CeilDiv(xs) => ("ceil_div", xs),
    };
    format!(
        "{name}({})",
        xs.iter().map(expression).collect::<Vec<_>>().join(", ")
    )
}

#[derive(Clone)]
struct Array {
    kind: String,
    offset: usize,
    count: usize,
}
struct Printer<'a> {
    quant: Vec<&'a Quantization>,
    quant_ids: HashMap<String, usize>,
    arrays: Vec<Array>,
    array_ids: HashMap<(String, String), usize>,
    spans: HashMap<String, (usize, usize)>,
    pool: Vec<u8>,
}
impl<'a> Printer<'a> {
    fn collect(&mut self, graph: &'a Graph, depth: usize) -> Result<()> {
        if depth > 64 {
            return Err(Error::invalid("Semantic function nesting limit exceeded"));
        }
        for value in graph.values.values() {
            if let Some(q) = &value.tensor.quant {
                let key = semantic_digest(q)?;
                if let Some(&id) = self.quant_ids.get(&key) {
                    if self.quant[id] != q {
                        return Err(Error::invalid("Quantization identity collision"));
                    }
                } else {
                    self.quant_ids.insert(key, self.quant.len());
                    self.quant.push(q);
                }
            }
        }
        for function in graph.functions.values() {
            self.collect(function, depth + 1)?;
        }
        Ok(())
    }
    fn value(&mut self, value: &Json, real: bool) -> Result<String> {
        Ok(match value {
            Json::Null => "null".into(),
            Json::Bool(v) => v.to_string(),
            Json::String(s) => quoted(s),
            Json::Number(n) if real => {
                let bits = n
                    .as_u64()
                    .ok_or_else(|| Error::invalid("Expected IEEE binary64 bits"))?;
                let f = f64::from_bits(bits);
                if f.is_finite() {
                    format!("real({f:?})")
                } else {
                    format!("bits(\"{bits:016x}\")")
                }
            }
            Json::Number(n) => n.to_string(),
            Json::Array(xs) => {
                if xs.len() >= 4 && xs[0].is_number() && xs.iter().all(|x| x == &xs[0]) {
                    format!("repeat({}, {})", self.value(&xs[0], real)?, xs.len())
                } else if xs.len() >= 16 && xs.iter().all(Json::is_number) {
                    let kind = if real {
                        "r64"
                    } else if xs.iter().any(|x| x.as_i64().is_some_and(|n| n < 0)) {
                        "i64"
                    } else {
                        "u64"
                    };
                    let mut bytes = Vec::with_capacity(
                        xs.len()
                            .checked_mul(8)
                            .ok_or_else(|| Error::invalid("Array size overflow"))?,
                    );
                    for x in xs {
                        let bits = if kind == "i64" {
                            x.as_i64()
                                .ok_or_else(|| Error::invalid("Non-integer numeric array"))?
                                as u64
                        } else {
                            x.as_u64()
                                .ok_or_else(|| Error::invalid("Non-integer numeric array"))?
                        };
                        bytes.extend_from_slice(&bits.to_le_bytes());
                    }
                    let hash = format!("{:x}", Sha256::digest(&bytes));
                    let key = (kind.to_owned(), hash.clone());
                    let id = if let Some(&id) = self.array_ids.get(&key) {
                        id
                    } else {
                        let offset = if let Some(&(offset, len)) = self.spans.get(&hash) {
                            if self.pool[offset..offset + len] != bytes {
                                return Err(Error::invalid("Numeric identity collision"));
                            }
                            offset
                        } else {
                            let offset = self.pool.len();
                            if bytes.len() > MAX_POOL.saturating_sub(offset) {
                                return Err(Error::invalid("Semantic numeric pool exceeds limit"));
                            }
                            self.pool.extend_from_slice(&bytes);
                            self.spans.insert(hash, (offset, bytes.len()));
                            offset
                        };
                        let id = self.arrays.len();
                        self.arrays.push(Array {
                            kind: kind.into(),
                            offset,
                            count: xs.len(),
                        });
                        self.array_ids.insert(key, id);
                        id
                    };
                    format!("@a{id}")
                } else {
                    format!(
                        "[{}]",
                        xs.iter()
                            .map(|x| self.value(x, real))
                            .collect::<Result<Vec<_>>>()?
                            .join(", ")
                    )
                }
            }
            Json::Object(fields) => {
                if fields.len() == 1 {
                    let (key, value) = fields.iter().next().unwrap();
                    if [
                        "known",
                        "symbol",
                        "add",
                        "mul",
                        "min",
                        "max",
                        "floor_div",
                        "ceil_div",
                    ]
                    .contains(&key.as_str())
                    {
                        return Ok(format!("{key}({})", self.value(value, false)?));
                    }
                }
                let mut result = Vec::new();
                for (key, value) in fields {
                    let name = if key.bytes().enumerate().all(|(i, b)| {
                        b == b'_' || b.is_ascii_alphabetic() || i > 0 && b.is_ascii_digit()
                    }) && !key.is_empty()
                    {
                        key.clone()
                    } else {
                        quoted(key)
                    };
                    result.push(format!(
                        "{name}: {}",
                        self.value(
                            value,
                            ["beta", "scale", "scales", "floats", "coefficients"]
                                .contains(&key.as_str())
                        )?
                    ));
                }
                format!("{{{}}}", result.join(", "))
            }
        })
    }
    fn record(&mut self, value: &impl Serialize) -> Result<String> {
        self.value(&serde_json::to_value(value)?, false)
    }
    fn graph(&mut self, graph: &Graph, out: &mut String, depth: usize) -> Result<()> {
        let indent = "  ".repeat(depth);
        for symbol in &graph.symbols {
            writeln!(out, "{indent}symbol {};", self.record(symbol)?).unwrap();
        }
        for guard in &graph.guards {
            writeln!(out, "{indent}guard {};", self.record(guard)?).unwrap();
        }
        for resource in &graph.resources {
            writeln!(out, "{indent}resource {};", self.record(resource)?).unwrap();
        }
        if !graph.completions.is_empty() {
            writeln!(out, "{indent}completions ({});", names(&graph.completions)).unwrap();
        }
        for (name, value) in &graph.values {
            let dtype = serde_json::to_value(value.tensor.dtype)?
                .as_str()
                .unwrap()
                .to_owned();
            write!(
                out,
                "{indent}{} {}: {dtype}[{}]",
                if value.constant { "const" } else { "value" },
                quoted(name),
                value
                    .tensor
                    .shape
                    .iter()
                    .map(expression)
                    .collect::<Vec<_>>()
                    .join(", ")
            )
            .unwrap();
            if let Some(q) = &value.tensor.quant {
                write!(out, " quant q{}", self.quant_ids[&semantic_digest(q)?]).unwrap();
            }
            if let Some(data) = &value.data {
                write!(out, " data {}", self.record(data)?).unwrap();
            }
            if !value.floats.is_empty() {
                write!(
                    out,
                    " floats {}",
                    self.value(&serde_json::to_value(&value.floats)?, true)?
                )
                .unwrap();
            }
            if !value.integers.is_empty() {
                write!(out, " integers {}", self.record(&value.integers)?).unwrap();
            }
            if let Some(resource) = &value.resource {
                write!(out, " resource {}", self.record(resource)?).unwrap();
            }
            out.push_str(";\n");
        }
        writeln!(out, "{indent}inputs ({});", names(&graph.inputs)).unwrap();
        writeln!(out, "{indent}outputs ({});", names(&graph.outputs)).unwrap();
        for (name, function) in &graph.functions {
            writeln!(out, "{indent}fn {} {{", quoted(name)).unwrap();
            self.graph(function, out, depth + 1)?;
            writeln!(out, "{indent}}}").unwrap();
        }
        for node in &graph.nodes {
            write!(
                out,
                "{indent}node {} ({}) -> ({})",
                node.op.name(),
                names(&node.inputs),
                names(&node.outputs)
            )
            .unwrap();
            let attrs = sparse(&node.attributes, &Attributes::default())?;
            if !attrs.as_object().unwrap().is_empty() {
                write!(out, " attrs {}", self.value(&attrs, false)?).unwrap();
            }
            if !node.waits.is_empty() {
                write!(out, " waits ({})", names(&node.waits)).unwrap();
            }
            if !node.completes.is_empty() {
                write!(out, " completes ({})", names(&node.completes)).unwrap();
            }
            if !node.scope.is_empty() {
                write!(out, " scope {}", quoted(&node.scope)).unwrap();
            }
            out.push_str(";\n");
        }
        Ok(())
    }
}

pub struct EncodedProgram {
    pub text: String,
    /// Names are SHA-256 identities, without a path or extension.
    pub blobs: BTreeMap<String, Vec<u8>>,
}
pub fn encode(program: &Program) -> Result<EncodedProgram> {
    if program.version != 1 {
        return Err(Error::invalid("Unsupported semantic program version"));
    }
    let mut writer = Printer {
        quant: vec![],
        quant_ids: HashMap::new(),
        arrays: vec![],
        array_ids: HashMap::new(),
        spans: HashMap::new(),
        pool: vec![],
    };
    for graph in program.phases.values() {
        writer.collect(graph, 0)?;
    }
    let mut body = String::new();
    for id in 0..writer.quant.len() {
        let q = writer.quant[id];
        let mut value = serde_json::to_value(q)?;
        let fields = value.as_object_mut().unwrap();
        if q.scales.is_empty() {
            fields.remove("scales");
        }
        if q.zeros.is_empty() {
            fields.remove("zeros");
        }
        if q.parameters.is_none() {
            fields.remove("parameters");
        }
        if !q.blockwise {
            fields.remove("blockwise");
        }
        writeln!(body, "  quant q{id} {};", writer.value(&value, false)?).unwrap();
    }
    let options = sparse(&program.options, &CompileOptions::default())?;
    if !options.as_object().unwrap().is_empty() {
        writeln!(body, "  options {};", writer.value(&options, false)?).unwrap();
    }
    for (name, options) in &program.phase_options {
        let options = sparse(options, &CompileOptions::default())?;
        writeln!(
            body,
            "  phase_options {} {};",
            quoted(name),
            writer.value(&options, false)?
        )
        .unwrap();
    }
    for (name, graph) in &program.phases {
        writeln!(body, "  phase {} {{", quoted(name)).unwrap();
        writer.graph(graph, &mut body, 2)?;
        body.push_str("  }\n");
    }
    let mut text = "ynn_program 1 {\n".to_owned();
    let mut blobs = BTreeMap::new();
    for chunk in writer.pool.chunks(CHUNK_BYTES) {
        let hash = format!("{:x}", Sha256::digest(chunk));
        writeln!(text, "  blob {} {};", quoted(&hash), chunk.len()).unwrap();
        blobs.insert(hash, chunk.to_vec());
    }
    for (id, a) in writer.arrays.iter().enumerate() {
        writeln!(
            text,
            "  array a{id} = {}({}, {});",
            a.kind, a.offset, a.count
        )
        .unwrap();
    }
    text.push_str(&body);
    text.push_str("}\n");
    if text.len() > MAX_TEXT {
        return Err(Error::invalid("Semantic source exceeds 32 MiB"));
    }
    Ok(EncodedProgram { text, blobs })
}

struct Parser<'a, F> {
    source: &'a str,
    lexer: Lexer<'a>,
    next: Token<'a>,
    load: F,
    pool: Vec<u8>,
    arrays: BTreeMap<String, Array>,
    quant: BTreeMap<String, Quantization>,
    blobs: BTreeMap<String, usize>,
    nodes: usize,
    scalars: usize,
}
impl<'a, F: FnMut(&str, usize) -> Result<Vec<u8>>> Parser<'a, F> {
    fn new(source: &'a str, load: F) -> Result<Self> {
        if source.len() > MAX_TEXT {
            return Err(Error::invalid("Semantic source exceeds 32 MiB"));
        }
        let mut lexer = Lexer::new(source);
        let next = lexer.next()?;
        Ok(Self {
            source,
            lexer,
            next,
            load,
            pool: vec![],
            arrays: BTreeMap::new(),
            quant: BTreeMap::new(),
            blobs: BTreeMap::new(),
            nodes: 0,
            scalars: 0,
        })
    }
    fn error(&self, message: impl std::fmt::Display) -> Error {
        diagnostic(self.source, self.next.span, message)
    }
    fn take(&mut self) -> Result<Token<'a>> {
        let old = self.next;
        self.next = self.lexer.next()?;
        Ok(old)
    }
    fn eat(&mut self, kind: Kind<'a>) -> Result<bool> {
        if self.next.kind != kind {
            return Ok(false);
        }
        self.take()?;
        Ok(true)
    }
    fn expect(&mut self, kind: Kind<'a>) -> Result<()> {
        if !self.eat(kind)? {
            return Err(self.error(format!("Expected {kind:?}")));
        }
        Ok(())
    }
    fn name(&mut self) -> Result<String> {
        match self.take()?.kind {
            Kind::Ident(s) | Kind::Tensor(s) | Kind::Symbol(s) => Ok(s.into()),
            Kind::String(s) => Ok(serde_json::from_str(s)?),
            _ => Err(self.error("Expected a name or string")),
        }
    }
    fn count(&mut self) -> Result<usize> {
        if let Kind::Number(s) = self.take()?.kind {
            if let Ok(n) = s.parse() {
                return Ok(n);
            }
        }
        Err(self.error("Expected a nonnegative integer"))
    }
    fn account(&mut self, n: usize) -> Result<()> {
        self.scalars = self
            .scalars
            .checked_add(n)
            .filter(|&n| n <= MAX_SCALARS)
            .ok_or_else(|| self.error("Expanded numeric metadata exceeds limit"))?;
        Ok(())
    }
    fn number_text(&mut self) -> Result<String> {
        let negative = self.eat(Kind::Punct(b'-'))?;
        match self.take()?.kind {
            Kind::Number(s) => Ok(format!("{}{s}", if negative { "-" } else { "" })),
            _ => Err(self.error("Expected a numeric literal")),
        }
    }
    fn value(&mut self, depth: usize) -> Result<Json> {
        self.nodes += 1;
        if depth > 64 || self.nodes > 4_000_000 {
            return Err(self.error("Semantic syntax nesting/node limit exceeded"));
        }
        match self.next.kind {
            Kind::Number(_) | Kind::Punct(b'-') => Ok(serde_json::from_str(&self.number_text()?)?),
            Kind::String(s) => {
                self.take()?;
                Ok(Json::String(serde_json::from_str(s)?))
            }
            Kind::Ident("true") => {
                self.take()?;
                Ok(Json::Bool(true))
            }
            Kind::Ident("false") => {
                self.take()?;
                Ok(Json::Bool(false))
            }
            Kind::Ident("null") => {
                self.take()?;
                Ok(Json::Null)
            }
            Kind::Punct(b'[') => {
                self.take()?;
                let mut values = Vec::new();
                if !self.eat(Kind::Punct(b']'))? {
                    loop {
                        values.push(self.value(depth + 1)?);
                        if self.eat(Kind::Punct(b']'))? {
                            break;
                        }
                        self.expect(Kind::Punct(b','))?;
                    }
                }
                Ok(Json::Array(values))
            }
            Kind::Punct(b'{') => {
                self.take()?;
                let mut values = serde_json::Map::new();
                if !self.eat(Kind::Punct(b'}'))? {
                    loop {
                        let key = self.name()?;
                        self.expect(Kind::Punct(b':'))?;
                        let value = self.value(depth + 1)?;
                        if values.insert(key, value).is_some() {
                            return Err(self.error("Duplicate record field"));
                        }
                        if self.eat(Kind::Punct(b'}'))? {
                            break;
                        }
                        self.expect(Kind::Punct(b','))?;
                    }
                }
                Ok(Json::Object(values))
            }
            Kind::Punct(b'@') => {
                self.take()?;
                let name = self.name()?;
                let a = self
                    .arrays
                    .get(&name)
                    .cloned()
                    .ok_or_else(|| self.error("Undefined numeric array"))?;
                self.account(a.count)?;
                let mut values = Vec::with_capacity(a.count);
                for b in self.pool[a.offset..a.offset + a.count * 8].chunks_exact(8) {
                    let bits = u64::from_le_bytes(b.try_into().unwrap());
                    values.push(if a.kind == "i64" {
                        Json::from(bits as i64)
                    } else {
                        Json::from(bits)
                    });
                }
                Ok(Json::Array(values))
            }
            Kind::Ident("real") => {
                self.take()?;
                self.expect(Kind::Punct(b'('))?;
                let text = self.number_text()?;
                let n = text
                    .parse::<f64>()
                    .map_err(|_| self.error("Invalid binary64 literal"))?;
                if !n.is_finite() {
                    return Err(self.error("Use bits() for nonfinite values"));
                }
                self.expect(Kind::Punct(b')'))?;
                Ok(Json::from(n.to_bits()))
            }
            Kind::Ident("bits") => {
                self.take()?;
                self.expect(Kind::Punct(b'('))?;
                let s = self.name()?;
                if s.len() != 16 {
                    return Err(self.error("Expected 16 hexadecimal digits"));
                }
                let n =
                    u64::from_str_radix(&s, 16).map_err(|_| self.error("Invalid bit pattern"))?;
                self.expect(Kind::Punct(b')'))?;
                Ok(Json::from(n))
            }
            Kind::Ident("repeat") => {
                self.take()?;
                self.expect(Kind::Punct(b'('))?;
                let value = self.value(depth + 1)?;
                if !value.is_number() {
                    return Err(self.error("repeat() requires a numeric scalar"));
                }
                self.expect(Kind::Punct(b','))?;
                let count = self.count()?;
                self.expect(Kind::Punct(b')'))?;
                self.account(count)?;
                Ok(Json::Array(vec![value; count]))
            }
            Kind::Ident(name)
                if [
                    "known",
                    "symbol",
                    "add",
                    "mul",
                    "min",
                    "max",
                    "floor_div",
                    "ceil_div",
                ]
                .contains(&name) =>
            {
                self.take()?;
                self.expect(Kind::Punct(b'('))?;
                let value = self.value(depth + 1)?;
                self.expect(Kind::Punct(b')'))?;
                Ok(Json::Object(serde_json::Map::from_iter([(
                    name.into(),
                    value,
                )])))
            }
            _ => Err(self.error("Expected a semantic attribute value")),
        }
    }
    fn typed<T: DeserializeOwned>(&mut self) -> Result<T> {
        let value = self.value(0)?;
        serde_json::from_value(value).map_err(|e| self.error(e))
    }
    fn expression(&mut self, depth: usize) -> Result<Expr> {
        if depth > 64 {
            return Err(self.error("Dimension expression nesting limit exceeded"));
        }
        match self.next.kind {
            Kind::Number(_) | Kind::Punct(b'-') => self
                .number_text()?
                .parse::<i64>()
                .map(Expr::Known)
                .map_err(|_| self.error("Invalid dimension literal")),
            Kind::Ident(name)
                if name.starts_with('s') && name[1..].bytes().all(|b| b.is_ascii_digit()) =>
            {
                self.take()?;
                name[1..]
                    .parse::<u32>()
                    .map(Expr::Symbol)
                    .map_err(|_| self.error("Invalid symbol ID"))
            }
            Kind::Ident(name)
                if ["add", "mul", "min", "max", "floor_div", "ceil_div"].contains(&name) =>
            {
                self.take()?;
                self.expect(Kind::Punct(b'('))?;
                let mut xs = Vec::new();
                if !self.eat(Kind::Punct(b')'))? {
                    loop {
                        xs.push(self.expression(depth + 1)?);
                        if self.eat(Kind::Punct(b')'))? {
                            break;
                        }
                        self.expect(Kind::Punct(b','))?;
                    }
                }
                Ok(match name {
                    "add" => Expr::Add(xs),
                    "mul" => Expr::Mul(xs),
                    "min" => Expr::Min(xs),
                    "max" => Expr::Max(xs),
                    "floor_div" => Expr::FloorDiv(xs),
                    _ => Expr::CeilDiv(xs),
                })
            }
            _ => Err(self.error("Expected a dimension expression")),
        }
    }
    fn names(&mut self) -> Result<Vec<String>> {
        self.expect(Kind::Punct(b'('))?;
        let mut names = Vec::new();
        if !self.eat(Kind::Punct(b')'))? {
            loop {
                names.push(self.name()?);
                if self.eat(Kind::Punct(b')'))? {
                    break;
                }
                self.expect(Kind::Punct(b','))?;
            }
        }
        Ok(names)
    }
    fn graph(&mut self, depth: usize) -> Result<Graph> {
        if depth > 64 {
            return Err(self.error("Semantic function nesting limit exceeded"));
        }
        self.expect(Kind::Punct(b'{'))?;
        let mut graph = Graph::default();
        let (mut inputs, mut outputs, mut completions) = (false, false, false);
        while !self.eat(Kind::Punct(b'}'))? {
            let kind = self.name()?;
            match kind.as_str() {
                "value" | "const" => {
                    let name = self.name()?;
                    self.expect(Kind::Punct(b':'))?;
                    let dtype: Dtype = serde_json::from_value(Json::String(self.name()?))
                        .map_err(|e| self.error(e))?;
                    self.expect(Kind::Punct(b'['))?;
                    let mut shape = Vec::new();
                    if !self.eat(Kind::Punct(b']'))? {
                        loop {
                            shape.push(self.expression(0)?);
                            if self.eat(Kind::Punct(b']'))? {
                                break;
                            }
                            self.expect(Kind::Punct(b','))?;
                        }
                    }
                    let mut value = Value {
                        tensor: TensorType {
                            dtype,
                            shape,
                            quant: None,
                        },
                        constant: kind == "const",
                        ..Default::default()
                    };
                    let mut fields = std::collections::BTreeSet::new();
                    while !self.eat(Kind::Punct(b';'))? {
                        let field = self.name()?;
                        if !fields.insert(field.clone()) {
                            return Err(self.error("Duplicate value field"));
                        }
                        match field.as_str() {
                            "quant" => {
                                let q = self.name()?;
                                let count = self
                                    .quant
                                    .get(&q)
                                    .map(|q| q.scales.len() + q.zeros.len())
                                    .ok_or_else(|| self.error("Undefined quantization"))?;
                                self.account(count)?;
                                value.tensor.quant = Some(self.quant[&q].clone());
                            }
                            "data" => value.data = Some(self.typed()?),
                            "resource" => value.resource = Some(self.typed()?),
                            "floats" => value.floats = self.typed()?,
                            "integers" => value.integers = self.typed()?,
                            _ => return Err(self.error("Unknown value field")),
                        }
                    }
                    if graph.values.insert(name, value).is_some() {
                        return Err(self.error("Duplicate value declaration"));
                    }
                }
                "node" => {
                    let op = serde_json::from_value(Json::String(self.name()?))
                        .map_err(|e| self.error(e))?;
                    let args = self.names()?;
                    self.expect(Kind::Punct(b'-'))?;
                    self.expect(Kind::Punct(b'>'))?;
                    let results = self.names()?;
                    let mut node = Node {
                        op,
                        inputs: args,
                        outputs: results,
                        attributes: Attributes::default(),
                        waits: vec![],
                        completes: vec![],
                        scope: String::new(),
                    };
                    let mut fields = std::collections::BTreeSet::new();
                    while !self.eat(Kind::Punct(b';'))? {
                        let field = self.name()?;
                        if !fields.insert(field.clone()) {
                            return Err(self.error("Duplicate node field"));
                        }
                        match field.as_str() {
                            "attrs" => node.attributes = self.typed()?,
                            "waits" => node.waits = self.names()?,
                            "completes" => node.completes = self.names()?,
                            "scope" => node.scope = self.name()?,
                            _ => return Err(self.error("Unknown node field")),
                        }
                    }
                    graph.nodes.push(node);
                }
                "fn" => {
                    let name = self.name()?;
                    let function = self.graph(depth + 1)?;
                    if graph.functions.insert(name, function).is_some() {
                        return Err(self.error("Duplicate function"));
                    }
                }
                "inputs" | "outputs" | "completions" => {
                    let (seen, values) = match kind.as_str() {
                        "inputs" => (&mut inputs, &mut graph.inputs),
                        "outputs" => (&mut outputs, &mut graph.outputs),
                        _ => (&mut completions, &mut graph.completions),
                    };
                    if *seen {
                        return Err(self.error("Duplicate graph interface"));
                    }
                    *seen = true;
                    *values = self.names()?;
                    self.expect(Kind::Punct(b';'))?;
                }
                "symbol" => {
                    graph.symbols.push(self.typed()?);
                    self.expect(Kind::Punct(b';'))?;
                }
                "guard" => {
                    graph.guards.push(self.typed()?);
                    self.expect(Kind::Punct(b';'))?;
                }
                "resource" => {
                    graph.resources.push(self.typed()?);
                    self.expect(Kind::Punct(b';'))?;
                }
                _ => return Err(self.error("Unknown semantic graph statement")),
            }
            if graph.values.len() > 100_000 || graph.nodes.len() > 500_000 {
                return Err(self.error("Semantic graph size limit exceeded"));
            }
        }
        if !inputs || !outputs {
            return Err(self.error("Graph requires inputs and outputs declarations"));
        }
        Ok(graph)
    }
    fn program(&mut self) -> Result<Program> {
        self.expect(Kind::Ident("ynn_program"))?;
        if self.count()? != 1 {
            return Err(self.error("Unsupported semantic DSL version"));
        }
        self.expect(Kind::Punct(b'{'))?;
        let mut program = Program::default();
        let mut options = false;
        while !self.eat(Kind::Punct(b'}'))? {
            let kind = self.name()?;
            match kind.as_str() {
                "blob" => {
                    if !self.arrays.is_empty()
                        || !self.quant.is_empty()
                        || !program.phases.is_empty()
                    {
                        return Err(self.error("Numeric blobs must precede declarations"));
                    }
                    let hash = self.name()?;
                    let bytes = self.count()?;
                    if hash.len() != 64
                        || !hash
                            .bytes()
                            .all(|b| b.is_ascii_digit() || (b'a'..=b'f').contains(&b))
                        || bytes == 0
                        || bytes > CHUNK_BYTES
                        || bytes > MAX_POOL.saturating_sub(self.pool.len())
                    {
                        return Err(self.error("Invalid numeric blob identity or size"));
                    }
                    let data = (self.load)(&hash, bytes)?;
                    if data.len() != bytes || format!("{:x}", Sha256::digest(&data)) != hash {
                        return Err(self.error("Numeric blob identity mismatch"));
                    }
                    self.pool.extend_from_slice(&data);
                    self.blobs.insert(hash, bytes);
                    self.expect(Kind::Punct(b';'))?;
                }
                "array" => {
                    if !self.quant.is_empty() || !program.phases.is_empty() {
                        return Err(self.error("Numeric arrays must precede uses"));
                    }
                    let name = self.name()?;
                    self.expect(Kind::Punct(b'='))?;
                    let kind = self.name()?;
                    if !["u64", "i64", "r64"].contains(&kind.as_str()) {
                        return Err(self.error("Unknown numeric array type"));
                    }
                    self.expect(Kind::Punct(b'('))?;
                    let offset = self.count()?;
                    self.expect(Kind::Punct(b','))?;
                    let count = self.count()?;
                    self.expect(Kind::Punct(b')'))?;
                    self.expect(Kind::Punct(b';'))?;
                    if offset % 8 != 0
                        || count
                            .checked_mul(8)
                            .and_then(|n| offset.checked_add(n))
                            .is_none_or(|end| end > self.pool.len())
                    {
                        return Err(self.error("Numeric array is outside the verified pool"));
                    }
                    if self
                        .arrays
                        .insert(
                            name,
                            Array {
                                kind,
                                offset,
                                count,
                            },
                        )
                        .is_some()
                    {
                        return Err(self.error("Duplicate numeric array"));
                    }
                }
                "quant" => {
                    if !program.phases.is_empty() {
                        return Err(self.error("Quantization declarations must precede phases"));
                    }
                    let name = self.name()?;
                    let value = self.typed()?;
                    self.expect(Kind::Punct(b';'))?;
                    if self.quant.insert(name, value).is_some() {
                        return Err(self.error("Duplicate quantization declaration"));
                    }
                }
                "options" => {
                    if options {
                        return Err(self.error("Duplicate compiler options"));
                    }
                    options = true;
                    program.options = self.typed()?;
                    self.expect(Kind::Punct(b';'))?;
                }
                "phase_options" => {
                    let name = self.name()?;
                    let value = self.typed()?;
                    self.expect(Kind::Punct(b';'))?;
                    if program.phase_options.insert(name, value).is_some() {
                        return Err(self.error("Duplicate phase options"));
                    }
                }
                "phase" => {
                    let name = self.name()?;
                    let graph = self.graph(0)?;
                    if program.phases.insert(name, graph).is_some() {
                        return Err(self.error("Duplicate phase"));
                    }
                }
                _ => return Err(self.error("Unknown semantic program statement")),
            }
        }
        self.expect(Kind::Eof)?;
        if program.phases.is_empty() {
            return Err(self.error("Semantic program has no phases"));
        }
        Ok(program)
    }
}

pub fn decode(source: &str, load: impl FnMut(&str, usize) -> Result<Vec<u8>>) -> Result<Program> {
    Parser::new(source, load)?.program()
}
fn limited(path: &Path, limit: usize) -> Result<Vec<u8>> {
    let mut data = Vec::new();
    std::fs::File::open(path)?
        .take(limit as u64 + 1)
        .read_to_end(&mut data)?;
    if data.len() > limit {
        return Err(Error::invalid("Semantic artifact exceeds size limit"));
    }
    Ok(data)
}
fn read_document(path: &Path) -> Result<(Program, BTreeMap<String, usize>)> {
    let bytes = limited(path, MAX_TEXT)?;
    let source =
        std::str::from_utf8(&bytes).map_err(|_| Error::invalid("Semantic source is not UTF-8"))?;
    let root = path.parent().unwrap_or(Path::new("."));
    let mut parser = Parser::new(source, |hash: &str, bytes| {
        limited(
            &root.join("program-data").join(format!("{hash}.bin")),
            bytes,
        )
    })?;
    let program = parser.program()?;
    Ok((program, parser.blobs))
}
pub fn read(path: &Path) -> Result<Program> {
    read_document(path).map(|(program, _)| program)
}
pub fn write(path: &Path, program: &Program) -> Result<()> {
    if path.exists() {
        return Err(Error::invalid("Semantic output already exists"));
    }
    let encoded = encode(program)?;
    let root = path.parent().unwrap_or(Path::new("."));
    std::fs::create_dir_all(root)?;
    if !encoded.blobs.is_empty() {
        std::fs::create_dir_all(root.join("program-data"))?;
    }
    for (hash, bytes) in encoded.blobs {
        let dest = root.join("program-data").join(format!("{hash}.bin"));
        if dest.exists() {
            if limited(&dest, CHUNK_BYTES)? != bytes {
                return Err(Error::invalid("Existing numeric blob differs"));
            }
        } else {
            let mut file = std::fs::OpenOptions::new()
                .write(true)
                .create_new(true)
                .open(dest)?;
            file.write_all(&bytes)?;
        }
    }
    let mut file = std::fs::OpenOptions::new()
        .write(true)
        .create_new(true)
        .open(path)?;
    file.write_all(encoded.text.as_bytes())?;
    Ok(())
}
/// Validate source and numeric payloads, without loading weights or compiling.
pub fn inspect(path: &Path) -> Result<Json> {
    let (program, blobs) = read_document(path)?;
    fn assets(graph: &Graph, out: &mut Vec<crate::compiler::Asset>) {
        out.extend(graph.values.values().filter_map(|v| v.data.clone()));
        for function in graph.functions.values() {
            assets(function, out);
        }
    }
    let mut source_assets = Vec::new();
    for graph in program.phases.values() {
        assets(graph, &mut source_assets);
    }
    let files = blobs.into_iter().map(|(hash, bytes)| json!({"path":format!("program-data/{hash}.bin"), "bytes":bytes, "sha256":hash})).collect::<Vec<_>>();
    Ok(json!({"format":"ynn-semantic-program", "version":1,
        "semantic_sha256":semantic_digest(&program)?, "phases":program.phases.keys().collect::<Vec<_>>(),
        "source_assets":source_assets, "numeric_files":files}))
}

#[cfg(test)]
mod tests;
