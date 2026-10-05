// Generated YNNPACK builder; do not edit.
#include "gemma4_decode_builder.h"

namespace BuildGemma4DecodeSource {

// Scope: "Layer8 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(59, 60, 0.0820433720946312, 0);
  g->Transpose(7001, 3721, {1,0});
  g->Binary(ynn_binary_multiply, 3718, 3720, 3716);
  g->Dot(60, 3721, YNN_INVALID_VALUE_ID, 3715, 1);
  g->DequantizeTensor(3715, YNN_INVALID_VALUE_ID, 3716, 3717);
  g->QuantizeTensor(3717, 6412, 3719, 61);
  g->Dequantize(61, 62, 0.09251969307661057, 0);
  g->Reshape(62, 63, {1,1,1,256});
  g->Reshape(63, 64, {1,1,1,256});
  g->Unary(ynn_unary_square, 64, 65);
  g->Reduce(ynn_reduce_sum, 65, 5490, {3}, true);
  g->ShapeProduct(65, 5489, {3});
  g->Binary(ynn_binary_divide, 5490, 5489, 66);
  g->Binary(ynn_binary_add, 66, 6446, 67);
  g->Binary(ynn_binary_pow, 67, 6448, 69);
  g->Binary(ynn_binary_multiply, 64, 69, 70);
  g->Convert(7000, 71);
  g->Binary(ynn_binary_multiply, 70, 71, 72);
  g->Slice(72, 73, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(72, 74, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 74, 75);
  g->Concat({75,73}, 76, 3);
  g->Binary(ynn_binary_multiply, 72, 2173, 77);
  g->Binary(ynn_binary_multiply, 76, 3050, 78);
  g->Binary(ynn_binary_add, 77, 78, 80);
  g->Transpose(7005, 3726, {1,0});
  g->Binary(ynn_binary_multiply, 3718, 3725, 3723);
  g->Dot(60, 3726, YNN_INVALID_VALUE_ID, 3722, 1);
  g->DequantizeTensor(3722, YNN_INVALID_VALUE_ID, 3723, 3724);
  g->QuantizeTensor(3724, 6412, 3719, 81);
  g->Dequantize(81, 82, 0.09251969307661057, 0);
  g->Reshape(82, 83, {1,1,1,256});
  g->Reshape(83, 84, {1,1,1,256});
  g->Unary(ynn_unary_square, 84, 85);
  g->Reduce(ynn_reduce_sum, 85, 5492, {3}, true);
  g->ShapeProduct(85, 5491, {3});
  g->Binary(ynn_binary_divide, 5492, 5491, 86);
  g->Binary(ynn_binary_add, 86, 6446, 87);
  g->Binary(ynn_binary_pow, 87, 6448, 88);
  g->Binary(ynn_binary_multiply, 84, 88, 90);
}

// Scope: "Layer8 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(80, 91, 0.006215503439307213, 0);
  g->Append(6426, 91, 7075, 2, s2, slinky::expr(int64_t{1}));
  g->View(7075, 7105, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7105, 92, 0.006215503439307213, 0);
  g->Quantize(90, 93, 0.047244105488061905, 0);
  g->Append(6441, 93, 7090, 2, s2, slinky::expr(int64_t{1}));
  g->View(7090, 7120, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7120, 94, 0.047244105488061905, 0);
}

// Scope: "Layer8 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(7004, 3739, {1,0});
  g->Binary(ynn_binary_multiply, 3718, 3738, 3735);
  g->Dot(60, 3739, YNN_INVALID_VALUE_ID, 3734, 1);
  g->DequantizeTensor(3734, YNN_INVALID_VALUE_ID, 3735, 3736);
  g->QuantizeTensor(3736, 6412, 3737, 96);
  g->Dequantize(96, 97, 0.1250000149011612, 0);
  g->SplitDim(97, 98, 2, {8,256});
  g->FuseDims(98, 100, 1, 2);
  g->SplitDim(100, 99, 1, {8,1});
  g->Unary(ynn_unary_square, 99, 101);
  g->Reduce(ynn_reduce_sum, 101, 5494, {3}, true);
  g->ShapeProduct(101, 5493, {3});
  g->Binary(ynn_binary_divide, 5494, 5493, 102);
  g->Binary(ynn_binary_add, 102, 6446, 103);
  g->Binary(ynn_binary_pow, 103, 6448, 104);
  g->Binary(ynn_binary_multiply, 99, 104, 105);
  g->Convert(7003, 106);
  g->Binary(ynn_binary_multiply, 105, 106, 109);
  g->Slice(109, 110, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(109, 111, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 111, 112);
  g->Concat({112,110}, 113, 3);
  g->Binary(ynn_binary_multiply, 109, 2173, 114);
  g->Binary(ynn_binary_multiply, 113, 3050, 115);
  g->Binary(ynn_binary_add, 114, 115, 116);
}

// Scope: "Layer8 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(116, 92, 117, false, true);
  g->Mask(117, 6486, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6486, 5498, {-1}, true);
  g->Binary(ynn_binary_subtract, 6486, 5498, 5495);
  g->Unary(ynn_unary_exp, 5495, 5496);
  g->Reduce(ynn_reduce_sum, 5496, 5499, {-1}, true);
  g->Binary(ynn_binary_divide, 5474, 5499, 5497);
  g->Binary(ynn_binary_multiply, 5496, 5497, 118);
  g->Matmul(118, 94, 119, false, false);
}

// Scope: "Layer8 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(119, 121, 1, 2);
  g->SplitDim(121, 120, 1, {1,8});
  g->FuseDims(120, 122, 2, 2);
  g->Quantize(122, 123, 0.025713592767715454, 0);
  g->Transpose(7002, 3746, {1,0});
  g->Binary(ynn_binary_multiply, 3743, 3745, 3741);
  g->Dot(123, 3746, YNN_INVALID_VALUE_ID, 3740, 1);
  g->DequantizeTensor(3740, YNN_INVALID_VALUE_ID, 3741, 3742);
  g->QuantizeTensor(3742, 6412, 3744, 124);
  g->Dequantize(124, 125, 0.022537967190146446, 0);
}

// Scope: "Layer8 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 51, 52);
  g->Reduce(ynn_reduce_sum, 52, 5488, {2}, true);
  g->ShapeProduct(52, 5487, {2});
  g->Binary(ynn_binary_divide, 5488, 5487, 53);
  g->Binary(ynn_binary_add, 53, 6446, 54);
  g->Binary(ynn_binary_pow, 54, 6448, 55);
  g->Binary(ynn_binary_multiply, 51, 55, 56);
  g->Convert(6989, 58);
  g->Binary(ynn_binary_multiply, 56, 58, 59);
  BuildLayer8AttentionKvProjection(ctx);
  BuildLayer8AttentionCacheUpdate(ctx);
  BuildLayer8AttentionQueryProjection(ctx);
  BuildLayer8AttentionSdpa(ctx);
  BuildLayer8AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 125, 126);
  g->Reduce(ynn_reduce_sum, 126, 5501, {2}, true);
  g->ShapeProduct(126, 5500, {2});
  g->Binary(ynn_binary_divide, 5501, 5500, 127);
  g->Binary(ynn_binary_add, 127, 6446, 128);
  g->Binary(ynn_binary_pow, 128, 6448, 130);
  g->Binary(ynn_binary_multiply, 125, 130, 131);
  g->Convert(6996, 132);
  g->Binary(ynn_binary_multiply, 131, 132, 133);
  g->Binary(ynn_binary_add, 51, 133, 134);
}

// Scope: "Layer8 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 134, 135);
  g->Reduce(ynn_reduce_sum, 135, 5503, {2}, true);
  g->ShapeProduct(135, 5502, {2});
  g->Binary(ynn_binary_divide, 5503, 5502, 136);
  g->Binary(ynn_binary_add, 136, 6446, 137);
  g->Binary(ynn_binary_pow, 137, 6448, 138);
  g->Binary(ynn_binary_multiply, 134, 138, 139);
  g->Convert(6999, 141);
  g->Binary(ynn_binary_multiply, 139, 141, 142);
  g->Quantize(142, 143, 0.015404289588332176, 0);
  g->Transpose(6993, 3758, {1,0});
  g->Binary(ynn_binary_multiply, 3755, 3757, 3753);
  g->Dot(143, 3758, YNN_INVALID_VALUE_ID, 3752, 1);
  g->DequantizeTensor(3752, YNN_INVALID_VALUE_ID, 3753, 3754);
  g->QuantizeTensor(3754, 6412, 3756, 144);
  g->Dequantize(144, 145, 0.018823828548192978, 0);
  g->Transpose(6992, 3763, {1,0});
  g->Binary(ynn_binary_multiply, 3755, 3762, 3760);
  g->Dot(143, 3763, YNN_INVALID_VALUE_ID, 3759, 1);
  g->DequantizeTensor(3759, YNN_INVALID_VALUE_ID, 3760, 3761);
  g->QuantizeTensor(3761, 6412, 3756, 146);
  g->Dequantize(146, 147, 0.018823828548192978, 0);
  g->Polynomial(147, 5506, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5506, 5507);
  g->Binary(ynn_binary_add, 5507, 5474, 5504);
  g->Binary(ynn_binary_multiply, 147, 5472, 5505);
  g->Binary(ynn_binary_multiply, 5505, 5504, 148);
  g->Binary(ynn_binary_multiply, 145, 148, 149);
  g->Quantize(149, 151, 0.012610738165676594, 0);
  g->Transpose(6991, 3770, {1,0});
  g->Binary(ynn_binary_multiply, 3767, 3769, 3765);
  g->Dot(151, 3770, YNN_INVALID_VALUE_ID, 3764, 1);
  g->DequantizeTensor(3764, YNN_INVALID_VALUE_ID, 3765, 3766);
  g->QuantizeTensor(3766, 6412, 3768, 152);
  g->Dequantize(152, 153, 0.009271269664168358, 0);
  g->Unary(ynn_unary_square, 153, 154);
  g->Reduce(ynn_reduce_sum, 154, 5513, {2}, true);
  g->ShapeProduct(154, 5512, {2});
  g->Binary(ynn_binary_divide, 5513, 5512, 155);
  g->Binary(ynn_binary_add, 155, 6446, 156);
  g->Binary(ynn_binary_pow, 156, 6448, 157);
  g->Binary(ynn_binary_multiply, 153, 157, 158);
  g->Convert(6997, 159);
  g->Binary(ynn_binary_multiply, 158, 159, 160);
  g->Binary(ynn_binary_add, 134, 160, 162);
}

// Scope: "Layer8 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1064, 163, {0,0,8,0}, {-1,-1,1,-1});
  g->Reshape(163, 164, {1,1,256});
  g->Binary(ynn_binary_add, 164, 7059, 165);
  g->Binary(ynn_binary_multiply, 165, 6444, 166);
  g->Quantize(162, 167, 0.19172413647174835, 0);
  g->Transpose(6994, 3777, {1,0});
  g->Binary(ynn_binary_multiply, 3774, 3776, 3772);
  g->Dot(167, 3777, YNN_INVALID_VALUE_ID, 3771, 1);
  g->DequantizeTensor(3771, YNN_INVALID_VALUE_ID, 3772, 3773);
  g->QuantizeTensor(3773, 6412, 3775, 168);
  g->Dequantize(168, 169, 0.11515748500823975, 0);
  g->Polynomial(169, 5516, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5516, 5517);
  g->Binary(ynn_binary_add, 5517, 5474, 5514);
  g->Binary(ynn_binary_multiply, 169, 5472, 5515);
  g->Binary(ynn_binary_multiply, 5515, 5514, 170);
  g->Binary(ynn_binary_multiply, 170, 166, 171);
  g->Quantize(171, 173, 0.787401556968689, 0);
  g->Transpose(6995, 3784, {1,0});
  g->Binary(ynn_binary_multiply, 3781, 3783, 3779);
  g->Dot(173, 3784, YNN_INVALID_VALUE_ID, 3778, 1);
  g->DequantizeTensor(3778, YNN_INVALID_VALUE_ID, 3779, 3780);
  g->QuantizeTensor(3780, 6412, 3782, 174);
  g->Dequantize(174, 175, 0.2950586676597595, 0);
  g->Unary(ynn_unary_square, 175, 176);
  g->Reduce(ynn_reduce_sum, 176, 5519, {2}, true);
  g->ShapeProduct(176, 5518, {2});
  g->Binary(ynn_binary_divide, 5519, 5518, 177);
  g->Binary(ynn_binary_add, 177, 6446, 178);
  g->Binary(ynn_binary_pow, 178, 6448, 179);
  g->Binary(ynn_binary_multiply, 175, 179, 180);
  g->Convert(6998, 181);
  g->Binary(ynn_binary_multiply, 180, 181, 182);
  g->Binary(ynn_binary_add, 162, 182, 184);
  g->Convert(6990, 185);
  g->Binary(ynn_binary_multiply, 184, 185, 186);
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
  g->Quantize(193, 195, 0.016753647476434708, 0);
  g->Transpose(7018, 3798, {1,0});
  g->Binary(ynn_binary_multiply, 3795, 3797, 3793);
  g->Dot(195, 3798, YNN_INVALID_VALUE_ID, 3792, 1);
  g->DequantizeTensor(3792, YNN_INVALID_VALUE_ID, 3793, 3794);
  g->QuantizeTensor(3794, 6412, 3796, 196);
  g->Dequantize(196, 197, 0.020177174359560013, 0);
  g->Reshape(197, 198, {1,1,1,512});
  g->Reshape(198, 199, {1,1,1,512});
  g->Unary(ynn_unary_square, 199, 200);
  g->Reduce(ynn_reduce_sum, 200, 5523, {3}, true);
  g->ShapeProduct(200, 5522, {3});
  g->Binary(ynn_binary_divide, 5523, 5522, 201);
  g->Binary(ynn_binary_add, 201, 6446, 202);
  g->Binary(ynn_binary_pow, 202, 6448, 203);
  g->Binary(ynn_binary_multiply, 199, 203, 204);
  g->Convert(7017, 206);
  g->Binary(ynn_binary_multiply, 204, 206, 207);
  g->Slice(207, 208, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(207, 209, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 209, 210);
  g->Concat({210,208}, 211, 3);
  g->Binary(ynn_binary_multiply, 207, 3471, 212);
  g->Binary(ynn_binary_multiply, 211, 3576, 213);
  g->Binary(ynn_binary_add, 212, 213, 214);
  g->Transpose(7022, 3803, {1,0});
  g->Binary(ynn_binary_multiply, 3795, 3802, 3800);
  g->Dot(195, 3803, YNN_INVALID_VALUE_ID, 3799, 1);
  g->DequantizeTensor(3799, YNN_INVALID_VALUE_ID, 3800, 3801);
  g->QuantizeTensor(3801, 6412, 3796, 217);
  g->Dequantize(217, 218, 0.020177174359560013, 0);
  g->Reshape(218, 219, {1,1,1,512});
  g->Reshape(219, 220, {1,1,1,512});
  g->Unary(ynn_unary_square, 220, 221);
  g->Reduce(ynn_reduce_sum, 221, 5527, {3}, true);
  g->ShapeProduct(221, 5526, {3});
  g->Binary(ynn_binary_divide, 5527, 5526, 222);
  g->Binary(ynn_binary_add, 222, 6446, 223);
  g->Binary(ynn_binary_pow, 223, 6448, 224);
  g->Binary(ynn_binary_multiply, 220, 224, 225);
}

// Scope: "Layer9 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(214, 226, 0.0010733711533248425, 0);
  g->Append(6427, 226, 7076, 2, s2, slinky::expr(int64_t{1}));
  g->View(7076, 7106, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7106, 228, 0.0010733711533248425, 0);
  g->Quantize(225, 229, 0.01785714365541935, 0);
  g->Append(6442, 229, 7091, 2, s2, slinky::expr(int64_t{1}));
  g->View(7091, 7121, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7121, 230, 0.01785714365541935, 0);
}

// Scope: "Layer9 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(7021, 3809, {1,0});
  g->Binary(ynn_binary_multiply, 3795, 3808, 3805);
  g->Dot(195, 3809, YNN_INVALID_VALUE_ID, 3804, 1);
  g->DequantizeTensor(3804, YNN_INVALID_VALUE_ID, 3805, 3806);
  g->QuantizeTensor(3806, 6412, 3807, 231);
  g->Dequantize(231, 232, 0.029650600627064705, 0);
  g->SplitDim(232, 234, 2, {8,512});
  g->FuseDims(234, 236, 1, 2);
  g->SplitDim(236, 235, 1, {8,1});
  g->Unary(ynn_unary_square, 235, 237);
  g->Reduce(ynn_reduce_sum, 237, 5529, {3}, true);
  g->ShapeProduct(237, 5528, {3});
  g->Binary(ynn_binary_divide, 5529, 5528, 238);
  g->Binary(ynn_binary_add, 238, 6446, 239);
  g->Binary(ynn_binary_pow, 239, 6448, 240);
  g->Binary(ynn_binary_multiply, 235, 240, 241);
  g->Convert(7020, 242);
  g->Binary(ynn_binary_multiply, 241, 242, 243);
  g->Slice(243, 244, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(243, 246, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 246, 247);
  g->Concat({247,244}, 248, 3);
  g->Binary(ynn_binary_multiply, 243, 3471, 249);
  g->Binary(ynn_binary_multiply, 248, 3576, 250);
  g->Binary(ynn_binary_add, 249, 250, 251);
}

// Scope: "Layer9 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(251, 228, 252, false, true);
  g->Mask(252, 6487, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 6487, 5533, {-1}, true);
  g->Binary(ynn_binary_subtract, 6487, 5533, 5530);
  g->Unary(ynn_unary_exp, 5530, 5531);
  g->Reduce(ynn_reduce_sum, 5531, 5534, {-1}, true);
  g->Binary(ynn_binary_divide, 5474, 5534, 5532);
  g->Binary(ynn_binary_multiply, 5531, 5532, 253);
  g->Matmul(253, 230, 254, false, false);
}

// Scope: "Layer9 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(254, 257, 1, 2);
  g->SplitDim(257, 256, 1, {1,8});
  g->FuseDims(256, 258, 2, 2);
  g->Quantize(258, 259, 0.017962608486413956, 0);
  g->Transpose(7019, 3816, {1,0});
  g->Binary(ynn_binary_multiply, 3813, 3815, 3811);
  g->Dot(259, 3816, YNN_INVALID_VALUE_ID, 3810, 1);
  g->DequantizeTensor(3810, YNN_INVALID_VALUE_ID, 3811, 3812);
  g->QuantizeTensor(3812, 6412, 3814, 260);
  g->Dequantize(260, 261, 0.02776472456753254, 0);
}

// Scope: "Layer9 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 186, 187);
  g->Reduce(ynn_reduce_sum, 187, 5521, {2}, true);
  g->ShapeProduct(187, 5520, {2});
  g->Binary(ynn_binary_divide, 5521, 5520, 188);
  g->Binary(ynn_binary_add, 188, 6446, 189);
  g->Binary(ynn_binary_pow, 189, 6448, 190);
  g->Binary(ynn_binary_multiply, 186, 190, 191);
  g->Convert(7006, 192);
  g->Binary(ynn_binary_multiply, 191, 192, 193);
  BuildLayer9AttentionKvProjection(ctx);
  BuildLayer9AttentionCacheUpdate(ctx);
  BuildLayer9AttentionQueryProjection(ctx);
  BuildLayer9AttentionSdpa(ctx);
  BuildLayer9AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 261, 262);
  g->Reduce(ynn_reduce_sum, 262, 5536, {2}, true);
  g->ShapeProduct(262, 5535, {2});
  g->Binary(ynn_binary_divide, 5536, 5535, 263);
  g->Binary(ynn_binary_add, 263, 6446, 264);
  g->Binary(ynn_binary_pow, 264, 6448, 265);
  g->Binary(ynn_binary_multiply, 261, 265, 266);
  g->Convert(7013, 268);
  g->Binary(ynn_binary_multiply, 266, 268, 269);
  g->Binary(ynn_binary_add, 186, 269, 270);
}

// Scope: "Layer9 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 270, 271);
  g->Reduce(ynn_reduce_sum, 271, 5538, {2}, true);
  g->ShapeProduct(271, 5537, {2});
  g->Binary(ynn_binary_divide, 5538, 5537, 272);
  g->Binary(ynn_binary_add, 272, 6446, 273);
  g->Binary(ynn_binary_pow, 273, 6448, 274);
  g->Binary(ynn_binary_multiply, 270, 274, 275);
  g->Convert(7016, 276);
  g->Binary(ynn_binary_multiply, 275, 276, 277);
  g->Quantize(277, 279, 0.028379227966070175, 0);
  g->Transpose(7010, 3823, {1,0});
  g->Binary(ynn_binary_multiply, 3820, 3822, 3818);
  g->Dot(279, 3823, YNN_INVALID_VALUE_ID, 3817, 1);
  g->DequantizeTensor(3817, YNN_INVALID_VALUE_ID, 3818, 3819);
  g->QuantizeTensor(3819, 6412, 3821, 280);
  g->Dequantize(280, 281, 0.01556349452584982, 0);
  g->Transpose(7009, 3828, {1,0});
  g->Binary(ynn_binary_multiply, 3820, 3827, 3825);
  g->Dot(279, 3828, YNN_INVALID_VALUE_ID, 3824, 1);
  g->DequantizeTensor(3824, YNN_INVALID_VALUE_ID, 3825, 3826);
  g->QuantizeTensor(3826, 6412, 3821, 282);
  g->Dequantize(282, 283, 0.01556349452584982, 0);
  g->Polynomial(283, 5541, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5541, 5542);
  g->Binary(ynn_binary_add, 5542, 5474, 5539);
  g->Binary(ynn_binary_multiply, 283, 5472, 5540);
  g->Binary(ynn_binary_multiply, 5540, 5539, 284);
  g->Binary(ynn_binary_multiply, 281, 284, 285);
  g->Quantize(285, 286, 0.011441939510405064, 0);
  g->Transpose(7008, 3835, {1,0});
  g->Binary(ynn_binary_multiply, 3832, 3834, 3830);
  g->Dot(286, 3835, YNN_INVALID_VALUE_ID, 3829, 1);
  g->DequantizeTensor(3829, YNN_INVALID_VALUE_ID, 3830, 3831);
  g->QuantizeTensor(3831, 6412, 3833, 287);
  g->Dequantize(287, 289, 0.005826006643474102, 0);
  g->Unary(ynn_unary_square, 289, 290);
  g->Reduce(ynn_reduce_sum, 290, 5544, {2}, true);
  g->ShapeProduct(290, 5543, {2});
  g->Binary(ynn_binary_divide, 5544, 5543, 291);
  g->Binary(ynn_binary_add, 291, 6446, 292);
  g->Binary(ynn_binary_pow, 292, 6448, 293);
  g->Binary(ynn_binary_multiply, 289, 293, 294);
  g->Convert(7014, 295);
  g->Binary(ynn_binary_multiply, 294, 295, 296);
  g->Binary(ynn_binary_add, 270, 296, 297);
}

// Scope: "Layer9 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1064, 298, {0,0,9,0}, {-1,-1,1,-1});
  g->Reshape(298, 300, {1,1,256});
  g->Binary(ynn_binary_add, 300, 7060, 301);
  g->Binary(ynn_binary_multiply, 301, 6444, 302);
  g->Quantize(297, 303, 0.22249335050582886, 0);
  g->Transpose(7011, 3842, {1,0});
  g->Binary(ynn_binary_multiply, 3839, 3841, 3837);
  g->Dot(303, 3842, YNN_INVALID_VALUE_ID, 3836, 1);
  g->DequantizeTensor(3836, YNN_INVALID_VALUE_ID, 3837, 3838);
  g->QuantizeTensor(3838, 6412, 3840, 304);
  g->Dequantize(304, 305, 0.04404528811573982, 0);
  g->Polynomial(305, 5547, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5547, 5548);
  g->Binary(ynn_binary_add, 5548, 5474, 5545);
  g->Binary(ynn_binary_multiply, 305, 5472, 5546);
  g->Binary(ynn_binary_multiply, 5546, 5545, 306);
  g->Binary(ynn_binary_multiply, 306, 302, 307);
  g->Quantize(307, 308, 0.12598426640033722, 0);
  g->Transpose(7012, 3849, {1,0});
  g->Binary(ynn_binary_multiply, 3846, 3848, 3844);
  g->Dot(308, 3849, YNN_INVALID_VALUE_ID, 3843, 1);
  g->DequantizeTensor(3843, YNN_INVALID_VALUE_ID, 3844, 3845);
  g->QuantizeTensor(3845, 6412, 3847, 309);
  g->Dequantize(309, 311, 0.10531344264745712, 0);
  g->Unary(ynn_unary_square, 311, 312);
  g->Reduce(ynn_reduce_sum, 312, 5550, {2}, true);
  g->ShapeProduct(312, 5549, {2});
  g->Binary(ynn_binary_divide, 5550, 5549, 313);
  g->Binary(ynn_binary_add, 313, 6446, 314);
  g->Binary(ynn_binary_pow, 314, 6448, 315);
  g->Binary(ynn_binary_multiply, 311, 315, 316);
  g->Convert(7015, 317);
  g->Binary(ynn_binary_multiply, 316, 317, 318);
  g->Binary(ynn_binary_add, 297, 318, 319);
  g->Convert(7007, 320);
  g->Binary(ynn_binary_multiply, 319, 320, 323);
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
  g->Quantize(330, 331, 0.15428009629249573, 0);
  g->Transpose(6534, 3856, {1,0});
  g->Binary(ynn_binary_multiply, 3853, 3855, 3851);
  g->Dot(331, 3856, YNN_INVALID_VALUE_ID, 3850, 1);
  g->DequantizeTensor(3850, YNN_INVALID_VALUE_ID, 3851, 3852);
  g->QuantizeTensor(3852, 6412, 3854, 332);
  g->Dequantize(332, 334, 0.19881890714168549, 0);
  g->Reshape(334, 335, {1,1,1,256});
  g->Reshape(335, 336, {1,1,1,256});
  g->Unary(ynn_unary_square, 336, 337);
  g->Reduce(ynn_reduce_sum, 337, 5554, {3}, true);
  g->ShapeProduct(337, 5553, {3});
  g->Binary(ynn_binary_divide, 5554, 5553, 338);
  g->Binary(ynn_binary_add, 338, 6446, 339);
  g->Binary(ynn_binary_pow, 339, 6448, 340);
  g->Binary(ynn_binary_multiply, 336, 340, 341);
  g->Convert(6533, 342);
  g->Binary(ynn_binary_multiply, 341, 342, 343);
  g->Slice(343, 345, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(343, 346, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 346, 347);
  g->Concat({347,345}, 348, 3);
  g->Binary(ynn_binary_multiply, 343, 2173, 349);
  g->Binary(ynn_binary_multiply, 348, 3050, 350);
  g->Binary(ynn_binary_add, 349, 350, 351);
  g->Transpose(6538, 3868, {1,0});
  g->Binary(ynn_binary_multiply, 3853, 3867, 3865);
  g->Dot(331, 3868, YNN_INVALID_VALUE_ID, 3864, 1);
  g->DequantizeTensor(3864, YNN_INVALID_VALUE_ID, 3865, 3866);
  g->QuantizeTensor(3866, 6412, 3854, 352);
  g->Dequantize(352, 353, 0.19881890714168549, 0);
  g->Reshape(353, 355, {1,1,1,256});
  g->Reshape(355, 356, {1,1,1,256});
  g->Unary(ynn_unary_square, 356, 357);
  g->Reduce(ynn_reduce_sum, 357, 5556, {3}, true);
  g->ShapeProduct(357, 5555, {3});
  g->Binary(ynn_binary_divide, 5556, 5555, 358);
  g->Binary(ynn_binary_add, 358, 6446, 359);
  g->Binary(ynn_binary_pow, 359, 6448, 360);
  g->Binary(ynn_binary_multiply, 356, 360, 361);
}

// Scope: "Layer10 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(351, 362, 0.005712664220482111, 0);
  g->Append(6415, 362, 7064, 2, s2, slinky::expr(int64_t{1}));
  g->View(7064, 7094, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7094, 364, 0.005712664220482111, 0);
  g->Quantize(361, 365, 0.047244105488061905, 0);
  g->Append(6430, 365, 7079, 2, s2, slinky::expr(int64_t{1}));
  g->View(7079, 7109, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7109, 366, 0.047244105488061905, 0);
}

// Scope: "Layer10 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(6537, 3874, {1,0});
  g->Binary(ynn_binary_multiply, 3853, 3873, 3870);
  g->Dot(331, 3874, YNN_INVALID_VALUE_ID, 3869, 1);
  g->DequantizeTensor(3869, YNN_INVALID_VALUE_ID, 3870, 3871);
  g->QuantizeTensor(3871, 6412, 3872, 367);
  g->Dequantize(367, 368, 0.3484252095222473, 0);
  g->SplitDim(368, 369, 2, {8,256});
  g->FuseDims(369, 371, 1, 2);
  g->SplitDim(371, 370, 1, {8,1});
  g->Unary(ynn_unary_square, 370, 373);
  g->Reduce(ynn_reduce_sum, 373, 5562, {3}, true);
  g->ShapeProduct(373, 5561, {3});
  g->Binary(ynn_binary_divide, 5562, 5561, 374);
  g->Binary(ynn_binary_add, 374, 6446, 375);
  g->Binary(ynn_binary_pow, 375, 6448, 376);
  g->Binary(ynn_binary_multiply, 370, 376, 377);
  g->Convert(6536, 378);
  g->Binary(ynn_binary_multiply, 377, 378, 379);
  g->Slice(379, 380, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(379, 381, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 381, 382);
  g->Concat({382,380}, 384, 3);
  g->Binary(ynn_binary_multiply, 379, 2173, 385);
  g->Binary(ynn_binary_multiply, 384, 3050, 386);
  g->Binary(ynn_binary_add, 385, 386, 387);
}

// Scope: "Layer10 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(387, 364, 388, false, true);
  g->Mask(388, 6455, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6455, 5566, {-1}, true);
  g->Binary(ynn_binary_subtract, 6455, 5566, 5563);
  g->Unary(ynn_unary_exp, 5563, 5564);
  g->Reduce(ynn_reduce_sum, 5564, 5567, {-1}, true);
  g->Binary(ynn_binary_divide, 5474, 5567, 5565);
  g->Binary(ynn_binary_multiply, 5564, 5565, 389);
  g->Matmul(389, 366, 390, false, false);
}

// Scope: "Layer10 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(390, 392, 1, 2);
  g->SplitDim(392, 391, 1, {1,8});
  g->FuseDims(391, 393, 2, 2);
  g->Quantize(393, 395, 0.028051190078258514, 0);
  g->Transpose(6535, 3888, {1,0});
  g->Binary(ynn_binary_multiply, 3885, 3887, 3883);
  g->Dot(395, 3888, YNN_INVALID_VALUE_ID, 3882, 1);
  g->DequantizeTensor(3882, YNN_INVALID_VALUE_ID, 3883, 3884);
  g->QuantizeTensor(3884, 6412, 3886, 396);
  g->Dequantize(396, 397, 0.029417896643280983, 0);
}

// Scope: "Layer10 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 323, 324);
  g->Reduce(ynn_reduce_sum, 324, 5552, {2}, true);
  g->ShapeProduct(324, 5551, {2});
  g->Binary(ynn_binary_divide, 5552, 5551, 325);
  g->Binary(ynn_binary_add, 325, 6446, 326);
  g->Binary(ynn_binary_pow, 326, 6448, 327);
  g->Binary(ynn_binary_multiply, 323, 327, 328);
  g->Convert(6522, 329);
  g->Binary(ynn_binary_multiply, 328, 329, 330);
  BuildLayer10AttentionKvProjection(ctx);
  BuildLayer10AttentionCacheUpdate(ctx);
  BuildLayer10AttentionQueryProjection(ctx);
  BuildLayer10AttentionSdpa(ctx);
  BuildLayer10AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 397, 398);
  g->Reduce(ynn_reduce_sum, 398, 5569, {2}, true);
  g->ShapeProduct(398, 5568, {2});
  g->Binary(ynn_binary_divide, 5569, 5568, 399);
  g->Binary(ynn_binary_add, 399, 6446, 400);
  g->Binary(ynn_binary_pow, 400, 6448, 401);
  g->Binary(ynn_binary_multiply, 397, 401, 402);
  g->Convert(6529, 403);
  g->Binary(ynn_binary_multiply, 402, 403, 404);
  g->Binary(ynn_binary_add, 323, 404, 406);
}

// Scope: "Layer10 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 406, 407);
  g->Reduce(ynn_reduce_sum, 407, 5571, {2}, true);
  g->ShapeProduct(407, 5570, {2});
  g->Binary(ynn_binary_divide, 5571, 5570, 408);
  g->Binary(ynn_binary_add, 408, 6446, 409);
  g->Binary(ynn_binary_pow, 409, 6448, 410);
  g->Binary(ynn_binary_multiply, 406, 410, 411);
  g->Convert(6532, 412);
  g->Binary(ynn_binary_multiply, 411, 412, 413);
  g->Quantize(413, 414, 0.018714377656579018, 0);
  g->Transpose(6526, 3895, {1,0});
  g->Binary(ynn_binary_multiply, 3892, 3894, 3890);
  g->Dot(414, 3895, YNN_INVALID_VALUE_ID, 3889, 1);
  g->DequantizeTensor(3889, YNN_INVALID_VALUE_ID, 3890, 3891);
  g->QuantizeTensor(3891, 6412, 3893, 415);
  g->Dequantize(415, 417, 0.01808563992381096, 0);
  g->Transpose(6525, 3900, {1,0});
  g->Binary(ynn_binary_multiply, 3892, 3899, 3897);
  g->Dot(414, 3900, YNN_INVALID_VALUE_ID, 3896, 1);
  g->DequantizeTensor(3896, YNN_INVALID_VALUE_ID, 3897, 3898);
  g->QuantizeTensor(3898, 6412, 3893, 418);
  g->Dequantize(418, 419, 0.01808563992381096, 0);
  g->Polynomial(419, 5574, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5574, 5575);
  g->Binary(ynn_binary_add, 5575, 5474, 5572);
  g->Binary(ynn_binary_multiply, 419, 5472, 5573);
  g->Binary(ynn_binary_multiply, 5573, 5572, 420);
  g->Binary(ynn_binary_multiply, 417, 420, 421);
  g->Quantize(421, 422, 0.01304134912788868, 0);
  g->Transpose(6524, 3907, {1,0});
  g->Binary(ynn_binary_multiply, 3904, 3906, 3902);
  g->Dot(422, 3907, YNN_INVALID_VALUE_ID, 3901, 1);
  g->DequantizeTensor(3901, YNN_INVALID_VALUE_ID, 3902, 3903);
  g->QuantizeTensor(3903, 6412, 3905, 423);
  g->Dequantize(423, 424, 0.011867290362715721, 0);
  g->Unary(ynn_unary_square, 424, 425);
  g->Reduce(ynn_reduce_sum, 425, 5579, {2}, true);
  g->ShapeProduct(425, 5578, {2});
  g->Binary(ynn_binary_divide, 5579, 5578, 428);
  g->Binary(ynn_binary_add, 428, 6446, 429);
  g->Binary(ynn_binary_pow, 429, 6448, 430);
  g->Binary(ynn_binary_multiply, 424, 430, 431);
  g->Convert(6530, 432);
  g->Binary(ynn_binary_multiply, 431, 432, 433);
  g->Binary(ynn_binary_add, 406, 433, 434);
}

// Scope: "Layer10 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1064, 435, {0,0,10,0}, {-1,-1,1,-1});
  g->Reshape(435, 436, {1,1,256});
  g->Binary(ynn_binary_add, 436, 7028, 437);
  g->Binary(ynn_binary_multiply, 437, 6444, 439);
  g->Quantize(434, 440, 0.14669467508792877, 0);
  g->Transpose(6527, 3914, {1,0});
  g->Binary(ynn_binary_multiply, 3911, 3913, 3909);
  g->Dot(440, 3914, YNN_INVALID_VALUE_ID, 3908, 1);
  g->DequantizeTensor(3908, YNN_INVALID_VALUE_ID, 3909, 3910);
  g->QuantizeTensor(3910, 6412, 3912, 441);
  g->Dequantize(441, 442, 0.038631901144981384, 0);
  g->Polynomial(442, 5582, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5582, 5583);
  g->Binary(ynn_binary_add, 5583, 5474, 5580);
  g->Binary(ynn_binary_multiply, 442, 5472, 5581);
  g->Binary(ynn_binary_multiply, 5581, 5580, 443);
  g->Binary(ynn_binary_multiply, 443, 439, 444);
  g->Quantize(444, 445, 0.05610237270593643, 0);
  g->Transpose(6528, 3921, {1,0});
  g->Binary(ynn_binary_multiply, 3918, 3920, 3916);
  g->Dot(445, 3921, YNN_INVALID_VALUE_ID, 3915, 1);
  g->DequantizeTensor(3915, YNN_INVALID_VALUE_ID, 3916, 3917);
  g->QuantizeTensor(3917, 6412, 3919, 446);
  g->Dequantize(446, 447, 0.041538726538419724, 0);
  g->Unary(ynn_unary_square, 447, 448);
  g->Reduce(ynn_reduce_sum, 448, 5585, {2}, true);
  g->ShapeProduct(448, 5584, {2});
  g->Binary(ynn_binary_divide, 5585, 5584, 450);
  g->Binary(ynn_binary_add, 450, 6446, 451);
  g->Binary(ynn_binary_pow, 451, 6448, 452);
  g->Binary(ynn_binary_multiply, 447, 452, 453);
  g->Convert(6531, 454);
  g->Binary(ynn_binary_multiply, 453, 454, 455);
  g->Binary(ynn_binary_add, 434, 455, 456);
  g->Convert(6523, 457);
  g->Binary(ynn_binary_multiply, 456, 457, 458);
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
  g->Quantize(466, 467, 0.11506716161966324, 0);
  g->Transpose(6551, 3928, {1,0});
  g->Binary(ynn_binary_multiply, 3925, 3927, 3923);
  g->Dot(467, 3928, YNN_INVALID_VALUE_ID, 3922, 1);
  g->DequantizeTensor(3922, YNN_INVALID_VALUE_ID, 3923, 3924);
  g->QuantizeTensor(3924, 6412, 3926, 468);
  g->Dequantize(468, 469, 0.12696851789951324, 0);
  g->Reshape(469, 470, {1,1,1,256});
  g->Reshape(470, 472, {1,1,1,256});
  g->Unary(ynn_unary_square, 472, 473);
  g->Reduce(ynn_reduce_sum, 473, 5589, {3}, true);
  g->ShapeProduct(473, 5588, {3});
  g->Binary(ynn_binary_divide, 5589, 5588, 474);
  g->Binary(ynn_binary_add, 474, 6446, 475);
  g->Binary(ynn_binary_pow, 475, 6448, 476);
  g->Binary(ynn_binary_multiply, 472, 476, 477);
  g->Convert(6550, 478);
  g->Binary(ynn_binary_multiply, 477, 478, 479);
  g->Slice(479, 480, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(479, 481, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 481, 483);
  g->Concat({483,480}, 484, 3);
  g->Binary(ynn_binary_multiply, 479, 2173, 485);
  g->Binary(ynn_binary_multiply, 484, 3050, 486);
  g->Binary(ynn_binary_add, 485, 486, 487);
  g->Transpose(6555, 3933, {1,0});
  g->Binary(ynn_binary_multiply, 3925, 3932, 3930);
  g->Dot(467, 3933, YNN_INVALID_VALUE_ID, 3929, 1);
  g->DequantizeTensor(3929, YNN_INVALID_VALUE_ID, 3930, 3931);
  g->QuantizeTensor(3931, 6412, 3926, 488);
  g->Dequantize(488, 489, 0.12696851789951324, 0);
  g->Reshape(489, 490, {1,1,1,256});
  g->Reshape(490, 491, {1,1,1,256});
  g->Unary(ynn_unary_square, 491, 493);
  g->Reduce(ynn_reduce_sum, 493, 5591, {3}, true);
  g->ShapeProduct(493, 5590, {3});
  g->Binary(ynn_binary_divide, 5591, 5590, 494);
  g->Binary(ynn_binary_add, 494, 6446, 495);
  g->Binary(ynn_binary_pow, 495, 6448, 496);
  g->Binary(ynn_binary_multiply, 491, 496, 497);
}

// Scope: "Layer11 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(487, 498, 0.005907459184527397, 0);
  g->Append(6416, 498, 7065, 2, s2, slinky::expr(int64_t{1}));
  g->View(7065, 7095, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7095, 499, 0.005907459184527397, 0);
  g->Quantize(497, 500, 0.047244105488061905, 0);
  g->Append(6431, 500, 7080, 2, s2, slinky::expr(int64_t{1}));
  g->View(7080, 7110, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7110, 502, 0.047244105488061905, 0);
}

// Scope: "Layer11 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(6554, 3939, {1,0});
  g->Binary(ynn_binary_multiply, 3925, 3938, 3935);
  g->Dot(467, 3939, YNN_INVALID_VALUE_ID, 3934, 1);
  g->DequantizeTensor(3934, YNN_INVALID_VALUE_ID, 3935, 3936);
  g->QuantizeTensor(3936, 6412, 3937, 503);
  g->Dequantize(503, 504, 0.2736220359802246, 0);
  g->SplitDim(504, 505, 2, {8,256});
  g->FuseDims(505, 507, 1, 2);
  g->SplitDim(507, 506, 1, {8,1});
  g->Unary(ynn_unary_square, 506, 508);
  g->Reduce(ynn_reduce_sum, 508, 5593, {3}, true);
  g->ShapeProduct(508, 5592, {3});
  g->Binary(ynn_binary_divide, 5593, 5592, 509);
  g->Binary(ynn_binary_add, 509, 6446, 511);
  g->Binary(ynn_binary_pow, 511, 6448, 512);
  g->Binary(ynn_binary_multiply, 506, 512, 513);
  g->Convert(6553, 514);
  g->Binary(ynn_binary_multiply, 513, 514, 515);
  g->Slice(515, 516, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(515, 517, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 517, 518);
  g->Concat({518,516}, 519, 3);
  g->Binary(ynn_binary_multiply, 515, 2173, 520);
  g->Binary(ynn_binary_multiply, 519, 3050, 522);
  g->Binary(ynn_binary_add, 520, 522, 523);
}

// Scope: "Layer11 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(523, 499, 524, false, true);
  g->Mask(524, 6456, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6456, 5597, {-1}, true);
  g->Binary(ynn_binary_subtract, 6456, 5597, 5594);
  g->Unary(ynn_unary_exp, 5594, 5595);
  g->Reduce(ynn_reduce_sum, 5595, 5598, {-1}, true);
  g->Binary(ynn_binary_divide, 5474, 5598, 5596);
  g->Binary(ynn_binary_multiply, 5595, 5596, 525);
  g->Matmul(525, 502, 526, false, false);
}

// Scope: "Layer11 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(526, 528, 1, 2);
  g->SplitDim(528, 527, 1, {1,8});
  g->FuseDims(527, 529, 2, 2);
  g->Quantize(529, 530, 0.026082687079906464, 0);
  g->Transpose(6552, 3946, {1,0});
  g->Binary(ynn_binary_multiply, 3943, 3945, 3941);
  g->Dot(530, 3946, YNN_INVALID_VALUE_ID, 3940, 1);
  g->DequantizeTensor(3940, YNN_INVALID_VALUE_ID, 3941, 3942);
  g->QuantizeTensor(3942, 6412, 3944, 531);
  g->Dequantize(531, 534, 0.028822369873523712, 0);
}

// Scope: "Layer11 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 458, 459);
  g->Reduce(ynn_reduce_sum, 459, 5587, {2}, true);
  g->ShapeProduct(459, 5586, {2});
  g->Binary(ynn_binary_divide, 5587, 5586, 461);
  g->Binary(ynn_binary_add, 461, 6446, 462);
  g->Binary(ynn_binary_pow, 462, 6448, 463);
  g->Binary(ynn_binary_multiply, 458, 463, 464);
  g->Convert(6539, 465);
  g->Binary(ynn_binary_multiply, 464, 465, 466);
  BuildLayer11AttentionKvProjection(ctx);
  BuildLayer11AttentionCacheUpdate(ctx);
  BuildLayer11AttentionQueryProjection(ctx);
  BuildLayer11AttentionSdpa(ctx);
  BuildLayer11AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 534, 535);
  g->Reduce(ynn_reduce_sum, 535, 5604, {2}, true);
  g->ShapeProduct(535, 5603, {2});
  g->Binary(ynn_binary_divide, 5604, 5603, 536);
  g->Binary(ynn_binary_add, 536, 6446, 537);
  g->Binary(ynn_binary_pow, 537, 6448, 538);
  g->Binary(ynn_binary_multiply, 534, 538, 539);
  g->Convert(6546, 540);
  g->Binary(ynn_binary_multiply, 539, 540, 541);
  g->Binary(ynn_binary_add, 458, 541, 542);
}

// Scope: "Layer11 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 542, 543);
  g->Reduce(ynn_reduce_sum, 543, 5606, {2}, true);
  g->ShapeProduct(543, 5605, {2});
  g->Binary(ynn_binary_divide, 5606, 5605, 545);
  g->Binary(ynn_binary_add, 545, 6446, 546);
  g->Binary(ynn_binary_pow, 546, 6448, 547);
  g->Binary(ynn_binary_multiply, 542, 547, 548);
  g->Convert(6549, 549);
  g->Binary(ynn_binary_multiply, 548, 549, 550);
  g->Quantize(550, 551, 0.015670500695705414, 0);
  g->Transpose(6543, 3953, {1,0});
  g->Binary(ynn_binary_multiply, 3950, 3952, 3948);
  g->Dot(551, 3953, YNN_INVALID_VALUE_ID, 3947, 1);
  g->DequantizeTensor(3947, YNN_INVALID_VALUE_ID, 3948, 3949);
  g->QuantizeTensor(3949, 6412, 3951, 552);
  g->Dequantize(552, 553, 0.015255915932357311, 0);
  g->Transpose(6542, 3958, {1,0});
  g->Binary(ynn_binary_multiply, 3950, 3957, 3955);
  g->Dot(551, 3958, YNN_INVALID_VALUE_ID, 3954, 1);
  g->DequantizeTensor(3954, YNN_INVALID_VALUE_ID, 3955, 3956);
  g->QuantizeTensor(3956, 6412, 3951, 555);
  g->Dequantize(555, 556, 0.015255915932357311, 0);
  g->Polynomial(556, 5609, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5609, 5610);
  g->Binary(ynn_binary_add, 5610, 5474, 5607);
  g->Binary(ynn_binary_multiply, 556, 5472, 5608);
  g->Binary(ynn_binary_multiply, 5608, 5607, 557);
  g->Binary(ynn_binary_multiply, 553, 557, 558);
  g->Quantize(558, 559, 0.011195876635611057, 0);
  g->Transpose(6541, 3965, {1,0});
  g->Binary(ynn_binary_multiply, 3962, 3964, 3960);
  g->Dot(559, 3965, YNN_INVALID_VALUE_ID, 3959, 1);
  g->DequantizeTensor(3959, YNN_INVALID_VALUE_ID, 3960, 3961);
  g->QuantizeTensor(3961, 6412, 3963, 560);
  g->Dequantize(560, 561, 0.004389102105051279, 0);
  g->Unary(ynn_unary_square, 561, 562);
  g->Reduce(ynn_reduce_sum, 562, 5612, {2}, true);
  g->ShapeProduct(562, 5611, {2});
  g->Binary(ynn_binary_divide, 5612, 5611, 563);
  g->Binary(ynn_binary_add, 563, 6446, 564);
  g->Binary(ynn_binary_pow, 564, 6448, 566);
  g->Binary(ynn_binary_multiply, 561, 566, 567);
  g->Convert(6547, 568);
  g->Binary(ynn_binary_multiply, 567, 568, 569);
  g->Binary(ynn_binary_add, 542, 569, 570);
}

// Scope: "Layer11 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1064, 571, {0,0,11,0}, {-1,-1,1,-1});
  g->Reshape(571, 572, {1,1,256});
  g->Binary(ynn_binary_add, 572, 7029, 573);
  g->Binary(ynn_binary_multiply, 573, 6444, 574);
  g->Quantize(570, 575, 0.1750430017709732, 0);
  g->Transpose(6544, 3972, {1,0});
  g->Binary(ynn_binary_multiply, 3969, 3971, 3967);
  g->Dot(575, 3972, YNN_INVALID_VALUE_ID, 3966, 1);
  g->DequantizeTensor(3966, YNN_INVALID_VALUE_ID, 3967, 3968);
  g->QuantizeTensor(3968, 6412, 3970, 577);
  g->Dequantize(577, 578, 0.07529528439044952, 0);
  g->Polynomial(578, 5615, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5615, 5616);
  g->Binary(ynn_binary_add, 5616, 5474, 5613);
  g->Binary(ynn_binary_multiply, 578, 5472, 5614);
  g->Binary(ynn_binary_multiply, 5614, 5613, 579);
  g->Binary(ynn_binary_multiply, 579, 574, 580);
  g->Quantize(580, 581, 0.15846458077430725, 0);
  g->Transpose(6545, 3979, {1,0});
  g->Binary(ynn_binary_multiply, 3976, 3978, 3974);
  g->Dot(581, 3979, YNN_INVALID_VALUE_ID, 3973, 1);
  g->DequantizeTensor(3973, YNN_INVALID_VALUE_ID, 3974, 3975);
  g->QuantizeTensor(3975, 6412, 3977, 582);
  g->Dequantize(582, 583, 0.1771666705608368, 0);
  g->Unary(ynn_unary_square, 583, 584);
  g->Reduce(ynn_reduce_sum, 584, 5618, {2}, true);
  g->ShapeProduct(584, 5617, {2});
  g->Binary(ynn_binary_divide, 5618, 5617, 585);
  g->Binary(ynn_binary_add, 585, 6446, 586);
  g->Binary(ynn_binary_pow, 586, 6448, 588);
  g->Binary(ynn_binary_multiply, 583, 588, 589);
  g->Convert(6548, 590);
  g->Binary(ynn_binary_multiply, 589, 590, 591);
  g->Binary(ynn_binary_add, 570, 591, 592);
  g->Convert(6540, 593);
  g->Binary(ynn_binary_multiply, 592, 593, 594);
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
  g->Quantize(602, 603, 0.08767248690128326, 0);
  g->Transpose(6568, 3986, {1,0});
  g->Binary(ynn_binary_multiply, 3983, 3985, 3981);
  g->Dot(603, 3986, YNN_INVALID_VALUE_ID, 3980, 1);
  g->DequantizeTensor(3980, YNN_INVALID_VALUE_ID, 3981, 3982);
  g->QuantizeTensor(3982, 6412, 3984, 604);
  g->Dequantize(604, 605, 0.08070866763591766, 0);
  g->Reshape(605, 606, {1,1,1,256});
  g->Reshape(606, 607, {1,1,1,256});
  g->Unary(ynn_unary_square, 607, 608);
  g->Reduce(ynn_reduce_sum, 608, 5622, {3}, true);
  g->ShapeProduct(608, 5621, {3});
  g->Binary(ynn_binary_divide, 5622, 5621, 610);
  g->Binary(ynn_binary_add, 610, 6446, 611);
  g->Binary(ynn_binary_pow, 611, 6448, 612);
  g->Binary(ynn_binary_multiply, 607, 612, 613);
  g->Convert(6567, 614);
  g->Binary(ynn_binary_multiply, 613, 614, 615);
  g->Slice(615, 616, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(615, 617, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 617, 618);
  g->Concat({618,616}, 619, 3);
  g->Binary(ynn_binary_multiply, 615, 2173, 621);
  g->Binary(ynn_binary_multiply, 619, 3050, 622);
  g->Binary(ynn_binary_add, 621, 622, 623);
  g->Transpose(6572, 3998, {1,0});
  g->Binary(ynn_binary_multiply, 3983, 3997, 3995);
  g->Dot(603, 3998, YNN_INVALID_VALUE_ID, 3994, 1);
  g->DequantizeTensor(3994, YNN_INVALID_VALUE_ID, 3995, 3996);
  g->QuantizeTensor(3996, 6412, 3984, 624);
  g->Dequantize(624, 625, 0.08070866763591766, 0);
  g->Reshape(625, 626, {1,1,1,256});
  g->Reshape(626, 627, {1,1,1,256});
  g->Unary(ynn_unary_square, 627, 628);
  g->Reduce(ynn_reduce_sum, 628, 5624, {3}, true);
  g->ShapeProduct(628, 5623, {3});
  g->Binary(ynn_binary_divide, 5624, 5623, 629);
  g->Binary(ynn_binary_add, 629, 6446, 631);
  g->Binary(ynn_binary_pow, 631, 6448, 632);
  g->Binary(ynn_binary_multiply, 627, 632, 633);
}

// Scope: "Layer12 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(623, 634, 0.005788442213088274, 0);
  g->Append(6417, 634, 7066, 2, s2, slinky::expr(int64_t{1}));
  g->View(7066, 7096, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7096, 635, 0.005788442213088274, 0);
  g->Quantize(633, 636, 0.047244105488061905, 0);
  g->Append(6432, 636, 7081, 2, s2, slinky::expr(int64_t{1}));
  g->View(7081, 7111, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7111, 639, 0.047244105488061905, 0);
}

// Scope: "Layer12 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(6571, 4004, {1,0});
  g->Binary(ynn_binary_multiply, 3983, 4003, 4000);
  g->Dot(603, 4004, YNN_INVALID_VALUE_ID, 3999, 1);
  g->DequantizeTensor(3999, YNN_INVALID_VALUE_ID, 4000, 4001);
  g->QuantizeTensor(4001, 6412, 4002, 640);
  g->Dequantize(640, 641, 0.12795276939868927, 0);
  g->SplitDim(641, 642, 2, {8,256});
  g->FuseDims(642, 644, 1, 2);
  g->SplitDim(644, 643, 1, {8,1});
  g->Unary(ynn_unary_square, 643, 645);
  g->Reduce(ynn_reduce_sum, 645, 5626, {3}, true);
  g->ShapeProduct(645, 5625, {3});
  g->Binary(ynn_binary_divide, 5626, 5625, 646);
  g->Binary(ynn_binary_add, 646, 6446, 647);
  g->Binary(ynn_binary_pow, 647, 6448, 648);
  g->Binary(ynn_binary_multiply, 643, 648, 650);
  g->Convert(6570, 651);
  g->Binary(ynn_binary_multiply, 650, 651, 652);
  g->Slice(652, 653, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(652, 654, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 654, 655);
  g->Concat({655,653}, 656, 3);
  g->Binary(ynn_binary_multiply, 652, 2173, 657);
  g->Binary(ynn_binary_multiply, 656, 3050, 658);
  g->Binary(ynn_binary_add, 657, 658, 659);
}

// Scope: "Layer12 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(659, 635, 661, false, true);
  g->Mask(661, 6457, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6457, 5632, {-1}, true);
  g->Binary(ynn_binary_subtract, 6457, 5632, 5629);
  g->Unary(ynn_unary_exp, 5629, 5630);
  g->Reduce(ynn_reduce_sum, 5630, 5633, {-1}, true);
  g->Binary(ynn_binary_divide, 5474, 5633, 5631);
  g->Binary(ynn_binary_multiply, 5630, 5631, 662);
  g->Matmul(662, 639, 663, false, false);
}

// Scope: "Layer12 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(663, 665, 1, 2);
  g->SplitDim(665, 664, 1, {1,8});
  g->FuseDims(664, 666, 2, 2);
  g->Quantize(666, 667, 0.028543315827846527, 0);
  g->Transpose(6569, 4011, {1,0});
  g->Binary(ynn_binary_multiply, 4008, 4010, 4006);
  g->Dot(667, 4011, YNN_INVALID_VALUE_ID, 4005, 1);
  g->DequantizeTensor(4005, YNN_INVALID_VALUE_ID, 4006, 4007);
  g->QuantizeTensor(4007, 6412, 4009, 668);
  g->Dequantize(668, 669, 0.021804405376315117, 0);
}

// Scope: "Layer12 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 594, 595);
  g->Reduce(ynn_reduce_sum, 595, 5620, {2}, true);
  g->ShapeProduct(595, 5619, {2});
  g->Binary(ynn_binary_divide, 5620, 5619, 596);
  g->Binary(ynn_binary_add, 596, 6446, 597);
  g->Binary(ynn_binary_pow, 597, 6448, 599);
  g->Binary(ynn_binary_multiply, 594, 599, 600);
  g->Convert(6556, 601);
  g->Binary(ynn_binary_multiply, 600, 601, 602);
  BuildLayer12AttentionKvProjection(ctx);
  BuildLayer12AttentionCacheUpdate(ctx);
  BuildLayer12AttentionQueryProjection(ctx);
  BuildLayer12AttentionSdpa(ctx);
  BuildLayer12AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 669, 670);
  g->Reduce(ynn_reduce_sum, 670, 5635, {2}, true);
  g->ShapeProduct(670, 5634, {2});
  g->Binary(ynn_binary_divide, 5635, 5634, 672);
  g->Binary(ynn_binary_add, 672, 6446, 673);
  g->Binary(ynn_binary_pow, 673, 6448, 674);
  g->Binary(ynn_binary_multiply, 669, 674, 675);
  g->Convert(6563, 676);
  g->Binary(ynn_binary_multiply, 675, 676, 677);
  g->Binary(ynn_binary_add, 594, 677, 678);
}

// Scope: "Layer12 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 678, 679);
  g->Reduce(ynn_reduce_sum, 679, 5637, {2}, true);
  g->ShapeProduct(679, 5636, {2});
  g->Binary(ynn_binary_divide, 5637, 5636, 680);
  g->Binary(ynn_binary_add, 680, 6446, 681);
  g->Binary(ynn_binary_pow, 681, 6448, 683);
  g->Binary(ynn_binary_multiply, 678, 683, 684);
  g->Convert(6566, 685);
  g->Binary(ynn_binary_multiply, 684, 685, 686);
  g->Quantize(686, 687, 0.013748278841376305, 0);
  g->Transpose(6560, 4018, {1,0});
  g->Binary(ynn_binary_multiply, 4015, 4017, 4013);
  g->Dot(687, 4018, YNN_INVALID_VALUE_ID, 4012, 1);
  g->DequantizeTensor(4012, YNN_INVALID_VALUE_ID, 4013, 4014);
  g->QuantizeTensor(4014, 6412, 4016, 688);
  g->Dequantize(688, 689, 0.012795286253094673, 0);
  g->Transpose(6559, 4023, {1,0});
  g->Binary(ynn_binary_multiply, 4015, 4022, 4020);
  g->Dot(687, 4023, YNN_INVALID_VALUE_ID, 4019, 1);
  g->DequantizeTensor(4019, YNN_INVALID_VALUE_ID, 4020, 4021);
  g->QuantizeTensor(4021, 6412, 4016, 690);
  g->Dequantize(690, 691, 0.012795286253094673, 0);
  g->Polynomial(691, 5640, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5640, 5641);
  g->Binary(ynn_binary_add, 5641, 5474, 5638);
  g->Binary(ynn_binary_multiply, 691, 5472, 5639);
  g->Binary(ynn_binary_multiply, 5639, 5638, 693);
  g->Binary(ynn_binary_multiply, 689, 693, 694);
  g->Quantize(694, 695, 0.00768947834149003, 0);
  g->Transpose(6558, 4030, {1,0});
  g->Binary(ynn_binary_multiply, 4027, 4029, 4025);
  g->Dot(695, 4030, YNN_INVALID_VALUE_ID, 4024, 1);
  g->DequantizeTensor(4024, YNN_INVALID_VALUE_ID, 4025, 4026);
  g->QuantizeTensor(4026, 6412, 4028, 696);
  g->Dequantize(696, 697, 0.005636297166347504, 0);
  g->Unary(ynn_unary_square, 697, 698);
  g->Reduce(ynn_reduce_sum, 698, 5643, {2}, true);
  g->ShapeProduct(698, 5642, {2});
  g->Binary(ynn_binary_divide, 5643, 5642, 699);
  g->Binary(ynn_binary_add, 699, 6446, 700);
  g->Binary(ynn_binary_pow, 700, 6448, 701);
  g->Binary(ynn_binary_multiply, 697, 701, 702);
  g->Convert(6564, 704);
  g->Binary(ynn_binary_multiply, 702, 704, 705);
  g->Binary(ynn_binary_add, 678, 705, 706);
}

// Scope: "Layer12 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1064, 707, {0,0,12,0}, {-1,-1,1,-1});
  g->Reshape(707, 708, {1,1,256});
  g->Binary(ynn_binary_add, 708, 7030, 709);
  g->Binary(ynn_binary_multiply, 709, 6444, 710);
  g->Quantize(706, 711, 0.19133253395557404, 0);
  g->Transpose(6561, 4036, {1,0});
  g->Binary(ynn_binary_multiply, 4034, 4035, 4032);
  g->Dot(711, 4036, YNN_INVALID_VALUE_ID, 4031, 1);
  g->DequantizeTensor(4031, YNN_INVALID_VALUE_ID, 4032, 4033);
  g->QuantizeTensor(4033, 6412, 3970, 712);
  g->Dequantize(712, 713, 0.07529528439044952, 0);
  g->Polynomial(713, 5646, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5646, 5647);
  g->Binary(ynn_binary_add, 5647, 5474, 5644);
  g->Binary(ynn_binary_multiply, 713, 5472, 5645);
  g->Binary(ynn_binary_multiply, 5645, 5644, 715);
  g->Binary(ynn_binary_multiply, 715, 710, 716);
  g->Quantize(716, 717, 0.12450788170099258, 0);
  g->Transpose(6562, 4043, {1,0});
  g->Binary(ynn_binary_multiply, 4040, 4042, 4038);
  g->Dot(717, 4043, YNN_INVALID_VALUE_ID, 4037, 1);
  g->DequantizeTensor(4037, YNN_INVALID_VALUE_ID, 4038, 4039);
  g->QuantizeTensor(4039, 6412, 4041, 718);
  g->Dequantize(718, 719, 0.12528184056282043, 0);
  g->Unary(ynn_unary_square, 719, 720);
  g->Reduce(ynn_reduce_sum, 720, 5649, {2}, true);
  g->ShapeProduct(720, 5648, {2});
  g->Binary(ynn_binary_divide, 5649, 5648, 721);
  g->Binary(ynn_binary_add, 721, 6446, 722);
  g->Binary(ynn_binary_pow, 722, 6448, 723);
  g->Binary(ynn_binary_multiply, 719, 723, 724);
  g->Convert(6565, 726);
  g->Binary(ynn_binary_multiply, 724, 726, 727);
  g->Binary(ynn_binary_add, 706, 727, 728);
  g->Convert(6557, 729);
  g->Binary(ynn_binary_multiply, 728, 729, 730);
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
  g->Quantize(738, 739, 0.02862965501844883, 0);
  g->Transpose(6585, 4050, {1,0});
  g->Binary(ynn_binary_multiply, 4047, 4049, 4045);
  g->Dot(739, 4050, YNN_INVALID_VALUE_ID, 4044, 1);
  g->DequantizeTensor(4044, YNN_INVALID_VALUE_ID, 4045, 4046);
  g->QuantizeTensor(4046, 6412, 4048, 740);
  g->Dequantize(740, 741, 0.035925209522247314, 0);
  g->Reshape(741, 742, {1,1,1,256});
  g->Reshape(742, 743, {1,1,1,256});
  g->Unary(ynn_unary_square, 743, 744);
  g->Reduce(ynn_reduce_sum, 744, 5653, {3}, true);
  g->ShapeProduct(744, 5652, {3});
  g->Binary(ynn_binary_divide, 5653, 5652, 745);
  g->Binary(ynn_binary_add, 745, 6446, 746);
  g->Binary(ynn_binary_pow, 746, 6448, 749);
  g->Binary(ynn_binary_multiply, 743, 749, 750);
  g->Convert(6584, 751);
  g->Binary(ynn_binary_multiply, 750, 751, 752);
  g->Slice(752, 753, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(752, 754, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 754, 755);
  g->Concat({755,753}, 756, 3);
  g->Binary(ynn_binary_multiply, 752, 2173, 757);
  g->Binary(ynn_binary_multiply, 756, 3050, 758);
  g->Binary(ynn_binary_add, 757, 758, 760);
  g->Transpose(6589, 4055, {1,0});
  g->Binary(ynn_binary_multiply, 4047, 4054, 4052);
  g->Dot(739, 4055, YNN_INVALID_VALUE_ID, 4051, 1);
  g->DequantizeTensor(4051, YNN_INVALID_VALUE_ID, 4052, 4053);
  g->QuantizeTensor(4053, 6412, 4048, 761);
  g->Dequantize(761, 762, 0.035925209522247314, 0);
  g->Reshape(762, 763, {1,1,1,256});
  g->Reshape(763, 764, {1,1,1,256});
  g->Unary(ynn_unary_square, 764, 765);
  g->Reduce(ynn_reduce_sum, 765, 5655, {3}, true);
  g->ShapeProduct(765, 5654, {3});
  g->Binary(ynn_binary_divide, 5655, 5654, 766);
  g->Binary(ynn_binary_add, 766, 6446, 767);
  g->Binary(ynn_binary_pow, 767, 6448, 768);
  g->Binary(ynn_binary_multiply, 764, 768, 770);
}

// Scope: "Layer13 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(760, 771, 0.0059552486054599285, 0);
  g->Append(6418, 771, 7067, 2, s2, slinky::expr(int64_t{1}));
  g->View(7067, 7097, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7097, 772, 0.0059552486054599285, 0);
  g->Quantize(770, 773, 0.047244105488061905, 0);
  g->Append(6433, 773, 7082, 2, s2, slinky::expr(int64_t{1}));
  g->View(7082, 7112, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7112, 774, 0.047244105488061905, 0);
}

// Scope: "Layer13 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(6588, 4060, {1,0});
  g->Binary(ynn_binary_multiply, 4047, 4059, 4057);
  g->Dot(739, 4060, YNN_INVALID_VALUE_ID, 4056, 1);
  g->DequantizeTensor(4056, YNN_INVALID_VALUE_ID, 4057, 4058);
  g->QuantizeTensor(4058, 6412, 3878, 776);
  g->Dequantize(776, 777, 0.03764764964580536, 0);
  g->SplitDim(777, 778, 2, {8,256});
  g->FuseDims(778, 780, 1, 2);
  g->SplitDim(780, 779, 1, {8,1});
  g->Unary(ynn_unary_square, 779, 781);
  g->Reduce(ynn_reduce_sum, 781, 5657, {3}, true);
  g->ShapeProduct(781, 5656, {3});
  g->Binary(ynn_binary_divide, 5657, 5656, 782);
  g->Binary(ynn_binary_add, 782, 6446, 783);
  g->Binary(ynn_binary_pow, 783, 6448, 784);
  g->Binary(ynn_binary_multiply, 779, 784, 785);
  g->Convert(6587, 786);
  g->Binary(ynn_binary_multiply, 785, 786, 788);
  g->Slice(788, 789, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(788, 790, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 790, 791);
  g->Concat({791,789}, 792, 3);
  g->Binary(ynn_binary_multiply, 788, 2173, 793);
  g->Binary(ynn_binary_multiply, 792, 3050, 794);
  g->Binary(ynn_binary_add, 793, 794, 795);
}

// Scope: "Layer13 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(795, 772, 796, false, true);
  g->Mask(796, 6458, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6458, 5661, {-1}, true);
  g->Binary(ynn_binary_subtract, 6458, 5661, 5658);
  g->Unary(ynn_unary_exp, 5658, 5659);
  g->Reduce(ynn_reduce_sum, 5659, 5662, {-1}, true);
  g->Binary(ynn_binary_divide, 5474, 5662, 5660);
  g->Binary(ynn_binary_multiply, 5659, 5660, 797);
  g->Matmul(797, 774, 798, false, false);
}

// Scope: "Layer13 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(798, 800, 1, 2);
  g->SplitDim(800, 799, 1, {1,8});
  g->FuseDims(799, 801, 2, 2);
  g->Quantize(801, 802, 0.026205718517303467, 0);
  g->Transpose(6586, 4067, {1,0});
  g->Binary(ynn_binary_multiply, 4064, 4066, 4062);
  g->Dot(802, 4067, YNN_INVALID_VALUE_ID, 4061, 1);
  g->DequantizeTensor(4061, YNN_INVALID_VALUE_ID, 4062, 4063);
  g->QuantizeTensor(4063, 6412, 4065, 803);
  g->Dequantize(803, 804, 0.03592992201447487, 0);
}

// Scope: "Layer13 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 730, 731);
  g->Reduce(ynn_reduce_sum, 731, 5651, {2}, true);
  g->ShapeProduct(731, 5650, {2});
  g->Binary(ynn_binary_divide, 5651, 5650, 732);
  g->Binary(ynn_binary_add, 732, 6446, 733);
  g->Binary(ynn_binary_pow, 733, 6448, 734);
  g->Binary(ynn_binary_multiply, 730, 734, 735);
  g->Convert(6573, 737);
  g->Binary(ynn_binary_multiply, 735, 737, 738);
  BuildLayer13AttentionKvProjection(ctx);
  BuildLayer13AttentionCacheUpdate(ctx);
  BuildLayer13AttentionQueryProjection(ctx);
  BuildLayer13AttentionSdpa(ctx);
  BuildLayer13AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 804, 805);
  g->Reduce(ynn_reduce_sum, 805, 5664, {2}, true);
  g->ShapeProduct(805, 5663, {2});
  g->Binary(ynn_binary_divide, 5664, 5663, 806);
  g->Binary(ynn_binary_add, 806, 6446, 807);
  g->Binary(ynn_binary_pow, 807, 6448, 809);
  g->Binary(ynn_binary_multiply, 804, 809, 810);
  g->Convert(6580, 811);
  g->Binary(ynn_binary_multiply, 810, 811, 812);
  g->Binary(ynn_binary_add, 730, 812, 813);
}

// Scope: "Layer13 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 813, 814);
  g->Reduce(ynn_reduce_sum, 814, 5666, {2}, true);
  g->ShapeProduct(814, 5665, {2});
  g->Binary(ynn_binary_divide, 5666, 5665, 815);
  g->Binary(ynn_binary_add, 815, 6446, 816);
  g->Binary(ynn_binary_pow, 816, 6448, 817);
  g->Binary(ynn_binary_multiply, 813, 817, 818);
  g->Convert(6583, 820);
  g->Binary(ynn_binary_multiply, 818, 820, 821);
  g->Quantize(821, 822, 0.0083004767075181, 0);
  g->Transpose(6577, 4079, {1,0});
  g->Binary(ynn_binary_multiply, 4076, 4078, 4074);
  g->Dot(822, 4079, YNN_INVALID_VALUE_ID, 4073, 1);
  g->DequantizeTensor(4073, YNN_INVALID_VALUE_ID, 4074, 4075);
  g->QuantizeTensor(4075, 6412, 4077, 823);
  g->Dequantize(823, 824, 0.011934065259993076, 0);
  g->Transpose(6576, 4084, {1,0});
  g->Binary(ynn_binary_multiply, 4076, 4083, 4081);
  g->Dot(822, 4084, YNN_INVALID_VALUE_ID, 4080, 1);
  g->DequantizeTensor(4080, YNN_INVALID_VALUE_ID, 4081, 4082);
  g->QuantizeTensor(4082, 6412, 4077, 825);
  g->Dequantize(825, 826, 0.011934065259993076, 0);
  g->Polynomial(826, 5669, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5669, 5670);
  g->Binary(ynn_binary_add, 5670, 5474, 5667);
  g->Binary(ynn_binary_multiply, 826, 5472, 5668);
  g->Binary(ynn_binary_multiply, 5668, 5667, 827);
  g->Binary(ynn_binary_multiply, 824, 827, 828);
  g->Quantize(828, 830, 0.0015532826073467731, 0);
  g->Transpose(6575, 4091, {1,0});
  g->Binary(ynn_binary_multiply, 4088, 4090, 4086);
  g->Dot(830, 4091, YNN_INVALID_VALUE_ID, 4085, 1);
  g->DequantizeTensor(4085, YNN_INVALID_VALUE_ID, 4086, 4087);
  g->QuantizeTensor(4087, 6412, 4089, 831);
  g->Dequantize(831, 832, 0.002153691602870822, 0);
  g->Unary(ynn_unary_square, 832, 833);
  g->Reduce(ynn_reduce_sum, 833, 5672, {2}, true);
  g->ShapeProduct(833, 5671, {2});
  g->Binary(ynn_binary_divide, 5672, 5671, 834);
  g->Binary(ynn_binary_add, 834, 6446, 835);
  g->Binary(ynn_binary_pow, 835, 6448, 836);
  g->Binary(ynn_binary_multiply, 832, 836, 837);
  g->Convert(6581, 838);
  g->Binary(ynn_binary_multiply, 837, 838, 839);
  g->Binary(ynn_binary_add, 813, 839, 841);
}

// Scope: "Layer13 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1064, 842, {0,0,13,0}, {-1,-1,1,-1});
  g->Reshape(842, 843, {1,1,256});
  g->Binary(ynn_binary_add, 843, 7031, 844);
  g->Binary(ynn_binary_multiply, 844, 6444, 845);
  g->Quantize(841, 846, 0.5171695351600647, 0);
  g->Transpose(6578, 4098, {1,0});
  g->Binary(ynn_binary_multiply, 4095, 4097, 4093);
  g->Dot(846, 4098, YNN_INVALID_VALUE_ID, 4092, 1);
  g->DequantizeTensor(4092, YNN_INVALID_VALUE_ID, 4093, 4094);
  g->QuantizeTensor(4094, 6412, 4096, 847);
  g->Dequantize(847, 848, 0.13385827839374542, 0);
  g->Polynomial(848, 5675, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5675, 5676);
  g->Binary(ynn_binary_add, 5676, 5474, 5673);
  g->Binary(ynn_binary_multiply, 848, 5472, 5674);
  g->Binary(ynn_binary_multiply, 5674, 5673, 849);
  g->Binary(ynn_binary_multiply, 849, 845, 850);
  g->Quantize(850, 853, 0.4094488322734833, 0);
  g->Transpose(6579, 4105, {1,0});
  g->Binary(ynn_binary_multiply, 4102, 4104, 4100);
  g->Dot(853, 4105, YNN_INVALID_VALUE_ID, 4099, 1);
  g->DequantizeTensor(4099, YNN_INVALID_VALUE_ID, 4100, 4101);
  g->QuantizeTensor(4101, 6412, 4103, 854);
  g->Dequantize(854, 855, 0.25065305829048157, 0);
  g->Unary(ynn_unary_square, 855, 856);
  g->Reduce(ynn_reduce_sum, 856, 5678, {2}, true);
  g->ShapeProduct(856, 5677, {2});
  g->Binary(ynn_binary_divide, 5678, 5677, 857);
  g->Binary(ynn_binary_add, 857, 6446, 858);
  g->Binary(ynn_binary_pow, 858, 6448, 859);
  g->Binary(ynn_binary_multiply, 855, 859, 860);
  g->Convert(6582, 861);
  g->Binary(ynn_binary_multiply, 860, 861, 862);
  g->Binary(ynn_binary_add, 841, 862, 864);
  g->Convert(6574, 865);
  g->Binary(ynn_binary_multiply, 864, 865, 866);
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
  g->Quantize(873, 875, 0.20956376194953918, 0);
  g->Transpose(6602, 4112, {1,0});
  g->Binary(ynn_binary_multiply, 4109, 4111, 4107);
  g->Dot(875, 4112, YNN_INVALID_VALUE_ID, 4106, 1);
  g->DequantizeTensor(4106, YNN_INVALID_VALUE_ID, 4107, 4108);
  g->QuantizeTensor(4108, 6412, 4110, 876);
  g->Dequantize(876, 877, 0.21751970052719116, 0);
  g->Reshape(877, 878, {1,1,1,512});
  g->Reshape(878, 879, {1,1,1,512});
  g->Unary(ynn_unary_square, 879, 880);
  g->Reduce(ynn_reduce_sum, 880, 5684, {3}, true);
  g->ShapeProduct(880, 5683, {3});
  g->Binary(ynn_binary_divide, 5684, 5683, 881);
  g->Binary(ynn_binary_add, 881, 6446, 882);
  g->Binary(ynn_binary_pow, 882, 6448, 883);
  g->Binary(ynn_binary_multiply, 879, 883, 884);
  g->Convert(6601, 886);
  g->Binary(ynn_binary_multiply, 884, 886, 887);
  g->Slice(887, 888, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(887, 889, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 889, 890);
  g->Concat({890,888}, 891, 3);
  g->Binary(ynn_binary_multiply, 887, 3471, 892);
  g->Binary(ynn_binary_multiply, 891, 3576, 893);
  g->Binary(ynn_binary_add, 892, 893, 894);
  g->Transpose(6606, 4117, {1,0});
  g->Binary(ynn_binary_multiply, 4109, 4116, 4114);
  g->Dot(875, 4117, YNN_INVALID_VALUE_ID, 4113, 1);
  g->DequantizeTensor(4113, YNN_INVALID_VALUE_ID, 4114, 4115);
  g->QuantizeTensor(4115, 6412, 4110, 896);
  g->Dequantize(896, 897, 0.21751970052719116, 0);
  g->Reshape(897, 898, {1,1,1,512});
  g->Reshape(898, 899, {1,1,1,512});
  g->Unary(ynn_unary_square, 899, 900);
  g->Reduce(ynn_reduce_sum, 900, 5686, {3}, true);
  g->ShapeProduct(900, 5685, {3});
  g->Binary(ynn_binary_divide, 5686, 5685, 901);
  g->Binary(ynn_binary_add, 901, 6446, 902);
  g->Binary(ynn_binary_pow, 902, 6448, 903);
  g->Binary(ynn_binary_multiply, 899, 903, 904);
}

// Scope: "Layer14 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(894, 905, 0.001091228099539876, 0);
  g->Append(6419, 905, 7068, 2, s2, slinky::expr(int64_t{1}));
  g->View(7068, 7098, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7098, 907, 0.001091228099539876, 0);
  g->Quantize(904, 908, 0.01785714365541935, 0);
  g->Append(6434, 908, 7083, 2, s2, slinky::expr(int64_t{1}));
  g->View(7083, 7113, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7113, 909, 0.01785714365541935, 0);
}

// Scope: "Layer14 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(6605, 4123, {1,0});
  g->Binary(ynn_binary_multiply, 4109, 4122, 4119);
  g->Dot(875, 4123, YNN_INVALID_VALUE_ID, 4118, 1);
  g->DequantizeTensor(4118, YNN_INVALID_VALUE_ID, 4119, 4120);
  g->QuantizeTensor(4120, 6412, 4121, 910);
  g->Dequantize(910, 911, 0.3385826647281647, 0);
  g->SplitDim(911, 912, 2, {8,512});
  g->FuseDims(912, 914, 1, 2);
  g->SplitDim(914, 913, 1, {8,1});
  g->Unary(ynn_unary_square, 913, 915);
  g->Reduce(ynn_reduce_sum, 915, 5688, {3}, true);
  g->ShapeProduct(915, 5687, {3});
  g->Binary(ynn_binary_divide, 5688, 5687, 916);
  g->Binary(ynn_binary_add, 916, 6446, 917);
  g->Binary(ynn_binary_pow, 917, 6448, 918);
  g->Binary(ynn_binary_multiply, 913, 918, 919);
  g->Convert(6604, 920);
  g->Binary(ynn_binary_multiply, 919, 920, 921);
  g->Slice(921, 922, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(921, 923, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 923, 924);
  g->Concat({924,922}, 925, 3);
  g->Binary(ynn_binary_multiply, 921, 3471, 926);
  g->Binary(ynn_binary_multiply, 925, 3576, 927);
  g->Binary(ynn_binary_add, 926, 927, 928);
}

// Scope: "Layer14 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(928, 907, 929, false, true);
  g->Mask(929, 6459, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 6459, 5692, {-1}, true);
  g->Binary(ynn_binary_subtract, 6459, 5692, 5689);
  g->Unary(ynn_unary_exp, 5689, 5690);
  g->Reduce(ynn_reduce_sum, 5690, 5693, {-1}, true);
  g->Binary(ynn_binary_divide, 5474, 5693, 5691);
  g->Binary(ynn_binary_multiply, 5690, 5691, 930);
  g->Matmul(930, 909, 931, false, false);
}

// Scope: "Layer14 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(931, 934, 1, 2);
  g->SplitDim(934, 933, 1, {1,8});
  g->FuseDims(933, 935, 2, 2);
  g->Quantize(935, 936, 0.017962608486413956, 0);
  g->Transpose(6603, 4129, {1,0});
  g->Binary(ynn_binary_multiply, 3813, 4128, 4125);
  g->Dot(936, 4129, YNN_INVALID_VALUE_ID, 4124, 1);
  g->DequantizeTensor(4124, YNN_INVALID_VALUE_ID, 4125, 4126);
  g->QuantizeTensor(4126, 6412, 4127, 937);
  g->Dequantize(937, 938, 0.019122116267681122, 0);
}

// Scope: "Layer14 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 866, 867);
  g->Reduce(ynn_reduce_sum, 867, 5682, {2}, true);
  g->ShapeProduct(867, 5681, {2});
  g->Binary(ynn_binary_divide, 5682, 5681, 868);
  g->Binary(ynn_binary_add, 868, 6446, 869);
  g->Binary(ynn_binary_pow, 869, 6448, 870);
  g->Binary(ynn_binary_multiply, 866, 870, 871);
  g->Convert(6590, 872);
  g->Binary(ynn_binary_multiply, 871, 872, 873);
  BuildLayer14AttentionKvProjection(ctx);
  BuildLayer14AttentionCacheUpdate(ctx);
  BuildLayer14AttentionQueryProjection(ctx);
  BuildLayer14AttentionSdpa(ctx);
  BuildLayer14AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 938, 939);
  g->Reduce(ynn_reduce_sum, 939, 5695, {2}, true);
  g->ShapeProduct(939, 5694, {2});
  g->Binary(ynn_binary_divide, 5695, 5694, 940);
  g->Binary(ynn_binary_add, 940, 6446, 941);
  g->Binary(ynn_binary_pow, 941, 6448, 942);
  g->Binary(ynn_binary_multiply, 938, 942, 943);
  g->Convert(6597, 945);
  g->Binary(ynn_binary_multiply, 943, 945, 946);
  g->Binary(ynn_binary_add, 866, 946, 947);
}

// Scope: "Layer14 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 947, 948);
  g->Reduce(ynn_reduce_sum, 948, 5697, {2}, true);
  g->ShapeProduct(948, 5696, {2});
  g->Binary(ynn_binary_divide, 5697, 5696, 949);
  g->Binary(ynn_binary_add, 949, 6446, 950);
  g->Binary(ynn_binary_pow, 950, 6448, 951);
  g->Binary(ynn_binary_multiply, 947, 951, 952);
  g->Convert(6600, 953);
  g->Binary(ynn_binary_multiply, 952, 953, 954);
  g->Quantize(954, 956, 0.01763528399169445, 0);
  g->Transpose(6594, 4136, {1,0});
  g->Binary(ynn_binary_multiply, 4133, 4135, 4131);
  g->Dot(956, 4136, YNN_INVALID_VALUE_ID, 4130, 1);
  g->DequantizeTensor(4130, YNN_INVALID_VALUE_ID, 4131, 4132);
  g->QuantizeTensor(4132, 6412, 4134, 957);
  g->Dequantize(957, 958, 0.01457924209535122, 0);
  g->Transpose(6593, 4141, {1,0});
  g->Binary(ynn_binary_multiply, 4133, 4140, 4138);
  g->Dot(956, 4141, YNN_INVALID_VALUE_ID, 4137, 1);
  g->DequantizeTensor(4137, YNN_INVALID_VALUE_ID, 4138, 4139);
  g->QuantizeTensor(4139, 6412, 4134, 959);
  g->Dequantize(959, 960, 0.01457924209535122, 0);
  g->Polynomial(960, 5700, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5700, 5701);
  g->Binary(ynn_binary_add, 5701, 5474, 5698);
  g->Binary(ynn_binary_multiply, 960, 5472, 5699);
  g->Binary(ynn_binary_multiply, 5699, 5698, 961);
  g->Binary(ynn_binary_multiply, 958, 961, 962);
  g->Quantize(962, 963, 0.010642234236001968, 0);
  g->Transpose(6592, 4148, {1,0});
  g->Binary(ynn_binary_multiply, 4145, 4147, 4143);
  g->Dot(963, 4148, YNN_INVALID_VALUE_ID, 4142, 1);
  g->DequantizeTensor(4142, YNN_INVALID_VALUE_ID, 4143, 4144);
  g->QuantizeTensor(4144, 6412, 4146, 964);
  g->Dequantize(964, 965, 0.013017668388783932, 0);
  g->Unary(ynn_unary_square, 965, 966);
  g->Reduce(ynn_reduce_sum, 966, 5703, {2}, true);
  g->ShapeProduct(966, 5702, {2});
  g->Binary(ynn_binary_divide, 5703, 5702, 967);
  g->Binary(ynn_binary_add, 967, 6446, 968);
  g->Binary(ynn_binary_pow, 968, 6448, 969);
  g->Binary(ynn_binary_multiply, 965, 969, 970);
  g->Convert(6598, 971);
  g->Binary(ynn_binary_multiply, 970, 971, 972);
  g->Binary(ynn_binary_add, 947, 972, 973);
}

// Scope: "Layer14 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1064, 974, {0,0,14,0}, {-1,-1,1,-1});
  g->Reshape(974, 976, {1,1,256});
  g->Binary(ynn_binary_add, 976, 7032, 977);
  g->Binary(ynn_binary_multiply, 977, 6444, 978);
  g->Quantize(973, 979, 1.2159134149551392, 0);
  g->Transpose(6595, 4155, {1,0});
  g->Binary(ynn_binary_multiply, 4152, 4154, 4150);
  g->Dot(979, 4155, YNN_INVALID_VALUE_ID, 4149, 1);
  g->DequantizeTensor(4149, YNN_INVALID_VALUE_ID, 4150, 4151);
  g->QuantizeTensor(4151, 6412, 4153, 980);
  g->Dequantize(980, 981, 0.04429135099053383, 0);
  g->Polynomial(981, 5706, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5706, 5707);
  g->Binary(ynn_binary_add, 5707, 5474, 5704);
  g->Binary(ynn_binary_multiply, 981, 5472, 5705);
  g->Binary(ynn_binary_multiply, 5705, 5704, 982);
  g->Binary(ynn_binary_multiply, 982, 978, 983);
  g->Quantize(983, 984, 0.10629922151565552, 0);
  g->Transpose(6596, 4162, {1,0});
  g->Binary(ynn_binary_multiply, 4159, 4161, 4157);
  g->Dot(984, 4162, YNN_INVALID_VALUE_ID, 4156, 1);
  g->DequantizeTensor(4156, YNN_INVALID_VALUE_ID, 4157, 4158);
  g->QuantizeTensor(4158, 6412, 4160, 985);
  g->Dequantize(985, 986, 0.045032795518636703, 0);
  g->Unary(ynn_unary_square, 986, 987);
  g->Reduce(ynn_reduce_sum, 987, 5709, {2}, true);
  g->ShapeProduct(987, 5708, {2});
  g->Binary(ynn_binary_divide, 5709, 5708, 988);
  g->Binary(ynn_binary_add, 988, 6446, 989);
  g->Binary(ynn_binary_pow, 989, 6448, 990);
  g->Binary(ynn_binary_multiply, 986, 990, 991);
  g->Convert(6599, 992);
  g->Binary(ynn_binary_multiply, 991, 992, 993);
  g->Binary(ynn_binary_add, 973, 993, 994);
  g->Convert(6591, 995);
  g->Binary(ynn_binary_multiply, 994, 995, 997);
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
  g->Quantize(1004, 1005, 0.18704485893249512, 0);
  g->Transpose(6620, 4175, {1,0});
  g->Binary(ynn_binary_multiply, 4172, 4174, 4170);
  g->Dot(1005, 4175, YNN_INVALID_VALUE_ID, 4169, 1);
  g->DequantizeTensor(4169, YNN_INVALID_VALUE_ID, 4170, 4171);
  g->QuantizeTensor(4171, 6412, 4173, 1006);
  g->Dequantize(1006, 1008, 0.2814960777759552, 0);
  g->SplitDim(1008, 1009, 2, {8,256});
  g->FuseDims(1009, 1011, 1, 2);
  g->SplitDim(1011, 1010, 1, {8,1});
  g->Unary(ynn_unary_square, 1010, 1012);
  g->Reduce(ynn_reduce_sum, 1012, 5713, {3}, true);
  g->ShapeProduct(1012, 5712, {3});
  g->Binary(ynn_binary_divide, 5713, 5712, 1013);
  g->Binary(ynn_binary_add, 1013, 6446, 1014);
  g->Binary(ynn_binary_pow, 1014, 6448, 1015);
  g->Binary(ynn_binary_multiply, 1010, 1015, 1016);
  g->Convert(6619, 1017);
  g->Binary(ynn_binary_multiply, 1016, 1017, 1018);
  g->Slice(1018, 1020, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1018, 1021, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1021, 1022);
  g->Concat({1022,1020}, 1023, 3);
  g->Binary(ynn_binary_multiply, 1018, 2173, 1024);
  g->Binary(ynn_binary_multiply, 1023, 3050, 1025);
  g->Binary(ynn_binary_add, 1024, 1025, 1026);
}

// Scope: "Layer15 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(1026, 772, 1027, false, true);
  g->Mask(1027, 6460, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6460, 5717, {-1}, true);
  g->Binary(ynn_binary_subtract, 6460, 5717, 5714);
  g->Unary(ynn_unary_exp, 5714, 5715);
  g->Reduce(ynn_reduce_sum, 5715, 5718, {-1}, true);
  g->Binary(ynn_binary_divide, 5474, 5718, 5716);
  g->Binary(ynn_binary_multiply, 5715, 5716, 1028);
  g->Matmul(1028, 774, 1031, false, false);
}

// Scope: "Layer15 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(1031, 1033, 1, 2);
  g->SplitDim(1033, 1032, 1, {1,8});
  g->FuseDims(1032, 1034, 2, 2);
  g->Quantize(1034, 1035, 0.02436024509370327, 0);
  g->Transpose(6618, 4182, {1,0});
  g->Binary(ynn_binary_multiply, 4179, 4181, 4177);
  g->Dot(1035, 4182, YNN_INVALID_VALUE_ID, 4176, 1);
  g->DequantizeTensor(4176, YNN_INVALID_VALUE_ID, 4177, 4178);
  g->QuantizeTensor(4178, 6412, 4180, 1036);
  g->Dequantize(1036, 1037, 0.060289591550827026, 0);
}

// Scope: "Layer15 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 997, 998);
  g->Reduce(ynn_reduce_sum, 998, 5711, {2}, true);
  g->ShapeProduct(998, 5710, {2});
  g->Binary(ynn_binary_divide, 5711, 5710, 999);
  g->Binary(ynn_binary_add, 999, 6446, 1000);
  g->Binary(ynn_binary_pow, 1000, 6448, 1001);
  g->Binary(ynn_binary_multiply, 997, 1001, 1002);
  g->Convert(6607, 1003);
  g->Binary(ynn_binary_multiply, 1002, 1003, 1004);
  BuildLayer15AttentionQueryProjection(ctx);
  BuildLayer15AttentionSdpa(ctx);
  BuildLayer15AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1037, 1038);
  g->Reduce(ynn_reduce_sum, 1038, 5720, {2}, true);
  g->ShapeProduct(1038, 5719, {2});
  g->Binary(ynn_binary_divide, 5720, 5719, 1039);
  g->Binary(ynn_binary_add, 1039, 6446, 1040);
  g->Binary(ynn_binary_pow, 1040, 6448, 1041);
  g->Binary(ynn_binary_multiply, 1037, 1041, 1043);
  g->Convert(6614, 1044);
  g->Binary(ynn_binary_multiply, 1043, 1044, 1045);
  g->Binary(ynn_binary_add, 997, 1045, 1046);
}

// Scope: "Layer15 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1046, 1047);
  g->Reduce(ynn_reduce_sum, 1047, 5722, {2}, true);
  g->ShapeProduct(1047, 5721, {2});
  g->Binary(ynn_binary_divide, 5722, 5721, 1048);
  g->Binary(ynn_binary_add, 1048, 6446, 1049);
  g->Binary(ynn_binary_pow, 1049, 6448, 1050);
  g->Binary(ynn_binary_multiply, 1046, 1050, 1051);
  g->Convert(6617, 1052);
  g->Binary(ynn_binary_multiply, 1051, 1052, 1054);
  g->Quantize(1054, 1055, 0.023188970983028412, 0);
  g->Transpose(6611, 4189, {1,0});
  g->Binary(ynn_binary_multiply, 4186, 4188, 4184);
  g->Dot(1055, 4189, YNN_INVALID_VALUE_ID, 4183, 1);
  g->DequantizeTensor(4183, YNN_INVALID_VALUE_ID, 4184, 4185);
  g->QuantizeTensor(4185, 6412, 4187, 1056);
  g->Dequantize(1056, 1057, 0.030511820688843727, 0);
  g->Transpose(6610, 4194, {1,0});
  g->Binary(ynn_binary_multiply, 4186, 4193, 4191);
  g->Dot(1055, 4194, YNN_INVALID_VALUE_ID, 4190, 1);
  g->DequantizeTensor(4190, YNN_INVALID_VALUE_ID, 4191, 4192);
  g->QuantizeTensor(4192, 6412, 4187, 1058);
  g->Dequantize(1058, 1059, 0.030511820688843727, 0);
  g->Polynomial(1059, 5727, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5727, 5728);
  g->Binary(ynn_binary_add, 5728, 5474, 5725);
  g->Binary(ynn_binary_multiply, 1059, 5472, 5726);
  g->Binary(ynn_binary_multiply, 5726, 5725, 1060);
  g->Binary(ynn_binary_multiply, 1057, 1060, 1061);
  g->Quantize(1061, 1062, 0.02005414292216301, 0);
  g->Transpose(6609, 4201, {1,0});
  g->Binary(ynn_binary_multiply, 4198, 4200, 4196);
  g->Dot(1062, 4201, YNN_INVALID_VALUE_ID, 4195, 1);
  g->DequantizeTensor(4195, YNN_INVALID_VALUE_ID, 4196, 4197);
  g->QuantizeTensor(4197, 6412, 4199, 1066);
  g->Dequantize(1066, 1067, 0.008105741813778877, 0);
  g->Unary(ynn_unary_square, 1067, 1068);
  g->Reduce(ynn_reduce_sum, 1068, 5730, {2}, true);
  g->ShapeProduct(1068, 5729, {2});
  g->Binary(ynn_binary_divide, 5730, 5729, 1069);
  g->Binary(ynn_binary_add, 1069, 6446, 1070);
  g->Binary(ynn_binary_pow, 1070, 6448, 1071);
  g->Binary(ynn_binary_multiply, 1067, 1071, 1072);
  g->Convert(6615, 1073);
  g->Binary(ynn_binary_multiply, 1072, 1073, 1074);
  g->Binary(ynn_binary_add, 1046, 1074, 1075);
}

// Scope: "Layer15 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1064, 1077, {0,0,15,0}, {-1,-1,1,-1});
  g->Reshape(1077, 1078, {1,1,256});
  g->Binary(ynn_binary_add, 1078, 7033, 1079);
  g->Binary(ynn_binary_multiply, 1079, 6444, 1080);
  g->Quantize(1075, 1081, 0.196418896317482, 0);
  g->Transpose(6612, 4208, {1,0});
  g->Binary(ynn_binary_multiply, 4205, 4207, 4203);
  g->Dot(1081, 4208, YNN_INVALID_VALUE_ID, 4202, 1);
  g->DequantizeTensor(4202, YNN_INVALID_VALUE_ID, 4203, 4204);
  g->QuantizeTensor(4204, 6412, 4206, 1082);
  g->Dequantize(1082, 1083, 0.05930119380354881, 0);
  g->Polynomial(1083, 5733, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5733, 5734);
  g->Binary(ynn_binary_add, 5734, 5474, 5731);
  g->Binary(ynn_binary_multiply, 1083, 5472, 5732);
  g->Binary(ynn_binary_multiply, 5732, 5731, 1084);
  g->Binary(ynn_binary_multiply, 1084, 1080, 1085);
  g->Quantize(1085, 1086, 0.6023622155189514, 0);
  g->Transpose(6613, 4215, {1,0});
  g->Binary(ynn_binary_multiply, 4212, 4214, 4210);
  g->Dot(1086, 4215, YNN_INVALID_VALUE_ID, 4209, 1);
  g->DequantizeTensor(4209, YNN_INVALID_VALUE_ID, 4210, 4211);
  g->QuantizeTensor(4211, 6412, 4213, 1088);
  g->Dequantize(1088, 1089, 0.33502069115638733, 0);
  g->Unary(ynn_unary_square, 1089, 1090);
  g->Reduce(ynn_reduce_sum, 1090, 5736, {2}, true);
  g->ShapeProduct(1090, 5735, {2});
  g->Binary(ynn_binary_divide, 5736, 5735, 1091);
  g->Binary(ynn_binary_add, 1091, 6446, 1092);
  g->Binary(ynn_binary_pow, 1092, 6448, 1093);
  g->Binary(ynn_binary_multiply, 1089, 1093, 1094);
  g->Convert(6616, 1095);
  g->Binary(ynn_binary_multiply, 1094, 1095, 1096);
  g->Binary(ynn_binary_add, 1075, 1096, 1097);
  g->Convert(6608, 1099);
  g->Binary(ynn_binary_multiply, 1097, 1099, 1100);
}

// Scope: "Layer15"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15(Context& ctx) {
  BuildLayer15Attention(ctx);
  BuildLayer15Mlp(ctx);
  BuildLayer15PerLayerEmbedding(ctx);
}

}  // namespace BuildGemma4DecodeSource
