// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "runtime/ynnpack_support.h"

namespace {

void Require(bool condition, const char* message) {
  if (!condition) throw std::runtime_error(message);
}

void CheckSelection() {
  using lab_ynn::detail::SelectBlockwiseDot;
  auto portable = SelectBlockwiseDot(8, 131, 0);
  Require(portable.kernel.tile_k == 1 && portable.activation_shift == 0,
          "portable U8 dot must use unpacked K");
#ifdef YNN_ARCH_X86_AVX2
  auto avx2 = SelectBlockwiseDot(8, 131, ynn::arch_flag::avx2);
  Require(avx2.kernel.tile_k == 4 && avx2.activation_shift == 128,
          "AVX2 without VNNI must recenter to signed codes");
#endif
#ifdef YNN_ARCH_ARM_NEONDOT
  auto neon = SelectBlockwiseDot(8, 131, ynn::arch_flag::neondot);
  Require(neon.kernel.tile_k == 4 && neon.activation_shift == 128,
          "NEON DOT must recenter to signed codes");
#endif
#if defined(YNN_ARCH_X86_AMXINT8) && defined(YNN_ARCH_X86_AVX512VNNI) && \
    __has_include("ynnpack/kernels/dot/cost_model/cost_model.h")
  // Selection only: this also runs on hosts that cannot execute AMX/VNNI.
  // Make AMX the cheapest candidate to catch accepting it and rejecting its
  // tile shape later, which made execution depend on the CI host's CPU.
  ynn::dot_cost_models costs;
  costs.x86_amx_uint8 = {0, 0, 0, 0};
  auto amx_host = SelectBlockwiseDot(
      8, 131, ynn::arch_flag::amxint8 | ynn::arch_flag::avx512vnni, costs);
  Require(amx_host.kernel.tile_m == 1 && amx_host.kernel.tile_k == 4 &&
              amx_host.activation_shift == 0,
          "AMX must not displace a compatible VNNI kernel");
#endif
}

void CheckNumerics(size_t rows, size_t n, size_t k, size_t threads,
                   uint64_t arch_flags) {
  // Bindings require a non-null address even for a zero-byte logical tensor.
  std::vector<float> input(std::max(size_t(1), rows * k)), scales(n * k / 32);
  std::vector<int8_t> weights(n * k);
  std::vector<uint8_t> packed(n * k / 2, 0);
  std::vector<float> output(rows * n + 16, 123456.0f);
  int32_t zero = 0;
  for (size_t i = 0; i < weights.size(); ++i) {
    weights[i] = int((i * 13 + i / 11) % 16) - 8;
    packed[i / 2] |= uint8_t(weights[i] & 15) << ((i % 2) * 4);
  }
  for (size_t i = 0; i < scales.size(); ++i)
    scales[i] = float(1 + i % 7) / 64.0f;
  for (size_t m = 0; m < rows; ++m)
    for (size_t r = 0; r < k; ++r) {
      const float value = float((r * 37 + m * 11) % 255) / 16.0f;
      // Mixed, zero, positive-only and negative-only rows exercise both ends
      // of the asymmetric code range and zero points 0 and 255.
      input[m * k + r] = m % 4 == 0   ? value - 8.0f
                         : m % 4 == 1 ? 0.0f
                         : m % 4 == 2 ? value
                                      : -value;
    }
  lab_ynn::Graph graph(5);
  graph.Tensor(0, "x", ynn_type_fp32, {rows, k}, YNN_VALUE_FLAG_EXTERNAL_INPUT,
               nullptr);
  graph.PackedTensor(1, "w", 4, {n, k}, 0, packed.data());
  graph.Tensor(2, "s", ynn_type_fp32, {n, k / 32}, 0, scales.data());
  graph.Tensor(3, "z", ynn_type_int32, {1, 1}, 0, &zero);
  graph.Tensor(4, "y", ynn_type_fp32, {rows, n}, YNN_VALUE_FLAG_EXTERNAL_OUTPUT,
               nullptr);
  graph.BlockwiseFullyConnected(0, 1, 2, 3, 4, 32, arch_flags);
  graph.Compile(threads);
  graph.Bind("x", input.data(), rows * k * sizeof(float));
  graph.Bind("y", output.data(), rows * n * sizeof(float));
  graph.Run();

  // Independent reference: unsigned per-row quantization, then direct
  // (code - zero_point) * signed_weight for each logical group. No kernel
  // packing, signed recentering, or weight-sum correction is used here.
  for (size_t m = 0; m < rows; ++m) {
    float lo = 0, hi = 0;
    for (size_t r = 0; r < k; ++r) {
      lo = std::min(lo, input[m * k + r]);
      hi = std::max(hi, input[m * k + r]);
    }
    const float scale = hi == lo ? 1.0f : (hi - lo) / 255.0f;
    const float inverse = hi == lo ? 1.0f : 255.0f / (hi - lo);
    const int32_t zp = int32_t(std::clamp(-lo * inverse, 0.0f, 255.0f) + 0.5f);
    std::vector<int32_t> codes(k);
    for (size_t r = 0; r < k; ++r)
      codes[r] = int32_t(std::clamp(
          std::nearbyint(input[m * k + r] * (1.0f / scale)) + float(zp), 0.0f,
          255.0f));
    for (size_t c = 0; c < n; ++c) {
      float expected = 0;
      for (size_t g = 0; g < k / 32; ++g) {
        int32_t sum = 0;
        for (size_t r = g * 32; r < (g + 1) * 32; ++r)
          sum += (codes[r] - zp) * weights[c * k + r];
        expected += float(sum) * (scale * scales[c * (k / 32) + g]);
      }
      Require(output[m * n + c] == expected, "blockwise FC reference mismatch");
    }
  }
  for (size_t i = rows * n; i < output.size(); ++i)
    Require(output[i] == 123456.0f, "blockwise FC wrote past the output");
}

}  // namespace

int main() {
  try {
    CheckSelection();
    std::vector<uint64_t> masks{0, ynn::get_supported_arch_flags()};
#ifdef YNN_ARCH_X86_AVX2
    if (ynn::is_arch_supported(ynn::arch_flag::avx2))
      masks.push_back(ynn::arch_flag::avx2);
#endif
#ifdef YNN_ARCH_ARM_NEONDOT
    if (ynn::is_arch_supported(ynn::arch_flag::neondot))
      masks.push_back(ynn::arch_flag::neondot);
#endif
    for (auto mask : masks) {
      for (size_t rows : {0, 1, 3, 8, 9, 17})
        for (auto shape :
             {std::pair<size_t, size_t>{7, 64}, {131, 256}, {256, 32}})
          for (size_t threads : {1, 4})
            CheckNumerics(rows, shape.first, shape.second, threads, mask);
      std::cout << "blockwise FC arch_flags=" << mask
                << ": exact reference match\n";
    }
  } catch (const std::exception& error) {
    std::cerr << error.what() << '\n';
    return 1;
  }
}
