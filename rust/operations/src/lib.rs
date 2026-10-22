// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
//! Group-32 asymmetric A8 / symmetric W4 operation. Native code supplies only
//! kernel catalogue queries, opaque kernel state and synchronous pool access.
use std::{
    ffi::c_void,
    panic::{catch_unwind, AssertUnwindSafe},
    ptr,
};

const CHANNELS: usize = 128;
const REDUCTION: usize = 32;
const ROWS: usize = 8;
const MAX_ACTIVATION_BYTES: usize = 1 << 30;

#[allow(
    dead_code,
    unused_imports,
    unused_variables,
    unused_mut,
    non_snake_case
)]
mod generated {
    extern crate alloc;
    include!(concat!(env!("OUT_DIR"), "/dispatch.rs"));
}
use generated::Strategy;

#[repr(C)]
#[derive(Default)]
struct ArchFacts {
    supported: u64,
    amx: u64,
}
#[repr(C)]
#[derive(Default)]
struct Candidate {
    handle: *mut c_void,
    block_m: usize,
    tile_m: usize,
    tile_n: usize,
    tile_k: usize,
}
impl Drop for Candidate {
    fn drop(&mut self) {
        if !self.handle.is_null() {
            unsafe { lab_dot_delete(self.handle) };
        }
    }
}
#[derive(Clone, Copy, Default)]
struct Metadata {
    present: bool,
    block_m: usize,
    tile_m: usize,
    tile_n: usize,
    tile_k: usize,
}
impl From<&Candidate> for Metadata {
    fn from(c: &Candidate) -> Self {
        Self {
            present: !c.handle.is_null(),
            block_m: c.block_m,
            tile_m: c.tile_m,
            tile_n: c.tile_n,
            tile_k: c.tile_k,
        }
    }
}
fn strategy_index(s: &Strategy) -> usize {
    match s {
        Strategy::UnsignedK4 => 0,
        Strategy::SignedK4 => 1,
        Strategy::PortableK1 => 2,
    }
}
struct Facts {
    candidates: [Metadata; 3],
}
impl generated::Context for Facts {
    fn usable(&mut self, strategy: &Strategy) -> u8 {
        let index = strategy_index(strategy);
        let c = self.candidates[index];
        (c.present
            && c.tile_m == 1
            && c.tile_k == if index == 2 { 1 } else { 4 }
            && c.block_m > 0
            && c.tile_n > 0
            && CHANNELS % c.tile_n == 0) as u8
    }
}

#[repr(C)]
#[derive(Clone, Copy, Debug)]
struct View {
    data: *const c_void,
    extent0: usize,
    extent1: usize,
    stride0: isize,
    stride1: isize,
}
impl View {
    unsafe fn at<T>(&self, x: usize, y: usize) -> *mut T {
        // SAFETY: callers validate shapes/strides; native storage owns the span.
        unsafe {
            self.data
                .cast::<T>()
                .offset(x as isize * self.stride0 + y as isize * self.stride1)
                .cast_mut()
        }
    }
    fn valid(&self, x: usize, y: usize) -> bool {
        !self.data.is_null()
            && self.extent0 == x
            && self.extent1 == y
            && self.stride0 >= 0
            && self.stride1 >= 0
            && (x.saturating_sub(1) as u128 * self.stride0 as u128
                + y.saturating_sub(1) as u128 * self.stride1 as u128)
                < (isize::MAX as u128 / 4)
    }
}
#[repr(C)]
#[derive(Debug)]
struct Invocation {
    x: View,
    weight: View,
    scales: View,
    zero: View,
    y: View,
    rows: usize,
    thread_pool: *mut c_void,
}
#[repr(C)]
struct Info {
    tile_k: usize,
    activation_shift: usize,
    block_m: usize,
    prepared_queries: usize,
    activation_bytes: usize,
    worker_scratch_bytes: usize,
    arch_flags: u64,
    kernel_name: *const std::ffi::c_char,
}
extern "C" {
    fn lab_dot_facts(out: *mut ArchFacts) -> i32;
    fn lab_dot_query(
        rows: usize,
        channels: usize,
        reduction: usize,
        packed_channels: usize,
        tile_k: usize,
        signed_a: i32,
        symmetric_b: i32,
        flags: u64,
        out: *mut Candidate,
    ) -> i32;
    fn lab_dot_delete(handle: *mut c_void);
    fn lab_dot_name(handle: *const c_void) -> *const std::ffi::c_char;
    fn lab_dot_invoke(
        handle: *const c_void,
        rows: usize,
        channels: usize,
        reduction: usize,
        a_stride: usize,
        a: *const u8,
        b_stride: usize,
        b: *const i8,
        c_stride: usize,
        c: *mut i32,
        state: *mut c_void,
    ) -> i32;
    fn lab_dot_parallel(
        pool: *mut c_void,
        tasks: usize,
        context: *const c_void,
        task: unsafe extern "C" fn(*const c_void, usize, *mut c_void) -> i32,
    ) -> i32;
}
struct Selection {
    kernel: Candidate,
    shift: i32,
}
struct Operation {
    kernels: Vec<Selection>,
    n: usize,
    k: usize,
    max_rows: usize,
    arch_flags: u64,
    a: Vec<u8>,
    scales: Vec<f32>,
    zeros: Vec<i32>,
}
fn permitted_arch(facts: &ArchFacts, requested: u64) -> u64 {
    // AMX's minimum 16-row tile is incompatible with unpadded A/C rows here.
    facts.supported & requested & !facts.amx
}
impl Operation {
    fn create(n: usize, k: usize, max_rows: usize, requested: u64) -> Result<Self, ()> {
        if n == 0
            || k == 0
            || k % REDUCTION != 0
            || n.checked_mul(k).is_none_or(|v| v > isize::MAX as usize)
            || max_rows > MAX_ACTIVATION_BYTES / k
        {
            return Err(());
        }
        let mut facts = ArchFacts::default();
        if unsafe { lab_dot_facts(&mut facts) } != 0 {
            return Err(());
        }
        let arch_flags = permitted_arch(&facts, requested);
        let mut kernels = Vec::with_capacity(ROWS);
        for rows in 1..=ROWS {
            let mut candidates: [Candidate; 3] = std::array::from_fn(|_| Candidate::default());
            for (index, candidate) in candidates.iter_mut().enumerate() {
                let signed = i32::from(index == 1);
                if unsafe {
                    lab_dot_query(
                        rows,
                        n.min(CHANNELS),
                        REDUCTION,
                        CHANNELS,
                        if index == 2 { 1 } else { 4 },
                        signed,
                        signed,
                        arch_flags,
                        candidate,
                    )
                } != 0
                {
                    return Err(());
                }
            }
            let mut facts = Facts {
                candidates: std::array::from_fn(|i| Metadata::from(&candidates[i])),
            };
            let selected = generated::constructor_select(&mut facts).ok_or(())?;
            let index = strategy_index(&selected);
            kernels.push(Selection {
                kernel: std::mem::take(&mut candidates[index]),
                shift: if index == 1 { 128 } else { 0 },
            });
        }
        Ok(Self {
            kernels,
            n,
            k,
            max_rows,
            arch_flags,
            a: Vec::new(),
            scales: Vec::new(),
            zeros: Vec::new(),
        })
    }
    fn run(&mut self, v: &Invocation) -> Result<(), ()> {
        let rows = v.rows;
        let (n, k) = (self.n, self.k);
        if rows > self.max_rows
            || !v.weight.valid(n * k / 2, 1)
            || v.weight.stride0 != 1
            || !v.scales.valid(k / REDUCTION, n)
            || !v.zero.valid(1, 1)
            || unsafe { *v.zero.at::<i32>(0, 0) } != 0
        {
            return Err(());
        }
        if rows == 0 {
            return Ok(());
        }
        if !v.x.valid(k, rows)
            || !v.y.valid(n, rows)
            || (n > 1 && v.y.stride0 != 1)
            || (rows > 1 && v.y.stride1 < n as isize)
        {
            return Err(());
        }
        let dot = &self.kernels[rows.min(ROWS) - 1];
        self.a.resize(rows * k, 0);
        self.scales.resize(rows, 0.0);
        self.zeros.resize(rows, 0);
        for m in 0..rows {
            let (mut lo, mut hi) = (0.0f32, 0.0f32);
            for r in 0..k {
                let x = unsafe { *v.x.at::<f32>(r, m) };
                if !x.is_finite() {
                    return Err(());
                }
                lo = lo.min(x);
                hi = hi.max(x);
            }
            let range = hi - lo;
            let scale = if range == 0.0 { 1.0 } else { range / 255.0 };
            if !scale.is_finite() || scale <= 0.0 {
                return Err(());
            }
            let inverse = if range == 0.0 { 1.0 } else { 255.0 / range };
            let zero = ((-lo * inverse).clamp(0.0, 255.0) + 0.5) as i32;
            let quant_inverse = 1.0 / scale;
            for r in 0..k {
                let x = unsafe { *v.x.at::<f32>(r, m) };
                self.a[m * k + r] = (((x * quant_inverse).round_ties_even() + zero as f32)
                    .clamp(0.0, 255.0) as i32
                    - dot.shift) as u8;
            }
            self.scales[m] = scale;
            self.zeros[m] = zero - dot.shift;
        }
        let work = Work {
            operation: self,
            invocation: v,
        };
        if unsafe {
            lab_dot_parallel(
                v.thread_pool,
                n.div_ceil(CHANNELS),
                (&work as *const Work<'_>).cast(),
                task,
            )
        } != 0
        {
            return Err(());
        }
        Ok(())
    }
}

#[repr(C, align(64))]
struct Scratch {
    b: [i8; REDUCTION * CHANNELS],
    sums: [i32; CHANNELS],
    c: [i32; ROWS * CHANNELS],
}
struct Work<'a> {
    operation: &'a Operation,
    invocation: &'a Invocation,
}
impl Work<'_> {
    unsafe fn run(&self, task: usize, state: *mut c_void) -> Result<(), ()> {
        let op = self.operation;
        let v = self.invocation;
        let dot = &op.kernels[v.rows.min(ROWS) - 1];
        let block_m = ROWS.min(dot.kernel.block_m);
        let first_n = task * CHANNELS;
        let width = CHANNELS.min(op.n - first_n);
        let mut scratch = Scratch {
            b: [0; REDUCTION * CHANNELS],
            sums: [0; CHANNELS],
            c: [0; ROWS * CHANNELS],
        };
        for g in 0..op.k / REDUCTION {
            scratch.b.fill(0);
            scratch.sums.fill(0);
            for c in 0..width {
                let scale = unsafe { *v.scales.at::<f32>(g, first_n + c) };
                if !scale.is_finite() || scale <= 0.0 {
                    return Err(());
                }
                for r in (0..REDUCTION).step_by(8) {
                    let offset = ((first_n + c) * op.k + g * REDUCTION + r) / 2;
                    let source = unsafe {
                        std::slice::from_raw_parts(v.weight.data.cast::<u8>().add(offset), 4)
                    };
                    let mut codes = u32::from_le_bytes(source.try_into().unwrap()) as u64;
                    codes = (codes | (codes << 16)) & 0x0000ffff0000ffff;
                    codes = (codes | (codes << 8)) & 0x00ff00ff00ff00ff;
                    codes = (codes | (codes << 4)) & 0x0f0f0f0f0f0f0f0f;
                    let signs = codes & 0x0808080808080808;
                    const SUM_LANES: u64 = 0x0101010101010101;
                    scratch.sums[c] += (codes.wrapping_mul(SUM_LANES) >> 56) as i32
                        - 16 * ((signs >> 3).wrapping_mul(SUM_LANES) >> 56) as i32;
                    codes |= signs * 30;
                    for j in 0..8 {
                        let target = if dot.kernel.tile_k == 4 {
                            ((r + j) / 4) * CHANNELS * 4 + c * 4 + j % 4
                        } else {
                            (r + j) * CHANNELS + c
                        };
                        scratch.b[target] = (codes >> (8 * j)) as u8 as i8;
                    }
                }
            }
            for first_m in (0..v.rows).step_by(block_m) {
                let height = block_m.min(v.rows - first_m);
                if unsafe {
                    lab_dot_invoke(
                        dot.kernel.handle,
                        height,
                        width,
                        REDUCTION,
                        op.k,
                        op.a.as_ptr().add(first_m * op.k + g * REDUCTION),
                        CHANNELS,
                        scratch.b.as_ptr(),
                        CHANNELS * 4,
                        scratch.c.as_mut_ptr(),
                        state,
                    )
                } != 0
                {
                    return Err(());
                }
                for m in 0..height {
                    for c in 0..width {
                        let acc =
                            scratch.c[m * CHANNELS + c] - op.zeros[first_m + m] * scratch.sums[c];
                        let result = acc as f32
                            * (op.scales[first_m + m]
                                * unsafe { *v.scales.at::<f32>(g, first_n + c) });
                        let out = unsafe { v.y.at::<f32>(first_n + c, first_m + m) };
                        // Same group accumulation order, no FMA/reassociation.
                        unsafe {
                            *out = result + if g != 0 { *out } else { 0.0 };
                        }
                    }
                }
            }
        }
        Ok(())
    }
}

fn boundary(f: impl FnOnce() -> Result<(), ()>) -> i32 {
    match catch_unwind(AssertUnwindSafe(f)) {
        Ok(Ok(())) => 0,
        _ => 1,
    }
}
unsafe extern "C" fn task(context: *const c_void, index: usize, state: *mut c_void) -> i32 {
    // Slinky joins all tasks before returning. Each task exclusively owns a
    // channel tile; operation storage is only read while workers are active.
    boundary(|| unsafe { (&*context.cast::<Work<'_>>()).run(index, state) })
}
#[no_mangle]
unsafe extern "C" fn lab_blockwise_create(
    n: usize,
    k: usize,
    max_rows: usize,
    flags: u64,
    out: *mut *mut c_void,
) -> i32 {
    if out.is_null() {
        return 1;
    }
    unsafe {
        *out = ptr::null_mut();
    }
    boundary(|| {
        let op = Operation::create(n, k, max_rows, flags)?;
        unsafe {
            *out = Box::into_raw(Box::new(op)).cast();
        }
        Ok(())
    })
}
#[no_mangle]
unsafe extern "C" fn lab_blockwise_delete(p: *mut c_void) {
    let _ = boundary(|| {
        if !p.is_null() {
            unsafe {
                drop(Box::from_raw(p.cast::<Operation>()));
            }
        }
        Ok(())
    });
}
#[no_mangle]
unsafe extern "C" fn lab_blockwise_run(p: *mut c_void, v: *const Invocation) -> i32 {
    if p.is_null() || v.is_null() {
        return 1;
    }
    boundary(|| unsafe { (&mut *p.cast::<Operation>()).run(&*v) })
}
#[no_mangle]
unsafe extern "C" fn lab_blockwise_info(p: *const c_void, rows: usize, out: *mut Info) -> i32 {
    if p.is_null() || out.is_null() {
        return 1;
    }
    boundary(|| {
        let op = unsafe { &*p.cast::<Operation>() };
        let dot = &op.kernels[rows.clamp(1, ROWS) - 1];
        unsafe {
            *out = Info {
                tile_k: dot.kernel.tile_k,
                activation_shift: dot.shift as usize,
                block_m: dot.kernel.block_m.min(ROWS),
                prepared_queries: ROWS * 3,
                activation_bytes: op.a.capacity()
                    + op.scales.capacity() * 4
                    + op.zeros.capacity() * 4,
                worker_scratch_bytes: std::mem::size_of::<Scratch>(),
                arch_flags: op.arch_flags,
                kernel_name: lab_dot_name(dot.kernel.handle),
            };
        }
        Ok(())
    })
}

#[cfg(test)]
mod tests {
    use super::*;
    fn metadata(m: usize, k: usize) -> Metadata {
        Metadata {
            present: true,
            block_m: 8,
            tile_m: m,
            tile_n: 8,
            tile_k: k,
        }
    }
    #[test]
    fn selection_and_incompatible_tiles() {
        for (candidates, expected) in [
            ([metadata(1, 4), metadata(1, 4), metadata(1, 1)], 0),
            ([Metadata::default(), metadata(1, 4), metadata(1, 1)], 1),
            (
                [Metadata::default(), Metadata::default(), metadata(1, 1)],
                2,
            ),
            ([metadata(16, 4), metadata(1, 4), metadata(1, 1)], 1),
        ] {
            assert_eq!(
                strategy_index(&generated::constructor_select(&mut Facts { candidates }).unwrap()),
                expected
            );
        }
        assert!(generated::constructor_select(&mut Facts {
            candidates: [Metadata::default(); 3]
        })
        .is_none());
    }
    #[test]
    fn synthetic_isa_flags_only_remove_features() {
        let f = ArchFacts {
            supported: 0b111,
            amx: 0b100,
        };
        assert_eq!(permitted_arch(&f, u64::MAX), 0b011);
        assert_eq!(permitted_arch(&f, 0b1001), 0b001);
    }
    #[test]
    fn callback_contains_panics() {
        assert_eq!(boundary(|| panic!("injected worker failure")), 1);
    }
}
