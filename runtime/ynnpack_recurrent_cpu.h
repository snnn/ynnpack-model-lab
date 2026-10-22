// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
#pragma once
#include <cstdint>

namespace lab_ynn {
// Element strides, not byte strides. All views begin at logical index zero.
struct RecurrentRead {
  const float* data;
  int64_t row, col;
  float operator()(int64_t r, int64_t c) const {
    return data[r * row + c * col];
  }
};
struct RecurrentWrite {
  float* data;
  int64_t row, col;
  float& operator()(int64_t r, int64_t c) const {
    return data[r * row + c * col];
  }
};
struct GatedDeltaCpuArgs {
  RecurrentRead q, k, v, initial;
  RecurrentWrite y, next;
  const float *decay, *beta;
  int64_t decay_stride, beta_stride, dk, rows, valid;
  float scale;
};
// Independent value-column tiles; next is working storage and never aliases
// initial. No allocation, persistent globals, or internal thread pool.
void GatedDeltaCpuTile(const GatedDeltaCpuArgs&, int64_t begin, int64_t end);
void GatedDeltaCpuScalarTile(const GatedDeltaCpuArgs&, int64_t begin,
                             int64_t end);
bool RecurrentCpuHasAvx2();
struct CausalConvCpuArgs {
  RecurrentRead input, history, filter;
  RecurrentWrite output, next;
  int64_t rows, valid, kernel;
  bool silu;
};
// Ordered FP32 FMA over kernel taps, including scalar tails/fallback. This
// preserves the qualified YNNPACK dot convolution's rounding contract.
void CausalConvCpuTile(const CausalConvCpuArgs&, int64_t begin, int64_t end);
}  // namespace lab_ynn
