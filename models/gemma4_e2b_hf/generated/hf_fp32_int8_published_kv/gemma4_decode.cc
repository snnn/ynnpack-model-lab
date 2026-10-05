// Generated YNNPACK builder; do not edit.
#include "gemma4_decode.h"
#include "gemma4_decode_builder.h"

std::unique_ptr<lab_ynn::Graph> BuildGemma4Decode(
    const std::function<const void*(const char*, size_t)>& weights) {
  auto g = std::make_unique<lab_ynn::Graph>(8435);
  BuildGemma4DecodeSource::Context ctx{g.get(), weights};
  BuildGemma4DecodeSource::BuildDefineValues(ctx);
  const slinky::expr s3 = g->Axis(7045, 2);
  const slinky::expr s2 = g->Parameter("position", int64_t{0}, int64_t{32768});
  ctx.s3 = s3;
  ctx.s2 = s2;
  BuildGemma4DecodeSource::BuildBindInvocation(ctx);
  BuildGemma4DecodeSource::BuildRopeTables(ctx);
  BuildGemma4DecodeSource::BuildInputProjection(ctx);
  BuildGemma4DecodeSource::BuildLayer0(ctx);
  BuildGemma4DecodeSource::BuildLayer1(ctx);
  BuildGemma4DecodeSource::BuildLayer2(ctx);
  BuildGemma4DecodeSource::BuildLayer3(ctx);
  BuildGemma4DecodeSource::BuildLayer4(ctx);
  BuildGemma4DecodeSource::BuildLayer5(ctx);
  BuildGemma4DecodeSource::BuildLayer6(ctx);
  BuildGemma4DecodeSource::BuildLayer7(ctx);
  BuildGemma4DecodeSource::BuildLayer8(ctx);
  BuildGemma4DecodeSource::BuildLayer9(ctx);
  BuildGemma4DecodeSource::BuildLayer10(ctx);
  BuildGemma4DecodeSource::BuildLayer11(ctx);
  BuildGemma4DecodeSource::BuildLayer12(ctx);
  BuildGemma4DecodeSource::BuildLayer13(ctx);
  BuildGemma4DecodeSource::BuildLayer14(ctx);
  BuildGemma4DecodeSource::BuildLayer15(ctx);
  BuildGemma4DecodeSource::BuildLayer16(ctx);
  BuildGemma4DecodeSource::BuildLayer17(ctx);
  BuildGemma4DecodeSource::BuildLayer18(ctx);
  BuildGemma4DecodeSource::BuildLayer19(ctx);
  BuildGemma4DecodeSource::BuildLayer20(ctx);
  BuildGemma4DecodeSource::BuildLayer21(ctx);
  BuildGemma4DecodeSource::BuildLayer22(ctx);
  BuildGemma4DecodeSource::BuildLayer23(ctx);
  BuildGemma4DecodeSource::BuildLayer24(ctx);
  BuildGemma4DecodeSource::BuildLayer25(ctx);
  BuildGemma4DecodeSource::BuildLayer26(ctx);
  BuildGemma4DecodeSource::BuildLayer27(ctx);
  BuildGemma4DecodeSource::BuildLayer28(ctx);
  BuildGemma4DecodeSource::BuildLayer29(ctx);
  BuildGemma4DecodeSource::BuildLayer30(ctx);
  BuildGemma4DecodeSource::BuildLayer31(ctx);
  BuildGemma4DecodeSource::BuildLayer32(ctx);
  BuildGemma4DecodeSource::BuildLayer33(ctx);
  BuildGemma4DecodeSource::BuildLayer34(ctx);
  BuildGemma4DecodeSource::BuildFinalNormAndHead(ctx);
  return g;
}
