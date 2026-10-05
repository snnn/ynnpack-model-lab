// Generated YNNPACK builder; do not edit.
#include "gemma4_prefill_builder.h"

namespace BuildGemma4PrefillSource {

// Scope: "Layer1 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(579, 590, 0.4842597544193268, 0);
  g->Transpose(3052, 2049, {1,0});
  g->Binary(ynn_binary_multiply, 2046, 2048, 2044);
  g->Dot(590, 2049, YNN_INVALID_VALUE_ID, 2043, 1);
  g->DequantizeTensor(2043, YNN_INVALID_VALUE_ID, 2044, 2045);
  g->QuantizeTensor(2045, 2971, 2047, 601);
  g->Dequantize(601, 612, 0.41535434126853943, 0);
  g->Reshape(612, 622, {1,0,1,256});
  g->Transpose(622, 630, {0,2,1,3});
  g->Unary(ynn_unary_square, 630, 640);
  g->Reduce(ynn_reduce_sum, 640, 2712, {3}, true);
  g->ShapeProduct(640, 2711, {3});
  g->Binary(ynn_binary_divide, 2712, 2711, 651);
  g->Binary(ynn_binary_add, 651, 3004, 661);
  g->Binary(ynn_binary_pow, 661, 3006, 672);
  g->Binary(ynn_binary_multiply, 630, 672, 682);
  g->Convert(3051, 693);
  g->Binary(ynn_binary_multiply, 682, 693, 704);
  g->Slice(704, 715, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(704, 726, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 726, 738);
  g->Concat({738,715}, 749, 3);
  g->Binary(ynn_binary_multiply, 704, 1015, 759);
  g->Binary(ynn_binary_multiply, 749, 1118, 765);
  g->Binary(ynn_binary_add, 759, 765, 776);
  g->Transpose(3056, 2128, {1,0});
  g->Binary(ynn_binary_multiply, 2046, 2127, 2125);
  g->Dot(590, 2128, YNN_INVALID_VALUE_ID, 2124, 1);
  g->DequantizeTensor(2124, YNN_INVALID_VALUE_ID, 2125, 2126);
  g->QuantizeTensor(2126, 2971, 2047, 796);
  g->Dequantize(796, 807, 0.41535434126853943, 0);
  g->Reshape(807, 817, {1,0,1,256});
  g->Transpose(817, 828, {0,2,1,3});
  g->Unary(ynn_unary_square, 828, 840);
  g->Reduce(ynn_reduce_sum, 840, 2764, {3}, true);
  g->ShapeProduct(840, 2763, {3});
  g->Binary(ynn_binary_divide, 2764, 2763, 851);
  g->Binary(ynn_binary_add, 851, 3004, 862);
  g->Binary(ynn_binary_pow, 862, 3006, 873);
  g->Binary(ynn_binary_multiply, 828, 873, 883);
}

// Scope: "Layer1 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(776, 894, 0.005761673673987389, 0);
  g->Append(2973, 894, 3283, 2, s2, s1);
  g->View(3283, 3313, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(3313, 896, 0.005761673673987389, 0);
  g->Quantize(883, 897, 0.047244105488061905, 0);
  g->Append(2988, 897, 3298, 2, s2, s1);
  g->View(3298, 3327, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(3327, 899, 0.047244105488061905, 0);
}

// Scope: "Layer1 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(3055, 2179, {1,0});
  g->Binary(ynn_binary_multiply, 2046, 2178, 2175);
  g->Dot(590, 2179, YNN_INVALID_VALUE_ID, 2174, 1);
  g->DequantizeTensor(2174, YNN_INVALID_VALUE_ID, 2175, 2176);
  g->QuantizeTensor(2176, 2971, 2177, 900);
  g->Dequantize(900, 901, 0.35039371252059937, 0);
  g->SplitDim(901, 902, 2, {8,256});
  g->Transpose(902, 903, {0,2,1,3});
  g->Unary(ynn_unary_square, 903, 904);
  g->Reduce(ynn_reduce_sum, 904, 2772, {3}, true);
  g->ShapeProduct(904, 2771, {3});
  g->Binary(ynn_binary_divide, 2772, 2771, 905);
  g->Binary(ynn_binary_add, 905, 3004, 908);
  g->Binary(ynn_binary_pow, 908, 3006, 909);
  g->Binary(ynn_binary_multiply, 903, 909, 910);
  g->Convert(3054, 911);
  g->Binary(ynn_binary_multiply, 910, 911, 912);
  g->Slice(912, 913, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(912, 914, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 914, 915);
  g->Concat({915,913}, 916, 3);
  g->Binary(ynn_binary_multiply, 912, 1015, 917);
  g->Binary(ynn_binary_multiply, 916, 1118, 919);
  g->Binary(ynn_binary_add, 917, 919, 920);
}

// Scope: "Layer1 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(920, 896, 921, false, true);
  g->Mask(921, 3010, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 3010, 2776, {-1}, true);
  g->Binary(ynn_binary_subtract, 3010, 2776, 2773);
  g->Unary(ynn_unary_exp, 2773, 2774);
  g->Reduce(ynn_reduce_sum, 2774, 2777, {-1}, true);
  g->Binary(ynn_binary_divide, 2558, 2777, 2775);
  g->Binary(ynn_binary_multiply, 2774, 2775, 922);
  g->Matmul(922, 899, 923, false, false);
}

// Scope: "Layer1 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(923, 924, {0,2,1,3});
  g->FuseDims(924, 925, 2, 2);
  g->Quantize(925, 926, 0.023129930719733238, 0);
  g->Transpose(3053, 2186, {1,0});
  g->Binary(ynn_binary_multiply, 2183, 2185, 2181);
  g->Dot(926, 2186, YNN_INVALID_VALUE_ID, 2180, 1);
  g->DequantizeTensor(2180, YNN_INVALID_VALUE_ID, 2181, 2182);
  g->QuantizeTensor(2182, 2971, 2184, 927);
  g->Dequantize(927, 929, 0.03322756290435791, 0);
}

// Scope: "Layer1 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 503, 514);
  g->Reduce(ynn_reduce_sum, 514, 2686, {2}, true);
  g->ShapeProduct(514, 2685, {2});
  g->Binary(ynn_binary_divide, 2686, 2685, 525);
  g->Binary(ynn_binary_add, 525, 3004, 536);
  g->Binary(ynn_binary_pow, 536, 3006, 546);
  g->Binary(ynn_binary_multiply, 503, 546, 557);
  g->Convert(3040, 568);
  g->Binary(ynn_binary_multiply, 557, 568, 579);
  BuildLayer1AttentionKvProjection(ctx);
  BuildLayer1AttentionCacheUpdate(ctx);
  BuildLayer1AttentionQueryProjection(ctx);
  BuildLayer1AttentionSdpa(ctx);
  BuildLayer1AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 929, 930);
  g->Reduce(ynn_reduce_sum, 930, 2781, {2}, true);
  g->ShapeProduct(930, 2780, {2});
  g->Binary(ynn_binary_divide, 2781, 2780, 931);
  g->Binary(ynn_binary_add, 931, 3004, 932);
  g->Binary(ynn_binary_pow, 932, 3006, 933);
  g->Binary(ynn_binary_multiply, 929, 933, 934);
  g->Convert(3047, 935);
  g->Binary(ynn_binary_multiply, 934, 935, 936);
  g->Binary(ynn_binary_add, 503, 936, 937);
}

// Scope: "Layer1 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 937, 938);
  g->Reduce(ynn_reduce_sum, 938, 2783, {2}, true);
  g->ShapeProduct(938, 2782, {2});
  g->Binary(ynn_binary_divide, 2783, 2782, 940);
  g->Binary(ynn_binary_add, 940, 3004, 941);
  g->Binary(ynn_binary_pow, 941, 3006, 942);
  g->Binary(ynn_binary_multiply, 937, 942, 943);
  g->Convert(3050, 944);
  g->Binary(ynn_binary_multiply, 943, 944, 945);
  g->Quantize(945, 946, 0.08275254815816879, 0);
  g->Transpose(3044, 2193, {1,0});
  g->Binary(ynn_binary_multiply, 2190, 2192, 2188);
  g->Dot(946, 2193, YNN_INVALID_VALUE_ID, 2187, 1);
  g->DequantizeTensor(2187, YNN_INVALID_VALUE_ID, 2188, 2189);
  g->QuantizeTensor(2189, 2971, 2191, 947);
  g->Dequantize(947, 948, 0.06889764219522476, 0);
  g->Transpose(3043, 2198, {1,0});
  g->Binary(ynn_binary_multiply, 2190, 2197, 2195);
  g->Dot(946, 2198, YNN_INVALID_VALUE_ID, 2194, 1);
  g->DequantizeTensor(2194, YNN_INVALID_VALUE_ID, 2195, 2196);
  g->QuantizeTensor(2196, 2971, 2191, 950);
  g->Dequantize(950, 951, 0.06889764219522476, 0);
  g->Polynomial(951, 2786, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2786, 2787);
  g->Binary(ynn_binary_add, 2787, 2558, 2784);
  g->Binary(ynn_binary_multiply, 951, 2556, 2785);
  g->Binary(ynn_binary_multiply, 2785, 2784, 952);
  g->Binary(ynn_binary_multiply, 948, 952, 953);
  g->Quantize(953, 954, 0.21062994003295898, 0);
  g->Transpose(3042, 2205, {1,0});
  g->Binary(ynn_binary_multiply, 2202, 2204, 2200);
  g->Dot(954, 2205, YNN_INVALID_VALUE_ID, 2199, 1);
  g->DequantizeTensor(2199, YNN_INVALID_VALUE_ID, 2200, 2201);
  g->QuantizeTensor(2201, 2971, 2203, 955);
  g->Dequantize(955, 956, 0.09257561713457108, 0);
  g->Unary(ynn_unary_square, 956, 957);
  g->Reduce(ynn_reduce_sum, 957, 2789, {2}, true);
  g->ShapeProduct(957, 2788, {2});
  g->Binary(ynn_binary_divide, 2789, 2788, 958);
  g->Binary(ynn_binary_add, 958, 3004, 959);
  g->Binary(ynn_binary_pow, 959, 3006, 961);
  g->Binary(ynn_binary_multiply, 956, 961, 962);
  g->Convert(3048, 963);
  g->Binary(ynn_binary_multiply, 962, 963, 964);
  g->Binary(ynn_binary_add, 937, 964, 965);
}

// Scope: "Layer1 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(907, 966, {0,0,1,0}, {-1,-1,1,-1});
  g->Reshape(966, 967, {1,0,256});
  g->Binary(ynn_binary_add, 967, 3268, 968);
  g->Binary(ynn_binary_multiply, 968, 3003, 969);
  g->Quantize(965, 970, 0.4206320643424988, 0);
  g->Transpose(3045, 2212, {1,0});
  g->Binary(ynn_binary_multiply, 2209, 2211, 2207);
  g->Dot(970, 2212, YNN_INVALID_VALUE_ID, 2206, 1);
  g->DequantizeTensor(2206, YNN_INVALID_VALUE_ID, 2207, 2208);
  g->QuantizeTensor(2208, 2971, 2210, 972);
  g->Dequantize(972, 973, 0.010150108486413956, 0);
  g->Polynomial(973, 2792, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2792, 2793);
  g->Binary(ynn_binary_add, 2793, 2558, 2790);
  g->Binary(ynn_binary_multiply, 973, 2556, 2791);
  g->Binary(ynn_binary_multiply, 2791, 2790, 974);
  g->Binary(ynn_binary_multiply, 974, 969, 975);
  g->Quantize(975, 976, 0.026820875704288483, 0);
  g->Transpose(3046, 2219, {1,0});
  g->Binary(ynn_binary_multiply, 2216, 2218, 2214);
  g->Dot(976, 2219, YNN_INVALID_VALUE_ID, 2213, 1);
  g->DequantizeTensor(2213, YNN_INVALID_VALUE_ID, 2214, 2215);
  g->QuantizeTensor(2215, 2971, 2217, 977);
  g->Dequantize(977, 978, 0.020895034074783325, 0);
  g->Unary(ynn_unary_square, 978, 979);
  g->Reduce(ynn_reduce_sum, 979, 2795, {2}, true);
  g->ShapeProduct(979, 2794, {2});
  g->Binary(ynn_binary_divide, 2795, 2794, 980);
  g->Binary(ynn_binary_add, 980, 3004, 981);
  g->Binary(ynn_binary_pow, 981, 3006, 983);
  g->Binary(ynn_binary_multiply, 978, 983, 984);
  g->Convert(3049, 985);
  g->Binary(ynn_binary_multiply, 984, 985, 986);
  g->Binary(ynn_binary_add, 965, 986, 987);
  g->Convert(3041, 988);
  g->Binary(ynn_binary_multiply, 987, 988, 989);
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
  g->Quantize(997, 998, 0.15746013820171356, 0);
  g->Transpose(3141, 2226, {1,0});
  g->Binary(ynn_binary_multiply, 2223, 2225, 2221);
  g->Dot(998, 2226, YNN_INVALID_VALUE_ID, 2220, 1);
  g->DequantizeTensor(2220, YNN_INVALID_VALUE_ID, 2221, 2222);
  g->QuantizeTensor(2222, 2971, 2224, 999);
  g->Dequantize(999, 1000, 0.180118128657341, 0);
  g->Reshape(1000, 1001, {1,0,1,256});
  g->Transpose(1001, 1002, {0,2,1,3});
  g->Unary(ynn_unary_square, 1002, 1003);
  g->Reduce(ynn_reduce_sum, 1003, 2799, {3}, true);
  g->ShapeProduct(1003, 2798, {3});
  g->Binary(ynn_binary_divide, 2799, 2798, 1005);
  g->Binary(ynn_binary_add, 1005, 3004, 1006);
  g->Binary(ynn_binary_pow, 1006, 3006, 1007);
  g->Binary(ynn_binary_multiply, 1002, 1007, 1008);
  g->Convert(3140, 1009);
  g->Binary(ynn_binary_multiply, 1008, 1009, 1010);
  g->Slice(1010, 1011, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1010, 1012, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1012, 1013);
  g->Concat({1013,1011}, 1014, 3);
  g->Binary(ynn_binary_multiply, 1010, 1015, 1017);
  g->Binary(ynn_binary_multiply, 1014, 1118, 1018);
  g->Binary(ynn_binary_add, 1017, 1018, 1019);
  g->Transpose(3145, 2238, {1,0});
  g->Binary(ynn_binary_multiply, 2223, 2237, 2235);
  g->Dot(998, 2238, YNN_INVALID_VALUE_ID, 2234, 1);
  g->DequantizeTensor(2234, YNN_INVALID_VALUE_ID, 2235, 2236);
  g->QuantizeTensor(2236, 2971, 2224, 1020);
  g->Dequantize(1020, 1021, 0.180118128657341, 0);
  g->Reshape(1021, 1022, {1,0,1,256});
  g->Transpose(1022, 1023, {0,2,1,3});
  g->Unary(ynn_unary_square, 1023, 1024);
  g->Reduce(ynn_reduce_sum, 1024, 2801, {3}, true);
  g->ShapeProduct(1024, 2800, {3});
  g->Binary(ynn_binary_divide, 2801, 2800, 1025);
  g->Binary(ynn_binary_add, 1025, 3004, 1027);
  g->Binary(ynn_binary_pow, 1027, 3006, 1028);
  g->Binary(ynn_binary_multiply, 1023, 1028, 1029);
}

// Scope: "Layer2 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(1019, 1030, 0.005684707313776016, 0);
  g->Append(2979, 1030, 3289, 2, s2, s1);
  g->View(3289, 3318, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(3318, 1031, 0.005684707313776016, 0);
  g->Quantize(1029, 1032, 0.047244105488061905, 0);
  g->Append(2994, 1032, 3304, 2, s2, s1);
  g->View(3304, 3332, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(3332, 1034, 0.047244105488061905, 0);
}

// Scope: "Layer2 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(3144, 2244, {1,0});
  g->Binary(ynn_binary_multiply, 2223, 2243, 2240);
  g->Dot(998, 2244, YNN_INVALID_VALUE_ID, 2239, 1);
  g->DequantizeTensor(2239, YNN_INVALID_VALUE_ID, 2240, 2241);
  g->QuantizeTensor(2241, 2971, 2242, 1035);
  g->Dequantize(1035, 1036, 0.1643700897693634, 0);
  g->SplitDim(1036, 1037, 2, {8,256});
  g->Transpose(1037, 1038, {0,2,1,3});
  g->Unary(ynn_unary_square, 1038, 1039);
  g->Reduce(ynn_reduce_sum, 1039, 2803, {3}, true);
  g->ShapeProduct(1039, 2802, {3});
  g->Binary(ynn_binary_divide, 2803, 2802, 1040);
  g->Binary(ynn_binary_add, 1040, 3004, 1041);
  g->Binary(ynn_binary_pow, 1041, 3006, 1042);
  g->Binary(ynn_binary_multiply, 1038, 1042, 1044);
  g->Convert(3143, 1045);
  g->Binary(ynn_binary_multiply, 1044, 1045, 1046);
  g->Slice(1046, 1047, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1046, 1048, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1048, 1049);
  g->Concat({1049,1047}, 1050, 3);
  g->Binary(ynn_binary_multiply, 1046, 1015, 1051);
  g->Binary(ynn_binary_multiply, 1050, 1118, 1052);
  g->Binary(ynn_binary_add, 1051, 1052, 1053);
}

// Scope: "Layer2 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(1053, 1031, 1055, false, true);
  g->Mask(1055, 3015, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 3015, 2809, {-1}, true);
  g->Binary(ynn_binary_subtract, 3015, 2809, 2806);
  g->Unary(ynn_unary_exp, 2806, 2807);
  g->Reduce(ynn_reduce_sum, 2807, 2810, {-1}, true);
  g->Binary(ynn_binary_divide, 2558, 2810, 2808);
  g->Binary(ynn_binary_multiply, 2807, 2808, 1056);
  g->Matmul(1056, 1034, 1057, false, false);
}

// Scope: "Layer2 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1057, 1058, {0,2,1,3});
  g->FuseDims(1058, 1059, 2, 2);
  g->Quantize(1059, 1060, 0.0216535534709692, 0);
  g->Transpose(3142, 2251, {1,0});
  g->Binary(ynn_binary_multiply, 2248, 2250, 2246);
  g->Dot(1060, 2251, YNN_INVALID_VALUE_ID, 2245, 1);
  g->DequantizeTensor(2245, YNN_INVALID_VALUE_ID, 2246, 2247);
  g->QuantizeTensor(2247, 2971, 2249, 1061);
  g->Dequantize(1061, 1062, 0.03426840156316757, 0);
}

// Scope: "Layer2 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 989, 990);
  g->Reduce(ynn_reduce_sum, 990, 2797, {2}, true);
  g->ShapeProduct(990, 2796, {2});
  g->Binary(ynn_binary_divide, 2797, 2796, 991);
  g->Binary(ynn_binary_add, 991, 3004, 992);
  g->Binary(ynn_binary_pow, 992, 3006, 994);
  g->Binary(ynn_binary_multiply, 989, 994, 995);
  g->Convert(3129, 996);
  g->Binary(ynn_binary_multiply, 995, 996, 997);
  BuildLayer2AttentionKvProjection(ctx);
  BuildLayer2AttentionCacheUpdate(ctx);
  BuildLayer2AttentionQueryProjection(ctx);
  BuildLayer2AttentionSdpa(ctx);
  BuildLayer2AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1062, 1063);
  g->Reduce(ynn_reduce_sum, 1063, 2812, {2}, true);
  g->ShapeProduct(1063, 2811, {2});
  g->Binary(ynn_binary_divide, 2812, 2811, 1065);
  g->Binary(ynn_binary_add, 1065, 3004, 1066);
  g->Binary(ynn_binary_pow, 1066, 3006, 1067);
  g->Binary(ynn_binary_multiply, 1062, 1067, 1068);
  g->Convert(3136, 1069);
  g->Binary(ynn_binary_multiply, 1068, 1069, 1070);
  g->Binary(ynn_binary_add, 989, 1070, 1071);
}

// Scope: "Layer2 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1071, 1072);
  g->Reduce(ynn_reduce_sum, 1072, 2814, {2}, true);
  g->ShapeProduct(1072, 2813, {2});
  g->Binary(ynn_binary_divide, 2814, 2813, 1073);
  g->Binary(ynn_binary_add, 1073, 3004, 1074);
  g->Binary(ynn_binary_pow, 1074, 3006, 1076);
  g->Binary(ynn_binary_multiply, 1071, 1076, 1077);
  g->Convert(3139, 1078);
  g->Binary(ynn_binary_multiply, 1077, 1078, 1079);
  g->Quantize(1079, 1080, 0.04049227386713028, 0);
  g->Transpose(3133, 2258, {1,0});
  g->Binary(ynn_binary_multiply, 2255, 2257, 2253);
  g->Dot(1080, 2258, YNN_INVALID_VALUE_ID, 2252, 1);
  g->DequantizeTensor(2252, YNN_INVALID_VALUE_ID, 2253, 2254);
  g->QuantizeTensor(2254, 2971, 2256, 1081);
  g->Dequantize(1081, 1082, 0.04183071851730347, 0);
  g->Transpose(3132, 2263, {1,0});
  g->Binary(ynn_binary_multiply, 2255, 2262, 2260);
  g->Dot(1080, 2263, YNN_INVALID_VALUE_ID, 2259, 1);
  g->DequantizeTensor(2259, YNN_INVALID_VALUE_ID, 2260, 2261);
  g->QuantizeTensor(2261, 2971, 2256, 1083);
  g->Dequantize(1083, 1084, 0.04183071851730347, 0);
  g->Polynomial(1084, 2817, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2817, 2818);
  g->Binary(ynn_binary_add, 2818, 2558, 2815);
  g->Binary(ynn_binary_multiply, 1084, 2556, 2816);
  g->Binary(ynn_binary_multiply, 2816, 2815, 1086);
  g->Binary(ynn_binary_multiply, 1082, 1086, 1087);
  g->Quantize(1087, 1088, 0.09645669907331467, 0);
  g->Transpose(3131, 2270, {1,0});
  g->Binary(ynn_binary_multiply, 2267, 2269, 2265);
  g->Dot(1088, 2270, YNN_INVALID_VALUE_ID, 2264, 1);
  g->DequantizeTensor(2264, YNN_INVALID_VALUE_ID, 2265, 2266);
  g->QuantizeTensor(2266, 2971, 2268, 1089);
  g->Dequantize(1089, 1090, 0.05011765658855438, 0);
  g->Unary(ynn_unary_square, 1090, 1091);
  g->Reduce(ynn_reduce_sum, 1091, 2820, {2}, true);
  g->ShapeProduct(1091, 2819, {2});
  g->Binary(ynn_binary_divide, 2820, 2819, 1092);
  g->Binary(ynn_binary_add, 1092, 3004, 1093);
  g->Binary(ynn_binary_pow, 1093, 3006, 1094);
  g->Binary(ynn_binary_multiply, 1090, 1094, 1095);
  g->Convert(3137, 1097);
  g->Binary(ynn_binary_multiply, 1095, 1097, 1098);
  g->Binary(ynn_binary_add, 1071, 1098, 1099);
}

// Scope: "Layer2 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(907, 1100, {0,0,2,0}, {-1,-1,1,-1});
  g->Reshape(1100, 1101, {1,0,256});
  g->Binary(ynn_binary_add, 1101, 3273, 1102);
  g->Binary(ynn_binary_multiply, 1102, 3003, 1103);
  g->Quantize(1099, 1104, 0.045230474323034286, 0);
  g->Transpose(3134, 2277, {1,0});
  g->Binary(ynn_binary_multiply, 2274, 2276, 2272);
  g->Dot(1104, 2277, YNN_INVALID_VALUE_ID, 2271, 1);
  g->DequantizeTensor(2271, YNN_INVALID_VALUE_ID, 2272, 2273);
  g->QuantizeTensor(2273, 2971, 2275, 1105);
  g->Dequantize(1105, 1106, 0.017839577049016953, 0);
  g->Polynomial(1106, 2823, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2823, 2824);
  g->Binary(ynn_binary_add, 2824, 2558, 2821);
  g->Binary(ynn_binary_multiply, 1106, 2556, 2822);
  g->Binary(ynn_binary_multiply, 2822, 2821, 1108);
  g->Binary(ynn_binary_multiply, 1108, 1103, 1109);
  g->Quantize(1109, 1110, 0.05216536670923233, 0);
  g->Transpose(3135, 2284, {1,0});
  g->Binary(ynn_binary_multiply, 2281, 2283, 2279);
  g->Dot(1110, 2284, YNN_INVALID_VALUE_ID, 2278, 1);
  g->DequantizeTensor(2278, YNN_INVALID_VALUE_ID, 2279, 2280);
  g->QuantizeTensor(2280, 2971, 2282, 1111);
  g->Dequantize(1111, 1112, 0.021943029016256332, 0);
  g->Unary(ynn_unary_square, 1112, 1113);
  g->Reduce(ynn_reduce_sum, 1113, 2826, {2}, true);
  g->ShapeProduct(1113, 2825, {2});
  g->Binary(ynn_binary_divide, 2826, 2825, 1114);
  g->Binary(ynn_binary_add, 1114, 3004, 1115);
  g->Binary(ynn_binary_pow, 1115, 3006, 1116);
  g->Binary(ynn_binary_multiply, 1112, 1116, 1117);
  g->Convert(3138, 1120);
  g->Binary(ynn_binary_multiply, 1117, 1120, 1121);
  g->Binary(ynn_binary_add, 1099, 1121, 1122);
  g->Convert(3130, 1123);
  g->Binary(ynn_binary_multiply, 1122, 1123, 1124);
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
  g->Quantize(1132, 1133, 0.12591414153575897, 0);
  g->Transpose(3158, 2291, {1,0});
  g->Binary(ynn_binary_multiply, 2288, 2290, 2286);
  g->Dot(1133, 2291, YNN_INVALID_VALUE_ID, 2285, 1);
  g->DequantizeTensor(2285, YNN_INVALID_VALUE_ID, 2286, 2287);
  g->QuantizeTensor(2287, 2971, 2289, 1134);
  g->Dequantize(1134, 1135, 0.08710630983114243, 0);
  g->Reshape(1135, 1136, {1,0,1,256});
  g->Transpose(1136, 1137, {0,2,1,3});
  g->Unary(ynn_unary_square, 1137, 1138);
  g->Reduce(ynn_reduce_sum, 1138, 2830, {3}, true);
  g->ShapeProduct(1138, 2829, {3});
  g->Binary(ynn_binary_divide, 2830, 2829, 1139);
  g->Binary(ynn_binary_add, 1139, 3004, 1140);
  g->Binary(ynn_binary_pow, 1140, 3006, 1142);
  g->Binary(ynn_binary_multiply, 1137, 1142, 1143);
  g->Convert(3157, 1144);
  g->Binary(ynn_binary_multiply, 1143, 1144, 1145);
  g->Slice(1145, 1146, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1145, 1147, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1147, 1148);
  g->Concat({1148,1146}, 1149, 3);
  g->Binary(ynn_binary_multiply, 1145, 1015, 1150);
  g->Binary(ynn_binary_multiply, 1149, 1118, 1151);
  g->Binary(ynn_binary_add, 1150, 1151, 1153);
  g->Transpose(3162, 2296, {1,0});
  g->Binary(ynn_binary_multiply, 2288, 2295, 2293);
  g->Dot(1133, 2296, YNN_INVALID_VALUE_ID, 2292, 1);
  g->DequantizeTensor(2292, YNN_INVALID_VALUE_ID, 2293, 2294);
  g->QuantizeTensor(2294, 2971, 2289, 1154);
  g->Dequantize(1154, 1155, 0.08710630983114243, 0);
  g->Reshape(1155, 1156, {1,0,1,256});
  g->Transpose(1156, 1157, {0,2,1,3});
  g->Unary(ynn_unary_square, 1157, 1158);
  g->Reduce(ynn_reduce_sum, 1158, 2832, {3}, true);
  g->ShapeProduct(1158, 2831, {3});
  g->Binary(ynn_binary_divide, 2832, 2831, 1159);
  g->Binary(ynn_binary_add, 1159, 3004, 1160);
  g->Binary(ynn_binary_pow, 1160, 3006, 1161);
  g->Binary(ynn_binary_multiply, 1157, 1161, 1163);
}

// Scope: "Layer3 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(1153, 1164, 0.00573749840259552, 0);
  g->Append(2980, 1164, 3290, 2, s2, s1);
  g->View(3290, 3319, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(3319, 1165, 0.00573749840259552, 0);
  g->Quantize(1163, 1166, 0.047244105488061905, 0);
  g->Append(2995, 1166, 3305, 2, s2, s1);
  g->View(3305, 3333, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(3333, 1167, 0.047244105488061905, 0);
}

// Scope: "Layer3 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(3161, 2302, {1,0});
  g->Binary(ynn_binary_multiply, 2288, 2301, 2298);
  g->Dot(1133, 2302, YNN_INVALID_VALUE_ID, 2297, 1);
  g->DequantizeTensor(2297, YNN_INVALID_VALUE_ID, 2298, 2299);
  g->QuantizeTensor(2299, 2971, 2300, 1169);
  g->Dequantize(1169, 1170, 0.15354332327842712, 0);
  g->SplitDim(1170, 1171, 2, {8,256});
  g->Transpose(1171, 1172, {0,2,1,3});
  g->Unary(ynn_unary_square, 1172, 1173);
  g->Reduce(ynn_reduce_sum, 1173, 2834, {3}, true);
  g->ShapeProduct(1173, 2833, {3});
  g->Binary(ynn_binary_divide, 2834, 2833, 1174);
  g->Binary(ynn_binary_add, 1174, 3004, 1175);
  g->Binary(ynn_binary_pow, 1175, 3006, 1176);
  g->Binary(ynn_binary_multiply, 1172, 1176, 1177);
  g->Convert(3160, 1178);
  g->Binary(ynn_binary_multiply, 1177, 1178, 1180);
  g->Slice(1180, 1181, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1180, 1182, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1182, 1183);
  g->Concat({1183,1181}, 1184, 3);
  g->Binary(ynn_binary_multiply, 1180, 1015, 1185);
  g->Binary(ynn_binary_multiply, 1184, 1118, 1186);
  g->Binary(ynn_binary_add, 1185, 1186, 1187);
}

// Scope: "Layer3 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(1187, 1165, 1188, false, true);
  g->Mask(1188, 3016, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 3016, 2838, {-1}, true);
  g->Binary(ynn_binary_subtract, 3016, 2838, 2835);
  g->Unary(ynn_unary_exp, 2835, 2836);
  g->Reduce(ynn_reduce_sum, 2836, 2839, {-1}, true);
  g->Binary(ynn_binary_divide, 2558, 2839, 2837);
  g->Binary(ynn_binary_multiply, 2836, 2837, 1189);
  g->Matmul(1189, 1167, 1190, false, false);
}

// Scope: "Layer3 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1190, 1191, {0,2,1,3});
  g->FuseDims(1191, 1192, 2, 2);
  g->Quantize(1192, 1193, 0.02706693857908249, 0);
  g->Transpose(3159, 2309, {1,0});
  g->Binary(ynn_binary_multiply, 2306, 2308, 2304);
  g->Dot(1193, 2309, YNN_INVALID_VALUE_ID, 2303, 1);
  g->DequantizeTensor(2303, YNN_INVALID_VALUE_ID, 2304, 2305);
  g->QuantizeTensor(2305, 2971, 2307, 1194);
  g->Dequantize(1194, 1195, 0.07367152720689774, 0);
}

// Scope: "Layer3 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1124, 1125);
  g->Reduce(ynn_reduce_sum, 1125, 2828, {2}, true);
  g->ShapeProduct(1125, 2827, {2});
  g->Binary(ynn_binary_divide, 2828, 2827, 1126);
  g->Binary(ynn_binary_add, 1126, 3004, 1127);
  g->Binary(ynn_binary_pow, 1127, 3006, 1128);
  g->Binary(ynn_binary_multiply, 1124, 1128, 1129);
  g->Convert(3146, 1131);
  g->Binary(ynn_binary_multiply, 1129, 1131, 1132);
  BuildLayer3AttentionKvProjection(ctx);
  BuildLayer3AttentionCacheUpdate(ctx);
  BuildLayer3AttentionQueryProjection(ctx);
  BuildLayer3AttentionSdpa(ctx);
  BuildLayer3AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1195, 1196);
  g->Reduce(ynn_reduce_sum, 1196, 2841, {2}, true);
  g->ShapeProduct(1196, 2840, {2});
  g->Binary(ynn_binary_divide, 2841, 2840, 1197);
  g->Binary(ynn_binary_add, 1197, 3004, 1198);
  g->Binary(ynn_binary_pow, 1198, 3006, 1200);
  g->Binary(ynn_binary_multiply, 1195, 1200, 1201);
  g->Convert(3153, 1202);
  g->Binary(ynn_binary_multiply, 1201, 1202, 1203);
  g->Binary(ynn_binary_add, 1124, 1203, 1204);
}

// Scope: "Layer3 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1204, 1205);
  g->Reduce(ynn_reduce_sum, 1205, 2843, {2}, true);
  g->ShapeProduct(1205, 2842, {2});
  g->Binary(ynn_binary_divide, 2843, 2842, 1206);
  g->Binary(ynn_binary_add, 1206, 3004, 1207);
  g->Binary(ynn_binary_pow, 1207, 3006, 1208);
  g->Binary(ynn_binary_multiply, 1204, 1208, 1209);
  g->Convert(3156, 1211);
  g->Binary(ynn_binary_multiply, 1209, 1211, 1212);
  g->Quantize(1212, 1213, 0.019482526928186417, 0);
  g->Transpose(3150, 2321, {1,0});
  g->Binary(ynn_binary_multiply, 2318, 2320, 2316);
  g->Dot(1213, 2321, YNN_INVALID_VALUE_ID, 2315, 1);
  g->DequantizeTensor(2315, YNN_INVALID_VALUE_ID, 2316, 2317);
  g->QuantizeTensor(2317, 2971, 2319, 1214);
  g->Dequantize(1214, 1215, 0.02005414292216301, 0);
  g->Transpose(3149, 2326, {1,0});
  g->Binary(ynn_binary_multiply, 2318, 2325, 2323);
  g->Dot(1213, 2326, YNN_INVALID_VALUE_ID, 2322, 1);
  g->DequantizeTensor(2322, YNN_INVALID_VALUE_ID, 2323, 2324);
  g->QuantizeTensor(2324, 2971, 2319, 1216);
  g->Dequantize(1216, 1217, 0.02005414292216301, 0);
  g->Polynomial(1217, 2846, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2846, 2847);
  g->Binary(ynn_binary_add, 2847, 2558, 2844);
  g->Binary(ynn_binary_multiply, 1217, 2556, 2845);
  g->Binary(ynn_binary_multiply, 2845, 2844, 1218);
  g->Binary(ynn_binary_multiply, 1215, 1218, 1219);
  g->Quantize(1219, 1222, 0.03297245129942894, 0);
  g->Transpose(3148, 2333, {1,0});
  g->Binary(ynn_binary_multiply, 2330, 2332, 2328);
  g->Dot(1222, 2333, YNN_INVALID_VALUE_ID, 2327, 1);
  g->DequantizeTensor(2327, YNN_INVALID_VALUE_ID, 2328, 2329);
  g->QuantizeTensor(2329, 2971, 2331, 1223);
  g->Dequantize(1223, 1224, 0.022154856473207474, 0);
  g->Unary(ynn_unary_square, 1224, 1225);
  g->Reduce(ynn_reduce_sum, 1225, 2849, {2}, true);
  g->ShapeProduct(1225, 2848, {2});
  g->Binary(ynn_binary_divide, 2849, 2848, 1226);
  g->Binary(ynn_binary_add, 1226, 3004, 1227);
  g->Binary(ynn_binary_pow, 1227, 3006, 1228);
  g->Binary(ynn_binary_multiply, 1224, 1228, 1229);
  g->Convert(3154, 1230);
  g->Binary(ynn_binary_multiply, 1229, 1230, 1231);
  g->Binary(ynn_binary_add, 1204, 1231, 1233);
}

// Scope: "Layer3 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(907, 1234, {0,0,3,0}, {-1,-1,1,-1});
  g->Reshape(1234, 1235, {1,0,256});
  g->Binary(ynn_binary_add, 1235, 3274, 1236);
  g->Binary(ynn_binary_multiply, 1236, 3003, 1237);
  g->Quantize(1233, 1238, 0.2861534655094147, 0);
  g->Transpose(3151, 2340, {1,0});
  g->Binary(ynn_binary_multiply, 2337, 2339, 2335);
  g->Dot(1238, 2340, YNN_INVALID_VALUE_ID, 2334, 1);
  g->DequantizeTensor(2334, YNN_INVALID_VALUE_ID, 2335, 2336);
  g->QuantizeTensor(2336, 2971, 2338, 1239);
  g->Dequantize(1239, 1240, 0.050688985735177994, 0);
  g->Polynomial(1240, 2852, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2852, 2853);
  g->Binary(ynn_binary_add, 2853, 2558, 2850);
  g->Binary(ynn_binary_multiply, 1240, 2556, 2851);
  g->Binary(ynn_binary_multiply, 2851, 2850, 1241);
  g->Binary(ynn_binary_multiply, 1241, 1237, 1242);
  g->Quantize(1242, 1244, 0.06692913919687271, 0);
  g->Transpose(3152, 2347, {1,0});
  g->Binary(ynn_binary_multiply, 2344, 2346, 2342);
  g->Dot(1244, 2347, YNN_INVALID_VALUE_ID, 2341, 1);
  g->DequantizeTensor(2341, YNN_INVALID_VALUE_ID, 2342, 2343);
  g->QuantizeTensor(2343, 2971, 2345, 1245);
  g->Dequantize(1245, 1246, 0.0805763527750969, 0);
  g->Unary(ynn_unary_square, 1246, 1247);
  g->Reduce(ynn_reduce_sum, 1247, 2855, {2}, true);
  g->ShapeProduct(1247, 2854, {2});
  g->Binary(ynn_binary_divide, 2855, 2854, 1248);
  g->Binary(ynn_binary_add, 1248, 3004, 1249);
  g->Binary(ynn_binary_pow, 1249, 3006, 1250);
  g->Binary(ynn_binary_multiply, 1246, 1250, 1251);
  g->Convert(3155, 1252);
  g->Binary(ynn_binary_multiply, 1251, 1252, 1253);
  g->Binary(ynn_binary_add, 1233, 1253, 1255);
  g->Convert(3147, 1256);
  g->Binary(ynn_binary_multiply, 1255, 1256, 1257);
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
  g->Quantize(1264, 1266, 0.023374712094664574, 0);
  g->Transpose(3175, 2354, {1,0});
  g->Binary(ynn_binary_multiply, 2351, 2353, 2349);
  g->Dot(1266, 2354, YNN_INVALID_VALUE_ID, 2348, 1);
  g->DequantizeTensor(2348, YNN_INVALID_VALUE_ID, 2349, 2350);
  g->QuantizeTensor(2350, 2971, 2352, 1267);
  g->Dequantize(1267, 1268, 0.024852370843291283, 0);
  g->Reshape(1268, 1269, {1,0,1,512});
  g->Transpose(1269, 1270, {0,2,1,3});
  g->Unary(ynn_unary_square, 1270, 1271);
  g->Reduce(ynn_reduce_sum, 1271, 2861, {3}, true);
  g->ShapeProduct(1271, 2860, {3});
  g->Binary(ynn_binary_divide, 2861, 2860, 1272);
  g->Binary(ynn_binary_add, 1272, 3004, 1273);
  g->Binary(ynn_binary_pow, 1273, 3006, 1274);
  g->Binary(ynn_binary_multiply, 1270, 1274, 1275);
  g->Convert(3174, 1277);
  g->Binary(ynn_binary_multiply, 1275, 1277, 1278);
  g->Slice(1278, 1279, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(1278, 1280, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 1280, 1281);
  g->Concat({1281,1279}, 1282, 3);
  g->Binary(ynn_binary_multiply, 1278, 1532, 1283);
  g->Binary(ynn_binary_multiply, 1282, 1634, 1284);
  g->Binary(ynn_binary_add, 1283, 1284, 1285);
  g->Transpose(3179, 2359, {1,0});
  g->Binary(ynn_binary_multiply, 2351, 2358, 2356);
  g->Dot(1266, 2359, YNN_INVALID_VALUE_ID, 2355, 1);
  g->DequantizeTensor(2355, YNN_INVALID_VALUE_ID, 2356, 2357);
  g->QuantizeTensor(2357, 2971, 2352, 1287);
  g->Dequantize(1287, 1288, 0.024852370843291283, 0);
  g->Reshape(1288, 1289, {1,0,1,512});
  g->Transpose(1289, 1290, {0,2,1,3});
  g->Unary(ynn_unary_square, 1290, 1291);
  g->Reduce(ynn_reduce_sum, 1291, 2863, {3}, true);
  g->ShapeProduct(1291, 2862, {3});
  g->Binary(ynn_binary_divide, 2863, 2862, 1292);
  g->Binary(ynn_binary_add, 1292, 3004, 1293);
  g->Binary(ynn_binary_pow, 1293, 3006, 1294);
  g->Binary(ynn_binary_multiply, 1290, 1294, 1295);
}

// Scope: "Layer4 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(1285, 1296, 0.0011563472216948867, 0);
  g->Append(2981, 1296, 3291, 2, s2, s1);
  g->View(3291, 3320, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(3320, 1298, 0.0011563472216948867, 0);
  g->Quantize(1295, 1299, 0.01785714365541935, 0);
  g->Append(2996, 1299, 3306, 2, s2, s1);
  g->View(3306, 3334, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(3334, 1300, 0.01785714365541935, 0);
}

// Scope: "Layer4 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(3178, 2365, {1,0});
  g->Binary(ynn_binary_multiply, 2351, 2364, 2361);
  g->Dot(1266, 2365, YNN_INVALID_VALUE_ID, 2360, 1);
  g->DequantizeTensor(2360, YNN_INVALID_VALUE_ID, 2361, 2362);
  g->QuantizeTensor(2362, 2971, 2363, 1301);
  g->Dequantize(1301, 1302, 0.03248032554984093, 0);
  g->SplitDim(1302, 1303, 2, {8,512});
  g->Transpose(1303, 1304, {0,2,1,3});
  g->Unary(ynn_unary_square, 1304, 1305);
  g->Reduce(ynn_reduce_sum, 1305, 2865, {3}, true);
  g->ShapeProduct(1305, 2864, {3});
  g->Binary(ynn_binary_divide, 2865, 2864, 1306);
  g->Binary(ynn_binary_add, 1306, 3004, 1307);
  g->Binary(ynn_binary_pow, 1307, 3006, 1308);
  g->Binary(ynn_binary_multiply, 1304, 1308, 1309);
  g->Convert(3177, 1310);
  g->Binary(ynn_binary_multiply, 1309, 1310, 1311);
  g->Slice(1311, 1312, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(1311, 1313, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 1313, 1314);
  g->Concat({1314,1312}, 1315, 3);
  g->Binary(ynn_binary_multiply, 1311, 1532, 1316);
  g->Binary(ynn_binary_multiply, 1315, 1634, 1317);
  g->Binary(ynn_binary_add, 1316, 1317, 1318);
}

// Scope: "Layer4 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(1318, 1298, 1319, false, true);
  g->Mask(1319, 3017, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 3017, 2869, {-1}, true);
  g->Binary(ynn_binary_subtract, 3017, 2869, 2866);
  g->Unary(ynn_unary_exp, 2866, 2867);
  g->Reduce(ynn_reduce_sum, 2867, 2870, {-1}, true);
  g->Binary(ynn_binary_divide, 2558, 2870, 2868);
  g->Binary(ynn_binary_multiply, 2867, 2868, 1320);
  g->Matmul(1320, 1300, 1321, false, false);
}

// Scope: "Layer4 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1321, 1324, {0,2,1,3});
  g->FuseDims(1324, 1325, 2, 2);
  g->Quantize(1325, 1326, 0.017962608486413956, 0);
  g->Transpose(3176, 2371, {1,0});
  g->Binary(ynn_binary_multiply, 1869, 2370, 2367);
  g->Dot(1326, 2371, YNN_INVALID_VALUE_ID, 2366, 1);
  g->DequantizeTensor(2366, YNN_INVALID_VALUE_ID, 2367, 2368);
  g->QuantizeTensor(2368, 2971, 2369, 1327);
  g->Dequantize(1327, 1328, 0.17608338594436646, 0);
}

// Scope: "Layer4 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1257, 1258);
  g->Reduce(ynn_reduce_sum, 1258, 2859, {2}, true);
  g->ShapeProduct(1258, 2858, {2});
  g->Binary(ynn_binary_divide, 2859, 2858, 1259);
  g->Binary(ynn_binary_add, 1259, 3004, 1260);
  g->Binary(ynn_binary_pow, 1260, 3006, 1261);
  g->Binary(ynn_binary_multiply, 1257, 1261, 1262);
  g->Convert(3163, 1263);
  g->Binary(ynn_binary_multiply, 1262, 1263, 1264);
  BuildLayer4AttentionKvProjection(ctx);
  BuildLayer4AttentionCacheUpdate(ctx);
  BuildLayer4AttentionQueryProjection(ctx);
  BuildLayer4AttentionSdpa(ctx);
  BuildLayer4AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1328, 1329);
  g->Reduce(ynn_reduce_sum, 1329, 2872, {2}, true);
  g->ShapeProduct(1329, 2871, {2});
  g->Binary(ynn_binary_divide, 2872, 2871, 1330);
  g->Binary(ynn_binary_add, 1330, 3004, 1331);
  g->Binary(ynn_binary_pow, 1331, 3006, 1332);
  g->Binary(ynn_binary_multiply, 1328, 1332, 1333);
  g->Convert(3170, 1335);
  g->Binary(ynn_binary_multiply, 1333, 1335, 1336);
  g->Binary(ynn_binary_add, 1257, 1336, 1337);
}

// Scope: "Layer4 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1337, 1338);
  g->Reduce(ynn_reduce_sum, 1338, 2874, {2}, true);
  g->ShapeProduct(1338, 2873, {2});
  g->Binary(ynn_binary_divide, 2874, 2873, 1339);
  g->Binary(ynn_binary_add, 1339, 3004, 1340);
  g->Binary(ynn_binary_pow, 1340, 3006, 1341);
  g->Binary(ynn_binary_multiply, 1337, 1341, 1342);
  g->Convert(3173, 1343);
  g->Binary(ynn_binary_multiply, 1342, 1343, 1344);
  g->Quantize(1344, 1345, 0.060907524079084396, 0);
  g->Transpose(3167, 2377, {1,0});
  g->Binary(ynn_binary_multiply, 2375, 2376, 2373);
  g->Dot(1345, 2377, YNN_INVALID_VALUE_ID, 2372, 1);
  g->DequantizeTensor(2372, YNN_INVALID_VALUE_ID, 2373, 2374);
  g->QuantizeTensor(2374, 2971, 1775, 1346);
  g->Dequantize(1346, 1347, 0.09251969307661057, 0);
  g->Transpose(3166, 2382, {1,0});
  g->Binary(ynn_binary_multiply, 2375, 2381, 2379);
  g->Dot(1345, 2382, YNN_INVALID_VALUE_ID, 2378, 1);
  g->DequantizeTensor(2378, YNN_INVALID_VALUE_ID, 2379, 2380);
  g->QuantizeTensor(2380, 2971, 1775, 1348);
  g->Dequantize(1348, 1349, 0.09251969307661057, 0);
  g->Polynomial(1349, 2877, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2877, 2878);
  g->Binary(ynn_binary_add, 2878, 2558, 2875);
  g->Binary(ynn_binary_multiply, 1349, 2556, 2876);
  g->Binary(ynn_binary_multiply, 2876, 2875, 1350);
  g->Binary(ynn_binary_multiply, 1347, 1350, 1351);
  g->Quantize(1351, 1352, 0.3444882035255432, 0);
  g->Transpose(3165, 2389, {1,0});
  g->Binary(ynn_binary_multiply, 2386, 2388, 2384);
  g->Dot(1352, 2389, YNN_INVALID_VALUE_ID, 2383, 1);
  g->DequantizeTensor(2383, YNN_INVALID_VALUE_ID, 2384, 2385);
  g->QuantizeTensor(2385, 2971, 2387, 1353);
  g->Dequantize(1353, 1354, 0.13582009077072144, 0);
  g->Unary(ynn_unary_square, 1354, 1355);
  g->Reduce(ynn_reduce_sum, 1355, 2880, {2}, true);
  g->ShapeProduct(1355, 2879, {2});
  g->Binary(ynn_binary_divide, 2880, 2879, 1356);
  g->Binary(ynn_binary_add, 1356, 3004, 1357);
  g->Binary(ynn_binary_pow, 1357, 3006, 1358);
  g->Binary(ynn_binary_multiply, 1354, 1358, 1359);
  g->Convert(3171, 1360);
  g->Binary(ynn_binary_multiply, 1359, 1360, 1361);
  g->Binary(ynn_binary_add, 1337, 1361, 1362);
}

// Scope: "Layer4 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(907, 1363, {0,0,4,0}, {-1,-1,1,-1});
  g->Reshape(1363, 1365, {1,0,256});
  g->Binary(ynn_binary_add, 1365, 3275, 1366);
  g->Binary(ynn_binary_multiply, 1366, 3003, 1367);
  g->Quantize(1362, 1368, 0.41414323449134827, 0);
  g->Transpose(3168, 2396, {1,0});
  g->Binary(ynn_binary_multiply, 2393, 2395, 2391);
  g->Dot(1368, 2396, YNN_INVALID_VALUE_ID, 2390, 1);
  g->DequantizeTensor(2390, YNN_INVALID_VALUE_ID, 2391, 2392);
  g->QuantizeTensor(2392, 2971, 2394, 1369);
  g->Dequantize(1369, 1370, 0.039862215518951416, 0);
  g->Polynomial(1370, 2883, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2883, 2884);
  g->Binary(ynn_binary_add, 2884, 2558, 2881);
  g->Binary(ynn_binary_multiply, 1370, 2556, 2882);
  g->Binary(ynn_binary_multiply, 2882, 2881, 1371);
  g->Binary(ynn_binary_multiply, 1371, 1367, 1372);
  g->Quantize(1372, 1373, 0.30314961075782776, 0);
  g->Transpose(3169, 2403, {1,0});
  g->Binary(ynn_binary_multiply, 2400, 2402, 2398);
  g->Dot(1373, 2403, YNN_INVALID_VALUE_ID, 2397, 1);
  g->DequantizeTensor(2397, YNN_INVALID_VALUE_ID, 2398, 2399);
  g->QuantizeTensor(2399, 2971, 2401, 1374);
  g->Dequantize(1374, 1375, 0.16701875627040863, 0);
  g->Unary(ynn_unary_square, 1375, 1376);
  g->Reduce(ynn_reduce_sum, 1376, 2886, {2}, true);
  g->ShapeProduct(1376, 2885, {2});
  g->Binary(ynn_binary_divide, 2886, 2885, 1377);
  g->Binary(ynn_binary_add, 1377, 3004, 1378);
  g->Binary(ynn_binary_pow, 1378, 3006, 1379);
  g->Binary(ynn_binary_multiply, 1375, 1379, 1380);
  g->Convert(3172, 1381);
  g->Binary(ynn_binary_multiply, 1380, 1381, 1382);
  g->Binary(ynn_binary_add, 1362, 1382, 1383);
  g->Convert(3164, 1384);
  g->Binary(ynn_binary_multiply, 1383, 1384, 1386);
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
  g->Quantize(1393, 1394, 0.07399173825979233, 0);
  g->Transpose(3192, 2416, {1,0});
  g->Binary(ynn_binary_multiply, 2413, 2415, 2411);
  g->Dot(1394, 2416, YNN_INVALID_VALUE_ID, 2410, 1);
  g->DequantizeTensor(2410, YNN_INVALID_VALUE_ID, 2411, 2412);
  g->QuantizeTensor(2412, 2971, 2414, 1395);
  g->Dequantize(1395, 1397, 0.09842520207166672, 0);
  g->Reshape(1397, 1398, {1,0,1,256});
  g->Transpose(1398, 1399, {0,2,1,3});
  g->Unary(ynn_unary_square, 1399, 1400);
  g->Reduce(ynn_reduce_sum, 1400, 2890, {3}, true);
  g->ShapeProduct(1400, 2889, {3});
  g->Binary(ynn_binary_divide, 2890, 2889, 1401);
  g->Binary(ynn_binary_add, 1401, 3004, 1402);
  g->Binary(ynn_binary_pow, 1402, 3006, 1403);
  g->Binary(ynn_binary_multiply, 1399, 1403, 1404);
  g->Convert(3191, 1405);
  g->Binary(ynn_binary_multiply, 1404, 1405, 1406);
  g->Slice(1406, 1408, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1406, 1409, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1409, 1410);
  g->Concat({1410,1408}, 1411, 3);
  g->Binary(ynn_binary_multiply, 1406, 1015, 1412);
  g->Binary(ynn_binary_multiply, 1411, 1118, 1413);
  g->Binary(ynn_binary_add, 1412, 1413, 1414);
  g->Transpose(3196, 2421, {1,0});
  g->Binary(ynn_binary_multiply, 2413, 2420, 2418);
  g->Dot(1394, 2421, YNN_INVALID_VALUE_ID, 2417, 1);
  g->DequantizeTensor(2417, YNN_INVALID_VALUE_ID, 2418, 2419);
  g->QuantizeTensor(2419, 2971, 2414, 1415);
  g->Dequantize(1415, 1416, 0.09842520207166672, 0);
  g->Reshape(1416, 1418, {1,0,1,256});
  g->Transpose(1418, 1419, {0,2,1,3});
  g->Unary(ynn_unary_square, 1419, 1420);
  g->Reduce(ynn_reduce_sum, 1420, 2892, {3}, true);
  g->ShapeProduct(1420, 2891, {3});
  g->Binary(ynn_binary_divide, 2892, 2891, 1421);
  g->Binary(ynn_binary_add, 1421, 3004, 1422);
  g->Binary(ynn_binary_pow, 1422, 3006, 1423);
  g->Binary(ynn_binary_multiply, 1419, 1423, 1424);
}

// Scope: "Layer5 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(1414, 1425, 0.006011798977851868, 0);
  g->Append(2982, 1425, 3292, 2, s2, s1);
  g->View(3292, 3321, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(3321, 1428, 0.006011798977851868, 0);
  g->Quantize(1424, 1429, 0.047244105488061905, 0);
  g->Append(2997, 1429, 3307, 2, s2, s1);
  g->View(3307, 3335, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(3335, 1430, 0.047244105488061905, 0);
}

// Scope: "Layer5 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(3195, 2426, {1,0});
  g->Binary(ynn_binary_multiply, 2413, 2425, 2423);
  g->Dot(1394, 2426, YNN_INVALID_VALUE_ID, 2422, 1);
  g->DequantizeTensor(2422, YNN_INVALID_VALUE_ID, 2423, 2424);
  g->QuantizeTensor(2424, 2971, 2152, 1431);
  g->Dequantize(1431, 1432, 0.13385827839374542, 0);
  g->SplitDim(1432, 1433, 2, {8,256});
  g->Transpose(1433, 1434, {0,2,1,3});
  g->Unary(ynn_unary_square, 1434, 1436);
  g->Reduce(ynn_reduce_sum, 1436, 2896, {3}, true);
  g->ShapeProduct(1436, 2895, {3});
  g->Binary(ynn_binary_divide, 2896, 2895, 1437);
  g->Binary(ynn_binary_add, 1437, 3004, 1438);
  g->Binary(ynn_binary_pow, 1438, 3006, 1439);
  g->Binary(ynn_binary_multiply, 1434, 1439, 1440);
  g->Convert(3194, 1441);
  g->Binary(ynn_binary_multiply, 1440, 1441, 1442);
  g->Slice(1442, 1443, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1442, 1444, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1444, 1445);
  g->Concat({1445,1443}, 1447, 3);
  g->Binary(ynn_binary_multiply, 1442, 1015, 1448);
  g->Binary(ynn_binary_multiply, 1447, 1118, 1449);
  g->Binary(ynn_binary_add, 1448, 1449, 1450);
}

// Scope: "Layer5 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(1450, 1428, 1451, false, true);
  g->Mask(1451, 3018, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 3018, 2900, {-1}, true);
  g->Binary(ynn_binary_subtract, 3018, 2900, 2897);
  g->Unary(ynn_unary_exp, 2897, 2898);
  g->Reduce(ynn_reduce_sum, 2898, 2901, {-1}, true);
  g->Binary(ynn_binary_divide, 2558, 2901, 2899);
  g->Binary(ynn_binary_multiply, 2898, 2899, 1452);
  g->Matmul(1452, 1430, 1453, false, false);
}

// Scope: "Layer5 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1453, 1454, {0,2,1,3});
  g->FuseDims(1454, 1455, 2, 2);
  g->Quantize(1455, 1457, 0.026451781392097473, 0);
  g->Transpose(3193, 2433, {1,0});
  g->Binary(ynn_binary_multiply, 2430, 2432, 2428);
  g->Dot(1457, 2433, YNN_INVALID_VALUE_ID, 2427, 1);
  g->DequantizeTensor(2427, YNN_INVALID_VALUE_ID, 2428, 2429);
  g->QuantizeTensor(2429, 2971, 2431, 1458);
  g->Dequantize(1458, 1459, 0.043322544544935226, 0);
}

// Scope: "Layer5 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1386, 1387);
  g->Reduce(ynn_reduce_sum, 1387, 2888, {2}, true);
  g->ShapeProduct(1387, 2887, {2});
  g->Binary(ynn_binary_divide, 2888, 2887, 1388);
  g->Binary(ynn_binary_add, 1388, 3004, 1389);
  g->Binary(ynn_binary_pow, 1389, 3006, 1390);
  g->Binary(ynn_binary_multiply, 1386, 1390, 1391);
  g->Convert(3180, 1392);
  g->Binary(ynn_binary_multiply, 1391, 1392, 1393);
  BuildLayer5AttentionKvProjection(ctx);
  BuildLayer5AttentionCacheUpdate(ctx);
  BuildLayer5AttentionQueryProjection(ctx);
  BuildLayer5AttentionSdpa(ctx);
  BuildLayer5AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1459, 1460);
  g->Reduce(ynn_reduce_sum, 1460, 2903, {2}, true);
  g->ShapeProduct(1460, 2902, {2});
  g->Binary(ynn_binary_divide, 2903, 2902, 1461);
  g->Binary(ynn_binary_add, 1461, 3004, 1462);
  g->Binary(ynn_binary_pow, 1462, 3006, 1463);
  g->Binary(ynn_binary_multiply, 1459, 1463, 1464);
  g->Convert(3187, 1465);
  g->Binary(ynn_binary_multiply, 1464, 1465, 1466);
  g->Binary(ynn_binary_add, 1386, 1466, 1468);
}

// Scope: "Layer5 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1468, 1469);
  g->Reduce(ynn_reduce_sum, 1469, 2905, {2}, true);
  g->ShapeProduct(1469, 2904, {2});
  g->Binary(ynn_binary_divide, 2905, 2904, 1470);
  g->Binary(ynn_binary_add, 1470, 3004, 1471);
  g->Binary(ynn_binary_pow, 1471, 3006, 1472);
  g->Binary(ynn_binary_multiply, 1468, 1472, 1473);
  g->Convert(3190, 1474);
  g->Binary(ynn_binary_multiply, 1473, 1474, 1475);
  g->Quantize(1475, 1476, 0.03518042340874672, 0);
  g->Transpose(3184, 2440, {1,0});
  g->Binary(ynn_binary_multiply, 2437, 2439, 2435);
  g->Dot(1476, 2440, YNN_INVALID_VALUE_ID, 2434, 1);
  g->DequantizeTensor(2434, YNN_INVALID_VALUE_ID, 2435, 2436);
  g->QuantizeTensor(2436, 2971, 2438, 1477);
  g->Dequantize(1477, 1479, 0.03567914664745331, 0);
  g->Transpose(3183, 2445, {1,0});
  g->Binary(ynn_binary_multiply, 2437, 2444, 2442);
  g->Dot(1476, 2445, YNN_INVALID_VALUE_ID, 2441, 1);
  g->DequantizeTensor(2441, YNN_INVALID_VALUE_ID, 2442, 2443);
  g->QuantizeTensor(2443, 2971, 2438, 1480);
  g->Dequantize(1480, 1481, 0.03567914664745331, 0);
  g->Polynomial(1481, 2908, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2908, 2909);
  g->Binary(ynn_binary_add, 2909, 2558, 2906);
  g->Binary(ynn_binary_multiply, 1481, 2556, 2907);
  g->Binary(ynn_binary_multiply, 2907, 2906, 1482);
  g->Binary(ynn_binary_multiply, 1479, 1482, 1483);
  g->Quantize(1483, 1484, 0.08415354788303375, 0);
  g->Transpose(3182, 2452, {1,0});
  g->Binary(ynn_binary_multiply, 2449, 2451, 2447);
  g->Dot(1484, 2452, YNN_INVALID_VALUE_ID, 2446, 1);
  g->DequantizeTensor(2446, YNN_INVALID_VALUE_ID, 2447, 2448);
  g->QuantizeTensor(2448, 2971, 2450, 1485);
  g->Dequantize(1485, 1486, 0.06301677227020264, 0);
  g->Unary(ynn_unary_square, 1486, 1487);
  g->Reduce(ynn_reduce_sum, 1487, 2911, {2}, true);
  g->ShapeProduct(1487, 2910, {2});
  g->Binary(ynn_binary_divide, 2911, 2910, 1489);
  g->Binary(ynn_binary_add, 1489, 3004, 1490);
  g->Binary(ynn_binary_pow, 1490, 3006, 1491);
  g->Binary(ynn_binary_multiply, 1486, 1491, 1492);
  g->Convert(3188, 1493);
  g->Binary(ynn_binary_multiply, 1492, 1493, 1494);
  g->Binary(ynn_binary_add, 1468, 1494, 1495);
}

// Scope: "Layer5 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(907, 1496, {0,0,5,0}, {-1,-1,1,-1});
  g->Reshape(1496, 1497, {1,0,256});
  g->Binary(ynn_binary_add, 1497, 3276, 1498);
  g->Binary(ynn_binary_multiply, 1498, 3003, 1500);
  g->Quantize(1495, 1501, 0.3165745139122009, 0);
  g->Transpose(3185, 2459, {1,0});
  g->Binary(ynn_binary_multiply, 2456, 2458, 2454);
  g->Dot(1501, 2459, YNN_INVALID_VALUE_ID, 2453, 1);
  g->DequantizeTensor(2453, YNN_INVALID_VALUE_ID, 2454, 2455);
  g->QuantizeTensor(2455, 2971, 2457, 1502);
  g->Dequantize(1502, 1503, 0.0393700897693634, 0);
  g->Polynomial(1503, 2914, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2914, 2915);
  g->Binary(ynn_binary_add, 2915, 2558, 2912);
  g->Binary(ynn_binary_multiply, 1503, 2556, 2913);
  g->Binary(ynn_binary_multiply, 2913, 2912, 1504);
  g->Binary(ynn_binary_multiply, 1504, 1500, 1505);
  g->Quantize(1505, 1506, 0.22933071851730347, 0);
  g->Transpose(3186, 2466, {1,0});
  g->Binary(ynn_binary_multiply, 2463, 2465, 2461);
  g->Dot(1506, 2466, YNN_INVALID_VALUE_ID, 2460, 1);
  g->DequantizeTensor(2460, YNN_INVALID_VALUE_ID, 2461, 2462);
  g->QuantizeTensor(2462, 2971, 2464, 1507);
  g->Dequantize(1507, 1508, 0.12322933226823807, 0);
  g->Unary(ynn_unary_square, 1508, 1509);
  g->Reduce(ynn_reduce_sum, 1509, 2917, {2}, true);
  g->ShapeProduct(1509, 2916, {2});
  g->Binary(ynn_binary_divide, 2917, 2916, 1511);
  g->Binary(ynn_binary_add, 1511, 3004, 1512);
  g->Binary(ynn_binary_pow, 1512, 3006, 1513);
  g->Binary(ynn_binary_multiply, 1508, 1513, 1514);
  g->Convert(3189, 1515);
  g->Binary(ynn_binary_multiply, 1514, 1515, 1516);
  g->Binary(ynn_binary_add, 1495, 1516, 1517);
  g->Convert(3181, 1518);
  g->Binary(ynn_binary_multiply, 1517, 1518, 1519);
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
  g->Quantize(1527, 1528, 0.341854453086853, 0);
  g->Transpose(3209, 2473, {1,0});
  g->Binary(ynn_binary_multiply, 2470, 2472, 2468);
  g->Dot(1528, 2473, YNN_INVALID_VALUE_ID, 2467, 1);
  g->DequantizeTensor(2467, YNN_INVALID_VALUE_ID, 2468, 2469);
  g->QuantizeTensor(2469, 2971, 2471, 1529);
  g->Dequantize(1529, 1530, 0.28740158677101135, 0);
  g->Reshape(1530, 1531, {1,0,1,256});
  g->Transpose(1531, 1534, {0,2,1,3});
  g->Unary(ynn_unary_square, 1534, 1535);
  g->Reduce(ynn_reduce_sum, 1535, 2921, {3}, true);
  g->ShapeProduct(1535, 2920, {3});
  g->Binary(ynn_binary_divide, 2921, 2920, 1536);
  g->Binary(ynn_binary_add, 1536, 3004, 1537);
  g->Binary(ynn_binary_pow, 1537, 3006, 1538);
  g->Binary(ynn_binary_multiply, 1534, 1538, 1539);
  g->Convert(3208, 1540);
  g->Binary(ynn_binary_multiply, 1539, 1540, 1541);
  g->Slice(1541, 1542, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1541, 1543, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1543, 1545);
  g->Concat({1545,1542}, 1546, 3);
  g->Binary(ynn_binary_multiply, 1541, 1015, 1547);
  g->Binary(ynn_binary_multiply, 1546, 1118, 1548);
  g->Binary(ynn_binary_add, 1547, 1548, 1549);
  g->Transpose(3213, 2478, {1,0});
  g->Binary(ynn_binary_multiply, 2470, 2477, 2475);
  g->Dot(1528, 2478, YNN_INVALID_VALUE_ID, 2474, 1);
  g->DequantizeTensor(2474, YNN_INVALID_VALUE_ID, 2475, 2476);
  g->QuantizeTensor(2476, 2971, 2471, 1550);
  g->Dequantize(1550, 1551, 0.28740158677101135, 0);
  g->Reshape(1551, 1552, {1,0,1,256});
  g->Transpose(1552, 1553, {0,2,1,3});
  g->Unary(ynn_unary_square, 1553, 1555);
  g->Reduce(ynn_reduce_sum, 1555, 2923, {3}, true);
  g->ShapeProduct(1555, 2922, {3});
  g->Binary(ynn_binary_divide, 2923, 2922, 1556);
  g->Binary(ynn_binary_add, 1556, 3004, 1557);
  g->Binary(ynn_binary_pow, 1557, 3006, 1558);
  g->Binary(ynn_binary_multiply, 1553, 1558, 1559);
}

// Scope: "Layer6 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(1549, 1560, 0.0057707298547029495, 0);
  g->Append(2983, 1560, 3293, 2, s2, s1);
  g->View(3293, 3322, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(3322, 1561, 0.0057707298547029495, 0);
  g->Quantize(1559, 1562, 0.047244105488061905, 0);
  g->Append(2998, 1562, 3308, 2, s2, s1);
  g->View(3308, 3336, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(3336, 1564, 0.047244105488061905, 0);
}

// Scope: "Layer6 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(3212, 2484, {1,0});
  g->Binary(ynn_binary_multiply, 2470, 2483, 2480);
  g->Dot(1528, 2484, YNN_INVALID_VALUE_ID, 2479, 1);
  g->DequantizeTensor(2479, YNN_INVALID_VALUE_ID, 2480, 2481);
  g->QuantizeTensor(2481, 2971, 2482, 1565);
  g->Dequantize(1565, 1566, 0.4566929042339325, 0);
  g->SplitDim(1566, 1567, 2, {8,256});
  g->Transpose(1567, 1568, {0,2,1,3});
  g->Unary(ynn_unary_square, 1568, 1569);
  g->Reduce(ynn_reduce_sum, 1569, 2925, {3}, true);
  g->ShapeProduct(1569, 2924, {3});
  g->Binary(ynn_binary_divide, 2925, 2924, 1570);
  g->Binary(ynn_binary_add, 1570, 3004, 1572);
  g->Binary(ynn_binary_pow, 1572, 3006, 1573);
  g->Binary(ynn_binary_multiply, 1568, 1573, 1574);
  g->Convert(3211, 1575);
  g->Binary(ynn_binary_multiply, 1574, 1575, 1576);
  g->Slice(1576, 1577, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1576, 1578, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1578, 1579);
  g->Concat({1579,1577}, 1580, 3);
  g->Binary(ynn_binary_multiply, 1576, 1015, 1581);
  g->Binary(ynn_binary_multiply, 1580, 1118, 1582);
  g->Binary(ynn_binary_add, 1581, 1582, 1583);
}

// Scope: "Layer6 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(1583, 1561, 1584, false, true);
  g->Mask(1584, 3019, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 3019, 2929, {-1}, true);
  g->Binary(ynn_binary_subtract, 3019, 2929, 2926);
  g->Unary(ynn_unary_exp, 2926, 2927);
  g->Reduce(ynn_reduce_sum, 2927, 2930, {-1}, true);
  g->Binary(ynn_binary_divide, 2558, 2930, 2928);
  g->Binary(ynn_binary_multiply, 2927, 2928, 1585);
  g->Matmul(1585, 1564, 1586, false, false);
}

// Scope: "Layer6 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1586, 1587, {0,2,1,3});
  g->FuseDims(1587, 1588, 2, 2);
  g->Quantize(1588, 1589, 0.0354330837726593, 0);
  g->Transpose(3210, 2491, {1,0});
  g->Binary(ynn_binary_multiply, 2488, 2490, 2486);
  g->Dot(1589, 2491, YNN_INVALID_VALUE_ID, 2485, 1);
  g->DequantizeTensor(2485, YNN_INVALID_VALUE_ID, 2486, 2487);
  g->QuantizeTensor(2487, 2971, 2489, 1590);
  g->Dequantize(1590, 1592, 0.05930274724960327, 0);
}

// Scope: "Layer6 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1519, 1520);
  g->Reduce(ynn_reduce_sum, 1520, 2919, {2}, true);
  g->ShapeProduct(1520, 2918, {2});
  g->Binary(ynn_binary_divide, 2919, 2918, 1522);
  g->Binary(ynn_binary_add, 1522, 3004, 1523);
  g->Binary(ynn_binary_pow, 1523, 3006, 1524);
  g->Binary(ynn_binary_multiply, 1519, 1524, 1525);
  g->Convert(3197, 1526);
  g->Binary(ynn_binary_multiply, 1525, 1526, 1527);
  BuildLayer6AttentionKvProjection(ctx);
  BuildLayer6AttentionCacheUpdate(ctx);
  BuildLayer6AttentionQueryProjection(ctx);
  BuildLayer6AttentionSdpa(ctx);
  BuildLayer6AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1592, 1593);
  g->Reduce(ynn_reduce_sum, 1593, 2937, {2}, true);
  g->ShapeProduct(1593, 2936, {2});
  g->Binary(ynn_binary_divide, 2937, 2936, 1594);
  g->Binary(ynn_binary_add, 1594, 3004, 1595);
  g->Binary(ynn_binary_pow, 1595, 3006, 1596);
  g->Binary(ynn_binary_multiply, 1592, 1596, 1597);
  g->Convert(3204, 1598);
  g->Binary(ynn_binary_multiply, 1597, 1598, 1599);
  g->Binary(ynn_binary_add, 1519, 1599, 1600);
}

// Scope: "Layer6 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1600, 1601);
  g->Reduce(ynn_reduce_sum, 1601, 2939, {2}, true);
  g->ShapeProduct(1601, 2938, {2});
  g->Binary(ynn_binary_divide, 2939, 2938, 1603);
  g->Binary(ynn_binary_add, 1603, 3004, 1604);
  g->Binary(ynn_binary_pow, 1604, 3006, 1605);
  g->Binary(ynn_binary_multiply, 1600, 1605, 1606);
  g->Convert(3207, 1607);
  g->Binary(ynn_binary_multiply, 1606, 1607, 1608);
  g->Quantize(1608, 1609, 0.02705955132842064, 0);
  g->Transpose(3201, 2498, {1,0});
  g->Binary(ynn_binary_multiply, 2495, 2497, 2493);
  g->Dot(1609, 2498, YNN_INVALID_VALUE_ID, 2492, 1);
  g->DequantizeTensor(2492, YNN_INVALID_VALUE_ID, 2493, 2494);
  g->QuantizeTensor(2494, 2971, 2496, 1610);
  g->Dequantize(1610, 1611, 0.02632874995470047, 0);
  g->Transpose(3200, 2503, {1,0});
  g->Binary(ynn_binary_multiply, 2495, 2502, 2500);
  g->Dot(1609, 2503, YNN_INVALID_VALUE_ID, 2499, 1);
  g->DequantizeTensor(2499, YNN_INVALID_VALUE_ID, 2500, 2501);
  g->QuantizeTensor(2501, 2971, 2496, 1613);
  g->Dequantize(1613, 1614, 0.02632874995470047, 0);
  g->Polynomial(1614, 2942, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2942, 2943);
  g->Binary(ynn_binary_add, 2943, 2558, 2940);
  g->Binary(ynn_binary_multiply, 1614, 2556, 2941);
  g->Binary(ynn_binary_multiply, 2941, 2940, 1615);
  g->Binary(ynn_binary_multiply, 1611, 1615, 1616);
  g->Quantize(1616, 1617, 0.039862215518951416, 0);
  g->Transpose(3199, 2509, {1,0});
  g->Binary(ynn_binary_multiply, 2394, 2508, 2505);
  g->Dot(1617, 2509, YNN_INVALID_VALUE_ID, 2504, 1);
  g->DequantizeTensor(2504, YNN_INVALID_VALUE_ID, 2505, 2506);
  g->QuantizeTensor(2506, 2971, 2507, 1618);
  g->Dequantize(1618, 1619, 0.019578030332922935, 0);
  g->Unary(ynn_unary_square, 1619, 1620);
  g->Reduce(ynn_reduce_sum, 1620, 2945, {2}, true);
  g->ShapeProduct(1620, 2944, {2});
  g->Binary(ynn_binary_divide, 2945, 2944, 1621);
  g->Binary(ynn_binary_add, 1621, 3004, 1622);
  g->Binary(ynn_binary_pow, 1622, 3006, 1624);
  g->Binary(ynn_binary_multiply, 1619, 1624, 1625);
  g->Convert(3205, 1626);
  g->Binary(ynn_binary_multiply, 1625, 1626, 1627);
  g->Binary(ynn_binary_add, 1600, 1627, 1628);
}

// Scope: "Layer6 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(907, 1629, {0,0,6,0}, {-1,-1,1,-1});
  g->Reshape(1629, 1630, {1,0,256});
  g->Binary(ynn_binary_add, 1630, 3277, 1631);
  g->Binary(ynn_binary_multiply, 1631, 3003, 1632);
  g->Quantize(1628, 1633, 0.34014976024627686, 0);
  g->Transpose(3202, 2516, {1,0});
  g->Binary(ynn_binary_multiply, 2513, 2515, 2511);
  g->Dot(1633, 2516, YNN_INVALID_VALUE_ID, 2510, 1);
  g->DequantizeTensor(2510, YNN_INVALID_VALUE_ID, 2511, 2512);
  g->QuantizeTensor(2512, 2971, 2514, 1636);
  g->Dequantize(1636, 1637, 0.04773623123764992, 0);
  g->Polynomial(1637, 2948, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2948, 2949);
  g->Binary(ynn_binary_add, 2949, 2558, 2946);
  g->Binary(ynn_binary_multiply, 1637, 2556, 2947);
  g->Binary(ynn_binary_multiply, 2947, 2946, 1638);
  g->Binary(ynn_binary_multiply, 1638, 1632, 1639);
  g->Quantize(1639, 1640, 0.12450788170099258, 0);
  g->Transpose(3203, 2522, {1,0});
  g->Binary(ynn_binary_multiply, 2096, 2521, 2518);
  g->Dot(1640, 2522, YNN_INVALID_VALUE_ID, 2517, 1);
  g->DequantizeTensor(2517, YNN_INVALID_VALUE_ID, 2518, 2519);
  g->QuantizeTensor(2519, 2971, 2520, 1641);
  g->Dequantize(1641, 1642, 0.07488936185836792, 0);
  g->Unary(ynn_unary_square, 1642, 1643);
  g->Reduce(ynn_reduce_sum, 1643, 2951, {2}, true);
  g->ShapeProduct(1643, 2950, {2});
  g->Binary(ynn_binary_divide, 2951, 2950, 1644);
  g->Binary(ynn_binary_add, 1644, 3004, 1645);
  g->Binary(ynn_binary_pow, 1645, 3006, 1647);
  g->Binary(ynn_binary_multiply, 1642, 1647, 1648);
  g->Convert(3206, 1649);
  g->Binary(ynn_binary_multiply, 1648, 1649, 1650);
  g->Binary(ynn_binary_add, 1628, 1650, 1651);
  g->Convert(3198, 1652);
  g->Binary(ynn_binary_multiply, 1651, 1652, 1653);
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
  g->Quantize(1661, 1662, 0.29519250988960266, 0);
  g->Transpose(3226, 2536, {1,0});
  g->Binary(ynn_binary_multiply, 2533, 2535, 2531);
  g->Dot(1662, 2536, YNN_INVALID_VALUE_ID, 2530, 1);
  g->DequantizeTensor(2530, YNN_INVALID_VALUE_ID, 2531, 2532);
  g->QuantizeTensor(2532, 2971, 2534, 1663);
  g->Dequantize(1663, 1664, 0.3681102395057678, 0);
  g->Reshape(1664, 1665, {1,0,1,256});
  g->Transpose(1665, 1666, {0,2,1,3});
  g->Unary(ynn_unary_square, 1666, 1667);
  g->Reduce(ynn_reduce_sum, 1667, 2955, {3}, true);
  g->ShapeProduct(1667, 2954, {3});
  g->Binary(ynn_binary_divide, 2955, 2954, 1669);
  g->Binary(ynn_binary_add, 1669, 3004, 1670);
  g->Binary(ynn_binary_pow, 1670, 3006, 1671);
  g->Binary(ynn_binary_multiply, 1666, 1671, 1672);
  g->Convert(3225, 1673);
  g->Binary(ynn_binary_multiply, 1672, 1673, 1674);
  g->Slice(1674, 1675, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1674, 1676, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1676, 1677);
  g->Concat({1677,1675}, 1678, 3);
  g->Binary(ynn_binary_multiply, 1674, 1015, 1680);
  g->Binary(ynn_binary_multiply, 1678, 1118, 1681);
  g->Binary(ynn_binary_add, 1680, 1681, 1682);
  g->Transpose(3230, 2541, {1,0});
  g->Binary(ynn_binary_multiply, 2533, 2540, 2538);
  g->Dot(1662, 2541, YNN_INVALID_VALUE_ID, 2537, 1);
  g->DequantizeTensor(2537, YNN_INVALID_VALUE_ID, 2538, 2539);
  g->QuantizeTensor(2539, 2971, 2534, 1683);
  g->Dequantize(1683, 1684, 0.3681102395057678, 0);
  g->Reshape(1684, 1685, {1,0,1,256});
  g->Transpose(1685, 1686, {0,2,1,3});
  g->Unary(ynn_unary_square, 1686, 1687);
  g->Reduce(ynn_reduce_sum, 1687, 2959, {3}, true);
  g->ShapeProduct(1687, 2958, {3});
  g->Binary(ynn_binary_divide, 2959, 2958, 1688);
  g->Binary(ynn_binary_add, 1688, 3004, 1690);
  g->Binary(ynn_binary_pow, 1690, 3006, 1691);
  g->Binary(ynn_binary_multiply, 1686, 1691, 1692);
}

// Scope: "Layer7 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(1682, 1693, 0.005869260523468256, 0);
  g->Append(2984, 1693, 3294, 2, s2, s1);
  g->View(3294, 3323, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(3323, 1694, 0.005869260523468256, 0);
  g->Quantize(1692, 1695, 0.047244105488061905, 0);
  g->Append(2999, 1695, 3309, 2, s2, s1);
  g->View(3309, 3337, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(3337, 1697, 0.047244105488061905, 0);
}

// Scope: "Layer7 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(3229, 2547, {1,0});
  g->Binary(ynn_binary_multiply, 2533, 2546, 2543);
  g->Dot(1662, 2547, YNN_INVALID_VALUE_ID, 2542, 1);
  g->DequantizeTensor(2542, YNN_INVALID_VALUE_ID, 2543, 2544);
  g->QuantizeTensor(2544, 2971, 2545, 1698);
  g->Dequantize(1698, 1699, 0.31496062874794006, 0);
  g->SplitDim(1699, 1700, 2, {8,256});
  g->Transpose(1700, 1701, {0,2,1,3});
  g->Unary(ynn_unary_square, 1701, 1702);
  g->Reduce(ynn_reduce_sum, 1702, 2961, {3}, true);
  g->ShapeProduct(1702, 2960, {3});
  g->Binary(ynn_binary_divide, 2961, 2960, 1703);
  g->Binary(ynn_binary_add, 1703, 3004, 1704);
  g->Binary(ynn_binary_pow, 1704, 3006, 1705);
  g->Binary(ynn_binary_multiply, 1701, 1705, 1707);
  g->Convert(3228, 1708);
  g->Binary(ynn_binary_multiply, 1707, 1708, 1709);
  g->Slice(1709, 1710, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1709, 1711, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1711, 1712);
  g->Concat({1712,1710}, 1713, 3);
  g->Binary(ynn_binary_multiply, 1709, 1015, 1714);
  g->Binary(ynn_binary_multiply, 1713, 1118, 1715);
  g->Binary(ynn_binary_add, 1714, 1715, 1716);
}

// Scope: "Layer7 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(1716, 1694, 1718, false, true);
  g->Mask(1718, 3020, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 3020, 2965, {-1}, true);
  g->Binary(ynn_binary_subtract, 3020, 2965, 2962);
  g->Unary(ynn_unary_exp, 2962, 2963);
  g->Reduce(ynn_reduce_sum, 2963, 2966, {-1}, true);
  g->Binary(ynn_binary_divide, 2558, 2966, 2964);
  g->Binary(ynn_binary_multiply, 2963, 2964, 1719);
  g->Matmul(1719, 1697, 1720, false, false);
}

// Scope: "Layer7 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1720, 1721, {0,2,1,3});
  g->FuseDims(1721, 1722, 2, 2);
  g->Quantize(1722, 1723, 0.028912410140037537, 0);
  g->Transpose(3227, 2554, {1,0});
  g->Binary(ynn_binary_multiply, 2551, 2553, 2549);
  g->Dot(1723, 2554, YNN_INVALID_VALUE_ID, 2548, 1);
  g->DequantizeTensor(2548, YNN_INVALID_VALUE_ID, 2549, 2550);
  g->QuantizeTensor(2550, 2971, 2552, 1724);
  g->Dequantize(1724, 1725, 0.025238478556275368, 0);
}

// Scope: "Layer7 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1653, 1654);
  g->Reduce(ynn_reduce_sum, 1654, 2953, {2}, true);
  g->ShapeProduct(1654, 2952, {2});
  g->Binary(ynn_binary_divide, 2953, 2952, 1655);
  g->Binary(ynn_binary_add, 1655, 3004, 1656);
  g->Binary(ynn_binary_pow, 1656, 3006, 1658);
  g->Binary(ynn_binary_multiply, 1653, 1658, 1659);
  g->Convert(3214, 1660);
  g->Binary(ynn_binary_multiply, 1659, 1660, 1661);
  BuildLayer7AttentionKvProjection(ctx);
  BuildLayer7AttentionCacheUpdate(ctx);
  BuildLayer7AttentionQueryProjection(ctx);
  BuildLayer7AttentionSdpa(ctx);
  BuildLayer7AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1725, 1726);
  g->Reduce(ynn_reduce_sum, 1726, 2968, {2}, true);
  g->ShapeProduct(1726, 2967, {2});
  g->Binary(ynn_binary_divide, 2968, 2967, 1728);
  g->Binary(ynn_binary_add, 1728, 3004, 1729);
  g->Binary(ynn_binary_pow, 1729, 3006, 1730);
  g->Binary(ynn_binary_multiply, 1725, 1730, 1731);
  g->Convert(3221, 1732);
  g->Binary(ynn_binary_multiply, 1731, 1732, 1733);
  g->Binary(ynn_binary_add, 1653, 1733, 1734);
}

// Scope: "Layer7 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1734, 1735);
  g->Reduce(ynn_reduce_sum, 1735, 2970, {2}, true);
  g->ShapeProduct(1735, 2969, {2});
  g->Binary(ynn_binary_divide, 2970, 2969, 1736);
  g->Binary(ynn_binary_add, 1736, 3004, 1737);
  g->Binary(ynn_binary_pow, 1737, 3006, 4);
  g->Binary(ynn_binary_multiply, 1734, 4, 5);
  g->Convert(3224, 6);
  g->Binary(ynn_binary_multiply, 5, 6, 7);
  g->Quantize(7, 8, 0.023717211559414864, 0);
  g->Transpose(3218, 1744, {1,0});
  g->Binary(ynn_binary_multiply, 1741, 1743, 1739);
  g->Dot(8, 1744, YNN_INVALID_VALUE_ID, 1738, 1);
  g->DequantizeTensor(1738, YNN_INVALID_VALUE_ID, 1739, 1740);
  g->QuantizeTensor(1740, 2971, 1742, 9);
  g->Dequantize(9, 10, 0.021899616345763206, 0);
  g->Transpose(3217, 1749, {1,0});
  g->Binary(ynn_binary_multiply, 1741, 1748, 1746);
  g->Dot(8, 1749, YNN_INVALID_VALUE_ID, 1745, 1);
  g->DequantizeTensor(1745, YNN_INVALID_VALUE_ID, 1746, 1747);
  g->QuantizeTensor(1747, 2971, 1742, 11);
  g->Dequantize(11, 12, 0.021899616345763206, 0);
  g->Polynomial(12, 2559, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2559, 2560);
  g->Binary(ynn_binary_add, 2560, 2558, 2555);
  g->Binary(ynn_binary_multiply, 12, 2556, 2557);
  g->Binary(ynn_binary_multiply, 2557, 2555, 14);
  g->Binary(ynn_binary_multiply, 10, 14, 15);
  g->Quantize(15, 16, 0.02202264778316021, 0);
  g->Transpose(3216, 1756, {1,0});
  g->Binary(ynn_binary_multiply, 1753, 1755, 1751);
  g->Dot(16, 1756, YNN_INVALID_VALUE_ID, 1750, 1);
  g->DequantizeTensor(1750, YNN_INVALID_VALUE_ID, 1751, 1752);
  g->QuantizeTensor(1752, 2971, 1754, 17);
  g->Dequantize(17, 18, 0.01081059779971838, 0);
  g->Unary(ynn_unary_square, 18, 19);
  g->Reduce(ynn_reduce_sum, 19, 2562, {2}, true);
  g->ShapeProduct(19, 2561, {2});
  g->Binary(ynn_binary_divide, 2562, 2561, 20);
  g->Binary(ynn_binary_add, 20, 3004, 21);
  g->Binary(ynn_binary_pow, 21, 3006, 22);
  g->Binary(ynn_binary_multiply, 18, 22, 23);
  g->Convert(3222, 25);
  g->Binary(ynn_binary_multiply, 23, 25, 26);
  g->Binary(ynn_binary_add, 1734, 26, 27);
}

// Scope: "Layer7 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(907, 28, {0,0,7,0}, {-1,-1,1,-1});
  g->Reshape(28, 29, {1,0,256});
  g->Binary(ynn_binary_add, 29, 3278, 30);
  g->Binary(ynn_binary_multiply, 30, 3003, 31);
  g->Quantize(27, 32, 0.15832224488258362, 0);
  g->Transpose(3219, 1763, {1,0});
  g->Binary(ynn_binary_multiply, 1760, 1762, 1758);
  g->Dot(32, 1763, YNN_INVALID_VALUE_ID, 1757, 1);
  g->DequantizeTensor(1757, YNN_INVALID_VALUE_ID, 1758, 1759);
  g->QuantizeTensor(1759, 2971, 1761, 33);
  g->Dequantize(33, 34, 0.055118121206760406, 0);
  g->Polynomial(34, 2567, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2567, 2568);
  g->Binary(ynn_binary_add, 2568, 2558, 2565);
  g->Binary(ynn_binary_multiply, 34, 2556, 2566);
  g->Binary(ynn_binary_multiply, 2566, 2565, 36);
  g->Binary(ynn_binary_multiply, 36, 31, 37);
  g->Quantize(37, 38, 0.22834646701812744, 0);
  g->Transpose(3220, 1770, {1,0});
  g->Binary(ynn_binary_multiply, 1767, 1769, 1765);
  g->Dot(38, 1770, YNN_INVALID_VALUE_ID, 1764, 1);
  g->DequantizeTensor(1764, YNN_INVALID_VALUE_ID, 1765, 1766);
  g->QuantizeTensor(1766, 2971, 1768, 39);
  g->Dequantize(39, 40, 0.08292699605226517, 0);
  g->Unary(ynn_unary_square, 40, 41);
  g->Reduce(ynn_reduce_sum, 41, 2570, {2}, true);
  g->ShapeProduct(41, 2569, {2});
  g->Binary(ynn_binary_divide, 2570, 2569, 42);
  g->Binary(ynn_binary_add, 42, 3004, 43);
  g->Binary(ynn_binary_pow, 43, 3006, 44);
  g->Binary(ynn_binary_multiply, 40, 44, 45);
  g->Convert(3223, 47);
  g->Binary(ynn_binary_multiply, 45, 47, 48);
  g->Binary(ynn_binary_add, 27, 48, 49);
  g->Convert(3215, 50);
  g->Binary(ynn_binary_multiply, 49, 50, 51);
}

// Scope: "Layer7"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7(Context& ctx) {
  BuildLayer7Attention(ctx);
  BuildLayer7Mlp(ctx);
  BuildLayer7PerLayerEmbedding(ctx);
}

// Scope: "Layer8 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(59, 60, 0.0820433720946312, 0);
  g->Transpose(3243, 1777, {1,0});
  g->Binary(ynn_binary_multiply, 1774, 1776, 1772);
  g->Dot(60, 1777, YNN_INVALID_VALUE_ID, 1771, 1);
  g->DequantizeTensor(1771, YNN_INVALID_VALUE_ID, 1772, 1773);
  g->QuantizeTensor(1773, 2971, 1775, 61);
  g->Dequantize(61, 62, 0.09251969307661057, 0);
  g->Reshape(62, 63, {1,0,1,256});
  g->Transpose(63, 64, {0,2,1,3});
  g->Unary(ynn_unary_square, 64, 65);
  g->Reduce(ynn_reduce_sum, 65, 2574, {3}, true);
  g->ShapeProduct(65, 2573, {3});
  g->Binary(ynn_binary_divide, 2574, 2573, 66);
  g->Binary(ynn_binary_add, 66, 3004, 67);
  g->Binary(ynn_binary_pow, 67, 3006, 69);
  g->Binary(ynn_binary_multiply, 64, 69, 70);
  g->Convert(3242, 71);
  g->Binary(ynn_binary_multiply, 70, 71, 72);
  g->Slice(72, 73, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(72, 74, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 74, 75);
  g->Concat({75,73}, 76, 3);
  g->Binary(ynn_binary_multiply, 72, 1015, 77);
  g->Binary(ynn_binary_multiply, 76, 1118, 78);
  g->Binary(ynn_binary_add, 77, 78, 80);
  g->Transpose(3247, 1782, {1,0});
  g->Binary(ynn_binary_multiply, 1774, 1781, 1779);
  g->Dot(60, 1782, YNN_INVALID_VALUE_ID, 1778, 1);
  g->DequantizeTensor(1778, YNN_INVALID_VALUE_ID, 1779, 1780);
  g->QuantizeTensor(1780, 2971, 1775, 81);
  g->Dequantize(81, 82, 0.09251969307661057, 0);
  g->Reshape(82, 83, {1,0,1,256});
  g->Transpose(83, 84, {0,2,1,3});
  g->Unary(ynn_unary_square, 84, 85);
  g->Reduce(ynn_reduce_sum, 85, 2576, {3}, true);
  g->ShapeProduct(85, 2575, {3});
  g->Binary(ynn_binary_divide, 2576, 2575, 86);
  g->Binary(ynn_binary_add, 86, 3004, 87);
  g->Binary(ynn_binary_pow, 87, 3006, 88);
  g->Binary(ynn_binary_multiply, 84, 88, 90);
}

// Scope: "Layer8 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(80, 91, 0.006215503439307213, 0);
  g->Append(2985, 91, 3295, 2, s2, s1);
  g->View(3295, 3324, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(3324, 92, 0.006215503439307213, 0);
  g->Quantize(90, 93, 0.047244105488061905, 0);
  g->Append(3000, 93, 3310, 2, s2, s1);
  g->View(3310, 3338, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(3338, 94, 0.047244105488061905, 0);
}

// Scope: "Layer8 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(3246, 1795, {1,0});
  g->Binary(ynn_binary_multiply, 1774, 1794, 1791);
  g->Dot(60, 1795, YNN_INVALID_VALUE_ID, 1790, 1);
  g->DequantizeTensor(1790, YNN_INVALID_VALUE_ID, 1791, 1792);
  g->QuantizeTensor(1792, 2971, 1793, 96);
  g->Dequantize(96, 97, 0.1250000149011612, 0);
  g->SplitDim(97, 98, 2, {8,256});
  g->Transpose(98, 99, {0,2,1,3});
  g->Unary(ynn_unary_square, 99, 100);
  g->Reduce(ynn_reduce_sum, 100, 2578, {3}, true);
  g->ShapeProduct(100, 2577, {3});
  g->Binary(ynn_binary_divide, 2578, 2577, 101);
  g->Binary(ynn_binary_add, 101, 3004, 102);
  g->Binary(ynn_binary_pow, 102, 3006, 103);
  g->Binary(ynn_binary_multiply, 99, 103, 104);
  g->Convert(3245, 105);
  g->Binary(ynn_binary_multiply, 104, 105, 108);
  g->Slice(108, 109, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(108, 110, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 110, 111);
  g->Concat({111,109}, 112, 3);
  g->Binary(ynn_binary_multiply, 108, 1015, 113);
  g->Binary(ynn_binary_multiply, 112, 1118, 114);
  g->Binary(ynn_binary_add, 113, 114, 115);
}

// Scope: "Layer8 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(115, 92, 116, false, true);
  g->Mask(116, 3021, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 3021, 2582, {-1}, true);
  g->Binary(ynn_binary_subtract, 3021, 2582, 2579);
  g->Unary(ynn_unary_exp, 2579, 2580);
  g->Reduce(ynn_reduce_sum, 2580, 2583, {-1}, true);
  g->Binary(ynn_binary_divide, 2558, 2583, 2581);
  g->Binary(ynn_binary_multiply, 2580, 2581, 117);
  g->Matmul(117, 94, 118, false, false);
}

// Scope: "Layer8 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(118, 119, {0,2,1,3});
  g->FuseDims(119, 120, 2, 2);
  g->Quantize(120, 121, 0.025713592767715454, 0);
  g->Transpose(3244, 1802, {1,0});
  g->Binary(ynn_binary_multiply, 1799, 1801, 1797);
  g->Dot(121, 1802, YNN_INVALID_VALUE_ID, 1796, 1);
  g->DequantizeTensor(1796, YNN_INVALID_VALUE_ID, 1797, 1798);
  g->QuantizeTensor(1798, 2971, 1800, 122);
  g->Dequantize(122, 123, 0.022537967190146446, 0);
}

// Scope: "Layer8 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 51, 52);
  g->Reduce(ynn_reduce_sum, 52, 2572, {2}, true);
  g->ShapeProduct(52, 2571, {2});
  g->Binary(ynn_binary_divide, 2572, 2571, 53);
  g->Binary(ynn_binary_add, 53, 3004, 54);
  g->Binary(ynn_binary_pow, 54, 3006, 55);
  g->Binary(ynn_binary_multiply, 51, 55, 56);
  g->Convert(3231, 58);
  g->Binary(ynn_binary_multiply, 56, 58, 59);
  BuildLayer8AttentionKvProjection(ctx);
  BuildLayer8AttentionCacheUpdate(ctx);
  BuildLayer8AttentionQueryProjection(ctx);
  BuildLayer8AttentionSdpa(ctx);
  BuildLayer8AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 123, 124);
  g->Reduce(ynn_reduce_sum, 124, 2585, {2}, true);
  g->ShapeProduct(124, 2584, {2});
  g->Binary(ynn_binary_divide, 2585, 2584, 125);
  g->Binary(ynn_binary_add, 125, 3004, 126);
  g->Binary(ynn_binary_pow, 126, 3006, 128);
  g->Binary(ynn_binary_multiply, 123, 128, 129);
  g->Convert(3238, 130);
  g->Binary(ynn_binary_multiply, 129, 130, 131);
  g->Binary(ynn_binary_add, 51, 131, 132);
}

// Scope: "Layer8 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 132, 133);
  g->Reduce(ynn_reduce_sum, 133, 2587, {2}, true);
  g->ShapeProduct(133, 2586, {2});
  g->Binary(ynn_binary_divide, 2587, 2586, 134);
  g->Binary(ynn_binary_add, 134, 3004, 135);
  g->Binary(ynn_binary_pow, 135, 3006, 136);
  g->Binary(ynn_binary_multiply, 132, 136, 137);
  g->Convert(3241, 139);
  g->Binary(ynn_binary_multiply, 137, 139, 140);
  g->Quantize(140, 141, 0.015404289588332176, 0);
  g->Transpose(3235, 1814, {1,0});
  g->Binary(ynn_binary_multiply, 1811, 1813, 1809);
  g->Dot(141, 1814, YNN_INVALID_VALUE_ID, 1808, 1);
  g->DequantizeTensor(1808, YNN_INVALID_VALUE_ID, 1809, 1810);
  g->QuantizeTensor(1810, 2971, 1812, 142);
  g->Dequantize(142, 143, 0.018823828548192978, 0);
  g->Transpose(3234, 1819, {1,0});
  g->Binary(ynn_binary_multiply, 1811, 1818, 1816);
  g->Dot(141, 1819, YNN_INVALID_VALUE_ID, 1815, 1);
  g->DequantizeTensor(1815, YNN_INVALID_VALUE_ID, 1816, 1817);
  g->QuantizeTensor(1817, 2971, 1812, 144);
  g->Dequantize(144, 145, 0.018823828548192978, 0);
  g->Polynomial(145, 2590, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2590, 2591);
  g->Binary(ynn_binary_add, 2591, 2558, 2588);
  g->Binary(ynn_binary_multiply, 145, 2556, 2589);
  g->Binary(ynn_binary_multiply, 2589, 2588, 146);
  g->Binary(ynn_binary_multiply, 143, 146, 147);
  g->Quantize(147, 149, 0.012610738165676594, 0);
  g->Transpose(3233, 1826, {1,0});
  g->Binary(ynn_binary_multiply, 1823, 1825, 1821);
  g->Dot(149, 1826, YNN_INVALID_VALUE_ID, 1820, 1);
  g->DequantizeTensor(1820, YNN_INVALID_VALUE_ID, 1821, 1822);
  g->QuantizeTensor(1822, 2971, 1824, 150);
  g->Dequantize(150, 151, 0.009271269664168358, 0);
  g->Unary(ynn_unary_square, 151, 152);
  g->Reduce(ynn_reduce_sum, 152, 2597, {2}, true);
  g->ShapeProduct(152, 2596, {2});
  g->Binary(ynn_binary_divide, 2597, 2596, 153);
  g->Binary(ynn_binary_add, 153, 3004, 154);
  g->Binary(ynn_binary_pow, 154, 3006, 155);
  g->Binary(ynn_binary_multiply, 151, 155, 156);
  g->Convert(3239, 157);
  g->Binary(ynn_binary_multiply, 156, 157, 158);
  g->Binary(ynn_binary_add, 132, 158, 160);
}

// Scope: "Layer8 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(907, 161, {0,0,8,0}, {-1,-1,1,-1});
  g->Reshape(161, 162, {1,0,256});
  g->Binary(ynn_binary_add, 162, 3279, 163);
  g->Binary(ynn_binary_multiply, 163, 3003, 164);
  g->Quantize(160, 165, 0.19172413647174835, 0);
  g->Transpose(3236, 1833, {1,0});
  g->Binary(ynn_binary_multiply, 1830, 1832, 1828);
  g->Dot(165, 1833, YNN_INVALID_VALUE_ID, 1827, 1);
  g->DequantizeTensor(1827, YNN_INVALID_VALUE_ID, 1828, 1829);
  g->QuantizeTensor(1829, 2971, 1831, 166);
  g->Dequantize(166, 167, 0.11515748500823975, 0);
  g->Polynomial(167, 2600, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2600, 2601);
  g->Binary(ynn_binary_add, 2601, 2558, 2598);
  g->Binary(ynn_binary_multiply, 167, 2556, 2599);
  g->Binary(ynn_binary_multiply, 2599, 2598, 168);
  g->Binary(ynn_binary_multiply, 168, 164, 169);
  g->Quantize(169, 171, 0.787401556968689, 0);
  g->Transpose(3237, 1840, {1,0});
  g->Binary(ynn_binary_multiply, 1837, 1839, 1835);
  g->Dot(171, 1840, YNN_INVALID_VALUE_ID, 1834, 1);
  g->DequantizeTensor(1834, YNN_INVALID_VALUE_ID, 1835, 1836);
  g->QuantizeTensor(1836, 2971, 1838, 172);
  g->Dequantize(172, 173, 0.2950586676597595, 0);
  g->Unary(ynn_unary_square, 173, 174);
  g->Reduce(ynn_reduce_sum, 174, 2603, {2}, true);
  g->ShapeProduct(174, 2602, {2});
  g->Binary(ynn_binary_divide, 2603, 2602, 175);
  g->Binary(ynn_binary_add, 175, 3004, 176);
  g->Binary(ynn_binary_pow, 176, 3006, 177);
  g->Binary(ynn_binary_multiply, 173, 177, 178);
  g->Convert(3240, 179);
  g->Binary(ynn_binary_multiply, 178, 179, 180);
  g->Binary(ynn_binary_add, 160, 180, 182);
  g->Convert(3232, 183);
  g->Binary(ynn_binary_multiply, 182, 183, 184);
}

// Scope: "Layer8"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8(Context& ctx) {
  BuildLayer8Attention(ctx);
  BuildLayer8Mlp(ctx);
  BuildLayer8PerLayerEmbedding(ctx);
}

}  // namespace BuildGemma4PrefillSource
