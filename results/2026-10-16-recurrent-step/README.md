<!-- Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0 -->

# Reusable recurrent-step CPU experiment — 2026-10-16

A prepared ordinary YNNPACK graph correctly implements a gated-delta token
step, without a custom recurrence operator or sequence-length graph expansion.
The tested full-state step **does not qualify as a performance replacement**.
Adapter bypass makes little difference; state locality and primitive scheduling
need further work. This is a component experiment, not full-model timing.

The [standalone fixtures](../../tests/generated/recurrent_step/README.md) and
[harness guide](../../docs/RECURRENT_STEP_EXPERIMENT.md) reproduce the experiment
without private compiler dependencies. The primary graph has 21 tensor
operations independent of sequence length. A C++ harness executes the same
construction commands as the emitted `.ynn`; Rust front-end overhead is excluded.

## Contract and correctness

B=1, Hk=16, Hv=32, Dk=Dv=128. Inputs/state are FP32; Q/K are normalized and the
initial state is nonzero. Primitive state is K-major `[B,Hv,Dk,Dv]` with
contiguous V; alternative persistent layouts were not measured. All token outputs and final state are materialized.
No projections, normalization, convolution, weights or quantization are timed.
Length 1024 is 1024 recurrent updates, not full-model TTFT.

All 102 numerical/state cases and 50 input-immutability/invalid-write cases pass
on each device. Coverage includes 512/1024 tokens, every primitive intermediate
state, partial/padded/empty valid rows, reset, chunk handoff, multiple batches,
arbitrary head maps, unequal widths, tails and strong decay. The independent
reference uses FP64. Maximum observed error is 1.304e-7, below the primary
2e-5 absolute limit; edge cases permit 2e-5 absolute plus 2e-5 relative error.
All timed processes also pass reference checks. Input hashes match between
platforms at all primary lengths. See [validation](validation-summary.json).

## Matched timings

Milliseconds per layer/sequence, lower is better. `custom` is the existing
whole-sequence recurrence; `custom step` invokes it once per token. Primitive
adapter/native paths use the same graph, with normal adapter checks or one-time
fixed-shape native setup. Two state buffers alternate without input/output aliasing.
The llama.cpp control runs `ggml_gated_delta_net`; setup maps grouped heads and
transposes state to its native layout. Timed results remain in that layout.

| Target | Threads | Tokens | Custom ms | Primitive adapter ms | Primitive native ms | Custom step ms | llama.cpp ms | Native gate |
| --- | ---: | ---: | ---: | ---: | ---: | ---: | ---: | --- |
| host | 1 | 1 | 0.122068 | 0.194103 | 0.193313 | 0.122508 | 0.173628 | FAIL |
| host | 1 | 17 | 1.015178 | 3.777649 | 3.752851 | 2.132965 | 1.945580 | FAIL |
| host | 1 | 32 | 1.651611 | 7.040675 | 7.068180 | 3.932750 | 3.434739 | FAIL |
| host | 1 | 128 | 6.612159 | 28.041101 | 28.042217 | 15.793040 | 13.500384 | INCONCLUSIVE |
| host | 1 | 1024 | 57.448993 | 226.331150 | 225.075585 | 126.200063 | 115.573822 | FAIL |
| host | 4 | 1 | 0.034787 | 0.061988 | 0.061589 | 0.034807 | 0.042815 | FAIL |
| host | 4 | 17 | 0.243788 | 1.291287 | 1.276460 | 0.657397 | 0.477921 | FAIL |
| host | 4 | 32 | 0.429105 | 2.441439 | 2.395839 | 1.246971 | 0.883205 | FAIL |
| host | 4 | 128 | 1.644132 | 9.703213 | 9.599981 | 4.932148 | 3.656711 | FAIL |
| host | 4 | 1024 | 14.782710 | 79.054571 | 77.428029 | 40.162079 | 28.768132 | FAIL |
| arm | 1 | 1 | 0.962587 | 0.318239 | 0.311869 | 0.960001 | 0.181398 | FAIL |
| arm | 1 | 17 | 12.283115 | 5.633647 | 5.531315 | 17.801468 | 1.923198 | FAIL |
| arm | 1 | 32 | 22.727073 | 10.467194 | 10.498415 | 33.796670 | 3.607795 | FAIL |
| arm | 1 | 128 | 88.924599 | 39.574826 | 41.192869 | 135.547687 | 14.080074 | FAIL |
| arm | 1 | 1024 | 732.173129 | 338.177365 | 316.710126 | 1070.376210 | 121.718996 | INCONCLUSIVE |
| arm | 4 | 1 | 0.369697 | 2.031265 | 1.954564 | 0.369375 | 0.070410 | INCONCLUSIVE |
| arm | 4 | 17 | 4.093221 | 35.763376 | 33.923164 | 14.524985 | 0.848400 | INCONCLUSIVE |
| arm | 4 | 32 | 7.603964 | 63.334094 | 62.593677 | 27.814943 | 1.570517 | INCONCLUSIVE |
| arm | 4 | 128 | 32.535701 | 255.328170 | 250.637471 | 112.849334 | 6.390559 | FAIL |
| arm | 4 | 1024 | 260.481903 | 2200.098735 | 2120.403879 | 905.497898 | 52.134085 | INCONCLUSIVE |

Native gates: host 9 FAIL, 1 INCONCLUSIVE; arm 5 FAIL, 5 INCONCLUSIVE. Adapter gates and every directional ratio are retained in the JSON. 0 of 40 candidate/configuration comparisons passed the performance gate.

Every process uses five warmups and five batches lasting at least 200 ms. Run
forward and reverse engine orders. If any paired medians differ by over 5%,
repeat all five engines once and use that pair for every engine. Remaining
instability makes the affected comparison inconclusive. x86 gates require
<=1.10 times custom latency in each direction; ARM requires that limit against
both custom and llama.cpp. No best-of selection. Raw samples and direction-level
ratios are retained in [timing-summary.json](timing-summary.json) and the two
platform timing JSONL files. Setup/reference checks are excluded; bindings,
invocation, state handoff and output writes are included.

## Findings

The subsequent [layout and chunkwise experiment](../2026-10-17-recurrent-followup/README.md)
executes the focused next work from this evaluation. This record retains the
original baseline, findings and limits.

- At four x86 threads and 1024 tokens, custom-whole is 14.783 ms, custom-step
  40.162 ms, and primitive-native 77.428 ms. Invocation granularity and loss of
  cross-token state locality matter; primitive execution adds a further gap.
  The custom-step ablation does not isolate dispatch from memory effects.
- The [x86 schedule](step-native-t4.pipeline.txt) materializes decayed-state and
  outer-product intermediates, then runs the output reduction in another
  parallel loop. The state is 2 MiB. The x86 custom sequence kernel retains
  compact state tiles across tokens.
- The [ARM schedule](arm-step-native-t4.pipeline.txt) additionally calls `pack_b`
  for changing state at both dot operations each token. Actual selected kernels
  are `dot_fp32_1x32x1_1x8x1_fma3` on x86 and
  `dot_fp32_1x64x4_1x4x1_neon` on ARM. The instrumented diagnostic binary is
  separate from timing. Scratch counts are allocator observations, not DRAM
  traffic or isolated packing costs.
- The custom recurrence has an explicit AVX2 specialization, with a portable
  fallback on ARM. Beating that fallback does not meet the ARM target: the
  independent llama.cpp control remains necessary.
- The initial singleton-reshape author failed on both native and adapter
  invocation. Explicit `ExpandDims` for broadcast axes avoids it on this tested
  backend. General singleton `SplitDim` broadcasting is not certified or fixed.

## Focused ARM follow-up

The [post-qualification diagnostic](focused-arm-summary.json) removes the core-class
confound: one thread on CPU 2 has paired medians 0.468/0.493 ms, versus
1.638/1.918 ms on CPUs 2–5 at four threads, for a single primitive step. The
regression persists within the same core class, although the four-thread result
is still variable. These additional runs do not replace the qualification pairs.

Explicit user-space sampling (`cpu-cycles:u`) succeeded: 7,239 samples, none lost.
Packing accounts for 31.18% of inclusive user cycles, with call chains through
`ynn::packer::pack` and tiled transpose/copy into `memmove`. Exclusive `memmove`
is 29.84%; those percentages overlap and must not be added. Dot and three main
elementwise kernels together account for 51.28% of exclusive user cycles.
The short profile includes startup/reference checks and is not used for timing.

A separate unprofiled run reports 5.18 seconds elapsed, 7.91 user CPU seconds and
9.34 system CPU seconds, summed across threads. About 54% of accumulated CPU
time is in the kernel; this is not a wall-time percentage. Default hardware and
task-clock event requests failed, while explicit user-space cycles worked.
Without kernel/syscall attribution, allocation, synchronization and other
system-cost shares remain unresolved. Packing is a demonstrated target, but
packing alone is not a sufficient explanation of the parallel regression.

The next experiments should compare persistent K-major/V-major state layouts
without hidden handoff transposes, improve rounding-preserving step fusion and
state-local scheduling, and investigate the ARM parallel regression and dynamic
GEMV packing. Then evaluate algebraic chunkwise
prefill with explicit numerical permissions. Wrapping this same full-state body
in a runtime loop does not automatically give chunkwise math or cross-iteration
tiling. No default lowering or model package was changed, and this CPU study
makes no MLDrift/GPU claim.

## Provenance and reproduction

[Provenance](provenance.json) records backend revisions, local patch fingerprints,
source/binary hashes and fixture identities. Dependencies match the qualified
YNNPACK `0a66ebb` / Slinky `a3eec6f` source manifests, not the stale default
extracted dependency directory. llama.cpp is `cd0e361`, without source changes.
The lab working tree is dirty; HEAD alone does not describe the binary.

Intel i9-12900K uses Clang 22.1.8 and CPU 0 or CPUs 0/2/4/6. Pixel 11 / Android 17
uses NDK r28c, ARM64/API 28/static libc++, and CPU 6 or CPUs 2–5. Phone masks use
different core classes; their ratio is not pure thread scaling. Clocks remain
governor-managed; [device snapshots](device-snapshots.json) retain battery
temperature and before/after frequencies, not continuous CPU thermals. Timings
run sequentially without concurrent builds or competing experiments.

The custom/harness compilation disables implicit contraction; YNNPACK uses
`NO_EXCESS_PRECISION`. ggml uses native SIMD and may differ in FMA/reduction
order; FP64 checks qualify numerical accuracy rather than bit identity. Fresh
ggml builds use OpenMP off, native host flags, and ARM
`armv8.2-a+dotprod+fp16`. Earlier exploratory runs with stale dependencies or
library-dependent random-float generation are excluded from these tables.

Build the optional targets as described in the harness guide. For each engine,
length 1/17/32/128/1024 and thread count 1/4, run sequential matched orders:

```sh
taskset -c "$CPUS" "$BUILD/recurrent_step_bench" \
  --engine="$ENGINE" --rows="$TOKENS" --threads="$THREADS"
adb -s "$ANDROID_SERIAL" shell \
  "LD_LIBRARY_PATH=$REMOTE taskset $MASK $REMOTE/recurrent_step_bench --engine=$ENGINE --rows=$TOKENS --threads=$THREADS"
```

Use `--batches=0` for correctness only. The public records contain runtime
measurements and standalone artifacts; graph authors and compiler provenance
remain in the private companion.
