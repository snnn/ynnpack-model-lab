// Copyright 2026 @snnn. Licensed under the Apache License, Version 2.0.
#pragma once

#include <atomic>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "logical_state.h"
#include "state_geometry.h"

namespace lab_ynn {
inline constexpr uint32_t kResourceStateContract = 1;
// Storage remains externally owned and must outlive all bound prepared graphs.
// Initialization/import is a caller assertion about the encoded prefix; it does
// not fill, copy, quantize, or clear capacity bytes.
class ResourceState : public lab_ynn_runtime::LogicalState {
 public:
  ResourceState(void* data, size_t bytes, std::vector<size_t> shape,
                size_t element_bytes, size_t axis, std::string encoding,
                size_t initialized = 0, size_t packed_bits = 0,
                std::vector<int64_t> strides = {})
      : LogicalState(axis < shape.size() ? shape[axis] : 0, initialized),
        data_(data),
        bytes_(bytes),
        shape_(std::move(shape)),
        element_bytes_(element_bytes),
        packed_bits_(packed_bits),
        axis_(axis),
        encoding_(std::move(encoding)),
        geometry_(std::vector<int64_t>(shape_.begin(), shape_.end()), axis,
                  std::move(strides)) {
    if (!data_ || (!element_bytes_ && !packed_bits_) || axis_ >= shape_.size() ||
        (packed_bits_ && (element_bytes_ || (packed_bits_ != 2 && packed_bits_ != 4))))
      throw std::invalid_argument("invalid resource storage");
    size_t elements = 1;
    for (size_t dimension : shape_) {
      if (dimension > size_t(std::numeric_limits<int64_t>::max()) ||
          (dimension &&
           elements > std::numeric_limits<size_t>::max() / dimension))
        throw std::invalid_argument("resource geometry overflow");
      elements *= dimension;
    }
    const size_t per_byte = packed_bits_ ? 8 / packed_bits_ : 1;
    const size_t span = geometry_.span;
    const size_t storage_elements = span / per_byte + (span % per_byte != 0);
    const size_t width = packed_bits_ ? 1 : element_bytes_;
    if (storage_elements > std::numeric_limits<size_t>::max() / width ||
        storage_elements * width > bytes_ || initialized > shape_[axis_])
      throw std::invalid_argument("resource size or initialized extent");
    const auto address = reinterpret_cast<uintptr_t>(data_);
    if (bytes_ > std::numeric_limits<uintptr_t>::max() - address)
      throw std::invalid_argument("resource address overflow");
  }
  ResourceState(const ResourceState&) = delete;
  ResourceState& operator=(const ResourceState&) = delete;

 private:
  friend class Graph;
  friend struct CapacityVariant;
  void* const data_;
  const size_t bytes_;
  const std::vector<size_t> shape_;
  const size_t element_bytes_, packed_bits_, axis_;
  const std::string encoding_;
  const lab_ynn_runtime::StateGeometry geometry_;
};
}  // namespace lab_ynn
