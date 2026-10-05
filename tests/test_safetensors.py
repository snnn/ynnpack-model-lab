# Copyright 2026 @snnn.
# SPDX-License-Identifier: Apache-2.0
import hashlib
import json
from pathlib import Path
import re
import struct
import tempfile
import unittest

from tools.safetensors import Checkpoint


class SafetensorsTest(unittest.TestCase):
    def test_generated_parameter_recipes_are_complete(self):
        generated = (
            Path(__file__).resolve().parents[1] / "models/gemma4_e2b_hf/generated"
        )
        recipes = list(generated.glob("*/asset_recipe.json"))
        self.assertGreaterEqual(len(recipes), 5)
        for path in recipes:
            with self.subTest(profile=path.parent.name):
                parameters = json.loads(path.read_text())["parameters"]
                for name, encoded in parameters.items():
                    self.assertEqual(
                        hashlib.sha256(bytes.fromhex(encoded)).hexdigest() + ".bin",
                        name,
                    )
                references = set()
                metadata = json.loads((path.parent / "model.json").read_text())
                sources = {name for graph in metadata["graphs"] for name in graph["builder_sources"]}
                self.assertEqual(sources, {p.name for p in path.parent.glob("gemma4_*.cc")})
                for source in [*path.parent.glob("gemma4_*.h"), *(path.parent / name for name in sources)]:
                    references.update(
                        re.findall(
                            r"@parameters/([0-9a-f]{64}\.bin)", source.read_text()
                        )
                    )
                self.assertTrue(references)
                self.assertLessEqual(references, parameters.keys())

    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)

    def write(self, header, data, name="model.safetensors"):
        h = json.dumps(header).encode() if isinstance(header, dict) else header
        (self.root / name).write_bytes(struct.pack("<Q", len(h)) + h + data)

    def test_single_file_lazy_and_scalars(self):
        payload = bytes(range(256))
        self.write(
            {
                "packed": dict(dtype="U8", shape=[16, 16], data_offsets=[0, 256]),
                "scale": dict(dtype="F32", shape=[], data_offsets=[256, 260]),
            },
            payload + struct.pack("<f", 0.25),
        )
        c = Checkpoint(self.root)
        self.assertEqual(c.digest("packed"), hashlib.sha256(payload).hexdigest())
        self.assertEqual(b"".join(c.chunks("packed", 7)), payload)
        self.assertEqual(c.scalar("scale"), 0.25)
        with self.assertRaisesRegex(ValueError, "streaming"):
            c.read("packed", 128)

    def test_shards_and_hf_symlinks(self):
        for name in ("a", "b"):
            self.write(
                {name: dict(dtype="BF16", shape=[1], data_offsets=[0, 2])},
                b"\x80\x3f",
                name + ".safetensors",
            )
        (self.root / "blob").write_bytes((self.root / "a.safetensors").read_bytes())
        (self.root / "a.safetensors").unlink()
        (self.root / "a.safetensors").symlink_to("blob")
        index = {"weight_map": {"a": "a.safetensors", "b": "b.safetensors"}}
        (self.root / "model.safetensors.index.json").write_text(json.dumps(index))
        self.assertEqual(set(Checkpoint(self.root).tensors), {"a", "b"})
        index["weight_map"]["b"] = "a.safetensors"
        (self.root / "model.safetensors.index.json").write_text(json.dumps(index))
        with self.assertRaisesRegex(ValueError, "Incomplete"):
            Checkpoint(self.root)

    def test_malformed_storage(self):
        invalid = [
            ({"x": dict(dtype="I8", shape=[2], data_offsets=[0, 1])}, b"x"),
            ({"x": dict(dtype="I8", shape=[1], data_offsets=[1, 2])}, b"xy"),
            ({"x": dict(dtype="I8", shape=[1], data_offsets=[0, 2**63])}, b"x"),
            ({"x": dict(dtype="I8", shape=[True], data_offsets=[0, 1])}, b"x"),
            (
                {
                    "x": dict(dtype="I8", shape=[1], data_offsets=[0, 1]),
                    "y": dict(dtype="I8", shape=[1], data_offsets=[0, 1]),
                },
                b"x",
            ),
            (b'{"x":{},"x":{}}', b""),
        ]
        for header, data in invalid:
            self.write(header, data)
            with self.assertRaises(ValueError):
                Checkpoint(self.root)
        (self.root / "model.safetensors").write_bytes(struct.pack("<Q", 2**63))
        with self.assertRaises(ValueError):
            Checkpoint(self.root)

    def test_invalid_shard_path_and_missing_file(self):
        for name in ("../escape", "/absolute", "missing"):
            (self.root / "model.safetensors.index.json").write_text(
                json.dumps({"weight_map": {"x": name}})
            )
            with self.assertRaises(ValueError):
                Checkpoint(self.root)


if __name__ == "__main__":
    unittest.main()
