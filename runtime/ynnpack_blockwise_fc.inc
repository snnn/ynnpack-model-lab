// Copyright 2026 @snnn. Licensed under the Apache License, Version 2.0.
// Included inside lab_ynn::Graph. Per-row asymmetric A8, group-32 W4.
// Packed weights stay packed; only a bounded tile is expanded for native dots.
  void BlockwiseFullyConnected(uint32_t input, uint32_t weight, uint32_t scales,
                               uint32_t zero, uint32_t out, int64_t group,
                               uint64_t dot_arch_flags = UINT64_MAX) {
    // Permit restricted-ISA experiments, never instructions unsupported here.
    dot_arch_flags &= ynn::get_supported_arch_flags();
    weight = ConstantSource(weight);
    scales = ConstantSource(scales);
    zero = ConstantSource(zero);
    const auto& x = graph_->value(input);
    const auto& w = graph_->value(weight);
    const auto& s = graph_->value(scales);
    const auto& z = graph_->value(zero);
    const auto shape = LogicalShape(weight);
    if (group != 32 || x.type != ynn_type_fp32 || x.rank() != 2 ||
        !packed_.count(weight) || packed_.at(weight).bits != 4 ||
        shape.size() != 2 ||
        s.type != ynn_type_fp32 || s.rank() != 2 ||
        z.type != ynn_type_int32 || z.rank() != 2 ||
        !w.is_static() || !s.is_static() || !z.is_static())
      throw std::invalid_argument("grouped hybrid FC requires FP32 rows and constant group-32 W4");
    auto& y = graph_->get_output_value(&out, x);
    y.extents = {shape[0], x.extent(1)};
    ynn_node node;
    node.op = ynn_node::opaque{"blockwise_fc_a8_w4_native_dot"};
    node.inputs = {input, weight, scales, zero};
    node.outputs = {out};
    node.create = [shape, dot_arch_flags](const ynn_node& node, ynn_runtime& runtime) {
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
      attrs.name = "blockwise_fc_a8_w4_native_dot";
      auto callback = [dot_arch_flags](const slinky::call_stmt* call,
                         slinky::eval_context& context) -> slinky::index_t {
        const auto& x = context.lookup_buffer(call->inputs[0])->cast<const float>();
        const auto& w = context.lookup_buffer(call->inputs[1])->cast<const uint8_t>();
        const auto& scales = context.lookup_buffer(call->inputs[2])->cast<const float>();
        const auto& zero = context.lookup_buffer(call->inputs[3])->cast<const int32_t>();
        const auto& y = context.lookup_buffer(call->outputs[0])->cast<float>();
        const size_t n = slinky::evaluate(call->scalars[0], context);
        const size_t k = slinky::evaluate(call->scalars[1], context);
        const size_t rows = slinky::evaluate(call->scalars[2], context);
        constexpr size_t reduction = detail::BlockwiseDot::kReduction;
        constexpr size_t channels = detail::BlockwiseDot::kChannels;
        constexpr size_t max_rows = detail::BlockwiseDot::kRows;
        if (!n || !k || k % 32 || x.dim(0).extent() != k || y.dim(0).extent() != n ||
            w.dim(0).extent() != n * k / 2 || w.dim(0).stride() != 1 || w.dim(0).min() != 0 ||
            scales.dim(0).extent() != k / 32 ||
            scales.dim(1).extent() != n || zero(0, 0) != 0) return 1;
        if (!rows) return 0;
        const auto dot = detail::SelectBlockwiseDot(rows, n, dot_arch_flags);
        const auto& kernel = dot.kernel;
        const size_t tile_k = kernel.tile_k;
        const uint8_t* packed_codes = &w(0);
        // Activation storage is proportional to the input, never the weights.
        std::vector<uint8_t> a(rows * k);
        std::vector<float> a_scale(rows);
        std::vector<int32_t> a_zero(rows);
        for (size_t m = 0; m < rows; ++m) {
          float lo = 0, hi = 0;
          for (size_t r = 0; r < k; ++r) {
            const float v = x(r, m);
            if (!std::isfinite(v)) return 1;
            lo = std::min(lo, v); hi = std::max(hi, v);
          }
          const float range = hi - lo;
          a_scale[m] = range == 0 ? 1.0f : range / 255.0f;
          const float inverse = range == 0 ? 1.0f : 255.0f / range;
          a_zero[m] = int32_t(std::clamp(-lo * inverse, 0.0f, 255.0f) + 0.5f);
          const float quant_inverse = 1.0f / a_scale[m];
          for (size_t r = 0; r < k; ++r)
            a[m * k + r] = uint8_t(int32_t(std::clamp(
                std::nearbyint(x(r, m) * quant_inverse) + float(a_zero[m]), 0.0f, 255.0f)) -
                dot.activation_shift);
          a_zero[m] -= dot.activation_shift;
        }
        const size_t block_m = std::min(max_rows, size_t(kernel.block_m));
        auto work = [&](size_t task) {
          alignas(64) int8_t b_tile[reduction * channels];
          alignas(64) int32_t sums[channels], c_tile[max_rows * channels];
          ynn::dot_kernel_state state;
          const size_t first_n = task * channels;
          const size_t width = std::min(channels, n - first_n);
          for (size_t g = 0; g < k / reduction; ++g) {
            std::fill_n(b_tile, reduction * channels, 0);
            std::fill_n(sums, channels, 0);
            for (size_t c = 0; c < width; ++c) {
              const float s = scales(g, first_n + c);
              if (!std::isfinite(s) || s <= 0)
                throw std::runtime_error("Invalid grouped weight scale");
              for (size_t r = 0; r < reduction; r += 8) {
                const size_t index = (first_n + c) * k + g * reduction + r;
                // Spread eight little-endian nibbles into byte lanes, then
                // sign-extend each lane. No full decoded matrix is retained.
                const auto* source = packed_codes + index / 2;
                uint64_t codes = uint64_t(source[0]) | (uint64_t(source[1]) << 8) |
                                 (uint64_t(source[2]) << 16) | (uint64_t(source[3]) << 24);
                codes = (codes | (codes << 16)) & UINT64_C(0x0000ffff0000ffff);
                codes = (codes | (codes << 8)) & UINT64_C(0x00ff00ff00ff00ff);
                codes = (codes | (codes << 4)) & UINT64_C(0x0f0f0f0f0f0f0f0f);
                const uint64_t signs = codes & UINT64_C(0x0808080808080808);
                constexpr uint64_t sum_lanes = UINT64_C(0x0101010101010101);
                sums[c] += int((codes * sum_lanes) >> 56) - 16 * int(((signs >> 3) * sum_lanes) >> 56);
                codes |= signs * 30;
                // Pack the K interleave required by the selected kernel.
                for (size_t j = 0; j < 8; ++j) {
                  const size_t offset = tile_k == 4
                      ? ((r + j) / 4) * channels * 4 + c * 4 + j % 4
                      : (r + j) * channels + c;
                  b_tile[offset] = int8_t(uint8_t(codes >> (8 * j)));
                }
              }
            }
            for (size_t first_m = 0; first_m < rows; first_m += block_m) {
              const size_t height = std::min(block_m, rows - first_m);
              // B's reduction stride is per logical K element. The kernel
              // multiplies it by tile_k to advance one packed K tile.
              kernel.kernel(height, width, 1, 1, reduction,
                  k, 0, 0, a.data() + first_m * k + g * reduction,
                  0, 0, channels, b_tile, channels * sizeof(int32_t), nullptr,
                  channels * sizeof(int32_t), c_tile, &state);
              for (size_t m = 0; m < height; ++m)
                for (size_t c = 0; c < width; ++c) {
                  const int32_t acc = c_tile[m * channels + c] - a_zero[first_m + m] * sums[c];
                  const float result = float(acc) * (a_scale[first_m + m] * scales(g, first_n + c));
                  y(first_n + c, first_m + m) = result + (g ? y(first_n + c, first_m + m) : 0.0f);
                }
            }
          }
        };
        const size_t tasks = (n + channels - 1) / channels;
        if (context.config && context.config->thread_pool && tasks > 1)
          context.config->thread_pool->parallel_for(tasks, work);
        else
          for (size_t task = 0; task < tasks; ++task) work(task);
        return 0;
      };
      std::vector<slinky::expr> sizes{shape[0], shape[1], runtime.value(node.inputs[0]).extent(1)};
      auto f = slinky::func(callback, std::move(sources), {{y.buffer, dims}}, sizes, attrs);
      f.compute_root();
      y.buffer->store_root();
      runtime.funcs.push_back(std::move(f));
      return ynn_status_success;
    };
    graph_->add_node(std::move(node));
  }
