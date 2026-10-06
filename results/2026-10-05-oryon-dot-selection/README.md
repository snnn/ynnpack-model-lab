<!-- Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0 -->

# One-row INT2/INT4 selection on Samsung Oryon

INT2 DOTPROD lowers observed one-row Gemma4 E2B decode latency by 15–28%
relative to the retained I8MM baseline on Samsung SM-S937U1. INT4 DOTPROD wins
the direct cached kernel comparison, while its full-model benefit varies by
case and thread count. All four selection policies preserve exact logits and
KV codes against the retained YNNPACK control.

This experiment investigates the retained YNNPACK baseline's I8MM decode
selection on Samsung SM-S937U1, where the preserved native Tensor API/XNNPACK
runner executes DOTPROD for INT2/INT4. The
[preceding profile study](../2026-10-05-decode-profile/README.md) records that
cross-runtime comparison. This follow-up compares kernel arithmetic and timing,
then restricts YNNPACK's one-row decode selection independently for INT2, INT4,
and both. It uses Gemma4 E2B's published weight codes and static QAT contract.

## Why the runners choose different kernels

The preserved native XNNPACK dispatcher does not rank DOTPROD against I8MM for
these operators. On ARM64 with DOTPROD available,
`init_qs8_qc2w_gemm_config`, `init_qs8_qc4w_gemm_config`, and
`init_qd8_f32_qc2w_gemm_config` populate DOTPROD tables. Their preserved
initialization functions have no I8MM candidate. The FC reshape chooses the
one-row table entry for batch size one. Native's choice therefore does not
establish that it measured both instruction families and chose the faster one.
See [selection evidence](selection-evidence.json) for source identities.

YNNPACK uses the detected Oryon cost model. At graph construction, it chooses a
kernel to determine weight packing and the activation transpose. Runtime
selection uses the actual shape but must respect that layout. The retained
known-row patch supplies M=1 during construction; Samsung's learned model still
predicts I8MM is cheaper:

| Weight type | Selection shape M/N/K | Predicted DOTPROD, ns | Predicted I8MM, ns |
| --- | --- | ---: | ---: |
| INT2 | 1 / 384 / 256 | 1,909 | 1,734 |
| INT4 | 1 / 384 / 256 | 2,474 | 1,949 |
| INT2 | 1 / 256 / 1536 | 7,458 | 6,696 |
| INT4 | 1 / 256 / 1536 | 9,676 | 7,540 |

The first shape is the clipped packing-selection query. The second represents
a common one-row decode dot extent. These are model predictions, not measured
latencies.

The fitting script supplies a concrete explanation for inaccurate one-row
ranking. In `fit_model`, if any kernel in a model family has `block_m > 1`, it
skips kernels with `block_m == 1`. The Oryon CSV contains 60 one-row DOTPROD
records for each low-bit type; all are excluded. Its 140 I8MM records per type
contain no M=1 shapes. The shared DOTPROD coefficients are therefore fitted to
larger-row kernels, while the I8MM model extrapolates to a partial two-row tile.
The selector accounts for tile rounding, but that does not replace measured
one-row kernel costs. [Training summary](cost-model-training.json) preserves
the counts. This is separate from the previously corrected unknown-M packing
bug and Pixel's CPUinfo issue.

The training benchmark itself sets `m = block_m`, so its two-row I8MM kernel
never receives M=1. It also limits the A/B/C working set to 24 KiB, targeting
L1-resident execution. That helps explain why direct cached rankings and
streaming/full-model outcomes need separate measurements.

## Kernel measurements

The optional [dot_decode_bench](../../tools/dot_decode_bench.cc) directly calls
each selected kernel with M=1. The tested shapes are N=384/K=256 and N=256 with
K=1536/2048/4096/6144/12288. Candidates use compatible, separately prepared
packing. Nontrivial signed inputs and full-range signed weight codes are checked
against an independent scalar INT32 dot before timing. Packing and reference
computation are outside timing.

Seven alternating-order trials per kernel use at least 0.1 seconds per trial.
Cached cases reuse one matrix; streaming cases rotate through at least 32 MiB
of distinct weight storage per kernel. Direct calls exclude YNNPACK's cache
scheduling, graph callbacks, activation quantization, epilogues and model state.
Synthetic kernel data is distinct from the full-model published weights below.

For N=256 and the model reduction sizes, cached DOTPROD median latency is
36.2–36.5% lower for INT2 and 25.4–25.6% lower for INT4. Streaming INT2 is about
11% faster at K=1536/2048 and roughly tied at larger K. Streaming INT4 ranges
from roughly tied/slightly slower at K=1536/2048 to 19–20% faster at larger K.
Small streaming differences need caution. The phone has unlocked clocks, and
absolute cached times change during the campaign; paired ratios are more
useful than comparing absolute times across shapes.

[Raw kernel trials](kernel-timings.jsonl) and [kernel summary](kernel-summary.csv)
include candidate names, predictions, working-set sizes, medians and ranges.
The candidates are:

| Type | Default I8MM | DOTPROD candidate |
| --- | --- | --- |
| INT2 | `dot_int8_int2_int32_2x32x8_2x4x8_neoni8mm` | `dot_int8_int2_int32_1x32x16_1x4x16_neondot` |
| INT4 | `dot_int8_int4_int32_2x32x8_2x4x8_neoni8mm` | `dot_int8_int4_int32_1x32x8_1x4x8_neondot` |

## Full-model experiment

An isolated dependency copy applies the optional
[one-row selection experiment](../../patches/experiments/ynnpack-one-row-dotprod.patch).
`LAB_EXPERIMENT_ONE_ROW_DOT=none|int2|int4|both` removes I8MM from the allowed
architectures for known-M=1 INT8/INT2 or INT8/INT4 dots. It passes the same
restriction to preparation and execution. Unknown-row prefill and INT8/float
paths retain normal selection. The normal dependency configuration is unchanged.

INT2 DOTPROD requires `tile_k=16`, while I8MM requires `tile_k=8`. A runtime-only
switch would be incompatible with the original packing. These full-model
comparisons include the compatible layout and activation-transpose changes;
they are not an isolated measurement of the instruction itself.

All four policies exactly match the retained baseline's 372 output files:
12 logit arrays and 35,555,328 INT8 KV codes at prompts 1/128/129/1024 with two
continuations. Prefill pipelines are identical after removing printed pointer
addresses. The `none` decode pipeline also matches the retained baseline.
[Validation](validation.json) includes these checks and the 12 passing host
CTest cases.

Latency runs disable profiling and dumps. Each policy uses capacity 2048,
32 forced continuations, one warmup and three measured requests. Two rounds
reverse policy order, providing six measured requests per configuration. The
one-thread mask is `80` (core 7); four-thread mask is `f0` (cores 4–7).
Processes have 25-second cooldowns. The tested combinations are prompt 17 at
one/four threads and prompt 1024 at four threads.

Mean subsequent-token latency in ms, with six measured requests per entry:

| Threads | Prompt tokens | Default I8MM | DOTPROD INT2 only | DOTPROD INT4 only | DOTPROD both |
| ---: | ---: | ---: | ---: | ---: | ---: |
| 1 | 17 | 70.74 | 55.81 | 71.37 | 54.82 |
| 4 | 17 | 30.58 | 22.09 | 24.53 | 22.25 |
| 4 | 1024 | 51.88 | 44.24 | 49.18 | 42.80 |

INT2 DOTPROD reduces observed mean latency by **21.1%, 27.8%, and 14.7%** in
these three configurations. Its per-process round means reproduce closely:
55.95/55.66, 21.73/22.45, and 44.16/44.32 ms. It is the clearest full-model
improvement from this selection experiment.

INT4 DOTPROD is more dependent on the case: about 19.8% lower latency for the
four-thread short prompt, 5.2% lower for the long prompt, and no improvement
in the aggregated one-thread short case. Adding it to the INT2 restriction
changes latency by -1.8%, +0.7%, and -3.2% respectively. Those small incremental
differences do not support a universal low-bit ISA preference.

The default one-thread short control varies between rounds: 65.10 versus
76.37 ms. All phone clocks remain unlocked. Battery temperatures during latency
runs span 35.3–38.4 °C; they do not measure CPU junction temperature. These are
reproduced observations under the recorded conditions, rather than fixed-clock
ISA speed ratios. The shape-specific streaming results also explain why a
cached kernel win does not translate directly to the same model-wide gain.

[Requests](requests.json) retain each measured token latency and temperature
snapshot, [metrics](metrics.csv) include per-request ranges and round means,
and [telemetry](telemetry.json) summarizes periodic clock observations. Setup,
prefix time, warm TTFT and peak RSS are retained separately. Profiling and dumps
are disabled in all 72 latency requests; exported token IDs match the public
performance fixture and history-view copy counters remain zero.

Separate one-thread/prompt-17 profiles verify executing symbols during measured
subsequent decode. They include execution profiling and CPU sampling and are
excluded from the latency table:

| Policy | Sampled INT2 | Sampled INT4 | Sampled INT8 |
| --- | --- | --- | --- |
| `none` | I8MM `2x32x8_2x4x8` | I8MM `2x32x8_2x4x8` | I8MM `2x32x8_2x4x8` |
| `int2` | DOTPROD `1x32x16_1x4x16` | I8MM `2x32x8_2x4x8` | I8MM `2x32x8_2x4x8` |
| `both` | DOTPROD `1x32x16_1x4x16` | DOTPROD `1x32x8_1x4x8` | I8MM `2x32x8_2x4x8` |

Mean callback worker time in ms per profiled step:

| Policy | Layer INT2 dots | INT2 head dot | Layer INT4 dots | Packing | Callbacks per step |
| --- | ---: | ---: | ---: | ---: | ---: |
| `none` | 33.35 | 12.89 | 19.86 | 0.82 | 32,077 |
| `int2` | 23.26 | 7.64 | 19.09 | 0.32 | 29,973 |
| `both` | 22.34 | 8.43 | 14.89 | 0.12 | 29,106 |

These diagnostics support the kernel-timing direction and show that the graph
also executes less packing work. Their observer overhead and unlocked clocks
prevent treating the callback differences as a decomposition of the unprofiled
latency reduction. [Kernel samples](kernel-samples.json) preserve actual symbol
names and sample counts; [execution profiles](execution-profiles.json) retain
categories and per-layer summaries. All three sampled INT8 paths remain I8MM.

## Implications for the cost model

For this model and Samsung CPU, the evidence supports a one-row INT2 DOTPROD
choice. INT4's choice depends on the shape and thread count. A backend fix
should collect explicit M=1 cases for both kernel families, retain a separate
fit for one-row DOTPROD kernels, and validate selection with representative
decode N/K extents and streaming weight reads. Larger-row prefill fits need
their own validation rather than assuming the decode ranking transfers.

The known-row packing correction remains necessary with a better cost model.
It supplies the actual M=1 before choosing the layout. Without that correction,
packing selection still uses M=480, and an INT2 I8MM layout can exclude the
one-row DOTPROD kernel at execution. Shape propagation and cost ranking are
separate fixes. The local packing patch can be dropped once the upstream
backend carries its shape-propagation change.

This optional architecture restriction lets developers reproduce a specific
selection policy while investigating the learned cost model. The retained
baseline and its evidence remain available. The exact checks compare YNNPACK
against its own retained arithmetic control. The preceding native comparison
records generation-quality differences as a separate investigation.

## Reproduction

The normal pinned dependencies and retained packing correction are the starting
point. Use a fresh experiment directory and preserve the existing baseline:

```sh
python3 tools/bootstrap.py --directory .deps/dot-control --no-tokenizers
cp -a .deps/dot-control .deps/dot-experiment
GIT_CEILING_DIRECTORIES="$PWD/.deps/dot-experiment" \
  git -C .deps/dot-experiment/XNNPACK apply \
  "$PWD/patches/experiments/ynnpack-one-row-dotprod.patch"
cmake -S . -B build-android-dot-experiment -G Ninja \
  -DCMAKE_TOOLCHAIN_FILE="$ANDROID_NDK/build/cmake/android.toolchain.cmake" \
  -DANDROID_ABI=arm64-v8a -DANDROID_PLATFORM=android-28 \
  -DANDROID_STL=c++_static -DCMAKE_BUILD_TYPE=Release \
  -DLAB_DEPS="$PWD/.deps/dot-experiment" \
  -DLAB_ENABLE_TOKENIZERS=OFF -DLAB_BUILD_DOT_BENCHMARK=ON
cmake --build build-android-dot-experiment --parallel 8 \
  --target gemma4_e2b dot_decode_bench
```

Use an explicit ADB serial, check device resources, and stage the binaries and
verified assets as documented in the root README. The benchmark requires ARM
DOTPROD and I8MM support. [Command templates](commands.json) use configurable
device paths. Create `p17.tsv` and `p1024.tsv` by selecting the corresponding
lines from the checked-in E2B performance fixture. CPU masks belong to the
recorded Samsung topology and must be checked on another device.

[Identities](identities.json) record the dependency revisions, optional patch,
compiled source, binaries, fixtures and build flags. [Hardware](hardware.json)
records the device model, CPUinfo family, frequency tiers and affinity. The
NDK is r28c, libc++ is static, runner optimization is `-O1`, and backend kernels
use their own optimization flags. SME/SME2 remain disabled.
