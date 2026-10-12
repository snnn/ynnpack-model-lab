// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
use crate::{Error, Result};
use std::ffi::{c_char, c_void, CStr};
use std::marker::PhantomData;
use std::ptr::NonNull;
use std::rc::Rc;

extern "C" {
    fn lab_sp_create(
        data: *const u8,
        size: usize,
        out: *mut *mut c_void,
        vocab: *mut i32,
        error: *mut c_char,
        error_size: usize,
    ) -> i32;
    fn lab_sp_encode(
        handle: *mut c_void,
        text: *const u8,
        size: usize,
        ids: *mut *const i32,
        count: *mut usize,
        error: *mut c_char,
        error_size: usize,
    ) -> i32;
    fn lab_sp_decode(
        handle: *mut c_void,
        ids: *const i32,
        count: usize,
        text: *mut *const u8,
        size: *mut usize,
        error: *mut c_char,
        error_size: usize,
    ) -> i32;
    fn lab_sp_delete(handle: *mut c_void);
}
fn call(f: impl FnOnce(*mut c_char, usize) -> i32) -> Result<()> {
    let mut error = [0; 1024];
    if f(error.as_mut_ptr(), error.len()) == 0 {
        return Ok(());
    }
    // SAFETY: native catches exceptions and writes a terminated error string.
    Err(Error::invalid(format!(
        "SentencePiece: {}",
        unsafe { CStr::from_ptr(error.as_ptr()) }.to_string_lossy()
    )))
}
pub(super) struct SentencePiece {
    handle: NonNull<c_void>,
    pub vocab: i32,
    _local: PhantomData<Rc<()>>,
}
impl SentencePiece {
    pub fn load(data: &[u8]) -> Result<Self> {
        let mut handle = std::ptr::null_mut();
        let mut vocab = 0;
        // SAFETY: synchronous load copies the protobuf; all output pointers live.
        call(|e, n| unsafe {
            lab_sp_create(data.as_ptr(), data.len(), &mut handle, &mut vocab, e, n)
        })?;
        Ok(Self {
            handle: NonNull::new(handle)
                .ok_or_else(|| Error::invalid("Null SentencePiece handle"))?,
            vocab,
            _local: PhantomData,
        })
    }
    pub fn encode(&mut self, text: &str) -> Result<Vec<i32>> {
        let mut ids = std::ptr::null();
        let mut count = 0;
        // SAFETY: exclusive handle borrow; native output remains alive while copied.
        call(|e, n| unsafe {
            lab_sp_encode(
                self.handle.as_ptr(),
                text.as_ptr(),
                text.len(),
                &mut ids,
                &mut count,
                e,
                n,
            )
        })?;
        Ok(if count == 0 {
            Vec::new()
        } else {
            unsafe { std::slice::from_raw_parts(ids, count) }.to_vec()
        })
    }
    pub fn decode(&mut self, ids: &[i32]) -> Result<String> {
        if ids.iter().any(|id| !(0..self.vocab).contains(id)) {
            return Err(Error::invalid("Unknown token ID"));
        }
        let mut text = std::ptr::null();
        let mut size = 0;
        // SAFETY: validated IDs, exclusive handle borrow, output copied before reuse.
        call(|e, n| unsafe {
            lab_sp_decode(
                self.handle.as_ptr(),
                ids.as_ptr(),
                ids.len(),
                &mut text,
                &mut size,
                e,
                n,
            )
        })?;
        let bytes = if size == 0 {
            &[]
        } else {
            unsafe { std::slice::from_raw_parts(text, size) }
        };
        Ok(std::str::from_utf8(bytes)
            .map_err(|e| Error::invalid(e.to_string()))?
            .to_owned())
    }
}
impl Drop for SentencePiece {
    fn drop(&mut self) {
        // SAFETY: exactly one owner; no output references escape this wrapper.
        unsafe { lab_sp_delete(self.handle.as_ptr()) };
    }
}
