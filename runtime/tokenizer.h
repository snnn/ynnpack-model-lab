// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace lab {
struct TokenizerManifest {
  std::string format, file, sha256, source_json, manifest_sha256;
  size_t bytes = 0;
  int vocab_size = 0;
  std::vector<int32_t> prefix_ids, suffix_ids;
};
class Tokenizer {
 public:
  // Verifies manifest and payload integrity before loading the native engine.
  static std::unique_ptr<Tokenizer> Load(const std::string& directory);
  virtual ~Tokenizer() = default;
  virtual std::vector<int32_t> Encode(const std::string& text) = 0;
  virtual std::string Decode(const std::vector<int32_t>& ids) = 0;
  const TokenizerManifest& manifest() const { return manifest_; }

 protected:
  TokenizerManifest manifest_;
};
}  // namespace lab
