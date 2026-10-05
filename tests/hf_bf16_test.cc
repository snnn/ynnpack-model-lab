// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
#include <iostream>

#include "models/gemma4/hf_assets.h"
#include "runtime/ynnpack_support.h"

int main() {
  try {
    if (lab::Sha256::Digest("abc", 3) !=
            "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015a"
            "d" ||
        lab::Sha256::Digest("", 0) !=
            "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855")
      throw std::runtime_error("SHA-256 known-answer failure");
    for (int bits : {2, 4, 8}) {
      constexpr size_t m = 3, n = 8, k = 32;
      std::vector<uint16_t> a(m * k), out(m * n);
      std::vector<uint8_t> w(n * k * bits / 8);
      std::vector<int> codes(n * k);
      for (size_t i = 0; i < a.size(); ++i)
        a[i] = lab::Bf16(float(int(i % 7) - 3) * 0.25f);
      for (size_t i = 0; i < codes.size(); ++i) {
        codes[i] = (i * 13 + i / 17) % (1 << bits) - (1 << (bits - 1));
        w[i * bits / 8] |= (codes[i] & ((1 << bits) - 1)) << ((i * bits) % 8);
      }
      lab_ynn::Graph g(4);
      g.Tensor(0, "a", ynn_type_bf16, {m, k}, YNN_VALUE_FLAG_EXTERNAL_INPUT,
               nullptr);
      g.Tensor(1, "w",
               bits == 2   ? ynn_type_int2
               : bits == 4 ? ynn_type_int4
                           : ynn_type_int8,
               {n, k}, 0, w.data());
      g.Tensor(2, "wb", ynn_type_bf16, {n, k}, 0, nullptr);
      g.Tensor(3, "out", ynn_type_bf16, {m, n}, YNN_VALUE_FLAG_EXTERNAL_OUTPUT,
               nullptr);
      g.Convert(1, 2);
      g.Matmul(0, 2, 3, false, true);
      g.Compile(2);
      g.Bind("a", a.data(), a.size() * 2);
      g.Bind("out", out.data(), out.size() * 2);
      g.Run();
      for (size_t i = 0; i < m; ++i)
        for (size_t j = 0; j < n; ++j) {
          float expected = 0;
          for (size_t z = 0; z < k; ++z)
            expected += lab::Float(a[i * k + z]) * codes[j * k + z];
          if (out[i * n + j] != lab::Bf16(expected))
            throw std::runtime_error("BF16 matmul mismatch");
        }
    }
    {
      lab_ynn::Graph g(5);
      float input[] = {1.234567f, -3.14159f, 1.004f, 0.01f}, output[4];
      const float two = 2.0f;
      g.Tensor(0, "x", ynn_type_fp32, {4}, YNN_VALUE_FLAG_EXTERNAL_INPUT,
               nullptr);
      g.Tensor(1, "two", ynn_type_fp32, {1}, 0, &two);
      g.Tensor(2, "product", ynn_type_fp32, {4}, 0, nullptr);
      g.Tensor(3, "rounded", ynn_type_bf16, {4}, 0, nullptr);
      g.Tensor(4, "out", ynn_type_fp32, {4}, YNN_VALUE_FLAG_EXTERNAL_OUTPUT,
               nullptr);
      g.Binary(ynn_binary_multiply, 0, 1, 2);
      g.Convert(2, 3);
      g.Convert(3, 4);
      g.Compile(1);
      g.Bind("x", input, sizeof(input));
      g.Bind("out", output, sizeof(output));
      g.Run();
      for (int i = 0; i < 4; ++i)
        if (output[i] != lab::Float(lab::Bf16(input[i] * two)))
          throw std::runtime_error(
              "Fusion removed BF16 rounding despite NO_EXCESS_PRECISION");
    }
    {
      lab_ynn::Graph g(8);
      float input[] = {0.12345f, -0.67891f, 1.004f, 0.01f}, output[4];
      const float scale = 30.0f;
      g.Tensor(0, "x", ynn_type_fp32, {4}, YNN_VALUE_FLAG_EXTERNAL_INPUT,
               nullptr);
      g.Tensor(1, "scale", ynn_type_fp32, {1}, 0, &scale);
      for (int i = 2; i < 8; ++i)
        g.Tensor(i, i == 7 ? "out" : "temp" + std::to_string(i),
                 (i == 3 || i == 6) ? ynn_type_bf16 : ynn_type_fp32, {4},
                 i == 7 ? YNN_VALUE_FLAG_EXTERNAL_OUTPUT : 0, nullptr);
      g.Unary(ynn_unary_tanh, 0, 2);
      g.Convert(2, 3);
      g.Convert(3, 4);
      g.Binary(ynn_binary_multiply, 4, 1, 5);
      g.Convert(5, 6);
      g.Convert(6, 7);
      g.Compile(1);
      g.Bind("x", input, sizeof(input));
      g.Bind("out", output, sizeof(output));
      g.Run();
      for (int i = 0; i < 4; ++i)
        if (output[i] !=
            lab::Float(
                lab::Bf16(lab::Float(lab::Bf16(std::tanh(input[i]))) * scale)))
          throw std::runtime_error("Tanh/scalar fusion removed BF16 rounding");
    }
    {
      lab_ynn::Graph g(6);
      float input[] = {1.004f, 1.012f, -1.004f, 0.12345f};
      float addend = 0.25f, sum = 0, output[4];
      g.Tensor(0, "x", ynn_type_fp32, {4}, YNN_VALUE_FLAG_EXTERNAL_INPUT,
               nullptr);
      g.Tensor(1, "rounded", ynn_type_bf16, {4}, 0, nullptr);
      g.Tensor(2, "addend", ynn_type_fp32, {1}, 0, &addend);
      g.Tensor(3, "out", ynn_type_fp32, {4}, YNN_VALUE_FLAG_EXTERNAL_OUTPUT,
               nullptr);
      g.Tensor(4, "expanded", ynn_type_fp32, {4}, 0, nullptr);
      g.Tensor(5, "mean", ynn_type_fp32, {1}, YNN_VALUE_FLAG_EXTERNAL_OUTPUT,
               nullptr);
      g.Convert(0, 1);
      g.Binary(ynn_binary_add, 1, 2, 3);
      g.Convert(1, 4);
      g.Mean(4, 5, {0}, true);
      g.Compile(1);
      g.Bind("x", input, sizeof(input));
      g.Bind("out", output, sizeof(output));
      g.Bind("mean", &sum, sizeof(sum));
      g.Run();
      float expected_sum = 0;
      for (int i = 0; i < 4; ++i) {
        const float rounded = lab::Float(lab::Bf16(input[i]));
        if (output[i] != rounded + addend)
          throw std::runtime_error("Binary bypassed input rounding");
        expected_sum += rounded;
      }
      if (sum != expected_sum * 0.25f)
        throw std::runtime_error("Reduction bypassed input rounding");
    }
    std::cout << "BF16 packed weights, dot, and rounding boundaries passed\n";
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    return 1;
  }
}
