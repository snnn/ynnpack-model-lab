// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
#include "runtime/rust/bridge_internal.h"

extern "C" {
int32_t lab_embedding_create(LabAssets* assets, const char* json, size_t rows,
                            size_t width, int bits, size_t block,
                            lab::Embedding** out, LabError* error) noexcept {
  if (out) *out = nullptr;
  return LabCatch(error, [&] {
    LabRequire(assets && json && out && rows && width && block &&
                   (bits == 2 || bits == 4 || bits == 8) && width % block == 0 &&
                   rows <= SIZE_MAX / width / sizeof(float), "Invalid embedding geometry");
    minijson::value value;
    const char* at = json;
    LabRequire(minijson::parse(at, value) == minijson::no_error && !*at &&
                   value.as<lab::Object>(), "Invalid embedding record");
    *out = new lab::Embedding(*value.as<lab::Object>(), rows, width, bits, block, assets->weights);
  });
}
void lab_embedding_delete(lab::Embedding* e) noexcept { delete e; }
int32_t lab_embedding_slice(lab::Embedding* e, const int32_t* tokens,
                           size_t count, size_t begin, size_t columns,
                           float* output, size_t elements, LabError* error) noexcept {
  return LabCatch(error, [&] {
    LabRequire(e && tokens && output && columns && count <= elements / columns,
               "Invalid embedding output");
    e->LookupSlice(tokens, count, begin, columns, output);
  });
}
}
