<!-- Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0 -->

# Current measurements and unresolved issues

Use the [current issue list](../docs/worklogs/README.md) to choose an
investigation and the [benchmarking guide](../docs/BENCHMARKING.md) to reproduce
measurements. A result applies only to its recorded binary, plans, assets,
backend revisions, device and numerical contract.

## Current baseline

The [October 21 current baseline](2026-10-21-current/README.md) covers the
Rust/`.ynn` host workloads, E2B on TECNO LJ9 and Pixel 8, paired capacity checks,
vision controls, and attention/HF/recurrent screens. It retains 612 measured LLM
requests, artifact identities, commands, numerical comparisons and selected-kernel
evidence. The [Samsung / Pixel 11 extension](2026-10-21-current/phone-expansion/README.md)
adds fresh phone measurements and records Samsung capacity sensitivity. Qwen3-0.6B Android preparation fails; E4B phone runs were skipped for
resource constraints. Alternate attention/HF profiles change outputs and remain
experiments. Older campaign timings are not substituted for this checkout.

The [Android vision extension](2026-10-21-current/vision-android/README.md)
tests all eight FP32 classifiers on TECNO LJ9, Pixel 11 and Samsung SM-S937U1
at one/four threads. Its baseline is LiteRT's native `benchmark_model_main`
entry point, with 216 passing independent fixture comparisons. The earlier
Linux Python control remains labeled separately.

## Evidence retained for unresolved issues

These records have **not been revalidated by the current refresh**. Their dates
and original configurations are intentional; they support questions to reproduce,
not current performance claims.

| Issue | Supporting record |
| --- | --- |
| ARM low-bit kernel selection | [Oryon selection](2026-10-05-oryon-dot-selection/README.md) |
| History conversion/packing | [KV history](2026-10-08-kv-history/README.md) |
| Attention arithmetic/layout tradeoffs | [Attention profiles](2026-10-09-attention-profiles/README.md) |
| HF global KV scale interpretation | [Source audit](hf_published_kv_audit_2026-10-02/README.md) |
| Recursive graph preparation stack use | [E4B reproduction](e4b_2026-10-02/preparation-stack-overflow.txt) |
| Quantized Qwen3.5 numerical gates | [Quantization](qwen35_quantization_20261015/README.md) |
| Ordinary-op recurrence performance | [Step experiment](2026-10-16-recurrent-step/README.md), [layout/chunk follow-up](2026-10-17-recurrent-followup/README.md) |

## Retention

Keep the current baseline's request observations, portable commands, artifact
identities, validation summaries and selected-kernel evidence. Keep the minimum
older evidence needed to reproduce an unresolved issue. Remove superseded
campaigns and resolved migration history rather than maintaining a project diary.
The removed campaigns have a local archive outside this repository.

Model payloads, private compiler material, raw profiles, machine logs, and
upstream PR-review experiments remain outside Git. See [publication guidance](../docs/PUBLICATION.md).
