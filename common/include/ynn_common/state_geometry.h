// Copyright 2026 @snnn. Licensed under the Apache License, Version 2.0.
#pragma once
#include <algorithm>
#include <cstdint>
#include <limits>
#include <stdexcept>
#include <vector>

namespace ynn_common {
// Element strides, including sub-byte elements. A representation is row-major
// with optional padding, never an inference from its allocation size.
struct StateGeometry {
  std::vector<int64_t> shape, strides;
  int axis = 0;
  int64_t span = 0;
  StateGeometry(std::vector<int64_t> dims, int append_axis,
                std::vector<int64_t> steps = {})
      : shape(std::move(dims)), strides(std::move(steps)), axis(append_axis) {
    if (axis < 0 || axis >= int(shape.size()))
      throw std::invalid_argument("invalid state axis");
    if (strides.empty()) {
      strides.resize(shape.size());
      int64_t n = 1;
      for (size_t i = shape.size(); i-- > 0;) {
        strides[i] = n;
        n = Multiply(n, std::max<int64_t>(1, shape[i]));
      }
    }
    if (strides.size() != shape.size())
      throw std::invalid_argument("state stride rank");
    int64_t inner = 1;
    bool empty = false;
    for (size_t i = shape.size(); i-- > 0;) {
      if (shape[i] < 0 || strides[i] < inner)
        throw std::invalid_argument("invalid or overlapping state strides");
      empty |= shape[i] == 0;
      inner = Multiply(strides[i], std::max<int64_t>(1, shape[i]));
      span =
          Add(span, Multiply(std::max<int64_t>(0, shape[i] - 1), strides[i]));
    }
    span = empty ? 0 : Add(span, 1);
  }
  static int64_t Multiply(int64_t a, int64_t b) {
    if (a < 0 || b < 0 || (b && a > INT64_MAX / b))
      throw std::overflow_error("state address multiplication");
    return a * b;
  }
  static int64_t Add(int64_t a, int64_t b) {
    if (a < 0 || b < 0 || a > INT64_MAX - b)
      throw std::overflow_error("state address addition");
    return a + b;
  }
  // Decode a physical element. False means padding, including trailing lanes.
  bool Coordinates(int64_t address, std::vector<int64_t>& c) const {
    c.resize(shape.size());
    if (address < 0 || address >= span) return false;
    for (size_t i = 0; i < shape.size(); ++i) {
      c[i] = address / strides[i];
      address %= strides[i];
      if (c[i] >= shape[i]) return false;
    }
    return address == 0;
  }
  int64_t Address(const std::vector<int64_t>& c) const {
    if (c.size() != shape.size())
      throw std::invalid_argument("state coordinate rank");
    int64_t result = 0;
    for (size_t i = 0; i < c.size(); ++i) {
      if (c[i] < 0 || c[i] >= shape[i])
        throw std::out_of_range("state coordinate");
      result = Add(result, Multiply(c[i], strides[i]));
    }
    return result;
  }
  int64_t Bytes(int bits) const {
    if (bits != 2 && bits != 4)
      throw std::invalid_argument("packed state width");
    const int per = 8 / bits;
    return span / per + (span % per != 0);
  }
};
}  // namespace ynn_common
