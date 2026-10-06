#!/usr/bin/env python3
# Copyright 2026 @snnn.
# SPDX-License-Identifier: Apache-2.0
"""Relink a preserved Gemma4 Tensor API runner with diagnostic profiling.

Consumes a native-build archive containing build.json, driver.cc, and its
recorded compiler/linker inputs. Does not rebuild XNNPACK or modify LiteRT.
Outputs and local build provenance belong in an ignored experiment directory.
"""

import argparse
import hashlib
import json
from pathlib import Path
import subprocess


def sha(path):
    with Path(path).open("rb") as stream:
        return hashlib.file_digest(stream, "sha256").hexdigest()


def replace_once(source, old, new):
    if source.count(old) != 1:
        raise ValueError(f"Archived driver does not match expected interface: {old}")
    return source.replace(old, new, 1)


def instrument(source):
    source = replace_once(
        source, '#include "tensor/examples/gemma4/native/memory_snapshot.h"',
        '#include "tensor/examples/gemma4/native/memory_snapshot.h"\n'
        '#include "native_xnnpack_profile.h"\n'
        'ABSL_FLAG(bool, profile_post_ops, false, "Diagnostic decode operator timings.");',
    )
    enable = "absl::GetFlag(FLAGS_profile_post_ops)"
    source = replace_once(source, "  bool reuse=absl::GetFlag(FLAGS_reuse_runtimes);",
        "  bool reuse=absl::GetFlag(FLAGS_reuse_runtimes);\n"
        f'  if ({enable} && !reuse) return absl::InvalidArgumentError("Profiling requires reused runtimes");')
    source = replace_once(
        source, "StageRunner::Create({output},pool,cache,0,workspace)",
        f"StageRunner::Create({{output}},pool,cache,rows==1 && {enable} ? XNN_FLAG_BASIC_PROFILING : 0,workspace)",
    )
    for output, condition in (("cut.output", "decode"),
                               ("sig->outputs.logits", "decode"),
                               ("sig->cuts.initial_hidden", "decode")):
        old = f"StageRunner::Create({{{output}}},pool,cache,0,workspace)"
        if old in source:
            source = replace_once(source, old,
                f"StageRunner::Create({{{output}}},pool,cache,{condition} && {enable} ? XNN_FLAG_BASIC_PROFILING : 0,workspace)")
    # Projection has multiple outputs; preserve that list exactly.
    for stage in ("preprocess", "projection"):
        needle = f"sig->{stage},StageRunner::Create(roots,pool,cache,0,workspace)" if stage == "preprocess" else "stage.projection,StageRunner::Create(roots,pool,cache,0,workspace)"
        source = replace_once(source, needle, needle.replace(
            "cache,0,workspace", f"cache,decode && {enable} ? XNN_FLAG_BASIC_PROFILING : 0,workspace"))
    for expression, stage, profile, index in (
        ("stage.projection->PrepareRuntime()", "*stage.projection", "projection", "i"),
        ("stage.post->PrepareRuntime()", "*stage.post", "post", "i"),
        ("sig->tail->PrepareRuntime()", "*sig->tail", "head", "-1"),
        ("sig->preprocess->PrepareRuntime()", "*sig->preprocess", "preprocess", "-1"),
    ):
        needle = f"LRT_TENSOR_RETURN_IF_ERROR({expression});"
        source = replace_once(source, needle, needle +
            f"\n    if (decode && {enable}) LRT_TENSOR_RETURN_IF_ERROR({profile}_operator_profile.Register({index}, {stage}, loaded.weights_handle));")
    needle = "    LRT_TENSOR_ASSIGN_OR_RETURN(stage.post,"
    source = replace_once(source, needle,
        f"    if (decode && {enable}) LRT_TENSOR_RETURN_IF_ERROR(attention_operator_profile.Register(i, *stage.attention.runner, loaded.weights_handle));\n" + needle)
    for stage, expression in (("projection", "double elapsed=Milliseconds(at);times.forward+=elapsed;times.projection+=elapsed;"),
                               ("attention", "elapsed=Milliseconds(at);times.forward+=elapsed;times.attention+=elapsed;"),
                               ("post", "elapsed=Milliseconds(at);times.forward+=elapsed;times.post+=elapsed;")):
        source = replace_once(source, expression, expression +
            f"\n    if (sig.decode && {enable}) LRT_TENSOR_RETURN_IF_ERROR({stage}_operator_profile.Sample(i, elapsed));")
    source = replace_once(source,
        "at=BenchClock::now();LRT_TENSOR_RETURN_IF_ERROR(sig.tail->Run());times.forward+=Milliseconds(at);",
        "at=BenchClock::now();LRT_TENSOR_RETURN_IF_ERROR(sig.tail->Run());\n"
        "    const double head_elapsed=Milliseconds(at);times.forward+=head_elapsed;\n"
        f"    if ({enable}) LRT_TENSOR_RETURN_IF_ERROR(head_operator_profile.Sample(-1, head_elapsed));")
    source = replace_once(source,
        "auto at=BenchClock::now();LRT_TENSOR_RETURN_IF_ERROR(sig.preprocess->Run());times.forward+=Milliseconds(at);",
        "auto at=BenchClock::now();LRT_TENSOR_RETURN_IF_ERROR(sig.preprocess->Run());\n"
        "  const double preprocess_elapsed=Milliseconds(at);times.forward+=preprocess_elapsed;\n"
        f"  if (sig.decode && {enable}) LRT_TENSOR_RETURN_IF_ERROR(preprocess_operator_profile.Sample(-1, preprocess_elapsed));")
    collect = ("post_operator_profile.collecting = projection_operator_profile.collecting = "
               "attention_operator_profile.collecting = head_operator_profile.collecting = preprocess_operator_profile.collecting")
    needle = "    int32_t token=i?item.forced[i-1]:item.prompt.back();"
    source = replace_once(source, needle, needle +
        f"\n    {collect} = {enable} && !warmup && i > 0;")
    needle = "  return WriteLiveRun(item,index,warmup,threads,reused,compiled,rt,load_ms,passes,dir,trace.enabled(),decode_section.elapsed_ms());"
    source = replace_once(source, needle, f"  {collect} = false;\n" + needle)
    needle = "  rt.reset();\n"
    source = replace_once(source, needle,
        f"  if ({enable}) {{\n" + "".join(
            f'    LRT_TENSOR_RETURN_IF_ERROR({stage}_operator_profile.Write(dir,"{stage}"));\n'
            for stage in ("preprocess", "projection", "attention", "post", "head")) + "  }\n" + needle)
    source = source.replace('(absl::GetFlag(FLAGS_memory_report)?"false":"true")',
        f'((absl::GetFlag(FLAGS_memory_report)||{enable})?"false":"true")')
    return source


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--archive", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    archive = args.archive.resolve()
    record = json.loads((archive / "build.json").read_text())
    baseline = archive / "runner.android"
    if sha(baseline) != record["binary_sha256"]:
        raise ValueError("Archived native binary identity mismatch")
    source = instrument((archive / "driver.cc").read_text())
    output = args.output.resolve()
    output.mkdir(parents=True, exist_ok=False)
    (output / "driver.cc").write_text(source)
    cwd = Path(record["cwd"])
    compile_command = list(record["commands"][2])
    compile_command.insert(1, "-I" + str(Path(__file__).resolve().parent))
    compile_command[compile_command.index("-c") + 1] = str(output / "driver.cc")
    compile_command[compile_command.index("-o") + 1] = str(output / "driver.o")
    link = list(record["commands"][3])
    link[link.index("-o") + 1] = str(output / "runner.android")
    link = [str(output / "driver.o") if Path(s).name == "driver.o" else s for s in link]
    inputs = {s: sha(cwd / s) for s in link if s.endswith((".a", ".o")) and Path(s).name != "driver.o"}
    xnnpack_hashes = [digest for name, digest in inputs.items()
                     if Path(name).name == "libXNNPACK.a"]
    if xnnpack_hashes != [record["private_xnnpack_archive_sha256"]]:
        raise ValueError("Recorded native XNNPACK archive identity mismatch")
    for name, command in (("compile", compile_command), ("link", link)):
        with (output / (name + ".log")).open("w") as log:
            subprocess.run(command, cwd=cwd, stdout=log, stderr=subprocess.STDOUT, check=True)
    provenance = {"baseline_sha256": sha(baseline), "profile_sha256": sha(output / "runner.android"),
                  "driver_sha256": sha(archive / "driver.cc"), "link_input_sha256": inputs,
                  "compile": compile_command, "link": link}
    (output / "provenance.json").write_text(json.dumps(provenance, indent=2) + "\n")
    print("Native profiling runner built:", provenance["profile_sha256"])


if __name__ == "__main__":
    main()
