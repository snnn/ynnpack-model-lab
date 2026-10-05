# Copyright 2026 @snnn.
# SPDX-License-Identifier: Apache-2.0
"""Opt-in exact native/Python tokenizer ID comparison using local real assets.

Requires Python tokenizers==0.22.2 or sentencepiece==0.2.1 for the selected
format. Ordinary CTest uses tiny checked-in fixtures and needs neither package
nor downloaded models. No chat templates or implicit special tokens are used.
"""

import argparse
import importlib.metadata
import json
from pathlib import Path
import subprocess

TEXTS = [
    "", "Hello, world!", " leading and trailing  ", "\t\n\r  ",
    "Café naïve résumé", "e\u0301 a\u0308", "中文 日本語 한국어",
    "العربية עברית हिन्दी", "🙂👩🏽\u200d💻🚀", "a\x00b",
    "<bos>Hello<eos>", "<special> hello", "<|im_start|>user\nHi<|im_end|>",
    "<|turn>user\nHello<turn|>", "<|endoftext|>", "<think>test</think>",
    'print("hi\\n");\n', "0123456789 -12.34", "𝕏 ∑ αβ", "tail\n",
    "one\r\ntwo\n", "\u00a0\u2003\u200b", "<image><audio>", "x" * 2048,
]


def run(probe, argv):
    subprocess.run([str(probe), *argv], check=True, capture_output=True, text=True)


def read_cases(path):
    def ids(field):
        return [] if field == "-" else [int(value) for value in field.split(",")]
    return [(name, ids(prompt), ids(continuation)) for name, prompt, continuation in
            (line.split("\t") for line in path.read_text().splitlines())]


def check(probe, tokenizer_dir, output):
    manifest = json.loads((tokenizer_dir / "manifest.json").read_text())
    if manifest["format"] == "hf_json":
        from tokenizers import Tokenizer
        reference = "tokenizers"
        version = "0.22.2"
        tokenizer = Tokenizer.from_file(str(tokenizer_dir / manifest["file"]))
        encode = lambda text: tokenizer.encode(text, add_special_tokens=False).ids
    else:
        import sentencepiece
        reference = "sentencepiece"
        version = "0.2.1"
        tokenizer = sentencepiece.SentencePieceProcessor(model_file=str(tokenizer_dir / manifest["file"]))
        encode = lambda text: tokenizer.encode(text, out_type=int)
    if importlib.metadata.version(reference) != version:
        raise ValueError(f"Use {reference}=={version} for this reference check")
    output.mkdir(parents=True, exist_ok=False)
    prefix, suffix = manifest["prefix_ids"], manifest["suffix_ids"]
    cases = [{"name": f"text_{i}", "prompt": text,
              "continuation": " next\n" if i % 2 else ""}
             for i, text in enumerate(TEXTS) if text or prefix or suffix]
    text_file = output / "cases.jsonl"
    text_file.write_text("".join(json.dumps(case, ensure_ascii=False) + "\n" for case in cases), encoding="utf-8")
    run(probe, [f"--tokenizer_dir={tokenizer_dir}", f"--text_cases_file={text_file}",
                f"--output_dir={output / 'explicit'}", "--cache_capacity=8192"])
    expected = [(case["name"], prefix + encode(case["prompt"]) + suffix,
                 encode(case["continuation"])) for case in cases]
    if read_cases(output / "explicit/resolved_cases.tsv") != expected:
        raise AssertionError("Explicit native token IDs differ from Python reference")
    corpus = ("The cat sat on the mat. 中文 café 🙂\n" * 400)
    corpus_file = output / "corpus.txt"
    corpus_file.write_text(corpus, encoding="utf-8")
    lengths = [1, 128, 129, 130, 511, 512, 513, 1024]
    run(probe, [f"--tokenizer_dir={tokenizer_dir}", f"--corpus_file={corpus_file}",
                "--prompt_lengths=" + ",".join(map(str, lengths)), "--continuation_tokens=2",
                f"--output_dir={output / 'corpus'}"])
    ids = encode(corpus)
    expected = []
    for length in lengths:
        body = length - len(prefix) - len(suffix)
        expected.append((f"prompt_{length}", prefix + ids[:body] + suffix, ids[body:body + 2]))
    if read_cases(output / "corpus/resolved_cases.tsv") != expected:
        raise AssertionError("Corpus native token IDs differ from Python reference")
    report = {"reference": f"{reference} {version}", "tokenizer": manifest,
              "explicit_cases": len(cases), "corpus_lengths": lengths, "exact_ids": True}
    (output / "parity.json").write_text(json.dumps(report, indent=2) + "\n")
    print(f"PASS: {len(cases)} explicit cases and {len(lengths)} corpus lengths match {reference} {version}")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--probe", type=Path, required=True)
    parser.add_argument("--tokenizer_dir", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    check(args.probe.resolve(), args.tokenizer_dir.resolve(), args.output.resolve())


if __name__ == "__main__":
    main()
