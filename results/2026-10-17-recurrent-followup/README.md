# Recurrent layouts, scratch reuse and chunkwise prefill — 2026-10-17

Ordinary YNNPACK operators can now match the retained optimized recurrence
controls for **1024-token prefill** on both tested CPUs. This requires an
algebraic chunk algorithm, and on Pixel 11 also reusable scratch storage.
The single-token step path still does not qualify. Production model lowering
and dependency pins remain unchanged.

At four threads, the 32-token chunk graph takes **15.765 ms** on x86 versus
**15.270 ms** for the custom kernel, within the 10% acceptance limit. On Pixel
11 it takes **40.753 ms** versus **52.225 ms** for llama.cpp, about 22% less
time. These are recurrence-component measurements for one layer, not full-model
prefill/decode, TTFT or token-throughput measurements.

## What was tested

The original K-major primitive step is retained as a control. New candidates
include persistent V-major state, a multiply/reduce spelling of the step, a
32-value state tile outside the token loop, and fixed 16/32/64-token algebraic
chunk graphs. All candidate arithmetic executes ordinary YNNPACK operators;
none hides a recurrent callback behind a decomposition. The tile control
reuses one prepared graph per worker and does not add architecture intrinsics.

The successful chunk paths retain **K-major recurrent state**, `[B,Hv,Dk,Dv]`.
This is the recurrent matrix, not a transformer KV-cache layout conclusion.
No new generic loop operator is required to represent these fixed chunks.
The graph is reused for every chunk, including the 1024-token input; node count
does not grow with total prompt length. Tail padding, tail copies, bindings,
output writes and state handoff are timed. Initial layout conversion for the
V-major/llama controls remains setup work.

Chunkwise math explicitly permits reassociation across tokens. For cumulative
log-decay G and causal decay matrix D, it solves the lower-triangular system
`(I + beta*(K K^T)*D_strict) U = beta*(V - exp(G)*(K S0))`, then forms all
outputs and next state with matrix products. The inverse uses blocked triangular
inversion, not recurrent-token unrolling. The tested domain has normalized
Q/K, beta in `[0,1]`, finite nonpositive log-decay and finite FP32 state.

The first solver used nilpotent power doubling. It passed random tests but
its author-level FP32 evaluation failed identical unit keys with beta one and zero decay: width 32 reached
0.25 absolute error; width 64 exceeded `6e8`. Large alternating powers suffered
catastrophic FP32 cancellation. That prototype is rejected. The retained
blocked inverse passes that stress case. Upper-triangle decay differences are
clamped before exp, avoiding `0*inf` under strong decay.

## Correctness

**810 native cases passed:** 270 per CPU across the six candidates with the
default allocator, plus 135 per CPU with scratch reuse for the original step
and the 16/32-token chunks. All 42 standalone plans parse. Independent author
tests cover six geometries, three input regimes and five full-graph variants.

Native coverage includes batch two, grouped/arbitrary head mappings, unequal
and tail widths, nonzero/reset state, strong decay, beta zero/one, identical
keys, valid-zero/partial requests, invalid requests, immutable input tensors,
output/state canaries, and lengths through **1024**, including a 1023-valid tail.
Every output and final state is checked against independent FP64 recurrence.
Full step graphs additionally check every intermediate state; chunks check
each chunk-boundary state. The tile-interchanged path checks all outputs and
final state. Largest error in the default-allocator sweep: `2.133e-6` on x86,
`1.985e-6` on Pixel, below the existing `2e-5` absolute primary tolerance.
The broader fixtures use `2e-5 + 2e-5*abs(reference)`.

An additional 50 immutable-input/invalid-write regression cases per CPU passed;
primary input hashes also match between host and phone. The control logs are
[host](host-regression.log) and [Pixel](arm-regression.log).

Every timed process repeats numerical/state checks outside its timer. The
harness and custom kernel use `-ffp-contract=off`; native graphs retain
`NO_EXCESS_PRECISION`. SIMD reduction/FMA order can differ. Chunkwise
reassociation is an additional explicit permission, not bitwise equivalence.
No full-model quality, quantization or GPU acceptance is claimed.

## Paired qualification

Five warmups and five batches of at least 200 ms per process, forward/reverse
engine order. If any engine's two medians differ by more than 5%, repeat the
whole group once and use that repeat for every engine. Continued instability
is **INCONCLUSIVE**, never a best-of selection. Cells below pool the selected
pair's samples; the gate checks each direction separately. Full direction
values and stability flags are in [timing-summary.json](timing-summary.json).

x86 must be no more than 1.10x the custom control; Pixel must be no more than
1.10x **both** custom and llama. The ARM custom kernel is a portable fallback,
so its large gap alone is not acceptance evidence.

**Allocator difference:** all x86 qualification uses the default allocator.
All Pixel native candidates in this table enable `STEP_SCRATCH_POOL=1`.
That option leaves the custom and llama controls unchanged. Default-allocator
screens remain in [screening.json](screening.json). C64, V-major and tiled paths
were screened but not promoted to ARM qualification. V-major also underwent
the full x86 paired run and failed or was inconclusive in every group.

| CPU | Threads | Tokens | Custom ms | Primitive step ms | Chunk16 ms | Chunk32 ms | llama ms | C16 gate | C32 gate |
| --- | ---: | ---: | ---: | ---: | ---: | ---: | ---: | --- | --- |
| x86 | 1 | 1 | 0.127 | 0.198 | 0.843 | 1.767 | 0.172 | FAIL | FAIL |
| x86 | 1 | 17 | 0.948 | 3.424 | 1.671 | 1.823 | 1.974 | FAIL | FAIL |
| x86 | 1 | 128 | 6.879 | 25.494 | 5.601 | 5.744 | 13.794 | INCONCLUSIVE | INCONCLUSIVE |
| x86 | 1 | 1024 | 54.760 | 207.404 | 46.405 | 48.042 | 120.940 | PASS | PASS |
| x86 | 4 | 1 | 0.036 | 0.063 | 0.412 | 0.738 | 0.045 | FAIL | FAIL |
| x86 | 4 | 17 | 0.250 | 1.104 | 0.819 | 0.743 | 0.507 | FAIL | FAIL |
| x86 | 4 | 128 | 1.651 | 8.420 | 2.215 | 1.840 | 3.637 | FAIL | FAIL |
| x86 | 4 | 1024 | 15.270 | 67.885 | 19.003 | 15.765 | 29.652 | FAIL | PASS |
| Pixel | 1 | 1 | 0.957 | 0.213 | 1.029 | 2.097 | 0.182 | FAIL | FAIL |
| Pixel | 1 | 128 | 89.226 | 29.221 | 8.431 | 8.522 | 14.077 | PASS | PASS |
| Pixel | 1 | 1024 | 735.511 | 234.725 | 67.573 | 68.024 | 120.657 | PASS | PASS |
| Pixel | 4 | 1 | 0.387 | 0.176 | 0.801 | 1.352 | 0.072 | FAIL | FAIL |
| Pixel | 4 | 128 | 32.042 | 16.563 | 5.840 | 5.168 | 6.382 | PASS | PASS |
| Pixel | 4 | 1024 | 260.814 | 130.950 | 47.868 | 40.753 | 52.225 | PASS | PASS |

There are 132 x86 and 70 Pixel qualification processes, all numerically valid.
The one-thread x86 128-token group remains inconclusive because its custom
control was unstable after the mandated repeat. The four-thread Pixel
single-token primitive path also remains unstable. Neither is reported as a
performance pass. Chunk graphs are not a suitable single-token lowering.

## Scratch lifecycle explains much of the ARM regression

A separate unprofiled A/B/B/A control used the **same binary, graph, input,
four-thread affinity and math**, with five one-second batches per process.
Only the native scratch allocator changed. Medians were:

| Order | Scratch | Step ms | Real s | User CPU s | System CPU s |
| ---: | --- | ---: | ---: | ---: | ---: |
| 1 | Default | 2.082096 | 5.21 | 8.07 | 9.37 |
| 2 | Reuse | 0.125352 | 5.18 | 18.17 | 1.69 |
| 3 | Reuse | 0.123138 | 5.15 | 18.37 | 1.45 |
| 4 | Default | 2.086641 | 5.22 | 8.19 | 9.22 |

Recycling scratch improves this step by about **16.7x**. Kernel time falls from
about 54% to 7–9% of accumulated user+system CPU time. Those CPU times sum
across threads and are not percentages of wall time. The control establishes
scratch allocation/reuse as a major cause of this configuration's regression;
it does not isolate mmap, page faults, allocator internals, synchronization or
cache effects individually. We did not patch Scudo or the thread pool.

Separate one-second process snapshots showed VmHWM 23,880 KiB without reuse
and 24,036 KiB with reuse, in this one-step fixture. These are process-level
snapshots, not a general pool-memory bound. The pool retains shape/alignment
classes until runtime destruction; production adoption still needs retention
limits and broader memory/concurrency testing.

## Layout, packing and fusion evidence

The actual ARM step kernel changes from
`dot_fp32_1x64x4_1x4x1_neon` (M=1,N=128,K=128) to
`dot_fp32_8x4x4_1x4x1_neon` (M=128,N=1,K=128) for V-major.
The latter packs the small K/Q vectors instead of the full changing state.
This does **not** make it a completely unpacked GEMV: the pinned NEON FP32
registry lacks `unaligned_b`, and `should_pack_b` requires that capability to
skip packing. Multiply/reduce authoring also ends up using dot kernels.
Merely renaming the source operations does not bypass that backend choice.

V-major did not improve the decisive measurements. On x86 four-thread
1024-token runs it took 74.230 ms versus 67.885 ms for the original primitive
layout. On the Pixel four-thread pooled 128-token screen it took 17.55 ms
versus 17.07 ms for the original primitive. The tile-local screen took
20.62 ms. These remain rejected candidates, despite eliminating full-state
packing or reducing heap scratch.

The full-step schedules still have separate state-update and output-dot
parallel loops. The scheduler deliberately prevents producers of external
outputs from being fused into consumer loops without correctly cropped
output regions. The tile control keeps those operations near a small state
tile, but still has separate native callbacks and many bindings/invocations;
it is **not** a new fused update/output kernel. Some tile schedules also copy
the small state result to its external output. Rounding-preserving multi-output
fusion remains open.

The 32-token chunk uses the existing ARM
`dot_fp32_5x16x4_1x4x1_neon` matrix kernels and x86
`dot_fp32_6x16x1_1x8x1_fma3`. Its FP32 math is amortized over a chunk. It still
computes dense masked triangular products and allocates intermediates; it is
not an optimized triangular-solve implementation. Diagnostic callback peaks
were about 4.85 MB for this chunk versus 1.05 MB for the original full step
and 0.79 MB for V-major at four threads. Callback allocation counters do not
measure DRAM traffic, stack storage or total retained pool memory.

## Decision and next work

1. Keep high-level recurrence semantics and explicit numerical permissions.
   Ordinary tensor graphs are sufficient for competitive **prefill on these
   CPUs**, with blocked chunk algebra and appropriate scratch lifetime. A
   black-box loop over the original full-state step was not sufficient.
2. Carry the scratch-reuse finding into a bounded prepared-workspace design,
   with live-allocation separation, alignment, worker safety and retention
   limits. Do not simply replace the production allocator with this probe.
3. For decode, investigate generic multi-output producer/consumer fusion with
   correct external-output cropping, and an ARM dynamic GEMV kernel contract
   that can avoid packing. Preserve the existing state/update rounding
   contract. The current experiment did not implement either backend feature.
4. Before changing model lowering, qualify the chunk candidate against actual
   recurrent-layer inputs and full-model logits/state, with both normal and
   correlated/long-history inputs. Keep custom decode/short-prefix fallback;
   chunk width should be a backend policy, not a new model-specific operator.
5. Defer broad generic control flow until its scheduling/state contract has a
   concrete consumer. Future loops must expose state dependence, independent
   tiles, aliasing and workspace lifetime. No model regeneration or GPU/MLDrift
   conclusion is part of this component experiment.

## Reproduction and retained evidence

Use the [experiment guide](../../docs/RECURRENT_STEP_EXPERIMENT.md), the standalone fixtures and the
recorded [runtime identities](runtime-provenance.json).
XNNPACK/YNNPACK is `0a66ebb5817fce48df605451444dcfc27a5e4ee4`; Slinky is
`a3eec6fcfe3093be04d6c3d7dcab7d4e70bdd0dc`, with the same previously qualified
local patches. Complete source manifests match the earlier baseline; no new
backend patch was applied. llama.cpp is
`cd0e36153b3f669d3e20ad2eb59ece6f5c8e23f5`, with no local source changes.

Host: Intel i9-12900K, Clang 22.1.8, CPU 0 or CPUs 0/2/4/6. Pixel 11:
Android 17, NDK r28c, ARM64/API 28/static libc++, CPU 6 or CPUs 2–5. These
phone affinities use different core classes, so their ratio is not a pure
thread-scaling measurement. Clocks remain governor-managed. Device snapshots
are before/after observations, not continuous CPU thermals or clocks.
ggml uses the retained OpenMP-off builds, host native flags and ARM
`armv8.2-a+dotprod+fp16`. Builds/profiles do not overlap qualification timing
on the same device. The large generated builder is unoptimized only during
graph construction; native execution/kernel flags remain unchanged.

This record includes [correctness](correctness.json), [screening](screening.json),
[paired timings](timing-summary.json), [allocator control](allocator.json),
and [kernel/scratch observations](diagnostics.json). The `schedules/` directory
retains actual host/ARM pipelines. Full commands, raw samples, rejected
prototypes and frozen exact compiled sources/binaries are retained separately.
