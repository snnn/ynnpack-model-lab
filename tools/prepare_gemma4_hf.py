#!/usr/bin/env python3
# Copyright 2026 @snnn.
# SPDX-License-Identifier: Apache-2.0
"""Verify HF tensors and write a direct-loading manifest; do not copy weights."""

import argparse
import hashlib
import json
from pathlib import Path
import sys

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from models.gemma4.hf_assets import SOURCE_REVISION, describe


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--hf-model-dir", type=Path, required=True)
    p.add_argument("--output", type=Path, required=True)
    p.add_argument("--revision", default=SOURCE_REVISION)
    p.add_argument(
        "--parameter-dir",
        type=Path,
        help="Materialize the checked-in builder constants here (default: next to manifest)",
    )
    args = p.parse_args()
    if args.output.exists():
        raise ValueError("Use a new manifest path")
    result = describe(args.hf_model_dir, args.revision)
    recipes = Path(__file__).resolve().parents[1] / "models/gemma4_e2b_hf/generated"
    parameter_dir = args.parameter_dir or args.output.parent / "parameters"
    parameters = {}
    for path in recipes.glob("*/asset_recipe.json"):
        recipe = json.loads(path.read_text())
        if recipe["source_identity"] != result["source_identity"]:
            raise ValueError(
                "Different source content: reauthor the HF graphs before using this checkpoint"
            )
        for name, encoded in recipe["parameters"].items():
            payload = bytes.fromhex(encoded)
            if name != hashlib.sha256(payload).hexdigest() + ".bin":
                raise ValueError("Invalid parameter recipe")
            parameters[name] = payload
    if parameters:
        parameter_dir.mkdir(parents=True, exist_ok=True)
        for name, payload in parameters.items():
            target = parameter_dir / name
            if target.exists() and target.read_bytes() != payload:
                raise ValueError(f"Conflicting parameter file: {name}")
            target.write_bytes(payload)
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(result, indent=2) + "\n")
    print(
        json.dumps(
            {
                "tensors": len(result["tensors"]),
                "identity": result["source_identity"],
                "parameters": len(parameters),
            }
        )
    )


if __name__ == "__main__":
    main()
