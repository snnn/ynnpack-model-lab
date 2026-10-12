// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
fn main() {
    let args: Vec<String> = std::env::args().skip(1).collect();
    if let Err(error) = ynnpack_lab::plan_text::main(&args) {
        eprintln!("{error}");
        std::process::exit(1);
    }
}
