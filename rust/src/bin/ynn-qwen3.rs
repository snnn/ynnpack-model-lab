// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
use serde_json::json;
use sha2::{Digest, Sha256};
use std::{collections::BTreeMap, path::PathBuf};
use ynnpack_lab::{compiler, models::qwen3::Assets, Error, Result};
fn main() {
    if let Err(e) = run() {
        eprintln!("{e}");
        std::process::exit(1);
    }
}
fn run() -> Result<()> {
    let args = std::env::args().skip(1).collect::<Vec<_>>();
    if args.len() != 8
        || args[0] != "--assets"
        || args[2] != "--output"
        || args[4] != "--capacity"
        || args[6] != "--prefill-rows"
    {
        return Err(Error::invalid("usage: ynn-qwen3 --assets assets.json --output NEW_DIRECTORY --capacity N --prefill-rows N"));
    }
    let input = PathBuf::from(&args[1]);
    let output = PathBuf::from(&args[3]);
    let capacity = args[5]
        .parse::<i64>()
        .map_err(|_| Error::invalid("Invalid capacity"))?;
    let rows = args[7]
        .parse::<i64>()
        .map_err(|_| Error::invalid("Invalid rows"))?;
    if output.exists() {
        return Err(Error::invalid("Output already exists"));
    }
    let assets: Assets = serde_json::from_slice(&std::fs::read(&input)?)?;
    let program = assets.program(capacity, rows)?;
    let compiled = compiler::compile(&program)?;
    let stage = output.with_extension(format!("stage-{}", std::process::id()));
    compiled.write(&stage)?;
    struct Cleanup(PathBuf);
    impl Drop for Cleanup {
        fn drop(&mut self) {
            let _ = std::fs::remove_dir_all(&self.0);
        }
    }
    let _cleanup = Cleanup(stage.clone());
    let base = input.parent().unwrap();
    let mut counts = 0;
    for entry in std::fs::read_dir(base.join("parameters"))? {
        let entry = entry?;
        let name = entry.file_name();
        let name = name
            .to_str()
            .ok_or_else(|| Error::invalid("Asset filename"))?;
        if !name.ends_with(".bin") {
            continue;
        }
        let content = std::fs::read(entry.path())?;
        if format!("{:x}.bin", Sha256::digest(&content)) != name {
            return Err(Error::invalid("Source asset checksum mismatch"));
        }
        let dest = stage.join("parameters").join(name);
        if !dest.exists() {
            std::fs::write(dest, content)?;
        }
        counts += 1;
    }
    let mut graphs = BTreeMap::new();
    for phase in ["prefill", "decode"] {
        let g = &compiled.graphs[phase];
        graphs.insert(phase,json!({"file":format!("{phase}.ynn"),"sha256":format!("{:x}",Sha256::digest(compiled.plans[phase].as_bytes())),"logits":if phase=="decode"{g.outputs.first()}else{None},"row_policy":"padded","scalars":{"position":"position","valid_rows":"valid_rows"},"inputs":[{"name":"token_ids","dtype":"int32","shape":[1,"rows"],"recipe":{"kind":"tokens"}},{"name":"input_pos","dtype":"int32","shape":["rows"],"recipe":{"kind":"positions"}},{"name":"mask","dtype":"fp32","shape":[1,1,"rows","capacity"],"recipe":{"kind":"mask","window":null,"masked":"finite_min"}}]}));
    }
    let resources=compiled.graphs["decode"].resources.iter().map(|r|json!({"name":r.owner,"axis":r.axis,"dtype":"fp32","shape":compiled.graphs["decode"].values[&r.owner].tensor.shape.iter().map(|d|d.literal().unwrap()).collect::<Vec<_>>()})).collect::<Vec<_>>();
    let runner = json!({"format":"ynn-llm-execution","model":"qwen3-rust","capacity":capacity,"prefill_rows":rows,"vocabulary":assets.config["vocab_size"],"prefill_after_decode":false,"graphs":graphs,"resources":resources,"fixed_states":[],"embeddings":{}});
    std::fs::write(
        stage.join("model.json"),
        serde_json::to_vec_pretty(
            &json!({"format":"qwen3-rust-author","recipe":assets.recipe,"runner":runner}),
        )?,
    )?;
    std::fs::write(
        stage.join("semantic-program.json"),
        serde_json::to_vec(&program)?,
    )?;
    let tokenizer = base.join("tokenizer");
    if tokenizer.is_dir() {
        std::fs::create_dir(stage.join("tokenizer"))?;
        for entry in std::fs::read_dir(tokenizer)? {
            let entry = entry?;
            if !entry.file_type()?.is_file() {
                return Err(Error::invalid("Invalid tokenizer asset"));
            }
            std::fs::copy(
                entry.path(),
                stage.join("tokenizer").join(entry.file_name()),
            )?;
        }
    }
    std::fs::copy(&input, stage.join("assets.json"))?;
    if output.exists() {
        return Err(Error::invalid("Output appeared during compilation"));
    }
    std::fs::rename(stage, &output)?;
    println!(
        "{}",
        json!({"output":output,"parameter_files":counts,"phases":compiled.report})
    );
    Ok(())
}
