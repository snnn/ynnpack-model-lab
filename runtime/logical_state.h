// Copyright 2026 @snnn. Licensed under the Apache License, Version 2.0.
#pragma once

#include <atomic>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <stdexcept>

namespace lab_ynn_runtime {
// Logical publication rules shared by CPU and GPU adapters. No buffer, device,
// scheduler or allocation policy lives here. Adapters hold all participating
// leases until completion/error handling and all publications have finished.
class LogicalState {
 public:
  explicit LogicalState(size_t capacity, size_t initialized = 0)
      : capacity_(capacity), committed_(initialized) {
    if (initialized > capacity)
      throw std::invalid_argument("invalid resource initialized extent");
  }
  LogicalState(const LogicalState&) = delete;
  LogicalState& operator=(const LogicalState&) = delete;
  size_t committed_extent() const { return committed_.load(); }
  uint64_t reset_epoch() const { return epoch_.load(); }
  bool poisoned() const { return poisoned_.load(); }

 protected:
  bool TryAcquire() {
    bool free = false;
    return busy_.compare_exchange_strong(free, true);
  }
  void Release() { busy_.store(false); }
  void ValidateInvocation(uint64_t epoch, size_t entry,
                          size_t successor) const {
    if (poisoned_ || epoch != epoch_)
      throw std::logic_error(
          "poisoned resource or stale reset epoch; reset/rebind required");
    if (entry != committed_ || successor < entry || successor > capacity_)
      throw std::invalid_argument(
          "resource extent differs from committed state or exceeds capacity");
  }
  // Called under a lease, after every participating successor was validated.
  // These stores cannot fail. All leases remain held until every store
  // finishes.
  void Publish(size_t successor) noexcept { committed_.store(successor); }
  void Poison() noexcept { poisoned_.store(true); }

 public:
  void Reset() { ImportPrefix(0); }
  void ImportPrefix(size_t initialized) {
    if (!TryAcquire())
      throw std::logic_error("cannot reset an executing resource");
    struct ReleaseLease {
      LogicalState& state;
      ~ReleaseLease() { state.Release(); }
    } release{*this};
    ImportUnderLease(initialized);
  }

 protected:
  void ImportUnderLease(size_t initialized) {
    if (initialized > capacity_ ||
        epoch_ == std::numeric_limits<uint64_t>::max())
      throw std::invalid_argument(
          "invalid resource prefix or exhausted reset epoch");
    committed_ = initialized;
    poisoned_ = false;
    ++epoch_;
  }
  const size_t capacity_;
  std::atomic<size_t> committed_{0};
  std::atomic<uint64_t> epoch_{0};
  std::atomic<bool> poisoned_{false}, busy_{false};
};
}  // namespace lab_ynn_runtime
