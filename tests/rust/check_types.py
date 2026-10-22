# Copyright 2026 @snnn.
# SPDX-License-Identifier: Apache-2.0
"""Require specific type errors, without invoking the native linker."""
import argparse
import json
from pathlib import Path
import subprocess
import tempfile


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--rustc', required=True)
    parser.add_argument('--library', type=Path, required=True)
    args = parser.parse_args()
    prelude = 'use ynnpack_lab::vision::{VisionBuilder, VisionSession};\n'
    examples = [
        ('prepared_program_not_send', 'E0277', '''
fn require_send<T: Send>() {}
fn example() { require_send::<ynnpack_lab::runtime::PreparedProgram>(); }'''),
        ('asset_store_not_sync', 'E0277', '''
fn require_sync<T: Sync>() {}
fn example() { require_sync::<ynnpack_lab::runtime::AssetStore>(); }'''),
        ('consumed_builder', 'E0382', '''
fn example(builder: VisionBuilder) {
    let first = builder.prepare(1);
    let second = builder.prepare(1);
}'''),
        ('unprepared_graph', 'E0599', '''
fn example(mut builder: VisionBuilder) { builder.run(); }'''),
        ('borrowed_output', 'E0499', '''
fn example(s: &mut VisionSession) {
    let output = s.run().unwrap();
    s.run().unwrap();
    println!("{}", output[0]);
}'''),
        ('input_with_live_output', 'E0502', '''
fn example(s: &mut VisionSession) {
    let output = s.output();
    s.input_mut()[0] = 1.0;
    println!("{}", output[0]);
}'''),
        ('no_shared_session', 'E0277', '''
fn require_send<T: Send>() {}
fn example() { require_send::<VisionSession>(); }'''),
        ('valid_borrows', None, '''
fn example(builder: VisionBuilder) {
    let mut s = builder.prepare(1).unwrap();
    s.input_mut()[0] = 2.0;
    let first = s.run().unwrap()[0];
    let second = s.run().unwrap()[0];
    println!("{} {}", first, second);
}'''),
    ]
    with tempfile.TemporaryDirectory() as tmp:
        for name, expected, body in examples:
            source = Path(tmp) / f'{name}.rs'
            source.write_text(prelude + body)
            command = [args.rustc, '--edition=2021', '--crate-type=lib', '--emit=metadata',
                       '--error-format=json', '--extern', f'ynnpack_lab={args.library}',
                       '-L', f'dependency={args.library.parent / "deps"}',
                       '--out-dir', tmp, str(source)]
            result = subprocess.run(command, text=True, capture_output=True)
            errors = [json.loads(line) for line in result.stderr.splitlines()]
            codes = {e['code']['code'] for e in errors if e.get('code') and e.get('level') == 'error'}
            if expected:
                if result.returncode == 0 or expected not in codes:
                    raise AssertionError(f'{name}: expected {expected}, got {result.stderr}')
            elif result.returncode:
                raise AssertionError(f'{name}: {result.stderr}')
            print(f'{name}: {expected or "compiles"}')


if __name__ == '__main__':
    main()
