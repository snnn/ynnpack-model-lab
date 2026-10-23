#!/usr/bin/env python3
# Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
"""Create semantic blockwise workloads for preparation and invocation measurements.

These shapes represent Qwen3-0.6B linears, but this is a separate INT4 workload:
the qualified Qwen3 recipe uses INT8 linears and does not exercise this operation.
"""
import argparse
import copy
import hashlib
import json
from pathlib import Path
import subprocess

import numpy as np

ROOT = Path(__file__).resolve().parents[1]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--baseline-compiler', type=Path,
                        help='Optional frozen compiler for experiments with an archived offline runner')
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    out = args.output.resolve()
    out.mkdir(parents=True, exist_ok=False)
    parameters = out / 'parameters'
    parameters.mkdir()
    template = json.loads((ROOT / 'tests/compiler/fixtures/blockwise_fc/blockwise_7_64.program.json').read_text())
    program = dict(version=1, options=template['options'], phases={})

    def asset(data):
        data = data.tobytes()
        digest = hashlib.sha256(data).hexdigest()
        (parameters / (digest + '.bin')).write_bytes(data)
        return dict(path='@parameters/' + digest + '.bin', bytes=len(data), sha256=digest)

    graphs, steps, manifest = {}, [], []
    shapes = [(7, 64), (131, 256), (1024, 1024), (3072, 1024), (1024, 3072)]
    for n, k in shapes:
        name = f'fc_{n}_{k}'
        g = copy.deepcopy(template['phases']['model'])
        values = g['values']
        values['weight']['tensor']['shape'] = [dict(known=n), dict(known=k)]
        i = np.arange(n*k, dtype=np.uint64)
        codes = ((i*13+i//11) % 16).astype(np.uint8)
        values['weight']['data'] = asset(codes[::2] | (codes[1::2] << 4))
        scales = ((1+np.arange(n*k//32) % 7)/64).astype('<f4')
        values['weight_scales']['tensor']['shape'] = [dict(known=n), dict(known=k//32)]
        values['weight_scales']['floats'] = []
        values['weight_scales']['data'] = asset(scales)
        values['x']['tensor']['shape'][1] = dict(known=k)
        values['y']['tensor']['shape'][1] = dict(known=n)
        g['symbols'][0]['upper'] = 128
        g['guards'][1]['rhs'] = dict(known=128)
        program['phases'][name] = g
        graphs[name] = name + '.ynn'
        for rows in [1, 17, 128]:
            x = (((np.arange(rows*k)*37) % 255)/16-8).astype('<f4')
            input_file = f'{name}_m{rows}.bin'
            (out / input_file).write_bytes(x.tobytes())
            steps.append(dict(graph=name, bindings=[dict(name='x', shape=[rows,k], bytes=x.nbytes, file=input_file),
                dict(name='y', shape=[], bytes=rows*n*4)], warmup_runs=1, measured_runs=3))
            manifest.append(dict(phase=name, n=n, k=k, rows=rows))
    (out / 'program.json').write_text(json.dumps(program) + '\n')
    if args.baseline_compiler:
        subprocess.run([str(args.baseline_compiler.resolve()), '--request', str(out / 'program.json'),
                        '--output', str(out / 'compiled')], check=True, stdout=subprocess.DEVNULL)
        for path in (out / 'compiled').glob('*.ynn'):
            path.rename(out / path.name)
        for path in (out / 'compiled/parameters').iterdir():
            target = parameters / path.name
            if target.exists():
                assert path.read_bytes() == target.read_bytes()
            else:
                path.rename(target)
    for threads in [1, 4]:
        fixture = dict(version=1, threads=threads,
            buffers=[dict(name='x', dtype='fp32', shape=[128,3072]), dict(name='y', dtype='fp32', shape=[128,3072])], steps=steps)
        for mode in (['runtime', 'offline'] if args.baseline_compiler else ['runtime']):
            item = copy.deepcopy(fixture)
            if mode == 'runtime':
                item['program'] = 'program.json'
            else:
                item['graphs'] = graphs
            (out / f'{mode}-t{threads}.json').write_text(json.dumps(item) + '\n')
            for i, step in enumerate(item['steps']):
                step['outputs'] = dict(y=f'actual/{mode}-t{threads}-{i}.bin')
                step['warmup_runs'], step['measured_runs'] = 0, 1
            (out / f'{mode}-t{threads}-check.json').write_text(json.dumps(item) + '\n')
    (out / 'cases.json').write_text(json.dumps(manifest, indent=2) + '\n')


if __name__ == '__main__':
    main()
