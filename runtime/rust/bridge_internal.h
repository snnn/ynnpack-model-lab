// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <cstdio>
#include <memory>
#include <stdexcept>

#include "models/gemma4/hf_assets.h"
#include "runtime/model_assets.h"
#include "runtime/rust/bridge.h"
#include "runtime/value_trace.h"
#include "runtime/ynnpack_support.h"

#ifdef LAB_RUNTIME_TEST_HOOKS
inline size_t lab_test_graphs = 0, lab_test_assets = 0;
inline int lab_test_compile_countdown = -1;
struct LabTestLifetime {
  size_t& count;
  explicit LabTestLifetime(size_t& count) : count(count) { ++count; }
  ~LabTestLifetime() { --count; }
};
#endif

// One native adapter implements the construction vocabulary for every model.
struct LabAssets {
#ifdef LAB_RUNTIME_TEST_HOOKS
  LabTestLifetime lifetime{lab_test_assets};
#endif
  lab::Weights weights;
  std::unique_ptr<lab::ModelAssets> model;
  std::unique_ptr<lab::TensorProvider> hf_weights;
  std::unique_ptr<lab::HfModelAssets> hf_model;
  bool bf16_activations = false;
  LabAssets(const char* bundle, const char* parameters)
      : weights(bundle, parameters) {}
  const void* Get(const char* name, size_t bytes) {
    return hf_weights ? hf_weights->Get(name, bytes) : weights.Get(name, bytes);
  }
};
struct LabPlanExpression {
  uint32_t op;
  slinky::expr value;
  std::vector<std::shared_ptr<LabPlanExpression>> operands;
  lab_ynn::CheckedIndex Evaluate(slinky::eval_context& ctx) const;
};
struct LabPlanContext {
  std::vector<std::shared_ptr<LabPlanExpression>> expressions;
  std::unordered_map<uint32_t, slinky::expr> symbols;
};
struct LabGraph {
#ifdef LAB_RUNTIME_TEST_HOOKS
  LabTestLifetime lifetime{lab_test_graphs};
#endif
  std::unique_ptr<lab::ValueTrace> trace;
  std::unique_ptr<lab_ynn::Graph> graph;
  slinky::stmt prepared_pipeline;
  std::shared_ptr<lab_ynn::ExecutionProfile> profile;
  std::shared_ptr<const lab_ynn::ScratchStatistics> scratch;
  std::ofstream profile_output;
  std::unique_ptr<LabPlanContext> construction;
};
struct LabResource {
  std::shared_ptr<lab_ynn::ResourceState> state;
};

template <typename F>
int32_t LabCatch(LabError* error, F&& f) noexcept {
  if (!error) return 3;
  *error = {};
  try {
    f();
    return 0;
  } catch (const std::logic_error& e) {
    error->kind = 1;
    std::snprintf(error->message, sizeof(error->message), "%s", e.what());
  } catch (const std::exception& e) {
    error->kind = 2;
    std::snprintf(error->message, sizeof(error->message), "%s", e.what());
  } catch (...) {
    error->kind = 3;
    std::snprintf(error->message, sizeof(error->message),
                  "Unknown C++ exception");
  }
  return error->kind;
}

inline void LabRequire(bool condition, const char* message) {
  if (!condition) throw std::invalid_argument(message);
}
