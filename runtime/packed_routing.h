// Copyright 2026 @snnn. Licensed under the Apache License, Version 2.0.
#pragma once
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>

#include "slinky/runtime/buffer.h"
#include "ynnpack/include/ynnpack.h"
namespace lab_ynn {
namespace packed {
using I = int64_t;
inline I Count(const std::vector<I>& shape) {
  I n = 1;
  for (auto d : shape) {
    if (d < 0) throw std::invalid_argument("negative logical extent");
    if (d == 0) return 0;
  }
  for (auto d : shape) {
    if (d && n > std::numeric_limits<I>::max() / d)
      throw std::overflow_error("packed element count");
    n *= d;
  }
  return n;
}
inline I Bytes(I n, int bits) {
  const I per = 8 / bits;
  return n / per + (n % per != 0);
}
inline std::vector<I> Coordinates(I flat, const std::vector<I>& shape) {
  std::vector<I> c(shape.size());
  for (size_t j = shape.size(); j-- > 0;) {
    c[j] = flat % std::max<I>(shape[j], 1);
    flat /= std::max<I>(shape[j], 1);
  }
  return c;
}
inline I Ordinal(const std::vector<I>& c, const std::vector<I>& shape) {
  if (c.size() != shape.size())
    throw std::invalid_argument("routing coordinate rank");
  I n = 0;
  for (size_t j = 0; j < c.size(); ++j) {
    if (c[j] < 0 || c[j] >= shape[j])
      throw std::out_of_range("routing coordinate out of bounds");
    n = n * shape[j] + c[j];
  }
  return n;
}
inline std::vector<I> Broadcast(const std::vector<I>& c,
                                const std::vector<I>& shape) {
  if (c.size() < shape.size())
    throw std::invalid_argument("routing broadcast rank");
  auto result = c;
  result.erase(result.begin(), result.begin() + (c.size() - shape.size()));
  for (size_t i = 0; i < shape.size(); ++i)
    if (shape[i] == 1) result[i] = 0;
  return result;
}
struct Tensor {
  const slinky::raw_buffer* buffer;
  std::vector<I> shape;
  int bits = 0;
  int type = 0;  // ynn_type, used by the adapter for numerical loads
  const void* At(const std::vector<I>& c) const {
    const I n = Ordinal(c, shape);
    if (bits) return buffer->address_at(n / (8 / bits));
    std::vector<slinky::index_t> reversed(c.rbegin(), c.rend());
    return buffer->address_at(slinky::span<slinky::index_t>(reversed));
  }
  I Code(const std::vector<I>& c) const {
    if (bits) {
      const I n = Ordinal(c, shape);
      const auto byte = *static_cast<const uint8_t*>(At(c));
      const unsigned q =
          (byte >> ((n % (8 / bits)) * bits)) & ((1u << bits) - 1);
      return (q & (1u << (bits - 1))) ? I(q) - (I(1) << bits) : I(q);
    }
    I result = 0;
    if (buffer->elem_size == 1) {
      int8_t v;
      std::memcpy(&v, At(c), 1);
      result = type == ynn_type_uint8 ? uint8_t(v) : v;
    } else if (buffer->elem_size == 4) {
      int32_t v;
      std::memcpy(&v, At(c), 4);
      result = v;
    } else if (buffer->elem_size == 8) {
      std::memcpy(&result, At(c), 8);
    } else
      throw std::invalid_argument("unsupported integer code width");
    return result;
  }
};
struct Selection {
  size_t input;
  std::vector<I> coordinate;
};
inline Selection Select(const std::string& kind, const std::vector<Tensor>& in,
                        const std::vector<I>& out_shape,
                        const std::vector<I>& c, const std::vector<I>& args,
                        const std::vector<I>& starts, int axis, int mode) {
  const auto& a = in[0];
  auto at = [&](size_t i, std::vector<I> coord) {
    return Selection{i, std::move(coord)};
  };
  if (kind == "select") {
    bool cond = in[0].Code(Broadcast(c, in[0].shape)) != 0;
    size_t i = cond ? 1 : 2;
    return at(i, Broadcast(c, in[i].shape));
  }
  if (kind == "transpose") {
    std::vector<I> x(c.size());
    for (size_t j = 0; j < c.size(); ++j) x.at(args.at(j)) = c[j];
    return at(0, x);
  }
  if (kind == "slice" || kind == "slice_like") {
    auto x = c;
    for (size_t j = 0; j < c.size(); ++j)
      x[j] += starts.empty() ? 0 : starts.at(j);
    return at(0, x);
  }
  if (kind == "reverse") {
    auto x = c;
    for (auto j : args) {
      if (j < 0) j += x.size();
      x.at(j) = a.shape.at(j) - 1 - x.at(j);
    }
    return at(0, x);
  }
  if (kind == "tile") {
    auto x = c;
    for (size_t j = 0; j < c.size(); ++j) x[j] %= std::max<I>(a.shape[j], 1);
    return at(0, x);
  }
  if (kind == "broadcast_to" || kind == "broadcast_like")
    return at(0, Broadcast(c, a.shape));
  if (kind == "gather") {
    if (axis < 0) axis += a.shape.size();
    const auto r = in[1].shape.size();
    std::vector<I> idx(c.begin() + axis, c.begin() + axis + r);
    const auto selected = in[1].Code(idx);
    if (selected < 0 || selected >= a.shape.at(axis))
      throw std::out_of_range("gather index out of bounds");
    auto x = c;
    x.erase(x.begin() + axis, x.begin() + axis + r);
    x.insert(x.begin() + axis, selected);
    return at(0, x);
  }
  if (kind == "even_split" || kind == "unstack") {
    if (axis < 0) axis += a.shape.size();
    auto x = c;
    if (kind == "unstack")
      x.insert(x.begin() + axis, args.at(0));
    else
      x.at(axis) += args.at(0) * out_shape.at(axis);
    return at(0, x);
  }
  if (kind == "concat" || kind == "stack") {
    if (axis < 0) axis += out_shape.size();
    auto x = c;
    if (kind == "stack") {
      size_t j = x.at(axis);
      x.erase(x.begin() + axis);
      return at(j, x);
    }
    for (size_t j = 0; j < in.size(); ++j) {
      if (x.at(axis) < in[j].shape.at(axis)) return at(j, x);
      x[axis] -= in[j].shape[axis];
    }
    throw std::out_of_range("concat coordinate");
  }
  if (kind == "pad") {
    auto x = c;
    for (size_t j = 0; j < x.size(); ++j) {
      x[j] -= starts[j];
      if (x[j] >= 0 && x[j] < a.shape[j]) continue;
      if (!mode) return at(1, {});
      x[j] = x[j] < 0 ? -x[j] - (mode == 2)
                      : 2 * a.shape[j] - x[j] - (mode == 2 ? 1 : 2);
    }
    return at(0, x);
  }
  // copy, code extraction, annotation and order-preserving reshape family.
  return at(0, Coordinates(Ordinal(c, out_shape), a.shape));
}
}  // namespace packed
}  // namespace lab_ynn
