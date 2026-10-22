// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
#pragma once
#include "recurrent_followup_generated.h"

// Included after the shared benchmark fixture/oracle definitions.
class VmajorEngine : public Engine {
 public:
  Fixture& f;
  StepNative graph{256, YNN_FLAG_NO_EXCESS_PRECISION};
  std::vector<float> initial;
  VmajorEngine(Fixture& f, int geometry, int threads, int variant,
               uint32_t flags)
      : f(f), graph(256, flags), initial(f.S()) {
    for (size_t h = 0; h < f.H(); ++h)
      for (int k = 0; k < f.d.dk; ++k)
        for (int v = 0; v < f.d.dv; ++v)
          initial[(h * f.d.dv + v) * f.d.dk + k] =
              f.initial[(h * f.d.dk + k) * f.d.dv + v];
    BuildRecurrentFollowup(graph, variant, geometry);
    graph.Compile(threads);
    graph.Bind("scale", &f.scale, 4);
  }
  bool StateVmajor() const override { return true; }
  void Run(int valid, Oracle* oracle = nullptr, int = 0) override {
    if (valid < 0 || valid > f.rows) throw std::invalid_argument("valid_rows");
    float* state = initial.data();
    for (int t = 0; t < valid; ++t) {
      float* next = t % 2 ? f.b.data() : f.a.data();
      graph.Bind("q", f.q.data() + t * f.Q(), f.Q() * 4);
      graph.Bind("k", f.k.data() + t * f.Q(), f.Q() * 4);
      graph.Bind("v", f.v.data() + t * f.V(), f.V() * 4);
      graph.Bind("decay", f.g.data() + t * f.H(), f.H() * 4);
      graph.Bind("beta", f.beta.data() + t * f.H(), f.H() * 4);
      graph.Bind("state", state, f.S() * 4);
      graph.Bind("next_state", next, f.S() * 4);
      graph.Bind("output", f.y.data() + t * f.V(), f.V() * 4);
      graph.Run();
      state = next;
      if (oracle) oracle->Step(t, state);
    }
    std::fill(f.y.begin() + valid * f.V(), f.y.begin() + f.rows * f.V(), 0);
    f.final = state;
  }
  void Print(std::ostream& out) override { graph.Print(out); }
};

class ChunkEngine : public Engine {
 public:
  Fixture& f;
  int size;
  StepNative graph;
  std::vector<float> lower, strict, identity, q, k, v, decay, beta, y;
  std::map<int, std::vector<float>> solve_masks;
  float zero = 0;
  ChunkEngine(Fixture& f, int geometry, int threads, int variant,
              uint32_t flags)
      : f(f),
        size(1 << (variant + 2)),
        graph(256, flags),
        lower(size * size),
        strict(size * size),
        identity(size * size),
        q(size * f.Q()),
        k(q.size()),
        v(size * f.V()),
        decay(size * f.H()),
        beta(decay.size()),
        y(size * f.V()) {
    for (int i = 0; i < size; ++i)
      for (int j = 0; j < size; ++j) {
        lower[i * size + j] = j <= i;
        strict[i * size + j] = j < i;
        identity[i * size + j] = j == i;
      }
    BuildRecurrentFollowup(graph, variant, geometry);
    graph.Compile(threads);
    graph.Bind("scale", &f.scale, 4);
    graph.Bind("zero", &zero, 4);
    graph.Bind("lower", lower.data(), lower.size() * 4);
    graph.Bind("strict", strict.data(), strict.size() * 4);
    graph.Bind("identity", identity.data(), identity.size() * 4);
    for (int width = 1; width < size; width *= 2) {
      auto& mask = solve_masks[width];
      mask.resize(size * size);
      for (int begin = 0; begin < size; begin += 2 * width)
        for (int i = begin + width; i < begin + 2 * width; ++i)
          for (int j = begin; j < begin + width; ++j) mask[i * size + j] = 1;
      graph.Bind("solve_mask" + std::to_string(width), mask.data(),
                 mask.size() * 4);
    }
  }
  void Run(int valid, Oracle* oracle = nullptr, int = 0) override {
    if (valid < 0 || valid > f.rows) throw std::invalid_argument("valid_rows");
    float* state = f.initial.data();
    for (int t = 0, call = 0; t < valid; t += size, ++call) {
      int real = std::min(size, valid - t);
      float* next = call % 2 ? f.b.data() : f.a.data();
      auto bind = [&](const char* name, std::vector<float>& source,
                      std::vector<float>& padded, size_t stride) {
        float* ptr = source.data() + t * stride;
        if (real < size) {
          std::copy_n(ptr, real * stride, padded.data());
          std::fill(padded.begin() + real * stride, padded.end(), 0);
          ptr = padded.data();
        }
        graph.Bind(name, ptr, size * stride * 4);
      };
      bind("q", f.q, q, f.Q());
      bind("k", f.k, k, f.Q());
      bind("v", f.v, v, f.V());
      bind("decay", f.g, decay, f.H());
      bind("beta", f.beta, beta, f.H());
      graph.Bind("state", state, f.S() * 4);
      graph.Bind("next_state", next, f.S() * 4);
      graph.Bind("output", real < size ? y.data() : f.y.data() + t * f.V(),
                 size * f.V() * 4);
      graph.Run();
      if (real < size)
        std::copy_n(y.data(), real * f.V(), f.y.data() + t * f.V());
      state = next;
      if (oracle) {
        for (int j = 0; j < real; ++j) oracle->Step(t + j, nullptr);
        oracle->CheckState(state);
      }
    }
    std::fill(f.y.begin() + valid * f.V(), f.y.begin() + f.rows * f.V(), 0);
    f.final = state;
  }
  void Print(std::ostream& out) override { graph.Print(out); }
};

// Dependence-aware loop interchange: independent state tiles outside time.
// Every worker owns its prepared runtime; no concurrent runtime invocation or
// nested backend pool. State remains V-major across every token and tile.
class TiledEngine : public Engine {
 public:
  Fixture& f;
  int workers;
  std::vector<float> initial;
  std::vector<std::unique_ptr<StepNative>> full, tail;
  std::unique_ptr<slinky::thread_pool_impl> pool;
  TiledEngine(Fixture& f, int geometry, int threads, uint32_t flags)
      : f(f), workers(threads), initial(f.S()) {
    for (size_t h = 0; h < f.H(); ++h)
      for (int k = 0; k < f.d.dk; ++k)
        for (int v = 0; v < f.d.dv; ++v)
          initial[(h * f.d.dv + v) * f.d.dk + k] =
              f.initial[(h * f.d.dk + k) * f.d.dv + v];
    for (int worker = 0; worker < threads; ++worker)
      for (int variant : {5, 6}) {
        auto graph = std::make_unique<StepNative>(256, flags);
        BuildRecurrentFollowup(*graph, variant, geometry);
        graph->Compile(1);
        graph->Bind("scale", &f.scale, 4);
        (variant == 5 ? full : tail).push_back(std::move(graph));
      }
    if (threads > 1)
      pool = std::make_unique<slinky::thread_pool_impl>(threads - 1);
  }
  bool StateVmajor() const override { return true; }
  void Run(int valid, Oracle* oracle = nullptr, int = 0) override {
    if (valid < 0 || valid > f.rows) throw std::invalid_argument("valid_rows");
    const int tiles = (f.d.dv + 31) / 32;
    auto work = [&](size_t worker) {
      for (size_t task = worker; task < f.H() * tiles; task += workers) {
        const size_t h = task / tiles, v = task % tiles * 32;
        const int width = std::min(32, f.d.dv - int(v));
        StepNative& graph =
            *(width == std::min(32, f.d.dv) ? full : tail)[worker];
        const size_t state_offset = (h * f.d.dv + v) * f.d.dk;
        const size_t key_offset =
            (h / f.d.hv * f.d.hk + f.head(h % f.d.hv)) * f.d.dk;
        float* state = initial.data() + state_offset;
        for (int t = 0; t < valid; ++t) {
          float* next = (t % 2 ? f.b.data() : f.a.data()) + state_offset;
          graph.Bind("q", f.q.data() + t * f.Q() + key_offset, f.d.dk * 4);
          graph.Bind("k", f.k.data() + t * f.Q() + key_offset, f.d.dk * 4);
          graph.Bind("v", f.v.data() + t * f.V() + h * f.d.dv + v, width * 4);
          graph.Bind("decay", f.g.data() + t * f.H() + h, 4);
          graph.Bind("beta", f.beta.data() + t * f.H() + h, 4);
          graph.Bind("state", state, width * f.d.dk * 4);
          graph.Bind("next_state", next, width * f.d.dk * 4);
          graph.Bind("output", f.y.data() + t * f.V() + h * f.d.dv + v,
                     width * 4);
          graph.Run();
          state = next;
        }
      }
    };
    if (valid) {
      if (pool)
        pool->parallel_for(workers, work);
      else
        work(0);
    }
    std::fill(f.y.begin() + valid * f.V(), f.y.begin() + f.rows * f.V(), 0);
    f.final = valid ? (valid % 2 ? f.a.data() : f.b.data()) : initial.data();
    if (oracle)
      for (int t = 0; t < valid; ++t) oracle->Step(t, nullptr);
  }
  void Print(std::ostream& out) override { full[0]->Print(out); }
};

inline std::unique_ptr<Engine> MakeFollowup(const std::string& name, Fixture& f,
                                            int geometry, int threads,
                                            uint32_t flags) {
  if (name == "vmajor-tiled")
    return std::make_unique<TiledEngine>(f, geometry, threads, flags);
  if (name == "vmajor" || name == "vmajor-reduce")
    return std::make_unique<VmajorEngine>(
        f, geometry, threads, name == "vmajor-reduce" ? 1 : 0, flags);
  for (int variant = 2; variant <= 4; ++variant)
    if (name == "chunk" + std::to_string(1 << (variant + 2)))
      return std::make_unique<ChunkEngine>(f, geometry, threads, variant,
                                           flags);
  throw std::invalid_argument("unknown followup engine");
}
