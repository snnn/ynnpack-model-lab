// Copyright 2026 @snnn. Licensed under the Apache License, Version 2.0.
// Included inside lab_ynn::Graph. Per-row asymmetric A8, group-32 W4.
// Packed weights stay packed; only a bounded tile is expanded for native dots.
  void BlockwiseFullyConnected(uint32_t input, uint32_t weight, uint32_t scales,
                               uint32_t zero, uint32_t out, int64_t group,
                               uint64_t dot_arch_flags = UINT64_MAX) {
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
      const auto n = slinky::as_constant(shape[0]);
      const auto k = slinky::as_constant(shape[1]);
      if (!n || !k || *n <= 0 || *k <= 0)
        throw std::invalid_argument("Blockwise weights must have fixed positive shape");
      const auto rows = slinky::as_constant(runtime.value(node.inputs[0]).extent(1));
      const size_t max_rows = rows ? size_t(*rows) : std::min<size_t>(32768, (size_t(1) << 30) / *k);
      void* raw = nullptr;
      if (lab_blockwise_create(*n, *k, max_rows, dot_arch_flags, &raw))
        throw std::runtime_error("Rust blockwise preparation failed");
      auto operation = std::shared_ptr<void>(raw, lab_blockwise_delete);
      auto callback = [operation](const slinky::call_stmt* call,
                         slinky::eval_context& context) -> slinky::index_t {
        const auto& x = context.lookup_buffer(call->inputs[0])->cast<const float>();
        const auto& w = context.lookup_buffer(call->inputs[1])->cast<const uint8_t>();
        const auto& scales = context.lookup_buffer(call->inputs[2])->cast<const float>();
        const auto& zero = context.lookup_buffer(call->inputs[3])->cast<const int32_t>();
        const auto& y = context.lookup_buffer(call->outputs[0])->cast<float>();
        const size_t n = slinky::evaluate(call->scalars[0], context);
        const size_t k = slinky::evaluate(call->scalars[1], context);
        const size_t rows = slinky::evaluate(call->scalars[2], context);
        auto view = [](const auto& buffer) -> LabBlockwiseView {
          const size_t rank = buffer.rank;
          if (rank != 1 && rank != 2) throw std::invalid_argument("Blockwise view rank");
          for (size_t d = 0; d < rank; ++d) {
            if (buffer.dim(d).min() != 0 || buffer.dim(d).extent() < 0 ||
                (buffer.dim(d).stride() != 0 && buffer.dim(d).fold_factor() != slinky::dim::unfolded &&
                 buffer.dim(d).fold_factor() < buffer.dim(d).extent()) ||
                buffer.dim(d).stride() % buffer.elem_size != 0)
              throw std::invalid_argument("Blockwise view layout: dim=" + std::to_string(d) + " min=" + std::to_string(buffer.dim(d).min()) + " fold=" + std::to_string(buffer.dim(d).fold_factor()) + " stride=" + std::to_string(buffer.dim(d).stride()) + " element=" + std::to_string(buffer.elem_size));
          }
          return {buffer.base(), size_t(buffer.dim(0).extent()),
                  rank == 2 ? size_t(buffer.dim(1).extent()) : 1,
                  buffer.dim(0).stride() / ptrdiff_t(buffer.elem_size),
                  rank == 2 ? buffer.dim(1).stride() / ptrdiff_t(buffer.elem_size) : 0};
        };
        (void)n;
        (void)k;
        LabBlockwiseCall invocation{view(x), view(w), view(scales), view(zero), view(y), rows,
            context.config ? context.config->thread_pool : nullptr};
        return lab_blockwise_run(operation.get(), &invocation);
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
