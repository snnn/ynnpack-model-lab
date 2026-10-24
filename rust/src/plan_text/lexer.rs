// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
use super::{diagnostic, Span};
use crate::Result;

#[derive(Clone, Copy, Debug, PartialEq)]
pub(crate) enum Kind<'a> {
    Ident(&'a str),
    Number(&'a str),
    String(&'a str),
    Tensor(&'a str),
    Symbol(&'a str),
    Punct(u8),
    FloorDiv,
    Range,
    Le,
    Ge,
    Eq,
    And,
    Eof,
}
#[derive(Clone, Copy, Debug)]
pub(crate) struct Token<'a> {
    pub kind: Kind<'a>,
    pub span: Span,
}
pub(crate) struct Lexer<'a> {
    source: &'a str,
    offset: usize,
}
impl<'a> Lexer<'a> {
    pub fn new(source: &'a str) -> Self {
        Self { source, offset: 0 }
    }
    pub fn next(&mut self) -> Result<Token<'a>> {
        let b = self.source.as_bytes();
        loop {
            while b.get(self.offset).is_some_and(u8::is_ascii_whitespace) {
                self.offset += 1;
            }
            let tail = &self.source[self.offset..];
            if tail.starts_with('#') {
                self.offset += tail.find('\n').unwrap_or(tail.len());
            } else if let Some(rest) = tail.strip_prefix("/*") {
                let Some(end) = rest.find("*/") else {
                    return Err(diagnostic(
                        self.source,
                        Span {
                            start: self.offset,
                            end: b.len(),
                        },
                        "Unterminated block comment",
                    ));
                };
                self.offset += end + 4;
            } else {
                break;
            }
        }
        let start = self.offset;
        let span = Span { start, end: start };
        let Some(&c) = b.get(start) else {
            return Ok(Token {
                kind: Kind::Eof,
                span,
            });
        };
        for (text, kind) in [
            ("..=", Kind::Range),
            ("//", Kind::FloorDiv),
            ("<=", Kind::Le),
            (">=", Kind::Ge),
            ("==", Kind::Eq),
            ("&&", Kind::And),
        ] {
            if self.source[start..].starts_with(text) {
                self.offset += text.len();
                return Ok(Token {
                    kind,
                    span: Span {
                        start,
                        end: self.offset,
                    },
                });
            }
        }
        let kind = match c {
            b'(' | b')' | b'[' | b']' | b'{' | b'}' | b',' | b';' | b'=' | b':' | b'@' | b'+'
            | b'-' | b'*' | b'<' | b'>' | b'?' => {
                self.offset += 1;
                Kind::Punct(c)
            }
            b'"' => {
                self.offset += 1;
                loop {
                    match b.get(self.offset) {
                        None => return Err(diagnostic(self.source, span, "Unterminated string")),
                        Some(b'"') => {
                            self.offset += 1;
                            break;
                        }
                        Some(b'\\') => {
                            self.offset += 1;
                            if self.offset < b.len() {
                                self.offset += 1;
                            }
                        }
                        _ => self.offset += 1,
                    }
                }
                Kind::String(&self.source[start..self.offset])
            }
            b'%' | b'$' | b'_' | b'a'..=b'z' | b'A'..=b'Z' => {
                let prefix = c == b'%' || c == b'$';
                let ns = start + usize::from(prefix);
                if !b
                    .get(ns)
                    .is_some_and(|c| c.is_ascii_alphabetic() || *c == b'_')
                {
                    return Err(diagnostic(self.source, span, "Expected a reference name"));
                }
                self.offset = ns + 1;
                while b
                    .get(self.offset)
                    .is_some_and(|c| c.is_ascii_alphanumeric() || *c == b'_')
                {
                    self.offset += 1;
                }
                if self.offset - ns > 256 {
                    return Err(diagnostic(
                        self.source,
                        span,
                        "Identifier exceeds 256 bytes",
                    ));
                }
                let name = &self.source[ns..self.offset];
                match c {
                    b'%' => Kind::Tensor(name),
                    b'$' => Kind::Symbol(name),
                    _ => Kind::Ident(name),
                }
            }
            b'0'..=b'9' => {
                while b.get(self.offset).is_some_and(u8::is_ascii_digit) {
                    self.offset += 1;
                }
                if b.get(self.offset) == Some(&b'.') && b.get(self.offset + 1) != Some(&b'.') {
                    self.offset += 1;
                    while b.get(self.offset).is_some_and(u8::is_ascii_digit) {
                        self.offset += 1;
                    }
                }
                if matches!(b.get(self.offset), Some(b'e' | b'E')) {
                    self.offset += 1;
                    if matches!(b.get(self.offset), Some(b'+' | b'-')) {
                        self.offset += 1;
                    }
                    while b.get(self.offset).is_some_and(u8::is_ascii_digit) {
                        self.offset += 1;
                    }
                }
                Kind::Number(&self.source[start..self.offset])
            }
            b'/' => {
                return Err(diagnostic(
                    self.source,
                    span,
                    "Use // or floor_div(...) for integer division",
                ))
            }
            _ => return Err(diagnostic(self.source, span, "Unexpected character")),
        };
        Ok(Token {
            kind,
            span: Span {
                start,
                end: self.offset,
            },
        })
    }
}
