// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
// Embedding unpacking follows LiteRT's Apache-2.0 Gemma example.
#pragma once

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include <cmath>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <limits>
#include <map>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "third_party/minijson.h"

namespace lab {
using Object = minijson::object;
using Array = minijson::array;
template <typename T>
T Field(const Object& object, const std::string& name) {
  minijson::value value;
  if (!object.at(name, &value) || !value.as<T>())
    throw std::invalid_argument("Missing/incorrect field: " + name);
  return *value.as<T>();
}
inline size_t Integer(const Object& object, const std::string& name) {
  double v = Field<minijson::number>(object, name);
  if (!std::isfinite(v) || v < 0 || v > 9007199254740991.0 ||
      std::floor(v) != v)
    throw std::invalid_argument("Invalid integer: " + name);
  return static_cast<size_t>(v);
}
inline Object ReadJson(const std::string& path) {
  std::ifstream f(path, std::ios::binary);
  if (!f) throw std::invalid_argument("Cannot read: " + path);
  std::string data((std::istreambuf_iterator<char>(f)), {});
  minijson::value value;
  const char* at = data.c_str();
  if (minijson::parse(at, value) != minijson::no_error || !value.as<Object>())
    throw std::invalid_argument("Invalid JSON: " + path);
  while (*at == ' ' || *at == '\n' || *at == '\r' || *at == '\t') ++at;
  if (*at) throw std::invalid_argument("Trailing JSON data");
  return *value.as<Object>();
}

class Weights {
 public:
  Weights(std::string bundle, std::string parameters)
      : bundle_(std::move(bundle)), parameters_(std::move(parameters)) {}
  Weights(const Weights&) = delete;
  Weights& operator=(const Weights&) = delete;
  ~Weights() {
    for (const auto& [_, m] : maps_) munmap(m.first, m.second);
  }
  const void* Get(const char* name, size_t bytes) {
    std::string key(name);
    auto it = maps_.find(key);
    if (it != maps_.end()) {
      if (it->second.second != bytes)
        throw std::runtime_error("Weight size mismatch");
      return it->second.first;
    }
    const bool parameter = key.rfind("@parameters/", 0) == 0;
    const auto relative = parameter ? key.substr(12) : key;
    const std::filesystem::path path(relative);
    if (relative.empty() || path.is_absolute() || bytes == 0)
      throw std::invalid_argument("Invalid relative weight path");
    for (const auto& part : path)
      if (part == "." || part == "..")
        throw std::invalid_argument("Invalid weight path");
    const auto full = (parameter ? parameters_ : bundle_) + "/" + relative;
    int fd = open(full.c_str(), O_RDONLY | O_CLOEXEC);
    struct stat st{};
    if (fd < 0 || fstat(fd, &st) || !S_ISREG(st.st_mode) || st.st_size < 0 ||
        static_cast<size_t>(st.st_size) != bytes) {
      if (fd >= 0) close(fd);
      throw std::runtime_error("Missing/wrong weight file: " + full);
    }
    void* data = mmap(nullptr, bytes, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);
    if (data == MAP_FAILED) throw std::runtime_error("mmap failed: " + full);
    maps_[key] = {data, bytes};
    return data;
  }

 private:
  std::string bundle_, parameters_;
  std::map<std::string, std::pair<void*, size_t>> maps_;
};

struct KvOwner {
  int owner, head_dim, num_heads;
};

// Model dimensions remain separate from capacity and active execution extents.
struct Gemma4Config {
  int vocab_size = 262144, embed_dim = 1536, num_layers = 35;
  int per_layer_input_dim = 256;
  int num_kv_heads = 1, num_kv_owners = 15, attention_pattern = 5;
  int per_layer_bits = 4;
  std::string variant = "e2b";
  static Gemma4Config E2B() { return {}; }
  static Gemma4Config E4B() {
    Gemma4Config c;
    c.embed_dim = 2560;
    c.num_layers = 42;
    c.num_kv_heads = 2;
    c.num_kv_owners = 24;
    c.attention_pattern = 6;
    c.per_layer_bits = 2;
    c.variant = "e4b";
    return c;
  }
};

class Embedding {
 public:
  Embedding(const Object& record, size_t rows, size_t width, int expected_bits,
            size_t expected_block, Weights& weights)
      : rows_(rows),
        width_(width),
        block_(expected_block),
        bits_(expected_bits) {
    const auto shape = Field<Array>(record, "shape");
    if (shape.size() != 2 || !shape[0].as<minijson::number>() ||
        !shape[1].as<minijson::number>() ||
        *shape[0].as<minijson::number>() != rows ||
        *shape[1].as<minijson::number>() != width ||
        Field<std::string>(record, "dtype") != "int" + std::to_string(bits_) ||
        width % (8 / bits_) || width % block_)
      throw std::invalid_argument("Embedding shape/type mismatch");
    const size_t bytes = rows * width / (8 / bits_);
    if (Integer(record, "bytes") != bytes)
      throw std::invalid_argument("Embedding byte count");
    data_ = static_cast<const uint8_t*>(
        weights.Get(Field<std::string>(record, "file").c_str(), bytes));
    const auto q = Field<Object>(record, "quantization");
    const auto zeros = Field<Array>(q, "zero_points");
    if (zeros.size() != 1 || !zeros[0].as<minijson::number>() ||
        *zeros[0].as<minijson::number>() != 0 ||
        Integer(q, "quantized_dimension") != 0 ||
        Field<std::string>(q, "scales_dtype") != "float32" ||
        Field<std::string>(q, "kind") !=
            (block_ == width_ ? "per_channel" : "blockwise") ||
        (block_ != width_ && Integer(q, "block_size") != block_))
      throw std::invalid_argument("Unsupported embedding quantization");
    const size_t count = rows * (width / block_);
    if (Integer(q, "scales_bytes") != count * sizeof(float))
      throw std::invalid_argument("Embedding scale bytes");
    scales_ = static_cast<const float*>(weights.Get(
        Field<std::string>(q, "scales_file").c_str(), count * sizeof(float)));
    for (size_t i = 0; i < count; ++i)
      if (!(scales_[i] > 0) || !std::isfinite(scales_[i]))
        throw std::invalid_argument("Invalid embedding scale");
  }
  void Lookup(const int32_t* tokens, size_t count, float* output) const {
    for (size_t i = 0; i < count; ++i)
      Decode(tokens[i], 0, width_, output + i * width_);
  }
  void LookupPerLayer(const int32_t* tokens, size_t count, int layers, int dim,
                      std::vector<std::vector<float>>& output) const {
    if (size_t(layers) * dim != width_ || output.size() != size_t(layers))
      throw std::invalid_argument("PLE dimensions");
    for (size_t i = 0; i < count; ++i)
      for (int l = 0; l < layers; ++l)
        Decode(tokens[i], l * dim, dim, output[l].data() + i * dim);
  }

 private:
  void Decode(int32_t row, size_t begin, size_t count, float* dst) const {
    if (row < 0 || size_t(row) >= rows_ || begin + count > width_)
      throw std::invalid_argument("Embedding index out of bounds");
    const int fields = 8 / bits_, mask = (1 << bits_) - 1;
    const uint8_t* src = data_ + size_t(row) * (width_ / fields);
    const float* scales = scales_ + size_t(row) * (width_ / block_);
    for (size_t i = 0; i < count; ++i) {
      const size_t col = begin + i;
      int code = (src[col / fields] >> ((col % fields) * bits_)) & mask;
      if (code & (1 << (bits_ - 1))) code -= 1 << bits_;
      dst[i] = static_cast<float>(code) * scales[col / block_];
    }
  }
  size_t rows_, width_, block_;
  int bits_;
  const uint8_t* data_;
  const float* scales_;
};

struct ModelAssets {
  std::unique_ptr<Embedding> token_embedding, emb_per_layer_table;
  std::vector<KvOwner> owners;
  ModelAssets(const std::string& bundle, Weights& weights,
              const Gemma4Config& config) {
    const auto manifest = ReadJson(bundle + "/manifest.json");
    if (Field<std::string>(manifest, "status") != "complete" ||
        Field<std::string>(manifest, "experimental_storage") !=
            "compact_int2_v1")
      throw std::invalid_argument("A validated compact Gemma4 bundle is required");
    if (config.variant == "e4b") {
      const auto metadata = Field<Object>(manifest, "model_config");
      if (Field<std::string>(metadata, "variant") != "e4b" ||
          Integer(metadata, "num_kv_heads") != 2 ||
          Integer(metadata, "num_layers") != 42 ||
          Integer(metadata, "embed_dim") != 2560)
        throw std::invalid_argument("E4B architecture mismatch");
    }
    for (const auto& value : Field<Array>(manifest, "tensors")) {
      if (!value.as<Object>()) throw std::invalid_argument("Tensor record");
      const auto& rec = *value.as<Object>();
      const auto name = Field<std::string>(rec, "name");
      if (name == "model.embed_tokens.weight")
        token_embedding = std::make_unique<Embedding>(
            rec, config.vocab_size, config.embed_dim, 2, config.embed_dim,
            weights);
      if (name == "model.embed_tokens_per_layer.weight")
        emb_per_layer_table = std::make_unique<Embedding>(
            rec, config.vocab_size,
            config.num_layers * config.per_layer_input_dim,
            config.per_layer_bits, 256, weights);
    }
    if (!token_embedding || !emb_per_layer_table)
      throw std::invalid_argument("Missing embeddings");
    const auto kv = Field<Array>(manifest, "kv_cache_specs");
    if (kv.size() != size_t(config.num_kv_owners))
      throw std::invalid_argument("Incorrect KV owner count");
    owners.resize(config.num_kv_owners);
    std::vector<bool> seen(config.num_kv_owners);
    for (const auto& value : kv) {
      if (!value.as<Object>()) throw std::invalid_argument("KV record");
      const auto& rec = *value.as<Object>();
      auto owner = Integer(rec, "owner"), dim = Integer(rec, "head_dim");
      if (owner >= size_t(config.num_kv_owners) || seen[owner] ||
          dim != ((owner + 1) % config.attention_pattern == 0 ? 512 : 256) ||
          Integer(rec, "zero_point") != 0)
        throw std::invalid_argument("Unexpected KV owner layout");
      if (config.num_kv_heads > 1 &&
          Integer(rec, "num_kv_heads") != size_t(config.num_kv_heads))
        throw std::invalid_argument("KV head count mismatch");
      seen[owner] = true;
      owners[owner] = {int(owner), int(dim), config.num_kv_heads};
    }
  }
};
}  // namespace lab
