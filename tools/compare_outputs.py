# Copyright 2026 @snnn.
# SPDX-License-Identifier: Apache-2.0
"""Compare diagnostic logits and KV dumps; requires NumPy, not the runtime."""

import argparse
import hashlib
import json
from pathlib import Path

import numpy as np


def dump_data(root, logits_only, execution):
    if not list(root.glob('*.logits.bin')):
        pattern = '*.f32' if logits_only else '*.f32*'
        return {p.name: p.read_bytes() for p in root.glob(pattern) if p.is_file()}
    rows = [json.loads(line) for line in (root/'timings.jsonl').read_text().splitlines()]
    result = {}
    if not logits_only:
        if execution is None:
            raise ValueError('Semantic-runner KV comparisons require --execution=execution.json')
        if execution['fixed_states'] or any(s['axis'] != 2 for s in execution['resources']):
            raise ValueError('Use compare_runtime.py for general recurrent/state contracts')
        capacity = json.loads((root/'run.json').read_text())['cache_capacity']
    for row in rows:
        if row['rep'] < 0:
            continue
        prefix = f"{row['case']}_r{row['rep']}_s{row['step']}"
        case = row['case'] if row['rep'] == 0 else f"{row['case']}_r{row['rep']}"
        name = case + ('.prefill.f32' if row['step'] == 0 else f".decode_{row['step']:04d}.f32")
        result[name] = (root/(prefix+'.logits.bin')).read_bytes()
        if logits_only:
            continue
        for state in execution['resources']:
            role, owner = state['name'].removeprefix('cache_').split('_')
            heads, width = state['shape'][1], state['shape'][-1]
            size, suffix = {'int8': (1, 'i8'), 'bf16': (2, 'bf16')}[state['dtype']]
            data = (root/f"{prefix}_{state['name']}.bin").read_bytes()
            if len(data) != heads * capacity * width * size:
                raise ValueError('KV byte count differs from execution contract')
            for head in range(heads):
                tail = f'.head{head}' if heads > 1 else ''
                start = head * capacity * width * size
                result[name+f'.owner{owner}{tail}.{role[0]}.{suffix}'] = data[start:start+row['position']*width*size]
    return result


def compare(reference, candidate, logits_only=False, execution=None):
    before, after = dump_data(reference, logits_only, execution), dump_data(candidate, logits_only, execution)
    files, other = sorted(before), sorted(after)
    if not files or files != other:
        raise ValueError("Missing or mismatched dump filenames")
    records = []
    exact = 0
    kv_changed, kv_count, kv_max = 0, 0, 0
    bf16_count, bf16_changed, bf16_max = 0, 0, 0.0
    for name in files:
        a, b = before[name], after[name]
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
    parser.add_argument("--execution", type=Path, help="Semantic execution contract for Gemma KV dumps")
    args = parser.parse_args()
    result = compare(args.reference, args.candidate, args.logits_only,
                     json.loads(args.execution.read_text()) if args.execution else None)
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(result, indent=2) + "\n")
    print(json.dumps({k: v for k, v in result.items() if k != "logits"}))


if __name__ == "__main__":
    main()
