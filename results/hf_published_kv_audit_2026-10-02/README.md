# Published-KV safetensors numerical audit

The focus is `hf_bf16_int8_published_kv`, compared with the preserved published
model implementation. This audit uses the existing **fully delegated
LiteRT/XNNPACK static-QAT runner** as the external reference and the
published-source YNNPACK runner as a bridge. It does not use Transformers as
the acceptance criterion, and it is not a new upstream LiteRT-LM benchmark.

The HF profile agrees on 25/27 next-token choices with both controls, but its
logits are not numerically equivalent. Differences start before the first
attention operation. Independent first-layer calculations support the intended
arithmetic rather than a weight-unpacking error. A separate chunk-size trace
identifies softmax reduction/rounding sensitivity with correctly aligned
attention windows. No new model execution bug was confirmed by these checks.

This is a numerical investigation on Linux x86-64, not a performance or model
quality evaluation. Normal runners, generated builders, dependency pins, and
the experimental KV-scale policy were not replaced.

## Matched whole-model comparisons

Intel Core i9-12900K, four threads, capacity 2048, real query rows without
padding. Nine prompts have lengths 1/17/128/129/130/511/512/513/1024. Each produces
first logits and two teacher-forced continuation outputs, for 27 full logit
vectors. All implementations receive exactly the same token IDs. The checked-in
TSV omits the comment line because the preserved XNNPACK runner rejects comments.
There is no change to the token sequences.

The controls use published integer FC arithmetic and FP32 floating boundaries.
The candidate uses BF16 arithmetic and BF16 simulation of static activation
quantization, with the published INT8 KV scales. These are intentional arithmetic
differences; this is not a comparison of file containers alone.

| Reference → candidate | Token agreement | Minimum centered logit cosine | Maximum KL | Maximum absolute logit difference |
| --- | ---: | ---: | ---: | ---: |
| LiteRT/XNNPACK → published-source YNNPACK | 27/27 | 0.961915 | 0.214622 | 9.458721 |
| LiteRT/XNNPACK → HF published-KV | 25/27 | 0.849099 | 2.587980 | 31.713638 |
| Published-source YNNPACK → HF published-KV | 25/27 | 0.850109 | 1.680465 | 31.090292 |

The HF disagreements are the first outputs for the one-token BOS prompt and
the 129-token prompt. The worst logit difference and KL occur on the BOS case.
That case has no prefix chunks or long history, so its difference cannot be
caused by chunk boundaries or sliding-window handling. It is also a special
edge case, not a representative chat-quality score.

The bridge control already has numerical differences from XNNPACK despite
matching all 27 token choices. KV-code disagreement rates are also substantial
between the controls. Greedy agreement and aggregate KV-code counts alone are
insufficient acceptance criteria for either path.

## Source tensor audit

The source audit reads actual payloads from both sources:

| Check | Result |
| --- | --- |
| 278 shared packed integer tensors, after offset-binary/sign recoding | Every byte agrees |
| Their 278 weight-scale tensors | Every scale agrees |
| 550 static activation input/output scales | Every scale agrees |
| 262 BF16 floating coefficient tensors | Exactly equal to published FP32 coefficients rounded to BF16 |
| Global PLE projection, 13,762,560 elements | Exactly BF16-rounded dequantization of the published INT8 weights |
| Requantize that projection using the published per-channel scales | Every original INT8 code recovered |

The global projection is therefore not an unrelated set of learned weights.
Its representation and execution differ: the HF graph runs a BF16 projection
without the published projection's integer activation/output boundaries.
Recovering the original codes in this audit required the published scales;
this does not establish a safetensors-only reconstruction recipe for them.

Global K/V scales for owners 4/9/14 are exactly 16 times the published scales.
Local-owner scales match. The candidate explicitly divides global scales by 16.
Which convention represents the intended range remains an open TODO; this audit
does not declare the original checkpoint scales incorrect.

## First divergence: embeddings and layer 0

Diagnostic graph outputs expose named norm/FC boundaries. On the BOS case,
both instrumented runners reproduce all 93 normal logit/KV files byte-for-byte.
The taps therefore did not change the observed final computation for this case.

Differences are already present in the scaled token embedding: maximum absolute
difference 0.0084603, RMS difference 0.0031927. The first RMSNorm output differs
by RMS 0.0313347, with cosine 0.999997. This follows the explicitly different
embedding/scale/coefficient rounding and normalization boundaries.

At the first Q/K/V FC inputs, 62 of 1536 quantized activation codes differ;
each differs by one code. Both paths use the same source QAT scale, but the HF
path rounds that scale and the division to BF16 before integer rounding. The
static path quantizes its FP32 input directly. Small differences can therefore
cross integer rounding thresholds before any KV update.

At the first saved cache owner, K differs in 15/256 codes and V in 21/256 codes,
with maximum difference two codes. Those are local-attention caches whose
source scales already match; the unresolved global 16× convention cannot
explain this first divergence.

Independent NumPy arithmetic checked layer 0's Q/K/V/O projections and all
three MLP FCs:

- All seven static input quantizations and all seven integer FC output-code
  predictions match the observed published-source runner exactly.
- All seven BF16 output fake-quantization calculations match observed outputs
  exactly when starting from the observed BF16 dot result.
- Six BF16 dots match FP64 accumulation followed by FP32/BF16 conversion exactly.
  Gate projection has one differing element, by one BF16 step (0.0009765625).
  An FP64 accumulation oracle is diagnostic; it is not the required contract
  for an FP32-accumulating backend kernel.

These checks explain the early difference as different arithmetic, without
requiring an importer or FC bug. They do not independently validate every
operation in all 35 layers or prove that all final-logit drift is acceptable.

### Follow-up: separating embedding, coefficient, and output rounding

An independent NumPy ablation now reproduces the scaled embeddings and first
RMSNorm outputs of both runners exactly for all three steps of the BOS fixture
(input token IDs 2, 669, and 160144). The following result sharpens the earlier
description: the first visible difference is in the embedding, but that
difference does **not** explain the first RMSNorm output difference in these
three cases.

For the BOS embedding, the shared FP32 row scale is approximately 0.033181842.
The HF execution rounds it to BF16, 0.033203125. After multiplication by
`sqrt(1536)` and the HF output rounding, an integer code of +1 becomes:

| Path | Scaled embedding value |
| --- | ---: |
| Published FP32 arithmetic | 1.3004574 |
| HF BF16 arithmetic | 1.3046875 |

This INT2 embedding has codes -2/-1/0/+1 and one scale for the entire token row.
For this row the change is a common factor, approximately 1.0032529, rather than
a change in vector direction. RMSNorm approximately cancels a common positive
factor: `a*x / sqrt(mean((a*x)^2)) = x / sqrt(mean(x^2))` when epsilon is ignored.
Finite precision and epsilon can prevent exact cancellation in general. In all
three measured rows, replacing only the embedding while retaining the published
coefficients and FP32 norm output reproduces the original norm output exactly.
The embedding also feeds residual/projection paths, so this does not imply that
embedding rounding is irrelevant to the complete model.

Both authors perform the RMS calculation in FP32. The HF path additionally uses
BF16-stored coefficients (promoted to FP32 for multiplication), and rounds the
norm output to BF16. The published path keeps its original FP32 coefficients
and FP32 output. On BOS, changing one component at a time gives:

| Variant relative to published arithmetic | RMS output error | Maximum output error |
| --- | ---: | ---: |
| Change only embedding to the HF values | 0 | 0 |
| Round only norm coefficients to BF16 | 0.022772 | 0.321098 |
| Round only norm output to BF16 | 0.020155 | 0.208542 |
| HF embedding + BF16 coefficients + BF16 output | 0.031335 | 0.451706 |

The last row is exactly equal to the captured HF norm output. These errors are
not additive. At the worst coordinate, the source coefficient changes from
74.7576523 to 75.0, and the final norm output changes from 99.048294 to 99.5.
Across the vector, RMS error is about 0.246% of the published output RMS.
No difference in the RMS formula or backend kernel is needed to explain these
three observed norm outputs.

Static activation quantization then exposes rounding thresholds. On BOS, using
the HF norm values with the original FP32 Q/K/V input scale changes 44/1536
integer codes. The HF path also rounds that scale from approximately 0.60880345
to 0.609375 and rounds the division result to BF16 before integer rounding.
With all those steps, 62/1536 codes differ, each by one. Intermediate changes
can undo earlier changes; the counts should not be summed as independent errors.

There are two distinct choices for a future execution variant. BF16 coefficient
precision is already part of the safetensors source; promoting 75.0 to FP32
cannot recover 74.7576523. In contrast, forcing embedding/activation scales,
division results, and norm outputs through BF16 is a choice of this experimental
author. Safetensors loading does not require those execution boundaries. A
variant that retains FP32 intermediates can be evaluated separately without
changing the original integer codes or the selected INT8 KV policy.

`audit_gemma4_embedding_norm.py` reproduces this ablation from the published
bundle and existing trace directories. The three `*-embedding-norm-ablation.json`
records retain component errors and exact trace agreement. No inference graph,
default, or benchmark result changed in this follow-up.

## Chunk-size sensitivity and its mechanism

| 128-row chunks → 64-row chunks | Token agreement | Identical dump files | Minimum centered logit cosine | Maximum KL |
| --- | ---: | ---: | ---: | ---: |
| HF published-KV | 27/27 | 798/837 | 0.969799 | 0.071096 |
| Published-source YNNPACK | 26/27 | 792/837 | 0.963551 | 0.163710 |

For the HF profile, all differences in this fixture occur in the 1024-token
case. The smaller cases, including partial chunks and the 512-token window
crossing, are byte-identical. The control's changed token choice is the first
forced continuation output for the 1024-token case. Chunk sensitivity therefore
predates the new importer; its magnitude must be measured, not presumed absent.

The full prefix trace covers layers 0–14. The earliest layer with a differing
observed boundary is layer 1's attention context at token position 634
(zero-based): seven of approximately 2.1 million context elements differ.
Subsequent FC quantization absorbs that particular difference. A difference at
layer 8, token 766, survives quantization and propagates into later layers and
KV state. Other later differences are retained in the complete stage report.

Two focused attention probes locate the source:

| Property | Layer 1, token 634 | Layer 8, token 766 |
| --- | --- | --- |
| Query, valid K/V, and valid scores | Identical across chunks | Identical across chunks |
| Valid key interval | `[123,635)` in both | `[255,767)` in both |
| Active chunk-wide key extents | 639 versus 575 | 639 versus 575 |
| Nonzero probabilities outside the valid interval | Zero in both | Zero in both |
| Maximum FP32 probability difference | 1.49e-8 | 2.98e-8 |
| BF16 probabilities differing | 5 | 1 |
| BF16 attention context elements differing | 7 | 10 |
| Maximum context difference | 0.001953125 | 0.001953125 |

Both chunks cover the same 512 valid keys for the probed query. Their wider
chunk-wide intervals include different counts of correctly masked positions.
The first measured difference is in FP32 softmax, consistent with a changed
reduction order for a different extent. The BF16 cast places a few probabilities
on opposite sides of rounding thresholds. Later static quantization can absorb
or amplify the resulting context difference.

For both probes, the 128-row result's BF16 probabilities match the FP64 softmax
oracle (converted through FP32 to BF16); the 64-row result differs in exactly
the five/one probabilities above.
That does not make 128 universally preferable: this is a small set of threshold
cases, and FP32 reductions need not match FP64 rounding exactly.

Every masked score outside the valid interval is negative infinity in these
probes. Q/K/V alignment and valid score equality rule out a wrong logical window
or cache slice for these cases. The traces reproduce all 93 normal logit/KV files
for each long-prompt configuration exactly, including the original differences.
This supports numerical shape sensitivity, not a demonstrated state-update bug.

## Validation, interpretation, and remaining work

Eight CTest entries and ten Core IR authoring tests pass. The new diagnostic test
checks BF16 snapshots with dynamic row counts and singleton/broadcast dimensions.
Python audit tools pass lint. All audited logits are finite. Previous
capacity-only checks remain recorded separately; they were not remeasured here.

The previously identified BF16 fusion bug is already fixed in the isolated HF
dependency tree used here. This audit found no additional confirmed numerical
bug requiring a default change. The global KV scale range remains unresolved.

The profile is a useful experimental focus, but it is not yet a numerically
qualified replacement for the published path. Next useful work is a broader
quality evaluation and controlled arithmetic variants: for example, reuse the
published integer FC computation while loading shared codes/scales directly,
or measure the effect of keeping attention probabilities in FP32. Such variants
must be labeled; neither is silently equivalent to the current BF16 profile.

The early-stage and focused-attention oracles are not exhaustive full-model
proofs. This pass did not rerun phone correctness, free generation, or performance.

## Reproduction

Use the existing HF preparation/build instructions in `docs/HF_GEMMA4.md`.
The optional trace executables share the normal builders and asset providers:

```sh
cmake -S . -B build-hf -DLAB_DEPS="$PWD/.deps/hf" \
  -DLAB_BUILD_HF=ON -DLAB_BUILD_VALUE_TRACES=ON
cmake --build build-hf --target gemma4_e2b_trace gemma4_e2b_hf_trace value_trace_test --parallel 2
ctest --test-dir build-hf -R value_trace --output-on-failure
```

Create `out/trace-plan-published` and `out/trace-plan-hf` with the separate
private graph-authoring tools. The plans are standalone TSV/JSON data.

Run `gemma4_e2b_trace` with the normal published-runner arguments plus
`--trace_plan=out/trace-plan-published`, or `gemma4_e2b_hf_trace` with the normal
HF arguments plus `--trace_plan=out/trace-plan-hf`. Use this directory's
`correctness.tsv`, capacity 2048, four threads, zero warmups, one repetition,
`--dump_outputs`, and a fresh output directory. Compare normal outputs first
with `tools/compare_outputs.py`; then inspect matching invocation directories
with `tools/compare_value_traces.py`.

For the full prefix trace, generate a plan with `--layers
0,1,2,3,4,5,6,7,8,9,10,11,12,13,14` and run only the `p1024` TSV row at chunk sizes
128 and 64. `compare_value_traces.py --prefill-sequence` aligns the chunks by
absolute token position. For focused attention, generate another plan with
`--layers 1,8 --attention --max-context 2048` and use
`audit_attention_trace.py --layer 1 --token 634` or `--layer 8 --token 766`.

The source and FC checks are provided by `audit_gemma4_sources.py` and
`audit_gemma4_fc_trace.py`; each tool documents its arguments with `--help`.
These analysis tools need NumPy. No Transformers execution is required.

Trace files can be several GB and remain outside Git. Exposing intermediates
may inhibit fusion, so always verify final-output agreement with an ordinary run
before interpreting traces. Trace timings are not benchmark results.

The external LiteRT/XNNPACK control executable and model are preserved artifacts
from the earlier experiment; this repository does not build them. Their hashes,
the tested HF/control binaries, and the fixture identity are in `environment.json`.
The small JSON records retain full per-output and per-stage numerical evidence.
