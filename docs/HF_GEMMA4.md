# Gemma4 E2B from Hugging Face safetensors

This separate research path loads `google/gemma-4-E2B-it-qat-mobile-transformers`
directly. It preserves the checkpoint's packed weight codes and scale values.
The existing published-bundle E2B/E4B runners remain the comparison controls.

**Best current candidate: `hf_static_int8_published_kv`.** Use this profile for
new model-compiler, symbolic-shape, and dynamism experiments. Its integer FCs
recover competitive warm desktop performance while loading the safetensors
checkpoint directly. The checkpoint's BF16 global PLE projection is accepted;
the candidate promotes those values to FP32 for computation. Exact bitwise
agreement with another implementation is not a requirement. Keep finite-output,
logit/distribution, model-quality, and state-invariance checks, and preserve the
earlier profiles as controls. This selection does not establish equivalent task
quality, phone performance, or resolve the higher measured peak RSS.

The experiment compares the candidate with **`hf_bf16_int8_published_kv`** and
the FP32 floating variant, using the published-model LiteRT/XNNPACK
runner as a compatibility reference. The follow-up
[numerical audit](../results/hf_published_kv_audit_2026-10-02/README.md) identifies
early arithmetic differences and chunk-sensitive softmax rounding. Matching the
KV scales does not establish whole-model numerical equivalence.

The first implementation supports text only, batch size one, chunk sizes 1–128,
and capacities up to 32,768. It uses the same symbolic position/length contracts,
append-only KV writes, windowed views, and KV-owner-only prefix execution as the
other runners. It does not add MTP, image/audio execution, E4B safetensors, or
other model architectures.

The BF16 implementation has Linux x86-64 and Android measurements. The FP32 and
integer-FC variants currently have Linux x86-64 validation only. The recorded
full-model checks have greedy
disagreements and appreciable logit/KV differences. Do not treat these profiles
as accuracy-qualified replacements for the published-source runners. See the
measurement record in `results/hf_safetensors_2026-10-02/`.

## Numerical profiles

| Executable suffix | Activation/weight arithmetic | KV storage and scales |
| --- | --- | --- |
| `hf_bf16` | HF BF16 execution boundaries | BF16; checkpoint KV scales are unused, as in ordinary Transformers execution |
| `hf_bf16_int8_raw_kv` | Same BF16 arithmetic | INT8, symmetric, per-tensor; checkpoint KV scales unchanged |
| `hf_bf16_int8_published_kv` | Same BF16 arithmetic | INT8; local scales unchanged, global scales divided by 16 |
| `hf_fp32_int8_published_kv` | FP32 arithmetic, including floating simulation of static activation quantization and weight dequantization | Same published-compatible INT8 policy |
| `hf_static_int8_published_kv` | FP32 between quantized FCs; static INT8 FC inputs/outputs and dynamic INT8 language-head input | Same published-compatible INT8 policy |

The last policy is restricted to the audited checkpoint content. The scale
relationship is an observed compatibility rule, not a general Gemma formula or
an explanation of the original exporter's intent. It does not make the entire
model equivalent to the published bundle.

**TODO: Resolve the intended global KV quantization range.** In the audited E2B
checkpoint, K and V scales for cache-owner layers 4, 9, and 14 (zero-based) are
16× the published LiteRT-LM scales; local-attention scales match. Determine
whether this reflects a different quantization convention, compensating scaling,
or an export error. Compare both policies with otherwise matched arithmetic,
checking KV clipping, quantization error, and model outputs against LiteRT-LM or
our previous XNNPACK runners; Transformers is an optional reference. Until this
is resolved, dividing by 16 remains an explicit compatibility experiment in
`hf_bf16_int8_published_kv`, not an established correction to the checkpoint.

In the three BF16 profiles, quantized linear weights are interpreted as
`BF16(integer_codes * BF16(weight_scale))`. Calibrated FC inputs and outputs use
HF's BF16 static-range rounding/clipping arithmetic. A zero activation scale
disables that operation; in particular, the language head does **not** use the
published-source runner's dynamic activation quantization. The global PLE
projection and norm/scalar coefficients retain their source BF16 values. RMSNorm
and softmax accumulation use FP32 with explicit BF16 result boundaries.

These are BF16 reference semantics, not a claim of bit identity with PyTorch.
Reduction ordering, transcendental approximations, and quantization ties can
differ between backends. Static activation clipping/rounding can amplify small
upstream differences. Measure logits and KV contents, not only greedy tokens.

A BF16 boundary means rounding the result to the values representable in BF16.
For example, FP32 `1.004` rounds to BF16 `1.0078125`. Converting back to FP32
does not restore the discarded precision. Multiplying, rounding, then adding
can differ from doing both operations in FP32 and rounding only once. The
author preserves these boundaries because this path tests HF arithmetic.

| Property | Published-source control | HF BF16 profiles |
| --- | --- | --- |
| Calibrated FC computation | Explicit static INT8 activation graph | BF16 simulation of static rounding/clipping, with BF16 weight dequantization and dot products |
| Language head activation | Existing control's dynamic quantization | Zero SRQ scale disables quantization; BF16 input |
| Global per-layer embedding projection | Quantized INT8 source | Original BF16 source |
| Norm/scalar coefficients | Published source precision | Original BF16 source; FP32 accumulation where specified |
| KV | Published INT8 scales | BF16, original HF INT8 scales, or the audited published-scale policy |

Thus a performance comparison changes arithmetic as well as the source format.
Using safetensors does not inherently require BF16 execution; these initial
profiles deliberately expose that numerical contract before adding faster
lowerings with separately measured numerical differences.

## Direct storage and derived cache

`tools/safetensors.py` reads single files or indexed shards using bounded,
validated spans. It detects duplicate names, index disagreement, overlapping or
truncated payloads, invalid dimensions, and unsafe relative shard paths. It does
not import Torch, expand packed weights, or deserialize executable objects.

`prepare_gemma4_hf.py` validates the E2B configuration, derives logical packed
shapes, checks scales/shared-KV ownership, hashes tensors, and writes a manifest.
The manifest retains source names, dtypes, shapes, shard spans, hashes, packing,
and quantization policy. Its tensor-content identity also binds the builders to
their source. A different checkpoint requires reauthoring, even if its dimensions
match, because activation scales are constants in the generated graph.

The runtime maps each original shard once and validates hashes of used tensors.
Token and PLE embeddings remain in their original packed storage. Lookup unpacks
only requested rows and applies HF's BF16 scale and embedding multiplications.
Unused shared-layer K/V weights and multimodal weights are not prepared.

YNNPACK's signed INT2/INT4 encoding differs from HF's offset-binary encoding.
The resolver lazily creates only the requested recoded matrices, preserving
integer codes: XOR `0xAA` for INT2 or `0x88` for INT4. Cache names contain the
source payload hash, bit width, and conversion version. Temporary files are
renamed after a completed write; warm-cache contents are verified by reversing
the recode and checking the source hash. Corrupt/stale files fail explicitly.
This cache is separate from YNNPACK's internal packing/preparation; it is **not**
a cache of compiled graphs or prepared backend weights.

Source mappings count toward RSS when resident. Hash verification touches the
embedding pages during setup, so a fresh process may report a large peak RSS
even when inference reads only a small set of rows. Keep source residency,
derived packed storage, backend preparation/scratch, and KV allocation separate
when explaining memory measurements. There is no automatic `madvise` eviction.

## Prepare and build standalone profiles

The checked-in builders and small parameter recipes require no private compiler
package at build or runtime. Download only the config and tensor shard for this
audited single-file checkpoint; the index reader also supports future sharded
sources.

```sh
uvx hf download google/gemma-4-E2B-it-qat-mobile-transformers \
  config.json model.safetensors \
  --revision dd693ff40353f057ca5f07e945ad867f4afbf2ec \
  --local-dir assets/hf-checkpoint
python3 tools/prepare_gemma4_hf.py \
  --hf-model-dir assets/hf-checkpoint \
  --output assets/gemma4_e2b_hf/manifest.json

python3 tools/bootstrap.py --directory .deps/hf --hf-bf16
cmake -S . -B build-hf -G Ninja \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ \
  -DLAB_DEPS="$PWD/.deps/hf" -DLAB_BUILD_HF=ON
cmake --build build-hf --parallel 8
ctest --test-dir build-hf --output-on-failure
```

The BF16 path needs `patches/hf-ynnpack-bf16-rounding.patch`. The pinned backend's
fusion rules can bypass BF16 rounding despite `YNN_FLAG_NO_EXCESS_PRECISION`.
The fix restricts rewrites that remove those intermediate boundaries; it retains
lossless conversions and applicable fusion. The normal dependency tree and
normal build defaults do not adopt this experimental fix. CMake rejects an HF
build against the unpatched dependency tree. The BF16 regression test includes
a `tanh → BF16 → multiply` chain that fails on the original backend.

## Run and validate

```sh
./build-hf/gemma4_e2b_hf_bf16 \
  --hf_model_dir=assets/hf-checkpoint \
  --asset_manifest=assets/gemma4_e2b_hf/manifest.json \
  --parameter_dir=assets/gemma4_e2b_hf/parameters \
  --cache_dir=assets/gemma4_e2b_hf/derived \
  --cases_file=models/gemma4_e2b_hf/fixtures/correctness.tsv \
  --output_dir=out/hf-bf16-correctness \
  --cache_capacity=2048 --prefill_rows=128 --num_threads=4 \
  --warmup_runs=0 --measured_runs=1 --dump_outputs
```

Choose an executable suffix to select arithmetic and KV policy. All profiles
share the source files and derived packed cache. The asset preparer materializes
the union of their constant recipes into its parameter directory. A run writes
its profile, source identity, dimensions, and repetition settings to `run.json`.
BF16 KV dumps end in `.bf16`; INT8 KV dumps end in `.i8`; logits are FP32 dumps.
Only current tokens are appended: 18,432 bytes/token for BF16 KV or 9,216 for
INT8 KV. History-view copy bytes must stay zero.

The correctness fixture covers prompts 1/17/128/129/130/511/512/513/1024 and two
forced continuation tokens. Repeat at capacity 8,448, with smaller chunks, and
with repeated requests to check state behavior. Changing capacity should not
change logical attention bounds. A 130-token prompt exercises a short second
prefix chunk because the last token runs the full decode graph.

For an independent reference, use an environment containing Torch, NumPy,
safetensors, and Transformers with Gemma4 and `integrations.gemma_quant`:

```sh
python tools/hf_reference.py \
  --hf-model-dir assets/hf-checkpoint \
  --asset-manifest assets/gemma4_e2b_hf/manifest.json \
  --profile hf_bf16 \
  --cases-file models/gemma4_e2b_hf/fixtures/correctness.tsv \
  --output out/hf-reference
python tools/compare_outputs.py \
  --reference out/hf-reference --candidate out/hf-bf16-correctness \
  --output out/hf-comparison.json
```

The reference executes Transformers' text model with its quantized modules,
original tensors, BF16 arithmetic, and eager attention. It records package
versions. For INT8 profiles, it instruments cache updates with FP32
divide/nearest-even rounding/clamp and BF16 dequantization; ordinary Transformers
does not consume these KV scales. This is an optional diagnostic for the authored
BF16 arithmetic; compatibility with the published-model runners is the primary
comparison. Use `--logits-only` to compare INT8 results with the
unmodified BF16 reference and quantify the KV policy's additional difference.

The performance fixture uses prompts 17/128/1024 and eight forced continuation
tokens. Use one warmup and three measurements, with output/pipeline dumps off.
Report preparation separately from warm TTFT, `(prompt_tokens-1)/prefix_time`,
and subsequent decode tok/s. A BF16 HF run and a static INT8 published-source
run have different numerical contracts; their timing difference is not an
isolated safetensors-loader comparison.

Android uses the usual NDK CMake toolchain plus `LAB_DEPS` and `LAB_BUILD_HF`
above. Push the source shard, manifest, parameter directory, case file, and
selected executable. The phone needs only the standalone runner and its assets.
Check storage and available memory first and run one benchmark at a time per
device. Keep SME disabled for this experiment.
Run the device-side `safetensors_assets_test` from a writable working directory;
it creates and removes temporary fixture files in that directory.

## Reauthoring and extension points

Graph authors and compiler integration are maintained in a separate private
repository. The public lab contains the standalone builders and parameter
recipes, plus the source-mapping and asset-validation tools. See `AUTHORING.md`
for the artifact interface and validation requirements.

Pass an alternative parent builder directory through `LAB_HF_GENERATED` to build
experimental profiles. Keep builder/configuration headers, model metadata,
parameter recipes, and the runtime adapter synchronized. Compiler reports and
graph-authoring sources stay with the external compiler.

## FP32 arithmetic and integer-FC experiment

Safetensors storage does not determine execution precision. The FP32 variant
uses original packed integer codes and full FP32 scale values, computes embedding
dequantization/scaling in FP32, and retains FP32 norm outputs, residuals, RoPE,
attention scores, softmax probabilities, and attention outputs. RMSNorm already
had FP32 intermediates in the BF16 control; removing its output rounding is the
change here. BF16 source coefficients are promoted without restoring the precision
lost in their original storage. No source tensors are recalibrated or rewritten.

`hf_fp32_int8_published_kv` is a precision ablation: it still uses floating
matrix multiplications and floating simulation of static rounding/clipping.
It is not presented as an efficient integer implementation.

`hf_static_int8_published_kv` reuses the existing integer-FC lowering. Its
calibrated layers consume/produce INT8 with the original QAT scales and compact
per-channel INT2/INT4/INT8 weights. The language head uses dynamic INT8 activation
quantization, matching the published-source control. That head policy is an
additional numerical change; the floating profiles leave the zero-scale head
unquantized. The global per-layer embedding projection remains floating because
the checkpoint provides BF16 weights without the published projection's QAT
activation scales. BF16 norm/scalar coefficients also remain the source of their
promoted FP32 values. Exact published-model equivalence is therefore not assumed.

The integer variant retains per-channel weight scales verified against the
source manifest. Its checked-in parameter recipe materializes those constants
without expanding the weight archive. The public asset preparer handles this
step; regenerating the graph is part of the separate private authoring workflow.

The Transformers reference tool deliberately accepts only the three BF16
profiles. Use the published-source runners and comparisons of logits, KV,
capacity, and chunk size to evaluate the new arithmetic policies. Preserve the
BF16 profile as a control while assessing these candidates.

The [October 5 backend refresh](../results/2026-10-05/README.md) retimes the
preferred integer-FC, BF16, and FP32 profiles with the adopted dependencies and
identical HF token fixtures. It preserves the source and KV policies described
here.

Those HF timings predate the later
[packing correction](../results/2026-10-05-packing-fix/README.md). Its follow-up
measures the published-bundle controls; HF profiles have not been retimed with
that additional patch.

The [FP32/integer-FC measurement record](../results/hf_fp32_arithmetic_2026-10-02/README.md)
contains the desktop comparison, numerical audit, and capacity/chunk checks.
The integer variant is the preferred candidate and approaches the published-source
YNNPACK control's warm speed, but has higher peak RSS and does not improve overall
reference agreement. The existing numerical controls remain available.

When reusing assets prepared before these profiles existed, rerun the asset
preparer with a fresh manifest/parameter destination so it materializes the new
integer-FC scale constants. The source checkpoint and derived packed-code cache
can be reused.
Only headers/metadata/recipes belong in the repository; tensor payloads and
large diagnostic outputs remain external.

The generated C++ construction code uses small helper functions to limit C++
compiler cost. Runtime execution still uses one prepared prefill graph and one
prepared decode graph, with symbolic bounds preserved as Slinky expressions.

The safetensors reader and tensor provider are model-independent. HF tensor-name
mapping, quantization interpretation, BF16 arithmetic, and E2B validation live
in the Gemma author/assets code. Adding another model requires its architecture
and state semantics; a generic container reader alone does not provide linear
attention, different KV layouts, or other model behavior.
