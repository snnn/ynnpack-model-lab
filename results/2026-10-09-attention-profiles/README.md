<!-- Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0 -->

# Decode attention profiles on i9-12900K

This study separates decode query-head layout from attention arithmetic for
Gemma4 E2B/E4B. The opt-in [four profiles](../../docs/ATTENTION_EXPERIMENTS.md)
reuse identical control prefill code and published parameter payloads. The
existing `fp32_batch` executables remain the normal baseline. Integer candidates
dynamically quantize Q/P while retaining the published INT8 KV codes/scales;
they change numerical behavior and remain experiments.

## Configuration

The host is an Intel Core i9-12900K running Linux x86_64. Affinity `55` allows
logical CPUs 0/2/4/6, four distinct physical P cores. One-thread E2B and
four-thread E2B/E4B measurements use that same mask. Clocks are unlocked and the
governor is `powersave`. Measurements run sequentially, without concurrent lab
builds, with 20-second process cooldowns. The Samsung phone was disconnected;
these are PC observations.

The 250 [telemetry samples](telemetry.json) within unprofiled full-model process
intervals record package temperatures of 44–73°C, unchanged 5.1 GHz frequency
caps, and zero core/package throttle counters on all four allowed CPUs. Samples
include preparation and idle workers; they are not effective-frequency averages
for each decode. No phone-style thermal reversal was observed in these PC runs.

The backend pins are XNNPACK `d297c798ea530c12a1878bb3a3a811bdf05d715b`,
Slinky `d18c98551c77f366857f125e3a0f7886deb82a47`, and CPUinfo
`8ce83db858065145192c97af90cb668ad72a12e9`, with the normal retained patches.
This build also has the retained HF BF16 rounding patch applied. These
published-bundle graphs do not contain BF16 operations. Clang 22.1.8 builds
Release runners at `-O1`, construction sources at `-O2`, and kernels with their
own flags. Floating-point contraction is off for the runner/adapter; VNNI
kernel sources use `-mavx2 -mavxvnni`. Tokenizers and value traces are disabled.

Unprofiled full-model runs use exact checked-in performance fixtures, capacity
2,048, chunks of up to 128 real prefix rows, one warmup and three measured
requests per case. E2B forces 32 subsequent tokens; E4B forces 16. Profile order
is reversed in the second process round. Each case therefore has six measured
requests per engine/thread setting. Decode latency averages subsequent tokens;
warm TTFT includes prefix execution and the final prompt-token decode, excluding
process startup and preparation. Dumps, memory hooks and callback profiling are
disabled in latency runs.

The archived host native Tensor API/XNNPACK and static-QAT LiteRT/XNNPACK
controls are retimed with the same E2B IDs, continuations, capacity, thread count
and affinity. They retain their archived binaries and backends. Native uses
32-token KV alignment, reused runtimes and a shared workspace. It does not use
the Samsung `qp8_all` prefill experiment. Native attention retains FP32 Q/P with
mixed FP32/INT8 kernels; neither control is numerically equivalent to the new
INT8 attention policy. Native prefill padding and FC lowering also differ.
The static control uses its existing on-disk weight cache. Preparation and
process peak RSS must be interpreted with those differences, separately from
warm latency.

## Full-model warm execution

Four-thread E2B decode latency in ms/token, averaging six measured requests:

| Engine / decode attention | Prompt 17 | Prompt 128 | Prompt 1,024 |
| --- | ---: | ---: | ---: |
| YNNPACK FP32 batch | 24.82 | 25.41 | 27.68 |
| YNNPACK FP32 rows | 24.73 | 25.60 | 27.74 |
| YNNPACK INT8 batch | 24.84 | 25.17 | 26.30 |
| YNNPACK INT8 rows | 24.73 | 25.17 | 26.52 |
| Archived LiteRT/XNNPACK static QAT | 23.42 | 23.90 | 25.74 |
| Archived native Tensor API/XNNPACK | 23.44 | 23.79 | 25.20 |

At prompt 1,024, INT8 batch lowers observed decode latency by 5.0%. The gap to
native falls from 2.48 to 1.10 ms/token, about 55% of the original latency gap;
the candidate remains 4.4% slower than native. Both INT8 process orders repeat
closely. FP32 row grouping does not show a four-thread full-model benefit, and
the short-prompt changes are small. These comparisons do not establish ARM
performance or numerical equivalence.

Four-thread E2B warm TTFT at prompt 1,024 is approximately 989 ms for the default,
985 ms for either INT8 policy, 1,003 ms for static XNNPACK, and 1,014 ms for
native. Prefill construction is unchanged. Native's prompt-17 TTFT is about
131 ms versus 42 ms for YNNPACK because its control retains padded prefill;
that short-prompt result does not isolate backend arithmetic.

One-thread E2B decode latency, with the same six-request convention:

| Decode attention | Prompt 17 | Prompt 128 | Prompt 1,024 |
| --- | ---: | ---: | ---: |
| FP32 batch | 43.56 | 44.79 | 51.01 |
| FP32 rows | 43.46 | 44.24 | 47.50 |
| INT8 batch | 43.39 | 43.82 | 45.77 |
| INT8 rows | 43.37 | 43.79 | 45.50 |

At prompt 1,024, FP32 grouping reduces observed one-thread latency by 6.9%,
while the INT8 profiles reduce it by approximately 10%. Short-prompt differences
are small. Grouping's effect therefore depends on thread count and history;
the four-thread result does not justify a universal grouped-row policy.

Four-thread E4B decode latency, also six measured requests per case:

| Decode attention | Prompt 17 | Prompt 128 | Prompt 1,024 |
| --- | ---: | ---: | ---: |
| FP32 batch | 65.97 | 67.62 | 76.39 |
| FP32 rows | 65.85 | 67.77 | 76.89 |
| INT8 batch | 65.41 | 66.16 | 68.65 |
| INT8 rows | 65.80 | 66.64 | 69.17 |

INT8 batch reduces prompt-1,024 latency by 10.1%, while FP32 grouping alone does
not help this four-thread workload. E4B warm TTFT remains approximately 3.25 s.
Its preparation costs approximately 35.9/39.9/46.0/54.5 s for
FP32 batch/FP32 rows/INT8 batch/INT8 rows respectively. There is no fresh E4B
native-XNNPACK comparison in this study.

Preparation costs approximately 13.0 seconds for four-thread E2B FP32 batch,
13.6 for FP32 rows, 14.9 for INT8 batch and 16.5 for INT8 rows.
These costs are excluded from warm
TTFT/decode. The cached static control prepares in about 0.17 seconds and native
in about 1.59 seconds; their caching/runtime setup differs. Observed process peak
RSS is approximately 1,693–1,695 MiB for the YNNPACK profiles, including setup and
resident mappings. It does not establish a useful peak-memory reduction from
the integer policy.

## Numerical and state checks

[validation.json](validation.json) records 18 dump-enabled invocations and
594 finite logit vectors. For both models, each of the four profiles produces
byte-identical logits and KV codes at capacities 2,048 and 8,448. The updated
default also matches the preserved pre-change binary exactly. Repeating prompt
130 after the capacity-boundary request reproduces its logits and KV codes
exactly. Every run reports zero history-view copy bytes.

The retained [E2B](validation-cases-e2b.tsv) and
[E4B](validation-cases-e4b.tsv) token fixtures cover prompts
1/17/128/129/130/511/512/513/1,024/2,046, two forced continuations and the
repeated prompt 130. The last continuation of prompt 2,046 reaches capacity
2,048. Prompt 130 exercises a short second prefix chunk; the 511/512/513 cases
cross the local-attention window.

| Model / candidate versus FP32 batch | Greedy agreement | Max logit error | Min centered cosine | Max KL(reference‖candidate) | Different KV codes |
| --- | ---: | ---: | ---: | ---: | ---: |
| E2B FP32 rows | 32/33 | 5.276 | 0.9671 | 0.3542 | 186,944 / 142,442,496 |
| E2B INT8 batch or rows | 30/33 | 5.526 | 0.9623 | 0.3954 | 391,093 / 142,442,496 |
| E4B FP32 rows | 31/33 | 7.033 | 0.9585 | 0.0535 | 557,960 / 443,154,432 |
| E4B INT8 batch or rows | 31/33 | 15.667 | 0.8177 | 1.3204 | 1,273,941 / 443,154,432 |

The two INT8 layouts match each other exactly for both models in these checks.
FP32 grouping can change accumulation order and propagate through QAT
thresholds. INT8 attention additionally quantizes Q and probabilities. The
table includes the repeated request and teacher-forced continuations; it is not
a generation-quality evaluation. The substantial propagated differences rule
out treating these candidates as validated equivalent replacements.

Use the normal runner arguments with the retained validation fixture,
`--warmup_runs=0 --measured_runs=1 --dump_outputs`, in fresh output directories.
Compare capacities and preserved controls with `tools/compare_outputs.py`.
Do not use these dump-enabled timings as latency data.

The host build passes 23 CTest checks, including ten weights-free arithmetic
cases, and all 45 public Python tests. Candidate parameter payloads match the
existing assets byte for byte: 692 E2B files and 841 E4B files per candidate.
[identities.json](identities.json) retains public source, binary, parameter,
fixture, dependency and patch hashes with the actual compile flags.
[commands.json](commands.json) contains portable unprofiled command templates;
external XNNPACK controls require matching archived artifacts.

The Android NDK r28c cross-build also succeeds for both controls, all six
candidates and the harness, using ARM64, API 28 and static libc++.
[android-build.json](android-build.json) records its configuration and binary
hashes. This is build validation only; no Android execution or new phone timing
was performed.

## Isolated attention checks and timing

The reusable `attention_decode_bench` exercises all four policies with eight
query heads, one/two KV heads, widths 256/512, global/window-512 attention, and
one/four threads. Two query consumers share each KV history. Capacity 2,048
visits histories 1/17/128/511/512/513/1,024/17. Capacity 8,448 stress cases use
two KV heads and four threads, adding histories 2,048/8,192 before returning
to 17. Input generation uses a fixed bank seed independent of capacity.

[harness.json](harness.json) retains all 80 process commands and 2,016
unprofiled observations, covering 672 history visits with three repetitions of
20 graph invocations. Policy order alternates by geometry with one-second
process cooldowns. Each process compiles once and reuses that graph as history
increases, decreases and repeats. The repetitions are within one process,
not independent process trials. These cached prepared-graph measurements include
scalar binding and adapter checks; they are neither kernel-only timing nor a
full-model speedup estimate.

Every case passes the independent scalar reference and reports zero history-view
copy bytes. FP32 maximum absolute error is 7.02e-6. Integer QK and PV arithmetic
and inspected/unobserved final outputs match their staged references exactly;
maximum probability error is 1.14e-7. Maximum integer-output difference from
FP32 attention is 0.0707. This validates the chosen arithmetic, rather than
establishing equivalent model quality.

Four-thread global attention at history 1,024, ms per prepared-graph invocation
for two consumers, averaging three repetitions:

| KV heads / width | FP32 batch | FP32 rows | INT8 batch | INT8 rows |
| --- | ---: | ---: | ---: | ---: |
| 1 / 256 | 0.337 | 0.372 | 0.165 | 0.187 |
| 1 / 512 | 0.777 | 0.680 | 0.223 | 0.250 |
| 2 / 256 | 0.647 | 0.811 | 0.208 | 0.239 |
| 2 / 512 | 1.593 | 1.485 | 0.280 | 0.307 |

The scalar oracle initially exposed a probability-rounding boundary: a roughly
2e-9 softmax difference crosses one INT8 half-code threshold. QK was identical;
one probability code changed the subsequent PV result. The integer oracle now
checks QK and softmax independently, then calculates PV from the actual FP32
probability row using independent quantization and integer accumulation. A
separate inspection graph supplies these rows outside all timed repetitions;
its final output must match the unobserved graph. Two CTest cases retain the
original input with `--bank-seed-stride=8448`. No general error tolerance was
relaxed. See the [harness contract](../../docs/ATTENTION_EXPERIMENTS.md).

## Separate execution profiles

[profiles.json](profiles.json) retains callback accounting for all eight model
profiles and four isolated attention profiles. Model diagnostics use capacity
2,048, four threads, one warmup and one measured request at prompts 17/1,024,
with four subsequent teacher-forced tokens per case. Their shorter continuation
lists are retained in [E2B](profile-cases-e2b.tsv) and
[E4B](profile-cases-e4b.tsv) fixtures. These runs use execution callbacks and
sampling together; their wall times are diagnostic and excluded from latency
tables. Isolated profiles use two KV heads, width 512, global attention,
histories 17/1,024, and 200 invocations per step.

Mean prompt-1,024 attention accounting per subsequent model step:

| Model / profile | KV dequantization worker ms | Packing worker ms | QK + PV worker ms | All attention worker ms | Attention callback busy wall ms |
| --- | ---: | ---: | ---: | ---: | ---: |
| E2B FP32 batch | 1.132 | 0.787 | 7.392 | 10.196 | 2.736 |
| E2B FP32 rows | 1.009 | 0.575 | 3.270 | 5.599 | 2.595 |
| E2B INT8 batch | 0 | 0.645 | 1.105 | 2.791 | 1.603 |
| E2B INT8 rows | 0 | 0.695 | 0.752 | 2.500 | 1.667 |
| E4B FP32 batch | 9.709 | 4.480 | 12.244 | 27.534 | 8.015 |
| E4B FP32 rows | 11.168 | 2.970 | 6.151 | 21.189 | 8.003 |
| E4B INT8 batch | 0 | 1.936 | 1.599 | 5.106 | 3.090 |
| E4B INT8 rows | 0 | 2.129 | 1.176 | 4.838 | 2.970 |

Worker time sums worker interval unions; busy wall time unions attention
callbacks across workers. Neither quantity identifies the critical path, and
the category unions cannot be added to recover wall time. FP32 grouped builders
do not retain distinct QK/PV origin labels, so their dot work is combined.
Integer profiles also spend time quantizing Q/P, summing integer RHS columns,
correcting/scaling accumulators and applying mask/softmax; the record separates
these categories. Accumulator conversion is not another floating matmul or a
full-history KV dequantization.

Grouping substantially reduces dot worker work, but attention busy wall hardly
changes for the four-thread FP32 models. Mask/softmax work in the grouped traces
has less overlap across workers. Integer attention reduces both dot work and
conversion/packing work, consistent with the unprofiled long-prompt benefit.
E4B's default conversion/packing is approximately 52% of attention worker work;
E2B's is approximately 19% on this PC. The earlier Samsung fraction must not be
assumed for every model or architecture.

## Actual kernels and remaining gaps

[kernel-samples.json](kernel-samples.json) contains exclusive instruction-pointer
cycle samples selected only within measured graph-run intervals. Capture uses
`perf record -F 999 -e cycles:u --clockid mono`, then
`perf script --ns -F time,period,ip,sym,dso`; interval extraction uses
`tools/analyze_cpu_samples.py`. Symbols retain binary basenames, without raw
instruction addresses or local paths. These cycle shares are not wall-time
fractions. The full-model profiles retain eight decode intervals each; isolated
profiles retain 400 graph-run intervals each.

The isolated attention workload resolves the ambiguity with integer FC/head
kernels elsewhere in the models. It samples these attention microkernels:

| Profile | Observed dot kernels, with `ynn::dot_` prefix |
| --- | --- |
| FP32 batch | `fp32_1x16x2_1x4x2_avx2_fma3`, `fp32_1x32x1_1x8x1_fma3`, `fp32_1x8x2_1x4x2_avx2_fma3` |
| FP32 rows | `fp32_4x16x1_1x8x1_fma3` |
| INT8 batch | `uint8_int8_int32_1x32x4_1x8x4_avxvnni` |
| INT8 rows | `uint8_int8_int32_4x16x4_1x8x4_avxvnni` |

Full-model callback types independently show FP32×FP32 attention for the two
FP32 policies and UINT8×INT8 for both integer policies. Integer model captures
contain no sampled FP32 dot microkernels. Full-model FC still selects AVX2 INT2
and AVX-VNNI INT4/INT8 kernels. INT2/INT4 FC accounts for most exclusive cycle
samples, so attention improvements leave substantial full-model work unchanged.

The next equivalent-arithmetic backend experiment is to fuse KV conversion with
packing, or support FP32×INT8 attention directly, while preserving FP32 Q/P.
That work remains separate from these numerically different integer candidates.
Grouping needs shape/thread-specific investigation; the current four-thread
measurements do not support adopting it universally. New ARM measurements remain
outstanding because this campaign used the PC. Large dumps, pipelines, raw
profiles and perf recordings remain in ignored local output directories; the
small retained records contain portable commands and artifact identities.
