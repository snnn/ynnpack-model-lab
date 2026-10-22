// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
#include "ynnpack_recurrent_cpu.h"

#include <algorithm>
#include <cmath>
#if (defined(__x86_64__) || defined(__i386__)) && \
    (defined(__GNUC__) || defined(__clang__))
#include <immintrin.h>
#define RECURRENT_AVX2 1
#endif

namespace lab_ynn {
bool RecurrentCpuHasAvx2() {
#ifdef RECURRENT_AVX2
  static const bool available = __builtin_cpu_supports("avx2");
  return available;
#else
  return false;
#endif
}

void GatedDeltaCpuScalarTile(const GatedDeltaCpuArgs& a, int64_t begin,
                             int64_t end) {
  for (int64_t j = begin; j < end; ++j) {
    for (int64_t i = 0; i < a.dk; ++i) a.next(i, j) = a.initial(i, j);
    for (int64_t t = 0; t < a.valid; ++t) {
      const float decay = std::exp(a.decay[t * a.decay_stride]);
      float dot = 0;
      for (int64_t i = 0; i < a.dk; ++i) {
        a.next(i, j) *= decay;
        dot += a.next(i, j) * a.k(t, i);
      }
      const float delta = (a.v(t, j) - dot) * a.beta[t * a.beta_stride];
      float y = 0;
      for (int64_t i = 0; i < a.dk; ++i) {
        a.next(i, j) += a.k(t, i) * delta;
        y += a.next(i, j) * (a.q(t, i) * a.scale);
      }
      a.y(t, j) = y;
    }
    for (int64_t t = a.valid; t < a.rows; ++t) a.y(t, j) = 0;
  }
}

#ifdef RECURRENT_AVX2
// Four independent accumulators vectorize output columns, preserving the
// original ordered reduction over key dimensions. Compile without contraction.
__attribute__((target("avx2"))) static void GatedDeltaAvx2(
    const GatedDeltaCpuArgs& a, int64_t begin, int64_t end) {
  int64_t j = begin;
  alignas(64) float local[128 * 32];
  for (; j + 32 <= end; j += 32) {
    // Compact working tiles avoid L1 set conflicts from 512-byte state rows.
    // Decode reads initial directly and writes next once, with no working copy.
    const bool decode = a.valid == 1;
    const bool compact = !decode && a.dk <= 128;
    float* state = compact ? local : a.next.data + j;
    const int64_t stride = compact ? 32 : a.next.row;
    if (!decode)
      for (int64_t i = 0; i < a.dk; ++i)
        for (int u = 0; u < 4; ++u)
          _mm256_storeu_ps(
              state + i * stride + u * 8,
              _mm256_loadu_ps(a.initial.data + i * a.initial.row + j + u * 8));
    for (int64_t t = 0; t < a.valid; ++t) {
      const auto decay = _mm256_set1_ps(std::exp(a.decay[t * a.decay_stride]));
      __m256 delta[4] = {_mm256_setzero_ps(), _mm256_setzero_ps(),
                         _mm256_setzero_ps(), _mm256_setzero_ps()};
      for (int64_t i = 0; i < a.dk; ++i) {
        const auto k = _mm256_set1_ps(a.k(t, i));
        for (int u = 0; u < 4; ++u) {
          const float* src =
              decode ? a.initial.data + i * a.initial.row + j + u * 8
                     : state + i * stride + u * 8;
          const auto s = _mm256_mul_ps(_mm256_loadu_ps(src), decay);
          if (!decode) _mm256_storeu_ps(state + i * stride + u * 8, s);
          delta[u] = _mm256_add_ps(delta[u], _mm256_mul_ps(s, k));
        }
      }
      const auto beta = _mm256_set1_ps(a.beta[t * a.beta_stride]);
      for (int u = 0; u < 4; ++u)
        delta[u] = _mm256_mul_ps(
            _mm256_sub_ps(_mm256_loadu_ps(a.v.data + t * a.v.row + j + u * 8),
                          delta[u]),
            beta);
      __m256 y[4] = {_mm256_setzero_ps(), _mm256_setzero_ps(),
                     _mm256_setzero_ps(), _mm256_setzero_ps()};
      for (int64_t i = 0; i < a.dk; ++i) {
        const auto k = _mm256_set1_ps(a.k(t, i)),
                   q = _mm256_set1_ps(a.q(t, i) * a.scale);
        for (int u = 0; u < 4; ++u) {
          auto previous =
              decode ? _mm256_mul_ps(
                           _mm256_loadu_ps(a.initial.data + i * a.initial.row +
                                           j + u * 8),
                           decay)
                     : _mm256_loadu_ps(state + i * stride + u * 8);
          const auto s = _mm256_add_ps(previous, _mm256_mul_ps(k, delta[u]));
          _mm256_storeu_ps(decode ? a.next.data + i * a.next.row + j + u * 8
                                  : state + i * stride + u * 8,
                           s);
          y[u] = _mm256_add_ps(y[u], _mm256_mul_ps(s, q));
        }
      }
      for (int u = 0; u < 4; ++u)
        _mm256_storeu_ps(a.y.data + t * a.y.row + j + u * 8, y[u]);
    }
    if (compact)
      for (int64_t i = 0; i < a.dk; ++i)
        for (int u = 0; u < 4; ++u)
          _mm256_storeu_ps(a.next.data + i * a.next.row + j + u * 8,
                           _mm256_loadu_ps(state + i * stride + u * 8));
    for (int64_t t = a.valid; t < a.rows; ++t)
      for (int u = 0; u < 4; ++u)
        _mm256_storeu_ps(a.y.data + t * a.y.row + j + u * 8,
                         _mm256_setzero_ps());
  }
  GatedDeltaCpuScalarTile(a, j, end);
}
#endif

void GatedDeltaCpuTile(const GatedDeltaCpuArgs& a, int64_t begin, int64_t end) {
#ifdef RECURRENT_AVX2
  if (RecurrentCpuHasAvx2() && a.initial.col == 1 && a.next.col == 1 &&
      a.v.col == 1 && a.y.col == 1) {
    GatedDeltaAvx2(a, begin, end);
    return;
  }
#endif
  GatedDeltaCpuScalarTile(a, begin, end);
}

#ifdef RECURRENT_AVX2
// Match the ordered FP32 FMA used by the qualified YNNPACK dot convolution.
// This is explicit even though the recurrence translation unit disables
// implicit contraction: changing convolution rounding perturbs INT8 FC inputs.
__attribute__((target("avx2,fma"))) static void CausalConvAvx2(
    const CausalConvCpuArgs& a, int64_t begin, int64_t end) {
  for (int64_t t = 0; t < a.rows; ++t) {
    int64_t c = begin;
    for (; c + 8 <= end; c += 8) {
      auto sum = _mm256_setzero_ps();
      for (int64_t k = 0; k < a.kernel; ++k) {
        const int64_t row = t + k;
        const float* x =
            row < a.kernel - 1
                ? a.history.data + row * a.history.row + c
                : a.input.data + (row - a.kernel + 1) * a.input.row + c;
        sum = _mm256_fmadd_ps(
            _mm256_loadu_ps(x),
            _mm256_loadu_ps(a.filter.data + k * a.filter.row + c), sum);
      }
      _mm256_storeu_ps(a.output.data + t * a.output.row + c, sum);
    }
    for (; c < end; ++c) {
      float sum = 0;
      for (int64_t k = 0; k < a.kernel; ++k) {
        int64_t row = t + k;
        sum = std::fma(row < a.kernel - 1 ? a.history(row, c)
                                          : a.input(row - a.kernel + 1, c),
                       a.filter(k, c), sum);
      }
      a.output(t, c) = sum;
    }
  }
}
#endif
void CausalConvCpuTile(const CausalConvCpuArgs& a, int64_t begin, int64_t end) {
#ifdef RECURRENT_AVX2
  if (RecurrentCpuHasAvx2() && __builtin_cpu_supports("fma") &&
      a.input.col == 1 && a.history.col == 1 && a.filter.col == 1 &&
      a.output.col == 1)
    CausalConvAvx2(a, begin, end);
  else
#endif
    for (int64_t t = 0; t < a.rows; ++t)
      for (int64_t c = begin; c < end; ++c) {
        float sum = 0;
        for (int64_t k = 0; k < a.kernel; ++k) {
          const int64_t row = t + k;
          sum = std::fma(row < a.kernel - 1 ? a.history(row, c)
                                            : a.input(row - a.kernel + 1, c),
                         a.filter(k, c), sum);
        }
        a.output(t, c) = sum;
      }
  if (a.silu)
    for (int64_t t = 0; t < a.rows; ++t)
      for (int64_t c = begin; c < end; ++c) {
        const float x = a.output(t, c);
        a.output(t, c) = x * (1.0f / (1.0f + std::exp(-x)));
      }
  for (int64_t t = 0; t < a.kernel - 1; ++t)
    for (int64_t c = begin; c < end; ++c) {
      const int64_t row = a.valid + t;
      a.next(t, c) = row < a.kernel - 1 ? a.history(row, c)
                                        : a.input(row - a.kernel + 1, c);
    }
}
}  // namespace lab_ynn
