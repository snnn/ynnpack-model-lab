# Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
"""Validate and publish semantic DSL packages using the public Rust formatter.

Formatting and publication perform no target lowering. JSON is only a transient
frontend bridge and small package metadata, never the deployed graph source.
"""
import hashlib
import json
import os
from pathlib import Path
import shutil
import subprocess
import tempfile

METADATA_FILES = {'model.json', 'asset_recipe.json', 'execution.json'}
PRIVATE_MARKERS = ('litert_core_ir', 'core_ir', 'CORE_IR', 'Core IR', 'litert_opt::')


def _tool(variable, name):
    tool = os.environ.get(variable) or shutil.which(name)
    if not tool:
        raise ValueError(f'Set {variable} to the public {name} executable')
    return str(Path(tool).resolve())


def plan_tool():
    return _tool('YNNPACK_PLAN_TOOL', 'ynn-plan')


def program_tool():
    return _tool('YNNPACK_PROGRAM_TOOL', 'ynn-program')


def digest(path):
    with Path(path).open('rb') as stream:
        return hashlib.file_digest(stream, 'sha256').hexdigest()


def inspect(path):
    return json.loads(subprocess.check_output([plan_tool(), 'inspect', str(path)], text=True))


def inspect_program(path):
    try:
        return json.loads(subprocess.check_output(
            [program_tool(), 'inspect', str(path)], text=True, stderr=subprocess.PIPE))
    except subprocess.CalledProcessError as error:
        raise ValueError(error.stderr.strip()) from error


def write_program(program, path):
    """Format a frontend projection with the single Rust DSL writer."""
    path = Path(path)
    path.parent.mkdir(parents=True, exist_ok=True)
    if path.exists():
        raise FileExistsError(path)
    with tempfile.TemporaryDirectory(prefix='.ynn-source-') as temporary:
        bridge = Path(temporary) / 'projection.json'
        bridge.write_text(json.dumps(program, allow_nan=False) + '\n')
        subprocess.run([program_tool(), 'from-json', str(bridge), str(path)], check=True,
                       stdout=subprocess.DEVNULL)


def seal(raw, metadata=None):
    """Bind DSL and execution identities; numeric chunks are sealed by the DSL."""
    root = Path(raw)
    inspect_program(root / 'program.ynn')
    if metadata is None:
        metadata = json.loads((root / 'model.json').read_text()) if (root / 'model.json').exists() else {}
    metadata['package'] = dict(format='ynn-semantic-package', version=2)
    for name in ('program.ynn', 'execution.json'):
        path = root / name
        metadata['package'][name] = dict(file=name, bytes=path.stat().st_size, sha256=digest(path))
    (root / 'model.json').write_text(json.dumps(metadata, allow_nan=False, indent=2) + '\n')
    return metadata


def _assets(value):
    if isinstance(value, dict):
        if set(value) >= {'path', 'bytes', 'sha256'}:
            yield value
        for child in value.values():
            yield from _assets(child)
    elif isinstance(value, list):
        for child in value:
            yield from _assets(child)


def _text(path, limit=16 << 20):
    with path.open('rb') as stream:
        data = stream.read(limit + 1)
    if len(data) > limit:
        raise ValueError('Oversized semantic artifact')
    return data.decode()


def semantic_files(root):
    """Verified deployment inputs, including every referenced numeric chunk."""
    root = Path(root)
    meta = json.loads(_text(root / 'model.json'))
    identity = meta.get('package', {})
    if identity.get('format') != 'ynn-semantic-package' or identity.get('version') != 2:
        raise ValueError('Regenerate this model as a version-2 semantic DSL package')
    files = {'model.json': root / 'model.json'}
    for name, limit in [('program.ynn', 32 << 20), ('execution.json', 16 << 20)]:
        item = identity[name]
        if item.get('file', name) != name:
            raise ValueError('Invalid semantic artifact filename')
        path = root / name
        if path.stat().st_size > limit or path.stat().st_size != item['bytes'] or digest(path) != item['sha256']:
            raise ValueError('Semantic artifact identity mismatch: ' + name)
        files[name] = path
    for item in inspect_program(root / 'program.ynn')['numeric_files']:
        files[item['path']] = root / item['path']
    return files


def read_program(root):
    """Diagnostic typed projection, parsed by Rust; not a deployment encoding."""
    files = semantic_files(root)
    return json.loads(subprocess.check_output([program_tool(), 'to-json', str(files['program.ynn'])], text=True))


def publish(raw, output):
    """Publish a semantic package atomically, without invoking target lowering."""
    raw, output = Path(raw), Path(output)
    if output.exists():
        raise FileExistsError(output)
    files = semantic_files(raw)
    values = {}
    for name in METADATA_FILES:
        source = raw / name
        if source.exists():
            content = _text(source)
            if any(marker in content for marker in PRIVATE_MARKERS):
                raise ValueError('Private implementation reference in ' + name)
            values[name] = json.loads(content)
            files[name] = source
    content = _text(files['program.ynn'], 32 << 20)
    if any(marker in content for marker in PRIVATE_MARKERS):
        raise ValueError('Private implementation reference in program.ynn')
    info = inspect_program(files['program.ynn'])
    execution = values['execution.json']
    if set(info['phases']) != set(execution.get('graphs', {})):
        raise ValueError('Execution phases differ from program')
    if any('file' in g or 'sha256' in g for g in execution['graphs'].values()):
        raise ValueError('Execution metadata must not reference compiled plans')
    for subdir in ('parameters', 'tokenizer'):
        directory = raw / subdir
        if not directory.exists():
            continue
        if directory.is_symlink():
            raise ValueError('Unexpected package directory: ' + subdir)
        for source in directory.iterdir():
            if subdir == 'parameters' and source.name != digest(source) + '.bin':
                raise ValueError('Parameter identity mismatch: ' + source.name)
            files[subdir + '/' + source.name] = source
    for name, source in files.items():
        if not source.is_file() or source.is_symlink() or source.parent.is_symlink():
            raise ValueError('Unexpected package entry: ' + name)
    hashes = {name: digest(path) for name, path in files.items()}
    for asset in _assets([info['source_assets'], execution]):
        if asset['path'].startswith('@parameters/'):
            name = 'parameters/' + asset['path'].removeprefix('@parameters/')
            if name not in files or files[name].stat().st_size != asset['bytes'] or hashes[name] != asset['sha256']:
                raise ValueError('Missing or inconsistent required parameter: ' + name)
    output.parent.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(prefix='.ynn-publish-', dir=output.parent) as temporary:
        stage = Path(temporary) / 'package'
        stage.mkdir()
        for name, source in files.items():
            destination = stage / name
            destination.parent.mkdir(parents=True, exist_ok=True)
            shutil.copyfile(source, destination)
            if digest(destination) != hashes[name]:
                raise ValueError('Artifact changed during publication: ' + name)
        stage.rename(output)
    return {str(output / name): value for name, value in hashes.items()}
