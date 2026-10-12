// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
#include "runtime/rust/bridge_internal.h"

namespace {
lab::Gemma4Config Config() {
#if defined(LAB_GEMMA4_E4B)
  return lab::Gemma4Config::E4B();
#else
  return lab::Gemma4Config::E2B();
#endif
}
}  // namespace

extern "C" {
const char* lab_model_name() noexcept {
#if defined(LAB_GEMMA4_E4B)
  return "gemma4_e4b";
#else
  return "gemma4_e2b";
#endif
}
int32_t lab_assets_create(const char* bundle, const char* parameters,
                          LabAssets** out, LabError* error) noexcept {
  if (out) *out = nullptr;
  return LabCatch(error, [&] {
    LabRequire(bundle && parameters && out, "Invalid asset paths");
    auto assets = std::make_unique<LabAssets>(bundle, parameters);
    assets->model =
        std::make_unique<lab::ModelAssets>(bundle, assets->weights, Config());
    *out = assets.release();
  });
}
int32_t lab_assets_config(LabAssets* assets, LabConfig* out,
                          LabError* error) noexcept {
  return LabCatch(error, [&] {
    LabRequire(assets && out, "Invalid config request");
    auto c = Config();
    *out = {uint32_t(c.vocab_size), uint32_t(c.embed_dim),
            uint32_t(c.num_layers), uint32_t(c.per_layer_input_dim),
            uint32_t(assets->hf_model ? assets->hf_model->owners.size()
                                      : assets->model->owners.size())};
  });
}
int32_t lab_assets_owner(LabAssets* assets, size_t index, LabKvSpec* out,
                         LabError* error) noexcept {
  return LabCatch(error, [&] {
    LabRequire(assets && out, "Invalid owner request");
    auto c = assets->hf_model ? assets->hf_model->owners.at(index)
                              : assets->model->owners.at(index);
    *out = {uint32_t(c.owner), uint32_t(c.num_heads), uint32_t(c.head_dim)};
  });
}
int32_t lab_assets_embed(LabAssets* assets, const int32_t* tokens, size_t count,
                         void* embedded, size_t embedded_count,
                         void* const* ple, size_t layers, size_t ple_count,
                         size_t element_bytes, LabError* error) noexcept {
  return LabCatch(error, [&] {
    auto c = Config();
    LabRequire(assets && tokens && embedded && ple && count >= 1 &&
                   count <= 128 && layers == size_t(c.num_layers) &&
                   embedded_count >= count * c.embed_dim &&
                   ple_count >= count * c.per_layer_input_dim,
               "Invalid embedding buffers");
    for (size_t i = 0; i < count; ++i)
      LabRequire(tokens[i] >= 0 && tokens[i] < c.vocab_size, "Invalid token");
    for (size_t i = 0; i < layers; ++i) LabRequire(ple[i], "Null PLE buffer");
    LabRequire(element_bytes == (assets->bf16_activations ? 2 : 4),
               "Embedding dtype mismatch");
    if (assets->bf16_activations) {
      auto* model = assets->hf_model.get();
      LabRequire(model, "BF16 requires HF assets");
      model->token_embedding->Lookup(tokens, count,
                                     static_cast<uint16_t*>(embedded));
      std::vector<uint16_t*> pointers;
      for (size_t i = 0; i < layers; ++i)
        pointers.push_back(static_cast<uint16_t*>(ple[i]));
      model->emb_per_layer_table->LookupPerLayer(
          tokens, count, layers, c.per_layer_input_dim, pointers.data());
    } else {
      std::vector<float*> pointers;
      for (size_t i = 0; i < layers; ++i)
        pointers.push_back(static_cast<float*>(ple[i]));
      if (assets->hf_model) {
        assets->hf_model->token_embedding->Lookup(
            tokens, count, static_cast<float*>(embedded));
        assets->hf_model->emb_per_layer_table->LookupPerLayer(
            tokens, count, layers, c.per_layer_input_dim, pointers.data());
      } else {
        assets->model->token_embedding->Lookup(tokens, count,
                                               static_cast<float*>(embedded));
        assets->model->emb_per_layer_table->LookupPerLayer(
            tokens, count, layers, c.per_layer_input_dim, pointers.data());
      }
    }
  });
}
int32_t lab_assets_create_hf(const char* source, const char* manifest,
                             const char* cache, const char* parameters,
                             const char* identity, int32_t bf16,
                             LabAssets** out, LabError* error) noexcept {
  if (out) *out = nullptr;
  return LabCatch(error, [&] {
    LabRequire(source && manifest && cache && parameters && identity && out,
               "Invalid HF asset paths");
    LabRequire(Config().variant == "e2b", "HF assets require E2B");
    LabRequire(LAB_HAS_BF16_ROUNDING,
               "HF packages require the BF16 rounding patch; bootstrap with "
               "--hf-bf16 in a separate LAB_DEPS tree");
    auto assets = std::make_unique<LabAssets>(source, parameters);
    assets->hf_weights = std::make_unique<lab::TensorProvider>(
        source, manifest, cache, parameters);
    assets->hf_model =
        std::make_unique<lab::HfModelAssets>(*assets->hf_weights, identity);
    assets->bf16_activations = bf16 != 0;
    *out = assets.release();
  });
}

}  // extern "C"
