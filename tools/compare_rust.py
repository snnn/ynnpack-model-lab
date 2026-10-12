# Copyright 2026 @snnn.
# SPDX-License-Identifier: Apache-2.0
"""Compare canonical Rust runners with archived C++ controls, sequentially.

Checks exact logits/KV and vision reference tolerances before measuring latency.
Outputs are retained under a fresh directory. No private compiler is needed.
"""
import argparse
import hashlib
import json
import os
from pathlib import Path
import platform
import statistics
import subprocess

ROOT = Path(__file__).resolve().parents[1]
VISION = ('resnet18', 'resnet34', 'resnet50', 'resnet101', 'resnet152',
          'resnext50_32x4d', 'wide_resnet50_2', 'mobilenet_v2')
LENGTHS = (1, 128, 129, 130, 511, 512, 513, 1024)


def digest(path):
    with Path(path).open('rb') as stream:
        return hashlib.file_digest(stream, 'sha256').hexdigest()


def save(path, value):
    path.write_text(json.dumps(value, indent=2) + '\n')


def host_conditions():
    """Observe controls; do not change governors, affinity, or other processes."""
    paths = list(Path('/sys/class/thermal').glob('thermal_zone*/temp'))
    paths += list(Path('/sys/class/hwmon').glob('hwmon*/temp*_input'))
    for name in ('scaling_governor', 'scaling_min_freq', 'scaling_max_freq', 'scaling_cur_freq'):
        paths += list(Path('/sys/devices/system/cpu').glob(f'cpu*/cpufreq/{name}'))
    values = {}
    for path in paths:
        try:
            values[str(path)] = path.read_text().strip()
        except OSError:
            pass
    return values


def exact_dumps(cpp, rust, pattern):
    def dumps(root):
        return sorted(p.name for p in root.glob(pattern) if pattern != '*.*' or p.suffix in ('.f32', '.i8', '.bf16'))
    files = dumps(cpp)
    other = dumps(rust)
    if not files or files != other:
        raise ValueError('Missing/mismatched output files')
    for name in files:
        if (cpp / name).read_bytes() != (rust / name).read_bytes():
            raise ValueError(f'Rust/C++ output differs: {name}')
    return len(files)


def vision_assets(model):
    import numpy as np
    generated = ROOT / 'models/vision' / model / 'generated'
    fixtures = ROOT / 'assets/vision' / model / 'validation'
    metadata = json.loads((generated / 'model.json').read_text())
    for name, entry in metadata['parameters'].items():
        path = generated / 'parameters' / name
        if path.stat().st_size != entry['bytes'] or digest(path) != entry['sha256']:
            raise ValueError(f'Parameter mismatch: {path}')
    contract = json.loads((fixtures / 'fixtures.json').read_text())
    for sample in contract['samples']:
        for key in ('input', 'expected'):
            if digest(fixtures / sample[key]) != sample[key + '_sha256']:
                raise ValueError(f'Fixture mismatch: {sample[key]}')
    inputs = [fixtures / s['input'] for s in contract['samples']]

    def validate(directory):
        errors = []
        for i, sample in enumerate(contract['samples']):
            actual = np.fromfile(directory / f'output_{i}.bin', dtype='<f4')
            expected = np.fromfile(fixtures / sample['expected'], dtype='<f4')
            if not np.isfinite(actual).all():
                raise ValueError('Non-finite vision output')
            np.testing.assert_allclose(actual, expected, atol=1e-4, rtol=1e-3)
            errors.append(float(np.max(np.abs(actual.astype('f8') - expected))))
        return errors

    identity = dict(model_json=digest(generated / 'model.json'),
                    fixtures_json=digest(fixtures / 'fixtures.json'))
    options = [f'--model_dir={generated}'] + [f'--input_file={p}' for p in inputs]
    return options, validate, identity


def gemma_assets(model, output, supplied_cases, lengths):
    bundle = ROOT / 'assets' / model / 'bundle'
    parameters = ROOT / 'assets' / model / 'parameters'
    source = ROOT / 'models' / model / 'fixtures/correctness.tsv'
    cases = output / f'{model}.tsv'
    if supplied_cases:
        cases.write_bytes(supplied_cases.read_bytes())
    else:
        # Keep the model's own published token fixture and continuation IDs.
        rows = [line.split('\t') for line in source.read_text().splitlines() if line]
        longest = max(rows, key=lambda row: len(row[1].split(',')))
        tokens = longest[1].split(',')
        if len(tokens) < max(lengths):
            raise ValueError('Source fixture is shorter than a requested prompt')
        cases.write_text(''.join(f'p{n}\t{",".join(tokens[:n])}\t{longest[2]}\n'
                                 for n in lengths))
    identity = dict(bundle_manifest=digest(bundle / 'manifest.json'),
                    cases_sha256=digest(cases),
                    parameters={p.name: digest(p) for p in sorted(parameters.glob('*.bin'))})
    options = [f'--bundle_dir={bundle}', f'--parameter_dir={parameters}',
               f'--cases_file={cases}', '--prefill_rows=128']
    return options, identity


def summary_records(kind, directory):
    if kind == 'vision':
        record = json.loads((directory / 'measurements.json').read_text())
        return dict(setup_ms=record['setup_ms'], peak_rss_kib=record['peak_rss_bytes']/1024,
                    cases={str(i): dict(inference_ms=statistics.median(c['inference_ms']))
                           for i, c in enumerate(record['cases'])})
    rows = [json.loads(line) for line in (directory / 'timings.jsonl').read_text().splitlines()]
    if not rows:
        raise ValueError('Missing Gemma timings')
    cases = {}
    for name in sorted({r['case'] for r in rows}):
        measured = [r for r in rows if r['case'] == name and r['repetition'] >= 0]
        first = [r for r in measured if r['step'] == 0]
        decode = [r for r in measured if r['step'] > 0]
        cases[name] = dict(prefix_ms=statistics.median(r['prefix_ms'] for r in first),
                           warm_ttft_ms=statistics.median(r['prefix_ms']+r['token_ms'] for r in first))
        if decode:
            cases[name]['decode_ms'] = statistics.mean(r['token_ms'] for r in decode)
    return dict(setup_ms=rows[0]['setup_ms'],
                peak_rss_kib=max(r['peak_rss_kib'] for r in rows), cases=cases)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('kind', choices=('vision', 'gemma'))
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--control-dir', type=Path, required=True,
                        help='Archived C++ binaries; this checkout no longer builds them')
    parser.add_argument('--models', nargs='+')
    parser.add_argument('--plans-dir', type=Path,
                        help='Compare runners that load MODEL/*.ynn without C++ builders')
    parser.add_argument('--threads', nargs='+', type=int, default=[1, 4])
    parser.add_argument('--capacities', nargs='+', type=int, default=[2048, 8448])
    parser.add_argument('--cases-file', type=Path)
    parser.add_argument('--prompt-lengths', nargs='+', type=int, default=LENGTHS)
    parser.add_argument('--cpus-1', required=True)
    parser.add_argument('--cpus-4', required=True)
    parser.add_argument('--warmup', type=int, default=1)
    parser.add_argument('--runs', type=int, default=3)
    parser.add_argument('--repeats', type=int, default=3)
    parser.add_argument('--check-only', action='store_true')
    args = parser.parse_args()
    if args.plans_dir:
        args.plans_dir = args.plans_dir.resolve()
    choices = VISION if args.kind == 'vision' else ('gemma4_e2b', 'gemma4_e4b')
    models = args.models or choices
    if any(m not in choices for m in models) or any(t not in (1, 4) for t in args.threads):
        parser.error('Unsupported model or thread count')
    if min(args.warmup, args.runs, args.repeats) < 1:
        parser.error('Measurement counts must be positive')
    if min(args.prompt_lengths) < 1 or len(set(args.prompt_lengths)) != len(args.prompt_lengths):
        parser.error('Prompt lengths must be positive and distinct')
    allowed = os.sched_getaffinity(0)
    affinities = {1: args.cpus_1, 4: args.cpus_4}
    for count, affinity in affinities.items():
        cpus = set(map(int, affinity.split(',')))
        if len(cpus) != count or not cpus <= allowed:
            parser.error(f'Choose {count} distinct available CPUs for --cpus-{count}')
    args.output.mkdir(parents=True, exist_ok=False)
    build = args.build_dir.resolve()
    identity = dict(host=platform.platform(), affinity=affinities,
                    cpu_topology=subprocess.check_output(['lscpu', '-e'], text=True),
                    build_cache=(build / 'CMakeCache.txt').read_text(),
                    compile_commands_sha256=digest(build / 'compile_commands.json') if (build / 'compile_commands.json').exists() else None,
                    cargo_lock_sha256=digest(ROOT / 'rust/Cargo.lock'),
                    rustc=subprocess.check_output(['rustc', '--version'], text=True).strip(),
                    host_conditions=host_conditions(), models={})
    configurations = []

    def binary_for(target, rust):
        if not rust:
            return args.control_dir.resolve() / target
        return build / ('vision' if args.kind == 'vision' else target)

    for model in models:
        target = f'vision_{model}' if args.kind == 'vision' else model
        if args.kind == 'vision':
            options, validate, asset_identity = vision_assets(model)
            capacities = [None]
        else:
            options, asset_identity = gemma_assets(model, args.output, args.cases_file, args.prompt_lengths)
            validate = None
            capacities = args.capacities
        asset_identity['binaries'] = {key: digest(binary_for(target, rust))
                                     for key, rust in [('cpp', False), ('_rust', True)]}
        if args.plans_dir:
            directory = args.plans_dir / model
            names = ['graph.ynn'] if args.kind == 'vision' else [
                'gemma4_prefill.ynn', 'gemma4_decode.ynn']
            asset_identity['plans'] = {name: digest(directory / name) for name in names}
            asset_identity['plan_parameters'] = {
                p.name: digest(p) for p in sorted((directory / 'parameters').glob('*.bin'))}
            if args.kind == 'vision':
                original = json.loads((ROOT / 'models/vision' / model / 'generated/model.json').read_text())
                candidate = json.loads((directory / 'model.json').read_text())
                if candidate != original:
                    raise ValueError(f'Plan model metadata/parameter identities changed: {model}')
        identity['models'][model] = asset_identity
        for threads in args.threads:
            for capacity in capacities:
                label = f'{model}_t{threads}' + (f'_c{capacity}' if capacity else '')
                invocation = options + [f'--num_threads={threads}']
                if capacity:
                    invocation.append(f'--cache_capacity={capacity}')
                configurations.append((label, target, threads, invocation, validate))
    save(args.output / 'identity.json', identity)
    commands, checks, timings = [], [], []
    conditions = []

    def run(config, rust, label, check):
        _, target, threads, options, _ = config
        directory = (args.output / label).resolve()
        model = target.removeprefix('vision_') if args.kind == 'vision' else target
        binary = binary_for(target, rust)
        if digest(binary) != identity['models'][model]['binaries']['_rust' if rust else 'cpp']:
            raise ValueError('Runner changed during comparison; use a fresh run directory')
        if rust and args.plans_dir:
            plans = args.plans_dir / model
            for name, expected in identity['models'][model]['plans'].items():
                if digest(plans / name) != expected:
                    raise ValueError('Graph artifact changed during comparison')
            if args.kind == 'vision':
                options = [o for o in options if not o.startswith('--model_dir=')]
                options += [f'--model_dir={plans}', f'--graph_file={plans / "graph.ynn"}']
            else:
                options = [o for o in options if not o.startswith('--parameter_dir=')]
                options += [f'--parameter_dir={plans / "parameters"}', f'--graph_dir={plans}']
        cmd = ['taskset', '-c', affinities[threads], str(binary),
               *options, f'--output_dir={directory}',
               f'--warmup_runs={int(args.kind == "vision") if check else args.warmup}',
               f'--measured_runs={1 if check else args.runs}']
        if check:
            cmd.append('--dump_outputs')
        commands.append(cmd)
        save(args.output / 'commands.json', commands)
        condition = dict(label=label, before=host_conditions())
        with (args.output / f'{label}.log').open('wb') as log:
            subprocess.run(cmd, stdout=log, stderr=subprocess.STDOUT, check=True)
        condition['after'] = host_conditions()
        conditions.append(condition)
        save(args.output / 'host_conditions.json', conditions)
        return directory

    # Complete correctness for the entire matrix before emitting performance.
    for config in configurations:
        label, _, _, _, validate = config
        cpp = run(config, False, f'check_{label}_cpp', True)
        rust = run(config, True, f'check_{label}_rust', True)
        files = exact_dumps(cpp, rust, 'output_*.bin' if args.kind == 'vision' else '*.*')
        check = dict(configuration=label, exact_dump_files=files)
        if validate:
            check['pytorch_max_abs'] = validate(rust)
        else:
            a = [json.loads(s) for s in (cpp / 'timings.jsonl').read_text().splitlines()]
            b = [json.loads(s) for s in (rust / 'timings.jsonl').read_text().splitlines()]
            keys = ('case', 'repetition', 'step', 'context', 'argmax', 'append_bytes', 'view_copy_bytes')
            if [[r[k] for k in keys] for r in a] != [[r[k] for k in keys] for r in b]:
                raise ValueError('Gemma state/counter records differ')
            if any(r['view_copy_bytes'] for r in b):
                raise ValueError('History view copy detected')
        checks.append(check)
        save(args.output / 'checks.json', checks)
        print(f'{label}: {files} exact output/KV files', flush=True)
    if args.check_only:
        return
    for config in configurations:
        for repetition in range(args.repeats):
            for rust in ((False, True) if repetition % 2 == 0 else (True, False)):
                engine = 'rust' if rust else 'cpp'
                label = f'perf_{config[0]}_r{repetition}_{engine}'
                directory = run(config, rust, label, False)
                timings.append(dict(configuration=config[0], runner=engine, repetition=repetition,
                                    **summary_records(args.kind, directory)))
                save(args.output / 'timings.json', timings)
            print(f'{config[0]}: paired repetition {repetition}', flush=True)


if __name__ == '__main__':
    main()
