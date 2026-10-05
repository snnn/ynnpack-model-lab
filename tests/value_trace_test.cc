// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
#include "runtime/value_trace.h"

#include <unistd.h>

#include <cstring>
#include <iostream>

int main() {
  const auto root = std::filesystem::temp_directory_path() /
                    ("ynn-value-trace-" + std::to_string(getpid()));
  try {
    if (!std::filesystem::create_directory(root))
      throw std::runtime_error("Test directory exists");
    {
      std::ofstream plan(root / "plan.tsv");
      plan << "input\tx\tf32\t48\tinput\n"
              "rounded\tb\tbf16\t24\toutput\n";
    }
    lab_ynn::Graph graph(3);
    graph.Tensor(0, "x", ynn_type_fp32, {1, 0, 4},
                 YNN_VALUE_FLAG_EXTERNAL_INPUT, nullptr);
    graph.Tensor(1, "b", ynn_type_bf16, {1, 0, 4}, 0, nullptr);
    graph.Tensor(2, "out", ynn_type_fp32, {1, 0, 4},
                 YNN_VALUE_FLAG_EXTERNAL_OUTPUT, nullptr);
    graph.Convert(0, 1);
    graph.Convert(1, 2);
    lab::ValueTrace trace(graph, (root / "plan.tsv").string());
    graph.Compile(1);
    trace.Bind();
    float x[] = {1, 2, -3, 4, 5, 6, 7, -8, 9, 10, 11, 12}, out[12];
    for (size_t rows : {1, 3}) {
      graph.Bind("x", x, sizeof(x), {1, rows, 4});
      graph.Bind("out", out, sizeof(out));
      graph.Run();
      const auto dir = root / std::to_string(rows);
      trace.Save(dir.string());
      if (std::filesystem::file_size(dir / "input.f32") != rows * 16 ||
          std::filesystem::file_size(dir / "rounded.bf16") != rows * 8 ||
          std::memcmp(x, out, rows * 16))
        throw std::runtime_error("Dynamic trace size/output mismatch");
      std::ifstream f(dir / "rounded.bf16", std::ios::binary);
      for (size_t i = 0; i < rows * 4; ++i) {
        uint16_t actual;
        uint32_t bits;
        f.read(reinterpret_cast<char*>(&actual), 2);
        std::memcpy(&bits, x + i, 4);
        if (!f || actual != bits >> 16)
          throw std::runtime_error("Trace snapshot content mismatch");
      }
    }
    std::filesystem::remove_all(root);
    std::cout << "Dynamic BF16 inspection and singleton dimensions passed\n";
    return 0;
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    return 1;
  }
}
