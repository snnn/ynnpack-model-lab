<!-- Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0 -->

# Performance gaps for backend investigation

The current [October 7 mobile baseline](../results/2026-10-07-upstream-refresh/README.md)
adopts merged upstream `d297c798ea53` and records fresh previous-pin/native
comparisons on the three phones, E4B on TECNO, cooled follow-ups, numerical checks
and separate execution/kernel profiles. Linux and host-only HF timings were
skipped because the host was busy. Upstream disables INT2 I8MM until its packing
matches other INT2 kernels; this change is separate from the learned cost model.

The Samsung four-thread repeat is close to the preserved native runner at prompt
17: 20.08 versus 19.71 ms per subsequent token. At prompt 1024, the gap remains
40.39 versus 25.69 ms, or 1.57 times the native latency. The previous-pin repeat
takes 24.41 and 41.38 ms respectively. This points to history-dependent work as
an important remaining target; it does not establish parity across workloads.
The runners also retain different FC activation contracts.

Actual Samsung decode samples show INT2 DOTPROD and INT4 I8MM in the new normal
baseline, while native uses DOTPROD for both low-bit FC paths. Separate profiles
identify INT4 FC and live-history attention/dequantization/packing as remaining
investigation targets. Cached INT4 kernel tests favor DOTPROD, but streaming
results depend on shape; a cached kernel win alone does not justify a universal
selection rule. Profile worker time and native operator wall time have different
scopes and must not be compared as interchangeable timings.

TECNO E4B's prompt-1024, four-thread warm TTFT improves from 15.55 to 12.06 s,
while decode remains approximately 152 ms per token. Linux and HF results below
retain their historical configurations and were not refreshed in this campaign.
TECNO E2B's corresponding warm TTFT improves from 4.31 to 3.58 s, while decode
moves from 57.72 to 60.19 ms per token. Clocks were unlocked, so the small
decode change is not an isolated estimate of an upstream regression.

Pixel's one-thread repeats show large thermal variation and frequency caps in
both versions. After additional rest before each four-thread prompt-1024 process,
previous/new decode is 85.76/86.16 ms per token, essentially unchanged within the
observed variation. These measurements do not establish a new Pixel decode
regression; the report preserves the throttled runs and their limitations.

The [October 5 backend refresh](../results/2026-10-05/README.md) substantially
improves desktop prefill and records actual AVX-VNNI execution. Decode,
preparation, memory, ARM performance, and numerical differences remain useful
backend investigations. This repository provides standalone workloads and
measurements for those questions.

The [packing correction follow-up](../results/2026-10-05-packing-fix/README.md)
restores one-row DOTPROD decode kernels on both tested phones and improves
observed decode throughput. Desktop speed is essentially unchanged, with
documented numerical differences. The baseline records retain their distinct
patch identities and thermal limitations.

The [Samsung Oryon selection study](../results/2026-10-05-oryon-dot-selection/README.md)
isolates another one-row issue after the packing correction. The preserved
native runner uses DOTPROD dispatch tables for its INT2/INT4 FC paths; YNNPACK's
Oryon model predicts I8MM is cheaper. The fitting script excludes one-row
DOTPROD kernels when larger-row kernels share the model family. Its I8MM
training benchmark always measures `M=block_m`, rather than a partial one-row
tile, and targets a 24 KiB resident working set.

At prompt 17, a compatible INT2 DOTPROD restriction reduces YNNPACK's observed
mean decode latency from 70.74 to 55.81 ms with one thread and from 30.58 to
22.09 ms with four threads. INT4's full-model benefit depends on the case and
thread count; direct cached kernel wins alone do not establish an optimal
model-wide policy. These optional selection experiments keep the retained
normal baseline intact and preserve exact logits/KV codes. See the study for
unprofiled request ranges, streaming cases and actual kernel evidence.

## Backend refresh before the packing correction

These fresh i9-12900K comparisons use identical current builders and token IDs:
1,024 prompt tokens, capacity 2,048, four physical P cores, one warmup, and three
measured requests. E2B has 32 forced continuations; E4B has 16.

| Model | Previous TTFT, s | Adopted TTFT, s | Previous prefill, tok/s | Adopted prefill, tok/s | Previous decode, tok/s | Adopted decode, tok/s |
| --- | ---: | ---: | ---: | ---: | ---: | ---: |
| E2B | 1.581 | 0.997 | 659.0 | 1,056.4 | 35.32 | 35.70 |
| E4B | 5.655 | 3.270 | 183.5 | 320.4 | 12.56 | 13.03 |

The backend update reduces warm TTFT by 36.9% for E2B and 42.2% for E4B.
One-thread and capacity-8,448 controls also show large prefill gains. Decode
changes are much smaller and some one-thread cases change in opposite directions.
Clocks were not locked; small differences need more controlled repetitions.

The adopted XNNPACK pin includes
[AVX-VNNI kernels](https://github.com/google/XNNPACK/pull/11521) and the
[learned dot cost model](https://github.com/google/XNNPACK/pull/11568), still
open when adopted. The comparison spans 23 XNNPACK and two Slinky commits,
including the required worker-context initialization interface. There is no
global kernel override, and this is not an isolated estimate of the cost-model
PR's contribution.

The matched E2B phone follow-up uses the same current builders, NDK r28c,
affinity, token IDs, and capacity with 60-second process cooldowns. At 1,024
tokens, the previous/adopted decode rates are 17.96/13.59 tok/s on TECNO and
14.01/11.64 tok/s on Pixel: 24.3% and 16.9% lower throughput respectively.
Prefill changes much less. These observations reproduce the mobile regression;
unlocked clocks and sequential previous/adopted order limit causal attribution.

The new E2B TTFT is near the historical static-QAT XNNPACK value below; E4B
TTFT is below its historical static control. Those controls were not retimed,
so this does not establish a fresh cross-runtime win. Both models' new decode
rates remain below the retained desktop XNNPACK rates. The
[full refresh record](../results/2026-10-05/README.md) includes the phone matrix,
safetensors arithmetic controls, observed ranges, setup, and RSS.

## Known bug: packing ignores the known decode row count

**Status:** the selector behavior is reproduced and a local fix is validated in
[`ynnpack-dot-packing-shape.patch`](../patches/ynnpack-dot-packing-shape.patch).
It is applied by normal bootstrap and has not been submitted upstream. The
behavior remains in upstream `d297c798ea530c12a1878bb3a3a811bdf05d715b`.
The original reproduction below uses
`f5122810ee8bb7461ed73efe7a678a472866cee3`; its measurements retain that identity.

The lab builds and prepares separate prefill and decode graphs. Decode FC inputs
already have a constant row count of one at graph construction. For example,
tensor 1030 in the [E2B decode builder](../models/gemma4_e2b/generated/gemma4_decode_DefineValues_0.cc)
has shape `{1,1,1536}` and feeds an INT2 projection through `g->Dot`.
The [runtime adapter](../runtime/ynnpack_support.h) passes these declared shapes
to YNNPACK. Dynamic attention history does not make this FC row count dynamic.

YNNPACK's packing selection in
[`define_dot`](https://github.com/google/XNNPACK/blob/f5122810ee8bb7461ed73efe7a678a472866cee3/ynnpack/subgraph/dot.cc)
reads the shape of weight tensor B but does not infer M from activation tensor A:

```cpp
dot_shape shape;                  // M defaults to unknown_dot_extent = 2048.
learn_shape_from_b(shape, num_k_dims, b);  // Reads N and K, leaving M unchanged.
shape.m = std::min<size_t>(shape.m, 480);   // Packing selection uses M = 480.
```

This selects a layout for many rows even when M is already known to be one.
At execution, kernel selection sees the actual M but must remain compatible with
the previously chosen weight layout and activation transpose. INT2 I8MM uses
`tile_k=8`; the one-row DOTPROD kernel uses `tile_k=16`. Packing for the former
therefore excludes the latter from subsequent selection.

The October 7 upstream pin disables those INT2 I8MM kernels, so this particular
INT2 layout conflict no longer occurs in its ARM dispatch. The general omission
of A's known row count remains, and the retained correction still supplies that
information for other types/layout decisions. The following selector and timing
observations describe the original revision, where both INT2 candidates existed.

A minimal selector reproduction uses INT8 activations, INT2 weights, INT32
output, and the adopted backend's detected CPU cost model on each phone:

1. Select without a packing constraint at M=480, N=384, K=256: I8MM is chosen.
2. Select at M=1 with the same N/K: one-row DOTPROD is chosen.
3. Repeat M=1 with required `tile_k=8`: I8MM is chosen because DOTPROD is
   incompatible. The same restriction holds for the projection shapes
   N=12288/K=1536 and N=1536/K=12288.

These are selector choices, not measured kernel speed ratios. They provide a
mechanism consistent with the retained Pixel DOTPROD-to-I8MM selection change
and ARM decode regression. The full-model follow-up below measures the retained
correction, with thermal limitations. The previous backend also learned shape
from B alone, so the defect
must not be described as newly introduced by the learned cost-model PR.

The retained correction infers M from A's logical row extent when it is constant,
including rank-one and broadcast cases, before choosing the packing layout.
Genuinely symbolic row counts retain the fallback. Existing packed-FC arithmetic
tests cover one-row and multi-row inputs; full-model validation exercises dynamic
prefill and compares logits/KV with preserved controls. Matched latency runs use
the adopted backend with only this correction. Pixel CPU detection remains a
separate issue to isolate independently.

The [matched follow-up](../results/2026-10-05-packing-fix/README.md) observes
INT2 and INT4 DOTPROD decode on both phones. At 1,024 prompt tokens, capacity
2,048, and four threads, E2B decode changes from 13.55 to 17.88 tok/s on TECNO
and from 10.01 to 12.78 tok/s on Pixel. Desktop E2B/E4B speed is essentially
unchanged. Pixel's warmer control slows across repetitions; the percentages
are observations, not isolated causal estimates.

Existing tests pass and capacity-only comparisons remain exact. Both phones'
E2B logits and KV codes also match the unpatched controls exactly. Desktop
E2B/E4B packing and floating-point kernel choices change numerical outputs,
including one argmax choice per model. Retain those controls and investigate
reference/task quality before claiming equivalent generation.

## Historical cross-runtime comparisons

The [October 5 decode profiling campaign](../results/2026-10-05-decode-profile/README.md)
provides a fresh comparison with the preserved native runner. On Samsung
SM-S937U1, prompt 1024/capacity 2048/four threads reaches 18.67 tok/s YNNPACK
versus 31.79 tok/s native. Focused TECNO/Pixel runs retain a long-history gap
even when both runners select INT2/INT4 DOTPROD. Profiles identify low-bit FC,
FP32 attention with KV dequantization/packing, and outside-callback work as
targets. Samsung CPUinfo correctly identifies Oryon; its I8MM selection is a
separate cost-model/kernel investigation. Profile overhead and unlocked clocks
limit causal attribution; the report retains unprofiled timings and numerical
differences separately.

These October 2, 2026 records use 1,024 prompt tokens, capacity 2,048, four
threads, one warmup, and three measured requests. E2B uses 32 forced
continuations; E4B uses 16. TTFT excludes loading, preparation, and tokenization.
Decode throughput excludes the first-logit step. The original graphs precede
the current standalone builder preparation policy; these are historical
comparisons, not fresh timings of the current checkout.

| Model / device | Comparison path | YNNPACK TTFT, s | Comparison TTFT, s | YNNPACK decode, tok/s | Comparison decode, tok/s |
| --- | --- | ---: | ---: | ---: | ---: |
| E2B / i9-12900K | LiteRT/XNNPACK static QAT | 1.714 | 1.008 | 35.1 | 38.6 |
| E2B / i9-12900K | LiteRT/XNNPACK packed dynamic | 1.714 | 0.861 | 35.1 | 38.7 |
| E2B / TECNO LJ9 | Native Tensor API/XNNPACK packed dynamic | 4.281 | 2.321 | 19.0 | 25.7 |
| E2B / Pixel 8 | Native Tensor API/XNNPACK packed dynamic | 5.345 | 3.592 | 15.5 | 20.9 |
| E4B / i9-12900K | LiteRT/XNNPACK static QAT | 6.019 | 3.651 | 12.6 | 14.6 |

Sources: [E2B metrics](../results/2026-10-02/metrics.csv),
[E2B request records](../results/2026-10-02/requests.json), and
[E4B metrics](../results/e4b_2026-10-02/metrics.json). The full matrices include
shorter prompts, capacity controls, and a one-thread desktop comparison.

Packed dynamic changes the W4 prefill activation/FC contract; it keeps the
original decode graph and W2/W8 paths. Static-QAT rows are the closer arithmetic
control. YNNPACK also loses to those controls at this prompt length on all three
E2B machines. Direct native XNNPACK and fully delegated LiteRT/XNNPACK are
different execution paths and must retain separate labels.

The native prompt timer includes KV allocation/reset. YNNPACK and LiteRT reset
preallocated storage before prefix timing. This difference matters most for
short prompts and large capacity. Phone clocks were not locked; small changes
need more controlled repetitions. See the [full methodology](MEASUREMENTS.md).

## Evidence and next experiments

| Area | What the retained data establishes | Useful next experiment |
| --- | --- | --- |
| x86 prefill FC | Fresh samples put 61.0% of E2B and 75.2% of E4B cycles in an AVX-VNNI INT4 dot. INT8 also selects VNNI. | Compare matching FC shapes and arithmetic against the XNNPACK controls; account for attention, masks, and runtime overhead after the ISA gap narrows. |
| x86 decode FC | E2B sampling is dominated by INT2 AVX2 (42.2%) and INT4 VNNI (37.1%); E4B sampling is dominated by INT4 VNNI (81.7%). | Benchmark the selected low-bit kernels at actual decode shapes/history lengths; investigate packing, bandwidth, and remaining INT2 selection without assuming VNNI is always faster. |
| ARM prefill/decode | The initial refresh regresses decode; the retained [known-row packing correction](#known-bug-packing-ignores-the-known-decode-row-count) restores INT2/INT4 DOTPROD and improves observed phone decode. Pixel CPU detection remains wrong. An SVE transpose takes 13.6% of sampled unpatched prefill cycles. | Repeat under controlled clocks and process order; isolate Pixel CPU detection and localize backend transpose/packing costs separately. |
| Preparation | Fresh desktop setup remains about 13 s for E2B and 35 s for E4B. It is excluded from warm TTFT. | Measure phase packing and preparation separately; investigate sharing prepared constants and a persistent packed-weight cache. |
| Memory | Fresh desktop peaks are 1,684 MiB for E2B and 4,546 MiB for E4B; historical cached LiteRT peaks are lower. Both phases are prepared independently. | Attribute source pages, packed constants, graph state, KV, scratch, and temporary allocations before changing ownership. |
| Attention/state | Capacity-only changes preserve outputs; fresh KV append checks pass and explicit history-view copies remain zero. | Preserve active intervals and capacity strides while profiling history reads, packing, score materialization, and window crossings. |
| Numerical contract | Before the packing correction, previous/adopted desktop E2B outputs are exact and E4B changes one logit vector/84 KV dumps with 27/27 argmax agreement. The packing correction changes one argmax per host model while both phones remain exact. ARM/desktop and HF reference differences remain. | Trace the host packing/kernel differences, including E2B `p1024.decode_0001` and E4B `p513.decode_0002`; retain full logit/KV metrics and evaluate quality separately from teacher-forced timing. |

The [backend refresh kernel summaries](../results/2026-10-05/kernel-profiles.json)
and [packing correction summaries](../results/2026-10-05-packing-fix/kernel-profiles.json)
record actual executed symbols. Their percentages are shares within each separate
profile, not a kernel speed ratio or a complete attribution of the latency
difference. Prefill-focused requests include final prompt-token decode; decode
profiles use different continuation/history ranges from the timing matrix.
The [E4B stack reproduction](../results/e4b_2026-10-02/preparation-stack-overflow.txt)
documents another backend preparation limitation.

## Later results and coverage

The [HF integer-FC follow-up](../results/hf_fp32_arithmetic_2026-10-02/README.md)
recovers performance near the published-source YNNPACK control on x86-64. It
does not establish a win against the earlier packed-dynamic XNNPACK baseline,
and its measured RSS is higher. The October 5 refresh retimes that profile and
its BF16/FP32 controls. Current timings must not be substituted into the old
cross-runtime table without retaining its historical labels.

There is no matched E4B phone control in these records. Qwen tokenizer support
does not include Qwen model-execution measurements. Long-context, sustained
generation, task quality, and thermally controlled ARM profiling remain useful
coverage gaps. The [measurement index](../results/README.md) separates timing
campaigns from correctness-only records.
