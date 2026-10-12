# YNNPACK plan text

The `.ynn` language provides compact source for the existing
[construction plan](GRAPH_PLANS.md). A handwritten Rust lexer, parser and resolver
lower it directly into the validated typed plan used by the runners. Operations bind
their results, symbolic dimensions use arithmetic expressions, and profiling and
asset identities live outside the computation where possible. No parser library,
model weights or native backend linkage is required by the authoring tool.

This is a construction language, with limited local type inference. It does not
replace a model compiler's graph transformations or prove model numerics.
Runners load `.ynn` directly. The same parser serves the offline authoring tool.

## Build and use

After the normal bootstrap and host CMake configuration:

```sh
cmake --build build --target ynn_plan --parallel 4
mkdir -p out/plan-text

build/ynn-plan check tests/rust/square.ynn
build/ynn-plan check tests/rust/kv_append.ynn
build/ynn-plan format tests/rust/square.ynn -o out/plan-text/square.ynn
build/ynn-plan inspect tests/rust/kv_append.ynn -o out/plan-text/state-report.json
build/ynn-plan expand models/gemma4_e2b/generated/gemma4_decode.ynn -o out/plan-text/decode-flat.ynn
build/ynn-plan check tests/generated/c2048_h2_w512_q8.ynn
build/ynn-plan check models/vision/resnet18/generated/graph.ynn
```

`format`, `expand` and `inspect` write to standard output when `-o` is omitted. `-` reads
source from standard input. Output files must be new; validation completes
before opening them. `check` accepts text source only. `inspect` produces a JSON
diagnostic report of functions, calls, expanded commands and constants; it is not
an executable format. Formatting removes comments and original whitespace while
retaining function definitions and calls. `expand` prints the equivalent flat
construction stream. The `ynn_plan`
target is a host utility and is omitted from Android builds.

For a candidate model package, update the corresponding phase hash in
`model.json` and keep assets and runtime contracts consistent. The formatter
does not update package metadata. Even source whitespace changes its file hash.
Use separate candidate directories to preserve recorded baselines.

Compare plan and parameter hashes before rerunning model accuracy comparisons
or performance benchmarks after an authoring/compiler change. Identical artifacts
can retain prior model evidence when the runtime behavior they use is unchanged.
Review adapter, backend, build and device changes separately; matching plan bytes
alone do not identify those parts of execution.

## Pure functions

Version `ynn 1` supports reusable typed functions. Calls expand during loading,
before preparing one native graph; they do not add per-layer host execution.

```text
ynn 1 resource_contract=1 completion_contract=1 profiling=explicit {
  fn square_pair(x: storage<fp32[4]>) -> (y: storage<fp32[4]>, z: storage<fp32[4]>) {
    Binary(operator=multiply, lhs=x, rhs=x, output=y);
    Binary(operator=add, lhs=y, rhs=x, output=z);
    return(y, z);
  }
  input x: storage<fp32[4]>;
  value y: storage<fp32[4]>;
  value z: storage<fp32[4]>;
  @scope(name="layer0") invoke square_pair(x) -> (y, z);
  output z;
}
```

Tensor parameters and named results require `storage<dtype[...]>` types. Scalar
indices use `position: index` and accept index expressions at a call. Arguments
are positional; results name already declared caller tensors. A body ends with
`return(...)` listing its named results in order. Local values and index aliases
are private to each invocation. Nested acyclic calls are supported.

Use `require` and `shape` for logical contracts. A zero in a storage template
is a backend placeholder, so matching storage types alone is not a logical
shape proof. Bodies cannot introduce inputs, runtime symbol bindings, resources,
state operations or completion edges, or capture caller values implicitly.
Weights declared with immutable assets are explicit local constants. Resource
owners/views cannot be passed as ordinary tensor parameters; dequantization or
other materialization belongs in the caller.

Definitions, including unused ones, are validated in a closed namespace.
Unknown calls, recursion, interface mismatches and invalid results reject.
Expansion is bounded by depth 64, 100,000 tensors, 500,000 statements/commands,
and the existing 128 MiB source limit. Definition validation has an aggregate
work bound. Errors identify the call and definition. Profiling regions derive
their names from `@scope`; inside an explicit caller completion/profile region,
the function contributes to that caller region instead of nesting incompatible
primitive regions.

The default Gemma graphs use separate global and sliding-window attention
functions. See [attention representation](ATTENTION.md).

## Results and types

The complete [square fixture](../tests/rust/square.ynn) is:

```text
ynn 1 resource_contract=1 completion_contract=1 profiling=explicit {
  input x: fp32[4];
  let squared = mul(x, x);
  output squared;
}
```

Bindings introduce tensors with unique names. Inputs, weights, state owners and
otherwise unproduced values use `input`, `weight`, `state` and `value`.
`output name;` marks an external output; it does not execute an operation.
Declarations are collected before emitting the construction stream, while
computation order remains source order. Forward references are useful for
binding a dimension to an input declared below it. A tensor operand still needs
a preceding producer before its computation runs.

The local inference supported for an unannotated result includes unary
operations, equal-type/equal-shape binary operations, copy, polynomial, softmax,
GELU, mask, append and view. Other cases require an explicit result type:

```text
let y: fp32[1, T, 64] = matmul(x, w, adjoint_lhs=false, adjoint_rhs=false);
let (q: storage<int8[4]>, scale: storage<fp32[1]>) = dynamic_quantization(x);
let (a: storage<fp32[2]>, b: storage<fp32[2]>) = split(x, axis=0, unstack=false);
```

These are syntax examples, not a single executable graph. Positional arguments
are tensor operands; operation attributes are named and **required, including
default values** such as `false`, `0`, or `[]`. Operands may also be named.
Named arguments can appear in any order, but positional operands precede them.
Unknown, duplicate and missing fields are errors. Operation fields and argument
kinds share the [typed wire schema](../rust/src/plan/commands.rs).

Types have two distinct meanings:

- `fp32[1, T, 64]` is a logical shape. An explicit result annotation emits a
  `ResultShape` contract. A symbolic input annotation emits `InputShape`;
  `@shape() input x: fp32[4];` also emits one for a static input.
- `storage<fp32[1, 0, 64]>` is the backend construction template. Its dimensions
  are nonnegative integers; a zero can be a backend placeholder. It does not
  assert that the runtime logical dimension is zero or insert a shape contract.

The canonical printer uses logical types where the artifact supplies a shape
contract, and storage types elsewhere. A `storage` metadata entry retains any
original template differing from the default (constant dimensions unchanged,
symbolic dimensions represented by zero). Unannotated local inference does not
add a new runtime shape contract. This preserves imported graphs without
inventing symbolic dimensions or substituting their upper bounds.

Dtypes include `fp32`, `fp16`, `bf16`, `fp64`, `int2`, `int4`, `int8`, `uint8` and
`int32`; short integer spellings `i2`, `i4`, `i8`, `u8`, `i32` are accepted.
`packed_i2` and `packed_i4` identify packed carrier declarations and remain
distinct from ordinary integer tensors. Use `native(weight)` where an operation
expects a packed carrier as a native operand. `none` is an explicit absent
optional operand.

FP32 comparisons require an explicit byte Boolean result and output shape:

```text
input x: fp32[1];
input y: fp32[4];
let predicate: uint8[4] = less(x, y, shape=[4]);
```

The six operations are `less`, `less_equal`, `greater`, `greater_equal`, `equal`
and `not_equal`. They broadcast trailing axes, accepting an input extent of one
or the corresponding output extent, including empty results. Both inputs must
be `fp32`; each result element is exactly zero or one. NaNs compare unequal and
all ordered comparisons with NaN are false; positive and negative zero compare
equal. A scheduled native callback implements these operations. Use the matching
adapter and runner; older runners reject the new comparison commands.

`symbolic_broadcast(x, shape=[...])` explicitly selects the destination shape.
Use it when a runtime singleton must expand to an independently symbolic extent
or an empty result; a native binary's implicit shape inference does not implement
every such case. Logical result annotations and request guards must remain
consistent with the selected destination.

## Symbolic dimensions and index expressions

Symbol sources, bounds and arithmetic follow the Core IR `DimExpr` vocabulary:

```text
dim T = axis(new_k, 2) in 1..=128;
dim p = parameter("position") in 0..=32768;
dim C = instance("capacity") in 1..=32768;

let end = checked(p + T);
let begin: index = max(0, p - 511);
require end <= C;
```

`axis` reads an input's logical dimension. `parameter` is an independently
updated invocation scalar, so advancing position does not require changing a
tensor shape. `instance` binds an instance parameter such as storage capacity.
The inclusive bounds participate in validation. Symbols must precede wire
commands that use them; source index aliases may refer to declared symbols
before those symbol statements because aliases emit no computation.

| Dimension concept | Source form |
| --- | --- |
| Known integer | `128`, `-1` |
| Symbol | `T`, `p`, `C` |
| Affine expression | `2 * T + p - 1` |
| Addition / multiplication | `a + b`, `a * b`, `add(a, b, c)`, `mul(a, b, c)` |
| Floor division | `a // b`, `floor_div(a, b)` |
| Ceiling division | `ceil_div(a, b)` |
| Minimum / maximum | `min(a, b)`, `max(a, b)` |
| Unresolved dimension | `?` is diagnosed and must be resolved before loading |

Unary `+`/`-` bind first, then `*`/`//`, then `+`/`-`; parentheses override
precedence. Division rounds down or up as named, including for negative
numerators. `/` is rejected. The current execution contract requires divisors
whose lower bound is strictly positive. Arithmetic uses signed 64-bit integers;
there are no implicit float-to-index conversions.

There is no separate affine wire node: affine syntax expands to addition and
multiplication. Imported expression grouping, term order and constants survive
exactly, without reassociation or constant folding. N-ary wire nodes print as
calls when binary infix syntax would change their tree. Repeated trees can be
factored into `let name: index = ...;` aliases. Such aliases are validated even
when unused. Cyclic or forward alias references fail explicitly.

`checked(expr)` is an index binding form. It emits a native checked guard, not
wrapping arithmetic or an unchecked assumption. Interval analysis rejects
unprotected expressions that may overflow; checked guards evaluate protected
arithmetic before shapes, execution or state mutation. Always-overflowing
expressions and invalid divisors are still rejected when loading.

## State and requirements

The [handwritten KV example](../tests/rust/kv_append.ynn) combines dimensions,
state metadata and the readable append/view sequence:

```text
@resource(name="K", axis=2, encoding=encoding(dtype=fp32, axis=none, scales=[], zero_points=[]))
state K: fp32[1, 2, C, 8];
input new_k: fp32[1, 2, T, 8];

require committed(K) == p;
let end = checked(p + T);
require end <= C;

let K1 = append(K, new_k, axis=2, position=p, rows=T);
let history = view(K1, axis=2, begin=0, end=end);
```

Declare the dimension sources and bounds as above. A committed-extent equality
establishes the resource's entry contract; it is not a general tensor expression
or a post-mutation read. Resource name, axis and encoding must be supplied in an
annotation or the metadata block. Encoding fields are structured and required:
`dtype` is the storage type, `axis=none, scales=[], zero_points=[]` denotes
unquantized storage; quantized storage supplies an integer axis, positive finite
scales and matching integer zero points. For example:
`encoding(dtype=int8, axis=0, scales=[0.03125], zero_points=[0])`.
Scale coefficients retain exact binary64 bits. The loader checks the encoding
against the owner's storage type and rank before native graph creation.

Ordinary `require` supports `==`, `<=` and `>=` (the latter reverses into `<=`).
Use separate statements for multiple requirements. Imported guards retain their
message and mode through `@guard(message="...", mode="ordinary")`, including
`bounds` and `checked` modes.

The native runtime still checks position, committed extent, physical strides,
reset epochs and write bounds on invocation. Append copies new rows only; view
retains the owner's physical capacity strides. A late failure can leave partial
state mutation. Discard the failed session; resetting resource handles does not
recover a poisoned graph.

## Profiling and completion dependencies

`profiling=auto` emits one profile operation for each tensor-producing `let`.
The default scope is `Compute`; kinds derive from the operation and input names
from runtime tensor names. Thus ordinary computation contains no profiling
begin/end calls. Overrides use `@profile(...)` or metadata:

```text
@profile(name="attention", kind="experiment.matmul")
let scores: fp32[1, 8, T, end] = matmul(q, k, adjoint_lhs=false, adjoint_rhs=true);
```

Metadata can override `name`, `kind`, `inputs`, `outputs`, and `input_names`.
`profile result_name = none;` suppresses that result's automatic profile.
`profiling=explicit` emits profiles only when requested. The header defaults to
explicit mode when its profiling field is absent.

Completion dependencies are real construction ordering, preserved with blocks:

```text
operation(waits=[], defines=["cache_written"], outputs=[K1]) {
  let K1 = append(K, new_k, axis=2, position=p, rows=T);
}
operation(waits=["cache_written"], defines=["history_ready"], outputs=[history]) {
  let history = view(K1, axis=2, begin=0, end=end);
}
```

For an imported multi-operation profile, the printer retains a
`profile(name=..., kind=..., inputs=[...], outputs=[...], input_names=[...])`
block. Automatic per-operation profiles are suppressed inside `profile` and
`operation` groups. Blocks preserve ordering and do not introduce separate name
scopes. Missing completion dependencies, unsupported nesting and incomplete
outputs are rejected by the shared validator.

## Metadata, constants and literals

Computation refers to an asset by name; its payload identity stays in metadata:

```text
weight w: storage<fp32[4]> = asset(weights);
metadata {
  asset weights = asset(path="@parameters/weight.bin", bytes=16,
                        sha256="aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
}
```

The illustrative digest must be replaced with the actual hash. Assembly checks
asset paths, digest syntax and declared storage size; native loading verifies
the mapped bytes. The authoring tool does not read or change packed weights.
An inline `asset(path=..., bytes=..., sha256=...)` is also accepted.

The printer's metadata footer can contain:

| Entry | Purpose |
| --- | --- |
| `order [x, w, y];` | Preserve dense wire tensor identities despite moving declarations to result bindings |
| `name y = "original/runtime/name";` | Preserve names when a readable source alias differs |
| `symbol T = 7;` | Preserve sparse numeric symbol identities |
| `storage y = [1, 0, 64];` | Preserve a storage template differing from the logical type |
| `declaration w = ConstantOutput;` | Preserve special constant-output declaration kinds |
| `resource K = resource(name=..., axis=..., encoding=...);` | Resource metadata separate from the state computation |
| `profile y = profile(input_names=["original/name"]);` | Preserve profile details differing from generated defaults |
| `asset weights = asset(...);` | Asset path, byte count and digest |

Unknown entries, invalid targets and duplicates are errors. Handwritten programs
do not need identity metadata: source binding order assigns tensor IDs, and
symbol IDs are assigned automatically. The printer derives deterministic unique
ASCII aliases and preserves original names as metadata.

Names match `[A-Za-z_][A-Za-z0-9_]*`; `none`, `true` and `false` are reserved
for literals. Quoted strings use JSON escaping and can
contain Unicode. `#` starts a line comment. Non-nested `/* ... */` comments are
also accepted. **`//` always means integer floor division.** Statements end in
`;`; empty lists and trailing argument/list commas are accepted.

Finite float attributes print as decimals when parsing that decimal reproduces
the exact original binary64 bit string. Otherwise they print as
`bits("3FF0000000000000")`, which also preserves hexadecimal spelling. Signed
zero and subnormals round-trip exactly. Nonfinite coefficients are rejected.

## Validation and implementation

The parser builds a bounded syntax tree with byte spans. Lowering resolves
names, result types, attributes and metadata, then invokes construction-plan validation
before native graph creation. Diagnostics report a line, column and source excerpt;
semantic command errors point to the corresponding source statement.

Limits include 128 MiB of source, 256-byte identifiers, 1,024 list/call entries,
100,000 tensors, 500,000 statements/commands, four million syntax values, bounded
syntax/block nesting, and 4,096 nodes/64 levels per expanded index expression.
Aliases cannot bypass expression budgets by exponential expansion. The printer
parses its own output and refuses any conversion that would change the
construction stream.

The [frontend](../rust/src/plan_text.rs) separates
[lexing](../rust/src/plan_text/lexer.rs),
[parsing](../rust/src/plan_text/parser.rs),
[lowering](../rust/src/plan_text/compile.rs),
[argument resolution](../rust/src/plan_text/resolve.rs),
[surface operation naming](../rust/src/plan_text/schema.rs), and
[printing](../rust/src/plan_text/printer.rs). No new runtime or parser dependency
is introduced.

```sh
cmake --build build --target ynn_plan rust_native_test --parallel 4
ctest --test-dir build -R '^(plan_text|rust_types|rust_gemma_types|rust_borrow_contracts)$' \
  --output-on-failure
```

The integration test formats all checked-in plans, compares
validated commands exactly (commands, IDs, attributes, expression trees, assets and
state/completion contracts), and checks canonical formatting stability. It then
runs the directly loaded square and nine state plans against the independent native
arithmetic/state oracle at one and four threads. Unit tests cover handwritten
syntax, symbolic dimensions, checked arithmetic, diagnostics, metadata,
multi-result operations, profile/completion groups, packed operands, float
precision, malformed input and resource limits.
