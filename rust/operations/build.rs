// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
fn main() {
    println!("cargo:rerun-if-changed=src/dispatch.isle");
    let options = cranelift_isle::codegen::CodegenOptions {
        exclude_global_allow_pragmas: true,
        ..Default::default()
    };
    let code = cranelift_isle::compile::from_files(["src/dispatch.isle"], &options)
        .unwrap_or_else(|e| panic!("{e}"));
    std::fs::write(
        std::path::PathBuf::from(std::env::var_os("OUT_DIR").unwrap()).join("dispatch.rs"),
        code,
    )
    .unwrap();
}
