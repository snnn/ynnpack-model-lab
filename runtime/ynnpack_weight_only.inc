// Copyright 2026 @snnn. Licensed under the Apache License, Version 2.0.
// Included inside lab_ynn::Graph. Target-owned capability implementation:
// packed constant codes -> bounded FP32 tiles -> native YNNPACK FP32 GEMM.
// This preserves FP32 activations; it is not the hybrid INT8 FC algorithm.
  struct WeightOnlyStatistics {
    std::atomic<size_t> calls{0}, native_dot_calls{0};
    std::atomic<size_t> worker_scratch_bytes{0};
  };
  std::shared_ptr<WeightOnlyStatistics> weight_only_statistics_ =
      std::make_shared<WeightOnlyStatistics>();
  const WeightOnlyStatistics& weight_only_statistics() const {
    return *weight_only_statistics_;
  }

  void WeightOnlyLinear(uint32_t input, uint32_t weight, uint32_t scales,
                        uint32_t zero, uint32_t out, int64_t group) {
    const auto& x = graph_->value(input);
    const auto& w = graph_->value(weight);
    const auto& s = graph_->value(scales);
    const auto& z = graph_->value(zero);
    const bool packed = packed_.count(weight);
    const int bits = packed ? packed_.at(weight).bits : 8;
    const auto shape = LogicalShape(weight);
    if (x.type != ynn_type_fp32 || x.rank() != 2 || shape.size() != 2 ||
        (!packed && (w.type != ynn_type_int8 || w.rank() != 2)) ||
        s.type != ynn_type_fp32 || s.rank() != 2 ||
        z.type != ynn_type_int32 || z.rank() != 2 || group <= 0 ||
        !w.is_static() || !s.is_static() || !z.is_static())
      throw std::invalid_argument("weight-only linear requires FP32 rows and constant signed codes/scales/zero");
    auto& y = graph_->get_output_value(&out, x);
    y.extents = {shape[0], x.extent(1)};
    ynn_node node;
    node.op = ynn_node::opaque{"core_weight_only_linear_tiled_fp32"};
    node.inputs = {input, weight, scales, zero};
    node.outputs = {out};
    node.create = [bits, packed, group, shape, statistics = weight_only_statistics_](
                      const ynn_node& node, ynn_runtime& runtime) {
      auto& y = runtime.value(node.outputs[0]);
      y.make_buffer(runtime, sizeof(float));
      auto dims = runtime.globals.make_dims(2);
      std::vector<slinky::func::input> sources;
      for (auto id : node.inputs) {
        const auto& value = runtime.value(id);
        slinky::box_expr bounds;
        for (int d = 0; d < value.rank(); ++d)
          bounds.push_back(slinky::min_extent(0, value.extent(d)));
        sources.push_back({value.buffer, std::move(bounds)});
      }
      slinky::call_stmt::attributes attrs;
      attrs.name = "core_weight_only_linear_tiled_fp32";
      auto callback = [bits, packed, group, statistics](
                          const slinky::call_stmt* call,
                          slinky::eval_context& context) -> slinky::index_t {
        const auto& x = context.lookup_buffer(call->inputs[0])->cast<const float>();
        const auto* w = context.lookup_buffer(call->inputs[1]);
        const auto& scales = context.lookup_buffer(call->inputs[2])->cast<const float>();
        const auto& zero = context.lookup_buffer(call->inputs[3])->cast<const int32_t>();
        const auto& y = context.lookup_buffer(call->outputs[0])->cast<float>();
        const int64_t n = slinky::evaluate(call->scalars[0], context);
        const int64_t k = slinky::evaluate(call->scalars[1], context);
        const int64_t groups = k / group + (k % group != 0);
        if (n <= 0 || k <= 0 || n > std::numeric_limits<int64_t>::max() / k ||
            x.dim(0).min() != 0 || x.dim(0).extent() != k ||
            y.dim(0).min() != 0 || y.dim(0).extent() != n ||
            y.dim(1).min() != x.dim(1).min() || y.dim(1).extent() != x.dim(1).extent() ||
            scales.dim(0).min() != 0 || scales.dim(1).min() != 0 ||
            scales.dim(0).extent() != groups || scales.dim(1).extent() != n ||
            zero.dim(0).extent() != 1 || zero.dim(1).extent() != 1 || zero(0, 0) != 0)
          return 1;
        if (packed) {
          const int64_t count = n * k;
          if (w->rank != 1 || w->dims[0].min() != 0 || w->dims[0].stride() != 1 ||
              w->dims[0].extent() != count / (8 / bits) + (count % (8 / bits) != 0)) return 1;
        } else if (w->rank != 2 || w->dims[0].extent() != k || w->dims[1].extent() != n) {
          return 1;
        }
        for (int64_t channel = 0; channel < n; ++channel)
          for (int64_t g = 0; g < groups; ++g)
            if (!std::isfinite(scales(g, channel)) || scales(g, channel) <= 0) return 1;
        if (y.dim(1).empty()) return 0;
        constexpr size_t kRows = 8, kChannels = 64, kReduction = 128;
        const size_t rows = y.dim(1).extent();
        const auto kernel = ynn::get_dot_kernel(
            {ynn_type_fp32, ynn_type_fp32, ynn_type_fp32},
#if __has_include("ynnpack/kernels/dot/cost_model/cost_model.h")
            // The learned-cost-model API adds this argument. Older backend
            // pins select kernels directly from the shape and packing contract.
            ynn::get_dot_cost_models(),
#endif
            {std::min(rows, kRows), std::min(size_t(n), kChannels), kReduction, 1, 1},
            // The shared contract permits both FMA and ordinary FP32 kernels.
            // Restrict packing to tile_k=1, not the available CPU ISA.
            {0, 1}, 0, false);
        if (!kernel.kernel || kernel.tile_k != 1 || kernel.tile_m != 1 ||
            kernel.block_m <= 0 || kernel.tile_n <= 0 || kChannels % kernel.tile_n)
          throw std::runtime_error("YNNPACK has no compatible FP32 tile kernel");
        const size_t block_m = std::min(kRows, size_t(kernel.block_m));
        auto work = [&](size_t task) {
          // Fixed, aligned scratch per worker. No full decoded weight matrix
          // or unquantized persistent weight cache is ever allocated.
          alignas(64) float b_tile[kReduction * kChannels];
          alignas(64) float a_tile[kRows * kReduction];
          alignas(64) float c_tile[kRows * kChannels];
          ynn::dot_kernel_state state;
          size_t dot_calls = 0;
          statistics->worker_scratch_bytes.store(sizeof(b_tile) + sizeof(a_tile) + sizeof(c_tile),
                                                  std::memory_order_relaxed);
          const int64_t first_n = task * kChannels;
          const size_t width = std::min(int64_t(kChannels), n - first_n);
          for (int64_t first_k = 0; first_k < k; first_k += kReduction) {
            const size_t reduction = std::min(int64_t(kReduction), k - first_k);
            std::fill_n(b_tile, reduction * kChannels, 0.0f);
            for (size_t c = 0; c < width; ++c)
              for (size_t r = 0; r < reduction; ++r) {
                const int64_t channel = first_n + c, index = first_k + r;
                int code;
                if (packed) {
                  const int64_t flat = channel * k + index;
                  const int raw = w->cast<const uint8_t>()(flat / (8 / bits));
                  code = (raw >> ((flat % (8 / bits)) * bits)) & ((1 << bits) - 1);
                  if (code & (1 << (bits - 1))) code -= 1 << bits;
                } else {
                  code = w->cast<const int8_t>()(index, channel);
                }
                b_tile[r * kChannels + c] = float(code) * scales(index / group, channel);
              }
            // Decode each B tile once and reuse it for all activation rows.
            for (size_t first_m = 0; first_m < rows; first_m += block_m) {
              const size_t height = std::min(block_m, rows - first_m);
              for (size_t m = 0; m < height; ++m) {
                const int64_t row = y.dim(1).min() + first_m + m;
                for (size_t r = 0; r < reduction; ++r)
                  a_tile[m * kReduction + r] = x(first_k + r, row);
                if (first_k)
                  for (size_t c = 0; c < width; ++c)
                    c_tile[m * kChannels + c] = y(first_n + c, row);
                std::fill(c_tile + m * kChannels + (first_k ? width : 0),
                          c_tile + (m + 1) * kChannels, 0.0f);
              }
              kernel.kernel(height, width, 1, 1, reduction,
                  kReduction * sizeof(float), 0, 0, a_tile,
                  0, 0, kChannels * sizeof(float), b_tile,
                  kChannels * sizeof(float), first_k ? c_tile : nullptr,
                  kChannels * sizeof(float), c_tile, &state);
              ++dot_calls;
              for (size_t m = 0; m < height; ++m)
                for (size_t c = 0; c < width; ++c)
                  y(first_n + c, y.dim(1).min() + first_m + m) = c_tile[m * kChannels + c];
            }
          }
          statistics->native_dot_calls.fetch_add(dot_calls, std::memory_order_relaxed);
        };
        statistics->calls.fetch_add(1, std::memory_order_relaxed);
        const size_t tasks = n / kChannels + (n % kChannels != 0);
        if (context.config && context.config->thread_pool && tasks > 1)
          context.config->thread_pool->parallel_for(tasks, work);
        else
          for (size_t task = 0; task < tasks; ++task) work(task);
        return 0;
      };
      auto f = slinky::func(callback, std::move(sources), {{y.buffer, dims}}, shape, attrs);
      f.compute_root();
      y.buffer->store_root();
      runtime.funcs.push_back(std::move(f));
      return ynn_status_success;
    };
    graph_->add_node(std::move(node));
  }
