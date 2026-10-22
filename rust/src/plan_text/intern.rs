// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
//! Intern closed construction functions after lowering. Captured assets and
//! native literal attributes become explicit, typed construction arguments.
//! This pass never changes tensor arithmetic or interprets model semantics.
use super::{diagnostic, functions as f, parser::*};
use crate::{plan::Op, Result};
use std::collections::HashMap;
use std::fmt::Write;

#[derive(Clone)]
struct Capture {
    ty: String,
    data: String,
}
#[derive(Clone)]
struct Replacement {
    name: String,
    captures: Vec<Capture>,
    literals: Vec<(String, String)>,
}
struct Body<'a> {
    names: HashMap<String, String>,
    replacements: &'a HashMap<String, Replacement>,
    captures: Vec<Capture>,
    literals: Vec<(String, String)>,
    declarations: String,
    function: bool,
    prefix: String,
}
impl Body<'_> {
    fn capture(&mut self, c: Capture) -> String {
        if let Some(i) = self
            .captures
            .iter()
            .position(|x| x.ty == c.ty && x.data == c.data)
        {
            return format!("{}c{i}", self.prefix);
        }
        let name = format!("{}c{}", self.prefix, self.captures.len());
        if !self.function {
            writeln!(self.declarations, "weight {name}: {} = {};", c.ty, c.data).unwrap();
        }
        self.captures.push(c);
        name
    }
    fn literal(&mut self, kind: &str, value: String) -> String {
        if !self.function {
            return value;
        }
        let name = format!("l{}", self.literals.len());
        self.literals.push((kind.into(), value));
        name
    }
    fn command(&mut self, c: &Call<'_>) -> String {
        let Some(op) = Op::from_name(c.name) else {
            return f::call(c, &self.names, "");
        };
        let mut args = vec![];
        for (i, a) in c.arguments.iter().enumerate() {
            let field = a.name.unwrap_or(op.fields()[i]);
            let at = op.fields().iter().position(|x| *x == field).unwrap_or(i);
            let kind = op.signature()[at];
            let mut value = f::value(&a.value, &self.names);
            if self.function && op == Op::BeginProfileOperation && field == "input_names" {
                // Diagnostic names are local to a template; tensor identities
                // and the caller scope remain in the expanded profile.
                if let ValueKind::List(xs) = &a.value.kind {
                    value = format!(
                        "[{}]",
                        xs.iter()
                            .enumerate()
                            .map(|(i, _)| format!("\"operand{i}\""))
                            .collect::<Vec<_>>()
                            .join(", ")
                    );
                }
            }
            if self.function && op == Op::Resource && field == "name" {
                let owner = c
                    .arguments
                    .iter()
                    .enumerate()
                    .find(|(i, a)| a.name == Some("owner") || a.name.is_none() && *i == 0)
                    .unwrap()
                    .1;
                value = serde_json::to_string(&f::value(&owner.value, &self.names)).unwrap();
            }
            if matches!(
                kind,
                "int" | "size" | "float" | "ints" | "sizes" | "floats" | "bool" | "encoding"
            ) {
                value = self.literal(kind, value);
            }
            args.push(format!("{field}={value}"));
        }
        format!("{}({})", op.name(), args.join(", "))
    }
    fn statement(&mut self, s: &Statement<'_>) -> Result<String> {
        let mut attrs = String::new();
        for a in &s.attributes {
            if self.function && a.name == "guard" {
                let mut a = a.clone();
                for arg in &mut a.arguments {
                    if arg.name == Some("message") {
                        arg.value.kind = ValueKind::String("function requirement".into());
                    }
                }
                write!(attrs, "@{} ", f::call(&a, &self.names, "")).unwrap();
            } else {
                write!(attrs, "@{} ", f::call(a, &self.names, "")).unwrap();
            }
        }
        let content = match &s.kind {
            StatementKind::Declaration { data: Some(_), .. } if self.function => {
                return Ok(String::new())
            }
            StatementKind::Call(c) => self.command(c) + ";\n",
            StatementKind::Invoke { call, outputs } => {
                let replacement = self
                    .replacements
                    .get(call.name)
                    .ok_or_else(|| {
                        crate::Error::invalid(
                            "Construction functions must be emitted in dependency order",
                        )
                    })?
                    .clone();
                let mut args = call
                    .arguments
                    .iter()
                    .map(|a| f::value(&a.value, &self.names))
                    .collect::<Vec<_>>();
                for c in replacement.captures {
                    args.push(self.capture(c));
                }
                for (kind, value) in replacement.literals {
                    args.push(self.literal(&kind, value));
                }
                format!(
                    "invoke {}({}) -> ({});\n",
                    replacement.name,
                    args.join(", "),
                    outputs
                        .iter()
                        .map(|n| self.names.get(*n).cloned().unwrap_or_else(|| n.to_string()))
                        .collect::<Vec<_>>()
                        .join(", ")
                )
            }
            StatementKind::Block { call, body } => {
                let mut out = self.command(call) + " {\n";
                for child in body {
                    out += &self.statement(child)?;
                }
                out + "}\n"
            }
            _ => {
                let mut s = s.clone();
                s.attributes.clear();
                f::render(&s, &self.names, "")
            }
        };
        Ok(attrs + &content)
    }
}

pub(crate) fn intern(source: &str) -> Result<String> {
    let doc = super::parser::document(source)?;
    if doc.functions.is_empty() {
        return Ok(source.into());
    }
    let mut replacements = HashMap::new();
    let mut templates = HashMap::<String, String>::new();
    let mut definitions = String::new();
    for fun in &doc.functions {
        let mut body = Body {
            names: HashMap::new(),
            replacements: &replacements,
            captures: vec![],
            literals: vec![],
            declarations: String::new(),
            function: true,
            prefix: String::new(),
        };
        for (i, b) in fun.parameters.iter().enumerate() {
            body.names.insert(b.name.into(), format!("a{i}"));
        }
        for (i, b) in fun.results.iter().enumerate() {
            body.names.insert(b.name.into(), format!("r{i}"));
        }
        let mut local = 0;
        for s in &fun.statements {
            if let StatementKind::Declaration { binding, data, .. } = &s.kind {
                let name = if let Some(data) = data {
                    let ty = binding.ty.as_ref().ok_or_else(|| {
                        diagnostic(source, binding.span, "Capture needs a storage type")
                    })?;
                    body.capture(Capture {
                        ty: f::ty(ty, &body.names),
                        data: f::value(data, &body.names),
                    })
                } else {
                    let n = format!("v{local}");
                    local += 1;
                    n
                };
                body.names.insert(binding.name.into(), name);
            }
        }
        let mut text = String::new();
        for s in &fun.statements {
            text += &body.statement(s)?;
        }
        let mut args = fun
            .parameters
            .iter()
            .map(|b| f::binding(b, &body.names))
            .collect::<Vec<_>>();
        args.extend(
            body.captures
                .iter()
                .enumerate()
                .map(|(i, c)| format!("c{i}: {}", c.ty)),
        );
        let results = fun
            .results
            .iter()
            .map(|b| f::binding(b, &body.names))
            .collect::<Vec<_>>()
            .join(", ");
        let key = format!(
            "{} -> ({results}) {}\n{text}",
            args.join(", "),
            body.literals
                .iter()
                .map(|x| x.0.as_str())
                .collect::<Vec<_>>()
                .join(",")
        );
        let name = if let Some(name) = templates.get(&key) {
            name.clone()
        } else {
            let name = format!("template{}", templates.len());
            args.extend(
                body.literals
                    .iter()
                    .enumerate()
                    .map(|(i, (kind, value))| format!("l{i}: {kind} = {value}")),
            );
            writeln!(
                definitions,
                "fn {name}({}) -> ({results}) {{\n{text}}}",
                args.join(", ")
            )
            .unwrap();
            templates.insert(key, name.clone());
            name
        };
        let replacement = Replacement {
            name,
            captures: body.captures,
            literals: body.literals,
        };
        replacements.insert(fun.name.to_string(), replacement);
    }
    let mut body = Body {
        names: HashMap::new(),
        replacements: &replacements,
        captures: vec![],
        literals: vec![],
        declarations: String::new(),
        function: false,
        prefix: "__ynn_capture_".into(),
    };
    // Names generated by the compiler are vN; still avoid collisions when this
    // pass is used with a hand-authored construction stream.
    while source.contains(&body.prefix) {
        body.prefix.push('_');
    }
    let mut text = String::new();
    for s in &doc.statements {
        text += &body.statement(s)?;
    }
    let result =
        f::header(&doc) + &definitions + &body.declarations + &text + &f::metadata(&doc, &[], &[]);
    super::check(&result)?;
    Ok(result)
}
