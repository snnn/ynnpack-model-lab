<!-- Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0 -->

# Dot packing with known rows, October 5, 2026

The retained [packing patch](../../patches/ynnpack-dot-packing-shape.patch)
uses activation tensor A's known logical row count before selecting a dot
packing layout. The adopted backend previously used its large-row fallback
even for a statically one-row decode graph. The correction restores one-row
DOTPROD selection for INT2 and INT4 decode on both tested phones. Desktop
execution speed is essentially unchanged.

This historical study established the local correction for the normal baseline.
The [earlier backend refresh](../2026-10-05/README.md) remains the control without
this patch. Both use XNNPACK `f5122810ee8bb7461ed73efe7a678a472866cee3`, Slinky
`d18c98551c77f366857f125e3a0f7886deb82a47`, the same CPUinfo pin, and identical
current builders, assets, token IDs, and arithmetic profiles. CPU detection and
cost models are unchanged. The fix has not been submitted upstream.

## Matched warm execution

Four threads, capacity 2,048, 128-row maximum prefill chunks, one warmup and
three measured requests per case. E2B uses 32 forced continuations; E4B uses
16. Affinities are `55` on the i9-12900K, `f0` on TECNO LJ9, and `1e0` on
Pixel 8. Host cooldown is 20 seconds; phone cooldown is 60 seconds.

At 1,024 prompt tokens:

| Device / model | Before TTFT, ms | Fixed TTFT, ms | Before decode, tok/s | Fixed decode, tok/s | Observed decode change |
| --- | ---: | ---: | ---: | ---: | ---: |
| i9-12900K / E2B | 991.55 | 986.50 | 35.91 | 35.95 | +0.1% |
| i9-12900K / E4B | 3,283.71 | 3,265.47 | 12.94 | 13.03 | +0.7% |
| TECNO LJ9 / E2B | 4,099.32 | 4,198.45 | 13.55 | 17.88 | +31.9% |
| Pixel 8 / E2B | 5,498.90 | 5,505.63 | 10.01 | 12.78 | +27.6% |

Short-prompt E2B decode also improves: at 17 tokens, TECNO changes from
18.01 to 25.84 tok/s and Pixel from 15.16 to 20.31 tok/s. Prefill, setup, and
RSS show no corresponding large improvement. Desktop setup remains roughly
13 seconds for E2B and 35 seconds for E4B; peak RSS remains about 1,684 and
4,546 MiB. The full 17/128/1,024 matrix and request ranges are in
[metrics.csv](metrics.csv) and [requests.json](requests.json).

**Clocks are unlocked and the phone comparisons are sequential.** TECNO runs
before/fixed; Pixel runs fixed/before. Pixel battery temperature changes from
31.7 to 33.0 C during the fixed process and from 33.5 to 34.5 C during the
control. Its 1,024-token control request means rise from 90.33 to 107.93 ms,
showing drift. The observed percentage gain includes thermal/order effects;
it is not an isolated estimate of the patch's contribution. TECNO's fixed
process also starts warmer than its control. Battery is a proxy, not CPU
temperature. [Phone observations](phone-observations.json) and
[host observations](host-observations.jsonl) retain the measurements.

TTFT is prefix execution plus the final prompt-token decode. Decode rate is
the reciprocal of pooled subsequent `token_ms`, excluding the first-logit
step. Setup, tokenization, dumps, and profiling are excluded from these timing
runs. No new LiteRT/XNNPACK comparison was measured. Capacity 8,448 is checked
for correctness only; HF profiles, one-thread performance, and E4B phone
performance were not retimed.

## Actual selected kernels

Separate E2B decode profiles use a 17-token prompt, 512 forced continuations,
one warmup, four threads, and capacity 2,048. Sampling starts after warmup.
These are cycle shares, not kernel speed ratios or latency measurements.

| Device | Selected kernel | Sampled cycles |
| --- | --- | ---: |
| i9-12900K | `dot_uint8_int2_int32_1x32x16_1x8x16_avx2` | 43.38% |
| i9-12900K | `dot_uint8_int4_int32_1x16x8_1x8x8_avxvnni` | 38.13% |
| TECNO LJ9 | `dot_int8_int2_int32_1x32x16_1x4x16_neondot` | 40.16% |
| TECNO LJ9 | `dot_int8_int4_int32_1x32x8_1x4x8_neondot` | 31.11% |
| Pixel 8 | `dot_int8_int2_int32_1x32x16_1x4x16_neondot` | 38.78% |
| Pixel 8 | `dot_int8_int4_int32_1x32x8_1x4x8_neondot` | 32.10% |

The earlier unpatched Pixel profile selects I8MM for both INT2 and INT4.
The new layout permits the one-row DOTPROD kernels. Pixel's pinned CPUinfo
still reports A510 on the actual A715/X3 cores used here; fixing that detection
would be a separate intervention. Full sampled symbol summaries and scope are
in [kernel-profiles.json](kernel-profiles.json).

## Numerical validation

All ten existing host tests pass. Existing state-view, quantized-FC, and asset
tests pass on both phones. The patch applies to fresh hash-verified dependency
archives, and repeating bootstrap succeeds. No new packing-layout regression
test was added.

Every tested capacity-only comparison is byte-identical: 372/372 E2B dumps
on host and each phone, and 2,619/2,619 E4B dumps on host. Both phones also
match their retained unpatched E2B controls exactly, including all 35,555,328
KV codes and 12 argmax choices per phone. Append checks pass and history-view
copy counters remain zero.

The patch also affects floating-point packing/kernel selection on x86, where
the unpatched comparisons are not exact:

| Model | Identical dumps | Argmax agreement | Max logit error | Min centered cosine | Max KL | Changed KV codes | Max KV code error |
| --- | ---: | ---: | ---: | ---: | ---: | ---: | ---: |
| E2B | 210/372 | 11/12 | 5.2757 | 0.9671 | 0.3656 | 51,877/35,555,328 | 27 |
| E4B | 1,300/2,619 | 26/27 | 4.5236 | 0.9784 | 0.2818 | 479,201/255,037,440 | 36 |

Changed argmax cases are E2B `p1024.decode_0001` and E4B
`p513.decode_0002`. All compared floating outputs are finite. The patched host
profile includes `dot_fp32_1x16x2_1x4x2_avx2_fma3`, unlike the retained
unpatched profile; the profiling histories differ, so this does not isolate
the first numerical divergence. Bit identity across kernel choices is not
required, but these differences need quality/reference investigation before
claiming equivalent generation. See [numerics-summary.json](numerics-summary.json),
[per-logit comparisons](logit-comparisons.json), and [validation.json](validation.json).

## Reproduction and identity

Build the patched configuration in a fresh tree:

```sh
uv run --locked python tools/bootstrap.py --directory .deps/packing-fix --no-tokenizers
uv run --locked cmake -S . -B build-packing-fix -G Ninja \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ \
  -DLAB_ENABLE_TOKENIZERS=OFF -DLAB_DEPS="$PWD/.deps/packing-fix"
uv run --locked cmake --build build-packing-fix --parallel 8
uv run --locked ctest --test-dir build-packing-fix --output-on-failure
```

For an isolated control, bootstrap a separate `.deps/packing-control` tree,
then reverse only the new patch before configuring its separate build:

```sh
uv run --locked python tools/bootstrap.py --directory .deps/packing-control --no-tokenizers
GIT_CEILING_DIRECTORIES="$PWD/.deps/packing-control" \
  git -C .deps/packing-control/XNNPACK apply --reverse \
  "$PWD/patches/ynnpack-dot-packing-shape.patch"
```

Repeating bootstrap on that control tree would reapply the correction.
The recorded control binaries are the preserved `build-vnni` and
`build-android-vnni` binaries. Android uses the same source correction with
NDK r28c, ARM64/API 28, and static libc++; follow the root Android CMake
instructions with the separate dependency/build directories.

The runner uses `-O1`, builders `-O2`, selector/kernels `-O2`, and subgraph
construction `-O3`; actual flag arrays match between controls. Runner/builder
floating-point contraction remains disabled. CPUINFO, DOTPROD, and I8MM are
enabled; SME/SME2 remain disabled. [Environment identity](environment.json)
retains dependency, patch, builder, fixture, asset, and binary hashes.
[Command records](commands.json) use repository-relative paths and configurable
device directories. Raw profiles, model dumps, device serials, and temporary
diagnostic tools remain outside the published record.

The duplicate per-process `timings/` tree has been pruned. All captured request
summaries and per-token latencies remain in [requests.json](requests.json),
alongside the compact kernel, numerical and identity records. See the
[retention policy](../README.md#retention) for the earlier detailed snapshot.
