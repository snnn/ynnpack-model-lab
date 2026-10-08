<!-- Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0 -->

# Gemma4 E2B decode profiling and native XNNPACK comparison

The October 5 YNNPACK packing baseline is slower than the preserved native
Tensor API/XNNPACK runner on these phones. The new execution profiler localizes
the remaining work to low-bit FCs, live-history attention/packing, and time
outside scheduled callbacks. Samsung is correctly detected as Oryon; its I8MM
selection differs from the native control's DOTPROD selection. Pixel's separate
CPUinfo issue remains unresolved.

These are fresh October 5 measurements: 20 unprofiled configurations and 96
measured requests, followed by separate diagnostics. They use the adopted
dependencies plus the retained known-row packing correction. Temporary
PR-review configurations and ISA overrides are not used.

## Unprofiled latency

All cases use capacity 2,048, 32 forced continuation tokens, one warmup, and
three measured requests per process. Samsung repeats the matrix with reversed
runner/thread order, giving six requests per configuration. Decode means exclude
the first logits-producing prompt token. Throughput is `1000 / mean_decode_ms`.

| Samsung threads | Prompt tokens | Native ms/token | YNNPACK ms/token | YNNPACK/native latency |
| ---: | ---: | ---: | ---: | ---: |
| 1 | 17 | 58.17 | 73.40 | 1.26× |
| 1 | 128 | 61.37 | 74.46 | 1.21× |
| 1 | 1024 | 87.25 | 92.61 | 1.06× |
| 4 | 17 | 20.75 | 27.17 | 1.31× |
| 4 | 128 | 25.72 | 29.29 | 1.14× |
| 4 | 1024 | 31.46 | 53.56 | 1.70× |

At prompt 1024/four threads, Samsung achieves 31.79 tok/s native versus
18.67 tok/s YNNPACK. Native's one-to-four-thread speedup is 2.77×; YNNPACK's is
1.73×. Long-history thread scaling is therefore an investigation target. This
is observed full-request scaling, with unlocked clocks and different kernels.

The focused four-thread follow-up uses three measured requests per case:

| Device | Prompt tokens | Native ms/token | YNNPACK ms/token | YNNPACK/native latency |
| --- | ---: | ---: | ---: | ---: |
| TECNO LJ9 | 17 | 33.62 | 38.75 | 1.15× |
| TECNO LJ9 | 1024 | 39.13 | 54.54 | 1.39× |
| Pixel 8 | 17 | 44.99 | 47.43 | 1.05× |
| Pixel 8 | 1024 | 48.18 | 71.91 | 1.49× |

Use [metrics.csv](metrics.csv) and [requests.json](requests.json) for ranges,
individual token timings, warm TTFT, setup and peak RSS. Samsung prompt-1024
request means span 27.34–35.08 ms native and 39.39–58.31 ms YNNPACK. Native's
one-thread short cases also vary substantially between rounds. Battery
temperatures during the Samsung latency campaign span 36.7–39.6 °C; these are
not CPU junction temperatures. Results are observations under the recorded
conditions, rather than thermally isolated estimates.

## What the profiles establish

The profiler times final scheduled execution callbacks. Construction helpers
only author graphs and are excluded. Operation provenance is captured before
Slinky recycles symbols, retained through fusion where available, and carried
to scheduled calls without exposing intermediate outputs. All 35 E2B layers
are represented. Unattributed work is below 0.2% of measured worker time in
these diagnostics.

The Samsung short-prompt, one-thread profile is dominated by FC work:

| Work | YNNPACK callback worker ms | Native operator wall ms |
| --- | ---: | ---: |
| Layer INT2 FCs | 30.78 | 29.09 |
| Layer INT4 FCs | 18.12 | 10.32 |
| Layer INT8 FCs | 2.22 | 0.82 |
| INT2 head dot/FC | 11.43 | 9.60 |

One thread removes parallel-worker summation from this comparison, but callback
and native operator scopes still differ. INT4 FCs are a substantial short-case
target. Native durations include dispatch and threadpool joins. YNNPACK records
some FC epilogue and quantization work in separate callbacks.

For Samsung prompt 1024/four threads, the diagnostic step means are 58.72 ms
YNNPACK and 27.73 ms native. YNNPACK has 45.95 ms of callback-busy wall coverage
and 12.76 ms outside callbacks. Its summed worker work is 146.86 ms, which is
not decode latency. The corresponding short-case outside-callback time is
4.04 ms. About 32,077 callbacks execute per short step and 36,254 per long step.

Long-history YNNPACK callback interval unions include 3.60 ms QK dots, 3.15 ms
PV dots, 4.54 ms other attention and 5.45 ms packing. Category unions overlap
on multiple threads and **must not be added as a wall-time breakdown**.
Native's combined quantized-KV batch-matmul operator wall total is 3.28 ms.
YNNPACK's scheduled attention dots have FP32/FP32 inputs and sampled execution
includes KV dequantization and packing; native executes F32/QC8W batch-matmul
kernels. This identifies a live-history implementation difference worth
isolating. It does not prove equivalent arithmetic or an exact speedup from
changing that path.

TECNO and Pixel reproduce the long-history pattern. Their YNNPACK diagnostics
also show FP32 attention dots, dequantization/packing and substantial
outside-callback time. The INT2/INT4 ISA difference is specific to Samsung in
these measurements:

| Device | YNNPACK INT2/INT4 decode | Native INT2/INT4 decode |
| --- | --- | --- |
| Samsung SM-S937U1 | I8MM, two-row blocks | DOTPROD, one-row blocks |
| TECNO LJ9 | DOTPROD, one-row blocks | DOTPROD, one-row blocks |
| Pixel 8 | DOTPROD, one-row blocks | DOTPROD, one-row blocks |

Samsung CPUinfo reports all eight cores as `cpuinfo_uarch_oryon` (`0x00400105`).
Cores 0–5 have a 3.53 GHz maximum; cores 6–7 have a 4.47 GHz maximum. Different
frequency tiers do not imply incorrect core-family detection. The backend has
an Oryon cost model. Pixel's A715/X3-as-A510 detection bug is separate.

[kernel-samples.json](kernel-samples.json) records actual executing symbols.
Samples are filtered to measured subsequent decode intervals using monotonic
timestamps, excluding construction, warmups, prefill and first logits. The
Samsung one-thread/prompt-17 YNNPACK run was missed by the sampler; its callback
trace is available, while its ISA is not independently sampled. Other listed
profile cases have samples for both runners. Cycle shares identify kernels;
they are neither wall fractions nor isolated ISA performance comparisons.

## Observer overhead and numerical checks

The separate Samsung four-thread on/off check, without CPU sampling, observes
29.33 → 36.67 ms/token at prompt 17 and 49.55 → 55.95 ms/token at prompt 1024:
25.0% and 12.9% mean increases. Clocks remain unlocked and request ranges are
retained in [profiling-overhead.json](profiling-overhead.json). These estimates
show why profiled timings must not replace the unprofiled latency matrix.
Outside-callback time includes profiler costs, host work, dispatch/allocation,
synchronization and scheduling delays; it cannot all be assigned to Slinky.

Both final profilers preserve their own uninstrumented controls exactly across
prompts 1/128/129/1024 with two continuations: 372/372 byte-identical dumps,
12/12 logit outputs, and 35,555,328 unchanged KV codes per backend. YNNPACK
prefill/decode printed pipelines also match after normalizing memory addresses.
Profiling on/off overhead runs retain identical argmax sequences.

Native and YNNPACK assets share exact signed weight codes. All 1,114 native
payload hashes were checked on Samsung, and both sets of 1,114 payload hashes
were checked on TECNO/Pixel. For 62 differently stored tensors, 1,937,768,448
decoded codes match exactly; the other 1,052 payloads match byte-for-byte.
Native source storage expands 60 INT2 MLP matrices to INT8 and stores embedding/
head codes in INT4; its preserved-static-INT2 operators repack the MLP codes.
YNNPACK maps the compact INT2 representation directly.

Cross-runner outputs differ: 9/12 argmax matches, centered cosine
0.8364–1.0000, maximum logit error 14.6002, and KL up to 1.7162. KV-code
differences are retained in [validation.json](validation.json). This benchmark
does not establish equivalent generation quality.

## Reproduction and limits

[identities.json](identities.json) records binary/source/dependency hashes and
build settings. The native control is the exact preserved October 2 binary
(`66df3296…`); profiling relinks its driver with the same archived libraries.
The YNNPACK main Samsung latency campaign uses a preserved profiling-capable
binary with profiling disabled. Attribution uses the corrected implementation;
final source formatting/relinks receive separate correctness checks.

The YNNPACK runner uses `-O1`, construction builders use `-O2`, and backend
targets retain their own kernel flags. The archived native driver uses `-O2`;
both drivers disable floating-point contraction. YNNPACK targets Android API
28; the preserved native driver targets API 24. Do not attribute the gap to a
single compiler flag without inspecting the actual kernel builds.

[commands.json](commands.json) contains configurable command templates and
[fixtures/](fixtures/) contains the matching timing inputs. Samsung affinity is
core 7 for one thread and cores 4–7 for four threads. TECNO uses cores 4–7;
Pixel uses cores 5–8. Governors/frequencies were not changed. Jobs run sequentially
per device with 25-second cooldowns. Tokenization, dumps and diagnostic
instrumentation are disabled for the main latency matrix.

Native uses packed-dynamic INT4 prefill (`qp8_all`), preserved static INT2,
reused stage runtimes, shared workspace/weight cache, chunk 16 for prompt 17
and chunk 128 for longer prompts, and KV alignment 32. YNNPACK uses static QAT
FCs and real prefill chunks of at most 128 rows. Native pads its final prefill
chunk and aligned attention extent where needed. These differences remain
part of the comparison. Both consume the same prompt/continuation IDs, capacity
and published integer weight codes.

Preparation is excluded from warm TTFT/decode. Four-thread Samsung setup is
about 37–39 s YNNPACK versus 3–4 s native; it cannot explain the measured warm
execution gap. Native shares packed weights across phases; YNNPACK prepares
phase packing separately. Peak RSS is a process high-water mark and includes
different source-storage representations and previous cases. The recorded
1,685 versus 2,154 MiB long-case peaks are not a controlled memory-contract
comparison.

The most useful next experiments are a controlled one-row Samsung I8MM versus
DOTPROD comparison; matching FC shapes including head/epilogues; attention
kernels that consume quantized KV directly; and low-overhead sampling of Slinky
dispatch, bounds/shape evaluation and synchronization. Preserve state strides,
real history bounds, numerical references and the current controls throughout.

The [profiling guide](../../docs/PROFILING.md) documents reusable tools.
[operator-profiles.json](operator-profiles.json) retains per-layer/category
worker and wall accounting, native per-layer stage totals, and native operator
categories summed across layers by stage, operator type and weight dtype.
The older individual native operator CSV and per-callback dot/packing tables
have been pruned; category timings, layer/stage totals and original profile
hashes are preserved. See the [retention policy](../README.md#retention) for the
earlier detailed snapshot. Raw events, full CPU profiles, local commands,
archived binaries and compiler material remain in ignored outputs.
