// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
// Required adapter runtime operation, not an upstream YNNPACK primitive or
// a composite with a fallback body. The scheduled kernel below executes.
// Included inside Graph. Pure recurrence: state input and output never alias.
void GatedDeltaRule(uint32_t q, uint32_t k, uint32_t v, uint32_t decay,
                    uint32_t beta, uint32_t state, uint32_t valid, uint32_t out,
                    uint32_t next, const std::vector<int64_t>& heads,
                    double scale) {
  const auto &qs = graph_->value(q), &vs = graph_->value(v);
  if (qs.rank() != 4 || vs.rank() != 4 || graph_->value(state).rank() != 4 ||
      graph_->value(valid).rank() != 0 ||
      graph_->value(valid).type != ynn_type_int32 || !std::isfinite(scale) ||
      scale <= 0 || heads.empty())
    throw std::invalid_argument("invalid gated delta contract");
  for (auto id : {q, k, v, decay, beta, state})
    if (graph_->value(id).type != ynn_type_fp32)
      throw std::invalid_argument("gated delta requires FP32 inputs");
  graph_->get_output_value(&out, vs).extents = vs.extents;
  graph_->get_output_value(&next, graph_->value(state)).extents =
      graph_->value(state).extents;
  const std::vector<slinky::expr> geometry = {qs.extent(0), qs.extent(1),
                                              qs.extent(2), qs.extent(3),
                                              vs.extent(0), vs.extent(1)};
  ynn_node node;
  node.op = ynn_node::opaque{"gated_delta_rule"};
  node.inputs = {q, k, v, decay, beta, state, valid};
  node.outputs = {out, next};
  node.create = [heads, scale, geometry](const ynn_node& node,
                                         ynn_runtime& runtime) {
    std::vector<slinky::func::input> sources;
    for (auto id : node.inputs) {
      const auto& value = runtime.value(id);
      slinky::box_expr bounds;
      for (int d = 0; d < value.rank(); ++d)
        bounds.push_back(slinky::min_extent(0, value.extent(d)));
      sources.push_back({value.buffer, std::move(bounds)});
    }
    auto &y = runtime.value(node.outputs[0]),
         &s = runtime.value(node.outputs[1]);
    y.make_buffer(runtime, sizeof(float));
    s.make_buffer(runtime, sizeof(float));
    slinky::call_stmt::attributes attrs;
    attrs.name = "gated_delta_rule";
    auto callback = [heads, scale](
                        const slinky::call_stmt* call,
                        slinky::eval_context& context) -> slinky::index_t {
      // Check every runtime extent before indexing, including malformed public
      // plans that supplied a conflicting InputShape declaration.
      const int64_t D = slinky::evaluate(call->scalars[0], context),
                    H = slinky::evaluate(call->scalars[1], context),
                    T = slinky::evaluate(call->scalars[2], context),
                    B = slinky::evaluate(call->scalars[3], context),
                    V = slinky::evaluate(call->scalars[4], context),
                    N = slinky::evaluate(call->scalars[5], context);
      const std::vector<std::vector<int64_t>> shapes = {{D, H, T, B},
                                                        {D, H, T, B},
                                                        {V, N, T, B},
                                                        {N, T, B},
                                                        {N, T, B},
                                                        {V, D, N, B},
                                                        {}};
      for (size_t i = 0; i < shapes.size(); ++i) {
        const auto* buffer = context.lookup_buffer(call->inputs[i]);
        if (buffer->rank > shapes[i].size())
          throw std::runtime_error("gated delta runtime input rank " +
                                   std::to_string(i));
        for (size_t d = 0; d < shapes[i].size(); ++d)
          if (shapes[i][d] <= 0 || (!buffer->dim_is_broadcast(d) &&
                                    (buffer->dim(d).min() != 0 ||
                                     buffer->dim(d).extent() != shapes[i][d])))
            throw std::runtime_error(
                "gated delta runtime input " + std::to_string(i) + " axis " +
                std::to_string(d) +
                " min=" + std::to_string(buffer->dim(d).min()) +
                " extent=" + std::to_string(buffer->dim(d).extent()) +
                " expected=" + std::to_string(shapes[i][d]));
      }
      const auto& q =
          context.lookup_buffer(call->inputs[0])->cast<const float>();
      const auto& k =
          context.lookup_buffer(call->inputs[1])->cast<const float>();
      const auto& v =
          context.lookup_buffer(call->inputs[2])->cast<const float>();
      const auto& g =
          context.lookup_buffer(call->inputs[3])->cast<const float>();
      const auto& beta =
          context.lookup_buffer(call->inputs[4])->cast<const float>();
      const auto& initial =
          context.lookup_buffer(call->inputs[5])->cast<const float>();
      const auto& valid =
          context.lookup_buffer(call->inputs[6])->cast<const int32_t>();
      const auto& y = context.lookup_buffer(call->outputs[0])->cast<float>();
      const auto& final =
          context.lookup_buffer(call->outputs[1])->cast<float>();
      const int64_t dk = D, hk = H, t = T, b = B, dv = V, hv = N, n = valid();
      if (n < 0 || n > t || heads.size() != size_t(hv))
        throw std::runtime_error("gated delta runtime valid_rows: " +
                                 std::to_string(n));
      for (auto h : heads)
        if (h < 0 || h >= hk)
          throw std::runtime_error("gated delta runtime head map");
      bool unfolded = true;
      for (auto id : call->inputs) {
        const auto* input = context.lookup_buffer(id);
        for (int d = 0; d < input->rank; ++d)
          unfolded &= (input->dim(d).stride() == 0 || input->dim(d).fold_factor() == slinky::dim::unfolded);
      }
      for (auto id : call->outputs) {
        const auto* output = context.lookup_buffer(id);
        for (int d = 0; d < output->rank; ++d)
          unfolded &= (output->dim(d).stride() == 0 || output->dim(d).fold_factor() == slinky::dim::unfolded);
      }
      if (unfolded) {
        const auto stride = [](const auto& value, int axis) -> int64_t {
          return value.dim_is_broadcast(axis) ? 0 : value.dim(axis).stride() / sizeof(float);
        };
        const int64_t width = 128;
        const int64_t tiles = (dv + width - 1) / width;
        auto tile = [&](size_t task) {
          const int64_t j = (task % tiles) * width;
          const int64_t h = (task / tiles) % hv, batch = task / (tiles * hv), kh = heads[h];
          GatedDeltaCpuArgs args{
            {&q(0,kh,0,batch),stride(q,2),stride(q,0)},
            {&k(0,kh,0,batch),stride(k,2),stride(k,0)},
            {&v(0,h,0,batch),stride(v,2),stride(v,0)},
            {&initial(0,0,h,batch),stride(initial,1),stride(initial,0)},
            {&y(0,h,0,batch),stride(y,2),stride(y,0)},
            {&final(0,0,h,batch),stride(final,1),stride(final,0)},
            &g(h,0,batch),&beta(h,0,batch),stride(g,1),stride(beta,1),dk,t,n,float(scale)};
          GatedDeltaCpuTile(args,j,std::min(j+width,dv));
        };
        if (context.config && context.config->thread_pool)
          context.config->thread_pool->parallel_for(b * hv * tiles, tile);
        else
          for (int64_t task = 0; task < b * hv * tiles; ++task) tile(task);
      } else {
      auto work = [&](size_t task) {
        const int64_t batch = task / hv, h = task % hv, kh = heads[h];
        std::vector<float> s(dk * dv), delta(dv), result(dv), query(dk);
        for (int64_t i = 0; i < dk; ++i)
          for (int64_t j = 0; j < dv; ++j)
            s[i * dv + j] = initial(j, i, h, batch);
        for (int64_t row = 0; row < t; ++row) {
          std::fill(result.begin(), result.end(), 0.0f);
          if (row < n) {
            const float decay = std::exp(g(h, row, batch));
            for (auto& x : s) x *= decay;
            std::fill(delta.begin(), delta.end(), 0.0f);
            for (int64_t i = 0; i < dk; ++i) {
              const float key = k(i, kh, row, batch);
              query[i] = q(i, kh, row, batch) * float(scale);
              for (int64_t j = 0; j < dv; ++j) delta[j] += s[i * dv + j] * key;
            }
            for (int64_t j = 0; j < dv; ++j)
              delta[j] = (v(j, h, row, batch) - delta[j]) * beta(h, row, batch);
            for (int64_t i = 0; i < dk; ++i) {
              const float key = k(i, kh, row, batch);
              for (int64_t j = 0; j < dv; ++j) {
                s[i * dv + j] += key * delta[j];
                result[j] += s[i * dv + j] * query[i];
              }
            }
          }
          for (int64_t j = 0; j < dv; ++j) y(j, h, row, batch) = result[j];
        }
        for (int64_t i = 0; i < dk; ++i)
          for (int64_t j = 0; j < dv; ++j)
            final(j, i, h, batch) = s[i * dv + j];
      };
      if (context.config && context.config->thread_pool)
        context.config->thread_pool->parallel_for(b * hv, work);
      else
        for (int64_t i = 0; i < b * hv; ++i) work(i);
      }
      return 0;
    };
    auto f = slinky::func(callback, std::move(sources),
                          {{y.buffer, runtime.globals.make_dims(4)},
                           {s.buffer, runtime.globals.make_dims(4)}},
                          geometry, attrs);
    f.compute_root();
    y.buffer->store_root();
    s.buffer->store_root();
    runtime.funcs.push_back(std::move(f));
    return ynn_status_success;
  };
  graph_->add_node(std::move(node));
}
