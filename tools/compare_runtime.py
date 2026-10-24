#!/usr/bin/env python3
# Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
"""Compare a frozen runner with semantic preparation, using explicit commands.

The JSON config contains jobs with name, kind (gemma, llm, vision), before and
after argv arrays, and an execution contract (LLM) or validation fixtures (vision).
Use separate check and measure invocations. Environment variables in argv and
paths are expanded; output directories, warmups, repetitions and dumps are owned
by this tool. Timed processes run sequentially in alternating paired order.
"""
import argparse
import hashlib
import json
import math
import os
from pathlib import Path
import statistics
import subprocess
import platform

import numpy as np


def read(path):
    return json.loads(Path(path).read_text())


def save(path, value):
    Path(path).write_text(json.dumps(value, indent=2) + '\n')


def digest(path):
    with Path(path).open('rb') as f:
        return hashlib.file_digest(f, 'sha256').hexdigest()


def conditions():
    paths = list(Path('/sys/class/thermal').glob('thermal_zone*/temp'))
    for name in ['scaling_governor', 'scaling_cur_freq', 'scaling_min_freq', 'scaling_max_freq']:
        paths += list(Path('/sys/devices/system/cpu').glob(f'cpu*/cpufreq/{name}'))
    result = {}
    for path in paths:
        try:
            result[str(path)] = path.read_text().strip()
        except OSError:
            pass
    return result


def expand(value):
    if isinstance(value, str):
        return os.path.expandvars(value)
    if isinstance(value, list):
        return [expand(v) for v in value]
    if isinstance(value, dict):
        return {k: expand(v) for k, v in value.items()}
    return value


def rows(root):
    result = []
    for line in (root / 'timings.jsonl').read_text().splitlines():
        r = json.loads(line)
        r['rep'] = r.get('rep', r.get('repetition'))
        r['position'] = r.get('position', r.get('context'))
        if r['rep'] >= 0:
            result.append(r)
    return result


def compare(job, before, after):
    checked = 0

    def exact(a, b, name):
        nonlocal checked
        if a != b:
            raise ValueError('Output mismatch: ' + name)
        checked += 1

    if job['kind'] == 'vision':
        fixtures = Path(job['fixtures'])
        contract = read(fixtures / 'fixtures.json')
        errors = []
        for i, sample in enumerate(contract['samples']):
            for key in ['input', 'expected']:
                if digest(fixtures / sample[key]) != sample[key + '_sha256']:
                    raise ValueError('Vision fixture identity mismatch')
            name = f'output_{i}.bin'
            exact((before / name).read_bytes(), (after / name).read_bytes(), name)
            got = np.fromfile(after / name, dtype='<f4')
            expected = np.fromfile(fixtures / sample['expected'], dtype='<f4')
            if not np.isfinite(got).all():
                raise ValueError('Nonfinite vision output')
            np.testing.assert_allclose(got, expected, rtol=1e-3, atol=1e-4)
            errors.append(float(np.max(np.abs(got.astype('f8') - expected))))
        return dict(exact_arrays=checked, reference_max_abs=errors)

    a, b = rows(before), rows(after)
    keys = ['case', 'rep', 'step', 'position', 'argmax']
    if [[r[k] for k in keys] for r in a] != [[r[k] for k in keys] for r in b]:
        raise ValueError('Execution/token sequence differs')
    exact((before / 'resolved_cases.tsv').read_bytes(),
          (after / 'resolved_cases.tsv').read_bytes(), 'resolved tokens')
    spec = read(job['execution'])
    capacity = read(after / 'run.json')['cache_capacity']
    for r in b:
        name = f"{r['case']}_r{r['rep']}_s{r['step']}"
        path = after / (name + '.logits.bin')
        if not np.isfinite(np.fromfile(path, dtype='<f4')).all():
            raise ValueError('Nonfinite logits')
        if job['kind'] == 'gemma':
            old = r['case'] + ('.prefill.f32' if r['step'] == 0 else f".decode_{r['step']:04d}.f32")
            exact((before / old).read_bytes(), path.read_bytes(), name)
            for resource in spec['resources']:
                role, owner = resource['name'].removeprefix('cache_').split('_')
                heads, width = resource['shape'][1], resource['shape'][-1]
                size = {'int8': 1, 'bf16': 2, 'fp32': 4}[resource['dtype']]
                ext = {'int8': 'i8', 'bf16': 'bf16', 'fp32': 'f32'}[resource['dtype']]
                data = (after / f"{name}_{resource['name']}.bin").read_bytes()
                if len(data) != heads * capacity * width * size:
                    raise ValueError('Cache allocation size differs')
                for h in range(heads):
                    suffix = f'.head{h}' if heads > 1 else ''
                    filename = old + f'.owner{owner}{suffix}.{role[0]}.{ext}'
                    start = h * capacity * width * size
                    exact((before / filename).read_bytes(),
                          data[start:start + r['position'] * width * size], filename)
        else:
            exact((before / path.name).read_bytes(), path.read_bytes(), name)
    if job['kind'] == 'llm':
        # The frozen general runner records final KV and recurrent state.
        for case in {r['case'] for r in b}:
            for state in [s['name'] for s in spec['resources']] + [s['input'] for s in spec['fixed_states']]:
                name = f'{case}_r0_{state}.bin'
                exact((before / name).read_bytes(), (after / name).read_bytes(), name)
    counters = read(after / 'counters.json')
    if any(c['view_copy_bytes'] for c in counters):
        raise ValueError('History view copied')
    if job['kind'] == 'gemma':
        old_append = a[-1]['append_bytes']
    else:
        old_counters = read(before / 'counters.json')
        if any(c['view_copy_bytes'] for c in old_counters):
            raise ValueError('Control copied history')
        old_append = sum(c['append_bytes'] for c in old_counters)
    if sum(c['append_bytes'] for c in counters) != old_append:
        raise ValueError('Append traffic differs')
    return dict(exact_arrays=checked, steps=len(b), append_bytes=old_append, view_copy_bytes=0)


def metrics(job, root):
    if job['kind'] == 'vision':
        d = read(root / 'measurements.json')
        return dict(setup_ms=d['setup_ms'], retained_bytes=d['prepared_rss_bytes'],
                    peak_bytes=d['peak_rss_bytes'], **{
                        f'input{i}.invoke_ms': statistics.median(c['inference_ms'])
                        for i, c in enumerate(d['cases'])})
    data = rows(root)
    if (root / 'setup.json').exists():
        setup, memory = read(root / 'setup.json'), read(root / 'memory.json')
        result = dict(setup_ms=setup['setup_ms'], retained_bytes=setup['rss_bytes'],
                      peak_bytes=memory['peak_rss_bytes'])
    else:
        result = dict(setup_ms=data[0]['setup_ms'], retained_bytes=data[0]['setup_rss_kib']*1024,
                      peak_bytes=max(r['peak_rss_kib'] for r in data)*1024)
    for case in sorted({r['case'] for r in data}):
        first = [r for r in data if r['case'] == case and r['step'] == 0]
        decode = [r for r in data if r['case'] == case and r['step'] > 0]
        if first[0]['position'] > 1:
            result[case + '.prefix_ms'] = statistics.median(r['prefix_ms'] for r in first)
        result[case + '.ttft_ms'] = statistics.median(r['prefix_ms'] + r['token_ms'] for r in first)
        if decode:
            result[case + '.decode_ms'] = statistics.mean(r['token_ms'] for r in decode)
    return result


def confidence(values):
    """Paired-process bootstrap, with requests kept within each process."""
    logs = np.log(np.asarray(values, dtype='f8'))
    draws = np.random.default_rng(1729).choice(logs, size=(10000, len(logs)), replace=True).mean(axis=1)
    return dict(ratio=math.exp(float(logs.mean())), upper95=math.exp(float(np.quantile(draws, .95))))


def summarize(records):
    results = {}
    for name, pairs in records.items():
        result = {}
        for key in pairs[0]['before']:
            a = [p['before'][key] for p in pairs]
            b = [p['after'][key] for p in pairs]
            stat = confidence([y/x for x, y in zip(a, b)])
            if key in ('retained_bytes', 'peak_bytes'):
                absolute, relative = (64 << 20, .05) if key == 'retained_bytes' else (256 << 20, .10)
                stat['max_increase_bytes'] = max(y-x for x, y in zip(a, b))
                stat['pass'] = all(y-x <= max(absolute, relative*x) for x, y in zip(a, b))
            else:
                stat['pass'] = stat['upper95'] <= (1.25 if key == 'setup_ms' else 1.05)
            result[key] = stat
        results[name] = result
    return results


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--config', type=Path, required=True)
    parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--mode', choices=['check', 'measure'], default='check')
    parser.add_argument('--checks', type=Path, help='Successful check output required before measuring')
    parser.add_argument('--jobs', nargs='+')
    parser.add_argument('--pairs', type=int, default=6)
    parser.add_argument('--runs', type=int, default=3)
    args = parser.parse_args()
    config = expand(read(args.config))
    jobs = [j for j in config['jobs'] if not args.jobs or j['name'] in args.jobs]
    if not jobs or (args.mode == 'measure' and (args.pairs < 6 or args.runs < 3 or not args.checks)):
        parser.error('Select jobs; measurements require successful checks, >=6 pairs and >=3 requests')
    args.output.mkdir(parents=True, exist_ok=False)
    # Track every executable, package identity and input path in the commands.
    identities = {}
    for j in jobs:
        paths = set()
        for cmd in [j['before'], j['after']]:
            for arg in cmd:
                p = Path(arg.split('=', 1)[-1])
                if p.is_file():
                    paths.add(p)
                elif p.is_dir():
                    paths.update(p/name for name in ['model.json', 'manifest.json', 'execution.json'] if (p/name).exists())
        identities[j['name']] = {str(p): digest(p) for p in sorted(paths)}
    save(args.output/'identities.json', identities)
    save(args.output/'host.json', dict(platform=platform.platform(),
        topology=subprocess.check_output(['lscpu', '-e'], text=True),
        initial_conditions=conditions(), environment={k:os.environ.get(k) for k in ['LAB_YNN_MATH']},
        provenance=config.get('provenance', {})))
    if args.mode == 'measure':
        checks = read(args.checks/'checks.json')
        checked_ids = read(args.checks/'identities.json')
        for j in jobs:
            if not checks.get(j['name']) or checked_ids.get(j['name']) != identities[j['name']]:
                raise ValueError('Correctness identity differs from measurement: '+j['name'])
    commands, checks, records, observations = [], {}, {}, []

    def run(job, engine, label):
        for path, expected in identities[job['name']].items():
            if digest(path) != expected:
                raise ValueError('Input/binary changed during comparison: '+path)
        output = args.output/label
        cmd = job[engine] + [f'--output_dir={output.resolve()}',
            f'--warmup_runs={1 if job["kind"] == "vision" or args.mode == "measure" else 0}',
            f'--measured_runs={args.runs if args.mode == "measure" else 1}']
        if args.mode == 'check':
            cmd.append('--dump_outputs')
            if job['kind'] == 'gemma' and engine == 'after':
                cmd.append('--dump_state_steps')
        commands.append(cmd)
        save(args.output/'commands.json', commands)
        observation = dict(label=label, before=conditions())
        with (args.output/(label+'.log')).open('wb') as log:
            subprocess.run(cmd, stdout=log, stderr=subprocess.STDOUT, check=True)
        observation['after'] = conditions()
        observations.append(observation)
        save(args.output/'conditions.json', observations)
        return output

    for job in jobs:
        name = job['name']
        if args.mode == 'check':
            a = run(job, 'before', name+'-before')
            b = run(job, 'after', name+'-after')
            checks[name] = compare(job, a, b)
            save(args.output/'checks.json', checks)
            print(name, checks[name], flush=True)
        else:
            records[name] = []
            for pair in range(args.pairs):
                result = {}
                for engine in (['before', 'after'] if pair % 2 == 0 else ['after', 'before']):
                    output = run(job, engine, f'{name}-p{pair}-{engine}')
                    result[engine] = metrics(job, output)
                records[name].append(result)
                save(args.output/'measurements.json', records)
                print(name, 'pair', pair, flush=True)
            save(args.output/'gates.json', summarize(records))
    if args.mode == 'measure' and not all(
            metric['pass'] for job in summarize(records).values() for metric in job.values()):
        raise SystemExit('Comparison gates did not all pass; inspect gates.json before accepting the change')


if __name__ == '__main__':
    main()
