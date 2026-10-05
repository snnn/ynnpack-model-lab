# Copyright 2026 @snnn.
# SPDX-License-Identifier: Apache-2.0
"""Compare diagnostic logits and KV dumps; requires NumPy, not the runtime."""

import argparse
import hashlib
import json
from pathlib import Path

import numpy as np


def compare(reference, candidate, logits_only=False):
    pattern = "*.f32" if logits_only else "*.f32*"
    files = sorted(p.name for p in reference.glob(pattern) if p.is_file())
    other = sorted(p.name for p in candidate.glob(pattern) if p.is_file())
    if not files or files != other:
        raise ValueError("Missing or mismatched dump filenames")
    records = []
    exact = 0
    kv_changed, kv_count, kv_max = 0, 0, 0
    bf16_count, bf16_changed, bf16_max = 0, 0, 0.0
    for name in files:
        a, b = (reference / name).read_bytes(), (candidate / name).read_bytes()
        if len(a) != len(b):
            raise ValueError(f"Dump size mismatch: {name}")
        exact += a == b
        if name.endswith(".i8"):
            x = np.frombuffer(a, dtype=np.int8).astype(np.int16)
            y = np.frombuffer(b, dtype=np.int8).astype(np.int16)
            kv_changed += int(np.count_nonzero(x != y))
            kv_count += x.size
            kv_max = max(kv_max, int(np.max(np.abs(x - y), initial=0)))
            continue
        if name.endswith(".bf16"):
            x = (np.frombuffer(a, dtype="<u2").astype(np.uint32) << 16).view(np.float32)
            y = (np.frombuffer(b, dtype="<u2").astype(np.uint32) << 16).view(np.float32)
            if not np.all(np.isfinite(x)) or not np.all(np.isfinite(y)):
                raise ValueError(f"Nonfinite BF16 KV: {name}")
            bf16_count += x.size
            bf16_changed += int(np.count_nonzero(x != y))
            bf16_max = max(bf16_max, float(np.max(np.abs(x-y), initial=0)))
            continue
        if not name.endswith(".f32"):
            raise ValueError(f"Unknown dump type: {name}")
        x = np.frombuffer(a, dtype="<f4").astype(np.float64)
        y = np.frombuffer(b, dtype="<f4").astype(np.float64)
        if not np.all(np.isfinite(x)) or not np.all(np.isfinite(y)):
            raise ValueError(f"Nonfinite logits: {name}")
        xc, yc = x - x.mean(), y - y.mean()
        norm = np.linalg.norm(xc) * np.linalg.norm(yc)
        logp = x - x.max()
        logp -= np.log(np.exp(logp).sum())
        logq = y - y.max()
        logq -= np.log(np.exp(logq).sum())
        records.append(
            {
                "file": name,
                "reference_sha256": hashlib.sha256(a).hexdigest(),
                "candidate_sha256": hashlib.sha256(b).hexdigest(),
                "max_abs_error": float(np.max(np.abs(x - y))),
                "centered_cosine": float(np.dot(xc, yc) / norm) if norm else None,
                "kl_reference_to_candidate": float(
                    np.sum(np.exp(logp) * (logp - logq))
                ),
                "reference_argmax": int(x.argmax()),
                "candidate_argmax": int(y.argmax()),
            }
        )
    return {
        "files": len(files),
        "byte_identical": exact,
        "logit_outputs": len(records),
        "argmax_agreement": sum(
            r["reference_argmax"] == r["candidate_argmax"] for r in records
        ),
        "kv_elements": kv_count,
        "kv_different": kv_changed,
        "kv_max_code_error": kv_max,
        "bf16_kv_elements": bf16_count,
        "bf16_kv_different": bf16_changed,
        "bf16_kv_max_abs_error": bf16_max,
        "logits": records,
    }


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--reference", type=Path, required=True)
    parser.add_argument("--candidate", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    parser.add_argument("--logits-only", action="store_true")
    args = parser.parse_args()
    result = compare(args.reference, args.candidate, args.logits_only)
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(result, indent=2) + "\n")
    print(json.dumps({k: v for k, v in result.items() if k != "logits"}))


if __name__ == "__main__":
    main()
