# Rust runtime

Rust owns semantic compilation, package loading, request orchestration and
buffers. `ynn-llm` serves all LLM profiles; `vision` uses a tensor-only session.
`gemma4_e2b`, `gemma4_e4b` and `qwen3` are thin aliases, with no independently
maintained execution logic. Every runner enters
[`runtime::prepare`](RUNTIME_PREPARATION.md) once per prepared program.

Build through CMake with Rust/Cargo 1.97+, following the [root guide](../README.md).
Bootstrap fetches locked crates and CMake uses frozen Cargo. `LAB_DEPS` and
`LAB_CARGO_HOME` can select existing verified dependency and crate directories.
ISLE generates Rust during the build; Wasmtime is not a runtime dependency.
The native backend, embedding primitives and resource-state support cross a
small C ABI. A C++ entry point preserves CMake's native link graph.

The CLI prepares large graphs on a thread with a 64-MiB stack reservation for
Slinky recursion. Library callers must provide that budget themselves.

## Ownership

`runtime::prepare` consumes an asset store and returns a `PreparedProgram` only
after all phases succeed. `Session::from_prepared` checks its execution contract
against the one validated during preparation. `TensorSession::from_prepared`
allocates the validated tensor contract's inputs and outputs.

Source mappings and generated aligned constants outlive every graph that retains
their pointers. Graphs drop before bound buffers. Preparing consumes builders;
invocation/reset require exclusive mutable access. Output borrows exclude another
invocation. Sessions are neither `Send` nor `Sync`. Compile-fail checks and native
lifetime/error-injection tests cover these properties.

Steady-state invocation reuses prepared native pipelines. It performs no source
interpretation, target lowering or compiler subprocess calls. Dynamic shape,
position, live-history and resource checks remain active. The native state
contract owns committed extents, epochs and poisoning. A late failure may have
partially modified state and must follow the session's reset/discard contract.
All source assets must remain immutable throughout a session.

## Diagnostics and tests

The compiler still uses in-memory `.ynn` emission/parsing internally. The
[plan tools](PLAN_TEXT.md) inspect and compare diagnostic output from that same
compiler. Runners do not load `.ynn` deployment files. No second lowerer or
model-specific offline fallback remains.

`plan_fixture case.fixture.json` accepts a semantic `program` path, typed buffers,
optional persistent resources and explicit invocation/reset/import steps. Its
oracles are independent expected arrays. Results include shapes, counters,
committed extents, epochs, poison status and timing. Canary checks, unchanged
prefix/suffix checks and native pipeline identity checks run around invocation.

CTest covers symbolic state strides at capacities 2048/8448, multiple KV heads,
window crossings, short chunks, stale bindings, partial failures, packed state,
BF16, tensor bindings, package hashes and ownership. Frozen compiler fingerprints
remain useful diagnostics alongside numerical execution of semantic fixtures.
`LAB_SANITIZERS=ON` instruments native adapter/tests with ASan/UBSan; it does not
instrument Rust std/crates or all backend dependency targets.

[compare_runtime.py](../tools/compare_runtime.py) accepts a JSON job list with
explicit frozen/current command arrays and execution/fixture paths. Run its
`check` mode first, then `measure --checks=CHECK_DIRECTORY` for six or more
alternating fresh-process pairs. It compares exact logits/KV/recurrent state,
vision reference tolerances, and append counters before measuring. Use separate
configs for different case sets, and select affinity from actual CPU topology.
Measurement gates are described in [RUNTIME_PREPARATION.md](RUNTIME_PREPARATION.md).
Keep raw commands, binary hashes, model/asset identities and device conditions.
