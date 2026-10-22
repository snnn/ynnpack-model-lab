# Attention in the generated Gemma graphs

The default E2B and E4B prefill/decode plans each define two reusable FP32
attention functions near the top of the `.ynn` file. Layer bodies invoke them
under a layer-specific scope. The function name identifies global or sliding
attention, head count, KV-head count, width and phase.

- `global_causal_attention_fp32_*` uses the complete initialized history with
  a causal mask. It has no window argument.
- `sliding_window_causal_w512_attention_fp32_*` uses the live window and applies
  both the causal and 512-token limits to each query row.

For query position `P`, query length `T` and history origin `B`, the live key
length is `P + T - B`. Global attention uses `B = 0`. Sliding attention uses
`B = max(0, P - 511)`. Query row `i` can attend to key row `j` when:

| Mode | Eligible key position |
| --- | --- |
| Global causal | `B + j <= P + i` |
| Sliding causal | `P + i - 511 <= B + j <= P + i` |

The history slice covers the entire query chunk; the per-query mask is still
necessary. The source exposes `query_position`, `key_length` and, for sliding
attention, `key_begin`, with explicit validity checks. Capacity remains storage,
not the amount of attention work.

Inside each function, QK produces `scores`, the mask produces `masked_scores`,
softmax uses a row maximum and row sum, and PV produces `context`. E4B's two KV
heads use query-group slices and concatenate their contexts. This retains the
existing FP32 arithmetic and checkpoint scaling. It is not an online/streaming
softmax implementation.

Cache append/view operations, INT8 KV dequantization, query projection and output
projection remain in the layer. Function arguments are ordinary FP32 tensors;
the body does not own or mutate cache state. This makes the attention computation
visible without hiding layer-specific state updates.

The Rust loader expands calls before native preparation, producing one graph.
To inspect all primitive commands without changing the packaged source:

```sh
build/ynn-plan expand models/gemma4_e2b/generated/gemma4_decode.ynn -o out/decode-flat.ynn
build/ynn-plan inspect models/gemma4_e4b/generated/gemma4_prefill.ynn -o out/prefill-inspection.json
```

The format remains `ynn 1`. Formatting retains function hierarchy; model phase
hashes cover the entire source. This change makes no performance claim. The
experimental INT8/row-grouped and HF BF16 artifacts retain their separate
representations and numerical contracts.