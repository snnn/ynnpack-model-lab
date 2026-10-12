// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
#![cfg_attr(
    any(
        feature = "native-tests",
        feature = "fixture",
        feature = "tokenizer-probe",
        feature = "frontend-tests"
    ),
    allow(dead_code)
)]
use crate::Error;
use crate::Result;
#[cfg(feature = "vision")]
use std::collections::BTreeMap;
use std::fs::{self, File};
use std::io::{BufWriter, Read, Write};
use std::path::Path;

pub(crate) fn read_limited(path: &Path, limit: u64) -> Result<Vec<u8>> {
    let mut bytes = Vec::new();
    File::open(path)?.take(limit + 1).read_to_end(&mut bytes)?;
    if bytes.len() as u64 > limit {
        return Err(Error::invalid("Artifact exceeds size limit"));
    }
    Ok(bytes)
}

#[cfg(feature = "vision")]
pub(crate) fn read_f32(path: &Path, count: usize) -> Result<Vec<f32>> {
    let bytes = fs::read(path)?;
    if Some(bytes.len()) != count.checked_mul(4) {
        return Err(Error::invalid(format!(
            "Wrong input size: {}",
            path.display()
        )));
    }
    let values: Vec<_> = bytes
        .chunks_exact(4)
        .map(|b| f32::from_le_bytes(b.try_into().unwrap()))
        .collect();
    if !values.iter().all(|x| x.is_finite()) {
        return Err(Error::invalid("Non-finite input"));
    }
    Ok(values)
}
pub(crate) fn write_f32(path: &Path, values: &[f32]) -> Result<()> {
    let mut out = BufWriter::new(File::create(path)?);
    for value in values {
        out.write_all(&value.to_le_bytes())?;
    }
    out.flush()?;
    Ok(())
}
pub(crate) fn new_directory(path: &Path) -> Result<()> {
    if let Some(parent) = path.parent() {
        if !parent.as_os_str().is_empty() {
            fs::create_dir_all(parent)?;
        }
    }
    // Atomic create fails for every existing directory, even an empty one.
    fs::create_dir(path)?;
    Ok(())
}
pub(crate) fn json(path: &Path, value: &impl serde::Serialize) -> Result<()> {
    let mut out = BufWriter::new(File::create(path)?);
    serde_json::to_writer_pretty(&mut out, value)?;
    out.write_all(b"\n")?;
    out.flush()?;
    Ok(())
}

#[cfg(feature = "vision")]
pub(crate) struct Arguments {
    pub values: BTreeMap<String, Vec<String>>,
}
#[cfg(feature = "vision")]
impl Arguments {
    pub fn parse(args: &[String], repeated: &[&str], flags: &[&str]) -> Result<Self> {
        let mut values = BTreeMap::<String, Vec<String>>::new();
        let mut iter = args.iter().skip(1);
        while let Some(arg) = iter.next() {
            let (key, value) = match arg.split_once('=') {
                Some((key, value)) => (key.to_owned(), value.to_owned()),
                None if flags.contains(&arg.as_str()) => (arg.clone(), "true".into()),
                None => (
                    arg.clone(),
                    iter.next()
                        .ok_or_else(|| Error::invalid(format!("Missing value: {arg}")))?
                        .clone(),
                ),
            };
            if !key.starts_with("--") || value.is_empty() {
                return Err(Error::invalid(format!("Invalid option: {key}")));
            }
            let list = values.entry(key.clone()).or_default();
            if !list.is_empty() && !repeated.contains(&key.as_str()) {
                return Err(Error::invalid(format!("Repeated option: {key}")));
            }
            list.push(value);
        }
        Ok(Self { values })
    }
    pub fn take(&mut self, key: &str, default: Option<&str>) -> Result<String> {
        self.values
            .remove(key)
            .and_then(|mut v| v.pop())
            .or_else(|| default.map(str::to_owned))
            .ok_or_else(|| Error::invalid(format!("Missing {key}")))
    }
    pub fn number(&mut self, key: &str, default: &str, min: usize, max: usize) -> Result<usize> {
        self.take(key, Some(default))?
            .parse::<usize>()
            .ok()
            .filter(|v| (min..=max).contains(v))
            .ok_or_else(|| Error::invalid(format!("Invalid {key}")))
    }
    pub fn boolean(&mut self, key: &str) -> Result<bool> {
        match self.take(key, Some("false"))?.as_str() {
            "true" | "1" => Ok(true),
            "false" | "0" => Ok(false),
            _ => Err(Error::invalid(format!("Invalid {key}"))),
        }
    }
    pub fn finish(self) -> Result<()> {
        if let Some(key) = self.values.keys().next() {
            return Err(Error::invalid(format!("Unknown option: {key}")));
        }
        Ok(())
    }
}
