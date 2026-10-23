// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
#include "runtime/rust/bridge_internal.h"
extern "C" int32_t lab_assets_raw_embedding(
    LabAssets* assets, const char* name, size_t bytes, const uint8_t** out,
    LabError* error) noexcept {
  if (out) *out = nullptr;
  return LabCatch(error, [&] {
    LabRequire(assets && assets->hf_weights && name && out,
               "Invalid HF embedding asset");
    const auto record = assets->hf_weights->Record(name);
    LabRequire(lab::Integer(record, "bytes") == bytes, "HF embedding size mismatch");
    // Embedding lookup consumes the original offset-binary codes. Verifying
    // those bytes must not materialize the native linear's signed-code cache.
    *out = assets->hf_weights->Raw(name);
  });
}
extern "C" int32_t lab_assets_create_hf(
    const char* source, const char* manifest, const char* cache,
    const char* parameters, const char* identity, int32_t bf16,
    LabAssets** out, LabError* error) noexcept {
  if (out) *out = nullptr;
  return LabCatch(error, [&] {
    LabRequire(source && manifest && cache && parameters && identity && out,
               "Invalid HF asset paths");
    LabRequire(LAB_HAS_BF16_ROUNDING,
               "HF packages require the BF16 rounding patch in a separate LAB_DEPS tree");
    auto assets = std::make_unique<LabAssets>(source, parameters);
    assets->hf_weights = std::make_unique<lab::TensorProvider>(source, manifest, cache, parameters);
    LabRequire(lab::Field<std::string>(assets->hf_weights->manifest(), "source_identity") == identity,
               "HF source identity mismatch");
    assets->bf16_activations = bf16 != 0;
    *out = assets.release();
  });
}
