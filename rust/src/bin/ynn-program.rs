// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
//! Source formatting and inspection only; never invokes target lowering.
use std::{
    io::{Read, Write},
    path::Path,
};
use ynnpack_lab::{compiler::Program, program_text, Error, Result};

fn main() {
    if let Err(error) = run() {
        eprintln!("{error}");
        std::process::exit(1);
    }
}
fn run() -> Result<()> {
    let args = std::env::args().skip(1).collect::<Vec<_>>();
    match args
        .iter()
        .map(String::as_str)
        .collect::<Vec<_>>()
        .as_slice()
    {
        ["from-json", input, output] => {
            let mut bytes = Vec::new();
            std::fs::File::open(input)?
                .take((128 << 20) + 1)
                .read_to_end(&mut bytes)?;
            if bytes.len() > 128 << 20 {
                return Err(Error::invalid("Projection exceeds 128 MiB"));
            }
            let program: Program = serde_json::from_slice(&bytes)?;
            drop(bytes);
            program_text::write(Path::new(output), &program)?;
            println!("{}", program_text::semantic_digest(&program)?);
            Ok(())
        }
        ["to-json", input] => {
            serde_json::to_writer(
                std::io::stdout().lock(),
                &program_text::read(Path::new(input))?,
            )?;
            std::io::stdout().write_all(b"\n")?;
            Ok(())
        }
        ["inspect", input] => {
            println!("{}", program_text::inspect(Path::new(input))?);
            Ok(())
        }
        _ => Err(Error::invalid(
            "usage: ynn-program from-json INPUT OUTPUT | to-json INPUT | inspect INPUT",
        )),
    }
}
