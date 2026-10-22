// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
#pragma once
#include <functional>
#include <map>
#include <memory>
#include <mutex>
#include <set>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include "logical_state.h"

namespace ynn_common {
// Both generations stay leased until migration and the all-owner publication
// finish. Failed preparation/copy never publishes a partial replacement set.
class StateMigrationLease {
 public:
  using States = std::map<std::string, LogicalState*>;
  StateMigrationLease(const States& before, const States& after) {
    try {
      if (before.size() != after.size())
        throw std::invalid_argument("capacity resource set changed");
      if (before.size() > leased_.max_size() / 2)
        throw std::length_error("capacity owner set too large");
      // Allocate bookkeeping before taking any lease. A failed allocation must
      // not strand an owner between TryAcquire and recording it for release.
      leased_.reserve(before.size() * 2);
      pairs_.reserve(before.size());
      std::set<LogicalState*> unique;
      for (const auto& [name, old] : before) {
        auto next = after.find(name);
        if (!old || next == after.end() || !next->second || old == next->second)
          throw std::invalid_argument("capacity resource identity mismatch");
        for (auto* state : {old, next->second}) {
          if (!unique.insert(state).second || !state->TryAcquire())
            throw std::logic_error("capacity owner is shared or executing");
          leased_.push_back(state);
          if (state->retired_ || state->poisoned_)
            throw std::logic_error("cannot migrate retired/poisoned state");
        }
        if (next->second->capacity_ <= old->capacity_ ||
            next->second->committed_ != 0)
          throw std::invalid_argument(
              "replacement must be larger and uninitialized");
        pairs_.emplace_back(old, next->second);
      }
    } catch (...) {
      Release();
      throw;
    }
  }
  ~StateMigrationLease() { Release(); }
  StateMigrationLease(const StateMigrationLease&) = delete;
  void Commit() noexcept {
    for (auto [old, next] : pairs_) next->Publish(old->committed_);
    for (auto [old, next] : pairs_) old->retired_ = true;
  }

 private:
  void Release() noexcept {
    for (auto* state : leased_) state->Release();
    leased_.clear();
  }
  std::vector<LogicalState*> leased_;
  std::vector<std::pair<LogicalState*, LogicalState*>> pairs_;
};

// Variant owns every prepared phase and its storage lifetimes. Preparation is
// an explicit supplied factory: it may select a larger data package, but this
// runtime never imports a compiler or silently changes a graph's descriptors.
// Callbacks run under the session lock and must not call back into the session.
template <class Variant>
class CapacitySession {
 public:
  using Prepare =
      std::function<std::unique_ptr<Variant>(size_t, const Variant&)>;
  // Observation/cancellation after copy and its completion, before publication.
  // Throwing here discards the replacement without retiring the current set.
  CapacitySession(std::unique_ptr<Variant> initial, Prepare prepare,
                  std::function<void()> before_publication = {})
      : current_(std::move(initial)),
        prepare_(std::move(prepare)),
        before_publication_(std::move(before_publication)) {
    if (!current_ || !current_->capacity || !prepare_)
      throw std::invalid_argument("invalid capacity session");
    current_->LogicalStates();
  }
  size_t capacity() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return current_->capacity;
  }
  auto Resource(const std::string& name) const {
    std::lock_guard<std::mutex> lock(mutex_);
    return current_->resources.at(name);
  }
  template <class F>
  decltype(auto) Run(const std::string& phase, F&& invoke) {
    static_assert(
        !std::is_reference_v<std::invoke_result_t<
            F, decltype(*current_->phases.begin()->second)>>,
        "capacity invocation results must not borrow a retired phase");
    std::unique_lock<std::mutex> lock(mutex_, std::try_to_lock);
    if (!lock.owns_lock())
      throw std::logic_error("capacity session is executing");
    return std::forward<F>(invoke)(*current_->phases.at(phase));
  }
  void ReserveCapacity(size_t capacity) {
    std::unique_lock<std::mutex> lock(mutex_, std::try_to_lock);
    if (!lock.owns_lock())
      throw std::logic_error("capacity session is executing");
    if (capacity < current_->capacity)
      throw std::invalid_argument("capacity cannot shrink");
    if (capacity == current_->capacity) return;
    auto next = prepare_(capacity, *current_);
    if (!next || next->capacity < capacity ||
        next->phases.size() != current_->phases.size())
      throw std::invalid_argument("incomplete capacity variant");
    for (const auto& [name, phase] : current_->phases)
      if (!phase || !next->phases.count(name) || !next->phases.at(name))
        throw std::invalid_argument("capacity phase set changed");
    StateMigrationLease lease(current_->LogicalStates(), next->LogicalStates());
    next->MigrateFrom(*current_);
    if (before_publication_) before_publication_();
    lease.Commit();
    current_.swap(next);
  }

 private:
  // Destroy retired runtimes before their externally owned allocations.
  std::unique_ptr<Variant> current_;
  Prepare prepare_;
  std::function<void()> before_publication_;
  mutable std::mutex mutex_;
};
}  // namespace ynn_common
