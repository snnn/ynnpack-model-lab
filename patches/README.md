# Dependency patches

`tools/bootstrap.py` downloads the exact revisions/hashes in `dependencies.json`
and applies the three `ynnpack-*.patch` files. Repeating it checks that the patches
are already applied. It refuses an unmanaged dependency directory or a different
revision instead of resetting local work.

The normal baseline uses upstream XNNPACK/YNNPACK
`0a66ebb5817fce48df605451444dcfc27a5e4ee4` and Slinky
`a3eec6fcfe3093be04d6c3d7dcab7d4e70bdd0dc`, matching the October 13 LiteRT-LM
comparison. Both the previous October 7 pin (`d297c798ea53`) and this pin
include upstream AVX-VNNI kernels and learned dot cost models. The update
changes x86 cost-model data, adds INT2 kernel shapes, fixes graph/runtime
edge cases and advances Slinky's thread pool. CPUinfo and tokenizer
dependencies retain their pins. Dated measurement records retain their
original revisions; Linux validation does not update earlier device results.

Use a fresh dependency/build directory when updating an existing checkout:

```sh
uv sync --locked
uv run --locked python tools/bootstrap.py --directory .deps/upstream-20261013
uv run --locked cmake -S . -B build-upstream-20261013 -G Ninja -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ \
  -DLAB_DEPS="$PWD/.deps/upstream-20261013"
uv run --locked cmake --build build-upstream-20261013 --parallel 8
uv run --locked ctest --test-dir build-upstream-20261013 --output-on-failure
```

The older dependency trees and measurement records remain useful controls.
VNNI is selected by the backend cost model on supported x86 CPUs; it is not
forced globally, and ARM measurements do not use VNNI.

## `ynnpack-dot-packing-shape.patch`

Before choosing a dot packing layout, infer the row count M from activation
tensor A when its logical row extent is constant. The previous code learned
only N/K from weight tensor B, so it used the unknown-row fallback even for a
statically one-row decode graph. The resulting layout can exclude the kernel
that the cost model prefers for the actual row count.

The patch uses `a.extent(num_k_dims)`, which also handles implicit singleton
rows in rank-one and broadcast inputs. Symbolic row counts retain the existing
fallback and packing-size caps. It changes neither arithmetic contracts nor
the cost model, and does not force an ISA or modify CPU detection. See the
[original selector reproduction](../results/2026-10-05-packing-fix/README.md#original-selector-reproduction).
The [matched validation and timing record](../results/2026-10-05-packing-fix/README.md)
documents phone DOTPROD selection, observed decode gains, and desktop numerical
differences.

The pinned upstream revision still needs this correction. Upstream separately
disables INT2 I8MM kernels until their packing uses the same `tile_k=16` as other
INT2 kernels. That removes the former INT2 layout conflict from current ARM
dispatch; it does not make unknown-row packing correct for every other dot type.

Use a fresh dependency/build directory for the patched baseline, as in the
update commands above. Preserve older binaries and measurements as controls.

## `ynnpack-symbolic-runtime.patch`

This is the original experiment's small functional patch:

- Pass frontend scalar parameters into Slinky pipeline construction/setup.
- Keep opaque state/parameter callbacks out of constant folding and common
  subgraph elimination; their semantic identities are not represented in those
  optimization keys.
- Crop reduction callbacks to logical extents for internal views, including
  empty axes. A larger physical backing buffer must not expand logical work.

The adapter uses internal APIs intentionally. This patch is not presented as a
finished upstream API proposal. We preserve independent reference tests for the
stateful behavior and arithmetic.

## `ynnpack-cmake-subproject.patch`

Build-system-only fixes for the pinned YNNPACK revision:

- Resolve Python generator paths relative to YNNPACK's project, allowing it to
  be included as a CMake subdirectory outside the XNNPACK root build.
- Generate each script's full output list while compiling only enabled ISA
  variants; the scripts require all their output arguments.
- Order dot-header generation before sources that include the common kernel
  declaration header, including handwritten AMX sources.

The current upstream CMake source already removes the disabled INT2 I8MM
variant. That formerly local patch hunk is dropped; the other build fixes
remain necessary. The symbolic-runtime and packing-shape patches apply
unchanged, as do the optional BF16 and one-row-selection patches.

The lab's root CMake config disables SME/SME2 by default and FP8 for compatibility
with the tested NDK. Disabling SME is an experiment choice, not a conclusion that
those kernels are universally bad. This extraction does not change dot arithmetic
or tune kernel selection. Previously missing x86 generator families are now
registered upstream, so their old patch hunks have been removed.

Graph-authoring integration and compiler binding patches are maintained outside
this repository. Bootstrap fetches and patches only public runtime dependencies.

## Optional one-row selection experiment

[`experiments/ynnpack-one-row-dotprod.patch`](experiments/ynnpack-one-row-dotprod.patch)
restricts compatible preparation and execution choices for known-M=1
INT8/INT2 and INT8/INT4 dots. It is used by the
[Samsung Oryon study](../results/2026-10-05-oryon-dot-selection/README.md).
`LAB_EXPERIMENT_ONE_ROW_DOT=none|int2|int4|both` selects the restriction;
unset or `none` retains normal selection. Apply it to a fresh dependency copy
after the normal patches and select that copy with `LAB_DEPS`.
Bootstrap does not apply patches under `experiments/`. The study documents
arithmetic checks, actual selected kernels, timing scope and reproduction.
The patch applies to the current pin. INT2 I8MM is unavailable in
that pin; an INT2-only restriction therefore no longer provides an I8MM/DOTPROD
comparison. The optional kernel benchmark reports candidate availability and
uses `null` for an unavailable I8MM prediction.
To replay the October 5 study, obtain its patch from the recorded lab revision;
the current patch context targets the October 7 upstream source.
