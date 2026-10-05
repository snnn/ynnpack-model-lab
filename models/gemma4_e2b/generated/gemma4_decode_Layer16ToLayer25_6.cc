// Generated YNNPACK builder; do not edit.
#include "gemma4_decode_builder.h"

namespace BuildGemma4DecodeSource {

// Scope: "Layer16 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(1086, 1087, 0.44548678398132324, 0);
  g->Transpose(6727, 4222, {1,0});
  g->Binary(ynn_binary_multiply, 4219, 4221, 4217);
  g->Dot(1087, 4222, YNN_INVALID_VALUE_ID, 4216, 1);
  g->DequantizeTensor(4216, YNN_INVALID_VALUE_ID, 4217, 4218);
  g->QuantizeTensor(4218, 6504, 4220, 1089);
  g->Dequantize(1089, 1090, 0.3641732335090637, 0);
  g->SplitDim(1090, 1091, 2, {8,256});
  g->FuseDims(1091, 1093, 1, 2);
  g->SplitDim(1093, 1092, 1, {8,1});
  g->Unary(ynn_unary_square, 1092, 1094);
  g->Reduce(ynn_reduce_sum, 1094, 5776, {3}, true);
  g->ShapeProduct(1094, 5775, {3});
  g->Binary(ynn_binary_divide, 5776, 5775, 1095);
  g->Binary(ynn_binary_add, 1095, 6539, 1096);
  g->Unary(ynn_unary_rsqrt, 1096, 1097);
  g->Binary(ynn_binary_multiply, 1092, 1097, 1098);
  g->Binary(ynn_binary_multiply, 1098, 6726, 1099);
  g->Slice(1099, 1100, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1099, 1101, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1101, 1102);
  g->Concat({1102,1100}, 1103, 3);
  g->Binary(ynn_binary_multiply, 1099, 3067, 1104);
  g->Binary(ynn_binary_multiply, 1103, 3172, 1105);
  g->Binary(ynn_binary_add, 1104, 1105, 1106);
}

// Scope: "Layer16 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7190, 1107, 0.0059552486054599285, 0);
  g->Dequantize(7205, 1108, 0.047244105488061905, 0);
  g->Matmul(1106, 1107, 1109, false, true);
  g->Mask(1109, 6553, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6553, 5785, {-1}, true);
  g->Binary(ynn_binary_subtract, 6553, 5785, 5782);
  g->Unary(ynn_unary_exp, 5782, 5783);
  g->Reduce(ynn_reduce_sum, 5783, 5786, {-1}, true);
  g->Binary(ynn_binary_divide, 5500, 5786, 5784);
  g->Binary(ynn_binary_multiply, 5783, 5784, 1111);
  g->Matmul(1111, 1108, 1112, false, false);
}

// Scope: "Layer16 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(1112, 1114, 1, 2);
  g->SplitDim(1114, 1113, 1, {1,8});
  g->FuseDims(1113, 1115, 2, 2);
  g->Quantize(1115, 1116, 0.023745087906718254, 0);
  g->Transpose(6725, 4229, {1,0});
  g->Binary(ynn_binary_multiply, 4226, 4228, 4224);
  g->Dot(1116, 4229, YNN_INVALID_VALUE_ID, 4223, 1);
  g->DequantizeTensor(4223, YNN_INVALID_VALUE_ID, 4224, 4225);
  g->QuantizeTensor(4225, 6504, 4227, 1117);
  g->Dequantize(1117, 1118, 0.02639034017920494, 0);
}

// Scope: "Layer16 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1080, 1081);
  g->Reduce(ynn_reduce_sum, 1081, 5774, {2}, true);
  g->ShapeProduct(1081, 5773, {2});
  g->Binary(ynn_binary_divide, 5774, 5773, 1082);
  g->Binary(ynn_binary_add, 1082, 6539, 1083);
  g->Unary(ynn_unary_rsqrt, 1083, 1084);
  g->Binary(ynn_binary_multiply, 1080, 1084, 1085);
  g->Binary(ynn_binary_multiply, 1085, 6714, 1086);
  BuildLayer16AttentionQueryProjection(ctx);
  BuildLayer16AttentionSdpa(ctx);
  BuildLayer16AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1118, 1119);
  g->Reduce(ynn_reduce_sum, 1119, 5788, {2}, true);
  g->ShapeProduct(1119, 5787, {2});
  g->Binary(ynn_binary_divide, 5788, 5787, 1120);
  g->Binary(ynn_binary_add, 1120, 6539, 1122);
  g->Unary(ynn_unary_rsqrt, 1122, 1123);
  g->Binary(ynn_binary_multiply, 1118, 1123, 1124);
  g->Binary(ynn_binary_multiply, 1124, 6721, 1125);
  g->Binary(ynn_binary_add, 1125, 1080, 1126);
}

// Scope: "Layer16 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1126, 1127);
  g->Reduce(ynn_reduce_sum, 1127, 5790, {2}, true);
  g->ShapeProduct(1127, 5789, {2});
  g->Binary(ynn_binary_divide, 5790, 5789, 1128);
  g->Binary(ynn_binary_add, 1128, 6539, 1129);
  g->Unary(ynn_unary_rsqrt, 1129, 1130);
  g->Binary(ynn_binary_multiply, 1126, 1130, 1131);
  g->Binary(ynn_binary_multiply, 1131, 6724, 1134);
  g->Quantize(1134, 1135, 0.019740456715226173, 0);
  g->Transpose(6718, 4236, {1,0});
  g->Binary(ynn_binary_multiply, 4233, 4235, 4231);
  g->Dot(1135, 4236, YNN_INVALID_VALUE_ID, 4230, 1);
  g->DequantizeTensor(4230, YNN_INVALID_VALUE_ID, 4231, 4232);
  g->QuantizeTensor(4232, 6504, 4234, 1136);
  g->Dequantize(1136, 1137, 0.02042323723435402, 0);
  g->Transpose(6717, 4241, {1,0});
  g->Binary(ynn_binary_multiply, 4233, 4240, 4238);
  g->Dot(1135, 4241, YNN_INVALID_VALUE_ID, 4237, 1);
  g->DequantizeTensor(4237, YNN_INVALID_VALUE_ID, 4238, 4239);
  g->QuantizeTensor(4239, 6504, 4234, 1138);
  g->Dequantize(1138, 1139, 0.02042323723435402, 0);
  g->Polynomial(1139, 5793, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5793, 5794);
  g->Binary(ynn_binary_add, 5794, 5500, 5791);
  g->Binary(ynn_binary_multiply, 1139, 5498, 5792);
  g->Binary(ynn_binary_multiply, 5792, 5791, 1140);
  g->Binary(ynn_binary_multiply, 1137, 1140, 1141);
  g->Quantize(1141, 1142, 0.021530522033572197, 0);
  g->Transpose(6716, 4248, {1,0});
  g->Binary(ynn_binary_multiply, 4245, 4247, 4243);
  g->Dot(1142, 4248, YNN_INVALID_VALUE_ID, 4242, 1);
  g->DequantizeTensor(4242, YNN_INVALID_VALUE_ID, 4243, 4244);
  g->QuantizeTensor(4244, 6504, 4246, 1144);
  g->Dequantize(1144, 1145, 0.011490405537188053, 0);
  g->Unary(ynn_unary_square, 1145, 1146);
  g->Reduce(ynn_reduce_sum, 1146, 5796, {2}, true);
  g->ShapeProduct(1146, 5795, {2});
  g->Binary(ynn_binary_divide, 5796, 5795, 1147);
  g->Binary(ynn_binary_add, 1147, 6539, 1148);
  g->Unary(ynn_unary_rsqrt, 1148, 1149);
  g->Binary(ynn_binary_multiply, 1145, 1149, 1150);
  g->Binary(ynn_binary_multiply, 1150, 6722, 1151);
  g->Binary(ynn_binary_add, 1151, 1126, 1152);
}

// Scope: "Layer16 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(427, 1153, {0,0,16,0}, {-1,-1,1,-1});
  g->Reshape(1153, 1155, {1,1,256});
  g->Unary(ynn_unary_square, 1155, 1156);
  g->Reduce(ynn_reduce_sum, 1156, 5798, {2}, true);
  g->ShapeProduct(1156, 5797, {2});
  g->Binary(ynn_binary_divide, 5798, 5797, 1157);
  g->Binary(ynn_binary_add, 1157, 6539, 1158);
  g->Unary(ynn_unary_rsqrt, 1158, 1159);
  g->Binary(ynn_binary_multiply, 1155, 1159, 1160);
  g->Binary(ynn_binary_multiply, 1160, 7118, 1161);
  g->Binary(ynn_binary_multiply, 7127, 6542, 1162);
  g->Binary(ynn_binary_add, 1161, 1162, 1163);
  g->Binary(ynn_binary_multiply, 1163, 6536, 1164);
  g->Quantize(1152, 1166, 0.1693648248910904, 0);
  g->Transpose(6719, 4262, {1,0});
  g->Binary(ynn_binary_multiply, 4259, 4261, 4257);
  g->Dot(1166, 4262, YNN_INVALID_VALUE_ID, 4256, 1);
  g->DequantizeTensor(4256, YNN_INVALID_VALUE_ID, 4257, 4258);
  g->QuantizeTensor(4258, 6504, 4260, 1167);
  g->Dequantize(1167, 1168, 0.07234252989292145, 0);
  g->Polynomial(1168, 5801, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5801, 5802);
  g->Binary(ynn_binary_add, 5802, 5500, 5799);
  g->Binary(ynn_binary_multiply, 1168, 5498, 5800);
  g->Binary(ynn_binary_multiply, 5800, 5799, 1169);
  g->Binary(ynn_binary_multiply, 1169, 1164, 1170);
  g->Quantize(1170, 1171, 0.8779527544975281, 0);
  g->Transpose(6720, 4269, {1,0});
  g->Binary(ynn_binary_multiply, 4266, 4268, 4264);
  g->Dot(1171, 4269, YNN_INVALID_VALUE_ID, 4263, 1);
  g->DequantizeTensor(4263, YNN_INVALID_VALUE_ID, 4264, 4265);
  g->QuantizeTensor(4265, 6504, 4267, 1172);
  g->Dequantize(1172, 1173, 0.16087517142295837, 0);
  g->Unary(ynn_unary_square, 1173, 1174);
  g->Reduce(ynn_reduce_sum, 1174, 5804, {2}, true);
  g->ShapeProduct(1174, 5803, {2});
  g->Binary(ynn_binary_divide, 5804, 5803, 1175);
  g->Binary(ynn_binary_add, 1175, 6539, 1178);
  g->Unary(ynn_unary_rsqrt, 1178, 1179);
  g->Binary(ynn_binary_multiply, 1173, 1179, 1180);
  g->Binary(ynn_binary_multiply, 1180, 6723, 1181);
  g->Binary(ynn_binary_add, 1152, 1181, 1182);
  g->Binary(ynn_binary_multiply, 1182, 6715, 1183);
}

// Scope: "Layer16"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16(Context& ctx) {
  BuildLayer16Attention(ctx);
  BuildLayer16Mlp(ctx);
  BuildLayer16PerLayerEmbedding(ctx);
}

// Scope: "Layer17 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(1190, 1191, 0.25072598457336426, 0);
  g->Transpose(6741, 4276, {1,0});
  g->Binary(ynn_binary_multiply, 4273, 4275, 4271);
  g->Dot(1191, 4276, YNN_INVALID_VALUE_ID, 4270, 1);
  g->DequantizeTensor(4270, YNN_INVALID_VALUE_ID, 4271, 4272);
  g->QuantizeTensor(4272, 6504, 4274, 1192);
  g->Dequantize(1192, 1193, 0.374015748500824, 0);
  g->SplitDim(1193, 1194, 2, {8,256});
  g->FuseDims(1194, 1196, 1, 2);
  g->SplitDim(1196, 1195, 1, {8,1});
  g->Unary(ynn_unary_square, 1195, 1197);
  g->Reduce(ynn_reduce_sum, 1197, 5808, {3}, true);
  g->ShapeProduct(1197, 5807, {3});
  g->Binary(ynn_binary_divide, 5808, 5807, 1198);
  g->Binary(ynn_binary_add, 1198, 6539, 1199);
  g->Unary(ynn_unary_rsqrt, 1199, 1201);
  g->Binary(ynn_binary_multiply, 1195, 1201, 1202);
  g->Binary(ynn_binary_multiply, 1202, 6740, 1203);
  g->Slice(1203, 1204, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1203, 1205, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1205, 1206);
  g->Concat({1206,1204}, 1207, 3);
  g->Binary(ynn_binary_multiply, 1203, 3067, 1208);
  g->Binary(ynn_binary_multiply, 1207, 3172, 1209);
  g->Binary(ynn_binary_add, 1208, 1209, 1210);
}

// Scope: "Layer17 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7190, 1212, 0.0059552486054599285, 0);
  g->Dequantize(7205, 1213, 0.047244105488061905, 0);
  g->Matmul(1210, 1212, 1214, false, true);
  g->Mask(1214, 6554, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6554, 5814, {-1}, true);
  g->Binary(ynn_binary_subtract, 6554, 5814, 5811);
  g->Unary(ynn_unary_exp, 5811, 5812);
  g->Reduce(ynn_reduce_sum, 5812, 5815, {-1}, true);
  g->Binary(ynn_binary_divide, 5500, 5815, 5813);
  g->Binary(ynn_binary_multiply, 5812, 5813, 1215);
  g->Matmul(1215, 1213, 1216, false, false);
}

// Scope: "Layer17 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(1216, 1218, 1, 2);
  g->SplitDim(1218, 1217, 1, {1,8});
  g->FuseDims(1217, 1219, 2, 2);
  g->Quantize(1219, 1220, 0.023375993594527245, 0);
  g->Transpose(6739, 4283, {1,0});
  g->Binary(ynn_binary_multiply, 4280, 4282, 4278);
  g->Dot(1220, 4283, YNN_INVALID_VALUE_ID, 4277, 1);
  g->DequantizeTensor(4277, YNN_INVALID_VALUE_ID, 4278, 4279);
  g->QuantizeTensor(4279, 6504, 4281, 1221);
  g->Dequantize(1221, 1223, 0.020179564133286476, 0);
}

// Scope: "Layer17 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1183, 1184);
  g->Reduce(ynn_reduce_sum, 1184, 5806, {2}, true);
  g->ShapeProduct(1184, 5805, {2});
  g->Binary(ynn_binary_divide, 5806, 5805, 1185);
  g->Binary(ynn_binary_add, 1185, 6539, 1186);
  g->Unary(ynn_unary_rsqrt, 1186, 1187);
  g->Binary(ynn_binary_multiply, 1183, 1187, 1189);
  g->Binary(ynn_binary_multiply, 1189, 6728, 1190);
  BuildLayer17AttentionQueryProjection(ctx);
  BuildLayer17AttentionSdpa(ctx);
  BuildLayer17AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1223, 1224);
  g->Reduce(ynn_reduce_sum, 1224, 5817, {2}, true);
  g->ShapeProduct(1224, 5816, {2});
  g->Binary(ynn_binary_divide, 5817, 5816, 1225);
  g->Binary(ynn_binary_add, 1225, 6539, 1226);
  g->Unary(ynn_unary_rsqrt, 1226, 1227);
  g->Binary(ynn_binary_multiply, 1223, 1227, 1228);
  g->Binary(ynn_binary_multiply, 1228, 6735, 1229);
  g->Binary(ynn_binary_add, 1229, 1183, 1230);
}

// Scope: "Layer17 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1230, 1231);
  g->Reduce(ynn_reduce_sum, 1231, 5819, {2}, true);
  g->ShapeProduct(1231, 5818, {2});
  g->Binary(ynn_binary_divide, 5819, 5818, 1232);
  g->Binary(ynn_binary_add, 1232, 6539, 1234);
  g->Unary(ynn_unary_rsqrt, 1234, 1235);
  g->Binary(ynn_binary_multiply, 1230, 1235, 1236);
  g->Binary(ynn_binary_multiply, 1236, 6738, 1237);
  g->Quantize(1237, 1238, 0.02002163790166378, 0);
  g->Transpose(6732, 4290, {1,0});
  g->Binary(ynn_binary_multiply, 4287, 4289, 4285);
  g->Dot(1238, 4290, YNN_INVALID_VALUE_ID, 4284, 1);
  g->DequantizeTensor(4284, YNN_INVALID_VALUE_ID, 4285, 4286);
  g->QuantizeTensor(4286, 6504, 4288, 1239);
  g->Dequantize(1239, 1240, 0.02325296215713024, 0);
  g->Transpose(6731, 4295, {1,0});
  g->Binary(ynn_binary_multiply, 4287, 4294, 4292);
  g->Dot(1238, 4295, YNN_INVALID_VALUE_ID, 4291, 1);
  g->DequantizeTensor(4291, YNN_INVALID_VALUE_ID, 4292, 4293);
  g->QuantizeTensor(4293, 6504, 4288, 1241);
  g->Dequantize(1241, 1242, 0.02325296215713024, 0);
  g->Polynomial(1242, 5822, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5822, 5823);
  g->Binary(ynn_binary_add, 5823, 5500, 5820);
  g->Binary(ynn_binary_multiply, 1242, 5498, 5821);
  g->Binary(ynn_binary_multiply, 5821, 5820, 1244);
  g->Binary(ynn_binary_multiply, 1240, 1244, 1245);
  g->Quantize(1245, 1246, 0.03641733527183533, 0);
  g->Transpose(6730, 4302, {1,0});
  g->Binary(ynn_binary_multiply, 4299, 4301, 4297);
  g->Dot(1246, 4302, YNN_INVALID_VALUE_ID, 4296, 1);
  g->DequantizeTensor(4296, YNN_INVALID_VALUE_ID, 4297, 4298);
  g->QuantizeTensor(4298, 6504, 4300, 1247);
  g->Dequantize(1247, 1248, 0.022161640226840973, 0);
  g->Unary(ynn_unary_square, 1248, 1249);
  g->Reduce(ynn_reduce_sum, 1249, 5825, {2}, true);
  g->ShapeProduct(1249, 5824, {2});
  g->Binary(ynn_binary_divide, 5825, 5824, 1250);
  g->Binary(ynn_binary_add, 1250, 6539, 1251);
  g->Unary(ynn_unary_rsqrt, 1251, 1252);
  g->Binary(ynn_binary_multiply, 1248, 1252, 1253);
  g->Binary(ynn_binary_multiply, 1253, 6736, 1255);
  g->Binary(ynn_binary_add, 1255, 1230, 1256);
}

// Scope: "Layer17 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(427, 1257, {0,0,17,0}, {-1,-1,1,-1});
  g->Reshape(1257, 1258, {1,1,256});
  g->Unary(ynn_unary_square, 1258, 1259);
  g->Reduce(ynn_reduce_sum, 1259, 5827, {2}, true);
  g->ShapeProduct(1259, 5826, {2});
  g->Binary(ynn_binary_divide, 5827, 5826, 1260);
  g->Binary(ynn_binary_add, 1260, 6539, 1261);
  g->Unary(ynn_unary_rsqrt, 1261, 1262);
  g->Binary(ynn_binary_multiply, 1258, 1262, 1263);
  g->Binary(ynn_binary_multiply, 1263, 7118, 1264);
  g->Binary(ynn_binary_multiply, 7128, 6542, 1266);
  g->Binary(ynn_binary_add, 1264, 1266, 1267);
  g->Binary(ynn_binary_multiply, 1267, 6536, 1268);
  g->Quantize(1256, 1269, 0.16417057812213898, 0);
  g->Transpose(6733, 4309, {1,0});
  g->Binary(ynn_binary_multiply, 4306, 4308, 4304);
  g->Dot(1269, 4309, YNN_INVALID_VALUE_ID, 4303, 1);
  g->DequantizeTensor(4303, YNN_INVALID_VALUE_ID, 4304, 4305);
  g->QuantizeTensor(4305, 6504, 4307, 1270);
  g->Dequantize(1270, 1271, 0.0821850448846817, 0);
  g->Polynomial(1271, 5830, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5830, 5831);
  g->Binary(ynn_binary_add, 5831, 5500, 5828);
  g->Binary(ynn_binary_multiply, 1271, 5498, 5829);
  g->Binary(ynn_binary_multiply, 5829, 5828, 1272);
  g->Binary(ynn_binary_multiply, 1272, 1268, 1273);
  g->Quantize(1273, 1274, 0.8188976645469666, 0);
  g->Transpose(6734, 4316, {1,0});
  g->Binary(ynn_binary_multiply, 4313, 4315, 4311);
  g->Dot(1274, 4316, YNN_INVALID_VALUE_ID, 4310, 1);
  g->DequantizeTensor(4310, YNN_INVALID_VALUE_ID, 4311, 4312);
  g->QuantizeTensor(4312, 6504, 4314, 1275);
  g->Dequantize(1275, 1277, 0.2322644591331482, 0);
  g->Unary(ynn_unary_square, 1277, 1278);
  g->Reduce(ynn_reduce_sum, 1278, 5835, {2}, true);
  g->ShapeProduct(1278, 5834, {2});
  g->Binary(ynn_binary_divide, 5835, 5834, 1279);
  g->Binary(ynn_binary_add, 1279, 6539, 1280);
  g->Unary(ynn_unary_rsqrt, 1280, 1281);
  g->Binary(ynn_binary_multiply, 1277, 1281, 1282);
  g->Binary(ynn_binary_multiply, 1282, 6737, 1283);
  g->Binary(ynn_binary_add, 1256, 1283, 1284);
  g->Binary(ynn_binary_multiply, 1284, 6729, 1285);
}

// Scope: "Layer17"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17(Context& ctx) {
  BuildLayer17Attention(ctx);
  BuildLayer17Mlp(ctx);
  BuildLayer17PerLayerEmbedding(ctx);
}

// Scope: "Layer18 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(1293, 1294, 0.3068588376045227, 0);
  g->Transpose(6755, 4330, {1,0});
  g->Binary(ynn_binary_multiply, 4327, 4329, 4325);
  g->Dot(1294, 4330, YNN_INVALID_VALUE_ID, 4324, 1);
  g->DequantizeTensor(4324, YNN_INVALID_VALUE_ID, 4325, 4326);
  g->QuantizeTensor(4326, 6504, 4328, 1295);
  g->Dequantize(1295, 1296, 0.36220473051071167, 0);
  g->SplitDim(1296, 1297, 2, {8,256});
  g->FuseDims(1297, 1299, 1, 2);
  g->SplitDim(1299, 1298, 1, {8,1});
  g->Unary(ynn_unary_square, 1298, 1301);
  g->Reduce(ynn_reduce_sum, 1301, 5839, {3}, true);
  g->ShapeProduct(1301, 5838, {3});
  g->Binary(ynn_binary_divide, 5839, 5838, 1302);
  g->Binary(ynn_binary_add, 1302, 6539, 1303);
  g->Unary(ynn_unary_rsqrt, 1303, 1304);
  g->Binary(ynn_binary_multiply, 1298, 1304, 1305);
  g->Binary(ynn_binary_multiply, 1305, 6754, 1306);
  g->Slice(1306, 1307, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1306, 1308, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1308, 1309);
  g->Concat({1309,1307}, 1310, 3);
  g->Binary(ynn_binary_multiply, 1306, 3067, 1312);
  g->Binary(ynn_binary_multiply, 1310, 3172, 1313);
  g->Binary(ynn_binary_add, 1312, 1313, 1314);
}

// Scope: "Layer18 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7190, 1315, 0.0059552486054599285, 0);
  g->Dequantize(7205, 1316, 0.047244105488061905, 0);
  g->Matmul(1314, 1315, 1317, false, true);
  g->Mask(1317, 6555, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6555, 5843, {-1}, true);
  g->Binary(ynn_binary_subtract, 6555, 5843, 5840);
  g->Unary(ynn_unary_exp, 5840, 5841);
  g->Reduce(ynn_reduce_sum, 5841, 5844, {-1}, true);
  g->Binary(ynn_binary_divide, 5500, 5844, 5842);
  g->Binary(ynn_binary_multiply, 5841, 5842, 1318);
  g->Matmul(1318, 1316, 1319, false, false);
}

// Scope: "Layer18 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(1319, 1321, 1, 2);
  g->SplitDim(1321, 1320, 1, {1,8});
  g->FuseDims(1320, 1323, 2, 2);
  g->Quantize(1323, 1324, 0.023006899282336235, 0);
  g->Transpose(6753, 4337, {1,0});
  g->Binary(ynn_binary_multiply, 4334, 4336, 4332);
  g->Dot(1324, 4337, YNN_INVALID_VALUE_ID, 4331, 1);
  g->DequantizeTensor(4331, YNN_INVALID_VALUE_ID, 4332, 4333);
  g->QuantizeTensor(4333, 6504, 4335, 1325);
  g->Dequantize(1325, 1326, 0.023901576176285744, 0);
}

// Scope: "Layer18 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1285, 1286);
  g->Reduce(ynn_reduce_sum, 1286, 5837, {2}, true);
  g->ShapeProduct(1286, 5836, {2});
  g->Binary(ynn_binary_divide, 5837, 5836, 1289);
  g->Binary(ynn_binary_add, 1289, 6539, 1290);
  g->Unary(ynn_unary_rsqrt, 1290, 1291);
  g->Binary(ynn_binary_multiply, 1285, 1291, 1292);
  g->Binary(ynn_binary_multiply, 1292, 6742, 1293);
  BuildLayer18AttentionQueryProjection(ctx);
  BuildLayer18AttentionSdpa(ctx);
  BuildLayer18AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1326, 1327);
  g->Reduce(ynn_reduce_sum, 1327, 5846, {2}, true);
  g->ShapeProduct(1327, 5845, {2});
  g->Binary(ynn_binary_divide, 5846, 5845, 1328);
  g->Binary(ynn_binary_add, 1328, 6539, 1329);
  g->Unary(ynn_unary_rsqrt, 1329, 1330);
  g->Binary(ynn_binary_multiply, 1326, 1330, 1331);
  g->Binary(ynn_binary_multiply, 1331, 6749, 1332);
  g->Binary(ynn_binary_add, 1332, 1285, 1334);
}

// Scope: "Layer18 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1334, 1335);
  g->Reduce(ynn_reduce_sum, 1335, 5848, {2}, true);
  g->ShapeProduct(1335, 5847, {2});
  g->Binary(ynn_binary_divide, 5848, 5847, 1336);
  g->Binary(ynn_binary_add, 1336, 6539, 1337);
  g->Unary(ynn_unary_rsqrt, 1337, 1338);
  g->Binary(ynn_binary_multiply, 1334, 1338, 1339);
  g->Binary(ynn_binary_multiply, 1339, 6752, 1340);
  g->Quantize(1340, 1341, 0.018082860857248306, 0);
  g->Transpose(6746, 4344, {1,0});
  g->Binary(ynn_binary_multiply, 4341, 4343, 4339);
  g->Dot(1341, 4344, YNN_INVALID_VALUE_ID, 4338, 1);
  g->DequantizeTensor(4338, YNN_INVALID_VALUE_ID, 4339, 4340);
  g->QuantizeTensor(4340, 6504, 4342, 1342);
  g->Dequantize(1342, 1343, 0.02362205646932125, 0);
  g->Transpose(6745, 4356, {1,0});
  g->Binary(ynn_binary_multiply, 4341, 4355, 4353);
  g->Dot(1341, 4356, YNN_INVALID_VALUE_ID, 4352, 1);
  g->DequantizeTensor(4352, YNN_INVALID_VALUE_ID, 4353, 4354);
  g->QuantizeTensor(4354, 6504, 4342, 1345);
  g->Dequantize(1345, 1346, 0.02362205646932125, 0);
  g->Polynomial(1346, 5851, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5851, 5852);
  g->Binary(ynn_binary_add, 5852, 5500, 5849);
  g->Binary(ynn_binary_multiply, 1346, 5498, 5850);
  g->Binary(ynn_binary_multiply, 5850, 5849, 1347);
  g->Binary(ynn_binary_multiply, 1343, 1347, 1348);
  g->Quantize(1348, 1349, 0.03297245129942894, 0);
  g->Transpose(6744, 4363, {1,0});
  g->Binary(ynn_binary_multiply, 4360, 4362, 4358);
  g->Dot(1349, 4363, YNN_INVALID_VALUE_ID, 4357, 1);
  g->DequantizeTensor(4357, YNN_INVALID_VALUE_ID, 4358, 4359);
  g->QuantizeTensor(4359, 6504, 4361, 1350);
  g->Dequantize(1350, 1351, 0.034845925867557526, 0);
  g->Unary(ynn_unary_square, 1351, 1352);
  g->Reduce(ynn_reduce_sum, 1352, 5854, {2}, true);
  g->ShapeProduct(1352, 5853, {2});
  g->Binary(ynn_binary_divide, 5854, 5853, 1353);
  g->Binary(ynn_binary_add, 1353, 6539, 1355);
  g->Unary(ynn_unary_rsqrt, 1355, 1356);
  g->Binary(ynn_binary_multiply, 1351, 1356, 1357);
  g->Binary(ynn_binary_multiply, 1357, 6750, 1358);
  g->Binary(ynn_binary_add, 1358, 1334, 1359);
}

// Scope: "Layer18 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(427, 1360, {0,0,18,0}, {-1,-1,1,-1});
  g->Reshape(1360, 1361, {1,1,256});
  g->Unary(ynn_unary_square, 1361, 1362);
  g->Reduce(ynn_reduce_sum, 1362, 5856, {2}, true);
  g->ShapeProduct(1362, 5855, {2});
  g->Binary(ynn_binary_divide, 5856, 5855, 1363);
  g->Binary(ynn_binary_add, 1363, 6539, 1364);
  g->Unary(ynn_unary_rsqrt, 1364, 1365);
  g->Binary(ynn_binary_multiply, 1361, 1365, 1366);
  g->Binary(ynn_binary_multiply, 1366, 7118, 1367);
  g->Binary(ynn_binary_multiply, 7129, 6542, 1368);
  g->Binary(ynn_binary_add, 1367, 1368, 1369);
  g->Binary(ynn_binary_multiply, 1369, 6536, 1370);
  g->Quantize(1359, 1371, 0.18026936054229736, 0);
  g->Transpose(6747, 4370, {1,0});
  g->Binary(ynn_binary_multiply, 4367, 4369, 4365);
  g->Dot(1371, 4370, YNN_INVALID_VALUE_ID, 4364, 1);
  g->DequantizeTensor(4364, YNN_INVALID_VALUE_ID, 4365, 4366);
  g->QuantizeTensor(4366, 6504, 4368, 1372);
  g->Dequantize(1372, 1373, 0.08562992513179779, 0);
  g->Polynomial(1373, 5859, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5859, 5860);
  g->Binary(ynn_binary_add, 5860, 5500, 5857);
  g->Binary(ynn_binary_multiply, 1373, 5498, 5858);
  g->Binary(ynn_binary_multiply, 5858, 5857, 1374);
  g->Binary(ynn_binary_multiply, 1374, 1370, 1376);
  g->Quantize(1376, 1377, 1.4409449100494385, 0);
  g->Transpose(6748, 4382, {1,0});
  g->Binary(ynn_binary_multiply, 4379, 4381, 4377);
  g->Dot(1377, 4382, YNN_INVALID_VALUE_ID, 4376, 1);
  g->DequantizeTensor(4376, YNN_INVALID_VALUE_ID, 4377, 4378);
  g->QuantizeTensor(4378, 6504, 4380, 1378);
  g->Dequantize(1378, 1379, 0.2601272463798523, 0);
  g->Unary(ynn_unary_square, 1379, 1380);
  g->Reduce(ynn_reduce_sum, 1380, 5862, {2}, true);
  g->ShapeProduct(1380, 5861, {2});
  g->Binary(ynn_binary_divide, 5862, 5861, 1381);
  g->Binary(ynn_binary_add, 1381, 6539, 1382);
  g->Unary(ynn_unary_rsqrt, 1382, 1383);
  g->Binary(ynn_binary_multiply, 1379, 1383, 1384);
  g->Binary(ynn_binary_multiply, 1384, 6751, 1385);
  g->Binary(ynn_binary_add, 1359, 1385, 1387);
  g->Binary(ynn_binary_multiply, 1387, 6743, 1388);
}

// Scope: "Layer18"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18(Context& ctx) {
  BuildLayer18Attention(ctx);
  BuildLayer18Mlp(ctx);
  BuildLayer18PerLayerEmbedding(ctx);
}

// Scope: "Layer19 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(1394, 1395, 0.3205932080745697, 0);
  g->Transpose(6769, 4389, {1,0});
  g->Binary(ynn_binary_multiply, 4386, 4388, 4384);
  g->Dot(1395, 4389, YNN_INVALID_VALUE_ID, 4383, 1);
  g->DequantizeTensor(4383, YNN_INVALID_VALUE_ID, 4384, 4385);
  g->QuantizeTensor(4385, 6504, 4387, 1396);
  g->Dequantize(1396, 1399, 0.4685039222240448, 0);
  g->SplitDim(1399, 1400, 2, {8,512});
  g->FuseDims(1400, 1402, 1, 2);
  g->SplitDim(1402, 1401, 1, {8,1});
  g->Unary(ynn_unary_square, 1401, 1403);
  g->Reduce(ynn_reduce_sum, 1403, 5870, {3}, true);
  g->ShapeProduct(1403, 5869, {3});
  g->Binary(ynn_binary_divide, 5870, 5869, 1404);
  g->Binary(ynn_binary_add, 1404, 6539, 1405);
  g->Unary(ynn_unary_rsqrt, 1405, 1406);
  g->Binary(ynn_binary_multiply, 1401, 1406, 1407);
  g->Binary(ynn_binary_multiply, 1407, 6768, 1408);
  g->Slice(1408, 1409, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(1408, 1411, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 1411, 1412);
  g->Concat({1412,1409}, 1413, 3);
  g->Binary(ynn_binary_multiply, 1408, 3594, 1414);
  g->Binary(ynn_binary_multiply, 1413, 2, 1415);
  g->Binary(ynn_binary_add, 1414, 1415, 1416);
}

// Scope: "Layer19 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7191, 1417, 0.001091228099539876, 0);
  g->Dequantize(7206, 1418, 0.01785714365541935, 0);
  g->Matmul(1416, 1417, 1419, false, true);
  g->Mask(1419, 6556, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 6556, 5874, {-1}, true);
  g->Binary(ynn_binary_subtract, 6556, 5874, 5871);
  g->Unary(ynn_unary_exp, 5871, 5872);
  g->Reduce(ynn_reduce_sum, 5872, 5875, {-1}, true);
  g->Binary(ynn_binary_divide, 5500, 5875, 5873);
  g->Binary(ynn_binary_multiply, 5872, 5873, 1421);
  g->Matmul(1421, 1418, 1422, false, false);
}

// Scope: "Layer19 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(1422, 1424, 1, 2);
  g->SplitDim(1424, 1423, 1, {1,8});
  g->FuseDims(1423, 1425, 2, 2);
  g->Quantize(1425, 1426, 0.014886821620166302, 0);
  g->Transpose(6767, 4396, {1,0});
  g->Binary(ynn_binary_multiply, 4393, 4395, 4391);
  g->Dot(1426, 4396, YNN_INVALID_VALUE_ID, 4390, 1);
  g->DequantizeTensor(4390, YNN_INVALID_VALUE_ID, 4391, 4392);
  g->QuantizeTensor(4392, 6504, 4394, 1427);
  g->Dequantize(1427, 1428, 0.01861305721104145, 0);
}

// Scope: "Layer19 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1388, 1389);
  g->Reduce(ynn_reduce_sum, 1389, 5864, {2}, true);
  g->ShapeProduct(1389, 5863, {2});
  g->Binary(ynn_binary_divide, 5864, 5863, 1390);
  g->Binary(ynn_binary_add, 1390, 6539, 1391);
  g->Unary(ynn_unary_rsqrt, 1391, 1392);
  g->Binary(ynn_binary_multiply, 1388, 1392, 1393);
  g->Binary(ynn_binary_multiply, 1393, 6756, 1394);
  BuildLayer19AttentionQueryProjection(ctx);
  BuildLayer19AttentionSdpa(ctx);
  BuildLayer19AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1428, 1429);
  g->Reduce(ynn_reduce_sum, 1429, 5877, {2}, true);
  g->ShapeProduct(1429, 5876, {2});
  g->Binary(ynn_binary_divide, 5877, 5876, 1430);
  g->Binary(ynn_binary_add, 1430, 6539, 1431);
  g->Unary(ynn_unary_rsqrt, 1431, 1433);
  g->Binary(ynn_binary_multiply, 1428, 1433, 1434);
  g->Binary(ynn_binary_multiply, 1434, 6763, 1435);
  g->Binary(ynn_binary_add, 1435, 1388, 1436);
}

// Scope: "Layer19 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1436, 1437);
  g->Reduce(ynn_reduce_sum, 1437, 5879, {2}, true);
  g->ShapeProduct(1437, 5878, {2});
  g->Binary(ynn_binary_divide, 5879, 5878, 1438);
  g->Binary(ynn_binary_add, 1438, 6539, 1439);
  g->Unary(ynn_unary_rsqrt, 1439, 1440);
  g->Binary(ynn_binary_multiply, 1436, 1440, 1441);
  g->Binary(ynn_binary_multiply, 1441, 6766, 1442);
  g->Quantize(1442, 1444, 0.019887126982212067, 0);
  g->Transpose(6760, 4410, {1,0});
  g->Binary(ynn_binary_multiply, 4407, 4409, 4405);
  g->Dot(1444, 4410, YNN_INVALID_VALUE_ID, 4404, 1);
  g->DequantizeTensor(4404, YNN_INVALID_VALUE_ID, 4405, 4406);
  g->QuantizeTensor(4406, 6504, 4408, 1445);
  g->Dequantize(1445, 1446, 0.022637804970145226, 0);
  g->Transpose(6759, 4415, {1,0});
  g->Binary(ynn_binary_multiply, 4407, 4414, 4412);
  g->Dot(1444, 4415, YNN_INVALID_VALUE_ID, 4411, 1);
  g->DequantizeTensor(4411, YNN_INVALID_VALUE_ID, 4412, 4413);
  g->QuantizeTensor(4413, 6504, 4408, 1447);
  g->Dequantize(1447, 1448, 0.022637804970145226, 0);
  g->Polynomial(1448, 5882, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5882, 5883);
  g->Binary(ynn_binary_add, 5883, 5500, 5880);
  g->Binary(ynn_binary_multiply, 1448, 5498, 5881);
  g->Binary(ynn_binary_multiply, 5881, 5880, 1449);
  g->Binary(ynn_binary_multiply, 1446, 1449, 1450);
  g->Quantize(1450, 1451, 0.019808080047369003, 0);
  g->Transpose(6758, 4422, {1,0});
  g->Binary(ynn_binary_multiply, 4419, 4421, 4417);
  g->Dot(1451, 4422, YNN_INVALID_VALUE_ID, 4416, 1);
  g->DequantizeTensor(4416, YNN_INVALID_VALUE_ID, 4417, 4418);
  g->QuantizeTensor(4418, 6504, 4420, 1452);
  g->Dequantize(1452, 1454, 0.014754860661923885, 0);
  g->Unary(ynn_unary_square, 1454, 1455);
  g->Reduce(ynn_reduce_sum, 1455, 5885, {2}, true);
  g->ShapeProduct(1455, 5884, {2});
  g->Binary(ynn_binary_divide, 5885, 5884, 1456);
  g->Binary(ynn_binary_add, 1456, 6539, 1457);
  g->Unary(ynn_unary_rsqrt, 1457, 1458);
  g->Binary(ynn_binary_multiply, 1454, 1458, 1459);
  g->Binary(ynn_binary_multiply, 1459, 6764, 1460);
  g->Binary(ynn_binary_add, 1460, 1436, 1461);
}

// Scope: "Layer19 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(427, 1462, {0,0,19,0}, {-1,-1,1,-1});
  g->Reshape(1462, 1463, {1,1,256});
  g->Unary(ynn_unary_square, 1463, 1465);
  g->Reduce(ynn_reduce_sum, 1465, 5889, {2}, true);
  g->ShapeProduct(1465, 5888, {2});
  g->Binary(ynn_binary_divide, 5889, 5888, 1466);
  g->Binary(ynn_binary_add, 1466, 6539, 1467);
  g->Unary(ynn_unary_rsqrt, 1467, 1468);
  g->Binary(ynn_binary_multiply, 1463, 1468, 1469);
  g->Binary(ynn_binary_multiply, 1469, 7118, 1470);
  g->Binary(ynn_binary_multiply, 7130, 6542, 1471);
  g->Binary(ynn_binary_add, 1470, 1471, 1472);
  g->Binary(ynn_binary_multiply, 1472, 6536, 1473);
  g->Quantize(1461, 1474, 0.18873928487300873, 0);
  g->Transpose(6761, 4428, {1,0});
  g->Binary(ynn_binary_multiply, 4426, 4427, 4424);
  g->Dot(1474, 4428, YNN_INVALID_VALUE_ID, 4423, 1);
  g->DequantizeTensor(4423, YNN_INVALID_VALUE_ID, 4424, 4425);
  g->QuantizeTensor(4425, 6504, 3991, 1476);
  g->Dequantize(1476, 1477, 0.08070866763591766, 0);
  g->Polynomial(1477, 5892, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5892, 5893);
  g->Binary(ynn_binary_add, 5893, 5500, 5890);
  g->Binary(ynn_binary_multiply, 1477, 5498, 5891);
  g->Binary(ynn_binary_multiply, 5891, 5890, 1478);
  g->Binary(ynn_binary_multiply, 1478, 1473, 1479);
  g->Quantize(1479, 1480, 0.3858267664909363, 0);
  g->Transpose(6762, 4435, {1,0});
  g->Binary(ynn_binary_multiply, 4432, 4434, 4430);
  g->Dot(1480, 4435, YNN_INVALID_VALUE_ID, 4429, 1);
  g->DequantizeTensor(4429, YNN_INVALID_VALUE_ID, 4430, 4431);
  g->QuantizeTensor(4431, 6504, 4433, 1481);
  g->Dequantize(1481, 1482, 0.16572551429271698, 0);
  g->Unary(ynn_unary_square, 1482, 1483);
  g->Reduce(ynn_reduce_sum, 1483, 5895, {2}, true);
  g->ShapeProduct(1483, 5894, {2});
  g->Binary(ynn_binary_divide, 5895, 5894, 1484);
  g->Binary(ynn_binary_add, 1484, 6539, 1485);
  g->Unary(ynn_unary_rsqrt, 1485, 1487);
  g->Binary(ynn_binary_multiply, 1482, 1487, 1488);
  g->Binary(ynn_binary_multiply, 1488, 6765, 1489);
  g->Binary(ynn_binary_add, 1461, 1489, 1490);
  g->Binary(ynn_binary_multiply, 1490, 6757, 1491);
}

// Scope: "Layer19"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19(Context& ctx) {
  BuildLayer19Attention(ctx);
  BuildLayer19Mlp(ctx);
  BuildLayer19PerLayerEmbedding(ctx);
}

// Scope: "Layer20 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(1498, 1499, 0.3106735646724701, 0);
  g->Transpose(6800, 4442, {1,0});
  g->Binary(ynn_binary_multiply, 4439, 4441, 4437);
  g->Dot(1499, 4442, YNN_INVALID_VALUE_ID, 4436, 1);
  g->DequantizeTensor(4436, YNN_INVALID_VALUE_ID, 4437, 4438);
  g->QuantizeTensor(4438, 6504, 4440, 1500);
  g->Dequantize(1500, 1501, 0.36614173650741577, 0);
  g->SplitDim(1501, 1502, 2, {8,256});
  g->FuseDims(1502, 1504, 1, 2);
  g->SplitDim(1504, 1503, 1, {8,1});
  g->Unary(ynn_unary_square, 1503, 1505);
  g->Reduce(ynn_reduce_sum, 1505, 5899, {3}, true);
  g->ShapeProduct(1505, 5898, {3});
  g->Binary(ynn_binary_divide, 5899, 5898, 1506);
  g->Binary(ynn_binary_add, 1506, 6539, 1507);
  g->Unary(ynn_unary_rsqrt, 1507, 1508);
  g->Binary(ynn_binary_multiply, 1503, 1508, 1511);
  g->Binary(ynn_binary_multiply, 1511, 6799, 1512);
  g->Slice(1512, 1513, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1512, 1514, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1514, 1515);
  g->Concat({1515,1513}, 1516, 3);
  g->Binary(ynn_binary_multiply, 1512, 3067, 1517);
  g->Binary(ynn_binary_multiply, 1516, 3172, 1518);
  g->Binary(ynn_binary_add, 1517, 1518, 1519);
}

// Scope: "Layer20 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7190, 1520, 0.0059552486054599285, 0);
  g->Dequantize(7205, 1522, 0.047244105488061905, 0);
  g->Matmul(1519, 1520, 1523, false, true);
  g->Mask(1523, 6558, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6558, 5903, {-1}, true);
  g->Binary(ynn_binary_subtract, 6558, 5903, 5900);
  g->Unary(ynn_unary_exp, 5900, 5901);
  g->Reduce(ynn_reduce_sum, 5901, 5904, {-1}, true);
  g->Binary(ynn_binary_divide, 5500, 5904, 5902);
  g->Binary(ynn_binary_multiply, 5901, 5902, 1524);
  g->Matmul(1524, 1522, 1525, false, false);
}

// Scope: "Layer20 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(1525, 1527, 1, 2);
  g->SplitDim(1527, 1526, 1, {1,8});
  g->FuseDims(1526, 1528, 2, 2);
  g->Quantize(1528, 1529, 0.02436024509370327, 0);
  g->Transpose(6798, 4448, {1,0});
  g->Binary(ynn_binary_multiply, 4179, 4447, 4444);
  g->Dot(1529, 4448, YNN_INVALID_VALUE_ID, 4443, 1);
  g->DequantizeTensor(4443, YNN_INVALID_VALUE_ID, 4444, 4445);
  g->QuantizeTensor(4445, 6504, 4446, 1530);
  g->Dequantize(1530, 1531, 0.035965267568826675, 0);
}

// Scope: "Layer20 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1491, 1492);
  g->Reduce(ynn_reduce_sum, 1492, 5897, {2}, true);
  g->ShapeProduct(1492, 5896, {2});
  g->Binary(ynn_binary_divide, 5897, 5896, 1493);
  g->Binary(ynn_binary_add, 1493, 6539, 1494);
  g->Unary(ynn_unary_rsqrt, 1494, 1495);
  g->Binary(ynn_binary_multiply, 1491, 1495, 1496);
  g->Binary(ynn_binary_multiply, 1496, 6787, 1498);
  BuildLayer20AttentionQueryProjection(ctx);
  BuildLayer20AttentionSdpa(ctx);
  BuildLayer20AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1531, 1533);
  g->Reduce(ynn_reduce_sum, 1533, 5906, {2}, true);
  g->ShapeProduct(1533, 5905, {2});
  g->Binary(ynn_binary_divide, 5906, 5905, 1534);
  g->Binary(ynn_binary_add, 1534, 6539, 1535);
  g->Unary(ynn_unary_rsqrt, 1535, 1536);
  g->Binary(ynn_binary_multiply, 1531, 1536, 1537);
  g->Binary(ynn_binary_multiply, 1537, 6794, 1538);
  g->Binary(ynn_binary_add, 1538, 1491, 1539);
}

// Scope: "Layer20 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1539, 1540);
  g->Reduce(ynn_reduce_sum, 1540, 5908, {2}, true);
  g->ShapeProduct(1540, 5907, {2});
  g->Binary(ynn_binary_divide, 5908, 5907, 1541);
  g->Binary(ynn_binary_add, 1541, 6539, 1542);
  g->Unary(ynn_unary_rsqrt, 1542, 1544);
  g->Binary(ynn_binary_multiply, 1539, 1544, 1545);
  g->Binary(ynn_binary_multiply, 1545, 6797, 1546);
  g->Quantize(1546, 1547, 0.021377958357334137, 0);
  g->Transpose(6791, 4455, {1,0});
  g->Binary(ynn_binary_multiply, 4452, 4454, 4450);
  g->Dot(1547, 4455, YNN_INVALID_VALUE_ID, 4449, 1);
  g->DequantizeTensor(4449, YNN_INVALID_VALUE_ID, 4450, 4451);
  g->QuantizeTensor(4451, 6504, 4453, 1548);
  g->Dequantize(1548, 1549, 0.02276083640754223, 0);
  g->Transpose(6790, 4460, {1,0});
  g->Binary(ynn_binary_multiply, 4452, 4459, 4457);
  g->Dot(1547, 4460, YNN_INVALID_VALUE_ID, 4456, 1);
  g->DequantizeTensor(4456, YNN_INVALID_VALUE_ID, 4457, 4458);
  g->QuantizeTensor(4458, 6504, 4453, 1550);
  g->Dequantize(1550, 1551, 0.02276083640754223, 0);
  g->Polynomial(1551, 5911, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5911, 5912);
  g->Binary(ynn_binary_add, 5912, 5500, 5909);
  g->Binary(ynn_binary_multiply, 1551, 5498, 5910);
  g->Binary(ynn_binary_multiply, 5910, 5909, 1552);
  g->Binary(ynn_binary_multiply, 1549, 1552, 1554);
  g->Quantize(1554, 1555, 0.026574812829494476, 0);
  g->Transpose(6789, 4467, {1,0});
  g->Binary(ynn_binary_multiply, 4464, 4466, 4462);
  g->Dot(1555, 4467, YNN_INVALID_VALUE_ID, 4461, 1);
  g->DequantizeTensor(4461, YNN_INVALID_VALUE_ID, 4462, 4463);
  g->QuantizeTensor(4463, 6504, 4465, 1556);
  g->Dequantize(1556, 1557, 0.028310857713222504, 0);
  g->Unary(ynn_unary_square, 1557, 1558);
  g->Reduce(ynn_reduce_sum, 1558, 5914, {2}, true);
  g->ShapeProduct(1558, 5913, {2});
  g->Binary(ynn_binary_divide, 5914, 5913, 1559);
  g->Binary(ynn_binary_add, 1559, 6539, 1560);
  g->Unary(ynn_unary_rsqrt, 1560, 1561);
  g->Binary(ynn_binary_multiply, 1557, 1561, 1562);
  g->Binary(ynn_binary_multiply, 1562, 6795, 1563);
  g->Binary(ynn_binary_add, 1563, 1539, 1565);
}

// Scope: "Layer20 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(427, 1566, {0,0,20,0}, {-1,-1,1,-1});
  g->Reshape(1566, 1567, {1,1,256});
  g->Unary(ynn_unary_square, 1567, 1568);
  g->Reduce(ynn_reduce_sum, 1568, 5918, {2}, true);
  g->ShapeProduct(1568, 5917, {2});
  g->Binary(ynn_binary_divide, 5918, 5917, 1569);
  g->Binary(ynn_binary_add, 1569, 6539, 1570);
  g->Unary(ynn_unary_rsqrt, 1570, 1571);
  g->Binary(ynn_binary_multiply, 1567, 1571, 1572);
  g->Binary(ynn_binary_multiply, 1572, 7118, 1573);
  g->Binary(ynn_binary_multiply, 7132, 6542, 1574);
  g->Binary(ynn_binary_add, 1573, 1574, 1576);
  g->Binary(ynn_binary_multiply, 1576, 6536, 1577);
  g->Quantize(1565, 1578, 0.17634929716587067, 0);
  g->Transpose(6792, 4474, {1,0});
  g->Binary(ynn_binary_multiply, 4471, 4473, 4469);
  g->Dot(1578, 4474, YNN_INVALID_VALUE_ID, 4468, 1);
  g->DequantizeTensor(4468, YNN_INVALID_VALUE_ID, 4469, 4470);
  g->QuantizeTensor(4470, 6504, 4472, 1579);
  g->Dequantize(1579, 1580, 0.059055130928754807, 0);
  g->Polynomial(1580, 5921, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5921, 5922);
  g->Binary(ynn_binary_add, 5922, 5500, 5919);
  g->Binary(ynn_binary_multiply, 1580, 5498, 5920);
  g->Binary(ynn_binary_multiply, 5920, 5919, 1581);
  g->Binary(ynn_binary_multiply, 1581, 1577, 1582);
  g->Quantize(1582, 1583, 0.1998031586408615, 0);
  g->Transpose(6793, 4481, {1,0});
  g->Binary(ynn_binary_multiply, 4478, 4480, 4476);
  g->Dot(1583, 4481, YNN_INVALID_VALUE_ID, 4475, 1);
  g->DequantizeTensor(4475, YNN_INVALID_VALUE_ID, 4476, 4477);
  g->QuantizeTensor(4477, 6504, 4479, 1584);
  g->Dequantize(1584, 1585, 0.07776007056236267, 0);
  g->Unary(ynn_unary_square, 1585, 1587);
  g->Reduce(ynn_reduce_sum, 1587, 5924, {2}, true);
  g->ShapeProduct(1587, 5923, {2});
  g->Binary(ynn_binary_divide, 5924, 5923, 1588);
  g->Binary(ynn_binary_add, 1588, 6539, 1589);
  g->Unary(ynn_unary_rsqrt, 1589, 1590);
  g->Binary(ynn_binary_multiply, 1585, 1590, 1591);
  g->Binary(ynn_binary_multiply, 1591, 6796, 1592);
  g->Binary(ynn_binary_add, 1565, 1592, 1593);
  g->Binary(ynn_binary_multiply, 1593, 6788, 1594);
}

// Scope: "Layer20"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20(Context& ctx) {
  BuildLayer20Attention(ctx);
  BuildLayer20Mlp(ctx);
  BuildLayer20PerLayerEmbedding(ctx);
}

// Scope: "Layer21 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(1601, 1602, 0.20073647797107697, 0);
  g->Transpose(6814, 4488, {1,0});
  g->Binary(ynn_binary_multiply, 4485, 4487, 4483);
  g->Dot(1602, 4488, YNN_INVALID_VALUE_ID, 4482, 1);
  g->DequantizeTensor(4482, YNN_INVALID_VALUE_ID, 4483, 4484);
  g->QuantizeTensor(4484, 6504, 4486, 1603);
  g->Dequantize(1603, 1604, 0.23622049391269684, 0);
  g->SplitDim(1604, 1605, 2, {8,256});
  g->FuseDims(1605, 1607, 1, 2);
  g->SplitDim(1607, 1606, 1, {8,1});
  g->Unary(ynn_unary_square, 1606, 1608);
  g->Reduce(ynn_reduce_sum, 1608, 5928, {3}, true);
  g->ShapeProduct(1608, 5927, {3});
  g->Binary(ynn_binary_divide, 5928, 5927, 1610);
  g->Binary(ynn_binary_add, 1610, 6539, 1611);
  g->Unary(ynn_unary_rsqrt, 1611, 1612);
  g->Binary(ynn_binary_multiply, 1606, 1612, 1613);
  g->Binary(ynn_binary_multiply, 1613, 6813, 1614);
  g->Slice(1614, 1615, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1614, 1616, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1616, 1617);
  g->Concat({1617,1615}, 1618, 3);
  g->Binary(ynn_binary_multiply, 1614, 3067, 1619);
  g->Binary(ynn_binary_multiply, 1618, 3172, 1622);
  g->Binary(ynn_binary_add, 1619, 1622, 1623);
}

// Scope: "Layer21 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7190, 1624, 0.0059552486054599285, 0);
  g->Dequantize(7205, 1625, 0.047244105488061905, 0);
  g->Matmul(1623, 1624, 1626, false, true);
  g->Mask(1626, 6559, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6559, 5932, {-1}, true);
  g->Binary(ynn_binary_subtract, 6559, 5932, 5929);
  g->Unary(ynn_unary_exp, 5929, 5930);
  g->Reduce(ynn_reduce_sum, 5930, 5933, {-1}, true);
  g->Binary(ynn_binary_divide, 5500, 5933, 5931);
  g->Binary(ynn_binary_multiply, 5930, 5931, 1627);
  g->Matmul(1627, 1625, 1628, false, false);
}

// Scope: "Layer21 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(1628, 1630, 1, 2);
  g->SplitDim(1630, 1629, 1, {1,8});
  g->FuseDims(1629, 1631, 2, 2);
  g->Quantize(1631, 1633, 0.025221465155482292, 0);
  g->Transpose(6812, 4495, {1,0});
  g->Binary(ynn_binary_multiply, 4492, 4494, 4490);
  g->Dot(1633, 4495, YNN_INVALID_VALUE_ID, 4489, 1);
  g->DequantizeTensor(4489, YNN_INVALID_VALUE_ID, 4490, 4491);
  g->QuantizeTensor(4491, 6504, 4493, 1634);
  g->Dequantize(1634, 1635, 0.03553423285484314, 0);
}

// Scope: "Layer21 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1594, 1595);
  g->Reduce(ynn_reduce_sum, 1595, 5926, {2}, true);
  g->ShapeProduct(1595, 5925, {2});
  g->Binary(ynn_binary_divide, 5926, 5925, 1596);
  g->Binary(ynn_binary_add, 1596, 6539, 1598);
  g->Unary(ynn_unary_rsqrt, 1598, 1599);
  g->Binary(ynn_binary_multiply, 1594, 1599, 1600);
  g->Binary(ynn_binary_multiply, 1600, 6801, 1601);
  BuildLayer21AttentionQueryProjection(ctx);
  BuildLayer21AttentionSdpa(ctx);
  BuildLayer21AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1635, 1636);
  g->Reduce(ynn_reduce_sum, 1636, 5935, {2}, true);
  g->ShapeProduct(1636, 5934, {2});
  g->Binary(ynn_binary_divide, 5935, 5934, 1637);
  g->Binary(ynn_binary_add, 1637, 6539, 1638);
  g->Unary(ynn_unary_rsqrt, 1638, 1639);
  g->Binary(ynn_binary_multiply, 1635, 1639, 1640);
  g->Binary(ynn_binary_multiply, 1640, 6808, 1641);
  g->Binary(ynn_binary_add, 1641, 1594, 1642);
}

// Scope: "Layer21 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1642, 1644);
  g->Reduce(ynn_reduce_sum, 1644, 5937, {2}, true);
  g->ShapeProduct(1644, 5936, {2});
  g->Binary(ynn_binary_divide, 5937, 5936, 1645);
  g->Binary(ynn_binary_add, 1645, 6539, 1646);
  g->Unary(ynn_unary_rsqrt, 1646, 1647);
  g->Binary(ynn_binary_multiply, 1642, 1647, 1648);
  g->Binary(ynn_binary_multiply, 1648, 6811, 1649);
  g->Quantize(1649, 1650, 0.019064493477344513, 0);
  g->Transpose(6805, 4501, {1,0});
  g->Binary(ynn_binary_multiply, 4499, 4500, 4497);
  g->Dot(1650, 4501, YNN_INVALID_VALUE_ID, 4496, 1);
  g->DequantizeTensor(4496, YNN_INVALID_VALUE_ID, 4497, 4498);
  g->QuantizeTensor(4498, 6504, 4342, 1651);
  g->Dequantize(1651, 1652, 0.02362205646932125, 0);
  g->Transpose(6804, 4506, {1,0});
  g->Binary(ynn_binary_multiply, 4499, 4505, 4503);
  g->Dot(1650, 4506, YNN_INVALID_VALUE_ID, 4502, 1);
  g->DequantizeTensor(4502, YNN_INVALID_VALUE_ID, 4503, 4504);
  g->QuantizeTensor(4504, 6504, 4342, 1654);
  g->Dequantize(1654, 1655, 0.02362205646932125, 0);
  g->Polynomial(1655, 5940, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5940, 5941);
  g->Binary(ynn_binary_add, 5941, 5500, 5938);
  g->Binary(ynn_binary_multiply, 1655, 5498, 5939);
  g->Binary(ynn_binary_multiply, 5939, 5938, 1656);
  g->Binary(ynn_binary_multiply, 1652, 1656, 1657);
  g->Quantize(1657, 1658, 0.030019694939255714, 0);
  g->Transpose(6803, 4513, {1,0});
  g->Binary(ynn_binary_multiply, 4510, 4512, 4508);
  g->Dot(1658, 4513, YNN_INVALID_VALUE_ID, 4507, 1);
  g->DequantizeTensor(4507, YNN_INVALID_VALUE_ID, 4508, 4509);
  g->QuantizeTensor(4509, 6504, 4511, 1659);
  g->Dequantize(1659, 1660, 0.03767223656177521, 0);
  g->Unary(ynn_unary_square, 1660, 1661);
  g->Reduce(ynn_reduce_sum, 1661, 5943, {2}, true);
  g->ShapeProduct(1661, 5942, {2});
  g->Binary(ynn_binary_divide, 5943, 5942, 1662);
  g->Binary(ynn_binary_add, 1662, 6539, 1663);
  g->Unary(ynn_unary_rsqrt, 1663, 1665);
  g->Binary(ynn_binary_multiply, 1660, 1665, 1666);
  g->Binary(ynn_binary_multiply, 1666, 6809, 1667);
  g->Binary(ynn_binary_add, 1667, 1642, 1668);
}

// Scope: "Layer21 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(427, 1669, {0,0,21,0}, {-1,-1,1,-1});
  g->Reshape(1669, 1670, {1,1,256});
  g->Unary(ynn_unary_square, 1670, 1671);
  g->Reduce(ynn_reduce_sum, 1671, 5945, {2}, true);
  g->ShapeProduct(1671, 5944, {2});
  g->Binary(ynn_binary_divide, 5945, 5944, 1672);
  g->Binary(ynn_binary_add, 1672, 6539, 1673);
  g->Unary(ynn_unary_rsqrt, 1673, 1674);
  g->Binary(ynn_binary_multiply, 1670, 1674, 1676);
  g->Binary(ynn_binary_multiply, 1676, 7118, 1677);
  g->Binary(ynn_binary_multiply, 7133, 6542, 1678);
  g->Binary(ynn_binary_add, 1677, 1678, 1679);
  g->Binary(ynn_binary_multiply, 1679, 6536, 1680);
  g->Quantize(1668, 1681, 0.14814288914203644, 0);
  g->Transpose(6806, 4527, {1,0});
  g->Binary(ynn_binary_multiply, 4524, 4526, 4522);
  g->Dot(1681, 4527, YNN_INVALID_VALUE_ID, 4521, 1);
  g->DequantizeTensor(4521, YNN_INVALID_VALUE_ID, 4522, 4523);
  g->QuantizeTensor(4523, 6504, 4525, 1682);
  g->Dequantize(1682, 1683, 0.047244105488061905, 0);
  g->Polynomial(1683, 5948, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5948, 5949);
  g->Binary(ynn_binary_add, 5949, 5500, 5946);
  g->Binary(ynn_binary_multiply, 1683, 5498, 5947);
  g->Binary(ynn_binary_multiply, 5947, 5946, 1684);
  g->Binary(ynn_binary_multiply, 1684, 1680, 1685);
  g->Quantize(1685, 1687, 0.10531497001647949, 0);
  g->Transpose(6807, 4534, {1,0});
  g->Binary(ynn_binary_multiply, 4531, 4533, 4529);
  g->Dot(1687, 4534, YNN_INVALID_VALUE_ID, 4528, 1);
  g->DequantizeTensor(4528, YNN_INVALID_VALUE_ID, 4529, 4530);
  g->QuantizeTensor(4530, 6504, 4532, 1688);
  g->Dequantize(1688, 1689, 0.061565153300762177, 0);
  g->Unary(ynn_unary_square, 1689, 1690);
  g->Reduce(ynn_reduce_sum, 1690, 5955, {2}, true);
  g->ShapeProduct(1690, 5954, {2});
  g->Binary(ynn_binary_divide, 5955, 5954, 1691);
  g->Binary(ynn_binary_add, 1691, 6539, 1692);
  g->Unary(ynn_unary_rsqrt, 1692, 1693);
  g->Binary(ynn_binary_multiply, 1689, 1693, 1694);
  g->Binary(ynn_binary_multiply, 1694, 6810, 1695);
  g->Binary(ynn_binary_add, 1668, 1695, 1696);
  g->Binary(ynn_binary_multiply, 1696, 6802, 1698);
}

// Scope: "Layer21"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21(Context& ctx) {
  BuildLayer21Attention(ctx);
  BuildLayer21Mlp(ctx);
  BuildLayer21PerLayerEmbedding(ctx);
}

// Scope: "Layer22 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(1704, 1705, 0.21987482905387878, 0);
  g->Transpose(6828, 4541, {1,0});
  g->Binary(ynn_binary_multiply, 4538, 4540, 4536);
  g->Dot(1705, 4541, YNN_INVALID_VALUE_ID, 4535, 1);
  g->DequantizeTensor(4535, YNN_INVALID_VALUE_ID, 4536, 4537);
  g->QuantizeTensor(4537, 6504, 4539, 1706);
  g->Dequantize(1706, 1707, 0.19685040414333344, 0);
  g->SplitDim(1707, 1709, 2, {8,256});
  g->FuseDims(1709, 1711, 1, 2);
  g->SplitDim(1711, 1710, 1, {8,1});
  g->Unary(ynn_unary_square, 1710, 1712);
  g->Reduce(ynn_reduce_sum, 1712, 5959, {3}, true);
  g->ShapeProduct(1712, 5958, {3});
  g->Binary(ynn_binary_divide, 5959, 5958, 1713);
  g->Binary(ynn_binary_add, 1713, 6539, 1714);
  g->Unary(ynn_unary_rsqrt, 1714, 1715);
  g->Binary(ynn_binary_multiply, 1710, 1715, 1716);
  g->Binary(ynn_binary_multiply, 1716, 6827, 1717);
  g->Slice(1717, 1718, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1717, 1719, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1719, 1721);
  g->Concat({1721,1718}, 1722, 3);
  g->Binary(ynn_binary_multiply, 1717, 3067, 1723);
  g->Binary(ynn_binary_multiply, 1722, 3172, 1724);
  g->Binary(ynn_binary_add, 1723, 1724, 1725);
}

// Scope: "Layer22 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7190, 1726, 0.0059552486054599285, 0);
  g->Dequantize(7205, 1727, 0.047244105488061905, 0);
  g->Matmul(1725, 1726, 1728, false, true);
  g->Mask(1728, 6560, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6560, 5963, {-1}, true);
  g->Binary(ynn_binary_subtract, 6560, 5963, 5960);
  g->Unary(ynn_unary_exp, 5960, 5961);
  g->Reduce(ynn_reduce_sum, 5961, 5964, {-1}, true);
  g->Binary(ynn_binary_divide, 5500, 5964, 5962);
  g->Binary(ynn_binary_multiply, 5961, 5962, 1729);
  g->Matmul(1729, 1727, 1732, false, false);
}

// Scope: "Layer22 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(1732, 1734, 1, 2);
  g->SplitDim(1734, 1733, 1, {1,8});
  g->FuseDims(1733, 1735, 2, 2);
  g->Quantize(1735, 1736, 0.023868119344115257, 0);
  g->Transpose(6826, 4555, {1,0});
  g->Binary(ynn_binary_multiply, 4552, 4554, 4550);
  g->Dot(1736, 4555, YNN_INVALID_VALUE_ID, 4549, 1);
  g->DequantizeTensor(4549, YNN_INVALID_VALUE_ID, 4550, 4551);
  g->QuantizeTensor(4551, 6504, 4553, 1737);
  g->Dequantize(1737, 1738, 0.047558318823575974, 0);
}

// Scope: "Layer22 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1698, 1699);
  g->Reduce(ynn_reduce_sum, 1699, 5957, {2}, true);
  g->ShapeProduct(1699, 5956, {2});
  g->Binary(ynn_binary_divide, 5957, 5956, 1700);
  g->Binary(ynn_binary_add, 1700, 6539, 1701);
  g->Unary(ynn_unary_rsqrt, 1701, 1702);
  g->Binary(ynn_binary_multiply, 1698, 1702, 1703);
  g->Binary(ynn_binary_multiply, 1703, 6815, 1704);
  BuildLayer22AttentionQueryProjection(ctx);
  BuildLayer22AttentionSdpa(ctx);
  BuildLayer22AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1738, 1739);
  g->Reduce(ynn_reduce_sum, 1739, 5966, {2}, true);
  g->ShapeProduct(1739, 5965, {2});
  g->Binary(ynn_binary_divide, 5966, 5965, 1740);
  g->Binary(ynn_binary_add, 1740, 6539, 1741);
  g->Unary(ynn_unary_rsqrt, 1741, 1742);
  g->Binary(ynn_binary_multiply, 1738, 1742, 1744);
  g->Binary(ynn_binary_multiply, 1744, 6822, 1745);
  g->Binary(ynn_binary_add, 1745, 1698, 1746);
}

// Scope: "Layer22 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1746, 1747);
  g->Reduce(ynn_reduce_sum, 1747, 5968, {2}, true);
  g->ShapeProduct(1747, 5967, {2});
  g->Binary(ynn_binary_divide, 5968, 5967, 1748);
  g->Binary(ynn_binary_add, 1748, 6539, 1749);
  g->Unary(ynn_unary_rsqrt, 1749, 1750);
  g->Binary(ynn_binary_multiply, 1746, 1750, 1751);
  g->Binary(ynn_binary_multiply, 1751, 6825, 1752);
  g->Quantize(1752, 1753, 0.019696271046996117, 0);
  g->Transpose(6819, 4562, {1,0});
  g->Binary(ynn_binary_multiply, 4559, 4561, 4557);
  g->Dot(1753, 4562, YNN_INVALID_VALUE_ID, 4556, 1);
  g->DequantizeTensor(4556, YNN_INVALID_VALUE_ID, 4557, 4558);
  g->QuantizeTensor(4558, 6504, 4560, 1755);
  g->Dequantize(1755, 1756, 0.024114182218909264, 0);
  g->Transpose(6818, 4567, {1,0});
  g->Binary(ynn_binary_multiply, 4559, 4566, 4564);
  g->Dot(1753, 4567, YNN_INVALID_VALUE_ID, 4563, 1);
  g->DequantizeTensor(4563, YNN_INVALID_VALUE_ID, 4564, 4565);
  g->QuantizeTensor(4565, 6504, 4560, 1757);
  g->Dequantize(1757, 1758, 0.024114182218909264, 0);
  g->Polynomial(1758, 5973, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5973, 5974);
  g->Binary(ynn_binary_add, 5974, 5500, 5971);
  g->Binary(ynn_binary_multiply, 1758, 5498, 5972);
  g->Binary(ynn_binary_multiply, 5972, 5971, 1759);
  g->Binary(ynn_binary_multiply, 1756, 1759, 1760);
  g->Quantize(1760, 1761, 0.03567914664745331, 0);
  g->Transpose(6817, 4574, {1,0});
  g->Binary(ynn_binary_multiply, 4571, 4573, 4569);
  g->Dot(1761, 4574, YNN_INVALID_VALUE_ID, 4568, 1);
  g->DequantizeTensor(4568, YNN_INVALID_VALUE_ID, 4569, 4570);
  g->QuantizeTensor(4570, 6504, 4572, 1762);
  g->Dequantize(1762, 1763, 0.05007796362042427, 0);
  g->Unary(ynn_unary_square, 1763, 1765);
  g->Reduce(ynn_reduce_sum, 1765, 5976, {2}, true);
  g->ShapeProduct(1765, 5975, {2});
  g->Binary(ynn_binary_divide, 5976, 5975, 1766);
  g->Binary(ynn_binary_add, 1766, 6539, 1767);
  g->Unary(ynn_unary_rsqrt, 1767, 1768);
  g->Binary(ynn_binary_multiply, 1763, 1768, 1769);
  g->Binary(ynn_binary_multiply, 1769, 6823, 1770);
  g->Binary(ynn_binary_add, 1770, 1746, 1771);
}

// Scope: "Layer22 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(427, 1772, {0,0,22,0}, {-1,-1,1,-1});
  g->Reshape(1772, 1773, {1,1,256});
  g->Unary(ynn_unary_square, 1773, 1774);
  g->Reduce(ynn_reduce_sum, 1774, 5978, {2}, true);
  g->ShapeProduct(1774, 5977, {2});
  g->Binary(ynn_binary_divide, 5978, 5977, 1776);
  g->Binary(ynn_binary_add, 1776, 6539, 1777);
  g->Unary(ynn_unary_rsqrt, 1777, 1778);
  g->Binary(ynn_binary_multiply, 1773, 1778, 1779);
  g->Binary(ynn_binary_multiply, 1779, 7118, 1780);
  g->Binary(ynn_binary_multiply, 7134, 6542, 1781);
  g->Binary(ynn_binary_add, 1780, 1781, 1782);
  g->Binary(ynn_binary_multiply, 1782, 6536, 1783);
  g->Quantize(1771, 1784, 0.15015320479869843, 0);
  g->Transpose(6820, 4581, {1,0});
  g->Binary(ynn_binary_multiply, 4578, 4580, 4576);
  g->Dot(1784, 4581, YNN_INVALID_VALUE_ID, 4575, 1);
  g->DequantizeTensor(4575, YNN_INVALID_VALUE_ID, 4576, 4577);
  g->QuantizeTensor(4577, 6504, 4579, 1785);
  g->Dequantize(1785, 1787, 0.06102363392710686, 0);
  g->Polynomial(1787, 5981, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5981, 5982);
  g->Binary(ynn_binary_add, 5982, 5500, 5979);
  g->Binary(ynn_binary_multiply, 1787, 5498, 5980);
  g->Binary(ynn_binary_multiply, 5980, 5979, 1788);
  g->Binary(ynn_binary_multiply, 1788, 1783, 1789);
  g->Quantize(1789, 1790, 0.3779527544975281, 0);
  g->Transpose(6821, 4588, {1,0});
  g->Binary(ynn_binary_multiply, 4585, 4587, 4583);
  g->Dot(1790, 4588, YNN_INVALID_VALUE_ID, 4582, 1);
  g->DequantizeTensor(4582, YNN_INVALID_VALUE_ID, 4583, 4584);
  g->QuantizeTensor(4584, 6504, 4586, 1791);
  g->Dequantize(1791, 1792, 0.11902644485235214, 0);
  g->Unary(ynn_unary_square, 1792, 1793);
  g->Reduce(ynn_reduce_sum, 1793, 5984, {2}, true);
  g->ShapeProduct(1793, 5983, {2});
  g->Binary(ynn_binary_divide, 5984, 5983, 1794);
  g->Binary(ynn_binary_add, 1794, 6539, 1795);
  g->Unary(ynn_unary_rsqrt, 1795, 1796);
  g->Binary(ynn_binary_multiply, 1792, 1796, 1798);
  g->Binary(ynn_binary_multiply, 1798, 6824, 1799);
  g->Binary(ynn_binary_add, 1771, 1799, 1800);
  g->Binary(ynn_binary_multiply, 1800, 6816, 1801);
}

// Scope: "Layer22"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22(Context& ctx) {
  BuildLayer22Attention(ctx);
  BuildLayer22Mlp(ctx);
  BuildLayer22PerLayerEmbedding(ctx);
}

// Scope: "Layer23 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(1807, 1809, 0.17847737669944763, 0);
  g->Transpose(6842, 4595, {1,0});
  g->Binary(ynn_binary_multiply, 4592, 4594, 4590);
  g->Dot(1809, 4595, YNN_INVALID_VALUE_ID, 4589, 1);
  g->DequantizeTensor(4589, YNN_INVALID_VALUE_ID, 4590, 4591);
  g->QuantizeTensor(4591, 6504, 4593, 1810);
  g->Dequantize(1810, 1811, 0.16338583827018738, 0);
  g->SplitDim(1811, 1812, 2, {8,256});
  g->FuseDims(1812, 1814, 1, 2);
  g->SplitDim(1814, 1813, 1, {8,1});
  g->Unary(ynn_unary_square, 1813, 1815);
  g->Reduce(ynn_reduce_sum, 1815, 5988, {3}, true);
  g->ShapeProduct(1815, 5987, {3});
  g->Binary(ynn_binary_divide, 5988, 5987, 1816);
  g->Binary(ynn_binary_add, 1816, 6539, 1817);
  g->Unary(ynn_unary_rsqrt, 1817, 1818);
  g->Binary(ynn_binary_multiply, 1813, 1818, 1819);
  g->Binary(ynn_binary_multiply, 1819, 6841, 1821);
  g->Slice(1821, 1822, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1821, 1823, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1823, 1824);
  g->Concat({1824,1822}, 1825, 3);
  g->Binary(ynn_binary_multiply, 1821, 3067, 1826);
  g->Binary(ynn_binary_multiply, 1825, 3172, 1827);
  g->Binary(ynn_binary_add, 1826, 1827, 1828);
}

// Scope: "Layer23 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7190, 1829, 0.0059552486054599285, 0);
  g->Dequantize(7205, 1830, 0.047244105488061905, 0);
  g->Matmul(1828, 1829, 1832, false, true);
  g->Mask(1832, 6561, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6561, 5992, {-1}, true);
  g->Binary(ynn_binary_subtract, 6561, 5992, 5989);
  g->Unary(ynn_unary_exp, 5989, 5990);
  g->Reduce(ynn_reduce_sum, 5990, 5993, {-1}, true);
  g->Binary(ynn_binary_divide, 5500, 5993, 5991);
  g->Binary(ynn_binary_multiply, 5990, 5991, 1833);
  g->Matmul(1833, 1830, 1834, false, false);
}

// Scope: "Layer23 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(1834, 1836, 1, 2);
  g->SplitDim(1836, 1835, 1, {1,8});
  g->FuseDims(1835, 1837, 2, 2);
  g->Quantize(1837, 1838, 0.02436024509370327, 0);
  g->Transpose(6840, 4601, {1,0});
  g->Binary(ynn_binary_multiply, 4179, 4600, 4597);
  g->Dot(1838, 4601, YNN_INVALID_VALUE_ID, 4596, 1);
  g->DequantizeTensor(4596, YNN_INVALID_VALUE_ID, 4597, 4598);
  g->QuantizeTensor(4598, 6504, 4599, 1839);
  g->Dequantize(1839, 1840, 0.027484547346830368, 0);
}

// Scope: "Layer23 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1801, 1802);
  g->Reduce(ynn_reduce_sum, 1802, 5986, {2}, true);
  g->ShapeProduct(1802, 5985, {2});
  g->Binary(ynn_binary_divide, 5986, 5985, 1803);
  g->Binary(ynn_binary_add, 1803, 6539, 1804);
  g->Unary(ynn_unary_rsqrt, 1804, 1805);
  g->Binary(ynn_binary_multiply, 1801, 1805, 1806);
  g->Binary(ynn_binary_multiply, 1806, 6829, 1807);
  BuildLayer23AttentionQueryProjection(ctx);
  BuildLayer23AttentionSdpa(ctx);
  BuildLayer23AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1840, 1841);
  g->Reduce(ynn_reduce_sum, 1841, 5999, {2}, true);
  g->ShapeProduct(1841, 5998, {2});
  g->Binary(ynn_binary_divide, 5999, 5998, 1844);
  g->Binary(ynn_binary_add, 1844, 6539, 1845);
  g->Unary(ynn_unary_rsqrt, 1845, 1846);
  g->Binary(ynn_binary_multiply, 1840, 1846, 1847);
  g->Binary(ynn_binary_multiply, 1847, 6836, 1848);
  g->Binary(ynn_binary_add, 1848, 1801, 1849);
}

// Scope: "Layer23 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1849, 1850);
  g->Reduce(ynn_reduce_sum, 1850, 6001, {2}, true);
  g->ShapeProduct(1850, 6000, {2});
  g->Binary(ynn_binary_divide, 6001, 6000, 1851);
  g->Binary(ynn_binary_add, 1851, 6539, 1852);
  g->Unary(ynn_unary_rsqrt, 1852, 1853);
  g->Binary(ynn_binary_multiply, 1849, 1853, 1855);
  g->Binary(ynn_binary_multiply, 1855, 6839, 1856);
  g->Quantize(1856, 1857, 0.02338595874607563, 0);
  g->Transpose(6833, 4608, {1,0});
  g->Binary(ynn_binary_multiply, 4605, 4607, 4603);
  g->Dot(1857, 4608, YNN_INVALID_VALUE_ID, 4602, 1);
  g->DequantizeTensor(4602, YNN_INVALID_VALUE_ID, 4603, 4604);
  g->QuantizeTensor(4604, 6504, 4606, 1858);
  g->Dequantize(1858, 1859, 0.03100394643843174, 0);
  g->Transpose(6832, 4613, {1,0});
  g->Binary(ynn_binary_multiply, 4605, 4612, 4610);
  g->Dot(1857, 4613, YNN_INVALID_VALUE_ID, 4609, 1);
  g->DequantizeTensor(4609, YNN_INVALID_VALUE_ID, 4610, 4611);
  g->QuantizeTensor(4611, 6504, 4606, 1860);
  g->Dequantize(1860, 1861, 0.03100394643843174, 0);
  g->Polynomial(1861, 6004, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6004, 6005);
  g->Binary(ynn_binary_add, 6005, 5500, 6002);
  g->Binary(ynn_binary_multiply, 1861, 5498, 6003);
  g->Binary(ynn_binary_multiply, 6003, 6002, 1862);
  g->Binary(ynn_binary_multiply, 1859, 1862, 1863);
  g->Quantize(1863, 1865, 0.0433070994913578, 0);
  g->Transpose(6831, 4620, {1,0});
  g->Binary(ynn_binary_multiply, 4617, 4619, 4615);
  g->Dot(1865, 4620, YNN_INVALID_VALUE_ID, 4614, 1);
  g->DequantizeTensor(4614, YNN_INVALID_VALUE_ID, 4615, 4616);
  g->QuantizeTensor(4616, 6504, 4618, 1866);
  g->Dequantize(1866, 1867, 0.025599855929613113, 0);
  g->Unary(ynn_unary_square, 1867, 1868);
  g->Reduce(ynn_reduce_sum, 1868, 6007, {2}, true);
  g->ShapeProduct(1868, 6006, {2});
  g->Binary(ynn_binary_divide, 6007, 6006, 1869);
  g->Binary(ynn_binary_add, 1869, 6539, 1870);
  g->Unary(ynn_unary_rsqrt, 1870, 1871);
  g->Binary(ynn_binary_multiply, 1867, 1871, 1872);
  g->Binary(ynn_binary_multiply, 1872, 6837, 1873);
  g->Binary(ynn_binary_add, 1873, 1849, 1874);
}

// Scope: "Layer23 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(427, 1876, {0,0,23,0}, {-1,-1,1,-1});
  g->Reshape(1876, 1877, {1,1,256});
  g->Unary(ynn_unary_square, 1877, 1878);
  g->Reduce(ynn_reduce_sum, 1878, 6009, {2}, true);
  g->ShapeProduct(1878, 6008, {2});
  g->Binary(ynn_binary_divide, 6009, 6008, 1879);
  g->Binary(ynn_binary_add, 1879, 6539, 1880);
  g->Unary(ynn_unary_rsqrt, 1880, 1881);
  g->Binary(ynn_binary_multiply, 1877, 1881, 1882);
  g->Binary(ynn_binary_multiply, 1882, 7118, 1883);
  g->Binary(ynn_binary_multiply, 7135, 6542, 1884);
  g->Binary(ynn_binary_add, 1883, 1884, 1885);
  g->Binary(ynn_binary_multiply, 1885, 6536, 1887);
  g->Quantize(1874, 1888, 0.1760360449552536, 0);
  g->Transpose(6834, 4627, {1,0});
  g->Binary(ynn_binary_multiply, 4624, 4626, 4622);
  g->Dot(1888, 4627, YNN_INVALID_VALUE_ID, 4621, 1);
  g->DequantizeTensor(4621, YNN_INVALID_VALUE_ID, 4622, 4623);
  g->QuantizeTensor(4623, 6504, 4625, 1889);
  g->Dequantize(1889, 1890, 0.07775591313838959, 0);
  g->Polynomial(1890, 6012, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6012, 6013);
  g->Binary(ynn_binary_add, 6013, 5500, 6010);
  g->Binary(ynn_binary_multiply, 1890, 5498, 6011);
  g->Binary(ynn_binary_multiply, 6011, 6010, 1891);
  g->Binary(ynn_binary_multiply, 1891, 1887, 1892);
  g->Quantize(1892, 1893, 0.3799212574958801, 0);
  g->Transpose(6835, 4634, {1,0});
  g->Binary(ynn_binary_multiply, 4631, 4633, 4629);
  g->Dot(1893, 4634, YNN_INVALID_VALUE_ID, 4628, 1);
  g->DequantizeTensor(4628, YNN_INVALID_VALUE_ID, 4629, 4630);
  g->QuantizeTensor(4630, 6504, 4632, 1894);
  g->Dequantize(1894, 1895, 0.08570276200771332, 0);
  g->Unary(ynn_unary_square, 1895, 1896);
  g->Reduce(ynn_reduce_sum, 1896, 6015, {2}, true);
  g->ShapeProduct(1896, 6014, {2});
  g->Binary(ynn_binary_divide, 6015, 6014, 1898);
  g->Binary(ynn_binary_add, 1898, 6539, 1899);
  g->Unary(ynn_unary_rsqrt, 1899, 1900);
  g->Binary(ynn_binary_multiply, 1895, 1900, 1901);
  g->Binary(ynn_binary_multiply, 1901, 6838, 1902);
  g->Binary(ynn_binary_add, 1874, 1902, 1903);
  g->Binary(ynn_binary_multiply, 1903, 6830, 1904);
}

// Scope: "Layer23"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23(Context& ctx) {
  BuildLayer23Attention(ctx);
  BuildLayer23Mlp(ctx);
  BuildLayer23PerLayerEmbedding(ctx);
}

// Scope: "Layer24 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer24AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(1911, 1912, 0.10295870155096054, 0);
  g->Transpose(6856, 4648, {1,0});
  g->Binary(ynn_binary_multiply, 4645, 4647, 4643);
  g->Dot(1912, 4648, YNN_INVALID_VALUE_ID, 4642, 1);
  g->DequantizeTensor(4642, YNN_INVALID_VALUE_ID, 4643, 4644);
  g->QuantizeTensor(4644, 6504, 4646, 1913);
  g->Dequantize(1913, 1914, 0.1919291466474533, 0);
  g->SplitDim(1914, 1915, 2, {8,512});
  g->FuseDims(1915, 1917, 1, 2);
  g->SplitDim(1917, 1916, 1, {8,1});
  g->Unary(ynn_unary_square, 1916, 1918);
  g->Reduce(ynn_reduce_sum, 1918, 6019, {3}, true);
  g->ShapeProduct(1918, 6018, {3});
  g->Binary(ynn_binary_divide, 6019, 6018, 1919);
  g->Binary(ynn_binary_add, 1919, 6539, 1921);
  g->Unary(ynn_unary_rsqrt, 1921, 1922);
  g->Binary(ynn_binary_multiply, 1916, 1922, 1923);
  g->Binary(ynn_binary_multiply, 1923, 6855, 1924);
  g->Slice(1924, 1925, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(1924, 1926, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 1926, 1927);
  g->Concat({1927,1925}, 1928, 3);
  g->Binary(ynn_binary_multiply, 1924, 3594, 1929);
  g->Binary(ynn_binary_multiply, 1928, 2, 1930);
  g->Binary(ynn_binary_add, 1929, 1930, 1932);
}

// Scope: "Layer24 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer24AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7191, 1933, 0.001091228099539876, 0);
  g->Dequantize(7206, 1934, 0.01785714365541935, 0);
  g->Matmul(1932, 1933, 1935, false, true);
  g->Mask(1935, 6562, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 6562, 6023, {-1}, true);
  g->Binary(ynn_binary_subtract, 6562, 6023, 6020);
  g->Unary(ynn_unary_exp, 6020, 6021);
  g->Reduce(ynn_reduce_sum, 6021, 6024, {-1}, true);
  g->Binary(ynn_binary_divide, 5500, 6024, 6022);
  g->Binary(ynn_binary_multiply, 6021, 6022, 1936);
  g->Matmul(1936, 1934, 1937, false, false);
}

// Scope: "Layer24 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer24AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(1937, 1939, 1, 2);
  g->SplitDim(1939, 1938, 1, {1,8});
  g->FuseDims(1938, 1940, 2, 2);
  g->Quantize(1940, 1941, 0.01457924209535122, 0);
  g->Transpose(6854, 4654, {1,0});
  g->Binary(ynn_binary_multiply, 4140, 4653, 4650);
  g->Dot(1941, 4654, YNN_INVALID_VALUE_ID, 4649, 1);
  g->DequantizeTensor(4649, YNN_INVALID_VALUE_ID, 4650, 4651);
  g->QuantizeTensor(4651, 6504, 4652, 1943);
  g->Dequantize(1943, 1944, 0.02337142638862133, 0);
}

// Scope: "Layer24 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer24Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1904, 1905);
  g->Reduce(ynn_reduce_sum, 1905, 6017, {2}, true);
  g->ShapeProduct(1905, 6016, {2});
  g->Binary(ynn_binary_divide, 6017, 6016, 1906);
  g->Binary(ynn_binary_add, 1906, 6539, 1907);
  g->Unary(ynn_unary_rsqrt, 1907, 1909);
  g->Binary(ynn_binary_multiply, 1904, 1909, 1910);
  g->Binary(ynn_binary_multiply, 1910, 6843, 1911);
  BuildLayer24AttentionQueryProjection(ctx);
  BuildLayer24AttentionSdpa(ctx);
  BuildLayer24AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1944, 1945);
  g->Reduce(ynn_reduce_sum, 1945, 6026, {2}, true);
  g->ShapeProduct(1945, 6025, {2});
  g->Binary(ynn_binary_divide, 6026, 6025, 1946);
  g->Binary(ynn_binary_add, 1946, 6539, 1947);
  g->Unary(ynn_unary_rsqrt, 1947, 1948);
  g->Binary(ynn_binary_multiply, 1944, 1948, 1949);
  g->Binary(ynn_binary_multiply, 1949, 6850, 1950);
  g->Binary(ynn_binary_add, 1950, 1904, 1951);
}

// Scope: "Layer24 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer24Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1951, 1952);
  g->Reduce(ynn_reduce_sum, 1952, 6028, {2}, true);
  g->ShapeProduct(1952, 6027, {2});
  g->Binary(ynn_binary_divide, 6028, 6027, 1955);
  g->Binary(ynn_binary_add, 1955, 6539, 1956);
  g->Unary(ynn_unary_rsqrt, 1956, 1957);
  g->Binary(ynn_binary_multiply, 1951, 1957, 1958);
  g->Binary(ynn_binary_multiply, 1958, 6853, 1959);
  g->Quantize(1959, 1960, 0.018518447875976562, 0);
  g->Transpose(6847, 4661, {1,0});
  g->Binary(ynn_binary_multiply, 4658, 4660, 4656);
  g->Dot(1960, 4661, YNN_INVALID_VALUE_ID, 4655, 1);
  g->DequantizeTensor(4655, YNN_INVALID_VALUE_ID, 4656, 4657);
  g->QuantizeTensor(4657, 6504, 4659, 1961);
  g->Dequantize(1961, 1962, 0.027313001453876495, 0);
  g->Transpose(6846, 4666, {1,0});
  g->Binary(ynn_binary_multiply, 4658, 4665, 4663);
  g->Dot(1960, 4666, YNN_INVALID_VALUE_ID, 4662, 1);
  g->DequantizeTensor(4662, YNN_INVALID_VALUE_ID, 4663, 4664);
  g->QuantizeTensor(4664, 6504, 4659, 1963);
  g->Dequantize(1963, 1965, 0.027313001453876495, 0);
  g->Polynomial(1965, 6033, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6033, 6034);
  g->Binary(ynn_binary_add, 6034, 5500, 6031);
  g->Binary(ynn_binary_multiply, 1965, 5498, 6032);
  g->Binary(ynn_binary_multiply, 6032, 6031, 1966);
  g->Binary(ynn_binary_multiply, 1962, 1966, 1967);
  g->Quantize(1967, 1968, 0.01894685998558998, 0);
  g->Transpose(6845, 4673, {1,0});
  g->Binary(ynn_binary_multiply, 4670, 4672, 4668);
  g->Dot(1968, 4673, YNN_INVALID_VALUE_ID, 4667, 1);
  g->DequantizeTensor(4667, YNN_INVALID_VALUE_ID, 4668, 4669);
  g->QuantizeTensor(4669, 6504, 4671, 1969);
  g->Dequantize(1969, 1970, 0.009169002994894981, 0);
  g->Unary(ynn_unary_square, 1970, 1971);
  g->Reduce(ynn_reduce_sum, 1971, 6036, {2}, true);
  g->ShapeProduct(1971, 6035, {2});
  g->Binary(ynn_binary_divide, 6036, 6035, 1972);
  g->Binary(ynn_binary_add, 1972, 6539, 1973);
  g->Unary(ynn_unary_rsqrt, 1973, 1974);
  g->Binary(ynn_binary_multiply, 1970, 1974, 1976);
  g->Binary(ynn_binary_multiply, 1976, 6851, 1977);
  g->Binary(ynn_binary_add, 1977, 1951, 1978);
}

// Scope: "Layer24 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer24PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(427, 1979, {0,0,24,0}, {-1,-1,1,-1});
  g->Reshape(1979, 1980, {1,1,256});
  g->Unary(ynn_unary_square, 1980, 1981);
  g->Reduce(ynn_reduce_sum, 1981, 6038, {2}, true);
  g->ShapeProduct(1981, 6037, {2});
  g->Binary(ynn_binary_divide, 6038, 6037, 1982);
  g->Binary(ynn_binary_add, 1982, 6539, 1983);
  g->Unary(ynn_unary_rsqrt, 1983, 1984);
  g->Binary(ynn_binary_multiply, 1980, 1984, 1985);
  g->Binary(ynn_binary_multiply, 1985, 7118, 1987);
  g->Binary(ynn_binary_multiply, 7136, 6542, 1988);
  g->Binary(ynn_binary_add, 1987, 1988, 1989);
  g->Binary(ynn_binary_multiply, 1989, 6536, 1990);
  g->Quantize(1978, 1991, 0.1741907149553299, 0);
  g->Transpose(6848, 4680, {1,0});
  g->Binary(ynn_binary_multiply, 4677, 4679, 4675);
  g->Dot(1991, 4680, YNN_INVALID_VALUE_ID, 4674, 1);
  g->DequantizeTensor(4674, YNN_INVALID_VALUE_ID, 4675, 4676);
  g->QuantizeTensor(4676, 6504, 4678, 1992);
  g->Dequantize(1992, 1993, 0.08710630983114243, 0);
  g->Polynomial(1993, 6041, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6041, 6042);
  g->Binary(ynn_binary_add, 6042, 5500, 6039);
  g->Binary(ynn_binary_multiply, 1993, 5498, 6040);
  g->Binary(ynn_binary_multiply, 6040, 6039, 1994);
  g->Binary(ynn_binary_multiply, 1994, 1990, 1995);
  g->Quantize(1995, 1996, 1.0236220359802246, 0);
  g->Transpose(6849, 4687, {1,0});
  g->Binary(ynn_binary_multiply, 4684, 4686, 4682);
  g->Dot(1996, 4687, YNN_INVALID_VALUE_ID, 4681, 1);
  g->DequantizeTensor(4681, YNN_INVALID_VALUE_ID, 4682, 4683);
  g->QuantizeTensor(4683, 6504, 4685, 1998);
  g->Dequantize(1998, 1999, 0.1628752052783966, 0);
  g->Unary(ynn_unary_square, 1999, 2000);
  g->Reduce(ynn_reduce_sum, 2000, 6044, {2}, true);
  g->ShapeProduct(2000, 6043, {2});
  g->Binary(ynn_binary_divide, 6044, 6043, 2001);
  g->Binary(ynn_binary_add, 2001, 6539, 2002);
  g->Unary(ynn_unary_rsqrt, 2002, 2003);
  g->Binary(ynn_binary_multiply, 1999, 2003, 2004);
  g->Binary(ynn_binary_multiply, 2004, 6852, 2005);
  g->Binary(ynn_binary_add, 1978, 2005, 2006);
  g->Binary(ynn_binary_multiply, 2006, 6844, 2007);
}

// Scope: "Layer24"
LAB_YNN_BUILDER_NOINLINE void BuildLayer24(Context& ctx) {
  BuildLayer24Attention(ctx);
  BuildLayer24Mlp(ctx);
  BuildLayer24PerLayerEmbedding(ctx);
}

// Scope: "Layer25 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer25AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(2014, 2015, 0.1674470156431198, 0);
  g->Transpose(6870, 4694, {1,0});
  g->Binary(ynn_binary_multiply, 4691, 4693, 4689);
  g->Dot(2015, 4694, YNN_INVALID_VALUE_ID, 4688, 1);
  g->DequantizeTensor(4688, YNN_INVALID_VALUE_ID, 4689, 4690);
  g->QuantizeTensor(4690, 6504, 4692, 2016);
  g->Dequantize(2016, 2017, 0.15452757477760315, 0);
  g->SplitDim(2017, 2018, 2, {8,256});
  g->FuseDims(2018, 2021, 1, 2);
  g->SplitDim(2021, 2020, 1, {8,1});
  g->Unary(ynn_unary_square, 2020, 2022);
  g->Reduce(ynn_reduce_sum, 2022, 6048, {3}, true);
  g->ShapeProduct(2022, 6047, {3});
  g->Binary(ynn_binary_divide, 6048, 6047, 2023);
  g->Binary(ynn_binary_add, 2023, 6539, 2024);
  g->Unary(ynn_unary_rsqrt, 2024, 2025);
  g->Binary(ynn_binary_multiply, 2020, 2025, 2026);
  g->Binary(ynn_binary_multiply, 2026, 6869, 2027);
  g->Slice(2027, 2028, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2027, 2029, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2029, 2030);
  g->Concat({2030,2028}, 2032, 3);
  g->Binary(ynn_binary_multiply, 2027, 3067, 2033);
  g->Binary(ynn_binary_multiply, 2032, 3172, 2034);
  g->Binary(ynn_binary_add, 2033, 2034, 2035);
}

// Scope: "Layer25 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer25AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7190, 2036, 0.0059552486054599285, 0);
  g->Dequantize(7205, 2037, 0.047244105488061905, 0);
  g->Matmul(2035, 2036, 2038, false, true);
  g->Mask(2038, 6563, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6563, 6052, {-1}, true);
  g->Binary(ynn_binary_subtract, 6563, 6052, 6049);
  g->Unary(ynn_unary_exp, 6049, 6050);
  g->Reduce(ynn_reduce_sum, 6050, 6053, {-1}, true);
  g->Binary(ynn_binary_divide, 5500, 6053, 6051);
  g->Binary(ynn_binary_multiply, 6050, 6051, 2039);
  g->Matmul(2039, 2037, 2040, false, false);
}

// Scope: "Layer25 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer25AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(2040, 2043, 1, 2);
  g->SplitDim(2043, 2042, 1, {1,8});
  g->FuseDims(2042, 2044, 2, 2);
  g->Quantize(2044, 2045, 0.02325296215713024, 0);
  g->Transpose(6868, 4700, {1,0});
  g->Binary(ynn_binary_multiply, 4288, 4699, 4696);
  g->Dot(2045, 4700, YNN_INVALID_VALUE_ID, 4695, 1);
  g->DequantizeTensor(4695, YNN_INVALID_VALUE_ID, 4696, 4697);
  g->QuantizeTensor(4697, 6504, 4698, 2046);
  g->Dequantize(2046, 2047, 0.040348730981349945, 0);
}

// Scope: "Layer25 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer25Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2007, 2009);
  g->Reduce(ynn_reduce_sum, 2009, 6046, {2}, true);
  g->ShapeProduct(2009, 6045, {2});
  g->Binary(ynn_binary_divide, 6046, 6045, 2010);
  g->Binary(ynn_binary_add, 2010, 6539, 2011);
  g->Unary(ynn_unary_rsqrt, 2011, 2012);
  g->Binary(ynn_binary_multiply, 2007, 2012, 2013);
  g->Binary(ynn_binary_multiply, 2013, 6857, 2014);
  BuildLayer25AttentionQueryProjection(ctx);
  BuildLayer25AttentionSdpa(ctx);
  BuildLayer25AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2047, 2048);
  g->Reduce(ynn_reduce_sum, 2048, 6055, {2}, true);
  g->ShapeProduct(2048, 6054, {2});
  g->Binary(ynn_binary_divide, 6055, 6054, 2049);
  g->Binary(ynn_binary_add, 2049, 6539, 2050);
  g->Unary(ynn_unary_rsqrt, 2050, 2051);
  g->Binary(ynn_binary_multiply, 2047, 2051, 2052);
  g->Binary(ynn_binary_multiply, 2052, 6864, 2054);
  g->Binary(ynn_binary_add, 2054, 2007, 2055);
}

// Scope: "Layer25 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer25Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2055, 2056);
  g->Reduce(ynn_reduce_sum, 2056, 6057, {2}, true);
  g->ShapeProduct(2056, 6056, {2});
  g->Binary(ynn_binary_divide, 6057, 6056, 2057);
  g->Binary(ynn_binary_add, 2057, 6539, 2058);
  g->Unary(ynn_unary_rsqrt, 2058, 2059);
  g->Binary(ynn_binary_multiply, 2055, 2059, 2060);
  g->Binary(ynn_binary_multiply, 2060, 6867, 2061);
  g->Quantize(2061, 2062, 0.02161904238164425, 0);
  g->Transpose(6861, 4706, {1,0});
  g->Binary(ynn_binary_multiply, 4704, 4705, 4702);
  g->Dot(2062, 4706, YNN_INVALID_VALUE_ID, 4701, 1);
  g->DequantizeTensor(4701, YNN_INVALID_VALUE_ID, 4702, 4703);
  g->QuantizeTensor(4703, 6504, 4360, 2063);
  g->Dequantize(2063, 2066, 0.03297245129942894, 0);
  g->Transpose(6860, 4711, {1,0});
  g->Binary(ynn_binary_multiply, 4704, 4710, 4708);
  g->Dot(2062, 4711, YNN_INVALID_VALUE_ID, 4707, 1);
  g->DequantizeTensor(4707, YNN_INVALID_VALUE_ID, 4708, 4709);
  g->QuantizeTensor(4709, 6504, 4360, 2067);
  g->Dequantize(2067, 2068, 0.03297245129942894, 0);
  g->Polynomial(2068, 6060, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6060, 6061);
  g->Binary(ynn_binary_add, 6061, 5500, 6058);
  g->Binary(ynn_binary_multiply, 2068, 5498, 6059);
  g->Binary(ynn_binary_multiply, 6059, 6058, 2069);
  g->Binary(ynn_binary_multiply, 2066, 2069, 2070);
  g->Quantize(2070, 2071, 0.032726388424634933, 0);
  g->Transpose(6859, 4718, {1,0});
  g->Binary(ynn_binary_multiply, 4715, 4717, 4713);
  g->Dot(2071, 4718, YNN_INVALID_VALUE_ID, 4712, 1);
  g->DequantizeTensor(4712, YNN_INVALID_VALUE_ID, 4713, 4714);
  g->QuantizeTensor(4714, 6504, 4716, 2072);
  g->Dequantize(2072, 2073, 0.00990387424826622, 0);
  g->Unary(ynn_unary_square, 2073, 2074);
  g->Reduce(ynn_reduce_sum, 2074, 6063, {2}, true);
  g->ShapeProduct(2074, 6062, {2});
  g->Binary(ynn_binary_divide, 6063, 6062, 2076);
  g->Binary(ynn_binary_add, 2076, 6539, 2077);
  g->Unary(ynn_unary_rsqrt, 2077, 2078);
  g->Binary(ynn_binary_multiply, 2073, 2078, 2079);
  g->Binary(ynn_binary_multiply, 2079, 6865, 2080);
  g->Binary(ynn_binary_add, 2080, 2055, 2081);
}

// Scope: "Layer25 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer25PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(427, 2082, {0,0,25,0}, {-1,-1,1,-1});
  g->Reshape(2082, 2083, {1,1,256});
  g->Unary(ynn_unary_square, 2083, 2084);
  g->Reduce(ynn_reduce_sum, 2084, 6065, {2}, true);
  g->ShapeProduct(2084, 6064, {2});
  g->Binary(ynn_binary_divide, 6065, 6064, 2085);
  g->Binary(ynn_binary_add, 2085, 6539, 2087);
  g->Unary(ynn_unary_rsqrt, 2087, 2088);
  g->Binary(ynn_binary_multiply, 2083, 2088, 2089);
  g->Binary(ynn_binary_multiply, 2089, 7118, 2090);
  g->Binary(ynn_binary_multiply, 7137, 6542, 2091);
  g->Binary(ynn_binary_add, 2090, 2091, 2092);
  g->Binary(ynn_binary_multiply, 2092, 6536, 2093);
  g->Quantize(2081, 2094, 0.1164931058883667, 0);
  g->Transpose(6862, 4725, {1,0});
  g->Binary(ynn_binary_multiply, 4722, 4724, 4720);
  g->Dot(2094, 4725, YNN_INVALID_VALUE_ID, 4719, 1);
  g->DequantizeTensor(4719, YNN_INVALID_VALUE_ID, 4720, 4721);
  g->QuantizeTensor(4721, 6504, 4723, 2095);
  g->Dequantize(2095, 2096, 0.11269685626029968, 0);
  g->Polynomial(2096, 6068, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6068, 6069);
  g->Binary(ynn_binary_add, 6069, 5500, 6066);
  g->Binary(ynn_binary_multiply, 2096, 5498, 6067);
  g->Binary(ynn_binary_multiply, 6067, 6066, 2097);
  g->Binary(ynn_binary_multiply, 2097, 2093, 2098);
  g->Quantize(2098, 2099, 0.5157480239868164, 0);
  g->Transpose(6863, 4732, {1,0});
  g->Binary(ynn_binary_multiply, 4729, 4731, 4727);
  g->Dot(2099, 4732, YNN_INVALID_VALUE_ID, 4726, 1);
  g->DequantizeTensor(4726, YNN_INVALID_VALUE_ID, 4727, 4728);
  g->QuantizeTensor(4728, 6504, 4730, 2100);
  g->Dequantize(2100, 2101, 0.3825955092906952, 0);
  g->Unary(ynn_unary_square, 2101, 2102);
  g->Reduce(ynn_reduce_sum, 2102, 6071, {2}, true);
  g->ShapeProduct(2102, 6070, {2});
  g->Binary(ynn_binary_divide, 6071, 6070, 2103);
  g->Binary(ynn_binary_add, 2103, 6539, 2104);
  g->Unary(ynn_unary_rsqrt, 2104, 2105);
  g->Binary(ynn_binary_multiply, 2101, 2105, 2106);
  g->Binary(ynn_binary_multiply, 2106, 6866, 2108);
  g->Binary(ynn_binary_add, 2081, 2108, 2109);
  g->Binary(ynn_binary_multiply, 2109, 6858, 2110);
}

// Scope: "Layer25"
LAB_YNN_BUILDER_NOINLINE void BuildLayer25(Context& ctx) {
  BuildLayer25Attention(ctx);
  BuildLayer25Mlp(ctx);
  BuildLayer25PerLayerEmbedding(ctx);
}

}  // namespace BuildGemma4DecodeSource
