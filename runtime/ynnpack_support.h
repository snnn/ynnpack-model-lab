// Copyright 2026 Google LLC.
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// https://www.apache.org/licenses/LICENSE-2.0
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

// Controlled ablation for builders emitted before scheduling was explicit.
// Current Core source always passes the policy as an operation argument.
#ifndef LAB_YNN_DEFAULT_SCHEDULED_MASK
#define LAB_YNN_DEFAULT_SCHEDULED_MASK false
#endif

// Experimental adapter for the pinned/patched YNNPACK internal API.
#include <algorithm>
#include <atomic>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <functional>
#include <limits>
#include <map>
#include <memory>
#include <optional>
#include <set>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "execution_profile.h"
#include "packed_routing.h"
#include "checked_index.h"
#include "resource_state.h"
#include "slinky/base/arithmetic.h"
#include "slinky/base/thread_pool_impl.h"
#include "slinky/builder/pipeline.h"
#include "slinky/builder/simplify.h"
#include "slinky/runtime/evaluate.h"
#include "slinky/runtime/print.h"
#include "ynnpack/composites/composites.h"
#include "ynnpack/base/type.h"
#include "ynnpack/include/ynnpack.h"
#include "ynnpack/subgraph/runtime.h"
#include "ynnpack/subgraph/slinky.h"

namespace lab_ynn {
inline constexpr uint32_t kCompletionContract = 1;
// Slinky's ceil_div uses (a+b-1)/b, whose intermediate can overflow even when
// the quotient fits. Core's emitter guarantees a positive constant divisor.
inline slinky::expr CeilDiv(const slinky::expr& a, const slinky::expr& b) {
  return a / b + slinky::select(a % b != 0, 1, 0);
}
inline void Check(ynn_status s) {
  if (s != ynn_status_success)
    throw std::runtime_error("YNNPACK status " + std::to_string(s));
}

struct Counters {
  size_t append_calls = 0;
  size_t append_bytes = 0;
  size_t view_copy_bytes = 0;
  size_t fail_before_append = std::numeric_limits<size_t>::max();
  std::function<void(size_t)> before_append;
};

struct ScratchStatistics {
  std::atomic<size_t> live{0}, peak{0}, allocated{0}, allocations{0};
};

class Graph {
 public:
  explicit Graph(size_t count) : bound_(count) {
    ynn_subgraph_t raw = nullptr;
    // Preserve authored quantize/dequantize boundaries. Default YNNPACK
    // rewrites can otherwise remove the QAT output rounding/clipping entirely.
    Check(ynn_create_subgraph(count, YNN_FLAG_NO_EXCESS_PRECISION, &raw));
    graph_.reset(raw);
  }
  Graph(const Graph&) = delete;
  Graph& operator=(const Graph&) = delete;

  // Completion identities have no tensor storage. Real result buffers provide
  // scheduling anchors; a dependent callback keeps its original kernel arity.
  void BeginOperation(const std::vector<std::string>& waits) {
    if (operation_open_) throw std::logic_error("nested completion boundary");
    operation_open_ = true;
    operation_begin_ = graph_->nodes.size();
    operation_waits_.clear();
    operation_coverage_.clear();
    RefreshNodeDependencies(operation_begin_);
    for (const auto& token : waits) {
      const auto found = completion_anchors_.find(token);
      if (found == completion_anchors_.end())
        throw std::invalid_argument("undefined completion: " + token);
      operation_waits_.insert(found->second.begin(), found->second.end());
      const auto& coverage = completion_coverage_.at(token);
      operation_coverage_.insert(coverage.begin(), coverage.end());
    }
  }
  void EndOperation(const std::vector<std::string>& definitions,
                    const std::vector<uint32_t>& results) {
    if (!operation_open_ || graph_->nodes.size() == operation_begin_)
      throw std::invalid_argument("completion boundary has no backend operation");
    if (results.empty())
      throw std::invalid_argument("completion requires real result anchors");
    for (size_t i = operation_begin_; i < graph_->nodes.size(); ++i) {
      auto& node = graph_->nodes[i];
      node_prerequisites_[i] = operation_coverage_;
      if (operation_waits_.empty()) continue;
      const auto original_op = node.op;
      const auto original_create = node.create;
      const size_t node_input_count = node.inputs.size();
      node.inputs.insert(node.inputs.end(), operation_waits_.begin(), operation_waits_.end());
      node.op = ynn_node::opaque{"core_completion_controlled"};
      node.create = [original_op, original_create, node_input_count](
                        const ynn_node& n, ynn_runtime& r) {
        ynn_node original = n;
        original.op = original_op;
        original.inputs.resize(node_input_count);
        const size_t begin = r.funcs.size();
        const auto status = original_create(original, r);
        if (status != ynn_status_success) return status;
        if (begin == r.funcs.size())
          throw std::invalid_argument("completion capability: metadata-only wait");
        // Remapping during YNNPACK optimization also remaps the appended IDs.
        std::vector<uint32_t> remapped(n.inputs.begin() + node_input_count,
                                       n.inputs.end());
        for (size_t j = begin; j < r.funcs.size(); ++j) {
          auto& f = r.funcs[j];
          if (!f.impl())
            throw std::invalid_argument("completion capability: copy/view wait");
          std::optional<slinky::func> original_func(std::move(f));
          auto& source = *original_func;
          auto inputs = source.inputs();
          const size_t kernel_inputs = inputs.size();
          for (auto id : remapped) {
            const auto& value = r.value(id);
            if (!value.buffer)
              throw std::invalid_argument("completion anchor has no backend buffer");
            slinky::box_expr bounds;
            for (int d = 0; d < value.rank(); ++d)
              bounds.push_back(slinky::min_extent(0, value.extent(d)));
            inputs.push_back({value.buffer, std::move(bounds)});
          }
          auto attrs = source.attrs();
          const uint32_t old_in_place = uint32_t(attrs.allow_in_place);
          attrs.allow_in_place = 0;
          for (size_t o = 0; o < source.outputs().size(); ++o)
            for (size_t in = 0; in < kernel_inputs; ++in) {
              const size_t old_bit = o * kernel_inputs + in;
              const size_t bit = o * inputs.size() + in;
              if (old_bit < 31 && bit < 31 && (old_in_place & (uint32_t(1) << old_bit)))
                attrs.allow_in_place |= int(uint32_t(1) << bit);
            }
          attrs.name = "core_completion_" + attrs.name;
          attrs.min_rank = std::numeric_limits<int>::max();
          const auto impl = source.impl();
          auto callback = [impl, kernel_inputs](const slinky::call_stmt* call,
                                               slinky::eval_context& ctx) {
            slinky::call_stmt kernel_call(*call);
            kernel_call.inputs = {call->inputs.data(), kernel_inputs};
            return impl(&kernel_call, ctx);
          };
          const auto call = source.make_call();
          const auto* native_call = call.as<slinky::call_stmt>();
          std::vector<slinky::expr> scalars(native_call->scalars.begin(),
                                           native_call->scalars.end());
          auto outputs = source.outputs();
          auto loops = source.loops();
          auto* user_data = source.user_data();
          // Destroying the old func releases its producer links through the
          // builder's API; replacing private buffer metadata is unnecessary.
          original_func.reset();
          auto controlled = slinky::func(std::move(callback), std::move(inputs),
                                         std::move(outputs), std::move(scalars), attrs);
          controlled.loops(std::move(loops));
          controlled.compute_root();
          controlled.user_data() = user_data;
          f = std::move(controlled);
        }
        return ynn_status_success;
      };
    }
    std::set<uint32_t> anchors(results.begin(), results.end());
    anchors.insert(operation_waits_.begin(), operation_waits_.end());
    RefreshNodeDependencies(graph_->nodes.size());
    auto coverage = operation_coverage_;
    for (auto result : results) {
      const auto& predecessors = value_node_dependencies_[result];
      coverage.insert(predecessors.begin(), predecessors.end());
    }
    for (const auto& token : definitions) {
      if (token.empty() || !completion_anchors_.emplace(token, anchors).second)
        throw std::invalid_argument("duplicate or invalid completion: " + token);
      completion_coverage_.emplace(token, coverage);
    }
    operation_open_ = false;
  }

  void BeginProfileOperation(const char* scope, const char* kind,
                             std::vector<uint32_t> inputs,
                             std::vector<uint32_t> outputs,
                             std::vector<std::string> input_names = {}) {
    if (profile_open_) throw std::logic_error("nested profile label");
    profile_open_ = true;
    profile_node_begin_ = graph_->nodes.size();
    profile_operations_.push_back({scope, kind, std::move(inputs), std::move(outputs), std::move(input_names)});
  }
  void EndProfileOperation() {
    if (!profile_open_) throw std::logic_error("missing profile label");
    auto& outputs = profile_operations_.back().outputs;
    for (size_t i = profile_node_begin_; i < graph_->nodes.size(); ++i)
      for (auto id : graph_->nodes[i].outputs)
        if (id != YNN_INVALID_VALUE_ID) outputs.push_back(id);
    std::sort(outputs.begin(), outputs.end());
    outputs.erase(std::unique(outputs.begin(), outputs.end()), outputs.end());
    profile_open_ = false;
  }
  std::shared_ptr<ExecutionProfile> TrackExecution(size_t event_limit = 65536) {
    if (runtime_ || execution_profile_)
      throw std::logic_error("enable execution profiling before Compile");
    execution_profile_ = std::make_shared<ExecutionProfile>(profile_operations_, event_limit);
    return execution_profile_;
  }

  void Tensor(uint32_t id, const std::string& name, ynn_type type,
              std::vector<size_t> dims, uint32_t flags, const void* data) {
    Check(ynn_define_tensor(graph_.get(), type, dims.size(), dims.data(), data,
                            flags, &id));
    names_.emplace(name, id);
  }
  void ConstantOutput(uint32_t id, const std::string& name, ynn_type type,
                      std::vector<size_t> dims, const void* data) {
    Tensor(id, name, type, dims, YNN_VALUE_FLAG_EXTERNAL_OUTPUT, nullptr);
    uint32_t source = YNN_INVALID_VALUE_ID;
    Check(ynn_define_tensor(graph_.get(), type, dims.size(), dims.data(), data, 0, &source));
    Copy(source, id);
  }
  #include "ynnpack_packed.inc"
  slinky::expr Axis(uint32_t id, size_t axis) const {
    if (packed_.count(id)) return packed_.at(id).shape.at(axis);
    const auto& v = graph_->value(id);
    if (axis >= v.rank()) throw std::invalid_argument("axis out of range");
    return v.extent(v.rank() - 1 - axis);
  }
  slinky::expr Parameter(const std::string& name, int64_t lo, int64_t hi) {
    if (parameters_.count(name) || lo > hi)
      throw std::invalid_argument("invalid scalar declaration");
    slinky::var symbol(graph_->globals.symbols, name);
    parameters_.emplace(name, graph_->scalar_parameters.size());
    parameter_ranges_.emplace(name, std::make_pair(lo, hi));
    graph_->scalar_parameters.push_back(symbol);
    RequireBounds(slinky::expr(symbol) >= lo && slinky::expr(symbol) <= hi,
                  "scalar bounds");
    return symbol;
  }
  slinky::expr InstanceParameter(const std::string& name, int64_t lo,
                                 int64_t hi) {
    auto expr = Parameter(name, lo, hi);
    instance_parameters_.insert(name);
    if (lo == hi) instance_values_[name] = lo;
    return expr;
  }
  void Require(slinky::expr condition, std::string message) {
    checks_.emplace_back(std::move(condition), std::move(message));
  }
  void RequireBounds(slinky::expr condition, std::string message) {
    binding_checks_.emplace_back(std::move(condition), std::move(message));
  }
  void RequireChecked(std::function<bool(slinky::eval_context&)> condition,
                      std::string message) {
    checked_checks_.emplace_back(std::move(condition), std::move(message));
  }
  void InputShape(uint32_t id, std::vector<slinky::expr> shape) {
    if (packed_.count(id)) {
      const auto old = packed_.at(id).shape;
      if (shape.size() != old.size()) throw std::invalid_argument("packed rank mismatch");
      for (size_t j = 0; j < shape.size(); ++j) Require(old[j] == shape[j], "packed logical shape");
      return;
    }
    auto& v = graph_->value(id);
    if (shape.size() != v.rank())
      throw std::invalid_argument("input rank mismatch");
    for (size_t a = 0; a < shape.size(); ++a) {
      const int d = shape.size() - 1 - a;
      Require(v.extent(d) == shape[a], "shared input dimension");
      v.extents[d] =
          slinky::is_constant(shape[a], 1) ? slinky::expr{} : shape[a];
    }
  }
  void ResultShape(uint32_t id, const std::vector<slinky::expr>& shape) {
    const auto& v = graph_->value(id);
    if (shape.size() != (packed_.count(id) ? packed_.at(id).shape.size() : v.rank()))
      throw std::invalid_argument("result rank mismatch");
    for (size_t a = 0; a < shape.size(); ++a)
      Require(Axis(id, a) == shape[a], "declared result dimension: value " +
                                           std::to_string(id) + " axis " +
                                           std::to_string(a));
  }
  void Binary(ynn_binary_operator op, uint32_t a, uint32_t b, uint32_t out) {
    Check(ynn_define_binary(graph_.get(), op, a, b, &out, 0));
  }
  uint32_t TransposeLast(uint32_t in) {
    const auto rank = graph_->value(in).rank();
    if (rank < 2) throw std::invalid_argument("matrix rank < 2");
    std::vector<int32_t> axes(rank);
    for (int i = 0; i < rank; ++i) axes[i] = i;
    std::swap(axes[rank - 1], axes[rank - 2]);
    uint32_t out = YNN_INVALID_VALUE_ID;
    Check(ynn_define_static_transpose(graph_.get(), rank, axes.data(), in, &out,
                                      0));
    return out;
  }
  void Matmul(uint32_t a, uint32_t b, uint32_t out, bool adj_a, bool adj_b) {
    if (adj_a) a = TransposeLast(a);
    if (adj_b) b = TransposeLast(b);
    Check(ynn_define_dot(graph_.get(), 1, a, b, YNN_INVALID_VALUE_ID, &out, 0));
  }
  void Dot(uint32_t a, uint32_t b, uint32_t bias, uint32_t out, size_t k) {
    Check(ynn_define_dot(graph_.get(), k, a, b, bias, &out, 0));
  }
  void BroadcastLike(uint32_t in, uint32_t like, uint32_t out,
                     std::vector<int32_t> axes) {
    Check(ynn_define_broadcast_like(graph_.get(), axes.size(), axes.data(), in,
                                    like, &out, 0));
  }
  void Reduce(ynn_reduce_operator op, uint32_t in, uint32_t out,
              std::vector<int32_t> axes, bool keep) {
    Check(ynn_define_reduce(graph_.get(), op, axes.size(), axes.data(), in,
                            YNN_INVALID_VALUE_ID, &out,
                            keep ? YNN_NODE_FLAG_KEEP_DIMS : 0));
  }
  void DynamicQuantization(uint32_t in, uint32_t zero, uint32_t scale) {
    Check(ynn_define_dynamic_quantization(graph_.get(), in, ynn_type_int8,
                                          &zero, &scale, 0));
  }
  void QuantizeTensor(uint32_t in, uint32_t zero, uint32_t scale,
                      uint32_t out) {
    Check(ynn_define_quantize(graph_.get(), in, graph_->value(out).type, zero,
                              scale, &out, 0));
  }
  void DequantizeTensor(uint32_t in, uint32_t zero, uint32_t scale,
                        uint32_t out) {
    Check(ynn_define_dequantize(graph_.get(), in, zero, scale,
                                graph_->value(out).type, &out, 0));
  }
  void FuseDims(uint32_t in, uint32_t out, int axis, int count) {
    Check(ynn_define_fuse_dim(graph_.get(), axis, count, in, &out, 0));
  }
  void SplitDim(uint32_t in, uint32_t out, int axis, std::vector<size_t> dims) {
    Check(ynn_define_split_dim(graph_.get(), axis, dims.size(), dims.data(), in,
                               &out, 0));
  }
  void ShapeProduct(uint32_t in, uint32_t out, std::vector<int32_t> axes) {
    Check(ynn_define_get_tensor_shape(
        graph_.get(), axes.size(), axes.data(), ynn_type_fp32, 0, in, &out,
        YNN_NODE_FLAG_RESHAPE_1D | YNN_NODE_FLAG_UNIQUE_DIMS));
  }
  void Polynomial(uint32_t in, uint32_t out, std::vector<double> coefficients) {
    if (coefficients.empty()) throw std::invalid_argument("empty polynomial");
    Check(ynn_define_unary_polynomial(graph_.get(), in, coefficients.size() - 1,
                                      coefficients.data(), &out, 0));
  }
  void Softmax(uint32_t in, uint32_t out, float beta) {
    Check(ynn::define_softmax(graph_.get(), in, beta, out));
  }
  void Quantize(uint32_t in, uint32_t out, float scale, int32_t zero) {
    Check(ynn_define_quantize(graph_.get(), in, graph_->value(out).type,
                              graph_->get_scalar_value_id(zero),
                              graph_->get_scalar_value_id(scale), &out, 0));
  }
  void Dequantize(uint32_t in, uint32_t out, float scale, int32_t zero) {
    Check(ynn_define_dequantize(
        graph_.get(), in, graph_->get_scalar_value_id(zero),
        graph_->get_scalar_value_id(scale), graph_->value(out).type, &out, 0));
  }
  void Unary(ynn_unary_operator op, uint32_t in, uint32_t out) {
    Check(ynn_define_unary(graph_.get(), op, in, &out, 0));
  }
  void Convert(uint32_t in, uint32_t out) {
    Check(
        ynn_define_convert(graph_.get(), in, graph_->value(out).type, &out, 0));
  }
  void Reshape(uint32_t in, uint32_t out, std::vector<size_t> dims) {
    Check(ynn_define_static_reshape(graph_.get(), dims.size(), dims.data(), in,
                                    &out, 0));
  }
  void BindScalarParameter(uint32_t input, std::string parameter) {
    const auto& v = graph_->value(input);
    if (v.rank() != 0 || v.type != ynn_type_int32 || !v.is_external_input())
      throw std::invalid_argument("scalar binding requires an INT32 scalar input");
    scalar_inputs_.emplace_back(input, std::move(parameter));
  }
  void ShapeTensor(uint32_t out, std::vector<slinky::expr> elements, bool scalar) {
    auto& output = graph_->value(out);
    if (output.type != ynn_type_int32 || (scalar && elements.size() != 1))
      throw std::invalid_argument("shape tensor requires INT32 scalar/vector");
    output.extents = scalar ? std::vector<slinky::expr>{}
                            : std::vector<slinky::expr>{static_cast<int64_t>(elements.size())};
    ynn_node node;
    node.op = ynn_node::opaque{"core_shape_tensor"};
    node.outputs = {out};
    node.create = [elements = std::move(elements), scalar](const ynn_node& n, ynn_runtime& r) {
      auto& b = r.value(n.outputs[0]);
      b.make_buffer(r, sizeof(int32_t));
      auto dims = r.globals.make_dims(b.rank());
      slinky::call_stmt::attributes attrs;
      attrs.name = "core_shape_tensor";
      auto fn = [scalar](const slinky::call_stmt* call, slinky::eval_context& ctx) -> slinky::index_t {
        auto& output = ctx.lookup_buffer(call->outputs[0])->cast<int32_t>();
        if (scalar) output() = slinky::evaluate(call->scalars[0], ctx);
        else for (auto i = output.dim(0).min(); i <= output.dim(0).max(); ++i)
          output(i) = slinky::evaluate(call->scalars[i], ctx);
        return 0;
      };
      auto f = slinky::func(fn, {}, {{b.buffer, dims}}, elements, attrs);
      f.compute_root();
      b.buffer->store_root();
      r.funcs.push_back(std::move(f));
      return ynn_status_success;
    };
    graph_->add_node(std::move(node));
  }
  // Exact fallback for shapes the native one-inferred-axis API cannot express.
  // This is a materializing logical reshape, never a persistent-state view.
  void SymbolicReshape(uint32_t in, uint32_t out, std::vector<slinky::expr> shape) {
    auto extents = shape;
    std::reverse(extents.begin(), extents.end());
    IndexedCopy("core_symbolic_reshape", in, out, std::move(shape),
                [extents = std::move(extents)](const ynn_runtime_value& a,
                                              const std::vector<slinky::var>& dims) {
      slinky::expr ordinal = 0;
      for (int d = static_cast<int>(dims.size()) - 1; d >= 0; --d)
        ordinal = ordinal * slinky::max(extents[d], 1) + dims[d];
      slinky::box_expr bounds;
      for (size_t d = 0; d < a.rank(); ++d) {
        auto extent = slinky::max(a.extent(d), 1);
        bounds.push_back(slinky::point(ordinal % extent));
        ordinal = ordinal / extent;
      }
      return bounds;
    });
  }
  void Copy(uint32_t in, uint32_t out) {
    Check(ynn_define_copy(graph_.get(), in, &out, 0));
  }
  void SliceLike(uint32_t in, uint32_t like, uint32_t out,
                 std::vector<int32_t> axes) {
    Check(ynn_define_slice_like(graph_.get(), axes.size(), axes.data(), in,
                                like, &out, 0));
  }
  void Broadcast(uint32_t in, uint32_t out, std::vector<size_t> shape) {
    Check(ynn_define_static_broadcast(graph_.get(), shape.size(), shape.data(),
                                      in, &out, 0));
  }
  // Ordinary logical routing: no persistent-state alias or no-copy promise.
  // Copy indices are Slinky expressions, evaluated in the prepared pipeline.
  using IndexMap = std::function<slinky::box_expr(
      const ynn_runtime_value&, const std::vector<slinky::var>&)>;
  void IndexedCopy(const char* name, uint32_t in, uint32_t out,
                   std::vector<slinky::expr> shape, IndexMap map) {
    const auto input = graph_->value(in);
    auto& output = graph_->get_output_value(&out, input);
    output.extents.assign(shape.rbegin(), shape.rend());
    for (auto& d : output.extents)
      if (slinky::is_constant(d, 1)) d = {};
    ynn_node node;
    node.op = ynn_node::opaque{name};
    node.inputs = {in};
    node.outputs = {out};
    node.create = [map = std::move(map)](const ynn_node& n, ynn_runtime& r) {
      const auto& a = r.value(n.inputs[0]);
      auto& b = r.value(n.outputs[0]);
      b.make_buffer(r, a.buffer->elem_size());
      auto dims = r.globals.make_dims(b.rank());
      auto bounds = map(a, dims);
      r.funcs.push_back(slinky::func::make_copy({a.buffer, std::move(bounds)},
                                                {b.buffer, std::move(dims)}));
      return ynn_status_success;
    };
    graph_->add_node(std::move(node));
  }
  void SymbolicBroadcast(uint32_t in, uint32_t out,
                         std::vector<slinky::expr> shape) {
    IndexedCopy(
        "core_symbolic_broadcast", in, out, std::move(shape),
        [](const ynn_runtime_value& a, const std::vector<slinky::var>& dims) {
          slinky::box_expr bounds;
          for (size_t d = 0; d < a.rank(); ++d)
            bounds.push_back(
                slinky::point(slinky::select(a.extent(d) == 1, 0, dims[d])));
          return bounds;
        });
  }
  void Reverse(uint32_t in, uint32_t out, std::vector<int32_t> axes) {
    const int rank = graph_->value(in).rank();
    std::set<int> reversed;
    for (int a : axes) reversed.insert(rank - 1 - (a < 0 ? a + rank : a));
    std::vector<slinky::expr> shape;
    for (int i = 0; i < rank; ++i) shape.push_back(Axis(in, i));
    IndexedCopy("core_reverse", in, out, std::move(shape),
                [reversed](const ynn_runtime_value& a,
                           const std::vector<slinky::var>& dims) {
                  slinky::box_expr bounds;
                  for (int d = 0; d < a.rank(); ++d)
                    bounds.push_back(slinky::point(
                        reversed.count(d) ? a.extent(d) - 1 - dims[d]
                                          : slinky::expr(dims[d])));
                  return bounds;
                });
  }
  void Tile(uint32_t in, uint32_t out, std::vector<int64_t> multiples) {
    std::vector<slinky::expr> shape;
    for (size_t a = 0; a < multiples.size(); ++a)
      shape.push_back(Axis(in, a) * multiples[a]);
    IndexedCopy(
        "core_tile", in, out, std::move(shape),
        [](const ynn_runtime_value& a, const std::vector<slinky::var>& dims) {
          slinky::box_expr bounds;
          for (size_t d = 0; d < a.rank(); ++d)
            bounds.push_back(
                slinky::point(dims[d] % slinky::max(a.extent(d), 1)));
          return bounds;
        });
  }
  // Modes: constant=0, reflect=1 (exclude edge), symmetric=2 (include edge).
  void Pad(uint32_t in, uint32_t fill, uint32_t out,
           std::vector<slinky::expr> low, std::vector<slinky::expr> high,
           int mode) {
    std::vector<slinky::expr> shape;
    for (size_t a = 0; a < low.size(); ++a)
      shape.push_back(Axis(in, a) + low[a] + high[a]);
    std::reverse(low.begin(), low.end());
    if (mode != 0) {
      IndexedCopy("core_mirror_pad", in, out, std::move(shape),
                  [low, mode](const ynn_runtime_value& a,
                              const std::vector<slinky::var>& dims) {
                    slinky::box_expr bounds;
                    const int edge = mode == 2 ? 1 : 0;
                    for (size_t d = 0; d < a.rank(); ++d) {
                      slinky::expr x = dims[d] - low[d];
                      x = slinky::select(
                          x < 0, -x - edge,
                          slinky::select(x >= a.extent(d),
                                         2 * a.extent(d) - 2 + edge - x, x));
                      bounds.push_back(slinky::point(x));
                    }
                    return bounds;
                  });
      return;
    }
    const auto input = graph_->value(in);
    auto& output = graph_->get_output_value(&out, input);
    output.extents.assign(shape.rbegin(), shape.rend());
    ynn_node node;
    node.op = ynn_node::opaque{"core_symbolic_pad"};
    node.inputs = {in, fill};
    node.outputs = {out};
    node.create = [low](const ynn_node& n, ynn_runtime& r) {
      const auto& a = r.value(n.inputs[0]);
      const auto& fill = r.value(n.inputs[1]);
      auto& b = r.value(n.outputs[0]);
      b.make_buffer(r, a.buffer->elem_size());
      auto dims = r.globals.make_dims(b.rank());
      slinky::func::input source{a.buffer, {}};
      for (size_t d = 0; d < a.rank(); ++d) {
        source.bounds.push_back(slinky::point(dims[d] - low[d]));
        source.input_crop.push_back(slinky::min_extent(0, a.extent(d)));
      }
      r.funcs.push_back(slinky::func::make_copy(
          std::move(source), {b.buffer, std::move(dims)}, {fill.buffer, {}}));
      return ynn_status_success;
    };
    graph_->add_node(std::move(node));
  }
  void Select(uint32_t condition, uint32_t yes, uint32_t no, uint32_t out,
              std::vector<slinky::expr> shape) {
    const auto input = graph_->value(yes);
    auto& output = graph_->get_output_value(&out, input);
    output.extents.assign(shape.rbegin(), shape.rend());
    ynn_node node;
    node.op = ynn_node::opaque{"core_select"};
    node.inputs = {condition, yes, no};
    node.outputs = {out};
    node.create = [](const ynn_node& n, ynn_runtime& r) {
      const auto& c = r.value(n.inputs[0]);
      const auto& a = r.value(n.inputs[1]);
      const auto& b = r.value(n.inputs[2]);
      auto& y = r.value(n.outputs[0]);
      y.make_buffer(r, a.buffer->elem_size());
      auto dims = r.globals.make_dims(y.rank());
      auto bounds = [&](const ynn_runtime_value& v) {
        auto b = ynn::make_elementwise_bounds(dims, v.physical_extents());
        b.resize(v.rank());
        return b;
      };
      auto fn = [](const slinky::raw_buffer& c, const slinky::raw_buffer& a,
                   const slinky::raw_buffer& b,
                   const slinky::raw_buffer& y) -> slinky::index_t {
        // Broadcast singleton dimensions without changing the underlying data.
        auto broadcast = [&](const slinky::raw_buffer& source) {
          slinky::buffer<const void, ynn::max_tensor_rank> result = source;
          for (size_t d = 0; d < source.rank; ++d)
            if (source.dim(d).extent() == 1 && y.dim(d).extent() != 1) {
              result.mutable_dim(d).set_stride(0);
              result.mutable_dim(d).set_bounds(y.dim(d).min(), y.dim(d).max());
            }
          return result;
        };
        auto cc = broadcast(c), aa = broadcast(a), bb = broadcast(b);
        slinky::for_each_element(
            [&](void* dst, const void* cond, const void* av, const void* bv) {
              std::memcpy(dst, *static_cast<const uint8_t*>(cond) ? av : bv,
                          y.elem_size);
            },
            y, cc, aa, bb);
        return 0;
      };
      slinky::call_stmt::attributes attrs;
      attrs.name = "core_select";
      auto f = slinky::func::make(
          std::move(fn),
          {{c.buffer, bounds(c)}, {a.buffer, bounds(a)}, {b.buffer, bounds(b)}},
          {{y.buffer, dims}}, attrs);
      auto schedule =
          r.make_schedule(dims, y.physical_extents(), y.buffer->elem_size());
      f.user_data() = schedule.get();
      r.scheduling_info_storage.push_back(std::move(schedule));
      r.funcs.push_back(std::move(f));
      return ynn_status_success;
    };
    graph_->add_node(std::move(node));
  }
  void Gather(uint32_t in, uint32_t indices, uint32_t out, int axis) {
    // Core replaces one data axis with the entire indices shape. YNN gathers
    // aligned axes, so introduce singleton axes around the two operands.
    const int rank = graph_->value(in).rank();
    const int irank = graph_->value(indices).rank();
    if (rank + irank > ynn::max_tensor_rank)
      throw std::invalid_argument(
          "gather expansion exceeds YNNPACK rank limit");
    if (axis < 0) axis += rank;
    std::vector<int32_t> data_axes, index_axes;
    for (int i = 0; i < irank; ++i) data_axes.push_back(axis + 1 + i);
    for (int i = 0; i <= axis; ++i) index_axes.push_back(i);
    for (int i = axis + 1 + irank; i < rank + irank; ++i)
      index_axes.push_back(i);
    uint32_t a = in, b = indices, gathered = YNN_INVALID_VALUE_ID;
    if (!data_axes.empty()) {
      a = YNN_INVALID_VALUE_ID;
      Check(ynn_define_static_expand_dims(graph_.get(), data_axes.size(),
                                          data_axes.data(), in, &a, 0));
    }
    b = YNN_INVALID_VALUE_ID;
    Check(ynn_define_static_expand_dims(graph_.get(), index_axes.size(),
                                        index_axes.data(), indices, &b, 0));
    int32_t ax = axis;
    Check(ynn_define_gather(graph_.get(), 1, &ax, rank + irank, a, b, &gathered,
                            0));
    Squeeze(gathered, out, {axis});
  }
  void ExpandDims(uint32_t in, uint32_t out, std::vector<int32_t> axes) {
    Check(ynn_define_static_expand_dims(graph_.get(), axes.size(), axes.data(),
                                        in, &out, 0));
  }
  void Squeeze(uint32_t in, uint32_t out, std::vector<int32_t> axes) {
    std::vector<int32_t> permutation;
    for (int32_t i = 0; i < graph_->value(in).rank(); ++i)
      if (std::find(axes.begin(), axes.end(), i) == axes.end())
        permutation.push_back(i);
    Transpose(in, out, std::move(permutation));
  }
  void Stack(std::vector<uint32_t> inputs, uint32_t out, int axis) {
    Check(ynn_define_stack(graph_.get(), axis, inputs.size(), inputs.data(),
                           &out, 0));
  }
  void Split(uint32_t in, std::vector<uint32_t> outputs, int axis,
             bool unstack) {
    auto parts = outputs;
    if (unstack) std::fill(parts.begin(), parts.end(), YNN_INVALID_VALUE_ID);
    Check(ynn_define_even_split(graph_.get(), axis, in, parts.size(),
                                parts.data(), 0));
    if (unstack)
      for (size_t i = 0; i < outputs.size(); ++i)
        Squeeze(parts[i], outputs[i], {axis});
  }
  void SymbolicSlice(uint32_t in, uint32_t out,
                     std::vector<slinky::expr> starts,
                     std::vector<slinky::expr> lengths) {
    if (starts.size() != lengths.size() ||
        starts.size() != graph_->value(in).rank())
      throw std::invalid_argument("symbolic slice rank");
    if (starts.empty()) {
      Copy(in, out);
      return;
    }
    for (size_t axis = 0; axis < starts.size(); ++axis) {
      uint32_t next = axis + 1 == starts.size() ? out : YNN_INVALID_VALUE_ID;
      // View allocates an ID internally, so reserve intermediates explicitly.
      if (next == YNN_INVALID_VALUE_ID)
        graph_->get_output_value(&next, graph_->value(in));
      View(in, next, axis, starts[axis], starts[axis] + lengths[axis], false);
      in = next;
    }
  }
  void Transpose(uint32_t in, uint32_t out, std::vector<int32_t> axes) {
    Check(ynn_define_static_transpose(graph_.get(), axes.size(), axes.data(),
                                      in, &out, 0));
  }
  void Slice(uint32_t in, uint32_t out, std::vector<int64_t> begins,
             std::vector<int64_t> sizes) {
    // Native static_slice treats end==0 as the input extent, not an empty
    // interval. Preserve literal-zero semantics using explicit expressions.
    if (std::find(sizes.begin(), sizes.end(), 0) != sizes.end()) {
      std::vector<slinky::expr> starts, lengths;
      for (size_t i = 0; i < sizes.size(); ++i) {
        starts.push_back(begins[i]);
        lengths.push_back(sizes[i] == -1 ? Axis(in, i) - begins[i]
                                         : slinky::expr(sizes[i]));
      }
      SymbolicSlice(in, out, std::move(starts), std::move(lengths));
      return;
    }
    std::vector<int32_t> axes;
    std::vector<int64_t> starts, ends, strides;
    for (size_t d = 0; d < sizes.size(); ++d) {
      if (sizes[d] == -1 && begins[d] == 0) continue;
      if (sizes[d] < 0)
        throw std::invalid_argument("nonzero dynamic slice origin");
      axes.push_back(d);
      starts.push_back(begins[d]);
      ends.push_back(begins[d] + sizes[d]);
      strides.push_back(1);
    }
    Check(ynn_define_static_slice(graph_.get(), axes.size(), axes.data(),
                                  starts.data(), ends.data(), strides.data(),
                                  in, &out, 0));
  }
  void Concat(std::vector<uint32_t> inputs, uint32_t out, int axis) {
    Check(ynn_define_concatenate(graph_.get(), axis, inputs.size(),
                                 inputs.data(), &out, 0));
  }
  void Mean(uint32_t in, uint32_t out, std::vector<int32_t> axes, bool keep) {
    Check(ynn::define_reduce_sum(
        graph_.get(), axes.size(), axes.data(), in, YNN_INVALID_VALUE_ID,
        YNN_INVALID_VALUE_ID, keep, true, false, graph_->value(out).type,
        YNN_INVALID_VALUE_ID, YNN_INVALID_VALUE_ID, out));
  }
  void Gelu(uint32_t in, uint32_t out, bool approximate) {
    Check(approximate ? ynn::define_approx_gelu(graph_.get(), in, out)
                      : ynn::define_gelu(graph_.get(), in, out));
  }
  void FullyConnected(uint32_t in, uint32_t weight, uint32_t out,
                      const float* weight_scales, size_t scale_count,
                      float input_scale, float output_scale) {
    uint32_t ws = YNN_INVALID_VALUE_ID;
    Check(ynn_define_tensor(graph_.get(), ynn_type_fp32, 1, &scale_count,
                            weight_scales, 0, &ws));
    uint32_t az = YNN_INVALID_VALUE_ID, as = YNN_INVALID_VALUE_ID;
    if (input_scale > 0) {
      as = graph_->get_scalar_value_id(input_scale);
    } else {
      int32_t axis = -1;
      uint32_t mm = YNN_INVALID_VALUE_ID, quantized = YNN_INVALID_VALUE_ID;
      Check(ynn_define_reduce(graph_.get(), ynn_reduce_min_max, 1, &axis, in,
                              YNN_INVALID_VALUE_ID, &mm,
                              YNN_NODE_FLAG_KEEP_DIMS));
      Check(ynn_define_dynamic_quantization(graph_.get(), mm, ynn_type_int8,
                                            &az, &as, 0));
      Check(ynn_define_quantize(graph_.get(), in, ynn_type_int8, az, as,
                                &quantized, 0));
      in = quantized;
    }
    auto wt = TransposeLast(weight);
    uint32_t zp = YNN_INVALID_VALUE_ID, scale = YNN_INVALID_VALUE_ID;
    Check(ynn::define_dot_quantization(graph_.get(), 1, in, az, as, wt,
                                       YNN_INVALID_VALUE_ID, ws, zp, scale));
    uint32_t bias = YNN_INVALID_VALUE_ID;
    if (zp != YNN_INVALID_VALUE_ID)
      Check(ynn_define_unary(graph_.get(), ynn_unary_negate, zp, &bias, 0));
    uint32_t acc = YNN_INVALID_VALUE_ID;
    Check(ynn_define_dot(graph_.get(), 1, in, wt, bias, &acc, 0));
    uint32_t f = output_scale > 0 ? YNN_INVALID_VALUE_ID : out;
    Check(ynn_define_dequantize(graph_.get(), acc, YNN_INVALID_VALUE_ID, scale,
                                ynn_type_fp32, &f, 0));
    if (output_scale > 0) Quantize(f, out, output_scale, 0);
  }

  bool Has(const std::string& name) const { return names_.count(name); }

  // Shared declarations lower to byte-addressable contiguous external owners.
  void Resource(uint32_t owner, std::string identity, int axis,
                slinky::expr entry_extent, std::string encoding) {
    const auto& value = graph_->value(owner);
    if (!value.is_external_input() || axis != value.rank() - 2 ||
        resources_.count(owner))
      throw std::invalid_argument("YNNPACK resource capability: unique token-major owner");
    for (const auto& [id, resource] : resources_)
      if (resource.identity == identity)
        throw std::invalid_argument("duplicate resource identity");
    resources_.emplace(owner, ResourceBinding{std::move(identity), axis,
        std::move(entry_extent), std::move(encoding)});
  }
  std::shared_ptr<ResourceState> NewResourceState(
      const std::string& name, void* data, size_t bytes,
      std::vector<size_t> shape = {}, size_t initialized = 0) const {
    const uint32_t id = names_.at(name);
    const auto& declaration = resources_.at(id);
    const auto& value = graph_->value(id);
    if (shape.empty()) {
      for (int axis = 0; axis < value.rank(); ++axis) {
        auto dimension = slinky::as_constant(value.extent(value.rank() - 1 - axis));
        if (!dimension || *dimension < 0)
          throw std::invalid_argument("dynamic resource needs concrete storage geometry");
        shape.push_back(size_t(*dimension));
      }
    }
    return std::make_shared<ResourceState>(data, bytes, std::move(shape),
        ynn::type_size_bytes(value.type), declaration.axis, declaration.encoding, initialized);
  }
  void BindResource(const std::string& name, std::shared_ptr<ResourceState> state) {
    if (!runtime_) throw std::logic_error("uncompiled graph");
    const uint32_t id = names_.at(name);
    auto& declaration = resources_.at(id);
    if (!state || state->encoding_ != declaration.encoding ||
        state->axis_ != size_t(declaration.axis) ||
        state->element_bytes_ != ynn::type_size_bytes(graph_->value(id).type) ||
        state->shape_.size() != size_t(graph_->value(id).rank()))
      throw std::invalid_argument("incompatible resource state");
    declaration.state = std::move(state);
    declaration.epoch = declaration.state->epoch_;
    BindTensor(name, declaration.state->data_, declaration.state->bytes_, declaration.state->shape_);
  }
  void View(uint32_t in, uint32_t out, int axis, slinky::expr begin,
            slinky::expr end, bool resource_view = true) {
    const auto& input = graph_->value(in);
    if (axis < 0 || axis >= input.rank())
      throw std::invalid_argument("view axis");
    const int d = input.rank() - 1 - axis;
    auto& output = graph_->get_output_value(&out, input);
    output.extents = input.extents;
    output.extents[d] = end - begin;
    Require(begin >= 0 && end >= begin && end <= input.extent(d),
            "view bounds");
    ynn_node node;
    node.op = ynn_node::opaque{resource_view ? "core_symbolic_view"
                                             : "core_symbolic_slice"};
    node.inputs = {in};
    node.outputs = {out};
    node.create = [d, begin, resource_view, stats = counters_](
                      const ynn_node& n, ynn_runtime& r) {
      const auto& a = r.value(n.inputs[0]);
      auto& b = r.value(n.outputs[0]);
      b.make_buffer(r, a.buffer->elem_size());
      auto dims = r.globals.make_dims(b.rank());
      slinky::box_expr bounds;
      for (int i = 0; i < b.rank(); ++i) {
        bounds.push_back(slinky::point(slinky::expr(dims[i]) +
                                       (i == d ? begin : slinky::expr(0))));
        // Preserve capacity strides. Compaction would turn this into a copy.
        if (resource_view)
          b.buffer->dim(i).stride = slinky::buffer_stride(a.buffer->sym(), i);
      }
      slinky::func::input src{a.buffer, bounds};
      src.output_crop.resize(b.rank());
      for (int i = 0; i < b.rank(); ++i)
        src.output_crop[i] = slinky::min_extent(0, b.extent(i));
      auto copy = [stats, resource_view](const slinky::raw_buffer& src,
                                         const slinky::raw_buffer& dst,
                                         const slinky::raw_buffer& pad) {
        if (resource_view)
          stats->view_copy_bytes += dst.elem_count() * dst.elem_size;
        slinky::copy(src, dst, pad);
      };
      auto f = slinky::func::make_copy(std::move(src), {b.buffer, dims}, copy);
      f.compute_root();
      b.buffer->store_root();
      r.funcs.push_back(std::move(f));
      return ynn_status_success;
    };
    graph_->add_node(std::move(node));
  }

  void Append(uint32_t cache, uint32_t fresh, uint32_t out, int axis,
              slinky::expr p, slinky::expr logical_length) {
    const auto& c = graph_->value(cache);
    const auto& a = graph_->value(fresh);
    const uint32_t owner = alias_owners_.count(cache) ? alias_owners_.at(cache) : cache;
    if (!resources_.count(owner))
      throw std::invalid_argument("append requires a shared resource declaration");
    resources_.at(owner).append_lengths.push_back(logical_length);
    if (c.type != a.type || c.rank() != a.rank() || axis != c.rank() - 2)
      throw std::invalid_argument(
          "append requires matching token-major tensors");
    if ((!c.is_external_input() && !alias_owners_.count(cache)) ||
        alias_owners_.count(out))
      throw std::invalid_argument(
          "append requires a unique external cache owner");
    auto& b = graph_->get_output_value(&out, c);
    b.extents = c.extents;
    if (!b.is_external_output())
      throw std::invalid_argument("append must be an effect root");
    for (int d = 0; d < c.rank(); ++d)
      if (d != 1) Require(c.extent(d) == a.extent(d), "append row shape");
    Require(p >= 0 && logical_length >= 0 && p + logical_length <= c.extent(1), "append capacity");
    aliases_[owner].push_back(out);
    alias_owners_.emplace(out, owner);
    ynn_node n;
    n.op = ynn_node::opaque{"core_append_rows"};
    n.inputs = {cache, fresh};
    n.outputs = {out};
    n.create = [p, logical_length, stats = counters_](const ynn_node& n, ynn_runtime& r) {
      const auto& old = r.value(n.inputs[0]);
      const auto& a = r.value(n.inputs[1]);
      auto& b = r.value(n.outputs[0]);
      b.make_buffer(r, a.buffer->elem_size());
      auto dims = r.globals.make_dims(b.rank());
      slinky::box_expr old_bounds, new_bounds;
      for (int d = 0; d < b.rank(); ++d) {
        old_bounds.push_back(slinky::min_extent(0, old.extent(d)));
        new_bounds.push_back(slinky::min_extent(0, a.extent(d)));
      }
      slinky::call_stmt::attributes attrs;
      attrs.name = "core_append_rows";
      attrs.allow_in_place = 1;  // output 0 explicitly aliases cache input 0.
      auto callback = [stats](const slinky::call_stmt* call,
                              slinky::eval_context& ctx) -> slinky::index_t {
        if (stats->append_calls == stats->fail_before_append) return 1;
        const auto* old = ctx.lookup_buffer(call->inputs[0]);
        const auto* src = ctx.lookup_buffer(call->inputs[1]);
        const auto* dst = ctx.lookup_buffer(call->outputs[0]);
        if (old->base != dst->base) return 1;
        const auto p = slinky::evaluate(call->scalars[0], ctx);
        slinky::buffer<const void, 8> a(*src);
        slinky::buffer<void, 8> b(*dst);
        const auto expected = slinky::evaluate(call->scalars[1], ctx);
        if (a.dim(1).extent() != expected || p < 0 || expected < 0 ||
            p > b.dim(1).extent() || expected > b.dim(1).extent() - p) return 1;
        if (stats->before_append) stats->before_append(stats->append_calls);
        if (a.elem_count() == 0) { ++stats->append_calls; return 0; }
        b.crop(1, p, p + a.dim(1).extent() - 1);
        b.translate(0, -p);
        slinky::copy(a, b);
        ++stats->append_calls;
        stats->append_bytes += a.elem_count() * a.elem_size;
        return 0;
      };
      auto f = slinky::func(callback,
                            {{old.buffer, old_bounds}, {a.buffer, new_bounds}},
                            {{b.buffer, dims}}, {p, logical_length}, attrs);
      f.compute_root();
      b.buffer->store_root();
      r.funcs.push_back(std::move(f));
      return ynn_status_success;
    };
    graph_->add_node(std::move(n));
  }

  void Mask(uint32_t in, uint32_t out, slinky::expr p, slinky::expr begin,
            int window, bool scheduled = LAB_YNN_DEFAULT_SCHEDULED_MASK) {
    const auto& a = graph_->value(in);
    if (a.type != ynn_type_fp32 || a.rank() != 4)
      throw std::invalid_argument("mask expects fp32 rank 4");
    if (window < 0) throw std::invalid_argument("negative attention window");
    Require(a.extent(3) == 1, "mask currently supports batch one");
    auto& b = graph_->get_output_value(&out, a);
    b.extents = a.extents;
    ynn_node n;
    n.op = ynn_node::opaque{"core_causal_mask"};
    n.inputs = {in};
    n.outputs = {out};
    n.create = [p, begin, window, scheduled](const ynn_node& n,
                                             ynn_runtime& r) {
      const auto& a = r.value(n.inputs[0]);
      auto& b = r.value(n.outputs[0]);
      b.make_buffer(r, a.buffer->elem_size());
      auto dims = r.globals.make_dims(b.rank());
      slinky::box_expr bounds;
      for (int d = 0; d < b.rank(); ++d)
        bounds.push_back(scheduled ? slinky::point(dims[d])
                                   : slinky::min_extent(0, b.extent(d)));
      slinky::call_stmt::attributes attrs;
      attrs.name = "core_causal_mask";
      auto fn = [window](const slinky::call_stmt* call,
                         slinky::eval_context& ctx) -> slinky::index_t {
        const auto& a = ctx.lookup_buffer(call->inputs[0])->cast<const float>();
        const auto& b = ctx.lookup_buffer(call->outputs[0])->cast<float>();
        auto p = slinky::evaluate(call->scalars[0], ctx),
             start = slinky::evaluate(call->scalars[1], ctx);
        for (int64_t h = b.dim(2).min(); h <= b.dim(2).max(); ++h)
          for (int64_t i = b.dim(1).min(); i <= b.dim(1).max(); ++i)
            for (int64_t j = b.dim(0).min(); j <= b.dim(0).max(); ++j) {
              const auto q = p + i, k = start + j;
              b(j, i, h, 0) = (k <= q && (window <= 0 || k >= q - window + 1))
                                  ? a(j, i, h, 0)
                                  : -std::numeric_limits<float>::infinity();
            }
        return 0;
      };
      auto f = slinky::func(fn, {{a.buffer, bounds}}, {{b.buffer, dims}},
                            {p, begin}, attrs);
      if (scheduled) {
        auto schedule =
            r.make_schedule(dims, b.physical_extents(), b.buffer->elem_size());
        f.user_data() = schedule.get();
        r.scheduling_info_storage.push_back(std::move(schedule));
      } else {
        f.compute_root();
        b.buffer->store_root();
      }
      r.funcs.push_back(std::move(f));
      return ynn_status_success;
    };
    graph_->add_node(std::move(n));
  }

  void Compile(size_t threads = 1) {
    if (runtime_) throw std::logic_error("already compiled");
    if (operation_open_) throw std::invalid_argument("unclosed completion boundary");
    // Old-version readers need explicit completion coverage before mutation;
    // the writer's own cache input carries its alias/generation dependency.
    // Check physical read-before-write prerequisites as well as Core's semantic
    // verifier. Direct adapter users cannot bypass ordering by adding any token.
    for (size_t i = 0; i < graph_->nodes.size(); ++i) {
      const auto& writer = graph_->nodes[i];
      if (writer.outputs.size() != 1 || !alias_owners_.count(writer.outputs[0])) continue;
      const uint32_t cache = writer.inputs[0];
      const auto prerequisites = node_prerequisites_.find(i);
      for (size_t j = 0; j < graph_->nodes.size(); ++j) {
        if (j == i) continue;
        const auto& reader = graph_->nodes[j];
        if (std::find(reader.inputs.begin(), reader.inputs.end(), cache) == reader.inputs.end()) continue;
        const bool ordered = j < i && prerequisites != node_prerequisites_.end() &&
            prerequisites->second.count(j);
        if (!ordered) throw std::invalid_argument("live old-state consumer lacks completion ordering");
      }
    }
    Check(ynn_optimize_subgraph(graph_.get(), nullptr, 0));
    if (execution_profile_) execution_profile_->AttachCreators(*graph_);
    if (threads > 1)
      pool_ = std::make_unique<slinky::thread_pool_impl>(threads - 1);
    ynn_runtime_t runtime = nullptr;
    Check(ynn_create_runtime(graph_.get(),
                             reinterpret_cast<ynn_threadpool_t>(pool_.get()), 0,
                             &runtime));
    runtime_.reset(runtime);
    if (execution_profile_)
      runtime_->pipeline.body = execution_profile_->Instrument(runtime_->pipeline.body);
    for (const auto& [name, value] : instance_values_) {
      runtime_->scalar_parameter_values.at(parameters_.at(name)) = value;
      scalar_bound_.insert(name);
    }
    shape_context_.config = &runtime_->eval_config;
    pipeline_ = runtime_->pipeline.body;
    // Reshape inference can introduce let-bound dimensions. Evaluate frontend
    // guards in the same scope as YNNPACK's own reshape guards.
    auto preflight = [this](const slinky::call_stmt*,
                            slinky::eval_context& ctx) -> slinky::index_t {
      for (const auto& [condition, message] : checks_)
        if (!slinky::evaluate(condition, ctx))
          throw std::invalid_argument(message);
      return 0;
    };
    preflight_ = slinky::let_stmt::make(
        runtime_->globals.lets,
        slinky::call_stmt::make(std::move(preflight), {}, {}, {}, {}));
  }
  void ScalarValue(const std::string& name, int64_t value) {
    if (!runtime_) throw std::logic_error("uncompiled graph");
    if (instance_parameters_.count(name)) {
      const auto& range = parameter_ranges_.at(name);
      if (value < range.first || value > range.second)
        throw std::invalid_argument("scalar bounds: " + name);
      auto [it, inserted] = instance_values_.emplace(name, value);
      if (!inserted && it->second != value)
        throw std::invalid_argument("immutable instance parameter changed: " +
                                    name);
    }
    runtime_->scalar_parameter_values.at(parameters_.at(name)) = value;
    scalar_bound_.insert(name);
  }
  // Diagnostic only: exposing an intermediate can change fusion/rounding.
  // Always compare final outputs with an uninstrumented run as well.
  void ExposeForInspection(const std::string& name) {
    if (runtime_) throw std::logic_error("inspection must precede compilation");
    auto& value = graph_->value(names_.at(name));
    if (value.is_static())
      throw std::invalid_argument("cannot expose a constant");
    if (!value.is_external_input())
      value.flags |= YNN_VALUE_FLAG_EXTERNAL_OUTPUT;
  }
  const slinky::raw_buffer& InspectionBuffer(const std::string& name) const {
    if (!runtime_) throw std::logic_error("uncompiled graph");
    const auto& value = runtime_->value(names_.at(name));
    if (!value.is_external() || !value.data || !value.data->base)
      throw std::invalid_argument("inspection needs a bound external value");
    return *value.data;
  }
  void Bind(const std::string& name, void* data, size_t bytes,
            std::vector<size_t> shape = {}) {
    if (resources_.count(names_.at(name)))
      throw std::invalid_argument("bind persistent storage through BindResource");
    BindTensor(name, data, bytes, std::move(shape));
  }
 private:
  void RefreshNodeDependencies(size_t end) {
    for (; indexed_nodes_ < end; ++indexed_nodes_) {
      const auto& n = graph_->nodes[indexed_nodes_];
      std::set<size_t> predecessors{indexed_nodes_};
      for (auto input : n.inputs) {
        const auto& prior = value_node_dependencies_[input];
        predecessors.insert(prior.begin(), prior.end());
      }
      const auto wait = node_prerequisites_.find(indexed_nodes_);
      if (wait != node_prerequisites_.end())
        predecessors.insert(wait->second.begin(), wait->second.end());
      for (auto out : n.outputs) value_node_dependencies_[out] = predecessors;
    }
  }
  void BindTensor(const std::string& name, void* data, size_t bytes,
                  std::vector<size_t> shape) {
    if (!runtime_) throw std::logic_error("uncompiled graph");
    const uint32_t id = names_.at(name);
    if (alias_owners_.count(id))
      throw std::invalid_argument("bind the cache owner, not its alias");
    if (packed_.count(id)) {
      const auto& p = packed_.at(id);
      if (!p.parameters.empty()) {
        if (shape.size() != p.parameters.size()) throw std::invalid_argument("bind packed input logical shape");
        for (size_t j = 0; j < shape.size(); ++j) ScalarValue(p.parameters[j], shape[j]);
      }
      if (!shape.empty()) {
        std::vector<int64_t> logical(shape.begin(), shape.end());
        shape = {size_t(packed::Bytes(packed::Count(logical), p.bits))};
      }
    }
    if (!shape.empty())
      Check(ynn_set_external_value_shape(runtime_.get(), id, shape.size(),
                                         shape.data()));
    Check(ynn_set_external_value_data(runtime_.get(), id, data));
    bound_.at(id) = {data, bytes};
    const auto alias = aliases_.find(id);
    if (alias != aliases_.end()) {
      for (auto updated : alias->second) {
        Check(ynn_set_external_value_data(runtime_.get(), updated, data));
        bound_.at(updated) = {data, bytes};
      }
    }
  }
  public:
  void Run() {
    ExecutionProfile::Span profile_span(execution_profile_.get(), 0);
    if (!runtime_) throw std::logic_error("uncompiled graph");
    if (failed_)
      throw std::logic_error("failed stateful runtime must be recreated");
    // Request scalars must be supplied again after success or rejection. Bound
    // input shapes and immutable instance configuration retain their lifetime.
    struct RequestBindings {
      std::set<std::string>& bound;
      const std::set<std::string>& instances;
      const std::set<std::string>& shapes;
      ~RequestBindings() {
        for (auto it = bound.begin(); it != bound.end();)
          if (instances.count(*it) || shapes.count(*it))
            ++it;
          else
            it = bound.erase(it);
      }
    } request_bindings{scalar_bound_, instance_parameters_, shape_parameters_};
    for (const auto& [id, name] : scalar_inputs_) {
      if (!bound_.at(id).first || bound_[id].second < sizeof(int32_t))
        throw std::invalid_argument("missing scalar input buffer");
      int32_t value;
      std::memcpy(&value, bound_[id].first, sizeof(value));
      ScalarValue(name, value);
    }
    if (scalar_bound_.size() != parameters_.size())
      throw std::invalid_argument("unbound scalar");
    // Slinky may recycle an unused input symbol for a compiled constant let.
    // A buffer used only by forward shape expressions is still live here, even
    // when its data is absent from the compute pipeline. Evaluate the original
    // shape program in its own context, using the original external symbols;
    // pipeline.setup() installs the compute program's symbol assignments later.
    for (size_t i = 0; i < graph_->scalar_parameters.size(); ++i)
      shape_context_[graph_->scalar_parameters[i]] = runtime_->scalar_parameter_values[i];
    for (const auto& v : runtime_->values)
      if (v.is_valid() && v.is_external())
        shape_context_[v.symbol] =
            reinterpret_cast<slinky::index_t>(v.data.get());
    // Raw binding bounds must precede even the let-bound forward shape
    // program: its arithmetic is justified only inside those declared ranges.
    for (const auto& [condition, message] : binding_checks_)
      if (!slinky::evaluate(condition, shape_context_))
        throw std::invalid_argument(message);
    for (const auto& [condition, message] : checked_checks_)
      if (!condition(shape_context_)) throw std::invalid_argument(message);
    slinky::evaluate(preflight_, shape_context_);
    Check(static_cast<ynn_status>(
        slinky::evaluate(runtime_->reshape_impl, shape_context_)));
    for (size_t id = 0; id < bound_.size(); ++id) {
      const auto& v = runtime_->value(id);
      if (!v.is_valid() || !v.is_external()) continue;
      if (!bound_[id].first || v.data->size_bytes() > bound_[id].second)
        throw std::invalid_argument("missing or undersized external buffer");
    }
    struct ResourceLease {
      std::vector<std::shared_ptr<ResourceState>> states;
      ~ResourceLease() { for (auto& state : states) state->busy_.store(false); }
    } lease;
    std::vector<std::pair<ResourceState*, size_t>> pending;
    std::set<ResourceState*> unique;
    for (const auto& [owner, declaration] : resources_) {
      const auto& state = declaration.state;
      if (!state || !unique.insert(state.get()).second)
        throw std::invalid_argument("missing or multiply owned resource state");
      bool available = false;
      if (!state->busy_.compare_exchange_strong(available, true))
        throw std::logic_error("concurrent resource execution is unsupported");
      lease.states.push_back(state);
      if (state->poisoned_ || state->epoch_ != declaration.epoch)
        throw std::invalid_argument("poisoned resource or stale reset epoch; reset/rebind required");
      const auto extent = slinky::evaluate(declaration.entry_extent, shape_context_);
      size_t length = 0;
      const size_t remaining = state->shape_[state->axis_] - state->committed_;
      for (const auto& expression : declaration.append_lengths) {
        const auto n = slinky::evaluate(expression, shape_context_);
        if (n < 0 || size_t(n) > remaining - length)
          throw std::invalid_argument("resource append chain exceeds capacity");
        length += size_t(n);
      }
      if (extent < 0 || size_t(extent) != state->committed_)
        throw std::invalid_argument("resource " + declaration.identity +
            " extent differs from committed state or exceeds capacity: entry=" +
            std::to_string(extent) + ", committed=" + std::to_string(state->committed_) +
            ", append=" + std::to_string(length));
      pending.emplace_back(state.get(), state->committed_ + size_t(length));
    }
    // Resource owners, including read-only owners, cannot overlap other bindings.
    for (const auto& [cache, declaration] : resources_) {
      const auto start = reinterpret_cast<uintptr_t>(bound_[cache].first);
      const auto bytes = bound_[cache].second;
      if (bytes > std::numeric_limits<uintptr_t>::max() - start)
        throw std::invalid_argument("cache address overflow");
      for (size_t id = 0; id < bound_.size(); ++id) {
        const auto alias = aliases_.find(cache);
        if (id == cache || (alias != aliases_.end() &&
            std::find(alias->second.begin(), alias->second.end(), id) != alias->second.end()) ||
            !bound_[id].first) continue;
        const auto other = reinterpret_cast<uintptr_t>(bound_[id].first);
        if (bound_[id].second > std::numeric_limits<uintptr_t>::max() - other)
          throw std::invalid_argument("buffer address overflow");
        if (start < other + bound_[id].second && other < start + bytes)
          throw std::invalid_argument("undeclared cache alias");
      }
    }
    Check(runtime_->setup());
    invoked_ = true;
    try {
      const auto status = ynn_invoke_runtime(runtime_.get());
      if (status != ynn_status_success || counters_->view_copy_bytes)
        throw std::runtime_error("stateful invocation failed or materialized a cache view");
      if (!pipeline_.same_as(runtime_->pipeline.body))
        throw std::logic_error("pipeline rebuilt");
    } catch (...) {
      failed_ = true;
      for (auto& state : lease.states) state->poisoned_ = true;
      throw;
    }
    for (const auto& [state, extent] : pending) state->committed_ = extent;
  }
  Counters counters() const { return *counters_; }
  // Read-only diagnostics. This is the root context's pool, not a process-wide
  // allocation total; worker contexts and allocator-retained pages are
  // separate.
  size_t RetainedRootScratchBytes() const {
    if (!runtime_) throw std::logic_error("uncompiled graph");
    return runtime_->eval_context.pool.retained_size();
  }
  // Enable immediately after Compile, before any execution. Allocation hooks
  // perturb timing and measure execution scratch, not preparation/weight data.
  std::shared_ptr<const ScratchStatistics> TrackScratchAllocations() {
    if (!runtime_ || invoked_ || scratch_statistics_ ||
        runtime_->eval_context.pool.retained_size())
      throw std::logic_error("scratch tracking requires a fresh runtime");
    auto statistics = std::make_shared<ScratchStatistics>();
    auto allocate = runtime_->eval_config.allocate;
    auto release = runtime_->eval_config.free;
    runtime_->eval_config.allocate = [statistics, allocate](size_t size,
                                                            size_t alignment) {
      void* ptr = allocate(size, alignment);
      if (!ptr) return ptr;
      const size_t live = statistics->live.fetch_add(size) + size;
      size_t peak = statistics->peak.load();
      while (peak < live &&
             !statistics->peak.compare_exchange_weak(peak, live)) {
      }
      statistics->allocated.fetch_add(size);
      statistics->allocations.fetch_add(1);
      return ptr;
    };
    runtime_->eval_config.free = [statistics, release](void* ptr, size_t size) {
      statistics->live.fetch_sub(size);
      release(ptr, size);
    };
    scratch_statistics_ = statistics;
    return statistics;
  }
  // Diagnostic hook: fail after n further completed appends. Never retries.
  void FailAfterAppends(size_t n) {
    counters_->fail_before_append = counters_->append_calls + n;
    runtime_->eval_config.call_failed = [](const slinky::call_stmt*) {};
  }
  void ObserveAppends(std::function<void(size_t)> observer) {
    counters_->before_append = std::move(observer);
  }
  void Print(std::ostream& out) const {
    slinky::print(out, runtime_->pipeline.body, &runtime_->globals.symbols);
  }
  slinky::stmt pipeline() const { return pipeline_; }

 private:
  std::unique_ptr<ynn_subgraph, decltype(&ynn_delete_subgraph)> graph_{
      nullptr, ynn_delete_subgraph};
  std::unique_ptr<slinky::thread_pool_impl> pool_;
  std::unique_ptr<ynn_runtime, decltype(&ynn_delete_runtime)> runtime_{
      nullptr, ynn_delete_runtime};
  std::map<std::string, uint32_t> names_;
  std::vector<ProfileOperation> profile_operations_;
  size_t profile_node_begin_ = 0;
  bool profile_open_ = false;
  std::shared_ptr<ExecutionProfile> execution_profile_;
  std::map<std::string, size_t> parameters_;
  std::map<std::string, std::pair<int64_t, int64_t>> parameter_ranges_;
  std::set<std::string> instance_parameters_;
  std::set<std::string> shape_parameters_;
  std::map<std::string, int64_t> instance_values_;
  std::set<std::string> scalar_bound_;
  std::vector<std::pair<uint32_t, std::string>> scalar_inputs_;
  struct ResourceBinding {
    std::string identity;
    int axis;
    slinky::expr entry_extent;
    std::string encoding;
    std::vector<slinky::expr> append_lengths;
    std::shared_ptr<ResourceState> state;
    uint64_t epoch = 0;
  };
  std::map<uint32_t, ResourceBinding> resources_;
  std::map<uint32_t, std::vector<uint32_t>> aliases_;
  std::map<uint32_t, uint32_t> alias_owners_;
  std::map<std::string, std::set<uint32_t>> completion_anchors_;
  std::map<std::string, std::set<size_t>> completion_coverage_;
  std::map<uint32_t, std::set<size_t>> value_node_dependencies_;
  std::map<size_t, std::set<size_t>> node_prerequisites_;
  std::set<uint32_t> operation_waits_;
  std::set<size_t> operation_coverage_;
  size_t indexed_nodes_ = 0;
  size_t operation_begin_ = 0;
  bool operation_open_ = false;
  std::vector<std::pair<slinky::expr, std::string>> checks_;
  std::vector<std::pair<slinky::expr, std::string>> binding_checks_;
  std::vector<
      std::pair<std::function<bool(slinky::eval_context&)>, std::string>>
      checked_checks_;
  std::vector<std::pair<void*, size_t>> bound_;
  std::shared_ptr<Counters> counters_ = std::make_shared<Counters>();
  slinky::stmt pipeline_;
  slinky::stmt preflight_;
  slinky::eval_context shape_context_;
  bool failed_ = false, invoked_ = false;
  std::shared_ptr<ScratchStatistics> scratch_statistics_;
};
}  // namespace lab_ynn
