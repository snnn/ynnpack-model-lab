// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
use super::*;

#[repr(C)]
#[derive(Default, Clone, Copy)]
pub(crate) struct Config {
    pub vocab: u32,
    pub width: u32,
    pub layers: u32,
    pub ple_width: u32,
    pub owners: u32,
}
#[repr(C)]
#[derive(Default, Clone, Copy)]
pub(crate) struct KvSpec {
    pub owner: u32,
    pub heads: u32,
    pub width: u32,
}
extern "C" {
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
    fn lab_assets_config(assets: *mut c_void, config: *mut Config, error: *mut NativeError) -> i32;
    fn lab_assets_owner(
        assets: *mut c_void,
        index: usize,
        owner: *mut KvSpec,
        error: *mut NativeError,
    ) -> i32;
    fn lab_assets_embed(
        assets: *mut c_void,
        tokens: *const i32,
        count: usize,
        embedded: *mut c_void,
        embedded_count: usize,
        ple: *const *mut c_void,
        layers: usize,
        ple_count: usize,
        element_bytes: usize,
        error: *mut NativeError,
    ) -> i32;

}
impl Assets {
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
        }))
    }
    pub fn config(&self) -> Result<Config> {
        let mut out = Config::default();
        call(|e| unsafe { lab_assets_config(self.ptr.as_ptr(), &mut out, e) })?;
        Ok(out)
    }
    pub fn owner(&self, index: usize) -> Result<KvSpec> {
        let mut out = KvSpec::default();
        call(|e| unsafe { lab_assets_owner(self.ptr.as_ptr(), index, &mut out, e) })?;
        Ok(out)
    }
    pub fn embed(
        &self,
        tokens: &[i32],
        embedded: &mut ActivationBuffer,
        ple: &mut [ActivationBuffer],
    ) -> Result<()> {
        let count = ple.iter().map(ActivationBuffer::len).min().unwrap_or(0);
        if ple
            .iter()
            .any(|p| p.element_bytes() != embedded.element_bytes())
        {
            return Err(Error::invalid("Mixed activation dtypes"));
        }
        let pointers: Vec<_> = ple.iter().map(ActivationBuffer::pointer).collect();
        // SAFETY: synchronous call; native validates token IDs and all lengths.
        call(|e| unsafe {
            lab_assets_embed(
                self.ptr.as_ptr(),
                tokens.as_ptr(),
                tokens.len(),
                embedded.pointer(),
                embedded.len(),
                pointers.as_ptr(),
                pointers.len(),
                count,
                embedded.element_bytes(),
                e,
            )
        })
    }
}

pub(crate) enum ActivationBuffer {
    Fp32(Buffer<f32>),
    Bf16(Buffer<u16>),
}
impl ActivationBuffer {
    pub fn new(count: usize, bf16: bool) -> Self {
        if bf16 {
            Self::Bf16(Buffer::new(count, 0))
        } else {
            Self::Fp32(Buffer::new(count, 0.0))
        }
    }
    fn len(&self) -> usize {
        match self {
            Self::Fp32(v) => v.len(),
            Self::Bf16(v) => v.len(),
        }
    }
    fn element_bytes(&self) -> usize {
        match self {
            Self::Fp32(_) => 4,
            Self::Bf16(_) => 2,
        }
    }
    fn pointer(&self) -> *mut c_void {
        match self {
            Self::Fp32(v) => v.native_ptr().cast(),
            Self::Bf16(v) => v.native_ptr().cast(),
        }
    }
    /// Same stable-storage/exclusive-session contract as PreparedGraph::bind.
    pub unsafe fn bind(
        &self,
        graph: &mut PreparedGraph,
        name: &CStr,
        shape: &[usize],
        optional: bool,
    ) -> Result<()> {
        match self {
            Self::Fp32(v) => unsafe { graph.bind(name, v, shape, optional) },
            Self::Bf16(v) => unsafe { graph.bind(name, v, shape, optional) },
        }
    }
}
