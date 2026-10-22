# General LLM runner

`ynn-llm` loads prefill/decode `.ynn` packages for multiple model families. It
uses YNNPACK only. Input recipes and state bindings live in `model.json` under
`runner`; model names do not select runtime code. The executable can load a new
supported package without recompilation.

```sh
cmake --build build --target ynn-llm --parallel 8
build/ynn-llm \
  --graph_dir=models/qwen3_0_6b/generated \
  --bundle_dir=models/qwen3_0_6b/generated \
  --parameter_dir=models/qwen3_0_6b/generated/parameters \
  --cases_file=cases.tsv --output_dir=out/qwen3-generic --num_threads=4
```

Case lines contain a name, comma-separated prompt IDs and comma-separated
continuation IDs, separated by tabs. The existing frontend's tokenizer,
teacher-forcing, repetition and timing options remain available. Token scoring
requires a package that explicitly exports prefill logits.

Qualified local profiles are Qwen3-0.6B, Qwen3-4B, Qwen3.5-4B INT8, and the
published FP32-activation Gemma4 E2B/E4B profiles. For Gemma, point `--bundle_dir`
and `--parameter_dir` at its existing `assets/MODEL/bundle` and
`assets/MODEL/parameters` directories. Qwen3.5 INT8 uses
`models/qwen3_5_4b/profiles/int8/generated`. Other Gemma HF/BF16 profiles continue
to use their existing runners until their generic package contracts are supplied
and validated.

The loader verifies graph hashes, input/state interfaces, scalar coverage,
geometry and vocabulary. Run `ynn-llm --check_package=PACKAGE` to check graph
contracts without native inference. Parameter and packed embedding hashes are
checked when loaded. Cache owners persist across both phases; fixed recurrent
states use paired buffers. Invalid requests leave state usable. Failure after
native execution begins poisons the session until reset.

Runner contract 2 additionally declares `compatibility`: backend `ynnpack`,
backend API `1`, artifact ABI `data-only-v1`, parameter encoding
`little-endian-typed-v1`, and required features `shape-preflight-v1`,
`resource-state-v1`, `completion-v1` and `fixed-state-v1`. The loader rejects
unknown, missing, duplicate or incompatible declarations before native execution.
Legacy contract 1 remains an explicit supported path; it cannot request newer
features. These declarations describe a data package, not a stable native
binary/cache ABI. Keep dependency, adapter, binary and parameter hashes with
correctness results when rebuilding the runner.

This migration adds metadata around the same `.ynn` plans and parameter bytes.
It does not change quantization, attention math or persistent cache layouts.
Legacy `qwen3`, `gemma4_e2b` and `gemma4_e4b` executables remain available for
comparison and profiles outside this qualification. There is no GPU backend in
this runner.
