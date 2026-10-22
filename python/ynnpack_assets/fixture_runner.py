# Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
"""Execute construction fixtures against their independently computed references."""
import argparse
import json
import os
from pathlib import Path
import subprocess
import numpy as np


def run(directory, runner, threads=(1, 4), selected='', known_failures=False):
    directory = Path(directory).resolve()
    cases = json.loads((directory / 'cases.json').read_text())
    failures = json.loads((directory / 'expected_backend_failures.json').read_text()) if (directory / 'expected_backend_failures.json').exists() else {}
    total = 0
    reproduced = []
    for count in threads:
        for case in cases:
            name = case['name']
            if selected and selected not in name:
                continue
            fixture = json.loads((directory / (name + '.fixture.json')).read_text())
            fixture['threads'] = count
            path = directory / (name + f'.t{count}.fixture.json')
            path.write_text(json.dumps(fixture) + '\n')
            result = subprocess.run([str(Path(runner).resolve()), str(path)], text=True, capture_output=True)
            if known_failures and name in failures and result.returncode:
                expected=failures[name]
                if result.returncode != expected['returncode']:
                    raise AssertionError(f"{name}: known failure changed: {result.returncode}; review {expected}")
                reproduced.append(dict(case=name,threads=count,returncode=result.returncode))
                print(f'{name} threads={count}: REPRODUCED known backend failure {result.returncode}',flush=True)
                continue
            if result.returncode:
                raise RuntimeError(f'{name}, threads={count}, returncode={result.returncode}: {result.stderr}')
            records = json.loads(result.stdout)
            (directory / (name + f'.t{count}.records.json')).write_text(json.dumps(records, indent=2) + '\n')
            if len(records) != len(fixture['steps']) or len(records) != len(case['runs']):
                raise AssertionError(f'{name}: missing invocation records')
            if case.get('required_callbacks'):
                profile = [json.loads(line) for line in
                           (directory / 'model.execution_profile.jsonl').read_text().splitlines()]
                calls = {c['id']:c['name'] for c in profile[0]['calls']}
                seen = {calls[e[1]] for step in profile[1:] for e in step.get('events', [])}
                if not set(case['required_callbacks']) <= seen or not all(
                        step.get('complete') and not step.get('dropped_events') for step in profile[1:]):
                    raise AssertionError(f'{name}: public completion did not execute its producers')
            for i, (expected, step, record) in enumerate(zip(case['runs'], fixture['steps'], records)):
                if record.get('expected_error') is not None:
                    for counter in ('append_bytes', 'append_calls', 'view_copy_bytes'):
                        if counter in expected and record.get(counter) != expected[counter]:
                            raise AssertionError(f'{name}/{i}: failed-request {counter} differs')
                    for owner, extent in expected.get('resources', {}).items():
                        poison = int(owner in expected.get('poisoned_resources', []))
                        if record['resources'][owner][0] != extent or record['resources'][owner][2] != poison:
                            raise AssertionError(f'{name}/{i}/{owner}: failed request published state')
                    continue
                for tensor, ref in expected['outputs'].items():
                    want = np.frombuffer((directory / ref['file']).read_bytes(), dtype=ref['dtype']).reshape(ref['shape'])
                    payload = (directory / step['outputs'][tensor]).read_bytes()
                    if len(payload) != want.nbytes:
                        raise AssertionError(f'{name}/{i}/{tensor}: output byte count')
                    if record['shapes'][tensor] != ref.get('storage_shape', ref['shape']):
                        raise AssertionError(f'{name}/{i}/{tensor}: result shape {record["shapes"][tensor]} != {ref["shape"]}')
                    got = np.frombuffer(payload, dtype=ref['dtype']).reshape(ref['shape'])
                    numeric = case.get('compare') == 'numeric' or (name.startswith(('matmul', 'numerical')) and want.dtype == np.dtype('f4'))
                    if numeric:
                        np.testing.assert_allclose(got, want, atol=case.get('atol', 2e-5), rtol=case.get('rtol', 2e-5), equal_nan=True,
                                                   err_msg=f'{name}/{i}/{tensor}')
                        if case.get('negate_zero_profile') == 'positive' and np.any(np.signbit(got[(want == 0) & (got == 0)])):
                            raise AssertionError('Negate zero profile changed; review backend semantics')
                    elif payload != want.tobytes():
                        raise AssertionError(f'{name}/{i}/{tensor}: routing bytes differ')
                for owner, extent in expected.get('resources', {}).items():
                    if record['resources'][owner][0] != extent or record['resources'][owner][2] != 0:
                        raise AssertionError(f'{name}/{i}/{owner}: committed extent or poison differs')
                for counter in ('append_bytes', 'append_calls', 'view_copy_bytes'):
                    if counter in expected and record[counter] != expected[counter]:
                        raise AssertionError(f'{name}/{i}: {counter} differs')
                total += 1
            if case.get('weight_only'):
                calls, native_dot_calls, scratch = records[-1]['weight_only_statistics']
                if calls != 4 or native_dot_calls == 0 or scratch != 38912:
                    raise AssertionError(f'{name}: weight-only execution/scratch contract changed')
            print(f'{name} threads={count}: {len(records)} invocations', flush=True)
    print(f'{total} requests passed; {len(reproduced)} known backend failures reproduced; independent references, shapes, canaries and prepared-graph reuse')
    report=dict(passed_requests=total,known_failures=reproduced)
    (directory/'validation.json').write_text(json.dumps(report,indent=2)+'\n')
    return report


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('directory', type=Path)
    parser.add_argument('--runner', default=os.environ.get('YNNPACK_PLAN_RUNNER'), required=not os.environ.get('YNNPACK_PLAN_RUNNER'))
    parser.add_argument('--threads', nargs='+', type=int, default=[1, 4])
    parser.add_argument('--filter', default='')
    parser.add_argument('--known-failures',action='store_true',help='Run and require the explicitly recorded baseline failures, reporting them separately')
    args = parser.parse_args()
    run(args.directory, args.runner, args.threads, args.filter, args.known_failures)


if __name__ == '__main__':
    main()
