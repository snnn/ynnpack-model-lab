# Runtime preparation prototype: 2026-10-22

Keep the semantic `Program` plus immutable assets as the preparation boundary.
The prototype demonstrates one public Rust/ISLE compiler and one Rust blockwise
operation implementation. Keep semantic-input preparation opt-in. The evidence
does not yet qualify a default change: some operation cells miss or do not resolve
the latency gate, and the full-model ARM64 comparison is unavailable.

## Comparison and scope

A is the frozen offline runner with the corrected native blockwise operation.
B prepares the semantic program in process and retains that operation.
C also implements the whole blockwise operation in Rust, with runtime ISLE
strategy selection and a native kernel/thread-pool bridge. A and B are frozen
external controls, not maintained fallback implementations. The final source has
one blockwise implementation. Offline package loading remains the default.

The Qwen3-0.6B recipe uses INT8 linears, FP32 activations/KV, and INT8 embeddings.
It tests preparation and session behavior; the separate W4 matrix tests the Rust
operation. Public Rust Qwen replay is bit-exact against its own A at one/four
threads for prompts 1/17/128/129/130/1024 plus reset, with four decode steps and
420 complete logit/KV tensors per comparison. Linux passes all 35 CTest checks,
including 386 frozen compiler packages and 2,196 numerical requests in each
runtime/offline fixture campaign. The three existing named backend failures are
unchanged. ARM64 blockwise, state, ownership, failure-cleanup and session checks
pass, including 15 larger W4 outputs per thread count against A and B.

## Paired measurements

The [machine-readable record](summary.json) includes revisions, patch/binary
hashes, per-cell confidence intervals, preparation samples, and lifecycle data.
Qwen uses four physical P cores on the i9-12900K. W4 uses one/four cores there and
one/four matching middle cores on Pixel 11. Each fresh process runs one warmup
and three measured requests, with alternating comparison order. Filesystem
caches are warm; dumps/profiling and competing builds are off. Qwen has 16
continuation tokens per prompt. Six pairs are extended to twelve for unresolved
warm-latency comparisons. W4's entire matrix has twelve pairs.

A process contributes a median request time; decode contributes the median of
per-request mean subsequent-token latency. Ratios below one favor the candidate.
Intervals are Student-t intervals of paired log ratios, with no correction for
multiple comparisons. Phone clocks use the default governor; thermal snapshots
and five-second interprocess pauses are retained with the raw local observations.
Several four-thread phone cells remain noisy, so these are not fixed-frequency
kernel throughput claims.

| Comparison | Pairs | Setup ratio | TTFT ratios (17 / 128 / 1024) | Decode ratios (17 / 128 / 1024) | Retained RSS delta |
| --- | ---: | --- | --- | --- | --- |
| AB | 6 | 1.071 [1.067, 1.075] | 0.995 / 0.995 / 0.988 | 1.000 / 1.000 / 0.993 | -73.3 MiB (-2.7%) |
| BC | 6 | 1.001 [0.999, 1.002] | 1.000 / 1.001 / 1.001 | 0.999 / 1.002 / 0.999 | +3.5 MiB (+0.1%) |

TTFT includes prefix work plus the final prompt-token decode and excludes setup.
Setup includes loading/authoring and preparation (A does not separately instrument
its small metadata read). Setup plus warm TTFT is only a proxy. Separate one-shot
runs in `summary.json` record setup plus first-request logits without an inference
warmup; they do not include process-loader/frontend overhead or establish a
statistical startup comparison. The robust startup gate uses paired setup time.
Setup/RSS `gate5pct` fields in
the raw statistics are generic ratio diagnostics; `qwen_gates` records the
different startup and memory policy applied here.

Representative W4 operation measurements:

| Platform | Threads | M / N / K | C/B time ratio [95% CI] | 5% gate |
| --- | ---: | --- | --- | --- |
| linux | 1 | 1 / 3072 / 1024 | 0.582 [0.578, 0.587] | pass |
| linux | 1 | 17 / 3072 / 1024 | 0.480 [0.479, 0.482] | pass |
| linux | 1 | 128 / 3072 / 1024 | 0.429 [0.427, 0.431] | pass |
| linux | 4 | 1 / 3072 / 1024 | 0.617 [0.594, 0.641] | pass |
| linux | 4 | 17 / 3072 / 1024 | 0.548 [0.541, 0.555] | pass |
| linux | 4 | 128 / 3072 / 1024 | 0.530 [0.524, 0.536] | pass |
| android | 1 | 1 / 3072 / 1024 | 0.674 [0.661, 0.687] | pass |
| android | 1 | 17 / 3072 / 1024 | 0.548 [0.529, 0.568] | pass |
| android | 1 | 128 / 3072 / 1024 | 0.514 [0.511, 0.518] | pass |
| android | 4 | 1 / 3072 / 1024 | 0.616 [0.517, 0.733] | pass |
| android | 4 | 17 / 3072 / 1024 | 0.803 [0.614, 1.051] | inconclusive |
| android | 4 | 128 / 3072 / 1024 | 0.813 [0.716, 0.923] | pass |

Across the full matrix after twelve pairs:

- linux AB: 20 pass, 0 fail, 10 inconclusive, across 30 shape/thread cells.
- linux BC: 25 pass, 2 fail, 3 inconclusive, across 30 shape/thread cells.
- android AB: 15 pass, 0 fail, 15 inconclusive, across 30 shape/thread cells.
- android BC: 29 pass, 0 fail, 1 inconclusive, across 30 shape/thread cells.

Confirmed failures under this timing protocol:

| Platform | Pair / threads | M / N / K | Baseline / candidate (microseconds) | Ratio [95% CI] |
| --- | --- | --- | --- | --- |
| linux | BC / 1 | 128 / 7 / 64 | 32.52 / 39.12 | 1.216 [1.113, 1.329] |
| linux | BC / 4 | 128 / 7 / 64 | 33.66 / 40.55 | 1.306 [1.152, 1.481] |

Do not drop the small/tail cells from the decision after seeing their results.
The larger-shape gains compare these implementations under the recorded build
settings: native adapter code uses `-O1`, Rust uses Cargo release optimization,
and allocation/dispatch placement also changes. They do not isolate a language
or ISLE speedup.

## Memory, size, and decision

The recorded retained-RSS allowance is max(64 MiB, 5% of A/B); preparation-peak
allowance is max(256 MiB, 10%). Compare setup's process high-water mark separately
from the final high-water mark after all prompts. Mapped pages count toward RSS.
Repeated Qwen prepare/drop reaches an allocator-retained RSS plateau. Native
handle counts return to baseline in the 32-cycle ownership test. The lifecycle
record retains its source program and small diagnostic records; `allocator_bytes`
is `[allocated arena bytes, free arena bytes, allocated mmap bytes]`, not RSS.

Stripped runner sizes in bytes:

| Platform | A | B | C |
| --- | ---: | ---: | ---: |
| linux | 11,202,152 | 12,689,000 | 12,742,232 |
| android | 9,557,664 | 10,743,968 | 10,775,768 |

For the public Qwen author, median C preparation spends about 88.4%
in native compilation. In-memory text emission plus parsing accounts for about
7.0%. Keep the existing text reuse for this prototype; a direct typed
builder should follow evidence that its cost matters. The current operation
uses 8,704 bytes of Rust worker scratch plus native kernel state and row-sized
activation scratch. Packed W4 weights are not fully decoded or cached as floats.

The architecture decision and performance qualification are separate:

- Keep one semantic compiler, shared by importer-compatible programs and public
  Rust authors. There is no evidence for a second lowering implementation.
- Keep backend catalogue/cost queries and native kernel invocation behind the
  small bridge. ISLE owns the operation strategy; duplicating the backend's
  catalogue or cost model would create another maintenance boundary.
- Address the failed/unresolved small-shape cells within the single Rust
  operation, then repeat focused measurements. Do not add a maintained C++
  fallback merely to hide the prototype result.
- Complete full-model ARM64 preparation and memory qualification before a
  default change. W4 microbenchmarks do not substitute for that missing evidence.

Reproduce program preparation and W4 fixture generation using
[the runtime guide](../../docs/RUNTIME_PREPARATION.md). Raw commands, temperatures,
per-process timing files, full dumps, archived binaries and control sources remain
in the local dated experiment archive; model payloads are not checked in.
