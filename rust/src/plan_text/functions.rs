// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
//! Typed source functions with explicit resource owners. Expansion ends before native plan validation;
//! execution still prepares one graph. Source formatting retains definitions.
use super::parser::*;
use super::{diagnostic, Span};
use crate::plan::{Arg, Op, RawCommand, MAX_COMMANDS, MAX_FILE, MAX_VALUES};
use crate::Result;
use std::collections::{HashMap, HashSet};
use std::fmt::Write;

type Names = HashMap<String, String>;
fn quote(s: &str) -> String { serde_json::to_string(s).unwrap() }
fn name(n: &str, names: &Names) -> String { names.get(n).cloned().unwrap_or_else(|| n.into()) }
pub(super) fn value(v: &Value<'_>, names: &Names) -> String {
    match &v.kind {
        ValueKind::Name(n) | ValueKind::Tensor(n) | ValueKind::Symbol(n) => name(n, names),
        ValueKind::Number(n) => (*n).into(),
        ValueKind::String(s) => quote(s),
        ValueKind::Unknown => "?".into(),
        ValueKind::List(xs) => format!("[{}]", xs.iter().map(|x| value(x, names)).collect::<Vec<_>>().join(", ")),
        ValueKind::Call(c) => call(c, names, ""),
        ValueKind::Unary(op, x) => format!("{}{}", *op as char, value(x, names)),
        ValueKind::Binary(op, a, b) => format!("({} {op} {})", value(a, names), value(b, names)),
    }
}
pub(super) fn call(c: &Call<'_>, names: &Names, path: &str) -> String {
    let args = c.arguments.iter().enumerate().map(|(i, a)| {
        let mut v = value(&a.value, names);
        if matches!(c.name, "operation" | "BeginOperation" | "begin_operation" | "EndOperation" | "end_operation")
            && (matches!(a.name, Some("waits" | "defines")) || a.name.is_none() && i == 0) {
            if let (Some(prefix), ValueKind::List(xs)) = (names.get("@completion"), &a.value.kind) {
                v = format!("[{}]", xs.iter().map(|x| match &x.kind {
                    ValueKind::String(s) => quote(&format!("{prefix}{s}")),
                    _ => value(x, names),
                }).collect::<Vec<_>>().join(", "));
            }
        }
        if !path.is_empty() && matches!(c.name, "profile" | "begin_profile_operation" | "BeginProfileOperation")
            && (a.name == Some("name") || a.name.is_none() && i == 0) {
            if let ValueKind::String(s) = &a.value.kind { v = quote(&format!("{path}/{s}")); }
        }
        match a.name { Some(n) => format!("{n}={v}"), None => v }
    }).collect::<Vec<_>>().join(", ");
    format!("{}({args})", c.name)
}
pub(super) fn ty(t: &Type<'_>, names: &Names) -> String {
    if t.name == "index" || t.literal { return t.name.into(); }
    let inner = format!("{}[{}]", t.name, t.dims.iter().map(|d| value(d, names)).collect::<Vec<_>>().join(", "));
    if t.owner { format!("owner<{inner}>") } else if t.storage { format!("storage<{inner}>") } else { inner }
}
pub(super) fn binding(b: &Binding<'_>, names: &Names) -> String {
    let text = match &b.ty { Some(t) => format!("{}: {}", name(b.name, names), ty(t, names)), None => name(b.name, names) };
    match &b.default { Some(v) => format!("{text} = {}", value(v, names)), None => text }
}
pub(super) fn header(doc: &Document<'_>) -> String {
    format!("ynn {} resource_contract={} completion_contract={} profiling={} {{\n", doc.version, doc.resource, doc.completion, if doc.auto_profile { "auto" } else { "explicit" })
}
pub(super) fn render(s: &Statement<'_>, names: &Names, path: &str) -> String {
    let mut out = String::new();
    for a in &s.attributes { write!(out, "@{} ", call(a, names, path)).unwrap(); }
    match &s.kind {
        StatementKind::Declaration { role, binding: b, data } => {
            write!(out, "{role} {}", binding(b, names)).unwrap();
            if let Some(d) = data { write!(out, " = {}", value(d, names)).unwrap(); }
        }
        StatementKind::Let { bindings, value: v } => {
            write!(out, "let ({}) = {}", bindings.iter().map(|b| binding(b, names)).collect::<Vec<_>>().join(", "), value(v, names)).unwrap();
        }
        StatementKind::Dim { name: n, source, lower, upper } => {
            write!(out, "dim {} = {} in {}..={}", name(n, names), value(source, names), value(lower, names), value(upper, names)).unwrap();
        }
        StatementKind::Require { lhs, rhs, relation } => {
            write!(out, "require {} {} {}", value(lhs, names), match *relation { "le" => "<=", "ge" => ">=", _ => "==" }, value(rhs, names)).unwrap();
        }
        StatementKind::Output(n) => { write!(out, "output {}", name(n, names)).unwrap(); }
        StatementKind::Shape { name: n, value: v, input } => {
            write!(out, "{} {} = {}", if *input { "input_shape" } else { "shape" }, name(n, names), value(v, names)).unwrap();
        }
        StatementKind::Call(c) => out.push_str(&call(c, names, path)),
        StatementKind::Block { call: c, body } => {
            writeln!(out, "{} {{", call(c, names, path)).unwrap();
            for child in body { out.push_str(&render(child, names, path)); }
            out.push_str("}\n"); return out;
        }
        StatementKind::Invoke { call: c, outputs } => {
            write!(out, "invoke {} -> ({})", call(c, names, path), outputs.iter().map(|n| name(n, names)).collect::<Vec<_>>().join(", ")).unwrap();
        }
        StatementKind::Return(ns) => { write!(out, "return({})", ns.iter().map(|n| name(n, names)).collect::<Vec<_>>().join(", ")).unwrap(); }
    }
    out.push_str(";\n"); out
}
fn declarations<'a, 'b>(ss: &'b [Statement<'a>], out: &mut Vec<&'b Binding<'a>>) {
    for s in ss { match &s.kind {
        StatementKind::Declaration { binding, .. } => out.push(binding),
        StatementKind::Let { bindings, .. } => out.extend(bindings),
        StatementKind::Block { body, .. } => declarations(body, out),
        _ => (),
    } }
}
pub(super) fn metadata(doc: &Document<'_>, extra_order: &[String], extra: &[String]) -> String {
    let mut out = "metadata {\n".to_string();
    if doc.order_set {
        writeln!(out, "order [{}];", doc.order.iter().map(|n| n.to_string()).chain(extra_order.iter().cloned()).collect::<Vec<_>>().join(", ")).unwrap();
    }
    for m in &doc.metadata { writeln!(out, "{} {} = {};", m.kind, m.target, value(&m.value, &Names::new())).unwrap(); }
    for m in extra { out.push_str(m); }
    out.push_str("}\n}\n"); out
}
// Use the same typed-let/profile vocabulary as flat plans. Preserve the tensor
// allocation order explicitly when moving a declaration to its producer.
fn compact<'a>(source: &'a str, doc: &Document<'a>) -> (Vec<Statement<'a>>, Vec<&'a str>) {
    let mut bindings = Vec::new(); declarations(&doc.statements, &mut bindings);
    let order = if doc.order_set { doc.order.clone() } else {
        bindings.iter().filter(|b| b.ty.as_ref().is_none_or(|t| t.name != "index")).map(|b| b.name).collect()
    };
    let declarations: HashMap<_, _> = doc.statements.iter().filter_map(|s| match &s.kind {
        StatementKind::Declaration { role: "value", binding, data: None } if s.attributes.is_empty() => Some((binding.name, binding)),
        _ => None,
    }).collect();
    let mut resolver = super::resolve::Resolver::new(source);
    let runtime_names: Vec<String> = order.iter().map(|n| doc.metadata.iter().find_map(|m| {
        if m.kind == "name" && m.target == *n { if let ValueKind::String(s) = &m.value.kind { return Some(s.clone()); } } None
    }).unwrap_or_else(|| n.to_string())).collect();
    for (i,n) in order.iter().enumerate() { resolver.tensors.insert((*n).into(), i as i64); }
    // Only tensor identities and enum options affect default profile metadata.
    // Index operands can be represented by distinct dummy symbols here.
    for s in &doc.statements {
        let n = match &s.kind {
            StatementKind::Dim { name, .. } => Some(*name),
            StatementKind::Let { bindings, .. } if bindings.len() == 1 && bindings[0].ty.as_ref().is_some_and(|t| t.name == "index") => Some(bindings[0].name),
            _ => None,
        };
        if let Some(n) = n { resolver.symbols.insert(n.into(), resolver.symbols.len() as u32); }
    }
    let mut replacements = HashMap::new();
    let mut moved = HashSet::new();
    let mut i = 0;
    while i + 2 < doc.statements.len() {
        let ss = &doc.statements[i..i+3];
        if let [Statement { kind: StatementKind::Call(begin), .. }, Statement { kind: StatementKind::Call(compute), .. }, Statement { kind: StatementKind::Call(end), .. }] = ss {
            if matches!(begin.name, "BeginProfileOperation" | "begin_profile_operation") && matches!(end.name, "EndProfileOperation" | "end_profile_operation") {
                if let Some((op, _)) = super::schema::lookup(compute.name) {
                    let outputs: Vec<_> = compute.arguments.iter().filter(|a| a.name.is_some_and(|n| super::schema::output(op,n))).collect();
                    let bs: Option<Vec<_>> = outputs.iter().map(|a| match a.value.kind {
                        ValueKind::Name(n) | ValueKind::Tensor(n) => declarations.get(n).map(|b| (*b).clone()), _ => None,
                    }).collect();
                    if let Some(bs) = bs.filter(|bs| !bs.is_empty()) {
                        if bs.iter().all(|b| !moved.contains(b.name)) {
                            moved.extend(bs.iter().map(|b| b.name));
                            let mut c = compute.clone();
                            c.arguments.retain(|a| !a.name.is_some_and(|n| super::schema::output(op,n)));
                            let mut profile = begin.clone(); profile.name = "profile";
                            // Avoid repeating the primitive's inferred input,
                            // output and kind lists on every authored operation.
                            let mut args = vec![None; op.fields().len()];
                            if let Some((_, implicit)) = super::schema::lookup(compute.name) { if let Some(a) = implicit { args[0] = Some(a); } }
                            for a in &compute.arguments {
                                if let Some(i) = a.name.and_then(|n| op.fields().iter().position(|f| *f == n)) {
                                    // These AST nodes already passed parse/validation.
                                    // Dummy spans keep optional formatting failures local.
                                    let mut v = a.value.clone(); v.span = Span { start: 0, end: 0 };
                                    args[i] = resolver.arg(op.signature()[i], op.fields()[i], &v).ok();
                                }
                            }
                            if let Some(args) = args.into_iter().collect::<Option<Vec<Arg>>>() {
                                let defaults = super::schema::profile(&RawCommand { op, args }, &runtime_names);
                                profile.arguments.retain(|a| {
                                    let Some(i) = a.name.and_then(|n| Op::BeginProfileOperation.fields().iter().position(|f| *f == n)) else { return true; };
                                    let mut v = a.value.clone(); v.span = Span { start: 0, end: 0 };
                                    resolver.arg(Op::BeginProfileOperation.signature()[i], Op::BeginProfileOperation.fields()[i], &v).ok().as_ref() != Some(&defaults[i])
                                });
                            }
                            replacements.insert(i, Statement { span: ss[0].span, attributes: vec![profile], kind: StatementKind::Let {
                                bindings: bs, value: Value { span: compute.span, depth: 1, kind: ValueKind::Call(c) },
                            }});
                            i += 3; continue;
                        }
                    }
                }
            }
        }
        i += 1;
    }
    let mut out = Vec::new(); i = 0;
    while i < doc.statements.len() {
        if let Some(s) = replacements.remove(&i) { out.push(s); i += 3; continue; }
        let s = &doc.statements[i];
        if !matches!(&s.kind, StatementKind::Declaration { binding, .. } if moved.contains(binding.name)) { out.push(s.clone()); }
        i += 1;
    }
    (out, order)
}
pub(super) fn format(source: &str, doc: &Document<'_>) -> Result<String> {
    let mut out = header(doc);
    for f in &doc.functions {
        writeln!(out, "  fn {}({}) -> ({}) {{", f.name,
            f.parameters.iter().map(|b| binding(b, &Names::new())).collect::<Vec<_>>().join(", "),
            f.results.iter().map(|b| binding(b, &Names::new())).collect::<Vec<_>>().join(", ")).unwrap();
        for s in &f.statements { for line in render(s, &Names::new(), "").lines() { writeln!(out, "    {line}").unwrap(); } }
        out.push_str("  }\n\n");
    }
    let (statements, order) = compact(source, doc);
    // Runtime names remain in metadata; readable aliases carry the code.
    let mut names = Names::new();
    let mut used: HashSet<String> = order.iter().map(|n| n.to_string()).collect();
    used.extend(["none".to_string(), "true".into(), "false".into()]);
    for m in &doc.metadata {
        if m.kind != "name" { continue; }
        if let ValueKind::String(s) = &m.value.kind {
            let mut alias: String = s.chars().take(72).map(|c| if c.is_ascii_alphanumeric() || c == '_' { c } else { '_' }).collect();
            if alias.is_empty() || alias.as_bytes()[0].is_ascii_digit() { alias.insert_str(0, "t_"); }
            while used.contains(&alias) && alias != m.target { alias.push('_'); }
            used.insert(alias.clone());
            names.insert(m.target.into(), alias);
        }
    }
    for s in &statements { for line in render(s, &names, "").lines() { writeln!(out, "  {line}").unwrap(); } }
    out.push_str("metadata {\n");
    writeln!(out, "order [{}];", order.iter().map(|n| name(n, &names)).collect::<Vec<_>>().join(", ")).unwrap();
    for m in &doc.metadata { writeln!(out, "{} {} = {};", m.kind, name(m.target, &names), value(&m.value, &names)).unwrap(); }
    out.push_str("}\n}\n");
    Ok(out)
}
#[derive(Clone)]
struct TensorType { dtype: String, dims: Vec<String> }
#[derive(Clone)]
struct Owner {
    root: String,
    generation: usize,
    axis: String,
    extent: String,
    encoding: String,
}
struct Expander<'a, 'b> {
    source: &'a str,
    functions: HashMap<&'a str, &'b Function<'a>>,
    used: HashSet<String>,
    types: HashMap<String, TensorType>,
    resources: HashSet<String>,
    resource_views: HashSet<String>,
    stack: Vec<&'a str>,
    serial: usize,
    statements: usize,
    locals: Vec<String>,
    metadata: Vec<String>,
    out: String,
    operation_depth: usize,
    profile_depth: usize,
    suppress_profiles: bool,
    owners: HashMap<String, Owner>,
    latest: HashMap<String, usize>,
    validation_owners: HashSet<String>,
    resource_specs: HashMap<String, Call<'a>>,
}
impl<'a, 'b> Expander<'a, 'b> {
    fn new(source: &'a str, doc: &'b Document<'a>) -> Result<Self> {
        let mut e = Self { source, functions: HashMap::new(), used: HashSet::new(), types: HashMap::new(), resources: HashSet::new(), resource_views: HashSet::new(), stack: Vec::new(), serial: 0, statements: 0, locals: Vec::new(), metadata: Vec::new(), out: header(doc), operation_depth: 0, profile_depth: 0, suppress_profiles: false, owners: HashMap::new(), latest: HashMap::new(), validation_owners: HashSet::new(), resource_specs: HashMap::new() };
        for f in &doc.functions {
            if e.functions.insert(f.name, f).is_some() {
                return Err(diagnostic(source, f.span, "Duplicate function name"));
            }
        }
        e.register(&doc.statements, &Names::new(), false, "")?;
        fn resources(ss: &[Statement<'_>], out: &mut HashSet<String>, views: &mut HashSet<String>) {
            for s in ss {
                match &s.kind {
                    StatementKind::Declaration { role: "state", binding, .. } => { out.insert(binding.name.into()); }
                    StatementKind::Call(c) => {
                        if let Some((op, _)) = super::schema::lookup(c.name) {
                            let field = match op { Op::Resource => "owner", Op::View | Op::Append => "output", _ => continue };
                            for (i, a) in c.arguments.iter().enumerate() {
                                if a.name.or_else(|| op.fields().get(i).copied()) == Some(field) { if let ValueKind::Name(n) | ValueKind::Tensor(n) = a.value.kind { out.insert(n.into()); if op == Op::View { views.insert(n.into()); } } }
                            }
                        }
                    }
                    StatementKind::Let { bindings, value } => {
                        if let ValueKind::Call(c) = &value.kind {
                            if matches!(super::schema::lookup(c.name), Some((Op::View | Op::Append, _))) { out.extend(bindings.iter().map(|b| b.name.into())); if matches!(super::schema::lookup(c.name), Some((Op::View, _))) { views.extend(bindings.iter().map(|b| b.name.into())); } }
                        }
                    }
                    StatementKind::Block { body, .. } => resources(body, out, views),
                    _ => (),
                }
            }
        }
        resources(&doc.statements, &mut e.resources, &mut e.resource_views);
        fn state_specs<'s>(ss: &[Statement<'s>], specs: &mut HashMap<String, Call<'s>>) {
            for s in ss {
                match &s.kind {
                    StatementKind::Declaration { role: "state", binding, .. } => {
                        if let Some(a) = s.attributes.iter().find(|a| a.name == "resource") {
                            specs.insert(binding.name.into(), a.clone());
                        }
                    }
                    StatementKind::Block { body, .. } => state_specs(body, specs),
                    _ => (),
                }
            }
        }
        state_specs(&doc.statements, &mut e.resource_specs);
        for m in &doc.metadata {
            if m.kind == "resource" {
                if let ValueKind::Call(c) = &m.value.kind { e.resource_specs.insert(m.target.into(), c.clone()); }
            }
        }
        Ok(e)
    }
    fn tensor(&self, t: &Type<'_>, names: &Names) -> TensorType {
        TensorType { dtype: t.name.into(), dims: t.dims.iter().map(|d| value(d, names)).collect() }
    }
    fn register(&mut self, ss: &[Statement<'a>], names: &Names, local: bool, path: &str) -> Result<()> {
        let mut bs = Vec::new(); declarations(ss, &mut bs);
        for b in bs {
            let n = name(b.name, names);
            if !self.used.insert(n.clone()) { return Err(diagnostic(self.source, b.span, "Duplicate function/local binding")); }
            if let Some(t) = &b.ty {
                if t.name == "index" { continue; }
                self.types.insert(n.clone(), self.tensor(t, names));
            }
            if local {
                self.locals.push(n.clone());
                // Scopes are human labels and may repeat. Native tensor names
                // still need a unique identity for each expanded invocation.
                self.metadata.push(format!("name {n} = {};\n", quote(&format!("{path}/{}#{n}", b.name))));
            }
            if self.types.len() > MAX_VALUES { return Err(diagnostic(self.source, b.span, "Function tensor expansion limit")); }
        }
        Ok(())
    }
    fn compatible(&self, b: &Binding<'_>, actual: &str, names: &Names, read_only: bool) -> Result<()> {
        let t = b.ty.as_ref().unwrap();
        if t.owner {
            if read_only && !self.owners.contains_key(actual) && !self.validation_owners.contains(actual) {
                return Err(diagnostic(self.source, b.span, "Function owner parameter requires a resource owner"));
            }
            if read_only && self.resource_views.contains(actual) {
                return Err(diagnostic(self.source, b.span, "Function owner parameter cannot borrow a view"));
            }
        } else if self.resources.contains(actual) && !(read_only && self.resource_views.contains(actual)) {
            return Err(diagnostic(self.source, b.span, "Function tensor must not carry a resource"));
        }
        if read_only {
            if let Some(owner) = self.owners.get(actual) {
                if self.latest.get(&owner.root) != Some(&owner.generation) {
                    return Err(diagnostic(self.source, b.span, "Function argument is a stale resource generation"));
                }
            }
        }
        let a = self.types.get(actual).ok_or_else(|| diagnostic(self.source, b.span, format!("Function tensor {actual} needs an explicit type")))?;
        let expected = self.tensor(t, names);
        if a.dtype != expected.dtype || a.dims.len() != expected.dims.len() || a.dims.iter().zip(&expected.dims).any(|(x,y)| {
            // Zero is the native plan's unspecified storage extent. Logical
            // extents are checked by the body's shape/require statements.
            match (x.parse::<i64>(), y.parse::<i64>()) { (Ok(x), Ok(y)) => x > 0 && y > 0 && x != y, _ => false }
        }) {
            return Err(diagnostic(self.source, b.span, format!("Function tensor type mismatch for {}", b.name)));
        }
        Ok(())
    }
    // Function owners bind existing storage. A Resource command in a definition
    // checks that binding; only the outer graph declares the native resource.
    fn state_command(&mut self, c: &Call<'_>, bindings: &[Binding<'_>], names: &Names) -> Result<bool> {
        let Some((op, _)) = super::schema::lookup(c.name) else { return Ok(false); };
        if !matches!(op, Op::Resource | Op::Append | Op::View) { return Ok(false); }
        let fields = op.fields();
        let outputs: Vec<_> = fields.iter().filter(|n| super::schema::output(op, n)).collect();
        let positional: Vec<_> = fields.iter().filter(|n| bindings.is_empty() || !super::schema::output(op, n)).collect();
        let field = |n: &str| -> Result<String> {
            if let Some(i) = outputs.iter().position(|x| **x == n) {
                if let Some(b) = bindings.get(i) { return Ok(name(b.name, names)); }
            }
            for (i, a) in c.arguments.iter().enumerate() {
                if a.name.or_else(|| positional.get(i).map(|n| **n)) == Some(n) { return Ok(value(&a.value, names)); }
            }
            Err(diagnostic(self.source, c.span, format!("Missing resource field {n}")))
        };
        let input = field(if op == Op::View { "input" } else { "owner" })?;
        if op == Op::Resource {
            let axis = field("axis")?;
            let extent = field("entry_extent")?;
            let encoding = field("encoding")?;
            if let Some(owner) = self.owners.get(&input).cloned() {
                if self.stack.is_empty() || owner.axis != axis || owner.encoding != encoding {
                    return Err(diagnostic(self.source, c.span, "Resource binding contract mismatch"));
                }
                self.push(&format!("require {} == {};\n", owner.extent, extent), c.span)?;
                return Ok(true);
            }
            if !self.stack.is_empty() && !self.validation_owners.remove(&input) {
                return Err(diagnostic(self.source, c.span, "Function declares a hidden resource"));
            }
            self.owners.insert(input.clone(), Owner { root: input.clone(), generation: 0, axis, extent, encoding });
            self.latest.insert(input.clone(), 0);
            self.resources.insert(input);
            return Ok(false);
        }
        let Some(mut owner) = self.owners.get(&input).cloned() else {
            return Err(diagnostic(self.source, c.span, "Append/view requires a declared resource"));
        };
        if self.latest.get(&owner.root) != Some(&owner.generation) {
            return Err(diagnostic(self.source, c.span, "Stale resource generation"));
        }
        if owner.axis != field("axis")? { return Err(diagnostic(self.source, c.span, "Resource axis mismatch")); }
        let output = field("output")?;
        if op == Op::Append {
            if self.resource_views.contains(&input) { return Err(diagnostic(self.source, c.span, "Cannot append through a resource view")); }
            owner.generation += 1;
            owner.extent = format!("add({}, {})", field("position")?, field("rows")?);
            self.latest.insert(owner.root.clone(), owner.generation);
        } else {
            self.resource_views.insert(output.clone());
        }
        self.owners.insert(output.clone(), owner);
        self.resources.insert(output);
        Ok(false)
    }
    fn push(&mut self, text: &str, span: Span) -> Result<()> {
        self.statements += 1;
        if self.statements > MAX_COMMANDS || self.out.len().saturating_add(text.len()) as u64 > MAX_FILE {
            return Err(diagnostic(self.source, span, "Function expansion budget exceeded"));
        }
        self.out.push_str(text); Ok(())
    }
    fn statements(&mut self, ss: &[Statement<'a>], names: &Names, path: &str) -> Result<()> {
        for s in ss {
            match &s.kind {
                StatementKind::Invoke { call: c, outputs } => self.invoke(s, c, outputs, names, path)
                    .map_err(|e| diagnostic(self.source, s.span, format!("Call to {}: {e}", c.name)))?,
                StatementKind::Return(_) => return Err(diagnostic(self.source, s.span, "Unexpected return")),
                StatementKind::Block { call: c, body } => {
                    if !s.attributes.is_empty() { return Err(diagnostic(self.source, s.span, "Block annotations unsupported")); }
                    if self.suppress_profiles && c.name == "profile" { self.statements(body, names, path)?; continue; }
                    self.operation_depth += usize::from(c.name == "operation");
                    self.profile_depth += usize::from(c.name == "profile");
                    self.push(&format!("{} {{\n", call(c, names, path)), s.span)?;
                    self.statements(body, names, path)?;
                    self.push("}\n", s.span)?;
                    self.operation_depth -= usize::from(c.name == "operation");
                    self.profile_depth -= usize::from(c.name == "profile");
                }
                StatementKind::Call(c) => {
                    let op = super::schema::lookup(c.name).map(|(op, _)| op);
                    if self.suppress_profiles && matches!(op, Some(Op::BeginProfileOperation | Op::EndProfileOperation)) { continue; }
                    if self.state_command(c, &[], names)? { continue; }
                    match op {
                        Some(Op::BeginOperation) => self.operation_depth += 1,
                        Some(Op::EndOperation) => self.operation_depth = self.operation_depth.saturating_sub(1),
                        Some(Op::BeginProfileOperation) => self.profile_depth += 1,
                        Some(Op::EndProfileOperation) => self.profile_depth = self.profile_depth.saturating_sub(1),
                        _ => (),
                    }
                    self.push(&render(s, names, path), s.span)?;
                }
                StatementKind::Let { bindings, value: v } => {
                    if let ValueKind::Call(c) = &v.kind { self.state_command(c, bindings, names)?; }
                    let mut unprofiled = s.clone();
                    if self.suppress_profiles { unprofiled.attributes.retain(|a| a.name != "profile"); }
                    self.push(&render(&unprofiled, names, path), s.span)?;
                }
                StatementKind::Require { lhs, rhs, relation: "eq" } => {
                    if let ValueKind::Call(c) = &lhs.kind {
                        if c.name == "committed" && c.arguments.len() == 1 {
                            let owner = value(&c.arguments[0].value, names);
                            let spec = self.resource_specs.get(&owner).ok_or_else(|| diagnostic(self.source, c.span, "Committed owner lacks resource metadata"))?;
                            let resolver = super::resolve::Resolver::new(self.source);
                            let fields = resolver.fields(spec, &["name", "axis", "encoding"])?;
                            if self.owners.contains_key(&owner) { return Err(diagnostic(self.source, c.span, "Resource already declared")); }
                            self.owners.insert(owner.clone(), Owner { root: owner.clone(), generation: 0, axis: value(fields[1], names), extent: value(rhs, names), encoding: value(fields[2], names) });
                            self.latest.insert(owner, 0);
                        }
                    }
                    self.push(&render(s, names, path), s.span)?;
                }
                _ => self.push(&render(s, names, path), s.span)?,
            }
        }
        Ok(())
    }
    fn invoke(&mut self, s: &Statement<'a>, c: &Call<'a>, outputs: &[&str], parent: &Names, path: &str) -> Result<()> {
        let f = *self.functions.get(c.name).ok_or_else(|| diagnostic(self.source, c.span, format!("Unknown function {}", c.name)))?;
        if self.stack.len() >= 64 || self.stack.contains(&c.name) { return Err(diagnostic(self.source, c.span, format!("Recursive/deep call to {}", c.name))); }
        if c.arguments.len() > f.parameters.len() || outputs.len() != f.results.len() || c.arguments.iter().any(|a| a.name.is_some()) {
            return Err(diagnostic(self.source, c.span, format!("Function arity mismatch: {}", c.name)));
        }
        let mut arguments = c.arguments.clone();
        for b in &f.parameters[arguments.len()..] {
            let default = b.default.clone().ok_or_else(|| diagnostic(self.source, c.span, "Missing function argument"))?;
            arguments.push(Argument { name: None, span: default.span, value: default });
        }
        self.serial += 1;
        let prefix = format!("__fn{}_", self.serial);
        let mut scope = format!("{}/{}{}", path, f.name, self.serial).trim_start_matches('/').to_string();
        if !s.attributes.is_empty() {
            if s.attributes.len() != 1 || s.attributes[0].name != "scope" || s.attributes[0].arguments.len() != 1 { return Err(diagnostic(self.source, s.span, "Invoke accepts only @scope(name=...)")); }
            let a = &s.attributes[0].arguments[0];
            if a.name != Some("name") { return Err(diagnostic(self.source, a.span, "Scope needs name")); }
            if let ValueKind::String(p) = &a.value.kind { scope = if path.is_empty() { p.clone() } else { format!("{path}/{p}") }; }
            else { return Err(diagnostic(self.source, a.span, "Scope must be a string")); }
        }
        let mut names = Names::new();
        names.insert("@completion".into(), prefix.clone());
        for (b, a) in f.parameters.iter().zip(&arguments) { names.insert(b.name.into(), value(&a.value, parent)); }
        for (b, n) in f.results.iter().zip(outputs) { names.insert(b.name.into(), name(n, parent)); }
        let mut incoming_owners = HashMap::new();
        for (b, a) in f.parameters.iter().zip(&arguments) {
            if b.ty.as_ref().unwrap().literal {
                // Reparse after substituting parent template parameters. An
                // empty resolver rejects tensor/index references even for an
                // unused argument; templates only accept closed literals.
                let stub = format!("ynn 1 resource_contract=1 completion_contract=1 {{ check(value={}); }}", names[b.name]);
                let doc = super::parser::document(&stub)?;
                let StatementKind::Call(check) = &doc.statements[0].kind else { unreachable!() };
                validate_literal(&stub, b.ty.as_ref().unwrap().name, &check.arguments[0].value)?;
                continue;
            }
            if b.ty.as_ref().unwrap().name != "index" {
                if !matches!(a.value.kind, ValueKind::Name(_) | ValueKind::Tensor(_)) { return Err(diagnostic(self.source, a.span, "Tensor argument must be a tensor name")); }
                self.compatible(b, &names[b.name], &names, true)?;
                if b.ty.as_ref().unwrap().owner {
                    let actual = &names[b.name];
                    let (root, generation) = self.owners.get(actual).map(|o| (o.root.clone(), o.generation)).unwrap_or((actual.clone(), 0));
                    if incoming_owners.insert(root, generation).is_some() {
                        return Err(diagnostic(self.source, a.span, "Function owner arguments alias"));
                    }
                }
            } else {
                let mut alias = format!("{prefix}index_{}", b.name);
                while self.used.contains(&alias) { alias.push('_'); }
                self.used.insert(alias.clone());
                self.push(&format!("let {alias}: index = {};\n", names[b.name]), c.span)?;
                names.insert(b.name.into(), alias);
            }
        }
        for b in &f.results { self.compatible(b, &names[b.name], &names, false)?; }
        let mut bs = Vec::new(); declarations(&f.statements, &mut bs);
        let mut local_names = HashSet::new();
        for b in bs {
            if names.contains_key(b.name) { return Err(diagnostic(self.source, b.span, "Function local shadows parameter/result")); }
            let mut n = format!("{prefix}{}", b.name);
            while self.used.contains(&n) || local_names.contains(&n) { n.push('_'); }
            local_names.insert(n.clone());
            names.insert(b.name.into(), n);
        }
        self.register(&f.statements, &names, true, &scope)?;
        self.stack.push(c.name);
        let previous_suppression = self.suppress_profiles;
        self.suppress_profiles |= self.operation_depth > 0 || self.profile_depth > 0;
        let body = &f.statements[..f.statements.len()-1];
        let result = self.statements(body, &names, &scope).map_err(|e| diagnostic(self.source, c.span, format!("Calling {} (definition at byte {}): {e}", f.name, f.span.start)));
        self.stack.pop();
        self.suppress_profiles = previous_suppression;
        result?;
        let mut returned = HashSet::new();
        for b in &f.results {
            let actual = &names[b.name];
            if b.ty.as_ref().unwrap().owner {
                let o = self.owners.get(actual).ok_or_else(|| diagnostic(self.source, b.span, "Function owner result is not an advanced owner"))?;
                if self.resource_views.contains(actual) || !incoming_owners.get(&o.root).is_some_and(|g| o.generation > *g)
                    || self.latest.get(&o.root) != Some(&o.generation) || !returned.insert(o.root.clone()) {
                    return Err(diagnostic(self.source, b.span, "Function needs one advanced successor per owner"));
                }
            } else if self.resources.contains(actual) {
                return Err(diagnostic(self.source, b.span, "Resource view cannot escape a function"));
            }
        }
        if returned.len() != incoming_owners.len() {
            return Err(diagnostic(self.source, c.span, "Function hides a resource successor"));
        }
        Ok(())
    }
}

fn validate_literal(source: &str, kind: &str, v: &Value<'_>) -> Result<()> {
    let arg = super::resolve::Resolver::new(source).arg(kind, "literal", v)?;
    if matches!((&arg, kind), (Arg::Int(n), "size") if *n < 0)
        || matches!((&arg, kind), (Arg::Ints(ns), "sizes") if ns.iter().any(|n| *n < 0)) {
        return Err(diagnostic(source, v.span, "Unsigned literal is negative"));
    }
    Ok(())
}
fn validate_signature(source: &str, f: &Function<'_>) -> Result<()> {
    let mut seen = HashSet::new();
    if f.results.is_empty() { return Err(diagnostic(source, f.span, "Function needs results")); }
    for b in f.parameters.iter().chain(&f.results) {
        let t = b.ty.as_ref().unwrap();
        if !seen.insert(b.name) { return Err(diagnostic(source, b.span, "Duplicate formal binding")); }
        if t.literal != b.default.is_some() { return Err(diagnostic(source, b.span, "Literal parameters need typed defaults; tensor/index parameters cannot have defaults")); }
        if let Some(v) = &b.default { validate_literal(source, t.name, v)?; }
        if t.name != "index" && !t.literal && !t.storage { return Err(diagnostic(source, b.span, "Function tensors need storage types; logical constraints belong in require/shape")); }
    }
    if f.results.iter().any(|b| b.ty.as_ref().unwrap().name == "index" || b.ty.as_ref().unwrap().literal) { return Err(diagnostic(source, f.span, "Function results must be tensors")); }
    if !matches!(f.statements.last().map(|s| &s.kind), Some(StatementKind::Return(ns)) if *ns == f.results.iter().map(|b| b.name).collect::<Vec<_>>()) {
        return Err(diagnostic(source, f.span, "Function must end with return of its named results"));
    }
    fn closed(source: &str, ss: &[Statement<'_>]) -> Result<()> {
        for s in ss {
            match &s.kind {
                StatementKind::Declaration { role: "input" | "state", .. } |
                StatementKind::Dim { .. } | StatementKind::Output(_) | StatementKind::Return(_) =>
                    return Err(diagnostic(source, s.span, "Function has a hidden input, state, or result")),
                StatementKind::Block { body, .. } => closed(source, body)?,
                _ => (),
            }
        }
        Ok(())
    }
    closed(source, &f.statements[..f.statements.len()-1])?;
    Ok(())
}
pub(super) fn expand(source: &str, doc: &Document<'_>) -> Result<String> {
    for f in &doc.functions { validate_signature(source, f)?; }
    // Validate each closed body, including unused definitions, in an isolated
    // namespace. A reference to a caller's tensor cannot become a capture.
    let mut validation_work = 0usize;
    for f in &doc.functions {
        let mut stub = header(doc);
        for b in f.parameters.iter().chain(&f.results) {
            let t = b.ty.as_ref().unwrap();
            if t.literal { continue; }
            if t.name == "index" { writeln!(stub, "dim {} = parameter({}) in 0..=2147483647;", b.name, quote(b.name)).unwrap(); }
            else { writeln!(stub, "{} {};", if f.parameters.iter().any(|p| p.name == b.name) { "input" } else { "value" }, binding(b, &Names::new())).unwrap(); }
        }
        for b in &f.results { writeln!(stub, "output {};", b.name).unwrap(); }
        writeln!(stub, "invoke {}({}) -> ({});", f.name, f.parameters.iter().map(|b| b.default.as_ref().map_or_else(|| b.name.to_string(), |v| value(v, &Names::new()))).collect::<Vec<_>>().join(", "), f.results.iter().map(|b| b.name).collect::<Vec<_>>().join(", ")).unwrap();
        stub.push_str("}\n");
        let stubdoc = super::parser::document(&stub)?;
        let mut e = Expander::new(source, doc)?;
        // The stub's AST borrows a different string, but all definitions are
        // still resolved from the original document during this invocation.
        e.types.clear(); e.used.clear(); e.resources.clear(); e.resource_views.clear(); e.owners.clear(); e.latest.clear(); e.out = header(doc);
        e.validation_owners = f.parameters.iter().filter(|b| b.ty.as_ref().unwrap().owner).map(|b| b.name.into()).collect();
        e.register(&stubdoc.statements, &Names::new(), false, "")?;
        e.statements(&stubdoc.statements, &Names::new(), "")?;
        validation_work = validation_work.saturating_add(e.statements);
        if validation_work > MAX_COMMANDS { return Err(diagnostic(source, f.span, "Function definition validation budget exceeded")); }
        e.out.push_str("}\n");
        let plan = super::compile::compile(&e.out, super::parser::document(&e.out)?)
            .map_err(|err| diagnostic(source, f.span, format!("Invalid closed function {}: {err}", f.name)))?;
        for c in &plan.commands {
            if matches!(c.op, Op::BindScalarParameter) ||
                (matches!(c.op, Op::Append | Op::View | Op::Resource) && !f.parameters.iter().any(|b| b.ty.as_ref().unwrap().owner)) {
                return Err(diagnostic(source, f.span, "Function must be pure and resource-free"));
            }
        }
    }
    let mut e = Expander::new(source, doc)?;
    e.statements(&doc.statements, &Names::new(), "")?;
    let tail = metadata(doc, &e.locals, &e.metadata);
    e.push(&tail, Span { start: 0, end: 0 })?;
    Ok(e.out)
}
pub(super) fn inspect(doc: &Document<'_>) -> serde_json::Value {
    fn calls(ss: &[Statement<'_>], out: &mut Vec<String>) {
        for s in ss { match &s.kind {
            StatementKind::Invoke { call, .. } => out.push(call.name.into()),
            StatementKind::Block { body, .. } => calls(body, out),
            _ => (),
        } }
    }
    let mut main = Vec::new(); calls(&doc.statements, &mut main);
    serde_json::json!({"definitions": doc.functions.iter().map(|f| {
        let mut nested = Vec::new(); calls(&f.statements, &mut nested);
        serde_json::json!({"name": f.name, "parameters": f.parameters.len(), "results": f.results.len(), "calls": nested})
    }).collect::<Vec<_>>(), "calls": main})
}
