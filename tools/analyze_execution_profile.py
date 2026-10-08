#!/usr/bin/env python3
# Copyright 2026 @snnn.
# SPDX-License-Identifier: Apache-2.0
"""Summarize scheduled YNNPACK worker work and native operator wall profiles.

Callback interval unions and summed worker time are different measurements.
Native XNNPACK operator durations include dispatch and threadpool joins. This
tool keeps those quantities separate, including explicit unknown attribution.
"""

import argparse
from collections import defaultdict
import json
from pathlib import Path
import re
import statistics


def union_ns(intervals):
    total, end = 0, None
    for start, stop in sorted(intervals):
        if stop < start:
            raise ValueError("Negative profile interval")
        total += max(0, stop - max(start, end if end is not None else start))
        end = max(stop, end if end is not None else stop)
    return total


def classify(call, operations):
    origins = [operations[i] for i in call["origins"]]
    scopes = {o["scope"] for o in origins}
    layers = {int(m.group(1)) for s in scopes if (m := re.search(r"(?:^|/)Layer(\d+)(?:/|$)", s))}
    layer = next(iter(layers)) if len(layers) == 1 else "shared" if layers else "outside_layers"
    name = call["name"].lower()
    scope = " ".join(sorted(scopes))
    if not origins:
        category = "unattributed"
    elif "pack" in name or "transpose_a" in name:
        category = "packing"
    elif name == "copy" or "memcpy" in name:
        category = "kv_append" if "CacheUpdate" in scope else "copy"
    elif "dot" in name:
        if "/Sdpa" in scope:
            names = " ".join(n for o in origins for n in o.get("input_names", []))
            category = "attention_pv" if "Softmax" in names else "attention_qk"
        else:
            category = "head_fc" if "FinalNormAndHead" in scope else "fc"
            types = call.get("backend_input_types", [])
            for precision in ("int2", "int4", "int8"):
                if precision in types[1:]:
                    category += "_" + precision
                    break
    elif "CacheUpdate" in scope:
        category = "kv_update"
    elif "/Sdpa" in scope:
        category = "attention_other"
    elif "Rope" in scope:
        category = "rope"
    elif any("quantiz" in o["kind"] for o in origins):
        category = "quantization"
    else:
        category = "elementwise_norm_other"
    return layer, category


def event_stats(events):
    workers = defaultdict(list)
    for worker, start, end in events:
        workers[worker].append((start, end))
    return {"calls": len(events),
            "interval_union_ms": union_ns([(s, e) for _, s, e in events]) / 1e6,
            "worker_ms": sum(union_ns(intervals) for intervals in workers.values()) / 1e6}


def attention_category(call, operations):
    """Split SDPA work without counting operation origins as extra calls."""
    origins = [operations[i] for i in call["origins"]]
    attention = ["/Attention/Sdpa" in o["scope"] for o in origins]
    if not any(attention):
        return None
    if not all(attention):
        return "mixed_origins"
    name = call["name"].lower()
    if "pack" in name or "transpose_a" in name:
        return "packing"
    if "dot" in name:
        return classify(call, operations)[1].removeprefix("attention_")
    if name == "dequantize":
        return "dequantization"
    return "mask_softmax_other"


def attention_wall_partition(wall_ms, attention_events, other_events):
    """Partition wall coverage; gaps and overlapping categories stay explicit."""
    attention = event_stats(attention_events)["interval_union_ms"]
    other = event_stats(other_events)["interval_union_ms"]
    busy = event_stats(attention_events + other_events)["interval_union_ms"]
    overlap = max(0.0, attention + other - busy)
    return {"attention_only_ms": max(0.0, attention - overlap),
            "other_callbacks_only_ms": max(0.0, other - overlap),
            "attention_other_overlap_ms": overlap,
            "outside_callbacks_ms": max(0.0, wall_ms - busy)}


def aggregate_attention(steps):
    categories = defaultdict(list)
    for step in steps:
        for category in step["attention_categories"]:
            categories[category["category"]].append(category)
    return {"steps": len(steps),
            "history_min": min(s["history"] for s in steps),
            "history_max": max(s["history"] for s in steps),
            "mean_wall_ms": statistics.mean(s["wall_ms"] for s in steps),
            "mean_attention_callback_worker_ms": statistics.mean(
                s["attention_callback_worker_ms"] for s in steps),
            "mean_attention_callback_busy_wall_ms": statistics.mean(
                s["attention_callback_busy_wall_ms"] for s in steps),
            "mean_wall_partition": {
                key: statistics.mean(s["wall_partition"][key] for s in steps)
                for key in steps[0]["wall_partition"]},
            "categories": [{"category": category,
                            "mean_calls_per_step": sum(g["calls"] for g in groups) / len(steps),
                            "mean_worker_ms": sum(g["worker_ms"] for g in groups) / len(steps),
                            "mean_interval_union_ms": sum(g["interval_union_ms"] for g in groups) / len(steps)}
                           for category, groups in categories.items()]}


def summarize_ynn(path):
    with Path(path).open() as stream:
        metadata = json.loads(next(stream))
        operations = {o["id"]: o for o in metadata["operations"]}
        calls = {c["id"]: c for c in metadata["calls"]}
        attention_kinds = {i: attention_category(call, operations)
                           for i, call in calls.items() if not call["envelope"]}
        results = []
        call_totals = defaultdict(lambda: {"calls": 0, "worker_ms": 0, "interval_union_ms": 0})
        for line in stream:
            step = json.loads(line)
            if step["type"] != "step" or not step["complete"] or step["dropped_events"]:
                raise ValueError("Incomplete execution trace")
            groups = defaultdict(list)
            categories = defaultdict(list)
            call_events = defaultdict(list)
            attention_categories = defaultdict(list)
            attention_events, other_events = [], []
            worker_intervals, graph_intervals = defaultdict(list), []
            for worker, call_id, start, end in step["events"]:
                if not step["start_ns"] <= start <= end <= step["end_ns"]:
                    raise ValueError("Event outside decode step")
                call = calls[call_id]
                if call["envelope"]:
                    graph_intervals.append((start, end))
                    continue
                layer, category = classify(call, operations)
                groups[layer, category].append((worker, start, end))
                categories[category].append((worker, start, end))
                call_events[call_id].append((worker, start, end))
                worker_intervals[worker].append((start, end))
                kind = attention_kinds[call_id]
                if kind is not None:
                    attention_events.append((worker, start, end))
                    attention_categories[kind].append((worker, start, end))
                else:
                    other_events.append((worker, start, end))
            for call_id, events in call_events.items():
                for key, value in event_stats(events).items():
                    call_totals[call_id][key] += value
            busy_ns = union_ns([(s, e) for events in worker_intervals.values() for s, e in events])
            wall_ns = step["end_ns"] - step["start_ns"]
            results.append({
                "case": step["case"], "repetition": step["repetition"], "step": step["step"],
                "position": step["position"], "history": step["history"],
                "wall_ms": wall_ns / 1e6,
                "graph_run_ms": union_ns(graph_intervals) / 1e6,
                "callback_busy_wall_ms": busy_ns / 1e6,
                "callback_worker_ms": sum(union_ns(v) for v in worker_intervals.values()) / 1e6,
                "outside_callbacks_ms": (wall_ns - busy_ns) / 1e6,
                "attention_callback_worker_ms": event_stats(attention_events)["worker_ms"],
                "attention_callback_busy_wall_ms": event_stats(attention_events)["interval_union_ms"],
                "wall_partition": attention_wall_partition(
                    wall_ns / 1e6, attention_events, other_events),
                "attention_categories": [{"category": category, **event_stats(events)}
                                         for category, events in attention_categories.items()],
                "categories": [{"category": category, **event_stats(events)}
                               for category, events in categories.items()],
                "groups": [{"layer": layer, "category": category, **event_stats(events)}
                           for (layer, category), events in groups.items()],
            })
    if not results:
        raise ValueError("No measured decode steps")
    aggregates = defaultdict(list)
    category_aggregates = defaultdict(list)
    for result in results:
        for group in result["groups"]:
            aggregates[group["layer"], group["category"]].append(group)
        for group in result["categories"]:
            category_aggregates[group["category"]].append(group)
    return {"timing_scope": metadata["scope"], "steps": results,
            "attention": {
                "timing_scope": "diagnostic_callback_work_and_wall_coverage_not_critical_path",
                "all_steps": aggregate_attention(results),
                "cases": [{"case": case, **aggregate_attention(
                    [s for s in results if s["case"] == case])}
                          for case in sorted({s["case"] for s in results})]},
            "mean_wall_ms": statistics.mean(s["wall_ms"] for s in results),
            "mean_outside_callbacks_ms": statistics.mean(s["outside_callbacks_ms"] for s in results),
            "calls": [{"id": call_id, "name": calls[call_id]["name"],
                       "origins": [operations[i] for i in calls[call_id]["origins"]],
                       "backend_input_types": calls[call_id].get("backend_input_types", []),
                       "mean_calls_per_step": totals["calls"] / len(results),
                       "mean_worker_ms": totals["worker_ms"] / len(results),
                       "mean_interval_union_ms": totals["interval_union_ms"] / len(results)}
                      for call_id, totals in call_totals.items()],
            "categories": [{"category": category,
                            "mean_calls_per_step": sum(g["calls"] for g in groups) / len(results),
                            "mean_worker_ms": sum(g["worker_ms"] for g in groups) / len(results),
                            "mean_interval_union_ms": sum(g["interval_union_ms"] for g in groups) / len(results)}
                           for category, groups in category_aggregates.items()],
            "groups": [{"layer": layer, "category": category,
                        "mean_calls_per_step": sum(g["calls"] for g in groups) / len(results),
                        "mean_worker_ms": sum(g["worker_ms"] for g in groups) / len(results),
                        "mean_interval_union_ms": sum(g["interval_union_ms"] for g in groups) / len(results)}
                       for (layer, category), groups in aggregates.items()]}


def summarize_native(directory):
    operators, stages = [], []
    for path in sorted(Path(directory).glob("*_operators.jsonl")):
        stage = path.name.removesuffix("_operators.jsonl")
        for line in path.read_text().splitlines():
            row = json.loads(line)
            values = row["samples_ns"]
            if not values or any(v < 0 for v in values):
                raise ValueError("Invalid native operator samples")
            operators.append({**row, "stage": stage, "mean_operator_wall_ms": statistics.mean(values) / 1e6})
    for path in sorted(Path(directory).glob("*_stages.jsonl")):
        stage = path.name.removesuffix("_stages.jsonl")
        for line in path.read_text().splitlines():
            row = json.loads(line)
            samples = row["wall_ns"]
            objects = [o for o in operators if o["stage"] == stage and o["layer"] == row["layer"]]
            if any(len(o["samples_ns"]) != len(samples) for o in objects):
                raise ValueError("Native stage/operator sample mismatch")
            totals = [sum(o["samples_ns"][i] for o in objects) for i in range(len(samples))]
            if any(total > wall for total, wall in zip(totals, samples)):
                raise ValueError("Native operator work exceeds stage wall time")
            stages.append({**row, "stage": stage,
                           "mean_stage_wall_ms": statistics.mean(samples) / 1e6,
                           "mean_operator_wall_ms": statistics.mean(totals) / 1e6})
    if not stages:
        raise ValueError("No native operator profile")
    return {"timing_scope": "operator_wall_including_dispatch_and_threadpool_join",
            "operators": operators, "stages": stages,
            "mean_total_stage_wall_ms": sum(s["mean_stage_wall_ms"] for s in stages)}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--ynn", type=Path)
    parser.add_argument("--native", type=Path)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    if not args.ynn and not args.native:
        parser.error("Provide --ynn and/or --native")
    result = {}
    if args.ynn:
        result["ynn"] = summarize_ynn(args.ynn)
    if args.native:
        result["native"] = summarize_native(args.native)
    args.output.write_text(json.dumps(result, indent=2) + "\n")
    print({engine: {k: v for k, v in summary.items() if k.startswith("mean_")}
           for engine, summary in result.items()})


if __name__ == "__main__":
    main()
