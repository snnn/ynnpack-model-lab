<!-- Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0 -->

# Qwen3-0.6B Android preparation failure

The fresh Pixel 8 `ynn-llm` build failed to prepare the checked-in
Qwen3-0.6B package at capacity 2048. One thread returned `std::bad_alloc`
(exit 1, about 90 seconds). Four threads aborted (exit 134, about 132 seconds).
The crash record identifies:

```
Scudo ERROR: internal map failure (error desc=Out of memory)
```

Symbolizing the matching unstripped binary places the allocation under
`std::__ndk1::__tree<...>::operator=`, `lab_ynn::Graph::Compile`,
`lab_graph_compile`, `GraphBuilder::prepare`, and `Session::load`.
No warm timing is reported. This identifies the failing preparation path;
it does not by itself establish the allocation growth's root cause.

Reproduce using the current Android build and the hash-matching package:

```sh
adb -s "$ANDROID_SERIAL" shell "$REMOTE_ROOT/bin/ynn-llm" \
  --graph_dir="$REMOTE_ROOT/qwen" --bundle_dir="$REMOTE_ROOT/qwen" \
  --parameter_dir="$REMOTE_ROOT/qwen/parameters" \
  --cases_file="$REMOTE_ROOT/qwen/perf.tsv" \
  --output_dir="$REMOTE_ROOT/qwen-repro-new" \
  --cache_capacity=2048 --num_threads=4 --warmup_runs=1 --measured_runs=3
```

Preflight available memory was approximately 3.2 GiB. The same package prepares
on the host, but host residency is not a guarantee of Android preparation
requirements. A separate one-thread diagnostic returned `std::bad_alloc` after 82 seconds.
Polling its own `/proc` status observed a 4.73 GiB resident high-water mark
and up to 3.29 GiB swapped out (these maxima need not be simultaneous).
The [samples](qwen-android-memory.json) are preparation diagnostics, not latency
measurements. Attribute allocations before proposing a change. Completion requires successful preparation and numerical/
state validation, not merely suppressing the allocation exception.

The TECNO LJ9 one-thread attempt also aborted (exit 134). Its crash stack
contains `scudo::reportMapError` while draining allocator blocks during
`std::__ndk1::__tree::destroy` / `lab_graph_delete`. This is a failure during
preparation cleanup; the captured stack does not establish the original
exception. Keep it distinct from the Pixel's explicit out-of-memory message.

## Samsung / Pixel 11 extension

The newly connected Samsung SM-S937U1 (SM8750) and Pixel 11 (Tensor G6)
also fail before warm execution at both one and four threads. Samsung exits
134; its matching crash record reports `Scudo ERROR: internal map failure
(error desc=Out of memory)`. Pixel 11 exits 1 and prints `std::bad_alloc`.
No throughput is inferred from these failed attempts. Preflight available RAM
was approximately 3.08 GiB on Samsung and 4.45 GiB on Pixel 11. These values
are snapshots, not allocation limits. This extension uses the metadata-fixed
Android binary; see its [identities and records](phone-expansion/README.md).
