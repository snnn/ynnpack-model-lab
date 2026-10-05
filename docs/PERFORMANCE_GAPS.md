<!-- Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0 -->

# Performance gaps for backend investigation

The retained Gemma4 measurements show YNNPACK behind the established
XNNPACK paths, especially in prefill. This repository gives backend engineers
standalone workloads and evidence for investigating those costs. Symbolic
state works; it has not established a full-model speed advantage.

## Comparable retained measurements

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
| x86 prefill FC | About 72% of sampled YNNPACK cycles are in an AVX2 INT4 dot; the XNNPACK controls select AVX-VNNI for their dominant W4 GEMM. | Compare matching FC shapes and quantization, then investigate YNNPACK VNNI implementation/selection. |
| ARM prefill/decode | Large full-model gaps are measured, but this campaign has no warm ARM kernel sampling. YNNPACK source includes I8MM kernels. | Record the actual selected FC/attention kernels and packing costs before attributing the gap to an ISA or scheduler. |
| Preparation | E2B takes roughly 12 s on desktop and 34–49 s on phones; E4B takes roughly 35 s on desktop and 125 s on TECNO. | Measure phase packing and preparation separately; investigate sharing prepared constants and a persistent packed-weight cache. |
| Memory | Published-bundle YNNPACK retains more RSS than cached LiteRT, less than the preserved native runner, and independently prepares both phases. | Attribute source pages, packed constants, graph state, KV, scratch, and temporary allocations before changing ownership. |
| Attention/state | Capacity-only changes preserve outputs; fresh KV append checks pass and explicit history-view copies remain zero. | Preserve active intervals and capacity strides while profiling history reads, packing, score materialization, and window crossings. |
| Numerical contract | Cross-backend logit/KV differences remain; packed-dynamic and HF profiles change arithmetic. | Keep static controls and independent references, and evaluate quality separately from teacher-forced timing. |

The [flat kernel reports](../results/2026-10-02/README.md) support the x86
kernel-path explanation. Their percentages are shares within each profile,
not a kernel speed ratio or a complete attribution of the latency difference.
The [E4B stack reproduction](../results/e4b_2026-10-02/preparation-stack-overflow.txt)
documents another backend preparation limitation.

## Later results and coverage

The [HF integer-FC follow-up](../results/hf_fp32_arithmetic_2026-10-02/README.md)
recovers performance near the published-source YNNPACK control on x86-64. It
does not establish a win against the earlier packed-dynamic XNNPACK baseline,
and its measured RSS is higher. Later graph-preparation and tokenizer changes
have validation evidence; their results must not be substituted into the old
cross-runtime table without a matched campaign.

There is no matched E4B phone control in these records. Qwen tokenizer support
does not include Qwen model-execution measurements. Long-context, sustained
generation, task quality, and thermally controlled ARM profiling remain useful
coverage gaps. The [measurement index](../results/README.md) separates timing
campaigns from correctness-only records.
