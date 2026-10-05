<!-- Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0 -->

# Original E2B performance comparison

This is the October 2, 2026 campaign described in
[MEASUREMENTS.md](../../docs/MEASUREMENTS.md). It contains 75 configurations,
225 measured requests, and 75 warmups. The original graphs precede the current
standalone builder preparation policy. Existing metric values are unchanged.

| File | Contents |
| --- | --- |
| `metrics.csv`, `metrics.json` | Final per-configuration median TTFT/prefix and reciprocal mean continuation latency, plus setup and process peak RSS |
| `requests.json` | All 300 requests, including warmups and individual continuation latencies; unchanged original timing values |
| `commands.json` | 33 recorded process command arrays, with external locations replaced by named placeholders |
| `environment.json` | Workload/hardware/affinity, binary/model/runtime/generated-artifact identities, fixture hashes, and scope notes |
| `profile-ynn-flat.txt`, `profile-litert-static-flat.txt`, `profile-litert-packed-flat.txt` | Warm desktop cycle-sample summaries identifying dominant kernels; raw perf captures are not included |
| `fixtures/p*-d32.tsv` | The three original hash-matching per-prompt native fixtures |
| `full-accuracy.json`, `self-consistency.json` | Cross-backend numerical characterization and capacity/chunk checks |
| `self-c8448-memory.json` | Resident mapping categories from one diagnostic snapshot |
| `standalone-*` | Later standalone correctness/build checks; not another performance campaign |

The canonical multi-case fixtures are
[`performance.tsv`](../../models/gemma4_e2b/fixtures/performance.tsv) and
[`correctness.tsv`](../../models/gemma4_e2b/fixtures/correctness.tsv).

## Recorded command substitutions

Command arrays preserve the flags, environment switches, affinity, capacity,
threads, and warmup/repetition settings. They are normalized historical
templates, not directly runnable `tools/benchmark.py` configurations. Resolve
the placeholders for the selected platform before executing a command:

| Placeholder | Meaning |
| --- | --- |
| `${YNN_BINARY}` | Historical YNNPACK executable for host or device |
| `${LITERT_XNNPACK_BINARY}` | Preserved fully delegated LiteRT/XNNPACK control |
| `${NATIVE_XNNPACK_BINARY}` | Preserved native Tensor API/XNNPACK control |
| `${CONTROL_MODEL_DIR}` | External control TFLite graphs |
| `${BUNDLE_DIR}` | Prepared source bundle appropriate to the selected runner |
| `${YNN_PARAMETER_DIR}` | Parameters matching the historical YNNPACK builders |
| `${PACKED_WEIGHT_CACHE}` | Separate control cache matching that graph and capacity |
| `${FIXTURE_DIR}` | Deployed fixtures: canonical multi-case TSV or supplied per-prompt TSV |
| `{output}` | A new output directory for that process |

`record_label` identifies the original process without retaining its local path.
The host packed control's initial cache-creation command is retained, together
with the later cache-warm command. The final metrics and request records use
the cache-warm process. Native short-prompt chunk settings and KV alignment
remain explicit in the command records.

The controls are external artifacts, identified by hashes, and are not built by
this repository. The supplied CMake/build/asset instructions reproduce the
standalone YNNPACK workload, not every historical control binary. Private
authoring/compiler provenance, individual device identifiers, and local source,
model, cache, and capture paths are excluded from these public records.
