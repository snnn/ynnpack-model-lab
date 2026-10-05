// Generated YNNPACK builder; do not edit.
#include "gemma4_decode_builder.h"

namespace BuildGemma4DecodeSource {

// Scope: "Layer16 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(1107, 1108, 0.44548678398132324, 0);
  g->Transpose(6634, 4222, {1,0});
  g->Binary(ynn_binary_multiply, 4219, 4221, 4217);
  g->Dot(1108, 4222, YNN_INVALID_VALUE_ID, 4216, 1);
  g->DequantizeTensor(4216, YNN_INVALID_VALUE_ID, 4217, 4218);
  g->QuantizeTensor(4218, 6412, 4220, 1110);
  g->Dequantize(1110, 1111, 0.3641732335090637, 0);
  g->SplitDim(1111, 1112, 2, {8,256});
  g->FuseDims(1112, 1114, 1, 2);
  g->SplitDim(1114, 1113, 1, {8,1});
  g->Unary(ynn_unary_square, 1113, 1115);
  g->Reduce(ynn_reduce_sum, 1115, 5740, {3}, true);
  g->ShapeProduct(1115, 5739, {3});
  g->Binary(ynn_binary_divide, 5740, 5739, 1116);
  g->Binary(ynn_binary_add, 1116, 6446, 1117);
  g->Binary(ynn_binary_pow, 1117, 6448, 1118);
  g->Binary(ynn_binary_multiply, 1113, 1118, 1119);
  g->Convert(6633, 1120);
  g->Binary(ynn_binary_multiply, 1119, 1120, 1122);
  g->Slice(1122, 1123, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1122, 1124, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1124, 1125);
  g->Concat({1125,1123}, 1126, 3);
  g->Binary(ynn_binary_multiply, 1122, 2173, 1127);
  g->Binary(ynn_binary_multiply, 1126, 3050, 1128);
  g->Binary(ynn_binary_add, 1127, 1128, 1129);
}

// Scope: "Layer16 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(1129, 772, 1130, false, true);
  g->Mask(1130, 6461, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6461, 5744, {-1}, true);
  g->Binary(ynn_binary_subtract, 6461, 5744, 5741);
  g->Unary(ynn_unary_exp, 5741, 5742);
  g->Reduce(ynn_reduce_sum, 5742, 5745, {-1}, true);
  g->Binary(ynn_binary_divide, 5474, 5745, 5743);
  g->Binary(ynn_binary_multiply, 5742, 5743, 1132);
  g->Matmul(1132, 774, 1133, false, false);
}

// Scope: "Layer16 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(1133, 1135, 1, 2);
  g->SplitDim(1135, 1134, 1, {1,8});
  g->FuseDims(1134, 1136, 2, 2);
  g->Quantize(1136, 1137, 0.023745087906718254, 0);
  g->Transpose(6632, 4229, {1,0});
  g->Binary(ynn_binary_multiply, 4226, 4228, 4224);
  g->Dot(1137, 4229, YNN_INVALID_VALUE_ID, 4223, 1);
  g->DequantizeTensor(4223, YNN_INVALID_VALUE_ID, 4224, 4225);
  g->QuantizeTensor(4225, 6412, 4227, 1138);
  g->Dequantize(1138, 1139, 0.02639034017920494, 0);
}

// Scope: "Layer16 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1100, 1101);
  g->Reduce(ynn_reduce_sum, 1101, 5738, {2}, true);
  g->ShapeProduct(1101, 5737, {2});
  g->Binary(ynn_binary_divide, 5738, 5737, 1102);
  g->Binary(ynn_binary_add, 1102, 6446, 1103);
  g->Binary(ynn_binary_pow, 1103, 6448, 1104);
  g->Binary(ynn_binary_multiply, 1100, 1104, 1105);
  g->Convert(6621, 1106);
  g->Binary(ynn_binary_multiply, 1105, 1106, 1107);
  BuildLayer16AttentionQueryProjection(ctx);
  BuildLayer16AttentionSdpa(ctx);
  BuildLayer16AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1139, 1140);
  g->Reduce(ynn_reduce_sum, 1140, 5747, {2}, true);
  g->ShapeProduct(1140, 5746, {2});
  g->Binary(ynn_binary_divide, 5747, 5746, 1141);
  g->Binary(ynn_binary_add, 1141, 6446, 1142);
  g->Binary(ynn_binary_pow, 1142, 6448, 1144);
  g->Binary(ynn_binary_multiply, 1139, 1144, 1145);
  g->Convert(6628, 1146);
  g->Binary(ynn_binary_multiply, 1145, 1146, 1147);
  g->Binary(ynn_binary_add, 1100, 1147, 1148);
}

// Scope: "Layer16 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1148, 1149);
  g->Reduce(ynn_reduce_sum, 1149, 5749, {2}, true);
  g->ShapeProduct(1149, 5748, {2});
  g->Binary(ynn_binary_divide, 5749, 5748, 1150);
  g->Binary(ynn_binary_add, 1150, 6446, 1151);
  g->Binary(ynn_binary_pow, 1151, 6448, 1152);
  g->Binary(ynn_binary_multiply, 1148, 1152, 1153);
  g->Convert(6631, 1155);
  g->Binary(ynn_binary_multiply, 1153, 1155, 1156);
  g->Quantize(1156, 1157, 0.019740456715226173, 0);
  g->Transpose(6625, 4236, {1,0});
  g->Binary(ynn_binary_multiply, 4233, 4235, 4231);
  g->Dot(1157, 4236, YNN_INVALID_VALUE_ID, 4230, 1);
  g->DequantizeTensor(4230, YNN_INVALID_VALUE_ID, 4231, 4232);
  g->QuantizeTensor(4232, 6412, 4234, 1158);
  g->Dequantize(1158, 1159, 0.02042323723435402, 0);
  g->Transpose(6624, 4241, {1,0});
  g->Binary(ynn_binary_multiply, 4233, 4240, 4238);
  g->Dot(1157, 4241, YNN_INVALID_VALUE_ID, 4237, 1);
  g->DequantizeTensor(4237, YNN_INVALID_VALUE_ID, 4238, 4239);
  g->QuantizeTensor(4239, 6412, 4234, 1160);
  g->Dequantize(1160, 1161, 0.02042323723435402, 0);
  g->Polynomial(1161, 5752, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5752, 5753);
  g->Binary(ynn_binary_add, 5753, 5474, 5750);
  g->Binary(ynn_binary_multiply, 1161, 5472, 5751);
  g->Binary(ynn_binary_multiply, 5751, 5750, 1162);
  g->Binary(ynn_binary_multiply, 1159, 1162, 1163);
  g->Quantize(1163, 1165, 0.021530522033572197, 0);
  g->Transpose(6623, 4248, {1,0});
  g->Binary(ynn_binary_multiply, 4245, 4247, 4243);
  g->Dot(1165, 4248, YNN_INVALID_VALUE_ID, 4242, 1);
  g->DequantizeTensor(4242, YNN_INVALID_VALUE_ID, 4243, 4244);
  g->QuantizeTensor(4244, 6412, 4246, 1166);
  g->Dequantize(1166, 1167, 0.011490405537188053, 0);
  g->Unary(ynn_unary_square, 1167, 1168);
  g->Reduce(ynn_reduce_sum, 1168, 5755, {2}, true);
  g->ShapeProduct(1168, 5754, {2});
  g->Binary(ynn_binary_divide, 5755, 5754, 1169);
  g->Binary(ynn_binary_add, 1169, 6446, 1170);
  g->Binary(ynn_binary_pow, 1170, 6448, 1171);
  g->Binary(ynn_binary_multiply, 1167, 1171, 1172);
  g->Convert(6629, 1173);
  g->Binary(ynn_binary_multiply, 1172, 1173, 1174);
  g->Binary(ynn_binary_add, 1148, 1174, 1177);
}

// Scope: "Layer16 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1064, 1178, {0,0,16,0}, {-1,-1,1,-1});
  g->Reshape(1178, 1179, {1,1,256});
  g->Binary(ynn_binary_add, 1179, 7034, 1180);
  g->Binary(ynn_binary_multiply, 1180, 6444, 1181);
  g->Quantize(1177, 1182, 0.1693648248910904, 0);
  g->Transpose(6626, 4255, {1,0});
  g->Binary(ynn_binary_multiply, 4252, 4254, 4250);
  g->Dot(1182, 4255, YNN_INVALID_VALUE_ID, 4249, 1);
  g->DequantizeTensor(4249, YNN_INVALID_VALUE_ID, 4250, 4251);
  g->QuantizeTensor(4251, 6412, 4253, 1183);
  g->Dequantize(1183, 1184, 0.07234252989292145, 0);
  g->Polynomial(1184, 5758, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5758, 5759);
  g->Binary(ynn_binary_add, 5759, 5474, 5756);
  g->Binary(ynn_binary_multiply, 1184, 5472, 5757);
  g->Binary(ynn_binary_multiply, 5757, 5756, 1185);
  g->Binary(ynn_binary_multiply, 1185, 1181, 1186);
  g->Quantize(1186, 1188, 0.8779527544975281, 0);
  g->Transpose(6627, 4262, {1,0});
  g->Binary(ynn_binary_multiply, 4259, 4261, 4257);
  g->Dot(1188, 4262, YNN_INVALID_VALUE_ID, 4256, 1);
  g->DequantizeTensor(4256, YNN_INVALID_VALUE_ID, 4257, 4258);
  g->QuantizeTensor(4258, 6412, 4260, 1189);
  g->Dequantize(1189, 1190, 0.16087517142295837, 0);
  g->Unary(ynn_unary_square, 1190, 1191);
  g->Reduce(ynn_reduce_sum, 1191, 5761, {2}, true);
  g->ShapeProduct(1191, 5760, {2});
  g->Binary(ynn_binary_divide, 5761, 5760, 1192);
  g->Binary(ynn_binary_add, 1192, 6446, 1193);
  g->Binary(ynn_binary_pow, 1193, 6448, 1194);
  g->Binary(ynn_binary_multiply, 1190, 1194, 1195);
  g->Convert(6630, 1196);
  g->Binary(ynn_binary_multiply, 1195, 1196, 1197);
  g->Binary(ynn_binary_add, 1177, 1197, 1199);
  g->Convert(6622, 1200);
  g->Binary(ynn_binary_multiply, 1199, 1200, 1201);
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
  g->Quantize(1208, 1209, 0.25072598457336426, 0);
  g->Transpose(6648, 4269, {1,0});
  g->Binary(ynn_binary_multiply, 4266, 4268, 4264);
  g->Dot(1209, 4269, YNN_INVALID_VALUE_ID, 4263, 1);
  g->DequantizeTensor(4263, YNN_INVALID_VALUE_ID, 4264, 4265);
  g->QuantizeTensor(4265, 6412, 4267, 1210);
  g->Dequantize(1210, 1211, 0.374015748500824, 0);
  g->SplitDim(1211, 1212, 2, {8,256});
  g->FuseDims(1212, 1214, 1, 2);
  g->SplitDim(1214, 1213, 1, {8,1});
  g->Unary(ynn_unary_square, 1213, 1215);
  g->Reduce(ynn_reduce_sum, 1215, 5765, {3}, true);
  g->ShapeProduct(1215, 5764, {3});
  g->Binary(ynn_binary_divide, 5765, 5764, 1216);
  g->Binary(ynn_binary_add, 1216, 6446, 1217);
  g->Binary(ynn_binary_pow, 1217, 6448, 1218);
  g->Binary(ynn_binary_multiply, 1213, 1218, 1219);
  g->Convert(6647, 1221);
  g->Binary(ynn_binary_multiply, 1219, 1221, 1222);
  g->Slice(1222, 1223, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1222, 1224, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1224, 1225);
  g->Concat({1225,1223}, 1226, 3);
  g->Binary(ynn_binary_multiply, 1222, 2173, 1227);
  g->Binary(ynn_binary_multiply, 1226, 3050, 1228);
  g->Binary(ynn_binary_add, 1227, 1228, 1229);
}

// Scope: "Layer17 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(1229, 772, 1230, false, true);
  g->Mask(1230, 6462, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6462, 5774, {-1}, true);
  g->Binary(ynn_binary_subtract, 6462, 5774, 5771);
  g->Unary(ynn_unary_exp, 5771, 5772);
  g->Reduce(ynn_reduce_sum, 5772, 5775, {-1}, true);
  g->Binary(ynn_binary_divide, 5474, 5775, 5773);
  g->Binary(ynn_binary_multiply, 5772, 5773, 1232);
  g->Matmul(1232, 774, 1233, false, false);
}

// Scope: "Layer17 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(1233, 1235, 1, 2);
  g->SplitDim(1235, 1234, 1, {1,8});
  g->FuseDims(1234, 1236, 2, 2);
  g->Quantize(1236, 1237, 0.023375993594527245, 0);
  g->Transpose(6646, 4276, {1,0});
  g->Binary(ynn_binary_multiply, 4273, 4275, 4271);
  g->Dot(1237, 4276, YNN_INVALID_VALUE_ID, 4270, 1);
  g->DequantizeTensor(4270, YNN_INVALID_VALUE_ID, 4271, 4272);
  g->QuantizeTensor(4272, 6412, 4274, 1238);
  g->Dequantize(1238, 1239, 0.020179564133286476, 0);
}

// Scope: "Layer17 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1201, 1202);
  g->Reduce(ynn_reduce_sum, 1202, 5763, {2}, true);
  g->ShapeProduct(1202, 5762, {2});
  g->Binary(ynn_binary_divide, 5763, 5762, 1203);
  g->Binary(ynn_binary_add, 1203, 6446, 1204);
  g->Binary(ynn_binary_pow, 1204, 6448, 1205);
  g->Binary(ynn_binary_multiply, 1201, 1205, 1206);
  g->Convert(6635, 1207);
  g->Binary(ynn_binary_multiply, 1206, 1207, 1208);
  BuildLayer17AttentionQueryProjection(ctx);
  BuildLayer17AttentionSdpa(ctx);
  BuildLayer17AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1239, 1240);
  g->Reduce(ynn_reduce_sum, 1240, 5777, {2}, true);
  g->ShapeProduct(1240, 5776, {2});
  g->Binary(ynn_binary_divide, 5777, 5776, 1241);
  g->Binary(ynn_binary_add, 1241, 6446, 1244);
  g->Binary(ynn_binary_pow, 1244, 6448, 1245);
  g->Binary(ynn_binary_multiply, 1239, 1245, 1246);
  g->Convert(6642, 1247);
  g->Binary(ynn_binary_multiply, 1246, 1247, 1248);
  g->Binary(ynn_binary_add, 1201, 1248, 1249);
}

// Scope: "Layer17 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1249, 1250);
  g->Reduce(ynn_reduce_sum, 1250, 5779, {2}, true);
  g->ShapeProduct(1250, 5778, {2});
  g->Binary(ynn_binary_divide, 5779, 5778, 1251);
  g->Binary(ynn_binary_add, 1251, 6446, 1252);
  g->Binary(ynn_binary_pow, 1252, 6448, 1253);
  g->Binary(ynn_binary_multiply, 1249, 1253, 1255);
  g->Convert(6645, 1256);
  g->Binary(ynn_binary_multiply, 1255, 1256, 1257);
  g->Quantize(1257, 1258, 0.02002163790166378, 0);
  g->Transpose(6639, 4283, {1,0});
  g->Binary(ynn_binary_multiply, 4280, 4282, 4278);
  g->Dot(1258, 4283, YNN_INVALID_VALUE_ID, 4277, 1);
  g->DequantizeTensor(4277, YNN_INVALID_VALUE_ID, 4278, 4279);
  g->QuantizeTensor(4279, 6412, 4281, 1259);
  g->Dequantize(1259, 1260, 0.02325296215713024, 0);
  g->Transpose(6638, 4288, {1,0});
  g->Binary(ynn_binary_multiply, 4280, 4287, 4285);
  g->Dot(1258, 4288, YNN_INVALID_VALUE_ID, 4284, 1);
  g->DequantizeTensor(4284, YNN_INVALID_VALUE_ID, 4285, 4286);
  g->QuantizeTensor(4286, 6412, 4281, 1261);
  g->Dequantize(1261, 1262, 0.02325296215713024, 0);
  g->Polynomial(1262, 5782, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5782, 5783);
  g->Binary(ynn_binary_add, 5783, 5474, 5780);
  g->Binary(ynn_binary_multiply, 1262, 5472, 5781);
  g->Binary(ynn_binary_multiply, 5781, 5780, 1263);
  g->Binary(ynn_binary_multiply, 1260, 1263, 1265);
  g->Quantize(1265, 1266, 0.03641733527183533, 0);
  g->Transpose(6637, 4295, {1,0});
  g->Binary(ynn_binary_multiply, 4292, 4294, 4290);
  g->Dot(1266, 4295, YNN_INVALID_VALUE_ID, 4289, 1);
  g->DequantizeTensor(4289, YNN_INVALID_VALUE_ID, 4290, 4291);
  g->QuantizeTensor(4291, 6412, 4293, 1267);
  g->Dequantize(1267, 1268, 0.022161640226840973, 0);
  g->Unary(ynn_unary_square, 1268, 1269);
  g->Reduce(ynn_reduce_sum, 1269, 5785, {2}, true);
  g->ShapeProduct(1269, 5784, {2});
  g->Binary(ynn_binary_divide, 5785, 5784, 1270);
  g->Binary(ynn_binary_add, 1270, 6446, 1271);
  g->Binary(ynn_binary_pow, 1271, 6448, 1272);
  g->Binary(ynn_binary_multiply, 1268, 1272, 1273);
  g->Convert(6643, 1274);
  g->Binary(ynn_binary_multiply, 1273, 1274, 1276);
  g->Binary(ynn_binary_add, 1249, 1276, 1277);
}

// Scope: "Layer17 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1064, 1278, {0,0,17,0}, {-1,-1,1,-1});
  g->Reshape(1278, 1279, {1,1,256});
  g->Binary(ynn_binary_add, 1279, 7035, 1280);
  g->Binary(ynn_binary_multiply, 1280, 6444, 1281);
  g->Quantize(1277, 1282, 0.16417057812213898, 0);
  g->Transpose(6640, 4309, {1,0});
  g->Binary(ynn_binary_multiply, 4306, 4308, 4304);
  g->Dot(1282, 4309, YNN_INVALID_VALUE_ID, 4303, 1);
  g->DequantizeTensor(4303, YNN_INVALID_VALUE_ID, 4304, 4305);
  g->QuantizeTensor(4305, 6412, 4307, 1283);
  g->Dequantize(1283, 1284, 0.0821850448846817, 0);
  g->Polynomial(1284, 5788, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5788, 5789);
  g->Binary(ynn_binary_add, 5789, 5474, 5786);
  g->Binary(ynn_binary_multiply, 1284, 5472, 5787);
  g->Binary(ynn_binary_multiply, 5787, 5786, 1285);
  g->Binary(ynn_binary_multiply, 1285, 1281, 1288);
  g->Quantize(1288, 1289, 0.8188976645469666, 0);
  g->Transpose(6641, 4316, {1,0});
  g->Binary(ynn_binary_multiply, 4313, 4315, 4311);
  g->Dot(1289, 4316, YNN_INVALID_VALUE_ID, 4310, 1);
  g->DequantizeTensor(4310, YNN_INVALID_VALUE_ID, 4311, 4312);
  g->QuantizeTensor(4312, 6412, 4314, 1290);
  g->Dequantize(1290, 1291, 0.2322644591331482, 0);
  g->Unary(ynn_unary_square, 1291, 1292);
  g->Reduce(ynn_reduce_sum, 1292, 5793, {2}, true);
  g->ShapeProduct(1292, 5792, {2});
  g->Binary(ynn_binary_divide, 5793, 5792, 1293);
  g->Binary(ynn_binary_add, 1293, 6446, 1294);
  g->Binary(ynn_binary_pow, 1294, 6448, 1295);
  g->Binary(ynn_binary_multiply, 1291, 1295, 1296);
  g->Convert(6644, 1297);
  g->Binary(ynn_binary_multiply, 1296, 1297, 1299);
  g->Binary(ynn_binary_add, 1277, 1299, 1300);
  g->Convert(6636, 1301);
  g->Binary(ynn_binary_multiply, 1300, 1301, 1302);
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
  g->Quantize(1310, 1311, 0.3068588376045227, 0);
  g->Transpose(6662, 4323, {1,0});
  g->Binary(ynn_binary_multiply, 4320, 4322, 4318);
  g->Dot(1311, 4323, YNN_INVALID_VALUE_ID, 4317, 1);
  g->DequantizeTensor(4317, YNN_INVALID_VALUE_ID, 4318, 4319);
  g->QuantizeTensor(4319, 6412, 4321, 1312);
  g->Dequantize(1312, 1313, 0.36220473051071167, 0);
  g->SplitDim(1313, 1314, 2, {8,256});
  g->FuseDims(1314, 1316, 1, 2);
  g->SplitDim(1316, 1315, 1, {8,1});
  g->Unary(ynn_unary_square, 1315, 1317);
  g->Reduce(ynn_reduce_sum, 1317, 5799, {3}, true);
  g->ShapeProduct(1317, 5798, {3});
  g->Binary(ynn_binary_divide, 5799, 5798, 1318);
  g->Binary(ynn_binary_add, 1318, 6446, 1319);
  g->Binary(ynn_binary_pow, 1319, 6448, 1320);
  g->Binary(ynn_binary_multiply, 1315, 1320, 1322);
  g->Convert(6661, 1323);
  g->Binary(ynn_binary_multiply, 1322, 1323, 1324);
  g->Slice(1324, 1325, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1324, 1326, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1326, 1327);
  g->Concat({1327,1325}, 1328, 3);
  g->Binary(ynn_binary_multiply, 1324, 2173, 1329);
  g->Binary(ynn_binary_multiply, 1328, 3050, 1330);
  g->Binary(ynn_binary_add, 1329, 1330, 1331);
}

// Scope: "Layer18 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(1331, 772, 1333, false, true);
  g->Mask(1333, 6463, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6463, 5803, {-1}, true);
  g->Binary(ynn_binary_subtract, 6463, 5803, 5800);
  g->Unary(ynn_unary_exp, 5800, 5801);
  g->Reduce(ynn_reduce_sum, 5801, 5804, {-1}, true);
  g->Binary(ynn_binary_divide, 5474, 5804, 5802);
  g->Binary(ynn_binary_multiply, 5801, 5802, 1334);
  g->Matmul(1334, 774, 1335, false, false);
}

// Scope: "Layer18 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(1335, 1337, 1, 2);
  g->SplitDim(1337, 1336, 1, {1,8});
  g->FuseDims(1336, 1338, 2, 2);
  g->Quantize(1338, 1339, 0.023006899282336235, 0);
  g->Transpose(6660, 4330, {1,0});
  g->Binary(ynn_binary_multiply, 4327, 4329, 4325);
  g->Dot(1339, 4330, YNN_INVALID_VALUE_ID, 4324, 1);
  g->DequantizeTensor(4324, YNN_INVALID_VALUE_ID, 4325, 4326);
  g->QuantizeTensor(4326, 6412, 4328, 1340);
  g->Dequantize(1340, 1341, 0.023901576176285744, 0);
}

// Scope: "Layer18 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1302, 1303);
  g->Reduce(ynn_reduce_sum, 1303, 5795, {2}, true);
  g->ShapeProduct(1303, 5794, {2});
  g->Binary(ynn_binary_divide, 5795, 5794, 1304);
  g->Binary(ynn_binary_add, 1304, 6446, 1305);
  g->Binary(ynn_binary_pow, 1305, 6448, 1306);
  g->Binary(ynn_binary_multiply, 1302, 1306, 1307);
  g->Convert(6649, 1308);
  g->Binary(ynn_binary_multiply, 1307, 1308, 1310);
  BuildLayer18AttentionQueryProjection(ctx);
  BuildLayer18AttentionSdpa(ctx);
  BuildLayer18AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1341, 1342);
  g->Reduce(ynn_reduce_sum, 1342, 5806, {2}, true);
  g->ShapeProduct(1342, 5805, {2});
  g->Binary(ynn_binary_divide, 5806, 5805, 1344);
  g->Binary(ynn_binary_add, 1344, 6446, 1345);
  g->Binary(ynn_binary_pow, 1345, 6448, 1346);
  g->Binary(ynn_binary_multiply, 1341, 1346, 1347);
  g->Convert(6656, 1348);
  g->Binary(ynn_binary_multiply, 1347, 1348, 1349);
  g->Binary(ynn_binary_add, 1302, 1349, 1350);
}

// Scope: "Layer18 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1350, 1351);
  g->Reduce(ynn_reduce_sum, 1351, 5808, {2}, true);
  g->ShapeProduct(1351, 5807, {2});
  g->Binary(ynn_binary_divide, 5808, 5807, 1352);
  g->Binary(ynn_binary_add, 1352, 6446, 1353);
  g->Binary(ynn_binary_pow, 1353, 6448, 1355);
  g->Binary(ynn_binary_multiply, 1350, 1355, 1356);
  g->Convert(6659, 1357);
  g->Binary(ynn_binary_multiply, 1356, 1357, 1358);
  g->Quantize(1358, 1359, 0.018082860857248306, 0);
  g->Transpose(6653, 4337, {1,0});
  g->Binary(ynn_binary_multiply, 4334, 4336, 4332);
  g->Dot(1359, 4337, YNN_INVALID_VALUE_ID, 4331, 1);
  g->DequantizeTensor(4331, YNN_INVALID_VALUE_ID, 4332, 4333);
  g->QuantizeTensor(4333, 6412, 4335, 1360);
  g->Dequantize(1360, 1361, 0.02362205646932125, 0);
  g->Transpose(6652, 4342, {1,0});
  g->Binary(ynn_binary_multiply, 4334, 4341, 4339);
  g->Dot(1359, 4342, YNN_INVALID_VALUE_ID, 4338, 1);
  g->DequantizeTensor(4338, YNN_INVALID_VALUE_ID, 4339, 4340);
  g->QuantizeTensor(4340, 6412, 4335, 1362);
  g->Dequantize(1362, 1363, 0.02362205646932125, 0);
  g->Polynomial(1363, 5811, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5811, 5812);
  g->Binary(ynn_binary_add, 5812, 5474, 5809);
  g->Binary(ynn_binary_multiply, 1363, 5472, 5810);
  g->Binary(ynn_binary_multiply, 5810, 5809, 1365);
  g->Binary(ynn_binary_multiply, 1361, 1365, 1366);
  g->Quantize(1366, 1367, 0.03297245129942894, 0);
  g->Transpose(6651, 4349, {1,0});
  g->Binary(ynn_binary_multiply, 4346, 4348, 4344);
  g->Dot(1367, 4349, YNN_INVALID_VALUE_ID, 4343, 1);
  g->DequantizeTensor(4343, YNN_INVALID_VALUE_ID, 4344, 4345);
  g->QuantizeTensor(4345, 6412, 4347, 1368);
  g->Dequantize(1368, 1369, 0.034845925867557526, 0);
  g->Unary(ynn_unary_square, 1369, 1370);
  g->Reduce(ynn_reduce_sum, 1370, 5814, {2}, true);
  g->ShapeProduct(1370, 5813, {2});
  g->Binary(ynn_binary_divide, 5814, 5813, 1371);
  g->Binary(ynn_binary_add, 1371, 6446, 1372);
  g->Binary(ynn_binary_pow, 1372, 6448, 1373);
  g->Binary(ynn_binary_multiply, 1369, 1373, 1374);
  g->Convert(6657, 1376);
  g->Binary(ynn_binary_multiply, 1374, 1376, 1377);
  g->Binary(ynn_binary_add, 1350, 1377, 1378);
}

// Scope: "Layer18 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1064, 1379, {0,0,18,0}, {-1,-1,1,-1});
  g->Reshape(1379, 1380, {1,1,256});
  g->Binary(ynn_binary_add, 1380, 7036, 1381);
  g->Binary(ynn_binary_multiply, 1381, 6444, 1382);
  g->Quantize(1378, 1383, 0.18026936054229736, 0);
  g->Transpose(6654, 4356, {1,0});
  g->Binary(ynn_binary_multiply, 4353, 4355, 4351);
  g->Dot(1383, 4356, YNN_INVALID_VALUE_ID, 4350, 1);
  g->DequantizeTensor(4350, YNN_INVALID_VALUE_ID, 4351, 4352);
  g->QuantizeTensor(4352, 6412, 4354, 1384);
  g->Dequantize(1384, 1385, 0.08562992513179779, 0);
  g->Polynomial(1385, 5817, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5817, 5818);
  g->Binary(ynn_binary_add, 5818, 5474, 5815);
  g->Binary(ynn_binary_multiply, 1385, 5472, 5816);
  g->Binary(ynn_binary_multiply, 5816, 5815, 1387);
  g->Binary(ynn_binary_multiply, 1387, 1382, 1388);
  g->Quantize(1388, 1389, 1.4409449100494385, 0);
  g->Transpose(6655, 4363, {1,0});
  g->Binary(ynn_binary_multiply, 4360, 4362, 4358);
  g->Dot(1389, 4363, YNN_INVALID_VALUE_ID, 4357, 1);
  g->DequantizeTensor(4357, YNN_INVALID_VALUE_ID, 4358, 4359);
  g->QuantizeTensor(4359, 6412, 4361, 1390);
  g->Dequantize(1390, 1391, 0.2601272463798523, 0);
  g->Unary(ynn_unary_square, 1391, 1392);
  g->Reduce(ynn_reduce_sum, 1392, 5820, {2}, true);
  g->ShapeProduct(1392, 5819, {2});
  g->Binary(ynn_binary_divide, 5820, 5819, 1393);
  g->Binary(ynn_binary_add, 1393, 6446, 1394);
  g->Binary(ynn_binary_pow, 1394, 6448, 1395);
  g->Binary(ynn_binary_multiply, 1391, 1395, 1396);
  g->Convert(6658, 1399);
  g->Binary(ynn_binary_multiply, 1396, 1399, 1400);
  g->Binary(ynn_binary_add, 1378, 1400, 1401);
  g->Convert(6650, 1402);
  g->Binary(ynn_binary_multiply, 1401, 1402, 1403);
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
  g->Quantize(1411, 1412, 0.3205932080745697, 0);
  g->Transpose(6676, 4370, {1,0});
  g->Binary(ynn_binary_multiply, 4367, 4369, 4365);
  g->Dot(1412, 4370, YNN_INVALID_VALUE_ID, 4364, 1);
  g->DequantizeTensor(4364, YNN_INVALID_VALUE_ID, 4365, 4366);
  g->QuantizeTensor(4366, 6412, 4368, 1413);
  g->Dequantize(1413, 1414, 0.4685039222240448, 0);
  g->SplitDim(1414, 1415, 2, {8,512});
  g->FuseDims(1415, 1417, 1, 2);
  g->SplitDim(1417, 1416, 1, {8,1});
  g->Unary(ynn_unary_square, 1416, 1418);
  g->Reduce(ynn_reduce_sum, 1418, 5826, {3}, true);
  g->ShapeProduct(1418, 5825, {3});
  g->Binary(ynn_binary_divide, 5826, 5825, 1419);
  g->Binary(ynn_binary_add, 1419, 6446, 1420);
  g->Binary(ynn_binary_pow, 1420, 6448, 1422);
  g->Binary(ynn_binary_multiply, 1416, 1422, 1423);
  g->Convert(6675, 1424);
  g->Binary(ynn_binary_multiply, 1423, 1424, 1425);
  g->Slice(1425, 1426, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(1425, 1427, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 1427, 1428);
  g->Concat({1428,1426}, 1429, 3);
  g->Binary(ynn_binary_multiply, 1425, 3471, 1430);
  g->Binary(ynn_binary_multiply, 1429, 3576, 1431);
  g->Binary(ynn_binary_add, 1430, 1431, 1433);
}

// Scope: "Layer19 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(1433, 907, 1434, false, true);
  g->Mask(1434, 6464, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 6464, 5830, {-1}, true);
  g->Binary(ynn_binary_subtract, 6464, 5830, 5827);
  g->Unary(ynn_unary_exp, 5827, 5828);
  g->Reduce(ynn_reduce_sum, 5828, 5831, {-1}, true);
  g->Binary(ynn_binary_divide, 5474, 5831, 5829);
  g->Binary(ynn_binary_multiply, 5828, 5829, 1435);
  g->Matmul(1435, 909, 1436, false, false);
}

// Scope: "Layer19 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(1436, 1438, 1, 2);
  g->SplitDim(1438, 1437, 1, {1,8});
  g->FuseDims(1437, 1439, 2, 2);
  g->Quantize(1439, 1440, 0.014886821620166302, 0);
  g->Transpose(6674, 4377, {1,0});
  g->Binary(ynn_binary_multiply, 4374, 4376, 4372);
  g->Dot(1440, 4377, YNN_INVALID_VALUE_ID, 4371, 1);
  g->DequantizeTensor(4371, YNN_INVALID_VALUE_ID, 4372, 4373);
  g->QuantizeTensor(4373, 6412, 4375, 1441);
  g->Dequantize(1441, 1442, 0.01861305721104145, 0);
}

// Scope: "Layer19 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1403, 1404);
  g->Reduce(ynn_reduce_sum, 1404, 5824, {2}, true);
  g->ShapeProduct(1404, 5823, {2});
  g->Binary(ynn_binary_divide, 5824, 5823, 1405);
  g->Binary(ynn_binary_add, 1405, 6446, 1406);
  g->Binary(ynn_binary_pow, 1406, 6448, 1407);
  g->Binary(ynn_binary_multiply, 1403, 1407, 1408);
  g->Convert(6663, 1410);
  g->Binary(ynn_binary_multiply, 1408, 1410, 1411);
  BuildLayer19AttentionQueryProjection(ctx);
  BuildLayer19AttentionSdpa(ctx);
  BuildLayer19AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1442, 1444);
  g->Reduce(ynn_reduce_sum, 1444, 5833, {2}, true);
  g->ShapeProduct(1444, 5832, {2});
  g->Binary(ynn_binary_divide, 5833, 5832, 1445);
  g->Binary(ynn_binary_add, 1445, 6446, 1446);
  g->Binary(ynn_binary_pow, 1446, 6448, 1447);
  g->Binary(ynn_binary_multiply, 1442, 1447, 1448);
  g->Convert(6670, 1449);
  g->Binary(ynn_binary_multiply, 1448, 1449, 1450);
  g->Binary(ynn_binary_add, 1403, 1450, 1451);
}

// Scope: "Layer19 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1451, 1452);
  g->Reduce(ynn_reduce_sum, 1452, 5835, {2}, true);
  g->ShapeProduct(1452, 5834, {2});
  g->Binary(ynn_binary_divide, 5835, 5834, 1453);
  g->Binary(ynn_binary_add, 1453, 6446, 1455);
  g->Binary(ynn_binary_pow, 1455, 6448, 1456);
  g->Binary(ynn_binary_multiply, 1451, 1456, 1457);
  g->Convert(6673, 1458);
  g->Binary(ynn_binary_multiply, 1457, 1458, 1459);
  g->Quantize(1459, 1460, 0.019887126982212067, 0);
  g->Transpose(6667, 4384, {1,0});
  g->Binary(ynn_binary_multiply, 4381, 4383, 4379);
  g->Dot(1460, 4384, YNN_INVALID_VALUE_ID, 4378, 1);
  g->DequantizeTensor(4378, YNN_INVALID_VALUE_ID, 4379, 4380);
  g->QuantizeTensor(4380, 6412, 4382, 1461);
  g->Dequantize(1461, 1462, 0.022637804970145226, 0);
  g->Transpose(6666, 4389, {1,0});
  g->Binary(ynn_binary_multiply, 4381, 4388, 4386);
  g->Dot(1460, 4389, YNN_INVALID_VALUE_ID, 4385, 1);
  g->DequantizeTensor(4385, YNN_INVALID_VALUE_ID, 4386, 4387);
  g->QuantizeTensor(4387, 6412, 4382, 1463);
  g->Dequantize(1463, 1465, 0.022637804970145226, 0);
  g->Polynomial(1465, 5838, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5838, 5839);
  g->Binary(ynn_binary_add, 5839, 5474, 5836);
  g->Binary(ynn_binary_multiply, 1465, 5472, 5837);
  g->Binary(ynn_binary_multiply, 5837, 5836, 1466);
  g->Binary(ynn_binary_multiply, 1462, 1466, 1467);
  g->Quantize(1467, 1468, 0.019808080047369003, 0);
  g->Transpose(6665, 4396, {1,0});
  g->Binary(ynn_binary_multiply, 4393, 4395, 4391);
  g->Dot(1468, 4396, YNN_INVALID_VALUE_ID, 4390, 1);
  g->DequantizeTensor(4390, YNN_INVALID_VALUE_ID, 4391, 4392);
  g->QuantizeTensor(4392, 6412, 4394, 1469);
  g->Dequantize(1469, 1470, 0.014754860661923885, 0);
  g->Unary(ynn_unary_square, 1470, 1471);
  g->Reduce(ynn_reduce_sum, 1471, 5841, {2}, true);
  g->ShapeProduct(1471, 5840, {2});
  g->Binary(ynn_binary_divide, 5841, 5840, 1472);
  g->Binary(ynn_binary_add, 1472, 6446, 1473);
  g->Binary(ynn_binary_pow, 1473, 6448, 1474);
  g->Binary(ynn_binary_multiply, 1470, 1474, 1476);
  g->Convert(6671, 1477);
  g->Binary(ynn_binary_multiply, 1476, 1477, 1478);
  g->Binary(ynn_binary_add, 1451, 1478, 1479);
}

// Scope: "Layer19 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1064, 1480, {0,0,19,0}, {-1,-1,1,-1});
  g->Reshape(1480, 1481, {1,1,256});
  g->Binary(ynn_binary_add, 1481, 7037, 1482);
  g->Binary(ynn_binary_multiply, 1482, 6444, 1483);
  g->Quantize(1479, 1484, 0.18873928487300873, 0);
  g->Transpose(6668, 4409, {1,0});
  g->Binary(ynn_binary_multiply, 4407, 4408, 4405);
  g->Dot(1484, 4409, YNN_INVALID_VALUE_ID, 4404, 1);
  g->DequantizeTensor(4404, YNN_INVALID_VALUE_ID, 4405, 4406);
  g->QuantizeTensor(4406, 6412, 3984, 1485);
  g->Dequantize(1485, 1487, 0.08070866763591766, 0);
  g->Polynomial(1487, 5844, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5844, 5845);
  g->Binary(ynn_binary_add, 5845, 5474, 5842);
  g->Binary(ynn_binary_multiply, 1487, 5472, 5843);
  g->Binary(ynn_binary_multiply, 5843, 5842, 1488);
  g->Binary(ynn_binary_multiply, 1488, 1483, 1489);
  g->Quantize(1489, 1490, 0.3858267664909363, 0);
  g->Transpose(6669, 4416, {1,0});
  g->Binary(ynn_binary_multiply, 4413, 4415, 4411);
  g->Dot(1490, 4416, YNN_INVALID_VALUE_ID, 4410, 1);
  g->DequantizeTensor(4410, YNN_INVALID_VALUE_ID, 4411, 4412);
  g->QuantizeTensor(4412, 6412, 4414, 1491);
  g->Dequantize(1491, 1492, 0.16572551429271698, 0);
  g->Unary(ynn_unary_square, 1492, 1493);
  g->Reduce(ynn_reduce_sum, 1493, 5847, {2}, true);
  g->ShapeProduct(1493, 5846, {2});
  g->Binary(ynn_binary_divide, 5847, 5846, 1494);
  g->Binary(ynn_binary_add, 1494, 6446, 1495);
  g->Binary(ynn_binary_pow, 1495, 6448, 1496);
  g->Binary(ynn_binary_multiply, 1492, 1496, 1497);
  g->Convert(6672, 1498);
  g->Binary(ynn_binary_multiply, 1497, 1498, 1499);
  g->Binary(ynn_binary_add, 1479, 1499, 1500);
  g->Convert(6664, 1501);
  g->Binary(ynn_binary_multiply, 1500, 1501, 1502);
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
  g->Quantize(1511, 1512, 0.3106735646724701, 0);
  g->Transpose(6707, 4428, {1,0});
  g->Binary(ynn_binary_multiply, 4425, 4427, 4423);
  g->Dot(1512, 4428, YNN_INVALID_VALUE_ID, 4422, 1);
  g->DequantizeTensor(4422, YNN_INVALID_VALUE_ID, 4423, 4424);
  g->QuantizeTensor(4424, 6412, 4426, 1513);
  g->Dequantize(1513, 1514, 0.36614173650741577, 0);
  g->SplitDim(1514, 1515, 2, {8,256});
  g->FuseDims(1515, 1517, 1, 2);
  g->SplitDim(1517, 1516, 1, {8,1});
  g->Unary(ynn_unary_square, 1516, 1518);
  g->Reduce(ynn_reduce_sum, 1518, 5851, {3}, true);
  g->ShapeProduct(1518, 5850, {3});
  g->Binary(ynn_binary_divide, 5851, 5850, 1519);
  g->Binary(ynn_binary_add, 1519, 6446, 1521);
  g->Binary(ynn_binary_pow, 1521, 6448, 1522);
  g->Binary(ynn_binary_multiply, 1516, 1522, 1523);
  g->Convert(6706, 1524);
  g->Binary(ynn_binary_multiply, 1523, 1524, 1525);
  g->Slice(1525, 1526, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1525, 1527, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1527, 1528);
  g->Concat({1528,1526}, 1529, 3);
  g->Binary(ynn_binary_multiply, 1525, 2173, 1530);
  g->Binary(ynn_binary_multiply, 1529, 3050, 1532);
  g->Binary(ynn_binary_add, 1530, 1532, 1533);
}

// Scope: "Layer20 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(1533, 772, 1534, false, true);
  g->Mask(1534, 6466, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6466, 5859, {-1}, true);
  g->Binary(ynn_binary_subtract, 6466, 5859, 5856);
  g->Unary(ynn_unary_exp, 5856, 5857);
  g->Reduce(ynn_reduce_sum, 5857, 5860, {-1}, true);
  g->Binary(ynn_binary_divide, 5474, 5860, 5858);
  g->Binary(ynn_binary_multiply, 5857, 5858, 1535);
  g->Matmul(1535, 774, 1536, false, false);
}

// Scope: "Layer20 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(1536, 1538, 1, 2);
  g->SplitDim(1538, 1537, 1, {1,8});
  g->FuseDims(1537, 1539, 2, 2);
  g->Quantize(1539, 1540, 0.02436024509370327, 0);
  g->Transpose(6705, 4434, {1,0});
  g->Binary(ynn_binary_multiply, 4179, 4433, 4430);
  g->Dot(1540, 4434, YNN_INVALID_VALUE_ID, 4429, 1);
  g->DequantizeTensor(4429, YNN_INVALID_VALUE_ID, 4430, 4431);
  g->QuantizeTensor(4431, 6412, 4432, 1541);
  g->Dequantize(1541, 1543, 0.035965267568826675, 0);
}

// Scope: "Layer20 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1502, 1503);
  g->Reduce(ynn_reduce_sum, 1503, 5849, {2}, true);
  g->ShapeProduct(1503, 5848, {2});
  g->Binary(ynn_binary_divide, 5849, 5848, 1504);
  g->Binary(ynn_binary_add, 1504, 6446, 1505);
  g->Binary(ynn_binary_pow, 1505, 6448, 1506);
  g->Binary(ynn_binary_multiply, 1502, 1506, 1509);
  g->Convert(6694, 1510);
  g->Binary(ynn_binary_multiply, 1509, 1510, 1511);
  BuildLayer20AttentionQueryProjection(ctx);
  BuildLayer20AttentionSdpa(ctx);
  BuildLayer20AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1543, 1544);
  g->Reduce(ynn_reduce_sum, 1544, 5862, {2}, true);
  g->ShapeProduct(1544, 5861, {2});
  g->Binary(ynn_binary_divide, 5862, 5861, 1545);
  g->Binary(ynn_binary_add, 1545, 6446, 1546);
  g->Binary(ynn_binary_pow, 1546, 6448, 1547);
  g->Binary(ynn_binary_multiply, 1543, 1547, 1548);
  g->Convert(6701, 1549);
  g->Binary(ynn_binary_multiply, 1548, 1549, 1550);
  g->Binary(ynn_binary_add, 1502, 1550, 1551);
}

// Scope: "Layer20 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1551, 1552);
  g->Reduce(ynn_reduce_sum, 1552, 5864, {2}, true);
  g->ShapeProduct(1552, 5863, {2});
  g->Binary(ynn_binary_divide, 5864, 5863, 1554);
  g->Binary(ynn_binary_add, 1554, 6446, 1555);
  g->Binary(ynn_binary_pow, 1555, 6448, 1556);
  g->Binary(ynn_binary_multiply, 1551, 1556, 1557);
  g->Convert(6704, 1558);
  g->Binary(ynn_binary_multiply, 1557, 1558, 1559);
  g->Quantize(1559, 1560, 0.021377958357334137, 0);
  g->Transpose(6698, 4441, {1,0});
  g->Binary(ynn_binary_multiply, 4438, 4440, 4436);
  g->Dot(1560, 4441, YNN_INVALID_VALUE_ID, 4435, 1);
  g->DequantizeTensor(4435, YNN_INVALID_VALUE_ID, 4436, 4437);
  g->QuantizeTensor(4437, 6412, 4439, 1561);
  g->Dequantize(1561, 1562, 0.02276083640754223, 0);
  g->Transpose(6697, 4453, {1,0});
  g->Binary(ynn_binary_multiply, 4438, 4452, 4450);
  g->Dot(1560, 4453, YNN_INVALID_VALUE_ID, 4449, 1);
  g->DequantizeTensor(4449, YNN_INVALID_VALUE_ID, 4450, 4451);
  g->QuantizeTensor(4451, 6412, 4439, 1564);
  g->Dequantize(1564, 1565, 0.02276083640754223, 0);
  g->Polynomial(1565, 5867, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5867, 5868);
  g->Binary(ynn_binary_add, 5868, 5474, 5865);
  g->Binary(ynn_binary_multiply, 1565, 5472, 5866);
  g->Binary(ynn_binary_multiply, 5866, 5865, 1566);
  g->Binary(ynn_binary_multiply, 1562, 1566, 1567);
  g->Quantize(1567, 1568, 0.026574812829494476, 0);
  g->Transpose(6696, 4460, {1,0});
  g->Binary(ynn_binary_multiply, 4457, 4459, 4455);
  g->Dot(1568, 4460, YNN_INVALID_VALUE_ID, 4454, 1);
  g->DequantizeTensor(4454, YNN_INVALID_VALUE_ID, 4455, 4456);
  g->QuantizeTensor(4456, 6412, 4458, 1569);
  g->Dequantize(1569, 1570, 0.028310857713222504, 0);
  g->Unary(ynn_unary_square, 1570, 1571);
  g->Reduce(ynn_reduce_sum, 1571, 5870, {2}, true);
  g->ShapeProduct(1571, 5869, {2});
  g->Binary(ynn_binary_divide, 5870, 5869, 1572);
  g->Binary(ynn_binary_add, 1572, 6446, 1573);
  g->Binary(ynn_binary_pow, 1573, 6448, 1575);
  g->Binary(ynn_binary_multiply, 1570, 1575, 1576);
  g->Convert(6702, 1577);
  g->Binary(ynn_binary_multiply, 1576, 1577, 1578);
  g->Binary(ynn_binary_add, 1551, 1578, 1579);
}

// Scope: "Layer20 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1064, 1580, {0,0,20,0}, {-1,-1,1,-1});
  g->Reshape(1580, 1581, {1,1,256});
  g->Binary(ynn_binary_add, 1581, 7039, 1582);
  g->Binary(ynn_binary_multiply, 1582, 6444, 1583);
  g->Quantize(1579, 1584, 0.17634929716587067, 0);
  g->Transpose(6699, 4467, {1,0});
  g->Binary(ynn_binary_multiply, 4464, 4466, 4462);
  g->Dot(1584, 4467, YNN_INVALID_VALUE_ID, 4461, 1);
  g->DequantizeTensor(4461, YNN_INVALID_VALUE_ID, 4462, 4463);
  g->QuantizeTensor(4463, 6412, 4465, 1586);
  g->Dequantize(1586, 1587, 0.059055130928754807, 0);
  g->Polynomial(1587, 5873, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5873, 5874);
  g->Binary(ynn_binary_add, 5874, 5474, 5871);
  g->Binary(ynn_binary_multiply, 1587, 5472, 5872);
  g->Binary(ynn_binary_multiply, 5872, 5871, 1588);
  g->Binary(ynn_binary_multiply, 1588, 1583, 1589);
  g->Quantize(1589, 1590, 0.1998031586408615, 0);
  g->Transpose(6700, 4474, {1,0});
  g->Binary(ynn_binary_multiply, 4471, 4473, 4469);
  g->Dot(1590, 4474, YNN_INVALID_VALUE_ID, 4468, 1);
  g->DequantizeTensor(4468, YNN_INVALID_VALUE_ID, 4469, 4470);
  g->QuantizeTensor(4470, 6412, 4472, 1591);
  g->Dequantize(1591, 1592, 0.07776007056236267, 0);
  g->Unary(ynn_unary_square, 1592, 1593);
  g->Reduce(ynn_reduce_sum, 1593, 5876, {2}, true);
  g->ShapeProduct(1593, 5875, {2});
  g->Binary(ynn_binary_divide, 5876, 5875, 1594);
  g->Binary(ynn_binary_add, 1594, 6446, 1595);
  g->Binary(ynn_binary_pow, 1595, 6448, 1597);
  g->Binary(ynn_binary_multiply, 1592, 1597, 1598);
  g->Convert(6703, 1599);
  g->Binary(ynn_binary_multiply, 1598, 1599, 1600);
  g->Binary(ynn_binary_add, 1579, 1600, 1601);
  g->Convert(6695, 1602);
  g->Binary(ynn_binary_multiply, 1601, 1602, 1603);
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
  g->Quantize(1611, 1612, 0.20073647797107697, 0);
  g->Transpose(6721, 4481, {1,0});
  g->Binary(ynn_binary_multiply, 4478, 4480, 4476);
  g->Dot(1612, 4481, YNN_INVALID_VALUE_ID, 4475, 1);
  g->DequantizeTensor(4475, YNN_INVALID_VALUE_ID, 4476, 4477);
  g->QuantizeTensor(4477, 6412, 4479, 1613);
  g->Dequantize(1613, 1614, 0.23622049391269684, 0);
  g->SplitDim(1614, 1615, 2, {8,256});
  g->FuseDims(1615, 1617, 1, 2);
  g->SplitDim(1617, 1616, 1, {8,1});
  g->Unary(ynn_unary_square, 1616, 1618);
  g->Reduce(ynn_reduce_sum, 1618, 5882, {3}, true);
  g->ShapeProduct(1618, 5881, {3});
  g->Binary(ynn_binary_divide, 5882, 5881, 1621);
  g->Binary(ynn_binary_add, 1621, 6446, 1622);
  g->Binary(ynn_binary_pow, 1622, 6448, 1623);
  g->Binary(ynn_binary_multiply, 1616, 1623, 1624);
  g->Convert(6720, 1625);
  g->Binary(ynn_binary_multiply, 1624, 1625, 1626);
  g->Slice(1626, 1627, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1626, 1628, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1628, 1629);
  g->Concat({1629,1627}, 1630, 3);
  g->Binary(ynn_binary_multiply, 1626, 2173, 1632);
  g->Binary(ynn_binary_multiply, 1630, 3050, 1633);
  g->Binary(ynn_binary_add, 1632, 1633, 1634);
}

// Scope: "Layer21 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(1634, 772, 1635, false, true);
  g->Mask(1635, 6467, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6467, 5886, {-1}, true);
  g->Binary(ynn_binary_subtract, 6467, 5886, 5883);
  g->Unary(ynn_unary_exp, 5883, 5884);
  g->Reduce(ynn_reduce_sum, 5884, 5887, {-1}, true);
  g->Binary(ynn_binary_divide, 5474, 5887, 5885);
  g->Binary(ynn_binary_multiply, 5884, 5885, 1636);
  g->Matmul(1636, 774, 1637, false, false);
}

// Scope: "Layer21 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(1637, 1639, 1, 2);
  g->SplitDim(1639, 1638, 1, {1,8});
  g->FuseDims(1638, 1640, 2, 2);
  g->Quantize(1640, 1641, 0.025221465155482292, 0);
  g->Transpose(6719, 4488, {1,0});
  g->Binary(ynn_binary_multiply, 4485, 4487, 4483);
  g->Dot(1641, 4488, YNN_INVALID_VALUE_ID, 4482, 1);
  g->DequantizeTensor(4482, YNN_INVALID_VALUE_ID, 4483, 4484);
  g->QuantizeTensor(4484, 6412, 4486, 1643);
  g->Dequantize(1643, 1644, 0.03553423285484314, 0);
}

// Scope: "Layer21 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1603, 1604);
  g->Reduce(ynn_reduce_sum, 1604, 5880, {2}, true);
  g->ShapeProduct(1604, 5879, {2});
  g->Binary(ynn_binary_divide, 5880, 5879, 1605);
  g->Binary(ynn_binary_add, 1605, 6446, 1606);
  g->Binary(ynn_binary_pow, 1606, 6448, 1608);
  g->Binary(ynn_binary_multiply, 1603, 1608, 1609);
  g->Convert(6708, 1610);
  g->Binary(ynn_binary_multiply, 1609, 1610, 1611);
  BuildLayer21AttentionQueryProjection(ctx);
  BuildLayer21AttentionSdpa(ctx);
  BuildLayer21AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1644, 1645);
  g->Reduce(ynn_reduce_sum, 1645, 5889, {2}, true);
  g->ShapeProduct(1645, 5888, {2});
  g->Binary(ynn_binary_divide, 5889, 5888, 1646);
  g->Binary(ynn_binary_add, 1646, 6446, 1647);
  g->Binary(ynn_binary_pow, 1647, 6448, 1648);
  g->Binary(ynn_binary_multiply, 1644, 1648, 1649);
  g->Convert(6715, 1650);
  g->Binary(ynn_binary_multiply, 1649, 1650, 1651);
  g->Binary(ynn_binary_add, 1603, 1651, 1652);
}

// Scope: "Layer21 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1652, 1654);
  g->Reduce(ynn_reduce_sum, 1654, 5891, {2}, true);
  g->ShapeProduct(1654, 5890, {2});
  g->Binary(ynn_binary_divide, 5891, 5890, 1655);
  g->Binary(ynn_binary_add, 1655, 6446, 1656);
  g->Binary(ynn_binary_pow, 1656, 6448, 1657);
  g->Binary(ynn_binary_multiply, 1652, 1657, 1658);
  g->Convert(6718, 1659);
  g->Binary(ynn_binary_multiply, 1658, 1659, 1660);
  g->Quantize(1660, 1661, 0.019064493477344513, 0);
  g->Transpose(6712, 4494, {1,0});
  g->Binary(ynn_binary_multiply, 4492, 4493, 4490);
  g->Dot(1661, 4494, YNN_INVALID_VALUE_ID, 4489, 1);
  g->DequantizeTensor(4489, YNN_INVALID_VALUE_ID, 4490, 4491);
  g->QuantizeTensor(4491, 6412, 4335, 1662);
  g->Dequantize(1662, 1663, 0.02362205646932125, 0);
  g->Transpose(6711, 4499, {1,0});
  g->Binary(ynn_binary_multiply, 4492, 4498, 4496);
  g->Dot(1661, 4499, YNN_INVALID_VALUE_ID, 4495, 1);
  g->DequantizeTensor(4495, YNN_INVALID_VALUE_ID, 4496, 4497);
  g->QuantizeTensor(4497, 6412, 4335, 1665);
  g->Dequantize(1665, 1666, 0.02362205646932125, 0);
  g->Polynomial(1666, 5894, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5894, 5895);
  g->Binary(ynn_binary_add, 5895, 5474, 5892);
  g->Binary(ynn_binary_multiply, 1666, 5472, 5893);
  g->Binary(ynn_binary_multiply, 5893, 5892, 1667);
  g->Binary(ynn_binary_multiply, 1663, 1667, 1668);
  g->Quantize(1668, 1669, 0.030019694939255714, 0);
  g->Transpose(6710, 4506, {1,0});
  g->Binary(ynn_binary_multiply, 4503, 4505, 4501);
  g->Dot(1669, 4506, YNN_INVALID_VALUE_ID, 4500, 1);
  g->DequantizeTensor(4500, YNN_INVALID_VALUE_ID, 4501, 4502);
  g->QuantizeTensor(4502, 6412, 4504, 1670);
  g->Dequantize(1670, 1671, 0.03767223656177521, 0);
  g->Unary(ynn_unary_square, 1671, 1672);
  g->Reduce(ynn_reduce_sum, 1672, 5897, {2}, true);
  g->ShapeProduct(1672, 5896, {2});
  g->Binary(ynn_binary_divide, 5897, 5896, 1673);
  g->Binary(ynn_binary_add, 1673, 6446, 1675);
  g->Binary(ynn_binary_pow, 1675, 6448, 1676);
  g->Binary(ynn_binary_multiply, 1671, 1676, 1677);
  g->Convert(6716, 1678);
  g->Binary(ynn_binary_multiply, 1677, 1678, 1679);
  g->Binary(ynn_binary_add, 1652, 1679, 1680);
}

// Scope: "Layer21 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1064, 1681, {0,0,21,0}, {-1,-1,1,-1});
  g->Reshape(1681, 1682, {1,1,256});
  g->Binary(ynn_binary_add, 1682, 7040, 1683);
  g->Binary(ynn_binary_multiply, 1683, 6444, 1684);
  g->Quantize(1680, 1686, 0.14814288914203644, 0);
  g->Transpose(6713, 4513, {1,0});
  g->Binary(ynn_binary_multiply, 4510, 4512, 4508);
  g->Dot(1686, 4513, YNN_INVALID_VALUE_ID, 4507, 1);
  g->DequantizeTensor(4507, YNN_INVALID_VALUE_ID, 4508, 4509);
  g->QuantizeTensor(4509, 6412, 4511, 1687);
  g->Dequantize(1687, 1688, 0.047244105488061905, 0);
  g->Polynomial(1688, 5900, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5900, 5901);
  g->Binary(ynn_binary_add, 5901, 5474, 5898);
  g->Binary(ynn_binary_multiply, 1688, 5472, 5899);
  g->Binary(ynn_binary_multiply, 5899, 5898, 1689);
  g->Binary(ynn_binary_multiply, 1689, 1684, 1690);
  g->Quantize(1690, 1691, 0.10531497001647949, 0);
  g->Transpose(6714, 4520, {1,0});
  g->Binary(ynn_binary_multiply, 4517, 4519, 4515);
  g->Dot(1691, 4520, YNN_INVALID_VALUE_ID, 4514, 1);
  g->DequantizeTensor(4514, YNN_INVALID_VALUE_ID, 4515, 4516);
  g->QuantizeTensor(4516, 6412, 4518, 1692);
  g->Dequantize(1692, 1693, 0.061565153300762177, 0);
  g->Unary(ynn_unary_square, 1693, 1694);
  g->Reduce(ynn_reduce_sum, 1694, 5903, {2}, true);
  g->ShapeProduct(1694, 5902, {2});
  g->Binary(ynn_binary_divide, 5903, 5902, 1695);
  g->Binary(ynn_binary_add, 1695, 6446, 1697);
  g->Binary(ynn_binary_pow, 1697, 6448, 1698);
  g->Binary(ynn_binary_multiply, 1693, 1698, 1699);
  g->Convert(6717, 1700);
  g->Binary(ynn_binary_multiply, 1699, 1700, 1701);
  g->Binary(ynn_binary_add, 1680, 1701, 1702);
  g->Convert(6709, 1703);
  g->Binary(ynn_binary_multiply, 1702, 1703, 1704);
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
  g->Quantize(1712, 1713, 0.21987482905387878, 0);
  g->Transpose(6735, 4527, {1,0});
  g->Binary(ynn_binary_multiply, 4524, 4526, 4522);
  g->Dot(1713, 4527, YNN_INVALID_VALUE_ID, 4521, 1);
  g->DequantizeTensor(4521, YNN_INVALID_VALUE_ID, 4522, 4523);
  g->QuantizeTensor(4523, 6412, 4525, 1714);
  g->Dequantize(1714, 1715, 0.19685040414333344, 0);
  g->SplitDim(1715, 1716, 2, {8,256});
  g->FuseDims(1716, 1718, 1, 2);
  g->SplitDim(1718, 1717, 1, {8,1});
  g->Unary(ynn_unary_square, 1717, 1720);
  g->Reduce(ynn_reduce_sum, 1720, 5907, {3}, true);
  g->ShapeProduct(1720, 5906, {3});
  g->Binary(ynn_binary_divide, 5907, 5906, 1721);
  g->Binary(ynn_binary_add, 1721, 6446, 1722);
  g->Binary(ynn_binary_pow, 1722, 6448, 1723);
  g->Binary(ynn_binary_multiply, 1717, 1723, 1724);
  g->Convert(6734, 1725);
  g->Binary(ynn_binary_multiply, 1724, 1725, 1726);
  g->Slice(1726, 1727, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1726, 1728, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1728, 1729);
  g->Concat({1729,1727}, 1732, 3);
  g->Binary(ynn_binary_multiply, 1726, 2173, 1733);
  g->Binary(ynn_binary_multiply, 1732, 3050, 1734);
  g->Binary(ynn_binary_add, 1733, 1734, 1735);
}

// Scope: "Layer22 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(1735, 772, 1736, false, true);
  g->Mask(1736, 6468, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6468, 5911, {-1}, true);
  g->Binary(ynn_binary_subtract, 6468, 5911, 5908);
  g->Unary(ynn_unary_exp, 5908, 5909);
  g->Reduce(ynn_reduce_sum, 5909, 5912, {-1}, true);
  g->Binary(ynn_binary_divide, 5474, 5912, 5910);
  g->Binary(ynn_binary_multiply, 5909, 5910, 1737);
  g->Matmul(1737, 774, 1738, false, false);
}

// Scope: "Layer22 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(1738, 1740, 1, 2);
  g->SplitDim(1740, 1739, 1, {1,8});
  g->FuseDims(1739, 1741, 2, 2);
  g->Quantize(1741, 1743, 0.023868119344115257, 0);
  g->Transpose(6733, 4541, {1,0});
  g->Binary(ynn_binary_multiply, 4538, 4540, 4536);
  g->Dot(1743, 4541, YNN_INVALID_VALUE_ID, 4535, 1);
  g->DequantizeTensor(4535, YNN_INVALID_VALUE_ID, 4536, 4537);
  g->QuantizeTensor(4537, 6412, 4539, 1744);
  g->Dequantize(1744, 1745, 0.047558318823575974, 0);
}

// Scope: "Layer22 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1704, 1705);
  g->Reduce(ynn_reduce_sum, 1705, 5905, {2}, true);
  g->ShapeProduct(1705, 5904, {2});
  g->Binary(ynn_binary_divide, 5905, 5904, 1706);
  g->Binary(ynn_binary_add, 1706, 6446, 1708);
  g->Binary(ynn_binary_pow, 1708, 6448, 1709);
  g->Binary(ynn_binary_multiply, 1704, 1709, 1710);
  g->Convert(6722, 1711);
  g->Binary(ynn_binary_multiply, 1710, 1711, 1712);
  BuildLayer22AttentionQueryProjection(ctx);
  BuildLayer22AttentionSdpa(ctx);
  BuildLayer22AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1745, 1746);
  g->Reduce(ynn_reduce_sum, 1746, 5914, {2}, true);
  g->ShapeProduct(1746, 5913, {2});
  g->Binary(ynn_binary_divide, 5914, 5913, 1747);
  g->Binary(ynn_binary_add, 1747, 6446, 1748);
  g->Binary(ynn_binary_pow, 1748, 6448, 1749);
  g->Binary(ynn_binary_multiply, 1745, 1749, 1750);
  g->Convert(6729, 1751);
  g->Binary(ynn_binary_multiply, 1750, 1751, 1752);
  g->Binary(ynn_binary_add, 1704, 1752, 1754);
}

// Scope: "Layer22 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1754, 1755);
  g->Reduce(ynn_reduce_sum, 1755, 5920, {2}, true);
  g->ShapeProduct(1755, 5919, {2});
  g->Binary(ynn_binary_divide, 5920, 5919, 1756);
  g->Binary(ynn_binary_add, 1756, 6446, 1757);
  g->Binary(ynn_binary_pow, 1757, 6448, 1758);
  g->Binary(ynn_binary_multiply, 1754, 1758, 1759);
  g->Convert(6732, 1760);
  g->Binary(ynn_binary_multiply, 1759, 1760, 1761);
  g->Quantize(1761, 1762, 0.019696271046996117, 0);
  g->Transpose(6726, 4548, {1,0});
  g->Binary(ynn_binary_multiply, 4545, 4547, 4543);
  g->Dot(1762, 4548, YNN_INVALID_VALUE_ID, 4542, 1);
  g->DequantizeTensor(4542, YNN_INVALID_VALUE_ID, 4543, 4544);
  g->QuantizeTensor(4544, 6412, 4546, 1763);
  g->Dequantize(1763, 1765, 0.024114182218909264, 0);
  g->Transpose(6725, 4553, {1,0});
  g->Binary(ynn_binary_multiply, 4545, 4552, 4550);
  g->Dot(1762, 4553, YNN_INVALID_VALUE_ID, 4549, 1);
  g->DequantizeTensor(4549, YNN_INVALID_VALUE_ID, 4550, 4551);
  g->QuantizeTensor(4551, 6412, 4546, 1766);
  g->Dequantize(1766, 1767, 0.024114182218909264, 0);
  g->Polynomial(1767, 5923, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5923, 5924);
  g->Binary(ynn_binary_add, 5924, 5474, 5921);
  g->Binary(ynn_binary_multiply, 1767, 5472, 5922);
  g->Binary(ynn_binary_multiply, 5922, 5921, 1768);
  g->Binary(ynn_binary_multiply, 1765, 1768, 1769);
  g->Quantize(1769, 1770, 0.03567914664745331, 0);
  g->Transpose(6724, 4560, {1,0});
  g->Binary(ynn_binary_multiply, 4557, 4559, 4555);
  g->Dot(1770, 4560, YNN_INVALID_VALUE_ID, 4554, 1);
  g->DequantizeTensor(4554, YNN_INVALID_VALUE_ID, 4555, 4556);
  g->QuantizeTensor(4556, 6412, 4558, 1771);
  g->Dequantize(1771, 1772, 0.05007796362042427, 0);
  g->Unary(ynn_unary_square, 1772, 1773);
  g->Reduce(ynn_reduce_sum, 1773, 5926, {2}, true);
  g->ShapeProduct(1773, 5925, {2});
  g->Binary(ynn_binary_divide, 5926, 5925, 1775);
  g->Binary(ynn_binary_add, 1775, 6446, 1776);
  g->Binary(ynn_binary_pow, 1776, 6448, 1777);
  g->Binary(ynn_binary_multiply, 1772, 1777, 1778);
  g->Convert(6730, 1779);
  g->Binary(ynn_binary_multiply, 1778, 1779, 1780);
  g->Binary(ynn_binary_add, 1754, 1780, 1781);
}

// Scope: "Layer22 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1064, 1782, {0,0,22,0}, {-1,-1,1,-1});
  g->Reshape(1782, 1783, {1,1,256});
  g->Binary(ynn_binary_add, 1783, 7041, 1784);
  g->Binary(ynn_binary_multiply, 1784, 6444, 1786);
  g->Quantize(1781, 1787, 0.15015320479869843, 0);
  g->Transpose(6727, 4574, {1,0});
  g->Binary(ynn_binary_multiply, 4571, 4573, 4569);
  g->Dot(1787, 4574, YNN_INVALID_VALUE_ID, 4568, 1);
  g->DequantizeTensor(4568, YNN_INVALID_VALUE_ID, 4569, 4570);
  g->QuantizeTensor(4570, 6412, 4572, 1788);
  g->Dequantize(1788, 1789, 0.06102363392710686, 0);
  g->Polynomial(1789, 5929, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5929, 5930);
  g->Binary(ynn_binary_add, 5930, 5474, 5927);
  g->Binary(ynn_binary_multiply, 1789, 5472, 5928);
  g->Binary(ynn_binary_multiply, 5928, 5927, 1790);
  g->Binary(ynn_binary_multiply, 1790, 1786, 1791);
  g->Quantize(1791, 1792, 0.3779527544975281, 0);
  g->Transpose(6728, 4581, {1,0});
  g->Binary(ynn_binary_multiply, 4578, 4580, 4576);
  g->Dot(1792, 4581, YNN_INVALID_VALUE_ID, 4575, 1);
  g->DequantizeTensor(4575, YNN_INVALID_VALUE_ID, 4576, 4577);
  g->QuantizeTensor(4577, 6412, 4579, 1793);
  g->Dequantize(1793, 1794, 0.11902644485235214, 0);
  g->Unary(ynn_unary_square, 1794, 1795);
  g->Reduce(ynn_reduce_sum, 1795, 5932, {2}, true);
  g->ShapeProduct(1795, 5931, {2});
  g->Binary(ynn_binary_divide, 5932, 5931, 1797);
  g->Binary(ynn_binary_add, 1797, 6446, 1798);
  g->Binary(ynn_binary_pow, 1798, 6448, 1799);
  g->Binary(ynn_binary_multiply, 1794, 1799, 1800);
  g->Convert(6731, 1801);
  g->Binary(ynn_binary_multiply, 1800, 1801, 1802);
  g->Binary(ynn_binary_add, 1781, 1802, 1803);
  g->Convert(6723, 1804);
  g->Binary(ynn_binary_multiply, 1803, 1804, 1805);
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
  g->Quantize(1813, 1814, 0.17847737669944763, 0);
  g->Transpose(6749, 4588, {1,0});
  g->Binary(ynn_binary_multiply, 4585, 4587, 4583);
  g->Dot(1814, 4588, YNN_INVALID_VALUE_ID, 4582, 1);
  g->DequantizeTensor(4582, YNN_INVALID_VALUE_ID, 4583, 4584);
  g->QuantizeTensor(4584, 6412, 4586, 1815);
  g->Dequantize(1815, 1816, 0.16338583827018738, 0);
  g->SplitDim(1816, 1817, 2, {8,256});
  g->FuseDims(1817, 1820, 1, 2);
  g->SplitDim(1820, 1819, 1, {8,1});
  g->Unary(ynn_unary_square, 1819, 1821);
  g->Reduce(ynn_reduce_sum, 1821, 5938, {3}, true);
  g->ShapeProduct(1821, 5937, {3});
  g->Binary(ynn_binary_divide, 5938, 5937, 1822);
  g->Binary(ynn_binary_add, 1822, 6446, 1823);
  g->Binary(ynn_binary_pow, 1823, 6448, 1824);
  g->Binary(ynn_binary_multiply, 1819, 1824, 1825);
  g->Convert(6748, 1826);
  g->Binary(ynn_binary_multiply, 1825, 1826, 1827);
  g->Slice(1827, 1828, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1827, 1829, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1829, 1831);
  g->Concat({1831,1828}, 1832, 3);
  g->Binary(ynn_binary_multiply, 1827, 2173, 1833);
  g->Binary(ynn_binary_multiply, 1832, 3050, 1834);
  g->Binary(ynn_binary_add, 1833, 1834, 1835);
}

// Scope: "Layer23 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(1835, 772, 1836, false, true);
  g->Mask(1836, 6469, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6469, 5942, {-1}, true);
  g->Binary(ynn_binary_subtract, 6469, 5942, 5939);
  g->Unary(ynn_unary_exp, 5939, 5940);
  g->Reduce(ynn_reduce_sum, 5940, 5943, {-1}, true);
  g->Binary(ynn_binary_divide, 5474, 5943, 5941);
  g->Binary(ynn_binary_multiply, 5940, 5941, 1837);
  g->Matmul(1837, 774, 1838, false, false);
}

// Scope: "Layer23 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(1838, 1840, 1, 2);
  g->SplitDim(1840, 1839, 1, {1,8});
  g->FuseDims(1839, 1843, 2, 2);
  g->Quantize(1843, 1844, 0.02436024509370327, 0);
  g->Transpose(6747, 4594, {1,0});
  g->Binary(ynn_binary_multiply, 4179, 4593, 4590);
  g->Dot(1844, 4594, YNN_INVALID_VALUE_ID, 4589, 1);
  g->DequantizeTensor(4589, YNN_INVALID_VALUE_ID, 4590, 4591);
  g->QuantizeTensor(4591, 6412, 4592, 1845);
  g->Dequantize(1845, 1846, 0.027484547346830368, 0);
}

// Scope: "Layer23 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1805, 1806);
  g->Reduce(ynn_reduce_sum, 1806, 5934, {2}, true);
  g->ShapeProduct(1806, 5933, {2});
  g->Binary(ynn_binary_divide, 5934, 5933, 1808);
  g->Binary(ynn_binary_add, 1808, 6446, 1809);
  g->Binary(ynn_binary_pow, 1809, 6448, 1810);
  g->Binary(ynn_binary_multiply, 1805, 1810, 1811);
  g->Convert(6736, 1812);
  g->Binary(ynn_binary_multiply, 1811, 1812, 1813);
  BuildLayer23AttentionQueryProjection(ctx);
  BuildLayer23AttentionSdpa(ctx);
  BuildLayer23AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1846, 1847);
  g->Reduce(ynn_reduce_sum, 1847, 5945, {2}, true);
  g->ShapeProduct(1847, 5944, {2});
  g->Binary(ynn_binary_divide, 5945, 5944, 1848);
  g->Binary(ynn_binary_add, 1848, 6446, 1849);
  g->Binary(ynn_binary_pow, 1849, 6448, 1850);
  g->Binary(ynn_binary_multiply, 1846, 1850, 1851);
  g->Convert(6743, 1852);
  g->Binary(ynn_binary_multiply, 1851, 1852, 1854);
  g->Binary(ynn_binary_add, 1805, 1854, 1855);
}

// Scope: "Layer23 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1855, 1856);
  g->Reduce(ynn_reduce_sum, 1856, 5947, {2}, true);
  g->ShapeProduct(1856, 5946, {2});
  g->Binary(ynn_binary_divide, 5947, 5946, 1857);
  g->Binary(ynn_binary_add, 1857, 6446, 1858);
  g->Binary(ynn_binary_pow, 1858, 6448, 1859);
  g->Binary(ynn_binary_multiply, 1855, 1859, 1860);
  g->Convert(6746, 1861);
  g->Binary(ynn_binary_multiply, 1860, 1861, 1862);
  g->Quantize(1862, 1863, 0.02338595874607563, 0);
  g->Transpose(6740, 4601, {1,0});
  g->Binary(ynn_binary_multiply, 4598, 4600, 4596);
  g->Dot(1863, 4601, YNN_INVALID_VALUE_ID, 4595, 1);
  g->DequantizeTensor(4595, YNN_INVALID_VALUE_ID, 4596, 4597);
  g->QuantizeTensor(4597, 6412, 4599, 1865);
  g->Dequantize(1865, 1866, 0.03100394643843174, 0);
  g->Transpose(6739, 4606, {1,0});
  g->Binary(ynn_binary_multiply, 4598, 4605, 4603);
  g->Dot(1863, 4606, YNN_INVALID_VALUE_ID, 4602, 1);
  g->DequantizeTensor(4602, YNN_INVALID_VALUE_ID, 4603, 4604);
  g->QuantizeTensor(4604, 6412, 4599, 1867);
  g->Dequantize(1867, 1868, 0.03100394643843174, 0);
  g->Polynomial(1868, 5950, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5950, 5951);
  g->Binary(ynn_binary_add, 5951, 5474, 5948);
  g->Binary(ynn_binary_multiply, 1868, 5472, 5949);
  g->Binary(ynn_binary_multiply, 5949, 5948, 1869);
  g->Binary(ynn_binary_multiply, 1866, 1869, 1870);
  g->Quantize(1870, 1871, 0.0433070994913578, 0);
  g->Transpose(6738, 4613, {1,0});
  g->Binary(ynn_binary_multiply, 4610, 4612, 4608);
  g->Dot(1871, 4613, YNN_INVALID_VALUE_ID, 4607, 1);
  g->DequantizeTensor(4607, YNN_INVALID_VALUE_ID, 4608, 4609);
  g->QuantizeTensor(4609, 6412, 4611, 1872);
  g->Dequantize(1872, 1873, 0.025599855929613113, 0);
  g->Unary(ynn_unary_square, 1873, 1875);
  g->Reduce(ynn_reduce_sum, 1875, 5953, {2}, true);
  g->ShapeProduct(1875, 5952, {2});
  g->Binary(ynn_binary_divide, 5953, 5952, 1876);
  g->Binary(ynn_binary_add, 1876, 6446, 1877);
  g->Binary(ynn_binary_pow, 1877, 6448, 1878);
  g->Binary(ynn_binary_multiply, 1873, 1878, 1879);
  g->Convert(6744, 1880);
  g->Binary(ynn_binary_multiply, 1879, 1880, 1881);
  g->Binary(ynn_binary_add, 1855, 1881, 1882);
}

// Scope: "Layer23 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1064, 1883, {0,0,23,0}, {-1,-1,1,-1});
  g->Reshape(1883, 1884, {1,1,256});
  g->Binary(ynn_binary_add, 1884, 7042, 1886);
  g->Binary(ynn_binary_multiply, 1886, 6444, 1887);
  g->Quantize(1882, 1888, 0.1760360449552536, 0);
  g->Transpose(6741, 4620, {1,0});
  g->Binary(ynn_binary_multiply, 4617, 4619, 4615);
  g->Dot(1888, 4620, YNN_INVALID_VALUE_ID, 4614, 1);
  g->DequantizeTensor(4614, YNN_INVALID_VALUE_ID, 4615, 4616);
  g->QuantizeTensor(4616, 6412, 4618, 1889);
  g->Dequantize(1889, 1890, 0.07775591313838959, 0);
  g->Polynomial(1890, 5956, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5956, 5957);
  g->Binary(ynn_binary_add, 5957, 5474, 5954);
  g->Binary(ynn_binary_multiply, 1890, 5472, 5955);
  g->Binary(ynn_binary_multiply, 5955, 5954, 1891);
  g->Binary(ynn_binary_multiply, 1891, 1887, 1892);
  g->Quantize(1892, 1893, 0.3799212574958801, 0);
  g->Transpose(6742, 4627, {1,0});
  g->Binary(ynn_binary_multiply, 4624, 4626, 4622);
  g->Dot(1893, 4627, YNN_INVALID_VALUE_ID, 4621, 1);
  g->DequantizeTensor(4621, YNN_INVALID_VALUE_ID, 4622, 4623);
  g->QuantizeTensor(4623, 6412, 4625, 1894);
  g->Dequantize(1894, 1895, 0.08570276200771332, 0);
  g->Unary(ynn_unary_square, 1895, 1897);
  g->Reduce(ynn_reduce_sum, 1897, 5959, {2}, true);
  g->ShapeProduct(1897, 5958, {2});
  g->Binary(ynn_binary_divide, 5959, 5958, 1898);
  g->Binary(ynn_binary_add, 1898, 6446, 1899);
  g->Binary(ynn_binary_pow, 1899, 6448, 1900);
  g->Binary(ynn_binary_multiply, 1895, 1900, 1901);
  g->Convert(6745, 1902);
  g->Binary(ynn_binary_multiply, 1901, 1902, 1903);
  g->Binary(ynn_binary_add, 1882, 1903, 1904);
  g->Convert(6737, 1905);
  g->Binary(ynn_binary_multiply, 1904, 1905, 1906);
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
  g->Quantize(1914, 1915, 0.10295870155096054, 0);
  g->Transpose(6763, 4634, {1,0});
  g->Binary(ynn_binary_multiply, 4631, 4633, 4629);
  g->Dot(1915, 4634, YNN_INVALID_VALUE_ID, 4628, 1);
  g->DequantizeTensor(4628, YNN_INVALID_VALUE_ID, 4629, 4630);
  g->QuantizeTensor(4630, 6412, 4632, 1916);
  g->Dequantize(1916, 1917, 0.1919291466474533, 0);
  g->SplitDim(1917, 1919, 2, {8,512});
  g->FuseDims(1919, 1921, 1, 2);
  g->SplitDim(1921, 1920, 1, {8,1});
  g->Unary(ynn_unary_square, 1920, 1922);
  g->Reduce(ynn_reduce_sum, 1922, 5963, {3}, true);
  g->ShapeProduct(1922, 5962, {3});
  g->Binary(ynn_binary_divide, 5963, 5962, 1923);
  g->Binary(ynn_binary_add, 1923, 6446, 1924);
  g->Binary(ynn_binary_pow, 1924, 6448, 1925);
  g->Binary(ynn_binary_multiply, 1920, 1925, 1926);
  g->Convert(6762, 1927);
  g->Binary(ynn_binary_multiply, 1926, 1927, 1928);
  g->Slice(1928, 1929, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(1928, 1931, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 1931, 1932);
  g->Concat({1932,1929}, 1933, 3);
  g->Binary(ynn_binary_multiply, 1928, 3471, 1934);
  g->Binary(ynn_binary_multiply, 1933, 3576, 1935);
  g->Binary(ynn_binary_add, 1934, 1935, 1936);
}

// Scope: "Layer24 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer24AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(1936, 907, 1937, false, true);
  g->Mask(1937, 6470, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 6470, 5969, {-1}, true);
  g->Binary(ynn_binary_subtract, 6470, 5969, 5966);
  g->Unary(ynn_unary_exp, 5966, 5967);
  g->Reduce(ynn_reduce_sum, 5967, 5970, {-1}, true);
  g->Binary(ynn_binary_divide, 5474, 5970, 5968);
  g->Binary(ynn_binary_multiply, 5967, 5968, 1938);
  g->Matmul(1938, 909, 1939, false, false);
}

// Scope: "Layer24 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer24AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(1939, 1942, 1, 2);
  g->SplitDim(1942, 1941, 1, {1,8});
  g->FuseDims(1941, 1943, 2, 2);
  g->Quantize(1943, 1944, 0.01457924209535122, 0);
  g->Transpose(6761, 4640, {1,0});
  g->Binary(ynn_binary_multiply, 4134, 4639, 4636);
  g->Dot(1944, 4640, YNN_INVALID_VALUE_ID, 4635, 1);
  g->DequantizeTensor(4635, YNN_INVALID_VALUE_ID, 4636, 4637);
  g->QuantizeTensor(4637, 6412, 4638, 1945);
  g->Dequantize(1945, 1946, 0.02337142638862133, 0);
}

// Scope: "Layer24 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer24Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1906, 1908);
  g->Reduce(ynn_reduce_sum, 1908, 5961, {2}, true);
  g->ShapeProduct(1908, 5960, {2});
  g->Binary(ynn_binary_divide, 5961, 5960, 1909);
  g->Binary(ynn_binary_add, 1909, 6446, 1910);
  g->Binary(ynn_binary_pow, 1910, 6448, 1911);
  g->Binary(ynn_binary_multiply, 1906, 1911, 1912);
  g->Convert(6750, 1913);
  g->Binary(ynn_binary_multiply, 1912, 1913, 1914);
  BuildLayer24AttentionQueryProjection(ctx);
  BuildLayer24AttentionSdpa(ctx);
  BuildLayer24AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1946, 1947);
  g->Reduce(ynn_reduce_sum, 1947, 5972, {2}, true);
  g->ShapeProduct(1947, 5971, {2});
  g->Binary(ynn_binary_divide, 5972, 5971, 1948);
  g->Binary(ynn_binary_add, 1948, 6446, 1949);
  g->Binary(ynn_binary_pow, 1949, 6448, 1950);
  g->Binary(ynn_binary_multiply, 1946, 1950, 1951);
  g->Convert(6757, 1954);
  g->Binary(ynn_binary_multiply, 1951, 1954, 1955);
  g->Binary(ynn_binary_add, 1906, 1955, 1956);
}

// Scope: "Layer24 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer24Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1956, 1957);
  g->Reduce(ynn_reduce_sum, 1957, 5974, {2}, true);
  g->ShapeProduct(1957, 5973, {2});
  g->Binary(ynn_binary_divide, 5974, 5973, 1958);
  g->Binary(ynn_binary_add, 1958, 6446, 1959);
  g->Binary(ynn_binary_pow, 1959, 6448, 1960);
  g->Binary(ynn_binary_multiply, 1956, 1960, 1961);
  g->Convert(6760, 1962);
  g->Binary(ynn_binary_multiply, 1961, 1962, 1963);
  g->Quantize(1963, 1965, 0.018518447875976562, 0);
  g->Transpose(6754, 4647, {1,0});
  g->Binary(ynn_binary_multiply, 4644, 4646, 4642);
  g->Dot(1965, 4647, YNN_INVALID_VALUE_ID, 4641, 1);
  g->DequantizeTensor(4641, YNN_INVALID_VALUE_ID, 4642, 4643);
  g->QuantizeTensor(4643, 6412, 4645, 1966);
  g->Dequantize(1966, 1967, 0.027313001453876495, 0);
  g->Transpose(6753, 4652, {1,0});
  g->Binary(ynn_binary_multiply, 4644, 4651, 4649);
  g->Dot(1965, 4652, YNN_INVALID_VALUE_ID, 4648, 1);
  g->DequantizeTensor(4648, YNN_INVALID_VALUE_ID, 4649, 4650);
  g->QuantizeTensor(4650, 6412, 4645, 1968);
  g->Dequantize(1968, 1969, 0.027313001453876495, 0);
  g->Polynomial(1969, 5977, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5977, 5978);
  g->Binary(ynn_binary_add, 5978, 5474, 5975);
  g->Binary(ynn_binary_multiply, 1969, 5472, 5976);
  g->Binary(ynn_binary_multiply, 5976, 5975, 1970);
  g->Binary(ynn_binary_multiply, 1967, 1970, 1971);
  g->Quantize(1971, 1972, 0.01894685998558998, 0);
  g->Transpose(6752, 4659, {1,0});
  g->Binary(ynn_binary_multiply, 4656, 4658, 4654);
  g->Dot(1972, 4659, YNN_INVALID_VALUE_ID, 4653, 1);
  g->DequantizeTensor(4653, YNN_INVALID_VALUE_ID, 4654, 4655);
  g->QuantizeTensor(4655, 6412, 4657, 1973);
  g->Dequantize(1973, 1975, 0.009169002994894981, 0);
  g->Unary(ynn_unary_square, 1975, 1976);
  g->Reduce(ynn_reduce_sum, 1976, 5980, {2}, true);
  g->ShapeProduct(1976, 5979, {2});
  g->Binary(ynn_binary_divide, 5980, 5979, 1977);
  g->Binary(ynn_binary_add, 1977, 6446, 1978);
  g->Binary(ynn_binary_pow, 1978, 6448, 1979);
  g->Binary(ynn_binary_multiply, 1975, 1979, 1980);
  g->Convert(6758, 1981);
  g->Binary(ynn_binary_multiply, 1980, 1981, 1982);
  g->Binary(ynn_binary_add, 1956, 1982, 1983);
}

// Scope: "Layer24 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer24PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1064, 1984, {0,0,24,0}, {-1,-1,1,-1});
  g->Reshape(1984, 1986, {1,1,256});
  g->Binary(ynn_binary_add, 1986, 7043, 1987);
  g->Binary(ynn_binary_multiply, 1987, 6444, 1988);
  g->Quantize(1983, 1989, 0.1741907149553299, 0);
  g->Transpose(6755, 4666, {1,0});
  g->Binary(ynn_binary_multiply, 4663, 4665, 4661);
  g->Dot(1989, 4666, YNN_INVALID_VALUE_ID, 4660, 1);
  g->DequantizeTensor(4660, YNN_INVALID_VALUE_ID, 4661, 4662);
  g->QuantizeTensor(4662, 6412, 4664, 1990);
  g->Dequantize(1990, 1991, 0.08710630983114243, 0);
  g->Polynomial(1991, 5983, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5983, 5984);
  g->Binary(ynn_binary_add, 5984, 5474, 5981);
  g->Binary(ynn_binary_multiply, 1991, 5472, 5982);
  g->Binary(ynn_binary_multiply, 5982, 5981, 1992);
  g->Binary(ynn_binary_multiply, 1992, 1988, 1993);
  g->Quantize(1993, 1994, 1.0236220359802246, 0);
  g->Transpose(6756, 4673, {1,0});
  g->Binary(ynn_binary_multiply, 4670, 4672, 4668);
  g->Dot(1994, 4673, YNN_INVALID_VALUE_ID, 4667, 1);
  g->DequantizeTensor(4667, YNN_INVALID_VALUE_ID, 4668, 4669);
  g->QuantizeTensor(4669, 6412, 4671, 1995);
  g->Dequantize(1995, 1997, 0.1628752052783966, 0);
  g->Unary(ynn_unary_square, 1997, 1998);
  g->Reduce(ynn_reduce_sum, 1998, 5986, {2}, true);
  g->ShapeProduct(1998, 5985, {2});
  g->Binary(ynn_binary_divide, 5986, 5985, 1999);
  g->Binary(ynn_binary_add, 1999, 6446, 2000);
  g->Binary(ynn_binary_pow, 2000, 6448, 2001);
  g->Binary(ynn_binary_multiply, 1997, 2001, 2002);
  g->Convert(6759, 2003);
  g->Binary(ynn_binary_multiply, 2002, 2003, 2004);
  g->Binary(ynn_binary_add, 1983, 2004, 2005);
  g->Convert(6751, 2006);
  g->Binary(ynn_binary_multiply, 2005, 2006, 2008);
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
  g->Quantize(2015, 2016, 0.1674470156431198, 0);
  g->Transpose(6777, 4687, {1,0});
  g->Binary(ynn_binary_multiply, 4684, 4686, 4682);
  g->Dot(2016, 4687, YNN_INVALID_VALUE_ID, 4681, 1);
  g->DequantizeTensor(4681, YNN_INVALID_VALUE_ID, 4682, 4683);
  g->QuantizeTensor(4683, 6412, 4685, 2017);
  g->Dequantize(2017, 2019, 0.15452757477760315, 0);
  g->SplitDim(2019, 2020, 2, {8,256});
  g->FuseDims(2020, 2022, 1, 2);
  g->SplitDim(2022, 2021, 1, {8,1});
  g->Unary(ynn_unary_square, 2021, 2023);
  g->Reduce(ynn_reduce_sum, 2023, 5990, {3}, true);
  g->ShapeProduct(2023, 5989, {3});
  g->Binary(ynn_binary_divide, 5990, 5989, 2024);
  g->Binary(ynn_binary_add, 2024, 6446, 2025);
  g->Binary(ynn_binary_pow, 2025, 6448, 2026);
  g->Binary(ynn_binary_multiply, 2021, 2026, 2027);
  g->Convert(6776, 2028);
  g->Binary(ynn_binary_multiply, 2027, 2028, 2029);
  g->Slice(2029, 2031, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2029, 2032, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2032, 2033);
  g->Concat({2033,2031}, 2034, 3);
  g->Binary(ynn_binary_multiply, 2029, 2173, 2035);
  g->Binary(ynn_binary_multiply, 2034, 3050, 2036);
  g->Binary(ynn_binary_add, 2035, 2036, 2037);
}

// Scope: "Layer25 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer25AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(2037, 772, 2038, false, true);
  g->Mask(2038, 6471, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6471, 5994, {-1}, true);
  g->Binary(ynn_binary_subtract, 6471, 5994, 5991);
  g->Unary(ynn_unary_exp, 5991, 5992);
  g->Reduce(ynn_reduce_sum, 5992, 5995, {-1}, true);
  g->Binary(ynn_binary_divide, 5474, 5995, 5993);
  g->Binary(ynn_binary_multiply, 5992, 5993, 2039);
  g->Matmul(2039, 774, 2041, false, false);
}

// Scope: "Layer25 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer25AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(2041, 2043, 1, 2);
  g->SplitDim(2043, 2042, 1, {1,8});
  g->FuseDims(2042, 2044, 2, 2);
  g->Quantize(2044, 2045, 0.02325296215713024, 0);
  g->Transpose(6775, 4693, {1,0});
  g->Binary(ynn_binary_multiply, 4281, 4692, 4689);
  g->Dot(2045, 4693, YNN_INVALID_VALUE_ID, 4688, 1);
  g->DequantizeTensor(4688, YNN_INVALID_VALUE_ID, 4689, 4690);
  g->QuantizeTensor(4690, 6412, 4691, 2046);
  g->Dequantize(2046, 2047, 0.040348730981349945, 0);
}

// Scope: "Layer25 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer25Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2008, 2009);
  g->Reduce(ynn_reduce_sum, 2009, 5988, {2}, true);
  g->ShapeProduct(2009, 5987, {2});
  g->Binary(ynn_binary_divide, 5988, 5987, 2010);
  g->Binary(ynn_binary_add, 2010, 6446, 2011);
  g->Binary(ynn_binary_pow, 2011, 6448, 2012);
  g->Binary(ynn_binary_multiply, 2008, 2012, 2013);
  g->Convert(6764, 2014);
  g->Binary(ynn_binary_multiply, 2013, 2014, 2015);
  BuildLayer25AttentionQueryProjection(ctx);
  BuildLayer25AttentionSdpa(ctx);
  BuildLayer25AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2047, 2048);
  g->Reduce(ynn_reduce_sum, 2048, 5997, {2}, true);
  g->ShapeProduct(2048, 5996, {2});
  g->Binary(ynn_binary_divide, 5997, 5996, 2049);
  g->Binary(ynn_binary_add, 2049, 6446, 2050);
  g->Binary(ynn_binary_pow, 2050, 6448, 2051);
  g->Binary(ynn_binary_multiply, 2047, 2051, 2053);
  g->Convert(6771, 2054);
  g->Binary(ynn_binary_multiply, 2053, 2054, 2055);
  g->Binary(ynn_binary_add, 2008, 2055, 2056);
}

// Scope: "Layer25 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer25Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2056, 2057);
  g->Reduce(ynn_reduce_sum, 2057, 5999, {2}, true);
  g->ShapeProduct(2057, 5998, {2});
  g->Binary(ynn_binary_divide, 5999, 5998, 2058);
  g->Binary(ynn_binary_add, 2058, 6446, 2059);
  g->Binary(ynn_binary_pow, 2059, 6448, 2060);
  g->Binary(ynn_binary_multiply, 2056, 2060, 2061);
  g->Convert(6774, 2062);
  g->Binary(ynn_binary_multiply, 2061, 2062, 2065);
  g->Quantize(2065, 2066, 0.02161904238164425, 0);
  g->Transpose(6768, 4706, {1,0});
  g->Binary(ynn_binary_multiply, 4704, 4705, 4702);
  g->Dot(2066, 4706, YNN_INVALID_VALUE_ID, 4701, 1);
  g->DequantizeTensor(4701, YNN_INVALID_VALUE_ID, 4702, 4703);
  g->QuantizeTensor(4703, 6412, 4346, 2067);
  g->Dequantize(2067, 2068, 0.03297245129942894, 0);
  g->Transpose(6767, 4711, {1,0});
  g->Binary(ynn_binary_multiply, 4704, 4710, 4708);
  g->Dot(2066, 4711, YNN_INVALID_VALUE_ID, 4707, 1);
  g->DequantizeTensor(4707, YNN_INVALID_VALUE_ID, 4708, 4709);
  g->QuantizeTensor(4709, 6412, 4346, 2069);
  g->Dequantize(2069, 2070, 0.03297245129942894, 0);
  g->Polynomial(2070, 6004, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6004, 6005);
  g->Binary(ynn_binary_add, 6005, 5474, 6002);
  g->Binary(ynn_binary_multiply, 2070, 5472, 6003);
  g->Binary(ynn_binary_multiply, 6003, 6002, 2071);
  g->Binary(ynn_binary_multiply, 2068, 2071, 2072);
  g->Quantize(2072, 2073, 0.032726388424634933, 0);
  g->Transpose(6766, 4718, {1,0});
  g->Binary(ynn_binary_multiply, 4715, 4717, 4713);
  g->Dot(2073, 4718, YNN_INVALID_VALUE_ID, 4712, 1);
  g->DequantizeTensor(4712, YNN_INVALID_VALUE_ID, 4713, 4714);
  g->QuantizeTensor(4714, 6412, 4716, 2075);
  g->Dequantize(2075, 2076, 0.00990387424826622, 0);
  g->Unary(ynn_unary_square, 2076, 2077);
  g->Reduce(ynn_reduce_sum, 2077, 6007, {2}, true);
  g->ShapeProduct(2077, 6006, {2});
  g->Binary(ynn_binary_divide, 6007, 6006, 2078);
  g->Binary(ynn_binary_add, 2078, 6446, 2079);
  g->Binary(ynn_binary_pow, 2079, 6448, 2080);
  g->Binary(ynn_binary_multiply, 2076, 2080, 2081);
  g->Convert(6772, 2082);
  g->Binary(ynn_binary_multiply, 2081, 2082, 2083);
  g->Binary(ynn_binary_add, 2056, 2083, 2084);
}

// Scope: "Layer25 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer25PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1064, 2086, {0,0,25,0}, {-1,-1,1,-1});
  g->Reshape(2086, 2087, {1,1,256});
  g->Binary(ynn_binary_add, 2087, 7044, 2088);
  g->Binary(ynn_binary_multiply, 2088, 6444, 2089);
  g->Quantize(2084, 2090, 0.1164931058883667, 0);
  g->Transpose(6769, 4725, {1,0});
  g->Binary(ynn_binary_multiply, 4722, 4724, 4720);
  g->Dot(2090, 4725, YNN_INVALID_VALUE_ID, 4719, 1);
  g->DequantizeTensor(4719, YNN_INVALID_VALUE_ID, 4720, 4721);
  g->QuantizeTensor(4721, 6412, 4723, 2091);
  g->Dequantize(2091, 2092, 0.11269685626029968, 0);
  g->Polynomial(2092, 6010, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6010, 6011);
  g->Binary(ynn_binary_add, 6011, 5474, 6008);
  g->Binary(ynn_binary_multiply, 2092, 5472, 6009);
  g->Binary(ynn_binary_multiply, 6009, 6008, 2093);
  g->Binary(ynn_binary_multiply, 2093, 2089, 2094);
  g->Quantize(2094, 2095, 0.5157480239868164, 0);
  g->Transpose(6770, 4732, {1,0});
  g->Binary(ynn_binary_multiply, 4729, 4731, 4727);
  g->Dot(2095, 4732, YNN_INVALID_VALUE_ID, 4726, 1);
  g->DequantizeTensor(4726, YNN_INVALID_VALUE_ID, 4727, 4728);
  g->QuantizeTensor(4728, 6412, 4730, 2097);
  g->Dequantize(2097, 2098, 0.3825955092906952, 0);
  g->Unary(ynn_unary_square, 2098, 2099);
  g->Reduce(ynn_reduce_sum, 2099, 6013, {2}, true);
  g->ShapeProduct(2099, 6012, {2});
  g->Binary(ynn_binary_divide, 6013, 6012, 2100);
  g->Binary(ynn_binary_add, 2100, 6446, 2101);
  g->Binary(ynn_binary_pow, 2101, 6448, 2102);
  g->Binary(ynn_binary_multiply, 2098, 2102, 2103);
  g->Convert(6773, 2104);
  g->Binary(ynn_binary_multiply, 2103, 2104, 2105);
  g->Binary(ynn_binary_add, 2084, 2105, 2106);
  g->Convert(6765, 2108);
  g->Binary(ynn_binary_multiply, 2106, 2108, 2109);
}

// Scope: "Layer25"
LAB_YNN_BUILDER_NOINLINE void BuildLayer25(Context& ctx) {
  BuildLayer25Attention(ctx);
  BuildLayer25Mlp(ctx);
  BuildLayer25PerLayerEmbedding(ctx);
}

// Scope: "Layer26 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer26AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(2116, 2117, 0.14451591670513153, 0);
  g->Transpose(6791, 4739, {1,0});
  g->Binary(ynn_binary_multiply, 4736, 4738, 4734);
  g->Dot(2117, 4739, YNN_INVALID_VALUE_ID, 4733, 1);
  g->DequantizeTensor(4733, YNN_INVALID_VALUE_ID, 4734, 4735);
  g->QuantizeTensor(4735, 6412, 4737, 2119);
  g->Dequantize(2119, 2120, 0.25196850299835205, 0);
  g->SplitDim(2120, 2121, 2, {8,256});
  g->FuseDims(2121, 2123, 1, 2);
  g->SplitDim(2123, 2122, 1, {8,1});
  g->Unary(ynn_unary_square, 2122, 2124);
  g->Reduce(ynn_reduce_sum, 2124, 6017, {3}, true);
  g->ShapeProduct(2124, 6016, {3});
  g->Binary(ynn_binary_divide, 6017, 6016, 2125);
  g->Binary(ynn_binary_add, 2125, 6446, 2126);
  g->Binary(ynn_binary_pow, 2126, 6448, 2127);
  g->Binary(ynn_binary_multiply, 2122, 2127, 2128);
  g->Convert(6790, 2129);
  g->Binary(ynn_binary_multiply, 2128, 2129, 2131);
  g->Slice(2131, 2132, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2131, 2133, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2133, 2134);
  g->Concat({2134,2132}, 2135, 3);
  g->Binary(ynn_binary_multiply, 2131, 2173, 2136);
  g->Binary(ynn_binary_multiply, 2135, 3050, 2137);
  g->Binary(ynn_binary_add, 2136, 2137, 2138);
}

// Scope: "Layer26 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer26AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(2138, 772, 2139, false, true);
  g->Mask(2139, 6472, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6472, 6021, {-1}, true);
  g->Binary(ynn_binary_subtract, 6472, 6021, 6018);
  g->Unary(ynn_unary_exp, 6018, 6019);
  g->Reduce(ynn_reduce_sum, 6019, 6022, {-1}, true);
  g->Binary(ynn_binary_divide, 5474, 6022, 6020);
  g->Binary(ynn_binary_multiply, 6019, 6020, 2141);
  g->Matmul(2141, 774, 2142, false, false);
}

// Scope: "Layer26 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer26AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(2142, 2144, 1, 2);
  g->SplitDim(2144, 2143, 1, {1,8});
  g->FuseDims(2143, 2145, 2, 2);
  g->Quantize(2145, 2146, 0.023129930719733238, 0);
  g->Transpose(6789, 4745, {1,0});
  g->Binary(ynn_binary_multiply, 4299, 4744, 4741);
  g->Dot(2146, 4745, YNN_INVALID_VALUE_ID, 4740, 1);
  g->DequantizeTensor(4740, YNN_INVALID_VALUE_ID, 4741, 4742);
  g->QuantizeTensor(4742, 6412, 4743, 2147);
  g->Dequantize(2147, 2148, 0.04343831539154053, 0);
}

// Scope: "Layer26 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer26Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2109, 2110);
  g->Reduce(ynn_reduce_sum, 2110, 6015, {2}, true);
  g->ShapeProduct(2110, 6014, {2});
  g->Binary(ynn_binary_divide, 6015, 6014, 2111);
  g->Binary(ynn_binary_add, 2111, 6446, 2112);
  g->Binary(ynn_binary_pow, 2112, 6448, 2113);
  g->Binary(ynn_binary_multiply, 2109, 2113, 2114);
  g->Convert(6778, 2115);
  g->Binary(ynn_binary_multiply, 2114, 2115, 2116);
  BuildLayer26AttentionQueryProjection(ctx);
  BuildLayer26AttentionSdpa(ctx);
  BuildLayer26AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2148, 2149);
  g->Reduce(ynn_reduce_sum, 2149, 6024, {2}, true);
  g->ShapeProduct(2149, 6023, {2});
  g->Binary(ynn_binary_divide, 6024, 6023, 2150);
  g->Binary(ynn_binary_add, 2150, 6446, 2151);
  g->Binary(ynn_binary_pow, 2151, 6448, 2153);
  g->Binary(ynn_binary_multiply, 2148, 2153, 2154);
  g->Convert(6785, 2155);
  g->Binary(ynn_binary_multiply, 2154, 2155, 2156);
  g->Binary(ynn_binary_add, 2109, 2156, 2157);
}

// Scope: "Layer26 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer26Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2157, 2158);
  g->Reduce(ynn_reduce_sum, 2158, 6026, {2}, true);
  g->ShapeProduct(2158, 6025, {2});
  g->Binary(ynn_binary_divide, 6026, 6025, 2159);
  g->Binary(ynn_binary_add, 2159, 6446, 2160);
  g->Binary(ynn_binary_pow, 2160, 6448, 2161);
  g->Binary(ynn_binary_multiply, 2157, 2161, 2162);
  g->Convert(6788, 2164);
  g->Binary(ynn_binary_multiply, 2162, 2164, 2165);
  g->Quantize(2165, 2166, 0.02699781395494938, 0);
  g->Transpose(6782, 4752, {1,0});
  g->Binary(ynn_binary_multiply, 4749, 4751, 4747);
  g->Dot(2166, 4752, YNN_INVALID_VALUE_ID, 4746, 1);
  g->DequantizeTensor(4746, YNN_INVALID_VALUE_ID, 4747, 4748);
  g->QuantizeTensor(4748, 6412, 4750, 2167);
  g->Dequantize(2167, 2168, 0.04478347674012184, 0);
  g->Transpose(6781, 4757, {1,0});
  g->Binary(ynn_binary_multiply, 4749, 4756, 4754);
  g->Dot(2166, 4757, YNN_INVALID_VALUE_ID, 4753, 1);
  g->DequantizeTensor(4753, YNN_INVALID_VALUE_ID, 4754, 4755);
  g->QuantizeTensor(4755, 6412, 4750, 2169);
  g->Dequantize(2169, 2170, 0.04478347674012184, 0);
  g->Polynomial(2170, 6029, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6029, 6030);
  g->Binary(ynn_binary_add, 6030, 5474, 6027);
  g->Binary(ynn_binary_multiply, 2170, 5472, 6028);
  g->Binary(ynn_binary_multiply, 6028, 6027, 2171);
  g->Binary(ynn_binary_multiply, 2168, 2171, 2172);
  g->Quantize(2172, 2176, 0.05019685998558998, 0);
  g->Transpose(6780, 4764, {1,0});
  g->Binary(ynn_binary_multiply, 4761, 4763, 4759);
  g->Dot(2176, 4764, YNN_INVALID_VALUE_ID, 4758, 1);
  g->DequantizeTensor(4758, YNN_INVALID_VALUE_ID, 4759, 4760);
  g->QuantizeTensor(4760, 6412, 4762, 2177);
  g->Dequantize(2177, 2178, 0.017497630789875984, 0);
  g->Unary(ynn_unary_square, 2178, 2179);
  g->Reduce(ynn_reduce_sum, 2179, 6032, {2}, true);
  g->ShapeProduct(2179, 6031, {2});
  g->Binary(ynn_binary_divide, 6032, 6031, 2180);
  g->Binary(ynn_binary_add, 2180, 6446, 2181);
  g->Binary(ynn_binary_pow, 2181, 6448, 2182);
  g->Binary(ynn_binary_multiply, 2178, 2182, 2183);
  g->Convert(6786, 2184);
  g->Binary(ynn_binary_multiply, 2183, 2184, 2185);
  g->Binary(ynn_binary_add, 2157, 2185, 2187);
}

// Scope: "Layer26 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer26PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1064, 2188, {0,0,26,0}, {-1,-1,1,-1});
  g->Reshape(2188, 2189, {1,1,256});
  g->Binary(ynn_binary_add, 2189, 7045, 2190);
  g->Binary(ynn_binary_multiply, 2190, 6444, 2191);
  g->Quantize(2187, 2192, 0.11300035566091537, 0);
  g->Transpose(6783, 4771, {1,0});
  g->Binary(ynn_binary_multiply, 4768, 4770, 4766);
  g->Dot(2192, 4771, YNN_INVALID_VALUE_ID, 4765, 1);
  g->DequantizeTensor(4765, YNN_INVALID_VALUE_ID, 4766, 4767);
  g->QuantizeTensor(4767, 6412, 4769, 2193);
  g->Dequantize(2193, 2194, 0.10088583081960678, 0);
  g->Polynomial(2194, 6035, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6035, 6036);
  g->Binary(ynn_binary_add, 6036, 5474, 6033);
  g->Binary(ynn_binary_multiply, 2194, 5472, 6034);
  g->Binary(ynn_binary_multiply, 6034, 6033, 2195);
  g->Binary(ynn_binary_multiply, 2195, 2191, 2196);
  g->Quantize(2196, 2198, 0.5472440719604492, 0);
  g->Transpose(6784, 4778, {1,0});
  g->Binary(ynn_binary_multiply, 4775, 4777, 4773);
  g->Dot(2198, 4778, YNN_INVALID_VALUE_ID, 4772, 1);
  g->DequantizeTensor(4772, YNN_INVALID_VALUE_ID, 4773, 4774);
  g->QuantizeTensor(4774, 6412, 4776, 2199);
  g->Dequantize(2199, 2200, 0.34460699558258057, 0);
  g->Unary(ynn_unary_square, 2200, 2201);
  g->Reduce(ynn_reduce_sum, 2201, 6038, {2}, true);
  g->ShapeProduct(2201, 6037, {2});
  g->Binary(ynn_binary_divide, 6038, 6037, 2202);
  g->Binary(ynn_binary_add, 2202, 6446, 2203);
  g->Binary(ynn_binary_pow, 2203, 6448, 2204);
  g->Binary(ynn_binary_multiply, 2200, 2204, 2205);
  g->Convert(6787, 2206);
  g->Binary(ynn_binary_multiply, 2205, 2206, 2207);
  g->Binary(ynn_binary_add, 2187, 2207, 2208);
  g->Convert(6779, 2209);
  g->Binary(ynn_binary_multiply, 2208, 2209, 2210);
}

// Scope: "Layer26"
LAB_YNN_BUILDER_NOINLINE void BuildLayer26(Context& ctx) {
  BuildLayer26Attention(ctx);
  BuildLayer26Mlp(ctx);
  BuildLayer26PerLayerEmbedding(ctx);
}

}  // namespace BuildGemma4DecodeSource
