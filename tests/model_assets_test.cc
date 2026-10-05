// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
#include "runtime/model_assets.h"

#include <cstring>
#include <iostream>

namespace {
void Expect(bool value) {
  if (!value) throw std::runtime_error("Embedding test failed");
}
void Write(const std::string& file, const void* data, size_t bytes) {
  std::ofstream f(file, std::ios::binary);
  if (!f.write(static_cast<const char*>(data), bytes))
    throw std::runtime_error("Test fixture write failed");
}
void Test(const std::string& dir, int bits, bool blockwise) {
  // Two rows, eight columns, covering every INT2 code and signed INT4 tails.
  int codes[16] = {-2, -1, 0, 1, 1, 0, -1, -2, 1, 0, -1, -2, -2, -1, 0, 1};
  if (bits == 4) {
    codes[0] = -8;
    codes[1] = -7;
    codes[4] = 7;
    codes[11] = -8;
  }
  std::vector<uint8_t> bytes(16 * bits / 8);
  for (int i = 0; i < 16; ++i)
    bytes[i / (8 / bits)] |= (codes[i] & ((1 << bits) - 1))
                             << ((i % (8 / bits)) * bits);
  const float scales[4] = {0.5f, 2.0f, 4.0f, 8.0f};
  const int block = blockwise ? 4 : 8;
  Write(dir + "/weight", bytes.data(), bytes.size());
  Write(dir + "/scale", scales, 16 / block * sizeof(float));
  const std::string json =
      "{\"shape\":[2,8],\"dtype\":\"int" + std::to_string(bits) +
      "\",\"file\":\"weight\",\"bytes\":" + std::to_string(bytes.size()) +
      ",\"quantization\":{\"zero_points\":[0],\"quantized_dimension\":0,"
      "\"scales_dtype\":\"float32\",\"kind\":\"" +
      (blockwise ? "blockwise" : "per_channel") +
      "\",\"block_size\":" + std::to_string(block) +
      ",\"scales_file\":\"scale\",\"scales_bytes\":" +
      std::to_string(16 / block * sizeof(float)) + "}}";
  Write(dir + "/record.json", json.data(), json.size());
  lab::Weights weights(dir, dir);
  lab::Embedding embedding(lab::ReadJson(dir + "/record.json"), 2, 8, bits,
                           block, weights);
  int32_t tokens[] = {1, 0};
  float output[16];
  embedding.Lookup(tokens, 2, output);
  for (int i = 0; i < 16; ++i) {
    const int index = tokens[i / 8] * 8 + i % 8;
    Expect(output[i] == codes[index] * scales[index / block]);
  }
  std::vector<std::vector<float>> ple(2, std::vector<float>(8));
  embedding.LookupPerLayer(tokens, 2, 2, 4, ple);
  for (int t = 0; t < 2; ++t)
    for (int l = 0; l < 2; ++l)
      for (int d = 0; d < 4; ++d)
        Expect(ple[l][t * 4 + d] == output[t * 8 + l * 4 + d]);
  bool rejected = false;
  tokens[0] = 2;
  try {
    embedding.Lookup(tokens, 1, output);
  } catch (const std::invalid_argument&) {
    rejected = true;
  }
  Expect(rejected);
}
}  // namespace

int main() {
  // Android does not have /tmp. CTest's working directory is writable on host;
  // the phone invocation also runs inside its writable test directory.
  char relative[] = "ynnpack-embedding-test-XXXXXX";
  const char* dir = mkdtemp(relative);
  if (!dir) return 1;
  try {
    Test(dir, 2, false);
    Test(dir, 2, true);
    Test(dir, 4, true);
    std::filesystem::remove_all(dir);
    std::cout << "INT2 per-channel and INT2/INT4 blockwise embeddings passed\n";
    return 0;
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    std::filesystem::remove_all(dir);
    return 1;
  }
}
