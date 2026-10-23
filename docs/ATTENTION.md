# Attention in the generated Gemma graphs

The semantic programs preserve global and sliding-window causal attention,
including query/KV head geometry, width, position, live-history origin and
numerical permissions. The shared Rust compiler selects its implementation and
may share native functions. Operation scopes retain layer attribution.

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

Runtime preparation lowers those operations and prepares one graph per phase.
To inspect a diagnostic construction stream:

```sh
mkdir -p out/attention-inspect
build/ynn-compile --request models/gemma4_e2b/generated/program.ynn --output out/attention-inspect/plans
build/ynn-plan expand out/attention-inspect/plans/decode.ynn -o out/attention-inspect/decode-flat.ynn
```

The diagnostic format remains `ynn 1`. Model identities cover stored semantic
program and execution bytes. Integer/row-grouped and HF BF16 profiles retain
their distinct numerical contracts. Selecting a profile does not change the
preparation boundary or add a separate runtime implementation.
