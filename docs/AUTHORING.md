# Authoring models

Rust authors and source importers produce the same public semantic `Program`.
The public Rust compiler owns decomposition, representation choices and ISLE
rules. Runners invoke that compiler during preparation; model export does not
run a target compiler. See [COMPILER.md](COMPILER.md) for the Rust authoring API.

## Package interface

A deployed model directory contains:

- `program.json` or `program.json.gz`: semantic operations, exact tensor/asset
  types, symbolic dimensions, resources, completion dependencies and phases.
- `execution.json`: phase bindings and request/state behavior. LLM contracts
  describe token, position, mask and embedding recipes; tensor contracts describe
  typed inputs and outputs without LLM conventions.
- `model.json`: descriptive metadata and a version-1 `ynn-semantic-package`
  identity binding the stored program and execution files by byte count/SHA-256.
- Immutable source parameters, or an asset recipe/provider for obtaining them.

Compression only changes storage. The runtime verifies the compressed identity,
bounds decompression, rejects trailing members/data, and deserializes the same
`Program`. Generated constants are produced and owned during preparation.
`.ynn` files and compiler reports are diagnostics, not deployed model inputs.

`ynn-llm --model_dir=DIR` serves every LLM profile. `gemma4_e2b`, `gemma4_e4b`
and `qwen3` are thin executable aliases of the same implementation. The two
Gemma aliases supply a default model directory; they contain no separate model
session. `vision --model_dir=DIR` uses a tensor session. The old `--graph_dir`
and `--graph_file` flags are rejected with regeneration instructions.

Large learned weights remain external. Asset tools preserve published packed
codes, scales and source precision. Changing arithmetic or assets requires a
complete matching package. HF/BF16 profiles still require their documented
backend patch and source manifest; see [HF_GEMMA4.md](HF_GEMMA4.md).

## Preparation and state

`runtime::prepare` validates and lowers all phases, verifies their assets and
execution interfaces, constructs native graphs and prepares each once. It
returns only when every phase succeeds. A failed later phase releases earlier
prepared graphs. The session owns stable input/output/state buffers and retains
source mappings and aligned generated constants for as long as graphs need them.

`ExecutionSpec` selects behavior through data, never a model-name switch. Gemma
packages declare a symbolic `capacity_range`; fixed-capacity Qwen packages omit
it. Capacity overrides are checked against both the declared range and lowered
input-axis bounds. Selecting smaller live prefill chunks uses
`--prefill-chunk-size`; it does not change the authored row bound.

Position is an independent runtime scalar. Attention sees live history and
capacity strides remain physical strides. Append writes only fresh payload.
Both phases share each resource owner. Fixed recurrent state uses paired
buffers. Requests are exclusive; failures after mutation poison the request.
Reset/discard follows the session contract. Invocation never recompiles or
silently grows capacity.

Compile options belong to the semantic program. `phase_options` can override
one phase, for example a prefill view ablation while preserving the decode
control. Unknown phase names fail. Quantization, numerical permissions and
architecture remain authored semantics.

## Validation and publication

`ynnpack_assets.artifacts.seal` records semantic identities;
`ynnpack_assets.artifacts.publish` validates and atomically publishes a fresh
package without a compiler subprocess. It verifies referenced source parameters
and excludes diagnostic plans/reports/runtime source. Publication scans inspect
compressed JSON as well as plain text.

Use `ynn-llm --check_package=DIR` for structural lowering/interface checks;
actual preparation additionally checks assets and the native backend. Compare
logits, KV and recurrent state against a frozen control with identical tokens,
profile, chunks, capacity and thread count. See [RUNTIME_PREPARATION.md](RUNTIME_PREPARATION.md)
and [BENCHMARKING.md](BENCHMARKING.md).

CTest uses source-independent semantic fixtures and independent arithmetic/state
oracles. Frozen `.ynn` fingerprints remain diagnostic compiler regressions;
the fixture runner executes source programs and builds its generated constants
in process. Source frontend authors and private reports stay outside this
repository. Public Rust authors, lowering, runtime helpers and semantic packages
live here. Learned weights, builds, large dumps and local captures remain ignored.
