<!-- Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0 -->

# October 7 upstream refresh: mobile baselines

Adopts upstream XNNPACK `d297c798ea530c12a1878bb3a3a811bdf05d715b`, captured
on October 7, 2026, including the merged
[learned dot cost model](https://github.com/google/XNNPACK/pull/11568).
Fresh Android builds compare it with the previous normal pin
`f5122810ee8bb7461ed73efe7a678a472866cee3`, using the same current builders,
token IDs and build flags. Historical baselines remain unchanged.

Samsung's short-prompt decode improves and approaches the preserved native
runner, but its long-history native gap remains. TECNO E4B improves prefill much
more than decode. The longer-rest Pixel four-thread long-prompt decode pair is
essentially unchanged; its other timing observations remain sensitive to throttling.
The observed INT2 DOTPROD switch follows an upstream kernel-availability change;
it does not demonstrate a corrected one-row cost fit. Native comparisons retain
material numerical and execution-contract differences, documented below.

The primary matrix contains **270 measured requests**. Focused
repeats with longer cooldown intervals add **42 requests**, retained
as a separate round rather than pooled into the main matrix. There are **104 configurations** in total,
**32 separate diagnostic profiles** and **1764 arithmetic-checked
kernel trials**. The Linux host was busy: local Linux and host-only HF binaries
were neither rebuilt nor retimed. E4B runs on TECNO; Pixel/Samsung E4B were
skipped because their available RAM was below the previously measured approximately 4.5-GiB footprint.

## Fresh long-prompt comparison

Prompt 1024, capacity 2048, four threads; three measured requests after one
warmup. E2B has 32 forced continuations, E4B has 16. Rates are reciprocals of
mean subsequent-token latency, excluding the first-logit step. These rows use
the primary round; see the reverse-order repeats below and request ranges in
[metrics.csv](metrics.csv).

| Model / device | Previous decode, tok/s | New decode, tok/s | Native decode, tok/s | New/native latency | New warm TTFT, s | Native warm TTFT, s |
| --- | ---: | ---: | ---: | ---: | ---: | ---: |
| E2B / tecno | 17.33 | 16.61 | 24.95 | 1.50× | 3.580 | 2.337 |
| E2B / pixel | 9.67 | 9.97 | 21.15 | 2.12× | 4.556 | 3.099 |
| E2B / samsung | 19.48 | 20.70 | 40.94 | 1.98× | 2.805 | 1.349 |
| E4B / tecno | 6.59 | 6.57 | — | — | 12.058 | — |

The native control is the preserved lab-authored Tensor API/XNNPACK runner,
retimed with verified original assets. It uses `qp8_all`, preserves static
INT2, reuses runtimes/workspace, and uses KV alignment 32. Its packed-dynamic
FC policy differs from YNNPACK's static QAT activations. Native prompt timing
includes KV allocation/reset; YNNPACK resets prepared state before prefix timing.
Native uses chunk 16 for prompt 17 and chunk 128 for longer prompts, padding
partial final prefix chunks and aligned attention extents where needed. YNNPACK
runs at most 128 real rows without padding and attends over real live history.
The real input IDs/continuations match; execution chunk policies still differ.
Neither timing includes process startup or graph preparation. There is no matched
E4B native phone artifact in this campaign.

The primary TECNO E2B long-prompt case improves warm TTFT from 4.312 to 3.580 s,
while subsequent-token latency moves from 57.72 to 60.19 ms (4.3% higher).
The unlocked-clock matrix does not isolate this small decode change. The update
therefore does not show a universal mobile decode improvement.

Samsung one-thread decode, capacity 2048, primary round:

| Prompt | Previous, ms/token | New, ms/token | Observed latency reduction |
| ---: | ---: | ---: | ---: |
| 17 | 67.65 | 49.66 | 26.6% |
| 128 | 62.47 | 45.54 | 27.1% |
| 1024 | 78.53 | 60.69 | 22.7% |

## Reverse-order checks with cooldown intervals

Primary processes group all three prompt lengths. Focused repeats use one prompt
per process, an initial 90-second cooldown, and 60 seconds between jobs. They
reverse the primary previous/new order for each thread count. Clocks remain
unlocked; this is a check on order/heat sensitivity, not a fixed-clock isolation
of an upstream commit. [Telemetry](telemetry.json) includes temperatures and
frequency observations before/after each process; those frequency snapshots are
not execution-window averages. Before each of the Pixel four-thread long-prompt
repeat processes, an additional five-minute idle period is enforced; exact
intervals are recorded in [additional-rest.json](additional-rest.json).

Pixel E2B, capacity 2048; each previous/new cell is ms per subsequent token:

| Threads | Prompt | Primary previous / new | Repeat previous / new | Repeat new latency change |
| ---: | ---: | ---: | ---: | ---: |
| 1 | 17 | 66.44 / 75.39 | 89.32 / 86.77 | -2.9% |
| 1 | 1024 | 90.00 / 104.19 | 219.97 / 169.97 | -22.7% |
| 4 | 17 | 65.60 / 49.24 | 67.16 / 62.89 | -6.4% |
| 4 | 1024 | 103.37 / 100.31 | 85.76 / 86.16 | +0.5% |

Pixel's one-thread long-prompt repeats remain heavily throttled despite the
initial cooldown convention. Before/after maximum-frequency observations on
core 8 fall from approximately 2.9 GHz to 1.164 GHz in both processes. The
new run's per-request mean decode latencies range from 132.49 to 244.84 ms;
the previous pin ranges from 167.75 to 254.94 ms. These observations show order
and thermal sensitivity; they do not establish the update's performance effect.
The longer-rest four-thread pair gives 85.76 ms/token previous versus 86.16 ms
new (0.5% higher). Its request means span 85.47–86.13 ms previous and
82.31–89.25 ms new. Both start with a 2.914-GHz maximum-frequency observation
and end at 1.885 GHz. This does not support a meaningful decode regression for
that case, and it does not isolate the update's effect on every Pixel workload.
The native Pixel control was retimed in the primary round; it was not repeated
in this longer-rest round.

Samsung E2B, capacity 2048, four threads; new → previous → native process order:

| Prompt | Previous, ms/token | New, ms/token | Native, ms/token | New/native latency |
| ---: | ---: | ---: | ---: | ---: |
| 17 | 24.41 | 20.08 | 19.71 | 1.02× |
| 1024 | 41.38 | 40.39 | 25.69 | 1.57× |

The Samsung repeat puts short-prompt decode close to native: 20.08 versus
19.71 ms/token, compared with 24.41 ms for the previous pin. At prompt 1024,
new/previous/native take 40.39/41.38/25.69 ms; the remaining native gap is
**1.57 times the latency**. The observed update gain is much smaller at long
history than at prompt 17. These are measured outcomes with unlocked clocks,
not an isolated estimate of a single upstream change.

TECNO E4B warm TTFT at prompt 1024 improves from 44.55 to 30.88 seconds with one
thread and from 15.55 to 12.06 seconds with four threads. Its four-thread decode
is essentially unchanged (151.78 to 152.24 ms/token). Prefill and decode therefore
need separate conclusions.

## What changed upstream

The previous pin already contained the premerge learned cost model. This update
is not a cost-model-only A/B. [The source-tree change list](upstream-changes.json)
records actual file differences between the two revisions, including:

- INT2 I8MM generation/registration is disabled until its `tile_k=8` packing can
  be rewritten to match the other INT2 kernels' `tile_k=16`. The lab removes its
  stale CMake target, which otherwise references a nonexistent generated file.
- Android scheduling targets four tasks per thread instead of two; provably
  single-iteration loops are marked serial more consistently.
- Dot activation transpose/fusion bounds, static-slice stride constraints and
  undefined physical extents change. Cortex-X2/X3 now map to the X4 cost model.
- ARM INT8 generation and x86 AMX fitting/selection also change. ARM coefficient
  headers, including Oryon's, are unchanged; one-row DOT fitting exclusions remain.

The known-row packing and symbolic-runtime patches remain in the normal baseline.
No optional ISA restriction is applied. CPUinfo retains its pin and the known
Pixel identification issue is not corrected in this campaign. The optional
one-row selection patch is rebased for applicability; INT2 I8MM is unavailable
in this revision, so that policy no longer offers an INT2 I8MM/DOTPROD A/B.

## Kernels and execution profiles

[Kernel samples](kernel-samples.json) filter 499-Hz `cpu-cycles:u` instruction
pointer samples to measured subsequent-decode graph/invocation intervals using
monotonic timestamps. [Execution summaries](execution-profiles.json) retain
worker time and callback interval unions separately from native operator wall
time, which includes dispatch/joins. E4B lacks operation-origin labels, so much
of its callback work is explicitly unattributed. Profiles and dumps are excluded
from every latency table.

The one-row benchmark uses deterministic synthetic INT8 activations and signed
INT2/INT4 matrices. It records selected kernels and candidate availability, with
cached tests on one packed matrix and streaming tests on working sets of at
least 32 MiB. Six N/K shapes use seven 100-ms trials per candidate/mode and
independent exact INT32 arithmetic checks. New INT2 records
report `i8mm_available=false` and `i8mm_predicted_ns=null`; unavailable kernels
have no fabricated timing. INT4 retains both candidates. Trial order alternates
where both candidates exist. See [kernel-summary.csv](kernel-summary.csv),
[raw kernel trials](kernel-timings.jsonl), and
[selector observations](kernel-selections.json).

TECNO and Pixel E2B samples use one-row INT2 and INT4 DOTPROD kernels, plus
INT8 I8MM. Their remaining native gap cannot be assigned solely to choosing
I8MM instead of DOTPROD for the low-bit FCs.

Samsung's new sampled decode uses
`dot_int8_int2_int32_1x32x16_1x4x16_neondot` for INT2 and
`dot_int8_int4_int32_2x32x8_2x4x8_neoni8mm` for INT4. Native samples include
`xnn_qs8_qc2w_gemm_minmax_fp32_ukernel_1x8c4__neondot` and
`xnn_qs8_qc4w_gemm_minmax_fp32_ukernel_1x16c4__asm_aarch64_neondot_ld128_2`.
The native attention path samples F32×QC8W GEMM; YNNPACK samples FP32 dot with
separate KV dequantization and packing. INT4 FC and live-history attention/packing
remain useful targets after the INT2 kernel availability change. In the Samsung
four-thread profiles, packing callback counts fall from 3,281 to 201 per short
decode step and from 3,422 to 342 per long-history step. The new backend reduces
callback fragmentation while history packing/dequantization still remains.

At M=1, N=256, K=1536 on Samsung, the new direct INT4 benchmark has cached
DOTPROD/I8MM medians of 5.78/7.75 microseconds, but streaming medians of
15.44/15.46 microseconds. This shape's cached win nearly disappears when cycling
through the larger packed-weight working set. Full-model epilogues, scheduling
and history still matter. Absolute kernel timing also drifts across the two
processes with unlocked clocks; an unchanged kernel generator is not evidence
of a code-caused speedup.

Samsung new-pin INT4, M=1: DOTPROD/I8MM latency ratios. Values below one
favor DOTPROD. Predictions use the same candidate shape; measured values are
ratios of the seven-trial medians, not full-model speedup estimates.

| N | K | Predicted ratio | Cached measured ratio | Streaming measured ratio |
| ---: | ---: | ---: | ---: | ---: |
| 384 | 256 | 1.269 | 0.741 | 0.745 |
| 256 | 1536 | 1.283 | 0.746 | 0.999 |
| 256 | 2048 | 1.284 | 0.746 | 1.055 |
| 256 | 4096 | 1.285 | 0.745 | 0.813 |
| 256 | 6144 | 1.285 | 0.745 | 0.813 |
| 256 | 12288 | 1.286 | 0.746 | 0.814 |

The model favors I8MM in all six shapes, while every cached measurement favors
DOTPROD. The streaming outcome depends on shape. Fit one-row kernels with
representative working sets and validate the full model before choosing a
general restriction.

Cycle percentages describe each profile's exclusive sampled work. They are not
kernel speed ratios or a full attribution of a model latency difference. Kernel
microbenchmarks omit scheduling, epilogues, activations and attention. Use the
unprofiled full-model measurements when comparing end-to-end decode.

The remaining targeted investigations are:

- **INT4 one-row selection:** fit partial I8MM row tiles and include one-row
  DOTPROD candidates; validate with larger working sets and full-model runs.
- **Live-history attention:** compare a path that consumes quantized KV directly
  with the current FP32 dequantization/packing path, preserving live bounds,
  physical strides and numerical checks.
- **Dispatch and preparation:** use low-overhead sampling for warmed scheduling,
  bounds evaluation and synchronization; investigate sharing prepared weights
  across phases separately from the warm execution gap.
- **Pixel measurements:** address CPU identification and stable thermal conditions
  independently. The noisy observations here cannot isolate their contributions.

## Setup and memory observations

These are the prompt-1024/four-thread primary processes. Setup is observed once
per process and reused in its request records; three requests are not three
independent setup measurements. [Preparation records](preparation.json) retain
existing construction and total-phase timers plus RSS snapshots. Total-phase
time includes construction; the timers are not additive. Labels distinguish
latency, correctness and diagnostic processes. RSS is the
process high-water mark, not the incremental memory cost of that prompt.

| Model / device | Previous setup, s | New setup, s | Native setup, s | New peak RSS, MiB | Native peak RSS, MiB |
| --- | ---: | ---: | ---: | ---: | ---: |
| E2B / tecno | 39.56 | 41.14 | 2.57 | 1685 | 2168 |
| E2B / pixel | 46.91 | 32.36 | 2.14 | 1684 | 2160 |
| E2B / samsung | 33.22 | 37.92 | 2.83 | 1683 | 2154 |
| E4B / tecno | 126.40 | 140.92 | — | 4494 | — |

Native shares prepared weights/workspace across phases. YNNPACK prepares phases
independently and has no packed-weight disk cache. Different activation policies
and residency histories also affect these observations. Setup remains a separate
large gap; it is excluded from the warm execution comparison and cannot explain
that measured gap.

## Numerical and state checks

Six weights-free C++ tests pass on each phone; the independent state suite
covers 198 invocations per device, including empty history, nonzero positions,
reset, multiple KV heads, partial chunks, window crossings and bounds. The packed
FC tests retain their existing rounding tolerance; the direct kernel benchmark
requires exact INT32 sums. [Device tests](device-tests.json) retain their results
and verified payload counts. All 32 Python tests and the clean GitHub CMake/CTest
workflow pass; [checks.json](checks.json) records those source-commit checks.
Linux CI testing is separate from skipped local Linux builds/performance; final
measurement-commit CI is reported on [pull request #3](https://github.com/snnn/ynnpack-model-lab/pull/3).

Full-model correctness uses E2B prompts 1/128/129/130/511/512/513/1024 and E4B's
additional prompt 8, four threads, two forced continuations, and two repeated
requests. Outputs are finite and repeated greedy IDs agree after reset. Dumps cover the first
repetition; repeated-request checks do not claim bitwise logit equality.
Capacity-only checks are exact: 744/744 files for E2B on each phone and
2,619/2,619 files for E4B on TECNO.
The new E2B outputs also match exactly across all three phones (744/744 files
in each TECNO/Pixel and TECNO/Samsung comparison). Every YNNPACK invocation
checks fresh KV append counts and zero history-view copy callbacks.

Comparisons below use previous/native as reference and new YNNPACK as candidate.
Full per-logit errors, centered cosine, KL and KV-code differences are retained
under [numerics/](numerics/); cross-phone checks are also retained.

| Comparison | Identical files | Greedy agreement | Maximum logit absolute error | Minimum centered cosine | Maximum KL(reference→new) | Different KV codes |
| --- | ---: | ---: | ---: | ---: | ---: | ---: |
| tecno-e2b-backend | 744/744 | 24/24 | 0.000000 | 1.000000 | 0.000000 | 0/81727488 |
| pixel-e2b-backend | 744/744 | 24/24 | 0.000000 | 1.000000 | 0.000000 | 0/81727488 |
| samsung-e2b-backend | 744/744 | 24/24 | 0.000000 | 1.000000 | 0.000000 | 0/81727488 |
| tecno-e4b-backend | 2619/2619 | 27/27 | 0.000000 | 1.000000 | 0.000000 | 0/255037440 |
| tecno-e2b-native | 90/744 | 19/24 | 14.600170 | 0.836372 | 2.309614 | 74053837/81727488 |
| pixel-e2b-native | 90/744 | 19/24 | 14.600170 | 0.836372 | 2.309614 | 74053837/81727488 |
| samsung-e2b-native | 90/744 | 19/24 | 14.600170 | 0.836372 | 2.309614 | 74053837/81727488 |

Native comparisons have minimum centered logit cosine 0.836372, maximum absolute
logit error 14.600170 and maximum KL 2.309614, with approximately 90.6% of retained
KV codes differing. These are material numerical differences despite 19/24 greedy
agreement. Exact capacity consistency is distinct from cross-backend agreement;
these teacher-forced checks do not establish equivalent free-generation/task quality.
See [validation.json](validation.json) for repeated-request checks and failures.
The archived native control's validity flag does not account for output dumps;
this campaign explicitly classifies those runs as correctness-only and excludes
their timings regardless of that flag.

## Reproduction and record contents

Build with NDK r28c, ARM64/API 28 and static libc++, following the root README.
The campaign uses two host build jobs; tokenizers and SME/SME2 are disabled,
while CPUinfo/DOTPROD/I8MM remain enabled. The missing INT2 I8MM kernel is an
upstream availability choice, not a global I8MM disable. Actual runner, builder,
backend flags, revisions, patch/model/fixture/binary identities are in
[identities.json](identities.json). Both backend source copies match their
verified archives plus the declared normal patches exactly. Weight codes and
scales are unchanged.

```sh
uv run --locked python tools/bootstrap.py --directory .deps/upstream --no-tokenizers
uv run --locked cmake -S . -B build-android-upstream -G Ninja \
  -DCMAKE_TOOLCHAIN_FILE="$ANDROID_NDK/build/cmake/android.toolchain.cmake" \
  -DANDROID_ABI=arm64-v8a -DANDROID_PLATFORM=android-28 \
  -DANDROID_STL=c++_static -DCMAKE_BUILD_TYPE=Release \
  -DLAB_DEPS="$PWD/.deps/upstream" -DLAB_ENABLE_TOKENIZERS=OFF \
  -DLAB_BUILD_DOT_BENCHMARK=ON
uv run --locked cmake --build build-android-upstream --parallel 2
```

To reconstruct the previous dependency tree, use the public pre-refresh commit
`fa6e613f5513c61a9027659b4c5a3fe247e3780c`'s bootstrap/pins/patches in a separate
checkout and dependency directory. Build the current lab sources against that
tree with `LAB_DEPS`, rather than replacing the current source artifacts.
The native control is an archived external artifact; its hashes/provenance are
recorded, and this repository does not build that runner.

[Commands](commands.json) use configurable device-work, asset and native-runner
placeholders. Resolve them on your machine and pass an explicit ADB serial.
[Hardware](hardware.json) records the actual affinity masks/topology; do not
reuse another phone's mask. Run one benchmark at a time per device. The
[fixtures](fixtures/) preserve the existing supplied token IDs and forced
continuations. Tokenization is disabled for these runs; each runner replays the
same IDs, checked against those files. The timing and teacher-forced correctness
checks do not evaluate free generation.

[Request records](requests.json), [per-process raw timings](timings/), and
[metrics](metrics.csv) exclude profiling/dump runs. Setup is reported separately
from warm TTFT. Peak RSS is a process high-water mark including preparation and
resident mappings; native one-prompt processes and YNNPACK three-prompt primary
processes have different residency histories. Account for cache/preparation
policies before comparing setup/RSS. Raw dumps, perf records, device serials,
process lists and local asset paths remain outside the published record.
Initial ADB command-length, fixture-placement and output-directory startup errors
were corrected before collecting the affected cases; those attempts produced
no retained timing observations. Every retained measured job completed successfully.
