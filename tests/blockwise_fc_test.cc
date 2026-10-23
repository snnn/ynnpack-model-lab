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
  auto check = [](uint64_t flags, size_t tile_k, size_t shift) {
    void* raw = nullptr;
    Require(!lab_blockwise_create(131, 256, 17, flags, &raw),
            "Rust preparation failed");
    std::shared_ptr<void> operation(raw, lab_blockwise_delete);
    for (size_t rows = 1; rows <= 17; ++rows) {
      LabBlockwiseInfo info{};
      Require(!lab_blockwise_info(raw, rows, &info),
              "Missing prepared descriptor");
      Require(
          !tile_k || (info.tile_k == tile_k && info.activation_shift == shift),
          "Unexpected runtime ISLE selection");
      Require(info.prepared_queries == 24 && info.worker_scratch_bytes == 8704,
              "Descriptor/scratch contract changed");
      Require(!(info.arch_flags & ~ynn::get_supported_arch_flags()),
              "Unsupported ISA selected");
      if (rows == 1 || rows == 8)
        std::cout << "selection flags=" << info.arch_flags << " rows=" << rows
                  << " kernel=" << info.kernel_name << " tile_k=" << info.tile_k
                  << " shift=" << info.activation_shift << '\n';
    }
  };
  check(0, 1, 0);
  check(UINT64_MAX, 0, 0);
#ifdef YNN_ARCH_X86_AVX2
  if (ynn::is_arch_supported(ynn::arch_flag::avx2))
    check(ynn::arch_flag::avx2, 4, 128);
#endif
#ifdef YNN_ARCH_ARM_NEONDOT
  if (ynn::is_arch_supported(ynn::arch_flag::neondot))
    check(ynn::arch_flag::neondot, 4, 128);
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
      if (m % 5 == 4)  // Exact half-way rounding, with scale one.
        input[m * k + r] = r == 0       ? 0.0f
                           : r == k - 1 ? 255.0f
                                        : float(r % 200) + 0.5f;
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
             {std::pair<size_t, size_t>{1, 32}, {7, 64}, {131, 256}, {256, 32}})
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
