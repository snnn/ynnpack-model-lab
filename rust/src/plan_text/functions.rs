// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
//! Pure, typed source functions. Expansion ends before native plan validation;
//! execution still prepares one graph. Source formatting retains definitions.
use super::parser::*;
use super::{diagnostic, Span};
use crate::plan::{Arg, Op, RawCommand, MAX_COMMANDS, MAX_FILE, MAX_VALUES};
use crate::Result;
use std::collections::{HashMap, HashSet};
use std::fmt::Write;

type Names = HashMap<String, String>;
fn quote(s: &str) -> String {
    serde_json::to_string(s).unwrap()
}
fn name(n: &str, names: &Names) -> String {
    names.get(n).cloned().unwrap_or_else(|| n.into())
}
fn value(v: &Value<'_>, names: &Names) -> String {
    match &v.kind {
        ValueKind::Name(n) | ValueKind::Tensor(n) | ValueKind::Symbol(n) => name(n, names),
        ValueKind::Number(n) => (*n).into(),
        ValueKind::String(s) => quote(s),
        ValueKind::Unknown => "?".into(),
        ValueKind::List(xs) => format!(
            "[{}]",
            xs.iter()
                .map(|x| value(x, names))
                .collect::<Vec<_>>()
                .join(", ")
        ),
        ValueKind::Call(c) => call(c, names, ""),
        ValueKind::Unary(op, x) => format!("{}{}", *op as char, value(x, names)),
        ValueKind::Binary(op, a, b) => format!("({} {op} {})", value(a, names), value(b, names)),
    }
}
fn call(c: &Call<'_>, names: &Names, path: &str) -> String {
    let args = c
        .arguments
        .iter()
        .enumerate()
        .map(|(i, a)| {
            let mut v = value(&a.value, names);
            if !path.is_empty()
                && matches!(
                    c.name,
                    "profile" | "begin_profile_operation" | "BeginProfileOperation"
                )
                && (a.name == Some("name") || a.name.is_none() && i == 0)
            {
                if let ValueKind::String(s) = &a.value.kind {
                    v = quote(&format!("{path}/{s}"));
                }
            }
            match a.name {
                Some(n) => format!("{n}={v}"),
                None => v,
            }
        })
        .collect::<Vec<_>>()
        .join(", ");
    format!("{}({args})", c.name)
}
fn ty(t: &Type<'_>, names: &Names) -> String {
    if t.name == "index" {
        return "index".into();
    }
    let inner = format!(
        "{}[{}]",
        t.name,
        t.dims
            .iter()
            .map(|d| value(d, names))
            .collect::<Vec<_>>()
            .join(", ")
    );
    if t.storage {
        format!("storage<{inner}>")
    } else {
        inner
    }
}
fn binding(b: &Binding<'_>, names: &Names) -> String {
    match &b.ty {
        Some(t) => format!("{}: {}", name(b.name, names), ty(t, names)),
        None => name(b.name, names),
    }
}
fn header(doc: &Document<'_>) -> String {
    format!(
        "ynn {} resource_contract={} completion_contract={} profiling={} {{\n",
        doc.version,
        doc.resource,
        doc.completion,
        if doc.auto_profile { "auto" } else { "explicit" }
    )
}
fn render(s: &Statement<'_>, names: &Names, path: &str) -> String {
    let mut out = String::new();
    for a in &s.attributes {
        write!(out, "@{} ", call(a, names, path)).unwrap();
    }
    match &s.kind {
        StatementKind::Declaration {
            role,
            binding: b,
            data,
        } => {
            write!(out, "{role} {}", binding(b, names)).unwrap();
            if let Some(d) = data {
                write!(out, " = {}", value(d, names)).unwrap();
            }
        }
        StatementKind::Let { bindings, value: v } => {
            write!(
                out,
                "let ({}) = {}",
                bindings
                    .iter()
                    .map(|b| binding(b, names))
                    .collect::<Vec<_>>()
                    .join(", "),
                value(v, names)
            )
            .unwrap();
        }
        StatementKind::Dim {
            name: n,
            source,
            lower,
            upper,
        } => {
            write!(
                out,
                "dim {} = {} in {}..={}",
                name(n, names),
                value(source, names),
                value(lower, names),
                value(upper, names)
            )
            .unwrap();
        }
        StatementKind::Require { lhs, rhs, relation } => {
            write!(
                out,
                "require {} {} {}",
                value(lhs, names),
                match *relation {
                    "le" => "<=",
                    "ge" => ">=",
                    _ => "==",
                },
                value(rhs, names)
            )
            .unwrap();
        }
        StatementKind::Output(n) => {
            write!(out, "output {}", name(n, names)).unwrap();
        }
        StatementKind::Shape {
            name: n,
            value: v,
            input,
        } => {
            write!(
                out,
                "{} {} = {}",
                if *input { "input_shape" } else { "shape" },
                name(n, names),
                value(v, names)
            )
            .unwrap();
        }
        StatementKind::Call(c) => out.push_str(&call(c, names, path)),
        StatementKind::Block { call: c, body } => {
            writeln!(out, "{} {{", call(c, names, path)).unwrap();
            for child in body {
                out.push_str(&render(child, names, path));
            }
            out.push_str("}\n");
            return out;
        }
        StatementKind::Invoke { call: c, outputs } => {
            write!(
                out,
                "invoke {} -> ({})",
                call(c, names, path),
                outputs
                    .iter()
                    .map(|n| name(n, names))
                    .collect::<Vec<_>>()
                    .join(", ")
            )
            .unwrap();
        }
        StatementKind::Return(ns) => {
            write!(
                out,
                "return({})",
                ns.iter()
                    .map(|n| name(n, names))
                    .collect::<Vec<_>>()
                    .join(", ")
            )
            .unwrap();
        }
    }
    out.push_str(";\n");
    out
}
fn declarations<'a, 'b>(ss: &'b [Statement<'a>], out: &mut Vec<&'b Binding<'a>>) {
    for s in ss {
        match &s.kind {
            StatementKind::Declaration { binding, .. } => out.push(binding),
            StatementKind::Let { bindings, .. } => out.extend(bindings),
            StatementKind::Block { body, .. } => declarations(body, out),
            _ => (),
        }
    }
}
fn metadata(doc: &Document<'_>, extra_order: &[String], extra: &[String]) -> String {
    let mut out = "metadata {\n".to_string();
    if doc.order_set {
        writeln!(
            out,
            "order [{}];",
            doc.order
                .iter()
                .map(|n| n.to_string())
                .chain(extra_order.iter().cloned())
                .collect::<Vec<_>>()
                .join(", ")
        )
        .unwrap();
    }
    for m in &doc.metadata {
        writeln!(
            out,
            "{} {} = {};",
            m.kind,
            m.target,
            value(&m.value, &Names::new())
        )
        .unwrap();
    }
    for m in extra {
        out.push_str(m);
    }
    out.push_str("}\n}\n");
    out
}
// Use the same typed-let/profile vocabulary as flat plans. Preserve the tensor
// allocation order explicitly when moving a declaration to its producer.
fn compact<'a>(source: &'a str, doc: &Document<'a>) -> (Vec<Statement<'a>>, Vec<&'a str>) {
    let mut bindings = Vec::new();
    declarations(&doc.statements, &mut bindings);
    let order = if doc.order_set {
        doc.order.clone()
    } else {
        bindings
            .iter()
            .filter(|b| b.ty.as_ref().is_none_or(|t| t.name != "index"))
            .map(|b| b.name)
            .collect()
    };
    let declarations: HashMap<_, _> = doc
        .statements
        .iter()
        .filter_map(|s| match &s.kind {
            StatementKind::Declaration {
                role: "value",
                binding,
                data: None,
            } if s.attributes.is_empty() => Some((binding.name, binding)),
            _ => None,
        })
        .collect();
    let mut resolver = super::resolve::Resolver::new(source);
    let runtime_names: Vec<String> = order
        .iter()
        .map(|n| {
            doc.metadata
                .iter()
                .find_map(|m| {
                    if m.kind == "name" && m.target == *n {
                        if let ValueKind::String(s) = &m.value.kind {
                            return Some(s.clone());
                        }
                    }
                    None
                })
                .unwrap_or_else(|| n.to_string())
        })
        .collect();
    for (i, n) in order.iter().enumerate() {
        resolver.tensors.insert((*n).into(), i as i64);
    }
    // Only tensor identities and enum options affect default profile metadata.
    // Index operands can be represented by distinct dummy symbols here.
    for s in &doc.statements {
        let n = match &s.kind {
            StatementKind::Dim { name, .. } => Some(*name),
            StatementKind::Let { bindings, .. }
                if bindings.len() == 1
                    && bindings[0].ty.as_ref().is_some_and(|t| t.name == "index") =>
            {
                Some(bindings[0].name)
            }
            _ => None,
        };
        if let Some(n) = n {
            resolver
                .symbols
                .insert(n.into(), resolver.symbols.len() as u32);
        }
    }
    let mut replacements = HashMap::new();
    let mut moved = HashSet::new();
    let mut i = 0;
    while i + 2 < doc.statements.len() {
        let ss = &doc.statements[i..i + 3];
        if let [Statement {
            kind: StatementKind::Call(begin),
            ..
        }, Statement {
            kind: StatementKind::Call(compute),
            ..
        }, Statement {
            kind: StatementKind::Call(end),
            ..
        }] = ss
        {
            if matches!(
                begin.name,
                "BeginProfileOperation" | "begin_profile_operation"
            ) && matches!(end.name, "EndProfileOperation" | "end_profile_operation")
            {
                if let Some((op, _)) = super::schema::lookup(compute.name) {
                    let outputs: Vec<_> = compute
                        .arguments
                        .iter()
                        .filter(|a| a.name.is_some_and(|n| super::schema::output(op, n)))
                        .collect();
                    let bs: Option<Vec<_>> = outputs
                        .iter()
                        .map(|a| match a.value.kind {
                            ValueKind::Name(n) | ValueKind::Tensor(n) => {
                                declarations.get(n).map(|b| (*b).clone())
                            }
                            _ => None,
                        })
                        .collect();
                    if let Some(bs) = bs.filter(|bs| !bs.is_empty()) {
                        if bs.iter().all(|b| !moved.contains(b.name)) {
                            moved.extend(bs.iter().map(|b| b.name));
                            let mut c = compute.clone();
                            c.arguments
                                .retain(|a| !a.name.is_some_and(|n| super::schema::output(op, n)));
                            let mut profile = begin.clone();
                            profile.name = "profile";
                            // Avoid repeating the primitive's inferred input,
                            // output and kind lists on every authored operation.
                            let mut args = vec![None; op.fields().len()];
                            if let Some((_, implicit)) = super::schema::lookup(compute.name) {
                                if let Some(a) = implicit {
                                    args[0] = Some(a);
                                }
                            }
                            for a in &compute.arguments {
                                if let Some(i) = a
                                    .name
                                    .and_then(|n| op.fields().iter().position(|f| *f == n))
                                {
                                    // These AST nodes already passed parse/validation.
                                    // Dummy spans keep optional formatting failures local.
                                    let mut v = a.value.clone();
                                    v.span = Span { start: 0, end: 0 };
                                    args[i] =
                                        resolver.arg(op.signature()[i], op.fields()[i], &v).ok();
                                }
                            }
                            if let Some(args) = args.into_iter().collect::<Option<Vec<Arg>>>() {
                                let defaults = super::schema::profile(
                                    &RawCommand { op, args },
                                    &runtime_names,
                                );
                                profile.arguments.retain(|a| {
                                    let Some(i) = a.name.and_then(|n| {
                                        Op::BeginProfileOperation
                                            .fields()
                                            .iter()
                                            .position(|f| *f == n)
                                    }) else {
                                        return true;
                                    };
                                    let mut v = a.value.clone();
                                    v.span = Span { start: 0, end: 0 };
                                    resolver
                                        .arg(
                                            Op::BeginProfileOperation.signature()[i],
                                            Op::BeginProfileOperation.fields()[i],
                                            &v,
                                        )
                                        .ok()
                                        .as_ref()
                                        != Some(&defaults[i])
                                });
                            }
                            replacements.insert(
                                i,
                                Statement {
                                    span: ss[0].span,
                                    attributes: vec![profile],
                                    kind: StatementKind::Let {
                                        bindings: bs,
                                        value: Value {
                                            span: compute.span,
                                            depth: 1,
                                            kind: ValueKind::Call(c),
                                        },
                                    },
                                },
                            );
                            i += 3;
                            continue;
                        }
                    }
                }
            }
        }
        i += 1;
    }
    let mut out = Vec::new();
    i = 0;
    while i < doc.statements.len() {
        if let Some(s) = replacements.remove(&i) {
            out.push(s);
            i += 3;
            continue;
        }
        let s = &doc.statements[i];
        if !matches!(&s.kind, StatementKind::Declaration { binding, .. } if moved.contains(binding.name))
        {
            out.push(s.clone());
        }
        i += 1;
    }
    (out, order)
}
pub(super) fn format(source: &str, doc: &Document<'_>) -> Result<String> {
    let mut out = header(doc);
    for f in &doc.functions {
        writeln!(
            out,
            "  fn {}({}) -> ({}) {{",
            f.name,
            f.parameters
                .iter()
                .map(|b| binding(b, &Names::new()))
                .collect::<Vec<_>>()
                .join(", "),
            f.results
                .iter()
                .map(|b| binding(b, &Names::new()))
                .collect::<Vec<_>>()
                .join(", ")
        )
        .unwrap();
        for s in &f.statements {
            for line in render(s, &Names::new(), "").lines() {
                writeln!(out, "    {line}").unwrap();
            }
        }
        out.push_str("  }\n\n");
    }
    let (statements, order) = compact(source, doc);
    // Runtime names remain in metadata; readable aliases carry the code.
    let mut names = Names::new();
    let mut used: HashSet<String> = order.iter().map(|n| n.to_string()).collect();
    used.extend(["none".to_string(), "true".into(), "false".into()]);
    for m in &doc.metadata {
        if m.kind != "name" {
            continue;
        }
        if let ValueKind::String(s) = &m.value.kind {
            let mut alias: String = s
                .chars()
                .take(72)
                .map(|c| {
                    if c.is_ascii_alphanumeric() || c == '_' {
                        c
                    } else {
                        '_'
                    }
                })
                .collect();
            if alias.is_empty() || alias.as_bytes()[0].is_ascii_digit() {
                alias.insert_str(0, "t_");
            }
            while used.contains(&alias) && alias != m.target {
                alias.push('_');
            }
            used.insert(alias.clone());
            names.insert(m.target.into(), alias);
        }
    }
    for s in &statements {
        for line in render(s, &names, "").lines() {
            writeln!(out, "  {line}").unwrap();
        }
    }
    out.push_str("metadata {\n");
    writeln!(
        out,
        "order [{}];",
        order
            .iter()
            .map(|n| name(n, &names))
            .collect::<Vec<_>>()
            .join(", ")
    )
    .unwrap();
    for m in &doc.metadata {
        writeln!(
            out,
            "{} {} = {};",
            m.kind,
            name(m.target, &names),
            value(&m.value, &names)
        )
        .unwrap();
    }
    out.push_str("}\n}\n");
    Ok(out)
}
#[derive(Clone)]
struct TensorType {
    dtype: String,
    dims: Vec<String>,
}
struct Expander<'a, 'b> {
    source: &'a str,
    functions: HashMap<&'a str, &'b Function<'a>>,
    used: HashSet<String>,
    types: HashMap<String, TensorType>,
    resources: HashSet<String>,
    stack: Vec<&'a str>,
    serial: usize,
    statements: usize,
    locals: Vec<String>,
    metadata: Vec<String>,
    out: String,
    operation_depth: usize,
    profile_depth: usize,
    suppress_profiles: bool,
}
impl<'a, 'b> Expander<'a, 'b> {
    fn new(source: &'a str, doc: &'b Document<'a>) -> Result<Self> {
        let mut e = Self {
            source,
            functions: HashMap::new(),
            used: HashSet::new(),
            types: HashMap::new(),
            resources: HashSet::new(),
            stack: Vec::new(),
            serial: 0,
            statements: 0,
            locals: Vec::new(),
            metadata: Vec::new(),
            out: header(doc),
            operation_depth: 0,
            profile_depth: 0,
            suppress_profiles: false,
        };
        for f in &doc.functions {
            if e.functions.insert(f.name, f).is_some() {
                return Err(diagnostic(source, f.span, "Duplicate function name"));
            }
        }
        e.register(&doc.statements, &Names::new(), false, "")?;
        fn resources(ss: &[Statement<'_>], out: &mut HashSet<String>) {
            for s in ss {
                match &s.kind {
                    StatementKind::Declaration {
                        role: "state",
                        binding,
                        ..
                    } => {
                        out.insert(binding.name.into());
                    }
                    StatementKind::Call(c) => {
                        if let Some((op, _)) = super::schema::lookup(c.name) {
                            let field = match op {
                                Op::Resource => "owner",
                                Op::View | Op::Append => "output",
                                _ => continue,
                            };
                            for (i, a) in c.arguments.iter().enumerate() {
                                if a.name.or_else(|| op.fields().get(i).copied()) == Some(field) {
                                    if let ValueKind::Name(n) | ValueKind::Tensor(n) = a.value.kind
                                    {
                                        out.insert(n.into());
                                    }
                                }
                            }
                        }
                    }
                    StatementKind::Let { bindings, value } => {
                        if let ValueKind::Call(c) = &value.kind {
                            if matches!(
                                super::schema::lookup(c.name),
                                Some((Op::View | Op::Append, _))
                            ) {
                                out.extend(bindings.iter().map(|b| b.name.into()));
                            }
                        }
                    }
                    StatementKind::Block { body, .. } => resources(body, out),
                    _ => (),
                }
            }
        }
        resources(&doc.statements, &mut e.resources);
        Ok(e)
    }
    fn tensor(&self, t: &Type<'_>, names: &Names) -> TensorType {
        TensorType {
            dtype: t.name.into(),
            dims: t.dims.iter().map(|d| value(d, names)).collect(),
        }
    }
    fn register(
        &mut self,
        ss: &[Statement<'a>],
        names: &Names,
        local: bool,
        path: &str,
    ) -> Result<()> {
        let mut bs = Vec::new();
        declarations(ss, &mut bs);
        for b in bs {
            let n = name(b.name, names);
            if !self.used.insert(n.clone()) {
                return Err(diagnostic(
                    self.source,
                    b.span,
                    "Duplicate function/local binding",
                ));
            }
            if let Some(t) = &b.ty {
                if t.name == "index" {
                    continue;
                }
                self.types.insert(n.clone(), self.tensor(t, names));
            }
            if local {
                self.locals.push(n.clone());
                self.metadata.push(format!(
                    "name {n} = {};\n",
                    quote(&format!("{path}/{}", b.name))
                ));
            }
            if self.types.len() > MAX_VALUES {
                return Err(diagnostic(
                    self.source,
                    b.span,
                    "Function tensor expansion limit",
                ));
            }
        }
        Ok(())
    }
    fn compatible(&self, b: &Binding<'_>, actual: &str, names: &Names) -> Result<()> {
        if self.resources.contains(actual) {
            return Err(diagnostic(
                self.source,
                b.span,
                "Function tensor must not carry a resource",
            ));
        }
        let t = b.ty.as_ref().unwrap();
        let a = self.types.get(actual).ok_or_else(|| {
            diagnostic(
                self.source,
                b.span,
                format!("Function tensor {actual} needs an explicit type"),
            )
        })?;
        let expected = self.tensor(t, names);
        if a.dtype != expected.dtype
            || a.dims.len() != expected.dims.len()
            || a.dims.iter().zip(&expected.dims).any(|(x, y)| {
                // Zero is the native plan's unspecified storage extent. Logical
                // extents are checked by the body's shape/require statements.
                match (x.parse::<i64>(), y.parse::<i64>()) {
                    (Ok(x), Ok(y)) => x > 0 && y > 0 && x != y,
                    _ => false,
                }
            })
        {
            return Err(diagnostic(
                self.source,
                b.span,
                format!("Function tensor type mismatch for {}", b.name),
            ));
        }
        Ok(())
    }
    fn push(&mut self, text: &str, span: Span) -> Result<()> {
        self.statements += 1;
        if self.statements > MAX_COMMANDS
            || self.out.len().saturating_add(text.len()) as u64 > MAX_FILE
        {
            return Err(diagnostic(
                self.source,
                span,
                "Function expansion budget exceeded",
            ));
        }
        self.out.push_str(text);
        Ok(())
    }
    fn statements(&mut self, ss: &[Statement<'a>], names: &Names, path: &str) -> Result<()> {
        for s in ss {
            match &s.kind {
                StatementKind::Invoke { call: c, outputs } => {
                    self.invoke(s, c, outputs, names, path).map_err(|e| {
                        diagnostic(self.source, s.span, format!("Call to {}: {e}", c.name))
                    })?
                }
                StatementKind::Return(_) => {
                    return Err(diagnostic(self.source, s.span, "Unexpected return"))
                }
                StatementKind::Block { call: c, body } => {
                    if !s.attributes.is_empty() {
                        return Err(diagnostic(
                            self.source,
                            s.span,
                            "Block annotations unsupported",
                        ));
                    }
                    if self.suppress_profiles && c.name == "profile" {
                        self.statements(body, names, path)?;
                        continue;
                    }
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
                    if self.suppress_profiles
                        && matches!(
                            op,
                            Some(Op::BeginProfileOperation | Op::EndProfileOperation)
                        )
                    {
                        continue;
                    }
                    match op {
                        Some(Op::BeginOperation) => self.operation_depth += 1,
                        Some(Op::EndOperation) => {
                            self.operation_depth = self.operation_depth.saturating_sub(1)
                        }
                        Some(Op::BeginProfileOperation) => self.profile_depth += 1,
                        Some(Op::EndProfileOperation) => {
                            self.profile_depth = self.profile_depth.saturating_sub(1)
                        }
                        _ => (),
                    }
                    self.push(&render(s, names, path), s.span)?;
                }
                StatementKind::Let { .. } if self.suppress_profiles => {
                    let mut unprofiled = s.clone();
                    unprofiled.attributes.retain(|a| a.name != "profile");
                    self.push(&render(&unprofiled, names, path), s.span)?;
                }
                _ => self.push(&render(s, names, path), s.span)?,
            }
        }
        Ok(())
    }
    fn invoke(
        &mut self,
        s: &Statement<'a>,
        c: &Call<'a>,
        outputs: &[&str],
        parent: &Names,
        path: &str,
    ) -> Result<()> {
        let f = *self.functions.get(c.name).ok_or_else(|| {
            diagnostic(self.source, c.span, format!("Unknown function {}", c.name))
        })?;
        if self.stack.len() >= 64 || self.stack.contains(&c.name) {
            return Err(diagnostic(
                self.source,
                c.span,
                format!("Recursive/deep call to {}", c.name),
            ));
        }
        if c.arguments.len() != f.parameters.len()
            || outputs.len() != f.results.len()
            || c.arguments.iter().any(|a| a.name.is_some())
        {
            return Err(diagnostic(
                self.source,
                c.span,
                format!("Function arity mismatch: {}", c.name),
            ));
        }
        self.serial += 1;
        let prefix = format!("__fn{}_", self.serial);
        let mut scope = format!("{}/{}{}", path, f.name, self.serial)
            .trim_start_matches('/')
            .to_string();
        if !s.attributes.is_empty() {
            if s.attributes.len() != 1
                || s.attributes[0].name != "scope"
                || s.attributes[0].arguments.len() != 1
            {
                return Err(diagnostic(
                    self.source,
                    s.span,
                    "Invoke accepts only @scope(name=...)",
                ));
            }
            let a = &s.attributes[0].arguments[0];
            if a.name != Some("name") {
                return Err(diagnostic(self.source, a.span, "Scope needs name"));
            }
            if let ValueKind::String(p) = &a.value.kind {
                scope = if path.is_empty() {
                    p.clone()
                } else {
                    format!("{path}/{p}")
                };
            } else {
                return Err(diagnostic(self.source, a.span, "Scope must be a string"));
            }
        }
        let mut names = Names::new();
        for (b, a) in f.parameters.iter().zip(&c.arguments) {
            names.insert(b.name.into(), value(&a.value, parent));
        }
        for (b, n) in f.results.iter().zip(outputs) {
            names.insert(b.name.into(), name(n, parent));
        }
        for (b, a) in f.parameters.iter().zip(&c.arguments) {
            if b.ty.as_ref().unwrap().name != "index" {
                if !matches!(a.value.kind, ValueKind::Name(_) | ValueKind::Tensor(_)) {
                    return Err(diagnostic(
                        self.source,
                        a.span,
                        "Tensor argument must be a tensor name",
                    ));
                }
                self.compatible(b, &names[b.name], &names)?;
            } else {
                let mut alias = format!("{prefix}index_{}", b.name);
                while self.used.contains(&alias) {
                    alias.push('_');
                }
                self.used.insert(alias.clone());
                self.push(
                    &format!("let {alias}: index = {};\n", names[b.name]),
                    c.span,
                )?;
                names.insert(b.name.into(), alias);
            }
        }
        for b in &f.results {
            self.compatible(b, &names[b.name], &names)?;
        }
        let mut bs = Vec::new();
        declarations(&f.statements, &mut bs);
        let mut local_names = HashSet::new();
        for b in bs {
            if names.contains_key(b.name) {
                return Err(diagnostic(
                    self.source,
                    b.span,
                    "Function local shadows parameter/result",
                ));
            }
            let mut n = format!("{prefix}{}", b.name);
            while self.used.contains(&n) || local_names.contains(&n) {
                n.push('_');
            }
            local_names.insert(n.clone());
            names.insert(b.name.into(), n);
        }
        self.register(&f.statements, &names, true, &scope)?;
        self.stack.push(c.name);
        let previous_suppression = self.suppress_profiles;
        self.suppress_profiles |= self.operation_depth > 0 || self.profile_depth > 0;
        let body = &f.statements[..f.statements.len() - 1];
        let result = self.statements(body, &names, &scope).map_err(|e| {
            diagnostic(
                self.source,
                c.span,
                format!(
                    "Calling {} (definition at byte {}): {e}",
                    f.name, f.span.start
                ),
            )
        });
        self.stack.pop();
        self.suppress_profiles = previous_suppression;
        result
    }
}

fn validate_signature(source: &str, f: &Function<'_>) -> Result<()> {
    let mut seen = HashSet::new();
    if f.results.is_empty() {
        return Err(diagnostic(source, f.span, "Function needs results"));
    }
    for b in f.parameters.iter().chain(&f.results) {
        let t = b.ty.as_ref().unwrap();
        if !seen.insert(b.name) {
            return Err(diagnostic(source, b.span, "Duplicate formal binding"));
        }
        if t.name != "index" && !t.storage {
            return Err(diagnostic(
                source,
                b.span,
                "Function tensors need storage types; logical constraints belong in require/shape",
            ));
        }
    }
    if f.results
        .iter()
        .any(|b| b.ty.as_ref().unwrap().name == "index")
    {
        return Err(diagnostic(
            source,
            f.span,
            "Function results must be tensors",
        ));
    }
    if !matches!(f.statements.last().map(|s| &s.kind), Some(StatementKind::Return(ns)) if *ns == f.results.iter().map(|b| b.name).collect::<Vec<_>>())
    {
        return Err(diagnostic(
            source,
            f.span,
            "Function must end with return of its named results",
        ));
    }
    fn closed(source: &str, ss: &[Statement<'_>]) -> Result<()> {
        for s in ss {
            match &s.kind {
                StatementKind::Declaration {
                    role: "input" | "state",
                    ..
                }
                | StatementKind::Dim { .. }
                | StatementKind::Output(_)
                | StatementKind::Return(_) => {
                    return Err(diagnostic(
                        source,
                        s.span,
                        "Function has a hidden input, state, or result",
                    ))
                }
                StatementKind::Block { body, .. } => closed(source, body)?,
                _ => (),
            }
        }
        Ok(())
    }
    closed(source, &f.statements[..f.statements.len() - 1])?;
    Ok(())
}
pub(super) fn expand(source: &str, doc: &Document<'_>) -> Result<String> {
    for f in &doc.functions {
        validate_signature(source, f)?;
    }
    // Validate each closed body, including unused definitions, in an isolated
    // namespace. A reference to a caller's tensor cannot become a capture.
    let mut validation_work = 0usize;
    for f in &doc.functions {
        let mut stub = header(doc);
        for b in f.parameters.iter().chain(&f.results) {
            let t = b.ty.as_ref().unwrap();
            if t.name == "index" {
                writeln!(
                    stub,
                    "dim {} = parameter({}) in 0..=2147483647;",
                    b.name,
                    quote(b.name)
                )
                .unwrap();
            } else {
                writeln!(
                    stub,
                    "{} {};",
                    if f.parameters.iter().any(|p| p.name == b.name) {
                        "input"
                    } else {
                        "value"
                    },
                    binding(b, &Names::new())
                )
                .unwrap();
            }
        }
        for b in &f.results {
            writeln!(stub, "output {};", b.name).unwrap();
        }
        writeln!(
            stub,
            "invoke {}({}) -> ({});",
            f.name,
            f.parameters
                .iter()
                .map(|b| b.name)
                .collect::<Vec<_>>()
                .join(", "),
            f.results
                .iter()
                .map(|b| b.name)
                .collect::<Vec<_>>()
                .join(", ")
        )
        .unwrap();
        stub.push_str("}\n");
        let stubdoc = super::parser::document(&stub)?;
        let mut e = Expander::new(source, doc)?;
        // The stub's AST borrows a different string, but all definitions are
        // still resolved from the original document during this invocation.
        e.types.clear();
        e.used.clear();
        e.resources.clear();
        e.out = header(doc);
        e.register(&stubdoc.statements, &Names::new(), false, "")?;
        e.statements(&stubdoc.statements, &Names::new(), "")?;
        validation_work = validation_work.saturating_add(e.statements);
        if validation_work > MAX_COMMANDS {
            return Err(diagnostic(
                source,
                f.span,
                "Function definition validation budget exceeded",
            ));
        }
        e.out.push_str("}\n");
        let plan =
            super::compile::compile(&e.out, super::parser::document(&e.out)?).map_err(|err| {
                diagnostic(
                    source,
                    f.span,
                    format!("Invalid closed function {}: {err}", f.name),
                )
            })?;
        for c in &plan.commands {
            if matches!(
                c.op,
                Op::Append
                    | Op::View
                    | Op::Resource
                    | Op::BeginOperation
                    | Op::EndOperation
                    | Op::BindScalarParameter
            ) {
                return Err(diagnostic(
                    source,
                    f.span,
                    "Function must be pure and resource-free",
                ));
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
        for s in ss {
            match &s.kind {
                StatementKind::Invoke { call, .. } => out.push(call.name.into()),
                StatementKind::Block { body, .. } => calls(body, out),
                _ => (),
            }
        }
    }
    let mut main = Vec::new();
    calls(&doc.statements, &mut main);
    serde_json::json!({"definitions": doc.functions.iter().map(|f| {
        let mut nested = Vec::new(); calls(&f.statements, &mut nested);
        serde_json::json!({"name": f.name, "parameters": f.parameters.len(), "results": f.results.len(), "calls": nested})
    }).collect::<Vec<_>>(), "calls": main})
}
