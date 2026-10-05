// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
#pragma once
#include <algorithm>
#include <array>
#include <cstdint>
#include <cstring>
#include <iomanip>
#include <sstream>
#include <string>

namespace lab {
// Streaming SHA-256 for asset integrity. No platform crypto library dependency.
class Sha256 {
 public:
  void Update(const void* data, size_t bytes) {
    const auto* p = static_cast<const uint8_t*>(data);
    bytes_ += bytes;
    while (bytes) {
      const size_t n = std::min(bytes, 64 - used_);
      std::memcpy(block_.data() + used_, p, n);
      used_ += n;
      p += n;
      bytes -= n;
      if (used_ == 64) {
        Compress();
        used_ = 0;
      }
    }
  }
  std::string Finish() {
    const uint64_t bits = bytes_ * 8;
    const uint8_t mark = 0x80, zero = 0;
    Update(&mark, 1);
    while (used_ != 56) Update(&zero, 1);
    uint8_t length[8];
    for (int i = 0; i < 8; ++i) length[7 - i] = bits >> (8 * i);
    Update(length, 8);
    std::ostringstream out;
    out << std::hex << std::setfill('0');
    for (auto v : h_) out << std::setw(8) << v;
    return out.str();
  }
  static std::string Digest(const void* p, size_t n) {
    Sha256 h;
    h.Update(p, n);
    return h.Finish();
  }

 private:
  static uint32_t R(uint32_t x, int n) { return (x >> n) | (x << (32 - n)); }
  void Compress() {
    static constexpr uint32_t k[64] = {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
        0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
        0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
        0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
        0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
        0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
        0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
        0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
        0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};
    uint32_t w[64];
    for (int i = 0; i < 16; ++i) {
      const uint8_t* p = block_.data() + 4 * i;
      w[i] = (uint32_t(p[0]) << 24) | (uint32_t(p[1]) << 16) |
             (uint32_t(p[2]) << 8) | p[3];
    }
    for (int i = 16; i < 64; ++i) {
      uint32_t a = w[i - 15], b = w[i - 2];
      w[i] = w[i - 16] + (R(a, 7) ^ R(a, 18) ^ (a >> 3)) + w[i - 7] +
             (R(b, 17) ^ R(b, 19) ^ (b >> 10));
    }
    auto s = h_;
    for (int i = 0; i < 64; ++i) {
      const uint32_t t = s[7] + (R(s[4], 6) ^ R(s[4], 11) ^ R(s[4], 25)) +
                         ((s[4] & s[5]) ^ (~s[4] & s[6])) + k[i] + w[i];
      const uint32_t u = (R(s[0], 2) ^ R(s[0], 13) ^ R(s[0], 22)) +
                         ((s[0] & s[1]) ^ (s[0] & s[2]) ^ (s[1] & s[2]));
      for (int j = 7; j > 0; --j) s[j] = s[j - 1];
      s[4] += t;
      s[0] = t + u;
    }
    for (int i = 0; i < 8; ++i) h_[i] += s[i];
  }
  std::array<uint32_t, 8> h_ = {0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
                                0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};
  std::array<uint8_t, 64> block_{};
  size_t used_ = 0;
  uint64_t bytes_ = 0;
};
}  // namespace lab
