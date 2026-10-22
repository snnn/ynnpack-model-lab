// Copyright 2026 @snnn. Licensed under the Apache License, Version 2.0.
#pragma once

#include <algorithm>
#include <initializer_list>
#include <optional>

#include "core_ir_checked_arithmetic.h"

namespace core_runtime {
using CheckedIndex = std::optional<int64_t>;

inline CheckedIndex CheckedAdd(std::initializer_list<CheckedIndex> terms) {
  if (!terms.size()) return {};
  int64_t result = 0;
  for (const auto& term : terms)
    if (!term || !litert_opt::core::CheckedAddI64(result, *term, &result))
      return {};
  return result;
}
inline CheckedIndex CheckedMul(std::initializer_list<CheckedIndex> terms) {
  if (!terms.size()) return {};
  int64_t result = 1;
  for (const auto& term : terms)
    if (!term || !litert_opt::core::CheckedMulI64(result, *term, &result))
      return {};
  return result;
}
inline CheckedIndex CheckedMinMax(std::initializer_list<CheckedIndex> terms,
                                  bool maximum) {
  if (!terms.size()) return {};
  CheckedIndex result;
  for (const auto& term : terms) {
    if (!term) return {};
    result = !result ? term
                     : CheckedIndex(maximum ? std::max(*result, *term)
                                            : std::min(*result, *term));
  }
  return result;
}
inline CheckedIndex CheckedDiv(CheckedIndex a, CheckedIndex b, bool ceil) {
  if (!a || !b || *b <= 0) return {};
  // Positive denominator excludes INT64_MIN / -1. Adjust the quotient without
  // the overflow-prone (a + b - 1) formulation, including negative numerators.
  int64_t result = *a / *b;
  const int adjustment = ceil ? (*a % *b > 0) : -(*a % *b < 0);
  if (!litert_opt::core::CheckedAddI64(result, adjustment, &result)) return {};
  return result;
}
inline bool CheckedCompare(CheckedIndex a, CheckedIndex b, bool equal) {
  return a && b && (equal ? *a == *b : *a <= *b);
}
}  // namespace core_runtime
namespace core_ynn {
using core_runtime::CheckedAdd;
using core_runtime::CheckedCompare;
using core_runtime::CheckedDiv;
using core_runtime::CheckedIndex;
using core_runtime::CheckedMinMax;
using core_runtime::CheckedMul;
}  // namespace core_ynn
