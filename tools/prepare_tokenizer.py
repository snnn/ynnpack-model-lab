# Copyright 2026 @snnn.
# SPDX-License-Identifier: Apache-2.0
"""Prepare a local tokenizer directory from a hash-pinned asset recipe.

Works with standalone HF tokenizer.json and exact SentencePiece sections in
published bundles. This tool does not download assets or require Python ML
packages. Payloads are copied without conversion.
"""

import argparse
import hashlib
import json
from pathlib import Path
import tempfile


def digest(path):
    with path.open("rb") as source:
        return hashlib.file_digest(source, "sha256").hexdigest()


def nonnegative(value, name):
    if type(value) is not int or value < 0:
        raise ValueError(f"Invalid integer: {name}")
    return value


def prepare(source, output, recipe, *, verified_source=None):
    """verified_source is the identity already checked by Gemma asset extraction."""
    source, output = Path(source), Path(output)
    if recipe["version"] != 1 or recipe["format"] not in ("hf_json", "sentencepiece"):
        raise ValueError("Unsupported tokenizer recipe")
    identity, payload = recipe["source"], recipe["payload"]
    size = nonnegative(identity["bytes"], "source bytes")
    if source.stat().st_size != size or (
        verified_source != {"bytes": size, "sha256": identity["sha256"]}
        and digest(source) != identity["sha256"]
    ):
        raise ValueError("Tokenizer source hash/size mismatch")
    if not identity["repo"] or not identity["revision"]:
        raise ValueError("Tokenizer source identity is empty")
    vocab_size = nonnegative(recipe["vocab_size"], "vocab_size")
    if not 0 < vocab_size <= 2147483647:
        raise ValueError("Invalid vocabulary size")
    for key in ("prefix_ids", "suffix_ids"):
        if not isinstance(recipe[key], list) or any(
            type(token) is not int or not 0 <= token < vocab_size
            for token in recipe[key]
        ):
            raise ValueError(f"Invalid policy: {key}")
    relative = Path(payload["file"])
    if not payload["file"] or relative.is_absolute() or any(
        part in (".", "..") for part in payload["file"].split("/")
    ):
        raise ValueError("Invalid tokenizer payload path")
    offset = nonnegative(payload.get("offset", 0), "payload offset")
    length = nonnegative(payload["bytes"], "payload bytes")
    if length == 0 or offset > size or length > size - offset:
        raise ValueError("Tokenizer payload exceeds source")
    if output.exists():
        raise FileExistsError(f"Choose a new output directory: {output}")
    output.parent.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(prefix=".tokenizer-", dir=output.parent) as temp:
        staged = Path(temp) / "assets"
        staged.mkdir()
        target = staged / relative
        target.parent.mkdir(parents=True, exist_ok=True)
        with source.open("rb") as inp, target.open("wb") as out:
            inp.seek(offset)
            remaining = length
            while remaining:
                data = inp.read(min(remaining, 8 * 1024 * 1024))
                if not data:
                    raise ValueError("Truncated tokenizer source")
                out.write(data)
                remaining -= len(data)
        if digest(target) != payload["sha256"]:
            raise ValueError("Tokenizer payload checksum mismatch")
        if recipe["format"] == "hf_json":
            tokenizer = json.loads(target.read_text(encoding="utf-8"))
            if (tokenizer.get("padding") is not None or
                    tokenizer.get("truncation") is not None):
                raise ValueError("Tokenizer JSON must disable padding and truncation")
        manifest = {key: recipe[key] for key in (
            "version", "format", "vocab_size", "prefix_ids", "suffix_ids", "source"
        )}
        manifest.update({key: payload[key] for key in ("file", "bytes", "sha256")})
        (staged / "manifest.json").write_text(
            json.dumps(manifest, indent=2, ensure_ascii=False) + "\n", encoding="utf-8"
        )
        staged.rename(output)
    return output


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--recipe", type=Path, required=True)
    parser.add_argument("--source", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    prepare(args.source, args.output, json.loads(args.recipe.read_text()))
    print(f"Prepared tokenizer in {args.output}")


if __name__ == "__main__":
    main()
