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

namespace lab_ynn {
inline constexpr uint32_t kResourceStateContract = 1;
// Storage remains externally owned and must outlive all bound prepared graphs.
// Initialization/import is a caller assertion about the encoded prefix; it does
// not fill, copy, quantize, or clear capacity bytes.
class ResourceState : public lab_ynn_runtime::LogicalState {
 public:
  ResourceState(void* data, size_t bytes, std::vector<size_t> shape,
                size_t element_bytes, size_t axis, std::string encoding,
                size_t initialized = 0)
      : LogicalState(axis < shape.size() ? shape[axis] : 0, initialized),
        data_(data),
        bytes_(bytes),
        shape_(std::move(shape)),
        element_bytes_(element_bytes),
        axis_(axis),
        encoding_(std::move(encoding)) {
    if (!data_ || !element_bytes_ || axis_ >= shape_.size())
      throw std::invalid_argument("invalid resource storage");
    size_t elements = 1;
    for (size_t dimension : shape_) {
      if (dimension > size_t(std::numeric_limits<int64_t>::max()) ||
          (dimension &&
           elements > std::numeric_limits<size_t>::max() / dimension))
        throw std::invalid_argument("resource geometry overflow");
      elements *= dimension;
    }
    if (elements > std::numeric_limits<size_t>::max() / element_bytes_ ||
        elements * element_bytes_ > bytes_ || initialized > shape_[axis_])
      throw std::invalid_argument("resource size or initialized extent");
    const auto address = reinterpret_cast<uintptr_t>(data_);
    if (bytes_ > std::numeric_limits<uintptr_t>::max() - address)
      throw std::invalid_argument("resource address overflow");
  }
  ResourceState(const ResourceState&) = delete;
  ResourceState& operator=(const ResourceState&) = delete;

 private:
  friend class Graph;
  void* const data_;
  const size_t bytes_;
  const std::vector<size_t> shape_;
  const size_t element_bytes_, axis_;
  const std::string encoding_;
};
}  // namespace lab_ynn
