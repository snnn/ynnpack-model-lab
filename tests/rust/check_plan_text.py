# Copyright 2026 @snnn.
# SPDX-License-Identifier: Apache-2.0
"""Check canonical plan semantics, then run the independent native state oracle."""
import argparse
import hashlib
import json
from pathlib import Path
import shutil
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[2]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--tool', type=Path, required=True)
    parser.add_argument('--state-runner', type=Path, required=True)
    args = parser.parse_args()

    def run(*command, success=True):
        result = subprocess.run([str(x) for x in command], capture_output=True, text=True)
        if (result.returncode == 0) != success:
            raise AssertionError(f'{command}: {result.stdout}\n{result.stderr}')
        return result

    plans = sorted((ROOT / 'models').rglob('*.ynn'))
    plans += sorted((ROOT / 'tests/generated').glob('*.ynn'))
    plans += sorted((ROOT / 'tests/rust').glob('*.ynn'))
    with tempfile.TemporaryDirectory(prefix='ynn-plan-text-') as temporary:
        tmp = Path(temporary)
        rebuilt = {}
        for index, original in enumerate(plans):
            canonical = tmp / f'{index}.ynn'
            run(args.tool, 'format', original, '-o', canonical)
            assert run(args.tool, 'inspect', original).stdout == run(args.tool, 'inspect', canonical).stdout, original
            assert canonical.read_text() == run(args.tool, 'format', canonical).stdout, original
            rebuilt[original] = canonical
        print(f'{len(plans)} plans preserve typed commands, attributes, IDs and dependencies')
        square = rebuilt[ROOT / 'tests/rust/square.ynn']
        previous = square.read_bytes()
        run(args.tool, 'format', square, '-o', square, success=False)
        assert square.read_bytes() == previous
        bad = tmp / 'bad.ynn'
        bad.write_text((ROOT / 'tests/rust/square.ynn').read_text().replace('mul(x, x)', 'mul(typo, x)'))
        absent = tmp / 'rejected.ynn'
        error = run(args.tool, 'format', bad, '-o', absent, success=False)
        assert 'Unknown tensor typo' in error.stderr and not absent.exists()
        report = tmp / 'inspection.json'
        run(args.tool, 'inspect', square, '-o', report)
        run(args.tool, 'check', report, success=False)
        for subdir in ['rust', 'generated']:
            (tmp / subdir).mkdir()
            for original, artifact in rebuilt.items():
                if original.parent == ROOT / 'tests' / subdir:
                    shutil.copyfile(artifact, tmp / subdir / original.name)
        shutil.copytree(ROOT / 'tests/generated/parameters', tmp / 'generated/parameters')
        metadata = json.loads((ROOT / 'tests/rust/model.json').read_bytes())
        metadata['execution']['graph']['sha256'] = hashlib.sha256((tmp / 'rust/graph.ynn').read_bytes()).hexdigest()
        (tmp / 'rust/model.json').write_text(json.dumps(metadata))
        result = run(args.state_runner, tmp / 'rust')
        assert 'Rust/native ownership and arithmetic checks passed' in result.stdout
        print('Direct text plans pass the square and all nine native state oracles at one/four threads')


if __name__ == '__main__':
    main()
