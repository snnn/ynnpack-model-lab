// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
// Identical FP32 inputs, independent FP64 oracle, prepared CPU graphs.
#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <functional>
#include <iostream>
#include <numeric>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

#if defined(__x86_64__) || defined(__i386__)
#include <immintrin.h>
#endif

#include "ggml-cpu.h"
#include "ggml.h"
#include "runtime/ynnpack_support.h"

using Clock = std::chrono::steady_clock;
int main(int argc, char** argv) {
  try {
    const std::string engine = argc > 1 ? argv[1] : "ynn";
    const int T = argc > 2 ? std::stoi(argv[2]) : 128;
    const int threads = argc > 3 ? std::stoi(argv[3]) : 4;
    const int D = argc > 4 ? std::stoi(argv[4]) : 128;
    const int V = argc > 5 ? std::stoi(argv[5]) : D;
    const std::string cache_mode = argc > 6 ? argv[6] : "warm";
    const bool cold_state = cache_mode == "cold-state";
    const int H = 32, K = 16;
    const auto native_head = [](int h) {
      return (h % (H / K)) * K + h / (H / K);
    };
    if (T < 1 || D < 1 || V < 1 || threads < 1 ||
        (engine != "ynn" && engine != "llama") ||
        (cache_mode != "warm" && !cold_state))
      throw std::runtime_error("bad arguments");
    std::mt19937 rng(354);
    std::uniform_real_distribution<float> dist(-0.5f, 0.5f);
    std::vector<float> q(T * K * D), k(q.size()), v(T * H * V), g(T * H),
        beta(g.size()), s(H * D * V), y(v.size()), next(s.size());
    for (auto* a : {&q, &k, &v, &s})
      for (auto& f : *a) f = dist(rng);
    for (auto* a : {&q, &k})
      for (int r = 0; r < T * K; ++r) {
        double z = 1e-6;
        for (int d = 0; d < D; ++d)
          z += double((*a)[r * D + d]) * (*a)[r * D + d];
        for (int d = 0; d < D; ++d) (*a)[r * D + d] /= std::sqrt(z);
      }
    for (auto& f : g) f = -std::abs(dist(rng));
    for (auto& f : beta) f = dist(rng) + 0.5f;
    const auto initial = s;
    std::vector<double> ref(s.begin(), s.end()), expected(y.size()), delta(V);
    for (int t = 0; t < T; ++t)
      for (int h = 0; h < H; ++h) {
        double* state = ref.data() + h * D * V;
        for (int i = 0; i < D * V; ++i)
          state[i] *= std::exp(double(g[t * H + h]));
        for (int j = 0; j < V; ++j) {
          double dot = 0;
          for (int i = 0; i < D; ++i)
            dot += state[i * V + j] * k[(t * K + h / 2) * D + i];
          delta[j] = (v[(t * H + h) * V + j] - dot) * beta[t * H + h];
        }
        for (int i = 0; i < D; ++i)
          for (int j = 0; j < V; ++j)
            state[i * V + j] += k[(t * K + h / 2) * D + i] * delta[j];
        for (int j = 0; j < V; ++j)
          for (int i = 0; i < D; ++i)
            expected[(t * H + h) * V + j] += state[i * V + j] *
                                             q[(t * K + h / 2) * D + i] /
                                             std::sqrt(double(D));
      }
    lab_ynn::Graph graph(9);
    ggml_context* ctx = nullptr;
    ggml_threadpool_t pool = nullptr;
    ggml_cgraph* gg = nullptr;
    ggml_cplan plan{};
    ggml_tensor* result = nullptr;
    std::vector<unsigned char> work;
    std::function<void()> run;
    std::vector<std::pair<const void*, size_t>> state_buffers;
    int32_t valid = T;
    if (engine == "ynn") {
      const std::vector<std::vector<size_t>> shapes = {
          {1, size_t(T), K, size_t(D)},
          {1, size_t(T), K, size_t(D)},
          {1, size_t(T), H, size_t(V)},
          {1, size_t(T), H},
          {1, size_t(T), H},
          {1, H, size_t(D), size_t(V)},
          {},
          {1, size_t(T), H, size_t(V)},
          {1, H, size_t(D), size_t(V)}};
      std::vector<int64_t> heads(H);
      for (int h = 0; h < H; ++h) heads[h] = h / 2;
      for (int i = 0; i < 9; ++i)
        graph.Tensor(i, std::to_string(i),
                     i == 6 ? ynn_type_int32 : ynn_type_fp32, shapes[i],
                     i < 7 ? YNN_VALUE_FLAG_EXTERNAL_INPUT
                           : YNN_VALUE_FLAG_EXTERNAL_OUTPUT,
                     nullptr);
      graph.GatedDeltaRule(0, 1, 2, 3, 4, 5, 6, 7, 8, heads,
                           1 / std::sqrt(double(D)));
      graph.Compile(threads);
      std::vector<std::vector<float>*> buffers = {&q, &k,      &v, &g,   &beta,
                                                  &s, nullptr, &y, &next};
      for (int i = 0; i < 9; ++i) {
        if (i == 6)
          graph.Bind("6", &valid, sizeof(valid));
        else
          graph.Bind(std::to_string(i), buffers[i]->data(),
                     buffers[i]->size() * 4);
      }
      run = [&] { graph.Run(); };
      state_buffers = {{s.data(), s.size() * sizeof(float)},
                       {next.data(), next.size() * sizeof(float)}};
    } else {
      if (D != V)
        throw std::runtime_error("llama primitive requires equal widths");
      ctx = ggml_init({size_t(64) << 20, nullptr, false});
      auto tensor = [&](int64_t a, int64_t b, int64_t c, int64_t d,
                        const std::vector<float>& x) {
        auto* r = ggml_new_tensor_4d(ctx, GGML_TYPE_F32, a, b, c, d);
        std::copy(x.begin(), x.end(), static_cast<float*>(r->data));
        return r;
      };
      // ggml broadcasts h%Hk. Permute value/state heads outside timing so both
      // engines keep the same 16 Q/K heads and 32 value heads, without Q/K
      // duplication. The inverse permutation is only used by the oracle.
      std::vector<float> vn(v.size()), gn(g.size()), bn(beta.size()),
          st(s.size());
      for (int t = 0; t < T; ++t)
        for (int h = 0; h < H; ++h) {
          const int nh = native_head(h);
          gn[t * H + nh] = g[t * H + h];
          bn[t * H + nh] = beta[t * H + h];
          for (int j = 0; j < V; ++j)
            vn[(t * H + nh) * V + j] = v[(t * H + h) * V + j];
        }
      for (int h = 0; h < H; ++h)
        for (int i = 0; i < D; ++i)
          for (int j = 0; j < V; ++j)
            st[(native_head(h) * V + j) * D + i] = s[(h * D + i) * V + j];
      auto* state = tensor(D, V, H, 1, st);
      result = ggml_gated_delta_net(
          ctx, tensor(D, K, T, 1, q), tensor(D, K, T, 1, k),
          tensor(V, H, T, 1, vn), tensor(1, H, T, 1, gn),
          tensor(1, H, T, 1, bn), state, 1);
      state_buffers = {{state->data, ggml_nbytes(state)},
                       {static_cast<const float*>(result->data) + y.size(),
                        next.size() * sizeof(float)}};
      gg = ggml_new_graph(ctx);
      ggml_build_forward_expand(gg, result);
      auto params = ggml_threadpool_params_default(threads);
      pool = ggml_threadpool_new(&params);
      plan = ggml_graph_plan(gg, threads, pool);
      work.resize(plan.work_size);
      plan.work_data = work.data();
      run = [&] {
        if (ggml_graph_compute(gg, &plan) != GGML_STATUS_SUCCESS)
          throw std::runtime_error("ggml compute");
      };
    }
    run();
    if (engine == "llama") {
      const auto* r = static_cast<float*>(result->data);
      for (int t = 0; t < T; ++t)
        for (int h = 0; h < H; ++h)
          for (int j = 0; j < V; ++j)
            y[(t * H + h) * V + j] = r[(t * H + native_head(h)) * V + j];
      r += y.size();
      for (int h = 0; h < H; ++h)
        for (int i = 0; i < D; ++i)
          for (int j = 0; j < V; ++j)
            next[(h * D + i) * V + j] = r[(native_head(h) * V + j) * D + i];
    }
    double error = 0;
    for (size_t i = 0; i < y.size(); ++i) {
      if (!std::isfinite(y[i])) throw std::runtime_error("nonfinite output");
      error = std::max(error, std::abs(y[i] - expected[i]));
    }
    for (size_t i = 0; i < next.size(); ++i) {
      if (!std::isfinite(next[i])) throw std::runtime_error("nonfinite state");
      error = std::max(error, std::abs(next[i] - ref[i]));
    }
    if (!std::isfinite(error) || error > 2e-5 || s != initial)
      throw std::runtime_error("oracle/input immutability failed: " +
                               std::to_string(error));
    for (int i = 0; i < 5; ++i) run();
    auto evict_state = [&] {
#if defined(__x86_64__) || defined(__i386__)
      for (const auto& buffer : state_buffers) {
        const auto begin = reinterpret_cast<uintptr_t>(buffer.first);
        for (auto line = begin & ~uintptr_t(63); line < begin + buffer.second;
             line += 64)
          _mm_clflush(reinterpret_cast<const void*>(line));
      }
      _mm_mfence();
#else
      throw std::runtime_error("cold-state diagnostic requires x86 CLFLUSH");
#endif
    };
    std::vector<double> samples;
    for (int batch = 0; batch < 5; ++batch) {
      auto start = Clock::now();
      size_t count = 0;
      double seconds, measured = 0;
      do {
        if (cold_state) {
          // Diagnostic only: eviction is outside the kernel timer. The main
          // qualification uses the unchanged amortized warm-graph loop.
          evict_state();
          const auto begin = Clock::now();
          run();
          measured +=
              std::chrono::duration<double>(Clock::now() - begin).count();
        } else {
          run();
        }
        ++count;
        seconds = std::chrono::duration<double>(Clock::now() - start).count();
      } while (seconds < 0.2);
      samples.push_back((cold_state ? measured : seconds) * 1000 / count);
    }
    std::cout << "{\"engine\":\"" << engine << "\",\"rows\":" << T
              << ",\"threads\":" << threads << ",\"dk\":" << D
              << ",\"dv\":" << V << ",\"qk_heads\":" << K
              << ",\"value_heads\":" << H << ",\"max_abs\":" << error
              << ",\"cache_mode\":\"" << cache_mode << "\""
              << ",\"ms\":[";
    for (size_t i = 0; i < samples.size(); ++i)
      std::cout << (i ? "," : "") << samples[i];
    std::cout << "]}\n";
    if (pool) ggml_threadpool_free(pool);
    if (ctx) ggml_free(ctx);
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    return 1;
  }
}
