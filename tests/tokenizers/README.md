# Native tokenizer fixtures

These small fixtures contain no LLM weights. The HF BPE vocabulary was trained
on a short multilingual string corpus with Python `tokenizers==0.22.2`, using
NFC, a Unicode regex split, and ByteLevel preprocessing/decoding. The
SentencePiece BPE model uses Python `sentencepiece==0.2.1`, identity
normalization, byte fallback, and preserved whitespace. Both vocabularies have
320 IDs and a `<special>` token. Their manifests use ID 1 as a prompt prefix.
The HF postprocessor would add `<special>` with default encoding; reference
IDs and native calls disable that implicit addition.

`golden.json` records exact IDs and decoded strings from those independent
Python libraries. Native CTest reads these recorded references; it does not
train models or install Python tokenizer packages. Cases cover empty text,
whitespace, NFC, CJK, emoji, embedded NUL, special-token spellings, and code.
The vocabularies deliberately give `~` one ID per byte for corpus boundary
tests. Real Gemma/Qwen asset parity is an opt-in check documented in
`docs/TOKENIZERS.md`.

Fixture data and golden records: Copyright 2026 @snnn., Apache-2.0.
