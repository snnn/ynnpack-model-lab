#ifndef YNNPACK_LAB_CHECKED_ARITHMETIC_H_
#define YNNPACK_LAB_CHECKED_ARITHMETIC_H_

#include <cstdint>
#include <limits>

namespace lab_ynn_arithmetic {

inline bool CheckedAddI64(int64_t a, int64_t b, int64_t* out) {
#if defined(__SIZEOF_INT128__)
  __int128 v = static_cast<__int128>(a) + static_cast<__int128>(b);
  if (v < static_cast<__int128>(std::numeric_limits<int64_t>::min()) ||
      v > static_cast<__int128>(std::numeric_limits<int64_t>::max())) {
    return false;
  }
  *out = static_cast<int64_t>(v);
  return true;
#else
  if ((b > 0 && a > std::numeric_limits<int64_t>::max() - b) ||
      (b < 0 && a < std::numeric_limits<int64_t>::min() - b)) {
    return false;
  }
  *out = a + b;
  return true;
#endif
}

inline bool CheckedMulI64(int64_t a, int64_t b, int64_t* out) {
#if defined(__SIZEOF_INT128__)
  __int128 v = static_cast<__int128>(a) * static_cast<__int128>(b);
  if (v < static_cast<__int128>(std::numeric_limits<int64_t>::min()) ||
      v > static_cast<__int128>(std::numeric_limits<int64_t>::max())) {
    return false;
  }
  *out = static_cast<int64_t>(v);
  return true;
#else
  if (a == 0 || b == 0) {
    *out = 0;
    return true;
  }
  if ((a == -1 && b == std::numeric_limits<int64_t>::min()) ||
      (b == -1 && a == std::numeric_limits<int64_t>::min())) {
    return false;
  }

  if (a > 0) {
    if (b > 0) {
      if (a > std::numeric_limits<int64_t>::max() / b) return false;
    } else {
      if (b < std::numeric_limits<int64_t>::min() / a) return false;
    }
  } else {
    if (b > 0) {
      if (a < std::numeric_limits<int64_t>::min() / b) return false;
    } else {
      if (b < std::numeric_limits<int64_t>::max() / a) return false;
    }
  }

  *out = a * b;
  return true;
#endif
}

inline bool CheckedMulAddI64(int64_t a, int64_t b, int64_t add,
                             int64_t* out) {
  int64_t product = 0;
  if (!CheckedMulI64(a, b, &product)) return false;
  return CheckedAddI64(product, add, out);
}

}  // namespace lab_ynn_arithmetic

#endif  // YNNPACK_LAB_CHECKED_ARITHMETIC_H_
