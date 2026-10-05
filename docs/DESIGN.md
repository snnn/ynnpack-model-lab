# Design and extension points

The lab separates model authoring, graph execution, persistent state, and
measurements. This lets a new model exercise YNNPACK without depending on a
large application runtime or copying the full E2B implementation.

| Component | Responsibility |
| --- | --- |
| External graph author | Offline graph preparation and C++ builder generation; maintained separately |
| `runtime/ynnpack_support.h` | Pinned YNNPACK/Slinky API adapter, bindings, state/view contracts |
| `runtime/model_assets.h` | Read-only mappings and Gemma4 embedding unpacking |
| `runtime/tokenizer.h`, `benchmark_cases.h` | Shared native tokenization, manifest policy, input resolution and fixture export |
| `models/gemma4/model_spec.py`, `hf_assets.py` | E2B/E4B architecture, source mapping and asset validation |
| `models/gemma4_*/generated/` | Reviewed, reproducible builders; no large learned tensors |
| `models/gemma4/runner.cc` | Request orchestration, embeddings, state ownership, timing |
| `tools/` | Dependency setup, asset extraction, benchmark orchestration |

## Symbolic state is more than dynamic tensor shapes

For a chunk beginning at position `p`, with `T` real rows and capacity `C`:

```
end = p + T
0 <= p <= end <= C
global K/V interval = [0, end)
local K/V interval  = [max(0, p - window + 1), end)
```

The local interval is the union required by all query rows in the chunk. A
per-row causal/window mask restricts each query further. Slinky expressions carry
these relationships to Slinky; `p` is an independent runtime scalar. Changing
`p` must update execution even when all input shapes remain unchanged.

Both K and V use separate token-major capacity buffers, logically `[1,1,C,D]`
for E2B. An append copies only the new `[T,D]` payload at the current position.
Attention consumes symbolic views of the updated storage. The graph orders the
write before its consumers. The host advances logical position after a successful
invocation. Physical state is not transactionally rolled back after a late
failure; callers must reset or discard a failed request. Invalid bounds are
checked before mutation. Resetting a successful request changes logical position;
old capacity bytes are excluded by views and masks.

Batch one and one KV head make E2B particularly convenient: an interval can be
contiguous. With multiple heads, a narrowed interval usually retains the original
capacity stride between heads. The state fixtures test those strided views and
grouped-query shapes, including two KV heads paired with eight query heads.
E4B now uses two heads in this layout; multiple request batches remain outside
the integration.
Never replace capacity strides with logical-length strides merely by reshaping.

## Prefill and decode

There are two prepared phase graphs, not one graph per layer and not a Cartesian
product of prompt/history buckets. They share source mappings and persistent KV
buffers. Packed backend constants and scratch are currently prepared independently.

Gemma's KV-sharing structure permits prefix-only execution to stop once all
required KV owners have been produced. The last prompt token traverses the full
decode graph and head to produce logits. The current source/compiler operation counts depend on the weight profile and
lowering policy; they are reported in each generated `model.json`. Prefill uses
at most 128 actual rows and does not pad the final chunk. Chunk scores are still materialized: global attention scratch grows with
`chunk_rows * live_history`, rather than `prompt_length²` for a full prompt graph.
Arithmetic over the whole sequence is not made linear by chunking.

No generic fusion is assumed to produce online-softmax tiled attention. That is
a separate backend scheduling/kernel project. Similarly, better state handling
does not guarantee faster FC kernels, good cache-size detection, or reusable
packed weights.

## Quantization and numerical contract

Weight codes/scales come from the published model, including static activation
and INT8 KV quantization. Norm coefficients retain their source precision. The
head has a floating interface and YNNPACK internally quantizes its input for an
integer dot. `YNN_FLAG_NO_EXCESS_PRECISION` keeps authored QAT rounding/clipping
boundaries from disappearing during backend rewriting.

Cross-backend bit identity is not required. Check finite outputs, logit error,
centered cosine/KL, greedy agreement, and eventually task quality. The existing
phone tests have a close top-two swap. Shape-dependent kernel/quantization
choices can change logits, so chunk-size changes deserve their own validation.
Capacity changes with identical logical work have a stronger invariant; the
original desktop capacity check produced identical logits.

## Adding another model

1. Add a model directory with architecture, weight provenance, extraction or
   import logic, token fixtures, and standalone builders. Maintain compiler
   integration and graph-authoring sources in their separate repository.
   Reuse the tokenizer and benchmark-case frontend with a hash-pinned asset
   recipe and explicit prompt prefix/suffix policy; pass the model's vocabulary
   bound to case resolution. See [TOKENIZERS.md](TOKENIZERS.md).
2. Reuse the YNNPACK runtime adapter. Add missing backend operations deliberately,
   with independent arithmetic/state tests. Avoid baking another model's layer
   counts or head layout into the adapter.
3. Supply runtime position parameters, view/append operations, and capacity bounds. Test
   nonzero origins, multiple heads, short final chunks, resets, and capacity
   boundaries. Only new KV writes may be copied for an append.
4. Validate logits against a trusted implementation before interpreting timing.
   Preserve controlled baseline weights and numerical contracts.
5. Measure preparation, warm prefill, decode, and memory separately across real
   query/history lengths. Record kernel choices before assigning a gap to graph
   authoring or the frontend runtime.

Qwen/Gemma3 integration should start with one concrete model, rather than a
large speculative model registry. A generic interactive/tokenizer API can follow
when a different model family reveals the remaining shared interfaces.
