// Generated YNNPACK builder; do not edit.
#include "gemma4_decode_builder.h"

namespace BuildGemma4DecodeSource {

// Scope: "Layer1 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Binary(ynn_binary_divide, 1482, 7151, 1488);
  g->Unary(ynn_unary_round, 1488, 1499);
  g->Binary(ynn_binary_max, 1499, 7155, 1508);
  g->Binary(ynn_binary_min, 1508, 7270, 1512);
  g->Binary(ynn_binary_multiply, 1512, 7151, 1524);
  g->Convert(7569, 1535);
  g->Binary(ynn_binary_multiply, 1535, 7570, 1545);
  g->Matmul(1524, 1545, 1556, false, true);
  g->Binary(ynn_binary_divide, 1556, 7327, 1567);
  g->Unary(ynn_unary_round, 1567, 1578);
  g->Binary(ynn_binary_max, 1578, 7155, 1588);
  g->Binary(ynn_binary_min, 1588, 7270, 1595);
  g->Binary(ynn_binary_multiply, 1595, 7327, 1606);
  g->Reshape(1606, 1617, {1,1,1,256});
  g->Transpose(1617, 1629, {0,2,1,3});
  g->Unary(ynn_unary_square, 1629, 1640);
  g->Reduce(ynn_reduce_sum, 1640, 6353, {3}, true);
  g->ShapeProduct(1640, 6352, {3});
  g->Binary(ynn_binary_divide, 6353, 6352, 1651);
  g->Binary(ynn_binary_add, 1651, 7303, 1662);
  g->Binary(ynn_binary_pow, 1662, 7358, 1673);
  g->Binary(ynn_binary_multiply, 1629, 1673, 1684);
  g->Convert(7568, 1695);
  g->Binary(ynn_binary_multiply, 1684, 1695, 1706);
  g->Slice(1706, 1712, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1706, 1723, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1723, 1731);
  g->Concat({1731,1712}, 1737, 3);
  g->Binary(ynn_binary_multiply, 1706, 2025, 1748);
  g->Binary(ynn_binary_multiply, 1737, 3078, 1759);
  g->Binary(ynn_binary_add, 1748, 1759, 1769);
  g->Convert(7576, 1826);
  g->Binary(ynn_binary_multiply, 1826, 7577, 1837);
  g->Matmul(1524, 1837, 1848, false, true);
  g->Binary(ynn_binary_divide, 1848, 7327, 1859);
  g->Unary(ynn_unary_round, 1859, 1870);
  g->Binary(ynn_binary_max, 1870, 7155, 1881);
  g->Binary(ynn_binary_min, 1881, 7270, 1892);
  g->Binary(ynn_binary_multiply, 1892, 7327, 1903);
  g->Reshape(1903, 1914, {1,1,1,256});
  g->Transpose(1914, 1925, {0,2,1,3});
  g->Unary(ynn_unary_square, 1925, 1932);
  g->Reduce(ynn_reduce_sum, 1932, 6392, {3}, true);
  g->ShapeProduct(1932, 6391, {3});
  g->Binary(ynn_binary_divide, 6392, 6391, 1943);
  g->Binary(ynn_binary_add, 1943, 7303, 1949);
  g->Binary(ynn_binary_pow, 1949, 7358, 1956);
  g->Binary(ynn_binary_multiply, 1925, 1956, 1967);
}

// Scope: "Layer1 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(1769, 1977, 0.005761673673987389, 0);
  g->Append(7046, 1977, 8376, 2, s2, slinky::expr(int64_t{1}));
  g->View(8376, 8406, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(8406, 2008, 0.005761673673987389, 0);
  g->Quantize(1967, 2019, 0.047244105488061905, 0);
  g->Append(7061, 2019, 8391, 2, s2, slinky::expr(int64_t{1}));
  g->View(8391, 8421, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(8421, 2047, 0.047244105488061905, 0);
}

// Scope: "Layer1 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Convert(7574, 2108);
  g->Binary(ynn_binary_multiply, 2108, 7575, 2119);
  g->Matmul(1524, 2119, 2131, false, true);
  g->Binary(ynn_binary_divide, 2131, 7234, 2141);
  g->Unary(ynn_unary_round, 2141, 2148);
  g->Binary(ynn_binary_max, 2148, 7155, 2159);
  g->Binary(ynn_binary_min, 2159, 7270, 2163);
  g->Binary(ynn_binary_multiply, 2163, 7234, 2172);
  g->SplitDim(2172, 2183, 2, {8,256});
  g->Transpose(2183, 2193, {0,2,1,3});
  g->Unary(ynn_unary_square, 2193, 2204);
  g->Reduce(ynn_reduce_sum, 2204, 6432, {3}, true);
  g->ShapeProduct(2204, 6431, {3});
  g->Binary(ynn_binary_divide, 6432, 6431, 2215);
  g->Binary(ynn_binary_add, 2215, 7303, 2227);
  g->Binary(ynn_binary_pow, 2227, 7358, 2238);
  g->Binary(ynn_binary_multiply, 2193, 2238, 2244);
  g->Convert(7573, 2255);
  g->Binary(ynn_binary_multiply, 2244, 2255, 2266);
  g->Slice(2266, 2277, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2266, 2288, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2288, 2299);
  g->Concat({2299,2277}, 2310, 3);
  g->Binary(ynn_binary_multiply, 2266, 2025, 2321);
  g->Binary(ynn_binary_multiply, 2310, 3078, 2333);
  g->Binary(ynn_binary_add, 2321, 2333, 2344);
}

// Scope: "Layer1 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(2344, 2008, 2355, false, true);
  g->Mask(2355, 7492, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 7492, 6459, {-1}, true);
  g->Binary(ynn_binary_subtract, 7492, 6459, 6456);
  g->Unary(ynn_unary_exp, 6456, 6457);
  g->Reduce(ynn_reduce_sum, 6457, 6460, {-1}, true);
  g->Binary(ynn_binary_divide, 6113, 6460, 6458);
  g->Binary(ynn_binary_multiply, 6457, 6458, 2375);
  g->Matmul(2375, 2047, 2386, false, false);
}

// Scope: "Layer1 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(2386, 2397, {0,2,1,3});
  g->FuseDims(2397, 2408, 2, 2);
  g->Binary(ynn_binary_divide, 2408, 7434, 2414);
  g->Unary(ynn_unary_round, 2414, 2425);
  g->Binary(ynn_binary_max, 2425, 7155, 2437);
  g->Binary(ynn_binary_min, 2437, 7270, 2448);
  g->Binary(ynn_binary_multiply, 2448, 7434, 2459);
  g->Convert(7571, 2470);
  g->Binary(ynn_binary_multiply, 2470, 7572, 2481);
  g->Matmul(2459, 2481, 2492, false, true);
  g->Binary(ynn_binary_divide, 2492, 7158, 2503);
  g->Unary(ynn_unary_round, 2503, 2514);
  g->Binary(ynn_binary_max, 2514, 7155, 2525);
  g->Binary(ynn_binary_min, 2525, 7270, 2535);
  g->Binary(ynn_binary_multiply, 2535, 7158, 2547);
}

// Scope: "Layer1 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1404, 1415);
  g->Reduce(ynn_reduce_sum, 1415, 6322, {2}, true);
  g->ShapeProduct(1415, 6321, {2});
  g->Binary(ynn_binary_divide, 6322, 6321, 1427);
  g->Binary(ynn_binary_add, 1427, 7303, 1438);
  g->Binary(ynn_binary_pow, 1438, 7358, 1449);
  g->Binary(ynn_binary_multiply, 1404, 1449, 1460);
  g->Convert(7552, 1471);
  g->Binary(ynn_binary_multiply, 1460, 1471, 1482);
  BuildLayer1AttentionKvProjection(ctx);
  BuildLayer1AttentionCacheUpdate(ctx);
  BuildLayer1AttentionQueryProjection(ctx);
  BuildLayer1AttentionSdpa(ctx);
  BuildLayer1AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2547, 2558);
  g->Reduce(ynn_reduce_sum, 2558, 6491, {2}, true);
  g->ShapeProduct(2558, 6490, {2});
  g->Binary(ynn_binary_divide, 6491, 6490, 2569);
  g->Binary(ynn_binary_add, 2569, 7303, 2580);
  g->Binary(ynn_binary_pow, 2580, 7358, 2586);
  g->Binary(ynn_binary_multiply, 2547, 2586, 2597);
  g->Convert(7564, 2608);
  g->Binary(ynn_binary_multiply, 2597, 2608, 2619);
  g->Binary(ynn_binary_add, 1404, 2619, 2630);
}

// Scope: "Layer1 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2630, 2641);
  g->Reduce(ynn_reduce_sum, 2641, 6503, {2}, true);
  g->ShapeProduct(2641, 6502, {2});
  g->Binary(ynn_binary_divide, 6503, 6502, 2653);
  g->Binary(ynn_binary_add, 2653, 7303, 2664);
  g->Binary(ynn_binary_pow, 2664, 7358, 2675);
  g->Binary(ynn_binary_multiply, 2630, 2675, 2686);
  g->Convert(7567, 2697);
  g->Binary(ynn_binary_multiply, 2686, 2697, 2708);
  g->Binary(ynn_binary_divide, 2708, 7337, 2718);
  g->Unary(ynn_unary_round, 2718, 2729);
  g->Binary(ynn_binary_max, 2729, 7155, 2740);
  g->Binary(ynn_binary_min, 2740, 7270, 2751);
  g->Binary(ynn_binary_multiply, 2751, 7337, 2759);
  g->Convert(7558, 2769);
  g->Binary(ynn_binary_multiply, 2769, 7559, 2780);
  g->Matmul(2759, 2780, 2791, false, true);
  g->Binary(ynn_binary_divide, 2791, 7091, 2802);
  g->Unary(ynn_unary_round, 2802, 2813);
  g->Binary(ynn_binary_max, 2813, 7155, 2824);
  g->Binary(ynn_binary_min, 2824, 7270, 2835);
  g->Binary(ynn_binary_multiply, 2835, 7091, 2846);
  g->Convert(7556, 2907);
  g->Binary(ynn_binary_multiply, 2907, 7557, 2918);
  g->Matmul(2759, 2918, 2926, false, true);
  g->Binary(ynn_binary_divide, 2926, 7091, 2935);
  g->Unary(ynn_unary_round, 2935, 2946);
  g->Binary(ynn_binary_max, 2946, 7155, 2957);
  g->Binary(ynn_binary_min, 2957, 7270, 2969);
  g->Binary(ynn_binary_multiply, 2969, 7091, 2980);
  g->Polynomial(2980, 6556, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6556, 6557);
  g->Binary(ynn_binary_add, 6557, 6113, 6554);
  g->Binary(ynn_binary_multiply, 2980, 6111, 6555);
  g->Binary(ynn_binary_multiply, 6555, 6554, 2991);
  g->Binary(ynn_binary_multiply, 2846, 2991, 3002);
  g->Binary(ynn_binary_divide, 3002, 7078, 3013);
  g->Unary(ynn_unary_round, 3013, 3024);
  g->Binary(ynn_binary_max, 3024, 7155, 3035);
  g->Binary(ynn_binary_min, 3035, 7270, 3046);
  g->Binary(ynn_binary_multiply, 3046, 7078, 3056);
  g->Convert(7554, 3067);
  g->Binary(ynn_binary_multiply, 3067, 7555, 3080);
  g->Matmul(3056, 3080, 3091, false, true);
  g->Binary(ynn_binary_divide, 3091, 7097, 3100);
  g->Unary(ynn_unary_round, 3100, 3108);
  g->Binary(ynn_binary_max, 3108, 7155, 3119);
  g->Binary(ynn_binary_min, 3119, 7270, 3130);
  g->Binary(ynn_binary_multiply, 3130, 7097, 3141);
  g->Unary(ynn_unary_square, 3141, 3152);
  g->Reduce(ynn_reduce_sum, 3152, 6584, {2}, true);
  g->ShapeProduct(3152, 6583, {2});
  g->Binary(ynn_binary_divide, 6584, 6583, 3163);
  g->Binary(ynn_binary_add, 3163, 7303, 3174);
  g->Binary(ynn_binary_pow, 3174, 7358, 3186);
  g->Binary(ynn_binary_multiply, 3141, 3186, 3197);
  g->Convert(7565, 3208);
  g->Binary(ynn_binary_multiply, 3197, 3208, 3219);
  g->Binary(ynn_binary_add, 2630, 3219, 3229);
}

// Scope: "Layer1 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1022, 3240, {0,0,1,0}, {-1,-1,1,-1});
  g->Reshape(3240, 3251, {1,1,256});
  g->Binary(ynn_binary_add, 3251, 8340, 3262);
  g->Binary(ynn_binary_multiply, 3262, 7085, 3272);
  g->Binary(ynn_binary_divide, 3229, 7253, 3279);
  g->Unary(ynn_unary_round, 3279, 3291);
  g->Binary(ynn_binary_max, 3291, 7155, 3302);
  g->Binary(ynn_binary_min, 3302, 7270, 3313);
  g->Binary(ynn_binary_multiply, 3313, 7253, 3324);
  g->Convert(7560, 3335);
  g->Binary(ynn_binary_multiply, 3335, 7561, 3346);
  g->Matmul(3324, 3346, 3357, false, true);
  g->Binary(ynn_binary_divide, 3357, 7429, 3368);
  g->Unary(ynn_unary_round, 3368, 3379);
  g->Binary(ynn_binary_max, 3379, 7155, 3390);
  g->Binary(ynn_binary_min, 3390, 7270, 3401);
  g->Binary(ynn_binary_multiply, 3401, 7429, 3412);
  g->Polynomial(3412, 6625, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6625, 6626);
  g->Binary(ynn_binary_add, 6626, 6113, 6623);
  g->Binary(ynn_binary_multiply, 3412, 6111, 6624);
  g->Binary(ynn_binary_multiply, 6624, 6623, 3423);
  g->Binary(ynn_binary_multiply, 3423, 3272, 3434);
  g->Binary(ynn_binary_divide, 3434, 7301, 3445);
  g->Unary(ynn_unary_round, 3445, 3451);
  g->Binary(ynn_binary_max, 3451, 7155, 3462);
  g->Binary(ynn_binary_min, 3462, 7270, 3473);
  g->Binary(ynn_binary_multiply, 3473, 7301, 3484);
  g->Convert(7562, 3495);
  g->Binary(ynn_binary_multiply, 3495, 7563, 3507);
  g->Matmul(3484, 3507, 3518, false, true);
  g->Binary(ynn_binary_divide, 3518, 7274, 3529);
  g->Unary(ynn_unary_round, 3529, 3540);
  g->Binary(ynn_binary_max, 3540, 7155, 3551);
  g->Binary(ynn_binary_min, 3551, 7270, 3562);
  g->Binary(ynn_binary_multiply, 3562, 7274, 3572);
  g->Unary(ynn_unary_square, 3572, 3583);
  g->Reduce(ynn_reduce_sum, 3583, 6655, {2}, true);
  g->ShapeProduct(3583, 6654, {2});
  g->Binary(ynn_binary_divide, 6655, 6654, 3594);
  g->Binary(ynn_binary_add, 3594, 7303, 3605);
  g->Binary(ynn_binary_pow, 3605, 7358, 3617);
  g->Binary(ynn_binary_multiply, 3572, 3617, 3623);
  g->Convert(7566, 3634);
  g->Binary(ynn_binary_multiply, 3623, 3634, 3645);
  g->Binary(ynn_binary_add, 3229, 3645, 3656);
  g->Convert(7553, 3667);
  g->Binary(ynn_binary_multiply, 3656, 3667, 3678);
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
  g->Binary(ynn_binary_divide, 3755, 7426, 3766);
  g->Unary(ynn_unary_round, 3766, 3777);
  g->Binary(ynn_binary_max, 3777, 7155, 3788);
  g->Binary(ynn_binary_min, 3788, 7270, 3794);
  g->Binary(ynn_binary_multiply, 3794, 7426, 3805);
  g->Convert(7830, 3816);
  g->Binary(ynn_binary_multiply, 3816, 7831, 3828);
  g->Matmul(3805, 3828, 3839, false, true);
  g->Binary(ynn_binary_divide, 3839, 7446, 3850);
  g->Unary(ynn_unary_round, 3850, 3861);
  g->Binary(ynn_binary_max, 3861, 7155, 3872);
  g->Binary(ynn_binary_min, 3872, 7270, 3883);
  g->Binary(ynn_binary_multiply, 3883, 7446, 3894);
  g->Reshape(3894, 3905, {1,1,1,256});
  g->Transpose(3905, 3915, {0,2,1,3});
  g->Unary(ynn_unary_square, 3915, 3926);
  g->Reduce(ynn_reduce_sum, 3926, 6709, {3}, true);
  g->ShapeProduct(3926, 6708, {3});
  g->Binary(ynn_binary_divide, 6709, 6708, 3938);
  g->Binary(ynn_binary_add, 3938, 7303, 3949);
  g->Binary(ynn_binary_pow, 3949, 7358, 3960);
  g->Binary(ynn_binary_multiply, 3915, 3960, 3966);
  g->Convert(7829, 3977);
  g->Binary(ynn_binary_multiply, 3966, 3977, 3988);
  g->Slice(3988, 3999, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3988, 4010, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 4010, 4021);
  g->Concat({4021,3999}, 4032, 3);
  g->Binary(ynn_binary_multiply, 3988, 2025, 4044);
  g->Binary(ynn_binary_multiply, 4032, 3078, 4055);
  g->Binary(ynn_binary_add, 4044, 4055, 4066);
  g->Convert(7837, 4126);
  g->Binary(ynn_binary_multiply, 4126, 7838, 4132);
  g->Matmul(3805, 4132, 4145, false, true);
  g->Binary(ynn_binary_divide, 4145, 7446, 4156);
  g->Unary(ynn_unary_round, 4156, 4167);
  g->Binary(ynn_binary_max, 4167, 7155, 4178);
  g->Binary(ynn_binary_min, 4178, 7270, 4189);
  g->Binary(ynn_binary_multiply, 4189, 7446, 4200);
  g->Reshape(4200, 4211, {1,1,1,256});
  g->Transpose(4211, 4222, {0,2,1,3});
  g->Unary(ynn_unary_square, 4222, 4233);
  g->Reduce(ynn_reduce_sum, 4233, 6754, {3}, true);
  g->ShapeProduct(4233, 6753, {3});
  g->Binary(ynn_binary_divide, 6754, 6753, 4244);
  g->Binary(ynn_binary_add, 4244, 7303, 4255);
  g->Binary(ynn_binary_pow, 4255, 7358, 4266);
  g->Binary(ynn_binary_multiply, 4222, 4266, 4277);
}

// Scope: "Layer2 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(4066, 4288, 0.005684707313776016, 0);
  g->Append(7052, 4288, 8382, 2, s2, slinky::expr(int64_t{1}));
  g->View(8382, 8412, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(8412, 4314, 0.005684707313776016, 0);
  g->Quantize(4277, 4325, 0.047244105488061905, 0);
  g->Append(7067, 4325, 8397, 2, s2, slinky::expr(int64_t{1}));
  g->View(8397, 8427, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(8427, 4357, 0.047244105488061905, 0);
}

// Scope: "Layer2 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Convert(7835, 4418);
  g->Binary(ynn_binary_multiply, 4418, 7836, 4428);
  g->Matmul(3805, 4428, 4439, false, true);
  g->Binary(ynn_binary_divide, 4439, 7334, 4450);
  g->Unary(ynn_unary_round, 4450, 4462);
  g->Binary(ynn_binary_max, 4462, 7155, 4469);
  g->Binary(ynn_binary_min, 4469, 7270, 4479);
  g->Binary(ynn_binary_multiply, 4479, 7334, 4490);
  g->SplitDim(4490, 4501, 2, {8,256});
  g->Transpose(4501, 4512, {0,2,1,3});
  g->Unary(ynn_unary_square, 4512, 4523);
  g->Reduce(ynn_reduce_sum, 4523, 6800, {3}, true);
  g->ShapeProduct(4523, 6799, {3});
  g->Binary(ynn_binary_divide, 6800, 6799, 4534);
  g->Binary(ynn_binary_add, 4534, 7303, 4545);
  g->Binary(ynn_binary_pow, 4545, 7358, 4556);
  g->Binary(ynn_binary_multiply, 4512, 4556, 4568);
  g->Convert(7834, 4579);
  g->Binary(ynn_binary_multiply, 4568, 4579, 4590);
  g->Slice(4590, 4600, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(4590, 4611, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 4611, 4622);
  g->Concat({4622,4600}, 4633, 3);
  g->Binary(ynn_binary_multiply, 4590, 2025, 4641);
  g->Binary(ynn_binary_multiply, 4633, 3078, 4650);
  g->Binary(ynn_binary_add, 4641, 4650, 4661);
}

// Scope: "Layer2 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(4661, 4314, 4673, false, true);
  g->Mask(4673, 7503, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 7503, 6825, {-1}, true);
  g->Binary(ynn_binary_subtract, 7503, 6825, 6822);
  g->Unary(ynn_unary_exp, 6822, 6823);
  g->Reduce(ynn_reduce_sum, 6823, 6826, {-1}, true);
  g->Binary(ynn_binary_divide, 6113, 6826, 6824);
  g->Binary(ynn_binary_multiply, 6823, 6824, 4694);
  g->Matmul(4694, 4357, 4705, false, false);
}

// Scope: "Layer2 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(4705, 4716, {0,2,1,3});
  g->FuseDims(4716, 4727, 2, 2);
  g->Binary(ynn_binary_divide, 4727, 7231, 4738);
  g->Unary(ynn_unary_round, 4738, 4749);
  g->Binary(ynn_binary_max, 4749, 7155, 4760);
  g->Binary(ynn_binary_min, 4760, 7270, 4770);
  g->Binary(ynn_binary_multiply, 4770, 7231, 4782);
  g->Convert(7832, 4793);
  g->Binary(ynn_binary_multiply, 4793, 7833, 4804);
  g->Matmul(4782, 4804, 4813, false, true);
  g->Binary(ynn_binary_divide, 4813, 7205, 4821);
  g->Unary(ynn_unary_round, 4821, 4832);
  g->Binary(ynn_binary_max, 4832, 7155, 4843);
  g->Binary(ynn_binary_min, 4843, 7270, 4854);
  g->Binary(ynn_binary_multiply, 4854, 7205, 4865);
}

// Scope: "Layer2 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3678, 3689);
  g->Reduce(ynn_reduce_sum, 3689, 6671, {2}, true);
  g->ShapeProduct(3689, 6670, {2});
  g->Binary(ynn_binary_divide, 6671, 6670, 3700);
  g->Binary(ynn_binary_add, 3700, 7303, 3711);
  g->Binary(ynn_binary_pow, 3711, 7358, 3723);
  g->Binary(ynn_binary_multiply, 3678, 3723, 3734);
  g->Convert(7813, 3744);
  g->Binary(ynn_binary_multiply, 3734, 3744, 3755);
  BuildLayer2AttentionKvProjection(ctx);
  BuildLayer2AttentionCacheUpdate(ctx);
  BuildLayer2AttentionQueryProjection(ctx);
  BuildLayer2AttentionSdpa(ctx);
  BuildLayer2AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 4865, 4876);
  g->Reduce(ynn_reduce_sum, 4876, 6859, {2}, true);
  g->ShapeProduct(4876, 6858, {2});
  g->Binary(ynn_binary_divide, 6859, 6858, 4887);
  g->Binary(ynn_binary_add, 4887, 7303, 4898);
  g->Binary(ynn_binary_pow, 4898, 7358, 4909);
  g->Binary(ynn_binary_multiply, 4865, 4909, 4920);
  g->Convert(7825, 4931);
  g->Binary(ynn_binary_multiply, 4920, 4931, 4941);
  g->Binary(ynn_binary_add, 3678, 4941, 4952);
}

// Scope: "Layer2 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 4952, 4963);
  g->Reduce(ynn_reduce_sum, 4963, 6874, {2}, true);
  g->ShapeProduct(4963, 6873, {2});
  g->Binary(ynn_binary_divide, 6874, 6873, 4974);
  g->Binary(ynn_binary_add, 4974, 7303, 4984);
  g->Binary(ynn_binary_pow, 4984, 7358, 4991);
  g->Binary(ynn_binary_multiply, 4952, 4991, 5002);
  g->Convert(7828, 5013);
  g->Binary(ynn_binary_multiply, 5002, 5013, 5024);
  g->Binary(ynn_binary_divide, 5024, 7415, 5035);
  g->Unary(ynn_unary_round, 5035, 5046);
  g->Binary(ynn_binary_max, 5046, 7155, 5057);
  g->Binary(ynn_binary_min, 5057, 7270, 5068);
  g->Binary(ynn_binary_multiply, 5068, 7415, 5079);
  g->Convert(7819, 5090);
  g->Binary(ynn_binary_multiply, 5090, 7820, 5101);
  g->Matmul(5079, 5101, 5111, false, true);
  g->Binary(ynn_binary_divide, 5111, 7226, 5122);
  g->Unary(ynn_unary_round, 5122, 5133);
  g->Binary(ynn_binary_max, 5133, 7155, 5144);
  g->Binary(ynn_binary_min, 5144, 7270, 5155);
  g->Binary(ynn_binary_multiply, 5155, 7226, 5161);
  g->Convert(7817, 5223);
  g->Binary(ynn_binary_multiply, 5223, 7818, 5234);
  g->Matmul(5079, 5234, 5245, false, true);
  g->Binary(ynn_binary_divide, 5245, 7226, 5256);
  g->Unary(ynn_unary_round, 5256, 5267);
  g->Binary(ynn_binary_max, 5267, 7155, 5277);
  g->Binary(ynn_binary_min, 5277, 7270, 5288);
  g->Binary(ynn_binary_multiply, 5288, 7226, 5299);
  g->Polynomial(5299, 6927, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6927, 6928);
  g->Binary(ynn_binary_add, 6928, 6113, 6925);
  g->Binary(ynn_binary_multiply, 5299, 6111, 6926);
  g->Binary(ynn_binary_multiply, 6926, 6925, 5310);
  g->Binary(ynn_binary_multiply, 5161, 5310, 5321);
  g->Binary(ynn_binary_divide, 5321, 7346, 5327);
  g->Unary(ynn_unary_round, 5327, 5338);
  g->Binary(ynn_binary_max, 5338, 7155, 5349);
  g->Binary(ynn_binary_min, 5349, 7270, 5360);
  g->Binary(ynn_binary_multiply, 5360, 7346, 5371);
  g->Convert(7815, 5382);
  g->Binary(ynn_binary_multiply, 5382, 7816, 5393);
  g->Matmul(5371, 5393, 5404, false, true);
  g->Binary(ynn_binary_divide, 5404, 7376, 5416);
  g->Unary(ynn_unary_round, 5416, 5427);
  g->Binary(ynn_binary_max, 5427, 7155, 5438);
  g->Binary(ynn_binary_min, 5438, 7270, 5448);
  g->Binary(ynn_binary_multiply, 5448, 7376, 5459);
  g->Unary(ynn_unary_square, 5459, 5470);
  g->Reduce(ynn_reduce_sum, 5470, 6955, {2}, true);
  g->ShapeProduct(5470, 6954, {2});
  g->Binary(ynn_binary_divide, 6955, 6954, 5481);
  g->Binary(ynn_binary_add, 5481, 7303, 5492);
  g->Binary(ynn_binary_pow, 5492, 7358, 5498);
  g->Binary(ynn_binary_multiply, 5459, 5498, 5509);
  g->Convert(7826, 5521);
  g->Binary(ynn_binary_multiply, 5509, 5521, 5532);
  g->Binary(ynn_binary_add, 4952, 5532, 5543);
}

// Scope: "Layer2 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1022, 5554, {0,0,2,0}, {-1,-1,1,-1});
  g->Reshape(5554, 5565, {1,1,256});
  g->Binary(ynn_binary_add, 5565, 8351, 5576);
  g->Binary(ynn_binary_multiply, 5576, 7085, 5587);
  g->Binary(ynn_binary_divide, 5543, 7316, 5598);
  g->Unary(ynn_unary_round, 5598, 5609);
  g->Binary(ynn_binary_max, 5609, 7155, 5619);
  g->Binary(ynn_binary_min, 5619, 7270, 5631);
  g->Binary(ynn_binary_multiply, 5631, 7316, 5642);
  g->Convert(7821, 5653);
  g->Binary(ynn_binary_multiply, 5653, 7822, 5664);
  g->Matmul(5642, 5664, 5670, false, true);
  g->Binary(ynn_binary_divide, 5670, 7225, 5681);
  g->Unary(ynn_unary_round, 5681, 5692);
  g->Binary(ynn_binary_max, 5692, 7155, 5703);
  g->Binary(ynn_binary_min, 5703, 7270, 5714);
  g->Binary(ynn_binary_multiply, 5714, 7225, 5725);
  g->Polynomial(5725, 6993, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6993, 6994);
  g->Binary(ynn_binary_add, 6994, 6113, 6991);
  g->Binary(ynn_binary_multiply, 5725, 6111, 6992);
  g->Binary(ynn_binary_multiply, 6992, 6991, 5737);
  g->Binary(ynn_binary_multiply, 5737, 5587, 5748);
  g->Binary(ynn_binary_divide, 5748, 7449, 5759);
  g->Unary(ynn_unary_round, 5759, 5764);
  g->Binary(ynn_binary_max, 5764, 7155, 5765);
  g->Binary(ynn_binary_min, 5765, 7270, 5766);
  g->Binary(ynn_binary_multiply, 5766, 7449, 5767);
  g->Convert(7823, 5768);
  g->Binary(ynn_binary_multiply, 5768, 7824, 5769);
  g->Matmul(5767, 5769, 5770, false, true);
  g->Binary(ynn_binary_divide, 5770, 7227, 5772);
  g->Unary(ynn_unary_round, 5772, 5773);
  g->Binary(ynn_binary_max, 5773, 7155, 5774);
  g->Binary(ynn_binary_min, 5774, 7270, 5775);
  g->Binary(ynn_binary_multiply, 5775, 7227, 5776);
  g->Unary(ynn_unary_square, 5776, 5777);
  g->Reduce(ynn_reduce_sum, 5777, 7000, {2}, true);
  g->ShapeProduct(5777, 6999, {2});
  g->Binary(ynn_binary_divide, 7000, 6999, 5778);
  g->Binary(ynn_binary_add, 5778, 7303, 5779);
  g->Binary(ynn_binary_pow, 5779, 7358, 5780);
  g->Binary(ynn_binary_multiply, 5776, 5780, 5781);
  g->Convert(7827, 5783);
  g->Binary(ynn_binary_multiply, 5781, 5783, 5784);
  g->Binary(ynn_binary_add, 5543, 5784, 5785);
  g->Convert(7814, 5786);
  g->Binary(ynn_binary_multiply, 5785, 5786, 5787);
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
  g->Binary(ynn_binary_divide, 5795, 7392, 5796);
  g->Unary(ynn_unary_round, 5796, 5797);
  g->Binary(ynn_binary_max, 5797, 7155, 5798);
  g->Binary(ynn_binary_min, 5798, 7270, 5799);
  g->Binary(ynn_binary_multiply, 5799, 7392, 5800);
  g->Convert(8066, 5801);
  g->Binary(ynn_binary_multiply, 5801, 8067, 5802);
  g->Matmul(5800, 5802, 5803, false, true);
  g->Binary(ynn_binary_divide, 5803, 7077, 5805);
  g->Unary(ynn_unary_round, 5805, 5806);
  g->Binary(ynn_binary_max, 5806, 7155, 5807);
  g->Binary(ynn_binary_min, 5807, 7270, 5808);
  g->Binary(ynn_binary_multiply, 5808, 7077, 5809);
  g->Reshape(5809, 5810, {1,1,1,256});
  g->Transpose(5810, 5811, {0,2,1,3});
  g->Unary(ynn_unary_square, 5811, 5812);
  g->Reduce(ynn_reduce_sum, 5812, 7004, {3}, true);
  g->ShapeProduct(5812, 7003, {3});
  g->Binary(ynn_binary_divide, 7004, 7003, 5813);
  g->Binary(ynn_binary_add, 5813, 7303, 5814);
  g->Binary(ynn_binary_pow, 5814, 7358, 5817);
  g->Binary(ynn_binary_multiply, 5811, 5817, 5818);
  g->Convert(8065, 5819);
  g->Binary(ynn_binary_multiply, 5818, 5819, 5820);
  g->Slice(5820, 5821, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(5820, 5822, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 5822, 5823);
  g->Concat({5823,5821}, 5824, 3);
  g->Binary(ynn_binary_multiply, 5820, 2025, 5825);
  g->Binary(ynn_binary_multiply, 5824, 3078, 5826);
  g->Binary(ynn_binary_add, 5825, 5826, 5828);
  g->Convert(8073, 5829);
  g->Binary(ynn_binary_multiply, 5829, 8074, 5830);
  g->Matmul(5800, 5830, 5831, false, true);
  g->Binary(ynn_binary_divide, 5831, 7077, 5832);
  g->Unary(ynn_unary_round, 5832, 5834);
  g->Binary(ynn_binary_max, 5834, 7155, 5835);
  g->Binary(ynn_binary_min, 5835, 7270, 5836);
  g->Binary(ynn_binary_multiply, 5836, 7077, 5837);
  g->Reshape(5837, 5838, {1,1,1,256});
  g->Transpose(5838, 5839, {0,2,1,3});
  g->Unary(ynn_unary_square, 5839, 5840);
  g->Reduce(ynn_reduce_sum, 5840, 7006, {3}, true);
  g->ShapeProduct(5840, 7005, {3});
  g->Binary(ynn_binary_divide, 7006, 7005, 5841);
  g->Binary(ynn_binary_add, 5841, 7303, 5842);
  g->Binary(ynn_binary_pow, 5842, 7358, 5843);
  g->Binary(ynn_binary_multiply, 5839, 5843, 5845);
}

// Scope: "Layer3 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(5828, 5846, 0.00573749840259552, 0);
  g->Append(7053, 5846, 8383, 2, s2, slinky::expr(int64_t{1}));
  g->View(8383, 8413, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(8413, 5847, 0.00573749840259552, 0);
  g->Quantize(5845, 5848, 0.047244105488061905, 0);
  g->Append(7068, 5848, 8398, 2, s2, slinky::expr(int64_t{1}));
  g->View(8398, 8428, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(8428, 5849, 0.047244105488061905, 0);
}

// Scope: "Layer3 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Convert(8071, 5851);
  g->Binary(ynn_binary_multiply, 5851, 8072, 5852);
  g->Matmul(5800, 5852, 5853, false, true);
  g->Binary(ynn_binary_divide, 5853, 7485, 5854);
  g->Unary(ynn_unary_round, 5854, 5855);
  g->Binary(ynn_binary_max, 5855, 7155, 5856);
  g->Binary(ynn_binary_min, 5856, 7270, 5858);
  g->Binary(ynn_binary_multiply, 5858, 7485, 5859);
  g->SplitDim(5859, 5860, 2, {8,256});
  g->Transpose(5860, 5861, {0,2,1,3});
  g->Unary(ynn_unary_square, 5861, 5862);
  g->Reduce(ynn_reduce_sum, 5862, 7010, {3}, true);
  g->ShapeProduct(5862, 7009, {3});
  g->Binary(ynn_binary_divide, 7010, 7009, 5863);
  g->Binary(ynn_binary_add, 5863, 7303, 5864);
  g->Binary(ynn_binary_pow, 5864, 7358, 5865);
  g->Binary(ynn_binary_multiply, 5861, 5865, 5866);
  g->Convert(8070, 5867);
  g->Binary(ynn_binary_multiply, 5866, 5867, 5869);
  g->Slice(5869, 5870, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(5869, 5871, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 5871, 5872);
  g->Concat({5872,5870}, 5873, 3);
  g->Binary(ynn_binary_multiply, 5869, 2025, 5874);
  g->Binary(ynn_binary_multiply, 5873, 3078, 5875);
  g->Binary(ynn_binary_add, 5874, 5875, 5876);
}

// Scope: "Layer3 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(5876, 5847, 5877, false, true);
  g->Mask(5877, 7514, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 7514, 7014, {-1}, true);
  g->Binary(ynn_binary_subtract, 7514, 7014, 7011);
  g->Unary(ynn_unary_exp, 7011, 7012);
  g->Reduce(ynn_reduce_sum, 7012, 7015, {-1}, true);
  g->Binary(ynn_binary_divide, 6113, 7015, 7013);
  g->Binary(ynn_binary_multiply, 7012, 7013, 5879);
  g->Matmul(5879, 5849, 5880, false, false);
}

// Scope: "Layer3 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(5880, 5881, {0,2,1,3});
  g->FuseDims(5881, 5882, 2, 2);
  g->Binary(ynn_binary_divide, 5882, 7122, 5883);
  g->Unary(ynn_unary_round, 5883, 5884);
  g->Binary(ynn_binary_max, 5884, 7155, 5885);
  g->Binary(ynn_binary_min, 5885, 7270, 5886);
  g->Binary(ynn_binary_multiply, 5886, 7122, 5887);
  g->Convert(8068, 5888);
  g->Binary(ynn_binary_multiply, 5888, 8069, 5889);
  g->Matmul(5887, 5889, 5890, false, true);
  g->Binary(ynn_binary_divide, 5890, 7293, 5891);
  g->Unary(ynn_unary_round, 5891, 5892);
  g->Binary(ynn_binary_max, 5892, 7155, 5893);
  g->Binary(ynn_binary_min, 5893, 7270, 5894);
  g->Binary(ynn_binary_multiply, 5894, 7293, 5895);
}

// Scope: "Layer3 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 5787, 5788);
  g->Reduce(ynn_reduce_sum, 5788, 7002, {2}, true);
  g->ShapeProduct(5788, 7001, {2});
  g->Binary(ynn_binary_divide, 7002, 7001, 5789);
  g->Binary(ynn_binary_add, 5789, 7303, 5790);
  g->Binary(ynn_binary_pow, 5790, 7358, 5791);
  g->Binary(ynn_binary_multiply, 5787, 5791, 5792);
  g->Convert(8049, 5794);
  g->Binary(ynn_binary_multiply, 5792, 5794, 5795);
  BuildLayer3AttentionKvProjection(ctx);
  BuildLayer3AttentionCacheUpdate(ctx);
  BuildLayer3AttentionQueryProjection(ctx);
  BuildLayer3AttentionSdpa(ctx);
  BuildLayer3AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 5895, 5896);
  g->Reduce(ynn_reduce_sum, 5896, 7017, {2}, true);
  g->ShapeProduct(5896, 7016, {2});
  g->Binary(ynn_binary_divide, 7017, 7016, 5897);
  g->Binary(ynn_binary_add, 5897, 7303, 5898);
  g->Binary(ynn_binary_pow, 5898, 7358, 5899);
  g->Binary(ynn_binary_multiply, 5895, 5899, 5900);
  g->Convert(8061, 5901);
  g->Binary(ynn_binary_multiply, 5900, 5901, 5902);
  g->Binary(ynn_binary_add, 5787, 5902, 5903);
}

// Scope: "Layer3 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 5903, 5904);
  g->Reduce(ynn_reduce_sum, 5904, 7019, {2}, true);
  g->ShapeProduct(5904, 7018, {2});
  g->Binary(ynn_binary_divide, 7019, 7018, 5905);
  g->Binary(ynn_binary_add, 5905, 7303, 5906);
  g->Binary(ynn_binary_pow, 5906, 7358, 5907);
  g->Binary(ynn_binary_multiply, 5903, 5907, 5908);
  g->Convert(8064, 5911);
  g->Binary(ynn_binary_multiply, 5908, 5911, 5912);
  g->Binary(ynn_binary_divide, 5912, 7161, 5913);
  g->Unary(ynn_unary_round, 5913, 5914);
  g->Binary(ynn_binary_max, 5914, 7155, 5915);
  g->Binary(ynn_binary_min, 5915, 7270, 5916);
  g->Binary(ynn_binary_multiply, 5916, 7161, 5917);
  g->Convert(8055, 5918);
  g->Binary(ynn_binary_multiply, 5918, 8056, 5919);
  g->Matmul(5917, 5919, 5920, false, true);
  g->Binary(ynn_binary_divide, 5920, 7436, 5922);
  g->Unary(ynn_unary_round, 5922, 5923);
  g->Binary(ynn_binary_max, 5923, 7155, 5924);
  g->Binary(ynn_binary_min, 5924, 7270, 5925);
  g->Binary(ynn_binary_multiply, 5925, 7436, 5926);
  g->Convert(8053, 5927);
  g->Binary(ynn_binary_multiply, 5927, 8054, 5928);
  g->Matmul(5917, 5928, 5929, false, true);
  g->Binary(ynn_binary_divide, 5929, 7436, 5930);
  g->Unary(ynn_unary_round, 5930, 5931);
  g->Binary(ynn_binary_max, 5931, 7155, 5932);
  g->Binary(ynn_binary_min, 5932, 7270, 5933);
  g->Binary(ynn_binary_multiply, 5933, 7436, 5934);
  g->Polynomial(5934, 7022, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7022, 7023);
  g->Binary(ynn_binary_add, 7023, 6113, 7020);
  g->Binary(ynn_binary_multiply, 5934, 6111, 7021);
  g->Binary(ynn_binary_multiply, 7021, 7020, 5935);
  g->Binary(ynn_binary_multiply, 5926, 5935, 5936);
  g->Binary(ynn_binary_divide, 5936, 7395, 5937);
  g->Unary(ynn_unary_round, 5937, 5938);
  g->Binary(ynn_binary_max, 5938, 7155, 5939);
  g->Binary(ynn_binary_min, 5939, 7270, 5940);
  g->Binary(ynn_binary_multiply, 5940, 7395, 5941);
  g->Convert(8051, 5942);
  g->Binary(ynn_binary_multiply, 5942, 8052, 5943);
  g->Matmul(5941, 5943, 5944, false, true);
  g->Binary(ynn_binary_divide, 5944, 7414, 5945);
  g->Unary(ynn_unary_round, 5945, 5946);
  g->Binary(ynn_binary_max, 5946, 7155, 5948);
  g->Binary(ynn_binary_min, 5948, 7270, 5949);
  g->Binary(ynn_binary_multiply, 5949, 7414, 5950);
  g->Unary(ynn_unary_square, 5950, 5951);
  g->Reduce(ynn_reduce_sum, 5951, 7025, {2}, true);
  g->ShapeProduct(5951, 7024, {2});
  g->Binary(ynn_binary_divide, 7025, 7024, 5952);
  g->Binary(ynn_binary_add, 5952, 7303, 5953);
  g->Binary(ynn_binary_pow, 5953, 7358, 5954);
  g->Binary(ynn_binary_multiply, 5950, 5954, 5955);
  g->Convert(8062, 5956);
  g->Binary(ynn_binary_multiply, 5955, 5956, 5957);
  g->Binary(ynn_binary_add, 5903, 5957, 5958);
}

// Scope: "Layer3 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1022, 5959, {0,0,3,0}, {-1,-1,1,-1});
  g->Reshape(5959, 5960, {1,1,256});
  g->Binary(ynn_binary_add, 5960, 8362, 5961);
  g->Binary(ynn_binary_multiply, 5961, 7085, 5962);
  g->Binary(ynn_binary_divide, 5958, 7282, 5963);
  g->Unary(ynn_unary_round, 5963, 5964);
  g->Binary(ynn_binary_max, 5964, 7155, 5965);
  g->Binary(ynn_binary_min, 5965, 7270, 5966);
  g->Binary(ynn_binary_multiply, 5966, 7282, 5967);
  g->Convert(8057, 5968);
  g->Binary(ynn_binary_multiply, 5968, 8058, 5969);
  g->Matmul(5967, 5969, 5970, false, true);
  g->Binary(ynn_binary_divide, 5970, 7452, 5971);
  g->Unary(ynn_unary_round, 5971, 5972);
  g->Binary(ynn_binary_max, 5972, 7155, 5973);
  g->Binary(ynn_binary_min, 5973, 7270, 5974);
  g->Binary(ynn_binary_multiply, 5974, 7452, 5975);
  g->Polynomial(5975, 7028, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7028, 7029);
  g->Binary(ynn_binary_add, 7029, 6113, 7026);
  g->Binary(ynn_binary_multiply, 5975, 6111, 7027);
  g->Binary(ynn_binary_multiply, 7027, 7026, 5976);
  g->Binary(ynn_binary_multiply, 5976, 5962, 5977);
  g->Binary(ynn_binary_divide, 5977, 7189, 5978);
  g->Unary(ynn_unary_round, 5978, 5979);
  g->Binary(ynn_binary_max, 5979, 7155, 5980);
  g->Binary(ynn_binary_min, 5980, 7270, 5981);
  g->Binary(ynn_binary_multiply, 5981, 7189, 5982);
  g->Convert(8059, 5983);
  g->Binary(ynn_binary_multiply, 5983, 8060, 5984);
  g->Matmul(5982, 5984, 5985, false, true);
  g->Binary(ynn_binary_divide, 5985, 7310, 5986);
  g->Unary(ynn_unary_round, 5986, 5987);
  g->Binary(ynn_binary_max, 5987, 7155, 5988);
  g->Binary(ynn_binary_min, 5988, 7270, 5989);
  g->Binary(ynn_binary_multiply, 5989, 7310, 5990);
  g->Unary(ynn_unary_square, 5990, 5991);
  g->Reduce(ynn_reduce_sum, 5991, 7031, {2}, true);
  g->ShapeProduct(5991, 7030, {2});
  g->Binary(ynn_binary_divide, 7031, 7030, 5992);
  g->Binary(ynn_binary_add, 5992, 7303, 5993);
  g->Binary(ynn_binary_pow, 5993, 7358, 5994);
  g->Binary(ynn_binary_multiply, 5990, 5994, 5995);
  g->Convert(8063, 5996);
  g->Binary(ynn_binary_multiply, 5995, 5996, 5997);
  g->Binary(ynn_binary_add, 5958, 5997, 5998);
  g->Convert(8050, 5999);
  g->Binary(ynn_binary_multiply, 5998, 5999, 6000);
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
  g->Binary(ynn_binary_divide, 6007, 7192, 6010);
  g->Unary(ynn_unary_round, 6010, 6011);
  g->Binary(ynn_binary_max, 6011, 7155, 6012);
  g->Binary(ynn_binary_min, 6012, 7270, 6013);
  g->Binary(ynn_binary_multiply, 6013, 7192, 6014);
  g->Convert(8197, 6015);
  g->Binary(ynn_binary_multiply, 6015, 8198, 6016);
  g->Matmul(6014, 6016, 6017, false, true);
  g->Binary(ynn_binary_divide, 6017, 7108, 6018);
  g->Unary(ynn_unary_round, 6018, 6019);
  g->Binary(ynn_binary_max, 6019, 7155, 6021);
  g->Binary(ynn_binary_min, 6021, 7270, 6022);
  g->Binary(ynn_binary_multiply, 6022, 7108, 6023);
  g->Reshape(6023, 6024, {1,1,1,512});
  g->Transpose(6024, 6025, {0,2,1,3});
  g->Unary(ynn_unary_square, 6025, 6026);
  g->Reduce(ynn_reduce_sum, 6026, 7035, {3}, true);
  g->ShapeProduct(6026, 7034, {3});
  g->Binary(ynn_binary_divide, 7035, 7034, 6027);
  g->Binary(ynn_binary_add, 6027, 7303, 6028);
  g->Binary(ynn_binary_pow, 6028, 7358, 6029);
  g->Binary(ynn_binary_multiply, 6025, 6029, 6030);
  g->Convert(8196, 6032);
  g->Binary(ynn_binary_multiply, 6030, 6032, 6033);
  g->Slice(6033, 6034, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(6033, 6035, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 6035, 6036);
  g->Concat({6036,6034}, 6037, 3);
  g->Binary(ynn_binary_multiply, 6033, 5909, 6038);
  g->Binary(ynn_binary_multiply, 6037, 6008, 6039);
  g->Binary(ynn_binary_add, 6038, 6039, 6040);
  g->Convert(8204, 6042);
  g->Binary(ynn_binary_multiply, 6042, 8205, 6043);
  g->Matmul(6014, 6043, 6044, false, true);
  g->Binary(ynn_binary_divide, 6044, 7108, 6045);
  g->Unary(ynn_unary_round, 6045, 6046);
  g->Binary(ynn_binary_max, 6046, 7155, 6047);
  g->Binary(ynn_binary_min, 6047, 7270, 6049);
  g->Binary(ynn_binary_multiply, 6049, 7108, 6050);
  g->Reshape(6050, 6051, {1,1,1,512});
  g->Transpose(6051, 6052, {0,2,1,3});
  g->Unary(ynn_unary_square, 6052, 6053);
  g->Reduce(ynn_reduce_sum, 6053, 7037, {3}, true);
  g->ShapeProduct(6053, 7036, {3});
  g->Binary(ynn_binary_divide, 7037, 7036, 6054);
  g->Binary(ynn_binary_add, 6054, 7303, 6055);
  g->Binary(ynn_binary_pow, 6055, 7358, 6056);
  g->Binary(ynn_binary_multiply, 6052, 6056, 6057);
}

// Scope: "Layer4 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(6040, 6058, 0.0011563472216948867, 0);
  g->Append(7054, 6058, 8384, 2, s2, slinky::expr(int64_t{1}));
  g->View(8384, 8414, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(8414, 6060, 0.0011563472216948867, 0);
  g->Quantize(6057, 6061, 0.01785714365541935, 0);
  g->Append(7069, 6061, 8399, 2, s2, slinky::expr(int64_t{1}));
  g->View(8399, 8429, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(8429, 6062, 0.01785714365541935, 0);
}

// Scope: "Layer4 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Convert(8202, 6064);
  g->Binary(ynn_binary_multiply, 6064, 8203, 6065);
  g->Matmul(6014, 6065, 6066, false, true);
  g->Binary(ynn_binary_divide, 6066, 7256, 6067);
  g->Unary(ynn_unary_round, 6067, 6068);
  g->Binary(ynn_binary_max, 6068, 7155, 6069);
  g->Binary(ynn_binary_min, 6069, 7270, 6070);
  g->Binary(ynn_binary_multiply, 6070, 7256, 6071);
  g->SplitDim(6071, 6073, 2, {8,512});
  g->Transpose(6073, 6074, {0,2,1,3});
  g->Unary(ynn_unary_square, 6074, 6075);
  g->Reduce(ynn_reduce_sum, 6075, 7039, {3}, true);
  g->ShapeProduct(6075, 7038, {3});
  g->Binary(ynn_binary_divide, 7039, 7038, 6076);
  g->Binary(ynn_binary_add, 6076, 7303, 6077);
  g->Binary(ynn_binary_pow, 6077, 7358, 6078);
  g->Binary(ynn_binary_multiply, 6074, 6078, 6079);
  g->Convert(8201, 6080);
  g->Binary(ynn_binary_multiply, 6079, 6080, 6081);
  g->Slice(6081, 6082, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(6081, 6084, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 6084, 6085);
  g->Concat({6085,6082}, 6086, 3);
  g->Binary(ynn_binary_multiply, 6081, 5909, 6087);
  g->Binary(ynn_binary_multiply, 6086, 6008, 6088);
  g->Binary(ynn_binary_add, 6087, 6088, 6089);
}

// Scope: "Layer4 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(6089, 6060, 6090, false, true);
  g->Mask(6090, 7520, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 7520, 7043, {-1}, true);
  g->Binary(ynn_binary_subtract, 7520, 7043, 7040);
  g->Unary(ynn_unary_exp, 7040, 7041);
  g->Reduce(ynn_reduce_sum, 7041, 7044, {-1}, true);
  g->Binary(ynn_binary_divide, 6113, 7044, 7042);
  g->Binary(ynn_binary_multiply, 7041, 7042, 6091);
  g->Matmul(6091, 6062, 6092, false, false);
}

// Scope: "Layer4 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(6092, 6094, {0,2,1,3});
  g->FuseDims(6094, 6095, 2, 2);
  g->Binary(ynn_binary_divide, 6095, 7245, 6096);
  g->Unary(ynn_unary_round, 6096, 6097);
  g->Binary(ynn_binary_max, 6097, 7155, 6098);
  g->Binary(ynn_binary_min, 6098, 7270, 6099);
  g->Binary(ynn_binary_multiply, 6099, 7245, 6100);
  g->Convert(8199, 6101);
  g->Binary(ynn_binary_multiply, 6101, 8200, 6102);
  g->Matmul(6100, 6102, 6103, false, true);
  g->Binary(ynn_binary_divide, 6103, 7173, 4);
  g->Unary(ynn_unary_round, 4, 5);
  g->Binary(ynn_binary_max, 5, 7155, 6);
  g->Binary(ynn_binary_min, 6, 7270, 7);
  g->Binary(ynn_binary_multiply, 7, 7173, 8);
}

// Scope: "Layer4 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 6000, 6001);
  g->Reduce(ynn_reduce_sum, 6001, 7033, {2}, true);
  g->ShapeProduct(6001, 7032, {2});
  g->Binary(ynn_binary_divide, 7033, 7032, 6002);
  g->Binary(ynn_binary_add, 6002, 7303, 6003);
  g->Binary(ynn_binary_pow, 6003, 7358, 6004);
  g->Binary(ynn_binary_multiply, 6000, 6004, 6005);
  g->Convert(8180, 6006);
  g->Binary(ynn_binary_multiply, 6005, 6006, 6007);
  BuildLayer4AttentionKvProjection(ctx);
  BuildLayer4AttentionCacheUpdate(ctx);
  BuildLayer4AttentionQueryProjection(ctx);
  BuildLayer4AttentionSdpa(ctx);
  BuildLayer4AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 8, 9);
  g->Reduce(ynn_reduce_sum, 9, 6105, {2}, true);
  g->ShapeProduct(9, 6104, {2});
  g->Binary(ynn_binary_divide, 6105, 6104, 10);
  g->Binary(ynn_binary_add, 10, 7303, 11);
  g->Binary(ynn_binary_pow, 11, 7358, 12);
  g->Binary(ynn_binary_multiply, 8, 12, 13);
  g->Convert(8192, 15);
  g->Binary(ynn_binary_multiply, 13, 15, 16);
  g->Binary(ynn_binary_add, 6000, 16, 17);
}

// Scope: "Layer4 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 17, 18);
  g->Reduce(ynn_reduce_sum, 18, 6109, {2}, true);
  g->ShapeProduct(18, 6108, {2});
  g->Binary(ynn_binary_divide, 6109, 6108, 19);
  g->Binary(ynn_binary_add, 19, 7303, 20);
  g->Binary(ynn_binary_pow, 20, 7358, 21);
  g->Binary(ynn_binary_multiply, 17, 21, 22);
  g->Convert(8195, 23);
  g->Binary(ynn_binary_multiply, 22, 23, 24);
  g->Binary(ynn_binary_divide, 24, 7163, 26);
  g->Unary(ynn_unary_round, 26, 27);
  g->Binary(ynn_binary_max, 27, 7155, 28);
  g->Binary(ynn_binary_min, 28, 7270, 29);
  g->Binary(ynn_binary_multiply, 29, 7163, 30);
  g->Convert(8186, 31);
  g->Binary(ynn_binary_multiply, 31, 8187, 32);
  g->Matmul(30, 32, 33, false, true);
  g->Binary(ynn_binary_divide, 33, 7421, 34);
  g->Unary(ynn_unary_round, 34, 35);
  g->Binary(ynn_binary_max, 35, 7155, 37);
  g->Binary(ynn_binary_min, 37, 7270, 38);
  g->Binary(ynn_binary_multiply, 38, 7421, 39);
  g->Convert(8184, 40);
  g->Binary(ynn_binary_multiply, 40, 8185, 41);
  g->Matmul(30, 41, 43, false, true);
  g->Binary(ynn_binary_divide, 43, 7421, 44);
  g->Unary(ynn_unary_round, 44, 45);
  g->Binary(ynn_binary_max, 45, 7155, 46);
  g->Binary(ynn_binary_min, 46, 7270, 47);
  g->Binary(ynn_binary_multiply, 47, 7421, 48);
  g->Polynomial(48, 6114, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6114, 6115);
  g->Binary(ynn_binary_add, 6115, 6113, 6110);
  g->Binary(ynn_binary_multiply, 48, 6111, 6112);
  g->Binary(ynn_binary_multiply, 6112, 6110, 49);
  g->Binary(ynn_binary_multiply, 39, 49, 50);
  g->Binary(ynn_binary_divide, 50, 7160, 51);
  g->Unary(ynn_unary_round, 51, 52);
  g->Binary(ynn_binary_max, 52, 7155, 54);
  g->Binary(ynn_binary_min, 54, 7270, 55);
  g->Binary(ynn_binary_multiply, 55, 7160, 56);
  g->Convert(8182, 57);
  g->Binary(ynn_binary_multiply, 57, 8183, 58);
  g->Matmul(56, 58, 59, false, true);
  g->Binary(ynn_binary_divide, 59, 7336, 60);
  g->Unary(ynn_unary_round, 60, 61);
  g->Binary(ynn_binary_max, 61, 7155, 62);
  g->Binary(ynn_binary_min, 62, 7270, 63);
  g->Binary(ynn_binary_multiply, 63, 7336, 65);
  g->Unary(ynn_unary_square, 65, 66);
  g->Reduce(ynn_reduce_sum, 66, 6117, {2}, true);
  g->ShapeProduct(66, 6116, {2});
  g->Binary(ynn_binary_divide, 6117, 6116, 67);
  g->Binary(ynn_binary_add, 67, 7303, 68);
  g->Binary(ynn_binary_pow, 68, 7358, 69);
  g->Binary(ynn_binary_multiply, 65, 69, 70);
  g->Convert(8193, 71);
  g->Binary(ynn_binary_multiply, 70, 71, 72);
  g->Binary(ynn_binary_add, 17, 72, 73);
}

// Scope: "Layer4 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1022, 74, {0,0,4,0}, {-1,-1,1,-1});
  g->Reshape(74, 76, {1,1,256});
  g->Binary(ynn_binary_add, 76, 8368, 77);
  g->Binary(ynn_binary_multiply, 77, 7085, 78);
  g->Binary(ynn_binary_divide, 73, 7440, 79);
  g->Unary(ynn_unary_round, 79, 80);
  g->Binary(ynn_binary_max, 80, 7155, 81);
  g->Binary(ynn_binary_min, 81, 7270, 82);
  g->Binary(ynn_binary_multiply, 82, 7440, 83);
  g->Convert(8188, 84);
  g->Binary(ynn_binary_multiply, 84, 8189, 85);
  g->Matmul(83, 85, 87, false, true);
  g->Binary(ynn_binary_divide, 87, 7094, 88);
  g->Unary(ynn_unary_round, 88, 89);
  g->Binary(ynn_binary_max, 89, 7155, 90);
  g->Binary(ynn_binary_min, 90, 7270, 91);
  g->Binary(ynn_binary_multiply, 91, 7094, 92);
  g->Polynomial(92, 6120, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6120, 6121);
  g->Binary(ynn_binary_add, 6121, 6113, 6118);
  g->Binary(ynn_binary_multiply, 92, 6111, 6119);
  g->Binary(ynn_binary_multiply, 6119, 6118, 93);
  g->Binary(ynn_binary_multiply, 93, 78, 94);
  g->Binary(ynn_binary_divide, 94, 7261, 95);
  g->Unary(ynn_unary_round, 95, 96);
  g->Binary(ynn_binary_max, 96, 7155, 98);
  g->Binary(ynn_binary_min, 98, 7270, 99);
  g->Binary(ynn_binary_multiply, 99, 7261, 100);
  g->Convert(8190, 101);
  g->Binary(ynn_binary_multiply, 101, 8191, 102);
  g->Matmul(100, 102, 103, false, true);
  g->Binary(ynn_binary_divide, 103, 7277, 104);
  g->Unary(ynn_unary_round, 104, 105);
  g->Binary(ynn_binary_max, 105, 7155, 106);
  g->Binary(ynn_binary_min, 106, 7270, 107);
  g->Binary(ynn_binary_multiply, 107, 7277, 110);
  g->Unary(ynn_unary_square, 110, 111);
  g->Reduce(ynn_reduce_sum, 111, 6123, {2}, true);
  g->ShapeProduct(111, 6122, {2});
  g->Binary(ynn_binary_divide, 6123, 6122, 112);
  g->Binary(ynn_binary_add, 112, 7303, 113);
  g->Binary(ynn_binary_pow, 113, 7358, 114);
  g->Binary(ynn_binary_multiply, 110, 114, 115);
  g->Convert(8194, 116);
  g->Binary(ynn_binary_multiply, 115, 116, 117);
  g->Binary(ynn_binary_add, 73, 117, 118);
  g->Convert(8181, 119);
  g->Binary(ynn_binary_multiply, 118, 119, 121);
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
  g->Binary(ynn_binary_divide, 128, 7320, 129);
  g->Unary(ynn_unary_round, 129, 130);
  g->Binary(ynn_binary_max, 130, 7155, 132);
  g->Binary(ynn_binary_min, 132, 7270, 133);
  g->Binary(ynn_binary_multiply, 133, 7320, 134);
  g->Convert(8223, 135);
  g->Binary(ynn_binary_multiply, 135, 8224, 136);
  g->Matmul(134, 136, 137, false, true);
  g->Binary(ynn_binary_divide, 137, 7243, 138);
  g->Unary(ynn_unary_round, 138, 139);
  g->Binary(ynn_binary_max, 139, 7155, 140);
  g->Binary(ynn_binary_min, 140, 7270, 141);
  g->Binary(ynn_binary_multiply, 141, 7243, 143);
  g->Reshape(143, 144, {1,1,1,256});
  g->Transpose(144, 145, {0,2,1,3});
  g->Unary(ynn_unary_square, 145, 146);
  g->Reduce(ynn_reduce_sum, 146, 6127, {3}, true);
  g->ShapeProduct(146, 6126, {3});
  g->Binary(ynn_binary_divide, 6127, 6126, 147);
  g->Binary(ynn_binary_add, 147, 7303, 148);
  g->Binary(ynn_binary_pow, 148, 7358, 149);
  g->Binary(ynn_binary_multiply, 145, 149, 150);
  g->Convert(8222, 151);
  g->Binary(ynn_binary_multiply, 150, 151, 152);
  g->Slice(152, 154, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(152, 155, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 155, 156);
  g->Concat({156,154}, 157, 3);
  g->Binary(ynn_binary_multiply, 152, 2025, 158);
  g->Binary(ynn_binary_multiply, 157, 3078, 159);
  g->Binary(ynn_binary_add, 158, 159, 160);
  g->Convert(8230, 161);
  g->Binary(ynn_binary_multiply, 161, 8231, 162);
  g->Matmul(134, 162, 163, false, true);
  g->Binary(ynn_binary_divide, 163, 7243, 164);
  g->Unary(ynn_unary_round, 164, 165);
  g->Binary(ynn_binary_max, 165, 7155, 166);
  g->Binary(ynn_binary_min, 166, 7270, 167);
  g->Binary(ynn_binary_multiply, 167, 7243, 168);
  g->Reshape(168, 170, {1,1,1,256});
  g->Transpose(170, 171, {0,2,1,3});
  g->Unary(ynn_unary_square, 171, 172);
  g->Reduce(ynn_reduce_sum, 172, 6134, {3}, true);
  g->ShapeProduct(172, 6133, {3});
  g->Binary(ynn_binary_divide, 6134, 6133, 173);
  g->Binary(ynn_binary_add, 173, 7303, 174);
  g->Binary(ynn_binary_pow, 174, 7358, 175);
  g->Binary(ynn_binary_multiply, 171, 175, 176);
}

// Scope: "Layer5 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(160, 177, 0.006011798977851868, 0);
  g->Append(7055, 177, 8385, 2, s2, slinky::expr(int64_t{1}));
  g->View(8385, 8415, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(8415, 179, 0.006011798977851868, 0);
  g->Quantize(176, 180, 0.047244105488061905, 0);
  g->Append(7070, 180, 8400, 2, s2, slinky::expr(int64_t{1}));
  g->View(8400, 8430, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(8430, 181, 0.047244105488061905, 0);
}

// Scope: "Layer5 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Convert(8228, 183);
  g->Binary(ynn_binary_multiply, 183, 8229, 184);
  g->Matmul(134, 184, 185, false, true);
  g->Binary(ynn_binary_divide, 185, 7390, 186);
  g->Unary(ynn_unary_round, 186, 187);
  g->Binary(ynn_binary_max, 187, 7155, 188);
  g->Binary(ynn_binary_min, 188, 7270, 189);
  g->Binary(ynn_binary_multiply, 189, 7390, 190);
  g->SplitDim(190, 191, 2, {8,256});
  g->Transpose(191, 192, {0,2,1,3});
  g->Unary(ynn_unary_square, 192, 194);
  g->Reduce(ynn_reduce_sum, 194, 6136, {3}, true);
  g->ShapeProduct(194, 6135, {3});
  g->Binary(ynn_binary_divide, 6136, 6135, 195);
  g->Binary(ynn_binary_add, 195, 7303, 196);
  g->Binary(ynn_binary_pow, 196, 7358, 197);
  g->Binary(ynn_binary_multiply, 192, 197, 198);
  g->Convert(8227, 199);
  g->Binary(ynn_binary_multiply, 198, 199, 200);
  g->Slice(200, 201, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(200, 202, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 202, 203);
  g->Concat({203,201}, 206, 3);
  g->Binary(ynn_binary_multiply, 200, 2025, 207);
  g->Binary(ynn_binary_multiply, 206, 3078, 208);
  g->Binary(ynn_binary_add, 207, 208, 209);
}

// Scope: "Layer5 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(209, 179, 210, false, true);
  g->Mask(210, 7521, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 7521, 6140, {-1}, true);
  g->Binary(ynn_binary_subtract, 7521, 6140, 6137);
  g->Unary(ynn_unary_exp, 6137, 6138);
  g->Reduce(ynn_reduce_sum, 6138, 6141, {-1}, true);
  g->Binary(ynn_binary_divide, 6113, 6141, 6139);
  g->Binary(ynn_binary_multiply, 6138, 6139, 211);
  g->Matmul(211, 181, 212, false, false);
}

// Scope: "Layer5 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(212, 213, {0,2,1,3});
  g->FuseDims(213, 214, 2, 2);
  g->Binary(ynn_binary_divide, 214, 7171, 216);
  g->Unary(ynn_unary_round, 216, 217);
  g->Binary(ynn_binary_max, 217, 7155, 218);
  g->Binary(ynn_binary_min, 218, 7270, 219);
  g->Binary(ynn_binary_multiply, 219, 7171, 220);
  g->Convert(8225, 221);
  g->Binary(ynn_binary_multiply, 221, 8226, 222);
  g->Matmul(220, 222, 223, false, true);
  g->Binary(ynn_binary_divide, 223, 7111, 224);
  g->Unary(ynn_unary_round, 224, 225);
  g->Binary(ynn_binary_max, 225, 7155, 227);
  g->Binary(ynn_binary_min, 227, 7270, 228);
  g->Binary(ynn_binary_multiply, 228, 7111, 229);
}

// Scope: "Layer5 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 121, 122);
  g->Reduce(ynn_reduce_sum, 122, 6125, {2}, true);
  g->ShapeProduct(122, 6124, {2});
  g->Binary(ynn_binary_divide, 6125, 6124, 123);
  g->Binary(ynn_binary_add, 123, 7303, 124);
  g->Binary(ynn_binary_pow, 124, 7358, 125);
  g->Binary(ynn_binary_multiply, 121, 125, 126);
  g->Convert(8206, 127);
  g->Binary(ynn_binary_multiply, 126, 127, 128);
  BuildLayer5AttentionKvProjection(ctx);
  BuildLayer5AttentionCacheUpdate(ctx);
  BuildLayer5AttentionQueryProjection(ctx);
  BuildLayer5AttentionSdpa(ctx);
  BuildLayer5AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 229, 230);
  g->Reduce(ynn_reduce_sum, 230, 6143, {2}, true);
  g->ShapeProduct(230, 6142, {2});
  g->Binary(ynn_binary_divide, 6143, 6142, 231);
  g->Binary(ynn_binary_add, 231, 7303, 232);
  g->Binary(ynn_binary_pow, 232, 7358, 233);
  g->Binary(ynn_binary_multiply, 229, 233, 234);
  g->Convert(8218, 235);
  g->Binary(ynn_binary_multiply, 234, 235, 236);
  g->Binary(ynn_binary_add, 121, 236, 238);
}

// Scope: "Layer5 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 238, 239);
  g->Reduce(ynn_reduce_sum, 239, 6145, {2}, true);
  g->ShapeProduct(239, 6144, {2});
  g->Binary(ynn_binary_divide, 6145, 6144, 240);
  g->Binary(ynn_binary_add, 240, 7303, 241);
  g->Binary(ynn_binary_pow, 241, 7358, 242);
  g->Binary(ynn_binary_multiply, 238, 242, 243);
  g->Convert(8221, 244);
  g->Binary(ynn_binary_multiply, 243, 244, 245);
  g->Binary(ynn_binary_divide, 245, 7202, 246);
  g->Unary(ynn_unary_round, 246, 247);
  g->Binary(ynn_binary_max, 247, 7155, 249);
  g->Binary(ynn_binary_min, 249, 7270, 250);
  g->Binary(ynn_binary_multiply, 250, 7202, 251);
  g->Convert(8212, 252);
  g->Binary(ynn_binary_multiply, 252, 8213, 253);
  g->Matmul(251, 253, 254, false, true);
  g->Binary(ynn_binary_divide, 254, 7154, 255);
  g->Unary(ynn_unary_round, 255, 256);
  g->Binary(ynn_binary_max, 256, 7155, 257);
  g->Binary(ynn_binary_min, 257, 7270, 258);
  g->Binary(ynn_binary_multiply, 258, 7154, 260);
  g->Convert(8210, 261);
  g->Binary(ynn_binary_multiply, 261, 8211, 262);
  g->Matmul(251, 262, 263, false, true);
  g->Binary(ynn_binary_divide, 263, 7154, 264);
  g->Unary(ynn_unary_round, 264, 266);
  g->Binary(ynn_binary_max, 266, 7155, 267);
  g->Binary(ynn_binary_min, 267, 7270, 268);
  g->Binary(ynn_binary_multiply, 268, 7154, 269);
  g->Polynomial(269, 6148, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6148, 6149);
  g->Binary(ynn_binary_add, 6149, 6113, 6146);
  g->Binary(ynn_binary_multiply, 269, 6111, 6147);
  g->Binary(ynn_binary_multiply, 6147, 6146, 270);
  g->Binary(ynn_binary_multiply, 260, 270, 271);
  g->Binary(ynn_binary_divide, 271, 7265, 272);
  g->Unary(ynn_unary_round, 272, 273);
  g->Binary(ynn_binary_max, 273, 7155, 274);
  g->Binary(ynn_binary_min, 274, 7270, 275);
  g->Binary(ynn_binary_multiply, 275, 7265, 277);
  g->Convert(8208, 278);
  g->Binary(ynn_binary_multiply, 278, 8209, 279);
  g->Matmul(277, 279, 280, false, true);
  g->Binary(ynn_binary_divide, 280, 7206, 281);
  g->Unary(ynn_unary_round, 281, 282);
  g->Binary(ynn_binary_max, 282, 7155, 283);
  g->Binary(ynn_binary_min, 283, 7270, 284);
  g->Binary(ynn_binary_multiply, 284, 7206, 285);
  g->Unary(ynn_unary_square, 285, 286);
  g->Reduce(ynn_reduce_sum, 286, 6151, {2}, true);
  g->ShapeProduct(286, 6150, {2});
  g->Binary(ynn_binary_divide, 6151, 6150, 288);
  g->Binary(ynn_binary_add, 288, 7303, 289);
  g->Binary(ynn_binary_pow, 289, 7358, 290);
  g->Binary(ynn_binary_multiply, 285, 290, 291);
  g->Convert(8219, 292);
  g->Binary(ynn_binary_multiply, 291, 292, 293);
  g->Binary(ynn_binary_add, 238, 293, 294);
}

// Scope: "Layer5 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1022, 295, {0,0,5,0}, {-1,-1,1,-1});
  g->Reshape(295, 296, {1,1,256});
  g->Binary(ynn_binary_add, 296, 8369, 297);
  g->Binary(ynn_binary_multiply, 297, 7085, 299);
  g->Binary(ynn_binary_divide, 294, 7290, 300);
  g->Unary(ynn_unary_round, 300, 301);
  g->Binary(ynn_binary_max, 301, 7155, 302);
  g->Binary(ynn_binary_min, 302, 7270, 303);
  g->Binary(ynn_binary_multiply, 303, 7290, 304);
  g->Convert(8214, 305);
  g->Binary(ynn_binary_multiply, 305, 8215, 306);
  g->Matmul(304, 306, 307, false, true);
  g->Binary(ynn_binary_divide, 307, 7333, 308);
  g->Unary(ynn_unary_round, 308, 311);
  g->Binary(ynn_binary_max, 311, 7155, 312);
  g->Binary(ynn_binary_min, 312, 7270, 313);
  g->Binary(ynn_binary_multiply, 313, 7333, 314);
  g->Polynomial(314, 6154, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6154, 6155);
  g->Binary(ynn_binary_add, 6155, 6113, 6152);
  g->Binary(ynn_binary_multiply, 314, 6111, 6153);
  g->Binary(ynn_binary_multiply, 6153, 6152, 315);
  g->Binary(ynn_binary_multiply, 315, 299, 316);
  g->Binary(ynn_binary_divide, 316, 7373, 317);
  g->Unary(ynn_unary_round, 317, 318);
  g->Binary(ynn_binary_max, 318, 7155, 319);
  g->Binary(ynn_binary_min, 319, 7270, 320);
  g->Binary(ynn_binary_multiply, 320, 7373, 322);
  g->Convert(8216, 323);
  g->Binary(ynn_binary_multiply, 323, 8217, 324);
  g->Matmul(322, 324, 325, false, true);
  g->Binary(ynn_binary_divide, 325, 7167, 326);
  g->Unary(ynn_unary_round, 326, 327);
  g->Binary(ynn_binary_max, 327, 7155, 328);
  g->Binary(ynn_binary_min, 328, 7270, 329);
  g->Binary(ynn_binary_multiply, 329, 7167, 330);
  g->Unary(ynn_unary_square, 330, 331);
  g->Reduce(ynn_reduce_sum, 331, 6157, {2}, true);
  g->ShapeProduct(331, 6156, {2});
  g->Binary(ynn_binary_divide, 6157, 6156, 333);
  g->Binary(ynn_binary_add, 333, 7303, 334);
  g->Binary(ynn_binary_pow, 334, 7358, 335);
  g->Binary(ynn_binary_multiply, 330, 335, 336);
  g->Convert(8220, 337);
  g->Binary(ynn_binary_multiply, 336, 337, 338);
  g->Binary(ynn_binary_add, 294, 338, 339);
  g->Convert(8207, 340);
  g->Binary(ynn_binary_multiply, 339, 340, 341);
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
  g->Binary(ynn_binary_divide, 349, 7292, 350);
  g->Unary(ynn_unary_round, 350, 351);
  g->Binary(ynn_binary_max, 351, 7155, 352);
  g->Binary(ynn_binary_min, 352, 7270, 353);
  g->Binary(ynn_binary_multiply, 353, 7292, 355);
  g->Convert(8249, 356);
  g->Binary(ynn_binary_multiply, 356, 8250, 357);
  g->Matmul(355, 357, 358, false, true);
  g->Binary(ynn_binary_divide, 358, 7123, 359);
  g->Unary(ynn_unary_round, 359, 360);
  g->Binary(ynn_binary_max, 360, 7155, 361);
  g->Binary(ynn_binary_min, 361, 7270, 362);
  g->Binary(ynn_binary_multiply, 362, 7123, 363);
  g->Reshape(363, 364, {1,1,1,256});
  g->Transpose(364, 366, {0,2,1,3});
  g->Unary(ynn_unary_square, 366, 367);
  g->Reduce(ynn_reduce_sum, 367, 6163, {3}, true);
  g->ShapeProduct(367, 6162, {3});
  g->Binary(ynn_binary_divide, 6163, 6162, 368);
  g->Binary(ynn_binary_add, 368, 7303, 369);
  g->Binary(ynn_binary_pow, 369, 7358, 370);
  g->Binary(ynn_binary_multiply, 366, 370, 371);
  g->Convert(8248, 372);
  g->Binary(ynn_binary_multiply, 371, 372, 373);
  g->Slice(373, 374, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(373, 375, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 375, 377);
  g->Concat({377,374}, 378, 3);
  g->Binary(ynn_binary_multiply, 373, 2025, 379);
  g->Binary(ynn_binary_multiply, 378, 3078, 380);
  g->Binary(ynn_binary_add, 379, 380, 381);
  g->Convert(8256, 383);
  g->Binary(ynn_binary_multiply, 383, 8257, 384);
  g->Matmul(355, 384, 385, false, true);
  g->Binary(ynn_binary_divide, 385, 7123, 386);
  g->Unary(ynn_unary_round, 386, 387);
  g->Binary(ynn_binary_max, 387, 7155, 388);
  g->Binary(ynn_binary_min, 388, 7270, 389);
  g->Binary(ynn_binary_multiply, 389, 7123, 390);
  g->Reshape(390, 391, {1,1,1,256});
  g->Transpose(391, 392, {0,2,1,3});
  g->Unary(ynn_unary_square, 392, 394);
  g->Reduce(ynn_reduce_sum, 394, 6165, {3}, true);
  g->ShapeProduct(394, 6164, {3});
  g->Binary(ynn_binary_divide, 6165, 6164, 395);
  g->Binary(ynn_binary_add, 395, 7303, 396);
  g->Binary(ynn_binary_pow, 396, 7358, 397);
  g->Binary(ynn_binary_multiply, 392, 397, 398);
}

// Scope: "Layer6 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(381, 399, 0.0057707298547029495, 0);
  g->Append(7056, 399, 8386, 2, s2, slinky::expr(int64_t{1}));
  g->View(8386, 8416, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(8416, 400, 0.0057707298547029495, 0);
  g->Quantize(398, 401, 0.047244105488061905, 0);
  g->Append(7071, 401, 8401, 2, s2, slinky::expr(int64_t{1}));
  g->View(8401, 8431, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(8431, 403, 0.047244105488061905, 0);
}

// Scope: "Layer6 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Convert(8254, 404);
  g->Binary(ynn_binary_multiply, 404, 8255, 405);
  g->Matmul(355, 405, 408, false, true);
  g->Binary(ynn_binary_divide, 408, 7146, 409);
  g->Unary(ynn_unary_round, 409, 410);
  g->Binary(ynn_binary_max, 410, 7155, 411);
  g->Binary(ynn_binary_min, 411, 7270, 412);
  g->Binary(ynn_binary_multiply, 412, 7146, 413);
  g->SplitDim(413, 414, 2, {8,256});
  g->Transpose(414, 415, {0,2,1,3});
  g->Unary(ynn_unary_square, 415, 416);
  g->Reduce(ynn_reduce_sum, 416, 6167, {3}, true);
  g->ShapeProduct(416, 6166, {3});
  g->Binary(ynn_binary_divide, 6167, 6166, 417);
  g->Binary(ynn_binary_add, 417, 7303, 419);
  g->Binary(ynn_binary_pow, 419, 7358, 420);
  g->Binary(ynn_binary_multiply, 415, 420, 421);
  g->Convert(8253, 422);
  g->Binary(ynn_binary_multiply, 421, 422, 423);
  g->Slice(423, 424, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(423, 425, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 425, 426);
  g->Concat({426,424}, 427, 3);
  g->Binary(ynn_binary_multiply, 423, 2025, 428);
  g->Binary(ynn_binary_multiply, 427, 3078, 430);
  g->Binary(ynn_binary_add, 428, 430, 431);
}

// Scope: "Layer6 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(431, 400, 432, false, true);
  g->Mask(432, 7522, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 7522, 6173, {-1}, true);
  g->Binary(ynn_binary_subtract, 7522, 6173, 6170);
  g->Unary(ynn_unary_exp, 6170, 6171);
  g->Reduce(ynn_reduce_sum, 6171, 6174, {-1}, true);
  g->Binary(ynn_binary_divide, 6113, 6174, 6172);
  g->Binary(ynn_binary_multiply, 6171, 6172, 433);
  g->Matmul(433, 403, 434, false, false);
}

// Scope: "Layer6 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(434, 435, {0,2,1,3});
  g->FuseDims(435, 436, 2, 2);
  g->Binary(ynn_binary_divide, 436, 7126, 437);
  g->Unary(ynn_unary_round, 437, 438);
  g->Binary(ynn_binary_max, 438, 7155, 440);
  g->Binary(ynn_binary_min, 440, 7270, 441);
  g->Binary(ynn_binary_multiply, 441, 7126, 442);
  g->Convert(8251, 443);
  g->Binary(ynn_binary_multiply, 443, 8252, 444);
  g->Matmul(442, 444, 445, false, true);
  g->Binary(ynn_binary_divide, 445, 7417, 446);
  g->Unary(ynn_unary_round, 446, 447);
  g->Binary(ynn_binary_max, 447, 7155, 448);
  g->Binary(ynn_binary_min, 448, 7270, 449);
  g->Binary(ynn_binary_multiply, 449, 7417, 451);
}

// Scope: "Layer6 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 341, 342);
  g->Reduce(ynn_reduce_sum, 342, 6159, {2}, true);
  g->ShapeProduct(342, 6158, {2});
  g->Binary(ynn_binary_divide, 6159, 6158, 344);
  g->Binary(ynn_binary_add, 344, 7303, 345);
  g->Binary(ynn_binary_pow, 345, 7358, 346);
  g->Binary(ynn_binary_multiply, 341, 346, 347);
  g->Convert(8232, 348);
  g->Binary(ynn_binary_multiply, 347, 348, 349);
  BuildLayer6AttentionKvProjection(ctx);
  BuildLayer6AttentionCacheUpdate(ctx);
  BuildLayer6AttentionQueryProjection(ctx);
  BuildLayer6AttentionSdpa(ctx);
  BuildLayer6AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 451, 452);
  g->Reduce(ynn_reduce_sum, 452, 6176, {2}, true);
  g->ShapeProduct(452, 6175, {2});
  g->Binary(ynn_binary_divide, 6176, 6175, 453);
  g->Binary(ynn_binary_add, 453, 7303, 454);
  g->Binary(ynn_binary_pow, 454, 7358, 455);
  g->Binary(ynn_binary_multiply, 451, 455, 456);
  g->Convert(8244, 457);
  g->Binary(ynn_binary_multiply, 456, 457, 458);
  g->Binary(ynn_binary_add, 341, 458, 459);
}

// Scope: "Layer6 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 459, 460);
  g->Reduce(ynn_reduce_sum, 460, 6178, {2}, true);
  g->ShapeProduct(460, 6177, {2});
  g->Binary(ynn_binary_divide, 6178, 6177, 462);
  g->Binary(ynn_binary_add, 462, 7303, 463);
  g->Binary(ynn_binary_pow, 463, 7358, 464);
  g->Binary(ynn_binary_multiply, 459, 464, 465);
  g->Convert(8247, 466);
  g->Binary(ynn_binary_multiply, 465, 466, 467);
  g->Binary(ynn_binary_divide, 467, 7232, 468);
  g->Unary(ynn_unary_round, 468, 469);
  g->Binary(ynn_binary_max, 469, 7155, 470);
  g->Binary(ynn_binary_min, 470, 7270, 471);
  g->Binary(ynn_binary_multiply, 471, 7232, 473);
  g->Convert(8238, 474);
  g->Binary(ynn_binary_multiply, 474, 8239, 475);
  g->Matmul(473, 475, 476, false, true);
  g->Binary(ynn_binary_divide, 476, 7124, 477);
  g->Unary(ynn_unary_round, 477, 478);
  g->Binary(ynn_binary_max, 478, 7155, 479);
  g->Binary(ynn_binary_min, 479, 7270, 480);
  g->Binary(ynn_binary_multiply, 480, 7124, 481);
  g->Convert(8236, 483);
  g->Binary(ynn_binary_multiply, 483, 8237, 484);
  g->Matmul(473, 484, 485, false, true);
  g->Binary(ynn_binary_divide, 485, 7124, 486);
  g->Unary(ynn_unary_round, 486, 487);
  g->Binary(ynn_binary_max, 487, 7155, 488);
  g->Binary(ynn_binary_min, 488, 7270, 490);
  g->Binary(ynn_binary_multiply, 490, 7124, 491);
  g->Polynomial(491, 6181, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6181, 6182);
  g->Binary(ynn_binary_add, 6182, 6113, 6179);
  g->Binary(ynn_binary_multiply, 491, 6111, 6180);
  g->Binary(ynn_binary_multiply, 6180, 6179, 492);
  g->Binary(ynn_binary_multiply, 481, 492, 493);
  g->Binary(ynn_binary_divide, 493, 7094, 494);
  g->Unary(ynn_unary_round, 494, 495);
  g->Binary(ynn_binary_max, 495, 7155, 496);
  g->Binary(ynn_binary_min, 496, 7270, 497);
  g->Binary(ynn_binary_multiply, 497, 7094, 498);
  g->Convert(8234, 499);
  g->Binary(ynn_binary_multiply, 499, 8235, 501);
  g->Matmul(498, 501, 502, false, true);
  g->Binary(ynn_binary_divide, 502, 7223, 503);
  g->Unary(ynn_unary_round, 503, 504);
  g->Binary(ynn_binary_max, 504, 7155, 505);
  g->Binary(ynn_binary_min, 505, 7270, 506);
  g->Binary(ynn_binary_multiply, 506, 7223, 507);
  g->Unary(ynn_unary_square, 507, 508);
  g->Reduce(ynn_reduce_sum, 508, 6184, {2}, true);
  g->ShapeProduct(508, 6183, {2});
  g->Binary(ynn_binary_divide, 6184, 6183, 509);
  g->Binary(ynn_binary_add, 509, 7303, 510);
  g->Binary(ynn_binary_pow, 510, 7358, 513);
  g->Binary(ynn_binary_multiply, 507, 513, 514);
  g->Convert(8245, 515);
  g->Binary(ynn_binary_multiply, 514, 515, 516);
  g->Binary(ynn_binary_add, 459, 516, 517);
}

// Scope: "Layer6 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1022, 518, {0,0,6,0}, {-1,-1,1,-1});
  g->Reshape(518, 519, {1,1,256});
  g->Binary(ynn_binary_add, 519, 8370, 520);
  g->Binary(ynn_binary_multiply, 520, 7085, 521);
  g->Binary(ynn_binary_divide, 517, 7318, 522);
  g->Unary(ynn_unary_round, 522, 524);
  g->Binary(ynn_binary_max, 524, 7155, 525);
  g->Binary(ynn_binary_min, 525, 7270, 526);
  g->Binary(ynn_binary_multiply, 526, 7318, 527);
  g->Convert(8240, 528);
  g->Binary(ynn_binary_multiply, 528, 8241, 529);
  g->Matmul(527, 529, 530, false, true);
  g->Binary(ynn_binary_divide, 530, 7112, 531);
  g->Unary(ynn_unary_round, 531, 532);
  g->Binary(ynn_binary_max, 532, 7155, 533);
  g->Binary(ynn_binary_min, 533, 7270, 535);
  g->Binary(ynn_binary_multiply, 535, 7112, 536);
  g->Polynomial(536, 6189, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6189, 6190);
  g->Binary(ynn_binary_add, 6190, 6113, 6187);
  g->Binary(ynn_binary_multiply, 536, 6111, 6188);
  g->Binary(ynn_binary_multiply, 6188, 6187, 537);
  g->Binary(ynn_binary_multiply, 537, 521, 538);
  g->Binary(ynn_binary_divide, 538, 7405, 539);
  g->Unary(ynn_unary_round, 539, 540);
  g->Binary(ynn_binary_max, 540, 7155, 541);
  g->Binary(ynn_binary_min, 541, 7270, 542);
  g->Binary(ynn_binary_multiply, 542, 7405, 543);
  g->Convert(8242, 544);
  g->Binary(ynn_binary_multiply, 544, 8243, 546);
  g->Matmul(543, 546, 547, false, true);
  g->Binary(ynn_binary_divide, 547, 7388, 548);
  g->Unary(ynn_unary_round, 548, 549);
  g->Binary(ynn_binary_max, 549, 7155, 550);
  g->Binary(ynn_binary_min, 550, 7270, 551);
  g->Binary(ynn_binary_multiply, 551, 7388, 552);
  g->Unary(ynn_unary_square, 552, 553);
  g->Reduce(ynn_reduce_sum, 553, 6192, {2}, true);
  g->ShapeProduct(553, 6191, {2});
  g->Binary(ynn_binary_divide, 6192, 6191, 554);
  g->Binary(ynn_binary_add, 554, 7303, 555);
  g->Binary(ynn_binary_pow, 555, 7358, 557);
  g->Binary(ynn_binary_multiply, 552, 557, 558);
  g->Convert(8246, 559);
  g->Binary(ynn_binary_multiply, 558, 559, 560);
  g->Binary(ynn_binary_add, 517, 560, 561);
  g->Convert(8233, 562);
  g->Binary(ynn_binary_multiply, 561, 562, 563);
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
  g->Binary(ynn_binary_divide, 571, 7254, 572);
  g->Unary(ynn_unary_round, 572, 573);
  g->Binary(ynn_binary_max, 573, 7155, 574);
  g->Binary(ynn_binary_min, 574, 7270, 575);
  g->Binary(ynn_binary_multiply, 575, 7254, 576);
  g->Convert(8275, 577);
  g->Binary(ynn_binary_multiply, 577, 8276, 579);
  g->Matmul(576, 579, 580, false, true);
  g->Binary(ynn_binary_divide, 580, 7479, 581);
  g->Unary(ynn_unary_round, 581, 582);
  g->Binary(ynn_binary_max, 582, 7155, 583);
  g->Binary(ynn_binary_min, 583, 7270, 584);
  g->Binary(ynn_binary_multiply, 584, 7479, 585);
  g->Reshape(585, 586, {1,1,1,256});
  g->Transpose(586, 587, {0,2,1,3});
  g->Unary(ynn_unary_square, 587, 588);
  g->Reduce(ynn_reduce_sum, 588, 6196, {3}, true);
  g->ShapeProduct(588, 6195, {3});
  g->Binary(ynn_binary_divide, 6196, 6195, 590);
  g->Binary(ynn_binary_add, 590, 7303, 591);
  g->Binary(ynn_binary_pow, 591, 7358, 592);
  g->Binary(ynn_binary_multiply, 587, 592, 593);
  g->Convert(8274, 594);
  g->Binary(ynn_binary_multiply, 593, 594, 595);
  g->Slice(595, 596, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(595, 597, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 597, 598);
  g->Concat({598,596}, 599, 3);
  g->Binary(ynn_binary_multiply, 595, 2025, 601);
  g->Binary(ynn_binary_multiply, 599, 3078, 602);
  g->Binary(ynn_binary_add, 601, 602, 603);
  g->Convert(8282, 604);
  g->Binary(ynn_binary_multiply, 604, 8283, 605);
  g->Matmul(576, 605, 607, false, true);
  g->Binary(ynn_binary_divide, 607, 7479, 608);
  g->Unary(ynn_unary_round, 608, 609);
  g->Binary(ynn_binary_max, 609, 7155, 610);
  g->Binary(ynn_binary_min, 610, 7270, 611);
  g->Binary(ynn_binary_multiply, 611, 7479, 612);
  g->Reshape(612, 613, {1,1,1,256});
  g->Transpose(613, 614, {0,2,1,3});
  g->Unary(ynn_unary_square, 614, 615);
  g->Reduce(ynn_reduce_sum, 615, 6198, {3}, true);
  g->ShapeProduct(615, 6197, {3});
  g->Binary(ynn_binary_divide, 6198, 6197, 616);
  g->Binary(ynn_binary_add, 616, 7303, 619);
  g->Binary(ynn_binary_pow, 619, 7358, 620);
  g->Binary(ynn_binary_multiply, 614, 620, 621);
}

// Scope: "Layer7 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(603, 622, 0.005869260523468256, 0);
  g->Append(7057, 622, 8387, 2, s2, slinky::expr(int64_t{1}));
  g->View(8387, 8417, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(8417, 623, 0.005869260523468256, 0);
  g->Quantize(621, 624, 0.047244105488061905, 0);
  g->Append(7072, 624, 8402, 2, s2, slinky::expr(int64_t{1}));
  g->View(8402, 8432, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(8432, 625, 0.047244105488061905, 0);
}

// Scope: "Layer7 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Convert(8280, 626);
  g->Binary(ynn_binary_multiply, 626, 8281, 627);
  g->Matmul(576, 627, 628, false, true);
  g->Binary(ynn_binary_divide, 628, 7375, 629);
  g->Unary(ynn_unary_round, 629, 630);
  g->Binary(ynn_binary_max, 630, 7155, 631);
  g->Binary(ynn_binary_min, 631, 7270, 632);
  g->Binary(ynn_binary_multiply, 632, 7375, 633);
  g->SplitDim(633, 634, 2, {8,256});
  g->Transpose(634, 635, {0,2,1,3});
  g->Unary(ynn_unary_square, 635, 636);
  g->Reduce(ynn_reduce_sum, 636, 6200, {3}, true);
  g->ShapeProduct(636, 6199, {3});
  g->Binary(ynn_binary_divide, 6200, 6199, 637);
  g->Binary(ynn_binary_add, 637, 7303, 638);
  g->Binary(ynn_binary_pow, 638, 7358, 639);
  g->Binary(ynn_binary_multiply, 635, 639, 640);
  g->Convert(8279, 641);
  g->Binary(ynn_binary_multiply, 640, 641, 642);
  g->Slice(642, 643, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(642, 644, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 644, 645);
  g->Concat({645,643}, 646, 3);
  g->Binary(ynn_binary_multiply, 642, 2025, 647);
  g->Binary(ynn_binary_multiply, 646, 3078, 648);
  g->Binary(ynn_binary_add, 647, 648, 649);
}

// Scope: "Layer7 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(649, 623, 650, false, true);
  g->Mask(650, 7523, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 7523, 6204, {-1}, true);
  g->Binary(ynn_binary_subtract, 7523, 6204, 6201);
  g->Unary(ynn_unary_exp, 6201, 6202);
  g->Reduce(ynn_reduce_sum, 6202, 6205, {-1}, true);
  g->Binary(ynn_binary_divide, 6113, 6205, 6203);
  g->Binary(ynn_binary_multiply, 6202, 6203, 651);
  g->Matmul(651, 625, 652, false, false);
}

// Scope: "Layer7 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(652, 653, {0,2,1,3});
  g->FuseDims(653, 654, 2, 2);
  g->Binary(ynn_binary_divide, 654, 7133, 655);
  g->Unary(ynn_unary_round, 655, 656);
  g->Binary(ynn_binary_max, 656, 7155, 657);
  g->Binary(ynn_binary_min, 657, 7270, 658);
  g->Binary(ynn_binary_multiply, 658, 7133, 659);
  g->Convert(8277, 660);
  g->Binary(ynn_binary_multiply, 660, 8278, 661);
  g->Matmul(659, 661, 662, false, true);
  g->Binary(ynn_binary_divide, 662, 7289, 663);
  g->Unary(ynn_unary_round, 663, 664);
  g->Binary(ynn_binary_max, 664, 7155, 665);
  g->Binary(ynn_binary_min, 665, 7270, 666);
  g->Binary(ynn_binary_multiply, 666, 7289, 667);
}

// Scope: "Layer7 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 563, 564);
  g->Reduce(ynn_reduce_sum, 564, 6194, {2}, true);
  g->ShapeProduct(564, 6193, {2});
  g->Binary(ynn_binary_divide, 6194, 6193, 565);
  g->Binary(ynn_binary_add, 565, 7303, 566);
  g->Binary(ynn_binary_pow, 566, 7358, 568);
  g->Binary(ynn_binary_multiply, 563, 568, 569);
  g->Convert(8258, 570);
  g->Binary(ynn_binary_multiply, 569, 570, 571);
  BuildLayer7AttentionKvProjection(ctx);
  BuildLayer7AttentionCacheUpdate(ctx);
  BuildLayer7AttentionQueryProjection(ctx);
  BuildLayer7AttentionSdpa(ctx);
  BuildLayer7AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 667, 668);
  g->Reduce(ynn_reduce_sum, 668, 6207, {2}, true);
  g->ShapeProduct(668, 6206, {2});
  g->Binary(ynn_binary_divide, 6207, 6206, 670);
  g->Binary(ynn_binary_add, 670, 7303, 671);
  g->Binary(ynn_binary_pow, 671, 7358, 672);
  g->Binary(ynn_binary_multiply, 667, 672, 673);
  g->Convert(8270, 674);
  g->Binary(ynn_binary_multiply, 673, 674, 675);
  g->Binary(ynn_binary_add, 563, 675, 676);
}

// Scope: "Layer7 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 676, 677);
  g->Reduce(ynn_reduce_sum, 677, 6209, {2}, true);
  g->ShapeProduct(677, 6208, {2});
  g->Binary(ynn_binary_divide, 6209, 6208, 678);
  g->Binary(ynn_binary_add, 678, 7303, 679);
  g->Binary(ynn_binary_pow, 679, 7358, 681);
  g->Binary(ynn_binary_multiply, 676, 681, 682);
  g->Convert(8273, 683);
  g->Binary(ynn_binary_multiply, 682, 683, 684);
  g->Binary(ynn_binary_divide, 684, 7110, 685);
  g->Unary(ynn_unary_round, 685, 686);
  g->Binary(ynn_binary_max, 686, 7155, 687);
  g->Binary(ynn_binary_min, 687, 7270, 688);
  g->Binary(ynn_binary_multiply, 688, 7110, 689);
  g->Convert(8264, 690);
  g->Binary(ynn_binary_multiply, 690, 8265, 692);
  g->Matmul(689, 692, 693, false, true);
  g->Binary(ynn_binary_divide, 693, 7480, 694);
  g->Unary(ynn_unary_round, 694, 695);
  g->Binary(ynn_binary_max, 695, 7155, 696);
  g->Binary(ynn_binary_min, 696, 7270, 697);
  g->Binary(ynn_binary_multiply, 697, 7480, 698);
  g->Convert(8262, 700);
  g->Binary(ynn_binary_multiply, 700, 8263, 701);
  g->Matmul(689, 701, 702, false, true);
  g->Binary(ynn_binary_divide, 702, 7480, 703);
  g->Unary(ynn_unary_round, 703, 704);
  g->Binary(ynn_binary_max, 704, 7155, 705);
  g->Binary(ynn_binary_min, 705, 7270, 706);
  g->Binary(ynn_binary_multiply, 706, 7480, 707);
  g->Polynomial(707, 6212, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6212, 6213);
  g->Binary(ynn_binary_add, 6213, 6113, 6210);
  g->Binary(ynn_binary_multiply, 707, 6111, 6211);
  g->Binary(ynn_binary_multiply, 6211, 6210, 710);
  g->Binary(ynn_binary_multiply, 698, 710, 711);
  g->Binary(ynn_binary_divide, 711, 7166, 712);
  g->Unary(ynn_unary_round, 712, 713);
  g->Binary(ynn_binary_max, 713, 7155, 714);
  g->Binary(ynn_binary_min, 714, 7270, 715);
  g->Binary(ynn_binary_multiply, 715, 7166, 716);
  g->Convert(8260, 717);
  g->Binary(ynn_binary_multiply, 717, 8261, 718);
  g->Matmul(716, 718, 719, false, true);
  g->Binary(ynn_binary_divide, 719, 7328, 721);
  g->Unary(ynn_unary_round, 721, 722);
  g->Binary(ynn_binary_max, 722, 7155, 723);
  g->Binary(ynn_binary_min, 723, 7270, 724);
  g->Binary(ynn_binary_multiply, 724, 7328, 725);
  g->Unary(ynn_unary_square, 725, 726);
  g->Reduce(ynn_reduce_sum, 726, 6215, {2}, true);
  g->ShapeProduct(726, 6214, {2});
  g->Binary(ynn_binary_divide, 6215, 6214, 727);
  g->Binary(ynn_binary_add, 727, 7303, 728);
  g->Binary(ynn_binary_pow, 728, 7358, 729);
  g->Binary(ynn_binary_multiply, 725, 729, 730);
  g->Convert(8271, 732);
  g->Binary(ynn_binary_multiply, 730, 732, 733);
  g->Binary(ynn_binary_add, 676, 733, 734);
}

// Scope: "Layer7 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1022, 735, {0,0,7,0}, {-1,-1,1,-1});
  g->Reshape(735, 736, {1,1,256});
  g->Binary(ynn_binary_add, 736, 8371, 737);
  g->Binary(ynn_binary_multiply, 737, 7085, 738);
  g->Binary(ynn_binary_divide, 734, 7104, 739);
  g->Unary(ynn_unary_round, 739, 740);
  g->Binary(ynn_binary_max, 740, 7155, 741);
  g->Binary(ynn_binary_min, 741, 7270, 743);
  g->Binary(ynn_binary_multiply, 743, 7104, 744);
  g->Convert(8266, 745);
  g->Binary(ynn_binary_multiply, 745, 8267, 746);
  g->Matmul(744, 746, 747, false, true);
  g->Binary(ynn_binary_divide, 747, 7119, 748);
  g->Unary(ynn_unary_round, 748, 749);
  g->Binary(ynn_binary_max, 749, 7155, 750);
  g->Binary(ynn_binary_min, 750, 7270, 751);
  g->Binary(ynn_binary_multiply, 751, 7119, 752);
  g->Polynomial(752, 6222, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6222, 6223);
  g->Binary(ynn_binary_add, 6223, 6113, 6220);
  g->Binary(ynn_binary_multiply, 752, 6111, 6221);
  g->Binary(ynn_binary_multiply, 6221, 6220, 754);
  g->Binary(ynn_binary_multiply, 754, 738, 755);
  g->Binary(ynn_binary_divide, 755, 7383, 756);
  g->Unary(ynn_unary_round, 756, 757);
  g->Binary(ynn_binary_max, 757, 7155, 758);
  g->Binary(ynn_binary_min, 758, 7270, 759);
  g->Binary(ynn_binary_multiply, 759, 7383, 760);
  g->Convert(8268, 761);
  g->Binary(ynn_binary_multiply, 761, 8269, 762);
  g->Matmul(760, 762, 763, false, true);
  g->Binary(ynn_binary_divide, 763, 7157, 765);
  g->Unary(ynn_unary_round, 765, 766);
  g->Binary(ynn_binary_max, 766, 7155, 767);
  g->Binary(ynn_binary_min, 767, 7270, 768);
  g->Binary(ynn_binary_multiply, 768, 7157, 769);
  g->Unary(ynn_unary_square, 769, 770);
  g->Reduce(ynn_reduce_sum, 770, 6225, {2}, true);
  g->ShapeProduct(770, 6224, {2});
  g->Binary(ynn_binary_divide, 6225, 6224, 771);
  g->Binary(ynn_binary_add, 771, 7303, 772);
  g->Binary(ynn_binary_pow, 772, 7358, 773);
  g->Binary(ynn_binary_multiply, 769, 773, 774);
  g->Convert(8272, 776);
  g->Binary(ynn_binary_multiply, 774, 776, 777);
  g->Binary(ynn_binary_add, 734, 777, 778);
  g->Convert(8259, 779);
  g->Binary(ynn_binary_multiply, 778, 779, 780);
}

// Scope: "Layer7"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7(Context& ctx) {
  BuildLayer7Attention(ctx);
  BuildLayer7Mlp(ctx);
  BuildLayer7PerLayerEmbedding(ctx);
}

}  // namespace BuildGemma4DecodeSource
