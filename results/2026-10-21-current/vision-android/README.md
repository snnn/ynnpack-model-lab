<!-- Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0 -->

# Android vision measurements — October 21, 2026

Eight FP32 TorchVision classifiers were tested on all three connected phones,
at one and four CPU threads. The control is LiteRT’s native
`benchmark_model_main` entry point, built as `//litert/tools:benchmark_model`.
No Python inference runs in either timed process. All 216 comparisons with
the independent PyTorch fixtures passed.

LiteRT/XNNPACK has the lower recorded warm mean in all 48 configurations.
The four-thread MobileNetV2 YNNPACK/LiteRT latency ratio is 6.51 on TECNO,
7.49 on Pixel 11 and 5.50 on Samsung. Pixel 11's five ResNet variants take
longer with four YNNPACK threads than with one on the prime core. This screen
does not identify the responsible kernels or threading mechanism.

## Configuration

| Device | SoC | Android | One-thread CPUs / mask | Four-thread CPUs / mask |
| --- | --- | --- | --- | --- |
| TECNO LJ9 | MT6897 | 15 | 7 / `80` | 4,5,6,7 / `f0` |
| Pixel 11 | Tensor G6 | 17 | 6 / `40` | 2,3,4,5 / `3c` |
| Samsung SM-S937U1 | SM8750 | 17 | 7 / `80` | 4,5,6,7 / `f0` |

Each model takes one FP32 NCHW image `[1,3,224,224]` and returns 1,000
logits. Model, parameter and fixture hashes match the earlier host screen.
Every deployed file was hash checked on each phone.

LiteRT is revision `5067199ff064a229d7f254b782168a7a1ac4f01f`, with its
pinned XNNPACK `35997e71119d191c807068a4d2aa28bf6048b59b`. Its source
has no runtime edits; existing documentation edits are listed in the provenance.
The lab’s YNNPACK comes from XNNPACK `0a66ebb5817fce48df605451444dcfc27a5e4ee4`
with Slinky `a3eec6fcfe3093be04d6c3d7dcab7d4e70bdd0dc` and the retained
lab patches. These are distinct dependency revisions. The YNNPACK binary
matches the retained Android baseline binary byte for byte.

Both builds use NDK r28c and static libc++; YNNPACK targets API 28 and
LiteRT API 35. LiteRT uses Bazel `-c opt`; the lab uses its existing CMake
Release configuration. The retained native compile commands use `-Oz` for
the benchmark/input utilities and `-O2` for the representative FP32 NEON kernel;
the lab’s [compiler flags](../compiler-flags.json) remain unchanged.
SME/SME2 are disabled. LiteRT’s optional YNNPACK
accelerator is disabled and the CPU accelerator is selected. Separate
runtime-info diagnostics show full XNNPACK delegation for seven models.
ResNeXt has 17 XNNPACK partitions and 16 CPU builtin concatenations on each
phone. Its baseline includes that fallback work; it is not fully delegated.

The SME audit in [provenance](provenance.json) checks the effective YNNPACK
CMake options, absence of real SME/SME2 source build actions and absence
of defined SME kernel symbols in the tested binary. FP32 NEON dot kernels
are linked. LiteRT compile actions define `XNN_ENABLE_ARM_SME=0` and
`XNN_ENABLE_ARM_SME2=0`. The observed Pixel threading behavior cannot be
attributed to execution of SME2 kernels in this configuration.

## Timing method

Two fresh processes per engine/model/thread/device each execute three
warmups and ten measured invocations. Engine order is YNNPACK then LiteRT
in round one and LiteRT then YNNPACK in round two. Processes run sequentially
across all phones, with at least ten seconds between jobs on the same phone.
No builds or competing benchmarks run during collection. Phones use USB
power and stay awake; their original power settings were restored afterward.

The table is the arithmetic mean of the two process means, representing
20 timed invocations. It measures warm full-model execution, including each
runner’s invocation overhead, and excludes setup, first invocation, input
copying, output dumping and diagnostics. LiteRT calls `CompiledModel::Run`.
The native benchmark’s generated FP32 input is reproduced for YNNPACK using
the same default-seeded `std::mt19937`, uniform range `[-0.5,0.5)`, shape
and NDK libc++ implementation. Its hash is retained in the identity record.

Clocks are unlocked and governors unchanged. The four-thread masks need
not use the same core class as the one-thread masks; especially on Pixel 11,
four-thread results are not a scaling measurement of the single prime core.
Two short rounds do not establish small performance differences. Per-round
means and native benchmark distributions are retained. The largest difference
between round means is 12.7% for YNNPACK (Pixel ResNet18, four threads) and
12.2% for LiteRT (Pixel MobileNetV2, four threads), computed as `max/min - 1`.
The earlier Linux
screen uses a Python wrapper, a photograph input and a different aggregation;
do not compare its numbers directly as a native platform speed ratio.

A separate [Pixel 11 follow-up](pixel11-same-cluster.md) keeps both thread
counts in the same cluster. YNNPACK ResNet18 takes 96.992 ms on CPU 2 and
170.095 ms on CPUs 2–5; LiteRT takes 75.666 and 20.327 ms respectively.
All nine additional fixture checks pass. The slowdown persists within that
cluster with SME/SME2 disabled; its cause still requires profiling. These
later results are retained separately from the main matrix below.

## Warm invocation latency

Milliseconds; ratio is YNNPACK divided by LiteRT/XNNPACK. Above 1 means
YNNPACK took longer.

### TECNO LJ9

| Model | Threads | YNNPACK ms | LiteRT/XNNPACK ms | Ratio |
| --- | ---: | ---: | ---: | ---: |
| resnet18 | 1 | 133.886 | 91.588 | 1.46 |
| resnet18 | 4 | 57.701 | 23.534 | 2.45 |
| resnet34 | 1 | 252.803 | 182.333 | 1.39 |
| resnet34 | 4 | 103.929 | 47.100 | 2.21 |
| resnet50 | 1 | 277.855 | 212.900 | 1.31 |
| resnet50 | 4 | 100.220 | 56.138 | 1.79 |
| resnet101 | 1 | 516.397 | 394.534 | 1.31 |
| resnet101 | 4 | 182.587 | 102.887 | 1.77 |
| resnet152 | 1 | 748.784 | 575.556 | 1.30 |
| resnet152 | 4 | 266.946 | 148.857 | 1.79 |
| resnext50_32x4d | 1 | 298.696 | 231.479 | 1.29 |
| resnext50_32x4d | 4 | 91.349 | 67.043 | 1.36 |
| wide_resnet50_2 | 1 | 807.387 | 586.595 | 1.38 |
| wide_resnet50_2 | 4 | 260.110 | 171.968 | 1.51 |
| mobilenet_v2 | 1 | 64.164 | 17.776 | 3.61 |
| mobilenet_v2 | 4 | 33.618 | 5.165 | 6.51 |

### Pixel 11

| Model | Threads | YNNPACK ms | LiteRT/XNNPACK ms | Ratio |
| --- | ---: | ---: | ---: | ---: |
| resnet18 | 1 | 46.023 | 40.390 | 1.14 |
| resnet18 | 4 | 163.749 | 20.319 | 8.06 |
| resnet34 | 1 | 81.752 | 78.983 | 1.04 |
| resnet34 | 4 | 178.831 | 38.895 | 4.60 |
| resnet50 | 1 | 107.490 | 86.522 | 1.24 |
| resnet50 | 4 | 130.399 | 45.552 | 2.86 |
| resnet101 | 1 | 188.102 | 158.834 | 1.18 |
| resnet101 | 4 | 320.870 | 84.990 | 3.78 |
| resnet152 | 1 | 272.440 | 230.151 | 1.18 |
| resnet152 | 4 | 494.992 | 123.735 | 4.00 |
| resnext50_32x4d | 1 | 133.098 | 93.953 | 1.42 |
| resnext50_32x4d | 4 | 83.564 | 55.082 | 1.52 |
| wide_resnet50_2 | 1 | 284.093 | 255.425 | 1.11 |
| wide_resnet50_2 | 4 | 216.225 | 137.947 | 1.57 |
| mobilenet_v2 | 1 | 37.866 | 7.324 | 5.17 |
| mobilenet_v2 | 4 | 33.821 | 4.515 | 7.49 |

### Samsung SM-S937U1

| Model | Threads | YNNPACK ms | LiteRT/XNNPACK ms | Ratio |
| --- | ---: | ---: | ---: | ---: |
| resnet18 | 1 | 46.286 | 29.770 | 1.55 |
| resnet18 | 4 | 28.851 | 13.672 | 2.11 |
| resnet34 | 1 | 84.885 | 59.570 | 1.42 |
| resnet34 | 4 | 53.084 | 24.524 | 2.16 |
| resnet50 | 1 | 104.928 | 68.461 | 1.53 |
| resnet50 | 4 | 58.195 | 28.925 | 2.01 |
| resnet101 | 1 | 192.028 | 130.372 | 1.47 |
| resnet101 | 4 | 107.457 | 57.906 | 1.86 |
| resnet152 | 1 | 282.754 | 193.915 | 1.46 |
| resnet152 | 4 | 158.154 | 87.808 | 1.80 |
| resnext50_32x4d | 1 | 134.237 | 82.744 | 1.62 |
| resnext50_32x4d | 4 | 60.879 | 39.597 | 1.54 |
| wide_resnet50_2 | 1 | 307.298 | 199.101 | 1.54 |
| wide_resnet50_2 | 4 | 145.074 | 92.394 | 1.57 |
| mobilenet_v2 | 1 | 40.880 | 6.415 | 6.37 |
| mobilenet_v2 | 4 | 30.115 | 5.473 | 5.50 |

## Correctness and delegation

All 216 fixture comparisons passed `atol=1e-4, rtol=1e-3`: 144 YNNPACK
checks at one/four threads and 72 LiteRT checks using the official
`run_model` tool at its default one CPU thread. Each uses the same two
random fixtures and one preprocessed photograph per model. The four-thread
LiteRT timing configuration does not have a separate output-dump check.
All outputs are finite; 216/216 match the PyTorch top-1 result.
The largest absolute logit error is 1.335144e-05.
These fixed inputs do not measure ImageNet accuracy.

| Model | XNNPACK nodes | XNNPACK partitions | CPU builtin nodes |
| --- | ---: | ---: | ---: |
| resnet18 | 55 | 1 | 0 |
| resnet34 | 95 | 1 | 0 |
| resnet50 | 128 | 1 | 0 |
| resnet101 | 234 | 1 | 0 |
| resnet152 | 366 | 1 | 0 |
| resnext50_32x4d | 1111 | 17 | 16 |
| wide_resnet50_2 | 128 | 1 | 0 |
| mobilenet_v2 | 106 | 1 | 0 |

## Environment snapshots

The ranges below cover snapshots immediately before/after timing jobs,
not continuous sampling inside invocation. Battery temperature is not CPU
temperature. CPU thermal access is denied on TECNO and Pixel 11.

| Device | Battery °C | CPU sensors °C |
| --- | ---: | ---: |
| TECNO LJ9 | 24.2–26.4 | unavailable |
| Pixel 11 | 25.1–26.6 | unavailable |
| Samsung SM-S937U1 | 25.1–29.6 | 28.3–88.0 |

Per-policy advertised maxima, observed frequency limits and sampled current
frequencies are in [environment-summary.json](environment-summary.json).
Unavailable frequency/governor fields remain null. OS frequency limits may
be below the advertised hardware maximum; no maximum-clock claim is made.

## Retained evidence and reproduction

[Summary](summary.json), [observations](observations.json),
[validation](validation.json), [validation totals](validation-summary.json),
[delegate coverage](delegation.json), [identities](identity.json),
[build provenance](provenance.json), [commands](commands.json) and
[filtered telemetry](telemetry.json) retain the measured configuration.
Commands use `${REMOTE_ROOT}` and device labels; supply a local ADB serial.
The [Android workflow](../../../docs/VISION.md#android-comparison-with-the-native-litert-benchmark)
documents the reusable harness and input generator.

Setup and first-invocation measurements remain in the summary and observation
files, outside the warm table. YNNPACK reports absolute process peak RSS;
LiteRT’s `init_footprint_kb` and `overall_footprint_kb` are increases in
process peak RSS. They are different metrics and are not compared as equal
memory measures. Peak-memory polling is disabled.

Raw native protobufs, output logits, process logs, builds and model payloads
remain under ignored local output/asset directories. Public records contain
no device serials or personal host paths.
