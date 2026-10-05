// Generated YNNPACK builder; do not edit.
#include "gemma4_decode_builder.h"

namespace BuildGemma4DecodeSource {

// Scope: "Layer16 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(1090, 1091, 0.44548678398132324, 0);
  g->Transpose(6564, 4152, {1,0});
  g->Binary(ynn_binary_multiply, 4149, 4151, 4147);
  g->Dot(1091, 4152, YNN_INVALID_VALUE_ID, 4146, 1);
  g->DequantizeTensor(4146, YNN_INVALID_VALUE_ID, 4147, 4148);
  g->QuantizeTensor(4148, 6342, 4150, 1093);
  g->Dequantize(1093, 1094, 0.3641732335090637, 0);
  g->SplitDim(1094, 1095, 2, {8,256});
  g->Transpose(1095, 1096, {0,2,1,3});
  g->Unary(ynn_unary_square, 1096, 1097);
  g->Reduce(ynn_reduce_sum, 1097, 5670, {3}, true);
  g->ShapeProduct(1097, 5669, {3});
  g->Binary(ynn_binary_divide, 5670, 5669, 1098);
  g->Binary(ynn_binary_add, 1098, 6376, 1099);
  g->Binary(ynn_binary_pow, 1099, 6378, 1100);
  g->Binary(ynn_binary_multiply, 1096, 1100, 1101);
  g->Convert(6563, 1102);
  g->Binary(ynn_binary_multiply, 1101, 1102, 1104);
  g->Slice(1104, 1105, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1104, 1106, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1106, 1107);
  g->Concat({1107,1105}, 1108, 3);
  g->Binary(ynn_binary_multiply, 1104, 2133, 1109);
  g->Binary(ynn_binary_multiply, 1108, 2992, 1110);
  g->Binary(ynn_binary_add, 1109, 1110, 1111);
}

// Scope: "Layer16 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(1111, 762, 1112, false, true);
  g->Mask(1112, 6391, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6391, 5674, {-1}, true);
  g->Binary(ynn_binary_subtract, 6391, 5674, 5671);
  g->Unary(ynn_unary_exp, 5671, 5672);
  g->Reduce(ynn_reduce_sum, 5672, 5675, {-1}, true);
  g->Binary(ynn_binary_divide, 5404, 5675, 5673);
  g->Binary(ynn_binary_multiply, 5672, 5673, 1114);
  g->Matmul(1114, 764, 1115, false, false);
}

// Scope: "Layer16 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1115, 1116, {0,2,1,3});
  g->FuseDims(1116, 1117, 2, 2);
  g->Quantize(1117, 1118, 0.023745087906718254, 0);
  g->Transpose(6562, 4159, {1,0});
  g->Binary(ynn_binary_multiply, 4156, 4158, 4154);
  g->Dot(1118, 4159, YNN_INVALID_VALUE_ID, 4153, 1);
  g->DequantizeTensor(4153, YNN_INVALID_VALUE_ID, 4154, 4155);
  g->QuantizeTensor(4155, 6342, 4157, 1119);
  g->Dequantize(1119, 1120, 0.02639034017920494, 0);
}

// Scope: "Layer16 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1083, 1084);
  g->Reduce(ynn_reduce_sum, 1084, 5668, {2}, true);
  g->ShapeProduct(1084, 5667, {2});
  g->Binary(ynn_binary_divide, 5668, 5667, 1085);
  g->Binary(ynn_binary_add, 1085, 6376, 1086);
  g->Binary(ynn_binary_pow, 1086, 6378, 1087);
  g->Binary(ynn_binary_multiply, 1083, 1087, 1088);
  g->Convert(6551, 1089);
  g->Binary(ynn_binary_multiply, 1088, 1089, 1090);
  BuildLayer16AttentionQueryProjection(ctx);
  BuildLayer16AttentionSdpa(ctx);
  BuildLayer16AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1120, 1121);
  g->Reduce(ynn_reduce_sum, 1121, 5677, {2}, true);
  g->ShapeProduct(1121, 5676, {2});
  g->Binary(ynn_binary_divide, 5677, 5676, 1122);
  g->Binary(ynn_binary_add, 1122, 6376, 1123);
  g->Binary(ynn_binary_pow, 1123, 6378, 1125);
  g->Binary(ynn_binary_multiply, 1120, 1125, 1126);
  g->Convert(6558, 1127);
  g->Binary(ynn_binary_multiply, 1126, 1127, 1128);
  g->Binary(ynn_binary_add, 1083, 1128, 1129);
}

// Scope: "Layer16 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1129, 1130);
  g->Reduce(ynn_reduce_sum, 1130, 5679, {2}, true);
  g->ShapeProduct(1130, 5678, {2});
  g->Binary(ynn_binary_divide, 5679, 5678, 1131);
  g->Binary(ynn_binary_add, 1131, 6376, 1132);
  g->Binary(ynn_binary_pow, 1132, 6378, 1133);
  g->Binary(ynn_binary_multiply, 1129, 1133, 1134);
  g->Convert(6561, 1136);
  g->Binary(ynn_binary_multiply, 1134, 1136, 1137);
  g->Quantize(1137, 1138, 0.019740456715226173, 0);
  g->Transpose(6555, 4166, {1,0});
  g->Binary(ynn_binary_multiply, 4163, 4165, 4161);
  g->Dot(1138, 4166, YNN_INVALID_VALUE_ID, 4160, 1);
  g->DequantizeTensor(4160, YNN_INVALID_VALUE_ID, 4161, 4162);
  g->QuantizeTensor(4162, 6342, 4164, 1139);
  g->Dequantize(1139, 1140, 0.02042323723435402, 0);
  g->Transpose(6554, 4171, {1,0});
  g->Binary(ynn_binary_multiply, 4163, 4170, 4168);
  g->Dot(1138, 4171, YNN_INVALID_VALUE_ID, 4167, 1);
  g->DequantizeTensor(4167, YNN_INVALID_VALUE_ID, 4168, 4169);
  g->QuantizeTensor(4169, 6342, 4164, 1141);
  g->Dequantize(1141, 1142, 0.02042323723435402, 0);
  g->Polynomial(1142, 5682, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5682, 5683);
  g->Binary(ynn_binary_add, 5683, 5404, 5680);
  g->Binary(ynn_binary_multiply, 1142, 5402, 5681);
  g->Binary(ynn_binary_multiply, 5681, 5680, 1143);
  g->Binary(ynn_binary_multiply, 1140, 1143, 1144);
  g->Quantize(1144, 1146, 0.021530522033572197, 0);
  g->Transpose(6553, 4178, {1,0});
  g->Binary(ynn_binary_multiply, 4175, 4177, 4173);
  g->Dot(1146, 4178, YNN_INVALID_VALUE_ID, 4172, 1);
  g->DequantizeTensor(4172, YNN_INVALID_VALUE_ID, 4173, 4174);
  g->QuantizeTensor(4174, 6342, 4176, 1147);
  g->Dequantize(1147, 1148, 0.011490405537188053, 0);
  g->Unary(ynn_unary_square, 1148, 1149);
  g->Reduce(ynn_reduce_sum, 1149, 5685, {2}, true);
  g->ShapeProduct(1149, 5684, {2});
  g->Binary(ynn_binary_divide, 5685, 5684, 1150);
  g->Binary(ynn_binary_add, 1150, 6376, 1151);
  g->Binary(ynn_binary_pow, 1151, 6378, 1152);
  g->Binary(ynn_binary_multiply, 1148, 1152, 1153);
  g->Convert(6559, 1154);
  g->Binary(ynn_binary_multiply, 1153, 1154, 1155);
  g->Binary(ynn_binary_add, 1129, 1155, 1158);
}

// Scope: "Layer16 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1047, 1159, {0,0,16,0}, {-1,-1,1,-1});
  g->Reshape(1159, 1160, {1,1,256});
  g->Binary(ynn_binary_add, 1160, 6964, 1161);
  g->Binary(ynn_binary_multiply, 1161, 6374, 1162);
  g->Quantize(1158, 1163, 0.1693648248910904, 0);
  g->Transpose(6556, 4185, {1,0});
  g->Binary(ynn_binary_multiply, 4182, 4184, 4180);
  g->Dot(1163, 4185, YNN_INVALID_VALUE_ID, 4179, 1);
  g->DequantizeTensor(4179, YNN_INVALID_VALUE_ID, 4180, 4181);
  g->QuantizeTensor(4181, 6342, 4183, 1164);
  g->Dequantize(1164, 1165, 0.07234252989292145, 0);
  g->Polynomial(1165, 5688, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5688, 5689);
  g->Binary(ynn_binary_add, 5689, 5404, 5686);
  g->Binary(ynn_binary_multiply, 1165, 5402, 5687);
  g->Binary(ynn_binary_multiply, 5687, 5686, 1166);
  g->Binary(ynn_binary_multiply, 1166, 1162, 1167);
  g->Quantize(1167, 1169, 0.8779527544975281, 0);
  g->Transpose(6557, 4192, {1,0});
  g->Binary(ynn_binary_multiply, 4189, 4191, 4187);
  g->Dot(1169, 4192, YNN_INVALID_VALUE_ID, 4186, 1);
  g->DequantizeTensor(4186, YNN_INVALID_VALUE_ID, 4187, 4188);
  g->QuantizeTensor(4188, 6342, 4190, 1170);
  g->Dequantize(1170, 1171, 0.16087517142295837, 0);
  g->Unary(ynn_unary_square, 1171, 1172);
  g->Reduce(ynn_reduce_sum, 1172, 5691, {2}, true);
  g->ShapeProduct(1172, 5690, {2});
  g->Binary(ynn_binary_divide, 5691, 5690, 1173);
  g->Binary(ynn_binary_add, 1173, 6376, 1174);
  g->Binary(ynn_binary_pow, 1174, 6378, 1175);
  g->Binary(ynn_binary_multiply, 1171, 1175, 1176);
  g->Convert(6560, 1177);
  g->Binary(ynn_binary_multiply, 1176, 1177, 1178);
  g->Binary(ynn_binary_add, 1158, 1178, 1180);
  g->Convert(6552, 1181);
  g->Binary(ynn_binary_multiply, 1180, 1181, 1182);
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
  g->Quantize(1189, 1190, 0.25072598457336426, 0);
  g->Transpose(6578, 4199, {1,0});
  g->Binary(ynn_binary_multiply, 4196, 4198, 4194);
  g->Dot(1190, 4199, YNN_INVALID_VALUE_ID, 4193, 1);
  g->DequantizeTensor(4193, YNN_INVALID_VALUE_ID, 4194, 4195);
  g->QuantizeTensor(4195, 6342, 4197, 1191);
  g->Dequantize(1191, 1192, 0.374015748500824, 0);
  g->SplitDim(1192, 1193, 2, {8,256});
  g->Transpose(1193, 1194, {0,2,1,3});
  g->Unary(ynn_unary_square, 1194, 1195);
  g->Reduce(ynn_reduce_sum, 1195, 5695, {3}, true);
  g->ShapeProduct(1195, 5694, {3});
  g->Binary(ynn_binary_divide, 5695, 5694, 1196);
  g->Binary(ynn_binary_add, 1196, 6376, 1197);
  g->Binary(ynn_binary_pow, 1197, 6378, 1198);
  g->Binary(ynn_binary_multiply, 1194, 1198, 1199);
  g->Convert(6577, 1201);
  g->Binary(ynn_binary_multiply, 1199, 1201, 1202);
  g->Slice(1202, 1203, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1202, 1204, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1204, 1205);
  g->Concat({1205,1203}, 1206, 3);
  g->Binary(ynn_binary_multiply, 1202, 2133, 1207);
  g->Binary(ynn_binary_multiply, 1206, 2992, 1208);
  g->Binary(ynn_binary_add, 1207, 1208, 1209);
}

// Scope: "Layer17 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(1209, 762, 1210, false, true);
  g->Mask(1210, 6392, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6392, 5704, {-1}, true);
  g->Binary(ynn_binary_subtract, 6392, 5704, 5701);
  g->Unary(ynn_unary_exp, 5701, 5702);
  g->Reduce(ynn_reduce_sum, 5702, 5705, {-1}, true);
  g->Binary(ynn_binary_divide, 5404, 5705, 5703);
  g->Binary(ynn_binary_multiply, 5702, 5703, 1212);
  g->Matmul(1212, 764, 1213, false, false);
}

// Scope: "Layer17 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1213, 1214, {0,2,1,3});
  g->FuseDims(1214, 1215, 2, 2);
  g->Quantize(1215, 1216, 0.023375993594527245, 0);
  g->Transpose(6576, 4206, {1,0});
  g->Binary(ynn_binary_multiply, 4203, 4205, 4201);
  g->Dot(1216, 4206, YNN_INVALID_VALUE_ID, 4200, 1);
  g->DequantizeTensor(4200, YNN_INVALID_VALUE_ID, 4201, 4202);
  g->QuantizeTensor(4202, 6342, 4204, 1217);
  g->Dequantize(1217, 1218, 0.020179564133286476, 0);
}

// Scope: "Layer17 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1182, 1183);
  g->Reduce(ynn_reduce_sum, 1183, 5693, {2}, true);
  g->ShapeProduct(1183, 5692, {2});
  g->Binary(ynn_binary_divide, 5693, 5692, 1184);
  g->Binary(ynn_binary_add, 1184, 6376, 1185);
  g->Binary(ynn_binary_pow, 1185, 6378, 1186);
  g->Binary(ynn_binary_multiply, 1182, 1186, 1187);
  g->Convert(6565, 1188);
  g->Binary(ynn_binary_multiply, 1187, 1188, 1189);
  BuildLayer17AttentionQueryProjection(ctx);
  BuildLayer17AttentionSdpa(ctx);
  BuildLayer17AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1218, 1219);
  g->Reduce(ynn_reduce_sum, 1219, 5707, {2}, true);
  g->ShapeProduct(1219, 5706, {2});
  g->Binary(ynn_binary_divide, 5707, 5706, 1220);
  g->Binary(ynn_binary_add, 1220, 6376, 1222);
  g->Binary(ynn_binary_pow, 1222, 6378, 1223);
  g->Binary(ynn_binary_multiply, 1218, 1223, 1224);
  g->Convert(6572, 1225);
  g->Binary(ynn_binary_multiply, 1224, 1225, 1226);
  g->Binary(ynn_binary_add, 1182, 1226, 1227);
}

// Scope: "Layer17 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1227, 1228);
  g->Reduce(ynn_reduce_sum, 1228, 5709, {2}, true);
  g->ShapeProduct(1228, 5708, {2});
  g->Binary(ynn_binary_divide, 5709, 5708, 1229);
  g->Binary(ynn_binary_add, 1229, 6376, 1230);
  g->Binary(ynn_binary_pow, 1230, 6378, 1231);
  g->Binary(ynn_binary_multiply, 1227, 1231, 1233);
  g->Convert(6575, 1234);
  g->Binary(ynn_binary_multiply, 1233, 1234, 1235);
  g->Quantize(1235, 1236, 0.02002163790166378, 0);
  g->Transpose(6569, 4213, {1,0});
  g->Binary(ynn_binary_multiply, 4210, 4212, 4208);
  g->Dot(1236, 4213, YNN_INVALID_VALUE_ID, 4207, 1);
  g->DequantizeTensor(4207, YNN_INVALID_VALUE_ID, 4208, 4209);
  g->QuantizeTensor(4209, 6342, 4211, 1237);
  g->Dequantize(1237, 1238, 0.02325296215713024, 0);
  g->Transpose(6568, 4218, {1,0});
  g->Binary(ynn_binary_multiply, 4210, 4217, 4215);
  g->Dot(1236, 4218, YNN_INVALID_VALUE_ID, 4214, 1);
  g->DequantizeTensor(4214, YNN_INVALID_VALUE_ID, 4215, 4216);
  g->QuantizeTensor(4216, 6342, 4211, 1239);
  g->Dequantize(1239, 1240, 0.02325296215713024, 0);
  g->Polynomial(1240, 5712, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5712, 5713);
  g->Binary(ynn_binary_add, 5713, 5404, 5710);
  g->Binary(ynn_binary_multiply, 1240, 5402, 5711);
  g->Binary(ynn_binary_multiply, 5711, 5710, 1241);
  g->Binary(ynn_binary_multiply, 1238, 1241, 1243);
  g->Quantize(1243, 1244, 0.03641733527183533, 0);
  g->Transpose(6567, 4225, {1,0});
  g->Binary(ynn_binary_multiply, 4222, 4224, 4220);
  g->Dot(1244, 4225, YNN_INVALID_VALUE_ID, 4219, 1);
  g->DequantizeTensor(4219, YNN_INVALID_VALUE_ID, 4220, 4221);
  g->QuantizeTensor(4221, 6342, 4223, 1245);
  g->Dequantize(1245, 1246, 0.022161640226840973, 0);
  g->Unary(ynn_unary_square, 1246, 1247);
  g->Reduce(ynn_reduce_sum, 1247, 5715, {2}, true);
  g->ShapeProduct(1247, 5714, {2});
  g->Binary(ynn_binary_divide, 5715, 5714, 1248);
  g->Binary(ynn_binary_add, 1248, 6376, 1249);
  g->Binary(ynn_binary_pow, 1249, 6378, 1250);
  g->Binary(ynn_binary_multiply, 1246, 1250, 1251);
  g->Convert(6573, 1252);
  g->Binary(ynn_binary_multiply, 1251, 1252, 1254);
  g->Binary(ynn_binary_add, 1227, 1254, 1255);
}

// Scope: "Layer17 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1047, 1256, {0,0,17,0}, {-1,-1,1,-1});
  g->Reshape(1256, 1257, {1,1,256});
  g->Binary(ynn_binary_add, 1257, 6965, 1258);
  g->Binary(ynn_binary_multiply, 1258, 6374, 1259);
  g->Quantize(1255, 1260, 0.16417057812213898, 0);
  g->Transpose(6570, 4239, {1,0});
  g->Binary(ynn_binary_multiply, 4236, 4238, 4234);
  g->Dot(1260, 4239, YNN_INVALID_VALUE_ID, 4233, 1);
  g->DequantizeTensor(4233, YNN_INVALID_VALUE_ID, 4234, 4235);
  g->QuantizeTensor(4235, 6342, 4237, 1261);
  g->Dequantize(1261, 1262, 0.0821850448846817, 0);
  g->Polynomial(1262, 5718, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5718, 5719);
  g->Binary(ynn_binary_add, 5719, 5404, 5716);
  g->Binary(ynn_binary_multiply, 1262, 5402, 5717);
  g->Binary(ynn_binary_multiply, 5717, 5716, 1263);
  g->Binary(ynn_binary_multiply, 1263, 1259, 1266);
  g->Quantize(1266, 1267, 0.8188976645469666, 0);
  g->Transpose(6571, 4246, {1,0});
  g->Binary(ynn_binary_multiply, 4243, 4245, 4241);
  g->Dot(1267, 4246, YNN_INVALID_VALUE_ID, 4240, 1);
  g->DequantizeTensor(4240, YNN_INVALID_VALUE_ID, 4241, 4242);
  g->QuantizeTensor(4242, 6342, 4244, 1268);
  g->Dequantize(1268, 1269, 0.2322644591331482, 0);
  g->Unary(ynn_unary_square, 1269, 1270);
  g->Reduce(ynn_reduce_sum, 1270, 5723, {2}, true);
  g->ShapeProduct(1270, 5722, {2});
  g->Binary(ynn_binary_divide, 5723, 5722, 1271);
  g->Binary(ynn_binary_add, 1271, 6376, 1272);
  g->Binary(ynn_binary_pow, 1272, 6378, 1273);
  g->Binary(ynn_binary_multiply, 1269, 1273, 1274);
  g->Convert(6574, 1275);
  g->Binary(ynn_binary_multiply, 1274, 1275, 1277);
  g->Binary(ynn_binary_add, 1255, 1277, 1278);
  g->Convert(6566, 1279);
  g->Binary(ynn_binary_multiply, 1278, 1279, 1280);
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
  g->Quantize(1288, 1289, 0.3068588376045227, 0);
  g->Transpose(6592, 4253, {1,0});
  g->Binary(ynn_binary_multiply, 4250, 4252, 4248);
  g->Dot(1289, 4253, YNN_INVALID_VALUE_ID, 4247, 1);
  g->DequantizeTensor(4247, YNN_INVALID_VALUE_ID, 4248, 4249);
  g->QuantizeTensor(4249, 6342, 4251, 1290);
  g->Dequantize(1290, 1291, 0.36220473051071167, 0);
  g->SplitDim(1291, 1292, 2, {8,256});
  g->Transpose(1292, 1293, {0,2,1,3});
  g->Unary(ynn_unary_square, 1293, 1294);
  g->Reduce(ynn_reduce_sum, 1294, 5729, {3}, true);
  g->ShapeProduct(1294, 5728, {3});
  g->Binary(ynn_binary_divide, 5729, 5728, 1295);
  g->Binary(ynn_binary_add, 1295, 6376, 1296);
  g->Binary(ynn_binary_pow, 1296, 6378, 1297);
  g->Binary(ynn_binary_multiply, 1293, 1297, 1299);
  g->Convert(6591, 1300);
  g->Binary(ynn_binary_multiply, 1299, 1300, 1301);
  g->Slice(1301, 1302, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1301, 1303, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1303, 1304);
  g->Concat({1304,1302}, 1305, 3);
  g->Binary(ynn_binary_multiply, 1301, 2133, 1306);
  g->Binary(ynn_binary_multiply, 1305, 2992, 1307);
  g->Binary(ynn_binary_add, 1306, 1307, 1308);
}

// Scope: "Layer18 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(1308, 762, 1310, false, true);
  g->Mask(1310, 6393, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6393, 5733, {-1}, true);
  g->Binary(ynn_binary_subtract, 6393, 5733, 5730);
  g->Unary(ynn_unary_exp, 5730, 5731);
  g->Reduce(ynn_reduce_sum, 5731, 5734, {-1}, true);
  g->Binary(ynn_binary_divide, 5404, 5734, 5732);
  g->Binary(ynn_binary_multiply, 5731, 5732, 1311);
  g->Matmul(1311, 764, 1312, false, false);
}

// Scope: "Layer18 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1312, 1313, {0,2,1,3});
  g->FuseDims(1313, 1314, 2, 2);
  g->Quantize(1314, 1315, 0.023006899282336235, 0);
  g->Transpose(6590, 4260, {1,0});
  g->Binary(ynn_binary_multiply, 4257, 4259, 4255);
  g->Dot(1315, 4260, YNN_INVALID_VALUE_ID, 4254, 1);
  g->DequantizeTensor(4254, YNN_INVALID_VALUE_ID, 4255, 4256);
  g->QuantizeTensor(4256, 6342, 4258, 1316);
  g->Dequantize(1316, 1317, 0.023901576176285744, 0);
}

// Scope: "Layer18 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1280, 1281);
  g->Reduce(ynn_reduce_sum, 1281, 5725, {2}, true);
  g->ShapeProduct(1281, 5724, {2});
  g->Binary(ynn_binary_divide, 5725, 5724, 1282);
  g->Binary(ynn_binary_add, 1282, 6376, 1283);
  g->Binary(ynn_binary_pow, 1283, 6378, 1284);
  g->Binary(ynn_binary_multiply, 1280, 1284, 1285);
  g->Convert(6579, 1286);
  g->Binary(ynn_binary_multiply, 1285, 1286, 1288);
  BuildLayer18AttentionQueryProjection(ctx);
  BuildLayer18AttentionSdpa(ctx);
  BuildLayer18AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1317, 1318);
  g->Reduce(ynn_reduce_sum, 1318, 5736, {2}, true);
  g->ShapeProduct(1318, 5735, {2});
  g->Binary(ynn_binary_divide, 5736, 5735, 1320);
  g->Binary(ynn_binary_add, 1320, 6376, 1321);
  g->Binary(ynn_binary_pow, 1321, 6378, 1322);
  g->Binary(ynn_binary_multiply, 1317, 1322, 1323);
  g->Convert(6586, 1324);
  g->Binary(ynn_binary_multiply, 1323, 1324, 1325);
  g->Binary(ynn_binary_add, 1280, 1325, 1326);
}

// Scope: "Layer18 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1326, 1327);
  g->Reduce(ynn_reduce_sum, 1327, 5738, {2}, true);
  g->ShapeProduct(1327, 5737, {2});
  g->Binary(ynn_binary_divide, 5738, 5737, 1328);
  g->Binary(ynn_binary_add, 1328, 6376, 1329);
  g->Binary(ynn_binary_pow, 1329, 6378, 1331);
  g->Binary(ynn_binary_multiply, 1326, 1331, 1332);
  g->Convert(6589, 1333);
  g->Binary(ynn_binary_multiply, 1332, 1333, 1334);
  g->Quantize(1334, 1335, 0.018082860857248306, 0);
  g->Transpose(6583, 4267, {1,0});
  g->Binary(ynn_binary_multiply, 4264, 4266, 4262);
  g->Dot(1335, 4267, YNN_INVALID_VALUE_ID, 4261, 1);
  g->DequantizeTensor(4261, YNN_INVALID_VALUE_ID, 4262, 4263);
  g->QuantizeTensor(4263, 6342, 4265, 1336);
  g->Dequantize(1336, 1337, 0.02362205646932125, 0);
  g->Transpose(6582, 4272, {1,0});
  g->Binary(ynn_binary_multiply, 4264, 4271, 4269);
  g->Dot(1335, 4272, YNN_INVALID_VALUE_ID, 4268, 1);
  g->DequantizeTensor(4268, YNN_INVALID_VALUE_ID, 4269, 4270);
  g->QuantizeTensor(4270, 6342, 4265, 1338);
  g->Dequantize(1338, 1339, 0.02362205646932125, 0);
  g->Polynomial(1339, 5741, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5741, 5742);
  g->Binary(ynn_binary_add, 5742, 5404, 5739);
  g->Binary(ynn_binary_multiply, 1339, 5402, 5740);
  g->Binary(ynn_binary_multiply, 5740, 5739, 1341);
  g->Binary(ynn_binary_multiply, 1337, 1341, 1342);
  g->Quantize(1342, 1343, 0.03297245129942894, 0);
  g->Transpose(6581, 4279, {1,0});
  g->Binary(ynn_binary_multiply, 4276, 4278, 4274);
  g->Dot(1343, 4279, YNN_INVALID_VALUE_ID, 4273, 1);
  g->DequantizeTensor(4273, YNN_INVALID_VALUE_ID, 4274, 4275);
  g->QuantizeTensor(4275, 6342, 4277, 1344);
  g->Dequantize(1344, 1345, 0.034845925867557526, 0);
  g->Unary(ynn_unary_square, 1345, 1346);
  g->Reduce(ynn_reduce_sum, 1346, 5744, {2}, true);
  g->ShapeProduct(1346, 5743, {2});
  g->Binary(ynn_binary_divide, 5744, 5743, 1347);
  g->Binary(ynn_binary_add, 1347, 6376, 1348);
  g->Binary(ynn_binary_pow, 1348, 6378, 1349);
  g->Binary(ynn_binary_multiply, 1345, 1349, 1350);
  g->Convert(6587, 1352);
  g->Binary(ynn_binary_multiply, 1350, 1352, 1353);
  g->Binary(ynn_binary_add, 1326, 1353, 1354);
}

// Scope: "Layer18 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1047, 1355, {0,0,18,0}, {-1,-1,1,-1});
  g->Reshape(1355, 1356, {1,1,256});
  g->Binary(ynn_binary_add, 1356, 6966, 1357);
  g->Binary(ynn_binary_multiply, 1357, 6374, 1358);
  g->Quantize(1354, 1359, 0.18026936054229736, 0);
  g->Transpose(6584, 4286, {1,0});
  g->Binary(ynn_binary_multiply, 4283, 4285, 4281);
  g->Dot(1359, 4286, YNN_INVALID_VALUE_ID, 4280, 1);
  g->DequantizeTensor(4280, YNN_INVALID_VALUE_ID, 4281, 4282);
  g->QuantizeTensor(4282, 6342, 4284, 1360);
  g->Dequantize(1360, 1361, 0.08562992513179779, 0);
  g->Polynomial(1361, 5747, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5747, 5748);
  g->Binary(ynn_binary_add, 5748, 5404, 5745);
  g->Binary(ynn_binary_multiply, 1361, 5402, 5746);
  g->Binary(ynn_binary_multiply, 5746, 5745, 1363);
  g->Binary(ynn_binary_multiply, 1363, 1358, 1364);
  g->Quantize(1364, 1365, 1.4409449100494385, 0);
  g->Transpose(6585, 4293, {1,0});
  g->Binary(ynn_binary_multiply, 4290, 4292, 4288);
  g->Dot(1365, 4293, YNN_INVALID_VALUE_ID, 4287, 1);
  g->DequantizeTensor(4287, YNN_INVALID_VALUE_ID, 4288, 4289);
  g->QuantizeTensor(4289, 6342, 4291, 1366);
  g->Dequantize(1366, 1367, 0.2601272463798523, 0);
  g->Unary(ynn_unary_square, 1367, 1368);
  g->Reduce(ynn_reduce_sum, 1368, 5750, {2}, true);
  g->ShapeProduct(1368, 5749, {2});
  g->Binary(ynn_binary_divide, 5750, 5749, 1369);
  g->Binary(ynn_binary_add, 1369, 6376, 1370);
  g->Binary(ynn_binary_pow, 1370, 6378, 1371);
  g->Binary(ynn_binary_multiply, 1367, 1371, 1372);
  g->Convert(6588, 1375);
  g->Binary(ynn_binary_multiply, 1372, 1375, 1376);
  g->Binary(ynn_binary_add, 1354, 1376, 1377);
  g->Convert(6580, 1378);
  g->Binary(ynn_binary_multiply, 1377, 1378, 1379);
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
  g->Quantize(1387, 1388, 0.3205932080745697, 0);
  g->Transpose(6606, 4300, {1,0});
  g->Binary(ynn_binary_multiply, 4297, 4299, 4295);
  g->Dot(1388, 4300, YNN_INVALID_VALUE_ID, 4294, 1);
  g->DequantizeTensor(4294, YNN_INVALID_VALUE_ID, 4295, 4296);
  g->QuantizeTensor(4296, 6342, 4298, 1389);
  g->Dequantize(1389, 1390, 0.4685039222240448, 0);
  g->SplitDim(1390, 1391, 2, {8,512});
  g->Transpose(1391, 1392, {0,2,1,3});
  g->Unary(ynn_unary_square, 1392, 1393);
  g->Reduce(ynn_reduce_sum, 1393, 5756, {3}, true);
  g->ShapeProduct(1393, 5755, {3});
  g->Binary(ynn_binary_divide, 5756, 5755, 1394);
  g->Binary(ynn_binary_add, 1394, 6376, 1395);
  g->Binary(ynn_binary_pow, 1395, 6378, 1397);
  g->Binary(ynn_binary_multiply, 1392, 1397, 1398);
  g->Convert(6605, 1399);
  g->Binary(ynn_binary_multiply, 1398, 1399, 1400);
  g->Slice(1400, 1401, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(1400, 1402, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 1402, 1403);
  g->Concat({1403,1401}, 1404, 3);
  g->Binary(ynn_binary_multiply, 1400, 3406, 1405);
  g->Binary(ynn_binary_multiply, 1404, 3508, 1406);
  g->Binary(ynn_binary_add, 1405, 1406, 1408);
}

// Scope: "Layer19 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(1408, 895, 1409, false, true);
  g->Mask(1409, 6394, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 6394, 5760, {-1}, true);
  g->Binary(ynn_binary_subtract, 6394, 5760, 5757);
  g->Unary(ynn_unary_exp, 5757, 5758);
  g->Reduce(ynn_reduce_sum, 5758, 5761, {-1}, true);
  g->Binary(ynn_binary_divide, 5404, 5761, 5759);
  g->Binary(ynn_binary_multiply, 5758, 5759, 1410);
  g->Matmul(1410, 897, 1411, false, false);
}

// Scope: "Layer19 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1411, 1412, {0,2,1,3});
  g->FuseDims(1412, 1413, 2, 2);
  g->Quantize(1413, 1414, 0.014886821620166302, 0);
  g->Transpose(6604, 4307, {1,0});
  g->Binary(ynn_binary_multiply, 4304, 4306, 4302);
  g->Dot(1414, 4307, YNN_INVALID_VALUE_ID, 4301, 1);
  g->DequantizeTensor(4301, YNN_INVALID_VALUE_ID, 4302, 4303);
  g->QuantizeTensor(4303, 6342, 4305, 1415);
  g->Dequantize(1415, 1416, 0.01861305721104145, 0);
}

// Scope: "Layer19 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1379, 1380);
  g->Reduce(ynn_reduce_sum, 1380, 5754, {2}, true);
  g->ShapeProduct(1380, 5753, {2});
  g->Binary(ynn_binary_divide, 5754, 5753, 1381);
  g->Binary(ynn_binary_add, 1381, 6376, 1382);
  g->Binary(ynn_binary_pow, 1382, 6378, 1383);
  g->Binary(ynn_binary_multiply, 1379, 1383, 1384);
  g->Convert(6593, 1386);
  g->Binary(ynn_binary_multiply, 1384, 1386, 1387);
  BuildLayer19AttentionQueryProjection(ctx);
  BuildLayer19AttentionSdpa(ctx);
  BuildLayer19AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1416, 1418);
  g->Reduce(ynn_reduce_sum, 1418, 5763, {2}, true);
  g->ShapeProduct(1418, 5762, {2});
  g->Binary(ynn_binary_divide, 5763, 5762, 1419);
  g->Binary(ynn_binary_add, 1419, 6376, 1420);
  g->Binary(ynn_binary_pow, 1420, 6378, 1421);
  g->Binary(ynn_binary_multiply, 1416, 1421, 1422);
  g->Convert(6600, 1423);
  g->Binary(ynn_binary_multiply, 1422, 1423, 1424);
  g->Binary(ynn_binary_add, 1379, 1424, 1425);
}

// Scope: "Layer19 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1425, 1426);
  g->Reduce(ynn_reduce_sum, 1426, 5765, {2}, true);
  g->ShapeProduct(1426, 5764, {2});
  g->Binary(ynn_binary_divide, 5765, 5764, 1427);
  g->Binary(ynn_binary_add, 1427, 6376, 1429);
  g->Binary(ynn_binary_pow, 1429, 6378, 1430);
  g->Binary(ynn_binary_multiply, 1425, 1430, 1431);
  g->Convert(6603, 1432);
  g->Binary(ynn_binary_multiply, 1431, 1432, 1433);
  g->Quantize(1433, 1434, 0.019887126982212067, 0);
  g->Transpose(6597, 4314, {1,0});
  g->Binary(ynn_binary_multiply, 4311, 4313, 4309);
  g->Dot(1434, 4314, YNN_INVALID_VALUE_ID, 4308, 1);
  g->DequantizeTensor(4308, YNN_INVALID_VALUE_ID, 4309, 4310);
  g->QuantizeTensor(4310, 6342, 4312, 1435);
  g->Dequantize(1435, 1436, 0.022637804970145226, 0);
  g->Transpose(6596, 4319, {1,0});
  g->Binary(ynn_binary_multiply, 4311, 4318, 4316);
  g->Dot(1434, 4319, YNN_INVALID_VALUE_ID, 4315, 1);
  g->DequantizeTensor(4315, YNN_INVALID_VALUE_ID, 4316, 4317);
  g->QuantizeTensor(4317, 6342, 4312, 1437);
  g->Dequantize(1437, 1439, 0.022637804970145226, 0);
  g->Polynomial(1439, 5768, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5768, 5769);
  g->Binary(ynn_binary_add, 5769, 5404, 5766);
  g->Binary(ynn_binary_multiply, 1439, 5402, 5767);
  g->Binary(ynn_binary_multiply, 5767, 5766, 1440);
  g->Binary(ynn_binary_multiply, 1436, 1440, 1441);
  g->Quantize(1441, 1442, 0.019808080047369003, 0);
  g->Transpose(6595, 4326, {1,0});
  g->Binary(ynn_binary_multiply, 4323, 4325, 4321);
  g->Dot(1442, 4326, YNN_INVALID_VALUE_ID, 4320, 1);
  g->DequantizeTensor(4320, YNN_INVALID_VALUE_ID, 4321, 4322);
  g->QuantizeTensor(4322, 6342, 4324, 1443);
  g->Dequantize(1443, 1444, 0.014754860661923885, 0);
  g->Unary(ynn_unary_square, 1444, 1445);
  g->Reduce(ynn_reduce_sum, 1445, 5771, {2}, true);
  g->ShapeProduct(1445, 5770, {2});
  g->Binary(ynn_binary_divide, 5771, 5770, 1446);
  g->Binary(ynn_binary_add, 1446, 6376, 1447);
  g->Binary(ynn_binary_pow, 1447, 6378, 1448);
  g->Binary(ynn_binary_multiply, 1444, 1448, 1450);
  g->Convert(6601, 1451);
  g->Binary(ynn_binary_multiply, 1450, 1451, 1452);
  g->Binary(ynn_binary_add, 1425, 1452, 1453);
}

// Scope: "Layer19 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1047, 1454, {0,0,19,0}, {-1,-1,1,-1});
  g->Reshape(1454, 1455, {1,1,256});
  g->Binary(ynn_binary_add, 1455, 6967, 1456);
  g->Binary(ynn_binary_multiply, 1456, 6374, 1457);
  g->Quantize(1453, 1458, 0.18873928487300873, 0);
  g->Transpose(6598, 4339, {1,0});
  g->Binary(ynn_binary_multiply, 4337, 4338, 4335);
  g->Dot(1458, 4339, YNN_INVALID_VALUE_ID, 4334, 1);
  g->DequantizeTensor(4334, YNN_INVALID_VALUE_ID, 4335, 4336);
  g->QuantizeTensor(4336, 6342, 3914, 1459);
  g->Dequantize(1459, 1461, 0.08070866763591766, 0);
  g->Polynomial(1461, 5774, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5774, 5775);
  g->Binary(ynn_binary_add, 5775, 5404, 5772);
  g->Binary(ynn_binary_multiply, 1461, 5402, 5773);
  g->Binary(ynn_binary_multiply, 5773, 5772, 1462);
  g->Binary(ynn_binary_multiply, 1462, 1457, 1463);
  g->Quantize(1463, 1464, 0.3858267664909363, 0);
  g->Transpose(6599, 4346, {1,0});
  g->Binary(ynn_binary_multiply, 4343, 4345, 4341);
  g->Dot(1464, 4346, YNN_INVALID_VALUE_ID, 4340, 1);
  g->DequantizeTensor(4340, YNN_INVALID_VALUE_ID, 4341, 4342);
  g->QuantizeTensor(4342, 6342, 4344, 1465);
  g->Dequantize(1465, 1466, 0.16572551429271698, 0);
  g->Unary(ynn_unary_square, 1466, 1467);
  g->Reduce(ynn_reduce_sum, 1467, 5777, {2}, true);
  g->ShapeProduct(1467, 5776, {2});
  g->Binary(ynn_binary_divide, 5777, 5776, 1468);
  g->Binary(ynn_binary_add, 1468, 6376, 1469);
  g->Binary(ynn_binary_pow, 1469, 6378, 1470);
  g->Binary(ynn_binary_multiply, 1466, 1470, 1471);
  g->Convert(6602, 1472);
  g->Binary(ynn_binary_multiply, 1471, 1472, 1473);
  g->Binary(ynn_binary_add, 1453, 1473, 1474);
  g->Convert(6594, 1475);
  g->Binary(ynn_binary_multiply, 1474, 1475, 1476);
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
  g->Quantize(1485, 1486, 0.3106735646724701, 0);
  g->Transpose(6637, 4358, {1,0});
  g->Binary(ynn_binary_multiply, 4355, 4357, 4353);
  g->Dot(1486, 4358, YNN_INVALID_VALUE_ID, 4352, 1);
  g->DequantizeTensor(4352, YNN_INVALID_VALUE_ID, 4353, 4354);
  g->QuantizeTensor(4354, 6342, 4356, 1487);
  g->Dequantize(1487, 1488, 0.36614173650741577, 0);
  g->SplitDim(1488, 1489, 2, {8,256});
  g->Transpose(1489, 1490, {0,2,1,3});
  g->Unary(ynn_unary_square, 1490, 1491);
  g->Reduce(ynn_reduce_sum, 1491, 5781, {3}, true);
  g->ShapeProduct(1491, 5780, {3});
  g->Binary(ynn_binary_divide, 5781, 5780, 1492);
  g->Binary(ynn_binary_add, 1492, 6376, 1494);
  g->Binary(ynn_binary_pow, 1494, 6378, 1495);
  g->Binary(ynn_binary_multiply, 1490, 1495, 1496);
  g->Convert(6636, 1497);
  g->Binary(ynn_binary_multiply, 1496, 1497, 1498);
  g->Slice(1498, 1499, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1498, 1500, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1500, 1501);
  g->Concat({1501,1499}, 1502, 3);
  g->Binary(ynn_binary_multiply, 1498, 2133, 1503);
  g->Binary(ynn_binary_multiply, 1502, 2992, 1505);
  g->Binary(ynn_binary_add, 1503, 1505, 1506);
}

// Scope: "Layer20 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(1506, 762, 1507, false, true);
  g->Mask(1507, 6396, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6396, 5789, {-1}, true);
  g->Binary(ynn_binary_subtract, 6396, 5789, 5786);
  g->Unary(ynn_unary_exp, 5786, 5787);
  g->Reduce(ynn_reduce_sum, 5787, 5790, {-1}, true);
  g->Binary(ynn_binary_divide, 5404, 5790, 5788);
  g->Binary(ynn_binary_multiply, 5787, 5788, 1508);
  g->Matmul(1508, 764, 1509, false, false);
}

// Scope: "Layer20 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1509, 1510, {0,2,1,3});
  g->FuseDims(1510, 1511, 2, 2);
  g->Quantize(1511, 1512, 0.02436024509370327, 0);
  g->Transpose(6635, 4364, {1,0});
  g->Binary(ynn_binary_multiply, 4109, 4363, 4360);
  g->Dot(1512, 4364, YNN_INVALID_VALUE_ID, 4359, 1);
  g->DequantizeTensor(4359, YNN_INVALID_VALUE_ID, 4360, 4361);
  g->QuantizeTensor(4361, 6342, 4362, 1513);
  g->Dequantize(1513, 1515, 0.035965267568826675, 0);
}

// Scope: "Layer20 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1476, 1477);
  g->Reduce(ynn_reduce_sum, 1477, 5779, {2}, true);
  g->ShapeProduct(1477, 5778, {2});
  g->Binary(ynn_binary_divide, 5779, 5778, 1478);
  g->Binary(ynn_binary_add, 1478, 6376, 1479);
  g->Binary(ynn_binary_pow, 1479, 6378, 1480);
  g->Binary(ynn_binary_multiply, 1476, 1480, 1483);
  g->Convert(6624, 1484);
  g->Binary(ynn_binary_multiply, 1483, 1484, 1485);
  BuildLayer20AttentionQueryProjection(ctx);
  BuildLayer20AttentionSdpa(ctx);
  BuildLayer20AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1515, 1516);
  g->Reduce(ynn_reduce_sum, 1516, 5792, {2}, true);
  g->ShapeProduct(1516, 5791, {2});
  g->Binary(ynn_binary_divide, 5792, 5791, 1517);
  g->Binary(ynn_binary_add, 1517, 6376, 1518);
  g->Binary(ynn_binary_pow, 1518, 6378, 1519);
  g->Binary(ynn_binary_multiply, 1515, 1519, 1520);
  g->Convert(6631, 1521);
  g->Binary(ynn_binary_multiply, 1520, 1521, 1522);
  g->Binary(ynn_binary_add, 1476, 1522, 1523);
}

// Scope: "Layer20 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1523, 1524);
  g->Reduce(ynn_reduce_sum, 1524, 5794, {2}, true);
  g->ShapeProduct(1524, 5793, {2});
  g->Binary(ynn_binary_divide, 5794, 5793, 1526);
  g->Binary(ynn_binary_add, 1526, 6376, 1527);
  g->Binary(ynn_binary_pow, 1527, 6378, 1528);
  g->Binary(ynn_binary_multiply, 1523, 1528, 1529);
  g->Convert(6634, 1530);
  g->Binary(ynn_binary_multiply, 1529, 1530, 1531);
  g->Quantize(1531, 1532, 0.021377958357334137, 0);
  g->Transpose(6628, 4371, {1,0});
  g->Binary(ynn_binary_multiply, 4368, 4370, 4366);
  g->Dot(1532, 4371, YNN_INVALID_VALUE_ID, 4365, 1);
  g->DequantizeTensor(4365, YNN_INVALID_VALUE_ID, 4366, 4367);
  g->QuantizeTensor(4367, 6342, 4369, 1533);
  g->Dequantize(1533, 1534, 0.02276083640754223, 0);
  g->Transpose(6627, 4383, {1,0});
  g->Binary(ynn_binary_multiply, 4368, 4382, 4380);
  g->Dot(1532, 4383, YNN_INVALID_VALUE_ID, 4379, 1);
  g->DequantizeTensor(4379, YNN_INVALID_VALUE_ID, 4380, 4381);
  g->QuantizeTensor(4381, 6342, 4369, 1536);
  g->Dequantize(1536, 1537, 0.02276083640754223, 0);
  g->Polynomial(1537, 5797, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5797, 5798);
  g->Binary(ynn_binary_add, 5798, 5404, 5795);
  g->Binary(ynn_binary_multiply, 1537, 5402, 5796);
  g->Binary(ynn_binary_multiply, 5796, 5795, 1538);
  g->Binary(ynn_binary_multiply, 1534, 1538, 1539);
  g->Quantize(1539, 1540, 0.026574812829494476, 0);
  g->Transpose(6626, 4390, {1,0});
  g->Binary(ynn_binary_multiply, 4387, 4389, 4385);
  g->Dot(1540, 4390, YNN_INVALID_VALUE_ID, 4384, 1);
  g->DequantizeTensor(4384, YNN_INVALID_VALUE_ID, 4385, 4386);
  g->QuantizeTensor(4386, 6342, 4388, 1541);
  g->Dequantize(1541, 1542, 0.028310857713222504, 0);
  g->Unary(ynn_unary_square, 1542, 1543);
  g->Reduce(ynn_reduce_sum, 1543, 5800, {2}, true);
  g->ShapeProduct(1543, 5799, {2});
  g->Binary(ynn_binary_divide, 5800, 5799, 1544);
  g->Binary(ynn_binary_add, 1544, 6376, 1545);
  g->Binary(ynn_binary_pow, 1545, 6378, 1547);
  g->Binary(ynn_binary_multiply, 1542, 1547, 1548);
  g->Convert(6632, 1549);
  g->Binary(ynn_binary_multiply, 1548, 1549, 1550);
  g->Binary(ynn_binary_add, 1523, 1550, 1551);
}

// Scope: "Layer20 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1047, 1552, {0,0,20,0}, {-1,-1,1,-1});
  g->Reshape(1552, 1553, {1,1,256});
  g->Binary(ynn_binary_add, 1553, 6969, 1554);
  g->Binary(ynn_binary_multiply, 1554, 6374, 1555);
  g->Quantize(1551, 1556, 0.17634929716587067, 0);
  g->Transpose(6629, 4397, {1,0});
  g->Binary(ynn_binary_multiply, 4394, 4396, 4392);
  g->Dot(1556, 4397, YNN_INVALID_VALUE_ID, 4391, 1);
  g->DequantizeTensor(4391, YNN_INVALID_VALUE_ID, 4392, 4393);
  g->QuantizeTensor(4393, 6342, 4395, 1558);
  g->Dequantize(1558, 1559, 0.059055130928754807, 0);
  g->Polynomial(1559, 5803, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5803, 5804);
  g->Binary(ynn_binary_add, 5804, 5404, 5801);
  g->Binary(ynn_binary_multiply, 1559, 5402, 5802);
  g->Binary(ynn_binary_multiply, 5802, 5801, 1560);
  g->Binary(ynn_binary_multiply, 1560, 1555, 1561);
  g->Quantize(1561, 1562, 0.1998031586408615, 0);
  g->Transpose(6630, 4404, {1,0});
  g->Binary(ynn_binary_multiply, 4401, 4403, 4399);
  g->Dot(1562, 4404, YNN_INVALID_VALUE_ID, 4398, 1);
  g->DequantizeTensor(4398, YNN_INVALID_VALUE_ID, 4399, 4400);
  g->QuantizeTensor(4400, 6342, 4402, 1563);
  g->Dequantize(1563, 1564, 0.07776007056236267, 0);
  g->Unary(ynn_unary_square, 1564, 1565);
  g->Reduce(ynn_reduce_sum, 1565, 5806, {2}, true);
  g->ShapeProduct(1565, 5805, {2});
  g->Binary(ynn_binary_divide, 5806, 5805, 1566);
  g->Binary(ynn_binary_add, 1566, 6376, 1567);
  g->Binary(ynn_binary_pow, 1567, 6378, 1569);
  g->Binary(ynn_binary_multiply, 1564, 1569, 1570);
  g->Convert(6633, 1571);
  g->Binary(ynn_binary_multiply, 1570, 1571, 1572);
  g->Binary(ynn_binary_add, 1551, 1572, 1573);
  g->Convert(6625, 1574);
  g->Binary(ynn_binary_multiply, 1573, 1574, 1575);
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
  g->Quantize(1583, 1584, 0.20073647797107697, 0);
  g->Transpose(6651, 4411, {1,0});
  g->Binary(ynn_binary_multiply, 4408, 4410, 4406);
  g->Dot(1584, 4411, YNN_INVALID_VALUE_ID, 4405, 1);
  g->DequantizeTensor(4405, YNN_INVALID_VALUE_ID, 4406, 4407);
  g->QuantizeTensor(4407, 6342, 4409, 1585);
  g->Dequantize(1585, 1586, 0.23622049391269684, 0);
  g->SplitDim(1586, 1587, 2, {8,256});
  g->Transpose(1587, 1588, {0,2,1,3});
  g->Unary(ynn_unary_square, 1588, 1589);
  g->Reduce(ynn_reduce_sum, 1589, 5812, {3}, true);
  g->ShapeProduct(1589, 5811, {3});
  g->Binary(ynn_binary_divide, 5812, 5811, 1592);
  g->Binary(ynn_binary_add, 1592, 6376, 1593);
  g->Binary(ynn_binary_pow, 1593, 6378, 1594);
  g->Binary(ynn_binary_multiply, 1588, 1594, 1595);
  g->Convert(6650, 1596);
  g->Binary(ynn_binary_multiply, 1595, 1596, 1597);
  g->Slice(1597, 1598, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1597, 1599, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1599, 1600);
  g->Concat({1600,1598}, 1601, 3);
  g->Binary(ynn_binary_multiply, 1597, 2133, 1603);
  g->Binary(ynn_binary_multiply, 1601, 2992, 1604);
  g->Binary(ynn_binary_add, 1603, 1604, 1605);
}

// Scope: "Layer21 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(1605, 762, 1606, false, true);
  g->Mask(1606, 6397, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6397, 5816, {-1}, true);
  g->Binary(ynn_binary_subtract, 6397, 5816, 5813);
  g->Unary(ynn_unary_exp, 5813, 5814);
  g->Reduce(ynn_reduce_sum, 5814, 5817, {-1}, true);
  g->Binary(ynn_binary_divide, 5404, 5817, 5815);
  g->Binary(ynn_binary_multiply, 5814, 5815, 1607);
  g->Matmul(1607, 764, 1608, false, false);
}

// Scope: "Layer21 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1608, 1609, {0,2,1,3});
  g->FuseDims(1609, 1610, 2, 2);
  g->Quantize(1610, 1611, 0.025221465155482292, 0);
  g->Transpose(6649, 4418, {1,0});
  g->Binary(ynn_binary_multiply, 4415, 4417, 4413);
  g->Dot(1611, 4418, YNN_INVALID_VALUE_ID, 4412, 1);
  g->DequantizeTensor(4412, YNN_INVALID_VALUE_ID, 4413, 4414);
  g->QuantizeTensor(4414, 6342, 4416, 1613);
  g->Dequantize(1613, 1614, 0.03553423285484314, 0);
}

// Scope: "Layer21 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1575, 1576);
  g->Reduce(ynn_reduce_sum, 1576, 5810, {2}, true);
  g->ShapeProduct(1576, 5809, {2});
  g->Binary(ynn_binary_divide, 5810, 5809, 1577);
  g->Binary(ynn_binary_add, 1577, 6376, 1578);
  g->Binary(ynn_binary_pow, 1578, 6378, 1580);
  g->Binary(ynn_binary_multiply, 1575, 1580, 1581);
  g->Convert(6638, 1582);
  g->Binary(ynn_binary_multiply, 1581, 1582, 1583);
  BuildLayer21AttentionQueryProjection(ctx);
  BuildLayer21AttentionSdpa(ctx);
  BuildLayer21AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1614, 1615);
  g->Reduce(ynn_reduce_sum, 1615, 5819, {2}, true);
  g->ShapeProduct(1615, 5818, {2});
  g->Binary(ynn_binary_divide, 5819, 5818, 1616);
  g->Binary(ynn_binary_add, 1616, 6376, 1617);
  g->Binary(ynn_binary_pow, 1617, 6378, 1618);
  g->Binary(ynn_binary_multiply, 1614, 1618, 1619);
  g->Convert(6645, 1620);
  g->Binary(ynn_binary_multiply, 1619, 1620, 1621);
  g->Binary(ynn_binary_add, 1575, 1621, 1622);
}

// Scope: "Layer21 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1622, 1624);
  g->Reduce(ynn_reduce_sum, 1624, 5821, {2}, true);
  g->ShapeProduct(1624, 5820, {2});
  g->Binary(ynn_binary_divide, 5821, 5820, 1625);
  g->Binary(ynn_binary_add, 1625, 6376, 1626);
  g->Binary(ynn_binary_pow, 1626, 6378, 1627);
  g->Binary(ynn_binary_multiply, 1622, 1627, 1628);
  g->Convert(6648, 1629);
  g->Binary(ynn_binary_multiply, 1628, 1629, 1630);
  g->Quantize(1630, 1631, 0.019064493477344513, 0);
  g->Transpose(6642, 4424, {1,0});
  g->Binary(ynn_binary_multiply, 4422, 4423, 4420);
  g->Dot(1631, 4424, YNN_INVALID_VALUE_ID, 4419, 1);
  g->DequantizeTensor(4419, YNN_INVALID_VALUE_ID, 4420, 4421);
  g->QuantizeTensor(4421, 6342, 4265, 1632);
  g->Dequantize(1632, 1633, 0.02362205646932125, 0);
  g->Transpose(6641, 4429, {1,0});
  g->Binary(ynn_binary_multiply, 4422, 4428, 4426);
  g->Dot(1631, 4429, YNN_INVALID_VALUE_ID, 4425, 1);
  g->DequantizeTensor(4425, YNN_INVALID_VALUE_ID, 4426, 4427);
  g->QuantizeTensor(4427, 6342, 4265, 1635);
  g->Dequantize(1635, 1636, 0.02362205646932125, 0);
  g->Polynomial(1636, 5824, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5824, 5825);
  g->Binary(ynn_binary_add, 5825, 5404, 5822);
  g->Binary(ynn_binary_multiply, 1636, 5402, 5823);
  g->Binary(ynn_binary_multiply, 5823, 5822, 1637);
  g->Binary(ynn_binary_multiply, 1633, 1637, 1638);
  g->Quantize(1638, 1639, 0.030019694939255714, 0);
  g->Transpose(6640, 4436, {1,0});
  g->Binary(ynn_binary_multiply, 4433, 4435, 4431);
  g->Dot(1639, 4436, YNN_INVALID_VALUE_ID, 4430, 1);
  g->DequantizeTensor(4430, YNN_INVALID_VALUE_ID, 4431, 4432);
  g->QuantizeTensor(4432, 6342, 4434, 1640);
  g->Dequantize(1640, 1641, 0.03767223656177521, 0);
  g->Unary(ynn_unary_square, 1641, 1642);
  g->Reduce(ynn_reduce_sum, 1642, 5827, {2}, true);
  g->ShapeProduct(1642, 5826, {2});
  g->Binary(ynn_binary_divide, 5827, 5826, 1643);
  g->Binary(ynn_binary_add, 1643, 6376, 1645);
  g->Binary(ynn_binary_pow, 1645, 6378, 1646);
  g->Binary(ynn_binary_multiply, 1641, 1646, 1647);
  g->Convert(6646, 1648);
  g->Binary(ynn_binary_multiply, 1647, 1648, 1649);
  g->Binary(ynn_binary_add, 1622, 1649, 1650);
}

// Scope: "Layer21 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1047, 1651, {0,0,21,0}, {-1,-1,1,-1});
  g->Reshape(1651, 1652, {1,1,256});
  g->Binary(ynn_binary_add, 1652, 6970, 1653);
  g->Binary(ynn_binary_multiply, 1653, 6374, 1654);
  g->Quantize(1650, 1656, 0.14814288914203644, 0);
  g->Transpose(6643, 4443, {1,0});
  g->Binary(ynn_binary_multiply, 4440, 4442, 4438);
  g->Dot(1656, 4443, YNN_INVALID_VALUE_ID, 4437, 1);
  g->DequantizeTensor(4437, YNN_INVALID_VALUE_ID, 4438, 4439);
  g->QuantizeTensor(4439, 6342, 4441, 1657);
  g->Dequantize(1657, 1658, 0.047244105488061905, 0);
  g->Polynomial(1658, 5830, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5830, 5831);
  g->Binary(ynn_binary_add, 5831, 5404, 5828);
  g->Binary(ynn_binary_multiply, 1658, 5402, 5829);
  g->Binary(ynn_binary_multiply, 5829, 5828, 1659);
  g->Binary(ynn_binary_multiply, 1659, 1654, 1660);
  g->Quantize(1660, 1661, 0.10531497001647949, 0);
  g->Transpose(6644, 4450, {1,0});
  g->Binary(ynn_binary_multiply, 4447, 4449, 4445);
  g->Dot(1661, 4450, YNN_INVALID_VALUE_ID, 4444, 1);
  g->DequantizeTensor(4444, YNN_INVALID_VALUE_ID, 4445, 4446);
  g->QuantizeTensor(4446, 6342, 4448, 1662);
  g->Dequantize(1662, 1663, 0.061565153300762177, 0);
  g->Unary(ynn_unary_square, 1663, 1664);
  g->Reduce(ynn_reduce_sum, 1664, 5833, {2}, true);
  g->ShapeProduct(1664, 5832, {2});
  g->Binary(ynn_binary_divide, 5833, 5832, 1665);
  g->Binary(ynn_binary_add, 1665, 6376, 1667);
  g->Binary(ynn_binary_pow, 1667, 6378, 1668);
  g->Binary(ynn_binary_multiply, 1663, 1668, 1669);
  g->Convert(6647, 1670);
  g->Binary(ynn_binary_multiply, 1669, 1670, 1671);
  g->Binary(ynn_binary_add, 1650, 1671, 1672);
  g->Convert(6639, 1673);
  g->Binary(ynn_binary_multiply, 1672, 1673, 1674);
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
  g->Quantize(1682, 1683, 0.21987482905387878, 0);
  g->Transpose(6665, 4457, {1,0});
  g->Binary(ynn_binary_multiply, 4454, 4456, 4452);
  g->Dot(1683, 4457, YNN_INVALID_VALUE_ID, 4451, 1);
  g->DequantizeTensor(4451, YNN_INVALID_VALUE_ID, 4452, 4453);
  g->QuantizeTensor(4453, 6342, 4455, 1684);
  g->Dequantize(1684, 1685, 0.19685040414333344, 0);
  g->SplitDim(1685, 1686, 2, {8,256});
  g->Transpose(1686, 1687, {0,2,1,3});
  g->Unary(ynn_unary_square, 1687, 1689);
  g->Reduce(ynn_reduce_sum, 1689, 5837, {3}, true);
  g->ShapeProduct(1689, 5836, {3});
  g->Binary(ynn_binary_divide, 5837, 5836, 1690);
  g->Binary(ynn_binary_add, 1690, 6376, 1691);
  g->Binary(ynn_binary_pow, 1691, 6378, 1692);
  g->Binary(ynn_binary_multiply, 1687, 1692, 1693);
  g->Convert(6664, 1694);
  g->Binary(ynn_binary_multiply, 1693, 1694, 1695);
  g->Slice(1695, 1696, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1695, 1697, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1697, 1698);
  g->Concat({1698,1696}, 1701, 3);
  g->Binary(ynn_binary_multiply, 1695, 2133, 1702);
  g->Binary(ynn_binary_multiply, 1701, 2992, 1703);
  g->Binary(ynn_binary_add, 1702, 1703, 1704);
}

// Scope: "Layer22 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(1704, 762, 1705, false, true);
  g->Mask(1705, 6398, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6398, 5841, {-1}, true);
  g->Binary(ynn_binary_subtract, 6398, 5841, 5838);
  g->Unary(ynn_unary_exp, 5838, 5839);
  g->Reduce(ynn_reduce_sum, 5839, 5842, {-1}, true);
  g->Binary(ynn_binary_divide, 5404, 5842, 5840);
  g->Binary(ynn_binary_multiply, 5839, 5840, 1706);
  g->Matmul(1706, 764, 1707, false, false);
}

// Scope: "Layer22 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1707, 1708, {0,2,1,3});
  g->FuseDims(1708, 1709, 2, 2);
  g->Quantize(1709, 1711, 0.023868119344115257, 0);
  g->Transpose(6663, 4471, {1,0});
  g->Binary(ynn_binary_multiply, 4468, 4470, 4466);
  g->Dot(1711, 4471, YNN_INVALID_VALUE_ID, 4465, 1);
  g->DequantizeTensor(4465, YNN_INVALID_VALUE_ID, 4466, 4467);
  g->QuantizeTensor(4467, 6342, 4469, 1712);
  g->Dequantize(1712, 1713, 0.047558318823575974, 0);
}

// Scope: "Layer22 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1674, 1675);
  g->Reduce(ynn_reduce_sum, 1675, 5835, {2}, true);
  g->ShapeProduct(1675, 5834, {2});
  g->Binary(ynn_binary_divide, 5835, 5834, 1676);
  g->Binary(ynn_binary_add, 1676, 6376, 1678);
  g->Binary(ynn_binary_pow, 1678, 6378, 1679);
  g->Binary(ynn_binary_multiply, 1674, 1679, 1680);
  g->Convert(6652, 1681);
  g->Binary(ynn_binary_multiply, 1680, 1681, 1682);
  BuildLayer22AttentionQueryProjection(ctx);
  BuildLayer22AttentionSdpa(ctx);
  BuildLayer22AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1713, 1714);
  g->Reduce(ynn_reduce_sum, 1714, 5844, {2}, true);
  g->ShapeProduct(1714, 5843, {2});
  g->Binary(ynn_binary_divide, 5844, 5843, 1715);
  g->Binary(ynn_binary_add, 1715, 6376, 1716);
  g->Binary(ynn_binary_pow, 1716, 6378, 1717);
  g->Binary(ynn_binary_multiply, 1713, 1717, 1718);
  g->Convert(6659, 1719);
  g->Binary(ynn_binary_multiply, 1718, 1719, 1720);
  g->Binary(ynn_binary_add, 1674, 1720, 1722);
}

// Scope: "Layer22 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1722, 1723);
  g->Reduce(ynn_reduce_sum, 1723, 5850, {2}, true);
  g->ShapeProduct(1723, 5849, {2});
  g->Binary(ynn_binary_divide, 5850, 5849, 1724);
  g->Binary(ynn_binary_add, 1724, 6376, 1725);
  g->Binary(ynn_binary_pow, 1725, 6378, 1726);
  g->Binary(ynn_binary_multiply, 1722, 1726, 1727);
  g->Convert(6662, 1728);
  g->Binary(ynn_binary_multiply, 1727, 1728, 1729);
  g->Quantize(1729, 1730, 0.019696271046996117, 0);
  g->Transpose(6656, 4478, {1,0});
  g->Binary(ynn_binary_multiply, 4475, 4477, 4473);
  g->Dot(1730, 4478, YNN_INVALID_VALUE_ID, 4472, 1);
  g->DequantizeTensor(4472, YNN_INVALID_VALUE_ID, 4473, 4474);
  g->QuantizeTensor(4474, 6342, 4476, 1731);
  g->Dequantize(1731, 1733, 0.024114182218909264, 0);
  g->Transpose(6655, 4483, {1,0});
  g->Binary(ynn_binary_multiply, 4475, 4482, 4480);
  g->Dot(1730, 4483, YNN_INVALID_VALUE_ID, 4479, 1);
  g->DequantizeTensor(4479, YNN_INVALID_VALUE_ID, 4480, 4481);
  g->QuantizeTensor(4481, 6342, 4476, 1734);
  g->Dequantize(1734, 1735, 0.024114182218909264, 0);
  g->Polynomial(1735, 5853, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5853, 5854);
  g->Binary(ynn_binary_add, 5854, 5404, 5851);
  g->Binary(ynn_binary_multiply, 1735, 5402, 5852);
  g->Binary(ynn_binary_multiply, 5852, 5851, 1736);
  g->Binary(ynn_binary_multiply, 1733, 1736, 1737);
  g->Quantize(1737, 1738, 0.03567914664745331, 0);
  g->Transpose(6654, 4490, {1,0});
  g->Binary(ynn_binary_multiply, 4487, 4489, 4485);
  g->Dot(1738, 4490, YNN_INVALID_VALUE_ID, 4484, 1);
  g->DequantizeTensor(4484, YNN_INVALID_VALUE_ID, 4485, 4486);
  g->QuantizeTensor(4486, 6342, 4488, 1739);
  g->Dequantize(1739, 1740, 0.05007796362042427, 0);
  g->Unary(ynn_unary_square, 1740, 1741);
  g->Reduce(ynn_reduce_sum, 1741, 5856, {2}, true);
  g->ShapeProduct(1741, 5855, {2});
  g->Binary(ynn_binary_divide, 5856, 5855, 1743);
  g->Binary(ynn_binary_add, 1743, 6376, 1744);
  g->Binary(ynn_binary_pow, 1744, 6378, 1745);
  g->Binary(ynn_binary_multiply, 1740, 1745, 1746);
  g->Convert(6660, 1747);
  g->Binary(ynn_binary_multiply, 1746, 1747, 1748);
  g->Binary(ynn_binary_add, 1722, 1748, 1749);
}

// Scope: "Layer22 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1047, 1750, {0,0,22,0}, {-1,-1,1,-1});
  g->Reshape(1750, 1751, {1,1,256});
  g->Binary(ynn_binary_add, 1751, 6971, 1752);
  g->Binary(ynn_binary_multiply, 1752, 6374, 1754);
  g->Quantize(1749, 1755, 0.15015320479869843, 0);
  g->Transpose(6657, 4504, {1,0});
  g->Binary(ynn_binary_multiply, 4501, 4503, 4499);
  g->Dot(1755, 4504, YNN_INVALID_VALUE_ID, 4498, 1);
  g->DequantizeTensor(4498, YNN_INVALID_VALUE_ID, 4499, 4500);
  g->QuantizeTensor(4500, 6342, 4502, 1756);
  g->Dequantize(1756, 1757, 0.06102363392710686, 0);
  g->Polynomial(1757, 5859, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5859, 5860);
  g->Binary(ynn_binary_add, 5860, 5404, 5857);
  g->Binary(ynn_binary_multiply, 1757, 5402, 5858);
  g->Binary(ynn_binary_multiply, 5858, 5857, 1758);
  g->Binary(ynn_binary_multiply, 1758, 1754, 1759);
  g->Quantize(1759, 1760, 0.3779527544975281, 0);
  g->Transpose(6658, 4511, {1,0});
  g->Binary(ynn_binary_multiply, 4508, 4510, 4506);
  g->Dot(1760, 4511, YNN_INVALID_VALUE_ID, 4505, 1);
  g->DequantizeTensor(4505, YNN_INVALID_VALUE_ID, 4506, 4507);
  g->QuantizeTensor(4507, 6342, 4509, 1761);
  g->Dequantize(1761, 1762, 0.11902644485235214, 0);
  g->Unary(ynn_unary_square, 1762, 1763);
  g->Reduce(ynn_reduce_sum, 1763, 5862, {2}, true);
  g->ShapeProduct(1763, 5861, {2});
  g->Binary(ynn_binary_divide, 5862, 5861, 1765);
  g->Binary(ynn_binary_add, 1765, 6376, 1766);
  g->Binary(ynn_binary_pow, 1766, 6378, 1767);
  g->Binary(ynn_binary_multiply, 1762, 1767, 1768);
  g->Convert(6661, 1769);
  g->Binary(ynn_binary_multiply, 1768, 1769, 1770);
  g->Binary(ynn_binary_add, 1749, 1770, 1771);
  g->Convert(6653, 1772);
  g->Binary(ynn_binary_multiply, 1771, 1772, 1773);
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
  g->Quantize(1781, 1782, 0.17847737669944763, 0);
  g->Transpose(6679, 4518, {1,0});
  g->Binary(ynn_binary_multiply, 4515, 4517, 4513);
  g->Dot(1782, 4518, YNN_INVALID_VALUE_ID, 4512, 1);
  g->DequantizeTensor(4512, YNN_INVALID_VALUE_ID, 4513, 4514);
  g->QuantizeTensor(4514, 6342, 4516, 1783);
  g->Dequantize(1783, 1784, 0.16338583827018738, 0);
  g->SplitDim(1784, 1785, 2, {8,256});
  g->Transpose(1785, 1787, {0,2,1,3});
  g->Unary(ynn_unary_square, 1787, 1788);
  g->Reduce(ynn_reduce_sum, 1788, 5868, {3}, true);
  g->ShapeProduct(1788, 5867, {3});
  g->Binary(ynn_binary_divide, 5868, 5867, 1789);
  g->Binary(ynn_binary_add, 1789, 6376, 1790);
  g->Binary(ynn_binary_pow, 1790, 6378, 1791);
  g->Binary(ynn_binary_multiply, 1787, 1791, 1792);
  g->Convert(6678, 1793);
  g->Binary(ynn_binary_multiply, 1792, 1793, 1794);
  g->Slice(1794, 1795, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1794, 1796, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1796, 1798);
  g->Concat({1798,1795}, 1799, 3);
  g->Binary(ynn_binary_multiply, 1794, 2133, 1800);
  g->Binary(ynn_binary_multiply, 1799, 2992, 1801);
  g->Binary(ynn_binary_add, 1800, 1801, 1802);
}

// Scope: "Layer23 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(1802, 762, 1803, false, true);
  g->Mask(1803, 6399, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6399, 5872, {-1}, true);
  g->Binary(ynn_binary_subtract, 6399, 5872, 5869);
  g->Unary(ynn_unary_exp, 5869, 5870);
  g->Reduce(ynn_reduce_sum, 5870, 5873, {-1}, true);
  g->Binary(ynn_binary_divide, 5404, 5873, 5871);
  g->Binary(ynn_binary_multiply, 5870, 5871, 1804);
  g->Matmul(1804, 764, 1805, false, false);
}

// Scope: "Layer23 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1805, 1806, {0,2,1,3});
  g->FuseDims(1806, 1809, 2, 2);
  g->Quantize(1809, 1810, 0.02436024509370327, 0);
  g->Transpose(6677, 4524, {1,0});
  g->Binary(ynn_binary_multiply, 4109, 4523, 4520);
  g->Dot(1810, 4524, YNN_INVALID_VALUE_ID, 4519, 1);
  g->DequantizeTensor(4519, YNN_INVALID_VALUE_ID, 4520, 4521);
  g->QuantizeTensor(4521, 6342, 4522, 1811);
  g->Dequantize(1811, 1812, 0.027484547346830368, 0);
}

// Scope: "Layer23 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1773, 1774);
  g->Reduce(ynn_reduce_sum, 1774, 5864, {2}, true);
  g->ShapeProduct(1774, 5863, {2});
  g->Binary(ynn_binary_divide, 5864, 5863, 1776);
  g->Binary(ynn_binary_add, 1776, 6376, 1777);
  g->Binary(ynn_binary_pow, 1777, 6378, 1778);
  g->Binary(ynn_binary_multiply, 1773, 1778, 1779);
  g->Convert(6666, 1780);
  g->Binary(ynn_binary_multiply, 1779, 1780, 1781);
  BuildLayer23AttentionQueryProjection(ctx);
  BuildLayer23AttentionSdpa(ctx);
  BuildLayer23AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1812, 1813);
  g->Reduce(ynn_reduce_sum, 1813, 5875, {2}, true);
  g->ShapeProduct(1813, 5874, {2});
  g->Binary(ynn_binary_divide, 5875, 5874, 1814);
  g->Binary(ynn_binary_add, 1814, 6376, 1815);
  g->Binary(ynn_binary_pow, 1815, 6378, 1816);
  g->Binary(ynn_binary_multiply, 1812, 1816, 1817);
  g->Convert(6673, 1818);
  g->Binary(ynn_binary_multiply, 1817, 1818, 1820);
  g->Binary(ynn_binary_add, 1773, 1820, 1821);
}

// Scope: "Layer23 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1821, 1822);
  g->Reduce(ynn_reduce_sum, 1822, 5877, {2}, true);
  g->ShapeProduct(1822, 5876, {2});
  g->Binary(ynn_binary_divide, 5877, 5876, 1823);
  g->Binary(ynn_binary_add, 1823, 6376, 1824);
  g->Binary(ynn_binary_pow, 1824, 6378, 1825);
  g->Binary(ynn_binary_multiply, 1821, 1825, 1826);
  g->Convert(6676, 1827);
  g->Binary(ynn_binary_multiply, 1826, 1827, 1828);
  g->Quantize(1828, 1829, 0.02338595874607563, 0);
  g->Transpose(6670, 4531, {1,0});
  g->Binary(ynn_binary_multiply, 4528, 4530, 4526);
  g->Dot(1829, 4531, YNN_INVALID_VALUE_ID, 4525, 1);
  g->DequantizeTensor(4525, YNN_INVALID_VALUE_ID, 4526, 4527);
  g->QuantizeTensor(4527, 6342, 4529, 1831);
  g->Dequantize(1831, 1832, 0.03100394643843174, 0);
  g->Transpose(6669, 4536, {1,0});
  g->Binary(ynn_binary_multiply, 4528, 4535, 4533);
  g->Dot(1829, 4536, YNN_INVALID_VALUE_ID, 4532, 1);
  g->DequantizeTensor(4532, YNN_INVALID_VALUE_ID, 4533, 4534);
  g->QuantizeTensor(4534, 6342, 4529, 1833);
  g->Dequantize(1833, 1834, 0.03100394643843174, 0);
  g->Polynomial(1834, 5880, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5880, 5881);
  g->Binary(ynn_binary_add, 5881, 5404, 5878);
  g->Binary(ynn_binary_multiply, 1834, 5402, 5879);
  g->Binary(ynn_binary_multiply, 5879, 5878, 1835);
  g->Binary(ynn_binary_multiply, 1832, 1835, 1836);
  g->Quantize(1836, 1837, 0.0433070994913578, 0);
  g->Transpose(6668, 4543, {1,0});
  g->Binary(ynn_binary_multiply, 4540, 4542, 4538);
  g->Dot(1837, 4543, YNN_INVALID_VALUE_ID, 4537, 1);
  g->DequantizeTensor(4537, YNN_INVALID_VALUE_ID, 4538, 4539);
  g->QuantizeTensor(4539, 6342, 4541, 1838);
  g->Dequantize(1838, 1839, 0.025599855929613113, 0);
  g->Unary(ynn_unary_square, 1839, 1841);
  g->Reduce(ynn_reduce_sum, 1841, 5883, {2}, true);
  g->ShapeProduct(1841, 5882, {2});
  g->Binary(ynn_binary_divide, 5883, 5882, 1842);
  g->Binary(ynn_binary_add, 1842, 6376, 1843);
  g->Binary(ynn_binary_pow, 1843, 6378, 1844);
  g->Binary(ynn_binary_multiply, 1839, 1844, 1845);
  g->Convert(6674, 1846);
  g->Binary(ynn_binary_multiply, 1845, 1846, 1847);
  g->Binary(ynn_binary_add, 1821, 1847, 1848);
}

// Scope: "Layer23 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1047, 1849, {0,0,23,0}, {-1,-1,1,-1});
  g->Reshape(1849, 1850, {1,1,256});
  g->Binary(ynn_binary_add, 1850, 6972, 1852);
  g->Binary(ynn_binary_multiply, 1852, 6374, 1853);
  g->Quantize(1848, 1854, 0.1760360449552536, 0);
  g->Transpose(6671, 4550, {1,0});
  g->Binary(ynn_binary_multiply, 4547, 4549, 4545);
  g->Dot(1854, 4550, YNN_INVALID_VALUE_ID, 4544, 1);
  g->DequantizeTensor(4544, YNN_INVALID_VALUE_ID, 4545, 4546);
  g->QuantizeTensor(4546, 6342, 4548, 1855);
  g->Dequantize(1855, 1856, 0.07775591313838959, 0);
  g->Polynomial(1856, 5886, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5886, 5887);
  g->Binary(ynn_binary_add, 5887, 5404, 5884);
  g->Binary(ynn_binary_multiply, 1856, 5402, 5885);
  g->Binary(ynn_binary_multiply, 5885, 5884, 1857);
  g->Binary(ynn_binary_multiply, 1857, 1853, 1858);
  g->Quantize(1858, 1859, 0.3799212574958801, 0);
  g->Transpose(6672, 4557, {1,0});
  g->Binary(ynn_binary_multiply, 4554, 4556, 4552);
  g->Dot(1859, 4557, YNN_INVALID_VALUE_ID, 4551, 1);
  g->DequantizeTensor(4551, YNN_INVALID_VALUE_ID, 4552, 4553);
  g->QuantizeTensor(4553, 6342, 4555, 1860);
  g->Dequantize(1860, 1861, 0.08570276200771332, 0);
  g->Unary(ynn_unary_square, 1861, 1863);
  g->Reduce(ynn_reduce_sum, 1863, 5889, {2}, true);
  g->ShapeProduct(1863, 5888, {2});
  g->Binary(ynn_binary_divide, 5889, 5888, 1864);
  g->Binary(ynn_binary_add, 1864, 6376, 1865);
  g->Binary(ynn_binary_pow, 1865, 6378, 1866);
  g->Binary(ynn_binary_multiply, 1861, 1866, 1867);
  g->Convert(6675, 1868);
  g->Binary(ynn_binary_multiply, 1867, 1868, 1869);
  g->Binary(ynn_binary_add, 1848, 1869, 1870);
  g->Convert(6667, 1871);
  g->Binary(ynn_binary_multiply, 1870, 1871, 1872);
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
  g->Quantize(1880, 1881, 0.10295870155096054, 0);
  g->Transpose(6693, 4564, {1,0});
  g->Binary(ynn_binary_multiply, 4561, 4563, 4559);
  g->Dot(1881, 4564, YNN_INVALID_VALUE_ID, 4558, 1);
  g->DequantizeTensor(4558, YNN_INVALID_VALUE_ID, 4559, 4560);
  g->QuantizeTensor(4560, 6342, 4562, 1882);
  g->Dequantize(1882, 1883, 0.1919291466474533, 0);
  g->SplitDim(1883, 1885, 2, {8,512});
  g->Transpose(1885, 1886, {0,2,1,3});
  g->Unary(ynn_unary_square, 1886, 1887);
  g->Reduce(ynn_reduce_sum, 1887, 5893, {3}, true);
  g->ShapeProduct(1887, 5892, {3});
  g->Binary(ynn_binary_divide, 5893, 5892, 1888);
  g->Binary(ynn_binary_add, 1888, 6376, 1889);
  g->Binary(ynn_binary_pow, 1889, 6378, 1890);
  g->Binary(ynn_binary_multiply, 1886, 1890, 1891);
  g->Convert(6692, 1892);
  g->Binary(ynn_binary_multiply, 1891, 1892, 1893);
  g->Slice(1893, 1894, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(1893, 1896, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 1896, 1897);
  g->Concat({1897,1894}, 1898, 3);
  g->Binary(ynn_binary_multiply, 1893, 3406, 1899);
  g->Binary(ynn_binary_multiply, 1898, 3508, 1900);
  g->Binary(ynn_binary_add, 1899, 1900, 1901);
}

// Scope: "Layer24 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer24AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(1901, 895, 1902, false, true);
  g->Mask(1902, 6400, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 6400, 5899, {-1}, true);
  g->Binary(ynn_binary_subtract, 6400, 5899, 5896);
  g->Unary(ynn_unary_exp, 5896, 5897);
  g->Reduce(ynn_reduce_sum, 5897, 5900, {-1}, true);
  g->Binary(ynn_binary_divide, 5404, 5900, 5898);
  g->Binary(ynn_binary_multiply, 5897, 5898, 1903);
  g->Matmul(1903, 897, 1904, false, false);
}

// Scope: "Layer24 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer24AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1904, 1906, {0,2,1,3});
  g->FuseDims(1906, 1907, 2, 2);
  g->Quantize(1907, 1908, 0.01457924209535122, 0);
  g->Transpose(6691, 4570, {1,0});
  g->Binary(ynn_binary_multiply, 4064, 4569, 4566);
  g->Dot(1908, 4570, YNN_INVALID_VALUE_ID, 4565, 1);
  g->DequantizeTensor(4565, YNN_INVALID_VALUE_ID, 4566, 4567);
  g->QuantizeTensor(4567, 6342, 4568, 1909);
  g->Dequantize(1909, 1910, 0.02337142638862133, 0);
}

// Scope: "Layer24 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer24Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1872, 1874);
  g->Reduce(ynn_reduce_sum, 1874, 5891, {2}, true);
  g->ShapeProduct(1874, 5890, {2});
  g->Binary(ynn_binary_divide, 5891, 5890, 1875);
  g->Binary(ynn_binary_add, 1875, 6376, 1876);
  g->Binary(ynn_binary_pow, 1876, 6378, 1877);
  g->Binary(ynn_binary_multiply, 1872, 1877, 1878);
  g->Convert(6680, 1879);
  g->Binary(ynn_binary_multiply, 1878, 1879, 1880);
  BuildLayer24AttentionQueryProjection(ctx);
  BuildLayer24AttentionSdpa(ctx);
  BuildLayer24AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1910, 1911);
  g->Reduce(ynn_reduce_sum, 1911, 5902, {2}, true);
  g->ShapeProduct(1911, 5901, {2});
  g->Binary(ynn_binary_divide, 5902, 5901, 1912);
  g->Binary(ynn_binary_add, 1912, 6376, 1913);
  g->Binary(ynn_binary_pow, 1913, 6378, 1914);
  g->Binary(ynn_binary_multiply, 1910, 1914, 1915);
  g->Convert(6687, 1918);
  g->Binary(ynn_binary_multiply, 1915, 1918, 1919);
  g->Binary(ynn_binary_add, 1872, 1919, 1920);
}

// Scope: "Layer24 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer24Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1920, 1921);
  g->Reduce(ynn_reduce_sum, 1921, 5904, {2}, true);
  g->ShapeProduct(1921, 5903, {2});
  g->Binary(ynn_binary_divide, 5904, 5903, 1922);
  g->Binary(ynn_binary_add, 1922, 6376, 1923);
  g->Binary(ynn_binary_pow, 1923, 6378, 1924);
  g->Binary(ynn_binary_multiply, 1920, 1924, 1925);
  g->Convert(6690, 1926);
  g->Binary(ynn_binary_multiply, 1925, 1926, 1927);
  g->Quantize(1927, 1929, 0.018518447875976562, 0);
  g->Transpose(6684, 4577, {1,0});
  g->Binary(ynn_binary_multiply, 4574, 4576, 4572);
  g->Dot(1929, 4577, YNN_INVALID_VALUE_ID, 4571, 1);
  g->DequantizeTensor(4571, YNN_INVALID_VALUE_ID, 4572, 4573);
  g->QuantizeTensor(4573, 6342, 4575, 1930);
  g->Dequantize(1930, 1931, 0.027313001453876495, 0);
  g->Transpose(6683, 4582, {1,0});
  g->Binary(ynn_binary_multiply, 4574, 4581, 4579);
  g->Dot(1929, 4582, YNN_INVALID_VALUE_ID, 4578, 1);
  g->DequantizeTensor(4578, YNN_INVALID_VALUE_ID, 4579, 4580);
  g->QuantizeTensor(4580, 6342, 4575, 1932);
  g->Dequantize(1932, 1933, 0.027313001453876495, 0);
  g->Polynomial(1933, 5907, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5907, 5908);
  g->Binary(ynn_binary_add, 5908, 5404, 5905);
  g->Binary(ynn_binary_multiply, 1933, 5402, 5906);
  g->Binary(ynn_binary_multiply, 5906, 5905, 1934);
  g->Binary(ynn_binary_multiply, 1931, 1934, 1935);
  g->Quantize(1935, 1936, 0.01894685998558998, 0);
  g->Transpose(6682, 4589, {1,0});
  g->Binary(ynn_binary_multiply, 4586, 4588, 4584);
  g->Dot(1936, 4589, YNN_INVALID_VALUE_ID, 4583, 1);
  g->DequantizeTensor(4583, YNN_INVALID_VALUE_ID, 4584, 4585);
  g->QuantizeTensor(4585, 6342, 4587, 1937);
  g->Dequantize(1937, 1939, 0.009169002994894981, 0);
  g->Unary(ynn_unary_square, 1939, 1940);
  g->Reduce(ynn_reduce_sum, 1940, 5910, {2}, true);
  g->ShapeProduct(1940, 5909, {2});
  g->Binary(ynn_binary_divide, 5910, 5909, 1941);
  g->Binary(ynn_binary_add, 1941, 6376, 1942);
  g->Binary(ynn_binary_pow, 1942, 6378, 1943);
  g->Binary(ynn_binary_multiply, 1939, 1943, 1944);
  g->Convert(6688, 1945);
  g->Binary(ynn_binary_multiply, 1944, 1945, 1946);
  g->Binary(ynn_binary_add, 1920, 1946, 1947);
}

// Scope: "Layer24 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer24PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1047, 1948, {0,0,24,0}, {-1,-1,1,-1});
  g->Reshape(1948, 1950, {1,1,256});
  g->Binary(ynn_binary_add, 1950, 6973, 1951);
  g->Binary(ynn_binary_multiply, 1951, 6374, 1952);
  g->Quantize(1947, 1953, 0.1741907149553299, 0);
  g->Transpose(6685, 4596, {1,0});
  g->Binary(ynn_binary_multiply, 4593, 4595, 4591);
  g->Dot(1953, 4596, YNN_INVALID_VALUE_ID, 4590, 1);
  g->DequantizeTensor(4590, YNN_INVALID_VALUE_ID, 4591, 4592);
  g->QuantizeTensor(4592, 6342, 4594, 1954);
  g->Dequantize(1954, 1955, 0.08710630983114243, 0);
  g->Polynomial(1955, 5913, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5913, 5914);
  g->Binary(ynn_binary_add, 5914, 5404, 5911);
  g->Binary(ynn_binary_multiply, 1955, 5402, 5912);
  g->Binary(ynn_binary_multiply, 5912, 5911, 1956);
  g->Binary(ynn_binary_multiply, 1956, 1952, 1957);
  g->Quantize(1957, 1958, 1.0236220359802246, 0);
  g->Transpose(6686, 4603, {1,0});
  g->Binary(ynn_binary_multiply, 4600, 4602, 4598);
  g->Dot(1958, 4603, YNN_INVALID_VALUE_ID, 4597, 1);
  g->DequantizeTensor(4597, YNN_INVALID_VALUE_ID, 4598, 4599);
  g->QuantizeTensor(4599, 6342, 4601, 1959);
  g->Dequantize(1959, 1961, 0.1628752052783966, 0);
  g->Unary(ynn_unary_square, 1961, 1962);
  g->Reduce(ynn_reduce_sum, 1962, 5916, {2}, true);
  g->ShapeProduct(1962, 5915, {2});
  g->Binary(ynn_binary_divide, 5916, 5915, 1963);
  g->Binary(ynn_binary_add, 1963, 6376, 1964);
  g->Binary(ynn_binary_pow, 1964, 6378, 1965);
  g->Binary(ynn_binary_multiply, 1961, 1965, 1966);
  g->Convert(6689, 1967);
  g->Binary(ynn_binary_multiply, 1966, 1967, 1968);
  g->Binary(ynn_binary_add, 1947, 1968, 1969);
  g->Convert(6681, 1970);
  g->Binary(ynn_binary_multiply, 1969, 1970, 1972);
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
  g->Quantize(1979, 1980, 0.1674470156431198, 0);
  g->Transpose(6707, 4617, {1,0});
  g->Binary(ynn_binary_multiply, 4614, 4616, 4612);
  g->Dot(1980, 4617, YNN_INVALID_VALUE_ID, 4611, 1);
  g->DequantizeTensor(4611, YNN_INVALID_VALUE_ID, 4612, 4613);
  g->QuantizeTensor(4613, 6342, 4615, 1981);
  g->Dequantize(1981, 1983, 0.15452757477760315, 0);
  g->SplitDim(1983, 1984, 2, {8,256});
  g->Transpose(1984, 1985, {0,2,1,3});
  g->Unary(ynn_unary_square, 1985, 1986);
  g->Reduce(ynn_reduce_sum, 1986, 5920, {3}, true);
  g->ShapeProduct(1986, 5919, {3});
  g->Binary(ynn_binary_divide, 5920, 5919, 1987);
  g->Binary(ynn_binary_add, 1987, 6376, 1988);
  g->Binary(ynn_binary_pow, 1988, 6378, 1989);
  g->Binary(ynn_binary_multiply, 1985, 1989, 1990);
  g->Convert(6706, 1991);
  g->Binary(ynn_binary_multiply, 1990, 1991, 1992);
  g->Slice(1992, 1994, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1992, 1995, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1995, 1996);
  g->Concat({1996,1994}, 1997, 3);
  g->Binary(ynn_binary_multiply, 1992, 2133, 1998);
  g->Binary(ynn_binary_multiply, 1997, 2992, 1999);
  g->Binary(ynn_binary_add, 1998, 1999, 2000);
}

// Scope: "Layer25 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer25AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(2000, 762, 2001, false, true);
  g->Mask(2001, 6401, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6401, 5924, {-1}, true);
  g->Binary(ynn_binary_subtract, 6401, 5924, 5921);
  g->Unary(ynn_unary_exp, 5921, 5922);
  g->Reduce(ynn_reduce_sum, 5922, 5925, {-1}, true);
  g->Binary(ynn_binary_divide, 5404, 5925, 5923);
  g->Binary(ynn_binary_multiply, 5922, 5923, 2002);
  g->Matmul(2002, 764, 2004, false, false);
}

// Scope: "Layer25 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer25AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(2004, 2005, {0,2,1,3});
  g->FuseDims(2005, 2006, 2, 2);
  g->Quantize(2006, 2007, 0.02325296215713024, 0);
  g->Transpose(6705, 4623, {1,0});
  g->Binary(ynn_binary_multiply, 4211, 4622, 4619);
  g->Dot(2007, 4623, YNN_INVALID_VALUE_ID, 4618, 1);
  g->DequantizeTensor(4618, YNN_INVALID_VALUE_ID, 4619, 4620);
  g->QuantizeTensor(4620, 6342, 4621, 2008);
  g->Dequantize(2008, 2009, 0.040348730981349945, 0);
}

// Scope: "Layer25 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer25Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1972, 1973);
  g->Reduce(ynn_reduce_sum, 1973, 5918, {2}, true);
  g->ShapeProduct(1973, 5917, {2});
  g->Binary(ynn_binary_divide, 5918, 5917, 1974);
  g->Binary(ynn_binary_add, 1974, 6376, 1975);
  g->Binary(ynn_binary_pow, 1975, 6378, 1976);
  g->Binary(ynn_binary_multiply, 1972, 1976, 1977);
  g->Convert(6694, 1978);
  g->Binary(ynn_binary_multiply, 1977, 1978, 1979);
  BuildLayer25AttentionQueryProjection(ctx);
  BuildLayer25AttentionSdpa(ctx);
  BuildLayer25AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2009, 2010);
  g->Reduce(ynn_reduce_sum, 2010, 5927, {2}, true);
  g->ShapeProduct(2010, 5926, {2});
  g->Binary(ynn_binary_divide, 5927, 5926, 2011);
  g->Binary(ynn_binary_add, 2011, 6376, 2012);
  g->Binary(ynn_binary_pow, 2012, 6378, 2013);
  g->Binary(ynn_binary_multiply, 2009, 2013, 2015);
  g->Convert(6701, 2016);
  g->Binary(ynn_binary_multiply, 2015, 2016, 2017);
  g->Binary(ynn_binary_add, 1972, 2017, 2018);
}

// Scope: "Layer25 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer25Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2018, 2019);
  g->Reduce(ynn_reduce_sum, 2019, 5929, {2}, true);
  g->ShapeProduct(2019, 5928, {2});
  g->Binary(ynn_binary_divide, 5929, 5928, 2020);
  g->Binary(ynn_binary_add, 2020, 6376, 2021);
  g->Binary(ynn_binary_pow, 2021, 6378, 2022);
  g->Binary(ynn_binary_multiply, 2018, 2022, 2023);
  g->Convert(6704, 2024);
  g->Binary(ynn_binary_multiply, 2023, 2024, 2027);
  g->Quantize(2027, 2028, 0.02161904238164425, 0);
  g->Transpose(6698, 4636, {1,0});
  g->Binary(ynn_binary_multiply, 4634, 4635, 4632);
  g->Dot(2028, 4636, YNN_INVALID_VALUE_ID, 4631, 1);
  g->DequantizeTensor(4631, YNN_INVALID_VALUE_ID, 4632, 4633);
  g->QuantizeTensor(4633, 6342, 4276, 2029);
  g->Dequantize(2029, 2030, 0.03297245129942894, 0);
  g->Transpose(6697, 4641, {1,0});
  g->Binary(ynn_binary_multiply, 4634, 4640, 4638);
  g->Dot(2028, 4641, YNN_INVALID_VALUE_ID, 4637, 1);
  g->DequantizeTensor(4637, YNN_INVALID_VALUE_ID, 4638, 4639);
  g->QuantizeTensor(4639, 6342, 4276, 2031);
  g->Dequantize(2031, 2032, 0.03297245129942894, 0);
  g->Polynomial(2032, 5934, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5934, 5935);
  g->Binary(ynn_binary_add, 5935, 5404, 5932);
  g->Binary(ynn_binary_multiply, 2032, 5402, 5933);
  g->Binary(ynn_binary_multiply, 5933, 5932, 2033);
  g->Binary(ynn_binary_multiply, 2030, 2033, 2034);
  g->Quantize(2034, 2035, 0.032726388424634933, 0);
  g->Transpose(6696, 4648, {1,0});
  g->Binary(ynn_binary_multiply, 4645, 4647, 4643);
  g->Dot(2035, 4648, YNN_INVALID_VALUE_ID, 4642, 1);
  g->DequantizeTensor(4642, YNN_INVALID_VALUE_ID, 4643, 4644);
  g->QuantizeTensor(4644, 6342, 4646, 2037);
  g->Dequantize(2037, 2038, 0.00990387424826622, 0);
  g->Unary(ynn_unary_square, 2038, 2039);
  g->Reduce(ynn_reduce_sum, 2039, 5937, {2}, true);
  g->ShapeProduct(2039, 5936, {2});
  g->Binary(ynn_binary_divide, 5937, 5936, 2040);
  g->Binary(ynn_binary_add, 2040, 6376, 2041);
  g->Binary(ynn_binary_pow, 2041, 6378, 2042);
  g->Binary(ynn_binary_multiply, 2038, 2042, 2043);
  g->Convert(6702, 2044);
  g->Binary(ynn_binary_multiply, 2043, 2044, 2045);
  g->Binary(ynn_binary_add, 2018, 2045, 2046);
}

// Scope: "Layer25 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer25PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1047, 2048, {0,0,25,0}, {-1,-1,1,-1});
  g->Reshape(2048, 2049, {1,1,256});
  g->Binary(ynn_binary_add, 2049, 6974, 2050);
  g->Binary(ynn_binary_multiply, 2050, 6374, 2051);
  g->Quantize(2046, 2052, 0.1164931058883667, 0);
  g->Transpose(6699, 4655, {1,0});
  g->Binary(ynn_binary_multiply, 4652, 4654, 4650);
  g->Dot(2052, 4655, YNN_INVALID_VALUE_ID, 4649, 1);
  g->DequantizeTensor(4649, YNN_INVALID_VALUE_ID, 4650, 4651);
  g->QuantizeTensor(4651, 6342, 4653, 2053);
  g->Dequantize(2053, 2054, 0.11269685626029968, 0);
  g->Polynomial(2054, 5940, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5940, 5941);
  g->Binary(ynn_binary_add, 5941, 5404, 5938);
  g->Binary(ynn_binary_multiply, 2054, 5402, 5939);
  g->Binary(ynn_binary_multiply, 5939, 5938, 2055);
  g->Binary(ynn_binary_multiply, 2055, 2051, 2056);
  g->Quantize(2056, 2057, 0.5157480239868164, 0);
  g->Transpose(6700, 4662, {1,0});
  g->Binary(ynn_binary_multiply, 4659, 4661, 4657);
  g->Dot(2057, 4662, YNN_INVALID_VALUE_ID, 4656, 1);
  g->DequantizeTensor(4656, YNN_INVALID_VALUE_ID, 4657, 4658);
  g->QuantizeTensor(4658, 6342, 4660, 2059);
  g->Dequantize(2059, 2060, 0.3825955092906952, 0);
  g->Unary(ynn_unary_square, 2060, 2061);
  g->Reduce(ynn_reduce_sum, 2061, 5943, {2}, true);
  g->ShapeProduct(2061, 5942, {2});
  g->Binary(ynn_binary_divide, 5943, 5942, 2062);
  g->Binary(ynn_binary_add, 2062, 6376, 2063);
  g->Binary(ynn_binary_pow, 2063, 6378, 2064);
  g->Binary(ynn_binary_multiply, 2060, 2064, 2065);
  g->Convert(6703, 2066);
  g->Binary(ynn_binary_multiply, 2065, 2066, 2067);
  g->Binary(ynn_binary_add, 2046, 2067, 2068);
  g->Convert(6695, 2070);
  g->Binary(ynn_binary_multiply, 2068, 2070, 2071);
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
  g->Quantize(2078, 2079, 0.14451591670513153, 0);
  g->Transpose(6721, 4669, {1,0});
  g->Binary(ynn_binary_multiply, 4666, 4668, 4664);
  g->Dot(2079, 4669, YNN_INVALID_VALUE_ID, 4663, 1);
  g->DequantizeTensor(4663, YNN_INVALID_VALUE_ID, 4664, 4665);
  g->QuantizeTensor(4665, 6342, 4667, 2081);
  g->Dequantize(2081, 2082, 0.25196850299835205, 0);
  g->SplitDim(2082, 2083, 2, {8,256});
  g->Transpose(2083, 2084, {0,2,1,3});
  g->Unary(ynn_unary_square, 2084, 2085);
  g->Reduce(ynn_reduce_sum, 2085, 5947, {3}, true);
  g->ShapeProduct(2085, 5946, {3});
  g->Binary(ynn_binary_divide, 5947, 5946, 2086);
  g->Binary(ynn_binary_add, 2086, 6376, 2087);
  g->Binary(ynn_binary_pow, 2087, 6378, 2088);
  g->Binary(ynn_binary_multiply, 2084, 2088, 2089);
  g->Convert(6720, 2090);
  g->Binary(ynn_binary_multiply, 2089, 2090, 2092);
  g->Slice(2092, 2093, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2092, 2094, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2094, 2095);
  g->Concat({2095,2093}, 2096, 3);
  g->Binary(ynn_binary_multiply, 2092, 2133, 2097);
  g->Binary(ynn_binary_multiply, 2096, 2992, 2098);
  g->Binary(ynn_binary_add, 2097, 2098, 2099);
}

// Scope: "Layer26 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer26AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(2099, 762, 2100, false, true);
  g->Mask(2100, 6402, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6402, 5951, {-1}, true);
  g->Binary(ynn_binary_subtract, 6402, 5951, 5948);
  g->Unary(ynn_unary_exp, 5948, 5949);
  g->Reduce(ynn_reduce_sum, 5949, 5952, {-1}, true);
  g->Binary(ynn_binary_divide, 5404, 5952, 5950);
  g->Binary(ynn_binary_multiply, 5949, 5950, 2102);
  g->Matmul(2102, 764, 2103, false, false);
}

// Scope: "Layer26 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer26AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(2103, 2104, {0,2,1,3});
  g->FuseDims(2104, 2105, 2, 2);
  g->Quantize(2105, 2106, 0.023129930719733238, 0);
  g->Transpose(6719, 4675, {1,0});
  g->Binary(ynn_binary_multiply, 4229, 4674, 4671);
  g->Dot(2106, 4675, YNN_INVALID_VALUE_ID, 4670, 1);
  g->DequantizeTensor(4670, YNN_INVALID_VALUE_ID, 4671, 4672);
  g->QuantizeTensor(4672, 6342, 4673, 2107);
  g->Dequantize(2107, 2108, 0.04343831539154053, 0);
}

// Scope: "Layer26 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer26Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2071, 2072);
  g->Reduce(ynn_reduce_sum, 2072, 5945, {2}, true);
  g->ShapeProduct(2072, 5944, {2});
  g->Binary(ynn_binary_divide, 5945, 5944, 2073);
  g->Binary(ynn_binary_add, 2073, 6376, 2074);
  g->Binary(ynn_binary_pow, 2074, 6378, 2075);
  g->Binary(ynn_binary_multiply, 2071, 2075, 2076);
  g->Convert(6708, 2077);
  g->Binary(ynn_binary_multiply, 2076, 2077, 2078);
  BuildLayer26AttentionQueryProjection(ctx);
  BuildLayer26AttentionSdpa(ctx);
  BuildLayer26AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2108, 2109);
  g->Reduce(ynn_reduce_sum, 2109, 5954, {2}, true);
  g->ShapeProduct(2109, 5953, {2});
  g->Binary(ynn_binary_divide, 5954, 5953, 2110);
  g->Binary(ynn_binary_add, 2110, 6376, 2111);
  g->Binary(ynn_binary_pow, 2111, 6378, 2113);
  g->Binary(ynn_binary_multiply, 2108, 2113, 2114);
  g->Convert(6715, 2115);
  g->Binary(ynn_binary_multiply, 2114, 2115, 2116);
  g->Binary(ynn_binary_add, 2071, 2116, 2117);
}

// Scope: "Layer26 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer26Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2117, 2118);
  g->Reduce(ynn_reduce_sum, 2118, 5956, {2}, true);
  g->ShapeProduct(2118, 5955, {2});
  g->Binary(ynn_binary_divide, 5956, 5955, 2119);
  g->Binary(ynn_binary_add, 2119, 6376, 2120);
  g->Binary(ynn_binary_pow, 2120, 6378, 2121);
  g->Binary(ynn_binary_multiply, 2117, 2121, 2122);
  g->Convert(6718, 2124);
  g->Binary(ynn_binary_multiply, 2122, 2124, 2125);
  g->Quantize(2125, 2126, 0.02699781395494938, 0);
  g->Transpose(6712, 4682, {1,0});
  g->Binary(ynn_binary_multiply, 4679, 4681, 4677);
  g->Dot(2126, 4682, YNN_INVALID_VALUE_ID, 4676, 1);
  g->DequantizeTensor(4676, YNN_INVALID_VALUE_ID, 4677, 4678);
  g->QuantizeTensor(4678, 6342, 4680, 2127);
  g->Dequantize(2127, 2128, 0.04478347674012184, 0);
  g->Transpose(6711, 4687, {1,0});
  g->Binary(ynn_binary_multiply, 4679, 4686, 4684);
  g->Dot(2126, 4687, YNN_INVALID_VALUE_ID, 4683, 1);
  g->DequantizeTensor(4683, YNN_INVALID_VALUE_ID, 4684, 4685);
  g->QuantizeTensor(4685, 6342, 4680, 2129);
  g->Dequantize(2129, 2130, 0.04478347674012184, 0);
  g->Polynomial(2130, 5959, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5959, 5960);
  g->Binary(ynn_binary_add, 5960, 5404, 5957);
  g->Binary(ynn_binary_multiply, 2130, 5402, 5958);
  g->Binary(ynn_binary_multiply, 5958, 5957, 2131);
  g->Binary(ynn_binary_multiply, 2128, 2131, 2132);
  g->Quantize(2132, 2136, 0.05019685998558998, 0);
  g->Transpose(6710, 4694, {1,0});
  g->Binary(ynn_binary_multiply, 4691, 4693, 4689);
  g->Dot(2136, 4694, YNN_INVALID_VALUE_ID, 4688, 1);
  g->DequantizeTensor(4688, YNN_INVALID_VALUE_ID, 4689, 4690);
  g->QuantizeTensor(4690, 6342, 4692, 2137);
  g->Dequantize(2137, 2138, 0.017497630789875984, 0);
  g->Unary(ynn_unary_square, 2138, 2139);
  g->Reduce(ynn_reduce_sum, 2139, 5962, {2}, true);
  g->ShapeProduct(2139, 5961, {2});
  g->Binary(ynn_binary_divide, 5962, 5961, 2140);
  g->Binary(ynn_binary_add, 2140, 6376, 2141);
  g->Binary(ynn_binary_pow, 2141, 6378, 2142);
  g->Binary(ynn_binary_multiply, 2138, 2142, 2143);
  g->Convert(6716, 2144);
  g->Binary(ynn_binary_multiply, 2143, 2144, 2145);
  g->Binary(ynn_binary_add, 2117, 2145, 2147);
}

// Scope: "Layer26 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer26PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1047, 2148, {0,0,26,0}, {-1,-1,1,-1});
  g->Reshape(2148, 2149, {1,1,256});
  g->Binary(ynn_binary_add, 2149, 6975, 2150);
  g->Binary(ynn_binary_multiply, 2150, 6374, 2151);
  g->Quantize(2147, 2152, 0.11300035566091537, 0);
  g->Transpose(6713, 4701, {1,0});
  g->Binary(ynn_binary_multiply, 4698, 4700, 4696);
  g->Dot(2152, 4701, YNN_INVALID_VALUE_ID, 4695, 1);
  g->DequantizeTensor(4695, YNN_INVALID_VALUE_ID, 4696, 4697);
  g->QuantizeTensor(4697, 6342, 4699, 2153);
  g->Dequantize(2153, 2154, 0.10088583081960678, 0);
  g->Polynomial(2154, 5965, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5965, 5966);
  g->Binary(ynn_binary_add, 5966, 5404, 5963);
  g->Binary(ynn_binary_multiply, 2154, 5402, 5964);
  g->Binary(ynn_binary_multiply, 5964, 5963, 2155);
  g->Binary(ynn_binary_multiply, 2155, 2151, 2156);
  g->Quantize(2156, 2158, 0.5472440719604492, 0);
  g->Transpose(6714, 4708, {1,0});
  g->Binary(ynn_binary_multiply, 4705, 4707, 4703);
  g->Dot(2158, 4708, YNN_INVALID_VALUE_ID, 4702, 1);
  g->DequantizeTensor(4702, YNN_INVALID_VALUE_ID, 4703, 4704);
  g->QuantizeTensor(4704, 6342, 4706, 2159);
  g->Dequantize(2159, 2160, 0.34460699558258057, 0);
  g->Unary(ynn_unary_square, 2160, 2161);
  g->Reduce(ynn_reduce_sum, 2161, 5968, {2}, true);
  g->ShapeProduct(2161, 5967, {2});
  g->Binary(ynn_binary_divide, 5968, 5967, 2162);
  g->Binary(ynn_binary_add, 2162, 6376, 2163);
  g->Binary(ynn_binary_pow, 2163, 6378, 2164);
  g->Binary(ynn_binary_multiply, 2160, 2164, 2165);
  g->Convert(6717, 2166);
  g->Binary(ynn_binary_multiply, 2165, 2166, 2167);
  g->Binary(ynn_binary_add, 2147, 2167, 2168);
  g->Convert(6709, 2169);
  g->Binary(ynn_binary_multiply, 2168, 2169, 2170);
}

// Scope: "Layer26"
LAB_YNN_BUILDER_NOINLINE void BuildLayer26(Context& ctx) {
  BuildLayer26Attention(ctx);
  BuildLayer26Mlp(ctx);
  BuildLayer26PerLayerEmbedding(ctx);
}

}  // namespace BuildGemma4DecodeSource
