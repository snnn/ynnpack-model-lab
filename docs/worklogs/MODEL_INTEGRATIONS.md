<!-- Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0 -->

# Planned model integrations

The intended LLM scope includes Gemma4 E2B, E4B, 12B and 31B, and multiple Qwen
models. Model guides have equal standing; current implementation coverage does
not define a preferred workload or the order of future integrations.

## Current coverage

| Model | Status in this checkout | Remaining integration work |
| --- | --- | --- |
| Gemma4 E2B | Published-bundle and HF profiles are integrated | Further validation is tracked separately |
| Gemma4 E4B | Published-bundle profile is integrated | Further validation is tracked separately |
| Gemma4 12B | Planned; no model package or runner target | Architecture/source mapping, assets, plans, runtime compatibility and validation |
| Gemma4 31B | Planned; no model package or runner target | Architecture/source mapping, assets, plans, runtime compatibility and validation |
| Qwen3-0.6B / Qwen3-4B | Dynamic INT8, FP32 KV packages and `qwen3` execution integrated | Broader quality/device validation; see [Qwen3](../QWEN3.md) for measured drift |
| Qwen3.5-4B | FP32 baseline and experimental INT8/INT4-MLP packages integrated | Quantized quality and broader device validation; see [Qwen3.5](../QWEN35.md) |
| Other Qwen models | Qwen3.5-0.8B tokenizer recipe; execution planned | Per-model architecture/state semantics, assets, plans, runtime compatibility and validation |

The [CMake targets](../../cmake/RustRuntime.cmake) use the shared semantic
runtime. Gemma names select a default package directory; all model interfaces
come from the [execution contract](../../rust/src/runtime/execution.rs).
The [public model specification](../../models/gemma4/model_spec.py) covers
Gemma architecture and checkpoint interpretation. Supplying another checkpoint
or tokenizer does not add model execution; a new family needs an authored
program and supported asset/state contracts.

## Completion checks for each addition

1. Record the exact checkpoint, architecture, numerical profile and tokenizer
   policy; provide hash-verified public asset preparation.
2. Export a matching semantic program, execution contract and metadata. Keep model-specific behavior
   in its author/package and add any required shared runtime operations with
   independent arithmetic/state checks. Private authoring remains separate.
3. Validate model outputs against a named reference and test the model's actual
   state transitions, reset, bounds and chunk behavior. Record device/resource
   limits and numerical differences explicitly.
4. Retain reproducible setup, warm execution and memory measurements, then add
   a self-contained model guide and update the support table.

Use the [extension design](../DESIGN.md#adding-another-model) and
[artifact interface](../AUTHORING.md). Current-model
[validation gaps](VALIDATION_GAPS.md) remain separate from these additions.
