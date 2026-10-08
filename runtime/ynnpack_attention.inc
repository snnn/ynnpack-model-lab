// Copyright 2026 @snnn. Licensed under the Apache License, Version 2.0.
// Included inside lab_ynn::Graph. This is the ordered FP32 capability control;
// it is not a claim of competitive native GEMM/attention performance.
  void Sdpa(uint32_t query, uint32_t key, uint32_t value, uint32_t mask,
            uint32_t out, std::vector<int> head_map, float scale, int mask_kind,
            bool causal, int window, slinky::expr query_position,
            slinky::expr key_position, slinky::expr queries, slinky::expr keys,
            bool all_masked_nan) {
    const auto& q = graph_->value(query);
    const auto& k = graph_->value(key);
    const auto& v = graph_->value(value);
    if (q.type != ynn_type_fp32 || k.type != ynn_type_fp32 ||
        v.type != ynn_type_fp32 || q.rank() != 4 || k.rank() != 4 || v.rank() != 4)
      throw std::invalid_argument("SDPA requires FP32 BHSD operands");
    if (mask_kind < 0 || mask_kind > 2 ||
        ((mask_kind == 0) != (mask == YNN_INVALID_VALUE_ID)))
      throw std::invalid_argument("SDPA mask contract");
    auto& y = graph_->get_output_value(&out, q);
    y.extents = q.extents;
    y.extents[0] = v.extent(0);
    y.extents[1] = queries;
    ynn_node node;
    node.op = ynn_node::opaque{"core_whole_head_sdpa_ordered_fp32"};
    node.inputs = {query, key, value};
    if (mask_kind) node.inputs.push_back(mask);
    node.outputs = {out};
    node.create = [head_map = std::move(head_map), scale, mask_kind, causal,
                   window, query_position, key_position, queries, keys,
                   all_masked_nan](const ynn_node& node, ynn_runtime& runtime) {
      auto& y = runtime.value(node.outputs[0]);
      y.make_buffer(runtime, sizeof(float));
      auto dims = runtime.globals.make_dims(4);
      std::vector<slinky::func::input> inputs;
      for (auto id : node.inputs) {
        const auto& input = runtime.value(id);
        slinky::box_expr bounds;
        for (int d = 0; d < input.rank(); ++d)
          bounds.push_back(slinky::min_extent(0, input.extent(d)));
        inputs.push_back({input.buffer, std::move(bounds)});
      }
      slinky::call_stmt::attributes attrs;
      attrs.name = "core_whole_head_sdpa_ordered_fp32";
      auto callback = [head_map, scale, mask_kind, causal, window, all_masked_nan](
                          const slinky::call_stmt* call,
                          slinky::eval_context& context) -> slinky::index_t {
        const auto& q = context.lookup_buffer(call->inputs[0])->cast<const float>();
        const auto& k = context.lookup_buffer(call->inputs[1])->cast<const float>();
        const auto& v = context.lookup_buffer(call->inputs[2])->cast<const float>();
        const auto& y = context.lookup_buffer(call->outputs[0])->cast<float>();
        const auto qp = slinky::evaluate(call->scalars[0], context);
        const auto kp = slinky::evaluate(call->scalars[1], context);
        const auto qlen = slinky::evaluate(call->scalars[2], context);
        const auto klen = slinky::evaluate(call->scalars[3], context);
        const auto* mask = mask_kind ? context.lookup_buffer(call->inputs[3]) : nullptr;
        const float infinity = std::numeric_limits<float>::infinity();
        const float nan = std::numeric_limits<float>::quiet_NaN();
        if (qlen < 0 || klen < 0 || qlen > q.dim(1).extent() ||
            klen > k.dim(1).extent() || klen > v.dim(1).extent()) return 1;
        std::vector<float> scores(klen), probabilities(klen);
        for (int64_t batch = y.dim(3).min(); batch <= y.dim(3).max(); ++batch)
          for (int64_t head = y.dim(2).min(); head <= y.dim(2).max(); ++head)
            for (int64_t row = y.dim(1).min(); row <= y.dim(1).max(); ++row) {
              const int kv_head = head_map.at(head);
              bool has_nan = false, has_keys = false;
              float maximum = -infinity;
              for (int64_t j = 0; j < klen; ++j) {
                bool keep = !causal || (kp + j <= qp + row &&
                    (!window || qp + row - (kp + j) < window));
                float bias = 0;
                if (keep && mask) {
                  int64_t coordinate[4] = {j, row, head, batch};
                  ptrdiff_t offset = 0;
                  for (size_t d = 0; d < mask->rank; ++d)
                    offset += (mask->dims[d].extent() == 1 ? 0 : coordinate[d]) *
                              mask->dims[d].stride();
                  const auto* address = static_cast<const uint8_t*>(mask->base) + offset;
                  if (mask_kind == 1) keep = *address != 0;
                  else {
                    std::memcpy(&bias, address, sizeof(float));
                    keep = bias != -infinity;
                  }
                }
                float score = -infinity;
                if (keep) {
                  float dot = 0;
                  for (int64_t channel = 0; channel < q.dim(0).extent(); ++channel)
                    dot += q(channel, row, head, batch) * k(channel, j, kv_head, batch);
                  // Preserve the scaled-score rounding boundary before adding bias.
                  volatile float scaled = dot * scale;
                  score = scaled + bias;
                }
                scores[j] = score;
                has_nan |= std::isnan(score);
                has_keys |= score != -infinity;
                maximum = std::max(maximum, score);
              }
              float mass = 0;
              for (int64_t j = 0; j < klen; ++j) {
                probabilities[j] = scores[j] == -infinity ? 0 : std::exp(scores[j] - maximum);
                mass += probabilities[j];
              }
              if (has_nan) mass = nan;
              for (int64_t j = 0; j < klen; ++j)
                if (scores[j] != -infinity) probabilities[j] /= mass;
              for (int64_t channel = y.dim(0).min(); channel <= y.dim(0).max(); ++channel) {
                float result = !has_keys && all_masked_nan ? nan : 0;
                for (int64_t j = 0; j < klen; ++j)
                  if (scores[j] != -infinity)
                    result += probabilities[j] * v(channel, j, kv_head, batch);
                y(channel, row, head, batch) = result;
              }
            }
        return 0;
      };
      auto f = slinky::func(callback, std::move(inputs), {{y.buffer, dims}},
                            {query_position, key_position, queries, keys}, attrs);
      f.compute_root();
      y.buffer->store_root();
      runtime.funcs.push_back(std::move(f));
      return ynn_status_success;
    };
    graph_->add_node(std::move(node));
  }
