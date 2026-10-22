// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
// Convolution + replacement history + SiLU, in each runtime's native layout.
#include <chrono>
#include <cmath>
#include <functional>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

#include "ggml-cpu.h"
#include "ggml.h"
#include "runtime/ynnpack_support.h"
using Clock = std::chrono::steady_clock;
int main(int argc, char** argv) {
  try {
    const std::string engine = argc > 1 ? argv[1] : "ynn";
    const int T = argc > 2 ? std::stoi(argv[2]) : 128,
              threads = argc > 3 ? std::stoi(argv[3]) : 4, C = 8192, K = 4;
    const bool fuse = argc > 4 ? std::stoi(argv[4]) : false;
    if (T < 1 || threads < 1 ||
        (engine != "ynn" && engine != "generic" && engine != "llama"))
      throw std::runtime_error("arguments");
    std::mt19937 rng(31);
    std::uniform_real_distribution<float> random(-0.5, 0.5);
    std::vector<float> x(T * C), h(3 * C), w(4 * C), y(T * C), next(3 * C);
    for (auto* z : {&x, &h, &w})
      for (auto& f : *z) f = random(rng);
    auto hx = [&](int t, int c) {
      return t < 3 ? h[t * C + c] : x[(t - 3) * C + c];
    };
    lab_ynn::Graph g(12);
    ggml_context* ctx = nullptr;
    ggml_threadpool_t pool = nullptr;
    ggml_cplan plan{};
    ggml_cgraph* gg = nullptr;
    ggml_tensor *gy = nullptr, *gn = nullptr;
    std::vector<uint8_t> work;
    std::function<void()> run;
    if (engine != "llama") {
      const std::vector<std::vector<size_t>> shapes = {{1, size_t(T), C},
                                                       {1, 3, C},
                                                       {1, 4, 1, C},
                                                       {1, size_t(T), 1, C},
                                                       {1, 3, C},
                                                       {1, size_t(T + 3), C},
                                                       {1, size_t(T + 3), 1, C},
                                                       {1, size_t(T), 1, C},
                                                       {1, size_t(T), 1, C}};
      for (int i = 0; i < 9; ++i)
        g.Tensor(i, std::to_string(i), ynn_type_fp32, shapes[i],
                 i < 2              ? YNN_VALUE_FLAG_EXTERNAL_INPUT
                 : i == 3 || i == 4 ? YNN_VALUE_FLAG_EXTERNAL_OUTPUT
                                    : 0,
                 i == 2 ? w.data() : nullptr);
      if (engine == "ynn")
        g.CausalDepthwiseConv(0, 2, 1, fuse ? 3 : 7, 4, T, fuse);
      else {
        g.Concat({1, 0}, 5, 1);
        g.ExpandDims(5, 6, {2});
        g.Conv2D(6, 2, YNN_INVALID_VALUE_ID, 7, {4, 1}, {1, 1}, {1, 1}, false,
                 true, C, 1);
        g.Slice(5, 4, {0, T, 0}, {1, 3, C});
      }
      if (engine == "generic" || !fuse) {
        g.Unary(ynn_unary_sigmoid, 7, 8);
        g.Binary(ynn_binary_multiply, 7, 8, 3);
      }
      g.Compile(threads);
      g.Bind("0", x.data(), x.size() * 4);
      g.Bind("1", h.data(), h.size() * 4);
      g.Bind("3", y.data(), y.size() * 4);
      g.Bind("4", next.data(), next.size() * 4);
      run = [&] { g.Run(); };
    } else {
      ctx = ggml_init({size_t(64) << 20, nullptr, false});
      auto transposed = [&](int rows, const std::vector<float>& v) {
        auto* z = ggml_new_tensor_2d(ctx, GGML_TYPE_F32, rows, C);
        float* p = static_cast<float*>(z->data);
        for (int c = 0; c < C; ++c)
          for (int t = 0; t < rows; ++t) p[c * rows + t] = v[t * C + c];
        return z;
      };
      auto* joined = ggml_concat(ctx, transposed(3, h), transposed(T, x), 0);
      gy = ggml_silu(ctx, ggml_ssm_conv(ctx, joined, transposed(4, w)));
      gn = ggml_cont(ctx, ggml_view_2d(ctx, joined, 3, C, joined->nb[1],
                                       T * sizeof(float)));
      gg = ggml_new_graph(ctx);
      ggml_build_forward_expand(gg, gy);
      ggml_build_forward_expand(gg, gn);
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
      std::copy_n(static_cast<float*>(gy->data), y.size(), y.data());
      const float* p = static_cast<float*>(gn->data);
      for (int t = 0; t < 3; ++t)
        for (int c = 0; c < C; ++c) next[t * C + c] = p[c * 3 + t];
    }
    double error = 0;
    for (int t = 0; t < T; ++t)
      for (int c = 0; c < C; ++c) {
        double sum = 0;
        for (int k = 0; k < K; ++k) sum += double(hx(t + k, c)) * w[k * C + c];
        sum *= 1 / (1 + std::exp(-sum));
        if (!std::isfinite(y[t * C + c]))
          throw std::runtime_error("nonfinite output");
        error = std::max(error, std::abs(sum - y[t * C + c]));
      }
    for (int t = 0; t < 3; ++t)
      for (int c = 0; c < C; ++c)
        if (next[t * C + c] != hx(T + t, c))
          throw std::runtime_error("history mismatch");
    if (error > 2e-5) throw std::runtime_error("convolution oracle mismatch");
    for (int i = 0; i < 5; ++i) run();
    std::vector<double> samples;
    for (int i = 0; i < 5; ++i) {
      auto start = Clock::now();
      int count = 0;
      double sec;
      do {
        run();
        ++count;
        sec = std::chrono::duration<double>(Clock::now() - start).count();
      } while (sec < 0.2);
      samples.push_back(sec * 1000 / count);
    }
    std::cout << "{\"engine\":\"" << engine << "\",\"rows\":" << T
              << ",\"threads\":" << threads
              << ",\"fused_silu\":" << (fuse ? "true" : "false")
              << ",\"max_abs\":" << error << ",\"ms\":[";
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
