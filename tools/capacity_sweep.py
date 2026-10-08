#!/usr/bin/env python3
# Copyright 2026 @snnn.
# SPDX-License-Identifier: Apache-2.0

"""Build and check capacity-only experiments for the benchmark harness."""

import argparse
import copy
import hashlib
import json
import math
from pathlib import Path
import statistics


def _settings(sweep):
    capacities = sweep["capacities"]
    if (len(capacities) < 2
            or any(type(c) is not int or c <= 0 for c in capacities)
            or capacities != sorted(set(capacities))):
        raise ValueError("capacities must contain at least two increasing positive integers")
    rounds = sweep.get("rounds", 2)
    if type(rounds) is not int or rounds < 2 or rounds % 2:
        raise ValueError("capacity rounds must be even and at least two")
    threshold = sweep.get("max_latency_change_percent", 10.0)
    if type(threshold) not in (float, int) or not math.isfinite(threshold) or threshold < 0:
        raise ValueError("max_latency_change_percent must be finite and nonnegative")
    return capacities, rounds, threshold


def expand_capacity_sweep(config):
    """Alternate capacity order, keeping every other runner argument fixed."""
    if "capacity_sweep" not in config:
        return config
    capacities, rounds, _ = _settings(config["capacity_sweep"])
    if not config["jobs"]:
        raise ValueError("capacity sweep needs at least one job")
    result = copy.deepcopy(config)
    result["jobs"] = []
    names = set()
    for job in config["jobs"]:
        if job["name"] in names:
            raise ValueError("capacity sweep job names must be unique")
        names.add(job["name"])
        argv = job["argv"]
        if (argv.count("--cache_capacity={capacity}") != 1
                or sum("{capacity}" in arg for arg in argv) != 1):
            raise ValueError("each sweep job needs exactly --cache_capacity={capacity}")
        for round_index in range(rounds):
            order = capacities if round_index % 2 == 0 else reversed(capacities)
            for capacity in order:
                expanded = copy.deepcopy(job)
                expanded.update(
                    name=f"{job['name']}-r{round_index + 1}-c{capacity}",
                    sweep_group=job["name"], sweep_round=round_index + 1,
                    capacity=capacity,
                )
                expanded["argv"] = [arg.replace("{capacity}", str(capacity)) for arg in argv]
                result["jobs"].append(expanded)
    return result


def check_capacity_sweep(config, directory):
    """Compare warm latencies; invalid or unmatched experiments fail explicitly."""
    capacities, rounds, threshold = _settings(config["capacity_sweep"])
    reference_capacity = capacities[0]
    groups = {}
    for job in config["jobs"]:
        groups.setdefault(job["sweep_group"], []).append(job)
    if not groups:
        raise ValueError("no expanded capacity jobs found")
    report = {
        "version": 1,
        "verdict": "pass",
        "max_latency_change_percent": threshold,
        "metric_scope": "Warm request latency; excludes setup, dumps and profiling. "
                        "Ratio is the median of paired round mean-latency ratios.",
        "interpretation": "A threshold crossing flags capacity-sensitive timings; "
                          "repeat under comparable clocks and temperatures to confirm.",
        "groups": [],
    }
    for name, jobs in groups.items():
        captures = {}
        identity = None
        case_keys = None
        greedy = {}
        processes = []
        for job in jobs:
            job_dir = Path(directory) / job["name"]
            capture = job_dir / "capture"
            run = json.loads((capture / "run.json").read_text())
            status = json.loads((job_dir / "status.json").read_text())
            if status["returncode"] != 0:
                raise ValueError(f"{job['name']}: runner failed")
            if (run.get("timings_valid_for_benchmark") is not True
                    or run.get("profile_execution", "none") != "none"
                    or run.get("report_memory", False)):
                raise ValueError(f"{job['name']}: diagnostic timings cannot test capacity")
            if run.get("warmups", 0) < 1 or run.get("repetitions", 0) < 3:
                raise ValueError("capacity checks require a warmup and at least three requests")
            capacity = run.pop("cache_capacity")
            if capacity != job["capacity"]:
                raise ValueError(f"{job['name']}: captured capacity differs from job")
            fixture = (capture / "resolved_cases.tsv").read_bytes()
            argv = ["--cache_capacity={capacity}" if arg == f"--cache_capacity={capacity}" else arg
                    for arg in job["argv"]]
            current_identity = (run, fixture, argv, job.get("engine"))
            if identity is None:
                identity = current_identity
            elif identity != current_identity:
                raise ValueError(f"{name}: inputs, runner arguments or settings differ")
            expected_cases = set()
            for line in fixture.decode("utf-8").splitlines():
                if not line or line.startswith("#"):
                    continue
                case_name, prompt, continuation = line.split("\t")
                expected_cases.add((case_name, len(prompt.split(",")),
                                    0 if continuation == "-" else len(continuation.split(","))))
            key = (job["sweep_round"], capacity)
            if key in captures:
                raise ValueError(f"{name}: duplicate round/capacity")
            observations = json.loads((job_dir / "summary.json").read_text())
            cases = {}
            repetitions = set()
            for row in observations:
                if row["warmup"]:
                    continue
                if row.get("timings_valid_for_benchmark") is not True:
                    raise ValueError(f"{job['name']}: invalid request timing")
                case = (row["case"], row["prompt_tokens"], len(row["decode_token_ms"]))
                if case[2] == 0:
                    raise ValueError("capacity checks need subsequent decode tokens")
                repetition = (case, row["repetition"])
                if repetition in repetitions:
                    raise ValueError(f"{job['name']}: duplicate request")
                repetitions.add(repetition)
                if row.get("view_copy_bytes") != 0:
                    raise ValueError(f"{job['name']}: history view copied")
                if case not in greedy:
                    greedy[case] = row["argmax"]
                elif greedy[case] != row["argmax"]:
                    raise ValueError(f"{name}: argmax sequence changed across requests/capacities")
                cases.setdefault(case, []).append(row)
            expected_repetitions = {(case, r) for case in expected_cases
                                    for r in range(run["repetitions"])}
            if not cases or repetitions != expected_repetitions:
                raise ValueError(f"{job['name']}: incomplete measured requests")
            if case_keys is None:
                case_keys = set(cases)
            elif set(cases) != case_keys:
                raise ValueError(f"{name}: case names, prompt or continuation lengths differ")
            captures[key] = cases
            processes.append({
                "job": job["name"], "round": key[0], "capacity": capacity,
                "setup_ms": next(iter(cases.values()))[0]["setup_ms"],
                "peak_rss_mib": max(row["peak_rss_mib"] for rows in cases.values() for row in rows),
            })
        expected = {(r, c) for r in range(1, rounds + 1) for c in capacities}
        if set(captures) != expected:
            raise ValueError(f"{name}: incomplete capacity rounds")
        group = {
            "name": name, "reference_capacity": reference_capacity,
            "resolved_cases_sha256": hashlib.sha256(identity[1]).hexdigest(),
            "argmax_equal": True, "processes": processes, "comparisons": [],
        }
        for case in sorted(case_keys):
            for capacity in capacities[1:]:
                comparison = {
                    "case": case[0], "prompt_tokens": case[1],
                    "continuations": case[2], "capacity": capacity, "metrics": {},
                }
                for metric in ("prefix_ms", "ttft_ms", "decode_ms"):
                    if metric == "prefix_ms" and case[1] == 1:
                        continue
                    paired = []
                    for round_index in range(1, rounds + 1):
                        control = [row[metric] for row in captures[round_index, reference_capacity][case]]
                        candidate = [row[metric] for row in captures[round_index, capacity][case]]
                        if any(type(v) not in (int, float) or not math.isfinite(v) or v <= 0
                               for v in control + candidate):
                            raise ValueError(f"{name}/{case[0]}: invalid {metric}")
                        control_mean, candidate_mean = statistics.mean(control), statistics.mean(candidate)
                        paired.append({
                            "round": round_index,
                            "reference_mean_ms": control_mean, "capacity_mean_ms": candidate_mean,
                            "reference_range_ms": [min(control), max(control)],
                            "capacity_range_ms": [min(candidate), max(candidate)],
                            "latency_ratio": candidate_mean / control_mean,
                        })
                    ratio = statistics.median(pair["latency_ratio"] for pair in paired)
                    verdict = ("capacity_sensitive" if ratio < 1 - threshold / 100
                               or ratio > 1 + threshold / 100 else "pass")
                    comparison["metrics"][metric] = {
                        "latency_ratio": ratio, "slowdown_percent": (ratio - 1) * 100,
                        "verdict": verdict, "rounds": paired,
                    }
                    if verdict != "pass":
                        report["verdict"] = verdict
                group["comparisons"].append(comparison)
        report["groups"].append(group)
    return report


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("directory", type=Path, help="Existing benchmark output directory")
    args = parser.parse_args()
    config = json.loads((args.directory / "config.json").read_text())
    report = check_capacity_sweep(config, args.directory)
    (args.directory / "capacity-check.json").write_text(json.dumps(report, indent=2) + "\n")
    print("Capacity check:", report["verdict"])
    if report["verdict"] != "pass":
        raise SystemExit(1)


if __name__ == "__main__":
    main()
