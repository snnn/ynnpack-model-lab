// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
//! Private C ABI. C++ catches all exceptions; handles are never Send or Sync.
// Each binary uses a subset of this ABI; the fixture build exercises both.
#![allow(dead_code)]
use crate::{Error, ErrorKind, Result};
use std::cell::RefCell;
use std::cell::UnsafeCell;
use std::collections::HashMap;
use std::ffi::{c_char, c_void, CStr, CString};
use std::ops::{Deref, DerefMut};
use std::path::Path;
use std::ptr::NonNull;
use std::rc::Rc;

// Native bindings retain pointers between calls. UnsafeCell permits native
// writes through those pointers after a temporary Rust output borrow ends.
// Sessions own these buffers, prohibit concurrent execution and drop graphs
// before storage. Keeping the allocation boxed prevents relocation/resizing.
pub(crate) struct Buffer<T> {
    cells: Box<[UnsafeCell<T>]>,
}
impl<T: Copy> Buffer<T> {
    pub fn new(count: usize, value: T) -> Self {
        Self {
            cells: (0..count)
                .map(|_| UnsafeCell::new(value))
                .collect::<Vec<_>>()
                .into_boxed_slice(),
        }
    }
}
impl<T> Buffer<T> {
    fn native_ptr(&self) -> *mut T {
        self.cells.as_ptr().cast::<T>().cast_mut()
    }
}
impl<T> Deref for Buffer<T> {
    type Target = [T];
    fn deref(&self) -> &[T] {
        // SAFETY: only private session code accesses buffers, outside native
        // calls. Public output borrows borrow the entire exclusive session.
        unsafe { std::slice::from_raw_parts(self.native_ptr(), self.cells.len()) }
    }
}
impl<T> DerefMut for Buffer<T> {
    fn deref_mut(&mut self) -> &mut [T] {
        unsafe { std::slice::from_raw_parts_mut(self.native_ptr(), self.cells.len()) }
    }
}

#[cfg(feature = "gemma")]
mod gemma;
#[cfg(feature = "gemma")]
pub(crate) use gemma::*;
mod plan;

#[repr(C)]
struct NativeError {
    kind: i32,
    message: [c_char; 1024],
}
#[repr(C)]
#[derive(Clone, Copy, Debug, Default)]
pub(crate) struct Counters {
    pub append_calls: u64,
    pub append_bytes: u64,
    pub view_copy_bytes: u64,
}
#[cfg(feature = "fixture")]
#[repr(C)]
pub(crate) struct AppendCheck {
    pub append: usize,
    pub actual: *const u8,
    pub expected: *const u8,
    pub bytes: usize,
}
#[repr(C)]
#[derive(Default)]
pub(crate) struct Memory {
    pub root: u64,
    pub live: u64,
    pub peak: u64,
    pub allocated: u64,
    pub allocations: u64,
}

extern "C" {
    fn lab_model_name() -> *const c_char;
    fn lab_assets_create(
        bundle: *const c_char,
        parameters: *const c_char,
        out: *mut *mut c_void,
        error: *mut NativeError,
    ) -> i32;
    fn lab_assets_delete(assets: *mut c_void);
    #[cfg(feature = "native-tests")]
    fn lab_test_graph_create(
        assets: *mut c_void,
        phase: u32,
        out: *mut *mut c_void,
        error: *mut NativeError,
    ) -> i32;
    fn lab_graph_delete(graph: *mut c_void);
    fn lab_graph_compile(graph: *mut c_void, threads: usize, error: *mut NativeError) -> i32;
    fn lab_graph_bind(
        graph: *mut c_void,
        name: *const c_char,
        data: *mut c_void,
        bytes: usize,
        shape: *const usize,
        rank: usize,
        optional: i32,
        error: *mut NativeError,
    ) -> i32;
    fn lab_graph_run(graph: *mut c_void, error: *mut NativeError) -> i32;
    #[cfg(feature = "fixture")]
    fn lab_fixture_run(
        graph: *mut c_void,
        checks: *const AppendCheck,
        count: usize,
        appends: usize,
        fail_after: usize,
        error: *mut NativeError,
    ) -> i32;
    fn lab_graph_trace(
        graph: *mut c_void,
        plan: *const c_char,
        output: *const c_char,
        error: *mut NativeError,
    ) -> i32;
    fn lab_graph_shape(
        graph: *mut c_void,
        name: *const c_char,
        dims: *mut usize,
        rank: *mut usize,
        error: *mut NativeError,
    ) -> i32;
    fn lab_graph_weight_stats(graph: *mut c_void, values: *mut u64, error: *mut NativeError)
        -> i32;
    fn lab_graph_counters(graph: *mut c_void, out: *mut Counters, error: *mut NativeError) -> i32;
    fn lab_rss_bytes() -> u64;
    fn lab_peak_rss_bytes() -> u64;
    fn lab_allocator_bytes(values: *mut u64) -> i32;
    fn lab_graph_scalar(
        graph: *mut c_void,
        name: *const c_char,
        value: i64,
        error: *mut NativeError,
    ) -> i32;
    fn lab_resource_create(
        graph: *mut c_void,
        name: *const c_char,
        data: *mut c_void,
        bytes: usize,
        shape: *const usize,
        rank: usize,
        out: *mut *mut c_void,
        error: *mut NativeError,
    ) -> i32;
    fn lab_resource_delete(resource: *mut c_void);
    fn lab_resource_reset(resource: *mut c_void, error: *mut NativeError) -> i32;
    fn lab_resource_import(resource: *mut c_void, prefix: usize, error: *mut NativeError) -> i32;
    fn lab_resource_status(resource: *mut c_void, values: *mut u64, error: *mut NativeError)
        -> i32;
    fn lab_graph_resource(
        graph: *mut c_void,
        name: *const c_char,
        resource: *mut c_void,
        error: *mut NativeError,
    ) -> i32;
    fn lab_graph_diagnostics(
        graph: *mut c_void,
        pipeline: *const c_char,
        profile: *const c_char,
        memory: i32,
        error: *mut NativeError,
    ) -> i32;
    fn lab_graph_profile_step(
        graph: *mut c_void,
        name: *const c_char,
        rep: i32,
        step: usize,
        position: usize,
        rows: usize,
        prefill: i32,
        action: i32,
        error: *mut NativeError,
    ) -> i32;
    fn lab_graph_memory(graph: *mut c_void, memory: *mut Memory, error: *mut NativeError) -> i32;
    #[cfg(feature = "native-tests")]
    fn lab_test_fail_after_appends(
        graph: *mut c_void,
        count: usize,
        error: *mut NativeError,
    ) -> i32;
    #[cfg(feature = "native-tests")]
    fn lab_test_state_views(
        graph: *mut c_void,
        capacity: i32,
        heads: i32,
        window: i32,
        threads: i32,
        output: *const c_char,
        queries: i32,
        error: *mut NativeError,
    ) -> i32;
}

fn call(f: impl FnOnce(*mut NativeError) -> i32) -> Result<()> {
    let mut error = NativeError {
        kind: 0,
        message: [0; 1024],
    };
    if f(&mut error) == 0 {
        return Ok(());
    }
    // Force termination even if the bridge ever violates its text contract.
    error.message[1023] = 0;
    // SAFETY: local initialized array with a terminating NUL.
    let message = unsafe { CStr::from_ptr(error.message.as_ptr()) }
        .to_string_lossy()
        .into_owned();
    Err(Error {
        kind: match error.kind {
            1 => ErrorKind::Invalid,
            2 => ErrorKind::Backend,
            _ => ErrorKind::Unexpected,
        },
        message,
    })
}
pub(crate) fn string(s: &str) -> Result<CString> {
    CString::new(s).map_err(|_| Error::invalid("NUL in native string"))
}
fn path(p: &Path) -> Result<CString> {
    use std::os::unix::ffi::OsStrExt;
    CString::new(p.as_os_str().as_bytes()).map_err(|_| Error::invalid("NUL in path"))
}
pub(crate) fn model_name() -> &'static str {
    // SAFETY: bridge returns a static string literal for the linked factory.
    unsafe { CStr::from_ptr(lab_model_name()) }
        .to_str()
        .expect("ASCII model name")
}
pub(crate) unsafe fn arguments(argc: i32, argv: *const *const c_char) -> Result<Vec<String>> {
    if argc < 1 || argv.is_null() {
        return Err(Error::invalid("Invalid argv"));
    }
    // SAFETY: caller guarantees argc initialized entries.
    unsafe { std::slice::from_raw_parts(argv, argc as usize) }
        .iter()
        .map(|&p| {
            if p.is_null() {
                return Err(Error::invalid("Null argv entry"));
            }
            // SAFETY: caller guarantees NUL-terminated argument storage.
            unsafe { CStr::from_ptr(p) }
                .to_str()
                .map(str::to_owned)
                .map_err(|_| Error::invalid("Arguments must be UTF-8"))
        })
        .collect()
}
pub(crate) fn rss() -> u64 {
    unsafe { lab_rss_bytes() }
}
pub(crate) fn peak_rss() -> u64 {
    unsafe { lab_peak_rss_bytes() }
}
pub(crate) fn allocator_bytes() -> Option<[u64; 3]> {
    let mut values = [0; 3];
    (unsafe { lab_allocator_bytes(values.as_mut_ptr()) } != 0).then_some(values)
}

pub(crate) struct Assets {
    ptr: NonNull<c_void>,
    verified: RefCell<HashMap<String, (usize, String)>>,
}
impl Assets {
    pub fn open(bundle: &Path, parameters: &Path) -> Result<Rc<Self>> {
        let (bundle, parameters) = (path(bundle)?, path(parameters)?);
        let mut ptr = std::ptr::null_mut();
        // SAFETY: strings and out/error storage live until this call returns.
        call(|e| unsafe { lab_assets_create(bundle.as_ptr(), parameters.as_ptr(), &mut ptr, e) })?;
        Ok(Rc::new(Self {
            ptr: NonNull::new(ptr).ok_or_else(|| Error::invalid("Null asset handle"))?,
            verified: RefCell::new(HashMap::new()),
        }))
    }
}
impl Drop for Assets {
    fn drop(&mut self) {
        unsafe { lab_assets_delete(self.ptr.as_ptr()) }
    }
}

// Typestate prevents calling Run before native compilation. Graph retains all
// constant mappings through Rc; its Drop runs before that Rc is released.
pub(crate) struct GraphBuilder {
    graph: NativeGraph,
}
pub(crate) struct PreparedGraph {
    graph: NativeGraph,
}
struct NativeGraph {
    ptr: NonNull<c_void>,
    _assets: Rc<Assets>,
}
impl Drop for NativeGraph {
    fn drop(&mut self) {
        unsafe { lab_graph_delete(self.ptr.as_ptr()) }
    }
}
impl GraphBuilder {
    #[cfg(feature = "native-tests")]
    pub fn state_fixture(
        self,
        capacity: i32,
        heads: i32,
        window: i32,
        threads: i32,
        output: &Path,
        queries: i32,
    ) -> Result<()> {
        let output = path(output)?;
        call(|e| unsafe {
            lab_test_state_views(
                self.graph.ptr.as_ptr(),
                capacity,
                heads,
                window,
                threads,
                output.as_ptr(),
                queries,
                e,
            )
        })
    }

    pub fn trace(&mut self, plan: &Path) -> Result<()> {
        let plan = path(plan)?;
        call(|e| unsafe {
            lab_graph_trace(self.graph.ptr.as_ptr(), plan.as_ptr(), c"".as_ptr(), e)
        })
    }
    pub fn profile(&mut self, output: &Path) -> Result<()> {
        let output = path(output)?;
        call(|e| unsafe {
            lab_graph_diagnostics(self.graph.ptr.as_ptr(), c"".as_ptr(), output.as_ptr(), 0, e)
        })
    }
    #[cfg(feature = "native-tests")]
    pub fn native_fixture(assets: Rc<Assets>, phase: u32) -> Result<Self> {
        let mut ptr = std::ptr::null_mut();
        call(|e| unsafe { lab_test_graph_create(assets.ptr.as_ptr(), phase, &mut ptr, e) })?;
        Ok(Self {
            graph: NativeGraph {
                ptr: NonNull::new(ptr).ok_or_else(|| Error::invalid("Null graph handle"))?,
                _assets: assets,
            },
        })
    }
    pub fn prepare(self, threads: usize) -> Result<PreparedGraph> {
        if !(1..=256).contains(&threads) {
            return Err(Error::invalid("threads must be 1..256"));
        }
        call(|e| unsafe { lab_graph_compile(self.graph.ptr.as_ptr(), threads, e) })?;
        Ok(PreparedGraph { graph: self.graph })
    }
}
impl PreparedGraph {
    pub fn weight_stats(&self) -> Result<[u64; 3]> {
        let mut values = [0; 3];
        call(|e| unsafe {
            lab_graph_weight_stats(self.graph.ptr.as_ptr(), values.as_mut_ptr(), e)
        })?;
        Ok(values)
    }
    pub fn shape(&self, name: &CStr) -> Result<Vec<usize>> {
        let mut shape = [0; 8];
        let mut rank = 0;
        call(|e| unsafe {
            lab_graph_shape(
                self.graph.ptr.as_ptr(),
                name.as_ptr(),
                shape.as_mut_ptr(),
                &mut rank,
                e,
            )
        })?;
        if rank > shape.len() {
            return Err(Error::invalid("Invalid native rank"));
        }
        Ok(shape[..rank].to_vec())
    }
    pub fn save_trace(&self, output: &Path) -> Result<()> {
        let output = path(output)?;
        call(|e| unsafe {
            lab_graph_trace(self.graph.ptr.as_ptr(), c"".as_ptr(), output.as_ptr(), e)
        })
    }
    pub fn scalar(&mut self, name: &CStr, value: i64) -> Result<()> {
        call(|e| unsafe { lab_graph_scalar(self.graph.ptr.as_ptr(), name.as_ptr(), value, e) })
    }
    /// Resource and its storage must outlive every graph it is bound to.
    pub unsafe fn resource(&mut self, name: &CStr, resource: &mut Resource) -> Result<()> {
        call(|e| unsafe {
            lab_graph_resource(
                self.graph.ptr.as_ptr(),
                name.as_ptr(),
                resource.ptr.as_ptr(),
                e,
            )
        })
    }
    pub fn diagnostics(&mut self, pipeline: Option<&Path>, memory: bool) -> Result<()> {
        let pipeline = path(pipeline.unwrap_or(Path::new("")))?;
        call(|e| unsafe {
            lab_graph_diagnostics(
                self.graph.ptr.as_ptr(),
                pipeline.as_ptr(),
                c"".as_ptr(),
                memory.into(),
                e,
            )
        })
    }
    pub fn memory(&self) -> Result<Memory> {
        let mut memory = Memory::default();
        call(|e| unsafe { lab_graph_memory(self.graph.ptr.as_ptr(), &mut memory, e) })?;
        Ok(memory)
    }
    pub fn profile_step(
        &mut self,
        name: &str,
        rep: i32,
        step: usize,
        position: usize,
        action: i32,
    ) -> Result<()> {
        self.profile_step_rows(name, rep, step, position, 1, false, action)
    }
    pub fn profile_step_rows(
        &mut self,
        name: &str,
        rep: i32,
        step: usize,
        position: usize,
        rows: usize,
        prefill: bool,
        action: i32,
    ) -> Result<()> {
        let name = string(name)?;
        call(|e| unsafe {
            lab_graph_profile_step(
                self.graph.ptr.as_ptr(),
                name.as_ptr(),
                rep,
                step,
                position,
                rows,
                i32::from(prefill),
                action,
                e,
            )
        })
    }
    #[cfg(feature = "native-tests")]
    pub fn fail_after_appends(&mut self, count: usize) -> Result<()> {
        call(|e| unsafe { lab_test_fail_after_appends(self.graph.ptr.as_ptr(), count, e) })
    }
    /// Allocation must not move, resize, be accessed during Run, or be freed
    /// until this graph is destroyed. Session owns it and drops the graph first.
    pub unsafe fn bind<T>(
        &mut self,
        name: &CStr,
        data: &Buffer<T>,
        shape: &[usize],
        optional: bool,
    ) -> Result<()> {
        unsafe {
            self.bind_bytes(
                name,
                data,
                data.cells.len() * std::mem::size_of::<T>(),
                shape,
                optional,
            )
        }
    }
    pub unsafe fn bind_bytes<T>(
        &mut self,
        name: &CStr,
        data: &Buffer<T>,
        bytes: usize,
        shape: &[usize],
        optional: bool,
    ) -> Result<()> {
        if bytes > data.cells.len() * std::mem::size_of::<T>() {
            return Err(Error::invalid("Binding exceeds allocation"));
        }
        call(|e| unsafe {
            lab_graph_bind(
                self.graph.ptr.as_ptr(),
                name.as_ptr(),
                data.native_ptr().cast(),
                bytes,
                shape.as_ptr(),
                shape.len(),
                optional.into(),
                e,
            )
        })
    }
    pub fn run(&mut self) -> Result<()> {
        call(|e| unsafe { lab_graph_run(self.graph.ptr.as_ptr(), e) })
    }
    #[cfg(feature = "fixture")]
    pub unsafe fn run_observed(
        &mut self,
        checks: &[AppendCheck],
        appends: usize,
        fail_after: Option<usize>,
    ) -> Result<()> {
        // Caller keeps all actual/expected spans alive and exclusively owns
        // native output storage until this synchronous call completes.
        call(|e| unsafe {
            lab_fixture_run(
                self.graph.ptr.as_ptr(),
                checks.as_ptr(),
                checks.len(),
                appends,
                fail_after.unwrap_or(usize::MAX),
                e,
            )
        })
    }
    pub fn counters(&self) -> Result<Counters> {
        let mut out = Counters::default();
        call(|e| unsafe { lab_graph_counters(self.graph.ptr.as_ptr(), &mut out, e) })?;
        Ok(out)
    }
}

pub(crate) struct Resource {
    ptr: NonNull<c_void>,
    data: Buffer<u64>,
    bytes: usize,
}
impl Resource {
    pub fn import(&mut self, prefix: usize) -> Result<()> {
        call(|e| unsafe { lab_resource_import(self.ptr.as_ptr(), prefix, e) })
    }
    pub fn status(&self) -> Result<[u64; 3]> {
        let mut values = [0; 3];
        call(|e| unsafe { lab_resource_status(self.ptr.as_ptr(), values.as_mut_ptr(), e) })?;
        Ok(values)
    }
    pub fn initialize(&mut self, bytes: &[u8], prefix: usize) -> Result<()> {
        if bytes.len() != self.bytes {
            return Err(Error::invalid("Resource initial payload size differs"));
        }
        self.import(prefix)?;
        // SAFETY: exclusive ownership outside execution; allocation is stable.
        let target = unsafe {
            std::slice::from_raw_parts_mut(self.data.native_ptr().cast::<u8>(), self.bytes)
        };
        target.copy_from_slice(bytes);
        Ok(())
    }
    pub fn check_canary(&self) -> Result<()> {
        let all = unsafe {
            std::slice::from_raw_parts(self.data.native_ptr().cast::<u8>(), self.data.len() * 8)
        };
        if all[self.bytes..].iter().any(|&b| b != 0xa5) {
            return Err(Error::invalid("Resource buffer canary overwritten"));
        }
        Ok(())
    }
    pub fn new(graph: &PreparedGraph, name: &CStr, shape: &[usize]) -> Result<Self> {
        Self::new_typed(graph, name, shape, 1)
    }
    pub fn new_typed(
        graph: &PreparedGraph,
        name: &CStr,
        shape: &[usize],
        element_bytes: usize,
    ) -> Result<Self> {
        if ![1, 2, 4, 8].contains(&element_bytes) {
            return Err(Error::invalid("Invalid resource element size"));
        }
        let count = shape
            .iter()
            .try_fold(1usize, |n, &d| n.checked_mul(d).filter(|_| d > 0))
            .and_then(|n| n.checked_mul(element_bytes))
            .and_then(|n| n.checked_add(64))
            .filter(|&n| n <= isize::MAX as usize)
            .ok_or_else(|| Error::invalid("Invalid resource shape"))?;
        let data = Buffer::new(count.div_ceil(8), 0u64);
        let bytes = count - 64;
        // SAFETY: allocation is exclusively owned and not yet bound.
        unsafe {
            std::slice::from_raw_parts_mut(data.native_ptr().cast::<u8>(), data.len() * 8)[bytes..]
                .fill(0xa5);
        }
        let mut ptr = std::ptr::null_mut();
        // SAFETY: native validates geometry and retains the owned allocation.
        call(|e| unsafe {
            lab_resource_create(
                graph.graph.ptr.as_ptr(),
                name.as_ptr(),
                data.native_ptr().cast(),
                data.len() * 8,
                shape.as_ptr(),
                shape.len(),
                &mut ptr,
                e,
            )
        })?;
        Ok(Self {
            ptr: NonNull::new(ptr).ok_or_else(|| Error::invalid("Null resource"))?,
            data,
            bytes,
        })
    }
    pub fn reset(&mut self) -> Result<()> {
        call(|e| unsafe { lab_resource_reset(self.ptr.as_ptr(), e) })
    }
    pub fn data(&self) -> &[i8] {
        // SAFETY: u64 storage is initialized; byte access occurs outside native calls.
        unsafe { std::slice::from_raw_parts(self.data.native_ptr().cast(), self.bytes) }
    }
}
impl Drop for Resource {
    fn drop(&mut self) {
        unsafe { lab_resource_delete(self.ptr.as_ptr()) };
    }
}
