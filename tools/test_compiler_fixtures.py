# Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
"""Compile public semantic fixtures and check independent numerical references."""
import argparse
import gzip
import json
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'python'))
from ynnpack_assets.fixture_runner import run


def validate(source, destination, compiler, runner, known_failures=False):
    shutil.copytree(source, destination)
    for compressed in destination.rglob('*.bin.gz'):
        compressed.with_suffix('').write_bytes(gzip.decompress(compressed.read_bytes()))
    cases = json.loads((destination / 'cases.json').read_text())
    for case in cases:
        name = case['name']
        fixture = json.loads((destination / (name + '.fixture.json')).read_text())
        with tempfile.TemporaryDirectory(dir=destination) as temporary:
            compiled = Path(temporary) / 'compiled'
            subprocess.run([str(compiler), '--request', str(destination / (name + '.program.json')),
                            '--output', str(compiled)], check=True, stdout=subprocess.DEVNULL)
            for phase, plan in fixture['graphs'].items():
                (compiled / (phase + '.ynn')).replace(destination / plan)
            shutil.copytree(compiled / 'parameters', destination / 'parameters', dirs_exist_ok=True)
    return run(destination, runner, known_failures=known_failures)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--compiler', type=Path, required=True)
    parser.add_argument('--runner', type=Path, required=True)
    parser.add_argument('--output', type=Path)
    parser.add_argument('--fixtures', type=Path, default=ROOT / 'tests/compiler/fixtures')
    parser.add_argument('--known-failures', action='store_true')
    args = parser.parse_args()
    temporary = tempfile.TemporaryDirectory(prefix='ynn-compiler-tests-') if args.output is None else None
    if temporary is not None:
        args.output = Path(temporary.name) / 'validation'
    args.output.mkdir(parents=True, exist_ok=False)
    results = {}
    for source in sorted(args.fixtures.iterdir()):
        if source.is_dir():
            results[source.name] = validate(source, args.output / source.name,
                args.compiler.resolve(), args.runner.resolve(), args.known_failures)
            (args.output / 'results.json').write_text(json.dumps(results, indent=2) + '\n')


if __name__ == '__main__':
    main()
