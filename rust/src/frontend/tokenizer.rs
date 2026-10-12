// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
use super::{hash, sentencepiece::SentencePiece};
use crate::{Error, Result};
use serde::{Deserialize, Serialize};
use serde_json::Value;
use std::{fs, path::Path};

#[derive(Deserialize, Serialize)]
pub(super) struct Manifest {
    pub version: u32,
    pub format: String,
    pub file: String,
    pub bytes: u64,
    pub sha256: String,
    pub vocab_size: i32,
    pub source: Value,
    pub prefix_ids: Vec<i32>,
    pub suffix_ids: Vec<i32>,
}
enum Engine {
    Hf(Box<tokenizers::Tokenizer>),
    Sp(SentencePiece),
}
pub(super) struct Tokenizer {
    pub manifest: Manifest,
    pub manifest_sha256: String,
    engine: Engine,
}
fn hf_error(e: tokenizers::Error) -> Error {
    Error::invalid(format!("HF tokenizer: {e}"))
}
impl Tokenizer {
    pub fn load(directory: &Path) -> Result<Self> {
        let bytes = fs::read(directory.join("manifest.json"))?;
        let manifest: Manifest = serde_json::from_value(super::strict_json::parse(&bytes)?)?;
        if manifest.version != 1 || manifest.vocab_size <= 0 {
            return Err(Error::invalid(
                "Invalid tokenizer manifest version/vocabulary",
            ));
        }
        if ["repo", "revision"].iter().any(|k| {
            manifest
                .source
                .get(k)
                .and_then(Value::as_str)
                .is_none_or(str::is_empty)
        }) {
            return Err(Error::invalid("Tokenizer source identity is empty/invalid"));
        }
        // Path::components normalizes internal '.' components: inspect spelling too.
        if manifest.file.is_empty()
            || manifest.file.contains('\0')
            || Path::new(&manifest.file).is_absolute()
            || manifest.file.split('/').any(|p| p == "." || p == "..")
        {
            return Err(Error::invalid("Invalid tokenizer payload path"));
        }
        let data = fs::read(directory.join(&manifest.file))?;
        if data.len() as u64 != manifest.bytes || hash(&data) != manifest.sha256 {
            return Err(Error::invalid("Tokenizer payload hash/size mismatch"));
        }
        let (engine, vocab) = match manifest.format.as_str() {
            "hf_json" => {
                let tokenizer = tokenizers::Tokenizer::from_bytes(&data).map_err(hf_error)?;
                if tokenizer.get_padding().is_some() || tokenizer.get_truncation().is_some() {
                    return Err(Error::invalid(
                        "Tokenizer JSON must disable padding and truncation",
                    ));
                }
                let vocab = tokenizer
                    .get_vocab(true)
                    .values()
                    .map(|id| u64::from(*id) + 1)
                    .max()
                    .unwrap_or(0);
                (Engine::Hf(Box::new(tokenizer)), vocab)
            }
            "sentencepiece" => {
                let tokenizer = SentencePiece::load(&data)?;
                let vocab = tokenizer.vocab as u64;
                (Engine::Sp(tokenizer), vocab)
            }
            _ => {
                return Err(Error::invalid(format!(
                    "Unsupported tokenizer format: {}",
                    manifest.format
                )))
            }
        };
        if vocab != manifest.vocab_size as u64 {
            return Err(Error::invalid("Tokenizer vocabulary differs from manifest"));
        }
        let mut tokenizer = Self {
            manifest,
            manifest_sha256: hash(&bytes),
            engine,
        };
        // Decoding also checks sparse HF vocabulary membership, beyond ID extent.
        tokenizer.decode(&tokenizer.manifest.prefix_ids.clone())?;
        tokenizer.decode(&tokenizer.manifest.suffix_ids.clone())?;
        Ok(tokenizer)
    }
    pub fn encode(&mut self, text: &str) -> Result<Vec<i32>> {
        let ids = match &mut self.engine {
            Engine::Hf(t) => t
                .encode(text, false)
                .map_err(hf_error)?
                .get_ids()
                .iter()
                .map(|id| {
                    i32::try_from(*id).map_err(|_| Error::invalid("Tokenizer ID exceeds i32"))
                })
                .collect::<Result<Vec<_>>>()?,
            Engine::Sp(t) => t.encode(text)?,
        };
        self.check_ids(&ids)?;
        Ok(ids)
    }
    fn check_ids(&self, ids: &[i32]) -> Result<()> {
        if ids
            .iter()
            .any(|id| !(0..self.manifest.vocab_size).contains(id))
        {
            return Err(Error::invalid("Tokenizer ID outside vocabulary"));
        }
        Ok(())
    }
    pub fn decode(&mut self, ids: &[i32]) -> Result<String> {
        self.check_ids(ids)?;
        match &mut self.engine {
            Engine::Hf(t) => {
                let ids: Vec<_> = ids.iter().map(|id| *id as u32).collect();
                if ids.iter().any(|id| t.id_to_token(*id).is_none()) {
                    return Err(Error::invalid("Unknown token ID"));
                }
                t.decode(&ids, false).map_err(hf_error)
            }
            Engine::Sp(t) => t.decode(ids),
        }
    }
}
