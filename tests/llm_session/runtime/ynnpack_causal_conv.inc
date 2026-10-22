// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
// Included inside Graph. Replacement history is distinct from input history.
// Kernel taps use ordered FP32 FMA; SiLU, when requested, follows convolution.
void CausalDepthwiseConv(uint32_t input, uint32_t filter, uint32_t history,
                         uint32_t out, uint32_t next, slinky::expr valid,
                         bool silu) {
  const auto& x = graph_->value(input);
  const auto& h = graph_->value(history);
  const auto& w = graph_->value(filter);
  if (x.rank() != 3 || h.rank() != 3 || w.rank() != 4 ||
      x.type != ynn_type_fp32 || h.type != ynn_type_fp32 ||
      w.type != ynn_type_fp32)
    throw std::invalid_argument(
        "causal convolution requires FP32 BTC/history/filter");
  graph_->get_output_value(&out, x).extents = {x.extent(0), 1, x.extent(1),
                                               x.extent(2)};
  graph_->get_output_value(&next, h).extents = h.extents;
  const std::vector<slinky::expr> geometry = {x.extent(0), x.extent(1),
                                              x.extent(2), w.extent(2), valid};
  ynn_node node;
  node.op = ynn_node::opaque{"causal_depthwise_conv"};
  node.inputs = {input, filter, history};
  node.outputs = {out, next};
  node.create = [geometry, silu](const ynn_node& node, ynn_runtime& runtime) {
    std::vector<slinky::func::input> sources;
    for (auto id : node.inputs) {
      auto& value = runtime.value(id);
      slinky::box_expr bounds;
      for (int d = 0; d < value.rank(); ++d)
        bounds.push_back(slinky::min_extent(0, value.extent(d)));
      sources.push_back({value.buffer, std::move(bounds)});
    }
    auto& y = runtime.value(node.outputs[0]);
    auto& h = runtime.value(node.outputs[1]);
    y.make_buffer(runtime, 4);
    h.make_buffer(runtime, 4);
    slinky::call_stmt::attributes attrs;
    attrs.name = "causal_depthwise_conv";
    auto callback = [silu](const slinky::call_stmt* call,
                           slinky::eval_context& ctx) -> slinky::index_t {
      const int64_t C = slinky::evaluate(call->scalars[0], ctx),
                    T = slinky::evaluate(call->scalars[1], ctx),
                    B = slinky::evaluate(call->scalars[2], ctx),
                    K = slinky::evaluate(call->scalars[3], ctx),
                    valid = slinky::evaluate(call->scalars[4], ctx);
      if (C <= 0 || T <= 0 || B <= 0 || K < 2 || valid < 0 || valid > T)
        throw std::runtime_error("causal convolution geometry/valid_rows");
      const auto& x = ctx.lookup_buffer(call->inputs[0])->cast<const float>();
      const auto& w = ctx.lookup_buffer(call->inputs[1])->cast<const float>();
      const auto& prev =
          ctx.lookup_buffer(call->inputs[2])->cast<const float>();
      const auto& y = ctx.lookup_buffer(call->outputs[0])->cast<float>();
      const auto& next = ctx.lookup_buffer(call->outputs[1])->cast<float>();
      const auto validate = [](const auto& buf,
                               std::initializer_list<int64_t> dims) {
        if (buf.rank > dims.size())
          throw std::runtime_error("causal convolution runtime rank");
        int d = 0;
        for (auto extent : dims) {
          if (!buf.dim_is_broadcast(d) &&
              (buf.dim(d).min() != 0 || buf.dim(d).extent() != extent))
            throw std::runtime_error("causal convolution runtime shape");
          if (!buf.dim_is_broadcast(d) && buf.dim(d).is_folded())
            throw std::runtime_error("causal convolution folded buffer");
          ++d;
        }
      };
      validate(x, {C, T, B});
      validate(w, {C, 1, K, 1});
      validate(prev, {C, K - 1, B});
      validate(y, {C, 1, T, B});
      validate(next, {C, K - 1, B});
      const auto stride = [](const auto& z, int d) -> int64_t {
        return z.dim_is_broadcast(d) ? 0 : z.dim(d).stride() / sizeof(float);
      };
      const int64_t tiles = (C + 255) / 256;
      auto work = [&](size_t task) {
        const int64_t batch = task / tiles, begin = (task % tiles) * 256;
        CausalConvCpuArgs args{
            {&x(0, 0, batch), stride(x, 1), stride(x, 0)},
            {&prev(0, 0, batch), stride(prev, 1), stride(prev, 0)},
            {&w(0, 0, 0, 0), stride(w, 2), stride(w, 0)},
            {&y(0, 0, 0, batch), stride(y, 2), stride(y, 0)},
            {&next(0, 0, batch), stride(next, 1), stride(next, 0)},
            T,
            valid,
            K,
            silu};
        CausalConvCpuTile(args, begin, std::min(begin + 256, C));
      };
      if (ctx.config && ctx.config->thread_pool)
        ctx.config->thread_pool->parallel_for(B * tiles, work);
      else
        for (int64_t i = 0; i < B * tiles; ++i) work(i);
      return 0;
    };
    auto f = slinky::func(callback, std::move(sources),
                          {{y.buffer, runtime.globals.make_dims(4)},
                           {h.buffer, runtime.globals.make_dims(3)}},
                          geometry, attrs);
    f.compute_root();
    y.buffer->store_root();
    h.buffer->store_root();
    runtime.funcs.push_back(std::move(f));
    return ynn_status_success;
  };
  graph_->add_node(std::move(node));
}
