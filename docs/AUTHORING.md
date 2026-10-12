# Standalone model artifacts

Graph authors and compiler integration live in a separate private repository.
This lab publishes `.ynn` construction plans, model metadata, parameter recipes,
state fixtures, and the matching native YNNPACK/Slinky adapter. Building and
running them requires no private compiler, Python authoring package, or ISLE.
The compiler emits `.ynn` and runners load it directly. Generated C++ model
builders and JSON graph generation/loading have been retired. The handwritten
[text frontend](PLAN_TEXT.md) validates and formats source with named results,
symbolic dimensions and structured state encodings. Archived controls preserve
the migration evidence. JSON metadata, manifests and measurement records retain
their existing roles.

## Package interface

| Workload | Plans | Runner selection |
| --- | --- | --- |
| Vision | `graph.ynn` | `vision --model_dir=DIR` |
| Published E2B/E4B | `gemma4_prefill.ynn`, `gemma4_decode.ynn` | `gemma4_e2b` / `gemma4_e4b --graph_dir=DIR` |
| Attention candidates | Both Gemma phases | Same runner, `models/gemma4_VARIANT/attention/PROFILE` |
| HF E2B profiles | Both Gemma phases | `gemma4_e2b --graph_dir=models/gemma4_e2b_hf/generated/PROFILE` |

Every package includes `model.json`. Its versioned `execution` section binds
phase filenames and SHA-256 hashes to the input/output, activation, KV, and
asset-source contract. The loader checks those fields against the plan and the
selected assets. Metadata replaces generated configuration headers; a profile
change requires selecting a complete matching package. When `--graph_dir` is
omitted, each Gemma executable loads its own `models/gemma4_VARIANT/generated`
directory relative to the working directory. The executable selects the variant;
this is a per-model path default. The package must match that executable.

Large weight payloads stay external. Public asset tools materialize small
parameters from hash-checked recipes and preserve published packed codes,
scales and source precision. Vision packages list the hash and size of each
parameter blob. See [GRAPH_PLANS.md](GRAPH_PLANS.md) for the construction format
and [HF_GEMMA4.md](HF_GEMMA4.md) for safetensors profiles and backend requirements.

The checked-in Gemma packages use the recorded `target_views` preparation
policy. Shared simplification, scheduled masks and eligible reshape/view
lowering are already reflected in the plans. The attention candidates include
an identical copy of the control prefill plan and their selected decode plan.
They reuse the existing parameter payloads. Native graph compilation, packing
and Slinky preparation still happen at load time; prefill and decode prepare
packed weights and scratch independently.

## Validation and execution

The exporter validates Core semantics and lowering. Rust parses `.ynn` source
into typed commands and creates an immutable validated plan before calling the
native adapter. Loading a new model still requires validation: Rust compilation
cannot prove the contents of a subsequently loaded file. Unsupported operations,
expressions, versions, and identities fail explicitly.

Symbolic query rows, independent runtime position and capacity strides remain
Slinky expressions. `resource-state-v1` binds shared state handles to prefill
and decode, validates the committed prefix before mutation, and publishes
progress after successful execution. Reset/import invalidate old bindings;
late failures poison state. Append writes only fresh payload. `completion-v1`
preserves supported reader-before-write dependencies. Operation labels remain
available for profiling without introducing execution boundaries.

Select a candidate without recompiling a model:

```sh
./build/gemma4_e2b \
  --graph_dir=out/candidate-e2b \
  --bundle_dir=assets/gemma4_e2b/bundle \
  --parameter_dir=out/candidate-e2b/parameters \
  --cases_file=models/gemma4_e2b/fixtures/correctness.tsv \
  --output_dir=out/candidate-check --cache_capacity=2048 --num_threads=4 \
  --warmup_runs=0 --measured_runs=1 --dump_outputs
```

Keep candidate directories and results separate from retained baselines. Hold
source assets, precision, tokens, capacity, chunks, threads and affinity fixed.
Compare logits and active KV against the corresponding control; capacity-only
changes have a stronger exact-match expectation than cross-backend comparisons.

`ctest` loads the nine checked-in state plans and runs the independent native
arithmetic/state oracle at one and four threads. It covers empty history,
nonzero position, multi-head strides, partial chunks, reset, window/capacity
boundaries, stale bindings and partial failure. `plan_fixture fixture.json`
is a reusable data-driven harness for additional compiler-produced tests;
its numerical references are supplied independently. See
[RUST_RUNTIME.md](RUST_RUNTIME.md).

## Publication

Publish reviewed `.ynn` plans, recipes, metadata and standalone runtime helpers
with their original notices. Keep private authors, compiler sources, binding
patches, installation instructions and raw compiler reports outside this
repository. Learned model payloads, downloads, builds and large dumps remain
ignored. Small deterministic state-test parameters are checked in with their
plans. Publication history must also exclude the private sources.

The [October 8 builder refresh](../results/2026-10-08-builder-refresh/README.md)
is historical evidence for the retired C++ artifact path. Its configurations
and results remain unchanged.
