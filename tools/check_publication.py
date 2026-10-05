#!/usr/bin/env python3
# Copyright 2026 @snnn
# SPDX-License-Identifier: Apache-2.0

"""Check the public file set without reading ignored local captures or Git identities."""

import argparse
import json
from pathlib import Path
import re
import subprocess

try:
    from email_validator import EmailNotValidError, validate_email
except ModuleNotFoundError:
    raise SystemExit(
        "Publication checks require the project dependencies. Run with "
        "'uv run --locked python tools/check_publication.py'."
    )


HOST_PATH = re.compile(
    r"/(?:home|Users|root|data/(?:home|bt)|mnt|media|workspace)/[^\s\"'<>`]+"
    r"|\b[A-Za-z]:[\\/](?:Users|Documents and Settings)[\\/]"
    r"|file:" r"//"
)
# Extract candidates from prose/code; email-validator owns syntax validation.
# Keep quoted local parts and bracketed IP domains together. The broad tokens
# include extra @ signs so malformed addresses are not accepted as substrings.
EMAIL_CANDIDATE = re.compile(
    r"""(?:"(?:[^"\\\r\n]|\\.)*"|[^\s<>()\[\]",:;]+)@"""
    r"""(?:\[[^\]\r\n]+\]|[^\s<>()\[\]"'\x60,:;/\\|!?*]+)"""
)
PRIVATE_IMPORT = re.compile(r"^\s*(?:from|import)\s+(?:litert_core_ir|core)(?:\.|\s|$)")
ADB_SERIAL = re.compile(r"\badb\s+-s\s+([^\s]+)")
IDENTITY_KEYS = {
    "serial", "device_serial", "android_serial", "hostname", "host_name",
    "username", "user_name", "ip_address", "mac_address", "imei", "imsi",
    "android_id",
}
SECRET_KEYS = {"password", "api_key", "access_token", "hf_token"}


def placeholder(value):
    return not value or value.startswith(("$", "<", "{"))


def contains_email(text):
    """Detect address syntax without DNS, delivery checks, or value disclosure."""
    if "@" not in text:
        return False
    for match in EMAIL_CANDIDATE.finditer(text):
        # A sentence's final period belongs to the prose, not the address.
        candidate = match.group().removesuffix(".")
        # Underscores can delimit Markdown emphasis as well as local parts.
        for marker in ("__", "_"):
            if candidate.startswith(marker) and candidate.endswith(marker):
                candidate = candidate[len(marker):-len(marker)]
                break
        try:
            validate_email(
                candidate,
                check_deliverability=False,
                allow_quoted_local=True,
                allow_domain_literal=True,
                allow_smtputf8=True,
                test_environment=True,
            )
        except EmailNotValidError:
            continue
        return True
    return False


def issues(name, data):
    """Return locations/categories, never the potentially private matched value."""
    path = Path(name)
    parts = path.parts
    problems = []
    if (
        parts[0] in {"assets", "out", ".deps", ".venv", "private", "authoring"}
        or parts[0].startswith("build")
        or path.name == "AGENTS.md"
        or "authoring" in parts
        or path.name in {".env", ".netrc", ".pypirc", "id_rsa", "id_ed25519"}
        or path.name.startswith(".env.")
        or name.startswith(("patches/core-ir-", "runtime/core_ir_"))
        or path.suffix in {".litertlm", ".safetensors", ".gguf", ".tflite"}
    ):
        problems.append((0, "local/private artifact"))
    if b"\0" in data:
        return problems
    try:
        source = data.decode("utf-8")
    except UnicodeDecodeError:
        return problems
    licensed_text = parts[0] == "third_party" or path.name in {"LICENSE", "NOTICE"}
    for number, line in enumerate(source.splitlines(), 1):
        if ("/" in line or "\\" in line) and HOST_PATH.search(line):
            problems.append((number, "host-specific path"))
        if not licensed_text and "copyright" not in line.lower() and contains_email(line):
            problems.append((number, "personal email in file content"))
        if path.suffix == ".py" and PRIVATE_IMPORT.search(line):
            problems.append((number, "private compiler import"))
        match = ADB_SERIAL.search(line)
        if match and not placeholder(match[1].strip("\"'\\")):
            problems.append((number, "literal ADB device identity"))
    if path.suffix == ".json":
        try:
            document = json.loads(source)
        except ValueError:
            return problems

        email_in_lines = any(
            category == "personal email in file content" for _, category in problems
        )

        def visit(value, location):
            if isinstance(value, dict):
                for key, child in value.items():
                    field = key.lower()
                    if isinstance(child, str) and not placeholder(child):
                        if field in IDENTITY_KEYS:
                            problems.append((0, f"device/user identity at {location}.{key}"))
                        if field in SECRET_KEYS:
                            problems.append((0, f"credential at {location}.{key}"))
                    if key.startswith("patches/core-ir-"):
                        problems.append((0, "private compiler provenance"))
                    visit(key, location)
                    visit(child, f"{location}.{key}")
            elif isinstance(value, list):
                for index, child in enumerate(value):
                    visit(child, f"{location}[{index}]")
            elif (
                isinstance(value, str) and not email_in_lines and not licensed_text
                and "copyright" not in value.lower() and contains_email(value)
            ):
                # JSON escaping can hide Unicode or quoted addresses from the
                # line scan. Do not print the value or a key containing it.
                problems.append((0, "personal email in JSON content"))

        visit(document, "record")
    return problems


def candidates(root, staged=False, revision=None):
    if revision:
        command = ["git", "ls-tree", "-r", "--name-only", "-z", revision]
    else:
        command = ["git", "ls-files", "--cached", "-z"]
        if not staged:
            command += ["--others", "--exclude-standard"]
    names = subprocess.check_output(command, cwd=root).decode().split("\0")
    for name in sorted(set(names) - {""}):
        if staged or revision:
            ref = f"{revision or ''}:{name}"
            data = subprocess.check_output(["git", "show", ref], cwd=root)
        else:
            path = root / name
            if not path.is_file():
                continue
            data = path.read_bytes()
        yield name, data


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    scope = parser.add_mutually_exclusive_group()
    scope.add_argument("--staged", action="store_true", help="check the complete Git index")
    scope.add_argument("--revision", help="check file contents at a specific Git revision")
    args = parser.parse_args()
    root = Path(__file__).resolve().parents[1]
    checked = failures = 0
    for name, data in candidates(root, args.staged, args.revision):
        checked += 1
        for number, category in issues(name, data):
            failures += 1
            print(f"{name}:{number}: {category}")
    print(f"Publication check: {checked} files, {failures} findings.")
    return bool(failures)


if __name__ == "__main__":
    raise SystemExit(main())
