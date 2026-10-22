// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
use super::*;
use crate::llm::package;
extern "C" {
    fn lab_embedding_create(assets: *mut c_void, json: *const c_char, rows: usize,
        width: usize, bits: i32, block: usize, out: *mut *mut c_void, error: *mut NativeError) -> i32;
    fn lab_embedding_delete(value: *mut c_void);
    fn lab_embedding_slice(value: *mut c_void, tokens: *const i32, count: usize,
        begin: usize, columns: usize, output: *mut f32, elements: usize, error: *mut NativeError) -> i32;
}
pub(crate) struct Embedding { ptr: NonNull<c_void>, _assets: Rc<Assets> }
impl Embedding {
    pub fn new(assets: Rc<Assets>, e: &package::Embedding, vocabulary: usize) -> Result<Self> {
        for a in &e.assets {
            assets.verify(&crate::plan::Data { path:a.path.clone(), bytes:a.bytes, sha256:a.sha256.clone() })?;
        }
        let json=string(&serde_json::to_string(&e.record)?)?;
        let mut ptr=std::ptr::null_mut();
        call(|err| unsafe {lab_embedding_create(assets.ptr.as_ptr(),json.as_ptr(),vocabulary,
            e.width,e.bits as i32,e.block,&mut ptr,err)})?;
        Ok(Self{ptr:NonNull::new(ptr).ok_or_else(||Error::invalid("Null embedding"))?,_assets:assets})
    }
    pub fn lookup(&self, tokens:&[i32], begin:usize, columns:usize, output:&mut Buffer<f32>) -> Result<()> {
        call(|err| unsafe {lab_embedding_slice(self.ptr.as_ptr(),tokens.as_ptr(),tokens.len(),begin,
            columns,output.native_ptr(),output.len(),err)})
    }
}
impl Drop for Embedding {fn drop(&mut self){unsafe{lab_embedding_delete(self.ptr.as_ptr())}}}
