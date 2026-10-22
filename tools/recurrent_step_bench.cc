// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
// Prepared primitive graphs, unchanged custom kernels, independent FP64 oracle.
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>

#include "recurrent_step_generated.h"
#include "tools/recurrent_step_native.h"
#ifdef LAB_STEP_GGML
#include "ggml-cpu.h"
#include "ggml.h"
#endif

using Clock = std::chrono::steady_clock;
struct Geometry {
  int b, hk, hv, dk, dv;
  bool arbitrary;
};
const Geometry geometries[] = {
    {1, 16, 32, 128, 128, false}, {1, 1, 1, 5, 7, false},
    {2, 2, 4, 5, 3, false},       {2, 2, 4, 5, 3, true},
    {1, 2, 4, 31, 33, false},     {1, 2, 4, 129, 17, false}};
struct Fixture {
  Geometry d;
  int rows;
  float scale;
  std::vector<float> q, k, v, g, beta, initial, y, a, b;
  float* final = nullptr;
  size_t Q() const { return d.b * d.hk * d.dk; }
  size_t V() const { return d.b * d.hv * d.dv; }
  size_t H() const { return d.b * d.hv; }
  size_t S() const { return H() * d.dk * d.dv; }
  int head(int h) const {
    return d.arbitrary ? (h + 1) % d.hk : h / (d.hv / d.hk);
  }
  Fixture(int geometry, int t, int stress)
      : d(geometries[geometry]),
        rows(t),
        scale(1 / std::sqrt(double(d.dk))),
        q(t * Q()),
        k(q.size()),
        v(t * V()),
        g(t * H()),
        beta(g.size()),
        initial(S()),
        y(t * V() + 16, 999),
        a(S() + 16, 999),
        b(a) {
    std::mt19937 rng(354);
    // Exact 24-bit mapping avoids library-specific uniform_real_distribution
    // rounding at endpoints. mt19937 itself has a standardized integer stream.
    auto dist = [](std::mt19937& random) {
      return (int32_t(random() >> 8) - (1 << 23)) * 0x1p-24f;
    };
    for (auto* x : {&q, &k, &v, &initial})
      for (auto& f : *x) f = dist(rng);
    for (auto* x : {&q, &k})
      for (size_t r = 0; r < x->size(); r += d.dk) {
        double norm = 1e-6;
        for (int i = 0; i < d.dk; ++i)
          norm += double((*x)[r + i]) * (*x)[r + i];
        for (int i = 0; i < d.dk; ++i) (*x)[r + i] /= std::sqrt(norm);
      }
    for (auto& f : g) f = -std::abs(dist(rng));
    for (auto& f : beta) f = dist(rng) + .5f;
    if (stress == 1 || stress == 2) {
      for (size_t i = 0; i < g.size(); ++i) {
        g[i] = i % 3 == 0 ? -80.f : i % 3 == 1 ? -1e-7f : -.5f;
        beta[i] = i % 2;
      }
      if (stress == 2) std::fill(initial.begin(), initial.end(), 0);
    }
    if (stress == 3) {
      std::fill(q.begin(), q.end(), scale);
      std::fill(k.begin(), k.end(), scale);
      std::fill(g.begin(), g.end(), 0);
      std::fill(beta.begin(), beta.end(), 1);
    }
  }
};

struct Oracle {
  Fixture& f;
  std::vector<double> state, delta;
  double error = 0, relative = 0;
  bool strict;
  bool state_vmajor = false;
  Oracle(Fixture& f, bool strict)
      : f(f),
        state(f.initial.begin(), f.initial.end()),
        delta(f.d.dv),
        strict(strict) {}
  void Check(float got, double want) {
    const double e = std::abs(double(got) - want);
    error = std::max(error, e);
    relative = std::max(relative, e / (2e-5 + 2e-5 * std::abs(want)));
    if (!std::isfinite(got) ||
        e > (strict ? 2e-5 : 2e-5 + 2e-5 * std::abs(want)))
      throw std::runtime_error("FP64 oracle error=" + std::to_string(e));
  }
  void Step(int t, const float* actual_state) {
    const auto d = f.d;
    for (int b = 0; b < d.b; ++b)
      for (int h = 0; h < d.hv; ++h) {
        const int bh = b * d.hv + h;
        const float* k = f.k.data() + t * f.Q() + (b * d.hk + f.head(h)) * d.dk;
        const float* q = f.q.data() + t * f.Q() + (b * d.hk + f.head(h)) * d.dk;
        double* s = state.data() + bh * d.dk * d.dv;
        for (int i = 0; i < d.dk * d.dv; ++i)
          s[i] *= std::exp(double(f.g[t * f.H() + bh]));
        for (int j = 0; j < d.dv; ++j) {
          double dot = 0;
          for (int i = 0; i < d.dk; ++i) dot += k[i] * s[i * d.dv + j];
          delta[j] =
              (f.v[t * f.V() + bh * d.dv + j] - dot) * f.beta[t * f.H() + bh];
        }
        for (int i = 0; i < d.dk; ++i)
          for (int j = 0; j < d.dv; ++j) s[i * d.dv + j] += k[i] * delta[j];
        for (int j = 0; j < d.dv; ++j) {
          double y = 0;
          for (int i = 0; i < d.dk; ++i)
            y += double(q[i]) * f.scale * s[i * d.dv + j];
          Check(f.y[t * f.V() + bh * d.dv + j], y);
        }
      }
    if (actual_state) CheckState(actual_state);
  }
  void CheckState(const float* actual) {
    for (size_t h = 0; h < f.H(); ++h)
      for (int k = 0; k < f.d.dk; ++k)
        for (int v = 0; v < f.d.dv; ++v)
          Check(actual[(h * (state_vmajor ? f.d.dv : f.d.dk) +
                        (state_vmajor ? v : k)) *
                           (state_vmajor ? f.d.dk : f.d.dv) +
                       (state_vmajor ? k : v)],
                state[(h * f.d.dk + k) * f.d.dv + v]);
  }
  void Finish(int valid, const float* final) {
    CheckState(final);
    for (size_t i = valid * f.V(); i < size_t(f.rows) * f.V(); ++i)
      if (f.y[i] != 0) throw std::runtime_error("padding");
    for (auto* x : {&f.a, &f.b})
      for (size_t i = f.S(); i < x->size(); ++i)
        if ((*x)[i] != 999) throw std::runtime_error("state canary");
    for (size_t i = f.rows * f.V(); i < f.y.size(); ++i)
      if (f.y[i] != 999) throw std::runtime_error("output canary");
  }
};

class Engine {
 public:
  virtual ~Engine() = default;
  virtual void Run(int valid, Oracle* oracle = nullptr, int chunk = 0) = 0;
  virtual void Print(std::ostream&) {}
  virtual bool StateVmajor() const { return false; }
};

template <class G>
class StepEngine : public Engine {
 public:
  Fixture& f;
  G graph;
  StepEngine(Fixture& f, int geometry, int threads, uint32_t flags)
      : f(f), graph(64, flags) {
    BuildRecurrentStep(graph, geometry);
    graph.Compile(threads);
    graph.Bind("scale", &f.scale, 4);
  }
  void Run(int valid, Oracle* oracle = nullptr, int chunk = 0) override {
    if (valid < 0 || valid > f.rows) throw std::invalid_argument("valid_rows");
    float* state = f.initial.data();
    // Chunk boundaries preserve state and invocation order. They do not create
    // another graph or switch algorithms.
    if (!chunk) chunk = std::max(valid, 1);
    for (int start = 0; start < valid; start += chunk)
      for (int t = start; t < std::min(start + chunk, valid); ++t) {
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

class CustomEngine : public Engine {
 public:
  Fixture& f;
  lab_ynn::Graph graph{9};
  bool step;
  int32_t n;
  CustomEngine(Fixture& f, int threads, bool step) : f(f), step(step) {
    if (f.d.b != 1)
      throw std::invalid_argument("custom diagnostic requires batch one");
    const auto d = f.d;
    const size_t T = step ? 1 : f.rows;
    std::vector<std::vector<size_t>> shapes = {
        {1, T, size_t(d.hk), size_t(d.dk)},
        {1, T, size_t(d.hk), size_t(d.dk)},
        {1, T, size_t(d.hv), size_t(d.dv)},
        {1, T, size_t(d.hv)},
        {1, T, size_t(d.hv)},
        {1, size_t(d.hv), size_t(d.dk), size_t(d.dv)},
        {},
        {1, T, size_t(d.hv), size_t(d.dv)},
        {1, size_t(d.hv), size_t(d.dk), size_t(d.dv)}};
    for (int i = 0; i < 9; ++i)
      graph.Tensor(i, std::to_string(i),
                   i == 6 ? ynn_type_int32 : ynn_type_fp32, shapes[i],
                   i < 7 ? 1 : 2, nullptr);
    std::vector<int64_t> heads(d.hv);
    for (int h = 0; h < d.hv; ++h) heads[h] = f.head(h);
    graph.GatedDeltaRule(0, 1, 2, 3, 4, 5, 6, 7, 8, heads,
                         1 / std::sqrt(double(d.dk)));
    graph.Compile(threads);
    graph.Bind("6", &n, 4);
  }
  void Run(int valid, Oracle* oracle = nullptr, int = 0) override {
    if (valid < 0 || valid > f.rows) throw std::invalid_argument("valid_rows");
    n = step ? 1 : valid;
    float* state = f.initial.data();
    const int calls = step ? valid : 1;
    for (int i = 0; i < calls; ++i) {
      int t = step ? i : 0, rows = step ? 1 : f.rows;
      float* next = i % 2 ? f.b.data() : f.a.data();
      float* ptrs[] = {f.q.data() + t * f.Q(),
                       f.k.data() + t * f.Q(),
                       f.v.data() + t * f.V(),
                       f.g.data() + t * f.H(),
                       f.beta.data() + t * f.H(),
                       state,
                       nullptr,
                       f.y.data() + t * f.V(),
                       next};
      const size_t lengths[] = {rows * f.Q(),
                                rows * f.Q(),
                                rows * f.V(),
                                rows * f.H(),
                                rows * f.H(),
                                f.S(),
                                0,
                                rows * f.V(),
                                f.S()};
      for (int j = 0; j < 9; ++j)
        if (j != 6) graph.Bind(std::to_string(j), ptrs[j], lengths[j] * 4);
      graph.Run();
      state = next;
      if (oracle && step) oracle->Step(t, state);
    }
    if (oracle && !step)
      for (int t = 0; t < valid; ++t) oracle->Step(t, nullptr);
    if (step)
      std::fill(f.y.begin() + valid * f.V(), f.y.begin() + f.rows * f.V(), 0);
    f.final = state;
  }
  void Print(std::ostream& out) override { graph.Print(out); }
};

#ifdef LAB_STEP_GGML
class LlamaEngine : public Engine {
 public:
  Fixture& f;
  ggml_context* ctx = nullptr;
  ggml_threadpool_t pool = nullptr;
  ggml_cgraph* graph;
  ggml_cplan plan{};
  ggml_tensor* result;
  std::vector<uint8_t> work;
  int nh(int h) const {
    return (h % (f.d.hv / f.d.hk)) * f.d.hk + h / (f.d.hv / f.d.hk);
  }
  LlamaEngine(Fixture& f, int threads) : f(f) {
    const auto d = f.d;
    if (d.b != 1 || d.dk != d.dv || d.arbitrary)
      throw std::invalid_argument("ggml geometry");
    ctx = ggml_init(
        {(f.q.size() * 2 + f.v.size() * 2 + f.g.size() * 2 + f.S() * 2) * 4 +
             (size_t(32) << 20),
         nullptr, false});
    if (!ctx) throw std::runtime_error("ggml context");
    auto tensor = [&](int a, int b, int c, int e, const std::vector<float>& x) {
      auto* t = ggml_new_tensor_4d(ctx, GGML_TYPE_F32, a, b, c, e);
      std::copy(x.begin(), x.end(), static_cast<float*>(t->data));
      return t;
    };
    std::vector<float> v(f.v.size()), g(f.g.size()), beta(g.size()), s(f.S());
    for (int t = 0; t < f.rows; ++t)
      for (int h = 0; h < d.hv; ++h) {
        g[t * d.hv + nh(h)] = f.g[t * d.hv + h];
        beta[t * d.hv + nh(h)] = f.beta[t * d.hv + h];
        for (int j = 0; j < d.dv; ++j)
          v[(t * d.hv + nh(h)) * d.dv + j] = f.v[(t * d.hv + h) * d.dv + j];
      }
    for (int h = 0; h < d.hv; ++h)
      for (int i = 0; i < d.dk; ++i)
        for (int j = 0; j < d.dv; ++j)
          s[(nh(h) * d.dv + j) * d.dk + i] =
              f.initial[(h * d.dk + i) * d.dv + j];
    result = ggml_gated_delta_net(
        ctx, tensor(d.dk, d.hk, f.rows, 1, f.q),
        tensor(d.dk, d.hk, f.rows, 1, f.k), tensor(d.dv, d.hv, f.rows, 1, v),
        tensor(1, d.hv, f.rows, 1, g), tensor(1, d.hv, f.rows, 1, beta),
        tensor(d.dk, d.dv, d.hv, 1, s), 1);
    graph = ggml_new_graph(ctx);
    ggml_build_forward_expand(graph, result);
    auto params = ggml_threadpool_params_default(threads);
    pool = ggml_threadpool_new(&params);
    plan = ggml_graph_plan(graph, threads, pool);
    work.resize(plan.work_size);
    plan.work_data = work.data();
  }
  ~LlamaEngine() {
    if (pool) ggml_threadpool_free(pool);
    if (ctx) ggml_free(ctx);
  }
  void Run(int valid, Oracle* oracle = nullptr, int = 0) override {
    if (valid != f.rows) throw std::invalid_argument("ggml full rows only");
    if (ggml_graph_compute(graph, &plan) != GGML_STATUS_SUCCESS)
      throw std::runtime_error("ggml compute");
    // Oracle layout conversions are outside all timed runs. Timed output/state
    // remain materialized in ggml's native layout, as in the existing
    // benchmark.
    if (oracle) {
      const auto d = f.d;
      const float* r = static_cast<float*>(result->data);
      for (int t = 0; t < f.rows; ++t)
        for (int h = 0; h < d.hv; ++h)
          for (int j = 0; j < d.dv; ++j)
            f.y[(t * d.hv + h) * d.dv + j] = r[(t * d.hv + nh(h)) * d.dv + j];
      r += f.rows * f.V();
      for (int h = 0; h < d.hv; ++h)
        for (int i = 0; i < d.dk; ++i)
          for (int j = 0; j < d.dv; ++j)
            f.a[(h * d.dk + i) * d.dv + j] = r[(nh(h) * d.dv + j) * d.dk + i];
      for (int t = 0; t < f.rows; ++t) oracle->Step(t, nullptr);
    }
    f.final = f.a.data();
  }
};
#endif

#ifdef LAB_RECURRENT_FOLLOWUP
#include "recurrent_followup_engines.h"
#endif

int main(int argc, char** argv) {
  try {
    std::map<std::string, std::string> args;
    for (int i = 1; i < argc; ++i) {
      std::string s = argv[i];
      const auto p = s.find('=');
      if (s.substr(0, 2) != "--" || p == s.npos)
        throw std::invalid_argument("use --key=value");
      args[s.substr(2, p - 2)] = s.substr(p + 1);
    }
    auto integer = [&](std::string n, int v) {
      return args.count(n) ? std::stoi(args[n]) : v;
    };
    const std::string engine =
        args.count("engine") ? args["engine"] : "step-native";
    const int rows = integer("rows", 128), threads = integer("threads", 4),
              geometry = integer("geometry", 0), valid = integer("valid", rows),
              stress = integer("stress", 0), batches = integer("batches", 5),
              duration = integer("duration-ms", 200);
    if (rows < 1 || rows > 4096 || threads < 1 || geometry < 0 ||
        geometry >= 6 || valid < 0 || valid > rows || batches < 0 ||
        duration < 1)
      throw std::invalid_argument("invalid arguments");
    const uint32_t flags =
        YNN_FLAG_NO_EXCESS_PRECISION |
        (integer("consistent", 0) ? YNN_FLAG_CONSISTENT_ARITHMETIC : 0);
    Fixture f(geometry, rows, stress);
    const auto initial = f.initial;
    const std::vector<std::vector<float>> protected_inputs = {f.q, f.k, f.v,
                                                              f.g, f.beta};
    auto setup = Clock::now();
    std::unique_ptr<Engine> runner;
#ifdef LAB_RECURRENT_FOLLOWUP
    if (engine.rfind("vmajor", 0) == 0 || engine.rfind("chunk", 0) == 0)
      runner = MakeFollowup(engine, f, geometry, threads, flags);
    else
#endif
        if (engine == "step-native")
      runner =
          std::make_unique<StepEngine<StepNative>>(f, geometry, threads, flags);
    else if (engine == "step-adapter")
      runner = std::make_unique<StepEngine<lab_ynn::Graph>>(f, geometry,
                                                            threads, flags);
    else if (engine == "custom" || engine == "custom-step")
      runner =
          std::make_unique<CustomEngine>(f, threads, engine == "custom-step");
#ifdef LAB_STEP_GGML
    else if (engine == "llama")
      runner = std::make_unique<LlamaEngine>(f, threads);
#endif
    else
      throw std::invalid_argument("unknown engine");
    const double setup_ms =
        std::chrono::duration<double, std::milli>(Clock::now() - setup).count();
    if (args.count("pipeline")) {
      std::ofstream out(args["pipeline"]);
      runner->Print(out);
    }
    Oracle oracle(f, geometry == 0 && !stress);
    oracle.state_vmajor = runner->StateVmajor();
    runner->Run(valid, &oracle);
    oracle.Finish(valid, f.final);
    const auto expected_y = f.y;
    const std::vector<float> expected_state(f.final, f.final + f.S());
    if (engine != "llama") {
      // Independent repeated request and split-sequence controls; no state
      // reset copies are included in timing because every run starts from
      // initial.
      runner->Run(valid, nullptr, 128);
      if (f.y != expected_y ||
          !std::equal(expected_state.begin(), expected_state.end(), f.final))
        throw std::runtime_error("reset/chunk equivalence");
      for (int bad : {-1, rows + 1}) {
        bool rejected = false;
        try {
          runner->Run(bad);
        } catch (const std::invalid_argument&) {
          rejected = true;
        }
        if (!rejected || f.y != expected_y ||
            !std::equal(expected_state.begin(), expected_state.end(), f.final))
          throw std::runtime_error("invalid request changed output");
      }
    }
    if (f.initial != initial) throw std::runtime_error("input state mutated");
    if (protected_inputs !=
        std::vector<std::vector<float>>{f.q, f.k, f.v, f.g, f.beta})
      throw std::runtime_error("input tensor mutated");
    if (args.count("pipeline")) {
      std::ofstream out(args["pipeline"]);
      runner->Print(out);
    }
    if (batches)
      for (int i = 0; i < 5; ++i) runner->Run(valid);
    std::vector<double> samples;
    for (int b = 0; b < batches; ++b) {
      size_t count = 0;
      const auto start = Clock::now();
      double ms;
      do {
        runner->Run(valid);
        ++count;
        ms = std::chrono::duration<double, std::milli>(Clock::now() - start)
                 .count();
      } while (ms < duration);
      samples.push_back(ms / count);
    }
    std::cout << std::setprecision(10) << "{\"engine\":\"" << engine
              << "\",\"rows\":" << rows << ",\"valid\":" << valid
              << ",\"threads\":" << threads << ",\"geometry\":" << geometry
              << ",\"stress\":" << stress << ",\"flags\":" << flags
              << ",\"max_abs\":" << oracle.error
              << ",\"max_scaled_error\":" << oracle.relative
              << ",\"setup_ms\":" << setup_ms << ",\"ms\":[";
    for (size_t i = 0; i < samples.size(); ++i)
      std::cout << (i ? "," : "") << samples[i];
    std::cout << "]}\n";
  } catch (const std::exception& e) {
    std::cerr << e.what() << "\n";
    return 1;
  }
  return 0;
}
