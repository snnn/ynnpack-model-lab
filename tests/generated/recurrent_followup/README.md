# Recurrent layout and chunk fixtures

Standalone `.ynn` construction plans and the matching restricted C++ builder.
No private author/compiler is needed to build or execute these fixtures.
See [the experiment guide](../../../docs/RECURRENT_STEP_EXPERIMENT.md) and
[retained evaluation](../../../results/2026-10-17-recurrent-followup/README.md).

`followup_VARIANT_GEOMETRY.ynn` uses:

| Variant | Engine / component | State order |
| ---: | --- | --- |
| 0 | `vmajor`: two matrix-vector products | V,K |
| 1 | `vmajor-reduce`: multiply/reduce spelling | V,K |
| 2 | `chunk16`: blocked triangular solve | K,V |
| 3 | `chunk32`: blocked triangular solve | K,V |
| 4 | `chunk64`: blocked triangular solve | K,V |
| 5 | `vmajor-tiled`: full 32-value tile (or smaller width) | V,K |
| 6 | `vmajor-tiled`: width-tail component | V,K |

| Geometry | Batch | K heads | V heads | K width | V width | Head map |
| ---: | ---: | ---: | ---: | ---: | ---: | --- |
| 0 | 1 | 16 | 32 | 128 | 128 | grouped |
| 1 | 1 | 1 | 1 | 5 | 7 | grouped |
| 2 | 2 | 2 | 4 | 5 | 3 | grouped |
| 3 | 2 | 2 | 4 | 5 | 3 | `(h+1)%Hk` |
| 4 | 1 | 2 | 4 | 31 | 33 | grouped |
| 5 | 1 | 2 | 4 | 129 | 17 | grouped |

Tile components use one batch/head and their geometry's K width, with value
width `min(32,Dv)` or the remainder. The harness binds the appropriate batch,
head and width slices; it does not duplicate a graph per prompt token.

Chunk constants `lower`, `strict`, `identity`, and `solve_maskWIDTH` are small
fixed matrices bound by the standalone harness. `lower` is inclusive lower
triangular; `strict` excludes the diagonal. Each solve mask selects the
lower-left block of every adjacent pair of WIDTH-sized diagonal blocks.
The blocked inverse is applied to the value/state residual, then ordinary
matrix products produce every token output and the next state.

Chunk graphs require permission for cross-token reassociation. A sequential
FP32 rounding contract alone does not authorize this algorithm. The retained
checks cover normalized Q/K, beta in `[0,1]`, finite nonpositive log-decay,
nonzero state, correlated keys, strong decay and partial chunks. No full-model
quality or GPU qualification is implied.
