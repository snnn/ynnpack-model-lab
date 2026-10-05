# Dependency patches

`tools/bootstrap.py` downloads the exact revisions/hashes in `dependencies.json`
and applies the two `ynnpack-*.patch` files. Repeating it checks that the patches
are already applied. It refuses an unmanaged dependency directory or a different
revision instead of resetting local work.

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
- Register missing x86 dot generator outputs/families, including symmetric INT8,
  low-bit INT2/INT4, and FP32 k8.
- Generate each script's full output list while compiling only enabled ISA
  variants; the scripts require all their output arguments.
- Order dot-header generation before sources that include the common kernel
  declaration header, including handwritten AMX sources.

The lab's root CMake config disables SME/SME2 by default and FP8 for compatibility
with the tested NDK. Disabling SME is an experiment choice, not a conclusion that
those kernels are universally bad. This extraction does not change dot arithmetic
or tune kernel selection.

Graph-authoring integration and compiler binding patches are maintained outside
this repository. Bootstrap fetches and patches only public runtime dependencies.
