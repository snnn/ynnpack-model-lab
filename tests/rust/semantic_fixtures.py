# Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
"""Authored semantic inputs for ownership and state tests; no native commands."""
import json
from pathlib import Path
import sys
ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'python'))
from ynnpack_assets.artifacts import seal, write_program


def value(dtype, shape, **kwargs):
    return dict(tensor=dict(dtype=dtype, shape=[dict(known=d) for d in shape]), **kwargs)


def node(op, inputs, output):
    return dict(op=op, inputs=inputs, outputs=[output])


def generate():
    root=ROOT/'tests/rust'
    g=dict(values={n:value('f32',[4]) for n in ['x','squared']}, inputs=['x'], outputs=['squared'],
           nodes=[node('mul',['x','x'],'squared')])
    (root/'program.ynn').unlink(missing_ok=True)
    write_program(dict(version=1,phases=dict(model=g)),root/'program.ynn')
    (root/'execution.json').write_text(json.dumps(dict(format='ynn-tensor-execution',version=1,graphs=dict(model=dict(
        inputs=[dict(name='x',dtype='fp32',shape=[4])],outputs=[dict(name='squared',dtype='fp32',shape=[4])]))))+'\n')
    meta=json.loads((root/'model.json').read_text());meta.pop('execution',None);seal(root,meta)
    root=ROOT/'tests/llm_session'
    phases={}
    for phase in ['prefill','decode']:
        values={n:value('f32',[1,4]) for n in ['memory','row','next','scores']}
        values['ids']=value('i32',[1])
        # Source bytes deliberately include a nonfinite row to test poisoning.
        data=next((root/'parameters').glob('*.bin'))
        import hashlib
        h=hashlib.sha256(data.read_bytes()).hexdigest()
        values['table']=value('f32',[4,4],constant=True,data=dict(path='@parameters/'+data.name,bytes=data.stat().st_size,sha256=h))
        nodes=[node('gather',['table','ids'],'row'),node('add',['row','memory'],'next')]
        if phase=='decode':nodes.append(node('copy',['next'],'scores'))
        phases[phase]=dict(values=values,inputs=['ids','memory'],outputs=['next']+(['scores'] if phase=='decode' else []),nodes=nodes)
    (root/'program.ynn').unlink(missing_ok=True)
    write_program(dict(version=1,phases=phases),root/'program.ynn')
    m=json.loads((root/'model.json').read_text())
    spec=m.pop('runner',None) or json.loads((root/'execution.json').read_text())
    for g in spec['graphs'].values():g.pop('file',None);g.pop('sha256',None)
    (root/'execution.json').write_text(json.dumps(spec)+'\n');seal(root,m)


if __name__=='__main__':generate()
