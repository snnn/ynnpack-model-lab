// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "runtime/options.h"

namespace lab {
struct BenchmarkCase {
  std::string name;
  std::vector<int32_t> prompt, continuation;
};
struct BenchmarkFrontend {
  std::vector<BenchmarkCase> cases;
  std::string resolved_tsv, metadata_json;
  void Save(const std::string& output_dir) const;
};
// Resolve and validate every case before the caller prepares or mutates a
// model. A zero vocabulary size is allowed only for the weights-free text
// probe.
BenchmarkFrontend ResolveBenchmarkCases(const Options& options, int vocab_size);
}  // namespace lab
