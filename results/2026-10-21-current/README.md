<!-- Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0 -->

# Current workload baseline — October 21, 2026

Fresh measurements of the Rust/`.ynn` checkout, with pinned YNNPACK/Slinky
sources and explicitly selected workload packages. These are research workloads
and teacher-forced execution measurements. A successful timing run is not a
model-quality qualification. Existing numerical limitations remain in the
[current issue trackers](../../docs/worklogs/README.md).

## Current findings

- Qwen3-0.6B cannot prepare on any of the four tested phones; the allocation failure is
  reproduced and recorded separately from throughput.
- Host Gemma E2B/E4B and the initial TECNO/Pixel 8 E2B runs pass the paired
  capacity timing check. The Samsung extension flags capacity sensitivity. State
  comparisons and their exact scope are retained separately.
- MobileNetV2 retains a substantial warm execution gap on all three tested
  Android phones: four-thread YNNPACK/LiteRT latency ratios are 5.50–7.49 with
  the native LiteRT/XNNPACK control. All independent output fixtures pass.
- Pixel 11's YNNPACK ResNet runs are slower at four threads than on the
  single prime core. A [same-cluster follow-up](vision-android/pixel11-same-cluster.md)
  reproduces the ResNet18 slowdown: 97 ms with one thread versus 170 ms with
  four. SME/SME2 kernels are disabled in these binaries; the cause remains
  unprofiled.
- Qwen3.5 INT4-MLP is very slow in this setup and remains numerically experimental.
  The refresh does not qualify it as a replacement for another profile.

## Measurement contract

The primary host screen uses prompts 17/128/1024, capacity 2048, one/four threads,
one warmup and three measured requests. [Exact fixtures](fixtures/) preserve the
IDs and continuation counts; compare the same fixture, not only the model name.
Gemma, Qwen3 and Qwen3.5 INT8 primary cases use `ynn-llm`; Qwen3.5 FP32
and INT4-MLP use the `qwen3` comparison runner. General-runner packages have
fixed capacity. Separate Gemma comparison
runners exercise capacities 2048/8448 in both orders. Phone E2B primary runs
were repeated with the thread order reversed; both rounds are retained.
Qwen prefill plans have 128 physical query rows even for a short chunk, while
only real rows update state. Gemma prefill accepts 1–128 real rows. Reported
prefill rates count real tokens; short-prompt rates therefore include different
physical work across these model families.

Prefill throughput is `(prompt_tokens - 1) * 1000 / mean(prefix_ms)`.
Warm TTFT includes prefix plus the last prompt-token decode, excluding startup,
mapping and preparation. Decode throughput is `1000 / mean(subsequent token ms)`;
first-token decode is excluded. Setup is a separate process measurement.
Peak RSS is a process high-water mark including preparation, mapped resident
weights and earlier cases. Repeated rows do not imply independent RSS samples.
Dumping, memory polling, execution tracing and CPU sampling are separate
correctness/diagnostic runs, excluded from the throughput tables.

Host: Intel Core i9-12900K, Linux, CPU 0 for one thread and physical P cores
0/2/4/6 for four. TECNO LJ9 uses CPU 7 or 4/5/6/7; Pixel 8 uses CPU 8 or
4/5/6/7. Android affinity uses hexadecimal `taskset` masks. One benchmark ran
at a time on each device; host builds were separated from host timings.
Frequency governors were not changed or clocks locked. Phone cooldown and
telemetry snapshots were collected; inaccessible sensor readings remain
unknown. Host telemetry began after the initial Gemma primary runs, so those
runs lack temperature snapshots. Small differences are not demonstrated gains.

Host Release uses Clang 22.1.8 and Rust 1.99.0; lab Android runners use NDK r28c,
arm64-v8a/API 28/static libc++. Native runner/adapter translation units use
`-O1`; Rust uses Cargo release, and backend kernels have their own flags. Floating-point contraction remains controlled.
The native LiteRT vision control targets API 35; its separate build provenance
is in the [Android vision report](vision-android/README.md).
HF profiles use a separate BF16-patched dependency build; default pins were not
replaced. [Identities](identities.json) record exact binaries, plans, patches and
source hashes. [Baseline identities](baseline-identities.json) preserve the exact
binaries used before a profiling-only fix: `ynn-llm` now emits phase metadata
before its first execution event. Unprofiled computation is unchanged; affected
diagnostics were rerun with the corrected binary. The new metadata contract is
covered by the session regression test and [repair validation](profile-repair-status.json).
[Commands](commands.json) are portable argv templates: substitute
external asset paths, deploy matching packages, and choose a fresh output path.
Run Android commands through `adb -s "$ANDROID_SERIAL" shell`; serials are
intentionally not retained. HF manifest/cache paths denote prepared local assets.

## Host primary screen

Four threads, prompt 1024, capacity 2048. Full one/four-thread and short-prompt
observations are in [summary.json](summary.json) and [requests.json](requests.json).
Qwen3.5 INT8 and INT4-MLP remain experimental numerical profiles.

| Workload / campaign | Prefill tok/s | Decode tok/s | Warm TTFT ms | Setup s | Peak RSS MiB |
| --- | ---: | ---: | ---: | ---: | ---: |
| gemma4_e2b_t4_c2048_r0 / host | 1,100.96 | 36.30 | 957.87 | 16.37 | 4,049.40 |
| gemma4_e4b_t4_c2048_r0 / host | 320.89 | 13.45 | 3,262.82 | 43.28 | 7,793.04 |
| qwen3_0_6b_t4_c2048_r0 / host | 1,016.03 | 36.45 | 1,035.28 | 18.72 | 2,706.81 |
| qwen3_4b_t4_c2048_r0 / host | 194.87 | 7.90 | 5,376.83 | 33.52 | 10,148.63 |
| qwen3_5_4b_fp32_t4_c2048_r0 / host | 68.35 | 1.93 | 15,485.55 | 17.08 | 32,822.29 |
| qwen3_5_4b_int4_mlp_t4_c2048_r0 / host | 12.40 | 1.64 | 83,124.23 | 12.26 | 6,210.31 |
| qwen3_5_4b_int8_t4_c2048_r0 / host | 194.48 | 7.97 | 5,386.50 | 17.24 | 9,519.35 |

## Phone E2B screen

Four threads, prompt 1024, capacity 2048. These rows retain both measurement
rounds rather than selecting the faster one. The separate capacity sweep uses
the Gemma comparison runner, so its setup costs should not be substituted here.

| Workload / campaign | Prefill tok/s | Decode tok/s | Warm TTFT ms | Setup s | Peak RSS MiB |
| --- | ---: | ---: | ---: | ---: | ---: |
| gemma4_e2b_t4_c2048 / tecno-v2 | 171.78 | 9.73 | 6,058.92 | 114.21 | 5,250.31 |
| gemma4_e2b_t4_c2048 / pixel8-v2 | 242.09 | 12.93 | 4,302.56 | 85.14 | 4,156.91 |
| gemma4_e2b_t4_c2048 / tecno-repeat | 172.03 | 9.62 | 6,052.53 | 114.48 | 5,249.65 |
| gemma4_e2b_t4_c2048 / pixel8-repeat | 254.53 | 12.72 | 4,088.90 | 86.12 | 4,077.35 |

Qwen3-0.6B failed during preparation in all four phone timing attempts. No warm
throughput exists for those attempts. The [allocation issue](qwen-android-allocation.md)
distinguishes Pixel's explicit Scudo out-of-memory report from TECNO's allocator
failure during cleanup. A separate Pixel memory diagnostic observed a 4.73 GiB
resident high-water mark before `std::bad_alloc`; this does not identify the root
allocation. E4B phone runs were skipped for available memory/storage constraints,
not reported as observed OOMs. See [failures](failures.json) and the explicit
skip reasons in [validation](validation.json). No fresh external LLM control was
run on the phones; these are lab-only measurements. The subsequently connected Samsung and Pixel 11 are covered by the
[phone extension](phone-expansion/README.md), with separate identities, requests
and validation. Its Samsung capacity check flags approximately 12% long-prompt
prefix/TTFT sensitivity under noisy, unlocked conditions.

## Additional screens and controls

Attention policies, direct-HF arithmetic profiles and recurrence variants are
experimental screens in a fixed policy order, with one warmup and three measured
requests per timing job. These are not paired optimization gates. Their
arithmetic/layout contracts differ; timing alone
does not qualify a replacement. [Numerical comparisons](numerical-comparisons.json)
retain finite-output checks, logit error, centered cosine, KL, greedy agreement
and KV-code differences where applicable. Short forced-token comparisons do
not establish generation quality.

The external E2B control uses an available older LiteRT binary/model and warm
on-disk weight cache, bracketed by fresh lab runs. The lab Gemma metadata declares
published static QAT with a dynamic head. The control's older binary/model lineage,
dependency versions and cache behavior prevent an isolated backend comparison;
matching source labels alone do not establish identical arithmetic.
Vision uses matching FP32 source fixtures and fresh paired runner measurements.
Recurrent timings are kernel/step screens, not full-model throughput.

[Execution profiles](execution-profiles.json) report scheduled callback work;
summed worker time is not critical-path wall time. [Selected kernel samples](selected-kernel-samples.json)
use user-cycle samples restricted to execution-profiler graph-step intervals,
excluding setup, input preparation outside those intervals and the first decode step. Sampling shares are distinct from wall-time shares.
These instrumented runs are not latency baselines.


### Numerical screen

Prompts 17/130 with two forced continuations, six logits per profile, compared
against the matching Gemma FP32-batch baseline. HF comparisons are logits-only
because KV formats differ; their source/arithmetic policies also differ from the
published-bundle baseline. Every reported comparison checked finite logits.

| Candidate | Greedy agreement | Max logit error | Min centered cosine | Max KL |
| --- | ---: | ---: | ---: | ---: |
| gemma4_e2b-fp32_rows | 5/6 | 3.9224 | 0.981579 | 0.072214 |
| gemma4_e2b-int8_batch | 6/6 | 3.9636 | 0.978662 | 0.058253 |
| gemma4_e2b-int8_rows | 6/6 | 3.9636 | 0.978662 | 0.058253 |
| gemma4_e4b-fp32_rows | 5/6 | 4.6128 | 0.976035 | 0.134010 |
| gemma4_e4b-int8_batch | 3/6 | 3.8466 | 0.987085 | 0.073379 |
| gemma4_e4b-int8_rows | 3/6 | 3.8466 | 0.987085 | 0.073379 |
| hf_fp32_int8_published_kv_t4_correctness | 5/6 | 7.5874 | 0.930203 | 0.343387 |
| hf_bf16_int8_raw_kv_t4_correctness | 5/6 | 7.9945 | 0.897149 | 0.566298 |
| hf_static_int8_published_kv_t4_correctness | 4/6 | 6.6993 | 0.930855 | 0.453967 |
| hf_bf16_int8_published_kv_t4_correctness | 5/6 | 6.7897 | 0.935694 | 0.365582 |
| hf_bf16_t4_correctness | 5/6 | 7.1144 | 0.924050 | 0.369262 |

FP32 row layout changes predictions in this screen, as does E4B integer attention.
These are not equivalent replacements. E2B integer attention agrees greedily on
these six outputs but still changes logits and KV codes. Capacity-only comparisons
are exact across all 744 E2B and 2,328 E4B dump files.


### Direct-HF screen

Four threads, prompt 1024, capacity 2048, eight forced continuations per request.
These profiles differ in arithmetic and KV policy; see the numerical comparisons.

| Workload / campaign | Prefill tok/s | Decode tok/s | Warm TTFT ms | Setup s | Peak RSS MiB |
| --- | ---: | ---: | ---: | ---: | ---: |
| hf_bf16_int8_published_kv_t4 / hf-screen | 207.88 | 1.42 | 5,623.96 | 65.84 | 7,651.89 |
| hf_bf16_int8_raw_kv_t4 / hf-screen | 208.18 | 1.43 | 5,616.15 | 64.80 | 7,651.07 |
| hf_bf16_t4 / hf-screen | 208.41 | 1.43 | 5,606.53 | 61.61 | 7,616.92 |
| hf_fp32_int8_published_kv_t4 / hf-screen | 364.42 | 1.05 | 3,763.70 | 41.93 | 4,398.47 |
| hf_static_int8_published_kv_t4 / hf-screen | 1,038.16 | 34.51 | 1,015.20 | 32.64 | 4,804.01 |


### Vision measurements on Android (native LiteRT)

All eight FP32 classifiers were tested on TECNO LJ9, Pixel 11 and Samsung
SM-S937U1. The LiteRT/XNNPACK baseline uses `benchmark_model_main` from
`litert/tools`, built as `//litert/tools:benchmark_model`; inference does not
use a Python wrapper. Each engine uses the same synthetic input and CPU mask.

Four threads below. Values are mean warm invocation milliseconds from two
paired rounds, each with three warmups and ten measured invocations. The
ratio is YNNPACK latency divided by LiteRT/XNNPACK latency.

| Device | Model | YNN ms | LiteRT/XNNPACK ms | Latency ratio |
| --- | --- | ---: | ---: | ---: |
| TECNO LJ9 | resnet18 | 57.701 | 23.534 | 2.45 |
| TECNO LJ9 | resnet34 | 103.929 | 47.100 | 2.21 |
| TECNO LJ9 | resnet50 | 100.220 | 56.138 | 1.79 |
| TECNO LJ9 | resnet101 | 182.587 | 102.887 | 1.77 |
| TECNO LJ9 | resnet152 | 266.946 | 148.857 | 1.79 |
| TECNO LJ9 | resnext50_32x4d | 91.349 | 67.043 | 1.36 |
| TECNO LJ9 | wide_resnet50_2 | 260.110 | 171.968 | 1.51 |
| TECNO LJ9 | mobilenet_v2 | 33.618 | 5.165 | 6.51 |
| Pixel 11 | resnet18 | 163.749 | 20.319 | 8.06 |
| Pixel 11 | resnet34 | 178.831 | 38.895 | 4.60 |
| Pixel 11 | resnet50 | 130.399 | 45.552 | 2.86 |
| Pixel 11 | resnet101 | 320.870 | 84.990 | 3.78 |
| Pixel 11 | resnet152 | 494.992 | 123.735 | 4.00 |
| Pixel 11 | resnext50_32x4d | 83.564 | 55.082 | 1.52 |
| Pixel 11 | wide_resnet50_2 | 216.225 | 137.947 | 1.57 |
| Pixel 11 | mobilenet_v2 | 33.821 | 4.515 | 7.49 |
| Samsung SM-S937U1 | resnet18 | 28.851 | 13.672 | 2.11 |
| Samsung SM-S937U1 | resnet34 | 53.084 | 24.524 | 2.16 |
| Samsung SM-S937U1 | resnet50 | 58.195 | 28.925 | 2.01 |
| Samsung SM-S937U1 | resnet101 | 107.457 | 57.906 | 1.86 |
| Samsung SM-S937U1 | resnet152 | 158.154 | 87.808 | 1.80 |
| Samsung SM-S937U1 | resnext50_32x4d | 60.879 | 39.597 | 1.54 |
| Samsung SM-S937U1 | wide_resnet50_2 | 145.074 | 92.394 | 1.57 |
| Samsung SM-S937U1 | mobilenet_v2 | 30.115 | 5.473 | 5.50 |

All 216 PyTorch fixture comparisons passed: YNNPACK at one/four threads and
LiteRT’s native `run_model` at its default one CPU thread. Seven models are
fully delegated to XNNPACK; ResNeXt retains 16 CPU concatenations between
17 XNNPACK partitions. Its latency includes that fallback work.

The [full Android report](vision-android/README.md) includes one/four-thread
tables, device topology, frequency/thermal conditions, correctness scope,
dependency revisions and native build commands. [Per-round observations](vision-android/observations.json)
retain setup and first invocation separately. Clocks are unlocked and only
two short rounds were collected; small differences are not established gains.
The [Pixel threading follow-up](vision-android/pixel11-same-cluster.md) adds
nine passing fixture checks and retains its later timing rounds separately.

### Earlier Linux x86_64 vision screen (Python control)

These earlier host measurements are retained with their original Python
baseline. They were not rerun as part of the Android campaign. Their input
and aggregation differ from the native Android screen.

Median warm invocation milliseconds across the two paired rounds. LiteRT includes
its Python invoke wrapper; setup and first invocation are recorded separately.

| Model | Threads | YNN ms | LiteRT/XNNPACK ms | Latency ratio |
| --- | ---: | ---: | ---: | ---: |
| resnet18 | 1 | 34.414 | 26.069 | 1.32 |
| resnet18 | 4 | 13.365 | 7.461 | 1.79 |
| resnet34 | 1 | 64.357 | 52.294 | 1.23 |
| resnet34 | 4 | 23.096 | 15.129 | 1.53 |
| resnet50 | 1 | 78.775 | 59.396 | 1.33 |
| resnet50 | 4 | 26.396 | 17.443 | 1.51 |
| resnet101 | 1 | 144.305 | 111.780 | 1.29 |
| resnet101 | 4 | 48.399 | 32.800 | 1.48 |
| resnet152 | 1 | 206.342 | 162.344 | 1.27 |
| resnet152 | 4 | 69.741 | 48.204 | 1.45 |
| resnext50_32x4d | 1 | 96.089 | 65.547 | 1.47 |
| resnext50_32x4d | 4 | 30.918 | 21.973 | 1.41 |
| wide_resnet50_2 | 1 | 220.050 | 159.073 | 1.38 |
| wide_resnet50_2 | 4 | 65.850 | 45.065 | 1.46 |
| mobilenet_v2 | 1 | 45.898 | 4.755 | 9.65 |
| mobilenet_v2 | 4 | 16.019 | 5.288 | 3.03 |

All 96 independent fixture comparisons passed. See [vision observations](vision-observations.json), [validation](vision-validation.json), and [identities](vision-identity.json).

## Validation and retained records

The clean-source build passes all 30 CTests, including the profiling regression.
Four native ASan/UBSan tests pass; the updated session regression also passes
under sanitizers. The benchmark harness has 11 passing unit tests. Native
arithmetic/state checks pass on both initial phones, and all 96 host vision
fixture comparisons pass. The native Android vision extension adds 216 passing
fixture comparisons across TECNO, Pixel 11 and Samsung. Host reset checks are
byte-identical for E2B (264 files),
E4B (408), Qwen3-0.6B (472), Qwen3-4B (600), and Qwen3.5 INT8 (536).
Each phone's E2B reset check matches 99 files. These are self-consistency and
arithmetic checks, not a generation-quality qualification.

The timing dataset contains 68 successful LLM timing jobs and 612 measured
requests, plus four Android preparation failures. Vision and recurrent screens
have separate observation files and timing definitions.

The first Qwen3 host reset attempts rejected an incorrectly shared Gemma fixture
for out-of-vocabulary IDs. [Corrected reruns](reset-retry-status.json) use each
Qwen model's own token fixture; those initial harness errors are not model failures.

[Validation](validation.json) records test-stage exit status, repeated-request
state/logit checks, capacity checks and skips. [Numerical comparisons](numerical-comparisons.json)
record capacity-only dump equality separately from changed-arithmetic screens.
[Process records](processes.json) retain setup, memory and cumulative state
counters; cumulative counters are not per-request counters. Zero history-view
copy callbacks do not exclude backend history reads, conversion or packing. [Battery snapshots](battery-snapshots.json)
retain available battery level/temperature/voltage readings. [Phone sensors](phone-sensors.json)
and [host samples](host-sensors.json) retain frequency/temperature availability.
[Compiler flags](compiler-flags.json), [test summaries](test-summary.json),
[recurrence observations](recurrent-screen.json) and [retention inventory](retention.json)
provide supporting detail.

Raw captures, full profiles, builds, weights and device logs remain in ignored
local output directories. Superseded results were archived outside this repository.
Older evidence in the [result index](../README.md) is retained only for unresolved
questions and is not relabeled as current measurement.
