<!-- Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0 -->

# Pixel 11: core choice and thread count

The primary screen showed slower four-thread YNNPACK ResNet18 execution
than the one-thread prime-core run. SME/SME2 kernels are disabled in the
tested binaries; the [build audit](provenance.json) verifies this. A separate
follow-up repeats ResNet18 with one thread on CPU 2 and four threads on
CPUs 2–5, all in the same CPU-frequency policy.

Binaries, model, inputs, thread counts, two engine-order rounds, three
warmups and ten timed invocations match the primary screen. The one-thread
affinity changes from CPU 6 (`40`) to CPU 2 (`4`); four threads retain
CPUs 2–5 (`3c`). The campaigns are sequential, with USB power, unlocked
clocks and unchanged governors. All nine additional fixture checks passed.
Original power settings were restored.

| Campaign | Threads / CPUs | YNNPACK mean ms | LiteRT/XNNPACK mean ms |
| --- | --- | ---: | ---: |
| Primary | 1 / 6 | 46.023 | 40.390 |
| Primary | 4 / 2,3,4,5 | 163.749 | 20.319 |
| Same-cluster follow-up | 1 / 2 | 96.992 | 75.666 |
| Same-cluster follow-up | 4 / 2,3,4,5 | 170.095 | 20.327 |

Per-process means, setup, memory, native benchmark distributions, fixture
checks, exact commands and filtered telemetry are retained in the
[follow-up records](pixel11-same-cluster.json). The two campaigns are
shown separately; the later results do not replace the primary rows.

The slowdown persists within the same cluster: YNNPACK's four-thread mean is
1.75 times its one-thread mean (170.095 versus 96.992 ms). Both four-thread
round means, 175.817 and 164.373 ms, exceed both one-thread means, 96.782 and
97.202 ms. LiteRT improves from 75.666 to 20.327 ms on the same masks.

Changing from the prime core to CPU 2 explains part of the primary one/four
contrast, but the slowdown remains after holding the cluster constant.
SME/SME2 kernels are absent from this build. The cause of the remaining
threaded slowdown requires profiling; these timings do not attribute it to
a particular scheduler, synchronization operation, or kernel.
