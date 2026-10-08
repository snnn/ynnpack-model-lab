# Copyright 2026 @snnn.
# SPDX-License-Identifier: Apache-2.0
import json
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest

from tools.benchmark import summarize
from tools.capacity_sweep import check_capacity_sweep, expand_capacity_sweep


class BenchmarkSummaryTest(unittest.TestCase):
    def test_native_status_does_not_override_diagnostic_requests(self):
        request = {"case_id": "a", "run_index": 0, "warmup": False,
                   "timings_valid_for_benchmark": False, "peak_process_rss_kib": 2048,
                   "passes": [{"elapsed_ms": 10, "argmax_id": 1},
                              {"elapsed_ms": 2, "argmax_id": 2}]}
        with tempfile.TemporaryDirectory() as temp:
            root = Path(temp)
            (root / "a.run_000.json").write_text(json.dumps(request))
            for status in [{"status": "completed"}, {"timings_valid_for_benchmark": True}]:
                with self.subTest(status=status):
                    (root / "run.json").write_text(json.dumps(status))
                    self.assertFalse(summarize(root)[0]["timings_valid_for_benchmark"])
            request["timings_valid_for_benchmark"] = True
            (root / "a.run_000.json").write_text(json.dumps(request))
            self.assertTrue(summarize(root)[0]["timings_valid_for_benchmark"])
            (root / "run.json").write_text(json.dumps({"timings_valid_for_benchmark": False}))
            self.assertFalse(summarize(root)[0]["timings_valid_for_benchmark"])

    def test_frontend_time_is_separate_from_warm_model_metrics(self):
        with tempfile.TemporaryDirectory() as temp:
            root = Path(temp)
            first = {"case": "a", "repetition": 0, "step": 0,
                     "context": 130, "prefix_ms": 10, "token_ms": 3,
                     "setup_ms": 5, "peak_rss_kib": 2048, "argmax": 7}
            second = {**first, "step": 1, "context": 131, "token_ms": 6}
            (root / "timings.jsonl").write_text(
                json.dumps(first) + "\n" + json.dumps(second) + "\n"
            )
            frontend = {"frontend_total_ms": 999, "tokenizer_load_ms": 123,
                        "tokenizer_encode_ms": 300, "resolved_cases_sha256": "abc"}
            (root / "frontend.json").write_text(json.dumps(frontend))
            row = summarize(root)[0]
            self.assertEqual(row["frontend"], frontend)
            self.assertEqual(row["ttft_ms"], 13)
            self.assertEqual(row["setup_ms"], 5)
            self.assertEqual(row["decode_ms"], 6)
            self.assertEqual(row["prefill_tok_s"], 12900)
            self.assertAlmostEqual(row["decode_tok_s"], 1000 / 6)
            (root / "run.json").write_text(json.dumps({"timings_valid_for_benchmark": False}))
            self.assertFalse(summarize(root)[0]["timings_valid_for_benchmark"])
            (root / "frontend.json").unlink()
            self.assertNotIn("frontend", summarize(root)[0])


class CapacitySweepTest(unittest.TestCase):
    def config(self):
        return {
            "capacity_sweep": {"capacities": [2048, 8448]},
            "jobs": [{"name": "ynn-t4", "engine": "ynn", "argv": [
                "runner", "--num_threads=4", "--cache_capacity={capacity}",
                "--output_dir={output}",
            ]}],
        }

    def captures(self, root, config, prefix_factor=1, decode_factor=1):
        for job in config["jobs"]:
            path = root / job["name"]
            capture = path / "capture"
            capture.mkdir(parents=True)
            (path / "status.json").write_text(json.dumps({"returncode": 0}))
            (capture / "resolved_cases.tsv").write_text(
                "p17\t" + ",".join(str(i) for i in range(17)) + "\t1,2\n")
            (capture / "run.json").write_text(json.dumps({
                "cache_capacity": job["capacity"], "warmups": 1,
                "repetitions": 3, "profile": "test", "threads": 4,
                "prefill_rows": 128, "timings_valid_for_benchmark": True,
            }))
            large = job["capacity"] == 8448
            prefix = 20 * (prefix_factor if large else 1)
            decode = 2 * (decode_factor if large else 1)
            rows = [{
                "case": "p17", "prompt_tokens": 17, "warmup": False,
                "repetition": r, "prefix_ms": prefix, "ttft_ms": prefix + 3,
                "decode_ms": decode, "decode_token_ms": [decode, decode],
                "argmax": [4, 5, 6], "view_copy_bytes": 0,
                "timings_valid_for_benchmark": True,
                "setup_ms": 10000 if large else 100,
                "peak_rss_mib": 200 if large else 100,
            } for r in range(3)]
            rows.append({**rows[0], "warmup": True, "repetition": -1,
                         "prefix_ms": 100000, "decode_ms": 100000})
            (path / "summary.json").write_text(json.dumps(rows))

    def test_alternates_order_and_changes_only_capacity(self):
        original = self.config()
        expanded = expand_capacity_sweep(original)
        self.assertEqual([j["capacity"] for j in expanded["jobs"]],
                         [2048, 8448, 8448, 2048])
        self.assertEqual([j["sweep_round"] for j in expanded["jobs"]], [1, 1, 2, 2])
        self.assertEqual(original["jobs"][0]["argv"][2], "--cache_capacity={capacity}")
        for job in expanded["jobs"]:
            self.assertEqual(job["argv"][:2], ["runner", "--num_threads=4"])

    def test_warm_latencies_exclude_setup_rss_and_warmups(self):
        config = expand_capacity_sweep(self.config())
        with tempfile.TemporaryDirectory() as temp:
            root = Path(temp)
            self.captures(root, config)
            report = check_capacity_sweep(config, root)
            self.assertEqual(report["verdict"], "pass")
            for metric in report["groups"][0]["comparisons"][0]["metrics"].values():
                self.assertEqual(metric["latency_ratio"], 1)
            self.assertEqual(report["groups"][0]["processes"][1]["setup_ms"], 10000)

    def test_detects_prefill_and_decode_independently(self):
        config = expand_capacity_sweep(self.config())
        for prefix, decode, failing in [(1.25, 1, "prefix_ms"), (1, 1.5, "decode_ms"),
                                        (1, 0.5, "decode_ms")]:
            with self.subTest(failing=failing), tempfile.TemporaryDirectory() as temp:
                root = Path(temp)
                self.captures(root, config, prefix, decode)
                report = check_capacity_sweep(config, root)
                self.assertEqual(report["verdict"], "capacity_sensitive")
                metrics = report["groups"][0]["comparisons"][0]["metrics"]
                self.assertEqual(metrics[failing]["verdict"], "capacity_sensitive")
                other = "decode_ms" if failing == "prefix_ms" else "prefix_ms"
                self.assertEqual(metrics[other]["verdict"], "pass")

    def test_one_token_prompt_has_no_prefill_metric(self):
        config = expand_capacity_sweep(self.config())
        with tempfile.TemporaryDirectory() as temp:
            root = Path(temp)
            self.captures(root, config)
            for job in config["jobs"]:
                path = root / job["name"]
                (path / "capture/resolved_cases.tsv").write_text("p1\t1\t2,3\n")
                file = path / "summary.json"
                rows = json.loads(file.read_text())
                for row in rows:
                    row.update(case="p1", prompt_tokens=1, prefix_ms=0, ttft_ms=3)
                file.write_text(json.dumps(rows))
            report = check_capacity_sweep(config, root)
            self.assertEqual(report["verdict"], "pass")
            metrics = report["groups"][0]["comparisons"][0]["metrics"]
            self.assertEqual(set(metrics), {"ttft_ms", "decode_ms"})

    def test_rejects_unmatched_instrumented_or_incomplete_captures(self):
        mutations = {
            "fixture": lambda p: (p / "capture/resolved_cases.tsv").write_text("p17\t9\t1,2\n"),
            "profile": ("run", "timings_valid_for_benchmark", False),
            "profile_mode": ("run", "profile_execution", "decode"),
            "memory_hooks": ("run", "report_memory", True),
            "threads": ("run", "threads", 1),
            "chunk": ("run", "prefill_rows", 64),
            "warmup": ("run", "warmups", 0),
            "nonfinite": ("summary", "decode_ms", float("nan")),
            "argmax": ("summary", "argmax", [9, 9, 9]),
            "copy": ("summary", "view_copy_bytes", 512),
            "missing_request": lambda p: (p / "summary.json").write_text(json.dumps(
                json.loads((p / "summary.json").read_text())[1:])),
        }
        for name, mutation in mutations.items():
            with self.subTest(name=name), tempfile.TemporaryDirectory() as temp:
                root = Path(temp)
                config = expand_capacity_sweep(self.config())
                self.captures(root, config)
                path = root / config["jobs"][1]["name"]
                if callable(mutation):
                    mutation(path)
                else:
                    target, field, value = mutation
                    file = path / ("capture/run.json" if target == "run" else "summary.json")
                    data = json.loads(file.read_text())
                    (data if target == "run" else data[0])[field] = value
                    file.write_text(json.dumps(data))
                with self.assertRaises(ValueError):
                    check_capacity_sweep(config, root)

    def test_rejects_missing_round_or_changed_affinity(self):
        for mode in ["round", "affinity"]:
            with self.subTest(mode=mode), tempfile.TemporaryDirectory() as temp:
                config = expand_capacity_sweep(self.config())
                root = Path(temp)
                self.captures(root, config)
                if mode == "round":
                    config["jobs"].pop()
                else:
                    config["jobs"][1]["argv"].append("--affinity=1")
                with self.assertRaises(ValueError):
                    check_capacity_sweep(config, root)

    def test_rejects_invalid_sweeps(self):
        for field, value in [("capacities", [2048]), ("capacities", [8448, 2048]),
                             ("capacities", [2048, 2048]), ("rounds", 1),
                             ("max_latency_change_percent", float("nan"))]:
            with self.subTest(field=field, value=value):
                config = self.config()
                config["capacity_sweep"][field] = value
                with self.assertRaises(ValueError):
                    expand_capacity_sweep(config)

    def test_command_line_runs_sweep_and_returns_failure_on_slowdown(self):
        # This executable generates timing fixtures to test harness behavior;
        # its durations are not model measurements.
        fake = '''import json, pathlib, sys
args = dict(a.removeprefix('--').split('=', 1) for a in sys.argv[1:])
out = pathlib.Path(args['output_dir']); out.mkdir()
capacity = int(args['cache_capacity'])
(out/'resolved_cases.tsv').write_text('sample\\t1,2\\t3,4\\n')
(out/'run.json').write_text(json.dumps(dict(cache_capacity=capacity, warmups=1,
    repetitions=3, timings_valid_for_benchmark=True)))
with (out/'timings.jsonl').open('w') as stream:
 for rep in [-1, 0, 1, 2]:
  for step in range(3):
   latency = 20 if step == 0 else (3 if args['slow'] == 'true' and capacity == 8448 else 2)
   stream.write(json.dumps(dict(case='sample', repetition=rep, step=step,
       context=2+step, prefix_ms=10, token_ms=latency, setup_ms=capacity,
       peak_rss_kib=capacity, argmax=7, view_copy_bytes=0))+'\\n')
'''
        with tempfile.TemporaryDirectory() as temp:
            root = Path(temp)
            executable = root / "fake.py"
            executable.write_text(fake)
            for slow in [False, True]:
                config = self.config()
                config["cooldown_seconds"] = 0
                config["jobs"][0]["argv"] = [
                    sys.executable, str(executable), "--cache_capacity={capacity}",
                    "--output_dir={output}", f"--slow={str(slow).lower()}",
                ]
                config_file = root / f"config-{slow}.json"
                config_file.write_text(json.dumps(config))
                output = root / f"output-{slow}"
                result = subprocess.run([
                    sys.executable, "tools/benchmark.py", "--config", str(config_file),
                    "--output", str(output),
                ], capture_output=True, text=True, timeout=30)
                self.assertEqual(result.returncode, int(slow), result.stdout + result.stderr)
                report = json.loads((output / "capacity-check.json").read_text())
                metrics = report["groups"][0]["comparisons"][0]["metrics"]
                self.assertEqual(metrics["prefix_ms"]["latency_ratio"], 1)
                self.assertEqual(metrics["ttft_ms"]["latency_ratio"], 1)
                self.assertEqual(metrics["decode_ms"]["latency_ratio"], 1.5 if slow else 1)
                recheck = subprocess.run([
                    sys.executable, "tools/capacity_sweep.py", str(output),
                ], capture_output=True, text=True, timeout=30)
                self.assertEqual(recheck.returncode, int(slow), recheck.stdout + recheck.stderr)
                self.assertEqual(json.loads((output / "capacity-check.json").read_text()), report)


if __name__ == "__main__":
    unittest.main()
