// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
#pragma once
#include "../runtime/ynnpack_support.h"
#ifdef LAB_STEP_DIAGNOSTICS
void RecurrentDiagnosticActive(bool);
#endif

// Experiment only: the generated builder is shared with lab_ynn::Graph.
// This wrapper admits only fixed shapes and no resource/parameter contracts.
// No validation bypass is added to the normal adapter.
class StepNative {
 public:
  // Optional experiment: recycle scratch between invocations. No tensor
  // contents are cached. Every live allocation has a distinct block; the
  // mutex permits allocations/frees from different scheduler workers.
  struct ScratchPool {
    struct Block {
      void* ptr;
      size_t size, alignment;
      bool live;
    };
    std::mutex mutex;
    std::vector<Block> blocks;
    std::function<void*(size_t, size_t)> allocate;
    std::function<void(void*, size_t)> release;
    ~ScratchPool() {
      for (const auto& b : blocks) release(b.ptr, b.size);
    }
    void* Get(size_t size, size_t alignment) {
      std::lock_guard<std::mutex> lock(mutex);
      for (auto& b : blocks)
        if (!b.live && b.size == size && b.alignment >= alignment) {
          b.live = true;
          return b.ptr;
        }
      void* ptr = allocate(size, alignment);
      if (ptr) blocks.push_back({ptr, size, alignment, true});
      return ptr;
    }
    void Put(void* ptr, size_t size) {
      std::lock_guard<std::mutex> lock(mutex);
      for (auto& b : blocks)
        if (b.ptr == ptr && b.live && b.size == size) {
          b.live = false;
          return;
        }
      throw std::runtime_error("scratch pool invalid release");
    }
  };
  explicit StepNative(size_t count, uint32_t flags) {
    lab_ynn::Check(ynn_create_subgraph(count, flags, &graph_));
  }
  ~StepNative() {
    if (statistics_)
      std::cerr << "scratch invocations=" << invocations_
                << " allocations=" << statistics_->allocations
                << " allocated_bytes=" << statistics_->allocated
                << " peak_live_bytes=" << statistics_->peak << "\n";
    if (runtime_) ynn_delete_runtime(runtime_);
    ynn_delete_subgraph(graph_);
  }
  void Tensor(uint32_t id, const std::string& name, ynn_type type,
              std::vector<size_t> dims, uint32_t flags, const void* data) {
    auto expected = id;
    lab_ynn::Check(ynn_define_tensor(graph_, type, dims.size(), dims.data(),
                                     data, flags, &id));
    if (id != expected) throw std::runtime_error("tensor ID changed");
    names_[name] = id;
    shapes_[id] = dims;
    bytes_[id] = sizeof(float);
    for (auto d : dims) bytes_[id] *= d;
  }
  void InputShape(uint32_t id, std::vector<slinky::expr> shape) {
    if (shape.size() != shapes_.at(id).size()) throw std::runtime_error("rank");
    for (size_t i = 0; i < shape.size(); ++i)
      if (!slinky::prove_true(shape[i] == shapes_.at(id)[i]))
        throw std::runtime_error("non-static or inconsistent shape");
  }
  void ResultShape(uint32_t id, std::vector<slinky::expr> shape) {
    InputShape(id, shape);
  }
  void BeginProfileOperation(const char*, const char*, std::vector<uint32_t>,
                             std::vector<uint32_t>, std::vector<std::string>) {}
  void EndProfileOperation() {}
  void ExpandDims(uint32_t in, uint32_t out, std::vector<int32_t> axes) {
    lab_ynn::Check(ynn_define_static_expand_dims(graph_, axes.size(),
                                                 axes.data(), in, &out, 0));
  }
  void SplitDim(uint32_t in, uint32_t out, int axis, std::vector<size_t> dims) {
    lab_ynn::Check(ynn_define_split_dim(graph_, axis, dims.size(), dims.data(),
                                        in, &out, 0));
  }
  void FuseDims(uint32_t in, uint32_t out, int axis, int count) {
    lab_ynn::Check(ynn_define_fuse_dim(graph_, axis, count, in, &out, 0));
  }
  void Reshape(uint32_t in, uint32_t out, std::vector<size_t> dims) {
    lab_ynn::Check(ynn_define_static_reshape(graph_, dims.size(), dims.data(),
                                             in, &out, 0));
  }
  void Binary(ynn_binary_operator op, uint32_t a, uint32_t b, uint32_t out) {
    lab_ynn::Check(ynn_define_binary(graph_, op, a, b, &out, 0));
  }
  void Unary(ynn_unary_operator op, uint32_t in, uint32_t out) {
    lab_ynn::Check(ynn_define_unary(graph_, op, in, &out, 0));
  }
  void Matmul(uint32_t a, uint32_t b, uint32_t out, bool adj_a, bool adj_b) {
    auto transpose = [&](uint32_t in) {
      const size_t rank = graph_->value(in).rank();
      std::vector<int32_t> axes(rank);
      std::iota(axes.begin(), axes.end(), 0);
      std::swap(axes[rank - 1], axes[rank - 2]);
      uint32_t value = YNN_INVALID_VALUE_ID;
      lab_ynn::Check(ynn_define_static_transpose(graph_, rank, axes.data(), in,
                                                 &value, 0));
      return value;
    };
    if (adj_a) a = transpose(a);
    if (adj_b) b = transpose(b);
    lab_ynn::Check(
        ynn_define_dot(graph_, 1, a, b, YNN_INVALID_VALUE_ID, &out, 0));
  }
  void Transpose(uint32_t in, uint32_t out, std::vector<int32_t> axes) {
    lab_ynn::Check(ynn_define_static_transpose(graph_, axes.size(), axes.data(),
                                               in, &out, 0));
  }
  void Reduce(ynn_reduce_operator op, uint32_t in, uint32_t out,
              std::vector<int32_t> axes, bool keep) {
    lab_ynn::Check(ynn_define_reduce(graph_, op, axes.size(), axes.data(), in,
                                     YNN_INVALID_VALUE_ID, &out,
                                     keep ? YNN_NODE_FLAG_KEEP_DIMS : 0));
  }
  void Copy(uint32_t in, uint32_t out) {
    lab_ynn::Check(ynn_define_copy(graph_, in, &out, 0));
  }
  void Slice(uint32_t in, uint32_t out, std::vector<int64_t> begins,
             std::vector<int64_t> sizes) {
    std::vector<int32_t> axes;
    std::vector<int64_t> starts, ends, strides;
    for (size_t i = 0; i < sizes.size(); ++i) {
      if (sizes[i] == -1 && begins[i] == 0) continue;
      if (sizes[i] <= 0) throw std::runtime_error("unexpected slice");
      axes.push_back(i);
      starts.push_back(begins[i]);
      ends.push_back(begins[i] + sizes[i]);
      strides.push_back(1);
    }
    lab_ynn::Check(ynn_define_static_slice(graph_, axes.size(), axes.data(),
                                           starts.data(), ends.data(),
                                           strides.data(), in, &out, 0));
  }
  void Concat(std::vector<uint32_t> ins, uint32_t out, int axis) {
    lab_ynn::Check(
        ynn_define_concatenate(graph_, axis, ins.size(), ins.data(), &out, 0));
  }
  void Compile(size_t threads) {
    lab_ynn::Check(ynn_optimize_subgraph(graph_, nullptr, 0));
    if (threads > 1)
      pool_ = std::make_unique<slinky::thread_pool_impl>(threads - 1);
    lab_ynn::Check(ynn_create_runtime(
        graph_, reinterpret_cast<ynn_threadpool_t>(pool_.get()), 0, &runtime_));
    if (std::getenv("STEP_SCRATCH_POOL")) {
      auto scratch = std::make_shared<ScratchPool>();
      scratch->allocate = runtime_->eval_config.allocate;
      scratch->release = runtime_->eval_config.free;
      runtime_->eval_config.allocate = [scratch](size_t n, size_t a) {
        return scratch->Get(n, a);
      };
      runtime_->eval_config.free = [scratch](void* p, size_t n) {
        scratch->Put(p, n);
      };
    }
#ifdef LAB_STEP_DIAGNOSTICS
    statistics_ = std::make_shared<lab_ynn::ScratchStatistics>();
    const auto stats = statistics_;
    const auto allocate = runtime_->eval_config.allocate;
    const auto release = runtime_->eval_config.free;
    runtime_->eval_config.allocate = [stats, allocate](size_t size,
                                                       size_t alignment) {
      void* p = allocate(size, alignment);
      if (p) {
        const size_t live = stats->live.fetch_add(size) + size;
        size_t peak = stats->peak.load();
        while (peak < live && !stats->peak.compare_exchange_weak(peak, live)) {
        }
        stats->allocated.fetch_add(size);
        stats->allocations.fetch_add(1);
      }
      return p;
    };
    runtime_->eval_config.free = [stats, release](void* p, size_t size) {
      stats->live.fetch_sub(size);
      release(p, size);
    };
#endif
  }
  void Bind(const std::string& name, void* ptr, size_t bytes) {
    const auto id = names_.at(name);
    if (!ptr || bytes < bytes_.at(id))
      throw std::runtime_error("invalid binding");
    lab_ynn::Check(ynn_set_external_value_data(runtime_, id, ptr));
  }
  class Trace : public slinky::stmt_mutator {
   public:
    void visit(const slinky::call_stmt* op) override {
      auto target = op->target;
      auto attrs = *op->attrs;
      auto name = attrs.name;
      set_result(slinky::call_stmt::make(
          [target, name](const slinky::call_stmt* call,
                         slinky::eval_context& ctx) {
            std::cerr << "CALL " << name << "\n";
            for (auto id : call->inputs) {
              auto* p = ctx.lookup_buffer(id);
              std::cerr << " base " << p->base << " rank " << p->rank;
              for (size_t d = 0; d < p->rank; ++d)
                std::cerr << " [" << p->dim(d).min() << "," << p->dim(d).max()
                          << "," << p->dim(d).stride() << "]";
              std::cerr << "\n";
            }
            return target(call, ctx);
          },
          op->inputs, op->outputs,
          std::vector<slinky::expr>(op->scalars.begin(), op->scalars.end()),
          attrs));
    }
  };
  void Run() {
    if (!ready_) {
      lab_ynn::Check(ynn_reshape_runtime(runtime_));
      lab_ynn::Check(runtime_->setup());
      if (std::getenv("STEP_TRACE")) {
        Trace t;
        runtime_->pipeline.body = t.mutate(runtime_->pipeline.body);
      }
      ready_ = true;
    }
#ifdef LAB_STEP_DIAGNOSTICS
    ++invocations_;
    RecurrentDiagnosticActive(true);
#endif
    lab_ynn::Check(ynn_invoke_runtime(runtime_));
#ifdef LAB_STEP_DIAGNOSTICS
    RecurrentDiagnosticActive(false);
#endif
  }
  void Print(std::ostream& out) const {
    slinky::print(out, runtime_->pipeline.body, &runtime_->globals.symbols);
  }

 private:
  ynn_subgraph_t graph_ = nullptr;
  std::unique_ptr<slinky::thread_pool_impl> pool_;
  ynn_runtime_t runtime_ = nullptr;
  std::map<std::string, uint32_t> names_;
  std::map<uint32_t, std::vector<size_t>> shapes_;
  std::map<uint32_t, size_t> bytes_;
  bool ready_ = false;
  size_t invocations_ = 0;
  std::shared_ptr<lab_ynn::ScratchStatistics> statistics_;
};
