#!/usr/bin/env python3
# Copyright 2026 @snnn.
# SPDX-License-Identifier: Apache-2.0
"""Check traced first-layer FCs with independent NumPy arithmetic.

The BF16 dot oracle accumulates in FP64 then converts through FP32 to BF16,
whereas backend kernels may accumulate in FP32. A difference from that oracle
is not by itself a bug.
The output fake-quantization check instead starts from the observed dot result.
"""

import argparse
import json
from pathlib import Path

import numpy as np

from audit_gemma4_sources import bf16_bits
from compare_value_traces import metrics, read_trace


def bf(x):
    return (bf16_bits(x).astype(np.uint32) << 16).view(np.float32)


def srq(x, scale):
    if scale == 0:
        return x
    s = bf(scale)
    return bf(bf(np.clip(np.rint(bf(x / s)), -128, 127)) * s)


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--asset-manifest", type=Path, required=True)
    p.add_argument("--bundle-dir", type=Path, required=True)
    p.add_argument("--control-trace", type=Path, required=True)
    p.add_argument("--hf-trace", type=Path, required=True)
    p.add_argument("--hf-arithmetic", choices=("bf16", "fp32"), default="bf16")
    p.add_argument("--output", type=Path, required=True)
    args = p.parse_args()
    hf = json.loads(args.asset_manifest.read_text())
    old = json.loads((args.bundle_dir / "manifest.json").read_text())
    tensors = {r["name"]: r for r in old["tensors"]}
    control, candidate = read_trace(args.control_trace), read_trace(args.hf_trace)
    rounding = (
        bf
        if args.hf_arithmetic == "bf16"
        else lambda x: np.asarray(x, dtype=np.float32)
    )

    def fake_quant(x, scale):
        if scale == 0:
            return x
        s = rounding(scale)
        return rounding(rounding(np.clip(np.rint(rounding(x / s)), -128, 127)) * s)

    def scalar(name):
        return np.fromfile(args.bundle_dir / tensors[name]["file"], "<f4")[0]

    results = []
    for tail in [
        "self_attn.k_proj",
        "self_attn.v_proj",
        "self_attn.q_proj",
        "self_attn.o_proj",
        "mlp.up_proj",
        "mlp.gate_proj",
        "mlp.down_proj",
    ]:
        module = "model.layers.0." + tail
        rec = tensors[module + ".weight"]
        raw = np.fromfile(args.bundle_dir / rec["file"], np.uint8)
        bits = int(rec["dtype"][3:])
        codes = ((raw[:, None] >> np.arange(0, 8, bits)) & ((1 << bits) - 1)).reshape(
            -1
        )
        codes = np.where(
            codes >= (1 << (bits - 1)), codes - (1 << bits), codes
        ).reshape(rec["shape"])
        ws = np.fromfile(args.bundle_dir / rec["quantization"]["scales_file"], "<f4")
        ins, outs = scalar(module + ".input_scale"), scalar(module + ".output_scale")
        x = control[module + ".input"][0]
        q = np.clip(np.rint(x / ins), -128, 127).astype(np.int64)
        exact = q @ codes.T.astype(np.int64)
        pred = np.clip(
            np.rint(exact.astype(np.float64) * float(ins) * ws / float(outs)), -128, 127
        )
        hx = candidate[module + ".input"][0]
        hw = rounding(codes.astype(np.float32) * rounding(ws[:, None]))
        hq = fake_quant(hx, hf["modules"][module]["input_scale"])
        hcodes = np.clip(np.rint(rounding(hx / rounding(ins))), -128, 127)
        dot_oracle = rounding(hq.astype(np.float64) @ hw.T.astype(np.float64))
        observed_dot = candidate[module + ".dot"][0]
        observed_output = candidate[module + ".output"][0]
        predicted_output = fake_quant(
            observed_dot, hf["modules"][module]["output_scale"]
        )
        results.append(
            dict(
                module=module,
                static_input_codes=metrics(q, control[module + ".input_codes"][0]),
                static_output_codes=metrics(pred, control[module + ".dot"][0]),
                bf16_dot_vs_fp64_oracle=metrics(dot_oracle, observed_dot),
                bf16_output_quantization=metrics(predicted_output, observed_output),
                static_vs_bf16_input_codes=metrics(q, hcodes),
                bf16_input_saturation=int(
                    np.count_nonzero(
                        (np.rint(rounding(hx / rounding(ins))) < -128)
                        | (np.rint(rounding(hx / rounding(ins))) > 127)
                    )
                ),
            )
        )
        if args.hf_arithmetic == "fp32":
            results[-1] = {k.replace("bf16", "fp32"): v for k, v in results[-1].items()}
    args.output.write_text(json.dumps(results, indent=2) + "\n")
    for r in results:
        print(
            r["module"],
            {k: v["max_abs_error"] for k, v in r.items() if isinstance(v, dict)},
        )


if __name__ == "__main__":
    main()
