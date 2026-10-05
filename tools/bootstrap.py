# Copyright 2026 @snnn.
# SPDX-License-Identifier: Apache-2.0
"""Fetch hash-pinned backend/tokenizer sources and apply reproducible patches."""

import argparse
import hashlib
import json
import os
from pathlib import Path
import shutil
import subprocess
import tempfile
import time
import urllib.request
import zipfile

ROOT = Path(__file__).resolve().parents[1]


def digest(path):
    with path.open("rb") as f:
        return hashlib.file_digest(f, "sha256").hexdigest()


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--directory", type=Path, default=ROOT / ".deps")
    parser.add_argument("--hf-bf16", action="store_true",
                        help="Apply BF16 precision fixes; use a separate dependency directory")
    parser.add_argument("--no-tokenizers", action="store_true",
                        help="Skip tokenizer sources/crates for LAB_ENABLE_TOKENIZERS=OFF")
    args = parser.parse_args()
    args.directory.mkdir(parents=True, exist_ok=True)
    for dep in json.loads((ROOT / "dependencies.json").read_text()):
        if args.no_tokenizers and dep.get("feature") == "tokenizers":
            continue
        dest = args.directory / dep["name"]
        archive = args.directory / (dep["name"] + ".zip")
        stamp = args.directory / (dep["name"] + ".revision")
        if dest.exists() and stamp.exists():
            if stamp.read_text().strip() != dep["revision"]:
                raise RuntimeError(
                    f"Different revision in {dest}; choose a fresh directory"
                )
        else:
            if dest.exists():
                raise RuntimeError(
                    f"Unmanaged directory: {dest}; choose a fresh directory"
                )
            if not archive.exists():
                for attempt in range(3):
                    try:
                        with urllib.request.urlopen(dep["url"], timeout=60) as src:
                            with archive.with_suffix(".part").open("wb") as out:
                                shutil.copyfileobj(src, out)
                        archive.with_suffix(".part").replace(archive)
                        break
                    except OSError:
                        if attempt == 2:
                            raise
                        time.sleep(2)
            if digest(archive) != dep["sha256"]:
                raise RuntimeError(f"Archive checksum mismatch: {archive}")
            with tempfile.TemporaryDirectory(dir=args.directory) as temporary:
                with zipfile.ZipFile(archive) as z:
                    for info in z.infolist():
                        path = Path(info.filename)
                        if path.is_absolute() or ".." in path.parts:
                            raise RuntimeError("Unsafe archive path")
                    z.extractall(temporary)
                entries = list(Path(temporary).iterdir())
                if len(entries) != 1 or not entries[0].is_dir():
                    raise RuntimeError("Unexpected archive layout")
                entries[0].rename(dest)
            stamp.write_text(dep["revision"] + "\n")
        print(f"{dep['name']}: {dep['revision']}", flush=True)
    source = args.directory / "XNNPACK"
    # Extracted sources are not Git checkouts. Prevent git apply from finding
    # this lab's parent repository and silently skipping dependency paths.
    env = {**os.environ, "GIT_CEILING_DIRECTORIES": str(args.directory.resolve())}
    patches = sorted((ROOT / "patches").glob("ynnpack-*.patch"))
    if args.hf_bf16:
        patches.append(ROOT / "patches" / "hf-ynnpack-bf16-rounding.patch")
    for patch in patches:
        check = subprocess.run(
            ["git", "apply", "--check", str(patch)],
            cwd=source,
            capture_output=True,
            env=env,
        )
        if check.returncode == 0:
            subprocess.run(
                ["git", "apply", str(patch)], cwd=source, check=True, env=env
            )
        else:
            subprocess.run(
                ["git", "apply", "--reverse", "--check", str(patch)],
                cwd=source,
                check=True,
                env=env,
            )
        print(f"Applied: {patch.name}", flush=True)
    if not args.no_tokenizers:
        source = args.directory / "tokenizers-cpp"
        extra_patches = [
            (source, patch)
            for patch in sorted((ROOT / "patches").glob("tokenizers-*.patch"))
        ]
        extra_patches.append((
            args.directory / "sentencepiece",
            ROOT / "patches/sentencepiece-offline-abseil.patch",
        ))
        for source, patch in extra_patches:
            check = subprocess.run(
                ["git", "apply", "--check", str(patch)],
                cwd=source, capture_output=True, env=env,
            )
            if check.returncode == 0:
                subprocess.run(
                    ["git", "apply", str(patch)], cwd=source, check=True, env=env
                )
            else:
                subprocess.run(
                    ["git", "apply", "--reverse", "--check", str(patch)],
                    cwd=source, check=True, env=env,
                )
            print(f"Applied: {patch.name}", flush=True)
        lock = ROOT / "patches/tokenizers.Cargo.lock"
        source = args.directory / "tokenizers-cpp"
        target = source / "rust/Cargo.lock"
        if target.exists() and target.read_bytes() != lock.read_bytes():
            raise RuntimeError(
                "Tokenizer Cargo.lock differs; choose a fresh dependency directory"
            )
        shutil.copyfile(lock, target)
        if not shutil.which("cargo"):
            raise RuntimeError(
                "Rust/Cargo is required; see README.md or use --no-tokenizers"
            )
        env = {**os.environ, "CARGO_HOME": str(args.directory.resolve() / "cargo")}
        subprocess.run(
            ["cargo", "fetch", "--locked", "--manifest-path",
             str((source / "rust/Cargo.toml").resolve())],
            check=True, env=env,
        )



if __name__ == "__main__":
    main()
