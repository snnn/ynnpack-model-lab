// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
use super::schema;
use crate::plan::{Arg, Expr, Op, Plan, RawCommand, INVALID};
use crate::{Error, Result};
use std::collections::{HashMap, HashSet};
use std::fmt::Write;

fn quoted(value: &str) -> String {
    // JSON string escaping is also the source language's string escaping.
    serde_json::to_string(value).unwrap()
}
fn list(values: impl IntoIterator<Item = String>) -> String {
    format!("[{}]", values.into_iter().collect::<Vec<_>>().join(", "))
}
fn alias(name: &str, fallback: &str, used: &mut HashSet<String>) -> String {
    let mut result: String = name
        .chars()
        .take(48)
        .map(|c| {
            if c.is_ascii_alphanumeric() || c == '_' {
                c
            } else {
                '_'
            }
        })
        .collect();
    if result.is_empty() || result.chars().all(|c| c == '_') {
        result = fallback.into();
    }
    if result.as_bytes()[0].is_ascii_digit() {
        result.insert(0, '_');
    }
    while !used.insert(result.clone()) {
        result.push('_');
        result.push_str(fallback);
    }
    result
}
struct Names {
    tensors: Vec<String>,
    symbols: HashMap<u32, String>,
    expressions: HashMap<Expr, String>,
}
impl Names {
    fn new(plan: &Plan) -> Self {
        let mut tensors = Vec::new();
        let mut symbols = HashMap::new();
        let mut used = HashSet::from(["none".into(), "true".into(), "false".into()]);
        for c in &plan.commands {
            if c.op.declares_tensor() {
                tensors.push(alias(
                    c.args[1].text(),
                    &format!("v{}", tensors.len()),
                    &mut used,
                ));
            }
        }
        for c in &plan.commands {
            if c.op == Op::Symbol {
                let id = c.args[0].int() as u32;
                let fallback = format!("s{id}");
                let name = if c.args[1].text() == "Axis" {
                    fallback.as_str()
                } else {
                    c.args[4].text()
                };
                symbols.insert(id, alias(name, &fallback, &mut used));
            }
        }
        Self {
            tensors,
            symbols,
            expressions: HashMap::new(),
        }
    }
    fn tensor(&self, id: i64) -> Result<String> {
        self.tensors
            .get(id as usize)
            .map(|n| n.clone())
            .ok_or_else(|| Error::invalid("Cannot print an undeclared tensor"))
    }
    fn symbol(&self, id: u32) -> Result<String> {
        self.symbols
            .get(&id)
            .map(|n| n.clone())
            .ok_or_else(|| Error::invalid("Cannot print an undeclared symbol"))
    }
    fn expr(&self, e: &Expr) -> Result<String> {
        if let Some(name) = self.expressions.get(e) {
            return Ok(name.clone());
        }
        let (name, xs) = match e {
            Expr::Known(n) => return Ok(n.to_string()),
            Expr::Symbol(id) => return self.symbol(*id),
            Expr::Add(xs) => ("add", xs),
            Expr::Mul(xs) => ("mul", xs),
            Expr::Min(xs) => ("min", xs),
            Expr::Max(xs) => ("max", xs),
            Expr::FloorDiv(xs) => ("floor_div", xs),
            Expr::CeilDiv(xs) => ("ceil_div", xs),
        };
        if xs.len() == 2 && matches!(name, "add" | "mul" | "floor_div") {
            let operator = match name {
                "add" => "+",
                "mul" => "*",
                _ => "//",
            };
            return Ok(format!(
                "({} {operator} {})",
                self.expr(&xs[0])?,
                self.expr(&xs[1])?
            ));
        }
        Ok(format!(
            "{name}({})",
            xs.iter()
                .map(|x| self.expr(x))
                .collect::<Result<Vec<_>>>()?
                .join(", ")
        ))
    }
    fn arg(&self, a: &Arg, kind: &str, field: &str) -> Result<String> {
        Ok(match a {
            Arg::Int(n) if field == "flags" && (0..=3).contains(n) => list(
                [(1, "input"), (2, "output")]
                    .iter()
                    .filter(|(b, _)| n & b != 0)
                    .map(|(_, n)| n.to_string()),
            ),
            Arg::Int(n) if kind == "optional" && *n == INVALID => "none".into(),
            Arg::Int(n) if matches!(kind, "id" | "optional" | "operand") => self.tensor(*n)?,
            Arg::Native(n) => format!("native({})", self.tensor(*n)?),
            Arg::Int(n) => n.to_string(),
            Arg::Bool(b) => b.to_string(),
            Arg::Text(s) => quoted(s),
            Arg::Dtype(s) | Arg::Binary(s) | Arg::Unary(s) | Arg::Reduce(s) => s.clone(),
            Arg::Float(s) => float(s),
            Arg::Encoding(e) => format!(
                "encoding(dtype={}, axis={}, scales={}, zero_points={})",
                e.dtype,
                e.axis.map_or("none".into(), |a| a.to_string()),
                list(e.scales.iter().map(|s| float(s))),
                list(e.zero_points.iter().map(ToString::to_string))
            ),
            Arg::Ints(xs) if kind == "ids" => list(
                xs.iter()
                    .map(|&v| self.tensor(v))
                    .collect::<Result<Vec<_>>>()?,
            ),
            Arg::Ints(xs) => list(xs.iter().map(ToString::to_string)),
            Arg::Texts(xs) => list(xs.iter().map(|s| quoted(s))),
            Arg::Floats(xs) => list(xs.iter().map(|s| float(s))),
            Arg::Expr(e) => self.expr(e)?,
            Arg::Exprs(xs) => list(
                xs.iter()
                    .map(|e| self.expr(e))
                    .collect::<Result<Vec<_>>>()?,
            ),
            Arg::Data(None) => "none".into(),
            Arg::Data(Some(data)) => format!(
                "asset(path={}, bytes={}, sha256={})",
                quoted(&data.path),
                data.bytes,
                quoted(&data.sha256)
            ),
        })
    }
}

fn float(bits: &str) -> String {
    let n = f64::from_bits(u64::from_str_radix(bits, 16).unwrap());
    let decimal = n.to_string();
    let scientific = format!("{n:e}");
    let text = if scientific.len() < decimal.len() {
        scientific
    } else {
        decimal
    };
    if text
        .parse::<f64>()
        .ok()
        .map(|n| format!("{:016x}", n.to_bits()))
        .as_deref()
        == Some(bits)
    {
        text
    } else {
        format!("bits({})", quoted(bits))
    }
}
fn fields(names: &Names, c: &RawCommand) -> Result<Vec<String>> {
    c.op.fields()
        .iter()
        .zip(c.op.signature())
        .zip(&c.args)
        .map(|((f, k), a)| Ok(format!("{f}={}", names.arg(a, k, f)?)))
        .collect()
}
fn same(a: &Arg, b: &Arg) -> bool {
    a == b
}
struct Printer<'a> {
    plan: &'a Plan,
    names: Names,
    declarations: Vec<&'a RawCommand>,
    runtime_names: Vec<String>,
    body: String,
    metadata: Vec<String>,
    produced: HashSet<i64>,
    deferred: HashSet<i64>,
    resources: HashSet<i64>,
    emitted: HashSet<i64>,
    binding_order: Vec<i64>,
    auto: bool,
}
impl Printer<'_> {
    fn line(&mut self, depth: usize, line: &str) {
        if line.is_empty() {
            self.body.push('\n');
        } else {
            writeln!(self.body, "{}{}", "  ".repeat(depth), line.trim_end()).unwrap();
        }
    }
    fn tensor_type(&self, id: i64, logical: Option<&[Expr]>) -> Result<String> {
        let decl = self.declarations[id as usize];
        let dtype = match &decl.args[2] {
            Arg::Dtype(s) => s.clone(),
            Arg::Int(n) => format!("packed_i{n}"),
            _ => unreachable!(),
        };
        let dims = if let Some(xs) = logical {
            list(
                xs.iter()
                    .map(|e| self.names.expr(e))
                    .collect::<Result<Vec<_>>>()?,
            )
        } else {
            self.names.arg(&decl.args[3], "sizes", "dims")?
        };
        Ok(if logical.is_some() {
            format!("{dtype}{dims}")
        } else {
            format!("storage<{dtype}{dims}>")
        })
    }
    fn storage_metadata(&mut self, id: i64, logical: &[Expr]) -> Result<()> {
        let default = Arg::Ints(
            logical
                .iter()
                .map(|e| if let Expr::Known(n) = e { *n } else { 0 })
                .collect(),
        );
        if !same(&default, &self.declarations[id as usize].args[3]) {
            self.metadata.push(format!(
                "storage {} = {};",
                self.names.tensor(id)?,
                self.names
                    .arg(&self.declarations[id as usize].args[3], "sizes", "dims")?
            ));
        }
        Ok(())
    }
    fn declaration(&mut self, id: i64, logical: Option<&[Expr]>, depth: usize) -> Result<()> {
        let decl = self.declarations[id as usize];
        let flags = if matches!(decl.op, Op::ConstantOutput | Op::PackedConstantOutput) {
            2
        } else {
            decl.args[4].int()
        };
        let has_data = matches!(decl.args.last(), Some(Arg::Data(Some(_))));
        let role = if self.resources.contains(&id) {
            "state"
        } else if flags & 1 != 0 {
            "input"
        } else if has_data {
            "weight"
        } else {
            "value"
        };
        let data = if has_data {
            format!(" = asset(a{id})")
        } else {
            String::new()
        };
        let annotation = if logical.is_some_and(|xs| xs.iter().all(|e| matches!(e, Expr::Known(_))))
        {
            "@shape() "
        } else {
            ""
        };
        self.line(
            depth,
            &format!(
                "{annotation}{role} {}: {}{data};",
                self.names.tensor(id)?,
                self.tensor_type(id, logical)?
            ),
        );
        if let Some(xs) = logical {
            self.storage_metadata(id, xs)?;
        }
        self.emitted.insert(id);
        self.binding_order.push(id);
        Ok(())
    }
    fn computation(
        &mut self,
        i: usize,
        profile: Option<&RawCommand>,
        depth: usize,
        grouped: bool,
    ) -> Result<usize> {
        let c = &self.plan.commands[i];
        let outputs = schema::results(c);
        let mut next = i + 1 + usize::from(profile.is_some()); // skip the matching profile end
        let mut shapes = HashMap::new();
        for &id in &outputs {
            if let Some(shape) = self
                .plan
                .commands
                .get(next)
                .filter(|cmd| cmd.op == Op::ResultShape && cmd.args[0].int() == id)
            {
                let Arg::Exprs(xs) = &shape.args[1] else {
                    unreachable!()
                };
                shapes.insert(id, xs.as_slice());
                next += 1;
            }
        }
        let bindings = outputs
            .iter()
            .map(|&id| {
                Ok(format!(
                    "{}: {}",
                    self.names.tensor(id)?,
                    self.tensor_type(id, shapes.get(&id).copied())?
                ))
            })
            .collect::<Result<Vec<_>>>()?;
        let bindings = if outputs.len() == 1 {
            bindings[0].clone()
        } else {
            format!("({})", bindings.join(", "))
        };
        let mut arguments = Vec::new();
        let mut named = false;
        for ((field, kind), arg) in c.op.fields().iter().zip(c.op.signature()).zip(&c.args) {
            if schema::output(c.op, field)
                || matches!(c.op, Op::Binary | Op::Compare | Op::Unary | Op::Reduce) && *field == "operator"
            {
                continue;
            }
            let value = self.names.arg(arg, kind, field)?;
            if !named && matches!(*kind, "id" | "operand" | "ids" | "optional") {
                arguments.push(value);
            } else {
                named = true;
                arguments.push(format!("{field}={value}"));
            }
        }
        let prefix = format!("let {bindings} = {}(", schema::surface(c));
        if prefix.len() + arguments.iter().map(|s| s.len() + 2).sum::<usize>() < 180 {
            self.line(depth, &format!("{prefix}{});", arguments.join(", ")));
        } else {
            self.line(depth, &prefix);
            // Wrap by width, not one line per attribute.
            let mut row = String::new();
            for a in arguments {
                if !row.is_empty() && row.len() + a.len() > 140 {
                    self.line(depth + 1, &row);
                    row.clear();
                }
                row.push_str(&a);
                row.push_str(", ");
            }
            if !row.is_empty() {
                self.line(depth + 1, row.trim_end());
            }
            self.line(depth, ");");
        }
        for &id in &outputs {
            if let Some(xs) = shapes.get(&id) {
                self.storage_metadata(id, xs)?;
            }
            self.emitted.insert(id);
            self.binding_order.push(id);
        }
        if !grouped {
            if let Some(profile) = profile {
                let defaults = schema::profile(c, &self.runtime_names);
                let differences = profile
                    .args
                    .iter()
                    .zip(&defaults)
                    .zip(Op::BeginProfileOperation.fields())
                    .zip(Op::BeginProfileOperation.signature())
                    .filter(|(((a, b), _), _)| !same(a, b))
                    .map(|(((a, _), field), kind)| {
                        Ok(format!("{field}={}", self.names.arg(a, kind, field)?))
                    })
                    .collect::<Result<Vec<_>>>()?;
                if !differences.is_empty() {
                    self.metadata.push(format!(
                        "profile {} = profile({});",
                        self.names.tensor(outputs[0])?,
                        differences.join(", ")
                    ));
                }
            } else if self.auto {
                self.metadata.push(format!(
                    "profile {} = none;",
                    self.names.tensor(outputs[0])?
                ));
            }
        }
        Ok(next)
    }
    fn commands(&mut self, start: usize, end: usize, depth: usize, grouped: bool) -> Result<()> {
        let mut i = start;
        while i < end {
            let c = &self.plan.commands[i];
            if c.op.declares_tensor() {
                i += 1;
                continue;
            }
            if !grouped
                && c.op == Op::BeginProfileOperation
                && i + 2 < end
                && self.plan.commands[i + 2].op == Op::EndProfileOperation
                && !schema::results(&self.plan.commands[i + 1]).is_empty()
            {
                i = self.computation(i + 1, Some(c), depth, grouped)?;
                continue;
            }
            if !schema::results(c).is_empty() {
                i = self.computation(i, None, depth, grouped)?;
                continue;
            }
            match c.op {
                Op::Symbol => {
                    let a = &c.args;
                    let source = match a[1].text() {
                        "Axis" => {
                            format!("axis({}, {})", self.names.tensor(a[4].int())?, a[5].int())
                        }
                        kind => format!(
                            "{}({})",
                            if kind == "Parameter" {
                                "parameter"
                            } else {
                                "instance"
                            },
                            quoted(a[4].text())
                        ),
                    };
                    let name = self.names.symbol(a[0].int() as u32)?;
                    self.line(
                        depth,
                        &format!("dim {name} = {source} in {}..={};", a[2].int(), a[3].int()),
                    );
                    self.metadata
                        .push(format!("symbol {name} = {};", a[0].int()));
                }
                Op::InputShape
                    if self.deferred.contains(&c.args[0].int())
                        && !self.emitted.contains(&c.args[0].int()) =>
                {
                    let Arg::Exprs(xs) = &c.args[1] else {
                        unreachable!()
                    };
                    self.declaration(c.args[0].int(), Some(xs), depth)?;
                }
                Op::InputShape | Op::ResultShape => self.line(
                    depth,
                    &format!(
                        "{} {} = {};",
                        if c.op == Op::InputShape {
                            "input_shape"
                        } else {
                            "shape"
                        },
                        self.names.tensor(c.args[0].int())?,
                        self.names.arg(&c.args[1], "exprs", "shape")?
                    ),
                ),
                Op::Resource => {
                    let name = self.names.tensor(c.args[0].int())?;
                    self.line(
                        depth,
                        &format!(
                            "require committed({name}) == {};",
                            self.names.arg(&c.args[3], "expr", "entry_extent")?
                        ),
                    );
                    self.metadata.push(format!(
                        "resource {name} = resource(name={}, axis={}, encoding={});",
                        quoted(c.args[1].text()),
                        c.args[2].int(),
                        self.names.arg(&c.args[4], "encoding", "encoding")?
                    ));
                }
                Op::Guard => {
                    let annotation =
                        if c.args[3].text() == "require" && c.args[4].text() == "ordinary" {
                            String::new()
                        } else {
                            format!(
                                "@guard(message={}, mode={}) ",
                                quoted(c.args[3].text()),
                                self.names.arg(&c.args[4], "encoding", "encoding")?
                            )
                        };
                    self.line(
                        depth,
                        &format!(
                            "{annotation}require {} {} {};",
                            self.names.arg(&c.args[0], "expr", "lhs")?,
                            if c.args[2].text() == "eq" { "==" } else { "<=" },
                            self.names.arg(&c.args[1], "expr", "rhs")?
                        ),
                    );
                }
                Op::BeginProfileOperation | Op::BeginOperation => {
                    let end_op = if c.op == Op::BeginOperation {
                        Op::EndOperation
                    } else {
                        Op::EndProfileOperation
                    };
                    let mut nesting = 1;
                    let mut j = i + 1;
                    while j < end {
                        if self.plan.commands[j].op == c.op {
                            nesting += 1;
                        }
                        if self.plan.commands[j].op == end_op {
                            nesting -= 1;
                            if nesting == 0 {
                                break;
                            }
                        }
                        j += 1;
                    }
                    if j == end {
                        return Err(Error::invalid("Unbalanced command group"));
                    }
                    let mut args = fields(&self.names, c)?;
                    if c.op == Op::BeginOperation {
                        args.extend(fields(&self.names, &self.plan.commands[j])?);
                    }
                    self.line(
                        depth,
                        &format!(
                            "{}({}) {{",
                            if c.op == Op::BeginOperation {
                                "operation"
                            } else {
                                "profile"
                            },
                            args.join(", ")
                        ),
                    );
                    self.commands(i + 1, j, depth + 1, true)?;
                    self.line(depth, "}");
                    i = j;
                }
                _ => self.line(
                    depth,
                    &format!(
                        "{}({});",
                        schema::snake(c.op.name()),
                        fields(&self.names, c)?.join(", ")
                    ),
                ),
            }
            i += 1;
        }
        Ok(())
    }
}
pub(super) fn print(plan: &Plan) -> Result<String> {
    let declarations: Vec<_> = plan
        .commands
        .iter()
        .filter(|c| c.op.declares_tensor())
        .collect();
    let produced: HashSet<_> = plan.commands.iter().flat_map(schema::results).collect();
    let deferred = plan
        .commands
        .iter()
        .filter(|c| c.op == Op::InputShape && !produced.contains(&c.args[0].int()))
        .map(|c| c.args[0].int())
        .collect();
    let resources = plan
        .commands
        .iter()
        .filter(|c| c.op == Op::Resource)
        .map(|c| c.args[0].int())
        .collect();
    let auto = plan
        .commands
        .iter()
        .any(|c| c.op == Op::BeginProfileOperation);
    let mut p = Printer {
        plan,
        names: Names::new(plan),
        runtime_names: declarations
            .iter()
            .map(|d| d.args[1].text().into())
            .collect(),
        declarations,
        body: String::new(),
        metadata: Vec::new(),
        produced,
        deferred,
        resources,
        emitted: HashSet::new(),
        binding_order: Vec::new(),
        auto,
    };
    p.body = format!(
        "ynn {} resource_contract={} completion_contract={} profiling={} {{\n",
        plan.version,
        plan.resource_contract,
        plan.completion_contract,
        if auto { "auto" } else { "explicit" }
    );
    for id in 0..plan.value_count as i64 {
        let d = p.declarations[id as usize];
        let name = p.names.tensor(id)?;
        if name != d.args[1].text() {
            p.metadata
                .push(format!("name {name} = {};", quoted(d.args[1].text())));
        }
        if matches!(d.op, Op::ConstantOutput | Op::PackedConstantOutput) {
            p.metadata
                .push(format!("declaration {name} = {};", d.op.name()));
        }
        if let Some(Arg::Data(Some(_))) = d.args.last() {
            p.metadata.push(format!(
                "asset a{id} = {};",
                p.names.arg(d.args.last().unwrap(), "data", "data")?
            ));
        }
        if !p.produced.contains(&id) && !p.deferred.contains(&id) {
            p.declaration(id, None, 1)?;
        }
    }
    // Repeated expression trees become source aliases without changing their
    // grouping, term order, or serialized representation.
    let mut counts = HashMap::new();
    let mut ordered = Vec::new();
    fn count<'a>(e: &'a Expr, counts: &mut HashMap<&'a Expr, usize>, ordered: &mut Vec<&'a Expr>) {
        match e {
            Expr::Known(_) | Expr::Symbol(_) => return,
            Expr::Add(xs)
            | Expr::Mul(xs)
            | Expr::Min(xs)
            | Expr::Max(xs)
            | Expr::FloorDiv(xs)
            | Expr::CeilDiv(xs) => {
                for x in xs {
                    count(x, counts, ordered);
                }
            }
        }
        if !counts.contains_key(e) {
            ordered.push(e);
        }
        *counts.entry(e).or_default() += 1;
    }
    for c in &plan.commands {
        for a in &c.args {
            match a {
                Arg::Expr(e) => count(e, &mut counts, &mut ordered),
                Arg::Exprs(xs) => {
                    for e in xs {
                        count(e, &mut counts, &mut ordered);
                    }
                }
                _ => {}
            }
        }
    }
    let mut used: HashSet<_> = p
        .names
        .tensors
        .iter()
        .chain(p.names.symbols.values())
        .cloned()
        .collect();
    for e in ordered {
        if counts[e] < 3 || p.names.expressions.len() >= 64 {
            continue;
        }
        let text = p.names.expr(e)?;
        let named_view_expression = plan.commands.iter().any(|c| {
            c.op == Op::View
                && [3, 4]
                    .iter()
                    .any(|&i| matches!(&c.args[i],Arg::Expr(x) if x==e))
        });
        if text.len() < 32 && !named_view_expression {
            continue;
        }
        let fallback = format!("d{}", p.names.expressions.len());
        let hint = plan
            .commands
            .iter()
            .find_map(|c| {
                if c.op == Op::View {
                    for (i, n) in [(3, "begin"), (4, "end")] {
                        if matches!(&c.args[i],Arg::Expr(x) if x==e) {
                            return Some(n);
                        }
                    }
                }
                None
            })
            .unwrap_or(&fallback);
        let name = alias(hint, &fallback, &mut used);
        p.line(1, &format!("let {name}: index = {text};"));
        p.names.expressions.insert(e.clone(), name);
    }
    p.commands(0, plan.commands.len(), 1, false)?;
    p.line(1, "");
    for id in 0..plan.value_count as i64 {
        let d = p.declarations[id as usize];
        let flags = if matches!(d.op, Op::ConstantOutput | Op::PackedConstantOutput) {
            2
        } else {
            d.args[4].int()
        };
        if flags & 2 != 0 {
            p.line(1, &format!("output {};", p.names.tensor(id)?));
        }
    }
    let needs_order = p.binding_order != (0..plan.value_count as i64).collect::<Vec<_>>();
    if needs_order || !p.metadata.is_empty() {
        p.line(1, "");
        p.line(1, "metadata {");
        if needs_order {
            p.line(2, "order [");
            let mut row = String::new();
            for name in &p.names.tensors.clone() {
                if row.len() + name.len() > 120 {
                    p.line(3, &row);
                    row.clear();
                }
                row.push_str(name);
                row.push_str(", ");
            }
            if !row.is_empty() {
                p.line(3, row.trim_end());
            }
            p.line(2, "];");
        }
        for line in std::mem::take(&mut p.metadata) {
            p.line(2, &line);
        }
        p.line(1, "}");
    }
    p.line(0, "}");
    Ok(p.body)
}
