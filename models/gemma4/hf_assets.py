# Copyright 2026 @snnn.
# SPDX-License-Identifier: Apache-2.0
"""Gemma mobile-QAT interpretation, kept separate from safetensors storage."""

import hashlib
import json
import math
from pathlib import Path
import re
import struct

from tools.safetensors import Checkpoint, read_json

SOURCE_REPO = "google/gemma-4-E2B-it-qat-mobile-transformers"
SOURCE_REVISION = "dd693ff40353f057ca5f07e945ad867f4afbf2ec"
BF16_PROFILES = ("hf_bf16", "hf_bf16_int8_raw_kv", "hf_bf16_int8_published_kv")
PROFILES = BF16_PROFILES + (
    "hf_fp32_int8_published_kv",
    "hf_static_int8_published_kv",
)
PREFIX = "model.language_model."


def canonical(name):
    if name.startswith(PREFIX):
        name = "model." + name[len(PREFIX) :]
    return (
        name.replace(".embedding_quantized", ".weight")
        .replace(".embedding_scale", ".weight_scale")
        .replace(".input_activation_scale", ".input_scale")
        .replace(".output_activation_scale", ".output_scale")
    )


def bit_width(module, config):
    for pattern, options in config.get("module_quant_configs", {}).items():
        if re.search(pattern, module):
            return options.get("num_bits", config["num_bits"])
    return config["num_bits"]


def describe(directory, revision=SOURCE_REVISION):
    checkpoint = Checkpoint(directory)
    config = read_json(Path(directory) / "config.json")
    text = config["text_config"]
    expected = dict(
        hidden_size=1536,
        num_hidden_layers=35,
        num_attention_heads=8,
        num_key_value_heads=1,
        num_kv_shared_layers=20,
        hidden_size_per_layer_input=256,
        vocab_size=262144,
        head_dim=256,
        global_head_dim=512,
        sliding_window=512,
        attention_k_eq_v=False,
        enable_moe_block=False,
        hidden_activation="gelu_pytorch_tanh",
        intermediate_size=6144,
        rms_norm_eps=1e-6,
        final_logit_softcapping=30.0,
        attention_bias=False,
        use_bidirectional_attention=None,
        use_double_wide_mlp=True,
        vocab_size_per_layer_input=262144,
        tie_word_embeddings=False,
    )
    if any(text.get(k) != v for k, v in expected.items()):
        raise ValueError("Unsupported Gemma4 E2B architecture")
    pattern = [
        "full_attention" if i % 5 == 4 else "sliding_attention" for i in range(35)
    ]
    if text["layer_types"] != pattern:
        raise ValueError("Unexpected attention pattern")
    if text["rope_parameters"] != {
        "full_attention": {
            "partial_rotary_factor": 0.25,
            "rope_theta": 1000000.0,
            "rope_type": "proportional",
        },
        "sliding_attention": {"rope_theta": 10000.0, "rope_type": "default"},
    }:
        raise ValueError("Unsupported RoPE parameters")
    records = {}
    for name, info in checkpoint.tensors.items():
        if not (name.startswith(PREFIX) or name.startswith("lm_head.")):
            continue
        rec = dict(
            info,
            source_name=name,
            logical_shape=info["shape"],
            sha256=checkpoint.digest(name),
            encoding="identity",
        )
        if info["dtype"] == "U8":
            bits = bit_width(name.rsplit(".", 1)[0], config["quantization_config"])
            if bits not in (2, 4) or len(info["shape"]) != 2:
                raise ValueError(f"Unsupported packed tensor: {name}")
            rec.update(
                bits=bits,
                encoding="offset_binary_low_first",
                logical_shape=[info["shape"][0], info["shape"][1] * (8 // bits)],
            )
        elif info["dtype"] == "I8":
            rec["bits"] = 8
        elif info["dtype"] not in ("F32", "BF16"):
            raise ValueError(f"Unexpected text dtype: {name}")
        key = canonical(name)
        if key in records:
            raise ValueError(f"Ambiguous canonical name: {key}")
        records[key] = rec
    # A changed packing declaration must not reinterpret unchanged payload
    # bytes under the identity used by the checked-in builders.
    shapes = {
        "model.embed_tokens": [262144, 1536],
        "model.embed_tokens_per_layer": [262144, 8960],
        "model.per_layer_model_projection": [8960, 1536],
        "lm_head": [262144, 1536],
    }
    for layer in range(35):
        prefix = f"model.layers.{layer}."
        dim, mlp = (512 if layer % 5 == 4 else 256), (6144 if layer < 15 else 12288)
        for name, shape in {
            "self_attn.q_proj": [8 * dim, 1536],
            "self_attn.k_proj": [dim, 1536],
            "self_attn.v_proj": [dim, 1536],
            "self_attn.o_proj": [1536, 8 * dim],
            "mlp.up_proj": [mlp, 1536],
            "mlp.gate_proj": [mlp, 1536],
            "mlp.down_proj": [1536, mlp],
            "per_layer_input_gate": [256, 1536],
            "per_layer_projection": [1536, 256],
        }.items():
            shapes[prefix + name] = shape
    for module, shape in shapes.items():
        if records[module + ".weight"]["logical_shape"] != shape:
            raise ValueError(f"Weight shape/packing does not match E2B: {module}")
    if records["model.per_layer_model_projection.weight"]["dtype"] != "BF16":
        raise ValueError("Expected the HF BF16 global PLE projection")
    modules = {}
    for key, rec in records.items():
        if not key.endswith(".weight") or "bits" not in rec:
            continue
        module = key[:-7]
        scale = records[module + ".weight_scale"]
        n, k = rec["logical_shape"]
        if (
            scale["dtype"] != "F32"
            or len(scale["shape"]) != 2
            or scale["shape"][0] != n
        ):
            raise ValueError(f"Invalid scale shape: {module}")
        groups = scale["shape"][1]
        if groups < 1 or k % groups:
            raise ValueError(f"Invalid scale groups: {module}")
        expected_groups = 35 if module == "model.embed_tokens_per_layer" else 1
        if groups != expected_groups:
            raise ValueError(f"Unsupported quantization groups: {module}")
        raw = checkpoint.read(scale["source_name"])
        if any(
            not math.isfinite(v[0]) or v[0] <= 0 for v in struct.iter_unpack("<f", raw)
        ):
            raise ValueError(f"Invalid weight scales: {module}")
        entry = dict(bits=rec["bits"], group_size=k // groups)
        if module not in ("model.embed_tokens", "model.embed_tokens_per_layer"):
            for side in ("input", "output"):
                entry[side + "_scale"] = checkpoint.scalar(
                    records[module + "." + side + "_scale"]["source_name"]
                )
        modules[module] = entry
    kv = []
    for layer in range(35):
        owner = layer if layer < 15 else (14 if layer % 5 == 4 else 13)
        entry = dict(layer=layer, owner=owner, head_dim=512 if layer % 5 == 4 else 256)
        for side in ("k", "v"):
            name = f"{PREFIX}layers.{layer}.self_attn.{side}_cache_scale"
            value = checkpoint.scalar(name)
            if value <= 0 or value != checkpoint.scalar(
                f"{PREFIX}layers.{owner}.self_attn.{side}_cache_scale"
            ):
                raise ValueError("Invalid or conflicting shared KV scale")
            entry[side + "_scale"] = value
        kv.append(entry)
    # Bind compatibility to real content, not merely a user-provided revision.
    identity = hashlib.sha256(
        json.dumps(
            {k: v["sha256"] for k, v in records.items()}, sort_keys=True
        ).encode()
    ).hexdigest()
    return dict(
        format="gemma4_hf_assets_v1",
        source_repo=SOURCE_REPO,
        source_revision=revision,
        source_identity=identity,
        config_sha256=hashlib.sha256(
            (Path(directory) / "config.json").read_bytes()
        ).hexdigest(),
        config=config,
        shards=checkpoint.files,
        tensors=records,
        modules=modules,
        kv=kv,
    )
