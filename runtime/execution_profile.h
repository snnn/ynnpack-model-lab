// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <atomic>
#include <chrono>
#include <cstdint>
#include <map>
#include <memory>
#include <mutex>
#include <ostream>
#include <set>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

#include "slinky/builder/node_mutator.h"
#include "slinky/runtime/evaluate.h"
#include "ynnpack/base/type.h"
#include "ynnpack/subgraph/runtime.h"

namespace lab_ynn {
// Presentation metadata only: never marks outputs external or alters
// scheduling.
struct ProfileOperation {
  std::string scope, kind;
  std::vector<uint32_t> inputs, outputs;
  std::vector<std::string> input_names;
};

inline std::string ProfileJson(const std::string& text) {
  std::string result = "\"";
  const char* hex = "0123456789abcdef";
  for (unsigned char c : text) {
    if (c == '"' || c == '\\') {
      result += '\\';
      result += c;
    } else if (c < 32) {
      result += "\\u00";
      result += hex[c >> 4];
      result += hex[c & 15];
    } else {
      result += c;
    }
  }
  return result + '"';
}

// Wraps the already scheduled callbacks, with no intermediate output bindings.
// Callback times are worker work, not operator wall time including thread
// joins.
class ExecutionProfile {
 public:
  struct Event {
    uint64_t start, end;
    size_t call;
  };
  struct Call {
    std::string name;
    std::vector<size_t> origins;
    std::vector<std::string> inputs, outputs;
    bool envelope = false;
    std::vector<std::string> backend_input_types;
  };
  struct Slot {
    std::vector<Event> events;
    size_t dropped = 0;
  };
  using Origins = std::set<size_t>;
  using SymbolOrigins = std::map<slinky::var, Origins>;

  explicit ExecutionProfile(std::vector<ProfileOperation> operations,
                            size_t event_limit = 65536)
      : operations_(std::move(operations)),
        event_limit_(event_limit),
        generation_(NextGeneration()) {
    if (!event_limit_) throw std::invalid_argument("zero profile event limit");
    calls_.push_back({"graph_run", {}, {}, {}, true});
  }
  static uint64_t Now() {
    return std::chrono::duration_cast<std::chrono::nanoseconds>(
               std::chrono::steady_clock::now().time_since_epoch())
        .count();
  }
  bool active() const { return active_.load(std::memory_order_relaxed); }

  class Span {
   public:
    Span(ExecutionProfile* profile, size_t call)
        : profile_(profile && profile->active() ? profile : nullptr),
          call_(call),
          start_(profile_ ? Now() : 0) {}
    ~Span() {
      if (profile_) profile_->Record(call_, start_, Now());
    }

   private:
    ExecutionProfile* profile_;
    size_t call_;
    uint64_t start_;
  };

  void AttachCreators(ynn_subgraph& graph) {
    std::map<uint32_t, Origins> labels;
    for (size_t i = 0; i < operations_.size(); ++i)
      for (auto id : operations_[i].outputs) labels[id].insert(i);
    // Optimization has completed. Capture value identity now, before Slinky's
    // lexical symbol recycling; do not change node optimization or call attrs.
    for (auto& node : graph.nodes) {
      if (!node.is_valid()) continue;
      Origins origins;
      std::vector<uint32_t> pending(node.outputs.begin(), node.outputs.end());
      std::set<uint32_t> visited;
      while (!pending.empty()) {
        const auto id = pending.back();
        pending.pop_back();
        if (!visited.insert(id).second) continue;
        for (auto origin : labels[id]) {
          origins.insert(origin);
          // Follow eliminated intermediates to retain fused operation origins.
          // Live inputs belong to other scheduled work and are not charged
          // here.
          for (auto input : operations_[origin].inputs)
            if (input < graph.values.size() && !graph.value(input).is_valid())
              pending.push_back(input);
        }
      }
      auto create = node.create;
      node.create = [this, create, origins](const ynn_node& n,
                                            ynn_runtime& runtime) {
        const size_t begin = runtime.funcs.size();
        const auto result = create(n, runtime);
        if (result != ynn_status_success) return result;
        for (size_t j = begin; j < runtime.funcs.size(); ++j) {
          auto& func = runtime.funcs[j];
          if (!func.impl())
            continue;  // copy statements are handled separately.
          Call call;
          call.name = func.attrs().name;
          for (auto input : n.inputs)
            if (input != YNN_INVALID_VALUE_ID)
              call.backend_input_types.push_back(
                  ynn::to_string(runtime.value(input).type));
          call.origins.assign(origins.begin(), origins.end());
          for (const auto& input : func.inputs())
            call.inputs.push_back(
                runtime.globals.symbols.name(input.buffer->sym()));
          for (const auto& output : func.outputs())
            call.outputs.push_back(
                runtime.globals.symbols.name(output.buffer->sym()));
          const size_t id = calls_.size();
          calls_.push_back(std::move(call));
          // Preserve the reserved memcpy name: Slinky recognizes its semantics.
          if (func.attrs().name == "memcpy") continue;
          auto& attrs =
              const_cast<slinky::call_stmt::attributes&>(func.attrs());
          attrs.name += "|lab_profile=" + std::to_string(id);
        }
        return result;
      };
    }
  }

  class Mutator : public slinky::stmt_mutator {
   public:
    explicit Mutator(ExecutionProfile& profile) : profile_(profile) {}
    void visit(const slinky::call_stmt* op) override {
      auto attrs = *op->attrs;
      auto target = op->target;
      const auto marker = attrs.name.rfind("|lab_profile=");
      size_t id;
      if (marker != std::string::npos) {
        id = std::stoull(attrs.name.substr(marker + 13));
        attrs.name.erase(marker);
        if (id >= profile_.calls_.size())
          throw std::logic_error("invalid profile tag");
      } else {
        id = profile_.calls_.size();
        profile_.calls_.push_back({attrs.name, {}, {}, {}, false});
      }
      set_result(slinky::call_stmt::make(
          [profile = &profile_, id, target](const slinky::call_stmt* call,
                                            slinky::eval_context& ctx) {
            Span span(profile, id);
            return target(call, ctx);
          },
          op->inputs, op->outputs,
          std::vector<slinky::expr>(op->scalars.begin(), op->scalars.end()),
          std::move(attrs)));
    }
    void visit(const slinky::copy_stmt* op) override {
      const size_t id = profile_.calls_.size();
      profile_.calls_.push_back({"copy", {}, {}, {}, false});
      auto impl = op->impl;
      set_result(slinky::copy_stmt::make(
          [profile = &profile_, id, impl](const slinky::raw_buffer& src,
                                          const slinky::raw_buffer& dst,
                                          const slinky::raw_buffer& pad) {
            Span span(profile, id);
            impl(src, dst, pad);
          },
          op->src,
          std::vector<slinky::expr>(op->src_x.begin(), op->src_x.end()),
          op->dst, std::vector<slinky::var>(op->dst_x.begin(), op->dst_x.end()),
          op->pad));
    }

   private:
    ExecutionProfile& profile_;
  };
  slinky::stmt Instrument(const slinky::stmt& pipeline) {
    return Mutator(*this).mutate(pipeline);
  }

  void WriteMetadata(std::ostream& out) const {
    out << "{\"type\":\"metadata\",\"version\":1,\"clock\":\"steady_clock_ns\","
           "\"scope\":\"scheduled_callback_worker_work\",\"operations\":[";
    for (size_t i = 0; i < operations_.size(); ++i) {
      if (i) out << ',';
      const auto& op = operations_[i];
      out << "{\"id\":" << i << ",\"scope\":" << ProfileJson(op.scope)
          << ",\"kind\":" << ProfileJson(op.kind) << ",\"input_names\":[";
      for (size_t j = 0; j < op.input_names.size(); ++j) {
        if (j) out << ',';
        out << ProfileJson(op.input_names[j]);
      }
      out << "]}";
    }
    out << "],\"calls\":[";
    for (size_t i = 0; i < calls_.size(); ++i) {
      if (i) out << ',';
      const auto& call = calls_[i];
      out << "{\"id\":" << i << ",\"name\":" << ProfileJson(call.name)
          << ",\"envelope\":" << (call.envelope ? "true" : "false")
          << ",\"origins\":[";
      for (size_t j = 0; j < call.origins.size(); ++j) {
        if (j) out << ',';
        out << call.origins[j];
      }
      out << ']';
      for (const auto& list :
           {std::make_pair("inputs", &call.inputs),
            std::make_pair("outputs", &call.outputs),
            std::make_pair("backend_input_types", &call.backend_input_types)}) {
        out << ",\"" << list.first << "\":[";
        for (size_t j = 0; j < list.second->size(); ++j) {
          if (j) out << ',';
          out << ProfileJson(list.second->at(j));
        }
        out << ']';
      }
      out << '}';
    }
    out << "]}\n";
    if (!out) throw std::runtime_error("profile metadata write failed");
  }
  void BeginStep(const std::string& name, int repetition, size_t step,
                 int position) {
    if (active()) throw std::logic_error("profile step already active");
    for (auto& slot : slots_) {
      slot->events.clear();
      slot->dropped = 0;
    }
    case_ = name;
    repetition_ = repetition;
    step_ = step;
    position_ = position;
    start_ = Now();
    active_.store(true, std::memory_order_release);
  }
  void EndStep(std::ostream& out, bool success = true) {
    if (!active_.exchange(false))
      throw std::logic_error("profile step not active");
    const auto end = Now();
    size_t dropped = 0;
    for (auto& slot : slots_) dropped += slot->dropped;
    out << "{\"type\":\"step\",\"case\":" << ProfileJson(case_)
        << ",\"repetition\":" << repetition_ << ",\"step\":" << step_
        << ",\"phase\":\"decode\",\"position\":" << position_
        << ",\"history\":" << position_ + 1
        << ",\"rows\":1,\"start_ns\":" << start_ << ",\"end_ns\":" << end
        << ",\"complete\":" << (success && !dropped ? "true" : "false")
        << ",\"dropped_events\":" << dropped << ",\"events\":[";
    bool first = true;
    for (size_t worker = 0; worker < slots_.size(); ++worker)
      for (const auto& event : slots_[worker]->events) {
        if (!first) out << ',';
        first = false;
        out << '[' << worker << ',' << event.call << ',' << event.start << ','
            << event.end << ']';
      }
    out << "]}\n";
    if (!out) throw std::runtime_error("profile event write failed");
    if (dropped) throw std::runtime_error("profile event buffer exhausted");
  }
  const std::vector<Call>& calls() const { return calls_; }

 private:
  static uint64_t NextGeneration() {
    static std::atomic<uint64_t> next{0};
    return ++next;
  }
  void Record(size_t call, uint64_t start, uint64_t end) {
    struct Cached {
      uint64_t generation = 0;
      Slot* slot = nullptr;
    };
    static thread_local Cached cached;
    if (cached.generation != generation_) {
      auto slot = std::make_unique<Slot>();
      slot->events.reserve(event_limit_);
      cached.slot = slot.get();
      cached.generation = generation_;
      std::lock_guard<std::mutex> lock(mutex_);
      slots_.push_back(std::move(slot));
    }
    auto& slot = *cached.slot;
    if (slot.events.size() == event_limit_)
      ++slot.dropped;
    else
      slot.events.push_back({start, end, call});
  }
  std::vector<ProfileOperation> operations_;
  std::vector<Call> calls_;
  std::vector<std::unique_ptr<Slot>> slots_;
  std::mutex mutex_;
  std::atomic<bool> active_{false};
  const size_t event_limit_;
  const uint64_t generation_;
  std::string case_;
  int repetition_ = 0, position_ = 0;
  size_t step_ = 0;
  uint64_t start_ = 0;
};
}  // namespace lab_ynn
