// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
#include "runtime/tokenizer.h"

#include <cmath>
#include <filesystem>
#include <limits>
#include <stdexcept>

#include "runtime/benchmark_io.h"
#include "runtime/sha256.h"

#if LAB_ENABLE_TOKENIZERS
#include "sentencepiece_processor.h"
extern "C" {
struct HfEncodeResult {
  uint32_t* ids;
  size_t len;
};
void* lab_tokenizers_new(const uint8_t*, size_t);
const char* lab_tokenizers_last_error();
int lab_tokenizers_encode(void*, const uint8_t*, size_t, HfEncodeResult*);
int lab_tokenizers_decode(void*, const uint32_t*, size_t, int);
void tokenizers_get_decode_str(void*, char**, size_t*);
size_t lab_tokenizers_vocab_size(void*);
void tokenizers_free_encode_results(HfEncodeResult*, size_t);
void tokenizers_free(void*);
}
#endif

namespace lab {
namespace {
#if LAB_ENABLE_TOKENIZERS
void CheckIds(const std::vector<int32_t>& ids, int vocab_size) {
  for (int32_t id : ids)
    if (id < 0 || id >= vocab_size)
      throw std::invalid_argument("Tokenizer ID outside vocabulary");
}
std::vector<int32_t> Policy(const minijson::object& object, const char* key) {
  std::vector<int32_t> ids;
  for (const auto& value : BenchmarkField<minijson::array>(object, key)) {
    const auto* n = value.as<minijson::number>();
    if (!n || !std::isfinite(*n) || *n < 0 ||
        *n > std::numeric_limits<int32_t>::max() || std::floor(*n) != *n)
      throw std::invalid_argument(std::string("Invalid token policy: ") + key);
    ids.push_back(static_cast<int32_t>(*n));
  }
  return ids;
}
void HfError() {
  throw std::invalid_argument(std::string("HF tokenizer: ") +
                              lab_tokenizers_last_error());
}
class HfTokenizer final : public Tokenizer {
 public:
  HfTokenizer(TokenizerManifest manifest, const std::string& data) {
    manifest_ = std::move(manifest);
    handle_ = lab_tokenizers_new(reinterpret_cast<const uint8_t*>(data.data()),
                                 data.size());
    if (!handle_) HfError();
    const size_t size = lab_tokenizers_vocab_size(handle_);
    if (size != static_cast<size_t>(manifest_.vocab_size)) {
      tokenizers_free(handle_);
      handle_ = nullptr;
      throw std::invalid_argument("HF vocabulary size differs from manifest");
    }
  }
  ~HfTokenizer() override {
    if (handle_) tokenizers_free(handle_);
  }
  std::vector<int32_t> Encode(const std::string& text) override {
    ValidateUtf8(text);
    HfEncodeResult result{};
    if (lab_tokenizers_encode(handle_,
                              reinterpret_cast<const uint8_t*>(text.data()),
                              text.size(), &result))
      HfError();
    // Free Rust's allocation even if vector allocation or ID validation fails.
    struct Guard {
      HfEncodeResult* result;
      ~Guard() { tokenizers_free_encode_results(result, 1); }
    } guard{&result};
    std::vector<int32_t> ids;
    ids.reserve(result.len);
    for (size_t i = 0; i < result.len; ++i) {
      if (result.ids[i] >= static_cast<uint32_t>(manifest_.vocab_size))
        throw std::invalid_argument("HF tokenizer ID outside vocabulary");
      ids.push_back(static_cast<int32_t>(result.ids[i]));
    }
    return ids;
  }
  std::string Decode(const std::vector<int32_t>& ids) override {
    CheckIds(ids, manifest_.vocab_size);
    std::vector<uint32_t> input(ids.begin(), ids.end());
    if (lab_tokenizers_decode(handle_, input.data(), input.size(), 0))
      HfError();
    char* data = nullptr;
    size_t size = 0;
    tokenizers_get_decode_str(handle_, &data, &size);
    return std::string(data, size);
  }

 private:
  void* handle_ = nullptr;
};
class SpTokenizer final : public Tokenizer {
 public:
  SpTokenizer(TokenizerManifest manifest, const std::string& data) {
    manifest_ = std::move(manifest);
    Check(processor_.LoadFromSerializedProto(data));
    if (processor_.GetPieceSize() != manifest_.vocab_size)
      throw std::invalid_argument(
          "SentencePiece vocabulary differs from manifest");
  }
  std::vector<int32_t> Encode(const std::string& text) override {
    ValidateUtf8(text);
    std::vector<int> ids;
    Check(processor_.Encode(text, &ids));
    return {ids.begin(), ids.end()};
  }
  std::string Decode(const std::vector<int32_t>& ids) override {
    CheckIds(ids, manifest_.vocab_size);
    std::vector<int> input(ids.begin(), ids.end());
    std::string text;
    Check(processor_.Decode(input, &text));
    return text;
  }

 private:
  static void Check(const sentencepiece::util::Status& status) {
    if (!status.ok())
      throw std::invalid_argument("SentencePiece: " + status.ToString());
  }
  sentencepiece::SentencePieceProcessor processor_;
};
#endif
}  // namespace

std::unique_ptr<Tokenizer> Tokenizer::Load(const std::string& directory) {
#if LAB_ENABLE_TOKENIZERS
  const auto manifest_data = ReadBenchmarkFile(directory + "/manifest.json");
  const auto object = ParseBenchmarkJson(manifest_data);
  if (BenchmarkInteger(object, "version") != 1)
    throw std::invalid_argument("Unsupported tokenizer manifest version");
  TokenizerManifest manifest;
  manifest.manifest_sha256 =
      Sha256::Digest(manifest_data.data(), manifest_data.size());
  manifest.format = BenchmarkField<std::string>(object, "format");
  manifest.file = BenchmarkField<std::string>(object, "file");
  manifest.sha256 = BenchmarkField<std::string>(object, "sha256");
  manifest.bytes = BenchmarkInteger(object, "bytes");
  const auto vocab_size = BenchmarkInteger(object, "vocab_size");
  if (!vocab_size || vocab_size > std::numeric_limits<int32_t>::max())
    throw std::invalid_argument("Invalid tokenizer vocabulary size");
  manifest.vocab_size = static_cast<int>(vocab_size);
  manifest.prefix_ids = Policy(object, "prefix_ids");
  manifest.suffix_ids = Policy(object, "suffix_ids");
  CheckIds(manifest.prefix_ids, manifest.vocab_size);
  CheckIds(manifest.suffix_ids, manifest.vocab_size);
  const auto source = BenchmarkField<minijson::object>(object, "source");
  const auto repo = BenchmarkField<std::string>(source, "repo");
  const auto revision = BenchmarkField<std::string>(source, "revision");
  if (repo.empty() || revision.empty())
    throw std::invalid_argument("Tokenizer source identity is empty");
  // Preserve the complete source identity, including bundle hashes/ranges.
  manifest.source_json = BenchmarkJson(minijson::value(source));
  const std::filesystem::path relative(manifest.file);
  if (manifest.file.empty() || manifest.file.find('\0') != std::string::npos ||
      relative.is_absolute())
    throw std::invalid_argument("Invalid tokenizer payload path");
  for (const auto& part : relative)
    if (part == "." || part == "..")
      throw std::invalid_argument("Invalid tokenizer payload path");
  const auto data =
      ReadBenchmarkFile((std::filesystem::path(directory) / relative).string());
  if (data.size() != manifest.bytes ||
      Sha256::Digest(data.data(), data.size()) != manifest.sha256)
    throw std::invalid_argument("Tokenizer payload hash/size mismatch");
  std::unique_ptr<Tokenizer> tokenizer;
  if (manifest.format == "hf_json")
    tokenizer = std::make_unique<HfTokenizer>(std::move(manifest), data);
  else if (manifest.format == "sentencepiece")
    tokenizer = std::make_unique<SpTokenizer>(std::move(manifest), data);
  else
    throw std::invalid_argument("Unsupported tokenizer format: " +
                                manifest.format);
  // Check that declared policy IDs also exist in sparse HF vocabularies.
  tokenizer->Decode(tokenizer->manifest().prefix_ids);
  tokenizer->Decode(tokenizer->manifest().suffix_ids);
  return tokenizer;
#else
  throw std::invalid_argument("Text input requires LAB_ENABLE_TOKENIZERS=ON");
#endif
}
}  // namespace lab
