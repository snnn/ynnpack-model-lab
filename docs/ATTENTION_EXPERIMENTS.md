# Decode attention experiments

The lab provides four explicit decode attention policies. They keep the published
weight codes, FC activation policy, INT8 KV storage/scales, live history and masks.
Prefill always uses the existing control graph. The candidates are experiments;
numerical validation and performance measurements determine whether to adopt one.

| Profile | Query-head layout within each KV head | QK / PV arithmetic |
| --- | --- | --- |
| `fp32_batch` | Heads in the batch axis, one matrix row | FP32 Q/P and dequantized FP32 K/V; existing control |
| `fp32_rows` | Heads in matrix rows | Same FP32 policy, potentially different kernel/reduction order |
| `int8_batch` | Heads in the batch axis, one matrix row | Dynamically quantized Q/P, unchanged INT8 K/V, INT32 accumulation |
| `int8_rows` | Heads in matrix rows | Same integer policy with grouped rows |

For integer attention, each Q or probability row gets an asymmetric INT8 scale
and zero point from its live contraction range, including zero. The dot corrects
that zero point and scales its accumulator to FP32. Masks and softmax stay FP32.
The x86 backend may represent the LHS as UINT8 with an equivalent zero point.
Cache values include -128; these are never declared symmetric constant weights
restricted to [-127,127]. There is no full-history FP32 KV expansion in this path.
Packing, integer column sums and FP32 result conversion still perform work.

Integer attention changes the numerical computation. The native Tensor
API/XNNPACK control retains FP32 Q/P and mixed FP32/INT8 attention kernels; it is
not this dynamically quantized policy. Its `qp8_all` experiment changes eligible
prefill FCs only, leaving decode FCs and attention unchanged.

The [PC study](../results/2026-10-09-attention-profiles/README.md) retains the
completed numerical and performance investigation using the earlier C++ runner.
Remaining ARM, current-loader and equivalent-arithmetic work is tracked in
[open work](worklogs/README.md).

## Full-model candidates

Build the opt-in standalone E2B/E4B candidates with the normal public toolchain:

```sh
cmake -S . -B build-attention -G Ninja \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ \
  -DLAB_BUILD_ATTENTION_BENCHMARK=ON
cmake --build build-attention --parallel 8
ctest --test-dir build-attention --output-on-failure
```

Use `gemma4_e2b` or `gemma4_e4b` and select the profile directory at runtime.
The directories are `models/gemma4_VARIANT/attention/PROFILE`; replace `e2b`
with `e4b` for the two-KV-head workload. No per-profile build is required.

Use the control's existing assets and parameters:

```sh
./build-attention/gemma4_e2b \
  --graph_dir=models/gemma4_e2b/attention/int8_rows \
  --bundle_dir=assets/gemma4_e2b/bundle \
  --parameter_dir=assets/gemma4_e2b/parameters \
  --cases_file=models/gemma4_e2b/fixtures/performance.tsv \
  --output_dir=out/attention-int8-rows-c2048-t4 \
  --cache_capacity=2048 --num_threads=4 --prefill_rows=128 \
  --warmup_runs=1 --measured_runs=3
```

`run.json` labels decode and prefill attention separately. Checked-in candidates
contain both phase plans, with prefill identical to the control plan.
They need no private compiler or additional model payloads. Their parameter
payloads match the existing prepared assets. Generation and policy authoring stay
in the private companion; see [AUTHORING.md](AUTHORING.md).

Grouped rows are restored to query-head layout before masking, so heads are never
interpreted as successive query positions. E4B selects each KV head without
compacting its capacity-backed stride. Both phases still reuse their prepared
graphs and append only newly produced K/V. These policies do not introduce a
whole-graph copy for each history length or an online-softmax implementation.

Use separate `--dump_outputs` runs and
`tools/compare_outputs.py --reference=... --candidate=... --output=...` to compare
finite logits, error, centered cosine, KL, greedy agreement and KV codes.
Grouping can change FP32 accumulation and propagate through QAT thresholds;
passing an isolated attention test does not guarantee full-model equivalence.
Do not silently relax a capacity-only exact-match check or present teacher-forced
agreement as a generation-quality result. Collect latency with dumps and
`--profile_execution` disabled, then profile a separate invocation.

## Weights-free harness

`attention_decode_bench` isolates the same arithmetic/layout choices with eight
query heads, one or two KV heads, widths 256/512, and one or two consumers sharing
history. Its deterministic inputs include the full INT8 range, a zero query row,
and a positive-only query row. A capacity-strided live view supplies K/V.
Bank seeds use a fixed stride of 16,384, independent of physical capacity, so
capacity comparisons retain identical logical inputs. `--bank-seed-stride=8448`
reproduces the retained probability-rounding boundary case.

```sh
./build-attention/attention_decode_bench \
  --arithmetic=int8 --layout=rows --width=512 --kv-heads=2 \
  --capacity=8448 --histories=1,17,128,511,512,513,1024,17 \
  --window=512 --threads=4 --consumers=2 --iterations=10 --repetitions=3
```

Use `--arithmetic=fp32|int8` and `--layout=batch|rows` independently. Window zero
means global attention; 512 is the model's local window. Histories must be
nonempty and no larger than capacity. Changing history, decreasing it and
repeating it reuse one prepared graph. Existing state tests cover empty history,
append ordering, reset and capacity rejection; this harness reads history only.

FP32 cases check all outputs against an independent scalar attention calculation
with `2e-5 + 2e-5 * abs(reference)` tolerance. Integer cases use a separate
inspection graph for correctness: independently check QK and softmax, then check
PV quantization, zero-point correction and integer accumulation using the actual
FP32 probability row. Compare its final output with the unobserved timed graph
using the same tolerance. A tiny floating softmax difference can cross an INT8
half-code boundary, so assuming identical probability codes from a double-precision
softmax is not a valid end-to-end oracle. Inspection never runs inside a timed
repetition and does not expose outputs on the timed graph.

The oracle includes asymmetric zero-point correction and full-range cache codes,
and separately reports error against FP32 attention. Its tolerance verifies the
chosen arithmetic; it is not a model-quality acceptance threshold. History-view
copy bytes must remain zero in both graphs. The adapter describes dense owner
strides explicitly so integer column sums and packing can alias the live view.

JSON lines report `arithmetic`, `layout`, geometry, setup time, `graph_ms`,
`max_abs_error` against the chosen arithmetic policy, and
`max_abs_error_vs_fp32`. Integer checks also report QK, probability and
inspection-output errors. Setup time covers compilation of the timed graph,
excluding the separate inspection graph. Each repetition averages the invocations,
including scalar binding and adapter preflight. Three repetitions within a
process are not three independent trials. This is prepared-graph time, not
kernel-only or full-model decode latency. Query values include the attention
scale; softmax beta is one.

For a separate diagnostic invocation, add `--profile=profile.jsonl` and
`--pipeline=pipeline.txt`. Callback profiles identify conversion, dots, packing
and other scheduled work. Normalize work/counts by `iterations` per step.
Worker work is not critical-path wall time; callback dot names do not identify
microkernels. Collect actual selected kernels separately with native sampling.
Scratch hooks are off. Profiled results are labeled diagnostic and excluded from
latency comparisons.

Compare identical backend pins, build flags, inputs, capacity, history, window,
threads and affinity. Alternate process order and use fresh output directories;
follow [BENCHMARKING.md](BENCHMARKING.md) for thermal/frequency observations.
Run one benchmark per device and no competing builds on the benchmark host.
The harness controls neither clocks nor cooldown. Retain small useful records
with portable commands, binary/model identities and the limitations of each
comparison.
