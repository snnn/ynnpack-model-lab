# General LLM runner

`ynn-llm` loads semantic model packages and prepares their prefill/decode graphs
in process. `execution.json` describes input recipes, resources, fixed recurrent
state and embeddings. Model names are descriptive; they do not select runtime
implementations. Published Gemma, HF/BF16, Qwen3 and Qwen3.5 profiles use this
same session. The compatibility executable names are thin aliases.

```sh
cmake --build build --target ynn-llm --parallel 8
build/ynn-llm --model_dir=models/qwen3_0_6b/generated \
  --cases_file=models/qwen3_0_6b/fixtures/matrix.tsv \
  --output_dir=out/qwen3 --num_threads=4
```

Bundle and parameter paths default to the selected model directory and its
`parameters` subdirectory. Published Gemma uses its extracted `--bundle_dir`
and `--parameter_dir`. HF profiles additionally select their source directory,
verified manifest and derived cache, as described in [HF_GEMMA4.md](HF_GEMMA4.md).
Model weights must be prepared first.

Case lines contain a name, comma-separated prompt IDs and comma-separated
continuation IDs, separated by tabs. Tokenizers, teacher forcing, repetition,
scoring and timing options use the shared frontend. Scoring requires an authored
package with prefill logits. Use `--help` for options.

`--cache_capacity` may differ from the default only when the package declares
an authored `capacity_range`. Both the contract and source tensor bounds are
checked. Fixed packages require reauthoring for different geometry.
`--prefill-chunk-size` selects live chunks within the authored row bound.
Explicit capacity replacement in the library prepares a complete new variant
before copying initialized state. Ordinary invocation never grows implicitly.

The loader verifies stored semantic identities, input/state interfaces, scalar
coverage, geometry and vocabulary. `--check_package=DIR` performs structural
checks without native inference; asset identities are verified during preparation.
Cache owners persist across phases and fixed recurrent states use paired buffers.
Invalid requests leave state usable. A late native failure poisons the request
until the session's reset/discard procedure succeeds.

Execution contract 2 declares backend `ynnpack`, API `1`, artifact ABI
`data-only-v1`, parameter encoding `little-endian-typed-v1`, and required features
`shape-preflight-v1`, `resource-state-v1`, `completion-v1` and `fixed-state-v1`.
Unknown, missing, duplicate or incompatible declarations fail. Contract 1 is
supported for small existing semantic fixtures; this is not an offline loader.
These experimental contracts make no stable native binary/cache ABI promise.

The run retains its `model.json` and records package/profile identities in
`run.json`. `setup.json` records parsing, lowering and preparation separately. `timings.jsonl`
uses `rep`, `step`, `position`, `prefix_ms` and `token_ms`; `memory.json` and
`counters.json` are process-wide observations. Dump names are
`CASE_rREP_sSTEP.logits.bin` and final-state `CASE_rREP_STATE.bin`.
Optional per-step state uses `CASE_rREP_sSTEP_STATE.bin`. Gemma's former specialized dump/timing schema is retired.
Use [compare_runtime.py](../tools/compare_runtime.py) when comparing frozen
specialized controls with this schema.

For diagnostics, `--dump_outputs` writes logits at every measured decode step
and final KV/fixed state for each request. Add `--dump_state_steps` when comparing
intermediate state transitions; it writes full-capacity state after every decode
step and can produce large captures. These runs are excluded from latency results.
