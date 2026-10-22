<!-- Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0 -->

# Publication contents

Publish enough source and evidence for XNNPACK/YNNPACK engineers to run the
workloads, inspect the performance gap, and reproduce backend limitations.
The [documentation index](README.md) separates usage/design references from
[open investigations](worklogs/README.md); the [result index](../results/README.md)
identifies retained evidence.

## Source and evidence to include

| Contents | Purpose |
| --- | --- |
| CMake files, pinned dependencies, and public backend/tokenizer patches | Rebuild the standalone Linux/Android workloads with known dependency changes. |
| `.ynn` construction plans, model metadata, Rust runners, and native runtime helpers | Execute the full models and their symbolic state contracts without a private compiler. Include both phases and their matching metadata hashes. |
| Public architecture/asset readers, hash-verified extraction recipes, and manifests | Obtain the same source weights, scales, and precision without distributing model payloads. |
| Token-ID fixtures, native input/tokenizer tools, and tiny synthetic tokenizer fixtures | Compare the same IDs and construct controlled prompt lengths. Qwen recipes currently cover tokenization only. |
| Independent arithmetic/state tests and focused backend bug reproductions | Establish what is correct and isolate failures, including E4B preparation depth and BF16 rounding. |
| Retained baseline metrics, request timings, kernel summaries, artifact hashes, and portable command records | Make performance claims inspectable, including uncertainty and different quantization/cache policies. |
| Numerical and capacity-consistency summaries | Distinguish backend arithmetic differences from changes to logically identical work. |
| LICENSE, NOTICE, and retained third-party notices | Preserve ownership and licensing, including required copyright attribution. |

Group evidence by model, source/numerical profile and device so readers can
select the comparison relevant to their workload. Keep arithmetic/precision
audits with those comparisons. A correctness run with dumps enabled must not
be presented as a latency baseline.

Retain the current baseline and minimal evidence for unresolved issues.
Superseded campaigns and resolved migration history are archived locally outside
the repository. The [result index](../results/README.md) identifies the retained
questions and whether they have been revalidated on the current checkout.

The XNNPACK/LiteRT comparison controls are preserved external artifacts. Their
hashes and normalized recorded flags are included, but this repository does not
build every control executable or export its TFLite graph. Independent
reproduction of those controls still needs distributable build/export recipes
and the exact source/quantization policy. State that gap instead of treating a
hash or unavailable binary as a complete reproduction recipe.

## Material to keep local

Exclude model weights, downloaded payloads, packed caches, build trees, large
output dumps, raw profiler captures, raw device logs, credentials, and personal
text corpora. Existing ignore rules cover the standard asset/build/output
directories. Temporary upstream PR reviews remain local experiments, including
their patches, reports, profiles, and timings.

Private graph authors, compiler sources/imports, binding patches, installation
instructions, raw compiler reports, and private provenance stay in their
separate repository. Local agent guidance is excluded as well. Standalone
`.ynn` plans and runtime helpers retain their notices; see [AUTHORING.md](AUTHORING.md).

## Portable measurement records

Retain performance-relevant information: CPU/device model, OS/firmware build,
compiler and NDK versions, actual compilation flags, dependency revisions and
patch hashes, graph/fixture/model/binary hashes, kernel symbols, thread count,
affinity, temperature/frequency observations, repetition counts, and timing
boundaries. Firmware build fingerprints identify software releases and are
distinct from individual device identifiers.

Omit device serials, IMEI/IMSI, account names, hostnames, personal contact
information, IP/MAC addresses, and user-directory paths. Use model/platform
labels to distinguish machines. Use repository-relative paths for supplied
files and named variables such as `ANDROID_NDK`, `ANDROID_SERIAL`, and
`BUNDLE_DIR` for external locations. Generic Android test directories in usage
examples are portable destinations created by those examples.

For unavailable historical binaries, record an artifact label and its hash;
do not link to a local capture directory. Mark normalized command arrays as
templates and document their substitutions. Keep original local captures
outside Git, and preserve measured values when sanitizing records.

## Checks before publishing

```sh
uv sync --locked
uv run --locked python tools/check_publication.py
uv run --locked python -m unittest discover -s tests -p test_publication.py
git diff --check
```

The Python dependency versions and package hashes are retained in
[`pyproject.toml`](../pyproject.toml) and [`uv.lock`](../uv.lock). The checker
uses [email-validator](https://github.com/JoshData/python-email-validator) for
address syntax after extracting candidates from text. It handles international
addresses, quoted local parts, bracketed IP domains, and escaped JSON strings.
DNS and delivery checks are disabled; detection does not require network access.
Third-party license files and copyright attribution retain their email notices.
Missing dependencies fail with setup instructions instead of skipping the check.

The publication check scans tracked files and unignored candidate files. It
flags common host paths, device identifiers, contact information, private
compiler provenance, and accidentally included local artifacts. CI runs it
before bootstrapping runtime dependencies. It does not inspect ignored captures or
change file contents. Review prose, arbitrary text fixtures, filenames, and
new record fields for information the pattern checks cannot recognize.

After selecting the changes for a commit, check its actual contents:

```sh
uv run --locked python tools/check_publication.py --staged
```

File cleanup does not remove earlier copies from Git history or change commit
author/committer metadata. Check any history intended for publication separately;
`--revision=HEAD` checks the files in that commit. Use a clean public snapshot
when earlier history contains personal/private material, retaining local
history separately. Do not publish the archived private authoring history.
