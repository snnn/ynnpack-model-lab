# Recurrent step graphs

The [2026-10-17 follow-up](../results/2026-10-17-recurrent-followup/README.md)
adds persistent state layouts, tile-local execution, scratch reuse and
algebraic chunkwise prefill. The 1024-token chunk candidates qualify on both
CPUs; decode remains open. These are component results, not full-model results.

The [2026-10-16 evaluation](../results/2026-10-16-recurrent-step/README.md)
records successful x86/Pixel 11 correctness through 1024 tokens and an
unqualified performance result for the tested primitive lowering. It includes
the native/adapter controls, selected kernels and explicit stability limits.

The optional `recurrent_step_bench` compares ordinary YNNPACK primitives against
the current custom gated-delta implementation and, when configured, llama.cpp.
It is a weights-free component experiment. It does not alter model packages,
the generic model runner, or the default recurrent lowering.

The standalone [fixtures](../tests/generated/recurrent_step/README.md) contain
`.ynn` files and `recurrent_step_generated.h` emitted by the same external author.
Set `LAB_RECURRENT_STEP_GENERATED` to `tests/generated/recurrent_step` as an
absolute path when configuring CMake. The public harness has no Core IR dependency.
Optional `LAB_GGML_ROOT` and `LAB_GGML_LIB_DIR` enable the llama.cpp control.
The same source builds for Linux x86-64 and Android ARM64.
Select `LAB_DEPS` explicitly and verify it against the baseline runner's build
cache and source manifests. Updating dependency pins does not update an existing
extracted `.deps` directory. The optional diagnostic interceptor uses the pinned
internal dot-kernel signature and needs review when that API changes.

```sh
cmake -S . -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ \
  -DLAB_DEPS="$QUALIFIED_DEPS" -DLAB_ENABLE_TOKENIZERS=OFF \
  -DLAB_RECURRENT_STEP_GENERATED="$PWD/tests/generated/recurrent_step"
cmake --build "$BUILD" --target recurrent_step_bench recurrent_step_test
"$BUILD/recurrent_step_test"
"$BUILD/recurrent_step_bench" --engine=step-native --rows=1024 --threads=4
```

Engine choices are `step-adapter`, `step-native`, `custom`, `custom-step`, and
optional `llama`. The first two execute the same primitive builder through
normal adapter validation or fixed-shape native invocation. `custom` processes
the sequence in one scheduled operation; `custom-step` invokes that operation
once per token. State buffers are explicit and never alias their incoming state.

Every benchmark process checks an independent FP64 reference before timing.
Use `--batches=0` for correctness only. Primary lengths include 1, 17, 32, 128
and 1024. Repeated step execution is sequential recurrence, not chunkwise matrix
prefill. Setup and reference checks are excluded from reported latency.
llama.cpp uses its native state/output layout; comparison permutations occur
outside timing.

`recurrent_step_diagnostics` separately reports actual selected dot kernels and
scratch allocation counts. It is instrumented and must not provide timing
results. `--pipeline=PATH` dumps the schedule; `STEP_TRACE=1` prints buffer bounds
in the fixed-shape native path. No backend dependency patch is needed.

Measure paired engines sequentially with matched affinity, threads and inputs,
and preserve both run orders, device conditions and source/binary identities.
Do not infer architecture-wide performance from the portable fallback baseline:
the current custom recurrence has explicit AVX2 specialization but no equivalent
ARM specialization. An independent optimized ARM control is necessary.

## Layout and chunk candidates

Add `-DLAB_RECURRENT_FOLLOWUP_GENERATED="$PWD/tests/generated/recurrent_followup"`
to the configuration above, keeping the original step artifacts enabled.
Rebuild `recurrent_step_bench` and `recurrent_step_diagnostics`.
The [new fixtures](../tests/generated/recurrent_followup/README.md) add engines
`vmajor`, `vmajor-reduce`, `vmajor-tiled`, `chunk16`, `chunk32`, and `chunk64`.
Use `--stress=3 --batches=0` for identical-key, zero-decay, beta-one checks.

```sh
"$BUILD/recurrent_step_bench" --engine=chunk32 --rows=1024 --threads=4
STEP_SCRATCH_POOL=1 "$BUILD/recurrent_step_bench" \
  --engine=chunk32 --rows=1024 --threads=4
```

Scratch reuse is an experiment-only allocator option. It retains separate
blocks for simultaneous live allocations and reuses them across invocations;
it never caches tensor contents. It is not enabled in production model runners.
The retained ARM qualification enables it; x86 qualification uses the default
allocator. Always label this difference when comparing those rows.

Chunk graphs use ordinary operators and a blocked triangular inverse. They
explicitly permit reassociation across tokens. They do not preserve the
sequential FP32 rounding order. Their tested domain has normalized Q/K,
nonpositive finite log-decay, beta in `[0,1]` and finite FP32 state. Partial
chunks pad with zero beta/log-decay/Q/K/V, leaving state unchanged. Padding,
tail copies and state handoffs are timed. Full chunks bind directly to the
token-major inputs and outputs. Graph size depends on the fixed chunk width,
not total prompt length.

V-major candidates retain `[B,Hv,Dv,Dk]` state across calls; setup converts only
the initial state. The tiled candidate loops over independent 32-value state
tiles outside time, with one prepared single-thread runtime per worker. It
introduces many small invocations and does not add a fused recurrent kernel.
The chunk candidates retain `[B,Hv,Dk,Dv]` state, compatible with the existing
custom recurrence's state layout.
