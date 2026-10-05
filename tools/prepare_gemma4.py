# Copyright 2026 @snnn.
# SPDX-License-Identifier: Apache-2.0
"""Prepare exact Gemma4 assets from the hash-pinned published .litertlm file.

This is an extraction recipe, not a general-purpose model converter. No LiteRT,
FlatBuffers, or NumPy installation is required. Learned tensors are
copied without requantization; PLE partitions are interleaved by token.
"""

import argparse
import hashlib
import json
import os
from pathlib import Path
import shutil
import tempfile

if __package__:
    from .prepare_tokenizer import prepare as prepare_tokenizer
else:
    from prepare_tokenizer import prepare as prepare_tokenizer

ROOT = Path(__file__).resolve().parents[1]


def digest(path):
    with path.open("rb") as f:
        return hashlib.file_digest(f, "sha256").hexdigest()


def relative_path(name):
    path = Path(name)
    if not name or path.is_absolute() or ".." in path.parts:
        raise ValueError(f"Invalid asset path: {name}")
    return path


def read_range(source, offset, size):
    if offset < 0 or size < 0:
        raise ValueError("Invalid source range")
    source.seek(offset)
    data = source.read(size)
    if len(data) != size:
        raise ValueError("Source range exceeds file")
    return data


def extract(source, recipe, output):
    if "literal" in recipe:
        output.write(bytes.fromhex(recipe["literal"]))
    elif "interleave" in recipe:
        # Bound temporary memory independently of the 1.09-GiB PLE table.
        columns = recipe["interleave"]
        row_bytes = recipe["row_bytes"]
        stride = row_bytes * len(columns)
        rows_per_block = max(1, 4 * 1024 * 1024 // stride)
        for first in range(0, recipe["rows"], rows_per_block):
            count = min(rows_per_block, recipe["rows"] - first)
            block = bytearray(count * stride)
            for col, item in enumerate(columns):
                if (first + count) * row_bytes > item["bytes"]:
                    raise ValueError("Invalid interleave source")
                data = memoryview(
                    read_range(
                        source, item["offset"] + first * row_bytes, count * row_bytes
                    )
                )
                for row in range(count):
                    start = row * stride + col * row_bytes
                    block[start : start + row_bytes] = data[
                        row * row_bytes : (row + 1) * row_bytes
                    ]
            output.write(block)
    else:
        offset, remaining = recipe["offset"], recipe["bytes"]
        while remaining:
            size = min(remaining, 8 * 1024 * 1024)
            output.write(read_range(source, offset, size))
            offset += size
            remaining -= size


def prepare(model, output, variant="e2b"):
    model_dir = ROOT / ("models/gemma4_" + variant)
    recipe = json.loads((model_dir / "asset_recipe.json").read_text())
    source = recipe["source"]
    if model.stat().st_size != source["bytes"] or digest(model) != source["sha256"]:
        raise ValueError(
            "Model hash/size mismatch; use the exact revision in README.md"
        )
    if output.exists():
        raise FileExistsError(f"Choose a new output directory: {output}")
    output.parent.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(prefix=".gemma4-", dir=output.parent) as temp:
        staged = Path(temp) / "assets"
        staged.mkdir()
        written = {}
        with model.open("rb") as inp:
            for name, sha in sorted(recipe["files"].items()):
                if name.startswith("@parameters/"):
                    target = staged / "parameters" / relative_path(name[12:])
                else:
                    target = staged / "bundle" / relative_path(name)
                target.parent.mkdir(parents=True, exist_ok=True)
                if sha in written:
                    # Hard links share immutable payloads; no symlinks to this machine.
                    os.link(written[sha], target)
                else:
                    with target.open("wb") as out:
                        extract(inp, recipe["recipes"][sha], out)
                    if (
                        target.stat().st_size != recipe["recipes"][sha]["bytes"]
                        or digest(target) != sha
                    ):
                        raise ValueError(f"Extracted asset checksum mismatch: {name}")
                    written[sha] = target
        shutil.copyfile(
            model_dir / "bundle_manifest.json", staged / "bundle/manifest.json"
        )
        shutil.copyfile(model_dir / "generated/model.json", staged / "model.json")
        tokenizer_recipe = json.loads((model_dir / "tokenizer_recipe.json").read_text())
        prepare_tokenizer(
            model, staged / "tokenizer", tokenizer_recipe,
            verified_source={"bytes": source["bytes"], "sha256": source["sha256"]},
        )
        staged.rename(output)
    print(
        f"Prepared {len(recipe['files'])} files ({len(written)} unique payloads) in {output}"
    )


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--model", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    parser.add_argument("--variant", choices=["e2b", "e4b"], default="e2b")
    args = parser.parse_args()
    prepare(args.model, args.output, args.variant)


if __name__ == "__main__":
    main()
