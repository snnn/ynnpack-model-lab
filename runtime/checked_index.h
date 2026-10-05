// Copyright 2026 @snnn. Licensed under the Apache License, Version 2.0.
#pragma once

#include <algorithm>
#include <initializer_list>
#include <optional>

#include "checked_arithmetic.h"

namespace lab_ynn_runtime {
using CheckedIndex = std::optional<int64_t>;

inline CheckedIndex CheckedAdd(std::initializer_list<CheckedIndex> terms) {
  if (!terms.size()) return {};
  int64_t result = 0;
  for (const auto& term : terms)
    if (!term || !lab_ynn_arithmetic::CheckedAddI64(result, *term, &result))
      return {};
  return result;
}
inline CheckedIndex CheckedMul(std::initializer_list<CheckedIndex> terms) {
  if (!terms.size()) return {};
  int64_t result = 1;
  for (const auto& term : terms)
    if (!term || !lab_ynn_arithmetic::CheckedMulI64(result, *term, &result))
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
  if (!lab_ynn_arithmetic::CheckedAddI64(result, adjustment, &result)) return {};
  return result;
}
inline bool CheckedCompare(CheckedIndex a, CheckedIndex b, bool equal) {
  return a && b && (equal ? *a == *b : *a <= *b);
}
}  // namespace lab_ynn_runtime
namespace lab_ynn {
using lab_ynn_runtime::CheckedAdd;
using lab_ynn_runtime::CheckedCompare;
using lab_ynn_runtime::CheckedDiv;
using lab_ynn_runtime::CheckedIndex;
using lab_ynn_runtime::CheckedMinMax;
using lab_ynn_runtime::CheckedMul;
}  // namespace lab_ynn
