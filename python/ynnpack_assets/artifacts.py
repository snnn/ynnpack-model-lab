# Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
"""Validate and publish data-only execution packages.

The runtime is built from this repository. Model publication never copies or
rewrites runtime source, and never publishes compiler diagnostic files.
"""
import hashlib
import json
import os
from pathlib import Path
import shutil
import subprocess
import tempfile

METADATA_FILES = {"model.json", "asset_recipe.json"}
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


def publish(raw, output):
    """Publish a new package atomically, after checking every artifact and hash."""
    raw, output = Path(raw), Path(output)
    if output.exists():
        raise FileExistsError(output)
    files = {}
    assets = []
    for source in raw.iterdir():
        if not source.is_file() or not (source.name in METADATA_FILES or source.suffix == ".ynn"):
            continue
        content = source.read_text()
        if any(marker in content for marker in PRIVATE_MARKERS):
            raise ValueError("Private implementation reference in " + source.name)
        if source.suffix == ".ynn":
            plan = inspect(source)
            for command in plan['commands']:
                for argument in command['args']:
                    if argument.get('data'):
                        assets.append(argument['data'])
        else:
            json.loads(content)
        files[source.name] = source
    if not any(Path(name).suffix == ".ynn" for name in files):
        raise ValueError("No executable plans")
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
    for asset in assets:
        if asset['path'].startswith('@parameters/'):
            name='parameters/'+asset['path'].removeprefix('@parameters/')
            if name not in files or files[name].stat().st_size != asset['bytes'] or hashes[name] != asset['sha256']:
                raise ValueError('Missing or inconsistent required parameter: '+name)

    # Check embedded phase hashes before copying. Other model metadata is data
    # owned by its author; the native session validates its execution contract.
    if "model.json" in files:
        model = json.loads(files["model.json"].read_text())
        for section in (model, model.get("runner", {}), model.get("execution", {})):
            phases = section.get("graphs", section.get("phases", {}))
            if not isinstance(phases, dict):
                continue
            for phase in phases.values():
                if phase.get("file") not in hashes or hashes[phase["file"]] != phase.get("sha256"):
                    raise ValueError("Phase hash mismatch")
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
