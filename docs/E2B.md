<!-- Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0 -->

# Gemma4 E2B

E2B uses the shared Gemma4 Rust runner with its own `.ynn` plans, asset recipes
and fixtures. Its executable is `gemma4_e2b`. Build with the repository
[Linux](../README.md#build-and-test-on-linux) or
[Android](../README.md#android-the-same-cmake-build) instructions;
`--target gemma4_e2b` builds only this model executable.

Two source paths are available. The published-bundle path below preserves its
packed weights, static QAT activation scales and INT8 KV policy. The
[safetensors guide](HF_GEMMA4.md) covers direct checkpoint loading with explicit
BF16, FP32 and integer-FC profiles. These paths have different numerical
contracts; select the source/profile needed for the experiment.

## Prepare and run

Download the exact published artifact used for the bundle plans. Follow the
publisher's access and license requirements; model weights are external.

```sh
uvx hf download litert-community/gemma-4-E2B-it-litert-lm \
  gemma-4-E2B-it.litertlm \
  --revision 2a101e00c47f942975ce8b493c2498311ed9900d \
  --local-dir assets/download-e2b
python3 tools/prepare_gemma4.py --variant e2b \
  --model assets/download-e2b/gemma-4-E2B-it.litertlm \
  --output assets/gemma4_e2b
./build/gemma4_e2b \
  --graph_dir=models/gemma4_e2b/generated \
  --bundle_dir=assets/gemma4_e2b/bundle \
  --parameter_dir=assets/gemma4_e2b/parameters \
  --cases_file=models/gemma4_e2b/fixtures/performance.tsv \
  --output_dir=out/e2b-performance \
  --cache_capacity=2048 --num_threads=4 --prefill_rows=128 \
  --warmup_runs=1 --measured_runs=3
```

Expected source: 2,583,085,056 bytes, SHA-256
`ab7838cdfc8f77e54d8ca45eadceb20452d9f01e4bfade03e5dce27911b27e42`.
Allow several GB of disk space for the source and extracted assets.

The standard-library preparer verifies the source, copies weight/scale ranges,
interleaves PLE partitions by token and verifies every unique output payload.
It preserves published integer codes and source precision; identical payloads
share hard links. A different model file requires a new reviewed recipe and
validation.

Use a fresh output directory for every run. The performance fixture has prompts
17/128/1024 and 32 forced continuation tokens per prompt. The correctness fixture
has prompts 1/128/129/1024 and two continuations. See
[text inputs](TOKENIZERS.md) for tokenizer preparation and text/corpus cases.

`timings.jsonl` records prefix/per-token time, setup, RSS, argmax and state
counters. Use `--dump_outputs` for separate logit/KV correctness checks and
`--dump_pipeline` for Slinky diagnostics. Disable dumps for timing and use the
[benchmarking guide](BENCHMARKING.md) for metric definitions and capacity checks.

## Architecture and state

The following storage contract describes the published-bundle profile.

| Property | Value |
| --- | ---: |
| Layers | 35 |
| Model width | 1536 |
| Query / KV heads | 8 / 1 |
| Unique KV owners | 15 |
| Global attention period | 5 |
| Local / global head width | 256 / 512 |
| PLE storage | INT4 |
| Transformer MLP weights | Mixed INT4 / INT2 |
| KV bytes per capacity token | 9,216 |

Each KV owner has separate K/V buffers shaped `[1,1,C,D]`. Appends write only new
tokens; attention views cover live history with causal and 512-token local-window
masks. Raw INT8 KV storage is 18 MiB at capacity 2048 and 74.25 MiB at 8448.
Increasing capacity reserves storage without extending logical attention work.

Prefill accepts 1–128 real rows, including a short final chunk, and stops after
the required KV owners. The last prompt token uses the full decode graph and
head for first logits. Both phase graphs and persistent state are reused across
requests. Increasing the 128-row bound requires reauthoring and validation.

## Android deployment

After the shared Android build and device tests, deploy the bundle profile into
its own directory. Check available storage and memory first.

```sh
adb -s "$ANDROID_SERIAL" shell mkdir -p /data/local/tmp/ynnpack-model-lab/gemma4_e2b
adb -s "$ANDROID_SERIAL" push build-android/gemma4_e2b \
  assets/gemma4_e2b/bundle assets/gemma4_e2b/parameters \
  models/gemma4_e2b/fixtures models/gemma4_e2b/generated \
  /data/local/tmp/ynnpack-model-lab/gemma4_e2b/
adb -s "$ANDROID_SERIAL" shell 'cd /data/local/tmp/ynnpack-model-lab/gemma4_e2b && \
  ./gemma4_e2b --graph_dir=generated \
  --bundle_dir=bundle --parameter_dir=parameters \
  --cases_file=fixtures/performance.tsv --output_dir=c2048-t4 \
  --cache_capacity=2048 --num_threads=4 --prefill_rows=128 \
  --warmup_runs=1 --measured_runs=3'
adb -s "$ANDROID_SERIAL" pull \
  /data/local/tmp/ynnpack-model-lab/gemma4_e2b/c2048-t4 out/android-e2b-c2048-t4
```

The HF profiles have different assets and backend requirements; use the
[HF instructions](HF_GEMMA4.md) for those packages.

## Runtime limits and validation

The shared Rust Gemma entry point reserves a 64-MiB execution-thread stack for
Slinky preparation. Library callers must supply the stack budget described in
[RUST_RUNTIME.md](RUST_RUNTIME.md). After a late execution failure, discard the
failed session; state can be partially modified.

Published-bundle text-to-TSV replay has been checked with the current Rust/`.ynn`
runner on Linux and one Android ARM64 device at capacity 2048, including partial
prefill chunks, window crossings and repeated requests. This does not establish
HF-profile device coverage, generation quality or current performance.
Historical device results apply to their recorded runners.

## Measurement records

| Record | Scope |
| --- | --- |
| [Original E2B comparison](MEASUREMENTS.md) | Historical host/phone controls, numerical checks and capacity comparison |
| [Packing correction](../results/2026-10-05-packing-fix/README.md) | Matched host/phone timing and numerical changes |
| [October 7 mobile baseline](../results/2026-10-07-upstream-refresh/README.md) | Previous-pin/native phone controls and separate profiles |
| [KV-history investigation](../results/2026-10-08-kv-history/README.md) | Samsung attention layout, conversion/packing and thermal effects |

These completed studies retain their C++ runners and exact configurations.
See the [results index](../results/README.md) for published HF and backend
studies.
