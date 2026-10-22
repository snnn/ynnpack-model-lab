#!/usr/bin/env python3
# Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
"""Compare complete compiler packages against a frozen compiler binary."""
import argparse
import hashlib
import json
from pathlib import Path
import subprocess


def digest(path):
    with path.open('rb') as stream:
        return hashlib.file_digest(stream, 'sha256').hexdigest()


def files(root):
    return {str(p.relative_to(root)): digest(p)
            for p in sorted(root.rglob('*')) if p.is_file()}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--baseline', type=Path, required=True)
    parser.add_argument('--candidate', type=Path, required=True)
    parser.add_argument('--program', type=Path, action='append', default=[])
    parser.add_argument('--fixtures', type=Path)
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    programs = args.program + (sorted(args.fixtures.rglob('*.program.json')) if args.fixtures else [])
    if not programs:
        parser.error('provide --program or --fixtures')
    args.output.mkdir(parents=True, exist_ok=False)
    results = []
    for i, program in enumerate(programs):
        outputs = []
        for label, binary in [('baseline', args.baseline), ('candidate', args.candidate)]:
            out = args.output / str(i) / label
            out.parent.mkdir(parents=True, exist_ok=True)
            run = subprocess.run([str(binary.resolve()), '--request', str(program.resolve()),
                                  '--output', str(out)], text=True, capture_output=True)
            (out.parent / (label + '.log')).write_text(run.stdout + run.stderr)
            if run.returncode:
                raise RuntimeError(f'{label} failed for {program}: {run.stderr}')
            outputs.append(files(out))
        different = sorted(k for k in outputs[0].keys() | outputs[1].keys()
                           if outputs[0].get(k) != outputs[1].get(k))
        results.append(dict(program=str(program), files=len(outputs[0]), different=different))
        (args.output / 'results.json').write_text(json.dumps(results, indent=2) + '\n')
        if different:
            raise AssertionError(f'{program}: different package files: {different}')
    print(f'{len(results)} programs: all package files byte-identical')


if __name__ == '__main__':
    main()
