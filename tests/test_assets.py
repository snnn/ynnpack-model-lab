# Copyright 2026 @snnn.
# SPDX-License-Identifier: Apache-2.0
import io
import hashlib
import json
from pathlib import Path
import unittest

from tools.prepare_gemma4 import extract, relative_path

import sys
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'python'))
from ynnpack_assets.artifacts import read_program, _assets


class AssetRecipesTest(unittest.TestCase):
    def test_checked_in_programs_have_complete_recipes(self):
        root = Path(__file__).resolve().parents[1]
        for variant in ("e2b", "e4b"):
            model = root / ("models/gemma4_" + variant)
            recipe = json.loads((model / "asset_recipe.json").read_text())
            generated = model / "generated"
            references = set()
            for data in _assets(read_program(generated)):
                if data['path'].startswith('@parameters/'):
                    references.add(data['path'])
                    self.assertEqual(recipe['files'][data['path']], data['sha256'])
                    self.assertEqual(recipe['recipes'][data['sha256']]['bytes'], data['bytes'])
            self.assertFalse(list(generated.glob('*.cc')))
            self.assertTrue(references)
            self.assertEqual(references - recipe["files"].keys(), set())
            for name in references:
                sha = recipe["files"][name]
                item = recipe["recipes"][sha]
                if "literal" in item:
                    payload = bytes.fromhex(item["literal"])
                    self.assertEqual(len(payload), item["bytes"])
                    self.assertEqual(hashlib.sha256(payload).hexdigest(), sha)

    def test_interleave_preserves_token_rows(self):
        source = io.BytesIO(b"xxaabbccAABBCC")
        recipe = {
            "interleave": [{"offset": 2, "bytes": 6}, {"offset": 8, "bytes": 6}],
            "rows": 3,
            "row_bytes": 2,
            "bytes": 12,
        }
        out = io.BytesIO()
        extract(source, recipe, out)
        self.assertEqual(out.getvalue(), b"aaAAbbBBccCC")

    def test_literal_and_range(self):
        source = io.BytesIO(b"abcdef")
        out = io.BytesIO()
        extract(source, {"offset": 1, "bytes": 3}, out)
        extract(source, {"literal": "00ff", "bytes": 2}, out)
        self.assertEqual(out.getvalue(), b"bcd\x00\xff")

    def test_truncated_source_fails(self):
        with self.assertRaises(ValueError):
            extract(io.BytesIO(b"ab"), {"offset": 1, "bytes": 5}, io.BytesIO())

    def test_no_parent_or_absolute_paths(self):
        for path in ["", "/weight", "../weight", "weights/../../escape"]:
            with self.assertRaises(ValueError):
                relative_path(path)


if __name__ == "__main__":
    unittest.main()
