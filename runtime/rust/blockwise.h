// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
#pragma once
#include <cstddef>
#include <cstdint>

// Internal C ABI: native kernel catalogue and Slinky execution plumbing only.
// Kernel compatibility, dispatch order, packing and task geometry live in Rust.
extern "C" {
struct LabDotFacts {
  uint64_t supported, amx;
};
struct LabDotCandidate {
  void* handle;
  size_t block_m, tile_m, tile_n, tile_k;
};
struct LabBlockwiseView {
  const void* data;
  size_t extent0, extent1;
  ptrdiff_t stride0, stride1;  // In elements, measured from logical (0,0).
};
struct LabBlockwiseCall {
  LabBlockwiseView x, weight, scales, zero, y;
  size_t rows;
  void* thread_pool;  // Borrowed until synchronous parallel_for returns.
};
struct LabBlockwiseInfo {
  size_t tile_k, activation_shift, block_m, prepared_queries;
  size_t activation_bytes, worker_scratch_bytes;
  uint64_t arch_flags;
  const char* kernel_name;  // Static backend name, valid for process lifetime.
};
int32_t lab_dot_facts(LabDotFacts*) noexcept;
int32_t lab_dot_query(size_t rows, size_t channels, size_t reduction,
                      size_t packed_channels, size_t tile_k, int32_t signed_a,
                      int32_t symmetric_b, uint64_t flags,
                      LabDotCandidate*) noexcept;
void lab_dot_delete(void*) noexcept;
const char* lab_dot_name(const void*) noexcept;
int32_t lab_dot_invoke(const void* handle, size_t rows, size_t channels,
                       size_t reduction, size_t a_stride, const uint8_t* a,
                       size_t b_stride, const int8_t* b, size_t c_stride,
                       int32_t* c, void* state) noexcept;
using LabDotTask = int32_t (*)(const void*, size_t, void*);
int32_t lab_dot_parallel(void* pool, size_t tasks, const void* context,
                         LabDotTask task) noexcept;

// Rust-owned prepared operation. Every entry point contains Rust panics.
int32_t lab_blockwise_create(size_t channels, size_t reduction, size_t max_rows,
                             uint64_t allowed_arch, void** out) noexcept;
void lab_blockwise_delete(void*) noexcept;
int32_t lab_blockwise_run(void*, const LabBlockwiseCall*) noexcept;
int32_t lab_blockwise_info(const void*, size_t rows,
                           LabBlockwiseInfo*) noexcept;
}
