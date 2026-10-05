// Generated YNNPACK builder; do not edit.
#include "gemma4_decode_builder.h"

namespace BuildGemma4DecodeSource {

// Scope: "Layer0 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer0AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(1807, 1916, 0.6088034510612488, 0);
  g->Transpose(6430, 4630, {1,0});
  g->Binary(ynn_binary_multiply, 4627, 4629, 4625);
  g->Dot(1916, 4630, YNN_INVALID_VALUE_ID, 4624, 1);
  g->DequantizeTensor(4624, YNN_INVALID_VALUE_ID, 4625, 4626);
  g->QuantizeTensor(4626, 6342, 4628, 2025);
  g->Dequantize(2025, 2134, 1.535433053970337, 0);
  g->Reshape(2134, 2242, {1,1,1,256});
  g->Transpose(2242, 2347, {0,2,1,3});
  g->Unary(ynn_unary_square, 2347, 2455);
  g->Reduce(ynn_reduce_sum, 2455, 6076, {3}, true);
  g->ShapeProduct(2455, 6075, {3});
  g->Binary(ynn_binary_divide, 6076, 6075, 2564);
  g->Binary(ynn_binary_add, 2564, 6376, 2672);
  g->Binary(ynn_binary_pow, 2672, 6378, 2781);
  g->Binary(ynn_binary_multiply, 2347, 2781, 2888);
  g->Convert(6429, 2970);
  g->Binary(ynn_binary_multiply, 2888, 2970, 2981);
  g->Slice(2981, 2993, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2981, 3004, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3004, 3015);
  g->Concat({3015,2993}, 3026, 3);
  g->Binary(ynn_binary_multiply, 2981, 2133, 3036);
  g->Binary(ynn_binary_multiply, 3026, 2992, 3042);
  g->Binary(ynn_binary_add, 3036, 3042, 3053);
  g->Transpose(6434, 5164, {1,0});
  g->Binary(ynn_binary_multiply, 4627, 5163, 5161);
  g->Dot(1916, 5164, YNN_INVALID_VALUE_ID, 5160, 1);
  g->DequantizeTensor(5160, YNN_INVALID_VALUE_ID, 5161, 5162);
  g->QuantizeTensor(5162, 6342, 4628, 3073);
  g->Dequantize(3073, 3084, 1.535433053970337, 0);
  g->Reshape(3084, 3095, {1,1,1,256});
  g->Transpose(3095, 3106, {0,2,1,3});
  g->Unary(ynn_unary_square, 3106, 3117);
  g->Reduce(ynn_reduce_sum, 3117, 6228, {3}, true);
  g->ShapeProduct(3117, 6227, {3});
  g->Binary(ynn_binary_divide, 6228, 6227, 3128);
  g->Binary(ynn_binary_add, 3128, 6376, 3139);
  g->Binary(ynn_binary_pow, 3139, 6378, 3150);
  g->Binary(ynn_binary_multiply, 3106, 3150, 3160);
}

// Scope: "Layer0 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer0AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(3053, 3171, 0.005997600965201855, 0);
  g->Append(6343, 3171, 6992, 2, s2, slinky::expr(int64_t{1}));
  g->View(6992, 7022, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7022, 3197, 0.005997600965201855, 0);
  g->Quantize(3160, 3208, 0.047244105488061905, 0);
  g->Append(6358, 3208, 7007, 2, s2, slinky::expr(int64_t{1}));
  g->View(7007, 7037, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7037, 3238, 0.047244105488061905, 0);
}

// Scope: "Layer0 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer0AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(6433, 5256, {1,0});
  g->Binary(ynn_binary_multiply, 4627, 5255, 5252);
  g->Dot(1916, 5256, YNN_INVALID_VALUE_ID, 5251, 1);
  g->DequantizeTensor(5251, YNN_INVALID_VALUE_ID, 5252, 5253);
  g->QuantizeTensor(5253, 6342, 5254, 3259);
  g->Dequantize(3259, 3270, 3.118110179901123, 0);
  g->SplitDim(3270, 3281, 2, {8,256});
  g->Transpose(3281, 3291, {0,2,1,3});
  g->Unary(ynn_unary_square, 3291, 3301);
  g->Reduce(ynn_reduce_sum, 3301, 6265, {3}, true);
  g->ShapeProduct(3301, 6264, {3});
  g->Binary(ynn_binary_divide, 6265, 6264, 3309);
  g->Binary(ynn_binary_add, 3309, 6376, 3320);
  g->Binary(ynn_binary_pow, 3320, 6378, 3330);
  g->Binary(ynn_binary_multiply, 3291, 3330, 3341);
  g->Convert(6432, 3352);
  g->Binary(ynn_binary_multiply, 3341, 3352, 3362);
  g->Slice(3362, 3373, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3362, 3384, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3384, 3395);
  g->Concat({3395,3373}, 3407, 3);
  g->Binary(ynn_binary_multiply, 3362, 2133, 3418);
  g->Binary(ynn_binary_multiply, 3407, 2992, 3428);
  g->Binary(ynn_binary_add, 3418, 3428, 3437);
}

// Scope: "Layer0 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer0AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(3437, 3197, 3445, false, true);
  g->Mask(3445, 6383, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6383, 6305, {-1}, true);
  g->Binary(ynn_binary_subtract, 6383, 6305, 6302);
  g->Unary(ynn_unary_exp, 6302, 6303);
  g->Reduce(ynn_reduce_sum, 6303, 6306, {-1}, true);
  g->Binary(ynn_binary_divide, 5404, 6306, 6304);
  g->Binary(ynn_binary_multiply, 6303, 6304, 3465);
  g->Matmul(3465, 3238, 3476, false, false);
}

// Scope: "Layer0 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer0AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(3476, 3486, {0,2,1,3});
  g->FuseDims(3486, 3497, 2, 2);
  g->Quantize(3497, 3509, 0.03026575781404972, 0);
  g->Transpose(6431, 5375, {1,0});
  g->Binary(ynn_binary_multiply, 5372, 5374, 5370);
  g->Dot(3509, 5375, YNN_INVALID_VALUE_ID, 5369, 1);
  g->DequantizeTensor(5369, YNN_INVALID_VALUE_ID, 5370, 5371);
  g->QuantizeTensor(5371, 6342, 5373, 3520);
  g->Dequantize(3520, 3531, 0.21056734025478363, 0);
}

// Scope: "Layer0 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer0Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 6373, 1156);
  g->Reduce(ynn_reduce_sum, 1156, 5721, {2}, true);
  g->ShapeProduct(1156, 5720, {2});
  g->Binary(ynn_binary_divide, 5721, 5720, 1264);
  g->Binary(ynn_binary_add, 1264, 6376, 1373);
  g->Binary(ynn_binary_pow, 1373, 6378, 1481);
  g->Binary(ynn_binary_multiply, 6373, 1481, 1590);
  g->Convert(6418, 1699);
  g->Binary(ynn_binary_multiply, 1590, 1699, 1807);
  BuildLayer0AttentionKvProjection(ctx);
  BuildLayer0AttentionCacheUpdate(ctx);
  BuildLayer0AttentionQueryProjection(ctx);
  BuildLayer0AttentionSdpa(ctx);
  BuildLayer0AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 3531, 3542);
  g->Reduce(ynn_reduce_sum, 3542, 6328, {2}, true);
  g->ShapeProduct(3542, 6327, {2});
  g->Binary(ynn_binary_divide, 6328, 6327, 3553);
  g->Binary(ynn_binary_add, 3553, 6376, 3563);
  g->Binary(ynn_binary_pow, 3563, 6378, 3570);
  g->Binary(ynn_binary_multiply, 3531, 3570, 3580);
  g->Convert(6425, 3591);
  g->Binary(ynn_binary_multiply, 3580, 3591, 3601);
  g->Binary(ynn_binary_add, 6373, 3601, 3);
}

// Scope: "Layer0 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer0Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3, 13);
  g->Reduce(ynn_reduce_sum, 13, 5410, {2}, true);
  g->ShapeProduct(13, 5409, {2});
  g->Binary(ynn_binary_divide, 5410, 5409, 24);
  g->Binary(ynn_binary_add, 24, 6376, 35);
  g->Binary(ynn_binary_pow, 35, 6378, 46);
  g->Binary(ynn_binary_multiply, 3, 46, 57);
  g->Convert(6428, 68);
  g->Binary(ynn_binary_multiply, 57, 68, 79);
  g->Quantize(79, 89, 0.9406865835189819, 0);
  g->Transpose(6422, 3663, {1,0});
  g->Binary(ynn_binary_multiply, 3660, 3662, 3658);
  g->Dot(89, 3663, YNN_INVALID_VALUE_ID, 3657, 1);
  g->DequantizeTensor(3657, YNN_INVALID_VALUE_ID, 3658, 3659);
  g->QuantizeTensor(3659, 6342, 3661, 95);
  g->Dequantize(95, 107, 0.6181102395057678, 0);
  g->Transpose(6421, 3681, {1,0});
  g->Binary(ynn_binary_multiply, 3660, 3680, 3678);
  g->Dot(89, 3681, YNN_INVALID_VALUE_ID, 3677, 1);
  g->DequantizeTensor(3677, YNN_INVALID_VALUE_ID, 3678, 3679);
  g->QuantizeTensor(3679, 6342, 3661, 127);
  g->Dequantize(127, 138, 0.6181102395057678, 0);
  g->Polynomial(138, 5440, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5440, 5441);
  g->Binary(ynn_binary_add, 5441, 5404, 5438);
  g->Binary(ynn_binary_multiply, 138, 5402, 5439);
  g->Binary(ynn_binary_multiply, 5439, 5438, 148);
  g->Binary(ynn_binary_multiply, 107, 148, 159);
  g->Quantize(159, 170, 27.842519760131836, 0);
  g->Transpose(6420, 3721, {1,0});
  g->Binary(ynn_binary_multiply, 3718, 3720, 3716);
  g->Dot(170, 3721, YNN_INVALID_VALUE_ID, 3715, 1);
  g->DequantizeTensor(3715, YNN_INVALID_VALUE_ID, 3716, 3717);
  g->QuantizeTensor(3717, 6342, 3719, 181);
  g->Dequantize(181, 192, 16.64207649230957, 0);
  g->Unary(ynn_unary_square, 192, 203);
  g->Reduce(ynn_reduce_sum, 203, 5455, {2}, true);
  g->ShapeProduct(203, 5454, {2});
  g->Binary(ynn_binary_divide, 5455, 5454, 214);
  g->Binary(ynn_binary_add, 214, 6376, 225);
  g->Binary(ynn_binary_pow, 225, 6378, 231);
  g->Binary(ynn_binary_multiply, 192, 231, 242);
  g->Convert(6426, 252);
  g->Binary(ynn_binary_multiply, 242, 252, 263);
  g->Binary(ynn_binary_add, 3, 263, 274);
}

// Scope: "Layer0 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer0PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1047, 284, {0,0,0,0}, {-1,-1,1,-1});
  g->Reshape(284, 295, {1,1,256});
  g->Binary(ynn_binary_add, 295, 6956, 306);
  g->Binary(ynn_binary_multiply, 306, 6374, 318);
  g->Quantize(274, 329, 3.334678888320923, 0);
  g->Transpose(6423, 3793, {1,0});
  g->Binary(ynn_binary_multiply, 3790, 3792, 3788);
  g->Dot(329, 3793, YNN_INVALID_VALUE_ID, 3787, 1);
  g->DequantizeTensor(3787, YNN_INVALID_VALUE_ID, 3788, 3789);
  g->QuantizeTensor(3789, 6342, 3791, 340);
  g->Dequantize(340, 350, 0.01857776567339897, 0);
  g->Polynomial(350, 5489, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5489, 5490);
  g->Binary(ynn_binary_add, 5490, 5404, 5487);
  g->Binary(ynn_binary_multiply, 350, 5402, 5488);
  g->Binary(ynn_binary_multiply, 5488, 5487, 359);
  g->Binary(ynn_binary_multiply, 359, 318, 367);
  g->Quantize(367, 378, 0.03764764964580536, 0);
  g->Transpose(6424, 3811, {1,0});
  g->Binary(ynn_binary_multiply, 3808, 3810, 3806);
  g->Dot(378, 3811, YNN_INVALID_VALUE_ID, 3805, 1);
  g->DequantizeTensor(3805, YNN_INVALID_VALUE_ID, 3806, 3807);
  g->QuantizeTensor(3807, 6342, 3809, 388);
  g->Dequantize(388, 399, 0.03129800781607628, 0);
  g->Unary(ynn_unary_square, 399, 410);
  g->Reduce(ynn_reduce_sum, 410, 5507, {2}, true);
  g->ShapeProduct(410, 5506, {2});
  g->Binary(ynn_binary_divide, 5507, 5506, 421);
  g->Binary(ynn_binary_add, 421, 6376, 432);
  g->Binary(ynn_binary_pow, 432, 6378, 443);
  g->Binary(ynn_binary_multiply, 399, 443, 454);
  g->Convert(6427, 465);
  g->Binary(ynn_binary_multiply, 454, 465, 476);
  g->Binary(ynn_binary_add, 274, 476, 486);
  g->Convert(6419, 495);
  g->Binary(ynn_binary_multiply, 486, 495, 503);
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
  g->Quantize(579, 590, 0.4842597544193268, 0);
  g->Transpose(6447, 3923, {1,0});
  g->Binary(ynn_binary_multiply, 3920, 3922, 3918);
  g->Dot(590, 3923, YNN_INVALID_VALUE_ID, 3917, 1);
  g->DequantizeTensor(3917, YNN_INVALID_VALUE_ID, 3918, 3919);
  g->QuantizeTensor(3919, 6342, 3921, 601);
  g->Dequantize(601, 612, 0.41535434126853943, 0);
  g->Reshape(612, 622, {1,1,1,256});
  g->Transpose(622, 630, {0,2,1,3});
  g->Unary(ynn_unary_square, 630, 640);
  g->Reduce(ynn_reduce_sum, 640, 5558, {3}, true);
  g->ShapeProduct(640, 5557, {3});
  g->Binary(ynn_binary_divide, 5558, 5557, 651);
  g->Binary(ynn_binary_add, 651, 6376, 661);
  g->Binary(ynn_binary_pow, 661, 6378, 672);
  g->Binary(ynn_binary_multiply, 630, 672, 682);
  g->Convert(6446, 693);
  g->Binary(ynn_binary_multiply, 682, 693, 704);
  g->Slice(704, 715, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(704, 726, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 726, 738);
  g->Concat({738,715}, 749, 3);
  g->Binary(ynn_binary_multiply, 704, 2133, 759);
  g->Binary(ynn_binary_multiply, 749, 2992, 765);
  g->Binary(ynn_binary_add, 759, 765, 776);
  g->Transpose(6451, 4002, {1,0});
  g->Binary(ynn_binary_multiply, 3920, 4001, 3999);
  g->Dot(590, 4002, YNN_INVALID_VALUE_ID, 3998, 1);
  g->DequantizeTensor(3998, YNN_INVALID_VALUE_ID, 3999, 4000);
  g->QuantizeTensor(4000, 6342, 3921, 796);
  g->Dequantize(796, 807, 0.41535434126853943, 0);
  g->Reshape(807, 817, {1,1,1,256});
  g->Transpose(817, 828, {0,2,1,3});
  g->Unary(ynn_unary_square, 828, 840);
  g->Reduce(ynn_reduce_sum, 840, 5610, {3}, true);
  g->ShapeProduct(840, 5609, {3});
  g->Binary(ynn_binary_divide, 5610, 5609, 851);
  g->Binary(ynn_binary_add, 851, 6376, 862);
  g->Binary(ynn_binary_pow, 862, 6378, 873);
  g->Binary(ynn_binary_multiply, 828, 873, 883);
}

// Scope: "Layer1 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(776, 894, 0.005761673673987389, 0);
  g->Append(6344, 894, 6993, 2, s2, slinky::expr(int64_t{1}));
  g->View(6993, 7023, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7023, 919, 0.005761673673987389, 0);
  g->Quantize(883, 930, 0.047244105488061905, 0);
  g->Append(6359, 930, 7008, 2, s2, slinky::expr(int64_t{1}));
  g->View(7008, 7038, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7038, 961, 0.047244105488061905, 0);
}

// Scope: "Layer1 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(6450, 4098, {1,0});
  g->Binary(ynn_binary_multiply, 3920, 4097, 4094);
  g->Dot(590, 4098, YNN_INVALID_VALUE_ID, 4093, 1);
  g->DequantizeTensor(4093, YNN_INVALID_VALUE_ID, 4094, 4095);
  g->QuantizeTensor(4095, 6342, 4096, 982);
  g->Dequantize(982, 993, 0.35039371252059937, 0);
  g->SplitDim(993, 1004, 2, {8,256});
  g->Transpose(1004, 1014, {0,2,1,3});
  g->Unary(ynn_unary_square, 1014, 1025);
  g->Reduce(ynn_reduce_sum, 1025, 5654, {3}, true);
  g->ShapeProduct(1025, 5653, {3});
  g->Binary(ynn_binary_divide, 5654, 5653, 1036);
  g->Binary(ynn_binary_add, 1036, 6376, 1048);
  g->Binary(ynn_binary_pow, 1048, 6378, 1059);
  g->Binary(ynn_binary_multiply, 1014, 1059, 1070);
  g->Convert(6449, 1081);
  g->Binary(ynn_binary_multiply, 1070, 1081, 1092);
  g->Slice(1092, 1103, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1092, 1113, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1113, 1124);
  g->Concat({1124,1103}, 1135, 3);
  g->Binary(ynn_binary_multiply, 1092, 2133, 1145);
  g->Binary(ynn_binary_multiply, 1135, 2992, 1157);
  g->Binary(ynn_binary_add, 1145, 1157, 1168);
}

// Scope: "Layer1 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(1168, 919, 1179, false, true);
  g->Mask(1179, 6384, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6384, 5699, {-1}, true);
  g->Binary(ynn_binary_subtract, 6384, 5699, 5696);
  g->Unary(ynn_unary_exp, 5696, 5697);
  g->Reduce(ynn_reduce_sum, 5697, 5700, {-1}, true);
  g->Binary(ynn_binary_divide, 5404, 5700, 5698);
  g->Binary(ynn_binary_multiply, 5697, 5698, 1200);
  g->Matmul(1200, 961, 1211, false, false);
}

// Scope: "Layer1 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1211, 1221, {0,2,1,3});
  g->FuseDims(1221, 1232, 2, 2);
  g->Quantize(1232, 1242, 0.023129930719733238, 0);
  g->Transpose(6448, 4232, {1,0});
  g->Binary(ynn_binary_multiply, 4229, 4231, 4227);
  g->Dot(1242, 4232, YNN_INVALID_VALUE_ID, 4226, 1);
  g->DequantizeTensor(4226, YNN_INVALID_VALUE_ID, 4227, 4228);
  g->QuantizeTensor(4228, 6342, 4230, 1253);
  g->Dequantize(1253, 1265, 0.03322756290435791, 0);
}

// Scope: "Layer1 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 503, 514);
  g->Reduce(ynn_reduce_sum, 514, 5532, {2}, true);
  g->ShapeProduct(514, 5531, {2});
  g->Binary(ynn_binary_divide, 5532, 5531, 525);
  g->Binary(ynn_binary_add, 525, 6376, 536);
  g->Binary(ynn_binary_pow, 536, 6378, 546);
  g->Binary(ynn_binary_multiply, 503, 546, 557);
  g->Convert(6435, 568);
  g->Binary(ynn_binary_multiply, 557, 568, 579);
  BuildLayer1AttentionKvProjection(ctx);
  BuildLayer1AttentionCacheUpdate(ctx);
  BuildLayer1AttentionQueryProjection(ctx);
  BuildLayer1AttentionSdpa(ctx);
  BuildLayer1AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1265, 1276);
  g->Reduce(ynn_reduce_sum, 1276, 5727, {2}, true);
  g->ShapeProduct(1276, 5726, {2});
  g->Binary(ynn_binary_divide, 5727, 5726, 1287);
  g->Binary(ynn_binary_add, 1287, 6376, 1298);
  g->Binary(ynn_binary_pow, 1298, 6378, 1309);
  g->Binary(ynn_binary_multiply, 1265, 1309, 1319);
  g->Convert(6442, 1330);
  g->Binary(ynn_binary_multiply, 1319, 1330, 1340);
  g->Binary(ynn_binary_add, 503, 1340, 1351);
}

// Scope: "Layer1 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1351, 1362);
  g->Reduce(ynn_reduce_sum, 1362, 5752, {2}, true);
  g->ShapeProduct(1362, 5751, {2});
  g->Binary(ynn_binary_divide, 5752, 5751, 1374);
  g->Binary(ynn_binary_add, 1374, 6376, 1385);
  g->Binary(ynn_binary_pow, 1385, 6378, 1396);
  g->Binary(ynn_binary_multiply, 1351, 1396, 1407);
  g->Convert(6445, 1417);
  g->Binary(ynn_binary_multiply, 1407, 1417, 1428);
  g->Quantize(1428, 1438, 0.08275254815816879, 0);
  g->Transpose(6439, 4333, {1,0});
  g->Binary(ynn_binary_multiply, 4330, 4332, 4328);
  g->Dot(1438, 4333, YNN_INVALID_VALUE_ID, 4327, 1);
  g->DequantizeTensor(4327, YNN_INVALID_VALUE_ID, 4328, 4329);
  g->QuantizeTensor(4329, 6342, 4331, 1449);
  g->Dequantize(1449, 1460, 0.06889764219522476, 0);
  g->Transpose(6438, 4351, {1,0});
  g->Binary(ynn_binary_multiply, 4330, 4350, 4348);
  g->Dot(1438, 4351, YNN_INVALID_VALUE_ID, 4347, 1);
  g->DequantizeTensor(4347, YNN_INVALID_VALUE_ID, 4348, 4349);
  g->QuantizeTensor(4349, 6342, 4331, 1482);
  g->Dequantize(1482, 1493, 0.06889764219522476, 0);
  g->Polynomial(1493, 5784, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5784, 5785);
  g->Binary(ynn_binary_add, 5785, 5404, 5782);
  g->Binary(ynn_binary_multiply, 1493, 5402, 5783);
  g->Binary(ynn_binary_multiply, 5783, 5782, 1504);
  g->Binary(ynn_binary_multiply, 1460, 1504, 1514);
  g->Quantize(1514, 1525, 0.21062994003295898, 0);
  g->Transpose(6437, 4378, {1,0});
  g->Binary(ynn_binary_multiply, 4375, 4377, 4373);
  g->Dot(1525, 4378, YNN_INVALID_VALUE_ID, 4372, 1);
  g->DequantizeTensor(4372, YNN_INVALID_VALUE_ID, 4373, 4374);
  g->QuantizeTensor(4374, 6342, 4376, 1535);
  g->Dequantize(1535, 1546, 0.09257561713457108, 0);
  g->Unary(ynn_unary_square, 1546, 1557);
  g->Reduce(ynn_reduce_sum, 1557, 5808, {2}, true);
  g->ShapeProduct(1557, 5807, {2});
  g->Binary(ynn_binary_divide, 5808, 5807, 1568);
  g->Binary(ynn_binary_add, 1568, 6376, 1579);
  g->Binary(ynn_binary_pow, 1579, 6378, 1591);
  g->Binary(ynn_binary_multiply, 1546, 1591, 1602);
  g->Convert(6443, 1612);
  g->Binary(ynn_binary_multiply, 1602, 1612, 1623);
  g->Binary(ynn_binary_add, 1351, 1623, 1634);
}

// Scope: "Layer1 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1047, 1644, {0,0,1,0}, {-1,-1,1,-1});
  g->Reshape(1644, 1655, {1,1,256});
  g->Binary(ynn_binary_add, 1655, 6957, 1666);
  g->Binary(ynn_binary_multiply, 1666, 6374, 1677);
  g->Quantize(1634, 1688, 0.4206320643424988, 0);
  g->Transpose(6440, 4464, {1,0});
  g->Binary(ynn_binary_multiply, 4461, 4463, 4459);
  g->Dot(1688, 4464, YNN_INVALID_VALUE_ID, 4458, 1);
  g->DequantizeTensor(4458, YNN_INVALID_VALUE_ID, 4459, 4460);
  g->QuantizeTensor(4460, 6342, 4462, 1700);
  g->Dequantize(1700, 1710, 0.010150108486413956, 0);
  g->Polynomial(1710, 5847, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5847, 5848);
  g->Binary(ynn_binary_add, 5848, 5404, 5845);
  g->Binary(ynn_binary_multiply, 1710, 5402, 5846);
  g->Binary(ynn_binary_multiply, 5846, 5845, 1721);
  g->Binary(ynn_binary_multiply, 1721, 1677, 1732);
  g->Quantize(1732, 1742, 0.026820875704288483, 0);
  g->Transpose(6441, 4497, {1,0});
  g->Binary(ynn_binary_multiply, 4494, 4496, 4492);
  g->Dot(1742, 4497, YNN_INVALID_VALUE_ID, 4491, 1);
  g->DequantizeTensor(4491, YNN_INVALID_VALUE_ID, 4492, 4493);
  g->QuantizeTensor(4493, 6342, 4495, 1753);
  g->Dequantize(1753, 1764, 0.020895034074783325, 0);
  g->Unary(ynn_unary_square, 1764, 1775);
  g->Reduce(ynn_reduce_sum, 1775, 5866, {2}, true);
  g->ShapeProduct(1775, 5865, {2});
  g->Binary(ynn_binary_divide, 5866, 5865, 1786);
  g->Binary(ynn_binary_add, 1786, 6376, 1797);
  g->Binary(ynn_binary_pow, 1797, 6378, 1808);
  g->Binary(ynn_binary_multiply, 1764, 1808, 1819);
  g->Convert(6444, 1830);
  g->Binary(ynn_binary_multiply, 1819, 1830, 1840);
  g->Binary(ynn_binary_add, 1634, 1840, 1851);
  g->Convert(6436, 1862);
  g->Binary(ynn_binary_multiply, 1851, 1862, 1873);
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
  g->Quantize(1949, 1960, 0.15746013820171356, 0);
  g->Transpose(6619, 4610, {1,0});
  g->Binary(ynn_binary_multiply, 4607, 4609, 4605);
  g->Dot(1960, 4610, YNN_INVALID_VALUE_ID, 4604, 1);
  g->DequantizeTensor(4604, YNN_INVALID_VALUE_ID, 4605, 4606);
  g->QuantizeTensor(4606, 6342, 4608, 1971);
  g->Dequantize(1971, 1982, 0.180118128657341, 0);
  g->Reshape(1982, 1993, {1,1,1,256});
  g->Transpose(1993, 2003, {0,2,1,3});
  g->Unary(ynn_unary_square, 2003, 2014);
  g->Reduce(ynn_reduce_sum, 2014, 5931, {3}, true);
  g->ShapeProduct(2014, 5930, {3});
  g->Binary(ynn_binary_divide, 5931, 5930, 2026);
  g->Binary(ynn_binary_add, 2026, 6376, 2036);
  g->Binary(ynn_binary_pow, 2036, 6378, 2047);
  g->Binary(ynn_binary_multiply, 2003, 2047, 2058);
  g->Convert(6618, 2069);
  g->Binary(ynn_binary_multiply, 2058, 2069, 2080);
  g->Slice(2080, 2091, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2080, 2101, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2101, 2112);
  g->Concat({2112,2091}, 2123, 3);
  g->Binary(ynn_binary_multiply, 2080, 2133, 2135);
  g->Binary(ynn_binary_multiply, 2123, 2992, 2146);
  g->Binary(ynn_binary_add, 2135, 2146, 2157);
  g->Transpose(6623, 4713, {1,0});
  g->Binary(ynn_binary_multiply, 4607, 4712, 4710);
  g->Dot(1960, 4713, YNN_INVALID_VALUE_ID, 4709, 1);
  g->DequantizeTensor(4709, YNN_INVALID_VALUE_ID, 4710, 4711);
  g->QuantizeTensor(4711, 6342, 4608, 2178);
  g->Dequantize(2178, 2189, 0.180118128657341, 0);
  g->Reshape(2189, 2200, {1,1,1,256});
  g->Transpose(2200, 2210, {0,2,1,3});
  g->Unary(ynn_unary_square, 2210, 2221);
  g->Reduce(ynn_reduce_sum, 2221, 5987, {3}, true);
  g->ShapeProduct(2221, 5986, {3});
  g->Binary(ynn_binary_divide, 5987, 5986, 2231);
  g->Binary(ynn_binary_add, 2231, 6376, 2243);
  g->Binary(ynn_binary_pow, 2243, 6378, 2254);
  g->Binary(ynn_binary_multiply, 2210, 2254, 2265);
}

// Scope: "Layer2 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(2157, 2276, 0.005684707313776016, 0);
  g->Append(6350, 2276, 6999, 2, s2, slinky::expr(int64_t{1}));
  g->View(6999, 7029, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7029, 2306, 0.005684707313776016, 0);
  g->Quantize(2265, 2317, 0.047244105488061905, 0);
  g->Append(6365, 2317, 7014, 2, s2, slinky::expr(int64_t{1}));
  g->View(7014, 7044, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7044, 2348, 0.047244105488061905, 0);
}

// Scope: "Layer2 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(6622, 4812, {1,0});
  g->Binary(ynn_binary_multiply, 4607, 4811, 4808);
  g->Dot(1960, 4812, YNN_INVALID_VALUE_ID, 4807, 1);
  g->DequantizeTensor(4807, YNN_INVALID_VALUE_ID, 4808, 4809);
  g->QuantizeTensor(4809, 6342, 4810, 2369);
  g->Dequantize(2369, 2380, 0.1643700897693634, 0);
  g->SplitDim(2380, 2391, 2, {8,256});
  g->Transpose(2391, 2401, {0,2,1,3});
  g->Unary(ynn_unary_square, 2401, 2412);
  g->Reduce(ynn_reduce_sum, 2412, 6035, {3}, true);
  g->ShapeProduct(2412, 6034, {3});
  g->Binary(ynn_binary_divide, 6035, 6034, 2422);
  g->Binary(ynn_binary_add, 2422, 6376, 2433);
  g->Binary(ynn_binary_pow, 2433, 6378, 2444);
  g->Binary(ynn_binary_multiply, 2401, 2444, 2456);
  g->Convert(6621, 2467);
  g->Binary(ynn_binary_multiply, 2456, 2467, 2478);
  g->Slice(2478, 2489, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2478, 2499, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2499, 2510);
  g->Concat({2510,2489}, 2520, 3);
  g->Binary(ynn_binary_multiply, 2478, 2133, 2531);
  g->Binary(ynn_binary_multiply, 2520, 2992, 2542);
  g->Binary(ynn_binary_add, 2531, 2542, 2553);
}

// Scope: "Layer2 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(2553, 2306, 2565, false, true);
  g->Mask(2565, 6395, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6395, 6082, {-1}, true);
  g->Binary(ynn_binary_subtract, 6395, 6082, 6079);
  g->Unary(ynn_unary_exp, 6079, 6080);
  g->Reduce(ynn_reduce_sum, 6080, 6083, {-1}, true);
  g->Binary(ynn_binary_divide, 5404, 6083, 6081);
  g->Binary(ynn_binary_multiply, 6080, 6081, 2586);
  g->Matmul(2586, 2348, 2596, false, false);
}

// Scope: "Layer2 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(2596, 2607, {0,2,1,3});
  g->FuseDims(2607, 2618, 2, 2);
  g->Quantize(2618, 2628, 0.0216535534709692, 0);
  g->Transpose(6620, 4942, {1,0});
  g->Binary(ynn_binary_multiply, 4939, 4941, 4937);
  g->Dot(2628, 4942, YNN_INVALID_VALUE_ID, 4936, 1);
  g->DequantizeTensor(4936, YNN_INVALID_VALUE_ID, 4937, 4938);
  g->QuantizeTensor(4938, 6342, 4940, 2639);
  g->Dequantize(2639, 2650, 0.03426840156316757, 0);
}

// Scope: "Layer2 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1873, 1884);
  g->Reduce(ynn_reduce_sum, 1884, 5895, {2}, true);
  g->ShapeProduct(1884, 5894, {2});
  g->Binary(ynn_binary_divide, 5895, 5894, 1895);
  g->Binary(ynn_binary_add, 1895, 6376, 1905);
  g->Binary(ynn_binary_pow, 1905, 6378, 1917);
  g->Binary(ynn_binary_multiply, 1873, 1917, 1928);
  g->Convert(6607, 1938);
  g->Binary(ynn_binary_multiply, 1928, 1938, 1949);
  BuildLayer2AttentionKvProjection(ctx);
  BuildLayer2AttentionCacheUpdate(ctx);
  BuildLayer2AttentionQueryProjection(ctx);
  BuildLayer2AttentionSdpa(ctx);
  BuildLayer2AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2650, 2661);
  g->Reduce(ynn_reduce_sum, 2661, 6108, {2}, true);
  g->ShapeProduct(2661, 6107, {2});
  g->Binary(ynn_binary_divide, 6108, 6107, 2673);
  g->Binary(ynn_binary_add, 2673, 6376, 2684);
  g->Binary(ynn_binary_pow, 2684, 6378, 2694);
  g->Binary(ynn_binary_multiply, 2650, 2694, 2705);
  g->Convert(6614, 2716);
  g->Binary(ynn_binary_multiply, 2705, 2716, 2726);
  g->Binary(ynn_binary_add, 1873, 2726, 2737);
}

// Scope: "Layer2 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2737, 2748);
  g->Reduce(ynn_reduce_sum, 2748, 6133, {2}, true);
  g->ShapeProduct(2748, 6132, {2});
  g->Binary(ynn_binary_divide, 6133, 6132, 2759);
  g->Binary(ynn_binary_add, 2759, 6376, 2770);
  g->Binary(ynn_binary_pow, 2770, 6378, 2782);
  g->Binary(ynn_binary_multiply, 2737, 2782, 2792);
  g->Convert(6617, 2803);
  g->Binary(ynn_binary_multiply, 2792, 2803, 2814);
  g->Quantize(2814, 2824, 0.04049227386713028, 0);
  g->Transpose(6611, 5037, {1,0});
  g->Binary(ynn_binary_multiply, 5034, 5036, 5032);
  g->Dot(2824, 5037, YNN_INVALID_VALUE_ID, 5031, 1);
  g->DequantizeTensor(5031, YNN_INVALID_VALUE_ID, 5032, 5033);
  g->QuantizeTensor(5033, 6342, 5035, 2835);
  g->Dequantize(2835, 2846, 0.04183071851730347, 0);
  g->Transpose(6610, 5063, {1,0});
  g->Binary(ynn_binary_multiply, 5034, 5062, 5060);
  g->Dot(2824, 5063, YNN_INVALID_VALUE_ID, 5059, 1);
  g->DequantizeTensor(5059, YNN_INVALID_VALUE_ID, 5060, 5061);
  g->QuantizeTensor(5061, 6342, 5035, 2867);
  g->Dequantize(2867, 2878, 0.04183071851730347, 0);
  g->Polynomial(2878, 6170, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6170, 6171);
  g->Binary(ynn_binary_add, 6171, 5404, 6168);
  g->Binary(ynn_binary_multiply, 2878, 5402, 6169);
  g->Binary(ynn_binary_multiply, 6169, 6168, 2889);
  g->Binary(ynn_binary_multiply, 2846, 2889, 2900);
  g->Quantize(2900, 2911, 0.09645669907331467, 0);
  g->Transpose(6609, 5096, {1,0});
  g->Binary(ynn_binary_multiply, 5093, 5095, 5091);
  g->Dot(2911, 5096, YNN_INVALID_VALUE_ID, 5090, 1);
  g->DequantizeTensor(5090, YNN_INVALID_VALUE_ID, 5091, 5092);
  g->QuantizeTensor(5092, 6342, 5094, 2921);
  g->Dequantize(2921, 2932, 0.05011765658855438, 0);
  g->Unary(ynn_unary_square, 2932, 2943);
  g->Reduce(ynn_reduce_sum, 2943, 6189, {2}, true);
  g->ShapeProduct(2943, 6188, {2});
  g->Binary(ynn_binary_divide, 6189, 6188, 2954);
  g->Binary(ynn_binary_add, 2954, 6376, 2965);
  g->Binary(ynn_binary_pow, 2965, 6378, 2968);
  g->Binary(ynn_binary_multiply, 2932, 2968, 2969);
  g->Convert(6615, 2971);
  g->Binary(ynn_binary_multiply, 2969, 2971, 2972);
  g->Binary(ynn_binary_add, 2737, 2972, 2973);
}

// Scope: "Layer2 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1047, 2974, {0,0,2,0}, {-1,-1,1,-1});
  g->Reshape(2974, 2975, {1,1,256});
  g->Binary(ynn_binary_add, 2975, 6968, 2976);
  g->Binary(ynn_binary_multiply, 2976, 6374, 2977);
  g->Quantize(2973, 2978, 0.045230474323034286, 0);
  g->Transpose(6612, 5128, {1,0});
  g->Binary(ynn_binary_multiply, 5125, 5127, 5123);
  g->Dot(2978, 5128, YNN_INVALID_VALUE_ID, 5122, 1);
  g->DequantizeTensor(5122, YNN_INVALID_VALUE_ID, 5123, 5124);
  g->QuantizeTensor(5124, 6342, 5126, 2979);
  g->Dequantize(2979, 2980, 0.017839577049016953, 0);
  g->Polynomial(2980, 6194, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6194, 6195);
  g->Binary(ynn_binary_add, 6195, 5404, 6192);
  g->Binary(ynn_binary_multiply, 2980, 5402, 6193);
  g->Binary(ynn_binary_multiply, 6193, 6192, 2982);
  g->Binary(ynn_binary_multiply, 2982, 2977, 2983);
  g->Quantize(2983, 2984, 0.05216536670923233, 0);
  g->Transpose(6613, 5135, {1,0});
  g->Binary(ynn_binary_multiply, 5132, 5134, 5130);
  g->Dot(2984, 5135, YNN_INVALID_VALUE_ID, 5129, 1);
  g->DequantizeTensor(5129, YNN_INVALID_VALUE_ID, 5130, 5131);
  g->QuantizeTensor(5131, 6342, 5133, 2985);
  g->Dequantize(2985, 2986, 0.021943029016256332, 0);
  g->Unary(ynn_unary_square, 2986, 2987);
  g->Reduce(ynn_reduce_sum, 2987, 6197, {2}, true);
  g->ShapeProduct(2987, 6196, {2});
  g->Binary(ynn_binary_divide, 6197, 6196, 2988);
  g->Binary(ynn_binary_add, 2988, 6376, 2989);
  g->Binary(ynn_binary_pow, 2989, 6378, 2990);
  g->Binary(ynn_binary_multiply, 2986, 2990, 2991);
  g->Convert(6616, 2994);
  g->Binary(ynn_binary_multiply, 2991, 2994, 2995);
  g->Binary(ynn_binary_add, 2973, 2995, 2996);
  g->Convert(6608, 2997);
  g->Binary(ynn_binary_multiply, 2996, 2997, 2998);
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
  g->Quantize(3006, 3007, 0.12591414153575897, 0);
  g->Transpose(6776, 5141, {1,0});
  g->Binary(ynn_binary_multiply, 5139, 5140, 5137);
  g->Dot(3007, 5141, YNN_INVALID_VALUE_ID, 5136, 1);
  g->DequantizeTensor(5136, YNN_INVALID_VALUE_ID, 5137, 5138);
  g->QuantizeTensor(5138, 6342, 4594, 3008);
  g->Dequantize(3008, 3009, 0.08710630983114243, 0);
  g->Reshape(3009, 3010, {1,1,1,256});
  g->Transpose(3010, 3011, {0,2,1,3});
  g->Unary(ynn_unary_square, 3011, 3012);
  g->Reduce(ynn_reduce_sum, 3012, 6201, {3}, true);
  g->ShapeProduct(3012, 6200, {3});
  g->Binary(ynn_binary_divide, 6201, 6200, 3013);
  g->Binary(ynn_binary_add, 3013, 6376, 3014);
  g->Binary(ynn_binary_pow, 3014, 6378, 3016);
  g->Binary(ynn_binary_multiply, 3011, 3016, 3017);
  g->Convert(6775, 3018);
  g->Binary(ynn_binary_multiply, 3017, 3018, 3019);
  g->Slice(3019, 3020, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3019, 3021, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3021, 3022);
  g->Concat({3022,3020}, 3023, 3);
  g->Binary(ynn_binary_multiply, 3019, 2133, 3024);
  g->Binary(ynn_binary_multiply, 3023, 2992, 3025);
  g->Binary(ynn_binary_add, 3024, 3025, 3027);
  g->Transpose(6780, 5146, {1,0});
  g->Binary(ynn_binary_multiply, 5139, 5145, 5143);
  g->Dot(3007, 5146, YNN_INVALID_VALUE_ID, 5142, 1);
  g->DequantizeTensor(5142, YNN_INVALID_VALUE_ID, 5143, 5144);
  g->QuantizeTensor(5144, 6342, 4594, 3028);
  g->Dequantize(3028, 3029, 0.08710630983114243, 0);
  g->Reshape(3029, 3030, {1,1,1,256});
  g->Transpose(3030, 3031, {0,2,1,3});
  g->Unary(ynn_unary_square, 3031, 3032);
  g->Reduce(ynn_reduce_sum, 3032, 6203, {3}, true);
  g->ShapeProduct(3032, 6202, {3});
  g->Binary(ynn_binary_divide, 6203, 6202, 3033);
  g->Binary(ynn_binary_add, 3033, 6376, 3034);
  g->Binary(ynn_binary_pow, 3034, 6378, 3035);
  g->Binary(ynn_binary_multiply, 3031, 3035, 3037);
}

// Scope: "Layer3 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(3027, 3038, 0.00573749840259552, 0);
  g->Append(6351, 3038, 7000, 2, s2, slinky::expr(int64_t{1}));
  g->View(7000, 7030, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7030, 3039, 0.00573749840259552, 0);
  g->Quantize(3037, 3040, 0.047244105488061905, 0);
  g->Append(6366, 3040, 7015, 2, s2, slinky::expr(int64_t{1}));
  g->View(7015, 7045, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7045, 3041, 0.047244105488061905, 0);
}

// Scope: "Layer3 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(6779, 5152, {1,0});
  g->Binary(ynn_binary_multiply, 5139, 5151, 5148);
  g->Dot(3007, 5152, YNN_INVALID_VALUE_ID, 5147, 1);
  g->DequantizeTensor(5147, YNN_INVALID_VALUE_ID, 5148, 5149);
  g->QuantizeTensor(5149, 6342, 5150, 3043);
  g->Dequantize(3043, 3044, 0.15354332327842712, 0);
  g->SplitDim(3044, 3045, 2, {8,256});
  g->Transpose(3045, 3046, {0,2,1,3});
  g->Unary(ynn_unary_square, 3046, 3047);
  g->Reduce(ynn_reduce_sum, 3047, 6205, {3}, true);
  g->ShapeProduct(3047, 6204, {3});
  g->Binary(ynn_binary_divide, 6205, 6204, 3048);
  g->Binary(ynn_binary_add, 3048, 6376, 3049);
  g->Binary(ynn_binary_pow, 3049, 6378, 3050);
  g->Binary(ynn_binary_multiply, 3046, 3050, 3051);
  g->Convert(6778, 3052);
  g->Binary(ynn_binary_multiply, 3051, 3052, 3054);
  g->Slice(3054, 3055, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3054, 3056, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3056, 3057);
  g->Concat({3057,3055}, 3058, 3);
  g->Binary(ynn_binary_multiply, 3054, 2133, 3059);
  g->Binary(ynn_binary_multiply, 3058, 2992, 3060);
  g->Binary(ynn_binary_add, 3059, 3060, 3061);
}

// Scope: "Layer3 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(3061, 3039, 3062, false, true);
  g->Mask(3062, 6406, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6406, 6209, {-1}, true);
  g->Binary(ynn_binary_subtract, 6406, 6209, 6206);
  g->Unary(ynn_unary_exp, 6206, 6207);
  g->Reduce(ynn_reduce_sum, 6207, 6210, {-1}, true);
  g->Binary(ynn_binary_divide, 5404, 6210, 6208);
  g->Binary(ynn_binary_multiply, 6207, 6208, 3063);
  g->Matmul(3063, 3041, 3064, false, false);
}

// Scope: "Layer3 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(3064, 3065, {0,2,1,3});
  g->FuseDims(3065, 3066, 2, 2);
  g->Quantize(3066, 3067, 0.02706693857908249, 0);
  g->Transpose(6777, 5159, {1,0});
  g->Binary(ynn_binary_multiply, 5156, 5158, 5154);
  g->Dot(3067, 5159, YNN_INVALID_VALUE_ID, 5153, 1);
  g->DequantizeTensor(5153, YNN_INVALID_VALUE_ID, 5154, 5155);
  g->QuantizeTensor(5155, 6342, 5157, 3068);
  g->Dequantize(3068, 3069, 0.07367152720689774, 0);
}

// Scope: "Layer3 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2998, 2999);
  g->Reduce(ynn_reduce_sum, 2999, 6199, {2}, true);
  g->ShapeProduct(2999, 6198, {2});
  g->Binary(ynn_binary_divide, 6199, 6198, 3000);
  g->Binary(ynn_binary_add, 3000, 6376, 3001);
  g->Binary(ynn_binary_pow, 3001, 6378, 3002);
  g->Binary(ynn_binary_multiply, 2998, 3002, 3003);
  g->Convert(6764, 3005);
  g->Binary(ynn_binary_multiply, 3003, 3005, 3006);
  BuildLayer3AttentionKvProjection(ctx);
  BuildLayer3AttentionCacheUpdate(ctx);
  BuildLayer3AttentionQueryProjection(ctx);
  BuildLayer3AttentionSdpa(ctx);
  BuildLayer3AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 3069, 3070);
  g->Reduce(ynn_reduce_sum, 3070, 6212, {2}, true);
  g->ShapeProduct(3070, 6211, {2});
  g->Binary(ynn_binary_divide, 6212, 6211, 3071);
  g->Binary(ynn_binary_add, 3071, 6376, 3072);
  g->Binary(ynn_binary_pow, 3072, 6378, 3074);
  g->Binary(ynn_binary_multiply, 3069, 3074, 3075);
  g->Convert(6771, 3076);
  g->Binary(ynn_binary_multiply, 3075, 3076, 3077);
  g->Binary(ynn_binary_add, 2998, 3077, 3078);
}

// Scope: "Layer3 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3078, 3079);
  g->Reduce(ynn_reduce_sum, 3079, 6214, {2}, true);
  g->ShapeProduct(3079, 6213, {2});
  g->Binary(ynn_binary_divide, 6214, 6213, 3080);
  g->Binary(ynn_binary_add, 3080, 6376, 3081);
  g->Binary(ynn_binary_pow, 3081, 6378, 3082);
  g->Binary(ynn_binary_multiply, 3078, 3082, 3083);
  g->Convert(6774, 3085);
  g->Binary(ynn_binary_multiply, 3083, 3085, 3086);
  g->Quantize(3086, 3087, 0.019482526928186417, 0);
  g->Transpose(6768, 5170, {1,0});
  g->Binary(ynn_binary_multiply, 5168, 5169, 5166);
  g->Dot(3087, 5170, YNN_INVALID_VALUE_ID, 5165, 1);
  g->DequantizeTensor(5165, YNN_INVALID_VALUE_ID, 5166, 5167);
  g->QuantizeTensor(5167, 6342, 4128, 3088);
  g->Dequantize(3088, 3089, 0.02005414292216301, 0);
  g->Transpose(6767, 5175, {1,0});
  g->Binary(ynn_binary_multiply, 5168, 5174, 5172);
  g->Dot(3087, 5175, YNN_INVALID_VALUE_ID, 5171, 1);
  g->DequantizeTensor(5171, YNN_INVALID_VALUE_ID, 5172, 5173);
  g->QuantizeTensor(5173, 6342, 4128, 3090);
  g->Dequantize(3090, 3091, 0.02005414292216301, 0);
  g->Polynomial(3091, 6217, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6217, 6218);
  g->Binary(ynn_binary_add, 6218, 5404, 6215);
  g->Binary(ynn_binary_multiply, 3091, 5402, 6216);
  g->Binary(ynn_binary_multiply, 6216, 6215, 3092);
  g->Binary(ynn_binary_multiply, 3089, 3092, 3093);
  g->Quantize(3093, 3096, 0.03297245129942894, 0);
  g->Transpose(6766, 5181, {1,0});
  g->Binary(ynn_binary_multiply, 4276, 5180, 5177);
  g->Dot(3096, 5181, YNN_INVALID_VALUE_ID, 5176, 1);
  g->DequantizeTensor(5176, YNN_INVALID_VALUE_ID, 5177, 5178);
  g->QuantizeTensor(5178, 6342, 5179, 3097);
  g->Dequantize(3097, 3098, 0.022154856473207474, 0);
  g->Unary(ynn_unary_square, 3098, 3099);
  g->Reduce(ynn_reduce_sum, 3099, 6220, {2}, true);
  g->ShapeProduct(3099, 6219, {2});
  g->Binary(ynn_binary_divide, 6220, 6219, 3100);
  g->Binary(ynn_binary_add, 3100, 6376, 3101);
  g->Binary(ynn_binary_pow, 3101, 6378, 3102);
  g->Binary(ynn_binary_multiply, 3098, 3102, 3103);
  g->Convert(6772, 3104);
  g->Binary(ynn_binary_multiply, 3103, 3104, 3105);
  g->Binary(ynn_binary_add, 3078, 3105, 3107);
}

// Scope: "Layer3 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1047, 3108, {0,0,3,0}, {-1,-1,1,-1});
  g->Reshape(3108, 3109, {1,1,256});
  g->Binary(ynn_binary_add, 3109, 6979, 3110);
  g->Binary(ynn_binary_multiply, 3110, 6374, 3111);
  g->Quantize(3107, 3112, 0.2861534655094147, 0);
  g->Transpose(6769, 5188, {1,0});
  g->Binary(ynn_binary_multiply, 5185, 5187, 5183);
  g->Dot(3112, 5188, YNN_INVALID_VALUE_ID, 5182, 1);
  g->DequantizeTensor(5182, YNN_INVALID_VALUE_ID, 5183, 5184);
  g->QuantizeTensor(5184, 6342, 5186, 3113);
  g->Dequantize(3113, 3114, 0.050688985735177994, 0);
  g->Polynomial(3114, 6223, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6223, 6224);
  g->Binary(ynn_binary_add, 6224, 5404, 6221);
  g->Binary(ynn_binary_multiply, 3114, 5402, 6222);
  g->Binary(ynn_binary_multiply, 6222, 6221, 3115);
  g->Binary(ynn_binary_multiply, 3115, 3111, 3116);
  g->Quantize(3116, 3118, 0.06692913919687271, 0);
  g->Transpose(6770, 5195, {1,0});
  g->Binary(ynn_binary_multiply, 5192, 5194, 5190);
  g->Dot(3118, 5195, YNN_INVALID_VALUE_ID, 5189, 1);
  g->DequantizeTensor(5189, YNN_INVALID_VALUE_ID, 5190, 5191);
  g->QuantizeTensor(5191, 6342, 5193, 3119);
  g->Dequantize(3119, 3120, 0.0805763527750969, 0);
  g->Unary(ynn_unary_square, 3120, 3121);
  g->Reduce(ynn_reduce_sum, 3121, 6226, {2}, true);
  g->ShapeProduct(3121, 6225, {2});
  g->Binary(ynn_binary_divide, 6226, 6225, 3122);
  g->Binary(ynn_binary_add, 3122, 6376, 3123);
  g->Binary(ynn_binary_pow, 3123, 6378, 3124);
  g->Binary(ynn_binary_multiply, 3120, 3124, 3125);
  g->Convert(6773, 3126);
  g->Binary(ynn_binary_multiply, 3125, 3126, 3127);
  g->Binary(ynn_binary_add, 3107, 3127, 3129);
  g->Convert(6765, 3130);
  g->Binary(ynn_binary_multiply, 3129, 3130, 3131);
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
  g->Quantize(3138, 3140, 0.023374712094664574, 0);
  g->Transpose(6863, 5202, {1,0});
  g->Binary(ynn_binary_multiply, 5199, 5201, 5197);
  g->Dot(3140, 5202, YNN_INVALID_VALUE_ID, 5196, 1);
  g->DequantizeTensor(5196, YNN_INVALID_VALUE_ID, 5197, 5198);
  g->QuantizeTensor(5198, 6342, 5200, 3141);
  g->Dequantize(3141, 3142, 0.024852370843291283, 0);
  g->Reshape(3142, 3143, {1,1,1,512});
  g->Transpose(3143, 3144, {0,2,1,3});
  g->Unary(ynn_unary_square, 3144, 3145);
  g->Reduce(ynn_reduce_sum, 3145, 6232, {3}, true);
  g->ShapeProduct(3145, 6231, {3});
  g->Binary(ynn_binary_divide, 6232, 6231, 3146);
  g->Binary(ynn_binary_add, 3146, 6376, 3147);
  g->Binary(ynn_binary_pow, 3147, 6378, 3148);
  g->Binary(ynn_binary_multiply, 3144, 3148, 3149);
  g->Convert(6862, 3151);
  g->Binary(ynn_binary_multiply, 3149, 3151, 3152);
  g->Slice(3152, 3153, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(3152, 3154, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 3154, 3155);
  g->Concat({3155,3153}, 3156, 3);
  g->Binary(ynn_binary_multiply, 3152, 3406, 3157);
  g->Binary(ynn_binary_multiply, 3156, 3508, 3158);
  g->Binary(ynn_binary_add, 3157, 3158, 3159);
  g->Transpose(6867, 5207, {1,0});
  g->Binary(ynn_binary_multiply, 5199, 5206, 5204);
  g->Dot(3140, 5207, YNN_INVALID_VALUE_ID, 5203, 1);
  g->DequantizeTensor(5203, YNN_INVALID_VALUE_ID, 5204, 5205);
  g->QuantizeTensor(5205, 6342, 5200, 3161);
  g->Dequantize(3161, 3162, 0.024852370843291283, 0);
  g->Reshape(3162, 3163, {1,1,1,512});
  g->Transpose(3163, 3164, {0,2,1,3});
  g->Unary(ynn_unary_square, 3164, 3165);
  g->Reduce(ynn_reduce_sum, 3165, 6234, {3}, true);
  g->ShapeProduct(3165, 6233, {3});
  g->Binary(ynn_binary_divide, 6234, 6233, 3166);
  g->Binary(ynn_binary_add, 3166, 6376, 3167);
  g->Binary(ynn_binary_pow, 3167, 6378, 3168);
  g->Binary(ynn_binary_multiply, 3164, 3168, 3169);
}

// Scope: "Layer4 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(3159, 3170, 0.0011563472216948867, 0);
  g->Append(6352, 3170, 7001, 2, s2, slinky::expr(int64_t{1}));
  g->View(7001, 7031, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7031, 3172, 0.0011563472216948867, 0);
  g->Quantize(3169, 3173, 0.01785714365541935, 0);
  g->Append(6367, 3173, 7016, 2, s2, slinky::expr(int64_t{1}));
  g->View(7016, 7046, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7046, 3174, 0.01785714365541935, 0);
}

// Scope: "Layer4 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(6866, 5213, {1,0});
  g->Binary(ynn_binary_multiply, 5199, 5212, 5209);
  g->Dot(3140, 5213, YNN_INVALID_VALUE_ID, 5208, 1);
  g->DequantizeTensor(5208, YNN_INVALID_VALUE_ID, 5209, 5210);
  g->QuantizeTensor(5210, 6342, 5211, 3175);
  g->Dequantize(3175, 3176, 0.03248032554984093, 0);
  g->SplitDim(3176, 3177, 2, {8,512});
  g->Transpose(3177, 3178, {0,2,1,3});
  g->Unary(ynn_unary_square, 3178, 3179);
  g->Reduce(ynn_reduce_sum, 3179, 6236, {3}, true);
  g->ShapeProduct(3179, 6235, {3});
  g->Binary(ynn_binary_divide, 6236, 6235, 3180);
  g->Binary(ynn_binary_add, 3180, 6376, 3181);
  g->Binary(ynn_binary_pow, 3181, 6378, 3182);
  g->Binary(ynn_binary_multiply, 3178, 3182, 3183);
  g->Convert(6865, 3184);
  g->Binary(ynn_binary_multiply, 3183, 3184, 3185);
  g->Slice(3185, 3186, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(3185, 3187, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 3187, 3188);
  g->Concat({3188,3186}, 3189, 3);
  g->Binary(ynn_binary_multiply, 3185, 3406, 3190);
  g->Binary(ynn_binary_multiply, 3189, 3508, 3191);
  g->Binary(ynn_binary_add, 3190, 3191, 3192);
}

// Scope: "Layer4 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(3192, 3172, 3193, false, true);
  g->Mask(3193, 6412, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 6412, 6240, {-1}, true);
  g->Binary(ynn_binary_subtract, 6412, 6240, 6237);
  g->Unary(ynn_unary_exp, 6237, 6238);
  g->Reduce(ynn_reduce_sum, 6238, 6241, {-1}, true);
  g->Binary(ynn_binary_divide, 5404, 6241, 6239);
  g->Binary(ynn_binary_multiply, 6238, 6239, 3194);
  g->Matmul(3194, 3174, 3195, false, false);
}

// Scope: "Layer4 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(3195, 3198, {0,2,1,3});
  g->FuseDims(3198, 3199, 2, 2);
  g->Quantize(3199, 3200, 0.017962608486413956, 0);
  g->Transpose(6864, 5219, {1,0});
  g->Binary(ynn_binary_multiply, 3743, 5218, 5215);
  g->Dot(3200, 5219, YNN_INVALID_VALUE_ID, 5214, 1);
  g->DequantizeTensor(5214, YNN_INVALID_VALUE_ID, 5215, 5216);
  g->QuantizeTensor(5216, 6342, 5217, 3201);
  g->Dequantize(3201, 3202, 0.17608338594436646, 0);
}

// Scope: "Layer4 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3131, 3132);
  g->Reduce(ynn_reduce_sum, 3132, 6230, {2}, true);
  g->ShapeProduct(3132, 6229, {2});
  g->Binary(ynn_binary_divide, 6230, 6229, 3133);
  g->Binary(ynn_binary_add, 3133, 6376, 3134);
  g->Binary(ynn_binary_pow, 3134, 6378, 3135);
  g->Binary(ynn_binary_multiply, 3131, 3135, 3136);
  g->Convert(6851, 3137);
  g->Binary(ynn_binary_multiply, 3136, 3137, 3138);
  BuildLayer4AttentionKvProjection(ctx);
  BuildLayer4AttentionCacheUpdate(ctx);
  BuildLayer4AttentionQueryProjection(ctx);
  BuildLayer4AttentionSdpa(ctx);
  BuildLayer4AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 3202, 3203);
  g->Reduce(ynn_reduce_sum, 3203, 6243, {2}, true);
  g->ShapeProduct(3203, 6242, {2});
  g->Binary(ynn_binary_divide, 6243, 6242, 3204);
  g->Binary(ynn_binary_add, 3204, 6376, 3205);
  g->Binary(ynn_binary_pow, 3205, 6378, 3206);
  g->Binary(ynn_binary_multiply, 3202, 3206, 3207);
  g->Convert(6858, 3209);
  g->Binary(ynn_binary_multiply, 3207, 3209, 3210);
  g->Binary(ynn_binary_add, 3131, 3210, 3211);
}

// Scope: "Layer4 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3211, 3212);
  g->Reduce(ynn_reduce_sum, 3212, 6245, {2}, true);
  g->ShapeProduct(3212, 6244, {2});
  g->Binary(ynn_binary_divide, 6245, 6244, 3213);
  g->Binary(ynn_binary_add, 3213, 6376, 3214);
  g->Binary(ynn_binary_pow, 3214, 6378, 3215);
  g->Binary(ynn_binary_multiply, 3211, 3215, 3216);
  g->Convert(6861, 3217);
  g->Binary(ynn_binary_multiply, 3216, 3217, 3218);
  g->Quantize(3218, 3219, 0.060907524079084396, 0);
  g->Transpose(6855, 5225, {1,0});
  g->Binary(ynn_binary_multiply, 5223, 5224, 5221);
  g->Dot(3219, 5225, YNN_INVALID_VALUE_ID, 5220, 1);
  g->DequantizeTensor(5220, YNN_INVALID_VALUE_ID, 5221, 5222);
  g->QuantizeTensor(5222, 6342, 3649, 3220);
  g->Dequantize(3220, 3221, 0.09251969307661057, 0);
  g->Transpose(6854, 5230, {1,0});
  g->Binary(ynn_binary_multiply, 5223, 5229, 5227);
  g->Dot(3219, 5230, YNN_INVALID_VALUE_ID, 5226, 1);
  g->DequantizeTensor(5226, YNN_INVALID_VALUE_ID, 5227, 5228);
  g->QuantizeTensor(5228, 6342, 3649, 3222);
  g->Dequantize(3222, 3223, 0.09251969307661057, 0);
  g->Polynomial(3223, 6248, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6248, 6249);
  g->Binary(ynn_binary_add, 6249, 5404, 6246);
  g->Binary(ynn_binary_multiply, 3223, 5402, 6247);
  g->Binary(ynn_binary_multiply, 6247, 6246, 3224);
  g->Binary(ynn_binary_multiply, 3221, 3224, 3225);
  g->Quantize(3225, 3226, 0.3444882035255432, 0);
  g->Transpose(6853, 5237, {1,0});
  g->Binary(ynn_binary_multiply, 5234, 5236, 5232);
  g->Dot(3226, 5237, YNN_INVALID_VALUE_ID, 5231, 1);
  g->DequantizeTensor(5231, YNN_INVALID_VALUE_ID, 5232, 5233);
  g->QuantizeTensor(5233, 6342, 5235, 3227);
  g->Dequantize(3227, 3228, 0.13582009077072144, 0);
  g->Unary(ynn_unary_square, 3228, 3229);
  g->Reduce(ynn_reduce_sum, 3229, 6251, {2}, true);
  g->ShapeProduct(3229, 6250, {2});
  g->Binary(ynn_binary_divide, 6251, 6250, 3230);
  g->Binary(ynn_binary_add, 3230, 6376, 3231);
  g->Binary(ynn_binary_pow, 3231, 6378, 3232);
  g->Binary(ynn_binary_multiply, 3228, 3232, 3233);
  g->Convert(6859, 3234);
  g->Binary(ynn_binary_multiply, 3233, 3234, 3235);
  g->Binary(ynn_binary_add, 3211, 3235, 3236);
}

// Scope: "Layer4 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1047, 3237, {0,0,4,0}, {-1,-1,1,-1});
  g->Reshape(3237, 3239, {1,1,256});
  g->Binary(ynn_binary_add, 3239, 6985, 3240);
  g->Binary(ynn_binary_multiply, 3240, 6374, 3241);
  g->Quantize(3236, 3242, 0.41414323449134827, 0);
  g->Transpose(6856, 5243, {1,0});
  g->Binary(ynn_binary_multiply, 5241, 5242, 5239);
  g->Dot(3242, 5243, YNN_INVALID_VALUE_ID, 5238, 1);
  g->DequantizeTensor(5238, YNN_INVALID_VALUE_ID, 5239, 5240);
  g->QuantizeTensor(5240, 6342, 5075, 3243);
  g->Dequantize(3243, 3244, 0.039862215518951416, 0);
  g->Polynomial(3244, 6254, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6254, 6255);
  g->Binary(ynn_binary_add, 6255, 5404, 6252);
  g->Binary(ynn_binary_multiply, 3244, 5402, 6253);
  g->Binary(ynn_binary_multiply, 6253, 6252, 3245);
  g->Binary(ynn_binary_multiply, 3245, 3241, 3246);
  g->Quantize(3246, 3247, 0.30314961075782776, 0);
  g->Transpose(6857, 5250, {1,0});
  g->Binary(ynn_binary_multiply, 5247, 5249, 5245);
  g->Dot(3247, 5250, YNN_INVALID_VALUE_ID, 5244, 1);
  g->DequantizeTensor(5244, YNN_INVALID_VALUE_ID, 5245, 5246);
  g->QuantizeTensor(5246, 6342, 5248, 3248);
  g->Dequantize(3248, 3249, 0.16701875627040863, 0);
  g->Unary(ynn_unary_square, 3249, 3250);
  g->Reduce(ynn_reduce_sum, 3250, 6257, {2}, true);
  g->ShapeProduct(3250, 6256, {2});
  g->Binary(ynn_binary_divide, 6257, 6256, 3251);
  g->Binary(ynn_binary_add, 3251, 6376, 3252);
  g->Binary(ynn_binary_pow, 3252, 6378, 3253);
  g->Binary(ynn_binary_multiply, 3249, 3253, 3254);
  g->Convert(6860, 3255);
  g->Binary(ynn_binary_multiply, 3254, 3255, 3256);
  g->Binary(ynn_binary_add, 3236, 3256, 3257);
  g->Convert(6852, 3258);
  g->Binary(ynn_binary_multiply, 3257, 3258, 3260);
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
  g->Quantize(3267, 3268, 0.07399173825979233, 0);
  g->Transpose(6880, 5263, {1,0});
  g->Binary(ynn_binary_multiply, 5260, 5262, 5258);
  g->Dot(3268, 5263, YNN_INVALID_VALUE_ID, 5257, 1);
  g->DequantizeTensor(5257, YNN_INVALID_VALUE_ID, 5258, 5259);
  g->QuantizeTensor(5259, 6342, 5261, 3269);
  g->Dequantize(3269, 3271, 0.09842520207166672, 0);
  g->Reshape(3271, 3272, {1,1,1,256});
  g->Transpose(3272, 3273, {0,2,1,3});
  g->Unary(ynn_unary_square, 3273, 3274);
  g->Reduce(ynn_reduce_sum, 3274, 6261, {3}, true);
  g->ShapeProduct(3274, 6260, {3});
  g->Binary(ynn_binary_divide, 6261, 6260, 3275);
  g->Binary(ynn_binary_add, 3275, 6376, 3276);
  g->Binary(ynn_binary_pow, 3276, 6378, 3277);
  g->Binary(ynn_binary_multiply, 3273, 3277, 3278);
  g->Convert(6879, 3279);
  g->Binary(ynn_binary_multiply, 3278, 3279, 3280);
  g->Slice(3280, 3282, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3280, 3283, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3283, 3284);
  g->Concat({3284,3282}, 3285, 3);
  g->Binary(ynn_binary_multiply, 3280, 2133, 3286);
  g->Binary(ynn_binary_multiply, 3285, 2992, 3287);
  g->Binary(ynn_binary_add, 3286, 3287, 3288);
  g->Transpose(6884, 5268, {1,0});
  g->Binary(ynn_binary_multiply, 5260, 5267, 5265);
  g->Dot(3268, 5268, YNN_INVALID_VALUE_ID, 5264, 1);
  g->DequantizeTensor(5264, YNN_INVALID_VALUE_ID, 5265, 5266);
  g->QuantizeTensor(5266, 6342, 5261, 3289);
  g->Dequantize(3289, 3290, 0.09842520207166672, 0);
  g->Reshape(3290, 3292, {1,1,1,256});
  g->Transpose(3292, 3293, {0,2,1,3});
  g->Unary(ynn_unary_square, 3293, 3294);
  g->Reduce(ynn_reduce_sum, 3294, 6263, {3}, true);
  g->ShapeProduct(3294, 6262, {3});
  g->Binary(ynn_binary_divide, 6263, 6262, 3295);
  g->Binary(ynn_binary_add, 3295, 6376, 3296);
  g->Binary(ynn_binary_pow, 3296, 6378, 3297);
  g->Binary(ynn_binary_multiply, 3293, 3297, 3298);
}

// Scope: "Layer5 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(3288, 3299, 0.006011798977851868, 0);
  g->Append(6353, 3299, 7002, 2, s2, slinky::expr(int64_t{1}));
  g->View(7002, 7032, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7032, 3302, 0.006011798977851868, 0);
  g->Quantize(3298, 3303, 0.047244105488061905, 0);
  g->Append(6368, 3303, 7017, 2, s2, slinky::expr(int64_t{1}));
  g->View(7017, 7047, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7047, 3304, 0.047244105488061905, 0);
}

// Scope: "Layer5 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(6883, 5273, {1,0});
  g->Binary(ynn_binary_multiply, 5260, 5272, 5270);
  g->Dot(3268, 5273, YNN_INVALID_VALUE_ID, 5269, 1);
  g->DequantizeTensor(5269, YNN_INVALID_VALUE_ID, 5270, 5271);
  g->QuantizeTensor(5271, 6342, 4026, 3305);
  g->Dequantize(3305, 3306, 0.13385827839374542, 0);
  g->SplitDim(3306, 3307, 2, {8,256});
  g->Transpose(3307, 3308, {0,2,1,3});
  g->Unary(ynn_unary_square, 3308, 3310);
  g->Reduce(ynn_reduce_sum, 3310, 6267, {3}, true);
  g->ShapeProduct(3310, 6266, {3});
  g->Binary(ynn_binary_divide, 6267, 6266, 3311);
  g->Binary(ynn_binary_add, 3311, 6376, 3312);
  g->Binary(ynn_binary_pow, 3312, 6378, 3313);
  g->Binary(ynn_binary_multiply, 3308, 3313, 3314);
  g->Convert(6882, 3315);
  g->Binary(ynn_binary_multiply, 3314, 3315, 3316);
  g->Slice(3316, 3317, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3316, 3318, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3318, 3319);
  g->Concat({3319,3317}, 3321, 3);
  g->Binary(ynn_binary_multiply, 3316, 2133, 3322);
  g->Binary(ynn_binary_multiply, 3321, 2992, 3323);
  g->Binary(ynn_binary_add, 3322, 3323, 3324);
}

// Scope: "Layer5 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(3324, 3302, 3325, false, true);
  g->Mask(3325, 6413, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6413, 6271, {-1}, true);
  g->Binary(ynn_binary_subtract, 6413, 6271, 6268);
  g->Unary(ynn_unary_exp, 6268, 6269);
  g->Reduce(ynn_reduce_sum, 6269, 6272, {-1}, true);
  g->Binary(ynn_binary_divide, 5404, 6272, 6270);
  g->Binary(ynn_binary_multiply, 6269, 6270, 3326);
  g->Matmul(3326, 3304, 3327, false, false);
}

// Scope: "Layer5 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(3327, 3328, {0,2,1,3});
  g->FuseDims(3328, 3329, 2, 2);
  g->Quantize(3329, 3331, 0.026451781392097473, 0);
  g->Transpose(6881, 5280, {1,0});
  g->Binary(ynn_binary_multiply, 5277, 5279, 5275);
  g->Dot(3331, 5280, YNN_INVALID_VALUE_ID, 5274, 1);
  g->DequantizeTensor(5274, YNN_INVALID_VALUE_ID, 5275, 5276);
  g->QuantizeTensor(5276, 6342, 5278, 3332);
  g->Dequantize(3332, 3333, 0.043322544544935226, 0);
}

// Scope: "Layer5 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3260, 3261);
  g->Reduce(ynn_reduce_sum, 3261, 6259, {2}, true);
  g->ShapeProduct(3261, 6258, {2});
  g->Binary(ynn_binary_divide, 6259, 6258, 3262);
  g->Binary(ynn_binary_add, 3262, 6376, 3263);
  g->Binary(ynn_binary_pow, 3263, 6378, 3264);
  g->Binary(ynn_binary_multiply, 3260, 3264, 3265);
  g->Convert(6868, 3266);
  g->Binary(ynn_binary_multiply, 3265, 3266, 3267);
  BuildLayer5AttentionKvProjection(ctx);
  BuildLayer5AttentionCacheUpdate(ctx);
  BuildLayer5AttentionQueryProjection(ctx);
  BuildLayer5AttentionSdpa(ctx);
  BuildLayer5AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 3333, 3334);
  g->Reduce(ynn_reduce_sum, 3334, 6274, {2}, true);
  g->ShapeProduct(3334, 6273, {2});
  g->Binary(ynn_binary_divide, 6274, 6273, 3335);
  g->Binary(ynn_binary_add, 3335, 6376, 3336);
  g->Binary(ynn_binary_pow, 3336, 6378, 3337);
  g->Binary(ynn_binary_multiply, 3333, 3337, 3338);
  g->Convert(6875, 3339);
  g->Binary(ynn_binary_multiply, 3338, 3339, 3340);
  g->Binary(ynn_binary_add, 3260, 3340, 3342);
}

// Scope: "Layer5 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3342, 3343);
  g->Reduce(ynn_reduce_sum, 3343, 6276, {2}, true);
  g->ShapeProduct(3343, 6275, {2});
  g->Binary(ynn_binary_divide, 6276, 6275, 3344);
  g->Binary(ynn_binary_add, 3344, 6376, 3345);
  g->Binary(ynn_binary_pow, 3345, 6378, 3346);
  g->Binary(ynn_binary_multiply, 3342, 3346, 3347);
  g->Convert(6878, 3348);
  g->Binary(ynn_binary_multiply, 3347, 3348, 3349);
  g->Quantize(3349, 3350, 0.03518042340874672, 0);
  g->Transpose(6872, 5286, {1,0});
  g->Binary(ynn_binary_multiply, 5284, 5285, 5282);
  g->Dot(3350, 5286, YNN_INVALID_VALUE_ID, 5281, 1);
  g->DequantizeTensor(5281, YNN_INVALID_VALUE_ID, 5282, 5283);
  g->QuantizeTensor(5283, 6342, 4487, 3351);
  g->Dequantize(3351, 3353, 0.03567914664745331, 0);
  g->Transpose(6871, 5291, {1,0});
  g->Binary(ynn_binary_multiply, 5284, 5290, 5288);
  g->Dot(3350, 5291, YNN_INVALID_VALUE_ID, 5287, 1);
  g->DequantizeTensor(5287, YNN_INVALID_VALUE_ID, 5288, 5289);
  g->QuantizeTensor(5289, 6342, 4487, 3354);
  g->Dequantize(3354, 3355, 0.03567914664745331, 0);
  g->Polynomial(3355, 6279, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6279, 6280);
  g->Binary(ynn_binary_add, 6280, 5404, 6277);
  g->Binary(ynn_binary_multiply, 3355, 5402, 6278);
  g->Binary(ynn_binary_multiply, 6278, 6277, 3356);
  g->Binary(ynn_binary_multiply, 3353, 3356, 3357);
  g->Quantize(3357, 3358, 0.08415354788303375, 0);
  g->Transpose(6870, 5298, {1,0});
  g->Binary(ynn_binary_multiply, 5295, 5297, 5293);
  g->Dot(3358, 5298, YNN_INVALID_VALUE_ID, 5292, 1);
  g->DequantizeTensor(5292, YNN_INVALID_VALUE_ID, 5293, 5294);
  g->QuantizeTensor(5294, 6342, 5296, 3359);
  g->Dequantize(3359, 3360, 0.06301677227020264, 0);
  g->Unary(ynn_unary_square, 3360, 3361);
  g->Reduce(ynn_reduce_sum, 3361, 6282, {2}, true);
  g->ShapeProduct(3361, 6281, {2});
  g->Binary(ynn_binary_divide, 6282, 6281, 3363);
  g->Binary(ynn_binary_add, 3363, 6376, 3364);
  g->Binary(ynn_binary_pow, 3364, 6378, 3365);
  g->Binary(ynn_binary_multiply, 3360, 3365, 3366);
  g->Convert(6876, 3367);
  g->Binary(ynn_binary_multiply, 3366, 3367, 3368);
  g->Binary(ynn_binary_add, 3342, 3368, 3369);
}

// Scope: "Layer5 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1047, 3370, {0,0,5,0}, {-1,-1,1,-1});
  g->Reshape(3370, 3371, {1,1,256});
  g->Binary(ynn_binary_add, 3371, 6986, 3372);
  g->Binary(ynn_binary_multiply, 3372, 6374, 3374);
  g->Quantize(3369, 3375, 0.3165745139122009, 0);
  g->Transpose(6873, 5305, {1,0});
  g->Binary(ynn_binary_multiply, 5302, 5304, 5300);
  g->Dot(3375, 5305, YNN_INVALID_VALUE_ID, 5299, 1);
  g->DequantizeTensor(5299, YNN_INVALID_VALUE_ID, 5300, 5301);
  g->QuantizeTensor(5301, 6342, 5303, 3376);
  g->Dequantize(3376, 3377, 0.0393700897693634, 0);
  g->Polynomial(3377, 6285, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6285, 6286);
  g->Binary(ynn_binary_add, 6286, 5404, 6283);
  g->Binary(ynn_binary_multiply, 3377, 5402, 6284);
  g->Binary(ynn_binary_multiply, 6284, 6283, 3378);
  g->Binary(ynn_binary_multiply, 3378, 3374, 3379);
  g->Quantize(3379, 3380, 0.22933071851730347, 0);
  g->Transpose(6874, 5312, {1,0});
  g->Binary(ynn_binary_multiply, 5309, 5311, 5307);
  g->Dot(3380, 5312, YNN_INVALID_VALUE_ID, 5306, 1);
  g->DequantizeTensor(5306, YNN_INVALID_VALUE_ID, 5307, 5308);
  g->QuantizeTensor(5308, 6342, 5310, 3381);
  g->Dequantize(3381, 3382, 0.12322933226823807, 0);
  g->Unary(ynn_unary_square, 3382, 3383);
  g->Reduce(ynn_reduce_sum, 3383, 6288, {2}, true);
  g->ShapeProduct(3383, 6287, {2});
  g->Binary(ynn_binary_divide, 6288, 6287, 3385);
  g->Binary(ynn_binary_add, 3385, 6376, 3386);
  g->Binary(ynn_binary_pow, 3386, 6378, 3387);
  g->Binary(ynn_binary_multiply, 3382, 3387, 3388);
  g->Convert(6877, 3389);
  g->Binary(ynn_binary_multiply, 3388, 3389, 3390);
  g->Binary(ynn_binary_add, 3369, 3390, 3391);
  g->Convert(6869, 3392);
  g->Binary(ynn_binary_multiply, 3391, 3392, 3393);
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
  g->Quantize(3401, 3402, 0.341854453086853, 0);
  g->Transpose(6897, 5319, {1,0});
  g->Binary(ynn_binary_multiply, 5316, 5318, 5314);
  g->Dot(3402, 5319, YNN_INVALID_VALUE_ID, 5313, 1);
  g->DequantizeTensor(5313, YNN_INVALID_VALUE_ID, 5314, 5315);
  g->QuantizeTensor(5315, 6342, 5317, 3403);
  g->Dequantize(3403, 3404, 0.28740158677101135, 0);
  g->Reshape(3404, 3405, {1,1,1,256});
  g->Transpose(3405, 3408, {0,2,1,3});
  g->Unary(ynn_unary_square, 3408, 3409);
  g->Reduce(ynn_reduce_sum, 3409, 6292, {3}, true);
  g->ShapeProduct(3409, 6291, {3});
  g->Binary(ynn_binary_divide, 6292, 6291, 3410);
  g->Binary(ynn_binary_add, 3410, 6376, 3411);
  g->Binary(ynn_binary_pow, 3411, 6378, 3412);
  g->Binary(ynn_binary_multiply, 3408, 3412, 3413);
  g->Convert(6896, 3414);
  g->Binary(ynn_binary_multiply, 3413, 3414, 3415);
  g->Slice(3415, 3416, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3415, 3417, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3417, 3419);
  g->Concat({3419,3416}, 3420, 3);
  g->Binary(ynn_binary_multiply, 3415, 2133, 3421);
  g->Binary(ynn_binary_multiply, 3420, 2992, 3422);
  g->Binary(ynn_binary_add, 3421, 3422, 3423);
  g->Transpose(6901, 5324, {1,0});
  g->Binary(ynn_binary_multiply, 5316, 5323, 5321);
  g->Dot(3402, 5324, YNN_INVALID_VALUE_ID, 5320, 1);
  g->DequantizeTensor(5320, YNN_INVALID_VALUE_ID, 5321, 5322);
  g->QuantizeTensor(5322, 6342, 5317, 3424);
  g->Dequantize(3424, 3425, 0.28740158677101135, 0);
  g->Reshape(3425, 3426, {1,1,1,256});
  g->Transpose(3426, 3427, {0,2,1,3});
  g->Unary(ynn_unary_square, 3427, 3429);
  g->Reduce(ynn_reduce_sum, 3429, 6294, {3}, true);
  g->ShapeProduct(3429, 6293, {3});
  g->Binary(ynn_binary_divide, 6294, 6293, 3430);
  g->Binary(ynn_binary_add, 3430, 6376, 3431);
  g->Binary(ynn_binary_pow, 3431, 6378, 3432);
  g->Binary(ynn_binary_multiply, 3427, 3432, 3433);
}

// Scope: "Layer6 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(3423, 3434, 0.0057707298547029495, 0);
  g->Append(6354, 3434, 7003, 2, s2, slinky::expr(int64_t{1}));
  g->View(7003, 7033, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7033, 3435, 0.0057707298547029495, 0);
  g->Quantize(3433, 3436, 0.047244105488061905, 0);
  g->Append(6369, 3436, 7018, 2, s2, slinky::expr(int64_t{1}));
  g->View(7018, 7048, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7048, 3438, 0.047244105488061905, 0);
}

// Scope: "Layer6 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(6900, 5330, {1,0});
  g->Binary(ynn_binary_multiply, 5316, 5329, 5326);
  g->Dot(3402, 5330, YNN_INVALID_VALUE_ID, 5325, 1);
  g->DequantizeTensor(5325, YNN_INVALID_VALUE_ID, 5326, 5327);
  g->QuantizeTensor(5327, 6342, 5328, 3439);
  g->Dequantize(3439, 3440, 0.4566929042339325, 0);
  g->SplitDim(3440, 3441, 2, {8,256});
  g->Transpose(3441, 3442, {0,2,1,3});
  g->Unary(ynn_unary_square, 3442, 3443);
  g->Reduce(ynn_reduce_sum, 3443, 6296, {3}, true);
  g->ShapeProduct(3443, 6295, {3});
  g->Binary(ynn_binary_divide, 6296, 6295, 3444);
  g->Binary(ynn_binary_add, 3444, 6376, 3446);
  g->Binary(ynn_binary_pow, 3446, 6378, 3447);
  g->Binary(ynn_binary_multiply, 3442, 3447, 3448);
  g->Convert(6899, 3449);
  g->Binary(ynn_binary_multiply, 3448, 3449, 3450);
  g->Slice(3450, 3451, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3450, 3452, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3452, 3453);
  g->Concat({3453,3451}, 3454, 3);
  g->Binary(ynn_binary_multiply, 3450, 2133, 3455);
  g->Binary(ynn_binary_multiply, 3454, 2992, 3456);
  g->Binary(ynn_binary_add, 3455, 3456, 3457);
}

// Scope: "Layer6 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(3457, 3435, 3458, false, true);
  g->Mask(3458, 6414, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6414, 6300, {-1}, true);
  g->Binary(ynn_binary_subtract, 6414, 6300, 6297);
  g->Unary(ynn_unary_exp, 6297, 6298);
  g->Reduce(ynn_reduce_sum, 6298, 6301, {-1}, true);
  g->Binary(ynn_binary_divide, 5404, 6301, 6299);
  g->Binary(ynn_binary_multiply, 6298, 6299, 3459);
  g->Matmul(3459, 3438, 3460, false, false);
}

// Scope: "Layer6 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(3460, 3461, {0,2,1,3});
  g->FuseDims(3461, 3462, 2, 2);
  g->Quantize(3462, 3463, 0.0354330837726593, 0);
  g->Transpose(6898, 5337, {1,0});
  g->Binary(ynn_binary_multiply, 5334, 5336, 5332);
  g->Dot(3463, 5337, YNN_INVALID_VALUE_ID, 5331, 1);
  g->DequantizeTensor(5331, YNN_INVALID_VALUE_ID, 5332, 5333);
  g->QuantizeTensor(5333, 6342, 5335, 3464);
  g->Dequantize(3464, 3466, 0.05930274724960327, 0);
}

// Scope: "Layer6 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3393, 3394);
  g->Reduce(ynn_reduce_sum, 3394, 6290, {2}, true);
  g->ShapeProduct(3394, 6289, {2});
  g->Binary(ynn_binary_divide, 6290, 6289, 3396);
  g->Binary(ynn_binary_add, 3396, 6376, 3397);
  g->Binary(ynn_binary_pow, 3397, 6378, 3398);
  g->Binary(ynn_binary_multiply, 3393, 3398, 3399);
  g->Convert(6885, 3400);
  g->Binary(ynn_binary_multiply, 3399, 3400, 3401);
  BuildLayer6AttentionKvProjection(ctx);
  BuildLayer6AttentionCacheUpdate(ctx);
  BuildLayer6AttentionQueryProjection(ctx);
  BuildLayer6AttentionSdpa(ctx);
  BuildLayer6AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 3466, 3467);
  g->Reduce(ynn_reduce_sum, 3467, 6308, {2}, true);
  g->ShapeProduct(3467, 6307, {2});
  g->Binary(ynn_binary_divide, 6308, 6307, 3468);
  g->Binary(ynn_binary_add, 3468, 6376, 3469);
  g->Binary(ynn_binary_pow, 3469, 6378, 3470);
  g->Binary(ynn_binary_multiply, 3466, 3470, 3471);
  g->Convert(6892, 3472);
  g->Binary(ynn_binary_multiply, 3471, 3472, 3473);
  g->Binary(ynn_binary_add, 3393, 3473, 3474);
}

// Scope: "Layer6 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3474, 3475);
  g->Reduce(ynn_reduce_sum, 3475, 6310, {2}, true);
  g->ShapeProduct(3475, 6309, {2});
  g->Binary(ynn_binary_divide, 6310, 6309, 3477);
  g->Binary(ynn_binary_add, 3477, 6376, 3478);
  g->Binary(ynn_binary_pow, 3478, 6378, 3479);
  g->Binary(ynn_binary_multiply, 3474, 3479, 3480);
  g->Convert(6895, 3481);
  g->Binary(ynn_binary_multiply, 3480, 3481, 3482);
  g->Quantize(3482, 3483, 0.02705955132842064, 0);
  g->Transpose(6889, 5344, {1,0});
  g->Binary(ynn_binary_multiply, 5341, 5343, 5339);
  g->Dot(3483, 5344, YNN_INVALID_VALUE_ID, 5338, 1);
  g->DequantizeTensor(5338, YNN_INVALID_VALUE_ID, 5339, 5340);
  g->QuantizeTensor(5340, 6342, 5342, 3484);
  g->Dequantize(3484, 3485, 0.02632874995470047, 0);
  g->Transpose(6888, 5349, {1,0});
  g->Binary(ynn_binary_multiply, 5341, 5348, 5346);
  g->Dot(3483, 5349, YNN_INVALID_VALUE_ID, 5345, 1);
  g->DequantizeTensor(5345, YNN_INVALID_VALUE_ID, 5346, 5347);
  g->QuantizeTensor(5347, 6342, 5342, 3487);
  g->Dequantize(3487, 3488, 0.02632874995470047, 0);
  g->Polynomial(3488, 6313, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6313, 6314);
  g->Binary(ynn_binary_add, 6314, 5404, 6311);
  g->Binary(ynn_binary_multiply, 3488, 5402, 6312);
  g->Binary(ynn_binary_multiply, 6312, 6311, 3489);
  g->Binary(ynn_binary_multiply, 3485, 3489, 3490);
  g->Quantize(3490, 3491, 0.039862215518951416, 0);
  g->Transpose(6887, 5355, {1,0});
  g->Binary(ynn_binary_multiply, 5075, 5354, 5351);
  g->Dot(3491, 5355, YNN_INVALID_VALUE_ID, 5350, 1);
  g->DequantizeTensor(5350, YNN_INVALID_VALUE_ID, 5351, 5352);
  g->QuantizeTensor(5352, 6342, 5353, 3492);
  g->Dequantize(3492, 3493, 0.019578030332922935, 0);
  g->Unary(ynn_unary_square, 3493, 3494);
  g->Reduce(ynn_reduce_sum, 3494, 6316, {2}, true);
  g->ShapeProduct(3494, 6315, {2});
  g->Binary(ynn_binary_divide, 6316, 6315, 3495);
  g->Binary(ynn_binary_add, 3495, 6376, 3496);
  g->Binary(ynn_binary_pow, 3496, 6378, 3498);
  g->Binary(ynn_binary_multiply, 3493, 3498, 3499);
  g->Convert(6893, 3500);
  g->Binary(ynn_binary_multiply, 3499, 3500, 3501);
  g->Binary(ynn_binary_add, 3474, 3501, 3502);
}

// Scope: "Layer6 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1047, 3503, {0,0,6,0}, {-1,-1,1,-1});
  g->Reshape(3503, 3504, {1,1,256});
  g->Binary(ynn_binary_add, 3504, 6987, 3505);
  g->Binary(ynn_binary_multiply, 3505, 6374, 3506);
  g->Quantize(3502, 3507, 0.34014976024627686, 0);
  g->Transpose(6890, 5362, {1,0});
  g->Binary(ynn_binary_multiply, 5359, 5361, 5357);
  g->Dot(3507, 5362, YNN_INVALID_VALUE_ID, 5356, 1);
  g->DequantizeTensor(5356, YNN_INVALID_VALUE_ID, 5357, 5358);
  g->QuantizeTensor(5358, 6342, 5360, 3510);
  g->Dequantize(3510, 3511, 0.04773623123764992, 0);
  g->Polynomial(3511, 6319, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6319, 6320);
  g->Binary(ynn_binary_add, 6320, 5404, 6317);
  g->Binary(ynn_binary_multiply, 3511, 5402, 6318);
  g->Binary(ynn_binary_multiply, 6318, 6317, 3512);
  g->Binary(ynn_binary_multiply, 3512, 3506, 3513);
  g->Quantize(3513, 3514, 0.12450788170099258, 0);
  g->Transpose(6891, 5368, {1,0});
  g->Binary(ynn_binary_multiply, 3970, 5367, 5364);
  g->Dot(3514, 5368, YNN_INVALID_VALUE_ID, 5363, 1);
  g->DequantizeTensor(5363, YNN_INVALID_VALUE_ID, 5364, 5365);
  g->QuantizeTensor(5365, 6342, 5366, 3515);
  g->Dequantize(3515, 3516, 0.07488936185836792, 0);
  g->Unary(ynn_unary_square, 3516, 3517);
  g->Reduce(ynn_reduce_sum, 3517, 6322, {2}, true);
  g->ShapeProduct(3517, 6321, {2});
  g->Binary(ynn_binary_divide, 6322, 6321, 3518);
  g->Binary(ynn_binary_add, 3518, 6376, 3519);
  g->Binary(ynn_binary_pow, 3519, 6378, 3521);
  g->Binary(ynn_binary_multiply, 3516, 3521, 3522);
  g->Convert(6894, 3523);
  g->Binary(ynn_binary_multiply, 3522, 3523, 3524);
  g->Binary(ynn_binary_add, 3502, 3524, 3525);
  g->Convert(6886, 3526);
  g->Binary(ynn_binary_multiply, 3525, 3526, 3527);
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
  g->Quantize(3535, 3536, 0.29519250988960266, 0);
  g->Transpose(6914, 5382, {1,0});
  g->Binary(ynn_binary_multiply, 5379, 5381, 5377);
  g->Dot(3536, 5382, YNN_INVALID_VALUE_ID, 5376, 1);
  g->DequantizeTensor(5376, YNN_INVALID_VALUE_ID, 5377, 5378);
  g->QuantizeTensor(5378, 6342, 5380, 3537);
  g->Dequantize(3537, 3538, 0.3681102395057678, 0);
  g->Reshape(3538, 3539, {1,1,1,256});
  g->Transpose(3539, 3540, {0,2,1,3});
  g->Unary(ynn_unary_square, 3540, 3541);
  g->Reduce(ynn_reduce_sum, 3541, 6326, {3}, true);
  g->ShapeProduct(3541, 6325, {3});
  g->Binary(ynn_binary_divide, 6326, 6325, 3543);
  g->Binary(ynn_binary_add, 3543, 6376, 3544);
  g->Binary(ynn_binary_pow, 3544, 6378, 3545);
  g->Binary(ynn_binary_multiply, 3540, 3545, 3546);
  g->Convert(6913, 3547);
  g->Binary(ynn_binary_multiply, 3546, 3547, 3548);
  g->Slice(3548, 3549, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3548, 3550, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3550, 3551);
  g->Concat({3551,3549}, 3552, 3);
  g->Binary(ynn_binary_multiply, 3548, 2133, 3554);
  g->Binary(ynn_binary_multiply, 3552, 2992, 3555);
  g->Binary(ynn_binary_add, 3554, 3555, 3556);
  g->Transpose(6918, 5387, {1,0});
  g->Binary(ynn_binary_multiply, 5379, 5386, 5384);
  g->Dot(3536, 5387, YNN_INVALID_VALUE_ID, 5383, 1);
  g->DequantizeTensor(5383, YNN_INVALID_VALUE_ID, 5384, 5385);
  g->QuantizeTensor(5385, 6342, 5380, 3557);
  g->Dequantize(3557, 3558, 0.3681102395057678, 0);
  g->Reshape(3558, 3559, {1,1,1,256});
  g->Transpose(3559, 3560, {0,2,1,3});
  g->Unary(ynn_unary_square, 3560, 3561);
  g->Reduce(ynn_reduce_sum, 3561, 6330, {3}, true);
  g->ShapeProduct(3561, 6329, {3});
  g->Binary(ynn_binary_divide, 6330, 6329, 3562);
  g->Binary(ynn_binary_add, 3562, 6376, 3564);
  g->Binary(ynn_binary_pow, 3564, 6378, 3565);
  g->Binary(ynn_binary_multiply, 3560, 3565, 3566);
}

// Scope: "Layer7 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(3556, 3567, 0.005869260523468256, 0);
  g->Append(6355, 3567, 7004, 2, s2, slinky::expr(int64_t{1}));
  g->View(7004, 7034, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7034, 3568, 0.005869260523468256, 0);
  g->Quantize(3566, 3569, 0.047244105488061905, 0);
  g->Append(6370, 3569, 7019, 2, s2, slinky::expr(int64_t{1}));
  g->View(7019, 7049, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(7049, 3571, 0.047244105488061905, 0);
}

// Scope: "Layer7 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(6917, 5393, {1,0});
  g->Binary(ynn_binary_multiply, 5379, 5392, 5389);
  g->Dot(3536, 5393, YNN_INVALID_VALUE_ID, 5388, 1);
  g->DequantizeTensor(5388, YNN_INVALID_VALUE_ID, 5389, 5390);
  g->QuantizeTensor(5390, 6342, 5391, 3572);
  g->Dequantize(3572, 3573, 0.31496062874794006, 0);
  g->SplitDim(3573, 3574, 2, {8,256});
  g->Transpose(3574, 3575, {0,2,1,3});
  g->Unary(ynn_unary_square, 3575, 3576);
  g->Reduce(ynn_reduce_sum, 3576, 6332, {3}, true);
  g->ShapeProduct(3576, 6331, {3});
  g->Binary(ynn_binary_divide, 6332, 6331, 3577);
  g->Binary(ynn_binary_add, 3577, 6376, 3578);
  g->Binary(ynn_binary_pow, 3578, 6378, 3579);
  g->Binary(ynn_binary_multiply, 3575, 3579, 3581);
  g->Convert(6916, 3582);
  g->Binary(ynn_binary_multiply, 3581, 3582, 3583);
  g->Slice(3583, 3584, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3583, 3585, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3585, 3586);
  g->Concat({3586,3584}, 3587, 3);
  g->Binary(ynn_binary_multiply, 3583, 2133, 3588);
  g->Binary(ynn_binary_multiply, 3587, 2992, 3589);
  g->Binary(ynn_binary_add, 3588, 3589, 3590);
}

// Scope: "Layer7 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(3590, 3568, 3592, false, true);
  g->Mask(3592, 6415, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6415, 6336, {-1}, true);
  g->Binary(ynn_binary_subtract, 6415, 6336, 6333);
  g->Unary(ynn_unary_exp, 6333, 6334);
  g->Reduce(ynn_reduce_sum, 6334, 6337, {-1}, true);
  g->Binary(ynn_binary_divide, 5404, 6337, 6335);
  g->Binary(ynn_binary_multiply, 6334, 6335, 3593);
  g->Matmul(3593, 3571, 3594, false, false);
}

// Scope: "Layer7 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(3594, 3595, {0,2,1,3});
  g->FuseDims(3595, 3596, 2, 2);
  g->Quantize(3596, 3597, 0.028912410140037537, 0);
  g->Transpose(6915, 5400, {1,0});
  g->Binary(ynn_binary_multiply, 5397, 5399, 5395);
  g->Dot(3597, 5400, YNN_INVALID_VALUE_ID, 5394, 1);
  g->DequantizeTensor(5394, YNN_INVALID_VALUE_ID, 5395, 5396);
  g->QuantizeTensor(5396, 6342, 5398, 3598);
  g->Dequantize(3598, 3599, 0.025238478556275368, 0);
}

// Scope: "Layer7 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3527, 3528);
  g->Reduce(ynn_reduce_sum, 3528, 6324, {2}, true);
  g->ShapeProduct(3528, 6323, {2});
  g->Binary(ynn_binary_divide, 6324, 6323, 3529);
  g->Binary(ynn_binary_add, 3529, 6376, 3530);
  g->Binary(ynn_binary_pow, 3530, 6378, 3532);
  g->Binary(ynn_binary_multiply, 3527, 3532, 3533);
  g->Convert(6902, 3534);
  g->Binary(ynn_binary_multiply, 3533, 3534, 3535);
  BuildLayer7AttentionKvProjection(ctx);
  BuildLayer7AttentionCacheUpdate(ctx);
  BuildLayer7AttentionQueryProjection(ctx);
  BuildLayer7AttentionSdpa(ctx);
  BuildLayer7AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 3599, 3600);
  g->Reduce(ynn_reduce_sum, 3600, 6339, {2}, true);
  g->ShapeProduct(3600, 6338, {2});
  g->Binary(ynn_binary_divide, 6339, 6338, 3602);
  g->Binary(ynn_binary_add, 3602, 6376, 3603);
  g->Binary(ynn_binary_pow, 3603, 6378, 3604);
  g->Binary(ynn_binary_multiply, 3599, 3604, 3605);
  g->Convert(6909, 3606);
  g->Binary(ynn_binary_multiply, 3605, 3606, 3607);
  g->Binary(ynn_binary_add, 3527, 3607, 3608);
}

// Scope: "Layer7 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3608, 3609);
  g->Reduce(ynn_reduce_sum, 3609, 6341, {2}, true);
  g->ShapeProduct(3609, 6340, {2});
  g->Binary(ynn_binary_divide, 6341, 6340, 3610);
  g->Binary(ynn_binary_add, 3610, 6376, 3611);
  g->Binary(ynn_binary_pow, 3611, 6378, 4);
  g->Binary(ynn_binary_multiply, 3608, 4, 5);
  g->Convert(6912, 6);
  g->Binary(ynn_binary_multiply, 5, 6, 7);
  g->Quantize(7, 8, 0.023717211559414864, 0);
  g->Transpose(6906, 3618, {1,0});
  g->Binary(ynn_binary_multiply, 3615, 3617, 3613);
  g->Dot(8, 3618, YNN_INVALID_VALUE_ID, 3612, 1);
  g->DequantizeTensor(3612, YNN_INVALID_VALUE_ID, 3613, 3614);
  g->QuantizeTensor(3614, 6342, 3616, 9);
  g->Dequantize(9, 10, 0.021899616345763206, 0);
  g->Transpose(6905, 3623, {1,0});
  g->Binary(ynn_binary_multiply, 3615, 3622, 3620);
  g->Dot(8, 3623, YNN_INVALID_VALUE_ID, 3619, 1);
  g->DequantizeTensor(3619, YNN_INVALID_VALUE_ID, 3620, 3621);
  g->QuantizeTensor(3621, 6342, 3616, 11);
  g->Dequantize(11, 12, 0.021899616345763206, 0);
  g->Polynomial(12, 5405, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5405, 5406);
  g->Binary(ynn_binary_add, 5406, 5404, 5401);
  g->Binary(ynn_binary_multiply, 12, 5402, 5403);
  g->Binary(ynn_binary_multiply, 5403, 5401, 14);
  g->Binary(ynn_binary_multiply, 10, 14, 15);
  g->Quantize(15, 16, 0.02202264778316021, 0);
  g->Transpose(6904, 3630, {1,0});
  g->Binary(ynn_binary_multiply, 3627, 3629, 3625);
  g->Dot(16, 3630, YNN_INVALID_VALUE_ID, 3624, 1);
  g->DequantizeTensor(3624, YNN_INVALID_VALUE_ID, 3625, 3626);
  g->QuantizeTensor(3626, 6342, 3628, 17);
  g->Dequantize(17, 18, 0.01081059779971838, 0);
  g->Unary(ynn_unary_square, 18, 19);
  g->Reduce(ynn_reduce_sum, 19, 5408, {2}, true);
  g->ShapeProduct(19, 5407, {2});
  g->Binary(ynn_binary_divide, 5408, 5407, 20);
  g->Binary(ynn_binary_add, 20, 6376, 21);
  g->Binary(ynn_binary_pow, 21, 6378, 22);
  g->Binary(ynn_binary_multiply, 18, 22, 23);
  g->Convert(6910, 25);
  g->Binary(ynn_binary_multiply, 23, 25, 26);
  g->Binary(ynn_binary_add, 3608, 26, 27);
}

// Scope: "Layer7 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1047, 28, {0,0,7,0}, {-1,-1,1,-1});
  g->Reshape(28, 29, {1,1,256});
  g->Binary(ynn_binary_add, 29, 6988, 30);
  g->Binary(ynn_binary_multiply, 30, 6374, 31);
  g->Quantize(27, 32, 0.15832224488258362, 0);
  g->Transpose(6907, 3637, {1,0});
  g->Binary(ynn_binary_multiply, 3634, 3636, 3632);
  g->Dot(32, 3637, YNN_INVALID_VALUE_ID, 3631, 1);
  g->DequantizeTensor(3631, YNN_INVALID_VALUE_ID, 3632, 3633);
  g->QuantizeTensor(3633, 6342, 3635, 33);
  g->Dequantize(33, 34, 0.055118121206760406, 0);
  g->Polynomial(34, 5413, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5413, 5414);
  g->Binary(ynn_binary_add, 5414, 5404, 5411);
  g->Binary(ynn_binary_multiply, 34, 5402, 5412);
  g->Binary(ynn_binary_multiply, 5412, 5411, 36);
  g->Binary(ynn_binary_multiply, 36, 31, 37);
  g->Quantize(37, 38, 0.22834646701812744, 0);
  g->Transpose(6908, 3644, {1,0});
  g->Binary(ynn_binary_multiply, 3641, 3643, 3639);
  g->Dot(38, 3644, YNN_INVALID_VALUE_ID, 3638, 1);
  g->DequantizeTensor(3638, YNN_INVALID_VALUE_ID, 3639, 3640);
  g->QuantizeTensor(3640, 6342, 3642, 39);
  g->Dequantize(39, 40, 0.08292699605226517, 0);
  g->Unary(ynn_unary_square, 40, 41);
  g->Reduce(ynn_reduce_sum, 41, 5416, {2}, true);
  g->ShapeProduct(41, 5415, {2});
  g->Binary(ynn_binary_divide, 5416, 5415, 42);
  g->Binary(ynn_binary_add, 42, 6376, 43);
  g->Binary(ynn_binary_pow, 43, 6378, 44);
  g->Binary(ynn_binary_multiply, 40, 44, 45);
  g->Convert(6911, 47);
  g->Binary(ynn_binary_multiply, 45, 47, 48);
  g->Binary(ynn_binary_add, 27, 48, 49);
  g->Convert(6903, 50);
  g->Binary(ynn_binary_multiply, 49, 50, 51);
}

// Scope: "Layer7"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7(Context& ctx) {
  BuildLayer7Attention(ctx);
  BuildLayer7Mlp(ctx);
  BuildLayer7PerLayerEmbedding(ctx);
}

}  // namespace BuildGemma4DecodeSource
