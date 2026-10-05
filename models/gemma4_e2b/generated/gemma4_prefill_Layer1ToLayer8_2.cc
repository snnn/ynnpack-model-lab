// Generated YNNPACK builder; do not edit.
#include "gemma4_prefill_builder.h"

namespace BuildGemma4PrefillSource {

// Scope: "Layer1 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(493, 503, 0.4842597544193268, 0);
  g->Transpose(3063, 1970, {1,0});
  g->Binary(ynn_binary_multiply, 1967, 1969, 1965);
  g->Dot(503, 1970, YNN_INVALID_VALUE_ID, 1964, 1);
  g->DequantizeTensor(1964, YNN_INVALID_VALUE_ID, 1965, 1966);
  g->QuantizeTensor(1966, 2982, 1968, 514);
  g->Dequantize(514, 525, 0.41535434126853943, 0);
  g->Reshape(525, 536, {1,0,1,256});
  g->Transpose(536, 547, {0,2,1,3});
  g->Unary(ynn_unary_square, 547, 558);
  g->Reduce(ynn_reduce_sum, 558, 2691, {3}, true);
  g->ShapeProduct(558, 2690, {3});
  g->Binary(ynn_binary_divide, 2691, 2690, 569);
  g->Binary(ynn_binary_add, 569, 3016, 580);
  g->Unary(ynn_unary_rsqrt, 580, 591);
  g->Binary(ynn_binary_multiply, 547, 591, 601);
  g->Binary(ynn_binary_multiply, 601, 3062, 607);
  g->Slice(607, 618, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(607, 630, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 630, 640);
  g->Concat({640,618}, 651, 3);
  g->Binary(ynn_binary_multiply, 607, 1096, 661);
  g->Binary(ynn_binary_multiply, 651, 1199, 672);
  g->Binary(ynn_binary_add, 661, 672, 683);
  g->Transpose(3067, 2065, {1,0});
  g->Binary(ynn_binary_multiply, 1967, 2064, 2062);
  g->Dot(503, 2065, YNN_INVALID_VALUE_ID, 2061, 1);
  g->DequantizeTensor(2061, YNN_INVALID_VALUE_ID, 2062, 2063);
  g->QuantizeTensor(2063, 2982, 1968, 704);
  g->Dequantize(704, 715, 0.41535434126853943, 0);
  g->Reshape(715, 726, {1,0,1,256});
  g->Transpose(726, 737, {0,2,1,3});
  g->Unary(ynn_unary_square, 737, 743);
  g->Reduce(ynn_reduce_sum, 743, 2734, {3}, true);
  g->ShapeProduct(743, 2733, {3});
  g->Binary(ynn_binary_divide, 2734, 2733, 754);
  g->Binary(ynn_binary_add, 754, 3016, 764);
  g->Unary(ynn_unary_rsqrt, 764, 775);
  g->Binary(ynn_binary_multiply, 737, 775, 786);
}

// Scope: "Layer1 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(683, 796, 0.005761673673987389, 0);
  g->Append(2984, 796, 3294, 2, s2, s1);
  g->View(3294, 3324, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(786, 827, 0.047244105488061905, 0);
  g->Append(2999, 827, 3309, 2, s2, s1);
  g->View(3309, 3338, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer1 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(3066, 2140, {1,0});
  g->Binary(ynn_binary_multiply, 1967, 2139, 2136);
  g->Dot(503, 2140, YNN_INVALID_VALUE_ID, 2135, 1);
  g->DequantizeTensor(2135, YNN_INVALID_VALUE_ID, 2136, 2137);
  g->QuantizeTensor(2137, 2982, 2138, 866);
  g->Dequantize(866, 868, 0.35039371252059937, 0);
  g->SplitDim(868, 869, 2, {8,256});
  g->Transpose(869, 870, {0,2,1,3});
  g->Unary(ynn_unary_square, 870, 871);
  g->Reduce(ynn_reduce_sum, 871, 2765, {3}, true);
  g->ShapeProduct(871, 2764, {3});
  g->Binary(ynn_binary_divide, 2765, 2764, 872);
  g->Binary(ynn_binary_add, 872, 3016, 873);
  g->Unary(ynn_unary_rsqrt, 873, 875);
  g->Binary(ynn_binary_multiply, 870, 875, 876);
  g->Binary(ynn_binary_multiply, 876, 3065, 877);
  g->Slice(877, 878, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(877, 879, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 879, 880);
  g->Concat({880,878}, 881, 3);
  g->Binary(ynn_binary_multiply, 877, 1096, 882);
  g->Binary(ynn_binary_multiply, 881, 1199, 883);
  g->Binary(ynn_binary_add, 882, 883, 884);
}

// Scope: "Layer1 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(3324, 887, 0.005761673673987389, 0);
  g->Dequantize(3338, 888, 0.047244105488061905, 0);
  g->Matmul(884, 887, 889, false, true);
  g->Mask(889, 3021, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 3021, 2769, {-1}, true);
  g->Binary(ynn_binary_subtract, 3021, 2769, 2766);
  g->Unary(ynn_unary_exp, 2766, 2767);
  g->Reduce(ynn_reduce_sum, 2767, 2770, {-1}, true);
  g->Binary(ynn_binary_divide, 2545, 2770, 2768);
  g->Binary(ynn_binary_multiply, 2767, 2768, 890);
  g->Matmul(890, 888, 891, false, false);
}

// Scope: "Layer1 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(891, 892, {0,2,1,3});
  g->FuseDims(892, 893, 2, 2);
  g->Quantize(893, 894, 0.023129930719733238, 0);
  g->Transpose(3064, 2147, {1,0});
  g->Binary(ynn_binary_multiply, 2144, 2146, 2142);
  g->Dot(894, 2147, YNN_INVALID_VALUE_ID, 2141, 1);
  g->DequantizeTensor(2141, YNN_INVALID_VALUE_ID, 2142, 2143);
  g->QuantizeTensor(2143, 2982, 2145, 895);
  g->Dequantize(895, 897, 0.03322756290435791, 0);
}

// Scope: "Layer1 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 433, 444);
  g->Reduce(ynn_reduce_sum, 444, 2662, {2}, true);
  g->ShapeProduct(444, 2661, {2});
  g->Binary(ynn_binary_divide, 2662, 2661, 455);
  g->Binary(ynn_binary_add, 455, 3016, 465);
  g->Unary(ynn_unary_rsqrt, 465, 474);
  g->Binary(ynn_binary_multiply, 433, 474, 482);
  g->Binary(ynn_binary_multiply, 482, 3051, 493);
  BuildLayer1AttentionKvProjection(ctx);
  BuildLayer1AttentionCacheUpdate(ctx);
  BuildLayer1AttentionQueryProjection(ctx);
  BuildLayer1AttentionSdpa(ctx);
  BuildLayer1AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 897, 898);
  g->Reduce(ynn_reduce_sum, 898, 2772, {2}, true);
  g->ShapeProduct(898, 2771, {2});
  g->Binary(ynn_binary_divide, 2772, 2771, 899);
  g->Binary(ynn_binary_add, 899, 3016, 900);
  g->Unary(ynn_unary_rsqrt, 900, 901);
  g->Binary(ynn_binary_multiply, 897, 901, 902);
  g->Binary(ynn_binary_multiply, 902, 3058, 903);
  g->Binary(ynn_binary_add, 903, 433, 904);
}

// Scope: "Layer1 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 904, 905);
  g->Reduce(ynn_reduce_sum, 905, 2774, {2}, true);
  g->ShapeProduct(905, 2773, {2});
  g->Binary(ynn_binary_divide, 2774, 2773, 906);
  g->Binary(ynn_binary_add, 906, 3016, 908);
  g->Unary(ynn_unary_rsqrt, 908, 909);
  g->Binary(ynn_binary_multiply, 904, 909, 910);
  g->Binary(ynn_binary_multiply, 910, 3061, 911);
  g->Quantize(911, 912, 0.08275254815816879, 0);
  g->Transpose(3055, 2161, {1,0});
  g->Binary(ynn_binary_multiply, 2158, 2160, 2156);
  g->Dot(912, 2161, YNN_INVALID_VALUE_ID, 2155, 1);
  g->DequantizeTensor(2155, YNN_INVALID_VALUE_ID, 2156, 2157);
  g->QuantizeTensor(2157, 2982, 2159, 913);
  g->Dequantize(913, 914, 0.06889764219522476, 0);
  g->Transpose(3054, 2166, {1,0});
  g->Binary(ynn_binary_multiply, 2158, 2165, 2163);
  g->Dot(912, 2166, YNN_INVALID_VALUE_ID, 2162, 1);
  g->DequantizeTensor(2162, YNN_INVALID_VALUE_ID, 2163, 2164);
  g->QuantizeTensor(2164, 2982, 2159, 915);
  g->Dequantize(915, 916, 0.06889764219522476, 0);
  g->Polynomial(916, 2777, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2777, 2778);
  g->Binary(ynn_binary_add, 2778, 2545, 2775);
  g->Binary(ynn_binary_multiply, 916, 2543, 2776);
  g->Binary(ynn_binary_multiply, 2776, 2775, 918);
  g->Binary(ynn_binary_multiply, 914, 918, 919);
  g->Quantize(919, 920, 0.21062994003295898, 0);
  g->Transpose(3053, 2173, {1,0});
  g->Binary(ynn_binary_multiply, 2170, 2172, 2168);
  g->Dot(920, 2173, YNN_INVALID_VALUE_ID, 2167, 1);
  g->DequantizeTensor(2167, YNN_INVALID_VALUE_ID, 2168, 2169);
  g->QuantizeTensor(2169, 2982, 2171, 921);
  g->Dequantize(921, 922, 0.09257561713457108, 0);
  g->Unary(ynn_unary_square, 922, 923);
  g->Reduce(ynn_reduce_sum, 923, 2780, {2}, true);
  g->ShapeProduct(923, 2779, {2});
  g->Binary(ynn_binary_divide, 2780, 2779, 924);
  g->Binary(ynn_binary_add, 924, 3016, 925);
  g->Unary(ynn_unary_rsqrt, 925, 926);
  g->Binary(ynn_binary_multiply, 922, 926, 927);
  g->Binary(ynn_binary_multiply, 927, 3059, 929);
  g->Binary(ynn_binary_add, 929, 904, 930);
}

// Scope: "Layer1 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer1PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(421, 931, {0,0,1,0}, {-1,-1,1,-1});
  g->Reshape(931, 932, {1,0,256});
  g->Unary(ynn_unary_square, 932, 933);
  g->Reduce(ynn_reduce_sum, 933, 2782, {2}, true);
  g->ShapeProduct(933, 2781, {2});
  g->Binary(ynn_binary_divide, 2782, 2781, 934);
  g->Binary(ynn_binary_add, 934, 3016, 935);
  g->Unary(ynn_unary_rsqrt, 935, 936);
  g->Binary(ynn_binary_multiply, 932, 936, 937);
  g->Binary(ynn_binary_multiply, 937, 3277, 938);
  g->Binary(ynn_binary_multiply, 3279, 3019, 940);
  g->Binary(ynn_binary_add, 938, 940, 941);
  g->Binary(ynn_binary_multiply, 941, 3014, 942);
  g->Quantize(930, 943, 0.4206320643424988, 0);
  g->Transpose(3056, 2180, {1,0});
  g->Binary(ynn_binary_multiply, 2177, 2179, 2175);
  g->Dot(943, 2180, YNN_INVALID_VALUE_ID, 2174, 1);
  g->DequantizeTensor(2174, YNN_INVALID_VALUE_ID, 2175, 2176);
  g->QuantizeTensor(2176, 2982, 2178, 944);
  g->Dequantize(944, 945, 0.010150108486413956, 0);
  g->Polynomial(945, 2785, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2785, 2786);
  g->Binary(ynn_binary_add, 2786, 2545, 2783);
  g->Binary(ynn_binary_multiply, 945, 2543, 2784);
  g->Binary(ynn_binary_multiply, 2784, 2783, 946);
  g->Binary(ynn_binary_multiply, 946, 942, 947);
  g->Quantize(947, 948, 0.026820875704288483, 0);
  g->Transpose(3057, 2187, {1,0});
  g->Binary(ynn_binary_multiply, 2184, 2186, 2182);
  g->Dot(948, 2187, YNN_INVALID_VALUE_ID, 2181, 1);
  g->DequantizeTensor(2181, YNN_INVALID_VALUE_ID, 2182, 2183);
  g->QuantizeTensor(2183, 2982, 2185, 949);
  g->Dequantize(949, 951, 0.020895034074783325, 0);
  g->Unary(ynn_unary_square, 951, 952);
  g->Reduce(ynn_reduce_sum, 952, 2788, {2}, true);
  g->ShapeProduct(952, 2787, {2});
  g->Binary(ynn_binary_divide, 2788, 2787, 953);
  g->Binary(ynn_binary_add, 953, 3016, 954);
  g->Unary(ynn_unary_rsqrt, 954, 955);
  g->Binary(ynn_binary_multiply, 951, 955, 956);
  g->Binary(ynn_binary_multiply, 956, 3060, 957);
  g->Binary(ynn_binary_add, 930, 957, 958);
  g->Binary(ynn_binary_multiply, 958, 3052, 959);
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
  g->Quantize(966, 967, 0.15746013820171356, 0);
  g->Transpose(3152, 2194, {1,0});
  g->Binary(ynn_binary_multiply, 2191, 2193, 2189);
  g->Dot(967, 2194, YNN_INVALID_VALUE_ID, 2188, 1);
  g->DequantizeTensor(2188, YNN_INVALID_VALUE_ID, 2189, 2190);
  g->QuantizeTensor(2190, 2982, 2192, 968);
  g->Dequantize(968, 969, 0.180118128657341, 0);
  g->Reshape(969, 970, {1,0,1,256});
  g->Transpose(970, 971, {0,2,1,3});
  g->Unary(ynn_unary_square, 971, 973);
  g->Reduce(ynn_reduce_sum, 973, 2794, {3}, true);
  g->ShapeProduct(973, 2793, {3});
  g->Binary(ynn_binary_divide, 2794, 2793, 974);
  g->Binary(ynn_binary_add, 974, 3016, 975);
  g->Unary(ynn_unary_rsqrt, 975, 976);
  g->Binary(ynn_binary_multiply, 971, 976, 977);
  g->Binary(ynn_binary_multiply, 977, 3151, 978);
  g->Slice(978, 979, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(978, 980, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 980, 981);
  g->Concat({981,979}, 982, 3);
  g->Binary(ynn_binary_multiply, 978, 1096, 984);
  g->Binary(ynn_binary_multiply, 982, 1199, 985);
  g->Binary(ynn_binary_add, 984, 985, 986);
  g->Transpose(3156, 2199, {1,0});
  g->Binary(ynn_binary_multiply, 2191, 2198, 2196);
  g->Dot(967, 2199, YNN_INVALID_VALUE_ID, 2195, 1);
  g->DequantizeTensor(2195, YNN_INVALID_VALUE_ID, 2196, 2197);
  g->QuantizeTensor(2197, 2982, 2192, 987);
  g->Dequantize(987, 988, 0.180118128657341, 0);
  g->Reshape(988, 989, {1,0,1,256});
  g->Transpose(989, 990, {0,2,1,3});
  g->Unary(ynn_unary_square, 990, 991);
  g->Reduce(ynn_reduce_sum, 991, 2796, {3}, true);
  g->ShapeProduct(991, 2795, {3});
  g->Binary(ynn_binary_divide, 2796, 2795, 992);
  g->Binary(ynn_binary_add, 992, 3016, 995);
  g->Unary(ynn_unary_rsqrt, 995, 996);
  g->Binary(ynn_binary_multiply, 990, 996, 997);
}

// Scope: "Layer2 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(986, 998, 0.005684707313776016, 0);
  g->Append(2990, 998, 3300, 2, s2, s1);
  g->View(3300, 3329, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(997, 999, 0.047244105488061905, 0);
  g->Append(3005, 999, 3315, 2, s2, s1);
  g->View(3315, 3343, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer2 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(3155, 2205, {1,0});
  g->Binary(ynn_binary_multiply, 2191, 2204, 2201);
  g->Dot(967, 2205, YNN_INVALID_VALUE_ID, 2200, 1);
  g->DequantizeTensor(2200, YNN_INVALID_VALUE_ID, 2201, 2202);
  g->QuantizeTensor(2202, 2982, 2203, 1001);
  g->Dequantize(1001, 1002, 0.1643700897693634, 0);
  g->SplitDim(1002, 1003, 2, {8,256});
  g->Transpose(1003, 1004, {0,2,1,3});
  g->Unary(ynn_unary_square, 1004, 1005);
  g->Reduce(ynn_reduce_sum, 1005, 2798, {3}, true);
  g->ShapeProduct(1005, 2797, {3});
  g->Binary(ynn_binary_divide, 2798, 2797, 1006);
  g->Binary(ynn_binary_add, 1006, 3016, 1007);
  g->Unary(ynn_unary_rsqrt, 1007, 1008);
  g->Binary(ynn_binary_multiply, 1004, 1008, 1009);
  g->Binary(ynn_binary_multiply, 1009, 3154, 1010);
  g->Slice(1010, 1012, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1010, 1013, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1013, 1014);
  g->Concat({1014,1012}, 1015, 3);
  g->Binary(ynn_binary_multiply, 1010, 1096, 1016);
  g->Binary(ynn_binary_multiply, 1015, 1199, 1017);
  g->Binary(ynn_binary_add, 1016, 1017, 1018);
}

// Scope: "Layer2 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(3329, 1019, 0.005684707313776016, 0);
  g->Dequantize(3343, 1020, 0.047244105488061905, 0);
  g->Matmul(1018, 1019, 1021, false, true);
  g->Mask(1021, 3026, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 3026, 2802, {-1}, true);
  g->Binary(ynn_binary_subtract, 3026, 2802, 2799);
  g->Unary(ynn_unary_exp, 2799, 2800);
  g->Reduce(ynn_reduce_sum, 2800, 2803, {-1}, true);
  g->Binary(ynn_binary_divide, 2545, 2803, 2801);
  g->Binary(ynn_binary_multiply, 2800, 2801, 1023);
  g->Matmul(1023, 1020, 1024, false, false);
}

// Scope: "Layer2 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1024, 1025, {0,2,1,3});
  g->FuseDims(1025, 1026, 2, 2);
  g->Quantize(1026, 1027, 0.0216535534709692, 0);
  g->Transpose(3153, 2212, {1,0});
  g->Binary(ynn_binary_multiply, 2209, 2211, 2207);
  g->Dot(1027, 2212, YNN_INVALID_VALUE_ID, 2206, 1);
  g->DequantizeTensor(2206, YNN_INVALID_VALUE_ID, 2207, 2208);
  g->QuantizeTensor(2208, 2982, 2210, 1028);
  g->Dequantize(1028, 1029, 0.03426840156316757, 0);
}

// Scope: "Layer2 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 959, 960);
  g->Reduce(ynn_reduce_sum, 960, 2792, {2}, true);
  g->ShapeProduct(960, 2791, {2});
  g->Binary(ynn_binary_divide, 2792, 2791, 962);
  g->Binary(ynn_binary_add, 962, 3016, 963);
  g->Unary(ynn_unary_rsqrt, 963, 964);
  g->Binary(ynn_binary_multiply, 959, 964, 965);
  g->Binary(ynn_binary_multiply, 965, 3140, 966);
  BuildLayer2AttentionKvProjection(ctx);
  BuildLayer2AttentionCacheUpdate(ctx);
  BuildLayer2AttentionQueryProjection(ctx);
  BuildLayer2AttentionSdpa(ctx);
  BuildLayer2AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1029, 1030);
  g->Reduce(ynn_reduce_sum, 1030, 2805, {2}, true);
  g->ShapeProduct(1030, 2804, {2});
  g->Binary(ynn_binary_divide, 2805, 2804, 1031);
  g->Binary(ynn_binary_add, 1031, 3016, 1033);
  g->Unary(ynn_unary_rsqrt, 1033, 1034);
  g->Binary(ynn_binary_multiply, 1029, 1034, 1035);
  g->Binary(ynn_binary_multiply, 1035, 3147, 1036);
  g->Binary(ynn_binary_add, 1036, 959, 1037);
}

// Scope: "Layer2 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1037, 1038);
  g->Reduce(ynn_reduce_sum, 1038, 2807, {2}, true);
  g->ShapeProduct(1038, 2806, {2});
  g->Binary(ynn_binary_divide, 2807, 2806, 1039);
  g->Binary(ynn_binary_add, 1039, 3016, 1040);
  g->Unary(ynn_unary_rsqrt, 1040, 1041);
  g->Binary(ynn_binary_multiply, 1037, 1041, 1042);
  g->Binary(ynn_binary_multiply, 1042, 3150, 1044);
  g->Quantize(1044, 1045, 0.04049227386713028, 0);
  g->Transpose(3144, 2219, {1,0});
  g->Binary(ynn_binary_multiply, 2216, 2218, 2214);
  g->Dot(1045, 2219, YNN_INVALID_VALUE_ID, 2213, 1);
  g->DequantizeTensor(2213, YNN_INVALID_VALUE_ID, 2214, 2215);
  g->QuantizeTensor(2215, 2982, 2217, 1046);
  g->Dequantize(1046, 1047, 0.04183071851730347, 0);
  g->Transpose(3143, 2224, {1,0});
  g->Binary(ynn_binary_multiply, 2216, 2223, 2221);
  g->Dot(1045, 2224, YNN_INVALID_VALUE_ID, 2220, 1);
  g->DequantizeTensor(2220, YNN_INVALID_VALUE_ID, 2221, 2222);
  g->QuantizeTensor(2222, 2982, 2217, 1048);
  g->Dequantize(1048, 1049, 0.04183071851730347, 0);
  g->Polynomial(1049, 2810, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2810, 2811);
  g->Binary(ynn_binary_add, 2811, 2545, 2808);
  g->Binary(ynn_binary_multiply, 1049, 2543, 2809);
  g->Binary(ynn_binary_multiply, 2809, 2808, 1050);
  g->Binary(ynn_binary_multiply, 1047, 1050, 1051);
  g->Quantize(1051, 1052, 0.09645669907331467, 0);
  g->Transpose(3142, 2231, {1,0});
  g->Binary(ynn_binary_multiply, 2228, 2230, 2226);
  g->Dot(1052, 2231, YNN_INVALID_VALUE_ID, 2225, 1);
  g->DequantizeTensor(2225, YNN_INVALID_VALUE_ID, 2226, 2227);
  g->QuantizeTensor(2227, 2982, 2229, 1054);
  g->Dequantize(1054, 1055, 0.05011765658855438, 0);
  g->Unary(ynn_unary_square, 1055, 1056);
  g->Reduce(ynn_reduce_sum, 1056, 2813, {2}, true);
  g->ShapeProduct(1056, 2812, {2});
  g->Binary(ynn_binary_divide, 2813, 2812, 1057);
  g->Binary(ynn_binary_add, 1057, 3016, 1058);
  g->Unary(ynn_unary_rsqrt, 1058, 1059);
  g->Binary(ynn_binary_multiply, 1055, 1059, 1060);
  g->Binary(ynn_binary_multiply, 1060, 3148, 1061);
  g->Binary(ynn_binary_add, 1061, 1037, 1062);
}

// Scope: "Layer2 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer2PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(421, 1063, {0,0,2,0}, {-1,-1,1,-1});
  g->Reshape(1063, 1065, {1,0,256});
  g->Unary(ynn_unary_square, 1065, 1066);
  g->Reduce(ynn_reduce_sum, 1066, 2815, {2}, true);
  g->ShapeProduct(1066, 2814, {2});
  g->Binary(ynn_binary_divide, 2815, 2814, 1067);
  g->Binary(ynn_binary_add, 1067, 3016, 1068);
  g->Unary(ynn_unary_rsqrt, 1068, 1069);
  g->Binary(ynn_binary_multiply, 1065, 1069, 1070);
  g->Binary(ynn_binary_multiply, 1070, 3277, 1071);
  g->Binary(ynn_binary_multiply, 3284, 3019, 1072);
  g->Binary(ynn_binary_add, 1071, 1072, 1073);
  g->Binary(ynn_binary_multiply, 1073, 3014, 1074);
  g->Quantize(1062, 1076, 0.045230474323034286, 0);
  g->Transpose(3145, 2238, {1,0});
  g->Binary(ynn_binary_multiply, 2235, 2237, 2233);
  g->Dot(1076, 2238, YNN_INVALID_VALUE_ID, 2232, 1);
  g->DequantizeTensor(2232, YNN_INVALID_VALUE_ID, 2233, 2234);
  g->QuantizeTensor(2234, 2982, 2236, 1077);
  g->Dequantize(1077, 1078, 0.017839577049016953, 0);
  g->Polynomial(1078, 2818, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2818, 2819);
  g->Binary(ynn_binary_add, 2819, 2545, 2816);
  g->Binary(ynn_binary_multiply, 1078, 2543, 2817);
  g->Binary(ynn_binary_multiply, 2817, 2816, 1079);
  g->Binary(ynn_binary_multiply, 1079, 1074, 1080);
  g->Quantize(1080, 1081, 0.05216536670923233, 0);
  g->Transpose(3146, 2245, {1,0});
  g->Binary(ynn_binary_multiply, 2242, 2244, 2240);
  g->Dot(1081, 2245, YNN_INVALID_VALUE_ID, 2239, 1);
  g->DequantizeTensor(2239, YNN_INVALID_VALUE_ID, 2240, 2241);
  g->QuantizeTensor(2241, 2982, 2243, 1082);
  g->Dequantize(1082, 1083, 0.021943029016256332, 0);
  g->Unary(ynn_unary_square, 1083, 1084);
  g->Reduce(ynn_reduce_sum, 1084, 2821, {2}, true);
  g->ShapeProduct(1084, 2820, {2});
  g->Binary(ynn_binary_divide, 2821, 2820, 1085);
  g->Binary(ynn_binary_add, 1085, 3016, 1086);
  g->Unary(ynn_unary_rsqrt, 1086, 1087);
  g->Binary(ynn_binary_multiply, 1083, 1087, 1088);
  g->Binary(ynn_binary_multiply, 1088, 3149, 1089);
  g->Binary(ynn_binary_add, 1062, 1089, 1090);
  g->Binary(ynn_binary_multiply, 1090, 3141, 1091);
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
  g->Quantize(1099, 1100, 0.12591414153575897, 0);
  g->Transpose(3169, 2257, {1,0});
  g->Binary(ynn_binary_multiply, 2254, 2256, 2252);
  g->Dot(1100, 2257, YNN_INVALID_VALUE_ID, 2251, 1);
  g->DequantizeTensor(2251, YNN_INVALID_VALUE_ID, 2252, 2253);
  g->QuantizeTensor(2253, 2982, 2255, 1101);
  g->Dequantize(1101, 1102, 0.08710630983114243, 0);
  g->Reshape(1102, 1103, {1,0,1,256});
  g->Transpose(1103, 1104, {0,2,1,3});
  g->Unary(ynn_unary_square, 1104, 1105);
  g->Reduce(ynn_reduce_sum, 1105, 2825, {3}, true);
  g->ShapeProduct(1105, 2824, {3});
  g->Binary(ynn_binary_divide, 2825, 2824, 1106);
  g->Binary(ynn_binary_add, 1106, 3016, 1107);
  g->Unary(ynn_unary_rsqrt, 1107, 1109);
  g->Binary(ynn_binary_multiply, 1104, 1109, 1110);
  g->Binary(ynn_binary_multiply, 1110, 3168, 1111);
  g->Slice(1111, 1112, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1111, 1113, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1113, 1114);
  g->Concat({1114,1112}, 1115, 3);
  g->Binary(ynn_binary_multiply, 1111, 1096, 1116);
  g->Binary(ynn_binary_multiply, 1115, 1199, 1117);
  g->Binary(ynn_binary_add, 1116, 1117, 1118);
  g->Transpose(3173, 2262, {1,0});
  g->Binary(ynn_binary_multiply, 2254, 2261, 2259);
  g->Dot(1100, 2262, YNN_INVALID_VALUE_ID, 2258, 1);
  g->DequantizeTensor(2258, YNN_INVALID_VALUE_ID, 2259, 2260);
  g->QuantizeTensor(2260, 2982, 2255, 1120);
  g->Dequantize(1120, 1121, 0.08710630983114243, 0);
  g->Reshape(1121, 1122, {1,0,1,256});
  g->Transpose(1122, 1123, {0,2,1,3});
  g->Unary(ynn_unary_square, 1123, 1124);
  g->Reduce(ynn_reduce_sum, 1124, 2827, {3}, true);
  g->ShapeProduct(1124, 2826, {3});
  g->Binary(ynn_binary_divide, 2827, 2826, 1125);
  g->Binary(ynn_binary_add, 1125, 3016, 1126);
  g->Unary(ynn_unary_rsqrt, 1126, 1127);
  g->Binary(ynn_binary_multiply, 1123, 1127, 1128);
}

// Scope: "Layer3 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(1118, 1130, 0.00573749840259552, 0);
  g->Append(2991, 1130, 3301, 2, s2, s1);
  g->View(3301, 3330, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(1128, 1131, 0.047244105488061905, 0);
  g->Append(3006, 1131, 3316, 2, s2, s1);
  g->View(3316, 3344, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer3 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(3172, 2268, {1,0});
  g->Binary(ynn_binary_multiply, 2254, 2267, 2264);
  g->Dot(1100, 2268, YNN_INVALID_VALUE_ID, 2263, 1);
  g->DequantizeTensor(2263, YNN_INVALID_VALUE_ID, 2264, 2265);
  g->QuantizeTensor(2265, 2982, 2266, 1132);
  g->Dequantize(1132, 1133, 0.15354332327842712, 0);
  g->SplitDim(1133, 1134, 2, {8,256});
  g->Transpose(1134, 1136, {0,2,1,3});
  g->Unary(ynn_unary_square, 1136, 1137);
  g->Reduce(ynn_reduce_sum, 1137, 2829, {3}, true);
  g->ShapeProduct(1137, 2828, {3});
  g->Binary(ynn_binary_divide, 2829, 2828, 1138);
  g->Binary(ynn_binary_add, 1138, 3016, 1139);
  g->Unary(ynn_unary_rsqrt, 1139, 1140);
  g->Binary(ynn_binary_multiply, 1136, 1140, 1141);
  g->Binary(ynn_binary_multiply, 1141, 3171, 1142);
  g->Slice(1142, 1143, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1142, 1144, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1144, 1145);
  g->Concat({1145,1143}, 1147, 3);
  g->Binary(ynn_binary_multiply, 1142, 1096, 1148);
  g->Binary(ynn_binary_multiply, 1147, 1199, 1149);
  g->Binary(ynn_binary_add, 1148, 1149, 1150);
}

// Scope: "Layer3 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(3330, 1151, 0.00573749840259552, 0);
  g->Dequantize(3344, 1152, 0.047244105488061905, 0);
  g->Matmul(1150, 1151, 1153, false, true);
  g->Mask(1153, 3027, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 3027, 2835, {-1}, true);
  g->Binary(ynn_binary_subtract, 3027, 2835, 2832);
  g->Unary(ynn_unary_exp, 2832, 2833);
  g->Reduce(ynn_reduce_sum, 2833, 2836, {-1}, true);
  g->Binary(ynn_binary_divide, 2545, 2836, 2834);
  g->Binary(ynn_binary_multiply, 2833, 2834, 1154);
  g->Matmul(1154, 1152, 1155, false, false);
}

// Scope: "Layer3 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1155, 1157, {0,2,1,3});
  g->FuseDims(1157, 1158, 2, 2);
  g->Quantize(1158, 1159, 0.02706693857908249, 0);
  g->Transpose(3170, 2275, {1,0});
  g->Binary(ynn_binary_multiply, 2272, 2274, 2270);
  g->Dot(1159, 2275, YNN_INVALID_VALUE_ID, 2269, 1);
  g->DequantizeTensor(2269, YNN_INVALID_VALUE_ID, 2270, 2271);
  g->QuantizeTensor(2271, 2982, 2273, 1160);
  g->Dequantize(1160, 1161, 0.07367152720689774, 0);
}

// Scope: "Layer3 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1091, 1092);
  g->Reduce(ynn_reduce_sum, 1092, 2823, {2}, true);
  g->ShapeProduct(1092, 2822, {2});
  g->Binary(ynn_binary_divide, 2823, 2822, 1093);
  g->Binary(ynn_binary_add, 1093, 3016, 1094);
  g->Unary(ynn_unary_rsqrt, 1094, 1095);
  g->Binary(ynn_binary_multiply, 1091, 1095, 1098);
  g->Binary(ynn_binary_multiply, 1098, 3157, 1099);
  BuildLayer3AttentionKvProjection(ctx);
  BuildLayer3AttentionCacheUpdate(ctx);
  BuildLayer3AttentionQueryProjection(ctx);
  BuildLayer3AttentionSdpa(ctx);
  BuildLayer3AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1161, 1162);
  g->Reduce(ynn_reduce_sum, 1162, 2838, {2}, true);
  g->ShapeProduct(1162, 2837, {2});
  g->Binary(ynn_binary_divide, 2838, 2837, 1163);
  g->Binary(ynn_binary_add, 1163, 3016, 1164);
  g->Unary(ynn_unary_rsqrt, 1164, 1165);
  g->Binary(ynn_binary_multiply, 1161, 1165, 1166);
  g->Binary(ynn_binary_multiply, 1166, 3164, 1168);
  g->Binary(ynn_binary_add, 1168, 1091, 1169);
}

// Scope: "Layer3 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1169, 1170);
  g->Reduce(ynn_reduce_sum, 1170, 2840, {2}, true);
  g->ShapeProduct(1170, 2839, {2});
  g->Binary(ynn_binary_divide, 2840, 2839, 1171);
  g->Binary(ynn_binary_add, 1171, 3016, 1172);
  g->Unary(ynn_unary_rsqrt, 1172, 1173);
  g->Binary(ynn_binary_multiply, 1169, 1173, 1174);
  g->Binary(ynn_binary_multiply, 1174, 3167, 1175);
  g->Quantize(1175, 1176, 0.019482526928186417, 0);
  g->Transpose(3161, 2282, {1,0});
  g->Binary(ynn_binary_multiply, 2279, 2281, 2277);
  g->Dot(1176, 2282, YNN_INVALID_VALUE_ID, 2276, 1);
  g->DequantizeTensor(2276, YNN_INVALID_VALUE_ID, 2277, 2278);
  g->QuantizeTensor(2278, 2982, 2280, 1177);
  g->Dequantize(1177, 1179, 0.02005414292216301, 0);
  g->Transpose(3160, 2287, {1,0});
  g->Binary(ynn_binary_multiply, 2279, 2286, 2284);
  g->Dot(1176, 2287, YNN_INVALID_VALUE_ID, 2283, 1);
  g->DequantizeTensor(2283, YNN_INVALID_VALUE_ID, 2284, 2285);
  g->QuantizeTensor(2285, 2982, 2280, 1180);
  g->Dequantize(1180, 1181, 0.02005414292216301, 0);
  g->Polynomial(1181, 2843, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2843, 2844);
  g->Binary(ynn_binary_add, 2844, 2545, 2841);
  g->Binary(ynn_binary_multiply, 1181, 2543, 2842);
  g->Binary(ynn_binary_multiply, 2842, 2841, 1182);
  g->Binary(ynn_binary_multiply, 1179, 1182, 1183);
  g->Quantize(1183, 1184, 0.03297245129942894, 0);
  g->Transpose(3159, 2294, {1,0});
  g->Binary(ynn_binary_multiply, 2291, 2293, 2289);
  g->Dot(1184, 2294, YNN_INVALID_VALUE_ID, 2288, 1);
  g->DequantizeTensor(2288, YNN_INVALID_VALUE_ID, 2289, 2290);
  g->QuantizeTensor(2290, 2982, 2292, 1185);
  g->Dequantize(1185, 1186, 0.022154856473207474, 0);
  g->Unary(ynn_unary_square, 1186, 1187);
  g->Reduce(ynn_reduce_sum, 1187, 2846, {2}, true);
  g->ShapeProduct(1187, 2845, {2});
  g->Binary(ynn_binary_divide, 2846, 2845, 1189);
  g->Binary(ynn_binary_add, 1189, 3016, 1190);
  g->Unary(ynn_unary_rsqrt, 1190, 1191);
  g->Binary(ynn_binary_multiply, 1186, 1191, 1192);
  g->Binary(ynn_binary_multiply, 1192, 3165, 1193);
  g->Binary(ynn_binary_add, 1193, 1169, 1194);
}

// Scope: "Layer3 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer3PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(421, 1195, {0,0,3,0}, {-1,-1,1,-1});
  g->Reshape(1195, 1196, {1,0,256});
  g->Unary(ynn_unary_square, 1196, 1197);
  g->Reduce(ynn_reduce_sum, 1197, 2848, {2}, true);
  g->ShapeProduct(1197, 2847, {2});
  g->Binary(ynn_binary_divide, 2848, 2847, 1198);
  g->Binary(ynn_binary_add, 1198, 3016, 1200);
  g->Unary(ynn_unary_rsqrt, 1200, 1201);
  g->Binary(ynn_binary_multiply, 1196, 1201, 1202);
  g->Binary(ynn_binary_multiply, 1202, 3277, 1203);
  g->Binary(ynn_binary_multiply, 3285, 3019, 1204);
  g->Binary(ynn_binary_add, 1203, 1204, 1205);
  g->Binary(ynn_binary_multiply, 1205, 3014, 1206);
  g->Quantize(1194, 1207, 0.2861534655094147, 0);
  g->Transpose(3162, 2301, {1,0});
  g->Binary(ynn_binary_multiply, 2298, 2300, 2296);
  g->Dot(1207, 2301, YNN_INVALID_VALUE_ID, 2295, 1);
  g->DequantizeTensor(2295, YNN_INVALID_VALUE_ID, 2296, 2297);
  g->QuantizeTensor(2297, 2982, 2299, 1208);
  g->Dequantize(1208, 1209, 0.050688985735177994, 0);
  g->Polynomial(1209, 2851, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2851, 2852);
  g->Binary(ynn_binary_add, 2852, 2545, 2849);
  g->Binary(ynn_binary_multiply, 1209, 2543, 2850);
  g->Binary(ynn_binary_multiply, 2850, 2849, 1210);
  g->Binary(ynn_binary_multiply, 1210, 1206, 1211);
  g->Quantize(1211, 1212, 0.06692913919687271, 0);
  g->Transpose(3163, 2308, {1,0});
  g->Binary(ynn_binary_multiply, 2305, 2307, 2303);
  g->Dot(1212, 2308, YNN_INVALID_VALUE_ID, 2302, 1);
  g->DequantizeTensor(2302, YNN_INVALID_VALUE_ID, 2303, 2304);
  g->QuantizeTensor(2304, 2982, 2306, 1213);
  g->Dequantize(1213, 1214, 0.0805763527750969, 0);
  g->Unary(ynn_unary_square, 1214, 1215);
  g->Reduce(ynn_reduce_sum, 1215, 2854, {2}, true);
  g->ShapeProduct(1215, 2853, {2});
  g->Binary(ynn_binary_divide, 2854, 2853, 1216);
  g->Binary(ynn_binary_add, 1216, 3016, 1217);
  g->Unary(ynn_unary_rsqrt, 1217, 1218);
  g->Binary(ynn_binary_multiply, 1214, 1218, 1219);
  g->Binary(ynn_binary_multiply, 1219, 3166, 1221);
  g->Binary(ynn_binary_add, 1194, 1221, 1222);
  g->Binary(ynn_binary_multiply, 1222, 3158, 1223);
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
  g->Quantize(1229, 1230, 0.023374712094664574, 0);
  g->Transpose(3186, 2315, {1,0});
  g->Binary(ynn_binary_multiply, 2312, 2314, 2310);
  g->Dot(1230, 2315, YNN_INVALID_VALUE_ID, 2309, 1);
  g->DequantizeTensor(2309, YNN_INVALID_VALUE_ID, 2310, 2311);
  g->QuantizeTensor(2311, 2982, 2313, 1231);
  g->Dequantize(1231, 1232, 0.024852370843291283, 0);
  g->Reshape(1232, 1233, {1,0,1,512});
  g->Transpose(1233, 1234, {0,2,1,3});
  g->Unary(ynn_unary_square, 1234, 1235);
  g->Reduce(ynn_reduce_sum, 1235, 2858, {3}, true);
  g->ShapeProduct(1235, 2857, {3});
  g->Binary(ynn_binary_divide, 2858, 2857, 1236);
  g->Binary(ynn_binary_add, 1236, 3016, 1237);
  g->Unary(ynn_unary_rsqrt, 1237, 1238);
  g->Binary(ynn_binary_multiply, 1234, 1238, 1239);
  g->Binary(ynn_binary_multiply, 1239, 3185, 1240);
  g->Slice(1240, 1241, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(1240, 1242, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 1242, 1243);
  g->Concat({1243,1241}, 1244, 3);
  g->Binary(ynn_binary_multiply, 1240, 1613, 1245);
  g->Binary(ynn_binary_multiply, 1244, 2, 1246);
  g->Binary(ynn_binary_add, 1245, 1246, 1247);
  g->Transpose(3190, 2320, {1,0});
  g->Binary(ynn_binary_multiply, 2312, 2319, 2317);
  g->Dot(1230, 2320, YNN_INVALID_VALUE_ID, 2316, 1);
  g->DequantizeTensor(2316, YNN_INVALID_VALUE_ID, 2317, 2318);
  g->QuantizeTensor(2318, 2982, 2313, 1248);
  g->Dequantize(1248, 1249, 0.024852370843291283, 0);
  g->Reshape(1249, 1250, {1,0,1,512});
  g->Transpose(1250, 1251, {0,2,1,3});
  g->Unary(ynn_unary_square, 1251, 1252);
  g->Reduce(ynn_reduce_sum, 1252, 2860, {3}, true);
  g->ShapeProduct(1252, 2859, {3});
  g->Binary(ynn_binary_divide, 2860, 2859, 1253);
  g->Binary(ynn_binary_add, 1253, 3016, 1254);
  g->Unary(ynn_unary_rsqrt, 1254, 1255);
  g->Binary(ynn_binary_multiply, 1251, 1255, 1256);
}

// Scope: "Layer4 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(1247, 1257, 0.0011563472216948867, 0);
  g->Append(2992, 1257, 3302, 2, s2, s1);
  g->View(3302, 3331, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(1256, 1259, 0.01785714365541935, 0);
  g->Append(3007, 1259, 3317, 2, s2, s1);
  g->View(3317, 3345, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer4 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(3189, 2332, {1,0});
  g->Binary(ynn_binary_multiply, 2312, 2331, 2328);
  g->Dot(1230, 2332, YNN_INVALID_VALUE_ID, 2327, 1);
  g->DequantizeTensor(2327, YNN_INVALID_VALUE_ID, 2328, 2329);
  g->QuantizeTensor(2329, 2982, 2330, 1260);
  g->Dequantize(1260, 1261, 0.03248032554984093, 0);
  g->SplitDim(1261, 1262, 2, {8,512});
  g->Transpose(1262, 1263, {0,2,1,3});
  g->Unary(ynn_unary_square, 1263, 1264);
  g->Reduce(ynn_reduce_sum, 1264, 2862, {3}, true);
  g->ShapeProduct(1264, 2861, {3});
  g->Binary(ynn_binary_divide, 2862, 2861, 1265);
  g->Binary(ynn_binary_add, 1265, 3016, 1267);
  g->Unary(ynn_unary_rsqrt, 1267, 1268);
  g->Binary(ynn_binary_multiply, 1263, 1268, 1269);
  g->Binary(ynn_binary_multiply, 1269, 3188, 1270);
  g->Slice(1270, 1271, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(1270, 1272, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 1272, 1273);
  g->Concat({1273,1271}, 1274, 3);
  g->Binary(ynn_binary_multiply, 1270, 1613, 1275);
  g->Binary(ynn_binary_multiply, 1274, 2, 1276);
  g->Binary(ynn_binary_add, 1275, 1276, 1278);
}

// Scope: "Layer4 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(3331, 1279, 0.0011563472216948867, 0);
  g->Dequantize(3345, 1280, 0.01785714365541935, 0);
  g->Matmul(1278, 1279, 1281, false, true);
  g->Mask(1281, 3028, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 3028, 2866, {-1}, true);
  g->Binary(ynn_binary_subtract, 3028, 2866, 2863);
  g->Unary(ynn_unary_exp, 2863, 2864);
  g->Reduce(ynn_reduce_sum, 2864, 2867, {-1}, true);
  g->Binary(ynn_binary_divide, 2545, 2867, 2865);
  g->Binary(ynn_binary_multiply, 2864, 2865, 1282);
  g->Matmul(1282, 1280, 1283, false, false);
}

// Scope: "Layer4 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1283, 1284, {0,2,1,3});
  g->FuseDims(1284, 1285, 2, 2);
  g->Quantize(1285, 1286, 0.017962608486413956, 0);
  g->Transpose(3187, 2338, {1,0});
  g->Binary(ynn_binary_multiply, 1830, 2337, 2334);
  g->Dot(1286, 2338, YNN_INVALID_VALUE_ID, 2333, 1);
  g->DequantizeTensor(2333, YNN_INVALID_VALUE_ID, 2334, 2335);
  g->QuantizeTensor(2335, 2982, 2336, 1288);
  g->Dequantize(1288, 1289, 0.17608338594436646, 0);
}

// Scope: "Layer4 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1223, 1224);
  g->Reduce(ynn_reduce_sum, 1224, 2856, {2}, true);
  g->ShapeProduct(1224, 2855, {2});
  g->Binary(ynn_binary_divide, 2856, 2855, 1225);
  g->Binary(ynn_binary_add, 1225, 3016, 1226);
  g->Unary(ynn_unary_rsqrt, 1226, 1227);
  g->Binary(ynn_binary_multiply, 1223, 1227, 1228);
  g->Binary(ynn_binary_multiply, 1228, 3174, 1229);
  BuildLayer4AttentionKvProjection(ctx);
  BuildLayer4AttentionCacheUpdate(ctx);
  BuildLayer4AttentionQueryProjection(ctx);
  BuildLayer4AttentionSdpa(ctx);
  BuildLayer4AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1289, 1290);
  g->Reduce(ynn_reduce_sum, 1290, 2869, {2}, true);
  g->ShapeProduct(1290, 2868, {2});
  g->Binary(ynn_binary_divide, 2869, 2868, 1291);
  g->Binary(ynn_binary_add, 1291, 3016, 1292);
  g->Unary(ynn_unary_rsqrt, 1292, 1293);
  g->Binary(ynn_binary_multiply, 1289, 1293, 1294);
  g->Binary(ynn_binary_multiply, 1294, 3181, 1295);
  g->Binary(ynn_binary_add, 1295, 1223, 1296);
}

// Scope: "Layer4 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1296, 1297);
  g->Reduce(ynn_reduce_sum, 1297, 2871, {2}, true);
  g->ShapeProduct(1297, 2870, {2});
  g->Binary(ynn_binary_divide, 2871, 2870, 1300);
  g->Binary(ynn_binary_add, 1300, 3016, 1301);
  g->Unary(ynn_unary_rsqrt, 1301, 1302);
  g->Binary(ynn_binary_multiply, 1296, 1302, 1303);
  g->Binary(ynn_binary_multiply, 1303, 3184, 1304);
  g->Quantize(1304, 1305, 0.060907524079084396, 0);
  g->Transpose(3178, 2344, {1,0});
  g->Binary(ynn_binary_multiply, 2342, 2343, 2340);
  g->Dot(1305, 2344, YNN_INVALID_VALUE_ID, 2339, 1);
  g->DequantizeTensor(2339, YNN_INVALID_VALUE_ID, 2340, 2341);
  g->QuantizeTensor(2341, 2982, 1741, 1306);
  g->Dequantize(1306, 1307, 0.09251969307661057, 0);
  g->Transpose(3177, 2349, {1,0});
  g->Binary(ynn_binary_multiply, 2342, 2348, 2346);
  g->Dot(1305, 2349, YNN_INVALID_VALUE_ID, 2345, 1);
  g->DequantizeTensor(2345, YNN_INVALID_VALUE_ID, 2346, 2347);
  g->QuantizeTensor(2347, 2982, 1741, 1308);
  g->Dequantize(1308, 1310, 0.09251969307661057, 0);
  g->Polynomial(1310, 2876, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2876, 2877);
  g->Binary(ynn_binary_add, 2877, 2545, 2874);
  g->Binary(ynn_binary_multiply, 1310, 2543, 2875);
  g->Binary(ynn_binary_multiply, 2875, 2874, 1311);
  g->Binary(ynn_binary_multiply, 1307, 1311, 1312);
  g->Quantize(1312, 1313, 0.3444882035255432, 0);
  g->Transpose(3176, 2356, {1,0});
  g->Binary(ynn_binary_multiply, 2353, 2355, 2351);
  g->Dot(1313, 2356, YNN_INVALID_VALUE_ID, 2350, 1);
  g->DequantizeTensor(2350, YNN_INVALID_VALUE_ID, 2351, 2352);
  g->QuantizeTensor(2352, 2982, 2354, 1314);
  g->Dequantize(1314, 1315, 0.13582009077072144, 0);
  g->Unary(ynn_unary_square, 1315, 1316);
  g->Reduce(ynn_reduce_sum, 1316, 2879, {2}, true);
  g->ShapeProduct(1316, 2878, {2});
  g->Binary(ynn_binary_divide, 2879, 2878, 1317);
  g->Binary(ynn_binary_add, 1317, 3016, 1318);
  g->Unary(ynn_unary_rsqrt, 1318, 1319);
  g->Binary(ynn_binary_multiply, 1315, 1319, 1321);
  g->Binary(ynn_binary_multiply, 1321, 3182, 1322);
  g->Binary(ynn_binary_add, 1322, 1296, 1323);
}

// Scope: "Layer4 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(421, 1324, {0,0,4,0}, {-1,-1,1,-1});
  g->Reshape(1324, 1325, {1,0,256});
  g->Unary(ynn_unary_square, 1325, 1326);
  g->Reduce(ynn_reduce_sum, 1326, 2881, {2}, true);
  g->ShapeProduct(1326, 2880, {2});
  g->Binary(ynn_binary_divide, 2881, 2880, 1327);
  g->Binary(ynn_binary_add, 1327, 3016, 1328);
  g->Unary(ynn_unary_rsqrt, 1328, 1329);
  g->Binary(ynn_binary_multiply, 1325, 1329, 1330);
  g->Binary(ynn_binary_multiply, 1330, 3277, 1332);
  g->Binary(ynn_binary_multiply, 3286, 3019, 1333);
  g->Binary(ynn_binary_add, 1332, 1333, 1334);
  g->Binary(ynn_binary_multiply, 1334, 3014, 1335);
  g->Quantize(1323, 1336, 0.41414323449134827, 0);
  g->Transpose(3179, 2363, {1,0});
  g->Binary(ynn_binary_multiply, 2360, 2362, 2358);
  g->Dot(1336, 2363, YNN_INVALID_VALUE_ID, 2357, 1);
  g->DequantizeTensor(2357, YNN_INVALID_VALUE_ID, 2358, 2359);
  g->QuantizeTensor(2359, 2982, 2361, 1337);
  g->Dequantize(1337, 1338, 0.039862215518951416, 0);
  g->Polynomial(1338, 2884, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2884, 2885);
  g->Binary(ynn_binary_add, 2885, 2545, 2882);
  g->Binary(ynn_binary_multiply, 1338, 2543, 2883);
  g->Binary(ynn_binary_multiply, 2883, 2882, 1339);
  g->Binary(ynn_binary_multiply, 1339, 1335, 1340);
  g->Quantize(1340, 1341, 0.30314961075782776, 0);
  g->Transpose(3180, 2370, {1,0});
  g->Binary(ynn_binary_multiply, 2367, 2369, 2365);
  g->Dot(1341, 2370, YNN_INVALID_VALUE_ID, 2364, 1);
  g->DequantizeTensor(2364, YNN_INVALID_VALUE_ID, 2365, 2366);
  g->QuantizeTensor(2366, 2982, 2368, 1343);
  g->Dequantize(1343, 1344, 0.16701875627040863, 0);
  g->Unary(ynn_unary_square, 1344, 1345);
  g->Reduce(ynn_reduce_sum, 1345, 2887, {2}, true);
  g->ShapeProduct(1345, 2886, {2});
  g->Binary(ynn_binary_divide, 2887, 2886, 1346);
  g->Binary(ynn_binary_add, 1346, 3016, 1347);
  g->Unary(ynn_unary_rsqrt, 1347, 1348);
  g->Binary(ynn_binary_multiply, 1344, 1348, 1349);
  g->Binary(ynn_binary_multiply, 1349, 3183, 1350);
  g->Binary(ynn_binary_add, 1323, 1350, 1351);
  g->Binary(ynn_binary_multiply, 1351, 3175, 1352);
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
  g->Quantize(1359, 1360, 0.07399173825979233, 0);
  g->Transpose(3203, 2377, {1,0});
  g->Binary(ynn_binary_multiply, 2374, 2376, 2372);
  g->Dot(1360, 2377, YNN_INVALID_VALUE_ID, 2371, 1);
  g->DequantizeTensor(2371, YNN_INVALID_VALUE_ID, 2372, 2373);
  g->QuantizeTensor(2373, 2982, 2375, 1361);
  g->Dequantize(1361, 1362, 0.09842520207166672, 0);
  g->Reshape(1362, 1363, {1,0,1,256});
  g->Transpose(1363, 1365, {0,2,1,3});
  g->Unary(ynn_unary_square, 1365, 1366);
  g->Reduce(ynn_reduce_sum, 1366, 2891, {3}, true);
  g->ShapeProduct(1366, 2890, {3});
  g->Binary(ynn_binary_divide, 2891, 2890, 1367);
  g->Binary(ynn_binary_add, 1367, 3016, 1368);
  g->Unary(ynn_unary_rsqrt, 1368, 1369);
  g->Binary(ynn_binary_multiply, 1365, 1369, 1370);
  g->Binary(ynn_binary_multiply, 1370, 3202, 1371);
  g->Slice(1371, 1372, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1371, 1373, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1373, 1374);
  g->Concat({1374,1372}, 1376, 3);
  g->Binary(ynn_binary_multiply, 1371, 1096, 1377);
  g->Binary(ynn_binary_multiply, 1376, 1199, 1378);
  g->Binary(ynn_binary_add, 1377, 1378, 1379);
  g->Transpose(3207, 2382, {1,0});
  g->Binary(ynn_binary_multiply, 2374, 2381, 2379);
  g->Dot(1360, 2382, YNN_INVALID_VALUE_ID, 2378, 1);
  g->DequantizeTensor(2378, YNN_INVALID_VALUE_ID, 2379, 2380);
  g->QuantizeTensor(2380, 2982, 2375, 1380);
  g->Dequantize(1380, 1381, 0.09842520207166672, 0);
  g->Reshape(1381, 1382, {1,0,1,256});
  g->Transpose(1382, 1383, {0,2,1,3});
  g->Unary(ynn_unary_square, 1383, 1384);
  g->Reduce(ynn_reduce_sum, 1384, 2893, {3}, true);
  g->ShapeProduct(1384, 2892, {3});
  g->Binary(ynn_binary_divide, 2893, 2892, 1386);
  g->Binary(ynn_binary_add, 1386, 3016, 1387);
  g->Unary(ynn_unary_rsqrt, 1387, 1388);
  g->Binary(ynn_binary_multiply, 1383, 1388, 1389);
}

// Scope: "Layer5 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(1379, 1390, 0.006011798977851868, 0);
  g->Append(2993, 1390, 3303, 2, s2, s1);
  g->View(3303, 3332, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(1389, 1391, 0.047244105488061905, 0);
  g->Append(3008, 1391, 3318, 2, s2, s1);
  g->View(3318, 3346, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer5 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(3206, 2387, {1,0});
  g->Binary(ynn_binary_multiply, 2374, 2386, 2384);
  g->Dot(1360, 2387, YNN_INVALID_VALUE_ID, 2383, 1);
  g->DequantizeTensor(2383, YNN_INVALID_VALUE_ID, 2384, 2385);
  g->QuantizeTensor(2385, 2982, 2113, 1393);
  g->Dequantize(1393, 1394, 0.13385827839374542, 0);
  g->SplitDim(1394, 1395, 2, {8,256});
  g->Transpose(1395, 1396, {0,2,1,3});
  g->Unary(ynn_unary_square, 1396, 1397);
  g->Reduce(ynn_reduce_sum, 1397, 2895, {3}, true);
  g->ShapeProduct(1397, 2894, {3});
  g->Binary(ynn_binary_divide, 2895, 2894, 1398);
  g->Binary(ynn_binary_add, 1398, 3016, 1399);
  g->Unary(ynn_unary_rsqrt, 1399, 1400);
  g->Binary(ynn_binary_multiply, 1396, 1400, 1401);
  g->Binary(ynn_binary_multiply, 1401, 3205, 1404);
  g->Slice(1404, 1405, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1404, 1406, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1406, 1407);
  g->Concat({1407,1405}, 1408, 3);
  g->Binary(ynn_binary_multiply, 1404, 1096, 1409);
  g->Binary(ynn_binary_multiply, 1408, 1199, 1410);
  g->Binary(ynn_binary_add, 1409, 1410, 1411);
}

// Scope: "Layer5 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(3332, 1412, 0.006011798977851868, 0);
  g->Dequantize(3346, 1413, 0.047244105488061905, 0);
  g->Matmul(1411, 1412, 1415, false, true);
  g->Mask(1415, 3029, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 3029, 2899, {-1}, true);
  g->Binary(ynn_binary_subtract, 3029, 2899, 2896);
  g->Unary(ynn_unary_exp, 2896, 2897);
  g->Reduce(ynn_reduce_sum, 2897, 2900, {-1}, true);
  g->Binary(ynn_binary_divide, 2545, 2900, 2898);
  g->Binary(ynn_binary_multiply, 2897, 2898, 1416);
  g->Matmul(1416, 1413, 1417, false, false);
}

// Scope: "Layer5 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1417, 1418, {0,2,1,3});
  g->FuseDims(1418, 1419, 2, 2);
  g->Quantize(1419, 1420, 0.026451781392097473, 0);
  g->Transpose(3204, 2394, {1,0});
  g->Binary(ynn_binary_multiply, 2391, 2393, 2389);
  g->Dot(1420, 2394, YNN_INVALID_VALUE_ID, 2388, 1);
  g->DequantizeTensor(2388, YNN_INVALID_VALUE_ID, 2389, 2390);
  g->QuantizeTensor(2390, 2982, 2392, 1421);
  g->Dequantize(1421, 1422, 0.043322544544935226, 0);
}

// Scope: "Layer5 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1352, 1354);
  g->Reduce(ynn_reduce_sum, 1354, 2889, {2}, true);
  g->ShapeProduct(1354, 2888, {2});
  g->Binary(ynn_binary_divide, 2889, 2888, 1355);
  g->Binary(ynn_binary_add, 1355, 3016, 1356);
  g->Unary(ynn_unary_rsqrt, 1356, 1357);
  g->Binary(ynn_binary_multiply, 1352, 1357, 1358);
  g->Binary(ynn_binary_multiply, 1358, 3191, 1359);
  BuildLayer5AttentionKvProjection(ctx);
  BuildLayer5AttentionCacheUpdate(ctx);
  BuildLayer5AttentionQueryProjection(ctx);
  BuildLayer5AttentionSdpa(ctx);
  BuildLayer5AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1422, 1423);
  g->Reduce(ynn_reduce_sum, 1423, 2902, {2}, true);
  g->ShapeProduct(1423, 2901, {2});
  g->Binary(ynn_binary_divide, 2902, 2901, 1425);
  g->Binary(ynn_binary_add, 1425, 3016, 1426);
  g->Unary(ynn_unary_rsqrt, 1426, 1427);
  g->Binary(ynn_binary_multiply, 1422, 1427, 1428);
  g->Binary(ynn_binary_multiply, 1428, 3198, 1429);
  g->Binary(ynn_binary_add, 1429, 1352, 1430);
}

// Scope: "Layer5 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1430, 1431);
  g->Reduce(ynn_reduce_sum, 1431, 2904, {2}, true);
  g->ShapeProduct(1431, 2903, {2});
  g->Binary(ynn_binary_divide, 2904, 2903, 1432);
  g->Binary(ynn_binary_add, 1432, 3016, 1433);
  g->Unary(ynn_unary_rsqrt, 1433, 1434);
  g->Binary(ynn_binary_multiply, 1430, 1434, 1436);
  g->Binary(ynn_binary_multiply, 1436, 3201, 1437);
  g->Quantize(1437, 1438, 0.03518042340874672, 0);
  g->Transpose(3195, 2401, {1,0});
  g->Binary(ynn_binary_multiply, 2398, 2400, 2396);
  g->Dot(1438, 2401, YNN_INVALID_VALUE_ID, 2395, 1);
  g->DequantizeTensor(2395, YNN_INVALID_VALUE_ID, 2396, 2397);
  g->QuantizeTensor(2397, 2982, 2399, 1439);
  g->Dequantize(1439, 1440, 0.03567914664745331, 0);
  g->Transpose(3194, 2406, {1,0});
  g->Binary(ynn_binary_multiply, 2398, 2405, 2403);
  g->Dot(1438, 2406, YNN_INVALID_VALUE_ID, 2402, 1);
  g->DequantizeTensor(2402, YNN_INVALID_VALUE_ID, 2403, 2404);
  g->QuantizeTensor(2404, 2982, 2399, 1441);
  g->Dequantize(1441, 1442, 0.03567914664745331, 0);
  g->Polynomial(1442, 2907, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2907, 2908);
  g->Binary(ynn_binary_add, 2908, 2545, 2905);
  g->Binary(ynn_binary_multiply, 1442, 2543, 2906);
  g->Binary(ynn_binary_multiply, 2906, 2905, 1443);
  g->Binary(ynn_binary_multiply, 1440, 1443, 1444);
  g->Quantize(1444, 1446, 0.08415354788303375, 0);
  g->Transpose(3193, 2413, {1,0});
  g->Binary(ynn_binary_multiply, 2410, 2412, 2408);
  g->Dot(1446, 2413, YNN_INVALID_VALUE_ID, 2407, 1);
  g->DequantizeTensor(2407, YNN_INVALID_VALUE_ID, 2408, 2409);
  g->QuantizeTensor(2409, 2982, 2411, 1447);
  g->Dequantize(1447, 1448, 0.06301677227020264, 0);
  g->Unary(ynn_unary_square, 1448, 1449);
  g->Reduce(ynn_reduce_sum, 1449, 2910, {2}, true);
  g->ShapeProduct(1449, 2909, {2});
  g->Binary(ynn_binary_divide, 2910, 2909, 1450);
  g->Binary(ynn_binary_add, 1450, 3016, 1451);
  g->Unary(ynn_unary_rsqrt, 1451, 1452);
  g->Binary(ynn_binary_multiply, 1448, 1452, 1453);
  g->Binary(ynn_binary_multiply, 1453, 3199, 1454);
  g->Binary(ynn_binary_add, 1454, 1430, 1455);
}

// Scope: "Layer5 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(421, 1457, {0,0,5,0}, {-1,-1,1,-1});
  g->Reshape(1457, 1458, {1,0,256});
  g->Unary(ynn_unary_square, 1458, 1459);
  g->Reduce(ynn_reduce_sum, 1459, 2912, {2}, true);
  g->ShapeProduct(1459, 2911, {2});
  g->Binary(ynn_binary_divide, 2912, 2911, 1460);
  g->Binary(ynn_binary_add, 1460, 3016, 1461);
  g->Unary(ynn_unary_rsqrt, 1461, 1462);
  g->Binary(ynn_binary_multiply, 1458, 1462, 1463);
  g->Binary(ynn_binary_multiply, 1463, 3277, 1464);
  g->Binary(ynn_binary_multiply, 3287, 3019, 1465);
  g->Binary(ynn_binary_add, 1464, 1465, 1466);
  g->Binary(ynn_binary_multiply, 1466, 3014, 1467);
  g->Quantize(1455, 1468, 0.3165745139122009, 0);
  g->Transpose(3196, 2420, {1,0});
  g->Binary(ynn_binary_multiply, 2417, 2419, 2415);
  g->Dot(1468, 2420, YNN_INVALID_VALUE_ID, 2414, 1);
  g->DequantizeTensor(2414, YNN_INVALID_VALUE_ID, 2415, 2416);
  g->QuantizeTensor(2416, 2982, 2418, 1469);
  g->Dequantize(1469, 1470, 0.0393700897693634, 0);
  g->Polynomial(1470, 2915, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2915, 2916);
  g->Binary(ynn_binary_add, 2916, 2545, 2913);
  g->Binary(ynn_binary_multiply, 1470, 2543, 2914);
  g->Binary(ynn_binary_multiply, 2914, 2913, 1471);
  g->Binary(ynn_binary_multiply, 1471, 1467, 1472);
  g->Quantize(1472, 1473, 0.22933071851730347, 0);
  g->Transpose(3197, 2427, {1,0});
  g->Binary(ynn_binary_multiply, 2424, 2426, 2422);
  g->Dot(1473, 2427, YNN_INVALID_VALUE_ID, 2421, 1);
  g->DequantizeTensor(2421, YNN_INVALID_VALUE_ID, 2422, 2423);
  g->QuantizeTensor(2423, 2982, 2425, 1474);
  g->Dequantize(1474, 1475, 0.12322933226823807, 0);
  g->Unary(ynn_unary_square, 1475, 1476);
  g->Reduce(ynn_reduce_sum, 1476, 2923, {2}, true);
  g->ShapeProduct(1476, 2922, {2});
  g->Binary(ynn_binary_divide, 2923, 2922, 1478);
  g->Binary(ynn_binary_add, 1478, 3016, 1479);
  g->Unary(ynn_unary_rsqrt, 1479, 1480);
  g->Binary(ynn_binary_multiply, 1475, 1480, 1481);
  g->Binary(ynn_binary_multiply, 1481, 3200, 1482);
  g->Binary(ynn_binary_add, 1455, 1482, 1483);
  g->Binary(ynn_binary_multiply, 1483, 3192, 1484);
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
  g->Quantize(1491, 1492, 0.341854453086853, 0);
  g->Transpose(3220, 2434, {1,0});
  g->Binary(ynn_binary_multiply, 2431, 2433, 2429);
  g->Dot(1492, 2434, YNN_INVALID_VALUE_ID, 2428, 1);
  g->DequantizeTensor(2428, YNN_INVALID_VALUE_ID, 2429, 2430);
  g->QuantizeTensor(2430, 2982, 2432, 1493);
  g->Dequantize(1493, 1494, 0.28740158677101135, 0);
  g->Reshape(1494, 1495, {1,0,1,256});
  g->Transpose(1495, 1496, {0,2,1,3});
  g->Unary(ynn_unary_square, 1496, 1497);
  g->Reduce(ynn_reduce_sum, 1497, 2927, {3}, true);
  g->ShapeProduct(1497, 2926, {3});
  g->Binary(ynn_binary_divide, 2927, 2926, 1498);
  g->Binary(ynn_binary_add, 1498, 3016, 1500);
  g->Unary(ynn_unary_rsqrt, 1500, 1501);
  g->Binary(ynn_binary_multiply, 1496, 1501, 1502);
  g->Binary(ynn_binary_multiply, 1502, 3219, 1503);
  g->Slice(1503, 1504, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1503, 1505, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1505, 1506);
  g->Concat({1506,1504}, 1507, 3);
  g->Binary(ynn_binary_multiply, 1503, 1096, 1508);
  g->Binary(ynn_binary_multiply, 1507, 1199, 1509);
  g->Binary(ynn_binary_add, 1508, 1509, 1512);
  g->Transpose(3224, 2439, {1,0});
  g->Binary(ynn_binary_multiply, 2431, 2438, 2436);
  g->Dot(1492, 2439, YNN_INVALID_VALUE_ID, 2435, 1);
  g->DequantizeTensor(2435, YNN_INVALID_VALUE_ID, 2436, 2437);
  g->QuantizeTensor(2437, 2982, 2432, 1513);
  g->Dequantize(1513, 1514, 0.28740158677101135, 0);
  g->Reshape(1514, 1515, {1,0,1,256});
  g->Transpose(1515, 1516, {0,2,1,3});
  g->Unary(ynn_unary_square, 1516, 1517);
  g->Reduce(ynn_reduce_sum, 1517, 2929, {3}, true);
  g->ShapeProduct(1517, 2928, {3});
  g->Binary(ynn_binary_divide, 2929, 2928, 1518);
  g->Binary(ynn_binary_add, 1518, 3016, 1519);
  g->Unary(ynn_unary_rsqrt, 1519, 1520);
  g->Binary(ynn_binary_multiply, 1516, 1520, 1522);
}

// Scope: "Layer6 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(1512, 1523, 0.0057707298547029495, 0);
  g->Append(2994, 1523, 3304, 2, s2, s1);
  g->View(3304, 3333, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(1522, 1524, 0.047244105488061905, 0);
  g->Append(3009, 1524, 3319, 2, s2, s1);
  g->View(3319, 3347, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer6 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(3223, 2445, {1,0});
  g->Binary(ynn_binary_multiply, 2431, 2444, 2441);
  g->Dot(1492, 2445, YNN_INVALID_VALUE_ID, 2440, 1);
  g->DequantizeTensor(2440, YNN_INVALID_VALUE_ID, 2441, 2442);
  g->QuantizeTensor(2442, 2982, 2443, 1525);
  g->Dequantize(1525, 1526, 0.4566929042339325, 0);
  g->SplitDim(1526, 1528, 2, {8,256});
  g->Transpose(1528, 1529, {0,2,1,3});
  g->Unary(ynn_unary_square, 1529, 1530);
  g->Reduce(ynn_reduce_sum, 1530, 2931, {3}, true);
  g->ShapeProduct(1530, 2930, {3});
  g->Binary(ynn_binary_divide, 2931, 2930, 1531);
  g->Binary(ynn_binary_add, 1531, 3016, 1532);
  g->Unary(ynn_unary_rsqrt, 1532, 1533);
  g->Binary(ynn_binary_multiply, 1529, 1533, 1534);
  g->Binary(ynn_binary_multiply, 1534, 3222, 1535);
  g->Slice(1535, 1536, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1535, 1537, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1537, 1539);
  g->Concat({1539,1536}, 1540, 3);
  g->Binary(ynn_binary_multiply, 1535, 1096, 1541);
  g->Binary(ynn_binary_multiply, 1540, 1199, 1542);
  g->Binary(ynn_binary_add, 1541, 1542, 1543);
}

// Scope: "Layer6 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(3333, 1544, 0.0057707298547029495, 0);
  g->Dequantize(3347, 1545, 0.047244105488061905, 0);
  g->Matmul(1543, 1544, 1546, false, true);
  g->Mask(1546, 3030, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 3030, 2935, {-1}, true);
  g->Binary(ynn_binary_subtract, 3030, 2935, 2932);
  g->Unary(ynn_unary_exp, 2932, 2933);
  g->Reduce(ynn_reduce_sum, 2933, 2936, {-1}, true);
  g->Binary(ynn_binary_divide, 2545, 2936, 2934);
  g->Binary(ynn_binary_multiply, 2933, 2934, 1547);
  g->Matmul(1547, 1545, 1549, false, false);
}

// Scope: "Layer6 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1549, 1550, {0,2,1,3});
  g->FuseDims(1550, 1551, 2, 2);
  g->Quantize(1551, 1552, 0.0354330837726593, 0);
  g->Transpose(3221, 2459, {1,0});
  g->Binary(ynn_binary_multiply, 2456, 2458, 2454);
  g->Dot(1552, 2459, YNN_INVALID_VALUE_ID, 2453, 1);
  g->DequantizeTensor(2453, YNN_INVALID_VALUE_ID, 2454, 2455);
  g->QuantizeTensor(2455, 2982, 2457, 1553);
  g->Dequantize(1553, 1554, 0.05930274724960327, 0);
}

// Scope: "Layer6 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1484, 1485);
  g->Reduce(ynn_reduce_sum, 1485, 2925, {2}, true);
  g->ShapeProduct(1485, 2924, {2});
  g->Binary(ynn_binary_divide, 2925, 2924, 1486);
  g->Binary(ynn_binary_add, 1486, 3016, 1487);
  g->Unary(ynn_unary_rsqrt, 1487, 1489);
  g->Binary(ynn_binary_multiply, 1484, 1489, 1490);
  g->Binary(ynn_binary_multiply, 1490, 3208, 1491);
  BuildLayer6AttentionKvProjection(ctx);
  BuildLayer6AttentionCacheUpdate(ctx);
  BuildLayer6AttentionQueryProjection(ctx);
  BuildLayer6AttentionSdpa(ctx);
  BuildLayer6AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1554, 1555);
  g->Reduce(ynn_reduce_sum, 1555, 2938, {2}, true);
  g->ShapeProduct(1555, 2937, {2});
  g->Binary(ynn_binary_divide, 2938, 2937, 1556);
  g->Binary(ynn_binary_add, 1556, 3016, 1557);
  g->Unary(ynn_unary_rsqrt, 1557, 1558);
  g->Binary(ynn_binary_multiply, 1554, 1558, 1560);
  g->Binary(ynn_binary_multiply, 1560, 3215, 1561);
  g->Binary(ynn_binary_add, 1561, 1484, 1562);
}

// Scope: "Layer6 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1562, 1563);
  g->Reduce(ynn_reduce_sum, 1563, 2942, {2}, true);
  g->ShapeProduct(1563, 2941, {2});
  g->Binary(ynn_binary_divide, 2942, 2941, 1564);
  g->Binary(ynn_binary_add, 1564, 3016, 1565);
  g->Unary(ynn_unary_rsqrt, 1565, 1566);
  g->Binary(ynn_binary_multiply, 1562, 1566, 1567);
  g->Binary(ynn_binary_multiply, 1567, 3218, 1568);
  g->Quantize(1568, 1569, 0.02705955132842064, 0);
  g->Transpose(3212, 2466, {1,0});
  g->Binary(ynn_binary_multiply, 2463, 2465, 2461);
  g->Dot(1569, 2466, YNN_INVALID_VALUE_ID, 2460, 1);
  g->DequantizeTensor(2460, YNN_INVALID_VALUE_ID, 2461, 2462);
  g->QuantizeTensor(2462, 2982, 2464, 1571);
  g->Dequantize(1571, 1572, 0.02632874995470047, 0);
  g->Transpose(3211, 2471, {1,0});
  g->Binary(ynn_binary_multiply, 2463, 2470, 2468);
  g->Dot(1569, 2471, YNN_INVALID_VALUE_ID, 2467, 1);
  g->DequantizeTensor(2467, YNN_INVALID_VALUE_ID, 2468, 2469);
  g->QuantizeTensor(2469, 2982, 2464, 1573);
  g->Dequantize(1573, 1574, 0.02632874995470047, 0);
  g->Polynomial(1574, 2945, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2945, 2946);
  g->Binary(ynn_binary_add, 2946, 2545, 2943);
  g->Binary(ynn_binary_multiply, 1574, 2543, 2944);
  g->Binary(ynn_binary_multiply, 2944, 2943, 1575);
  g->Binary(ynn_binary_multiply, 1572, 1575, 1576);
  g->Quantize(1576, 1577, 0.039862215518951416, 0);
  g->Transpose(3210, 2477, {1,0});
  g->Binary(ynn_binary_multiply, 2361, 2476, 2473);
  g->Dot(1577, 2477, YNN_INVALID_VALUE_ID, 2472, 1);
  g->DequantizeTensor(2472, YNN_INVALID_VALUE_ID, 2473, 2474);
  g->QuantizeTensor(2474, 2982, 2475, 1578);
  g->Dequantize(1578, 1579, 0.019578030332922935, 0);
  g->Unary(ynn_unary_square, 1579, 1581);
  g->Reduce(ynn_reduce_sum, 1581, 2948, {2}, true);
  g->ShapeProduct(1581, 2947, {2});
  g->Binary(ynn_binary_divide, 2948, 2947, 1582);
  g->Binary(ynn_binary_add, 1582, 3016, 1583);
  g->Unary(ynn_unary_rsqrt, 1583, 1584);
  g->Binary(ynn_binary_multiply, 1579, 1584, 1585);
  g->Binary(ynn_binary_multiply, 1585, 3216, 1586);
  g->Binary(ynn_binary_add, 1586, 1562, 1587);
}

// Scope: "Layer6 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(421, 1588, {0,0,6,0}, {-1,-1,1,-1});
  g->Reshape(1588, 1589, {1,0,256});
  g->Unary(ynn_unary_square, 1589, 1590);
  g->Reduce(ynn_reduce_sum, 1590, 2950, {2}, true);
  g->ShapeProduct(1590, 2949, {2});
  g->Binary(ynn_binary_divide, 2950, 2949, 1592);
  g->Binary(ynn_binary_add, 1592, 3016, 1593);
  g->Unary(ynn_unary_rsqrt, 1593, 1594);
  g->Binary(ynn_binary_multiply, 1589, 1594, 1595);
  g->Binary(ynn_binary_multiply, 1595, 3277, 1596);
  g->Binary(ynn_binary_multiply, 3288, 3019, 1597);
  g->Binary(ynn_binary_add, 1596, 1597, 1598);
  g->Binary(ynn_binary_multiply, 1598, 3014, 1599);
  g->Quantize(1587, 1600, 0.34014976024627686, 0);
  g->Transpose(3213, 2484, {1,0});
  g->Binary(ynn_binary_multiply, 2481, 2483, 2479);
  g->Dot(1600, 2484, YNN_INVALID_VALUE_ID, 2478, 1);
  g->DequantizeTensor(2478, YNN_INVALID_VALUE_ID, 2479, 2480);
  g->QuantizeTensor(2480, 2982, 2482, 1601);
  g->Dequantize(1601, 1603, 0.04773623123764992, 0);
  g->Polynomial(1603, 2953, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2953, 2954);
  g->Binary(ynn_binary_add, 2954, 2545, 2951);
  g->Binary(ynn_binary_multiply, 1603, 2543, 2952);
  g->Binary(ynn_binary_multiply, 2952, 2951, 1604);
  g->Binary(ynn_binary_multiply, 1604, 1599, 1605);
  g->Quantize(1605, 1606, 0.12450788170099258, 0);
  g->Transpose(3214, 2490, {1,0});
  g->Binary(ynn_binary_multiply, 2057, 2489, 2486);
  g->Dot(1606, 2490, YNN_INVALID_VALUE_ID, 2485, 1);
  g->DequantizeTensor(2485, YNN_INVALID_VALUE_ID, 2486, 2487);
  g->QuantizeTensor(2487, 2982, 2488, 1607);
  g->Dequantize(1607, 1608, 0.07488936185836792, 0);
  g->Unary(ynn_unary_square, 1608, 1609);
  g->Reduce(ynn_reduce_sum, 1609, 2956, {2}, true);
  g->ShapeProduct(1609, 2955, {2});
  g->Binary(ynn_binary_divide, 2956, 2955, 1610);
  g->Binary(ynn_binary_add, 1610, 3016, 1611);
  g->Unary(ynn_unary_rsqrt, 1611, 1612);
  g->Binary(ynn_binary_multiply, 1608, 1612, 1615);
  g->Binary(ynn_binary_multiply, 1615, 3217, 1616);
  g->Binary(ynn_binary_add, 1587, 1616, 1617);
  g->Binary(ynn_binary_multiply, 1617, 3209, 1618);
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
  g->Quantize(1624, 1626, 0.29519250988960266, 0);
  g->Transpose(3237, 2497, {1,0});
  g->Binary(ynn_binary_multiply, 2494, 2496, 2492);
  g->Dot(1626, 2497, YNN_INVALID_VALUE_ID, 2491, 1);
  g->DequantizeTensor(2491, YNN_INVALID_VALUE_ID, 2492, 2493);
  g->QuantizeTensor(2493, 2982, 2495, 1627);
  g->Dequantize(1627, 1628, 0.3681102395057678, 0);
  g->Reshape(1628, 1629, {1,0,1,256});
  g->Transpose(1629, 1630, {0,2,1,3});
  g->Unary(ynn_unary_square, 1630, 1631);
  g->Reduce(ynn_reduce_sum, 1631, 2960, {3}, true);
  g->ShapeProduct(1631, 2959, {3});
  g->Binary(ynn_binary_divide, 2960, 2959, 1632);
  g->Binary(ynn_binary_add, 1632, 3016, 1633);
  g->Unary(ynn_unary_rsqrt, 1633, 1634);
  g->Binary(ynn_binary_multiply, 1630, 1634, 1635);
  g->Binary(ynn_binary_multiply, 1635, 3236, 1637);
  g->Slice(1637, 1638, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1637, 1639, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1639, 1640);
  g->Concat({1640,1638}, 1641, 3);
  g->Binary(ynn_binary_multiply, 1637, 1096, 1642);
  g->Binary(ynn_binary_multiply, 1641, 1199, 1643);
  g->Binary(ynn_binary_add, 1642, 1643, 1644);
  g->Transpose(3241, 2502, {1,0});
  g->Binary(ynn_binary_multiply, 2494, 2501, 2499);
  g->Dot(1626, 2502, YNN_INVALID_VALUE_ID, 2498, 1);
  g->DequantizeTensor(2498, YNN_INVALID_VALUE_ID, 2499, 2500);
  g->QuantizeTensor(2500, 2982, 2495, 1645);
  g->Dequantize(1645, 1647, 0.3681102395057678, 0);
  g->Reshape(1647, 1648, {1,0,1,256});
  g->Transpose(1648, 1649, {0,2,1,3});
  g->Unary(ynn_unary_square, 1649, 1650);
  g->Reduce(ynn_reduce_sum, 1650, 2964, {3}, true);
  g->ShapeProduct(1650, 2963, {3});
  g->Binary(ynn_binary_divide, 2964, 2963, 1651);
  g->Binary(ynn_binary_add, 1651, 3016, 1652);
  g->Unary(ynn_unary_rsqrt, 1652, 1653);
  g->Binary(ynn_binary_multiply, 1649, 1653, 1654);
}

// Scope: "Layer7 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(1644, 1655, 0.005869260523468256, 0);
  g->Append(2995, 1655, 3305, 2, s2, s1);
  g->View(3305, 3334, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(1654, 1657, 0.047244105488061905, 0);
  g->Append(3010, 1657, 3320, 2, s2, s1);
  g->View(3320, 3348, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer7 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(3240, 2508, {1,0});
  g->Binary(ynn_binary_multiply, 2494, 2507, 2504);
  g->Dot(1626, 2508, YNN_INVALID_VALUE_ID, 2503, 1);
  g->DequantizeTensor(2503, YNN_INVALID_VALUE_ID, 2504, 2505);
  g->QuantizeTensor(2505, 2982, 2506, 1658);
  g->Dequantize(1658, 1659, 0.31496062874794006, 0);
  g->SplitDim(1659, 1660, 2, {8,256});
  g->Transpose(1660, 1661, {0,2,1,3});
  g->Unary(ynn_unary_square, 1661, 1662);
  g->Reduce(ynn_reduce_sum, 1662, 2966, {3}, true);
  g->ShapeProduct(1662, 2965, {3});
  g->Binary(ynn_binary_divide, 2966, 2965, 1664);
  g->Binary(ynn_binary_add, 1664, 3016, 1665);
  g->Unary(ynn_unary_rsqrt, 1665, 1666);
  g->Binary(ynn_binary_multiply, 1661, 1666, 1667);
  g->Binary(ynn_binary_multiply, 1667, 3239, 1668);
  g->Slice(1668, 1669, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1668, 1670, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1670, 1671);
  g->Concat({1671,1669}, 1672, 3);
  g->Binary(ynn_binary_multiply, 1668, 1096, 1673);
  g->Binary(ynn_binary_multiply, 1672, 1199, 1675);
  g->Binary(ynn_binary_add, 1673, 1675, 1676);
}

// Scope: "Layer7 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(3334, 1677, 0.005869260523468256, 0);
  g->Dequantize(3348, 1678, 0.047244105488061905, 0);
  g->Matmul(1676, 1677, 1679, false, true);
  g->Mask(1679, 3031, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 3031, 2970, {-1}, true);
  g->Binary(ynn_binary_subtract, 3031, 2970, 2967);
  g->Unary(ynn_unary_exp, 2967, 2968);
  g->Reduce(ynn_reduce_sum, 2968, 2971, {-1}, true);
  g->Binary(ynn_binary_divide, 2545, 2971, 2969);
  g->Binary(ynn_binary_multiply, 2968, 2969, 1680);
  g->Matmul(1680, 1678, 1681, false, false);
}

// Scope: "Layer7 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1681, 1682, {0,2,1,3});
  g->FuseDims(1682, 1683, 2, 2);
  g->Quantize(1683, 1685, 0.028912410140037537, 0);
  g->Transpose(3238, 2515, {1,0});
  g->Binary(ynn_binary_multiply, 2512, 2514, 2510);
  g->Dot(1685, 2515, YNN_INVALID_VALUE_ID, 2509, 1);
  g->DequantizeTensor(2509, YNN_INVALID_VALUE_ID, 2510, 2511);
  g->QuantizeTensor(2511, 2982, 2513, 1686);
  g->Dequantize(1686, 1687, 0.025238478556275368, 0);
}

// Scope: "Layer7 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1618, 1619);
  g->Reduce(ynn_reduce_sum, 1619, 2958, {2}, true);
  g->ShapeProduct(1619, 2957, {2});
  g->Binary(ynn_binary_divide, 2958, 2957, 1620);
  g->Binary(ynn_binary_add, 1620, 3016, 1621);
  g->Unary(ynn_unary_rsqrt, 1621, 1622);
  g->Binary(ynn_binary_multiply, 1618, 1622, 1623);
  g->Binary(ynn_binary_multiply, 1623, 3225, 1624);
  BuildLayer7AttentionKvProjection(ctx);
  BuildLayer7AttentionCacheUpdate(ctx);
  BuildLayer7AttentionQueryProjection(ctx);
  BuildLayer7AttentionSdpa(ctx);
  BuildLayer7AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1687, 1688);
  g->Reduce(ynn_reduce_sum, 1688, 2973, {2}, true);
  g->ShapeProduct(1688, 2972, {2});
  g->Binary(ynn_binary_divide, 2973, 2972, 1689);
  g->Binary(ynn_binary_add, 1689, 3016, 1690);
  g->Unary(ynn_unary_rsqrt, 1690, 1691);
  g->Binary(ynn_binary_multiply, 1687, 1691, 1692);
  g->Binary(ynn_binary_multiply, 1692, 3232, 1693);
  g->Binary(ynn_binary_add, 1693, 1618, 1694);
}

// Scope: "Layer7 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1694, 1696);
  g->Reduce(ynn_reduce_sum, 1696, 2975, {2}, true);
  g->ShapeProduct(1696, 2974, {2});
  g->Binary(ynn_binary_divide, 2975, 2974, 1697);
  g->Binary(ynn_binary_add, 1697, 3016, 1698);
  g->Unary(ynn_unary_rsqrt, 1698, 1699);
  g->Binary(ynn_binary_multiply, 1694, 1699, 1700);
  g->Binary(ynn_binary_multiply, 1700, 3235, 1701);
  g->Quantize(1701, 1702, 0.023717211559414864, 0);
  g->Transpose(3229, 2527, {1,0});
  g->Binary(ynn_binary_multiply, 2524, 2526, 2522);
  g->Dot(1702, 2527, YNN_INVALID_VALUE_ID, 2521, 1);
  g->DequantizeTensor(2521, YNN_INVALID_VALUE_ID, 2522, 2523);
  g->QuantizeTensor(2523, 2982, 2525, 1703);
  g->Dequantize(1703, 1704, 0.021899616345763206, 0);
  g->Transpose(3228, 2532, {1,0});
  g->Binary(ynn_binary_multiply, 2524, 2531, 2529);
  g->Dot(1702, 2532, YNN_INVALID_VALUE_ID, 2528, 1);
  g->DequantizeTensor(2528, YNN_INVALID_VALUE_ID, 2529, 2530);
  g->QuantizeTensor(2530, 2982, 2525, 1706);
  g->Dequantize(1706, 1707, 0.021899616345763206, 0);
  g->Polynomial(1707, 2978, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2978, 2979);
  g->Binary(ynn_binary_add, 2979, 2545, 2976);
  g->Binary(ynn_binary_multiply, 1707, 2543, 2977);
  g->Binary(ynn_binary_multiply, 2977, 2976, 1708);
  g->Binary(ynn_binary_multiply, 1704, 1708, 1709);
  g->Quantize(1709, 1710, 0.02202264778316021, 0);
  g->Transpose(3227, 2539, {1,0});
  g->Binary(ynn_binary_multiply, 2536, 2538, 2534);
  g->Dot(1710, 2539, YNN_INVALID_VALUE_ID, 2533, 1);
  g->DequantizeTensor(2533, YNN_INVALID_VALUE_ID, 2534, 2535);
  g->QuantizeTensor(2535, 2982, 2537, 1711);
  g->Dequantize(1711, 1712, 0.01081059779971838, 0);
  g->Unary(ynn_unary_square, 1712, 1713);
  g->Reduce(ynn_reduce_sum, 1713, 2981, {2}, true);
  g->ShapeProduct(1713, 2980, {2});
  g->Binary(ynn_binary_divide, 2981, 2980, 1714);
  g->Binary(ynn_binary_add, 1714, 3016, 1715);
  g->Unary(ynn_unary_rsqrt, 1715, 3);
  g->Binary(ynn_binary_multiply, 1712, 3, 4);
  g->Binary(ynn_binary_multiply, 4, 3233, 5);
  g->Binary(ynn_binary_add, 5, 1694, 6);
}

// Scope: "Layer7 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(421, 7, {0,0,7,0}, {-1,-1,1,-1});
  g->Reshape(7, 8, {1,0,256});
  g->Unary(ynn_unary_square, 8, 9);
  g->Reduce(ynn_reduce_sum, 9, 2541, {2}, true);
  g->ShapeProduct(9, 2540, {2});
  g->Binary(ynn_binary_divide, 2541, 2540, 10);
  g->Binary(ynn_binary_add, 10, 3016, 11);
  g->Unary(ynn_unary_rsqrt, 11, 12);
  g->Binary(ynn_binary_multiply, 8, 12, 14);
  g->Binary(ynn_binary_multiply, 14, 3277, 15);
  g->Binary(ynn_binary_multiply, 3289, 3019, 16);
  g->Binary(ynn_binary_add, 15, 16, 17);
  g->Binary(ynn_binary_multiply, 17, 3014, 18);
  g->Quantize(6, 19, 0.15832224488258362, 0);
  g->Transpose(3230, 1729, {1,0});
  g->Binary(ynn_binary_multiply, 1726, 1728, 1724);
  g->Dot(19, 1729, YNN_INVALID_VALUE_ID, 1723, 1);
  g->DequantizeTensor(1723, YNN_INVALID_VALUE_ID, 1724, 1725);
  g->QuantizeTensor(1725, 2982, 1727, 20);
  g->Dequantize(20, 21, 0.055118121206760406, 0);
  g->Polynomial(21, 2546, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2546, 2547);
  g->Binary(ynn_binary_add, 2547, 2545, 2542);
  g->Binary(ynn_binary_multiply, 21, 2543, 2544);
  g->Binary(ynn_binary_multiply, 2544, 2542, 22);
  g->Binary(ynn_binary_multiply, 22, 18, 23);
  g->Quantize(23, 25, 0.22834646701812744, 0);
  g->Transpose(3231, 1736, {1,0});
  g->Binary(ynn_binary_multiply, 1733, 1735, 1731);
  g->Dot(25, 1736, YNN_INVALID_VALUE_ID, 1730, 1);
  g->DequantizeTensor(1730, YNN_INVALID_VALUE_ID, 1731, 1732);
  g->QuantizeTensor(1732, 2982, 1734, 26);
  g->Dequantize(26, 27, 0.08292699605226517, 0);
  g->Unary(ynn_unary_square, 27, 28);
  g->Reduce(ynn_reduce_sum, 28, 2549, {2}, true);
  g->ShapeProduct(28, 2548, {2});
  g->Binary(ynn_binary_divide, 2549, 2548, 29);
  g->Binary(ynn_binary_add, 29, 3016, 30);
  g->Unary(ynn_unary_rsqrt, 30, 31);
  g->Binary(ynn_binary_multiply, 27, 31, 32);
  g->Binary(ynn_binary_multiply, 32, 3234, 33);
  g->Binary(ynn_binary_add, 6, 33, 34);
  g->Binary(ynn_binary_multiply, 34, 3226, 36);
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
  g->Quantize(42, 43, 0.0820433720946312, 0);
  g->Transpose(3254, 1743, {1,0});
  g->Binary(ynn_binary_multiply, 1740, 1742, 1738);
  g->Dot(43, 1743, YNN_INVALID_VALUE_ID, 1737, 1);
  g->DequantizeTensor(1737, YNN_INVALID_VALUE_ID, 1738, 1739);
  g->QuantizeTensor(1739, 2982, 1741, 44);
  g->Dequantize(44, 45, 0.09251969307661057, 0);
  g->Reshape(45, 47, {1,0,1,256});
  g->Transpose(47, 48, {0,2,1,3});
  g->Unary(ynn_unary_square, 48, 49);
  g->Reduce(ynn_reduce_sum, 49, 2557, {3}, true);
  g->ShapeProduct(49, 2556, {3});
  g->Binary(ynn_binary_divide, 2557, 2556, 50);
  g->Binary(ynn_binary_add, 50, 3016, 51);
  g->Unary(ynn_unary_rsqrt, 51, 52);
  g->Binary(ynn_binary_multiply, 48, 52, 53);
  g->Binary(ynn_binary_multiply, 53, 3253, 54);
  g->Slice(54, 55, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(54, 56, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 56, 58);
  g->Concat({58,55}, 59, 3);
  g->Binary(ynn_binary_multiply, 54, 1096, 60);
  g->Binary(ynn_binary_multiply, 59, 1199, 61);
  g->Binary(ynn_binary_add, 60, 61, 62);
  g->Transpose(3258, 1748, {1,0});
  g->Binary(ynn_binary_multiply, 1740, 1747, 1745);
  g->Dot(43, 1748, YNN_INVALID_VALUE_ID, 1744, 1);
  g->DequantizeTensor(1744, YNN_INVALID_VALUE_ID, 1745, 1746);
  g->QuantizeTensor(1746, 2982, 1741, 63);
  g->Dequantize(63, 64, 0.09251969307661057, 0);
  g->Reshape(64, 65, {1,0,1,256});
  g->Transpose(65, 66, {0,2,1,3});
  g->Unary(ynn_unary_square, 66, 68);
  g->Reduce(ynn_reduce_sum, 68, 2559, {3}, true);
  g->ShapeProduct(68, 2558, {3});
  g->Binary(ynn_binary_divide, 2559, 2558, 69);
  g->Binary(ynn_binary_add, 69, 3016, 70);
  g->Unary(ynn_unary_rsqrt, 70, 71);
  g->Binary(ynn_binary_multiply, 66, 71, 72);
}

// Scope: "Layer8 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(62, 73, 0.006215503439307213, 0);
  g->Append(2996, 73, 3306, 2, s2, s1);
  g->View(3306, 3335, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(72, 74, 0.047244105488061905, 0);
  g->Append(3011, 74, 3321, 2, s2, s1);
  g->View(3321, 3349, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer8 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(3257, 1761, {1,0});
  g->Binary(ynn_binary_multiply, 1740, 1760, 1757);
  g->Dot(43, 1761, YNN_INVALID_VALUE_ID, 1756, 1);
  g->DequantizeTensor(1756, YNN_INVALID_VALUE_ID, 1757, 1758);
  g->QuantizeTensor(1758, 2982, 1759, 76);
  g->Dequantize(76, 77, 0.1250000149011612, 0);
  g->SplitDim(77, 78, 2, {8,256});
  g->Transpose(78, 79, {0,2,1,3});
  g->Unary(ynn_unary_square, 79, 80);
  g->Reduce(ynn_reduce_sum, 80, 2561, {3}, true);
  g->ShapeProduct(80, 2560, {3});
  g->Binary(ynn_binary_divide, 2561, 2560, 81);
  g->Binary(ynn_binary_add, 81, 3016, 82);
  g->Unary(ynn_unary_rsqrt, 82, 83);
  g->Binary(ynn_binary_multiply, 79, 83, 85);
  g->Binary(ynn_binary_multiply, 85, 3256, 86);
  g->Slice(86, 87, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(86, 88, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 88, 89);
  g->Concat({89,87}, 90, 3);
  g->Binary(ynn_binary_multiply, 86, 1096, 91);
  g->Binary(ynn_binary_multiply, 90, 1199, 92);
  g->Binary(ynn_binary_add, 91, 92, 93);
}

// Scope: "Layer8 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(3335, 94, 0.006215503439307213, 0);
  g->Dequantize(3349, 96, 0.047244105488061905, 0);
  g->Matmul(93, 94, 97, false, true);
  g->Mask(97, 3032, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 3032, 2567, {-1}, true);
  g->Binary(ynn_binary_subtract, 3032, 2567, 2564);
  g->Unary(ynn_unary_exp, 2564, 2565);
  g->Reduce(ynn_reduce_sum, 2565, 2568, {-1}, true);
  g->Binary(ynn_binary_divide, 2545, 2568, 2566);
  g->Binary(ynn_binary_multiply, 2565, 2566, 98);
  g->Matmul(98, 96, 99, false, false);
}

// Scope: "Layer8 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(99, 100, {0,2,1,3});
  g->FuseDims(100, 101, 2, 2);
  g->Quantize(101, 102, 0.025713592767715454, 0);
  g->Transpose(3255, 1768, {1,0});
  g->Binary(ynn_binary_multiply, 1765, 1767, 1763);
  g->Dot(102, 1768, YNN_INVALID_VALUE_ID, 1762, 1);
  g->DequantizeTensor(1762, YNN_INVALID_VALUE_ID, 1763, 1764);
  g->QuantizeTensor(1764, 2982, 1766, 103);
  g->Dequantize(103, 104, 0.022537967190146446, 0);
}

// Scope: "Layer8 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 36, 37);
  g->Reduce(ynn_reduce_sum, 37, 2555, {2}, true);
  g->ShapeProduct(37, 2554, {2});
  g->Binary(ynn_binary_divide, 2555, 2554, 38);
  g->Binary(ynn_binary_add, 38, 3016, 39);
  g->Unary(ynn_unary_rsqrt, 39, 40);
  g->Binary(ynn_binary_multiply, 36, 40, 41);
  g->Binary(ynn_binary_multiply, 41, 3242, 42);
  BuildLayer8AttentionKvProjection(ctx);
  BuildLayer8AttentionCacheUpdate(ctx);
  BuildLayer8AttentionQueryProjection(ctx);
  BuildLayer8AttentionSdpa(ctx);
  BuildLayer8AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 104, 107);
  g->Reduce(ynn_reduce_sum, 107, 2570, {2}, true);
  g->ShapeProduct(107, 2569, {2});
  g->Binary(ynn_binary_divide, 2570, 2569, 108);
  g->Binary(ynn_binary_add, 108, 3016, 109);
  g->Unary(ynn_unary_rsqrt, 109, 110);
  g->Binary(ynn_binary_multiply, 104, 110, 111);
  g->Binary(ynn_binary_multiply, 111, 3249, 112);
  g->Binary(ynn_binary_add, 112, 36, 113);
}

// Scope: "Layer8 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 113, 114);
  g->Reduce(ynn_reduce_sum, 114, 2572, {2}, true);
  g->ShapeProduct(114, 2571, {2});
  g->Binary(ynn_binary_divide, 2572, 2571, 115);
  g->Binary(ynn_binary_add, 115, 3016, 116);
  g->Unary(ynn_unary_rsqrt, 116, 118);
  g->Binary(ynn_binary_multiply, 113, 118, 119);
  g->Binary(ynn_binary_multiply, 119, 3252, 120);
  g->Quantize(120, 121, 0.015404289588332176, 0);
  g->Transpose(3246, 1775, {1,0});
  g->Binary(ynn_binary_multiply, 1772, 1774, 1770);
  g->Dot(121, 1775, YNN_INVALID_VALUE_ID, 1769, 1);
  g->DequantizeTensor(1769, YNN_INVALID_VALUE_ID, 1770, 1771);
  g->QuantizeTensor(1771, 2982, 1773, 122);
  g->Dequantize(122, 123, 0.018823828548192978, 0);
  g->Transpose(3245, 1780, {1,0});
  g->Binary(ynn_binary_multiply, 1772, 1779, 1777);
  g->Dot(121, 1780, YNN_INVALID_VALUE_ID, 1776, 1);
  g->DequantizeTensor(1776, YNN_INVALID_VALUE_ID, 1777, 1778);
  g->QuantizeTensor(1778, 2982, 1773, 124);
  g->Dequantize(124, 125, 0.018823828548192978, 0);
  g->Polynomial(125, 2575, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2575, 2576);
  g->Binary(ynn_binary_add, 2576, 2545, 2573);
  g->Binary(ynn_binary_multiply, 125, 2543, 2574);
  g->Binary(ynn_binary_multiply, 2574, 2573, 126);
  g->Binary(ynn_binary_multiply, 123, 126, 128);
  g->Quantize(128, 129, 0.012610738165676594, 0);
  g->Transpose(3244, 1787, {1,0});
  g->Binary(ynn_binary_multiply, 1784, 1786, 1782);
  g->Dot(129, 1787, YNN_INVALID_VALUE_ID, 1781, 1);
  g->DequantizeTensor(1781, YNN_INVALID_VALUE_ID, 1782, 1783);
  g->QuantizeTensor(1783, 2982, 1785, 130);
  g->Dequantize(130, 131, 0.009271269664168358, 0);
  g->Unary(ynn_unary_square, 131, 132);
  g->Reduce(ynn_reduce_sum, 132, 2578, {2}, true);
  g->ShapeProduct(132, 2577, {2});
  g->Binary(ynn_binary_divide, 2578, 2577, 133);
  g->Binary(ynn_binary_add, 133, 3016, 134);
  g->Unary(ynn_unary_rsqrt, 134, 135);
  g->Binary(ynn_binary_multiply, 131, 135, 136);
  g->Binary(ynn_binary_multiply, 136, 3250, 137);
  g->Binary(ynn_binary_add, 137, 113, 139);
}

// Scope: "Layer8 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(421, 140, {0,0,8,0}, {-1,-1,1,-1});
  g->Reshape(140, 141, {1,0,256});
  g->Unary(ynn_unary_square, 141, 142);
  g->Reduce(ynn_reduce_sum, 142, 2580, {2}, true);
  g->ShapeProduct(142, 2579, {2});
  g->Binary(ynn_binary_divide, 2580, 2579, 143);
  g->Binary(ynn_binary_add, 143, 3016, 144);
  g->Unary(ynn_unary_rsqrt, 144, 145);
  g->Binary(ynn_binary_multiply, 141, 145, 146);
  g->Binary(ynn_binary_multiply, 146, 3277, 147);
  g->Binary(ynn_binary_multiply, 3290, 3019, 148);
  g->Binary(ynn_binary_add, 147, 148, 150);
  g->Binary(ynn_binary_multiply, 150, 3014, 151);
  g->Quantize(139, 152, 0.19172413647174835, 0);
  g->Transpose(3247, 1794, {1,0});
  g->Binary(ynn_binary_multiply, 1791, 1793, 1789);
  g->Dot(152, 1794, YNN_INVALID_VALUE_ID, 1788, 1);
  g->DequantizeTensor(1788, YNN_INVALID_VALUE_ID, 1789, 1790);
  g->QuantizeTensor(1790, 2982, 1792, 153);
  g->Dequantize(153, 154, 0.11515748500823975, 0);
  g->Polynomial(154, 2583, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2583, 2584);
  g->Binary(ynn_binary_add, 2584, 2545, 2581);
  g->Binary(ynn_binary_multiply, 154, 2543, 2582);
  g->Binary(ynn_binary_multiply, 2582, 2581, 155);
  g->Binary(ynn_binary_multiply, 155, 151, 156);
  g->Quantize(156, 157, 0.787401556968689, 0);
  g->Transpose(3248, 1801, {1,0});
  g->Binary(ynn_binary_multiply, 1798, 1800, 1796);
  g->Dot(157, 1801, YNN_INVALID_VALUE_ID, 1795, 1);
  g->DequantizeTensor(1795, YNN_INVALID_VALUE_ID, 1796, 1797);
  g->QuantizeTensor(1797, 2982, 1799, 158);
  g->Dequantize(158, 159, 0.2950586676597595, 0);
  g->Unary(ynn_unary_square, 159, 161);
  g->Reduce(ynn_reduce_sum, 161, 2586, {2}, true);
  g->ShapeProduct(161, 2585, {2});
  g->Binary(ynn_binary_divide, 2586, 2585, 162);
  g->Binary(ynn_binary_add, 162, 3016, 163);
  g->Unary(ynn_unary_rsqrt, 163, 164);
  g->Binary(ynn_binary_multiply, 159, 164, 165);
  g->Binary(ynn_binary_multiply, 165, 3251, 166);
  g->Binary(ynn_binary_add, 139, 166, 167);
  g->Binary(ynn_binary_multiply, 167, 3243, 168);
}

// Scope: "Layer8"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8(Context& ctx) {
  BuildLayer8Attention(ctx);
  BuildLayer8Mlp(ctx);
  BuildLayer8PerLayerEmbedding(ctx);
}

}  // namespace BuildGemma4PrefillSource
