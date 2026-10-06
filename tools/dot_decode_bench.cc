// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0

// Compare one-row low-bit dot kernels without graph scheduling or epilogues.
// Each candidate has its own compatible packing and an independent arithmetic
// check. Streaming cases rotate through distinct copies of the same matrix.
#include <algorithm>
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "ynnpack/kernels/dot/dot.h"

namespace {

using Clock = std::chrono::steady_clock;
using Allocation = std::unique_ptr<uint8_t, decltype(&std::free)>;

Allocation Allocate(size_t bytes) {
  auto* p = static_cast<uint8_t*>(std::aligned_alloc(64, (bytes + 63) & ~63));
  if (!p) throw std::bad_alloc();
  std::memset(p, 0, bytes);
  return Allocation(p, &std::free);
}

const char* KernelName(ynn::dot_kernel_fn fn) {
#define YNN_DOT_KERNEL(arch, name, ...) \
  if (fn == ynn::name) return #name;
#include "ynnpack/kernels/dot/kernels.inc"
#undef YNN_DOT_KERNEL
  return "unknown";
}

uint32_t Mix(uint32_t x) {
  x ^= x >> 16;
  x *= 0x7feb352d;
  x ^= x >> 15;
  x *= 0x846ca68b;
  return x ^ (x >> 16);
}

int Weight(size_t k, size_t n, unsigned bits) {
  return static_cast<int>(Mix(static_cast<uint32_t>(k * 65537 + n)) &
                          ((1u << bits) - 1)) -
         (1 << (bits - 1));
}

struct Candidate {
  ynn::dot_kernel kernel;
  Allocation a{nullptr, &std::free};
  Allocation b{nullptr, &std::free};
  std::vector<int32_t> output;
  ynn::dot_kernel_state state;
  size_t n, k, bytes, slots, a_stride;
  unsigned bits;

  Candidate(ynn::dot_kernel selected, size_t columns, size_t reduction,
            unsigned weight_bits, size_t stream_bytes)
      : kernel(selected), n(columns), k(reduction), bits(weight_bits) {
    const size_t tile_k = kernel.tile_k;
    const bool transpose = kernel.flags & ynn::dot_flag::transpose_a;
    const size_t rows = transpose ? kernel.tile_m : 1;
    a = Allocate(rows * k);
    for (size_t i = 0; i < k; ++i) {
      size_t dest = transpose ? (i / tile_k) * rows * tile_k + i % tile_k : i;
      a.get()[dest] = static_cast<uint8_t>(
          static_cast<int>(Mix(static_cast<uint32_t>(i + 91)) % 255) - 127);
    }
    a_stride = transpose ? rows : k;
    bytes = n * k * bits / 8;
    slots = std::max<size_t>(1, (stream_bytes + bytes - 1) / bytes);
    b = Allocate(bytes * slots);
    for (size_t i = 0; i < k; ++i) {
      for (size_t j = 0; j < n; ++j) {
        size_t element = ((i / tile_k) * n + j) * tile_k + i % tile_k;
        size_t bit = element * bits;
        b.get()[bit / 8] |=
            (static_cast<unsigned>(Weight(i, j, bits)) & ((1u << bits) - 1))
            << (bit % 8);
      }
    }
    for (size_t slot = 1; slot < slots; ++slot) {
      std::memcpy(b.get() + slot * bytes, b.get(), bytes);
    }
    output.resize(n);
    Run(0);
    for (size_t j = 0; j < n; ++j) {
      int32_t expected = 0;
      for (size_t i = 0; i < k; ++i) {
        int value =
            static_cast<int>(Mix(static_cast<uint32_t>(i + 91)) % 255) - 127;
        expected += value * Weight(i, j, bits);
      }
      if (output[j] != expected) {
        throw std::runtime_error(std::string("Arithmetic mismatch: ") +
                                 KernelName(kernel.kernel));
      }
    }
  }

  void Run(size_t slot) {
    kernel.kernel(1, n, 1, 1, k, a_stride, 0, 0, a.get(), 0, 0, n * bits / 8,
                  b.get() + slot * bytes, 0, nullptr, n * sizeof(int32_t),
                  output.data(), &state);
  }

  void Measure(bool streaming, unsigned trial, double seconds) {
    for (size_t i = 0; i < 64; ++i) Run(streaming ? i % slots : 0);
    const auto start = Clock::now();
    size_t calls = 0;
    double elapsed;
    do {
      for (unsigned i = 0; i < 16; ++i, ++calls) {
        Run(streaming ? calls % slots : 0);
      }
      elapsed = std::chrono::duration<double>(Clock::now() - start).count();
    } while (elapsed < seconds);
    std::cout << "{\"kind\":\"timing\",\"bits\":" << bits
              << ",\"m\":1,\"n\":" << n << ",\"k\":" << k << ",\"kernel\":\""
              << KernelName(kernel.kernel) << "\",\"mode\":\""
              << (streaming ? "streaming" : "cached")
              << "\",\"working_set_bytes\":"
              << (streaming ? bytes * slots : bytes) << ",\"trial\":" << trial
              << ",\"calls\":" << calls
              << ",\"ns_per_call\":" << elapsed * 1e9 / calls
              << ",\"predicted_ns\":" << kernel.estimate_cost(1, n, k) * 1e9
              << ",\"arithmetic\":\"exact_int32\"}\n";
  }
};

}  // namespace

int main(int argc, char** argv) {
  try {
#ifndef YNN_ARCH_ARM
    throw std::runtime_error("This comparison requires ARM DOTPROD and I8MM");
#else
    double seconds = 0.05;
    unsigned trials = 5;
    size_t stream_bytes = 32 * 1024 * 1024;
    std::vector<std::pair<size_t, size_t> > shapes;
    for (int i = 1; i < argc; ++i) {
      const std::string arg = argv[i];
      if (arg.rfind("--seconds=", 0) == 0) {
        seconds = std::stod(arg.substr(10));
      } else if (arg.rfind("--trials=", 0) == 0) {
        trials = std::stoul(arg.substr(9));
      } else if (arg.rfind("--stream_bytes=", 0) == 0) {
        stream_bytes = std::stoull(arg.substr(15));
      } else if (arg.rfind("--shape=", 0) == 0) {
        const size_t comma = arg.find(',');
        if (comma == std::string::npos)
          throw std::runtime_error("Use --shape=N,K");
        shapes.emplace_back(std::stoull(arg.substr(8, comma - 8)),
                            std::stoull(arg.substr(comma + 1)));
      } else {
        throw std::runtime_error("Unknown argument: " + arg);
      }
    }
    if (!(seconds > 0 && seconds <= 10) || trials == 0 || trials > 100 ||
        stream_bytes > 512 * 1024 * 1024) {
      throw std::runtime_error("Invalid duration, trials, or working set");
    }
    if (shapes.empty()) {
      for (size_t k : {256, 1536, 2048, 4096, 6144, 12288}) {
        shapes.emplace_back(256, k);
      }
    }
    const uint64_t supported = ynn::get_supported_arch_flags();
    if (!ynn::is_arch_supported(
            ynn::arch_flag::neondot | ynn::arch_flag::neoni8mm, supported)) {
      throw std::runtime_error("CPU must support both DOTPROD and I8MM");
    }
    for (unsigned bits : {2u, 4u}) {
      const ynn::dot_type type{ynn_type_int8,
                               bits == 2 ? ynn_type_int2 : ynn_type_int4,
                               ynn_type_int32};
      for (auto [n, k] : shapes) {
        if (n == 0 || k == 0 || n % 32 || k % 16 || n > 262144 || k > 12288 ||
            n * k > 64 * 1024 * 1024) {
          throw std::runtime_error("Use N aligned to 32 and K aligned to 16");
        }
        const ynn::dot_shape shape{1, n, k, 1, 1};
        const auto& costs = ynn::get_dot_cost_models();
        const auto normal = ynn::get_dot_kernel(type, costs, shape);
        const auto dot = ynn::get_dot_kernel(
            type, costs, shape, {}, 0, std::nullopt,
            supported & ~static_cast<uint64_t>(ynn::arch_flag::neoni8mm));
        const auto i8mm = ynn::get_dot_kernel(
            type, costs, shape, {}, 0, std::nullopt,
            supported & ~static_cast<uint64_t>(ynn::arch_flag::neondot));
        if (!dot.kernel || !i8mm.kernel ||
            std::string(KernelName(dot.kernel)).find("neondot") ==
                std::string::npos ||
            std::string(KernelName(i8mm.kernel)).find("neoni8mm") ==
                std::string::npos) {
          throw std::runtime_error("Requested ISA kernel was not selected");
        }
        std::cout << "{\"kind\":\"selection\",\"bits\":" << bits
                  << ",\"m\":1,\"n\":" << n << ",\"k\":" << k
                  << ",\"kernel\":\"" << KernelName(normal.kernel)
                  << "\",\"tile_k\":" << normal.tile_k
                  << ",\"dotprod_predicted_ns\":" << dot.cost * 1e9
                  << ",\"i8mm_predicted_ns\":" << i8mm.cost * 1e9 << "}\n";
        Candidate candidates[] = {{dot, n, k, bits, stream_bytes},
                                  {i8mm, n, k, bits, stream_bytes}};
        for (bool streaming : {false, true}) {
          for (unsigned trial = 0; trial < trials; ++trial) {
            candidates[trial % 2].Measure(streaming, trial, seconds);
            candidates[1 - trial % 2].Measure(streaming, trial, seconds);
          }
        }
      }
    }
#endif
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    return 1;
  }
  return 0;
}
