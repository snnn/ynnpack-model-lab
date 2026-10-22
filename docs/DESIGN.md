# Design and extension points

The lab separates model authoring, graph execution, persistent state, and
measurements. The intended LLM scope includes Gemma4 E2B, E4B, 12B and 31B,
and multiple Qwen models. Shared interfaces should serve each model's actual
architecture, state and numerical contract. Current integrations are listed in
[model support](../README.md#models-and-workloads); implementation order does
not make a model the default design or documentation entry point.

| Component | Responsibility |
| --- | --- |
| External graph author | Offline graph preparation and `.ynn` plan export; maintained separately |
| `runtime/ynnpack_support.h` | Pinned YNNPACK/Slinky API adapter, bindings, state/view contracts |
| `runtime/model_assets.h` | Read-only mappings and Gemma4 embedding unpacking |
| `rust/src/frontend.rs`, `rust/src/frontend/` | Shared argument/input handling, direct HF tokenization, manifest policy, provenance and fixture export |
| `runtime/rust/sentencepiece.h` | Small FFI for the SentencePiece C++ engine |
| `models/gemma4/model_spec.py`, `hf_assets.py` | E2B/E4B architecture, source mapping and asset validation |
| `models/gemma4_*/generated/` | Reviewed, reproducible plans; no large learned tensors |
| `rust/src/gemma.rs`, `rust/src/gemma/` | Request orchestration, package validation, state ownership and timing |
| `tools/` | Dependency setup, asset extraction, benchmark orchestration |

The [Rust runtime](RUST_RUNTIME.md) owns vision/Gemma request orchestration and
buffers. Typed, validated `.ynn` plans construct native graphs through one adapter.
Embedding arithmetic and authoritative resource-state checks remain native.
There is no generated C++ model path. See [the plan format](GRAPH_PLANS.md).

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

Current Gemma K/V owners use separate K and V allocations shaped
`[1,Hkv,C,D]`, with `Hkv=1` for E2B and `Hkv=2` for E4B. Each allocation
reserves a full `[C,D]` region for every KV head. The physical layout groups
tokens by head: head `h` begins at element offset `h * C * D`, regardless of
the current logical length.

An append copies only the new `[1,Hkv,T,D]` payload into those reserved regions.
For each K or V allocation, the update is:

```python
for h in range(Hkv):
    cache[0, h, p:p + T, :] = fresh[0, h, 0:T, :]
```

E4B therefore writes two ranges per allocation. For `C=8`, `p=3` and `T=2`,
each slot below represents one token's `D` elements:

```text
head 0: [old old old NEW NEW unused unused unused]
head 1: [old old old NEW NEW unused unused unused]
```

The second head stays at offset `C * D`; neither its old tokens nor the first
head's old tokens move. The adapter crops the destination along the token axis
and uses a stride-aware `slinky::copy`. A dense fresh payload has head stride
`T * D`, while the destination retains head stride `C * D`.

Attention consumes symbolic views of the updated storage. The graph orders the
write before its consumers. The host advances logical position after a successful
invocation. Physical state is not transactionally rolled back after a late
failure; callers must discard the failed session. Invalid bounds are
checked before mutation. Resetting a successful request changes logical position;
old capacity bytes are excluded by views and masks.

For an attention interval `[begin,end)`, the view has logical shape
`[1,Hkv,end-begin,D]`. Its head stride remains `C * D` elements, and its first
token for head `h` is at offset `(h * C + begin) * D` in the allocation.
The state fixtures test those strided views and grouped-query
shapes, including two KV heads paired with eight query heads. Multiple request
batches remain outside the current integration. New models must supply their
own state semantics rather than assume a single KV head or this Gemma layout.
Never replace capacity strides with logical-length strides merely by reshaping.

## Prefill and decode

The current Gemma integrations use two prepared phase graphs. They share source
mappings and persistent KV buffers; packed backend constants and scratch are
currently prepared independently. Graphs are reused across prompt/history
lengths without host execution per layer.

E2B/E4B's KV-sharing structure permits prefix-only execution to stop once all
required KV owners have been produced. The last prompt token traverses the full
decode graph and head to produce logits. Source/compiler operation counts depend
on the weight profile and lowering policy; each generated `model.json` records
them. Prefill uses at most 128 actual rows and does not pad the final chunk.
Chunk scores are still materialized: global attention scratch grows with
`chunk_rows * live_history`, rather than `prompt_length²` for a full prompt graph.
Arithmetic over the whole sequence is not made linear by chunking.

No generic fusion is assumed to produce online-softmax tiled attention. That is
a separate backend scheduling/kernel project. Similarly, better state handling
does not guarantee faster FC kernels, good cache-size detection, or reusable
packed weights.

## Quantization and numerical contract

Each package declares its source and numerical contract. The published-bundle
Gemma profiles preserve weight codes/scales, static activation and INT8 KV
quantization, and source coefficient precision. Their head has a floating
interface and YNNPACK internally quantizes its input for an integer dot.
`YNN_FLAG_NO_EXCESS_PRECISION` preserves authored QAT rounding/clipping
boundaries during backend rewriting. HF and future model profiles must specify
their own arithmetic; these Gemma choices are not universal runner defaults.

Cross-backend bit identity is not required. Check finite outputs, logit error,
centered cosine/KL, greedy agreement, and eventually task quality. The existing
phone tests have a close top-two swap. Shape-dependent kernel/quantization
choices can change logits, so chunk-size changes deserve their own validation.
Capacity changes with identical logical work have a stronger invariant; the
original desktop capacity check produced identical logits.

## Adding another model

1. Add a model directory with architecture, weight provenance, extraction or
   import logic, token fixtures, and standalone `.ynn` plans. Maintain compiler
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

Add each Gemma4 or Qwen integration from a concrete checkpoint and extend shared
interfaces when its architecture requires them. Keep layer counts, head layouts,
quantization and tokenizer policy in model-specific authors, assets and metadata.
[Planned integrations](worklogs/MODEL_INTEGRATIONS.md) track missing packages and
their completion checks. Unfinished investigations and coverage checks are kept
in [open work](worklogs/README.md); dated numerical/performance evidence belongs
in [results](../results/README.md).
