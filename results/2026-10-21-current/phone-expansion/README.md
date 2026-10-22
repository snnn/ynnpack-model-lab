<!-- Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0 -->

# Samsung and Pixel 11 extension

Fresh measurements on the newly connected Samsung SM-S937U1 / SM8750
(user's Samsung S25 label) and Google Pixel 11 / Tensor G6. The requested
Pixel 10 was not connected; the user confirmed using the device reporting
Pixel 11. Firmware identities and preflight resources are in [devices.json](devices.json).

This extends the [October 21 baseline](../README.md) with the same E2B and
Qwen3-0.6B packages and [token-ID fixtures](../fixtures/). No model-quality
qualification is implied. The primary screen uses capacity 2048, prompts
17/128/1024, one warmup and three measured requests, at one/four threads.
E2B thread order is repeated in reverse. The separate Gemma comparison runner
checks capacities 2048/8448 in forward/reverse order at four threads.

## Device and timing contract

Samsung uses CPU 7 for one thread and CPUs 4–7 for four: the latter spans
its six-core and two-core frequency domains. Pixel 11 uses CPU 6 for one
thread and CPUs 2–5 for four, a different core class from its prime CPU.
These are explicit affinity configurations, not isolated thread-scaling tests.
CPU masks, maximum frequencies and governors are recorded in the device file.
No governors or frequency controls were changed. Processes ran sequentially
on each phone with 45-second cooldowns. [Sensors](sensors.json) preserve
battery and available frequency/thermal snapshots, not execution averages.
Samsung timing varies substantially; retain both rounds and request ranges.

The deployed `ynn-llm` includes the profiling-metadata fix described in the
parent report. It was built with the same NDK r28c ARM64/API28/static-libc++
configuration; [binary hashes](devices.json) identify the stripped executables.
[Parent identities](../identities.json) record source, plans, toolchains and
unstripped build binaries. Timing runs disable dumps/profiling. Warm TTFT
excludes setup; prefill rate is `(prompt_tokens - 1) * 1000 / mean(prefix_ms)`;
decode rate excludes the first token. Peak RSS is a process high-water mark,
not per-request or exclusive allocation. See [benchmarking](../../../docs/BENCHMARKING.md).

## E2B warm execution

Prompt 1024, capacity 2048. Both rounds are shown; none is selected as best.

| Device / round | Threads | Prefill tok/s | Decode tok/s | Warm TTFT ms | Setup s | Peak RSS MiB |
| --- | ---: | ---: | ---: | ---: | ---: | ---: |
| samsung_s25-primary | 1 | 240.87 | 18.67 | 4301.73 | 36.98 | 5081.07 |
| samsung_s25-primary | 4 | 448.08 | 22.85 | 2325.45 | 44.52 | 5048.74 |
| samsung_s25-repeat | 1 | 226.87 | 17.02 | 4568.31 | 44.69 | 5520.54 |
| samsung_s25-repeat | 4 | 356.84 | 21.18 | 2919.81 | 46.74 | 5031.78 |
| pixel11-primary | 1 | 280.32 | 16.32 | 3710.96 | 46.11 | 4740.25 |
| pixel11-primary | 4 | 242.20 | 12.45 | 4309.49 | 92.30 | 5366.83 |
| pixel11-repeat | 1 | 281.80 | 16.82 | 3689.93 | 46.26 | 5521.90 |
| pixel11-repeat | 4 | 256.92 | 12.30 | 4062.77 | 58.07 | 4798.71 |

[All summaries](summary.json) preserve ranges and shorter prompts;
[request observations](requests.json) retain individual measurements.
[Portable commands](commands.json) require an explicit ADB serial and a fresh
output directory. Deploy the parent's E2B bundle/parameter package under
`${REMOTE_ROOT}/bundle` and `e2b`, and Qwen under `qwen`; copy the matching
performance fixtures as `perf.tsv`. [Process records](processes.json) retain
status, setup, memory, counters and resolved-fixture hashes where emitted.

## Failures and validation

Qwen3-0.6B fails during preparation in all four attempts. Samsung exits 134;
its crash record reports a Scudo out-of-memory mapping failure. Pixel 11 exits
1 with `std::bad_alloc`. No Qwen warm throughput is available. See
[failures](failures.json) and the [allocation issue](../qwen-android-allocation.md).
E4B and external phone runtime controls were not run in this extension;
these are E2B lab timings. E4B's host process peak is about 7.8 GiB, versus
preflight available RAM of about 3.08/4.45 GiB on these phones; omission is
resource planning, not an observed E4B OOM.

Native arithmetic/state/asset/recurrent tests pass on both phones.
[Validation records](validation.json) retain the logs, reset file hashes and
capacity comparison details. Reset checks run prompts 1/130/513 twice with
two continuations, checking all emitted files byte-for-byte.

This extension retains 144 successful measured requests.
- samsung_s25 capacity: **capacity_sensitive**.
- samsung_s25 reset: 99 files; exact=True.
- pixel11 capacity: **pass**.
- pixel11 reset: 99 files; exact=True.

Samsung exceeds the 10% capacity threshold for prompt-1024 prefix time and
warm TTFT (both about +12%); its other checked metrics remain inside the band.
Argmax sequences match across capacities on both phones. Pixel 11 passes the
configured timing check. These results do not include fresh byte-exact
cross-capacity dumps on these phones; the 99-file checks are repeated-request
reset comparisons at fixed capacity. Samsung's noisy observations warrant a
controlled thermal/frequency follow-up, not a relaxed threshold or a claim
that unused KV capacity is necessarily being read.
