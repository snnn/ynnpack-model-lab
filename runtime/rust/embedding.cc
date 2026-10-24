// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
#include "runtime/rust/bridge_internal.h"

struct LabEmbedding {
  std::unique_ptr<lab::Embedding> packed;
  std::unique_ptr<lab::HfEmbedding> hf;
};
extern "C" {
int32_t lab_embedding_create(LabAssets* assets, const char* json, size_t rows,
                            size_t width, int bits, size_t block,
                            LabEmbedding** out, LabError* error) noexcept {
  if (out) *out = nullptr;
  return LabCatch(error, [&] {
    LabRequire(assets && json && out && rows && width && block &&
                   (bits == 2 || bits == 4 || bits == 8) && width % block == 0 &&
                   rows <= SIZE_MAX / width / sizeof(float), "Invalid embedding geometry");
    minijson::value value;
    const char* at = json;
    LabRequire(minijson::parse(at, value) == minijson::no_error && !*at &&
                   value.as<lab::Object>(), "Invalid embedding record");
    auto result = std::make_unique<LabEmbedding>();
    const auto& rec = *value.as<lab::Object>();
    if (rec.count("source")) {
      LabRequire(lab::Field<std::string>(rec, "source") == "hf" && assets->hf_weights,
                 "HF embedding requires matching assets");
      result->hf = std::make_unique<lab::HfEmbedding>(*assets->hf_weights,
          lab::Field<std::string>(rec, "module"), rows, width, block, bits,
          lab::Field<minijson::number>(rec, "multiplier"));
    } else {
      result->packed = std::make_unique<lab::Embedding>(rec, rows, width, bits, block, assets->weights);
    }
    *out = result.release();
  });
}
void lab_embedding_delete(LabEmbedding* e) noexcept { delete e; }
int32_t lab_embedding_slice(LabEmbedding* e, const int32_t* tokens,
                           size_t count, size_t begin, size_t columns,
                           void* output, size_t elements, int32_t bf16, LabError* error) noexcept {
  return LabCatch(error, [&] {
    LabRequire(e && tokens && output && columns && count <= elements / columns,
               "Invalid embedding output");
    if (e->hf) {
      if (bf16) e->hf->LookupSlice(tokens, count, begin, columns, static_cast<uint16_t*>(output));
      else e->hf->LookupSlice(tokens, count, begin, columns, static_cast<float*>(output));
    } else {
      LabRequire(!bf16, "Packed embedding expects FP32 output");
      e->packed->LookupSlice(tokens, count, begin, columns, static_cast<float*>(output));
    }
  });
}
}
