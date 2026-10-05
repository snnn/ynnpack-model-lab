// Copyright 2026 The LiteRT Authors.
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// https://www.apache.org/licenses/LICENSE-2.0
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

#include "runtime/ynnpack_support.h"
int main() {
  try {
    for (int bits : {2, 4, 8})
      for (size_t m : {1, 17, 128}) {
        const size_t n = 32, k = 256;
        std::vector<int8_t> input(m * k), output(m * n);
        std::vector<uint8_t> packed(n * k * bits / 8);
        std::vector<int> weight(n * k);
        std::vector<float> scales(n);
        for (size_t i = 0; i < input.size(); ++i)
          input[i] = (i * 37 % 255) - 127;
        for (size_t i = 0; i < weight.size(); ++i) {
          weight[i] = (i * 13 + i / 11) % (1 << bits) - (1 << (bits - 1));
          packed[i * bits / 8] |= uint8_t(weight[i] & ((1 << bits) - 1))
                                  << ((i * bits) % 8);
        }
        for (size_t i = 0; i < n; ++i) scales[i] = 0.001f * (1 + i % 7);
        lab_ynn::Graph g(3);
        g.Tensor(0, "input", ynn_type_int8, {m, k},
                 YNN_VALUE_FLAG_EXTERNAL_INPUT, nullptr);
        g.Tensor(1, "weight",
                 bits == 2   ? ynn_type_int2
                 : bits == 4 ? ynn_type_int4
                             : ynn_type_int8,
                 {n, k}, 0, packed.data());
        g.Tensor(2, "output", ynn_type_int8, {m, n},
                 YNN_VALUE_FLAG_EXTERNAL_OUTPUT, nullptr);
        g.FullyConnected(0, 1, 2, scales.data(), n, 0.03125f, 0.0275f);
        g.Compile(4);
        g.Bind("input", input.data(), input.size());
        g.Bind("output", output.data(), output.size());
        g.Run();
        int maxerror = 0;
        for (size_t row = 0; row < m; ++row)
          for (size_t col = 0; col < n; ++col) {
            int32_t acc = 0;
            for (size_t z = 0; z < k; ++z)
              acc += int(input[row * k + z]) * weight[col * k + z];
            float f = acc * 0.03125f * scales[col] / 0.0275f;
            int expected =
                std::max(-128, std::min(127, int(std::nearbyint(f))));
            maxerror =
                std::max(maxerror, std::abs(expected - output[row * n + col]));
          }
        std::cout << "bits=" << bits << " rows=" << m
                  << " max_code_error=" << maxerror << "\n";
        if (maxerror > 1) return 1;
      }
  } catch (const std::exception& e) {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
