# Shared semantic runtime baseline: 2026-10-22

The deployment boundary is a semantic `Program`, an execution contract, and
immutable assets. The runner prepares that program through the public Rust/ISLE
compiler and reuses the prepared graphs for subsequent requests. Gemma, Qwen,
and vision use the same preparation and asset ownership implementation.

This record qualifies the semantic-package implementation against the frozen
offline runners at `d3e66dc4a103c4a8302f810e132a15a98ff31301`. It does not compare
two kernel implementations: both sides already use the same Rust blockwise
operation. The [earlier prototype](../runtime_preparation_20261022/README.md)
records the native-to-Rust operation comparison and its limitations.

## Implementation and scope

- Version-2 `model.json` seals the compact semantic `program.ynn` and
  `execution.json`; the DSL binds shared exact numeric chunks by size/SHA-256.
  Source, chunk and numeric expansion limits are checked before native construction.
- A single preparation path validates all phase interfaces and assets before
  native graph construction. Generated constants have aligned owned storage;
  source mappings and constants outlive the graphs that use them. A later-phase
  failure releases earlier graphs without returning a partial prepared object.
- `Session` owns LLM resources, embeddings, masks, token/position recipes, and
  fixed recurrent state. `TensorSession` provides owned stateless tensor bindings
  without token or vocabulary assumptions. Invocation requires exclusive access;
  failed invocation poisons the session.
- Gemma's symbolic capacity can be selected within its declared range. Qwen's
  fixed-capacity programs reject an incompatible override before preparation.
  Capacity remains storage: attention reads the live prefix and appends only
  newly produced rows.
- Deployment reads `ynn_program 1` semantic source, not precompiled `ynn 1` plans. The same compiler still
  emits and parses text internally, and the diagnostic CLI and frozen compiler
  fingerprints remain available. There is no second lowering implementation,
  compiler subprocess, persistent preparation cache, or temporary plan file.

The package inventory is 26 profiles: four published E2B profiles, four E4B
profiles, five HF E2B profiles, five Qwen profiles, and eight vision models.
[packages.json](packages.json) records every semantic artifact identity and the
corresponding control plan identity. Source weights remain external. Quantization
metadata is part of the semantic representation. The DSL migration reduces model
source from 1,008,887,738 raw JSON bytes (275,242,308 gzip bytes) to 35,967,226
text bytes plus 131,786,240 numeric bytes, without compression. The largest text
file is 4,052,675 bytes and numeric files are at most 8,388,608 bytes. There are
56,010,240 bytes of distinct numeric payloads before Git compression. Execution
contracts are unchanged. Native control plans totaled 67,917,587 bytes; they
represent a different compiler stage and exclude generated constant payloads.

[dsl-migration.json](dsl-migration.json) records all 423 lossless typed-program
round trips: 26 model packages, 386 compiler fixtures, nine state fixtures and
two session fixtures. [dsl-validation.json](dsl-validation.json) records the
final DSL checks, including public Rust author parity, all 11 timing-configuration
correctness checks, 14 Android records and both successful Linux CI runs.
Complete compiler output files for all 26 old/new model
programs are byte-identical. The DSL migration does not change lowering rules.
The current host suite passes 36/36 targets, including exact-bit parser tests,
chunk integrity checks, all frozen compiler fingerprints and numerical fixtures.

## Correctness protocol

[correctness.json](correctness.json) records the earlier semantic runtime
checks, performed before the DSL storage change. The lossless source and full
compiler-output comparisons above connect that evidence to the new format.
Fresh final-binary model checks and paired measurements are recorded separately:

| Check | Capture | Result |
| --- | --- | --- |
| 26 host packages × one/four threads | Before DSL | 52/52 exact comparisons passed; 2,232 decoded steps |
| E2B/E4B capacity 8,448 × one/four threads | Before DSL | 4/4 matched the frozen control |
| Capacity 2,048 versus 8,448 | Before DSL | 3,840 live logit/KV arrays were identical |
| Compiler worklist change | Before DSL | Complete outputs for all 26 packages were byte-identical |
| Pixel 8 and Pixel 11 | Before DSL | All 12 native/session/arithmetic/vision records passed |
| Source and compiler identity | Final DSL | 423 exact typed-program round trips; all 26 compiler packages byte-identical |
| Public Rust Qwen3-0.6B author, four threads | Final DSL | 658 exact arrays across 153 decode steps; full prompt/reset matrix |
| Host CTest | Final DSL | 36/36 targets passed; 386 compiler fixtures, 2,196 passed numerical requests |
| Timing configurations | Final DSL | All 11 correctness prechecks passed |
| Pixel 8 and Pixel 11 | Final DSL | All 14 native/session/CLI/arithmetic/vision records passed |

The earlier host comparisons performed 43,392 exact file comparisons, including resolved
token files. The three unchanged expected backend failures are listed below.

Host model checks use the same assets, token IDs, shapes, capacity, and numerical
profile on each side. Dumping and profiling are excluded from latency runs.
Each profile is checked at one and four threads.

LLM cases cover prompts 1, 128, 129, 130, 511, 512, 513, and 1024, followed by a
repeated/reset request. Gemma uses two forced continuation tokens per case;
Qwen uses sixteen. Comparisons require finite, byte-identical full logits,
matching argmax/token sequences, identical append traffic, and zero history-view
copy callbacks. Gemma also compares every active KV owner/head after every decode
step. The frozen Qwen runner exposes final KV and recurrent-state dumps, so its
state comparison is at the end of each case rather than every intermediate step.

Vision checks compare three complete outputs per model against the frozen
runner exactly and against the retained PyTorch references with `atol=1e-4`,
`rtol=1e-3`. These checks validate this execution change; they are not a model
quality evaluation.

The additional capacity matrix compares E2B/E4B at 8,448 against the control,
then compares matching live outputs directly against capacity 2,048. It covers
both thread counts. The public Rust Qwen3 author is compared against the
serialized semantic Qwen3-0.6B package using the full prompt/reset matrix.

The compiler cleanup now uses a worklist for quantization dependencies instead
of repeatedly scanning all live values. Complete compiler output directories
for all 26 programs remain byte-identical to the pre-cleanup compiler, including
reports and generated constants.

Full-model verification exposed two issues that are fixed in this baseline:

- Verifying large embedding mappings made every page resident; HF embedding
  verification also created an unused signed-recode cache. Packed embedding
  hashes now use bounded streaming reads, and HF embedding records verify the
  original checkpoint representation. Compiler constants retain their required
  signed representation.
- Equal maximum logits selected different token IDs in the older model-specific
  and general runners. The shared runner now selects the lowest token ID,
  including signed-zero ties. All 837 logit/KV arrays in the failing HF case were
  already identical; this was a selection-policy difference, not arithmetic drift.

The full-model campaign retains the identity of the candidate used for each job.
Some jobs completed before the final worklist, tie-selection, and diagnostic-dump
changes. Compiler byte-parity covers all 26 programs after the worklist change;
the tie case is rerun with the corrected runner. The lowest-token policy also
matches all 1,530 retained Qwen full-matrix logits. The final binaries run CTest,
the Android checks, and the separate correctness checks for the 11-job timing
configuration. [provenance.json](provenance.json) distinguishes the intermediate
and final binaries rather than attributing every capture to one executable.

## Performance protocol

[comparison.json](comparison.json) is the portable 11-job configuration. It covers
published E2B, HF BF16 E2B, Qwen3-0.6B, Qwen3.5-4B INT4 MLP, and ResNet18 at one
and four threads, plus published E4B at four threads. Gemma and Qwen3.5 fixtures
use prompts 17/128/1024; Qwen3-0.6B's retained performance fixture uses 129/1025.
Continuation counts are E2B 32, HF 8, E4B 16, and Qwen 16.

Each comparison uses six alternating fresh-process pairs, one warmup and three
measured requests per case. Processes run sequentially, with no concurrent
model checks or builds. Filesystem and HF on-disk caches are warm. The host is an
i9-12900K; one-thread jobs use logical CPU 8 and four-thread jobs use physical
P cores 0/2/4/6. The existing `intel_pstate` powersave policy is unchanged;
frequency and thermal observations accompany the local raw records.

Each process contributes the median prefix/TTFT or vision invocation time.
Decode is the mean subsequent-token latency across the three requests.
The tool bootstraps the paired process log-ratios with a fixed seed and 10,000
resamples. The upper one-sided 95% bound must be at most 1.05 for warm latency
and 1.25 for setup. Retained RSS may increase by at most max(64 MiB, 5%) in
each pair; process peak RSS may increase by max(256 MiB, 10%). These are local
experiment gates, not shared-CI performance assertions.

Setup includes semantic loading and preparation. Warm TTFT is prefix execution
plus the final prompt-token decode and excludes setup. Retained RSS is sampled
after preparation and session allocation; peak RSS is the process high-water
mark after the full case sequence. Mapped resident pages count toward both.

## Reproduction

Build the candidate and a separate checkout of the frozen control with CMake,
the same pinned dependencies and the same options. The main host build enables
tokenizers and the attention benchmark. HF uses a separate dependency tree with
the recorded BF16-rounding patch and tokenizers disabled on both sides. Android
uses NDK r28c, ARM64, static libc++, and the Rust 1.97 minimum toolchain. The host
uses Rust 1.99 and Clang 22.1.8. SME/SME2 are disabled.

Prepare assets using the model guides. Set absolute `LAB` and `CONTROL` checkout
paths and the `HF_MODEL_DIR`, `HF_ASSET_MANIFEST`, and `HF_CACHE_DIR` paths used by
the HF guide. Vision controls must read their original metadata from `CONTROL`;
link their `models/vision/*/generated/parameters` directories to the same verified
payload directories used by the candidate. Adjust the explicit affinity masks for a different host rather
than assuming the same CPU topology.

```sh
ctest --test-dir build --output-on-failure
python tools/check_model_packages.py --runner build/ynn-llm
python tools/compare_runtime.py \
  --config results/semantic_runtime_20261022/correctness-comparison.json \
  --output out/semantic-full-checks --mode check
python tools/compare_runtime.py \
  --config results/semantic_runtime_20261022/capacity-comparison.json \
  --output out/semantic-capacity-checks --mode check
python tools/compare_runtime.py \
  --config results/semantic_runtime_20261022/comparison.json \
  --output out/semantic-checks --mode check
python tools/compare_runtime.py \
  --config results/semantic_runtime_20261022/comparison.json \
  --output out/semantic-measurements --mode measure --checks out/semantic-checks
```

Checks bind the executable, package metadata, contract, and input identities to
the measured configuration. The runtime separately verifies immutable asset
payloads. Changed identities require a new correctness run. Output directories
must be fresh; full state dumps can be large.

## Qualification limits

The three pre-existing named backend fixture failures are unchanged:
`numerical_affine_symbolic_prefix_before`,
`numerical_affine_symbolic_prefix_shared`, and
`numerical_affine_symbolic_prefix_native`, at one thread with signal 11. They
remain explicit expected failures; no allowance is added for this change.

Pixel 8 and Pixel 11 run the native ownership/state tests, LLM session tests,
quantized-FC and blockwise-FC tests, plus ResNet18 at one/four threads. This is
ARM64 runtime and vision coverage. The frozen full-Qwen control exhausts device
memory during native compilation, so the phones do not provide full-LLM
qualification or a full-LLM latency comparison.

The earlier small W4 `M=128, N=7, K=64` regression remains a recorded operation
limitation. Both sides of this semantic-package comparison already use that same
Rust operation. This work does not claim to resolve that regression or the
earlier noisy phone performance cells.

Raw commands, full output dumps, environmental observations, build commands,
dependency source fingerprints, and binary identities are retained in the local
dated archive. The public baseline retains small numerical and measurement
records without weight payloads, device identifiers, or host paths.
