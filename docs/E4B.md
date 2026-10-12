# Gemma4 E4B

E4B uses the shared Gemma4 author and Rust runner with its own `.ynn` plans
and hash-verified asset recipe. The executable is `gemma4_e4b`; its published
bundle preserves packed weights, static QAT activation scales and INT8 KV.

## Prepare and run

Build with the repository [Linux](../README.md#build-and-test-on-linux) or
[Android](../README.md#android-the-same-cmake-build) commands;
`--target gemma4_e4b` builds only this model executable.

```sh
uvx hf download litert-community/gemma-4-E4B-it-litert-lm \
  gemma-4-E4B-it.litertlm \
  --revision 1a64948b38efa40cd88a820e1e7cc1a6179ae05e \
  --local-dir assets/download-e4b
python3 tools/prepare_gemma4.py --variant e4b \
  --model assets/download-e4b/gemma-4-E4B-it.litertlm \
  --output assets/gemma4_e4b
./build/gemma4_e4b \
  --graph_dir=models/gemma4_e4b/generated \
  --bundle_dir=assets/gemma4_e4b/bundle \
  --parameter_dir=assets/gemma4_e4b/parameters \
  --cases_file=models/gemma4_e4b/fixtures/performance.tsv \
  --output_dir=out/e4b-performance \
  --cache_capacity=2048 --num_threads=4 --prefill_rows=128 \
  --warmup_runs=1 --measured_runs=3
```

Source identity: 3,654,467,584 bytes, SHA-256
`f335f2bfd1b758dc6476db16c0f41854bd6237e2658d604cbe566bcefd00a7bc`.
The preparer verifies 2,143 files / 1,570 unique payloads. The two phase plans use
426 generated parameter files. There is no new quantization or calibration.
Its format remains an artifact-specific extraction recipe, not a general
LiteRT-LM importer.

Use a fresh output directory per run. The performance fixture uses prompts
17/128/1024 and 16 forced continuation tokens; correctness fixtures cover
short chunks and window crossings with two continuations. See
[benchmarking](BENCHMARKING.md) for timing definitions and
[text inputs](TOKENIZERS.md) for tokenizer preparation and text/corpus cases.

## Architecture and state

| Property | Value |
| --- | ---: |
| Layers | 42 |
| Model width | 2560 |
| Query / KV heads | 8 / 2 |
| Unique KV owners | 24 |
| Global attention period | 6 |
| Local / global head width | 256 / 512 |
| PLE storage | INT2 |
| Transformer MLP weights | INT4 |
| KV bytes per capacity token | 28,672 |

E4B keeps K and V in separate `[1,2,C,D]` allocations for each owner. A cropped
view retains the capacity stride between heads. Each append writes the new rows
for both heads; old history is not concatenated or copied to update state.
Query heads 0–3 consume KV head 0; query heads 4–7 consume KV head 1. Their
attention results are concatenated along the query-head axis. This concatenates
new attention outputs, not the persistent KV history. The manifest preserves
the published graph's original shape templates as provenance; the native
runner's allocation layout is the token-major layout described here.

The graph uses real query rows and bounded live history. The local view covers
the union of key positions needed by the chunk, then a per-query mask applies
causality and the 512-token window. Prefix-only execution stops after producing
the last KV owner; the final prompt token runs the full decode graph.

Raw persistent KV is 56 MiB at capacity 2048 and 231 MiB at 8448. That 175 MiB
increment is storage, not a requirement to compute attention over unused slots.
Weights, independent phase packing, scratch, and embedding residency are much
larger contributors to the present overall footprint.

## Android deployment

After the shared Android build and device tests, deploy into a model-specific
directory. Check storage and available memory first: retained E4B measurements
use several GB of resident memory, as detailed below.

```sh
adb -s "$ANDROID_SERIAL" shell mkdir -p /data/local/tmp/ynnpack-model-lab/gemma4_e4b
adb -s "$ANDROID_SERIAL" push build-android/gemma4_e4b \
  assets/gemma4_e4b/bundle assets/gemma4_e4b/parameters \
  models/gemma4_e4b/fixtures models/gemma4_e4b/generated \
  /data/local/tmp/ynnpack-model-lab/gemma4_e4b/
adb -s "$ANDROID_SERIAL" shell 'cd /data/local/tmp/ynnpack-model-lab/gemma4_e4b && \
  ./gemma4_e4b --graph_dir=generated \
  --bundle_dir=bundle --parameter_dir=parameters \
  --cases_file=fixtures/performance.tsv --output_dir=c2048-t4 \
  --cache_capacity=2048 --num_threads=4 --prefill_rows=128 \
  --warmup_runs=1 --measured_runs=3'
adb -s "$ANDROID_SERIAL" pull \
  /data/local/tmp/ynnpack-model-lab/gemma4_e4b/c2048-t4 out/android-e4b-c2048-t4
```

## Runtime limits and validation

The shared Rust Gemma entry point prepares and executes both E2B and E4B on
an explicit thread with a 64-MiB stack reservation. This works around recursive
Slinky preparation depth; pages become resident only when touched. The
[original E4B crash and workaround](../results/e4b_2026-10-02/README.md#android-preparation-stack-overflow)
remain recorded. A larger stack does not fix backend recursion. Library callers
must provide the stack budget described in [RUST_RUNTIME.md](RUST_RUNTIME.md).

Published-bundle text-to-TSV replay has been checked with the current Rust/`.ynn`
runner on Linux and one Android ARM64 device at capacity 2048, including partial
prefill chunks, window crossings and repeated requests. These checks do not
establish broader device/profile coverage, generation quality or current
performance. Earlier C++ device results retain their original scope.

Use correctness fixtures and `--dump_outputs` in separate runs, then compare
matching logit/KV dumps:

```sh
uv run --no-project --with numpy python tools/compare_outputs.py \
  --reference out/reference-dumps --candidate out/candidate-dumps \
  --output out/comparison.json
```

The NumPy dependency runs in a separate uv environment. Keep capacity-only
comparisons exact where the control is exact. Cross-backend logit/KV differences
and teacher-forced greedy agreement need separate interpretation; they do not
certify equivalent generation quality. Disable dumps for timing runs.

## Measurement records

| Record | Scope |
| --- | --- |
| [Original E4B integration](../results/e4b_2026-10-02/README.md) | Desktop/TECNO execution, exact capacity checks, static-QAT XNNPACK host comparison and stack reproduction |
| [October 5 backend refresh](../results/2026-10-05/README.md) | Fresh previous/adopted desktop controls and selected kernels |
| [Packing correction](../results/2026-10-05-packing-fix/README.md) | Desktop timing and numerical changes; capacity comparisons remain exact |
| [October 7 mobile baseline](../results/2026-10-07-upstream-refresh/README.md) | TECNO one/four-thread, capacity and numerical checks; Linux was not retimed |

These records retain their C++ runners and original configurations. The October 7
campaign skipped Pixel/Samsung E4B for available-memory limits. No matched native
E4B phone control is included. Check current device storage and available RAM
before deployment; mmap weights and independent phase packing contribute to
RSS beyond the raw KV allocation.
