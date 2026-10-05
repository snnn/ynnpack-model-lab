<!-- Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0 -->

# Retained measurements and validation

Start with [performance gaps and investigation priorities](../docs/PERFORMANCE_GAPS.md).
These records support backend investigations; each describes its captured
configuration. Historical timing is not automatically a measurement of the
current generated builders.

| Record | Role | Comparison scope |
| --- | --- | --- |
| [E2B original comparison](2026-10-02/README.md) | Primary performance baseline: 75 configurations, 225 measured requests, kernel samples, and capacity controls | Linux, TECNO, Pixel; YNNPACK versus static/packed LiteRT-XNNPACK and phone native Tensor API-XNNPACK |
| [E4B integration](e4b_2026-10-02/README.md) | Primary larger-model baseline, state checks, and preparation-stack reproduction | Desktop static-QAT LiteRT-XNNPACK control; TECNO YNNPACK timing has no matched phone control |
| [Initial HF safetensors](hf_safetensors_2026-10-02/README.md) | Precision/source-format experiment with much slower BF16 execution | YNNPACK HF profiles versus published-source YNNPACK and independent numerical references |
| [HF integer-FC follow-up](hf_fp32_arithmetic_2026-10-02/README.md) | Quantized FC speed recovery, higher RSS, and arithmetic checks | Matched x86-64 YNNPACK profiles; not a new comparison against packed-dynamic XNNPACK |
| [HF published-KV audit](hf_published_kv_audit_2026-10-02/README.md) | Correctness and intermediate-value investigation | Numerical references only; no performance claim |
| [Native tokenizer validation](native_tokenizers_validation_20261005.json) | Input/reference parity and exact text-to-TSV replay | Correctness only, with dumps and no controlled latency campaign; Qwen model execution is not included |

Small summaries, per-request timings, command templates, hashes, and focused
test/failure records belong here. Model payloads, raw profiles, machine logs,
private compiler material, and temporary PR-review experiments remain local.
See [publication contents and privacy](../docs/PUBLICATION.md).
