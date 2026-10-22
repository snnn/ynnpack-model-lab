# YNNPACK construction plans

A construction plan is a standalone sequence of typed calls to this lab's
native graph adapter. The Rust runner validates and executes that sequence once
to construct a YNNPACK graph, then prepares and reuses the native pipeline.
The executable artifact is the [`.ynn` language](PLAN_TEXT.md), with result
bindings, symbolic shapes, explicit attributes and profiling metadata. Rust
parses it directly into the typed construction model and validates it before
native construction. No graph JSON serialization or decoding occurs. The format
is experimental and tied to the pinned adapter; unsupported versions fail.

Vision packages contain `graph.ynn` alongside `model.json` and their
hash-addressed parameters. Gemma packages contain `gemma4_prefill.ynn` and
`gemma4_decode.ynn`, using the existing bundle and parameter recipes. The
plans preserve packed weight codes, quantization scales, symbolic expressions,
resource declarations, and operation completion dependencies. They contain no
private compiler code or installation dependency.

## Format

The header declares language version 1 and resource/completion contract versions.
For example:

```text
ynn 1 resource_contract=1 completion_contract=1 profiling=explicit {
  input x: fp32[4];
  let squared = mul(x, x);
  output squared;
}
```

[The square fixture](../tests/rust/square.ynn) is a complete artifact. The
[command table](../rust/src/plan/commands.rs) defines supported operations and
argument types. Unknown operations, fields, enumeration values, argument types
and expressions are errors. Source names resolve to dense tensor IDs; metadata
preserves externally meaningful IDs and names across formatting.

Floating attributes accept finite decimal literals or exact binary64
`bits("0123456789abcdef")` values. Index expressions support constants, symbols,
`add`, `mul`, `min`, `max`, `floor_div` and `ceil_div` without losing tree grouping.
Arithmetic uses signed indices and positive
divisors, with conservative interval checks for overflow. Expressions that cannot be
proved safe statically require an explicit checked-arithmetic guard evaluated
before native shape evaluation or state mutation. Symbols bind to input
axes, independent runtime scalars, or instance parameters with explicit bounds.
An unknown expression is never replaced by a maximum dimension.

Constants identify a relative file path, exact byte count, and SHA-256 digest.
`@parameters/` selects the parameter directory; other paths select the bundle.
Absolute paths and parent traversal are rejected. The loader hashes the mapped
bytes before constructing a native graph and rejects conflicting identities for
the same path. Asset files must remain immutable while a session is alive, as
with any retained native mapping. Model payloads remain external to this repository.

Resource encodings use structured `encoding(dtype=..., axis=..., scales=[...],
zero_points=[...])` fields. Scale bits survive parsing and printing exactly;
invalid storage types, axes, scales and zero points fail validation. The native
adapter compares canonical encoding identities when graphs share state.

`model.json`, asset manifests, fixture controls and diagnostic reports remain
JSON. `ynn-plan inspect` writes a read-only report for tooling; runners reject
that report as graph input.

## Checks and limits

Rust's type system checks the loader and session code when they are compiled.
The contents of a later-loaded graph require checks at load time. The loader
checks format/contracts, typed attributes, declarations, symbol binding,
producer order, supported rank/axis constraints, constant sizes and hashes,
resource declarations, and completion dependencies before native construction.
The exporter also validates its model and emits typed commands. These checks
are complementary to the native adapter's operator and shape validation; they
do not constitute a proof of arbitrary model semantics or numerical quality.

Dynamic position, history extent, capacity, physical strides, reset epochs,
and write bounds remain native checks on every invocation. Rust owns buffers
and request orchestration; native `ResourceState` remains the authority for
committed extents and failure poisoning. A validation rejection before execution
preserves state and permits corrected bindings on the same prepared graph. The
fixture runner checks expected validation errors with `expect_unchanged` and
verified buffer/resource snapshots. An injected backend failure can leave
modified storage; the failed graph must be discarded. Failure fixtures can reset
the shared owner and bind another still-usable prepared phase, checking failed
append counters, committed extents and poison before recovery. Reset alone does
not recover the failed graph.

`CompletionOutput` roots a public completion through a scheduled adapter sink.
Copies with completion waits use scheduled callbacks; alias-only metadata waits
remain unsupported. Serial explicit rank-one INT2/INT4 resources support
append/view with bit offsets, partial-byte preservation and fresh-lane checks.
The fixture runner checks physical edge-byte canaries and logical committed
extents. Higher-rank, target-selected and concurrent packed writes are not
supported by this extension.

Version 1 covers the eight vision classifiers, thirteen Gemma packages, packed
routing, direct SDPA, weight-only linear and dynamically quantized attention.
Qwen3.5 also uses `GatedDeltaRule` for compact recurrence and
`CausalDepthwiseConv` for direct convolution with replacement history. These are
scheduled native graph operations with explicit state inputs and outputs;
the host does not execute a per-layer or per-token callback loop. See
[Qwen3.5](QWEN35.md) for their numerical and CPU coverage.
They are required lab runtime extensions, not upstream YNNPACK primitives or
composites with decomposition bodies. Reusable functions construct the operations
written in their bodies. Mathematical reference implementations belong in tests;
the executable plan does not carry an unused fallback. An unsupported operation
fails construction.
Dedicated numerical and state fixtures exercise those capabilities. Additional
operations require explicit lowering, typed loader support and independent tests.

## Validation

The exporter emits `.ynn` plans only. The public comparison harness checks exact
outputs and state counters against archived C++ controls. Independent weights-free
state tests load `.ynn` plans and cover bounds, reset, multiple KV heads, window
crossings, real partial chunks, stale bindings and failure after partial writes.

Alternative compiler emitters must satisfy the same construction contract;
runners do not link compiler implementations. Runtime usage and candidate
comparison commands are in [RUST_RUNTIME.md](RUST_RUNTIME.md). Dated migration
evidence is indexed in [results](../results/README.md), separately from the
[remaining coverage gaps](worklogs/VALIDATION_GAPS.md).
