// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
#include "ynnpack/kernels/dot/dot.h"

#include <atomic>

#include "runtime/rust/blockwise.h"
#include "slinky/base/thread_pool.h"

extern "C" int32_t lab_dot_facts(LabDotFacts* out) noexcept {
  try {
    *out = {ynn::get_supported_arch_flags(), 0};
#ifdef YNN_ARCH_X86
    out->amx = ynn::arch_flag::amxint8;
#endif
    return 0;
  } catch (...) {
    return 1;
  }
}
extern "C" int32_t lab_dot_query(size_t rows, size_t channels, size_t reduction,
                                 size_t packed_channels, size_t tile_k,
                                 int32_t signed_a, int32_t symmetric_b,
                                 uint64_t flags,
                                 LabDotCandidate* out) noexcept {
  *out = {};
  try {
    // Never construct an executable descriptor for an unsupported ISA.
    if (flags & ~ynn::get_supported_arch_flags()) return 1;
    auto kernel = ynn::get_dot_kernel(
        {signed_a ? ynn_type_int8 : ynn_type_uint8, ynn_type_int8,
         ynn_type_int32},
#if __has_include("ynnpack/kernels/dot/cost_model/cost_model.h")
        ynn::get_dot_cost_models(),
#endif
        {rows, channels, reduction, 1, 1}, {int(packed_channels), int(tile_k)},
        symmetric_b ? ynn::dot_flag::symmetric_b : 0, false, flags);
    if (kernel.kernel) {
      out->handle = new ynn::dot_kernel(kernel);
      out->block_m = kernel.block_m;
      out->tile_m = kernel.tile_m;
      out->tile_n = kernel.tile_n;
      out->tile_k = kernel.tile_k;
    }
    return 0;
  } catch (...) {
    return 1;
  }
}
extern "C" void lab_dot_delete(void* handle) noexcept {
  delete static_cast<ynn::dot_kernel*>(handle);
}
extern "C" const char* lab_dot_name(const void* handle) noexcept {
  auto fn = static_cast<const ynn::dot_kernel*>(handle)->kernel;
  // Derive diagnostics from the backend catalogue; do not maintain a copy.
#define YNN_DOT_KERNEL(arch, name, ...) \
  if (fn == ynn::name) return #name;
#include "ynnpack/kernels/dot/kernels.inc"
#undef YNN_DOT_KERNEL
  return "unknown";
}
extern "C" int32_t lab_dot_invoke(const void* handle, size_t rows,
                                  size_t channels, size_t reduction,
                                  size_t a_stride, const uint8_t* a,
                                  size_t b_stride, const int8_t* b,
                                  size_t c_stride, int32_t* c,
                                  void* state) noexcept {
  try {
    const auto& kernel = *static_cast<const ynn::dot_kernel*>(handle);
    kernel.kernel(rows, channels, 1, 1, reduction, a_stride, 0, 0, a, 0, 0,
                  b_stride, b, c_stride, nullptr, c_stride, c,
                  static_cast<ynn::dot_kernel_state*>(state));
    return 0;
  } catch (...) {
    return 1;
  }
}
extern "C" int32_t lab_dot_parallel(void* pool, size_t tasks,
                                    const void* context,
                                    LabDotTask task) noexcept {
  try {
    std::atomic<int32_t> failed{0};
    auto work = [&](size_t index) {
      // Native state stays opaque to Rust and is destroyed on its worker.
      ynn::dot_kernel_state state;
      if (task(context, index, &state))
        failed.store(1, std::memory_order_relaxed);
    };
    if (pool && tasks > 1)
      static_cast<slinky::thread_pool*>(pool)->parallel_for(tasks, work);
    else
      for (size_t i = 0; i < tasks; ++i) work(i);
    return failed.load(std::memory_order_relaxed);
  } catch (...) {
    return 1;
  }
}
