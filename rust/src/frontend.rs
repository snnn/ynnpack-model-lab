// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
//! Shared benchmark inputs. Everything resolves before model setup; tokenizer
//! engines drop before RSS snapshots and no tokenization enters warm execution.
#![cfg_attr(not(feature = "gemma"), allow(dead_code))]
mod options;
use options::Input;
pub(crate) use options::Options;
#[cfg(feature = "tokenizers")]
mod sentencepiece;
#[cfg(feature = "tokenizers")]
mod strict_json;
#[cfg(feature = "frontend-tests")]
pub(crate) mod tests;
#[cfg(feature = "tokenizers")]
mod tokenizer;
use crate::{io, Error, Result};
use serde_json::{json, Value};
use sha2::{Digest, Sha256};
use std::collections::BTreeSet;
use std::fs;
use std::path::Path;
use std::time::Instant;

#[derive(Debug, PartialEq, Eq)]
pub(crate) struct Case {
    pub name: String,
    pub prompt: Vec<i32>,
    pub continuation: Vec<i32>,
}
pub(crate) struct Frontend {
    pub cases: Vec<Case>,
    pub resolved_tsv: String,
    pub metadata: Value,
}
fn hash(data: &[u8]) -> String {
    format!("{:x}", Sha256::digest(data))
}
fn ms(start: Instant) -> f64 {
    start.elapsed().as_secs_f64() * 1000.0
}
fn rss() -> (u64, u64) {
    // Linux and Android report both values in KiB; unavailable fields remain 0.
    let status = fs::read_to_string("/proc/self/status").unwrap_or_default();
    let get = |key| {
        status
            .lines()
            .find_map(|line| {
                line.strip_prefix(key)?
                    .split_whitespace()
                    .next()?
                    .parse()
                    .ok()
            })
            .unwrap_or(0)
    };
    (get("VmRSS:"), get("VmHWM:"))
}
fn positive(text: &str, zero: bool) -> Result<usize> {
    if text.is_empty() || !text.bytes().all(|b| b.is_ascii_digit()) {
        return Err(Error::invalid(format!(
            "Invalid nonnegative integer: {text}"
        )));
    }
    text.parse::<i32>()
        .ok()
        .filter(|n| *n > 0 || zero)
        .map(|n| n as usize)
        .ok_or_else(|| Error::invalid(format!("Invalid positive integer: {text}")))
}
fn token_ids(text: &str) -> Result<Vec<i32>> {
    if text == "-" {
        return Ok(Vec::new());
    }
    text.split(',')
        .map(|v| positive(v, true).map(|v| v as i32))
        .collect()
}
fn input_record(role: &str, path: &str, data: &[u8]) -> Value {
    json!({"role":role,"path":path,"bytes":data.len(),"sha256":hash(data)})
}
fn read_input(role: &str, path: &str, inputs: &mut Vec<Value>) -> Result<String> {
    let text = fs::read_to_string(path)?;
    inputs.push(input_record(role, path, text.as_bytes()));
    Ok(text)
}
impl Frontend {
    #[allow(unused_mut)] // Timing/tokenizer fields stay zero in token-ID-only builds.
    pub fn resolve(o: &Options, model_vocab: Option<usize>) -> Result<Self> {
        let start = Instant::now();
        let (rss_before, peak_before) = rss();
        let mut inputs = Vec::new();
        let mut vocab = model_vocab;
        let mut load_ms = 0.0;
        let mut encode_ms = 0.0;
        let mut encode_calls = 0;
        let mut tokenizer_record = Value::Null;
        let (mode, cases) = if let Input::TokenIds(path) = &o.input {
            if model_vocab.is_none_or(|v| v == 0) {
                return Err(Error::invalid("TSV requires a model vocabulary size"));
            }
            let text = read_input("cases", path, &mut inputs)?;
            let mut cases = Vec::new();
            for line in text.split_terminator('\n') {
                // The TSV reader also accepts a final CR without a newline.
                let line = line.strip_suffix('\r').unwrap_or(line);
                if line.is_empty() || line.starts_with('#') {
                    continue;
                }
                let fields: Vec<_> = line.split('\t').collect();
                if fields.len() != 3 {
                    return Err(Error::invalid("Expected three TSV fields"));
                }
                cases.push(Case {
                    name: fields[0].into(),
                    prompt: token_ids(fields[1])?,
                    continuation: token_ids(fields[2])?,
                });
            }
            ("token_ids", cases)
        } else {
            #[cfg(not(feature = "tokenizers"))]
            return Err(Error::invalid(
                "Text input requires LAB_ENABLE_TOKENIZERS=ON",
            ));
            #[cfg(feature = "tokenizers")]
            {
                let load_start = Instant::now();
                let mut tokenizer = tokenizer::Tokenizer::load(Path::new(&o.tokenizer_dir))?;
                load_ms = ms(load_start);
                let m = &tokenizer.manifest;
                if model_vocab.is_some_and(|v| v < m.vocab_size as usize) {
                    return Err(Error::invalid(
                        "Tokenizer vocabulary exceeds model vocabulary",
                    ));
                }
                vocab = Some(model_vocab.unwrap_or(m.vocab_size as usize));
                tokenizer_record = json!({
                    "directory":o.tokenizer_dir,"format":m.format,"file":m.file,"bytes":m.bytes,"sha256":m.sha256,
                    "manifest_sha256":tokenizer.manifest_sha256,"source":m.source,"vocab_size":m.vocab_size,"prefix_ids":m.prefix_ids,"suffix_ids":m.suffix_ids,
                });
                let prefix = m.prefix_ids.clone();
                let suffix = m.suffix_ids.clone();
                let policy = prefix.len() + suffix.len();
                let mut encode = |text: &str| -> Result<Vec<i32>> {
                    let time = Instant::now();
                    let ids = tokenizer.encode(text)?;
                    encode_ms += ms(time);
                    encode_calls += 1;
                    Ok(ids)
                };
                let mut text_case =
                    |name: String, prompt: &str, continuation: &str| -> Result<Case> {
                        let mut ids = prefix.clone();
                        ids.extend(encode(prompt)?);
                        ids.extend_from_slice(&suffix);
                        Ok(Case {
                            name,
                            prompt: ids,
                            continuation: encode(continuation)?,
                        })
                    };
                let result = match &o.input {
                    Input::Prompt {
                        prompt,
                        continuation,
                    } => {
                        let mut text = |role, value: &options::Text| -> Result<String> {
                            match value {
                                options::Text::File(path) => read_input(role, path, &mut inputs),
                                options::Text::Literal(value) => {
                                    inputs.push(input_record(role, "", value.as_bytes()));
                                    Ok(value.clone())
                                }
                            }
                        };
                        (
                            "prompt",
                            vec![text_case(
                                "prompt".into(),
                                &text("prompt", prompt)?,
                                &text("continuation", continuation)?,
                            )?],
                        )
                    }
                    Input::Jsonl(path) => {
                        #[derive(serde::Deserialize)]
                        #[serde(deny_unknown_fields)]
                        struct Record {
                            name: String,
                            prompt: String,
                            #[serde(default)]
                            continuation: String,
                        }
                        let data = read_input("text_cases", path, &mut inputs)?;
                        let mut cases = Vec::new();
                        for (i, line) in data.lines().enumerate() {
                            if line.trim_matches([' ', '\t', '\r']).is_empty() {
                                continue;
                            }
                            let record: Record = serde_json::from_str(line).map_err(|e| {
                                Error::invalid(format!("Text case line {}: {e}", i + 1))
                            })?;
                            cases.push(text_case(
                                record.name,
                                &record.prompt,
                                &record.continuation,
                            )?);
                        }
                        ("text_cases", cases)
                    }
                    Input::Corpus {
                        file,
                        lengths,
                        continuation,
                    } => {
                        let data = read_input("corpus", file, &mut inputs)?;
                        let ids = encode(&data)?;
                        let mut seen = BTreeSet::new();
                        let mut cases = Vec::new();
                        for length in lengths.split(',') {
                            let length = positive(length, false)?;
                            if !seen.insert(length) {
                                return Err(Error::invalid("Duplicate corpus prompt length"));
                            }
                            if length < policy
                                || length > o.cache_capacity
                                || *continuation > o.cache_capacity - length
                            {
                                return Err(Error::invalid(
                                    "Invalid corpus prompt/continuation length",
                                ));
                            }
                            let body = length - policy;
                            if body > ids.len() || *continuation > ids.len() - body {
                                return Err(Error::invalid(
                                    "Corpus has too few tokens for requested lengths",
                                ));
                            }
                            let mut prompt = prefix.clone();
                            prompt.extend_from_slice(&ids[..body]);
                            prompt.extend_from_slice(&suffix);
                            cases.push(Case {
                                name: format!("prompt_{length}"),
                                prompt,
                                continuation: ids[body..body + continuation].to_vec(),
                            });
                        }
                        ("corpus", cases)
                    }
                    Input::TokenIds(_) => unreachable!(),
                };
                drop(tokenizer);
                result
            }
        };
        let vocab = vocab.ok_or_else(|| Error::invalid("Missing vocabulary"))?;
        if cases.is_empty() {
            return Err(Error::invalid("No benchmark cases"));
        }
        let mut seen = BTreeSet::new();
        let mut resolved_tsv = String::new();
        let mut records = Vec::new();
        for c in &cases {
            if c.name.is_empty()
                || !c
                    .name
                    .bytes()
                    .all(|b| b.is_ascii_alphanumeric() || b == b'_' || b == b'-')
            {
                return Err(Error::invalid("Case names must be simple identifiers"));
            }
            if !seen.insert(&c.name) {
                return Err(Error::invalid(format!("Duplicate case name: {}", c.name)));
            }
            if c.prompt.is_empty() {
                return Err(Error::invalid(format!("Empty resolved prompt: {}", c.name)));
            }
            if c.prompt.len() > o.cache_capacity
                || c.continuation.len() > o.cache_capacity - c.prompt.len()
            {
                return Err(Error::invalid(format!(
                    "Prompt + continuation exceeds capacity: {}",
                    c.name
                )));
            }
            if c.prompt
                .iter()
                .chain(&c.continuation)
                .any(|id| *id < 0 || *id as usize >= vocab)
            {
                return Err(Error::invalid(format!(
                    "Token ID outside model vocabulary: {}",
                    c.name
                )));
            }
            let ids = |ids: &[i32]| {
                if ids.is_empty() {
                    "-".into()
                } else {
                    ids.iter().map(i32::to_string).collect::<Vec<_>>().join(",")
                }
            };
            resolved_tsv.push_str(&format!(
                "{}\t{}\t{}\n",
                c.name,
                ids(&c.prompt),
                ids(&c.continuation)
            ));
            records.push(json!({"name":c.name,"prompt_tokens":c.prompt.len(),"continuation_tokens":c.continuation.len()}));
        }
        let digest = hash(resolved_tsv.as_bytes());
        let total_ms = ms(start);
        let (rss_after, peak_after) = rss();
        let metadata = json!({
            "version":1,"mode":mode,"tokenizer":tokenizer_record,"model_vocab_size":model_vocab,"inputs":inputs,"cases":records,
            "resolved_cases_sha256":digest,"tokenizer_load_ms":load_ms,"tokenizer_encode_ms":encode_ms,"tokenizer_encode_calls":encode_calls,
            "frontend_total_ms":total_ms,"rss_before_kib":rss_before,"rss_after_release_kib":rss_after,"peak_rss_before_kib":peak_before,"peak_rss_after_release_kib":peak_after,
        });
        Ok(Self {
            cases,
            resolved_tsv,
            metadata,
        })
    }
    pub fn save(&self, output: &Path) -> Result<()> {
        fs::write(output.join("resolved_cases.tsv"), &self.resolved_tsv)?;
        io::json(&output.join("frontend.json"), &self.metadata)
    }
}
#[cfg(feature = "tokenizer-probe")]
pub(crate) fn probe(args: &[String]) -> Result<()> {
    let Some(options) = Options::parse(args, false)? else {
        return Ok(());
    };
    let frontend = Frontend::resolve(&options, None)?;
    let output = Path::new(&options.output_dir);
    io::new_directory(output)?;
    frontend.save(output)?;
    print!("{}", frontend.resolved_tsv);
    Ok(())
}
