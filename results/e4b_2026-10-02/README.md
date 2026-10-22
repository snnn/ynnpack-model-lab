<!-- Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0 -->

# E4B preparation stack evidence

This compact record is retained for an unresolved preparation-depth issue.
It describes the October 2 configuration and has not been reproduced with a
small stack in the current refresh. Use the [current baseline](../README.md)
for performance; superseded integration timings have been archived locally.

## Android preparation stack overflow

The original TECNO decode graph failed under an 8-MiB shell stack with a
stack-overflow diagnosis and repeated Slinky simplifier frames. The
[symbolized crash summary](preparation-stack-overflow.txt) identifies the path.

An explicit 64-MiB execution-thread stack allowed preparation to complete.
The [host parity check](stack-workaround-parity.json) retained 2,619 exact output
matches across that workaround. This did not change Slinky's recursive traversal.
The current Rust runners also reserve a larger stack; successful runs with that
reservation do not close the underlying issue.

To close it, reproduce preparation of the affected E4B graph with bounded stack
use and validate outputs against the matching control. Keep the workaround
until that check passes.
