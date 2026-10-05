// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
#include "runtime/benchmark_io.h"

#include <cmath>
#include <fstream>
#include <iomanip>
#include <limits>
#include <sstream>
#include <stdexcept>

namespace lab {
std::string ReadBenchmarkFile(const std::string& path) {
  std::ifstream input(path, std::ios::binary);
  if (!input) throw std::invalid_argument("Cannot read: " + path);
  std::string data((std::istreambuf_iterator<char>(input)), {});
  if (input.bad()) throw std::runtime_error("Read failed: " + path);
  return data;
}
void ValidateUtf8(std::string_view text) {
  size_t i = 0;
  while (i < text.size()) {
    const unsigned char first = text[i++];
    if (first < 0x80) continue;
    int count;
    uint32_t value, minimum;
    if (first >= 0xc2 && first <= 0xdf) {
      count = 1;
      value = first & 0x1f;
      minimum = 0x80;
    } else if (first >= 0xe0 && first <= 0xef) {
      count = 2;
      value = first & 0xf;
      minimum = 0x800;
    } else if (first >= 0xf0 && first <= 0xf4) {
      count = 3;
      value = first & 7;
      minimum = 0x10000;
    } else {
      throw std::invalid_argument("Invalid UTF-8");
    }
    if (text.size() - i < static_cast<size_t>(count))
      throw std::invalid_argument("Truncated UTF-8");
    while (count--) {
      const unsigned char next = text[i++];
      if ((next & 0xc0) != 0x80) throw std::invalid_argument("Invalid UTF-8");
      value = (value << 6) | (next & 0x3f);
    }
    if (value < minimum || value > 0x10ffff ||
        (value >= 0xd800 && value <= 0xdfff))
      throw std::invalid_argument("Invalid UTF-8 code point");
  }
}
minijson::object ParseBenchmarkJson(const std::string& data) {
  ValidateUtf8(data);
  if (data.find('\0') != std::string::npos)
    throw std::invalid_argument("Unescaped NUL in JSON");
  minijson::value value;
  const char* at = data.c_str();
  if (minijson::parse(at, value) != minijson::no_error ||
      !value.as<minijson::object>())
    throw std::invalid_argument("Invalid JSON object");
  while (*at == ' ' || *at == '\t' || *at == '\r' || *at == '\n') ++at;
  if (*at) throw std::invalid_argument("Trailing JSON data");
  return *value.as<minijson::object>();
}
size_t BenchmarkInteger(const minijson::object& object,
                        const std::string& key) {
  double n = BenchmarkField<minijson::number>(object, key);
  if (!std::isfinite(n) || n < 0 || n > 9007199254740991.0 ||
      n >= static_cast<double>(std::numeric_limits<size_t>::max()) ||
      std::floor(n) != n)
    throw std::invalid_argument("Invalid integer: " + key);
  return static_cast<size_t>(n);
}
std::string JsonString(std::string_view value) {
  static constexpr char hex[] = "0123456789abcdef";
  std::string out = "\"";
  for (unsigned char c : value) {
    if (c == '"' || c == '\\') {
      out += '\\';
      out += c;
    } else if (c < 0x20) {
      out += "\\u00";
      out += hex[c >> 4];
      out += hex[c & 15];
    } else {
      out += c;
    }
  }
  return out + '"';
}
std::string BenchmarkJson(const minijson::value& value) {
  if (const auto* text = value.as<std::string>()) return JsonString(*text);
  if (const auto* number = value.as<minijson::number>()) {
    std::ostringstream out;
    out << std::setprecision(17) << *number;
    return out.str();
  }
  if (const auto* array = value.as<minijson::array>()) {
    std::string out = "[";
    for (const auto& item : *array) {
      if (out.size() > 1) out += ',';
      out += BenchmarkJson(item);
    }
    return out + ']';
  }
  if (const auto* object = value.as<minijson::object>()) {
    std::string out = "{";
    for (const auto& key : object->keys()) {
      minijson::value item;
      object->at(key, &item);
      if (out.size() > 1) out += ',';
      out += JsonString(key) + ':' + BenchmarkJson(item);
    }
    return out + '}';
  }
  return value.str();
}
}  // namespace lab
