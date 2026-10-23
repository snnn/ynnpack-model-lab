// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
use std::{env, fs, path::PathBuf};
fn main() {
    let sources = ["common", "linear", "attention", "decode"]
        .map(|s| format!("src/compiler/lower/rules/{s}.isle"));
    println!("cargo:rerun-if-changed=build.rs");
    for source in &sources {
        println!("cargo:rerun-if-changed={source}");
    }
    let options = cranelift_isle::codegen::CodegenOptions {
        exclude_global_allow_pragmas: true,
        ..Default::default()
    };
    let code =
        cranelift_isle::compile::from_files(&sources, &options).unwrap_or_else(|e| panic!("{e}"));
    println!("cargo:rerun-if-changed=src/compiler/lower/rules/regions.isle");
    let regions =
        cranelift_isle::compile::from_files(["src/compiler/lower/rules/regions.isle"], &options)
            .unwrap_or_else(|e| panic!("{e}"));
    fs::write(
        PathBuf::from(env::var_os("OUT_DIR").unwrap()).join("regions.rs"),
        regions,
    )
    .unwrap();
    fs::write(
        PathBuf::from(env::var_os("OUT_DIR").unwrap()).join("lower.rs"),
        code,
    )
    .unwrap();
}
