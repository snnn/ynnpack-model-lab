# Semantic program text

`program.ynn` is the deployment source for the public Rust `Program`. The same
Rust parser/writer serves imported models, Rust authors, inspection tools and
runtime preparation. It does not select kernels or lower operations. The header
`ynn_program 1` distinguishes this source language from the internal native-plan
language, whose header is `ynn 1`.

A small complete example:

```text
ynn_program 1 {
  phase "model" {
    value "x": f32[4];
    value "y": f32[4];
    inputs ("x");
    outputs ("y");
    node mul ("x", "x") -> ("y");
  }
}
```

Values declare semantic types, symbolic shapes and optional quantization or
resource metadata. `const` additionally declares a constant. Nodes name semantic
operations and their input/output values. Nondefault attributes follow `attrs`;
`waits`, `completes`, and `scope` retain completion and profiling information.
Nested `fn` declarations, symbols, guards, resources and graph completions retain
the corresponding typed `Program` fields. Names may be quoted strings; `#` and
`/* ... */` introduce comments.

Shapes use integer dimensions, `s0` symbol references, and prefix expressions
such as `mul(s0, 8)` and `add(s1, 1)`. Structured attributes use records and lists;
expression-valued record fields use constructors such as `known(1)`, `symbol(0)`
and `add([symbol(0), known(1)])`. Omitted attributes and compiler options take
the version-1 public defaults. Changing their meaning requires a source-format
version change. `options {...};` applies to all phases;
`phase_options "prefill" {...};` supplies a complete option set for one phase.
Unknown fields, duplicate declarations, missing references and trailing input
fail explicitly.

## Numeric metadata

Large source arrays, particularly quantization scales, use shared numeric tables.
These were previously expanded repeatedly inside JSON. Tables are source data,
not packed runtime weights or compiled kernels. Learned weight payloads retain
their existing external asset identities and recipes.

For example, after a `blob "<64 lowercase SHA-256 digits>" 8192;` declaration,
these declarations describe 1,024 exact binary64 scale values:

```text
array a0 = r64(0, 1024);
quant q0 {axis: 0, scales: @a0, zeros: repeat(0, 1024)};
```

`blob` declarations name `program-data/<sha256>.bin` files and give their byte
counts. Their order defines one logical byte pool. `array` gives a type, byte
offset and element count in that pool; spans may cross chunk boundaries. The
writer emits chunks of at most 8 MiB, deduplicates identical arrays, and interns
quantization descriptions across phases. There is no compression or float
precision conversion. Table words are little-endian 64-bit integers (`i64` or
`u64`) or exact IEEE binary64 bit patterns (`r64`).

Short arrays stay inline. Repeated numeric scalars use `repeat(value, count)`.
`real(0.125)` uses correctly rounded binary64 parsing; the writer prints a
round-tripping decimal. `real(-0.0)` retains its sign. `bits("7ff8000000000042")`
retains a nonfinite value's exact bits, including NaN payloads. These forms map
to the existing `Real` type; the compiler's numerical validation still applies.

The migrated profiles currently track these numeric files in Git, separate from
externally acquired weights, so lowering/interface checks need no downloads.
This is a provisional distribution choice. Across 26 profiles the numeric files
occupy 131,786,240 bytes, with 56,010,240 bytes of distinct payloads before Git
compression. Chunking bounds individual files; it does not bound repository
history as checkpoints and quantization variants accumulate. External asset
distribution is a follow-up. The existing hash references permit fetching these
payloads alongside weights without changing semantic lowering. Small synthetic
fixtures should remain self-contained.

## Tools and package integrity

```sh
build/ynn-program inspect models/qwen3_0_6b/generated/program.ynn
build/ynn-program to-json models/qwen3_0_6b/generated/program.ynn > out/projection.json
build/ynn-program from-json out/projection.json out/program.ynn
build/ynn-compile --request out/program.ynn --output out/diagnostic-plans
```

`from-json` prints the canonical typed input SHA-256. `inspect` returns the same
semantic identity, phase names, source assets and verified numeric-file list.
That identity includes every typed field, including defaults and exact `Real`
bits. `to-json` is a diagnostic/frontend bridge, not a runtime deployment format.
The formatter refuses to overwrite its source output. Use a fresh output
directory when publishing a package.

Rust authors call `program_text::write(path, &program)` directly. Python importers
use `ynnpack_assets.artifacts.write_program(program, path)` with
`YNNPACK_PROGRAM_TOOL` pointing to `ynn-program`; they do not implement the DSL
again. The subprocess only formats source, never performs target lowering.

Version-2 `ynn-semantic-package` metadata binds `program.ynn` and `execution.json`
by size and SHA-256. The DSL transitively binds its numeric chunks. The runtime
verifies those bytes before constructing native graphs. The reader limits source
to 32 MiB, each chunk to 8 MiB, the logical numeric pool to 128 MiB, nesting to 64,
and expanded numeric references to 16 million scalars. Invalid offsets, excessive
expansion, corrupt or missing chunks fail without fallback to JSON or old native
plans. Small execution and descriptive metadata remain JSON.
