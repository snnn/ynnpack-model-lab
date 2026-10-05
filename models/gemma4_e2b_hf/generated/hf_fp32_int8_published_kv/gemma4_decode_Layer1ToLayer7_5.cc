// Generated YNNPACK builder; do not edit.
#include "gemma4_decode_builder.h"

namespace BuildGemma4DecodeSource {

// Scope: "Layer1 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Binary(ynn_binary_divide, 1495, 7221, 1501);
  g->Unary(ynn_unary_round, 1501, 1512);
  g->Binary(ynn_binary_max, 1512, 7225, 1521);
  g->Binary(ynn_binary_min, 1521, 7340, 1525);
  g->Binary(ynn_binary_multiply, 1525, 7221, 1538);
  g->Convert(7639, 1549);
  g->Binary(ynn_binary_multiply, 1549, 7640, 1560);
  g->Matmul(1538, 1560, 1571, false, true);
  g->Binary(ynn_binary_divide, 1571, 7397, 1582);
  g->Unary(ynn_unary_round, 1582, 1593);
  g->Binary(ynn_binary_max, 1593, 7225, 1603);
  g->Binary(ynn_binary_min, 1603, 7340, 1610);
  g->Binary(ynn_binary_multiply, 1610, 7397, 1621);
  g->Reshape(1621, 1632, {1,1,1,256});
  g->Reshape(1632, 1644, {1,1,1,256});
  g->Unary(ynn_unary_square, 1644, 1655);
  g->Reduce(ynn_reduce_sum, 1655, 6423, {3}, true);
  g->ShapeProduct(1655, 6422, {3});
  g->Binary(ynn_binary_divide, 6423, 6422, 1666);
  g->Binary(ynn_binary_add, 1666, 7373, 1677);
  g->Binary(ynn_binary_pow, 1677, 7428, 1688);
  g->Binary(ynn_binary_multiply, 1644, 1688, 1699);
  g->Convert(7638, 1710);
  g->Binary(ynn_binary_multiply, 1699, 1710, 1721);
  g->Slice(1721, 1727, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1721, 1738, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1738, 1746);
  g->Concat({1746,1727}, 1752, 3);
  g->Binary(ynn_binary_multiply, 1721, 2044, 1764);
  g->Binary(ynn_binary_multiply, 1752, 3111, 1775);
  g->Binary(ynn_binary_add, 1764, 1775, 1786);
  g->Convert(7646, 1843);
  g->Binary(ynn_binary_multiply, 1843, 7647, 1854);
  g->Matmul(1538, 1854, 1865, false, true);
  g->Binary(ynn_binary_divide, 1865, 7397, 1876);
  g->Unary(ynn_unary_round, 1876, 1887);
  g->Binary(ynn_binary_max, 1887, 7225, 1898);
  g->Binary(ynn_binary_min, 1898, 7340, 1909);
  g->Binary(ynn_binary_multiply, 1909, 7397, 1920);
  g->Reshape(1920, 1931, {1,1,1,256});
  g->Reshape(1931, 1942, {1,1,1,256});
  g->Unary(ynn_unary_square, 1942, 1949);
  g->Reduce(ynn_reduce_sum, 1949, 6462, {3}, true);
  g->ShapeProduct(1949, 6461, {3});
  g->Binary(ynn_binary_divide, 6462, 6461, 1960);
  g->Binary(ynn_binary_add, 1960, 7373, 1966);
  g->Binary(ynn_binary_pow, 1966, 7428, 1973);
  g->Binary(ynn_binary_multiply, 1942, 1973, 1985);
}

// Scope: "Layer1 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(1786, 1995, 0.005761673673987389, 0);
  g->Append(7116, 1995, 8446, 2, s2, slinky::expr(int64_t{1}));
  g->View(8446, 8476, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(8476, 2027, 0.005761673673987389, 0);
  g->Quantize(1985, 2038, 0.047244105488061905, 0);
  g->Append(7131, 2038, 8461, 2, s2, slinky::expr(int64_t{1}));
  g->View(8461, 8491, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(8491, 2066, 0.047244105488061905, 0);
}

// Scope: "Layer1 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Convert(7644, 2127);
  g->Binary(ynn_binary_multiply, 2127, 7645, 2138);
  g->Matmul(1538, 2138, 2150, false, true);
  g->Binary(ynn_binary_divide, 2150, 7304, 2160);
  g->Unary(ynn_unary_round, 2160, 2167);
  g->Binary(ynn_binary_max, 2167, 7225, 2178);
  g->Binary(ynn_binary_min, 2178, 7340, 2182);
  g->Binary(ynn_binary_multiply, 2182, 7304, 2191);
  g->SplitDim(2191, 2203, 2, {8,256});
  g->FuseDims(2203, 2214, 1, 2);
  g->SplitDim(2214, 2213, 1, {8,1});
  g->Unary(ynn_unary_square, 2213, 2226);
  g->Reduce(ynn_reduce_sum, 2226, 6502, {3}, true);
  g->ShapeProduct(2226, 6501, {3});
  g->Binary(ynn_binary_divide, 6502, 6501, 2237);
  g->Binary(ynn_binary_add, 2237, 7373, 2249);
  g->Binary(ynn_binary_pow, 2249, 7428, 2260);
  g->Binary(ynn_binary_multiply, 2213, 2260, 2266);
  g->Convert(7643, 2277);
  g->Binary(ynn_binary_multiply, 2266, 2277, 2288);
  g->Slice(2288, 2299, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2288, 2310, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2310, 2321);
  g->Concat({2321,2299}, 2332, 3);
  g->Binary(ynn_binary_multiply, 2288, 2044, 2343);
  g->Binary(ynn_binary_multiply, 2332, 3111, 2355);
  g->Binary(ynn_binary_add, 2343, 2355, 2366);
}

// Scope: "Layer1 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(2366, 2027, 2378, false, true);
  g->Mask(2378, 7562, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 7562, 6529, {-1}, true);
  g->Binary(ynn_binary_subtract, 7562, 6529, 6526);
  g->Unary(ynn_unary_exp, 6526, 6527);
  g->Reduce(ynn_reduce_sum, 6527, 6530, {-1}, true);
  g->Binary(ynn_binary_divide, 6183, 6530, 6528);
  g->Binary(ynn_binary_multiply, 6527, 6528, 2399);
  g->Matmul(2399, 2066, 2410, false, false);
}

// Scope: "Layer1 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(2410, 2422, 1, 2);
  g->SplitDim(2422, 2421, 1, {1,8});
  g->FuseDims(2421, 2433, 2, 2);
  g->Binary(ynn_binary_divide, 2433, 7504, 2439);
  g->Unary(ynn_unary_round, 2439, 2450);
  g->Binary(ynn_binary_max, 2450, 7225, 2462);
  g->Binary(ynn_binary_min, 2462, 7340, 2473);
  g->Binary(ynn_binary_multiply, 2473, 7504, 2484);
  g->Convert(7641, 2495);
  g->Binary(ynn_binary_multiply, 2495, 7642, 2506);
  g->Matmul(2484, 2506, 2517, false, true);
  g->Binary(ynn_binary_divide, 2517, 7228, 2528);
  g->Unary(ynn_unary_round, 2528, 2539);
  g->Binary(ynn_binary_max, 2539, 7225, 2551);
  g->Binary(ynn_binary_min, 2551, 7340, 2561);
  g->Binary(ynn_binary_multiply, 2561, 7228, 2574);
}

// Scope: "Layer1 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1417, 1428);
  g->Reduce(ynn_reduce_sum, 1428, 6392, {2}, true);
  g->ShapeProduct(1428, 6391, {2});
  g->Binary(ynn_binary_divide, 6392, 6391, 1440);
  g->Binary(ynn_binary_add, 1440, 7373, 1451);
  g->Binary(ynn_binary_pow, 1451, 7428, 1462);
  g->Binary(ynn_binary_multiply, 1417, 1462, 1473);
  g->Convert(7622, 1484);
  g->Binary(ynn_binary_multiply, 1473, 1484, 1495);
  BuildLayer1AttentionKvProjection(ctx);
  BuildLayer1AttentionCacheUpdate(ctx);
  BuildLayer1AttentionQueryProjection(ctx);
  BuildLayer1AttentionSdpa(ctx);
  BuildLayer1AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2574, 2585);
  g->Reduce(ynn_reduce_sum, 2585, 6561, {2}, true);
  g->ShapeProduct(2585, 6560, {2});
  g->Binary(ynn_binary_divide, 6561, 6560, 2596);
  g->Binary(ynn_binary_add, 2596, 7373, 2607);
  g->Binary(ynn_binary_pow, 2607, 7428, 2613);
  g->Binary(ynn_binary_multiply, 2574, 2613, 2624);
  g->Convert(7634, 2635);
  g->Binary(ynn_binary_multiply, 2624, 2635, 2646);
  g->Binary(ynn_binary_add, 1417, 2646, 2657);
}

// Scope: "Layer1 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2657, 2668);
  g->Reduce(ynn_reduce_sum, 2668, 6573, {2}, true);
  g->ShapeProduct(2668, 6572, {2});
  g->Binary(ynn_binary_divide, 6573, 6572, 2680);
  g->Binary(ynn_binary_add, 2680, 7373, 2691);
  g->Binary(ynn_binary_pow, 2691, 7428, 2702);
  g->Binary(ynn_binary_multiply, 2657, 2702, 2713);
  g->Convert(7637, 2725);
  g->Binary(ynn_binary_multiply, 2713, 2725, 2736);
  g->Binary(ynn_binary_divide, 2736, 7407, 2747);
  g->Unary(ynn_unary_round, 2747, 2758);
  g->Binary(ynn_binary_max, 2758, 7225, 2769);
  g->Binary(ynn_binary_min, 2769, 7340, 2780);
  g->Binary(ynn_binary_multiply, 2780, 7407, 2788);
  g->Convert(7628, 2798);
  g->Binary(ynn_binary_multiply, 2798, 7629, 2809);
  g->Matmul(2788, 2809, 2820, false, true);
  g->Binary(ynn_binary_divide, 2820, 7161, 2831);
  g->Unary(ynn_unary_round, 2831, 2842);
  g->Binary(ynn_binary_max, 2842, 7225, 2853);
  g->Binary(ynn_binary_min, 2853, 7340, 2864);
  g->Binary(ynn_binary_multiply, 2864, 7161, 2875);
  g->Convert(7626, 2938);
  g->Binary(ynn_binary_multiply, 2938, 7627, 2949);
  g->Matmul(2788, 2949, 2957, false, true);
  g->Binary(ynn_binary_divide, 2957, 7161, 2966);
  g->Unary(ynn_unary_round, 2966, 2977);
  g->Binary(ynn_binary_max, 2977, 7225, 2988);
  g->Binary(ynn_binary_min, 2988, 7340, 3000);
  g->Binary(ynn_binary_multiply, 3000, 7161, 3011);
  g->Polynomial(3011, 6626, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6626, 6627);
  g->Binary(ynn_binary_add, 6627, 6183, 6624);
  g->Binary(ynn_binary_multiply, 3011, 6181, 6625);
  g->Binary(ynn_binary_multiply, 6625, 6624, 3022);
  g->Binary(ynn_binary_multiply, 2875, 3022, 3033);
  g->Binary(ynn_binary_divide, 3033, 7148, 3044);
  g->Unary(ynn_unary_round, 3044, 3055);
  g->Binary(ynn_binary_max, 3055, 7225, 3067);
  g->Binary(ynn_binary_min, 3067, 7340, 3078);
  g->Binary(ynn_binary_multiply, 3078, 7148, 3089);
  g->Convert(7624, 3100);
  g->Binary(ynn_binary_multiply, 3100, 7625, 3113);
  g->Matmul(3089, 3113, 3124, false, true);
  g->Binary(ynn_binary_divide, 3124, 7167, 3133);
  g->Unary(ynn_unary_round, 3133, 3141);
  g->Binary(ynn_binary_max, 3141, 7225, 3152);
  g->Binary(ynn_binary_min, 3152, 7340, 3163);
  g->Binary(ynn_binary_multiply, 3163, 7167, 3174);
  g->Unary(ynn_unary_square, 3174, 3185);
  g->Reduce(ynn_reduce_sum, 3185, 6654, {2}, true);
  g->ShapeProduct(3185, 6653, {2});
  g->Binary(ynn_binary_divide, 6654, 6653, 3196);
  g->Binary(ynn_binary_add, 3196, 7373, 3207);
  g->Binary(ynn_binary_pow, 3207, 7428, 3219);
  g->Binary(ynn_binary_multiply, 3174, 3219, 3230);
  g->Convert(7635, 3242);
  g->Binary(ynn_binary_multiply, 3230, 3242, 3253);
  g->Binary(ynn_binary_add, 2657, 3253, 3264);
}

// Scope: "Layer1 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1031, 3275, {0,0,1,0}, {-1,-1,1,-1});
  g->Reshape(3275, 3286, {1,1,256});
  g->Binary(ynn_binary_add, 3286, 8410, 3297);
  g->Binary(ynn_binary_multiply, 3297, 7155, 3307);
  g->Binary(ynn_binary_divide, 3264, 7323, 3314);
  g->Unary(ynn_unary_round, 3314, 3326);
  g->Binary(ynn_binary_max, 3326, 7225, 3337);
  g->Binary(ynn_binary_min, 3337, 7340, 3348);
  g->Binary(ynn_binary_multiply, 3348, 7323, 3359);
  g->Convert(7630, 3370);
  g->Binary(ynn_binary_multiply, 3370, 7631, 3381);
  g->Matmul(3359, 3381, 3392, false, true);
  g->Binary(ynn_binary_divide, 3392, 7499, 3403);
  g->Unary(ynn_unary_round, 3403, 3415);
  g->Binary(ynn_binary_max, 3415, 7225, 3426);
  g->Binary(ynn_binary_min, 3426, 7340, 3438);
  g->Binary(ynn_binary_multiply, 3438, 7499, 3449);
  g->Polynomial(3449, 6695, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6695, 6696);
  g->Binary(ynn_binary_add, 6696, 6183, 6693);
  g->Binary(ynn_binary_multiply, 3449, 6181, 6694);
  g->Binary(ynn_binary_multiply, 6694, 6693, 3460);
  g->Binary(ynn_binary_multiply, 3460, 3307, 3471);
  g->Binary(ynn_binary_divide, 3471, 7371, 3482);
  g->Unary(ynn_unary_round, 3482, 3488);
  g->Binary(ynn_binary_max, 3488, 7225, 3499);
  g->Binary(ynn_binary_min, 3499, 7340, 3510);
  g->Binary(ynn_binary_multiply, 3510, 7371, 3521);
  g->Convert(7632, 3532);
  g->Binary(ynn_binary_multiply, 3532, 7633, 3544);
  g->Matmul(3521, 3544, 3555, false, true);
  g->Binary(ynn_binary_divide, 3555, 7344, 3566);
  g->Unary(ynn_unary_round, 3566, 3577);
  g->Binary(ynn_binary_max, 3577, 7225, 3589);
  g->Binary(ynn_binary_min, 3589, 7340, 3600);
  g->Binary(ynn_binary_multiply, 3600, 7344, 3611);
  g->Unary(ynn_unary_square, 3611, 3622);
  g->Reduce(ynn_reduce_sum, 3622, 6725, {2}, true);
  g->ShapeProduct(3622, 6724, {2});
  g->Binary(ynn_binary_divide, 6725, 6724, 3633);
  g->Binary(ynn_binary_add, 3633, 7373, 3644);
  g->Binary(ynn_binary_pow, 3644, 7428, 3656);
  g->Binary(ynn_binary_multiply, 3611, 3656, 3662);
  g->Convert(7636, 3673);
  g->Binary(ynn_binary_multiply, 3662, 3673, 3684);
  g->Binary(ynn_binary_add, 3264, 3684, 3695);
  g->Convert(7623, 3706);
  g->Binary(ynn_binary_multiply, 3695, 3706, 3717);
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
  g->Binary(ynn_binary_divide, 3796, 7496, 3807);
  g->Unary(ynn_unary_round, 3807, 3818);
  g->Binary(ynn_binary_max, 3818, 7225, 3829);
  g->Binary(ynn_binary_min, 3829, 7340, 3835);
  g->Binary(ynn_binary_multiply, 3835, 7496, 3846);
  g->Convert(7900, 3857);
  g->Binary(ynn_binary_multiply, 3857, 7901, 3869);
  g->Matmul(3846, 3869, 3880, false, true);
  g->Binary(ynn_binary_divide, 3880, 7516, 3891);
  g->Unary(ynn_unary_round, 3891, 3902);
  g->Binary(ynn_binary_max, 3902, 7225, 3913);
  g->Binary(ynn_binary_min, 3913, 7340, 3924);
  g->Binary(ynn_binary_multiply, 3924, 7516, 3935);
  g->Reshape(3935, 3947, {1,1,1,256});
  g->Reshape(3947, 3957, {1,1,1,256});
  g->Unary(ynn_unary_square, 3957, 3969);
  g->Reduce(ynn_reduce_sum, 3969, 6779, {3}, true);
  g->ShapeProduct(3969, 6778, {3});
  g->Binary(ynn_binary_divide, 6779, 6778, 3981);
  g->Binary(ynn_binary_add, 3981, 7373, 3992);
  g->Binary(ynn_binary_pow, 3992, 7428, 4003);
  g->Binary(ynn_binary_multiply, 3957, 4003, 4009);
  g->Convert(7899, 4020);
  g->Binary(ynn_binary_multiply, 4009, 4020, 4031);
  g->Slice(4031, 4042, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(4031, 4053, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 4053, 4064);
  g->Concat({4064,4042}, 4075, 3);
  g->Binary(ynn_binary_multiply, 4031, 2044, 4087);
  g->Binary(ynn_binary_multiply, 4075, 3111, 4098);
  g->Binary(ynn_binary_add, 4087, 4098, 4109);
  g->Convert(7907, 4171);
  g->Binary(ynn_binary_multiply, 4171, 7908, 4177);
  g->Matmul(3846, 4177, 4190, false, true);
  g->Binary(ynn_binary_divide, 4190, 7516, 4201);
  g->Unary(ynn_unary_round, 4201, 4212);
  g->Binary(ynn_binary_max, 4212, 7225, 4223);
  g->Binary(ynn_binary_min, 4223, 7340, 4234);
  g->Binary(ynn_binary_multiply, 4234, 7516, 4245);
  g->Reshape(4245, 4256, {1,1,1,256});
  g->Reshape(4256, 4267, {1,1,1,256});
  g->Unary(ynn_unary_square, 4267, 4278);
  g->Reduce(ynn_reduce_sum, 4278, 6824, {3}, true);
  g->ShapeProduct(4278, 6823, {3});
  g->Binary(ynn_binary_divide, 6824, 6823, 4290);
  g->Binary(ynn_binary_add, 4290, 7373, 4301);
  g->Binary(ynn_binary_pow, 4301, 7428, 4313);
  g->Binary(ynn_binary_multiply, 4267, 4313, 4324);
}

// Scope: "Layer2 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(4109, 4335, 0.005684707313776016, 0);
  g->Append(7122, 4335, 8452, 2, s2, slinky::expr(int64_t{1}));
  g->View(8452, 8482, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(8482, 4361, 0.005684707313776016, 0);
  g->Quantize(4324, 4372, 0.047244105488061905, 0);
  g->Append(7137, 4372, 8467, 2, s2, slinky::expr(int64_t{1}));
  g->View(8467, 8497, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(8497, 4404, 0.047244105488061905, 0);
}

// Scope: "Layer2 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Convert(7905, 4466);
  g->Binary(ynn_binary_multiply, 4466, 7906, 4477);
  g->Matmul(3846, 4477, 4488, false, true);
  g->Binary(ynn_binary_divide, 4488, 7404, 4499);
  g->Unary(ynn_unary_round, 4499, 4511);
  g->Binary(ynn_binary_max, 4511, 7225, 4518);
  g->Binary(ynn_binary_min, 4518, 7340, 4528);
  g->Binary(ynn_binary_multiply, 4528, 7404, 4539);
  g->SplitDim(4539, 4550, 2, {8,256});
  g->FuseDims(4550, 4562, 1, 2);
  g->SplitDim(4562, 4561, 1, {8,1});
  g->Unary(ynn_unary_square, 4561, 4573);
  g->Reduce(ynn_reduce_sum, 4573, 6870, {3}, true);
  g->ShapeProduct(4573, 6869, {3});
  g->Binary(ynn_binary_divide, 6870, 6869, 4584);
  g->Binary(ynn_binary_add, 4584, 7373, 4595);
  g->Binary(ynn_binary_pow, 4595, 7428, 4606);
  g->Binary(ynn_binary_multiply, 4561, 4606, 4618);
  g->Convert(7904, 4630);
  g->Binary(ynn_binary_multiply, 4618, 4630, 4641);
  g->Slice(4641, 4652, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(4641, 4663, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 4663, 4674);
  g->Concat({4674,4652}, 4685, 3);
  g->Binary(ynn_binary_multiply, 4641, 2044, 4693);
  g->Binary(ynn_binary_multiply, 4685, 3111, 4702);
  g->Binary(ynn_binary_add, 4693, 4702, 4713);
}

// Scope: "Layer2 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(4713, 4361, 4725, false, true);
  g->Mask(4725, 7573, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 7573, 6895, {-1}, true);
  g->Binary(ynn_binary_subtract, 7573, 6895, 6892);
  g->Unary(ynn_unary_exp, 6892, 6893);
  g->Reduce(ynn_reduce_sum, 6893, 6896, {-1}, true);
  g->Binary(ynn_binary_divide, 6183, 6896, 6894);
  g->Binary(ynn_binary_multiply, 6893, 6894, 4746);
  g->Matmul(4746, 4404, 4757, false, false);
}

// Scope: "Layer2 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(4757, 4769, 1, 2);
  g->SplitDim(4769, 4768, 1, {1,8});
  g->FuseDims(4768, 4780, 2, 2);
  g->Binary(ynn_binary_divide, 4780, 7301, 4791);
  g->Unary(ynn_unary_round, 4791, 4803);
  g->Binary(ynn_binary_max, 4803, 7225, 4814);
  g->Binary(ynn_binary_min, 4814, 7340, 4825);
  g->Binary(ynn_binary_multiply, 4825, 7301, 4837);
  g->Convert(7902, 4848);
  g->Binary(ynn_binary_multiply, 4848, 7903, 4859);
  g->Matmul(4837, 4859, 4868, false, true);
  g->Binary(ynn_binary_divide, 4868, 7275, 4876);
  g->Unary(ynn_unary_round, 4876, 4887);
  g->Binary(ynn_binary_max, 4887, 7225, 4898);
  g->Binary(ynn_binary_min, 4898, 7340, 4909);
  g->Binary(ynn_binary_multiply, 4909, 7275, 4920);
}

// Scope: "Layer2 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3717, 3728);
  g->Reduce(ynn_reduce_sum, 3728, 6741, {2}, true);
  g->ShapeProduct(3728, 6740, {2});
  g->Binary(ynn_binary_divide, 6741, 6740, 3739);
  g->Binary(ynn_binary_add, 3739, 7373, 3750);
  g->Binary(ynn_binary_pow, 3750, 7428, 3762);
  g->Binary(ynn_binary_multiply, 3717, 3762, 3774);
  g->Convert(7883, 3785);
  g->Binary(ynn_binary_multiply, 3774, 3785, 3796);
  BuildLayer2AttentionKvProjection(ctx);
  BuildLayer2AttentionCacheUpdate(ctx);
  BuildLayer2AttentionQueryProjection(ctx);
  BuildLayer2AttentionSdpa(ctx);
  BuildLayer2AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 4920, 4931);
  g->Reduce(ynn_reduce_sum, 4931, 6929, {2}, true);
  g->ShapeProduct(4931, 6928, {2});
  g->Binary(ynn_binary_divide, 6929, 6928, 4942);
  g->Binary(ynn_binary_add, 4942, 7373, 4953);
  g->Binary(ynn_binary_pow, 4953, 7428, 4964);
  g->Binary(ynn_binary_multiply, 4920, 4964, 4976);
  g->Convert(7895, 4987);
  g->Binary(ynn_binary_multiply, 4976, 4987, 4998);
  g->Binary(ynn_binary_add, 3717, 4998, 5009);
}

// Scope: "Layer2 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 5009, 5020);
  g->Reduce(ynn_reduce_sum, 5020, 6944, {2}, true);
  g->ShapeProduct(5020, 6943, {2});
  g->Binary(ynn_binary_divide, 6944, 6943, 5031);
  g->Binary(ynn_binary_add, 5031, 7373, 5041);
  g->Binary(ynn_binary_pow, 5041, 7428, 5048);
  g->Binary(ynn_binary_multiply, 5009, 5048, 5059);
  g->Convert(7898, 5070);
  g->Binary(ynn_binary_multiply, 5059, 5070, 5081);
  g->Binary(ynn_binary_divide, 5081, 7485, 5092);
  g->Unary(ynn_unary_round, 5092, 5103);
  g->Binary(ynn_binary_max, 5103, 7225, 5114);
  g->Binary(ynn_binary_min, 5114, 7340, 5125);
  g->Binary(ynn_binary_multiply, 5125, 7485, 5136);
  g->Convert(7889, 5148);
  g->Binary(ynn_binary_multiply, 5148, 7890, 5159);
  g->Matmul(5136, 5159, 5170, false, true);
  g->Binary(ynn_binary_divide, 5170, 7296, 5181);
  g->Unary(ynn_unary_round, 5181, 5192);
  g->Binary(ynn_binary_max, 5192, 7225, 5203);
  g->Binary(ynn_binary_min, 5203, 7340, 5214);
  g->Binary(ynn_binary_multiply, 5214, 7296, 5220);
  g->Convert(7887, 5282);
  g->Binary(ynn_binary_multiply, 5282, 7888, 5293);
  g->Matmul(5136, 5293, 5304, false, true);
  g->Binary(ynn_binary_divide, 5304, 7296, 5316);
  g->Unary(ynn_unary_round, 5316, 5327);
  g->Binary(ynn_binary_max, 5327, 7225, 5338);
  g->Binary(ynn_binary_min, 5338, 7340, 5349);
  g->Binary(ynn_binary_multiply, 5349, 7296, 5360);
  g->Polynomial(5360, 6997, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6997, 6998);
  g->Binary(ynn_binary_add, 6998, 6183, 6995);
  g->Binary(ynn_binary_multiply, 5360, 6181, 6996);
  g->Binary(ynn_binary_multiply, 6996, 6995, 5371);
  g->Binary(ynn_binary_multiply, 5220, 5371, 5382);
  g->Binary(ynn_binary_divide, 5382, 7416, 5388);
  g->Unary(ynn_unary_round, 5388, 5399);
  g->Binary(ynn_binary_max, 5399, 7225, 5410);
  g->Binary(ynn_binary_min, 5410, 7340, 5421);
  g->Binary(ynn_binary_multiply, 5421, 7416, 5432);
  g->Convert(7885, 5443);
  g->Binary(ynn_binary_multiply, 5443, 7886, 5454);
  g->Matmul(5432, 5454, 5465, false, true);
  g->Binary(ynn_binary_divide, 5465, 7446, 5477);
  g->Unary(ynn_unary_round, 5477, 5488);
  g->Binary(ynn_binary_max, 5488, 7225, 5500);
  g->Binary(ynn_binary_min, 5500, 7340, 5511);
  g->Binary(ynn_binary_multiply, 5511, 7446, 5522);
  g->Unary(ynn_unary_square, 5522, 5533);
  g->Reduce(ynn_reduce_sum, 5533, 7025, {2}, true);
  g->ShapeProduct(5533, 7024, {2});
  g->Binary(ynn_binary_divide, 7025, 7024, 5544);
  g->Binary(ynn_binary_add, 5544, 7373, 5555);
  g->Binary(ynn_binary_pow, 5555, 7428, 5561);
  g->Binary(ynn_binary_multiply, 5522, 5561, 5572);
  g->Convert(7896, 5584);
  g->Binary(ynn_binary_multiply, 5572, 5584, 5595);
  g->Binary(ynn_binary_add, 5009, 5595, 5606);
}

// Scope: "Layer2 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1031, 5617, {0,0,2,0}, {-1,-1,1,-1});
  g->Reshape(5617, 5628, {1,1,256});
  g->Binary(ynn_binary_add, 5628, 8421, 5639);
  g->Binary(ynn_binary_multiply, 5639, 7155, 5650);
  g->Binary(ynn_binary_divide, 5606, 7386, 5661);
  g->Unary(ynn_unary_round, 5661, 5673);
  g->Binary(ynn_binary_max, 5673, 7225, 5683);
  g->Binary(ynn_binary_min, 5683, 7340, 5696);
  g->Binary(ynn_binary_multiply, 5696, 7386, 5707);
  g->Convert(7891, 5718);
  g->Binary(ynn_binary_multiply, 5718, 7892, 5729);
  g->Matmul(5707, 5729, 5735, false, true);
  g->Binary(ynn_binary_divide, 5735, 7295, 5746);
  g->Unary(ynn_unary_round, 5746, 5757);
  g->Binary(ynn_binary_max, 5757, 7225, 5768);
  g->Binary(ynn_binary_min, 5768, 7340, 5779);
  g->Binary(ynn_binary_multiply, 5779, 7295, 5790);
  g->Polynomial(5790, 7063, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7063, 7064);
  g->Binary(ynn_binary_add, 7064, 6183, 7061);
  g->Binary(ynn_binary_multiply, 5790, 6181, 7062);
  g->Binary(ynn_binary_multiply, 7062, 7061, 5802);
  g->Binary(ynn_binary_multiply, 5802, 5650, 5813);
  g->Binary(ynn_binary_divide, 5813, 7519, 5824);
  g->Unary(ynn_unary_round, 5824, 5829);
  g->Binary(ynn_binary_max, 5829, 7225, 5830);
  g->Binary(ynn_binary_min, 5830, 7340, 5831);
  g->Binary(ynn_binary_multiply, 5831, 7519, 5832);
  g->Convert(7893, 5833);
  g->Binary(ynn_binary_multiply, 5833, 7894, 5834);
  g->Matmul(5832, 5834, 5835, false, true);
  g->Binary(ynn_binary_divide, 5835, 7297, 5837);
  g->Unary(ynn_unary_round, 5837, 5838);
  g->Binary(ynn_binary_max, 5838, 7225, 5839);
  g->Binary(ynn_binary_min, 5839, 7340, 5840);
  g->Binary(ynn_binary_multiply, 5840, 7297, 5841);
  g->Unary(ynn_unary_square, 5841, 5842);
  g->Reduce(ynn_reduce_sum, 5842, 7070, {2}, true);
  g->ShapeProduct(5842, 7069, {2});
  g->Binary(ynn_binary_divide, 7070, 7069, 5843);
  g->Binary(ynn_binary_add, 5843, 7373, 5844);
  g->Binary(ynn_binary_pow, 5844, 7428, 5845);
  g->Binary(ynn_binary_multiply, 5841, 5845, 5846);
  g->Convert(7897, 5848);
  g->Binary(ynn_binary_multiply, 5846, 5848, 5849);
  g->Binary(ynn_binary_add, 5606, 5849, 5850);
  g->Convert(7884, 5851);
  g->Binary(ynn_binary_multiply, 5850, 5851, 5852);
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
  g->Binary(ynn_binary_divide, 5860, 7462, 5861);
  g->Unary(ynn_unary_round, 5861, 5862);
  g->Binary(ynn_binary_max, 5862, 7225, 5863);
  g->Binary(ynn_binary_min, 5863, 7340, 5864);
  g->Binary(ynn_binary_multiply, 5864, 7462, 5865);
  g->Convert(8136, 5866);
  g->Binary(ynn_binary_multiply, 5866, 8137, 5867);
  g->Matmul(5865, 5867, 5868, false, true);
  g->Binary(ynn_binary_divide, 5868, 7147, 5870);
  g->Unary(ynn_unary_round, 5870, 5871);
  g->Binary(ynn_binary_max, 5871, 7225, 5872);
  g->Binary(ynn_binary_min, 5872, 7340, 5873);
  g->Binary(ynn_binary_multiply, 5873, 7147, 5874);
  g->Reshape(5874, 5875, {1,1,1,256});
  g->Reshape(5875, 5876, {1,1,1,256});
  g->Unary(ynn_unary_square, 5876, 5877);
  g->Reduce(ynn_reduce_sum, 5877, 7074, {3}, true);
  g->ShapeProduct(5877, 7073, {3});
  g->Binary(ynn_binary_divide, 7074, 7073, 5878);
  g->Binary(ynn_binary_add, 5878, 7373, 5879);
  g->Binary(ynn_binary_pow, 5879, 7428, 5882);
  g->Binary(ynn_binary_multiply, 5876, 5882, 5883);
  g->Convert(8135, 5884);
  g->Binary(ynn_binary_multiply, 5883, 5884, 5885);
  g->Slice(5885, 5886, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(5885, 5887, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 5887, 5888);
  g->Concat({5888,5886}, 5889, 3);
  g->Binary(ynn_binary_multiply, 5885, 2044, 5890);
  g->Binary(ynn_binary_multiply, 5889, 3111, 5891);
  g->Binary(ynn_binary_add, 5890, 5891, 5893);
  g->Convert(8143, 5894);
  g->Binary(ynn_binary_multiply, 5894, 8144, 5895);
  g->Matmul(5865, 5895, 5896, false, true);
  g->Binary(ynn_binary_divide, 5896, 7147, 5897);
  g->Unary(ynn_unary_round, 5897, 5899);
  g->Binary(ynn_binary_max, 5899, 7225, 5900);
  g->Binary(ynn_binary_min, 5900, 7340, 5901);
  g->Binary(ynn_binary_multiply, 5901, 7147, 5902);
  g->Reshape(5902, 5903, {1,1,1,256});
  g->Reshape(5903, 5904, {1,1,1,256});
  g->Unary(ynn_unary_square, 5904, 5905);
  g->Reduce(ynn_reduce_sum, 5905, 7076, {3}, true);
  g->ShapeProduct(5905, 7075, {3});
  g->Binary(ynn_binary_divide, 7076, 7075, 5906);
  g->Binary(ynn_binary_add, 5906, 7373, 5907);
  g->Binary(ynn_binary_pow, 5907, 7428, 5908);
  g->Binary(ynn_binary_multiply, 5904, 5908, 5910);
}

// Scope: "Layer3 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(5893, 5911, 0.00573749840259552, 0);
  g->Append(7123, 5911, 8453, 2, s2, slinky::expr(int64_t{1}));
  g->View(8453, 8483, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(8483, 5912, 0.00573749840259552, 0);
  g->Quantize(5910, 5913, 0.047244105488061905, 0);
  g->Append(7138, 5913, 8468, 2, s2, slinky::expr(int64_t{1}));
  g->View(8468, 8498, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(8498, 5914, 0.047244105488061905, 0);
}

// Scope: "Layer3 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Convert(8141, 5916);
  g->Binary(ynn_binary_multiply, 5916, 8142, 5917);
  g->Matmul(5865, 5917, 5918, false, true);
  g->Binary(ynn_binary_divide, 5918, 7555, 5919);
  g->Unary(ynn_unary_round, 5919, 5920);
  g->Binary(ynn_binary_max, 5920, 7225, 5921);
  g->Binary(ynn_binary_min, 5921, 7340, 5923);
  g->Binary(ynn_binary_multiply, 5923, 7555, 5924);
  g->SplitDim(5924, 5925, 2, {8,256});
  g->FuseDims(5925, 5927, 1, 2);
  g->SplitDim(5927, 5926, 1, {8,1});
  g->Unary(ynn_unary_square, 5926, 5928);
  g->Reduce(ynn_reduce_sum, 5928, 7080, {3}, true);
  g->ShapeProduct(5928, 7079, {3});
  g->Binary(ynn_binary_divide, 7080, 7079, 5929);
  g->Binary(ynn_binary_add, 5929, 7373, 5930);
  g->Binary(ynn_binary_pow, 5930, 7428, 5931);
  g->Binary(ynn_binary_multiply, 5926, 5931, 5932);
  g->Convert(8140, 5933);
  g->Binary(ynn_binary_multiply, 5932, 5933, 5935);
  g->Slice(5935, 5936, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(5935, 5937, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 5937, 5938);
  g->Concat({5938,5936}, 5939, 3);
  g->Binary(ynn_binary_multiply, 5935, 2044, 5940);
  g->Binary(ynn_binary_multiply, 5939, 3111, 5941);
  g->Binary(ynn_binary_add, 5940, 5941, 5942);
}

// Scope: "Layer3 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(5942, 5912, 5943, false, true);
  g->Mask(5943, 7584, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 7584, 7084, {-1}, true);
  g->Binary(ynn_binary_subtract, 7584, 7084, 7081);
  g->Unary(ynn_unary_exp, 7081, 7082);
  g->Reduce(ynn_reduce_sum, 7082, 7085, {-1}, true);
  g->Binary(ynn_binary_divide, 6183, 7085, 7083);
  g->Binary(ynn_binary_multiply, 7082, 7083, 5945);
  g->Matmul(5945, 5914, 5946, false, false);
}

// Scope: "Layer3 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(5946, 5948, 1, 2);
  g->SplitDim(5948, 5947, 1, {1,8});
  g->FuseDims(5947, 5949, 2, 2);
  g->Binary(ynn_binary_divide, 5949, 7192, 5950);
  g->Unary(ynn_unary_round, 5950, 5951);
  g->Binary(ynn_binary_max, 5951, 7225, 5952);
  g->Binary(ynn_binary_min, 5952, 7340, 5953);
  g->Binary(ynn_binary_multiply, 5953, 7192, 5954);
  g->Convert(8138, 5955);
  g->Binary(ynn_binary_multiply, 5955, 8139, 5956);
  g->Matmul(5954, 5956, 5957, false, true);
  g->Binary(ynn_binary_divide, 5957, 7363, 5958);
  g->Unary(ynn_unary_round, 5958, 5959);
  g->Binary(ynn_binary_max, 5959, 7225, 5960);
  g->Binary(ynn_binary_min, 5960, 7340, 5961);
  g->Binary(ynn_binary_multiply, 5961, 7363, 5962);
}

// Scope: "Layer3 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 5852, 5853);
  g->Reduce(ynn_reduce_sum, 5853, 7072, {2}, true);
  g->ShapeProduct(5853, 7071, {2});
  g->Binary(ynn_binary_divide, 7072, 7071, 5854);
  g->Binary(ynn_binary_add, 5854, 7373, 5855);
  g->Binary(ynn_binary_pow, 5855, 7428, 5856);
  g->Binary(ynn_binary_multiply, 5852, 5856, 5857);
  g->Convert(8119, 5859);
  g->Binary(ynn_binary_multiply, 5857, 5859, 5860);
  BuildLayer3AttentionKvProjection(ctx);
  BuildLayer3AttentionCacheUpdate(ctx);
  BuildLayer3AttentionQueryProjection(ctx);
  BuildLayer3AttentionSdpa(ctx);
  BuildLayer3AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 5962, 5963);
  g->Reduce(ynn_reduce_sum, 5963, 7087, {2}, true);
  g->ShapeProduct(5963, 7086, {2});
  g->Binary(ynn_binary_divide, 7087, 7086, 5964);
  g->Binary(ynn_binary_add, 5964, 7373, 5965);
  g->Binary(ynn_binary_pow, 5965, 7428, 5966);
  g->Binary(ynn_binary_multiply, 5962, 5966, 5967);
  g->Convert(8131, 5968);
  g->Binary(ynn_binary_multiply, 5967, 5968, 5969);
  g->Binary(ynn_binary_add, 5852, 5969, 5970);
}

// Scope: "Layer3 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 5970, 5971);
  g->Reduce(ynn_reduce_sum, 5971, 7089, {2}, true);
  g->ShapeProduct(5971, 7088, {2});
  g->Binary(ynn_binary_divide, 7089, 7088, 5972);
  g->Binary(ynn_binary_add, 5972, 7373, 5973);
  g->Binary(ynn_binary_pow, 5973, 7428, 5974);
  g->Binary(ynn_binary_multiply, 5970, 5974, 5975);
  g->Convert(8134, 5978);
  g->Binary(ynn_binary_multiply, 5975, 5978, 5979);
  g->Binary(ynn_binary_divide, 5979, 7231, 5980);
  g->Unary(ynn_unary_round, 5980, 5981);
  g->Binary(ynn_binary_max, 5981, 7225, 5982);
  g->Binary(ynn_binary_min, 5982, 7340, 5983);
  g->Binary(ynn_binary_multiply, 5983, 7231, 5984);
  g->Convert(8125, 5985);
  g->Binary(ynn_binary_multiply, 5985, 8126, 5986);
  g->Matmul(5984, 5986, 5987, false, true);
  g->Binary(ynn_binary_divide, 5987, 7506, 5989);
  g->Unary(ynn_unary_round, 5989, 5990);
  g->Binary(ynn_binary_max, 5990, 7225, 5991);
  g->Binary(ynn_binary_min, 5991, 7340, 5992);
  g->Binary(ynn_binary_multiply, 5992, 7506, 5993);
  g->Convert(8123, 5994);
  g->Binary(ynn_binary_multiply, 5994, 8124, 5995);
  g->Matmul(5984, 5995, 5996, false, true);
  g->Binary(ynn_binary_divide, 5996, 7506, 5997);
  g->Unary(ynn_unary_round, 5997, 5998);
  g->Binary(ynn_binary_max, 5998, 7225, 5999);
  g->Binary(ynn_binary_min, 5999, 7340, 6000);
  g->Binary(ynn_binary_multiply, 6000, 7506, 6001);
  g->Polynomial(6001, 7092, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7092, 7093);
  g->Binary(ynn_binary_add, 7093, 6183, 7090);
  g->Binary(ynn_binary_multiply, 6001, 6181, 7091);
  g->Binary(ynn_binary_multiply, 7091, 7090, 6002);
  g->Binary(ynn_binary_multiply, 5993, 6002, 6003);
  g->Binary(ynn_binary_divide, 6003, 7465, 6004);
  g->Unary(ynn_unary_round, 6004, 6005);
  g->Binary(ynn_binary_max, 6005, 7225, 6006);
  g->Binary(ynn_binary_min, 6006, 7340, 6007);
  g->Binary(ynn_binary_multiply, 6007, 7465, 6008);
  g->Convert(8121, 6009);
  g->Binary(ynn_binary_multiply, 6009, 8122, 6010);
  g->Matmul(6008, 6010, 6011, false, true);
  g->Binary(ynn_binary_divide, 6011, 7484, 6012);
  g->Unary(ynn_unary_round, 6012, 6013);
  g->Binary(ynn_binary_max, 6013, 7225, 6015);
  g->Binary(ynn_binary_min, 6015, 7340, 6016);
  g->Binary(ynn_binary_multiply, 6016, 7484, 6017);
  g->Unary(ynn_unary_square, 6017, 6018);
  g->Reduce(ynn_reduce_sum, 6018, 7095, {2}, true);
  g->ShapeProduct(6018, 7094, {2});
  g->Binary(ynn_binary_divide, 7095, 7094, 6019);
  g->Binary(ynn_binary_add, 6019, 7373, 6020);
  g->Binary(ynn_binary_pow, 6020, 7428, 6021);
  g->Binary(ynn_binary_multiply, 6017, 6021, 6022);
  g->Convert(8132, 6023);
  g->Binary(ynn_binary_multiply, 6022, 6023, 6024);
  g->Binary(ynn_binary_add, 5970, 6024, 6025);
}

// Scope: "Layer3 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1031, 6026, {0,0,3,0}, {-1,-1,1,-1});
  g->Reshape(6026, 6027, {1,1,256});
  g->Binary(ynn_binary_add, 6027, 8432, 6028);
  g->Binary(ynn_binary_multiply, 6028, 7155, 6029);
  g->Binary(ynn_binary_divide, 6025, 7352, 6030);
  g->Unary(ynn_unary_round, 6030, 6031);
  g->Binary(ynn_binary_max, 6031, 7225, 6032);
  g->Binary(ynn_binary_min, 6032, 7340, 6033);
  g->Binary(ynn_binary_multiply, 6033, 7352, 6034);
  g->Convert(8127, 6035);
  g->Binary(ynn_binary_multiply, 6035, 8128, 6036);
  g->Matmul(6034, 6036, 6037, false, true);
  g->Binary(ynn_binary_divide, 6037, 7522, 6038);
  g->Unary(ynn_unary_round, 6038, 6039);
  g->Binary(ynn_binary_max, 6039, 7225, 6040);
  g->Binary(ynn_binary_min, 6040, 7340, 6041);
  g->Binary(ynn_binary_multiply, 6041, 7522, 6042);
  g->Polynomial(6042, 7098, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7098, 7099);
  g->Binary(ynn_binary_add, 7099, 6183, 7096);
  g->Binary(ynn_binary_multiply, 6042, 6181, 7097);
  g->Binary(ynn_binary_multiply, 7097, 7096, 6043);
  g->Binary(ynn_binary_multiply, 6043, 6029, 6044);
  g->Binary(ynn_binary_divide, 6044, 7259, 6045);
  g->Unary(ynn_unary_round, 6045, 6046);
  g->Binary(ynn_binary_max, 6046, 7225, 6047);
  g->Binary(ynn_binary_min, 6047, 7340, 6048);
  g->Binary(ynn_binary_multiply, 6048, 7259, 6049);
  g->Convert(8129, 6050);
  g->Binary(ynn_binary_multiply, 6050, 8130, 6051);
  g->Matmul(6049, 6051, 6052, false, true);
  g->Binary(ynn_binary_divide, 6052, 7380, 6053);
  g->Unary(ynn_unary_round, 6053, 6054);
  g->Binary(ynn_binary_max, 6054, 7225, 6055);
  g->Binary(ynn_binary_min, 6055, 7340, 6056);
  g->Binary(ynn_binary_multiply, 6056, 7380, 6057);
  g->Unary(ynn_unary_square, 6057, 6058);
  g->Reduce(ynn_reduce_sum, 6058, 7101, {2}, true);
  g->ShapeProduct(6058, 7100, {2});
  g->Binary(ynn_binary_divide, 7101, 7100, 6059);
  g->Binary(ynn_binary_add, 6059, 7373, 6060);
  g->Binary(ynn_binary_pow, 6060, 7428, 6061);
  g->Binary(ynn_binary_multiply, 6057, 6061, 6062);
  g->Convert(8133, 6063);
  g->Binary(ynn_binary_multiply, 6062, 6063, 6064);
  g->Binary(ynn_binary_add, 6025, 6064, 6065);
  g->Convert(8120, 6066);
  g->Binary(ynn_binary_multiply, 6065, 6066, 6067);
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
  g->Binary(ynn_binary_divide, 6074, 7262, 6077);
  g->Unary(ynn_unary_round, 6077, 6078);
  g->Binary(ynn_binary_max, 6078, 7225, 6079);
  g->Binary(ynn_binary_min, 6079, 7340, 6080);
  g->Binary(ynn_binary_multiply, 6080, 7262, 6081);
  g->Convert(8267, 6082);
  g->Binary(ynn_binary_multiply, 6082, 8268, 6083);
  g->Matmul(6081, 6083, 6084, false, true);
  g->Binary(ynn_binary_divide, 6084, 7178, 6085);
  g->Unary(ynn_unary_round, 6085, 6086);
  g->Binary(ynn_binary_max, 6086, 7225, 6088);
  g->Binary(ynn_binary_min, 6088, 7340, 6089);
  g->Binary(ynn_binary_multiply, 6089, 7178, 6090);
  g->Reshape(6090, 6091, {1,1,1,512});
  g->Reshape(6091, 6092, {1,1,1,512});
  g->Unary(ynn_unary_square, 6092, 6093);
  g->Reduce(ynn_reduce_sum, 6093, 7105, {3}, true);
  g->ShapeProduct(6093, 7104, {3});
  g->Binary(ynn_binary_divide, 7105, 7104, 6094);
  g->Binary(ynn_binary_add, 6094, 7373, 6095);
  g->Binary(ynn_binary_pow, 6095, 7428, 6096);
  g->Binary(ynn_binary_multiply, 6092, 6096, 6097);
  g->Convert(8266, 6099);
  g->Binary(ynn_binary_multiply, 6097, 6099, 6100);
  g->Slice(6100, 6101, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(6100, 6102, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 6102, 6103);
  g->Concat({6103,6101}, 6104, 3);
  g->Binary(ynn_binary_multiply, 6100, 5976, 6105);
  g->Binary(ynn_binary_multiply, 6104, 6075, 6106);
  g->Binary(ynn_binary_add, 6105, 6106, 6107);
  g->Convert(8274, 6109);
  g->Binary(ynn_binary_multiply, 6109, 8275, 6110);
  g->Matmul(6081, 6110, 6111, false, true);
  g->Binary(ynn_binary_divide, 6111, 7178, 6112);
  g->Unary(ynn_unary_round, 6112, 6113);
  g->Binary(ynn_binary_max, 6113, 7225, 6114);
  g->Binary(ynn_binary_min, 6114, 7340, 6116);
  g->Binary(ynn_binary_multiply, 6116, 7178, 6117);
  g->Reshape(6117, 6118, {1,1,1,512});
  g->Reshape(6118, 6119, {1,1,1,512});
  g->Unary(ynn_unary_square, 6119, 6120);
  g->Reduce(ynn_reduce_sum, 6120, 7107, {3}, true);
  g->ShapeProduct(6120, 7106, {3});
  g->Binary(ynn_binary_divide, 7107, 7106, 6121);
  g->Binary(ynn_binary_add, 6121, 7373, 6122);
  g->Binary(ynn_binary_pow, 6122, 7428, 6123);
  g->Binary(ynn_binary_multiply, 6119, 6123, 6124);
}

// Scope: "Layer4 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(6107, 6125, 0.0011563472216948867, 0);
  g->Append(7124, 6125, 8454, 2, s2, slinky::expr(int64_t{1}));
  g->View(8454, 8484, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(8484, 6127, 0.0011563472216948867, 0);
  g->Quantize(6124, 6128, 0.01785714365541935, 0);
  g->Append(7139, 6128, 8469, 2, s2, slinky::expr(int64_t{1}));
  g->View(8469, 8499, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(8499, 6129, 0.01785714365541935, 0);
}

// Scope: "Layer4 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Convert(8272, 6131);
  g->Binary(ynn_binary_multiply, 6131, 8273, 6132);
  g->Matmul(6081, 6132, 6133, false, true);
  g->Binary(ynn_binary_divide, 6133, 7326, 6134);
  g->Unary(ynn_unary_round, 6134, 6135);
  g->Binary(ynn_binary_max, 6135, 7225, 6136);
  g->Binary(ynn_binary_min, 6136, 7340, 6137);
  g->Binary(ynn_binary_multiply, 6137, 7326, 6138);
  g->SplitDim(6138, 6140, 2, {8,512});
  g->FuseDims(6140, 6142, 1, 2);
  g->SplitDim(6142, 6141, 1, {8,1});
  g->Unary(ynn_unary_square, 6141, 6143);
  g->Reduce(ynn_reduce_sum, 6143, 7109, {3}, true);
  g->ShapeProduct(6143, 7108, {3});
  g->Binary(ynn_binary_divide, 7109, 7108, 6144);
  g->Binary(ynn_binary_add, 6144, 7373, 6145);
  g->Binary(ynn_binary_pow, 6145, 7428, 6146);
  g->Binary(ynn_binary_multiply, 6141, 6146, 6147);
  g->Convert(8271, 6148);
  g->Binary(ynn_binary_multiply, 6147, 6148, 6149);
  g->Slice(6149, 6150, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(6149, 6152, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 6152, 6153);
  g->Concat({6153,6150}, 6154, 3);
  g->Binary(ynn_binary_multiply, 6149, 5976, 6155);
  g->Binary(ynn_binary_multiply, 6154, 6075, 6156);
  g->Binary(ynn_binary_add, 6155, 6156, 6157);
}

// Scope: "Layer4 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(6157, 6127, 6158, false, true);
  g->Mask(6158, 7590, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 7590, 7113, {-1}, true);
  g->Binary(ynn_binary_subtract, 7590, 7113, 7110);
  g->Unary(ynn_unary_exp, 7110, 7111);
  g->Reduce(ynn_reduce_sum, 7111, 7114, {-1}, true);
  g->Binary(ynn_binary_divide, 6183, 7114, 7112);
  g->Binary(ynn_binary_multiply, 7111, 7112, 6159);
  g->Matmul(6159, 6129, 6160, false, false);
}

// Scope: "Layer4 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(6160, 6164, 1, 2);
  g->SplitDim(6164, 6163, 1, {1,8});
  g->FuseDims(6163, 6165, 2, 2);
  g->Binary(ynn_binary_divide, 6165, 7315, 6166);
  g->Unary(ynn_unary_round, 6166, 6167);
  g->Binary(ynn_binary_max, 6167, 7225, 6168);
  g->Binary(ynn_binary_min, 6168, 7340, 6169);
  g->Binary(ynn_binary_multiply, 6169, 7315, 6170);
  g->Convert(8269, 6171);
  g->Binary(ynn_binary_multiply, 6171, 8270, 6172);
  g->Matmul(6170, 6172, 6173, false, true);
  g->Binary(ynn_binary_divide, 6173, 7243, 4);
  g->Unary(ynn_unary_round, 4, 5);
  g->Binary(ynn_binary_max, 5, 7225, 6);
  g->Binary(ynn_binary_min, 6, 7340, 7);
  g->Binary(ynn_binary_multiply, 7, 7243, 8);
}

// Scope: "Layer4 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 6067, 6068);
  g->Reduce(ynn_reduce_sum, 6068, 7103, {2}, true);
  g->ShapeProduct(6068, 7102, {2});
  g->Binary(ynn_binary_divide, 7103, 7102, 6069);
  g->Binary(ynn_binary_add, 6069, 7373, 6070);
  g->Binary(ynn_binary_pow, 6070, 7428, 6071);
  g->Binary(ynn_binary_multiply, 6067, 6071, 6072);
  g->Convert(8250, 6073);
  g->Binary(ynn_binary_multiply, 6072, 6073, 6074);
  BuildLayer4AttentionKvProjection(ctx);
  BuildLayer4AttentionCacheUpdate(ctx);
  BuildLayer4AttentionQueryProjection(ctx);
  BuildLayer4AttentionSdpa(ctx);
  BuildLayer4AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 8, 9);
  g->Reduce(ynn_reduce_sum, 9, 6175, {2}, true);
  g->ShapeProduct(9, 6174, {2});
  g->Binary(ynn_binary_divide, 6175, 6174, 10);
  g->Binary(ynn_binary_add, 10, 7373, 11);
  g->Binary(ynn_binary_pow, 11, 7428, 12);
  g->Binary(ynn_binary_multiply, 8, 12, 13);
  g->Convert(8262, 15);
  g->Binary(ynn_binary_multiply, 13, 15, 16);
  g->Binary(ynn_binary_add, 6067, 16, 17);
}

// Scope: "Layer4 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 17, 18);
  g->Reduce(ynn_reduce_sum, 18, 6179, {2}, true);
  g->ShapeProduct(18, 6178, {2});
  g->Binary(ynn_binary_divide, 6179, 6178, 19);
  g->Binary(ynn_binary_add, 19, 7373, 20);
  g->Binary(ynn_binary_pow, 20, 7428, 21);
  g->Binary(ynn_binary_multiply, 17, 21, 22);
  g->Convert(8265, 23);
  g->Binary(ynn_binary_multiply, 22, 23, 24);
  g->Binary(ynn_binary_divide, 24, 7233, 26);
  g->Unary(ynn_unary_round, 26, 27);
  g->Binary(ynn_binary_max, 27, 7225, 28);
  g->Binary(ynn_binary_min, 28, 7340, 29);
  g->Binary(ynn_binary_multiply, 29, 7233, 30);
  g->Convert(8256, 31);
  g->Binary(ynn_binary_multiply, 31, 8257, 32);
  g->Matmul(30, 32, 33, false, true);
  g->Binary(ynn_binary_divide, 33, 7491, 34);
  g->Unary(ynn_unary_round, 34, 35);
  g->Binary(ynn_binary_max, 35, 7225, 37);
  g->Binary(ynn_binary_min, 37, 7340, 38);
  g->Binary(ynn_binary_multiply, 38, 7491, 39);
  g->Convert(8254, 40);
  g->Binary(ynn_binary_multiply, 40, 8255, 41);
  g->Matmul(30, 41, 43, false, true);
  g->Binary(ynn_binary_divide, 43, 7491, 44);
  g->Unary(ynn_unary_round, 44, 45);
  g->Binary(ynn_binary_max, 45, 7225, 46);
  g->Binary(ynn_binary_min, 46, 7340, 47);
  g->Binary(ynn_binary_multiply, 47, 7491, 48);
  g->Polynomial(48, 6184, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6184, 6185);
  g->Binary(ynn_binary_add, 6185, 6183, 6180);
  g->Binary(ynn_binary_multiply, 48, 6181, 6182);
  g->Binary(ynn_binary_multiply, 6182, 6180, 49);
  g->Binary(ynn_binary_multiply, 39, 49, 50);
  g->Binary(ynn_binary_divide, 50, 7230, 51);
  g->Unary(ynn_unary_round, 51, 52);
  g->Binary(ynn_binary_max, 52, 7225, 54);
  g->Binary(ynn_binary_min, 54, 7340, 55);
  g->Binary(ynn_binary_multiply, 55, 7230, 56);
  g->Convert(8252, 57);
  g->Binary(ynn_binary_multiply, 57, 8253, 58);
  g->Matmul(56, 58, 59, false, true);
  g->Binary(ynn_binary_divide, 59, 7406, 60);
  g->Unary(ynn_unary_round, 60, 61);
  g->Binary(ynn_binary_max, 61, 7225, 62);
  g->Binary(ynn_binary_min, 62, 7340, 63);
  g->Binary(ynn_binary_multiply, 63, 7406, 65);
  g->Unary(ynn_unary_square, 65, 66);
  g->Reduce(ynn_reduce_sum, 66, 6187, {2}, true);
  g->ShapeProduct(66, 6186, {2});
  g->Binary(ynn_binary_divide, 6187, 6186, 67);
  g->Binary(ynn_binary_add, 67, 7373, 68);
  g->Binary(ynn_binary_pow, 68, 7428, 69);
  g->Binary(ynn_binary_multiply, 65, 69, 70);
  g->Convert(8263, 71);
  g->Binary(ynn_binary_multiply, 70, 71, 72);
  g->Binary(ynn_binary_add, 17, 72, 73);
}

// Scope: "Layer4 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1031, 74, {0,0,4,0}, {-1,-1,1,-1});
  g->Reshape(74, 76, {1,1,256});
  g->Binary(ynn_binary_add, 76, 8438, 77);
  g->Binary(ynn_binary_multiply, 77, 7155, 78);
  g->Binary(ynn_binary_divide, 73, 7510, 79);
  g->Unary(ynn_unary_round, 79, 80);
  g->Binary(ynn_binary_max, 80, 7225, 81);
  g->Binary(ynn_binary_min, 81, 7340, 82);
  g->Binary(ynn_binary_multiply, 82, 7510, 83);
  g->Convert(8258, 84);
  g->Binary(ynn_binary_multiply, 84, 8259, 85);
  g->Matmul(83, 85, 87, false, true);
  g->Binary(ynn_binary_divide, 87, 7164, 88);
  g->Unary(ynn_unary_round, 88, 89);
  g->Binary(ynn_binary_max, 89, 7225, 90);
  g->Binary(ynn_binary_min, 90, 7340, 91);
  g->Binary(ynn_binary_multiply, 91, 7164, 92);
  g->Polynomial(92, 6190, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6190, 6191);
  g->Binary(ynn_binary_add, 6191, 6183, 6188);
  g->Binary(ynn_binary_multiply, 92, 6181, 6189);
  g->Binary(ynn_binary_multiply, 6189, 6188, 93);
  g->Binary(ynn_binary_multiply, 93, 78, 94);
  g->Binary(ynn_binary_divide, 94, 7331, 95);
  g->Unary(ynn_unary_round, 95, 96);
  g->Binary(ynn_binary_max, 96, 7225, 98);
  g->Binary(ynn_binary_min, 98, 7340, 99);
  g->Binary(ynn_binary_multiply, 99, 7331, 100);
  g->Convert(8260, 101);
  g->Binary(ynn_binary_multiply, 101, 8261, 102);
  g->Matmul(100, 102, 103, false, true);
  g->Binary(ynn_binary_divide, 103, 7347, 104);
  g->Unary(ynn_unary_round, 104, 105);
  g->Binary(ynn_binary_max, 105, 7225, 106);
  g->Binary(ynn_binary_min, 106, 7340, 107);
  g->Binary(ynn_binary_multiply, 107, 7347, 110);
  g->Unary(ynn_unary_square, 110, 111);
  g->Reduce(ynn_reduce_sum, 111, 6193, {2}, true);
  g->ShapeProduct(111, 6192, {2});
  g->Binary(ynn_binary_divide, 6193, 6192, 112);
  g->Binary(ynn_binary_add, 112, 7373, 113);
  g->Binary(ynn_binary_pow, 113, 7428, 114);
  g->Binary(ynn_binary_multiply, 110, 114, 115);
  g->Convert(8264, 116);
  g->Binary(ynn_binary_multiply, 115, 116, 117);
  g->Binary(ynn_binary_add, 73, 117, 118);
  g->Convert(8251, 119);
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
  g->Binary(ynn_binary_divide, 128, 7390, 129);
  g->Unary(ynn_unary_round, 129, 130);
  g->Binary(ynn_binary_max, 130, 7225, 132);
  g->Binary(ynn_binary_min, 132, 7340, 133);
  g->Binary(ynn_binary_multiply, 133, 7390, 134);
  g->Convert(8293, 135);
  g->Binary(ynn_binary_multiply, 135, 8294, 136);
  g->Matmul(134, 136, 137, false, true);
  g->Binary(ynn_binary_divide, 137, 7313, 138);
  g->Unary(ynn_unary_round, 138, 139);
  g->Binary(ynn_binary_max, 139, 7225, 140);
  g->Binary(ynn_binary_min, 140, 7340, 141);
  g->Binary(ynn_binary_multiply, 141, 7313, 143);
  g->Reshape(143, 144, {1,1,1,256});
  g->Reshape(144, 145, {1,1,1,256});
  g->Unary(ynn_unary_square, 145, 146);
  g->Reduce(ynn_reduce_sum, 146, 6197, {3}, true);
  g->ShapeProduct(146, 6196, {3});
  g->Binary(ynn_binary_divide, 6197, 6196, 147);
  g->Binary(ynn_binary_add, 147, 7373, 148);
  g->Binary(ynn_binary_pow, 148, 7428, 149);
  g->Binary(ynn_binary_multiply, 145, 149, 150);
  g->Convert(8292, 151);
  g->Binary(ynn_binary_multiply, 150, 151, 152);
  g->Slice(152, 154, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(152, 155, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 155, 156);
  g->Concat({156,154}, 157, 3);
  g->Binary(ynn_binary_multiply, 152, 2044, 158);
  g->Binary(ynn_binary_multiply, 157, 3111, 159);
  g->Binary(ynn_binary_add, 158, 159, 160);
  g->Convert(8300, 161);
  g->Binary(ynn_binary_multiply, 161, 8301, 162);
  g->Matmul(134, 162, 163, false, true);
  g->Binary(ynn_binary_divide, 163, 7313, 164);
  g->Unary(ynn_unary_round, 164, 165);
  g->Binary(ynn_binary_max, 165, 7225, 166);
  g->Binary(ynn_binary_min, 166, 7340, 167);
  g->Binary(ynn_binary_multiply, 167, 7313, 168);
  g->Reshape(168, 170, {1,1,1,256});
  g->Reshape(170, 171, {1,1,1,256});
  g->Unary(ynn_unary_square, 171, 172);
  g->Reduce(ynn_reduce_sum, 172, 6204, {3}, true);
  g->ShapeProduct(172, 6203, {3});
  g->Binary(ynn_binary_divide, 6204, 6203, 173);
  g->Binary(ynn_binary_add, 173, 7373, 174);
  g->Binary(ynn_binary_pow, 174, 7428, 175);
  g->Binary(ynn_binary_multiply, 171, 175, 176);
}

// Scope: "Layer5 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(160, 177, 0.006011798977851868, 0);
  g->Append(7125, 177, 8455, 2, s2, slinky::expr(int64_t{1}));
  g->View(8455, 8485, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(8485, 179, 0.006011798977851868, 0);
  g->Quantize(176, 180, 0.047244105488061905, 0);
  g->Append(7140, 180, 8470, 2, s2, slinky::expr(int64_t{1}));
  g->View(8470, 8500, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(8500, 181, 0.047244105488061905, 0);
}

// Scope: "Layer5 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Convert(8298, 184);
  g->Binary(ynn_binary_multiply, 184, 8299, 185);
  g->Matmul(134, 185, 186, false, true);
  g->Binary(ynn_binary_divide, 186, 7460, 187);
  g->Unary(ynn_unary_round, 187, 188);
  g->Binary(ynn_binary_max, 188, 7225, 189);
  g->Binary(ynn_binary_min, 189, 7340, 190);
  g->Binary(ynn_binary_multiply, 190, 7460, 191);
  g->SplitDim(191, 192, 2, {8,256});
  g->FuseDims(192, 194, 1, 2);
  g->SplitDim(194, 193, 1, {8,1});
  g->Unary(ynn_unary_square, 193, 196);
  g->Reduce(ynn_reduce_sum, 196, 6206, {3}, true);
  g->ShapeProduct(196, 6205, {3});
  g->Binary(ynn_binary_divide, 6206, 6205, 197);
  g->Binary(ynn_binary_add, 197, 7373, 198);
  g->Binary(ynn_binary_pow, 198, 7428, 199);
  g->Binary(ynn_binary_multiply, 193, 199, 200);
  g->Convert(8297, 201);
  g->Binary(ynn_binary_multiply, 200, 201, 202);
  g->Slice(202, 203, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(202, 204, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 204, 205);
  g->Concat({205,203}, 208, 3);
  g->Binary(ynn_binary_multiply, 202, 2044, 209);
  g->Binary(ynn_binary_multiply, 208, 3111, 210);
  g->Binary(ynn_binary_add, 209, 210, 211);
}

// Scope: "Layer5 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(211, 179, 212, false, true);
  g->Mask(212, 7591, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 7591, 6210, {-1}, true);
  g->Binary(ynn_binary_subtract, 7591, 6210, 6207);
  g->Unary(ynn_unary_exp, 6207, 6208);
  g->Reduce(ynn_reduce_sum, 6208, 6211, {-1}, true);
  g->Binary(ynn_binary_divide, 6183, 6211, 6209);
  g->Binary(ynn_binary_multiply, 6208, 6209, 213);
  g->Matmul(213, 181, 214, false, false);
}

// Scope: "Layer5 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(214, 216, 1, 2);
  g->SplitDim(216, 215, 1, {1,8});
  g->FuseDims(215, 217, 2, 2);
  g->Binary(ynn_binary_divide, 217, 7241, 219);
  g->Unary(ynn_unary_round, 219, 220);
  g->Binary(ynn_binary_max, 220, 7225, 221);
  g->Binary(ynn_binary_min, 221, 7340, 222);
  g->Binary(ynn_binary_multiply, 222, 7241, 223);
  g->Convert(8295, 224);
  g->Binary(ynn_binary_multiply, 224, 8296, 225);
  g->Matmul(223, 225, 226, false, true);
  g->Binary(ynn_binary_divide, 226, 7181, 227);
  g->Unary(ynn_unary_round, 227, 228);
  g->Binary(ynn_binary_max, 228, 7225, 230);
  g->Binary(ynn_binary_min, 230, 7340, 231);
  g->Binary(ynn_binary_multiply, 231, 7181, 232);
}

// Scope: "Layer5 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 121, 122);
  g->Reduce(ynn_reduce_sum, 122, 6195, {2}, true);
  g->ShapeProduct(122, 6194, {2});
  g->Binary(ynn_binary_divide, 6195, 6194, 123);
  g->Binary(ynn_binary_add, 123, 7373, 124);
  g->Binary(ynn_binary_pow, 124, 7428, 125);
  g->Binary(ynn_binary_multiply, 121, 125, 126);
  g->Convert(8276, 127);
  g->Binary(ynn_binary_multiply, 126, 127, 128);
  BuildLayer5AttentionKvProjection(ctx);
  BuildLayer5AttentionCacheUpdate(ctx);
  BuildLayer5AttentionQueryProjection(ctx);
  BuildLayer5AttentionSdpa(ctx);
  BuildLayer5AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 232, 233);
  g->Reduce(ynn_reduce_sum, 233, 6213, {2}, true);
  g->ShapeProduct(233, 6212, {2});
  g->Binary(ynn_binary_divide, 6213, 6212, 234);
  g->Binary(ynn_binary_add, 234, 7373, 235);
  g->Binary(ynn_binary_pow, 235, 7428, 236);
  g->Binary(ynn_binary_multiply, 232, 236, 237);
  g->Convert(8288, 238);
  g->Binary(ynn_binary_multiply, 237, 238, 239);
  g->Binary(ynn_binary_add, 121, 239, 241);
}

// Scope: "Layer5 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 241, 242);
  g->Reduce(ynn_reduce_sum, 242, 6215, {2}, true);
  g->ShapeProduct(242, 6214, {2});
  g->Binary(ynn_binary_divide, 6215, 6214, 243);
  g->Binary(ynn_binary_add, 243, 7373, 244);
  g->Binary(ynn_binary_pow, 244, 7428, 245);
  g->Binary(ynn_binary_multiply, 241, 245, 246);
  g->Convert(8291, 247);
  g->Binary(ynn_binary_multiply, 246, 247, 248);
  g->Binary(ynn_binary_divide, 248, 7272, 249);
  g->Unary(ynn_unary_round, 249, 250);
  g->Binary(ynn_binary_max, 250, 7225, 252);
  g->Binary(ynn_binary_min, 252, 7340, 253);
  g->Binary(ynn_binary_multiply, 253, 7272, 254);
  g->Convert(8282, 255);
  g->Binary(ynn_binary_multiply, 255, 8283, 256);
  g->Matmul(254, 256, 257, false, true);
  g->Binary(ynn_binary_divide, 257, 7224, 258);
  g->Unary(ynn_unary_round, 258, 259);
  g->Binary(ynn_binary_max, 259, 7225, 260);
  g->Binary(ynn_binary_min, 260, 7340, 261);
  g->Binary(ynn_binary_multiply, 261, 7224, 263);
  g->Convert(8280, 264);
  g->Binary(ynn_binary_multiply, 264, 8281, 265);
  g->Matmul(254, 265, 266, false, true);
  g->Binary(ynn_binary_divide, 266, 7224, 267);
  g->Unary(ynn_unary_round, 267, 269);
  g->Binary(ynn_binary_max, 269, 7225, 270);
  g->Binary(ynn_binary_min, 270, 7340, 271);
  g->Binary(ynn_binary_multiply, 271, 7224, 272);
  g->Polynomial(272, 6218, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6218, 6219);
  g->Binary(ynn_binary_add, 6219, 6183, 6216);
  g->Binary(ynn_binary_multiply, 272, 6181, 6217);
  g->Binary(ynn_binary_multiply, 6217, 6216, 273);
  g->Binary(ynn_binary_multiply, 263, 273, 274);
  g->Binary(ynn_binary_divide, 274, 7335, 275);
  g->Unary(ynn_unary_round, 275, 276);
  g->Binary(ynn_binary_max, 276, 7225, 277);
  g->Binary(ynn_binary_min, 277, 7340, 278);
  g->Binary(ynn_binary_multiply, 278, 7335, 280);
  g->Convert(8278, 281);
  g->Binary(ynn_binary_multiply, 281, 8279, 282);
  g->Matmul(280, 282, 283, false, true);
  g->Binary(ynn_binary_divide, 283, 7276, 284);
  g->Unary(ynn_unary_round, 284, 285);
  g->Binary(ynn_binary_max, 285, 7225, 286);
  g->Binary(ynn_binary_min, 286, 7340, 287);
  g->Binary(ynn_binary_multiply, 287, 7276, 288);
  g->Unary(ynn_unary_square, 288, 289);
  g->Reduce(ynn_reduce_sum, 289, 6221, {2}, true);
  g->ShapeProduct(289, 6220, {2});
  g->Binary(ynn_binary_divide, 6221, 6220, 291);
  g->Binary(ynn_binary_add, 291, 7373, 292);
  g->Binary(ynn_binary_pow, 292, 7428, 293);
  g->Binary(ynn_binary_multiply, 288, 293, 294);
  g->Convert(8289, 295);
  g->Binary(ynn_binary_multiply, 294, 295, 296);
  g->Binary(ynn_binary_add, 241, 296, 297);
}

// Scope: "Layer5 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1031, 298, {0,0,5,0}, {-1,-1,1,-1});
  g->Reshape(298, 299, {1,1,256});
  g->Binary(ynn_binary_add, 299, 8439, 300);
  g->Binary(ynn_binary_multiply, 300, 7155, 302);
  g->Binary(ynn_binary_divide, 297, 7360, 303);
  g->Unary(ynn_unary_round, 303, 304);
  g->Binary(ynn_binary_max, 304, 7225, 305);
  g->Binary(ynn_binary_min, 305, 7340, 306);
  g->Binary(ynn_binary_multiply, 306, 7360, 307);
  g->Convert(8284, 308);
  g->Binary(ynn_binary_multiply, 308, 8285, 309);
  g->Matmul(307, 309, 310, false, true);
  g->Binary(ynn_binary_divide, 310, 7403, 311);
  g->Unary(ynn_unary_round, 311, 314);
  g->Binary(ynn_binary_max, 314, 7225, 315);
  g->Binary(ynn_binary_min, 315, 7340, 316);
  g->Binary(ynn_binary_multiply, 316, 7403, 317);
  g->Polynomial(317, 6224, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6224, 6225);
  g->Binary(ynn_binary_add, 6225, 6183, 6222);
  g->Binary(ynn_binary_multiply, 317, 6181, 6223);
  g->Binary(ynn_binary_multiply, 6223, 6222, 318);
  g->Binary(ynn_binary_multiply, 318, 302, 319);
  g->Binary(ynn_binary_divide, 319, 7443, 320);
  g->Unary(ynn_unary_round, 320, 321);
  g->Binary(ynn_binary_max, 321, 7225, 322);
  g->Binary(ynn_binary_min, 322, 7340, 323);
  g->Binary(ynn_binary_multiply, 323, 7443, 325);
  g->Convert(8286, 326);
  g->Binary(ynn_binary_multiply, 326, 8287, 327);
  g->Matmul(325, 327, 328, false, true);
  g->Binary(ynn_binary_divide, 328, 7237, 329);
  g->Unary(ynn_unary_round, 329, 330);
  g->Binary(ynn_binary_max, 330, 7225, 331);
  g->Binary(ynn_binary_min, 331, 7340, 332);
  g->Binary(ynn_binary_multiply, 332, 7237, 333);
  g->Unary(ynn_unary_square, 333, 334);
  g->Reduce(ynn_reduce_sum, 334, 6227, {2}, true);
  g->ShapeProduct(334, 6226, {2});
  g->Binary(ynn_binary_divide, 6227, 6226, 336);
  g->Binary(ynn_binary_add, 336, 7373, 337);
  g->Binary(ynn_binary_pow, 337, 7428, 338);
  g->Binary(ynn_binary_multiply, 333, 338, 339);
  g->Convert(8290, 340);
  g->Binary(ynn_binary_multiply, 339, 340, 341);
  g->Binary(ynn_binary_add, 297, 341, 342);
  g->Convert(8277, 343);
  g->Binary(ynn_binary_multiply, 342, 343, 344);
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
  g->Binary(ynn_binary_divide, 352, 7362, 353);
  g->Unary(ynn_unary_round, 353, 354);
  g->Binary(ynn_binary_max, 354, 7225, 355);
  g->Binary(ynn_binary_min, 355, 7340, 356);
  g->Binary(ynn_binary_multiply, 356, 7362, 358);
  g->Convert(8319, 359);
  g->Binary(ynn_binary_multiply, 359, 8320, 360);
  g->Matmul(358, 360, 361, false, true);
  g->Binary(ynn_binary_divide, 361, 7193, 362);
  g->Unary(ynn_unary_round, 362, 363);
  g->Binary(ynn_binary_max, 363, 7225, 364);
  g->Binary(ynn_binary_min, 364, 7340, 365);
  g->Binary(ynn_binary_multiply, 365, 7193, 366);
  g->Reshape(366, 367, {1,1,1,256});
  g->Reshape(367, 369, {1,1,1,256});
  g->Unary(ynn_unary_square, 369, 370);
  g->Reduce(ynn_reduce_sum, 370, 6233, {3}, true);
  g->ShapeProduct(370, 6232, {3});
  g->Binary(ynn_binary_divide, 6233, 6232, 371);
  g->Binary(ynn_binary_add, 371, 7373, 372);
  g->Binary(ynn_binary_pow, 372, 7428, 373);
  g->Binary(ynn_binary_multiply, 369, 373, 374);
  g->Convert(8318, 375);
  g->Binary(ynn_binary_multiply, 374, 375, 376);
  g->Slice(376, 377, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(376, 378, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 378, 380);
  g->Concat({380,377}, 381, 3);
  g->Binary(ynn_binary_multiply, 376, 2044, 382);
  g->Binary(ynn_binary_multiply, 381, 3111, 383);
  g->Binary(ynn_binary_add, 382, 383, 384);
  g->Convert(8326, 386);
  g->Binary(ynn_binary_multiply, 386, 8327, 387);
  g->Matmul(358, 387, 388, false, true);
  g->Binary(ynn_binary_divide, 388, 7193, 389);
  g->Unary(ynn_unary_round, 389, 390);
  g->Binary(ynn_binary_max, 390, 7225, 391);
  g->Binary(ynn_binary_min, 391, 7340, 392);
  g->Binary(ynn_binary_multiply, 392, 7193, 393);
  g->Reshape(393, 394, {1,1,1,256});
  g->Reshape(394, 395, {1,1,1,256});
  g->Unary(ynn_unary_square, 395, 397);
  g->Reduce(ynn_reduce_sum, 397, 6235, {3}, true);
  g->ShapeProduct(397, 6234, {3});
  g->Binary(ynn_binary_divide, 6235, 6234, 398);
  g->Binary(ynn_binary_add, 398, 7373, 399);
  g->Binary(ynn_binary_pow, 399, 7428, 400);
  g->Binary(ynn_binary_multiply, 395, 400, 401);
}

// Scope: "Layer6 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(384, 402, 0.0057707298547029495, 0);
  g->Append(7126, 402, 8456, 2, s2, slinky::expr(int64_t{1}));
  g->View(8456, 8486, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(8486, 403, 0.0057707298547029495, 0);
  g->Quantize(401, 404, 0.047244105488061905, 0);
  g->Append(7141, 404, 8471, 2, s2, slinky::expr(int64_t{1}));
  g->View(8471, 8501, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(8501, 406, 0.047244105488061905, 0);
}

// Scope: "Layer6 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Convert(8324, 407);
  g->Binary(ynn_binary_multiply, 407, 8325, 408);
  g->Matmul(358, 408, 411, false, true);
  g->Binary(ynn_binary_divide, 411, 7216, 412);
  g->Unary(ynn_unary_round, 412, 413);
  g->Binary(ynn_binary_max, 413, 7225, 414);
  g->Binary(ynn_binary_min, 414, 7340, 415);
  g->Binary(ynn_binary_multiply, 415, 7216, 416);
  g->SplitDim(416, 417, 2, {8,256});
  g->FuseDims(417, 419, 1, 2);
  g->SplitDim(419, 418, 1, {8,1});
  g->Unary(ynn_unary_square, 418, 420);
  g->Reduce(ynn_reduce_sum, 420, 6237, {3}, true);
  g->ShapeProduct(420, 6236, {3});
  g->Binary(ynn_binary_divide, 6237, 6236, 421);
  g->Binary(ynn_binary_add, 421, 7373, 423);
  g->Binary(ynn_binary_pow, 423, 7428, 424);
  g->Binary(ynn_binary_multiply, 418, 424, 425);
  g->Convert(8323, 426);
  g->Binary(ynn_binary_multiply, 425, 426, 427);
  g->Slice(427, 428, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(427, 429, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 429, 430);
  g->Concat({430,428}, 431, 3);
  g->Binary(ynn_binary_multiply, 427, 2044, 432);
  g->Binary(ynn_binary_multiply, 431, 3111, 434);
  g->Binary(ynn_binary_add, 432, 434, 435);
}

// Scope: "Layer6 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(435, 403, 436, false, true);
  g->Mask(436, 7592, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 7592, 6243, {-1}, true);
  g->Binary(ynn_binary_subtract, 7592, 6243, 6240);
  g->Unary(ynn_unary_exp, 6240, 6241);
  g->Reduce(ynn_reduce_sum, 6241, 6244, {-1}, true);
  g->Binary(ynn_binary_divide, 6183, 6244, 6242);
  g->Binary(ynn_binary_multiply, 6241, 6242, 437);
  g->Matmul(437, 406, 438, false, false);
}

// Scope: "Layer6 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(438, 440, 1, 2);
  g->SplitDim(440, 439, 1, {1,8});
  g->FuseDims(439, 441, 2, 2);
  g->Binary(ynn_binary_divide, 441, 7196, 442);
  g->Unary(ynn_unary_round, 442, 443);
  g->Binary(ynn_binary_max, 443, 7225, 445);
  g->Binary(ynn_binary_min, 445, 7340, 446);
  g->Binary(ynn_binary_multiply, 446, 7196, 447);
  g->Convert(8321, 448);
  g->Binary(ynn_binary_multiply, 448, 8322, 449);
  g->Matmul(447, 449, 450, false, true);
  g->Binary(ynn_binary_divide, 450, 7487, 451);
  g->Unary(ynn_unary_round, 451, 452);
  g->Binary(ynn_binary_max, 452, 7225, 453);
  g->Binary(ynn_binary_min, 453, 7340, 454);
  g->Binary(ynn_binary_multiply, 454, 7487, 456);
}

// Scope: "Layer6 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 344, 345);
  g->Reduce(ynn_reduce_sum, 345, 6229, {2}, true);
  g->ShapeProduct(345, 6228, {2});
  g->Binary(ynn_binary_divide, 6229, 6228, 347);
  g->Binary(ynn_binary_add, 347, 7373, 348);
  g->Binary(ynn_binary_pow, 348, 7428, 349);
  g->Binary(ynn_binary_multiply, 344, 349, 350);
  g->Convert(8302, 351);
  g->Binary(ynn_binary_multiply, 350, 351, 352);
  BuildLayer6AttentionKvProjection(ctx);
  BuildLayer6AttentionCacheUpdate(ctx);
  BuildLayer6AttentionQueryProjection(ctx);
  BuildLayer6AttentionSdpa(ctx);
  BuildLayer6AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 456, 457);
  g->Reduce(ynn_reduce_sum, 457, 6246, {2}, true);
  g->ShapeProduct(457, 6245, {2});
  g->Binary(ynn_binary_divide, 6246, 6245, 458);
  g->Binary(ynn_binary_add, 458, 7373, 459);
  g->Binary(ynn_binary_pow, 459, 7428, 460);
  g->Binary(ynn_binary_multiply, 456, 460, 461);
  g->Convert(8314, 462);
  g->Binary(ynn_binary_multiply, 461, 462, 463);
  g->Binary(ynn_binary_add, 344, 463, 464);
}

// Scope: "Layer6 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 464, 465);
  g->Reduce(ynn_reduce_sum, 465, 6248, {2}, true);
  g->ShapeProduct(465, 6247, {2});
  g->Binary(ynn_binary_divide, 6248, 6247, 467);
  g->Binary(ynn_binary_add, 467, 7373, 468);
  g->Binary(ynn_binary_pow, 468, 7428, 469);
  g->Binary(ynn_binary_multiply, 464, 469, 470);
  g->Convert(8317, 471);
  g->Binary(ynn_binary_multiply, 470, 471, 472);
  g->Binary(ynn_binary_divide, 472, 7302, 473);
  g->Unary(ynn_unary_round, 473, 474);
  g->Binary(ynn_binary_max, 474, 7225, 475);
  g->Binary(ynn_binary_min, 475, 7340, 476);
  g->Binary(ynn_binary_multiply, 476, 7302, 478);
  g->Convert(8308, 479);
  g->Binary(ynn_binary_multiply, 479, 8309, 480);
  g->Matmul(478, 480, 481, false, true);
  g->Binary(ynn_binary_divide, 481, 7194, 482);
  g->Unary(ynn_unary_round, 482, 483);
  g->Binary(ynn_binary_max, 483, 7225, 484);
  g->Binary(ynn_binary_min, 484, 7340, 485);
  g->Binary(ynn_binary_multiply, 485, 7194, 486);
  g->Convert(8306, 488);
  g->Binary(ynn_binary_multiply, 488, 8307, 489);
  g->Matmul(478, 489, 490, false, true);
  g->Binary(ynn_binary_divide, 490, 7194, 491);
  g->Unary(ynn_unary_round, 491, 492);
  g->Binary(ynn_binary_max, 492, 7225, 493);
  g->Binary(ynn_binary_min, 493, 7340, 495);
  g->Binary(ynn_binary_multiply, 495, 7194, 496);
  g->Polynomial(496, 6251, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6251, 6252);
  g->Binary(ynn_binary_add, 6252, 6183, 6249);
  g->Binary(ynn_binary_multiply, 496, 6181, 6250);
  g->Binary(ynn_binary_multiply, 6250, 6249, 497);
  g->Binary(ynn_binary_multiply, 486, 497, 498);
  g->Binary(ynn_binary_divide, 498, 7164, 499);
  g->Unary(ynn_unary_round, 499, 500);
  g->Binary(ynn_binary_max, 500, 7225, 501);
  g->Binary(ynn_binary_min, 501, 7340, 502);
  g->Binary(ynn_binary_multiply, 502, 7164, 503);
  g->Convert(8304, 504);
  g->Binary(ynn_binary_multiply, 504, 8305, 506);
  g->Matmul(503, 506, 507, false, true);
  g->Binary(ynn_binary_divide, 507, 7293, 508);
  g->Unary(ynn_unary_round, 508, 509);
  g->Binary(ynn_binary_max, 509, 7225, 510);
  g->Binary(ynn_binary_min, 510, 7340, 511);
  g->Binary(ynn_binary_multiply, 511, 7293, 512);
  g->Unary(ynn_unary_square, 512, 513);
  g->Reduce(ynn_reduce_sum, 513, 6254, {2}, true);
  g->ShapeProduct(513, 6253, {2});
  g->Binary(ynn_binary_divide, 6254, 6253, 514);
  g->Binary(ynn_binary_add, 514, 7373, 515);
  g->Binary(ynn_binary_pow, 515, 7428, 518);
  g->Binary(ynn_binary_multiply, 512, 518, 519);
  g->Convert(8315, 520);
  g->Binary(ynn_binary_multiply, 519, 520, 521);
  g->Binary(ynn_binary_add, 464, 521, 522);
}

// Scope: "Layer6 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1031, 523, {0,0,6,0}, {-1,-1,1,-1});
  g->Reshape(523, 524, {1,1,256});
  g->Binary(ynn_binary_add, 524, 8440, 525);
  g->Binary(ynn_binary_multiply, 525, 7155, 526);
  g->Binary(ynn_binary_divide, 522, 7388, 527);
  g->Unary(ynn_unary_round, 527, 529);
  g->Binary(ynn_binary_max, 529, 7225, 530);
  g->Binary(ynn_binary_min, 530, 7340, 531);
  g->Binary(ynn_binary_multiply, 531, 7388, 532);
  g->Convert(8310, 533);
  g->Binary(ynn_binary_multiply, 533, 8311, 534);
  g->Matmul(532, 534, 535, false, true);
  g->Binary(ynn_binary_divide, 535, 7182, 536);
  g->Unary(ynn_unary_round, 536, 537);
  g->Binary(ynn_binary_max, 537, 7225, 538);
  g->Binary(ynn_binary_min, 538, 7340, 540);
  g->Binary(ynn_binary_multiply, 540, 7182, 541);
  g->Polynomial(541, 6259, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6259, 6260);
  g->Binary(ynn_binary_add, 6260, 6183, 6257);
  g->Binary(ynn_binary_multiply, 541, 6181, 6258);
  g->Binary(ynn_binary_multiply, 6258, 6257, 542);
  g->Binary(ynn_binary_multiply, 542, 526, 543);
  g->Binary(ynn_binary_divide, 543, 7475, 544);
  g->Unary(ynn_unary_round, 544, 545);
  g->Binary(ynn_binary_max, 545, 7225, 546);
  g->Binary(ynn_binary_min, 546, 7340, 547);
  g->Binary(ynn_binary_multiply, 547, 7475, 548);
  g->Convert(8312, 549);
  g->Binary(ynn_binary_multiply, 549, 8313, 551);
  g->Matmul(548, 551, 552, false, true);
  g->Binary(ynn_binary_divide, 552, 7458, 553);
  g->Unary(ynn_unary_round, 553, 554);
  g->Binary(ynn_binary_max, 554, 7225, 555);
  g->Binary(ynn_binary_min, 555, 7340, 556);
  g->Binary(ynn_binary_multiply, 556, 7458, 557);
  g->Unary(ynn_unary_square, 557, 558);
  g->Reduce(ynn_reduce_sum, 558, 6262, {2}, true);
  g->ShapeProduct(558, 6261, {2});
  g->Binary(ynn_binary_divide, 6262, 6261, 559);
  g->Binary(ynn_binary_add, 559, 7373, 560);
  g->Binary(ynn_binary_pow, 560, 7428, 562);
  g->Binary(ynn_binary_multiply, 557, 562, 563);
  g->Convert(8316, 564);
  g->Binary(ynn_binary_multiply, 563, 564, 565);
  g->Binary(ynn_binary_add, 522, 565, 566);
  g->Convert(8303, 567);
  g->Binary(ynn_binary_multiply, 566, 567, 568);
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
  g->Binary(ynn_binary_divide, 576, 7324, 577);
  g->Unary(ynn_unary_round, 577, 578);
  g->Binary(ynn_binary_max, 578, 7225, 579);
  g->Binary(ynn_binary_min, 579, 7340, 580);
  g->Binary(ynn_binary_multiply, 580, 7324, 581);
  g->Convert(8345, 582);
  g->Binary(ynn_binary_multiply, 582, 8346, 584);
  g->Matmul(581, 584, 585, false, true);
  g->Binary(ynn_binary_divide, 585, 7549, 586);
  g->Unary(ynn_unary_round, 586, 587);
  g->Binary(ynn_binary_max, 587, 7225, 588);
  g->Binary(ynn_binary_min, 588, 7340, 589);
  g->Binary(ynn_binary_multiply, 589, 7549, 590);
  g->Reshape(590, 591, {1,1,1,256});
  g->Reshape(591, 592, {1,1,1,256});
  g->Unary(ynn_unary_square, 592, 593);
  g->Reduce(ynn_reduce_sum, 593, 6266, {3}, true);
  g->ShapeProduct(593, 6265, {3});
  g->Binary(ynn_binary_divide, 6266, 6265, 595);
  g->Binary(ynn_binary_add, 595, 7373, 596);
  g->Binary(ynn_binary_pow, 596, 7428, 597);
  g->Binary(ynn_binary_multiply, 592, 597, 598);
  g->Convert(8344, 599);
  g->Binary(ynn_binary_multiply, 598, 599, 600);
  g->Slice(600, 601, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(600, 602, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 602, 603);
  g->Concat({603,601}, 604, 3);
  g->Binary(ynn_binary_multiply, 600, 2044, 606);
  g->Binary(ynn_binary_multiply, 604, 3111, 607);
  g->Binary(ynn_binary_add, 606, 607, 608);
  g->Convert(8352, 609);
  g->Binary(ynn_binary_multiply, 609, 8353, 610);
  g->Matmul(581, 610, 612, false, true);
  g->Binary(ynn_binary_divide, 612, 7549, 613);
  g->Unary(ynn_unary_round, 613, 614);
  g->Binary(ynn_binary_max, 614, 7225, 615);
  g->Binary(ynn_binary_min, 615, 7340, 616);
  g->Binary(ynn_binary_multiply, 616, 7549, 617);
  g->Reshape(617, 618, {1,1,1,256});
  g->Reshape(618, 619, {1,1,1,256});
  g->Unary(ynn_unary_square, 619, 620);
  g->Reduce(ynn_reduce_sum, 620, 6268, {3}, true);
  g->ShapeProduct(620, 6267, {3});
  g->Binary(ynn_binary_divide, 6268, 6267, 621);
  g->Binary(ynn_binary_add, 621, 7373, 624);
  g->Binary(ynn_binary_pow, 624, 7428, 625);
  g->Binary(ynn_binary_multiply, 619, 625, 626);
}

// Scope: "Layer7 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(608, 627, 0.005869260523468256, 0);
  g->Append(7127, 627, 8457, 2, s2, slinky::expr(int64_t{1}));
  g->View(8457, 8487, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(8487, 628, 0.005869260523468256, 0);
  g->Quantize(626, 629, 0.047244105488061905, 0);
  g->Append(7142, 629, 8472, 2, s2, slinky::expr(int64_t{1}));
  g->View(8472, 8502, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(8502, 630, 0.047244105488061905, 0);
}

// Scope: "Layer7 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Convert(8350, 631);
  g->Binary(ynn_binary_multiply, 631, 8351, 632);
  g->Matmul(581, 632, 633, false, true);
  g->Binary(ynn_binary_divide, 633, 7445, 634);
  g->Unary(ynn_unary_round, 634, 635);
  g->Binary(ynn_binary_max, 635, 7225, 636);
  g->Binary(ynn_binary_min, 636, 7340, 637);
  g->Binary(ynn_binary_multiply, 637, 7445, 638);
  g->SplitDim(638, 639, 2, {8,256});
  g->FuseDims(639, 641, 1, 2);
  g->SplitDim(641, 640, 1, {8,1});
  g->Unary(ynn_unary_square, 640, 642);
  g->Reduce(ynn_reduce_sum, 642, 6270, {3}, true);
  g->ShapeProduct(642, 6269, {3});
  g->Binary(ynn_binary_divide, 6270, 6269, 643);
  g->Binary(ynn_binary_add, 643, 7373, 644);
  g->Binary(ynn_binary_pow, 644, 7428, 645);
  g->Binary(ynn_binary_multiply, 640, 645, 646);
  g->Convert(8349, 647);
  g->Binary(ynn_binary_multiply, 646, 647, 648);
  g->Slice(648, 649, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(648, 650, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 650, 651);
  g->Concat({651,649}, 652, 3);
  g->Binary(ynn_binary_multiply, 648, 2044, 653);
  g->Binary(ynn_binary_multiply, 652, 3111, 654);
  g->Binary(ynn_binary_add, 653, 654, 655);
}

// Scope: "Layer7 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(655, 628, 656, false, true);
  g->Mask(656, 7593, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 7593, 6274, {-1}, true);
  g->Binary(ynn_binary_subtract, 7593, 6274, 6271);
  g->Unary(ynn_unary_exp, 6271, 6272);
  g->Reduce(ynn_reduce_sum, 6272, 6275, {-1}, true);
  g->Binary(ynn_binary_divide, 6183, 6275, 6273);
  g->Binary(ynn_binary_multiply, 6272, 6273, 657);
  g->Matmul(657, 630, 658, false, false);
}

// Scope: "Layer7 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(658, 660, 1, 2);
  g->SplitDim(660, 659, 1, {1,8});
  g->FuseDims(659, 661, 2, 2);
  g->Binary(ynn_binary_divide, 661, 7203, 662);
  g->Unary(ynn_unary_round, 662, 663);
  g->Binary(ynn_binary_max, 663, 7225, 664);
  g->Binary(ynn_binary_min, 664, 7340, 665);
  g->Binary(ynn_binary_multiply, 665, 7203, 666);
  g->Convert(8347, 667);
  g->Binary(ynn_binary_multiply, 667, 8348, 668);
  g->Matmul(666, 668, 669, false, true);
  g->Binary(ynn_binary_divide, 669, 7359, 670);
  g->Unary(ynn_unary_round, 670, 671);
  g->Binary(ynn_binary_max, 671, 7225, 672);
  g->Binary(ynn_binary_min, 672, 7340, 673);
  g->Binary(ynn_binary_multiply, 673, 7359, 674);
}

// Scope: "Layer7 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 568, 569);
  g->Reduce(ynn_reduce_sum, 569, 6264, {2}, true);
  g->ShapeProduct(569, 6263, {2});
  g->Binary(ynn_binary_divide, 6264, 6263, 570);
  g->Binary(ynn_binary_add, 570, 7373, 571);
  g->Binary(ynn_binary_pow, 571, 7428, 573);
  g->Binary(ynn_binary_multiply, 568, 573, 574);
  g->Convert(8328, 575);
  g->Binary(ynn_binary_multiply, 574, 575, 576);
  BuildLayer7AttentionKvProjection(ctx);
  BuildLayer7AttentionCacheUpdate(ctx);
  BuildLayer7AttentionQueryProjection(ctx);
  BuildLayer7AttentionSdpa(ctx);
  BuildLayer7AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 674, 675);
  g->Reduce(ynn_reduce_sum, 675, 6277, {2}, true);
  g->ShapeProduct(675, 6276, {2});
  g->Binary(ynn_binary_divide, 6277, 6276, 677);
  g->Binary(ynn_binary_add, 677, 7373, 678);
  g->Binary(ynn_binary_pow, 678, 7428, 679);
  g->Binary(ynn_binary_multiply, 674, 679, 680);
  g->Convert(8340, 681);
  g->Binary(ynn_binary_multiply, 680, 681, 682);
  g->Binary(ynn_binary_add, 568, 682, 683);
}

// Scope: "Layer7 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 683, 684);
  g->Reduce(ynn_reduce_sum, 684, 6279, {2}, true);
  g->ShapeProduct(684, 6278, {2});
  g->Binary(ynn_binary_divide, 6279, 6278, 685);
  g->Binary(ynn_binary_add, 685, 7373, 686);
  g->Binary(ynn_binary_pow, 686, 7428, 688);
  g->Binary(ynn_binary_multiply, 683, 688, 689);
  g->Convert(8343, 690);
  g->Binary(ynn_binary_multiply, 689, 690, 691);
  g->Binary(ynn_binary_divide, 691, 7180, 692);
  g->Unary(ynn_unary_round, 692, 693);
  g->Binary(ynn_binary_max, 693, 7225, 694);
  g->Binary(ynn_binary_min, 694, 7340, 695);
  g->Binary(ynn_binary_multiply, 695, 7180, 696);
  g->Convert(8334, 697);
  g->Binary(ynn_binary_multiply, 697, 8335, 699);
  g->Matmul(696, 699, 700, false, true);
  g->Binary(ynn_binary_divide, 700, 7550, 701);
  g->Unary(ynn_unary_round, 701, 702);
  g->Binary(ynn_binary_max, 702, 7225, 703);
  g->Binary(ynn_binary_min, 703, 7340, 704);
  g->Binary(ynn_binary_multiply, 704, 7550, 705);
  g->Convert(8332, 707);
  g->Binary(ynn_binary_multiply, 707, 8333, 708);
  g->Matmul(696, 708, 709, false, true);
  g->Binary(ynn_binary_divide, 709, 7550, 710);
  g->Unary(ynn_unary_round, 710, 711);
  g->Binary(ynn_binary_max, 711, 7225, 712);
  g->Binary(ynn_binary_min, 712, 7340, 713);
  g->Binary(ynn_binary_multiply, 713, 7550, 714);
  g->Polynomial(714, 6282, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6282, 6283);
  g->Binary(ynn_binary_add, 6283, 6183, 6280);
  g->Binary(ynn_binary_multiply, 714, 6181, 6281);
  g->Binary(ynn_binary_multiply, 6281, 6280, 717);
  g->Binary(ynn_binary_multiply, 705, 717, 718);
  g->Binary(ynn_binary_divide, 718, 7236, 719);
  g->Unary(ynn_unary_round, 719, 720);
  g->Binary(ynn_binary_max, 720, 7225, 721);
  g->Binary(ynn_binary_min, 721, 7340, 722);
  g->Binary(ynn_binary_multiply, 722, 7236, 723);
  g->Convert(8330, 724);
  g->Binary(ynn_binary_multiply, 724, 8331, 725);
  g->Matmul(723, 725, 726, false, true);
  g->Binary(ynn_binary_divide, 726, 7398, 728);
  g->Unary(ynn_unary_round, 728, 729);
  g->Binary(ynn_binary_max, 729, 7225, 730);
  g->Binary(ynn_binary_min, 730, 7340, 731);
  g->Binary(ynn_binary_multiply, 731, 7398, 732);
  g->Unary(ynn_unary_square, 732, 733);
  g->Reduce(ynn_reduce_sum, 733, 6285, {2}, true);
  g->ShapeProduct(733, 6284, {2});
  g->Binary(ynn_binary_divide, 6285, 6284, 734);
  g->Binary(ynn_binary_add, 734, 7373, 735);
  g->Binary(ynn_binary_pow, 735, 7428, 736);
  g->Binary(ynn_binary_multiply, 732, 736, 737);
  g->Convert(8341, 739);
  g->Binary(ynn_binary_multiply, 737, 739, 740);
  g->Binary(ynn_binary_add, 683, 740, 741);
}

// Scope: "Layer7 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1031, 742, {0,0,7,0}, {-1,-1,1,-1});
  g->Reshape(742, 743, {1,1,256});
  g->Binary(ynn_binary_add, 743, 8441, 744);
  g->Binary(ynn_binary_multiply, 744, 7155, 745);
  g->Binary(ynn_binary_divide, 741, 7174, 746);
  g->Unary(ynn_unary_round, 746, 747);
  g->Binary(ynn_binary_max, 747, 7225, 748);
  g->Binary(ynn_binary_min, 748, 7340, 750);
  g->Binary(ynn_binary_multiply, 750, 7174, 751);
  g->Convert(8336, 752);
  g->Binary(ynn_binary_multiply, 752, 8337, 753);
  g->Matmul(751, 753, 754, false, true);
  g->Binary(ynn_binary_divide, 754, 7189, 755);
  g->Unary(ynn_unary_round, 755, 756);
  g->Binary(ynn_binary_max, 756, 7225, 757);
  g->Binary(ynn_binary_min, 757, 7340, 758);
  g->Binary(ynn_binary_multiply, 758, 7189, 759);
  g->Polynomial(759, 6292, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6292, 6293);
  g->Binary(ynn_binary_add, 6293, 6183, 6290);
  g->Binary(ynn_binary_multiply, 759, 6181, 6291);
  g->Binary(ynn_binary_multiply, 6291, 6290, 761);
  g->Binary(ynn_binary_multiply, 761, 745, 762);
  g->Binary(ynn_binary_divide, 762, 7453, 763);
  g->Unary(ynn_unary_round, 763, 764);
  g->Binary(ynn_binary_max, 764, 7225, 765);
  g->Binary(ynn_binary_min, 765, 7340, 766);
  g->Binary(ynn_binary_multiply, 766, 7453, 767);
  g->Convert(8338, 768);
  g->Binary(ynn_binary_multiply, 768, 8339, 769);
  g->Matmul(767, 769, 770, false, true);
  g->Binary(ynn_binary_divide, 770, 7227, 772);
  g->Unary(ynn_unary_round, 772, 773);
  g->Binary(ynn_binary_max, 773, 7225, 774);
  g->Binary(ynn_binary_min, 774, 7340, 775);
  g->Binary(ynn_binary_multiply, 775, 7227, 776);
  g->Unary(ynn_unary_square, 776, 777);
  g->Reduce(ynn_reduce_sum, 777, 6295, {2}, true);
  g->ShapeProduct(777, 6294, {2});
  g->Binary(ynn_binary_divide, 6295, 6294, 778);
  g->Binary(ynn_binary_add, 778, 7373, 779);
  g->Binary(ynn_binary_pow, 779, 7428, 780);
  g->Binary(ynn_binary_multiply, 776, 780, 781);
  g->Convert(8342, 783);
  g->Binary(ynn_binary_multiply, 781, 783, 784);
  g->Binary(ynn_binary_add, 741, 784, 785);
  g->Convert(8329, 786);
  g->Binary(ynn_binary_multiply, 785, 786, 787);
}

// Scope: "Layer7"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7(Context& ctx) {
  BuildLayer7Attention(ctx);
  BuildLayer7Mlp(ctx);
  BuildLayer7PerLayerEmbedding(ctx);
}

}  // namespace BuildGemma4DecodeSource
