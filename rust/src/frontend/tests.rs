// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
//! CMake-linked checks also run on Android, against checked-in independent
//! Python goldens. No model weights or Python tokenizers are needed.
use super::*;

fn check(ok: bool, message: &str) -> Result<()> {
    if ok {
        Ok(())
    } else {
        Err(Error::invalid(message))
    }
}
fn fails<T>(value: Result<T>) -> Result<()> {
    check(value.is_err(), "Expected invalid input to fail")
}
fn args(extra: &[&str]) -> Vec<String> {
    [
        "runner",
        "--bundle_dir=unused",
        "--parameter_dir=unused",
        "--output_dir=unused",
    ]
    .into_iter()
    .chain(extra.iter().copied())
    .map(str::to_owned)
    .collect()
}
fn parse(extra: &[&str]) -> Result<Options> {
    Options::parse(&args(extra), true)?.ok_or_else(|| Error::invalid("Unexpected help"))
}
fn cases(temp: &Path) -> Result<()> {
    let file = temp.join("cases.tsv");
    let option = format!("--cases_file={}", file.display());
    let o = parse(&[&option, "--cache_capacity=3"])?;
    fs::write(&file, "# comment\r\n\na\t0,3\t2\r\nb\t1\t-\r")?;
    let f = Frontend::resolve(&o, Some(4))?;
    check(
        f.resolved_tsv == "a\t0,3\t2\nb\t1\t-\n",
        "TSV bytes changed",
    )?;
    check(
        f.metadata["tokenizer_encode_calls"] == 0
            && f.metadata["tokenizer_load_ms"] == 0.0
            && f.metadata["tokenizer_encode_ms"] == 0.0,
        "TSV should not tokenize",
    )?;
    f.save(temp)?;
    check(
        fs::read_to_string(temp.join("resolved_cases.tsv"))? == f.resolved_tsv,
        "Fixture write failed",
    )?;
    fails(Frontend::resolve(&o, None))?;
    fails(Frontend::resolve(
        &parse(&[&option, "--cache_capacity=2"])?,
        Some(4),
    ))?;
    for data in [
        "a\t0\t-\nb\t4\t-\n",
        "a\t-\t-\n",
        "a\t0\t-\na\t1\t-\n",
        "a\t0,\t-\n",
        "a\t-1\t-\n",
        "a\t0\n",
        "\n",
        "a/b\t0\t-\n",
        "a\t1.5\t-\n",
        "a\t2147483648\t-\n",
        "a\t+1\t-\n",
        "a\t0\t\n",
    ] {
        fs::write(&file, data)?;
        fails(Frontend::resolve(&o, Some(4)))?;
    }
    for extra in [
        vec![&option[..], "--cases_file=other"],
        vec!["--cases_file="],
        vec![&option, "--prompt=x"],
        vec![&option, "--continuation=x"],
        vec![&option, "--prompt_lengths=1"],
        vec![&option, "--tokenizer_dir=unused"],
        vec![&option, "--continuation_tokens=0"],
        vec![&option, "--cache_capacity=32769"],
        vec![&option, "--prefill_rows=129"],
        vec![&option, "--num_threads=0"],
        vec![&option, "--warmup_runs=-1"],
        vec![&option, "--measured_runs=0"],
        vec![&option, "--dump_outputs=maybe"],
        vec![&option, "--profile_execution=other"],
        vec![&option, "--unknown=x"],
        vec![&option, "--output_dir=x"],
        vec![&option, "--graph_dir="],
        vec![&option, "--graph_dir=x", "--graph_dir=y"],
        vec![&option, "--num_threads=1x"],
        vec![&option, "--num_threads=99999999999999"],
        vec![&option, "--measured_runs"],
    ] {
        fails(parse(&extra))?;
    }
    check(
        parse(&[&option, "--graph_dir", "plans"])?
            .graph_dir
            .as_deref()
            == Some("plans"),
        "Space-separated graph_dir failed",
    )?;
    let o = parse(&[
        &option,
        "--dump_outputs=0",
        "--dump_pipeline",
        "--report_memory=1",
        "--num_threads= +2",
    ])?;
    check(
        !o.dump_outputs && o.dump_pipeline && o.report_memory && o.num_threads == 2,
        "CLI options changed",
    )?;
    let text = ["--prompt=", "--tokenizer_dir=unused"];
    check(
        parse(&text).is_ok() == cfg!(feature = "tokenizers"),
        "Text build feature not enforced",
    )?;
    for conflicting in [
        "--text_cases_file=unused",
        "--prompt_file=unused",
        "--prompt_lengths=1",
        "--continuation_tokens=2",
    ] {
        fails(parse(&[text[0], text[1], conflicting]))?;
    }
    Ok(())
}

#[cfg(feature = "tokenizers")]
fn tokenizers(fixtures: &Path, temp: &Path) -> Result<()> {
    use super::tokenizer::Tokenizer;
    let ids = |value: &Value| -> Vec<i32> { serde_json::from_value(value.clone()).unwrap() };
    for kind in ["hf", "sp"] {
        let directory = fixtures.join(kind);
        let token_option = format!("--tokenizer_dir={}", directory.display());
        let mut tokenizer = Tokenizer::load(&directory)?;
        let golden: Value = serde_json::from_slice(&fs::read(directory.join("golden.json"))?)?;
        for case in golden["cases"].as_array().unwrap() {
            let text = case["text"].as_str().unwrap();
            let expected = ids(&case["ids"]);
            check(
                tokenizer.encode(text)? == expected,
                "IDs differ from independent Python reference",
            )?;
            check(
                tokenizer.decode(&expected)? == case["decoded"].as_str().unwrap(),
                "Decoded text differs from reference",
            )?;
            check(
                tokenizer.encode(text)? == expected,
                "Repeated encode changed IDs",
            )?;
        }
        fails(tokenizer.decode(&[-1]))?;
        fails(tokenizer.decode(&[320]))?;
        let mut o = parse(&[
            &token_option,
            "--prompt=hello world",
            "--continuation= there",
        ])?;
        let f = Frontend::resolve(&o, Some(320))?;
        let expected: Vec<_> = [1]
            .into_iter()
            .chain(tokenizer.encode("hello world")?)
            .collect();
        check(
            f.cases[0].prompt == expected
                && f.cases[0].continuation == tokenizer.encode(" there")?,
            "Manifest/continuation policy incorrect",
        )?;
        check(
            f.metadata["tokenizer_encode_calls"] == 2
                && f.metadata["resolved_cases_sha256"] == hash(f.resolved_tsv.as_bytes()),
            "Provenance incorrect",
        )?;
        check(
            f.metadata["inputs"][0]["sha256"] == hash(b"hello world"),
            "Input hash incorrect",
        )?;
        fails(Frontend::resolve(&o, Some(319)))?;
        check(
            Frontend::resolve(&o, None)?.metadata["model_vocab_size"].is_null(),
            "Probe claimed a model vocabulary",
        )?;
        check(
            Frontend::resolve(&o, Some(512))?.resolved_tsv == f.resolved_tsv,
            "Padded model vocabulary changed IDs",
        )?;
        o.cache_capacity = f.cases[0].prompt.len() + f.cases[0].continuation.len();
        check(
            Frontend::resolve(&o, Some(320))?.resolved_tsv == f.resolved_tsv,
            "Capacity boundary changed IDs",
        )?;
        o.cache_capacity -= 1;
        fails(Frontend::resolve(&o, Some(320)))?;
        check(
            Frontend::resolve(&parse(&[&token_option, "--prompt="])?, Some(320))?.cases[0].prompt
                == vec![1],
            "Empty text lost prefix",
        )?;

        let prompt_file = temp.join("prompt.txt");
        let file_option = format!("--prompt_file={}", prompt_file.display());
        for invalid in [
            vec![0xc0, 0x80],
            vec![0xed, 0xa0, 0x80],
            vec![0xf4, 0x90, 0x80, 0x80],
            vec![0xe2, 0x82],
            vec![0x80],
        ] {
            fs::write(&prompt_file, invalid)?;
            fails(Frontend::resolve(
                &parse(&[&token_option, &file_option])?,
                Some(320),
            ))?;
        }
        let exact = " hello\n\0world\n";
        fs::write(&prompt_file, exact)?;
        let expected: Vec<_> = [1].into_iter().chain(tokenizer.encode(exact)?).collect();
        let f = Frontend::resolve(&parse(&[&token_option, &file_option])?, Some(320))?;
        check(f.cases[0].prompt == expected, "Prompt file bytes changed")?;
        let continuation_option = format!("--continuation_file={}", prompt_file.display());
        let f = Frontend::resolve(
            &parse(&[&token_option, "--prompt=hello", &continuation_option])?,
            Some(320),
        )?;
        check(
            f.cases[0].continuation == tokenizer.encode(exact)?,
            "Continuation file bytes changed",
        )?;
        fails(parse(&[
            &token_option,
            "--prompt=x",
            "--continuation=",
            &continuation_option,
        ]))?;

        let file = temp.join("cases.jsonl");
        let jsonl = format!("--text_cases_file={}", file.display());
        let o = parse(&[&token_option, &jsonl])?;
        fs::write(
            &file,
            format!(
                "{}\n{}\n",
                json!({"name":"one","prompt":exact}),
                json!({"name":"two","prompt":"hello","continuation":" world"})
            ),
        )?;
        let f = Frontend::resolve(&o, Some(320))?;
        check(
            f.cases.len() == 2 && f.cases[0].prompt == expected,
            "JSONL resolution differs",
        )?;
        f.save(temp)?;
        let tsv = format!("--cases_file={}", temp.join("resolved_cases.tsv").display());
        check(
            Frontend::resolve(&parse(&[&tsv])?, Some(320))?.resolved_tsv == f.resolved_tsv,
            "Export does not replay",
        )?;
        for bad in [
            "{\"name\":\"one\",\"prompt\":\"hello\"}\n{\"name\":\"one\",\"prompt\":\"world\"}\n",
            "{\"name\":\"../bad\",\"prompt\":\"x\"}",
            "{\"name\":\"one\",\"prompt\":3}",
            "{\"name\":\"one\",\"prompt\":\"x\",\"extra\":true}",
            "{\"name\":\"one\",\"prompt\":\"\\ud800\"}",
            "{\"name\":\"one\",\"prompt\":\"x\",\"prompt\":\"y\"}",
            "{\"name\":\"one\",\"prompt\":\"x\",\"continuation\":null}",
            "{} trailing",
            "[]",
            "\n",
        ] {
            fs::write(&file, bad)?;
            fails(Frontend::resolve(&o, Some(320)))?;
        }
        let corpus_file = temp.join("corpus.txt");
        let corpus = "~".repeat(1100);
        fs::write(&corpus_file, &corpus)?;
        let stream = tokenizer.encode(&corpus)?;
        check(
            stream.len() == corpus.len(),
            "Unexpected test corpus tokenization",
        )?;
        let corpus_option = format!("--corpus_file={}", corpus_file.display());
        let resolve = |lengths: &str| {
            Frontend::resolve(
                &parse(&[
                    &token_option,
                    &corpus_option,
                    &format!("--prompt_lengths={lengths}"),
                    "--continuation_tokens=2",
                ])?,
                Some(320),
            )
        };
        let f = resolve("1,128,129,130,511,512,513,1024")?;
        for (case, length) in f.cases.iter().zip([1, 128, 129, 130, 511, 512, 513, 1024]) {
            let expected: Vec<_> = [1]
                .into_iter()
                .chain(stream[..length - 1].iter().copied())
                .collect();
            check(
                case.prompt == expected && case.continuation == stream[length - 1..length + 1],
                "Corpus slicing incorrect",
            )?;
        }
        check(
            f.cases.len() == 8 && f.metadata["tokenizer_encode_calls"] == 1,
            "Corpus should encode once",
        )?;
        for lengths in ["1,1", "1100", "0", "-1", "1,", "32769"] {
            fails(resolve(lengths))?;
        }
        let policy_dir = temp.join(format!("{kind}-policy"));
        fs::create_dir(&policy_dir)?;
        let mut manifest: Value =
            serde_json::from_slice(&fs::read(directory.join("manifest.json"))?)?;
        fs::copy(
            directory.join(&tokenizer.manifest.file),
            policy_dir.join(&tokenizer.manifest.file),
        )?;
        manifest["suffix_ids"] = json!([3]);
        io::json(&policy_dir.join("manifest.json"), &manifest)?;
        let policy_option = format!("--tokenizer_dir={}", policy_dir.display());
        let f = Frontend::resolve(
            &parse(&[
                &policy_option,
                &corpus_option,
                "--prompt_lengths=4",
                "--continuation_tokens=2",
            ])?,
            Some(320),
        )?;
        check(
            f.cases[0].prompt == vec![1, stream[0], stream[1], 3]
                && f.cases[0].continuation == stream[2..4],
            "Prefix/suffix corpus policy incorrect",
        )?;
        fails(Frontend::resolve(
            &parse(&[&policy_option, &corpus_option, "--prompt_lengths=1"])?,
            Some(320),
        ))?;
        manifest["prefix_ids"] = json!([]);
        manifest["suffix_ids"] = json!([]);
        io::json(&policy_dir.join("manifest.json"), &manifest)?;
        fails(Frontend::resolve(
            &parse(&[&policy_option, "--prompt="])?,
            Some(320),
        ))?;
    }
    let directory = temp.join("bad");
    fs::create_dir(&directory)?;
    let payload = fs::read(fixtures.join("hf/tokenizer.json"))?;
    let manifest: Value = serde_json::from_slice(&fs::read(fixtures.join("hf/manifest.json"))?)?;
    for format in ["hf_json", "sentencepiece", "unknown"] {
        let mut m = manifest.clone();
        m["format"] = format.into();
        m["bytes"] = 3.into();
        m["sha256"] = hash(b"bad").into();
        io::json(&directory.join("manifest.json"), &m)?;
        fs::write(directory.join("tokenizer.json"), "bad")?;
        fails(Tokenizer::load(&directory))?;
    }
    for key in ["padding", "truncation"] {
        let mut data: Value = serde_json::from_slice(&payload)?;
        data[key] = if key == "padding" {
            json!({"strategy":"BatchLongest","direction":"Right","pad_to_multiple_of":null,"pad_id":0,"pad_type_id":0,"pad_token":"<unk>"})
        } else {
            json!({"direction":"Right","max_length":3,"strategy":"LongestFirst","stride":0})
        };
        let data = serde_json::to_vec(&data)?;
        let mut m = manifest.clone();
        m["bytes"] = data.len().into();
        m["sha256"] = hash(&data).into();
        io::json(&directory.join("manifest.json"), &m)?;
        fs::write(directory.join("tokenizer.json"), data)?;
        fails(Tokenizer::load(&directory))?;
    }
    fs::write(directory.join("tokenizer.json"), &payload)?;
    for (key, value) in [
        ("sha256", json!("0".repeat(64))),
        ("bytes", json!(0)),
        ("vocab_size", json!(0)),
        ("vocab_size", json!(319)),
        ("prefix_ids", json!([-1])),
        ("suffix_ids", json!([320])),
        ("prefix_ids", json!([1.5])),
        ("version", json!(2)),
        ("source", json!({"repo":"", "revision":"v1"})),
        ("source", json!({"repo":"test"})),
        ("file", json!("../tokenizer.json")),
        ("file", json!("./tokenizer.json")),
        ("file", json!("a/./b")),
        ("file", json!("/tokenizer.json")),
        ("file", json!("\u{0}")),
    ] {
        let mut m = manifest.clone();
        m[key] = value;
        io::json(&directory.join("manifest.json"), &m)?;
        fails(Tokenizer::load(&directory))?;
    }
    let duplicate = serde_json::to_string(&manifest)?.replacen('{', "{\"version\":1,", 1);
    fs::write(directory.join("manifest.json"), duplicate)?;
    fails(Tokenizer::load(&directory))?;
    let duplicate = serde_json::to_string(&manifest)?
        .replace("\"source\":{", "\"source\":{\"repo\":\"duplicate\",");
    fs::write(directory.join("manifest.json"), duplicate)?;
    fails(Tokenizer::load(&directory))?;
    let sparse = br#"{"version":"1.0","added_tokens":[],"normalizer":null,"pre_tokenizer":null,"post_processor":null,"decoder":null,"model":{"type":"BPE","unk_token":"<unk>","vocab":{"<unk>":0,"a":7},"merges":[]}}"#;
    let mut m = manifest;
    m["bytes"] = sparse.len().into();
    m["sha256"] = hash(sparse).into();
    m["vocab_size"] = 8.into();
    m["prefix_ids"] = json!([7]);
    io::json(&directory.join("manifest.json"), &m)?;
    fs::write(directory.join("tokenizer.json"), sparse)?;
    let mut tokenizer = Tokenizer::load(&directory)?;
    check(
        tokenizer.encode("a")? == vec![7],
        "Sparse vocabulary extent treated as count",
    )?;
    fails(tokenizer.decode(&[1]))?;
    m["prefix_ids"] = json!([1]);
    io::json(&directory.join("manifest.json"), &m)?;
    fails(Tokenizer::load(&directory))?;
    Ok(())
}

pub(crate) fn run(args: &[String]) -> Result<()> {
    let mode = args.get(1).map(String::as_str);
    let (base, fixtures) = match (mode, args.len()) {
        (Some("cases"), 3) => (&args[2], None),
        (Some("tokenizers"), 4) => (&args[3], Some(Path::new(&args[2]))),
        _ => {
            return Err(Error::invalid(
                "frontend_test cases TEMP | tokenizers FIXTURES TEMP",
            ))
        }
    };
    let temp = Path::new(base).join(format!(
        "{}-{}",
        std::process::id(),
        std::time::SystemTime::now()
            .duration_since(std::time::UNIX_EPOCH)
            .unwrap()
            .as_nanos()
    ));
    fs::create_dir_all(&temp)?;
    match fixtures {
        None => cases(&temp)?,
        Some(fixtures) => {
            #[cfg(feature = "tokenizers")]
            tokenizers(fixtures, &temp)?;
            #[cfg(not(feature = "tokenizers"))]
            {
                let _ = fixtures;
                return Err(Error::invalid("Text tokenizers disabled"));
            }
        }
    }
    fs::remove_dir_all(temp)?;
    println!("Rust frontend {} passed", mode.unwrap());
    Ok(())
}
