// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
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
int32_t lab_test_graph_create(LabAssets* assets, uint32_t phase, LabGraph** out,
                              LabError* error) noexcept {
  if (out) *out = nullptr;
  return LabCatch(error, [&] {
    LabRequire(assets && out && (phase == 0 || phase == 3),
               "Unsupported fixture phase");
    auto handle = std::make_unique<LabGraph>();
    {
      auto& g = handle->graph;
      g = std::make_unique<lab_ynn::Graph>(phase == 3 ? 3 : 2);
      g->Tensor(0, "x", ynn_type_fp32, {4}, YNN_VALUE_FLAG_EXTERNAL_INPUT,
                nullptr);
      g->Tensor(1, "squared", ynn_type_fp32, {4},
                YNN_VALUE_FLAG_EXTERNAL_OUTPUT, nullptr);
      if (phase == 3) {
        g->Tensor(2, "scale", ynn_type_fp32, {1}, 0,
                  assets->weights.Get("scale.bin", 4));
        g->Binary(ynn_binary_multiply, 0, 2, 1);
      } else {
        g->Binary(ynn_binary_multiply, 0, 0, 1);
      }
    }
    *out = handle.release();
  });
}
int32_t lab_test_fail_after_appends(LabGraph* graph, size_t n,
                                    LabError* error) noexcept {
  return LabCatch(error, [&] { graph->graph->FailAfterAppends(n); });
}
}  // extern "C"
