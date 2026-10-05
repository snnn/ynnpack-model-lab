// Generated YNNPACK builder; do not edit.
#include "gemma4_decode_builder.h"

namespace BuildGemma4DecodeSource {

// Scope: "Layer8 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Binary(ynn_binary_divide, 795, 7394, 796);
  g->Unary(ynn_unary_round, 796, 797);
  g->Binary(ynn_binary_max, 797, 7225, 798);
  g->Binary(ynn_binary_min, 798, 7340, 799);
  g->Binary(ynn_binary_multiply, 799, 7394, 800);
  g->Convert(8371, 801);
  g->Binary(ynn_binary_multiply, 801, 8372, 802);
  g->Matmul(800, 802, 803, false, true);
  g->Binary(ynn_binary_divide, 803, 7491, 805);
  g->Unary(ynn_unary_round, 805, 806);
  g->Binary(ynn_binary_max, 806, 7225, 807);
  g->Binary(ynn_binary_min, 807, 7340, 808);
  g->Binary(ynn_binary_multiply, 808, 7491, 809);
  g->Reshape(809, 810, {1,1,1,256});
  g->Reshape(810, 811, {1,1,1,256});
  g->Unary(ynn_unary_square, 811, 812);
  g->Reduce(ynn_reduce_sum, 812, 6299, {3}, true);
  g->ShapeProduct(812, 6298, {3});
  g->Binary(ynn_binary_divide, 6299, 6298, 813);
  g->Binary(ynn_binary_add, 813, 7373, 814);
  g->Binary(ynn_binary_pow, 814, 7428, 816);
  g->Binary(ynn_binary_multiply, 811, 816, 817);
  g->Convert(8370, 818);
  g->Binary(ynn_binary_multiply, 817, 818, 819);
  g->Slice(819, 820, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(819, 821, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 821, 822);
  g->Concat({822,820}, 823, 3);
  g->Binary(ynn_binary_multiply, 819, 2044, 824);
  g->Binary(ynn_binary_multiply, 823, 3111, 825);
  g->Binary(ynn_binary_add, 824, 825, 828);
  g->Convert(8378, 829);
  g->Binary(ynn_binary_multiply, 829, 8379, 830);
  g->Matmul(800, 830, 831, false, true);
  g->Binary(ynn_binary_divide, 831, 7491, 832);
  g->Unary(ynn_unary_round, 832, 834);
  g->Binary(ynn_binary_max, 834, 7225, 835);
  g->Binary(ynn_binary_min, 835, 7340, 836);
  g->Binary(ynn_binary_multiply, 836, 7491, 837);
  g->Reshape(837, 838, {1,1,1,256});
  g->Reshape(838, 839, {1,1,1,256});
  g->Unary(ynn_unary_square, 839, 840);
  g->Reduce(ynn_reduce_sum, 840, 6301, {3}, true);
  g->ShapeProduct(840, 6300, {3});
  g->Binary(ynn_binary_divide, 6301, 6300, 841);
  g->Binary(ynn_binary_add, 841, 7373, 842);
  g->Binary(ynn_binary_pow, 842, 7428, 843);
  g->Binary(ynn_binary_multiply, 839, 843, 845);
}

// Scope: "Layer8 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(828, 846, 0.006215503439307213, 0);
  g->Append(7128, 846, 8458, 2, s2, slinky::expr(int64_t{1}));
  g->View(8458, 8488, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(8488, 847, 0.006215503439307213, 0);
  g->Quantize(845, 848, 0.047244105488061905, 0);
  g->Append(7143, 848, 8473, 2, s2, slinky::expr(int64_t{1}));
  g->View(8473, 8503, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(8503, 849, 0.047244105488061905, 0);
}

// Scope: "Layer8 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Convert(8376, 851);
  g->Binary(ynn_binary_multiply, 851, 8377, 852);
  g->Matmul(800, 852, 853, false, true);
  g->Binary(ynn_binary_divide, 853, 7229, 854);
  g->Unary(ynn_unary_round, 854, 855);
  g->Binary(ynn_binary_max, 855, 7225, 856);
  g->Binary(ynn_binary_min, 856, 7340, 858);
  g->Binary(ynn_binary_multiply, 858, 7229, 859);
  g->SplitDim(859, 860, 2, {8,256});
  g->FuseDims(860, 862, 1, 2);
  g->SplitDim(862, 861, 1, {8,1});
  g->Unary(ynn_unary_square, 861, 863);
  g->Reduce(ynn_reduce_sum, 863, 6303, {3}, true);
  g->ShapeProduct(863, 6302, {3});
  g->Binary(ynn_binary_divide, 6303, 6302, 864);
  g->Binary(ynn_binary_add, 864, 7373, 865);
  g->Binary(ynn_binary_pow, 865, 7428, 866);
  g->Binary(ynn_binary_multiply, 861, 866, 867);
  g->Convert(8375, 868);
  g->Binary(ynn_binary_multiply, 867, 868, 870);
  g->Slice(870, 871, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(870, 872, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 872, 873);
  g->Concat({873,871}, 874, 3);
  g->Binary(ynn_binary_multiply, 870, 2044, 875);
  g->Binary(ynn_binary_multiply, 874, 3111, 876);
  g->Binary(ynn_binary_add, 875, 876, 877);
}

// Scope: "Layer8 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(877, 847, 878, false, true);
  g->Mask(878, 7594, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 7594, 6307, {-1}, true);
  g->Binary(ynn_binary_subtract, 7594, 6307, 6304);
  g->Unary(ynn_unary_exp, 6304, 6305);
  g->Reduce(ynn_reduce_sum, 6305, 6308, {-1}, true);
  g->Binary(ynn_binary_divide, 6183, 6308, 6306);
  g->Binary(ynn_binary_multiply, 6305, 6306, 880);
  g->Matmul(880, 849, 881, false, false);
}

// Scope: "Layer8 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(881, 883, 1, 2);
  g->SplitDim(883, 882, 1, {1,8});
  g->FuseDims(882, 884, 2, 2);
  g->Binary(ynn_binary_divide, 884, 7220, 885);
  g->Unary(ynn_unary_round, 885, 886);
  g->Binary(ynn_binary_max, 886, 7225, 887);
  g->Binary(ynn_binary_min, 887, 7340, 888);
  g->Binary(ynn_binary_multiply, 888, 7220, 889);
  g->Convert(8373, 890);
  g->Binary(ynn_binary_multiply, 890, 8374, 892);
  g->Matmul(889, 892, 893, false, true);
  g->Binary(ynn_binary_divide, 893, 7250, 894);
  g->Unary(ynn_unary_round, 894, 895);
  g->Binary(ynn_binary_max, 895, 7225, 896);
  g->Binary(ynn_binary_min, 896, 7340, 897);
  g->Binary(ynn_binary_multiply, 897, 7250, 898);
}

// Scope: "Layer8 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 787, 788);
  g->Reduce(ynn_reduce_sum, 788, 6297, {2}, true);
  g->ShapeProduct(788, 6296, {2});
  g->Binary(ynn_binary_divide, 6297, 6296, 789);
  g->Binary(ynn_binary_add, 789, 7373, 790);
  g->Binary(ynn_binary_pow, 790, 7428, 791);
  g->Binary(ynn_binary_multiply, 787, 791, 792);
  g->Convert(8354, 794);
  g->Binary(ynn_binary_multiply, 792, 794, 795);
  BuildLayer8AttentionKvProjection(ctx);
  BuildLayer8AttentionCacheUpdate(ctx);
  BuildLayer8AttentionQueryProjection(ctx);
  BuildLayer8AttentionSdpa(ctx);
  BuildLayer8AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 898, 899);
  g->Reduce(ynn_reduce_sum, 899, 6310, {2}, true);
  g->ShapeProduct(899, 6309, {2});
  g->Binary(ynn_binary_divide, 6310, 6309, 900);
  g->Binary(ynn_binary_add, 900, 7373, 901);
  g->Binary(ynn_binary_pow, 901, 7428, 903);
  g->Binary(ynn_binary_multiply, 898, 903, 904);
  g->Convert(8366, 905);
  g->Binary(ynn_binary_multiply, 904, 905, 906);
  g->Binary(ynn_binary_add, 787, 906, 907);
}

// Scope: "Layer8 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 907, 908);
  g->Reduce(ynn_reduce_sum, 908, 6312, {2}, true);
  g->ShapeProduct(908, 6311, {2});
  g->Binary(ynn_binary_divide, 6312, 6311, 909);
  g->Binary(ynn_binary_add, 909, 7373, 910);
  g->Binary(ynn_binary_pow, 910, 7428, 911);
  g->Binary(ynn_binary_multiply, 907, 911, 912);
  g->Convert(8369, 914);
  g->Binary(ynn_binary_multiply, 912, 914, 915);
  g->Binary(ynn_binary_divide, 915, 7339, 916);
  g->Unary(ynn_unary_round, 916, 917);
  g->Binary(ynn_binary_max, 917, 7225, 918);
  g->Binary(ynn_binary_min, 918, 7340, 919);
  g->Binary(ynn_binary_multiply, 919, 7339, 920);
  g->Convert(8360, 921);
  g->Binary(ynn_binary_multiply, 921, 8361, 922);
  g->Matmul(920, 922, 923, false, true);
  g->Binary(ynn_binary_divide, 923, 7199, 926);
  g->Unary(ynn_unary_round, 926, 927);
  g->Binary(ynn_binary_max, 927, 7225, 928);
  g->Binary(ynn_binary_min, 928, 7340, 929);
  g->Binary(ynn_binary_multiply, 929, 7199, 930);
  g->Convert(8358, 932);
  g->Binary(ynn_binary_multiply, 932, 8359, 933);
  g->Matmul(920, 933, 934, false, true);
  g->Binary(ynn_binary_divide, 934, 7199, 935);
  g->Unary(ynn_unary_round, 935, 936);
  g->Binary(ynn_binary_max, 936, 7225, 937);
  g->Binary(ynn_binary_min, 937, 7340, 938);
  g->Binary(ynn_binary_multiply, 938, 7199, 939);
  g->Polynomial(939, 6317, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6317, 6318);
  g->Binary(ynn_binary_add, 6318, 6183, 6315);
  g->Binary(ynn_binary_multiply, 939, 6181, 6316);
  g->Binary(ynn_binary_multiply, 6316, 6315, 940);
  g->Binary(ynn_binary_multiply, 930, 940, 941);
  g->Binary(ynn_binary_divide, 941, 7333, 943);
  g->Unary(ynn_unary_round, 943, 944);
  g->Binary(ynn_binary_max, 944, 7225, 945);
  g->Binary(ynn_binary_min, 945, 7340, 946);
  g->Binary(ynn_binary_multiply, 946, 7333, 947);
  g->Convert(8356, 948);
  g->Binary(ynn_binary_multiply, 948, 8357, 949);
  g->Matmul(947, 949, 950, false, true);
  g->Binary(ynn_binary_divide, 950, 7432, 951);
  g->Unary(ynn_unary_round, 951, 952);
  g->Binary(ynn_binary_max, 952, 7225, 954);
  g->Binary(ynn_binary_min, 954, 7340, 955);
  g->Binary(ynn_binary_multiply, 955, 7432, 956);
  g->Unary(ynn_unary_square, 956, 957);
  g->Reduce(ynn_reduce_sum, 957, 6320, {2}, true);
  g->ShapeProduct(957, 6319, {2});
  g->Binary(ynn_binary_divide, 6320, 6319, 958);
  g->Binary(ynn_binary_add, 958, 7373, 959);
  g->Binary(ynn_binary_pow, 959, 7428, 960);
  g->Binary(ynn_binary_multiply, 956, 960, 961);
  g->Convert(8367, 962);
  g->Binary(ynn_binary_multiply, 961, 962, 963);
  g->Binary(ynn_binary_add, 907, 963, 965);
}

// Scope: "Layer8 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1031, 966, {0,0,8,0}, {-1,-1,1,-1});
  g->Reshape(966, 967, {1,1,256});
  g->Binary(ynn_binary_add, 967, 8442, 968);
  g->Binary(ynn_binary_multiply, 968, 7155, 969);
  g->Binary(ynn_binary_divide, 965, 7188, 970);
  g->Unary(ynn_unary_round, 970, 971);
  g->Binary(ynn_binary_max, 971, 7225, 972);
  g->Binary(ynn_binary_min, 972, 7340, 973);
  g->Binary(ynn_binary_multiply, 973, 7188, 974);
  g->Convert(8362, 976);
  g->Binary(ynn_binary_multiply, 976, 8363, 977);
  g->Matmul(974, 977, 978, false, true);
  g->Binary(ynn_binary_divide, 978, 7195, 979);
  g->Unary(ynn_unary_round, 979, 980);
  g->Binary(ynn_binary_max, 980, 7225, 981);
  g->Binary(ynn_binary_min, 981, 7340, 982);
  g->Binary(ynn_binary_multiply, 982, 7195, 983);
  g->Polynomial(983, 6323, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6323, 6324);
  g->Binary(ynn_binary_add, 6324, 6183, 6321);
  g->Binary(ynn_binary_multiply, 983, 6181, 6322);
  g->Binary(ynn_binary_multiply, 6322, 6321, 984);
  g->Binary(ynn_binary_multiply, 984, 969, 985);
  g->Binary(ynn_binary_divide, 985, 7254, 987);
  g->Unary(ynn_unary_round, 987, 988);
  g->Binary(ynn_binary_max, 988, 7225, 989);
  g->Binary(ynn_binary_min, 989, 7340, 990);
  g->Binary(ynn_binary_multiply, 990, 7254, 991);
  g->Convert(8364, 992);
  g->Binary(ynn_binary_multiply, 992, 8365, 993);
  g->Matmul(991, 993, 994, false, true);
  g->Binary(ynn_binary_divide, 994, 7168, 995);
  g->Unary(ynn_unary_round, 995, 996);
  g->Binary(ynn_binary_max, 996, 7225, 998);
  g->Binary(ynn_binary_min, 998, 7340, 999);
  g->Binary(ynn_binary_multiply, 999, 7168, 1000);
  g->Unary(ynn_unary_square, 1000, 1001);
  g->Reduce(ynn_reduce_sum, 1001, 6326, {2}, true);
  g->ShapeProduct(1001, 6325, {2});
  g->Binary(ynn_binary_divide, 6326, 6325, 1002);
  g->Binary(ynn_binary_add, 1002, 7373, 1003);
  g->Binary(ynn_binary_pow, 1003, 7428, 1004);
  g->Binary(ynn_binary_multiply, 1000, 1004, 1005);
  g->Convert(8368, 1006);
  g->Binary(ynn_binary_multiply, 1005, 1006, 1007);
  g->Binary(ynn_binary_add, 965, 1007, 1009);
  g->Convert(8355, 1010);
  g->Binary(ynn_binary_multiply, 1009, 1010, 1011);
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
  g->Binary(ynn_binary_divide, 1018, 7153, 1020);
  g->Unary(ynn_unary_round, 1020, 1021);
  g->Binary(ynn_binary_max, 1021, 7225, 1022);
  g->Binary(ynn_binary_min, 1022, 7340, 1023);
  g->Binary(ynn_binary_multiply, 1023, 7153, 1024);
  g->Convert(8397, 1025);
  g->Binary(ynn_binary_multiply, 1025, 8398, 1026);
  g->Matmul(1024, 1026, 1027, false, true);
  g->Binary(ynn_binary_divide, 1027, 7498, 1028);
  g->Unary(ynn_unary_round, 1028, 1029);
  g->Binary(ynn_binary_max, 1029, 7225, 1033);
  g->Binary(ynn_binary_min, 1033, 7340, 1034);
  g->Binary(ynn_binary_multiply, 1034, 7498, 1035);
  g->Reshape(1035, 1036, {1,1,1,512});
  g->Reshape(1036, 1037, {1,1,1,512});
  g->Unary(ynn_unary_square, 1037, 1038);
  g->Reduce(ynn_reduce_sum, 1038, 6330, {3}, true);
  g->ShapeProduct(1038, 6329, {3});
  g->Binary(ynn_binary_divide, 6330, 6329, 1039);
  g->Binary(ynn_binary_add, 1039, 7373, 1040);
  g->Binary(ynn_binary_pow, 1040, 7428, 1041);
  g->Binary(ynn_binary_multiply, 1037, 1041, 1042);
  g->Convert(8396, 1044);
  g->Binary(ynn_binary_multiply, 1042, 1044, 1045);
  g->Slice(1045, 1046, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(1045, 1047, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 1047, 1048);
  g->Concat({1048,1046}, 1049, 3);
  g->Binary(ynn_binary_multiply, 1045, 5976, 1050);
  g->Binary(ynn_binary_multiply, 1049, 6075, 1051);
  g->Binary(ynn_binary_add, 1050, 1051, 1052);
  g->Convert(8404, 1054);
  g->Binary(ynn_binary_multiply, 1054, 8405, 1055);
  g->Matmul(1024, 1055, 1056, false, true);
  g->Binary(ynn_binary_divide, 1056, 7498, 1057);
  g->Unary(ynn_unary_round, 1057, 1058);
  g->Binary(ynn_binary_max, 1058, 7225, 1059);
  g->Binary(ynn_binary_min, 1059, 7340, 1061);
  g->Binary(ynn_binary_multiply, 1061, 7498, 1062);
  g->Reshape(1062, 1063, {1,1,1,512});
  g->Reshape(1063, 1064, {1,1,1,512});
  g->Unary(ynn_unary_square, 1064, 1065);
  g->Reduce(ynn_reduce_sum, 1065, 6332, {3}, true);
  g->ShapeProduct(1065, 6331, {3});
  g->Binary(ynn_binary_divide, 6332, 6331, 1066);
  g->Binary(ynn_binary_add, 1066, 7373, 1067);
  g->Binary(ynn_binary_pow, 1067, 7428, 1068);
  g->Binary(ynn_binary_multiply, 1064, 1068, 1069);
}

// Scope: "Layer9 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(1052, 1070, 0.0010733711533248425, 0);
  g->Append(7129, 1070, 8459, 2, s2, slinky::expr(int64_t{1}));
  g->View(8459, 8489, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(8489, 1072, 0.0010733711533248425, 0);
  g->Quantize(1069, 1073, 0.01785714365541935, 0);
  g->Append(7144, 1073, 8474, 2, s2, slinky::expr(int64_t{1}));
  g->View(8474, 8504, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(8504, 1074, 0.01785714365541935, 0);
}

// Scope: "Layer9 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Convert(8402, 1076);
  g->Binary(ynn_binary_multiply, 1076, 8403, 1077);
  g->Matmul(1024, 1077, 1078, false, true);
  g->Binary(ynn_binary_divide, 1078, 7286, 1079);
  g->Unary(ynn_unary_round, 1079, 1080);
  g->Binary(ynn_binary_max, 1080, 7225, 1081);
  g->Binary(ynn_binary_min, 1081, 7340, 1082);
  g->Binary(ynn_binary_multiply, 1082, 7286, 1083);
  g->SplitDim(1083, 1085, 2, {8,512});
  g->FuseDims(1085, 1087, 1, 2);
  g->SplitDim(1087, 1086, 1, {8,1});
  g->Unary(ynn_unary_square, 1086, 1088);
  g->Reduce(ynn_reduce_sum, 1088, 6334, {3}, true);
  g->ShapeProduct(1088, 6333, {3});
  g->Binary(ynn_binary_divide, 6334, 6333, 1089);
  g->Binary(ynn_binary_add, 1089, 7373, 1090);
  g->Binary(ynn_binary_pow, 1090, 7428, 1091);
  g->Binary(ynn_binary_multiply, 1086, 1091, 1092);
  g->Convert(8401, 1093);
  g->Binary(ynn_binary_multiply, 1092, 1093, 1094);
  g->Slice(1094, 1095, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(1094, 1097, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 1097, 1098);
  g->Concat({1098,1095}, 1099, 3);
  g->Binary(ynn_binary_multiply, 1094, 5976, 1100);
  g->Binary(ynn_binary_multiply, 1099, 6075, 1101);
  g->Binary(ynn_binary_add, 1100, 1101, 1102);
}

// Scope: "Layer9 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(1102, 1072, 1103, false, true);
  g->Mask(1103, 7595, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 7595, 6338, {-1}, true);
  g->Binary(ynn_binary_subtract, 7595, 6338, 6335);
  g->Unary(ynn_unary_exp, 6335, 6336);
  g->Reduce(ynn_reduce_sum, 6336, 6339, {-1}, true);
  g->Binary(ynn_binary_divide, 6183, 6339, 6337);
  g->Binary(ynn_binary_multiply, 6336, 6337, 1104);
  g->Matmul(1104, 1074, 1105, false, false);
}

// Scope: "Layer9 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(1105, 1108, 1, 2);
  g->SplitDim(1108, 1107, 1, {1,8});
  g->FuseDims(1107, 1109, 2, 2);
  g->Binary(ynn_binary_divide, 1109, 7315, 1110);
  g->Unary(ynn_unary_round, 1110, 1111);
  g->Binary(ynn_binary_max, 1111, 7225, 1112);
  g->Binary(ynn_binary_min, 1112, 7340, 1113);
  g->Binary(ynn_binary_multiply, 1113, 7315, 1114);
  g->Convert(8399, 1115);
  g->Binary(ynn_binary_multiply, 1115, 8400, 1116);
  g->Matmul(1114, 1116, 1117, false, true);
  g->Binary(ynn_binary_divide, 1117, 7206, 1119);
  g->Unary(ynn_unary_round, 1119, 1120);
  g->Binary(ynn_binary_max, 1120, 7225, 1121);
  g->Binary(ynn_binary_min, 1121, 7340, 1122);
  g->Binary(ynn_binary_multiply, 1122, 7206, 1123);
}

// Scope: "Layer9 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1011, 1012);
  g->Reduce(ynn_reduce_sum, 1012, 6328, {2}, true);
  g->ShapeProduct(1012, 6327, {2});
  g->Binary(ynn_binary_divide, 6328, 6327, 1013);
  g->Binary(ynn_binary_add, 1013, 7373, 1014);
  g->Binary(ynn_binary_pow, 1014, 7428, 1015);
  g->Binary(ynn_binary_multiply, 1011, 1015, 1016);
  g->Convert(8380, 1017);
  g->Binary(ynn_binary_multiply, 1016, 1017, 1018);
  BuildLayer9AttentionKvProjection(ctx);
  BuildLayer9AttentionCacheUpdate(ctx);
  BuildLayer9AttentionQueryProjection(ctx);
  BuildLayer9AttentionSdpa(ctx);
  BuildLayer9AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1123, 1124);
  g->Reduce(ynn_reduce_sum, 1124, 6341, {2}, true);
  g->ShapeProduct(1124, 6340, {2});
  g->Binary(ynn_binary_divide, 6341, 6340, 1125);
  g->Binary(ynn_binary_add, 1125, 7373, 1126);
  g->Binary(ynn_binary_pow, 1126, 7428, 1127);
  g->Binary(ynn_binary_multiply, 1123, 1127, 1128);
  g->Convert(8392, 1131);
  g->Binary(ynn_binary_multiply, 1128, 1131, 1132);
  g->Binary(ynn_binary_add, 1011, 1132, 1133);
}

// Scope: "Layer9 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1133, 1134);
  g->Reduce(ynn_reduce_sum, 1134, 6343, {2}, true);
  g->ShapeProduct(1134, 6342, {2});
  g->Binary(ynn_binary_divide, 6343, 6342, 1135);
  g->Binary(ynn_binary_add, 1135, 7373, 1136);
  g->Binary(ynn_binary_pow, 1136, 7428, 1137);
  g->Binary(ynn_binary_multiply, 1133, 1137, 1138);
  g->Convert(8395, 1139);
  g->Binary(ynn_binary_multiply, 1138, 1139, 1140);
  g->Binary(ynn_binary_divide, 1140, 7395, 1142);
  g->Unary(ynn_unary_round, 1142, 1143);
  g->Binary(ynn_binary_max, 1143, 7225, 1144);
  g->Binary(ynn_binary_min, 1144, 7340, 1145);
  g->Binary(ynn_binary_multiply, 1145, 7395, 1146);
  g->Convert(8386, 1147);
  g->Binary(ynn_binary_multiply, 1147, 8387, 1148);
  g->Matmul(1146, 1148, 1149, false, true);
  g->Binary(ynn_binary_divide, 1149, 7385, 1150);
  g->Unary(ynn_unary_round, 1150, 1151);
  g->Binary(ynn_binary_max, 1151, 7225, 1153);
  g->Binary(ynn_binary_min, 1153, 7340, 1154);
  g->Binary(ynn_binary_multiply, 1154, 7385, 1155);
  g->Convert(8384, 1156);
  g->Binary(ynn_binary_multiply, 1156, 8385, 1157);
  g->Matmul(1146, 1157, 1159, false, true);
  g->Binary(ynn_binary_divide, 1159, 7385, 1160);
  g->Unary(ynn_unary_round, 1160, 1161);
  g->Binary(ynn_binary_max, 1161, 7225, 1162);
  g->Binary(ynn_binary_min, 1162, 7340, 1163);
  g->Binary(ynn_binary_multiply, 1163, 7385, 1164);
  g->Polynomial(1164, 6346, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6346, 6347);
  g->Binary(ynn_binary_add, 6347, 6183, 6344);
  g->Binary(ynn_binary_multiply, 1164, 6181, 6345);
  g->Binary(ynn_binary_multiply, 6345, 6344, 1165);
  g->Binary(ynn_binary_multiply, 1155, 1165, 1166);
  g->Binary(ynn_binary_divide, 1166, 7492, 1167);
  g->Unary(ynn_unary_round, 1167, 1168);
  g->Binary(ynn_binary_max, 1168, 7225, 1170);
  g->Binary(ynn_binary_min, 1170, 7340, 1171);
  g->Binary(ynn_binary_multiply, 1171, 7492, 1172);
  g->Convert(8382, 1173);
  g->Binary(ynn_binary_multiply, 1173, 8383, 1174);
  g->Matmul(1172, 1174, 1175, false, true);
  g->Binary(ynn_binary_divide, 1175, 7240, 1176);
  g->Unary(ynn_unary_round, 1176, 1177);
  g->Binary(ynn_binary_max, 1177, 7225, 1178);
  g->Binary(ynn_binary_min, 1178, 7340, 1179);
  g->Binary(ynn_binary_multiply, 1179, 7240, 1181);
  g->Unary(ynn_unary_square, 1181, 1182);
  g->Reduce(ynn_reduce_sum, 1182, 6353, {2}, true);
  g->ShapeProduct(1182, 6352, {2});
  g->Binary(ynn_binary_divide, 6353, 6352, 1183);
  g->Binary(ynn_binary_add, 1183, 7373, 1184);
  g->Binary(ynn_binary_pow, 1184, 7428, 1185);
  g->Binary(ynn_binary_multiply, 1181, 1185, 1186);
  g->Convert(8393, 1187);
  g->Binary(ynn_binary_multiply, 1186, 1187, 1188);
  g->Binary(ynn_binary_add, 1133, 1188, 1189);
}

// Scope: "Layer9 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1031, 1190, {0,0,9,0}, {-1,-1,1,-1});
  g->Reshape(1190, 1192, {1,1,256});
  g->Binary(ynn_binary_add, 1192, 8443, 1193);
  g->Binary(ynn_binary_multiply, 1193, 7155, 1194);
  g->Binary(ynn_binary_divide, 1189, 7252, 1195);
  g->Unary(ynn_unary_round, 1195, 1196);
  g->Binary(ynn_binary_max, 1196, 7225, 1197);
  g->Binary(ynn_binary_min, 1197, 7340, 1198);
  g->Binary(ynn_binary_multiply, 1198, 7252, 1199);
  g->Convert(8388, 1200);
  g->Binary(ynn_binary_multiply, 1200, 8389, 1201);
  g->Matmul(1199, 1201, 1203, false, true);
  g->Binary(ynn_binary_divide, 1203, 7246, 1204);
  g->Unary(ynn_unary_round, 1204, 1205);
  g->Binary(ynn_binary_max, 1205, 7225, 1206);
  g->Binary(ynn_binary_min, 1206, 7340, 1207);
  g->Binary(ynn_binary_multiply, 1207, 7246, 1208);
  g->Polynomial(1208, 6356, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6356, 6357);
  g->Binary(ynn_binary_add, 6357, 6183, 6354);
  g->Binary(ynn_binary_multiply, 1208, 6181, 6355);
  g->Binary(ynn_binary_multiply, 6355, 6354, 1209);
  g->Binary(ynn_binary_multiply, 1209, 1194, 1210);
  g->Binary(ynn_binary_divide, 1210, 7413, 1211);
  g->Unary(ynn_unary_round, 1211, 1212);
  g->Binary(ynn_binary_max, 1212, 7225, 1214);
  g->Binary(ynn_binary_min, 1214, 7340, 1215);
  g->Binary(ynn_binary_multiply, 1215, 7413, 1216);
  g->Convert(8390, 1217);
  g->Binary(ynn_binary_multiply, 1217, 8391, 1218);
  g->Matmul(1216, 1218, 1219, false, true);
  g->Binary(ynn_binary_divide, 1219, 7495, 1220);
  g->Unary(ynn_unary_round, 1220, 1221);
  g->Binary(ynn_binary_max, 1221, 7225, 1222);
  g->Binary(ynn_binary_min, 1222, 7340, 1223);
  g->Binary(ynn_binary_multiply, 1223, 7495, 1225);
  g->Unary(ynn_unary_square, 1225, 1226);
  g->Reduce(ynn_reduce_sum, 1226, 6359, {2}, true);
  g->ShapeProduct(1226, 6358, {2});
  g->Binary(ynn_binary_divide, 6359, 6358, 1227);
  g->Binary(ynn_binary_add, 1227, 7373, 1228);
  g->Binary(ynn_binary_pow, 1228, 7428, 1229);
  g->Binary(ynn_binary_multiply, 1225, 1229, 1230);
  g->Convert(8394, 1231);
  g->Binary(ynn_binary_multiply, 1230, 1231, 1232);
  g->Binary(ynn_binary_add, 1189, 1232, 1233);
  g->Convert(8381, 1234);
  g->Binary(ynn_binary_multiply, 1233, 1234, 1237);
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
  g->Binary(ynn_binary_divide, 1244, 7242, 1245);
  g->Unary(ynn_unary_round, 1245, 1246);
  g->Binary(ynn_binary_max, 1246, 7225, 1248);
  g->Binary(ynn_binary_min, 1248, 7340, 1249);
  g->Binary(ynn_binary_multiply, 1249, 7242, 1250);
  g->Convert(7665, 1251);
  g->Binary(ynn_binary_multiply, 1251, 7666, 1252);
  g->Matmul(1250, 1252, 1253, false, true);
  g->Binary(ynn_binary_divide, 1253, 7166, 1254);
  g->Unary(ynn_unary_round, 1254, 1255);
  g->Binary(ynn_binary_max, 1255, 7225, 1256);
  g->Binary(ynn_binary_min, 1256, 7340, 1257);
  g->Binary(ynn_binary_multiply, 1257, 7166, 1259);
  g->Reshape(1259, 1260, {1,1,1,256});
  g->Reshape(1260, 1261, {1,1,1,256});
  g->Unary(ynn_unary_square, 1261, 1262);
  g->Reduce(ynn_reduce_sum, 1262, 6365, {3}, true);
  g->ShapeProduct(1262, 6364, {3});
  g->Binary(ynn_binary_divide, 6365, 6364, 1263);
  g->Binary(ynn_binary_add, 1263, 7373, 1264);
  g->Binary(ynn_binary_pow, 1264, 7428, 1265);
  g->Binary(ynn_binary_multiply, 1261, 1265, 1266);
  g->Convert(7664, 1267);
  g->Binary(ynn_binary_multiply, 1266, 1267, 1268);
  g->Slice(1268, 1270, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1268, 1271, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1271, 1272);
  g->Concat({1272,1270}, 1273, 3);
  g->Binary(ynn_binary_multiply, 1268, 2044, 1274);
  g->Binary(ynn_binary_multiply, 1273, 3111, 1275);
  g->Binary(ynn_binary_add, 1274, 1275, 1276);
  g->Convert(7672, 1278);
  g->Binary(ynn_binary_multiply, 1278, 7673, 1279);
  g->Matmul(1250, 1279, 1280, false, true);
  g->Binary(ynn_binary_divide, 1280, 7166, 1281);
  g->Unary(ynn_unary_round, 1281, 1282);
  g->Binary(ynn_binary_max, 1282, 7225, 1283);
  g->Binary(ynn_binary_min, 1283, 7340, 1284);
  g->Binary(ynn_binary_multiply, 1284, 7166, 1285);
  g->Reshape(1285, 1287, {1,1,1,256});
  g->Reshape(1287, 1288, {1,1,1,256});
  g->Unary(ynn_unary_square, 1288, 1289);
  g->Reduce(ynn_reduce_sum, 1289, 6367, {3}, true);
  g->ShapeProduct(1289, 6366, {3});
  g->Binary(ynn_binary_divide, 6367, 6366, 1290);
  g->Binary(ynn_binary_add, 1290, 7373, 1291);
  g->Binary(ynn_binary_pow, 1291, 7428, 1292);
  g->Binary(ynn_binary_multiply, 1288, 1292, 1293);
}

// Scope: "Layer10 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(1276, 1294, 0.005712664220482111, 0);
  g->Append(7117, 1294, 8447, 2, s2, slinky::expr(int64_t{1}));
  g->View(8447, 8477, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(8477, 1296, 0.005712664220482111, 0);
  g->Quantize(1293, 1297, 0.047244105488061905, 0);
  g->Append(7132, 1297, 8462, 2, s2, slinky::expr(int64_t{1}));
  g->View(8462, 8492, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(8492, 1298, 0.047244105488061905, 0);
}

// Scope: "Layer10 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Convert(7670, 1300);
  g->Binary(ynn_binary_multiply, 1300, 7671, 1301);
  g->Matmul(1250, 1301, 1302, false, true);
  g->Binary(ynn_binary_divide, 1302, 7440, 1303);
  g->Unary(ynn_unary_round, 1303, 1304);
  g->Binary(ynn_binary_max, 1304, 7225, 1305);
  g->Binary(ynn_binary_min, 1305, 7340, 1306);
  g->Binary(ynn_binary_multiply, 1306, 7440, 1307);
  g->SplitDim(1307, 1308, 2, {8,256});
  g->FuseDims(1308, 1310, 1, 2);
  g->SplitDim(1310, 1309, 1, {8,1});
  g->Unary(ynn_unary_square, 1309, 1312);
  g->Reduce(ynn_reduce_sum, 1312, 6369, {3}, true);
  g->ShapeProduct(1312, 6368, {3});
  g->Binary(ynn_binary_divide, 6369, 6368, 1313);
  g->Binary(ynn_binary_add, 1313, 7373, 1314);
  g->Binary(ynn_binary_pow, 1314, 7428, 1315);
  g->Binary(ynn_binary_multiply, 1309, 1315, 1316);
  g->Convert(7669, 1317);
  g->Binary(ynn_binary_multiply, 1316, 1317, 1318);
  g->Slice(1318, 1319, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1318, 1320, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1320, 1321);
  g->Concat({1321,1319}, 1323, 3);
  g->Binary(ynn_binary_multiply, 1318, 2044, 1324);
  g->Binary(ynn_binary_multiply, 1323, 3111, 1325);
  g->Binary(ynn_binary_add, 1324, 1325, 1326);
}

// Scope: "Layer10 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(1326, 1296, 1327, false, true);
  g->Mask(1327, 7563, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 7563, 6373, {-1}, true);
  g->Binary(ynn_binary_subtract, 7563, 6373, 6370);
  g->Unary(ynn_unary_exp, 6370, 6371);
  g->Reduce(ynn_reduce_sum, 6371, 6374, {-1}, true);
  g->Binary(ynn_binary_divide, 6183, 6374, 6372);
  g->Binary(ynn_binary_multiply, 6371, 6372, 1328);
  g->Matmul(1328, 1298, 1329, false, false);
}

// Scope: "Layer10 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(1329, 1331, 1, 2);
  g->SplitDim(1331, 1330, 1, {1,8});
  g->FuseDims(1330, 1332, 2, 2);
  g->Binary(ynn_binary_divide, 1332, 7341, 1335);
  g->Unary(ynn_unary_round, 1335, 1336);
  g->Binary(ynn_binary_max, 1336, 7225, 1337);
  g->Binary(ynn_binary_min, 1337, 7340, 1338);
  g->Binary(ynn_binary_multiply, 1338, 7341, 1339);
  g->Convert(7667, 1340);
  g->Binary(ynn_binary_multiply, 1340, 7668, 1341);
  g->Matmul(1339, 1341, 1342, false, true);
  g->Binary(ynn_binary_divide, 1342, 7338, 1343);
  g->Unary(ynn_unary_round, 1343, 1344);
  g->Binary(ynn_binary_max, 1344, 7225, 1346);
  g->Binary(ynn_binary_min, 1346, 7340, 1347);
  g->Binary(ynn_binary_multiply, 1347, 7338, 1348);
}

// Scope: "Layer10 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1237, 1238);
  g->Reduce(ynn_reduce_sum, 1238, 6363, {2}, true);
  g->ShapeProduct(1238, 6362, {2});
  g->Binary(ynn_binary_divide, 6363, 6362, 1239);
  g->Binary(ynn_binary_add, 1239, 7373, 1240);
  g->Binary(ynn_binary_pow, 1240, 7428, 1241);
  g->Binary(ynn_binary_multiply, 1237, 1241, 1242);
  g->Convert(7648, 1243);
  g->Binary(ynn_binary_multiply, 1242, 1243, 1244);
  BuildLayer10AttentionKvProjection(ctx);
  BuildLayer10AttentionCacheUpdate(ctx);
  BuildLayer10AttentionQueryProjection(ctx);
  BuildLayer10AttentionSdpa(ctx);
  BuildLayer10AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1348, 1349);
  g->Reduce(ynn_reduce_sum, 1349, 6378, {2}, true);
  g->ShapeProduct(1349, 6377, {2});
  g->Binary(ynn_binary_divide, 6378, 6377, 1350);
  g->Binary(ynn_binary_add, 1350, 7373, 1351);
  g->Binary(ynn_binary_pow, 1351, 7428, 1352);
  g->Binary(ynn_binary_multiply, 1348, 1352, 1353);
  g->Convert(7660, 1354);
  g->Binary(ynn_binary_multiply, 1353, 1354, 1355);
  g->Binary(ynn_binary_add, 1237, 1355, 1357);
}

// Scope: "Layer10 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1357, 1358);
  g->Reduce(ynn_reduce_sum, 1358, 6380, {2}, true);
  g->ShapeProduct(1358, 6379, {2});
  g->Binary(ynn_binary_divide, 6380, 6379, 1359);
  g->Binary(ynn_binary_add, 1359, 7373, 1360);
  g->Binary(ynn_binary_pow, 1360, 7428, 1361);
  g->Binary(ynn_binary_multiply, 1357, 1361, 1362);
  g->Convert(7663, 1363);
  g->Binary(ynn_binary_multiply, 1362, 1363, 1364);
  g->Binary(ynn_binary_divide, 1364, 7425, 1365);
  g->Unary(ynn_unary_round, 1365, 1366);
  g->Binary(ynn_binary_max, 1366, 7225, 1368);
  g->Binary(ynn_binary_min, 1368, 7340, 1369);
  g->Binary(ynn_binary_multiply, 1369, 7425, 1370);
  g->Convert(7654, 1371);
  g->Binary(ynn_binary_multiply, 1371, 7655, 1372);
  g->Matmul(1370, 1372, 1373, false, true);
  g->Binary(ynn_binary_divide, 1373, 7202, 1374);
  g->Unary(ynn_unary_round, 1374, 1375);
  g->Binary(ynn_binary_max, 1375, 7225, 1376);
  g->Binary(ynn_binary_min, 1376, 7340, 1377);
  g->Binary(ynn_binary_multiply, 1377, 7202, 1379);
  g->Convert(7652, 1380);
  g->Binary(ynn_binary_multiply, 1380, 7653, 1381);
  g->Matmul(1370, 1381, 1382, false, true);
  g->Binary(ynn_binary_divide, 1382, 7202, 1383);
  g->Unary(ynn_unary_round, 1383, 1385);
  g->Binary(ynn_binary_max, 1385, 7225, 1386);
  g->Binary(ynn_binary_min, 1386, 7340, 1387);
  g->Binary(ynn_binary_multiply, 1387, 7202, 1388);
  g->Polynomial(1388, 6383, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6383, 6384);
  g->Binary(ynn_binary_add, 6384, 6183, 6381);
  g->Binary(ynn_binary_multiply, 1388, 6181, 6382);
  g->Binary(ynn_binary_multiply, 6382, 6381, 1389);
  g->Binary(ynn_binary_multiply, 1379, 1389, 1390);
  g->Binary(ynn_binary_divide, 1390, 7530, 1391);
  g->Unary(ynn_unary_round, 1391, 1392);
  g->Binary(ynn_binary_max, 1392, 7225, 1393);
  g->Binary(ynn_binary_min, 1393, 7340, 1394);
  g->Binary(ynn_binary_multiply, 1394, 7530, 1396);
  g->Convert(7650, 1397);
  g->Binary(ynn_binary_multiply, 1397, 7651, 1398);
  g->Matmul(1396, 1398, 1399, false, true);
  g->Binary(ynn_binary_divide, 1399, 7280, 1400);
  g->Unary(ynn_unary_round, 1400, 1401);
  g->Binary(ynn_binary_max, 1401, 7225, 1402);
  g->Binary(ynn_binary_min, 1402, 7340, 1403);
  g->Binary(ynn_binary_multiply, 1403, 7280, 1404);
  g->Unary(ynn_unary_square, 1404, 1405);
  g->Reduce(ynn_reduce_sum, 1405, 6386, {2}, true);
  g->ShapeProduct(1405, 6385, {2});
  g->Binary(ynn_binary_divide, 6386, 6385, 1407);
  g->Binary(ynn_binary_add, 1407, 7373, 1408);
  g->Binary(ynn_binary_pow, 1408, 7428, 1409);
  g->Binary(ynn_binary_multiply, 1404, 1409, 1410);
  g->Convert(7661, 1411);
  g->Binary(ynn_binary_multiply, 1410, 1411, 1412);
  g->Binary(ynn_binary_add, 1357, 1412, 1413);
}

// Scope: "Layer10 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1031, 1414, {0,0,10,0}, {-1,-1,1,-1});
  g->Reshape(1414, 1415, {1,1,256});
  g->Binary(ynn_binary_add, 1415, 8411, 1416);
  g->Binary(ynn_binary_multiply, 1416, 7155, 1418);
  g->Binary(ynn_binary_divide, 1413, 7214, 1419);
  g->Unary(ynn_unary_round, 1419, 1420);
  g->Binary(ynn_binary_max, 1420, 7225, 1421);
  g->Binary(ynn_binary_min, 1421, 7340, 1422);
  g->Binary(ynn_binary_multiply, 1422, 7214, 1423);
  g->Convert(7656, 1424);
  g->Binary(ynn_binary_multiply, 1424, 7657, 1425);
  g->Matmul(1423, 1425, 1426, false, true);
  g->Binary(ynn_binary_divide, 1426, 7521, 1427);
  g->Unary(ynn_unary_round, 1427, 1429);
  g->Binary(ynn_binary_max, 1429, 7225, 1430);
  g->Binary(ynn_binary_min, 1430, 7340, 1431);
  g->Binary(ynn_binary_multiply, 1431, 7521, 1432);
  g->Polynomial(1432, 6389, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6389, 6390);
  g->Binary(ynn_binary_add, 6390, 6183, 6387);
  g->Binary(ynn_binary_multiply, 1432, 6181, 6388);
  g->Binary(ynn_binary_multiply, 6388, 6387, 1433);
  g->Binary(ynn_binary_multiply, 1433, 1418, 1434);
  g->Binary(ynn_binary_divide, 1434, 7223, 1435);
  g->Unary(ynn_unary_round, 1435, 1436);
  g->Binary(ynn_binary_max, 1436, 7225, 1437);
  g->Binary(ynn_binary_min, 1437, 7340, 1438);
  g->Binary(ynn_binary_multiply, 1438, 7223, 1441);
  g->Convert(7658, 1442);
  g->Binary(ynn_binary_multiply, 1442, 7659, 1443);
  g->Matmul(1441, 1443, 1444, false, true);
  g->Binary(ynn_binary_divide, 1444, 7461, 1445);
  g->Unary(ynn_unary_round, 1445, 1446);
  g->Binary(ynn_binary_max, 1446, 7225, 1447);
  g->Binary(ynn_binary_min, 1447, 7340, 1448);
  g->Binary(ynn_binary_multiply, 1448, 7461, 1449);
  g->Unary(ynn_unary_square, 1449, 1450);
  g->Reduce(ynn_reduce_sum, 1450, 6394, {2}, true);
  g->ShapeProduct(1450, 6393, {2});
  g->Binary(ynn_binary_divide, 6394, 6393, 1452);
  g->Binary(ynn_binary_add, 1452, 7373, 1453);
  g->Binary(ynn_binary_pow, 1453, 7428, 1454);
  g->Binary(ynn_binary_multiply, 1449, 1454, 1455);
  g->Convert(7662, 1456);
  g->Binary(ynn_binary_multiply, 1455, 1456, 1457);
  g->Binary(ynn_binary_add, 1413, 1457, 1458);
  g->Convert(7649, 1459);
  g->Binary(ynn_binary_multiply, 1458, 1459, 1460);
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
  g->Binary(ynn_binary_divide, 1468, 7497, 1469);
  g->Unary(ynn_unary_round, 1469, 1470);
  g->Binary(ynn_binary_max, 1470, 7225, 1471);
  g->Binary(ynn_binary_min, 1471, 7340, 1472);
  g->Binary(ynn_binary_multiply, 1472, 7497, 1474);
  g->Convert(7691, 1475);
  g->Binary(ynn_binary_multiply, 1475, 7692, 1476);
  g->Matmul(1474, 1476, 1477, false, true);
  g->Binary(ynn_binary_divide, 1477, 7482, 1478);
  g->Unary(ynn_unary_round, 1478, 1479);
  g->Binary(ynn_binary_max, 1479, 7225, 1480);
  g->Binary(ynn_binary_min, 1480, 7340, 1481);
  g->Binary(ynn_binary_multiply, 1481, 7482, 1482);
  g->Reshape(1482, 1483, {1,1,1,256});
  g->Reshape(1483, 1485, {1,1,1,256});
  g->Unary(ynn_unary_square, 1485, 1486);
  g->Reduce(ynn_reduce_sum, 1486, 6398, {3}, true);
  g->ShapeProduct(1486, 6397, {3});
  g->Binary(ynn_binary_divide, 6398, 6397, 1487);
  g->Binary(ynn_binary_add, 1487, 7373, 1488);
  g->Binary(ynn_binary_pow, 1488, 7428, 1489);
  g->Binary(ynn_binary_multiply, 1485, 1489, 1490);
  g->Convert(7690, 1491);
  g->Binary(ynn_binary_multiply, 1490, 1491, 1492);
  g->Slice(1492, 1493, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1492, 1494, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1494, 1496);
  g->Concat({1496,1493}, 1497, 3);
  g->Binary(ynn_binary_multiply, 1492, 2044, 1498);
  g->Binary(ynn_binary_multiply, 1497, 3111, 1499);
  g->Binary(ynn_binary_add, 1498, 1499, 1500);
  g->Convert(7698, 1502);
  g->Binary(ynn_binary_multiply, 1502, 7699, 1503);
  g->Matmul(1474, 1503, 1504, false, true);
  g->Binary(ynn_binary_divide, 1504, 7482, 1505);
  g->Unary(ynn_unary_round, 1505, 1506);
  g->Binary(ynn_binary_max, 1506, 7225, 1507);
  g->Binary(ynn_binary_min, 1507, 7340, 1508);
  g->Binary(ynn_binary_multiply, 1508, 7482, 1509);
  g->Reshape(1509, 1510, {1,1,1,256});
  g->Reshape(1510, 1511, {1,1,1,256});
  g->Unary(ynn_unary_square, 1511, 1513);
  g->Reduce(ynn_reduce_sum, 1513, 6400, {3}, true);
  g->ShapeProduct(1513, 6399, {3});
  g->Binary(ynn_binary_divide, 6400, 6399, 1514);
  g->Binary(ynn_binary_add, 1514, 7373, 1515);
  g->Binary(ynn_binary_pow, 1515, 7428, 1516);
  g->Binary(ynn_binary_multiply, 1511, 1516, 1517);
}

// Scope: "Layer11 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(1500, 1518, 0.005907459184527397, 0);
  g->Append(7118, 1518, 8448, 2, s2, slinky::expr(int64_t{1}));
  g->View(8448, 8478, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(8478, 1519, 0.005907459184527397, 0);
  g->Quantize(1517, 1520, 0.047244105488061905, 0);
  g->Append(7133, 1520, 8463, 2, s2, slinky::expr(int64_t{1}));
  g->View(8463, 8493, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(8493, 1522, 0.047244105488061905, 0);
}

// Scope: "Layer11 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Convert(7696, 1523);
  g->Binary(ynn_binary_multiply, 1523, 7697, 1524);
  g->Matmul(1474, 1524, 1526, false, true);
  g->Binary(ynn_binary_divide, 1526, 7518, 1527);
  g->Unary(ynn_unary_round, 1527, 1528);
  g->Binary(ynn_binary_max, 1528, 7225, 1529);
  g->Binary(ynn_binary_min, 1529, 7340, 1530);
  g->Binary(ynn_binary_multiply, 1530, 7518, 1531);
  g->SplitDim(1531, 1532, 2, {8,256});
  g->FuseDims(1532, 1534, 1, 2);
  g->SplitDim(1534, 1533, 1, {8,1});
  g->Unary(ynn_unary_square, 1533, 1535);
  g->Reduce(ynn_reduce_sum, 1535, 6402, {3}, true);
  g->ShapeProduct(1535, 6401, {3});
  g->Binary(ynn_binary_divide, 6402, 6401, 1536);
  g->Binary(ynn_binary_add, 1536, 7373, 1539);
  g->Binary(ynn_binary_pow, 1539, 7428, 1540);
  g->Binary(ynn_binary_multiply, 1533, 1540, 1541);
  g->Convert(7695, 1542);
  g->Binary(ynn_binary_multiply, 1541, 1542, 1543);
  g->Slice(1543, 1544, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1543, 1545, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1545, 1546);
  g->Concat({1546,1544}, 1547, 3);
  g->Binary(ynn_binary_multiply, 1543, 2044, 1548);
  g->Binary(ynn_binary_multiply, 1547, 3111, 1550);
  g->Binary(ynn_binary_add, 1548, 1550, 1551);
}

// Scope: "Layer11 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(1551, 1519, 1552, false, true);
  g->Mask(1552, 7564, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 7564, 6406, {-1}, true);
  g->Binary(ynn_binary_subtract, 7564, 6406, 6403);
  g->Unary(ynn_unary_exp, 6403, 6404);
  g->Reduce(ynn_reduce_sum, 6404, 6407, {-1}, true);
  g->Binary(ynn_binary_divide, 6183, 6407, 6405);
  g->Binary(ynn_binary_multiply, 6404, 6405, 1553);
  g->Matmul(1553, 1522, 1554, false, false);
}

// Scope: "Layer11 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(1554, 1556, 1, 2);
  g->SplitDim(1556, 1555, 1, {1,8});
  g->FuseDims(1555, 1557, 2, 2);
  g->Binary(ynn_binary_divide, 1557, 7299, 1558);
  g->Unary(ynn_unary_round, 1558, 1559);
  g->Binary(ynn_binary_max, 1559, 7225, 1561);
  g->Binary(ynn_binary_min, 1561, 7340, 1562);
  g->Binary(ynn_binary_multiply, 1562, 7299, 1563);
  g->Convert(7693, 1564);
  g->Binary(ynn_binary_multiply, 1564, 7694, 1565);
  g->Matmul(1563, 1565, 1566, false, true);
  g->Binary(ynn_binary_divide, 1566, 7354, 1567);
  g->Unary(ynn_unary_round, 1567, 1568);
  g->Binary(ynn_binary_max, 1568, 7225, 1569);
  g->Binary(ynn_binary_min, 1569, 7340, 1570);
  g->Binary(ynn_binary_multiply, 1570, 7354, 1572);
}

// Scope: "Layer11 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1460, 1461);
  g->Reduce(ynn_reduce_sum, 1461, 6396, {2}, true);
  g->ShapeProduct(1461, 6395, {2});
  g->Binary(ynn_binary_divide, 6396, 6395, 1463);
  g->Binary(ynn_binary_add, 1463, 7373, 1464);
  g->Binary(ynn_binary_pow, 1464, 7428, 1465);
  g->Binary(ynn_binary_multiply, 1460, 1465, 1466);
  g->Convert(7674, 1467);
  g->Binary(ynn_binary_multiply, 1466, 1467, 1468);
  BuildLayer11AttentionKvProjection(ctx);
  BuildLayer11AttentionCacheUpdate(ctx);
  BuildLayer11AttentionQueryProjection(ctx);
  BuildLayer11AttentionSdpa(ctx);
  BuildLayer11AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1572, 1573);
  g->Reduce(ynn_reduce_sum, 1573, 6409, {2}, true);
  g->ShapeProduct(1573, 6408, {2});
  g->Binary(ynn_binary_divide, 6409, 6408, 1574);
  g->Binary(ynn_binary_add, 1574, 7373, 1575);
  g->Binary(ynn_binary_pow, 1575, 7428, 1576);
  g->Binary(ynn_binary_multiply, 1572, 1576, 1577);
  g->Convert(7686, 1578);
  g->Binary(ynn_binary_multiply, 1577, 1578, 1579);
  g->Binary(ynn_binary_add, 1460, 1579, 1580);
}

// Scope: "Layer11 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1580, 1581);
  g->Reduce(ynn_reduce_sum, 1581, 6411, {2}, true);
  g->ShapeProduct(1581, 6410, {2});
  g->Binary(ynn_binary_divide, 6411, 6410, 1583);
  g->Binary(ynn_binary_add, 1583, 7373, 1584);
  g->Binary(ynn_binary_pow, 1584, 7428, 1585);
  g->Binary(ynn_binary_multiply, 1580, 1585, 1586);
  g->Convert(7689, 1587);
  g->Binary(ynn_binary_multiply, 1586, 1587, 1588);
  g->Binary(ynn_binary_divide, 1588, 7374, 1589);
  g->Unary(ynn_unary_round, 1589, 1590);
  g->Binary(ynn_binary_max, 1590, 7225, 1591);
  g->Binary(ynn_binary_min, 1591, 7340, 1592);
  g->Binary(ynn_binary_multiply, 1592, 7374, 1594);
  g->Convert(7680, 1595);
  g->Binary(ynn_binary_multiply, 1595, 7681, 1596);
  g->Matmul(1594, 1596, 1597, false, true);
  g->Binary(ynn_binary_divide, 1597, 7494, 1598);
  g->Unary(ynn_unary_round, 1598, 1599);
  g->Binary(ynn_binary_max, 1599, 7225, 1600);
  g->Binary(ynn_binary_min, 1600, 7340, 1601);
  g->Binary(ynn_binary_multiply, 1601, 7494, 1602);
  g->Convert(7678, 1604);
  g->Binary(ynn_binary_multiply, 1604, 7679, 1605);
  g->Matmul(1594, 1605, 1606, false, true);
  g->Binary(ynn_binary_divide, 1606, 7494, 1607);
  g->Unary(ynn_unary_round, 1607, 1608);
  g->Binary(ynn_binary_max, 1608, 7225, 1609);
  g->Binary(ynn_binary_min, 1609, 7340, 1611);
  g->Binary(ynn_binary_multiply, 1611, 7494, 1612);
  g->Polynomial(1612, 6414, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6414, 6415);
  g->Binary(ynn_binary_add, 6415, 6183, 6412);
  g->Binary(ynn_binary_multiply, 1612, 6181, 6413);
  g->Binary(ynn_binary_multiply, 6413, 6412, 1613);
  g->Binary(ynn_binary_multiply, 1602, 1613, 1614);
  g->Binary(ynn_binary_divide, 1614, 7431, 1615);
  g->Unary(ynn_unary_round, 1615, 1616);
  g->Binary(ynn_binary_max, 1616, 7225, 1617);
  g->Binary(ynn_binary_min, 1617, 7340, 1618);
  g->Binary(ynn_binary_multiply, 1618, 7431, 1619);
  g->Convert(7676, 1620);
  g->Binary(ynn_binary_multiply, 1620, 7677, 1622);
  g->Matmul(1619, 1622, 1623, false, true);
  g->Binary(ynn_binary_divide, 1623, 7319, 1624);
  g->Unary(ynn_unary_round, 1624, 1625);
  g->Binary(ynn_binary_max, 1625, 7225, 1626);
  g->Binary(ynn_binary_min, 1626, 7340, 1627);
  g->Binary(ynn_binary_multiply, 1627, 7319, 1628);
  g->Unary(ynn_unary_square, 1628, 1629);
  g->Reduce(ynn_reduce_sum, 1629, 6417, {2}, true);
  g->ShapeProduct(1629, 6416, {2});
  g->Binary(ynn_binary_divide, 6417, 6416, 1630);
  g->Binary(ynn_binary_add, 1630, 7373, 1631);
  g->Binary(ynn_binary_pow, 1631, 7428, 1633);
  g->Binary(ynn_binary_multiply, 1628, 1633, 1634);
  g->Convert(7687, 1635);
  g->Binary(ynn_binary_multiply, 1634, 1635, 1636);
  g->Binary(ynn_binary_add, 1580, 1636, 1637);
}

// Scope: "Layer11 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1031, 1638, {0,0,11,0}, {-1,-1,1,-1});
  g->Reshape(1638, 1639, {1,1,256});
  g->Binary(ynn_binary_add, 1639, 8412, 1640);
  g->Binary(ynn_binary_multiply, 1640, 7155, 1641);
  g->Binary(ynn_binary_divide, 1637, 7244, 1642);
  g->Unary(ynn_unary_round, 1642, 1645);
  g->Binary(ynn_binary_max, 1645, 7225, 1646);
  g->Binary(ynn_binary_min, 1646, 7340, 1647);
  g->Binary(ynn_binary_multiply, 1647, 7244, 1648);
  g->Convert(7682, 1649);
  g->Binary(ynn_binary_multiply, 1649, 7683, 1650);
  g->Matmul(1648, 1650, 1651, false, true);
  g->Binary(ynn_binary_divide, 1651, 7490, 1652);
  g->Unary(ynn_unary_round, 1652, 1653);
  g->Binary(ynn_binary_max, 1653, 7225, 1654);
  g->Binary(ynn_binary_min, 1654, 7340, 1656);
  g->Binary(ynn_binary_multiply, 1656, 7490, 1657);
  g->Polynomial(1657, 6420, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6420, 6421);
  g->Binary(ynn_binary_add, 6421, 6183, 6418);
  g->Binary(ynn_binary_multiply, 1657, 6181, 6419);
  g->Binary(ynn_binary_multiply, 6419, 6418, 1658);
  g->Binary(ynn_binary_multiply, 1658, 1641, 1659);
  g->Binary(ynn_binary_divide, 1659, 7345, 1660);
  g->Unary(ynn_unary_round, 1660, 1661);
  g->Binary(ynn_binary_max, 1661, 7225, 1662);
  g->Binary(ynn_binary_min, 1662, 7340, 1663);
  g->Binary(ynn_binary_multiply, 1663, 7345, 1664);
  g->Convert(7684, 1665);
  g->Binary(ynn_binary_multiply, 1665, 7685, 1667);
  g->Matmul(1664, 1667, 1668, false, true);
  g->Binary(ynn_binary_divide, 1668, 7454, 1669);
  g->Unary(ynn_unary_round, 1669, 1670);
  g->Binary(ynn_binary_max, 1670, 7225, 1671);
  g->Binary(ynn_binary_min, 1671, 7340, 1672);
  g->Binary(ynn_binary_multiply, 1672, 7454, 1673);
  g->Unary(ynn_unary_square, 1673, 1674);
  g->Reduce(ynn_reduce_sum, 1674, 6425, {2}, true);
  g->ShapeProduct(1674, 6424, {2});
  g->Binary(ynn_binary_divide, 6425, 6424, 1675);
  g->Binary(ynn_binary_add, 1675, 7373, 1676);
  g->Binary(ynn_binary_pow, 1676, 7428, 1678);
  g->Binary(ynn_binary_multiply, 1673, 1678, 1679);
  g->Convert(7688, 1680);
  g->Binary(ynn_binary_multiply, 1679, 1680, 1681);
  g->Binary(ynn_binary_add, 1637, 1681, 1682);
  g->Convert(7675, 1683);
  g->Binary(ynn_binary_multiply, 1682, 1683, 1684);
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
  g->Binary(ynn_binary_divide, 1692, 7369, 1693);
  g->Unary(ynn_unary_round, 1693, 1694);
  g->Binary(ynn_binary_max, 1694, 7225, 1695);
  g->Binary(ynn_binary_min, 1695, 7340, 1696);
  g->Binary(ynn_binary_multiply, 1696, 7369, 1697);
  g->Convert(7717, 1698);
  g->Binary(ynn_binary_multiply, 1698, 7718, 1700);
  g->Matmul(1697, 1700, 1701, false, true);
  g->Binary(ynn_binary_divide, 1701, 7303, 1702);
  g->Unary(ynn_unary_round, 1702, 1703);
  g->Binary(ynn_binary_max, 1703, 7225, 1704);
  g->Binary(ynn_binary_min, 1704, 7340, 1705);
  g->Binary(ynn_binary_multiply, 1705, 7303, 1706);
  g->Reshape(1706, 1707, {1,1,1,256});
  g->Reshape(1707, 1708, {1,1,1,256});
  g->Unary(ynn_unary_square, 1708, 1709);
  g->Reduce(ynn_reduce_sum, 1709, 6429, {3}, true);
  g->ShapeProduct(1709, 6428, {3});
  g->Binary(ynn_binary_divide, 6429, 6428, 1711);
  g->Binary(ynn_binary_add, 1711, 7373, 1712);
  g->Binary(ynn_binary_pow, 1712, 7428, 1713);
  g->Binary(ynn_binary_multiply, 1708, 1713, 1714);
  g->Convert(7716, 1715);
  g->Binary(ynn_binary_multiply, 1714, 1715, 1716);
  g->Slice(1716, 1717, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1716, 1718, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1718, 1719);
  g->Concat({1719,1717}, 1720, 3);
  g->Binary(ynn_binary_multiply, 1716, 2044, 1722);
  g->Binary(ynn_binary_multiply, 1720, 3111, 1723);
  g->Binary(ynn_binary_add, 1722, 1723, 1724);
  g->Convert(7724, 1725);
  g->Binary(ynn_binary_multiply, 1725, 7725, 1726);
  g->Matmul(1697, 1726, 1728, false, true);
  g->Binary(ynn_binary_divide, 1728, 7303, 1729);
  g->Unary(ynn_unary_round, 1729, 1730);
  g->Binary(ynn_binary_max, 1730, 7225, 1731);
  g->Binary(ynn_binary_min, 1731, 7340, 1732);
  g->Binary(ynn_binary_multiply, 1732, 7303, 1733);
  g->Reshape(1733, 1734, {1,1,1,256});
  g->Reshape(1734, 1735, {1,1,1,256});
  g->Unary(ynn_unary_square, 1735, 1736);
  g->Reduce(ynn_reduce_sum, 1736, 6431, {3}, true);
  g->ShapeProduct(1736, 6430, {3});
  g->Binary(ynn_binary_divide, 6431, 6430, 1737);
  g->Binary(ynn_binary_add, 1737, 7373, 1739);
  g->Binary(ynn_binary_pow, 1739, 7428, 1740);
  g->Binary(ynn_binary_multiply, 1735, 1740, 1741);
}

// Scope: "Layer12 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(1724, 1742, 0.005788442213088274, 0);
  g->Append(7119, 1742, 8449, 2, s2, slinky::expr(int64_t{1}));
  g->View(8449, 8479, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(8479, 1743, 0.005788442213088274, 0);
  g->Quantize(1741, 1744, 0.047244105488061905, 0);
  g->Append(7134, 1744, 8464, 2, s2, slinky::expr(int64_t{1}));
  g->View(8464, 8494, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(8494, 1747, 0.047244105488061905, 0);
}

// Scope: "Layer12 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Convert(7722, 1748);
  g->Binary(ynn_binary_multiply, 1748, 7723, 1749);
  g->Matmul(1697, 1749, 1750, false, true);
  g->Binary(ynn_binary_divide, 1750, 7270, 1751);
  g->Unary(ynn_unary_round, 1751, 1753);
  g->Binary(ynn_binary_max, 1753, 7225, 1754);
  g->Binary(ynn_binary_min, 1754, 7340, 1755);
  g->Binary(ynn_binary_multiply, 1755, 7270, 1756);
  g->SplitDim(1756, 1757, 2, {8,256});
  g->FuseDims(1757, 1759, 1, 2);
  g->SplitDim(1759, 1758, 1, {8,1});
  g->Unary(ynn_unary_square, 1758, 1760);
  g->Reduce(ynn_reduce_sum, 1760, 6433, {3}, true);
  g->ShapeProduct(1760, 6432, {3});
  g->Binary(ynn_binary_divide, 6433, 6432, 1761);
  g->Binary(ynn_binary_add, 1761, 7373, 1762);
  g->Binary(ynn_binary_pow, 1762, 7428, 1763);
  g->Binary(ynn_binary_multiply, 1758, 1763, 1765);
  g->Convert(7721, 1766);
  g->Binary(ynn_binary_multiply, 1765, 1766, 1767);
  g->Slice(1767, 1768, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1767, 1769, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1769, 1770);
  g->Concat({1770,1768}, 1771, 3);
  g->Binary(ynn_binary_multiply, 1767, 2044, 1772);
  g->Binary(ynn_binary_multiply, 1771, 3111, 1773);
  g->Binary(ynn_binary_add, 1772, 1773, 1774);
}

// Scope: "Layer12 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(1774, 1743, 1776, false, true);
  g->Mask(1776, 7565, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 7565, 6437, {-1}, true);
  g->Binary(ynn_binary_subtract, 7565, 6437, 6434);
  g->Unary(ynn_unary_exp, 6434, 6435);
  g->Reduce(ynn_reduce_sum, 6435, 6438, {-1}, true);
  g->Binary(ynn_binary_divide, 6183, 6438, 6436);
  g->Binary(ynn_binary_multiply, 6435, 6436, 1777);
  g->Matmul(1777, 1747, 1778, false, false);
}

// Scope: "Layer12 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(1778, 1780, 1, 2);
  g->SplitDim(1780, 1779, 1, {1,8});
  g->FuseDims(1779, 1781, 2, 2);
  g->Binary(ynn_binary_divide, 1781, 7367, 1782);
  g->Unary(ynn_unary_round, 1782, 1783);
  g->Binary(ynn_binary_max, 1783, 7225, 1784);
  g->Binary(ynn_binary_min, 1784, 7340, 1785);
  g->Binary(ynn_binary_multiply, 1785, 7367, 1787);
  g->Convert(7719, 1788);
  g->Binary(ynn_binary_multiply, 1788, 7720, 1789);
  g->Matmul(1787, 1789, 1790, false, true);
  g->Binary(ynn_binary_divide, 1790, 7479, 1791);
  g->Unary(ynn_unary_round, 1791, 1792);
  g->Binary(ynn_binary_max, 1792, 7225, 1793);
  g->Binary(ynn_binary_min, 1793, 7340, 1794);
  g->Binary(ynn_binary_multiply, 1794, 7479, 1795);
}

// Scope: "Layer12 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1684, 1685);
  g->Reduce(ynn_reduce_sum, 1685, 6427, {2}, true);
  g->ShapeProduct(1685, 6426, {2});
  g->Binary(ynn_binary_divide, 6427, 6426, 1686);
  g->Binary(ynn_binary_add, 1686, 7373, 1687);
  g->Binary(ynn_binary_pow, 1687, 7428, 1689);
  g->Binary(ynn_binary_multiply, 1684, 1689, 1690);
  g->Convert(7700, 1691);
  g->Binary(ynn_binary_multiply, 1690, 1691, 1692);
  BuildLayer12AttentionKvProjection(ctx);
  BuildLayer12AttentionCacheUpdate(ctx);
  BuildLayer12AttentionQueryProjection(ctx);
  BuildLayer12AttentionSdpa(ctx);
  BuildLayer12AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1795, 1796);
  g->Reduce(ynn_reduce_sum, 1796, 6440, {2}, true);
  g->ShapeProduct(1796, 6439, {2});
  g->Binary(ynn_binary_divide, 6440, 6439, 1797);
  g->Binary(ynn_binary_add, 1797, 7373, 1798);
  g->Binary(ynn_binary_pow, 1798, 7428, 1799);
  g->Binary(ynn_binary_multiply, 1795, 1799, 1800);
  g->Convert(7712, 1801);
  g->Binary(ynn_binary_multiply, 1800, 1801, 1802);
  g->Binary(ynn_binary_add, 1684, 1802, 1803);
}

// Scope: "Layer12 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1803, 1804);
  g->Reduce(ynn_reduce_sum, 1804, 6442, {2}, true);
  g->ShapeProduct(1804, 6441, {2});
  g->Binary(ynn_binary_divide, 6442, 6441, 1805);
  g->Binary(ynn_binary_add, 1805, 7373, 1806);
  g->Binary(ynn_binary_pow, 1806, 7428, 1807);
  g->Binary(ynn_binary_multiply, 1803, 1807, 1808);
  g->Convert(7715, 1809);
  g->Binary(ynn_binary_multiply, 1808, 1809, 1810);
  g->Binary(ynn_binary_divide, 1810, 7528, 1811);
  g->Unary(ynn_unary_round, 1811, 1812);
  g->Binary(ynn_binary_max, 1812, 7225, 1813);
  g->Binary(ynn_binary_min, 1813, 7340, 1814);
  g->Binary(ynn_binary_multiply, 1814, 7528, 1815);
  g->Convert(7706, 1816);
  g->Binary(ynn_binary_multiply, 1816, 7707, 1817);
  g->Matmul(1815, 1817, 1818, false, true);
  g->Binary(ynn_binary_divide, 1818, 7556, 1819);
  g->Unary(ynn_unary_round, 1819, 1820);
  g->Binary(ynn_binary_max, 1820, 7225, 1821);
  g->Binary(ynn_binary_min, 1821, 7340, 1822);
  g->Binary(ynn_binary_multiply, 1822, 7556, 1823);
  g->Convert(7704, 1824);
  g->Binary(ynn_binary_multiply, 1824, 7705, 1825);
  g->Matmul(1815, 1825, 1826, false, true);
  g->Binary(ynn_binary_divide, 1826, 7556, 1827);
  g->Unary(ynn_unary_round, 1827, 1828);
  g->Binary(ynn_binary_max, 1828, 7225, 1829);
  g->Binary(ynn_binary_min, 1829, 7340, 1830);
  g->Binary(ynn_binary_multiply, 1830, 7556, 1831);
  g->Polynomial(1831, 6445, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6445, 6446);
  g->Binary(ynn_binary_add, 6446, 6183, 6443);
  g->Binary(ynn_binary_multiply, 1831, 6181, 6444);
  g->Binary(ynn_binary_multiply, 6444, 6443, 1832);
  g->Binary(ynn_binary_multiply, 1823, 1832, 1833);
  g->Binary(ynn_binary_divide, 1833, 7543, 1834);
  g->Unary(ynn_unary_round, 1834, 1835);
  g->Binary(ynn_binary_max, 1835, 7225, 1836);
  g->Binary(ynn_binary_min, 1836, 7340, 1837);
  g->Binary(ynn_binary_multiply, 1837, 7543, 1838);
  g->Convert(7702, 1839);
  g->Binary(ynn_binary_multiply, 1839, 7703, 1840);
  g->Matmul(1838, 1840, 1841, false, true);
  g->Binary(ynn_binary_divide, 1841, 7424, 1844);
  g->Unary(ynn_unary_round, 1844, 1845);
  g->Binary(ynn_binary_max, 1845, 7225, 1846);
  g->Binary(ynn_binary_min, 1846, 7340, 1847);
  g->Binary(ynn_binary_multiply, 1847, 7424, 1848);
  g->Unary(ynn_unary_square, 1848, 1849);
  g->Reduce(ynn_reduce_sum, 1849, 6448, {2}, true);
  g->ShapeProduct(1849, 6447, {2});
  g->Binary(ynn_binary_divide, 6448, 6447, 1850);
  g->Binary(ynn_binary_add, 1850, 7373, 1851);
  g->Binary(ynn_binary_pow, 1851, 7428, 1852);
  g->Binary(ynn_binary_multiply, 1848, 1852, 1853);
  g->Convert(7713, 1855);
  g->Binary(ynn_binary_multiply, 1853, 1855, 1856);
  g->Binary(ynn_binary_add, 1803, 1856, 1857);
}

// Scope: "Layer12 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1031, 1858, {0,0,12,0}, {-1,-1,1,-1});
  g->Reshape(1858, 1859, {1,1,256});
  g->Binary(ynn_binary_add, 1859, 8413, 1860);
  g->Binary(ynn_binary_multiply, 1860, 7155, 1861);
  g->Binary(ynn_binary_divide, 1857, 7554, 1862);
  g->Unary(ynn_unary_round, 1862, 1863);
  g->Binary(ynn_binary_max, 1863, 7225, 1864);
  g->Binary(ynn_binary_min, 1864, 7340, 1866);
  g->Binary(ynn_binary_multiply, 1866, 7554, 1867);
  g->Convert(7708, 1868);
  g->Binary(ynn_binary_multiply, 1868, 7709, 1869);
  g->Matmul(1867, 1869, 1870, false, true);
  g->Binary(ynn_binary_divide, 1870, 7490, 1871);
  g->Unary(ynn_unary_round, 1871, 1872);
  g->Binary(ynn_binary_max, 1872, 7225, 1873);
  g->Binary(ynn_binary_min, 1873, 7340, 1874);
  g->Binary(ynn_binary_multiply, 1874, 7490, 1875);
  g->Polynomial(1875, 6451, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6451, 6452);
  g->Binary(ynn_binary_add, 6452, 6183, 6449);
  g->Binary(ynn_binary_multiply, 1875, 6181, 6450);
  g->Binary(ynn_binary_multiply, 6450, 6449, 1877);
  g->Binary(ynn_binary_multiply, 1877, 1861, 1878);
  g->Binary(ynn_binary_divide, 1878, 7475, 1879);
  g->Unary(ynn_unary_round, 1879, 1880);
  g->Binary(ynn_binary_max, 1880, 7225, 1881);
  g->Binary(ynn_binary_min, 1881, 7340, 1882);
  g->Binary(ynn_binary_multiply, 1882, 7475, 1883);
  g->Convert(7710, 1884);
  g->Binary(ynn_binary_multiply, 1884, 7711, 1885);
  g->Matmul(1883, 1885, 1886, false, true);
  g->Binary(ynn_binary_divide, 1886, 7546, 1888);
  g->Unary(ynn_unary_round, 1888, 1889);
  g->Binary(ynn_binary_max, 1889, 7225, 1890);
  g->Binary(ynn_binary_min, 1890, 7340, 1891);
  g->Binary(ynn_binary_multiply, 1891, 7546, 1892);
  g->Unary(ynn_unary_square, 1892, 1893);
  g->Reduce(ynn_reduce_sum, 1893, 6454, {2}, true);
  g->ShapeProduct(1893, 6453, {2});
  g->Binary(ynn_binary_divide, 6454, 6453, 1894);
  g->Binary(ynn_binary_add, 1894, 7373, 1895);
  g->Binary(ynn_binary_pow, 1895, 7428, 1896);
  g->Binary(ynn_binary_multiply, 1892, 1896, 1897);
  g->Convert(7714, 1899);
  g->Binary(ynn_binary_multiply, 1897, 1899, 1900);
  g->Binary(ynn_binary_add, 1857, 1900, 1901);
  g->Convert(7701, 1902);
  g->Binary(ynn_binary_multiply, 1901, 1902, 1903);
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
  g->Binary(ynn_binary_divide, 1911, 7249, 1912);
  g->Unary(ynn_unary_round, 1912, 1913);
  g->Binary(ynn_binary_max, 1913, 7225, 1914);
  g->Binary(ynn_binary_min, 1914, 7340, 1915);
  g->Binary(ynn_binary_multiply, 1915, 7249, 1916);
  g->Convert(7743, 1917);
  g->Binary(ynn_binary_multiply, 1917, 7744, 1918);
  g->Matmul(1916, 1918, 1919, false, true);
  g->Binary(ynn_binary_divide, 1919, 7351, 1921);
  g->Unary(ynn_unary_round, 1921, 1922);
  g->Binary(ynn_binary_max, 1922, 7225, 1923);
  g->Binary(ynn_binary_min, 1923, 7340, 1924);
  g->Binary(ynn_binary_multiply, 1924, 7351, 1925);
  g->Reshape(1925, 1926, {1,1,1,256});
  g->Reshape(1926, 1927, {1,1,1,256});
  g->Unary(ynn_unary_square, 1927, 1928);
  g->Reduce(ynn_reduce_sum, 1928, 6458, {3}, true);
  g->ShapeProduct(1928, 6457, {3});
  g->Binary(ynn_binary_divide, 6458, 6457, 1929);
  g->Binary(ynn_binary_add, 1929, 7373, 1930);
  g->Binary(ynn_binary_pow, 1930, 7428, 1932);
  g->Binary(ynn_binary_multiply, 1927, 1932, 1933);
  g->Convert(7742, 1934);
  g->Binary(ynn_binary_multiply, 1933, 1934, 1935);
  g->Slice(1935, 1936, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1935, 1937, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1937, 1938);
  g->Concat({1938,1936}, 1939, 3);
  g->Binary(ynn_binary_multiply, 1935, 2044, 1940);
  g->Binary(ynn_binary_multiply, 1939, 3111, 1941);
  g->Binary(ynn_binary_add, 1940, 1941, 1943);
  g->Convert(7750, 1944);
  g->Binary(ynn_binary_multiply, 1944, 7751, 1945);
  g->Matmul(1916, 1945, 1946, false, true);
  g->Binary(ynn_binary_divide, 1946, 7351, 1947);
  g->Unary(ynn_unary_round, 1947, 1950);
  g->Binary(ynn_binary_max, 1950, 7225, 1951);
  g->Binary(ynn_binary_min, 1951, 7340, 1952);
  g->Binary(ynn_binary_multiply, 1952, 7351, 1953);
  g->Reshape(1953, 1954, {1,1,1,256});
  g->Reshape(1954, 1955, {1,1,1,256});
  g->Unary(ynn_unary_square, 1955, 1956);
  g->Reduce(ynn_reduce_sum, 1956, 6460, {3}, true);
  g->ShapeProduct(1956, 6459, {3});
  g->Binary(ynn_binary_divide, 6460, 6459, 1957);
  g->Binary(ynn_binary_add, 1957, 7373, 1958);
  g->Binary(ynn_binary_pow, 1958, 7428, 1959);
  g->Binary(ynn_binary_multiply, 1955, 1959, 1961);
}

// Scope: "Layer13 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(1943, 1962, 0.0059552486054599285, 0);
  g->Append(7120, 1962, 8450, 2, s2, slinky::expr(int64_t{1}));
  g->View(8450, 8480, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(8480, 1963, 0.0059552486054599285, 0);
  g->Quantize(1961, 1964, 0.047244105488061905, 0);
  g->Append(7135, 1964, 8465, 2, s2, slinky::expr(int64_t{1}));
  g->View(8465, 8495, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(8495, 1965, 0.047244105488061905, 0);
}

// Scope: "Layer13 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Convert(7748, 1967);
  g->Binary(ynn_binary_multiply, 1967, 7749, 1968);
  g->Matmul(1916, 1968, 1969, false, true);
  g->Binary(ynn_binary_divide, 1969, 7318, 1970);
  g->Unary(ynn_unary_round, 1970, 1971);
  g->Binary(ynn_binary_max, 1971, 7225, 1972);
  g->Binary(ynn_binary_min, 1972, 7340, 1974);
  g->Binary(ynn_binary_multiply, 1974, 7318, 1975);
  g->SplitDim(1975, 1976, 2, {8,256});
  g->FuseDims(1976, 1978, 1, 2);
  g->SplitDim(1978, 1977, 1, {8,1});
  g->Unary(ynn_unary_square, 1977, 1979);
  g->Reduce(ynn_reduce_sum, 1979, 6464, {3}, true);
  g->ShapeProduct(1979, 6463, {3});
  g->Binary(ynn_binary_divide, 6464, 6463, 1980);
  g->Binary(ynn_binary_add, 1980, 7373, 1981);
  g->Binary(ynn_binary_pow, 1981, 7428, 1982);
  g->Binary(ynn_binary_multiply, 1977, 1982, 1983);
  g->Convert(7747, 1984);
  g->Binary(ynn_binary_multiply, 1983, 1984, 1986);
  g->Slice(1986, 1987, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1986, 1988, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1988, 1989);
  g->Concat({1989,1987}, 1990, 3);
  g->Binary(ynn_binary_multiply, 1986, 2044, 1991);
  g->Binary(ynn_binary_multiply, 1990, 3111, 1992);
  g->Binary(ynn_binary_add, 1991, 1992, 1993);
}

// Scope: "Layer13 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(1993, 1963, 1994, false, true);
  g->Mask(1994, 7566, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 7566, 6468, {-1}, true);
  g->Binary(ynn_binary_subtract, 7566, 6468, 6465);
  g->Unary(ynn_unary_exp, 6465, 6466);
  g->Reduce(ynn_reduce_sum, 6466, 6469, {-1}, true);
  g->Binary(ynn_binary_divide, 6183, 6469, 6467);
  g->Binary(ynn_binary_multiply, 6466, 6467, 1996);
  g->Matmul(1996, 1965, 1997, false, false);
}

// Scope: "Layer13 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(1997, 1999, 1, 2);
  g->SplitDim(1999, 1998, 1, {1,8});
  g->FuseDims(1998, 2000, 2, 2);
  g->Binary(ynn_binary_divide, 2000, 7245, 2001);
  g->Unary(ynn_unary_round, 2001, 2002);
  g->Binary(ynn_binary_max, 2002, 7225, 2003);
  g->Binary(ynn_binary_min, 2003, 7340, 2004);
  g->Binary(ynn_binary_multiply, 2004, 7245, 2005);
  g->Convert(7745, 2006);
  g->Binary(ynn_binary_multiply, 2006, 7746, 2007);
  g->Matmul(2005, 2007, 2008, false, true);
  g->Binary(ynn_binary_divide, 2008, 7156, 2009);
  g->Unary(ynn_unary_round, 2009, 2010);
  g->Binary(ynn_binary_max, 2010, 7225, 2011);
  g->Binary(ynn_binary_min, 2011, 7340, 2012);
  g->Binary(ynn_binary_multiply, 2012, 7156, 2013);
}

// Scope: "Layer13 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1903, 1904);
  g->Reduce(ynn_reduce_sum, 1904, 6456, {2}, true);
  g->ShapeProduct(1904, 6455, {2});
  g->Binary(ynn_binary_divide, 6456, 6455, 1905);
  g->Binary(ynn_binary_add, 1905, 7373, 1906);
  g->Binary(ynn_binary_pow, 1906, 7428, 1907);
  g->Binary(ynn_binary_multiply, 1903, 1907, 1908);
  g->Convert(7726, 1910);
  g->Binary(ynn_binary_multiply, 1908, 1910, 1911);
  BuildLayer13AttentionKvProjection(ctx);
  BuildLayer13AttentionCacheUpdate(ctx);
  BuildLayer13AttentionQueryProjection(ctx);
  BuildLayer13AttentionSdpa(ctx);
  BuildLayer13AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2013, 2014);
  g->Reduce(ynn_reduce_sum, 2014, 6471, {2}, true);
  g->ShapeProduct(2014, 6470, {2});
  g->Binary(ynn_binary_divide, 6471, 6470, 2015);
  g->Binary(ynn_binary_add, 2015, 7373, 2016);
  g->Binary(ynn_binary_pow, 2016, 7428, 2017);
  g->Binary(ynn_binary_multiply, 2013, 2017, 2018);
  g->Convert(7738, 2019);
  g->Binary(ynn_binary_multiply, 2018, 2019, 2020);
  g->Binary(ynn_binary_add, 1903, 2020, 2021);
}

// Scope: "Layer13 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2021, 2022);
  g->Reduce(ynn_reduce_sum, 2022, 6473, {2}, true);
  g->ShapeProduct(2022, 6472, {2});
  g->Binary(ynn_binary_divide, 6473, 6472, 2023);
  g->Binary(ynn_binary_add, 2023, 7373, 2024);
  g->Binary(ynn_binary_pow, 2024, 7428, 2025);
  g->Binary(ynn_binary_multiply, 2021, 2025, 2026);
  g->Convert(7741, 2028);
  g->Binary(ynn_binary_multiply, 2026, 2028, 2029);
  g->Binary(ynn_binary_divide, 2029, 7358, 2030);
  g->Unary(ynn_unary_round, 2030, 2031);
  g->Binary(ynn_binary_max, 2031, 7225, 2032);
  g->Binary(ynn_binary_min, 2032, 7340, 2033);
  g->Binary(ynn_binary_multiply, 2033, 7358, 2034);
  g->Convert(7732, 2035);
  g->Binary(ynn_binary_multiply, 2035, 7733, 2036);
  g->Matmul(2034, 2036, 2037, false, true);
  g->Binary(ynn_binary_divide, 2037, 7409, 2039);
  g->Unary(ynn_unary_round, 2039, 2040);
  g->Binary(ynn_binary_max, 2040, 7225, 2041);
  g->Binary(ynn_binary_min, 2041, 7340, 2042);
  g->Binary(ynn_binary_multiply, 2042, 7409, 2043);
  g->Convert(7730, 2046);
  g->Binary(ynn_binary_multiply, 2046, 7731, 2047);
  g->Matmul(2034, 2047, 2048, false, true);
  g->Binary(ynn_binary_divide, 2048, 7409, 2049);
  g->Unary(ynn_unary_round, 2049, 2050);
  g->Binary(ynn_binary_max, 2050, 7225, 2051);
  g->Binary(ynn_binary_min, 2051, 7340, 2052);
  g->Binary(ynn_binary_multiply, 2052, 7409, 2053);
  g->Polynomial(2053, 6476, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6476, 6477);
  g->Binary(ynn_binary_add, 6477, 6183, 6474);
  g->Binary(ynn_binary_multiply, 2053, 6181, 6475);
  g->Binary(ynn_binary_multiply, 6475, 6474, 2054);
  g->Binary(ynn_binary_multiply, 2043, 2054, 2055);
  g->Binary(ynn_binary_divide, 2055, 7266, 2056);
  g->Unary(ynn_unary_round, 2056, 2057);
  g->Binary(ynn_binary_max, 2057, 7225, 2058);
  g->Binary(ynn_binary_min, 2058, 7340, 2059);
  g->Binary(ynn_binary_multiply, 2059, 7266, 2060);
  g->Convert(7728, 2061);
  g->Binary(ynn_binary_multiply, 2061, 7729, 2062);
  g->Matmul(2060, 2062, 2063, false, true);
  g->Binary(ynn_binary_divide, 2063, 7526, 2064);
  g->Unary(ynn_unary_round, 2064, 2065);
  g->Binary(ynn_binary_max, 2065, 7225, 2067);
  g->Binary(ynn_binary_min, 2067, 7340, 2068);
  g->Binary(ynn_binary_multiply, 2068, 7526, 2069);
  g->Unary(ynn_unary_square, 2069, 2070);
  g->Reduce(ynn_reduce_sum, 2070, 6479, {2}, true);
  g->ShapeProduct(2070, 6478, {2});
  g->Binary(ynn_binary_divide, 6479, 6478, 2071);
  g->Binary(ynn_binary_add, 2071, 7373, 2072);
  g->Binary(ynn_binary_pow, 2072, 7428, 2073);
  g->Binary(ynn_binary_multiply, 2069, 2073, 2074);
  g->Convert(7739, 2075);
  g->Binary(ynn_binary_multiply, 2074, 2075, 2076);
  g->Binary(ynn_binary_add, 2021, 2076, 2077);
}

// Scope: "Layer13 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1031, 2078, {0,0,13,0}, {-1,-1,1,-1});
  g->Reshape(2078, 2079, {1,1,256});
  g->Binary(ynn_binary_add, 2079, 8414, 2080);
  g->Binary(ynn_binary_multiply, 2080, 7155, 2081);
  g->Binary(ynn_binary_divide, 2077, 7278, 2082);
  g->Unary(ynn_unary_round, 2082, 2083);
  g->Binary(ynn_binary_max, 2083, 7225, 2084);
  g->Binary(ynn_binary_min, 2084, 7340, 2085);
  g->Binary(ynn_binary_multiply, 2085, 7278, 2086);
  g->Convert(7734, 2087);
  g->Binary(ynn_binary_multiply, 2087, 7735, 2088);
  g->Matmul(2086, 2088, 2089, false, true);
  g->Binary(ynn_binary_divide, 2089, 7460, 2090);
  g->Unary(ynn_unary_round, 2090, 2091);
  g->Binary(ynn_binary_max, 2091, 7225, 2092);
  g->Binary(ynn_binary_min, 2092, 7340, 2093);
  g->Binary(ynn_binary_multiply, 2093, 7460, 2094);
  g->Polynomial(2094, 6482, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6482, 6483);
  g->Binary(ynn_binary_add, 6483, 6183, 6480);
  g->Binary(ynn_binary_multiply, 2094, 6181, 6481);
  g->Binary(ynn_binary_multiply, 6481, 6480, 2095);
  g->Binary(ynn_binary_multiply, 2095, 2081, 2096);
  g->Binary(ynn_binary_divide, 2096, 7191, 2097);
  g->Unary(ynn_unary_round, 2097, 2098);
  g->Binary(ynn_binary_max, 2098, 7225, 2099);
  g->Binary(ynn_binary_min, 2099, 7340, 2100);
  g->Binary(ynn_binary_multiply, 2100, 7191, 2101);
  g->Convert(7736, 2102);
  g->Binary(ynn_binary_multiply, 2102, 7737, 2103);
  g->Matmul(2101, 2103, 2104, false, true);
  g->Binary(ynn_binary_divide, 2104, 7410, 2105);
  g->Unary(ynn_unary_round, 2105, 2106);
  g->Binary(ynn_binary_max, 2106, 7225, 2107);
  g->Binary(ynn_binary_min, 2107, 7340, 2108);
  g->Binary(ynn_binary_multiply, 2108, 7410, 2109);
  g->Unary(ynn_unary_square, 2109, 2110);
  g->Reduce(ynn_reduce_sum, 2110, 6485, {2}, true);
  g->ShapeProduct(2110, 6484, {2});
  g->Binary(ynn_binary_divide, 6485, 6484, 2111);
  g->Binary(ynn_binary_add, 2111, 7373, 2112);
  g->Binary(ynn_binary_pow, 2112, 7428, 2113);
  g->Binary(ynn_binary_multiply, 2109, 2113, 2114);
  g->Convert(7740, 2115);
  g->Binary(ynn_binary_multiply, 2114, 2115, 2116);
  g->Binary(ynn_binary_add, 2077, 2116, 2117);
  g->Convert(7727, 2118);
  g->Binary(ynn_binary_multiply, 2117, 2118, 2119);
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
  g->Binary(ynn_binary_divide, 2126, 7176, 2128);
  g->Unary(ynn_unary_round, 2128, 2129);
  g->Binary(ynn_binary_max, 2129, 7225, 2130);
  g->Binary(ynn_binary_min, 2130, 7340, 2131);
  g->Binary(ynn_binary_multiply, 2131, 7176, 2132);
  g->Convert(7769, 2133);
  g->Binary(ynn_binary_multiply, 2133, 7770, 2134);
  g->Matmul(2132, 2134, 2135, false, true);
  g->Binary(ynn_binary_divide, 2135, 7472, 2136);
  g->Unary(ynn_unary_round, 2136, 2137);
  g->Binary(ynn_binary_max, 2137, 7225, 2139);
  g->Binary(ynn_binary_min, 2139, 7340, 2140);
  g->Binary(ynn_binary_multiply, 2140, 7472, 2141);
  g->Reshape(2141, 2142, {1,1,1,512});
  g->Reshape(2142, 2143, {1,1,1,512});
  g->Unary(ynn_unary_square, 2143, 2144);
  g->Reduce(ynn_reduce_sum, 2144, 6489, {3}, true);
  g->ShapeProduct(2144, 6488, {3});
  g->Binary(ynn_binary_divide, 6489, 6488, 2145);
  g->Binary(ynn_binary_add, 2145, 7373, 2146);
  g->Binary(ynn_binary_pow, 2146, 7428, 2147);
  g->Binary(ynn_binary_multiply, 2143, 2147, 2148);
  g->Convert(7768, 2151);
  g->Binary(ynn_binary_multiply, 2148, 2151, 2152);
  g->Slice(2152, 2153, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(2152, 2154, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 2154, 2155);
  g->Concat({2155,2153}, 2156, 3);
  g->Binary(ynn_binary_multiply, 2152, 5976, 2157);
  g->Binary(ynn_binary_multiply, 2156, 6075, 2158);
  g->Binary(ynn_binary_add, 2157, 2158, 2159);
  g->Convert(7776, 2161);
  g->Binary(ynn_binary_multiply, 2161, 7777, 2162);
  g->Matmul(2132, 2162, 2163, false, true);
  g->Binary(ynn_binary_divide, 2163, 7472, 2164);
  g->Unary(ynn_unary_round, 2164, 2165);
  g->Binary(ynn_binary_max, 2165, 7225, 2166);
  g->Binary(ynn_binary_min, 2166, 7340, 2168);
  g->Binary(ynn_binary_multiply, 2168, 7472, 2169);
  g->Reshape(2169, 2170, {1,1,1,512});
  g->Reshape(2170, 2171, {1,1,1,512});
  g->Unary(ynn_unary_square, 2171, 2172);
  g->Reduce(ynn_reduce_sum, 2172, 6491, {3}, true);
  g->ShapeProduct(2172, 6490, {3});
  g->Binary(ynn_binary_divide, 6491, 6490, 2173);
  g->Binary(ynn_binary_add, 2173, 7373, 2174);
  g->Binary(ynn_binary_pow, 2174, 7428, 2175);
  g->Binary(ynn_binary_multiply, 2171, 2175, 2176);
}

// Scope: "Layer14 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(2159, 2177, 0.001091228099539876, 0);
  g->Append(7121, 2177, 8451, 2, s2, slinky::expr(int64_t{1}));
  g->View(8451, 8481, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(8481, 2179, 0.001091228099539876, 0);
  g->Quantize(2176, 2180, 0.01785714365541935, 0);
  g->Append(7136, 2180, 8466, 2, s2, slinky::expr(int64_t{1}));
  g->View(8466, 8496, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(8496, 2181, 0.01785714365541935, 0);
}

// Scope: "Layer14 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Convert(7774, 2183);
  g->Binary(ynn_binary_multiply, 2183, 7775, 2184);
  g->Matmul(2132, 2184, 2185, false, true);
  g->Binary(ynn_binary_divide, 2185, 7361, 2186);
  g->Unary(ynn_unary_round, 2186, 2187);
  g->Binary(ynn_binary_max, 2187, 7225, 2188);
  g->Binary(ynn_binary_min, 2188, 7340, 2189);
  g->Binary(ynn_binary_multiply, 2189, 7361, 2190);
  g->SplitDim(2190, 2192, 2, {8,512});
  g->FuseDims(2192, 2194, 1, 2);
  g->SplitDim(2194, 2193, 1, {8,1});
  g->Unary(ynn_unary_square, 2193, 2195);
  g->Reduce(ynn_reduce_sum, 2195, 6493, {3}, true);
  g->ShapeProduct(2195, 6492, {3});
  g->Binary(ynn_binary_divide, 6493, 6492, 2196);
  g->Binary(ynn_binary_add, 2196, 7373, 2197);
  g->Binary(ynn_binary_pow, 2197, 7428, 2198);
  g->Binary(ynn_binary_multiply, 2193, 2198, 2199);
  g->Convert(7773, 2200);
  g->Binary(ynn_binary_multiply, 2199, 2200, 2201);
  g->Slice(2201, 2202, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(2201, 2204, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 2204, 2205);
  g->Concat({2205,2202}, 2206, 3);
  g->Binary(ynn_binary_multiply, 2201, 5976, 2207);
  g->Binary(ynn_binary_multiply, 2206, 6075, 2208);
  g->Binary(ynn_binary_add, 2207, 2208, 2209);
}

// Scope: "Layer14 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(2209, 2179, 2210, false, true);
  g->Mask(2210, 7567, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 7567, 6497, {-1}, true);
  g->Binary(ynn_binary_subtract, 7567, 6497, 6494);
  g->Unary(ynn_unary_exp, 6494, 6495);
  g->Reduce(ynn_reduce_sum, 6495, 6498, {-1}, true);
  g->Binary(ynn_binary_divide, 6183, 6498, 6496);
  g->Binary(ynn_binary_multiply, 6495, 6496, 2211);
  g->Matmul(2211, 2181, 2212, false, false);
}

// Scope: "Layer14 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(2212, 2216, 1, 2);
  g->SplitDim(2216, 2215, 1, {1,8});
  g->FuseDims(2215, 2217, 2, 2);
  g->Binary(ynn_binary_divide, 2217, 7315, 2218);
  g->Unary(ynn_unary_round, 2218, 2219);
  g->Binary(ynn_binary_max, 2219, 7225, 2220);
  g->Binary(ynn_binary_min, 2220, 7340, 2221);
  g->Binary(ynn_binary_multiply, 2221, 7315, 2222);
  g->Convert(7771, 2223);
  g->Binary(ynn_binary_multiply, 2223, 7772, 2224);
  g->Matmul(2222, 2224, 2225, false, true);
  g->Binary(ynn_binary_divide, 2225, 7483, 2227);
  g->Unary(ynn_unary_round, 2227, 2228);
  g->Binary(ynn_binary_max, 2228, 7225, 2229);
  g->Binary(ynn_binary_min, 2229, 7340, 2230);
  g->Binary(ynn_binary_multiply, 2230, 7483, 2231);
}

// Scope: "Layer14 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2119, 2120);
  g->Reduce(ynn_reduce_sum, 2120, 6487, {2}, true);
  g->ShapeProduct(2120, 6486, {2});
  g->Binary(ynn_binary_divide, 6487, 6486, 2121);
  g->Binary(ynn_binary_add, 2121, 7373, 2122);
  g->Binary(ynn_binary_pow, 2122, 7428, 2123);
  g->Binary(ynn_binary_multiply, 2119, 2123, 2124);
  g->Convert(7752, 2125);
  g->Binary(ynn_binary_multiply, 2124, 2125, 2126);
  BuildLayer14AttentionKvProjection(ctx);
  BuildLayer14AttentionCacheUpdate(ctx);
  BuildLayer14AttentionQueryProjection(ctx);
  BuildLayer14AttentionSdpa(ctx);
  BuildLayer14AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2231, 2232);
  g->Reduce(ynn_reduce_sum, 2232, 6500, {2}, true);
  g->ShapeProduct(2232, 6499, {2});
  g->Binary(ynn_binary_divide, 6500, 6499, 2233);
  g->Binary(ynn_binary_add, 2233, 7373, 2234);
  g->Binary(ynn_binary_pow, 2234, 7428, 2235);
  g->Binary(ynn_binary_multiply, 2231, 2235, 2236);
  g->Convert(7764, 2238);
  g->Binary(ynn_binary_multiply, 2236, 2238, 2239);
  g->Binary(ynn_binary_add, 2119, 2239, 2240);
}

// Scope: "Layer14 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2240, 2241);
  g->Reduce(ynn_reduce_sum, 2241, 6504, {2}, true);
  g->ShapeProduct(2241, 6503, {2});
  g->Binary(ynn_binary_divide, 6504, 6503, 2242);
  g->Binary(ynn_binary_add, 2242, 7373, 2243);
  g->Binary(ynn_binary_pow, 2243, 7428, 2244);
  g->Binary(ynn_binary_multiply, 2240, 2244, 2245);
  g->Convert(7767, 2246);
  g->Binary(ynn_binary_multiply, 2245, 2246, 2247);
  g->Binary(ynn_binary_divide, 2247, 7309, 2250);
  g->Unary(ynn_unary_round, 2250, 2251);
  g->Binary(ynn_binary_max, 2251, 7225, 2252);
  g->Binary(ynn_binary_min, 2252, 7340, 2253);
  g->Binary(ynn_binary_multiply, 2253, 7309, 2254);
  g->Convert(7758, 2255);
  g->Binary(ynn_binary_multiply, 2255, 7759, 2256);
  g->Matmul(2254, 2256, 2257, false, true);
  g->Binary(ynn_binary_divide, 2257, 7417, 2258);
  g->Unary(ynn_unary_round, 2258, 2259);
  g->Binary(ynn_binary_max, 2259, 7225, 2261);
  g->Binary(ynn_binary_min, 2261, 7340, 2262);
  g->Binary(ynn_binary_multiply, 2262, 7417, 2263);
  g->Convert(7756, 2264);
  g->Binary(ynn_binary_multiply, 2264, 7757, 2265);
  g->Matmul(2254, 2265, 2267, false, true);
  g->Binary(ynn_binary_divide, 2267, 7417, 2268);
  g->Unary(ynn_unary_round, 2268, 2269);
  g->Binary(ynn_binary_max, 2269, 7225, 2270);
  g->Binary(ynn_binary_min, 2270, 7340, 2271);
  g->Binary(ynn_binary_multiply, 2271, 7417, 2272);
  g->Polynomial(2272, 6507, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6507, 6508);
  g->Binary(ynn_binary_add, 6508, 6183, 6505);
  g->Binary(ynn_binary_multiply, 2272, 6181, 6506);
  g->Binary(ynn_binary_multiply, 6506, 6505, 2273);
  g->Binary(ynn_binary_multiply, 2263, 2273, 2274);
  g->Binary(ynn_binary_divide, 2274, 7336, 2275);
  g->Unary(ynn_unary_round, 2275, 2276);
  g->Binary(ynn_binary_max, 2276, 7225, 2278);
  g->Binary(ynn_binary_min, 2278, 7340, 2279);
  g->Binary(ynn_binary_multiply, 2279, 7336, 2280);
  g->Convert(7754, 2281);
  g->Binary(ynn_binary_multiply, 2281, 7755, 2282);
  g->Matmul(2280, 2282, 2283, false, true);
  g->Binary(ynn_binary_divide, 2283, 7211, 2284);
  g->Unary(ynn_unary_round, 2284, 2285);
  g->Binary(ynn_binary_max, 2285, 7225, 2286);
  g->Binary(ynn_binary_min, 2286, 7340, 2287);
  g->Binary(ynn_binary_multiply, 2287, 7211, 2289);
  g->Unary(ynn_unary_square, 2289, 2290);
  g->Reduce(ynn_reduce_sum, 2290, 6510, {2}, true);
  g->ShapeProduct(2290, 6509, {2});
  g->Binary(ynn_binary_divide, 6510, 6509, 2291);
  g->Binary(ynn_binary_add, 2291, 7373, 2292);
  g->Binary(ynn_binary_pow, 2292, 7428, 2293);
  g->Binary(ynn_binary_multiply, 2289, 2293, 2294);
  g->Convert(7765, 2295);
  g->Binary(ynn_binary_multiply, 2294, 2295, 2296);
  g->Binary(ynn_binary_add, 2240, 2296, 2297);
}

// Scope: "Layer14 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1031, 2298, {0,0,14,0}, {-1,-1,1,-1});
  g->Reshape(2298, 2300, {1,1,256});
  g->Binary(ynn_binary_add, 2300, 8415, 2301);
  g->Binary(ynn_binary_multiply, 2301, 7155, 2302);
  g->Binary(ynn_binary_divide, 2297, 7539, 2303);
  g->Unary(ynn_unary_round, 2303, 2304);
  g->Binary(ynn_binary_max, 2304, 7225, 2305);
  g->Binary(ynn_binary_min, 2305, 7340, 2306);
  g->Binary(ynn_binary_multiply, 2306, 7539, 2307);
  g->Convert(7760, 2308);
  g->Binary(ynn_binary_multiply, 2308, 7761, 2309);
  g->Matmul(2307, 2309, 2311, false, true);
  g->Binary(ynn_binary_divide, 2311, 7439, 2312);
  g->Unary(ynn_unary_round, 2312, 2313);
  g->Binary(ynn_binary_max, 2313, 7225, 2314);
  g->Binary(ynn_binary_min, 2314, 7340, 2315);
  g->Binary(ynn_binary_multiply, 2315, 7439, 2316);
  g->Polynomial(2316, 6513, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6513, 6514);
  g->Binary(ynn_binary_add, 6514, 6183, 6511);
  g->Binary(ynn_binary_multiply, 2316, 6181, 6512);
  g->Binary(ynn_binary_multiply, 6512, 6511, 2317);
  g->Binary(ynn_binary_multiply, 2317, 2302, 2318);
  g->Binary(ynn_binary_divide, 2318, 7311, 2319);
  g->Unary(ynn_unary_round, 2319, 2320);
  g->Binary(ynn_binary_max, 2320, 7225, 2322);
  g->Binary(ynn_binary_min, 2322, 7340, 2323);
  g->Binary(ynn_binary_multiply, 2323, 7311, 2324);
  g->Convert(7762, 2325);
  g->Binary(ynn_binary_multiply, 2325, 7763, 2326);
  g->Matmul(2324, 2326, 2327, false, true);
  g->Binary(ynn_binary_divide, 2327, 7480, 2328);
  g->Unary(ynn_unary_round, 2328, 2329);
  g->Binary(ynn_binary_max, 2329, 7225, 2330);
  g->Binary(ynn_binary_min, 2330, 7340, 2331);
  g->Binary(ynn_binary_multiply, 2331, 7480, 2333);
  g->Unary(ynn_unary_square, 2333, 2334);
  g->Reduce(ynn_reduce_sum, 2334, 6516, {2}, true);
  g->ShapeProduct(2334, 6515, {2});
  g->Binary(ynn_binary_divide, 6516, 6515, 2335);
  g->Binary(ynn_binary_add, 2335, 7373, 2336);
  g->Binary(ynn_binary_pow, 2336, 7428, 2337);
  g->Binary(ynn_binary_multiply, 2333, 2337, 2338);
  g->Convert(7766, 2339);
  g->Binary(ynn_binary_multiply, 2338, 2339, 2340);
  g->Binary(ynn_binary_add, 2297, 2340, 2341);
  g->Convert(7753, 2342);
  g->Binary(ynn_binary_multiply, 2341, 2342, 2344);
}

// Scope: "Layer14"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14(Context& ctx) {
  BuildLayer14Attention(ctx);
  BuildLayer14Mlp(ctx);
  BuildLayer14PerLayerEmbedding(ctx);
}

}  // namespace BuildGemma4DecodeSource
