<!-- Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0 -->

# Qwen3

The `qwen3` runner executes Qwen3-0.6B and the original Qwen3-4B as standalone
`.ynn` packages. Both use global grouped-query attention. These are experimental
CPU comparison workloads; cross-runtime INT8 drift remains, and task accuracy
and free-running generation quality have not been established.

| Model | Directory | Layers | Hidden width | Q / KV heads | Head width |
| --- | --- | ---: | ---: | ---: | ---: |
| Qwen/Qwen3-0.6B | `models/qwen3_0_6b` | 28 | 1024 | 16 / 8 | 128 |
| Qwen/Qwen3-4B | `models/qwen3_4b` | 36 | 2560 | 32 / 8 | 128 |

The 4B package is not Qwen3-4B-Instruct-2507. Both vocabularies have 151,936
entries. The checkpoint snapshot identities are recorded in each `model.json`.

## Package and arithmetic

The generated directory contains `prefill.ynn`, `decode.ynn`, and `model.json`.
Matching weight payloads belong in its ignored `parameters/` directory and
tokenizer assets in its ignored `tokenizer/` directory. Parameter filenames are
SHA-256 identities; the runtime checks the plans against the manifest and
validates parameter payloads. Use a complete matching package. Copying a
different checkpoint into the parameter directory is not an asset conversion.

The `mixed_int8_int8_mlp_only` recipe uses symmetric INT8 linear weights per
output channel, asymmetric dynamic INT8 activations per token, and INT8
embeddings. Its historical name does not limit INT8 weights to MLPs. Attention
and KV caches use FP32. Embedding codes/scales are gathered before
dequantization. Prefill and decode use the same arithmetic policy.

Each plan defines one reusable `global_attention_h*_kv8_d128_q*` function.
Layer calls retain `LayerNN/GlobalAttention` profiling scopes. Resource writes
remain outside that pure function. The function lowers to native YNNPACK
matmuls, scale/mask, softmax, and a value matmul; it does not use the ordered
scalar attention callback. Capacity is 2,048 and the prefill graph has 128
physical query rows. The final short chunk is padded for computation but only
real K/V rows are appended. Decode has one row. The FP32 cache layouts are
`[1,8,2048,128]` for K and `[1,8,128,2048]` for V.

## Build and run

Follow the root build instructions, then build the model runner:

```sh
cmake --build build --target qwen3 ynn_plan --parallel 8
```

With a complete package in `models/qwen3_0_6b/generated`:

```sh
LAB_YNN_MATH=fast_math build/qwen3 \
  --bundle_dir=models/qwen3_0_6b/generated \
  --parameter_dir=models/qwen3_0_6b/generated/parameters \
  --cases_file=models/qwen3_0_6b/fixtures/perf.tsv \
  --output_dir=out/qwen3_0_6b \
  --cache_capacity=2048 --prefill_rows=128 --num_threads=4 \
  --warmup_runs=1 --measured_runs=3
```

Replace `qwen3_0_6b` with `qwen3_4b` for 4B. A token-ID case file does not require
a tokenizer. Text input uses the shared [input frontend](TOKENIZERS.md) and an
explicit matching `--tokenizer_dir`. Outputs must use a fresh directory.

A request resets state, prefills all but the final prompt token in chunks, and
then decodes that token followed by the forced continuation. Continue-prefill
after decoding is outside this package's paired runtime contract. Requests
cannot exceed capacity; a failed execution poisons the session until reset.
The last prefill layer produces KV only, so prefill has 27/35 attention calls
and decode has 28/36.

## Validation and measurements

`fixtures/matrix.tsv` covers prompts 1, 17, 128, 129, 130, 513, 1025 and 2032,
with 16 continuation tokens and a repeated short request after reset. Use
`--dump_outputs --warmup_runs=0 --measured_runs=2` for correctness. Compare
logits and committed KV history; reset invalidates logical extent without
zeroing unused cache tails.

Use the [current results index](../results/README.md) for timings and actual
validation coverage. Qwen3 has recorded numerical drift against independent
Torch and LiteRT-LM controls; teacher-forced agreement does not establish
sustained generation quality. Keep the same source, token IDs, math flags,
quantization and real prefill work in a paired comparison.

`--profile_execution=all` collects separate layer diagnostics. `--report_memory`
and value tracing are diagnostic too; `run.json` marks their timing unsuitable
for latency claims. Setup is separate from warm TTFT. Decode excludes the first
prompt-token step. See [benchmarking](BENCHMARKING.md).

## Attention layout contract

The packages use small-query operand reversal and a transposed persistent V
cache. Track storage layout, operand orientation, capacity strides and selected
kernels together. Cancelling serialized transpose operators alone does not
prove that backend packing/transposition work disappeared. Cropped live views
retain their physical capacity strides.

Check layout changes with persistent resource views and an independent FP64
attention oracle, then validate full-model logits and live KV. Preserve the
current arithmetic policy when isolating a layout experiment.

`LAB_YNN_MATH=fast_math` selects the graph flags used by the earlier LiteRT
comparison; `no_excess_precision` remains the default. Changing flags changes
the arithmetic contract. Also inspect the comparator's actual prefix work:
some static executors prefill all prompt tokens and recompute the last in decode,
whereas this runner prefills `prompt_tokens - 1`.
