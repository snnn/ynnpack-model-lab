// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
// Link-time interception for diagnostics only; never linked into timing binary.
#include <atomic>
#include <iostream>
#include <mutex>
#include <set>
#include <string>

#include "ynnpack/kernels/dot/dot.h"
namespace {
std::atomic<bool> active{false};
std::mutex mutex;
std::set<std::string> seen;
const char* Name(ynn::dot_kernel_fn fn) {
#define YNN_DOT_KERNEL(arch, name, ...) \
  if (fn == ynn::name) return #name;
#include "ynnpack/kernels/dot/kernels.inc"
#undef YNN_DOT_KERNEL
  return "unknown";
}
}  // namespace
void RecurrentDiagnosticActive(bool value) { active = value; }
#ifdef __ANDROID__
#define DOT_SYMBOL                                                           \
  "_ZN3ynn14get_dot_kernelERKNS_8dot_typeERKNS_15dot_cost_modelsERKNS_9dot_" \
  "shapeENS_16dot_packed_"                                                   \
  "shapeEjNSt6__ndk18optionalIbEEmi"
#else
#define DOT_SYMBOL                                                           \
  "_ZN3ynn14get_dot_kernelERKNS_8dot_typeERKNS_15dot_cost_modelsERKNS_9dot_" \
  "shapeENS_16dot_packed_"                                                   \
  "shapeEjSt8optionalIbEmi"
#endif
ynn::dot_kernel RealDot(const ynn::dot_type&, const ynn::dot_cost_models&,
                        const ynn::dot_shape&, ynn::dot_packed_shape, uint32_t,
                        std::optional<bool>, uint64_t,
                        int) asm("__real_" DOT_SYMBOL);
ynn::dot_kernel WrappedDot(const ynn::dot_type&, const ynn::dot_cost_models&,
                           const ynn::dot_shape&, ynn::dot_packed_shape,
                           uint32_t, std::optional<bool>, uint64_t,
                           int) asm("__wrap_" DOT_SYMBOL);
ynn::dot_kernel WrappedDot(const ynn::dot_type& type,
                           const ynn::dot_cost_models& costs,
                           const ynn::dot_shape& shape,
                           ynn::dot_packed_shape packed, uint32_t flags,
                           std::optional<bool> transpose, uint64_t arch,
                           int threads) {
  auto kernel =
      RealDot(type, costs, shape, packed, flags, transpose, arch, threads);
  if (active && kernel.kernel) {
    std::string message =
        std::string("executing_dot=") + Name(kernel.kernel) +
        " m=" + std::to_string(shape.m) + " n=" + std::to_string(shape.n) +
        " k=" + std::to_string(shape.k1 * shape.k2 * shape.k3) +
        " threads=" + std::to_string(threads) +
        " tile_k=" + std::to_string(kernel.tile_k) +
        " flags=" + std::to_string(kernel.flags);
    std::lock_guard<std::mutex> lock(mutex);
    if (seen.insert(message).second) std::cerr << message << "\n";
  }
  return kernel;
}
