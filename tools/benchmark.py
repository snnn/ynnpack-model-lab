#!/usr/bin/env python3
# Copyright 2026 The LiteRT Authors.
# Copyright 2026 @snnn.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# https://www.apache.org/licenses/LICENSE-2.0
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

"""Run an explicit local/ADB command matrix and preserve raw measurements.

The JSON configuration contains optional `serial`, `remote_root`, and
`cooldown_seconds`, and a list of `jobs`: {name, engine, argv}. Each argv is an
array, not shell text. A literal {output} is replaced with a fresh output
directory. Models, binaries, fixtures and cache files must already be present.
No device CPU governors or power settings are changed.
An optional capacity_sweep expands --cache_capacity={capacity} into alternating
capacity rounds and checks warm prefill/decode latency after collection.
"""

import argparse
import json
from pathlib import Path
import shlex
import statistics
import subprocess
import time

if __package__:
    from .capacity_sweep import check_capacity_sweep, expand_capacity_sweep
else:
    from capacity_sweep import check_capacity_sweep, expand_capacity_sweep


def save(path, value):
    path.write_text(json.dumps(value, indent=2) + "\n")


def capture_capacity_telemetry(adb, directory, when):
    result = subprocess.run(adb + ["shell", "\n".join([
        'for p in /sys/devices/system/cpu/cpufreq/policy*; do',
        'echo "$p"; cat "$p/scaling_cur_freq" "$p/scaling_max_freq" "$p/scaling_governor"',
        'done',
        'for p in /sys/class/thermal/thermal_zone*; do',
        'echo "$p"; cat "$p/type" "$p/temp"',
        'done',
    ])], capture_output=True, text=True, timeout=30)
    (directory / f"telemetry-{when}.txt").write_text(result.stdout + result.stderr)


def summarize(directory):
    rows = []
    timings = directory / "timings.jsonl"
    if timings.exists():
        raw = [json.loads(s) for s in timings.read_text().splitlines()]
        for case, rep in sorted({(r["case"], r["repetition"]) for r in raw}):
            r = [v for v in raw if v["case"] == case and v["repetition"] == rep]
            assert [v["step"] for v in r] == list(range(len(r)))
            first = r[0]
            decode = [v["token_ms"] for v in r[1:]]
            prompt_tokens = first["context"]
            ttft_ms = first["prefix_ms"] + first["token_ms"]
            rows.append(
                {
                    "case": case,
                    "repetition": rep,
                    "warmup": rep < 0,
                    "prompt_tokens": prompt_tokens,
                    "ttft_ms": ttft_ms,
                    "prefix_ms": first["prefix_ms"],
                    "prefill_tok_s": (
                        (prompt_tokens - 1) * 1000 / first["prefix_ms"]
                        if prompt_tokens > 1 and first["prefix_ms"] > 0
                        else None
                    ),
                    "prompt_over_ttft_tok_s": prompt_tokens * 1000 / ttft_ms,
                    "decode_ms": statistics.mean(decode) if decode else None,
                    "decode_tok_s": 1000 / statistics.mean(decode) if decode else None,
                    "decode_token_ms": decode,
                    "setup_ms": first["setup_ms"],
                    "peak_rss_mib": max(v["peak_rss_kib"] for v in r) / 1024,
                    "argmax": [v["argmax"] for v in r],
                    "last_append_bytes": r[-1].get("append_bytes"),
                    "view_copy_bytes": r[-1].get("view_copy_bytes"),
                }
            )
    else:
        for path in sorted(directory.glob("*.json")):
            raw = json.loads(path.read_text())
            if "passes" not in raw:
                continue
            passes = raw["passes"]
            decode = [v["elapsed_ms"] for v in passes[1:]]
            rows.append(
                {
                    "case": raw.get("case_id", path.stem),
                    "repetition": raw["run_index"],
                    "warmup": raw["warmup"],
                    "ttft_ms": passes[0]["elapsed_ms"],
                    "prefix_ms": None,
                    "decode_ms": statistics.mean(decode) if decode else None,
                    "decode_token_ms": decode,
                    "setup_ms": raw.get(
                        "runtime_setup_ms", raw.get("model_load_prepare_ms")
                    ),
                    "peak_rss_mib": raw["peak_process_rss_kib"] / 1024,
                    "argmax": [v["argmax_id"] for v in passes],
                }
            )
    frontend_file = directory / "frontend.json"
    if frontend_file.exists():
        frontend = json.loads(frontend_file.read_text())
        for row in rows:
            # Frontend setup belongs to this process, not to each timed request.
            # Do not add it to warm TTFT or decode latency.
            row["frontend"] = frontend
    run_file = directory / "run.json"
    validity = json.loads(run_file.read_text()).get("timings_valid_for_benchmark", True) if run_file.exists() else None
    flags = []
    if validity is None:
        for path in directory.glob("*.json"):
            record = json.loads(path.read_text())
            if isinstance(record, dict) and "passes" in record and "timings_valid_for_benchmark" in record:
                flags.append(record["timings_valid_for_benchmark"])
    for row in rows:
        if validity is not None:
            row["timings_valid_for_benchmark"] = validity
        else:
            # External native runners carry this field in each request record.
            row["timings_valid_for_benchmark"] = all(flags) if flags else True
    if not rows:
        raise RuntimeError("No runner measurements found")
    return rows


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--config", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    config = expand_capacity_sweep(json.loads(args.config.read_text()))
    args.output.mkdir(parents=True, exist_ok=False)
    save(args.output / "config.json", config)
    adb = ["adb", "-s", config["serial"]] if config.get("serial") else []
    if adb:
        for name, command in {
            "device.txt": "getprop ro.product.model; getprop ro.build.fingerprint",
            "memory.txt": "cat /proc/meminfo",
        }.items():
            result = subprocess.run(
                adb + ["shell", command],
                capture_output=True,
                text=True,
                check=True,
                timeout=30,
            )
            (args.output / name).write_text(result.stdout)
    failures = []
    time.sleep(config.get("initial_cooldown_seconds", 0))
    for job in config["jobs"]:
        name = job["name"]
        if not name or any(
            c not in "abcdefghijklmnopqrstuvwxyz0123456789_-" for c in name
        ):
            raise ValueError("Job names must be simple lowercase identifiers")
        directory = args.output / name
        directory.mkdir()
        output = (
            config["remote_root"] + "/" + name
            if adb
            else str((directory / "capture").resolve())
        )
        argv = [s.replace("{output}", output) for s in job["argv"]]
        save(directory / "command.json", argv)
        if adb:
            subprocess.run(
                adb + ["shell", shlex.join(["test", "!", "-e", output])],
                check=True,
                timeout=30,
            )
        print("START", name, flush=True)
        start = time.monotonic()
        if adb:
            before = subprocess.run(
                adb + ["shell", "dumpsys battery"],
                capture_output=True,
                text=True,
                timeout=30,
            )
            (directory / "battery-before.txt").write_text(before.stdout)
            if "capacity_sweep" in config:
                capture_capacity_telemetry(adb, directory, "before")
        with (directory / "process.log").open("w") as log:
            result = subprocess.run(
                adb + ["shell", shlex.join(argv)] if adb else argv,
                stdout=log,
                stderr=subprocess.STDOUT,
                timeout=3600,
            )
        save(
            directory / "status.json",
            {
                "returncode": result.returncode,
                "elapsed_seconds": time.monotonic() - start,
            },
        )
        if adb:
            after = subprocess.run(
                adb + ["shell", "dumpsys battery"],
                capture_output=True,
                text=True,
                timeout=30,
            )
            (directory / "battery-after.txt").write_text(after.stdout)
            if "capacity_sweep" in config:
                capture_capacity_telemetry(adb, directory, "after")
        if result.returncode:
            failures.append(name)
            print("FAILED", name, result.returncode, flush=True)
        else:
            if adb:
                subprocess.run(
                    adb + ["pull", output + "/.", str(directory / "capture")],
                    capture_output=True,
                    check=True,
                    timeout=300,
                )
            rows = summarize(directory / "capture")
            save(directory / "summary.json", rows)
            measured = [r for r in rows if not r["warmup"]]
            print(
                "DONE",
                name,
                "TTFT ms",
                [round(r["ttft_ms"], 2) for r in measured],
                flush=True,
            )
        time.sleep(config.get("cooldown_seconds", 20))
    if failures:
        raise SystemExit("Failed jobs: " + ", ".join(failures))
    if "capacity_sweep" in config:
        report = check_capacity_sweep(config, args.output)
        save(args.output / "capacity-check.json", report)
        print("CAPACITY CHECK", report["verdict"], flush=True)
        if report["verdict"] != "pass":
            raise SystemExit("Capacity-sensitive timings; inspect capacity-check.json")


if __name__ == "__main__":
    main()
