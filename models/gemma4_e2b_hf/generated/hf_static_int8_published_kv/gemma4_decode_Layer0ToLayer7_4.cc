// Generated YNNPACK builder; do not edit.
#include "gemma4_decode_builder.h"

namespace BuildGemma4DecodeSource {

// Scope: "Layer0 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer0AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(1841, 1952, 0.6088034510612488, 0);
  g->Transpose(6500, 4700, {1,0});
  g->Binary(ynn_binary_multiply, 4697, 4699, 4695);
  g->Dot(1952, 4700, YNN_INVALID_VALUE_ID, 4694, 1);
  g->DequantizeTensor(4694, YNN_INVALID_VALUE_ID, 4695, 4696);
  g->QuantizeTensor(4696, 6412, 4698, 2063);
  g->Dequantize(2063, 2174, 1.535433053970337, 0);
  g->Reshape(2174, 2284, {1,1,1,256});
  g->Reshape(2284, 2391, {1,1,1,256});
  g->Unary(ynn_unary_square, 2391, 2502);
  g->Reduce(ynn_reduce_sum, 2502, 6146, {3}, true);
  g->ShapeProduct(2502, 6145, {3});
  g->Binary(ynn_binary_divide, 6146, 6145, 2613);
  g->Binary(ynn_binary_add, 2613, 6446, 2725);
  g->Binary(ynn_binary_pow, 2725, 6448, 2836);
  g->Binary(ynn_binary_multiply, 2391, 2836, 2945);
  g->Convert(6499, 3028);
  g->Binary(ynn_binary_multiply, 2945, 3028, 3039);
  g->Slice(3039, 3051, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3039, 3062, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3062, 3073);
  g->Concat({3073,3051}, 3084, 3);
  g->Binary(ynn_binary_multiply, 3039, 2173, 3094);
  g->Binary(ynn_binary_multiply, 3084, 3050, 3100);
  g->Binary(ynn_binary_add, 3094, 3100, 3112);
  g->Transpose(6504, 5234, {1,0});
  g->Binary(ynn_binary_multiply, 4697, 5233, 5231);
  g->Dot(1952, 5234, YNN_INVALID_VALUE_ID, 5230, 1);
  g->DequantizeTensor(5230, YNN_INVALID_VALUE_ID, 5231, 5232);
  g->QuantizeTensor(5232, 6412, 4698, 3133);
  g->Dequantize(3133, 3144, 1.535433053970337, 0);
  g->Reshape(3144, 3155, {1,1,1,256});
  g->Reshape(3155, 3166, {1,1,1,256});
  g->Unary(ynn_unary_square, 3166, 3177);
  g->Reduce(ynn_reduce_sum, 3177, 6298, {3}, true);
  g->ShapeProduct(3177, 6297, {3});
  g->Binary(ynn_binary_divide, 6298, 6297, 3188);
  g->Binary(ynn_binary_add, 3188, 6446, 3199);
  g->Binary(ynn_binary_pow, 3199, 6448, 3210);
  g->Binary(ynn_binary_multiply, 3166, 3210, 3220);
}

// Scope: "Layer0 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer0AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(3112, 3231, 0.005997600965201855, 0);
  g->Append(6413, 3231, 7062, 2, s2, slinky::expr(int64_t{1}));
  g->View(7062, 7092, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7092, 3258, 0.005997600965201855, 0);
  g->Quantize(3220, 3270, 0.047244105488061905, 0);
  g->Append(6428, 3270, 7077, 2, s2, slinky::expr(int64_t{1}));
  g->View(7077, 7107, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7107, 3300, 0.047244105488061905, 0);
}

// Scope: "Layer0 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer0AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(6503, 5326, {1,0});
  g->Binary(ynn_binary_multiply, 4697, 5325, 5322);
  g->Dot(1952, 5326, YNN_INVALID_VALUE_ID, 5321, 1);
  g->DequantizeTensor(5321, YNN_INVALID_VALUE_ID, 5322, 5323);
  g->QuantizeTensor(5323, 6412, 5324, 3321);
  g->Dequantize(3321, 3332, 3.118110179901123, 0);
  g->SplitDim(3332, 3343, 2, {8,256});
  g->FuseDims(3343, 3354, 1, 2);
  g->SplitDim(3354, 3353, 1, {8,1});
  g->Unary(ynn_unary_square, 3353, 3364);
  g->Reduce(ynn_reduce_sum, 3364, 6335, {3}, true);
  g->ShapeProduct(3364, 6334, {3});
  g->Binary(ynn_binary_divide, 6335, 6334, 3373);
  g->Binary(ynn_binary_add, 3373, 6446, 3384);
  g->Binary(ynn_binary_pow, 3384, 6448, 3395);
  g->Binary(ynn_binary_multiply, 3353, 3395, 3406);
  g->Convert(6502, 3417);
  g->Binary(ynn_binary_multiply, 3406, 3417, 3427);
  g->Slice(3427, 3438, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3427, 3449, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3449, 3460);
  g->Concat({3460,3438}, 3472, 3);
  g->Binary(ynn_binary_multiply, 3427, 2173, 3483);
  g->Binary(ynn_binary_multiply, 3472, 3050, 3493);
  g->Binary(ynn_binary_add, 3483, 3493, 3502);
}

// Scope: "Layer0 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer0AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(3502, 3258, 3511, false, true);
  g->Mask(3511, 6453, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6453, 6375, {-1}, true);
  g->Binary(ynn_binary_subtract, 6453, 6375, 6372);
  g->Unary(ynn_unary_exp, 6372, 6373);
  g->Reduce(ynn_reduce_sum, 6373, 6376, {-1}, true);
  g->Binary(ynn_binary_divide, 5474, 6376, 6374);
  g->Binary(ynn_binary_multiply, 6373, 6374, 3532);
  g->Matmul(3532, 3300, 3543, false, false);
}

// Scope: "Layer0 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer0AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(3543, 3554, 1, 2);
  g->SplitDim(3554, 3553, 1, {1,8});
  g->FuseDims(3553, 3565, 2, 2);
  g->Quantize(3565, 3577, 0.03026575781404972, 0);
  g->Transpose(6501, 5445, {1,0});
  g->Binary(ynn_binary_multiply, 5442, 5444, 5440);
  g->Dot(3577, 5445, YNN_INVALID_VALUE_ID, 5439, 1);
  g->DequantizeTensor(5439, YNN_INVALID_VALUE_ID, 5440, 5441);
  g->QuantizeTensor(5441, 6412, 5443, 3588);
  g->Dequantize(3588, 3599, 0.21056734025478363, 0);
}

// Scope: "Layer0 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer0Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 6443, 1175);
  g->Reduce(ynn_reduce_sum, 1175, 5791, {2}, true);
  g->ShapeProduct(1175, 5790, {2});
  g->Binary(ynn_binary_divide, 5791, 5790, 1286);
  g->Binary(ynn_binary_add, 1286, 6446, 1397);
  g->Binary(ynn_binary_pow, 1397, 6448, 1507);
  g->Binary(ynn_binary_multiply, 6443, 1507, 1619);
  g->Convert(6488, 1730);
  g->Binary(ynn_binary_multiply, 1619, 1730, 1841);
  BuildLayer0AttentionKvProjection(ctx);
  BuildLayer0AttentionCacheUpdate(ctx);
  BuildLayer0AttentionQueryProjection(ctx);
  BuildLayer0AttentionSdpa(ctx);
  BuildLayer0AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 3599, 3610);
  g->Reduce(ynn_reduce_sum, 3610, 6398, {2}, true);
  g->ShapeProduct(3610, 6397, {2});
  g->Binary(ynn_binary_divide, 6398, 6397, 3621);
  g->Binary(ynn_binary_add, 3621, 6446, 3631);
  g->Binary(ynn_binary_pow, 3631, 6448, 3638);
  g->Binary(ynn_binary_multiply, 3599, 3638, 3649);
  g->Convert(6495, 3660);
  g->Binary(ynn_binary_multiply, 3649, 3660, 3671);
  g->Binary(ynn_binary_add, 6443, 3671, 3);
}

// Scope: "Layer0 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer0Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3, 13);
  g->Reduce(ynn_reduce_sum, 13, 5480, {2}, true);
  g->ShapeProduct(13, 5479, {2});
  g->Binary(ynn_binary_divide, 5480, 5479, 24);
  g->Binary(ynn_binary_add, 24, 6446, 35);
  g->Binary(ynn_binary_pow, 35, 6448, 46);
  g->Binary(ynn_binary_multiply, 3, 46, 57);
  g->Convert(6498, 68);
  g->Binary(ynn_binary_multiply, 57, 68, 79);
  g->Quantize(79, 89, 0.9406865835189819, 0);
  g->Transpose(6492, 3733, {1,0});
  g->Binary(ynn_binary_multiply, 3730, 3732, 3728);
  g->Dot(89, 3733, YNN_INVALID_VALUE_ID, 3727, 1);
  g->DequantizeTensor(3727, YNN_INVALID_VALUE_ID, 3728, 3729);
  g->QuantizeTensor(3729, 6412, 3731, 95);
  g->Dequantize(95, 108, 0.6181102395057678, 0);
  g->Transpose(6491, 3751, {1,0});
  g->Binary(ynn_binary_multiply, 3730, 3750, 3748);
  g->Dot(89, 3751, YNN_INVALID_VALUE_ID, 3747, 1);
  g->DequantizeTensor(3747, YNN_INVALID_VALUE_ID, 3748, 3749);
  g->QuantizeTensor(3749, 6412, 3731, 129);
  g->Dequantize(129, 140, 0.6181102395057678, 0);
  g->Polynomial(140, 5510, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5510, 5511);
  g->Binary(ynn_binary_add, 5511, 5474, 5508);
  g->Binary(ynn_binary_multiply, 140, 5472, 5509);
  g->Binary(ynn_binary_multiply, 5509, 5508, 150);
  g->Binary(ynn_binary_multiply, 108, 150, 161);
  g->Quantize(161, 172, 27.842519760131836, 0);
  g->Transpose(6490, 3791, {1,0});
  g->Binary(ynn_binary_multiply, 3788, 3790, 3786);
  g->Dot(172, 3791, YNN_INVALID_VALUE_ID, 3785, 1);
  g->DequantizeTensor(3785, YNN_INVALID_VALUE_ID, 3786, 3787);
  g->QuantizeTensor(3787, 6412, 3789, 183);
  g->Dequantize(183, 194, 16.64207649230957, 0);
  g->Unary(ynn_unary_square, 194, 205);
  g->Reduce(ynn_reduce_sum, 205, 5525, {2}, true);
  g->ShapeProduct(205, 5524, {2});
  g->Binary(ynn_binary_divide, 5525, 5524, 216);
  g->Binary(ynn_binary_add, 216, 6446, 227);
  g->Binary(ynn_binary_pow, 227, 6448, 233);
  g->Binary(ynn_binary_multiply, 194, 233, 245);
  g->Convert(6496, 255);
  g->Binary(ynn_binary_multiply, 245, 255, 267);
  g->Binary(ynn_binary_add, 3, 267, 278);
}

// Scope: "Layer0 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer0PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1064, 288, {0,0,0,0}, {-1,-1,1,-1});
  g->Reshape(288, 299, {1,1,256});
  g->Binary(ynn_binary_add, 299, 7026, 310);
  g->Binary(ynn_binary_multiply, 310, 6444, 322);
  g->Quantize(278, 333, 3.334678888320923, 0);
  g->Transpose(6493, 3863, {1,0});
  g->Binary(ynn_binary_multiply, 3860, 3862, 3858);
  g->Dot(333, 3863, YNN_INVALID_VALUE_ID, 3857, 1);
  g->DequantizeTensor(3857, YNN_INVALID_VALUE_ID, 3858, 3859);
  g->QuantizeTensor(3859, 6412, 3861, 344);
  g->Dequantize(344, 354, 0.01857776567339897, 0);
  g->Polynomial(354, 5559, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5559, 5560);
  g->Binary(ynn_binary_add, 5560, 5474, 5557);
  g->Binary(ynn_binary_multiply, 354, 5472, 5558);
  g->Binary(ynn_binary_multiply, 5558, 5557, 363);
  g->Binary(ynn_binary_multiply, 363, 322, 372);
  g->Quantize(372, 383, 0.03764764964580536, 0);
  g->Transpose(6494, 3881, {1,0});
  g->Binary(ynn_binary_multiply, 3878, 3880, 3876);
  g->Dot(383, 3881, YNN_INVALID_VALUE_ID, 3875, 1);
  g->DequantizeTensor(3875, YNN_INVALID_VALUE_ID, 3876, 3877);
  g->QuantizeTensor(3877, 6412, 3879, 394);
  g->Dequantize(394, 405, 0.03129800781607628, 0);
  g->Unary(ynn_unary_square, 405, 416);
  g->Reduce(ynn_reduce_sum, 416, 5577, {2}, true);
  g->ShapeProduct(416, 5576, {2});
  g->Binary(ynn_binary_divide, 5577, 5576, 427);
  g->Binary(ynn_binary_add, 427, 6446, 438);
  g->Binary(ynn_binary_pow, 438, 6448, 449);
  g->Binary(ynn_binary_multiply, 405, 449, 460);
  g->Convert(6497, 471);
  g->Binary(ynn_binary_multiply, 460, 471, 482);
  g->Binary(ynn_binary_add, 278, 482, 492);
  g->Convert(6489, 501);
  g->Binary(ynn_binary_multiply, 492, 501, 510);
}

// Scope: "Layer0"
LAB_YNN_BUILDER_NOINLINE void BuildLayer0(Context& ctx) {
  BuildLayer0Attention(ctx);
  BuildLayer0Mlp(ctx);
  BuildLayer0PerLayerEmbedding(ctx);
}

// Scope: "Layer1 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(587, 598, 0.4842597544193268, 0);
  g->Transpose(6517, 3993, {1,0});
  g->Binary(ynn_binary_multiply, 3990, 3992, 3988);
  g->Dot(598, 3993, YNN_INVALID_VALUE_ID, 3987, 1);
  g->DequantizeTensor(3987, YNN_INVALID_VALUE_ID, 3988, 3989);
  g->QuantizeTensor(3989, 6412, 3991, 609);
  g->Dequantize(609, 620, 0.41535434126853943, 0);
  g->Reshape(620, 630, {1,1,1,256});
  g->Reshape(630, 638, {1,1,1,256});
  g->Unary(ynn_unary_square, 638, 649);
  g->Reduce(ynn_reduce_sum, 649, 5628, {3}, true);
  g->ShapeProduct(649, 5627, {3});
  g->Binary(ynn_binary_divide, 5628, 5627, 660);
  g->Binary(ynn_binary_add, 660, 6446, 671);
  g->Binary(ynn_binary_pow, 671, 6448, 682);
  g->Binary(ynn_binary_multiply, 638, 682, 692);
  g->Convert(6516, 703);
  g->Binary(ynn_binary_multiply, 692, 703, 714);
  g->Slice(714, 725, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(714, 736, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 736, 748);
  g->Concat({748,725}, 759, 3);
  g->Binary(ynn_binary_multiply, 714, 2173, 769);
  g->Binary(ynn_binary_multiply, 759, 3050, 775);
  g->Binary(ynn_binary_add, 769, 775, 787);
  g->Transpose(6521, 4072, {1,0});
  g->Binary(ynn_binary_multiply, 3990, 4071, 4069);
  g->Dot(598, 4072, YNN_INVALID_VALUE_ID, 4068, 1);
  g->DequantizeTensor(4068, YNN_INVALID_VALUE_ID, 4069, 4070);
  g->QuantizeTensor(4070, 6412, 3991, 808);
  g->Dequantize(808, 819, 0.41535434126853943, 0);
  g->Reshape(819, 829, {1,1,1,256});
  g->Reshape(829, 840, {1,1,1,256});
  g->Unary(ynn_unary_square, 840, 852);
  g->Reduce(ynn_reduce_sum, 852, 5680, {3}, true);
  g->ShapeProduct(852, 5679, {3});
  g->Binary(ynn_binary_divide, 5680, 5679, 863);
  g->Binary(ynn_binary_add, 863, 6446, 874);
  g->Binary(ynn_binary_pow, 874, 6448, 885);
  g->Binary(ynn_binary_multiply, 840, 885, 895);
}

// Scope: "Layer1 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(787, 906, 0.005761673673987389, 0);
  g->Append(6414, 906, 7063, 2, s2, slinky::expr(int64_t{1}));
  g->View(7063, 7093, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7093, 932, 0.005761673673987389, 0);
  g->Quantize(895, 944, 0.047244105488061905, 0);
  g->Append(6429, 944, 7078, 2, s2, slinky::expr(int64_t{1}));
  g->View(7078, 7108, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7108, 975, 0.047244105488061905, 0);
}

// Scope: "Layer1 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(6520, 4168, {1,0});
  g->Binary(ynn_binary_multiply, 3990, 4167, 4164);
  g->Dot(598, 4168, YNN_INVALID_VALUE_ID, 4163, 1);
  g->DequantizeTensor(4163, YNN_INVALID_VALUE_ID, 4164, 4165);
  g->QuantizeTensor(4165, 6412, 4166, 996);
  g->Dequantize(996, 1007, 0.35039371252059937, 0);
  g->SplitDim(1007, 1019, 2, {8,256});
  g->FuseDims(1019, 1030, 1, 2);
  g->SplitDim(1030, 1029, 1, {8,1});
  g->Unary(ynn_unary_square, 1029, 1042);
  g->Reduce(ynn_reduce_sum, 1042, 5724, {3}, true);
  g->ShapeProduct(1042, 5723, {3});
  g->Binary(ynn_binary_divide, 5724, 5723, 1053);
  g->Binary(ynn_binary_add, 1053, 6446, 1065);
  g->Binary(ynn_binary_pow, 1065, 6448, 1076);
  g->Binary(ynn_binary_multiply, 1029, 1076, 1087);
  g->Convert(6519, 1098);
  g->Binary(ynn_binary_multiply, 1087, 1098, 1109);
  g->Slice(1109, 1121, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1109, 1131, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1131, 1143);
  g->Concat({1143,1121}, 1154, 3);
  g->Binary(ynn_binary_multiply, 1109, 2173, 1164);
  g->Binary(ynn_binary_multiply, 1154, 3050, 1176);
  g->Binary(ynn_binary_add, 1164, 1176, 1187);
}

// Scope: "Layer1 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(1187, 932, 1198, false, true);
  g->Mask(1198, 6454, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6454, 5769, {-1}, true);
  g->Binary(ynn_binary_subtract, 6454, 5769, 5766);
  g->Unary(ynn_unary_exp, 5766, 5767);
  g->Reduce(ynn_reduce_sum, 5767, 5770, {-1}, true);
  g->Binary(ynn_binary_divide, 5474, 5770, 5768);
  g->Binary(ynn_binary_multiply, 5767, 5768, 1220);
  g->Matmul(1220, 975, 1231, false, false);
}

// Scope: "Layer1 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(1231, 1243, 1, 2);
  g->SplitDim(1243, 1242, 1, {1,8});
  g->FuseDims(1242, 1254, 2, 2);
  g->Quantize(1254, 1264, 0.023129930719733238, 0);
  g->Transpose(6518, 4302, {1,0});
  g->Binary(ynn_binary_multiply, 4299, 4301, 4297);
  g->Dot(1264, 4302, YNN_INVALID_VALUE_ID, 4296, 1);
  g->DequantizeTensor(4296, YNN_INVALID_VALUE_ID, 4297, 4298);
  g->QuantizeTensor(4298, 6412, 4300, 1275);
  g->Dequantize(1275, 1287, 0.03322756290435791, 0);
}

// Scope: "Layer1 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 510, 521);
  g->Reduce(ynn_reduce_sum, 521, 5602, {2}, true);
  g->ShapeProduct(521, 5601, {2});
  g->Binary(ynn_binary_divide, 5602, 5601, 533);
  g->Binary(ynn_binary_add, 533, 6446, 544);
  g->Binary(ynn_binary_pow, 544, 6448, 554);
  g->Binary(ynn_binary_multiply, 510, 554, 565);
  g->Convert(6505, 576);
  g->Binary(ynn_binary_multiply, 565, 576, 587);
  BuildLayer1AttentionKvProjection(ctx);
  BuildLayer1AttentionCacheUpdate(ctx);
  BuildLayer1AttentionQueryProjection(ctx);
  BuildLayer1AttentionSdpa(ctx);
  BuildLayer1AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1287, 1298);
  g->Reduce(ynn_reduce_sum, 1298, 5797, {2}, true);
  g->ShapeProduct(1298, 5796, {2});
  g->Binary(ynn_binary_divide, 5797, 5796, 1309);
  g->Binary(ynn_binary_add, 1309, 6446, 1321);
  g->Binary(ynn_binary_pow, 1321, 6448, 1332);
  g->Binary(ynn_binary_multiply, 1287, 1332, 1343);
  g->Convert(6512, 1354);
  g->Binary(ynn_binary_multiply, 1343, 1354, 1364);
  g->Binary(ynn_binary_add, 510, 1364, 1375);
}

// Scope: "Layer1 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1375, 1386);
  g->Reduce(ynn_reduce_sum, 1386, 5822, {2}, true);
  g->ShapeProduct(1386, 5821, {2});
  g->Binary(ynn_binary_divide, 5822, 5821, 1398);
  g->Binary(ynn_binary_add, 1398, 6446, 1409);
  g->Binary(ynn_binary_pow, 1409, 6448, 1421);
  g->Binary(ynn_binary_multiply, 1375, 1421, 1432);
  g->Convert(6515, 1443);
  g->Binary(ynn_binary_multiply, 1432, 1443, 1454);
  g->Quantize(1454, 1464, 0.08275254815816879, 0);
  g->Transpose(6509, 4403, {1,0});
  g->Binary(ynn_binary_multiply, 4400, 4402, 4398);
  g->Dot(1464, 4403, YNN_INVALID_VALUE_ID, 4397, 1);
  g->DequantizeTensor(4397, YNN_INVALID_VALUE_ID, 4398, 4399);
  g->QuantizeTensor(4399, 6412, 4401, 1475);
  g->Dequantize(1475, 1486, 0.06889764219522476, 0);
  g->Transpose(6508, 4421, {1,0});
  g->Binary(ynn_binary_multiply, 4400, 4420, 4418);
  g->Dot(1464, 4421, YNN_INVALID_VALUE_ID, 4417, 1);
  g->DequantizeTensor(4417, YNN_INVALID_VALUE_ID, 4418, 4419);
  g->QuantizeTensor(4419, 6412, 4401, 1508);
  g->Dequantize(1508, 1520, 0.06889764219522476, 0);
  g->Polynomial(1520, 5854, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5854, 5855);
  g->Binary(ynn_binary_add, 5855, 5474, 5852);
  g->Binary(ynn_binary_multiply, 1520, 5472, 5853);
  g->Binary(ynn_binary_multiply, 5853, 5852, 1531);
  g->Binary(ynn_binary_multiply, 1486, 1531, 1542);
  g->Quantize(1542, 1553, 0.21062994003295898, 0);
  g->Transpose(6507, 4448, {1,0});
  g->Binary(ynn_binary_multiply, 4445, 4447, 4443);
  g->Dot(1553, 4448, YNN_INVALID_VALUE_ID, 4442, 1);
  g->DequantizeTensor(4442, YNN_INVALID_VALUE_ID, 4443, 4444);
  g->QuantizeTensor(4444, 6412, 4446, 1563);
  g->Dequantize(1563, 1574, 0.09257561713457108, 0);
  g->Unary(ynn_unary_square, 1574, 1585);
  g->Reduce(ynn_reduce_sum, 1585, 5878, {2}, true);
  g->ShapeProduct(1585, 5877, {2});
  g->Binary(ynn_binary_divide, 5878, 5877, 1596);
  g->Binary(ynn_binary_add, 1596, 6446, 1607);
  g->Binary(ynn_binary_pow, 1607, 6448, 1620);
  g->Binary(ynn_binary_multiply, 1574, 1620, 1631);
  g->Convert(6513, 1642);
  g->Binary(ynn_binary_multiply, 1631, 1642, 1653);
  g->Binary(ynn_binary_add, 1375, 1653, 1664);
}

// Scope: "Layer1 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1064, 1674, {0,0,1,0}, {-1,-1,1,-1});
  g->Reshape(1674, 1685, {1,1,256});
  g->Binary(ynn_binary_add, 1685, 7027, 1696);
  g->Binary(ynn_binary_multiply, 1696, 6444, 1707);
  g->Quantize(1664, 1719, 0.4206320643424988, 0);
  g->Transpose(6510, 4534, {1,0});
  g->Binary(ynn_binary_multiply, 4531, 4533, 4529);
  g->Dot(1719, 4534, YNN_INVALID_VALUE_ID, 4528, 1);
  g->DequantizeTensor(4528, YNN_INVALID_VALUE_ID, 4529, 4530);
  g->QuantizeTensor(4530, 6412, 4532, 1731);
  g->Dequantize(1731, 1742, 0.010150108486413956, 0);
  g->Polynomial(1742, 5917, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5917, 5918);
  g->Binary(ynn_binary_add, 5918, 5474, 5915);
  g->Binary(ynn_binary_multiply, 1742, 5472, 5916);
  g->Binary(ynn_binary_multiply, 5916, 5915, 1753);
  g->Binary(ynn_binary_multiply, 1753, 1707, 1764);
  g->Quantize(1764, 1774, 0.026820875704288483, 0);
  g->Transpose(6511, 4567, {1,0});
  g->Binary(ynn_binary_multiply, 4564, 4566, 4562);
  g->Dot(1774, 4567, YNN_INVALID_VALUE_ID, 4561, 1);
  g->DequantizeTensor(4561, YNN_INVALID_VALUE_ID, 4562, 4563);
  g->QuantizeTensor(4563, 6412, 4565, 1785);
  g->Dequantize(1785, 1796, 0.020895034074783325, 0);
  g->Unary(ynn_unary_square, 1796, 1807);
  g->Reduce(ynn_reduce_sum, 1807, 5936, {2}, true);
  g->ShapeProduct(1807, 5935, {2});
  g->Binary(ynn_binary_divide, 5936, 5935, 1818);
  g->Binary(ynn_binary_add, 1818, 6446, 1830);
  g->Binary(ynn_binary_pow, 1830, 6448, 1842);
  g->Binary(ynn_binary_multiply, 1796, 1842, 1853);
  g->Convert(6514, 1864);
  g->Binary(ynn_binary_multiply, 1853, 1864, 1874);
  g->Binary(ynn_binary_add, 1664, 1874, 1885);
  g->Convert(6506, 1896);
  g->Binary(ynn_binary_multiply, 1885, 1896, 1907);
}

// Scope: "Layer1"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1(Context& ctx) {
  BuildLayer1Attention(ctx);
  BuildLayer1Mlp(ctx);
  BuildLayer1PerLayerEmbedding(ctx);
}

// Scope: "Layer2 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(1985, 1996, 0.15746013820171356, 0);
  g->Transpose(6689, 4680, {1,0});
  g->Binary(ynn_binary_multiply, 4677, 4679, 4675);
  g->Dot(1996, 4680, YNN_INVALID_VALUE_ID, 4674, 1);
  g->DequantizeTensor(4674, YNN_INVALID_VALUE_ID, 4675, 4676);
  g->QuantizeTensor(4676, 6412, 4678, 2007);
  g->Dequantize(2007, 2018, 0.180118128657341, 0);
  g->Reshape(2018, 2030, {1,1,1,256});
  g->Reshape(2030, 2040, {1,1,1,256});
  g->Unary(ynn_unary_square, 2040, 2052);
  g->Reduce(ynn_reduce_sum, 2052, 6001, {3}, true);
  g->ShapeProduct(2052, 6000, {3});
  g->Binary(ynn_binary_divide, 6001, 6000, 2064);
  g->Binary(ynn_binary_add, 2064, 6446, 2074);
  g->Binary(ynn_binary_pow, 2074, 6448, 2085);
  g->Binary(ynn_binary_multiply, 2040, 2085, 2096);
  g->Convert(6688, 2107);
  g->Binary(ynn_binary_multiply, 2096, 2107, 2118);
  g->Slice(2118, 2130, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2118, 2140, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2140, 2152);
  g->Concat({2152,2130}, 2163, 3);
  g->Binary(ynn_binary_multiply, 2118, 2173, 2175);
  g->Binary(ynn_binary_multiply, 2163, 3050, 2186);
  g->Binary(ynn_binary_add, 2175, 2186, 2197);
  g->Transpose(6693, 4783, {1,0});
  g->Binary(ynn_binary_multiply, 4677, 4782, 4780);
  g->Dot(1996, 4783, YNN_INVALID_VALUE_ID, 4779, 1);
  g->DequantizeTensor(4779, YNN_INVALID_VALUE_ID, 4780, 4781);
  g->QuantizeTensor(4781, 6412, 4678, 2218);
  g->Dequantize(2218, 2230, 0.180118128657341, 0);
  g->Reshape(2230, 2241, {1,1,1,256});
  g->Reshape(2241, 2252, {1,1,1,256});
  g->Unary(ynn_unary_square, 2252, 2263);
  g->Reduce(ynn_reduce_sum, 2263, 6057, {3}, true);
  g->ShapeProduct(2263, 6056, {3});
  g->Binary(ynn_binary_divide, 6057, 6056, 2273);
  g->Binary(ynn_binary_add, 2273, 6446, 2285);
  g->Binary(ynn_binary_pow, 2285, 6448, 2296);
  g->Binary(ynn_binary_multiply, 2252, 2296, 2307);
}

// Scope: "Layer2 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(2197, 2318, 0.005684707313776016, 0);
  g->Append(6420, 2318, 7069, 2, s2, slinky::expr(int64_t{1}));
  g->View(7069, 7099, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7099, 2350, 0.005684707313776016, 0);
  g->Quantize(2307, 2361, 0.047244105488061905, 0);
  g->Append(6435, 2361, 7084, 2, s2, slinky::expr(int64_t{1}));
  g->View(7084, 7114, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7114, 2392, 0.047244105488061905, 0);
}

// Scope: "Layer2 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(6692, 4882, {1,0});
  g->Binary(ynn_binary_multiply, 4677, 4881, 4878);
  g->Dot(1996, 4882, YNN_INVALID_VALUE_ID, 4877, 1);
  g->DequantizeTensor(4877, YNN_INVALID_VALUE_ID, 4878, 4879);
  g->QuantizeTensor(4879, 6412, 4880, 2413);
  g->Dequantize(2413, 2425, 0.1643700897693634, 0);
  g->SplitDim(2425, 2436, 2, {8,256});
  g->FuseDims(2436, 2448, 1, 2);
  g->SplitDim(2448, 2447, 1, {8,1});
  g->Unary(ynn_unary_square, 2447, 2459);
  g->Reduce(ynn_reduce_sum, 2459, 6105, {3}, true);
  g->ShapeProduct(2459, 6104, {3});
  g->Binary(ynn_binary_divide, 6105, 6104, 2469);
  g->Binary(ynn_binary_add, 2469, 6446, 2480);
  g->Binary(ynn_binary_pow, 2480, 6448, 2491);
  g->Binary(ynn_binary_multiply, 2447, 2491, 2503);
  g->Convert(6691, 2514);
  g->Binary(ynn_binary_multiply, 2503, 2514, 2526);
  g->Slice(2526, 2537, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2526, 2548, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2548, 2559);
  g->Concat({2559,2537}, 2569, 3);
  g->Binary(ynn_binary_multiply, 2526, 2173, 2580);
  g->Binary(ynn_binary_multiply, 2569, 3050, 2591);
  g->Binary(ynn_binary_add, 2580, 2591, 2602);
}

// Scope: "Layer2 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(2602, 2350, 2614, false, true);
  g->Mask(2614, 6465, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6465, 6152, {-1}, true);
  g->Binary(ynn_binary_subtract, 6465, 6152, 6149);
  g->Unary(ynn_unary_exp, 6149, 6150);
  g->Reduce(ynn_reduce_sum, 6150, 6153, {-1}, true);
  g->Binary(ynn_binary_divide, 5474, 6153, 6151);
  g->Binary(ynn_binary_multiply, 6150, 6151, 2636);
  g->Matmul(2636, 2392, 2647, false, false);
}

// Scope: "Layer2 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(2647, 2659, 1, 2);
  g->SplitDim(2659, 2658, 1, {1,8});
  g->FuseDims(2658, 2670, 2, 2);
  g->Quantize(2670, 2680, 0.0216535534709692, 0);
  g->Transpose(6690, 5012, {1,0});
  g->Binary(ynn_binary_multiply, 5009, 5011, 5007);
  g->Dot(2680, 5012, YNN_INVALID_VALUE_ID, 5006, 1);
  g->DequantizeTensor(5006, YNN_INVALID_VALUE_ID, 5007, 5008);
  g->QuantizeTensor(5008, 6412, 5010, 2691);
  g->Dequantize(2691, 2702, 0.03426840156316757, 0);
}

// Scope: "Layer2 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1907, 1918);
  g->Reduce(ynn_reduce_sum, 1918, 5965, {2}, true);
  g->ShapeProduct(1918, 5964, {2});
  g->Binary(ynn_binary_divide, 5965, 5964, 1930);
  g->Binary(ynn_binary_add, 1930, 6446, 1940);
  g->Binary(ynn_binary_pow, 1940, 6448, 1953);
  g->Binary(ynn_binary_multiply, 1907, 1953, 1964);
  g->Convert(6677, 1974);
  g->Binary(ynn_binary_multiply, 1964, 1974, 1985);
  BuildLayer2AttentionKvProjection(ctx);
  BuildLayer2AttentionCacheUpdate(ctx);
  BuildLayer2AttentionQueryProjection(ctx);
  BuildLayer2AttentionSdpa(ctx);
  BuildLayer2AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2702, 2713);
  g->Reduce(ynn_reduce_sum, 2713, 6178, {2}, true);
  g->ShapeProduct(2713, 6177, {2});
  g->Binary(ynn_binary_divide, 6178, 6177, 2726);
  g->Binary(ynn_binary_add, 2726, 6446, 2737);
  g->Binary(ynn_binary_pow, 2737, 6448, 2748);
  g->Binary(ynn_binary_multiply, 2702, 2748, 2759);
  g->Convert(6684, 2770);
  g->Binary(ynn_binary_multiply, 2759, 2770, 2780);
  g->Binary(ynn_binary_add, 1907, 2780, 2791);
}

// Scope: "Layer2 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2791, 2802);
  g->Reduce(ynn_reduce_sum, 2802, 6203, {2}, true);
  g->ShapeProduct(2802, 6202, {2});
  g->Binary(ynn_binary_divide, 6203, 6202, 2813);
  g->Binary(ynn_binary_add, 2813, 6446, 2824);
  g->Binary(ynn_binary_pow, 2824, 6448, 2837);
  g->Binary(ynn_binary_multiply, 2791, 2837, 2848);
  g->Convert(6687, 2859);
  g->Binary(ynn_binary_multiply, 2848, 2859, 2870);
  g->Quantize(2870, 2880, 0.04049227386713028, 0);
  g->Transpose(6681, 5107, {1,0});
  g->Binary(ynn_binary_multiply, 5104, 5106, 5102);
  g->Dot(2880, 5107, YNN_INVALID_VALUE_ID, 5101, 1);
  g->DequantizeTensor(5101, YNN_INVALID_VALUE_ID, 5102, 5103);
  g->QuantizeTensor(5103, 6412, 5105, 2891);
  g->Dequantize(2891, 2902, 0.04183071851730347, 0);
  g->Transpose(6680, 5133, {1,0});
  g->Binary(ynn_binary_multiply, 5104, 5132, 5130);
  g->Dot(2880, 5133, YNN_INVALID_VALUE_ID, 5129, 1);
  g->DequantizeTensor(5129, YNN_INVALID_VALUE_ID, 5130, 5131);
  g->QuantizeTensor(5131, 6412, 5105, 2923);
  g->Dequantize(2923, 2935, 0.04183071851730347, 0);
  g->Polynomial(2935, 6240, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6240, 6241);
  g->Binary(ynn_binary_add, 6241, 5474, 6238);
  g->Binary(ynn_binary_multiply, 2935, 5472, 6239);
  g->Binary(ynn_binary_multiply, 6239, 6238, 2946);
  g->Binary(ynn_binary_multiply, 2902, 2946, 2958);
  g->Quantize(2958, 2969, 0.09645669907331467, 0);
  g->Transpose(6679, 5166, {1,0});
  g->Binary(ynn_binary_multiply, 5163, 5165, 5161);
  g->Dot(2969, 5166, YNN_INVALID_VALUE_ID, 5160, 1);
  g->DequantizeTensor(5160, YNN_INVALID_VALUE_ID, 5161, 5162);
  g->QuantizeTensor(5162, 6412, 5164, 2979);
  g->Dequantize(2979, 2990, 0.05011765658855438, 0);
  g->Unary(ynn_unary_square, 2990, 3001);
  g->Reduce(ynn_reduce_sum, 3001, 6259, {2}, true);
  g->ShapeProduct(3001, 6258, {2});
  g->Binary(ynn_binary_divide, 6259, 6258, 3012);
  g->Binary(ynn_binary_add, 3012, 6446, 3023);
  g->Binary(ynn_binary_pow, 3023, 6448, 3026);
  g->Binary(ynn_binary_multiply, 2990, 3026, 3027);
  g->Convert(6685, 3029);
  g->Binary(ynn_binary_multiply, 3027, 3029, 3030);
  g->Binary(ynn_binary_add, 2791, 3030, 3031);
}

// Scope: "Layer2 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1064, 3032, {0,0,2,0}, {-1,-1,1,-1});
  g->Reshape(3032, 3033, {1,1,256});
  g->Binary(ynn_binary_add, 3033, 7038, 3034);
  g->Binary(ynn_binary_multiply, 3034, 6444, 3035);
  g->Quantize(3031, 3036, 0.045230474323034286, 0);
  g->Transpose(6682, 5198, {1,0});
  g->Binary(ynn_binary_multiply, 5195, 5197, 5193);
  g->Dot(3036, 5198, YNN_INVALID_VALUE_ID, 5192, 1);
  g->DequantizeTensor(5192, YNN_INVALID_VALUE_ID, 5193, 5194);
  g->QuantizeTensor(5194, 6412, 5196, 3037);
  g->Dequantize(3037, 3038, 0.017839577049016953, 0);
  g->Polynomial(3038, 6264, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6264, 6265);
  g->Binary(ynn_binary_add, 6265, 5474, 6262);
  g->Binary(ynn_binary_multiply, 3038, 5472, 6263);
  g->Binary(ynn_binary_multiply, 6263, 6262, 3040);
  g->Binary(ynn_binary_multiply, 3040, 3035, 3041);
  g->Quantize(3041, 3042, 0.05216536670923233, 0);
  g->Transpose(6683, 5205, {1,0});
  g->Binary(ynn_binary_multiply, 5202, 5204, 5200);
  g->Dot(3042, 5205, YNN_INVALID_VALUE_ID, 5199, 1);
  g->DequantizeTensor(5199, YNN_INVALID_VALUE_ID, 5200, 5201);
  g->QuantizeTensor(5201, 6412, 5203, 3043);
  g->Dequantize(3043, 3044, 0.021943029016256332, 0);
  g->Unary(ynn_unary_square, 3044, 3045);
  g->Reduce(ynn_reduce_sum, 3045, 6267, {2}, true);
  g->ShapeProduct(3045, 6266, {2});
  g->Binary(ynn_binary_divide, 6267, 6266, 3046);
  g->Binary(ynn_binary_add, 3046, 6446, 3047);
  g->Binary(ynn_binary_pow, 3047, 6448, 3048);
  g->Binary(ynn_binary_multiply, 3044, 3048, 3049);
  g->Convert(6686, 3052);
  g->Binary(ynn_binary_multiply, 3049, 3052, 3053);
  g->Binary(ynn_binary_add, 3031, 3053, 3054);
  g->Convert(6678, 3055);
  g->Binary(ynn_binary_multiply, 3054, 3055, 3056);
}

// Scope: "Layer2"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2(Context& ctx) {
  BuildLayer2Attention(ctx);
  BuildLayer2Mlp(ctx);
  BuildLayer2PerLayerEmbedding(ctx);
}

// Scope: "Layer3 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(3064, 3065, 0.12591414153575897, 0);
  g->Transpose(6846, 5211, {1,0});
  g->Binary(ynn_binary_multiply, 5209, 5210, 5207);
  g->Dot(3065, 5211, YNN_INVALID_VALUE_ID, 5206, 1);
  g->DequantizeTensor(5206, YNN_INVALID_VALUE_ID, 5207, 5208);
  g->QuantizeTensor(5208, 6412, 4664, 3066);
  g->Dequantize(3066, 3067, 0.08710630983114243, 0);
  g->Reshape(3067, 3068, {1,1,1,256});
  g->Reshape(3068, 3069, {1,1,1,256});
  g->Unary(ynn_unary_square, 3069, 3070);
  g->Reduce(ynn_reduce_sum, 3070, 6271, {3}, true);
  g->ShapeProduct(3070, 6270, {3});
  g->Binary(ynn_binary_divide, 6271, 6270, 3071);
  g->Binary(ynn_binary_add, 3071, 6446, 3072);
  g->Binary(ynn_binary_pow, 3072, 6448, 3074);
  g->Binary(ynn_binary_multiply, 3069, 3074, 3075);
  g->Convert(6845, 3076);
  g->Binary(ynn_binary_multiply, 3075, 3076, 3077);
  g->Slice(3077, 3078, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3077, 3079, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3079, 3080);
  g->Concat({3080,3078}, 3081, 3);
  g->Binary(ynn_binary_multiply, 3077, 2173, 3082);
  g->Binary(ynn_binary_multiply, 3081, 3050, 3083);
  g->Binary(ynn_binary_add, 3082, 3083, 3085);
  g->Transpose(6850, 5216, {1,0});
  g->Binary(ynn_binary_multiply, 5209, 5215, 5213);
  g->Dot(3065, 5216, YNN_INVALID_VALUE_ID, 5212, 1);
  g->DequantizeTensor(5212, YNN_INVALID_VALUE_ID, 5213, 5214);
  g->QuantizeTensor(5214, 6412, 4664, 3086);
  g->Dequantize(3086, 3087, 0.08710630983114243, 0);
  g->Reshape(3087, 3088, {1,1,1,256});
  g->Reshape(3088, 3089, {1,1,1,256});
  g->Unary(ynn_unary_square, 3089, 3090);
  g->Reduce(ynn_reduce_sum, 3090, 6273, {3}, true);
  g->ShapeProduct(3090, 6272, {3});
  g->Binary(ynn_binary_divide, 6273, 6272, 3091);
  g->Binary(ynn_binary_add, 3091, 6446, 3092);
  g->Binary(ynn_binary_pow, 3092, 6448, 3093);
  g->Binary(ynn_binary_multiply, 3089, 3093, 3095);
}

// Scope: "Layer3 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(3085, 3096, 0.00573749840259552, 0);
  g->Append(6421, 3096, 7070, 2, s2, slinky::expr(int64_t{1}));
  g->View(7070, 7100, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7100, 3097, 0.00573749840259552, 0);
  g->Quantize(3095, 3098, 0.047244105488061905, 0);
  g->Append(6436, 3098, 7085, 2, s2, slinky::expr(int64_t{1}));
  g->View(7085, 7115, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7115, 3099, 0.047244105488061905, 0);
}

// Scope: "Layer3 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(6849, 5222, {1,0});
  g->Binary(ynn_binary_multiply, 5209, 5221, 5218);
  g->Dot(3065, 5222, YNN_INVALID_VALUE_ID, 5217, 1);
  g->DequantizeTensor(5217, YNN_INVALID_VALUE_ID, 5218, 5219);
  g->QuantizeTensor(5219, 6412, 5220, 3101);
  g->Dequantize(3101, 3102, 0.15354332327842712, 0);
  g->SplitDim(3102, 3103, 2, {8,256});
  g->FuseDims(3103, 3105, 1, 2);
  g->SplitDim(3105, 3104, 1, {8,1});
  g->Unary(ynn_unary_square, 3104, 3106);
  g->Reduce(ynn_reduce_sum, 3106, 6275, {3}, true);
  g->ShapeProduct(3106, 6274, {3});
  g->Binary(ynn_binary_divide, 6275, 6274, 3107);
  g->Binary(ynn_binary_add, 3107, 6446, 3108);
  g->Binary(ynn_binary_pow, 3108, 6448, 3109);
  g->Binary(ynn_binary_multiply, 3104, 3109, 3110);
  g->Convert(6848, 3111);
  g->Binary(ynn_binary_multiply, 3110, 3111, 3113);
  g->Slice(3113, 3114, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3113, 3115, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3115, 3116);
  g->Concat({3116,3114}, 3117, 3);
  g->Binary(ynn_binary_multiply, 3113, 2173, 3118);
  g->Binary(ynn_binary_multiply, 3117, 3050, 3119);
  g->Binary(ynn_binary_add, 3118, 3119, 3120);
}

// Scope: "Layer3 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(3120, 3097, 3121, false, true);
  g->Mask(3121, 6476, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6476, 6279, {-1}, true);
  g->Binary(ynn_binary_subtract, 6476, 6279, 6276);
  g->Unary(ynn_unary_exp, 6276, 6277);
  g->Reduce(ynn_reduce_sum, 6277, 6280, {-1}, true);
  g->Binary(ynn_binary_divide, 5474, 6280, 6278);
  g->Binary(ynn_binary_multiply, 6277, 6278, 3122);
  g->Matmul(3122, 3099, 3123, false, false);
}

// Scope: "Layer3 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(3123, 3125, 1, 2);
  g->SplitDim(3125, 3124, 1, {1,8});
  g->FuseDims(3124, 3126, 2, 2);
  g->Quantize(3126, 3127, 0.02706693857908249, 0);
  g->Transpose(6847, 5229, {1,0});
  g->Binary(ynn_binary_multiply, 5226, 5228, 5224);
  g->Dot(3127, 5229, YNN_INVALID_VALUE_ID, 5223, 1);
  g->DequantizeTensor(5223, YNN_INVALID_VALUE_ID, 5224, 5225);
  g->QuantizeTensor(5225, 6412, 5227, 3128);
  g->Dequantize(3128, 3129, 0.07367152720689774, 0);
}

// Scope: "Layer3 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3056, 3057);
  g->Reduce(ynn_reduce_sum, 3057, 6269, {2}, true);
  g->ShapeProduct(3057, 6268, {2});
  g->Binary(ynn_binary_divide, 6269, 6268, 3058);
  g->Binary(ynn_binary_add, 3058, 6446, 3059);
  g->Binary(ynn_binary_pow, 3059, 6448, 3060);
  g->Binary(ynn_binary_multiply, 3056, 3060, 3061);
  g->Convert(6834, 3063);
  g->Binary(ynn_binary_multiply, 3061, 3063, 3064);
  BuildLayer3AttentionKvProjection(ctx);
  BuildLayer3AttentionCacheUpdate(ctx);
  BuildLayer3AttentionQueryProjection(ctx);
  BuildLayer3AttentionSdpa(ctx);
  BuildLayer3AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 3129, 3130);
  g->Reduce(ynn_reduce_sum, 3130, 6282, {2}, true);
  g->ShapeProduct(3130, 6281, {2});
  g->Binary(ynn_binary_divide, 6282, 6281, 3131);
  g->Binary(ynn_binary_add, 3131, 6446, 3132);
  g->Binary(ynn_binary_pow, 3132, 6448, 3134);
  g->Binary(ynn_binary_multiply, 3129, 3134, 3135);
  g->Convert(6841, 3136);
  g->Binary(ynn_binary_multiply, 3135, 3136, 3137);
  g->Binary(ynn_binary_add, 3056, 3137, 3138);
}

// Scope: "Layer3 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3138, 3139);
  g->Reduce(ynn_reduce_sum, 3139, 6284, {2}, true);
  g->ShapeProduct(3139, 6283, {2});
  g->Binary(ynn_binary_divide, 6284, 6283, 3140);
  g->Binary(ynn_binary_add, 3140, 6446, 3141);
  g->Binary(ynn_binary_pow, 3141, 6448, 3142);
  g->Binary(ynn_binary_multiply, 3138, 3142, 3143);
  g->Convert(6844, 3145);
  g->Binary(ynn_binary_multiply, 3143, 3145, 3146);
  g->Quantize(3146, 3147, 0.019482526928186417, 0);
  g->Transpose(6838, 5240, {1,0});
  g->Binary(ynn_binary_multiply, 5238, 5239, 5236);
  g->Dot(3147, 5240, YNN_INVALID_VALUE_ID, 5235, 1);
  g->DequantizeTensor(5235, YNN_INVALID_VALUE_ID, 5236, 5237);
  g->QuantizeTensor(5237, 6412, 4198, 3148);
  g->Dequantize(3148, 3149, 0.02005414292216301, 0);
  g->Transpose(6837, 5245, {1,0});
  g->Binary(ynn_binary_multiply, 5238, 5244, 5242);
  g->Dot(3147, 5245, YNN_INVALID_VALUE_ID, 5241, 1);
  g->DequantizeTensor(5241, YNN_INVALID_VALUE_ID, 5242, 5243);
  g->QuantizeTensor(5243, 6412, 4198, 3150);
  g->Dequantize(3150, 3151, 0.02005414292216301, 0);
  g->Polynomial(3151, 6287, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6287, 6288);
  g->Binary(ynn_binary_add, 6288, 5474, 6285);
  g->Binary(ynn_binary_multiply, 3151, 5472, 6286);
  g->Binary(ynn_binary_multiply, 6286, 6285, 3152);
  g->Binary(ynn_binary_multiply, 3149, 3152, 3153);
  g->Quantize(3153, 3156, 0.03297245129942894, 0);
  g->Transpose(6836, 5251, {1,0});
  g->Binary(ynn_binary_multiply, 4346, 5250, 5247);
  g->Dot(3156, 5251, YNN_INVALID_VALUE_ID, 5246, 1);
  g->DequantizeTensor(5246, YNN_INVALID_VALUE_ID, 5247, 5248);
  g->QuantizeTensor(5248, 6412, 5249, 3157);
  g->Dequantize(3157, 3158, 0.022154856473207474, 0);
  g->Unary(ynn_unary_square, 3158, 3159);
  g->Reduce(ynn_reduce_sum, 3159, 6290, {2}, true);
  g->ShapeProduct(3159, 6289, {2});
  g->Binary(ynn_binary_divide, 6290, 6289, 3160);
  g->Binary(ynn_binary_add, 3160, 6446, 3161);
  g->Binary(ynn_binary_pow, 3161, 6448, 3162);
  g->Binary(ynn_binary_multiply, 3158, 3162, 3163);
  g->Convert(6842, 3164);
  g->Binary(ynn_binary_multiply, 3163, 3164, 3165);
  g->Binary(ynn_binary_add, 3138, 3165, 3167);
}

// Scope: "Layer3 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1064, 3168, {0,0,3,0}, {-1,-1,1,-1});
  g->Reshape(3168, 3169, {1,1,256});
  g->Binary(ynn_binary_add, 3169, 7049, 3170);
  g->Binary(ynn_binary_multiply, 3170, 6444, 3171);
  g->Quantize(3167, 3172, 0.2861534655094147, 0);
  g->Transpose(6839, 5258, {1,0});
  g->Binary(ynn_binary_multiply, 5255, 5257, 5253);
  g->Dot(3172, 5258, YNN_INVALID_VALUE_ID, 5252, 1);
  g->DequantizeTensor(5252, YNN_INVALID_VALUE_ID, 5253, 5254);
  g->QuantizeTensor(5254, 6412, 5256, 3173);
  g->Dequantize(3173, 3174, 0.050688985735177994, 0);
  g->Polynomial(3174, 6293, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6293, 6294);
  g->Binary(ynn_binary_add, 6294, 5474, 6291);
  g->Binary(ynn_binary_multiply, 3174, 5472, 6292);
  g->Binary(ynn_binary_multiply, 6292, 6291, 3175);
  g->Binary(ynn_binary_multiply, 3175, 3171, 3176);
  g->Quantize(3176, 3178, 0.06692913919687271, 0);
  g->Transpose(6840, 5265, {1,0});
  g->Binary(ynn_binary_multiply, 5262, 5264, 5260);
  g->Dot(3178, 5265, YNN_INVALID_VALUE_ID, 5259, 1);
  g->DequantizeTensor(5259, YNN_INVALID_VALUE_ID, 5260, 5261);
  g->QuantizeTensor(5261, 6412, 5263, 3179);
  g->Dequantize(3179, 3180, 0.0805763527750969, 0);
  g->Unary(ynn_unary_square, 3180, 3181);
  g->Reduce(ynn_reduce_sum, 3181, 6296, {2}, true);
  g->ShapeProduct(3181, 6295, {2});
  g->Binary(ynn_binary_divide, 6296, 6295, 3182);
  g->Binary(ynn_binary_add, 3182, 6446, 3183);
  g->Binary(ynn_binary_pow, 3183, 6448, 3184);
  g->Binary(ynn_binary_multiply, 3180, 3184, 3185);
  g->Convert(6843, 3186);
  g->Binary(ynn_binary_multiply, 3185, 3186, 3187);
  g->Binary(ynn_binary_add, 3167, 3187, 3189);
  g->Convert(6835, 3190);
  g->Binary(ynn_binary_multiply, 3189, 3190, 3191);
}

// Scope: "Layer3"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3(Context& ctx) {
  BuildLayer3Attention(ctx);
  BuildLayer3Mlp(ctx);
  BuildLayer3PerLayerEmbedding(ctx);
}

// Scope: "Layer4 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(3198, 3200, 0.023374712094664574, 0);
  g->Transpose(6933, 5272, {1,0});
  g->Binary(ynn_binary_multiply, 5269, 5271, 5267);
  g->Dot(3200, 5272, YNN_INVALID_VALUE_ID, 5266, 1);
  g->DequantizeTensor(5266, YNN_INVALID_VALUE_ID, 5267, 5268);
  g->QuantizeTensor(5268, 6412, 5270, 3201);
  g->Dequantize(3201, 3202, 0.024852370843291283, 0);
  g->Reshape(3202, 3203, {1,1,1,512});
  g->Reshape(3203, 3204, {1,1,1,512});
  g->Unary(ynn_unary_square, 3204, 3205);
  g->Reduce(ynn_reduce_sum, 3205, 6302, {3}, true);
  g->ShapeProduct(3205, 6301, {3});
  g->Binary(ynn_binary_divide, 6302, 6301, 3206);
  g->Binary(ynn_binary_add, 3206, 6446, 3207);
  g->Binary(ynn_binary_pow, 3207, 6448, 3208);
  g->Binary(ynn_binary_multiply, 3204, 3208, 3209);
  g->Convert(6932, 3211);
  g->Binary(ynn_binary_multiply, 3209, 3211, 3212);
  g->Slice(3212, 3213, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(3212, 3214, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 3214, 3215);
  g->Concat({3215,3213}, 3216, 3);
  g->Binary(ynn_binary_multiply, 3212, 3471, 3217);
  g->Binary(ynn_binary_multiply, 3216, 3576, 3218);
  g->Binary(ynn_binary_add, 3217, 3218, 3219);
  g->Transpose(6937, 5277, {1,0});
  g->Binary(ynn_binary_multiply, 5269, 5276, 5274);
  g->Dot(3200, 5277, YNN_INVALID_VALUE_ID, 5273, 1);
  g->DequantizeTensor(5273, YNN_INVALID_VALUE_ID, 5274, 5275);
  g->QuantizeTensor(5275, 6412, 5270, 3221);
  g->Dequantize(3221, 3222, 0.024852370843291283, 0);
  g->Reshape(3222, 3223, {1,1,1,512});
  g->Reshape(3223, 3224, {1,1,1,512});
  g->Unary(ynn_unary_square, 3224, 3225);
  g->Reduce(ynn_reduce_sum, 3225, 6304, {3}, true);
  g->ShapeProduct(3225, 6303, {3});
  g->Binary(ynn_binary_divide, 6304, 6303, 3226);
  g->Binary(ynn_binary_add, 3226, 6446, 3227);
  g->Binary(ynn_binary_pow, 3227, 6448, 3228);
  g->Binary(ynn_binary_multiply, 3224, 3228, 3229);
}

// Scope: "Layer4 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(3219, 3230, 0.0011563472216948867, 0);
  g->Append(6422, 3230, 7071, 2, s2, slinky::expr(int64_t{1}));
  g->View(7071, 7101, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7101, 3232, 0.0011563472216948867, 0);
  g->Quantize(3229, 3233, 0.01785714365541935, 0);
  g->Append(6437, 3233, 7086, 2, s2, slinky::expr(int64_t{1}));
  g->View(7086, 7116, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7116, 3234, 0.01785714365541935, 0);
}

// Scope: "Layer4 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(6936, 5283, {1,0});
  g->Binary(ynn_binary_multiply, 5269, 5282, 5279);
  g->Dot(3200, 5283, YNN_INVALID_VALUE_ID, 5278, 1);
  g->DequantizeTensor(5278, YNN_INVALID_VALUE_ID, 5279, 5280);
  g->QuantizeTensor(5280, 6412, 5281, 3235);
  g->Dequantize(3235, 3236, 0.03248032554984093, 0);
  g->SplitDim(3236, 3237, 2, {8,512});
  g->FuseDims(3237, 3239, 1, 2);
  g->SplitDim(3239, 3238, 1, {8,1});
  g->Unary(ynn_unary_square, 3238, 3240);
  g->Reduce(ynn_reduce_sum, 3240, 6306, {3}, true);
  g->ShapeProduct(3240, 6305, {3});
  g->Binary(ynn_binary_divide, 6306, 6305, 3241);
  g->Binary(ynn_binary_add, 3241, 6446, 3242);
  g->Binary(ynn_binary_pow, 3242, 6448, 3243);
  g->Binary(ynn_binary_multiply, 3238, 3243, 3244);
  g->Convert(6935, 3245);
  g->Binary(ynn_binary_multiply, 3244, 3245, 3246);
  g->Slice(3246, 3247, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(3246, 3248, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 3248, 3249);
  g->Concat({3249,3247}, 3250, 3);
  g->Binary(ynn_binary_multiply, 3246, 3471, 3251);
  g->Binary(ynn_binary_multiply, 3250, 3576, 3252);
  g->Binary(ynn_binary_add, 3251, 3252, 3253);
}

// Scope: "Layer4 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(3253, 3232, 3254, false, true);
  g->Mask(3254, 6482, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 6482, 6310, {-1}, true);
  g->Binary(ynn_binary_subtract, 6482, 6310, 6307);
  g->Unary(ynn_unary_exp, 6307, 6308);
  g->Reduce(ynn_reduce_sum, 6308, 6311, {-1}, true);
  g->Binary(ynn_binary_divide, 5474, 6311, 6309);
  g->Binary(ynn_binary_multiply, 6308, 6309, 3255);
  g->Matmul(3255, 3234, 3256, false, false);
}

// Scope: "Layer4 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(3256, 3260, 1, 2);
  g->SplitDim(3260, 3259, 1, {1,8});
  g->FuseDims(3259, 3261, 2, 2);
  g->Quantize(3261, 3262, 0.017962608486413956, 0);
  g->Transpose(6934, 5289, {1,0});
  g->Binary(ynn_binary_multiply, 3813, 5288, 5285);
  g->Dot(3262, 5289, YNN_INVALID_VALUE_ID, 5284, 1);
  g->DequantizeTensor(5284, YNN_INVALID_VALUE_ID, 5285, 5286);
  g->QuantizeTensor(5286, 6412, 5287, 3263);
  g->Dequantize(3263, 3264, 0.17608338594436646, 0);
}

// Scope: "Layer4 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3191, 3192);
  g->Reduce(ynn_reduce_sum, 3192, 6300, {2}, true);
  g->ShapeProduct(3192, 6299, {2});
  g->Binary(ynn_binary_divide, 6300, 6299, 3193);
  g->Binary(ynn_binary_add, 3193, 6446, 3194);
  g->Binary(ynn_binary_pow, 3194, 6448, 3195);
  g->Binary(ynn_binary_multiply, 3191, 3195, 3196);
  g->Convert(6921, 3197);
  g->Binary(ynn_binary_multiply, 3196, 3197, 3198);
  BuildLayer4AttentionKvProjection(ctx);
  BuildLayer4AttentionCacheUpdate(ctx);
  BuildLayer4AttentionQueryProjection(ctx);
  BuildLayer4AttentionSdpa(ctx);
  BuildLayer4AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 3264, 3265);
  g->Reduce(ynn_reduce_sum, 3265, 6313, {2}, true);
  g->ShapeProduct(3265, 6312, {2});
  g->Binary(ynn_binary_divide, 6313, 6312, 3266);
  g->Binary(ynn_binary_add, 3266, 6446, 3267);
  g->Binary(ynn_binary_pow, 3267, 6448, 3268);
  g->Binary(ynn_binary_multiply, 3264, 3268, 3269);
  g->Convert(6928, 3271);
  g->Binary(ynn_binary_multiply, 3269, 3271, 3272);
  g->Binary(ynn_binary_add, 3191, 3272, 3273);
}

// Scope: "Layer4 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3273, 3274);
  g->Reduce(ynn_reduce_sum, 3274, 6315, {2}, true);
  g->ShapeProduct(3274, 6314, {2});
  g->Binary(ynn_binary_divide, 6315, 6314, 3275);
  g->Binary(ynn_binary_add, 3275, 6446, 3276);
  g->Binary(ynn_binary_pow, 3276, 6448, 3277);
  g->Binary(ynn_binary_multiply, 3273, 3277, 3278);
  g->Convert(6931, 3279);
  g->Binary(ynn_binary_multiply, 3278, 3279, 3280);
  g->Quantize(3280, 3281, 0.060907524079084396, 0);
  g->Transpose(6925, 5295, {1,0});
  g->Binary(ynn_binary_multiply, 5293, 5294, 5291);
  g->Dot(3281, 5295, YNN_INVALID_VALUE_ID, 5290, 1);
  g->DequantizeTensor(5290, YNN_INVALID_VALUE_ID, 5291, 5292);
  g->QuantizeTensor(5292, 6412, 3719, 3282);
  g->Dequantize(3282, 3283, 0.09251969307661057, 0);
  g->Transpose(6924, 5300, {1,0});
  g->Binary(ynn_binary_multiply, 5293, 5299, 5297);
  g->Dot(3281, 5300, YNN_INVALID_VALUE_ID, 5296, 1);
  g->DequantizeTensor(5296, YNN_INVALID_VALUE_ID, 5297, 5298);
  g->QuantizeTensor(5298, 6412, 3719, 3284);
  g->Dequantize(3284, 3285, 0.09251969307661057, 0);
  g->Polynomial(3285, 6318, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6318, 6319);
  g->Binary(ynn_binary_add, 6319, 5474, 6316);
  g->Binary(ynn_binary_multiply, 3285, 5472, 6317);
  g->Binary(ynn_binary_multiply, 6317, 6316, 3286);
  g->Binary(ynn_binary_multiply, 3283, 3286, 3287);
  g->Quantize(3287, 3288, 0.3444882035255432, 0);
  g->Transpose(6923, 5307, {1,0});
  g->Binary(ynn_binary_multiply, 5304, 5306, 5302);
  g->Dot(3288, 5307, YNN_INVALID_VALUE_ID, 5301, 1);
  g->DequantizeTensor(5301, YNN_INVALID_VALUE_ID, 5302, 5303);
  g->QuantizeTensor(5303, 6412, 5305, 3289);
  g->Dequantize(3289, 3290, 0.13582009077072144, 0);
  g->Unary(ynn_unary_square, 3290, 3291);
  g->Reduce(ynn_reduce_sum, 3291, 6321, {2}, true);
  g->ShapeProduct(3291, 6320, {2});
  g->Binary(ynn_binary_divide, 6321, 6320, 3292);
  g->Binary(ynn_binary_add, 3292, 6446, 3293);
  g->Binary(ynn_binary_pow, 3293, 6448, 3294);
  g->Binary(ynn_binary_multiply, 3290, 3294, 3295);
  g->Convert(6929, 3296);
  g->Binary(ynn_binary_multiply, 3295, 3296, 3297);
  g->Binary(ynn_binary_add, 3273, 3297, 3298);
}

// Scope: "Layer4 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1064, 3299, {0,0,4,0}, {-1,-1,1,-1});
  g->Reshape(3299, 3301, {1,1,256});
  g->Binary(ynn_binary_add, 3301, 7055, 3302);
  g->Binary(ynn_binary_multiply, 3302, 6444, 3303);
  g->Quantize(3298, 3304, 0.41414323449134827, 0);
  g->Transpose(6926, 5313, {1,0});
  g->Binary(ynn_binary_multiply, 5311, 5312, 5309);
  g->Dot(3304, 5313, YNN_INVALID_VALUE_ID, 5308, 1);
  g->DequantizeTensor(5308, YNN_INVALID_VALUE_ID, 5309, 5310);
  g->QuantizeTensor(5310, 6412, 5145, 3305);
  g->Dequantize(3305, 3306, 0.039862215518951416, 0);
  g->Polynomial(3306, 6324, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6324, 6325);
  g->Binary(ynn_binary_add, 6325, 5474, 6322);
  g->Binary(ynn_binary_multiply, 3306, 5472, 6323);
  g->Binary(ynn_binary_multiply, 6323, 6322, 3307);
  g->Binary(ynn_binary_multiply, 3307, 3303, 3308);
  g->Quantize(3308, 3309, 0.30314961075782776, 0);
  g->Transpose(6927, 5320, {1,0});
  g->Binary(ynn_binary_multiply, 5317, 5319, 5315);
  g->Dot(3309, 5320, YNN_INVALID_VALUE_ID, 5314, 1);
  g->DequantizeTensor(5314, YNN_INVALID_VALUE_ID, 5315, 5316);
  g->QuantizeTensor(5316, 6412, 5318, 3310);
  g->Dequantize(3310, 3311, 0.16701875627040863, 0);
  g->Unary(ynn_unary_square, 3311, 3312);
  g->Reduce(ynn_reduce_sum, 3312, 6327, {2}, true);
  g->ShapeProduct(3312, 6326, {2});
  g->Binary(ynn_binary_divide, 6327, 6326, 3313);
  g->Binary(ynn_binary_add, 3313, 6446, 3314);
  g->Binary(ynn_binary_pow, 3314, 6448, 3315);
  g->Binary(ynn_binary_multiply, 3311, 3315, 3316);
  g->Convert(6930, 3317);
  g->Binary(ynn_binary_multiply, 3316, 3317, 3318);
  g->Binary(ynn_binary_add, 3298, 3318, 3319);
  g->Convert(6922, 3320);
  g->Binary(ynn_binary_multiply, 3319, 3320, 3322);
}

// Scope: "Layer4"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4(Context& ctx) {
  BuildLayer4Attention(ctx);
  BuildLayer4Mlp(ctx);
  BuildLayer4PerLayerEmbedding(ctx);
}

// Scope: "Layer5 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(3329, 3330, 0.07399173825979233, 0);
  g->Transpose(6950, 5333, {1,0});
  g->Binary(ynn_binary_multiply, 5330, 5332, 5328);
  g->Dot(3330, 5333, YNN_INVALID_VALUE_ID, 5327, 1);
  g->DequantizeTensor(5327, YNN_INVALID_VALUE_ID, 5328, 5329);
  g->QuantizeTensor(5329, 6412, 5331, 3331);
  g->Dequantize(3331, 3333, 0.09842520207166672, 0);
  g->Reshape(3333, 3334, {1,1,1,256});
  g->Reshape(3334, 3335, {1,1,1,256});
  g->Unary(ynn_unary_square, 3335, 3336);
  g->Reduce(ynn_reduce_sum, 3336, 6331, {3}, true);
  g->ShapeProduct(3336, 6330, {3});
  g->Binary(ynn_binary_divide, 6331, 6330, 3337);
  g->Binary(ynn_binary_add, 3337, 6446, 3338);
  g->Binary(ynn_binary_pow, 3338, 6448, 3339);
  g->Binary(ynn_binary_multiply, 3335, 3339, 3340);
  g->Convert(6949, 3341);
  g->Binary(ynn_binary_multiply, 3340, 3341, 3342);
  g->Slice(3342, 3344, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3342, 3345, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3345, 3346);
  g->Concat({3346,3344}, 3347, 3);
  g->Binary(ynn_binary_multiply, 3342, 2173, 3348);
  g->Binary(ynn_binary_multiply, 3347, 3050, 3349);
  g->Binary(ynn_binary_add, 3348, 3349, 3350);
  g->Transpose(6954, 5338, {1,0});
  g->Binary(ynn_binary_multiply, 5330, 5337, 5335);
  g->Dot(3330, 5338, YNN_INVALID_VALUE_ID, 5334, 1);
  g->DequantizeTensor(5334, YNN_INVALID_VALUE_ID, 5335, 5336);
  g->QuantizeTensor(5336, 6412, 5331, 3351);
  g->Dequantize(3351, 3352, 0.09842520207166672, 0);
  g->Reshape(3352, 3355, {1,1,1,256});
  g->Reshape(3355, 3356, {1,1,1,256});
  g->Unary(ynn_unary_square, 3356, 3357);
  g->Reduce(ynn_reduce_sum, 3357, 6333, {3}, true);
  g->ShapeProduct(3357, 6332, {3});
  g->Binary(ynn_binary_divide, 6333, 6332, 3358);
  g->Binary(ynn_binary_add, 3358, 6446, 3359);
  g->Binary(ynn_binary_pow, 3359, 6448, 3360);
  g->Binary(ynn_binary_multiply, 3356, 3360, 3361);
}

// Scope: "Layer5 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(3350, 3362, 0.006011798977851868, 0);
  g->Append(6423, 3362, 7072, 2, s2, slinky::expr(int64_t{1}));
  g->View(7072, 7102, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7102, 3365, 0.006011798977851868, 0);
  g->Quantize(3361, 3366, 0.047244105488061905, 0);
  g->Append(6438, 3366, 7087, 2, s2, slinky::expr(int64_t{1}));
  g->View(7087, 7117, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7117, 3367, 0.047244105488061905, 0);
}

// Scope: "Layer5 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(6953, 5343, {1,0});
  g->Binary(ynn_binary_multiply, 5330, 5342, 5340);
  g->Dot(3330, 5343, YNN_INVALID_VALUE_ID, 5339, 1);
  g->DequantizeTensor(5339, YNN_INVALID_VALUE_ID, 5340, 5341);
  g->QuantizeTensor(5341, 6412, 4096, 3368);
  g->Dequantize(3368, 3369, 0.13385827839374542, 0);
  g->SplitDim(3369, 3370, 2, {8,256});
  g->FuseDims(3370, 3372, 1, 2);
  g->SplitDim(3372, 3371, 1, {8,1});
  g->Unary(ynn_unary_square, 3371, 3374);
  g->Reduce(ynn_reduce_sum, 3374, 6337, {3}, true);
  g->ShapeProduct(3374, 6336, {3});
  g->Binary(ynn_binary_divide, 6337, 6336, 3375);
  g->Binary(ynn_binary_add, 3375, 6446, 3376);
  g->Binary(ynn_binary_pow, 3376, 6448, 3377);
  g->Binary(ynn_binary_multiply, 3371, 3377, 3378);
  g->Convert(6952, 3379);
  g->Binary(ynn_binary_multiply, 3378, 3379, 3380);
  g->Slice(3380, 3381, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3380, 3382, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3382, 3383);
  g->Concat({3383,3381}, 3385, 3);
  g->Binary(ynn_binary_multiply, 3380, 2173, 3386);
  g->Binary(ynn_binary_multiply, 3385, 3050, 3387);
  g->Binary(ynn_binary_add, 3386, 3387, 3388);
}

// Scope: "Layer5 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(3388, 3365, 3389, false, true);
  g->Mask(3389, 6483, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6483, 6341, {-1}, true);
  g->Binary(ynn_binary_subtract, 6483, 6341, 6338);
  g->Unary(ynn_unary_exp, 6338, 6339);
  g->Reduce(ynn_reduce_sum, 6339, 6342, {-1}, true);
  g->Binary(ynn_binary_divide, 5474, 6342, 6340);
  g->Binary(ynn_binary_multiply, 6339, 6340, 3390);
  g->Matmul(3390, 3367, 3391, false, false);
}

// Scope: "Layer5 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(3391, 3393, 1, 2);
  g->SplitDim(3393, 3392, 1, {1,8});
  g->FuseDims(3392, 3394, 2, 2);
  g->Quantize(3394, 3396, 0.026451781392097473, 0);
  g->Transpose(6951, 5350, {1,0});
  g->Binary(ynn_binary_multiply, 5347, 5349, 5345);
  g->Dot(3396, 5350, YNN_INVALID_VALUE_ID, 5344, 1);
  g->DequantizeTensor(5344, YNN_INVALID_VALUE_ID, 5345, 5346);
  g->QuantizeTensor(5346, 6412, 5348, 3397);
  g->Dequantize(3397, 3398, 0.043322544544935226, 0);
}

// Scope: "Layer5 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3322, 3323);
  g->Reduce(ynn_reduce_sum, 3323, 6329, {2}, true);
  g->ShapeProduct(3323, 6328, {2});
  g->Binary(ynn_binary_divide, 6329, 6328, 3324);
  g->Binary(ynn_binary_add, 3324, 6446, 3325);
  g->Binary(ynn_binary_pow, 3325, 6448, 3326);
  g->Binary(ynn_binary_multiply, 3322, 3326, 3327);
  g->Convert(6938, 3328);
  g->Binary(ynn_binary_multiply, 3327, 3328, 3329);
  BuildLayer5AttentionKvProjection(ctx);
  BuildLayer5AttentionCacheUpdate(ctx);
  BuildLayer5AttentionQueryProjection(ctx);
  BuildLayer5AttentionSdpa(ctx);
  BuildLayer5AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 3398, 3399);
  g->Reduce(ynn_reduce_sum, 3399, 6344, {2}, true);
  g->ShapeProduct(3399, 6343, {2});
  g->Binary(ynn_binary_divide, 6344, 6343, 3400);
  g->Binary(ynn_binary_add, 3400, 6446, 3401);
  g->Binary(ynn_binary_pow, 3401, 6448, 3402);
  g->Binary(ynn_binary_multiply, 3398, 3402, 3403);
  g->Convert(6945, 3404);
  g->Binary(ynn_binary_multiply, 3403, 3404, 3405);
  g->Binary(ynn_binary_add, 3322, 3405, 3407);
}

// Scope: "Layer5 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3407, 3408);
  g->Reduce(ynn_reduce_sum, 3408, 6346, {2}, true);
  g->ShapeProduct(3408, 6345, {2});
  g->Binary(ynn_binary_divide, 6346, 6345, 3409);
  g->Binary(ynn_binary_add, 3409, 6446, 3410);
  g->Binary(ynn_binary_pow, 3410, 6448, 3411);
  g->Binary(ynn_binary_multiply, 3407, 3411, 3412);
  g->Convert(6948, 3413);
  g->Binary(ynn_binary_multiply, 3412, 3413, 3414);
  g->Quantize(3414, 3415, 0.03518042340874672, 0);
  g->Transpose(6942, 5356, {1,0});
  g->Binary(ynn_binary_multiply, 5354, 5355, 5352);
  g->Dot(3415, 5356, YNN_INVALID_VALUE_ID, 5351, 1);
  g->DequantizeTensor(5351, YNN_INVALID_VALUE_ID, 5352, 5353);
  g->QuantizeTensor(5353, 6412, 4557, 3416);
  g->Dequantize(3416, 3418, 0.03567914664745331, 0);
  g->Transpose(6941, 5361, {1,0});
  g->Binary(ynn_binary_multiply, 5354, 5360, 5358);
  g->Dot(3415, 5361, YNN_INVALID_VALUE_ID, 5357, 1);
  g->DequantizeTensor(5357, YNN_INVALID_VALUE_ID, 5358, 5359);
  g->QuantizeTensor(5359, 6412, 4557, 3419);
  g->Dequantize(3419, 3420, 0.03567914664745331, 0);
  g->Polynomial(3420, 6349, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6349, 6350);
  g->Binary(ynn_binary_add, 6350, 5474, 6347);
  g->Binary(ynn_binary_multiply, 3420, 5472, 6348);
  g->Binary(ynn_binary_multiply, 6348, 6347, 3421);
  g->Binary(ynn_binary_multiply, 3418, 3421, 3422);
  g->Quantize(3422, 3423, 0.08415354788303375, 0);
  g->Transpose(6940, 5368, {1,0});
  g->Binary(ynn_binary_multiply, 5365, 5367, 5363);
  g->Dot(3423, 5368, YNN_INVALID_VALUE_ID, 5362, 1);
  g->DequantizeTensor(5362, YNN_INVALID_VALUE_ID, 5363, 5364);
  g->QuantizeTensor(5364, 6412, 5366, 3424);
  g->Dequantize(3424, 3425, 0.06301677227020264, 0);
  g->Unary(ynn_unary_square, 3425, 3426);
  g->Reduce(ynn_reduce_sum, 3426, 6352, {2}, true);
  g->ShapeProduct(3426, 6351, {2});
  g->Binary(ynn_binary_divide, 6352, 6351, 3428);
  g->Binary(ynn_binary_add, 3428, 6446, 3429);
  g->Binary(ynn_binary_pow, 3429, 6448, 3430);
  g->Binary(ynn_binary_multiply, 3425, 3430, 3431);
  g->Convert(6946, 3432);
  g->Binary(ynn_binary_multiply, 3431, 3432, 3433);
  g->Binary(ynn_binary_add, 3407, 3433, 3434);
}

// Scope: "Layer5 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1064, 3435, {0,0,5,0}, {-1,-1,1,-1});
  g->Reshape(3435, 3436, {1,1,256});
  g->Binary(ynn_binary_add, 3436, 7056, 3437);
  g->Binary(ynn_binary_multiply, 3437, 6444, 3439);
  g->Quantize(3434, 3440, 0.3165745139122009, 0);
  g->Transpose(6943, 5375, {1,0});
  g->Binary(ynn_binary_multiply, 5372, 5374, 5370);
  g->Dot(3440, 5375, YNN_INVALID_VALUE_ID, 5369, 1);
  g->DequantizeTensor(5369, YNN_INVALID_VALUE_ID, 5370, 5371);
  g->QuantizeTensor(5371, 6412, 5373, 3441);
  g->Dequantize(3441, 3442, 0.0393700897693634, 0);
  g->Polynomial(3442, 6355, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6355, 6356);
  g->Binary(ynn_binary_add, 6356, 5474, 6353);
  g->Binary(ynn_binary_multiply, 3442, 5472, 6354);
  g->Binary(ynn_binary_multiply, 6354, 6353, 3443);
  g->Binary(ynn_binary_multiply, 3443, 3439, 3444);
  g->Quantize(3444, 3445, 0.22933071851730347, 0);
  g->Transpose(6944, 5382, {1,0});
  g->Binary(ynn_binary_multiply, 5379, 5381, 5377);
  g->Dot(3445, 5382, YNN_INVALID_VALUE_ID, 5376, 1);
  g->DequantizeTensor(5376, YNN_INVALID_VALUE_ID, 5377, 5378);
  g->QuantizeTensor(5378, 6412, 5380, 3446);
  g->Dequantize(3446, 3447, 0.12322933226823807, 0);
  g->Unary(ynn_unary_square, 3447, 3448);
  g->Reduce(ynn_reduce_sum, 3448, 6358, {2}, true);
  g->ShapeProduct(3448, 6357, {2});
  g->Binary(ynn_binary_divide, 6358, 6357, 3450);
  g->Binary(ynn_binary_add, 3450, 6446, 3451);
  g->Binary(ynn_binary_pow, 3451, 6448, 3452);
  g->Binary(ynn_binary_multiply, 3447, 3452, 3453);
  g->Convert(6947, 3454);
  g->Binary(ynn_binary_multiply, 3453, 3454, 3455);
  g->Binary(ynn_binary_add, 3434, 3455, 3456);
  g->Convert(6939, 3457);
  g->Binary(ynn_binary_multiply, 3456, 3457, 3458);
}

// Scope: "Layer5"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5(Context& ctx) {
  BuildLayer5Attention(ctx);
  BuildLayer5Mlp(ctx);
  BuildLayer5PerLayerEmbedding(ctx);
}

// Scope: "Layer6 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(3466, 3467, 0.341854453086853, 0);
  g->Transpose(6967, 5389, {1,0});
  g->Binary(ynn_binary_multiply, 5386, 5388, 5384);
  g->Dot(3467, 5389, YNN_INVALID_VALUE_ID, 5383, 1);
  g->DequantizeTensor(5383, YNN_INVALID_VALUE_ID, 5384, 5385);
  g->QuantizeTensor(5385, 6412, 5387, 3468);
  g->Dequantize(3468, 3469, 0.28740158677101135, 0);
  g->Reshape(3469, 3470, {1,1,1,256});
  g->Reshape(3470, 3473, {1,1,1,256});
  g->Unary(ynn_unary_square, 3473, 3474);
  g->Reduce(ynn_reduce_sum, 3474, 6362, {3}, true);
  g->ShapeProduct(3474, 6361, {3});
  g->Binary(ynn_binary_divide, 6362, 6361, 3475);
  g->Binary(ynn_binary_add, 3475, 6446, 3476);
  g->Binary(ynn_binary_pow, 3476, 6448, 3477);
  g->Binary(ynn_binary_multiply, 3473, 3477, 3478);
  g->Convert(6966, 3479);
  g->Binary(ynn_binary_multiply, 3478, 3479, 3480);
  g->Slice(3480, 3481, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3480, 3482, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3482, 3484);
  g->Concat({3484,3481}, 3485, 3);
  g->Binary(ynn_binary_multiply, 3480, 2173, 3486);
  g->Binary(ynn_binary_multiply, 3485, 3050, 3487);
  g->Binary(ynn_binary_add, 3486, 3487, 3488);
  g->Transpose(6971, 5394, {1,0});
  g->Binary(ynn_binary_multiply, 5386, 5393, 5391);
  g->Dot(3467, 5394, YNN_INVALID_VALUE_ID, 5390, 1);
  g->DequantizeTensor(5390, YNN_INVALID_VALUE_ID, 5391, 5392);
  g->QuantizeTensor(5392, 6412, 5387, 3489);
  g->Dequantize(3489, 3490, 0.28740158677101135, 0);
  g->Reshape(3490, 3491, {1,1,1,256});
  g->Reshape(3491, 3492, {1,1,1,256});
  g->Unary(ynn_unary_square, 3492, 3494);
  g->Reduce(ynn_reduce_sum, 3494, 6364, {3}, true);
  g->ShapeProduct(3494, 6363, {3});
  g->Binary(ynn_binary_divide, 6364, 6363, 3495);
  g->Binary(ynn_binary_add, 3495, 6446, 3496);
  g->Binary(ynn_binary_pow, 3496, 6448, 3497);
  g->Binary(ynn_binary_multiply, 3492, 3497, 3498);
}

// Scope: "Layer6 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(3488, 3499, 0.0057707298547029495, 0);
  g->Append(6424, 3499, 7073, 2, s2, slinky::expr(int64_t{1}));
  g->View(7073, 7103, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7103, 3500, 0.0057707298547029495, 0);
  g->Quantize(3498, 3501, 0.047244105488061905, 0);
  g->Append(6439, 3501, 7088, 2, s2, slinky::expr(int64_t{1}));
  g->View(7088, 7118, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7118, 3503, 0.047244105488061905, 0);
}

// Scope: "Layer6 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(6970, 5400, {1,0});
  g->Binary(ynn_binary_multiply, 5386, 5399, 5396);
  g->Dot(3467, 5400, YNN_INVALID_VALUE_ID, 5395, 1);
  g->DequantizeTensor(5395, YNN_INVALID_VALUE_ID, 5396, 5397);
  g->QuantizeTensor(5397, 6412, 5398, 3504);
  g->Dequantize(3504, 3505, 0.4566929042339325, 0);
  g->SplitDim(3505, 3506, 2, {8,256});
  g->FuseDims(3506, 3508, 1, 2);
  g->SplitDim(3508, 3507, 1, {8,1});
  g->Unary(ynn_unary_square, 3507, 3509);
  g->Reduce(ynn_reduce_sum, 3509, 6366, {3}, true);
  g->ShapeProduct(3509, 6365, {3});
  g->Binary(ynn_binary_divide, 6366, 6365, 3510);
  g->Binary(ynn_binary_add, 3510, 6446, 3512);
  g->Binary(ynn_binary_pow, 3512, 6448, 3513);
  g->Binary(ynn_binary_multiply, 3507, 3513, 3514);
  g->Convert(6969, 3515);
  g->Binary(ynn_binary_multiply, 3514, 3515, 3516);
  g->Slice(3516, 3517, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3516, 3518, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3518, 3519);
  g->Concat({3519,3517}, 3520, 3);
  g->Binary(ynn_binary_multiply, 3516, 2173, 3521);
  g->Binary(ynn_binary_multiply, 3520, 3050, 3522);
  g->Binary(ynn_binary_add, 3521, 3522, 3523);
}

// Scope: "Layer6 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(3523, 3500, 3524, false, true);
  g->Mask(3524, 6484, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6484, 6370, {-1}, true);
  g->Binary(ynn_binary_subtract, 6484, 6370, 6367);
  g->Unary(ynn_unary_exp, 6367, 6368);
  g->Reduce(ynn_reduce_sum, 6368, 6371, {-1}, true);
  g->Binary(ynn_binary_divide, 5474, 6371, 6369);
  g->Binary(ynn_binary_multiply, 6368, 6369, 3525);
  g->Matmul(3525, 3503, 3526, false, false);
}

// Scope: "Layer6 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(3526, 3528, 1, 2);
  g->SplitDim(3528, 3527, 1, {1,8});
  g->FuseDims(3527, 3529, 2, 2);
  g->Quantize(3529, 3530, 0.0354330837726593, 0);
  g->Transpose(6968, 5407, {1,0});
  g->Binary(ynn_binary_multiply, 5404, 5406, 5402);
  g->Dot(3530, 5407, YNN_INVALID_VALUE_ID, 5401, 1);
  g->DequantizeTensor(5401, YNN_INVALID_VALUE_ID, 5402, 5403);
  g->QuantizeTensor(5403, 6412, 5405, 3531);
  g->Dequantize(3531, 3533, 0.05930274724960327, 0);
}

// Scope: "Layer6 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3458, 3459);
  g->Reduce(ynn_reduce_sum, 3459, 6360, {2}, true);
  g->ShapeProduct(3459, 6359, {2});
  g->Binary(ynn_binary_divide, 6360, 6359, 3461);
  g->Binary(ynn_binary_add, 3461, 6446, 3462);
  g->Binary(ynn_binary_pow, 3462, 6448, 3463);
  g->Binary(ynn_binary_multiply, 3458, 3463, 3464);
  g->Convert(6955, 3465);
  g->Binary(ynn_binary_multiply, 3464, 3465, 3466);
  BuildLayer6AttentionKvProjection(ctx);
  BuildLayer6AttentionCacheUpdate(ctx);
  BuildLayer6AttentionQueryProjection(ctx);
  BuildLayer6AttentionSdpa(ctx);
  BuildLayer6AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 3533, 3534);
  g->Reduce(ynn_reduce_sum, 3534, 6378, {2}, true);
  g->ShapeProduct(3534, 6377, {2});
  g->Binary(ynn_binary_divide, 6378, 6377, 3535);
  g->Binary(ynn_binary_add, 3535, 6446, 3536);
  g->Binary(ynn_binary_pow, 3536, 6448, 3537);
  g->Binary(ynn_binary_multiply, 3533, 3537, 3538);
  g->Convert(6962, 3539);
  g->Binary(ynn_binary_multiply, 3538, 3539, 3540);
  g->Binary(ynn_binary_add, 3458, 3540, 3541);
}

// Scope: "Layer6 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3541, 3542);
  g->Reduce(ynn_reduce_sum, 3542, 6380, {2}, true);
  g->ShapeProduct(3542, 6379, {2});
  g->Binary(ynn_binary_divide, 6380, 6379, 3544);
  g->Binary(ynn_binary_add, 3544, 6446, 3545);
  g->Binary(ynn_binary_pow, 3545, 6448, 3546);
  g->Binary(ynn_binary_multiply, 3541, 3546, 3547);
  g->Convert(6965, 3548);
  g->Binary(ynn_binary_multiply, 3547, 3548, 3549);
  g->Quantize(3549, 3550, 0.02705955132842064, 0);
  g->Transpose(6959, 5414, {1,0});
  g->Binary(ynn_binary_multiply, 5411, 5413, 5409);
  g->Dot(3550, 5414, YNN_INVALID_VALUE_ID, 5408, 1);
  g->DequantizeTensor(5408, YNN_INVALID_VALUE_ID, 5409, 5410);
  g->QuantizeTensor(5410, 6412, 5412, 3551);
  g->Dequantize(3551, 3552, 0.02632874995470047, 0);
  g->Transpose(6958, 5419, {1,0});
  g->Binary(ynn_binary_multiply, 5411, 5418, 5416);
  g->Dot(3550, 5419, YNN_INVALID_VALUE_ID, 5415, 1);
  g->DequantizeTensor(5415, YNN_INVALID_VALUE_ID, 5416, 5417);
  g->QuantizeTensor(5417, 6412, 5412, 3555);
  g->Dequantize(3555, 3556, 0.02632874995470047, 0);
  g->Polynomial(3556, 6383, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6383, 6384);
  g->Binary(ynn_binary_add, 6384, 5474, 6381);
  g->Binary(ynn_binary_multiply, 3556, 5472, 6382);
  g->Binary(ynn_binary_multiply, 6382, 6381, 3557);
  g->Binary(ynn_binary_multiply, 3552, 3557, 3558);
  g->Quantize(3558, 3559, 0.039862215518951416, 0);
  g->Transpose(6957, 5425, {1,0});
  g->Binary(ynn_binary_multiply, 5145, 5424, 5421);
  g->Dot(3559, 5425, YNN_INVALID_VALUE_ID, 5420, 1);
  g->DequantizeTensor(5420, YNN_INVALID_VALUE_ID, 5421, 5422);
  g->QuantizeTensor(5422, 6412, 5423, 3560);
  g->Dequantize(3560, 3561, 0.019578030332922935, 0);
  g->Unary(ynn_unary_square, 3561, 3562);
  g->Reduce(ynn_reduce_sum, 3562, 6386, {2}, true);
  g->ShapeProduct(3562, 6385, {2});
  g->Binary(ynn_binary_divide, 6386, 6385, 3563);
  g->Binary(ynn_binary_add, 3563, 6446, 3564);
  g->Binary(ynn_binary_pow, 3564, 6448, 3566);
  g->Binary(ynn_binary_multiply, 3561, 3566, 3567);
  g->Convert(6963, 3568);
  g->Binary(ynn_binary_multiply, 3567, 3568, 3569);
  g->Binary(ynn_binary_add, 3541, 3569, 3570);
}

// Scope: "Layer6 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1064, 3571, {0,0,6,0}, {-1,-1,1,-1});
  g->Reshape(3571, 3572, {1,1,256});
  g->Binary(ynn_binary_add, 3572, 7057, 3573);
  g->Binary(ynn_binary_multiply, 3573, 6444, 3574);
  g->Quantize(3570, 3575, 0.34014976024627686, 0);
  g->Transpose(6960, 5432, {1,0});
  g->Binary(ynn_binary_multiply, 5429, 5431, 5427);
  g->Dot(3575, 5432, YNN_INVALID_VALUE_ID, 5426, 1);
  g->DequantizeTensor(5426, YNN_INVALID_VALUE_ID, 5427, 5428);
  g->QuantizeTensor(5428, 6412, 5430, 3578);
  g->Dequantize(3578, 3579, 0.04773623123764992, 0);
  g->Polynomial(3579, 6389, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6389, 6390);
  g->Binary(ynn_binary_add, 6390, 5474, 6387);
  g->Binary(ynn_binary_multiply, 3579, 5472, 6388);
  g->Binary(ynn_binary_multiply, 6388, 6387, 3580);
  g->Binary(ynn_binary_multiply, 3580, 3574, 3581);
  g->Quantize(3581, 3582, 0.12450788170099258, 0);
  g->Transpose(6961, 5438, {1,0});
  g->Binary(ynn_binary_multiply, 4040, 5437, 5434);
  g->Dot(3582, 5438, YNN_INVALID_VALUE_ID, 5433, 1);
  g->DequantizeTensor(5433, YNN_INVALID_VALUE_ID, 5434, 5435);
  g->QuantizeTensor(5435, 6412, 5436, 3583);
  g->Dequantize(3583, 3584, 0.07488936185836792, 0);
  g->Unary(ynn_unary_square, 3584, 3585);
  g->Reduce(ynn_reduce_sum, 3585, 6392, {2}, true);
  g->ShapeProduct(3585, 6391, {2});
  g->Binary(ynn_binary_divide, 6392, 6391, 3586);
  g->Binary(ynn_binary_add, 3586, 6446, 3587);
  g->Binary(ynn_binary_pow, 3587, 6448, 3589);
  g->Binary(ynn_binary_multiply, 3584, 3589, 3590);
  g->Convert(6964, 3591);
  g->Binary(ynn_binary_multiply, 3590, 3591, 3592);
  g->Binary(ynn_binary_add, 3570, 3592, 3593);
  g->Convert(6956, 3594);
  g->Binary(ynn_binary_multiply, 3593, 3594, 3595);
}

// Scope: "Layer6"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6(Context& ctx) {
  BuildLayer6Attention(ctx);
  BuildLayer6Mlp(ctx);
  BuildLayer6PerLayerEmbedding(ctx);
}

// Scope: "Layer7 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(3603, 3604, 0.29519250988960266, 0);
  g->Transpose(6984, 5452, {1,0});
  g->Binary(ynn_binary_multiply, 5449, 5451, 5447);
  g->Dot(3604, 5452, YNN_INVALID_VALUE_ID, 5446, 1);
  g->DequantizeTensor(5446, YNN_INVALID_VALUE_ID, 5447, 5448);
  g->QuantizeTensor(5448, 6412, 5450, 3605);
  g->Dequantize(3605, 3606, 0.3681102395057678, 0);
  g->Reshape(3606, 3607, {1,1,1,256});
  g->Reshape(3607, 3608, {1,1,1,256});
  g->Unary(ynn_unary_square, 3608, 3609);
  g->Reduce(ynn_reduce_sum, 3609, 6396, {3}, true);
  g->ShapeProduct(3609, 6395, {3});
  g->Binary(ynn_binary_divide, 6396, 6395, 3611);
  g->Binary(ynn_binary_add, 3611, 6446, 3612);
  g->Binary(ynn_binary_pow, 3612, 6448, 3613);
  g->Binary(ynn_binary_multiply, 3608, 3613, 3614);
  g->Convert(6983, 3615);
  g->Binary(ynn_binary_multiply, 3614, 3615, 3616);
  g->Slice(3616, 3617, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3616, 3618, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3618, 3619);
  g->Concat({3619,3617}, 3620, 3);
  g->Binary(ynn_binary_multiply, 3616, 2173, 3622);
  g->Binary(ynn_binary_multiply, 3620, 3050, 3623);
  g->Binary(ynn_binary_add, 3622, 3623, 3624);
  g->Transpose(6988, 5457, {1,0});
  g->Binary(ynn_binary_multiply, 5449, 5456, 5454);
  g->Dot(3604, 5457, YNN_INVALID_VALUE_ID, 5453, 1);
  g->DequantizeTensor(5453, YNN_INVALID_VALUE_ID, 5454, 5455);
  g->QuantizeTensor(5455, 6412, 5450, 3625);
  g->Dequantize(3625, 3626, 0.3681102395057678, 0);
  g->Reshape(3626, 3627, {1,1,1,256});
  g->Reshape(3627, 3628, {1,1,1,256});
  g->Unary(ynn_unary_square, 3628, 3629);
  g->Reduce(ynn_reduce_sum, 3629, 6400, {3}, true);
  g->ShapeProduct(3629, 6399, {3});
  g->Binary(ynn_binary_divide, 6400, 6399, 3630);
  g->Binary(ynn_binary_add, 3630, 6446, 3632);
  g->Binary(ynn_binary_pow, 3632, 6448, 3633);
  g->Binary(ynn_binary_multiply, 3628, 3633, 3634);
}

// Scope: "Layer7 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(3624, 3635, 0.005869260523468256, 0);
  g->Append(6425, 3635, 7074, 2, s2, slinky::expr(int64_t{1}));
  g->View(7074, 7104, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7104, 3636, 0.005869260523468256, 0);
  g->Quantize(3634, 3637, 0.047244105488061905, 0);
  g->Append(6440, 3637, 7089, 2, s2, slinky::expr(int64_t{1}));
  g->View(7089, 7119, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7119, 3639, 0.047244105488061905, 0);
}

// Scope: "Layer7 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(6987, 5463, {1,0});
  g->Binary(ynn_binary_multiply, 5449, 5462, 5459);
  g->Dot(3604, 5463, YNN_INVALID_VALUE_ID, 5458, 1);
  g->DequantizeTensor(5458, YNN_INVALID_VALUE_ID, 5459, 5460);
  g->QuantizeTensor(5460, 6412, 5461, 3640);
  g->Dequantize(3640, 3641, 0.31496062874794006, 0);
  g->SplitDim(3641, 3642, 2, {8,256});
  g->FuseDims(3642, 3644, 1, 2);
  g->SplitDim(3644, 3643, 1, {8,1});
  g->Unary(ynn_unary_square, 3643, 3645);
  g->Reduce(ynn_reduce_sum, 3645, 6402, {3}, true);
  g->ShapeProduct(3645, 6401, {3});
  g->Binary(ynn_binary_divide, 6402, 6401, 3646);
  g->Binary(ynn_binary_add, 3646, 6446, 3647);
  g->Binary(ynn_binary_pow, 3647, 6448, 3648);
  g->Binary(ynn_binary_multiply, 3643, 3648, 3650);
  g->Convert(6986, 3651);
  g->Binary(ynn_binary_multiply, 3650, 3651, 3652);
  g->Slice(3652, 3653, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3652, 3654, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3654, 3655);
  g->Concat({3655,3653}, 3656, 3);
  g->Binary(ynn_binary_multiply, 3652, 2173, 3657);
  g->Binary(ynn_binary_multiply, 3656, 3050, 3658);
  g->Binary(ynn_binary_add, 3657, 3658, 3659);
}

// Scope: "Layer7 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(3659, 3636, 3661, false, true);
  g->Mask(3661, 6485, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6485, 6406, {-1}, true);
  g->Binary(ynn_binary_subtract, 6485, 6406, 6403);
  g->Unary(ynn_unary_exp, 6403, 6404);
  g->Reduce(ynn_reduce_sum, 6404, 6407, {-1}, true);
  g->Binary(ynn_binary_divide, 5474, 6407, 6405);
  g->Binary(ynn_binary_multiply, 6404, 6405, 3662);
  g->Matmul(3662, 3639, 3663, false, false);
}

// Scope: "Layer7 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(3663, 3665, 1, 2);
  g->SplitDim(3665, 3664, 1, {1,8});
  g->FuseDims(3664, 3666, 2, 2);
  g->Quantize(3666, 3667, 0.028912410140037537, 0);
  g->Transpose(6985, 5470, {1,0});
  g->Binary(ynn_binary_multiply, 5467, 5469, 5465);
  g->Dot(3667, 5470, YNN_INVALID_VALUE_ID, 5464, 1);
  g->DequantizeTensor(5464, YNN_INVALID_VALUE_ID, 5465, 5466);
  g->QuantizeTensor(5466, 6412, 5468, 3668);
  g->Dequantize(3668, 3669, 0.025238478556275368, 0);
}

// Scope: "Layer7 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3595, 3596);
  g->Reduce(ynn_reduce_sum, 3596, 6394, {2}, true);
  g->ShapeProduct(3596, 6393, {2});
  g->Binary(ynn_binary_divide, 6394, 6393, 3597);
  g->Binary(ynn_binary_add, 3597, 6446, 3598);
  g->Binary(ynn_binary_pow, 3598, 6448, 3600);
  g->Binary(ynn_binary_multiply, 3595, 3600, 3601);
  g->Convert(6972, 3602);
  g->Binary(ynn_binary_multiply, 3601, 3602, 3603);
  BuildLayer7AttentionKvProjection(ctx);
  BuildLayer7AttentionCacheUpdate(ctx);
  BuildLayer7AttentionQueryProjection(ctx);
  BuildLayer7AttentionSdpa(ctx);
  BuildLayer7AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 3669, 3670);
  g->Reduce(ynn_reduce_sum, 3670, 6409, {2}, true);
  g->ShapeProduct(3670, 6408, {2});
  g->Binary(ynn_binary_divide, 6409, 6408, 3672);
  g->Binary(ynn_binary_add, 3672, 6446, 3673);
  g->Binary(ynn_binary_pow, 3673, 6448, 3674);
  g->Binary(ynn_binary_multiply, 3669, 3674, 3675);
  g->Convert(6979, 3676);
  g->Binary(ynn_binary_multiply, 3675, 3676, 3677);
  g->Binary(ynn_binary_add, 3595, 3677, 3678);
}

// Scope: "Layer7 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3678, 3679);
  g->Reduce(ynn_reduce_sum, 3679, 6411, {2}, true);
  g->ShapeProduct(3679, 6410, {2});
  g->Binary(ynn_binary_divide, 6411, 6410, 3680);
  g->Binary(ynn_binary_add, 3680, 6446, 3681);
  g->Binary(ynn_binary_pow, 3681, 6448, 4);
  g->Binary(ynn_binary_multiply, 3678, 4, 5);
  g->Convert(6982, 6);
  g->Binary(ynn_binary_multiply, 5, 6, 7);
  g->Quantize(7, 8, 0.023717211559414864, 0);
  g->Transpose(6976, 3688, {1,0});
  g->Binary(ynn_binary_multiply, 3685, 3687, 3683);
  g->Dot(8, 3688, YNN_INVALID_VALUE_ID, 3682, 1);
  g->DequantizeTensor(3682, YNN_INVALID_VALUE_ID, 3683, 3684);
  g->QuantizeTensor(3684, 6412, 3686, 9);
  g->Dequantize(9, 10, 0.021899616345763206, 0);
  g->Transpose(6975, 3693, {1,0});
  g->Binary(ynn_binary_multiply, 3685, 3692, 3690);
  g->Dot(8, 3693, YNN_INVALID_VALUE_ID, 3689, 1);
  g->DequantizeTensor(3689, YNN_INVALID_VALUE_ID, 3690, 3691);
  g->QuantizeTensor(3691, 6412, 3686, 11);
  g->Dequantize(11, 12, 0.021899616345763206, 0);
  g->Polynomial(12, 5475, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5475, 5476);
  g->Binary(ynn_binary_add, 5476, 5474, 5471);
  g->Binary(ynn_binary_multiply, 12, 5472, 5473);
  g->Binary(ynn_binary_multiply, 5473, 5471, 14);
  g->Binary(ynn_binary_multiply, 10, 14, 15);
  g->Quantize(15, 16, 0.02202264778316021, 0);
  g->Transpose(6974, 3700, {1,0});
  g->Binary(ynn_binary_multiply, 3697, 3699, 3695);
  g->Dot(16, 3700, YNN_INVALID_VALUE_ID, 3694, 1);
  g->DequantizeTensor(3694, YNN_INVALID_VALUE_ID, 3695, 3696);
  g->QuantizeTensor(3696, 6412, 3698, 17);
  g->Dequantize(17, 18, 0.01081059779971838, 0);
  g->Unary(ynn_unary_square, 18, 19);
  g->Reduce(ynn_reduce_sum, 19, 5478, {2}, true);
  g->ShapeProduct(19, 5477, {2});
  g->Binary(ynn_binary_divide, 5478, 5477, 20);
  g->Binary(ynn_binary_add, 20, 6446, 21);
  g->Binary(ynn_binary_pow, 21, 6448, 22);
  g->Binary(ynn_binary_multiply, 18, 22, 23);
  g->Convert(6980, 25);
  g->Binary(ynn_binary_multiply, 23, 25, 26);
  g->Binary(ynn_binary_add, 3678, 26, 27);
}

// Scope: "Layer7 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1064, 28, {0,0,7,0}, {-1,-1,1,-1});
  g->Reshape(28, 29, {1,1,256});
  g->Binary(ynn_binary_add, 29, 7058, 30);
  g->Binary(ynn_binary_multiply, 30, 6444, 31);
  g->Quantize(27, 32, 0.15832224488258362, 0);
  g->Transpose(6977, 3707, {1,0});
  g->Binary(ynn_binary_multiply, 3704, 3706, 3702);
  g->Dot(32, 3707, YNN_INVALID_VALUE_ID, 3701, 1);
  g->DequantizeTensor(3701, YNN_INVALID_VALUE_ID, 3702, 3703);
  g->QuantizeTensor(3703, 6412, 3705, 33);
  g->Dequantize(33, 34, 0.055118121206760406, 0);
  g->Polynomial(34, 5483, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5483, 5484);
  g->Binary(ynn_binary_add, 5484, 5474, 5481);
  g->Binary(ynn_binary_multiply, 34, 5472, 5482);
  g->Binary(ynn_binary_multiply, 5482, 5481, 36);
  g->Binary(ynn_binary_multiply, 36, 31, 37);
  g->Quantize(37, 38, 0.22834646701812744, 0);
  g->Transpose(6978, 3714, {1,0});
  g->Binary(ynn_binary_multiply, 3711, 3713, 3709);
  g->Dot(38, 3714, YNN_INVALID_VALUE_ID, 3708, 1);
  g->DequantizeTensor(3708, YNN_INVALID_VALUE_ID, 3709, 3710);
  g->QuantizeTensor(3710, 6412, 3712, 39);
  g->Dequantize(39, 40, 0.08292699605226517, 0);
  g->Unary(ynn_unary_square, 40, 41);
  g->Reduce(ynn_reduce_sum, 41, 5486, {2}, true);
  g->ShapeProduct(41, 5485, {2});
  g->Binary(ynn_binary_divide, 5486, 5485, 42);
  g->Binary(ynn_binary_add, 42, 6446, 43);
  g->Binary(ynn_binary_pow, 43, 6448, 44);
  g->Binary(ynn_binary_multiply, 40, 44, 45);
  g->Convert(6981, 47);
  g->Binary(ynn_binary_multiply, 45, 47, 48);
  g->Binary(ynn_binary_add, 27, 48, 49);
  g->Convert(6973, 50);
  g->Binary(ynn_binary_multiply, 49, 50, 51);
}

// Scope: "Layer7"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7(Context& ctx) {
  BuildLayer7Attention(ctx);
  BuildLayer7Mlp(ctx);
  BuildLayer7PerLayerEmbedding(ctx);
}

}  // namespace BuildGemma4DecodeSource
