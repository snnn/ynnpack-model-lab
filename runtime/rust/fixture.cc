// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
#include <cstring>
#include <limits>

#include "runtime/rust/bridge_internal.h"

extern "C" {
int32_t lab_assets_create(const char* bundle, const char* parameters,
                          LabAssets** out, LabError* error) noexcept {
  if (out) *out = nullptr;
  return LabCatch(error, [&] {
    LabRequire(bundle && parameters && out, "Invalid asset paths");
    *out = new LabAssets(bundle, parameters);
  });
}

int32_t lab_fixture_run(LabGraph* handle, const LabAppendCheck* checks,
                        size_t count, size_t appends, size_t fail_after,
                        LabError* error) noexcept {
  size_t observed = 0;
  int32_t result = LabCatch(error, [&] {
    LabRequire(handle && handle->graph && (checks || !count),
               "Invalid append observer");
    auto& graph = *handle->graph;
    const size_t first = graph.counters().append_calls;
    for (size_t i = 0; i < count; ++i) {
      LabRequire(
          checks[i].append < appends &&
              (!checks[i].bytes || (checks[i].actual && checks[i].expected)),
          "Invalid append check");
    }
    if (fail_after != std::numeric_limits<size_t>::max())
      graph.FailAfterAppends(fail_after);
    graph.ObserveAppends([&, first](size_t call) {
      LabRequire(call == first + observed && observed < appends,
                 "Append callbacks out of order");
      for (size_t i = 0; i < count; ++i) {
        const auto& check = checks[i];
        if (check.append == observed && check.bytes)
          LabRequire(
              std::memcmp(check.actual, check.expected, check.bytes) == 0,
              "Reader output unfinished before append");
      }
      ++observed;
    });
  });
  if (result) return result;
  result = lab_graph_run(handle, error);
  handle->graph->ObserveAppends({});
  if (result) return result;
  return LabCatch(error, [&] {
    LabRequire(observed == appends, "Missing append callback");
  });
}
}
