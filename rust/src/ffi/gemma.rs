// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
use super::*;

extern "C" {
    fn lab_assets_raw_embedding(
        assets: *mut c_void,
        name: *const c_char,
        bytes: usize,
        out: *mut *const u8,
        error: *mut NativeError,
    ) -> i32;
    fn lab_assets_create_hf(
        source: *const c_char,
        manifest: *const c_char,
        cache: *const c_char,
        parameters: *const c_char,
        identity: *const c_char,
        bf16: i32,
        out: *mut *mut c_void,
        error: *mut NativeError,
    ) -> i32;

}
impl Assets {
    pub(super) fn verify_hf_embedding(&self, d: &crate::plan::Data) -> Result<()> {
        if let Some((size, hash)) = self.verified.borrow().get(&d.path) {
            return if *size == d.bytes && *hash == d.sha256 {
                Ok(())
            } else {
                Err(Error::invalid("Conflicting embedding identities"))
            };
        }
        let name = d
            .path
            .strip_prefix("@hf_raw/")
            .ok_or_else(|| Error::invalid("HF embeddings require original tensor identities"))?;
        let name = string(name)?;
        let mut pointer = std::ptr::null();
        call(|e| unsafe {
            lab_assets_raw_embedding(self.ptr.as_ptr(), name.as_ptr(), d.bytes, &mut pointer, e)
        })?;
        if pointer.is_null() {
            return Err(Error::invalid("Null embedding mapping"));
        }
        // Provider validates the span and owns the immutable source mapping.
        use sha2::{Digest, Sha256};
        let bytes = unsafe { std::slice::from_raw_parts(pointer, d.bytes) };
        if format!("{:x}", Sha256::digest(bytes)) != d.sha256 {
            return Err(Error::invalid("HF embedding identity mismatch"));
        }
        self.verified
            .borrow_mut()
            .insert(d.path.clone(), (d.bytes, d.sha256.clone()));
        Ok(())
    }
    pub fn open_hf(
        source: &Path,
        manifest: &Path,
        cache: &Path,
        parameters: &Path,
        identity: &str,
        bf16: bool,
    ) -> Result<Rc<Self>> {
        let (source, manifest, cache, parameters, identity) = (
            path(source)?,
            path(manifest)?,
            path(cache)?,
            path(parameters)?,
            string(identity)?,
        );
        let mut ptr = std::ptr::null_mut();
        call(|e| unsafe {
            lab_assets_create_hf(
                source.as_ptr(),
                manifest.as_ptr(),
                cache.as_ptr(),
                parameters.as_ptr(),
                identity.as_ptr(),
                bf16.into(),
                &mut ptr,
                e,
            )
        })?;
        Ok(Rc::new(Self {
            ptr: NonNull::new(ptr).ok_or_else(|| Error::invalid("Null HF assets"))?,
            verified: RefCell::new(HashMap::new()),
            owned: HashMap::new(),
            source_dirs: None,
        }))
    }
}
