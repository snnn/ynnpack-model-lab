#!/usr/bin/env python3
# Copyright 2026 @snnn.
# SPDX-License-Identifier: Apache-2.0
"""Independent Transformers BF16 reference for the HF Gemma4 E2B profiles.

Optional validation tool: requires torch, transformers with gemma_quant, and
safetensors. The C++ runtime and normal CMake tests do not depend on them.
"""

import argparse
import json
from pathlib import Path
import sys
import time

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from models.gemma4.hf_assets import BF16_PROFILES as PROFILES, canonical


def load_model(directory, manifest):
    import torch
    from safetensors import safe_open
    from transformers import Gemma4TextConfig, Gemma4ForCausalLM
    from transformers.integrations.gemma_quant import (
        QuantizedEmbedding,
        QuantizedLinear,
    )
    from transformers.models.gemma4.modeling_gemma4 import Gemma4TextRotaryEmbedding

    config = Gemma4TextConfig(**manifest["config"]["text_config"])
    config._attn_implementation = "eager"
    with torch.device("meta"):
        model = Gemma4ForCausalLM(config).to(dtype=torch.bfloat16)
        for name, module in list(model.named_modules()):
            q = manifest["modules"].get(name)
            if q is None:
                continue
            if isinstance(module, torch.nn.Embedding):
                new = QuantizedEmbedding(
                    module.num_embeddings,
                    module.embedding_dim,
                    torch.bfloat16,
                    module.scalar_embed_scale,
                    q["bits"],
                )
                shape = manifest["tensors"][name + ".weight_scale"]["shape"]
                new.embedding_scale = torch.nn.Parameter(
                    torch.empty(shape), requires_grad=False
                )
            elif isinstance(module, torch.nn.Linear):
                new = QuantizedLinear(
                    module.in_features, module.out_features, False, q["bits"]
                )
            else:
                raise ValueError(f"Unsupported reference module: {name}")
            model.set_submodule(name, new)
    state = {}
    handles = {
        name: safe_open(str(directory / name), framework="pt", device="cpu")
        for name in manifest["shards"]
    }
    for name in model.state_dict():
        rec = manifest["tensors"][canonical(name)]
        state[name] = handles[rec["file"]].get_tensor(rec["source_name"])
    model.load_state_dict(state, strict=True, assign=True)
    model.model.rotary_emb = Gemma4TextRotaryEmbedding(config)
    model.eval().requires_grad_(False)
    return model


def main():
    import torch
    import transformers
    from transformers import DynamicCache

    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--hf-model-dir", type=Path, required=True)
    p.add_argument("--asset-manifest", type=Path, required=True)
    p.add_argument("--profile", choices=PROFILES, required=True)
    p.add_argument("--cases-file", type=Path, required=True)
    p.add_argument("--output", type=Path, required=True)
    p.add_argument("--prefill-rows", type=int, default=128)
    p.add_argument("--threads", type=int, default=4)
    args = p.parse_args()
    if not 1 <= args.prefill_rows <= 128:
        raise ValueError("prefill rows must be 1..128")
    args.output.mkdir(parents=True, exist_ok=False)
    torch.set_num_threads(args.threads)
    manifest = json.loads(args.asset_manifest.read_text())
    if args.profile == PROFILES[2]:
        # Enforce the audited source content used by the published-KV builders.
        if (
            manifest["source_identity"]
            != "b454fea4385836b70181ce7f8d797413d695d7f916b21ed3dd49896cdad6d579"
        ):
            raise ValueError("Unaudited published-KV compatibility source")
    at = time.monotonic()
    model = load_model(args.hf_model_dir, manifest)
    metadata = dict(
        profile=args.profile,
        source_identity=manifest["source_identity"],
        torch=torch.__version__,
        transformers=transformers.__version__,
        load_seconds=time.monotonic() - at,
        prefill_rows=args.prefill_rows,
        attention="eager",
        dtype="bfloat16",
        int8_kv_reference="FP32 divide/RNE/clamp/dequantize then BF16",
    )
    (args.output / "reference.json").write_text(json.dumps(metadata, indent=2) + "\n")

    def save(tensor, path):
        tensor.detach().contiguous().view(torch.uint8).numpy().tofile(path)

    with torch.inference_mode():
        for line in args.cases_file.read_text().splitlines():
            if not line or line.startswith("#"):
                continue
            name, prompt, continuation = line.split("\t")
            if not name.replace("_", "").replace("-", "").isalnum():
                raise ValueError("Invalid case name")
            tokens = [int(x) for x in prompt.split(",")]
            decode = [tokens[-1]] + (
                [] if continuation == "-" else [int(x) for x in continuation.split(",")]
            )
            cache = DynamicCache(config=model.config)
            original_update = cache.update
            history = {}

            def update(key, value, layer, *extra, **kwargs):
                stored = []
                converted = []
                for side, tensor in (("k", key), ("v", value)):
                    if args.profile == PROFILES[0]:
                        codes, decoded = tensor, tensor
                    else:
                        scale = manifest["kv"][layer][side + "_scale"]
                        if args.profile == PROFILES[2] and layer % 5 == 4:
                            scale /= 16
                        codes = (
                            torch.round(tensor.float() / scale)
                            .clamp(-128, 127)
                            .to(torch.int8)
                        )
                        decoded = (codes.float() * scale).to(torch.bfloat16)
                    stored.append(codes)
                    converted.append(decoded)
                if layer in history:
                    stored = [
                        torch.cat((old, new), dim=2)
                        for old, new in zip(history[layer], stored)
                    ]
                history[layer] = stored
                return original_update(*converted, layer, *extra, **kwargs)

            cache.update = update
            for start in range(0, len(tokens) - 1, args.prefill_rows):
                chunk = tokens[start : min(start + args.prefill_rows, len(tokens) - 1)]
                model(
                    input_ids=torch.tensor([chunk]),
                    past_key_values=cache,
                    use_cache=True,
                    logits_to_keep=1,
                )
            for step, token in enumerate(decode):
                result = model(
                    input_ids=torch.tensor([[token]]),
                    past_key_values=cache,
                    use_cache=True,
                    logits_to_keep=1,
                )
                suffix = ".prefill.f32" if step == 0 else f".decode_{step:04d}.f32"
                path = args.output / (name + suffix)
                save(result.logits.float(), path)
                for owner, kv in history.items():
                    for side, tensor in zip(("k", "v"), kv):
                        save(
                            tensor,
                            str(path)
                            + f".owner{owner}.{side}."
                            + ("bf16" if args.profile == PROFILES[0] else "i8"),
                        )
                print(
                    json.dumps(
                        dict(case=name, step=step, argmax=result.logits.argmax().item())
                    ),
                    flush=True,
                )


if __name__ == "__main__":
    main()
