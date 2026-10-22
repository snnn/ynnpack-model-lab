// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
#pragma once

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <stdexcept>

#include "ynnpack/kernels/dot/dot.h"

namespace lab_ynn::detail {

struct BlockwiseDot {
  static constexpr size_t kRows = 8, kChannels = 128, kReduction = 32;
  ynn::dot_kernel kernel;
  int32_t activation_shift;
};

inline BlockwiseDot SelectBlockwiseDot(
    size_t rows, size_t channels, uint64_t arch_flags
#if __has_include("ynnpack/kernels/dot/cost_model/cost_model.h")
    ,
    const ynn::dot_cost_models& cost_models = ynn::get_dot_cost_models()
#endif
) {
#ifdef YNN_ARCH_X86
  // AMX needs padded 16-row tiles. This adapter supplies at most eight rows
  // without padding A or C, so it must not enter the AMX candidate set.
  arch_flags &= ~uint64_t(ynn::arch_flag::amxint8);
#endif
  auto select = [&](ynn_type activation_type, int tile_k, uint32_t flags) {
    return ynn::get_dot_kernel({activation_type, ynn_type_int8, ynn_type_int32},
#if __has_include("ynnpack/kernels/dot/cost_model/cost_model.h")
                               cost_models,
#endif
                               {std::min(rows, BlockwiseDot::kRows),
                                std::min(channels, BlockwiseDot::kChannels),
                                BlockwiseDot::kReduction, 1, 1},
                               {BlockwiseDot::kChannels, tile_k}, flags, false,
                               arch_flags);
  };
  auto compatible = [](const ynn::dot_kernel& kernel, int tile_k) {
    return kernel.kernel && kernel.tile_m == 1 && kernel.tile_k == tile_k &&
           kernel.block_m > 0 && kernel.tile_n > 0 &&
           BlockwiseDot::kChannels % kernel.tile_n == 0;
  };
  // Preserve the U8/I8 VNNI path where available.
  auto kernel = select(ynn_type_uint8, 4, 0);
  if (compatible(kernel, 4)) return {kernel, 0};
  // AVX2 and NEON DOT provide signed dots. Recenter both the activation codes
  // and their zero point by 128; (q - z) * w is unchanged. INT4 weights never
  // contain -128, so symmetric_b kernels are also valid.
  kernel = select(ynn_type_int8, 4, ynn::dot_flag::symmetric_b);
  if (compatible(kernel, 4)) return {kernel, 128};
  // The portable U8/I8 kernel uses one K code per N, not quartet packing.
  kernel = select(ynn_type_uint8, 1, 0);
  if (compatible(kernel, 1)) return {kernel, 0};
  throw std::runtime_error("YNNPACK has no compatible group-32 dot kernel");
}

}  // namespace lab_ynn::detail
