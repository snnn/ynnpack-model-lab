# Gemma4 E4B

E4B uses the shared Gemma4 author and C++ runner with its own generated graphs
and hash-verified asset recipe. The executable is `gemma4_e4b`. The E2B executable
and emitted E2B builders retain their earlier model behavior.

## Prepare and run

Build with the root README's Linux or Android CMake commands. Both model targets
are built by default; `--target gemma4_e4b` can build just this executable.

```sh
uvx hf download litert-community/gemma-4-E4B-it-litert-lm \
  gemma-4-E4B-it.litertlm \
  --revision 1a64948b38efa40cd88a820e1e7cc1a6179ae05e \
  --local-dir assets/download-e4b
python3 tools/prepare_gemma4.py --variant e4b \
  --model assets/download-e4b/gemma-4-E4B-it.litertlm \
  --output assets/gemma4_e4b
./build/gemma4_e4b \
  --bundle_dir=assets/gemma4_e4b/bundle \
  --parameter_dir=assets/gemma4_e4b/parameters \
  --cases_file=models/gemma4_e4b/fixtures/performance.tsv \
  --output_dir=out/e4b-performance \
  --cache_capacity=2048 --num_threads=4 --prefill_rows=128 \
  --warmup_runs=1 --measured_runs=3
```

Source identity: 3,654,467,584 bytes, SHA-256
`f335f2bfd1b758dc6476db16c0f41854bd6237e2658d604cbe566bcefd00a7bc`.
The preparer verifies 2,143 files / 1,570 unique payloads. Both builders and all
426 generated parameter files reproduce exactly from the extracted assets.
There is no new quantization or calibration. Its format remains an artifact-specific extraction
recipe, not a general LiteRT-LM importer.

For Android, use `build-android/gemma4_e4b` and push the E4B `bundle`, `parameters`,
and `fixtures` directories. The launch flags are identical to the Linux example,
using on-device paths as in the root README. This prototype requires several GB
of resident memory; read the measured memory and platform limits below.

## Architecture differences

| Property | E2B | E4B |
| --- | ---: | ---: |
| Layers | 35 | 42 |
| Hidden width | 1536 | 2560 |
| Query / KV heads | 8 / 1 | 8 / 2 |
| Unique KV owners | 15 | 24 |
| Global attention period | 5 | 6 |
| Local / global head width | 256 / 512 | 256 / 512 |
| PLE storage | INT4 | INT2 |
| Transformer MLP weights | Mixed INT4 / INT2 | INT4 |
| KV bytes per capacity token | 9,216 | 28,672 |
| Authored prefill / decode operations | 1,831 / 3,790 | 3,227 / 5,209 |

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

## Validation

The shared refactor reproduces E2B's two builders byte for byte and all 372
existing desktop logits/KV dumps exactly. The independent state suite now has
198 successful stateful invocations, including 8 query heads / 2 KV heads under
local and global attention, with capacity strides and a double-precision oracle.
This suite passes on Linux, TECNO LJ9, and Pixel 8. Embedding tests now include
blockwise INT2 PLE as well as E2B's INT4 PLE and per-channel INT2 token embeddings.

The full E4B desktop checks use prompts 1, 8, 128, 129, 130, 511, 512, 513, and
1024 with two forced continuation tokens. All 27 logit vectors are finite.
The same full set also completes on TECNO after the stack workaround below.
All 2,619 logit/KV files are identical at capacities 2048 and 8448. Every call
checks 28,672 fresh KV bytes written per token and zero view-copy callbacks.

Against the existing Core-authored LiteRT/XNNPACK static-QAT E4B graph, 26/27
argmax choices agree. Minimum centered logit cosine is 0.9305 and maximum
reference-to-candidate KL is 0.4265. The first-token KV dumps agree exactly;
later differences grow substantially through quantized layers. These are not
ULP-only differences and do not certify equivalent task quality. The comparison
reference is our earlier authored graph, not an official application benchmark.

For a repeatable comparison of diagnostic dumps:

```sh
uv run --no-project --with numpy python tools/compare_outputs.py \
  --reference out/reference-dumps --candidate out/candidate-dumps \
  --output out/comparison.json
```

The optional NumPy dependency runs in a separate uv environment. The tool
requires matching dump names/layouts and reports logits separately from
KV code differences. Teacher-forced agreement does not measure free-generation
quality. Exact capacity consistency is a different check from cross-backend
numerical agreement.

Across YNNPACK's desktop and TECNO implementations, 25/27 argmax choices agree;
minimum centered cosine is 0.9375 and maximum KL is 0.3139. The two mismatches
occur in forced continuations of the 129- and 513-token prompts. All outputs
are finite. These results establish execution and state-update coverage, while
leaving cross-platform numerical consistency and task-level quality open.

## Android preparation stack overflow

The first TECNO run crashed while preparing E4B decode. Android's crash report
identified a stack pointer outside the stack mapping; the environment reported
an 8-MiB stack limit. Repeated frames resolve to Slinky's recursive simplifier:

```
simplifier::mutate_with_buffer
simplifier::visit(make_buffer const*)
stmt::accept(stmt_visitor*)
simplifier::mutate_and_set_result
```

The E4B executable now prepares and runs on an explicit thread with a 64-MiB
stack reservation. Stack pages become resident only when touched. The original
main thread waits; `--num_threads=4` still means four compute workers including
the execution thread. E2B keeps its prior execution-thread behavior.

This is a practical experiment workaround, not a fix for recursive traversal
depth in Slinky. An upstream improvement would bound traversal stack usage or
use an iterative traversal for deeply nested buffer scopes. This failure is
separate from the large weight-packing footprint.

## Measurements

See `results/e4b_2026-10-02/` for raw summaries, capacity consistency, and
cross-backend numerical records. Warm timing excludes preparation, uses real
chunks up to 128, one warmup and three measured requests, and 16 forced decode
tokens per request. Desktop uses an i9-12900K, four physical P cores, affinity
mask `55`; TECNO uses four big cores, mask `f0`. No SME/SME2 paths are enabled.

Capacity is 2048 throughout this timing table. TTFT includes processing the last
prompt token through the full decode graph. Prefill throughput counts the other
`P - 1` prompt tokens divided by their prefix execution time. TTFT and prefill
throughput are medians of three requests; decode throughput is the reciprocal
of the mean latency over their 48 continuation steps. Peak RSS is the process
high-water mark, including preparation and all earlier cases in that process.

| Device / engine | Prompt tokens | TTFT, ms | Prefill, tok/s | Decode, tok/s | Peak RSS, MiB |
| --- | ---: | ---: | ---: | ---: | ---: |
| Linux / YNNPACK | 17 | 152.6 | 187.6 | 14.88 | 4544 |
| Linux / YNNPACK | 128 | 752.4 | 186.1 | 14.40 | 4553 |
| Linux / YNNPACK | 1024 | 6018.7 | 172.3 | 12.58 | 4692 |
| Linux / LiteRT-XNNPACK static control | 17 | 139.6 | 208.9 | 15.85 | 2391 |
| Linux / LiteRT-XNNPACK static control | 128 | 484.0 | 302.4 | 15.58 | 2454 |
| Linux / LiteRT-XNNPACK static control | 1024 | 3650.5 | 285.5 | 14.61 | 2579 |
| TECNO LJ9 / YNNPACK | 17 | 257.5 | 99.7 | 11.07 | 4415 |
| TECNO LJ9 / YNNPACK | 128 | 1624.9 | 83.3 | 9.46 | 4476 |
| TECNO LJ9 / YNNPACK | 1024 | 14446.7 | 71.5 | 7.07 | 4526 |

YNNPACK setup takes 35.49 seconds on Linux and 124.87 seconds on TECNO.
The Linux LiteRT/XNNPACK control loads and prepares in 0.289 seconds with its
existing packed-weight cache. The measured binaries use Clang 22.1.8 on Linux
and NDK r28b on Android, Release CMake configuration for the standalone runner.
The harness uses `-O1`; YNNPACK kernel targets use their upstream `-O2` flags.

The LiteRT/XNNPACK reference loads an existing packed-weight cache. YNNPACK has
no such cache and independently packs its two phase graphs. Report setup and
RSS separately from warm execution. These static-QAT controls do not implement
the separate packed-dynamic W4 activation optimization.

The Linux YNNPACK prototype is slower than this static control, including after
setup is excluded: at 1024 tokens it achieves 60% of the control's prefill
throughput and 86% of its decode throughput. It also retains substantially more
resident memory. There is no matched E4B LiteRT/XNNPACK phone measurement in this
standalone extraction, so the TECNO rows cannot establish a mobile speedup.
Preparation depth, repeated weight packing, memory ownership, and kernel or
schedule selection remain optimization targets. These results do not show that
symbolic state alone improves full-model speed.

Pixel full-model execution was skipped: its observed available memory was about
3.7 GiB, below the roughly 4.5-GiB process footprint already seen on desktop.
Only the small state/GQA tests were run there. This is a practical limit of the
current prototype, not a claim that E4B intrinsically needs that much memory.
