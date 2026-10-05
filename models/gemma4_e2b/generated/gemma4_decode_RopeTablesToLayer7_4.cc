// Generated YNNPACK builder; do not edit.
#include "gemma4_decode_builder.h"

namespace BuildGemma4DecodeSource {

// Scope: "RopeTables"
LAB_YNN_BUILDER_NOINLINE void BuildRopeTables(Context& ctx) {
  auto* g = ctx.g;
  g->Binary(ynn_binary_multiply, 7154, 6541, 1);
  g->Unary(ynn_unary_cos, 1, 1064);
  g->Unary(ynn_unary_sin, 1, 2173);
  g->Concat({1064,1064}, 3067, 3);
  g->Concat({2173,2173}, 3172, 3);
  g->Binary(ynn_binary_multiply, 7154, 6540, 3274);
  g->Unary(ynn_unary_cos, 3274, 3379);
  g->Unary(ynn_unary_sin, 3274, 3489);
  g->Concat({3379,3379}, 3594, 3);
  g->Concat({3489,3489}, 2, 3);
}

// Scope: "InputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildInputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(0, 107, 0.03887796401977539, 0);
  g->Transpose(7117, 3809, {1,0});
  g->Binary(ynn_binary_multiply, 3806, 3808, 3804);
  g->Dot(107, 3809, YNN_INVALID_VALUE_ID, 3803, 1);
  g->DequantizeTensor(3803, YNN_INVALID_VALUE_ID, 3804, 3805);
  g->QuantizeTensor(3805, 6504, 3807, 211);
  g->Dequantize(211, 322, 0.002352987416088581, 0);
  g->SplitDim(322, 427, 2, {35,256});
}

// Scope: "Layer0 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer0AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(1065, 1176, 0.6088034510612488, 0);
  g->Transpose(6593, 4323, {1,0});
  g->Binary(ynn_binary_multiply, 4320, 4322, 4318);
  g->Dot(1176, 4323, YNN_INVALID_VALUE_ID, 4317, 1);
  g->DequantizeTensor(4317, YNN_INVALID_VALUE_ID, 4318, 4319);
  g->QuantizeTensor(4319, 6504, 4321, 1287);
  g->Dequantize(1287, 1397, 1.535433053970337, 0);
  g->Reshape(1397, 1509, {1,1,1,256});
  g->Reshape(1509, 1620, {1,1,1,256});
  g->Unary(ynn_unary_square, 1620, 1730);
  g->Reduce(ynn_reduce_sum, 1730, 5995, {3}, true);
  g->ShapeProduct(1730, 5994, {3});
  g->Binary(ynn_binary_divide, 5995, 5994, 1842);
  g->Binary(ynn_binary_add, 1842, 6539, 1953);
  g->Unary(ynn_unary_rsqrt, 1953, 2064);
  g->Binary(ynn_binary_multiply, 1620, 2064, 2174);
  g->Binary(ynn_binary_multiply, 2174, 6592, 2280);
  g->Slice(2280, 2392, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2280, 2503, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2503, 2614);
  g->Concat({2614,2392}, 2725, 3);
  g->Binary(ynn_binary_multiply, 2280, 3067, 2835);
  g->Binary(ynn_binary_multiply, 2725, 3172, 2947);
  g->Binary(ynn_binary_add, 2835, 2947, 3046);
  g->Transpose(6597, 5210, {1,0});
  g->Binary(ynn_binary_multiply, 4320, 5209, 5207);
  g->Dot(1176, 5210, YNN_INVALID_VALUE_ID, 5206, 1);
  g->DequantizeTensor(5206, YNN_INVALID_VALUE_ID, 5207, 5208);
  g->QuantizeTensor(5208, 6504, 4321, 3068);
  g->Dequantize(3068, 3079, 1.535433053970337, 0);
  g->Reshape(3079, 3090, {1,1,1,256});
  g->Reshape(3090, 3100, {1,1,1,256});
  g->Unary(ynn_unary_square, 3100, 3106);
  g->Reduce(ynn_reduce_sum, 3106, 6353, {3}, true);
  g->ShapeProduct(3106, 6352, {3});
  g->Binary(ynn_binary_divide, 6353, 6352, 3118);
  g->Binary(ynn_binary_add, 3118, 6539, 3128);
  g->Unary(ynn_unary_rsqrt, 3128, 3140);
  g->Binary(ynn_binary_multiply, 3100, 3140, 3151);
}

// Scope: "Layer0 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer0AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(3046, 3161, 0.005997600965201855, 0);
  g->Append(6505, 3161, 7155, 2, s2, slinky::expr(int64_t{1}));
  g->View(7155, 7185, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(3151, 3193, 0.047244105488061905, 0);
  g->Append(6520, 3193, 7170, 2, s2, slinky::expr(int64_t{1}));
  g->View(7170, 7200, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer0 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer0AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(6596, 5283, {1,0});
  g->Binary(ynn_binary_multiply, 4320, 5282, 5279);
  g->Dot(1176, 5283, YNN_INVALID_VALUE_ID, 5278, 1);
  g->DequantizeTensor(5278, YNN_INVALID_VALUE_ID, 5279, 5280);
  g->QuantizeTensor(5280, 6504, 5281, 3231);
  g->Dequantize(3231, 3240, 3.118110179901123, 0);
  g->SplitDim(3240, 3251, 2, {8,256});
  g->FuseDims(3251, 3263, 1, 2);
  g->SplitDim(3263, 3262, 1, {8,1});
  g->Unary(ynn_unary_square, 3262, 3275);
  g->Reduce(ynn_reduce_sum, 3275, 6395, {3}, true);
  g->ShapeProduct(3275, 6394, {3});
  g->Binary(ynn_binary_divide, 6395, 6394, 3285);
  g->Binary(ynn_binary_add, 3285, 6539, 3296);
  g->Unary(ynn_unary_rsqrt, 3296, 3307);
  g->Binary(ynn_binary_multiply, 3262, 3307, 3318);
  g->Binary(ynn_binary_multiply, 3318, 6595, 3329);
  g->Slice(3329, 3340, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3329, 3351, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3351, 3361);
  g->Concat({3361,3340}, 3368, 3);
  g->Binary(ynn_binary_multiply, 3329, 3067, 3380);
  g->Binary(ynn_binary_multiply, 3368, 3172, 3391);
  g->Binary(ynn_binary_add, 3380, 3391, 3402);
}

// Scope: "Layer0 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer0AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7185, 3413, 0.005997600965201855, 0);
  g->Dequantize(7200, 3423, 0.047244105488061905, 0);
  g->Matmul(3402, 3413, 3434, false, true);
  g->Mask(3434, 6545, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6545, 6442, {-1}, true);
  g->Binary(ynn_binary_subtract, 6545, 6442, 6439);
  g->Unary(ynn_unary_exp, 6439, 6440);
  g->Reduce(ynn_reduce_sum, 6440, 6443, {-1}, true);
  g->Binary(ynn_binary_divide, 5500, 6443, 6441);
  g->Binary(ynn_binary_multiply, 6440, 6441, 3455);
  g->Matmul(3455, 3423, 3466, false, false);
}

// Scope: "Layer0 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer0AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(3466, 3478, 1, 2);
  g->SplitDim(3478, 3477, 1, {1,8});
  g->FuseDims(3477, 3490, 2, 2);
  g->Quantize(3490, 3500, 0.03026575781404972, 0);
  g->Transpose(6594, 5407, {1,0});
  g->Binary(ynn_binary_multiply, 5404, 5406, 5402);
  g->Dot(3500, 5407, YNN_INVALID_VALUE_ID, 5401, 1);
  g->DequantizeTensor(5401, YNN_INVALID_VALUE_ID, 5402, 5403);
  g->QuantizeTensor(5403, 6504, 5405, 3506);
  g->Dequantize(3506, 3518, 0.21056734025478363, 0);
}

// Scope: "Layer0 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer0Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 0, 532);
  g->Reduce(ynn_reduce_sum, 532, 5656, {2}, true);
  g->ShapeProduct(532, 5655, {2});
  g->Binary(ynn_binary_divide, 5656, 5655, 638);
  g->Binary(ynn_binary_add, 638, 6539, 746);
  g->Unary(ynn_unary_rsqrt, 746, 850);
  g->Binary(ynn_binary_multiply, 0, 850, 953);
  g->Binary(ynn_binary_multiply, 953, 6581, 1065);
  BuildLayer0AttentionKvProjection(ctx);
  BuildLayer0AttentionCacheUpdate(ctx);
  BuildLayer0AttentionQueryProjection(ctx);
  BuildLayer0AttentionSdpa(ctx);
  BuildLayer0AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 3518, 3528);
  g->Reduce(ynn_reduce_sum, 3528, 6462, {2}, true);
  g->ShapeProduct(3528, 6461, {2});
  g->Binary(ynn_binary_divide, 6462, 6461, 3540);
  g->Binary(ynn_binary_add, 3540, 6539, 3551);
  g->Unary(ynn_unary_rsqrt, 3551, 3561);
  g->Binary(ynn_binary_multiply, 3518, 3561, 3572);
  g->Binary(ynn_binary_multiply, 3572, 6588, 3583);
  g->Binary(ynn_binary_add, 3583, 0, 3595);
}

// Scope: "Layer0 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer0Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3595, 3606);
  g->Reduce(ynn_reduce_sum, 3606, 6484, {2}, true);
  g->ShapeProduct(3606, 6483, {2});
  g->Binary(ynn_binary_divide, 6484, 6483, 3617);
  g->Binary(ynn_binary_add, 3617, 6539, 3627);
  g->Unary(ynn_unary_rsqrt, 3627, 3637);
  g->Binary(ynn_binary_multiply, 3595, 3637, 3645);
  g->Binary(ynn_binary_multiply, 3645, 6591, 3656);
  g->Quantize(3656, 3667, 0.9406865835189819, 0);
  g->Transpose(6585, 5475, {1,0});
  g->Binary(ynn_binary_multiply, 3702, 5474, 5472);
  g->Dot(3667, 5475, YNN_INVALID_VALUE_ID, 5471, 1);
  g->DequantizeTensor(5471, YNN_INVALID_VALUE_ID, 5472, 5473);
  g->QuantizeTensor(5473, 6504, 3703, 3678);
  g->Dequantize(3678, 3688, 0.6181102395057678, 0);
  g->Transpose(6584, 3705, {1,0});
  g->Binary(ynn_binary_multiply, 3702, 3704, 3700);
  g->Dot(3667, 3705, YNN_INVALID_VALUE_ID, 3699, 1);
  g->DequantizeTensor(3699, YNN_INVALID_VALUE_ID, 3700, 3701);
  g->QuantizeTensor(3701, 6504, 3703, 13);
  g->Dequantize(13, 24, 0.6181102395057678, 0);
  g->Polynomial(24, 5507, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5507, 5508);
  g->Binary(ynn_binary_add, 5508, 5500, 5505);
  g->Binary(ynn_binary_multiply, 24, 5498, 5506);
  g->Binary(ynn_binary_multiply, 5506, 5505, 35);
  g->Binary(ynn_binary_multiply, 3688, 35, 46);
  g->Quantize(46, 57, 27.842519760131836, 0);
  g->Transpose(6583, 3738, {1,0});
  g->Binary(ynn_binary_multiply, 3735, 3737, 3733);
  g->Dot(57, 3738, YNN_INVALID_VALUE_ID, 3732, 1);
  g->DequantizeTensor(3732, YNN_INVALID_VALUE_ID, 3733, 3734);
  g->QuantizeTensor(3734, 6504, 3736, 67);
  g->Dequantize(67, 75, 16.64207649230957, 0);
  g->Unary(ynn_unary_square, 75, 85);
  g->Reduce(ynn_reduce_sum, 85, 5518, {2}, true);
  g->ShapeProduct(85, 5517, {2});
  g->Binary(ynn_binary_divide, 5518, 5517, 96);
  g->Binary(ynn_binary_add, 96, 6539, 108);
  g->Unary(ynn_unary_rsqrt, 108, 119);
  g->Binary(ynn_binary_multiply, 75, 119, 129);
  g->Binary(ynn_binary_multiply, 129, 6589, 140);
  g->Binary(ynn_binary_add, 140, 3595, 151);
}

// Scope: "Layer0 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer0PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(427, 162, {0,0,0,0}, {-1,-1,1,-1});
  g->Reshape(162, 173, {1,1,256});
  g->Unary(ynn_unary_square, 173, 184);
  g->Reduce(ynn_reduce_sum, 184, 5547, {2}, true);
  g->ShapeProduct(184, 5546, {2});
  g->Binary(ynn_binary_divide, 5547, 5546, 195);
  g->Binary(ynn_binary_add, 195, 6539, 205);
  g->Unary(ynn_unary_rsqrt, 205, 212);
  g->Binary(ynn_binary_multiply, 173, 212, 224);
  g->Binary(ynn_binary_multiply, 224, 7118, 234);
  g->Binary(ynn_binary_multiply, 7119, 6542, 246);
  g->Binary(ynn_binary_add, 234, 246, 257);
  g->Binary(ynn_binary_multiply, 257, 6536, 267);
  g->Quantize(151, 278, 3.334678888320923, 0);
  g->Transpose(6586, 3842, {1,0});
  g->Binary(ynn_binary_multiply, 3839, 3841, 3837);
  g->Dot(278, 3842, YNN_INVALID_VALUE_ID, 3836, 1);
  g->DequantizeTensor(3836, YNN_INVALID_VALUE_ID, 3837, 3838);
  g->QuantizeTensor(3838, 6504, 3840, 289);
  g->Dequantize(289, 300, 0.01857776567339897, 0);
  g->Polynomial(300, 5579, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5579, 5580);
  g->Binary(ynn_binary_add, 5580, 5500, 5577);
  g->Binary(ynn_binary_multiply, 300, 5498, 5578);
  g->Binary(ynn_binary_multiply, 5578, 5577, 311);
  g->Binary(ynn_binary_multiply, 311, 267, 323);
  g->Quantize(323, 333, 0.03764764964580536, 0);
  g->Transpose(6587, 3875, {1,0});
  g->Binary(ynn_binary_multiply, 3872, 3874, 3870);
  g->Dot(333, 3875, YNN_INVALID_VALUE_ID, 3869, 1);
  g->DequantizeTensor(3869, YNN_INVALID_VALUE_ID, 3870, 3871);
  g->QuantizeTensor(3871, 6504, 3873, 344);
  g->Dequantize(344, 351, 0.03129800781607628, 0);
  g->Unary(ynn_unary_square, 351, 362);
  g->Reduce(ynn_reduce_sum, 362, 5593, {2}, true);
  g->ShapeProduct(362, 5592, {2});
  g->Binary(ynn_binary_divide, 5593, 5592, 373);
  g->Binary(ynn_binary_add, 373, 6539, 384);
  g->Unary(ynn_unary_rsqrt, 384, 395);
  g->Binary(ynn_binary_multiply, 351, 395, 405);
  g->Binary(ynn_binary_multiply, 405, 6590, 416);
  g->Binary(ynn_binary_add, 151, 416, 428);
  g->Binary(ynn_binary_multiply, 428, 6582, 439);
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
  g->Quantize(500, 511, 0.4842597544193268, 0);
  g->Transpose(6610, 3953, {1,0});
  g->Binary(ynn_binary_multiply, 3950, 3952, 3948);
  g->Dot(511, 3953, YNN_INVALID_VALUE_ID, 3947, 1);
  g->DequantizeTensor(3947, YNN_INVALID_VALUE_ID, 3948, 3949);
  g->QuantizeTensor(3949, 6504, 3951, 522);
  g->Dequantize(522, 533, 0.41535434126853943, 0);
  g->Reshape(533, 544, {1,1,1,256});
  g->Reshape(544, 555, {1,1,1,256});
  g->Unary(ynn_unary_square, 555, 566);
  g->Reduce(ynn_reduce_sum, 566, 5646, {3}, true);
  g->ShapeProduct(566, 5645, {3});
  g->Binary(ynn_binary_divide, 5646, 5645, 577);
  g->Binary(ynn_binary_add, 577, 6539, 588);
  g->Unary(ynn_unary_rsqrt, 588, 599);
  g->Binary(ynn_binary_multiply, 555, 599, 609);
  g->Binary(ynn_binary_multiply, 609, 6609, 615);
  g->Slice(615, 627, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(615, 639, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 639, 650);
  g->Concat({650,627}, 661, 3);
  g->Binary(ynn_binary_multiply, 615, 3067, 671);
  g->Binary(ynn_binary_multiply, 661, 3172, 682);
  g->Binary(ynn_binary_add, 671, 682, 693);
  g->Transpose(6614, 4048, {1,0});
  g->Binary(ynn_binary_multiply, 3950, 4047, 4045);
  g->Dot(511, 4048, YNN_INVALID_VALUE_ID, 4044, 1);
  g->DequantizeTensor(4044, YNN_INVALID_VALUE_ID, 4045, 4046);
  g->QuantizeTensor(4046, 6504, 3951, 714);
  g->Dequantize(714, 725, 0.41535434126853943, 0);
  g->Reshape(725, 736, {1,1,1,256});
  g->Reshape(736, 747, {1,1,1,256});
  g->Unary(ynn_unary_square, 747, 753);
  g->Reduce(ynn_reduce_sum, 753, 5689, {3}, true);
  g->ShapeProduct(753, 5688, {3});
  g->Binary(ynn_binary_divide, 5689, 5688, 765);
  g->Binary(ynn_binary_add, 765, 6539, 775);
  g->Unary(ynn_unary_rsqrt, 775, 787);
  g->Binary(ynn_binary_multiply, 747, 787, 798);
}

// Scope: "Layer1 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(693, 808, 0.005761673673987389, 0);
  g->Append(6506, 808, 7156, 2, s2, slinky::expr(int64_t{1}));
  g->View(7156, 7186, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(798, 839, 0.047244105488061905, 0);
  g->Append(6521, 839, 7171, 2, s2, slinky::expr(int64_t{1}));
  g->View(7171, 7201, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer1 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(6613, 4123, {1,0});
  g->Binary(ynn_binary_multiply, 3950, 4122, 4119);
  g->Dot(511, 4123, YNN_INVALID_VALUE_ID, 4118, 1);
  g->DequantizeTensor(4118, YNN_INVALID_VALUE_ID, 4119, 4120);
  g->QuantizeTensor(4120, 6504, 4121, 878);
  g->Dequantize(878, 887, 0.35039371252059937, 0);
  g->SplitDim(887, 898, 2, {8,256});
  g->FuseDims(898, 910, 1, 2);
  g->SplitDim(910, 909, 1, {8,1});
  g->Unary(ynn_unary_square, 909, 921);
  g->Reduce(ynn_reduce_sum, 921, 5731, {3}, true);
  g->ShapeProduct(921, 5730, {3});
  g->Binary(ynn_binary_divide, 5731, 5730, 931);
  g->Binary(ynn_binary_add, 931, 6539, 942);
  g->Unary(ynn_unary_rsqrt, 942, 954);
  g->Binary(ynn_binary_multiply, 909, 954, 965);
  g->Binary(ynn_binary_multiply, 965, 6612, 976);
  g->Slice(976, 987, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(976, 999, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 999, 1009);
  g->Concat({1009,987}, 1021, 3);
  g->Binary(ynn_binary_multiply, 976, 3067, 1032);
  g->Binary(ynn_binary_multiply, 1021, 3172, 1042);
  g->Binary(ynn_binary_add, 1032, 1042, 1053);
}

// Scope: "Layer1 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7186, 1066, 0.005761673673987389, 0);
  g->Dequantize(7201, 1077, 0.047244105488061905, 0);
  g->Matmul(1053, 1066, 1088, false, true);
  g->Mask(1088, 6546, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6546, 5780, {-1}, true);
  g->Binary(ynn_binary_subtract, 6546, 5780, 5777);
  g->Unary(ynn_unary_exp, 5777, 5778);
  g->Reduce(ynn_reduce_sum, 5778, 5781, {-1}, true);
  g->Binary(ynn_binary_divide, 5500, 5781, 5779);
  g->Binary(ynn_binary_multiply, 5778, 5779, 1110);
  g->Matmul(1110, 1077, 1121, false, false);
}

// Scope: "Layer1 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(1121, 1133, 1, 2);
  g->SplitDim(1133, 1132, 1, {1,8});
  g->FuseDims(1132, 1143, 2, 2);
  g->Quantize(1143, 1154, 0.023129930719733238, 0);
  g->Transpose(6611, 4255, {1,0});
  g->Binary(ynn_binary_multiply, 4252, 4254, 4250);
  g->Dot(1154, 4255, YNN_INVALID_VALUE_ID, 4249, 1);
  g->DequantizeTensor(4249, YNN_INVALID_VALUE_ID, 4250, 4251);
  g->QuantizeTensor(4251, 6504, 4253, 1165);
  g->Dequantize(1165, 1177, 0.03322756290435791, 0);
}

// Scope: "Layer1 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 439, 450);
  g->Reduce(ynn_reduce_sum, 450, 5617, {2}, true);
  g->ShapeProduct(450, 5616, {2});
  g->Binary(ynn_binary_divide, 5617, 5616, 461);
  g->Binary(ynn_binary_add, 461, 6539, 471);
  g->Unary(ynn_unary_rsqrt, 471, 480);
  g->Binary(ynn_binary_multiply, 439, 480, 489);
  g->Binary(ynn_binary_multiply, 489, 6598, 500);
  BuildLayer1AttentionKvProjection(ctx);
  BuildLayer1AttentionCacheUpdate(ctx);
  BuildLayer1AttentionQueryProjection(ctx);
  BuildLayer1AttentionSdpa(ctx);
  BuildLayer1AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1177, 1188);
  g->Reduce(ynn_reduce_sum, 1188, 5810, {2}, true);
  g->ShapeProduct(1188, 5809, {2});
  g->Binary(ynn_binary_divide, 5810, 5809, 1200);
  g->Binary(ynn_binary_add, 1200, 6539, 1211);
  g->Unary(ynn_unary_rsqrt, 1211, 1222);
  g->Binary(ynn_binary_multiply, 1177, 1222, 1233);
  g->Binary(ynn_binary_multiply, 1233, 6605, 1243);
  g->Binary(ynn_binary_add, 1243, 439, 1254);
}

// Scope: "Layer1 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1254, 1265);
  g->Reduce(ynn_reduce_sum, 1265, 5833, {2}, true);
  g->ShapeProduct(1265, 5832, {2});
  g->Binary(ynn_binary_divide, 5833, 5832, 1276);
  g->Binary(ynn_binary_add, 1276, 6539, 1288);
  g->Unary(ynn_unary_rsqrt, 1288, 1300);
  g->Binary(ynn_binary_multiply, 1254, 1300, 1311);
  g->Binary(ynn_binary_multiply, 1311, 6608, 1322);
  g->Quantize(1322, 1333, 0.08275254815816879, 0);
  g->Transpose(6602, 4351, {1,0});
  g->Binary(ynn_binary_multiply, 4348, 4350, 4346);
  g->Dot(1333, 4351, YNN_INVALID_VALUE_ID, 4345, 1);
  g->DequantizeTensor(4345, YNN_INVALID_VALUE_ID, 4346, 4347);
  g->QuantizeTensor(4347, 6504, 4349, 1344);
  g->Dequantize(1344, 1354, 0.06889764219522476, 0);
  g->Transpose(6601, 4375, {1,0});
  g->Binary(ynn_binary_multiply, 4348, 4374, 4372);
  g->Dot(1333, 4375, YNN_INVALID_VALUE_ID, 4371, 1);
  g->DequantizeTensor(4371, YNN_INVALID_VALUE_ID, 4372, 4373);
  g->QuantizeTensor(4373, 6504, 4349, 1375);
  g->Dequantize(1375, 1386, 0.06889764219522476, 0);
  g->Polynomial(1386, 5867, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5867, 5868);
  g->Binary(ynn_binary_add, 5868, 5500, 5865);
  g->Binary(ynn_binary_multiply, 1386, 5498, 5866);
  g->Binary(ynn_binary_multiply, 5866, 5865, 1398);
  g->Binary(ynn_binary_multiply, 1354, 1398, 1410);
  g->Quantize(1410, 1420, 0.21062994003295898, 0);
  g->Transpose(6600, 4403, {1,0});
  g->Binary(ynn_binary_multiply, 4400, 4402, 4398);
  g->Dot(1420, 4403, YNN_INVALID_VALUE_ID, 4397, 1);
  g->DequantizeTensor(4397, YNN_INVALID_VALUE_ID, 4398, 4399);
  g->QuantizeTensor(4399, 6504, 4401, 1432);
  g->Dequantize(1432, 1443, 0.09257561713457108, 0);
  g->Unary(ynn_unary_square, 1443, 1453);
  g->Reduce(ynn_reduce_sum, 1453, 5887, {2}, true);
  g->ShapeProduct(1453, 5886, {2});
  g->Binary(ynn_binary_divide, 5887, 5886, 1464);
  g->Binary(ynn_binary_add, 1464, 6539, 1475);
  g->Unary(ynn_unary_rsqrt, 1475, 1486);
  g->Binary(ynn_binary_multiply, 1443, 1486, 1497);
  g->Binary(ynn_binary_multiply, 1497, 6606, 1510);
  g->Binary(ynn_binary_add, 1510, 1254, 1521);
}

// Scope: "Layer1 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(427, 1532, {0,0,1,0}, {-1,-1,1,-1});
  g->Reshape(1532, 1543, {1,1,256});
  g->Unary(ynn_unary_square, 1543, 1553);
  g->Reduce(ynn_reduce_sum, 1553, 5916, {2}, true);
  g->ShapeProduct(1553, 5915, {2});
  g->Binary(ynn_binary_divide, 5916, 5915, 1564);
  g->Binary(ynn_binary_add, 1564, 6539, 1575);
  g->Unary(ynn_unary_rsqrt, 1575, 1586);
  g->Binary(ynn_binary_multiply, 1543, 1586, 1597);
  g->Binary(ynn_binary_multiply, 1597, 7118, 1609);
  g->Binary(ynn_binary_multiply, 7120, 6542, 1621);
  g->Binary(ynn_binary_add, 1609, 1621, 1632);
  g->Binary(ynn_binary_multiply, 1632, 6536, 1643);
  g->Quantize(1521, 1653, 0.4206320643424988, 0);
  g->Transpose(6603, 4520, {1,0});
  g->Binary(ynn_binary_multiply, 4517, 4519, 4515);
  g->Dot(1653, 4520, YNN_INVALID_VALUE_ID, 4514, 1);
  g->DequantizeTensor(4514, YNN_INVALID_VALUE_ID, 4515, 4516);
  g->QuantizeTensor(4516, 6504, 4518, 1664);
  g->Dequantize(1664, 1675, 0.010150108486413956, 0);
  g->Polynomial(1675, 5952, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5952, 5953);
  g->Binary(ynn_binary_add, 5953, 5500, 5950);
  g->Binary(ynn_binary_multiply, 1675, 5498, 5951);
  g->Binary(ynn_binary_multiply, 5951, 5950, 1686);
  g->Binary(ynn_binary_multiply, 1686, 1643, 1697);
  g->Quantize(1697, 1708, 0.026820875704288483, 0);
  g->Transpose(6604, 4548, {1,0});
  g->Binary(ynn_binary_multiply, 4545, 4547, 4543);
  g->Dot(1708, 4548, YNN_INVALID_VALUE_ID, 4542, 1);
  g->DequantizeTensor(4542, YNN_INVALID_VALUE_ID, 4543, 4544);
  g->QuantizeTensor(4544, 6504, 4546, 1720);
  g->Dequantize(1720, 1731, 0.020895034074783325, 0);
  g->Unary(ynn_unary_square, 1731, 1743);
  g->Reduce(ynn_reduce_sum, 1743, 5970, {2}, true);
  g->ShapeProduct(1743, 5969, {2});
  g->Binary(ynn_binary_divide, 5970, 5969, 1754);
  g->Binary(ynn_binary_add, 1754, 6539, 1764);
  g->Unary(ynn_unary_rsqrt, 1764, 1775);
  g->Binary(ynn_binary_multiply, 1731, 1775, 1786);
  g->Binary(ynn_binary_multiply, 1786, 6607, 1797);
  g->Binary(ynn_binary_add, 1521, 1797, 1808);
  g->Binary(ynn_binary_multiply, 1808, 6599, 1820);
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
  g->Quantize(1886, 1897, 0.15746013820171356, 0);
  g->Transpose(6782, 4641, {1,0});
  g->Binary(ynn_binary_multiply, 4638, 4640, 4636);
  g->Dot(1897, 4641, YNN_INVALID_VALUE_ID, 4635, 1);
  g->DequantizeTensor(4635, YNN_INVALID_VALUE_ID, 4636, 4637);
  g->QuantizeTensor(4637, 6504, 4639, 1908);
  g->Dequantize(1908, 1920, 0.180118128657341, 0);
  g->Reshape(1920, 1931, {1,1,1,256});
  g->Reshape(1931, 1942, {1,1,1,256});
  g->Unary(ynn_unary_square, 1942, 1954);
  g->Reduce(ynn_reduce_sum, 1954, 6030, {3}, true);
  g->ShapeProduct(1954, 6029, {3});
  g->Binary(ynn_binary_divide, 6030, 6029, 1964);
  g->Binary(ynn_binary_add, 1964, 6539, 1975);
  g->Unary(ynn_unary_rsqrt, 1975, 1986);
  g->Binary(ynn_binary_multiply, 1942, 1986, 1997);
  g->Binary(ynn_binary_multiply, 1997, 6781, 2008);
  g->Slice(2008, 2019, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2008, 2031, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2031, 2041);
  g->Concat({2041,2019}, 2053, 3);
  g->Binary(ynn_binary_multiply, 2008, 3067, 2065);
  g->Binary(ynn_binary_multiply, 2053, 3172, 2075);
  g->Binary(ynn_binary_add, 2065, 2075, 2086);
  g->Transpose(6786, 4737, {1,0});
  g->Binary(ynn_binary_multiply, 4638, 4736, 4734);
  g->Dot(1897, 4737, YNN_INVALID_VALUE_ID, 4733, 1);
  g->DequantizeTensor(4733, YNN_INVALID_VALUE_ID, 4734, 4735);
  g->QuantizeTensor(4735, 6504, 4639, 2107);
  g->Dequantize(2107, 2118, 0.180118128657341, 0);
  g->Reshape(2118, 2130, {1,1,1,256});
  g->Reshape(2130, 2141, {1,1,1,256});
  g->Unary(ynn_unary_square, 2141, 2152);
  g->Reduce(ynn_reduce_sum, 2152, 6086, {3}, true);
  g->ShapeProduct(2152, 6085, {3});
  g->Binary(ynn_binary_divide, 6086, 6085, 2163);
  g->Binary(ynn_binary_add, 2163, 6539, 2175);
  g->Unary(ynn_unary_rsqrt, 2175, 2186);
  g->Binary(ynn_binary_multiply, 2141, 2186, 2197);
}

// Scope: "Layer2 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(2086, 2208, 0.005684707313776016, 0);
  g->Append(6512, 2208, 7162, 2, s2, slinky::expr(int64_t{1}));
  g->View(7162, 7192, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(2197, 2240, 0.047244105488061905, 0);
  g->Append(6527, 2240, 7177, 2, s2, slinky::expr(int64_t{1}));
  g->View(7177, 7207, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer2 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(6785, 4822, {1,0});
  g->Binary(ynn_binary_multiply, 4638, 4821, 4818);
  g->Dot(1897, 4822, YNN_INVALID_VALUE_ID, 4817, 1);
  g->DequantizeTensor(4817, YNN_INVALID_VALUE_ID, 4818, 4819);
  g->QuantizeTensor(4819, 6504, 4820, 2281);
  g->Dequantize(2281, 2292, 0.1643700897693634, 0);
  g->SplitDim(2292, 2303, 2, {8,256});
  g->FuseDims(2303, 2315, 1, 2);
  g->SplitDim(2315, 2314, 1, {8,1});
  g->Unary(ynn_unary_square, 2314, 2327);
  g->Reduce(ynn_reduce_sum, 2327, 6133, {3}, true);
  g->ShapeProduct(2327, 6132, {3});
  g->Binary(ynn_binary_divide, 6133, 6132, 2338);
  g->Binary(ynn_binary_add, 2338, 6539, 2349);
  g->Unary(ynn_unary_rsqrt, 2349, 2360);
  g->Binary(ynn_binary_multiply, 2314, 2360, 2371);
  g->Binary(ynn_binary_multiply, 2371, 6784, 2381);
  g->Slice(2381, 2393, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2381, 2404, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2404, 2415);
  g->Concat({2415,2393}, 2426, 3);
  g->Binary(ynn_binary_multiply, 2381, 3067, 2438);
  g->Binary(ynn_binary_multiply, 2426, 3172, 2448);
  g->Binary(ynn_binary_add, 2438, 2448, 2460);
}

// Scope: "Layer2 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7192, 2471, 0.005684707313776016, 0);
  g->Dequantize(7207, 2481, 0.047244105488061905, 0);
  g->Matmul(2460, 2471, 2492, false, true);
  g->Mask(2492, 6557, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6557, 6187, {-1}, true);
  g->Binary(ynn_binary_subtract, 6557, 6187, 6184);
  g->Unary(ynn_unary_exp, 6184, 6185);
  g->Reduce(ynn_reduce_sum, 6185, 6188, {-1}, true);
  g->Binary(ynn_binary_divide, 5500, 6188, 6186);
  g->Binary(ynn_binary_multiply, 6185, 6186, 2514);
  g->Matmul(2514, 2481, 2525, false, false);
}

// Scope: "Layer2 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(2525, 2538, 1, 2);
  g->SplitDim(2538, 2537, 1, {1,8});
  g->FuseDims(2537, 2549, 2, 2);
  g->Quantize(2549, 2560, 0.0216535534709692, 0);
  g->Transpose(6783, 4948, {1,0});
  g->Binary(ynn_binary_multiply, 4945, 4947, 4943);
  g->Dot(2560, 4948, YNN_INVALID_VALUE_ID, 4942, 1);
  g->DequantizeTensor(4942, YNN_INVALID_VALUE_ID, 4943, 4944);
  g->QuantizeTensor(4944, 6504, 4946, 2571);
  g->Dequantize(2571, 2581, 0.03426840156316757, 0);
}

// Scope: "Layer2 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1820, 1831);
  g->Reduce(ynn_reduce_sum, 1831, 5997, {2}, true);
  g->ShapeProduct(1831, 5996, {2});
  g->Binary(ynn_binary_divide, 5997, 5996, 1843);
  g->Binary(ynn_binary_add, 1843, 6539, 1854);
  g->Unary(ynn_unary_rsqrt, 1854, 1864);
  g->Binary(ynn_binary_multiply, 1820, 1864, 1875);
  g->Binary(ynn_binary_multiply, 1875, 6770, 1886);
  BuildLayer2AttentionKvProjection(ctx);
  BuildLayer2AttentionCacheUpdate(ctx);
  BuildLayer2AttentionQueryProjection(ctx);
  BuildLayer2AttentionSdpa(ctx);
  BuildLayer2AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2581, 2592);
  g->Reduce(ynn_reduce_sum, 2592, 6211, {2}, true);
  g->ShapeProduct(2592, 6210, {2});
  g->Binary(ynn_binary_divide, 6211, 6210, 2603);
  g->Binary(ynn_binary_add, 2603, 6539, 2615);
  g->Unary(ynn_unary_rsqrt, 2615, 2626);
  g->Binary(ynn_binary_multiply, 2581, 2626, 2638);
  g->Binary(ynn_binary_multiply, 2638, 6777, 2649);
  g->Binary(ynn_binary_add, 2649, 1820, 2660);
}

// Scope: "Layer2 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2660, 2671);
  g->Reduce(ynn_reduce_sum, 2671, 6232, {2}, true);
  g->ShapeProduct(2671, 6231, {2});
  g->Binary(ynn_binary_divide, 6232, 6231, 2681);
  g->Binary(ynn_binary_add, 2681, 6539, 2692);
  g->Unary(ynn_unary_rsqrt, 2692, 2703);
  g->Binary(ynn_binary_multiply, 2660, 2703, 2714);
  g->Binary(ynn_binary_multiply, 2714, 6780, 2726);
  g->Quantize(2726, 2737, 0.04049227386713028, 0);
  g->Transpose(6774, 5039, {1,0});
  g->Binary(ynn_binary_multiply, 5036, 5038, 5034);
  g->Dot(2737, 5039, YNN_INVALID_VALUE_ID, 5033, 1);
  g->DequantizeTensor(5033, YNN_INVALID_VALUE_ID, 5034, 5035);
  g->QuantizeTensor(5035, 6504, 5037, 2749);
  g->Dequantize(2749, 2759, 0.04183071851730347, 0);
  g->Transpose(6773, 5050, {1,0});
  g->Binary(ynn_binary_multiply, 5036, 5049, 5047);
  g->Dot(2737, 5050, YNN_INVALID_VALUE_ID, 5046, 1);
  g->DequantizeTensor(5046, YNN_INVALID_VALUE_ID, 5047, 5048);
  g->QuantizeTensor(5048, 6504, 5037, 2781);
  g->Dequantize(2781, 2791, 0.04183071851730347, 0);
  g->Polynomial(2791, 6268, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6268, 6269);
  g->Binary(ynn_binary_add, 6269, 5500, 6266);
  g->Binary(ynn_binary_multiply, 2791, 5498, 6267);
  g->Binary(ynn_binary_multiply, 6267, 6266, 2802);
  g->Binary(ynn_binary_multiply, 2759, 2802, 2813);
  g->Quantize(2813, 2824, 0.09645669907331467, 0);
  g->Transpose(6772, 5087, {1,0});
  g->Binary(ynn_binary_multiply, 5084, 5086, 5082);
  g->Dot(2824, 5087, YNN_INVALID_VALUE_ID, 5081, 1);
  g->DequantizeTensor(5081, YNN_INVALID_VALUE_ID, 5082, 5083);
  g->QuantizeTensor(5083, 6504, 5085, 2836);
  g->Dequantize(2836, 2848, 0.05011765658855438, 0);
  g->Unary(ynn_unary_square, 2848, 2859);
  g->Reduce(ynn_reduce_sum, 2859, 6288, {2}, true);
  g->ShapeProduct(2859, 6287, {2});
  g->Binary(ynn_binary_divide, 6288, 6287, 2870);
  g->Binary(ynn_binary_add, 2870, 6539, 2881);
  g->Unary(ynn_unary_rsqrt, 2881, 2891);
  g->Binary(ynn_binary_multiply, 2848, 2891, 2902);
  g->Binary(ynn_binary_multiply, 2902, 6778, 2913);
  g->Binary(ynn_binary_add, 2913, 2660, 2924);
}

// Scope: "Layer2 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(427, 2935, {0,0,2,0}, {-1,-1,1,-1});
  g->Reshape(2935, 2948, {1,1,256});
  g->Unary(ynn_unary_square, 2948, 2959);
  g->Reduce(ynn_reduce_sum, 2959, 6317, {2}, true);
  g->ShapeProduct(2959, 6316, {2});
  g->Binary(ynn_binary_divide, 6317, 6316, 2970);
  g->Binary(ynn_binary_add, 2970, 6539, 2981);
  g->Unary(ynn_unary_rsqrt, 2981, 2991);
  g->Binary(ynn_binary_multiply, 2948, 2991, 3002);
  g->Binary(ynn_binary_multiply, 3002, 7118, 3013);
  g->Binary(ynn_binary_multiply, 7131, 6542, 3024);
  g->Binary(ynn_binary_add, 3013, 3024, 3035);
  g->Binary(ynn_binary_multiply, 3035, 6536, 3045);
  g->Quantize(2924, 3047, 0.045230474323034286, 0);
  g->Transpose(6775, 5198, {1,0});
  g->Binary(ynn_binary_multiply, 5195, 5197, 5193);
  g->Dot(3047, 5198, YNN_INVALID_VALUE_ID, 5192, 1);
  g->DequantizeTensor(5192, YNN_INVALID_VALUE_ID, 5193, 5194);
  g->QuantizeTensor(5194, 6504, 5196, 3048);
  g->Dequantize(3048, 3049, 0.017839577049016953, 0);
  g->Polynomial(3049, 6340, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6340, 6341);
  g->Binary(ynn_binary_add, 6341, 5500, 6338);
  g->Binary(ynn_binary_multiply, 3049, 5498, 6339);
  g->Binary(ynn_binary_multiply, 6339, 6338, 3050);
  g->Binary(ynn_binary_multiply, 3050, 3045, 3051);
  g->Quantize(3051, 3052, 0.05216536670923233, 0);
  g->Transpose(6776, 5205, {1,0});
  g->Binary(ynn_binary_multiply, 5202, 5204, 5200);
  g->Dot(3052, 5205, YNN_INVALID_VALUE_ID, 5199, 1);
  g->DequantizeTensor(5199, YNN_INVALID_VALUE_ID, 5200, 5201);
  g->QuantizeTensor(5201, 6504, 5203, 3053);
  g->Dequantize(3053, 3054, 0.021943029016256332, 0);
  g->Unary(ynn_unary_square, 3054, 3055);
  g->Reduce(ynn_reduce_sum, 3055, 6343, {2}, true);
  g->ShapeProduct(3055, 6342, {2});
  g->Binary(ynn_binary_divide, 6343, 6342, 3056);
  g->Binary(ynn_binary_add, 3056, 6539, 3057);
  g->Unary(ynn_unary_rsqrt, 3057, 3058);
  g->Binary(ynn_binary_multiply, 3054, 3058, 3059);
  g->Binary(ynn_binary_multiply, 3059, 6779, 3060);
  g->Binary(ynn_binary_add, 2924, 3060, 3061);
  g->Binary(ynn_binary_multiply, 3061, 6771, 3062);
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
  g->Quantize(3070, 3071, 0.12591414153575897, 0);
  g->Transpose(6939, 5216, {1,0});
  g->Binary(ynn_binary_multiply, 5214, 5215, 5212);
  g->Dot(3071, 5216, YNN_INVALID_VALUE_ID, 5211, 1);
  g->DequantizeTensor(5211, YNN_INVALID_VALUE_ID, 5212, 5213);
  g->QuantizeTensor(5213, 6504, 4678, 3072);
  g->Dequantize(3072, 3073, 0.08710630983114243, 0);
  g->Reshape(3073, 3074, {1,1,1,256});
  g->Reshape(3074, 3075, {1,1,1,256});
  g->Unary(ynn_unary_square, 3075, 3076);
  g->Reduce(ynn_reduce_sum, 3076, 6347, {3}, true);
  g->ShapeProduct(3076, 6346, {3});
  g->Binary(ynn_binary_divide, 6347, 6346, 3077);
  g->Binary(ynn_binary_add, 3077, 6539, 3078);
  g->Unary(ynn_unary_rsqrt, 3078, 3080);
  g->Binary(ynn_binary_multiply, 3075, 3080, 3081);
  g->Binary(ynn_binary_multiply, 3081, 6938, 3082);
  g->Slice(3082, 3083, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3082, 3084, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3084, 3085);
  g->Concat({3085,3083}, 3086, 3);
  g->Binary(ynn_binary_multiply, 3082, 3067, 3087);
  g->Binary(ynn_binary_multiply, 3086, 3172, 3088);
  g->Binary(ynn_binary_add, 3087, 3088, 3089);
  g->Transpose(6943, 5221, {1,0});
  g->Binary(ynn_binary_multiply, 5214, 5220, 5218);
  g->Dot(3071, 5221, YNN_INVALID_VALUE_ID, 5217, 1);
  g->DequantizeTensor(5217, YNN_INVALID_VALUE_ID, 5218, 5219);
  g->QuantizeTensor(5219, 6504, 4678, 3091);
  g->Dequantize(3091, 3092, 0.08710630983114243, 0);
  g->Reshape(3092, 3093, {1,1,1,256});
  g->Reshape(3093, 3094, {1,1,1,256});
  g->Unary(ynn_unary_square, 3094, 3095);
  g->Reduce(ynn_reduce_sum, 3095, 6349, {3}, true);
  g->ShapeProduct(3095, 6348, {3});
  g->Binary(ynn_binary_divide, 6349, 6348, 3096);
  g->Binary(ynn_binary_add, 3096, 6539, 3097);
  g->Unary(ynn_unary_rsqrt, 3097, 3098);
  g->Binary(ynn_binary_multiply, 3094, 3098, 3099);
}

// Scope: "Layer3 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(3089, 3101, 0.00573749840259552, 0);
  g->Append(6513, 3101, 7163, 2, s2, slinky::expr(int64_t{1}));
  g->View(7163, 7193, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(3099, 3102, 0.047244105488061905, 0);
  g->Append(6528, 3102, 7178, 2, s2, slinky::expr(int64_t{1}));
  g->View(7178, 7208, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer3 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(6942, 5227, {1,0});
  g->Binary(ynn_binary_multiply, 5214, 5226, 5223);
  g->Dot(3071, 5227, YNN_INVALID_VALUE_ID, 5222, 1);
  g->DequantizeTensor(5222, YNN_INVALID_VALUE_ID, 5223, 5224);
  g->QuantizeTensor(5224, 6504, 5225, 3103);
  g->Dequantize(3103, 3104, 0.15354332327842712, 0);
  g->SplitDim(3104, 3105, 2, {8,256});
  g->FuseDims(3105, 3108, 1, 2);
  g->SplitDim(3108, 3107, 1, {8,1});
  g->Unary(ynn_unary_square, 3107, 3109);
  g->Reduce(ynn_reduce_sum, 3109, 6351, {3}, true);
  g->ShapeProduct(3109, 6350, {3});
  g->Binary(ynn_binary_divide, 6351, 6350, 3110);
  g->Binary(ynn_binary_add, 3110, 6539, 3111);
  g->Unary(ynn_unary_rsqrt, 3111, 3112);
  g->Binary(ynn_binary_multiply, 3107, 3112, 3113);
  g->Binary(ynn_binary_multiply, 3113, 6941, 3114);
  g->Slice(3114, 3115, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3114, 3116, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3116, 3117);
  g->Concat({3117,3115}, 3119, 3);
  g->Binary(ynn_binary_multiply, 3114, 3067, 3120);
  g->Binary(ynn_binary_multiply, 3119, 3172, 3121);
  g->Binary(ynn_binary_add, 3120, 3121, 3122);
}

// Scope: "Layer3 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7193, 3123, 0.00573749840259552, 0);
  g->Dequantize(7208, 3124, 0.047244105488061905, 0);
  g->Matmul(3122, 3123, 3125, false, true);
  g->Mask(3125, 6568, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6568, 6357, {-1}, true);
  g->Binary(ynn_binary_subtract, 6568, 6357, 6354);
  g->Unary(ynn_unary_exp, 6354, 6355);
  g->Reduce(ynn_reduce_sum, 6355, 6358, {-1}, true);
  g->Binary(ynn_binary_divide, 5500, 6358, 6356);
  g->Binary(ynn_binary_multiply, 6355, 6356, 3126);
  g->Matmul(3126, 3124, 3127, false, false);
}

// Scope: "Layer3 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(3127, 3130, 1, 2);
  g->SplitDim(3130, 3129, 1, {1,8});
  g->FuseDims(3129, 3131, 2, 2);
  g->Quantize(3131, 3132, 0.02706693857908249, 0);
  g->Transpose(6940, 5234, {1,0});
  g->Binary(ynn_binary_multiply, 5231, 5233, 5229);
  g->Dot(3132, 5234, YNN_INVALID_VALUE_ID, 5228, 1);
  g->DequantizeTensor(5228, YNN_INVALID_VALUE_ID, 5229, 5230);
  g->QuantizeTensor(5230, 6504, 5232, 3133);
  g->Dequantize(3133, 3134, 0.07367152720689774, 0);
}

// Scope: "Layer3 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3062, 3063);
  g->Reduce(ynn_reduce_sum, 3063, 6345, {2}, true);
  g->ShapeProduct(3063, 6344, {2});
  g->Binary(ynn_binary_divide, 6345, 6344, 3064);
  g->Binary(ynn_binary_add, 3064, 6539, 3065);
  g->Unary(ynn_unary_rsqrt, 3065, 3066);
  g->Binary(ynn_binary_multiply, 3062, 3066, 3069);
  g->Binary(ynn_binary_multiply, 3069, 6927, 3070);
  BuildLayer3AttentionKvProjection(ctx);
  BuildLayer3AttentionCacheUpdate(ctx);
  BuildLayer3AttentionQueryProjection(ctx);
  BuildLayer3AttentionSdpa(ctx);
  BuildLayer3AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 3134, 3135);
  g->Reduce(ynn_reduce_sum, 3135, 6360, {2}, true);
  g->ShapeProduct(3135, 6359, {2});
  g->Binary(ynn_binary_divide, 6360, 6359, 3136);
  g->Binary(ynn_binary_add, 3136, 6539, 3137);
  g->Unary(ynn_unary_rsqrt, 3137, 3138);
  g->Binary(ynn_binary_multiply, 3134, 3138, 3139);
  g->Binary(ynn_binary_multiply, 3139, 6934, 3141);
  g->Binary(ynn_binary_add, 3141, 3062, 3142);
}

// Scope: "Layer3 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3142, 3143);
  g->Reduce(ynn_reduce_sum, 3143, 6362, {2}, true);
  g->ShapeProduct(3143, 6361, {2});
  g->Binary(ynn_binary_divide, 6362, 6361, 3144);
  g->Binary(ynn_binary_add, 3144, 6539, 3145);
  g->Unary(ynn_unary_rsqrt, 3145, 3146);
  g->Binary(ynn_binary_multiply, 3142, 3146, 3147);
  g->Binary(ynn_binary_multiply, 3147, 6937, 3148);
  g->Quantize(3148, 3149, 0.019482526928186417, 0);
  g->Transpose(6931, 5240, {1,0});
  g->Binary(ynn_binary_multiply, 5238, 5239, 5236);
  g->Dot(3149, 5240, YNN_INVALID_VALUE_ID, 5235, 1);
  g->DequantizeTensor(5235, YNN_INVALID_VALUE_ID, 5236, 5237);
  g->QuantizeTensor(5237, 6504, 4198, 3150);
  g->Dequantize(3150, 3152, 0.02005414292216301, 0);
  g->Transpose(6930, 5245, {1,0});
  g->Binary(ynn_binary_multiply, 5238, 5244, 5242);
  g->Dot(3149, 5245, YNN_INVALID_VALUE_ID, 5241, 1);
  g->DequantizeTensor(5241, YNN_INVALID_VALUE_ID, 5242, 5243);
  g->QuantizeTensor(5243, 6504, 4198, 3153);
  g->Dequantize(3153, 3154, 0.02005414292216301, 0);
  g->Polynomial(3154, 6365, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6365, 6366);
  g->Binary(ynn_binary_add, 6366, 5500, 6363);
  g->Binary(ynn_binary_multiply, 3154, 5498, 6364);
  g->Binary(ynn_binary_multiply, 6364, 6363, 3155);
  g->Binary(ynn_binary_multiply, 3152, 3155, 3156);
  g->Quantize(3156, 3157, 0.03297245129942894, 0);
  g->Transpose(6929, 5251, {1,0});
  g->Binary(ynn_binary_multiply, 4360, 5250, 5247);
  g->Dot(3157, 5251, YNN_INVALID_VALUE_ID, 5246, 1);
  g->DequantizeTensor(5246, YNN_INVALID_VALUE_ID, 5247, 5248);
  g->QuantizeTensor(5248, 6504, 5249, 3158);
  g->Dequantize(3158, 3159, 0.022154856473207474, 0);
  g->Unary(ynn_unary_square, 3159, 3160);
  g->Reduce(ynn_reduce_sum, 3160, 6368, {2}, true);
  g->ShapeProduct(3160, 6367, {2});
  g->Binary(ynn_binary_divide, 6368, 6367, 3162);
  g->Binary(ynn_binary_add, 3162, 6539, 3163);
  g->Unary(ynn_unary_rsqrt, 3163, 3164);
  g->Binary(ynn_binary_multiply, 3159, 3164, 3165);
  g->Binary(ynn_binary_multiply, 3165, 6935, 3166);
  g->Binary(ynn_binary_add, 3166, 3142, 3167);
}

// Scope: "Layer3 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(427, 3168, {0,0,3,0}, {-1,-1,1,-1});
  g->Reshape(3168, 3169, {1,1,256});
  g->Unary(ynn_unary_square, 3169, 3170);
  g->Reduce(ynn_reduce_sum, 3170, 6370, {2}, true);
  g->ShapeProduct(3170, 6369, {2});
  g->Binary(ynn_binary_divide, 6370, 6369, 3171);
  g->Binary(ynn_binary_add, 3171, 6539, 3173);
  g->Unary(ynn_unary_rsqrt, 3173, 3174);
  g->Binary(ynn_binary_multiply, 3169, 3174, 3175);
  g->Binary(ynn_binary_multiply, 3175, 7118, 3176);
  g->Binary(ynn_binary_multiply, 7142, 6542, 3177);
  g->Binary(ynn_binary_add, 3176, 3177, 3178);
  g->Binary(ynn_binary_multiply, 3178, 6536, 3179);
  g->Quantize(3167, 3180, 0.2861534655094147, 0);
  g->Transpose(6932, 5258, {1,0});
  g->Binary(ynn_binary_multiply, 5255, 5257, 5253);
  g->Dot(3180, 5258, YNN_INVALID_VALUE_ID, 5252, 1);
  g->DequantizeTensor(5252, YNN_INVALID_VALUE_ID, 5253, 5254);
  g->QuantizeTensor(5254, 6504, 5256, 3181);
  g->Dequantize(3181, 3182, 0.050688985735177994, 0);
  g->Polynomial(3182, 6373, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6373, 6374);
  g->Binary(ynn_binary_add, 6374, 5500, 6371);
  g->Binary(ynn_binary_multiply, 3182, 5498, 6372);
  g->Binary(ynn_binary_multiply, 6372, 6371, 3183);
  g->Binary(ynn_binary_multiply, 3183, 3179, 3184);
  g->Quantize(3184, 3185, 0.06692913919687271, 0);
  g->Transpose(6933, 5265, {1,0});
  g->Binary(ynn_binary_multiply, 5262, 5264, 5260);
  g->Dot(3185, 5265, YNN_INVALID_VALUE_ID, 5259, 1);
  g->DequantizeTensor(5259, YNN_INVALID_VALUE_ID, 5260, 5261);
  g->QuantizeTensor(5261, 6504, 5263, 3186);
  g->Dequantize(3186, 3187, 0.0805763527750969, 0);
  g->Unary(ynn_unary_square, 3187, 3188);
  g->Reduce(ynn_reduce_sum, 3188, 6376, {2}, true);
  g->ShapeProduct(3188, 6375, {2});
  g->Binary(ynn_binary_divide, 6376, 6375, 3189);
  g->Binary(ynn_binary_add, 3189, 6539, 3190);
  g->Unary(ynn_unary_rsqrt, 3190, 3191);
  g->Binary(ynn_binary_multiply, 3187, 3191, 3192);
  g->Binary(ynn_binary_multiply, 3192, 6936, 3194);
  g->Binary(ynn_binary_add, 3167, 3194, 3195);
  g->Binary(ynn_binary_multiply, 3195, 6928, 3196);
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
  g->Quantize(3202, 3203, 0.023374712094664574, 0);
  g->Transpose(7026, 5272, {1,0});
  g->Binary(ynn_binary_multiply, 5269, 5271, 5267);
  g->Dot(3203, 5272, YNN_INVALID_VALUE_ID, 5266, 1);
  g->DequantizeTensor(5266, YNN_INVALID_VALUE_ID, 5267, 5268);
  g->QuantizeTensor(5268, 6504, 5270, 3204);
  g->Dequantize(3204, 3205, 0.024852370843291283, 0);
  g->Reshape(3205, 3206, {1,1,1,512});
  g->Reshape(3206, 3207, {1,1,1,512});
  g->Unary(ynn_unary_square, 3207, 3208);
  g->Reduce(ynn_reduce_sum, 3208, 6380, {3}, true);
  g->ShapeProduct(3208, 6379, {3});
  g->Binary(ynn_binary_divide, 6380, 6379, 3209);
  g->Binary(ynn_binary_add, 3209, 6539, 3210);
  g->Unary(ynn_unary_rsqrt, 3210, 3211);
  g->Binary(ynn_binary_multiply, 3207, 3211, 3212);
  g->Binary(ynn_binary_multiply, 3212, 7025, 3213);
  g->Slice(3213, 3214, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(3213, 3215, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 3215, 3216);
  g->Concat({3216,3214}, 3217, 3);
  g->Binary(ynn_binary_multiply, 3213, 3594, 3218);
  g->Binary(ynn_binary_multiply, 3217, 2, 3219);
  g->Binary(ynn_binary_add, 3218, 3219, 3220);
  g->Transpose(7030, 5277, {1,0});
  g->Binary(ynn_binary_multiply, 5269, 5276, 5274);
  g->Dot(3203, 5277, YNN_INVALID_VALUE_ID, 5273, 1);
  g->DequantizeTensor(5273, YNN_INVALID_VALUE_ID, 5274, 5275);
  g->QuantizeTensor(5275, 6504, 5270, 3221);
  g->Dequantize(3221, 3222, 0.024852370843291283, 0);
  g->Reshape(3222, 3223, {1,1,1,512});
  g->Reshape(3223, 3224, {1,1,1,512});
  g->Unary(ynn_unary_square, 3224, 3225);
  g->Reduce(ynn_reduce_sum, 3225, 6382, {3}, true);
  g->ShapeProduct(3225, 6381, {3});
  g->Binary(ynn_binary_divide, 6382, 6381, 3226);
  g->Binary(ynn_binary_add, 3226, 6539, 3227);
  g->Unary(ynn_unary_rsqrt, 3227, 3228);
  g->Binary(ynn_binary_multiply, 3224, 3228, 3229);
}

// Scope: "Layer4 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(3220, 3230, 0.0011563472216948867, 0);
  g->Append(6514, 3230, 7164, 2, s2, slinky::expr(int64_t{1}));
  g->View(7164, 7194, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(3229, 3232, 0.01785714365541935, 0);
  g->Append(6529, 3232, 7179, 2, s2, slinky::expr(int64_t{1}));
  g->View(7179, 7209, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer4 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(7029, 5289, {1,0});
  g->Binary(ynn_binary_multiply, 5269, 5288, 5285);
  g->Dot(3203, 5289, YNN_INVALID_VALUE_ID, 5284, 1);
  g->DequantizeTensor(5284, YNN_INVALID_VALUE_ID, 5285, 5286);
  g->QuantizeTensor(5286, 6504, 5287, 3233);
  g->Dequantize(3233, 3234, 0.03248032554984093, 0);
  g->SplitDim(3234, 3235, 2, {8,512});
  g->FuseDims(3235, 3237, 1, 2);
  g->SplitDim(3237, 3236, 1, {8,1});
  g->Unary(ynn_unary_square, 3236, 3238);
  g->Reduce(ynn_reduce_sum, 3238, 6384, {3}, true);
  g->ShapeProduct(3238, 6383, {3});
  g->Binary(ynn_binary_divide, 6384, 6383, 3239);
  g->Binary(ynn_binary_add, 3239, 6539, 3241);
  g->Unary(ynn_unary_rsqrt, 3241, 3242);
  g->Binary(ynn_binary_multiply, 3236, 3242, 3243);
  g->Binary(ynn_binary_multiply, 3243, 7028, 3244);
  g->Slice(3244, 3245, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(3244, 3246, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 3246, 3247);
  g->Concat({3247,3245}, 3248, 3);
  g->Binary(ynn_binary_multiply, 3244, 3594, 3249);
  g->Binary(ynn_binary_multiply, 3248, 2, 3250);
  g->Binary(ynn_binary_add, 3249, 3250, 3252);
}

// Scope: "Layer4 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7194, 3253, 0.0011563472216948867, 0);
  g->Dequantize(7209, 3254, 0.01785714365541935, 0);
  g->Matmul(3252, 3253, 3255, false, true);
  g->Mask(3255, 6574, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 6574, 6388, {-1}, true);
  g->Binary(ynn_binary_subtract, 6574, 6388, 6385);
  g->Unary(ynn_unary_exp, 6385, 6386);
  g->Reduce(ynn_reduce_sum, 6386, 6389, {-1}, true);
  g->Binary(ynn_binary_divide, 5500, 6389, 6387);
  g->Binary(ynn_binary_multiply, 6386, 6387, 3256);
  g->Matmul(3256, 3254, 3257, false, false);
}

// Scope: "Layer4 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(3257, 3259, 1, 2);
  g->SplitDim(3259, 3258, 1, {1,8});
  g->FuseDims(3258, 3260, 2, 2);
  g->Quantize(3260, 3261, 0.017962608486413956, 0);
  g->Transpose(7027, 5295, {1,0});
  g->Binary(ynn_binary_multiply, 3813, 5294, 5291);
  g->Dot(3261, 5295, YNN_INVALID_VALUE_ID, 5290, 1);
  g->DequantizeTensor(5290, YNN_INVALID_VALUE_ID, 5291, 5292);
  g->QuantizeTensor(5292, 6504, 5293, 3264);
  g->Dequantize(3264, 3265, 0.17608338594436646, 0);
}

// Scope: "Layer4 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3196, 3197);
  g->Reduce(ynn_reduce_sum, 3197, 6378, {2}, true);
  g->ShapeProduct(3197, 6377, {2});
  g->Binary(ynn_binary_divide, 6378, 6377, 3198);
  g->Binary(ynn_binary_add, 3198, 6539, 3199);
  g->Unary(ynn_unary_rsqrt, 3199, 3200);
  g->Binary(ynn_binary_multiply, 3196, 3200, 3201);
  g->Binary(ynn_binary_multiply, 3201, 7014, 3202);
  BuildLayer4AttentionKvProjection(ctx);
  BuildLayer4AttentionCacheUpdate(ctx);
  BuildLayer4AttentionQueryProjection(ctx);
  BuildLayer4AttentionSdpa(ctx);
  BuildLayer4AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 3265, 3266);
  g->Reduce(ynn_reduce_sum, 3266, 6391, {2}, true);
  g->ShapeProduct(3266, 6390, {2});
  g->Binary(ynn_binary_divide, 6391, 6390, 3267);
  g->Binary(ynn_binary_add, 3267, 6539, 3268);
  g->Unary(ynn_unary_rsqrt, 3268, 3269);
  g->Binary(ynn_binary_multiply, 3265, 3269, 3270);
  g->Binary(ynn_binary_multiply, 3270, 7021, 3271);
  g->Binary(ynn_binary_add, 3271, 3196, 3272);
}

// Scope: "Layer4 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3272, 3273);
  g->Reduce(ynn_reduce_sum, 3273, 6393, {2}, true);
  g->ShapeProduct(3273, 6392, {2});
  g->Binary(ynn_binary_divide, 6393, 6392, 3276);
  g->Binary(ynn_binary_add, 3276, 6539, 3277);
  g->Unary(ynn_unary_rsqrt, 3277, 3278);
  g->Binary(ynn_binary_multiply, 3272, 3278, 3279);
  g->Binary(ynn_binary_multiply, 3279, 7024, 3280);
  g->Quantize(3280, 3281, 0.060907524079084396, 0);
  g->Transpose(7018, 5301, {1,0});
  g->Binary(ynn_binary_multiply, 5299, 5300, 5297);
  g->Dot(3281, 5301, YNN_INVALID_VALUE_ID, 5296, 1);
  g->DequantizeTensor(5296, YNN_INVALID_VALUE_ID, 5297, 5298);
  g->QuantizeTensor(5298, 6504, 3724, 3282);
  g->Dequantize(3282, 3283, 0.09251969307661057, 0);
  g->Transpose(7017, 5306, {1,0});
  g->Binary(ynn_binary_multiply, 5299, 5305, 5303);
  g->Dot(3281, 5306, YNN_INVALID_VALUE_ID, 5302, 1);
  g->DequantizeTensor(5302, YNN_INVALID_VALUE_ID, 5303, 5304);
  g->QuantizeTensor(5304, 6504, 3724, 3284);
  g->Dequantize(3284, 3286, 0.09251969307661057, 0);
  g->Polynomial(3286, 6398, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6398, 6399);
  g->Binary(ynn_binary_add, 6399, 5500, 6396);
  g->Binary(ynn_binary_multiply, 3286, 5498, 6397);
  g->Binary(ynn_binary_multiply, 6397, 6396, 3287);
  g->Binary(ynn_binary_multiply, 3283, 3287, 3288);
  g->Quantize(3288, 3289, 0.3444882035255432, 0);
  g->Transpose(7016, 5313, {1,0});
  g->Binary(ynn_binary_multiply, 5310, 5312, 5308);
  g->Dot(3289, 5313, YNN_INVALID_VALUE_ID, 5307, 1);
  g->DequantizeTensor(5307, YNN_INVALID_VALUE_ID, 5308, 5309);
  g->QuantizeTensor(5309, 6504, 5311, 3290);
  g->Dequantize(3290, 3291, 0.13582009077072144, 0);
  g->Unary(ynn_unary_square, 3291, 3292);
  g->Reduce(ynn_reduce_sum, 3292, 6401, {2}, true);
  g->ShapeProduct(3292, 6400, {2});
  g->Binary(ynn_binary_divide, 6401, 6400, 3293);
  g->Binary(ynn_binary_add, 3293, 6539, 3294);
  g->Unary(ynn_unary_rsqrt, 3294, 3295);
  g->Binary(ynn_binary_multiply, 3291, 3295, 3297);
  g->Binary(ynn_binary_multiply, 3297, 7022, 3298);
  g->Binary(ynn_binary_add, 3298, 3272, 3299);
}

// Scope: "Layer4 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(427, 3300, {0,0,4,0}, {-1,-1,1,-1});
  g->Reshape(3300, 3301, {1,1,256});
  g->Unary(ynn_unary_square, 3301, 3302);
  g->Reduce(ynn_reduce_sum, 3302, 6403, {2}, true);
  g->ShapeProduct(3302, 6402, {2});
  g->Binary(ynn_binary_divide, 6403, 6402, 3303);
  g->Binary(ynn_binary_add, 3303, 6539, 3304);
  g->Unary(ynn_unary_rsqrt, 3304, 3305);
  g->Binary(ynn_binary_multiply, 3301, 3305, 3306);
  g->Binary(ynn_binary_multiply, 3306, 7118, 3308);
  g->Binary(ynn_binary_multiply, 7148, 6542, 3309);
  g->Binary(ynn_binary_add, 3308, 3309, 3310);
  g->Binary(ynn_binary_multiply, 3310, 6536, 3311);
  g->Quantize(3299, 3312, 0.41414323449134827, 0);
  g->Transpose(7019, 5319, {1,0});
  g->Binary(ynn_binary_multiply, 5317, 5318, 5315);
  g->Dot(3312, 5319, YNN_INVALID_VALUE_ID, 5314, 1);
  g->DequantizeTensor(5314, YNN_INVALID_VALUE_ID, 5315, 5316);
  g->QuantizeTensor(5316, 6504, 5152, 3313);
  g->Dequantize(3313, 3314, 0.039862215518951416, 0);
  g->Polynomial(3314, 6406, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6406, 6407);
  g->Binary(ynn_binary_add, 6407, 5500, 6404);
  g->Binary(ynn_binary_multiply, 3314, 5498, 6405);
  g->Binary(ynn_binary_multiply, 6405, 6404, 3315);
  g->Binary(ynn_binary_multiply, 3315, 3311, 3316);
  g->Quantize(3316, 3317, 0.30314961075782776, 0);
  g->Transpose(7020, 5326, {1,0});
  g->Binary(ynn_binary_multiply, 5323, 5325, 5321);
  g->Dot(3317, 5326, YNN_INVALID_VALUE_ID, 5320, 1);
  g->DequantizeTensor(5320, YNN_INVALID_VALUE_ID, 5321, 5322);
  g->QuantizeTensor(5322, 6504, 5324, 3319);
  g->Dequantize(3319, 3320, 0.16701875627040863, 0);
  g->Unary(ynn_unary_square, 3320, 3321);
  g->Reduce(ynn_reduce_sum, 3321, 6409, {2}, true);
  g->ShapeProduct(3321, 6408, {2});
  g->Binary(ynn_binary_divide, 6409, 6408, 3322);
  g->Binary(ynn_binary_add, 3322, 6539, 3323);
  g->Unary(ynn_unary_rsqrt, 3323, 3324);
  g->Binary(ynn_binary_multiply, 3320, 3324, 3325);
  g->Binary(ynn_binary_multiply, 3325, 7023, 3326);
  g->Binary(ynn_binary_add, 3299, 3326, 3327);
  g->Binary(ynn_binary_multiply, 3327, 7015, 3328);
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
  g->Quantize(3335, 3336, 0.07399173825979233, 0);
  g->Transpose(7043, 5333, {1,0});
  g->Binary(ynn_binary_multiply, 5330, 5332, 5328);
  g->Dot(3336, 5333, YNN_INVALID_VALUE_ID, 5327, 1);
  g->DequantizeTensor(5327, YNN_INVALID_VALUE_ID, 5328, 5329);
  g->QuantizeTensor(5329, 6504, 5331, 3337);
  g->Dequantize(3337, 3338, 0.09842520207166672, 0);
  g->Reshape(3338, 3339, {1,1,1,256});
  g->Reshape(3339, 3341, {1,1,1,256});
  g->Unary(ynn_unary_square, 3341, 3342);
  g->Reduce(ynn_reduce_sum, 3342, 6413, {3}, true);
  g->ShapeProduct(3342, 6412, {3});
  g->Binary(ynn_binary_divide, 6413, 6412, 3343);
  g->Binary(ynn_binary_add, 3343, 6539, 3344);
  g->Unary(ynn_unary_rsqrt, 3344, 3345);
  g->Binary(ynn_binary_multiply, 3341, 3345, 3346);
  g->Binary(ynn_binary_multiply, 3346, 7042, 3347);
  g->Slice(3347, 3348, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3347, 3349, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3349, 3350);
  g->Concat({3350,3348}, 3352, 3);
  g->Binary(ynn_binary_multiply, 3347, 3067, 3353);
  g->Binary(ynn_binary_multiply, 3352, 3172, 3354);
  g->Binary(ynn_binary_add, 3353, 3354, 3355);
  g->Transpose(7047, 5338, {1,0});
  g->Binary(ynn_binary_multiply, 5330, 5337, 5335);
  g->Dot(3336, 5338, YNN_INVALID_VALUE_ID, 5334, 1);
  g->DequantizeTensor(5334, YNN_INVALID_VALUE_ID, 5335, 5336);
  g->QuantizeTensor(5336, 6504, 5331, 3356);
  g->Dequantize(3356, 3357, 0.09842520207166672, 0);
  g->Reshape(3357, 3358, {1,1,1,256});
  g->Reshape(3358, 3359, {1,1,1,256});
  g->Unary(ynn_unary_square, 3359, 3360);
  g->Reduce(ynn_reduce_sum, 3360, 6415, {3}, true);
  g->ShapeProduct(3360, 6414, {3});
  g->Binary(ynn_binary_divide, 6415, 6414, 3362);
  g->Binary(ynn_binary_add, 3362, 6539, 3363);
  g->Unary(ynn_unary_rsqrt, 3363, 3364);
  g->Binary(ynn_binary_multiply, 3359, 3364, 3365);
}

// Scope: "Layer5 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(3355, 3366, 0.006011798977851868, 0);
  g->Append(6515, 3366, 7165, 2, s2, slinky::expr(int64_t{1}));
  g->View(7165, 7195, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(3365, 3367, 0.047244105488061905, 0);
  g->Append(6530, 3367, 7180, 2, s2, slinky::expr(int64_t{1}));
  g->View(7180, 7210, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer5 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(7046, 5343, {1,0});
  g->Binary(ynn_binary_multiply, 5330, 5342, 5340);
  g->Dot(3336, 5343, YNN_INVALID_VALUE_ID, 5339, 1);
  g->DequantizeTensor(5339, YNN_INVALID_VALUE_ID, 5340, 5341);
  g->QuantizeTensor(5341, 6504, 4096, 3369);
  g->Dequantize(3369, 3370, 0.13385827839374542, 0);
  g->SplitDim(3370, 3371, 2, {8,256});
  g->FuseDims(3371, 3373, 1, 2);
  g->SplitDim(3373, 3372, 1, {8,1});
  g->Unary(ynn_unary_square, 3372, 3374);
  g->Reduce(ynn_reduce_sum, 3374, 6417, {3}, true);
  g->ShapeProduct(3374, 6416, {3});
  g->Binary(ynn_binary_divide, 6417, 6416, 3375);
  g->Binary(ynn_binary_add, 3375, 6539, 3376);
  g->Unary(ynn_unary_rsqrt, 3376, 3377);
  g->Binary(ynn_binary_multiply, 3372, 3377, 3378);
  g->Binary(ynn_binary_multiply, 3378, 7045, 3381);
  g->Slice(3381, 3382, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3381, 3383, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3383, 3384);
  g->Concat({3384,3382}, 3385, 3);
  g->Binary(ynn_binary_multiply, 3381, 3067, 3386);
  g->Binary(ynn_binary_multiply, 3385, 3172, 3387);
  g->Binary(ynn_binary_add, 3386, 3387, 3388);
}

// Scope: "Layer5 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7195, 3389, 0.006011798977851868, 0);
  g->Dequantize(7210, 3390, 0.047244105488061905, 0);
  g->Matmul(3388, 3389, 3392, false, true);
  g->Mask(3392, 6575, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6575, 6421, {-1}, true);
  g->Binary(ynn_binary_subtract, 6575, 6421, 6418);
  g->Unary(ynn_unary_exp, 6418, 6419);
  g->Reduce(ynn_reduce_sum, 6419, 6422, {-1}, true);
  g->Binary(ynn_binary_divide, 5500, 6422, 6420);
  g->Binary(ynn_binary_multiply, 6419, 6420, 3393);
  g->Matmul(3393, 3390, 3394, false, false);
}

// Scope: "Layer5 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(3394, 3396, 1, 2);
  g->SplitDim(3396, 3395, 1, {1,8});
  g->FuseDims(3395, 3397, 2, 2);
  g->Quantize(3397, 3398, 0.026451781392097473, 0);
  g->Transpose(7044, 5350, {1,0});
  g->Binary(ynn_binary_multiply, 5347, 5349, 5345);
  g->Dot(3398, 5350, YNN_INVALID_VALUE_ID, 5344, 1);
  g->DequantizeTensor(5344, YNN_INVALID_VALUE_ID, 5345, 5346);
  g->QuantizeTensor(5346, 6504, 5348, 3399);
  g->Dequantize(3399, 3400, 0.043322544544935226, 0);
}

// Scope: "Layer5 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3328, 3330);
  g->Reduce(ynn_reduce_sum, 3330, 6411, {2}, true);
  g->ShapeProduct(3330, 6410, {2});
  g->Binary(ynn_binary_divide, 6411, 6410, 3331);
  g->Binary(ynn_binary_add, 3331, 6539, 3332);
  g->Unary(ynn_unary_rsqrt, 3332, 3333);
  g->Binary(ynn_binary_multiply, 3328, 3333, 3334);
  g->Binary(ynn_binary_multiply, 3334, 7031, 3335);
  BuildLayer5AttentionKvProjection(ctx);
  BuildLayer5AttentionCacheUpdate(ctx);
  BuildLayer5AttentionQueryProjection(ctx);
  BuildLayer5AttentionSdpa(ctx);
  BuildLayer5AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 3400, 3401);
  g->Reduce(ynn_reduce_sum, 3401, 6424, {2}, true);
  g->ShapeProduct(3401, 6423, {2});
  g->Binary(ynn_binary_divide, 6424, 6423, 3403);
  g->Binary(ynn_binary_add, 3403, 6539, 3404);
  g->Unary(ynn_unary_rsqrt, 3404, 3405);
  g->Binary(ynn_binary_multiply, 3400, 3405, 3406);
  g->Binary(ynn_binary_multiply, 3406, 7038, 3407);
  g->Binary(ynn_binary_add, 3407, 3328, 3408);
}

// Scope: "Layer5 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3408, 3409);
  g->Reduce(ynn_reduce_sum, 3409, 6426, {2}, true);
  g->ShapeProduct(3409, 6425, {2});
  g->Binary(ynn_binary_divide, 6426, 6425, 3410);
  g->Binary(ynn_binary_add, 3410, 6539, 3411);
  g->Unary(ynn_unary_rsqrt, 3411, 3412);
  g->Binary(ynn_binary_multiply, 3408, 3412, 3414);
  g->Binary(ynn_binary_multiply, 3414, 7041, 3415);
  g->Quantize(3415, 3416, 0.03518042340874672, 0);
  g->Transpose(7035, 5356, {1,0});
  g->Binary(ynn_binary_multiply, 5354, 5355, 5352);
  g->Dot(3416, 5356, YNN_INVALID_VALUE_ID, 5351, 1);
  g->DequantizeTensor(5351, YNN_INVALID_VALUE_ID, 5352, 5353);
  g->QuantizeTensor(5353, 6504, 4571, 3417);
  g->Dequantize(3417, 3418, 0.03567914664745331, 0);
  g->Transpose(7034, 5361, {1,0});
  g->Binary(ynn_binary_multiply, 5354, 5360, 5358);
  g->Dot(3416, 5361, YNN_INVALID_VALUE_ID, 5357, 1);
  g->DequantizeTensor(5357, YNN_INVALID_VALUE_ID, 5358, 5359);
  g->QuantizeTensor(5359, 6504, 4571, 3419);
  g->Dequantize(3419, 3420, 0.03567914664745331, 0);
  g->Polynomial(3420, 6429, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6429, 6430);
  g->Binary(ynn_binary_add, 6430, 5500, 6427);
  g->Binary(ynn_binary_multiply, 3420, 5498, 6428);
  g->Binary(ynn_binary_multiply, 6428, 6427, 3421);
  g->Binary(ynn_binary_multiply, 3418, 3421, 3422);
  g->Quantize(3422, 3424, 0.08415354788303375, 0);
  g->Transpose(7033, 5368, {1,0});
  g->Binary(ynn_binary_multiply, 5365, 5367, 5363);
  g->Dot(3424, 5368, YNN_INVALID_VALUE_ID, 5362, 1);
  g->DequantizeTensor(5362, YNN_INVALID_VALUE_ID, 5363, 5364);
  g->QuantizeTensor(5364, 6504, 5366, 3425);
  g->Dequantize(3425, 3426, 0.06301677227020264, 0);
  g->Unary(ynn_unary_square, 3426, 3427);
  g->Reduce(ynn_reduce_sum, 3427, 6432, {2}, true);
  g->ShapeProduct(3427, 6431, {2});
  g->Binary(ynn_binary_divide, 6432, 6431, 3428);
  g->Binary(ynn_binary_add, 3428, 6539, 3429);
  g->Unary(ynn_unary_rsqrt, 3429, 3430);
  g->Binary(ynn_binary_multiply, 3426, 3430, 3431);
  g->Binary(ynn_binary_multiply, 3431, 7039, 3432);
  g->Binary(ynn_binary_add, 3432, 3408, 3433);
}

// Scope: "Layer5 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(427, 3435, {0,0,5,0}, {-1,-1,1,-1});
  g->Reshape(3435, 3436, {1,1,256});
  g->Unary(ynn_unary_square, 3436, 3437);
  g->Reduce(ynn_reduce_sum, 3437, 6434, {2}, true);
  g->ShapeProduct(3437, 6433, {2});
  g->Binary(ynn_binary_divide, 6434, 6433, 3438);
  g->Binary(ynn_binary_add, 3438, 6539, 3439);
  g->Unary(ynn_unary_rsqrt, 3439, 3440);
  g->Binary(ynn_binary_multiply, 3436, 3440, 3441);
  g->Binary(ynn_binary_multiply, 3441, 7118, 3442);
  g->Binary(ynn_binary_multiply, 7149, 6542, 3443);
  g->Binary(ynn_binary_add, 3442, 3443, 3444);
  g->Binary(ynn_binary_multiply, 3444, 6536, 3445);
  g->Quantize(3433, 3446, 0.3165745139122009, 0);
  g->Transpose(7036, 5375, {1,0});
  g->Binary(ynn_binary_multiply, 5372, 5374, 5370);
  g->Dot(3446, 5375, YNN_INVALID_VALUE_ID, 5369, 1);
  g->DequantizeTensor(5369, YNN_INVALID_VALUE_ID, 5370, 5371);
  g->QuantizeTensor(5371, 6504, 5373, 3447);
  g->Dequantize(3447, 3448, 0.0393700897693634, 0);
  g->Polynomial(3448, 6437, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6437, 6438);
  g->Binary(ynn_binary_add, 6438, 5500, 6435);
  g->Binary(ynn_binary_multiply, 3448, 5498, 6436);
  g->Binary(ynn_binary_multiply, 6436, 6435, 3449);
  g->Binary(ynn_binary_multiply, 3449, 3445, 3450);
  g->Quantize(3450, 3451, 0.22933071851730347, 0);
  g->Transpose(7037, 5382, {1,0});
  g->Binary(ynn_binary_multiply, 5379, 5381, 5377);
  g->Dot(3451, 5382, YNN_INVALID_VALUE_ID, 5376, 1);
  g->DequantizeTensor(5376, YNN_INVALID_VALUE_ID, 5377, 5378);
  g->QuantizeTensor(5378, 6504, 5380, 3452);
  g->Dequantize(3452, 3453, 0.12322933226823807, 0);
  g->Unary(ynn_unary_square, 3453, 3454);
  g->Reduce(ynn_reduce_sum, 3454, 6445, {2}, true);
  g->ShapeProduct(3454, 6444, {2});
  g->Binary(ynn_binary_divide, 6445, 6444, 3456);
  g->Binary(ynn_binary_add, 3456, 6539, 3457);
  g->Unary(ynn_unary_rsqrt, 3457, 3458);
  g->Binary(ynn_binary_multiply, 3453, 3458, 3459);
  g->Binary(ynn_binary_multiply, 3459, 7040, 3460);
  g->Binary(ynn_binary_add, 3433, 3460, 3461);
  g->Binary(ynn_binary_multiply, 3461, 7032, 3462);
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
  g->Quantize(3469, 3470, 0.341854453086853, 0);
  g->Transpose(7060, 5389, {1,0});
  g->Binary(ynn_binary_multiply, 5386, 5388, 5384);
  g->Dot(3470, 5389, YNN_INVALID_VALUE_ID, 5383, 1);
  g->DequantizeTensor(5383, YNN_INVALID_VALUE_ID, 5384, 5385);
  g->QuantizeTensor(5385, 6504, 5387, 3471);
  g->Dequantize(3471, 3472, 0.28740158677101135, 0);
  g->Reshape(3472, 3473, {1,1,1,256});
  g->Reshape(3473, 3474, {1,1,1,256});
  g->Unary(ynn_unary_square, 3474, 3475);
  g->Reduce(ynn_reduce_sum, 3475, 6449, {3}, true);
  g->ShapeProduct(3475, 6448, {3});
  g->Binary(ynn_binary_divide, 6449, 6448, 3476);
  g->Binary(ynn_binary_add, 3476, 6539, 3479);
  g->Unary(ynn_unary_rsqrt, 3479, 3480);
  g->Binary(ynn_binary_multiply, 3474, 3480, 3481);
  g->Binary(ynn_binary_multiply, 3481, 7059, 3482);
  g->Slice(3482, 3483, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3482, 3484, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3484, 3485);
  g->Concat({3485,3483}, 3486, 3);
  g->Binary(ynn_binary_multiply, 3482, 3067, 3487);
  g->Binary(ynn_binary_multiply, 3486, 3172, 3488);
  g->Binary(ynn_binary_add, 3487, 3488, 3491);
  g->Transpose(7064, 5394, {1,0});
  g->Binary(ynn_binary_multiply, 5386, 5393, 5391);
  g->Dot(3470, 5394, YNN_INVALID_VALUE_ID, 5390, 1);
  g->DequantizeTensor(5390, YNN_INVALID_VALUE_ID, 5391, 5392);
  g->QuantizeTensor(5392, 6504, 5387, 3492);
  g->Dequantize(3492, 3493, 0.28740158677101135, 0);
  g->Reshape(3493, 3494, {1,1,1,256});
  g->Reshape(3494, 3495, {1,1,1,256});
  g->Unary(ynn_unary_square, 3495, 3496);
  g->Reduce(ynn_reduce_sum, 3496, 6451, {3}, true);
  g->ShapeProduct(3496, 6450, {3});
  g->Binary(ynn_binary_divide, 6451, 6450, 3497);
  g->Binary(ynn_binary_add, 3497, 6539, 3498);
  g->Unary(ynn_unary_rsqrt, 3498, 3499);
  g->Binary(ynn_binary_multiply, 3495, 3499, 3501);
}

// Scope: "Layer6 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(3491, 3502, 0.0057707298547029495, 0);
  g->Append(6516, 3502, 7166, 2, s2, slinky::expr(int64_t{1}));
  g->View(7166, 7196, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(3501, 3503, 0.047244105488061905, 0);
  g->Append(6531, 3503, 7181, 2, s2, slinky::expr(int64_t{1}));
  g->View(7181, 7211, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer6 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(7063, 5400, {1,0});
  g->Binary(ynn_binary_multiply, 5386, 5399, 5396);
  g->Dot(3470, 5400, YNN_INVALID_VALUE_ID, 5395, 1);
  g->DequantizeTensor(5395, YNN_INVALID_VALUE_ID, 5396, 5397);
  g->QuantizeTensor(5397, 6504, 5398, 3504);
  g->Dequantize(3504, 3505, 0.4566929042339325, 0);
  g->SplitDim(3505, 3507, 2, {8,256});
  g->FuseDims(3507, 3509, 1, 2);
  g->SplitDim(3509, 3508, 1, {8,1});
  g->Unary(ynn_unary_square, 3508, 3510);
  g->Reduce(ynn_reduce_sum, 3510, 6453, {3}, true);
  g->ShapeProduct(3510, 6452, {3});
  g->Binary(ynn_binary_divide, 6453, 6452, 3511);
  g->Binary(ynn_binary_add, 3511, 6539, 3512);
  g->Unary(ynn_unary_rsqrt, 3512, 3513);
  g->Binary(ynn_binary_multiply, 3508, 3513, 3514);
  g->Binary(ynn_binary_multiply, 3514, 7062, 3515);
  g->Slice(3515, 3516, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3515, 3517, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3517, 3519);
  g->Concat({3519,3516}, 3520, 3);
  g->Binary(ynn_binary_multiply, 3515, 3067, 3521);
  g->Binary(ynn_binary_multiply, 3520, 3172, 3522);
  g->Binary(ynn_binary_add, 3521, 3522, 3523);
}

// Scope: "Layer6 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7196, 3524, 0.0057707298547029495, 0);
  g->Dequantize(7211, 3525, 0.047244105488061905, 0);
  g->Matmul(3523, 3524, 3526, false, true);
  g->Mask(3526, 6576, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6576, 6457, {-1}, true);
  g->Binary(ynn_binary_subtract, 6576, 6457, 6454);
  g->Unary(ynn_unary_exp, 6454, 6455);
  g->Reduce(ynn_reduce_sum, 6455, 6458, {-1}, true);
  g->Binary(ynn_binary_divide, 5500, 6458, 6456);
  g->Binary(ynn_binary_multiply, 6455, 6456, 3527);
  g->Matmul(3527, 3525, 3529, false, false);
}

// Scope: "Layer6 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(3529, 3531, 1, 2);
  g->SplitDim(3531, 3530, 1, {1,8});
  g->FuseDims(3530, 3532, 2, 2);
  g->Quantize(3532, 3533, 0.0354330837726593, 0);
  g->Transpose(7061, 5414, {1,0});
  g->Binary(ynn_binary_multiply, 5411, 5413, 5409);
  g->Dot(3533, 5414, YNN_INVALID_VALUE_ID, 5408, 1);
  g->DequantizeTensor(5408, YNN_INVALID_VALUE_ID, 5409, 5410);
  g->QuantizeTensor(5410, 6504, 5412, 3534);
  g->Dequantize(3534, 3535, 0.05930274724960327, 0);
}

// Scope: "Layer6 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3462, 3463);
  g->Reduce(ynn_reduce_sum, 3463, 6447, {2}, true);
  g->ShapeProduct(3463, 6446, {2});
  g->Binary(ynn_binary_divide, 6447, 6446, 3464);
  g->Binary(ynn_binary_add, 3464, 6539, 3465);
  g->Unary(ynn_unary_rsqrt, 3465, 3467);
  g->Binary(ynn_binary_multiply, 3462, 3467, 3468);
  g->Binary(ynn_binary_multiply, 3468, 7048, 3469);
  BuildLayer6AttentionKvProjection(ctx);
  BuildLayer6AttentionCacheUpdate(ctx);
  BuildLayer6AttentionQueryProjection(ctx);
  BuildLayer6AttentionSdpa(ctx);
  BuildLayer6AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 3535, 3536);
  g->Reduce(ynn_reduce_sum, 3536, 6460, {2}, true);
  g->ShapeProduct(3536, 6459, {2});
  g->Binary(ynn_binary_divide, 6460, 6459, 3537);
  g->Binary(ynn_binary_add, 3537, 6539, 3538);
  g->Unary(ynn_unary_rsqrt, 3538, 3539);
  g->Binary(ynn_binary_multiply, 3535, 3539, 3541);
  g->Binary(ynn_binary_multiply, 3541, 7055, 3542);
  g->Binary(ynn_binary_add, 3542, 3462, 3543);
}

// Scope: "Layer6 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3543, 3544);
  g->Reduce(ynn_reduce_sum, 3544, 6464, {2}, true);
  g->ShapeProduct(3544, 6463, {2});
  g->Binary(ynn_binary_divide, 6464, 6463, 3545);
  g->Binary(ynn_binary_add, 3545, 6539, 3546);
  g->Unary(ynn_unary_rsqrt, 3546, 3547);
  g->Binary(ynn_binary_multiply, 3543, 3547, 3548);
  g->Binary(ynn_binary_multiply, 3548, 7058, 3549);
  g->Quantize(3549, 3550, 0.02705955132842064, 0);
  g->Transpose(7052, 5421, {1,0});
  g->Binary(ynn_binary_multiply, 5418, 5420, 5416);
  g->Dot(3550, 5421, YNN_INVALID_VALUE_ID, 5415, 1);
  g->DequantizeTensor(5415, YNN_INVALID_VALUE_ID, 5416, 5417);
  g->QuantizeTensor(5417, 6504, 5419, 3552);
  g->Dequantize(3552, 3553, 0.02632874995470047, 0);
  g->Transpose(7051, 5426, {1,0});
  g->Binary(ynn_binary_multiply, 5418, 5425, 5423);
  g->Dot(3550, 5426, YNN_INVALID_VALUE_ID, 5422, 1);
  g->DequantizeTensor(5422, YNN_INVALID_VALUE_ID, 5423, 5424);
  g->QuantizeTensor(5424, 6504, 5419, 3554);
  g->Dequantize(3554, 3555, 0.02632874995470047, 0);
  g->Polynomial(3555, 6467, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6467, 6468);
  g->Binary(ynn_binary_add, 6468, 5500, 6465);
  g->Binary(ynn_binary_multiply, 3555, 5498, 6466);
  g->Binary(ynn_binary_multiply, 6466, 6465, 3556);
  g->Binary(ynn_binary_multiply, 3553, 3556, 3557);
  g->Quantize(3557, 3558, 0.039862215518951416, 0);
  g->Transpose(7050, 5432, {1,0});
  g->Binary(ynn_binary_multiply, 5152, 5431, 5428);
  g->Dot(3558, 5432, YNN_INVALID_VALUE_ID, 5427, 1);
  g->DequantizeTensor(5427, YNN_INVALID_VALUE_ID, 5428, 5429);
  g->QuantizeTensor(5429, 6504, 5430, 3559);
  g->Dequantize(3559, 3560, 0.019578030332922935, 0);
  g->Unary(ynn_unary_square, 3560, 3562);
  g->Reduce(ynn_reduce_sum, 3562, 6470, {2}, true);
  g->ShapeProduct(3562, 6469, {2});
  g->Binary(ynn_binary_divide, 6470, 6469, 3563);
  g->Binary(ynn_binary_add, 3563, 6539, 3564);
  g->Unary(ynn_unary_rsqrt, 3564, 3565);
  g->Binary(ynn_binary_multiply, 3560, 3565, 3566);
  g->Binary(ynn_binary_multiply, 3566, 7056, 3567);
  g->Binary(ynn_binary_add, 3567, 3543, 3568);
}

// Scope: "Layer6 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(427, 3569, {0,0,6,0}, {-1,-1,1,-1});
  g->Reshape(3569, 3570, {1,1,256});
  g->Unary(ynn_unary_square, 3570, 3571);
  g->Reduce(ynn_reduce_sum, 3571, 6472, {2}, true);
  g->ShapeProduct(3571, 6471, {2});
  g->Binary(ynn_binary_divide, 6472, 6471, 3573);
  g->Binary(ynn_binary_add, 3573, 6539, 3574);
  g->Unary(ynn_unary_rsqrt, 3574, 3575);
  g->Binary(ynn_binary_multiply, 3570, 3575, 3576);
  g->Binary(ynn_binary_multiply, 3576, 7118, 3577);
  g->Binary(ynn_binary_multiply, 7150, 6542, 3578);
  g->Binary(ynn_binary_add, 3577, 3578, 3579);
  g->Binary(ynn_binary_multiply, 3579, 6536, 3580);
  g->Quantize(3568, 3581, 0.34014976024627686, 0);
  g->Transpose(7053, 5439, {1,0});
  g->Binary(ynn_binary_multiply, 5436, 5438, 5434);
  g->Dot(3581, 5439, YNN_INVALID_VALUE_ID, 5433, 1);
  g->DequantizeTensor(5433, YNN_INVALID_VALUE_ID, 5434, 5435);
  g->QuantizeTensor(5435, 6504, 5437, 3582);
  g->Dequantize(3582, 3584, 0.04773623123764992, 0);
  g->Polynomial(3584, 6475, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6475, 6476);
  g->Binary(ynn_binary_add, 6476, 5500, 6473);
  g->Binary(ynn_binary_multiply, 3584, 5498, 6474);
  g->Binary(ynn_binary_multiply, 6474, 6473, 3585);
  g->Binary(ynn_binary_multiply, 3585, 3580, 3586);
  g->Quantize(3586, 3587, 0.12450788170099258, 0);
  g->Transpose(7054, 5445, {1,0});
  g->Binary(ynn_binary_multiply, 4040, 5444, 5441);
  g->Dot(3587, 5445, YNN_INVALID_VALUE_ID, 5440, 1);
  g->DequantizeTensor(5440, YNN_INVALID_VALUE_ID, 5441, 5442);
  g->QuantizeTensor(5442, 6504, 5443, 3588);
  g->Dequantize(3588, 3589, 0.07488936185836792, 0);
  g->Unary(ynn_unary_square, 3589, 3590);
  g->Reduce(ynn_reduce_sum, 3590, 6478, {2}, true);
  g->ShapeProduct(3590, 6477, {2});
  g->Binary(ynn_binary_divide, 6478, 6477, 3591);
  g->Binary(ynn_binary_add, 3591, 6539, 3592);
  g->Unary(ynn_unary_rsqrt, 3592, 3593);
  g->Binary(ynn_binary_multiply, 3589, 3593, 3596);
  g->Binary(ynn_binary_multiply, 3596, 7057, 3597);
  g->Binary(ynn_binary_add, 3568, 3597, 3598);
  g->Binary(ynn_binary_multiply, 3598, 7049, 3599);
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
  g->Quantize(3605, 3607, 0.29519250988960266, 0);
  g->Transpose(7077, 5452, {1,0});
  g->Binary(ynn_binary_multiply, 5449, 5451, 5447);
  g->Dot(3607, 5452, YNN_INVALID_VALUE_ID, 5446, 1);
  g->DequantizeTensor(5446, YNN_INVALID_VALUE_ID, 5447, 5448);
  g->QuantizeTensor(5448, 6504, 5450, 3608);
  g->Dequantize(3608, 3609, 0.3681102395057678, 0);
  g->Reshape(3609, 3610, {1,1,1,256});
  g->Reshape(3610, 3611, {1,1,1,256});
  g->Unary(ynn_unary_square, 3611, 3612);
  g->Reduce(ynn_reduce_sum, 3612, 6482, {3}, true);
  g->ShapeProduct(3612, 6481, {3});
  g->Binary(ynn_binary_divide, 6482, 6481, 3613);
  g->Binary(ynn_binary_add, 3613, 6539, 3614);
  g->Unary(ynn_unary_rsqrt, 3614, 3615);
  g->Binary(ynn_binary_multiply, 3611, 3615, 3616);
  g->Binary(ynn_binary_multiply, 3616, 7076, 3618);
  g->Slice(3618, 3619, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3618, 3620, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3620, 3621);
  g->Concat({3621,3619}, 3622, 3);
  g->Binary(ynn_binary_multiply, 3618, 3067, 3623);
  g->Binary(ynn_binary_multiply, 3622, 3172, 3624);
  g->Binary(ynn_binary_add, 3623, 3624, 3625);
  g->Transpose(7081, 5457, {1,0});
  g->Binary(ynn_binary_multiply, 5449, 5456, 5454);
  g->Dot(3607, 5457, YNN_INVALID_VALUE_ID, 5453, 1);
  g->DequantizeTensor(5453, YNN_INVALID_VALUE_ID, 5454, 5455);
  g->QuantizeTensor(5455, 6504, 5450, 3626);
  g->Dequantize(3626, 3628, 0.3681102395057678, 0);
  g->Reshape(3628, 3629, {1,1,1,256});
  g->Reshape(3629, 3630, {1,1,1,256});
  g->Unary(ynn_unary_square, 3630, 3631);
  g->Reduce(ynn_reduce_sum, 3631, 6486, {3}, true);
  g->ShapeProduct(3631, 6485, {3});
  g->Binary(ynn_binary_divide, 6486, 6485, 3632);
  g->Binary(ynn_binary_add, 3632, 6539, 3633);
  g->Unary(ynn_unary_rsqrt, 3633, 3634);
  g->Binary(ynn_binary_multiply, 3630, 3634, 3635);
}

// Scope: "Layer7 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(3625, 3636, 0.005869260523468256, 0);
  g->Append(6517, 3636, 7167, 2, s2, slinky::expr(int64_t{1}));
  g->View(7167, 7197, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(3635, 3638, 0.047244105488061905, 0);
  g->Append(6532, 3638, 7182, 2, s2, slinky::expr(int64_t{1}));
  g->View(7182, 7212, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer7 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(7080, 5463, {1,0});
  g->Binary(ynn_binary_multiply, 5449, 5462, 5459);
  g->Dot(3607, 5463, YNN_INVALID_VALUE_ID, 5458, 1);
  g->DequantizeTensor(5458, YNN_INVALID_VALUE_ID, 5459, 5460);
  g->QuantizeTensor(5460, 6504, 5461, 3639);
  g->Dequantize(3639, 3640, 0.31496062874794006, 0);
  g->SplitDim(3640, 3641, 2, {8,256});
  g->FuseDims(3641, 3643, 1, 2);
  g->SplitDim(3643, 3642, 1, {8,1});
  g->Unary(ynn_unary_square, 3642, 3644);
  g->Reduce(ynn_reduce_sum, 3644, 6488, {3}, true);
  g->ShapeProduct(3644, 6487, {3});
  g->Binary(ynn_binary_divide, 6488, 6487, 3646);
  g->Binary(ynn_binary_add, 3646, 6539, 3647);
  g->Unary(ynn_unary_rsqrt, 3647, 3648);
  g->Binary(ynn_binary_multiply, 3642, 3648, 3649);
  g->Binary(ynn_binary_multiply, 3649, 7079, 3650);
  g->Slice(3650, 3651, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3650, 3652, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3652, 3653);
  g->Concat({3653,3651}, 3654, 3);
  g->Binary(ynn_binary_multiply, 3650, 3067, 3655);
  g->Binary(ynn_binary_multiply, 3654, 3172, 3657);
  g->Binary(ynn_binary_add, 3655, 3657, 3658);
}

// Scope: "Layer7 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7197, 3659, 0.005869260523468256, 0);
  g->Dequantize(7212, 3660, 0.047244105488061905, 0);
  g->Matmul(3658, 3659, 3661, false, true);
  g->Mask(3661, 6577, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6577, 6492, {-1}, true);
  g->Binary(ynn_binary_subtract, 6577, 6492, 6489);
  g->Unary(ynn_unary_exp, 6489, 6490);
  g->Reduce(ynn_reduce_sum, 6490, 6493, {-1}, true);
  g->Binary(ynn_binary_divide, 5500, 6493, 6491);
  g->Binary(ynn_binary_multiply, 6490, 6491, 3662);
  g->Matmul(3662, 3660, 3663, false, false);
}

// Scope: "Layer7 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(3663, 3665, 1, 2);
  g->SplitDim(3665, 3664, 1, {1,8});
  g->FuseDims(3664, 3666, 2, 2);
  g->Quantize(3666, 3668, 0.028912410140037537, 0);
  g->Transpose(7078, 5470, {1,0});
  g->Binary(ynn_binary_multiply, 5467, 5469, 5465);
  g->Dot(3668, 5470, YNN_INVALID_VALUE_ID, 5464, 1);
  g->DequantizeTensor(5464, YNN_INVALID_VALUE_ID, 5465, 5466);
  g->QuantizeTensor(5466, 6504, 5468, 3669);
  g->Dequantize(3669, 3670, 0.025238478556275368, 0);
}

// Scope: "Layer7 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3599, 3600);
  g->Reduce(ynn_reduce_sum, 3600, 6480, {2}, true);
  g->ShapeProduct(3600, 6479, {2});
  g->Binary(ynn_binary_divide, 6480, 6479, 3601);
  g->Binary(ynn_binary_add, 3601, 6539, 3602);
  g->Unary(ynn_unary_rsqrt, 3602, 3603);
  g->Binary(ynn_binary_multiply, 3599, 3603, 3604);
  g->Binary(ynn_binary_multiply, 3604, 7065, 3605);
  BuildLayer7AttentionKvProjection(ctx);
  BuildLayer7AttentionCacheUpdate(ctx);
  BuildLayer7AttentionQueryProjection(ctx);
  BuildLayer7AttentionSdpa(ctx);
  BuildLayer7AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 3670, 3671);
  g->Reduce(ynn_reduce_sum, 3671, 6495, {2}, true);
  g->ShapeProduct(3671, 6494, {2});
  g->Binary(ynn_binary_divide, 6495, 6494, 3672);
  g->Binary(ynn_binary_add, 3672, 6539, 3673);
  g->Unary(ynn_unary_rsqrt, 3673, 3674);
  g->Binary(ynn_binary_multiply, 3670, 3674, 3675);
  g->Binary(ynn_binary_multiply, 3675, 7072, 3676);
  g->Binary(ynn_binary_add, 3676, 3599, 3677);
}

// Scope: "Layer7 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3677, 3679);
  g->Reduce(ynn_reduce_sum, 3679, 6497, {2}, true);
  g->ShapeProduct(3679, 6496, {2});
  g->Binary(ynn_binary_divide, 6497, 6496, 3680);
  g->Binary(ynn_binary_add, 3680, 6539, 3681);
  g->Unary(ynn_unary_rsqrt, 3681, 3682);
  g->Binary(ynn_binary_multiply, 3677, 3682, 3683);
  g->Binary(ynn_binary_multiply, 3683, 7075, 3684);
  g->Quantize(3684, 3685, 0.023717211559414864, 0);
  g->Transpose(7069, 5482, {1,0});
  g->Binary(ynn_binary_multiply, 5479, 5481, 5477);
  g->Dot(3685, 5482, YNN_INVALID_VALUE_ID, 5476, 1);
  g->DequantizeTensor(5476, YNN_INVALID_VALUE_ID, 5477, 5478);
  g->QuantizeTensor(5478, 6504, 5480, 3686);
  g->Dequantize(3686, 3687, 0.021899616345763206, 0);
  g->Transpose(7068, 5487, {1,0});
  g->Binary(ynn_binary_multiply, 5479, 5486, 5484);
  g->Dot(3685, 5487, YNN_INVALID_VALUE_ID, 5483, 1);
  g->DequantizeTensor(5483, YNN_INVALID_VALUE_ID, 5484, 5485);
  g->QuantizeTensor(5485, 6504, 5480, 3689);
  g->Dequantize(3689, 3690, 0.021899616345763206, 0);
  g->Polynomial(3690, 6500, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6500, 6501);
  g->Binary(ynn_binary_add, 6501, 5500, 6498);
  g->Binary(ynn_binary_multiply, 3690, 5498, 6499);
  g->Binary(ynn_binary_multiply, 6499, 6498, 3691);
  g->Binary(ynn_binary_multiply, 3687, 3691, 3692);
  g->Quantize(3692, 3693, 0.02202264778316021, 0);
  g->Transpose(7067, 5494, {1,0});
  g->Binary(ynn_binary_multiply, 5491, 5493, 5489);
  g->Dot(3693, 5494, YNN_INVALID_VALUE_ID, 5488, 1);
  g->DequantizeTensor(5488, YNN_INVALID_VALUE_ID, 5489, 5490);
  g->QuantizeTensor(5490, 6504, 5492, 3694);
  g->Dequantize(3694, 3695, 0.01081059779971838, 0);
  g->Unary(ynn_unary_square, 3695, 3696);
  g->Reduce(ynn_reduce_sum, 3696, 6503, {2}, true);
  g->ShapeProduct(3696, 6502, {2});
  g->Binary(ynn_binary_divide, 6503, 6502, 3697);
  g->Binary(ynn_binary_add, 3697, 6539, 3698);
  g->Unary(ynn_unary_rsqrt, 3698, 3);
  g->Binary(ynn_binary_multiply, 3695, 3, 4);
  g->Binary(ynn_binary_multiply, 4, 7073, 5);
  g->Binary(ynn_binary_add, 5, 3677, 6);
}

// Scope: "Layer7 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(427, 7, {0,0,7,0}, {-1,-1,1,-1});
  g->Reshape(7, 8, {1,1,256});
  g->Unary(ynn_unary_square, 8, 9);
  g->Reduce(ynn_reduce_sum, 9, 5496, {2}, true);
  g->ShapeProduct(9, 5495, {2});
  g->Binary(ynn_binary_divide, 5496, 5495, 10);
  g->Binary(ynn_binary_add, 10, 6539, 11);
  g->Unary(ynn_unary_rsqrt, 11, 12);
  g->Binary(ynn_binary_multiply, 8, 12, 14);
  g->Binary(ynn_binary_multiply, 14, 7118, 15);
  g->Binary(ynn_binary_multiply, 7151, 6542, 16);
  g->Binary(ynn_binary_add, 15, 16, 17);
  g->Binary(ynn_binary_multiply, 17, 6536, 18);
  g->Quantize(6, 19, 0.15832224488258362, 0);
  g->Transpose(7070, 3712, {1,0});
  g->Binary(ynn_binary_multiply, 3709, 3711, 3707);
  g->Dot(19, 3712, YNN_INVALID_VALUE_ID, 3706, 1);
  g->DequantizeTensor(3706, YNN_INVALID_VALUE_ID, 3707, 3708);
  g->QuantizeTensor(3708, 6504, 3710, 20);
  g->Dequantize(20, 21, 0.055118121206760406, 0);
  g->Polynomial(21, 5501, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5501, 5502);
  g->Binary(ynn_binary_add, 5502, 5500, 5497);
  g->Binary(ynn_binary_multiply, 21, 5498, 5499);
  g->Binary(ynn_binary_multiply, 5499, 5497, 22);
  g->Binary(ynn_binary_multiply, 22, 18, 23);
  g->Quantize(23, 25, 0.22834646701812744, 0);
  g->Transpose(7071, 3719, {1,0});
  g->Binary(ynn_binary_multiply, 3716, 3718, 3714);
  g->Dot(25, 3719, YNN_INVALID_VALUE_ID, 3713, 1);
  g->DequantizeTensor(3713, YNN_INVALID_VALUE_ID, 3714, 3715);
  g->QuantizeTensor(3715, 6504, 3717, 26);
  g->Dequantize(26, 27, 0.08292699605226517, 0);
  g->Unary(ynn_unary_square, 27, 28);
  g->Reduce(ynn_reduce_sum, 28, 5504, {2}, true);
  g->ShapeProduct(28, 5503, {2});
  g->Binary(ynn_binary_divide, 5504, 5503, 29);
  g->Binary(ynn_binary_add, 29, 6539, 30);
  g->Unary(ynn_unary_rsqrt, 30, 31);
  g->Binary(ynn_binary_multiply, 27, 31, 32);
  g->Binary(ynn_binary_multiply, 32, 7074, 33);
  g->Binary(ynn_binary_add, 6, 33, 34);
  g->Binary(ynn_binary_multiply, 34, 7066, 36);
}

// Scope: "Layer7"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7(Context& ctx) {
  BuildLayer7Attention(ctx);
  BuildLayer7Mlp(ctx);
  BuildLayer7PerLayerEmbedding(ctx);
}

}  // namespace BuildGemma4DecodeSource
