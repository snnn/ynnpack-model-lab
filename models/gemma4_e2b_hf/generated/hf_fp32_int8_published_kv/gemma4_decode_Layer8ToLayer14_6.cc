// Generated YNNPACK builder; do not edit.
#include "gemma4_decode_builder.h"

namespace BuildGemma4DecodeSource {

// Scope: "Layer8 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Binary(ynn_binary_divide, 788, 7324, 789);
  g->Unary(ynn_unary_round, 789, 790);
  g->Binary(ynn_binary_max, 790, 7155, 791);
  g->Binary(ynn_binary_min, 791, 7270, 792);
  g->Binary(ynn_binary_multiply, 792, 7324, 793);
  g->Convert(8301, 794);
  g->Binary(ynn_binary_multiply, 794, 8302, 795);
  g->Matmul(793, 795, 796, false, true);
  g->Binary(ynn_binary_divide, 796, 7421, 798);
  g->Unary(ynn_unary_round, 798, 799);
  g->Binary(ynn_binary_max, 799, 7155, 800);
  g->Binary(ynn_binary_min, 800, 7270, 801);
  g->Binary(ynn_binary_multiply, 801, 7421, 802);
  g->Reshape(802, 803, {1,1,1,256});
  g->Transpose(803, 804, {0,2,1,3});
  g->Unary(ynn_unary_square, 804, 805);
  g->Reduce(ynn_reduce_sum, 805, 6229, {3}, true);
  g->ShapeProduct(805, 6228, {3});
  g->Binary(ynn_binary_divide, 6229, 6228, 806);
  g->Binary(ynn_binary_add, 806, 7303, 807);
  g->Binary(ynn_binary_pow, 807, 7358, 809);
  g->Binary(ynn_binary_multiply, 804, 809, 810);
  g->Convert(8300, 811);
  g->Binary(ynn_binary_multiply, 810, 811, 812);
  g->Slice(812, 813, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(812, 814, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 814, 815);
  g->Concat({815,813}, 816, 3);
  g->Binary(ynn_binary_multiply, 812, 2025, 817);
  g->Binary(ynn_binary_multiply, 816, 3078, 818);
  g->Binary(ynn_binary_add, 817, 818, 821);
  g->Convert(8308, 822);
  g->Binary(ynn_binary_multiply, 822, 8309, 823);
  g->Matmul(793, 823, 824, false, true);
  g->Binary(ynn_binary_divide, 824, 7421, 825);
  g->Unary(ynn_unary_round, 825, 827);
  g->Binary(ynn_binary_max, 827, 7155, 828);
  g->Binary(ynn_binary_min, 828, 7270, 829);
  g->Binary(ynn_binary_multiply, 829, 7421, 830);
  g->Reshape(830, 831, {1,1,1,256});
  g->Transpose(831, 832, {0,2,1,3});
  g->Unary(ynn_unary_square, 832, 833);
  g->Reduce(ynn_reduce_sum, 833, 6231, {3}, true);
  g->ShapeProduct(833, 6230, {3});
  g->Binary(ynn_binary_divide, 6231, 6230, 834);
  g->Binary(ynn_binary_add, 834, 7303, 835);
  g->Binary(ynn_binary_pow, 835, 7358, 836);
  g->Binary(ynn_binary_multiply, 832, 836, 838);
}

// Scope: "Layer8 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(821, 839, 0.006215503439307213, 0);
  g->Append(7058, 839, 8388, 2, s2, slinky::expr(int64_t{1}));
  g->View(8388, 8418, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(8418, 840, 0.006215503439307213, 0);
  g->Quantize(838, 841, 0.047244105488061905, 0);
  g->Append(7073, 841, 8403, 2, s2, slinky::expr(int64_t{1}));
  g->View(8403, 8433, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(8433, 842, 0.047244105488061905, 0);
}

// Scope: "Layer8 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Convert(8306, 844);
  g->Binary(ynn_binary_multiply, 844, 8307, 845);
  g->Matmul(793, 845, 846, false, true);
  g->Binary(ynn_binary_divide, 846, 7159, 847);
  g->Unary(ynn_unary_round, 847, 848);
  g->Binary(ynn_binary_max, 848, 7155, 849);
  g->Binary(ynn_binary_min, 849, 7270, 851);
  g->Binary(ynn_binary_multiply, 851, 7159, 852);
  g->SplitDim(852, 853, 2, {8,256});
  g->Transpose(853, 854, {0,2,1,3});
  g->Unary(ynn_unary_square, 854, 855);
  g->Reduce(ynn_reduce_sum, 855, 6233, {3}, true);
  g->ShapeProduct(855, 6232, {3});
  g->Binary(ynn_binary_divide, 6233, 6232, 856);
  g->Binary(ynn_binary_add, 856, 7303, 857);
  g->Binary(ynn_binary_pow, 857, 7358, 858);
  g->Binary(ynn_binary_multiply, 854, 858, 859);
  g->Convert(8305, 860);
  g->Binary(ynn_binary_multiply, 859, 860, 862);
  g->Slice(862, 863, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(862, 864, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 864, 865);
  g->Concat({865,863}, 866, 3);
  g->Binary(ynn_binary_multiply, 862, 2025, 867);
  g->Binary(ynn_binary_multiply, 866, 3078, 868);
  g->Binary(ynn_binary_add, 867, 868, 869);
}

// Scope: "Layer8 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(869, 840, 870, false, true);
  g->Mask(870, 7524, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 7524, 6237, {-1}, true);
  g->Binary(ynn_binary_subtract, 7524, 6237, 6234);
  g->Unary(ynn_unary_exp, 6234, 6235);
  g->Reduce(ynn_reduce_sum, 6235, 6238, {-1}, true);
  g->Binary(ynn_binary_divide, 6113, 6238, 6236);
  g->Binary(ynn_binary_multiply, 6235, 6236, 872);
  g->Matmul(872, 842, 873, false, false);
}

// Scope: "Layer8 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(873, 874, {0,2,1,3});
  g->FuseDims(874, 875, 2, 2);
  g->Binary(ynn_binary_divide, 875, 7150, 876);
  g->Unary(ynn_unary_round, 876, 877);
  g->Binary(ynn_binary_max, 877, 7155, 878);
  g->Binary(ynn_binary_min, 878, 7270, 879);
  g->Binary(ynn_binary_multiply, 879, 7150, 880);
  g->Convert(8303, 881);
  g->Binary(ynn_binary_multiply, 881, 8304, 883);
  g->Matmul(880, 883, 884, false, true);
  g->Binary(ynn_binary_divide, 884, 7180, 885);
  g->Unary(ynn_unary_round, 885, 886);
  g->Binary(ynn_binary_max, 886, 7155, 887);
  g->Binary(ynn_binary_min, 887, 7270, 888);
  g->Binary(ynn_binary_multiply, 888, 7180, 889);
}

// Scope: "Layer8 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 780, 781);
  g->Reduce(ynn_reduce_sum, 781, 6227, {2}, true);
  g->ShapeProduct(781, 6226, {2});
  g->Binary(ynn_binary_divide, 6227, 6226, 782);
  g->Binary(ynn_binary_add, 782, 7303, 783);
  g->Binary(ynn_binary_pow, 783, 7358, 784);
  g->Binary(ynn_binary_multiply, 780, 784, 785);
  g->Convert(8284, 787);
  g->Binary(ynn_binary_multiply, 785, 787, 788);
  BuildLayer8AttentionKvProjection(ctx);
  BuildLayer8AttentionCacheUpdate(ctx);
  BuildLayer8AttentionQueryProjection(ctx);
  BuildLayer8AttentionSdpa(ctx);
  BuildLayer8AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 889, 890);
  g->Reduce(ynn_reduce_sum, 890, 6240, {2}, true);
  g->ShapeProduct(890, 6239, {2});
  g->Binary(ynn_binary_divide, 6240, 6239, 891);
  g->Binary(ynn_binary_add, 891, 7303, 892);
  g->Binary(ynn_binary_pow, 892, 7358, 894);
  g->Binary(ynn_binary_multiply, 889, 894, 895);
  g->Convert(8296, 896);
  g->Binary(ynn_binary_multiply, 895, 896, 897);
  g->Binary(ynn_binary_add, 780, 897, 898);
}

// Scope: "Layer8 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 898, 899);
  g->Reduce(ynn_reduce_sum, 899, 6242, {2}, true);
  g->ShapeProduct(899, 6241, {2});
  g->Binary(ynn_binary_divide, 6242, 6241, 900);
  g->Binary(ynn_binary_add, 900, 7303, 901);
  g->Binary(ynn_binary_pow, 901, 7358, 902);
  g->Binary(ynn_binary_multiply, 898, 902, 903);
  g->Convert(8299, 905);
  g->Binary(ynn_binary_multiply, 903, 905, 906);
  g->Binary(ynn_binary_divide, 906, 7269, 907);
  g->Unary(ynn_unary_round, 907, 908);
  g->Binary(ynn_binary_max, 908, 7155, 909);
  g->Binary(ynn_binary_min, 909, 7270, 910);
  g->Binary(ynn_binary_multiply, 910, 7269, 911);
  g->Convert(8290, 912);
  g->Binary(ynn_binary_multiply, 912, 8291, 913);
  g->Matmul(911, 913, 914, false, true);
  g->Binary(ynn_binary_divide, 914, 7129, 917);
  g->Unary(ynn_unary_round, 917, 918);
  g->Binary(ynn_binary_max, 918, 7155, 919);
  g->Binary(ynn_binary_min, 919, 7270, 920);
  g->Binary(ynn_binary_multiply, 920, 7129, 921);
  g->Convert(8288, 923);
  g->Binary(ynn_binary_multiply, 923, 8289, 924);
  g->Matmul(911, 924, 925, false, true);
  g->Binary(ynn_binary_divide, 925, 7129, 926);
  g->Unary(ynn_unary_round, 926, 927);
  g->Binary(ynn_binary_max, 927, 7155, 928);
  g->Binary(ynn_binary_min, 928, 7270, 929);
  g->Binary(ynn_binary_multiply, 929, 7129, 930);
  g->Polynomial(930, 6247, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6247, 6248);
  g->Binary(ynn_binary_add, 6248, 6113, 6245);
  g->Binary(ynn_binary_multiply, 930, 6111, 6246);
  g->Binary(ynn_binary_multiply, 6246, 6245, 931);
  g->Binary(ynn_binary_multiply, 921, 931, 932);
  g->Binary(ynn_binary_divide, 932, 7263, 934);
  g->Unary(ynn_unary_round, 934, 935);
  g->Binary(ynn_binary_max, 935, 7155, 936);
  g->Binary(ynn_binary_min, 936, 7270, 937);
  g->Binary(ynn_binary_multiply, 937, 7263, 938);
  g->Convert(8286, 939);
  g->Binary(ynn_binary_multiply, 939, 8287, 940);
  g->Matmul(938, 940, 941, false, true);
  g->Binary(ynn_binary_divide, 941, 7362, 942);
  g->Unary(ynn_unary_round, 942, 943);
  g->Binary(ynn_binary_max, 943, 7155, 945);
  g->Binary(ynn_binary_min, 945, 7270, 946);
  g->Binary(ynn_binary_multiply, 946, 7362, 947);
  g->Unary(ynn_unary_square, 947, 948);
  g->Reduce(ynn_reduce_sum, 948, 6250, {2}, true);
  g->ShapeProduct(948, 6249, {2});
  g->Binary(ynn_binary_divide, 6250, 6249, 949);
  g->Binary(ynn_binary_add, 949, 7303, 950);
  g->Binary(ynn_binary_pow, 950, 7358, 951);
  g->Binary(ynn_binary_multiply, 947, 951, 952);
  g->Convert(8297, 953);
  g->Binary(ynn_binary_multiply, 952, 953, 954);
  g->Binary(ynn_binary_add, 898, 954, 956);
}

// Scope: "Layer8 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1022, 957, {0,0,8,0}, {-1,-1,1,-1});
  g->Reshape(957, 958, {1,1,256});
  g->Binary(ynn_binary_add, 958, 8372, 959);
  g->Binary(ynn_binary_multiply, 959, 7085, 960);
  g->Binary(ynn_binary_divide, 956, 7118, 961);
  g->Unary(ynn_unary_round, 961, 962);
  g->Binary(ynn_binary_max, 962, 7155, 963);
  g->Binary(ynn_binary_min, 963, 7270, 964);
  g->Binary(ynn_binary_multiply, 964, 7118, 965);
  g->Convert(8292, 967);
  g->Binary(ynn_binary_multiply, 967, 8293, 968);
  g->Matmul(965, 968, 969, false, true);
  g->Binary(ynn_binary_divide, 969, 7125, 970);
  g->Unary(ynn_unary_round, 970, 971);
  g->Binary(ynn_binary_max, 971, 7155, 972);
  g->Binary(ynn_binary_min, 972, 7270, 973);
  g->Binary(ynn_binary_multiply, 973, 7125, 974);
  g->Polynomial(974, 6253, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6253, 6254);
  g->Binary(ynn_binary_add, 6254, 6113, 6251);
  g->Binary(ynn_binary_multiply, 974, 6111, 6252);
  g->Binary(ynn_binary_multiply, 6252, 6251, 975);
  g->Binary(ynn_binary_multiply, 975, 960, 976);
  g->Binary(ynn_binary_divide, 976, 7184, 978);
  g->Unary(ynn_unary_round, 978, 979);
  g->Binary(ynn_binary_max, 979, 7155, 980);
  g->Binary(ynn_binary_min, 980, 7270, 981);
  g->Binary(ynn_binary_multiply, 981, 7184, 982);
  g->Convert(8294, 983);
  g->Binary(ynn_binary_multiply, 983, 8295, 984);
  g->Matmul(982, 984, 985, false, true);
  g->Binary(ynn_binary_divide, 985, 7098, 986);
  g->Unary(ynn_unary_round, 986, 987);
  g->Binary(ynn_binary_max, 987, 7155, 989);
  g->Binary(ynn_binary_min, 989, 7270, 990);
  g->Binary(ynn_binary_multiply, 990, 7098, 991);
  g->Unary(ynn_unary_square, 991, 992);
  g->Reduce(ynn_reduce_sum, 992, 6256, {2}, true);
  g->ShapeProduct(992, 6255, {2});
  g->Binary(ynn_binary_divide, 6256, 6255, 993);
  g->Binary(ynn_binary_add, 993, 7303, 994);
  g->Binary(ynn_binary_pow, 994, 7358, 995);
  g->Binary(ynn_binary_multiply, 991, 995, 996);
  g->Convert(8298, 997);
  g->Binary(ynn_binary_multiply, 996, 997, 998);
  g->Binary(ynn_binary_add, 956, 998, 1000);
  g->Convert(8285, 1001);
  g->Binary(ynn_binary_multiply, 1000, 1001, 1002);
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
  g->Binary(ynn_binary_divide, 1009, 7083, 1011);
  g->Unary(ynn_unary_round, 1011, 1012);
  g->Binary(ynn_binary_max, 1012, 7155, 1013);
  g->Binary(ynn_binary_min, 1013, 7270, 1014);
  g->Binary(ynn_binary_multiply, 1014, 7083, 1015);
  g->Convert(8327, 1016);
  g->Binary(ynn_binary_multiply, 1016, 8328, 1017);
  g->Matmul(1015, 1017, 1018, false, true);
  g->Binary(ynn_binary_divide, 1018, 7428, 1019);
  g->Unary(ynn_unary_round, 1019, 1020);
  g->Binary(ynn_binary_max, 1020, 7155, 1024);
  g->Binary(ynn_binary_min, 1024, 7270, 1025);
  g->Binary(ynn_binary_multiply, 1025, 7428, 1026);
  g->Reshape(1026, 1027, {1,1,1,512});
  g->Transpose(1027, 1028, {0,2,1,3});
  g->Unary(ynn_unary_square, 1028, 1029);
  g->Reduce(ynn_reduce_sum, 1029, 6260, {3}, true);
  g->ShapeProduct(1029, 6259, {3});
  g->Binary(ynn_binary_divide, 6260, 6259, 1030);
  g->Binary(ynn_binary_add, 1030, 7303, 1031);
  g->Binary(ynn_binary_pow, 1031, 7358, 1032);
  g->Binary(ynn_binary_multiply, 1028, 1032, 1033);
  g->Convert(8326, 1035);
  g->Binary(ynn_binary_multiply, 1033, 1035, 1036);
  g->Slice(1036, 1037, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(1036, 1038, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 1038, 1039);
  g->Concat({1039,1037}, 1040, 3);
  g->Binary(ynn_binary_multiply, 1036, 5909, 1041);
  g->Binary(ynn_binary_multiply, 1040, 6008, 1042);
  g->Binary(ynn_binary_add, 1041, 1042, 1043);
  g->Convert(8334, 1045);
  g->Binary(ynn_binary_multiply, 1045, 8335, 1046);
  g->Matmul(1015, 1046, 1047, false, true);
  g->Binary(ynn_binary_divide, 1047, 7428, 1048);
  g->Unary(ynn_unary_round, 1048, 1049);
  g->Binary(ynn_binary_max, 1049, 7155, 1050);
  g->Binary(ynn_binary_min, 1050, 7270, 1052);
  g->Binary(ynn_binary_multiply, 1052, 7428, 1053);
  g->Reshape(1053, 1054, {1,1,1,512});
  g->Transpose(1054, 1055, {0,2,1,3});
  g->Unary(ynn_unary_square, 1055, 1056);
  g->Reduce(ynn_reduce_sum, 1056, 6262, {3}, true);
  g->ShapeProduct(1056, 6261, {3});
  g->Binary(ynn_binary_divide, 6262, 6261, 1057);
  g->Binary(ynn_binary_add, 1057, 7303, 1058);
  g->Binary(ynn_binary_pow, 1058, 7358, 1059);
  g->Binary(ynn_binary_multiply, 1055, 1059, 1060);
}

// Scope: "Layer9 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(1043, 1061, 0.0010733711533248425, 0);
  g->Append(7059, 1061, 8389, 2, s2, slinky::expr(int64_t{1}));
  g->View(8389, 8419, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(8419, 1063, 0.0010733711533248425, 0);
  g->Quantize(1060, 1064, 0.01785714365541935, 0);
  g->Append(7074, 1064, 8404, 2, s2, slinky::expr(int64_t{1}));
  g->View(8404, 8434, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(8434, 1065, 0.01785714365541935, 0);
}

// Scope: "Layer9 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Convert(8332, 1067);
  g->Binary(ynn_binary_multiply, 1067, 8333, 1068);
  g->Matmul(1015, 1068, 1069, false, true);
  g->Binary(ynn_binary_divide, 1069, 7216, 1070);
  g->Unary(ynn_unary_round, 1070, 1071);
  g->Binary(ynn_binary_max, 1071, 7155, 1072);
  g->Binary(ynn_binary_min, 1072, 7270, 1073);
  g->Binary(ynn_binary_multiply, 1073, 7216, 1074);
  g->SplitDim(1074, 1076, 2, {8,512});
  g->Transpose(1076, 1077, {0,2,1,3});
  g->Unary(ynn_unary_square, 1077, 1078);
  g->Reduce(ynn_reduce_sum, 1078, 6264, {3}, true);
  g->ShapeProduct(1078, 6263, {3});
  g->Binary(ynn_binary_divide, 6264, 6263, 1079);
  g->Binary(ynn_binary_add, 1079, 7303, 1080);
  g->Binary(ynn_binary_pow, 1080, 7358, 1081);
  g->Binary(ynn_binary_multiply, 1077, 1081, 1082);
  g->Convert(8331, 1083);
  g->Binary(ynn_binary_multiply, 1082, 1083, 1084);
  g->Slice(1084, 1085, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(1084, 1087, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 1087, 1088);
  g->Concat({1088,1085}, 1089, 3);
  g->Binary(ynn_binary_multiply, 1084, 5909, 1090);
  g->Binary(ynn_binary_multiply, 1089, 6008, 1091);
  g->Binary(ynn_binary_add, 1090, 1091, 1092);
}

// Scope: "Layer9 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(1092, 1063, 1093, false, true);
  g->Mask(1093, 7525, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 7525, 6268, {-1}, true);
  g->Binary(ynn_binary_subtract, 7525, 6268, 6265);
  g->Unary(ynn_unary_exp, 6265, 6266);
  g->Reduce(ynn_reduce_sum, 6266, 6269, {-1}, true);
  g->Binary(ynn_binary_divide, 6113, 6269, 6267);
  g->Binary(ynn_binary_multiply, 6266, 6267, 1094);
  g->Matmul(1094, 1065, 1095, false, false);
}

// Scope: "Layer9 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1095, 1097, {0,2,1,3});
  g->FuseDims(1097, 1098, 2, 2);
  g->Binary(ynn_binary_divide, 1098, 7245, 1099);
  g->Unary(ynn_unary_round, 1099, 1100);
  g->Binary(ynn_binary_max, 1100, 7155, 1101);
  g->Binary(ynn_binary_min, 1101, 7270, 1102);
  g->Binary(ynn_binary_multiply, 1102, 7245, 1103);
  g->Convert(8329, 1104);
  g->Binary(ynn_binary_multiply, 1104, 8330, 1105);
  g->Matmul(1103, 1105, 1106, false, true);
  g->Binary(ynn_binary_divide, 1106, 7136, 1108);
  g->Unary(ynn_unary_round, 1108, 1109);
  g->Binary(ynn_binary_max, 1109, 7155, 1110);
  g->Binary(ynn_binary_min, 1110, 7270, 1111);
  g->Binary(ynn_binary_multiply, 1111, 7136, 1112);
}

// Scope: "Layer9 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1002, 1003);
  g->Reduce(ynn_reduce_sum, 1003, 6258, {2}, true);
  g->ShapeProduct(1003, 6257, {2});
  g->Binary(ynn_binary_divide, 6258, 6257, 1004);
  g->Binary(ynn_binary_add, 1004, 7303, 1005);
  g->Binary(ynn_binary_pow, 1005, 7358, 1006);
  g->Binary(ynn_binary_multiply, 1002, 1006, 1007);
  g->Convert(8310, 1008);
  g->Binary(ynn_binary_multiply, 1007, 1008, 1009);
  BuildLayer9AttentionKvProjection(ctx);
  BuildLayer9AttentionCacheUpdate(ctx);
  BuildLayer9AttentionQueryProjection(ctx);
  BuildLayer9AttentionSdpa(ctx);
  BuildLayer9AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1112, 1113);
  g->Reduce(ynn_reduce_sum, 1113, 6271, {2}, true);
  g->ShapeProduct(1113, 6270, {2});
  g->Binary(ynn_binary_divide, 6271, 6270, 1114);
  g->Binary(ynn_binary_add, 1114, 7303, 1115);
  g->Binary(ynn_binary_pow, 1115, 7358, 1116);
  g->Binary(ynn_binary_multiply, 1112, 1116, 1117);
  g->Convert(8322, 1120);
  g->Binary(ynn_binary_multiply, 1117, 1120, 1121);
  g->Binary(ynn_binary_add, 1002, 1121, 1122);
}

// Scope: "Layer9 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1122, 1123);
  g->Reduce(ynn_reduce_sum, 1123, 6273, {2}, true);
  g->ShapeProduct(1123, 6272, {2});
  g->Binary(ynn_binary_divide, 6273, 6272, 1124);
  g->Binary(ynn_binary_add, 1124, 7303, 1125);
  g->Binary(ynn_binary_pow, 1125, 7358, 1126);
  g->Binary(ynn_binary_multiply, 1122, 1126, 1127);
  g->Convert(8325, 1128);
  g->Binary(ynn_binary_multiply, 1127, 1128, 1129);
  g->Binary(ynn_binary_divide, 1129, 7325, 1131);
  g->Unary(ynn_unary_round, 1131, 1132);
  g->Binary(ynn_binary_max, 1132, 7155, 1133);
  g->Binary(ynn_binary_min, 1133, 7270, 1134);
  g->Binary(ynn_binary_multiply, 1134, 7325, 1135);
  g->Convert(8316, 1136);
  g->Binary(ynn_binary_multiply, 1136, 8317, 1137);
  g->Matmul(1135, 1137, 1138, false, true);
  g->Binary(ynn_binary_divide, 1138, 7315, 1139);
  g->Unary(ynn_unary_round, 1139, 1140);
  g->Binary(ynn_binary_max, 1140, 7155, 1142);
  g->Binary(ynn_binary_min, 1142, 7270, 1143);
  g->Binary(ynn_binary_multiply, 1143, 7315, 1144);
  g->Convert(8314, 1145);
  g->Binary(ynn_binary_multiply, 1145, 8315, 1146);
  g->Matmul(1135, 1146, 1148, false, true);
  g->Binary(ynn_binary_divide, 1148, 7315, 1149);
  g->Unary(ynn_unary_round, 1149, 1150);
  g->Binary(ynn_binary_max, 1150, 7155, 1151);
  g->Binary(ynn_binary_min, 1151, 7270, 1152);
  g->Binary(ynn_binary_multiply, 1152, 7315, 1153);
  g->Polynomial(1153, 6276, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6276, 6277);
  g->Binary(ynn_binary_add, 6277, 6113, 6274);
  g->Binary(ynn_binary_multiply, 1153, 6111, 6275);
  g->Binary(ynn_binary_multiply, 6275, 6274, 1154);
  g->Binary(ynn_binary_multiply, 1144, 1154, 1155);
  g->Binary(ynn_binary_divide, 1155, 7422, 1156);
  g->Unary(ynn_unary_round, 1156, 1157);
  g->Binary(ynn_binary_max, 1157, 7155, 1159);
  g->Binary(ynn_binary_min, 1159, 7270, 1160);
  g->Binary(ynn_binary_multiply, 1160, 7422, 1161);
  g->Convert(8312, 1162);
  g->Binary(ynn_binary_multiply, 1162, 8313, 1163);
  g->Matmul(1161, 1163, 1164, false, true);
  g->Binary(ynn_binary_divide, 1164, 7170, 1165);
  g->Unary(ynn_unary_round, 1165, 1166);
  g->Binary(ynn_binary_max, 1166, 7155, 1167);
  g->Binary(ynn_binary_min, 1167, 7270, 1168);
  g->Binary(ynn_binary_multiply, 1168, 7170, 1170);
  g->Unary(ynn_unary_square, 1170, 1171);
  g->Reduce(ynn_reduce_sum, 1171, 6283, {2}, true);
  g->ShapeProduct(1171, 6282, {2});
  g->Binary(ynn_binary_divide, 6283, 6282, 1172);
  g->Binary(ynn_binary_add, 1172, 7303, 1173);
  g->Binary(ynn_binary_pow, 1173, 7358, 1174);
  g->Binary(ynn_binary_multiply, 1170, 1174, 1175);
  g->Convert(8323, 1176);
  g->Binary(ynn_binary_multiply, 1175, 1176, 1177);
  g->Binary(ynn_binary_add, 1122, 1177, 1178);
}

// Scope: "Layer9 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1022, 1179, {0,0,9,0}, {-1,-1,1,-1});
  g->Reshape(1179, 1181, {1,1,256});
  g->Binary(ynn_binary_add, 1181, 8373, 1182);
  g->Binary(ynn_binary_multiply, 1182, 7085, 1183);
  g->Binary(ynn_binary_divide, 1178, 7182, 1184);
  g->Unary(ynn_unary_round, 1184, 1185);
  g->Binary(ynn_binary_max, 1185, 7155, 1186);
  g->Binary(ynn_binary_min, 1186, 7270, 1187);
  g->Binary(ynn_binary_multiply, 1187, 7182, 1188);
  g->Convert(8318, 1189);
  g->Binary(ynn_binary_multiply, 1189, 8319, 1190);
  g->Matmul(1188, 1190, 1192, false, true);
  g->Binary(ynn_binary_divide, 1192, 7176, 1193);
  g->Unary(ynn_unary_round, 1193, 1194);
  g->Binary(ynn_binary_max, 1194, 7155, 1195);
  g->Binary(ynn_binary_min, 1195, 7270, 1196);
  g->Binary(ynn_binary_multiply, 1196, 7176, 1197);
  g->Polynomial(1197, 6286, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6286, 6287);
  g->Binary(ynn_binary_add, 6287, 6113, 6284);
  g->Binary(ynn_binary_multiply, 1197, 6111, 6285);
  g->Binary(ynn_binary_multiply, 6285, 6284, 1198);
  g->Binary(ynn_binary_multiply, 1198, 1183, 1199);
  g->Binary(ynn_binary_divide, 1199, 7343, 1200);
  g->Unary(ynn_unary_round, 1200, 1201);
  g->Binary(ynn_binary_max, 1201, 7155, 1203);
  g->Binary(ynn_binary_min, 1203, 7270, 1204);
  g->Binary(ynn_binary_multiply, 1204, 7343, 1205);
  g->Convert(8320, 1206);
  g->Binary(ynn_binary_multiply, 1206, 8321, 1207);
  g->Matmul(1205, 1207, 1208, false, true);
  g->Binary(ynn_binary_divide, 1208, 7425, 1209);
  g->Unary(ynn_unary_round, 1209, 1210);
  g->Binary(ynn_binary_max, 1210, 7155, 1211);
  g->Binary(ynn_binary_min, 1211, 7270, 1212);
  g->Binary(ynn_binary_multiply, 1212, 7425, 1214);
  g->Unary(ynn_unary_square, 1214, 1215);
  g->Reduce(ynn_reduce_sum, 1215, 6289, {2}, true);
  g->ShapeProduct(1215, 6288, {2});
  g->Binary(ynn_binary_divide, 6289, 6288, 1216);
  g->Binary(ynn_binary_add, 1216, 7303, 1217);
  g->Binary(ynn_binary_pow, 1217, 7358, 1218);
  g->Binary(ynn_binary_multiply, 1214, 1218, 1219);
  g->Convert(8324, 1220);
  g->Binary(ynn_binary_multiply, 1219, 1220, 1221);
  g->Binary(ynn_binary_add, 1178, 1221, 1222);
  g->Convert(8311, 1223);
  g->Binary(ynn_binary_multiply, 1222, 1223, 1226);
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
  g->Binary(ynn_binary_divide, 1233, 7172, 1234);
  g->Unary(ynn_unary_round, 1234, 1235);
  g->Binary(ynn_binary_max, 1235, 7155, 1237);
  g->Binary(ynn_binary_min, 1237, 7270, 1238);
  g->Binary(ynn_binary_multiply, 1238, 7172, 1239);
  g->Convert(7595, 1240);
  g->Binary(ynn_binary_multiply, 1240, 7596, 1241);
  g->Matmul(1239, 1241, 1242, false, true);
  g->Binary(ynn_binary_divide, 1242, 7096, 1243);
  g->Unary(ynn_unary_round, 1243, 1244);
  g->Binary(ynn_binary_max, 1244, 7155, 1245);
  g->Binary(ynn_binary_min, 1245, 7270, 1246);
  g->Binary(ynn_binary_multiply, 1246, 7096, 1248);
  g->Reshape(1248, 1249, {1,1,1,256});
  g->Transpose(1249, 1250, {0,2,1,3});
  g->Unary(ynn_unary_square, 1250, 1251);
  g->Reduce(ynn_reduce_sum, 1251, 6295, {3}, true);
  g->ShapeProduct(1251, 6294, {3});
  g->Binary(ynn_binary_divide, 6295, 6294, 1252);
  g->Binary(ynn_binary_add, 1252, 7303, 1253);
  g->Binary(ynn_binary_pow, 1253, 7358, 1254);
  g->Binary(ynn_binary_multiply, 1250, 1254, 1255);
  g->Convert(7594, 1256);
  g->Binary(ynn_binary_multiply, 1255, 1256, 1257);
  g->Slice(1257, 1259, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1257, 1260, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1260, 1261);
  g->Concat({1261,1259}, 1262, 3);
  g->Binary(ynn_binary_multiply, 1257, 2025, 1263);
  g->Binary(ynn_binary_multiply, 1262, 3078, 1264);
  g->Binary(ynn_binary_add, 1263, 1264, 1265);
  g->Convert(7602, 1267);
  g->Binary(ynn_binary_multiply, 1267, 7603, 1268);
  g->Matmul(1239, 1268, 1269, false, true);
  g->Binary(ynn_binary_divide, 1269, 7096, 1270);
  g->Unary(ynn_unary_round, 1270, 1271);
  g->Binary(ynn_binary_max, 1271, 7155, 1272);
  g->Binary(ynn_binary_min, 1272, 7270, 1273);
  g->Binary(ynn_binary_multiply, 1273, 7096, 1274);
  g->Reshape(1274, 1276, {1,1,1,256});
  g->Transpose(1276, 1277, {0,2,1,3});
  g->Unary(ynn_unary_square, 1277, 1278);
  g->Reduce(ynn_reduce_sum, 1278, 6297, {3}, true);
  g->ShapeProduct(1278, 6296, {3});
  g->Binary(ynn_binary_divide, 6297, 6296, 1279);
  g->Binary(ynn_binary_add, 1279, 7303, 1280);
  g->Binary(ynn_binary_pow, 1280, 7358, 1281);
  g->Binary(ynn_binary_multiply, 1277, 1281, 1282);
}

// Scope: "Layer10 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(1265, 1283, 0.005712664220482111, 0);
  g->Append(7047, 1283, 8377, 2, s2, slinky::expr(int64_t{1}));
  g->View(8377, 8407, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(8407, 1285, 0.005712664220482111, 0);
  g->Quantize(1282, 1286, 0.047244105488061905, 0);
  g->Append(7062, 1286, 8392, 2, s2, slinky::expr(int64_t{1}));
  g->View(8392, 8422, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(8422, 1287, 0.047244105488061905, 0);
}

// Scope: "Layer10 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Convert(7600, 1289);
  g->Binary(ynn_binary_multiply, 1289, 7601, 1290);
  g->Matmul(1239, 1290, 1291, false, true);
  g->Binary(ynn_binary_divide, 1291, 7370, 1292);
  g->Unary(ynn_unary_round, 1292, 1293);
  g->Binary(ynn_binary_max, 1293, 7155, 1294);
  g->Binary(ynn_binary_min, 1294, 7270, 1295);
  g->Binary(ynn_binary_multiply, 1295, 7370, 1296);
  g->SplitDim(1296, 1297, 2, {8,256});
  g->Transpose(1297, 1298, {0,2,1,3});
  g->Unary(ynn_unary_square, 1298, 1300);
  g->Reduce(ynn_reduce_sum, 1300, 6299, {3}, true);
  g->ShapeProduct(1300, 6298, {3});
  g->Binary(ynn_binary_divide, 6299, 6298, 1301);
  g->Binary(ynn_binary_add, 1301, 7303, 1302);
  g->Binary(ynn_binary_pow, 1302, 7358, 1303);
  g->Binary(ynn_binary_multiply, 1298, 1303, 1304);
  g->Convert(7599, 1305);
  g->Binary(ynn_binary_multiply, 1304, 1305, 1306);
  g->Slice(1306, 1307, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1306, 1308, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1308, 1309);
  g->Concat({1309,1307}, 1311, 3);
  g->Binary(ynn_binary_multiply, 1306, 2025, 1312);
  g->Binary(ynn_binary_multiply, 1311, 3078, 1313);
  g->Binary(ynn_binary_add, 1312, 1313, 1314);
}

// Scope: "Layer10 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(1314, 1285, 1315, false, true);
  g->Mask(1315, 7493, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 7493, 6303, {-1}, true);
  g->Binary(ynn_binary_subtract, 7493, 6303, 6300);
  g->Unary(ynn_unary_exp, 6300, 6301);
  g->Reduce(ynn_reduce_sum, 6301, 6304, {-1}, true);
  g->Binary(ynn_binary_divide, 6113, 6304, 6302);
  g->Binary(ynn_binary_multiply, 6301, 6302, 1316);
  g->Matmul(1316, 1287, 1317, false, false);
}

// Scope: "Layer10 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1317, 1318, {0,2,1,3});
  g->FuseDims(1318, 1319, 2, 2);
  g->Binary(ynn_binary_divide, 1319, 7271, 1322);
  g->Unary(ynn_unary_round, 1322, 1323);
  g->Binary(ynn_binary_max, 1323, 7155, 1324);
  g->Binary(ynn_binary_min, 1324, 7270, 1325);
  g->Binary(ynn_binary_multiply, 1325, 7271, 1326);
  g->Convert(7597, 1327);
  g->Binary(ynn_binary_multiply, 1327, 7598, 1328);
  g->Matmul(1326, 1328, 1329, false, true);
  g->Binary(ynn_binary_divide, 1329, 7268, 1330);
  g->Unary(ynn_unary_round, 1330, 1331);
  g->Binary(ynn_binary_max, 1331, 7155, 1333);
  g->Binary(ynn_binary_min, 1333, 7270, 1334);
  g->Binary(ynn_binary_multiply, 1334, 7268, 1335);
}

// Scope: "Layer10 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1226, 1227);
  g->Reduce(ynn_reduce_sum, 1227, 6293, {2}, true);
  g->ShapeProduct(1227, 6292, {2});
  g->Binary(ynn_binary_divide, 6293, 6292, 1228);
  g->Binary(ynn_binary_add, 1228, 7303, 1229);
  g->Binary(ynn_binary_pow, 1229, 7358, 1230);
  g->Binary(ynn_binary_multiply, 1226, 1230, 1231);
  g->Convert(7578, 1232);
  g->Binary(ynn_binary_multiply, 1231, 1232, 1233);
  BuildLayer10AttentionKvProjection(ctx);
  BuildLayer10AttentionCacheUpdate(ctx);
  BuildLayer10AttentionQueryProjection(ctx);
  BuildLayer10AttentionSdpa(ctx);
  BuildLayer10AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1335, 1336);
  g->Reduce(ynn_reduce_sum, 1336, 6308, {2}, true);
  g->ShapeProduct(1336, 6307, {2});
  g->Binary(ynn_binary_divide, 6308, 6307, 1337);
  g->Binary(ynn_binary_add, 1337, 7303, 1338);
  g->Binary(ynn_binary_pow, 1338, 7358, 1339);
  g->Binary(ynn_binary_multiply, 1335, 1339, 1340);
  g->Convert(7590, 1341);
  g->Binary(ynn_binary_multiply, 1340, 1341, 1342);
  g->Binary(ynn_binary_add, 1226, 1342, 1344);
}

// Scope: "Layer10 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1344, 1345);
  g->Reduce(ynn_reduce_sum, 1345, 6310, {2}, true);
  g->ShapeProduct(1345, 6309, {2});
  g->Binary(ynn_binary_divide, 6310, 6309, 1346);
  g->Binary(ynn_binary_add, 1346, 7303, 1347);
  g->Binary(ynn_binary_pow, 1347, 7358, 1348);
  g->Binary(ynn_binary_multiply, 1344, 1348, 1349);
  g->Convert(7593, 1350);
  g->Binary(ynn_binary_multiply, 1349, 1350, 1351);
  g->Binary(ynn_binary_divide, 1351, 7355, 1352);
  g->Unary(ynn_unary_round, 1352, 1353);
  g->Binary(ynn_binary_max, 1353, 7155, 1355);
  g->Binary(ynn_binary_min, 1355, 7270, 1356);
  g->Binary(ynn_binary_multiply, 1356, 7355, 1357);
  g->Convert(7584, 1358);
  g->Binary(ynn_binary_multiply, 1358, 7585, 1359);
  g->Matmul(1357, 1359, 1360, false, true);
  g->Binary(ynn_binary_divide, 1360, 7132, 1361);
  g->Unary(ynn_unary_round, 1361, 1362);
  g->Binary(ynn_binary_max, 1362, 7155, 1363);
  g->Binary(ynn_binary_min, 1363, 7270, 1364);
  g->Binary(ynn_binary_multiply, 1364, 7132, 1366);
  g->Convert(7582, 1367);
  g->Binary(ynn_binary_multiply, 1367, 7583, 1368);
  g->Matmul(1357, 1368, 1369, false, true);
  g->Binary(ynn_binary_divide, 1369, 7132, 1370);
  g->Unary(ynn_unary_round, 1370, 1372);
  g->Binary(ynn_binary_max, 1372, 7155, 1373);
  g->Binary(ynn_binary_min, 1373, 7270, 1374);
  g->Binary(ynn_binary_multiply, 1374, 7132, 1375);
  g->Polynomial(1375, 6313, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6313, 6314);
  g->Binary(ynn_binary_add, 6314, 6113, 6311);
  g->Binary(ynn_binary_multiply, 1375, 6111, 6312);
  g->Binary(ynn_binary_multiply, 6312, 6311, 1376);
  g->Binary(ynn_binary_multiply, 1366, 1376, 1377);
  g->Binary(ynn_binary_divide, 1377, 7460, 1378);
  g->Unary(ynn_unary_round, 1378, 1379);
  g->Binary(ynn_binary_max, 1379, 7155, 1380);
  g->Binary(ynn_binary_min, 1380, 7270, 1381);
  g->Binary(ynn_binary_multiply, 1381, 7460, 1383);
  g->Convert(7580, 1384);
  g->Binary(ynn_binary_multiply, 1384, 7581, 1385);
  g->Matmul(1383, 1385, 1386, false, true);
  g->Binary(ynn_binary_divide, 1386, 7210, 1387);
  g->Unary(ynn_unary_round, 1387, 1388);
  g->Binary(ynn_binary_max, 1388, 7155, 1389);
  g->Binary(ynn_binary_min, 1389, 7270, 1390);
  g->Binary(ynn_binary_multiply, 1390, 7210, 1391);
  g->Unary(ynn_unary_square, 1391, 1392);
  g->Reduce(ynn_reduce_sum, 1392, 6316, {2}, true);
  g->ShapeProduct(1392, 6315, {2});
  g->Binary(ynn_binary_divide, 6316, 6315, 1394);
  g->Binary(ynn_binary_add, 1394, 7303, 1395);
  g->Binary(ynn_binary_pow, 1395, 7358, 1396);
  g->Binary(ynn_binary_multiply, 1391, 1396, 1397);
  g->Convert(7591, 1398);
  g->Binary(ynn_binary_multiply, 1397, 1398, 1399);
  g->Binary(ynn_binary_add, 1344, 1399, 1400);
}

// Scope: "Layer10 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1022, 1401, {0,0,10,0}, {-1,-1,1,-1});
  g->Reshape(1401, 1402, {1,1,256});
  g->Binary(ynn_binary_add, 1402, 8341, 1403);
  g->Binary(ynn_binary_multiply, 1403, 7085, 1405);
  g->Binary(ynn_binary_divide, 1400, 7144, 1406);
  g->Unary(ynn_unary_round, 1406, 1407);
  g->Binary(ynn_binary_max, 1407, 7155, 1408);
  g->Binary(ynn_binary_min, 1408, 7270, 1409);
  g->Binary(ynn_binary_multiply, 1409, 7144, 1410);
  g->Convert(7586, 1411);
  g->Binary(ynn_binary_multiply, 1411, 7587, 1412);
  g->Matmul(1410, 1412, 1413, false, true);
  g->Binary(ynn_binary_divide, 1413, 7451, 1414);
  g->Unary(ynn_unary_round, 1414, 1416);
  g->Binary(ynn_binary_max, 1416, 7155, 1417);
  g->Binary(ynn_binary_min, 1417, 7270, 1418);
  g->Binary(ynn_binary_multiply, 1418, 7451, 1419);
  g->Polynomial(1419, 6319, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6319, 6320);
  g->Binary(ynn_binary_add, 6320, 6113, 6317);
  g->Binary(ynn_binary_multiply, 1419, 6111, 6318);
  g->Binary(ynn_binary_multiply, 6318, 6317, 1420);
  g->Binary(ynn_binary_multiply, 1420, 1405, 1421);
  g->Binary(ynn_binary_divide, 1421, 7153, 1422);
  g->Unary(ynn_unary_round, 1422, 1423);
  g->Binary(ynn_binary_max, 1423, 7155, 1424);
  g->Binary(ynn_binary_min, 1424, 7270, 1425);
  g->Binary(ynn_binary_multiply, 1425, 7153, 1428);
  g->Convert(7588, 1429);
  g->Binary(ynn_binary_multiply, 1429, 7589, 1430);
  g->Matmul(1428, 1430, 1431, false, true);
  g->Binary(ynn_binary_divide, 1431, 7391, 1432);
  g->Unary(ynn_unary_round, 1432, 1433);
  g->Binary(ynn_binary_max, 1433, 7155, 1434);
  g->Binary(ynn_binary_min, 1434, 7270, 1435);
  g->Binary(ynn_binary_multiply, 1435, 7391, 1436);
  g->Unary(ynn_unary_square, 1436, 1437);
  g->Reduce(ynn_reduce_sum, 1437, 6324, {2}, true);
  g->ShapeProduct(1437, 6323, {2});
  g->Binary(ynn_binary_divide, 6324, 6323, 1439);
  g->Binary(ynn_binary_add, 1439, 7303, 1440);
  g->Binary(ynn_binary_pow, 1440, 7358, 1441);
  g->Binary(ynn_binary_multiply, 1436, 1441, 1442);
  g->Convert(7592, 1443);
  g->Binary(ynn_binary_multiply, 1442, 1443, 1444);
  g->Binary(ynn_binary_add, 1400, 1444, 1445);
  g->Convert(7579, 1446);
  g->Binary(ynn_binary_multiply, 1445, 1446, 1447);
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
  g->Binary(ynn_binary_divide, 1455, 7427, 1456);
  g->Unary(ynn_unary_round, 1456, 1457);
  g->Binary(ynn_binary_max, 1457, 7155, 1458);
  g->Binary(ynn_binary_min, 1458, 7270, 1459);
  g->Binary(ynn_binary_multiply, 1459, 7427, 1461);
  g->Convert(7621, 1462);
  g->Binary(ynn_binary_multiply, 1462, 7622, 1463);
  g->Matmul(1461, 1463, 1464, false, true);
  g->Binary(ynn_binary_divide, 1464, 7412, 1465);
  g->Unary(ynn_unary_round, 1465, 1466);
  g->Binary(ynn_binary_max, 1466, 7155, 1467);
  g->Binary(ynn_binary_min, 1467, 7270, 1468);
  g->Binary(ynn_binary_multiply, 1468, 7412, 1469);
  g->Reshape(1469, 1470, {1,1,1,256});
  g->Transpose(1470, 1472, {0,2,1,3});
  g->Unary(ynn_unary_square, 1472, 1473);
  g->Reduce(ynn_reduce_sum, 1473, 6328, {3}, true);
  g->ShapeProduct(1473, 6327, {3});
  g->Binary(ynn_binary_divide, 6328, 6327, 1474);
  g->Binary(ynn_binary_add, 1474, 7303, 1475);
  g->Binary(ynn_binary_pow, 1475, 7358, 1476);
  g->Binary(ynn_binary_multiply, 1472, 1476, 1477);
  g->Convert(7620, 1478);
  g->Binary(ynn_binary_multiply, 1477, 1478, 1479);
  g->Slice(1479, 1480, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1479, 1481, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1481, 1483);
  g->Concat({1483,1480}, 1484, 3);
  g->Binary(ynn_binary_multiply, 1479, 2025, 1485);
  g->Binary(ynn_binary_multiply, 1484, 3078, 1486);
  g->Binary(ynn_binary_add, 1485, 1486, 1487);
  g->Convert(7628, 1489);
  g->Binary(ynn_binary_multiply, 1489, 7629, 1490);
  g->Matmul(1461, 1490, 1491, false, true);
  g->Binary(ynn_binary_divide, 1491, 7412, 1492);
  g->Unary(ynn_unary_round, 1492, 1493);
  g->Binary(ynn_binary_max, 1493, 7155, 1494);
  g->Binary(ynn_binary_min, 1494, 7270, 1495);
  g->Binary(ynn_binary_multiply, 1495, 7412, 1496);
  g->Reshape(1496, 1497, {1,1,1,256});
  g->Transpose(1497, 1498, {0,2,1,3});
  g->Unary(ynn_unary_square, 1498, 1500);
  g->Reduce(ynn_reduce_sum, 1500, 6330, {3}, true);
  g->ShapeProduct(1500, 6329, {3});
  g->Binary(ynn_binary_divide, 6330, 6329, 1501);
  g->Binary(ynn_binary_add, 1501, 7303, 1502);
  g->Binary(ynn_binary_pow, 1502, 7358, 1503);
  g->Binary(ynn_binary_multiply, 1498, 1503, 1504);
}

// Scope: "Layer11 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(1487, 1505, 0.005907459184527397, 0);
  g->Append(7048, 1505, 8378, 2, s2, slinky::expr(int64_t{1}));
  g->View(8378, 8408, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(8408, 1506, 0.005907459184527397, 0);
  g->Quantize(1504, 1507, 0.047244105488061905, 0);
  g->Append(7063, 1507, 8393, 2, s2, slinky::expr(int64_t{1}));
  g->View(8393, 8423, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(8423, 1509, 0.047244105488061905, 0);
}

// Scope: "Layer11 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Convert(7626, 1510);
  g->Binary(ynn_binary_multiply, 1510, 7627, 1511);
  g->Matmul(1461, 1511, 1513, false, true);
  g->Binary(ynn_binary_divide, 1513, 7448, 1514);
  g->Unary(ynn_unary_round, 1514, 1515);
  g->Binary(ynn_binary_max, 1515, 7155, 1516);
  g->Binary(ynn_binary_min, 1516, 7270, 1517);
  g->Binary(ynn_binary_multiply, 1517, 7448, 1518);
  g->SplitDim(1518, 1519, 2, {8,256});
  g->Transpose(1519, 1520, {0,2,1,3});
  g->Unary(ynn_unary_square, 1520, 1521);
  g->Reduce(ynn_reduce_sum, 1521, 6332, {3}, true);
  g->ShapeProduct(1521, 6331, {3});
  g->Binary(ynn_binary_divide, 6332, 6331, 1522);
  g->Binary(ynn_binary_add, 1522, 7303, 1525);
  g->Binary(ynn_binary_pow, 1525, 7358, 1526);
  g->Binary(ynn_binary_multiply, 1520, 1526, 1527);
  g->Convert(7625, 1528);
  g->Binary(ynn_binary_multiply, 1527, 1528, 1529);
  g->Slice(1529, 1530, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1529, 1531, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1531, 1532);
  g->Concat({1532,1530}, 1533, 3);
  g->Binary(ynn_binary_multiply, 1529, 2025, 1534);
  g->Binary(ynn_binary_multiply, 1533, 3078, 1536);
  g->Binary(ynn_binary_add, 1534, 1536, 1537);
}

// Scope: "Layer11 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(1537, 1506, 1538, false, true);
  g->Mask(1538, 7494, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 7494, 6336, {-1}, true);
  g->Binary(ynn_binary_subtract, 7494, 6336, 6333);
  g->Unary(ynn_unary_exp, 6333, 6334);
  g->Reduce(ynn_reduce_sum, 6334, 6337, {-1}, true);
  g->Binary(ynn_binary_divide, 6113, 6337, 6335);
  g->Binary(ynn_binary_multiply, 6334, 6335, 1539);
  g->Matmul(1539, 1509, 1540, false, false);
}

// Scope: "Layer11 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1540, 1541, {0,2,1,3});
  g->FuseDims(1541, 1542, 2, 2);
  g->Binary(ynn_binary_divide, 1542, 7229, 1543);
  g->Unary(ynn_unary_round, 1543, 1544);
  g->Binary(ynn_binary_max, 1544, 7155, 1546);
  g->Binary(ynn_binary_min, 1546, 7270, 1547);
  g->Binary(ynn_binary_multiply, 1547, 7229, 1548);
  g->Convert(7623, 1549);
  g->Binary(ynn_binary_multiply, 1549, 7624, 1550);
  g->Matmul(1548, 1550, 1551, false, true);
  g->Binary(ynn_binary_divide, 1551, 7284, 1552);
  g->Unary(ynn_unary_round, 1552, 1553);
  g->Binary(ynn_binary_max, 1553, 7155, 1554);
  g->Binary(ynn_binary_min, 1554, 7270, 1555);
  g->Binary(ynn_binary_multiply, 1555, 7284, 1557);
}

// Scope: "Layer11 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1447, 1448);
  g->Reduce(ynn_reduce_sum, 1448, 6326, {2}, true);
  g->ShapeProduct(1448, 6325, {2});
  g->Binary(ynn_binary_divide, 6326, 6325, 1450);
  g->Binary(ynn_binary_add, 1450, 7303, 1451);
  g->Binary(ynn_binary_pow, 1451, 7358, 1452);
  g->Binary(ynn_binary_multiply, 1447, 1452, 1453);
  g->Convert(7604, 1454);
  g->Binary(ynn_binary_multiply, 1453, 1454, 1455);
  BuildLayer11AttentionKvProjection(ctx);
  BuildLayer11AttentionCacheUpdate(ctx);
  BuildLayer11AttentionQueryProjection(ctx);
  BuildLayer11AttentionSdpa(ctx);
  BuildLayer11AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1557, 1558);
  g->Reduce(ynn_reduce_sum, 1558, 6339, {2}, true);
  g->ShapeProduct(1558, 6338, {2});
  g->Binary(ynn_binary_divide, 6339, 6338, 1559);
  g->Binary(ynn_binary_add, 1559, 7303, 1560);
  g->Binary(ynn_binary_pow, 1560, 7358, 1561);
  g->Binary(ynn_binary_multiply, 1557, 1561, 1562);
  g->Convert(7616, 1563);
  g->Binary(ynn_binary_multiply, 1562, 1563, 1564);
  g->Binary(ynn_binary_add, 1447, 1564, 1565);
}

// Scope: "Layer11 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1565, 1566);
  g->Reduce(ynn_reduce_sum, 1566, 6341, {2}, true);
  g->ShapeProduct(1566, 6340, {2});
  g->Binary(ynn_binary_divide, 6341, 6340, 1568);
  g->Binary(ynn_binary_add, 1568, 7303, 1569);
  g->Binary(ynn_binary_pow, 1569, 7358, 1570);
  g->Binary(ynn_binary_multiply, 1565, 1570, 1571);
  g->Convert(7619, 1572);
  g->Binary(ynn_binary_multiply, 1571, 1572, 1573);
  g->Binary(ynn_binary_divide, 1573, 7304, 1574);
  g->Unary(ynn_unary_round, 1574, 1575);
  g->Binary(ynn_binary_max, 1575, 7155, 1576);
  g->Binary(ynn_binary_min, 1576, 7270, 1577);
  g->Binary(ynn_binary_multiply, 1577, 7304, 1579);
  g->Convert(7610, 1580);
  g->Binary(ynn_binary_multiply, 1580, 7611, 1581);
  g->Matmul(1579, 1581, 1582, false, true);
  g->Binary(ynn_binary_divide, 1582, 7424, 1583);
  g->Unary(ynn_unary_round, 1583, 1584);
  g->Binary(ynn_binary_max, 1584, 7155, 1585);
  g->Binary(ynn_binary_min, 1585, 7270, 1586);
  g->Binary(ynn_binary_multiply, 1586, 7424, 1587);
  g->Convert(7608, 1589);
  g->Binary(ynn_binary_multiply, 1589, 7609, 1590);
  g->Matmul(1579, 1590, 1591, false, true);
  g->Binary(ynn_binary_divide, 1591, 7424, 1592);
  g->Unary(ynn_unary_round, 1592, 1593);
  g->Binary(ynn_binary_max, 1593, 7155, 1594);
  g->Binary(ynn_binary_min, 1594, 7270, 1596);
  g->Binary(ynn_binary_multiply, 1596, 7424, 1597);
  g->Polynomial(1597, 6344, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6344, 6345);
  g->Binary(ynn_binary_add, 6345, 6113, 6342);
  g->Binary(ynn_binary_multiply, 1597, 6111, 6343);
  g->Binary(ynn_binary_multiply, 6343, 6342, 1598);
  g->Binary(ynn_binary_multiply, 1587, 1598, 1599);
  g->Binary(ynn_binary_divide, 1599, 7361, 1600);
  g->Unary(ynn_unary_round, 1600, 1601);
  g->Binary(ynn_binary_max, 1601, 7155, 1602);
  g->Binary(ynn_binary_min, 1602, 7270, 1603);
  g->Binary(ynn_binary_multiply, 1603, 7361, 1604);
  g->Convert(7606, 1605);
  g->Binary(ynn_binary_multiply, 1605, 7607, 1607);
  g->Matmul(1604, 1607, 1608, false, true);
  g->Binary(ynn_binary_divide, 1608, 7249, 1609);
  g->Unary(ynn_unary_round, 1609, 1610);
  g->Binary(ynn_binary_max, 1610, 7155, 1611);
  g->Binary(ynn_binary_min, 1611, 7270, 1612);
  g->Binary(ynn_binary_multiply, 1612, 7249, 1613);
  g->Unary(ynn_unary_square, 1613, 1614);
  g->Reduce(ynn_reduce_sum, 1614, 6347, {2}, true);
  g->ShapeProduct(1614, 6346, {2});
  g->Binary(ynn_binary_divide, 6347, 6346, 1615);
  g->Binary(ynn_binary_add, 1615, 7303, 1616);
  g->Binary(ynn_binary_pow, 1616, 7358, 1618);
  g->Binary(ynn_binary_multiply, 1613, 1618, 1619);
  g->Convert(7617, 1620);
  g->Binary(ynn_binary_multiply, 1619, 1620, 1621);
  g->Binary(ynn_binary_add, 1565, 1621, 1622);
}

// Scope: "Layer11 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1022, 1623, {0,0,11,0}, {-1,-1,1,-1});
  g->Reshape(1623, 1624, {1,1,256});
  g->Binary(ynn_binary_add, 1624, 8342, 1625);
  g->Binary(ynn_binary_multiply, 1625, 7085, 1626);
  g->Binary(ynn_binary_divide, 1622, 7174, 1627);
  g->Unary(ynn_unary_round, 1627, 1630);
  g->Binary(ynn_binary_max, 1630, 7155, 1631);
  g->Binary(ynn_binary_min, 1631, 7270, 1632);
  g->Binary(ynn_binary_multiply, 1632, 7174, 1633);
  g->Convert(7612, 1634);
  g->Binary(ynn_binary_multiply, 1634, 7613, 1635);
  g->Matmul(1633, 1635, 1636, false, true);
  g->Binary(ynn_binary_divide, 1636, 7420, 1637);
  g->Unary(ynn_unary_round, 1637, 1638);
  g->Binary(ynn_binary_max, 1638, 7155, 1639);
  g->Binary(ynn_binary_min, 1639, 7270, 1641);
  g->Binary(ynn_binary_multiply, 1641, 7420, 1642);
  g->Polynomial(1642, 6350, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6350, 6351);
  g->Binary(ynn_binary_add, 6351, 6113, 6348);
  g->Binary(ynn_binary_multiply, 1642, 6111, 6349);
  g->Binary(ynn_binary_multiply, 6349, 6348, 1643);
  g->Binary(ynn_binary_multiply, 1643, 1626, 1644);
  g->Binary(ynn_binary_divide, 1644, 7275, 1645);
  g->Unary(ynn_unary_round, 1645, 1646);
  g->Binary(ynn_binary_max, 1646, 7155, 1647);
  g->Binary(ynn_binary_min, 1647, 7270, 1648);
  g->Binary(ynn_binary_multiply, 1648, 7275, 1649);
  g->Convert(7614, 1650);
  g->Binary(ynn_binary_multiply, 1650, 7615, 1652);
  g->Matmul(1649, 1652, 1653, false, true);
  g->Binary(ynn_binary_divide, 1653, 7384, 1654);
  g->Unary(ynn_unary_round, 1654, 1655);
  g->Binary(ynn_binary_max, 1655, 7155, 1656);
  g->Binary(ynn_binary_min, 1656, 7270, 1657);
  g->Binary(ynn_binary_multiply, 1657, 7384, 1658);
  g->Unary(ynn_unary_square, 1658, 1659);
  g->Reduce(ynn_reduce_sum, 1659, 6355, {2}, true);
  g->ShapeProduct(1659, 6354, {2});
  g->Binary(ynn_binary_divide, 6355, 6354, 1660);
  g->Binary(ynn_binary_add, 1660, 7303, 1661);
  g->Binary(ynn_binary_pow, 1661, 7358, 1663);
  g->Binary(ynn_binary_multiply, 1658, 1663, 1664);
  g->Convert(7618, 1665);
  g->Binary(ynn_binary_multiply, 1664, 1665, 1666);
  g->Binary(ynn_binary_add, 1622, 1666, 1667);
  g->Convert(7605, 1668);
  g->Binary(ynn_binary_multiply, 1667, 1668, 1669);
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
  g->Binary(ynn_binary_divide, 1677, 7299, 1678);
  g->Unary(ynn_unary_round, 1678, 1679);
  g->Binary(ynn_binary_max, 1679, 7155, 1680);
  g->Binary(ynn_binary_min, 1680, 7270, 1681);
  g->Binary(ynn_binary_multiply, 1681, 7299, 1682);
  g->Convert(7647, 1683);
  g->Binary(ynn_binary_multiply, 1683, 7648, 1685);
  g->Matmul(1682, 1685, 1686, false, true);
  g->Binary(ynn_binary_divide, 1686, 7233, 1687);
  g->Unary(ynn_unary_round, 1687, 1688);
  g->Binary(ynn_binary_max, 1688, 7155, 1689);
  g->Binary(ynn_binary_min, 1689, 7270, 1690);
  g->Binary(ynn_binary_multiply, 1690, 7233, 1691);
  g->Reshape(1691, 1692, {1,1,1,256});
  g->Transpose(1692, 1693, {0,2,1,3});
  g->Unary(ynn_unary_square, 1693, 1694);
  g->Reduce(ynn_reduce_sum, 1694, 6359, {3}, true);
  g->ShapeProduct(1694, 6358, {3});
  g->Binary(ynn_binary_divide, 6359, 6358, 1696);
  g->Binary(ynn_binary_add, 1696, 7303, 1697);
  g->Binary(ynn_binary_pow, 1697, 7358, 1698);
  g->Binary(ynn_binary_multiply, 1693, 1698, 1699);
  g->Convert(7646, 1700);
  g->Binary(ynn_binary_multiply, 1699, 1700, 1701);
  g->Slice(1701, 1702, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1701, 1703, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1703, 1704);
  g->Concat({1704,1702}, 1705, 3);
  g->Binary(ynn_binary_multiply, 1701, 2025, 1707);
  g->Binary(ynn_binary_multiply, 1705, 3078, 1708);
  g->Binary(ynn_binary_add, 1707, 1708, 1709);
  g->Convert(7654, 1710);
  g->Binary(ynn_binary_multiply, 1710, 7655, 1711);
  g->Matmul(1682, 1711, 1713, false, true);
  g->Binary(ynn_binary_divide, 1713, 7233, 1714);
  g->Unary(ynn_unary_round, 1714, 1715);
  g->Binary(ynn_binary_max, 1715, 7155, 1716);
  g->Binary(ynn_binary_min, 1716, 7270, 1717);
  g->Binary(ynn_binary_multiply, 1717, 7233, 1718);
  g->Reshape(1718, 1719, {1,1,1,256});
  g->Transpose(1719, 1720, {0,2,1,3});
  g->Unary(ynn_unary_square, 1720, 1721);
  g->Reduce(ynn_reduce_sum, 1721, 6361, {3}, true);
  g->ShapeProduct(1721, 6360, {3});
  g->Binary(ynn_binary_divide, 6361, 6360, 1722);
  g->Binary(ynn_binary_add, 1722, 7303, 1724);
  g->Binary(ynn_binary_pow, 1724, 7358, 1725);
  g->Binary(ynn_binary_multiply, 1720, 1725, 1726);
}

// Scope: "Layer12 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(1709, 1727, 0.005788442213088274, 0);
  g->Append(7049, 1727, 8379, 2, s2, slinky::expr(int64_t{1}));
  g->View(8379, 8409, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(8409, 1728, 0.005788442213088274, 0);
  g->Quantize(1726, 1729, 0.047244105488061905, 0);
  g->Append(7064, 1729, 8394, 2, s2, slinky::expr(int64_t{1}));
  g->View(8394, 8424, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(8424, 1732, 0.047244105488061905, 0);
}

// Scope: "Layer12 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Convert(7652, 1733);
  g->Binary(ynn_binary_multiply, 1733, 7653, 1734);
  g->Matmul(1682, 1734, 1735, false, true);
  g->Binary(ynn_binary_divide, 1735, 7200, 1736);
  g->Unary(ynn_unary_round, 1736, 1738);
  g->Binary(ynn_binary_max, 1738, 7155, 1739);
  g->Binary(ynn_binary_min, 1739, 7270, 1740);
  g->Binary(ynn_binary_multiply, 1740, 7200, 1741);
  g->SplitDim(1741, 1742, 2, {8,256});
  g->Transpose(1742, 1743, {0,2,1,3});
  g->Unary(ynn_unary_square, 1743, 1744);
  g->Reduce(ynn_reduce_sum, 1744, 6363, {3}, true);
  g->ShapeProduct(1744, 6362, {3});
  g->Binary(ynn_binary_divide, 6363, 6362, 1745);
  g->Binary(ynn_binary_add, 1745, 7303, 1746);
  g->Binary(ynn_binary_pow, 1746, 7358, 1747);
  g->Binary(ynn_binary_multiply, 1743, 1747, 1749);
  g->Convert(7651, 1750);
  g->Binary(ynn_binary_multiply, 1749, 1750, 1751);
  g->Slice(1751, 1752, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1751, 1753, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1753, 1754);
  g->Concat({1754,1752}, 1755, 3);
  g->Binary(ynn_binary_multiply, 1751, 2025, 1756);
  g->Binary(ynn_binary_multiply, 1755, 3078, 1757);
  g->Binary(ynn_binary_add, 1756, 1757, 1758);
}

// Scope: "Layer12 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(1758, 1728, 1760, false, true);
  g->Mask(1760, 7495, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 7495, 6367, {-1}, true);
  g->Binary(ynn_binary_subtract, 7495, 6367, 6364);
  g->Unary(ynn_unary_exp, 6364, 6365);
  g->Reduce(ynn_reduce_sum, 6365, 6368, {-1}, true);
  g->Binary(ynn_binary_divide, 6113, 6368, 6366);
  g->Binary(ynn_binary_multiply, 6365, 6366, 1761);
  g->Matmul(1761, 1732, 1762, false, false);
}

// Scope: "Layer12 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1762, 1763, {0,2,1,3});
  g->FuseDims(1763, 1764, 2, 2);
  g->Binary(ynn_binary_divide, 1764, 7297, 1765);
  g->Unary(ynn_unary_round, 1765, 1766);
  g->Binary(ynn_binary_max, 1766, 7155, 1767);
  g->Binary(ynn_binary_min, 1767, 7270, 1768);
  g->Binary(ynn_binary_multiply, 1768, 7297, 1770);
  g->Convert(7649, 1771);
  g->Binary(ynn_binary_multiply, 1771, 7650, 1772);
  g->Matmul(1770, 1772, 1773, false, true);
  g->Binary(ynn_binary_divide, 1773, 7409, 1774);
  g->Unary(ynn_unary_round, 1774, 1775);
  g->Binary(ynn_binary_max, 1775, 7155, 1776);
  g->Binary(ynn_binary_min, 1776, 7270, 1777);
  g->Binary(ynn_binary_multiply, 1777, 7409, 1778);
}

// Scope: "Layer12 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1669, 1670);
  g->Reduce(ynn_reduce_sum, 1670, 6357, {2}, true);
  g->ShapeProduct(1670, 6356, {2});
  g->Binary(ynn_binary_divide, 6357, 6356, 1671);
  g->Binary(ynn_binary_add, 1671, 7303, 1672);
  g->Binary(ynn_binary_pow, 1672, 7358, 1674);
  g->Binary(ynn_binary_multiply, 1669, 1674, 1675);
  g->Convert(7630, 1676);
  g->Binary(ynn_binary_multiply, 1675, 1676, 1677);
  BuildLayer12AttentionKvProjection(ctx);
  BuildLayer12AttentionCacheUpdate(ctx);
  BuildLayer12AttentionQueryProjection(ctx);
  BuildLayer12AttentionSdpa(ctx);
  BuildLayer12AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1778, 1779);
  g->Reduce(ynn_reduce_sum, 1779, 6370, {2}, true);
  g->ShapeProduct(1779, 6369, {2});
  g->Binary(ynn_binary_divide, 6370, 6369, 1780);
  g->Binary(ynn_binary_add, 1780, 7303, 1781);
  g->Binary(ynn_binary_pow, 1781, 7358, 1782);
  g->Binary(ynn_binary_multiply, 1778, 1782, 1783);
  g->Convert(7642, 1784);
  g->Binary(ynn_binary_multiply, 1783, 1784, 1785);
  g->Binary(ynn_binary_add, 1669, 1785, 1786);
}

// Scope: "Layer12 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1786, 1787);
  g->Reduce(ynn_reduce_sum, 1787, 6372, {2}, true);
  g->ShapeProduct(1787, 6371, {2});
  g->Binary(ynn_binary_divide, 6372, 6371, 1788);
  g->Binary(ynn_binary_add, 1788, 7303, 1789);
  g->Binary(ynn_binary_pow, 1789, 7358, 1790);
  g->Binary(ynn_binary_multiply, 1786, 1790, 1791);
  g->Convert(7645, 1792);
  g->Binary(ynn_binary_multiply, 1791, 1792, 1793);
  g->Binary(ynn_binary_divide, 1793, 7458, 1794);
  g->Unary(ynn_unary_round, 1794, 1795);
  g->Binary(ynn_binary_max, 1795, 7155, 1796);
  g->Binary(ynn_binary_min, 1796, 7270, 1797);
  g->Binary(ynn_binary_multiply, 1797, 7458, 1798);
  g->Convert(7636, 1799);
  g->Binary(ynn_binary_multiply, 1799, 7637, 1800);
  g->Matmul(1798, 1800, 1801, false, true);
  g->Binary(ynn_binary_divide, 1801, 7486, 1802);
  g->Unary(ynn_unary_round, 1802, 1803);
  g->Binary(ynn_binary_max, 1803, 7155, 1804);
  g->Binary(ynn_binary_min, 1804, 7270, 1805);
  g->Binary(ynn_binary_multiply, 1805, 7486, 1806);
  g->Convert(7634, 1807);
  g->Binary(ynn_binary_multiply, 1807, 7635, 1808);
  g->Matmul(1798, 1808, 1809, false, true);
  g->Binary(ynn_binary_divide, 1809, 7486, 1810);
  g->Unary(ynn_unary_round, 1810, 1811);
  g->Binary(ynn_binary_max, 1811, 7155, 1812);
  g->Binary(ynn_binary_min, 1812, 7270, 1813);
  g->Binary(ynn_binary_multiply, 1813, 7486, 1814);
  g->Polynomial(1814, 6375, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6375, 6376);
  g->Binary(ynn_binary_add, 6376, 6113, 6373);
  g->Binary(ynn_binary_multiply, 1814, 6111, 6374);
  g->Binary(ynn_binary_multiply, 6374, 6373, 1815);
  g->Binary(ynn_binary_multiply, 1806, 1815, 1816);
  g->Binary(ynn_binary_divide, 1816, 7473, 1817);
  g->Unary(ynn_unary_round, 1817, 1818);
  g->Binary(ynn_binary_max, 1818, 7155, 1819);
  g->Binary(ynn_binary_min, 1819, 7270, 1820);
  g->Binary(ynn_binary_multiply, 1820, 7473, 1821);
  g->Convert(7632, 1822);
  g->Binary(ynn_binary_multiply, 1822, 7633, 1823);
  g->Matmul(1821, 1823, 1824, false, true);
  g->Binary(ynn_binary_divide, 1824, 7354, 1827);
  g->Unary(ynn_unary_round, 1827, 1828);
  g->Binary(ynn_binary_max, 1828, 7155, 1829);
  g->Binary(ynn_binary_min, 1829, 7270, 1830);
  g->Binary(ynn_binary_multiply, 1830, 7354, 1831);
  g->Unary(ynn_unary_square, 1831, 1832);
  g->Reduce(ynn_reduce_sum, 1832, 6378, {2}, true);
  g->ShapeProduct(1832, 6377, {2});
  g->Binary(ynn_binary_divide, 6378, 6377, 1833);
  g->Binary(ynn_binary_add, 1833, 7303, 1834);
  g->Binary(ynn_binary_pow, 1834, 7358, 1835);
  g->Binary(ynn_binary_multiply, 1831, 1835, 1836);
  g->Convert(7643, 1838);
  g->Binary(ynn_binary_multiply, 1836, 1838, 1839);
  g->Binary(ynn_binary_add, 1786, 1839, 1840);
}

// Scope: "Layer12 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1022, 1841, {0,0,12,0}, {-1,-1,1,-1});
  g->Reshape(1841, 1842, {1,1,256});
  g->Binary(ynn_binary_add, 1842, 8343, 1843);
  g->Binary(ynn_binary_multiply, 1843, 7085, 1844);
  g->Binary(ynn_binary_divide, 1840, 7484, 1845);
  g->Unary(ynn_unary_round, 1845, 1846);
  g->Binary(ynn_binary_max, 1846, 7155, 1847);
  g->Binary(ynn_binary_min, 1847, 7270, 1849);
  g->Binary(ynn_binary_multiply, 1849, 7484, 1850);
  g->Convert(7638, 1851);
  g->Binary(ynn_binary_multiply, 1851, 7639, 1852);
  g->Matmul(1850, 1852, 1853, false, true);
  g->Binary(ynn_binary_divide, 1853, 7420, 1854);
  g->Unary(ynn_unary_round, 1854, 1855);
  g->Binary(ynn_binary_max, 1855, 7155, 1856);
  g->Binary(ynn_binary_min, 1856, 7270, 1857);
  g->Binary(ynn_binary_multiply, 1857, 7420, 1858);
  g->Polynomial(1858, 6381, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6381, 6382);
  g->Binary(ynn_binary_add, 6382, 6113, 6379);
  g->Binary(ynn_binary_multiply, 1858, 6111, 6380);
  g->Binary(ynn_binary_multiply, 6380, 6379, 1860);
  g->Binary(ynn_binary_multiply, 1860, 1844, 1861);
  g->Binary(ynn_binary_divide, 1861, 7405, 1862);
  g->Unary(ynn_unary_round, 1862, 1863);
  g->Binary(ynn_binary_max, 1863, 7155, 1864);
  g->Binary(ynn_binary_min, 1864, 7270, 1865);
  g->Binary(ynn_binary_multiply, 1865, 7405, 1866);
  g->Convert(7640, 1867);
  g->Binary(ynn_binary_multiply, 1867, 7641, 1868);
  g->Matmul(1866, 1868, 1869, false, true);
  g->Binary(ynn_binary_divide, 1869, 7476, 1871);
  g->Unary(ynn_unary_round, 1871, 1872);
  g->Binary(ynn_binary_max, 1872, 7155, 1873);
  g->Binary(ynn_binary_min, 1873, 7270, 1874);
  g->Binary(ynn_binary_multiply, 1874, 7476, 1875);
  g->Unary(ynn_unary_square, 1875, 1876);
  g->Reduce(ynn_reduce_sum, 1876, 6384, {2}, true);
  g->ShapeProduct(1876, 6383, {2});
  g->Binary(ynn_binary_divide, 6384, 6383, 1877);
  g->Binary(ynn_binary_add, 1877, 7303, 1878);
  g->Binary(ynn_binary_pow, 1878, 7358, 1879);
  g->Binary(ynn_binary_multiply, 1875, 1879, 1880);
  g->Convert(7644, 1882);
  g->Binary(ynn_binary_multiply, 1880, 1882, 1883);
  g->Binary(ynn_binary_add, 1840, 1883, 1884);
  g->Convert(7631, 1885);
  g->Binary(ynn_binary_multiply, 1884, 1885, 1886);
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
  g->Binary(ynn_binary_divide, 1894, 7179, 1895);
  g->Unary(ynn_unary_round, 1895, 1896);
  g->Binary(ynn_binary_max, 1896, 7155, 1897);
  g->Binary(ynn_binary_min, 1897, 7270, 1898);
  g->Binary(ynn_binary_multiply, 1898, 7179, 1899);
  g->Convert(7673, 1900);
  g->Binary(ynn_binary_multiply, 1900, 7674, 1901);
  g->Matmul(1899, 1901, 1902, false, true);
  g->Binary(ynn_binary_divide, 1902, 7281, 1904);
  g->Unary(ynn_unary_round, 1904, 1905);
  g->Binary(ynn_binary_max, 1905, 7155, 1906);
  g->Binary(ynn_binary_min, 1906, 7270, 1907);
  g->Binary(ynn_binary_multiply, 1907, 7281, 1908);
  g->Reshape(1908, 1909, {1,1,1,256});
  g->Transpose(1909, 1910, {0,2,1,3});
  g->Unary(ynn_unary_square, 1910, 1911);
  g->Reduce(ynn_reduce_sum, 1911, 6388, {3}, true);
  g->ShapeProduct(1911, 6387, {3});
  g->Binary(ynn_binary_divide, 6388, 6387, 1912);
  g->Binary(ynn_binary_add, 1912, 7303, 1913);
  g->Binary(ynn_binary_pow, 1913, 7358, 1915);
  g->Binary(ynn_binary_multiply, 1910, 1915, 1916);
  g->Convert(7672, 1917);
  g->Binary(ynn_binary_multiply, 1916, 1917, 1918);
  g->Slice(1918, 1919, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1918, 1920, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1920, 1921);
  g->Concat({1921,1919}, 1922, 3);
  g->Binary(ynn_binary_multiply, 1918, 2025, 1923);
  g->Binary(ynn_binary_multiply, 1922, 3078, 1924);
  g->Binary(ynn_binary_add, 1923, 1924, 1926);
  g->Convert(7680, 1927);
  g->Binary(ynn_binary_multiply, 1927, 7681, 1928);
  g->Matmul(1899, 1928, 1929, false, true);
  g->Binary(ynn_binary_divide, 1929, 7281, 1930);
  g->Unary(ynn_unary_round, 1930, 1933);
  g->Binary(ynn_binary_max, 1933, 7155, 1934);
  g->Binary(ynn_binary_min, 1934, 7270, 1935);
  g->Binary(ynn_binary_multiply, 1935, 7281, 1936);
  g->Reshape(1936, 1937, {1,1,1,256});
  g->Transpose(1937, 1938, {0,2,1,3});
  g->Unary(ynn_unary_square, 1938, 1939);
  g->Reduce(ynn_reduce_sum, 1939, 6390, {3}, true);
  g->ShapeProduct(1939, 6389, {3});
  g->Binary(ynn_binary_divide, 6390, 6389, 1940);
  g->Binary(ynn_binary_add, 1940, 7303, 1941);
  g->Binary(ynn_binary_pow, 1941, 7358, 1942);
  g->Binary(ynn_binary_multiply, 1938, 1942, 1944);
}

// Scope: "Layer13 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(1926, 1945, 0.0059552486054599285, 0);
  g->Append(7050, 1945, 8380, 2, s2, slinky::expr(int64_t{1}));
  g->View(8380, 8410, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(8410, 1946, 0.0059552486054599285, 0);
  g->Quantize(1944, 1947, 0.047244105488061905, 0);
  g->Append(7065, 1947, 8395, 2, s2, slinky::expr(int64_t{1}));
  g->View(8395, 8425, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(8425, 1948, 0.047244105488061905, 0);
}

// Scope: "Layer13 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Convert(7678, 1950);
  g->Binary(ynn_binary_multiply, 1950, 7679, 1951);
  g->Matmul(1899, 1951, 1952, false, true);
  g->Binary(ynn_binary_divide, 1952, 7248, 1953);
  g->Unary(ynn_unary_round, 1953, 1954);
  g->Binary(ynn_binary_max, 1954, 7155, 1955);
  g->Binary(ynn_binary_min, 1955, 7270, 1957);
  g->Binary(ynn_binary_multiply, 1957, 7248, 1958);
  g->SplitDim(1958, 1959, 2, {8,256});
  g->Transpose(1959, 1960, {0,2,1,3});
  g->Unary(ynn_unary_square, 1960, 1961);
  g->Reduce(ynn_reduce_sum, 1961, 6394, {3}, true);
  g->ShapeProduct(1961, 6393, {3});
  g->Binary(ynn_binary_divide, 6394, 6393, 1962);
  g->Binary(ynn_binary_add, 1962, 7303, 1963);
  g->Binary(ynn_binary_pow, 1963, 7358, 1964);
  g->Binary(ynn_binary_multiply, 1960, 1964, 1965);
  g->Convert(7677, 1966);
  g->Binary(ynn_binary_multiply, 1965, 1966, 1968);
  g->Slice(1968, 1969, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1968, 1970, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1970, 1971);
  g->Concat({1971,1969}, 1972, 3);
  g->Binary(ynn_binary_multiply, 1968, 2025, 1973);
  g->Binary(ynn_binary_multiply, 1972, 3078, 1974);
  g->Binary(ynn_binary_add, 1973, 1974, 1975);
}

// Scope: "Layer13 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(1975, 1946, 1976, false, true);
  g->Mask(1976, 7496, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 7496, 6398, {-1}, true);
  g->Binary(ynn_binary_subtract, 7496, 6398, 6395);
  g->Unary(ynn_unary_exp, 6395, 6396);
  g->Reduce(ynn_reduce_sum, 6396, 6399, {-1}, true);
  g->Binary(ynn_binary_divide, 6113, 6399, 6397);
  g->Binary(ynn_binary_multiply, 6396, 6397, 1978);
  g->Matmul(1978, 1948, 1979, false, false);
}

// Scope: "Layer13 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1979, 1980, {0,2,1,3});
  g->FuseDims(1980, 1981, 2, 2);
  g->Binary(ynn_binary_divide, 1981, 7175, 1982);
  g->Unary(ynn_unary_round, 1982, 1983);
  g->Binary(ynn_binary_max, 1983, 7155, 1984);
  g->Binary(ynn_binary_min, 1984, 7270, 1985);
  g->Binary(ynn_binary_multiply, 1985, 7175, 1986);
  g->Convert(7675, 1987);
  g->Binary(ynn_binary_multiply, 1987, 7676, 1988);
  g->Matmul(1986, 1988, 1989, false, true);
  g->Binary(ynn_binary_divide, 1989, 7086, 1990);
  g->Unary(ynn_unary_round, 1990, 1991);
  g->Binary(ynn_binary_max, 1991, 7155, 1992);
  g->Binary(ynn_binary_min, 1992, 7270, 1993);
  g->Binary(ynn_binary_multiply, 1993, 7086, 1994);
}

// Scope: "Layer13 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1886, 1887);
  g->Reduce(ynn_reduce_sum, 1887, 6386, {2}, true);
  g->ShapeProduct(1887, 6385, {2});
  g->Binary(ynn_binary_divide, 6386, 6385, 1888);
  g->Binary(ynn_binary_add, 1888, 7303, 1889);
  g->Binary(ynn_binary_pow, 1889, 7358, 1890);
  g->Binary(ynn_binary_multiply, 1886, 1890, 1891);
  g->Convert(7656, 1893);
  g->Binary(ynn_binary_multiply, 1891, 1893, 1894);
  BuildLayer13AttentionKvProjection(ctx);
  BuildLayer13AttentionCacheUpdate(ctx);
  BuildLayer13AttentionQueryProjection(ctx);
  BuildLayer13AttentionSdpa(ctx);
  BuildLayer13AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1994, 1995);
  g->Reduce(ynn_reduce_sum, 1995, 6401, {2}, true);
  g->ShapeProduct(1995, 6400, {2});
  g->Binary(ynn_binary_divide, 6401, 6400, 1996);
  g->Binary(ynn_binary_add, 1996, 7303, 1997);
  g->Binary(ynn_binary_pow, 1997, 7358, 1998);
  g->Binary(ynn_binary_multiply, 1994, 1998, 1999);
  g->Convert(7668, 2000);
  g->Binary(ynn_binary_multiply, 1999, 2000, 2001);
  g->Binary(ynn_binary_add, 1886, 2001, 2002);
}

// Scope: "Layer13 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2002, 2003);
  g->Reduce(ynn_reduce_sum, 2003, 6403, {2}, true);
  g->ShapeProduct(2003, 6402, {2});
  g->Binary(ynn_binary_divide, 6403, 6402, 2004);
  g->Binary(ynn_binary_add, 2004, 7303, 2005);
  g->Binary(ynn_binary_pow, 2005, 7358, 2006);
  g->Binary(ynn_binary_multiply, 2002, 2006, 2007);
  g->Convert(7671, 2009);
  g->Binary(ynn_binary_multiply, 2007, 2009, 2010);
  g->Binary(ynn_binary_divide, 2010, 7288, 2011);
  g->Unary(ynn_unary_round, 2011, 2012);
  g->Binary(ynn_binary_max, 2012, 7155, 2013);
  g->Binary(ynn_binary_min, 2013, 7270, 2014);
  g->Binary(ynn_binary_multiply, 2014, 7288, 2015);
  g->Convert(7662, 2016);
  g->Binary(ynn_binary_multiply, 2016, 7663, 2017);
  g->Matmul(2015, 2017, 2018, false, true);
  g->Binary(ynn_binary_divide, 2018, 7339, 2020);
  g->Unary(ynn_unary_round, 2020, 2021);
  g->Binary(ynn_binary_max, 2021, 7155, 2022);
  g->Binary(ynn_binary_min, 2022, 7270, 2023);
  g->Binary(ynn_binary_multiply, 2023, 7339, 2024);
  g->Convert(7660, 2027);
  g->Binary(ynn_binary_multiply, 2027, 7661, 2028);
  g->Matmul(2015, 2028, 2029, false, true);
  g->Binary(ynn_binary_divide, 2029, 7339, 2030);
  g->Unary(ynn_unary_round, 2030, 2031);
  g->Binary(ynn_binary_max, 2031, 7155, 2032);
  g->Binary(ynn_binary_min, 2032, 7270, 2033);
  g->Binary(ynn_binary_multiply, 2033, 7339, 2034);
  g->Polynomial(2034, 6406, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6406, 6407);
  g->Binary(ynn_binary_add, 6407, 6113, 6404);
  g->Binary(ynn_binary_multiply, 2034, 6111, 6405);
  g->Binary(ynn_binary_multiply, 6405, 6404, 2035);
  g->Binary(ynn_binary_multiply, 2024, 2035, 2036);
  g->Binary(ynn_binary_divide, 2036, 7196, 2037);
  g->Unary(ynn_unary_round, 2037, 2038);
  g->Binary(ynn_binary_max, 2038, 7155, 2039);
  g->Binary(ynn_binary_min, 2039, 7270, 2040);
  g->Binary(ynn_binary_multiply, 2040, 7196, 2041);
  g->Convert(7658, 2042);
  g->Binary(ynn_binary_multiply, 2042, 7659, 2043);
  g->Matmul(2041, 2043, 2044, false, true);
  g->Binary(ynn_binary_divide, 2044, 7456, 2045);
  g->Unary(ynn_unary_round, 2045, 2046);
  g->Binary(ynn_binary_max, 2046, 7155, 2048);
  g->Binary(ynn_binary_min, 2048, 7270, 2049);
  g->Binary(ynn_binary_multiply, 2049, 7456, 2050);
  g->Unary(ynn_unary_square, 2050, 2051);
  g->Reduce(ynn_reduce_sum, 2051, 6409, {2}, true);
  g->ShapeProduct(2051, 6408, {2});
  g->Binary(ynn_binary_divide, 6409, 6408, 2052);
  g->Binary(ynn_binary_add, 2052, 7303, 2053);
  g->Binary(ynn_binary_pow, 2053, 7358, 2054);
  g->Binary(ynn_binary_multiply, 2050, 2054, 2055);
  g->Convert(7669, 2056);
  g->Binary(ynn_binary_multiply, 2055, 2056, 2057);
  g->Binary(ynn_binary_add, 2002, 2057, 2058);
}

// Scope: "Layer13 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1022, 2059, {0,0,13,0}, {-1,-1,1,-1});
  g->Reshape(2059, 2060, {1,1,256});
  g->Binary(ynn_binary_add, 2060, 8344, 2061);
  g->Binary(ynn_binary_multiply, 2061, 7085, 2062);
  g->Binary(ynn_binary_divide, 2058, 7208, 2063);
  g->Unary(ynn_unary_round, 2063, 2064);
  g->Binary(ynn_binary_max, 2064, 7155, 2065);
  g->Binary(ynn_binary_min, 2065, 7270, 2066);
  g->Binary(ynn_binary_multiply, 2066, 7208, 2067);
  g->Convert(7664, 2068);
  g->Binary(ynn_binary_multiply, 2068, 7665, 2069);
  g->Matmul(2067, 2069, 2070, false, true);
  g->Binary(ynn_binary_divide, 2070, 7390, 2071);
  g->Unary(ynn_unary_round, 2071, 2072);
  g->Binary(ynn_binary_max, 2072, 7155, 2073);
  g->Binary(ynn_binary_min, 2073, 7270, 2074);
  g->Binary(ynn_binary_multiply, 2074, 7390, 2075);
  g->Polynomial(2075, 6412, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6412, 6413);
  g->Binary(ynn_binary_add, 6413, 6113, 6410);
  g->Binary(ynn_binary_multiply, 2075, 6111, 6411);
  g->Binary(ynn_binary_multiply, 6411, 6410, 2076);
  g->Binary(ynn_binary_multiply, 2076, 2062, 2077);
  g->Binary(ynn_binary_divide, 2077, 7121, 2078);
  g->Unary(ynn_unary_round, 2078, 2079);
  g->Binary(ynn_binary_max, 2079, 7155, 2080);
  g->Binary(ynn_binary_min, 2080, 7270, 2081);
  g->Binary(ynn_binary_multiply, 2081, 7121, 2082);
  g->Convert(7666, 2083);
  g->Binary(ynn_binary_multiply, 2083, 7667, 2084);
  g->Matmul(2082, 2084, 2085, false, true);
  g->Binary(ynn_binary_divide, 2085, 7340, 2086);
  g->Unary(ynn_unary_round, 2086, 2087);
  g->Binary(ynn_binary_max, 2087, 7155, 2088);
  g->Binary(ynn_binary_min, 2088, 7270, 2089);
  g->Binary(ynn_binary_multiply, 2089, 7340, 2090);
  g->Unary(ynn_unary_square, 2090, 2091);
  g->Reduce(ynn_reduce_sum, 2091, 6415, {2}, true);
  g->ShapeProduct(2091, 6414, {2});
  g->Binary(ynn_binary_divide, 6415, 6414, 2092);
  g->Binary(ynn_binary_add, 2092, 7303, 2093);
  g->Binary(ynn_binary_pow, 2093, 7358, 2094);
  g->Binary(ynn_binary_multiply, 2090, 2094, 2095);
  g->Convert(7670, 2096);
  g->Binary(ynn_binary_multiply, 2095, 2096, 2097);
  g->Binary(ynn_binary_add, 2058, 2097, 2098);
  g->Convert(7657, 2099);
  g->Binary(ynn_binary_multiply, 2098, 2099, 2100);
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
  g->Binary(ynn_binary_divide, 2107, 7106, 2109);
  g->Unary(ynn_unary_round, 2109, 2110);
  g->Binary(ynn_binary_max, 2110, 7155, 2111);
  g->Binary(ynn_binary_min, 2111, 7270, 2112);
  g->Binary(ynn_binary_multiply, 2112, 7106, 2113);
  g->Convert(7699, 2114);
  g->Binary(ynn_binary_multiply, 2114, 7700, 2115);
  g->Matmul(2113, 2115, 2116, false, true);
  g->Binary(ynn_binary_divide, 2116, 7402, 2117);
  g->Unary(ynn_unary_round, 2117, 2118);
  g->Binary(ynn_binary_max, 2118, 7155, 2120);
  g->Binary(ynn_binary_min, 2120, 7270, 2121);
  g->Binary(ynn_binary_multiply, 2121, 7402, 2122);
  g->Reshape(2122, 2123, {1,1,1,512});
  g->Transpose(2123, 2124, {0,2,1,3});
  g->Unary(ynn_unary_square, 2124, 2125);
  g->Reduce(ynn_reduce_sum, 2125, 6419, {3}, true);
  g->ShapeProduct(2125, 6418, {3});
  g->Binary(ynn_binary_divide, 6419, 6418, 2126);
  g->Binary(ynn_binary_add, 2126, 7303, 2127);
  g->Binary(ynn_binary_pow, 2127, 7358, 2128);
  g->Binary(ynn_binary_multiply, 2124, 2128, 2129);
  g->Convert(7698, 2132);
  g->Binary(ynn_binary_multiply, 2129, 2132, 2133);
  g->Slice(2133, 2134, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(2133, 2135, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 2135, 2136);
  g->Concat({2136,2134}, 2137, 3);
  g->Binary(ynn_binary_multiply, 2133, 5909, 2138);
  g->Binary(ynn_binary_multiply, 2137, 6008, 2139);
  g->Binary(ynn_binary_add, 2138, 2139, 2140);
  g->Convert(7706, 2142);
  g->Binary(ynn_binary_multiply, 2142, 7707, 2143);
  g->Matmul(2113, 2143, 2144, false, true);
  g->Binary(ynn_binary_divide, 2144, 7402, 2145);
  g->Unary(ynn_unary_round, 2145, 2146);
  g->Binary(ynn_binary_max, 2146, 7155, 2147);
  g->Binary(ynn_binary_min, 2147, 7270, 2149);
  g->Binary(ynn_binary_multiply, 2149, 7402, 2150);
  g->Reshape(2150, 2151, {1,1,1,512});
  g->Transpose(2151, 2152, {0,2,1,3});
  g->Unary(ynn_unary_square, 2152, 2153);
  g->Reduce(ynn_reduce_sum, 2153, 6421, {3}, true);
  g->ShapeProduct(2153, 6420, {3});
  g->Binary(ynn_binary_divide, 6421, 6420, 2154);
  g->Binary(ynn_binary_add, 2154, 7303, 2155);
  g->Binary(ynn_binary_pow, 2155, 7358, 2156);
  g->Binary(ynn_binary_multiply, 2152, 2156, 2157);
}

// Scope: "Layer14 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(2140, 2158, 0.001091228099539876, 0);
  g->Append(7051, 2158, 8381, 2, s2, slinky::expr(int64_t{1}));
  g->View(8381, 8411, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(8411, 2160, 0.001091228099539876, 0);
  g->Quantize(2157, 2161, 0.01785714365541935, 0);
  g->Append(7066, 2161, 8396, 2, s2, slinky::expr(int64_t{1}));
  g->View(8396, 8426, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(8426, 2162, 0.01785714365541935, 0);
}

// Scope: "Layer14 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Convert(7704, 2164);
  g->Binary(ynn_binary_multiply, 2164, 7705, 2165);
  g->Matmul(2113, 2165, 2166, false, true);
  g->Binary(ynn_binary_divide, 2166, 7291, 2167);
  g->Unary(ynn_unary_round, 2167, 2168);
  g->Binary(ynn_binary_max, 2168, 7155, 2169);
  g->Binary(ynn_binary_min, 2169, 7270, 2170);
  g->Binary(ynn_binary_multiply, 2170, 7291, 2171);
  g->SplitDim(2171, 2173, 2, {8,512});
  g->Transpose(2173, 2174, {0,2,1,3});
  g->Unary(ynn_unary_square, 2174, 2175);
  g->Reduce(ynn_reduce_sum, 2175, 6423, {3}, true);
  g->ShapeProduct(2175, 6422, {3});
  g->Binary(ynn_binary_divide, 6423, 6422, 2176);
  g->Binary(ynn_binary_add, 2176, 7303, 2177);
  g->Binary(ynn_binary_pow, 2177, 7358, 2178);
  g->Binary(ynn_binary_multiply, 2174, 2178, 2179);
  g->Convert(7703, 2180);
  g->Binary(ynn_binary_multiply, 2179, 2180, 2181);
  g->Slice(2181, 2182, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(2181, 2184, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 2184, 2185);
  g->Concat({2185,2182}, 2186, 3);
  g->Binary(ynn_binary_multiply, 2181, 5909, 2187);
  g->Binary(ynn_binary_multiply, 2186, 6008, 2188);
  g->Binary(ynn_binary_add, 2187, 2188, 2189);
}

// Scope: "Layer14 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(2189, 2160, 2190, false, true);
  g->Mask(2190, 7497, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 7497, 6427, {-1}, true);
  g->Binary(ynn_binary_subtract, 7497, 6427, 6424);
  g->Unary(ynn_unary_exp, 6424, 6425);
  g->Reduce(ynn_reduce_sum, 6425, 6428, {-1}, true);
  g->Binary(ynn_binary_divide, 6113, 6428, 6426);
  g->Binary(ynn_binary_multiply, 6425, 6426, 2191);
  g->Matmul(2191, 2162, 2192, false, false);
}

// Scope: "Layer14 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(2192, 2194, {0,2,1,3});
  g->FuseDims(2194, 2195, 2, 2);
  g->Binary(ynn_binary_divide, 2195, 7245, 2196);
  g->Unary(ynn_unary_round, 2196, 2197);
  g->Binary(ynn_binary_max, 2197, 7155, 2198);
  g->Binary(ynn_binary_min, 2198, 7270, 2199);
  g->Binary(ynn_binary_multiply, 2199, 7245, 2200);
  g->Convert(7701, 2201);
  g->Binary(ynn_binary_multiply, 2201, 7702, 2202);
  g->Matmul(2200, 2202, 2203, false, true);
  g->Binary(ynn_binary_divide, 2203, 7413, 2205);
  g->Unary(ynn_unary_round, 2205, 2206);
  g->Binary(ynn_binary_max, 2206, 7155, 2207);
  g->Binary(ynn_binary_min, 2207, 7270, 2208);
  g->Binary(ynn_binary_multiply, 2208, 7413, 2209);
}

// Scope: "Layer14 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2100, 2101);
  g->Reduce(ynn_reduce_sum, 2101, 6417, {2}, true);
  g->ShapeProduct(2101, 6416, {2});
  g->Binary(ynn_binary_divide, 6417, 6416, 2102);
  g->Binary(ynn_binary_add, 2102, 7303, 2103);
  g->Binary(ynn_binary_pow, 2103, 7358, 2104);
  g->Binary(ynn_binary_multiply, 2100, 2104, 2105);
  g->Convert(7682, 2106);
  g->Binary(ynn_binary_multiply, 2105, 2106, 2107);
  BuildLayer14AttentionKvProjection(ctx);
  BuildLayer14AttentionCacheUpdate(ctx);
  BuildLayer14AttentionQueryProjection(ctx);
  BuildLayer14AttentionSdpa(ctx);
  BuildLayer14AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2209, 2210);
  g->Reduce(ynn_reduce_sum, 2210, 6430, {2}, true);
  g->ShapeProduct(2210, 6429, {2});
  g->Binary(ynn_binary_divide, 6430, 6429, 2211);
  g->Binary(ynn_binary_add, 2211, 7303, 2212);
  g->Binary(ynn_binary_pow, 2212, 7358, 2213);
  g->Binary(ynn_binary_multiply, 2209, 2213, 2214);
  g->Convert(7694, 2216);
  g->Binary(ynn_binary_multiply, 2214, 2216, 2217);
  g->Binary(ynn_binary_add, 2100, 2217, 2218);
}

// Scope: "Layer14 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2218, 2219);
  g->Reduce(ynn_reduce_sum, 2219, 6434, {2}, true);
  g->ShapeProduct(2219, 6433, {2});
  g->Binary(ynn_binary_divide, 6434, 6433, 2220);
  g->Binary(ynn_binary_add, 2220, 7303, 2221);
  g->Binary(ynn_binary_pow, 2221, 7358, 2222);
  g->Binary(ynn_binary_multiply, 2218, 2222, 2223);
  g->Convert(7697, 2224);
  g->Binary(ynn_binary_multiply, 2223, 2224, 2225);
  g->Binary(ynn_binary_divide, 2225, 7239, 2228);
  g->Unary(ynn_unary_round, 2228, 2229);
  g->Binary(ynn_binary_max, 2229, 7155, 2230);
  g->Binary(ynn_binary_min, 2230, 7270, 2231);
  g->Binary(ynn_binary_multiply, 2231, 7239, 2232);
  g->Convert(7688, 2233);
  g->Binary(ynn_binary_multiply, 2233, 7689, 2234);
  g->Matmul(2232, 2234, 2235, false, true);
  g->Binary(ynn_binary_divide, 2235, 7347, 2236);
  g->Unary(ynn_unary_round, 2236, 2237);
  g->Binary(ynn_binary_max, 2237, 7155, 2239);
  g->Binary(ynn_binary_min, 2239, 7270, 2240);
  g->Binary(ynn_binary_multiply, 2240, 7347, 2241);
  g->Convert(7686, 2242);
  g->Binary(ynn_binary_multiply, 2242, 7687, 2243);
  g->Matmul(2232, 2243, 2245, false, true);
  g->Binary(ynn_binary_divide, 2245, 7347, 2246);
  g->Unary(ynn_unary_round, 2246, 2247);
  g->Binary(ynn_binary_max, 2247, 7155, 2248);
  g->Binary(ynn_binary_min, 2248, 7270, 2249);
  g->Binary(ynn_binary_multiply, 2249, 7347, 2250);
  g->Polynomial(2250, 6437, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6437, 6438);
  g->Binary(ynn_binary_add, 6438, 6113, 6435);
  g->Binary(ynn_binary_multiply, 2250, 6111, 6436);
  g->Binary(ynn_binary_multiply, 6436, 6435, 2251);
  g->Binary(ynn_binary_multiply, 2241, 2251, 2252);
  g->Binary(ynn_binary_divide, 2252, 7266, 2253);
  g->Unary(ynn_unary_round, 2253, 2254);
  g->Binary(ynn_binary_max, 2254, 7155, 2256);
  g->Binary(ynn_binary_min, 2256, 7270, 2257);
  g->Binary(ynn_binary_multiply, 2257, 7266, 2258);
  g->Convert(7684, 2259);
  g->Binary(ynn_binary_multiply, 2259, 7685, 2260);
  g->Matmul(2258, 2260, 2261, false, true);
  g->Binary(ynn_binary_divide, 2261, 7141, 2262);
  g->Unary(ynn_unary_round, 2262, 2263);
  g->Binary(ynn_binary_max, 2263, 7155, 2264);
  g->Binary(ynn_binary_min, 2264, 7270, 2265);
  g->Binary(ynn_binary_multiply, 2265, 7141, 2267);
  g->Unary(ynn_unary_square, 2267, 2268);
  g->Reduce(ynn_reduce_sum, 2268, 6440, {2}, true);
  g->ShapeProduct(2268, 6439, {2});
  g->Binary(ynn_binary_divide, 6440, 6439, 2269);
  g->Binary(ynn_binary_add, 2269, 7303, 2270);
  g->Binary(ynn_binary_pow, 2270, 7358, 2271);
  g->Binary(ynn_binary_multiply, 2267, 2271, 2272);
  g->Convert(7695, 2273);
  g->Binary(ynn_binary_multiply, 2272, 2273, 2274);
  g->Binary(ynn_binary_add, 2218, 2274, 2275);
}

// Scope: "Layer14 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1022, 2276, {0,0,14,0}, {-1,-1,1,-1});
  g->Reshape(2276, 2278, {1,1,256});
  g->Binary(ynn_binary_add, 2278, 8345, 2279);
  g->Binary(ynn_binary_multiply, 2279, 7085, 2280);
  g->Binary(ynn_binary_divide, 2275, 7469, 2281);
  g->Unary(ynn_unary_round, 2281, 2282);
  g->Binary(ynn_binary_max, 2282, 7155, 2283);
  g->Binary(ynn_binary_min, 2283, 7270, 2284);
  g->Binary(ynn_binary_multiply, 2284, 7469, 2285);
  g->Convert(7690, 2286);
  g->Binary(ynn_binary_multiply, 2286, 7691, 2287);
  g->Matmul(2285, 2287, 2289, false, true);
  g->Binary(ynn_binary_divide, 2289, 7369, 2290);
  g->Unary(ynn_unary_round, 2290, 2291);
  g->Binary(ynn_binary_max, 2291, 7155, 2292);
  g->Binary(ynn_binary_min, 2292, 7270, 2293);
  g->Binary(ynn_binary_multiply, 2293, 7369, 2294);
  g->Polynomial(2294, 6443, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6443, 6444);
  g->Binary(ynn_binary_add, 6444, 6113, 6441);
  g->Binary(ynn_binary_multiply, 2294, 6111, 6442);
  g->Binary(ynn_binary_multiply, 6442, 6441, 2295);
  g->Binary(ynn_binary_multiply, 2295, 2280, 2296);
  g->Binary(ynn_binary_divide, 2296, 7241, 2297);
  g->Unary(ynn_unary_round, 2297, 2298);
  g->Binary(ynn_binary_max, 2298, 7155, 2300);
  g->Binary(ynn_binary_min, 2300, 7270, 2301);
  g->Binary(ynn_binary_multiply, 2301, 7241, 2302);
  g->Convert(7692, 2303);
  g->Binary(ynn_binary_multiply, 2303, 7693, 2304);
  g->Matmul(2302, 2304, 2305, false, true);
  g->Binary(ynn_binary_divide, 2305, 7410, 2306);
  g->Unary(ynn_unary_round, 2306, 2307);
  g->Binary(ynn_binary_max, 2307, 7155, 2308);
  g->Binary(ynn_binary_min, 2308, 7270, 2309);
  g->Binary(ynn_binary_multiply, 2309, 7410, 2311);
  g->Unary(ynn_unary_square, 2311, 2312);
  g->Reduce(ynn_reduce_sum, 2312, 6446, {2}, true);
  g->ShapeProduct(2312, 6445, {2});
  g->Binary(ynn_binary_divide, 6446, 6445, 2313);
  g->Binary(ynn_binary_add, 2313, 7303, 2314);
  g->Binary(ynn_binary_pow, 2314, 7358, 2315);
  g->Binary(ynn_binary_multiply, 2311, 2315, 2316);
  g->Convert(7696, 2317);
  g->Binary(ynn_binary_multiply, 2316, 2317, 2318);
  g->Binary(ynn_binary_add, 2275, 2318, 2319);
  g->Convert(7683, 2320);
  g->Binary(ynn_binary_multiply, 2319, 2320, 2322);
}

// Scope: "Layer14"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14(Context& ctx) {
  BuildLayer14Attention(ctx);
  BuildLayer14Mlp(ctx);
  BuildLayer14PerLayerEmbedding(ctx);
}

}  // namespace BuildGemma4DecodeSource
