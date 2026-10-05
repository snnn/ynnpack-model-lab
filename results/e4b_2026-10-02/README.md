# E4B integration records

See `docs/E4B.md` for commands, interpretation, and numerical limitations.
The main runner measurements use capacity 2048, four threads, chunks up to 128,
one warmup and three measured requests per prompt, and 16 forced continuations.
Each engine/platform runs its three cases in one process. Setup and process
peak RSS are recorded separately from warm inference.

- `metrics.json`: final timing table. Host YNNPACK includes the 64-MiB stack
  reservation workaround used by the committed E4B runner.
- `e4b-*-performance.jsonl`: individual invocation records, including warmups.
- `e4b-*-performance.json`: per-request summaries made by
  `tools.benchmark.summarize`.
- `host-c*-correctness.jsonl` and `tecno-correctness.jsonl`: diagnostic runs;
  no warmup, with output dumps enabled. Do not use these as warm benchmarks.
- `capacity-parity.json`: 2,619 host dumps identical at capacities 2048/8448.
- `stack-workaround-parity.json`: 2,619 host dumps unchanged by the explicit
  execution-thread stack workaround.
- `cross-backend.json`: desktop LiteRT/XNNPACK reference versus desktop YNNPACK.
- `tecno-vs-host.json`: desktop versus TECNO YNNPACK. Cross-backend and
  cross-platform differences are substantial; these are not task-quality tests.
- `e2b-regression.json`: unchanged E2B builders and 372 desktop dumps after the
  shared-author/runner refactor.
- `ctest.txt`, `pixel-state-views.txt`: weight-free checks. Pixel did not run
  full E4B because its available memory was below the measured footprint.
- `preparation-stack-overflow.txt`: focused crash diagnosis and workaround.

TTFT is prefix time plus the final prompt-token execution. Prefill throughput
counts `prompt_length - 1` prefix tokens; it is not `prompt_length / TTFT`.
Table TTFT/prefill values are request medians. Decode throughput uses the mean
latency of all 48 measured continuation steps. RSS is the maximum observed
process high-water mark, including model preparation and earlier cases.

The Linux static-QAT LiteRT/XNNPACK control is the preserved Core-authored E4B
graph with a warm on-disk packed-weight cache. It is an external comparison,
not a runtime dependency or an executable included in this repository. It
uses the same extracted source weights and forced-token cases. No packed-dynamic
activation control or matched E4B phone control is included here.

Model weights and large diagnostic dumps are excluded from Git. Each numerical
comparison records hashes of the individual logit vectors for traceability.
