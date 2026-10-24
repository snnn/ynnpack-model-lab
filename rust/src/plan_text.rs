// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
//! Handwritten text frontend for the existing construction plan contract.
//! Parsing and printing never call the native backend or map model weights.
use crate::plan::{Plan, ValidatedPlan, MAX_FILE};
use crate::{Error, Result};

mod compile;
mod functions;
mod intern;
#[cfg(any(test, feature = "diagnostic-tools"))]
mod compare;
#[cfg(any(test, feature = "diagnostic-tools"))]
mod cpp;
#[cfg(any(test, feature = "diagnostic-tools"))]
pub use compare::compare;
pub(crate) use intern::intern;
pub(crate) mod lexer;
mod parser;
mod printer;
mod resolve;
mod schema;
#[cfg(test)]
mod tests;

#[derive(Clone, Copy, Debug)]
pub(crate) struct Span {
    pub(crate) start: usize,
    pub(crate) end: usize,
}

pub(crate) fn diagnostic(source: &str, span: Span, message: impl std::fmt::Display) -> Error {
    // Synthetic invocations used to validate a closed function can carry spans
    // from a temporary document. Never let an error-reporting path panic.
    let mut offset = span.start.min(source.len());
    while !source.is_char_boundary(offset) { offset -= 1; }
    let prefix = &source[..offset];
    let line = prefix.bytes().filter(|&b| b == b'\n').count() + 1;
    let start = prefix.rfind('\n').map_or(0, |p| p + 1);
    let column = source[start..offset].chars().count() + 1;
    // Keep diagnostics bounded even for a large generated line/string.
    let excerpt: String = source[start..]
        .lines()
        .next()
        .unwrap_or("")
        .chars()
        .take(160)
        .collect();
    let marker = if column <= 160 {
        format!("\n{}^", " ".repeat(column - 1))
    } else {
        String::new()
    };
    Error::invalid(format!("{line}:{column}: {message}\n{excerpt}{marker}"))
}

/// Parse directly into the construction model; there is no graph JSON decoder.
pub(crate) fn parse(source: &str) -> Result<Plan> {
    if source.len() as u64 > MAX_FILE {
        return Err(Error::invalid("Graph source exceeds size limit"));
    }
    parser::parse(source)
}

/// Validate source without creating a native graph or mapping constants.
pub fn check(source: &str) -> Result<()> {
    ValidatedPlan::from_bytes(source.as_bytes()).map(|_| ())
}

/// Canonicalize source. Comments and original whitespace are intentionally lost.
pub fn format(source: &str) -> Result<String> {
    let plan = parse(source)?;
    let doc = parser::document(source)?;
    let formatted = if doc.functions.is_empty() {
        printer::print(&plan)?
    } else {
        functions::format(source, &doc)?
    };
    if plan != parse(&formatted)? {
        return Err(Error::invalid(
            "Text printer cannot preserve this construction stream exactly",
        ));
    }
    Ok(formatted)
}

/// Read-only diagnostic report. Reports are not accepted as executable graphs.
#[cfg(any(test, feature = "diagnostic-tools"))]
pub fn inspect(source: &str) -> Result<String> {
    let plan = parse(source)?;
    let doc = parser::document(source)?;
    let constants: Vec<_> = plan
        .commands
        .iter()
        .flat_map(|c| &c.args)
        .filter_map(|a| {
            if let crate::plan::Arg::Data(Some(d)) = a {
                Some(d)
            } else {
                None
            }
        })
        .collect();
    Ok(serde_json::to_string(&serde_json::json!({
        "report": "ynn-plan-inspection", "version": 1,
        "value_count": plan.value_count, "commands": plan.commands,
        "constants": constants,
        "functions": functions::inspect(&doc),
    }))? + "\n")
}

/// Standalone CLI shared with the Cargo binary. Output files must be new.
#[cfg(feature = "diagnostic-tools")]
pub fn main(args: &[String]) -> Result<()> {
    use std::io::{Read, Write};
    if args.len()==3 && args[0]=="compare" {
        let left=std::fs::read_to_string(&args[1])?;
        let right=std::fs::read_to_string(&args[2])?;
        println!("{}",serde_json::to_string_pretty(&compare(&left,&right)?)?);
        return Ok(());
    }
    let usage = "ynn-plan compare LEFT.ynn RIGHT.ynn\nynn-plan check INPUT.ynn\nynn-plan format INPUT.ynn [-o NEW.ynn]\nynn-plan expand INPUT.ynn [-o NEW.ynn]\nynn-plan inspect INPUT.ynn [-o REPORT.json]\nynn-plan cpp-static INPUT.ynn [-o STATEMENTS.inc]\nUse - for stdin. Formatting discards comments and does not update model.json hashes.";
    if args.len() == 1 && matches!(args[0].as_str(), "--help" | "-h") {
        println!("{usage}");
        return Ok(());
    }
    if !(args.len() == 2 || args.len() == 4 && args[2] == "-o")
        || !matches!(args[0].as_str(), "check" | "format" | "inspect" | "expand" | "cpp-static")
        || args[0] == "check" && args.len() != 2
    {
        return Err(Error::invalid(usage));
    }
    let mut bytes = Vec::new();
    if args[1] == "-" {
        std::io::stdin()
            .lock()
            .take(MAX_FILE + 1)
            .read_to_end(&mut bytes)?;
    } else {
        std::fs::File::open(&args[1])?
            .take(MAX_FILE + 1)
            .read_to_end(&mut bytes)?;
    }
    if bytes.len() as u64 > MAX_FILE {
        return Err(Error::invalid("Graph file exceeds size limit"));
    }
    let result = (|| {
        let source =
            std::str::from_utf8(&bytes).map_err(|_| Error::invalid("Source must be UTF-8"))?;
        match args[0].as_str() {
            "inspect" => inspect(source).map(String::into_bytes),
            "cpp-static" => cpp::statements(source).map(String::into_bytes),
            "format" => format(source).map(String::into_bytes),
            "expand" => printer::print(&parse(source)?).map(String::into_bytes),
            _ => check(source).map(|_| Vec::new()),
        }
    })()
    .map_err(|e: Error| Error::invalid(format!("{}:{e}", args[1])))?;
    if args[0] == "check" {
        println!("Validated {}", args[1]);
    } else if args.len() == 4 {
        std::fs::OpenOptions::new()
            .write(true)
            .create_new(true)
            .open(&args[3])?
            .write_all(&result)?;
    } else {
        std::io::stdout().lock().write_all(&result)?;
    }
    Ok(())
}
