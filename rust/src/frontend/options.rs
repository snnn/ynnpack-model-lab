// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
// Parse text options even in token-ID-only builds, to report the disabled feature.
#![cfg_attr(not(feature = "tokenizers"), allow(dead_code))]
use crate::{Error, Result};
use std::collections::{BTreeMap, BTreeSet};

#[derive(Debug)]
pub(crate) enum Input {
    TokenIds(String),
    Prompt {
        prompt: Text,
        continuation: Text,
    },
    Jsonl(String),
    Corpus {
        file: String,
        lengths: String,
        continuation: usize,
    },
}
#[derive(Debug)]
pub(crate) enum Text {
    Literal(String),
    File(String),
}
#[derive(Debug)]
pub(crate) struct Options {
    pub bundle_dir: String,
    pub parameter_dir: String,
    pub hf_model_dir: String,
    pub asset_manifest: String,
    pub cache_dir: String,
    pub model_dir: Option<String>,
    pub trace_plan: String,
    pub output_dir: String,
    pub tokenizer_dir: String,
    pub input: Input,
    pub cache_capacity: usize,
    pub num_threads: usize,
    pub prefill_rows: usize,
    pub warmup_runs: i32,
    pub measured_runs: i32,
    pub dump_outputs: bool,
    pub dump_pipeline: bool,
    pub report_memory: bool,
    pub profile_execution: String,
}

impl Options {
    // None means --help was printed. No process exit from library code.
    pub fn parse(args: &[String], require_model: bool) -> Result<Option<Self>> {
        let mut values = BTreeMap::new();
        let mut iter = args.iter().skip(1);
        while let Some(arg) = iter.next() {
            if arg == "--help" || arg == "-h" {
                println!(
                    "{}\nRequired: {}--output_dir=NEW_DIR\n\
Input (choose one): --cases_file=TSV (model runner only)\n\
  --tokenizer_dir=DIR --prompt=TEXT (or --prompt_file=FILE)\n\
    optional --continuation=TEXT (or --continuation_file=FILE)\n\
  --tokenizer_dir=DIR --text_cases_file=JSONL\n\
  --tokenizer_dir=DIR --corpus_file=FILE --prompt_lengths=17,128,1024\n\
    --continuation_tokens=32\n\
Options: --cache_capacity=2048 --num_threads=4 --prefill_rows=128\n\
  --warmup_runs=1 --measured_runs=3 --dump_outputs --dump_pipeline --report_memory\n\
  --profile_execution=none|prefill|decode|all (diagnostic timings)\n\
HF packages: replace --bundle_dir with --hf_model_dir=DIR --asset_manifest=FILE --cache_dir=DIR",
                    if require_model {
                        "YNNPACK model experiment"
                    } else {
                        "Tokenizer benchmark case probe"
                    },
                    if require_model {
                        "--bundle_dir=DIR --parameter_dir=DIR "
                    } else {
                        ""
                    }
                );
                if require_model {
                    println!(
                        "Model package: --model_dir=DIR (program.json, execution.json and model.json)\n\
Diagnostics: --trace_plan=DIR (changes graph outputs; do not use for performance measurements)"
                    );
                }
                return Ok(None);
            }
            let (key, value) = match arg.split_once('=') {
                Some(pair) => pair,
                None if ["--dump_outputs", "--dump_pipeline", "--report_memory"]
                    .contains(&arg.as_str()) =>
                {
                    (arg.as_str(), "true")
                }
                None => (
                    arg.as_str(),
                    iter.next()
                        .ok_or_else(|| Error::invalid(format!("Missing value for {arg}")))?
                        .as_str(),
                ),
            };
            if !key.starts_with("--")
                || (value.is_empty() && key != "--prompt" && key != "--continuation")
            {
                return Err(Error::invalid(format!("Invalid/empty option: {key}")));
            }
            if values.insert(key.to_owned(), value.to_owned()).is_some() {
                return Err(Error::invalid(format!("Repeated option: {key}")));
            }
        }
        let present: BTreeSet<_> = values.keys().cloned().collect();
        let mut take =
            |key: &str, default: &str| values.remove(key).unwrap_or_else(|| default.into());
        let mut bundle_dir = take("--bundle_dir", "");
        let mut parameter_dir = take("--parameter_dir", "");
        let hf_model_dir = take("--hf_model_dir", "");
        let asset_manifest = take("--asset_manifest", "");
        let cache_dir = take("--cache_dir", "");
        let model_dir = if require_model && present.contains("--model_dir") {
            Some(take("--model_dir", ""))
        } else {
            None
        };
        let trace_plan = if require_model {
            take("--trace_plan", "")
        } else {
            String::new()
        };
        let output_dir = take("--output_dir", "");
        let tokenizer_dir = take("--tokenizer_dir", "");
        let cases_file = take("--cases_file", "");
        let text_cases_file = take("--text_cases_file", "");
        let corpus_file = take("--corpus_file", "");
        let prompt = take("--prompt", "");
        let prompt_file = take("--prompt_file", "");
        let continuation = take("--continuation", "");
        let continuation_file = take("--continuation_file", "");
        let lengths = take("--prompt_lengths", "17,128,1024");
        let count = number(&take("--continuation_tokens", "32"), 0, i32::MAX as usize)?;
        let cache_capacity = number(&take("--cache_capacity", "2048"), 1, 32768)?;
        let num_threads = number(&take("--num_threads", "4"), 1, 256)?;
        let prefill_rows = number(&take("--prefill_rows", "128"), 1, 128)?;
        let warmup_runs = number(&take("--warmup_runs", "1"), 0, i32::MAX as usize)? as i32;
        let measured_runs = number(&take("--measured_runs", "3"), 1, i32::MAX as usize)? as i32;
        let dump_outputs = boolean(&take("--dump_outputs", "false"))?;
        let dump_pipeline = boolean(&take("--dump_pipeline", "false"))?;
        let report_memory = boolean(&take("--report_memory", "false"))?;
        let profile_execution = take("--profile_execution", "none");
        if let Some(key) = values.keys().next() {
            return Err(Error::invalid(format!("Unknown option: {key}")));
        }
        let has = |key: &str| present.contains(key);
        let explicit = has("--prompt") || has("--prompt_file");
        let modes = usize::from(!cases_file.is_empty())
            + usize::from(!text_cases_file.is_empty())
            + usize::from(!corpus_file.is_empty())
            + usize::from(explicit);
        if modes != 1
            || (has("--prompt") && has("--prompt_file"))
            || (has("--continuation") && has("--continuation_file"))
        {
            return Err(Error::invalid("Choose exactly one input mode; use --help"));
        }
        if (has("--continuation") || has("--continuation_file")) && !explicit {
            return Err(Error::invalid(
                "Continuation text requires an explicit prompt",
            ));
        }
        if (has("--prompt_lengths") || has("--continuation_tokens")) && corpus_file.is_empty() {
            return Err(Error::invalid("Length options require --corpus_file"));
        }
        if cases_file.is_empty() == tokenizer_dir.is_empty() {
            return Err(Error::invalid(
                "Text input requires --tokenizer_dir; TSV uses token IDs directly",
            ));
        }
        if !cfg!(feature = "tokenizers") && cases_file.is_empty() {
            return Err(Error::invalid(
                "Text input requires LAB_ENABLE_TOKENIZERS=ON",
            ));
        }
        if let Some(root) = &model_dir {
            if bundle_dir.is_empty() { bundle_dir = root.clone(); }
            if parameter_dir.is_empty() { parameter_dir = format!("{root}/parameters"); }
        }
        let hf = !hf_model_dir.is_empty() && !asset_manifest.is_empty() && !cache_dir.is_empty();
        if output_dir.is_empty()
            || (require_model && ((bundle_dir.is_empty() && !hf) || parameter_dir.is_empty()))
        {
            return Err(Error::invalid("Invalid/missing options; use --help"));
        }
        if !["none", "prefill", "decode", "all"].contains(&profile_execution.as_str())
            || (!require_model && profile_execution != "none")
        {
            return Err(Error::invalid("Invalid execution profiling mode"));
        }
        let input = if !cases_file.is_empty() {
            Input::TokenIds(cases_file)
        } else if !corpus_file.is_empty() {
            Input::Corpus {
                file: corpus_file,
                lengths,
                continuation: count,
            }
        } else if !text_cases_file.is_empty() {
            Input::Jsonl(text_cases_file)
        } else {
            Input::Prompt {
                prompt: if has("--prompt_file") {
                    Text::File(prompt_file)
                } else {
                    Text::Literal(prompt)
                },
                continuation: if has("--continuation_file") {
                    Text::File(continuation_file)
                } else {
                    Text::Literal(continuation)
                },
            }
        };
        Ok(Some(Self {
            bundle_dir,
            parameter_dir,
            hf_model_dir,
            asset_manifest,
            cache_dir,
            model_dir,
            trace_plan,
            output_dir,
            tokenizer_dir,
            input,
            cache_capacity,
            num_threads,
            prefill_rows,
            warmup_runs,
            measured_runs,
            dump_outputs,
            dump_pipeline,
            report_memory,
            profile_execution,
        }))
    }
}

fn number(text: &str, min: usize, max: usize) -> Result<usize> {
    // Match std::stoi's leading whitespace/+ handling for existing runner CLI.
    text.trim_start_matches(|c: char| c.is_ascii_whitespace())
        .parse::<i32>()
        .ok()
        .and_then(|n| usize::try_from(n).ok())
        .filter(|n| (min..=max).contains(n))
        .ok_or_else(|| Error::invalid(format!("Invalid integer: {text}")))
}
fn boolean(text: &str) -> Result<bool> {
    match text {
        "true" | "1" => Ok(true),
        "false" | "0" => Ok(false),
        _ => Err(Error::invalid(format!("Invalid boolean: {text}"))),
    }
}
