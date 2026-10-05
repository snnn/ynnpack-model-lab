#!/usr/bin/env python3
# Copyright 2026 @snnn.
# SPDX-License-Identifier: Apache-2.0
"""Compare named floating-point observations from diagnostic trace runners."""

import argparse
import json
from pathlib import Path
import re

import numpy as np


def read_trace(directory):
    result = {}
    for line in (directory / "values.tsv").read_text().splitlines():
        label, name, dtype, shape = line.split("\t")
        dims = [int(x) for x in shape.split(",")]
        data = np.fromfile(
            directory / (label + "." + dtype),
            dtype={"f32": "<f4", "bf16": "<u2", "i8": "i1"}[dtype],
        )
        if dtype == "bf16":
            data = (data.astype(np.uint32) << 16).view(np.float32)
        result[label] = (data.reshape(dims), dtype, name)
    return result


def metrics(a, b):
    a, b = np.asarray(a, dtype=np.float64), np.asarray(b, dtype=np.float64)
    if a.shape != b.shape or not np.isfinite(a).all() or not np.isfinite(b).all():
        raise ValueError("Mismatched shape or nonfinite trace")
    delta = a - b
    norm = np.linalg.norm(a) * np.linalg.norm(b)
    return dict(
        elements=int(a.size),
        different=int(np.count_nonzero(delta)),
        max_abs_error=float(np.max(np.abs(delta), initial=0)),
        rms_error=float(np.sqrt(np.mean(delta**2))),
        reference_rms=float(np.sqrt(np.mean(a**2))),
        cosine=float(np.sum(a * b) / norm) if norm else None,
    )


def sequence_frames(directory):
    frames = []
    for path in directory.iterdir():
        match = re.fullmatch(r"\d+-prefill-p(\d+)-q(\d+)", path.name)
        if match:
            frames.append((int(match[1]), int(match[2]), path))
    frames.sort()
    end = 0
    for position, count, _ in frames:
        if position != end:
            raise ValueError("Trace must contain one contiguous prefill request")
        end += count
    if not frames:
        raise ValueError("No prefill frames")
    return frames


def read_sequence(frames, label):
    pieces, dtype = [], None
    for _, count, directory in frames:
        meta = next(
            line.split("\t")
            for line in (directory / "values.tsv").read_text().splitlines()
            if line.split("\t")[0] == label
        )
        _, _, kind, shape = meta
        dims = tuple(int(x) for x in shape.split(","))
        dtype = dtype or kind
        if dtype != kind:
            raise ValueError("Trace type changed between chunks")
        axis = 1 if dims[1] == count else 2
        if dims[axis] != count:
            raise ValueError("Cannot locate token axis: " + label)
        data = np.fromfile(
            directory / (label + "." + dtype),
            dtype={"f32": "<f4", "bf16": "<u2", "i8": "i1"}[dtype],
        )
        if dtype == "bf16":
            data = (data.astype(np.uint32) << 16).view(np.float32)
        pieces.append(np.moveaxis(data.reshape(dims), axis, 0))
    return np.concatenate(pieces, axis=0), dtype


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--reference", type=Path, required=True)
    p.add_argument("--candidate", type=Path, required=True)
    p.add_argument("--output", type=Path, required=True)
    p.add_argument(
        "--prefill-sequence",
        action="store_true",
        help="Align one request's prefill chunks by absolute token position",
    )
    args = p.parse_args()
    if args.prefill_sequence:
        af, bf = sequence_frames(args.reference), sequence_frames(args.candidate)
        a = read_trace(af[0][2])
        b = read_trace(bf[0][2])
    else:
        a, b = read_trace(args.reference), read_trace(args.candidate)
    records = []
    for name in sorted(a.keys() & b.keys()):
        if args.prefill_sequence:
            if ".attention." in name and name.rsplit(".", 1)[-1] not in (
                "query",
                "context",
            ):
                records.append(
                    dict(
                        label=name,
                        skipped="Use audit_attention_trace.py to align active key intervals",
                    )
                )
                continue
            x, xt = read_sequence(af, name)
            y, yt = read_sequence(bf, name)
        else:
            x, xt, _ = a[name]
            y, yt, _ = b[name]
        # Integer codes require explicit quantization scales, so do not compare
        # them directly with floating activations just because labels match.
        if x.shape != y.shape or ((xt == "i8") != (yt == "i8")):
            records.append(dict(label=name, skipped="shape or representation differs"))
            continue
        record = dict(
            label=name, reference_dtype=xt, candidate_dtype=yt, **metrics(x, y)
        )
        if args.prefill_sequence:
            changed = np.flatnonzero(np.any((x != y).reshape(x.shape[0], -1), axis=1))
            record.update(
                different_tokens=int(changed.size),
                first_different_token=int(changed[0]) if changed.size else None,
            )
        records.append(record)
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(records, indent=2) + "\n")
    print(len(records), "common named observations")


if __name__ == "__main__":
    main()
