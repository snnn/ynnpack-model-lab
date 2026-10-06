# Copyright 2026 @snnn.
# SPDX-License-Identifier: Apache-2.0
import json
from pathlib import Path
import tempfile
import unittest

from tools.analyze_execution_profile import summarize_ynn, union_ns
from tools.analyze_cpu_samples import decode_intervals, merge_intervals


class ProfileAccountingTest(unittest.TestCase):
    def test_interval_union(self):
        self.assertEqual(union_ns([(0, 10), (2, 4), (8, 20), (25, 30)]), 25)
        self.assertEqual(union_ns([]), 0)
        with self.assertRaises(ValueError):
            union_ns([(5, 4)])

    def test_parallel_work_is_distinct_from_wall(self):
        metadata = {"scope": "scheduled_callback_worker_work", "operations": [],
                    "calls": [{"id": 0, "name": "graph_run", "envelope": True, "origins": []},
                              {"id": 1, "name": "unmapped", "envelope": False, "origins": []}]}
        step = {"type": "step", "complete": True, "dropped_events": 0, "case": "test",
                "repetition": 0, "step": 1, "position": 128, "history": 129,
                "start_ns": 0, "end_ns": 20_000_000,
                "events": [[0, 0, 0, 20_000_000], [0, 1, 0, 10_000_000],
                           [1, 1, 0, 10_000_000]]}
        with tempfile.TemporaryDirectory() as temporary:
            path = Path(temporary) / "trace.jsonl"
            path.write_text(json.dumps(metadata) + "\n" + json.dumps(step) + "\n")
            result = summarize_ynn(path)["steps"][0]
            self.assertEqual(result["wall_ms"], 20)
            self.assertEqual(result["callback_worker_ms"], 20)
            self.assertEqual(result["callback_busy_wall_ms"], 10)
            self.assertEqual(result["outside_callbacks_ms"], 10)
            self.assertEqual(result["groups"][0]["category"], "unattributed")
            step["complete"] = False
            path.write_text(json.dumps(metadata) + "\n" + json.dumps(step) + "\n")
            with self.assertRaises(ValueError):
                summarize_ynn(path)

    def test_cpu_sampling_uses_execution_envelopes(self):
        metadata = {"calls": [{"id": 0, "envelope": True},
                              {"id": 1, "envelope": False}]}
        step = {"complete": True, "dropped_events": 0,
                "start_ns": 0, "end_ns": 100,
                "events": [[0, 0, 10, 90], [0, 1, 20, 80]]}
        with tempfile.TemporaryDirectory() as temporary:
            path = Path(temporary) / "trace.jsonl"
            path.write_text(json.dumps(metadata) + "\n" + json.dumps(step) + "\n")
            intervals, scope = decode_intervals(ynn=path)
            self.assertEqual(intervals, [(10, 90)])
            self.assertEqual(scope, "measured_subsequent_decode_graph_run")
        self.assertEqual(merge_intervals([(10, 30), (15, 20), (25, 40)]), [(10, 40)])

    def test_native_sampling_stops_at_last_operator(self):
        with tempfile.TemporaryDirectory() as temporary:
            directory = Path(temporary)
            stage = {"layer": 0, "invoke_start_ns": [100], "wall_ns": [50]}
            operators = [{"layer": 0, "samples_ns": [10]},
                         {"layer": 0, "samples_ns": [20]}]
            (directory / "post_stages.jsonl").write_text(json.dumps(stage) + "\n")
            (directory / "post_operators.jsonl").write_text(
                "\n".join(json.dumps(op) for op in operators) + "\n")
            intervals, _ = decode_intervals(native=directory)
            # The remaining 20 ns of host collection is excluded.
            self.assertEqual(intervals, [(100, 130)])


if __name__ == "__main__":
    unittest.main()
