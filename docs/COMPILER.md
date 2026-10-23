# Public Rust authoring and compiler

The compiler consumes a deferred tensor program and lowers it during runtime
preparation. It owns YNNPACK decomposition, target views, packed representations,
native function sharing and construction serialization. There is one compiler
implementation in `rust/src/compiler`, shared by every frontend and by the
optional diagnostic `ynn-compile` command. Normal authoring/export does not
invoke that command. [runtime::prepare](RUNTIME_PREPARATION.md) lowers and prepares
the program in process, then invocation reuses its native graphs.

FC, attention, and selected graph rewrites use build-time generated Rust from
[ISLE rules](ISLE_LOWERING.md). That guide describes rule ownership, extension,
and regression checks.

An importer translates source semantics into this program. It does not translate
operations into native commands. A Rust model author builds the same program
directly. Adding a model does not require an importer or any other repository.

```text
source importer ─┐
                ├─> Program + assets ─> runtime::prepare ─> prepared session
Rust author ────┘
```

`Program` is an experimental semantic contract, not the native execution plan.
It carries typed tensor values, symbolic dimensions and bindings, operation
attributes, quantization, exact immutable asset identities, guards, completion
dependencies, persistent resources, functions, and named execution phases. Model
architecture and explicit numerical permissions belong to the author. Target
decomposition and representation choices belong to the compiler. Unsupported
semantics fail explicitly; they are never replaced by maximum tensor dimensions.

All phases are compiled together. Incompatible persistent storage contracts fail
before native construction. The diagnostic report records public input/output types, packed storage,
resolved resource strides and bindings, and completion roots. Logical history
length never changes physical capacity strides. Numerical reassociation requires
the operation's explicit permission.

Build the host tools through CMake after the usual dependency bootstrap:

```sh
cmake --build build --target ynn_compile ynn_qwen3 ynn_plan
build/ynn-compile --request program.ynn --output out/new-package
build/ynn-plan check out/new-package/decode.ynn
```

`ynn-compile` writes generated constants and plans atomically into a new directory.
External assets remain references with byte counts and SHA256 identities. The
packaging frontend must provide those assets or a supported external asset
provider. `ynnpack_assets.artifacts.publish` verifies packaged parameter identities
and semantic program/execution identities before publishing a data-only package. It does not copy runtime
source. Existing destinations are rejected.

The Rust API is usable without the CLI:

```rust
use ynnpack_lab::compiler::*;
let mut graph = GraphBuilder::default();
graph.input("x", TensorType {
    shape: vec![Expr::Known(2), Expr::Known(3)],
    ..TensorType::default()
})?;
graph.operation(Op::Square, &["x"], "y", Attributes::default())?;
let mut program = ProgramBuilder::default();
program.phase("evaluate", graph.finish(&["y"]))?;
let program = program.finish();
// Serialize `program` for a package, or pass it to runtime::prepare with
// a TensorExecutionSpec binding x=[2,3] and y=[2,3].
// compile(&program) is available for diagnostics, using the same rules.
# Ok::<(), ynnpack_lab::Error>(())
```

Operations with inference implemented by the builder derive their result types.
Other operations require explicit result contracts through `GraphBuilder::value`.
Both paths are validated at compilation. `outline` captures an authored region
into a function; explicit completion-bearing functions use the full function
contract. Native template sharing is a later compiler operation, not model code.

## Qwen3

The first independent Rust model author is `rust/src/models/qwen3.rs`. Checkpoint
preparation uses the public `python/ynnpack_assets` package and public PyTorch,
TorchAO, Transformers, and safetensors dependencies. The tested optional dependency
versions are recorded in `python/pyproject.toml`; choose the Torch wheel index for
the machine's CPU/CUDA/ROCm environment. No source importer is needed.

```sh
PYTHONPATH=python python -m ynnpack_assets.qwen3 \
  --checkpoint /path/to/local/Qwen3-0.6B --output out/qwen-assets
build/ynn-qwen3 --assets out/qwen-assets/assets.json \
  --output out/qwen-rust --capacity 2048 --prefill-rows 128
build/ynn-llm --model_dir=out/qwen-rust \
  --parameter_dir=out/qwen-rust/parameters --output_dir=out/qwen-run \
  --cases_file=models/qwen3_0_6b/fixtures/matrix.tsv \
  --cache_capacity=2048 --prefill_rows=128 --num_threads=1 \
  --warmup_runs=0 --measured_runs=1 --dump_outputs
```

The current recipe is INT8 per-row weights with symmetric weight codes, dynamic
asymmetric INT8 activation quantization for linear layers, INT8 embeddings, and
FP32 KV state. It is named `mixed_int8_int8_mlp_only` for consistency with its
recorded recipe identity; the actual module map quantizes all linear layers.
The asset manifest records source file hashes, dependency versions, roles,
geometry, scales, and content hashes. Preparation is atomic. The Rust author
checks architecture and recipe constraints before writing a semantic package.

## Validation and diagnostics

`tests/compiler/fixtures` contains semantic programs and independent numerical
references, including state, completion, spatial, attention, packed quantization,
fully connected layers, and recurrence. These are data, not importer code.
Reference payloads use gzip to keep the repository small. To check diagnostic plan fingerprints and execute semantic programs
against the numerical references on one and four threads using only this checkout:

```sh
uv sync --frozen
uv run python tools/test_compiler_fixtures.py \
  --compiler build/ynn-compile --runner build/plan_fixture \
  --output out/compiler-validation --known-failures
```

Three symbolic FC cases have an intermittent SIGSEGV in the pinned backend's AVX2
dot kernel, also observed in the frozen baseline. `--known-failures` runs these
cases and reports only the recorded signal separately. A successful execution
must still pass every numerical check. Other failures fail the suite. Omit the
flag to treat every backend failure as fatal. CTest uses the explicit baseline
allowance; read its reported known-failure count as well as its exit status.

The `blockwise_fc` CTest checks group-32 INT4 arithmetic under native and
restricted CPU feature masks. The runtime uses unsigned VNNI dots when available,
signed AVX2/NEON dots with equivalent activation zero-point recentering, or a
portable dot with its own weight packing. AMX tiles are excluded because this
adapter does not provide their padded row buffers. The test also checks AMX
selection without executing unsupported instructions. CI records `lscpu` so
kernel dispatch failures can be tied to the runner's actual capabilities.

`ynn-plan compare LEFT.ynn RIGHT.ynn` expands native functions and compares
normalized construction, public contracts, constants, state, and arithmetic. It
ignores local value names, asset locations, and profiling labels. Different valid
lowerings can compare unequal. File equality and normalized equality are useful
regression checks, but numerical logit/state comparisons remain necessary.

`keep_views` is a diagnostic compiler option retaining only `fuse` or `split`
target views. `ynn-plan cpp-static` renders asset-free static benchmark commands
from the same validated native schema; it is not another lowering implementation.

The program format and Rust API are experimental. They have a version field for
fail-closed rejection, without an API or serialized-format compatibility promise.
