<!-- Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0 -->

# Samsung E2B: attention cost as KV history grows

The current YNNPACK path has two concrete differences from the preserved native
Tensor API/XNNPACK control: it converts INT8 KV to FP32 before packing, and it
keeps query heads in separate batch entries with one matrix row each. Native
combines the eight heads into matrix rows and executes F32×QC8W attention.
These are useful optimization targets. Their individual contributions to the
full-model gap have not been isolated by changing execution yet.

Fresh diagnostic data puts **54.8% of YNNPACK's long-history attention worker
time in separate dequantization and packing callbacks**. Local attention's
matmul call counts stop growing at the 512-token window; global attention keeps
growing. The history-length sweep also demonstrates substantial thermal/order
effects, so its raw latency slope is not a controlled estimate of attention
scaling. This study preserves those effects instead of pooling both rounds.

## Configuration and retained evidence

Samsung SM-S937U1, Gemma4 E2B, capacity 2048, four threads, affinity `f0`, one
warmup and three measured requests, 32 forced continuation tokens. Inputs are
prefixes of the checked-in `p1024` token-ID fixture, with its same continuations.
YNNPACK uses real prefix chunks of at most 128 rows; native uses chunk 128 and
KV alignment 32, including padding. FC policies remain static QAT versus
packed dynamic. These comparisons do not establish equivalent generation quality.

The binaries and every model/parameter payload were rechecked against the
[October 7 identities](../2026-10-07-upstream-refresh/identities.json).
There was no model/backend rebuild or execution-policy change. Linux host
builds and performance remain skipped. The normal upstream pin is
`d297c798ea530c12a1878bb3a3a811bdf05d715b`, with the same declared patches.

[record.json](record.json) retains all **84 unprofiled measured requests**, their
per-token latencies, request ranges, self-consistency observations, setup/RSS,
portable commands, identities and sanitized telemetry. Two separate diagnostic
processes add six measured requests and 96 subsequent decode steps per engine.
The record includes YNNPACK per-step attention accounting, per-layer QK/PV work,
KV preparation call sites, and native stage/operator aggregates. Raw process,
device and profiling logs stay outside Git.

The fixture derivation and its SHA-256 hashes are recorded. Reproduce it by
taking the first 17/128/256/480/512/768/1024 IDs from `p1024` in
`models/gemma4_e2b/fixtures/performance.tsv`; give cases names `h17`, etc., and
retain its continuation column. Reverse the TSV line order for the second round.
Diagnostic cases use 17/512/1024 in that order. Supply the recorded binaries and
assets through the command variables in `record.json` and use fresh outputs.

## Unprofiled history sweep

Process order is YNNPACK ascending, native ascending, native descending,
YNNPACK descending. There is a 60-second initial cooldown and 60 seconds between
processes; clocks/governors are unchanged. Each process prepares its runtimes
once. Cells are mean subsequent-token latency in milliseconds; setup and the
first-logit step are excluded.

| Prompt tokens | YNN ascending | Native ascending | YNN descending | Native descending |
| ---: | ---: | ---: | ---: | ---: |
| 17 | 20.07 | 19.95 | 29.55 | 27.14 |
| 128 | 25.45 | 21.43 | 34.71 | 27.93 |
| 256 | 36.45 | 22.05 | 41.11 | 28.76 |
| 480 | 40.39 | 28.87 | 42.76 | 30.21 |
| 512 | 38.84 | 30.43 | 43.13 | 30.44 |
| 768 | 42.08 | 30.97 | 44.53 | 30.97 |
| 1024 | 44.01 | 31.45 | 41.81 | 22.76 |

The descending native process runs prompt 1024 first: it takes 22.76 ms/token,
while its final prompt-17 case takes 27.14 ms. Native attention itself still
grows with history. Its non-attention forward time changes from about 18.67 ms
at the first long case to 25.47 ms at the final short case, despite unchanged
non-attention operator shapes. The ascending process exhibits the opposite
ordering effect. Its later 512/768/1024 non-attention forward means stay close
to 25.5 ms, while attention increases from 4.05 to 4.60 to 5.08 ms.

Frequency-cap observations corroborate throttling: the prime policy starts
processes at 4.474 GHz maximum and ends the first three at 2.246 GHz. The final
YNNPACK process ends at 1.958 GHz. Its prompt-1024 request means increase from
35.12 to 45.48 and 44.83 ms. Battery temperatures and both CPU policies are
retained per process; snapshots are not execution-window average frequencies
or CPU temperatures. A 60-second cooldown does not provide fixed-clock isolation.

## Diagnostic attention breakdown

These fresh profiles have one warmup and one measured request per case, no CPU
sampling, and no output dumps. YNNPACK also writes its scheduled pipeline.
Global history ranges are 18–49, 513–544 and 1025–1056 for the three prompts;
local history is capped at 512. Values below are **summed worker milliseconds**,
averaged over 32 subsequent decode steps. They are not decode latency.

| YNNPACK SDPA callback work | Prompt 17 | Prompt 512 | Prompt 1024 |
| --- | ---: | ---: | ---: |
| KV dequantization | 0.102 | 5.711 | 8.077 |
| Packing | 0.069 | 6.626 | 10.626 |
| QK matmul | 0.526 | 5.359 | 7.451 |
| PV matmul | 0.284 | 3.930 | 5.875 |
| Mask / softmax / other | 0.205 | 1.660 | 2.105 |
| Total | 1.186 | 23.286 | 34.135 |

At prompt 1024, dequantization plus packing contributes 18.70 of 34.13 worker
ms. The earlier same-binary sampled profile gives 56.1%; the fresh profile gives
54.8%. This fraction describes attention callback work, not an achievable
full-model speedup.

The union of all attention callbacks covers **0.717 / 8.089 / 11.225 ms** of the
three diagnostic steps' average wall intervals. Category unions overlap and
cannot be added. Complete diagnostic steps take 26.676 / 41.869 / 47.454 ms,
including instrumentation. At prompt 1024 the disjoint wall partition is:
11.091 ms attention callbacks only, 24.370 ms other callbacks only, 0.134 ms
overlap, and 11.859 ms outside callbacks. Gaps include scheduling, allocation,
synchronization, host work and profiler overhead; they are not assigned to
attention. This is coverage accounting, not critical-path attribution.

Native diagnostic attention-stage wall time is **0.622 / 2.933 / 5.097 ms**.
Its combined QK/PV operator wall time is 0.428 / 2.218 / 4.191 ms; INT8 format
conversion contributes 0.050 / 0.443 / 0.541 ms. Native operator time includes
dispatch and joins, and native also warms during the process. These quantities
have different scopes from YNNPACK worker time and callback coverage.

## What the graph and schedule establish

E2B has eight query heads, one KV head, 28 local and seven global attention
layers, and 15 KV owners. At decode, YNNPACK's Q tensor is `[1,8,1,D]` and its
probability tensor is `[1,8,1,H]`: eight batch entries, each with `M=1`. Native
uses `[1,1,8,D]` and `[1,1,8,H]`, giving `M=8` against the same KV head.
The checked-in [value declarations](../../models/gemma4_e2b/generated/gemma4_decode_DefineValues_1.cc)
and [SDPA builder](../../models/gemma4_e2b/generated/gemma4_decode_RopeTablesToLayer2_4.cc)
show the current YNNPACK shapes and explicit dequantization.

The same verified binaries' retained
[endpoint kernel samples](../2026-10-07-upstream-refresh/kernel-samples.json)
identify `dot_fp32_1x64x4_1x4x1_neon` in YNNPACK attention and
`xnn_f32_qc8w_gemm_minmax_ukernel_6x8__asm_aarch64_neonfma_ld128` in native.
Combining query heads into rows can permit a multi-row kernel to reuse KV loads
across queries. Its benefit in this YNNPACK graph remains to be measured.

KV preparation is already shared: each diagnostic case has 30 dequantization
and 30 packing call sites, all attributed to the 15 owner layers. Their
execution is tiled: at prompt 1024 they produce 699 dequantization and 171
packing callback events per step. Later layers sharing KV reuse prepared
operands. A retained dequantization origin on a later FP32 dot does not prove
that the dot performs another conversion.

Preparation still reprocesses the visible history on each decode invocation.
At prompt 1024, the mean logical visible owner KV payload is about 6.05 MiB as
INT8, versus 24.19 MiB as FP32, before packing. These are logical operand data
volumes; tiled buffer lifetimes, padding and caches prevent interpreting them
as simultaneous RSS or measured DRAM traffic. Native also performs conversion
to its quantized format and packing, but avoids a full FP32 KV representation.

The dot implementation uses fixed 32-KiB L1 and 128-KiB L2 budgets, explicitly
marked as experimental heuristics rather than CPUinfo-derived cache sizes.
The latter controls FP32 packing blocks in `define_pack_b`. This is another
tuning candidate, not evidence of incorrect Samsung CPU identification or a
measured benefit from changing that budget.

[Pipeline excerpts](pipeline-excerpts.txt) show local bounds ending at
`min(position,511)` and global bounds ending at `position`. At prompts 512 and
1024, local QK/PV callback counts remain 448/224 per step; global QK counts rise
from 168 to 280. Global QK+PV worker time grows from 3.06 to 6.57 ms, while
local QK+PV moves from 6.23 to 6.75 ms under changing thermal conditions.
The schedule uses valid history, appends only new KV, and records zero
history-view copies. Capacity invariance is covered by the separate
[fixed-input capacity check](../2026-10-08-capacity-sweep/README.md).

## Concrete follow-up experiments

1. **Query heads as matrix rows.** Keep INT8 state and the present FP32 numerical
   path. For E2B decode, view Q as `[1,1,8,D]` for QK, then restore scores to
   `[1,8,1,H]` before the causal/window mask. View normalized probabilities as
   `[1,1,8,H]` for PV and restore its output afterward. All eight queries have
   the same position; the mask must not treat them as eight consecutive tokens.
   For models with multiple KV heads, combine only query heads sharing a KV
   head and retain physical cache strides. Start with a standalone attention
   experiment, then regenerate the author and validate full-model/state outputs.
2. **Fuse conversion with packing.** Preserve INT8 KV codes/scales and the
   current FP32 dequantization boundary, while producing the packed FP32
   operand directly. Measure the removed intermediate buffer/copy cost and
   ensure shared owners still prepare once. Vary the packing budget separately
   from this change rather than attributing both to fusion.
3. **Direct FP32×INT8 attention.** Investigate mixed-type QK/PV kernels to avoid
   full FP32 KV expansion. Validate scale placement, rounding, logits and KV
   codes explicitly. This is a backend arithmetic/kernel experiment; it must
   not silently change QAT activations or quantize queries differently.

Use separate dependency/build copies, unprofiled latency and diagnostic
captures, and controlled clocks or paced, separately cooled cases. Preserve
empty/nonzero history, window crossings, partial chunks, multi-head strides,
reset and capacity invariants. Report each experiment independently before
combining changes. No speedup from these candidates is claimed here.

## Harness validation

The analyzer now separates SDPA work by case/history and partitions overlapping
wall intervals without double charging them. Tests cover parallel overlap,
missing attention in a case, and mixed/eliminated operation origins.
The investigation also found and fixed a summary bug: native's status-only
`run.json` could override a diagnostic flag in its request files. Any explicit
invalid timing flag now keeps the capture diagnostic. Historical profile tables
were already labeled and kept separate from unprofiled throughput.

All **43 Python tests pass**. Every process succeeded; argmax sequences agree
within each engine/case across both orders and the diagnostic capture. This is
self-consistency evidence, not cross-engine logits/KV or generation-quality
validation. No model/backend arithmetic changed; the stronger numerical checks
in the [October 7 report](../2026-10-07-upstream-refresh/README.md) retain their
original input scope.
