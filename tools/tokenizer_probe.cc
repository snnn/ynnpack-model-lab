// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
// Resolve text fixtures without model weights; useful for tokenizer parity.
#include <filesystem>
#include <iostream>

#include "runtime/benchmark_cases.h"

int main(int argc, char** argv) {
  try {
    const auto options = lab::ParseOptions(argc, argv, false);
    const auto frontend = lab::ResolveBenchmarkCases(options, 0);
    if (std::filesystem::exists(options.output_dir))
      throw std::invalid_argument("New output directory required");
    std::filesystem::create_directories(options.output_dir);
    frontend.Save(options.output_dir);
    std::cout << frontend.resolved_tsv;
    return 0;
  } catch (const std::exception& error) {
    std::cerr << error.what() << '\n';
    return 1;
  }
}
