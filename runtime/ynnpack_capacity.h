// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
#pragma once
#include "capacity_session.h"
#include "ynnpack_support.h"

namespace lab_ynn {
struct CapacityVariant {
  size_t capacity = 0;
  // Allocation owners outlive graphs and ResourceStates.
  std::vector<std::shared_ptr<void>> storage_owners;
  std::map<std::string, std::shared_ptr<void>> fixed_states;
  std::map<std::string, std::shared_ptr<ResourceState>> resources;
  std::map<std::string, std::unique_ptr<Graph>> phases;
  lab_ynn_runtime::StateMigrationLease::States LogicalStates() const {
    lab_ynn_runtime::StateMigrationLease::States states;
    for (const auto& [name, state] : resources) states[name] = state.get();
    for (const auto& [name, graph] : phases) {
      if (!graph || !graph->runtime_ || graph->failed_)
        throw std::invalid_argument("unprepared capacity phase");
      for (const auto& [id, r] : graph->resources_)
        if (!resources.count(r.identity) || r.state != resources.at(r.identity))
          throw std::invalid_argument(
              "capacity phase bound to a different owner");
    }
    return states;
  }
  void MigrateFrom(const CapacityVariant& previous) {
    if (fixed_states != previous.fixed_states)
      throw std::invalid_argument("capacity variant changed fixed state");
    // Validate every owner before copying any bytes. The coordinator holds
    // old/new logical-state leases, so external requests cannot write them.
    for (const auto& [name, dst] : resources) {
      const auto& src = previous.resources.at(name);
      if (src->axis_ != dst->axis_ || src->packed_bits_ != dst->packed_bits_ ||
          src->element_bytes_ != dst->element_bytes_ ||
          src->encoding_ != dst->encoding_ ||
          src->shape_.size() != dst->shape_.size() ||
          dst->shape_[dst->axis_] != capacity)
        throw std::invalid_argument("capacity encoding/geometry mismatch");
      for (size_t i = 0; i < src->shape_.size(); ++i)
        if (i != src->axis_ && src->shape_[i] != dst->shape_[i])
          throw std::invalid_argument("capacity changed a nonappend dimension");
      const auto d = reinterpret_cast<uintptr_t>(dst->data_);
      for (const auto* group : {&previous.resources, &std::as_const(resources)})
        for (const auto& [other_name, other] : *group) {
          if (other == dst) continue;
          const auto s = reinterpret_cast<uintptr_t>(other->data_);
          if (d < s + other->bytes_ && s < d + dst->bytes_)
            throw std::invalid_argument("capacity owners overlap");
        }
    }
    for (const auto& [name, dst] : resources) {
      const auto& src = previous.resources.at(name);
      auto live = src->shape_;
      live[src->axis_] = src->committed_extent();
      size_t count = 1;
      for (auto d : live) count *= d;
      std::vector<int64_t> c(live.size(), 0);
      for (size_t i = 0; i < count; ++i) {
        const auto s = src->geometry_.Address(c), d = dst->geometry_.Address(c);
        if (src->packed_bits_) {
          const int bits = src->packed_bits_, per = 8 / bits;
          auto* output = static_cast<uint8_t*>(dst->data_) + d / per;
          const unsigned code =
              (static_cast<const uint8_t*>(src->data_)[s / per] >>
               ((s % per) * bits)) &
              ((1u << bits) - 1);
          const unsigned mask = ((1u << bits) - 1) << ((d % per) * bits);
          *output = uint8_t((*output & ~mask) | (code << ((d % per) * bits)));
        } else {
          std::memcpy(
              static_cast<uint8_t*>(dst->data_) + d * dst->element_bytes_,
              static_cast<const uint8_t*>(src->data_) + s * src->element_bytes_,
              src->element_bytes_);
        }
        for (size_t j = c.size(); j-- > 0;) {
          if (++c[j] < int64_t(live[j])) break;
          c[j] = 0;
        }
      }
    }
  }
};
using CapacitySession = lab_ynn_runtime::CapacitySession<CapacityVariant>;
}  // namespace lab_ynn
