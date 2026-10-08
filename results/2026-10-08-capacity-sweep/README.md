<!-- Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0 -->

# Fixed-input capacity check, October 8, 2026 UTC

Exercises the [capacity-invariance harness](../../docs/BENCHMARKING.md#capacity-invariance-check)
using the existing October 7 Android Gemma4 E2B binary on Samsung SM-S937U1.
No model/backend code was rebuilt or changed. The Linux host was not benchmarked.

Four threads, affinity `f0`, capacities 2,048/8,448, prompts 17/128/1,024,
32 forced continuations, maximum 128 real prefill rows. Each process has one
warmup and three measured requests per case. Process order is
2,048/8,448/8,448/2,048, with an initial 60-second idle period and 60-second
cooldowns. All four processes complete: 36 measured requests in total.

Each value below is the median of the two paired-round latency ratios minus
one, expressed as a percentage. Positive values mean the larger capacity is
slower. Prefix time, warm TTFT and subsequent-token latency are distinct;
the first-token step is excluded from decode. Setup and RSS do not enter the
latency check.

| Prompt tokens | Prefix latency change | Warm TTFT change | Decode latency change |
| ---: | ---: | ---: | ---: |
| 17 | +1.38% | +0.11% | -4.38% |
| 128 | -5.13% | -4.71% | -3.32% |
| 1024 | -3.71% | -3.62% | -0.13% |

The configured ±10% check reports **`pass`**. All paired latency changes are
within 5.2%; this sweep does not establish a systematic larger-capacity slowdown.
The reserved E2B KV increment is 56.25 MiB, independent of timing. This is a
capacity-sensitivity screen under the recorded conditions, not a fixed-clock
causal estimate. Battery temperatures span 27.6–35.5 °C;
before/after frequency/governor snapshots and per-request/per-round ranges are
retained. Inspect those observations before assigning a change to attention
over unused capacity.

Individual rounds still drift: prompt-1,024 decode is 10.1% slower at the larger
capacity in the forward pair and 10.3% faster in the reversed pair. The nearly
unchanged paired result should be read alongside these ranges and the thermal
observations, rather than as a claim of precisely equal latency.

The harness verifies identical resolved input IDs, arguments other than capacity,
profile, thread/chunk settings, complete repetitions, identical argmax sequences
and zero history-view copy counters. Dumps/profiling/memory hooks are disabled.
Argmax matching alone does not establish exact logits/KV; the existing
[capacity correctness checks](../2026-10-07-upstream-refresh/README.md#numerical-and-state-checks)
remain the stronger separate evidence.

[record.json](record.json) contains the compact check report, all 36 measured
request summaries with per-token latencies, process setup/RSS, telemetry,
command template, and exact binary/fixture/tool/dependency identities.
Model/build details are shared with the
[October 7 identities](../2026-10-07-upstream-refresh/identities.json).
Raw device/process logs remain in ignored outputs.

For reproduction, use the checked-in performance fixture and the documented
capacity-sweep configuration. Replace the command-template variables with the
same verified assets and a matching Android binary; create a fresh output root
and pass an explicit ADB serial. Do not reuse the affinity mask without checking
the device topology. Both original capacity pairs and their reversed repeats
are retained separately in the check report.
