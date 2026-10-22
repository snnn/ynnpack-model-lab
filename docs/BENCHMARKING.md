# Benchmarking

Use the same token IDs, prompt lengths, forced continuations, thread counts,
affinity, and capacities when comparing runs. Keep weights and activation/KV
quantization fixed unless changing them is the explicit experiment.

The Rust Gemma runners also accept text and corpus inputs; see
[TOKENIZERS.md](TOKENIZERS.md). Every run writes `resolved_cases.tsv` and
`frontend.json`, including tokenizer/input identities and resolved counts.
Replay the exported TSV to compare the exact IDs across frontends or runtimes.

Token-ID fixtures have three tab-separated columns: case name, comma-separated
prompt IDs, and comma-separated forced continuation IDs (`-` for none). The last
prompt token runs through decode for first logits; subsequent tokens are
teacher-forced. This measures controlled execution, not free-generation quality.

The Rust runners with native kernels, Python command-matrix orchestration, and
measurement analyzers form a small benchmark harness. CTest covers arithmetic, state and
harness behavior without weights. Full-model performance checks run explicitly
on the selected device with its model assets and recorded conditions.

`tools/benchmark.py` accepts both the Gemma comparison-runner records and the
general `ynn-llm`/Qwen records. The latter store setup in `setup.json`, final
process memory in `memory.json`, and cumulative state counters in `counters.json`.
Their summary labels final process peak RSS and process counters explicitly;
these are not per-request memory or append measurements. Warmups are executed
but omitted from those runners' timing rows.

Execution profile files begin with metadata describing operations and scheduled
calls, followed by step events. Keep that first record when processing traces;
event IDs alone are not interpretable. The session test checks both phase files,
including their first step. Profiling runs are diagnostics, not latency baselines.

General-runner packages declare a fixed capacity. The currently checked-in
qualified packages use 2048; a different capacity requires a matching package.
Use the Gemma comparison runners for their supported 2048/8448 capacity sweep.

Start with prompts 17, 128, and 1024, capacities 2048/8448, and one/four threads.
The checked-in performance fixtures have different continuation counts:

| Fixture | Forced continuation tokens per prompt |
| --- | ---: |
| `models/gemma4_e2b/fixtures/performance.tsv` | 32 |
| `models/gemma4_e4b/fixtures/performance.tsv` | 16 |
| `models/gemma4_e2b_hf/fixtures/performance.tsv` | 8 |

Use identical counts for each paired comparison, with one warmup and three
measured repetitions initially. For chunk-boundary correctness, use the model's
`correctness.tsv` (two continuations; E2B prompts 1/128/129/1024, with additional
short-chunk/window cases in E4B and HF).
Add 130 tokens when specifically testing a short second prefix chunk: the last
prompt token is withheld for the first full decode invocation, so 129 prompt
tokens correspond to exactly 128 prefix rows here.

## Metrics

| Metric | Calculation / scope |
| --- | --- |
| Setup | Metadata/plan validation, constant hashing, mapping, embedding initialization, graph construction and preparation |
| Tokenizer load/encode | Separate process frontend fields in `frontend.json`; excluded from model setup and warm TTFT |
| Prefix throughput | `(prompt_tokens - 1) * 1000 / prefix_ms` |
| Warm TTFT | `prefix_ms + token_ms` for step zero |
| Prompt/TTFT rate | `prompt_tokens * 1000 / TTFT_ms`; distinct from prefix rate |
| Decode throughput | `1000 / mean(token_ms)` for steps after zero |
| Current RSS | Resident pages reported by `/proc/self/statm` |
| Peak RSS | Process high-water mark; includes preparation and previous cases |
| Append counter | Cumulative copied fresh K/V payload bytes for the process |
| View-copy counter | History-view materialization callbacks; expected zero |

Warm TTFT excludes tokenizer, process launch, model mapping, and graph preparation.
`token_ms` includes embedding lookup, YNNPACK execution, finite checks, and argmax.
`decode_ms` excludes the finite/argmax scan. Neither is a kernel-only metric.
For an end-user startup claim, report setup separately or add it explicitly.

Peak RSS includes resident mmap weight and embedding pages. It is not private
anonymous memory or the memory needed for one request. Text runs release the
tokenizer before model setup, but peak RSS still includes its allocations and
libc may retain freed pages. Inspect the frontend's current/peak RSS snapshots.
The prototype does not page out source weights and has no packed-weight disk cache. Compare it carefully
with an XNNPACK process that loads an existing cache. Change prompt token
distribution when evaluating embedding residency; repeated token fixtures do not
represent every workload.

For allocation diagnosis, add `--report_memory` to a separate run. It writes
`memory.jsonl` after setup, each prefix, and each first decode. It records current
and peak RSS, resident anonymous/file-page categories from Linux `smaps_rollup`,
and each phase's scratch counters. With glibc 2.33 or newer it also records
allocated/free arena bytes and allocator-owned mmap bytes from `mallinfo2`.
Android does not expose these glibc fields.

Scratch hooks count bytes requested through Slinky's execution allocation
callbacks across the root and worker contexts. They report live bytes,
cumulative allocated bytes/calls, and a concurrent high-water mark. They exclude
preparation, weight packing, source mappings, and caller-owned KV buffers. The
root-pool field covers only that pool; zero root retention alone does not imply
zero worker scratch. Cumulative allocation volume is not simultaneously live
memory or hardware memory traffic. A free returns storage to the allocator;
libc may retain those pages in RSS. Free arena bytes are allocator accounting,
not an exact count of resident or immediately reclaimable pages.

These hooks add atomic operations inside execution even though snapshots are
outside timed regions. Use these runs for memory diagnosis, then disable the
option and dumps for latency comparisons. The option neither trims allocator
arenas nor pages out weights. Do not add overlapping RSS and allocator fields
as if they were separate allocations.

Capacity changes allocate additional storage. For E2B the exact KV increment is
`delta_capacity * 9216` bytes; 2048 to 8448 adds 56.25 MiB. At identical logical
history, this must not imply attention over the unused capacity. Check emitted
pipeline extents, outputs, and timing together rather than infer work solely from
noisy phone throughput. E4B uses 28,672 KV bytes per capacity token; the same
capacity increase adds 175 MiB.

## Collecting runs

The [model guides](README.md#run-workloads) provide single-process commands.
Use `taskset` before the executable for explicit affinity; choose masks from the actual device topology,
not from another phone. Keep CPUs awake, record temperatures/battery and governor
state, allow cooldown between processes, and run only one benchmark per device.
Do not compare a cold/throttled trial with a warm high-frequency one.

`tools/benchmark.py` runs an explicit command matrix and retains command arrays,
logs, status, battery snapshots (ADB), timing records, and summaries. Example:

```json
{
  "cooldown_seconds": 25,
  "jobs": [{
    "name": "ynn-c2048-t4",
    "engine": "ynn",
    "argv": [
      "./build/gemma4_e2b",
      "--bundle_dir=assets/gemma4_e2b/bundle",
      "--parameter_dir=assets/gemma4_e2b/parameters",
      "--cases_file=models/gemma4_e2b/fixtures/performance.tsv",
      "--output_dir={output}",
      "--cache_capacity=2048", "--num_threads=4",
      "--warmup_runs=1", "--measured_runs=3"
    ]
  }]
}
```

Save this as `out/matrix.json`, then run:

```sh
python3 tools/benchmark.py --config out/matrix.json --output out/matrix-results
```

For ADB, add `serial` and `remote_root` to the JSON and use on-device paths in
the argument arrays. The script expects binaries/assets to be present; it does
not change governors, push models, or delete device files. Every output directory
must be new. An external baseline can be another job if its output format is
one supported by `summarize`; otherwise add a parser with explicit metric scope.

Set `capture_telemetry: true` to capture accessible Android frequency/governor
and thermal sensors before and after every job, including non-capacity runs.
Permission-denied sensors remain explicit in the raw capture. Android's toybox
`taskset` accepts a hexadecimal mask; Linux's `taskset -c` syntax is not portable
to every phone.

## Capacity invariance check

At fixed prompt and continuation IDs, increasing reserved KV capacity should
leave warm prefill/decode latency approximately unchanged. Attention still uses
the valid history and window. Setup and KV storage can grow; these are reported
separately and do not enter the latency check. Different physical strides,
cache/TLB behavior and unlocked clocks can still affect timings, so a threshold
crossing needs investigation rather than immediately proving excess attention
work.

Add `capacity_sweep` to a normal benchmark configuration and use the literal
`--cache_capacity={capacity}` argument:

```json
{
  "initial_cooldown_seconds": 60,
  "cooldown_seconds": 60,
  "capacity_sweep": {
    "capacities": [2048, 8448],
    "rounds": 2,
    "max_latency_change_percent": 10
  },
  "jobs": [{
    "name": "ynn-t4",
    "engine": "ynn",
    "argv": [
      "./build/gemma4_e2b",
      "--bundle_dir=assets/gemma4_e2b/bundle",
      "--parameter_dir=assets/gemma4_e2b/parameters",
      "--cases_file=models/gemma4_e2b/fixtures/performance.tsv",
      "--output_dir={output}",
      "--cache_capacity={capacity}", "--num_threads=4",
      "--prefill_rows=128", "--warmup_runs=1", "--measured_runs=3"
    ]
  }]
}
```

Save as `out/capacity.json` and run:

```sh
uv run --locked python tools/benchmark.py \
  --config out/capacity.json --output out/capacity-results
```

Select affinity from the device's topology and prepend `taskset` plus that mask
to the argument array. For Android, add an explicit `serial` and a prepared
`remote_root`, and supply on-device binary, asset and fixture paths. Only
`{capacity}` and `{output}` are substituted. Each job runs all capacities in
forward then reverse order: with two capacities and two rounds, the process
order is 2048/8448/8448/2048. Add independent one-thread or other-model jobs to
the same configuration. Rounds must be even and at least two.

The harness writes `capacity-check.json` and exits nonzero if a latency ratio
falls outside the configured band. It compares prefix time, warm TTFT and mean
subsequent-token latency separately, excluding warmups and the first-token step
from decode. For each case/capacity, the ratio is the median of the paired
rounds' mean-latency ratios against the smallest capacity. Per-round request
ranges and process setup/RSS remain in the report. Both large slowdowns and
speedups flag capacity sensitivity; either can reflect thermal/order bias.
Ten percent is an initial configurable tolerance, not a universal performance
guarantee or a shared-CI timing gate.

Checks require matching resolved token-ID files, arguments, model profile,
chunk/thread settings and complete measured requests. Dumps, execution profiling
and memory-hook timings are rejected. Argmax sequences and zero history-view
copy counters must agree; exact logit/KV comparisons still belong in separate
correctness runs. One warmup and at least three measured requests are required.
Android sweeps retain battery, frequency/governor and accessible thermal-zone
snapshots before and after each process. They do not change frequency controls;
snapshots are not execution-window averages. Raw device captures stay in ignored
outputs.

Recheck an existing sweep without executing the model again:

```sh
uv run --locked python tools/capacity_sweep.py out/capacity-results
```

## What belongs in the repository

See [publication contents and privacy](PUBLICATION.md) before retaining a new
record. `uv run --locked python tools/check_publication.py` checks candidate public files;
`--staged` checks the exact file contents in the Git index. Keep device models,
firmware/toolchain versions, selected kernels, affinity, and artifact hashes.
Replace device serials and machine-specific paths with labels or configurable
locations. Review text fixtures for personal content as well.

Retain established model/backend baseline measurements and reusable benchmark
tools in Git. Temporary pull-request reviews, including their patches, dedicated
harnesses, profiles, reports, and timing records, stay in ignored `out/`
directories or an external local archive. Do not commit them to this repository.
When an upstream change is adopted into the lab's normal dependency baseline,
record a new baseline with its exact revision and configuration; keep temporary
PR-review artifacts separate from that lasting record.
