<!-- Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0 -->

# Performance questions to reproduce

The current refresh uses the pinned XNNPACK `0a66ebb5817f` and Slinky
`a3eec6fcfe30` with the Rust/`.ynn` runners. Earlier observations below are
**not revalidated** until a fresh result explicitly says otherwise. See the
[result index](../../results/README.md) for retained evidence and current coverage.

## Reproduced in the current refresh

Qwen3-0.6B fails during Android preparation: Pixel 8 reports allocation failures,
and TECNO aborts in Scudo mapping/cleanup. The host prepares the same package.
See the [fresh reproduction](../../results/2026-10-21-current/qwen-android-allocation.md).
Investigate completion-dependency metadata allocations and their lifetimes in
`Graph::Compile`; do not attribute this solely to model weights or native kernels.

The fresh host vision screen reproduces a MobileNetV2 execution gap: about
45.9 ms versus 4.75 ms at one thread and 16.0 ms versus 5.29 ms at four,
using the paired FP32 controls. All independent output fixtures pass. These
measurements do not yet attribute the gap to selected depthwise or other kernels.
The [native Android screen](../../results/2026-10-21-current/vision-android/README.md)
reproduces the MobileNetV2 gap on TECNO LJ9, Pixel 11 and Samsung SM-S937U1:
four-thread YNNPACK/LiteRT latency ratios are 6.51, 7.49 and 5.50. It uses
LiteRT's official `benchmark_model_main` entry point. All 216 fixture checks
pass. Pixel 11's YNNPACK ResNet variants also take longer with four threads
than with one on the prime core; SME/SME2 kernels are disabled. The exact
affinity, build audit, repeated timings and frequency/thermal snapshots are
retained; this does not yet attribute the slowdown to a scheduler or kernel.
The [same-cluster follow-up](../../results/2026-10-21-current/vision-android/pixel11-same-cluster.md)
reproduces slower YNNPACK ResNet18 with four threads (170.1 ms) than one
(97.0 ms) on the same Pixel cluster. LiteRT improves from 75.7 to 20.3 ms.
Core choice alone does not explain the recorded slowdown; further attribution
requires profiling, and the SME-disabled build remains the measured scope.
Qwen3.5 INT4-MLP is also much slower than the other tested profiles; its numerical
gates remain unresolved. See the [current baseline](../../results/2026-10-21-current/README.md).

Fresh host graph-window samples select AVX-VNNI low-bit dot kernels for Gemma
and INT8 dot kernels for Qwen. In the sampled decode windows, E2B INT2/INT4 dot
symbols account for about 43%/37% of sampled cycle periods; E4B's leading INT4
dot accounts for about 80%. The leading INT8 dot accounts for about 76% for
Qwen3-0.6B, 92% for Qwen3-4B and 94% for Qwen3.5 INT8. These are diagnostic
sample shares, not uninstrumented token-latency fractions, and do not attribute
unprofiled HF/INT4-MLP or ARM gaps. See the
[selected symbols](../../results/2026-10-21-current/selected-kernel-samples.json).

## Questions awaiting fresh attribution

| Question | Reproduction and evidence | Completion check |
| --- | --- | --- |
| Does long-history decode still spend substantial time converting/packing KV? | Run E2B/E4B at prompts 17/128/1024, fixed capacity and threads; collect separate execution profiles. [Earlier evidence](../../results/2026-10-08-kv-history/README.md). | Identify selected kernels and conversion costs; compare unprofiled latency and outputs. Preserve live intervals, capacity strides and fresh-only append. |
| Which attention policies trade accuracy for speed? | Run the [existing policies](../ATTENTION_EXPERIMENTS.md) with matching weights and independent attention checks. | Report numerical changes separately from layout changes, on host and ARM. Integer Q/P arithmetic is experimental. |
| Are low-bit decode kernels selected appropriately on ARM? | Use the reusable one-row benchmark with streaming working sets, then full models. [Oryon evidence](../../results/2026-10-05-oryon-dot-selection/README.md). | Record actual selected kernels, compatible packing and matched output checks. A microbenchmark win alone is insufficient. |
| Where do setup time and memory go? | Use separate `--report_memory` runs and setup profiles; both phases currently prepare weights independently. | Attribute source residency, packed weights, KV and scratch without double counting. Separate setup from warm execution and record cache policy in comparisons. |
| Does graph preparation still require excessive stack? | [E4B reproduction](../../results/e4b_2026-10-02/preparation-stack-overflow.txt). | Prepare the affected graph with bounded stack use. A larger execution-thread stack is a workaround, not closure. |
| Which vision operators explain execution/setup gaps? | Use the [native Android comparison](../VISION.md#android-comparison-with-the-native-litert-benchmark) with matching FP32 assets; profile MobileNetV2 depthwise, ResNet convolution and ResNeXt preparation separately. | Independent output checks and fresh one/four-thread measurements with selected-kernel evidence. |
| Can ordinary tensor graphs compete with custom recurrence? | [Reusable step harness](../RECURRENT_STEP_EXPERIMENT.md), [layout/chunk evidence](../../results/2026-10-17-recurrent-followup/README.md). | Independent FP64 state checks and stable paired results against the same controls; preserve allocator and reassociation labels. |

No new optimization is implied by this list. Close an issue only with evidence
for its affected model, device, shapes, numerical contract and thread count.
Capacity-only differences require exact numerical checks before timing analysis.

## Samsung capacity sensitivity

The [fresh phone extension](../../results/2026-10-21-current/phone-expansion/README.md)
flags roughly 12% slower E2B prefix/TTFT at prompt 1024 when capacity increases
from 2048 to 8448 on Samsung SM-S937U1. The forward/reverse check exceeds the
existing 10% threshold, with equal argmax sequences. Request ranges show substantial
variation and clocks are unlocked; controlled thermal/frequency reproduction is
needed before attributing this to attention over unused capacity. Keep the failed
timing gate as evidence. Qwen3-0.6B preparation also fails on Samsung and Pixel 11;
see the allocation record for the distinct error messages.
