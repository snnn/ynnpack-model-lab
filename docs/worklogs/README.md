<!-- Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0 -->

# Current open work

The October 21 refresh reviews this list against the current Rust/`.ynn`
runtime. Completed runtime migrations are implementation details, not open work.
Historical evidence alone does not establish that an issue still reproduces.

| Area | Required outcome |
| --- | --- |
| [Performance](PERFORMANCE_GAPS.md) | Fresh timings and separate profiles that identify current bottlenecks |
| [Validation and reproduction](VALIDATION_GAPS.md) | Explicit device/profile coverage, numerical gates and reproducible inputs |
| [Model integrations](MODEL_INTEGRATIONS.md) | Missing model packages and their model-specific validation |

For each issue, retain its affected configuration, reproduction command or
harness, observed symptom, supporting evidence and completion check. Distinguish
reproduced failures, untested hypotheses and missing coverage. Remove resolved
entries; keep a compact regression test where practical.
