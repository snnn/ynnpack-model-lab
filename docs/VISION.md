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

## Correctness and CPU comparison

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
not measure ImageNet classification accuracy or establish device performance.
