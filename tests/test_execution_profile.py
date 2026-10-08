# Copyright 2026 @snnn.
# SPDX-License-Identifier: Apache-2.0
import json
from pathlib import Path
import tempfile
import unittest

from tools.analyze_execution_profile import attention_category, summarize_ynn, union_ns
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

    def test_attention_overlap_and_history_accounting(self):
        operations = [
            {"id": 0, "scope": "Layer0/Attention/Sdpa", "kind": "core.dequantize"},
            {"id": 1, "scope": "Layer0/Attention/Sdpa", "kind": "core.matmul",
             "input_names": ["query", "dequantized_key"]},
        ]
        metadata = {"scope": "scheduled_callback_worker_work", "operations": operations,
                    "calls": [
                        {"id": 0, "name": "graph_run", "envelope": True, "origins": []},
                        {"id": 1, "name": "dequantize", "envelope": False, "origins": [0]},
                        {"id": 2, "name": "dot", "envelope": False, "origins": [1]},
                        {"id": 3, "name": "unknown", "envelope": False, "origins": []},
                    ]}
        # Attention covers [2,16], other callbacks [10,22] and [28,30].
        # Their shared [10,16] interval must be charged only once.
        first = {"type": "step", "complete": True, "dropped_events": 0,
                 "case": "short", "repetition": 0, "step": 1, "position": 128,
                 "history": 129, "start_ns": 0, "end_ns": 40_000_000,
                 "events": [[0, 0, 0, 40_000_000], [0, 1, 2_000_000, 12_000_000],
                            [1, 2, 6_000_000, 16_000_000],
                            [2, 3, 10_000_000, 22_000_000],
                            [0, 3, 28_000_000, 30_000_000]]}
        second = {**first, "case": "long", "position": 1024, "history": 1025,
                  "events": [[0, 0, 0, 40_000_000], [0, 3, 0, 40_000_000]]}
        with tempfile.TemporaryDirectory() as temporary:
            path = Path(temporary) / "trace.jsonl"
            path.write_text("\n".join(json.dumps(r) for r in [metadata, first, second]) + "\n")
            result = summarize_ynn(path)
        step = result["steps"][0]
        self.assertEqual(step["attention_callback_worker_ms"], 20)
        self.assertEqual(step["attention_callback_busy_wall_ms"], 14)
        self.assertEqual(step["wall_partition"], {
            "attention_only_ms": 8, "other_callbacks_only_ms": 8,
            "attention_other_overlap_ms": 6, "outside_callbacks_ms": 18})
        self.assertEqual(sum(step["wall_partition"].values()), step["wall_ms"])
        summary = result["attention"]["all_steps"]
        self.assertEqual(summary["mean_attention_callback_worker_ms"], 10)
        self.assertEqual(summary["history_min"], 129)
        self.assertEqual(summary["history_max"], 1025)
        self.assertEqual(summary["categories"][0]["mean_calls_per_step"], 0.5)
        cases = {r["case"]: r for r in result["attention"]["cases"]}
        self.assertEqual(cases["short"]["mean_attention_callback_busy_wall_ms"], 14)
        self.assertEqual(cases["long"]["mean_attention_callback_busy_wall_ms"], 0)

    def test_fused_attention_origins_are_counted_once(self):
        operations = {
            0: {"scope": "Layer0/Attention/Sdpa", "kind": "core.dequantize"},
            1: {"scope": "Layer0/Attention/Sdpa", "kind": "core.matmul",
                "input_names": ["query", "dequantized_key"]},
            2: {"scope": "Layer0/Attention/Sdpa", "kind": "core.matmul",
                "input_names": ["Softmax", "dequantized_value"]},
            3: {"scope": "Layer0/Attention/QueryProjection", "kind": "core.mul"},
        }
        self.assertEqual(attention_category({"name": "dot", "origins": [0, 1]}, operations), "qk")
        self.assertEqual(attention_category({"name": "dot", "origins": [0, 2]}, operations), "pv")
        self.assertEqual(attention_category({"name": "pack_b", "origins": [1]}, operations), "packing")
        self.assertEqual(attention_category({"name": "dequantize", "origins": [0]}, operations), "dequantization")
        self.assertEqual(attention_category({"name": "multiply", "origins": [0, 3]}, operations), "mixed_origins")
        self.assertIsNone(attention_category({"name": "unknown", "origins": []}, operations))

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
