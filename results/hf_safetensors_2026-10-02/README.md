# Initial direct-safetensors Gemma4 E2B measurements

This record evaluates the initial HF BF16 profiles, not a replacement for the
published-source integer runner. The loader, symbolic state contracts, and
full-model execution work. Numerical parity with Transformers is **not yet
established**, and the initial implementation is substantially slower than the
existing integer path. Performance results below characterize this implementation;
they do not establish a general safetensors or BF16 performance limitation.

## What was measured

- Original `google/gemma-4-E2B-it-qat-mobile-transformers` checkpoint, revision
  `dd693ff40353f057ca5f07e945ad867f4afbf2ec`; tensor-content identity
  `b454fea4385836b70181ce7f8d797413d695d7f916b21ed3dd49896cdad6d579`.
- Pinned backend and state patches from `dependencies.json`, plus the separate
  BF16 rounding fix. SME/SME2 disabled. These measurements use the `Pow(-0.5)`
  RMSNorm author, matching the operation explicitly used by Transformers.
- Intel Core i9-12900K Linux host, TECNO LJ9, and Pixel 8. Release builds:
  host Clang 22.1.8; Android NDK r28c, Android API 28, static libc++.
- Warm derived packed-weight cache, one warmup and three measured requests per
  case. The cache contains recoded integer payloads, not backend-prepared weights.
- Prompts 17/128/1024. Desktop uses eight forced continuation tokens; phones use
  two, as retained in `phone-performance.tsv`. Do not equate these workloads
  with the official 256-decode-token model-card benchmark.
- Default four threads, capacity 2048, chunks up to 128 real rows. Desktop also
  checks BF16 with capacity 8448 and with one thread. Affinity/governors are not
  forced. Each phone runs one benchmark process at a time; host timing runs
  exclude competing builds/reference runs. Phone profiles have a 30-second gap;
  this does not guarantee identical thermal conditions.

Warm TTFT includes prefix execution and the full final prompt-token step.
Prefill tok/s is `(prompt_length - 1) / prefix_seconds`; decode tok/s excludes
that final prompt-token step. Setup is reported separately. Timing/dump runs
are separate. Median latency is taken across the three measured requests;
decode throughput is the reciprocal of median per-request mean token latency.

## Numerical and state validation

Each full reference comparison covers nine prompts (1/17/128/129/130/511/512/
513/1024), the first logits and two teacher-forced continuation outputs: 27
logit vectors and the corresponding KV histories. The reference runs the
Transformers text model directly from the original checkpoint, using its
quantized modules, BF16 execution, and eager attention. The two INT8 references
instrument cache updates with their respective scales; ordinary Transformers
does not consume the checkpoint KV scales. Exact package versions are retained.

| Profile versus matching reference | Greedy agreement | Minimum centered logit cosine | Maximum KL(reference → candidate) | Maximum absolute logit error |
| --- | ---: | ---: | ---: | ---: |
| BF16 KV | 22/27 | 0.960655 | 0.496356 | 7.5000 |
| Original HF INT8 KV scales | 23/27 | 0.953912 | 0.656702 | 8.4375 |
| Published-compatible INT8 KV scales | 24/27 | 0.965086 | 0.257526 | 5.8906 |

On the same full BF16 fixture, both phones have 21/27 greedy agreement with
Transformers, minimum logit cosine 0.958089, maximum KL 0.274816, and maximum
absolute logit error 13.71875. All 837 output files are byte-identical between
the two phones. This establishes repeatable ARM behavior for this fixture,
while retaining the reference discrepancy; it does not establish cross-platform
or reference bit identity.

The largest phone logit error already occurs on the one-token BOS case:
reference argmax 568 versus runner argmax 529. It cannot be explained solely
by a long-context window or capacity issue. In that case, saved KV values for
owners 0–12 have zero numerical error (a few signed-zero bit differences);
the first nonzero saved KV differences appear at owner 13. This narrows the
trace needed next, but saved KV boundaries are not a complete operator trace.

During the separate timing runs, all repeated requests have identical greedy
choices within each configuration. On the nine phone performance outputs,
BF16 and published-compatible INT8 each match their own reference on 9/9
choices, and raw INT8 matches on 8/9. The larger correctness fixture is more
discriminating, so the short performance fixture alone would overstate parity.

The KV policy itself also changes outputs even within the independent reference:

| Transformers INT8 cache policy versus Transformers BF16 cache | Greedy agreement | Minimum logit cosine | Maximum KL |
| --- | ---: | ---: | ---: |
| Original HF scales | 22/27 | 0.937734 | 0.414852 |
| Published-compatible scales | 19/27 | 0.894087 | 2.329353 |

The global-scale division by 16 is therefore a compatibility experiment, not
an accuracy improvement demonstrated by these checks. A policy's difference
from BF16 and the backend's difference from its matching reference are separate
measurements.

All compared logits and BF16 KV values are finite. These discrepancies are too
large to declare reference parity. Differences in reductions, transcendental
approximations, and static quantization ties can contribute, but we have not
proved that they explain every discrepancy. The records retain full per-output
metrics and aggregate KV differences. Teacher forcing is not a free-generation
quality evaluation, and the small greedy-agreement differences do not rank the
three KV policies by model quality.

The stronger self-consistency/control checks are:

| Check | Result |
| --- | --- |
| Capacity 2048 → 8448, each of the three profiles | All 837 dump files byte-identical per profile: 27 logit vectors and 82,225,152 KV elements |
| BF16 chunks 128 → 64 | 27/27 greedy choices agree; 768/837 dump files byte-identical; minimum logit cosine 0.965877, maximum KL 0.222371; numerical shape sensitivity remains |
| Existing published-source E2B versus its saved control | All 372 files byte-identical, including 12 logit vectors |
| Existing published-source E4B versus its saved control | All 2,619 files byte-identical, including 27 logit vectors |
| Explicit history-view copies | Zero; append byte/call invariants checked on every invocation |

The capacity check covers logical bounds independently of physical allocation.
The chunk check covers nonzero positions, short final chunks, and window
crossings, but its numerical differences mean we should not claim chunk-size
bit invariance for BF16. The existing controls retain their exact results.

A separate regression identified an actual fusion problem: a
`tanh → BF16 → FP32 → multiply → BF16 → FP32` chain lost an intermediate
rounding despite `YNN_FLAG_NO_EXCESS_PRECISION`. The original backend fails the
small test; the isolated patch passes on the host and both phones. That fix
improves semantic fidelity but does not resolve the full-model reference gap.
No upstream issue or pull request was submitted.

Final validation also passes all seven CTest entries, the ten optional Core IR
authoring tests, and both the BF16 arithmetic and safetensors asset tests on
each phone. All three HF generated builder sets and parameter recipes reproduce
byte-for-byte after reauthoring. These implementation checks are separate from
the unresolved full-model numerical comparison.

## Storage and memory interpretation

The original shard is 2,458,111,846 bytes. Text tensor payloads described by the
manifest total 2,118,056,254 bytes; not every text tensor is used. The lazy
signed-packed cache contains 206 files totaling 735,313,920 bytes (701.25 MiB).
It preserves integer codes while recoding offset-binary INT2/INT4 storage.
There is no second full model archive. In particular, the 1,174,405,120-byte
per-layer embedding table stays in its original source storage.

Hash validation reads source pages during setup. Those resident mmap pages
count toward RSS; there is no `madvise` eviction. Peak RSS also includes the
recoded mappings, graph state, preparation, scratch, and previous cases. It
is not a private-heap measurement and should not be compared with a hypothetical
weight-excluded memory budget. Setup still prepares the two backend phases;
the derived cache does not avoid that work.

KV storage and fresh append payloads are 18,432 bytes/token for BF16 and 9,216
bytes/token for INT8. At capacity 2048, these are 36 MiB and 18 MiB. Raising
capacity to 8448 adds 112.5 MiB and 56.25 MiB respectively. Attention operates
on the live interval, not the entire allocation. Identical capacity-test
outputs and zero view-copy counters support the state contract; they do not
claim zero backend packing/dequantization or zero history reads.

## What remains open

1. Localize the remaining numerical discrepancies with the independent
   reference before calling these profiles accuracy-qualified.
2. Profile BF16 weight dequantization, dot selection, intermediate conversions,
   and preparation to explain the large cost. The BF16 profile name alone is
   not evidence that a particular hardware BF16 kernel was selected.
3. Evaluate faster arithmetic lowerings as separate profiles with explicit
   numerical measurements. Moving scales outside a dot, dropping BF16
   boundaries, or adopting the published INT8 graph is not silently equivalent
   to the authored HF computation.
4. Broader prompts and free-generation/quality evaluation remain necessary.
   E4B safetensors and other architectures are outside this first integration.

Build and reproduction instructions are in `docs/HF_GEMMA4.md`. The small JSON
records alongside this document preserve numerical evidence and raw timing
observations; model tensors and large output dumps are intentionally external.

## Warm 1,024-token measurements

Desktop rows use eight continuation tokens; phone rows use two. The control
uses a different arithmetic contract. Full prompt-length results, observed
ranges, and raw per-token timings are retained in `metrics.csv`,
`metrics.json`, and `timings/`. All runs have output dumping disabled.

| Device | Profile | Threads | Capacity | TTFT, s | Prefill tok/s | Decode tok/s | Peak RSS, MiB | Setup, s |
| --- | --- | ---: | ---: | ---: | ---: | ---: | ---: | ---: |
| desktop | INT8 published KV | 4 | 2048 | 5.169 | 229.5 | 1.40 | 3046.5 | 59.2 |
| desktop | INT8 raw KV | 4 | 2048 | 5.208 | 227.9 | 1.39 | 3045.2 | 60.7 |
| desktop | BF16 KV | 1 | 2048 | 18.122 | 64.2 | 0.45 | 3025.7 | 59.5 |
| desktop | BF16 KV | 4 | 2048 | 5.208 | 228.5 | 1.37 | 3083.7 | 60.3 |
| desktop | BF16 KV | 4 | 8448 | 5.215 | 227.9 | 1.38 | 3197.9 | 61.8 |
| desktop | Published-source control | 4 | 2048 | 1.751 | 593.9 | 36.19 | 1689.7 | 11.9 |
| tecno_lj9 | INT8 published KV | 4 | 2048 | 12.979 | 91.8 | 0.55 | 3027.4 | 217.5 |
| tecno_lj9 | INT8 raw KV | 4 | 2048 | 12.788 | 93.6 | 0.55 | 3030.9 | 218.8 |
| tecno_lj9 | BF16 KV | 4 | 2048 | 12.238 | 98.0 | 0.56 | 3049.3 | 209.7 |
| pixel8 | INT8 published KV | 4 | 2048 | 16.992 | 74.5 | 0.38 | 3022.6 | 174.3 |
| pixel8 | INT8 raw KV | 4 | 2048 | 15.376 | 82.4 | 0.39 | 3019.2 | 164.6 |
| pixel8 | BF16 KV | 4 | 2048 | 16.445 | 76.9 | 0.51 | 3032.8 | 156.1 |

Peak RSS is a process high-water mark, including startup and earlier cases.
Pixel timing varies noticeably between repetitions; thermal/frequency effects
were not isolated. Small differences among KV policies are not a kernel-level
comparison and should not be treated as a reliable ranking.

Before backend optimization, the BF16 decode author emits 14,444 operations,
including 8,519 conversions; the published-source control emits 3,790
operations. These are authoring counts, not executed-kernel counts. They
illustrate the additional precision handling expressed by this first version.
No full operator profile was collected in this integration pass.
