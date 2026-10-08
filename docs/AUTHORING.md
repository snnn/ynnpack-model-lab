# Standalone builder artifacts

Graph-authoring sources and compiler integration are maintained in a separate
private repository. This repository contains the execution artifacts needed to
build and run the lab without that compiler: model builder headers and sources, model
metadata, small parameter recipes, state fixtures, and standalone YNNPACK/Slinky
runtime helpers. Private Python authors, compiler binding patches, and compiler
reports must stay outside this repository.

## Artifact and runtime interface

Each model has `gemma4_prefill.h`, `gemma4_decode.h`, and `model.json`. The two
10-line headers declare the builders; matching `.cc` files implement them.
Each phase also has a `*_builder.h` construction-context header and an explicit
`*_sources.cmake` source manifest. `builder_sources` in each graph's metadata
lists the source files. CMake consumes these manifests without regenerating code.
HF profiles
also have `gemma4_hf_config.h` and `asset_recipe.json`. The public asset preparers
materialize immutable parameters from these hash-checked recipes while retaining
published packed weights and scales. Large weights remain external.

The checked-in models use the `target_views` preparation policy, recorded as
`optimization` in `model.json`. It includes shared literal deduplication,
equivalent-computation and dead-code elimination, scheduled attention masks,
and eligible reshape-to-fuse/split view lowering. These transformations are
already reflected in the standalone builders; runtime preparation still belongs
to YNNPACK/Slinky. This policy does not change the model's quantization profile.

Builders return a `lab_ynn::Graph` and use `runtime/ynnpack_support.h`. Keep the
builders and all matching standalone runtime headers synchronized. Symbolic
query rows, independent runtime position, and capacity-dependent strides remain
Slinky expressions; generation must not replace them with maximum shapes.

`resource-state-v1` builders bind the same `ResourceState` handles to prefill and
decode. The adapter validates the committed prefix before mutation and publishes
progress after successful execution. Reset/import invalidate previous bindings;
late execution failures poison participating state. Append writes only fresh
payload, and history views retain backing-resource identity and capacity strides.
`completion-v1` preserves supported explicit reader-before-write dependencies.
The runtime helpers implement these execution contracts without a compiler or
private IR library at runtime.

Named layer helpers call attention, SDPA, MLP, and per-layer embedding helpers.
Large blocks are divided into functions containing at most 256 emitted body
lines, keeping each operation and its ordering checks together. Source files
contain at most 2,048 lines of helper definitions plus includes and namespace
wrappers. Functions construct one shared graph per phase, preserving operation
order and shared values. They introduce no per-layer host execution calls,
backend fusion boundaries, or separate memory plans.

All retained E2B, E4B, and HF builders emit presentation-only operation labels
for execution profiling. The adapter carries these through optimized backend
lowering and times scheduled callbacks; see [PROFILING.md](PROFILING.md). Labels
do not create execution boundaries or change intermediate output visibility.

Generated construction sources use `-O2` by default and prevent helper inlining.
`-DLAB_BUILDER_OPTIMIZATION=0`, `1`, `2`, or `3` controls that compilation level
separately from the runner and backend kernels. Builder libraries are reused by
normal and diagnostic runners. Small state fixtures and retained experiment
controls may still use header-only builders. Callers using the declaration
headers must also include `runtime/ynnpack_support.h` to use the returned graph.

Source generation is separate from backend preparation. The executable still
constructs YNNPACK graphs, packs weights, and prepares Slinky pipelines. Prefill
and decode share source storage and persistent state, while backend packing and
scratch are currently prepared independently.

The [October 8 builder refresh](../results/2026-10-08-builder-refresh/README.md)
records construction and output parity for all seven profiles. Helper boundaries
count profiling statements toward the source-size limits. The synchronized
adapter also contains standalone FP32 SDPA and packed weight-only linear
capability helpers. The retained models continue to use their existing attention
and FC implementations; these helpers do not enable grouped query-head rows or
fused INT8 KV conversion/packing.

## Build an alternative artifact set

Use a fresh generated directory so retained controls remain available:

```sh
cmake -S . -B build-candidate -G Ninja -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ \
  -DLAB_DEPS="$PWD/.deps/hf" \
  -DLAB_COMPILER_GENERATED="$PWD/out/candidate-hf" \
  -DLAB_COMPILER_PROFILE=hf_static
cmake --build build-candidate --target gemma4_compiler_experiment --parallel 8
```

Use `published_e2b` or `published_e4b` for published-bundle builders. HF candidates
use the separately bootstrapped HF dependencies with their existing BF16 rounding
fix. Give each candidate its own parameter directory and retain the same source,
precision policy, fixtures, capacities, chunking, threads, and affinity.

Alternative state fixtures use `-DLAB_STATE_FIXTURES="$PWD/out/state-candidate"`.
The public C++ oracle checks empty history, window/capacity boundaries, partial
chunks, repeated/reset requests, multi-head strides/GQA, invalid writes, and
one/four threads. Fresh-write byte counts and zero history-view copies are part
of the contract.

## Validation and publication

```sh
uv run --locked python -m unittest discover -s tests -p 'test_*.py'
ctest --test-dir build --output-on-failure
```

Before accepting changed builders, compare logits and active KV with retained
controls and check parameter recipes and source identities. An unchanged
numerical policy should preserve its own control. Cross-implementation bit
identity is not a general model-quality requirement.

Publish standalone builder headers, sources, CMake manifests, recipes, metadata,
and runtime helpers with their
original notices. Keep graph authors, compiler sources, installation instructions,
binding patches, raw compiler reports, generated parameter directories, and local
agent guidance outside the public snapshot. Ignore rules cover the former private
integration paths so they cannot be accidentally added again. Git history used
for publication must also exclude those private sources.
