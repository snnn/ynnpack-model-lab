// Copyright 2026 The LiteRT Authors.
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// https://www.apache.org/licenses/LICENSE-2.0
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "c2048_h1_w512.h"
#include "c2048_h1_w512_q4.h"
#include "c2048_h2_w0.h"
#include "c2048_h2_w1.h"
#include "c2048_h2_w512.h"
#include "c2048_h2_w512_q8.h"
#include "c8448_h2_w0_q8.h"
#include "c8448_h2_w512.h"
#include "c8448_h4_w512.h"

namespace {
void Expect(bool ok, const std::string& message) {
  if (!ok) throw std::runtime_error(message);
}
float Source(int64_t h, int64_t t, int64_t d, int salt) {
  return std::sin(float(h * 79 + t * 17 + d * 11 + salt) * 0.013f) * 0.6f;
}

void Test(std::unique_ptr<lab_ynn::Graph> g, int c, int heads, int window,
          int threads, const std::string& path, int query_heads = 0) {
  if (!query_heads) query_heads = heads;
  g->Compile(threads);
  const auto scratch = g->TrackScratchAllocations();
  std::ofstream ir(path);
  g->Print(ir);
  ir.close();
  const auto original = g->pipeline();
  std::vector<int8_t> k(heads * c * 8 + 64), v(k.size()), only(k.size());
  std::vector<float> q(query_heads * 128 * 8 + 32), fresh(heads * 128 * 8 + 32),
      result(q.size());
  std::vector<int8_t> knew(heads * 128 * 8 + 64), vnew(knew.size());
  const std::vector<std::pair<int, int>> requests = {
      {0, 1},         {0, 128}, {128, 17}, {511, 128}, {512, 128}, {1024, 1},
      {c - 129, 128}, {1, 2},   {0, 17},   {512, 1},   {513, 127}};
  auto key_state = g->NewResourceState("kcache", k.data(), k.size(), {1,size_t(heads),size_t(c),8});
  auto value_state = g->NewResourceState("vcache", v.data(), v.size(), {1,size_t(heads),size_t(c),8});
  auto only_state = g->NewResourceState("onlycache", only.data(), only.size(), {1,size_t(heads),size_t(c),8});
  double max_error = 0;
  for (auto [p, t] : requests) {
    for (int h = 0; h < heads; ++h)
      for (int j = 0; j < c; ++j)
        for (int d = 0; d < 8; ++d) {
          // This request continues the preceding 128-row append unchanged.
          if (p == 128 && t == 17) continue;
          const size_t pos = (h * c + j) * 8 + d;
          k[pos] =
              j < p ? int8_t(std::round(Source(h, j, d, 3) * 32)) : int8_t(101);
          v[pos] = j < p ? int8_t(std::round(Source(h, j, d, 19) * 32))
                         : int8_t(-99);
          only[pos] = int8_t(67);
        }
    if (!(p == 128 && t == 17)) {
      key_state->ImportPrefix(p); value_state->ImportPrefix(p); only_state->ImportPrefix(p);
    }
    auto kbefore = k, vbefore = v, obefore = only;
    for (int h = 0; h < query_heads; ++h)
      for (int i = 0; i < t; ++i)
        for (int d = 0; d < 8; ++d)
          q[(h * t + i) * 8 + d] = Source(h, p + i, d, 31);
    for (int h = 0; h < heads; ++h)
      for (int i = 0; i < t; ++i)
        for (int d = 0; d < 8; ++d) {
          fresh[(h * t + i) * 8 + d] = Source(h, p + i, d, 47);
        }
    g->ScalarValue("position", p);
    const std::vector<size_t> rows = {1, size_t(heads), size_t(t), 8};
    g->Bind("q", q.data(), q.size() * sizeof(float),
            {1, size_t(query_heads), size_t(t), 8});
    g->Bind("fresh", fresh.data(), fresh.size() * sizeof(float), rows);
    g->BindResource("kcache", key_state);
    g->BindResource("vcache", value_state);
    g->BindResource("onlycache", only_state);
    g->Bind("result", result.data(), result.size() * sizeof(float));
    g->Bind("knew", knew.data(), knew.size());
    g->Bind("vnew", vnew.data(), vnew.size());
    auto before = g->counters();
    g->Run();
    auto after = g->counters();
    Expect(scratch->live.load() >= g->RetainedRootScratchBytes(),
           "scratch accounting omitted retained root allocations");
    Expect(scratch->peak.load() <= scratch->allocated.load(),
           "scratch accounting overflowed");
    Expect(original.same_as(g->pipeline()), "pipeline changed");
    Expect(after.append_calls - before.append_calls == 3, "append count");
    Expect(
        after.append_bytes - before.append_bytes == size_t(3 * heads * t * 8),
        "append bytes");
    Expect(after.view_copy_bytes == 0, "history view was copied");
    for (size_t pos = 0; pos < k.size(); ++pos) {
      const bool in_tensor = pos < size_t(heads * c * 8);
      const int h = pos / (c * 8), j = pos / 8 % c, d = pos % 8;
      if (in_tensor && j >= p && j < p + t) {
        const auto index = (h * t + j - p) * 8 + d;
        Expect(k[pos] == knew[index] && only[pos] == knew[index] &&
                   v[pos] == vnew[index],
               "append codes");
        Expect(std::abs(int(knew[index]) -
                        int(std::round(fresh[index] * 32))) <= 1 &&
                   std::abs(int(vnew[index]) -
                            int(std::round(fresh[index] * 64))) <= 1,
               "quantization error");
      } else {
        Expect(k[pos] == kbefore[pos] && v[pos] == vbefore[pos] &&
                   only[pos] == obefore[pos],
               "changed untouched cache bytes");
      }
    }
    // Attention oracle uses the committed codes generated by this backend,
    // isolating addressing/masking from cross-backend quantization rounding.
    for (int h = 0; h < query_heads; ++h)
      for (int i = 0; i < t; ++i) {
        const int kh = h / (query_heads / heads);
        const int lo = window ? std::max(0, p + i - window + 1) : 0, hi = p + i;
        std::vector<double> probs(hi - lo + 1);
        double max_score = -1e100, total = 0;
        for (int j = lo; j <= hi; ++j) {
          double score = 0;
          for (int d = 0; d < 8; ++d)
            score +=
                q[(h * t + i) * 8 + d] * double(k[(kh * c + j) * 8 + d]) / 32;
          probs[j - lo] = score / std::sqrt(8.0);
          max_score = std::max(max_score, probs[j - lo]);
        }
        for (auto& score : probs) {
          score = std::exp(score - max_score);
          total += score;
        }
        for (int d = 0; d < 8; ++d) {
          double expected = 0;
          for (int j = lo; j <= hi; ++j)
            expected +=
                probs[j - lo] / total * double(v[(kh * c + j) * 8 + d]) / 32;
          for (int z = 0; z < 8; ++z)
            expected +=
                q[(h * t + i) * 8 + z] * (z == d ? 0.2 : 0.01 * (z - d));
          const double error = std::abs(expected - result[(h * t + i) * 8 + d]);
          Expect(std::isfinite(result[(h * t + i) * 8 + d]) && error < 2e-4,
                 "attention/reference mismatch");
          max_error = std::max(max_error, error);
        }
      }
  }
  // Preflight rejection cannot write any cache bytes.
  for (auto [p, t] :
       std::vector<std::pair<int, int>>{{c, 1}, {-1, 1}, {0, 129}}) {
    auto before = k, before_v = v, before_only = only;
    g->ScalarValue("position", p);
    g->Bind("q", q.data(), q.size() * sizeof(float),
            {1, size_t(query_heads), size_t(t), 8});
    g->Bind("fresh", fresh.data(), fresh.size() * sizeof(float),
            {1, size_t(heads), size_t(t), 8});
    bool rejected = false;
    try {
      g->Run();
    } catch (const std::invalid_argument&) {
      rejected = true;
    }
    Expect(rejected && before == k && before_v == v && before_only == only,
           "invalid request wrote cache");
  }
  key_state->ImportPrefix(512); value_state->ImportPrefix(512); only_state->ImportPrefix(512);
  g->BindResource("kcache", key_state); g->BindResource("vcache", value_state);
  g->BindResource("onlycache", only_state);
  // Shared shape symbols and storage ownership are real runtime contracts.
  g->ScalarValue("position", 512);
  g->Bind("q", q.data(), q.size() * sizeof(float),
          {1, size_t(query_heads), 1, 8});
  for (bool alias : {false, true}) {
    g->ScalarValue("position", 512);
    auto before = k, before_v = v, before_only = only;
    g->Bind("fresh", fresh.data(), fresh.size() * sizeof(float),
            {1, size_t(heads), size_t(alias ? 1 : 2), 8});
    if (alias) g->BindResource("vcache", g->NewResourceState("vcache", k.data(), k.size(),
        {1,size_t(heads),size_t(c),8},512));
    bool rejected = false;
    try {
      g->Run();
    } catch (const std::invalid_argument&) {
      rejected = true;
    }
    Expect(rejected && before == k && before_v == v && before_only == only,
           "bad shape/alias wrote cache");
    g->BindResource("vcache", value_state);
  }
  // Inject an execution failure after one owner's update. Preserve the prefix
  // and prohibit reusing a runtime that might contain unpublished suffixes.
  g->ScalarValue("position", 512);
  g->Bind("q", q.data(), q.size() * sizeof(float),
          {1, size_t(query_heads), 1, 8});
  g->Bind("fresh", fresh.data(), fresh.size() * sizeof(float),
          {1, size_t(heads), 1, 8});
  const auto successful_counters = g->counters();
  g->FailAfterAppends(1);
  auto old_k = k, old_v = v;
  bool failed = false;
  try {
    g->Run();
  } catch (const std::runtime_error&) {
    failed = true;
  }
  Expect(failed, "injected append failure ignored");
  for (int h = 0; h < heads; ++h)
    for (int j = 0; j < 512 * 8; ++j)
      Expect(k[h * c * 8 + j] == old_k[h * c * 8 + j] &&
                 v[h * c * 8 + j] == old_v[h * c * 8 + j],
             "failure changed old prefix");
  bool retry_rejected = false;
  try {
    g->Run();
  } catch (const std::logic_error&) {
    retry_rejected = true;
  }
  Expect(retry_rejected, "failed stateful runtime was reused");
  Expect(scratch->allocations.load() > 0 && scratch->peak.load() > 0,
         "scratch hooks did not observe execution allocations");
  // Hooks own their counters through runtime/worker teardown, including an
  // invocation that failed after an append. No allocation may outlive Graph.
  g.reset();
  Expect(scratch->live.load() == 0, "scratch remained live after teardown");
  std::cout << "capacity=" << c << ",heads=" << heads
            << ",query_heads=" << query_heads << ",window=" << window
            << ",threads=" << threads << ",requests=" << requests.size()
            << ",max_error=" << max_error
            << ",append_bytes=" << successful_counters.append_bytes
            << ",view_copy_bytes=" << successful_counters.view_copy_bytes
            << '\n';
}
}  // namespace

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "usage: state_views_test EXISTING_OUTPUT_DIRECTORY\n";
    return 2;
  }
  try {
    for (int threads : {1, 4}) {
      Test(Build_c2048_h2_w512_q8(), 2048, 2, 512, threads,
           std::string(argv[1]) + "/gqa2-local.ir.txt", 8);
      Test(Build_c8448_h2_w0_q8(), 8448, 2, 0, threads,
           std::string(argv[1]) + "/gqa2-global.ir.txt", 8);
      auto run = [&](std::unique_ptr<lab_ynn::Graph> g, int c, int h, int w) {
        Test(std::move(g), c, h, w, threads,
             std::string(argv[1]) + "/c" + std::to_string(c) + "h" +
                 std::to_string(h) + "w" + std::to_string(w) + "t" +
                 std::to_string(threads) + ".ir.txt");
      };
      run(Build_c2048_h1_w512(), 2048, 1, 512);
      run(Build_c2048_h2_w512(), 2048, 2, 512);
      run(Build_c8448_h2_w512(), 8448, 2, 512);
      run(Build_c8448_h4_w512(), 8448, 4, 512);
      run(Build_c2048_h2_w0(), 2048, 2, 0);
      run(Build_c2048_h2_w1(), 2048, 2, 1);
      Test(
          Build_c2048_h1_w512_q4(), 2048, 1, 512, threads,
          std::string(argv[1]) + "/gqa_t" + std::to_string(threads) + ".ir.txt",
          4);
    }
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    return 1;
  }
}
