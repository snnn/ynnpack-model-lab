<!-- Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0 -->

# Retained measurements and validation

Start with [performance gaps and investigation priorities](../docs/PERFORMANCE_GAPS.md).
These records support backend investigations; each describes its captured
configuration. Historical timing is not automatically a measurement of the
current generated builders.

| Record | Role | Comparison scope |
| --- | --- | --- |
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

Small summaries, per-request timings, command templates, hashes, and focused
test/failure records belong here. Model payloads, raw profiles, machine logs,
private compiler material, and temporary PR-review experiments remain local.
See [publication contents and privacy](../docs/PUBLICATION.md).
