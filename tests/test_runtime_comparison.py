# Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
"""Guard the migration decision against timing-field and threshold mistakes."""
import importlib.util
import json
from pathlib import Path
import tempfile
import unittest


spec = importlib.util.spec_from_file_location(
    'compare_runtime', Path(__file__).resolve().parents[1] / 'tools/compare_runtime.py')
comparison = importlib.util.module_from_spec(spec)
spec.loader.exec_module(comparison)


class ComparisonTest(unittest.TestCase):
    def test_ratio_gates_and_absolute_memory_allowance(self):
        before = dict(setup_ms=100, warm_ms=100, retained_bytes=16 << 20, peak_bytes=32 << 20)
        after = dict(setup_ms=124, warm_ms=104, retained_bytes=80 << 20, peak_bytes=288 << 20)
        pairs = [dict(before=before, after=after) for _ in range(6)]
        result = comparison.summarize({'job': pairs})['job']
        self.assertTrue(all(v['pass'] for v in result.values()))
        after.update(setup_ms=126, warm_ms=106, retained_bytes=(80 << 20) + 1, peak_bytes=(288 << 20) + 1)
        result = comparison.summarize({'job': pairs})['job']
        self.assertFalse(any(v['pass'] for v in result.values()))

    def test_relative_memory_allowance_and_paired_ratios(self):
        pairs = []
        for scale in [1, 2, 4, 8, 16, 32]:
            before = dict(warm_ms=scale, retained_bytes=4 << 30, peak_bytes=8 << 30)
            after = dict(warm_ms=scale * 1.02, retained_bytes=int((4 << 30) * 1.04),
                         peak_bytes=int((8 << 30) * 1.09))
            pairs.append(dict(before=before, after=after))
        result = comparison.summarize({'job': pairs})['job']
        self.assertTrue(all(v['pass'] for v in result.values()))
        self.assertAlmostEqual(result['warm_ms']['ratio'], 1.02)
        self.assertAlmostEqual(result['warm_ms']['upper95'], 1.02)
        pairs[-1]['after']['retained_bytes'] = int((4 << 30) * 1.06)
        self.assertFalse(comparison.summarize({'job': pairs})['job']['retained_bytes']['pass'])

    def test_old_and_new_timing_fields(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            records = []
            for rep in [-1, 0, 1, 2]:
                for step, elapsed in enumerate([10, 20, 40]):
                    records.append(dict(case='prompt17', repetition=rep, step=step, context=17 + step,
                                        prefix_ms=100, token_ms=elapsed, setup_ms=500,
                                        setup_rss_kib=1024, peak_rss_kib=2048))
            (root / 'timings.jsonl').write_text(''.join(json.dumps(r) + '\n' for r in records))
            old = comparison.metrics({'kind': 'gemma'}, root)
            self.assertEqual(old, dict(setup_ms=500, retained_bytes=1 << 20, peak_bytes=2 << 20,
                                      **{'prompt17.prefix_ms': 100, 'prompt17.ttft_ms': 110,
                                         'prompt17.decode_ms': 30}))
            for r in records:
                r['rep'] = r.pop('repetition')
                r['position'] = r.pop('context')
            (root / 'timings.jsonl').write_text(''.join(json.dumps(r) + '\n' for r in records))
            (root / 'setup.json').write_text(json.dumps(dict(setup_ms=500, rss_bytes=1 << 20)))
            (root / 'memory.json').write_text(json.dumps(dict(peak_rss_bytes=2 << 20)))
            self.assertEqual(comparison.metrics({'kind': 'llm'}, root), old)


if __name__ == '__main__':
    unittest.main()
