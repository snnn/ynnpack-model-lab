# Rust runners

Rust owns model loading, request orchestration and buffers. The canonical
executables are `vision`, `gemma4_e2b`, and `gemma4_e4b`. They load typed `.ynn`
construction plans and build reusable native YNNPACK/Slinky pipelines. There is
no generated C++ model builder or fallback. Native kernels, graph preparation,
embedding arithmetic and resource-state contracts remain behind the private
C ABI. Rust owns the shared benchmark input frontend and calls HF tokenizers
directly; only the SentencePiece engine crosses its own small FFI. This is a research runtime, not a production framework.

## Build and run

Use CMake and Rust/Cargo 1.87+. Bootstrap fetches the locked crates; CMake builds
with frozen offline Cargo. Rust is required even when tokenizers are disabled.
An existing hash-verified dependency directory can be selected with `LAB_DEPS`,
and `LAB_CARGO_HOME` selects an already populated Cargo cache.

```sh
uv run --locked python tools/bootstrap.py --directory .deps/runtime --no-tokenizers
uv run --locked cmake -S . -B build-runtime -G Ninja \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ \
  -DLAB_DEPS="$PWD/.deps/runtime" -DLAB_ENABLE_TOKENIZERS=OFF
uv run --locked cmake --build build-runtime --parallel 8
uv run --locked ctest --test-dir build-runtime --output-on-failure

build-runtime/vision \
  --model_dir=models/vision/resnet50/generated \
  --input_file=assets/vision/resnet50/validation/input_0.bin \
  --output_dir=out/resnet50 --num_threads=1 \
  --warmup_runs=1 --measured_runs=3 --dump_outputs

build-runtime/gemma4_e2b \
  --graph_dir=models/gemma4_e2b/generated \
  --bundle_dir=assets/gemma4_e2b/bundle \
  --parameter_dir=assets/gemma4_e2b/parameters \
  --cases_file=models/gemma4_e2b/fixtures/correctness.tsv \
  --output_dir=out/e2b --cache_capacity=2048 --num_threads=4 \
  --warmup_runs=0 --measured_runs=1 --dump_outputs
```

Use `gemma4_e4b` and E4B assets for E4B. Select attention and HF profiles by
`--graph_dir`; see [ATTENTION_EXPERIMENTS.md](ATTENTION_EXPERIMENTS.md) and
[HF_GEMMA4.md](HF_GEMMA4.md). Each package's `model.json` describes both phases
and their hashes, numerical profile, activation/KV types and asset source.
HF profiles require the separately patched HF backend, as before the cutover.

Gemma accepts token-ID and native tokenizer inputs, pipeline dumps, value traces,
memory reports and decode execution profiling. Timings and dump filenames retain
the earlier formats; `run.json` identifies the Rust runner and selected profile.
Tokenization and diagnostic output remain outside warm model timing. See
[TOKENIZERS.md](TOKENIZERS.md), [PROFILING.md](PROFILING.md), and
[BENCHMARKING.md](BENCHMARKING.md).

A small C++ `main` forwards to Rust so CMake retains the native link graph.
Gemma preparation/execution runs on a Rust thread with a 64 MiB stack for large
Slinky graphs. Library callers using `GemmaSession` must provide the same stack
budget themselves.

## Ownership and execution

`rust/src/ffi.rs` wraps `runtime/rust/bridge.h`. The bridge catches C++ exceptions
and returns caller-owned error records. Rust panics cannot unwind through C++
`main`. Assets outlive graphs through reference counting. Preparing consumes a
builder. A session owns stable allocations and drops graphs before their bound
storage. Internal `UnsafeCell` buffers account for retained native pointers.

Execution and reset require exclusive mutable access. Output borrows prevent
another invocation while logits are in use. Sessions are neither Send nor Sync.
Compile-fail checks assert these ownership properties, with a positive compile
control. They supplement native bounds and state checks rather than proving
arbitrary model semantics.

Rust owns chunking, logical position, KV allocations, reset, timing and dumps.
Native `ResourceState` is the authority for committed extents, reset epochs,
leases and poisoning. Both phase graphs share handles and rebind after reset or
publication. A late failure can modify storage; discard the failed session.
Resetting resource handles does not recover a poisoned graph.

Plans are interpreted once during construction. Steady-state inference invokes
the prepared native graph. Setup includes DSL parsing, validation, constant
hashing, graph construction, packing and compilation. There is no per-layer
host execution or per-operation source interpretation during inference. Constant mappings
must remain immutable throughout the session.

## Fixtures and validation

CTest covers typed plan rejection, phase/asset contracts, ownership, constant
identity and mapping lifetime, state arithmetic, canaries, stale bindings,
capacity strides and partial failures. The state oracle loads nine `.ynn` plans
and compares against independent arithmetic at one and four threads.

`plan_fixture path/to/case.fixture.json` accepts version-1 fixture data: named
plans, typed input/output buffers, optional persistent resources, and a sequence
of bindings, scalar updates, resets/imports and output files. Independent
oracles stay in the producer. Each result records shapes, counters, committed
extents, epochs, poison state, setup and invocation times. Optional append-boundary
observations verify reader completion before mutation. Failure injection tests
partial writes. Buffer canaries, unchanged prefix/suffix bytes and native pipeline
identity are checked by the harness. Stateful repetitions must be explicit steps.

Use `-DLAB_SANITIZERS=ON` in a separate build to instrument the native adapter
and tests with ASan/UBSan. That option does not instrument Rust std/crates or
backend dependency targets. Instrument dependencies too with explicit C/C++
compiler flags when needed. Run correctness separately from latency measurements.

`tools/compare_rust.py` compares canonical executables with archived C++ controls:

```sh
python3 tools/compare_rust.py vision \
  --build-dir build-runtime --control-dir "$ARCHIVED_CPP_BINARIES" \
  --output out/vision-cutover-check \
  --cpus-1 "$ONE_CPU" --cpus-4 "$FOUR_CPUS" --check-only
```

Choose CPUs from the actual host topology. Gemma comparison accepts `gemma`,
capacities and prompt lengths; candidate packages can be supplied under
`--plans-dir=DIR/MODEL` (pass `DIR`). The controls are external artifacts and
are no longer build targets. Correctness requires exact corresponding dumps;
performance observations use separate unprofiled invocations and have no
migration acceptance threshold. Preserve raw commands and binary/asset hashes.

The shared [text frontend](PLAN_TEXT.md) parses readable `.ynn` source directly
into validated commands and formats existing plans. Alternative compiler
emitters are outside the runtime; runners require neither ISLE nor Wasmtime.
Completed migration checks are indexed under [results](../results/README.md),
with outstanding device/profile coverage in [open work](worklogs/README.md).
