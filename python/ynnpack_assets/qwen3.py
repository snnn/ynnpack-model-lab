# Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
"""Prepare Qwen3 assets using public libraries and a shared exact weight recipe."""
import argparse
import hashlib
import importlib.metadata
import json
from pathlib import Path
import shutil
import struct
import tempfile

RECIPE = 'mixed_int8_int8_mlp_only'

def quantize(model):
    import torch
    from torchao.quantization import Int8DynamicActivationIntxWeightConfig, IntxWeightOnlyConfig, ModuleFqnToConfig
    from torchao.quantization.granularity import PerAxis
    from .torchao_weight_quantization import quantize_symmetric_
    if model.config.model_type != 'qwen3': raise ValueError('Qwen3 architecture required')
    # Untie before quantization: embedding and dynamic linear are distinct roles.
    if model.lm_head.weight is model.model.embed_tokens.weight:
        model.lm_head.weight = torch.nn.Parameter(model.lm_head.weight.detach().clone(), requires_grad=False)
    linear = Int8DynamicActivationIntxWeightConfig(weight_dtype=torch.int8, weight_granularity=PerAxis(0), weight_scale_dtype=torch.float32, version=2)
    embedding = IntxWeightOnlyConfig(weight_dtype=torch.int8, granularity=PerAxis(0), scale_dtype=torch.float32, version=2)
    configs={name: linear for name,module in model.named_modules() if isinstance(module, torch.nn.Linear)}
    configs['model.embed_tokens']=embedding
    quantize_symmetric_(model, ModuleFqnToConfig(configs), filter_fn=None)
    return model.eval()

def prepare(checkpoint, output):
    checkpoint, output = Path(checkpoint).resolve(), Path(output).resolve()
    if output.exists():
        raise FileExistsError(output)
    output.parent.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(prefix='.qwen3-assets-', dir=output.parent) as temporary:
        stage = Path(temporary) / 'package'
        _prepare(checkpoint, stage)
        stage.rename(output)


def _prepare(checkpoint, output):
    import torch
    from transformers import AutoModelForCausalLM
    checkpoint,output=Path(checkpoint).resolve(),Path(output).resolve()
    output.mkdir(parents=True,exist_ok=False)
    parameters=output/'parameters';parameters.mkdir()
    model=AutoModelForCausalLM.from_pretrained(str(checkpoint),dtype=torch.float32,local_files_only=True,attn_implementation='eager').eval()
    model=quantize(model)
    def asset(t):
        raw=t.detach().cpu().contiguous().numpy().tobytes()
        digest=hashlib.sha256(raw).hexdigest();path=parameters/(digest+'.bin')
        if not path.exists():path.write_bytes(raw)
        return dict(path='@parameters/'+path.name,bytes=len(raw),sha256=digest)
    weights={}
    for name,t in model.state_dict().items():
        if hasattr(t,'qdata'):
            if t.target_dtype!=torch.int8 or t.block_size!=(1,t.shape[1]):raise ValueError('Unexpected quantization geometry: '+name)
            if torch.any(t.zero_point!=0):raise ValueError('Expected symmetric weights')
            scales=t.scale.reshape(-1)
            weights[name]=dict(shape=list(t.shape),dtype='i8',asset=asset(t.qdata),scale_asset=asset(scales),scales=[struct.unpack('<Q',struct.pack('<d',float(x)))[0] for x in scales.tolist()])
        else:weights[name]=dict(shape=list(t.shape),dtype='f32',asset=asset(t.float()),scales=[])
    weights['rotary.inv_freq']=dict(shape=list(model.model.rotary_emb.inv_freq.shape),dtype='f32',asset=asset(model.model.rotary_emb.inv_freq.float()),scales=[])
    sources = {}
    for source in sorted(checkpoint.iterdir()):
        if source.suffix == '.safetensors' or source.name in ('config.json','model.safetensors.index.json','tokenizer.json','tokenizer_config.json','special_tokens_map.json'):
            with source.open('rb') as stream:
                sources[source.name] = dict(bytes=source.stat().st_size, sha256=hashlib.file_digest(stream,'sha256').hexdigest())
    manifest=dict(source_files=sources,format='qwen3-checkpoint-assets-v1',recipe=RECIPE,config=model.config.to_dict(),weights=weights,versions={n:importlib.metadata.version(n) for n in ('torch','torchao','transformers')},source_config_sha256=hashlib.sha256((checkpoint/'config.json').read_bytes()).hexdigest())
    (output/'assets.json').write_text(json.dumps(manifest,indent=2)+'\n')
    for name in ('tokenizer.json','tokenizer_config.json','special_tokens_map.json'):
        if (checkpoint/name).exists():
            (output/'tokenizer').mkdir(exist_ok=True);shutil.copyfile(checkpoint/name,output/'tokenizer'/name)
    print(json.dumps(dict(parameters=len(list(parameters.iterdir())),weight_roles=len(weights),recipe=RECIPE)))

if __name__=='__main__':
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--checkpoint',required=True);p.add_argument('--output',required=True)
    a=p.parse_args();prepare(a.checkpoint,a.output)
