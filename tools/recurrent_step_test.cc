// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
// Exercise exactly the experiment engines, without another graph author.
#define main RecurrentStepBenchmarkMain
#include "recurrent_step_bench.cc"
#undef main

template <class G>
void CheckInputs(int geometry, int rows, int valid) {
  Fixture f(geometry, rows, 1);
  const std::vector<std::vector<float>> inputs = {f.q, f.k,    f.v,
                                                  f.g, f.beta, f.initial};
  StepEngine<G> engine(f, geometry, 1, YNN_FLAG_NO_EXCESS_PRECISION);
  Oracle reference(f, false);
  engine.Run(valid, &reference);
  reference.Finish(valid, f.final);
  if (inputs !=
      std::vector<std::vector<float>>{f.q, f.k, f.v, f.g, f.beta, f.initial})
    throw std::runtime_error("immutable input changed");
  const auto a = f.a, b = f.b, y = f.y;
  for (int invalid : {-1, rows + 1}) {
    bool rejected = false;
    try {
      engine.Run(invalid);
    } catch (const std::invalid_argument&) {
      rejected = true;
    }
    if (!rejected || f.a != a || f.b != b || f.y != y)
      throw std::runtime_error("invalid request wrote a buffer");
  }
}
int main() {
  try {
    for (int rows : {1, 17, 32, 128, 1024}) {
      Fixture f(0, rows, 0);
      uint64_t hash = 14695981039346656037ULL;
      for (const auto* input : {&f.q, &f.k, &f.v, &f.g, &f.beta, &f.initial}) {
        const auto* bytes =
            reinterpret_cast<const unsigned char*>(input->data());
        for (size_t i = 0; i < input->size() * sizeof(float); ++i) {
          hash ^= bytes[i];
          hash *= 1099511628211ULL;
        }
      }
      std::cout << "input_hash rows=" << rows << " fnv1a64=" << std::hex << hash
                << std::dec << "\n";
    }
    for (int geometry = 0; geometry < 6; ++geometry)
      for (int valid : {0, 1, 16, 17}) {
        CheckInputs<StepNative>(geometry, 17, valid);
        CheckInputs<lab_ynn::Graph>(geometry, 17, valid);
      }
    CheckInputs<StepNative>(0, 1024, 1024);
    CheckInputs<lab_ynn::Graph>(0, 1024, 1024);
    std::cout << "50 immutable-input and invalid-write cases passed\n";
  } catch (const std::exception& e) {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
