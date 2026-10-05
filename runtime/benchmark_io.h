// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <string_view>

#include "third_party/minijson.h"

namespace lab {
// Text files are binary reads: no trimming, newline conversion, or NUL loss.
std::string ReadBenchmarkFile(const std::string& path);
void ValidateUtf8(std::string_view text);
minijson::object ParseBenchmarkJson(const std::string& data);
std::string JsonString(std::string_view value);
std::string BenchmarkJson(const minijson::value& value);
template <typename T>
T BenchmarkField(const minijson::object& object, const std::string& key) {
  minijson::value value;
  if (!object.at(key, &value) || !value.as<T>())
    throw std::invalid_argument("Missing/incorrect field: " + key);
  return *value.as<T>();
}
size_t BenchmarkInteger(const minijson::object& object, const std::string& key);
}  // namespace lab
