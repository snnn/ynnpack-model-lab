// Generated YNNPACK builder; do not edit.
#include "gemma4_prefill.h"
#include "gemma4_prefill_builder.h"

std::unique_ptr<lab_ynn::Graph> BuildGemma4Prefill(
    const std::function<const void*(const char*, size_t)>& weights) {
  auto g = std::make_unique<lab_ynn::Graph>(6875);
  BuildGemma4PrefillSource::Context ctx{g.get(), weights};
  BuildGemma4PrefillSource::BuildDefineValues(ctx);
  const slinky::expr s3 = g->Axis(6200, 2);
  const slinky::expr s1 = g->Axis(6230, 1);
  const slinky::expr s2 = g->Parameter("position", int64_t{0}, int64_t{32768});
  ctx.s3 = s3;
  ctx.s1 = s1;
  ctx.s2 = s2;
  BuildGemma4PrefillSource::BuildBindInvocation(ctx);
  BuildGemma4PrefillSource::BuildRopeTables(ctx);
  BuildGemma4PrefillSource::BuildInputProjection(ctx);
  BuildGemma4PrefillSource::BuildLayer0(ctx);
  BuildGemma4PrefillSource::BuildLayer1(ctx);
  BuildGemma4PrefillSource::BuildLayer2(ctx);
  BuildGemma4PrefillSource::BuildLayer3(ctx);
  BuildGemma4PrefillSource::BuildLayer4(ctx);
  BuildGemma4PrefillSource::BuildLayer5(ctx);
  BuildGemma4PrefillSource::BuildLayer6(ctx);
  BuildGemma4PrefillSource::BuildLayer7(ctx);
  BuildGemma4PrefillSource::BuildLayer8(ctx);
  BuildGemma4PrefillSource::BuildLayer9(ctx);
  BuildGemma4PrefillSource::BuildLayer10(ctx);
  BuildGemma4PrefillSource::BuildLayer11(ctx);
  BuildGemma4PrefillSource::BuildLayer12(ctx);
  BuildGemma4PrefillSource::BuildLayer13(ctx);
  BuildGemma4PrefillSource::BuildLayer14(ctx);
  return g;
}
