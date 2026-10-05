# Text inputs and native tokenizers

The C++ benchmark frontend accepts real text and resolves it to token IDs before
preparing the model. It supports Hugging Face `tokenizer.json` through the
Rust tokenizer library and SentencePiece model files through its C++ processor.
The same frontend can be used by future Qwen and other model runners.

Existing TSV fixtures remain useful for controlled performance and numerical
comparisons. Their IDs are already supplied by the fixture; a tokenizer does
not participate in a TSV run. No random or synthetic IDs are introduced when
text is tokenized. Every successful run exports the actual IDs it uses.

This frontend performs forced continuation benchmarks. Argmax remains a
diagnostic; it is not fed back into the model. Text inputs do not apply chat
templates or automatically append EOS. Supply any desired conversation
formatting as literal text, with the chosen tokenizer's special-token semantics.

## Build

Native tokenizers are enabled by default. Install Rust/Cargo in addition to the
root README's host prerequisites. Use Rust 1.87 or newer; the implementation was
validated with host Rust 1.98.1 and Android Rust 1.99.0.

```sh
python3 tools/bootstrap.py
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++
cmake --build build --parallel 8
ctest --test-dir build --output-on-failure
```

Bootstrap checks the source archives in `dependencies.json`, applies the
checked tokenizer FFI and offline SentencePiece patches, installs the tracked
Cargo lockfile, and fetches its checksum-verified crates into `.deps/cargo`.
CMake builds with `cargo --frozen`: it cannot resolve new versions or download
missing crates. SentencePiece and Abseil also use bootstrapped local sources.
The unused upstream RWKV/MsgPack wrapper is excluded. The Rust tokenizer version
is exactly 0.22.2; do not change it without updating the lockfile and parity checks.

To retain token-ID-only benchmarks on a machine without Rust:

```sh
python3 tools/bootstrap.py --no-tokenizers
cmake -S . -B build -G Ninja -DLAB_ENABLE_TOKENIZERS=OFF
```

This build accepts TSV input and gives an explicit error for text inputs.

## Prepare local assets

Running the regular `tools/prepare_gemma4.py` extraction now also writes
`tokenizer/manifest.json` and `tokenizer/tokenizer.model` under the new asset
directory. E2B and E4B extract the hash-pinned SentencePiece section from their
own published `.litertlm` source. For an existing weight extraction, prepare
only the tokenizer into a fresh directory:

```sh
python3 tools/prepare_tokenizer.py \
  --recipe models/gemma4_e2b/tokenizer_recipe.json \
  --source assets/download/gemma-4-E2B-it.litertlm \
  --output assets/gemma4_e2b/tokenizer
```

For E4B, use `models/gemma4_e4b/tokenizer_recipe.json` and its exact downloaded
bundle. Both published bundles currently contain identical tokenizer payloads;
their source identities remain distinct in the manifests.

HF recipes are available in `models/tokenizers/` for Gemma4, Qwen3-0.6B, and
Qwen3.5-0.8B. Each recipe records an immutable publisher revision, source size
and SHA-256, and the payload identity. For example:

```sh
uvx hf download Qwen/Qwen3-0.6B tokenizer.json \
  --revision c1899de289a04d12100db370d81485cdf75e47ca \
  --local-dir assets/download-qwen3
python3 tools/prepare_tokenizer.py \
  --recipe models/tokenizers/qwen3_0_6b.json \
  --source assets/download-qwen3/tokenizer.json \
  --output assets/qwen3-tokenizer
```

The preparation tool copies the payload without conversion. It uses only the
Python standard library. It validates source and output hashes, rejects an
existing output directory, and publishes the directory only after verification.
The runner requires explicit local assets and never downloads a tokenizer.
Preparing Qwen tokenizer assets does not add Qwen execution graphs to this lab.

## Input modes

Choose exactly one input mode. Text modes require `--tokenizer_dir=DIR`; TSV
uses the supplied IDs directly. Other runner options retain their meanings.

An explicit prompt and optional forced continuation:

```sh
./build/gemma4_e2b \
  --bundle_dir=assets/gemma4_e2b/bundle \
  --parameter_dir=assets/gemma4_e2b/parameters \
  --tokenizer_dir=assets/gemma4_e2b/tokenizer \
  --prompt='The cat sat' --continuation=' on the mat.' \
  --output_dir=out/text-prompt
```

Use `--prompt_file=FILE` or `--continuation_file=FILE` for binary file reads that
preserve all UTF-8 bytes, including leading/trailing whitespace, newlines, and
embedded NULs. Invalid UTF-8 fails. Empty literal text is allowed when the final
prompt still contains at least one token, such as Gemma's BOS. The explicit case
is named `prompt`.

For multiple cases, `--text_cases_file=JSONL` reads objects of this form:

```json
{"name":"cat","prompt":"The cat sat","continuation":" on the mat."}
{"name":"unicode","prompt":"中文 café 🙂\n"}
```

Names must be unique ASCII identifiers using letters, digits, `_`, or `-`.
The continuation defaults to empty. Unknown fields, duplicate JSON keys,
incorrect types, and malformed records fail. Prompt and continuation are
encoded **separately**, so their concatenated IDs need not equal the encoding
of concatenated text. This preserves an explicit forced-continuation boundary.

For an exact-length matrix from a corpus:

```sh
./build/gemma4_e2b \
  --bundle_dir=assets/gemma4_e2b/bundle \
  --parameter_dir=assets/gemma4_e2b/parameters \
  --tokenizer_dir=assets/gemma4_e2b/tokenizer \
  --corpus_file=assets/corpus.txt --prompt_lengths=17,128,1024 \
  --continuation_tokens=32 --cache_capacity=2048 \
  --output_dir=out/text-matrix
```

The corpus is encoded once. Each case starts at the same corpus position. A
requested length `P` includes manifest prefix and suffix IDs; the body takes
the first `P - prefix_count - suffix_count` corpus IDs. The continuation takes
the following `D` corpus IDs. Case names are `prompt_P`. Duplicate lengths,
insufficient corpus text, and requests exceeding capacity fail. The frontend
does not repeat text or pad tokens to make a request fit.

All cases are resolved and checked before model setup or state mutation.
Every ID must fit the model vocabulary and every request must satisfy
`prompt_count + continuation_count <= capacity`. The final prompt token still
uses the full decode graph to produce first logits, and prefix chunks still
use 1–128 real rows with a partial final chunk.

## Manifest and model policy

A tokenizer directory contains `manifest.json` and the referenced payload:

```json
{
  "version": 1,
  "format": "hf_json",
  "file": "tokenizer.json",
  "bytes": 11422654,
  "sha256": "aeb13307a71acd8fe81861d94ad54ab689df773318809eed3cbe794b4492dae4",
  "vocab_size": 151669,
  "source": {
    "repo": "Qwen/Qwen3-0.6B",
    "revision": "c1899de289a04d12100db370d81485cdf75e47ca",
    "path": "tokenizer.json",
    "bytes": 11422654,
    "sha256": "aeb13307a71acd8fe81861d94ad54ab689df773318809eed3cbe794b4492dae4"
  },
  "prefix_ids": [],
  "suffix_ids": []
}
```

The other format is `sentencepiece`. Payload paths must be relative and cannot
contain `.` or `..` components. The runner verifies size and SHA-256 before
loading. `vocab_size` is the ID extent: highest tokenizer ID plus one, including
added tokens. It is checked against the native tokenizer. A model may have
extra padded embedding/head entries; the tokenizer's extent must fit inside
the model vocabulary. Policy IDs must also exist in the native vocabulary.

Only the manifest applies prompt prefix/suffix IDs. HF encoding uses
`add_special_tokens=false`; SentencePiece has no implicit BOS/EOS options.
Published Gemma manifests specify `prefix_ids: [2]`; Qwen manifests specify
empty prefix/suffix arrays. HF assets containing automatic padding or
truncation are rejected. The metadata records the complete selected policy.

HF and SentencePiece are separate native formats. For example, Gemma HF JSON
recognizes literal `<bos>`/`<eos>` strings as special IDs, while its published
SentencePiece tokenizer encodes those control-token spellings as ordinary
text. Compare each format to its own reference. Do not assume two formats
always produce the same IDs just because their vocabularies match.

## Artifacts and timing

Every successful run, including TSV input, writes:

- `resolved_cases.tsv`: canonical case names, prompt IDs, and continuation IDs.
- `frontend.json`: input byte counts/hashes, source and payload identities,
  manifest hash, selected policy, resolved counts and fixture hash, timing,
  and current/peak RSS snapshots before and after frontend work.
- The existing `run.json`, `timings.jsonl`, and optional model dumps.

`tokenizer_load_ms` includes manifest/payload verification and native loading.
`tokenizer_encode_ms` measures native encode calls; a corpus matrix makes one
call. `frontend_total_ms` additionally includes input reading, parsing,
validation, fixture serialization, and tokenizer destruction. Writing output
files and process startup are excluded. TSV runs report zero tokenizer load
and encode time.

The tokenizer is released before model setup. Allocators may retain released
pages, and process peak RSS still includes the frontend's peak. The metadata's
`rss_after_release_kib` is a measured current RSS, not a promise that all pages
were returned to the OS. These snapshots also include resolved case IDs.

Model `setup_ms` retains its original scope. Warm TTFT remains prefix time plus
the final prompt-token step; decode throughput excludes that first step.
Tokenizer time is reported separately and is never added to either metric.
`tools/benchmark.py` preserves the frontend record in its summaries.

Replay a text run's `resolved_cases.tsv` with `--cases_file` when comparing
another tokenizer frontend or runtime. Match IDs, continuation counts,
capacity, chunking, threads, affinity, and numerical formats.

## Validation and Android

Ordinary CTest includes native exact-ID/decoded-string references and frontend
input validation, using small local fixtures without model weights or Python
tokenizer packages. To compare downloaded real assets against Python:

```sh
uv run --no-project --with tokenizers==0.22.2 --with sentencepiece==0.2.1 \
  python tools/check_tokenizer_parity.py \
  --probe build/tokenizer_probe --tokenizer_dir=assets/gemma4_e2b/tokenizer \
  --output out/tokenizer-parity
```

`tokenizer_probe` resolves text to the same fixture/metadata without loading a
model. The parity tool tests multilingual text, controls, special spellings,
and corpus lengths 1/128/129/130/511/512/513/1024 using independent Python IDs.

Android builds additionally need the Rust target:

```sh
rustup target add aarch64-linux-android
cmake -S . -B build-android -G Ninja \
  -DCMAKE_TOOLCHAIN_FILE="$ANDROID_NDK/build/cmake/android.toolchain.cmake" \
  -DANDROID_ABI=arm64-v8a -DANDROID_PLATFORM=android-28 \
  -DANDROID_STL=c++_static -DCMAKE_BUILD_TYPE=Release
cmake --build build-android --parallel 8
```

The CMake integration selects the NDK API-specific C compiler and archiver for
Rust's native dependencies. ARM64, NDK r28c, API 28, and static libc++ are the
validated configuration. Set `LAB_CARGO` for an alternate Cargo executable and
preserve `RUSTUP_HOME` during configure/build if using an isolated Rust install.
Set `LAB_RUST_TARGET` explicitly for other cross builds; those are unvalidated.

Use an explicit ADB serial, check free storage/memory, and push the tokenizer
directory along with the model assets. To run the weights-free native tests:

```sh
adb -s "$ANDROID_SERIAL" shell mkdir -p /data/local/tmp/ynnpack-tokenizers
adb -s "$ANDROID_SERIAL" push build-android/tokenizer_test tests/tokenizers \
  /data/local/tmp/ynnpack-tokenizers/
adb -s "$ANDROID_SERIAL" shell \
  /data/local/tmp/ynnpack-tokenizers/tokenizer_test \
  /data/local/tmp/ynnpack-tokenizers/tokenizers \
  /data/local/tmp/ynnpack-tokenizers/test-data
```

For model validation, run text and exported TSV inputs with `--dump_outputs` in
separate fresh directories and compare logits and live KV dumps exactly on the
same binary. Disable dumps for latency measurements.
