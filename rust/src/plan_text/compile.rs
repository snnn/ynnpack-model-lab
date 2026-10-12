// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
//! Resolve the surface language into the existing validated construction plan.
use super::parser::*;
use super::resolve::Resolver;
use super::{schema, Span};
use crate::plan::{Arg, Expr, Op, Plan, RawCommand, MAX_COMMANDS, MAX_VALUES};
use crate::Result;
use std::collections::{HashMap, HashSet};

#[derive(Clone)]
struct TensorType {
    dtype: String,
    dims: Vec<Expr>,
    storage: bool,
}
struct Compiler<'a> {
    r: Resolver<'a>,
    metadata: HashMap<(String, String), Value<'a>>,
    types: HashMap<String, TensorType>,
    names: Vec<String>,
    tensor_order: Vec<String>,
    declarations: Vec<Option<(RawCommand, Span)>>,
    commands: Vec<RawCommand>,
    spans: Vec<Span>,
    outputs: HashSet<&'a str>,
    auto_profile: bool,
    profile_targets: HashSet<&'a str>,
    resource_targets: HashSet<String>,
    alias_spans: Vec<(String, Span)>,
}
fn index(bindings: &[Binding<'_>], value: &Value<'_>) -> bool {
    bindings.len() == 1
        && (bindings[0].ty.as_ref().is_some_and(|t| t.name == "index")
            || bindings[0].ty.is_none()
                && match &value.kind {
                    ValueKind::Call(c) => {
                        matches!(c.name, "checked" | "min" | "max" | "floor_div" | "ceil_div")
                    }
                    _ => true,
                })
}
fn walk<'a, 'b>(statements: &'b [Statement<'a>], out: &mut Vec<&'b Statement<'a>>) {
    for s in statements {
        out.push(s);
        if let StatementKind::Block { body, .. } = &s.kind {
            walk(body, out);
        }
    }
}
impl<'a> Compiler<'a> {
    fn emit(&mut self, op: Op, args: Vec<Arg>, span: Span) -> Result<()> {
        if self.commands.len() >= MAX_COMMANDS {
            return Err(self.r.error(span, "Command limit exceeded"));
        }
        self.commands.push(RawCommand { op, args });
        self.spans.push(span);
        Ok(())
    }
    fn meta(&self, kind: &'a str, name: &str) -> Option<&Value<'a>> {
        self.metadata.get(&(kind.into(), name.into()))
    }
    fn call<'b>(&self, value: &'b Value<'a>, name: &str) -> Result<&'b Call<'a>> {
        if let ValueKind::Call(c) = &value.kind {
            if c.name == name {
                return Ok(c);
            }
        }
        Err(self.r.error(value.span, format!("Expected {name}(...)")))
    }
    fn annotation<'b>(&self, s: &'b Statement<'a>, name: &str) -> Option<&'b Call<'a>> {
        s.attributes.iter().find(|a| a.name == name)
    }
    fn check_annotations(&self, s: &Statement<'a>, allowed: &[&str]) -> Result<()> {
        let mut seen = HashSet::new();
        for a in &s.attributes {
            if !allowed.contains(&a.name) || !seen.insert(a.name) {
                return Err(self.r.error(
                    a.span,
                    format!("Unknown or duplicate annotation {}", a.name),
                ));
            }
        }
        Ok(())
    }
    fn ty(&self, ty: &Type<'a>) -> Result<TensorType> {
        if ty.name == "index" {
            return Err(self.r.error(ty.span, "Expected a tensor type"));
        }
        let dims = ty
            .dims
            .iter()
            .map(|d| self.r.expr(d))
            .collect::<Result<Vec<_>>>()?;
        if ty.storage && dims.iter().any(|e| !matches!(e, Expr::Known(_))) {
            return Err(self
                .r
                .error(ty.span, "Storage templates require integer dimensions"));
        }
        Ok(TensorType {
            dtype: ty.name.into(),
            dims,
            storage: ty.storage,
        })
    }
    fn declare(
        &mut self,
        b: &Binding<'a>,
        ty: TensorType,
        role: &str,
        data: Option<&Value<'a>>,
    ) -> Result<()> {
        let id = self.r.tensors[b.name] as usize;
        let flags = i64::from(role == "input" || role == "state")
            | if self.outputs.contains(b.name) { 2 } else { 0 };
        let packed = ty
            .dtype
            .strip_prefix("packed_i")
            .and_then(|s| s.parse::<i64>().ok());
        let mut op = if packed.is_some() {
            Op::PackedTensor
        } else {
            Op::Tensor
        };
        if let Some(v) = self.meta("declaration", b.name) {
            op = Op::from_name(&self.r.name(v)?)
                .filter(|op| op.declares_tensor())
                .ok_or_else(|| self.r.error(v.span, "Invalid declaration kind"))?;
            if matches!(op, Op::PackedTensor | Op::PackedConstantOutput) != packed.is_some() {
                return Err(self.r.error(v.span, "Declaration kind conflicts with type"));
            }
        }
        if matches!(op, Op::ConstantOutput | Op::PackedConstantOutput) && flags != 2 {
            return Err(self
                .r
                .error(b.span, "ConstantOutput requires only the output flag"));
        }
        let mut dims = ty
            .dims
            .iter()
            .map(|e| if let Expr::Known(n) = e { *n } else { 0 })
            .collect();
        if let Some(v) = self.meta("storage", b.name) {
            dims = self
                .r
                .list(v)?
                .iter()
                .map(|v| self.r.int(v))
                .collect::<Result<_>>()?;
        }
        let data = match data {
            Some(v) => self.r.arg("data", "data", v)?,
            None => Arg::Data(None),
        };
        if role == "weight" && matches!(data, Arg::Data(None)) {
            return Err(self.r.error(b.span, "A weight requires an asset"));
        }
        let dtype = if let Some(n) = packed {
            Arg::Int(n)
        } else {
            Arg::Dtype(
                match ty.dtype.as_str() {
                    "i2" => "int2",
                    "i4" => "int4",
                    "i8" => "int8",
                    "u8" => "uint8",
                    "i32" => "int32",
                    s => s,
                }
                .into(),
            )
        };
        let mut args = vec![
            Arg::Int(id as i64),
            Arg::Text(self.names[id].clone()),
            dtype,
            Arg::Ints(dims),
        ];
        if matches!(op, Op::Tensor | Op::PackedTensor) {
            args.push(Arg::Int(flags));
        }
        args.push(data);
        self.declarations[id] = Some((RawCommand { op, args }, b.span));
        self.types.insert(b.name.into(), ty);
        Ok(())
    }
    fn command(&self, c: &Call<'a>, bindings: &[Binding<'a>]) -> Result<RawCommand> {
        let (op, operator) = schema::lookup(c.name).ok_or_else(|| {
            self.r
                .error(c.span, format!("Unknown operation {}", c.name))
        })?;
        if op.declares_tensor() || op == Op::Symbol {
            return Err(self
                .r
                .error(c.span, "Use a typed declaration or dim binding"));
        }
        let fields = op.fields();
        let mut values = vec![None; fields.len()];
        if let Some(a) = operator {
            values[0] = Some(a);
        }
        if !bindings.is_empty() {
            let output_fields: Vec<usize> = fields
                .iter()
                .enumerate()
                .filter(|(_, f)| schema::output(op, f))
                .map(|(i, _)| i)
                .collect();
            if op == Op::Split {
                values[output_fields[0]] = Some(Arg::Ints(
                    bindings.iter().map(|b| self.r.tensors[b.name]).collect(),
                ));
            } else {
                if output_fields.len() != bindings.len() {
                    return Err(self.r.error(c.span, "Wrong number of result bindings"));
                }
                for (i, b) in output_fields.into_iter().zip(bindings) {
                    values[i] = Some(Arg::Int(self.r.tensors[b.name]));
                }
            }
        }
        let mut named = false;
        for a in &c.arguments {
            let i = if let Some(field) = a.name {
                named = true;
                fields.iter().position(|f| *f == field).ok_or_else(|| {
                    self.r
                        .error(a.span, format!("Unknown field {field} for {}", c.name))
                })?
            } else {
                if named {
                    return Err(self
                        .r
                        .error(a.span, "Positional operands must precede named attributes"));
                }
                let i = values
                    .iter()
                    .position(Option::is_none)
                    .ok_or_else(|| self.r.error(a.span, "Too many operands"))?;
                if !matches!(op.signature()[i], "id" | "ids" | "operand" | "optional") {
                    return Err(self.r.error(a.span, "Attributes must be named"));
                }
                i
            };
            if values[i].is_some() {
                return Err(self
                    .r
                    .error(a.span, format!("Duplicate field {}", fields[i])));
            }
            values[i] = Some(self.r.arg(op.signature()[i], fields[i], &a.value)?);
        }
        let args = values
            .into_iter()
            .enumerate()
            .map(|(i, a)| {
                a.ok_or_else(|| {
                    self.r.error(
                        c.span,
                        format!("Missing field {} for {}", fields[i], c.name),
                    )
                })
            })
            .collect::<Result<_>>()?;
        Ok(RawCommand { op, args })
    }
    fn infer(&self, command: &RawCommand, b: &Binding<'a>) -> Result<TensorType> {
        let ids = schema::inputs(command);
        let first = ids
            .first()
            .and_then(|id| self.types.get(&self.tensor_order[*id as usize]));
        let Some(first) = first else {
            return Err(self
                .r
                .error(b.span, "Result requires an explicit tensor type"));
        };
        let mut ty = first.clone();
        match command.op {
            Op::Unary
            | Op::Copy
            | Op::Polynomial
            | Op::Softmax
            | Op::Gelu
            | Op::Mask
            | Op::Append => {}
            Op::Binary => {
                let other = self.types.get(&self.tensor_order[ids[1] as usize]);
                if !other.is_some_and(|t| t.dtype == ty.dtype && t.dims == ty.dims) {
                    return Err(self
                        .r
                        .error(b.span, "Broadcast result requires an explicit tensor type"));
                }
            }
            Op::View => {
                let axis = command.args[2].int();
                let axis = if axis < 0 {
                    ty.dims.len() as i64 + axis
                } else {
                    axis
                };
                if axis < 0 || axis as usize >= ty.dims.len() {
                    return Err(self.r.error(b.span, "View axis out of range"));
                }
                let (Arg::Expr(begin), Arg::Expr(end)) = (&command.args[3], &command.args[4])
                else {
                    unreachable!()
                };
                ty.dims[axis as usize] = match (begin, end) {
                    (Expr::Known(begin), Expr::Known(end)) => Expr::Known(
                        end.checked_sub(*begin)
                            .ok_or_else(|| self.r.error(b.span, "View length overflow"))?,
                    ),
                    _ => Expr::Add(vec![
                        end.clone(),
                        Expr::Mul(vec![Expr::Known(-1), begin.clone()]),
                    ]),
                };
            }
            _ => {
                return Err(self
                    .r
                    .error(b.span, "Result requires an explicit tensor type"))
            }
        }
        // Inference does not add a new runtime shape contract. Explicit logical
        // annotations do; backend construction still infers operation shapes.
        ty.storage = true;
        Ok(ty)
    }
    fn overlay(&self, call: &Call<'a>, args: &mut [Arg], op: Op) -> Result<()> {
        let mut seen = HashSet::new();
        for a in &call.arguments {
            let name = a
                .name
                .ok_or_else(|| self.r.error(a.span, "Expected a named metadata field"))?;
            let i = op
                .fields()
                .iter()
                .position(|f| *f == name)
                .ok_or_else(|| self.r.error(a.span, format!("Unknown field {name}")))?;
            if !seen.insert(name) {
                return Err(self.r.error(a.span, format!("Duplicate field {name}")));
            }
            args[i] = self.r.arg(op.signature()[i], name, &a.value)?;
        }
        Ok(())
    }
    fn shape(&mut self, b: &Binding<'a>, input: bool, force: bool, span: Span) -> Result<()> {
        let ty = &self.types[b.name];
        if !ty.storage && (!input || force || ty.dims.iter().any(|d| !matches!(d, Expr::Known(_))))
        {
            self.emit(
                if input {
                    Op::InputShape
                } else {
                    Op::ResultShape
                },
                vec![
                    Arg::Int(self.r.tensors[b.name]),
                    Arg::Exprs(ty.dims.clone()),
                ],
                span,
            )?;
        }
        Ok(())
    }
    fn statements(&mut self, statements: &[Statement<'a>], grouped: bool) -> Result<()> {
        for s in statements {
            match &s.kind {
                StatementKind::Invoke { .. } | StatementKind::Return(_) => {
                    return Err(self
                        .r
                        .error(s.span, "Function call/return outside function expansion"));
                }
                StatementKind::Declaration {
                    role,
                    binding,
                    data,
                } => {
                    self.check_annotations(s, &["shape", "resource"])?;
                    if let Some(a) = self.annotation(s, "shape") {
                        self.r.positional(a, Some(0))?;
                    }
                    if self.annotation(s, "resource").is_some() && *role != "state" {
                        return Err(self
                            .r
                            .error(s.span, "@resource requires a state declaration"));
                    }
                    let ty = self.ty(binding.ty.as_ref().unwrap())?;
                    if ty.storage && self.annotation(s, "shape").is_some() {
                        return Err(self.r.error(
                            s.span,
                            "@shape requires a logical type, not a storage template",
                        ));
                    }
                    self.declare(binding, ty, role, data.as_ref())?;
                    self.shape(binding, true, self.annotation(s, "shape").is_some(), s.span)?;
                }
                StatementKind::Dim {
                    name,
                    source,
                    lower,
                    upper,
                } => {
                    self.check_annotations(s, &[])?;
                    let lo = self.r.int(lower)?;
                    let hi = self.r.int(upper)?;
                    let ValueKind::Call(c) = &source.kind else {
                        return Err(self
                            .r
                            .error(source.span, "Expected axis, parameter or instance binding"));
                    };
                    let mut args = vec![Arg::Int(self.r.symbols[*name] as i64)];
                    let (kind, tail) = match c.name {
                        "axis" => {
                            let a = self.r.positional(c, Some(2))?;
                            (
                                "Axis",
                                vec![Arg::Int(self.r.tensor(a[0])?), Arg::Int(self.r.int(a[1])?)],
                            )
                        }
                        "parameter" | "instance" => {
                            let a = self.r.positional(c, Some(1))?;
                            (
                                if c.name == "parameter" {
                                    "Parameter"
                                } else {
                                    "InstanceParameter"
                                },
                                vec![Arg::Text(self.r.string(a[0])?), Arg::Int(lo), Arg::Int(hi)],
                            )
                        }
                        _ => {
                            return Err(self.r.error(
                                source.span,
                                "Unknown symbol binding; expected axis, parameter or instance",
                            ))
                        }
                    };
                    args.extend([Arg::Text(kind.into()), Arg::Int(lo), Arg::Int(hi)]);
                    args.extend(tail);
                    self.emit(Op::Symbol, args, s.span)?;
                }
                StatementKind::Let { bindings, value } if index(bindings, value) => {
                    self.check_annotations(s, &[])?;
                    let (v, checked) = if let ValueKind::Call(c) = &value.kind {
                        if c.name == "checked" {
                            (self.r.positional(c, Some(1))?[0], true)
                        } else {
                            (value, false)
                        }
                    } else {
                        (value, false)
                    };
                    let expr = self.r.expr(v)?;
                    if checked {
                        self.emit(
                            Op::Guard,
                            vec![
                                Arg::Expr(expr.clone()),
                                Arg::Expr(expr.clone()),
                                Arg::Text("eq".into()),
                                Arg::Text(format!("checked {}", bindings[0].name)),
                                Arg::Text("checked".into()),
                            ],
                            s.span,
                        )?;
                    }
                    self.r.aliases.insert(bindings[0].name.into(), expr);
                    self.alias_spans.push((bindings[0].name.into(), s.span));
                }
                StatementKind::Let { bindings, value } => {
                    self.check_annotations(s, &["profile"])?;
                    let ValueKind::Call(c) = &value.kind else {
                        return Err(self
                            .r
                            .error(value.span, "Tensor results require an operation"));
                    };
                    let command = self.command(c, bindings)?;
                    for b in bindings {
                        let ty = match &b.ty {
                            Some(t) => self.ty(t)?,
                            None => self.infer(&command, b)?,
                        };
                        self.declare(b, ty, "value", None)?;
                    }
                    let target = bindings[0].name;
                    let metadata = self.meta("profile", target);
                    let annotation = self.annotation(s, "profile");
                    if grouped && (metadata.is_some() || annotation.is_some()) {
                        return Err(self
                            .r
                            .error(s.span, "Profile overrides cannot be nested inside a group"));
                    }
                    let disabled =
                        metadata.is_some_and(|v| matches!(v.kind, ValueKind::Name("none")));
                    let profiled = !grouped
                        && !disabled
                        && (self.auto_profile || metadata.is_some() || annotation.is_some());
                    if disabled && annotation.is_some() {
                        return Err(self.r.error(s.span, "Conflicting profile overrides"));
                    }
                    if profiled {
                        let mut args = schema::profile(&command, &self.names);
                        if let Some(v) = metadata {
                            self.overlay(
                                self.call(v, "profile")?,
                                &mut args,
                                Op::BeginProfileOperation,
                            )?;
                        }
                        if let Some(a) = annotation {
                            self.overlay(a, &mut args, Op::BeginProfileOperation)?;
                        }
                        self.emit(Op::BeginProfileOperation, args, s.span)?;
                    }
                    self.emit(command.op, command.args, s.span)?;
                    if profiled {
                        self.emit(Op::EndProfileOperation, vec![], s.span)?;
                    }
                    for b in bindings {
                        self.shape(b, false, false, s.span)?;
                    }
                }
                StatementKind::Require { lhs, rhs, relation } => {
                    if let ValueKind::Call(c) = &lhs.kind {
                        if c.name == "committed" {
                            self.check_annotations(s, &[])?;
                            if *relation != "eq" {
                                return Err(self
                                    .r
                                    .error(s.span, "Committed extent requires equality"));
                            }
                            let v = self.r.positional(c, Some(1))?[0];
                            let id = self.r.tensor(v)?;
                            let name = self.tensor_order[id as usize].clone();
                            let resource = self.meta("resource", &name).ok_or_else(|| self.r.error(c.span, "State requires resource(name=..., axis=..., encoding=...) metadata or @resource annotation"))?;
                            let a = self.r.fields(
                                self.call(resource, "resource")?,
                                &["name", "axis", "encoding"],
                            )?;
                            let args = vec![
                                Arg::Int(id),
                                Arg::Text(self.r.string(a[0])?),
                                Arg::Int(self.r.int(a[1])?),
                                Arg::Expr(self.r.expr(rhs)?),
                                self.r.arg("encoding", "encoding", a[2])?,
                            ];
                            self.emit(Op::Resource, args, s.span)?;
                            self.resource_targets.insert(name);
                            continue;
                        }
                    }
                    self.check_annotations(s, &["guard"])?;
                    let (lhs, rhs, relation) = if *relation == "ge" {
                        (rhs, lhs, "le")
                    } else {
                        (lhs, rhs, *relation)
                    };
                    let mut args = vec![
                        Arg::Expr(self.r.expr(lhs)?),
                        Arg::Expr(self.r.expr(rhs)?),
                        Arg::Text(relation.into()),
                        Arg::Text("require".into()),
                        Arg::Text("ordinary".into()),
                    ];
                    if let Some(a) = self.annotation(s, "guard") {
                        for f in &a.arguments {
                            if !matches!(f.name, Some("message" | "mode")) {
                                return Err(self
                                    .r
                                    .error(f.span, "@guard accepts message and mode"));
                            }
                        }
                        self.overlay(a, &mut args, Op::Guard)?;
                    }
                    self.emit(Op::Guard, args, s.span)?;
                }
                StatementKind::Shape { name, value, input } => {
                    self.check_annotations(s, &[])?;
                    let id =
                        self.r.tensors.get(*name).ok_or_else(|| {
                            self.r.error(s.span, format!("Unknown tensor {name}"))
                        })?;
                    self.emit(
                        if *input {
                            Op::InputShape
                        } else {
                            Op::ResultShape
                        },
                        vec![Arg::Int(*id), self.r.arg("exprs", "shape", value)?],
                        s.span,
                    )?;
                }
                StatementKind::Output(_) => self.check_annotations(s, &[])?,
                StatementKind::Call(c) => {
                    self.check_annotations(s, &[])?;
                    let cmd = self.command(c, &[])?;
                    self.emit(cmd.op, cmd.args, s.span)?;
                }
                StatementKind::Block { call, body } => {
                    self.check_annotations(s, &[])?;
                    match call.name {
                        "profile" => {
                            let a = self.r.fields(call, Op::BeginProfileOperation.fields())?;
                            let args = a
                                .into_iter()
                                .zip(Op::BeginProfileOperation.signature())
                                .zip(Op::BeginProfileOperation.fields())
                                .map(|((v, k), f)| self.r.arg(k, f, v))
                                .collect::<Result<_>>()?;
                            self.emit(Op::BeginProfileOperation, args, s.span)?;
                            self.statements(body, true)?;
                            self.emit(Op::EndProfileOperation, vec![], s.span)?;
                        }
                        "operation" => {
                            let a = self.r.fields(call, &["waits", "defines", "outputs"])?;
                            let waits = self.r.arg("texts", "waits", a[0])?;
                            let end = vec![
                                self.r.arg("texts", "defines", a[1])?,
                                self.r.arg("ids", "outputs", a[2])?,
                            ];
                            self.emit(Op::BeginOperation, vec![waits], s.span)?;
                            self.statements(body, true)?;
                            self.emit(Op::EndOperation, end, s.span)?;
                        }
                        _ => {
                            return Err(self
                                .r
                                .error(call.span, "Unknown block; expected profile or operation"))
                        }
                    }
                }
            }
        }
        Ok(())
    }
}

pub(super) fn compile<'a>(source: &'a str, doc: Document<'a>) -> Result<Plan> {
    let mut c = Compiler {
        r: Resolver::new(source),
        metadata: HashMap::new(),
        types: HashMap::new(),
        names: vec![],
        tensor_order: vec![],
        declarations: vec![],
        commands: vec![],
        spans: vec![],
        outputs: HashSet::new(),
        auto_profile: doc.auto_profile,
        profile_targets: HashSet::new(),
        resource_targets: HashSet::new(),
        alias_spans: Vec::new(),
    };
    let mut flat = vec![];
    walk(&doc.statements, &mut flat);
    let mut bindings = Vec::new();
    let mut all_names = HashSet::new();
    let mut symbols = Vec::new();
    for s in &flat {
        let bs: &[Binding<'a>] = match &s.kind {
            StatementKind::Declaration { binding, .. } => std::slice::from_ref(binding),
            StatementKind::Let {
                bindings: bs,
                value,
            } => {
                if index(bs, value) {
                    if !all_names.insert(bs[0].name) {
                        return Err(c.r.error(s.span, "Duplicate binding"));
                    }
                    continue;
                }
                c.profile_targets.insert(bs[0].name);
                bs
            }
            StatementKind::Dim { name, .. } => {
                if !all_names.insert(*name) {
                    return Err(c.r.error(s.span, "Duplicate binding"));
                }
                symbols.push((*name, s.span));
                continue;
            }
            StatementKind::Output(n) => {
                if !c.outputs.insert(*n) {
                    return Err(c.r.error(s.span, "Duplicate output"));
                }
                continue;
            }
            _ => continue,
        };
        for b in bs {
            if !all_names.insert(b.name) {
                return Err(c.r.error(b.span, format!("Duplicate tensor {}", b.name)));
            }
            bindings.push(b);
        }
    }
    if bindings.len() > MAX_VALUES {
        return Err(c.r.error(Span { start: 0, end: 0 }, "Too many tensors"));
    }
    for m in &doc.metadata {
        if !matches!(
            m.kind,
            "name" | "symbol" | "storage" | "declaration" | "profile" | "resource" | "asset"
        ) {
            return Err(c.r.error(m.span, format!("Unknown metadata {}", m.kind)));
        }
        if c.metadata
            .insert((m.kind.into(), m.target.into()), m.value.clone())
            .is_some()
        {
            return Err(c.r.error(m.span, "Duplicate metadata"));
        }
    }
    let order = if !doc.order_set {
        bindings.iter().map(|b| b.name).collect()
    } else {
        doc.order.clone()
    };
    if order.len() != bindings.len() {
        return Err(c.r.error(
            Span { start: 0, end: 0 },
            "Tensor order must list every tensor exactly once",
        ));
    }
    let tensor_names: HashSet<_> = bindings.iter().map(|b| b.name).collect();
    for name in order {
        let id = c.r.tensors.len() as i64;
        if !tensor_names.contains(name) || c.r.tensors.insert(name.into(), id).is_some() {
            return Err(c.r.error(
                Span { start: 0, end: 0 },
                "Invalid or duplicate tensor identity in order",
            ));
        }
        c.names.push(if let Some(v) = c.meta("name", name) {
            c.r.string(v)?
        } else {
            name.into()
        });
        c.declarations.push(None);
        c.tensor_order.push(name.into());
    }
    let mut used_ids = HashSet::new();
    for (name, span) in &symbols {
        if let Some(v) = c.meta("symbol", name) {
            let id =
                u32::try_from(c.r.int(v)?).map_err(|_| c.r.error(v.span, "Invalid symbol ID"))?;
            if !used_ids.insert(id) {
                return Err(c.r.error(*span, "Duplicate symbol ID"));
            }
            c.r.symbols.insert((*name).into(), id);
        }
    }
    let mut next = 0;
    for (name, _) in symbols {
        if !c.r.symbols.contains_key(name) {
            while used_ids.contains(&next) {
                next += 1;
            }
            c.r.symbols.insert(name.into(), next);
            used_ids.insert(next);
        }
    }
    for m in &doc.metadata {
        let valid = match m.kind {
            "asset" => {
                if let Arg::Data(Some(d)) = c.r.arg("data", "data", &m.value)? {
                    Arg::Data(Some(d.clone()))
                        .check("data", &HashMap::new(), &HashSet::new())
                        .map_err(|e| c.r.error(m.span, e))?;
                    c.r.assets.insert(m.target.into(), d);
                    true
                } else {
                    false
                }
            }
            "symbol" => c.r.symbols.contains_key(m.target),
            "profile" => c.profile_targets.contains(m.target),
            _ => c.r.tensors.contains_key(m.target),
        };
        if !valid {
            return Err(c.r.error(
                m.span,
                format!("Unknown or invalid metadata target {}", m.target),
            ));
        }
    }
    for n in &c.outputs {
        if !c.r.tensors.contains_key(*n) {
            return Err(c
                .r
                .error(Span { start: 0, end: 0 }, format!("Unknown output {n}")));
        }
    }
    // Resource annotations and footer metadata share one lowering path.
    let resources: Vec<_> = flat
        .iter()
        .filter_map(|s| match &s.kind {
            StatementKind::Declaration { binding, .. } => {
                s.attributes.iter().find(|a| a.name == "resource").map(|a| {
                    (
                        binding.name,
                        Value {
                            kind: ValueKind::Call(a.clone()),
                            span: a.span,
                            depth: 1,
                        },
                    )
                })
            }
            _ => None,
        })
        .collect();
    for (name, v) in &resources {
        if c.metadata
            .insert(("resource".into(), (*name).into()), v.clone())
            .is_some()
        {
            return Err(c.r.error(v.span, "Duplicate resource metadata"));
        }
    }
    c.statements(&doc.statements, false)?;
    for ((kind, target), v) in &c.metadata {
        if *kind == "resource" && !c.resource_targets.contains(target) {
            return Err(c.r.error(
                v.span,
                "Resource metadata requires a committed extent precondition",
            ));
        }
    }
    // Validate even unused index aliases against the same interval rules as
    // wire expressions. Runtime checked guards protect only their own trees.
    let mut ranges = HashMap::new();
    let mut protected = HashSet::new();
    for cmd in &c.commands {
        if cmd.op == Op::Symbol {
            ranges.insert(
                cmd.args[0].int() as u32,
                (cmd.args[2].int(), cmd.args[3].int()),
            );
        }
        if cmd.op == Op::Guard && cmd.args[4].text() == "checked" {
            for arg in &cmd.args[..2] {
                if let Arg::Expr(e) = arg {
                    e.checked_subexpressions(&mut protected, &mut 4096, 0)?;
                }
            }
        }
    }
    for (name, span) in &c.alias_spans {
        c.r.aliases[name]
            .bounds_in(&ranges, &mut 4096, 0, &protected, false)
            .map_err(|e| c.r.error(*span, e))?;
    }
    let mut commands = Vec::new();
    let mut spans = Vec::new();
    for d in c.declarations {
        let (cmd, span) = d.expect("every tensor binding is lowered");
        commands.push(cmd);
        spans.push(span);
    }
    commands.extend(c.commands);
    spans.extend(c.spans);
    let plan = Plan {
        format: "ynnpack-construction-plan".into(),
        version: doc.version,
        resource_contract: doc.resource,
        completion_contract: doc.completion,
        value_count: c.r.tensor_count(),
        commands,
    };
    plan.validate_with_location().map_err(|e| {
        c.r.error(
            e.command
                .and_then(|i| spans.get(i))
                .copied()
                .unwrap_or(Span { start: 0, end: 0 }),
            e.error,
        )
    })?;
    Ok(plan)
}
