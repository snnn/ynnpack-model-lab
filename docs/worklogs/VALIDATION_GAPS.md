<!-- Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0 -->

# Validation and reproduction gaps

Use fresh run identities and explicit pass/fail/skip status. Historical migration
checks do not establish coverage for the current checkout. The [result index](../../results/README.md)
is the entry point for measurements; [benchmarking](../BENCHMARKING.md) defines timing boundaries.

## Current campaign coverage

The [semantic runtime baseline](../../results/semantic_runtime_20261022/README.md)
records all 26 packages and distinguishes the earlier full-model matrix from
the final DSL checks. All 423 migrated sources retain exact typed identities;
all 26 model compiler outputs are byte-identical. Final DSL binaries pass 36
host CTests, all 11 timing-configuration correctness checks, the public Qwen3
author matrix, and 14 checks on Pixel 8/Pixel 11. All 11 paired host performance
configurations pass the original setup, latency and memory gates. Android
coverage includes native state, arithmetic and ResNet18; full-LLM qualification remains blocked
by the frozen Qwen control's allocation failure during native compilation.

The earlier October 21 refresh covers the i9-12900K host, TECNO LJ9 and Pixel 8, plus a
[Samsung / Pixel 11 extension](../../results/2026-10-21-current/phone-expansion/README.md).
The connected Google device reports Pixel 11 / Tensor G6, not Pixel 10. The Pixel 8 preflight found about 2.1 GiB free storage and 3.2 GiB
available memory; larger-model skips must state their resource basis.

Gemma semantic packages declare a capacity range; the shared runner checks an
override against that range and the authored tensor bounds. Fixed-capacity Qwen
packages require matching exports for other capacities. The semantic baseline
includes E2B/E4B comparisons at 2048 and 8448. Do not mutate package metadata to
bypass these contracts.

Complete coverage requires numerical/state comparisons, reset, nonzero position,
partial final chunks, window crossings and capacity boundaries. Treat diagnostic
runs separately from latency. Confirm matching token IDs, continuation counts,
math flags and actual prefill work for every external comparison. Missing controls
are missing coverage, not evidence of parity or a performance advantage.

The October 21 clean staged-source build passes all 30 CTests. Fresh full-model
reset checks are byte-identical for E2B/E4B, Qwen3-0.6B/4B and Qwen3.5 INT8
on the host, and E2B on the initial TECNO/Pixel 8 phones. The extension records
its reset and capacity checks separately. All 96 host vision fixture comparisons pass.
The [native Android vision screen](../../results/2026-10-21-current/vision-android/README.md)
adds 216 passing comparisons on TECNO LJ9, Pixel 11 and Samsung SM-S937U1:
YNNPACK at one/four threads and LiteRT's official `run_model` at one thread,
against the same three PyTorch fixtures per model. LiteRT four-thread timing
does not include a separate output-dump check. Seven models fully delegate to
XNNPACK; ResNeXt retains 16 CPU concatenations between 17 XNNPACK partitions.
The separate Pixel 11 same-cluster ResNet18 follow-up adds nine passing fixture
checks with the same binaries and assets.
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
