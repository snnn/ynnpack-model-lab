// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>

#include "runtime/ynnpack_recurrent_cpu.h"
namespace {
void Check(double got, double want) {
  if (!std::isfinite(got) ||
      std::abs(got - want) > 2e-5 + 2e-5 * std::abs(want))
    throw std::runtime_error("independent FP64 oracle mismatch");
}
void Recurrence(int D, int V, int T, int valid, bool strided) {
  std::mt19937 rng(33 + D + V + T);
  std::uniform_real_distribution<float> r(-0.2f, 0.2f);
  int step = strided ? 2 : 1;
  std::vector<float> q(T * D), k(q.size()), v(T * V * step), g(T), beta(T),
      initial(D * V * step), next(initial.size() + 16, 999),
      y(v.size() + 16, 999);
  for (auto* z : {&q, &k, &v, &initial})
    for (auto& x : *z) x = r(rng);
  for (int t = 0; t < T; ++t) {
    g[t] = t % 3 == 0 ? -80.f : t % 3 == 1 ? -1e-7f : -0.5f;
    beta[t] = t % 2 ? 1 : 0;
  }
  const auto initial_copy = initial;
  lab_ynn::GatedDeltaCpuArgs a{{q.data(), D, 1},
                               {k.data(), D, 1},
                               {v.data(), V * step, step},
                               {initial.data(), V * step, step},
                               {y.data(), V * step, step},
                               {next.data(), V * step, step},
                               g.data(),
                               beta.data(),
                               1,
                               1,
                               D,
                               T,
                               valid,
                               1 / std::sqrt(float(D))};
  for (int pass = 0; pass < 2; ++pass) {
    for (int j = 0; j < V; j += 32)
      lab_ynn::GatedDeltaCpuTile(a, j, std::min(j + 32, V));
    std::vector<double> s(D * V), delta(V);
    for (int i = 0; i < D * V; ++i) s[i] = initial[i * step];
    for (int t = 0; t < T; ++t) {
      if (t < valid) {
        for (auto& x : s) x *= std::exp(double(g[t]));
        for (int j = 0; j < V; ++j) {
          double dot = 0;
          for (int i = 0; i < D; ++i) dot += s[i * V + j] * k[t * D + i];
          delta[j] = (v[(t * V + j) * step] - dot) * beta[t];
        }
        for (int i = 0; i < D; ++i)
          for (int j = 0; j < V; ++j) s[i * V + j] += k[t * D + i] * delta[j];
      }
      for (int j = 0; j < V; ++j) {
        double out = 0;
        if (t < valid)
          for (int i = 0; i < D; ++i)
            out += s[i * V + j] * q[t * D + i] * a.scale;
        Check(y[(t * V + j) * step], out);
      }
    }
    for (int i = 0; i < D * V; ++i) Check(next[i * step], s[i]);
  }
  if (initial != initial_copy) throw std::runtime_error("input state mutated");
  for (size_t i = initial.size(); i < next.size(); ++i) Check(next[i], 999);
  for (size_t i = v.size(); i < y.size(); ++i) Check(y[i], 999);
  if (strided) {
    for (size_t i = 1; i < initial.size(); i += 2) Check(next[i], 999);
    for (size_t i = 1; i < v.size(); i += 2) Check(y[i], 999);
  }
}
void Conv(int C, int T, int valid, bool strided, bool silu) {
  const int K = 4, step = strided ? 2 : 1;
  std::mt19937 rng(C + T);
  std::uniform_real_distribution<float> r(-2, 2);
  std::vector<float> x(T * C * step), h((K - 1) * C * step), w(K * C * step),
      y(x.size() + 16, 999), next(h.size() + 16, 999);
  for (auto* z : {&x, &h, &w})
    for (auto& f : *z) f = r(rng);
  const auto old = h;
  lab_ynn::CausalConvCpuArgs a{{x.data(), C * step, step},
                               {h.data(), C * step, step},
                               {w.data(), C * step, step},
                               {y.data(), C * step, step},
                               {next.data(), C * step, step},
                               T,
                               valid,
                               K,
                               silu};
  lab_ynn::CausalConvCpuTile(a, 0, C);
  auto read = [&](int row, int c) {
    return row < K - 1 ? h[(row * C + c) * step]
                       : x[((row - K + 1) * C + c) * step];
  };
  for (int t = 0; t < T; ++t)
    for (int c = 0; c < C; ++c) {
      double sum = 0;
      float ordered_fma = 0;
      for (int k = 0; k < K; ++k) {
        sum += double(read(t + k, c)) * w[(k * C + c) * step];
        ordered_fma =
            std::fma(read(t + k, c), w[(k * C + c) * step], ordered_fma);
      }
      if (silu) sum *= 1 / (1 + std::exp(-sum));
      Check(y[(t * C + c) * step], sum);
      if (!silu && y[(t * C + c) * step] != ordered_fma)
        throw std::runtime_error("convolution ordered FMA changed");
    }
  for (int t = 0; t < K - 1; ++t)
    for (int c = 0; c < C; ++c)
      Check(next[(t * C + c) * step], read(valid + t, c));
  if (h != old) throw std::runtime_error("history mutated");
  for (size_t i = h.size(); i < next.size(); ++i) Check(next[i], 999);
  for (size_t i = x.size(); i < y.size(); ++i) Check(y[i], 999);
}
}  // namespace
int main() {
  try {
    for (bool strided : {false, true})
      for (int T : {1, 7, 128})
        for (int valid : {0, 1, T - 1, T}) {
          for (auto dims : {std::pair<int, int>{5, 3}, {128, 128}, {129, 67}})
            Recurrence(dims.first, dims.second, T, valid, strided);
          for (int C : {3, 67, 256})
            for (bool silu : {false, true}) Conv(C, T, valid, strided, silu);
        }
    std::cout << "FP64 recurrence/convolution, tails, strides, valid rows, "
                 "reset, canaries passed; avx2="
              << lab_ynn::RecurrentCpuHasAvx2() << '\n';
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    return 1;
  }
}
