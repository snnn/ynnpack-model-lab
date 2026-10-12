// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
// Weights-free decode attention. Timings cover the entire prepared graph;
// optional callback profiles are collected in a separate diagnostic invocation.
#include <algorithm>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "runtime/ynnpack_support.h"

namespace {
using Clock = std::chrono::steady_clock;
constexpr float kScale = 0.03125f;
struct Options {
  size_t width = 256, capacity = 2048, kv_heads = 1, threads = 4;
  size_t repetitions = 3, iterations = 10, consumers = 2;
  size_t bank_seed_stride = 16384;
  int window = 0;
  bool grouped = false, quantized = false;
  std::string histories = "1,17,128,511,512,513,1024", profile, pipeline;
};
Options Parse(int argc, char** argv) {
  Options o;
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    auto p = arg.find('=');
    if (p == std::string::npos)
      throw std::invalid_argument("expected --name=value");
    auto key = arg.substr(0, p), v = arg.substr(p + 1);
    if (key == "--histories")
      o.histories = v;
    else if (key == "--profile")
      o.profile = v;
    else if (key == "--pipeline")
      o.pipeline = v;
    else if (key == "--layout") {
      if (v != "batch" && v != "rows")
        throw std::invalid_argument("layout must be batch or rows");
      o.grouped = v == "rows";
    } else if (key == "--arithmetic") {
      if (v != "fp32" && v != "int8")
        throw std::invalid_argument("arithmetic must be fp32 or int8");
      o.quantized = v == "int8";
    } else {
      if (v.empty() || v.find_first_not_of("0123456789") != std::string::npos)
        throw std::invalid_argument("expected nonnegative integer");
      size_t n = std::stoull(v);
      if (key == "--width")
        o.width = n;
      else if (key == "--capacity")
        o.capacity = n;
      else if (key == "--kv-heads")
        o.kv_heads = n;
      else if (key == "--threads")
        o.threads = n;
      else if (key == "--repetitions")
        o.repetitions = n;
      else if (key == "--iterations")
        o.iterations = n;
      else if (key == "--consumers")
        o.consumers = n;
      else if (key == "--bank-seed-stride")
        o.bank_seed_stride = n;
      else if (key == "--window" && n <= 8192)
        o.window = n;
      else
        throw std::invalid_argument("unknown option");
    }
  }
  if ((o.width != 256 && o.width != 512) || !o.capacity || o.capacity > 16384 ||
      (o.kv_heads != 1 && o.kv_heads != 2) || !o.threads || o.threads > 64 ||
      !o.repetitions || !o.iterations || !o.consumers || o.consumers > 2 ||
      o.bank_seed_stride < o.capacity || o.bank_seed_stride > 1048576)
    throw std::invalid_argument("unsupported experiment geometry");
  return o;
}
struct Query {
  std::string input, output;
  size_t kv;
  std::vector<float> q, result;
  std::vector<float> probabilities, scores;
};
struct QuantizedRow {
  float scale;
  int32_t zero;
  std::vector<int32_t> codes;
};
// Independent scalar reference: include zero in the range, use all 256 codes,
// and round a nonnegative zero point half up, then values to nearest even.
QuantizedRow QuantizeRow(const std::vector<float>& x) {
  float lo = std::min(0.0f, *std::min_element(x.begin(), x.end()));
  float hi = std::max(0.0f, *std::max_element(x.begin(), x.end()));
  float range = hi - lo;
  QuantizedRow q{range == 0 ? 1.0f : range / 255.0f, -128, {}};
  if (range != 0)
    q.zero += int32_t(std::clamp(-lo * (255.0f / range), 0.0f, 255.0f) + 0.5f);
  const float reciprocal = 1.0f / q.scale;
  for (float value : x)
    q.codes.push_back(std::clamp(
        int32_t(std::nearbyint(value * reciprocal)) + q.zero, -128, 127));
  return q;
}
std::vector<double> Probabilities(const std::vector<double>& scores) {
  double maximum = *std::max_element(scores.begin(), scores.end()), total = 0;
  for (double x : scores) total += std::exp(x - maximum);
  std::vector<double> p;
  for (double x : scores) p.push_back(std::exp(x - maximum) / total);
  return p;
}
void Run(const Options& o) {
  const size_t heads = 8 / o.kv_heads, d = o.width, c = o.capacity;
  std::vector<size_t> histories;
  std::istringstream hs(o.histories);
  for (std::string s; std::getline(hs, s, ',');) {
    if (s.empty() || s.find_first_not_of("0123456789") != std::string::npos)
      throw std::invalid_argument("invalid history");
    auto h = std::stoull(s);
    if (!h || h > c)
      throw std::invalid_argument("history must be in [1,capacity]");
    histories.push_back(h);
  }
  if (histories.empty()) throw std::invalid_argument("empty history list");
  const auto mix = [](uint32_t x) {
    x ^= x >> 16;
    x *= 0x7feb352d;
    x ^= x >> 15;
    x *= 0x846ca68b;
    return x ^ (x >> 16);
  };
  std::vector<int8_t> k(o.kv_heads * c * d + 64), v(k.size());
  for (size_t bank = 0; bank < o.kv_heads; ++bank)
    for (size_t t = 0; t < c; ++t)
      for (size_t z = 0; z < d; ++z) {
        const size_t i = (bank * c + t) * d + z;
        const auto seed = uint32_t((bank * o.bank_seed_stride + t) * d + z);
        k[i] = int(mix(seed) % 256) - 128;
        v[i] = int(mix(seed + 7919) % 256) - 128;
      }
  auto build = [&](bool inspect, std::vector<Query>& queries) {
    auto graph = std::make_unique<lab_ynn::Graph>(256);
    auto& g = *graph;
    uint32_t next = 0;
    auto tensor = [&](std::string name, ynn_type type,
                      std::vector<size_t> shape, uint32_t flags = 0) {
      auto id = next++;
      g.Tensor(id, name, type, shape, flags, nullptr);
      return id;
    };
    // Match the view-based target rewrite: only singleton/head axes move.
    auto swap_heads = [&](uint32_t in, uint32_t out, bool rows,
                          size_t columns) {
      auto fused = tensor("head_fusion" + std::to_string(next), ynn_type_fp32,
                          {1, heads, columns});
      g.FuseDims(in, fused, 1, 2);
      g.SplitDim(
          fused, out, 1,
          rows ? std::vector<size_t>{1, heads} : std::vector<size_t>{heads, 1});
    };
    auto ki = tensor("key", ynn_type_int8, {1, o.kv_heads, c, d},
                     YNN_VALUE_FLAG_EXTERNAL_INPUT);
    auto vi = tensor("value", ynn_type_int8, {1, o.kv_heads, c, d},
                     YNN_VALUE_FLAG_EXTERNAL_INPUT);
    auto end = g.Parameter("end", 1, c);
    auto begin = o.window ? slinky::max(end - o.window, 0) : slinky::expr(0);
    g.Resource(ki, "key", 2, end, "symmetric_i8_0.03125");
    g.Resource(vi, "value", 2, end, "symmetric_i8_0.03125");
    auto kh = tensor("key_history", ynn_type_int8, {1, o.kv_heads, c, d});
    auto vh = tensor("value_history", ynn_type_int8, {1, o.kv_heads, c, d});
    g.View(ki, kh, 2, begin, end);
    g.View(vi, vh, 2, begin, end);
    auto kf = kh, vf = vh;
    if (!o.quantized) {
      kf = tensor("key_float", ynn_type_fp32, {1, o.kv_heads, c, d});
      vf = tensor("value_float", ynn_type_fp32, {1, o.kv_heads, c, d});
      g.BeginProfileOperation("SharedKV/Attention/Sdpa", "dequantize", {kh, vh},
                              {kf, vf});
      g.Dequantize(kh, kf, kScale, 0);
      g.Dequantize(vh, vf, kScale, 0);
      g.EndProfileOperation();
    }
    auto matmul = [&](uint32_t a, uint32_t b, uint32_t out, bool adj_b) {
      if (o.quantized)
        g.DynamicallyQuantizedMatmul(a, b, out, kScale, adj_b);
      else
        g.Matmul(a, b, out, false, adj_b);
    };
    for (size_t bank = 0; bank < o.kv_heads; ++bank) {
      auto kv_type = o.quantized ? ynn_type_int8 : ynn_type_fp32;
      auto kb =
          tensor("key_bank" + std::to_string(bank), kv_type, {1, 1, c, d});
      auto vb =
          tensor("value_bank" + std::to_string(bank), kv_type, {1, 1, c, d});
      g.Slice(kf, kb, {0, int64_t(bank), 0, 0}, {1, 1, -1, -1});
      g.Slice(vf, vb, {0, int64_t(bank), 0, 0}, {1, 1, -1, -1});
      for (size_t consumer = 0; consumer < o.consumers; ++consumer) {
        auto name = "bank" + std::to_string(bank) + "_consumer" +
                    std::to_string(consumer);
        Query q{name + "_q", name + "_y", bank, std::vector<float>(heads * d),
                std::vector<float>(heads * d)};
        for (size_t i = 0; i < q.q.size(); ++i)
          q.q[i] = std::sin(float(i * 7 + bank * 31 + consumer * 11) * 0.013f) *
                   std::sqrt(2.0f / float(d));
        // Exercise the degenerate dynamic range and asymmetric positive rows.
        if (consumer == 1) {
          std::fill(q.q.begin(), q.q.begin() + d, 0.0f);
          for (size_t i = d; i < 2 * d; ++i) q.q[i] = std::abs(q.q[i]);
        }
        auto qi = tensor(q.input, ynn_type_fp32, {1, heads, 1, d},
                         YNN_VALUE_FLAG_EXTERNAL_INPUT);
        auto out = tensor(q.output, ynn_type_fp32, {1, heads, 1, d},
                          YNN_VALUE_FLAG_EXTERNAL_OUTPUT);
        auto scores = tensor(name + "_scores", ynn_type_fp32, {1, heads, 1, c});
        auto masked = tensor(name + "_masked", ynn_type_fp32, {1, heads, 1, c});
        auto probs = tensor(name + "_probs", ynn_type_fp32, {1, heads, 1, c});
        const auto scope = name + "/Attention/Sdpa";
        const auto dot_kind =
            o.quantized ? "ynn.dynamic_matmul" : "core.matmul";
        g.BeginProfileOperation((scope + "/QK").c_str(), dot_kind, {qi, kb},
                                {scores});
        if (o.grouped) {
          auto rows = tensor(name + "_q_rows", ynn_type_fp32, {1, 1, heads, d});
          auto dot = tensor(name + "_qk_rows", ynn_type_fp32, {1, 1, heads, c});
          swap_heads(qi, rows, true, d);
          matmul(rows, kb, dot, true);
          swap_heads(dot, scores, false, c);
        } else
          matmul(qi, kb, scores, true);
        g.EndProfileOperation();
        g.BeginProfileOperation(scope.c_str(), "mask_softmax", {scores},
                                {probs});
        g.Mask(scores, masked, end - 1, begin, o.window, true);
        g.Softmax(masked, probs, 1.0f);
        g.EndProfileOperation();
        g.BeginProfileOperation((scope + "/PV").c_str(), dot_kind, {probs, vb},
                                {out});
        if (o.grouped) {
          auto rows = tensor(name + "_p_rows", ynn_type_fp32, {1, 1, heads, c});
          auto dot = tensor(name + "_pv_rows", ynn_type_fp32, {1, 1, heads, d});
          swap_heads(probs, rows, true, c);
          matmul(rows, vb, dot, false);
          swap_heads(dot, out, false, d);
        } else
          matmul(probs, vb, out, false);
        g.EndProfileOperation();
        queries.push_back(std::move(q));
      }
    }
    if (inspect)
      for (auto& q : queries) {
        const auto base = q.input.substr(0, q.input.size() - 2);
        g.ExposeForInspection(base + "_scores");
        g.ExposeForInspection(base + "_probs");
        q.scores.resize(heads * c);
        q.probabilities.resize(heads * c);
      }
    return graph;
  };
  std::vector<Query> queries, inspected_queries;
  auto graph = build(false, queries);
  auto& g = *graph;
  auto inspected = o.quantized ? build(true, inspected_queries) : nullptr;
  auto profile = o.profile.empty() ? nullptr : g.TrackExecution();
  auto started = Clock::now();
  g.Compile(o.threads);
  double setup_ms =
      std::chrono::duration<double, std::milli>(Clock::now() - started).count();
  if (inspected) inspected->Compile(o.threads);
  if (!o.pipeline.empty()) {
    std::ofstream f(o.pipeline);
    g.Print(f);
    if (!f) throw std::runtime_error("pipeline write failed");
  }
  auto ks =
      g.NewResourceState("key", k.data(), k.size(), {1, o.kv_heads, c, d}, c);
  auto vs =
      g.NewResourceState("value", v.data(), v.size(), {1, o.kv_heads, c, d}, c);
  g.ScalarValue("end", c);
  g.BindResource("key", ks);
  g.BindResource("value", vs);
  for (auto& q : queries) {
    g.Bind(q.input, q.q.data(), q.q.size() * 4);
    g.Bind(q.output, q.result.data(), q.result.size() * 4);
  }
  std::shared_ptr<lab_ynn::ResourceState> inspected_k, inspected_v;
  if (inspected) {
    inspected_k = inspected->NewResourceState("key", k.data(), k.size(),
                                              {1, o.kv_heads, c, d}, c);
    inspected_v = inspected->NewResourceState("value", v.data(), v.size(),
                                              {1, o.kv_heads, c, d}, c);
    inspected->ScalarValue("end", c);
    inspected->BindResource("key", inspected_k);
    inspected->BindResource("value", inspected_v);
    for (auto& q : inspected_queries) {
      const auto base = q.input.substr(0, q.input.size() - 2);
      inspected->Bind(q.input, q.q.data(), q.q.size() * 4);
      inspected->Bind(q.output, q.result.data(), q.result.size() * 4);
      inspected->Bind(base + "_scores", q.scores.data(), q.scores.size() * 4);
      inspected->Bind(base + "_probs", q.probabilities.data(),
                      q.probabilities.size() * 4);
    }
  }
  std::ofstream pf;
  if (profile) {
    pf.open(o.profile);
    if (!pf) throw std::runtime_error("profile open failed");
    profile->WriteMetadata(pf);
  }
  for (size_t h : histories) {
    g.ScalarValue("end", h);
    ks->ImportPrefix(h);
    vs->ImportPrefix(h);
    g.BindResource("key", ks);
    g.BindResource("value", vs);
    g.ScalarValue("end", h);
    g.Run();  // same prepared graph, warmup and correctness
    if (inspected) {
      inspected_k->ImportPrefix(h);
      inspected_v->ImportPrefix(h);
      inspected->BindResource("key", inspected_k);
      inspected->BindResource("value", inspected_v);
      inspected->ScalarValue("end", h);
      inspected->Run();
    }
    double max_error = 0, max_fp32_error = 0, max_score_error = 0;
    double max_probability_error = 0, max_inspection_error = 0;
    const size_t first = o.window && h > size_t(o.window) ? h - o.window : 0;
    for (const auto& q : queries)
      for (size_t head = 0; head < heads; ++head) {
        std::vector<double> scores(h - first), quantized_scores(h - first);
        std::vector<float> query(q.q.begin() + head * d,
                                 q.q.begin() + (head + 1) * d);
        auto qa = QuantizeRow(query);
        for (size_t t = first; t < h; ++t) {
          double sum = 0;
          for (size_t z = 0; z < d; ++z)
            sum += double(q.q[head * d + z]) *
                   float(k[(q.kv * c + t) * d + z]) * kScale;
          scores[t - first] = sum;
          int32_t accumulator = 0;
          for (size_t z = 0; z < d; ++z)
            accumulator +=
                (qa.codes[z] - qa.zero) * int32_t(k[(q.kv * c + t) * d + z]);
          quantized_scores[t - first] =
              float(accumulator) * (qa.scale * kScale);
        }
        auto fp = Probabilities(scores);
        auto p = Probabilities(quantized_scores);
        std::vector<float> pv_input(p.begin(), p.end());
        const auto index = size_t(&q - queries.data());
        if (inspected) {
          const auto base = q.input.substr(0, q.input.size() - 2);
          const auto read = [&](const char* suffix, size_t t) {
            const auto& b = inspected->InspectionBuffer(base + suffix);
            const auto* address = static_cast<const char*>(b.base) +
                                  t * b.dim(0).stride() +
                                  head * b.dim(2).stride();
            return *reinterpret_cast<const float*>(address);
          };
          for (size_t t = 0; t < p.size(); ++t) {
            const float score = read("_scores", t), prob = read("_probs", t);
            const double score_error = std::abs(score - quantized_scores[t]);
            const double prob_error = std::abs(prob - p[t]);
            if (!std::isfinite(score) || !std::isfinite(prob) ||
                score_error > 2e-5 + 2e-5 * std::abs(quantized_scores[t]) ||
                prob_error > 2e-5 + 2e-5 * std::abs(p[t]))
              throw std::runtime_error("independent QK/softmax oracle failed");
            max_score_error = std::max(max_score_error, score_error);
            max_probability_error = std::max(max_probability_error, prob_error);
            pv_input[t] = prob;
          }
        }
        // Floating softmax can cross a probability quantization threshold.
        // Verify PV independently from its actual FP32 input, and verify that
        // inspection did not change the unobserved graph's final computation.
        auto qp = QuantizeRow(pv_input);
        for (size_t z = 0; z < d; ++z) {
          double fp32_expected = 0;
          int32_t accumulator = 0;
          for (size_t t = first; t < h; ++t) {
            fp32_expected += double(fp[t - first]) *
                             float(v[(q.kv * c + t) * d + z]) * kScale;
            accumulator += (qp.codes[t - first] - qp.zero) *
                           int32_t(v[(q.kv * c + t) * d + z]);
          }
          double expected = o.quantized
                                ? float(accumulator) * (qp.scale * kScale)
                                : fp32_expected;
          double actual = q.result[head * d + z],
                 error = std::abs(actual - expected);
          if (inspected) {
            const double inspection_error = std::abs(
                actual - inspected_queries[index].result[head * d + z]);
            if (!std::isfinite(inspection_error) ||
                inspection_error > 2e-5 + 2e-5 * std::abs(actual))
              throw std::runtime_error("inspection changed attention output");
            max_inspection_error =
                std::max(max_inspection_error, inspection_error);
          }
          if (!std::isfinite(actual) ||
              error > 2e-5 + 2e-5 * std::abs(expected))
            throw std::runtime_error(
                "independent attention oracle failed at history=" +
                std::to_string(h) + ", error=" + std::to_string(error));
          max_error = std::max(max_error, error);
          max_fp32_error =
              std::max(max_fp32_error, std::abs(actual - fp32_expected));
        }
      }
    if (g.counters().view_copy_bytes)
      throw std::runtime_error("history view materialized");
    if (inspected && inspected->counters().view_copy_bytes)
      throw std::runtime_error("inspection history view materialized");
    for (size_t r = 0; r < o.repetitions; ++r) {
      if (profile) profile->BeginStep("attention", r, h, h - 1);
      started = Clock::now();
      for (size_t i = 0; i < o.iterations; ++i) {
        g.ScalarValue("end", h);
        g.Run();
      }
      double ms =
          std::chrono::duration<double, std::milli>(Clock::now() - started)
              .count() /
          o.iterations;
      if (profile) profile->EndStep(pf);
      std::cout << "{\"layout\":\"" << (o.grouped ? "rows" : "batch")
                << "\",\"arithmetic\":\"" << (o.quantized ? "int8" : "fp32")
                << "\",\"history\":" << h << ",\"capacity\":" << c
                << ",\"width\":" << d << ",\"kv_heads\":" << o.kv_heads
                << ",\"consumers\":" << o.consumers
                << ",\"bank_seed_stride\":" << o.bank_seed_stride
                << ",\"window\":" << o.window << ",\"threads\":" << o.threads
                << ",\"repetition\":" << r << ",\"iterations\":" << o.iterations
                << ",\"diagnostic\":" << (profile ? "true" : "false")
                << ",\"oracle\":\""
                << (o.quantized ? "staged_int8" : "fp32_attention") << "\""
                << ",\"view_copy_bytes\":" << g.counters().view_copy_bytes
                << ",\"graph_ms\":" << ms << ",\"setup_ms\":" << setup_ms
                << ",\"max_abs_error\":" << max_error
                << ",\"max_score_error\":" << max_score_error
                << ",\"max_probability_error\":" << max_probability_error
                << ",\"max_inspection_output_error\":" << max_inspection_error
                << ",\"max_abs_error_vs_fp32\":" << max_fp32_error << "}\n";
    }
  }
}
}  // namespace
int main(int argc, char** argv) {
  try {
    Run(Parse(argc, argv));
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    return 1;
  }
}
