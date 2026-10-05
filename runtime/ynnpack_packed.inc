// Copyright 2026 @snnn. Licensed under the Apache License, Version 2.0.
// Included inside lab_ynn::Graph. Physical packed carriers are rank-one bytes;
// logical dimensions remain explicit Slinky expressions.
struct PackedDescriptor {
  int bits;
  std::vector<slinky::expr> shape;
  std::vector<std::string> parameters;
};
std::map<uint32_t, PackedDescriptor> packed_;
void PackedTensor(uint32_t id, const std::string& name, int bits,
                  std::vector<size_t> dims, uint32_t flags, const void* data) {
  if (bits != 2 && bits != 4) throw std::invalid_argument("packed width");
  std::vector<int64_t> sizes(dims.begin(), dims.end());
  Tensor(id, name, ynn_type_uint8,
         {static_cast<size_t>(packed::Bytes(packed::Count(sizes), bits))},
         flags, data);
  PackedDescriptor p{bits, {}, {}};
  for (size_t a = 0; a < dims.size(); ++a) {
    if (flags & YNN_VALUE_FLAG_EXTERNAL_INPUT) {
      auto key = "__packed_axis/" + name + "/" + std::to_string(a);
      p.shape.push_back(Parameter(key, 0, std::numeric_limits<int64_t>::max()));
      shape_parameters_.insert(key);
      p.parameters.push_back(key);
    } else
      p.shape.push_back(int64_t(dims[a]));
  }
  packed_.emplace(id, std::move(p));
}
void PackedShape(uint32_t id, std::vector<slinky::expr> shape) {
  packed_.at(id).shape = std::move(shape);
}
std::vector<slinky::expr> LogicalShape(uint32_t id) const {
  auto p = packed_.find(id);
  if (p != packed_.end()) return p->second.shape;
  std::vector<slinky::expr> shape;
  const auto& v = graph_->value(id);
  for (int d = v.rank(); d-- > 0;) shape.push_back(v.extent(d));
  return shape;
}
void PackedRoute(const std::string& kind, std::vector<uint32_t> inputs,
                 uint32_t out, std::vector<slinky::expr> shape,
                 std::vector<int64_t> args = {},
                 std::vector<slinky::expr> starts = {}, int axis = 0,
                 int mode = 0) {
  const int out_bits = packed_.count(out) ? packed_.at(out).bits : 0;
  if (out_bits) PackedShape(out, shape);
  auto& output = graph_->value(out);
  if (out_bits) {
    slinky::expr count = 1;
    for (const auto& d : shape) count = count * d;
    output.extents = {slinky::ceil_div(count, slinky::expr(8 / out_bits))};
  } else
    output.extents.assign(shape.rbegin(), shape.rend());
  std::vector<std::vector<slinky::expr>> in_shapes;
  std::vector<int> bits, types;
  for (auto id : inputs) {
    in_shapes.push_back(LogicalShape(id));
    bits.push_back(packed_.count(id) ? packed_.at(id).bits : 0);
    types.push_back(graph_->value(id).type);
  }
  ynn_node n;
  n.op = ynn_node::opaque{"core_packed_route"};
  n.inputs = inputs;
  n.outputs = {out};
  n.create = [kind, shape, in_shapes, bits, types, out_bits, args, starts, axis,
              mode](const ynn_node& n, ynn_runtime& r) {
    auto& b = r.value(n.outputs[0]);
    b.make_buffer(r, int64_t(out_bits ? 1 : ynn::type_size_bytes(b.type)));
    auto dims = r.globals.make_dims(b.rank());
    std::vector<slinky::func::input> sources;
    for (auto id : n.inputs) {
      const auto& a = r.value(id);
      slinky::box_expr bounds;
      for (int d = 0; d < a.rank(); ++d)
        bounds.push_back(slinky::min_extent(0, a.extent(d)));
      sources.push_back({a.buffer, bounds});
    }
    std::vector<slinky::expr> scalar = shape;
    for (const auto& s : in_shapes)
      scalar.insert(scalar.end(), s.begin(), s.end());
    scalar.insert(scalar.end(), starts.begin(), starts.end());
    auto callback = [kind, shape, in_shapes, bits, types, out_bits, args,
                     starts, axis,
                     mode](const slinky::call_stmt* call,
                           slinky::eval_context& ctx) -> slinky::index_t {
      try {
        size_t next = 0;
        auto read = [&](size_t n) {
          std::vector<int64_t> values;
          for (size_t i = 0; i < n; ++i)
            values.push_back(slinky::evaluate(call->scalars[next++], ctx));
          packed::Count(values);
          return values;
        };
        auto os = read(shape.size());
        std::vector<packed::Tensor> in;
        for (size_t j = 0; j < in_shapes.size(); ++j)
          in.push_back({ctx.lookup_buffer(call->inputs[j]),
                        read(in_shapes[j].size()), bits[j], types[j]});
        // Starts may contain only nonnegative indices; do not multiply them.
        std::vector<int64_t> begin;
        for (size_t j = 0; j < starts.size(); ++j)
          begin.push_back(slinky::evaluate(call->scalars[next++], ctx));
        auto* dst = ctx.lookup_buffer(call->outputs[0]);
        const auto count = packed::Count(os);
        auto selected = [&](const std::vector<int64_t>& coord) {
          return packed::Select(kind, in, os, coord, args, begin, axis, mode);
        };
        if (out_bits) {
          // One invocation owns whole destination bytes, including tail bits.
          for (int64_t byte = dst->dim(0).min(); byte <= dst->dim(0).max();
               ++byte) {
            uint8_t value = 0;
            for (int lane = 0; lane < 8 / out_bits; ++lane) {
              const int64_t flat = byte * (8 / out_bits) + lane;
              if (flat >= count) break;
              auto pick = selected(packed::Coordinates(flat, os));
              auto q = in.at(pick.input).Code(pick.coordinate);
              value |= (uint8_t(q) & ((1u << out_bits) - 1))
                       << (lane * out_bits);
            }
            std::memcpy(dst->address_at(byte), &value, 1);
          }
        } else {
          // Numerical boundary fallback is explicit and computes each live
          // element once. No implicit FC/dot precision-policy change.
          for (int64_t flat = 0; flat < count; ++flat) {
            auto coord = packed::Coordinates(flat, os);
            std::vector<slinky::index_t> dc(coord.rbegin(), coord.rend());
            bool inside = true;
            for (size_t d = 0; d < dc.size(); ++d)
              inside &=
                  dc[d] >= dst->dim(d).min() && dc[d] <= dst->dim(d).max();
            if (!inside) continue;
            auto* address = dst->address_at(slinky::span<slinky::index_t>(dc));
            if (kind == "dequantize") {
              const float scale =
                  LoadScale(in[1], packed::Broadcast(coord, in[1].shape));
              const auto z = in[2].Code(packed::Broadcast(coord, in[2].shape));
              if (!std::isfinite(scale) || scale <= 0) return 1;
              const float value =
                  static_cast<float>(in[0].Code(coord) - z) * scale;
              std::memcpy(address, &value, 4);
            } else {
              auto pick = selected(coord);
              const auto& src = in.at(pick.input);
              if (src.bits) {
                const int8_t value =
                    static_cast<int8_t>(src.Code(pick.coordinate));
                if (dst->elem_size != 1) return 1;
                std::memcpy(address, &value, 1);
              } else
                std::memcpy(address, src.At(pick.coordinate), dst->elem_size);
            }
          }
        }
        return 0;
      } catch (const std::exception&) {
        return 1;
      }
    };
    slinky::call_stmt::attributes attrs;
    attrs.name = "core_packed_route";
    auto f = slinky::func(callback, sources, {{b.buffer, dims}}, scalar, attrs);
    if (out_bits) {
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
static float LoadScale(const packed::Tensor& t, const std::vector<int64_t>& c) {
  if (t.type == ynn_type_fp32) {
    float f;
    std::memcpy(&f, t.At(c), 4);
    return f;
  }
  uint16_t h;
  std::memcpy(&h, t.At(c), 2);
  if (t.type == ynn_type_bf16) {
    uint32_t u = uint32_t(h) << 16;
    float f;
    std::memcpy(&f, &u, 4);
    return f;
  }
  if (t.type == ynn_type_fp16) {
    int e = (h >> 10) & 31;
    float f = e == 31 ? (h & 1023 ? NAN : INFINITY)
                      : std::ldexp(float((h & 1023) + (e ? 1024 : 0)),
                                   e ? e - 25 : -24);
    return h & 32768 ? -f : f;
  }
  throw std::invalid_argument("scale type");
}
uint32_t PackedNative(uint32_t in) {
  if (!packed_.count(in)) return in;
  const auto descriptor = packed_.at(in);
  uint32_t out = YNN_INVALID_VALUE_ID;
  const auto last = descriptor.shape.empty()
                        ? std::optional<slinky::index_t>{}
                        : slinky::as_constant(descriptor.shape.back());
  if (last && *last % (8 / descriptor.bits) == 0) {
    // Compatible packed bytes retain their native type. Slinky can alias this
    // byte-coordinate reshape; no integer-to-float conversion is introduced.
    const auto type = descriptor.bits == 2 ? ynn_type_int2 : ynn_type_int4;
    Check(ynn_define_tensor(graph_.get(), type, descriptor.shape.size(),
                            nullptr, nullptr, 0, &out));
    auto& output = graph_->value(out);
    output.extents.assign(descriptor.shape.rbegin(), descriptor.shape.rend());
    ynn_node node;
    node.op = ynn_node::opaque{"core_packed_native_view"};
    node.inputs = {in};
    node.outputs = {out};
    node.create = [](const ynn_node& n, ynn_runtime& r) {
      const auto& a = r.value(n.inputs[0]);
      auto& b = r.value(n.outputs[0]);
      b.make_buffer(r, int64_t(1));
      auto dims = r.globals.make_dims(b.rank());
      const auto physical = b.physical_extents();
      slinky::expr ordinal = 0;
      for (int d = b.rank(); d-- > 0;)
        ordinal = ordinal * physical[d] + dims[d];
      r.funcs.push_back(slinky::func::make_copy(
          {a.buffer, {slinky::point(ordinal)}}, {b.buffer, dims}));
      return ynn_status_success;
    };
    graph_->add_node(std::move(node));
  } else {
    Check(ynn_define_tensor(graph_.get(), ynn_type_int8,
                            descriptor.shape.size(), nullptr, nullptr, 0,
                            &out));
    PackedRoute("copy", {in}, out, descriptor.shape);
  }
  return out;
}

void ParameterExpand(uint32_t in, uint32_t like, uint32_t out,
                     std::vector<int32_t> axes, std::vector<int64_t> blocks) {
  const auto shape = LogicalShape(like);
  IndexedCopy(
      "core_quantization_parameters", in, out, shape,
      [axes, blocks, rank = shape.size()](
          const ynn_runtime_value& a, const std::vector<slinky::var>& dims) {
        slinky::box_expr bounds;
        for (int j = int(axes.size()); j-- > 0;) {
          auto c = slinky::expr(dims[rank - 1 - axes[j]]) / blocks[j];
          bounds.push_back(slinky::point(
              slinky::select(a.extent(axes.size() - 1 - j) == 1, 0, c)));
        }
        return bounds;
      });
}

void MappedDequantize(uint32_t in, uint32_t scale, uint32_t zero, uint32_t out,
                      const std::vector<int32_t>& axes,
                      const std::vector<int64_t>& blocks) {
  uint32_t s = YNN_INVALID_VALUE_ID, z = YNN_INVALID_VALUE_ID;
  const auto rank = LogicalShape(in).size();
  Check(ynn_define_tensor(graph_.get(), graph_->value(scale).type, rank,
                          nullptr, nullptr, 0, &s));
  Check(ynn_define_tensor(graph_.get(), ynn_type_int32, rank, nullptr, nullptr,
                          0, &z));
  ParameterExpand(scale, in, s, axes, blocks);
  ParameterExpand(zero, in, z, axes, blocks);
  PackedRoute("dequantize", {in, s, z}, out, LogicalShape(in));
}

void PackedConstantOutput(uint32_t id, const std::string& name, int bits,
                          std::vector<size_t> dims, const void* data) {
  PackedTensor(id, name, bits, dims, YNN_VALUE_FLAG_EXTERNAL_OUTPUT, nullptr);
  uint32_t source = YNN_INVALID_VALUE_ID;
  std::vector<int64_t> logical(dims.begin(), dims.end());
  size_t bytes = packed::Bytes(packed::Count(logical), bits);
  Check(ynn_define_tensor(graph_.get(), ynn_type_uint8, 1, &bytes, data, 0,
                          &source));
  packed_.emplace(source, packed_.at(id));
  PackedRoute("copy", {source}, id, packed_.at(id).shape);
}
