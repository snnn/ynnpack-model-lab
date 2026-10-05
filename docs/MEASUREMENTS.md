<!--
Copyright 2026 The LiteRT Authors.
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
https://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND.
-->

# Full Gemma4 E2B: native YNNPACK measurements

These are the **original integrated experiment measurements**, retained as the
performance record. Standalone CMake extraction validation is documented
separately in [VALIDATION.md](VALIDATION.md); it is not a new timing campaign.

Measured October 2, 2026. **The current YNNPACK integration is slower than our
packed-dynamic XNNPACK path, including when model loading and preparation are
excluded.** Symbolic state handling works, but it does not compensate for the
current execution costs. Keep the established runner defaults.

## What is integrated

The external graph author generated complete E2B KV-only prefill and
decode graphs directly for native YNNPACK. They contain 1,831/3,790 operations
and 2,156/4,454 logical values respectively. The model uses the published
`.litertlm`-derived weights, static QAT activation scales, and INT8 KV scales.
Packed INT2/INT4/INT8 constants remain integer storage. It does not substitute
the Transformers checkpoint or float weights for the existing experiment.

Each phase has one prepared YNNPACK/Slinky pipeline. The runtime supplies
query rows, independent position, and external buffers. Symbolic expressions carry
`end = position + rows`, global history, and the sliding-window interval into
the backend. Prefill chunks contain at most 128 real query rows, including the
short final chunk. The cache has fixed capacity and a changing logical extent.
The pipeline updates it before attention consumes its views.

Every invocation checks the append payload: exactly **9,216 bytes per token**
across E2B's 15 K/V owners. There are zero view-copy callbacks in all successful
full-model invocations. These counts cover fresh KV writes and history-view
materialization. Attention still reads history, may dequantize/pack it, and
materializes chunk scores. This is chunked attention, not online-softmax tiled
attention. No whole-cache copy or host per-layer execution was introduced.

The direct integration, offline graph author, and isolated local dependency
patch leave the existing XNNPACK/LiteRT defaults unchanged.

## Measurement method

- Linux i9-12900K: four physical P cores, affinity `55`; the one-thread control
  uses affinity `40`. Desktop XNNPACK measurements use the fully delegated
  LiteRT runner.
- TECNO LJ9: four threads, affinity `f0`. Pixel 8: four threads, affinity `1e0`.
  Both phones also run the preserved direct native XNNPACK implementation.
- Prompts 17, 128, and 1,024; capacities 2,048 and 8,448; 32 forced continuation
  tokens. Desktop additionally tests one thread at capacity 2,048.
- One warmup and three measured requests per case. Tables use median TTFT and
  prefix latency; decode throughput is the reciprocal of mean token latency
  over the 96 measured decode steps. There are 75 configurations, 225 measured
  requests, and 75 warmups in the final matrix.
- TTFT starts at prompt execution and ends with first logits/argmax. Tokenization
  and graph setup are excluded. Prefix throughput is `(prompt_length-1) /
  prefix_time`: the last prompt token runs through the decode graph for first
  logits. Native XNNPACK reports combined TTFT, so its separate prefix rate is
  left blank. The CSV also gives `prompt_length/TTFT` for every implementation.
- Prefix and decode use the same forced token IDs across engines/capacities.
  Timing runs do not dump logits. One benchmark runs at a time per device.
- XNNPACK uses existing on-disk weight caches. The first desktop packed-control
  process created its cache and is preserved in raw artifacts; the final table
  uses a separate process loading that cache. This matters especially for peak
  RSS and setup time, even though request timing was already warm.
- The YNNPACK kernel libraries use optimized builds. The experiment harness
  uses `-O1`; its large generated setup-only builder disables compiler
  optimization to control compilation cost. Python is absent during inference.
- Phone runs have 25-second process cooldowns and recorded battery readings;
  CPU frequencies are not locked. Pixel repeats vary appreciably. This is a
  first comparative matrix, not a thermally normalized microbenchmark. Large
  gaps are clear; small percentage differences need more repetitions.

The static controls retain the same source QAT schema. The packed-dynamic
controls use our established faster activation/FC lowering and are practical
performance controls, not identical-arithmetic controls. Host static uses the
Core-authored TFLite graph; phone static uses the earlier C++-authored dynamic
graph. Control artifacts and their binary/model hashes are recorded. They are
preserved working builds, not a rebuild forcing all backends to the same
dependency revision.

In these tables, “packed dynamic” names the established **prefill-only W4
graph configuration**. It replaces fixed QAT activation quantization/clipping
around 100 prefill FCs with floating interfaces and runtime dynamic INT8
quantization. On ARM, the earlier kernel audits identified the QP8 packed-input
I8MM path. The desktop profile in this experiment instead identifies ordinary
QD8 input with AVX-VNNI; the configuration name does not mean that desktop used
a QP8 kernel. Decode retains its original static graph, and W2/W8 FCs and INT8
KV scales are unchanged. Consequently this comparison includes both backend
and activation-contract differences; the static-QAT rows are the closer
quantization-matched control.

“Static QAT” describes the transformer's quantized projections. The language
head retains a floating interface; this YNNPACK lowerer internally dynamically
quantizes its input to INT8 before the integer dot. Backend choices inside a
floating interface can therefore contribute to numerical differences even
when the source weight codes and QAT scales are the same.

## Main result: 1,024-token prompt, capacity 2,048, four threads

| Machine | Path | Warm TTFT, ms | Prefix tok/s | Decode tok/s | Peak RSS, MiB |
| --- | --- | --- | --- | --- | --- |
| Linux i9-12900K | YNNPACK static QAT | 1,714.0 | 606.9 | 35.1 | 1,728.7 |
| Linux i9-12900K | LiteRT/XNNPACK static QAT | 1,008.3 | 1,041.7 | 38.6 | 972.0 |
| Linux i9-12900K | LiteRT/XNNPACK packed dynamic | 861.3 | 1,224.6 | 38.7 | 1,217.9 |
| TECNO LJ9 | LiteRT/XNNPACK static QAT | 3,289.3 | 315.2 | 24.0 | 1,021.8 |
| TECNO LJ9 | YNNPACK static QAT | 4,281.3 | 242.0 | 19.0 | 1,725.0 |
| TECNO LJ9 | LiteRT/XNNPACK packed dynamic | 2,285.9 | 455.8 | 24.0 | 1,267.9 |
| TECNO LJ9 | Native XNNPACK packed dynamic | 2,321.3 | — | 25.7 | 2,168.4 |
| Pixel 8 | LiteRT/XNNPACK static QAT | 3,384.3 | 306.4 | 18.3 | 1,015.5 |
| Pixel 8 | YNNPACK static QAT | 5,345.0 | 194.1 | 15.5 | 1,723.8 |
| Pixel 8 | LiteRT/XNNPACK packed dynamic | 2,551.8 | 408.8 | 18.7 | 1,262.1 |
| Pixel 8 | Native XNNPACK packed dynamic | 3,591.8 | — | 20.9 | 2,160.8 |

The packed path wins prefill on every machine. YNNPACK is also slower than the
static-QAT control at this prompt length. Decode differences are smaller than
prefill differences, especially on the desktop. The direct native result on
Pixel varies more than the fully delegated LiteRT result; these runs do not
establish a universal ranking of the two XNNPACK frontends.

Peak RSS is a process high-water mark, including preparation, mappings,
resident packed weights, and all requests already executed in that process.
YNNPACK retains two prepared phase runtimes. These values are not isolated
activation/scratch sizes or incremental KV costs.

## Short prompts

| Machine | Path | Prompt | TTFT, ms | Prefix tok/s | Decode tok/s |
| --- | --- | --- | --- | --- | --- |
| Linux i9-12900K | YNNPACK static QAT | 128 | 206.8 | 702.6 | 39.2 |
| Linux i9-12900K | YNNPACK static QAT | 17 | 48.2 | 684.8 | 40.6 |
| Linux i9-12900K | LiteRT/XNNPACK packed dynamic | 128 | 115.6 | 1,393.2 | 41.7 |
| Linux i9-12900K | LiteRT/XNNPACK packed dynamic | 17 | 42.4 | 866.5 | 42.4 |
| TECNO LJ9 | YNNPACK static QAT | 128 | 458.5 | 305.0 | 23.0 |
| TECNO LJ9 | YNNPACK static QAT | 17 | 76.8 | 408.9 | 26.3 |
| TECNO LJ9 | LiteRT/XNNPACK packed dynamic | 128 | 232.9 | 647.0 | 27.3 |
| TECNO LJ9 | LiteRT/XNNPACK packed dynamic | 17 | 60.1 | 639.0 | 28.1 |
| Pixel 8 | YNNPACK static QAT | 128 | 492.8 | 285.4 | 19.5 |
| Pixel 8 | YNNPACK static QAT | 17 | 90.9 | 349.9 | 22.0 |
| Pixel 8 | LiteRT/XNNPACK packed dynamic | 128 | 322.9 | 456.5 | 20.5 |
| Pixel 8 | LiteRT/XNNPACK packed dynamic | 17 | 84.5 | 386.6 | 20.1 |

The complete CSV also contains static and direct-native short-prompt controls.
YNNPACK beats the static control in some short cases, but packed-dynamic
XNNPACK remains the better practical path in this matrix. A shorter prefix
reduces the absolute value of any prefill optimization; decode/head and
embedding work become a larger share of TTFT.

## Changing capacity without changing the prompt

| Machine | Capacity | TTFT, ms | Prefix tok/s | Decode tok/s | Peak RSS, MiB |
| --- | --- | --- | --- | --- | --- |
| Linux i9-12900K | 2048 | 1,714.0 | 606.9 | 35.1 | 1,728.7 |
| Linux i9-12900K | 8448 | 1,722.7 | 604.1 | 35.6 | 1,785.2 |
| TECNO LJ9 | 2048 | 4,281.3 | 242.0 | 19.0 | 1,725.0 |
| TECNO LJ9 | 8448 | 4,486.4 | 230.7 | 18.7 | 1,781.3 |
| Pixel 8 | 2048 | 5,345.0 | 194.1 | 15.5 | 1,723.8 |
| Pixel 8 | 8448 | 5,359.4 | 193.6 | 15.5 | 1,781.0 |

Capacity increases by 4.125×, while warm YNNPACK execution stays in the same
range. Desktop prefix throughput changes from 606.9 to 604.1 tok/s; Pixel from
194.1 to 193.6. TECNO's approximately 5% change warrants more controlled
repetitions, rather than interpreting it as unused-capacity arithmetic.

The authored attention extent depends on position/query rows and window bounds,
not capacity. Desktop checks at both capacities produced **bit-identical logits
for all 12 diagnostic outputs**. INT8 KV allocation grows by exactly
`(8448-2048) * 9216 = 58,982,400 bytes = 56.25 MiB`; observed YNNPACK peak-RSS
growth is about 56–57 MiB. This is the expected storage cost of extra capacity.
It does not require processing that capacity in attention.

## One desktop thread, 1,024 tokens, capacity 2,048

| Path | TTFT, ms | Prefix tok/s | Decode tok/s |
| --- | --- | --- | --- |
| LiteRT/XNNPACK packed dynamic | 2,990.6 | 346.9 | 23.9 |
| YNNPACK static QAT | 5,533.3 | 186.5 | 20.8 |
| LiteRT/XNNPACK static QAT | 3,619.5 | 286.1 | 23.1 |

The prefill gap remains with one thread. It is not explained solely by
four-thread scheduling or synchronization overhead.

## Why this path is slower so far

Warm desktop cycle sampling, with startup excluded, identifies the principal
prefill kernel families:

| Path | Main sampled kernel | Share of sampled cycles |
| --- | --- | ---: |
| YNNPACK static QAT | `dot_uint8_int4_int32_3x16x32_1x8x8_avx2` | 71.66% |
| LiteRT/XNNPACK static QAT | `xnn_qs8_qc4w_gemm_minmax_fp32_ukernel_5x8c8__avxvnni_prfm` | 72.17% |
| LiteRT/XNNPACK packed dynamic | `xnn_qd8_f32_qc4w_gemm_minmax_ukernel_5x8c8__avxvnni_prfm` | 67.97% |

YNNPACK additionally spends 8.21% in its FP32 FMA dot kernel in this capture.
The sampled profiles support a kernel-path explanation for the desktop gap:
this CPU has AVX-VNNI, and XNNPACK uses it for the dominant W4 operation while
the selected YNNPACK path uses AVX2. Percentages are within each profile; they
are not a matched kernel-only speed ratio or a complete allocation of the
time difference.

Removing history concatenation improves the state contract, but it does not
remove the dominant transformer FC work. At 1K context, saving that copy is
insufficient to overcome slower heavy kernels. CPU symbolic support, kernel
quality, weight packing, and scheduling must be assessed separately.

This run does **not** include phone kernel sampling. YNNPACK's source contains
ARM I8MM INT4 kernels, so the mobile gap must not be described as proof that
YNNPACK lacks I8MM. Its actual kernel/packing choices and execution schedule
need a subsequent matched profile.

## Preparation and memory

YNNPACK prepares in roughly 12.4 seconds on the desktop, 49 seconds on TECNO,
and 34–35 seconds on Pixel with four threads. These costs are excluded from
the tables' TTFT. Warm-cache LiteRT setup is around 0.18–0.20 seconds on the
desktop and roughly 0.5–1.1 seconds on these phones. Disk-cache creation and
source-page residency affect setup measurements.

The YNNPACK prototype shares raw constant mappings and persistent KV between
phases, but each pipeline independently prepares its packed constants. It has
no on-disk packed-weight cache and does not discard source weight pages after
packing. A desktop `/proc` snapshot at capacity 8,448, after preparation and
initial execution, breaks resident memory into:

| Mapping category | RSS, MiB |
| --- | ---: |
| Source weights and embedding pages | 750.72 |
| Generated constants/channel-scale parameter files | 5.04 |
| Anonymous/heap/stack | 961.92 |
| Executable/libraries/other files | 12.08 |
| Total at this instant | 1,729.77 |

The anonymous category includes packed weights, graph/runtime data, KV,
scratch, and allocator-retained storage. This snapshot does not separate those
owners, so it cannot justify assigning the whole category to weight packing.
It recorded no swapped pages. The larger process peak includes temporary
preparation allocations. Embeddings are demand-paged; a different token
corpus may change their residency.

YNNPACK currently uses more RSS than the cached LiteRT controls and less than
the preserved direct-native packed implementation. Those differences reflect
allocation ownership and cache policy, not an intrinsic memory requirement of
one graph API. No `MADV_PAGEOUT` or explicit eviction was used here.

## Numerical checks and integration fixes

The integration preserves static QAT boundaries with
`YNN_FLAG_NO_EXCESS_PRECISION`. Without it, YNNPACK can remove authored
`dequantize(quantize(x))` pairs, dropping their rounding/clipping. That default
is an allowed backend precision policy, but it would change the intended QAT
experiment. Earlier pilot runs without the flag are excluded from this matrix.

Core shape guards must execute inside the same let-bound dimension scope used
by YNNPACK/Slinky reshape inference. The adapter now evaluates a compiled
preflight statement in that scope before any state writes. This fixed a
full-model reshape guard failure without concretizing symbolic dimensions.

Validation completed:

- The packed FC lowering passed nine independent integer-dot reference cases:
  INT2/INT4/INT8 weights × 1/17/128 rows. Maximum output-code error was one.
- Eight Python exporter tests passed, including packed constant byte bounds,
  external weight references, and deduplicated parameter files.
- The updated adapter passed the 154 stateful fixture invocations, invalid
  request checks, all 92 original diagnostic cases, and targeted upstream
  reduction/slice/runtime tests. Debug AddressSanitizer/leak checks passed for
  the state fixtures and original diagnostic. This is not a full-model ASan run.
- Full-model checks used prompts 1/128/129/1024 and two forced decode tokens:
  all outputs were finite; desktop argmax matched 12/12, each phone 11/12.
- The phone mismatch is prompt 129's first output. The reference's top two
  logits were 25.3653/25.2208 for tokens 699/2342; YNNPACK's were 25.250/25.019
  for tokens 2342/699. The same close swap appeared on both phones.
- Across those 36 outputs, minimum centered logit cosine was 0.9537 and maximum
  reference-to-candidate KL was 0.2642. Differences are larger than a few ULPs;
  greedy agreement alone is not a quality evaluation.
- Desktop capacity changes were bit-identical. Changing YNNPACK's chunk limit
  from 128 to 17 kept all 12 argmax choices but changed logits (maximum absolute
  change 4.545). Quantized, shape-dependent execution is not bit invariant.
  A layerwise audit would be needed before attributing all drift to expected
  backend arithmetic. Do not conflate this with equivalence under capacity changes.
- In the desktop timing corpus with 32 forced continuations, YNNPACK/static
  XNNPACK matched 98/99 first-repeat argmax choices. This remains a small,
  teacher-forced sample, not a task-quality or free-generation test.

The data supports a working full-model experiment and performance comparisons
with explicit numerical limits. It does not certify generation quality.

## What to do next

1. Keep XNNPACK as the performance control. Retain the YNNPACK path to test
   symbolic state/view contracts without history copying.
2. Profile the ARM FC kernels and compare identical shapes/quantization before
   changing graph partitioning. On x86, investigate AVX-VNNI support/selection
   for the selected low-bit YNNPACK dot path.
3. Measure and share prepared constants between prefill/decode; then add a
   persistent packed-weight cache or a controlled source-page release policy.
   Measure both residency and warm execution when changing that policy.
4. Investigate the remaining numerical drift with layerwise outputs and an
   explicit task-quality evaluation before considering this a default backend.
5. Treat online-softmax attention, matched E4B phone controls, and
   LiteRT/YNNPACK delegation as separate follow-up experiments. The later
   [E4B integration](E4B.md) has its own desktop comparison and numerical limits.

## Evidence in this repository

The compact CSV/JSON metrics, all 300 request records, normalized command arrays,
public artifact identities, sampled kernel reports, and numerical summaries are in
[results/2026-10-02](../results/2026-10-02/). They are retained results, not claims
that this repository builds every baseline executable. The XNNPACK/LiteRT control
runners are external to this standalone project. Command records use documented
placeholders for external artifacts; they preserve the recorded flags and affinity.
Machine-specific logs, large model files, weight caches, private compiler
provenance, and binary dumps are not committed here.

The root README gives standalone build/run instructions. Use the checked-in
fixtures and [benchmark methodology](BENCHMARKING.md) when collecting new data.
