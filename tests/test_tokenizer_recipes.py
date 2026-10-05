# Copyright 2026 @snnn.
# SPDX-License-Identifier: Apache-2.0
import copy
import hashlib
import json
from pathlib import Path
import tempfile
import unittest

from tools.prepare_tokenizer import prepare


class TokenizerRecipesTest(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.payload = b'{"version":"1.0","padding":null,"truncation":null}'
        self.data = b"header" + self.payload + b"tail"
        self.source = self.root / "bundle"
        self.source.write_bytes(self.data)
        self.recipe = {
            "version": 1, "format": "hf_json", "vocab_size": 32,
            "prefix_ids": [2], "suffix_ids": [],
            "source": {"repo": "test/model", "revision": "immutable",
                       "path": "bundle", "bytes": len(self.data),
                       "sha256": hashlib.sha256(self.data).hexdigest()},
            "payload": {"file": "tokenizer.json", "offset": 6,
                        "bytes": len(self.payload),
                        "sha256": hashlib.sha256(self.payload).hexdigest()},
        }
        self.output = self.root / "output"

    def test_extract_exact_range_and_identity(self):
        prepare(self.source, self.output, self.recipe)
        self.assertEqual((self.output / "tokenizer.json").read_bytes(), self.payload)
        manifest = json.loads((self.output / "manifest.json").read_text())
        self.assertEqual(manifest["source"], self.recipe["source"])
        self.assertEqual(manifest["prefix_ids"], [2])
        self.assertEqual(manifest["bytes"], len(self.payload))
        self.assertEqual(manifest["sha256"], self.recipe["payload"]["sha256"])
        self.assertNotIn("offset", manifest)
        with self.assertRaises(FileExistsError):
            prepare(self.source, self.output, self.recipe)

    def test_wrong_source_or_payload_is_never_published(self):
        for section in ("source", "payload"):
            recipe = copy.deepcopy(self.recipe)
            recipe[section]["sha256"] = "0" * 64
            with self.assertRaises(ValueError):
                prepare(self.source, self.output, recipe)
            self.assertFalse(self.output.exists())
        self.source.write_bytes(self.data[:-1])
        with self.assertRaises(ValueError):
            prepare(self.source, self.output, self.recipe)
        self.assertFalse(self.output.exists())

    def test_invalid_range_path_or_policy(self):
        for key, value in (("offset", -1), ("offset", len(self.data)),
                           ("bytes", 0), ("bytes", True),
                           ("file", "../escape"), ("file", "/escape")):
            recipe = copy.deepcopy(self.recipe)
            recipe["payload"][key] = value
            with self.assertRaises(ValueError):
                prepare(self.source, self.output, recipe)
        for policy in ([32], [-1], [True], [0.5]):
            recipe = copy.deepcopy(self.recipe)
            recipe["prefix_ids"] = policy
            with self.assertRaises(ValueError):
                prepare(self.source, self.output, recipe)

    def test_published_recipes_have_complete_immutable_identities(self):
        root = Path(__file__).resolve().parents[1]
        recipes = [*root.glob("models/tokenizers/*.json"),
                   *root.glob("models/gemma4_e?b/tokenizer_recipe.json")]
        required = {
            "models/tokenizers/gemma4_hf.json",
            "models/tokenizers/qwen3_0_6b.json",
            "models/tokenizers/qwen3_5_0_8b.json",
            "models/gemma4_e2b/tokenizer_recipe.json",
            "models/gemma4_e4b/tokenizer_recipe.json",
        }
        self.assertTrue(required.issubset({p.relative_to(root).as_posix() for p in recipes}))
        for path in recipes:
            recipe = json.loads(path.read_text())
            self.assertRegex(recipe["source"]["revision"], r"^[0-9a-f]{40}$")
            self.assertRegex(recipe["source"]["sha256"], r"^[0-9a-f]{64}$")
            self.assertRegex(recipe["payload"]["sha256"], r"^[0-9a-f]{64}$")
            self.assertGreater(recipe["vocab_size"], 0)
            self.assertLessEqual(recipe["payload"].get("offset", 0) + recipe["payload"]["bytes"],
                                 recipe["source"]["bytes"])
            if path.parent.name.startswith("gemma4_e"):
                weights = json.loads((path.parent / "asset_recipe.json").read_text())["source"]
                for key in ("bytes", "sha256", "path"):
                    self.assertEqual(recipe["source"][key], weights[key])


if __name__ == "__main__":
    unittest.main()
