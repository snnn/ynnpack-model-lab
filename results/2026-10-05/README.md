<!-- Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0 -->

# Gemma4 backend baseline, October 5, 2026

The adopted backend substantially improves desktop prefill: warm TTFT falls
36.9% for E2B and 42.2% for E4B at 1,024 prompt tokens, capacity 2,048, and four
threads. Samples verify AVX-VNNI INT4/INT8 execution without a kernel override.
E2B INT2 decode still selects AVX2. Decode gains are much smaller, setup and RSS
remain high, and a matched E2B phone follow-up reproduces lower decode throughput
with the adopted backend.

This is a new baseline for the normal dependency pins, using the current
`target_views` builders with singleton decode attention transposes removed.
The October 2 records remain unchanged. XNNPACK controls were not retimed;
comparisons against them below are historical.

This record predates the [known-row packing correction](../2026-10-05-packing-fix/README.md).
That follow-up uses the same dependency revisions with an additional local
patch; these captured timings and patch identities remain unchanged.

## Backend and build identity

| Component | Previous baseline | Adopted baseline |
| --- | --- | --- |
| XNNPACK | `35997e71119d191c807068a4d2aa28bf6048b59b` | `f5122810ee8bb7461ed73efe7a678a472866cee3` |
| Slinky | `97c346749bf0f7fbdc2b0b8e6ff0c380806a32e2` | `d18c98551c77f366857f125e3a0f7886deb82a47` |
| CPUinfo | `8ce83db858065145192c97af90cb668ad72a12e9` | Same |
| Lab builders/runtime | `7c3a9caec93a05e6a72288b4387795e189d89e06` | Same |

The adopted pin includes the merged
[AVX-VNNI kernels, #11521](https://github.com/google/XNNPACK/pull/11521) and the
[learned dot cost models, #11568](https://github.com/google/XNNPACK/pull/11568).
The latter PR was **still open when adopted**. The exact archive is hash-pinned;
this is not a claim that the PR has merged. The Slinky update supplies the
required worker-context initialization API.

The update spans 23 XNNPACK and two Slinky commits. The comparison measures
that backend update as a whole, with unchanged builders and arithmetic policies;
it does not isolate the cost-model PR or assign all gains to VNNI. The retained
CMake patch was rebased onto the adopted revision, removing kernel-registration
hunks now provided upstream. The symbolic runtime patch is unchanged. HF builds
also retain the existing BF16 rounding patch.

Previous dependency sources were checked against a fresh hash-verified
bootstrap with their retained patches. Separate dependency copies and builds
preserved the previous controls. Host builds use Clang 22.1.8; Android uses NDK
r28c, API 28, ARM64, and static libc++. Tokenizers are disabled for these token-ID
runs. CPUINFO, DOTPROD, and I8MM are enabled; SME/SME2 remain disabled.

Actual compile commands show runner `-O1`, builders `-O2`, dot selector `-O2`,
subgraph construction `-O3`, and generated dot kernels `-O2`. Runner/builder
floating-point contraction is disabled in both controls. VNNI kernels compile
with `-mavx2 -mavxvnni`; ARM
I8MM kernels use `-march=armv8.2-a+i8mm`. These are not unoptimized kernel builds.
Exact archive, patch, builder, fixture, model, and binary identities are in
[environment.json](environment.json).

## Fresh desktop comparison

Intel Core i9-12900K, four distinct physical P cores, affinity `55`, prompt
1,024, capacity 2,048. E2B has 32 forced continuations; E4B has 16.

| Model / backend | Warm TTFT, ms | Prefill, tok/s | Decode, tok/s | Setup, s | Peak RSS, MiB |
| --- | ---: | ---: | ---: | ---: | ---: |
| E2B / previous | 1,581.34 | 659.03 | 35.32 | 12.77 | 1,682.9 |
| E2B / adopted | 997.23 | 1,056.39 | 35.70 | 12.95 | 1,684.1 |
| E4B / previous | 5,655.09 | 183.48 | 12.56 | 36.13 | 4,529.1 |
| E4B / adopted | 3,269.87 | 320.41 | 13.03 | 35.38 | 4,546.3 |

Prefill throughput rises about 60% for E2B and 75% for E4B. Decode changes are
only about 1% and 4%, respectively; unlocked clocks and three repetitions do
not support a universal small-gain claim. E2B's one-thread decode changes in
opposite directions across capacities. Setup and RSS show no comparable gain.

| Model, one thread / capacity | Previous TTFT, ms | Adopted TTFT, ms |
| --- | ---: | ---: |
| E2B / 2,048 | 5,598.87 | 3,389.64 |
| E2B / 8,448 | 5,620.10 | 3,288.96 |
| E4B / 2,048 | 20,623.78 | 11,307.73 |
| E4B / 8,448 | 20,621.15 | 11,285.99 |

The complete prompts 17/128/1,024, capacities 2,048/8,448, and one/four-thread
matrix is in [metrics.csv](metrics.csv), including observed ranges. Logical
history stays fixed when capacity changes; the correctness checks below preserve
exact outputs at both capacities.

## Actual kernel execution

These are sampled cycle shares from separate execution profiles, excluding
graph preparation. They are not kernel speed ratios or a full attribution of
the latency changes.

| Device / model / phase | Selected kernel | Sampled cycles |
| --- | --- | ---: |
| Desktop / E2B / prefill | `dot_uint8_int4_int32_5x8x8_1x8x8_avxvnni` | 60.98% |
| Desktop / E2B / decode | `dot_uint8_int2_int32_1x32x16_1x8x16_avx2` | 42.21% |
| Desktop / E2B / decode | `dot_uint8_int4_int32_1x16x8_1x8x8_avxvnni` | 37.05% |
| Desktop / E4B / prefill | `dot_uint8_int4_int32_5x8x8_1x8x8_avxvnni` | 75.24% |
| Desktop / E4B / decode | `dot_uint8_int4_int32_1x16x8_1x8x8_avxvnni` | 81.71% |
| Pixel / E2B / prefill | `dot_int8_int4_int32_10x8x8_2x4x8_neoni8mm` | 48.19% |
| Pixel / E2B / prefill | `transpose_x64_sve` | 13.57% |
| Pixel / E2B / decode | `dot_int8_int2_int32_2x32x8_2x4x8_neoni8mm` | 54.03% |
| Pixel / E2B / decode | `dot_int8_int4_int32_2x32x8_2x4x8_neoni8mm` | 23.82% |
| Pixel / E2B / previous decode | `dot_int8_int2_int32_1x32x16_1x4x16_neondot` | 38.07% |

INT8 VNNI is also sampled on desktop. Disassembly of the sampled INT4 prefill
and decode functions confirms `vpdpbusd` instructions. INT2 remains AVX2 in
these desktop captures; forcing every dot to VNNI would describe a different
experiment. E4B decode is dominated by INT4 VNNI, so the remaining decode gap
cannot be reduced to E2B's INT2 selection alone.

The Pixel capture verifies I8MM execution. Its backend transpose share is
present despite zero explicit history-view copy callbacks; those counters do
not count backend transposes, packing, or attention reads.

The previous Pixel decoder selects DOTPROD INT2 where the adopted decoder
selects I8MM INT2. INT4 selects I8MM in both profiles. This identifies a concrete
selection change to investigate alongside the matched decode regression; the
different cycle shares are not an isolated speed comparison of those kernels.

Prefill-focused profiles include the full final prompt-token decode/head.
Decode profiles use prompt 17 with longer continuations than the latency matrix:
1,024 on desktop E2B, 128 on desktop E4B, and 256 on Pixel. Desktop E4B sampling
starts after preparation and includes its initial short prefix. Pixel sampling
starts after a complete warmup request. Requested workloads, sampling scope,
events, and sanitized flat symbols are in
[kernel-profiles.json](kernel-profiles.json). Raw profiles remain local.

## ARM measurements and paired follow-up

The primary refreshed phone matrix uses four threads, one warmup, three measured
requests, 25-second process cooldowns, and the same published token fixtures.
These 1,024-token rows use capacity 2,048.

| Device / model | Warm TTFT, ms | Decode, tok/s |
| --- | ---: | ---: |
| TECNO LJ9 / E2B | 4,139.8 | 13.60 |
| Pixel 8 / E2B | 5,301.9 | 11.49 |
| TECNO LJ9 / E4B | 15,825.4 | 5.78 |

E2B also runs capacity 8,448 on both phones. E4B runs only on TECNO at capacity
2,048. Pixel E4B is skipped because its initial available memory, about 3.4 GiB,
is below the observed E4B process footprint.

Lower decode rates than the old campaign prompted a fresh previous/adopted
E2B comparison. Both use identical current builders, NDK r28c, assets, fixtures,
affinity, and capacity 2,048, with 60-second process cooldowns.

| Device, prompt 1,024 | Previous TTFT, ms | Adopted TTFT, ms | Previous decode, tok/s | Adopted decode, tok/s |
| --- | ---: | ---: | ---: | ---: |
| TECNO LJ9 | 4,066.05 | 4,179.25 | 17.96 | 13.59 |
| Pixel 8 | 5,306.68 | 5,365.08 | 14.01 | 11.64 |

The follow-up reproduces 24.3% lower decode throughput on TECNO and 16.9% on
Pixel. Short-prompt decode is also lower. Prefill changes much less. Old and new
per-request decode ranges do not overlap in these 1,024-token comparisons.

This is a measured backend regression under the observed conditions, not an
isolated causal estimate for #11568. The order is previous then adopted; clocks
are unlocked. Paired battery temperatures span 27.5–30.0 °C on TECNO and
29.2–31.1 °C on Pixel. Temperature and frequency observations are retained;
device conditions are not fully normalized. There is no fresh paired previous
E4B phone run or fresh XNNPACK phone control in this record.

## Direct safetensors profiles

The same original checkpoint, revision
`dd693ff40353f057ca5f07e945ad867f4afbf2ec`, supplies all HF profiles. Packed codes,
QAT scales, source coefficient precision, and the existing published-compatible
INT8 KV policies are preserved. The global KV division-by-16 convention remains
unresolved. No checkpoint is recalibrated or silently replaced.

These desktop rows use four threads, affinity `55`, capacity 2,048, prompt
1,024, and **eight** forced continuations for every profile, including the
published-source control. The derived signed-code cache is warm; it is not a
backend-prepared weight cache.

| Profile | Warm TTFT, ms | Prefill, tok/s | Decode, tok/s | Setup, s | Peak RSS, MiB |
| --- | ---: | ---: | ---: | ---: | ---: |
| Published source, HF token fixture | 993.94 | 1,059.77 | 35.96 | 13.04 | 1,684.0 |
| HF static integer FC | 1,022.97 | 1,030.35 | 34.09 | 29.73 | 3,665.6 |
| HF BF16 arithmetic | 5,643.99 | 207.85 | 1.38 | 53.90 | 3,045.1 |
| HF FP32 arithmetic | 3,809.69 | 362.14 | 1.02 | 38.59 | 3,002.2 |

The preferred integer-FC profile remains near the published control's warm
execution speed and retains much higher RSS. BF16/FP32 are arithmetic controls,
with different FC/head arithmetic. These timings do not resolve the independent
reference discrepancies in the [HF audit](../../docs/HF_GEMMA4.md). Initial HF
BF16/raw-KV phone experiments retain their historical records; they are not
retimed here.

## Numerical and state validation

Capacity-only changes are exact: E2B has 372/372 byte-identical logit/KV files;
E4B has 2,619/2,619. The fixtures cover empty history, nonzero positions, partial
chunks, window crossings, reset/repeated requests, and E4B's multiple KV heads.
E4B includes prompts 1/8/128/129/130/511/512/513/1,024; E2B uses 1/128/129/1,024.

| Comparison | Greedy agreement | Minimum centered cosine | Maximum KL(reference → candidate) | Maximum absolute logit error |
| --- | ---: | ---: | ---: | ---: |
| Desktop E2B, previous → adopted | 12/12 | 1.000000 | 0 | 0 |
| Desktop E4B, previous → adopted | 27/27 | 0.978448 | 0.313860 | 4.523599 |
| Adopted desktop → TECNO E2B | 12/12 | 0.958334 | 0.201997 | 4.860675 |
| Adopted desktop → Pixel E2B | 12/12 | 0.958334 | 0.201997 | 4.860675 |
| Adopted desktop → TECNO E4B | 25/27 | 0.937470 | 0.178139 | 5.568896 |

Desktop E2B reproduces all 372 files exactly across the backend update. Desktop
E4B reproduces 2,534/2,619: one logit vector and 84 KV files change, all on the
second continuation of the BOS-only case. The first differing saved KV owner
is 3. Other cases are byte-identical. The cause has not been isolated to an
operator or kernel; this remains an actionable short-history numerical case.
Of 255,037,440 compared E4B KV codes, 17,668 differ, with maximum code error 25.
See [the localization record](e4b-backend-difference-location.json).

E2B also reproduces 372/372 files across the backend update on each phone, and
the adopted TECNO/Pixel outputs are byte-identical. The E2B cross-platform
differences below were therefore already present with the previous backend
and current builders. E4B has no matching previous-backend phone capture here.

Cross-platform KV differences are much larger: 17,802,867/35,555,328 E2B codes
differ on each phone, maximum error 182; TECNO E4B differs on
168,066,496/255,037,440 codes, maximum error 255. Full per-output logit and KV
metrics are retained in `numerics/`. All compared floating outputs are finite.
Teacher-forced greedy agreement does not establish equivalent generation quality.

Every execution checks fresh append payloads, 9,216 bytes/token for E2B and
28,672 for E4B. History-view copy counters remain zero. These do not exclude
backend history reads, dequantization, packing, or materialized attention scores.
Host CTest passes 10/10 for each backend; the HF BF16 rounding test and the
state/FC/asset tests pass on both phones. Native tokenizer execution is outside
these token-ID builds. Test scope is recorded in
[validation.json](validation.json).

## Historical XNNPACK context and remaining gaps

The October 2 desktop XNNPACK controls reported E2B TTFT 1,008.3 ms for static
QAT and 861.3 ms for packed dynamic, with decode 38.6/38.7 tok/s. The new YNNPACK
E2B is near that historical static TTFT and still above packed dynamic; its
decode is lower. E4B's new TTFT, 3,269.9 ms, is below the historical static
3,650.5 ms, while its decode remains below 14.61 tok/s. These are **historical
references, not fresh A/B cross-runtime measurements**.

The retained native Tensor API/XNNPACK phone controls reported TECNO TTFT
2,321.3 ms and decode 25.7 tok/s, and Pixel TTFT 3,591.8 ms and decode 20.9 tok/s.
The refreshed YNNPACK phone rows retain higher TTFT and lower decode rates than
those historical controls. They were not rerun under the new campaign's device
conditions.

Packed dynamic changes the W4 prefill activation/FC contract. Static QAT is
the closer arithmetic control. XNNPACK controls also use existing prepared
weight caches, which materially affect setup and RSS comparisons. Warm request
timing excludes those setup costs.

Useful next work is matching low-bit decode shapes against the established
XNNPACK paths, investigating the ARM selection regression, tracing the E4B
short-history numerical difference, and separating packing, runtime, attention,
and memory costs. The new profiles support these narrower investigations after
the dominant desktop prefill ISA gap has narrowed.

## Method and retained files

There are **87 configurations, 261 measured requests, and 87 warmups**: 60 host
configurations, 15 primary phone configurations, and 12 paired phone follow-ups.
Correctness and profiling requests are separate and excluded from those counts.
Each performance case has one warmup and three measured requests, chunks of up
to 128 real rows, and identical prompt/continuation IDs within each comparison.

TTFT is prefix execution plus final prompt-token decode/head. Prefill throughput
is `(prompt_tokens - 1) * 1000 / prefix_ms`; it is distinct from prompt/TTFT.
Tables use median TTFT and prefill rate. Decode throughput is `1000 / mean`
of all measured continuation `token_ms`, excluding the first-token step:
96 samples for E2B, 48 for E4B, and 24 for HF per configuration. `token_ms`
includes embeddings, finite checks, and argmax. Setup and tokenization are
excluded from warm timing.

Only one benchmark runs per device. Host latency/profiling excludes competing
builds and numerical reductions. Host clocks use `intel_pstate`/`powersave` and
are not locked. Phone affinities are `f0` on TECNO and `1e0` on Pixel, selected
from their topology. Governor reads are unavailable on TECNO. Dumps, profiling,
and allocation instrumentation are disabled in latency runs.

Peak RSS is a process high-water mark, including preparation, resident source
mappings, packed weights, KV, scratch, and earlier cases. HF source validation
touches mapped tensor pages. Mmap and the derived cache do not exclude these
pages from RSS. This prototype has no persistent backend packed-weight cache.

The interrupted HF capture was discarded from this baseline and restarted in a
fresh output directory. Host temperature/frequency observations have a coverage
gap across that interruption and begin after the first E2B pair. No incomplete
measurement is included. Initial Android attempts referenced stale parameter
directories and failed before timing; current parameters were deployed for the
retained captures. Those failed attempts remain in ignored local logs.

Retained files include aggregate [metrics](metrics.json), per-request
[observations](requests.json), portable [command templates](commands.json),
raw per-token `timings/`, fixture snapshots, artifact/environment identities,
kernel symbol summaries, numerical reports, and test summaries. Command paths
are normalized to configurable locations. Device serials, host identities,
private checkpoint paths, model weights, raw profiles, and build logs remain
outside Git.

Use the root [build/asset instructions](../../README.md) and
[fresh dependency directory procedure](../../patches/README.md). For this
token-ID campaign, bootstrap with `--no-tokenizers` and configure
`-DLAB_ENABLE_TOKENIZERS=OFF`. Use separate HF dependencies with `--hf-bf16`.
The previous public lab source revision above supplies its old pins and patches;
build it in a separate checkout for the previous control. `commands.json`
contains templates: substitute the binary for its device/profile/backend,
asset directories, and a fresh output directory. Check the local CPU topology
before choosing affinity. Follow [BENCHMARKING.md](../../docs/BENCHMARKING.md)
for aggregation and metric scope.
