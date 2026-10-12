// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
#include <cstring>
#include <limits>

#include "runtime/rust/bridge_internal.h"

lab_ynn::CheckedIndex LabPlanExpression::Evaluate(
    slinky::eval_context& ctx) const {
  using namespace lab_ynn;
  if (op <= 1) return slinky::evaluate(value, ctx);
  auto result = operands.at(0)->Evaluate(ctx);
  for (size_t i = 1; i < operands.size(); ++i) {
    auto rhs = operands[i]->Evaluate(ctx);
    switch (op) {
      case 2:
        result = CheckedAdd({result, rhs});
        break;
      case 3:
        result = CheckedMul({result, rhs});
        break;
      case 4:
        result = CheckedMinMax({result, rhs}, false);
        break;
      case 5:
        result = CheckedMinMax({result, rhs}, true);
        break;
      case 6:
        result = CheckedDiv(result, rhs, false);
        break;
      case 7:
        result = CheckedDiv(result, rhs, true);
        break;
      default:
        return {};
    }
  }
  return result;
}

namespace {
template <typename T>
T Integer(int64_t x) {
  if constexpr (std::is_unsigned_v<T>)
    LabRequire(x >= 0 && uint64_t(x) <= std::numeric_limits<T>::max(),
               "Unsigned construction argument overflow");
  else
    LabRequire(x >= std::numeric_limits<T>::min() &&
                   x <= std::numeric_limits<T>::max(),
               "Signed construction argument overflow");
  return static_cast<T>(x);
}
class Arguments {
 public:
  Arguments(LabGraph* h, const LabPlanArg* a, size_t n) : h_(h), a_(a), n_(n) {}
  void Check(std::initializer_list<uint32_t> kinds) const {
    LabRequire(n_ == kinds.size(), "Construction argument count mismatch");
    size_t i = 0;
    for (auto kind : kinds) {
      auto actual = a_[i++].kind;
      LabRequire(
          actual == kind || (kind == 16 && (actual == 1 || actual == 15)),
          "Construction argument type mismatch");
    }
  }
  template <typename T = int64_t>
  T I(size_t i) const {
    return Integer<T>(a_[i].integer);
  }
  bool B(size_t i) const {
    LabRequire(I(i) == 0 || I(i) == 1, "Invalid boolean");
    return I(i) != 0;
  }
  double F(size_t i) const {
    LabRequire(std::isfinite(a_[i].real), "Nonfinite construction float");
    return a_[i].real;
  }
  const char* S(size_t i) const {
    LabRequire(a_[i].data, "Null construction string");
    return static_cast<const char*>(a_[i].data);
  }
  const void* D(size_t i) const { return a_[i].data; }
  uint32_t Operand(size_t i) const {
    auto id = I<uint32_t>(i);
    return a_[i].kind == 15 ? h_->graph->PackedNative(id) : id;
  }
  template <typename T>
  std::vector<T> V(size_t i) const {
    LabRequire(a_[i].count <= 1024 && (a_[i].count == 0 || a_[i].data),
               "Invalid construction vector");
    const auto* p = static_cast<const int64_t*>(a_[i].data);
    std::vector<T> out;
    for (size_t j = 0; j < a_[i].count; ++j) out.push_back(Integer<T>(p[j]));
    return out;
  }
  std::vector<double> Floats(size_t i) const {
    LabRequire(a_[i].count <= 1024 && (a_[i].count == 0 || a_[i].data),
               "Invalid coefficient vector");
    const auto* p = static_cast<const double*>(a_[i].data);
    std::vector<double> out;
    for (size_t j = 0; j < a_[i].count; ++j) {
      LabRequire(std::isfinite(p[j]), "Nonfinite coefficient");
      out.push_back(p[j]);
    }
    return out;
  }
  std::vector<std::string> Strings(size_t i) const {
    LabRequire(a_[i].count <= 1024 && (a_[i].count == 0 || a_[i].data),
               "Invalid string vector");
    const auto* p = static_cast<const char* const*>(a_[i].data);
    std::vector<std::string> out;
    for (size_t j = 0; j < a_[i].count; ++j) {
      LabRequire(p[j], "Null string");
      out.emplace_back(p[j]);
    }
    return out;
  }
  std::shared_ptr<LabPlanExpression> E(size_t i) const {
    return h_->construction->expressions.at(I<size_t>(i));
  }
  std::vector<slinky::expr> Expressions(size_t i) const {
    auto ids = V<size_t>(i);
    std::vector<slinky::expr> out;
    for (auto id : ids)
      out.push_back(h_->construction->expressions.at(id)->value);
    return out;
  }
  ynn_type Type(size_t i) const;
  ynn_binary_operator Binary(size_t i) const;
  ynn_unary_operator Unary(size_t i) const;
  ynn_reduce_operator Reduce(size_t i) const;

 private:
  LabGraph* h_;
  const LabPlanArg* a_;
  size_t n_;
};
ynn_type Arguments::Type(size_t i) const {
  const std::string name(S(i));
  if (name == "bf16") return ynn_type_bf16;
  if (name == "fp16") return ynn_type_fp16;
  if (name == "fp32") return ynn_type_fp32;
  if (name == "fp64") return ynn_type_fp64;
  if (name == "int2") return ynn_type_int2;
  if (name == "int32") return ynn_type_int32;
  if (name == "int4") return ynn_type_int4;
  if (name == "int8") return ynn_type_int8;
  if (name == "uint8") return ynn_type_uint8;
  throw std::invalid_argument("Unknown construction enum");
}
ynn_binary_operator Arguments::Binary(size_t i) const {
  const std::string name(S(i));
  if (name == "add") return ynn_binary_add;
  if (name == "divide") return ynn_binary_divide;
  if (name == "leaky_relu") return ynn_binary_leaky_relu;
  if (name == "max") return ynn_binary_max;
  if (name == "min") return ynn_binary_min;
  if (name == "multiply") return ynn_binary_multiply;
  if (name == "pow") return ynn_binary_pow;
  if (name == "subtract") return ynn_binary_subtract;
  throw std::invalid_argument("Unknown construction enum");
}
ynn_unary_operator Arguments::Unary(size_t i) const {
  const std::string name(S(i));
  if (name == "abs") return ynn_unary_abs;
  if (name == "cos") return ynn_unary_cos;
  if (name == "erf") return ynn_unary_erf;
  if (name == "exp") return ynn_unary_exp;
  if (name == "hardswish") return ynn_unary_hardswish;
  if (name == "negate") return ynn_unary_negate;
  if (name == "round") return ynn_unary_round;
  if (name == "rsqrt") return ynn_unary_rsqrt;
  if (name == "sin") return ynn_unary_sin;
  if (name == "sqrt") return ynn_unary_sqrt;
  if (name == "square") return ynn_unary_square;
  if (name == "tanh") return ynn_unary_tanh;
  throw std::invalid_argument("Unknown construction enum");
}
ynn_reduce_operator Arguments::Reduce(size_t i) const {
  const std::string name(S(i));
  if (name == "max") return ynn_reduce_max;
  if (name == "min") return ynn_reduce_min;
  if (name == "min_max") return ynn_reduce_min_max;
  if (name == "sum") return ynn_reduce_sum;
  if (name == "sum_squared") return ynn_reduce_sum_squared;
  throw std::invalid_argument("Unknown construction enum");
}
}  // namespace

extern "C" {
int32_t lab_assets_data(LabAssets* assets, const char* path, size_t size,
                        const void** out, LabError* error) noexcept {
  if (out) *out = nullptr;
  return LabCatch(error, [&] {
    LabRequire(assets && path && out, "Invalid asset request");
    *out = assets->Get(path, size);
  });
}
int32_t lab_plan_create(size_t values, LabGraph** out,
                        LabError* error) noexcept {
  if (out) *out = nullptr;
  return LabCatch(error, [&] {
    LabRequire(out && values > 0 && values <= 100000,
               "Invalid plan value count");
    auto h = std::make_unique<LabGraph>();
    h->graph = std::make_unique<lab_ynn::Graph>(values);
    h->construction = std::make_unique<LabPlanContext>();
    *out = h.release();
  });
}
int32_t lab_plan_expr(LabGraph* h, uint32_t op, int64_t literal,
                      const uint32_t* children, size_t count, uint32_t* out,
                      LabError* error) noexcept {
  return LabCatch(error, [&] {
    LabRequire(h && h->construction && out && op <= 7 && count <= 4096 &&
                   (!count || children),
               "Invalid expression request");
    auto e = std::make_shared<LabPlanExpression>();
    e->op = op;
    if (op == 0) {
      LabRequire(count == 0, "Constant has operands");
      e->value = slinky::expr(literal);
    } else if (op == 1) {
      LabRequire(count == 0, "Symbol has operands");
      e->value = h->construction->symbols.at(Integer<uint32_t>(literal));
    } else {
      LabRequire(count > 0 && (op < 6 || count == 2),
                 "Invalid expression arity");
      for (size_t i = 0; i < count; ++i)
        e->operands.push_back(h->construction->expressions.at(children[i]));
      auto value = e->operands[0]->value;
      for (size_t i = 1; i < count; ++i) {
        auto rhs = e->operands[i]->value;
        switch (op) {
          case 2:
            value = value + rhs;
            break;
          case 3:
            value = value * rhs;
            break;
          case 4:
            value = slinky::min(value, rhs);
            break;
          case 5:
            value = slinky::max(value, rhs);
            break;
          case 6:
            value = value / rhs;
            break;
          case 7:
            value = lab_ynn::CeilDiv(value, rhs);
            break;
        }
      }
      e->value = value;
    }
    *out = Integer<uint32_t>(h->construction->expressions.size());
    h->construction->expressions.push_back(std::move(e));
  });
}
int32_t lab_plan_command(LabGraph* h, const char* method, const LabPlanArg* a,
                         size_t n, LabError* error) noexcept {
  return LabCatch(error, [&] {
    LabRequire(h && h->construction && method && (!n || a),
               "Invalid construction command");
    auto* g = h->graph.get();
    Arguments x(h, a, n);
    const std::string name(method);
    if (name == "Symbol") {
      LabRequire(n >= 6 && a[1].kind == 2, "Invalid symbol arguments");
      const std::string source(x.S(1));
      slinky::expr value;
      if (source == "Axis") {
        x.Check({1, 2, 1, 1, 1, 1});
        value = g->Axis(x.I<uint32_t>(4), x.I<size_t>(5));
      } else if (source == "Parameter" || source == "InstanceParameter") {
        x.Check({1, 2, 1, 1, 2, 1, 1});
        value = source == "Parameter"
                    ? g->Parameter(x.S(4), x.I(5), x.I(6))
                    : g->InstanceParameter(x.S(4), x.I(5), x.I(6));
      } else
        throw std::invalid_argument("Unknown symbol source");
      LabRequire(
          x.I(2) <= x.I(3) &&
              h->construction->symbols.emplace(x.I<uint32_t>(0), value).second,
          "Invalid/duplicate symbol");
      g->RequireBounds(value >= x.I(2) && value <= x.I(3),
                       "declared symbol bounds");
      return;
    }
    if (name == "Guard") {
      x.Check({6, 6, 2, 2, 2});
      auto lhs = x.E(0), rhs = x.E(1);
      const std::string relation(x.S(2)), mode(x.S(4));
      LabRequire(relation == "eq" || relation == "le", "Unknown relation");
      bool eq = relation == "eq";
      if (mode == "checked")
        g->RequireChecked(
            [lhs, rhs, eq](slinky::eval_context& ctx) {
              return lab_ynn::CheckedCompare(lhs->Evaluate(ctx),
                                             rhs->Evaluate(ctx), eq);
            },
            x.S(3));
      else {
        auto condition =
            eq ? lhs->value == rhs->value : lhs->value <= rhs->value;
        if (mode == "bounds")
          g->RequireBounds(condition, x.S(3));
        else {
          LabRequire(mode == "ordinary", "Unknown guard mode");
          g->Require(condition, x.S(3));
        }
      }
      return;
    }
    if (name == "PackedTensor") {
      x.Check({1, 2, 1, 4, 1, 5});
      g->PackedTensor(x.I<uint32_t>(0), x.S(1), x.I<size_t>(2), x.V<size_t>(3),
                      x.I<int32_t>(4), x.D(5));
      return;
    }
    if (name == "PackedConstantOutput") {
      x.Check({1, 2, 1, 4, 5});
      g->PackedConstantOutput(x.I<uint32_t>(0), x.S(1), x.I<size_t>(2),
                              x.V<size_t>(3), x.D(4));
      return;
    }
    if (name == "PackedRoute") {
      x.Check({2, 4, 1, 7, 4, 7, 1, 1});
      g->PackedRoute(x.S(0), x.V<uint32_t>(1), x.I<uint32_t>(2),
                     x.Expressions(3), x.V<int64_t>(4), x.Expressions(5),
                     x.I<int32_t>(6), x.I<int32_t>(7));
      return;
    }
    if (name == "ParameterExpand") {
      x.Check({1, 1, 1, 4, 4});
      g->ParameterExpand(x.I<uint32_t>(0), x.I<uint32_t>(1), x.I<uint32_t>(2),
                         x.V<int32_t>(3), x.V<int64_t>(4));
      return;
    }
    if (name == "MappedDequantize") {
      x.Check({1, 1, 1, 1, 4, 4});
      g->MappedDequantize(x.I<uint32_t>(0), x.I<uint32_t>(1), x.I<uint32_t>(2),
                          x.I<uint32_t>(3), x.V<int32_t>(4), x.V<int64_t>(5));
      return;
    }
    if (name == "Sdpa") {
      x.Check({1, 1, 1, 1, 1, 4, 12, 1, 11, 1, 6, 6, 6, 6, 11});
      g->Sdpa(x.I<uint32_t>(0), x.I<uint32_t>(1), x.I<uint32_t>(2),
              x.I<uint32_t>(3), x.I<uint32_t>(4), x.V<int32_t>(5), x.F(6),
              x.I<int32_t>(7), x.B(8), x.I<int32_t>(9), x.E(10)->value,
              x.E(11)->value, x.E(12)->value, x.E(13)->value, x.B(14));
      return;
    }
    if (name == "WeightOnlyLinear") {
      x.Check({1, 1, 1, 1, 1, 1});
      g->WeightOnlyLinear(x.I<uint32_t>(0), x.I<uint32_t>(1), x.I<uint32_t>(2),
                          x.I<uint32_t>(3), x.I<uint32_t>(4), x.I<size_t>(5));
      return;
    }
    if (name == "Reverse") {
      x.Check({1, 1, 4});
      g->Reverse(x.I<uint32_t>(0), x.I<uint32_t>(1), x.V<int32_t>(2));
      return;
    }
    if (name == "Tile") {
      x.Check({1, 1, 4});
      g->Tile(x.I<uint32_t>(0), x.I<uint32_t>(1), x.V<int64_t>(2));
      return;
    }
    if (name == "Compare") {
      x.Check({2, 1, 1, 1, 7});
      g->Compare(x.S(0), x.I<uint32_t>(1), x.I<uint32_t>(2), x.I<uint32_t>(3),
                 x.Expressions(4));
      return;
    }
    if (name == "Select") {
      x.Check({1, 1, 1, 1, 7});
      g->Select(x.I<uint32_t>(0), x.I<uint32_t>(1), x.I<uint32_t>(2),
                x.I<uint32_t>(3), x.Expressions(4));
      return;
    }
    if (name == "Gather") {
      x.Check({1, 1, 1, 1});
      g->Gather(x.I<uint32_t>(0), x.I<uint32_t>(1), x.I<uint32_t>(2),
                x.I<int32_t>(3));
      return;
    }
    if (name == "Stack") {
      x.Check({4, 1, 1});
      g->Stack(x.V<uint32_t>(0), x.I<uint32_t>(1), x.I<int32_t>(2));
      return;
    }
    if (name == "Split") {
      x.Check({1, 4, 1, 11});
      g->Split(x.I<uint32_t>(0), x.V<uint32_t>(1), x.I<int32_t>(2), x.B(3));
      return;
    }
    if (name == "DynamicallyQuantizedMatmul") {
      x.Check({1, 1, 1, 12, 11, 1});
      g->DynamicallyQuantizedMatmul(x.I<uint32_t>(0), x.I<uint32_t>(1),
                                    x.I<uint32_t>(2), x.F(3), x.B(4),
                                    x.I<int32_t>(5));
      return;
    }
    if (name == "ShapeTensor") {
      x.Check({1, 7, 11});
      g->ShapeTensor(x.I<uint32_t>(0), x.Expressions(1), x.B(2));
      return;
    }
    if (name == "Tensor") {
      x.Check({1, 2, 3, 4, 1, 5});
      g->Tensor(x.I<uint32_t>(0), x.S(1), x.Type(2), x.V<size_t>(3),
                x.I<int32_t>(4), x.D(5));
      return;
    }
    if (name == "ConstantOutput") {
      x.Check({1, 2, 3, 4, 5});
      g->ConstantOutput(x.I<uint32_t>(0), x.S(1), x.Type(2), x.V<size_t>(3),
                        x.D(4));
      return;
    }
    if (name == "BindScalarParameter") {
      x.Check({1, 2});
      g->BindScalarParameter(x.I<uint32_t>(0), x.S(1));
      return;
    }
    if (name == "InputShape") {
      x.Check({1, 7});
      g->InputShape(x.I<uint32_t>(0), x.Expressions(1));
      return;
    }
    if (name == "ResultShape") {
      x.Check({1, 7});
      g->ResultShape(x.I<uint32_t>(0), x.Expressions(1));
      return;
    }
    if (name == "Resource") {
      x.Check({1, 2, 1, 6, 2});
      g->Resource(x.I<uint32_t>(0), x.S(1), x.I<int32_t>(2), x.E(3)->value,
                  x.S(4));
      return;
    }
    if (name == "BeginProfileOperation") {
      x.Check({2, 2, 4, 4, 14});
      g->BeginProfileOperation(x.S(0), x.S(1), x.V<uint32_t>(2),
                               x.V<uint32_t>(3), x.Strings(4));
      return;
    }
    if (name == "EndProfileOperation") {
      x.Check({});
      g->EndProfileOperation();
      return;
    }
    if (name == "BeginOperation") {
      x.Check({14});
      g->BeginOperation(x.Strings(0));
      return;
    }
    if (name == "EndOperation") {
      x.Check({14, 4});
      g->EndOperation(x.Strings(0), x.V<uint32_t>(1));
      return;
    }
    if (name == "Binary") {
      x.Check({8, 1, 1, 1});
      g->Binary(x.Binary(0), x.I<uint32_t>(1), x.I<uint32_t>(2),
                x.I<uint32_t>(3));
      return;
    }
    if (name == "Unary") {
      x.Check({9, 1, 1});
      g->Unary(x.Unary(0), x.I<uint32_t>(1), x.I<uint32_t>(2));
      return;
    }
    if (name == "Matmul") {
      x.Check({1, 1, 1, 11, 11});
      g->Matmul(x.I<uint32_t>(0), x.I<uint32_t>(1), x.I<uint32_t>(2), x.B(3),
                x.B(4));
      return;
    }
    if (name == "Dot") {
      x.Check({16, 16, 1, 1, 1});
      g->Dot(x.Operand(0), x.Operand(1), x.I<uint32_t>(2), x.I<uint32_t>(3),
             x.I<size_t>(4));
      return;
    }
    if (name == "Quantize") {
      x.Check({1, 1, 12, 1});
      g->Quantize(x.I<uint32_t>(0), x.I<uint32_t>(1), x.F(2), x.I<int32_t>(3));
      return;
    }
    if (name == "Dequantize") {
      x.Check({16, 1, 12, 1});
      g->Dequantize(x.Operand(0), x.I<uint32_t>(1), x.F(2), x.I<int32_t>(3));
      return;
    }
    if (name == "QuantizeTensor") {
      x.Check({1, 1, 1, 1});
      g->QuantizeTensor(x.I<uint32_t>(0), x.I<uint32_t>(1), x.I<uint32_t>(2),
                        x.I<uint32_t>(3));
      return;
    }
    if (name == "DequantizeTensor") {
      x.Check({1, 1, 1, 1});
      g->DequantizeTensor(x.I<uint32_t>(0), x.I<uint32_t>(1), x.I<uint32_t>(2),
                          x.I<uint32_t>(3));
      return;
    }
    if (name == "DynamicQuantization") {
      x.Check({1, 1, 1});
      g->DynamicQuantization(x.I<uint32_t>(0), x.I<uint32_t>(1),
                             x.I<uint32_t>(2));
      return;
    }
    if (name == "FuseDims") {
      x.Check({1, 1, 1, 1});
      g->FuseDims(x.I<uint32_t>(0), x.I<uint32_t>(1), x.I<int32_t>(2),
                  x.I<int32_t>(3));
      return;
    }
    if (name == "SplitDim") {
      x.Check({1, 1, 1, 4});
      g->SplitDim(x.I<uint32_t>(0), x.I<uint32_t>(1), x.I<int32_t>(2),
                  x.V<size_t>(3));
      return;
    }
    if (name == "ShapeProduct") {
      x.Check({1, 1, 4});
      g->ShapeProduct(x.I<uint32_t>(0), x.I<uint32_t>(1), x.V<int32_t>(2));
      return;
    }
    if (name == "Polynomial") {
      x.Check({1, 1, 13});
      g->Polynomial(x.I<uint32_t>(0), x.I<uint32_t>(1), x.Floats(2));
      return;
    }
    if (name == "Reduce") {
      x.Check({10, 1, 1, 4, 11});
      g->Reduce(x.Reduce(0), x.I<uint32_t>(1), x.I<uint32_t>(2),
                x.V<int32_t>(3), x.B(4));
      return;
    }
    if (name == "Softmax") {
      x.Check({1, 1, 12});
      g->Softmax(x.I<uint32_t>(0), x.I<uint32_t>(1), x.F(2));
      return;
    }
    if (name == "Reshape") {
      x.Check({1, 1, 4});
      g->Reshape(x.I<uint32_t>(0), x.I<uint32_t>(1), x.V<size_t>(2));
      return;
    }
    if (name == "Transpose") {
      x.Check({1, 1, 4});
      g->Transpose(x.I<uint32_t>(0), x.I<uint32_t>(1), x.V<int32_t>(2));
      return;
    }
    if (name == "Slice") {
      x.Check({1, 1, 4, 4});
      g->Slice(x.I<uint32_t>(0), x.I<uint32_t>(1), x.V<int64_t>(2),
               x.V<int64_t>(3));
      return;
    }
    if (name == "Concat") {
      x.Check({4, 1, 1});
      g->Concat(x.V<uint32_t>(0), x.I<uint32_t>(1), x.I<int32_t>(2));
      return;
    }
    if (name == "View") {
      x.Check({1, 1, 1, 6, 6});
      g->View(x.I<uint32_t>(0), x.I<uint32_t>(1), x.I<int32_t>(2),
              x.E(3)->value, x.E(4)->value);
      return;
    }
    if (name == "Append") {
      x.Check({1, 1, 1, 1, 6, 6});
      g->Append(x.I<uint32_t>(0), x.I<uint32_t>(1), x.I<uint32_t>(2),
                x.I<int32_t>(3), x.E(4)->value, x.E(5)->value);
      return;
    }
    if (name == "Mask") {
      x.Check({1, 1, 6, 6, 1, 11});
      g->Mask(x.I<uint32_t>(0), x.I<uint32_t>(1), x.E(2)->value, x.E(3)->value,
              x.I<int32_t>(4), x.B(5));
      return;
    }
    if (name == "Conv2D") {
      x.Check({1, 1, 1, 1, 4, 4, 4, 11, 11, 1, 1});
      g->Conv2D(x.I<uint32_t>(0), x.I<uint32_t>(1), x.I<uint32_t>(2),
                x.I<uint32_t>(3), x.V<size_t>(4), x.V<size_t>(5),
                x.V<size_t>(6), x.B(7), x.B(8), x.I<size_t>(9),
                x.I<size_t>(10));
      return;
    }
    if (name == "Pool2D") {
      x.Check({1, 1, 4, 4, 11, 11});
      g->Pool2D(x.I<uint32_t>(0), x.I<uint32_t>(1), x.V<size_t>(2),
                x.V<size_t>(3), x.B(4), x.B(5));
      return;
    }
    if (name == "Pad") {
      x.Check({1, 1, 1, 7, 7, 1});
      g->Pad(x.I<uint32_t>(0), x.I<uint32_t>(1), x.I<uint32_t>(2),
             x.Expressions(3), x.Expressions(4), x.I<int32_t>(5));
      return;
    }
    if (name == "Copy") {
      x.Check({1, 1});
      g->Copy(x.I<uint32_t>(0), x.I<uint32_t>(1));
      return;
    }
    if (name == "ExpandDims") {
      x.Check({1, 1, 4});
      g->ExpandDims(x.I<uint32_t>(0), x.I<uint32_t>(1), x.V<int32_t>(2));
      return;
    }
    if (name == "Squeeze") {
      x.Check({1, 1, 4});
      g->Squeeze(x.I<uint32_t>(0), x.I<uint32_t>(1), x.V<int32_t>(2));
      return;
    }
    if (name == "Broadcast") {
      x.Check({1, 1, 4});
      g->Broadcast(x.I<uint32_t>(0), x.I<uint32_t>(1), x.V<size_t>(2));
      return;
    }
    if (name == "SymbolicBroadcast") {
      x.Check({1, 1, 7});
      g->SymbolicBroadcast(x.I<uint32_t>(0), x.I<uint32_t>(1),
                           x.Expressions(2));
      return;
    }
    if (name == "SymbolicReshape") {
      x.Check({1, 1, 7});
      g->SymbolicReshape(x.I<uint32_t>(0), x.I<uint32_t>(1), x.Expressions(2));
      return;
    }
    if (name == "SymbolicSlice") {
      x.Check({1, 1, 7, 7});
      g->SymbolicSlice(x.I<uint32_t>(0), x.I<uint32_t>(1), x.Expressions(2),
                       x.Expressions(3));
      return;
    }
    if (name == "BroadcastLike") {
      x.Check({1, 1, 1, 4});
      g->BroadcastLike(x.I<uint32_t>(0), x.I<uint32_t>(1), x.I<uint32_t>(2),
                       x.V<int32_t>(3));
      return;
    }
    if (name == "SliceLike") {
      x.Check({1, 1, 1, 4});
      g->SliceLike(x.I<uint32_t>(0), x.I<uint32_t>(1), x.I<uint32_t>(2),
                   x.V<int32_t>(3));
      return;
    }
    if (name == "Convert") {
      x.Check({1, 1});
      g->Convert(x.I<uint32_t>(0), x.I<uint32_t>(1));
      return;
    }
    if (name == "Mean") {
      x.Check({1, 1, 4, 11});
      g->Mean(x.I<uint32_t>(0), x.I<uint32_t>(1), x.V<int32_t>(2), x.B(3));
      return;
    }
    if (name == "Gelu") {
      x.Check({1, 1, 11});
      g->Gelu(x.I<uint32_t>(0), x.I<uint32_t>(1), x.B(2));
      return;
    }
    throw std::invalid_argument("Unsupported construction command");
  });
}
}  // extern "C"
