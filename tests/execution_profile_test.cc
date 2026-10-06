// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
#include <iostream>
#include <sstream>
#include <vector>

#include "runtime/ynnpack_support.h"

void Require(bool condition, const char* message) {
  if (!condition) throw std::runtime_error(message);
}

int main() {
  try {
    for (int threads : {1, 4}) {
      const size_t n = 65536;
      std::vector<float> a(n), b(n), output(n);
      for (size_t i = 0; i < n; ++i) {
        a[i] = i % 31;
        b[i] = i % 7;
      }
      lab_ynn::Graph graph(4);
      graph.Tensor(0, "input", ynn_type_fp32, {n},
                   YNN_VALUE_FLAG_EXTERNAL_INPUT, nullptr);
      graph.Tensor(1, "other", ynn_type_fp32, {n},
                   YNN_VALUE_FLAG_EXTERNAL_INPUT, nullptr);
      graph.Tensor(2, "sum", ynn_type_fp32, {n}, 0, nullptr);
      graph.Tensor(3, "output", ynn_type_fp32, {n},
                   YNN_VALUE_FLAG_EXTERNAL_OUTPUT, nullptr);
      graph.BeginProfileOperation("Layer0/Add", "core.add", {0, 1}, {2});
      graph.Binary(ynn_binary_add, 0, 1, 2);
      graph.EndProfileOperation();
      graph.BeginProfileOperation("Layer1/Product", "core.mul", {2, 1}, {3});
      graph.Binary(ynn_binary_multiply, 2, 1, 3);
      graph.EndProfileOperation();
      auto profile = graph.TrackExecution();
      graph.Compile(threads);
      graph.Bind("input", a.data(), a.size() * sizeof(float));
      graph.Bind("other", b.data(), b.size() * sizeof(float));
      graph.Bind("output", output.data(), output.size() * sizeof(float));
      std::ostringstream trace;
      profile->WriteMetadata(trace);
      for (int step = 1; step <= 2; ++step) {
        profile->BeginStep("arithmetic", 0, step, step);
        graph.Run();
        profile->EndStep(trace);
        for (size_t i = 0; i < n; ++i)
          Require(output[i] == (a[i] + b[i]) * b[i], "arithmetic changed");
      }
      Require(trace.str().find("\"complete\":true") != std::string::npos,
              "missing completion");
      Require(profile->calls().size() > 1, "missing scheduled calls");
      std::set<size_t> origins;
      for (const auto& call : profile->calls())
        origins.insert(call.origins.begin(), call.origins.end());
      Require(origins == std::set<size_t>({0, 1}),
              "lost or incorrect fused operation origins");
      profile->BeginStep("failure", 0, 3, 3);
      profile->EndStep(trace, false);
      Require(trace.str().find("\"complete\":false") != std::string::npos,
              "missing failure");
    }
    // Deterministically exhaust a bounded buffer using a simple scheduled call.
    lab_ynn::ExecutionProfile profile({}, 1);
    std::ostringstream trace;
    profile.BeginStep("overflow", 0, 1, 0);
    {
      lab_ynn::ExecutionProfile::Span span(&profile, 0);
    }
    {
      lab_ynn::ExecutionProfile::Span span(&profile, 0);
    }
    bool rejected = false;
    try {
      profile.EndStep(trace);
    } catch (const std::runtime_error&) {
      rejected = true;
    }
    Require(rejected &&
                trace.str().find("\"dropped_events\":1") != std::string::npos,
            "event loss must invalidate profile");
    Require(lab_ynn::ProfileJson("a\n\"b") == "\"a\\n\\\"b\"" ||
                lab_ynn::ProfileJson("a\n\"b") == "\"a\\u000a\\\"b\"",
            "invalid JSON escaping");
    std::cout << "execution profiling: arithmetic, threads, reset, failure, "
                 "overflow passed\n";
  } catch (const std::exception& error) {
    std::cerr << error.what() << '\n';
    return 1;
  }
}
