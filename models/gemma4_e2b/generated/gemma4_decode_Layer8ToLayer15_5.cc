// Generated YNNPACK builder; do not edit.
#include "gemma4_decode_builder.h"

namespace BuildGemma4DecodeSource {

// Scope: "Layer8 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(42, 43, 0.0820433720946312, 0);
  g->Transpose(7094, 3726, {1,0});
  g->Binary(ynn_binary_multiply, 3723, 3725, 3721);
  g->Dot(43, 3726, YNN_INVALID_VALUE_ID, 3720, 1);
  g->DequantizeTensor(3720, YNN_INVALID_VALUE_ID, 3721, 3722);
  g->QuantizeTensor(3722, 6504, 3724, 44);
  g->Dequantize(44, 45, 0.09251969307661057, 0);
  g->Reshape(45, 47, {1,1,1,256});
  g->Reshape(47, 48, {1,1,1,256});
  g->Unary(ynn_unary_square, 48, 49);
  g->Reduce(ynn_reduce_sum, 49, 5512, {3}, true);
  g->ShapeProduct(49, 5511, {3});
  g->Binary(ynn_binary_divide, 5512, 5511, 50);
  g->Binary(ynn_binary_add, 50, 6539, 51);
  g->Unary(ynn_unary_rsqrt, 51, 52);
  g->Binary(ynn_binary_multiply, 48, 52, 53);
  g->Binary(ynn_binary_multiply, 53, 7093, 54);
  g->Slice(54, 55, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(54, 56, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 56, 58);
  g->Concat({58,55}, 59, 3);
  g->Binary(ynn_binary_multiply, 54, 3067, 60);
  g->Binary(ynn_binary_multiply, 59, 3172, 61);
  g->Binary(ynn_binary_add, 60, 61, 62);
  g->Transpose(7098, 3731, {1,0});
  g->Binary(ynn_binary_multiply, 3723, 3730, 3728);
  g->Dot(43, 3731, YNN_INVALID_VALUE_ID, 3727, 1);
  g->DequantizeTensor(3727, YNN_INVALID_VALUE_ID, 3728, 3729);
  g->QuantizeTensor(3729, 6504, 3724, 63);
  g->Dequantize(63, 64, 0.09251969307661057, 0);
  g->Reshape(64, 65, {1,1,1,256});
  g->Reshape(65, 66, {1,1,1,256});
  g->Unary(ynn_unary_square, 66, 68);
  g->Reduce(ynn_reduce_sum, 68, 5514, {3}, true);
  g->ShapeProduct(68, 5513, {3});
  g->Binary(ynn_binary_divide, 5514, 5513, 69);
  g->Binary(ynn_binary_add, 69, 6539, 70);
  g->Unary(ynn_unary_rsqrt, 70, 71);
  g->Binary(ynn_binary_multiply, 66, 71, 72);
}

// Scope: "Layer8 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(62, 73, 0.006215503439307213, 0);
  g->Append(6518, 73, 7168, 2, s2, slinky::expr(int64_t{1}));
  g->View(7168, 7198, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(72, 74, 0.047244105488061905, 0);
  g->Append(6533, 74, 7183, 2, s2, slinky::expr(int64_t{1}));
  g->View(7183, 7213, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer8 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(7097, 3744, {1,0});
  g->Binary(ynn_binary_multiply, 3723, 3743, 3740);
  g->Dot(43, 3744, YNN_INVALID_VALUE_ID, 3739, 1);
  g->DequantizeTensor(3739, YNN_INVALID_VALUE_ID, 3740, 3741);
  g->QuantizeTensor(3741, 6504, 3742, 76);
  g->Dequantize(76, 77, 0.1250000149011612, 0);
  g->SplitDim(77, 78, 2, {8,256});
  g->FuseDims(78, 80, 1, 2);
  g->SplitDim(80, 79, 1, {8,1});
  g->Unary(ynn_unary_square, 79, 81);
  g->Reduce(ynn_reduce_sum, 81, 5516, {3}, true);
  g->ShapeProduct(81, 5515, {3});
  g->Binary(ynn_binary_divide, 5516, 5515, 82);
  g->Binary(ynn_binary_add, 82, 6539, 83);
  g->Unary(ynn_unary_rsqrt, 83, 84);
  g->Binary(ynn_binary_multiply, 79, 84, 86);
  g->Binary(ynn_binary_multiply, 86, 7096, 87);
  g->Slice(87, 88, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(87, 89, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 89, 90);
  g->Concat({90,88}, 91, 3);
  g->Binary(ynn_binary_multiply, 87, 3067, 92);
  g->Binary(ynn_binary_multiply, 91, 3172, 93);
  g->Binary(ynn_binary_add, 92, 93, 94);
}

// Scope: "Layer8 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7198, 95, 0.006215503439307213, 0);
  g->Dequantize(7213, 97, 0.047244105488061905, 0);
  g->Matmul(94, 95, 98, false, true);
  g->Mask(98, 6578, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6578, 5522, {-1}, true);
  g->Binary(ynn_binary_subtract, 6578, 5522, 5519);
  g->Unary(ynn_unary_exp, 5519, 5520);
  g->Reduce(ynn_reduce_sum, 5520, 5523, {-1}, true);
  g->Binary(ynn_binary_divide, 5500, 5523, 5521);
  g->Binary(ynn_binary_multiply, 5520, 5521, 99);
  g->Matmul(99, 97, 100, false, false);
}

// Scope: "Layer8 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(100, 102, 1, 2);
  g->SplitDim(102, 101, 1, {1,8});
  g->FuseDims(101, 103, 2, 2);
  g->Quantize(103, 104, 0.025713592767715454, 0);
  g->Transpose(7095, 3751, {1,0});
  g->Binary(ynn_binary_multiply, 3748, 3750, 3746);
  g->Dot(104, 3751, YNN_INVALID_VALUE_ID, 3745, 1);
  g->DequantizeTensor(3745, YNN_INVALID_VALUE_ID, 3746, 3747);
  g->QuantizeTensor(3747, 6504, 3749, 105);
  g->Dequantize(105, 106, 0.022537967190146446, 0);
}

// Scope: "Layer8 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 36, 37);
  g->Reduce(ynn_reduce_sum, 37, 5510, {2}, true);
  g->ShapeProduct(37, 5509, {2});
  g->Binary(ynn_binary_divide, 5510, 5509, 38);
  g->Binary(ynn_binary_add, 38, 6539, 39);
  g->Unary(ynn_unary_rsqrt, 39, 40);
  g->Binary(ynn_binary_multiply, 36, 40, 41);
  g->Binary(ynn_binary_multiply, 41, 7082, 42);
  BuildLayer8AttentionKvProjection(ctx);
  BuildLayer8AttentionCacheUpdate(ctx);
  BuildLayer8AttentionQueryProjection(ctx);
  BuildLayer8AttentionSdpa(ctx);
  BuildLayer8AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 106, 109);
  g->Reduce(ynn_reduce_sum, 109, 5525, {2}, true);
  g->ShapeProduct(109, 5524, {2});
  g->Binary(ynn_binary_divide, 5525, 5524, 110);
  g->Binary(ynn_binary_add, 110, 6539, 111);
  g->Unary(ynn_unary_rsqrt, 111, 112);
  g->Binary(ynn_binary_multiply, 106, 112, 113);
  g->Binary(ynn_binary_multiply, 113, 7089, 114);
  g->Binary(ynn_binary_add, 114, 36, 115);
}

// Scope: "Layer8 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 115, 116);
  g->Reduce(ynn_reduce_sum, 116, 5527, {2}, true);
  g->ShapeProduct(116, 5526, {2});
  g->Binary(ynn_binary_divide, 5527, 5526, 117);
  g->Binary(ynn_binary_add, 117, 6539, 118);
  g->Unary(ynn_unary_rsqrt, 118, 120);
  g->Binary(ynn_binary_multiply, 115, 120, 121);
  g->Binary(ynn_binary_multiply, 121, 7092, 122);
  g->Quantize(122, 123, 0.015404289588332176, 0);
  g->Transpose(7086, 3758, {1,0});
  g->Binary(ynn_binary_multiply, 3755, 3757, 3753);
  g->Dot(123, 3758, YNN_INVALID_VALUE_ID, 3752, 1);
  g->DequantizeTensor(3752, YNN_INVALID_VALUE_ID, 3753, 3754);
  g->QuantizeTensor(3754, 6504, 3756, 124);
  g->Dequantize(124, 125, 0.018823828548192978, 0);
  g->Transpose(7085, 3763, {1,0});
  g->Binary(ynn_binary_multiply, 3755, 3762, 3760);
  g->Dot(123, 3763, YNN_INVALID_VALUE_ID, 3759, 1);
  g->DequantizeTensor(3759, YNN_INVALID_VALUE_ID, 3760, 3761);
  g->QuantizeTensor(3761, 6504, 3756, 126);
  g->Dequantize(126, 127, 0.018823828548192978, 0);
  g->Polynomial(127, 5530, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5530, 5531);
  g->Binary(ynn_binary_add, 5531, 5500, 5528);
  g->Binary(ynn_binary_multiply, 127, 5498, 5529);
  g->Binary(ynn_binary_multiply, 5529, 5528, 128);
  g->Binary(ynn_binary_multiply, 125, 128, 130);
  g->Quantize(130, 131, 0.012610738165676594, 0);
  g->Transpose(7084, 3770, {1,0});
  g->Binary(ynn_binary_multiply, 3767, 3769, 3765);
  g->Dot(131, 3770, YNN_INVALID_VALUE_ID, 3764, 1);
  g->DequantizeTensor(3764, YNN_INVALID_VALUE_ID, 3765, 3766);
  g->QuantizeTensor(3766, 6504, 3768, 132);
  g->Dequantize(132, 133, 0.009271269664168358, 0);
  g->Unary(ynn_unary_square, 133, 134);
  g->Reduce(ynn_reduce_sum, 134, 5533, {2}, true);
  g->ShapeProduct(134, 5532, {2});
  g->Binary(ynn_binary_divide, 5533, 5532, 135);
  g->Binary(ynn_binary_add, 135, 6539, 136);
  g->Unary(ynn_unary_rsqrt, 136, 137);
  g->Binary(ynn_binary_multiply, 133, 137, 138);
  g->Binary(ynn_binary_multiply, 138, 7090, 139);
  g->Binary(ynn_binary_add, 139, 115, 141);
}

// Scope: "Layer8 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(427, 142, {0,0,8,0}, {-1,-1,1,-1});
  g->Reshape(142, 143, {1,1,256});
  g->Unary(ynn_unary_square, 143, 144);
  g->Reduce(ynn_reduce_sum, 144, 5535, {2}, true);
  g->ShapeProduct(144, 5534, {2});
  g->Binary(ynn_binary_divide, 5535, 5534, 145);
  g->Binary(ynn_binary_add, 145, 6539, 146);
  g->Unary(ynn_unary_rsqrt, 146, 147);
  g->Binary(ynn_binary_multiply, 143, 147, 148);
  g->Binary(ynn_binary_multiply, 148, 7118, 149);
  g->Binary(ynn_binary_multiply, 7152, 6542, 150);
  g->Binary(ynn_binary_add, 149, 150, 152);
  g->Binary(ynn_binary_multiply, 152, 6536, 153);
  g->Quantize(141, 154, 0.19172413647174835, 0);
  g->Transpose(7087, 3777, {1,0});
  g->Binary(ynn_binary_multiply, 3774, 3776, 3772);
  g->Dot(154, 3777, YNN_INVALID_VALUE_ID, 3771, 1);
  g->DequantizeTensor(3771, YNN_INVALID_VALUE_ID, 3772, 3773);
  g->QuantizeTensor(3773, 6504, 3775, 155);
  g->Dequantize(155, 156, 0.11515748500823975, 0);
  g->Polynomial(156, 5538, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5538, 5539);
  g->Binary(ynn_binary_add, 5539, 5500, 5536);
  g->Binary(ynn_binary_multiply, 156, 5498, 5537);
  g->Binary(ynn_binary_multiply, 5537, 5536, 157);
  g->Binary(ynn_binary_multiply, 157, 153, 158);
  g->Quantize(158, 159, 0.787401556968689, 0);
  g->Transpose(7088, 3784, {1,0});
  g->Binary(ynn_binary_multiply, 3781, 3783, 3779);
  g->Dot(159, 3784, YNN_INVALID_VALUE_ID, 3778, 1);
  g->DequantizeTensor(3778, YNN_INVALID_VALUE_ID, 3779, 3780);
  g->QuantizeTensor(3780, 6504, 3782, 160);
  g->Dequantize(160, 161, 0.2950586676597595, 0);
  g->Unary(ynn_unary_square, 161, 163);
  g->Reduce(ynn_reduce_sum, 163, 5541, {2}, true);
  g->ShapeProduct(163, 5540, {2});
  g->Binary(ynn_binary_divide, 5541, 5540, 164);
  g->Binary(ynn_binary_add, 164, 6539, 165);
  g->Unary(ynn_unary_rsqrt, 165, 166);
  g->Binary(ynn_binary_multiply, 161, 166, 167);
  g->Binary(ynn_binary_multiply, 167, 7091, 168);
  g->Binary(ynn_binary_add, 141, 168, 169);
  g->Binary(ynn_binary_multiply, 169, 7083, 170);
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
  g->Quantize(177, 178, 0.016753647476434708, 0);
  g->Transpose(7111, 3791, {1,0});
  g->Binary(ynn_binary_multiply, 3788, 3790, 3786);
  g->Dot(178, 3791, YNN_INVALID_VALUE_ID, 3785, 1);
  g->DequantizeTensor(3785, YNN_INVALID_VALUE_ID, 3786, 3787);
  g->QuantizeTensor(3787, 6504, 3789, 179);
  g->Dequantize(179, 180, 0.020177174359560013, 0);
  g->Reshape(180, 181, {1,1,1,512});
  g->Reshape(181, 182, {1,1,1,512});
  g->Unary(ynn_unary_square, 182, 183);
  g->Reduce(ynn_reduce_sum, 183, 5545, {3}, true);
  g->ShapeProduct(183, 5544, {3});
  g->Binary(ynn_binary_divide, 5545, 5544, 185);
  g->Binary(ynn_binary_add, 185, 6539, 186);
  g->Unary(ynn_unary_rsqrt, 186, 187);
  g->Binary(ynn_binary_multiply, 182, 187, 188);
  g->Binary(ynn_binary_multiply, 188, 7110, 189);
  g->Slice(189, 190, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(189, 191, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 191, 192);
  g->Concat({192,190}, 193, 3);
  g->Binary(ynn_binary_multiply, 189, 3594, 194);
  g->Binary(ynn_binary_multiply, 193, 2, 196);
  g->Binary(ynn_binary_add, 194, 196, 197);
  g->Transpose(7115, 3796, {1,0});
  g->Binary(ynn_binary_multiply, 3788, 3795, 3793);
  g->Dot(178, 3796, YNN_INVALID_VALUE_ID, 3792, 1);
  g->DequantizeTensor(3792, YNN_INVALID_VALUE_ID, 3793, 3794);
  g->QuantizeTensor(3794, 6504, 3789, 198);
  g->Dequantize(198, 199, 0.020177174359560013, 0);
  g->Reshape(199, 200, {1,1,1,512});
  g->Reshape(200, 201, {1,1,1,512});
  g->Unary(ynn_unary_square, 201, 202);
  g->Reduce(ynn_reduce_sum, 202, 5549, {3}, true);
  g->ShapeProduct(202, 5548, {3});
  g->Binary(ynn_binary_divide, 5549, 5548, 203);
  g->Binary(ynn_binary_add, 203, 6539, 204);
  g->Unary(ynn_unary_rsqrt, 204, 206);
  g->Binary(ynn_binary_multiply, 201, 206, 207);
}

// Scope: "Layer9 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(197, 208, 0.0010733711533248425, 0);
  g->Append(6519, 208, 7169, 2, s2, slinky::expr(int64_t{1}));
  g->View(7169, 7199, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(207, 209, 0.01785714365541935, 0);
  g->Append(6534, 209, 7184, 2, s2, slinky::expr(int64_t{1}));
  g->View(7184, 7214, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer9 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(7114, 3802, {1,0});
  g->Binary(ynn_binary_multiply, 3788, 3801, 3798);
  g->Dot(178, 3802, YNN_INVALID_VALUE_ID, 3797, 1);
  g->DequantizeTensor(3797, YNN_INVALID_VALUE_ID, 3798, 3799);
  g->QuantizeTensor(3799, 6504, 3800, 210);
  g->Dequantize(210, 213, 0.029650600627064705, 0);
  g->SplitDim(213, 214, 2, {8,512});
  g->FuseDims(214, 216, 1, 2);
  g->SplitDim(216, 215, 1, {8,1});
  g->Unary(ynn_unary_square, 215, 217);
  g->Reduce(ynn_reduce_sum, 217, 5551, {3}, true);
  g->ShapeProduct(217, 5550, {3});
  g->Binary(ynn_binary_divide, 5551, 5550, 218);
  g->Binary(ynn_binary_add, 218, 6539, 219);
  g->Unary(ynn_unary_rsqrt, 219, 220);
  g->Binary(ynn_binary_multiply, 215, 220, 221);
  g->Binary(ynn_binary_multiply, 221, 7113, 222);
  g->Slice(222, 223, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(222, 225, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 225, 226);
  g->Concat({226,223}, 227, 3);
  g->Binary(ynn_binary_multiply, 222, 3594, 228);
  g->Binary(ynn_binary_multiply, 227, 2, 229);
  g->Binary(ynn_binary_add, 228, 229, 230);
}

// Scope: "Layer9 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7199, 231, 0.0010733711533248425, 0);
  g->Dequantize(7214, 232, 0.01785714365541935, 0);
  g->Matmul(230, 231, 233, false, true);
  g->Mask(233, 6579, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 6579, 5555, {-1}, true);
  g->Binary(ynn_binary_subtract, 6579, 5555, 5552);
  g->Unary(ynn_unary_exp, 5552, 5553);
  g->Reduce(ynn_reduce_sum, 5553, 5556, {-1}, true);
  g->Binary(ynn_binary_divide, 5500, 5556, 5554);
  g->Binary(ynn_binary_multiply, 5553, 5554, 235);
  g->Matmul(235, 232, 236, false, false);
}

// Scope: "Layer9 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(236, 238, 1, 2);
  g->SplitDim(238, 237, 1, {1,8});
  g->FuseDims(237, 239, 2, 2);
  g->Quantize(239, 240, 0.017962608486413956, 0);
  g->Transpose(7112, 3816, {1,0});
  g->Binary(ynn_binary_multiply, 3813, 3815, 3811);
  g->Dot(240, 3816, YNN_INVALID_VALUE_ID, 3810, 1);
  g->DequantizeTensor(3810, YNN_INVALID_VALUE_ID, 3811, 3812);
  g->QuantizeTensor(3812, 6504, 3814, 241);
  g->Dequantize(241, 242, 0.02776472456753254, 0);
}

// Scope: "Layer9 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 170, 171);
  g->Reduce(ynn_reduce_sum, 171, 5543, {2}, true);
  g->ShapeProduct(171, 5542, {2});
  g->Binary(ynn_binary_divide, 5543, 5542, 172);
  g->Binary(ynn_binary_add, 172, 6539, 174);
  g->Unary(ynn_unary_rsqrt, 174, 175);
  g->Binary(ynn_binary_multiply, 170, 175, 176);
  g->Binary(ynn_binary_multiply, 176, 7099, 177);
  BuildLayer9AttentionKvProjection(ctx);
  BuildLayer9AttentionCacheUpdate(ctx);
  BuildLayer9AttentionQueryProjection(ctx);
  BuildLayer9AttentionSdpa(ctx);
  BuildLayer9AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 242, 243);
  g->Reduce(ynn_reduce_sum, 243, 5558, {2}, true);
  g->ShapeProduct(243, 5557, {2});
  g->Binary(ynn_binary_divide, 5558, 5557, 244);
  g->Binary(ynn_binary_add, 244, 6539, 245);
  g->Unary(ynn_unary_rsqrt, 245, 247);
  g->Binary(ynn_binary_multiply, 242, 247, 248);
  g->Binary(ynn_binary_multiply, 248, 7106, 249);
  g->Binary(ynn_binary_add, 249, 170, 250);
}

// Scope: "Layer9 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 250, 251);
  g->Reduce(ynn_reduce_sum, 251, 5560, {2}, true);
  g->ShapeProduct(251, 5559, {2});
  g->Binary(ynn_binary_divide, 5560, 5559, 252);
  g->Binary(ynn_binary_add, 252, 6539, 253);
  g->Unary(ynn_unary_rsqrt, 253, 254);
  g->Binary(ynn_binary_multiply, 250, 254, 255);
  g->Binary(ynn_binary_multiply, 255, 7109, 256);
  g->Quantize(256, 258, 0.028379227966070175, 0);
  g->Transpose(7103, 3823, {1,0});
  g->Binary(ynn_binary_multiply, 3820, 3822, 3818);
  g->Dot(258, 3823, YNN_INVALID_VALUE_ID, 3817, 1);
  g->DequantizeTensor(3817, YNN_INVALID_VALUE_ID, 3818, 3819);
  g->QuantizeTensor(3819, 6504, 3821, 259);
  g->Dequantize(259, 260, 0.01556349452584982, 0);
  g->Transpose(7102, 3828, {1,0});
  g->Binary(ynn_binary_multiply, 3820, 3827, 3825);
  g->Dot(258, 3828, YNN_INVALID_VALUE_ID, 3824, 1);
  g->DequantizeTensor(3824, YNN_INVALID_VALUE_ID, 3825, 3826);
  g->QuantizeTensor(3826, 6504, 3821, 261);
  g->Dequantize(261, 262, 0.01556349452584982, 0);
  g->Polynomial(262, 5563, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5563, 5564);
  g->Binary(ynn_binary_add, 5564, 5500, 5561);
  g->Binary(ynn_binary_multiply, 262, 5498, 5562);
  g->Binary(ynn_binary_multiply, 5562, 5561, 263);
  g->Binary(ynn_binary_multiply, 260, 263, 264);
  g->Quantize(264, 265, 0.011441939510405064, 0);
  g->Transpose(7101, 3835, {1,0});
  g->Binary(ynn_binary_multiply, 3832, 3834, 3830);
  g->Dot(265, 3835, YNN_INVALID_VALUE_ID, 3829, 1);
  g->DequantizeTensor(3829, YNN_INVALID_VALUE_ID, 3830, 3831);
  g->QuantizeTensor(3831, 6504, 3833, 266);
  g->Dequantize(266, 268, 0.005826006643474102, 0);
  g->Unary(ynn_unary_square, 268, 269);
  g->Reduce(ynn_reduce_sum, 269, 5566, {2}, true);
  g->ShapeProduct(269, 5565, {2});
  g->Binary(ynn_binary_divide, 5566, 5565, 270);
  g->Binary(ynn_binary_add, 270, 6539, 271);
  g->Unary(ynn_unary_rsqrt, 271, 272);
  g->Binary(ynn_binary_multiply, 268, 272, 273);
  g->Binary(ynn_binary_multiply, 273, 7107, 274);
  g->Binary(ynn_binary_add, 274, 250, 275);
}

// Scope: "Layer9 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(427, 276, {0,0,9,0}, {-1,-1,1,-1});
  g->Reshape(276, 277, {1,1,256});
  g->Unary(ynn_unary_square, 277, 279);
  g->Reduce(ynn_reduce_sum, 279, 5568, {2}, true);
  g->ShapeProduct(279, 5567, {2});
  g->Binary(ynn_binary_divide, 5568, 5567, 280);
  g->Binary(ynn_binary_add, 280, 6539, 281);
  g->Unary(ynn_unary_rsqrt, 281, 282);
  g->Binary(ynn_binary_multiply, 277, 282, 283);
  g->Binary(ynn_binary_multiply, 283, 7118, 284);
  g->Binary(ynn_binary_multiply, 7153, 6542, 285);
  g->Binary(ynn_binary_add, 284, 285, 286);
  g->Binary(ynn_binary_multiply, 286, 6536, 287);
  g->Quantize(275, 288, 0.22249335050582886, 0);
  g->Transpose(7104, 3849, {1,0});
  g->Binary(ynn_binary_multiply, 3846, 3848, 3844);
  g->Dot(288, 3849, YNN_INVALID_VALUE_ID, 3843, 1);
  g->DequantizeTensor(3843, YNN_INVALID_VALUE_ID, 3844, 3845);
  g->QuantizeTensor(3845, 6504, 3847, 290);
  g->Dequantize(290, 291, 0.04404528811573982, 0);
  g->Polynomial(291, 5571, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5571, 5572);
  g->Binary(ynn_binary_add, 5572, 5500, 5569);
  g->Binary(ynn_binary_multiply, 291, 5498, 5570);
  g->Binary(ynn_binary_multiply, 5570, 5569, 292);
  g->Binary(ynn_binary_multiply, 292, 287, 293);
  g->Quantize(293, 294, 0.12598426640033722, 0);
  g->Transpose(7105, 3856, {1,0});
  g->Binary(ynn_binary_multiply, 3853, 3855, 3851);
  g->Dot(294, 3856, YNN_INVALID_VALUE_ID, 3850, 1);
  g->DequantizeTensor(3850, YNN_INVALID_VALUE_ID, 3851, 3852);
  g->QuantizeTensor(3852, 6504, 3854, 295);
  g->Dequantize(295, 296, 0.10531344264745712, 0);
  g->Unary(ynn_unary_square, 296, 297);
  g->Reduce(ynn_reduce_sum, 297, 5574, {2}, true);
  g->ShapeProduct(297, 5573, {2});
  g->Binary(ynn_binary_divide, 5574, 5573, 298);
  g->Binary(ynn_binary_add, 298, 6539, 299);
  g->Unary(ynn_unary_rsqrt, 299, 301);
  g->Binary(ynn_binary_multiply, 296, 301, 302);
  g->Binary(ynn_binary_multiply, 302, 7108, 303);
  g->Binary(ynn_binary_add, 275, 303, 304);
  g->Binary(ynn_binary_multiply, 304, 7100, 305);
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
  g->Quantize(312, 313, 0.15428009629249573, 0);
  g->Transpose(6627, 3863, {1,0});
  g->Binary(ynn_binary_multiply, 3860, 3862, 3858);
  g->Dot(313, 3863, YNN_INVALID_VALUE_ID, 3857, 1);
  g->DequantizeTensor(3857, YNN_INVALID_VALUE_ID, 3858, 3859);
  g->QuantizeTensor(3859, 6504, 3861, 314);
  g->Dequantize(314, 315, 0.19881890714168549, 0);
  g->Reshape(315, 316, {1,1,1,256});
  g->Reshape(316, 317, {1,1,1,256});
  g->Unary(ynn_unary_square, 317, 318);
  g->Reduce(ynn_reduce_sum, 318, 5582, {3}, true);
  g->ShapeProduct(318, 5581, {3});
  g->Binary(ynn_binary_divide, 5582, 5581, 319);
  g->Binary(ynn_binary_add, 319, 6539, 320);
  g->Unary(ynn_unary_rsqrt, 320, 321);
  g->Binary(ynn_binary_multiply, 317, 321, 324);
  g->Binary(ynn_binary_multiply, 324, 6626, 325);
  g->Slice(325, 326, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(325, 327, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 327, 328);
  g->Concat({328,326}, 329, 3);
  g->Binary(ynn_binary_multiply, 325, 3067, 330);
  g->Binary(ynn_binary_multiply, 329, 3172, 331);
  g->Binary(ynn_binary_add, 330, 331, 332);
  g->Transpose(6631, 3868, {1,0});
  g->Binary(ynn_binary_multiply, 3860, 3867, 3865);
  g->Dot(313, 3868, YNN_INVALID_VALUE_ID, 3864, 1);
  g->DequantizeTensor(3864, YNN_INVALID_VALUE_ID, 3865, 3866);
  g->QuantizeTensor(3866, 6504, 3861, 334);
  g->Dequantize(334, 335, 0.19881890714168549, 0);
  g->Reshape(335, 336, {1,1,1,256});
  g->Reshape(336, 337, {1,1,1,256});
  g->Unary(ynn_unary_square, 337, 338);
  g->Reduce(ynn_reduce_sum, 338, 5584, {3}, true);
  g->ShapeProduct(338, 5583, {3});
  g->Binary(ynn_binary_divide, 5584, 5583, 339);
  g->Binary(ynn_binary_add, 339, 6539, 340);
  g->Unary(ynn_unary_rsqrt, 340, 341);
  g->Binary(ynn_binary_multiply, 337, 341, 342);
}

// Scope: "Layer10 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(332, 343, 0.005712664220482111, 0);
  g->Append(6507, 343, 7157, 2, s2, slinky::expr(int64_t{1}));
  g->View(7157, 7187, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(342, 345, 0.047244105488061905, 0);
  g->Append(6522, 345, 7172, 2, s2, slinky::expr(int64_t{1}));
  g->View(7172, 7202, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer10 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(6630, 3881, {1,0});
  g->Binary(ynn_binary_multiply, 3860, 3880, 3877);
  g->Dot(313, 3881, YNN_INVALID_VALUE_ID, 3876, 1);
  g->DequantizeTensor(3876, YNN_INVALID_VALUE_ID, 3877, 3878);
  g->QuantizeTensor(3878, 6504, 3879, 346);
  g->Dequantize(346, 347, 0.3484252095222473, 0);
  g->SplitDim(347, 348, 2, {8,256});
  g->FuseDims(348, 350, 1, 2);
  g->SplitDim(350, 349, 1, {8,1});
  g->Unary(ynn_unary_square, 349, 352);
  g->Reduce(ynn_reduce_sum, 352, 5586, {3}, true);
  g->ShapeProduct(352, 5585, {3});
  g->Binary(ynn_binary_divide, 5586, 5585, 353);
  g->Binary(ynn_binary_add, 353, 6539, 354);
  g->Unary(ynn_unary_rsqrt, 354, 355);
  g->Binary(ynn_binary_multiply, 349, 355, 356);
  g->Binary(ynn_binary_multiply, 356, 6629, 357);
  g->Slice(357, 358, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(357, 359, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 359, 360);
  g->Concat({360,358}, 361, 3);
  g->Binary(ynn_binary_multiply, 357, 3067, 363);
  g->Binary(ynn_binary_multiply, 361, 3172, 364);
  g->Binary(ynn_binary_add, 363, 364, 365);
}

// Scope: "Layer10 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7187, 366, 0.005712664220482111, 0);
  g->Dequantize(7202, 367, 0.047244105488061905, 0);
  g->Matmul(365, 366, 368, false, true);
  g->Mask(368, 6547, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6547, 5590, {-1}, true);
  g->Binary(ynn_binary_subtract, 6547, 5590, 5587);
  g->Unary(ynn_unary_exp, 5587, 5588);
  g->Reduce(ynn_reduce_sum, 5588, 5591, {-1}, true);
  g->Binary(ynn_binary_divide, 5500, 5591, 5589);
  g->Binary(ynn_binary_multiply, 5588, 5589, 369);
  g->Matmul(369, 367, 370, false, false);
}

// Scope: "Layer10 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(370, 372, 1, 2);
  g->SplitDim(372, 371, 1, {1,8});
  g->FuseDims(371, 374, 2, 2);
  g->Quantize(374, 375, 0.028051190078258514, 0);
  g->Transpose(6628, 3888, {1,0});
  g->Binary(ynn_binary_multiply, 3885, 3887, 3883);
  g->Dot(375, 3888, YNN_INVALID_VALUE_ID, 3882, 1);
  g->DequantizeTensor(3882, YNN_INVALID_VALUE_ID, 3883, 3884);
  g->QuantizeTensor(3884, 6504, 3886, 376);
  g->Dequantize(376, 377, 0.029417896643280983, 0);
}

// Scope: "Layer10 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 305, 306);
  g->Reduce(ynn_reduce_sum, 306, 5576, {2}, true);
  g->ShapeProduct(306, 5575, {2});
  g->Binary(ynn_binary_divide, 5576, 5575, 307);
  g->Binary(ynn_binary_add, 307, 6539, 308);
  g->Unary(ynn_unary_rsqrt, 308, 309);
  g->Binary(ynn_binary_multiply, 305, 309, 310);
  g->Binary(ynn_binary_multiply, 310, 6615, 312);
  BuildLayer10AttentionKvProjection(ctx);
  BuildLayer10AttentionCacheUpdate(ctx);
  BuildLayer10AttentionQueryProjection(ctx);
  BuildLayer10AttentionSdpa(ctx);
  BuildLayer10AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 377, 378);
  g->Reduce(ynn_reduce_sum, 378, 5595, {2}, true);
  g->ShapeProduct(378, 5594, {2});
  g->Binary(ynn_binary_divide, 5595, 5594, 379);
  g->Binary(ynn_binary_add, 379, 6539, 380);
  g->Unary(ynn_unary_rsqrt, 380, 381);
  g->Binary(ynn_binary_multiply, 377, 381, 382);
  g->Binary(ynn_binary_multiply, 382, 6622, 383);
  g->Binary(ynn_binary_add, 383, 305, 385);
}

// Scope: "Layer10 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 385, 386);
  g->Reduce(ynn_reduce_sum, 386, 5597, {2}, true);
  g->ShapeProduct(386, 5596, {2});
  g->Binary(ynn_binary_divide, 5597, 5596, 387);
  g->Binary(ynn_binary_add, 387, 6539, 388);
  g->Unary(ynn_unary_rsqrt, 388, 389);
  g->Binary(ynn_binary_multiply, 385, 389, 390);
  g->Binary(ynn_binary_multiply, 390, 6625, 391);
  g->Quantize(391, 392, 0.018714377656579018, 0);
  g->Transpose(6619, 3895, {1,0});
  g->Binary(ynn_binary_multiply, 3892, 3894, 3890);
  g->Dot(392, 3895, YNN_INVALID_VALUE_ID, 3889, 1);
  g->DequantizeTensor(3889, YNN_INVALID_VALUE_ID, 3890, 3891);
  g->QuantizeTensor(3891, 6504, 3893, 393);
  g->Dequantize(393, 394, 0.01808563992381096, 0);
  g->Transpose(6618, 3900, {1,0});
  g->Binary(ynn_binary_multiply, 3892, 3899, 3897);
  g->Dot(392, 3900, YNN_INVALID_VALUE_ID, 3896, 1);
  g->DequantizeTensor(3896, YNN_INVALID_VALUE_ID, 3897, 3898);
  g->QuantizeTensor(3898, 6504, 3893, 396);
  g->Dequantize(396, 397, 0.01808563992381096, 0);
  g->Polynomial(397, 5600, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5600, 5601);
  g->Binary(ynn_binary_add, 5601, 5500, 5598);
  g->Binary(ynn_binary_multiply, 397, 5498, 5599);
  g->Binary(ynn_binary_multiply, 5599, 5598, 398);
  g->Binary(ynn_binary_multiply, 394, 398, 399);
  g->Quantize(399, 400, 0.01304134912788868, 0);
  g->Transpose(6617, 3907, {1,0});
  g->Binary(ynn_binary_multiply, 3904, 3906, 3902);
  g->Dot(400, 3907, YNN_INVALID_VALUE_ID, 3901, 1);
  g->DequantizeTensor(3901, YNN_INVALID_VALUE_ID, 3902, 3903);
  g->QuantizeTensor(3903, 6504, 3905, 401);
  g->Dequantize(401, 402, 0.011867290362715721, 0);
  g->Unary(ynn_unary_square, 402, 403);
  g->Reduce(ynn_reduce_sum, 403, 5603, {2}, true);
  g->ShapeProduct(403, 5602, {2});
  g->Binary(ynn_binary_divide, 5603, 5602, 404);
  g->Binary(ynn_binary_add, 404, 6539, 406);
  g->Unary(ynn_unary_rsqrt, 406, 407);
  g->Binary(ynn_binary_multiply, 402, 407, 408);
  g->Binary(ynn_binary_multiply, 408, 6623, 409);
  g->Binary(ynn_binary_add, 409, 385, 410);
}

// Scope: "Layer10 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(427, 411, {0,0,10,0}, {-1,-1,1,-1});
  g->Reshape(411, 412, {1,1,256});
  g->Unary(ynn_unary_square, 412, 413);
  g->Reduce(ynn_reduce_sum, 413, 5605, {2}, true);
  g->ShapeProduct(413, 5604, {2});
  g->Binary(ynn_binary_divide, 5605, 5604, 414);
  g->Binary(ynn_binary_add, 414, 6539, 415);
  g->Unary(ynn_unary_rsqrt, 415, 417);
  g->Binary(ynn_binary_multiply, 412, 417, 418);
  g->Binary(ynn_binary_multiply, 418, 7118, 419);
  g->Binary(ynn_binary_multiply, 7121, 6542, 420);
  g->Binary(ynn_binary_add, 419, 420, 421);
  g->Binary(ynn_binary_multiply, 421, 6536, 422);
  g->Quantize(410, 423, 0.14669467508792877, 0);
  g->Transpose(6620, 3914, {1,0});
  g->Binary(ynn_binary_multiply, 3911, 3913, 3909);
  g->Dot(423, 3914, YNN_INVALID_VALUE_ID, 3908, 1);
  g->DequantizeTensor(3908, YNN_INVALID_VALUE_ID, 3909, 3910);
  g->QuantizeTensor(3910, 6504, 3912, 424);
  g->Dequantize(424, 425, 0.038631901144981384, 0);
  g->Polynomial(425, 5608, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5608, 5609);
  g->Binary(ynn_binary_add, 5609, 5500, 5606);
  g->Binary(ynn_binary_multiply, 425, 5498, 5607);
  g->Binary(ynn_binary_multiply, 5607, 5606, 426);
  g->Binary(ynn_binary_multiply, 426, 422, 429);
  g->Quantize(429, 430, 0.05610237270593643, 0);
  g->Transpose(6621, 3921, {1,0});
  g->Binary(ynn_binary_multiply, 3918, 3920, 3916);
  g->Dot(430, 3921, YNN_INVALID_VALUE_ID, 3915, 1);
  g->DequantizeTensor(3915, YNN_INVALID_VALUE_ID, 3916, 3917);
  g->QuantizeTensor(3917, 6504, 3919, 431);
  g->Dequantize(431, 432, 0.041538726538419724, 0);
  g->Unary(ynn_unary_square, 432, 433);
  g->Reduce(ynn_reduce_sum, 433, 5611, {2}, true);
  g->ShapeProduct(433, 5610, {2});
  g->Binary(ynn_binary_divide, 5611, 5610, 434);
  g->Binary(ynn_binary_add, 434, 6539, 435);
  g->Unary(ynn_unary_rsqrt, 435, 436);
  g->Binary(ynn_binary_multiply, 432, 436, 437);
  g->Binary(ynn_binary_multiply, 437, 6624, 438);
  g->Binary(ynn_binary_add, 410, 438, 440);
  g->Binary(ynn_binary_multiply, 440, 6616, 441);
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
  g->Quantize(447, 448, 0.11506716161966324, 0);
  g->Transpose(6644, 3928, {1,0});
  g->Binary(ynn_binary_multiply, 3925, 3927, 3923);
  g->Dot(448, 3928, YNN_INVALID_VALUE_ID, 3922, 1);
  g->DequantizeTensor(3922, YNN_INVALID_VALUE_ID, 3923, 3924);
  g->QuantizeTensor(3924, 6504, 3926, 449);
  g->Dequantize(449, 451, 0.12696851789951324, 0);
  g->Reshape(451, 452, {1,1,1,256});
  g->Reshape(452, 453, {1,1,1,256});
  g->Unary(ynn_unary_square, 453, 454);
  g->Reduce(ynn_reduce_sum, 454, 5615, {3}, true);
  g->ShapeProduct(454, 5614, {3});
  g->Binary(ynn_binary_divide, 5615, 5614, 455);
  g->Binary(ynn_binary_add, 455, 6539, 456);
  g->Unary(ynn_unary_rsqrt, 456, 457);
  g->Binary(ynn_binary_multiply, 453, 457, 458);
  g->Binary(ynn_binary_multiply, 458, 6643, 459);
  g->Slice(459, 460, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(459, 462, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 462, 463);
  g->Concat({463,460}, 464, 3);
  g->Binary(ynn_binary_multiply, 459, 3067, 465);
  g->Binary(ynn_binary_multiply, 464, 3172, 466);
  g->Binary(ynn_binary_add, 465, 466, 467);
  g->Transpose(6648, 3933, {1,0});
  g->Binary(ynn_binary_multiply, 3925, 3932, 3930);
  g->Dot(448, 3933, YNN_INVALID_VALUE_ID, 3929, 1);
  g->DequantizeTensor(3929, YNN_INVALID_VALUE_ID, 3930, 3931);
  g->QuantizeTensor(3931, 6504, 3926, 468);
  g->Dequantize(468, 469, 0.12696851789951324, 0);
  g->Reshape(469, 470, {1,1,1,256});
  g->Reshape(470, 472, {1,1,1,256});
  g->Unary(ynn_unary_square, 472, 473);
  g->Reduce(ynn_reduce_sum, 473, 5619, {3}, true);
  g->ShapeProduct(473, 5618, {3});
  g->Binary(ynn_binary_divide, 5619, 5618, 474);
  g->Binary(ynn_binary_add, 474, 6539, 475);
  g->Unary(ynn_unary_rsqrt, 475, 476);
  g->Binary(ynn_binary_multiply, 472, 476, 477);
}

// Scope: "Layer11 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(467, 478, 0.005907459184527397, 0);
  g->Append(6508, 478, 7158, 2, s2, slinky::expr(int64_t{1}));
  g->View(7158, 7188, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(477, 479, 0.047244105488061905, 0);
  g->Append(6523, 479, 7173, 2, s2, slinky::expr(int64_t{1}));
  g->View(7173, 7203, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer11 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(6647, 3939, {1,0});
  g->Binary(ynn_binary_multiply, 3925, 3938, 3935);
  g->Dot(448, 3939, YNN_INVALID_VALUE_ID, 3934, 1);
  g->DequantizeTensor(3934, YNN_INVALID_VALUE_ID, 3935, 3936);
  g->QuantizeTensor(3936, 6504, 3937, 481);
  g->Dequantize(481, 482, 0.2736220359802246, 0);
  g->SplitDim(482, 483, 2, {8,256});
  g->FuseDims(483, 485, 1, 2);
  g->SplitDim(485, 484, 1, {8,1});
  g->Unary(ynn_unary_square, 484, 486);
  g->Reduce(ynn_reduce_sum, 486, 5621, {3}, true);
  g->ShapeProduct(486, 5620, {3});
  g->Binary(ynn_binary_divide, 5621, 5620, 487);
  g->Binary(ynn_binary_add, 487, 6539, 488);
  g->Unary(ynn_unary_rsqrt, 488, 490);
  g->Binary(ynn_binary_multiply, 484, 490, 491);
  g->Binary(ynn_binary_multiply, 491, 6646, 492);
  g->Slice(492, 493, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(492, 494, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 494, 495);
  g->Concat({495,493}, 496, 3);
  g->Binary(ynn_binary_multiply, 492, 3067, 497);
  g->Binary(ynn_binary_multiply, 496, 3172, 498);
  g->Binary(ynn_binary_add, 497, 498, 499);
}

// Scope: "Layer11 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7188, 501, 0.005907459184527397, 0);
  g->Dequantize(7203, 502, 0.047244105488061905, 0);
  g->Matmul(499, 501, 503, false, true);
  g->Mask(503, 6548, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6548, 5625, {-1}, true);
  g->Binary(ynn_binary_subtract, 6548, 5625, 5622);
  g->Unary(ynn_unary_exp, 5622, 5623);
  g->Reduce(ynn_reduce_sum, 5623, 5626, {-1}, true);
  g->Binary(ynn_binary_divide, 5500, 5626, 5624);
  g->Binary(ynn_binary_multiply, 5623, 5624, 504);
  g->Matmul(504, 502, 505, false, false);
}

// Scope: "Layer11 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(505, 507, 1, 2);
  g->SplitDim(507, 506, 1, {1,8});
  g->FuseDims(506, 508, 2, 2);
  g->Quantize(508, 509, 0.026082687079906464, 0);
  g->Transpose(6645, 3946, {1,0});
  g->Binary(ynn_binary_multiply, 3943, 3945, 3941);
  g->Dot(509, 3946, YNN_INVALID_VALUE_ID, 3940, 1);
  g->DequantizeTensor(3940, YNN_INVALID_VALUE_ID, 3941, 3942);
  g->QuantizeTensor(3942, 6504, 3944, 510);
  g->Dequantize(510, 512, 0.028822369873523712, 0);
}

// Scope: "Layer11 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 441, 442);
  g->Reduce(ynn_reduce_sum, 442, 5613, {2}, true);
  g->ShapeProduct(442, 5612, {2});
  g->Binary(ynn_binary_divide, 5613, 5612, 443);
  g->Binary(ynn_binary_add, 443, 6539, 444);
  g->Unary(ynn_unary_rsqrt, 444, 445);
  g->Binary(ynn_binary_multiply, 441, 445, 446);
  g->Binary(ynn_binary_multiply, 446, 6632, 447);
  BuildLayer11AttentionKvProjection(ctx);
  BuildLayer11AttentionCacheUpdate(ctx);
  BuildLayer11AttentionQueryProjection(ctx);
  BuildLayer11AttentionSdpa(ctx);
  BuildLayer11AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 512, 513);
  g->Reduce(ynn_reduce_sum, 513, 5628, {2}, true);
  g->ShapeProduct(513, 5627, {2});
  g->Binary(ynn_binary_divide, 5628, 5627, 514);
  g->Binary(ynn_binary_add, 514, 6539, 515);
  g->Unary(ynn_unary_rsqrt, 515, 516);
  g->Binary(ynn_binary_multiply, 512, 516, 517);
  g->Binary(ynn_binary_multiply, 517, 6639, 518);
  g->Binary(ynn_binary_add, 518, 441, 519);
}

// Scope: "Layer11 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 519, 520);
  g->Reduce(ynn_reduce_sum, 520, 5630, {2}, true);
  g->ShapeProduct(520, 5629, {2});
  g->Binary(ynn_binary_divide, 5630, 5629, 521);
  g->Binary(ynn_binary_add, 521, 6539, 523);
  g->Unary(ynn_unary_rsqrt, 523, 524);
  g->Binary(ynn_binary_multiply, 519, 524, 525);
  g->Binary(ynn_binary_multiply, 525, 6642, 526);
  g->Quantize(526, 527, 0.015670500695705414, 0);
  g->Transpose(6636, 3960, {1,0});
  g->Binary(ynn_binary_multiply, 3957, 3959, 3955);
  g->Dot(527, 3960, YNN_INVALID_VALUE_ID, 3954, 1);
  g->DequantizeTensor(3954, YNN_INVALID_VALUE_ID, 3955, 3956);
  g->QuantizeTensor(3956, 6504, 3958, 528);
  g->Dequantize(528, 529, 0.015255915932357311, 0);
  g->Transpose(6635, 3965, {1,0});
  g->Binary(ynn_binary_multiply, 3957, 3964, 3962);
  g->Dot(527, 3965, YNN_INVALID_VALUE_ID, 3961, 1);
  g->DequantizeTensor(3961, YNN_INVALID_VALUE_ID, 3962, 3963);
  g->QuantizeTensor(3963, 6504, 3958, 530);
  g->Dequantize(530, 531, 0.015255915932357311, 0);
  g->Polynomial(531, 5633, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5633, 5634);
  g->Binary(ynn_binary_add, 5634, 5500, 5631);
  g->Binary(ynn_binary_multiply, 531, 5498, 5632);
  g->Binary(ynn_binary_multiply, 5632, 5631, 534);
  g->Binary(ynn_binary_multiply, 529, 534, 535);
  g->Quantize(535, 536, 0.011195876635611057, 0);
  g->Transpose(6634, 3972, {1,0});
  g->Binary(ynn_binary_multiply, 3969, 3971, 3967);
  g->Dot(536, 3972, YNN_INVALID_VALUE_ID, 3966, 1);
  g->DequantizeTensor(3966, YNN_INVALID_VALUE_ID, 3967, 3968);
  g->QuantizeTensor(3968, 6504, 3970, 537);
  g->Dequantize(537, 538, 0.004389102105051279, 0);
  g->Unary(ynn_unary_square, 538, 539);
  g->Reduce(ynn_reduce_sum, 539, 5636, {2}, true);
  g->ShapeProduct(539, 5635, {2});
  g->Binary(ynn_binary_divide, 5636, 5635, 540);
  g->Binary(ynn_binary_add, 540, 6539, 541);
  g->Unary(ynn_unary_rsqrt, 541, 542);
  g->Binary(ynn_binary_multiply, 538, 542, 543);
  g->Binary(ynn_binary_multiply, 543, 6640, 545);
  g->Binary(ynn_binary_add, 545, 519, 546);
}

// Scope: "Layer11 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(427, 547, {0,0,11,0}, {-1,-1,1,-1});
  g->Reshape(547, 548, {1,1,256});
  g->Unary(ynn_unary_square, 548, 549);
  g->Reduce(ynn_reduce_sum, 549, 5638, {2}, true);
  g->ShapeProduct(549, 5637, {2});
  g->Binary(ynn_binary_divide, 5638, 5637, 550);
  g->Binary(ynn_binary_add, 550, 6539, 551);
  g->Unary(ynn_unary_rsqrt, 551, 552);
  g->Binary(ynn_binary_multiply, 548, 552, 553);
  g->Binary(ynn_binary_multiply, 553, 7118, 554);
  g->Binary(ynn_binary_multiply, 7122, 6542, 556);
  g->Binary(ynn_binary_add, 554, 556, 557);
  g->Binary(ynn_binary_multiply, 557, 6536, 558);
  g->Quantize(546, 559, 0.1750430017709732, 0);
  g->Transpose(6637, 3979, {1,0});
  g->Binary(ynn_binary_multiply, 3976, 3978, 3974);
  g->Dot(559, 3979, YNN_INVALID_VALUE_ID, 3973, 1);
  g->DequantizeTensor(3973, YNN_INVALID_VALUE_ID, 3974, 3975);
  g->QuantizeTensor(3975, 6504, 3977, 560);
  g->Dequantize(560, 561, 0.07529528439044952, 0);
  g->Polynomial(561, 5641, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5641, 5642);
  g->Binary(ynn_binary_add, 5642, 5500, 5639);
  g->Binary(ynn_binary_multiply, 561, 5498, 5640);
  g->Binary(ynn_binary_multiply, 5640, 5639, 562);
  g->Binary(ynn_binary_multiply, 562, 558, 563);
  g->Quantize(563, 564, 0.15846458077430725, 0);
  g->Transpose(6638, 3986, {1,0});
  g->Binary(ynn_binary_multiply, 3983, 3985, 3981);
  g->Dot(564, 3986, YNN_INVALID_VALUE_ID, 3980, 1);
  g->DequantizeTensor(3980, YNN_INVALID_VALUE_ID, 3981, 3982);
  g->QuantizeTensor(3982, 6504, 3984, 565);
  g->Dequantize(565, 567, 0.1771666705608368, 0);
  g->Unary(ynn_unary_square, 567, 568);
  g->Reduce(ynn_reduce_sum, 568, 5644, {2}, true);
  g->ShapeProduct(568, 5643, {2});
  g->Binary(ynn_binary_divide, 5644, 5643, 569);
  g->Binary(ynn_binary_add, 569, 6539, 570);
  g->Unary(ynn_unary_rsqrt, 570, 571);
  g->Binary(ynn_binary_multiply, 567, 571, 572);
  g->Binary(ynn_binary_multiply, 572, 6641, 573);
  g->Binary(ynn_binary_add, 546, 573, 574);
  g->Binary(ynn_binary_multiply, 574, 6633, 575);
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
  g->Quantize(582, 583, 0.08767248690128326, 0);
  g->Transpose(6661, 3993, {1,0});
  g->Binary(ynn_binary_multiply, 3990, 3992, 3988);
  g->Dot(583, 3993, YNN_INVALID_VALUE_ID, 3987, 1);
  g->DequantizeTensor(3987, YNN_INVALID_VALUE_ID, 3988, 3989);
  g->QuantizeTensor(3989, 6504, 3991, 584);
  g->Dequantize(584, 585, 0.08070866763591766, 0);
  g->Reshape(585, 586, {1,1,1,256});
  g->Reshape(586, 587, {1,1,1,256});
  g->Unary(ynn_unary_square, 587, 589);
  g->Reduce(ynn_reduce_sum, 589, 5650, {3}, true);
  g->ShapeProduct(589, 5649, {3});
  g->Binary(ynn_binary_divide, 5650, 5649, 590);
  g->Binary(ynn_binary_add, 590, 6539, 591);
  g->Unary(ynn_unary_rsqrt, 591, 592);
  g->Binary(ynn_binary_multiply, 587, 592, 593);
  g->Binary(ynn_binary_multiply, 593, 6660, 594);
  g->Slice(594, 595, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(594, 596, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 596, 597);
  g->Concat({597,595}, 598, 3);
  g->Binary(ynn_binary_multiply, 594, 3067, 600);
  g->Binary(ynn_binary_multiply, 598, 3172, 601);
  g->Binary(ynn_binary_add, 600, 601, 602);
  g->Transpose(6665, 3998, {1,0});
  g->Binary(ynn_binary_multiply, 3990, 3997, 3995);
  g->Dot(583, 3998, YNN_INVALID_VALUE_ID, 3994, 1);
  g->DequantizeTensor(3994, YNN_INVALID_VALUE_ID, 3995, 3996);
  g->QuantizeTensor(3996, 6504, 3991, 603);
  g->Dequantize(603, 604, 0.08070866763591766, 0);
  g->Reshape(604, 605, {1,1,1,256});
  g->Reshape(605, 606, {1,1,1,256});
  g->Unary(ynn_unary_square, 606, 607);
  g->Reduce(ynn_reduce_sum, 607, 5652, {3}, true);
  g->ShapeProduct(607, 5651, {3});
  g->Binary(ynn_binary_divide, 5652, 5651, 608);
  g->Binary(ynn_binary_add, 608, 6539, 610);
  g->Unary(ynn_unary_rsqrt, 610, 611);
  g->Binary(ynn_binary_multiply, 606, 611, 612);
}

// Scope: "Layer12 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(602, 613, 0.005788442213088274, 0);
  g->Append(6509, 613, 7159, 2, s2, slinky::expr(int64_t{1}));
  g->View(7159, 7189, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(612, 614, 0.047244105488061905, 0);
  g->Append(6524, 614, 7174, 2, s2, slinky::expr(int64_t{1}));
  g->View(7174, 7204, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer12 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(6664, 4004, {1,0});
  g->Binary(ynn_binary_multiply, 3990, 4003, 4000);
  g->Dot(583, 4004, YNN_INVALID_VALUE_ID, 3999, 1);
  g->DequantizeTensor(3999, YNN_INVALID_VALUE_ID, 4000, 4001);
  g->QuantizeTensor(4001, 6504, 4002, 616);
  g->Dequantize(616, 617, 0.12795276939868927, 0);
  g->SplitDim(617, 618, 2, {8,256});
  g->FuseDims(618, 620, 1, 2);
  g->SplitDim(620, 619, 1, {8,1});
  g->Unary(ynn_unary_square, 619, 621);
  g->Reduce(ynn_reduce_sum, 621, 5654, {3}, true);
  g->ShapeProduct(621, 5653, {3});
  g->Binary(ynn_binary_divide, 5654, 5653, 622);
  g->Binary(ynn_binary_add, 622, 6539, 623);
  g->Unary(ynn_unary_rsqrt, 623, 624);
  g->Binary(ynn_binary_multiply, 619, 624, 625);
  g->Binary(ynn_binary_multiply, 625, 6663, 626);
  g->Slice(626, 628, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(626, 629, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 629, 630);
  g->Concat({630,628}, 631, 3);
  g->Binary(ynn_binary_multiply, 626, 3067, 632);
  g->Binary(ynn_binary_multiply, 631, 3172, 633);
  g->Binary(ynn_binary_add, 632, 633, 634);
}

// Scope: "Layer12 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7189, 635, 0.005788442213088274, 0);
  g->Dequantize(7204, 636, 0.047244105488061905, 0);
  g->Matmul(634, 635, 637, false, true);
  g->Mask(637, 6549, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6549, 5660, {-1}, true);
  g->Binary(ynn_binary_subtract, 6549, 5660, 5657);
  g->Unary(ynn_unary_exp, 5657, 5658);
  g->Reduce(ynn_reduce_sum, 5658, 5661, {-1}, true);
  g->Binary(ynn_binary_divide, 5500, 5661, 5659);
  g->Binary(ynn_binary_multiply, 5658, 5659, 640);
  g->Matmul(640, 636, 641, false, false);
}

// Scope: "Layer12 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(641, 643, 1, 2);
  g->SplitDim(643, 642, 1, {1,8});
  g->FuseDims(642, 644, 2, 2);
  g->Quantize(644, 645, 0.028543315827846527, 0);
  g->Transpose(6662, 4011, {1,0});
  g->Binary(ynn_binary_multiply, 4008, 4010, 4006);
  g->Dot(645, 4011, YNN_INVALID_VALUE_ID, 4005, 1);
  g->DequantizeTensor(4005, YNN_INVALID_VALUE_ID, 4006, 4007);
  g->QuantizeTensor(4007, 6504, 4009, 646);
  g->Dequantize(646, 647, 0.021804405376315117, 0);
}

// Scope: "Layer12 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 575, 576);
  g->Reduce(ynn_reduce_sum, 576, 5648, {2}, true);
  g->ShapeProduct(576, 5647, {2});
  g->Binary(ynn_binary_divide, 5648, 5647, 578);
  g->Binary(ynn_binary_add, 578, 6539, 579);
  g->Unary(ynn_unary_rsqrt, 579, 580);
  g->Binary(ynn_binary_multiply, 575, 580, 581);
  g->Binary(ynn_binary_multiply, 581, 6649, 582);
  BuildLayer12AttentionKvProjection(ctx);
  BuildLayer12AttentionCacheUpdate(ctx);
  BuildLayer12AttentionQueryProjection(ctx);
  BuildLayer12AttentionSdpa(ctx);
  BuildLayer12AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 647, 648);
  g->Reduce(ynn_reduce_sum, 648, 5663, {2}, true);
  g->ShapeProduct(648, 5662, {2});
  g->Binary(ynn_binary_divide, 5663, 5662, 649);
  g->Binary(ynn_binary_add, 649, 6539, 651);
  g->Unary(ynn_unary_rsqrt, 651, 652);
  g->Binary(ynn_binary_multiply, 647, 652, 653);
  g->Binary(ynn_binary_multiply, 653, 6656, 654);
  g->Binary(ynn_binary_add, 654, 575, 655);
}

// Scope: "Layer12 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 655, 656);
  g->Reduce(ynn_reduce_sum, 656, 5665, {2}, true);
  g->ShapeProduct(656, 5664, {2});
  g->Binary(ynn_binary_divide, 5665, 5664, 657);
  g->Binary(ynn_binary_add, 657, 6539, 658);
  g->Unary(ynn_unary_rsqrt, 658, 659);
  g->Binary(ynn_binary_multiply, 655, 659, 660);
  g->Binary(ynn_binary_multiply, 660, 6659, 662);
  g->Quantize(662, 663, 0.013748278841376305, 0);
  g->Transpose(6653, 4018, {1,0});
  g->Binary(ynn_binary_multiply, 4015, 4017, 4013);
  g->Dot(663, 4018, YNN_INVALID_VALUE_ID, 4012, 1);
  g->DequantizeTensor(4012, YNN_INVALID_VALUE_ID, 4013, 4014);
  g->QuantizeTensor(4014, 6504, 4016, 664);
  g->Dequantize(664, 665, 0.012795286253094673, 0);
  g->Transpose(6652, 4023, {1,0});
  g->Binary(ynn_binary_multiply, 4015, 4022, 4020);
  g->Dot(663, 4023, YNN_INVALID_VALUE_ID, 4019, 1);
  g->DequantizeTensor(4019, YNN_INVALID_VALUE_ID, 4020, 4021);
  g->QuantizeTensor(4021, 6504, 4016, 666);
  g->Dequantize(666, 667, 0.012795286253094673, 0);
  g->Polynomial(667, 5668, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5668, 5669);
  g->Binary(ynn_binary_add, 5669, 5500, 5666);
  g->Binary(ynn_binary_multiply, 667, 5498, 5667);
  g->Binary(ynn_binary_multiply, 5667, 5666, 668);
  g->Binary(ynn_binary_multiply, 665, 668, 669);
  g->Quantize(669, 670, 0.00768947834149003, 0);
  g->Transpose(6651, 4030, {1,0});
  g->Binary(ynn_binary_multiply, 4027, 4029, 4025);
  g->Dot(670, 4030, YNN_INVALID_VALUE_ID, 4024, 1);
  g->DequantizeTensor(4024, YNN_INVALID_VALUE_ID, 4025, 4026);
  g->QuantizeTensor(4026, 6504, 4028, 672);
  g->Dequantize(672, 673, 0.005636297166347504, 0);
  g->Unary(ynn_unary_square, 673, 674);
  g->Reduce(ynn_reduce_sum, 674, 5671, {2}, true);
  g->ShapeProduct(674, 5670, {2});
  g->Binary(ynn_binary_divide, 5671, 5670, 675);
  g->Binary(ynn_binary_add, 675, 6539, 676);
  g->Unary(ynn_unary_rsqrt, 676, 677);
  g->Binary(ynn_binary_multiply, 673, 677, 678);
  g->Binary(ynn_binary_multiply, 678, 6657, 679);
  g->Binary(ynn_binary_add, 679, 655, 680);
}

// Scope: "Layer12 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(427, 681, {0,0,12,0}, {-1,-1,1,-1});
  g->Reshape(681, 683, {1,1,256});
  g->Unary(ynn_unary_square, 683, 684);
  g->Reduce(ynn_reduce_sum, 684, 5673, {2}, true);
  g->ShapeProduct(684, 5672, {2});
  g->Binary(ynn_binary_divide, 5673, 5672, 685);
  g->Binary(ynn_binary_add, 685, 6539, 686);
  g->Unary(ynn_unary_rsqrt, 686, 687);
  g->Binary(ynn_binary_multiply, 683, 687, 688);
  g->Binary(ynn_binary_multiply, 688, 7118, 689);
  g->Binary(ynn_binary_multiply, 7123, 6542, 690);
  g->Binary(ynn_binary_add, 689, 690, 691);
  g->Binary(ynn_binary_multiply, 691, 6536, 692);
  g->Quantize(680, 694, 0.19133253395557404, 0);
  g->Transpose(6654, 4036, {1,0});
  g->Binary(ynn_binary_multiply, 4034, 4035, 4032);
  g->Dot(694, 4036, YNN_INVALID_VALUE_ID, 4031, 1);
  g->DequantizeTensor(4031, YNN_INVALID_VALUE_ID, 4032, 4033);
  g->QuantizeTensor(4033, 6504, 3977, 695);
  g->Dequantize(695, 696, 0.07529528439044952, 0);
  g->Polynomial(696, 5676, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5676, 5677);
  g->Binary(ynn_binary_add, 5677, 5500, 5674);
  g->Binary(ynn_binary_multiply, 696, 5498, 5675);
  g->Binary(ynn_binary_multiply, 5675, 5674, 697);
  g->Binary(ynn_binary_multiply, 697, 692, 698);
  g->Quantize(698, 699, 0.12450788170099258, 0);
  g->Transpose(6655, 4043, {1,0});
  g->Binary(ynn_binary_multiply, 4040, 4042, 4038);
  g->Dot(699, 4043, YNN_INVALID_VALUE_ID, 4037, 1);
  g->DequantizeTensor(4037, YNN_INVALID_VALUE_ID, 4038, 4039);
  g->QuantizeTensor(4039, 6504, 4041, 700);
  g->Dequantize(700, 701, 0.12528184056282043, 0);
  g->Unary(ynn_unary_square, 701, 702);
  g->Reduce(ynn_reduce_sum, 702, 5679, {2}, true);
  g->ShapeProduct(702, 5678, {2});
  g->Binary(ynn_binary_divide, 5679, 5678, 703);
  g->Binary(ynn_binary_add, 703, 6539, 704);
  g->Unary(ynn_unary_rsqrt, 704, 705);
  g->Binary(ynn_binary_multiply, 701, 705, 706);
  g->Binary(ynn_binary_multiply, 706, 6658, 707);
  g->Binary(ynn_binary_add, 680, 707, 708);
  g->Binary(ynn_binary_multiply, 708, 6650, 709);
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
  g->Quantize(716, 717, 0.02862965501844883, 0);
  g->Transpose(6678, 4055, {1,0});
  g->Binary(ynn_binary_multiply, 4052, 4054, 4050);
  g->Dot(717, 4055, YNN_INVALID_VALUE_ID, 4049, 1);
  g->DequantizeTensor(4049, YNN_INVALID_VALUE_ID, 4050, 4051);
  g->QuantizeTensor(4051, 6504, 4053, 718);
  g->Dequantize(718, 719, 0.035925209522247314, 0);
  g->Reshape(719, 720, {1,1,1,256});
  g->Reshape(720, 721, {1,1,1,256});
  g->Unary(ynn_unary_square, 721, 722);
  g->Reduce(ynn_reduce_sum, 722, 5683, {3}, true);
  g->ShapeProduct(722, 5682, {3});
  g->Binary(ynn_binary_divide, 5683, 5682, 723);
  g->Binary(ynn_binary_add, 723, 6539, 724);
  g->Unary(ynn_unary_rsqrt, 724, 726);
  g->Binary(ynn_binary_multiply, 721, 726, 727);
  g->Binary(ynn_binary_multiply, 727, 6677, 728);
  g->Slice(728, 729, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(728, 730, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 730, 731);
  g->Concat({731,729}, 732, 3);
  g->Binary(ynn_binary_multiply, 728, 3067, 733);
  g->Binary(ynn_binary_multiply, 732, 3172, 734);
  g->Binary(ynn_binary_add, 733, 734, 735);
  g->Transpose(6682, 4060, {1,0});
  g->Binary(ynn_binary_multiply, 4052, 4059, 4057);
  g->Dot(717, 4060, YNN_INVALID_VALUE_ID, 4056, 1);
  g->DequantizeTensor(4056, YNN_INVALID_VALUE_ID, 4057, 4058);
  g->QuantizeTensor(4058, 6504, 4053, 737);
  g->Dequantize(737, 738, 0.035925209522247314, 0);
  g->Reshape(738, 739, {1,1,1,256});
  g->Reshape(739, 740, {1,1,1,256});
  g->Unary(ynn_unary_square, 740, 741);
  g->Reduce(ynn_reduce_sum, 741, 5685, {3}, true);
  g->ShapeProduct(741, 5684, {3});
  g->Binary(ynn_binary_divide, 5685, 5684, 742);
  g->Binary(ynn_binary_add, 742, 6539, 743);
  g->Unary(ynn_unary_rsqrt, 743, 744);
  g->Binary(ynn_binary_multiply, 740, 744, 745);
}

// Scope: "Layer13 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(735, 748, 0.0059552486054599285, 0);
  g->Append(6510, 748, 7160, 2, s2, slinky::expr(int64_t{1}));
  g->View(7160, 7190, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(745, 749, 0.047244105488061905, 0);
  g->Append(6525, 749, 7175, 2, s2, slinky::expr(int64_t{1}));
  g->View(7175, 7205, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer13 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(6681, 4065, {1,0});
  g->Binary(ynn_binary_multiply, 4052, 4064, 4062);
  g->Dot(717, 4065, YNN_INVALID_VALUE_ID, 4061, 1);
  g->DequantizeTensor(4061, YNN_INVALID_VALUE_ID, 4062, 4063);
  g->QuantizeTensor(4063, 6504, 3872, 750);
  g->Dequantize(750, 751, 0.03764764964580536, 0);
  g->SplitDim(751, 752, 2, {8,256});
  g->FuseDims(752, 755, 1, 2);
  g->SplitDim(755, 754, 1, {8,1});
  g->Unary(ynn_unary_square, 754, 756);
  g->Reduce(ynn_reduce_sum, 756, 5687, {3}, true);
  g->ShapeProduct(756, 5686, {3});
  g->Binary(ynn_binary_divide, 5687, 5686, 757);
  g->Binary(ynn_binary_add, 757, 6539, 758);
  g->Unary(ynn_unary_rsqrt, 758, 759);
  g->Binary(ynn_binary_multiply, 754, 759, 760);
  g->Binary(ynn_binary_multiply, 760, 6680, 761);
  g->Slice(761, 762, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(761, 763, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 763, 764);
  g->Concat({764,762}, 766, 3);
  g->Binary(ynn_binary_multiply, 761, 3067, 767);
  g->Binary(ynn_binary_multiply, 766, 3172, 768);
  g->Binary(ynn_binary_add, 767, 768, 769);
}

// Scope: "Layer13 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7190, 770, 0.0059552486054599285, 0);
  g->Dequantize(7205, 771, 0.047244105488061905, 0);
  g->Matmul(769, 770, 772, false, true);
  g->Mask(772, 6550, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6550, 5693, {-1}, true);
  g->Binary(ynn_binary_subtract, 6550, 5693, 5690);
  g->Unary(ynn_unary_exp, 5690, 5691);
  g->Reduce(ynn_reduce_sum, 5691, 5694, {-1}, true);
  g->Binary(ynn_binary_divide, 5500, 5694, 5692);
  g->Binary(ynn_binary_multiply, 5691, 5692, 773);
  g->Matmul(773, 771, 774, false, false);
}

// Scope: "Layer13 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(774, 777, 1, 2);
  g->SplitDim(777, 776, 1, {1,8});
  g->FuseDims(776, 778, 2, 2);
  g->Quantize(778, 779, 0.026205718517303467, 0);
  g->Transpose(6679, 4072, {1,0});
  g->Binary(ynn_binary_multiply, 4069, 4071, 4067);
  g->Dot(779, 4072, YNN_INVALID_VALUE_ID, 4066, 1);
  g->DequantizeTensor(4066, YNN_INVALID_VALUE_ID, 4067, 4068);
  g->QuantizeTensor(4068, 6504, 4070, 780);
  g->Dequantize(780, 781, 0.03592992201447487, 0);
}

// Scope: "Layer13 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 709, 710);
  g->Reduce(ynn_reduce_sum, 710, 5681, {2}, true);
  g->ShapeProduct(710, 5680, {2});
  g->Binary(ynn_binary_divide, 5681, 5680, 711);
  g->Binary(ynn_binary_add, 711, 6539, 712);
  g->Unary(ynn_unary_rsqrt, 712, 713);
  g->Binary(ynn_binary_multiply, 709, 713, 715);
  g->Binary(ynn_binary_multiply, 715, 6666, 716);
  BuildLayer13AttentionKvProjection(ctx);
  BuildLayer13AttentionCacheUpdate(ctx);
  BuildLayer13AttentionQueryProjection(ctx);
  BuildLayer13AttentionSdpa(ctx);
  BuildLayer13AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 781, 782);
  g->Reduce(ynn_reduce_sum, 782, 5696, {2}, true);
  g->ShapeProduct(782, 5695, {2});
  g->Binary(ynn_binary_divide, 5696, 5695, 783);
  g->Binary(ynn_binary_add, 783, 6539, 784);
  g->Unary(ynn_unary_rsqrt, 784, 785);
  g->Binary(ynn_binary_multiply, 781, 785, 786);
  g->Binary(ynn_binary_multiply, 786, 6673, 788);
  g->Binary(ynn_binary_add, 788, 709, 789);
}

// Scope: "Layer13 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 789, 790);
  g->Reduce(ynn_reduce_sum, 790, 5698, {2}, true);
  g->ShapeProduct(790, 5697, {2});
  g->Binary(ynn_binary_divide, 5698, 5697, 791);
  g->Binary(ynn_binary_add, 791, 6539, 792);
  g->Unary(ynn_unary_rsqrt, 792, 793);
  g->Binary(ynn_binary_multiply, 789, 793, 794);
  g->Binary(ynn_binary_multiply, 794, 6676, 795);
  g->Quantize(795, 796, 0.0083004767075181, 0);
  g->Transpose(6670, 4079, {1,0});
  g->Binary(ynn_binary_multiply, 4076, 4078, 4074);
  g->Dot(796, 4079, YNN_INVALID_VALUE_ID, 4073, 1);
  g->DequantizeTensor(4073, YNN_INVALID_VALUE_ID, 4074, 4075);
  g->QuantizeTensor(4075, 6504, 4077, 797);
  g->Dequantize(797, 799, 0.011934065259993076, 0);
  g->Transpose(6669, 4084, {1,0});
  g->Binary(ynn_binary_multiply, 4076, 4083, 4081);
  g->Dot(796, 4084, YNN_INVALID_VALUE_ID, 4080, 1);
  g->DequantizeTensor(4080, YNN_INVALID_VALUE_ID, 4081, 4082);
  g->QuantizeTensor(4082, 6504, 4077, 800);
  g->Dequantize(800, 801, 0.011934065259993076, 0);
  g->Polynomial(801, 5701, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5701, 5702);
  g->Binary(ynn_binary_add, 5702, 5500, 5699);
  g->Binary(ynn_binary_multiply, 801, 5498, 5700);
  g->Binary(ynn_binary_multiply, 5700, 5699, 802);
  g->Binary(ynn_binary_multiply, 799, 802, 803);
  g->Quantize(803, 804, 0.0015532826073467731, 0);
  g->Transpose(6668, 4091, {1,0});
  g->Binary(ynn_binary_multiply, 4088, 4090, 4086);
  g->Dot(804, 4091, YNN_INVALID_VALUE_ID, 4085, 1);
  g->DequantizeTensor(4085, YNN_INVALID_VALUE_ID, 4086, 4087);
  g->QuantizeTensor(4087, 6504, 4089, 805);
  g->Dequantize(805, 806, 0.002153691602870822, 0);
  g->Unary(ynn_unary_square, 806, 807);
  g->Reduce(ynn_reduce_sum, 807, 5704, {2}, true);
  g->ShapeProduct(807, 5703, {2});
  g->Binary(ynn_binary_divide, 5704, 5703, 809);
  g->Binary(ynn_binary_add, 809, 6539, 810);
  g->Unary(ynn_unary_rsqrt, 810, 811);
  g->Binary(ynn_binary_multiply, 806, 811, 812);
  g->Binary(ynn_binary_multiply, 812, 6674, 813);
  g->Binary(ynn_binary_add, 813, 789, 814);
}

// Scope: "Layer13 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(427, 815, {0,0,13,0}, {-1,-1,1,-1});
  g->Reshape(815, 816, {1,1,256});
  g->Unary(ynn_unary_square, 816, 817);
  g->Reduce(ynn_reduce_sum, 817, 5706, {2}, true);
  g->ShapeProduct(817, 5705, {2});
  g->Binary(ynn_binary_divide, 5706, 5705, 818);
  g->Binary(ynn_binary_add, 818, 6539, 819);
  g->Unary(ynn_unary_rsqrt, 819, 820);
  g->Binary(ynn_binary_multiply, 816, 820, 821);
  g->Binary(ynn_binary_multiply, 821, 7118, 822);
  g->Binary(ynn_binary_multiply, 7124, 6542, 823);
  g->Binary(ynn_binary_add, 822, 823, 824);
  g->Binary(ynn_binary_multiply, 824, 6536, 825);
  g->Quantize(814, 826, 0.5171695351600647, 0);
  g->Transpose(6671, 4098, {1,0});
  g->Binary(ynn_binary_multiply, 4095, 4097, 4093);
  g->Dot(826, 4098, YNN_INVALID_VALUE_ID, 4092, 1);
  g->DequantizeTensor(4092, YNN_INVALID_VALUE_ID, 4093, 4094);
  g->QuantizeTensor(4094, 6504, 4096, 827);
  g->Dequantize(827, 828, 0.13385827839374542, 0);
  g->Polynomial(828, 5709, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5709, 5710);
  g->Binary(ynn_binary_add, 5710, 5500, 5707);
  g->Binary(ynn_binary_multiply, 828, 5498, 5708);
  g->Binary(ynn_binary_multiply, 5708, 5707, 829);
  g->Binary(ynn_binary_multiply, 829, 825, 830);
  g->Quantize(830, 831, 0.4094488322734833, 0);
  g->Transpose(6672, 4105, {1,0});
  g->Binary(ynn_binary_multiply, 4102, 4104, 4100);
  g->Dot(831, 4105, YNN_INVALID_VALUE_ID, 4099, 1);
  g->DequantizeTensor(4099, YNN_INVALID_VALUE_ID, 4100, 4101);
  g->QuantizeTensor(4101, 6504, 4103, 832);
  g->Dequantize(832, 833, 0.25065305829048157, 0);
  g->Unary(ynn_unary_square, 833, 834);
  g->Reduce(ynn_reduce_sum, 834, 5712, {2}, true);
  g->ShapeProduct(834, 5711, {2});
  g->Binary(ynn_binary_divide, 5712, 5711, 835);
  g->Binary(ynn_binary_add, 835, 6539, 836);
  g->Unary(ynn_unary_rsqrt, 836, 837);
  g->Binary(ynn_binary_multiply, 833, 837, 838);
  g->Binary(ynn_binary_multiply, 838, 6675, 840);
  g->Binary(ynn_binary_add, 814, 840, 841);
  g->Binary(ynn_binary_multiply, 841, 6667, 842);
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
  g->Quantize(848, 849, 0.20956376194953918, 0);
  g->Transpose(6695, 4112, {1,0});
  g->Binary(ynn_binary_multiply, 4109, 4111, 4107);
  g->Dot(849, 4112, YNN_INVALID_VALUE_ID, 4106, 1);
  g->DequantizeTensor(4106, YNN_INVALID_VALUE_ID, 4107, 4108);
  g->QuantizeTensor(4108, 6504, 4110, 851);
  g->Dequantize(851, 852, 0.21751970052719116, 0);
  g->Reshape(852, 853, {1,1,1,512});
  g->Reshape(853, 854, {1,1,1,512});
  g->Unary(ynn_unary_square, 854, 855);
  g->Reduce(ynn_reduce_sum, 855, 5716, {3}, true);
  g->ShapeProduct(855, 5715, {3});
  g->Binary(ynn_binary_divide, 5716, 5715, 856);
  g->Binary(ynn_binary_add, 856, 6539, 857);
  g->Unary(ynn_unary_rsqrt, 857, 858);
  g->Binary(ynn_binary_multiply, 854, 858, 859);
  g->Binary(ynn_binary_multiply, 859, 6694, 860);
  g->Slice(860, 861, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(860, 862, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 862, 863);
  g->Concat({863,861}, 864, 3);
  g->Binary(ynn_binary_multiply, 860, 3594, 865);
  g->Binary(ynn_binary_multiply, 864, 2, 866);
  g->Binary(ynn_binary_add, 865, 866, 867);
  g->Transpose(6699, 4117, {1,0});
  g->Binary(ynn_binary_multiply, 4109, 4116, 4114);
  g->Dot(849, 4117, YNN_INVALID_VALUE_ID, 4113, 1);
  g->DequantizeTensor(4113, YNN_INVALID_VALUE_ID, 4114, 4115);
  g->QuantizeTensor(4115, 6504, 4110, 868);
  g->Dequantize(868, 869, 0.21751970052719116, 0);
  g->Reshape(869, 870, {1,1,1,512});
  g->Reshape(870, 871, {1,1,1,512});
  g->Unary(ynn_unary_square, 871, 872);
  g->Reduce(ynn_reduce_sum, 872, 5718, {3}, true);
  g->ShapeProduct(872, 5717, {3});
  g->Binary(ynn_binary_divide, 5718, 5717, 873);
  g->Binary(ynn_binary_add, 873, 6539, 874);
  g->Unary(ynn_unary_rsqrt, 874, 875);
  g->Binary(ynn_binary_multiply, 871, 875, 876);
}

// Scope: "Layer14 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(867, 877, 0.001091228099539876, 0);
  g->Append(6511, 877, 7161, 2, s2, slinky::expr(int64_t{1}));
  g->View(7161, 7191, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(876, 879, 0.01785714365541935, 0);
  g->Append(6526, 879, 7176, 2, s2, slinky::expr(int64_t{1}));
  g->View(7176, 7206, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer14 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(6698, 4129, {1,0});
  g->Binary(ynn_binary_multiply, 4109, 4128, 4125);
  g->Dot(849, 4129, YNN_INVALID_VALUE_ID, 4124, 1);
  g->DequantizeTensor(4124, YNN_INVALID_VALUE_ID, 4125, 4126);
  g->QuantizeTensor(4126, 6504, 4127, 880);
  g->Dequantize(880, 881, 0.3385826647281647, 0);
  g->SplitDim(881, 882, 2, {8,512});
  g->FuseDims(882, 884, 1, 2);
  g->SplitDim(884, 883, 1, {8,1});
  g->Unary(ynn_unary_square, 883, 885);
  g->Reduce(ynn_reduce_sum, 885, 5720, {3}, true);
  g->ShapeProduct(885, 5719, {3});
  g->Binary(ynn_binary_divide, 5720, 5719, 886);
  g->Binary(ynn_binary_add, 886, 6539, 888);
  g->Unary(ynn_unary_rsqrt, 888, 889);
  g->Binary(ynn_binary_multiply, 883, 889, 890);
  g->Binary(ynn_binary_multiply, 890, 6697, 891);
  g->Slice(891, 892, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(891, 893, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 893, 894);
  g->Concat({894,892}, 895, 3);
  g->Binary(ynn_binary_multiply, 891, 3594, 896);
  g->Binary(ynn_binary_multiply, 895, 2, 897);
  g->Binary(ynn_binary_add, 896, 897, 899);
}

// Scope: "Layer14 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7191, 900, 0.001091228099539876, 0);
  g->Dequantize(7206, 901, 0.01785714365541935, 0);
  g->Matmul(899, 900, 902, false, true);
  g->Mask(902, 6551, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 6551, 5724, {-1}, true);
  g->Binary(ynn_binary_subtract, 6551, 5724, 5721);
  g->Unary(ynn_unary_exp, 5721, 5722);
  g->Reduce(ynn_reduce_sum, 5722, 5725, {-1}, true);
  g->Binary(ynn_binary_divide, 5500, 5725, 5723);
  g->Binary(ynn_binary_multiply, 5722, 5723, 903);
  g->Matmul(903, 901, 904, false, false);
}

// Scope: "Layer14 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(904, 906, 1, 2);
  g->SplitDim(906, 905, 1, {1,8});
  g->FuseDims(905, 907, 2, 2);
  g->Quantize(907, 908, 0.017962608486413956, 0);
  g->Transpose(6696, 4135, {1,0});
  g->Binary(ynn_binary_multiply, 3813, 4134, 4131);
  g->Dot(908, 4135, YNN_INVALID_VALUE_ID, 4130, 1);
  g->DequantizeTensor(4130, YNN_INVALID_VALUE_ID, 4131, 4132);
  g->QuantizeTensor(4132, 6504, 4133, 911);
  g->Dequantize(911, 912, 0.019122116267681122, 0);
}

// Scope: "Layer14 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 842, 843);
  g->Reduce(ynn_reduce_sum, 843, 5714, {2}, true);
  g->ShapeProduct(843, 5713, {2});
  g->Binary(ynn_binary_divide, 5714, 5713, 844);
  g->Binary(ynn_binary_add, 844, 6539, 845);
  g->Unary(ynn_unary_rsqrt, 845, 846);
  g->Binary(ynn_binary_multiply, 842, 846, 847);
  g->Binary(ynn_binary_multiply, 847, 6683, 848);
  BuildLayer14AttentionKvProjection(ctx);
  BuildLayer14AttentionCacheUpdate(ctx);
  BuildLayer14AttentionQueryProjection(ctx);
  BuildLayer14AttentionSdpa(ctx);
  BuildLayer14AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 912, 913);
  g->Reduce(ynn_reduce_sum, 913, 5727, {2}, true);
  g->ShapeProduct(913, 5726, {2});
  g->Binary(ynn_binary_divide, 5727, 5726, 914);
  g->Binary(ynn_binary_add, 914, 6539, 915);
  g->Unary(ynn_unary_rsqrt, 915, 916);
  g->Binary(ynn_binary_multiply, 912, 916, 917);
  g->Binary(ynn_binary_multiply, 917, 6690, 918);
  g->Binary(ynn_binary_add, 918, 842, 919);
}

// Scope: "Layer14 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 919, 920);
  g->Reduce(ynn_reduce_sum, 920, 5729, {2}, true);
  g->ShapeProduct(920, 5728, {2});
  g->Binary(ynn_binary_divide, 5729, 5728, 922);
  g->Binary(ynn_binary_add, 922, 6539, 923);
  g->Unary(ynn_unary_rsqrt, 923, 924);
  g->Binary(ynn_binary_multiply, 919, 924, 925);
  g->Binary(ynn_binary_multiply, 925, 6693, 926);
  g->Quantize(926, 927, 0.01763528399169445, 0);
  g->Transpose(6687, 4142, {1,0});
  g->Binary(ynn_binary_multiply, 4139, 4141, 4137);
  g->Dot(927, 4142, YNN_INVALID_VALUE_ID, 4136, 1);
  g->DequantizeTensor(4136, YNN_INVALID_VALUE_ID, 4137, 4138);
  g->QuantizeTensor(4138, 6504, 4140, 928);
  g->Dequantize(928, 929, 0.01457924209535122, 0);
  g->Transpose(6686, 4147, {1,0});
  g->Binary(ynn_binary_multiply, 4139, 4146, 4144);
  g->Dot(927, 4147, YNN_INVALID_VALUE_ID, 4143, 1);
  g->DequantizeTensor(4143, YNN_INVALID_VALUE_ID, 4144, 4145);
  g->QuantizeTensor(4145, 6504, 4140, 930);
  g->Dequantize(930, 932, 0.01457924209535122, 0);
  g->Polynomial(932, 5734, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5734, 5735);
  g->Binary(ynn_binary_add, 5735, 5500, 5732);
  g->Binary(ynn_binary_multiply, 932, 5498, 5733);
  g->Binary(ynn_binary_multiply, 5733, 5732, 933);
  g->Binary(ynn_binary_multiply, 929, 933, 934);
  g->Quantize(934, 935, 0.010642234236001968, 0);
  g->Transpose(6685, 4154, {1,0});
  g->Binary(ynn_binary_multiply, 4151, 4153, 4149);
  g->Dot(935, 4154, YNN_INVALID_VALUE_ID, 4148, 1);
  g->DequantizeTensor(4148, YNN_INVALID_VALUE_ID, 4149, 4150);
  g->QuantizeTensor(4150, 6504, 4152, 936);
  g->Dequantize(936, 937, 0.013017668388783932, 0);
  g->Unary(ynn_unary_square, 937, 938);
  g->Reduce(ynn_reduce_sum, 938, 5737, {2}, true);
  g->ShapeProduct(938, 5736, {2});
  g->Binary(ynn_binary_divide, 5737, 5736, 939);
  g->Binary(ynn_binary_add, 939, 6539, 940);
  g->Unary(ynn_unary_rsqrt, 940, 941);
  g->Binary(ynn_binary_multiply, 937, 941, 943);
  g->Binary(ynn_binary_multiply, 943, 6691, 944);
  g->Binary(ynn_binary_add, 944, 919, 945);
}

// Scope: "Layer14 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(427, 946, {0,0,14,0}, {-1,-1,1,-1});
  g->Reshape(946, 947, {1,1,256});
  g->Unary(ynn_unary_square, 947, 948);
  g->Reduce(ynn_reduce_sum, 948, 5739, {2}, true);
  g->ShapeProduct(948, 5738, {2});
  g->Binary(ynn_binary_divide, 5739, 5738, 949);
  g->Binary(ynn_binary_add, 949, 6539, 950);
  g->Unary(ynn_unary_rsqrt, 950, 951);
  g->Binary(ynn_binary_multiply, 947, 951, 952);
  g->Binary(ynn_binary_multiply, 952, 7118, 955);
  g->Binary(ynn_binary_multiply, 7125, 6542, 956);
  g->Binary(ynn_binary_add, 955, 956, 957);
  g->Binary(ynn_binary_multiply, 957, 6536, 958);
  g->Quantize(945, 959, 1.2159134149551392, 0);
  g->Transpose(6688, 4161, {1,0});
  g->Binary(ynn_binary_multiply, 4158, 4160, 4156);
  g->Dot(959, 4161, YNN_INVALID_VALUE_ID, 4155, 1);
  g->DequantizeTensor(4155, YNN_INVALID_VALUE_ID, 4156, 4157);
  g->QuantizeTensor(4157, 6504, 4159, 960);
  g->Dequantize(960, 961, 0.04429135099053383, 0);
  g->Polynomial(961, 5742, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5742, 5743);
  g->Binary(ynn_binary_add, 5743, 5500, 5740);
  g->Binary(ynn_binary_multiply, 961, 5498, 5741);
  g->Binary(ynn_binary_multiply, 5741, 5740, 962);
  g->Binary(ynn_binary_multiply, 962, 958, 963);
  g->Quantize(963, 964, 0.10629922151565552, 0);
  g->Transpose(6689, 4168, {1,0});
  g->Binary(ynn_binary_multiply, 4165, 4167, 4163);
  g->Dot(964, 4168, YNN_INVALID_VALUE_ID, 4162, 1);
  g->DequantizeTensor(4162, YNN_INVALID_VALUE_ID, 4163, 4164);
  g->QuantizeTensor(4164, 6504, 4166, 966);
  g->Dequantize(966, 967, 0.045032795518636703, 0);
  g->Unary(ynn_unary_square, 967, 968);
  g->Reduce(ynn_reduce_sum, 968, 5745, {2}, true);
  g->ShapeProduct(968, 5744, {2});
  g->Binary(ynn_binary_divide, 5745, 5744, 969);
  g->Binary(ynn_binary_add, 969, 6539, 970);
  g->Unary(ynn_unary_rsqrt, 970, 971);
  g->Binary(ynn_binary_multiply, 967, 971, 972);
  g->Binary(ynn_binary_multiply, 972, 6692, 973);
  g->Binary(ynn_binary_add, 945, 973, 974);
  g->Binary(ynn_binary_multiply, 974, 6684, 975);
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
  g->Quantize(982, 983, 0.18704485893249512, 0);
  g->Transpose(6713, 4175, {1,0});
  g->Binary(ynn_binary_multiply, 4172, 4174, 4170);
  g->Dot(983, 4175, YNN_INVALID_VALUE_ID, 4169, 1);
  g->DequantizeTensor(4169, YNN_INVALID_VALUE_ID, 4170, 4171);
  g->QuantizeTensor(4171, 6504, 4173, 984);
  g->Dequantize(984, 985, 0.2814960777759552, 0);
  g->SplitDim(985, 986, 2, {8,256});
  g->FuseDims(986, 989, 1, 2);
  g->SplitDim(989, 988, 1, {8,1});
  g->Unary(ynn_unary_square, 988, 990);
  g->Reduce(ynn_reduce_sum, 990, 5749, {3}, true);
  g->ShapeProduct(990, 5748, {3});
  g->Binary(ynn_binary_divide, 5749, 5748, 991);
  g->Binary(ynn_binary_add, 991, 6539, 992);
  g->Unary(ynn_unary_rsqrt, 992, 993);
  g->Binary(ynn_binary_multiply, 988, 993, 994);
  g->Binary(ynn_binary_multiply, 994, 6712, 995);
  g->Slice(995, 996, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(995, 997, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 997, 998);
  g->Concat({998,996}, 1000, 3);
  g->Binary(ynn_binary_multiply, 995, 3067, 1001);
  g->Binary(ynn_binary_multiply, 1000, 3172, 1002);
  g->Binary(ynn_binary_add, 1001, 1002, 1003);
}

// Scope: "Layer15 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7190, 1004, 0.0059552486054599285, 0);
  g->Dequantize(7205, 1005, 0.047244105488061905, 0);
  g->Matmul(1003, 1004, 1006, false, true);
  g->Mask(1006, 6552, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6552, 5753, {-1}, true);
  g->Binary(ynn_binary_subtract, 6552, 5753, 5750);
  g->Unary(ynn_unary_exp, 5750, 5751);
  g->Reduce(ynn_reduce_sum, 5751, 5754, {-1}, true);
  g->Binary(ynn_binary_divide, 5500, 5754, 5752);
  g->Binary(ynn_binary_multiply, 5751, 5752, 1007);
  g->Matmul(1007, 1005, 1008, false, false);
}

// Scope: "Layer15 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(1008, 1011, 1, 2);
  g->SplitDim(1011, 1010, 1, {1,8});
  g->FuseDims(1010, 1012, 2, 2);
  g->Quantize(1012, 1013, 0.02436024509370327, 0);
  g->Transpose(6711, 4182, {1,0});
  g->Binary(ynn_binary_multiply, 4179, 4181, 4177);
  g->Dot(1013, 4182, YNN_INVALID_VALUE_ID, 4176, 1);
  g->DequantizeTensor(4176, YNN_INVALID_VALUE_ID, 4177, 4178);
  g->QuantizeTensor(4178, 6504, 4180, 1014);
  g->Dequantize(1014, 1015, 0.060289591550827026, 0);
}

// Scope: "Layer15 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 975, 977);
  g->Reduce(ynn_reduce_sum, 977, 5747, {2}, true);
  g->ShapeProduct(977, 5746, {2});
  g->Binary(ynn_binary_divide, 5747, 5746, 978);
  g->Binary(ynn_binary_add, 978, 6539, 979);
  g->Unary(ynn_unary_rsqrt, 979, 980);
  g->Binary(ynn_binary_multiply, 975, 980, 981);
  g->Binary(ynn_binary_multiply, 981, 6700, 982);
  BuildLayer15AttentionQueryProjection(ctx);
  BuildLayer15AttentionSdpa(ctx);
  BuildLayer15AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1015, 1016);
  g->Reduce(ynn_reduce_sum, 1016, 5756, {2}, true);
  g->ShapeProduct(1016, 5755, {2});
  g->Binary(ynn_binary_divide, 5756, 5755, 1017);
  g->Binary(ynn_binary_add, 1017, 6539, 1018);
  g->Unary(ynn_unary_rsqrt, 1018, 1019);
  g->Binary(ynn_binary_multiply, 1015, 1019, 1020);
  g->Binary(ynn_binary_multiply, 1020, 6707, 1022);
  g->Binary(ynn_binary_add, 1022, 975, 1023);
}

// Scope: "Layer15 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1023, 1024);
  g->Reduce(ynn_reduce_sum, 1024, 5758, {2}, true);
  g->ShapeProduct(1024, 5757, {2});
  g->Binary(ynn_binary_divide, 5758, 5757, 1025);
  g->Binary(ynn_binary_add, 1025, 6539, 1026);
  g->Unary(ynn_unary_rsqrt, 1026, 1027);
  g->Binary(ynn_binary_multiply, 1023, 1027, 1028);
  g->Binary(ynn_binary_multiply, 1028, 6710, 1029);
  g->Quantize(1029, 1030, 0.023188970983028412, 0);
  g->Transpose(6704, 4189, {1,0});
  g->Binary(ynn_binary_multiply, 4186, 4188, 4184);
  g->Dot(1030, 4189, YNN_INVALID_VALUE_ID, 4183, 1);
  g->DequantizeTensor(4183, YNN_INVALID_VALUE_ID, 4184, 4185);
  g->QuantizeTensor(4185, 6504, 4187, 1031);
  g->Dequantize(1031, 1033, 0.030511820688843727, 0);
  g->Transpose(6703, 4194, {1,0});
  g->Binary(ynn_binary_multiply, 4186, 4193, 4191);
  g->Dot(1030, 4194, YNN_INVALID_VALUE_ID, 4190, 1);
  g->DequantizeTensor(4190, YNN_INVALID_VALUE_ID, 4191, 4192);
  g->QuantizeTensor(4192, 6504, 4187, 1034);
  g->Dequantize(1034, 1035, 0.030511820688843727, 0);
  g->Polynomial(1035, 5761, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5761, 5762);
  g->Binary(ynn_binary_add, 5762, 5500, 5759);
  g->Binary(ynn_binary_multiply, 1035, 5498, 5760);
  g->Binary(ynn_binary_multiply, 5760, 5759, 1036);
  g->Binary(ynn_binary_multiply, 1033, 1036, 1037);
  g->Quantize(1037, 1038, 0.02005414292216301, 0);
  g->Transpose(6702, 4201, {1,0});
  g->Binary(ynn_binary_multiply, 4198, 4200, 4196);
  g->Dot(1038, 4201, YNN_INVALID_VALUE_ID, 4195, 1);
  g->DequantizeTensor(4195, YNN_INVALID_VALUE_ID, 4196, 4197);
  g->QuantizeTensor(4197, 6504, 4199, 1039);
  g->Dequantize(1039, 1040, 0.008105741813778877, 0);
  g->Unary(ynn_unary_square, 1040, 1041);
  g->Reduce(ynn_reduce_sum, 1041, 5764, {2}, true);
  g->ShapeProduct(1041, 5763, {2});
  g->Binary(ynn_binary_divide, 5764, 5763, 1043);
  g->Binary(ynn_binary_add, 1043, 6539, 1044);
  g->Unary(ynn_unary_rsqrt, 1044, 1045);
  g->Binary(ynn_binary_multiply, 1040, 1045, 1046);
  g->Binary(ynn_binary_multiply, 1046, 6708, 1047);
  g->Binary(ynn_binary_add, 1047, 1023, 1048);
}

// Scope: "Layer15 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(427, 1049, {0,0,15,0}, {-1,-1,1,-1});
  g->Reshape(1049, 1050, {1,1,256});
  g->Unary(ynn_unary_square, 1050, 1051);
  g->Reduce(ynn_reduce_sum, 1051, 5766, {2}, true);
  g->ShapeProduct(1051, 5765, {2});
  g->Binary(ynn_binary_divide, 5766, 5765, 1052);
  g->Binary(ynn_binary_add, 1052, 6539, 1054);
  g->Unary(ynn_unary_rsqrt, 1054, 1055);
  g->Binary(ynn_binary_multiply, 1050, 1055, 1056);
  g->Binary(ynn_binary_multiply, 1056, 7118, 1057);
  g->Binary(ynn_binary_multiply, 7126, 6542, 1058);
  g->Binary(ynn_binary_add, 1057, 1058, 1059);
  g->Binary(ynn_binary_multiply, 1059, 6536, 1060);
  g->Quantize(1048, 1061, 0.196418896317482, 0);
  g->Transpose(6705, 4208, {1,0});
  g->Binary(ynn_binary_multiply, 4205, 4207, 4203);
  g->Dot(1061, 4208, YNN_INVALID_VALUE_ID, 4202, 1);
  g->DequantizeTensor(4202, YNN_INVALID_VALUE_ID, 4203, 4204);
  g->QuantizeTensor(4204, 6504, 4206, 1062);
  g->Dequantize(1062, 1063, 0.05930119380354881, 0);
  g->Polynomial(1063, 5769, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5769, 5770);
  g->Binary(ynn_binary_add, 5770, 5500, 5767);
  g->Binary(ynn_binary_multiply, 1063, 5498, 5768);
  g->Binary(ynn_binary_multiply, 5768, 5767, 1067);
  g->Binary(ynn_binary_multiply, 1067, 1060, 1068);
  g->Quantize(1068, 1069, 0.6023622155189514, 0);
  g->Transpose(6706, 4215, {1,0});
  g->Binary(ynn_binary_multiply, 4212, 4214, 4210);
  g->Dot(1069, 4215, YNN_INVALID_VALUE_ID, 4209, 1);
  g->DequantizeTensor(4209, YNN_INVALID_VALUE_ID, 4210, 4211);
  g->QuantizeTensor(4211, 6504, 4213, 1070);
  g->Dequantize(1070, 1071, 0.33502069115638733, 0);
  g->Unary(ynn_unary_square, 1071, 1072);
  g->Reduce(ynn_reduce_sum, 1072, 5772, {2}, true);
  g->ShapeProduct(1072, 5771, {2});
  g->Binary(ynn_binary_divide, 5772, 5771, 1073);
  g->Binary(ynn_binary_add, 1073, 6539, 1074);
  g->Unary(ynn_unary_rsqrt, 1074, 1075);
  g->Binary(ynn_binary_multiply, 1071, 1075, 1076);
  g->Binary(ynn_binary_multiply, 1076, 6709, 1078);
  g->Binary(ynn_binary_add, 1048, 1078, 1079);
  g->Binary(ynn_binary_multiply, 1079, 6701, 1080);
}

// Scope: "Layer15"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15(Context& ctx) {
  BuildLayer15Attention(ctx);
  BuildLayer15Mlp(ctx);
  BuildLayer15PerLayerEmbedding(ctx);
}

}  // namespace BuildGemma4DecodeSource
