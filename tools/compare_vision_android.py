# Copyright 2026 @snnn.
# SPDX-License-Identifier: Apache-2.0
"""Deploy and validate FP32 vision models, then compare Android CPU runners.

Devices JSON is a local-only list with label, serial, masks ("1"/"4" -> hex),
and performance_cpus (CPU ID -> expected MIDR hex) for reviewed non-little cores.
Choose masks from device topology. All device processes execute sequentially.
Raw captures belong under ignored out/. No CPU governor or clock is changed.
"""
import argparse
from datetime import datetime, timezone
import json
from pathlib import Path
import re
import shlex
import statistics
import subprocess
import time

from compare_vision import MODELS, ROOT, digest, save


def shell(device, command, timeout=120):
    return subprocess.run(['adb', '-s', device['serial'], 'shell', command],
                          capture_output=True, text=True, timeout=timeout)


def checked_shell(device, command, timeout=120):
    result = shell(device, command, timeout)
    if result.returncode:
        raise RuntimeError(device['label'] + ': ' + result.stdout + result.stderr)
    return result.stdout.strip()


def telemetry(device):
    # Retain only performance-related battery fields, not vendor battery histories.
    battery = shell(device, 'dumpsys battery').stdout
    keys = ('level', 'temperature', 'voltage', 'status', 'USB powered', 'AC powered')
    battery = {k: re.search(r'^\s*' + re.escape(k) + r': (.*)$', battery, re.M).group(1)
               for k in keys if re.search(r'^\s*' + re.escape(k) + r': (.*)$', battery, re.M)}
    sensors = shell(device, '\n'.join([
        'for p in /sys/devices/system/cpu/cpufreq/policy*; do',
        'echo "$p"; for f in related_cpus cpuinfo_max_freq scaling_cur_freq scaling_max_freq scaling_governor; do',
        'echo "$f"; cat "$p/$f"; done; done',
        'for p in /sys/class/thermal/thermal_zone*; do',
        'echo "$p"; cat "$p/type" "$p/temp"; done',
    ]))
    return dict(utc=datetime.now(timezone.utc).isoformat(), battery=battery,
                sensors=sensors.stdout + sensors.stderr,
                sensor_returncode=sensors.returncode)


def cpu_list(value):
    cpus = set()
    for group in value.split(','):
        first, _, last = group.partition('-')
        cpus.update(range(int(first), int(last or first) + 1))
    return cpus


def cpu_topology(device):
    fields = ('regs/identification/midr_el1', 'cpu_capacity', 'topology/cluster_id',
              'topology/core_id', 'topology/thread_siblings_list',
              'cpufreq/related_cpus', 'cpufreq/cpuinfo_max_freq')
    captured = checked_shell(device, '\n'.join([
        'for p in /sys/devices/system/cpu/cpu[0-9]*; do',
        'echo "cpu ${p##*cpu}"',
        'for f in ' + ' '.join(fields) + '; do',
        'printf "%s " "$f"',
        'if [ -r "$p/$f" ]; then cat "$p/$f"; else echo unavailable; fi',
        'done; done',
    ]))
    topology = {}
    for line in captured.splitlines():
        key, _, value = line.partition(' ')
        if key == 'cpu':
            record = topology.setdefault(value, {})
        else:
            record[key.rsplit('/', 1)[-1]] = value if value != 'unavailable' else None
    return topology


def verify_affinity(device, online_cpus, topology):
    # Core classes must be reviewed from MIDR/vendor evidence, not frequency alone.
    reviewed = device.get('performance_cpus')
    if not isinstance(reviewed, dict) or len(reviewed) < 4:
        raise ValueError(device['label'] + ': provide at least four reviewed performance_cpus with MIDRs')
    for cpu, expected in reviewed.items():
        actual = topology.get(cpu, {}).get('midr_el1')
        if not re.fullmatch(r'[0-9]+', cpu) or not actual or int(actual, 16) != int(expected, 16):
            raise ValueError(device['label'] + ': reviewed CPU MIDR mismatch: ' + cpu)
    for threads in ('1', '4'):
        mask = int(device['masks'][threads], 16)
        selected = {cpu for cpu in range(mask.bit_length()) if mask & (1 << cpu)}
        if mask <= 0 or len(selected) != int(threads):
            raise ValueError('Affinity mask must contain the requested number of CPUs')
        if not selected <= cpu_list(online_cpus) or not selected <= {int(cpu) for cpu in reviewed}:
            raise ValueError(device['label'] + ': affinity must use online, reviewed performance CPUs only')


def identify(device):
    properties = {}
    for key in ('ro.product.model', 'ro.soc.model', 'ro.build.fingerprint',
                'ro.build.version.release', 'ro.build.version.sdk'):
        properties[key] = checked_shell(device, 'getprop ' + key)
    online_cpus = checked_shell(device, 'cat /sys/devices/system/cpu/online')
    topology = cpu_topology(device)
    verify_affinity(device, online_cpus, topology)
    return dict(label=device['label'], properties=properties, masks=device['masks'],
                performance_cpus=device['performance_cpus'], cpu_topology=topology,
                kernel=checked_shell(device, 'uname -r'),
                online_cpus=online_cpus,
                memory=checked_shell(device, 'head -5 /proc/meminfo'),
                storage=checked_shell(device, 'df -k /data/local/tmp'),
                initial=telemetry(device))


def model_files(name, tflite_root):
    generated = ROOT / 'models/vision' / name / 'generated'
    fixtures = ROOT / 'assets/vision' / name / 'validation'
    metadata = json.loads((generated / 'model.json').read_text())
    contract = json.loads((fixtures / 'fixtures.json').read_text())
    import sys
    sys.path.insert(0, str(ROOT / 'python'))
    from ynnpack_assets.artifacts import semantic_files
    files = semantic_files(generated)
    files['model.tflite'] = tflite_root / name / 'model.tflite'
    for file, item in metadata['parameters'].items():
        path = generated / 'parameters' / file
        if path.stat().st_size != item['bytes'] or digest(path) != item['sha256']:
            raise ValueError('Parameter identity mismatch: ' + name)
        files['parameters/' + file] = path
    for case in contract['samples']:
        for key in ('input', 'expected'):
            if digest(fixtures / case[key]) != case[key + '_sha256']:
                raise ValueError('Fixture identity mismatch: ' + name)
        files[case['input']] = fixtures / case['input']
    return files, contract


def deploy(device, args, models, log):
    remote = args.remote_root
    checked_shell(device, shlex.join(['mkdir'] + (['-p'] if args.reuse_deployment else []) + [remote]))
    adb = ['adb', '-s', device['serial']]
    files = {'vision': args.ynn_binary, 'benchmark_model': args.benchmark_binary,
             'run_model': args.validation_binary, 'benchmark_input.bin': args.benchmark_input}
    for name, (mapping, contract) in models.items():
        checked_shell(device, shlex.join(['mkdir', '-p', remote + '/' + name + '/parameters']))
        files.update({name + '/' + key: value for key, value in mapping.items()})
        source = ROOT / 'models/vision' / name / 'generated'
        commands = [adb + ['push', '--sync', *[str(p) for k, p in mapping.items() if k in ('model.json', 'execution.json', 'program.ynn')],
                           str(source / 'parameters'), *([str(source / 'program-data')] if (source/'program-data').exists() else []), remote + '/' + name + '/'],
                    adb + ['push', '--sync', str(mapping['model.tflite']), remote + '/' + name + '/model.tflite'],
                    adb + ['push', '--sync', *[str(p) for k, p in mapping.items() if k.startswith('input_')],
                           remote + '/' + name + '/']]
        for argv in commands:
            subprocess.run(argv, stdout=log, stderr=subprocess.STDOUT, check=True, timeout=600)
        for i, case in enumerate(contract['samples']):
            destination = remote + '/' + name + f'/case_{i}'
            checked_shell(device, shlex.join(['mkdir', '-p', destination]))
            checked_shell(device, shlex.join(['cp', remote + '/' + name + '/' + case['input'],
                                             destination + '/' + args.input_name + '.raw']))
            files[name + f'/case_{i}/' + args.input_name + '.raw'] = mapping[case['input']]
    for name in ('vision', 'benchmark_model', 'run_model', 'benchmark_input.bin'):
        subprocess.run(adb + ['push', str(files[name]), remote + '/' + name],
                       stdout=log, stderr=subprocess.STDOUT, check=True, timeout=120)
    checked_shell(device, shlex.join(['chmod', '755', *[remote + '/' + n for n in
                                                      ('vision', 'benchmark_model', 'run_model')]]))
    paths = list(files)
    for begin in range(0, len(paths), 100):
        selected = paths[begin:begin + 100]
        result = checked_shell(device, shlex.join(['sha256sum', *[remote + '/' + p for p in selected]]))
        actual = {line.split(None, 1)[1].strip(): line.split()[0] for line in result.splitlines()}
        for path in selected:
            if actual.get(remote + '/' + path) != digest(files[path]):
                raise ValueError('Deployed identity mismatch: ' + device['label'] + '/' + path)
    return len(files)


def proto_readers(args):
    from google.protobuf import descriptor_pb2, descriptor_pool, message_factory
    descriptor = args.output / 'benchmark-descriptors.pb'
    subprocess.run([str(args.protoc), '--proto_path=' + str(args.litert_root),
                    '--include_imports', '--descriptor_set_out=' + str(descriptor),
                    'tflite/tools/benchmark/proto/benchmark_result.proto',
                    'tflite/profiling/proto/model_runtime_info.proto'], check=True)
    files = descriptor_pb2.FileDescriptorSet.FromString(descriptor.read_bytes())
    pool = descriptor_pool.DescriptorPool()
    for file in files.file:
        pool.Add(file)
    return [message_factory.GetMessageClass(pool.FindMessageTypeByName(name)) for name in
            ('tflite.tools.benchmark.BenchmarkResult', 'tflite.profiling.ModelRuntimeDetails')]


def summarize(observations, devices, models):
    summary = []
    for device in devices:
        for name in models:
            for threads in (1, 4):
                row = dict(device=device['label'], model=name, threads=threads)
                for engine in ('ynnpack', 'litert_xnnpack'):
                    records = [o['measurements'] for o in observations
                               if o['device'] == device['label'] and o['model'] == name
                               and o['threads'] == threads and o['engine'] == engine]
                    if engine == 'ynnpack':
                        means = [statistics.mean(r['cases'][0]['inference_ms']) for r in records]
                        setup = [r['setup_ms'] for r in records]
                        first = [r['cases'][0]['first_invoke_ms'] for r in records]
                    else:
                        means = [r['latency_metrics']['avg_ms'] for r in records]
                        setup = [r['latency_metrics']['init_ms'] for r in records]
                        first = [r['latency_metrics']['first_inference_ms'] for r in records]
                    row[engine] = dict(mean_ms=statistics.mean(means), run_means_ms=means,
                                       setup_ms=statistics.mean(setup), first_invoke_ms=statistics.mean(first))
                row['ynn_over_litert_latency'] = row['ynnpack']['mean_ms'] / row['litert_xnnpack']['mean_ms']
                summary.append(row)
    return summary


def compare(args):
    import numpy as np
    from google.protobuf.json_format import MessageToDict
    devices = json.loads(args.devices_json.read_text())
    if not devices or len({d['label'] for d in devices}) != len(devices):
        raise ValueError('Devices require unique labels')
    for device in devices:
        if not re.fullmatch(r'[a-z0-9_-]+', device['label']):
            raise ValueError('Use a portable device label')
    args.output.mkdir(parents=True, exist_ok=False)
    result_proto, runtime_proto = proto_readers(args)
    models = {name: model_files(name, args.tflite_root) for name in args.models}
    identities = dict(devices=[identify(d) for d in devices],
        binaries={k: digest(v) for k, v in [('vision', args.ynn_binary),
                    ('benchmark_model', args.benchmark_binary), ('run_model', args.validation_binary)]},
        benchmark_input_sha256=digest(args.benchmark_input), input_name=args.input_name,
        output_name=args.output_name,
        models={name: dict(files={key: digest(path) for key, path in files.items()}, fixtures=contract)
                for name, (files, contract) in models.items()},
        warmup=args.warmup, runs=args.runs, repetitions=args.repeats, cooldown_seconds=args.cooldown,
        conditions='Sequential fresh processes, fixed affinity, unchanged governors/unlocked clocks; USB power.',
        timing='Native warm invocation; mean across rounds. LiteRT uses official benchmark_model / CompiledModel::Run.',
        input='Default benchmark_model FP32 random input, reproduced with matching NDK libc++; original fixtures used for correctness.',
        validation='YNNPACK at one/four threads; LiteRT run_model at its default one CPU thread; three PyTorch fixtures.',
        memory='YNNPACK current/peak RSS; native benchmark reports incremental footprint; peak polling disabled.')
    save(args.output / 'identity.json', identities)
    for device in devices:
        print('deploy', device['label'], flush=True)
        with (args.output / (device['label'] + '-deploy.log')).open('w') as log:
            count = deploy(device, args, models, log)
        identities['devices'][devices.index(device)]['verified_remote_files'] = count
        save(args.output / 'identity.json', identities)
    jobs, validations, observations, sensors, delegation = [], [], [], [], []
    last_end = {d['label']: time.monotonic() for d in devices}
    power = {}
    try:
        for device in devices:
            label = device['label']
            power[label] = dict(stay_on=checked_shell(device, 'settings get global stay_on_while_plugged_in'),
                               was_awake='mWakefulness=Awake' in checked_shell(device, 'dumpsys power'))
            checked_shell(device, 'svc power stayon true')
        save(args.output / 'power-original.json', power)

        def execute(device, name, threads, engine, label, argv, create_output=False):
            local, remote = args.output / label, args.remote_root + '/' + label
            if create_output:
                checked_shell(device, shlex.join(['mkdir', remote]))
            delay = args.cooldown - (time.monotonic() - last_end[device['label']])
            if delay > 0:
                time.sleep(delay)
            before = telemetry(device)
            print(label, flush=True)
            started = time.monotonic()
            result = shell(device, shlex.join(argv), args.timeout)
            duration = time.monotonic() - started
            last_end[device['label']] = time.monotonic()
            after = telemetry(device)
            (args.output / (label + '.log')).write_text(result.stdout + result.stderr)
            jobs.append(dict(device=device['label'], model=name, threads=threads, engine=engine,
                label=label, argv=argv, returncode=result.returncode, wall_seconds=duration))
            sensors.append(dict(label=label, before=before, after=after))
            save(args.output / 'commands.json', jobs)
            save(args.output / 'telemetry.json', sensors)
            if result.returncode:
                raise RuntimeError('Execution failed: ' + label)
            subprocess.run(['adb', '-s', device['serial'], 'pull', remote, str(local)],
                           capture_output=True, check=True, timeout=120)
            return local

        def validate(device, name, threads, engine, case_id, actual_path):
            contract = models[name][1]
            case = contract['samples'][case_id]
            actual = np.fromfile(actual_path, dtype='<f4').astype('f8')
            expected = np.fromfile(ROOT / 'assets/vision' / name / 'validation' / case['expected'], dtype='<f4').astype('f8')
            if actual.shape != expected.shape:
                raise ValueError('Output shape mismatch: ' + str(actual_path))
            passed = bool(np.isfinite(actual).all() and np.allclose(actual, expected,
                           atol=contract['atol'], rtol=contract['rtol']))
            error = np.abs(actual - expected)
            validations.append(dict(device=device['label'], model=name, threads=threads, engine=engine,
                case=case_id, max_abs=float(error.max()), mae=float(error.mean()),
                cosine=float(np.dot(actual, expected) / (np.linalg.norm(actual) * np.linalg.norm(expected))),
                top1_match=bool(np.argmax(actual) == np.argmax(expected)), passed=passed,
                output_sha256=digest(actual_path)))
            save(args.output / 'validation.json', validations)
            if not passed:
                raise ValueError('Numerical validation failed: ' + str(actual_path))

        def run_ynn(device, name, threads, repetition=None):
            checking = repetition is None
            label = f"{device['label']}_{name}_t{threads}_ynnpack_" + ('validate' if checking else f'r{repetition}')
            remote = args.remote_root + '/' + label
            model_root = args.remote_root + '/' + name
            argv = ['taskset', device['masks'][str(threads)], args.remote_root + '/vision',
                    '--model_dir=' + model_root, '--output_dir=' + remote,
                    '--num_threads=' + str(threads), '--warmup_runs=' + str(1 if checking else args.warmup),
                    '--measured_runs=' + str(1 if checking else args.runs)]
            if checking:
                argv += ['--input_file=' + model_root + '/' + c['input'] for c in models[name][1]['samples']]
                argv.append('--dump_outputs')
            else:
                argv.append('--input_file=' + args.remote_root + '/benchmark_input.bin')
            local = execute(device, name, threads, 'ynnpack', label, argv)
            if checking:
                for i in range(len(models[name][1]['samples'])):
                    validate(device, name, threads, 'ynnpack', i, local / f'output_{i}.bin')
            else:
                observations.append(dict(device=device['label'], model=name, threads=threads, engine='ynnpack',
                    repetition=repetition, measurements=json.loads((local / 'measurements.json').read_text())))
                save(args.output / 'observations.json', observations)

        def run_litert(device, name, threads, repetition=None):
            diagnostic = repetition is None
            label = f"{device['label']}_{name}_t{threads}_litert_xnnpack_" + ('delegation' if diagnostic else f'r{repetition}')
            remote = args.remote_root + '/' + label
            argv = ['taskset', device['masks'][str(threads)], args.remote_root + '/benchmark_model',
                    '--graph=' + args.remote_root + '/' + name + '/model.tflite',
                    '--use_cpu=true', '--use_gpu=false', '--use_npu=false', '--num_threads=' + str(threads),
                    '--warmup_runs=' + str(1 if diagnostic else args.warmup), '--warmup_min_secs=0',
                    '--num_runs=' + str(1 if diagnostic else args.runs), '--min_secs=0', '--max_secs=600',
                    '--run_delay=0', '--report_peak_memory_footprint=false', '--use_profiler=false',
                    '--input_layer_value_range=' + args.input_name + ',-0.5,0.5',
                    '--result_file_path=' + remote + '/result.pb']
            if diagnostic:
                argv.append('--model_runtime_info_output_file=' + remote + '/runtime.pb')
            local = execute(device, name, threads, 'litert_xnnpack', label, argv, True)
            result = result_proto.FromString((local / 'result.pb').read_bytes())
            expected_runs, expected_warmup = (1, 1) if diagnostic else (args.runs, args.warmup)
            if result.misc_metrics.num_runs != expected_runs or result.misc_metrics.num_warmup_runs != expected_warmup:
                raise ValueError('Benchmark run-count mismatch: ' + label)
            record = MessageToDict(result, preserving_proto_field_name=True)
            save(local / 'measurements.json', record)
            if diagnostic:
                runtime = runtime_proto.FromString((local / 'runtime.pb').read_bytes())
                coverage = []
                for subgraph in runtime.subgraphs:
                    nodes = {n.id: n for n in subgraph.nodes}
                    for index in subgraph.execution_plan:
                        node = nodes[index]
                        if node.HasField('delegate_node_details'):
                            info = node.delegate_node_details
                            coverage.append(dict(delegate=info.delegate_name,
                                                 replaced_nodes=list(info.tflite_node_ids_replaced)))
                        else:
                            coverage.append(dict(builtin_node=index))
                if not any('delegate' in r for r in coverage):
                    raise ValueError('No delegated node in native benchmark: ' + label)
                if any(r.get('delegate', 'TfLiteXNNPackDelegate') != 'TfLiteXNNPackDelegate'
                       for r in coverage):
                    raise ValueError('Unexpected baseline delegate: ' + label)
                delegation.append(dict(device=device['label'], model=name, coverage=coverage))
                save(args.output / 'delegation.json', delegation)
            else:
                observations.append(dict(device=device['label'], model=name, threads=threads,
                    engine='litert_xnnpack', repetition=repetition, measurements=record))
                save(args.output / 'observations.json', observations)

        # Validate all fixed fixtures before collecting any performance rows.
        for name in models:
            for threads in (1, 4):
                for device in devices:
                    run_ynn(device, name, threads)
            for i in range(len(models[name][1]['samples'])):
                for device in devices:
                    label = f"{device['label']}_{name}_t1_litert_xnnpack_validate_{i}"
                    argv = ['taskset', device['masks']['1'], args.remote_root + '/run_model',
                            '--graph=' + args.remote_root + '/' + name + '/model.tflite',
                            '--accelerator=cpu', '--cpu_kernel_mode=delegate', '--enable_ynnpack=false',
                            '--input_dir=' + args.remote_root + '/' + name + f'/case_{i}',
                            '--output_dir=' + args.remote_root + '/' + label,
                            '--iterations=1', '--report_peak_memory_footprint=false']
                    local = execute(device, name, 1, 'litert_xnnpack', label, argv, True)
                    validate(device, name, 1, 'litert_xnnpack', i, local / (args.output_name + '.raw'))
            for device in devices:
                run_litert(device, name, 1)
        for name in models:
            for threads in (1, 4):
                for repetition in range(args.repeats):
                    order = (run_ynn, run_litert) if repetition % 2 == 0 else (run_litert, run_ynn)
                    for run in order:
                        for device in devices:
                            run(device, name, threads, repetition)
        save(args.output / 'summary.json', summarize(observations, devices, models))
    finally:
        restored = {}
        for device in devices:
            label = device['label']
            if label not in power:
                continue
            original = power[label]
            command = (['settings', 'delete', 'global', 'stay_on_while_plugged_in']
                       if original['stay_on'] == 'null' else
                       ['settings', 'put', 'global', 'stay_on_while_plugged_in', original['stay_on']])
            result = shell(device, shlex.join(command))
            if not original['was_awake']:
                shell(device, 'input keyevent KEYCODE_SLEEP')
            restored[label] = dict(returncode=result.returncode,
                stay_on=shell(device, 'settings get global stay_on_while_plugged_in').stdout.strip())
        save(args.output / 'power-restored.json', restored)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    for name in ('devices-json', 'ynn-binary', 'benchmark-binary', 'validation-binary',
                 'benchmark-input', 'tflite-root', 'litert-root', 'protoc', 'output'):
        parser.add_argument('--' + name, type=Path, required=True)
    parser.add_argument('--remote-root', required=True)
    parser.add_argument('--reuse-deployment', action='store_true')
    parser.add_argument('--input-name', default='x')
    parser.add_argument('--output-name', default='linear')
    parser.add_argument('--models', nargs='+', choices=MODELS, default=MODELS)
    parser.add_argument('--warmup', type=int, default=3)
    parser.add_argument('--runs', type=int, default=10)
    parser.add_argument('--repeats', type=int, default=2)
    parser.add_argument('--cooldown', type=float, default=10)
    parser.add_argument('--timeout', type=int, default=600)
    args = parser.parse_args()
    if min(args.warmup, args.runs, args.repeats, args.timeout) < 1 or args.cooldown < 0:
        parser.error('Positive run counts and timeout, nonnegative cooldown required')
    if not args.remote_root.startswith('/data/local/tmp/') or '..' in Path(args.remote_root).parts:
        parser.error('Use a directory under /data/local/tmp/')
    compare(args)


if __name__ == '__main__':
    main()
