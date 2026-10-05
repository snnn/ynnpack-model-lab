// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
#pragma once
#include <type_traits>

#include "runtime/safetensors_assets.h"

namespace lab {
inline uint16_t Bf16(float x) {
  uint32_t bits;
  std::memcpy(&bits, &x, sizeof(bits));
  if ((bits & 0x7fffffff) > 0x7f800000) return (bits >> 16) | 0x40;
  return (bits + 0x7fff + ((bits >> 16) & 1)) >> 16;
}
inline float Float(uint16_t x) {
  uint32_t bits = uint32_t(x) << 16;
  float f;
  std::memcpy(&f, &bits, sizeof(f));
  return f;
}

class HfEmbedding {
 public:
  HfEmbedding(TensorProvider& provider, const std::string& module, size_t rows,
              size_t width, size_t block, int bits, float multiplier)
      : rows_(rows),
        width_(width),
        block_(block),
        bits_(bits),
        multiplier_(multiplier) {
    if (!rows || !width || !block || width % block ||
        (bits != 2 && bits != 4) || width % (8 / bits) ||
        rows > std::numeric_limits<size_t>::max() / width / 4 ||
        !std::isfinite(multiplier))
      throw std::invalid_argument("Invalid HF embedding dimensions");
    const auto rec = provider.Record(module + ".weight");
    const auto shape = Field<Array>(rec, "logical_shape");
    const auto scale = provider.Record(module + ".weight_scale");
    const auto scale_shape = Field<Array>(scale, "logical_shape");
    if (shape.size() != 2 || scale_shape.size() != 2 ||
        !shape[0].as<minijson::number>() || !shape[1].as<minijson::number>() ||
        !scale_shape[0].as<minijson::number>() ||
        !scale_shape[1].as<minijson::number>() ||
        *shape[0].as<minijson::number>() != rows ||
        *shape[1].as<minijson::number>() != width ||
        *scale_shape[0].as<minijson::number>() != rows ||
        *scale_shape[1].as<minijson::number>() != width / block ||
        Integer(rec, "bits") != size_t(bits) || (bits != 2 && bits != 4) ||
        Integer(rec, "bytes") != rows * width / (8 / bits) ||
        Field<std::string>(rec, "encoding") != "offset_binary_low_first" ||
        Field<std::string>(scale, "dtype") != "F32" ||
        Integer(scale, "bytes") != rows * (width / block) * 4)
      throw std::invalid_argument("HF embedding layout mismatch");
    data_ = provider.Raw(module + ".weight");
    scales_ = provider.Raw(module + ".weight_scale");
  }
  template <typename T>
  void Lookup(const int32_t* tokens, size_t count, T* output) const {
    for (size_t t = 0; t < count; ++t)
      Decode(tokens[t], 0, width_, output + t * width_);
  }
  template <typename T>
  void LookupPerLayer(const int32_t* tokens, size_t count, int layers, int dim,
                      std::vector<std::vector<T>>& output) const {
    if (size_t(layers) * dim != width_ || output.size() != size_t(layers))
      throw std::invalid_argument("HF PLE shape mismatch");
    for (size_t t = 0; t < count; ++t)
      for (int l = 0; l < layers; ++l)
        Decode(tokens[t], l * dim, dim, output[l].data() + t * dim);
  }

 private:
  template <typename T>
  void Decode(int row, size_t begin, size_t n, T* output) const {
    static_assert(std::is_same_v<T, float> || std::is_same_v<T, uint16_t>);
    if (row < 0 || size_t(row) >= rows_ || begin > width_ || n > width_ - begin)
      throw std::invalid_argument("HF embedding row out of bounds");
    const size_t fields = 8 / bits_, mask = (1 << bits_) - 1;
    const auto* codes = data_ + size_t(row) * (width_ / fields);
    for (size_t i = 0; i < n; ++i) {
      const size_t col = begin + i;
      const int code =
          int((codes[col / fields] >> ((col % fields) * bits_)) & mask) -
          (1 << (bits_ - 1));
      float scale;
      std::memcpy(
          &scale,
          scales_ + (size_t(row) * (width_ / block_) + col / block_) * 4, 4);
      // HF casts scale to output dtype, multiplies codes, then multiplies the
      // Python scalar embed_scale. Both tensor results are rounded to BF16.
      if constexpr (std::is_same_v<T, float>) {
        output[i] = (code * scale) * multiplier_;
      } else {
        output[i] = Bf16(Float(Bf16(code * Float(Bf16(scale)))) * multiplier_);
      }
    }
  }
  size_t rows_, width_, block_;
  int bits_;
  float multiplier_;
  const uint8_t *data_, *scales_;
};

struct HfModelAssets {
  std::unique_ptr<HfEmbedding> token_embedding, emb_per_layer_table;
  std::vector<KvOwner> owners;
  HfModelAssets(TensorProvider& provider, const char* identity) {
    const auto& manifest = provider.manifest();
    if (Field<std::string>(manifest, "format") != "gemma4_hf_assets_v1" ||
        Field<std::string>(manifest, "source_identity") != identity)
      throw std::invalid_argument("HF manifest does not match generated graph");
    token_embedding =
        std::make_unique<HfEmbedding>(provider, "model.embed_tokens", 262144,
                                      1536, 1536, 2, std::sqrt(1536.0f));
    emb_per_layer_table = std::make_unique<HfEmbedding>(
        provider, "model.embed_tokens_per_layer", 262144, 8960, 256, 4, 16.0f);
    for (int i = 0; i < 15; ++i)
      owners.push_back({i, i % 5 == 4 ? 512 : 256, 1});
  }
};
}  // namespace lab
