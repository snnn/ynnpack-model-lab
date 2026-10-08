<!-- Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0 -->

# Retained measurements and validation

Start with [performance gaps and investigation priorities](../docs/PERFORMANCE_GAPS.md).
These records support backend investigations; each describes its captured
configuration. Historical timing is not automatically a measurement of the
current generated builders.

| Record | Role | Comparison scope |
| --- | --- | --- |
| [Capacity-invariance follow-up](2026-10-08-capacity-sweep/README.md) | Reusable harness validation: 36 measured requests, forward/reverse capacity order, separate warm latency checks and setup/RSS | Samsung E2B, four threads, prompts 17/128/1,024, capacities 2,048/8,448; paired changes within 5.2% with individual-round thermal variation |
| [October 7 upstream refresh](2026-10-07-upstream-refresh/README.md) | Current normal mobile baseline: 104 configurations, 312 unprofiled requests, 32 separate profiles, 1,764 arithmetic-checked kernel trials and numerical/state checks | New/previous upstream E2B on TECNO/Pixel/Samsung, fresh native E2B controls, TECNO E4B; Linux/HF skipped on the busy host; Pixel throttling and additional rest intervals recorded |
| [October 5 Oryon selection](2026-10-05-oryon-dot-selection/README.md) | One-row cost-model and dispatcher investigation: 336 kernel trials, 72 unprofiled requests, optional selection patch and exact output checks | Samsung E2B: default I8MM versus compatible INT2/INT4 DOTPROD restrictions; normal baseline unchanged |
| [October 5 decode profiling](2026-10-05-decode-profile/README.md) | Phone comparison: 20 configurations, 96 unprofiled requests, separate execution/kernel profiles and exact profiler checks | Samsung one/four threads, focused Pixel/TECNO; previous normal packing baseline versus preserved native Tensor API/XNNPACK |
| [October 5 packing correction](2026-10-05-packing-fix/README.md) | Known-row packing correction: 24 configurations, 72 measured requests, actual DOTPROD/VNNI kernel samples, and capacity checks | Same-pin before/fixed E2B host/phone and E4B host comparisons; exact phone controls and documented desktop numerical differences |
| [October 5 backend refresh](2026-10-05/README.md) | Backend baseline before the packing correction: 87 configurations, 261 measured requests, actual VNNI/I8MM kernel samples, and capacity checks | Same-builder previous/adopted YNNPACK comparisons on Linux and E2B phones; E4B and HF arithmetic controls; XNNPACK comparisons remain historical |
| [E2B original comparison](2026-10-02/README.md) | Historical cross-runtime baseline: 75 configurations, 225 measured requests, kernel samples, and capacity controls | Linux, TECNO, Pixel; YNNPACK versus static/packed LiteRT-XNNPACK and phone native Tensor API-XNNPACK |
| [E4B integration](e4b_2026-10-02/README.md) | Historical larger-model baseline, state checks, and preparation-stack reproduction | Desktop static-QAT LiteRT-XNNPACK control; TECNO YNNPACK timing has no matched phone control |
| [Initial HF safetensors](hf_safetensors_2026-10-02/README.md) | Precision/source-format experiment with much slower BF16 execution | YNNPACK HF profiles versus published-source YNNPACK and independent numerical references |
| [HF integer-FC follow-up](hf_fp32_arithmetic_2026-10-02/README.md) | Quantized FC speed recovery, higher RSS, and arithmetic checks | Matched x86-64 YNNPACK profiles; not a new comparison against packed-dynamic XNNPACK |
| [HF published-KV audit](hf_published_kv_audit_2026-10-02/README.md) | Correctness and intermediate-value investigation | Numerical references only; no performance claim |
| [Native tokenizer validation](native_tokenizers_validation_20261005.json) | Input/reference parity and exact text-to-TSV replay | Correctness only, with dumps and no controlled latency campaign; Qwen model execution is not included |

## Retention

Keep detailed timing and diagnostic records for the current baseline. Older
studies retain reports, metrics and request observations, command templates,
artifact hashes, selected-kernel evidence, and numerical/state checks. Remove
duplicate process logs and per-step captures once summaries support the
conclusions; a resolved issue normally needs a compact explanation and useful
reproducer rather than every investigation log.

The October 5 backend and packing studies retain all request observations,
including per-token latency arrays, in their `requests.json` files. Their
duplicate `timings/` trees have been removed. The older decode profile keeps
YNNPACK category/layer accounting, native per-layer stage totals and native
operator-category totals; individual operator/callback tables have been pruned.
The initial HF studies retain per-request summaries and run settings, without
per-step timing logs. Original detailed captures remain accessible in the
[earlier public snapshot](https://github.com/snnn/ynnpack-model-lab/tree/fa6e613f5513c61a9027659b4c5a3fe247e3780c/results).

The October 7 baseline, historical host/native comparisons, unresolved Oryon
INT4 selection and HF precision/KV evidence, and E4B preparation-stack
reproduction remain available. A local patch or workaround does not establish
that the corresponding upstream issue is resolved.

Model payloads, raw profiles, machine logs, private compiler material, and
temporary PR-review experiments remain local. See
[publication contents and privacy](../docs/PUBLICATION.md).
