<!-- Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0 -->

# Qwen3.5-4B quantization and llama.cpp comparison

The standalone `int8` and `int4_mlp` profiles are experimental. INT8 passes the
held-out perplexity gate; INT4-MLP misses its gate. Both fail strict full-model
logit parity against the independent quantized HF oracle. The qualified
FP32 baseline (historical record archived locally) is preserved.
This capture validates Linux x86-64, without Android or ARM revalidation.

At prompt 128 on four physical cores, the matched uninstrumented runs give:

| Runtime/profile | Prefill tokens/s | Warm TTFT ms | Decode tokens/s |
| --- | ---: | ---: | ---: |
| Lab FP32 | 50.80 | 3036.90 | 1.870 |
| llama.cpp F32 | 63.08 | 2482.91 | 2.131 |
| Lab INT8 | 99.20 | 1422.70 | 7.051 |
| llama.cpp Q8_0 | 62.08 | 2175.28 | 7.745 |
| Lab INT4-MLP | 11.68 | 11468.32 | 1.670 |
| llama.cpp Q4_K_M | 93.35 | 1447.66 | 11.513 |

INT8 improves lab decode by 3.77x over FP32. Its prefill is 1.60x llama.cpp
Q8_0 at this prompt, while its decode rate is 9.0% lower. The grouped INT4
adapter is slower than lab FP32 despite its smaller coefficient payload.
This measures the current adapter and recipe, not all possible INT4 lowerings.

The reverse-order prompt-128 repeat changes decode rates by at most 0.70%.
Prefill varies more: llama.cpp Q8_0's repeat is 9.6% slower. Eight physical
cores give:

| Runtime/profile | Prefill tokens/s | Decode tokens/s |
| --- | ---: | ---: |
| Lab FP32 | 90.56 | 1.944 |
| llama.cpp F32 | 110.02 | 2.239 |
| Lab INT8 | 172.42 | 7.889 |
| llama.cpp Q8_0 | 105.34 | 8.095 |
| Lab INT4-MLP | 23.70 | 2.870 |
| llama.cpp Q4_K_M | 174.57 | 12.248 |

The INT8 decode gap falls to about 2.5% at eight cores. INT4's much larger gap
persists; increasing thread count does not make this adapter competitive.

## Arithmetic and quality

INT8 uses symmetric per-output-row weights for the tied embedding/head and
large attention/MLP projections. INT4-MLP changes the 96 MLP matrices to signed
INT4 with group size 32. Selected linear operations dynamically quantize
activation rows. Control projections, convolution, normalization, attention,
KV and recurrent state remain FP32. The INT4 adapter expands only a bounded
integer tile; it does not retain a fully decoded weight matrix.

Original HF means publisher weights and unmodified Transformers architecture,
with CPU FP32 eager attention. The quantized oracle separately substitutes
linear/embedding arithmetic over the exported codes and scales. No converter
graph patches participate in either reference. All quality rows use the same
16,376 predictions from the first eight nonoverlapping 2,048-token blocks of a
pinned WikiText-2 raw test split, with state reset between blocks and no inserted
BOS/EOS or chat template. This is a quality screen, not full task evaluation.

| Execution | Perplexity | Increase over original HF |
| --- | ---: | ---: |
| Original HF FP32 | 8.246952 | baseline |
| Quantized HF INT8 oracle | 8.231185 | -0.191% |
| Lab INT8 | 8.257779 | +0.131% — passes 1% gate |
| Quantized HF INT4-MLP oracle | 8.551579 | +3.694% — misses 3% gate |
| Lab INT4-MLP | 8.521534 | +3.329% — misses 3% gate |
| llama.cpp F32 | 8.246960 | +0.000091% |
| llama.cpp Q8_0 | 8.292532 | +0.553% |
| llama.cpp Q4_K_M | 8.506707 | +3.150% |

The full nine-prompt logit matrix contains 153 distinct predictions per recipe,
repeated after reset. All outputs are finite and reset is exact. Against the
quantized HF oracle, INT8's worst RMSE/max error are `1.757848`/`10.635621`,
and INT4-MLP's are `1.488943`/`7.976877`. Both exceed the unchanged thresholds
`1e-3`/`1e-2`. A focused INT8 layer replay demonstrated amplification at a dynamic
quantization rounding boundary after a tiny incoming FP32 difference; it does
not establish the cause of every full-model outlier.

Prompt-128 capacity-4096 and chunk-32 variants each match all 17 baseline logit
arrays exactly for both recipes, including reset, fixed state and live KV.
The INT4 full numerical matrix used the preserved scalar-unpack binary. The
optimized unpack binary passed 30 native primitive invocations, exact prompt-17
and prompt-128 comparisons, and the complete held-out scoring run.

## Measurement contract

Intel Core i9-12900K, Linux x86-64. Four physical cores use affinity `0,2,4,6`;
the eight-core check uses `0,2,4,6,8,10,12,14`. Context capacity is 2048, prefill
chunks contain at most 128 tokens, and each request has 16 forced continuation
tokens. The lab uses `LAB_YNN_MATH=no_excess_precision`; llama.cpp uses its native
CPU build with FP32 KV and flash attention enabled. No GPU executes either path.

All variants consume identical token-ID fixtures. Each timing process has one
warmup and three measured requests. Prefix prefill consumes `prompt_tokens - 1`;
warm TTFT adds the last prompt-token decode. Decode rate is the reciprocal of
mean subsequent token latency, excluding step zero. Prefix/TTFT use the median
request. Setup and diagnostics are measured separately. No competing build,
reference scoring or benchmark runs during timing. The governor remains
`powersave`; frequency and filesystem cache state are not locked.

The lab's short prefill chunks still compute padded 128-row projections.
llama.cpp processes the actual row count. This matters especially at prompt 17.
The llama.cpp F32/Q8_0/Q4_K_M GGUFs come from the identical HF checkpoint, but
Q4_K_M is a different quantization recipe with different coefficient storage.

The diagnostic llama callback requests every node and can split execution or
inhibit fusion. Its operator times help locate costs but are not headline
latencies. Lab profile values are callback interval unions, not summed worker
CPU time. Memory-controller measurements cover separate FIFO-gated decode
windows; they are socket-wide, include background traffic and have no idle
subtraction.

The source HF revision is `851bf6e806efd8d0a36b00ddf55e13ccb7b8cd0a`.
llama.cpp is `cd0e36153b3f669d3e20ad2eb59ece6f5c8e23f5`.
The lab uses XNNPACK/YNNPACK `0a66ebb5817fce48df605451444dcfc27a5e4ee4`
and Slinky `a3eec6fcfe3093be04d6c3d7dcab7d4e70bdd0dc`, with existing local
backend patches retained. No new backend patch is part of this comparison.

## What the profiles identify

The [INT8 layer table](profiles/lab-int8/layer-stages.csv),
[INT4 layer table](profiles/lab-int4/layer-stages.csv),
[llama Q8 operator table](llama-q8-operator-profile.csv) and
[compact totals](bottlenecks.json) retain diagnostic measurements.

* The INT4 grouped-FC callback takes `519.32 ms` of a `598.91 ms` decode and
  `9868.81 ms` of a `10880.05 ms` prefill: about 87% and 91%, respectively.
  Integrating packed INT4 dot kernels and reducing group-rescale overhead are
  the main opportunities. The adapter is compiled at `-O1 -ffp-contract=off`;
  testing an optimized hot-loop build is another unmeasured candidate.
* INT8's recurrence callback takes `16.90 ms/decode` and `435.64 ms/prefill`,
  versus roughly `1.05 ms` and `63.58 ms` for llama.cpp Q8_0 `GATED_DELTA_NET`
  nodes. INT8 MLP is already competitive: lab MLP scope is `62.78 ms/decode`,
  while llama Q8 MLP matmuls total about `65.11 ms` in the diagnostic profile.
* Lab INT8 causal-conv scope takes `3.76 ms/decode` and `230.92 ms/prefill`.
  llama's `SSM_CONV` nodes take `0.17 ms` and `9.13 ms`, with concatenation and
  state handling attributed separately. Compare those surrounding operations
  before claiming an exact end-to-end saving.
* The INT4 plan also routes its INT8 embedding gather through the packed
  routing callback: about `30.33 ms` in the profiled prefill, versus `0.055 ms`
  for INT8's native gather. This is a smaller, distinct graph-routing cost.

These are targets for further validation, not measured speedups. The operator
profiles are separate from headline timing and can change execution behavior.

## Direct decode memory traffic

All six four-thread prompt-128 captures pass completion/window checks, with
three windows and 48 tokens per variant. Collector/native elapsed ratios range
from `0.999993` to `1.000014`. GB is decimal; counters are socket-wide and have
no idle subtraction.

| Runtime/profile | Measured GB/token | Effective GB/s |
| --- | ---: | ---: |
| Lab FP32 | 17.20680 | 32.42 |
| llama.cpp F32 | 17.03338 | 36.25 |
| Lab INT8 | 4.45154 | 31.55 |
| llama.cpp Q8_0 | 4.65364 | 36.03 |
| Lab INT4-MLP | 3.66535 | 6.12 |
| llama.cpp Q4_K_M | 2.88472 | 33.24 |

[Counter summaries](imc-summary.json) retain separate reads and writes;
[structural budgets](structural-byte-budget.json) are logical payload estimates,
not DRAM measurements. The grouped INT4 path moves fewer bytes but has much
greater execution overhead. GGUF accounting excludes 15 unused MTP tensors;
the execution inventory observed all 426 main-model tensors as inputs.

## Retained records

[Timing summary](timing-summary.csv) covers all prompt/thread/order cases;
[raw request timings](timing/timing-lab-int8-t4/timings.jsonl) retain individual
token observations. [Provenance](provenance.json) records model/binary hashes,
compiler/build settings and dependency identities. Command paths are portable
templates with named variables. Sparse CPU temperature/frequency samples are
in [host observations](host-observations.json); they are not continuous
monitoring or proof of fixed frequency.

The initial lab FP32/INT8/INT4 setup observations are 63.10/38.12/17.13 s, with
31.04/8.49/5.58 GiB peak RSS over complete requests. Mapped weights, separate
prepared phases, state and scratch contribute to RSS. Filesystem cache state is
uncontrolled, so these are not cold-start comparisons. Raw profiler captures,
model payloads and machine-local logs are outside this repository.

## Reproduction templates

The following are templates, with paths supplied by the caller. Use matching
parameter assets for the checked-in standalone plans. Quantized asset creation
is separate from this lab; the record does not include model payloads or a
standalone public quantization exporter.

```sh
cmake -S "$LAB_ROOT" -B "$LAB_BUILD" -G Ninja \
  -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=clang \
  -DCMAKE_CXX_COMPILER=clang++ -DLAB_DEPS="$BACKEND_ROOT" \
  -DLAB_ENABLE_TOKENIZERS=OFF
cmake --build "$LAB_BUILD" --target qwen3 --parallel 8

taskset -c 0,2,4,6 env LAB_YNN_MATH=no_excess_precision \
  "$LAB_BUILD/qwen3" --bundle_dir="$BUNDLE_DIR" \
  --parameter_dir="$PARAMETER_DIR" \
  --cases_file="$LAB_ROOT/models/qwen3_5_4b/fixtures/perf.tsv" \
  --output_dir="$FRESH_OUTPUT_DIR" --num_threads=4 \
  --cache_capacity=2048 --prefill_rows=128 \
  --warmup_runs=1 --measured_runs=3
```

The retained [standalone llama replay harness](llama_replay.cc) uses the same
TSV phase split and token accounting. It links against the pinned llama.cpp
CPU build. F32 GGUF conversion and Q8_0/Q4_K_M quantization use that checkout's
`convert_hf_to_gguf.py` and `llama-quantize`, respectively.

```sh
cmake -S "$LLAMA_ROOT" -B "$LLAMA_BUILD" -G Ninja \
  -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=clang \
  -DCMAKE_CXX_COMPILER=clang++ -DGGML_NATIVE=ON \
  -DGGML_CUDA=OFF -DGGML_HIP=OFF -DGGML_VULKAN=OFF
cmake --build "$LLAMA_BUILD" --target llama-quantize --parallel 8
clang++ -std=c++20 -O3 -I"$LLAMA_ROOT/include" \
  -I"$LLAMA_ROOT/ggml/include" llama_replay.cc \
  -L"$LLAMA_BUILD/bin" -Wl,-rpath,"$LLAMA_BUILD/bin" \
  -lllama -lggml -lggml-base -o "$REPLAY_BINARY"

taskset -c 0,2,4,6 "$REPLAY_BINARY" --model="$GGUF_MODEL" \
  --cases_file="$LAB_ROOT/models/qwen3_5_4b/fixtures/perf.tsv" \
  --output_dir="$FRESH_OUTPUT_DIR" --num_threads=4 \
  --cache_capacity=2048 --prefill_rows=128 \
  --warmup_runs=1 --measured_runs=3
```
