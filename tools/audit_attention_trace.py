#!/usr/bin/env python3
# Copyright 2026 @snnn.
# SPDX-License-Identifier: Apache-2.0
"""Compare one local-attention query across differently chunked HF traces.

Aligns absolute key positions, checks masked probabilities, and uses FP64
arithmetic as a diagnostic oracle, converting through FP32 to BF16. Does not
require exact oracle agreement from FP32-accumulating backend kernels. Requires
NumPy.
"""

import argparse
import json
from pathlib import Path

import numpy as np

from audit_gemma4_fc_trace import bf
from compare_value_traces import metrics, read_trace, sequence_frames


def query(directory, token, layer, window):
    frames = sequence_frames(directory)
    position, count, path = next(f for f in frames if f[0] <= token < f[0] + f[1])
    data = read_trace(path)
    begin = max(0, position - window + 1)
    valid_begin = max(0, token - window + 1)
    lo, hi = valid_begin - begin, token + 1 - begin
    row = token - position
    prefix = f"model.layers.{layer}.attention."
    result = {}
    for name in [
        "query",
        "keys",
        "values",
        "scores",
        "masked_scores",
        "probabilities_fp32",
        "probabilities",
        "context",
    ]:
        x = data[prefix + name][0]
        if name in ("keys", "values"):
            x = x[0, 0, lo:hi]
        elif name in ("query", "context"):
            x = x[0, :, row]
        else:
            x = x[0, :, row, lo:hi]
        result[name] = x
    probabilities = data[prefix + "probabilities"][0][0, :, row]
    masked = data[prefix + "masked_scores"][0][0, :, row]
    outside = np.ones(probabilities.shape[-1], dtype=bool)
    outside[lo:hi] = False
    info = dict(
        chunk_position=position,
        query_rows=count,
        history_begin=begin,
        history_end=position + count,
        valid_begin=valid_begin,
        valid_end=token + 1,
        active_key_extent=int(probabilities.shape[-1]),
        nonzero_masked_probabilities=int(np.count_nonzero(probabilities[:, outside])),
        masked_scores_not_negative_infinity=int(
            np.count_nonzero(~np.isneginf(masked[:, outside]))
        ),
    )
    if probabilities.shape[-1] != position + count - begin:
        raise ValueError("Unexpected active key extent")
    return result, info


def oracles(data):
    scores = data["scores"].astype(np.float64)
    p = np.exp(scores - scores.max(axis=-1, keepdims=True))
    p /= p.sum(axis=-1, keepdims=True)
    context = bf(
        data["probabilities"].astype(np.float64) @ data["values"].astype(np.float64)
    )
    return dict(
        scores=metrics(
            bf(data["query"].astype(np.float64) @ data["keys"].T.astype(np.float64)),
            data["scores"],
        ),
        probabilities=metrics(bf(p), data["probabilities"]),
        context=metrics(context, data["context"]),
    )


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--reference", type=Path, required=True)
    p.add_argument("--candidate", type=Path, required=True)
    p.add_argument("--layer", type=int, required=True)
    p.add_argument("--token", type=int, required=True)
    p.add_argument("--window", type=int, default=512)
    p.add_argument("--output", type=Path, required=True)
    args = p.parse_args()
    a, ai = query(args.reference, args.token, args.layer, args.window)
    b, bi = query(args.candidate, args.token, args.layer, args.window)
    result = dict(
        layer=args.layer,
        token=args.token,
        reference_bounds=ai,
        candidate_bounds=bi,
        comparison={k: metrics(a[k], b[k]) for k in a},
        reference_vs_fp64_oracle=oracles(a),
        candidate_vs_fp64_oracle=oracles(b),
    )
    args.output.write_text(json.dumps(result, indent=2) + "\n")
    print(json.dumps(result, indent=2))


if __name__ == "__main__":
    main()
