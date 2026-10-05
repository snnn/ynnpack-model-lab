// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
#include <iostream>

#include "models/gemma4/hf_assets.h"

namespace {
void Write(const std::string& path, const std::string& data) {
  std::ofstream f(path, std::ios::binary);
  if (!f.write(data.data(), data.size()))
    throw std::runtime_error("Fixture write");
}
void Expect(bool b) {
  if (!b) throw std::runtime_error("Asset assertion failed");
}
template <class F>
void Reject(F f) {
  bool rejected = false;
  try {
    f();
  } catch (const std::exception&) {
    rejected = true;
  }
  Expect(rejected);
}
void Test(const std::string& root, int bits) {
  std::string data;
  for (int i = 0; i < 256; ++i) data.push_back(i);
  const auto hash = lab::Sha256::Digest(data.data(), data.size());
  // A two-byte origin deliberately misaligns the FP32 coefficient.
  const float coefficient = 1.25f;
  std::string scale(reinterpret_cast<const char*>(&coefficient), 4);
  Write(root + "/shard", "xx" + scale + data);
  const auto manifest =
      "{\"shards\":{\"shard\":{\"bytes\":262}},\"tensors\":{"
      "\"w\":{\"file\":\"shard\",\"offset\":6,\"bytes\":256,\"bits\":" +
      std::to_string(bits) +
      ",\"dtype\":\"U8\",\"encoding\":\"offset_binary_low_first\",\"sha256\":"
      "\"" +
      hash +
      "\"},"
      "\"scale\":{\"file\":\"shard\",\"offset\":2,\"bytes\":4,\"dtype\":"
      "\"F32\",\"encoding\":\"identity\",\"sha256\":\"" +
      lab::Sha256::Digest(scale.data(), 4) + "\"}}}";
  Write(root + "/manifest.json", manifest);
  const auto cache = root + "/cache";
  const auto name =
      cache + "/" + hash + ".signed" + std::to_string(bits) + "-v1.bin";
  for (int pass = 0; pass < 2; ++pass) {
    lab::TensorProvider p(root, root + "/manifest.json", cache, root);
    const auto* raw = p.Raw("w");
    const auto* converted = static_cast<const uint8_t*>(p.Get("@hf/w", 256));
    Expect(p.Get("@hf/w", 256) == converted);
    for (int byte = 0; byte < 256; ++byte)
      for (int field = 0; field < 8 / bits; ++field) {
        const int offset = (raw[byte] >> (bits * field)) & ((1 << bits) - 1);
        int actual = (converted[byte] >> (bits * field)) & ((1 << bits) - 1);
        if (actual & (1 << (bits - 1))) actual -= 1 << bits;
        Expect(actual == offset - (1 << (bits - 1)));
      }
    const auto* f = static_cast<const float*>(p.Get("@hf/scale", 4));
    Expect(reinterpret_cast<uintptr_t>(f) % alignof(float) == 0 &&
           *f == coefficient);
    Reject([&] { p.Get("@hf/w", 255); });
  }
  Write(name, std::string(256, '\0'));
  lab::TensorProvider bad(root, root + "/manifest.json", cache, root);
  Reject([&] { bad.Get("@hf/w", 256); });
  Reject([&] {
    bad.Get("@hf/w", 256);
  });  // failure cannot mark the cache verified
  std::filesystem::remove(name);
  Write(root + "/shard", std::string(262, '\0'));
  lab::TensorProvider changed(root, root + "/manifest.json", cache, root);
  Reject([&] { changed.Raw("w"); });
  Reject([&] { changed.Raw("w"); });
  Write(root + "/shard", "short");
  lab::TensorProvider truncated(root, root + "/manifest.json", cache, root);
  Reject([&] { truncated.Raw("w"); });
}

void TestEmbedding(const std::string& root, int bits) {
  const size_t rows = 2, width = 16, block = 8;
  const float scales[] = {0.033181842f, 0.608803451f, 0.10001f, 1.003f};
  const float multiplier = std::sqrt(1536.0f);
  std::string weights(rows * width * bits / 8, '\0');
  std::vector<int> codes(rows * width);
  for (size_t i = 0; i < codes.size(); ++i) {
    const int encoded = i % (1 << bits);
    codes[i] = encoded - (1 << (bits - 1));
    weights[i * bits / 8] |= encoded << ((i * bits) % 8);
  }
  std::string scale_bytes(reinterpret_cast<const char*>(scales),
                          sizeof(scales));
  Write(root + "/embedding", weights + scale_bytes);
  std::ostringstream manifest;
  manifest
      << "{\"shards\":{\"embedding\":{\"bytes\":"
      << weights.size() + scale_bytes.size()
      << "}},\"tensors\":{\"e.weight\":{\"file\":\"embedding\","
         "\"offset\":0,\"bytes\":"
      << weights.size() << ",\"dtype\":\"U8\",\"bits\":" << bits
      << ",\"logical_shape\":[2,16],\"encoding\":\"offset_binary_low_first\","
         "\"sha256\":\""
      << lab::Sha256::Digest(weights.data(), weights.size())
      << "\"},\"e.weight_scale\":{\"file\":\"embedding\",\"offset\":"
      << weights.size() << ",\"bytes\":" << sizeof(scales)
      << ",\"dtype\":\"F32\",\"logical_shape\":[2,2],\"encoding\":\"identity\","
         "\"sha256\":\""
      << lab::Sha256::Digest(scales, sizeof(scales)) << "\"}}}";
  Write(root + "/embedding.json", manifest.str());
  lab::TensorProvider provider(root, root + "/embedding.json", root + "/cache",
                               root);
  lab::HfEmbedding embedding(provider, "e", rows, width, block, bits,
                             multiplier);
  int32_t tokens[] = {1, 0};
  std::vector<float> full(32);
  std::vector<uint16_t> bf16(32);
  std::vector<std::vector<float>> ple(2, std::vector<float>(16));
  embedding.Lookup(tokens, 2, full.data());
  embedding.Lookup(tokens, 2, bf16.data());
  embedding.LookupPerLayer(tokens, 2, 2, 8, ple);
  int differences = 0;
  for (size_t t = 0; t < 2; ++t) {
    for (size_t c = 0; c < width; ++c) {
      const int code = codes[tokens[t] * width + c];
      const float scale = scales[tokens[t] * 2 + c / block];
      const float dequantized = float(code) * scale;
      const float expected = dequantized * multiplier;
      Expect(full[t * width + c] == expected);
      Expect(ple[c / 8][t * 8 + c % 8] == expected);
      Expect(
          bf16[t * width + c] ==
          lab::Bf16(lab::Float(lab::Bf16(code * lab::Float(lab::Bf16(scale)))) *
                    multiplier));
      differences += full[t * width + c] != lab::Float(bf16[t * width + c]);
    }
  }
  Expect(differences > 0);
}
}  // namespace
int main() {
  char pattern[] = "ynnpack-hf-assets-XXXXXX";
  const char* root = mkdtemp(pattern);
  if (!root) return 1;
  try {
    Test(root, 2);
    Test(root, 4);
    TestEmbedding(root, 2);
    TestEmbedding(root, 4);
    std::filesystem::remove_all(root);
    std::cout << "All packed byte patterns, warm cache, corruption, and "
                 "unaligned coefficients passed\n";
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    std::filesystem::remove_all(root);
    return 1;
  }
}
