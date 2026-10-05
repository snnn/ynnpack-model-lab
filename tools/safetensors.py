# Copyright 2026 @snnn.
# SPDX-License-Identifier: Apache-2.0
"""Bounded, lazy safetensors reader; no Torch or model-framework dependency."""

import hashlib
import json
import math
from pathlib import Path
import struct


DTYPE_BYTES = {
    "F64": 8,
    "F32": 4,
    "F16": 2,
    "BF16": 2,
    "I64": 8,
    "I32": 4,
    "I16": 2,
    "I8": 1,
    "U8": 1,
    "BOOL": 1,
}


def unique_object(items):
    result = {}
    for key, value in items:
        if key in result:
            raise ValueError(f"Duplicate JSON key: {key}")
        result[key] = value
    return result


def read_json(path):
    return json.loads(Path(path).read_text(), object_pairs_hook=unique_object)


def relative_file(root, name):
    path = Path(name)
    if path.is_absolute() or not name or ".." in path.parts:
        raise ValueError(f"Invalid checkpoint-relative path: {name}")
    # HF snapshots use symlinks into the blob cache; allow these.
    result = root / path
    if not result.is_file():
        raise ValueError(f"Missing checkpoint file: {name}")
    return result


class Checkpoint:
    """Tensor descriptors use absolute file offsets and preserve source dtype."""

    def __init__(self, directory):
        self.directory = Path(directory).resolve()
        index = self.directory / "model.safetensors.index.json"
        mapping = read_json(index)["weight_map"] if index.exists() else None
        if mapping is not None and (
            not isinstance(mapping, dict)
            or not mapping
            or any(
                not isinstance(k, str) or not isinstance(v, str)
                for k, v in mapping.items()
            )
        ):
            raise ValueError("Invalid shard index weight_map")
        files = sorted(set(mapping.values())) if mapping else ["model.safetensors"]
        self.tensors, self.files = {}, {}
        for name in files:
            path = relative_file(self.directory, name)
            size = path.stat().st_size
            with path.open("rb") as stream:
                prefix = stream.read(8)
                if len(prefix) != 8:
                    raise ValueError("Truncated safetensors prefix")
                length = struct.unpack("<Q", prefix)[0]
                if not 0 < length <= min(64 * 1024 * 1024, size - 8):
                    raise ValueError("Invalid safetensors header length")
                raw = stream.read(length)
            header = json.loads(raw, object_pairs_hook=unique_object)
            if not isinstance(header, dict):
                raise ValueError("Expected safetensors header object")
            start, intervals = 8 + length, []
            for tensor, info in header.items():
                if tensor == "__metadata__":
                    if not isinstance(info, dict) or any(
                        not isinstance(v, str) for v in info.values()
                    ):
                        raise ValueError("Invalid safetensors metadata")
                    continue
                if not isinstance(info, dict) or not all(
                    k in info for k in ("dtype", "shape", "data_offsets")
                ):
                    raise ValueError(f"Invalid tensor descriptor: {tensor}")
                if tensor in self.tensors:
                    raise ValueError(f"Duplicate tensor: {tensor}")
                if mapping is not None and mapping.get(tensor) != name:
                    raise ValueError(f"Tensor/index disagreement: {tensor}")
                dtype, shape = info["dtype"], info["shape"]
                if (
                    not isinstance(dtype, str)
                    or dtype not in DTYPE_BYTES
                    or not isinstance(shape, list)
                    or any(type(d) is not int or d < 0 for d in shape)
                ):
                    raise ValueError(f"Unsupported dtype/shape: {tensor}")
                offsets = info["data_offsets"]
                if (
                    not isinstance(offsets, list)
                    or len(offsets) != 2
                    or any(type(v) is not int for v in offsets)
                ):
                    raise ValueError(f"Invalid tensor offsets: {tensor}")
                lo, hi = offsets
                if (
                    not 0 <= lo <= hi <= size - start
                    or hi - lo != math.prod(shape) * DTYPE_BYTES[dtype]
                ):
                    raise ValueError(f"Invalid tensor extent: {tensor}")
                intervals.append((lo, hi))
                self.tensors[tensor] = dict(
                    file=name,
                    offset=start + lo,
                    bytes=hi - lo,
                    dtype=dtype,
                    shape=shape,
                )
            previous = 0
            for lo, hi in sorted(intervals):
                if lo != previous:
                    raise ValueError("Overlapping or non-contiguous tensor data")
                previous = hi
            if previous != size - start:
                raise ValueError("Unaccounted safetensors payload")
            self.files[name] = dict(
                bytes=size, header_sha256=hashlib.sha256(raw).hexdigest()
            )
        if mapping is not None and set(mapping) != set(self.tensors):
            raise ValueError("Incomplete shard index")

    def chunks(self, name, chunk_bytes=8 * 1024 * 1024):
        if type(chunk_bytes) is not int or chunk_bytes <= 0:
            raise ValueError("Positive streaming block size required")
        rec = self.tensors[name]
        with relative_file(self.directory, rec["file"]).open("rb") as stream:
            stream.seek(rec["offset"])
            remaining = rec["bytes"]
            while remaining:
                block = stream.read(min(remaining, chunk_bytes))
                if not block:
                    raise ValueError(f"Truncated tensor: {name}")
                yield block
                remaining -= len(block)

    def read(self, name, max_bytes=64 * 1024 * 1024):
        if self.tensors[name]["bytes"] > max_bytes:
            raise ValueError("Use streaming access for large tensors")
        return b"".join(self.chunks(name))

    def digest(self, name):
        h = hashlib.sha256()
        for data in self.chunks(name):
            h.update(data)
        return h.hexdigest()

    def scalar(self, name):
        rec = self.tensors[name]
        if rec["dtype"] != "F32" or math.prod(rec["shape"]) != 1:
            raise ValueError(f"Expected FP32 scalar: {name}")
        (value,) = struct.unpack("<f", self.read(name))
        if not math.isfinite(value) or value < 0:
            raise ValueError(f"Invalid scale: {name}")
        return value
