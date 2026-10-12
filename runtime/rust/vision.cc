// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
#include "runtime/rust/bridge_internal.h"

extern "C" {
const char* lab_model_name() noexcept { return ""; }
int32_t lab_assets_create(const char* bundle, const char* parameters,
                          LabAssets** out, LabError* error) noexcept {
  if (out) *out = nullptr;
  return LabCatch(error, [&] {
    LabRequire(bundle && parameters && out, "Invalid asset paths");
    *out = new LabAssets(bundle, parameters);
  });
}

}  // extern "C"
