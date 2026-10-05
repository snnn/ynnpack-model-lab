#!/usr/bin/env python3
# Copyright 2026 @snnn.
# SPDX-License-Identifier: Apache-2.0
"""Compare audited safetensors assets with the published Gemma4 E2B bundle.

Requires NumPy. Reads existing manifests/payloads without modifying either
source. The preparation tools remain responsible for source hash validation.
"""

import argparse
import json
from pathlib import Path

import numpy as np


def bf16_bits(x):
    bits = np.asarray(x, dtype=np.float32).view(np.uint32)
    return ((bits + 0x7FFF + ((bits >> 16) & 1)) >> 16).astype(np.uint16)


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--hf-model-dir", type=Path, required=True)
    p.add_argument("--asset-manifest", type=Path, required=True)
    p.add_argument("--bundle-dir", type=Path, required=True)
    p.add_argument("--output", type=Path, required=True)
    args = p.parse_args()
    hf = json.loads(args.asset_manifest.read_text())
    published = json.loads((args.bundle_dir / "manifest.json").read_text())
    tensors = {r["name"]: r for r in published["tensors"]}

    def source(name, dtype, raw=False):
        r = hf["tensors"][name]
        shape = (r["bytes"],) if raw else tuple(r["logical_shape"])
        return np.memmap(
            args.hf_model_dir / r["file"],
            mode="r",
            dtype=dtype,
            offset=r["offset"],
            shape=shape,
        )

    integers, coefficients, scales, activations = [], [], [], []
    for name, r in tensors.items():
        if name not in hf["tensors"]:
            continue
        hr = hf["tensors"][name]
        if r["dtype"] in ("int2", "int4", "int8") and hr["dtype"] in ("U8", "I8"):
            a = np.memmap(args.bundle_dir / r["file"], mode="r", dtype=np.uint8)
            b = source(name, np.uint8, True)
            if a.size != b.size:
                raise ValueError("Packed byte length mismatch: " + name)
            mask = {2: 0xAA, 4: 0x88, 8: 0}[hr["bits"]]
            count = sum(
                int(np.count_nonzero(a[i : i + 1048576] != (b[i : i + 1048576] ^ mask)))
                for i in range(0, a.size, 1048576)
            )
            integers.append(dict(name=name, bytes=int(a.size), different_bytes=count))
            q = r["quantization"]
            x = np.fromfile(args.bundle_dir / q["scales_file"], dtype="<f4")
            y = source(name.removesuffix(".weight") + ".weight_scale", "<f4").reshape(
                -1
            )
            scales.append(
                dict(
                    name=name,
                    count=int(x.size),
                    different=int(np.count_nonzero(x != y)),
                )
            )
        elif r["dtype"] == "float32" and hr["dtype"] == "BF16":
            a = np.fromfile(args.bundle_dir / r["file"], dtype="<f4")
            b = source(name, "<u2").reshape(-1)
            restored = (b.astype(np.uint32) << 16).view(np.float32)
            coefficients.append(
                dict(
                    name=name,
                    count=int(a.size),
                    bf16_rounding_mismatches=int(np.count_nonzero(bf16_bits(a) != b)),
                    max_abs_error=float(np.max(np.abs(a - restored))),
                )
            )
        elif name.endswith((".input_scale", ".output_scale")) and hr["dtype"] == "F32":
            a = np.fromfile(args.bundle_dir / r["file"], dtype="<f4")
            b = source(name, "<f4").reshape(-1)
            activations.append(dict(name=name, different=int(np.count_nonzero(a != b))))
    name = "model.per_layer_model_projection.weight"
    r = tensors[name]
    w = np.fromfile(args.bundle_dir / r["file"], np.int8).reshape(r["shape"])
    s = np.fromfile(args.bundle_dir / r["quantization"]["scales_file"], "<f4")[:, None]
    b = source(name, "<u2")
    f = (b.astype(np.uint32) << 16).view(np.float32)
    projection = dict(
        elements=int(w.size),
        bf16_dequant_mismatches=int(np.count_nonzero(bf16_bits(w * s) != b)),
        requantized_code_mismatches=int(
            np.count_nonzero(np.clip(np.rint(f / s), -128, 127).astype(np.int8) != w)
        ),
        max_abs_weight_error=float(np.max(np.abs(f - w * s))),
        caveat="Reconstruction uses published per-channel scales; those scales are absent for this BF16 HF tensor.",
    )
    kv = []
    for r in published["kv_cache_specs"]:
        owner = r["owner"]
        hr = hf["kv"][owner]
        kv.append(
            dict(
                owner=owner,
                key_ratio=hr["k_scale"] / r["key_scale"],
                value_ratio=hr["v_scale"] / r["value_scale"],
            )
        )
    result = dict(
        source_identity=hf["source_identity"],
        integer_weights=integers,
        weight_scales=scales,
        activation_scales=activations,
        coefficients=coefficients,
        global_projection=projection,
        kv_scales=kv,
    )
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(result, indent=2) + "\n")
    print(
        json.dumps(
            dict(
                integer_tensors=len(integers),
                different_integer_bytes=sum(x["different_bytes"] for x in integers),
                weight_scale_tensors=len(scales),
                different_scales=sum(x["different"] for x in scales),
                bf16_coefficients=len(coefficients),
                bf16_rounding_mismatches=sum(
                    x["bf16_rounding_mismatches"] for x in coefficients
                ),
                activation_scales=len(activations),
                different_activation_scales=sum(x["different"] for x in activations),
                global_projection=projection,
            )
        )
    )


if __name__ == "__main__":
    main()
