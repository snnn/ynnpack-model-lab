# Copyright 2026 @snnn.
# SPDX-License-Identifier: Apache-2.0
import json
from pathlib import Path
import tempfile
import unittest

from tools.benchmark import summarize


class BenchmarkSummaryTest(unittest.TestCase):
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
            (root / "frontend.json").unlink()
            self.assertNotIn("frontend", summarize(root)[0])


if __name__ == "__main__":
    unittest.main()
