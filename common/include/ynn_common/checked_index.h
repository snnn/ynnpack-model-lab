// Copyright 2026 @snnn. Licensed under the Apache License, Version 2.0.
#pragma once

#include <algorithm>
#include <initializer_list>
#include <optional>

#include "checked_arithmetic.h"

namespace ynn_common {
using CheckedIndex = std::optional<int64_t>;

inline CheckedIndex CheckedAdd(std::initializer_list<CheckedIndex> terms) {
  if (!terms.size()) return {};
  int64_t result = 0;
  for (const auto& term : terms)
    if (!term || !ynn_common::CheckedAddI64(result, *term, &result))
      return {};
  return result;
}
inline CheckedIndex CheckedMul(std::initializer_list<CheckedIndex> terms) {
  if (!terms.size()) return {};
  int64_t result = 1;
  for (const auto& term : terms)
    if (!term || !ynn_common::CheckedMulI64(result, *term, &result))
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
  if (!ynn_common::CheckedAddI64(result, adjustment, &result)) return {};
  return result;
}
inline bool CheckedCompare(CheckedIndex a, CheckedIndex b, bool equal) {
  return a && b && (equal ? *a == *b : *a <= *b);
}
}  // namespace ynn_common
