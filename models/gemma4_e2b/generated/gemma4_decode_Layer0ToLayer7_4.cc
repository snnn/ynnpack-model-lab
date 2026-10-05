// Generated YNNPACK builder; do not edit.
#include "gemma4_decode_builder.h"

namespace BuildGemma4DecodeSource {

// Scope: "Layer0 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer0AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(1048, 1156, 0.6088034510612488, 0);
  g->Transpose(6523, 4253, {1,0});
  g->Binary(ynn_binary_multiply, 4250, 4252, 4248);
  g->Dot(1156, 4253, YNN_INVALID_VALUE_ID, 4247, 1);
  g->DequantizeTensor(4247, YNN_INVALID_VALUE_ID, 4248, 4249);
  g->QuantizeTensor(4249, 6434, 4251, 1265);
  g->Dequantize(1265, 1373, 1.535433053970337, 0);
  g->Reshape(1373, 1482, {1,1,1,256});
  g->Transpose(1482, 1591, {0,2,1,3});
  g->Unary(ynn_unary_square, 1591, 1699);
  g->Reduce(ynn_reduce_sum, 1699, 5925, {3}, true);
  g->ShapeProduct(1699, 5924, {3});
  g->Binary(ynn_binary_divide, 5925, 5924, 1808);
  g->Binary(ynn_binary_add, 1808, 6469, 1917);
  g->Unary(ynn_unary_rsqrt, 1917, 2026);
  g->Binary(ynn_binary_multiply, 1591, 2026, 2134);
  g->Binary(ynn_binary_multiply, 2134, 6522, 2238);
  g->Slice(2238, 2347, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2238, 2456, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2456, 2564);
  g->Concat({2564,2347}, 2673, 3);
  g->Binary(ynn_binary_multiply, 2238, 3009, 2781);
  g->Binary(ynn_binary_multiply, 2673, 3112, 2890);
  g->Binary(ynn_binary_add, 2781, 2890, 2988);
  g->Transpose(6527, 5140, {1,0});
  g->Binary(ynn_binary_multiply, 4250, 5139, 5137);
  g->Dot(1156, 5140, YNN_INVALID_VALUE_ID, 5136, 1);
  g->DequantizeTensor(5136, YNN_INVALID_VALUE_ID, 5137, 5138);
  g->QuantizeTensor(5138, 6434, 4251, 3010);
  g->Dequantize(3010, 3021, 1.535433053970337, 0);
  g->Reshape(3021, 3032, {1,1,1,256});
  g->Transpose(3032, 3042, {0,2,1,3});
  g->Unary(ynn_unary_square, 3042, 3048);
  g->Reduce(ynn_reduce_sum, 3048, 6283, {3}, true);
  g->ShapeProduct(3048, 6282, {3});
  g->Binary(ynn_binary_divide, 6283, 6282, 3059);
  g->Binary(ynn_binary_add, 3059, 6469, 3069);
  g->Unary(ynn_unary_rsqrt, 3069, 3080);
  g->Binary(ynn_binary_multiply, 3042, 3080, 3091);
}

// Scope: "Layer0 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer0AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(2988, 3101, 0.005997600965201855, 0);
  g->Append(6435, 3101, 7085, 2, s2, slinky::expr(int64_t{1}));
  g->View(7085, 7115, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(3091, 3133, 0.047244105488061905, 0);
  g->Append(6450, 3133, 7100, 2, s2, slinky::expr(int64_t{1}));
  g->View(7100, 7130, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer0 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer0AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(6526, 5213, {1,0});
  g->Binary(ynn_binary_multiply, 4250, 5212, 5209);
  g->Dot(1156, 5213, YNN_INVALID_VALUE_ID, 5208, 1);
  g->DequantizeTensor(5208, YNN_INVALID_VALUE_ID, 5209, 5210);
  g->QuantizeTensor(5210, 6434, 5211, 3171);
  g->Dequantize(3171, 3179, 3.118110179901123, 0);
  g->SplitDim(3179, 3190, 2, {8,256});
  g->Transpose(3190, 3200, {0,2,1,3});
  g->Unary(ynn_unary_square, 3200, 3212);
  g->Reduce(ynn_reduce_sum, 3212, 6325, {3}, true);
  g->ShapeProduct(3212, 6324, {3});
  g->Binary(ynn_binary_divide, 6325, 6324, 3222);
  g->Binary(ynn_binary_add, 3222, 6469, 3233);
  g->Unary(ynn_unary_rsqrt, 3233, 3244);
  g->Binary(ynn_binary_multiply, 3200, 3244, 3255);
  g->Binary(ynn_binary_multiply, 3255, 6525, 3266);
  g->Slice(3266, 3277, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3266, 3288, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3288, 3298);
  g->Concat({3298,3277}, 3305, 3);
  g->Binary(ynn_binary_multiply, 3266, 3009, 3316);
  g->Binary(ynn_binary_multiply, 3305, 3112, 3327);
  g->Binary(ynn_binary_add, 3316, 3327, 3337);
}

// Scope: "Layer0 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer0AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7115, 3348, 0.005997600965201855, 0);
  g->Dequantize(7130, 3358, 0.047244105488061905, 0);
  g->Matmul(3337, 3348, 3369, false, true);
  g->Mask(3369, 6475, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6475, 6372, {-1}, true);
  g->Binary(ynn_binary_subtract, 6475, 6372, 6369);
  g->Unary(ynn_unary_exp, 6369, 6370);
  g->Reduce(ynn_reduce_sum, 6370, 6373, {-1}, true);
  g->Binary(ynn_binary_divide, 5430, 6373, 6371);
  g->Binary(ynn_binary_multiply, 6370, 6371, 3390);
  g->Matmul(3390, 3358, 3401, false, false);
}

// Scope: "Layer0 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer0AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(3401, 3412, {0,2,1,3});
  g->FuseDims(3412, 3424, 2, 2);
  g->Quantize(3424, 3434, 0.03026575781404972, 0);
  g->Transpose(6524, 5337, {1,0});
  g->Binary(ynn_binary_multiply, 5334, 5336, 5332);
  g->Dot(3434, 5337, YNN_INVALID_VALUE_ID, 5331, 1);
  g->DequantizeTensor(5331, YNN_INVALID_VALUE_ID, 5332, 5333);
  g->QuantizeTensor(5333, 6434, 5335, 3440);
  g->Dequantize(3440, 3451, 0.21056734025478363, 0);
}

// Scope: "Layer0 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer0Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 0, 524);
  g->Reduce(ynn_reduce_sum, 524, 5586, {2}, true);
  g->ShapeProduct(524, 5585, {2});
  g->Binary(ynn_binary_divide, 5586, 5585, 629);
  g->Binary(ynn_binary_add, 629, 6469, 736);
  g->Unary(ynn_unary_rsqrt, 736, 838);
  g->Binary(ynn_binary_multiply, 0, 838, 938);
  g->Binary(ynn_binary_multiply, 938, 6511, 1048);
  BuildLayer0AttentionKvProjection(ctx);
  BuildLayer0AttentionCacheUpdate(ctx);
  BuildLayer0AttentionQueryProjection(ctx);
  BuildLayer0AttentionSdpa(ctx);
  BuildLayer0AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 3451, 3461);
  g->Reduce(ynn_reduce_sum, 3461, 6392, {2}, true);
  g->ShapeProduct(3461, 6391, {2});
  g->Binary(ynn_binary_divide, 6392, 6391, 3472);
  g->Binary(ynn_binary_add, 3472, 6469, 3483);
  g->Unary(ynn_unary_rsqrt, 3483, 3493);
  g->Binary(ynn_binary_multiply, 3451, 3493, 3504);
  g->Binary(ynn_binary_multiply, 3504, 6518, 3515);
  g->Binary(ynn_binary_add, 3515, 0, 3527);
}

// Scope: "Layer0 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer0Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3527, 3538);
  g->Reduce(ynn_reduce_sum, 3538, 6414, {2}, true);
  g->ShapeProduct(3538, 6413, {2});
  g->Binary(ynn_binary_divide, 6414, 6413, 3549);
  g->Binary(ynn_binary_add, 3549, 6469, 3559);
  g->Unary(ynn_unary_rsqrt, 3559, 3569);
  g->Binary(ynn_binary_multiply, 3527, 3569, 3576);
  g->Binary(ynn_binary_multiply, 3576, 6521, 3587);
  g->Quantize(3587, 3597, 0.9406865835189819, 0);
  g->Transpose(6515, 5405, {1,0});
  g->Binary(ynn_binary_multiply, 3632, 5404, 5402);
  g->Dot(3597, 5405, YNN_INVALID_VALUE_ID, 5401, 1);
  g->DequantizeTensor(5401, YNN_INVALID_VALUE_ID, 5402, 5403);
  g->QuantizeTensor(5403, 6434, 3633, 3608);
  g->Dequantize(3608, 3618, 0.6181102395057678, 0);
  g->Transpose(6514, 3635, {1,0});
  g->Binary(ynn_binary_multiply, 3632, 3634, 3630);
  g->Dot(3597, 3635, YNN_INVALID_VALUE_ID, 3629, 1);
  g->DequantizeTensor(3629, YNN_INVALID_VALUE_ID, 3630, 3631);
  g->QuantizeTensor(3631, 6434, 3633, 13);
  g->Dequantize(13, 24, 0.6181102395057678, 0);
  g->Polynomial(24, 5437, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5437, 5438);
  g->Binary(ynn_binary_add, 5438, 5430, 5435);
  g->Binary(ynn_binary_multiply, 24, 5428, 5436);
  g->Binary(ynn_binary_multiply, 5436, 5435, 35);
  g->Binary(ynn_binary_multiply, 3618, 35, 46);
  g->Quantize(46, 57, 27.842519760131836, 0);
  g->Transpose(6513, 3668, {1,0});
  g->Binary(ynn_binary_multiply, 3665, 3667, 3663);
  g->Dot(57, 3668, YNN_INVALID_VALUE_ID, 3662, 1);
  g->DequantizeTensor(3662, YNN_INVALID_VALUE_ID, 3663, 3664);
  g->QuantizeTensor(3664, 6434, 3666, 67);
  g->Dequantize(67, 75, 16.64207649230957, 0);
  g->Unary(ynn_unary_square, 75, 84);
  g->Reduce(ynn_reduce_sum, 84, 5448, {2}, true);
  g->ShapeProduct(84, 5447, {2});
  g->Binary(ynn_binary_divide, 5448, 5447, 95);
  g->Binary(ynn_binary_add, 95, 6469, 106);
  g->Unary(ynn_unary_rsqrt, 106, 117);
  g->Binary(ynn_binary_multiply, 75, 117, 127);
  g->Binary(ynn_binary_multiply, 127, 6519, 138);
  g->Binary(ynn_binary_add, 138, 3527, 149);
}

// Scope: "Layer0 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer0PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(421, 160, {0,0,0,0}, {-1,-1,1,-1});
  g->Reshape(160, 171, {1,1,256});
  g->Unary(ynn_unary_square, 171, 182);
  g->Reduce(ynn_reduce_sum, 182, 5477, {2}, true);
  g->ShapeProduct(182, 5476, {2});
  g->Binary(ynn_binary_divide, 5477, 5476, 193);
  g->Binary(ynn_binary_add, 193, 6469, 203);
  g->Unary(ynn_unary_rsqrt, 203, 210);
  g->Binary(ynn_binary_multiply, 171, 210, 221);
  g->Binary(ynn_binary_multiply, 221, 7048, 231);
  g->Binary(ynn_binary_multiply, 7049, 6472, 242);
  g->Binary(ynn_binary_add, 231, 242, 253);
  g->Binary(ynn_binary_multiply, 253, 6466, 263);
  g->Quantize(149, 274, 3.334678888320923, 0);
  g->Transpose(6516, 3772, {1,0});
  g->Binary(ynn_binary_multiply, 3769, 3771, 3767);
  g->Dot(274, 3772, YNN_INVALID_VALUE_ID, 3766, 1);
  g->DequantizeTensor(3766, YNN_INVALID_VALUE_ID, 3767, 3768);
  g->QuantizeTensor(3768, 6434, 3770, 285);
  g->Dequantize(285, 296, 0.01857776567339897, 0);
  g->Polynomial(296, 5509, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5509, 5510);
  g->Binary(ynn_binary_add, 5510, 5430, 5507);
  g->Binary(ynn_binary_multiply, 296, 5428, 5508);
  g->Binary(ynn_binary_multiply, 5508, 5507, 307);
  g->Binary(ynn_binary_multiply, 307, 263, 319);
  g->Quantize(319, 329, 0.03764764964580536, 0);
  g->Transpose(6517, 3805, {1,0});
  g->Binary(ynn_binary_multiply, 3802, 3804, 3800);
  g->Dot(329, 3805, YNN_INVALID_VALUE_ID, 3799, 1);
  g->DequantizeTensor(3799, YNN_INVALID_VALUE_ID, 3800, 3801);
  g->QuantizeTensor(3801, 6434, 3803, 340);
  g->Dequantize(340, 346, 0.03129800781607628, 0);
  g->Unary(ynn_unary_square, 346, 357);
  g->Reduce(ynn_reduce_sum, 357, 5523, {2}, true);
  g->ShapeProduct(357, 5522, {2});
  g->Binary(ynn_binary_divide, 5523, 5522, 367);
  g->Binary(ynn_binary_add, 367, 6469, 378);
  g->Unary(ynn_unary_rsqrt, 378, 389);
  g->Binary(ynn_binary_multiply, 346, 389, 399);
  g->Binary(ynn_binary_multiply, 399, 6520, 410);
  g->Binary(ynn_binary_add, 149, 410, 422);
  g->Binary(ynn_binary_multiply, 422, 6512, 433);
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
  g->Quantize(493, 503, 0.4842597544193268, 0);
  g->Transpose(6540, 3883, {1,0});
  g->Binary(ynn_binary_multiply, 3880, 3882, 3878);
  g->Dot(503, 3883, YNN_INVALID_VALUE_ID, 3877, 1);
  g->DequantizeTensor(3877, YNN_INVALID_VALUE_ID, 3878, 3879);
  g->QuantizeTensor(3879, 6434, 3881, 514);
  g->Dequantize(514, 525, 0.41535434126853943, 0);
  g->Reshape(525, 536, {1,1,1,256});
  g->Transpose(536, 547, {0,2,1,3});
  g->Unary(ynn_unary_square, 547, 558);
  g->Reduce(ynn_reduce_sum, 558, 5576, {3}, true);
  g->ShapeProduct(558, 5575, {3});
  g->Binary(ynn_binary_divide, 5576, 5575, 569);
  g->Binary(ynn_binary_add, 569, 6469, 580);
  g->Unary(ynn_unary_rsqrt, 580, 591);
  g->Binary(ynn_binary_multiply, 547, 591, 601);
  g->Binary(ynn_binary_multiply, 601, 6539, 607);
  g->Slice(607, 618, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(607, 630, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 630, 640);
  g->Concat({640,618}, 651, 3);
  g->Binary(ynn_binary_multiply, 607, 3009, 661);
  g->Binary(ynn_binary_multiply, 651, 3112, 672);
  g->Binary(ynn_binary_add, 661, 672, 683);
  g->Transpose(6544, 3978, {1,0});
  g->Binary(ynn_binary_multiply, 3880, 3977, 3975);
  g->Dot(503, 3978, YNN_INVALID_VALUE_ID, 3974, 1);
  g->DequantizeTensor(3974, YNN_INVALID_VALUE_ID, 3975, 3976);
  g->QuantizeTensor(3976, 6434, 3881, 704);
  g->Dequantize(704, 715, 0.41535434126853943, 0);
  g->Reshape(715, 726, {1,1,1,256});
  g->Transpose(726, 737, {0,2,1,3});
  g->Unary(ynn_unary_square, 737, 743);
  g->Reduce(ynn_reduce_sum, 743, 5619, {3}, true);
  g->ShapeProduct(743, 5618, {3});
  g->Binary(ynn_binary_divide, 5619, 5618, 754);
  g->Binary(ynn_binary_add, 754, 6469, 764);
  g->Unary(ynn_unary_rsqrt, 764, 775);
  g->Binary(ynn_binary_multiply, 737, 775, 786);
}

// Scope: "Layer1 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(683, 796, 0.005761673673987389, 0);
  g->Append(6436, 796, 7086, 2, s2, slinky::expr(int64_t{1}));
  g->View(7086, 7116, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(786, 827, 0.047244105488061905, 0);
  g->Append(6451, 827, 7101, 2, s2, slinky::expr(int64_t{1}));
  g->View(7101, 7131, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer1 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(6543, 4053, {1,0});
  g->Binary(ynn_binary_multiply, 3880, 4052, 4049);
  g->Dot(503, 4053, YNN_INVALID_VALUE_ID, 4048, 1);
  g->DequantizeTensor(4048, YNN_INVALID_VALUE_ID, 4049, 4050);
  g->QuantizeTensor(4050, 6434, 4051, 866);
  g->Dequantize(866, 874, 0.35039371252059937, 0);
  g->SplitDim(874, 885, 2, {8,256});
  g->Transpose(885, 895, {0,2,1,3});
  g->Unary(ynn_unary_square, 895, 906);
  g->Reduce(ynn_reduce_sum, 906, 5661, {3}, true);
  g->ShapeProduct(906, 5660, {3});
  g->Binary(ynn_binary_divide, 5661, 5660, 916);
  g->Binary(ynn_binary_add, 916, 6469, 927);
  g->Unary(ynn_unary_rsqrt, 927, 939);
  g->Binary(ynn_binary_multiply, 895, 939, 950);
  g->Binary(ynn_binary_multiply, 950, 6542, 961);
  g->Slice(961, 972, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(961, 983, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 983, 993);
  g->Concat({993,972}, 1004, 3);
  g->Binary(ynn_binary_multiply, 961, 3009, 1015);
  g->Binary(ynn_binary_multiply, 1004, 3112, 1025);
  g->Binary(ynn_binary_add, 1015, 1025, 1036);
}

// Scope: "Layer1 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7116, 1049, 0.005761673673987389, 0);
  g->Dequantize(7131, 1060, 0.047244105488061905, 0);
  g->Matmul(1036, 1049, 1071, false, true);
  g->Mask(1071, 6476, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6476, 5710, {-1}, true);
  g->Binary(ynn_binary_subtract, 6476, 5710, 5707);
  g->Unary(ynn_unary_exp, 5707, 5708);
  g->Reduce(ynn_reduce_sum, 5708, 5711, {-1}, true);
  g->Binary(ynn_binary_divide, 5430, 5711, 5709);
  g->Binary(ynn_binary_multiply, 5708, 5709, 1092);
  g->Matmul(1092, 1060, 1102, false, false);
}

// Scope: "Layer1 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1102, 1113, {0,2,1,3});
  g->FuseDims(1113, 1123, 2, 2);
  g->Quantize(1123, 1134, 0.023129930719733238, 0);
  g->Transpose(6541, 4185, {1,0});
  g->Binary(ynn_binary_multiply, 4182, 4184, 4180);
  g->Dot(1134, 4185, YNN_INVALID_VALUE_ID, 4179, 1);
  g->DequantizeTensor(4179, YNN_INVALID_VALUE_ID, 4180, 4181);
  g->QuantizeTensor(4181, 6434, 4183, 1145);
  g->Dequantize(1145, 1157, 0.03322756290435791, 0);
}

// Scope: "Layer1 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 433, 444);
  g->Reduce(ynn_reduce_sum, 444, 5547, {2}, true);
  g->ShapeProduct(444, 5546, {2});
  g->Binary(ynn_binary_divide, 5547, 5546, 455);
  g->Binary(ynn_binary_add, 455, 6469, 465);
  g->Unary(ynn_unary_rsqrt, 465, 474);
  g->Binary(ynn_binary_multiply, 433, 474, 482);
  g->Binary(ynn_binary_multiply, 482, 6528, 493);
  BuildLayer1AttentionKvProjection(ctx);
  BuildLayer1AttentionCacheUpdate(ctx);
  BuildLayer1AttentionQueryProjection(ctx);
  BuildLayer1AttentionSdpa(ctx);
  BuildLayer1AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1157, 1168);
  g->Reduce(ynn_reduce_sum, 1168, 5740, {2}, true);
  g->ShapeProduct(1168, 5739, {2});
  g->Binary(ynn_binary_divide, 5740, 5739, 1179);
  g->Binary(ynn_binary_add, 1179, 6469, 1190);
  g->Unary(ynn_unary_rsqrt, 1190, 1200);
  g->Binary(ynn_binary_multiply, 1157, 1200, 1211);
  g->Binary(ynn_binary_multiply, 1211, 6535, 1221);
  g->Binary(ynn_binary_add, 1221, 433, 1232);
}

// Scope: "Layer1 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1232, 1243);
  g->Reduce(ynn_reduce_sum, 1243, 5763, {2}, true);
  g->ShapeProduct(1243, 5762, {2});
  g->Binary(ynn_binary_divide, 5763, 5762, 1254);
  g->Binary(ynn_binary_add, 1254, 6469, 1266);
  g->Unary(ynn_unary_rsqrt, 1266, 1277);
  g->Binary(ynn_binary_multiply, 1232, 1277, 1288);
  g->Binary(ynn_binary_multiply, 1288, 6538, 1298);
  g->Quantize(1298, 1309, 0.08275254815816879, 0);
  g->Transpose(6532, 4281, {1,0});
  g->Binary(ynn_binary_multiply, 4278, 4280, 4276);
  g->Dot(1309, 4281, YNN_INVALID_VALUE_ID, 4275, 1);
  g->DequantizeTensor(4275, YNN_INVALID_VALUE_ID, 4276, 4277);
  g->QuantizeTensor(4277, 6434, 4279, 1320);
  g->Dequantize(1320, 1330, 0.06889764219522476, 0);
  g->Transpose(6531, 4305, {1,0});
  g->Binary(ynn_binary_multiply, 4278, 4304, 4302);
  g->Dot(1309, 4305, YNN_INVALID_VALUE_ID, 4301, 1);
  g->DequantizeTensor(4301, YNN_INVALID_VALUE_ID, 4302, 4303);
  g->QuantizeTensor(4303, 6434, 4279, 1351);
  g->Dequantize(1351, 1362, 0.06889764219522476, 0);
  g->Polynomial(1362, 5797, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5797, 5798);
  g->Binary(ynn_binary_add, 5798, 5430, 5795);
  g->Binary(ynn_binary_multiply, 1362, 5428, 5796);
  g->Binary(ynn_binary_multiply, 5796, 5795, 1374);
  g->Binary(ynn_binary_multiply, 1330, 1374, 1385);
  g->Quantize(1385, 1395, 0.21062994003295898, 0);
  g->Transpose(6530, 4333, {1,0});
  g->Binary(ynn_binary_multiply, 4330, 4332, 4328);
  g->Dot(1395, 4333, YNN_INVALID_VALUE_ID, 4327, 1);
  g->DequantizeTensor(4327, YNN_INVALID_VALUE_ID, 4328, 4329);
  g->QuantizeTensor(4329, 6434, 4331, 1406);
  g->Dequantize(1406, 1417, 0.09257561713457108, 0);
  g->Unary(ynn_unary_square, 1417, 1427);
  g->Reduce(ynn_reduce_sum, 1427, 5817, {2}, true);
  g->ShapeProduct(1427, 5816, {2});
  g->Binary(ynn_binary_divide, 5817, 5816, 1438);
  g->Binary(ynn_binary_add, 1438, 6469, 1449);
  g->Unary(ynn_unary_rsqrt, 1449, 1460);
  g->Binary(ynn_binary_multiply, 1417, 1460, 1471);
  g->Binary(ynn_binary_multiply, 1471, 6536, 1483);
  g->Binary(ynn_binary_add, 1483, 1232, 1494);
}

// Scope: "Layer1 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(421, 1504, {0,0,1,0}, {-1,-1,1,-1});
  g->Reshape(1504, 1515, {1,1,256});
  g->Unary(ynn_unary_square, 1515, 1525);
  g->Reduce(ynn_reduce_sum, 1525, 5846, {2}, true);
  g->ShapeProduct(1525, 5845, {2});
  g->Binary(ynn_binary_divide, 5846, 5845, 1536);
  g->Binary(ynn_binary_add, 1536, 6469, 1547);
  g->Unary(ynn_unary_rsqrt, 1547, 1558);
  g->Binary(ynn_binary_multiply, 1515, 1558, 1569);
  g->Binary(ynn_binary_multiply, 1569, 7048, 1580);
  g->Binary(ynn_binary_multiply, 7050, 6472, 1592);
  g->Binary(ynn_binary_add, 1580, 1592, 1602);
  g->Binary(ynn_binary_multiply, 1602, 6466, 1613);
  g->Quantize(1494, 1623, 0.4206320643424988, 0);
  g->Transpose(6533, 4450, {1,0});
  g->Binary(ynn_binary_multiply, 4447, 4449, 4445);
  g->Dot(1623, 4450, YNN_INVALID_VALUE_ID, 4444, 1);
  g->DequantizeTensor(4444, YNN_INVALID_VALUE_ID, 4445, 4446);
  g->QuantizeTensor(4446, 6434, 4448, 1634);
  g->Dequantize(1634, 1645, 0.010150108486413956, 0);
  g->Polynomial(1645, 5882, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5882, 5883);
  g->Binary(ynn_binary_add, 5883, 5430, 5880);
  g->Binary(ynn_binary_multiply, 1645, 5428, 5881);
  g->Binary(ynn_binary_multiply, 5881, 5880, 1656);
  g->Binary(ynn_binary_multiply, 1656, 1613, 1667);
  g->Quantize(1667, 1678, 0.026820875704288483, 0);
  g->Transpose(6534, 4478, {1,0});
  g->Binary(ynn_binary_multiply, 4475, 4477, 4473);
  g->Dot(1678, 4478, YNN_INVALID_VALUE_ID, 4472, 1);
  g->DequantizeTensor(4472, YNN_INVALID_VALUE_ID, 4473, 4474);
  g->QuantizeTensor(4474, 6434, 4476, 1689);
  g->Dequantize(1689, 1700, 0.020895034074783325, 0);
  g->Unary(ynn_unary_square, 1700, 1711);
  g->Reduce(ynn_reduce_sum, 1711, 5900, {2}, true);
  g->ShapeProduct(1711, 5899, {2});
  g->Binary(ynn_binary_divide, 5900, 5899, 1722);
  g->Binary(ynn_binary_add, 1722, 6469, 1732);
  g->Unary(ynn_unary_rsqrt, 1732, 1743);
  g->Binary(ynn_binary_multiply, 1700, 1743, 1754);
  g->Binary(ynn_binary_multiply, 1754, 6537, 1765);
  g->Binary(ynn_binary_add, 1494, 1765, 1776);
  g->Binary(ynn_binary_multiply, 1776, 6529, 1787);
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
  g->Quantize(1852, 1863, 0.15746013820171356, 0);
  g->Transpose(6712, 4571, {1,0});
  g->Binary(ynn_binary_multiply, 4568, 4570, 4566);
  g->Dot(1863, 4571, YNN_INVALID_VALUE_ID, 4565, 1);
  g->DequantizeTensor(4565, YNN_INVALID_VALUE_ID, 4566, 4567);
  g->QuantizeTensor(4567, 6434, 4569, 1874);
  g->Dequantize(1874, 1885, 0.180118128657341, 0);
  g->Reshape(1885, 1896, {1,1,1,256});
  g->Transpose(1896, 1906, {0,2,1,3});
  g->Unary(ynn_unary_square, 1906, 1918);
  g->Reduce(ynn_reduce_sum, 1918, 5960, {3}, true);
  g->ShapeProduct(1918, 5959, {3});
  g->Binary(ynn_binary_divide, 5960, 5959, 1928);
  g->Binary(ynn_binary_add, 1928, 6469, 1939);
  g->Unary(ynn_unary_rsqrt, 1939, 1950);
  g->Binary(ynn_binary_multiply, 1906, 1950, 1961);
  g->Binary(ynn_binary_multiply, 1961, 6711, 1972);
  g->Slice(1972, 1983, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1972, 1994, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1994, 2004);
  g->Concat({2004,1983}, 2015, 3);
  g->Binary(ynn_binary_multiply, 1972, 3009, 2027);
  g->Binary(ynn_binary_multiply, 2015, 3112, 2037);
  g->Binary(ynn_binary_add, 2027, 2037, 2048);
  g->Transpose(6716, 4667, {1,0});
  g->Binary(ynn_binary_multiply, 4568, 4666, 4664);
  g->Dot(1863, 4667, YNN_INVALID_VALUE_ID, 4663, 1);
  g->DequantizeTensor(4663, YNN_INVALID_VALUE_ID, 4664, 4665);
  g->QuantizeTensor(4665, 6434, 4569, 2069);
  g->Dequantize(2069, 2080, 0.180118128657341, 0);
  g->Reshape(2080, 2091, {1,1,1,256});
  g->Transpose(2091, 2102, {0,2,1,3});
  g->Unary(ynn_unary_square, 2102, 2112);
  g->Reduce(ynn_reduce_sum, 2112, 6016, {3}, true);
  g->ShapeProduct(2112, 6015, {3});
  g->Binary(ynn_binary_divide, 6016, 6015, 2123);
  g->Binary(ynn_binary_add, 2123, 6469, 2135);
  g->Unary(ynn_unary_rsqrt, 2135, 2146);
  g->Binary(ynn_binary_multiply, 2102, 2146, 2157);
}

// Scope: "Layer2 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(2048, 2168, 0.005684707313776016, 0);
  g->Append(6442, 2168, 7092, 2, s2, slinky::expr(int64_t{1}));
  g->View(7092, 7122, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(2157, 2199, 0.047244105488061905, 0);
  g->Append(6457, 2199, 7107, 2, s2, slinky::expr(int64_t{1}));
  g->View(7107, 7137, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer2 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(6715, 4752, {1,0});
  g->Binary(ynn_binary_multiply, 4568, 4751, 4748);
  g->Dot(1863, 4752, YNN_INVALID_VALUE_ID, 4747, 1);
  g->DequantizeTensor(4747, YNN_INVALID_VALUE_ID, 4748, 4749);
  g->QuantizeTensor(4749, 6434, 4750, 2239);
  g->Dequantize(2239, 2250, 0.1643700897693634, 0);
  g->SplitDim(2250, 2261, 2, {8,256});
  g->Transpose(2261, 2272, {0,2,1,3});
  g->Unary(ynn_unary_square, 2272, 2283);
  g->Reduce(ynn_reduce_sum, 2283, 6063, {3}, true);
  g->ShapeProduct(2283, 6062, {3});
  g->Binary(ynn_binary_divide, 6063, 6062, 2294);
  g->Binary(ynn_binary_add, 2294, 6469, 2304);
  g->Unary(ynn_unary_rsqrt, 2304, 2315);
  g->Binary(ynn_binary_multiply, 2272, 2315, 2326);
  g->Binary(ynn_binary_multiply, 2326, 6714, 2336);
  g->Slice(2336, 2348, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2336, 2359, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2359, 2370);
  g->Concat({2370,2348}, 2381, 3);
  g->Binary(ynn_binary_multiply, 2336, 3009, 2392);
  g->Binary(ynn_binary_multiply, 2381, 3112, 2402);
  g->Binary(ynn_binary_add, 2392, 2402, 2413);
}

// Scope: "Layer2 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7122, 2424, 0.005684707313776016, 0);
  g->Dequantize(7137, 2434, 0.047244105488061905, 0);
  g->Matmul(2413, 2424, 2445, false, true);
  g->Mask(2445, 6487, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6487, 6117, {-1}, true);
  g->Binary(ynn_binary_subtract, 6487, 6117, 6114);
  g->Unary(ynn_unary_exp, 6114, 6115);
  g->Reduce(ynn_reduce_sum, 6115, 6118, {-1}, true);
  g->Binary(ynn_binary_divide, 5430, 6118, 6116);
  g->Binary(ynn_binary_multiply, 6115, 6116, 2467);
  g->Matmul(2467, 2434, 2478, false, false);
}

// Scope: "Layer2 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(2478, 2489, {0,2,1,3});
  g->FuseDims(2489, 2500, 2, 2);
  g->Quantize(2500, 2510, 0.0216535534709692, 0);
  g->Transpose(6713, 4878, {1,0});
  g->Binary(ynn_binary_multiply, 4875, 4877, 4873);
  g->Dot(2510, 4878, YNN_INVALID_VALUE_ID, 4872, 1);
  g->DequantizeTensor(4872, YNN_INVALID_VALUE_ID, 4873, 4874);
  g->QuantizeTensor(4874, 6434, 4876, 2521);
  g->Dequantize(2521, 2531, 0.03426840156316757, 0);
}

// Scope: "Layer2 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1787, 1798);
  g->Reduce(ynn_reduce_sum, 1798, 5927, {2}, true);
  g->ShapeProduct(1798, 5926, {2});
  g->Binary(ynn_binary_divide, 5927, 5926, 1809);
  g->Binary(ynn_binary_add, 1809, 6469, 1820);
  g->Unary(ynn_unary_rsqrt, 1820, 1830);
  g->Binary(ynn_binary_multiply, 1787, 1830, 1841);
  g->Binary(ynn_binary_multiply, 1841, 6700, 1852);
  BuildLayer2AttentionKvProjection(ctx);
  BuildLayer2AttentionCacheUpdate(ctx);
  BuildLayer2AttentionQueryProjection(ctx);
  BuildLayer2AttentionSdpa(ctx);
  BuildLayer2AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2531, 2542);
  g->Reduce(ynn_reduce_sum, 2542, 6141, {2}, true);
  g->ShapeProduct(2542, 6140, {2});
  g->Binary(ynn_binary_divide, 6141, 6140, 2553);
  g->Binary(ynn_binary_add, 2553, 6469, 2565);
  g->Unary(ynn_unary_rsqrt, 2565, 2576);
  g->Binary(ynn_binary_multiply, 2531, 2576, 2587);
  g->Binary(ynn_binary_multiply, 2587, 6707, 2598);
  g->Binary(ynn_binary_add, 2598, 1787, 2608);
}

// Scope: "Layer2 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2608, 2619);
  g->Reduce(ynn_reduce_sum, 2619, 6162, {2}, true);
  g->ShapeProduct(2619, 6161, {2});
  g->Binary(ynn_binary_divide, 6162, 6161, 2629);
  g->Binary(ynn_binary_add, 2629, 6469, 2640);
  g->Unary(ynn_unary_rsqrt, 2640, 2651);
  g->Binary(ynn_binary_multiply, 2608, 2651, 2662);
  g->Binary(ynn_binary_multiply, 2662, 6710, 2674);
  g->Quantize(2674, 2685, 0.04049227386713028, 0);
  g->Transpose(6704, 4969, {1,0});
  g->Binary(ynn_binary_multiply, 4966, 4968, 4964);
  g->Dot(2685, 4969, YNN_INVALID_VALUE_ID, 4963, 1);
  g->DequantizeTensor(4963, YNN_INVALID_VALUE_ID, 4964, 4965);
  g->QuantizeTensor(4965, 6434, 4967, 2696);
  g->Dequantize(2696, 2706, 0.04183071851730347, 0);
  g->Transpose(6703, 4980, {1,0});
  g->Binary(ynn_binary_multiply, 4966, 4979, 4977);
  g->Dot(2685, 4980, YNN_INVALID_VALUE_ID, 4976, 1);
  g->DequantizeTensor(4976, YNN_INVALID_VALUE_ID, 4977, 4978);
  g->QuantizeTensor(4978, 6434, 4967, 2727);
  g->Dequantize(2727, 2737, 0.04183071851730347, 0);
  g->Polynomial(2737, 6198, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6198, 6199);
  g->Binary(ynn_binary_add, 6199, 5430, 6196);
  g->Binary(ynn_binary_multiply, 2737, 5428, 6197);
  g->Binary(ynn_binary_multiply, 6197, 6196, 2748);
  g->Binary(ynn_binary_multiply, 2706, 2748, 2759);
  g->Quantize(2759, 2770, 0.09645669907331467, 0);
  g->Transpose(6702, 5017, {1,0});
  g->Binary(ynn_binary_multiply, 5014, 5016, 5012);
  g->Dot(2770, 5017, YNN_INVALID_VALUE_ID, 5011, 1);
  g->DequantizeTensor(5011, YNN_INVALID_VALUE_ID, 5012, 5013);
  g->QuantizeTensor(5013, 6434, 5015, 2782);
  g->Dequantize(2782, 2793, 0.05011765658855438, 0);
  g->Unary(ynn_unary_square, 2793, 2804);
  g->Reduce(ynn_reduce_sum, 2804, 6218, {2}, true);
  g->ShapeProduct(2804, 6217, {2});
  g->Binary(ynn_binary_divide, 6218, 6217, 2814);
  g->Binary(ynn_binary_add, 2814, 6469, 2825);
  g->Unary(ynn_unary_rsqrt, 2825, 2835);
  g->Binary(ynn_binary_multiply, 2793, 2835, 2846);
  g->Binary(ynn_binary_multiply, 2846, 6708, 2857);
  g->Binary(ynn_binary_add, 2857, 2608, 2868);
}

// Scope: "Layer2 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(421, 2879, {0,0,2,0}, {-1,-1,1,-1});
  g->Reshape(2879, 2891, {1,1,256});
  g->Unary(ynn_unary_square, 2891, 2902);
  g->Reduce(ynn_reduce_sum, 2902, 6247, {2}, true);
  g->ShapeProduct(2902, 6246, {2});
  g->Binary(ynn_binary_divide, 6247, 6246, 2912);
  g->Binary(ynn_binary_add, 2912, 6469, 2923);
  g->Unary(ynn_unary_rsqrt, 2923, 2933);
  g->Binary(ynn_binary_multiply, 2891, 2933, 2944);
  g->Binary(ynn_binary_multiply, 2944, 7048, 2955);
  g->Binary(ynn_binary_multiply, 7061, 6472, 2966);
  g->Binary(ynn_binary_add, 2955, 2966, 2977);
  g->Binary(ynn_binary_multiply, 2977, 6466, 2987);
  g->Quantize(2868, 2989, 0.045230474323034286, 0);
  g->Transpose(6705, 5128, {1,0});
  g->Binary(ynn_binary_multiply, 5125, 5127, 5123);
  g->Dot(2989, 5128, YNN_INVALID_VALUE_ID, 5122, 1);
  g->DequantizeTensor(5122, YNN_INVALID_VALUE_ID, 5123, 5124);
  g->QuantizeTensor(5124, 6434, 5126, 2990);
  g->Dequantize(2990, 2991, 0.017839577049016953, 0);
  g->Polynomial(2991, 6270, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6270, 6271);
  g->Binary(ynn_binary_add, 6271, 5430, 6268);
  g->Binary(ynn_binary_multiply, 2991, 5428, 6269);
  g->Binary(ynn_binary_multiply, 6269, 6268, 2992);
  g->Binary(ynn_binary_multiply, 2992, 2987, 2993);
  g->Quantize(2993, 2994, 0.05216536670923233, 0);
  g->Transpose(6706, 5135, {1,0});
  g->Binary(ynn_binary_multiply, 5132, 5134, 5130);
  g->Dot(2994, 5135, YNN_INVALID_VALUE_ID, 5129, 1);
  g->DequantizeTensor(5129, YNN_INVALID_VALUE_ID, 5130, 5131);
  g->QuantizeTensor(5131, 6434, 5133, 2995);
  g->Dequantize(2995, 2996, 0.021943029016256332, 0);
  g->Unary(ynn_unary_square, 2996, 2997);
  g->Reduce(ynn_reduce_sum, 2997, 6273, {2}, true);
  g->ShapeProduct(2997, 6272, {2});
  g->Binary(ynn_binary_divide, 6273, 6272, 2998);
  g->Binary(ynn_binary_add, 2998, 6469, 2999);
  g->Unary(ynn_unary_rsqrt, 2999, 3000);
  g->Binary(ynn_binary_multiply, 2996, 3000, 3001);
  g->Binary(ynn_binary_multiply, 3001, 6709, 3002);
  g->Binary(ynn_binary_add, 2868, 3002, 3003);
  g->Binary(ynn_binary_multiply, 3003, 6701, 3004);
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
  g->Quantize(3012, 3013, 0.12591414153575897, 0);
  g->Transpose(6869, 5146, {1,0});
  g->Binary(ynn_binary_multiply, 5144, 5145, 5142);
  g->Dot(3013, 5146, YNN_INVALID_VALUE_ID, 5141, 1);
  g->DequantizeTensor(5141, YNN_INVALID_VALUE_ID, 5142, 5143);
  g->QuantizeTensor(5143, 6434, 4608, 3014);
  g->Dequantize(3014, 3015, 0.08710630983114243, 0);
  g->Reshape(3015, 3016, {1,1,1,256});
  g->Transpose(3016, 3017, {0,2,1,3});
  g->Unary(ynn_unary_square, 3017, 3018);
  g->Reduce(ynn_reduce_sum, 3018, 6277, {3}, true);
  g->ShapeProduct(3018, 6276, {3});
  g->Binary(ynn_binary_divide, 6277, 6276, 3019);
  g->Binary(ynn_binary_add, 3019, 6469, 3020);
  g->Unary(ynn_unary_rsqrt, 3020, 3022);
  g->Binary(ynn_binary_multiply, 3017, 3022, 3023);
  g->Binary(ynn_binary_multiply, 3023, 6868, 3024);
  g->Slice(3024, 3025, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3024, 3026, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3026, 3027);
  g->Concat({3027,3025}, 3028, 3);
  g->Binary(ynn_binary_multiply, 3024, 3009, 3029);
  g->Binary(ynn_binary_multiply, 3028, 3112, 3030);
  g->Binary(ynn_binary_add, 3029, 3030, 3031);
  g->Transpose(6873, 5151, {1,0});
  g->Binary(ynn_binary_multiply, 5144, 5150, 5148);
  g->Dot(3013, 5151, YNN_INVALID_VALUE_ID, 5147, 1);
  g->DequantizeTensor(5147, YNN_INVALID_VALUE_ID, 5148, 5149);
  g->QuantizeTensor(5149, 6434, 4608, 3033);
  g->Dequantize(3033, 3034, 0.08710630983114243, 0);
  g->Reshape(3034, 3035, {1,1,1,256});
  g->Transpose(3035, 3036, {0,2,1,3});
  g->Unary(ynn_unary_square, 3036, 3037);
  g->Reduce(ynn_reduce_sum, 3037, 6279, {3}, true);
  g->ShapeProduct(3037, 6278, {3});
  g->Binary(ynn_binary_divide, 6279, 6278, 3038);
  g->Binary(ynn_binary_add, 3038, 6469, 3039);
  g->Unary(ynn_unary_rsqrt, 3039, 3040);
  g->Binary(ynn_binary_multiply, 3036, 3040, 3041);
}

// Scope: "Layer3 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(3031, 3043, 0.00573749840259552, 0);
  g->Append(6443, 3043, 7093, 2, s2, slinky::expr(int64_t{1}));
  g->View(7093, 7123, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(3041, 3044, 0.047244105488061905, 0);
  g->Append(6458, 3044, 7108, 2, s2, slinky::expr(int64_t{1}));
  g->View(7108, 7138, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer3 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(6872, 5157, {1,0});
  g->Binary(ynn_binary_multiply, 5144, 5156, 5153);
  g->Dot(3013, 5157, YNN_INVALID_VALUE_ID, 5152, 1);
  g->DequantizeTensor(5152, YNN_INVALID_VALUE_ID, 5153, 5154);
  g->QuantizeTensor(5154, 6434, 5155, 3045);
  g->Dequantize(3045, 3046, 0.15354332327842712, 0);
  g->SplitDim(3046, 3047, 2, {8,256});
  g->Transpose(3047, 3049, {0,2,1,3});
  g->Unary(ynn_unary_square, 3049, 3050);
  g->Reduce(ynn_reduce_sum, 3050, 6281, {3}, true);
  g->ShapeProduct(3050, 6280, {3});
  g->Binary(ynn_binary_divide, 6281, 6280, 3051);
  g->Binary(ynn_binary_add, 3051, 6469, 3052);
  g->Unary(ynn_unary_rsqrt, 3052, 3053);
  g->Binary(ynn_binary_multiply, 3049, 3053, 3054);
  g->Binary(ynn_binary_multiply, 3054, 6871, 3055);
  g->Slice(3055, 3056, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3055, 3057, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3057, 3058);
  g->Concat({3058,3056}, 3060, 3);
  g->Binary(ynn_binary_multiply, 3055, 3009, 3061);
  g->Binary(ynn_binary_multiply, 3060, 3112, 3062);
  g->Binary(ynn_binary_add, 3061, 3062, 3063);
}

// Scope: "Layer3 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7123, 3064, 0.00573749840259552, 0);
  g->Dequantize(7138, 3065, 0.047244105488061905, 0);
  g->Matmul(3063, 3064, 3066, false, true);
  g->Mask(3066, 6498, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6498, 6287, {-1}, true);
  g->Binary(ynn_binary_subtract, 6498, 6287, 6284);
  g->Unary(ynn_unary_exp, 6284, 6285);
  g->Reduce(ynn_reduce_sum, 6285, 6288, {-1}, true);
  g->Binary(ynn_binary_divide, 5430, 6288, 6286);
  g->Binary(ynn_binary_multiply, 6285, 6286, 3067);
  g->Matmul(3067, 3065, 3068, false, false);
}

// Scope: "Layer3 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(3068, 3070, {0,2,1,3});
  g->FuseDims(3070, 3071, 2, 2);
  g->Quantize(3071, 3072, 0.02706693857908249, 0);
  g->Transpose(6870, 5164, {1,0});
  g->Binary(ynn_binary_multiply, 5161, 5163, 5159);
  g->Dot(3072, 5164, YNN_INVALID_VALUE_ID, 5158, 1);
  g->DequantizeTensor(5158, YNN_INVALID_VALUE_ID, 5159, 5160);
  g->QuantizeTensor(5160, 6434, 5162, 3073);
  g->Dequantize(3073, 3074, 0.07367152720689774, 0);
}

// Scope: "Layer3 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3004, 3005);
  g->Reduce(ynn_reduce_sum, 3005, 6275, {2}, true);
  g->ShapeProduct(3005, 6274, {2});
  g->Binary(ynn_binary_divide, 6275, 6274, 3006);
  g->Binary(ynn_binary_add, 3006, 6469, 3007);
  g->Unary(ynn_unary_rsqrt, 3007, 3008);
  g->Binary(ynn_binary_multiply, 3004, 3008, 3011);
  g->Binary(ynn_binary_multiply, 3011, 6857, 3012);
  BuildLayer3AttentionKvProjection(ctx);
  BuildLayer3AttentionCacheUpdate(ctx);
  BuildLayer3AttentionQueryProjection(ctx);
  BuildLayer3AttentionSdpa(ctx);
  BuildLayer3AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 3074, 3075);
  g->Reduce(ynn_reduce_sum, 3075, 6290, {2}, true);
  g->ShapeProduct(3075, 6289, {2});
  g->Binary(ynn_binary_divide, 6290, 6289, 3076);
  g->Binary(ynn_binary_add, 3076, 6469, 3077);
  g->Unary(ynn_unary_rsqrt, 3077, 3078);
  g->Binary(ynn_binary_multiply, 3074, 3078, 3079);
  g->Binary(ynn_binary_multiply, 3079, 6864, 3081);
  g->Binary(ynn_binary_add, 3081, 3004, 3082);
}

// Scope: "Layer3 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3082, 3083);
  g->Reduce(ynn_reduce_sum, 3083, 6292, {2}, true);
  g->ShapeProduct(3083, 6291, {2});
  g->Binary(ynn_binary_divide, 6292, 6291, 3084);
  g->Binary(ynn_binary_add, 3084, 6469, 3085);
  g->Unary(ynn_unary_rsqrt, 3085, 3086);
  g->Binary(ynn_binary_multiply, 3082, 3086, 3087);
  g->Binary(ynn_binary_multiply, 3087, 6867, 3088);
  g->Quantize(3088, 3089, 0.019482526928186417, 0);
  g->Transpose(6861, 5170, {1,0});
  g->Binary(ynn_binary_multiply, 5168, 5169, 5166);
  g->Dot(3089, 5170, YNN_INVALID_VALUE_ID, 5165, 1);
  g->DequantizeTensor(5165, YNN_INVALID_VALUE_ID, 5166, 5167);
  g->QuantizeTensor(5167, 6434, 4128, 3090);
  g->Dequantize(3090, 3092, 0.02005414292216301, 0);
  g->Transpose(6860, 5175, {1,0});
  g->Binary(ynn_binary_multiply, 5168, 5174, 5172);
  g->Dot(3089, 5175, YNN_INVALID_VALUE_ID, 5171, 1);
  g->DequantizeTensor(5171, YNN_INVALID_VALUE_ID, 5172, 5173);
  g->QuantizeTensor(5173, 6434, 4128, 3093);
  g->Dequantize(3093, 3094, 0.02005414292216301, 0);
  g->Polynomial(3094, 6295, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6295, 6296);
  g->Binary(ynn_binary_add, 6296, 5430, 6293);
  g->Binary(ynn_binary_multiply, 3094, 5428, 6294);
  g->Binary(ynn_binary_multiply, 6294, 6293, 3095);
  g->Binary(ynn_binary_multiply, 3092, 3095, 3096);
  g->Quantize(3096, 3097, 0.03297245129942894, 0);
  g->Transpose(6859, 5181, {1,0});
  g->Binary(ynn_binary_multiply, 4290, 5180, 5177);
  g->Dot(3097, 5181, YNN_INVALID_VALUE_ID, 5176, 1);
  g->DequantizeTensor(5176, YNN_INVALID_VALUE_ID, 5177, 5178);
  g->QuantizeTensor(5178, 6434, 5179, 3098);
  g->Dequantize(3098, 3099, 0.022154856473207474, 0);
  g->Unary(ynn_unary_square, 3099, 3100);
  g->Reduce(ynn_reduce_sum, 3100, 6298, {2}, true);
  g->ShapeProduct(3100, 6297, {2});
  g->Binary(ynn_binary_divide, 6298, 6297, 3102);
  g->Binary(ynn_binary_add, 3102, 6469, 3103);
  g->Unary(ynn_unary_rsqrt, 3103, 3104);
  g->Binary(ynn_binary_multiply, 3099, 3104, 3105);
  g->Binary(ynn_binary_multiply, 3105, 6865, 3106);
  g->Binary(ynn_binary_add, 3106, 3082, 3107);
}

// Scope: "Layer3 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(421, 3108, {0,0,3,0}, {-1,-1,1,-1});
  g->Reshape(3108, 3109, {1,1,256});
  g->Unary(ynn_unary_square, 3109, 3110);
  g->Reduce(ynn_reduce_sum, 3110, 6300, {2}, true);
  g->ShapeProduct(3110, 6299, {2});
  g->Binary(ynn_binary_divide, 6300, 6299, 3111);
  g->Binary(ynn_binary_add, 3111, 6469, 3113);
  g->Unary(ynn_unary_rsqrt, 3113, 3114);
  g->Binary(ynn_binary_multiply, 3109, 3114, 3115);
  g->Binary(ynn_binary_multiply, 3115, 7048, 3116);
  g->Binary(ynn_binary_multiply, 7072, 6472, 3117);
  g->Binary(ynn_binary_add, 3116, 3117, 3118);
  g->Binary(ynn_binary_multiply, 3118, 6466, 3119);
  g->Quantize(3107, 3120, 0.2861534655094147, 0);
  g->Transpose(6862, 5188, {1,0});
  g->Binary(ynn_binary_multiply, 5185, 5187, 5183);
  g->Dot(3120, 5188, YNN_INVALID_VALUE_ID, 5182, 1);
  g->DequantizeTensor(5182, YNN_INVALID_VALUE_ID, 5183, 5184);
  g->QuantizeTensor(5184, 6434, 5186, 3121);
  g->Dequantize(3121, 3122, 0.050688985735177994, 0);
  g->Polynomial(3122, 6303, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6303, 6304);
  g->Binary(ynn_binary_add, 6304, 5430, 6301);
  g->Binary(ynn_binary_multiply, 3122, 5428, 6302);
  g->Binary(ynn_binary_multiply, 6302, 6301, 3123);
  g->Binary(ynn_binary_multiply, 3123, 3119, 3124);
  g->Quantize(3124, 3125, 0.06692913919687271, 0);
  g->Transpose(6863, 5195, {1,0});
  g->Binary(ynn_binary_multiply, 5192, 5194, 5190);
  g->Dot(3125, 5195, YNN_INVALID_VALUE_ID, 5189, 1);
  g->DequantizeTensor(5189, YNN_INVALID_VALUE_ID, 5190, 5191);
  g->QuantizeTensor(5191, 6434, 5193, 3126);
  g->Dequantize(3126, 3127, 0.0805763527750969, 0);
  g->Unary(ynn_unary_square, 3127, 3128);
  g->Reduce(ynn_reduce_sum, 3128, 6306, {2}, true);
  g->ShapeProduct(3128, 6305, {2});
  g->Binary(ynn_binary_divide, 6306, 6305, 3129);
  g->Binary(ynn_binary_add, 3129, 6469, 3130);
  g->Unary(ynn_unary_rsqrt, 3130, 3131);
  g->Binary(ynn_binary_multiply, 3127, 3131, 3132);
  g->Binary(ynn_binary_multiply, 3132, 6866, 3134);
  g->Binary(ynn_binary_add, 3107, 3134, 3135);
  g->Binary(ynn_binary_multiply, 3135, 6858, 3136);
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
  g->Quantize(3142, 3143, 0.023374712094664574, 0);
  g->Transpose(6956, 5202, {1,0});
  g->Binary(ynn_binary_multiply, 5199, 5201, 5197);
  g->Dot(3143, 5202, YNN_INVALID_VALUE_ID, 5196, 1);
  g->DequantizeTensor(5196, YNN_INVALID_VALUE_ID, 5197, 5198);
  g->QuantizeTensor(5198, 6434, 5200, 3144);
  g->Dequantize(3144, 3145, 0.024852370843291283, 0);
  g->Reshape(3145, 3146, {1,1,1,512});
  g->Transpose(3146, 3147, {0,2,1,3});
  g->Unary(ynn_unary_square, 3147, 3148);
  g->Reduce(ynn_reduce_sum, 3148, 6310, {3}, true);
  g->ShapeProduct(3148, 6309, {3});
  g->Binary(ynn_binary_divide, 6310, 6309, 3149);
  g->Binary(ynn_binary_add, 3149, 6469, 3150);
  g->Unary(ynn_unary_rsqrt, 3150, 3151);
  g->Binary(ynn_binary_multiply, 3147, 3151, 3152);
  g->Binary(ynn_binary_multiply, 3152, 6955, 3153);
  g->Slice(3153, 3154, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(3153, 3155, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 3155, 3156);
  g->Concat({3156,3154}, 3157, 3);
  g->Binary(ynn_binary_multiply, 3153, 3526, 3158);
  g->Binary(ynn_binary_multiply, 3157, 2, 3159);
  g->Binary(ynn_binary_add, 3158, 3159, 3160);
  g->Transpose(6960, 5207, {1,0});
  g->Binary(ynn_binary_multiply, 5199, 5206, 5204);
  g->Dot(3143, 5207, YNN_INVALID_VALUE_ID, 5203, 1);
  g->DequantizeTensor(5203, YNN_INVALID_VALUE_ID, 5204, 5205);
  g->QuantizeTensor(5205, 6434, 5200, 3161);
  g->Dequantize(3161, 3162, 0.024852370843291283, 0);
  g->Reshape(3162, 3163, {1,1,1,512});
  g->Transpose(3163, 3164, {0,2,1,3});
  g->Unary(ynn_unary_square, 3164, 3165);
  g->Reduce(ynn_reduce_sum, 3165, 6312, {3}, true);
  g->ShapeProduct(3165, 6311, {3});
  g->Binary(ynn_binary_divide, 6312, 6311, 3166);
  g->Binary(ynn_binary_add, 3166, 6469, 3167);
  g->Unary(ynn_unary_rsqrt, 3167, 3168);
  g->Binary(ynn_binary_multiply, 3164, 3168, 3169);
}

// Scope: "Layer4 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(3160, 3170, 0.0011563472216948867, 0);
  g->Append(6444, 3170, 7094, 2, s2, slinky::expr(int64_t{1}));
  g->View(7094, 7124, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(3169, 3172, 0.01785714365541935, 0);
  g->Append(6459, 3172, 7109, 2, s2, slinky::expr(int64_t{1}));
  g->View(7109, 7139, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer4 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(6959, 5219, {1,0});
  g->Binary(ynn_binary_multiply, 5199, 5218, 5215);
  g->Dot(3143, 5219, YNN_INVALID_VALUE_ID, 5214, 1);
  g->DequantizeTensor(5214, YNN_INVALID_VALUE_ID, 5215, 5216);
  g->QuantizeTensor(5216, 6434, 5217, 3173);
  g->Dequantize(3173, 3174, 0.03248032554984093, 0);
  g->SplitDim(3174, 3175, 2, {8,512});
  g->Transpose(3175, 3176, {0,2,1,3});
  g->Unary(ynn_unary_square, 3176, 3177);
  g->Reduce(ynn_reduce_sum, 3177, 6314, {3}, true);
  g->ShapeProduct(3177, 6313, {3});
  g->Binary(ynn_binary_divide, 6314, 6313, 3178);
  g->Binary(ynn_binary_add, 3178, 6469, 3180);
  g->Unary(ynn_unary_rsqrt, 3180, 3181);
  g->Binary(ynn_binary_multiply, 3176, 3181, 3182);
  g->Binary(ynn_binary_multiply, 3182, 6958, 3183);
  g->Slice(3183, 3184, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(3183, 3185, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 3185, 3186);
  g->Concat({3186,3184}, 3187, 3);
  g->Binary(ynn_binary_multiply, 3183, 3526, 3188);
  g->Binary(ynn_binary_multiply, 3187, 2, 3189);
  g->Binary(ynn_binary_add, 3188, 3189, 3191);
}

// Scope: "Layer4 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7124, 3192, 0.0011563472216948867, 0);
  g->Dequantize(7139, 3193, 0.01785714365541935, 0);
  g->Matmul(3191, 3192, 3194, false, true);
  g->Mask(3194, 6504, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 6504, 6318, {-1}, true);
  g->Binary(ynn_binary_subtract, 6504, 6318, 6315);
  g->Unary(ynn_unary_exp, 6315, 6316);
  g->Reduce(ynn_reduce_sum, 6316, 6319, {-1}, true);
  g->Binary(ynn_binary_divide, 5430, 6319, 6317);
  g->Binary(ynn_binary_multiply, 6316, 6317, 3195);
  g->Matmul(3195, 3193, 3196, false, false);
}

// Scope: "Layer4 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(3196, 3197, {0,2,1,3});
  g->FuseDims(3197, 3198, 2, 2);
  g->Quantize(3198, 3199, 0.017962608486413956, 0);
  g->Transpose(6957, 5225, {1,0});
  g->Binary(ynn_binary_multiply, 3743, 5224, 5221);
  g->Dot(3199, 5225, YNN_INVALID_VALUE_ID, 5220, 1);
  g->DequantizeTensor(5220, YNN_INVALID_VALUE_ID, 5221, 5222);
  g->QuantizeTensor(5222, 6434, 5223, 3201);
  g->Dequantize(3201, 3202, 0.17608338594436646, 0);
}

// Scope: "Layer4 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3136, 3137);
  g->Reduce(ynn_reduce_sum, 3137, 6308, {2}, true);
  g->ShapeProduct(3137, 6307, {2});
  g->Binary(ynn_binary_divide, 6308, 6307, 3138);
  g->Binary(ynn_binary_add, 3138, 6469, 3139);
  g->Unary(ynn_unary_rsqrt, 3139, 3140);
  g->Binary(ynn_binary_multiply, 3136, 3140, 3141);
  g->Binary(ynn_binary_multiply, 3141, 6944, 3142);
  BuildLayer4AttentionKvProjection(ctx);
  BuildLayer4AttentionCacheUpdate(ctx);
  BuildLayer4AttentionQueryProjection(ctx);
  BuildLayer4AttentionSdpa(ctx);
  BuildLayer4AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 3202, 3203);
  g->Reduce(ynn_reduce_sum, 3203, 6321, {2}, true);
  g->ShapeProduct(3203, 6320, {2});
  g->Binary(ynn_binary_divide, 6321, 6320, 3204);
  g->Binary(ynn_binary_add, 3204, 6469, 3205);
  g->Unary(ynn_unary_rsqrt, 3205, 3206);
  g->Binary(ynn_binary_multiply, 3202, 3206, 3207);
  g->Binary(ynn_binary_multiply, 3207, 6951, 3208);
  g->Binary(ynn_binary_add, 3208, 3136, 3209);
}

// Scope: "Layer4 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3209, 3210);
  g->Reduce(ynn_reduce_sum, 3210, 6323, {2}, true);
  g->ShapeProduct(3210, 6322, {2});
  g->Binary(ynn_binary_divide, 6323, 6322, 3213);
  g->Binary(ynn_binary_add, 3213, 6469, 3214);
  g->Unary(ynn_unary_rsqrt, 3214, 3215);
  g->Binary(ynn_binary_multiply, 3209, 3215, 3216);
  g->Binary(ynn_binary_multiply, 3216, 6954, 3217);
  g->Quantize(3217, 3218, 0.060907524079084396, 0);
  g->Transpose(6948, 5231, {1,0});
  g->Binary(ynn_binary_multiply, 5229, 5230, 5227);
  g->Dot(3218, 5231, YNN_INVALID_VALUE_ID, 5226, 1);
  g->DequantizeTensor(5226, YNN_INVALID_VALUE_ID, 5227, 5228);
  g->QuantizeTensor(5228, 6434, 3654, 3219);
  g->Dequantize(3219, 3220, 0.09251969307661057, 0);
  g->Transpose(6947, 5236, {1,0});
  g->Binary(ynn_binary_multiply, 5229, 5235, 5233);
  g->Dot(3218, 5236, YNN_INVALID_VALUE_ID, 5232, 1);
  g->DequantizeTensor(5232, YNN_INVALID_VALUE_ID, 5233, 5234);
  g->QuantizeTensor(5234, 6434, 3654, 3221);
  g->Dequantize(3221, 3223, 0.09251969307661057, 0);
  g->Polynomial(3223, 6328, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6328, 6329);
  g->Binary(ynn_binary_add, 6329, 5430, 6326);
  g->Binary(ynn_binary_multiply, 3223, 5428, 6327);
  g->Binary(ynn_binary_multiply, 6327, 6326, 3224);
  g->Binary(ynn_binary_multiply, 3220, 3224, 3225);
  g->Quantize(3225, 3226, 0.3444882035255432, 0);
  g->Transpose(6946, 5243, {1,0});
  g->Binary(ynn_binary_multiply, 5240, 5242, 5238);
  g->Dot(3226, 5243, YNN_INVALID_VALUE_ID, 5237, 1);
  g->DequantizeTensor(5237, YNN_INVALID_VALUE_ID, 5238, 5239);
  g->QuantizeTensor(5239, 6434, 5241, 3227);
  g->Dequantize(3227, 3228, 0.13582009077072144, 0);
  g->Unary(ynn_unary_square, 3228, 3229);
  g->Reduce(ynn_reduce_sum, 3229, 6331, {2}, true);
  g->ShapeProduct(3229, 6330, {2});
  g->Binary(ynn_binary_divide, 6331, 6330, 3230);
  g->Binary(ynn_binary_add, 3230, 6469, 3231);
  g->Unary(ynn_unary_rsqrt, 3231, 3232);
  g->Binary(ynn_binary_multiply, 3228, 3232, 3234);
  g->Binary(ynn_binary_multiply, 3234, 6952, 3235);
  g->Binary(ynn_binary_add, 3235, 3209, 3236);
}

// Scope: "Layer4 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(421, 3237, {0,0,4,0}, {-1,-1,1,-1});
  g->Reshape(3237, 3238, {1,1,256});
  g->Unary(ynn_unary_square, 3238, 3239);
  g->Reduce(ynn_reduce_sum, 3239, 6333, {2}, true);
  g->ShapeProduct(3239, 6332, {2});
  g->Binary(ynn_binary_divide, 6333, 6332, 3240);
  g->Binary(ynn_binary_add, 3240, 6469, 3241);
  g->Unary(ynn_unary_rsqrt, 3241, 3242);
  g->Binary(ynn_binary_multiply, 3238, 3242, 3243);
  g->Binary(ynn_binary_multiply, 3243, 7048, 3245);
  g->Binary(ynn_binary_multiply, 7078, 6472, 3246);
  g->Binary(ynn_binary_add, 3245, 3246, 3247);
  g->Binary(ynn_binary_multiply, 3247, 6466, 3248);
  g->Quantize(3236, 3249, 0.41414323449134827, 0);
  g->Transpose(6949, 5249, {1,0});
  g->Binary(ynn_binary_multiply, 5247, 5248, 5245);
  g->Dot(3249, 5249, YNN_INVALID_VALUE_ID, 5244, 1);
  g->DequantizeTensor(5244, YNN_INVALID_VALUE_ID, 5245, 5246);
  g->QuantizeTensor(5246, 6434, 5082, 3250);
  g->Dequantize(3250, 3251, 0.039862215518951416, 0);
  g->Polynomial(3251, 6336, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6336, 6337);
  g->Binary(ynn_binary_add, 6337, 5430, 6334);
  g->Binary(ynn_binary_multiply, 3251, 5428, 6335);
  g->Binary(ynn_binary_multiply, 6335, 6334, 3252);
  g->Binary(ynn_binary_multiply, 3252, 3248, 3253);
  g->Quantize(3253, 3254, 0.30314961075782776, 0);
  g->Transpose(6950, 5256, {1,0});
  g->Binary(ynn_binary_multiply, 5253, 5255, 5251);
  g->Dot(3254, 5256, YNN_INVALID_VALUE_ID, 5250, 1);
  g->DequantizeTensor(5250, YNN_INVALID_VALUE_ID, 5251, 5252);
  g->QuantizeTensor(5252, 6434, 5254, 3256);
  g->Dequantize(3256, 3257, 0.16701875627040863, 0);
  g->Unary(ynn_unary_square, 3257, 3258);
  g->Reduce(ynn_reduce_sum, 3258, 6339, {2}, true);
  g->ShapeProduct(3258, 6338, {2});
  g->Binary(ynn_binary_divide, 6339, 6338, 3259);
  g->Binary(ynn_binary_add, 3259, 6469, 3260);
  g->Unary(ynn_unary_rsqrt, 3260, 3261);
  g->Binary(ynn_binary_multiply, 3257, 3261, 3262);
  g->Binary(ynn_binary_multiply, 3262, 6953, 3263);
  g->Binary(ynn_binary_add, 3236, 3263, 3264);
  g->Binary(ynn_binary_multiply, 3264, 6945, 3265);
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
  g->Quantize(3272, 3273, 0.07399173825979233, 0);
  g->Transpose(6973, 5263, {1,0});
  g->Binary(ynn_binary_multiply, 5260, 5262, 5258);
  g->Dot(3273, 5263, YNN_INVALID_VALUE_ID, 5257, 1);
  g->DequantizeTensor(5257, YNN_INVALID_VALUE_ID, 5258, 5259);
  g->QuantizeTensor(5259, 6434, 5261, 3274);
  g->Dequantize(3274, 3275, 0.09842520207166672, 0);
  g->Reshape(3275, 3276, {1,1,1,256});
  g->Transpose(3276, 3278, {0,2,1,3});
  g->Unary(ynn_unary_square, 3278, 3279);
  g->Reduce(ynn_reduce_sum, 3279, 6343, {3}, true);
  g->ShapeProduct(3279, 6342, {3});
  g->Binary(ynn_binary_divide, 6343, 6342, 3280);
  g->Binary(ynn_binary_add, 3280, 6469, 3281);
  g->Unary(ynn_unary_rsqrt, 3281, 3282);
  g->Binary(ynn_binary_multiply, 3278, 3282, 3283);
  g->Binary(ynn_binary_multiply, 3283, 6972, 3284);
  g->Slice(3284, 3285, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3284, 3286, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3286, 3287);
  g->Concat({3287,3285}, 3289, 3);
  g->Binary(ynn_binary_multiply, 3284, 3009, 3290);
  g->Binary(ynn_binary_multiply, 3289, 3112, 3291);
  g->Binary(ynn_binary_add, 3290, 3291, 3292);
  g->Transpose(6977, 5268, {1,0});
  g->Binary(ynn_binary_multiply, 5260, 5267, 5265);
  g->Dot(3273, 5268, YNN_INVALID_VALUE_ID, 5264, 1);
  g->DequantizeTensor(5264, YNN_INVALID_VALUE_ID, 5265, 5266);
  g->QuantizeTensor(5266, 6434, 5261, 3293);
  g->Dequantize(3293, 3294, 0.09842520207166672, 0);
  g->Reshape(3294, 3295, {1,1,1,256});
  g->Transpose(3295, 3296, {0,2,1,3});
  g->Unary(ynn_unary_square, 3296, 3297);
  g->Reduce(ynn_reduce_sum, 3297, 6345, {3}, true);
  g->ShapeProduct(3297, 6344, {3});
  g->Binary(ynn_binary_divide, 6345, 6344, 3299);
  g->Binary(ynn_binary_add, 3299, 6469, 3300);
  g->Unary(ynn_unary_rsqrt, 3300, 3301);
  g->Binary(ynn_binary_multiply, 3296, 3301, 3302);
}

// Scope: "Layer5 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(3292, 3303, 0.006011798977851868, 0);
  g->Append(6445, 3303, 7095, 2, s2, slinky::expr(int64_t{1}));
  g->View(7095, 7125, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(3302, 3304, 0.047244105488061905, 0);
  g->Append(6460, 3304, 7110, 2, s2, slinky::expr(int64_t{1}));
  g->View(7110, 7140, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer5 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(6976, 5273, {1,0});
  g->Binary(ynn_binary_multiply, 5260, 5272, 5270);
  g->Dot(3273, 5273, YNN_INVALID_VALUE_ID, 5269, 1);
  g->DequantizeTensor(5269, YNN_INVALID_VALUE_ID, 5270, 5271);
  g->QuantizeTensor(5271, 6434, 4026, 3306);
  g->Dequantize(3306, 3307, 0.13385827839374542, 0);
  g->SplitDim(3307, 3308, 2, {8,256});
  g->Transpose(3308, 3309, {0,2,1,3});
  g->Unary(ynn_unary_square, 3309, 3310);
  g->Reduce(ynn_reduce_sum, 3310, 6347, {3}, true);
  g->ShapeProduct(3310, 6346, {3});
  g->Binary(ynn_binary_divide, 6347, 6346, 3311);
  g->Binary(ynn_binary_add, 3311, 6469, 3312);
  g->Unary(ynn_unary_rsqrt, 3312, 3313);
  g->Binary(ynn_binary_multiply, 3309, 3313, 3314);
  g->Binary(ynn_binary_multiply, 3314, 6975, 3317);
  g->Slice(3317, 3318, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3317, 3319, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3319, 3320);
  g->Concat({3320,3318}, 3321, 3);
  g->Binary(ynn_binary_multiply, 3317, 3009, 3322);
  g->Binary(ynn_binary_multiply, 3321, 3112, 3323);
  g->Binary(ynn_binary_add, 3322, 3323, 3324);
}

// Scope: "Layer5 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7125, 3325, 0.006011798977851868, 0);
  g->Dequantize(7140, 3326, 0.047244105488061905, 0);
  g->Matmul(3324, 3325, 3328, false, true);
  g->Mask(3328, 6505, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6505, 6351, {-1}, true);
  g->Binary(ynn_binary_subtract, 6505, 6351, 6348);
  g->Unary(ynn_unary_exp, 6348, 6349);
  g->Reduce(ynn_reduce_sum, 6349, 6352, {-1}, true);
  g->Binary(ynn_binary_divide, 5430, 6352, 6350);
  g->Binary(ynn_binary_multiply, 6349, 6350, 3329);
  g->Matmul(3329, 3326, 3330, false, false);
}

// Scope: "Layer5 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(3330, 3331, {0,2,1,3});
  g->FuseDims(3331, 3332, 2, 2);
  g->Quantize(3332, 3333, 0.026451781392097473, 0);
  g->Transpose(6974, 5280, {1,0});
  g->Binary(ynn_binary_multiply, 5277, 5279, 5275);
  g->Dot(3333, 5280, YNN_INVALID_VALUE_ID, 5274, 1);
  g->DequantizeTensor(5274, YNN_INVALID_VALUE_ID, 5275, 5276);
  g->QuantizeTensor(5276, 6434, 5278, 3334);
  g->Dequantize(3334, 3335, 0.043322544544935226, 0);
}

// Scope: "Layer5 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3265, 3267);
  g->Reduce(ynn_reduce_sum, 3267, 6341, {2}, true);
  g->ShapeProduct(3267, 6340, {2});
  g->Binary(ynn_binary_divide, 6341, 6340, 3268);
  g->Binary(ynn_binary_add, 3268, 6469, 3269);
  g->Unary(ynn_unary_rsqrt, 3269, 3270);
  g->Binary(ynn_binary_multiply, 3265, 3270, 3271);
  g->Binary(ynn_binary_multiply, 3271, 6961, 3272);
  BuildLayer5AttentionKvProjection(ctx);
  BuildLayer5AttentionCacheUpdate(ctx);
  BuildLayer5AttentionQueryProjection(ctx);
  BuildLayer5AttentionSdpa(ctx);
  BuildLayer5AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 3335, 3336);
  g->Reduce(ynn_reduce_sum, 3336, 6354, {2}, true);
  g->ShapeProduct(3336, 6353, {2});
  g->Binary(ynn_binary_divide, 6354, 6353, 3338);
  g->Binary(ynn_binary_add, 3338, 6469, 3339);
  g->Unary(ynn_unary_rsqrt, 3339, 3340);
  g->Binary(ynn_binary_multiply, 3335, 3340, 3341);
  g->Binary(ynn_binary_multiply, 3341, 6968, 3342);
  g->Binary(ynn_binary_add, 3342, 3265, 3343);
}

// Scope: "Layer5 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3343, 3344);
  g->Reduce(ynn_reduce_sum, 3344, 6356, {2}, true);
  g->ShapeProduct(3344, 6355, {2});
  g->Binary(ynn_binary_divide, 6356, 6355, 3345);
  g->Binary(ynn_binary_add, 3345, 6469, 3346);
  g->Unary(ynn_unary_rsqrt, 3346, 3347);
  g->Binary(ynn_binary_multiply, 3343, 3347, 3349);
  g->Binary(ynn_binary_multiply, 3349, 6971, 3350);
  g->Quantize(3350, 3351, 0.03518042340874672, 0);
  g->Transpose(6965, 5286, {1,0});
  g->Binary(ynn_binary_multiply, 5284, 5285, 5282);
  g->Dot(3351, 5286, YNN_INVALID_VALUE_ID, 5281, 1);
  g->DequantizeTensor(5281, YNN_INVALID_VALUE_ID, 5282, 5283);
  g->QuantizeTensor(5283, 6434, 4501, 3352);
  g->Dequantize(3352, 3353, 0.03567914664745331, 0);
  g->Transpose(6964, 5291, {1,0});
  g->Binary(ynn_binary_multiply, 5284, 5290, 5288);
  g->Dot(3351, 5291, YNN_INVALID_VALUE_ID, 5287, 1);
  g->DequantizeTensor(5287, YNN_INVALID_VALUE_ID, 5288, 5289);
  g->QuantizeTensor(5289, 6434, 4501, 3354);
  g->Dequantize(3354, 3355, 0.03567914664745331, 0);
  g->Polynomial(3355, 6359, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6359, 6360);
  g->Binary(ynn_binary_add, 6360, 5430, 6357);
  g->Binary(ynn_binary_multiply, 3355, 5428, 6358);
  g->Binary(ynn_binary_multiply, 6358, 6357, 3356);
  g->Binary(ynn_binary_multiply, 3353, 3356, 3357);
  g->Quantize(3357, 3359, 0.08415354788303375, 0);
  g->Transpose(6963, 5298, {1,0});
  g->Binary(ynn_binary_multiply, 5295, 5297, 5293);
  g->Dot(3359, 5298, YNN_INVALID_VALUE_ID, 5292, 1);
  g->DequantizeTensor(5292, YNN_INVALID_VALUE_ID, 5293, 5294);
  g->QuantizeTensor(5294, 6434, 5296, 3360);
  g->Dequantize(3360, 3361, 0.06301677227020264, 0);
  g->Unary(ynn_unary_square, 3361, 3362);
  g->Reduce(ynn_reduce_sum, 3362, 6362, {2}, true);
  g->ShapeProduct(3362, 6361, {2});
  g->Binary(ynn_binary_divide, 6362, 6361, 3363);
  g->Binary(ynn_binary_add, 3363, 6469, 3364);
  g->Unary(ynn_unary_rsqrt, 3364, 3365);
  g->Binary(ynn_binary_multiply, 3361, 3365, 3366);
  g->Binary(ynn_binary_multiply, 3366, 6969, 3367);
  g->Binary(ynn_binary_add, 3367, 3343, 3368);
}

// Scope: "Layer5 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(421, 3370, {0,0,5,0}, {-1,-1,1,-1});
  g->Reshape(3370, 3371, {1,1,256});
  g->Unary(ynn_unary_square, 3371, 3372);
  g->Reduce(ynn_reduce_sum, 3372, 6364, {2}, true);
  g->ShapeProduct(3372, 6363, {2});
  g->Binary(ynn_binary_divide, 6364, 6363, 3373);
  g->Binary(ynn_binary_add, 3373, 6469, 3374);
  g->Unary(ynn_unary_rsqrt, 3374, 3375);
  g->Binary(ynn_binary_multiply, 3371, 3375, 3376);
  g->Binary(ynn_binary_multiply, 3376, 7048, 3377);
  g->Binary(ynn_binary_multiply, 7079, 6472, 3378);
  g->Binary(ynn_binary_add, 3377, 3378, 3379);
  g->Binary(ynn_binary_multiply, 3379, 6466, 3380);
  g->Quantize(3368, 3381, 0.3165745139122009, 0);
  g->Transpose(6966, 5305, {1,0});
  g->Binary(ynn_binary_multiply, 5302, 5304, 5300);
  g->Dot(3381, 5305, YNN_INVALID_VALUE_ID, 5299, 1);
  g->DequantizeTensor(5299, YNN_INVALID_VALUE_ID, 5300, 5301);
  g->QuantizeTensor(5301, 6434, 5303, 3382);
  g->Dequantize(3382, 3383, 0.0393700897693634, 0);
  g->Polynomial(3383, 6367, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6367, 6368);
  g->Binary(ynn_binary_add, 6368, 5430, 6365);
  g->Binary(ynn_binary_multiply, 3383, 5428, 6366);
  g->Binary(ynn_binary_multiply, 6366, 6365, 3384);
  g->Binary(ynn_binary_multiply, 3384, 3380, 3385);
  g->Quantize(3385, 3386, 0.22933071851730347, 0);
  g->Transpose(6967, 5312, {1,0});
  g->Binary(ynn_binary_multiply, 5309, 5311, 5307);
  g->Dot(3386, 5312, YNN_INVALID_VALUE_ID, 5306, 1);
  g->DequantizeTensor(5306, YNN_INVALID_VALUE_ID, 5307, 5308);
  g->QuantizeTensor(5308, 6434, 5310, 3387);
  g->Dequantize(3387, 3388, 0.12322933226823807, 0);
  g->Unary(ynn_unary_square, 3388, 3389);
  g->Reduce(ynn_reduce_sum, 3389, 6375, {2}, true);
  g->ShapeProduct(3389, 6374, {2});
  g->Binary(ynn_binary_divide, 6375, 6374, 3391);
  g->Binary(ynn_binary_add, 3391, 6469, 3392);
  g->Unary(ynn_unary_rsqrt, 3392, 3393);
  g->Binary(ynn_binary_multiply, 3388, 3393, 3394);
  g->Binary(ynn_binary_multiply, 3394, 6970, 3395);
  g->Binary(ynn_binary_add, 3368, 3395, 3396);
  g->Binary(ynn_binary_multiply, 3396, 6962, 3397);
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
  g->Quantize(3404, 3405, 0.341854453086853, 0);
  g->Transpose(6990, 5319, {1,0});
  g->Binary(ynn_binary_multiply, 5316, 5318, 5314);
  g->Dot(3405, 5319, YNN_INVALID_VALUE_ID, 5313, 1);
  g->DequantizeTensor(5313, YNN_INVALID_VALUE_ID, 5314, 5315);
  g->QuantizeTensor(5315, 6434, 5317, 3406);
  g->Dequantize(3406, 3407, 0.28740158677101135, 0);
  g->Reshape(3407, 3408, {1,1,1,256});
  g->Transpose(3408, 3409, {0,2,1,3});
  g->Unary(ynn_unary_square, 3409, 3410);
  g->Reduce(ynn_reduce_sum, 3410, 6379, {3}, true);
  g->ShapeProduct(3410, 6378, {3});
  g->Binary(ynn_binary_divide, 6379, 6378, 3411);
  g->Binary(ynn_binary_add, 3411, 6469, 3413);
  g->Unary(ynn_unary_rsqrt, 3413, 3414);
  g->Binary(ynn_binary_multiply, 3409, 3414, 3415);
  g->Binary(ynn_binary_multiply, 3415, 6989, 3416);
  g->Slice(3416, 3417, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3416, 3418, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3418, 3419);
  g->Concat({3419,3417}, 3420, 3);
  g->Binary(ynn_binary_multiply, 3416, 3009, 3421);
  g->Binary(ynn_binary_multiply, 3420, 3112, 3422);
  g->Binary(ynn_binary_add, 3421, 3422, 3425);
  g->Transpose(6994, 5324, {1,0});
  g->Binary(ynn_binary_multiply, 5316, 5323, 5321);
  g->Dot(3405, 5324, YNN_INVALID_VALUE_ID, 5320, 1);
  g->DequantizeTensor(5320, YNN_INVALID_VALUE_ID, 5321, 5322);
  g->QuantizeTensor(5322, 6434, 5317, 3426);
  g->Dequantize(3426, 3427, 0.28740158677101135, 0);
  g->Reshape(3427, 3428, {1,1,1,256});
  g->Transpose(3428, 3429, {0,2,1,3});
  g->Unary(ynn_unary_square, 3429, 3430);
  g->Reduce(ynn_reduce_sum, 3430, 6381, {3}, true);
  g->ShapeProduct(3430, 6380, {3});
  g->Binary(ynn_binary_divide, 6381, 6380, 3431);
  g->Binary(ynn_binary_add, 3431, 6469, 3432);
  g->Unary(ynn_unary_rsqrt, 3432, 3433);
  g->Binary(ynn_binary_multiply, 3429, 3433, 3435);
}

// Scope: "Layer6 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(3425, 3436, 0.0057707298547029495, 0);
  g->Append(6446, 3436, 7096, 2, s2, slinky::expr(int64_t{1}));
  g->View(7096, 7126, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(3435, 3437, 0.047244105488061905, 0);
  g->Append(6461, 3437, 7111, 2, s2, slinky::expr(int64_t{1}));
  g->View(7111, 7141, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer6 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(6993, 5330, {1,0});
  g->Binary(ynn_binary_multiply, 5316, 5329, 5326);
  g->Dot(3405, 5330, YNN_INVALID_VALUE_ID, 5325, 1);
  g->DequantizeTensor(5325, YNN_INVALID_VALUE_ID, 5326, 5327);
  g->QuantizeTensor(5327, 6434, 5328, 3438);
  g->Dequantize(3438, 3439, 0.4566929042339325, 0);
  g->SplitDim(3439, 3441, 2, {8,256});
  g->Transpose(3441, 3442, {0,2,1,3});
  g->Unary(ynn_unary_square, 3442, 3443);
  g->Reduce(ynn_reduce_sum, 3443, 6383, {3}, true);
  g->ShapeProduct(3443, 6382, {3});
  g->Binary(ynn_binary_divide, 6383, 6382, 3444);
  g->Binary(ynn_binary_add, 3444, 6469, 3445);
  g->Unary(ynn_unary_rsqrt, 3445, 3446);
  g->Binary(ynn_binary_multiply, 3442, 3446, 3447);
  g->Binary(ynn_binary_multiply, 3447, 6992, 3448);
  g->Slice(3448, 3449, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3448, 3450, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3450, 3452);
  g->Concat({3452,3449}, 3453, 3);
  g->Binary(ynn_binary_multiply, 3448, 3009, 3454);
  g->Binary(ynn_binary_multiply, 3453, 3112, 3455);
  g->Binary(ynn_binary_add, 3454, 3455, 3456);
}

// Scope: "Layer6 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7126, 3457, 0.0057707298547029495, 0);
  g->Dequantize(7141, 3458, 0.047244105488061905, 0);
  g->Matmul(3456, 3457, 3459, false, true);
  g->Mask(3459, 6506, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6506, 6387, {-1}, true);
  g->Binary(ynn_binary_subtract, 6506, 6387, 6384);
  g->Unary(ynn_unary_exp, 6384, 6385);
  g->Reduce(ynn_reduce_sum, 6385, 6388, {-1}, true);
  g->Binary(ynn_binary_divide, 5430, 6388, 6386);
  g->Binary(ynn_binary_multiply, 6385, 6386, 3460);
  g->Matmul(3460, 3458, 3462, false, false);
}

// Scope: "Layer6 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(3462, 3463, {0,2,1,3});
  g->FuseDims(3463, 3464, 2, 2);
  g->Quantize(3464, 3465, 0.0354330837726593, 0);
  g->Transpose(6991, 5344, {1,0});
  g->Binary(ynn_binary_multiply, 5341, 5343, 5339);
  g->Dot(3465, 5344, YNN_INVALID_VALUE_ID, 5338, 1);
  g->DequantizeTensor(5338, YNN_INVALID_VALUE_ID, 5339, 5340);
  g->QuantizeTensor(5340, 6434, 5342, 3466);
  g->Dequantize(3466, 3467, 0.05930274724960327, 0);
}

// Scope: "Layer6 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3397, 3398);
  g->Reduce(ynn_reduce_sum, 3398, 6377, {2}, true);
  g->ShapeProduct(3398, 6376, {2});
  g->Binary(ynn_binary_divide, 6377, 6376, 3399);
  g->Binary(ynn_binary_add, 3399, 6469, 3400);
  g->Unary(ynn_unary_rsqrt, 3400, 3402);
  g->Binary(ynn_binary_multiply, 3397, 3402, 3403);
  g->Binary(ynn_binary_multiply, 3403, 6978, 3404);
  BuildLayer6AttentionKvProjection(ctx);
  BuildLayer6AttentionCacheUpdate(ctx);
  BuildLayer6AttentionQueryProjection(ctx);
  BuildLayer6AttentionSdpa(ctx);
  BuildLayer6AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 3467, 3468);
  g->Reduce(ynn_reduce_sum, 3468, 6390, {2}, true);
  g->ShapeProduct(3468, 6389, {2});
  g->Binary(ynn_binary_divide, 6390, 6389, 3469);
  g->Binary(ynn_binary_add, 3469, 6469, 3470);
  g->Unary(ynn_unary_rsqrt, 3470, 3471);
  g->Binary(ynn_binary_multiply, 3467, 3471, 3473);
  g->Binary(ynn_binary_multiply, 3473, 6985, 3474);
  g->Binary(ynn_binary_add, 3474, 3397, 3475);
}

// Scope: "Layer6 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3475, 3476);
  g->Reduce(ynn_reduce_sum, 3476, 6394, {2}, true);
  g->ShapeProduct(3476, 6393, {2});
  g->Binary(ynn_binary_divide, 6394, 6393, 3477);
  g->Binary(ynn_binary_add, 3477, 6469, 3478);
  g->Unary(ynn_unary_rsqrt, 3478, 3479);
  g->Binary(ynn_binary_multiply, 3475, 3479, 3480);
  g->Binary(ynn_binary_multiply, 3480, 6988, 3481);
  g->Quantize(3481, 3482, 0.02705955132842064, 0);
  g->Transpose(6982, 5351, {1,0});
  g->Binary(ynn_binary_multiply, 5348, 5350, 5346);
  g->Dot(3482, 5351, YNN_INVALID_VALUE_ID, 5345, 1);
  g->DequantizeTensor(5345, YNN_INVALID_VALUE_ID, 5346, 5347);
  g->QuantizeTensor(5347, 6434, 5349, 3484);
  g->Dequantize(3484, 3485, 0.02632874995470047, 0);
  g->Transpose(6981, 5356, {1,0});
  g->Binary(ynn_binary_multiply, 5348, 5355, 5353);
  g->Dot(3482, 5356, YNN_INVALID_VALUE_ID, 5352, 1);
  g->DequantizeTensor(5352, YNN_INVALID_VALUE_ID, 5353, 5354);
  g->QuantizeTensor(5354, 6434, 5349, 3486);
  g->Dequantize(3486, 3487, 0.02632874995470047, 0);
  g->Polynomial(3487, 6397, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6397, 6398);
  g->Binary(ynn_binary_add, 6398, 5430, 6395);
  g->Binary(ynn_binary_multiply, 3487, 5428, 6396);
  g->Binary(ynn_binary_multiply, 6396, 6395, 3488);
  g->Binary(ynn_binary_multiply, 3485, 3488, 3489);
  g->Quantize(3489, 3490, 0.039862215518951416, 0);
  g->Transpose(6980, 5362, {1,0});
  g->Binary(ynn_binary_multiply, 5082, 5361, 5358);
  g->Dot(3490, 5362, YNN_INVALID_VALUE_ID, 5357, 1);
  g->DequantizeTensor(5357, YNN_INVALID_VALUE_ID, 5358, 5359);
  g->QuantizeTensor(5359, 6434, 5360, 3491);
  g->Dequantize(3491, 3492, 0.019578030332922935, 0);
  g->Unary(ynn_unary_square, 3492, 3494);
  g->Reduce(ynn_reduce_sum, 3494, 6400, {2}, true);
  g->ShapeProduct(3494, 6399, {2});
  g->Binary(ynn_binary_divide, 6400, 6399, 3495);
  g->Binary(ynn_binary_add, 3495, 6469, 3496);
  g->Unary(ynn_unary_rsqrt, 3496, 3497);
  g->Binary(ynn_binary_multiply, 3492, 3497, 3498);
  g->Binary(ynn_binary_multiply, 3498, 6986, 3499);
  g->Binary(ynn_binary_add, 3499, 3475, 3500);
}

// Scope: "Layer6 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(421, 3501, {0,0,6,0}, {-1,-1,1,-1});
  g->Reshape(3501, 3502, {1,1,256});
  g->Unary(ynn_unary_square, 3502, 3503);
  g->Reduce(ynn_reduce_sum, 3503, 6402, {2}, true);
  g->ShapeProduct(3503, 6401, {2});
  g->Binary(ynn_binary_divide, 6402, 6401, 3505);
  g->Binary(ynn_binary_add, 3505, 6469, 3506);
  g->Unary(ynn_unary_rsqrt, 3506, 3507);
  g->Binary(ynn_binary_multiply, 3502, 3507, 3508);
  g->Binary(ynn_binary_multiply, 3508, 7048, 3509);
  g->Binary(ynn_binary_multiply, 7080, 6472, 3510);
  g->Binary(ynn_binary_add, 3509, 3510, 3511);
  g->Binary(ynn_binary_multiply, 3511, 6466, 3512);
  g->Quantize(3500, 3513, 0.34014976024627686, 0);
  g->Transpose(6983, 5369, {1,0});
  g->Binary(ynn_binary_multiply, 5366, 5368, 5364);
  g->Dot(3513, 5369, YNN_INVALID_VALUE_ID, 5363, 1);
  g->DequantizeTensor(5363, YNN_INVALID_VALUE_ID, 5364, 5365);
  g->QuantizeTensor(5365, 6434, 5367, 3514);
  g->Dequantize(3514, 3516, 0.04773623123764992, 0);
  g->Polynomial(3516, 6405, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6405, 6406);
  g->Binary(ynn_binary_add, 6406, 5430, 6403);
  g->Binary(ynn_binary_multiply, 3516, 5428, 6404);
  g->Binary(ynn_binary_multiply, 6404, 6403, 3517);
  g->Binary(ynn_binary_multiply, 3517, 3512, 3518);
  g->Quantize(3518, 3519, 0.12450788170099258, 0);
  g->Transpose(6984, 5375, {1,0});
  g->Binary(ynn_binary_multiply, 3970, 5374, 5371);
  g->Dot(3519, 5375, YNN_INVALID_VALUE_ID, 5370, 1);
  g->DequantizeTensor(5370, YNN_INVALID_VALUE_ID, 5371, 5372);
  g->QuantizeTensor(5372, 6434, 5373, 3520);
  g->Dequantize(3520, 3521, 0.07488936185836792, 0);
  g->Unary(ynn_unary_square, 3521, 3522);
  g->Reduce(ynn_reduce_sum, 3522, 6408, {2}, true);
  g->ShapeProduct(3522, 6407, {2});
  g->Binary(ynn_binary_divide, 6408, 6407, 3523);
  g->Binary(ynn_binary_add, 3523, 6469, 3524);
  g->Unary(ynn_unary_rsqrt, 3524, 3525);
  g->Binary(ynn_binary_multiply, 3521, 3525, 3528);
  g->Binary(ynn_binary_multiply, 3528, 6987, 3529);
  g->Binary(ynn_binary_add, 3500, 3529, 3530);
  g->Binary(ynn_binary_multiply, 3530, 6979, 3531);
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
  g->Quantize(3537, 3539, 0.29519250988960266, 0);
  g->Transpose(7007, 5382, {1,0});
  g->Binary(ynn_binary_multiply, 5379, 5381, 5377);
  g->Dot(3539, 5382, YNN_INVALID_VALUE_ID, 5376, 1);
  g->DequantizeTensor(5376, YNN_INVALID_VALUE_ID, 5377, 5378);
  g->QuantizeTensor(5378, 6434, 5380, 3540);
  g->Dequantize(3540, 3541, 0.3681102395057678, 0);
  g->Reshape(3541, 3542, {1,1,1,256});
  g->Transpose(3542, 3543, {0,2,1,3});
  g->Unary(ynn_unary_square, 3543, 3544);
  g->Reduce(ynn_reduce_sum, 3544, 6412, {3}, true);
  g->ShapeProduct(3544, 6411, {3});
  g->Binary(ynn_binary_divide, 6412, 6411, 3545);
  g->Binary(ynn_binary_add, 3545, 6469, 3546);
  g->Unary(ynn_unary_rsqrt, 3546, 3547);
  g->Binary(ynn_binary_multiply, 3543, 3547, 3548);
  g->Binary(ynn_binary_multiply, 3548, 7006, 3550);
  g->Slice(3550, 3551, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3550, 3552, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3552, 3553);
  g->Concat({3553,3551}, 3554, 3);
  g->Binary(ynn_binary_multiply, 3550, 3009, 3555);
  g->Binary(ynn_binary_multiply, 3554, 3112, 3556);
  g->Binary(ynn_binary_add, 3555, 3556, 3557);
  g->Transpose(7011, 5387, {1,0});
  g->Binary(ynn_binary_multiply, 5379, 5386, 5384);
  g->Dot(3539, 5387, YNN_INVALID_VALUE_ID, 5383, 1);
  g->DequantizeTensor(5383, YNN_INVALID_VALUE_ID, 5384, 5385);
  g->QuantizeTensor(5385, 6434, 5380, 3558);
  g->Dequantize(3558, 3560, 0.3681102395057678, 0);
  g->Reshape(3560, 3561, {1,1,1,256});
  g->Transpose(3561, 3562, {0,2,1,3});
  g->Unary(ynn_unary_square, 3562, 3563);
  g->Reduce(ynn_reduce_sum, 3563, 6416, {3}, true);
  g->ShapeProduct(3563, 6415, {3});
  g->Binary(ynn_binary_divide, 6416, 6415, 3564);
  g->Binary(ynn_binary_add, 3564, 6469, 3565);
  g->Unary(ynn_unary_rsqrt, 3565, 3566);
  g->Binary(ynn_binary_multiply, 3562, 3566, 3567);
}

// Scope: "Layer7 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(3557, 3568, 0.005869260523468256, 0);
  g->Append(6447, 3568, 7097, 2, s2, slinky::expr(int64_t{1}));
  g->View(7097, 7127, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(3567, 3570, 0.047244105488061905, 0);
  g->Append(6462, 3570, 7112, 2, s2, slinky::expr(int64_t{1}));
  g->View(7112, 7142, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer7 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(7010, 5393, {1,0});
  g->Binary(ynn_binary_multiply, 5379, 5392, 5389);
  g->Dot(3539, 5393, YNN_INVALID_VALUE_ID, 5388, 1);
  g->DequantizeTensor(5388, YNN_INVALID_VALUE_ID, 5389, 5390);
  g->QuantizeTensor(5390, 6434, 5391, 3571);
  g->Dequantize(3571, 3572, 0.31496062874794006, 0);
  g->SplitDim(3572, 3573, 2, {8,256});
  g->Transpose(3573, 3574, {0,2,1,3});
  g->Unary(ynn_unary_square, 3574, 3575);
  g->Reduce(ynn_reduce_sum, 3575, 6418, {3}, true);
  g->ShapeProduct(3575, 6417, {3});
  g->Binary(ynn_binary_divide, 6418, 6417, 3577);
  g->Binary(ynn_binary_add, 3577, 6469, 3578);
  g->Unary(ynn_unary_rsqrt, 3578, 3579);
  g->Binary(ynn_binary_multiply, 3574, 3579, 3580);
  g->Binary(ynn_binary_multiply, 3580, 7009, 3581);
  g->Slice(3581, 3582, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3581, 3583, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3583, 3584);
  g->Concat({3584,3582}, 3585, 3);
  g->Binary(ynn_binary_multiply, 3581, 3009, 3586);
  g->Binary(ynn_binary_multiply, 3585, 3112, 3588);
  g->Binary(ynn_binary_add, 3586, 3588, 3589);
}

// Scope: "Layer7 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7127, 3590, 0.005869260523468256, 0);
  g->Dequantize(7142, 3591, 0.047244105488061905, 0);
  g->Matmul(3589, 3590, 3592, false, true);
  g->Mask(3592, 6507, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6507, 6422, {-1}, true);
  g->Binary(ynn_binary_subtract, 6507, 6422, 6419);
  g->Unary(ynn_unary_exp, 6419, 6420);
  g->Reduce(ynn_reduce_sum, 6420, 6423, {-1}, true);
  g->Binary(ynn_binary_divide, 5430, 6423, 6421);
  g->Binary(ynn_binary_multiply, 6420, 6421, 3593);
  g->Matmul(3593, 3591, 3594, false, false);
}

// Scope: "Layer7 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(3594, 3595, {0,2,1,3});
  g->FuseDims(3595, 3596, 2, 2);
  g->Quantize(3596, 3598, 0.028912410140037537, 0);
  g->Transpose(7008, 5400, {1,0});
  g->Binary(ynn_binary_multiply, 5397, 5399, 5395);
  g->Dot(3598, 5400, YNN_INVALID_VALUE_ID, 5394, 1);
  g->DequantizeTensor(5394, YNN_INVALID_VALUE_ID, 5395, 5396);
  g->QuantizeTensor(5396, 6434, 5398, 3599);
  g->Dequantize(3599, 3600, 0.025238478556275368, 0);
}

// Scope: "Layer7 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3531, 3532);
  g->Reduce(ynn_reduce_sum, 3532, 6410, {2}, true);
  g->ShapeProduct(3532, 6409, {2});
  g->Binary(ynn_binary_divide, 6410, 6409, 3533);
  g->Binary(ynn_binary_add, 3533, 6469, 3534);
  g->Unary(ynn_unary_rsqrt, 3534, 3535);
  g->Binary(ynn_binary_multiply, 3531, 3535, 3536);
  g->Binary(ynn_binary_multiply, 3536, 6995, 3537);
  BuildLayer7AttentionKvProjection(ctx);
  BuildLayer7AttentionCacheUpdate(ctx);
  BuildLayer7AttentionQueryProjection(ctx);
  BuildLayer7AttentionSdpa(ctx);
  BuildLayer7AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 3600, 3601);
  g->Reduce(ynn_reduce_sum, 3601, 6425, {2}, true);
  g->ShapeProduct(3601, 6424, {2});
  g->Binary(ynn_binary_divide, 6425, 6424, 3602);
  g->Binary(ynn_binary_add, 3602, 6469, 3603);
  g->Unary(ynn_unary_rsqrt, 3603, 3604);
  g->Binary(ynn_binary_multiply, 3600, 3604, 3605);
  g->Binary(ynn_binary_multiply, 3605, 7002, 3606);
  g->Binary(ynn_binary_add, 3606, 3531, 3607);
}

// Scope: "Layer7 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3607, 3609);
  g->Reduce(ynn_reduce_sum, 3609, 6427, {2}, true);
  g->ShapeProduct(3609, 6426, {2});
  g->Binary(ynn_binary_divide, 6427, 6426, 3610);
  g->Binary(ynn_binary_add, 3610, 6469, 3611);
  g->Unary(ynn_unary_rsqrt, 3611, 3612);
  g->Binary(ynn_binary_multiply, 3607, 3612, 3613);
  g->Binary(ynn_binary_multiply, 3613, 7005, 3614);
  g->Quantize(3614, 3615, 0.023717211559414864, 0);
  g->Transpose(6999, 5412, {1,0});
  g->Binary(ynn_binary_multiply, 5409, 5411, 5407);
  g->Dot(3615, 5412, YNN_INVALID_VALUE_ID, 5406, 1);
  g->DequantizeTensor(5406, YNN_INVALID_VALUE_ID, 5407, 5408);
  g->QuantizeTensor(5408, 6434, 5410, 3616);
  g->Dequantize(3616, 3617, 0.021899616345763206, 0);
  g->Transpose(6998, 5417, {1,0});
  g->Binary(ynn_binary_multiply, 5409, 5416, 5414);
  g->Dot(3615, 5417, YNN_INVALID_VALUE_ID, 5413, 1);
  g->DequantizeTensor(5413, YNN_INVALID_VALUE_ID, 5414, 5415);
  g->QuantizeTensor(5415, 6434, 5410, 3619);
  g->Dequantize(3619, 3620, 0.021899616345763206, 0);
  g->Polynomial(3620, 6430, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6430, 6431);
  g->Binary(ynn_binary_add, 6431, 5430, 6428);
  g->Binary(ynn_binary_multiply, 3620, 5428, 6429);
  g->Binary(ynn_binary_multiply, 6429, 6428, 3621);
  g->Binary(ynn_binary_multiply, 3617, 3621, 3622);
  g->Quantize(3622, 3623, 0.02202264778316021, 0);
  g->Transpose(6997, 5424, {1,0});
  g->Binary(ynn_binary_multiply, 5421, 5423, 5419);
  g->Dot(3623, 5424, YNN_INVALID_VALUE_ID, 5418, 1);
  g->DequantizeTensor(5418, YNN_INVALID_VALUE_ID, 5419, 5420);
  g->QuantizeTensor(5420, 6434, 5422, 3624);
  g->Dequantize(3624, 3625, 0.01081059779971838, 0);
  g->Unary(ynn_unary_square, 3625, 3626);
  g->Reduce(ynn_reduce_sum, 3626, 6433, {2}, true);
  g->ShapeProduct(3626, 6432, {2});
  g->Binary(ynn_binary_divide, 6433, 6432, 3627);
  g->Binary(ynn_binary_add, 3627, 6469, 3628);
  g->Unary(ynn_unary_rsqrt, 3628, 3);
  g->Binary(ynn_binary_multiply, 3625, 3, 4);
  g->Binary(ynn_binary_multiply, 4, 7003, 5);
  g->Binary(ynn_binary_add, 5, 3607, 6);
}

// Scope: "Layer7 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(421, 7, {0,0,7,0}, {-1,-1,1,-1});
  g->Reshape(7, 8, {1,1,256});
  g->Unary(ynn_unary_square, 8, 9);
  g->Reduce(ynn_reduce_sum, 9, 5426, {2}, true);
  g->ShapeProduct(9, 5425, {2});
  g->Binary(ynn_binary_divide, 5426, 5425, 10);
  g->Binary(ynn_binary_add, 10, 6469, 11);
  g->Unary(ynn_unary_rsqrt, 11, 12);
  g->Binary(ynn_binary_multiply, 8, 12, 14);
  g->Binary(ynn_binary_multiply, 14, 7048, 15);
  g->Binary(ynn_binary_multiply, 7081, 6472, 16);
  g->Binary(ynn_binary_add, 15, 16, 17);
  g->Binary(ynn_binary_multiply, 17, 6466, 18);
  g->Quantize(6, 19, 0.15832224488258362, 0);
  g->Transpose(7000, 3642, {1,0});
  g->Binary(ynn_binary_multiply, 3639, 3641, 3637);
  g->Dot(19, 3642, YNN_INVALID_VALUE_ID, 3636, 1);
  g->DequantizeTensor(3636, YNN_INVALID_VALUE_ID, 3637, 3638);
  g->QuantizeTensor(3638, 6434, 3640, 20);
  g->Dequantize(20, 21, 0.055118121206760406, 0);
  g->Polynomial(21, 5431, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5431, 5432);
  g->Binary(ynn_binary_add, 5432, 5430, 5427);
  g->Binary(ynn_binary_multiply, 21, 5428, 5429);
  g->Binary(ynn_binary_multiply, 5429, 5427, 22);
  g->Binary(ynn_binary_multiply, 22, 18, 23);
  g->Quantize(23, 25, 0.22834646701812744, 0);
  g->Transpose(7001, 3649, {1,0});
  g->Binary(ynn_binary_multiply, 3646, 3648, 3644);
  g->Dot(25, 3649, YNN_INVALID_VALUE_ID, 3643, 1);
  g->DequantizeTensor(3643, YNN_INVALID_VALUE_ID, 3644, 3645);
  g->QuantizeTensor(3645, 6434, 3647, 26);
  g->Dequantize(26, 27, 0.08292699605226517, 0);
  g->Unary(ynn_unary_square, 27, 28);
  g->Reduce(ynn_reduce_sum, 28, 5434, {2}, true);
  g->ShapeProduct(28, 5433, {2});
  g->Binary(ynn_binary_divide, 5434, 5433, 29);
  g->Binary(ynn_binary_add, 29, 6469, 30);
  g->Unary(ynn_unary_rsqrt, 30, 31);
  g->Binary(ynn_binary_multiply, 27, 31, 32);
  g->Binary(ynn_binary_multiply, 32, 7004, 33);
  g->Binary(ynn_binary_add, 6, 33, 34);
  g->Binary(ynn_binary_multiply, 34, 6996, 36);
}

// Scope: "Layer7"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7(Context& ctx) {
  BuildLayer7Attention(ctx);
  BuildLayer7Mlp(ctx);
  BuildLayer7PerLayerEmbedding(ctx);
}

}  // namespace BuildGemma4DecodeSource
