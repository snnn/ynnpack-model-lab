# Execution profiling

The model runner accepts `--profile_execution=decode`. It writes
`execution_profile.jsonl` alongside the usual timing records. Profiling is
disabled by default. Use separate output directories for diagnostic and latency
runs; diagnostic records carry `timings_valid_for_benchmark: false`.

```sh
./build/gemma4_e2b \
  --bundle_dir=assets/gemma4_e2b/bundle \
  --parameter_dir=assets/gemma4_e2b/parameters \
  --cases_file=models/gemma4_e2b/fixtures/performance.tsv \
  --output_dir=out/decode-profile --cache_capacity=2048 --num_threads=4 \
  --warmup_runs=1 --measured_runs=1 --profile_execution=decode
python3 tools/analyze_execution_profile.py \
  --ynn out/decode-profile/execution_profile.jsonl \
  --output out/decode-profile/analysis.json
```

## Measurement and attribution

Generated construction functions are setup functions. They do not execute a
layer. Generated operation labels instead associate authored scopes and inputs
with backend values. The checked-in E2B, E4B, and all five HF profile builders
contain these labels. Builders without labels still run, with explicit
unattributed profiling entries. The
[October 8 refresh](../results/2026-10-08-builder-refresh/README.md) adds labels to
the E4B and HF artifacts while preserving their computation and state contracts.

The adapter associates optimized backend functions with those labels before
Slinky recycles symbol IDs. It tags diagnostic call names, preserving Slinky's
reserved `memcpy` name, then instruments the final scheduled call and copy
statements. Instrumentation removes the temporary name tags. It preserves
kernel arguments, scheduling, fusion, state ordering, and output bindings.
Eliminated intermediate values retain available fused-operation origins; shared
origins remain shared. Scheduled copies and runtime-generated calls without
stable provenance are explicitly unattributed. Do not infer a layer from a
recycled numeric symbol or expose intermediate outputs to obtain timing labels.

Only measured subsequent decode steps are collected. Warmups, prefill, the
first logits-producing prompt token, construction, and packing during setup are
excluded. Each step records its position, live history length, complete-step
wall interval, and events `[worker, call_id, start_ns, end_ns]`. The initial
metadata record identifies operations and calls. Timestamps use the process's
steady monotonic clock. Worker identifiers are local to the profile.

Callback duration measures work on a worker. Summing parallel callbacks does
not produce decode latency. The analyzer reports worker time and interval unions
separately, excludes the enclosing graph timer from callback totals, and retains
time outside callbacks. Categories and layers can overlap; their interval
unions are not additive. Time outside callbacks includes interpreter/dispatch,
allocation and synchronization, embedding/host work, and profiler overhead.

The analyzer also emits an `attention` summary for all steps and separately for
each case, including the actual history range. It separates scheduled SDPA
dequantization, packing, QK, PV, and mask/softmax/other work. A dot retaining a
dequantization origin is counted as a dot once; provenance alone does not
establish where the conversion executes. Calls with both attention and other origins
remain explicitly mixed. These labels describe callback work, not every
instruction executed inside a kernel.

Each step's `wall_partition` divides its wall interval into attention callbacks
only, other callbacks only, their overlap, and time outside callbacks. These
four fields sum to the step interval. The attention fields include callbacks
with mixed origins; inspect that category before treating the coverage as
exclusively attention. This accounting avoids adding overlapping category
unions or dividing worker time by the thread count. It does not assign gaps to
attention or establish the critical path. Profiled wall coverage is diagnostic;
use separate unprofiled runs for throughput and to check instrumentation cost.

For a history-length investigation, hold capacity, threads, affinity, assets and
continuations fixed, and replay exact token IDs at several prompt lengths.
Reverse case and runner order in another round. Inspect local-window and global
attention separately: local work should saturate at its window, while global
work continues growing. Check the authored matmul shapes as well as selected
kernels. Keeping grouped query heads as separate batch entries can expose
one-row matmuls; combining heads that share KV into matrix rows can permit
reuse across queries. Neither a different layout nor a quantized-KV kernel is
an established optimization until measured and numerically validated.
The retained [Samsung history investigation](../results/2026-10-08-kv-history/README.md)
shows this accounting, the matrix-layout difference and the thermal limitations.

Events use bounded per-worker buffers, flushed after the timed step. Event loss
invalidates the trace and fails the diagnostic run. A failed request produces an
incomplete step and must be discarded; profiling does not make state updates
transactional. Timers and recording add overhead even when no output dump is
requested. Compare against an unprofiled run and use unprofiled results for
throughput claims. Confirm actual selected kernels with a separate CPU sample
profile; operation labels do not identify an ISA.

## Preserved native XNNPACK control

`tools/build_native_profile.py` relinks a compatible archived Gemma4 Tensor API
driver with its recorded libraries. Supply an external native-build archive;
this lab does not rebuild or distribute the archived runtime or its weights.

```sh
python3 tools/build_native_profile.py \
  --archive "$NATIVE_BUILD_ARCHIVE" --output out/native-profile-build
```

The archive must include `build.json`, `driver.cc`, `runner.android`, and
accessible recorded compiler/linker inputs. Source replacements require the
matching staged-driver interfaces and fail on unexpected source. Build commands
and machine-local provenance remain under the ignored output directory.
The recorded control binary and XNNPACK archive hashes must both match.

Run the diagnostic binary with the original runner arguments and
`--profile_post_ops=true`, reused runtimes, warmups, and measured repetitions.
The flag now collects preprocessing, projection, attention, post-attention/MLP,
and head stages. Each operator record includes its type, formats, weight role
when identifiable, and nanosecond samples. Stage records include wall samples
and monotonic invoke timestamps. Collection excludes warmups and first logits.

```sh
python3 tools/analyze_execution_profile.py \
  --ynn out/decode-profile/execution_profile.jsonl \
  --native out/native-profile-capture --output out/profile-comparison.json
```

Native operator times include dispatch and threadpool joins. Compare those
with YNNPACK wall intervals and complete-step latency, and present YNNPACK
worker totals as a separate quantity. Match tokens, continuations, capacity,
threads, affinity, and weight codes. Retain native alignment/padding and
quantization differences in the report. Check both profilers against their own
uninstrumented controls before interpreting a cross-runner gap.

## Selected kernel samples on Android

Record diagnostic execution with the NDK's ARM64 `simpleperf`, using
`-e cpu-cycles:u -f 499 --clockid monotonic`. Attach to the diagnostic process
or record its full command. Sampling adds overhead; keep this separate from
unprofiled latency runs. The record may include setup, warmups and prefill.
The analyzer filters these out using measured subsequent decode intervals:

```sh
python3 tools/analyze_cpu_samples.py \
  --simpleperf-dir "$ANDROID_NDK/simpleperf" --record out/decode.perf.data \
  --ynn out/decode-profile/execution_profile.jsonl \
  --output out/decode-kernels.json
# For the preserved control, replace --ynn with:
# --native out/native-profile-capture
```

YNNPACK filtering uses graph-run envelopes. Native filtering uses runtime
invocation start through last operator completion, excluding host collection.
Both clocks use Android's monotonic clock. The output records included sample
counts, CPUs and exclusive instruction-pointer cycle shares with binary
basenames. It contains no device paths or process addresses. These shares
identify executing kernels; they do not measure wall-time fractions or prove
that a different ISA would be faster.
