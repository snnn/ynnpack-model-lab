# Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
"""Validate and publish data-only execution packages.

The runtime is built from this repository. Model publication never copies or
rewrites runtime source, and never publishes compiler diagnostic files.
"""
import gzip
import hashlib
import json
import os
from pathlib import Path
import shutil
import subprocess
import tempfile
import zlib

METADATA_FILES = {"model.json", "asset_recipe.json", "program.json", "program.json.gz", "execution.json"}
PRIVATE_MARKERS = ("litert_core_ir", "core_ir", "CORE_IR", "Core IR", "litert_opt::")


def plan_tool():
    tool = os.environ.get("YNNPACK_PLAN_TOOL") or shutil.which("ynn-plan")
    if not tool:
        raise ValueError("Set YNNPACK_PLAN_TOOL to the public ynn-plan executable")
    return str(Path(tool).resolve())


def digest(path):
    with Path(path).open("rb") as stream:
        return hashlib.file_digest(stream, "sha256").hexdigest()


def inspect(path):
    return json.loads(subprocess.check_output([plan_tool(), "inspect", str(path)], text=True))


def seal(raw, metadata=None, *, compress=False):
    """Bind serialized semantic inputs; this does not perform target lowering."""
    root = Path(raw)
    if metadata is None:
        metadata = json.loads((root / "model.json").read_text()) if (root / "model.json").exists() else {}
    if compress:
        (root / "program.json.gz").write_bytes(gzip.compress((root / "program.json").read_bytes(), mtime=0))
    metadata["package"] = dict(format="ynn-semantic-package", version=1)
    for name in ("program.json", "execution.json"):
        file = "program.json.gz" if name == "program.json" and compress else name
        path = root / file
        metadata["package"][name] = dict(file=file, bytes=path.stat().st_size, sha256=digest(path))
    (root / "model.json").write_text(json.dumps(metadata, allow_nan=False, indent=2) + "\n")
    return metadata


def _assets(value):
    if isinstance(value, dict):
        if set(value) >= {"path", "bytes", "sha256"}:
            yield value
        for child in value.values():
            yield from _assets(child)
    elif isinstance(value, list):
        for child in value:
            yield from _assets(child)


def _json_content(path):
    limit = (128 if path.name.startswith('program.json') else 16) << 20
    with path.open('rb') as stream:
        data = stream.read(limit + 1)
    if len(data) > limit:
        raise ValueError('Oversized semantic artifact')
    if path.suffix == '.gz':
        decoder = zlib.decompressobj(16 + zlib.MAX_WBITS)
        try:
            data = decoder.decompress(data, limit + 1)
        except zlib.error as error:
            raise ValueError('Invalid compressed semantic artifact') from error
        if len(data) > limit or not decoder.eof or decoder.unused_data or decoder.unconsumed_tail:
            raise ValueError('Oversized, truncated or trailing compressed semantic data')
    return data.decode()


def publish(raw, output):
    """Publish a semantic package atomically, without invoking a compiler."""
    raw, output = Path(raw), Path(output)
    if output.exists():
        raise FileExistsError(output)
    files, values = {}, {}
    for name in METADATA_FILES:
        source = raw / name
        if not source.exists():
            continue
        if source.is_symlink() or not source.is_file():
            raise ValueError("Unexpected package entry: " + name)
        content = _json_content(source)
        if any(marker in content for marker in PRIVATE_MARKERS):
            raise ValueError("Private implementation reference in " + name)
        values[name] = json.loads(content)
        files[name] = source
    if not {"execution.json", "model.json"} <= files.keys() or not {"program.json", "program.json.gz"} & files.keys():
        raise ValueError("Expected a semantic package, not offline plans")
    identity = values["model.json"].get("package", {})
    if identity.get("format") != "ynn-semantic-package" or identity.get("version") != 1:
        raise ValueError("Unsupported semantic package")
    for name in ("program.json", "execution.json"):
        file = identity.get(name, {}).get("file", name)
        if file not in (name, "program.json.gz" if name == "program.json" else name) or file not in files:
            raise ValueError("Invalid semantic artifact filename")
        expected = dict(bytes=files[file].stat().st_size, sha256=digest(files[file]))
        if "file" in identity[name]: expected["file"] = file
        if identity[name] != expected:
            raise ValueError("Semantic artifact identity mismatch: " + name)
    program_file = identity["program.json"].get("file", "program.json")
    program, execution = values[program_file], values["execution.json"]
    for other in ("program.json", "program.json.gz"):
        if other != program_file: files.pop(other, None)
    if program.get("version") != 1 or not program.get("phases") or set(program["phases"]) != set(execution.get("graphs", {})):
        raise ValueError("Execution phases differ from program")
    if any("file" in g or "sha256" in g for g in execution["graphs"].values()):
        raise ValueError("Execution metadata must not reference compiled plans")
    for subdir in ("parameters", "tokenizer"):
        directory = raw / subdir
        if not directory.exists():
            continue
        for source in directory.iterdir():
            if not source.is_file() or source.is_symlink():
                raise ValueError("Unexpected package entry: " + str(source))
            if subdir == "parameters" and source.name != digest(source) + ".bin":
                raise ValueError("Parameter identity mismatch: " + source.name)
            files[subdir + "/" + source.name] = source
    hashes = {name: digest(path) for name, path in files.items()}
    for asset in _assets([program, execution]):
        if asset["path"].startswith("@parameters/"):
            name = "parameters/" + asset["path"].removeprefix("@parameters/")
            if name not in files or files[name].stat().st_size != asset["bytes"] or hashes[name] != asset["sha256"]:
                raise ValueError("Missing or inconsistent required parameter: " + name)
    output.parent.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(prefix=".ynn-publish-", dir=output.parent) as temporary:
        stage = Path(temporary) / "package"
        stage.mkdir()
        for name, source in files.items():
            destination = stage / name
            destination.parent.mkdir(parents=True, exist_ok=True)
            shutil.copyfile(source, destination)
            if digest(destination) != hashes[name]:
                raise ValueError("Artifact changed during publication: " + name)
        stage.rename(output)
    return {str(output / name): value for name, value in hashes.items()}


def semantic_files(root):
    """Verified package inputs for deployment and inspection tools."""
    root = Path(root)
    meta = json.loads((root / 'model.json').read_text())
    identity = meta.get('package', {})
    if identity.get('format') != 'ynn-semantic-package' or identity.get('version') != 1:
        raise ValueError('Regenerate this model as a semantic package')
    files = {'model.json': root / 'model.json'}
    for name in ('program.json', 'execution.json'):
        item = identity[name]
        file = item.get('file', name)
        if file not in (name, 'program.json.gz' if name == 'program.json' else name):
            raise ValueError('Invalid semantic artifact filename')
        path = root / file
        if path.stat().st_size != item['bytes'] or digest(path) != item['sha256']:
            raise ValueError('Semantic artifact identity mismatch: ' + name)
        files[file] = path
    return files


def read_program(root):
    files = semantic_files(root)
    path = files.get('program.json', files.get('program.json.gz'))
    return json.loads(_json_content(path))
