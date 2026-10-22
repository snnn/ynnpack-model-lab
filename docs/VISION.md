# FP32 vision models

Standalone YNNPACK `.ynn` plans are available for these pretrained TorchVision
classifiers:

| Family | Models |
| --- | --- |
| ResNet | `resnet18`, `resnet34`, `resnet50`, `resnet101`, `resnet152` |
| ResNeXt | `resnext50_32x4d` |
| Wide ResNet | `wide_resnet50_2` |
| MobileNet | `mobilenet_v2` |

Each model takes one FP32 image shaped `[1,3,224,224]` in NCHW order and returns
1,000 classification logits. Use the preprocessing transform for the exact
TorchVision weights named in its `model.json`. The models retain FP32 weights
and activations. Convolution and pooling execute through native YNNPACK
stencil, dot and reduction operations.

Plans live in `models/vision/<model>/generated/`. Their `model.json` records
the checkpoint, input/output names and shapes, and parameter sizes and SHA-256
hashes. Parameter blobs are local assets, excluded from Git; supply the
`parameters/` directory matching that manifest. Execution needs no model
compiler or PyTorch installation. The optional comparison harness uses NumPy,
LiteRT and previously generated PyTorch reference tensors.

Supply parameters under `models/vision/<model>/generated/parameters/` and the
comparison fixtures under `assets/vision/<model>/validation/`. The public tools
currently consume these prepared assets; they do not create the complete vision
asset/reference set from a clean download. See the
[reproduction gap](worklogs/VALIDATION_GAPS.md#public-reproduction-inputs).

## Build and run

Use the pinned backend dependencies and a separate build directory:

```sh
python3 tools/bootstrap.py --directory .deps/vision --no-tokenizers
cmake -S . -B build-vision -G Ninja \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ \
  -DLAB_DEPS="$PWD/.deps/vision" -DLAB_ENABLE_TOKENIZERS=OFF
cmake --build build-vision --parallel 8 --target vision

./build-vision/vision \
  --model_dir=models/vision/resnet50/generated \
  --input_file=assets/vision/resnet50/validation/input_2.bin \
  --output_dir=out/resnet50-example --num_threads=4 \
  --warmup_runs=3 --measured_runs=30 --dump_outputs
```

Inputs are raw little-endian FP32 values. Repeat `--input_file` to run multiple
cases through one prepared graph. The output directory must be new. The runner
writes `measurements.json` and, with `--dump_outputs`, `output_<case>.bin` logits.

## Historical host Python comparison

This workflow reproduces the earlier Linux measurements with the Python
interpreter wrapper. New baseline measurements use LiteRT's native benchmark;
the Android workflow below documents that path.

Each validation asset set contains two seeded random inputs, a photograph
processed with the checkpoint's transform, PyTorch logits, and their hashes.
The comparison tool verifies all parameter/fixture hashes, then checks every
output using `atol=1e-4, rtol=1e-3` at one and four threads. Any failed check stops
the comparison before performance measurements.

Supply the corresponding LiteRT FP32 files as
`$TFLITE_MODELS/<model>/model.tflite`. Choose CPU lists from the actual host
topology; the following example uses four distinct performance cores on the
recorded i9-12900K host:

```sh
python3 tools/compare_vision.py compare \
  --build-dir "$PWD/build-vision" --tflite-root "$TFLITE_MODELS" \
  --output out/vision-comparison \
  --cpus-1 4 --cpus-4 4,6,8,10 --warmup 3 --runs 30 --repeats 3
```

Run with a Python environment containing NumPy and `ai-edge-litert`. Use
`--models resnet50 resnet152` to select a subset. Benchmark processes run
sequentially; stop competing builds and benchmarks before starting. Both
engines use the same photograph input, FP32 checkpoint, thread count and
affinity. Pair order alternates between repetitions.

Warm latency includes invocation and runtime checks, and excludes input copying,
output copying, graph construction and preparation. YNNPACK uses the Rust
runner with native kernels; LiteRT/XNNPACK uses `Interpreter.invoke()`, including its Python wrapper.
The harness checks that the default delegate created at least one partition;
this does not establish complete delegation. Setup and first invocation are
reported separately. Current and peak RSS include each process's frontend;
incremental RSS is also reported and is not a tensor-allocation measurement.

Raw invocations, per-run medians, setup, memory, correctness, commands and model
identities are retained in the output directory. These fixed-input checks do
not measure ImageNet classification accuracy. Timing claims apply only to the
measured device and configuration.

## Android comparison with the native LiteRT benchmark

Use LiteRT's `//litert/tools:benchmark_model` target, whose entry point is
`benchmark_model_main` in `litert/tools/BUILD`, for the Android control. Build it
with the LiteRT checkout's documented Android Bazel command, adding
`--define=litert_enable_ynnpack=false`, `--define=xnn_enable_arm_sme=false`, and
`--define=xnn_enable_arm_sme2=false`. These select the ordinary XNNPACK CPU
control and keep SME studies separate. Build `//litert/tools:run_model` with
the same options for independent fixture validation. On Android, add
`--per_file_copt=litert/tools/run_model.cc@-DABSL_FLAGS_STRIP_NAMES=0` to preserve
that tool's CLI flags. Keep copies of both binaries before another build.

The native benchmark generates its own input; it does not consume the saved
photograph. Reproduce its default FP32 input using the same C++ standard library
as the benchmark. With NDK r28c and static libc++:

```sh
"$ANDROID_NDK/toolchains/llvm/prebuilt/linux-x86_64/bin/aarch64-linux-android28-clang++" \
  -std=c++20 -O2 -static-libstdc++ tools/vision_benchmark_input.cc \
  -o out/vision_benchmark_input
adb -s "$ANDROID_SERIAL" push out/vision_benchmark_input /data/local/tmp/
adb -s "$ANDROID_SERIAL" shell \
  /data/local/tmp/vision_benchmark_input /data/local/tmp/vision-input.bin
adb -s "$ANDROID_SERIAL" pull /data/local/tmp/vision-input.bin out/vision-input.bin
```

The generator mirrors `tflite/tools/utils.cc`: default-seeded `std::mt19937`
and `std::uniform_real_distribution<float>(-0.5, 0.5)` for `[1,3,224,224]`.
Review that source when changing LiteRT versions. STL implementations can
produce different sequences. The generator requires a new output file.

Create an ignored devices JSON file containing a list of objects with `label`,
`serial`, `masks`, and `performance_cpus` fields. `masks` maps `"1"` and `"4"`
to hexadecimal CPU masks containing one and four CPUs. `performance_cpus`
maps reviewed big/middle CPU IDs to their expected hexadecimal MIDR values.
For the measured TECNO, for example:

```json
{
  "label": "tecno",
  "serial": "${ANDROID_SERIAL}",
  "masks": {"1": "80", "4": "f0"},
  "performance_cpus": {
    "4": "0x411fd4d0", "5": "0x411fd4d0",
    "6": "0x411fd4d0", "7": "0x411fd4d0"
  }
}
```

Substitute the serial in this JSON; the harness does not expand variables.
Check `/sys/devices/system/cpu/cpu*/regs/identification/midr_el1`,
`cpu_capacity`, and `cpufreq/related_cpus` against CPU/vendor documentation
before approving that map. Frequency alone does not identify a little core.
Exclude little cores from both timing and validation masks. The harness records
per-core topology, checks expected MIDRs, and rejects masks outside the reviewed
set or online CPUs before deploying or running models. This is an explicit
reviewed map, not automatic core-class detection. Do not reuse another phone's
map; check free storage and memory before deployment. The retained
[topology audit](../results/2026-10-21-current/vision-android/cpu-topology.json)
contains the three measured devices' core identities and reviewed maps.

```sh
python tools/compare_vision_android.py \
  --devices-json out/vision-devices.json \
  --ynn-binary build-android/vision \
  --benchmark-binary "$LITERT_BENCHMARK" \
  --validation-binary "$LITERT_RUN_MODEL" \
  --benchmark-input out/vision-input.bin \
  --litert-root "$LITERT_ROOT" --protoc "$PROTOC" \
  --tflite-root "$TFLITE_MODELS" \
  --remote-root /data/local/tmp/vision-comparison \
  --output out/vision-android --warmup 3 --runs 10 --repeats 2 --cooldown 10
```

Run with NumPy and protobuf installed. `PROTOC` is a host executable; the harness
reads the benchmark's own result and runtime-info schemas. It verifies local
and deployed hashes, runs every process sequentially, reverses engine order
between rounds, captures battery/frequency/thermal snapshots, and restores the
original stay-awake setting. Governors and frequency limits are unchanged.
The device directory and local result directory must be new. An explicit
`--reuse-deployment` permits an existing device directory, rechecks every file,
and still rejects existing per-job output directories.

YNNPACK fixture checks cover one and four threads. LiteRT fixture checks use
`run_model`'s default one CPU thread and the same three PyTorch references.
Separate `benchmark_model` diagnostic runs retain actual delegate coverage.
Both timed engines use one/four threads and the matched synthetic input; neither
Python inference nor output dumping runs inside the timed processes.
The Android summary reports mean warm invocation time across the rounds. Native
benchmark protobufs retain per-process mean, median, range, setup, first invoke,
and run counts; YNNPACK also retains individual invocation times. LiteRT's memory
footprint fields are increments in process peak RSS on these platforms, whereas
YNNPACK records current and absolute peak RSS. Peak-memory polling is disabled.
