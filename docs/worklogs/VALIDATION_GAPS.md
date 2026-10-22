<!-- Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0 -->

# Validation and reproduction gaps

Use fresh run identities and explicit pass/fail/skip status. Historical migration
checks do not establish coverage for the current checkout. The [result index](../../results/README.md)
is the entry point for measurements; [benchmarking](../BENCHMARKING.md) defines timing boundaries.

## Current campaign coverage

The refresh covers the i9-12900K host, TECNO LJ9 and Pixel 8, plus a
[Samsung / Pixel 11 extension](../../results/2026-10-21-current/phone-expansion/README.md).
The connected Google device reports Pixel 11 / Tensor G6, not Pixel 10. The Pixel 8 preflight found about 2.1 GiB free storage and 3.2 GiB
available memory; larger-model skips must state their resource basis.

All general-runner packages currently declare capacity 2048. They reject a
mismatched capacity argument. Use matching exported packages for other capacities;
the Gemma comparison runners provide the existing 2048/8448 capacity experiment.
Do not mutate package metadata to bypass this contract.

Complete coverage requires numerical/state comparisons, reset, nonzero position,
partial final chunks, window crossings and capacity boundaries. Treat diagnostic
runs separately from latency. Confirm matching token IDs, continuation counts,
math flags and actual prefill work for every external comparison. Missing controls
are missing coverage, not evidence of parity or a performance advantage.

The October 21 clean staged-source build passes all 30 CTests. Fresh full-model
reset checks are byte-identical for E2B/E4B, Qwen3-0.6B/4B and Qwen3.5 INT8
on the host, and E2B on the initial TECNO/Pixel 8 phones. The extension records
its reset and capacity checks separately. All 96 vision fixture comparisons pass.
These checks establish the recorded state/arithmetic scope, not model-quality
parity. Qwen3-0.6B Android preparation fails before correctness execution.
See the [current records](../../results/2026-10-21-current/README.md).

## HF global KV scale interpretation

The [source audit](../../results/hf_published_kv_audit_2026-10-02/README.md)
observes a factor of 16 between global checkpoint and published-bundle scales.
The `*_published_kv` profiles apply an explicit compatibility policy. Source
intent remains unresolved: retain both policies and compare clipping, KV-code
error and logits before calling either a correction.

## Numerical quality

The [Qwen3.5 quantization study](../../results/qwen35_quantization_20261015/README.md)
retains failed numerical gates. Keep INT8/INT4-MLP experimental; throughput does
not qualify model quality. Qwen3 and alternative Gemma arithmetic also have
recorded drift. Report finite outputs, logit error, centered cosine, KL, greedy
agreement and live-state differences as applicable. Teacher-forced agreement
alone is not a sustained-generation or task-quality result.

## Reproduction inputs

Public Gemma extraction uses hash-verified recipes. Some Qwen/vision parameter
packages and external comparison controls remain supplied local assets; checked-in
plans alone do not reproduce their preparation. Document the exact checkpoint,
parameter/fixture hashes and numerical policy. Complete independent reproduction
needs public asset/build recipes without private compiler dependencies. Do not
publish weights or private authoring sources to fill that gap.

## Current attention policy drift

The fresh short screen changes greedy predictions for the FP32 row layout
(5/6 agreement for each Gemma variant) and E4B integer attention (3/6).
E2B integer attention matches all six greedy predictions but changes logits and
KV codes. Keep these as experiments; neither layout naming nor a short greedy
match establishes equivalence. Capacity-only dump comparisons remain exact
(744 E2B files and 2,328 E4B files). See the
[current numerical records](../../results/2026-10-21-current/numerical-comparisons.json).

The direct-HF short screen is finite but differs from the published-bundle
baseline: BF16/FP32 profiles agree on 5/6 greedy outputs and the static-integer
profile on 4/6. This compares different source/arithmetic policies and is not a
quality qualification or proof that a KV-scale policy is correct.
