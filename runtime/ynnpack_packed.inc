// Copyright 2026 @snnn. Licensed under the Apache License, Version 2.0.
// Included inside lab_ynn::Graph. Physical packed carriers are rank-one bytes;
// logical dimensions remain explicit Slinky expressions.
struct PackedDescriptor {
  int bits;
  std::vector<slinky::expr> shape;
  std::vector<std::string> parameters;
  slinky::expr offset = 0;
  bool resource_view = false;
  std::vector<slinky::expr> strides;
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
std::vector<slinky::expr> PackedStridesOf(uint32_t id) const {
  const auto& p = packed_.at(id);
  if (!p.strides.empty()) return p.strides;
  std::vector<slinky::expr> strides(p.shape.size());
  slinky::expr stride = 1;
  for (size_t i = p.shape.size(); i-- > 0;) {
    strides[i] = stride;
    stride = stride * slinky::max(p.shape[i], 1);
  }
  return strides;
}
void PackedStrides(uint32_t id, std::vector<slinky::expr> strides) {
  auto& p = packed_.at(id);
  if (runtime_ || !resources_.count(id) || !p.strides.empty())
    throw std::invalid_argument("packed strides require an unconsumed resource declaration");
  for (const auto& node : graph_->nodes)
    if (std::find(node.inputs.begin(), node.inputs.end(), id) != node.inputs.end())
      throw std::invalid_argument("packed strides cannot change after a resource consumer");
  if (strides.size() != p.shape.size()) throw std::invalid_argument("packed stride rank");
  p.strides = std::move(strides);
  slinky::expr span = 1, empty = 0, inner = 1;
  for (size_t i = p.shape.size(); i-- > 0;) {
    Require(p.strides[i] >= inner, "overlapping packed strides");
    span = span + slinky::max(p.shape[i] - 1, 0) * p.strides[i];
    empty = empty || p.shape[i] == 0;
    inner = p.strides[i] * slinky::max(p.shape[i], 1);
  }
  graph_->value(id).extents = {slinky::select(empty, 0, CeilDiv(span, 8 / p.bits))};
}
void PackedView(uint32_t in, uint32_t out, int axis, slinky::expr begin,
                slinky::expr end) {
  const auto source = packed_.at(in);
  if (axis < 0 || axis >= int(source.shape.size()) || !packed_.count(out) ||
      graph_->value(out).is_external_output())
    throw std::invalid_argument("packed view requires a private code view");
  Require(begin >= 0 && end >= begin && end <= source.shape[axis], "packed view bounds");
  // Retain the complete owner carrier. The code coordinate offset, including
  // a partial first byte, is interpreted by consumers. No history is repacked.
  auto descriptor = source;
  descriptor.strides = PackedStridesOf(in);
  descriptor.shape[axis] = end - begin;
  descriptor.offset = source.offset + begin * descriptor.strides[axis];
  descriptor.parameters.clear();
  descriptor.resource_view = true;
  packed_[out] = std::move(descriptor);
  auto& output = graph_->value(out);
  output.extents = graph_->value(in).extents;
  ynn_node node;
  node.op = ynn_node::opaque{"core_packed_resource_view"};
  node.inputs = {in};
  node.outputs = {out};
  node.create = [stats = counters_](const ynn_node& n, ynn_runtime& r) {
    auto& a = r.value(n.inputs[0]);
    auto& b = r.value(n.outputs[0]);
    a.buffer->dim(0).stride = 1;
    b.make_buffer(r, 1);
    b.buffer->dim(0).stride = 1;
    auto dims = r.globals.make_dims(1);
    r.funcs.push_back(slinky::func::make_copy(
        {a.buffer, {slinky::point(dims[0])}}, {b.buffer, dims},
        [stats](const slinky::raw_buffer& src, const slinky::raw_buffer& dst,
                const slinky::raw_buffer& pad) {
          stats->view_copy_bytes += dst.elem_count();
          slinky::copy(src, dst, pad);
        }));
    return ynn_status_success;
  };
  graph_->add_node(std::move(node));
}
void PackedAppend(uint32_t cache, uint32_t fresh, uint32_t out, int axis,
                  slinky::expr position, slinky::expr length) {
  const auto descriptor = packed_.at(cache);
  const uint32_t owner = alias_owners_.count(cache) ? alias_owners_.at(cache) : cache;
  if (axis < 0 || axis >= int(descriptor.shape.size()) || descriptor.resource_view ||
      !resources_.count(owner) || !packed_.count(fresh) || !packed_.count(out) ||
      packed_.at(fresh).bits != descriptor.bits ||
      LogicalShape(fresh).size() != descriptor.shape.size() ||
      packed_.at(fresh).resource_view || alias_owners_.count(out) ||
      !graph_->value(out).is_external_output())
    throw std::invalid_argument("packed append requires independent fresh codes and an effect root");
  for (size_t i = 0; i < descriptor.shape.size(); ++i)
    if (int(i) != axis) Require(descriptor.shape[i] == Axis(fresh, i), "packed append row shape");
  Require(position >= 0 && length >= 0 && length == Axis(fresh, axis) &&
          position + length <= descriptor.shape[axis], "packed append bounds");
  resources_.at(owner).append_lengths.push_back(length);
  packed_[out] = descriptor;
  packed_[out].parameters.clear();
  graph_->value(out).extents = graph_->value(cache).extents;
  aliases_[owner].push_back(out);
  alias_owners_.emplace(out, owner);
  std::vector<slinky::expr> scalar{position, length};
  scalar.insert(scalar.end(), descriptor.shape.begin(), descriptor.shape.end());
  const auto strides = PackedStridesOf(cache);
  scalar.insert(scalar.end(), strides.begin(), strides.end());
  ynn_node node;
  node.op = ynn_node::opaque{"core_packed_append"};
  node.inputs = {cache, fresh};
  node.outputs = {out};
  node.create = [scalar, axis, rank = descriptor.shape.size(), bits = descriptor.bits,
                 stats = counters_](const ynn_node& n, ynn_runtime& r) {
    const auto& old = r.value(n.inputs[0]);
    const auto& a = r.value(n.inputs[1]);
    auto& b = r.value(n.outputs[0]);
    b.make_buffer(r, 1);
    slinky::call_stmt::attributes attrs;
    attrs.name = "core_packed_append";
    attrs.allow_in_place = 1;
    auto callback = [axis, rank, bits, stats](const slinky::call_stmt* call,
                                             slinky::eval_context& ctx) -> slinky::index_t {
      if (stats->append_calls == stats->fail_before_append) return 1;
      const auto* old = ctx.lookup_buffer(call->inputs[0]);
      const auto* src = ctx.lookup_buffer(call->inputs[1]);
      auto* dst = ctx.lookup_buffer(call->outputs[0]);
      const int64_t p = slinky::evaluate(call->scalars[0], ctx);
      const int64_t n = slinky::evaluate(call->scalars[1], ctx);
      std::vector<int64_t> shape, strides;
      for (size_t i = 0; i < rank; ++i) {
        shape.push_back(slinky::evaluate(call->scalars[2+i], ctx));
        strides.push_back(slinky::evaluate(call->scalars[2+rank+i], ctx));
      }
      const lab_ynn_runtime::StateGeometry geometry(shape, axis, strides);
      if (old->base != dst->base || p < 0 || n < 0 || p > shape[axis] ||
          n > shape[axis] - p || geometry.Bytes(bits) > dst->elem_count()) return 1;
      shape[axis] = n;
      if (packed::Bytes(packed::Count(shape), bits) > src->elem_count()) return 1;
      if (stats->before_append) stats->before_append(stats->append_calls);
      std::atomic<size_t> touched{0};
      const int per = 8 / bits;
      // Distribute whole bytes. Even different logical rows can share a byte;
      // each read/modify/write therefore has exactly one physical owner.
      auto work = [&](size_t chunk) {
        std::vector<int64_t> c;
        size_t count = 0;
        const int64_t stop = std::min<int64_t>((chunk + 1) * 512, geometry.Bytes(bits));
        for (int64_t byte = chunk * 512; byte < stop; ++byte) {
          unsigned mask = 0, value = 0;
          for (int lane = 0; lane < per; ++lane) {
            if (!geometry.Coordinates(byte * per + lane, c) ||
                c[axis] < p || c[axis] >= p+n) continue;
            c[axis] -= p;
            const int64_t index = packed::Ordinal(c, shape);
            const unsigned code = (*static_cast<const uint8_t*>(src->address_at(index / per)) >>
                                   ((index % per) * bits)) & ((1u << bits) - 1);
            mask |= ((1u << bits) - 1) << (lane * bits);
            value |= code << (lane * bits);
          }
          if (mask) {
            auto* address = static_cast<uint8_t*>(dst->address_at(byte));
            *address = uint8_t((*address & ~mask) | value);
            ++count;
          }
        }
        touched.fetch_add(count, std::memory_order_relaxed);
      };
      if (n) {
        const size_t chunks = (geometry.Bytes(bits) + 511) / 512;
        if (ctx.config->thread_pool) ctx.config->thread_pool->parallel_for(chunks, work);
        else for (size_t i = 0; i < chunks; ++i) work(i);
      }
      ++stats->append_calls;
      stats->append_bytes += touched.load();
      return 0;
    };
    auto f = slinky::func(callback,
        {{old.buffer, {slinky::min_extent(0, old.extent(0))}},
         {a.buffer, {slinky::min_extent(0, a.extent(0))}}},
        {{b.buffer, r.globals.make_dims(1)}}, scalar, attrs);
    f.compute_root();
    b.buffer->store_root();
    r.funcs.push_back(std::move(f));
    return ynn_status_success;
  };
  graph_->add_node(std::move(node));
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
  std::vector<slinky::expr> offsets;
  std::vector<std::vector<slinky::expr>> strides;
  for (auto id : inputs) {
    in_shapes.push_back(LogicalShape(id));
    strides.push_back(packed_.count(id) ? packed_.at(id).strides : std::vector<slinky::expr>{});
    bits.push_back(packed_.count(id) ? packed_.at(id).bits : 0);
    types.push_back(graph_->value(id).type);
    offsets.push_back(packed_.count(id) ? packed_.at(id).offset : slinky::expr(0));
  }
  ynn_node n;
  n.op = ynn_node::opaque{"core_packed_route"};
  n.inputs = inputs;
  n.outputs = {out};
  n.create = [kind, shape, in_shapes, bits, types, offsets, strides, out_bits, args, starts, axis,
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
    scalar.insert(scalar.end(), offsets.begin(), offsets.end());
    for (const auto& s : strides) scalar.insert(scalar.end(), s.begin(), s.end());
    scalar.insert(scalar.end(), starts.begin(), starts.end());
    auto callback = [kind, shape, in_shapes, bits, types, strides, out_bits, args,
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
        for (auto& tensor : in)
          tensor.offset = slinky::evaluate(call->scalars[next++], ctx);
        for (size_t j = 0; j < in.size(); ++j)
          for (size_t i = 0; i < strides[j].size(); ++i)
            in[j].strides.push_back(slinky::evaluate(call->scalars[next++], ctx));
        // Starts may contain only nonnegative indices; do not multiply them.
        std::vector<int64_t> begin;
        for (size_t j = 0; j < starts.size(); ++j)
          begin.push_back(slinky::evaluate(call->scalars[next++], ctx));
        auto* dst = ctx.lookup_buffer(call->outputs[0]);
        const auto count = packed::Count(os);
        // Identity/reshape routes preserve row-major code order. Copy aligned
        // byte spans directly, including byte-aligned resource windows, while
        // keeping canonical zero padding in the last partial destination byte.
        const bool linear = kind == "copy" || kind == "reshape" ||
            kind == "squeeze" || kind == "expand_dims" ||
            kind == "fuse_dims" || kind == "split_dim";
        if (linear && out_bits && in.size() == 1 && in[0].bits == out_bits &&
            in[0].strides.empty() &&
            packed::Count(in[0].shape) == count && in[0].offset % (8 / out_bits) == 0 &&
            dst->rank == 1 && in[0].buffer->rank == 1 &&
            dst->dim(0).stride() == 1 && in[0].buffer->dim(0).stride() == 1) {
          const int64_t first = dst->dim(0).min(), last = dst->dim(0).max();
          if (last >= first) {
            const int64_t offset = in[0].offset / (8 / out_bits);
            std::memcpy(dst->address_at(first), in[0].buffer->address_at(first + offset),
                        size_t(last - first + 1));
            if (count % (8 / out_bits) && last == packed::Bytes(count, out_bits) - 1) {
              auto* tail = static_cast<uint8_t*>(dst->address_at(last));
              *tail &= uint8_t((1u << ((count % (8 / out_bits)) * out_bits)) - 1);
            }
          }
          return 0;
        }
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
  if (!descriptor.resource_view && descriptor.strides.empty() && last && *last % (8 / descriptor.bits) == 0) {
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
  constant_sources_.emplace(id, source);
  PackedRoute("copy", {source}, id, packed_.at(id).shape);
}
