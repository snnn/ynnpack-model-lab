<!-- Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0 -->

# Documentation

Start with the repository [README](../README.md) for the lab's research scope,
host/Android builds, and [model support](../README.md#models-and-workloads).
Model guides have equal standing; select the workload and numerical profile
needed for your experiment. Run example commands from the
repository root. Guides describe the current checkout; dated results describe
only their recorded binaries, artifacts, dependencies and devices.

## Run workloads

| Guide | Contents |
| --- | --- |
| [Gemma4 E2B](E2B.md) | Asset preparation, execution, state, source profiles and validation |
| [Gemma4 E4B](E4B.md) | Asset preparation, execution, multi-head state and memory/stack requirements |
| [Qwen3-0.6B / Qwen3-4B](QWEN3.md) | Standalone packages, dynamic INT8 arithmetic, state, validation and timing policy |
| [Gemma4 E2B from safetensors](HF_GEMMA4.md) | Direct loading, arithmetic/KV profiles, derived storage and reference checks |
| [Vision models](VISION.md) | FP32 classifiers, required assets and CPU comparison commands |
| [Text inputs and tokenizers](TOKENIZERS.md) | Tokenizer preparation, text/corpus inputs and exact token-ID replay |
| [Decode attention experiments](ATTENTION_EXPERIMENTS.md) | Opt-in policies and the independent attention harness |
| [Recurrent step experiments](RECURRENT_STEP_EXPERIMENT.md) | Prepared primitive graphs, state checks and CPU component comparisons |

Gemma4 12B, 31B and other Qwen variants remain planned additions; see
[model integration work](worklogs/MODEL_INTEGRATIONS.md). Tokenizer support alone
does not imply model-execution support.

## Design and developer interfaces

| Reference | Contents |
| --- | --- |
| [Design](DESIGN.md) | Architecture, state invariants, numerical contracts and model extension |
| [Model artifacts](AUTHORING.md) | Public package layout, asset identities and author/runtime responsibilities |
| [Construction plans](GRAPH_PLANS.md) | Typed construction model, validation stages and execution limits |
| [Plan text](PLAN_TEXT.md) | `.ynn` syntax, formatter, inspection tool and diagnostics |
| [Rust runtime](RUST_RUNTIME.md) | Ownership, native boundary, request lifecycle and fixture harness |

## Measure and publish

| Guide | Contents |
| --- | --- |
| [Benchmarking](BENCHMARKING.md) | Timing/RSS definitions, controlled comparisons and capacity sweeps |
| [Profiling](PROFILING.md) | Execution attribution, native controls and selected-kernel samples |
| [Publication](PUBLICATION.md) | Public source/evidence, portable records and publication checks |
| [Dependency patches](../patches/README.md) | Pinned backend changes and isolated experimental builds |

## Work logs and retained evidence

[Open work](worklogs/README.md) separates unfinished investigations and validation
gaps from these usage/design references. The [results index](../results/README.md)
holds the current baseline and supporting evidence for unresolved issues.

Keep documentation in these roles:

- `docs/`: current usage, interfaces, design decisions and known limitations.
- `docs/worklogs/`: unfinished work, with evidence, the remaining gap and a
  concrete completion check. Do not copy full measurement tables here.
- `results/`: dated, reproducible evidence with its exact configuration and
  numerical/measurement limits. Completion alone is no reason to discard a
  useful baseline or bug reproduction.

When work finishes, fold lasting behavior into its guide and retain useful
evidence under `results/`. Delete the completed work log or resolved entry;
avoid keeping a second chronological account. Raw captures and temporary
PR-review experiments remain in ignored output directories.
