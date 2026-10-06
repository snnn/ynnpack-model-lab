#!/usr/bin/env python3
# Copyright 2026 @snnn.
# SPDX-License-Identifier: Apache-2.0
"""Filter Android simpleperf samples to measured decode execution intervals.

Requires the NDK's simpleperf_report_lib.py. Reports exclusive instruction
pointer cycle shares, not wall-time attribution or a callchain profile.
"""

import argparse
from bisect import bisect_right
from collections import defaultdict
import json
from pathlib import Path
import sys


def merge_intervals(intervals):
    merged = []
    for start, end in sorted(intervals):
        if end < start:
            raise ValueError("Negative execution interval")
        if merged and start <= merged[-1][1]:
            merged[-1] = (merged[-1][0], max(end, merged[-1][1]))
        else:
            merged.append((start, end))
    return merged


def decode_intervals(ynn=None, native=None):
    if ynn:
        with Path(ynn).open() as stream:
            metadata = json.loads(next(stream))
            envelopes = {c["id"] for c in metadata["calls"] if c["envelope"]}
            intervals = []
            for line in stream:
                step = json.loads(line)
                if not step["complete"] or step["dropped_events"]:
                    raise ValueError("Incomplete execution trace")
                intervals.extend((start, end) for _, call, start, end in step["events"]
                                 if call in envelopes)
        scope = "measured_subsequent_decode_graph_run"
    else:
        intervals = []
        for path in sorted(Path(native).glob("*_stages.jsonl")):
            operators = [json.loads(line) for line in path.with_name(
                path.name.replace("_stages", "_operators")).read_text().splitlines()]
            for line in path.read_text().splitlines():
                stage = json.loads(line)
                samples = [op["samples_ns"] for op in operators
                           if op["layer"] == stage["layer"]]
                starts = stage["invoke_start_ns"]
                if not samples or any(len(s) != len(starts) for s in samples):
                    raise ValueError("Native stage/operator sample mismatch")
                # Operator durations telescope from runtime start to last
                # operator completion. Avoid including host profile collection.
                for i, start in enumerate(starts):
                    duration = sum(s[i] for s in samples)
                    if duration < 0 or duration > stage["wall_ns"][i]:
                        raise ValueError("Invalid native invocation duration")
                    intervals.append((start, start + duration))
        scope = "measured_subsequent_decode_native_invocations"
    if not intervals:
        raise ValueError("No measured execution intervals")
    return merge_intervals(intervals), scope


def summarize(record, intervals, report_library):
    lib = report_library(str(record))
    try:
        if lib.MetaInfo().get("clockid") != "monotonic":
            raise ValueError("Record with simpleperf --clockid monotonic")
        starts = [start for start, _ in intervals]
        symbols = defaultdict(lambda: {"samples": 0, "cycles": 0})
        cpus = defaultdict(int)
        sampled, included = 0, 0
        while (sample := lib.GetNextSample()) is not None:
            sampled += 1
            index = bisect_right(starts, sample.time) - 1
            if index < 0 or sample.time > intervals[index][1]:
                continue
            if lib.GetEventOfCurrentSample().name != "cpu-cycles:u":
                raise ValueError("Expected cpu-cycles:u samples")
            symbol = lib.GetSymbolOfCurrentSample()
            key = symbol.symbol_name, Path(symbol.dso_name).name
            # Unknown addresses are deliberately aggregated without publishing
            # process-specific addresses or device paths.
            if key[0].startswith("0x"):
                key = "unknown", key[1]
            symbols[key]["samples"] += 1
            symbols[key]["cycles"] += sample.period
            cpus[sample.cpu] += 1
            included += 1
        if not included:
            raise ValueError("No CPU samples overlap measured decode")
        total = sum(value["cycles"] for value in symbols.values())
        return {"measurement": "exclusive_instruction_pointer_cpu_cycles",
                "recorded_samples": sampled, "included_samples": included,
                "included_cycles": total, "samples_by_cpu": dict(cpus),
                "symbols": [{"symbol": symbol, "binary": binary, **value,
                             "cycle_percent": value["cycles"] * 100 / total}
                            for (symbol, binary), value in sorted(
                                symbols.items(), key=lambda item: -item[1]["cycles"])]}
    finally:
        lib.Close()


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--simpleperf-dir", type=Path, required=True,
                        help="NDK simpleperf directory containing simpleperf_report_lib.py")
    parser.add_argument("--record", type=Path, required=True)
    source = parser.add_mutually_exclusive_group(required=True)
    source.add_argument("--ynn", type=Path)
    source.add_argument("--native", type=Path)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    sys.path.insert(0, str(args.simpleperf_dir))
    from simpleperf_report_lib import GetReportLib

    intervals, scope = decode_intervals(args.ynn, args.native)
    result = summarize(args.record, intervals, GetReportLib)
    result["scope"] = scope
    result["interval_count"] = len(intervals)
    args.output.write_text(json.dumps(result, indent=2) + "\n")
    print("Measured decode samples:", result["included_samples"],
          "of", result["recorded_samples"])


if __name__ == "__main__":
    main()
