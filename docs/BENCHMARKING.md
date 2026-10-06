# Benchmarking

Use the same token IDs, prompt lengths, forced continuations, thread counts,
affinity, and capacities when comparing runs. Keep weights and activation/KV
quantization fixed unless changing them is the explicit experiment.

The C++ runner also accepts text and corpus inputs; see
[TOKENIZERS.md](TOKENIZERS.md). Every run writes `resolved_cases.tsv` and
`frontend.json`, including tokenizer/input identities and resolved counts.
Replay the exported TSV to compare the exact IDs across frontends or runtimes.

Start with prompts 17, 128, and 1024, capacities 2048/8448, and one/four threads.
The checked-in performance TSV has 32 forced continuation tokens per prompt.
Use one warmup and three measured repetitions initially. For chunk-boundary
correctness, use `correctness.tsv` (prompts 1/128/129/1024, two continuations).
Add 130 tokens when specifically testing a short second prefix chunk: the last
prompt token is withheld for the first full decode invocation, so 129 prompt
tokens correspond to exactly 128 prefix rows here.

## Metrics

| Metric | Calculation / scope |
| --- | --- |
| Setup | Mapping, embedding initialization, graph construction and preparation |
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
noisy phone throughput.

## Collecting runs

The root README provides single-process commands. Use `taskset` before the
executable for explicit affinity; choose masks from the actual device topology,
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

For regressions, retain raw observations and binary/dependency/model hashes.
For per-layer and operator execution diagnosis, see [PROFILING.md](PROFILING.md).
Profiled timing records are diagnostic; collect unprofiled latency separately.
Separate authoring, backend packing, kernel selection, and thermal changes before
attributing a difference to “dynamic shapes.” The historical comparison in
`MEASUREMENTS.md` includes different activation contracts in its static versus
packed-dynamic rows, and is labeled accordingly.

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
