// Generated YNNPACK builder; do not edit.
#include "gemma4_decode_builder.h"

namespace BuildGemma4DecodeSource {

// Scope: "Layer8 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(42, 43, 0.0820433720946312, 0);
  g->Transpose(7024, 3656, {1,0});
  g->Binary(ynn_binary_multiply, 3653, 3655, 3651);
  g->Dot(43, 3656, YNN_INVALID_VALUE_ID, 3650, 1);
  g->DequantizeTensor(3650, YNN_INVALID_VALUE_ID, 3651, 3652);
  g->QuantizeTensor(3652, 6434, 3654, 44);
  g->Dequantize(44, 45, 0.09251969307661057, 0);
  g->Reshape(45, 47, {1,1,1,256});
  g->Transpose(47, 48, {0,2,1,3});
  g->Unary(ynn_unary_square, 48, 49);
  g->Reduce(ynn_reduce_sum, 49, 5442, {3}, true);
  g->ShapeProduct(49, 5441, {3});
  g->Binary(ynn_binary_divide, 5442, 5441, 50);
  g->Binary(ynn_binary_add, 50, 6469, 51);
  g->Unary(ynn_unary_rsqrt, 51, 52);
  g->Binary(ynn_binary_multiply, 48, 52, 53);
  g->Binary(ynn_binary_multiply, 53, 7023, 54);
  g->Slice(54, 55, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(54, 56, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 56, 58);
  g->Concat({58,55}, 59, 3);
  g->Binary(ynn_binary_multiply, 54, 3009, 60);
  g->Binary(ynn_binary_multiply, 59, 3112, 61);
  g->Binary(ynn_binary_add, 60, 61, 62);
  g->Transpose(7028, 3661, {1,0});
  g->Binary(ynn_binary_multiply, 3653, 3660, 3658);
  g->Dot(43, 3661, YNN_INVALID_VALUE_ID, 3657, 1);
  g->DequantizeTensor(3657, YNN_INVALID_VALUE_ID, 3658, 3659);
  g->QuantizeTensor(3659, 6434, 3654, 63);
  g->Dequantize(63, 64, 0.09251969307661057, 0);
  g->Reshape(64, 65, {1,1,1,256});
  g->Transpose(65, 66, {0,2,1,3});
  g->Unary(ynn_unary_square, 66, 68);
  g->Reduce(ynn_reduce_sum, 68, 5444, {3}, true);
  g->ShapeProduct(68, 5443, {3});
  g->Binary(ynn_binary_divide, 5444, 5443, 69);
  g->Binary(ynn_binary_add, 69, 6469, 70);
  g->Unary(ynn_unary_rsqrt, 70, 71);
  g->Binary(ynn_binary_multiply, 66, 71, 72);
}

// Scope: "Layer8 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(62, 73, 0.006215503439307213, 0);
  g->Append(6448, 73, 7098, 2, s2, slinky::expr(int64_t{1}));
  g->View(7098, 7128, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(72, 74, 0.047244105488061905, 0);
  g->Append(6463, 74, 7113, 2, s2, slinky::expr(int64_t{1}));
  g->View(7113, 7143, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer8 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(7027, 3674, {1,0});
  g->Binary(ynn_binary_multiply, 3653, 3673, 3670);
  g->Dot(43, 3674, YNN_INVALID_VALUE_ID, 3669, 1);
  g->DequantizeTensor(3669, YNN_INVALID_VALUE_ID, 3670, 3671);
  g->QuantizeTensor(3671, 6434, 3672, 76);
  g->Dequantize(76, 77, 0.1250000149011612, 0);
  g->SplitDim(77, 78, 2, {8,256});
  g->Transpose(78, 79, {0,2,1,3});
  g->Unary(ynn_unary_square, 79, 80);
  g->Reduce(ynn_reduce_sum, 80, 5446, {3}, true);
  g->ShapeProduct(80, 5445, {3});
  g->Binary(ynn_binary_divide, 5446, 5445, 81);
  g->Binary(ynn_binary_add, 81, 6469, 82);
  g->Unary(ynn_unary_rsqrt, 82, 83);
  g->Binary(ynn_binary_multiply, 79, 83, 85);
  g->Binary(ynn_binary_multiply, 85, 7026, 86);
  g->Slice(86, 87, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(86, 88, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 88, 89);
  g->Concat({89,87}, 90, 3);
  g->Binary(ynn_binary_multiply, 86, 3009, 91);
  g->Binary(ynn_binary_multiply, 90, 3112, 92);
  g->Binary(ynn_binary_add, 91, 92, 93);
}

// Scope: "Layer8 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7128, 94, 0.006215503439307213, 0);
  g->Dequantize(7143, 96, 0.047244105488061905, 0);
  g->Matmul(93, 94, 97, false, true);
  g->Mask(97, 6508, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6508, 5452, {-1}, true);
  g->Binary(ynn_binary_subtract, 6508, 5452, 5449);
  g->Unary(ynn_unary_exp, 5449, 5450);
  g->Reduce(ynn_reduce_sum, 5450, 5453, {-1}, true);
  g->Binary(ynn_binary_divide, 5430, 5453, 5451);
  g->Binary(ynn_binary_multiply, 5450, 5451, 98);
  g->Matmul(98, 96, 99, false, false);
}

// Scope: "Layer8 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(99, 100, {0,2,1,3});
  g->FuseDims(100, 101, 2, 2);
  g->Quantize(101, 102, 0.025713592767715454, 0);
  g->Transpose(7025, 3681, {1,0});
  g->Binary(ynn_binary_multiply, 3678, 3680, 3676);
  g->Dot(102, 3681, YNN_INVALID_VALUE_ID, 3675, 1);
  g->DequantizeTensor(3675, YNN_INVALID_VALUE_ID, 3676, 3677);
  g->QuantizeTensor(3677, 6434, 3679, 103);
  g->Dequantize(103, 104, 0.022537967190146446, 0);
}

// Scope: "Layer8 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 36, 37);
  g->Reduce(ynn_reduce_sum, 37, 5440, {2}, true);
  g->ShapeProduct(37, 5439, {2});
  g->Binary(ynn_binary_divide, 5440, 5439, 38);
  g->Binary(ynn_binary_add, 38, 6469, 39);
  g->Unary(ynn_unary_rsqrt, 39, 40);
  g->Binary(ynn_binary_multiply, 36, 40, 41);
  g->Binary(ynn_binary_multiply, 41, 7012, 42);
  BuildLayer8AttentionKvProjection(ctx);
  BuildLayer8AttentionCacheUpdate(ctx);
  BuildLayer8AttentionQueryProjection(ctx);
  BuildLayer8AttentionSdpa(ctx);
  BuildLayer8AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 104, 107);
  g->Reduce(ynn_reduce_sum, 107, 5455, {2}, true);
  g->ShapeProduct(107, 5454, {2});
  g->Binary(ynn_binary_divide, 5455, 5454, 108);
  g->Binary(ynn_binary_add, 108, 6469, 109);
  g->Unary(ynn_unary_rsqrt, 109, 110);
  g->Binary(ynn_binary_multiply, 104, 110, 111);
  g->Binary(ynn_binary_multiply, 111, 7019, 112);
  g->Binary(ynn_binary_add, 112, 36, 113);
}

// Scope: "Layer8 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 113, 114);
  g->Reduce(ynn_reduce_sum, 114, 5457, {2}, true);
  g->ShapeProduct(114, 5456, {2});
  g->Binary(ynn_binary_divide, 5457, 5456, 115);
  g->Binary(ynn_binary_add, 115, 6469, 116);
  g->Unary(ynn_unary_rsqrt, 116, 118);
  g->Binary(ynn_binary_multiply, 113, 118, 119);
  g->Binary(ynn_binary_multiply, 119, 7022, 120);
  g->Quantize(120, 121, 0.015404289588332176, 0);
  g->Transpose(7016, 3688, {1,0});
  g->Binary(ynn_binary_multiply, 3685, 3687, 3683);
  g->Dot(121, 3688, YNN_INVALID_VALUE_ID, 3682, 1);
  g->DequantizeTensor(3682, YNN_INVALID_VALUE_ID, 3683, 3684);
  g->QuantizeTensor(3684, 6434, 3686, 122);
  g->Dequantize(122, 123, 0.018823828548192978, 0);
  g->Transpose(7015, 3693, {1,0});
  g->Binary(ynn_binary_multiply, 3685, 3692, 3690);
  g->Dot(121, 3693, YNN_INVALID_VALUE_ID, 3689, 1);
  g->DequantizeTensor(3689, YNN_INVALID_VALUE_ID, 3690, 3691);
  g->QuantizeTensor(3691, 6434, 3686, 124);
  g->Dequantize(124, 125, 0.018823828548192978, 0);
  g->Polynomial(125, 5460, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5460, 5461);
  g->Binary(ynn_binary_add, 5461, 5430, 5458);
  g->Binary(ynn_binary_multiply, 125, 5428, 5459);
  g->Binary(ynn_binary_multiply, 5459, 5458, 126);
  g->Binary(ynn_binary_multiply, 123, 126, 128);
  g->Quantize(128, 129, 0.012610738165676594, 0);
  g->Transpose(7014, 3700, {1,0});
  g->Binary(ynn_binary_multiply, 3697, 3699, 3695);
  g->Dot(129, 3700, YNN_INVALID_VALUE_ID, 3694, 1);
  g->DequantizeTensor(3694, YNN_INVALID_VALUE_ID, 3695, 3696);
  g->QuantizeTensor(3696, 6434, 3698, 130);
  g->Dequantize(130, 131, 0.009271269664168358, 0);
  g->Unary(ynn_unary_square, 131, 132);
  g->Reduce(ynn_reduce_sum, 132, 5463, {2}, true);
  g->ShapeProduct(132, 5462, {2});
  g->Binary(ynn_binary_divide, 5463, 5462, 133);
  g->Binary(ynn_binary_add, 133, 6469, 134);
  g->Unary(ynn_unary_rsqrt, 134, 135);
  g->Binary(ynn_binary_multiply, 131, 135, 136);
  g->Binary(ynn_binary_multiply, 136, 7020, 137);
  g->Binary(ynn_binary_add, 137, 113, 139);
}

// Scope: "Layer8 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(421, 140, {0,0,8,0}, {-1,-1,1,-1});
  g->Reshape(140, 141, {1,1,256});
  g->Unary(ynn_unary_square, 141, 142);
  g->Reduce(ynn_reduce_sum, 142, 5465, {2}, true);
  g->ShapeProduct(142, 5464, {2});
  g->Binary(ynn_binary_divide, 5465, 5464, 143);
  g->Binary(ynn_binary_add, 143, 6469, 144);
  g->Unary(ynn_unary_rsqrt, 144, 145);
  g->Binary(ynn_binary_multiply, 141, 145, 146);
  g->Binary(ynn_binary_multiply, 146, 7048, 147);
  g->Binary(ynn_binary_multiply, 7082, 6472, 148);
  g->Binary(ynn_binary_add, 147, 148, 150);
  g->Binary(ynn_binary_multiply, 150, 6466, 151);
  g->Quantize(139, 152, 0.19172413647174835, 0);
  g->Transpose(7017, 3707, {1,0});
  g->Binary(ynn_binary_multiply, 3704, 3706, 3702);
  g->Dot(152, 3707, YNN_INVALID_VALUE_ID, 3701, 1);
  g->DequantizeTensor(3701, YNN_INVALID_VALUE_ID, 3702, 3703);
  g->QuantizeTensor(3703, 6434, 3705, 153);
  g->Dequantize(153, 154, 0.11515748500823975, 0);
  g->Polynomial(154, 5468, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5468, 5469);
  g->Binary(ynn_binary_add, 5469, 5430, 5466);
  g->Binary(ynn_binary_multiply, 154, 5428, 5467);
  g->Binary(ynn_binary_multiply, 5467, 5466, 155);
  g->Binary(ynn_binary_multiply, 155, 151, 156);
  g->Quantize(156, 157, 0.787401556968689, 0);
  g->Transpose(7018, 3714, {1,0});
  g->Binary(ynn_binary_multiply, 3711, 3713, 3709);
  g->Dot(157, 3714, YNN_INVALID_VALUE_ID, 3708, 1);
  g->DequantizeTensor(3708, YNN_INVALID_VALUE_ID, 3709, 3710);
  g->QuantizeTensor(3710, 6434, 3712, 158);
  g->Dequantize(158, 159, 0.2950586676597595, 0);
  g->Unary(ynn_unary_square, 159, 161);
  g->Reduce(ynn_reduce_sum, 161, 5471, {2}, true);
  g->ShapeProduct(161, 5470, {2});
  g->Binary(ynn_binary_divide, 5471, 5470, 162);
  g->Binary(ynn_binary_add, 162, 6469, 163);
  g->Unary(ynn_unary_rsqrt, 163, 164);
  g->Binary(ynn_binary_multiply, 159, 164, 165);
  g->Binary(ynn_binary_multiply, 165, 7021, 166);
  g->Binary(ynn_binary_add, 139, 166, 167);
  g->Binary(ynn_binary_multiply, 167, 7013, 168);
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
  g->Quantize(175, 176, 0.016753647476434708, 0);
  g->Transpose(7041, 3721, {1,0});
  g->Binary(ynn_binary_multiply, 3718, 3720, 3716);
  g->Dot(176, 3721, YNN_INVALID_VALUE_ID, 3715, 1);
  g->DequantizeTensor(3715, YNN_INVALID_VALUE_ID, 3716, 3717);
  g->QuantizeTensor(3717, 6434, 3719, 177);
  g->Dequantize(177, 178, 0.020177174359560013, 0);
  g->Reshape(178, 179, {1,1,1,512});
  g->Transpose(179, 180, {0,2,1,3});
  g->Unary(ynn_unary_square, 180, 181);
  g->Reduce(ynn_reduce_sum, 181, 5475, {3}, true);
  g->ShapeProduct(181, 5474, {3});
  g->Binary(ynn_binary_divide, 5475, 5474, 183);
  g->Binary(ynn_binary_add, 183, 6469, 184);
  g->Unary(ynn_unary_rsqrt, 184, 185);
  g->Binary(ynn_binary_multiply, 180, 185, 186);
  g->Binary(ynn_binary_multiply, 186, 7040, 187);
  g->Slice(187, 188, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(187, 189, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 189, 190);
  g->Concat({190,188}, 191, 3);
  g->Binary(ynn_binary_multiply, 187, 3526, 192);
  g->Binary(ynn_binary_multiply, 191, 2, 194);
  g->Binary(ynn_binary_add, 192, 194, 195);
  g->Transpose(7045, 3726, {1,0});
  g->Binary(ynn_binary_multiply, 3718, 3725, 3723);
  g->Dot(176, 3726, YNN_INVALID_VALUE_ID, 3722, 1);
  g->DequantizeTensor(3722, YNN_INVALID_VALUE_ID, 3723, 3724);
  g->QuantizeTensor(3724, 6434, 3719, 196);
  g->Dequantize(196, 197, 0.020177174359560013, 0);
  g->Reshape(197, 198, {1,1,1,512});
  g->Transpose(198, 199, {0,2,1,3});
  g->Unary(ynn_unary_square, 199, 200);
  g->Reduce(ynn_reduce_sum, 200, 5479, {3}, true);
  g->ShapeProduct(200, 5478, {3});
  g->Binary(ynn_binary_divide, 5479, 5478, 201);
  g->Binary(ynn_binary_add, 201, 6469, 202);
  g->Unary(ynn_unary_rsqrt, 202, 204);
  g->Binary(ynn_binary_multiply, 199, 204, 205);
}

// Scope: "Layer9 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(195, 206, 0.0010733711533248425, 0);
  g->Append(6449, 206, 7099, 2, s2, slinky::expr(int64_t{1}));
  g->View(7099, 7129, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(205, 207, 0.01785714365541935, 0);
  g->Append(6464, 207, 7114, 2, s2, slinky::expr(int64_t{1}));
  g->View(7114, 7144, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer9 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(7044, 3732, {1,0});
  g->Binary(ynn_binary_multiply, 3718, 3731, 3728);
  g->Dot(176, 3732, YNN_INVALID_VALUE_ID, 3727, 1);
  g->DequantizeTensor(3727, YNN_INVALID_VALUE_ID, 3728, 3729);
  g->QuantizeTensor(3729, 6434, 3730, 208);
  g->Dequantize(208, 211, 0.029650600627064705, 0);
  g->SplitDim(211, 212, 2, {8,512});
  g->Transpose(212, 213, {0,2,1,3});
  g->Unary(ynn_unary_square, 213, 214);
  g->Reduce(ynn_reduce_sum, 214, 5481, {3}, true);
  g->ShapeProduct(214, 5480, {3});
  g->Binary(ynn_binary_divide, 5481, 5480, 215);
  g->Binary(ynn_binary_add, 215, 6469, 216);
  g->Unary(ynn_unary_rsqrt, 216, 217);
  g->Binary(ynn_binary_multiply, 213, 217, 218);
  g->Binary(ynn_binary_multiply, 218, 7043, 219);
  g->Slice(219, 220, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(219, 222, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 222, 223);
  g->Concat({223,220}, 224, 3);
  g->Binary(ynn_binary_multiply, 219, 3526, 225);
  g->Binary(ynn_binary_multiply, 224, 2, 226);
  g->Binary(ynn_binary_add, 225, 226, 227);
}

// Scope: "Layer9 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7129, 228, 0.0010733711533248425, 0);
  g->Dequantize(7144, 229, 0.01785714365541935, 0);
  g->Matmul(227, 228, 230, false, true);
  g->Mask(230, 6509, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 6509, 5485, {-1}, true);
  g->Binary(ynn_binary_subtract, 6509, 5485, 5482);
  g->Unary(ynn_unary_exp, 5482, 5483);
  g->Reduce(ynn_reduce_sum, 5483, 5486, {-1}, true);
  g->Binary(ynn_binary_divide, 5430, 5486, 5484);
  g->Binary(ynn_binary_multiply, 5483, 5484, 232);
  g->Matmul(232, 229, 233, false, false);
}

// Scope: "Layer9 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(233, 234, {0,2,1,3});
  g->FuseDims(234, 235, 2, 2);
  g->Quantize(235, 236, 0.017962608486413956, 0);
  g->Transpose(7042, 3746, {1,0});
  g->Binary(ynn_binary_multiply, 3743, 3745, 3741);
  g->Dot(236, 3746, YNN_INVALID_VALUE_ID, 3740, 1);
  g->DequantizeTensor(3740, YNN_INVALID_VALUE_ID, 3741, 3742);
  g->QuantizeTensor(3742, 6434, 3744, 237);
  g->Dequantize(237, 238, 0.02776472456753254, 0);
}

// Scope: "Layer9 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 168, 169);
  g->Reduce(ynn_reduce_sum, 169, 5473, {2}, true);
  g->ShapeProduct(169, 5472, {2});
  g->Binary(ynn_binary_divide, 5473, 5472, 170);
  g->Binary(ynn_binary_add, 170, 6469, 172);
  g->Unary(ynn_unary_rsqrt, 172, 173);
  g->Binary(ynn_binary_multiply, 168, 173, 174);
  g->Binary(ynn_binary_multiply, 174, 7029, 175);
  BuildLayer9AttentionKvProjection(ctx);
  BuildLayer9AttentionCacheUpdate(ctx);
  BuildLayer9AttentionQueryProjection(ctx);
  BuildLayer9AttentionSdpa(ctx);
  BuildLayer9AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 238, 239);
  g->Reduce(ynn_reduce_sum, 239, 5488, {2}, true);
  g->ShapeProduct(239, 5487, {2});
  g->Binary(ynn_binary_divide, 5488, 5487, 240);
  g->Binary(ynn_binary_add, 240, 6469, 241);
  g->Unary(ynn_unary_rsqrt, 241, 243);
  g->Binary(ynn_binary_multiply, 238, 243, 244);
  g->Binary(ynn_binary_multiply, 244, 7036, 245);
  g->Binary(ynn_binary_add, 245, 168, 246);
}

// Scope: "Layer9 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 246, 247);
  g->Reduce(ynn_reduce_sum, 247, 5490, {2}, true);
  g->ShapeProduct(247, 5489, {2});
  g->Binary(ynn_binary_divide, 5490, 5489, 248);
  g->Binary(ynn_binary_add, 248, 6469, 249);
  g->Unary(ynn_unary_rsqrt, 249, 250);
  g->Binary(ynn_binary_multiply, 246, 250, 251);
  g->Binary(ynn_binary_multiply, 251, 7039, 252);
  g->Quantize(252, 254, 0.028379227966070175, 0);
  g->Transpose(7033, 3753, {1,0});
  g->Binary(ynn_binary_multiply, 3750, 3752, 3748);
  g->Dot(254, 3753, YNN_INVALID_VALUE_ID, 3747, 1);
  g->DequantizeTensor(3747, YNN_INVALID_VALUE_ID, 3748, 3749);
  g->QuantizeTensor(3749, 6434, 3751, 255);
  g->Dequantize(255, 256, 0.01556349452584982, 0);
  g->Transpose(7032, 3758, {1,0});
  g->Binary(ynn_binary_multiply, 3750, 3757, 3755);
  g->Dot(254, 3758, YNN_INVALID_VALUE_ID, 3754, 1);
  g->DequantizeTensor(3754, YNN_INVALID_VALUE_ID, 3755, 3756);
  g->QuantizeTensor(3756, 6434, 3751, 257);
  g->Dequantize(257, 258, 0.01556349452584982, 0);
  g->Polynomial(258, 5493, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5493, 5494);
  g->Binary(ynn_binary_add, 5494, 5430, 5491);
  g->Binary(ynn_binary_multiply, 258, 5428, 5492);
  g->Binary(ynn_binary_multiply, 5492, 5491, 259);
  g->Binary(ynn_binary_multiply, 256, 259, 260);
  g->Quantize(260, 261, 0.011441939510405064, 0);
  g->Transpose(7031, 3765, {1,0});
  g->Binary(ynn_binary_multiply, 3762, 3764, 3760);
  g->Dot(261, 3765, YNN_INVALID_VALUE_ID, 3759, 1);
  g->DequantizeTensor(3759, YNN_INVALID_VALUE_ID, 3760, 3761);
  g->QuantizeTensor(3761, 6434, 3763, 262);
  g->Dequantize(262, 264, 0.005826006643474102, 0);
  g->Unary(ynn_unary_square, 264, 265);
  g->Reduce(ynn_reduce_sum, 265, 5496, {2}, true);
  g->ShapeProduct(265, 5495, {2});
  g->Binary(ynn_binary_divide, 5496, 5495, 266);
  g->Binary(ynn_binary_add, 266, 6469, 267);
  g->Unary(ynn_unary_rsqrt, 267, 268);
  g->Binary(ynn_binary_multiply, 264, 268, 269);
  g->Binary(ynn_binary_multiply, 269, 7037, 270);
  g->Binary(ynn_binary_add, 270, 246, 271);
}

// Scope: "Layer9 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(421, 272, {0,0,9,0}, {-1,-1,1,-1});
  g->Reshape(272, 273, {1,1,256});
  g->Unary(ynn_unary_square, 273, 275);
  g->Reduce(ynn_reduce_sum, 275, 5498, {2}, true);
  g->ShapeProduct(275, 5497, {2});
  g->Binary(ynn_binary_divide, 5498, 5497, 276);
  g->Binary(ynn_binary_add, 276, 6469, 277);
  g->Unary(ynn_unary_rsqrt, 277, 278);
  g->Binary(ynn_binary_multiply, 273, 278, 279);
  g->Binary(ynn_binary_multiply, 279, 7048, 280);
  g->Binary(ynn_binary_multiply, 7083, 6472, 281);
  g->Binary(ynn_binary_add, 280, 281, 282);
  g->Binary(ynn_binary_multiply, 282, 6466, 283);
  g->Quantize(271, 284, 0.22249335050582886, 0);
  g->Transpose(7034, 3779, {1,0});
  g->Binary(ynn_binary_multiply, 3776, 3778, 3774);
  g->Dot(284, 3779, YNN_INVALID_VALUE_ID, 3773, 1);
  g->DequantizeTensor(3773, YNN_INVALID_VALUE_ID, 3774, 3775);
  g->QuantizeTensor(3775, 6434, 3777, 286);
  g->Dequantize(286, 287, 0.04404528811573982, 0);
  g->Polynomial(287, 5501, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5501, 5502);
  g->Binary(ynn_binary_add, 5502, 5430, 5499);
  g->Binary(ynn_binary_multiply, 287, 5428, 5500);
  g->Binary(ynn_binary_multiply, 5500, 5499, 288);
  g->Binary(ynn_binary_multiply, 288, 283, 289);
  g->Quantize(289, 290, 0.12598426640033722, 0);
  g->Transpose(7035, 3786, {1,0});
  g->Binary(ynn_binary_multiply, 3783, 3785, 3781);
  g->Dot(290, 3786, YNN_INVALID_VALUE_ID, 3780, 1);
  g->DequantizeTensor(3780, YNN_INVALID_VALUE_ID, 3781, 3782);
  g->QuantizeTensor(3782, 6434, 3784, 291);
  g->Dequantize(291, 292, 0.10531344264745712, 0);
  g->Unary(ynn_unary_square, 292, 293);
  g->Reduce(ynn_reduce_sum, 293, 5504, {2}, true);
  g->ShapeProduct(293, 5503, {2});
  g->Binary(ynn_binary_divide, 5504, 5503, 294);
  g->Binary(ynn_binary_add, 294, 6469, 295);
  g->Unary(ynn_unary_rsqrt, 295, 297);
  g->Binary(ynn_binary_multiply, 292, 297, 298);
  g->Binary(ynn_binary_multiply, 298, 7038, 299);
  g->Binary(ynn_binary_add, 271, 299, 300);
  g->Binary(ynn_binary_multiply, 300, 7030, 301);
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
  g->Quantize(308, 309, 0.15428009629249573, 0);
  g->Transpose(6557, 3793, {1,0});
  g->Binary(ynn_binary_multiply, 3790, 3792, 3788);
  g->Dot(309, 3793, YNN_INVALID_VALUE_ID, 3787, 1);
  g->DequantizeTensor(3787, YNN_INVALID_VALUE_ID, 3788, 3789);
  g->QuantizeTensor(3789, 6434, 3791, 310);
  g->Dequantize(310, 311, 0.19881890714168549, 0);
  g->Reshape(311, 312, {1,1,1,256});
  g->Transpose(312, 313, {0,2,1,3});
  g->Unary(ynn_unary_square, 313, 314);
  g->Reduce(ynn_reduce_sum, 314, 5512, {3}, true);
  g->ShapeProduct(314, 5511, {3});
  g->Binary(ynn_binary_divide, 5512, 5511, 315);
  g->Binary(ynn_binary_add, 315, 6469, 316);
  g->Unary(ynn_unary_rsqrt, 316, 317);
  g->Binary(ynn_binary_multiply, 313, 317, 320);
  g->Binary(ynn_binary_multiply, 320, 6556, 321);
  g->Slice(321, 322, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(321, 323, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 323, 324);
  g->Concat({324,322}, 325, 3);
  g->Binary(ynn_binary_multiply, 321, 3009, 326);
  g->Binary(ynn_binary_multiply, 325, 3112, 327);
  g->Binary(ynn_binary_add, 326, 327, 328);
  g->Transpose(6561, 3798, {1,0});
  g->Binary(ynn_binary_multiply, 3790, 3797, 3795);
  g->Dot(309, 3798, YNN_INVALID_VALUE_ID, 3794, 1);
  g->DequantizeTensor(3794, YNN_INVALID_VALUE_ID, 3795, 3796);
  g->QuantizeTensor(3796, 6434, 3791, 330);
  g->Dequantize(330, 331, 0.19881890714168549, 0);
  g->Reshape(331, 332, {1,1,1,256});
  g->Transpose(332, 333, {0,2,1,3});
  g->Unary(ynn_unary_square, 333, 334);
  g->Reduce(ynn_reduce_sum, 334, 5514, {3}, true);
  g->ShapeProduct(334, 5513, {3});
  g->Binary(ynn_binary_divide, 5514, 5513, 335);
  g->Binary(ynn_binary_add, 335, 6469, 336);
  g->Unary(ynn_unary_rsqrt, 336, 337);
  g->Binary(ynn_binary_multiply, 333, 337, 338);
}

// Scope: "Layer10 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(328, 339, 0.005712664220482111, 0);
  g->Append(6437, 339, 7087, 2, s2, slinky::expr(int64_t{1}));
  g->View(7087, 7117, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(338, 341, 0.047244105488061905, 0);
  g->Append(6452, 341, 7102, 2, s2, slinky::expr(int64_t{1}));
  g->View(7102, 7132, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer10 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(6560, 3811, {1,0});
  g->Binary(ynn_binary_multiply, 3790, 3810, 3807);
  g->Dot(309, 3811, YNN_INVALID_VALUE_ID, 3806, 1);
  g->DequantizeTensor(3806, YNN_INVALID_VALUE_ID, 3807, 3808);
  g->QuantizeTensor(3808, 6434, 3809, 342);
  g->Dequantize(342, 343, 0.3484252095222473, 0);
  g->SplitDim(343, 344, 2, {8,256});
  g->Transpose(344, 345, {0,2,1,3});
  g->Unary(ynn_unary_square, 345, 347);
  g->Reduce(ynn_reduce_sum, 347, 5516, {3}, true);
  g->ShapeProduct(347, 5515, {3});
  g->Binary(ynn_binary_divide, 5516, 5515, 348);
  g->Binary(ynn_binary_add, 348, 6469, 349);
  g->Unary(ynn_unary_rsqrt, 349, 350);
  g->Binary(ynn_binary_multiply, 345, 350, 351);
  g->Binary(ynn_binary_multiply, 351, 6559, 352);
  g->Slice(352, 353, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(352, 354, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 354, 355);
  g->Concat({355,353}, 356, 3);
  g->Binary(ynn_binary_multiply, 352, 3009, 358);
  g->Binary(ynn_binary_multiply, 356, 3112, 359);
  g->Binary(ynn_binary_add, 358, 359, 360);
}

// Scope: "Layer10 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7117, 361, 0.005712664220482111, 0);
  g->Dequantize(7132, 362, 0.047244105488061905, 0);
  g->Matmul(360, 361, 363, false, true);
  g->Mask(363, 6477, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6477, 5520, {-1}, true);
  g->Binary(ynn_binary_subtract, 6477, 5520, 5517);
  g->Unary(ynn_unary_exp, 5517, 5518);
  g->Reduce(ynn_reduce_sum, 5518, 5521, {-1}, true);
  g->Binary(ynn_binary_divide, 5430, 5521, 5519);
  g->Binary(ynn_binary_multiply, 5518, 5519, 364);
  g->Matmul(364, 362, 365, false, false);
}

// Scope: "Layer10 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(365, 366, {0,2,1,3});
  g->FuseDims(366, 368, 2, 2);
  g->Quantize(368, 369, 0.028051190078258514, 0);
  g->Transpose(6558, 3818, {1,0});
  g->Binary(ynn_binary_multiply, 3815, 3817, 3813);
  g->Dot(369, 3818, YNN_INVALID_VALUE_ID, 3812, 1);
  g->DequantizeTensor(3812, YNN_INVALID_VALUE_ID, 3813, 3814);
  g->QuantizeTensor(3814, 6434, 3816, 370);
  g->Dequantize(370, 371, 0.029417896643280983, 0);
}

// Scope: "Layer10 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 301, 302);
  g->Reduce(ynn_reduce_sum, 302, 5506, {2}, true);
  g->ShapeProduct(302, 5505, {2});
  g->Binary(ynn_binary_divide, 5506, 5505, 303);
  g->Binary(ynn_binary_add, 303, 6469, 304);
  g->Unary(ynn_unary_rsqrt, 304, 305);
  g->Binary(ynn_binary_multiply, 301, 305, 306);
  g->Binary(ynn_binary_multiply, 306, 6545, 308);
  BuildLayer10AttentionKvProjection(ctx);
  BuildLayer10AttentionCacheUpdate(ctx);
  BuildLayer10AttentionQueryProjection(ctx);
  BuildLayer10AttentionSdpa(ctx);
  BuildLayer10AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 371, 372);
  g->Reduce(ynn_reduce_sum, 372, 5525, {2}, true);
  g->ShapeProduct(372, 5524, {2});
  g->Binary(ynn_binary_divide, 5525, 5524, 373);
  g->Binary(ynn_binary_add, 373, 6469, 374);
  g->Unary(ynn_unary_rsqrt, 374, 375);
  g->Binary(ynn_binary_multiply, 371, 375, 376);
  g->Binary(ynn_binary_multiply, 376, 6552, 377);
  g->Binary(ynn_binary_add, 377, 301, 379);
}

// Scope: "Layer10 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 379, 380);
  g->Reduce(ynn_reduce_sum, 380, 5527, {2}, true);
  g->ShapeProduct(380, 5526, {2});
  g->Binary(ynn_binary_divide, 5527, 5526, 381);
  g->Binary(ynn_binary_add, 381, 6469, 382);
  g->Unary(ynn_unary_rsqrt, 382, 383);
  g->Binary(ynn_binary_multiply, 379, 383, 384);
  g->Binary(ynn_binary_multiply, 384, 6555, 385);
  g->Quantize(385, 386, 0.018714377656579018, 0);
  g->Transpose(6549, 3825, {1,0});
  g->Binary(ynn_binary_multiply, 3822, 3824, 3820);
  g->Dot(386, 3825, YNN_INVALID_VALUE_ID, 3819, 1);
  g->DequantizeTensor(3819, YNN_INVALID_VALUE_ID, 3820, 3821);
  g->QuantizeTensor(3821, 6434, 3823, 387);
  g->Dequantize(387, 388, 0.01808563992381096, 0);
  g->Transpose(6548, 3830, {1,0});
  g->Binary(ynn_binary_multiply, 3822, 3829, 3827);
  g->Dot(386, 3830, YNN_INVALID_VALUE_ID, 3826, 1);
  g->DequantizeTensor(3826, YNN_INVALID_VALUE_ID, 3827, 3828);
  g->QuantizeTensor(3828, 6434, 3823, 390);
  g->Dequantize(390, 391, 0.01808563992381096, 0);
  g->Polynomial(391, 5530, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5530, 5531);
  g->Binary(ynn_binary_add, 5531, 5430, 5528);
  g->Binary(ynn_binary_multiply, 391, 5428, 5529);
  g->Binary(ynn_binary_multiply, 5529, 5528, 392);
  g->Binary(ynn_binary_multiply, 388, 392, 393);
  g->Quantize(393, 394, 0.01304134912788868, 0);
  g->Transpose(6547, 3837, {1,0});
  g->Binary(ynn_binary_multiply, 3834, 3836, 3832);
  g->Dot(394, 3837, YNN_INVALID_VALUE_ID, 3831, 1);
  g->DequantizeTensor(3831, YNN_INVALID_VALUE_ID, 3832, 3833);
  g->QuantizeTensor(3833, 6434, 3835, 395);
  g->Dequantize(395, 396, 0.011867290362715721, 0);
  g->Unary(ynn_unary_square, 396, 397);
  g->Reduce(ynn_reduce_sum, 397, 5533, {2}, true);
  g->ShapeProduct(397, 5532, {2});
  g->Binary(ynn_binary_divide, 5533, 5532, 398);
  g->Binary(ynn_binary_add, 398, 6469, 400);
  g->Unary(ynn_unary_rsqrt, 400, 401);
  g->Binary(ynn_binary_multiply, 396, 401, 402);
  g->Binary(ynn_binary_multiply, 402, 6553, 403);
  g->Binary(ynn_binary_add, 403, 379, 404);
}

// Scope: "Layer10 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(421, 405, {0,0,10,0}, {-1,-1,1,-1});
  g->Reshape(405, 406, {1,1,256});
  g->Unary(ynn_unary_square, 406, 407);
  g->Reduce(ynn_reduce_sum, 407, 5535, {2}, true);
  g->ShapeProduct(407, 5534, {2});
  g->Binary(ynn_binary_divide, 5535, 5534, 408);
  g->Binary(ynn_binary_add, 408, 6469, 409);
  g->Unary(ynn_unary_rsqrt, 409, 411);
  g->Binary(ynn_binary_multiply, 406, 411, 412);
  g->Binary(ynn_binary_multiply, 412, 7048, 413);
  g->Binary(ynn_binary_multiply, 7051, 6472, 414);
  g->Binary(ynn_binary_add, 413, 414, 415);
  g->Binary(ynn_binary_multiply, 415, 6466, 416);
  g->Quantize(404, 417, 0.14669467508792877, 0);
  g->Transpose(6550, 3844, {1,0});
  g->Binary(ynn_binary_multiply, 3841, 3843, 3839);
  g->Dot(417, 3844, YNN_INVALID_VALUE_ID, 3838, 1);
  g->DequantizeTensor(3838, YNN_INVALID_VALUE_ID, 3839, 3840);
  g->QuantizeTensor(3840, 6434, 3842, 418);
  g->Dequantize(418, 419, 0.038631901144981384, 0);
  g->Polynomial(419, 5538, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5538, 5539);
  g->Binary(ynn_binary_add, 5539, 5430, 5536);
  g->Binary(ynn_binary_multiply, 419, 5428, 5537);
  g->Binary(ynn_binary_multiply, 5537, 5536, 420);
  g->Binary(ynn_binary_multiply, 420, 416, 423);
  g->Quantize(423, 424, 0.05610237270593643, 0);
  g->Transpose(6551, 3851, {1,0});
  g->Binary(ynn_binary_multiply, 3848, 3850, 3846);
  g->Dot(424, 3851, YNN_INVALID_VALUE_ID, 3845, 1);
  g->DequantizeTensor(3845, YNN_INVALID_VALUE_ID, 3846, 3847);
  g->QuantizeTensor(3847, 6434, 3849, 425);
  g->Dequantize(425, 426, 0.041538726538419724, 0);
  g->Unary(ynn_unary_square, 426, 427);
  g->Reduce(ynn_reduce_sum, 427, 5541, {2}, true);
  g->ShapeProduct(427, 5540, {2});
  g->Binary(ynn_binary_divide, 5541, 5540, 428);
  g->Binary(ynn_binary_add, 428, 6469, 429);
  g->Unary(ynn_unary_rsqrt, 429, 430);
  g->Binary(ynn_binary_multiply, 426, 430, 431);
  g->Binary(ynn_binary_multiply, 431, 6554, 432);
  g->Binary(ynn_binary_add, 404, 432, 434);
  g->Binary(ynn_binary_multiply, 434, 6546, 435);
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
  g->Quantize(441, 442, 0.11506716161966324, 0);
  g->Transpose(6574, 3858, {1,0});
  g->Binary(ynn_binary_multiply, 3855, 3857, 3853);
  g->Dot(442, 3858, YNN_INVALID_VALUE_ID, 3852, 1);
  g->DequantizeTensor(3852, YNN_INVALID_VALUE_ID, 3853, 3854);
  g->QuantizeTensor(3854, 6434, 3856, 443);
  g->Dequantize(443, 445, 0.12696851789951324, 0);
  g->Reshape(445, 446, {1,1,1,256});
  g->Transpose(446, 447, {0,2,1,3});
  g->Unary(ynn_unary_square, 447, 448);
  g->Reduce(ynn_reduce_sum, 448, 5545, {3}, true);
  g->ShapeProduct(448, 5544, {3});
  g->Binary(ynn_binary_divide, 5545, 5544, 449);
  g->Binary(ynn_binary_add, 449, 6469, 450);
  g->Unary(ynn_unary_rsqrt, 450, 451);
  g->Binary(ynn_binary_multiply, 447, 451, 452);
  g->Binary(ynn_binary_multiply, 452, 6573, 453);
  g->Slice(453, 454, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(453, 456, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 456, 457);
  g->Concat({457,454}, 458, 3);
  g->Binary(ynn_binary_multiply, 453, 3009, 459);
  g->Binary(ynn_binary_multiply, 458, 3112, 460);
  g->Binary(ynn_binary_add, 459, 460, 461);
  g->Transpose(6578, 3863, {1,0});
  g->Binary(ynn_binary_multiply, 3855, 3862, 3860);
  g->Dot(442, 3863, YNN_INVALID_VALUE_ID, 3859, 1);
  g->DequantizeTensor(3859, YNN_INVALID_VALUE_ID, 3860, 3861);
  g->QuantizeTensor(3861, 6434, 3856, 462);
  g->Dequantize(462, 463, 0.12696851789951324, 0);
  g->Reshape(463, 464, {1,1,1,256});
  g->Transpose(464, 466, {0,2,1,3});
  g->Unary(ynn_unary_square, 466, 467);
  g->Reduce(ynn_reduce_sum, 467, 5549, {3}, true);
  g->ShapeProduct(467, 5548, {3});
  g->Binary(ynn_binary_divide, 5549, 5548, 468);
  g->Binary(ynn_binary_add, 468, 6469, 469);
  g->Unary(ynn_unary_rsqrt, 469, 470);
  g->Binary(ynn_binary_multiply, 466, 470, 471);
}

// Scope: "Layer11 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(461, 472, 0.005907459184527397, 0);
  g->Append(6438, 472, 7088, 2, s2, slinky::expr(int64_t{1}));
  g->View(7088, 7118, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(471, 473, 0.047244105488061905, 0);
  g->Append(6453, 473, 7103, 2, s2, slinky::expr(int64_t{1}));
  g->View(7103, 7133, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer11 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(6577, 3869, {1,0});
  g->Binary(ynn_binary_multiply, 3855, 3868, 3865);
  g->Dot(442, 3869, YNN_INVALID_VALUE_ID, 3864, 1);
  g->DequantizeTensor(3864, YNN_INVALID_VALUE_ID, 3865, 3866);
  g->QuantizeTensor(3866, 6434, 3867, 475);
  g->Dequantize(475, 476, 0.2736220359802246, 0);
  g->SplitDim(476, 477, 2, {8,256});
  g->Transpose(477, 478, {0,2,1,3});
  g->Unary(ynn_unary_square, 478, 479);
  g->Reduce(ynn_reduce_sum, 479, 5551, {3}, true);
  g->ShapeProduct(479, 5550, {3});
  g->Binary(ynn_binary_divide, 5551, 5550, 480);
  g->Binary(ynn_binary_add, 480, 6469, 481);
  g->Unary(ynn_unary_rsqrt, 481, 483);
  g->Binary(ynn_binary_multiply, 478, 483, 484);
  g->Binary(ynn_binary_multiply, 484, 6576, 485);
  g->Slice(485, 486, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(485, 487, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 487, 488);
  g->Concat({488,486}, 489, 3);
  g->Binary(ynn_binary_multiply, 485, 3009, 490);
  g->Binary(ynn_binary_multiply, 489, 3112, 491);
  g->Binary(ynn_binary_add, 490, 491, 492);
}

// Scope: "Layer11 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7118, 494, 0.005907459184527397, 0);
  g->Dequantize(7133, 495, 0.047244105488061905, 0);
  g->Matmul(492, 494, 496, false, true);
  g->Mask(496, 6478, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6478, 5555, {-1}, true);
  g->Binary(ynn_binary_subtract, 6478, 5555, 5552);
  g->Unary(ynn_unary_exp, 5552, 5553);
  g->Reduce(ynn_reduce_sum, 5553, 5556, {-1}, true);
  g->Binary(ynn_binary_divide, 5430, 5556, 5554);
  g->Binary(ynn_binary_multiply, 5553, 5554, 497);
  g->Matmul(497, 495, 498, false, false);
}

// Scope: "Layer11 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(498, 499, {0,2,1,3});
  g->FuseDims(499, 500, 2, 2);
  g->Quantize(500, 501, 0.026082687079906464, 0);
  g->Transpose(6575, 3876, {1,0});
  g->Binary(ynn_binary_multiply, 3873, 3875, 3871);
  g->Dot(501, 3876, YNN_INVALID_VALUE_ID, 3870, 1);
  g->DequantizeTensor(3870, YNN_INVALID_VALUE_ID, 3871, 3872);
  g->QuantizeTensor(3872, 6434, 3874, 502);
  g->Dequantize(502, 504, 0.028822369873523712, 0);
}

// Scope: "Layer11 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 435, 436);
  g->Reduce(ynn_reduce_sum, 436, 5543, {2}, true);
  g->ShapeProduct(436, 5542, {2});
  g->Binary(ynn_binary_divide, 5543, 5542, 437);
  g->Binary(ynn_binary_add, 437, 6469, 438);
  g->Unary(ynn_unary_rsqrt, 438, 439);
  g->Binary(ynn_binary_multiply, 435, 439, 440);
  g->Binary(ynn_binary_multiply, 440, 6562, 441);
  BuildLayer11AttentionKvProjection(ctx);
  BuildLayer11AttentionCacheUpdate(ctx);
  BuildLayer11AttentionQueryProjection(ctx);
  BuildLayer11AttentionSdpa(ctx);
  BuildLayer11AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 504, 505);
  g->Reduce(ynn_reduce_sum, 505, 5558, {2}, true);
  g->ShapeProduct(505, 5557, {2});
  g->Binary(ynn_binary_divide, 5558, 5557, 506);
  g->Binary(ynn_binary_add, 506, 6469, 507);
  g->Unary(ynn_unary_rsqrt, 507, 508);
  g->Binary(ynn_binary_multiply, 504, 508, 509);
  g->Binary(ynn_binary_multiply, 509, 6569, 510);
  g->Binary(ynn_binary_add, 510, 435, 511);
}

// Scope: "Layer11 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 511, 512);
  g->Reduce(ynn_reduce_sum, 512, 5560, {2}, true);
  g->ShapeProduct(512, 5559, {2});
  g->Binary(ynn_binary_divide, 5560, 5559, 513);
  g->Binary(ynn_binary_add, 513, 6469, 515);
  g->Unary(ynn_unary_rsqrt, 515, 516);
  g->Binary(ynn_binary_multiply, 511, 516, 517);
  g->Binary(ynn_binary_multiply, 517, 6572, 518);
  g->Quantize(518, 519, 0.015670500695705414, 0);
  g->Transpose(6566, 3890, {1,0});
  g->Binary(ynn_binary_multiply, 3887, 3889, 3885);
  g->Dot(519, 3890, YNN_INVALID_VALUE_ID, 3884, 1);
  g->DequantizeTensor(3884, YNN_INVALID_VALUE_ID, 3885, 3886);
  g->QuantizeTensor(3886, 6434, 3888, 520);
  g->Dequantize(520, 521, 0.015255915932357311, 0);
  g->Transpose(6565, 3895, {1,0});
  g->Binary(ynn_binary_multiply, 3887, 3894, 3892);
  g->Dot(519, 3895, YNN_INVALID_VALUE_ID, 3891, 1);
  g->DequantizeTensor(3891, YNN_INVALID_VALUE_ID, 3892, 3893);
  g->QuantizeTensor(3893, 6434, 3888, 522);
  g->Dequantize(522, 523, 0.015255915932357311, 0);
  g->Polynomial(523, 5563, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5563, 5564);
  g->Binary(ynn_binary_add, 5564, 5430, 5561);
  g->Binary(ynn_binary_multiply, 523, 5428, 5562);
  g->Binary(ynn_binary_multiply, 5562, 5561, 526);
  g->Binary(ynn_binary_multiply, 521, 526, 527);
  g->Quantize(527, 528, 0.011195876635611057, 0);
  g->Transpose(6564, 3902, {1,0});
  g->Binary(ynn_binary_multiply, 3899, 3901, 3897);
  g->Dot(528, 3902, YNN_INVALID_VALUE_ID, 3896, 1);
  g->DequantizeTensor(3896, YNN_INVALID_VALUE_ID, 3897, 3898);
  g->QuantizeTensor(3898, 6434, 3900, 529);
  g->Dequantize(529, 530, 0.004389102105051279, 0);
  g->Unary(ynn_unary_square, 530, 531);
  g->Reduce(ynn_reduce_sum, 531, 5566, {2}, true);
  g->ShapeProduct(531, 5565, {2});
  g->Binary(ynn_binary_divide, 5566, 5565, 532);
  g->Binary(ynn_binary_add, 532, 6469, 533);
  g->Unary(ynn_unary_rsqrt, 533, 534);
  g->Binary(ynn_binary_multiply, 530, 534, 535);
  g->Binary(ynn_binary_multiply, 535, 6570, 537);
  g->Binary(ynn_binary_add, 537, 511, 538);
}

// Scope: "Layer11 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(421, 539, {0,0,11,0}, {-1,-1,1,-1});
  g->Reshape(539, 540, {1,1,256});
  g->Unary(ynn_unary_square, 540, 541);
  g->Reduce(ynn_reduce_sum, 541, 5568, {2}, true);
  g->ShapeProduct(541, 5567, {2});
  g->Binary(ynn_binary_divide, 5568, 5567, 542);
  g->Binary(ynn_binary_add, 542, 6469, 543);
  g->Unary(ynn_unary_rsqrt, 543, 544);
  g->Binary(ynn_binary_multiply, 540, 544, 545);
  g->Binary(ynn_binary_multiply, 545, 7048, 546);
  g->Binary(ynn_binary_multiply, 7052, 6472, 548);
  g->Binary(ynn_binary_add, 546, 548, 549);
  g->Binary(ynn_binary_multiply, 549, 6466, 550);
  g->Quantize(538, 551, 0.1750430017709732, 0);
  g->Transpose(6567, 3909, {1,0});
  g->Binary(ynn_binary_multiply, 3906, 3908, 3904);
  g->Dot(551, 3909, YNN_INVALID_VALUE_ID, 3903, 1);
  g->DequantizeTensor(3903, YNN_INVALID_VALUE_ID, 3904, 3905);
  g->QuantizeTensor(3905, 6434, 3907, 552);
  g->Dequantize(552, 553, 0.07529528439044952, 0);
  g->Polynomial(553, 5571, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5571, 5572);
  g->Binary(ynn_binary_add, 5572, 5430, 5569);
  g->Binary(ynn_binary_multiply, 553, 5428, 5570);
  g->Binary(ynn_binary_multiply, 5570, 5569, 554);
  g->Binary(ynn_binary_multiply, 554, 550, 555);
  g->Quantize(555, 556, 0.15846458077430725, 0);
  g->Transpose(6568, 3916, {1,0});
  g->Binary(ynn_binary_multiply, 3913, 3915, 3911);
  g->Dot(556, 3916, YNN_INVALID_VALUE_ID, 3910, 1);
  g->DequantizeTensor(3910, YNN_INVALID_VALUE_ID, 3911, 3912);
  g->QuantizeTensor(3912, 6434, 3914, 557);
  g->Dequantize(557, 559, 0.1771666705608368, 0);
  g->Unary(ynn_unary_square, 559, 560);
  g->Reduce(ynn_reduce_sum, 560, 5574, {2}, true);
  g->ShapeProduct(560, 5573, {2});
  g->Binary(ynn_binary_divide, 5574, 5573, 561);
  g->Binary(ynn_binary_add, 561, 6469, 562);
  g->Unary(ynn_unary_rsqrt, 562, 563);
  g->Binary(ynn_binary_multiply, 559, 563, 564);
  g->Binary(ynn_binary_multiply, 564, 6571, 565);
  g->Binary(ynn_binary_add, 538, 565, 566);
  g->Binary(ynn_binary_multiply, 566, 6563, 567);
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
  g->Quantize(574, 575, 0.08767248690128326, 0);
  g->Transpose(6591, 3923, {1,0});
  g->Binary(ynn_binary_multiply, 3920, 3922, 3918);
  g->Dot(575, 3923, YNN_INVALID_VALUE_ID, 3917, 1);
  g->DequantizeTensor(3917, YNN_INVALID_VALUE_ID, 3918, 3919);
  g->QuantizeTensor(3919, 6434, 3921, 576);
  g->Dequantize(576, 577, 0.08070866763591766, 0);
  g->Reshape(577, 578, {1,1,1,256});
  g->Transpose(578, 579, {0,2,1,3});
  g->Unary(ynn_unary_square, 579, 581);
  g->Reduce(ynn_reduce_sum, 581, 5580, {3}, true);
  g->ShapeProduct(581, 5579, {3});
  g->Binary(ynn_binary_divide, 5580, 5579, 582);
  g->Binary(ynn_binary_add, 582, 6469, 583);
  g->Unary(ynn_unary_rsqrt, 583, 584);
  g->Binary(ynn_binary_multiply, 579, 584, 585);
  g->Binary(ynn_binary_multiply, 585, 6590, 586);
  g->Slice(586, 587, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(586, 588, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 588, 589);
  g->Concat({589,587}, 590, 3);
  g->Binary(ynn_binary_multiply, 586, 3009, 592);
  g->Binary(ynn_binary_multiply, 590, 3112, 593);
  g->Binary(ynn_binary_add, 592, 593, 594);
  g->Transpose(6595, 3928, {1,0});
  g->Binary(ynn_binary_multiply, 3920, 3927, 3925);
  g->Dot(575, 3928, YNN_INVALID_VALUE_ID, 3924, 1);
  g->DequantizeTensor(3924, YNN_INVALID_VALUE_ID, 3925, 3926);
  g->QuantizeTensor(3926, 6434, 3921, 595);
  g->Dequantize(595, 596, 0.08070866763591766, 0);
  g->Reshape(596, 597, {1,1,1,256});
  g->Transpose(597, 598, {0,2,1,3});
  g->Unary(ynn_unary_square, 598, 599);
  g->Reduce(ynn_reduce_sum, 599, 5582, {3}, true);
  g->ShapeProduct(599, 5581, {3});
  g->Binary(ynn_binary_divide, 5582, 5581, 600);
  g->Binary(ynn_binary_add, 600, 6469, 602);
  g->Unary(ynn_unary_rsqrt, 602, 603);
  g->Binary(ynn_binary_multiply, 598, 603, 604);
}

// Scope: "Layer12 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(594, 605, 0.005788442213088274, 0);
  g->Append(6439, 605, 7089, 2, s2, slinky::expr(int64_t{1}));
  g->View(7089, 7119, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(604, 606, 0.047244105488061905, 0);
  g->Append(6454, 606, 7104, 2, s2, slinky::expr(int64_t{1}));
  g->View(7104, 7134, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer12 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(6594, 3934, {1,0});
  g->Binary(ynn_binary_multiply, 3920, 3933, 3930);
  g->Dot(575, 3934, YNN_INVALID_VALUE_ID, 3929, 1);
  g->DequantizeTensor(3929, YNN_INVALID_VALUE_ID, 3930, 3931);
  g->QuantizeTensor(3931, 6434, 3932, 608);
  g->Dequantize(608, 609, 0.12795276939868927, 0);
  g->SplitDim(609, 610, 2, {8,256});
  g->Transpose(610, 611, {0,2,1,3});
  g->Unary(ynn_unary_square, 611, 612);
  g->Reduce(ynn_reduce_sum, 612, 5584, {3}, true);
  g->ShapeProduct(612, 5583, {3});
  g->Binary(ynn_binary_divide, 5584, 5583, 613);
  g->Binary(ynn_binary_add, 613, 6469, 614);
  g->Unary(ynn_unary_rsqrt, 614, 615);
  g->Binary(ynn_binary_multiply, 611, 615, 616);
  g->Binary(ynn_binary_multiply, 616, 6593, 617);
  g->Slice(617, 619, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(617, 620, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 620, 621);
  g->Concat({621,619}, 622, 3);
  g->Binary(ynn_binary_multiply, 617, 3009, 623);
  g->Binary(ynn_binary_multiply, 622, 3112, 624);
  g->Binary(ynn_binary_add, 623, 624, 625);
}

// Scope: "Layer12 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7119, 626, 0.005788442213088274, 0);
  g->Dequantize(7134, 627, 0.047244105488061905, 0);
  g->Matmul(625, 626, 628, false, true);
  g->Mask(628, 6479, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6479, 5590, {-1}, true);
  g->Binary(ynn_binary_subtract, 6479, 5590, 5587);
  g->Unary(ynn_unary_exp, 5587, 5588);
  g->Reduce(ynn_reduce_sum, 5588, 5591, {-1}, true);
  g->Binary(ynn_binary_divide, 5430, 5591, 5589);
  g->Binary(ynn_binary_multiply, 5588, 5589, 631);
  g->Matmul(631, 627, 632, false, false);
}

// Scope: "Layer12 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(632, 633, {0,2,1,3});
  g->FuseDims(633, 634, 2, 2);
  g->Quantize(634, 635, 0.028543315827846527, 0);
  g->Transpose(6592, 3941, {1,0});
  g->Binary(ynn_binary_multiply, 3938, 3940, 3936);
  g->Dot(635, 3941, YNN_INVALID_VALUE_ID, 3935, 1);
  g->DequantizeTensor(3935, YNN_INVALID_VALUE_ID, 3936, 3937);
  g->QuantizeTensor(3937, 6434, 3939, 636);
  g->Dequantize(636, 637, 0.021804405376315117, 0);
}

// Scope: "Layer12 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 567, 568);
  g->Reduce(ynn_reduce_sum, 568, 5578, {2}, true);
  g->ShapeProduct(568, 5577, {2});
  g->Binary(ynn_binary_divide, 5578, 5577, 570);
  g->Binary(ynn_binary_add, 570, 6469, 571);
  g->Unary(ynn_unary_rsqrt, 571, 572);
  g->Binary(ynn_binary_multiply, 567, 572, 573);
  g->Binary(ynn_binary_multiply, 573, 6579, 574);
  BuildLayer12AttentionKvProjection(ctx);
  BuildLayer12AttentionCacheUpdate(ctx);
  BuildLayer12AttentionQueryProjection(ctx);
  BuildLayer12AttentionSdpa(ctx);
  BuildLayer12AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 637, 638);
  g->Reduce(ynn_reduce_sum, 638, 5593, {2}, true);
  g->ShapeProduct(638, 5592, {2});
  g->Binary(ynn_binary_divide, 5593, 5592, 639);
  g->Binary(ynn_binary_add, 639, 6469, 641);
  g->Unary(ynn_unary_rsqrt, 641, 642);
  g->Binary(ynn_binary_multiply, 637, 642, 643);
  g->Binary(ynn_binary_multiply, 643, 6586, 644);
  g->Binary(ynn_binary_add, 644, 567, 645);
}

// Scope: "Layer12 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 645, 646);
  g->Reduce(ynn_reduce_sum, 646, 5595, {2}, true);
  g->ShapeProduct(646, 5594, {2});
  g->Binary(ynn_binary_divide, 5595, 5594, 647);
  g->Binary(ynn_binary_add, 647, 6469, 648);
  g->Unary(ynn_unary_rsqrt, 648, 649);
  g->Binary(ynn_binary_multiply, 645, 649, 650);
  g->Binary(ynn_binary_multiply, 650, 6589, 652);
  g->Quantize(652, 653, 0.013748278841376305, 0);
  g->Transpose(6583, 3948, {1,0});
  g->Binary(ynn_binary_multiply, 3945, 3947, 3943);
  g->Dot(653, 3948, YNN_INVALID_VALUE_ID, 3942, 1);
  g->DequantizeTensor(3942, YNN_INVALID_VALUE_ID, 3943, 3944);
  g->QuantizeTensor(3944, 6434, 3946, 654);
  g->Dequantize(654, 655, 0.012795286253094673, 0);
  g->Transpose(6582, 3953, {1,0});
  g->Binary(ynn_binary_multiply, 3945, 3952, 3950);
  g->Dot(653, 3953, YNN_INVALID_VALUE_ID, 3949, 1);
  g->DequantizeTensor(3949, YNN_INVALID_VALUE_ID, 3950, 3951);
  g->QuantizeTensor(3951, 6434, 3946, 656);
  g->Dequantize(656, 657, 0.012795286253094673, 0);
  g->Polynomial(657, 5598, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5598, 5599);
  g->Binary(ynn_binary_add, 5599, 5430, 5596);
  g->Binary(ynn_binary_multiply, 657, 5428, 5597);
  g->Binary(ynn_binary_multiply, 5597, 5596, 658);
  g->Binary(ynn_binary_multiply, 655, 658, 659);
  g->Quantize(659, 660, 0.00768947834149003, 0);
  g->Transpose(6581, 3960, {1,0});
  g->Binary(ynn_binary_multiply, 3957, 3959, 3955);
  g->Dot(660, 3960, YNN_INVALID_VALUE_ID, 3954, 1);
  g->DequantizeTensor(3954, YNN_INVALID_VALUE_ID, 3955, 3956);
  g->QuantizeTensor(3956, 6434, 3958, 662);
  g->Dequantize(662, 663, 0.005636297166347504, 0);
  g->Unary(ynn_unary_square, 663, 664);
  g->Reduce(ynn_reduce_sum, 664, 5601, {2}, true);
  g->ShapeProduct(664, 5600, {2});
  g->Binary(ynn_binary_divide, 5601, 5600, 665);
  g->Binary(ynn_binary_add, 665, 6469, 666);
  g->Unary(ynn_unary_rsqrt, 666, 667);
  g->Binary(ynn_binary_multiply, 663, 667, 668);
  g->Binary(ynn_binary_multiply, 668, 6587, 669);
  g->Binary(ynn_binary_add, 669, 645, 670);
}

// Scope: "Layer12 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(421, 671, {0,0,12,0}, {-1,-1,1,-1});
  g->Reshape(671, 673, {1,1,256});
  g->Unary(ynn_unary_square, 673, 674);
  g->Reduce(ynn_reduce_sum, 674, 5603, {2}, true);
  g->ShapeProduct(674, 5602, {2});
  g->Binary(ynn_binary_divide, 5603, 5602, 675);
  g->Binary(ynn_binary_add, 675, 6469, 676);
  g->Unary(ynn_unary_rsqrt, 676, 677);
  g->Binary(ynn_binary_multiply, 673, 677, 678);
  g->Binary(ynn_binary_multiply, 678, 7048, 679);
  g->Binary(ynn_binary_multiply, 7053, 6472, 680);
  g->Binary(ynn_binary_add, 679, 680, 681);
  g->Binary(ynn_binary_multiply, 681, 6466, 682);
  g->Quantize(670, 684, 0.19133253395557404, 0);
  g->Transpose(6584, 3966, {1,0});
  g->Binary(ynn_binary_multiply, 3964, 3965, 3962);
  g->Dot(684, 3966, YNN_INVALID_VALUE_ID, 3961, 1);
  g->DequantizeTensor(3961, YNN_INVALID_VALUE_ID, 3962, 3963);
  g->QuantizeTensor(3963, 6434, 3907, 685);
  g->Dequantize(685, 686, 0.07529528439044952, 0);
  g->Polynomial(686, 5606, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5606, 5607);
  g->Binary(ynn_binary_add, 5607, 5430, 5604);
  g->Binary(ynn_binary_multiply, 686, 5428, 5605);
  g->Binary(ynn_binary_multiply, 5605, 5604, 687);
  g->Binary(ynn_binary_multiply, 687, 682, 688);
  g->Quantize(688, 689, 0.12450788170099258, 0);
  g->Transpose(6585, 3973, {1,0});
  g->Binary(ynn_binary_multiply, 3970, 3972, 3968);
  g->Dot(689, 3973, YNN_INVALID_VALUE_ID, 3967, 1);
  g->DequantizeTensor(3967, YNN_INVALID_VALUE_ID, 3968, 3969);
  g->QuantizeTensor(3969, 6434, 3971, 690);
  g->Dequantize(690, 691, 0.12528184056282043, 0);
  g->Unary(ynn_unary_square, 691, 692);
  g->Reduce(ynn_reduce_sum, 692, 5609, {2}, true);
  g->ShapeProduct(692, 5608, {2});
  g->Binary(ynn_binary_divide, 5609, 5608, 693);
  g->Binary(ynn_binary_add, 693, 6469, 694);
  g->Unary(ynn_unary_rsqrt, 694, 695);
  g->Binary(ynn_binary_multiply, 691, 695, 696);
  g->Binary(ynn_binary_multiply, 696, 6588, 697);
  g->Binary(ynn_binary_add, 670, 697, 698);
  g->Binary(ynn_binary_multiply, 698, 6580, 699);
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
  g->Quantize(706, 707, 0.02862965501844883, 0);
  g->Transpose(6608, 3985, {1,0});
  g->Binary(ynn_binary_multiply, 3982, 3984, 3980);
  g->Dot(707, 3985, YNN_INVALID_VALUE_ID, 3979, 1);
  g->DequantizeTensor(3979, YNN_INVALID_VALUE_ID, 3980, 3981);
  g->QuantizeTensor(3981, 6434, 3983, 708);
  g->Dequantize(708, 709, 0.035925209522247314, 0);
  g->Reshape(709, 710, {1,1,1,256});
  g->Transpose(710, 711, {0,2,1,3});
  g->Unary(ynn_unary_square, 711, 712);
  g->Reduce(ynn_reduce_sum, 712, 5613, {3}, true);
  g->ShapeProduct(712, 5612, {3});
  g->Binary(ynn_binary_divide, 5613, 5612, 713);
  g->Binary(ynn_binary_add, 713, 6469, 714);
  g->Unary(ynn_unary_rsqrt, 714, 716);
  g->Binary(ynn_binary_multiply, 711, 716, 717);
  g->Binary(ynn_binary_multiply, 717, 6607, 718);
  g->Slice(718, 719, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(718, 720, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 720, 721);
  g->Concat({721,719}, 722, 3);
  g->Binary(ynn_binary_multiply, 718, 3009, 723);
  g->Binary(ynn_binary_multiply, 722, 3112, 724);
  g->Binary(ynn_binary_add, 723, 724, 725);
  g->Transpose(6612, 3990, {1,0});
  g->Binary(ynn_binary_multiply, 3982, 3989, 3987);
  g->Dot(707, 3990, YNN_INVALID_VALUE_ID, 3986, 1);
  g->DequantizeTensor(3986, YNN_INVALID_VALUE_ID, 3987, 3988);
  g->QuantizeTensor(3988, 6434, 3983, 727);
  g->Dequantize(727, 728, 0.035925209522247314, 0);
  g->Reshape(728, 729, {1,1,1,256});
  g->Transpose(729, 730, {0,2,1,3});
  g->Unary(ynn_unary_square, 730, 731);
  g->Reduce(ynn_reduce_sum, 731, 5615, {3}, true);
  g->ShapeProduct(731, 5614, {3});
  g->Binary(ynn_binary_divide, 5615, 5614, 732);
  g->Binary(ynn_binary_add, 732, 6469, 733);
  g->Unary(ynn_unary_rsqrt, 733, 734);
  g->Binary(ynn_binary_multiply, 730, 734, 735);
}

// Scope: "Layer13 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(725, 738, 0.0059552486054599285, 0);
  g->Append(6440, 738, 7090, 2, s2, slinky::expr(int64_t{1}));
  g->View(7090, 7120, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(735, 739, 0.047244105488061905, 0);
  g->Append(6455, 739, 7105, 2, s2, slinky::expr(int64_t{1}));
  g->View(7105, 7135, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer13 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(6611, 3995, {1,0});
  g->Binary(ynn_binary_multiply, 3982, 3994, 3992);
  g->Dot(707, 3995, YNN_INVALID_VALUE_ID, 3991, 1);
  g->DequantizeTensor(3991, YNN_INVALID_VALUE_ID, 3992, 3993);
  g->QuantizeTensor(3993, 6434, 3802, 740);
  g->Dequantize(740, 741, 0.03764764964580536, 0);
  g->SplitDim(741, 742, 2, {8,256});
  g->Transpose(742, 744, {0,2,1,3});
  g->Unary(ynn_unary_square, 744, 745);
  g->Reduce(ynn_reduce_sum, 745, 5617, {3}, true);
  g->ShapeProduct(745, 5616, {3});
  g->Binary(ynn_binary_divide, 5617, 5616, 746);
  g->Binary(ynn_binary_add, 746, 6469, 747);
  g->Unary(ynn_unary_rsqrt, 747, 748);
  g->Binary(ynn_binary_multiply, 744, 748, 749);
  g->Binary(ynn_binary_multiply, 749, 6610, 750);
  g->Slice(750, 751, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(750, 752, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 752, 753);
  g->Concat({753,751}, 755, 3);
  g->Binary(ynn_binary_multiply, 750, 3009, 756);
  g->Binary(ynn_binary_multiply, 755, 3112, 757);
  g->Binary(ynn_binary_add, 756, 757, 758);
}

// Scope: "Layer13 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7120, 759, 0.0059552486054599285, 0);
  g->Dequantize(7135, 760, 0.047244105488061905, 0);
  g->Matmul(758, 759, 761, false, true);
  g->Mask(761, 6480, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6480, 5623, {-1}, true);
  g->Binary(ynn_binary_subtract, 6480, 5623, 5620);
  g->Unary(ynn_unary_exp, 5620, 5621);
  g->Reduce(ynn_reduce_sum, 5621, 5624, {-1}, true);
  g->Binary(ynn_binary_divide, 5430, 5624, 5622);
  g->Binary(ynn_binary_multiply, 5621, 5622, 762);
  g->Matmul(762, 760, 763, false, false);
}

// Scope: "Layer13 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(763, 765, {0,2,1,3});
  g->FuseDims(765, 766, 2, 2);
  g->Quantize(766, 767, 0.026205718517303467, 0);
  g->Transpose(6609, 4002, {1,0});
  g->Binary(ynn_binary_multiply, 3999, 4001, 3997);
  g->Dot(767, 4002, YNN_INVALID_VALUE_ID, 3996, 1);
  g->DequantizeTensor(3996, YNN_INVALID_VALUE_ID, 3997, 3998);
  g->QuantizeTensor(3998, 6434, 4000, 768);
  g->Dequantize(768, 769, 0.03592992201447487, 0);
}

// Scope: "Layer13 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 699, 700);
  g->Reduce(ynn_reduce_sum, 700, 5611, {2}, true);
  g->ShapeProduct(700, 5610, {2});
  g->Binary(ynn_binary_divide, 5611, 5610, 701);
  g->Binary(ynn_binary_add, 701, 6469, 702);
  g->Unary(ynn_unary_rsqrt, 702, 703);
  g->Binary(ynn_binary_multiply, 699, 703, 705);
  g->Binary(ynn_binary_multiply, 705, 6596, 706);
  BuildLayer13AttentionKvProjection(ctx);
  BuildLayer13AttentionCacheUpdate(ctx);
  BuildLayer13AttentionQueryProjection(ctx);
  BuildLayer13AttentionSdpa(ctx);
  BuildLayer13AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 769, 770);
  g->Reduce(ynn_reduce_sum, 770, 5626, {2}, true);
  g->ShapeProduct(770, 5625, {2});
  g->Binary(ynn_binary_divide, 5626, 5625, 771);
  g->Binary(ynn_binary_add, 771, 6469, 772);
  g->Unary(ynn_unary_rsqrt, 772, 773);
  g->Binary(ynn_binary_multiply, 769, 773, 774);
  g->Binary(ynn_binary_multiply, 774, 6603, 776);
  g->Binary(ynn_binary_add, 776, 699, 777);
}

// Scope: "Layer13 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 777, 778);
  g->Reduce(ynn_reduce_sum, 778, 5628, {2}, true);
  g->ShapeProduct(778, 5627, {2});
  g->Binary(ynn_binary_divide, 5628, 5627, 779);
  g->Binary(ynn_binary_add, 779, 6469, 780);
  g->Unary(ynn_unary_rsqrt, 780, 781);
  g->Binary(ynn_binary_multiply, 777, 781, 782);
  g->Binary(ynn_binary_multiply, 782, 6606, 783);
  g->Quantize(783, 784, 0.0083004767075181, 0);
  g->Transpose(6600, 4009, {1,0});
  g->Binary(ynn_binary_multiply, 4006, 4008, 4004);
  g->Dot(784, 4009, YNN_INVALID_VALUE_ID, 4003, 1);
  g->DequantizeTensor(4003, YNN_INVALID_VALUE_ID, 4004, 4005);
  g->QuantizeTensor(4005, 6434, 4007, 785);
  g->Dequantize(785, 787, 0.011934065259993076, 0);
  g->Transpose(6599, 4014, {1,0});
  g->Binary(ynn_binary_multiply, 4006, 4013, 4011);
  g->Dot(784, 4014, YNN_INVALID_VALUE_ID, 4010, 1);
  g->DequantizeTensor(4010, YNN_INVALID_VALUE_ID, 4011, 4012);
  g->QuantizeTensor(4012, 6434, 4007, 788);
  g->Dequantize(788, 789, 0.011934065259993076, 0);
  g->Polynomial(789, 5631, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5631, 5632);
  g->Binary(ynn_binary_add, 5632, 5430, 5629);
  g->Binary(ynn_binary_multiply, 789, 5428, 5630);
  g->Binary(ynn_binary_multiply, 5630, 5629, 790);
  g->Binary(ynn_binary_multiply, 787, 790, 791);
  g->Quantize(791, 792, 0.0015532826073467731, 0);
  g->Transpose(6598, 4021, {1,0});
  g->Binary(ynn_binary_multiply, 4018, 4020, 4016);
  g->Dot(792, 4021, YNN_INVALID_VALUE_ID, 4015, 1);
  g->DequantizeTensor(4015, YNN_INVALID_VALUE_ID, 4016, 4017);
  g->QuantizeTensor(4017, 6434, 4019, 793);
  g->Dequantize(793, 794, 0.002153691602870822, 0);
  g->Unary(ynn_unary_square, 794, 795);
  g->Reduce(ynn_reduce_sum, 795, 5634, {2}, true);
  g->ShapeProduct(795, 5633, {2});
  g->Binary(ynn_binary_divide, 5634, 5633, 797);
  g->Binary(ynn_binary_add, 797, 6469, 798);
  g->Unary(ynn_unary_rsqrt, 798, 799);
  g->Binary(ynn_binary_multiply, 794, 799, 800);
  g->Binary(ynn_binary_multiply, 800, 6604, 801);
  g->Binary(ynn_binary_add, 801, 777, 802);
}

// Scope: "Layer13 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(421, 803, {0,0,13,0}, {-1,-1,1,-1});
  g->Reshape(803, 804, {1,1,256});
  g->Unary(ynn_unary_square, 804, 805);
  g->Reduce(ynn_reduce_sum, 805, 5636, {2}, true);
  g->ShapeProduct(805, 5635, {2});
  g->Binary(ynn_binary_divide, 5636, 5635, 806);
  g->Binary(ynn_binary_add, 806, 6469, 807);
  g->Unary(ynn_unary_rsqrt, 807, 808);
  g->Binary(ynn_binary_multiply, 804, 808, 809);
  g->Binary(ynn_binary_multiply, 809, 7048, 810);
  g->Binary(ynn_binary_multiply, 7054, 6472, 811);
  g->Binary(ynn_binary_add, 810, 811, 812);
  g->Binary(ynn_binary_multiply, 812, 6466, 813);
  g->Quantize(802, 814, 0.5171695351600647, 0);
  g->Transpose(6601, 4028, {1,0});
  g->Binary(ynn_binary_multiply, 4025, 4027, 4023);
  g->Dot(814, 4028, YNN_INVALID_VALUE_ID, 4022, 1);
  g->DequantizeTensor(4022, YNN_INVALID_VALUE_ID, 4023, 4024);
  g->QuantizeTensor(4024, 6434, 4026, 815);
  g->Dequantize(815, 816, 0.13385827839374542, 0);
  g->Polynomial(816, 5639, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5639, 5640);
  g->Binary(ynn_binary_add, 5640, 5430, 5637);
  g->Binary(ynn_binary_multiply, 816, 5428, 5638);
  g->Binary(ynn_binary_multiply, 5638, 5637, 817);
  g->Binary(ynn_binary_multiply, 817, 813, 818);
  g->Quantize(818, 819, 0.4094488322734833, 0);
  g->Transpose(6602, 4035, {1,0});
  g->Binary(ynn_binary_multiply, 4032, 4034, 4030);
  g->Dot(819, 4035, YNN_INVALID_VALUE_ID, 4029, 1);
  g->DequantizeTensor(4029, YNN_INVALID_VALUE_ID, 4030, 4031);
  g->QuantizeTensor(4031, 6434, 4033, 820);
  g->Dequantize(820, 821, 0.25065305829048157, 0);
  g->Unary(ynn_unary_square, 821, 822);
  g->Reduce(ynn_reduce_sum, 822, 5642, {2}, true);
  g->ShapeProduct(822, 5641, {2});
  g->Binary(ynn_binary_divide, 5642, 5641, 823);
  g->Binary(ynn_binary_add, 823, 6469, 824);
  g->Unary(ynn_unary_rsqrt, 824, 825);
  g->Binary(ynn_binary_multiply, 821, 825, 826);
  g->Binary(ynn_binary_multiply, 826, 6605, 828);
  g->Binary(ynn_binary_add, 802, 828, 829);
  g->Binary(ynn_binary_multiply, 829, 6597, 830);
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
  g->Quantize(836, 837, 0.20956376194953918, 0);
  g->Transpose(6625, 4042, {1,0});
  g->Binary(ynn_binary_multiply, 4039, 4041, 4037);
  g->Dot(837, 4042, YNN_INVALID_VALUE_ID, 4036, 1);
  g->DequantizeTensor(4036, YNN_INVALID_VALUE_ID, 4037, 4038);
  g->QuantizeTensor(4038, 6434, 4040, 839);
  g->Dequantize(839, 840, 0.21751970052719116, 0);
  g->Reshape(840, 841, {1,1,1,512});
  g->Transpose(841, 842, {0,2,1,3});
  g->Unary(ynn_unary_square, 842, 843);
  g->Reduce(ynn_reduce_sum, 843, 5646, {3}, true);
  g->ShapeProduct(843, 5645, {3});
  g->Binary(ynn_binary_divide, 5646, 5645, 844);
  g->Binary(ynn_binary_add, 844, 6469, 845);
  g->Unary(ynn_unary_rsqrt, 845, 846);
  g->Binary(ynn_binary_multiply, 842, 846, 847);
  g->Binary(ynn_binary_multiply, 847, 6624, 848);
  g->Slice(848, 849, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(848, 850, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 850, 851);
  g->Concat({851,849}, 852, 3);
  g->Binary(ynn_binary_multiply, 848, 3526, 853);
  g->Binary(ynn_binary_multiply, 852, 2, 854);
  g->Binary(ynn_binary_add, 853, 854, 855);
  g->Transpose(6629, 4047, {1,0});
  g->Binary(ynn_binary_multiply, 4039, 4046, 4044);
  g->Dot(837, 4047, YNN_INVALID_VALUE_ID, 4043, 1);
  g->DequantizeTensor(4043, YNN_INVALID_VALUE_ID, 4044, 4045);
  g->QuantizeTensor(4045, 6434, 4040, 856);
  g->Dequantize(856, 857, 0.21751970052719116, 0);
  g->Reshape(857, 858, {1,1,1,512});
  g->Transpose(858, 859, {0,2,1,3});
  g->Unary(ynn_unary_square, 859, 860);
  g->Reduce(ynn_reduce_sum, 860, 5648, {3}, true);
  g->ShapeProduct(860, 5647, {3});
  g->Binary(ynn_binary_divide, 5648, 5647, 861);
  g->Binary(ynn_binary_add, 861, 6469, 862);
  g->Unary(ynn_unary_rsqrt, 862, 863);
  g->Binary(ynn_binary_multiply, 859, 863, 864);
}

// Scope: "Layer14 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(855, 865, 0.001091228099539876, 0);
  g->Append(6441, 865, 7091, 2, s2, slinky::expr(int64_t{1}));
  g->View(7091, 7121, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(864, 867, 0.01785714365541935, 0);
  g->Append(6456, 867, 7106, 2, s2, slinky::expr(int64_t{1}));
  g->View(7106, 7136, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer14 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(6628, 4059, {1,0});
  g->Binary(ynn_binary_multiply, 4039, 4058, 4055);
  g->Dot(837, 4059, YNN_INVALID_VALUE_ID, 4054, 1);
  g->DequantizeTensor(4054, YNN_INVALID_VALUE_ID, 4055, 4056);
  g->QuantizeTensor(4056, 6434, 4057, 868);
  g->Dequantize(868, 869, 0.3385826647281647, 0);
  g->SplitDim(869, 870, 2, {8,512});
  g->Transpose(870, 871, {0,2,1,3});
  g->Unary(ynn_unary_square, 871, 872);
  g->Reduce(ynn_reduce_sum, 872, 5650, {3}, true);
  g->ShapeProduct(872, 5649, {3});
  g->Binary(ynn_binary_divide, 5650, 5649, 873);
  g->Binary(ynn_binary_add, 873, 6469, 875);
  g->Unary(ynn_unary_rsqrt, 875, 876);
  g->Binary(ynn_binary_multiply, 871, 876, 877);
  g->Binary(ynn_binary_multiply, 877, 6627, 878);
  g->Slice(878, 879, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(878, 880, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 880, 881);
  g->Concat({881,879}, 882, 3);
  g->Binary(ynn_binary_multiply, 878, 3526, 883);
  g->Binary(ynn_binary_multiply, 882, 2, 884);
  g->Binary(ynn_binary_add, 883, 884, 886);
}

// Scope: "Layer14 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7121, 887, 0.001091228099539876, 0);
  g->Dequantize(7136, 888, 0.01785714365541935, 0);
  g->Matmul(886, 887, 889, false, true);
  g->Mask(889, 6481, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 6481, 5654, {-1}, true);
  g->Binary(ynn_binary_subtract, 6481, 5654, 5651);
  g->Unary(ynn_unary_exp, 5651, 5652);
  g->Reduce(ynn_reduce_sum, 5652, 5655, {-1}, true);
  g->Binary(ynn_binary_divide, 5430, 5655, 5653);
  g->Binary(ynn_binary_multiply, 5652, 5653, 890);
  g->Matmul(890, 888, 891, false, false);
}

// Scope: "Layer14 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(891, 892, {0,2,1,3});
  g->FuseDims(892, 893, 2, 2);
  g->Quantize(893, 894, 0.017962608486413956, 0);
  g->Transpose(6626, 4065, {1,0});
  g->Binary(ynn_binary_multiply, 3743, 4064, 4061);
  g->Dot(894, 4065, YNN_INVALID_VALUE_ID, 4060, 1);
  g->DequantizeTensor(4060, YNN_INVALID_VALUE_ID, 4061, 4062);
  g->QuantizeTensor(4062, 6434, 4063, 896);
  g->Dequantize(896, 897, 0.019122116267681122, 0);
}

// Scope: "Layer14 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 830, 831);
  g->Reduce(ynn_reduce_sum, 831, 5644, {2}, true);
  g->ShapeProduct(831, 5643, {2});
  g->Binary(ynn_binary_divide, 5644, 5643, 832);
  g->Binary(ynn_binary_add, 832, 6469, 833);
  g->Unary(ynn_unary_rsqrt, 833, 834);
  g->Binary(ynn_binary_multiply, 830, 834, 835);
  g->Binary(ynn_binary_multiply, 835, 6613, 836);
  BuildLayer14AttentionKvProjection(ctx);
  BuildLayer14AttentionCacheUpdate(ctx);
  BuildLayer14AttentionQueryProjection(ctx);
  BuildLayer14AttentionSdpa(ctx);
  BuildLayer14AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 897, 898);
  g->Reduce(ynn_reduce_sum, 898, 5657, {2}, true);
  g->ShapeProduct(898, 5656, {2});
  g->Binary(ynn_binary_divide, 5657, 5656, 899);
  g->Binary(ynn_binary_add, 899, 6469, 900);
  g->Unary(ynn_unary_rsqrt, 900, 901);
  g->Binary(ynn_binary_multiply, 897, 901, 902);
  g->Binary(ynn_binary_multiply, 902, 6620, 903);
  g->Binary(ynn_binary_add, 903, 830, 904);
}

// Scope: "Layer14 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 904, 905);
  g->Reduce(ynn_reduce_sum, 905, 5659, {2}, true);
  g->ShapeProduct(905, 5658, {2});
  g->Binary(ynn_binary_divide, 5659, 5658, 907);
  g->Binary(ynn_binary_add, 907, 6469, 908);
  g->Unary(ynn_unary_rsqrt, 908, 909);
  g->Binary(ynn_binary_multiply, 904, 909, 910);
  g->Binary(ynn_binary_multiply, 910, 6623, 911);
  g->Quantize(911, 912, 0.01763528399169445, 0);
  g->Transpose(6617, 4072, {1,0});
  g->Binary(ynn_binary_multiply, 4069, 4071, 4067);
  g->Dot(912, 4072, YNN_INVALID_VALUE_ID, 4066, 1);
  g->DequantizeTensor(4066, YNN_INVALID_VALUE_ID, 4067, 4068);
  g->QuantizeTensor(4068, 6434, 4070, 913);
  g->Dequantize(913, 914, 0.01457924209535122, 0);
  g->Transpose(6616, 4077, {1,0});
  g->Binary(ynn_binary_multiply, 4069, 4076, 4074);
  g->Dot(912, 4077, YNN_INVALID_VALUE_ID, 4073, 1);
  g->DequantizeTensor(4073, YNN_INVALID_VALUE_ID, 4074, 4075);
  g->QuantizeTensor(4075, 6434, 4070, 915);
  g->Dequantize(915, 917, 0.01457924209535122, 0);
  g->Polynomial(917, 5664, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5664, 5665);
  g->Binary(ynn_binary_add, 5665, 5430, 5662);
  g->Binary(ynn_binary_multiply, 917, 5428, 5663);
  g->Binary(ynn_binary_multiply, 5663, 5662, 918);
  g->Binary(ynn_binary_multiply, 914, 918, 919);
  g->Quantize(919, 920, 0.010642234236001968, 0);
  g->Transpose(6615, 4084, {1,0});
  g->Binary(ynn_binary_multiply, 4081, 4083, 4079);
  g->Dot(920, 4084, YNN_INVALID_VALUE_ID, 4078, 1);
  g->DequantizeTensor(4078, YNN_INVALID_VALUE_ID, 4079, 4080);
  g->QuantizeTensor(4080, 6434, 4082, 921);
  g->Dequantize(921, 922, 0.013017668388783932, 0);
  g->Unary(ynn_unary_square, 922, 923);
  g->Reduce(ynn_reduce_sum, 923, 5667, {2}, true);
  g->ShapeProduct(923, 5666, {2});
  g->Binary(ynn_binary_divide, 5667, 5666, 924);
  g->Binary(ynn_binary_add, 924, 6469, 925);
  g->Unary(ynn_unary_rsqrt, 925, 926);
  g->Binary(ynn_binary_multiply, 922, 926, 928);
  g->Binary(ynn_binary_multiply, 928, 6621, 929);
  g->Binary(ynn_binary_add, 929, 904, 930);
}

// Scope: "Layer14 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(421, 931, {0,0,14,0}, {-1,-1,1,-1});
  g->Reshape(931, 932, {1,1,256});
  g->Unary(ynn_unary_square, 932, 933);
  g->Reduce(ynn_reduce_sum, 933, 5669, {2}, true);
  g->ShapeProduct(933, 5668, {2});
  g->Binary(ynn_binary_divide, 5669, 5668, 934);
  g->Binary(ynn_binary_add, 934, 6469, 935);
  g->Unary(ynn_unary_rsqrt, 935, 936);
  g->Binary(ynn_binary_multiply, 932, 936, 937);
  g->Binary(ynn_binary_multiply, 937, 7048, 940);
  g->Binary(ynn_binary_multiply, 7055, 6472, 941);
  g->Binary(ynn_binary_add, 940, 941, 942);
  g->Binary(ynn_binary_multiply, 942, 6466, 943);
  g->Quantize(930, 944, 1.2159134149551392, 0);
  g->Transpose(6618, 4091, {1,0});
  g->Binary(ynn_binary_multiply, 4088, 4090, 4086);
  g->Dot(944, 4091, YNN_INVALID_VALUE_ID, 4085, 1);
  g->DequantizeTensor(4085, YNN_INVALID_VALUE_ID, 4086, 4087);
  g->QuantizeTensor(4087, 6434, 4089, 945);
  g->Dequantize(945, 946, 0.04429135099053383, 0);
  g->Polynomial(946, 5672, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5672, 5673);
  g->Binary(ynn_binary_add, 5673, 5430, 5670);
  g->Binary(ynn_binary_multiply, 946, 5428, 5671);
  g->Binary(ynn_binary_multiply, 5671, 5670, 947);
  g->Binary(ynn_binary_multiply, 947, 943, 948);
  g->Quantize(948, 949, 0.10629922151565552, 0);
  g->Transpose(6619, 4098, {1,0});
  g->Binary(ynn_binary_multiply, 4095, 4097, 4093);
  g->Dot(949, 4098, YNN_INVALID_VALUE_ID, 4092, 1);
  g->DequantizeTensor(4092, YNN_INVALID_VALUE_ID, 4093, 4094);
  g->QuantizeTensor(4094, 6434, 4096, 951);
  g->Dequantize(951, 952, 0.045032795518636703, 0);
  g->Unary(ynn_unary_square, 952, 953);
  g->Reduce(ynn_reduce_sum, 953, 5675, {2}, true);
  g->ShapeProduct(953, 5674, {2});
  g->Binary(ynn_binary_divide, 5675, 5674, 954);
  g->Binary(ynn_binary_add, 954, 6469, 955);
  g->Unary(ynn_unary_rsqrt, 955, 956);
  g->Binary(ynn_binary_multiply, 952, 956, 957);
  g->Binary(ynn_binary_multiply, 957, 6622, 958);
  g->Binary(ynn_binary_add, 930, 958, 959);
  g->Binary(ynn_binary_multiply, 959, 6614, 960);
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
  g->Quantize(967, 968, 0.18704485893249512, 0);
  g->Transpose(6643, 4105, {1,0});
  g->Binary(ynn_binary_multiply, 4102, 4104, 4100);
  g->Dot(968, 4105, YNN_INVALID_VALUE_ID, 4099, 1);
  g->DequantizeTensor(4099, YNN_INVALID_VALUE_ID, 4100, 4101);
  g->QuantizeTensor(4101, 6434, 4103, 969);
  g->Dequantize(969, 970, 0.2814960777759552, 0);
  g->SplitDim(970, 971, 2, {8,256});
  g->Transpose(971, 973, {0,2,1,3});
  g->Unary(ynn_unary_square, 973, 974);
  g->Reduce(ynn_reduce_sum, 974, 5679, {3}, true);
  g->ShapeProduct(974, 5678, {3});
  g->Binary(ynn_binary_divide, 5679, 5678, 975);
  g->Binary(ynn_binary_add, 975, 6469, 976);
  g->Unary(ynn_unary_rsqrt, 976, 977);
  g->Binary(ynn_binary_multiply, 973, 977, 978);
  g->Binary(ynn_binary_multiply, 978, 6642, 979);
  g->Slice(979, 980, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(979, 981, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 981, 982);
  g->Concat({982,980}, 984, 3);
  g->Binary(ynn_binary_multiply, 979, 3009, 985);
  g->Binary(ynn_binary_multiply, 984, 3112, 986);
  g->Binary(ynn_binary_add, 985, 986, 987);
}

// Scope: "Layer15 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7120, 988, 0.0059552486054599285, 0);
  g->Dequantize(7135, 989, 0.047244105488061905, 0);
  g->Matmul(987, 988, 990, false, true);
  g->Mask(990, 6482, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6482, 5683, {-1}, true);
  g->Binary(ynn_binary_subtract, 6482, 5683, 5680);
  g->Unary(ynn_unary_exp, 5680, 5681);
  g->Reduce(ynn_reduce_sum, 5681, 5684, {-1}, true);
  g->Binary(ynn_binary_divide, 5430, 5684, 5682);
  g->Binary(ynn_binary_multiply, 5681, 5682, 991);
  g->Matmul(991, 989, 992, false, false);
}

// Scope: "Layer15 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(992, 994, {0,2,1,3});
  g->FuseDims(994, 995, 2, 2);
  g->Quantize(995, 996, 0.02436024509370327, 0);
  g->Transpose(6641, 4112, {1,0});
  g->Binary(ynn_binary_multiply, 4109, 4111, 4107);
  g->Dot(996, 4112, YNN_INVALID_VALUE_ID, 4106, 1);
  g->DequantizeTensor(4106, YNN_INVALID_VALUE_ID, 4107, 4108);
  g->QuantizeTensor(4108, 6434, 4110, 997);
  g->Dequantize(997, 998, 0.060289591550827026, 0);
}

// Scope: "Layer15 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 960, 962);
  g->Reduce(ynn_reduce_sum, 962, 5677, {2}, true);
  g->ShapeProduct(962, 5676, {2});
  g->Binary(ynn_binary_divide, 5677, 5676, 963);
  g->Binary(ynn_binary_add, 963, 6469, 964);
  g->Unary(ynn_unary_rsqrt, 964, 965);
  g->Binary(ynn_binary_multiply, 960, 965, 966);
  g->Binary(ynn_binary_multiply, 966, 6630, 967);
  BuildLayer15AttentionQueryProjection(ctx);
  BuildLayer15AttentionSdpa(ctx);
  BuildLayer15AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 998, 999);
  g->Reduce(ynn_reduce_sum, 999, 5686, {2}, true);
  g->ShapeProduct(999, 5685, {2});
  g->Binary(ynn_binary_divide, 5686, 5685, 1000);
  g->Binary(ynn_binary_add, 1000, 6469, 1001);
  g->Unary(ynn_unary_rsqrt, 1001, 1002);
  g->Binary(ynn_binary_multiply, 998, 1002, 1003);
  g->Binary(ynn_binary_multiply, 1003, 6637, 1005);
  g->Binary(ynn_binary_add, 1005, 960, 1006);
}

// Scope: "Layer15 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1006, 1007);
  g->Reduce(ynn_reduce_sum, 1007, 5688, {2}, true);
  g->ShapeProduct(1007, 5687, {2});
  g->Binary(ynn_binary_divide, 5688, 5687, 1008);
  g->Binary(ynn_binary_add, 1008, 6469, 1009);
  g->Unary(ynn_unary_rsqrt, 1009, 1010);
  g->Binary(ynn_binary_multiply, 1006, 1010, 1011);
  g->Binary(ynn_binary_multiply, 1011, 6640, 1012);
  g->Quantize(1012, 1013, 0.023188970983028412, 0);
  g->Transpose(6634, 4119, {1,0});
  g->Binary(ynn_binary_multiply, 4116, 4118, 4114);
  g->Dot(1013, 4119, YNN_INVALID_VALUE_ID, 4113, 1);
  g->DequantizeTensor(4113, YNN_INVALID_VALUE_ID, 4114, 4115);
  g->QuantizeTensor(4115, 6434, 4117, 1014);
  g->Dequantize(1014, 1016, 0.030511820688843727, 0);
  g->Transpose(6633, 4124, {1,0});
  g->Binary(ynn_binary_multiply, 4116, 4123, 4121);
  g->Dot(1013, 4124, YNN_INVALID_VALUE_ID, 4120, 1);
  g->DequantizeTensor(4120, YNN_INVALID_VALUE_ID, 4121, 4122);
  g->QuantizeTensor(4122, 6434, 4117, 1017);
  g->Dequantize(1017, 1018, 0.030511820688843727, 0);
  g->Polynomial(1018, 5691, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5691, 5692);
  g->Binary(ynn_binary_add, 5692, 5430, 5689);
  g->Binary(ynn_binary_multiply, 1018, 5428, 5690);
  g->Binary(ynn_binary_multiply, 5690, 5689, 1019);
  g->Binary(ynn_binary_multiply, 1016, 1019, 1020);
  g->Quantize(1020, 1021, 0.02005414292216301, 0);
  g->Transpose(6632, 4131, {1,0});
  g->Binary(ynn_binary_multiply, 4128, 4130, 4126);
  g->Dot(1021, 4131, YNN_INVALID_VALUE_ID, 4125, 1);
  g->DequantizeTensor(4125, YNN_INVALID_VALUE_ID, 4126, 4127);
  g->QuantizeTensor(4127, 6434, 4129, 1022);
  g->Dequantize(1022, 1023, 0.008105741813778877, 0);
  g->Unary(ynn_unary_square, 1023, 1024);
  g->Reduce(ynn_reduce_sum, 1024, 5694, {2}, true);
  g->ShapeProduct(1024, 5693, {2});
  g->Binary(ynn_binary_divide, 5694, 5693, 1026);
  g->Binary(ynn_binary_add, 1026, 6469, 1027);
  g->Unary(ynn_unary_rsqrt, 1027, 1028);
  g->Binary(ynn_binary_multiply, 1023, 1028, 1029);
  g->Binary(ynn_binary_multiply, 1029, 6638, 1030);
  g->Binary(ynn_binary_add, 1030, 1006, 1031);
}

// Scope: "Layer15 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(421, 1032, {0,0,15,0}, {-1,-1,1,-1});
  g->Reshape(1032, 1033, {1,1,256});
  g->Unary(ynn_unary_square, 1033, 1034);
  g->Reduce(ynn_reduce_sum, 1034, 5696, {2}, true);
  g->ShapeProduct(1034, 5695, {2});
  g->Binary(ynn_binary_divide, 5696, 5695, 1035);
  g->Binary(ynn_binary_add, 1035, 6469, 1037);
  g->Unary(ynn_unary_rsqrt, 1037, 1038);
  g->Binary(ynn_binary_multiply, 1033, 1038, 1039);
  g->Binary(ynn_binary_multiply, 1039, 7048, 1040);
  g->Binary(ynn_binary_multiply, 7056, 6472, 1041);
  g->Binary(ynn_binary_add, 1040, 1041, 1042);
  g->Binary(ynn_binary_multiply, 1042, 6466, 1043);
  g->Quantize(1031, 1044, 0.196418896317482, 0);
  g->Transpose(6635, 4138, {1,0});
  g->Binary(ynn_binary_multiply, 4135, 4137, 4133);
  g->Dot(1044, 4138, YNN_INVALID_VALUE_ID, 4132, 1);
  g->DequantizeTensor(4132, YNN_INVALID_VALUE_ID, 4133, 4134);
  g->QuantizeTensor(4134, 6434, 4136, 1045);
  g->Dequantize(1045, 1046, 0.05930119380354881, 0);
  g->Polynomial(1046, 5699, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5699, 5700);
  g->Binary(ynn_binary_add, 5700, 5430, 5697);
  g->Binary(ynn_binary_multiply, 1046, 5428, 5698);
  g->Binary(ynn_binary_multiply, 5698, 5697, 1050);
  g->Binary(ynn_binary_multiply, 1050, 1043, 1051);
  g->Quantize(1051, 1052, 0.6023622155189514, 0);
  g->Transpose(6636, 4145, {1,0});
  g->Binary(ynn_binary_multiply, 4142, 4144, 4140);
  g->Dot(1052, 4145, YNN_INVALID_VALUE_ID, 4139, 1);
  g->DequantizeTensor(4139, YNN_INVALID_VALUE_ID, 4140, 4141);
  g->QuantizeTensor(4141, 6434, 4143, 1053);
  g->Dequantize(1053, 1054, 0.33502069115638733, 0);
  g->Unary(ynn_unary_square, 1054, 1055);
  g->Reduce(ynn_reduce_sum, 1055, 5702, {2}, true);
  g->ShapeProduct(1055, 5701, {2});
  g->Binary(ynn_binary_divide, 5702, 5701, 1056);
  g->Binary(ynn_binary_add, 1056, 6469, 1057);
  g->Unary(ynn_unary_rsqrt, 1057, 1058);
  g->Binary(ynn_binary_multiply, 1054, 1058, 1059);
  g->Binary(ynn_binary_multiply, 1059, 6639, 1061);
  g->Binary(ynn_binary_add, 1031, 1061, 1062);
  g->Binary(ynn_binary_multiply, 1062, 6631, 1063);
}

// Scope: "Layer15"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15(Context& ctx) {
  BuildLayer15Attention(ctx);
  BuildLayer15Mlp(ctx);
  BuildLayer15PerLayerEmbedding(ctx);
}

}  // namespace BuildGemma4DecodeSource
