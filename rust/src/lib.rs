// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
//! Owned sessions and typed DSL construction around the pinned native backend.
//! Graph compilation and kernels remain native. No Core IR is linked.

mod ffi;
#[cfg(feature = "fixture")]
mod fixture;
#[cfg(feature = "input-frontend")]
mod frontend;
#[cfg(feature = "gemma")]
pub mod gemma;
#[cfg(any(
    feature = "vision",
    feature = "gemma",
    feature = "input-frontend",
    test
))]
mod io;
mod plan;
pub mod plan_text;
#[cfg(all(feature = "vision", feature = "gemma"))]
compile_error!("Vision and Gemma have separate application entry points; build them separately");
#[cfg(feature = "native-tests")]
mod native_tests;
#[cfg(feature = "vision")]
pub mod vision;

use std::fmt;

#[derive(Debug)]
pub struct Error {
    pub kind: ErrorKind,
    pub message: String,
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum ErrorKind {
    Invalid,
    Backend,
    Unexpected,
    Io,
}

impl Error {
    pub(crate) fn invalid(message: impl Into<String>) -> Self {
        Self {
            kind: ErrorKind::Invalid,
            message: message.into(),
        }
    }
}
impl fmt::Display for Error {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        f.write_str(&self.message)
    }
}
impl std::error::Error for Error {}
impl From<std::io::Error> for Error {
    fn from(e: std::io::Error) -> Self {
        Self {
            kind: ErrorKind::Io,
            message: e.to_string(),
        }
    }
}
impl From<serde_json::Error> for Error {
    fn from(e: serde_json::Error) -> Self {
        Self::invalid(e.to_string())
    }
}
pub type Result<T> = std::result::Result<T, Error>;

// No Rust unwind may cross C main. No native pointers leave the private ABI.
#[no_mangle]
unsafe extern "C" fn lab_rust_main(argc: i32, argv: *const *const std::ffi::c_char) -> i32 {
    let result = std::panic::catch_unwind(|| {
        // SAFETY: C main supplies argc live NUL-terminated argv strings.
        let args = unsafe { ffi::arguments(argc, argv) }?;
        #[cfg(feature = "fixture")]
        return fixture::main(&args);
        #[cfg(feature = "native-tests")]
        return native_tests::run(&args);
        #[cfg(all(feature = "vision", not(feature = "native-tests")))]
        return vision::main(&args);
        #[cfg(feature = "tokenizer-probe")]
        return frontend::probe(&args);
        #[cfg(feature = "frontend-tests")]
        return frontend::tests::run(&args);
        #[cfg(feature = "gemma")]
        return std::thread::Builder::new()
            .name("gemma".into())
            .stack_size(64 * 1024 * 1024)
            .spawn(move || gemma::main(&args))?
            .join()
            .map_err(|_| Error::invalid("Gemma execution thread panicked"))?;
        #[cfg(not(any(
            feature = "vision",
            feature = "gemma",
            feature = "fixture",
            feature = "tokenizer-probe",
            feature = "frontend-tests"
        )))]
        {
            let _ = args;
            Err::<(), _>(Error::invalid("No runner selected"))
        }
    });
    match result {
        Ok(Ok(())) => 0,
        Ok(Err(e)) => {
            eprintln!("{e}");
            1
        }
        Err(_) => {
            eprintln!("Rust runner panicked; discard this session");
            1
        }
    }
}
