<!-- Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0 -->

# Qwen3.5-4B

The shared `qwen3` runner executes the text portion of Qwen/Qwen3.5-4B from
`models/qwen3_5_4b/generated`. FP32 remains the validated baseline. Experimental
INT8 and mixed INT4 profiles are available under `models/qwen3_5_4b/profiles`.
Vision, task evaluation, and free-running generation quality are outside the
validated scope. LiteRT-LM is not used as the reference for these packages.

## Model and state

The 32 layers repeat three gated-delta layers followed by one global-attention
layer. Each semantic phase retains reusable gated-delta and global-attention
functions. Gated-delta recurrence is one scheduled native operation per layer,
with a sequential token loop and parallel independent heads/value tiles. Its
AVX2 CPU kernel retains the state layout and uses a compact stack tile during
prefill. Graph size does not grow with the number of prefill tokens. Each phase
also has 24 direct causal-convolution/history-update operations, avoiding a
concatenated history tensor and generic stencil/dot execution. Q/K normalization,
SiLU, gated normalization, partial RoPE, and MLPs remain surrounding tensor work.

| Property | Value |
| --- | --- |
| Checkpoint | Qwen/Qwen3.5-4B, revision `851bf6e806efd8d0a36b00ddf55e13ccb7b8cd0a` |
| Weights and arithmetic | Published BF16 weights cast to FP32; no quantization |
| Batch / prefill rows / decode rows | 1 / 128 / 1 |
| Default capacity | 2,048 |
| Full attention | 16 query heads, 4 KV heads, width 256; partial rotary width 64 |
| K cache | `[1,4,capacity,256]` |
| V cache | `[1,4,256,capacity]`, retained across the function boundary |
| Recurrent state per linear layer | `[1,32,128,128]`, FP32 |
| Convolution history per linear layer | `[1,3,8192]`, FP32 |

Only real rows update state. Convolution history ends at the last real token;
recurrence skips padded rows. Full attention appends only real K/V rows and
reads committed history. Each fixed-size convolution/recurrent state uses
separate incoming/outgoing buffers, swapped after successful execution and
both cleared on reset. KV resource reset invalidates its live extent. A late
failure poisons the session until reset. Prepared phases support continued
prefill and prefill after decode.

## Run

Build the shared runner with the repository's pinned dependencies:

```sh
cmake --build build --target qwen3 --parallel 8
LAB_YNN_MATH=no_excess_precision build/ynn-llm \
  --model_dir=models/qwen3_5_4b/generated \
  --parameter_dir=models/qwen3_5_4b/generated/parameters \
  --cases_file=models/qwen3_5_4b/fixtures/perf.tsv \
  --output_dir=out/qwen35-fp32 \
  --cache_capacity=2048 --prefill_rows=128 --num_threads=4 \
  --warmup_runs=1 --measured_runs=3
```

The matching FP32 parameter payloads and tokenizer are ignored local assets.
Use a complete generated package; the BF16 checkpoint files are not substitutes
for its hash-verified FP32 parameters. The two prepared phases use about 32 GiB
of resident memory on the measured host, so allow memory for setup and the OS.

A request prefills all but its final prompt token, then decodes that token and
the forced continuation. `--prefill_chunk_size=32` exercises shorter real chunks
with the same prepared 128-row graph. It must be between one and the package's
prefill row count. Changing cache capacity requires a matching generated package.
Text inputs use `--tokenizer_dir` and `--prompt`, as described in
[TOKENIZERS.md](TOKENIZERS.md).

For correctness, use `--dump_outputs --warmup_runs=0 --measured_runs=2`. Dumps
include full-vocabulary logits, fixed states and physical KV buffers; compare
only live KV history. For layer diagnostics use a separate
`--profile_execution=all` run. It identifies recurrent projection, causal
convolution, gated-delta, global attention, normalization, MLP and output-head
work. Instrumented timings are not benchmark results.

## Recorded numerical qualification

The following qualification predates the current refresh. Fresh coverage is
listed in the [results index](../results/README.md); these observations do not
automatically qualify a changed runner or backend.

Unmodified Transformers 5.12.1 eager CPU FP32 is the independent model reference.
The matrix covers prompt lengths 1, 17, 128, 129, 130, 513, 1,024, 1,025 and
2,032, each followed by 16 forced tokens. All full-model logit gates passed:
maximum RMSE `2.28e-4`, maximum absolute error `1.46e-3`, and 153/153 distinct
top-token predictions agreed. Reset reproduced logits, fixed states and live
KV exactly. Shorter chunks and a 4,096-capacity package passed the same gates.

Isolated recurrence tests include an FP64 oracle, unequal key/value widths,
explicit head mappings, nonzero incoming state and zero valid rows. A small
four-layer model and the checkpoint's first four layers additionally cover
prefill after decode. These checks do not establish generation-quality parity.
Full-model states are not bit-identical to HF; the largest measured KV element
error was about `0.0194`, with normalized RMS error `7.77e-5` in that cache.

## Experimental quantized profiles

Choose the complete package with `--model_dir` and its matching
`--parameter_dir`. The original `generated` directory remains FP32.

| Profile directory | MLP weights | Other large projections | Tied embedding/head |
| --- | --- | --- | --- |
| `profiles/int8/generated` | INT8 per output row | INT8 per output row | INT8 per output row |
| `profiles/int4_mlp/generated` | Signed INT4, group 32 | INT8 per output row | INT8 per output row |

Linear activations are dynamically quantized per token row. Attention, KV,
recurrent state, control projections, convolution and norms remain FP32.
The grouped INT4 adapter retains packed weights and unpacks a 4 KiB tile for
native integer dots; there is no full decoded weight matrix. Matching parameter
payloads and tokenizer directories are ignored local assets.

These profiles do **not** pass the baseline's strict full-model logit gate
against the quantized PyTorch oracle. A focused replay traced divergence to
activation-quantization rounding boundaries after tiny FP32 differences.
The native INT8 profile passes the separate held-out perplexity gate: `8.25778`
versus original HF `8.24695`, a `0.131%` increase on 16,376 predictions.
The earlier INT4-MLP study scored `8.52153` (+3.33%), missing its 3% gate.
This CPU update checked INT4 compatibility with exact prompt-17 replay; it did
not repeat full INT4 quality or timing. The original HF
reference uses unmodified Transformers with CPU FP32 eager attention. The
quantized oracle separately substitutes arithmetic over the exported codes
and scales. These checks do not establish generation-quality parity.

Held-out scoring uses a separate package with all-row prefill logits and
`--score_tokens --warmup_runs=0 --measured_runs=1`. The runner rejects a scoring
package in ordinary benchmark mode. Benchmark prefill omits the output head;
the final prompt token still runs through decode and produces first logits.

## Performance and remaining questions

Use the [current results index](../results/README.md) for fresh measurements.
The [quantization study](../results/qwen35_quantization_20261015/README.md)
retains historical quality failures and comparison limitations. Quantization
recipes and arithmetic differ between lab INT8 and llama.cpp Q8_0.

Profile complete recurrence/state stages, including state gather/writeback,
rather than comparing named kernel nodes alone. Setup, memory and execution
profiles belong in separate diagnostic runs. Prefix throughput uses
`prompt_tokens - 1`; decode excludes the final prompt-token step. Do not combine
older bandwidth observations with new latency measurements.
