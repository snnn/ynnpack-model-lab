<!-- Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0 -->

# October 8 standalone builder refresh

Regenerate all seven retained profiles and nine state fixtures, and synchronize
the standalone runtime helpers. Preserve `target_views`, global layout, decode
singleton-transpose cleanup, source identities, weight codes, activation/KV
policies, and all existing operation/value counts.

The semantic construction sequence is identical for all 14 phase graphs after
excluding diagnostic label calls. All 3,878 newly emitted parameter payloads
match the previous artifacts. E4B and the five HF profiles gain the operation
labels already present in E2B. Named layer/attention/SDPA/MLP helpers still build
one graph per phase. Labels count toward bounded helper/source sizes, increasing
the number of source files from 155 to 302; source files contain at most 2,048
helper-definition lines plus six wrapper/include lines. Construction functions
remain separate from model execution and introduce no backend graph boundaries.

The runtime now includes standalone FP32 SDPA and packed weight-only linear
capability helpers. Its kernel selector accepts the current learned-cost-model
API and the earlier shape-only API. The retained models use their existing
attention/FC implementations. Query-head row grouping, fused INT8 KV
conversion/packing, and direct mixed-type attention remain pending. This refresh
makes no speedup claim and includes no latency campaign. Additional construction
metadata can affect setup cost; it is not a new setup-time measurement.

## Validation

Compare against public commit `25684cdfba56bf1ce941a8f675c88a977dde9fcb`, building
both artifact sets with upstream `d297c798ea530c12a1878bb3a3a811bdf05d715b` and
the declared patches, including the HF BF16 rounding fix. Linux uses Clang
22.1.8, generated builders at `-O2`, the runner at `-O1`, and FP contraction off.
Replay the checked-in correctness fixtures at capacity 2,048, at most 128 real
prefill rows, four threads, no warmup and one repetition, with output dumps.
The 58 cases cover repeated requests/reset, prompts 1–1,024, chunk boundaries,
window crossings, and E4B multi-KV-head storage. These diagnostic timings are not
performance observations.

| Profile | C++ source files before → after | Exact logit/KV dump files |
| --- | --- | --- |
| e2b | 23 → 23 | 372 |
| e4b | 20 → 37 | 2619 |
| hf_bf16 | 27 → 63 | 837 |
| hf_bf16_int8_published_kv | 27 → 63 | 837 |
| hf_bf16_int8_raw_kv | 27 → 63 | 837 |
| hf_fp32_int8_published_kv | 17 → 30 | 837 |
| hf_static_int8_published_kv | 14 → 23 | 837 |

All 7,176 dump files match byte for byte, including every logit and active KV
payload. All 43 public Python tests and 13 host CTest checks pass. The Android
E2B/E4B runners and weights-free tests cross-compile successfully with the
existing NDK r28c configuration; no new device timing or execution is claimed.
The state oracle covers one/four threads, capacity/window bounds, invalid writes,
state-only effects, and GQA strides. Separate short E4B, HF BF16, and HF static
profiling runs preserve their unprofiled outputs, retain attributed callbacks,
and complete without lost events. Profiling remains opt-in.

[validation.json](validation.json) records construction digests, parameter
counts, source bounds, binary/model/runtime identities, per-profile output
parity and profiling checks. Raw logs, dumps and compiler material remain local.

## Reproduce output comparisons

Use separate checkouts for the baseline commit and this artifact set. Build
both with the same freshly bootstrapped dependency directory, adding
`--hf-bf16` for the five HF profiles. Follow the root README and
[HF asset instructions](../../docs/HF_GEMMA4.md) to prepare the same verified
sources and parameter recipes. Enable `LAB_BUILD_HF=ON` for the full matrix;
`LAB_ENABLE_TOKENIZERS=OFF` is sufficient for token-ID fixtures.

Run each binary against its model's `fixtures/correctness.tsv`, with
`--cache_capacity=2048 --prefill_rows=128 --num_threads=4 --warmup_runs=0
--measured_runs=1 --dump_outputs`, and save separate output directories.
For each matched profile, compare the outputs with:

```sh
uv run --locked python tools/compare_outputs.py \
  --reference "$BASELINE_OUTPUT" --candidate "$CANDIDATE_OUTPUT" \
  --output out/builder-refresh-comparison.json
```

Require `files == byte_identical` and identical dump filenames. Use separate
`--profile_execution=decode` runs to inspect callback attribution. These checks
establish parity with the same profile; they do not establish cross-profile
accuracy or equivalence to the native comparison runner.
