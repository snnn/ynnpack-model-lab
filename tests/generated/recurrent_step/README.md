# Recurrent-step fixtures

These standalone artifacts describe one prepared FP32 gated-delta token step.
Sequence length is not part of any graph. They contain ordinary tensor operators,
with explicit input/output state; no custom recurrence or hidden body is used.

| File | Batch | K heads | V heads | K width | V width | Mapping |
| --- | ---: | ---: | ---: | ---: | ---: | --- |
| `step_0.ynn` | 1 | 16 | 32 | 128 | 128 | grouped |
| `step_1.ynn` | 1 | 1 | 1 | 5 | 7 | grouped |
| `step_2.ynn` | 2 | 2 | 4 | 5 | 3 | grouped |
| `step_3.ynn` | 2 | 2 | 4 | 5 | 3 | `(h+1)%Hk` |
| `step_4.ynn` | 1 | 2 | 4 | 31 | 33 | grouped |
| `step_5.ynn` | 1 | 2 | 4 | 129 | 17 | grouped |

`recurrent_step_generated.h` renders the same construction commands for the
optional [component harness](../../../docs/RECURRENT_STEP_EXPERIMENT.md).
Generated files must be replaced together after changing the external author.
