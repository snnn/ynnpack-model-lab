// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
// Reproduce the first FP32 input from LiteRT benchmark_model: the default-seeded
// mt19937 and uniform_real_distribution<float>(-0.5, 0.5) in tflite/tools/utils.cc.
// Build with the benchmark's C++ standard library: distributions are not
// guaranteed to produce identical sequences across different STL libraries.
#include <cstdio>
#include <random>
#include <vector>

int main(int argc, char** argv) {
  if (argc != 2) {
    std::fprintf(stderr, "Usage: vision_benchmark_input OUTPUT.bin\n");
    return 1;
  }
  static_assert(sizeof(float) == 4);
  std::mt19937 engine;
  std::uniform_real_distribution<float> distribution(-0.5f, 0.5f);
  std::vector<float> input(1 * 3 * 224 * 224);
  for (auto& value : input) value = distribution(engine);
  auto* file = std::fopen(argv[1], "wbx");
  if (!file) return 1;
  const auto written = std::fwrite(input.data(), sizeof(float), input.size(), file);
  const auto status = std::fclose(file);
  return written == input.size() && status == 0 ? 0 : 1;
}
