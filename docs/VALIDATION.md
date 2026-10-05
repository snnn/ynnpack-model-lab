# Standalone extraction validation

This page records the initial E2B extraction. E4B integration, the expanded
198-invocation state suite, and new measurements are documented in
[E4B validation](E4B.md). The shared refactor preserves the E2B builders and
all 372 desktop diagnostic dumps exactly.

Validated October 2, 2026. This verifies the standalone extraction; it is not a
new controlled performance campaign. Historical timing comparisons remain in
`MEASUREMENTS.md`.

## Builds and weight-free checks

- Linux x86_64, Clang 22.1.8, CMake Release.
- Android ARM64, NDK 28.2.13676358, API 28, static libc++.
- Fresh archive bootstrap, repeated bootstrap, and a clean Linux CMake build.
- Linux CTest: embedding decoding, asset recipes, state/views, quantized FCs.
- The original external graph-authoring environment: eight Python
  exporter tests, both builders, and all 342 parameter files reproduced exactly.
- TECNO LJ9 and Pixel 8: state/view, quantized-FC, and embedding tests.
- The state fixtures perform 154 stateful invocations covering multiple KV/query
  heads, window bounds, nonzero positions, capacity strides, invalid requests,
  and injected failures. They require no learned weights.
- Nine FC cases cover INT2/INT4/INT8 weights at 1/17/128 rows against an
  independent integer-dot reference; maximum output-code difference is one.
- Python extraction tests cover row interleaving, byte ranges/literals,
  truncated inputs, and output path rejection.

## Model assets and authoring

The standalone standard-library preparer extracted 1,735 files comprising 1,277
unique payloads from the hash-pinned published `.litertlm` file. Every payload
matched its expected SHA-256. The two generated model builders matched the
original experimental builders byte for byte after the include-path adaptation.
All 342 generated parameter files matched the extraction recipe's payloads.

The new embedding reader uses the same signed packed integer decoding and
float scale multiplication. Its scales are mapped rather than copied. Model
weights remain external and compact; neither the repository nor the executable
contains the large learned tensors.

## Full-model comparison against the preserved YNNPACK experiment

Each run uses capacity 2048, four threads, maximum chunk size 128, prompt lengths
1/128/129/1024, and two forced continuation tokens. Dumps contain first logits
and each subsequent decode output plus all 15 owners' live K/V bytes.

| Platform | Files compared | Exactly identical |
| --- | ---: | ---: |
| Linux x86_64 | 372 | 372 |
| TECNO LJ9 | 372 | 372 |
| Pixel 8 | 372 | 372 |

Per platform this is 12 full logit vectors and 360 live KV dumps. The reference
is the earlier YNNPACK build on that platform, not XNNPACK or the official
LiteRT-LM graph. The earlier cross-backend numerical differences still apply.
No task-quality claim follows from extraction parity.

Each invocation also verifies exactly 9,216 fresh KV bytes appended per token
and no view-copy callbacks. Timing records for these diagnostic runs are under
`results/2026-10-02/standalone-*-correctness.json`, with a compact parity record
and CTest log. These runs have no warmup, dump outputs, and use no controlled
affinity/thermal schedule. Do not treat their latencies as replacement benchmarks.

Large binary dumps and model payloads are intentionally excluded from Git. The
original integrated experiment's source trees, baselines, and defaults were
left unchanged.
