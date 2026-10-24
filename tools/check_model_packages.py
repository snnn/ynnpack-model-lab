# Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
"""Validate every published semantic program/interface without model weights."""
import argparse
from pathlib import Path
import subprocess


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--runner', type=Path, required=True)
    parser.add_argument('--models', type=Path, default=Path(__file__).resolve().parents[1] / 'models')
    args = parser.parse_args()
    packages = sorted(args.models.glob('*/**/model.json'))
    if not packages:
        raise ValueError('No model packages found')
    for metadata in packages:
        subprocess.run([str(args.runner.resolve()), '--check_package=' + str(metadata.parent.resolve())],
                       check=True, stdout=subprocess.DEVNULL)
        print(metadata.parent.relative_to(args.models), 'passed', flush=True)
    print(f'{len(packages)} semantic packages validated without model weights')


if __name__ == '__main__':
    main()
