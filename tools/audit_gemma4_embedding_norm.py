#!/usr/bin/env python3
# Copyright 2026 @snnn.
# SPDX-License-Identifier: Apache-2.0
"""Ablate E2B embedding/first-RMSNorm precision using existing diagnostic traces.

Requires NumPy and a single-token decode trace from each runner. First run the
source audit: this calculation uses the verified equality of shared integer
codes/scales and HF coefficients with BF16-rounded published coefficients.
It changes no model or runtime configuration.
"""

import argparse
import json
from pathlib import Path

import numpy as np

from audit_gemma4_fc_trace import bf
from compare_value_traces import metrics, read_trace


def norm(x, weight):
    mean = np.mean(x * x, axis=-1, keepdims=True, dtype=np.float32)
    inv = np.power(mean + np.float32(1e-6), np.float32(-0.5))
    return (x * inv) * weight


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--bundle-dir", type=Path, required=True)
    p.add_argument("--control-trace", type=Path, required=True)
    p.add_argument("--hf-trace", type=Path, required=True)
    p.add_argument("--token-id", type=int, required=True)
    p.add_argument("--output", type=Path, required=True)
    args = p.parse_args()
    a, b = read_trace(args.control_trace), read_trace(args.hf_trace)
    manifest = json.loads((args.bundle_dir / "manifest.json").read_text())
    tensors = {r["name"]: r for r in manifest["tensors"]}
    name = "model.layers.0.input_layernorm"
    x, hx = a[name + ".input"][0], b[name + ".input"][0]
    y, hy = a[name + ".output"][0], b[name + ".output"][0]
    if x.shape != (1, 1, 1536) or hx.shape != x.shape:
        raise ValueError("Expected single-token E2B first-layer traces")
    w = np.fromfile(args.bundle_dir / tensors[name + ".weight"]["file"], "<f4")
    r = tensors["model.embed_tokens.weight"]
    if r["dtype"] != "int2" or r["shape"] != [262144, 1536]:
        raise ValueError("Expected compact E2B INT2 embedding")
    if not 0 <= args.token_id < r["shape"][0]:
        raise ValueError("Invalid token ID")
    q = r["quantization"]
    scale = np.fromfile(
        args.bundle_dir / q["scales_file"], "<f4", count=1, offset=4 * args.token_id
    )[0]
    raw = np.fromfile(
        args.bundle_dir / r["file"], np.uint8, count=384, offset=384 * args.token_id
    )
    codes = ((raw[:, None] >> np.arange(0, 8, 2)) & 3).reshape(-1)
    codes = np.where(codes >= 2, codes - 4, codes).astype(np.float32)
    multiplier = np.sqrt(np.float32(1536))
    pred = ((codes * scale) * multiplier).reshape(x.shape)
    hpred = bf(bf(codes * bf(scale)) * multiplier).reshape(x.shape)
    baseline = norm(x, w)
    variants = {
        "embedding_only": norm(hx, w),
        "coefficients_only": norm(x, bf(w)),
        "output_rounding_only": bf(baseline),
        "embedding_and_coefficients": norm(hx, bf(w)),
        "embedding_coefficients_and_output": bf(norm(hx, bf(w))),
    }
    module = "model.layers.0.self_attn.k_proj"
    activation_scale = np.fromfile(
        args.bundle_dir / tensors[module + ".input_scale"]["file"], "<f4"
    )[0]
    q0 = np.clip(np.rint(y / activation_scale), -128, 127)
    stages = {
        "hf_norm_only": np.clip(np.rint(hy / activation_scale), -128, 127),
        "hf_norm_and_scale_rounding": np.clip(
            np.rint(hy / bf(activation_scale)), -128, 127
        ),
        "hf_norm_scale_and_division_rounding": np.clip(
            np.rint(bf(hy / bf(activation_scale))), -128, 127
        ),
    }
    quant = {}
    previous = q0
    for label, value in stages.items():
        quant[label] = {
            "versus_static": metrics(q0, value),
            "codes_changed_from_previous_step": int(
                np.count_nonzero(previous != value)
            ),
        }
        previous = value
    index = int(np.argmax(np.abs(y - hy)))
    result = dict(
        token_id=args.token_id,
        embedding=dict(
            source_scale=float(scale),
            bf16_scale=float(bf(scale)),
            multiplier=float(multiplier),
            published_unit_code_value=float(scale * multiplier),
            hf_unit_code_value=float(bf(bf(scale) * multiplier)),
            nonzero_ratios=np.unique(hx[x != 0] / x[x != 0]).tolist(),
            published_calculation_vs_trace=metrics(x, pred),
            hf_calculation_vs_trace=metrics(hx, hpred),
            published_vs_hf=metrics(x, hx),
        ),
        norm=dict(
            fp32_calculation_vs_trace=metrics(y, baseline),
            ablations={
                label: {
                    "versus_published_trace": metrics(y, value),
                    "versus_hf_trace": metrics(hy, value),
                }
                for label, value in variants.items()
            },
            coefficient_rounding=metrics(w, bf(w)),
            worst_coordinate=dict(
                index=index,
                published=float(y.reshape(-1)[index]),
                hf=float(hy.reshape(-1)[index]),
                published_coefficient=float(w[index]),
                hf_coefficient=float(bf(w)[index]),
            ),
        ),
        activation_quantization=dict(
            source_scale=float(activation_scale),
            bf16_scale=float(bf(activation_scale)),
            static_codes_vs_trace=metrics(q0, a[module + ".input_codes"][0]),
            stages=quant,
        ),
    )
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(result, indent=2) + "\n")
    print(json.dumps(result, indent=2))


if __name__ == "__main__":
    main()
