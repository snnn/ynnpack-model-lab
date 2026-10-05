// Generated YNNPACK builder; do not edit.
#include "gemma4_decode_builder.h"

namespace BuildGemma4DecodeSource {

// Scope: "Layer8 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(59, 60, 0.0820433720946312, 0);
  g->Transpose(6931, 3651, {1,0});
  g->Binary(ynn_binary_multiply, 3648, 3650, 3646);
  g->Dot(60, 3651, YNN_INVALID_VALUE_ID, 3645, 1);
  g->DequantizeTensor(3645, YNN_INVALID_VALUE_ID, 3646, 3647);
  g->QuantizeTensor(3647, 6342, 3649, 61);
  g->Dequantize(61, 62, 0.09251969307661057, 0);
  g->Reshape(62, 63, {1,1,1,256});
  g->Transpose(63, 64, {0,2,1,3});
  g->Unary(ynn_unary_square, 64, 65);
  g->Reduce(ynn_reduce_sum, 65, 5420, {3}, true);
  g->ShapeProduct(65, 5419, {3});
  g->Binary(ynn_binary_divide, 5420, 5419, 66);
  g->Binary(ynn_binary_add, 66, 6376, 67);
  g->Binary(ynn_binary_pow, 67, 6378, 69);
  g->Binary(ynn_binary_multiply, 64, 69, 70);
  g->Convert(6930, 71);
  g->Binary(ynn_binary_multiply, 70, 71, 72);
  g->Slice(72, 73, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(72, 74, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 74, 75);
  g->Concat({75,73}, 76, 3);
  g->Binary(ynn_binary_multiply, 72, 2133, 77);
  g->Binary(ynn_binary_multiply, 76, 2992, 78);
  g->Binary(ynn_binary_add, 77, 78, 80);
  g->Transpose(6935, 3656, {1,0});
  g->Binary(ynn_binary_multiply, 3648, 3655, 3653);
  g->Dot(60, 3656, YNN_INVALID_VALUE_ID, 3652, 1);
  g->DequantizeTensor(3652, YNN_INVALID_VALUE_ID, 3653, 3654);
  g->QuantizeTensor(3654, 6342, 3649, 81);
  g->Dequantize(81, 82, 0.09251969307661057, 0);
  g->Reshape(82, 83, {1,1,1,256});
  g->Transpose(83, 84, {0,2,1,3});
  g->Unary(ynn_unary_square, 84, 85);
  g->Reduce(ynn_reduce_sum, 85, 5422, {3}, true);
  g->ShapeProduct(85, 5421, {3});
  g->Binary(ynn_binary_divide, 5422, 5421, 86);
  g->Binary(ynn_binary_add, 86, 6376, 87);
  g->Binary(ynn_binary_pow, 87, 6378, 88);
  g->Binary(ynn_binary_multiply, 84, 88, 90);
}

// Scope: "Layer8 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(80, 91, 0.006215503439307213, 0);
  g->Append(6356, 91, 7005, 2, s2, slinky::expr(int64_t{1}));
  g->View(7005, 7035, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7035, 92, 0.006215503439307213, 0);
  g->Quantize(90, 93, 0.047244105488061905, 0);
  g->Append(6371, 93, 7020, 2, s2, slinky::expr(int64_t{1}));
  g->View(7020, 7050, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7050, 94, 0.047244105488061905, 0);
}

// Scope: "Layer8 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(6934, 3669, {1,0});
  g->Binary(ynn_binary_multiply, 3648, 3668, 3665);
  g->Dot(60, 3669, YNN_INVALID_VALUE_ID, 3664, 1);
  g->DequantizeTensor(3664, YNN_INVALID_VALUE_ID, 3665, 3666);
  g->QuantizeTensor(3666, 6342, 3667, 96);
  g->Dequantize(96, 97, 0.1250000149011612, 0);
  g->SplitDim(97, 98, 2, {8,256});
  g->Transpose(98, 99, {0,2,1,3});
  g->Unary(ynn_unary_square, 99, 100);
  g->Reduce(ynn_reduce_sum, 100, 5424, {3}, true);
  g->ShapeProduct(100, 5423, {3});
  g->Binary(ynn_binary_divide, 5424, 5423, 101);
  g->Binary(ynn_binary_add, 101, 6376, 102);
  g->Binary(ynn_binary_pow, 102, 6378, 103);
  g->Binary(ynn_binary_multiply, 99, 103, 104);
  g->Convert(6933, 105);
  g->Binary(ynn_binary_multiply, 104, 105, 108);
  g->Slice(108, 109, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(108, 110, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 110, 111);
  g->Concat({111,109}, 112, 3);
  g->Binary(ynn_binary_multiply, 108, 2133, 113);
  g->Binary(ynn_binary_multiply, 112, 2992, 114);
  g->Binary(ynn_binary_add, 113, 114, 115);
}

// Scope: "Layer8 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(115, 92, 116, false, true);
  g->Mask(116, 6416, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6416, 5428, {-1}, true);
  g->Binary(ynn_binary_subtract, 6416, 5428, 5425);
  g->Unary(ynn_unary_exp, 5425, 5426);
  g->Reduce(ynn_reduce_sum, 5426, 5429, {-1}, true);
  g->Binary(ynn_binary_divide, 5404, 5429, 5427);
  g->Binary(ynn_binary_multiply, 5426, 5427, 117);
  g->Matmul(117, 94, 118, false, false);
}

// Scope: "Layer8 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(118, 119, {0,2,1,3});
  g->FuseDims(119, 120, 2, 2);
  g->Quantize(120, 121, 0.025713592767715454, 0);
  g->Transpose(6932, 3676, {1,0});
  g->Binary(ynn_binary_multiply, 3673, 3675, 3671);
  g->Dot(121, 3676, YNN_INVALID_VALUE_ID, 3670, 1);
  g->DequantizeTensor(3670, YNN_INVALID_VALUE_ID, 3671, 3672);
  g->QuantizeTensor(3672, 6342, 3674, 122);
  g->Dequantize(122, 123, 0.022537967190146446, 0);
}

// Scope: "Layer8 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 51, 52);
  g->Reduce(ynn_reduce_sum, 52, 5418, {2}, true);
  g->ShapeProduct(52, 5417, {2});
  g->Binary(ynn_binary_divide, 5418, 5417, 53);
  g->Binary(ynn_binary_add, 53, 6376, 54);
  g->Binary(ynn_binary_pow, 54, 6378, 55);
  g->Binary(ynn_binary_multiply, 51, 55, 56);
  g->Convert(6919, 58);
  g->Binary(ynn_binary_multiply, 56, 58, 59);
  BuildLayer8AttentionKvProjection(ctx);
  BuildLayer8AttentionCacheUpdate(ctx);
  BuildLayer8AttentionQueryProjection(ctx);
  BuildLayer8AttentionSdpa(ctx);
  BuildLayer8AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 123, 124);
  g->Reduce(ynn_reduce_sum, 124, 5431, {2}, true);
  g->ShapeProduct(124, 5430, {2});
  g->Binary(ynn_binary_divide, 5431, 5430, 125);
  g->Binary(ynn_binary_add, 125, 6376, 126);
  g->Binary(ynn_binary_pow, 126, 6378, 128);
  g->Binary(ynn_binary_multiply, 123, 128, 129);
  g->Convert(6926, 130);
  g->Binary(ynn_binary_multiply, 129, 130, 131);
  g->Binary(ynn_binary_add, 51, 131, 132);
}

// Scope: "Layer8 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 132, 133);
  g->Reduce(ynn_reduce_sum, 133, 5433, {2}, true);
  g->ShapeProduct(133, 5432, {2});
  g->Binary(ynn_binary_divide, 5433, 5432, 134);
  g->Binary(ynn_binary_add, 134, 6376, 135);
  g->Binary(ynn_binary_pow, 135, 6378, 136);
  g->Binary(ynn_binary_multiply, 132, 136, 137);
  g->Convert(6929, 139);
  g->Binary(ynn_binary_multiply, 137, 139, 140);
  g->Quantize(140, 141, 0.015404289588332176, 0);
  g->Transpose(6923, 3688, {1,0});
  g->Binary(ynn_binary_multiply, 3685, 3687, 3683);
  g->Dot(141, 3688, YNN_INVALID_VALUE_ID, 3682, 1);
  g->DequantizeTensor(3682, YNN_INVALID_VALUE_ID, 3683, 3684);
  g->QuantizeTensor(3684, 6342, 3686, 142);
  g->Dequantize(142, 143, 0.018823828548192978, 0);
  g->Transpose(6922, 3693, {1,0});
  g->Binary(ynn_binary_multiply, 3685, 3692, 3690);
  g->Dot(141, 3693, YNN_INVALID_VALUE_ID, 3689, 1);
  g->DequantizeTensor(3689, YNN_INVALID_VALUE_ID, 3690, 3691);
  g->QuantizeTensor(3691, 6342, 3686, 144);
  g->Dequantize(144, 145, 0.018823828548192978, 0);
  g->Polynomial(145, 5436, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5436, 5437);
  g->Binary(ynn_binary_add, 5437, 5404, 5434);
  g->Binary(ynn_binary_multiply, 145, 5402, 5435);
  g->Binary(ynn_binary_multiply, 5435, 5434, 146);
  g->Binary(ynn_binary_multiply, 143, 146, 147);
  g->Quantize(147, 149, 0.012610738165676594, 0);
  g->Transpose(6921, 3700, {1,0});
  g->Binary(ynn_binary_multiply, 3697, 3699, 3695);
  g->Dot(149, 3700, YNN_INVALID_VALUE_ID, 3694, 1);
  g->DequantizeTensor(3694, YNN_INVALID_VALUE_ID, 3695, 3696);
  g->QuantizeTensor(3696, 6342, 3698, 150);
  g->Dequantize(150, 151, 0.009271269664168358, 0);
  g->Unary(ynn_unary_square, 151, 152);
  g->Reduce(ynn_reduce_sum, 152, 5443, {2}, true);
  g->ShapeProduct(152, 5442, {2});
  g->Binary(ynn_binary_divide, 5443, 5442, 153);
  g->Binary(ynn_binary_add, 153, 6376, 154);
  g->Binary(ynn_binary_pow, 154, 6378, 155);
  g->Binary(ynn_binary_multiply, 151, 155, 156);
  g->Convert(6927, 157);
  g->Binary(ynn_binary_multiply, 156, 157, 158);
  g->Binary(ynn_binary_add, 132, 158, 160);
}

// Scope: "Layer8 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1047, 161, {0,0,8,0}, {-1,-1,1,-1});
  g->Reshape(161, 162, {1,1,256});
  g->Binary(ynn_binary_add, 162, 6989, 163);
  g->Binary(ynn_binary_multiply, 163, 6374, 164);
  g->Quantize(160, 165, 0.19172413647174835, 0);
  g->Transpose(6924, 3707, {1,0});
  g->Binary(ynn_binary_multiply, 3704, 3706, 3702);
  g->Dot(165, 3707, YNN_INVALID_VALUE_ID, 3701, 1);
  g->DequantizeTensor(3701, YNN_INVALID_VALUE_ID, 3702, 3703);
  g->QuantizeTensor(3703, 6342, 3705, 166);
  g->Dequantize(166, 167, 0.11515748500823975, 0);
  g->Polynomial(167, 5446, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5446, 5447);
  g->Binary(ynn_binary_add, 5447, 5404, 5444);
  g->Binary(ynn_binary_multiply, 167, 5402, 5445);
  g->Binary(ynn_binary_multiply, 5445, 5444, 168);
  g->Binary(ynn_binary_multiply, 168, 164, 169);
  g->Quantize(169, 171, 0.787401556968689, 0);
  g->Transpose(6925, 3714, {1,0});
  g->Binary(ynn_binary_multiply, 3711, 3713, 3709);
  g->Dot(171, 3714, YNN_INVALID_VALUE_ID, 3708, 1);
  g->DequantizeTensor(3708, YNN_INVALID_VALUE_ID, 3709, 3710);
  g->QuantizeTensor(3710, 6342, 3712, 172);
  g->Dequantize(172, 173, 0.2950586676597595, 0);
  g->Unary(ynn_unary_square, 173, 174);
  g->Reduce(ynn_reduce_sum, 174, 5449, {2}, true);
  g->ShapeProduct(174, 5448, {2});
  g->Binary(ynn_binary_divide, 5449, 5448, 175);
  g->Binary(ynn_binary_add, 175, 6376, 176);
  g->Binary(ynn_binary_pow, 176, 6378, 177);
  g->Binary(ynn_binary_multiply, 173, 177, 178);
  g->Convert(6928, 179);
  g->Binary(ynn_binary_multiply, 178, 179, 180);
  g->Binary(ynn_binary_add, 160, 180, 182);
  g->Convert(6920, 183);
  g->Binary(ynn_binary_multiply, 182, 183, 184);
}

// Scope: "Layer8"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8(Context& ctx) {
  BuildLayer8Attention(ctx);
  BuildLayer8Mlp(ctx);
  BuildLayer8PerLayerEmbedding(ctx);
}

// Scope: "Layer9 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(191, 193, 0.016753647476434708, 0);
  g->Transpose(6948, 3728, {1,0});
  g->Binary(ynn_binary_multiply, 3725, 3727, 3723);
  g->Dot(193, 3728, YNN_INVALID_VALUE_ID, 3722, 1);
  g->DequantizeTensor(3722, YNN_INVALID_VALUE_ID, 3723, 3724);
  g->QuantizeTensor(3724, 6342, 3726, 194);
  g->Dequantize(194, 195, 0.020177174359560013, 0);
  g->Reshape(195, 196, {1,1,1,512});
  g->Transpose(196, 197, {0,2,1,3});
  g->Unary(ynn_unary_square, 197, 198);
  g->Reduce(ynn_reduce_sum, 198, 5453, {3}, true);
  g->ShapeProduct(198, 5452, {3});
  g->Binary(ynn_binary_divide, 5453, 5452, 199);
  g->Binary(ynn_binary_add, 199, 6376, 200);
  g->Binary(ynn_binary_pow, 200, 6378, 201);
  g->Binary(ynn_binary_multiply, 197, 201, 202);
  g->Convert(6947, 204);
  g->Binary(ynn_binary_multiply, 202, 204, 205);
  g->Slice(205, 206, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(205, 207, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 207, 208);
  g->Concat({208,206}, 209, 3);
  g->Binary(ynn_binary_multiply, 205, 3406, 210);
  g->Binary(ynn_binary_multiply, 209, 3508, 211);
  g->Binary(ynn_binary_add, 210, 211, 212);
  g->Transpose(6952, 3733, {1,0});
  g->Binary(ynn_binary_multiply, 3725, 3732, 3730);
  g->Dot(193, 3733, YNN_INVALID_VALUE_ID, 3729, 1);
  g->DequantizeTensor(3729, YNN_INVALID_VALUE_ID, 3730, 3731);
  g->QuantizeTensor(3731, 6342, 3726, 215);
  g->Dequantize(215, 216, 0.020177174359560013, 0);
  g->Reshape(216, 217, {1,1,1,512});
  g->Transpose(217, 218, {0,2,1,3});
  g->Unary(ynn_unary_square, 218, 219);
  g->Reduce(ynn_reduce_sum, 219, 5457, {3}, true);
  g->ShapeProduct(219, 5456, {3});
  g->Binary(ynn_binary_divide, 5457, 5456, 220);
  g->Binary(ynn_binary_add, 220, 6376, 221);
  g->Binary(ynn_binary_pow, 221, 6378, 222);
  g->Binary(ynn_binary_multiply, 218, 222, 223);
}

// Scope: "Layer9 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(212, 224, 0.0010733711533248425, 0);
  g->Append(6357, 224, 7006, 2, s2, slinky::expr(int64_t{1}));
  g->View(7006, 7036, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7036, 226, 0.0010733711533248425, 0);
  g->Quantize(223, 227, 0.01785714365541935, 0);
  g->Append(6372, 227, 7021, 2, s2, slinky::expr(int64_t{1}));
  g->View(7021, 7051, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7051, 228, 0.01785714365541935, 0);
}

// Scope: "Layer9 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(6951, 3739, {1,0});
  g->Binary(ynn_binary_multiply, 3725, 3738, 3735);
  g->Dot(193, 3739, YNN_INVALID_VALUE_ID, 3734, 1);
  g->DequantizeTensor(3734, YNN_INVALID_VALUE_ID, 3735, 3736);
  g->QuantizeTensor(3736, 6342, 3737, 229);
  g->Dequantize(229, 230, 0.029650600627064705, 0);
  g->SplitDim(230, 232, 2, {8,512});
  g->Transpose(232, 233, {0,2,1,3});
  g->Unary(ynn_unary_square, 233, 234);
  g->Reduce(ynn_reduce_sum, 234, 5459, {3}, true);
  g->ShapeProduct(234, 5458, {3});
  g->Binary(ynn_binary_divide, 5459, 5458, 235);
  g->Binary(ynn_binary_add, 235, 6376, 236);
  g->Binary(ynn_binary_pow, 236, 6378, 237);
  g->Binary(ynn_binary_multiply, 233, 237, 238);
  g->Convert(6950, 239);
  g->Binary(ynn_binary_multiply, 238, 239, 240);
  g->Slice(240, 241, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(240, 243, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 243, 244);
  g->Concat({244,241}, 245, 3);
  g->Binary(ynn_binary_multiply, 240, 3406, 246);
  g->Binary(ynn_binary_multiply, 245, 3508, 247);
  g->Binary(ynn_binary_add, 246, 247, 248);
}

// Scope: "Layer9 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(248, 226, 249, false, true);
  g->Mask(249, 6417, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 6417, 5463, {-1}, true);
  g->Binary(ynn_binary_subtract, 6417, 5463, 5460);
  g->Unary(ynn_unary_exp, 5460, 5461);
  g->Reduce(ynn_reduce_sum, 5461, 5464, {-1}, true);
  g->Binary(ynn_binary_divide, 5404, 5464, 5462);
  g->Binary(ynn_binary_multiply, 5461, 5462, 250);
  g->Matmul(250, 228, 251, false, false);
}

// Scope: "Layer9 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(251, 253, {0,2,1,3});
  g->FuseDims(253, 254, 2, 2);
  g->Quantize(254, 255, 0.017962608486413956, 0);
  g->Transpose(6949, 3746, {1,0});
  g->Binary(ynn_binary_multiply, 3743, 3745, 3741);
  g->Dot(255, 3746, YNN_INVALID_VALUE_ID, 3740, 1);
  g->DequantizeTensor(3740, YNN_INVALID_VALUE_ID, 3741, 3742);
  g->QuantizeTensor(3742, 6342, 3744, 256);
  g->Dequantize(256, 257, 0.02776472456753254, 0);
}

// Scope: "Layer9 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 184, 185);
  g->Reduce(ynn_reduce_sum, 185, 5451, {2}, true);
  g->ShapeProduct(185, 5450, {2});
  g->Binary(ynn_binary_divide, 5451, 5450, 186);
  g->Binary(ynn_binary_add, 186, 6376, 187);
  g->Binary(ynn_binary_pow, 187, 6378, 188);
  g->Binary(ynn_binary_multiply, 184, 188, 189);
  g->Convert(6936, 190);
  g->Binary(ynn_binary_multiply, 189, 190, 191);
  BuildLayer9AttentionKvProjection(ctx);
  BuildLayer9AttentionCacheUpdate(ctx);
  BuildLayer9AttentionQueryProjection(ctx);
  BuildLayer9AttentionSdpa(ctx);
  BuildLayer9AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 257, 258);
  g->Reduce(ynn_reduce_sum, 258, 5466, {2}, true);
  g->ShapeProduct(258, 5465, {2});
  g->Binary(ynn_binary_divide, 5466, 5465, 259);
  g->Binary(ynn_binary_add, 259, 6376, 260);
  g->Binary(ynn_binary_pow, 260, 6378, 261);
  g->Binary(ynn_binary_multiply, 257, 261, 262);
  g->Convert(6943, 264);
  g->Binary(ynn_binary_multiply, 262, 264, 265);
  g->Binary(ynn_binary_add, 184, 265, 266);
}

// Scope: "Layer9 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 266, 267);
  g->Reduce(ynn_reduce_sum, 267, 5468, {2}, true);
  g->ShapeProduct(267, 5467, {2});
  g->Binary(ynn_binary_divide, 5468, 5467, 268);
  g->Binary(ynn_binary_add, 268, 6376, 269);
  g->Binary(ynn_binary_pow, 269, 6378, 270);
  g->Binary(ynn_binary_multiply, 266, 270, 271);
  g->Convert(6946, 272);
  g->Binary(ynn_binary_multiply, 271, 272, 273);
  g->Quantize(273, 275, 0.028379227966070175, 0);
  g->Transpose(6940, 3753, {1,0});
  g->Binary(ynn_binary_multiply, 3750, 3752, 3748);
  g->Dot(275, 3753, YNN_INVALID_VALUE_ID, 3747, 1);
  g->DequantizeTensor(3747, YNN_INVALID_VALUE_ID, 3748, 3749);
  g->QuantizeTensor(3749, 6342, 3751, 276);
  g->Dequantize(276, 277, 0.01556349452584982, 0);
  g->Transpose(6939, 3758, {1,0});
  g->Binary(ynn_binary_multiply, 3750, 3757, 3755);
  g->Dot(275, 3758, YNN_INVALID_VALUE_ID, 3754, 1);
  g->DequantizeTensor(3754, YNN_INVALID_VALUE_ID, 3755, 3756);
  g->QuantizeTensor(3756, 6342, 3751, 278);
  g->Dequantize(278, 279, 0.01556349452584982, 0);
  g->Polynomial(279, 5471, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5471, 5472);
  g->Binary(ynn_binary_add, 5472, 5404, 5469);
  g->Binary(ynn_binary_multiply, 279, 5402, 5470);
  g->Binary(ynn_binary_multiply, 5470, 5469, 280);
  g->Binary(ynn_binary_multiply, 277, 280, 281);
  g->Quantize(281, 282, 0.011441939510405064, 0);
  g->Transpose(6938, 3765, {1,0});
  g->Binary(ynn_binary_multiply, 3762, 3764, 3760);
  g->Dot(282, 3765, YNN_INVALID_VALUE_ID, 3759, 1);
  g->DequantizeTensor(3759, YNN_INVALID_VALUE_ID, 3760, 3761);
  g->QuantizeTensor(3761, 6342, 3763, 283);
  g->Dequantize(283, 285, 0.005826006643474102, 0);
  g->Unary(ynn_unary_square, 285, 286);
  g->Reduce(ynn_reduce_sum, 286, 5474, {2}, true);
  g->ShapeProduct(286, 5473, {2});
  g->Binary(ynn_binary_divide, 5474, 5473, 287);
  g->Binary(ynn_binary_add, 287, 6376, 288);
  g->Binary(ynn_binary_pow, 288, 6378, 289);
  g->Binary(ynn_binary_multiply, 285, 289, 290);
  g->Convert(6944, 291);
  g->Binary(ynn_binary_multiply, 290, 291, 292);
  g->Binary(ynn_binary_add, 266, 292, 293);
}

// Scope: "Layer9 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1047, 294, {0,0,9,0}, {-1,-1,1,-1});
  g->Reshape(294, 296, {1,1,256});
  g->Binary(ynn_binary_add, 296, 6990, 297);
  g->Binary(ynn_binary_multiply, 297, 6374, 298);
  g->Quantize(293, 299, 0.22249335050582886, 0);
  g->Transpose(6941, 3772, {1,0});
  g->Binary(ynn_binary_multiply, 3769, 3771, 3767);
  g->Dot(299, 3772, YNN_INVALID_VALUE_ID, 3766, 1);
  g->DequantizeTensor(3766, YNN_INVALID_VALUE_ID, 3767, 3768);
  g->QuantizeTensor(3768, 6342, 3770, 300);
  g->Dequantize(300, 301, 0.04404528811573982, 0);
  g->Polynomial(301, 5477, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5477, 5478);
  g->Binary(ynn_binary_add, 5478, 5404, 5475);
  g->Binary(ynn_binary_multiply, 301, 5402, 5476);
  g->Binary(ynn_binary_multiply, 5476, 5475, 302);
  g->Binary(ynn_binary_multiply, 302, 298, 303);
  g->Quantize(303, 304, 0.12598426640033722, 0);
  g->Transpose(6942, 3779, {1,0});
  g->Binary(ynn_binary_multiply, 3776, 3778, 3774);
  g->Dot(304, 3779, YNN_INVALID_VALUE_ID, 3773, 1);
  g->DequantizeTensor(3773, YNN_INVALID_VALUE_ID, 3774, 3775);
  g->QuantizeTensor(3775, 6342, 3777, 305);
  g->Dequantize(305, 307, 0.10531344264745712, 0);
  g->Unary(ynn_unary_square, 307, 308);
  g->Reduce(ynn_reduce_sum, 308, 5480, {2}, true);
  g->ShapeProduct(308, 5479, {2});
  g->Binary(ynn_binary_divide, 5480, 5479, 309);
  g->Binary(ynn_binary_add, 309, 6376, 310);
  g->Binary(ynn_binary_pow, 310, 6378, 311);
  g->Binary(ynn_binary_multiply, 307, 311, 312);
  g->Convert(6945, 313);
  g->Binary(ynn_binary_multiply, 312, 313, 314);
  g->Binary(ynn_binary_add, 293, 314, 315);
  g->Convert(6937, 316);
  g->Binary(ynn_binary_multiply, 315, 316, 319);
}

// Scope: "Layer9"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9(Context& ctx) {
  BuildLayer9Attention(ctx);
  BuildLayer9Mlp(ctx);
  BuildLayer9PerLayerEmbedding(ctx);
}

// Scope: "Layer10 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(326, 327, 0.15428009629249573, 0);
  g->Transpose(6464, 3786, {1,0});
  g->Binary(ynn_binary_multiply, 3783, 3785, 3781);
  g->Dot(327, 3786, YNN_INVALID_VALUE_ID, 3780, 1);
  g->DequantizeTensor(3780, YNN_INVALID_VALUE_ID, 3781, 3782);
  g->QuantizeTensor(3782, 6342, 3784, 328);
  g->Dequantize(328, 330, 0.19881890714168549, 0);
  g->Reshape(330, 331, {1,1,1,256});
  g->Transpose(331, 332, {0,2,1,3});
  g->Unary(ynn_unary_square, 332, 333);
  g->Reduce(ynn_reduce_sum, 333, 5484, {3}, true);
  g->ShapeProduct(333, 5483, {3});
  g->Binary(ynn_binary_divide, 5484, 5483, 334);
  g->Binary(ynn_binary_add, 334, 6376, 335);
  g->Binary(ynn_binary_pow, 335, 6378, 336);
  g->Binary(ynn_binary_multiply, 332, 336, 337);
  g->Convert(6463, 338);
  g->Binary(ynn_binary_multiply, 337, 338, 339);
  g->Slice(339, 341, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(339, 342, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 342, 343);
  g->Concat({343,341}, 344, 3);
  g->Binary(ynn_binary_multiply, 339, 2133, 345);
  g->Binary(ynn_binary_multiply, 344, 2992, 346);
  g->Binary(ynn_binary_add, 345, 346, 347);
  g->Transpose(6468, 3798, {1,0});
  g->Binary(ynn_binary_multiply, 3783, 3797, 3795);
  g->Dot(327, 3798, YNN_INVALID_VALUE_ID, 3794, 1);
  g->DequantizeTensor(3794, YNN_INVALID_VALUE_ID, 3795, 3796);
  g->QuantizeTensor(3796, 6342, 3784, 348);
  g->Dequantize(348, 349, 0.19881890714168549, 0);
  g->Reshape(349, 351, {1,1,1,256});
  g->Transpose(351, 352, {0,2,1,3});
  g->Unary(ynn_unary_square, 352, 353);
  g->Reduce(ynn_reduce_sum, 353, 5486, {3}, true);
  g->ShapeProduct(353, 5485, {3});
  g->Binary(ynn_binary_divide, 5486, 5485, 354);
  g->Binary(ynn_binary_add, 354, 6376, 355);
  g->Binary(ynn_binary_pow, 355, 6378, 356);
  g->Binary(ynn_binary_multiply, 352, 356, 357);
}

// Scope: "Layer10 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(347, 358, 0.005712664220482111, 0);
  g->Append(6345, 358, 6994, 2, s2, slinky::expr(int64_t{1}));
  g->View(6994, 7024, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7024, 360, 0.005712664220482111, 0);
  g->Quantize(357, 361, 0.047244105488061905, 0);
  g->Append(6360, 361, 7009, 2, s2, slinky::expr(int64_t{1}));
  g->View(7009, 7039, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7039, 362, 0.047244105488061905, 0);
}

// Scope: "Layer10 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(6467, 3804, {1,0});
  g->Binary(ynn_binary_multiply, 3783, 3803, 3800);
  g->Dot(327, 3804, YNN_INVALID_VALUE_ID, 3799, 1);
  g->DequantizeTensor(3799, YNN_INVALID_VALUE_ID, 3800, 3801);
  g->QuantizeTensor(3801, 6342, 3802, 363);
  g->Dequantize(363, 364, 0.3484252095222473, 0);
  g->SplitDim(364, 365, 2, {8,256});
  g->Transpose(365, 366, {0,2,1,3});
  g->Unary(ynn_unary_square, 366, 368);
  g->Reduce(ynn_reduce_sum, 368, 5492, {3}, true);
  g->ShapeProduct(368, 5491, {3});
  g->Binary(ynn_binary_divide, 5492, 5491, 369);
  g->Binary(ynn_binary_add, 369, 6376, 370);
  g->Binary(ynn_binary_pow, 370, 6378, 371);
  g->Binary(ynn_binary_multiply, 366, 371, 372);
  g->Convert(6466, 373);
  g->Binary(ynn_binary_multiply, 372, 373, 374);
  g->Slice(374, 375, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(374, 376, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 376, 377);
  g->Concat({377,375}, 379, 3);
  g->Binary(ynn_binary_multiply, 374, 2133, 380);
  g->Binary(ynn_binary_multiply, 379, 2992, 381);
  g->Binary(ynn_binary_add, 380, 381, 382);
}

// Scope: "Layer10 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(382, 360, 383, false, true);
  g->Mask(383, 6385, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6385, 5496, {-1}, true);
  g->Binary(ynn_binary_subtract, 6385, 5496, 5493);
  g->Unary(ynn_unary_exp, 5493, 5494);
  g->Reduce(ynn_reduce_sum, 5494, 5497, {-1}, true);
  g->Binary(ynn_binary_divide, 5404, 5497, 5495);
  g->Binary(ynn_binary_multiply, 5494, 5495, 384);
  g->Matmul(384, 362, 385, false, false);
}

// Scope: "Layer10 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(385, 386, {0,2,1,3});
  g->FuseDims(386, 387, 2, 2);
  g->Quantize(387, 389, 0.028051190078258514, 0);
  g->Transpose(6465, 3818, {1,0});
  g->Binary(ynn_binary_multiply, 3815, 3817, 3813);
  g->Dot(389, 3818, YNN_INVALID_VALUE_ID, 3812, 1);
  g->DequantizeTensor(3812, YNN_INVALID_VALUE_ID, 3813, 3814);
  g->QuantizeTensor(3814, 6342, 3816, 390);
  g->Dequantize(390, 391, 0.029417896643280983, 0);
}

// Scope: "Layer10 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 319, 320);
  g->Reduce(ynn_reduce_sum, 320, 5482, {2}, true);
  g->ShapeProduct(320, 5481, {2});
  g->Binary(ynn_binary_divide, 5482, 5481, 321);
  g->Binary(ynn_binary_add, 321, 6376, 322);
  g->Binary(ynn_binary_pow, 322, 6378, 323);
  g->Binary(ynn_binary_multiply, 319, 323, 324);
  g->Convert(6452, 325);
  g->Binary(ynn_binary_multiply, 324, 325, 326);
  BuildLayer10AttentionKvProjection(ctx);
  BuildLayer10AttentionCacheUpdate(ctx);
  BuildLayer10AttentionQueryProjection(ctx);
  BuildLayer10AttentionSdpa(ctx);
  BuildLayer10AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 391, 392);
  g->Reduce(ynn_reduce_sum, 392, 5499, {2}, true);
  g->ShapeProduct(392, 5498, {2});
  g->Binary(ynn_binary_divide, 5499, 5498, 393);
  g->Binary(ynn_binary_add, 393, 6376, 394);
  g->Binary(ynn_binary_pow, 394, 6378, 395);
  g->Binary(ynn_binary_multiply, 391, 395, 396);
  g->Convert(6459, 397);
  g->Binary(ynn_binary_multiply, 396, 397, 398);
  g->Binary(ynn_binary_add, 319, 398, 400);
}

// Scope: "Layer10 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 400, 401);
  g->Reduce(ynn_reduce_sum, 401, 5501, {2}, true);
  g->ShapeProduct(401, 5500, {2});
  g->Binary(ynn_binary_divide, 5501, 5500, 402);
  g->Binary(ynn_binary_add, 402, 6376, 403);
  g->Binary(ynn_binary_pow, 403, 6378, 404);
  g->Binary(ynn_binary_multiply, 400, 404, 405);
  g->Convert(6462, 406);
  g->Binary(ynn_binary_multiply, 405, 406, 407);
  g->Quantize(407, 408, 0.018714377656579018, 0);
  g->Transpose(6456, 3825, {1,0});
  g->Binary(ynn_binary_multiply, 3822, 3824, 3820);
  g->Dot(408, 3825, YNN_INVALID_VALUE_ID, 3819, 1);
  g->DequantizeTensor(3819, YNN_INVALID_VALUE_ID, 3820, 3821);
  g->QuantizeTensor(3821, 6342, 3823, 409);
  g->Dequantize(409, 411, 0.01808563992381096, 0);
  g->Transpose(6455, 3830, {1,0});
  g->Binary(ynn_binary_multiply, 3822, 3829, 3827);
  g->Dot(408, 3830, YNN_INVALID_VALUE_ID, 3826, 1);
  g->DequantizeTensor(3826, YNN_INVALID_VALUE_ID, 3827, 3828);
  g->QuantizeTensor(3828, 6342, 3823, 412);
  g->Dequantize(412, 413, 0.01808563992381096, 0);
  g->Polynomial(413, 5504, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5504, 5505);
  g->Binary(ynn_binary_add, 5505, 5404, 5502);
  g->Binary(ynn_binary_multiply, 413, 5402, 5503);
  g->Binary(ynn_binary_multiply, 5503, 5502, 414);
  g->Binary(ynn_binary_multiply, 411, 414, 415);
  g->Quantize(415, 416, 0.01304134912788868, 0);
  g->Transpose(6454, 3837, {1,0});
  g->Binary(ynn_binary_multiply, 3834, 3836, 3832);
  g->Dot(416, 3837, YNN_INVALID_VALUE_ID, 3831, 1);
  g->DequantizeTensor(3831, YNN_INVALID_VALUE_ID, 3832, 3833);
  g->QuantizeTensor(3833, 6342, 3835, 417);
  g->Dequantize(417, 418, 0.011867290362715721, 0);
  g->Unary(ynn_unary_square, 418, 419);
  g->Reduce(ynn_reduce_sum, 419, 5509, {2}, true);
  g->ShapeProduct(419, 5508, {2});
  g->Binary(ynn_binary_divide, 5509, 5508, 422);
  g->Binary(ynn_binary_add, 422, 6376, 423);
  g->Binary(ynn_binary_pow, 423, 6378, 424);
  g->Binary(ynn_binary_multiply, 418, 424, 425);
  g->Convert(6460, 426);
  g->Binary(ynn_binary_multiply, 425, 426, 427);
  g->Binary(ynn_binary_add, 400, 427, 428);
}

// Scope: "Layer10 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1047, 429, {0,0,10,0}, {-1,-1,1,-1});
  g->Reshape(429, 430, {1,1,256});
  g->Binary(ynn_binary_add, 430, 6958, 431);
  g->Binary(ynn_binary_multiply, 431, 6374, 433);
  g->Quantize(428, 434, 0.14669467508792877, 0);
  g->Transpose(6457, 3844, {1,0});
  g->Binary(ynn_binary_multiply, 3841, 3843, 3839);
  g->Dot(434, 3844, YNN_INVALID_VALUE_ID, 3838, 1);
  g->DequantizeTensor(3838, YNN_INVALID_VALUE_ID, 3839, 3840);
  g->QuantizeTensor(3840, 6342, 3842, 435);
  g->Dequantize(435, 436, 0.038631901144981384, 0);
  g->Polynomial(436, 5512, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5512, 5513);
  g->Binary(ynn_binary_add, 5513, 5404, 5510);
  g->Binary(ynn_binary_multiply, 436, 5402, 5511);
  g->Binary(ynn_binary_multiply, 5511, 5510, 437);
  g->Binary(ynn_binary_multiply, 437, 433, 438);
  g->Quantize(438, 439, 0.05610237270593643, 0);
  g->Transpose(6458, 3851, {1,0});
  g->Binary(ynn_binary_multiply, 3848, 3850, 3846);
  g->Dot(439, 3851, YNN_INVALID_VALUE_ID, 3845, 1);
  g->DequantizeTensor(3845, YNN_INVALID_VALUE_ID, 3846, 3847);
  g->QuantizeTensor(3847, 6342, 3849, 440);
  g->Dequantize(440, 441, 0.041538726538419724, 0);
  g->Unary(ynn_unary_square, 441, 442);
  g->Reduce(ynn_reduce_sum, 442, 5515, {2}, true);
  g->ShapeProduct(442, 5514, {2});
  g->Binary(ynn_binary_divide, 5515, 5514, 444);
  g->Binary(ynn_binary_add, 444, 6376, 445);
  g->Binary(ynn_binary_pow, 445, 6378, 446);
  g->Binary(ynn_binary_multiply, 441, 446, 447);
  g->Convert(6461, 448);
  g->Binary(ynn_binary_multiply, 447, 448, 449);
  g->Binary(ynn_binary_add, 428, 449, 450);
  g->Convert(6453, 451);
  g->Binary(ynn_binary_multiply, 450, 451, 452);
}

// Scope: "Layer10"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10(Context& ctx) {
  BuildLayer10Attention(ctx);
  BuildLayer10Mlp(ctx);
  BuildLayer10PerLayerEmbedding(ctx);
}

// Scope: "Layer11 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(460, 461, 0.11506716161966324, 0);
  g->Transpose(6481, 3858, {1,0});
  g->Binary(ynn_binary_multiply, 3855, 3857, 3853);
  g->Dot(461, 3858, YNN_INVALID_VALUE_ID, 3852, 1);
  g->DequantizeTensor(3852, YNN_INVALID_VALUE_ID, 3853, 3854);
  g->QuantizeTensor(3854, 6342, 3856, 462);
  g->Dequantize(462, 463, 0.12696851789951324, 0);
  g->Reshape(463, 464, {1,1,1,256});
  g->Transpose(464, 466, {0,2,1,3});
  g->Unary(ynn_unary_square, 466, 467);
  g->Reduce(ynn_reduce_sum, 467, 5519, {3}, true);
  g->ShapeProduct(467, 5518, {3});
  g->Binary(ynn_binary_divide, 5519, 5518, 468);
  g->Binary(ynn_binary_add, 468, 6376, 469);
  g->Binary(ynn_binary_pow, 469, 6378, 470);
  g->Binary(ynn_binary_multiply, 466, 470, 471);
  g->Convert(6480, 472);
  g->Binary(ynn_binary_multiply, 471, 472, 473);
  g->Slice(473, 474, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(473, 475, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 475, 477);
  g->Concat({477,474}, 478, 3);
  g->Binary(ynn_binary_multiply, 473, 2133, 479);
  g->Binary(ynn_binary_multiply, 478, 2992, 480);
  g->Binary(ynn_binary_add, 479, 480, 481);
  g->Transpose(6485, 3863, {1,0});
  g->Binary(ynn_binary_multiply, 3855, 3862, 3860);
  g->Dot(461, 3863, YNN_INVALID_VALUE_ID, 3859, 1);
  g->DequantizeTensor(3859, YNN_INVALID_VALUE_ID, 3860, 3861);
  g->QuantizeTensor(3861, 6342, 3856, 482);
  g->Dequantize(482, 483, 0.12696851789951324, 0);
  g->Reshape(483, 484, {1,1,1,256});
  g->Transpose(484, 485, {0,2,1,3});
  g->Unary(ynn_unary_square, 485, 487);
  g->Reduce(ynn_reduce_sum, 487, 5521, {3}, true);
  g->ShapeProduct(487, 5520, {3});
  g->Binary(ynn_binary_divide, 5521, 5520, 488);
  g->Binary(ynn_binary_add, 488, 6376, 489);
  g->Binary(ynn_binary_pow, 489, 6378, 490);
  g->Binary(ynn_binary_multiply, 485, 490, 491);
}

// Scope: "Layer11 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(481, 492, 0.005907459184527397, 0);
  g->Append(6346, 492, 6995, 2, s2, slinky::expr(int64_t{1}));
  g->View(6995, 7025, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7025, 493, 0.005907459184527397, 0);
  g->Quantize(491, 494, 0.047244105488061905, 0);
  g->Append(6361, 494, 7010, 2, s2, slinky::expr(int64_t{1}));
  g->View(7010, 7040, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7040, 496, 0.047244105488061905, 0);
}

// Scope: "Layer11 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(6484, 3869, {1,0});
  g->Binary(ynn_binary_multiply, 3855, 3868, 3865);
  g->Dot(461, 3869, YNN_INVALID_VALUE_ID, 3864, 1);
  g->DequantizeTensor(3864, YNN_INVALID_VALUE_ID, 3865, 3866);
  g->QuantizeTensor(3866, 6342, 3867, 497);
  g->Dequantize(497, 498, 0.2736220359802246, 0);
  g->SplitDim(498, 499, 2, {8,256});
  g->Transpose(499, 500, {0,2,1,3});
  g->Unary(ynn_unary_square, 500, 501);
  g->Reduce(ynn_reduce_sum, 501, 5523, {3}, true);
  g->ShapeProduct(501, 5522, {3});
  g->Binary(ynn_binary_divide, 5523, 5522, 502);
  g->Binary(ynn_binary_add, 502, 6376, 504);
  g->Binary(ynn_binary_pow, 504, 6378, 505);
  g->Binary(ynn_binary_multiply, 500, 505, 506);
  g->Convert(6483, 507);
  g->Binary(ynn_binary_multiply, 506, 507, 508);
  g->Slice(508, 509, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(508, 510, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 510, 511);
  g->Concat({511,509}, 512, 3);
  g->Binary(ynn_binary_multiply, 508, 2133, 513);
  g->Binary(ynn_binary_multiply, 512, 2992, 515);
  g->Binary(ynn_binary_add, 513, 515, 516);
}

// Scope: "Layer11 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(516, 493, 517, false, true);
  g->Mask(517, 6386, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6386, 5527, {-1}, true);
  g->Binary(ynn_binary_subtract, 6386, 5527, 5524);
  g->Unary(ynn_unary_exp, 5524, 5525);
  g->Reduce(ynn_reduce_sum, 5525, 5528, {-1}, true);
  g->Binary(ynn_binary_divide, 5404, 5528, 5526);
  g->Binary(ynn_binary_multiply, 5525, 5526, 518);
  g->Matmul(518, 496, 519, false, false);
}

// Scope: "Layer11 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(519, 520, {0,2,1,3});
  g->FuseDims(520, 521, 2, 2);
  g->Quantize(521, 522, 0.026082687079906464, 0);
  g->Transpose(6482, 3876, {1,0});
  g->Binary(ynn_binary_multiply, 3873, 3875, 3871);
  g->Dot(522, 3876, YNN_INVALID_VALUE_ID, 3870, 1);
  g->DequantizeTensor(3870, YNN_INVALID_VALUE_ID, 3871, 3872);
  g->QuantizeTensor(3872, 6342, 3874, 523);
  g->Dequantize(523, 526, 0.028822369873523712, 0);
}

// Scope: "Layer11 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 452, 453);
  g->Reduce(ynn_reduce_sum, 453, 5517, {2}, true);
  g->ShapeProduct(453, 5516, {2});
  g->Binary(ynn_binary_divide, 5517, 5516, 455);
  g->Binary(ynn_binary_add, 455, 6376, 456);
  g->Binary(ynn_binary_pow, 456, 6378, 457);
  g->Binary(ynn_binary_multiply, 452, 457, 458);
  g->Convert(6469, 459);
  g->Binary(ynn_binary_multiply, 458, 459, 460);
  BuildLayer11AttentionKvProjection(ctx);
  BuildLayer11AttentionCacheUpdate(ctx);
  BuildLayer11AttentionQueryProjection(ctx);
  BuildLayer11AttentionSdpa(ctx);
  BuildLayer11AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 526, 527);
  g->Reduce(ynn_reduce_sum, 527, 5534, {2}, true);
  g->ShapeProduct(527, 5533, {2});
  g->Binary(ynn_binary_divide, 5534, 5533, 528);
  g->Binary(ynn_binary_add, 528, 6376, 529);
  g->Binary(ynn_binary_pow, 529, 6378, 530);
  g->Binary(ynn_binary_multiply, 526, 530, 531);
  g->Convert(6476, 532);
  g->Binary(ynn_binary_multiply, 531, 532, 533);
  g->Binary(ynn_binary_add, 452, 533, 534);
}

// Scope: "Layer11 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 534, 535);
  g->Reduce(ynn_reduce_sum, 535, 5536, {2}, true);
  g->ShapeProduct(535, 5535, {2});
  g->Binary(ynn_binary_divide, 5536, 5535, 537);
  g->Binary(ynn_binary_add, 537, 6376, 538);
  g->Binary(ynn_binary_pow, 538, 6378, 539);
  g->Binary(ynn_binary_multiply, 534, 539, 540);
  g->Convert(6479, 541);
  g->Binary(ynn_binary_multiply, 540, 541, 542);
  g->Quantize(542, 543, 0.015670500695705414, 0);
  g->Transpose(6473, 3883, {1,0});
  g->Binary(ynn_binary_multiply, 3880, 3882, 3878);
  g->Dot(543, 3883, YNN_INVALID_VALUE_ID, 3877, 1);
  g->DequantizeTensor(3877, YNN_INVALID_VALUE_ID, 3878, 3879);
  g->QuantizeTensor(3879, 6342, 3881, 544);
  g->Dequantize(544, 545, 0.015255915932357311, 0);
  g->Transpose(6472, 3888, {1,0});
  g->Binary(ynn_binary_multiply, 3880, 3887, 3885);
  g->Dot(543, 3888, YNN_INVALID_VALUE_ID, 3884, 1);
  g->DequantizeTensor(3884, YNN_INVALID_VALUE_ID, 3885, 3886);
  g->QuantizeTensor(3886, 6342, 3881, 547);
  g->Dequantize(547, 548, 0.015255915932357311, 0);
  g->Polynomial(548, 5539, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5539, 5540);
  g->Binary(ynn_binary_add, 5540, 5404, 5537);
  g->Binary(ynn_binary_multiply, 548, 5402, 5538);
  g->Binary(ynn_binary_multiply, 5538, 5537, 549);
  g->Binary(ynn_binary_multiply, 545, 549, 550);
  g->Quantize(550, 551, 0.011195876635611057, 0);
  g->Transpose(6471, 3895, {1,0});
  g->Binary(ynn_binary_multiply, 3892, 3894, 3890);
  g->Dot(551, 3895, YNN_INVALID_VALUE_ID, 3889, 1);
  g->DequantizeTensor(3889, YNN_INVALID_VALUE_ID, 3890, 3891);
  g->QuantizeTensor(3891, 6342, 3893, 552);
  g->Dequantize(552, 553, 0.004389102105051279, 0);
  g->Unary(ynn_unary_square, 553, 554);
  g->Reduce(ynn_reduce_sum, 554, 5542, {2}, true);
  g->ShapeProduct(554, 5541, {2});
  g->Binary(ynn_binary_divide, 5542, 5541, 555);
  g->Binary(ynn_binary_add, 555, 6376, 556);
  g->Binary(ynn_binary_pow, 556, 6378, 558);
  g->Binary(ynn_binary_multiply, 553, 558, 559);
  g->Convert(6477, 560);
  g->Binary(ynn_binary_multiply, 559, 560, 561);
  g->Binary(ynn_binary_add, 534, 561, 562);
}

// Scope: "Layer11 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1047, 563, {0,0,11,0}, {-1,-1,1,-1});
  g->Reshape(563, 564, {1,1,256});
  g->Binary(ynn_binary_add, 564, 6959, 565);
  g->Binary(ynn_binary_multiply, 565, 6374, 566);
  g->Quantize(562, 567, 0.1750430017709732, 0);
  g->Transpose(6474, 3902, {1,0});
  g->Binary(ynn_binary_multiply, 3899, 3901, 3897);
  g->Dot(567, 3902, YNN_INVALID_VALUE_ID, 3896, 1);
  g->DequantizeTensor(3896, YNN_INVALID_VALUE_ID, 3897, 3898);
  g->QuantizeTensor(3898, 6342, 3900, 569);
  g->Dequantize(569, 570, 0.07529528439044952, 0);
  g->Polynomial(570, 5545, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5545, 5546);
  g->Binary(ynn_binary_add, 5546, 5404, 5543);
  g->Binary(ynn_binary_multiply, 570, 5402, 5544);
  g->Binary(ynn_binary_multiply, 5544, 5543, 571);
  g->Binary(ynn_binary_multiply, 571, 566, 572);
  g->Quantize(572, 573, 0.15846458077430725, 0);
  g->Transpose(6475, 3909, {1,0});
  g->Binary(ynn_binary_multiply, 3906, 3908, 3904);
  g->Dot(573, 3909, YNN_INVALID_VALUE_ID, 3903, 1);
  g->DequantizeTensor(3903, YNN_INVALID_VALUE_ID, 3904, 3905);
  g->QuantizeTensor(3905, 6342, 3907, 574);
  g->Dequantize(574, 575, 0.1771666705608368, 0);
  g->Unary(ynn_unary_square, 575, 576);
  g->Reduce(ynn_reduce_sum, 576, 5548, {2}, true);
  g->ShapeProduct(576, 5547, {2});
  g->Binary(ynn_binary_divide, 5548, 5547, 577);
  g->Binary(ynn_binary_add, 577, 6376, 578);
  g->Binary(ynn_binary_pow, 578, 6378, 580);
  g->Binary(ynn_binary_multiply, 575, 580, 581);
  g->Convert(6478, 582);
  g->Binary(ynn_binary_multiply, 581, 582, 583);
  g->Binary(ynn_binary_add, 562, 583, 584);
  g->Convert(6470, 585);
  g->Binary(ynn_binary_multiply, 584, 585, 586);
}

// Scope: "Layer11"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11(Context& ctx) {
  BuildLayer11Attention(ctx);
  BuildLayer11Mlp(ctx);
  BuildLayer11PerLayerEmbedding(ctx);
}

// Scope: "Layer12 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(594, 595, 0.08767248690128326, 0);
  g->Transpose(6498, 3916, {1,0});
  g->Binary(ynn_binary_multiply, 3913, 3915, 3911);
  g->Dot(595, 3916, YNN_INVALID_VALUE_ID, 3910, 1);
  g->DequantizeTensor(3910, YNN_INVALID_VALUE_ID, 3911, 3912);
  g->QuantizeTensor(3912, 6342, 3914, 596);
  g->Dequantize(596, 597, 0.08070866763591766, 0);
  g->Reshape(597, 598, {1,1,1,256});
  g->Transpose(598, 599, {0,2,1,3});
  g->Unary(ynn_unary_square, 599, 600);
  g->Reduce(ynn_reduce_sum, 600, 5552, {3}, true);
  g->ShapeProduct(600, 5551, {3});
  g->Binary(ynn_binary_divide, 5552, 5551, 602);
  g->Binary(ynn_binary_add, 602, 6376, 603);
  g->Binary(ynn_binary_pow, 603, 6378, 604);
  g->Binary(ynn_binary_multiply, 599, 604, 605);
  g->Convert(6497, 606);
  g->Binary(ynn_binary_multiply, 605, 606, 607);
  g->Slice(607, 608, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(607, 609, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 609, 610);
  g->Concat({610,608}, 611, 3);
  g->Binary(ynn_binary_multiply, 607, 2133, 613);
  g->Binary(ynn_binary_multiply, 611, 2992, 614);
  g->Binary(ynn_binary_add, 613, 614, 615);
  g->Transpose(6502, 3928, {1,0});
  g->Binary(ynn_binary_multiply, 3913, 3927, 3925);
  g->Dot(595, 3928, YNN_INVALID_VALUE_ID, 3924, 1);
  g->DequantizeTensor(3924, YNN_INVALID_VALUE_ID, 3925, 3926);
  g->QuantizeTensor(3926, 6342, 3914, 616);
  g->Dequantize(616, 617, 0.08070866763591766, 0);
  g->Reshape(617, 618, {1,1,1,256});
  g->Transpose(618, 619, {0,2,1,3});
  g->Unary(ynn_unary_square, 619, 620);
  g->Reduce(ynn_reduce_sum, 620, 5554, {3}, true);
  g->ShapeProduct(620, 5553, {3});
  g->Binary(ynn_binary_divide, 5554, 5553, 621);
  g->Binary(ynn_binary_add, 621, 6376, 623);
  g->Binary(ynn_binary_pow, 623, 6378, 624);
  g->Binary(ynn_binary_multiply, 619, 624, 625);
}

// Scope: "Layer12 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(615, 626, 0.005788442213088274, 0);
  g->Append(6347, 626, 6996, 2, s2, slinky::expr(int64_t{1}));
  g->View(6996, 7026, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7026, 627, 0.005788442213088274, 0);
  g->Quantize(625, 628, 0.047244105488061905, 0);
  g->Append(6362, 628, 7011, 2, s2, slinky::expr(int64_t{1}));
  g->View(7011, 7041, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7041, 631, 0.047244105488061905, 0);
}

// Scope: "Layer12 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(6501, 3934, {1,0});
  g->Binary(ynn_binary_multiply, 3913, 3933, 3930);
  g->Dot(595, 3934, YNN_INVALID_VALUE_ID, 3929, 1);
  g->DequantizeTensor(3929, YNN_INVALID_VALUE_ID, 3930, 3931);
  g->QuantizeTensor(3931, 6342, 3932, 632);
  g->Dequantize(632, 633, 0.12795276939868927, 0);
  g->SplitDim(633, 634, 2, {8,256});
  g->Transpose(634, 635, {0,2,1,3});
  g->Unary(ynn_unary_square, 635, 636);
  g->Reduce(ynn_reduce_sum, 636, 5556, {3}, true);
  g->ShapeProduct(636, 5555, {3});
  g->Binary(ynn_binary_divide, 5556, 5555, 637);
  g->Binary(ynn_binary_add, 637, 6376, 638);
  g->Binary(ynn_binary_pow, 638, 6378, 639);
  g->Binary(ynn_binary_multiply, 635, 639, 641);
  g->Convert(6500, 642);
  g->Binary(ynn_binary_multiply, 641, 642, 643);
  g->Slice(643, 644, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(643, 645, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 645, 646);
  g->Concat({646,644}, 647, 3);
  g->Binary(ynn_binary_multiply, 643, 2133, 648);
  g->Binary(ynn_binary_multiply, 647, 2992, 649);
  g->Binary(ynn_binary_add, 648, 649, 650);
}

// Scope: "Layer12 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(650, 627, 652, false, true);
  g->Mask(652, 6387, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6387, 5562, {-1}, true);
  g->Binary(ynn_binary_subtract, 6387, 5562, 5559);
  g->Unary(ynn_unary_exp, 5559, 5560);
  g->Reduce(ynn_reduce_sum, 5560, 5563, {-1}, true);
  g->Binary(ynn_binary_divide, 5404, 5563, 5561);
  g->Binary(ynn_binary_multiply, 5560, 5561, 653);
  g->Matmul(653, 631, 654, false, false);
}

// Scope: "Layer12 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(654, 655, {0,2,1,3});
  g->FuseDims(655, 656, 2, 2);
  g->Quantize(656, 657, 0.028543315827846527, 0);
  g->Transpose(6499, 3941, {1,0});
  g->Binary(ynn_binary_multiply, 3938, 3940, 3936);
  g->Dot(657, 3941, YNN_INVALID_VALUE_ID, 3935, 1);
  g->DequantizeTensor(3935, YNN_INVALID_VALUE_ID, 3936, 3937);
  g->QuantizeTensor(3937, 6342, 3939, 658);
  g->Dequantize(658, 659, 0.021804405376315117, 0);
}

// Scope: "Layer12 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 586, 587);
  g->Reduce(ynn_reduce_sum, 587, 5550, {2}, true);
  g->ShapeProduct(587, 5549, {2});
  g->Binary(ynn_binary_divide, 5550, 5549, 588);
  g->Binary(ynn_binary_add, 588, 6376, 589);
  g->Binary(ynn_binary_pow, 589, 6378, 591);
  g->Binary(ynn_binary_multiply, 586, 591, 592);
  g->Convert(6486, 593);
  g->Binary(ynn_binary_multiply, 592, 593, 594);
  BuildLayer12AttentionKvProjection(ctx);
  BuildLayer12AttentionCacheUpdate(ctx);
  BuildLayer12AttentionQueryProjection(ctx);
  BuildLayer12AttentionSdpa(ctx);
  BuildLayer12AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 659, 660);
  g->Reduce(ynn_reduce_sum, 660, 5565, {2}, true);
  g->ShapeProduct(660, 5564, {2});
  g->Binary(ynn_binary_divide, 5565, 5564, 662);
  g->Binary(ynn_binary_add, 662, 6376, 663);
  g->Binary(ynn_binary_pow, 663, 6378, 664);
  g->Binary(ynn_binary_multiply, 659, 664, 665);
  g->Convert(6493, 666);
  g->Binary(ynn_binary_multiply, 665, 666, 667);
  g->Binary(ynn_binary_add, 586, 667, 668);
}

// Scope: "Layer12 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 668, 669);
  g->Reduce(ynn_reduce_sum, 669, 5567, {2}, true);
  g->ShapeProduct(669, 5566, {2});
  g->Binary(ynn_binary_divide, 5567, 5566, 670);
  g->Binary(ynn_binary_add, 670, 6376, 671);
  g->Binary(ynn_binary_pow, 671, 6378, 673);
  g->Binary(ynn_binary_multiply, 668, 673, 674);
  g->Convert(6496, 675);
  g->Binary(ynn_binary_multiply, 674, 675, 676);
  g->Quantize(676, 677, 0.013748278841376305, 0);
  g->Transpose(6490, 3948, {1,0});
  g->Binary(ynn_binary_multiply, 3945, 3947, 3943);
  g->Dot(677, 3948, YNN_INVALID_VALUE_ID, 3942, 1);
  g->DequantizeTensor(3942, YNN_INVALID_VALUE_ID, 3943, 3944);
  g->QuantizeTensor(3944, 6342, 3946, 678);
  g->Dequantize(678, 679, 0.012795286253094673, 0);
  g->Transpose(6489, 3953, {1,0});
  g->Binary(ynn_binary_multiply, 3945, 3952, 3950);
  g->Dot(677, 3953, YNN_INVALID_VALUE_ID, 3949, 1);
  g->DequantizeTensor(3949, YNN_INVALID_VALUE_ID, 3950, 3951);
  g->QuantizeTensor(3951, 6342, 3946, 680);
  g->Dequantize(680, 681, 0.012795286253094673, 0);
  g->Polynomial(681, 5570, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5570, 5571);
  g->Binary(ynn_binary_add, 5571, 5404, 5568);
  g->Binary(ynn_binary_multiply, 681, 5402, 5569);
  g->Binary(ynn_binary_multiply, 5569, 5568, 683);
  g->Binary(ynn_binary_multiply, 679, 683, 684);
  g->Quantize(684, 685, 0.00768947834149003, 0);
  g->Transpose(6488, 3960, {1,0});
  g->Binary(ynn_binary_multiply, 3957, 3959, 3955);
  g->Dot(685, 3960, YNN_INVALID_VALUE_ID, 3954, 1);
  g->DequantizeTensor(3954, YNN_INVALID_VALUE_ID, 3955, 3956);
  g->QuantizeTensor(3956, 6342, 3958, 686);
  g->Dequantize(686, 687, 0.005636297166347504, 0);
  g->Unary(ynn_unary_square, 687, 688);
  g->Reduce(ynn_reduce_sum, 688, 5573, {2}, true);
  g->ShapeProduct(688, 5572, {2});
  g->Binary(ynn_binary_divide, 5573, 5572, 689);
  g->Binary(ynn_binary_add, 689, 6376, 690);
  g->Binary(ynn_binary_pow, 690, 6378, 691);
  g->Binary(ynn_binary_multiply, 687, 691, 692);
  g->Convert(6494, 694);
  g->Binary(ynn_binary_multiply, 692, 694, 695);
  g->Binary(ynn_binary_add, 668, 695, 696);
}

// Scope: "Layer12 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1047, 697, {0,0,12,0}, {-1,-1,1,-1});
  g->Reshape(697, 698, {1,1,256});
  g->Binary(ynn_binary_add, 698, 6960, 699);
  g->Binary(ynn_binary_multiply, 699, 6374, 700);
  g->Quantize(696, 701, 0.19133253395557404, 0);
  g->Transpose(6491, 3966, {1,0});
  g->Binary(ynn_binary_multiply, 3964, 3965, 3962);
  g->Dot(701, 3966, YNN_INVALID_VALUE_ID, 3961, 1);
  g->DequantizeTensor(3961, YNN_INVALID_VALUE_ID, 3962, 3963);
  g->QuantizeTensor(3963, 6342, 3900, 702);
  g->Dequantize(702, 703, 0.07529528439044952, 0);
  g->Polynomial(703, 5576, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5576, 5577);
  g->Binary(ynn_binary_add, 5577, 5404, 5574);
  g->Binary(ynn_binary_multiply, 703, 5402, 5575);
  g->Binary(ynn_binary_multiply, 5575, 5574, 705);
  g->Binary(ynn_binary_multiply, 705, 700, 706);
  g->Quantize(706, 707, 0.12450788170099258, 0);
  g->Transpose(6492, 3973, {1,0});
  g->Binary(ynn_binary_multiply, 3970, 3972, 3968);
  g->Dot(707, 3973, YNN_INVALID_VALUE_ID, 3967, 1);
  g->DequantizeTensor(3967, YNN_INVALID_VALUE_ID, 3968, 3969);
  g->QuantizeTensor(3969, 6342, 3971, 708);
  g->Dequantize(708, 709, 0.12528184056282043, 0);
  g->Unary(ynn_unary_square, 709, 710);
  g->Reduce(ynn_reduce_sum, 710, 5579, {2}, true);
  g->ShapeProduct(710, 5578, {2});
  g->Binary(ynn_binary_divide, 5579, 5578, 711);
  g->Binary(ynn_binary_add, 711, 6376, 712);
  g->Binary(ynn_binary_pow, 712, 6378, 713);
  g->Binary(ynn_binary_multiply, 709, 713, 714);
  g->Convert(6495, 716);
  g->Binary(ynn_binary_multiply, 714, 716, 717);
  g->Binary(ynn_binary_add, 696, 717, 718);
  g->Convert(6487, 719);
  g->Binary(ynn_binary_multiply, 718, 719, 720);
}

// Scope: "Layer12"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12(Context& ctx) {
  BuildLayer12Attention(ctx);
  BuildLayer12Mlp(ctx);
  BuildLayer12PerLayerEmbedding(ctx);
}

// Scope: "Layer13 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(728, 729, 0.02862965501844883, 0);
  g->Transpose(6515, 3980, {1,0});
  g->Binary(ynn_binary_multiply, 3977, 3979, 3975);
  g->Dot(729, 3980, YNN_INVALID_VALUE_ID, 3974, 1);
  g->DequantizeTensor(3974, YNN_INVALID_VALUE_ID, 3975, 3976);
  g->QuantizeTensor(3976, 6342, 3978, 730);
  g->Dequantize(730, 731, 0.035925209522247314, 0);
  g->Reshape(731, 732, {1,1,1,256});
  g->Transpose(732, 733, {0,2,1,3});
  g->Unary(ynn_unary_square, 733, 734);
  g->Reduce(ynn_reduce_sum, 734, 5583, {3}, true);
  g->ShapeProduct(734, 5582, {3});
  g->Binary(ynn_binary_divide, 5583, 5582, 735);
  g->Binary(ynn_binary_add, 735, 6376, 736);
  g->Binary(ynn_binary_pow, 736, 6378, 739);
  g->Binary(ynn_binary_multiply, 733, 739, 740);
  g->Convert(6514, 741);
  g->Binary(ynn_binary_multiply, 740, 741, 742);
  g->Slice(742, 743, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(742, 744, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 744, 745);
  g->Concat({745,743}, 746, 3);
  g->Binary(ynn_binary_multiply, 742, 2133, 747);
  g->Binary(ynn_binary_multiply, 746, 2992, 748);
  g->Binary(ynn_binary_add, 747, 748, 750);
  g->Transpose(6519, 3985, {1,0});
  g->Binary(ynn_binary_multiply, 3977, 3984, 3982);
  g->Dot(729, 3985, YNN_INVALID_VALUE_ID, 3981, 1);
  g->DequantizeTensor(3981, YNN_INVALID_VALUE_ID, 3982, 3983);
  g->QuantizeTensor(3983, 6342, 3978, 751);
  g->Dequantize(751, 752, 0.035925209522247314, 0);
  g->Reshape(752, 753, {1,1,1,256});
  g->Transpose(753, 754, {0,2,1,3});
  g->Unary(ynn_unary_square, 754, 755);
  g->Reduce(ynn_reduce_sum, 755, 5585, {3}, true);
  g->ShapeProduct(755, 5584, {3});
  g->Binary(ynn_binary_divide, 5585, 5584, 756);
  g->Binary(ynn_binary_add, 756, 6376, 757);
  g->Binary(ynn_binary_pow, 757, 6378, 758);
  g->Binary(ynn_binary_multiply, 754, 758, 760);
}

// Scope: "Layer13 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(750, 761, 0.0059552486054599285, 0);
  g->Append(6348, 761, 6997, 2, s2, slinky::expr(int64_t{1}));
  g->View(6997, 7027, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7027, 762, 0.0059552486054599285, 0);
  g->Quantize(760, 763, 0.047244105488061905, 0);
  g->Append(6363, 763, 7012, 2, s2, slinky::expr(int64_t{1}));
  g->View(7012, 7042, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7042, 764, 0.047244105488061905, 0);
}

// Scope: "Layer13 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(6518, 3990, {1,0});
  g->Binary(ynn_binary_multiply, 3977, 3989, 3987);
  g->Dot(729, 3990, YNN_INVALID_VALUE_ID, 3986, 1);
  g->DequantizeTensor(3986, YNN_INVALID_VALUE_ID, 3987, 3988);
  g->QuantizeTensor(3988, 6342, 3808, 766);
  g->Dequantize(766, 767, 0.03764764964580536, 0);
  g->SplitDim(767, 768, 2, {8,256});
  g->Transpose(768, 769, {0,2,1,3});
  g->Unary(ynn_unary_square, 769, 770);
  g->Reduce(ynn_reduce_sum, 770, 5587, {3}, true);
  g->ShapeProduct(770, 5586, {3});
  g->Binary(ynn_binary_divide, 5587, 5586, 771);
  g->Binary(ynn_binary_add, 771, 6376, 772);
  g->Binary(ynn_binary_pow, 772, 6378, 773);
  g->Binary(ynn_binary_multiply, 769, 773, 774);
  g->Convert(6517, 775);
  g->Binary(ynn_binary_multiply, 774, 775, 777);
  g->Slice(777, 778, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(777, 779, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 779, 780);
  g->Concat({780,778}, 781, 3);
  g->Binary(ynn_binary_multiply, 777, 2133, 782);
  g->Binary(ynn_binary_multiply, 781, 2992, 783);
  g->Binary(ynn_binary_add, 782, 783, 784);
}

// Scope: "Layer13 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(784, 762, 785, false, true);
  g->Mask(785, 6388, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6388, 5591, {-1}, true);
  g->Binary(ynn_binary_subtract, 6388, 5591, 5588);
  g->Unary(ynn_unary_exp, 5588, 5589);
  g->Reduce(ynn_reduce_sum, 5589, 5592, {-1}, true);
  g->Binary(ynn_binary_divide, 5404, 5592, 5590);
  g->Binary(ynn_binary_multiply, 5589, 5590, 786);
  g->Matmul(786, 764, 787, false, false);
}

// Scope: "Layer13 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(787, 788, {0,2,1,3});
  g->FuseDims(788, 789, 2, 2);
  g->Quantize(789, 790, 0.026205718517303467, 0);
  g->Transpose(6516, 3997, {1,0});
  g->Binary(ynn_binary_multiply, 3994, 3996, 3992);
  g->Dot(790, 3997, YNN_INVALID_VALUE_ID, 3991, 1);
  g->DequantizeTensor(3991, YNN_INVALID_VALUE_ID, 3992, 3993);
  g->QuantizeTensor(3993, 6342, 3995, 791);
  g->Dequantize(791, 792, 0.03592992201447487, 0);
}

// Scope: "Layer13 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 720, 721);
  g->Reduce(ynn_reduce_sum, 721, 5581, {2}, true);
  g->ShapeProduct(721, 5580, {2});
  g->Binary(ynn_binary_divide, 5581, 5580, 722);
  g->Binary(ynn_binary_add, 722, 6376, 723);
  g->Binary(ynn_binary_pow, 723, 6378, 724);
  g->Binary(ynn_binary_multiply, 720, 724, 725);
  g->Convert(6503, 727);
  g->Binary(ynn_binary_multiply, 725, 727, 728);
  BuildLayer13AttentionKvProjection(ctx);
  BuildLayer13AttentionCacheUpdate(ctx);
  BuildLayer13AttentionQueryProjection(ctx);
  BuildLayer13AttentionSdpa(ctx);
  BuildLayer13AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 792, 793);
  g->Reduce(ynn_reduce_sum, 793, 5594, {2}, true);
  g->ShapeProduct(793, 5593, {2});
  g->Binary(ynn_binary_divide, 5594, 5593, 794);
  g->Binary(ynn_binary_add, 794, 6376, 795);
  g->Binary(ynn_binary_pow, 795, 6378, 797);
  g->Binary(ynn_binary_multiply, 792, 797, 798);
  g->Convert(6510, 799);
  g->Binary(ynn_binary_multiply, 798, 799, 800);
  g->Binary(ynn_binary_add, 720, 800, 801);
}

// Scope: "Layer13 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 801, 802);
  g->Reduce(ynn_reduce_sum, 802, 5596, {2}, true);
  g->ShapeProduct(802, 5595, {2});
  g->Binary(ynn_binary_divide, 5596, 5595, 803);
  g->Binary(ynn_binary_add, 803, 6376, 804);
  g->Binary(ynn_binary_pow, 804, 6378, 805);
  g->Binary(ynn_binary_multiply, 801, 805, 806);
  g->Convert(6513, 808);
  g->Binary(ynn_binary_multiply, 806, 808, 809);
  g->Quantize(809, 810, 0.0083004767075181, 0);
  g->Transpose(6507, 4009, {1,0});
  g->Binary(ynn_binary_multiply, 4006, 4008, 4004);
  g->Dot(810, 4009, YNN_INVALID_VALUE_ID, 4003, 1);
  g->DequantizeTensor(4003, YNN_INVALID_VALUE_ID, 4004, 4005);
  g->QuantizeTensor(4005, 6342, 4007, 811);
  g->Dequantize(811, 812, 0.011934065259993076, 0);
  g->Transpose(6506, 4014, {1,0});
  g->Binary(ynn_binary_multiply, 4006, 4013, 4011);
  g->Dot(810, 4014, YNN_INVALID_VALUE_ID, 4010, 1);
  g->DequantizeTensor(4010, YNN_INVALID_VALUE_ID, 4011, 4012);
  g->QuantizeTensor(4012, 6342, 4007, 813);
  g->Dequantize(813, 814, 0.011934065259993076, 0);
  g->Polynomial(814, 5599, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5599, 5600);
  g->Binary(ynn_binary_add, 5600, 5404, 5597);
  g->Binary(ynn_binary_multiply, 814, 5402, 5598);
  g->Binary(ynn_binary_multiply, 5598, 5597, 815);
  g->Binary(ynn_binary_multiply, 812, 815, 816);
  g->Quantize(816, 818, 0.0015532826073467731, 0);
  g->Transpose(6505, 4021, {1,0});
  g->Binary(ynn_binary_multiply, 4018, 4020, 4016);
  g->Dot(818, 4021, YNN_INVALID_VALUE_ID, 4015, 1);
  g->DequantizeTensor(4015, YNN_INVALID_VALUE_ID, 4016, 4017);
  g->QuantizeTensor(4017, 6342, 4019, 819);
  g->Dequantize(819, 820, 0.002153691602870822, 0);
  g->Unary(ynn_unary_square, 820, 821);
  g->Reduce(ynn_reduce_sum, 821, 5602, {2}, true);
  g->ShapeProduct(821, 5601, {2});
  g->Binary(ynn_binary_divide, 5602, 5601, 822);
  g->Binary(ynn_binary_add, 822, 6376, 823);
  g->Binary(ynn_binary_pow, 823, 6378, 824);
  g->Binary(ynn_binary_multiply, 820, 824, 825);
  g->Convert(6511, 826);
  g->Binary(ynn_binary_multiply, 825, 826, 827);
  g->Binary(ynn_binary_add, 801, 827, 829);
}

// Scope: "Layer13 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1047, 830, {0,0,13,0}, {-1,-1,1,-1});
  g->Reshape(830, 831, {1,1,256});
  g->Binary(ynn_binary_add, 831, 6961, 832);
  g->Binary(ynn_binary_multiply, 832, 6374, 833);
  g->Quantize(829, 834, 0.5171695351600647, 0);
  g->Transpose(6508, 4028, {1,0});
  g->Binary(ynn_binary_multiply, 4025, 4027, 4023);
  g->Dot(834, 4028, YNN_INVALID_VALUE_ID, 4022, 1);
  g->DequantizeTensor(4022, YNN_INVALID_VALUE_ID, 4023, 4024);
  g->QuantizeTensor(4024, 6342, 4026, 835);
  g->Dequantize(835, 836, 0.13385827839374542, 0);
  g->Polynomial(836, 5605, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5605, 5606);
  g->Binary(ynn_binary_add, 5606, 5404, 5603);
  g->Binary(ynn_binary_multiply, 836, 5402, 5604);
  g->Binary(ynn_binary_multiply, 5604, 5603, 837);
  g->Binary(ynn_binary_multiply, 837, 833, 838);
  g->Quantize(838, 841, 0.4094488322734833, 0);
  g->Transpose(6509, 4035, {1,0});
  g->Binary(ynn_binary_multiply, 4032, 4034, 4030);
  g->Dot(841, 4035, YNN_INVALID_VALUE_ID, 4029, 1);
  g->DequantizeTensor(4029, YNN_INVALID_VALUE_ID, 4030, 4031);
  g->QuantizeTensor(4031, 6342, 4033, 842);
  g->Dequantize(842, 843, 0.25065305829048157, 0);
  g->Unary(ynn_unary_square, 843, 844);
  g->Reduce(ynn_reduce_sum, 844, 5608, {2}, true);
  g->ShapeProduct(844, 5607, {2});
  g->Binary(ynn_binary_divide, 5608, 5607, 845);
  g->Binary(ynn_binary_add, 845, 6376, 846);
  g->Binary(ynn_binary_pow, 846, 6378, 847);
  g->Binary(ynn_binary_multiply, 843, 847, 848);
  g->Convert(6512, 849);
  g->Binary(ynn_binary_multiply, 848, 849, 850);
  g->Binary(ynn_binary_add, 829, 850, 852);
  g->Convert(6504, 853);
  g->Binary(ynn_binary_multiply, 852, 853, 854);
}

// Scope: "Layer13"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13(Context& ctx) {
  BuildLayer13Attention(ctx);
  BuildLayer13Mlp(ctx);
  BuildLayer13PerLayerEmbedding(ctx);
}

// Scope: "Layer14 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(861, 863, 0.20956376194953918, 0);
  g->Transpose(6532, 4042, {1,0});
  g->Binary(ynn_binary_multiply, 4039, 4041, 4037);
  g->Dot(863, 4042, YNN_INVALID_VALUE_ID, 4036, 1);
  g->DequantizeTensor(4036, YNN_INVALID_VALUE_ID, 4037, 4038);
  g->QuantizeTensor(4038, 6342, 4040, 864);
  g->Dequantize(864, 865, 0.21751970052719116, 0);
  g->Reshape(865, 866, {1,1,1,512});
  g->Transpose(866, 867, {0,2,1,3});
  g->Unary(ynn_unary_square, 867, 868);
  g->Reduce(ynn_reduce_sum, 868, 5614, {3}, true);
  g->ShapeProduct(868, 5613, {3});
  g->Binary(ynn_binary_divide, 5614, 5613, 869);
  g->Binary(ynn_binary_add, 869, 6376, 870);
  g->Binary(ynn_binary_pow, 870, 6378, 871);
  g->Binary(ynn_binary_multiply, 867, 871, 872);
  g->Convert(6531, 874);
  g->Binary(ynn_binary_multiply, 872, 874, 875);
  g->Slice(875, 876, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(875, 877, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 877, 878);
  g->Concat({878,876}, 879, 3);
  g->Binary(ynn_binary_multiply, 875, 3406, 880);
  g->Binary(ynn_binary_multiply, 879, 3508, 881);
  g->Binary(ynn_binary_add, 880, 881, 882);
  g->Transpose(6536, 4047, {1,0});
  g->Binary(ynn_binary_multiply, 4039, 4046, 4044);
  g->Dot(863, 4047, YNN_INVALID_VALUE_ID, 4043, 1);
  g->DequantizeTensor(4043, YNN_INVALID_VALUE_ID, 4044, 4045);
  g->QuantizeTensor(4045, 6342, 4040, 884);
  g->Dequantize(884, 885, 0.21751970052719116, 0);
  g->Reshape(885, 886, {1,1,1,512});
  g->Transpose(886, 887, {0,2,1,3});
  g->Unary(ynn_unary_square, 887, 888);
  g->Reduce(ynn_reduce_sum, 888, 5616, {3}, true);
  g->ShapeProduct(888, 5615, {3});
  g->Binary(ynn_binary_divide, 5616, 5615, 889);
  g->Binary(ynn_binary_add, 889, 6376, 890);
  g->Binary(ynn_binary_pow, 890, 6378, 891);
  g->Binary(ynn_binary_multiply, 887, 891, 892);
}

// Scope: "Layer14 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(882, 893, 0.001091228099539876, 0);
  g->Append(6349, 893, 6998, 2, s2, slinky::expr(int64_t{1}));
  g->View(6998, 7028, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7028, 895, 0.001091228099539876, 0);
  g->Quantize(892, 896, 0.01785714365541935, 0);
  g->Append(6364, 896, 7013, 2, s2, slinky::expr(int64_t{1}));
  g->View(7013, 7043, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7043, 897, 0.01785714365541935, 0);
}

// Scope: "Layer14 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(6535, 4053, {1,0});
  g->Binary(ynn_binary_multiply, 4039, 4052, 4049);
  g->Dot(863, 4053, YNN_INVALID_VALUE_ID, 4048, 1);
  g->DequantizeTensor(4048, YNN_INVALID_VALUE_ID, 4049, 4050);
  g->QuantizeTensor(4050, 6342, 4051, 898);
  g->Dequantize(898, 899, 0.3385826647281647, 0);
  g->SplitDim(899, 900, 2, {8,512});
  g->Transpose(900, 901, {0,2,1,3});
  g->Unary(ynn_unary_square, 901, 902);
  g->Reduce(ynn_reduce_sum, 902, 5618, {3}, true);
  g->ShapeProduct(902, 5617, {3});
  g->Binary(ynn_binary_divide, 5618, 5617, 903);
  g->Binary(ynn_binary_add, 903, 6376, 904);
  g->Binary(ynn_binary_pow, 904, 6378, 905);
  g->Binary(ynn_binary_multiply, 901, 905, 906);
  g->Convert(6534, 907);
  g->Binary(ynn_binary_multiply, 906, 907, 908);
  g->Slice(908, 909, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(908, 910, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 910, 911);
  g->Concat({911,909}, 912, 3);
  g->Binary(ynn_binary_multiply, 908, 3406, 913);
  g->Binary(ynn_binary_multiply, 912, 3508, 914);
  g->Binary(ynn_binary_add, 913, 914, 915);
}

// Scope: "Layer14 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(915, 895, 916, false, true);
  g->Mask(916, 6389, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 6389, 5622, {-1}, true);
  g->Binary(ynn_binary_subtract, 6389, 5622, 5619);
  g->Unary(ynn_unary_exp, 5619, 5620);
  g->Reduce(ynn_reduce_sum, 5620, 5623, {-1}, true);
  g->Binary(ynn_binary_divide, 5404, 5623, 5621);
  g->Binary(ynn_binary_multiply, 5620, 5621, 917);
  g->Matmul(917, 897, 918, false, false);
}

// Scope: "Layer14 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(918, 920, {0,2,1,3});
  g->FuseDims(920, 921, 2, 2);
  g->Quantize(921, 922, 0.017962608486413956, 0);
  g->Transpose(6533, 4059, {1,0});
  g->Binary(ynn_binary_multiply, 3743, 4058, 4055);
  g->Dot(922, 4059, YNN_INVALID_VALUE_ID, 4054, 1);
  g->DequantizeTensor(4054, YNN_INVALID_VALUE_ID, 4055, 4056);
  g->QuantizeTensor(4056, 6342, 4057, 923);
  g->Dequantize(923, 924, 0.019122116267681122, 0);
}

// Scope: "Layer14 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 854, 855);
  g->Reduce(ynn_reduce_sum, 855, 5612, {2}, true);
  g->ShapeProduct(855, 5611, {2});
  g->Binary(ynn_binary_divide, 5612, 5611, 856);
  g->Binary(ynn_binary_add, 856, 6376, 857);
  g->Binary(ynn_binary_pow, 857, 6378, 858);
  g->Binary(ynn_binary_multiply, 854, 858, 859);
  g->Convert(6520, 860);
  g->Binary(ynn_binary_multiply, 859, 860, 861);
  BuildLayer14AttentionKvProjection(ctx);
  BuildLayer14AttentionCacheUpdate(ctx);
  BuildLayer14AttentionQueryProjection(ctx);
  BuildLayer14AttentionSdpa(ctx);
  BuildLayer14AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 924, 925);
  g->Reduce(ynn_reduce_sum, 925, 5625, {2}, true);
  g->ShapeProduct(925, 5624, {2});
  g->Binary(ynn_binary_divide, 5625, 5624, 926);
  g->Binary(ynn_binary_add, 926, 6376, 927);
  g->Binary(ynn_binary_pow, 927, 6378, 928);
  g->Binary(ynn_binary_multiply, 924, 928, 929);
  g->Convert(6527, 931);
  g->Binary(ynn_binary_multiply, 929, 931, 932);
  g->Binary(ynn_binary_add, 854, 932, 933);
}

// Scope: "Layer14 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 933, 934);
  g->Reduce(ynn_reduce_sum, 934, 5627, {2}, true);
  g->ShapeProduct(934, 5626, {2});
  g->Binary(ynn_binary_divide, 5627, 5626, 935);
  g->Binary(ynn_binary_add, 935, 6376, 936);
  g->Binary(ynn_binary_pow, 936, 6378, 937);
  g->Binary(ynn_binary_multiply, 933, 937, 938);
  g->Convert(6530, 939);
  g->Binary(ynn_binary_multiply, 938, 939, 940);
  g->Quantize(940, 942, 0.01763528399169445, 0);
  g->Transpose(6524, 4066, {1,0});
  g->Binary(ynn_binary_multiply, 4063, 4065, 4061);
  g->Dot(942, 4066, YNN_INVALID_VALUE_ID, 4060, 1);
  g->DequantizeTensor(4060, YNN_INVALID_VALUE_ID, 4061, 4062);
  g->QuantizeTensor(4062, 6342, 4064, 943);
  g->Dequantize(943, 944, 0.01457924209535122, 0);
  g->Transpose(6523, 4071, {1,0});
  g->Binary(ynn_binary_multiply, 4063, 4070, 4068);
  g->Dot(942, 4071, YNN_INVALID_VALUE_ID, 4067, 1);
  g->DequantizeTensor(4067, YNN_INVALID_VALUE_ID, 4068, 4069);
  g->QuantizeTensor(4069, 6342, 4064, 945);
  g->Dequantize(945, 946, 0.01457924209535122, 0);
  g->Polynomial(946, 5630, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5630, 5631);
  g->Binary(ynn_binary_add, 5631, 5404, 5628);
  g->Binary(ynn_binary_multiply, 946, 5402, 5629);
  g->Binary(ynn_binary_multiply, 5629, 5628, 947);
  g->Binary(ynn_binary_multiply, 944, 947, 948);
  g->Quantize(948, 949, 0.010642234236001968, 0);
  g->Transpose(6522, 4078, {1,0});
  g->Binary(ynn_binary_multiply, 4075, 4077, 4073);
  g->Dot(949, 4078, YNN_INVALID_VALUE_ID, 4072, 1);
  g->DequantizeTensor(4072, YNN_INVALID_VALUE_ID, 4073, 4074);
  g->QuantizeTensor(4074, 6342, 4076, 950);
  g->Dequantize(950, 951, 0.013017668388783932, 0);
  g->Unary(ynn_unary_square, 951, 952);
  g->Reduce(ynn_reduce_sum, 952, 5633, {2}, true);
  g->ShapeProduct(952, 5632, {2});
  g->Binary(ynn_binary_divide, 5633, 5632, 953);
  g->Binary(ynn_binary_add, 953, 6376, 954);
  g->Binary(ynn_binary_pow, 954, 6378, 955);
  g->Binary(ynn_binary_multiply, 951, 955, 956);
  g->Convert(6528, 957);
  g->Binary(ynn_binary_multiply, 956, 957, 958);
  g->Binary(ynn_binary_add, 933, 958, 959);
}

// Scope: "Layer14 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1047, 960, {0,0,14,0}, {-1,-1,1,-1});
  g->Reshape(960, 962, {1,1,256});
  g->Binary(ynn_binary_add, 962, 6962, 963);
  g->Binary(ynn_binary_multiply, 963, 6374, 964);
  g->Quantize(959, 965, 1.2159134149551392, 0);
  g->Transpose(6525, 4085, {1,0});
  g->Binary(ynn_binary_multiply, 4082, 4084, 4080);
  g->Dot(965, 4085, YNN_INVALID_VALUE_ID, 4079, 1);
  g->DequantizeTensor(4079, YNN_INVALID_VALUE_ID, 4080, 4081);
  g->QuantizeTensor(4081, 6342, 4083, 966);
  g->Dequantize(966, 967, 0.04429135099053383, 0);
  g->Polynomial(967, 5636, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5636, 5637);
  g->Binary(ynn_binary_add, 5637, 5404, 5634);
  g->Binary(ynn_binary_multiply, 967, 5402, 5635);
  g->Binary(ynn_binary_multiply, 5635, 5634, 968);
  g->Binary(ynn_binary_multiply, 968, 964, 969);
  g->Quantize(969, 970, 0.10629922151565552, 0);
  g->Transpose(6526, 4092, {1,0});
  g->Binary(ynn_binary_multiply, 4089, 4091, 4087);
  g->Dot(970, 4092, YNN_INVALID_VALUE_ID, 4086, 1);
  g->DequantizeTensor(4086, YNN_INVALID_VALUE_ID, 4087, 4088);
  g->QuantizeTensor(4088, 6342, 4090, 971);
  g->Dequantize(971, 972, 0.045032795518636703, 0);
  g->Unary(ynn_unary_square, 972, 973);
  g->Reduce(ynn_reduce_sum, 973, 5639, {2}, true);
  g->ShapeProduct(973, 5638, {2});
  g->Binary(ynn_binary_divide, 5639, 5638, 974);
  g->Binary(ynn_binary_add, 974, 6376, 975);
  g->Binary(ynn_binary_pow, 975, 6378, 976);
  g->Binary(ynn_binary_multiply, 972, 976, 977);
  g->Convert(6529, 978);
  g->Binary(ynn_binary_multiply, 977, 978, 979);
  g->Binary(ynn_binary_add, 959, 979, 980);
  g->Convert(6521, 981);
  g->Binary(ynn_binary_multiply, 980, 981, 983);
}

// Scope: "Layer14"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14(Context& ctx) {
  BuildLayer14Attention(ctx);
  BuildLayer14Mlp(ctx);
  BuildLayer14PerLayerEmbedding(ctx);
}

// Scope: "Layer15 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(990, 991, 0.18704485893249512, 0);
  g->Transpose(6550, 4105, {1,0});
  g->Binary(ynn_binary_multiply, 4102, 4104, 4100);
  g->Dot(991, 4105, YNN_INVALID_VALUE_ID, 4099, 1);
  g->DequantizeTensor(4099, YNN_INVALID_VALUE_ID, 4100, 4101);
  g->QuantizeTensor(4101, 6342, 4103, 992);
  g->Dequantize(992, 994, 0.2814960777759552, 0);
  g->SplitDim(994, 995, 2, {8,256});
  g->Transpose(995, 996, {0,2,1,3});
  g->Unary(ynn_unary_square, 996, 997);
  g->Reduce(ynn_reduce_sum, 997, 5643, {3}, true);
  g->ShapeProduct(997, 5642, {3});
  g->Binary(ynn_binary_divide, 5643, 5642, 998);
  g->Binary(ynn_binary_add, 998, 6376, 999);
  g->Binary(ynn_binary_pow, 999, 6378, 1000);
  g->Binary(ynn_binary_multiply, 996, 1000, 1001);
  g->Convert(6549, 1002);
  g->Binary(ynn_binary_multiply, 1001, 1002, 1003);
  g->Slice(1003, 1005, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1003, 1006, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1006, 1007);
  g->Concat({1007,1005}, 1008, 3);
  g->Binary(ynn_binary_multiply, 1003, 2133, 1009);
  g->Binary(ynn_binary_multiply, 1008, 2992, 1010);
  g->Binary(ynn_binary_add, 1009, 1010, 1011);
}

// Scope: "Layer15 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(1011, 762, 1012, false, true);
  g->Mask(1012, 6390, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6390, 5647, {-1}, true);
  g->Binary(ynn_binary_subtract, 6390, 5647, 5644);
  g->Unary(ynn_unary_exp, 5644, 5645);
  g->Reduce(ynn_reduce_sum, 5645, 5648, {-1}, true);
  g->Binary(ynn_binary_divide, 5404, 5648, 5646);
  g->Binary(ynn_binary_multiply, 5645, 5646, 1013);
  g->Matmul(1013, 764, 1015, false, false);
}

// Scope: "Layer15 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1015, 1016, {0,2,1,3});
  g->FuseDims(1016, 1017, 2, 2);
  g->Quantize(1017, 1018, 0.02436024509370327, 0);
  g->Transpose(6548, 4112, {1,0});
  g->Binary(ynn_binary_multiply, 4109, 4111, 4107);
  g->Dot(1018, 4112, YNN_INVALID_VALUE_ID, 4106, 1);
  g->DequantizeTensor(4106, YNN_INVALID_VALUE_ID, 4107, 4108);
  g->QuantizeTensor(4108, 6342, 4110, 1019);
  g->Dequantize(1019, 1020, 0.060289591550827026, 0);
}

// Scope: "Layer15 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 983, 984);
  g->Reduce(ynn_reduce_sum, 984, 5641, {2}, true);
  g->ShapeProduct(984, 5640, {2});
  g->Binary(ynn_binary_divide, 5641, 5640, 985);
  g->Binary(ynn_binary_add, 985, 6376, 986);
  g->Binary(ynn_binary_pow, 986, 6378, 987);
  g->Binary(ynn_binary_multiply, 983, 987, 988);
  g->Convert(6537, 989);
  g->Binary(ynn_binary_multiply, 988, 989, 990);
  BuildLayer15AttentionQueryProjection(ctx);
  BuildLayer15AttentionSdpa(ctx);
  BuildLayer15AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1020, 1021);
  g->Reduce(ynn_reduce_sum, 1021, 5650, {2}, true);
  g->ShapeProduct(1021, 5649, {2});
  g->Binary(ynn_binary_divide, 5650, 5649, 1022);
  g->Binary(ynn_binary_add, 1022, 6376, 1023);
  g->Binary(ynn_binary_pow, 1023, 6378, 1024);
  g->Binary(ynn_binary_multiply, 1020, 1024, 1026);
  g->Convert(6544, 1027);
  g->Binary(ynn_binary_multiply, 1026, 1027, 1028);
  g->Binary(ynn_binary_add, 983, 1028, 1029);
}

// Scope: "Layer15 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1029, 1030);
  g->Reduce(ynn_reduce_sum, 1030, 5652, {2}, true);
  g->ShapeProduct(1030, 5651, {2});
  g->Binary(ynn_binary_divide, 5652, 5651, 1031);
  g->Binary(ynn_binary_add, 1031, 6376, 1032);
  g->Binary(ynn_binary_pow, 1032, 6378, 1033);
  g->Binary(ynn_binary_multiply, 1029, 1033, 1034);
  g->Convert(6547, 1035);
  g->Binary(ynn_binary_multiply, 1034, 1035, 1037);
  g->Quantize(1037, 1038, 0.023188970983028412, 0);
  g->Transpose(6541, 4119, {1,0});
  g->Binary(ynn_binary_multiply, 4116, 4118, 4114);
  g->Dot(1038, 4119, YNN_INVALID_VALUE_ID, 4113, 1);
  g->DequantizeTensor(4113, YNN_INVALID_VALUE_ID, 4114, 4115);
  g->QuantizeTensor(4115, 6342, 4117, 1039);
  g->Dequantize(1039, 1040, 0.030511820688843727, 0);
  g->Transpose(6540, 4124, {1,0});
  g->Binary(ynn_binary_multiply, 4116, 4123, 4121);
  g->Dot(1038, 4124, YNN_INVALID_VALUE_ID, 4120, 1);
  g->DequantizeTensor(4120, YNN_INVALID_VALUE_ID, 4121, 4122);
  g->QuantizeTensor(4122, 6342, 4117, 1041);
  g->Dequantize(1041, 1042, 0.030511820688843727, 0);
  g->Polynomial(1042, 5657, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5657, 5658);
  g->Binary(ynn_binary_add, 5658, 5404, 5655);
  g->Binary(ynn_binary_multiply, 1042, 5402, 5656);
  g->Binary(ynn_binary_multiply, 5656, 5655, 1043);
  g->Binary(ynn_binary_multiply, 1040, 1043, 1044);
  g->Quantize(1044, 1045, 0.02005414292216301, 0);
  g->Transpose(6539, 4131, {1,0});
  g->Binary(ynn_binary_multiply, 4128, 4130, 4126);
  g->Dot(1045, 4131, YNN_INVALID_VALUE_ID, 4125, 1);
  g->DequantizeTensor(4125, YNN_INVALID_VALUE_ID, 4126, 4127);
  g->QuantizeTensor(4127, 6342, 4129, 1049);
  g->Dequantize(1049, 1050, 0.008105741813778877, 0);
  g->Unary(ynn_unary_square, 1050, 1051);
  g->Reduce(ynn_reduce_sum, 1051, 5660, {2}, true);
  g->ShapeProduct(1051, 5659, {2});
  g->Binary(ynn_binary_divide, 5660, 5659, 1052);
  g->Binary(ynn_binary_add, 1052, 6376, 1053);
  g->Binary(ynn_binary_pow, 1053, 6378, 1054);
  g->Binary(ynn_binary_multiply, 1050, 1054, 1055);
  g->Convert(6545, 1056);
  g->Binary(ynn_binary_multiply, 1055, 1056, 1057);
  g->Binary(ynn_binary_add, 1029, 1057, 1058);
}

// Scope: "Layer15 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1047, 1060, {0,0,15,0}, {-1,-1,1,-1});
  g->Reshape(1060, 1061, {1,1,256});
  g->Binary(ynn_binary_add, 1061, 6963, 1062);
  g->Binary(ynn_binary_multiply, 1062, 6374, 1063);
  g->Quantize(1058, 1064, 0.196418896317482, 0);
  g->Transpose(6542, 4138, {1,0});
  g->Binary(ynn_binary_multiply, 4135, 4137, 4133);
  g->Dot(1064, 4138, YNN_INVALID_VALUE_ID, 4132, 1);
  g->DequantizeTensor(4132, YNN_INVALID_VALUE_ID, 4133, 4134);
  g->QuantizeTensor(4134, 6342, 4136, 1065);
  g->Dequantize(1065, 1066, 0.05930119380354881, 0);
  g->Polynomial(1066, 5663, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5663, 5664);
  g->Binary(ynn_binary_add, 5664, 5404, 5661);
  g->Binary(ynn_binary_multiply, 1066, 5402, 5662);
  g->Binary(ynn_binary_multiply, 5662, 5661, 1067);
  g->Binary(ynn_binary_multiply, 1067, 1063, 1068);
  g->Quantize(1068, 1069, 0.6023622155189514, 0);
  g->Transpose(6543, 4145, {1,0});
  g->Binary(ynn_binary_multiply, 4142, 4144, 4140);
  g->Dot(1069, 4145, YNN_INVALID_VALUE_ID, 4139, 1);
  g->DequantizeTensor(4139, YNN_INVALID_VALUE_ID, 4140, 4141);
  g->QuantizeTensor(4141, 6342, 4143, 1071);
  g->Dequantize(1071, 1072, 0.33502069115638733, 0);
  g->Unary(ynn_unary_square, 1072, 1073);
  g->Reduce(ynn_reduce_sum, 1073, 5666, {2}, true);
  g->ShapeProduct(1073, 5665, {2});
  g->Binary(ynn_binary_divide, 5666, 5665, 1074);
  g->Binary(ynn_binary_add, 1074, 6376, 1075);
  g->Binary(ynn_binary_pow, 1075, 6378, 1076);
  g->Binary(ynn_binary_multiply, 1072, 1076, 1077);
  g->Convert(6546, 1078);
  g->Binary(ynn_binary_multiply, 1077, 1078, 1079);
  g->Binary(ynn_binary_add, 1058, 1079, 1080);
  g->Convert(6538, 1082);
  g->Binary(ynn_binary_multiply, 1080, 1082, 1083);
}

// Scope: "Layer15"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15(Context& ctx) {
  BuildLayer15Attention(ctx);
  BuildLayer15Mlp(ctx);
  BuildLayer15PerLayerEmbedding(ctx);
}

}  // namespace BuildGemma4DecodeSource
