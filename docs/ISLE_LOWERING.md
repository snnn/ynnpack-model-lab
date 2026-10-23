# ISLE lowering rules

The semantic compiler uses `cranelift-isle` 0.136.3 to compile lowering rules into
Rust during the Cargo build. Rust/Cargo 1.97 or newer is required. The dependency
is pinned in `Cargo.lock`, has its default features disabled, and is used only on
the build host. Neither Cranelift code generation nor a Wasmtime runtime is a
runner dependency. The upstream crate carries its own Apache-2.0 WITH
LLVM-exception license.

Both importers and Rust model authors continue to supply the same `Program`.
There is no ISLE-specific public representation, command-line option, or package
format. Each supported rule family has one implementation.

## Ownership

The rule sources are under `rust/src/compiler/lower/rules`:

- `linear.isle` selects native weight-only, blockwise INT4, float, and hybrid FC
  paths and expresses their decompositions. It also defines shared softmax.
- `regions.isle` matches the convolution/history producer chain. Its result is
  a replacement descriptor, committed by the Rust graph traversal.
- `decode.isle` expresses singleton query-row reshaping around matmul.
- `attention.isle` selects grouped, small-query, sliced-head, and native SDPA
  paths; it composes masks, head views, dot products, and softmax.
- `common.isle` declares shared types and primitive construction functions.

Rust supplies tensor and quantization validation, symbolic bounds, producer/use
analysis, state legality, and primitive graph construction. Head-run enumeration
is Rust analysis; the computation for each run is an ISLE rule. Constant folding,
target views, packing, global cleanup, function sharing, and `.ynn` serialization
remain Rust passes.

Runtime operation preparation has a separate, small rule family in
`rust/operations/src/dispatch.isle`. It chooses unsigned K4, signed K4, or
portable K1 blockwise dot strategies from immutable backend facts and tile
compatibility checks. The generated selector executes during preparation;
ISLE itself is still only a build dependency. Rust owns the operation's
quantization, packing, accumulation, scratch, and task partitioning. C++ supplies
the existing backend kernel catalogue, opaque invocation state, and thread-pool
bridge. See [RUNTIME_PREPARATION.md](RUNTIME_PREPARATION.md) for this boundary,
feature-mask restrictions, and validation.

A rule must express a meaningful choice or decomposition. Do not add a rule that
merely calls a Rust implementation of the entire same lowering family. Do not
retain a second handwritten selection tree or a legacy implementation behind a
feature flag. Native SDPA is a supported target when decomposition permissions
are absent; it is not a legacy compiler fallback.

## Matching and construction

Extern extractors and `pure` constructors inspect facts. They must not emit
nodes, allocate graph names, change resources, or depend on a prior failed match.
Causal-convolution matching uses an immutable graph and checks exclusive uses,
observable intermediates, effects, geometry, and overlapping replacements before
committing a region in source order.

Construction terms call fallible Rust graph primitives through a context. The
first error is retained; subsequent constructors perform no graph writes. A
construction error terminates compilation instead of trying another alternative.
The lowering pass owns a temporary graph, and that graph is returned only after
all rules and validation succeed. This transaction is at graph/pass granularity;
cloning the whole graph for every individual operation would introduce quadratic
copying. Source programs and published packages remain unchanged on failure.

Value handles are local to a construction context. They are not public value IDs.
The context retains existing allocation names, scopes, and completion handling.
Use explicit `let` bindings to preserve construction order, including constants
and temporary values. For example, dynamic activation quantization is expressed
as ordered rule steps:

```lisp
(let ((mm Val (reduction $ReduceMinMax x))
      (az Val (fresh_zero))
      (scale Val (fresh_scale))
      (_ Flag (dynamic_parameters mm az scale))
      (codes Val (quantize_input x az scale)))
  (QuantInput.Input az scale codes))
```

Rule priorities preserve the established specialization order. ISLE checks types
and detects certain overlapping or shadowed rules. These checks do not prove
floating-point equivalence, tensor legality, or effect safety. Numerical
permissions must still be checked before selecting a decomposition.

## Adding or changing a rule

1. Express the pattern or decomposition in its existing family file. Add a typed
   fact or a reusable graph primitive to the Rust context only when needed.
2. Make eligibility queries read-only. Validate unsupported numerical contracts
   explicitly; never turn a construction error into an alternate match.
3. Add a focused regression for the selection, rejection, or state condition.
   Extend numerical fixtures when arithmetic behavior changes.
4. Build through CMake and run the relevant tests. For a new rule source file,
   register it in `rust/build.rs`; CMake also tracks all `.isle` inputs.

Cargo writes generated Rust into `OUT_DIR`. It is not checked in. Inputs use
repository-relative paths, so generated code has no checkout-specific paths.
`build.rs` and `.isle` changes invalidate both the host compiler tools and Rust
runtime libraries. Android cross-builds run the generator on the host.

After the normal dependency bootstrap, CMake uses frozen Cargo builds. Compiler
errors include the rule source filename and location.

## Regression checks

CTest's `compiler_numerics` compiles the 386 semantic fixture programs, checks
complete package hashes against `tests/compiler/package_hashes.json`, and then
executes the independent numerical references. The hash reference covers plans,
compiler reports, and generated parameters. The reference was captured from public
compiler commit `173507948379300b6ef617b2a688da72c2f3ac8d`. The existing three named backend
failure allowances remain unchanged.

For differential checking against a saved compiler:

```sh
python3 tools/compare_compilers.py \
  --baseline /path/to/saved/ynn-compile --candidate build/ynn-compile \
  --fixtures tests/compiler/fixtures --output out/compiler-comparison
```

Use repeated `--program` arguments for model programs. Comparison includes every
package file and rejects different file sets or failed compilations. Frozen
binaries and hash references are test oracles, not maintained implementations.
Do not refresh expected hashes to clear an unexplained failure. Intentional
future changes require reviewed output differences and numerical validation.

The integration preserves operation order and naming, so byte equality is the
required regression check. Independently authored models can have different
construction plans; compare each against its own baseline and use execution
comparisons to establish agreement between authors.

## Integration assessment (2026-10-22)

Validation of this baseline covered all 386 fixture packages byte-for-byte on
Rust 1.97 and 1.99, all 32 CTest checks, and an Android ARM64 runner cross-build
with NDK r28c and Rust 1.97. Model replay preserved all 44 plans from 26 programs.
Qwen3-0.6B regeneration preserved each frontend's baseline plans; all 660 logits
and state dumps matched exactly at both one and four threads, including between
frontends. The three existing AVX2 symbolic-FC backend failures remained explicitly
reported; no failure allowances were added.

ISLE improved the visibility of decomposition order and specialization rules, but
this integration increased handwritten code. Counting the affected lowering
modules, including comments, whitespace, and region tests, the baseline had 1,178
Rust lines; the integration has 1,560 Rust lines plus 337 ISLE lines. The generator
produces another 932 Rust lines (29,497 bytes), which are not maintained by hand.
The typed bridge and analysis boundary account for much of the increase. Future
rule families should justify their interface cost; this is not a code-size win.

One sequential clean-target build pair, using Rust 1.97, eight Cargo jobs, cached
crate downloads, and the release `ynn-compile` target, took 8.79 seconds before
and 8.95 seconds after integration. Debug-info-bearing binaries were 20,688,296
and 20,959,064 bytes. This single-host sample describes build overhead, not a
stable performance rate. Identical plans provide no basis for claiming faster
model execution from adopting ISLE.
