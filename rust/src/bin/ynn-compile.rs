// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
use std::path::PathBuf;
use ynnpack_lab::{
    compiler::{compile, Program},
    Error, ErrorKind, Result,
};
fn main() {
    if let Err(e) = run() {
        eprintln!("{e}");
        std::process::exit(1);
    }
}
fn run() -> Result<()> {
    let args = std::env::args().skip(1).collect::<Vec<_>>();
    if args.len() != 4 || args[0] != "--request" || args[2] != "--output" {
        return Err(Error {
            kind: ErrorKind::Invalid,
            message: "usage: ynn-compile --request FILE --output NEW_DIRECTORY".into(),
        });
    }
    use std::io::Read;
    let mut data = Vec::new();
    std::fs::File::open(&args[1])?
        .take(128 * 1024 * 1024 + 1)
        .read_to_end(&mut data)?;
    if data.len() > 128 * 1024 * 1024 {
        return Err(Error::invalid("Compiler request exceeds 128 MiB"));
    }
    // JSON remains an explicit diagnostic/frontend bridge, never a runner input.
    let request: Program = if data.iter().find(|b| !b.is_ascii_whitespace()) == Some(&b'{') {
        serde_json::from_slice(&data)?
    } else {
        ynnpack_lab::program_text::read(std::path::Path::new(&args[1]))?
    };
    let result = compile(&request)?;
    result.write(&PathBuf::from(&args[3]))?;
    println!("{}", serde_json::to_string(&result.report)?);
    Ok(())
}
