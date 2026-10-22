// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
//! Bounded handwritten syntax parser. Tensor declarations are resolved in a second pass.
use super::lexer::{Kind, Lexer, Token};
use super::{diagnostic, Span};
use crate::plan::{Plan, MAX_COMMANDS, MAX_VALUES};
use crate::Result;
use std::collections::VecDeque;

#[derive(Clone)]
pub(super) struct Value<'a> {
    pub kind: ValueKind<'a>,
    pub span: Span,
    pub depth: usize,
}
#[derive(Clone)]
pub(super) enum ValueKind<'a> {
    Name(&'a str),
    Number(&'a str),
    String(String),
    Tensor(&'a str),
    Symbol(&'a str),
    List(Vec<Value<'a>>),
    Call(Call<'a>),
    Unary(u8, Box<Value<'a>>),
    Binary(&'static str, Box<Value<'a>>, Box<Value<'a>>),
    Unknown,
}
#[derive(Clone)]
pub(super) struct Argument<'a> {
    pub name: Option<&'a str>,
    pub span: Span,
    pub value: Value<'a>,
}
#[derive(Clone)]
pub(super) struct Call<'a> {
    pub name: &'a str,
    pub arguments: Vec<Argument<'a>>,
    pub span: Span,
}
#[derive(Clone)]
pub(super) struct Type<'a> {
    pub name: &'a str,
    pub dims: Vec<Value<'a>>,
    pub storage: bool,
    pub owner: bool,
    pub literal: bool,
    pub span: Span,
}
#[derive(Clone)]
pub(super) struct Binding<'a> {
    pub name: &'a str,
    pub ty: Option<Type<'a>>,
    pub default: Option<Value<'a>>,
    pub span: Span,
}
#[derive(Clone)]
pub(super) struct Statement<'a> {
    pub kind: StatementKind<'a>,
    pub attributes: Vec<Call<'a>>,
    pub span: Span,
}
#[derive(Clone)]
pub(super) enum StatementKind<'a> {
    Invoke { call: Call<'a>, outputs: Vec<&'a str> },
    Return(Vec<&'a str>),
    Declaration {
        role: &'a str,
        binding: Binding<'a>,
        data: Option<Value<'a>>,
    },
    Let {
        bindings: Vec<Binding<'a>>,
        value: Value<'a>,
    },
    Dim {
        name: &'a str,
        source: Value<'a>,
        lower: Value<'a>,
        upper: Value<'a>,
    },
    Require {
        lhs: Value<'a>,
        rhs: Value<'a>,
        relation: &'static str,
    },
    Output(&'a str),
    Shape {
        name: &'a str,
        value: Value<'a>,
        input: bool,
    },
    Block {
        call: Call<'a>,
        body: Vec<Statement<'a>>,
    },
    Call(Call<'a>),
}
pub(super) struct Metadata<'a> {
    pub kind: &'a str,
    pub target: &'a str,
    pub value: Value<'a>,
    pub span: Span,
}
pub(super) struct Document<'a> {
    pub functions: Vec<Function<'a>>,
    pub version: u32,
    pub resource: u32,
    pub completion: u32,
    pub auto_profile: bool,
    pub statements: Vec<Statement<'a>>,
    pub order: Vec<&'a str>,
    pub order_set: bool,
    pub metadata: Vec<Metadata<'a>>,
}
pub(super) struct Function<'a> {
    pub name: &'a str,
    pub parameters: Vec<Binding<'a>>,
    pub results: Vec<Binding<'a>>,
    pub statements: Vec<Statement<'a>>,
    pub span: Span,
}
struct Parser<'a> {
    source: &'a str,
    lexer: Lexer<'a>,
    lookahead: VecDeque<Token<'a>>,
    nodes: usize,
    statements: usize,
}
impl<'a> Parser<'a> {
    fn peek(&mut self, n: usize) -> Result<Token<'a>> {
        while self.lookahead.len() <= n {
            self.lookahead.push_back(self.lexer.next()?);
        }
        Ok(self.lookahead[n])
    }
    fn take(&mut self) -> Result<Token<'a>> {
        self.peek(0)?;
        Ok(self.lookahead.pop_front().unwrap())
    }
    fn expect(&mut self, kind: Kind<'a>) -> Result<Token<'a>> {
        let t = self.take()?;
        if t.kind != kind {
            return Err(diagnostic(
                self.source,
                t.span,
                format!("Expected {kind:?}"),
            ));
        }
        Ok(t)
    }
    fn eat(&mut self, kind: Kind<'a>) -> Result<bool> {
        if self.peek(0)?.kind == kind {
            self.take()?;
            Ok(true)
        } else {
            Ok(false)
        }
    }
    fn name(&mut self) -> Result<(&'a str, Span)> {
        let t = self.take()?;
        match t.kind {
            Kind::Ident(n) | Kind::Tensor(n) | Kind::Symbol(n) => Ok((n, t.span)),
            _ => Err(diagnostic(self.source, t.span, "Expected a name")),
        }
    }
    fn number(&mut self) -> Result<u32> {
        let t = self.take()?;
        if let Kind::Number(n) = t.kind {
            if let Ok(n) = n.parse() {
                return Ok(n);
            }
        }
        Err(diagnostic(
            self.source,
            t.span,
            "Expected an unsigned 32-bit integer",
        ))
    }
    fn value(&self, kind: ValueKind<'a>, span: Span) -> Result<Value<'a>> {
        let depth = 1 + match &kind {
            ValueKind::Unary(_, x) => x.depth,
            ValueKind::Binary(_, x, y) => x.depth.max(y.depth),
            ValueKind::List(xs) => xs.iter().map(|v| v.depth).max().unwrap_or(0),
            ValueKind::Call(c) => c.arguments.iter().map(|a| a.value.depth).max().unwrap_or(0),
            _ => 0,
        };
        if depth > 64 {
            return Err(diagnostic(
                self.source,
                span,
                "Expression nesting limit exceeded",
            ));
        }
        Ok(Value { kind, span, depth })
    }
    fn expression(&mut self, depth: usize, precedence: u8) -> Result<Value<'a>> {
        let t = self.peek(0)?;
        self.nodes += 1;
        if depth > 72 || self.nodes > 4_000_000 {
            return Err(diagnostic(
                self.source,
                t.span,
                "Syntax nesting/node limit exceeded",
            ));
        }
        let mut lhs = if matches!(t.kind, Kind::Punct(b'+' | b'-')) {
            self.take()?;
            let Kind::Punct(sign) = t.kind else {
                unreachable!()
            };
            let value = self.expression(depth + 1, 30)?;
            let span = Span {
                start: t.span.start,
                end: value.span.end,
            };
            self.value(ValueKind::Unary(sign, Box::new(value)), span)?
        } else if self.eat(Kind::Punct(b'('))? {
            let value = self.expression(depth + 1, 0)?;
            self.expect(Kind::Punct(b')'))?;
            value
        } else if matches!(t.kind, Kind::Ident(_)) && self.peek(1)?.kind == Kind::Punct(b'(') {
            let call = self.call(depth + 1)?;
            let span = call.span;
            self.value(ValueKind::Call(call), span)?
        } else {
            self.take()?;
            let kind = match t.kind {
                Kind::Ident(n) => ValueKind::Name(n),
                Kind::Number(n) => ValueKind::Number(n),
                Kind::Tensor(n) => ValueKind::Tensor(n),
                Kind::Symbol(n) => ValueKind::Symbol(n),
                Kind::String(s) => ValueKind::String(
                    serde_json::from_str(s).map_err(|e| diagnostic(self.source, t.span, e))?,
                ),
                Kind::Punct(b'?') => ValueKind::Unknown,
                Kind::Punct(b'[') => {
                    let mut values = Vec::new();
                    while self.peek(0)?.kind != Kind::Punct(b']') {
                        if values.len() == 1024 {
                            return Err(diagnostic(
                                self.source,
                                t.span,
                                "List exceeds 1024 elements",
                            ));
                        }
                        values.push(self.expression(depth + 1, 0)?);
                        if !self.eat(Kind::Punct(b','))? {
                            break;
                        }
                    }
                    self.expect(Kind::Punct(b']'))?;
                    ValueKind::List(values)
                }
                _ => return Err(diagnostic(self.source, t.span, "Expected a value")),
            };
            self.value(kind, t.span)?
        };
        let mut chain = 0;
        loop {
            let (op, p) = match self.peek(0)?.kind {
                Kind::Punct(b'+') => ("add", 10),
                Kind::Punct(b'-') => ("sub", 10),
                Kind::Punct(b'*') => ("mul", 20),
                Kind::FloorDiv => ("floor_div", 20),
                _ => break,
            };
            if p < precedence {
                break;
            }
            chain += 1;
            if depth + chain > 64 {
                return Err(diagnostic(
                    self.source,
                    lhs.span,
                    "Expression nesting limit exceeded",
                ));
            }
            self.take()?;
            let rhs = self.expression(depth + 1, p + 1)?;
            let span = Span {
                start: lhs.span.start,
                end: rhs.span.end,
            };
            lhs = self.value(ValueKind::Binary(op, Box::new(lhs), Box::new(rhs)), span)?;
            // Flat infix chains also build nested trees. Bound them explicitly.
            if self.nodes > 4_000_000 {
                return Err(diagnostic(self.source, span, "Syntax node limit exceeded"));
            }
        }
        Ok(lhs)
    }
    fn call(&mut self, depth: usize) -> Result<Call<'a>> {
        let (name, span) = self.name()?;
        self.expect(Kind::Punct(b'('))?;
        let mut arguments = Vec::new();
        while self.peek(0)?.kind != Kind::Punct(b')') {
            if arguments.len() == 1024 {
                return Err(diagnostic(self.source, span, "Call exceeds 1024 arguments"));
            }
            let first = self.peek(0)?;
            let field = if let Kind::Ident(n) = first.kind {
                if self.peek(1)?.kind == Kind::Punct(b'=') {
                    self.take()?;
                    self.take()?;
                    Some(n)
                } else {
                    None
                }
            } else {
                None
            };
            arguments.push(Argument {
                name: field,
                span: first.span,
                value: self.expression(depth + 1, 0)?,
            });
            if !self.eat(Kind::Punct(b','))? {
                break;
            }
        }
        let end = self.expect(Kind::Punct(b')'))?.span.end;
        Ok(Call {
            name,
            arguments,
            span: Span {
                start: span.start,
                end,
            },
        })
    }
    fn ty(&mut self) -> Result<Type<'a>> {
        let (mut name, span) = self.name()?;
        let owner = name == "owner";
        let storage = name == "storage" || owner;
        if storage {
            self.expect(Kind::Punct(b'<'))?;
            name = self.name()?.0;
        }
        if storage && name == "index" {
            return Err(diagnostic(
                self.source,
                span,
                "index cannot be a storage template",
            ));
        }
        let literal = !storage && matches!(name, "float" | "int" | "size" | "ints" | "sizes" | "floats" | "encoding" | "bool");
        let dims = if name == "index" || literal {
            Vec::new()
        } else {
            let v = self.expression(0, 30)?;
            let ValueKind::List(xs) = v.kind else {
                return Err(diagnostic(self.source, v.span, "Expected a tensor shape"));
            };
            xs
        };
        if storage {
            self.expect(Kind::Punct(b'>'))?;
        }
        Ok(Type {
            name,
            dims,
            storage,
            owner,
            literal,
            span,
        })
    }
    fn binding(&mut self) -> Result<Binding<'a>> {
        let (name, span) = self.name()?;
        if matches!(name, "none" | "true" | "false") {
            return Err(diagnostic(
                self.source,
                span,
                "Reserved literal cannot be a binding name",
            ));
        }
        let ty = if self.eat(Kind::Punct(b':'))? {
            Some(self.ty()?)
        } else {
            None
        };
        Ok(Binding { name, ty, default: None, span })
    }
    fn names(&mut self) -> Result<Vec<&'a str>> {
        self.expect(Kind::Punct(b'('))?;
        let mut names = Vec::new();
        while self.peek(0)?.kind != Kind::Punct(b')') {
            if names.len() >= 1024 { return Err(diagnostic(self.source, self.peek(0)?.span, "Too many results")); }
            names.push(self.name()?.0);
            if !self.eat(Kind::Punct(b','))? { break; }
        }
        self.expect(Kind::Punct(b')'))?;
        Ok(names)
    }
    fn parameters(&mut self) -> Result<Vec<Binding<'a>>> {
        self.expect(Kind::Punct(b'('))?;
        let mut bindings = Vec::new();
        while self.peek(0)?.kind != Kind::Punct(b')') {
            if bindings.len() >= 1024 { return Err(diagnostic(self.source, self.peek(0)?.span, "Too many parameters")); }
            let mut binding = self.binding()?;
            if binding.ty.is_none() { return Err(diagnostic(self.source, binding.span, "Function parameters and results require types")); }
            if self.eat(Kind::Punct(b'='))? { binding.default = Some(self.expression(0, 0)?); }
            bindings.push(binding);
            if !self.eat(Kind::Punct(b','))? { break; }
        }
        self.expect(Kind::Punct(b')'))?;
        Ok(bindings)
    }
    fn function(&mut self) -> Result<Function<'a>> {
        let (name, span) = self.name()?;
        let parameters = self.parameters()?;
        self.expect(Kind::Punct(b'-'))?;
        self.expect(Kind::Punct(b'>'))?;
        let results = self.parameters()?;
        self.expect(Kind::Punct(b'{'))?;
        let mut statements = Vec::new();
        while self.peek(0)?.kind != Kind::Punct(b'}') { statements.push(self.statement(1)?); }
        self.take()?;
        Ok(Function { name, parameters, results, statements, span })
    }
    fn statement(&mut self, depth: usize) -> Result<Statement<'a>> {
        let span = self.peek(0)?.span;
        self.statements += 1;
        if depth > 64 || self.statements > MAX_COMMANDS {
            return Err(diagnostic(
                self.source,
                span,
                "Statement nesting/count limit exceeded",
            ));
        }
        let mut attributes = Vec::new();
        while self.eat(Kind::Punct(b'@'))? {
            if attributes.len() == 16 {
                return Err(diagnostic(self.source, span, "Too many annotations"));
            }
            attributes.push(self.call(0)?);
        }
        let (word, _) = self.name()?;
        let kind = match word {
            "invoke" => {
                let call = self.call(0)?;
                self.expect(Kind::Punct(b'-'))?;
                self.expect(Kind::Punct(b'>'))?;
                StatementKind::Invoke { call, outputs: self.names()? }
            }
            "return" => StatementKind::Return(self.names()?),
            "input" | "weight" | "value" | "state" => {
                let binding = self.binding()?;
                if binding.ty.is_none() {
                    return Err(diagnostic(
                        self.source,
                        binding.span,
                        "Declaration requires a type",
                    ));
                }
                let data = if self.eat(Kind::Punct(b'='))? {
                    Some(self.expression(0, 0)?)
                } else {
                    None
                };
                StatementKind::Declaration {
                    role: word,
                    binding,
                    data,
                }
            }
            "let" => {
                let tuple = self.eat(Kind::Punct(b'('))?;
                let mut bindings = vec![self.binding()?];
                if tuple {
                    while self.eat(Kind::Punct(b','))? {
                        if self.peek(0)?.kind == Kind::Punct(b')') {
                            break;
                        }
                        if bindings.len() == 1024 {
                            return Err(diagnostic(self.source, span, "Too many results"));
                        }
                        bindings.push(self.binding()?);
                    }
                    self.expect(Kind::Punct(b')'))?;
                }
                self.expect(Kind::Punct(b'='))?;
                StatementKind::Let {
                    bindings,
                    value: self.expression(0, 0)?,
                }
            }
            "dim" => {
                let name = self.name()?.0;
                self.expect(Kind::Punct(b'='))?;
                let source = self.expression(0, 0)?;
                self.expect(Kind::Ident("in"))?;
                let lower = self.expression(0, 0)?;
                self.expect(Kind::Range)?;
                let upper = self.expression(0, 0)?;
                StatementKind::Dim {
                    name,
                    source,
                    lower,
                    upper,
                }
            }
            "require" => {
                let lhs = self.expression(0, 0)?;
                let t = self.take()?;
                let relation = match t.kind {
                    Kind::Le => "le",
                    Kind::Eq => "eq",
                    Kind::Ge => "ge",
                    _ => return Err(diagnostic(self.source, t.span, "Expected <=, >= or ==")),
                };
                let rhs = self.expression(0, 0)?;
                StatementKind::Require { lhs, rhs, relation }
            }
            "output" => StatementKind::Output(self.name()?.0),
            "shape" | "input_shape" => {
                let name = self.name()?.0;
                self.expect(Kind::Punct(b'='))?;
                StatementKind::Shape {
                    name,
                    value: self.expression(0, 0)?,
                    input: word == "input_shape",
                }
            }
            _ => {
                // The operation name was consumed; put it back for the common call parser.
                self.lookahead.push_front(Token {
                    kind: Kind::Ident(word),
                    span,
                });
                let call = self.call(0)?;
                if self.eat(Kind::Punct(b'{'))? {
                    let mut body = Vec::new();
                    while self.peek(0)?.kind != Kind::Punct(b'}') {
                        body.push(self.statement(depth + 1)?);
                    }
                    self.take()?;
                    return Ok(Statement {
                        kind: StatementKind::Block { call, body },
                        attributes,
                        span,
                    });
                }
                StatementKind::Call(call)
            }
        };
        self.expect(Kind::Punct(b';'))?;
        Ok(Statement {
            kind,
            attributes,
            span,
        })
    }
    fn metadata(&mut self, doc: &mut Document<'a>) -> Result<()> {
        self.expect(Kind::Punct(b'{'))?;
        while self.peek(0)?.kind != Kind::Punct(b'}') {
            let (kind, span) = self.name()?;
            if kind == "order" {
                if doc.order_set {
                    return Err(diagnostic(self.source, span, "Duplicate tensor order"));
                }
                doc.order_set = true;
                self.expect(Kind::Punct(b'['))?;
                while self.peek(0)?.kind != Kind::Punct(b']') {
                    if doc.order.len() == MAX_VALUES {
                        return Err(diagnostic(self.source, span, "Too many tensor identities"));
                    }
                    doc.order.push(self.name()?.0);
                    if !self.eat(Kind::Punct(b','))? {
                        break;
                    }
                }
                self.expect(Kind::Punct(b']'))?;
            } else {
                if doc.metadata.len() >= MAX_COMMANDS {
                    return Err(diagnostic(self.source, span, "Metadata limit exceeded"));
                }
                let target = self.name()?.0;
                self.expect(Kind::Punct(b'='))?;
                doc.metadata.push(Metadata {
                    kind,
                    target,
                    value: self.expression(0, 0)?,
                    span,
                });
            }
            self.expect(Kind::Punct(b';'))?;
        }
        self.take()?;
        Ok(())
    }
}
pub(super) fn document(source: &str) -> Result<Document<'_>> {
    let mut p = Parser {
        source,
        lexer: Lexer::new(source),
        lookahead: VecDeque::new(),
        nodes: 0,
        statements: 0,
    };
    p.expect(Kind::Ident("ynn"))?;
    let version = p.number()?;
    p.expect(Kind::Ident("resource_contract"))?;
    p.expect(Kind::Punct(b'='))?;
    let resource = p.number()?;
    p.expect(Kind::Ident("completion_contract"))?;
    p.expect(Kind::Punct(b'='))?;
    let completion = p.number()?;
    let auto_profile = if p.eat(Kind::Ident("profiling"))? {
        p.expect(Kind::Punct(b'='))?;
        let (mode, span) = p.name()?;
        match mode {
            "auto" => true,
            "explicit" => false,
            _ => {
                return Err(diagnostic(
                    source,
                    span,
                    "Expected auto or explicit profiling",
                ))
            }
        }
    } else {
        false
    };
    p.expect(Kind::Punct(b'{'))?;
    let mut doc = Document {
        functions: Vec::new(),
        version,
        resource,
        completion,
        auto_profile,
        statements: Vec::new(),
        order: Vec::new(),
        order_set: false,
        metadata: Vec::new(),
    };
    while p.peek(0)?.kind != Kind::Punct(b'}') {
        if p.eat(Kind::Ident("metadata"))? {
            p.metadata(&mut doc)?;
        } else if p.eat(Kind::Ident("fn"))? {
            if doc.functions.len() >= 1024 { return Err(diagnostic(source, p.peek(0)?.span, "Too many functions")); }
            doc.functions.push(p.function()?);
        } else {
            doc.statements.push(p.statement(0)?);
        }
    }
    p.take()?;
    p.expect(Kind::Eof)?;
    Ok(doc)
}
pub(super) fn parse(source: &str) -> Result<Plan> {
    let doc = document(source)?;
    if doc.functions.is_empty() {
        super::compile::compile(source, doc)
    } else {
        let expanded = super::functions::expand(source, &doc)?;
        super::compile::compile(&expanded, document(&expanded)?)
    }
}
