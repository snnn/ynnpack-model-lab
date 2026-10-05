# Safetensors FP32 arithmetic and integer-FC experiment

This experiment separates source storage from execution arithmetic. It compares
the existing BF16 safetensors profile with two additional profiles on an Intel
Core i9-12900K Linux host. Existing published-source and BF16 controls remain
available and retain their exact previous outputs.

The new profiles are experiments, not accuracy-qualified replacements. Removing
BF16 rounding alone did not improve overall agreement with the published-source
reference. Integer FC execution substantially changes performance; the warm
measurements below evaluate it separately from setup and diagnostic captures.

## What changed

All three safetensors profiles use the same audited checkpoint, original packed
integer codes, and the same INT8 KV policy. Local KV scales are unchanged; global
scales are divided by 16 under the existing published-compatible experiment.
The intended global scale convention remains unresolved.

| Label | Executable suffix | Floating boundaries | FC computation | Language head |
| --- | --- | --- | --- | --- |
| BF16 | `hf_bf16_int8_published_kv` | BF16, with FP32 RMSNorm/softmax internals | BF16 weight dequantization and simulation of static rounding/clipping | BF16; zero QAT scale leaves input unquantized |
| FP32 | `hf_fp32_int8_published_kv` | FP32 | FP32 weight dequantization and simulation of static rounding/clipping | FP32; input unquantized |
| Integer FC | `hf_static_int8_published_kv` | FP32 between quantized FCs | Static INT8 inputs/outputs, original per-channel integer weights and FP32 QAT scales | Dynamic INT8 activation quantization |
| Published control | `gemma4_e2b` | Existing FP32 graph | Existing static INT8 FCs | Existing dynamic INT8 activation quantization |

The FP32 profile changes embedding dequantization/scaling, normalization outputs,
residual arithmetic, RoPE, attention QK/PV arithmetic, softmax probabilities,
weight dequantization, FC arithmetic, and fake-quantization boundaries. RMSNorm
already computed its intermediates in FP32 in the BF16 profile. This is a broad
precision ablation, not an isolated RMSNorm change.

The integer variant additionally changes the FC algorithm and language-head
quantization policy. Its speed and numerical changes cannot all be attributed
to removing BF16 casts. The global PLE projection still uses the checkpoint's
floating weights; its published INT8 activation scales are absent from the
safetensors checkpoint. Normalization/scalar coefficients still originate from
BF16 storage. Promoting them to FP32 cannot recover the published model's
original FP32 coefficient values.

No checkpoint tensors were recalibrated or rewritten. Weight scale arrays used
by the integer-FC builder are hash-verified against the source manifest. The
original source and derived signed packed-code cache are shared by all three
safetensors profiles.
There is no new prepared-weight disk cache.

| Authored graph | BF16 | FP32 | Integer FC |
| --- | ---: | ---: | ---: |
| KV-only prefill operators | 6,839 | 3,133 | 1,853 |
| Full decode operators | 14,504 | 6,525 | 3,773 |

These are authored Core operation counts, not executed kernel counts. Backend
fusion and lowering determine the actual execution plan.

## Warm performance

| Prompt tokens | Profile | Warm TTFT, ms | Prefill tok/s | Decode tok/s |
| ---: | --- | ---: | ---: | ---: |
| 17 | Published-source YNNPACK | 47.5 | 699.8 | 41.16 |
| 17 | Safetensors BF16 | 903.2 | 82.6 | 1.41 |
| 17 | Safetensors FP32 | 1,102.1 | 139.6 | 1.03 |
| 17 | Safetensors integer FC | 50.4 | 677.2 | 37.66 |
| 128 | Published-source YNNPACK | 208.8 | 694.4 | 39.86 |
| 128 | Safetensors BF16 | 1,205.3 | 248.0 | 1.43 |
| 128 | Safetensors FP32 | 1,329.6 | 373.0 | 1.02 |
| 128 | Safetensors integer FC | 211.5 | 691.3 | 36.56 |
| 1,024 | Published-source YNNPACK | 1,721.1 | 604.4 | 36.24 |
| 1,024 | Safetensors BF16 | 5,188.8 | 228.6 | 1.40 |
| 1,024 | Safetensors FP32 | 3,999.0 | 340.4 | 1.01 |
| 1,024 | Safetensors integer FC | 1,746.9 | 595.9 | 33.84 |

At 1,024 tokens, integer-FC TTFT is 66.3% lower than BF16, prefill throughput is
2.61× higher, and decode throughput is 24.2× higher. Its TTFT is about 1.5% higher than the
published-source YNNPACK control, with 1.4% lower prefill throughput and 6.6%
lower decode throughput. FP32 floating arithmetic alone improves long-prompt TTFT, but
reduces decode speed and worsens short-prompt TTFT.

The two new variants use the same FP32 boundaries outside FCs. Their performance
difference reflects the change to quantized FC execution, including dynamic
quantization of the language head. This experiment does not apportion that gain
between the head and other FCs, or between individual kernels and backend
rewrites. No kernel-only profiling was collected here.

The measurements use four threads pinned to logical CPUs 0, 2, 4, and 6, four
distinct physical performance cores. Capacity is 2,048 and maximum prefill chunk
size is 128. Each prompt length has one warmup and three measured requests, each
with eight teacher-forced continuation tokens. The same prompt/continuation IDs
are used for every profile. Processes run sequentially; compilation and numerical
audits finish before timing. No traces or tensor dumps are enabled.

Warm TTFT is prefix execution plus the final prompt-token decode. Prefill tok/s
is `(prompt_tokens - 1) / prefix_seconds`; the final token is reserved for the
full decode graph. Decode tok/s uses the mean of the eight subsequent decode
steps in each request. Tables report medians of the three request measurements.
This is warm model execution, not process-start-to-first-token latency.

| Profile | Setup, s | Peak RSS after 1,024-token case, MiB |
| --- | ---: | ---: |
| Published-source YNNPACK | 12.05 | 1,690.2 |
| Safetensors BF16 | 61.32 | 3,046.4 |
| Safetensors FP32 | 38.28 | 2,998.9 |
| Safetensors integer FC | 29.38 | 3,625.6 |

The integer variant's peak is 579.2 MiB above BF16 and about 2.15× the
published-source control. It is a speed improvement, not a demonstrated memory
improvement.

Peak RSS is the process high-water mark, including setup, all earlier requests,
resident source mappings, derived mappings, prepared weights, KV, and scratch.
It is not a count of live activation tensors. The safetensors provider hashes
used source tensors, including complete embedding tables, touching those mmap
pages during setup. The published-source control has a different asset-loading
and verification path. Thus the RSS comparison is a real measurement of these
programs, but not an isolated activation-dtype comparison. No page eviction or
`madvise` policy was changed. Exact allocation-owner attribution of the new
profiles' RSS is outside this experiment.

These are x86-64 results. No ARM/I8MM/SME or phone speedup is inferred, and no new
comparison against the best packed-dynamic XNNPACK performance is claimed.

## Numerical comparison

The primary reference is the preserved, fully delegated published-source
LiteRT/XNNPACK static-QAT runner used in the preceding audit. This is not a new
run of the official upstream application. Its complete saved outputs are reused.
The published-source YNNPACK control is rerun and checked against its previous
capture. All numerical runs use four threads, without the performance affinity
restriction, and have one diagnostic request per case.

Prompts contain 1, 17, 128, 129, 130, 511, 512, 513, and 1,024 tokens. Two forced
continuations produce 27 logit vectors and 837 total logit/KV files per profile.
All captured outputs are finite.

| Candidate versus published-source XNNPACK | Greedy agreement | Minimum centered cosine | Maximum KL(reference → candidate) | Maximum absolute logit error |
| --- | ---: | ---: | ---: | ---: |
| Published-source YNNPACK | 27/27 | 0.961915 | 0.214622 | 9.45872 |
| Safetensors BF16 | 25/27 | 0.849099 | 2.587980 | 31.71364 |
| Safetensors FP32 | 23/27 | 0.814265 | 3.149650 | 31.67053 |
| Safetensors integer FC | 24/27 | 0.818130 | 3.335725 | 34.09106 |

The BOS-only case drives the worst KL values for the safetensors profiles.
Excluding all three outputs of that case, maximum KL is 0.336011 for BF16,
0.310898 for FP32, and 0.295560 for integer FC. That narrower statistic improves,
while greedy agreement and worst-case agreement do not. None of these small
teacher-forced fixtures establishes model-quality superiority.

FP32 disagreements occur at `p1.prefill`, `p129.prefill`,
`p511.decode_0001`, and `p512.decode_0001`. Integer-FC disagreements occur at
`p1.prefill`, `p128.decode_0001`, and `p129.prefill`.

Both rebuilt controls reproduce all 837 files of their respective previous
captures byte-for-byte. Reauthoring the BF16 control also produces byte-identical
prefill and decode builder code. Changes to the shared runner and author have
therefore preserved these recorded controls.
All four performance profiles also have stable greedy outputs across warmup and
three measured requests; their first three outputs match their correctness
capture for each of the three performance prompt lengths.

## Capacity, chunking, and persistent state

| Change within a new profile | FP32 | Integer FC |
| --- | --- | --- |
| Capacity 2,048 → 8,448, same 128-token chunks | 837/837 files identical | 837/837 files identical |
| Chunks 128 → 64, capacity 2,048 | 693/837 files identical; 27/27 greedy agreement | 750/837 files identical; 27/27 greedy agreement |
| Chunk comparison minimum centered cosine | 0.967139 | 0.965016 |
| Chunk comparison maximum KL | 0.198954 | 0.167812 |

The new profiles preserve the capacity-only invariant. Removing BF16 rounding
does not make different chunk schedules numerically identical: floating-point
reductions and quantized boundaries remain. These results do not reproduce the
previous BF16 probability-rounding localization for the new profiles; they show
that its removal is insufficient to eliminate chunk sensitivity.
The FP32 logit differences start in the 513-token case and also affect the
1,024-token case. The integer variant's changed logits are confined to the
1,024-token case in this fixture.

Both variants retain symbolic active-history bounds, real partial chunks,
KV-owner-only prefix execution, and INT8 cache writes. Runner checks enforce
9,216 newly appended bytes per token and zero history-view copy callbacks.
These counters exclude backend reads, packing, and dequantization of history.

## Independent arithmetic checks

Separate diagnostic binaries expose first-layer FC and attention values on the
BOS fixture. For both new profiles, all 93 final logit/KV files match the normal
executable, so these taps preserve the observed computation in this check.

For Q/K/V/output projections and all three MLP FCs:

- The integer variant's input codes and output codes match an independent
  NumPy integer-dot-and-scales calculation exactly for all seven FCs.
- The FP32 simulation's output quantization matches independent rounding and
  clipping of its observed dot outputs exactly for all seven FCs.
- The two new variants have identical first-layer FC input codes in these
  probes. Their later full-model differences cannot be inferred from this
  first-layer agreement.
- FP32 dot results differ from FP64 accumulation rounded to FP32 by at most
  0.000122071 in these probes. The FP64 oracle is diagnostic; it is not a claim
  that FP32 accumulation must match FP64 exactly.

Synthetic embedding tests cover packed INT2/INT4 codes, FP32 scales that change
under BF16 rounding, token lookup, and per-layer slicing. The existing BF16
rounding regression, quantized FC, state-view, and asset tests pass. Optional
Core IR tests check FP32 RMSNorm internals/results, unchanged BF16 source
coefficients, FP32 fake quantization, and the source-identity restriction on
published-compatible KV profiles.

## Reproduce

Use the asset preparation and separate HF dependency/build instructions in
`docs/HF_GEMMA4.md`. Build the new target names with CMake. The checked-in builders
and parameter recipes do not require Core IR at inference or build time.

```sh
cmake --build build-hf --parallel 8 --target \
  gemma4_e2b_hf_bf16_int8_published_kv \
  gemma4_e2b_hf_fp32_int8_published_kv \
  gemma4_e2b_hf_static_int8_published_kv gemma4_e2b

taskset -c "$BENCHMARK_CPUS" ./build-hf/gemma4_e2b_hf_static_int8_published_kv \
  --hf_model_dir=assets/hf-checkpoint \
  --asset_manifest=assets/gemma4_e2b_hf/manifest.json \
  --parameter_dir=assets/gemma4_e2b_hf/parameters \
  --cache_dir=assets/gemma4_e2b_hf/derived \
  --cases_file=models/gemma4_e2b_hf/fixtures/performance.tsv \
  --output_dir=out/hf-static-performance \
  --cache_capacity=2048 --prefill_rows=128 --num_threads=4 \
  --warmup_runs=1 --measured_runs=3
```

Select four suitable physical cores for `BENCHMARK_CPUS` on the actual host.
Repeat with the BF16 and FP32 suffixes, using fresh output directories. The
published control uses its existing bundle/parameter flags and the same fixture.
For numerical captures use `fixtures/correctness.tsv`, zero warmups, one measured
request, and `--dump_outputs`. Repeat at capacity 8,448 and chunk size 64, then
use `tools/compare_outputs.py`. Keep these captures separate from timing.

Small records alongside this report retain comparisons, raw timing/summary
records, test results, source/binary identities, and the first-layer oracle.
Large weights, traces, and logits remain outside Git.

The optional trace command manifest also requires `LAB_BUILD_VALUE_TRACES=ON`
and building `gemma4_e2b_hf_fp32_trace` and `gemma4_e2b_hf_static_trace`.
Create its `out/hf-fp32-experiment/bos.tsv` by selecting the `p1` row of the
correctness fixture. The `trace-plan-fp32` / `trace-plan-static` TSV/JSON plans
are generated by the separate private graph-authoring tools, selecting the
corresponding HF profile, source manifest/checkpoint, and layer-0 attention.
Only the standalone diagnostic runners and plan-consumption tools live here.
The first-layer oracle is `tools/audit_gemma4_fc_trace.py --hf-arithmetic fp32`,
with the integer variant as `--control-trace` and the floating variant as
`--hf-trace`. Diagnostic compilation and execution are separate from timing.

## Decision

Follow-up decision: **`hf_static_int8_published_kv` is the best current candidate
for further compiler and dynamism work.** BF16 source global PLE projection
weights are accepted. Cross-implementation bit identity is not a selection
criterion; this does not change the measured numerical differences or establish
task-quality equivalence. The original measurements and controls below remain
the evidence for that decision.

Keep the BF16 profile as the existing numerical control and retain both new
profiles with explicit names. The integer-FC variant is the useful performance
candidate for the next safetensors experiments. It has not established better
model quality or exact published-model compatibility. The FP32 floating variant
is an arithmetic ablation; it should not be selected merely because its
intermediate values have more precision.

Before treating the integer variant as a general replacement, evaluate a broader
quality workload and isolate the remaining source/graph differences, particularly
normalization coefficient precision, the global PLE projection, the head policy,
and the unresolved global KV scale convention. These are separate questions
from the demonstrated capacity and append behavior.
