# Copyright 2026 @snnn.
# SPDX-License-Identifier: Apache-2.0
"""Verify standalone vision plans, then compare sequential CPU invocations.

Requires NumPy and ai-edge-litert for the baseline. PyTorch reference tensors
and generated parameters are supplied as assets; no model compiler is imported.
"""
import argparse
import hashlib
import importlib.metadata
import json
import os
from pathlib import Path
import platform
import resource
import statistics
import subprocess
import sys
import time

MODELS = ('resnet18', 'resnet34', 'resnet50', 'resnet101', 'resnet152',
          'resnext50_32x4d', 'wide_resnet50_2', 'mobilenet_v2')
ROOT = Path(__file__).resolve().parents[1]


def digest(path):
    with Path(path).open('rb') as source:
        return hashlib.file_digest(source, 'sha256').hexdigest()


def save(path, data):
    Path(path).write_text(json.dumps(data, indent=2)+'\n')


def rss():
    return int(Path('/proc/self/statm').read_text().split()[1])*os.sysconf('SC_PAGE_SIZE')


def litert(args):
    import numpy as np
    from ai_edge_litert.interpreter import Interpreter
    args.output.mkdir(parents=True, exist_ok=False)
    base_rss = rss()
    start = time.perf_counter_ns()
    runtime = Interpreter(model_path=str(args.model), num_threads=args.threads)
    runtime.allocate_tensors()
    setup_ms = (time.perf_counter_ns()-start)/1e6
    prepared_rss = rss()
    operators = runtime._get_ops_details()
    delegates = sum(op['op_name'] == 'DELEGATE' for op in operators)
    if not delegates:
        raise RuntimeError('No default XNNPACK delegate partition was created')
    ins, outs = runtime.get_input_details(), runtime.get_output_details()
    if len(ins) != 1 or len(outs) != 1 or ins[0]['dtype'] != np.float32 or outs[0]['dtype'] != np.float32:
        raise ValueError('Expected single-input/output FP32 classification model')
    record = dict(engine='litert_xnnpack', threads=args.threads, setup_ms=setup_ms,
                  base_rss_bytes=base_rss, prepared_rss_bytes=prepared_rss,
                  delegate_partitions=delegates,
                  ai_edge_litert=importlib.metadata.version('ai-edge-litert'), cases=[])
    for case_id, path in enumerate(args.inputs):
        x = np.fromfile(path, dtype='<f4').reshape(ins[0]['shape'])
        runtime.set_tensor(ins[0]['index'], x)
        first_ms = 0
        for i in range(args.warmup):
            begin = time.perf_counter_ns()
            runtime.invoke()
            if i == 0:
                first_ms = (time.perf_counter_ns()-begin)/1e6
        observations = []
        for _ in range(args.runs):
            begin = time.perf_counter_ns()
            runtime.invoke()
            observations.append((time.perf_counter_ns()-begin)/1e6)
        y = runtime.get_tensor(outs[0]['index'])
        if not np.isfinite(y).all():
            raise ValueError('Non-finite LiteRT output')
        if args.dump:
            y.tofile(args.output/f'output_{case_id}.bin')
        record['cases'].append(dict(first_invoke_ms=first_ms, inference_ms=observations,
                                    rss_bytes=rss()))
    record['peak_rss_bytes'] = resource.getrusage(resource.RUSAGE_SELF).ru_maxrss*1024
    save(args.output/'measurements.json', record)


def compare(args):
    import numpy as np
    args.output.mkdir(parents=True, exist_ok=False)
    if len(os.sched_getaffinity(0)) < 4:
        raise ValueError('This comparison requires at least four available CPUs')
    identities = dict(platform=platform.platform(), python=sys.version,
                      cpuinfo=Path('/proc/cpuinfo').read_text().split('\n\n')[0],
                      affinity={1: args.cpus_1, 4: args.cpus_4},
                      dependencies=json.loads((ROOT/'dependencies.json').read_text()),
                      conditions='Fixed affinity; clocks/governor unchanged; sequential processes',
                      warmup=args.warmup, runs=args.runs, repetitions=args.repeats,
                      timing='Warm invocation, input binding/output copying excluded. LiteRT includes Python invoke wrapper.',
                      memory='Fresh-process RSS includes each frontend; report current, incremental and peak separately.',
                      models={})
    for name in args.models:
        generated = ROOT/'models/vision'/name/'generated'
        metadata = json.loads((generated/'model.json').read_text())
        fixtures = ROOT/'assets/vision'/name/'validation'
        contract = json.loads((fixtures/'fixtures.json').read_text())
        for file, item in metadata['parameters'].items():
            path = generated/'parameters'/file
            if path.stat().st_size != item['bytes'] or digest(path) != item['sha256']:
                raise ValueError('Parameter identity mismatch: '+str(path))
        for case in contract['samples']:
            for key in ('input', 'expected'):
                if digest(fixtures/case[key]) != case[key+'_sha256']:
                    raise ValueError('Fixture identity mismatch: '+name)
        binary = args.build_dir/'vision'
        model = args.tflite_root/name/'model.tflite'
        identities['models'][name] = dict(metadata=metadata, fixtures=contract,
                                          binary_sha256=digest(binary), tflite_sha256=digest(model))
    save(args.output/'identity.json', identities)
    validations, jobs, observations = [], [], []

    def run(name, threads, engine, label, validation=False):
        directory = args.output/label
        fixtures = ROOT/'assets/vision'/name/'validation'
        contract = identities['models'][name]['fixtures']
        inputs = [fixtures/c['input'] for c in contract['samples']]
        if not validation:
            inputs = inputs[-1:]  # Same transformed photograph in both engines.
        cpus = args.cpus_1 if threads == 1 else args.cpus_4
        runs, warmup = (1, 1) if validation else (args.runs, args.warmup)
        if engine == 'ynnpack':
            command = ['taskset', '-c', cpus, str(args.build_dir/'vision'),
                       '--model_dir='+str(ROOT/'models/vision'/name/'generated'),
                       '--output_dir='+str(directory), '--num_threads='+str(threads),
                       '--warmup_runs='+str(warmup), '--measured_runs='+str(runs)]
            command += ['--input_file='+str(path) for path in inputs]
            if validation:
                command.append('--dump_outputs')
        else:
            command = ['taskset', '-c', cpus, sys.executable, str(Path(__file__).resolve()),
                       'litert', '--model', str(args.tflite_root/name/'model.tflite'),
                       '--output', str(directory), '--threads', str(threads),
                       '--warmup', str(warmup), '--runs', str(runs), '--inputs', *map(str, inputs)]
            if validation:
                command.append('--dump')
        job = dict(model=name, threads=threads, engine=engine, label=label, argv=command)
        print(label, flush=True)
        with (args.output/(label+'.log')).open('w') as log:
            result = subprocess.run(command, stdout=log, stderr=subprocess.STDOUT)
        job['returncode'] = result.returncode
        jobs.append(job)
        save(args.output/'commands.json', jobs)
        if result.returncode:
            raise RuntimeError('Execution failed: '+label+'; see retained log')
        record = json.loads((directory/'measurements.json').read_text())
        if validation:
            for i, case in enumerate(contract['samples']):
                actual = np.fromfile(directory/f'output_{i}.bin', dtype='<f4')
                expected = np.fromfile(fixtures/case['expected'], dtype='<f4')
                np.testing.assert_allclose(actual, expected, atol=contract['atol'], rtol=contract['rtol'])
                error = actual.astype('f8')-expected
                validations.append(dict(model=name, threads=threads, engine=engine, case=i,
                                        max_abs=float(np.max(np.abs(error))), mae=float(np.mean(np.abs(error))),
                                        cosine=float(np.dot(actual.astype('f8'), expected)/(np.linalg.norm(actual.astype('f8'))*np.linalg.norm(expected.astype('f8')))),
                                        top1_match=bool(np.argmax(actual) == np.argmax(expected)), passed=True))
                save(args.output/'validation.json', validations)
        return record

    for name in args.models:
        for threads in (1, 4):
            for engine in ('ynnpack', 'litert_xnnpack'):
                run(name, threads, engine, f'validate_{name}_t{threads}_{engine}', True)
    # No latency claim is emitted until every requested correctness case passes.
    for name in args.models:
        for threads in (1, 4):
            for repetition in range(args.repeats):
                engines = ('ynnpack', 'litert_xnnpack') if repetition % 2 == 0 else ('litert_xnnpack', 'ynnpack')
                for engine in engines:
                    label = f'perf_{name}_t{threads}_r{repetition}_{engine}'
                    record = run(name, threads, engine, label)
                    observations.append(dict(model=name, threads=threads, repetition=repetition,
                                             engine=engine, measurements=record))
                    save(args.output/'observations.json', observations)
    summary = []
    for name in args.models:
        for threads in (1, 4):
            row = dict(model=name, threads=threads)
            for engine in ('ynnpack', 'litert_xnnpack'):
                records = [r['measurements'] for r in observations if r['model'] == name and r['threads'] == threads and r['engine'] == engine]
                medians = [statistics.median(r['cases'][0]['inference_ms']) for r in records]
                row[engine] = dict(median_ms=statistics.median(medians), run_medians_ms=medians,
                                   setup_ms=statistics.median(r['setup_ms'] for r in records),
                                   first_invoke_ms=statistics.median(r['cases'][0]['first_invoke_ms'] for r in records),
                                   rss_mib=statistics.median(r['cases'][0]['rss_bytes']/2**20 for r in records),
                                   incremental_rss_mib=statistics.median((r['cases'][0]['rss_bytes']-r['base_rss_bytes'])/2**20 for r in records),
                                   peak_rss_mib=statistics.median(r['peak_rss_bytes']/2**20 for r in records))
            row['ynn_over_litert_latency'] = row['ynnpack']['median_ms']/row['litert_xnnpack']['median_ms']
            summary.append(row)
    save(args.output/'summary.json', summary)
    for row in summary:
        print(f"{row['model']:20} t{row['threads']}: YNN {row['ynnpack']['median_ms']:.3f} ms, "
              f"LiteRT/XNN {row['litert_xnnpack']['median_ms']:.3f} ms, "
              f"ratio {row['ynn_over_litert_latency']:.2f}")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    sub = parser.add_subparsers(dest='command', required=True)
    baseline = sub.add_parser('litert')
    baseline.add_argument('--model', type=Path, required=True)
    baseline.add_argument('--inputs', type=Path, nargs='+', required=True)
    baseline.add_argument('--threads', type=int, required=True)
    baseline.add_argument('--dump', action='store_true')
    paired = sub.add_parser('compare')
    paired.add_argument('--build-dir', type=Path, required=True)
    paired.add_argument('--tflite-root', type=Path, required=True)
    paired.add_argument('--models', nargs='+', choices=MODELS, default=MODELS)
    paired.add_argument('--cpus-1', required=True)
    paired.add_argument('--cpus-4', required=True)
    paired.add_argument('--repeats', type=int, default=3)
    for item in (baseline, paired):
        item.add_argument('--output', type=Path, required=True)
        item.add_argument('--warmup', type=int, default=3)
        item.add_argument('--runs', type=int, default=30)
    args = parser.parse_args()
    if args.warmup < 1 or args.runs < 1 or getattr(args, 'repeats', 1) < 1:
        parser.error('Run counts must be positive')
    (litert if args.command == 'litert' else compare)(args)


if __name__ == '__main__':
    main()
