// Generated YNNPACK builder; do not edit.
#include "gemma4_decode_builder.h"

namespace BuildGemma4DecodeSource {

// Scope: "Layer16 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(1069, 1070, 0.44548678398132324, 0);
  g->Transpose(6657, 4152, {1,0});
  g->Binary(ynn_binary_multiply, 4149, 4151, 4147);
  g->Dot(1070, 4152, YNN_INVALID_VALUE_ID, 4146, 1);
  g->DequantizeTensor(4146, YNN_INVALID_VALUE_ID, 4147, 4148);
  g->QuantizeTensor(4148, 6434, 4150, 1072);
  g->Dequantize(1072, 1073, 0.3641732335090637, 0);
  g->SplitDim(1073, 1074, 2, {8,256});
  g->Transpose(1074, 1075, {0,2,1,3});
  g->Unary(ynn_unary_square, 1075, 1076);
  g->Reduce(ynn_reduce_sum, 1076, 5706, {3}, true);
  g->ShapeProduct(1076, 5705, {3});
  g->Binary(ynn_binary_divide, 5706, 5705, 1077);
  g->Binary(ynn_binary_add, 1077, 6469, 1078);
  g->Unary(ynn_unary_rsqrt, 1078, 1079);
  g->Binary(ynn_binary_multiply, 1075, 1079, 1080);
  g->Binary(ynn_binary_multiply, 1080, 6656, 1081);
  g->Slice(1081, 1082, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1081, 1083, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1083, 1084);
  g->Concat({1084,1082}, 1085, 3);
  g->Binary(ynn_binary_multiply, 1081, 3009, 1086);
  g->Binary(ynn_binary_multiply, 1085, 3112, 1087);
  g->Binary(ynn_binary_add, 1086, 1087, 1088);
}

// Scope: "Layer16 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7120, 1089, 0.0059552486054599285, 0);
  g->Dequantize(7135, 1090, 0.047244105488061905, 0);
  g->Matmul(1088, 1089, 1091, false, true);
  g->Mask(1091, 6483, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6483, 5715, {-1}, true);
  g->Binary(ynn_binary_subtract, 6483, 5715, 5712);
  g->Unary(ynn_unary_exp, 5712, 5713);
  g->Reduce(ynn_reduce_sum, 5713, 5716, {-1}, true);
  g->Binary(ynn_binary_divide, 5430, 5716, 5714);
  g->Binary(ynn_binary_multiply, 5713, 5714, 1093);
  g->Matmul(1093, 1090, 1094, false, false);
}

// Scope: "Layer16 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1094, 1095, {0,2,1,3});
  g->FuseDims(1095, 1096, 2, 2);
  g->Quantize(1096, 1097, 0.023745087906718254, 0);
  g->Transpose(6655, 4159, {1,0});
  g->Binary(ynn_binary_multiply, 4156, 4158, 4154);
  g->Dot(1097, 4159, YNN_INVALID_VALUE_ID, 4153, 1);
  g->DequantizeTensor(4153, YNN_INVALID_VALUE_ID, 4154, 4155);
  g->QuantizeTensor(4155, 6434, 4157, 1098);
  g->Dequantize(1098, 1099, 0.02639034017920494, 0);
}

// Scope: "Layer16 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1063, 1064);
  g->Reduce(ynn_reduce_sum, 1064, 5704, {2}, true);
  g->ShapeProduct(1064, 5703, {2});
  g->Binary(ynn_binary_divide, 5704, 5703, 1065);
  g->Binary(ynn_binary_add, 1065, 6469, 1066);
  g->Unary(ynn_unary_rsqrt, 1066, 1067);
  g->Binary(ynn_binary_multiply, 1063, 1067, 1068);
  g->Binary(ynn_binary_multiply, 1068, 6644, 1069);
  BuildLayer16AttentionQueryProjection(ctx);
  BuildLayer16AttentionSdpa(ctx);
  BuildLayer16AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1099, 1100);
  g->Reduce(ynn_reduce_sum, 1100, 5718, {2}, true);
  g->ShapeProduct(1100, 5717, {2});
  g->Binary(ynn_binary_divide, 5718, 5717, 1101);
  g->Binary(ynn_binary_add, 1101, 6469, 1103);
  g->Unary(ynn_unary_rsqrt, 1103, 1104);
  g->Binary(ynn_binary_multiply, 1099, 1104, 1105);
  g->Binary(ynn_binary_multiply, 1105, 6651, 1106);
  g->Binary(ynn_binary_add, 1106, 1063, 1107);
}

// Scope: "Layer16 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1107, 1108);
  g->Reduce(ynn_reduce_sum, 1108, 5720, {2}, true);
  g->ShapeProduct(1108, 5719, {2});
  g->Binary(ynn_binary_divide, 5720, 5719, 1109);
  g->Binary(ynn_binary_add, 1109, 6469, 1110);
  g->Unary(ynn_unary_rsqrt, 1110, 1111);
  g->Binary(ynn_binary_multiply, 1107, 1111, 1112);
  g->Binary(ynn_binary_multiply, 1112, 6654, 1114);
  g->Quantize(1114, 1115, 0.019740456715226173, 0);
  g->Transpose(6648, 4166, {1,0});
  g->Binary(ynn_binary_multiply, 4163, 4165, 4161);
  g->Dot(1115, 4166, YNN_INVALID_VALUE_ID, 4160, 1);
  g->DequantizeTensor(4160, YNN_INVALID_VALUE_ID, 4161, 4162);
  g->QuantizeTensor(4162, 6434, 4164, 1116);
  g->Dequantize(1116, 1117, 0.02042323723435402, 0);
  g->Transpose(6647, 4171, {1,0});
  g->Binary(ynn_binary_multiply, 4163, 4170, 4168);
  g->Dot(1115, 4171, YNN_INVALID_VALUE_ID, 4167, 1);
  g->DequantizeTensor(4167, YNN_INVALID_VALUE_ID, 4168, 4169);
  g->QuantizeTensor(4169, 6434, 4164, 1118);
  g->Dequantize(1118, 1119, 0.02042323723435402, 0);
  g->Polynomial(1119, 5723, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5723, 5724);
  g->Binary(ynn_binary_add, 5724, 5430, 5721);
  g->Binary(ynn_binary_multiply, 1119, 5428, 5722);
  g->Binary(ynn_binary_multiply, 5722, 5721, 1120);
  g->Binary(ynn_binary_multiply, 1117, 1120, 1121);
  g->Quantize(1121, 1122, 0.021530522033572197, 0);
  g->Transpose(6646, 4178, {1,0});
  g->Binary(ynn_binary_multiply, 4175, 4177, 4173);
  g->Dot(1122, 4178, YNN_INVALID_VALUE_ID, 4172, 1);
  g->DequantizeTensor(4172, YNN_INVALID_VALUE_ID, 4173, 4174);
  g->QuantizeTensor(4174, 6434, 4176, 1124);
  g->Dequantize(1124, 1125, 0.011490405537188053, 0);
  g->Unary(ynn_unary_square, 1125, 1126);
  g->Reduce(ynn_reduce_sum, 1126, 5726, {2}, true);
  g->ShapeProduct(1126, 5725, {2});
  g->Binary(ynn_binary_divide, 5726, 5725, 1127);
  g->Binary(ynn_binary_add, 1127, 6469, 1128);
  g->Unary(ynn_unary_rsqrt, 1128, 1129);
  g->Binary(ynn_binary_multiply, 1125, 1129, 1130);
  g->Binary(ynn_binary_multiply, 1130, 6652, 1131);
  g->Binary(ynn_binary_add, 1131, 1107, 1132);
}

// Scope: "Layer16 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(421, 1133, {0,0,16,0}, {-1,-1,1,-1});
  g->Reshape(1133, 1135, {1,1,256});
  g->Unary(ynn_unary_square, 1135, 1136);
  g->Reduce(ynn_reduce_sum, 1136, 5728, {2}, true);
  g->ShapeProduct(1136, 5727, {2});
  g->Binary(ynn_binary_divide, 5728, 5727, 1137);
  g->Binary(ynn_binary_add, 1137, 6469, 1138);
  g->Unary(ynn_unary_rsqrt, 1138, 1139);
  g->Binary(ynn_binary_multiply, 1135, 1139, 1140);
  g->Binary(ynn_binary_multiply, 1140, 7048, 1141);
  g->Binary(ynn_binary_multiply, 7057, 6472, 1142);
  g->Binary(ynn_binary_add, 1141, 1142, 1143);
  g->Binary(ynn_binary_multiply, 1143, 6466, 1144);
  g->Quantize(1132, 1146, 0.1693648248910904, 0);
  g->Transpose(6649, 4192, {1,0});
  g->Binary(ynn_binary_multiply, 4189, 4191, 4187);
  g->Dot(1146, 4192, YNN_INVALID_VALUE_ID, 4186, 1);
  g->DequantizeTensor(4186, YNN_INVALID_VALUE_ID, 4187, 4188);
  g->QuantizeTensor(4188, 6434, 4190, 1147);
  g->Dequantize(1147, 1148, 0.07234252989292145, 0);
  g->Polynomial(1148, 5731, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5731, 5732);
  g->Binary(ynn_binary_add, 5732, 5430, 5729);
  g->Binary(ynn_binary_multiply, 1148, 5428, 5730);
  g->Binary(ynn_binary_multiply, 5730, 5729, 1149);
  g->Binary(ynn_binary_multiply, 1149, 1144, 1150);
  g->Quantize(1150, 1151, 0.8779527544975281, 0);
  g->Transpose(6650, 4199, {1,0});
  g->Binary(ynn_binary_multiply, 4196, 4198, 4194);
  g->Dot(1151, 4199, YNN_INVALID_VALUE_ID, 4193, 1);
  g->DequantizeTensor(4193, YNN_INVALID_VALUE_ID, 4194, 4195);
  g->QuantizeTensor(4195, 6434, 4197, 1152);
  g->Dequantize(1152, 1153, 0.16087517142295837, 0);
  g->Unary(ynn_unary_square, 1153, 1154);
  g->Reduce(ynn_reduce_sum, 1154, 5734, {2}, true);
  g->ShapeProduct(1154, 5733, {2});
  g->Binary(ynn_binary_divide, 5734, 5733, 1155);
  g->Binary(ynn_binary_add, 1155, 6469, 1158);
  g->Unary(ynn_unary_rsqrt, 1158, 1159);
  g->Binary(ynn_binary_multiply, 1153, 1159, 1160);
  g->Binary(ynn_binary_multiply, 1160, 6653, 1161);
  g->Binary(ynn_binary_add, 1132, 1161, 1162);
  g->Binary(ynn_binary_multiply, 1162, 6645, 1163);
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
  g->Quantize(1170, 1171, 0.25072598457336426, 0);
  g->Transpose(6671, 4206, {1,0});
  g->Binary(ynn_binary_multiply, 4203, 4205, 4201);
  g->Dot(1171, 4206, YNN_INVALID_VALUE_ID, 4200, 1);
  g->DequantizeTensor(4200, YNN_INVALID_VALUE_ID, 4201, 4202);
  g->QuantizeTensor(4202, 6434, 4204, 1172);
  g->Dequantize(1172, 1173, 0.374015748500824, 0);
  g->SplitDim(1173, 1174, 2, {8,256});
  g->Transpose(1174, 1175, {0,2,1,3});
  g->Unary(ynn_unary_square, 1175, 1176);
  g->Reduce(ynn_reduce_sum, 1176, 5738, {3}, true);
  g->ShapeProduct(1176, 5737, {3});
  g->Binary(ynn_binary_divide, 5738, 5737, 1177);
  g->Binary(ynn_binary_add, 1177, 6469, 1178);
  g->Unary(ynn_unary_rsqrt, 1178, 1180);
  g->Binary(ynn_binary_multiply, 1175, 1180, 1181);
  g->Binary(ynn_binary_multiply, 1181, 6670, 1182);
  g->Slice(1182, 1183, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1182, 1184, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1184, 1185);
  g->Concat({1185,1183}, 1186, 3);
  g->Binary(ynn_binary_multiply, 1182, 3009, 1187);
  g->Binary(ynn_binary_multiply, 1186, 3112, 1188);
  g->Binary(ynn_binary_add, 1187, 1188, 1189);
}

// Scope: "Layer17 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7120, 1191, 0.0059552486054599285, 0);
  g->Dequantize(7135, 1192, 0.047244105488061905, 0);
  g->Matmul(1189, 1191, 1193, false, true);
  g->Mask(1193, 6484, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6484, 5744, {-1}, true);
  g->Binary(ynn_binary_subtract, 6484, 5744, 5741);
  g->Unary(ynn_unary_exp, 5741, 5742);
  g->Reduce(ynn_reduce_sum, 5742, 5745, {-1}, true);
  g->Binary(ynn_binary_divide, 5430, 5745, 5743);
  g->Binary(ynn_binary_multiply, 5742, 5743, 1194);
  g->Matmul(1194, 1192, 1195, false, false);
}

// Scope: "Layer17 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1195, 1196, {0,2,1,3});
  g->FuseDims(1196, 1197, 2, 2);
  g->Quantize(1197, 1198, 0.023375993594527245, 0);
  g->Transpose(6669, 4213, {1,0});
  g->Binary(ynn_binary_multiply, 4210, 4212, 4208);
  g->Dot(1198, 4213, YNN_INVALID_VALUE_ID, 4207, 1);
  g->DequantizeTensor(4207, YNN_INVALID_VALUE_ID, 4208, 4209);
  g->QuantizeTensor(4209, 6434, 4211, 1199);
  g->Dequantize(1199, 1201, 0.020179564133286476, 0);
}

// Scope: "Layer17 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1163, 1164);
  g->Reduce(ynn_reduce_sum, 1164, 5736, {2}, true);
  g->ShapeProduct(1164, 5735, {2});
  g->Binary(ynn_binary_divide, 5736, 5735, 1165);
  g->Binary(ynn_binary_add, 1165, 6469, 1166);
  g->Unary(ynn_unary_rsqrt, 1166, 1167);
  g->Binary(ynn_binary_multiply, 1163, 1167, 1169);
  g->Binary(ynn_binary_multiply, 1169, 6658, 1170);
  BuildLayer17AttentionQueryProjection(ctx);
  BuildLayer17AttentionSdpa(ctx);
  BuildLayer17AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1201, 1202);
  g->Reduce(ynn_reduce_sum, 1202, 5747, {2}, true);
  g->ShapeProduct(1202, 5746, {2});
  g->Binary(ynn_binary_divide, 5747, 5746, 1203);
  g->Binary(ynn_binary_add, 1203, 6469, 1204);
  g->Unary(ynn_unary_rsqrt, 1204, 1205);
  g->Binary(ynn_binary_multiply, 1201, 1205, 1206);
  g->Binary(ynn_binary_multiply, 1206, 6665, 1207);
  g->Binary(ynn_binary_add, 1207, 1163, 1208);
}

// Scope: "Layer17 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1208, 1209);
  g->Reduce(ynn_reduce_sum, 1209, 5749, {2}, true);
  g->ShapeProduct(1209, 5748, {2});
  g->Binary(ynn_binary_divide, 5749, 5748, 1210);
  g->Binary(ynn_binary_add, 1210, 6469, 1212);
  g->Unary(ynn_unary_rsqrt, 1212, 1213);
  g->Binary(ynn_binary_multiply, 1208, 1213, 1214);
  g->Binary(ynn_binary_multiply, 1214, 6668, 1215);
  g->Quantize(1215, 1216, 0.02002163790166378, 0);
  g->Transpose(6662, 4220, {1,0});
  g->Binary(ynn_binary_multiply, 4217, 4219, 4215);
  g->Dot(1216, 4220, YNN_INVALID_VALUE_ID, 4214, 1);
  g->DequantizeTensor(4214, YNN_INVALID_VALUE_ID, 4215, 4216);
  g->QuantizeTensor(4216, 6434, 4218, 1217);
  g->Dequantize(1217, 1218, 0.02325296215713024, 0);
  g->Transpose(6661, 4225, {1,0});
  g->Binary(ynn_binary_multiply, 4217, 4224, 4222);
  g->Dot(1216, 4225, YNN_INVALID_VALUE_ID, 4221, 1);
  g->DequantizeTensor(4221, YNN_INVALID_VALUE_ID, 4222, 4223);
  g->QuantizeTensor(4223, 6434, 4218, 1219);
  g->Dequantize(1219, 1220, 0.02325296215713024, 0);
  g->Polynomial(1220, 5752, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5752, 5753);
  g->Binary(ynn_binary_add, 5753, 5430, 5750);
  g->Binary(ynn_binary_multiply, 1220, 5428, 5751);
  g->Binary(ynn_binary_multiply, 5751, 5750, 1222);
  g->Binary(ynn_binary_multiply, 1218, 1222, 1223);
  g->Quantize(1223, 1224, 0.03641733527183533, 0);
  g->Transpose(6660, 4232, {1,0});
  g->Binary(ynn_binary_multiply, 4229, 4231, 4227);
  g->Dot(1224, 4232, YNN_INVALID_VALUE_ID, 4226, 1);
  g->DequantizeTensor(4226, YNN_INVALID_VALUE_ID, 4227, 4228);
  g->QuantizeTensor(4228, 6434, 4230, 1225);
  g->Dequantize(1225, 1226, 0.022161640226840973, 0);
  g->Unary(ynn_unary_square, 1226, 1227);
  g->Reduce(ynn_reduce_sum, 1227, 5755, {2}, true);
  g->ShapeProduct(1227, 5754, {2});
  g->Binary(ynn_binary_divide, 5755, 5754, 1228);
  g->Binary(ynn_binary_add, 1228, 6469, 1229);
  g->Unary(ynn_unary_rsqrt, 1229, 1230);
  g->Binary(ynn_binary_multiply, 1226, 1230, 1231);
  g->Binary(ynn_binary_multiply, 1231, 6666, 1233);
  g->Binary(ynn_binary_add, 1233, 1208, 1234);
}

// Scope: "Layer17 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(421, 1235, {0,0,17,0}, {-1,-1,1,-1});
  g->Reshape(1235, 1236, {1,1,256});
  g->Unary(ynn_unary_square, 1236, 1237);
  g->Reduce(ynn_reduce_sum, 1237, 5757, {2}, true);
  g->ShapeProduct(1237, 5756, {2});
  g->Binary(ynn_binary_divide, 5757, 5756, 1238);
  g->Binary(ynn_binary_add, 1238, 6469, 1239);
  g->Unary(ynn_unary_rsqrt, 1239, 1240);
  g->Binary(ynn_binary_multiply, 1236, 1240, 1241);
  g->Binary(ynn_binary_multiply, 1241, 7048, 1242);
  g->Binary(ynn_binary_multiply, 7058, 6472, 1244);
  g->Binary(ynn_binary_add, 1242, 1244, 1245);
  g->Binary(ynn_binary_multiply, 1245, 6466, 1246);
  g->Quantize(1234, 1247, 0.16417057812213898, 0);
  g->Transpose(6663, 4239, {1,0});
  g->Binary(ynn_binary_multiply, 4236, 4238, 4234);
  g->Dot(1247, 4239, YNN_INVALID_VALUE_ID, 4233, 1);
  g->DequantizeTensor(4233, YNN_INVALID_VALUE_ID, 4234, 4235);
  g->QuantizeTensor(4235, 6434, 4237, 1248);
  g->Dequantize(1248, 1249, 0.0821850448846817, 0);
  g->Polynomial(1249, 5760, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5760, 5761);
  g->Binary(ynn_binary_add, 5761, 5430, 5758);
  g->Binary(ynn_binary_multiply, 1249, 5428, 5759);
  g->Binary(ynn_binary_multiply, 5759, 5758, 1250);
  g->Binary(ynn_binary_multiply, 1250, 1246, 1251);
  g->Quantize(1251, 1252, 0.8188976645469666, 0);
  g->Transpose(6664, 4246, {1,0});
  g->Binary(ynn_binary_multiply, 4243, 4245, 4241);
  g->Dot(1252, 4246, YNN_INVALID_VALUE_ID, 4240, 1);
  g->DequantizeTensor(4240, YNN_INVALID_VALUE_ID, 4241, 4242);
  g->QuantizeTensor(4242, 6434, 4244, 1253);
  g->Dequantize(1253, 1255, 0.2322644591331482, 0);
  g->Unary(ynn_unary_square, 1255, 1256);
  g->Reduce(ynn_reduce_sum, 1256, 5765, {2}, true);
  g->ShapeProduct(1256, 5764, {2});
  g->Binary(ynn_binary_divide, 5765, 5764, 1257);
  g->Binary(ynn_binary_add, 1257, 6469, 1258);
  g->Unary(ynn_unary_rsqrt, 1258, 1259);
  g->Binary(ynn_binary_multiply, 1255, 1259, 1260);
  g->Binary(ynn_binary_multiply, 1260, 6667, 1261);
  g->Binary(ynn_binary_add, 1234, 1261, 1262);
  g->Binary(ynn_binary_multiply, 1262, 6659, 1263);
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
  g->Quantize(1271, 1272, 0.3068588376045227, 0);
  g->Transpose(6685, 4260, {1,0});
  g->Binary(ynn_binary_multiply, 4257, 4259, 4255);
  g->Dot(1272, 4260, YNN_INVALID_VALUE_ID, 4254, 1);
  g->DequantizeTensor(4254, YNN_INVALID_VALUE_ID, 4255, 4256);
  g->QuantizeTensor(4256, 6434, 4258, 1273);
  g->Dequantize(1273, 1274, 0.36220473051071167, 0);
  g->SplitDim(1274, 1275, 2, {8,256});
  g->Transpose(1275, 1276, {0,2,1,3});
  g->Unary(ynn_unary_square, 1276, 1278);
  g->Reduce(ynn_reduce_sum, 1278, 5769, {3}, true);
  g->ShapeProduct(1278, 5768, {3});
  g->Binary(ynn_binary_divide, 5769, 5768, 1279);
  g->Binary(ynn_binary_add, 1279, 6469, 1280);
  g->Unary(ynn_unary_rsqrt, 1280, 1281);
  g->Binary(ynn_binary_multiply, 1276, 1281, 1282);
  g->Binary(ynn_binary_multiply, 1282, 6684, 1283);
  g->Slice(1283, 1284, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1283, 1285, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1285, 1286);
  g->Concat({1286,1284}, 1287, 3);
  g->Binary(ynn_binary_multiply, 1283, 3009, 1289);
  g->Binary(ynn_binary_multiply, 1287, 3112, 1290);
  g->Binary(ynn_binary_add, 1289, 1290, 1291);
}

// Scope: "Layer18 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7120, 1292, 0.0059552486054599285, 0);
  g->Dequantize(7135, 1293, 0.047244105488061905, 0);
  g->Matmul(1291, 1292, 1294, false, true);
  g->Mask(1294, 6485, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6485, 5773, {-1}, true);
  g->Binary(ynn_binary_subtract, 6485, 5773, 5770);
  g->Unary(ynn_unary_exp, 5770, 5771);
  g->Reduce(ynn_reduce_sum, 5771, 5774, {-1}, true);
  g->Binary(ynn_binary_divide, 5430, 5774, 5772);
  g->Binary(ynn_binary_multiply, 5771, 5772, 1295);
  g->Matmul(1295, 1293, 1296, false, false);
}

// Scope: "Layer18 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1296, 1297, {0,2,1,3});
  g->FuseDims(1297, 1299, 2, 2);
  g->Quantize(1299, 1300, 0.023006899282336235, 0);
  g->Transpose(6683, 4267, {1,0});
  g->Binary(ynn_binary_multiply, 4264, 4266, 4262);
  g->Dot(1300, 4267, YNN_INVALID_VALUE_ID, 4261, 1);
  g->DequantizeTensor(4261, YNN_INVALID_VALUE_ID, 4262, 4263);
  g->QuantizeTensor(4263, 6434, 4265, 1301);
  g->Dequantize(1301, 1302, 0.023901576176285744, 0);
}

// Scope: "Layer18 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1263, 1264);
  g->Reduce(ynn_reduce_sum, 1264, 5767, {2}, true);
  g->ShapeProduct(1264, 5766, {2});
  g->Binary(ynn_binary_divide, 5767, 5766, 1267);
  g->Binary(ynn_binary_add, 1267, 6469, 1268);
  g->Unary(ynn_unary_rsqrt, 1268, 1269);
  g->Binary(ynn_binary_multiply, 1263, 1269, 1270);
  g->Binary(ynn_binary_multiply, 1270, 6672, 1271);
  BuildLayer18AttentionQueryProjection(ctx);
  BuildLayer18AttentionSdpa(ctx);
  BuildLayer18AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1302, 1303);
  g->Reduce(ynn_reduce_sum, 1303, 5776, {2}, true);
  g->ShapeProduct(1303, 5775, {2});
  g->Binary(ynn_binary_divide, 5776, 5775, 1304);
  g->Binary(ynn_binary_add, 1304, 6469, 1305);
  g->Unary(ynn_unary_rsqrt, 1305, 1306);
  g->Binary(ynn_binary_multiply, 1302, 1306, 1307);
  g->Binary(ynn_binary_multiply, 1307, 6679, 1308);
  g->Binary(ynn_binary_add, 1308, 1263, 1310);
}

// Scope: "Layer18 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1310, 1311);
  g->Reduce(ynn_reduce_sum, 1311, 5778, {2}, true);
  g->ShapeProduct(1311, 5777, {2});
  g->Binary(ynn_binary_divide, 5778, 5777, 1312);
  g->Binary(ynn_binary_add, 1312, 6469, 1313);
  g->Unary(ynn_unary_rsqrt, 1313, 1314);
  g->Binary(ynn_binary_multiply, 1310, 1314, 1315);
  g->Binary(ynn_binary_multiply, 1315, 6682, 1316);
  g->Quantize(1316, 1317, 0.018082860857248306, 0);
  g->Transpose(6676, 4274, {1,0});
  g->Binary(ynn_binary_multiply, 4271, 4273, 4269);
  g->Dot(1317, 4274, YNN_INVALID_VALUE_ID, 4268, 1);
  g->DequantizeTensor(4268, YNN_INVALID_VALUE_ID, 4269, 4270);
  g->QuantizeTensor(4270, 6434, 4272, 1318);
  g->Dequantize(1318, 1319, 0.02362205646932125, 0);
  g->Transpose(6675, 4286, {1,0});
  g->Binary(ynn_binary_multiply, 4271, 4285, 4283);
  g->Dot(1317, 4286, YNN_INVALID_VALUE_ID, 4282, 1);
  g->DequantizeTensor(4282, YNN_INVALID_VALUE_ID, 4283, 4284);
  g->QuantizeTensor(4284, 6434, 4272, 1321);
  g->Dequantize(1321, 1322, 0.02362205646932125, 0);
  g->Polynomial(1322, 5781, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5781, 5782);
  g->Binary(ynn_binary_add, 5782, 5430, 5779);
  g->Binary(ynn_binary_multiply, 1322, 5428, 5780);
  g->Binary(ynn_binary_multiply, 5780, 5779, 1323);
  g->Binary(ynn_binary_multiply, 1319, 1323, 1324);
  g->Quantize(1324, 1325, 0.03297245129942894, 0);
  g->Transpose(6674, 4293, {1,0});
  g->Binary(ynn_binary_multiply, 4290, 4292, 4288);
  g->Dot(1325, 4293, YNN_INVALID_VALUE_ID, 4287, 1);
  g->DequantizeTensor(4287, YNN_INVALID_VALUE_ID, 4288, 4289);
  g->QuantizeTensor(4289, 6434, 4291, 1326);
  g->Dequantize(1326, 1327, 0.034845925867557526, 0);
  g->Unary(ynn_unary_square, 1327, 1328);
  g->Reduce(ynn_reduce_sum, 1328, 5784, {2}, true);
  g->ShapeProduct(1328, 5783, {2});
  g->Binary(ynn_binary_divide, 5784, 5783, 1329);
  g->Binary(ynn_binary_add, 1329, 6469, 1331);
  g->Unary(ynn_unary_rsqrt, 1331, 1332);
  g->Binary(ynn_binary_multiply, 1327, 1332, 1333);
  g->Binary(ynn_binary_multiply, 1333, 6680, 1334);
  g->Binary(ynn_binary_add, 1334, 1310, 1335);
}

// Scope: "Layer18 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(421, 1336, {0,0,18,0}, {-1,-1,1,-1});
  g->Reshape(1336, 1337, {1,1,256});
  g->Unary(ynn_unary_square, 1337, 1338);
  g->Reduce(ynn_reduce_sum, 1338, 5786, {2}, true);
  g->ShapeProduct(1338, 5785, {2});
  g->Binary(ynn_binary_divide, 5786, 5785, 1339);
  g->Binary(ynn_binary_add, 1339, 6469, 1340);
  g->Unary(ynn_unary_rsqrt, 1340, 1341);
  g->Binary(ynn_binary_multiply, 1337, 1341, 1342);
  g->Binary(ynn_binary_multiply, 1342, 7048, 1343);
  g->Binary(ynn_binary_multiply, 7059, 6472, 1344);
  g->Binary(ynn_binary_add, 1343, 1344, 1345);
  g->Binary(ynn_binary_multiply, 1345, 6466, 1346);
  g->Quantize(1335, 1347, 0.18026936054229736, 0);
  g->Transpose(6677, 4300, {1,0});
  g->Binary(ynn_binary_multiply, 4297, 4299, 4295);
  g->Dot(1347, 4300, YNN_INVALID_VALUE_ID, 4294, 1);
  g->DequantizeTensor(4294, YNN_INVALID_VALUE_ID, 4295, 4296);
  g->QuantizeTensor(4296, 6434, 4298, 1348);
  g->Dequantize(1348, 1349, 0.08562992513179779, 0);
  g->Polynomial(1349, 5789, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5789, 5790);
  g->Binary(ynn_binary_add, 5790, 5430, 5787);
  g->Binary(ynn_binary_multiply, 1349, 5428, 5788);
  g->Binary(ynn_binary_multiply, 5788, 5787, 1350);
  g->Binary(ynn_binary_multiply, 1350, 1346, 1352);
  g->Quantize(1352, 1353, 1.4409449100494385, 0);
  g->Transpose(6678, 4312, {1,0});
  g->Binary(ynn_binary_multiply, 4309, 4311, 4307);
  g->Dot(1353, 4312, YNN_INVALID_VALUE_ID, 4306, 1);
  g->DequantizeTensor(4306, YNN_INVALID_VALUE_ID, 4307, 4308);
  g->QuantizeTensor(4308, 6434, 4310, 1354);
  g->Dequantize(1354, 1355, 0.2601272463798523, 0);
  g->Unary(ynn_unary_square, 1355, 1356);
  g->Reduce(ynn_reduce_sum, 1356, 5792, {2}, true);
  g->ShapeProduct(1356, 5791, {2});
  g->Binary(ynn_binary_divide, 5792, 5791, 1357);
  g->Binary(ynn_binary_add, 1357, 6469, 1358);
  g->Unary(ynn_unary_rsqrt, 1358, 1359);
  g->Binary(ynn_binary_multiply, 1355, 1359, 1360);
  g->Binary(ynn_binary_multiply, 1360, 6681, 1361);
  g->Binary(ynn_binary_add, 1335, 1361, 1363);
  g->Binary(ynn_binary_multiply, 1363, 6673, 1364);
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
  g->Quantize(1370, 1371, 0.3205932080745697, 0);
  g->Transpose(6699, 4319, {1,0});
  g->Binary(ynn_binary_multiply, 4316, 4318, 4314);
  g->Dot(1371, 4319, YNN_INVALID_VALUE_ID, 4313, 1);
  g->DequantizeTensor(4313, YNN_INVALID_VALUE_ID, 4314, 4315);
  g->QuantizeTensor(4315, 6434, 4317, 1372);
  g->Dequantize(1372, 1375, 0.4685039222240448, 0);
  g->SplitDim(1375, 1376, 2, {8,512});
  g->Transpose(1376, 1377, {0,2,1,3});
  g->Unary(ynn_unary_square, 1377, 1378);
  g->Reduce(ynn_reduce_sum, 1378, 5800, {3}, true);
  g->ShapeProduct(1378, 5799, {3});
  g->Binary(ynn_binary_divide, 5800, 5799, 1379);
  g->Binary(ynn_binary_add, 1379, 6469, 1380);
  g->Unary(ynn_unary_rsqrt, 1380, 1381);
  g->Binary(ynn_binary_multiply, 1377, 1381, 1382);
  g->Binary(ynn_binary_multiply, 1382, 6698, 1383);
  g->Slice(1383, 1384, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(1383, 1386, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 1386, 1387);
  g->Concat({1387,1384}, 1388, 3);
  g->Binary(ynn_binary_multiply, 1383, 3526, 1389);
  g->Binary(ynn_binary_multiply, 1388, 2, 1390);
  g->Binary(ynn_binary_add, 1389, 1390, 1391);
}

// Scope: "Layer19 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7121, 1392, 0.001091228099539876, 0);
  g->Dequantize(7136, 1393, 0.01785714365541935, 0);
  g->Matmul(1391, 1392, 1394, false, true);
  g->Mask(1394, 6486, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 6486, 5804, {-1}, true);
  g->Binary(ynn_binary_subtract, 6486, 5804, 5801);
  g->Unary(ynn_unary_exp, 5801, 5802);
  g->Reduce(ynn_reduce_sum, 5802, 5805, {-1}, true);
  g->Binary(ynn_binary_divide, 5430, 5805, 5803);
  g->Binary(ynn_binary_multiply, 5802, 5803, 1396);
  g->Matmul(1396, 1393, 1397, false, false);
}

// Scope: "Layer19 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1397, 1398, {0,2,1,3});
  g->FuseDims(1398, 1399, 2, 2);
  g->Quantize(1399, 1400, 0.014886821620166302, 0);
  g->Transpose(6697, 4326, {1,0});
  g->Binary(ynn_binary_multiply, 4323, 4325, 4321);
  g->Dot(1400, 4326, YNN_INVALID_VALUE_ID, 4320, 1);
  g->DequantizeTensor(4320, YNN_INVALID_VALUE_ID, 4321, 4322);
  g->QuantizeTensor(4322, 6434, 4324, 1401);
  g->Dequantize(1401, 1402, 0.01861305721104145, 0);
}

// Scope: "Layer19 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1364, 1365);
  g->Reduce(ynn_reduce_sum, 1365, 5794, {2}, true);
  g->ShapeProduct(1365, 5793, {2});
  g->Binary(ynn_binary_divide, 5794, 5793, 1366);
  g->Binary(ynn_binary_add, 1366, 6469, 1367);
  g->Unary(ynn_unary_rsqrt, 1367, 1368);
  g->Binary(ynn_binary_multiply, 1364, 1368, 1369);
  g->Binary(ynn_binary_multiply, 1369, 6686, 1370);
  BuildLayer19AttentionQueryProjection(ctx);
  BuildLayer19AttentionSdpa(ctx);
  BuildLayer19AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1402, 1403);
  g->Reduce(ynn_reduce_sum, 1403, 5807, {2}, true);
  g->ShapeProduct(1403, 5806, {2});
  g->Binary(ynn_binary_divide, 5807, 5806, 1404);
  g->Binary(ynn_binary_add, 1404, 6469, 1405);
  g->Unary(ynn_unary_rsqrt, 1405, 1407);
  g->Binary(ynn_binary_multiply, 1402, 1407, 1408);
  g->Binary(ynn_binary_multiply, 1408, 6693, 1409);
  g->Binary(ynn_binary_add, 1409, 1364, 1410);
}

// Scope: "Layer19 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1410, 1411);
  g->Reduce(ynn_reduce_sum, 1411, 5809, {2}, true);
  g->ShapeProduct(1411, 5808, {2});
  g->Binary(ynn_binary_divide, 5809, 5808, 1412);
  g->Binary(ynn_binary_add, 1412, 6469, 1413);
  g->Unary(ynn_unary_rsqrt, 1413, 1414);
  g->Binary(ynn_binary_multiply, 1410, 1414, 1415);
  g->Binary(ynn_binary_multiply, 1415, 6696, 1416);
  g->Quantize(1416, 1418, 0.019887126982212067, 0);
  g->Transpose(6690, 4340, {1,0});
  g->Binary(ynn_binary_multiply, 4337, 4339, 4335);
  g->Dot(1418, 4340, YNN_INVALID_VALUE_ID, 4334, 1);
  g->DequantizeTensor(4334, YNN_INVALID_VALUE_ID, 4335, 4336);
  g->QuantizeTensor(4336, 6434, 4338, 1419);
  g->Dequantize(1419, 1420, 0.022637804970145226, 0);
  g->Transpose(6689, 4345, {1,0});
  g->Binary(ynn_binary_multiply, 4337, 4344, 4342);
  g->Dot(1418, 4345, YNN_INVALID_VALUE_ID, 4341, 1);
  g->DequantizeTensor(4341, YNN_INVALID_VALUE_ID, 4342, 4343);
  g->QuantizeTensor(4343, 6434, 4338, 1421);
  g->Dequantize(1421, 1422, 0.022637804970145226, 0);
  g->Polynomial(1422, 5812, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5812, 5813);
  g->Binary(ynn_binary_add, 5813, 5430, 5810);
  g->Binary(ynn_binary_multiply, 1422, 5428, 5811);
  g->Binary(ynn_binary_multiply, 5811, 5810, 1423);
  g->Binary(ynn_binary_multiply, 1420, 1423, 1424);
  g->Quantize(1424, 1425, 0.019808080047369003, 0);
  g->Transpose(6688, 4352, {1,0});
  g->Binary(ynn_binary_multiply, 4349, 4351, 4347);
  g->Dot(1425, 4352, YNN_INVALID_VALUE_ID, 4346, 1);
  g->DequantizeTensor(4346, YNN_INVALID_VALUE_ID, 4347, 4348);
  g->QuantizeTensor(4348, 6434, 4350, 1426);
  g->Dequantize(1426, 1428, 0.014754860661923885, 0);
  g->Unary(ynn_unary_square, 1428, 1429);
  g->Reduce(ynn_reduce_sum, 1429, 5815, {2}, true);
  g->ShapeProduct(1429, 5814, {2});
  g->Binary(ynn_binary_divide, 5815, 5814, 1430);
  g->Binary(ynn_binary_add, 1430, 6469, 1431);
  g->Unary(ynn_unary_rsqrt, 1431, 1432);
  g->Binary(ynn_binary_multiply, 1428, 1432, 1433);
  g->Binary(ynn_binary_multiply, 1433, 6694, 1434);
  g->Binary(ynn_binary_add, 1434, 1410, 1435);
}

// Scope: "Layer19 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(421, 1436, {0,0,19,0}, {-1,-1,1,-1});
  g->Reshape(1436, 1437, {1,1,256});
  g->Unary(ynn_unary_square, 1437, 1439);
  g->Reduce(ynn_reduce_sum, 1439, 5819, {2}, true);
  g->ShapeProduct(1439, 5818, {2});
  g->Binary(ynn_binary_divide, 5819, 5818, 1440);
  g->Binary(ynn_binary_add, 1440, 6469, 1441);
  g->Unary(ynn_unary_rsqrt, 1441, 1442);
  g->Binary(ynn_binary_multiply, 1437, 1442, 1443);
  g->Binary(ynn_binary_multiply, 1443, 7048, 1444);
  g->Binary(ynn_binary_multiply, 7060, 6472, 1445);
  g->Binary(ynn_binary_add, 1444, 1445, 1446);
  g->Binary(ynn_binary_multiply, 1446, 6466, 1447);
  g->Quantize(1435, 1448, 0.18873928487300873, 0);
  g->Transpose(6691, 4358, {1,0});
  g->Binary(ynn_binary_multiply, 4356, 4357, 4354);
  g->Dot(1448, 4358, YNN_INVALID_VALUE_ID, 4353, 1);
  g->DequantizeTensor(4353, YNN_INVALID_VALUE_ID, 4354, 4355);
  g->QuantizeTensor(4355, 6434, 3921, 1450);
  g->Dequantize(1450, 1451, 0.08070866763591766, 0);
  g->Polynomial(1451, 5822, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5822, 5823);
  g->Binary(ynn_binary_add, 5823, 5430, 5820);
  g->Binary(ynn_binary_multiply, 1451, 5428, 5821);
  g->Binary(ynn_binary_multiply, 5821, 5820, 1452);
  g->Binary(ynn_binary_multiply, 1452, 1447, 1453);
  g->Quantize(1453, 1454, 0.3858267664909363, 0);
  g->Transpose(6692, 4365, {1,0});
  g->Binary(ynn_binary_multiply, 4362, 4364, 4360);
  g->Dot(1454, 4365, YNN_INVALID_VALUE_ID, 4359, 1);
  g->DequantizeTensor(4359, YNN_INVALID_VALUE_ID, 4360, 4361);
  g->QuantizeTensor(4361, 6434, 4363, 1455);
  g->Dequantize(1455, 1456, 0.16572551429271698, 0);
  g->Unary(ynn_unary_square, 1456, 1457);
  g->Reduce(ynn_reduce_sum, 1457, 5825, {2}, true);
  g->ShapeProduct(1457, 5824, {2});
  g->Binary(ynn_binary_divide, 5825, 5824, 1458);
  g->Binary(ynn_binary_add, 1458, 6469, 1459);
  g->Unary(ynn_unary_rsqrt, 1459, 1461);
  g->Binary(ynn_binary_multiply, 1456, 1461, 1462);
  g->Binary(ynn_binary_multiply, 1462, 6695, 1463);
  g->Binary(ynn_binary_add, 1435, 1463, 1464);
  g->Binary(ynn_binary_multiply, 1464, 6687, 1465);
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
  g->Quantize(1472, 1473, 0.3106735646724701, 0);
  g->Transpose(6730, 4372, {1,0});
  g->Binary(ynn_binary_multiply, 4369, 4371, 4367);
  g->Dot(1473, 4372, YNN_INVALID_VALUE_ID, 4366, 1);
  g->DequantizeTensor(4366, YNN_INVALID_VALUE_ID, 4367, 4368);
  g->QuantizeTensor(4368, 6434, 4370, 1474);
  g->Dequantize(1474, 1475, 0.36614173650741577, 0);
  g->SplitDim(1475, 1476, 2, {8,256});
  g->Transpose(1476, 1477, {0,2,1,3});
  g->Unary(ynn_unary_square, 1477, 1478);
  g->Reduce(ynn_reduce_sum, 1478, 5829, {3}, true);
  g->ShapeProduct(1478, 5828, {3});
  g->Binary(ynn_binary_divide, 5829, 5828, 1479);
  g->Binary(ynn_binary_add, 1479, 6469, 1480);
  g->Unary(ynn_unary_rsqrt, 1480, 1481);
  g->Binary(ynn_binary_multiply, 1477, 1481, 1484);
  g->Binary(ynn_binary_multiply, 1484, 6729, 1485);
  g->Slice(1485, 1486, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1485, 1487, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1487, 1488);
  g->Concat({1488,1486}, 1489, 3);
  g->Binary(ynn_binary_multiply, 1485, 3009, 1490);
  g->Binary(ynn_binary_multiply, 1489, 3112, 1491);
  g->Binary(ynn_binary_add, 1490, 1491, 1492);
}

// Scope: "Layer20 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7120, 1493, 0.0059552486054599285, 0);
  g->Dequantize(7135, 1495, 0.047244105488061905, 0);
  g->Matmul(1492, 1493, 1496, false, true);
  g->Mask(1496, 6488, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6488, 5833, {-1}, true);
  g->Binary(ynn_binary_subtract, 6488, 5833, 5830);
  g->Unary(ynn_unary_exp, 5830, 5831);
  g->Reduce(ynn_reduce_sum, 5831, 5834, {-1}, true);
  g->Binary(ynn_binary_divide, 5430, 5834, 5832);
  g->Binary(ynn_binary_multiply, 5831, 5832, 1497);
  g->Matmul(1497, 1495, 1498, false, false);
}

// Scope: "Layer20 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1498, 1499, {0,2,1,3});
  g->FuseDims(1499, 1500, 2, 2);
  g->Quantize(1500, 1501, 0.02436024509370327, 0);
  g->Transpose(6728, 4378, {1,0});
  g->Binary(ynn_binary_multiply, 4109, 4377, 4374);
  g->Dot(1501, 4378, YNN_INVALID_VALUE_ID, 4373, 1);
  g->DequantizeTensor(4373, YNN_INVALID_VALUE_ID, 4374, 4375);
  g->QuantizeTensor(4375, 6434, 4376, 1502);
  g->Dequantize(1502, 1503, 0.035965267568826675, 0);
}

// Scope: "Layer20 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1465, 1466);
  g->Reduce(ynn_reduce_sum, 1466, 5827, {2}, true);
  g->ShapeProduct(1466, 5826, {2});
  g->Binary(ynn_binary_divide, 5827, 5826, 1467);
  g->Binary(ynn_binary_add, 1467, 6469, 1468);
  g->Unary(ynn_unary_rsqrt, 1468, 1469);
  g->Binary(ynn_binary_multiply, 1465, 1469, 1470);
  g->Binary(ynn_binary_multiply, 1470, 6717, 1472);
  BuildLayer20AttentionQueryProjection(ctx);
  BuildLayer20AttentionSdpa(ctx);
  BuildLayer20AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1503, 1505);
  g->Reduce(ynn_reduce_sum, 1505, 5836, {2}, true);
  g->ShapeProduct(1505, 5835, {2});
  g->Binary(ynn_binary_divide, 5836, 5835, 1506);
  g->Binary(ynn_binary_add, 1506, 6469, 1507);
  g->Unary(ynn_unary_rsqrt, 1507, 1508);
  g->Binary(ynn_binary_multiply, 1503, 1508, 1509);
  g->Binary(ynn_binary_multiply, 1509, 6724, 1510);
  g->Binary(ynn_binary_add, 1510, 1465, 1511);
}

// Scope: "Layer20 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1511, 1512);
  g->Reduce(ynn_reduce_sum, 1512, 5838, {2}, true);
  g->ShapeProduct(1512, 5837, {2});
  g->Binary(ynn_binary_divide, 5838, 5837, 1513);
  g->Binary(ynn_binary_add, 1513, 6469, 1514);
  g->Unary(ynn_unary_rsqrt, 1514, 1516);
  g->Binary(ynn_binary_multiply, 1511, 1516, 1517);
  g->Binary(ynn_binary_multiply, 1517, 6727, 1518);
  g->Quantize(1518, 1519, 0.021377958357334137, 0);
  g->Transpose(6721, 4385, {1,0});
  g->Binary(ynn_binary_multiply, 4382, 4384, 4380);
  g->Dot(1519, 4385, YNN_INVALID_VALUE_ID, 4379, 1);
  g->DequantizeTensor(4379, YNN_INVALID_VALUE_ID, 4380, 4381);
  g->QuantizeTensor(4381, 6434, 4383, 1520);
  g->Dequantize(1520, 1521, 0.02276083640754223, 0);
  g->Transpose(6720, 4390, {1,0});
  g->Binary(ynn_binary_multiply, 4382, 4389, 4387);
  g->Dot(1519, 4390, YNN_INVALID_VALUE_ID, 4386, 1);
  g->DequantizeTensor(4386, YNN_INVALID_VALUE_ID, 4387, 4388);
  g->QuantizeTensor(4388, 6434, 4383, 1522);
  g->Dequantize(1522, 1523, 0.02276083640754223, 0);
  g->Polynomial(1523, 5841, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5841, 5842);
  g->Binary(ynn_binary_add, 5842, 5430, 5839);
  g->Binary(ynn_binary_multiply, 1523, 5428, 5840);
  g->Binary(ynn_binary_multiply, 5840, 5839, 1524);
  g->Binary(ynn_binary_multiply, 1521, 1524, 1526);
  g->Quantize(1526, 1527, 0.026574812829494476, 0);
  g->Transpose(6719, 4397, {1,0});
  g->Binary(ynn_binary_multiply, 4394, 4396, 4392);
  g->Dot(1527, 4397, YNN_INVALID_VALUE_ID, 4391, 1);
  g->DequantizeTensor(4391, YNN_INVALID_VALUE_ID, 4392, 4393);
  g->QuantizeTensor(4393, 6434, 4395, 1528);
  g->Dequantize(1528, 1529, 0.028310857713222504, 0);
  g->Unary(ynn_unary_square, 1529, 1530);
  g->Reduce(ynn_reduce_sum, 1530, 5844, {2}, true);
  g->ShapeProduct(1530, 5843, {2});
  g->Binary(ynn_binary_divide, 5844, 5843, 1531);
  g->Binary(ynn_binary_add, 1531, 6469, 1532);
  g->Unary(ynn_unary_rsqrt, 1532, 1533);
  g->Binary(ynn_binary_multiply, 1529, 1533, 1534);
  g->Binary(ynn_binary_multiply, 1534, 6725, 1535);
  g->Binary(ynn_binary_add, 1535, 1511, 1537);
}

// Scope: "Layer20 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(421, 1538, {0,0,20,0}, {-1,-1,1,-1});
  g->Reshape(1538, 1539, {1,1,256});
  g->Unary(ynn_unary_square, 1539, 1540);
  g->Reduce(ynn_reduce_sum, 1540, 5848, {2}, true);
  g->ShapeProduct(1540, 5847, {2});
  g->Binary(ynn_binary_divide, 5848, 5847, 1541);
  g->Binary(ynn_binary_add, 1541, 6469, 1542);
  g->Unary(ynn_unary_rsqrt, 1542, 1543);
  g->Binary(ynn_binary_multiply, 1539, 1543, 1544);
  g->Binary(ynn_binary_multiply, 1544, 7048, 1545);
  g->Binary(ynn_binary_multiply, 7062, 6472, 1546);
  g->Binary(ynn_binary_add, 1545, 1546, 1548);
  g->Binary(ynn_binary_multiply, 1548, 6466, 1549);
  g->Quantize(1537, 1550, 0.17634929716587067, 0);
  g->Transpose(6722, 4404, {1,0});
  g->Binary(ynn_binary_multiply, 4401, 4403, 4399);
  g->Dot(1550, 4404, YNN_INVALID_VALUE_ID, 4398, 1);
  g->DequantizeTensor(4398, YNN_INVALID_VALUE_ID, 4399, 4400);
  g->QuantizeTensor(4400, 6434, 4402, 1551);
  g->Dequantize(1551, 1552, 0.059055130928754807, 0);
  g->Polynomial(1552, 5851, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5851, 5852);
  g->Binary(ynn_binary_add, 5852, 5430, 5849);
  g->Binary(ynn_binary_multiply, 1552, 5428, 5850);
  g->Binary(ynn_binary_multiply, 5850, 5849, 1553);
  g->Binary(ynn_binary_multiply, 1553, 1549, 1554);
  g->Quantize(1554, 1555, 0.1998031586408615, 0);
  g->Transpose(6723, 4411, {1,0});
  g->Binary(ynn_binary_multiply, 4408, 4410, 4406);
  g->Dot(1555, 4411, YNN_INVALID_VALUE_ID, 4405, 1);
  g->DequantizeTensor(4405, YNN_INVALID_VALUE_ID, 4406, 4407);
  g->QuantizeTensor(4407, 6434, 4409, 1556);
  g->Dequantize(1556, 1557, 0.07776007056236267, 0);
  g->Unary(ynn_unary_square, 1557, 1559);
  g->Reduce(ynn_reduce_sum, 1559, 5854, {2}, true);
  g->ShapeProduct(1559, 5853, {2});
  g->Binary(ynn_binary_divide, 5854, 5853, 1560);
  g->Binary(ynn_binary_add, 1560, 6469, 1561);
  g->Unary(ynn_unary_rsqrt, 1561, 1562);
  g->Binary(ynn_binary_multiply, 1557, 1562, 1563);
  g->Binary(ynn_binary_multiply, 1563, 6726, 1564);
  g->Binary(ynn_binary_add, 1537, 1564, 1565);
  g->Binary(ynn_binary_multiply, 1565, 6718, 1566);
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
  g->Quantize(1573, 1574, 0.20073647797107697, 0);
  g->Transpose(6744, 4418, {1,0});
  g->Binary(ynn_binary_multiply, 4415, 4417, 4413);
  g->Dot(1574, 4418, YNN_INVALID_VALUE_ID, 4412, 1);
  g->DequantizeTensor(4412, YNN_INVALID_VALUE_ID, 4413, 4414);
  g->QuantizeTensor(4414, 6434, 4416, 1575);
  g->Dequantize(1575, 1576, 0.23622049391269684, 0);
  g->SplitDim(1576, 1577, 2, {8,256});
  g->Transpose(1577, 1578, {0,2,1,3});
  g->Unary(ynn_unary_square, 1578, 1579);
  g->Reduce(ynn_reduce_sum, 1579, 5858, {3}, true);
  g->ShapeProduct(1579, 5857, {3});
  g->Binary(ynn_binary_divide, 5858, 5857, 1581);
  g->Binary(ynn_binary_add, 1581, 6469, 1582);
  g->Unary(ynn_unary_rsqrt, 1582, 1583);
  g->Binary(ynn_binary_multiply, 1578, 1583, 1584);
  g->Binary(ynn_binary_multiply, 1584, 6743, 1585);
  g->Slice(1585, 1586, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1585, 1587, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1587, 1588);
  g->Concat({1588,1586}, 1589, 3);
  g->Binary(ynn_binary_multiply, 1585, 3009, 1590);
  g->Binary(ynn_binary_multiply, 1589, 3112, 1593);
  g->Binary(ynn_binary_add, 1590, 1593, 1594);
}

// Scope: "Layer21 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7120, 1595, 0.0059552486054599285, 0);
  g->Dequantize(7135, 1596, 0.047244105488061905, 0);
  g->Matmul(1594, 1595, 1597, false, true);
  g->Mask(1597, 6489, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6489, 5862, {-1}, true);
  g->Binary(ynn_binary_subtract, 6489, 5862, 5859);
  g->Unary(ynn_unary_exp, 5859, 5860);
  g->Reduce(ynn_reduce_sum, 5860, 5863, {-1}, true);
  g->Binary(ynn_binary_divide, 5430, 5863, 5861);
  g->Binary(ynn_binary_multiply, 5860, 5861, 1598);
  g->Matmul(1598, 1596, 1599, false, false);
}

// Scope: "Layer21 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1599, 1600, {0,2,1,3});
  g->FuseDims(1600, 1601, 2, 2);
  g->Quantize(1601, 1603, 0.025221465155482292, 0);
  g->Transpose(6742, 4425, {1,0});
  g->Binary(ynn_binary_multiply, 4422, 4424, 4420);
  g->Dot(1603, 4425, YNN_INVALID_VALUE_ID, 4419, 1);
  g->DequantizeTensor(4419, YNN_INVALID_VALUE_ID, 4420, 4421);
  g->QuantizeTensor(4421, 6434, 4423, 1604);
  g->Dequantize(1604, 1605, 0.03553423285484314, 0);
}

// Scope: "Layer21 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1566, 1567);
  g->Reduce(ynn_reduce_sum, 1567, 5856, {2}, true);
  g->ShapeProduct(1567, 5855, {2});
  g->Binary(ynn_binary_divide, 5856, 5855, 1568);
  g->Binary(ynn_binary_add, 1568, 6469, 1570);
  g->Unary(ynn_unary_rsqrt, 1570, 1571);
  g->Binary(ynn_binary_multiply, 1566, 1571, 1572);
  g->Binary(ynn_binary_multiply, 1572, 6731, 1573);
  BuildLayer21AttentionQueryProjection(ctx);
  BuildLayer21AttentionSdpa(ctx);
  BuildLayer21AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1605, 1606);
  g->Reduce(ynn_reduce_sum, 1606, 5865, {2}, true);
  g->ShapeProduct(1606, 5864, {2});
  g->Binary(ynn_binary_divide, 5865, 5864, 1607);
  g->Binary(ynn_binary_add, 1607, 6469, 1608);
  g->Unary(ynn_unary_rsqrt, 1608, 1609);
  g->Binary(ynn_binary_multiply, 1605, 1609, 1610);
  g->Binary(ynn_binary_multiply, 1610, 6738, 1611);
  g->Binary(ynn_binary_add, 1611, 1566, 1612);
}

// Scope: "Layer21 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1612, 1614);
  g->Reduce(ynn_reduce_sum, 1614, 5867, {2}, true);
  g->ShapeProduct(1614, 5866, {2});
  g->Binary(ynn_binary_divide, 5867, 5866, 1615);
  g->Binary(ynn_binary_add, 1615, 6469, 1616);
  g->Unary(ynn_unary_rsqrt, 1616, 1617);
  g->Binary(ynn_binary_multiply, 1612, 1617, 1618);
  g->Binary(ynn_binary_multiply, 1618, 6741, 1619);
  g->Quantize(1619, 1620, 0.019064493477344513, 0);
  g->Transpose(6735, 4431, {1,0});
  g->Binary(ynn_binary_multiply, 4429, 4430, 4427);
  g->Dot(1620, 4431, YNN_INVALID_VALUE_ID, 4426, 1);
  g->DequantizeTensor(4426, YNN_INVALID_VALUE_ID, 4427, 4428);
  g->QuantizeTensor(4428, 6434, 4272, 1621);
  g->Dequantize(1621, 1622, 0.02362205646932125, 0);
  g->Transpose(6734, 4436, {1,0});
  g->Binary(ynn_binary_multiply, 4429, 4435, 4433);
  g->Dot(1620, 4436, YNN_INVALID_VALUE_ID, 4432, 1);
  g->DequantizeTensor(4432, YNN_INVALID_VALUE_ID, 4433, 4434);
  g->QuantizeTensor(4434, 6434, 4272, 1624);
  g->Dequantize(1624, 1625, 0.02362205646932125, 0);
  g->Polynomial(1625, 5870, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5870, 5871);
  g->Binary(ynn_binary_add, 5871, 5430, 5868);
  g->Binary(ynn_binary_multiply, 1625, 5428, 5869);
  g->Binary(ynn_binary_multiply, 5869, 5868, 1626);
  g->Binary(ynn_binary_multiply, 1622, 1626, 1627);
  g->Quantize(1627, 1628, 0.030019694939255714, 0);
  g->Transpose(6733, 4443, {1,0});
  g->Binary(ynn_binary_multiply, 4440, 4442, 4438);
  g->Dot(1628, 4443, YNN_INVALID_VALUE_ID, 4437, 1);
  g->DequantizeTensor(4437, YNN_INVALID_VALUE_ID, 4438, 4439);
  g->QuantizeTensor(4439, 6434, 4441, 1629);
  g->Dequantize(1629, 1630, 0.03767223656177521, 0);
  g->Unary(ynn_unary_square, 1630, 1631);
  g->Reduce(ynn_reduce_sum, 1631, 5873, {2}, true);
  g->ShapeProduct(1631, 5872, {2});
  g->Binary(ynn_binary_divide, 5873, 5872, 1632);
  g->Binary(ynn_binary_add, 1632, 6469, 1633);
  g->Unary(ynn_unary_rsqrt, 1633, 1635);
  g->Binary(ynn_binary_multiply, 1630, 1635, 1636);
  g->Binary(ynn_binary_multiply, 1636, 6739, 1637);
  g->Binary(ynn_binary_add, 1637, 1612, 1638);
}

// Scope: "Layer21 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(421, 1639, {0,0,21,0}, {-1,-1,1,-1});
  g->Reshape(1639, 1640, {1,1,256});
  g->Unary(ynn_unary_square, 1640, 1641);
  g->Reduce(ynn_reduce_sum, 1641, 5875, {2}, true);
  g->ShapeProduct(1641, 5874, {2});
  g->Binary(ynn_binary_divide, 5875, 5874, 1642);
  g->Binary(ynn_binary_add, 1642, 6469, 1643);
  g->Unary(ynn_unary_rsqrt, 1643, 1644);
  g->Binary(ynn_binary_multiply, 1640, 1644, 1646);
  g->Binary(ynn_binary_multiply, 1646, 7048, 1647);
  g->Binary(ynn_binary_multiply, 7063, 6472, 1648);
  g->Binary(ynn_binary_add, 1647, 1648, 1649);
  g->Binary(ynn_binary_multiply, 1649, 6466, 1650);
  g->Quantize(1638, 1651, 0.14814288914203644, 0);
  g->Transpose(6736, 4457, {1,0});
  g->Binary(ynn_binary_multiply, 4454, 4456, 4452);
  g->Dot(1651, 4457, YNN_INVALID_VALUE_ID, 4451, 1);
  g->DequantizeTensor(4451, YNN_INVALID_VALUE_ID, 4452, 4453);
  g->QuantizeTensor(4453, 6434, 4455, 1652);
  g->Dequantize(1652, 1653, 0.047244105488061905, 0);
  g->Polynomial(1653, 5878, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5878, 5879);
  g->Binary(ynn_binary_add, 5879, 5430, 5876);
  g->Binary(ynn_binary_multiply, 1653, 5428, 5877);
  g->Binary(ynn_binary_multiply, 5877, 5876, 1654);
  g->Binary(ynn_binary_multiply, 1654, 1650, 1655);
  g->Quantize(1655, 1657, 0.10531497001647949, 0);
  g->Transpose(6737, 4464, {1,0});
  g->Binary(ynn_binary_multiply, 4461, 4463, 4459);
  g->Dot(1657, 4464, YNN_INVALID_VALUE_ID, 4458, 1);
  g->DequantizeTensor(4458, YNN_INVALID_VALUE_ID, 4459, 4460);
  g->QuantizeTensor(4460, 6434, 4462, 1658);
  g->Dequantize(1658, 1659, 0.061565153300762177, 0);
  g->Unary(ynn_unary_square, 1659, 1660);
  g->Reduce(ynn_reduce_sum, 1660, 5885, {2}, true);
  g->ShapeProduct(1660, 5884, {2});
  g->Binary(ynn_binary_divide, 5885, 5884, 1661);
  g->Binary(ynn_binary_add, 1661, 6469, 1662);
  g->Unary(ynn_unary_rsqrt, 1662, 1663);
  g->Binary(ynn_binary_multiply, 1659, 1663, 1664);
  g->Binary(ynn_binary_multiply, 1664, 6740, 1665);
  g->Binary(ynn_binary_add, 1638, 1665, 1666);
  g->Binary(ynn_binary_multiply, 1666, 6732, 1668);
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
  g->Quantize(1674, 1675, 0.21987482905387878, 0);
  g->Transpose(6758, 4471, {1,0});
  g->Binary(ynn_binary_multiply, 4468, 4470, 4466);
  g->Dot(1675, 4471, YNN_INVALID_VALUE_ID, 4465, 1);
  g->DequantizeTensor(4465, YNN_INVALID_VALUE_ID, 4466, 4467);
  g->QuantizeTensor(4467, 6434, 4469, 1676);
  g->Dequantize(1676, 1677, 0.19685040414333344, 0);
  g->SplitDim(1677, 1679, 2, {8,256});
  g->Transpose(1679, 1680, {0,2,1,3});
  g->Unary(ynn_unary_square, 1680, 1681);
  g->Reduce(ynn_reduce_sum, 1681, 5889, {3}, true);
  g->ShapeProduct(1681, 5888, {3});
  g->Binary(ynn_binary_divide, 5889, 5888, 1682);
  g->Binary(ynn_binary_add, 1682, 6469, 1683);
  g->Unary(ynn_unary_rsqrt, 1683, 1684);
  g->Binary(ynn_binary_multiply, 1680, 1684, 1685);
  g->Binary(ynn_binary_multiply, 1685, 6757, 1686);
  g->Slice(1686, 1687, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1686, 1688, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1688, 1690);
  g->Concat({1690,1687}, 1691, 3);
  g->Binary(ynn_binary_multiply, 1686, 3009, 1692);
  g->Binary(ynn_binary_multiply, 1691, 3112, 1693);
  g->Binary(ynn_binary_add, 1692, 1693, 1694);
}

// Scope: "Layer22 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7120, 1695, 0.0059552486054599285, 0);
  g->Dequantize(7135, 1696, 0.047244105488061905, 0);
  g->Matmul(1694, 1695, 1697, false, true);
  g->Mask(1697, 6490, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6490, 5893, {-1}, true);
  g->Binary(ynn_binary_subtract, 6490, 5893, 5890);
  g->Unary(ynn_unary_exp, 5890, 5891);
  g->Reduce(ynn_reduce_sum, 5891, 5894, {-1}, true);
  g->Binary(ynn_binary_divide, 5430, 5894, 5892);
  g->Binary(ynn_binary_multiply, 5891, 5892, 1698);
  g->Matmul(1698, 1696, 1701, false, false);
}

// Scope: "Layer22 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1701, 1702, {0,2,1,3});
  g->FuseDims(1702, 1703, 2, 2);
  g->Quantize(1703, 1704, 0.023868119344115257, 0);
  g->Transpose(6756, 4485, {1,0});
  g->Binary(ynn_binary_multiply, 4482, 4484, 4480);
  g->Dot(1704, 4485, YNN_INVALID_VALUE_ID, 4479, 1);
  g->DequantizeTensor(4479, YNN_INVALID_VALUE_ID, 4480, 4481);
  g->QuantizeTensor(4481, 6434, 4483, 1705);
  g->Dequantize(1705, 1706, 0.047558318823575974, 0);
}

// Scope: "Layer22 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1668, 1669);
  g->Reduce(ynn_reduce_sum, 1669, 5887, {2}, true);
  g->ShapeProduct(1669, 5886, {2});
  g->Binary(ynn_binary_divide, 5887, 5886, 1670);
  g->Binary(ynn_binary_add, 1670, 6469, 1671);
  g->Unary(ynn_unary_rsqrt, 1671, 1672);
  g->Binary(ynn_binary_multiply, 1668, 1672, 1673);
  g->Binary(ynn_binary_multiply, 1673, 6745, 1674);
  BuildLayer22AttentionQueryProjection(ctx);
  BuildLayer22AttentionSdpa(ctx);
  BuildLayer22AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1706, 1707);
  g->Reduce(ynn_reduce_sum, 1707, 5896, {2}, true);
  g->ShapeProduct(1707, 5895, {2});
  g->Binary(ynn_binary_divide, 5896, 5895, 1708);
  g->Binary(ynn_binary_add, 1708, 6469, 1709);
  g->Unary(ynn_unary_rsqrt, 1709, 1710);
  g->Binary(ynn_binary_multiply, 1706, 1710, 1712);
  g->Binary(ynn_binary_multiply, 1712, 6752, 1713);
  g->Binary(ynn_binary_add, 1713, 1668, 1714);
}

// Scope: "Layer22 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1714, 1715);
  g->Reduce(ynn_reduce_sum, 1715, 5898, {2}, true);
  g->ShapeProduct(1715, 5897, {2});
  g->Binary(ynn_binary_divide, 5898, 5897, 1716);
  g->Binary(ynn_binary_add, 1716, 6469, 1717);
  g->Unary(ynn_unary_rsqrt, 1717, 1718);
  g->Binary(ynn_binary_multiply, 1714, 1718, 1719);
  g->Binary(ynn_binary_multiply, 1719, 6755, 1720);
  g->Quantize(1720, 1721, 0.019696271046996117, 0);
  g->Transpose(6749, 4492, {1,0});
  g->Binary(ynn_binary_multiply, 4489, 4491, 4487);
  g->Dot(1721, 4492, YNN_INVALID_VALUE_ID, 4486, 1);
  g->DequantizeTensor(4486, YNN_INVALID_VALUE_ID, 4487, 4488);
  g->QuantizeTensor(4488, 6434, 4490, 1723);
  g->Dequantize(1723, 1724, 0.024114182218909264, 0);
  g->Transpose(6748, 4497, {1,0});
  g->Binary(ynn_binary_multiply, 4489, 4496, 4494);
  g->Dot(1721, 4497, YNN_INVALID_VALUE_ID, 4493, 1);
  g->DequantizeTensor(4493, YNN_INVALID_VALUE_ID, 4494, 4495);
  g->QuantizeTensor(4495, 6434, 4490, 1725);
  g->Dequantize(1725, 1726, 0.024114182218909264, 0);
  g->Polynomial(1726, 5903, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5903, 5904);
  g->Binary(ynn_binary_add, 5904, 5430, 5901);
  g->Binary(ynn_binary_multiply, 1726, 5428, 5902);
  g->Binary(ynn_binary_multiply, 5902, 5901, 1727);
  g->Binary(ynn_binary_multiply, 1724, 1727, 1728);
  g->Quantize(1728, 1729, 0.03567914664745331, 0);
  g->Transpose(6747, 4504, {1,0});
  g->Binary(ynn_binary_multiply, 4501, 4503, 4499);
  g->Dot(1729, 4504, YNN_INVALID_VALUE_ID, 4498, 1);
  g->DequantizeTensor(4498, YNN_INVALID_VALUE_ID, 4499, 4500);
  g->QuantizeTensor(4500, 6434, 4502, 1730);
  g->Dequantize(1730, 1731, 0.05007796362042427, 0);
  g->Unary(ynn_unary_square, 1731, 1733);
  g->Reduce(ynn_reduce_sum, 1733, 5906, {2}, true);
  g->ShapeProduct(1733, 5905, {2});
  g->Binary(ynn_binary_divide, 5906, 5905, 1734);
  g->Binary(ynn_binary_add, 1734, 6469, 1735);
  g->Unary(ynn_unary_rsqrt, 1735, 1736);
  g->Binary(ynn_binary_multiply, 1731, 1736, 1737);
  g->Binary(ynn_binary_multiply, 1737, 6753, 1738);
  g->Binary(ynn_binary_add, 1738, 1714, 1739);
}

// Scope: "Layer22 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(421, 1740, {0,0,22,0}, {-1,-1,1,-1});
  g->Reshape(1740, 1741, {1,1,256});
  g->Unary(ynn_unary_square, 1741, 1742);
  g->Reduce(ynn_reduce_sum, 1742, 5908, {2}, true);
  g->ShapeProduct(1742, 5907, {2});
  g->Binary(ynn_binary_divide, 5908, 5907, 1744);
  g->Binary(ynn_binary_add, 1744, 6469, 1745);
  g->Unary(ynn_unary_rsqrt, 1745, 1746);
  g->Binary(ynn_binary_multiply, 1741, 1746, 1747);
  g->Binary(ynn_binary_multiply, 1747, 7048, 1748);
  g->Binary(ynn_binary_multiply, 7064, 6472, 1749);
  g->Binary(ynn_binary_add, 1748, 1749, 1750);
  g->Binary(ynn_binary_multiply, 1750, 6466, 1751);
  g->Quantize(1739, 1752, 0.15015320479869843, 0);
  g->Transpose(6750, 4511, {1,0});
  g->Binary(ynn_binary_multiply, 4508, 4510, 4506);
  g->Dot(1752, 4511, YNN_INVALID_VALUE_ID, 4505, 1);
  g->DequantizeTensor(4505, YNN_INVALID_VALUE_ID, 4506, 4507);
  g->QuantizeTensor(4507, 6434, 4509, 1753);
  g->Dequantize(1753, 1755, 0.06102363392710686, 0);
  g->Polynomial(1755, 5911, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5911, 5912);
  g->Binary(ynn_binary_add, 5912, 5430, 5909);
  g->Binary(ynn_binary_multiply, 1755, 5428, 5910);
  g->Binary(ynn_binary_multiply, 5910, 5909, 1756);
  g->Binary(ynn_binary_multiply, 1756, 1751, 1757);
  g->Quantize(1757, 1758, 0.3779527544975281, 0);
  g->Transpose(6751, 4518, {1,0});
  g->Binary(ynn_binary_multiply, 4515, 4517, 4513);
  g->Dot(1758, 4518, YNN_INVALID_VALUE_ID, 4512, 1);
  g->DequantizeTensor(4512, YNN_INVALID_VALUE_ID, 4513, 4514);
  g->QuantizeTensor(4514, 6434, 4516, 1759);
  g->Dequantize(1759, 1760, 0.11902644485235214, 0);
  g->Unary(ynn_unary_square, 1760, 1761);
  g->Reduce(ynn_reduce_sum, 1761, 5914, {2}, true);
  g->ShapeProduct(1761, 5913, {2});
  g->Binary(ynn_binary_divide, 5914, 5913, 1762);
  g->Binary(ynn_binary_add, 1762, 6469, 1763);
  g->Unary(ynn_unary_rsqrt, 1763, 1764);
  g->Binary(ynn_binary_multiply, 1760, 1764, 1766);
  g->Binary(ynn_binary_multiply, 1766, 6754, 1767);
  g->Binary(ynn_binary_add, 1739, 1767, 1768);
  g->Binary(ynn_binary_multiply, 1768, 6746, 1769);
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
  g->Quantize(1775, 1777, 0.17847737669944763, 0);
  g->Transpose(6772, 4525, {1,0});
  g->Binary(ynn_binary_multiply, 4522, 4524, 4520);
  g->Dot(1777, 4525, YNN_INVALID_VALUE_ID, 4519, 1);
  g->DequantizeTensor(4519, YNN_INVALID_VALUE_ID, 4520, 4521);
  g->QuantizeTensor(4521, 6434, 4523, 1778);
  g->Dequantize(1778, 1779, 0.16338583827018738, 0);
  g->SplitDim(1779, 1780, 2, {8,256});
  g->Transpose(1780, 1781, {0,2,1,3});
  g->Unary(ynn_unary_square, 1781, 1782);
  g->Reduce(ynn_reduce_sum, 1782, 5918, {3}, true);
  g->ShapeProduct(1782, 5917, {3});
  g->Binary(ynn_binary_divide, 5918, 5917, 1783);
  g->Binary(ynn_binary_add, 1783, 6469, 1784);
  g->Unary(ynn_unary_rsqrt, 1784, 1785);
  g->Binary(ynn_binary_multiply, 1781, 1785, 1786);
  g->Binary(ynn_binary_multiply, 1786, 6771, 1788);
  g->Slice(1788, 1789, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1788, 1790, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1790, 1791);
  g->Concat({1791,1789}, 1792, 3);
  g->Binary(ynn_binary_multiply, 1788, 3009, 1793);
  g->Binary(ynn_binary_multiply, 1792, 3112, 1794);
  g->Binary(ynn_binary_add, 1793, 1794, 1795);
}

// Scope: "Layer23 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7120, 1796, 0.0059552486054599285, 0);
  g->Dequantize(7135, 1797, 0.047244105488061905, 0);
  g->Matmul(1795, 1796, 1799, false, true);
  g->Mask(1799, 6491, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6491, 5922, {-1}, true);
  g->Binary(ynn_binary_subtract, 6491, 5922, 5919);
  g->Unary(ynn_unary_exp, 5919, 5920);
  g->Reduce(ynn_reduce_sum, 5920, 5923, {-1}, true);
  g->Binary(ynn_binary_divide, 5430, 5923, 5921);
  g->Binary(ynn_binary_multiply, 5920, 5921, 1800);
  g->Matmul(1800, 1797, 1801, false, false);
}

// Scope: "Layer23 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1801, 1802, {0,2,1,3});
  g->FuseDims(1802, 1803, 2, 2);
  g->Quantize(1803, 1804, 0.02436024509370327, 0);
  g->Transpose(6770, 4531, {1,0});
  g->Binary(ynn_binary_multiply, 4109, 4530, 4527);
  g->Dot(1804, 4531, YNN_INVALID_VALUE_ID, 4526, 1);
  g->DequantizeTensor(4526, YNN_INVALID_VALUE_ID, 4527, 4528);
  g->QuantizeTensor(4528, 6434, 4529, 1805);
  g->Dequantize(1805, 1806, 0.027484547346830368, 0);
}

// Scope: "Layer23 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1769, 1770);
  g->Reduce(ynn_reduce_sum, 1770, 5916, {2}, true);
  g->ShapeProduct(1770, 5915, {2});
  g->Binary(ynn_binary_divide, 5916, 5915, 1771);
  g->Binary(ynn_binary_add, 1771, 6469, 1772);
  g->Unary(ynn_unary_rsqrt, 1772, 1773);
  g->Binary(ynn_binary_multiply, 1769, 1773, 1774);
  g->Binary(ynn_binary_multiply, 1774, 6759, 1775);
  BuildLayer23AttentionQueryProjection(ctx);
  BuildLayer23AttentionSdpa(ctx);
  BuildLayer23AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1806, 1807);
  g->Reduce(ynn_reduce_sum, 1807, 5929, {2}, true);
  g->ShapeProduct(1807, 5928, {2});
  g->Binary(ynn_binary_divide, 5929, 5928, 1810);
  g->Binary(ynn_binary_add, 1810, 6469, 1811);
  g->Unary(ynn_unary_rsqrt, 1811, 1812);
  g->Binary(ynn_binary_multiply, 1806, 1812, 1813);
  g->Binary(ynn_binary_multiply, 1813, 6766, 1814);
  g->Binary(ynn_binary_add, 1814, 1769, 1815);
}

// Scope: "Layer23 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1815, 1816);
  g->Reduce(ynn_reduce_sum, 1816, 5931, {2}, true);
  g->ShapeProduct(1816, 5930, {2});
  g->Binary(ynn_binary_divide, 5931, 5930, 1817);
  g->Binary(ynn_binary_add, 1817, 6469, 1818);
  g->Unary(ynn_unary_rsqrt, 1818, 1819);
  g->Binary(ynn_binary_multiply, 1815, 1819, 1821);
  g->Binary(ynn_binary_multiply, 1821, 6769, 1822);
  g->Quantize(1822, 1823, 0.02338595874607563, 0);
  g->Transpose(6763, 4538, {1,0});
  g->Binary(ynn_binary_multiply, 4535, 4537, 4533);
  g->Dot(1823, 4538, YNN_INVALID_VALUE_ID, 4532, 1);
  g->DequantizeTensor(4532, YNN_INVALID_VALUE_ID, 4533, 4534);
  g->QuantizeTensor(4534, 6434, 4536, 1824);
  g->Dequantize(1824, 1825, 0.03100394643843174, 0);
  g->Transpose(6762, 4543, {1,0});
  g->Binary(ynn_binary_multiply, 4535, 4542, 4540);
  g->Dot(1823, 4543, YNN_INVALID_VALUE_ID, 4539, 1);
  g->DequantizeTensor(4539, YNN_INVALID_VALUE_ID, 4540, 4541);
  g->QuantizeTensor(4541, 6434, 4536, 1826);
  g->Dequantize(1826, 1827, 0.03100394643843174, 0);
  g->Polynomial(1827, 5934, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5934, 5935);
  g->Binary(ynn_binary_add, 5935, 5430, 5932);
  g->Binary(ynn_binary_multiply, 1827, 5428, 5933);
  g->Binary(ynn_binary_multiply, 5933, 5932, 1828);
  g->Binary(ynn_binary_multiply, 1825, 1828, 1829);
  g->Quantize(1829, 1831, 0.0433070994913578, 0);
  g->Transpose(6761, 4550, {1,0});
  g->Binary(ynn_binary_multiply, 4547, 4549, 4545);
  g->Dot(1831, 4550, YNN_INVALID_VALUE_ID, 4544, 1);
  g->DequantizeTensor(4544, YNN_INVALID_VALUE_ID, 4545, 4546);
  g->QuantizeTensor(4546, 6434, 4548, 1832);
  g->Dequantize(1832, 1833, 0.025599855929613113, 0);
  g->Unary(ynn_unary_square, 1833, 1834);
  g->Reduce(ynn_reduce_sum, 1834, 5937, {2}, true);
  g->ShapeProduct(1834, 5936, {2});
  g->Binary(ynn_binary_divide, 5937, 5936, 1835);
  g->Binary(ynn_binary_add, 1835, 6469, 1836);
  g->Unary(ynn_unary_rsqrt, 1836, 1837);
  g->Binary(ynn_binary_multiply, 1833, 1837, 1838);
  g->Binary(ynn_binary_multiply, 1838, 6767, 1839);
  g->Binary(ynn_binary_add, 1839, 1815, 1840);
}

// Scope: "Layer23 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(421, 1842, {0,0,23,0}, {-1,-1,1,-1});
  g->Reshape(1842, 1843, {1,1,256});
  g->Unary(ynn_unary_square, 1843, 1844);
  g->Reduce(ynn_reduce_sum, 1844, 5939, {2}, true);
  g->ShapeProduct(1844, 5938, {2});
  g->Binary(ynn_binary_divide, 5939, 5938, 1845);
  g->Binary(ynn_binary_add, 1845, 6469, 1846);
  g->Unary(ynn_unary_rsqrt, 1846, 1847);
  g->Binary(ynn_binary_multiply, 1843, 1847, 1848);
  g->Binary(ynn_binary_multiply, 1848, 7048, 1849);
  g->Binary(ynn_binary_multiply, 7065, 6472, 1850);
  g->Binary(ynn_binary_add, 1849, 1850, 1851);
  g->Binary(ynn_binary_multiply, 1851, 6466, 1853);
  g->Quantize(1840, 1854, 0.1760360449552536, 0);
  g->Transpose(6764, 4557, {1,0});
  g->Binary(ynn_binary_multiply, 4554, 4556, 4552);
  g->Dot(1854, 4557, YNN_INVALID_VALUE_ID, 4551, 1);
  g->DequantizeTensor(4551, YNN_INVALID_VALUE_ID, 4552, 4553);
  g->QuantizeTensor(4553, 6434, 4555, 1855);
  g->Dequantize(1855, 1856, 0.07775591313838959, 0);
  g->Polynomial(1856, 5942, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5942, 5943);
  g->Binary(ynn_binary_add, 5943, 5430, 5940);
  g->Binary(ynn_binary_multiply, 1856, 5428, 5941);
  g->Binary(ynn_binary_multiply, 5941, 5940, 1857);
  g->Binary(ynn_binary_multiply, 1857, 1853, 1858);
  g->Quantize(1858, 1859, 0.3799212574958801, 0);
  g->Transpose(6765, 4564, {1,0});
  g->Binary(ynn_binary_multiply, 4561, 4563, 4559);
  g->Dot(1859, 4564, YNN_INVALID_VALUE_ID, 4558, 1);
  g->DequantizeTensor(4558, YNN_INVALID_VALUE_ID, 4559, 4560);
  g->QuantizeTensor(4560, 6434, 4562, 1860);
  g->Dequantize(1860, 1861, 0.08570276200771332, 0);
  g->Unary(ynn_unary_square, 1861, 1862);
  g->Reduce(ynn_reduce_sum, 1862, 5945, {2}, true);
  g->ShapeProduct(1862, 5944, {2});
  g->Binary(ynn_binary_divide, 5945, 5944, 1864);
  g->Binary(ynn_binary_add, 1864, 6469, 1865);
  g->Unary(ynn_unary_rsqrt, 1865, 1866);
  g->Binary(ynn_binary_multiply, 1861, 1866, 1867);
  g->Binary(ynn_binary_multiply, 1867, 6768, 1868);
  g->Binary(ynn_binary_add, 1840, 1868, 1869);
  g->Binary(ynn_binary_multiply, 1869, 6760, 1870);
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
  g->Quantize(1877, 1878, 0.10295870155096054, 0);
  g->Transpose(6786, 4578, {1,0});
  g->Binary(ynn_binary_multiply, 4575, 4577, 4573);
  g->Dot(1878, 4578, YNN_INVALID_VALUE_ID, 4572, 1);
  g->DequantizeTensor(4572, YNN_INVALID_VALUE_ID, 4573, 4574);
  g->QuantizeTensor(4574, 6434, 4576, 1879);
  g->Dequantize(1879, 1880, 0.1919291466474533, 0);
  g->SplitDim(1880, 1881, 2, {8,512});
  g->Transpose(1881, 1882, {0,2,1,3});
  g->Unary(ynn_unary_square, 1882, 1883);
  g->Reduce(ynn_reduce_sum, 1883, 5949, {3}, true);
  g->ShapeProduct(1883, 5948, {3});
  g->Binary(ynn_binary_divide, 5949, 5948, 1884);
  g->Binary(ynn_binary_add, 1884, 6469, 1886);
  g->Unary(ynn_unary_rsqrt, 1886, 1887);
  g->Binary(ynn_binary_multiply, 1882, 1887, 1888);
  g->Binary(ynn_binary_multiply, 1888, 6785, 1889);
  g->Slice(1889, 1890, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(1889, 1891, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 1891, 1892);
  g->Concat({1892,1890}, 1893, 3);
  g->Binary(ynn_binary_multiply, 1889, 3526, 1894);
  g->Binary(ynn_binary_multiply, 1893, 2, 1895);
  g->Binary(ynn_binary_add, 1894, 1895, 1897);
}

// Scope: "Layer24 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer24AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7121, 1898, 0.001091228099539876, 0);
  g->Dequantize(7136, 1899, 0.01785714365541935, 0);
  g->Matmul(1897, 1898, 1900, false, true);
  g->Mask(1900, 6492, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 6492, 5953, {-1}, true);
  g->Binary(ynn_binary_subtract, 6492, 5953, 5950);
  g->Unary(ynn_unary_exp, 5950, 5951);
  g->Reduce(ynn_reduce_sum, 5951, 5954, {-1}, true);
  g->Binary(ynn_binary_divide, 5430, 5954, 5952);
  g->Binary(ynn_binary_multiply, 5951, 5952, 1901);
  g->Matmul(1901, 1899, 1902, false, false);
}

// Scope: "Layer24 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer24AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1902, 1903, {0,2,1,3});
  g->FuseDims(1903, 1904, 2, 2);
  g->Quantize(1904, 1905, 0.01457924209535122, 0);
  g->Transpose(6784, 4584, {1,0});
  g->Binary(ynn_binary_multiply, 4070, 4583, 4580);
  g->Dot(1905, 4584, YNN_INVALID_VALUE_ID, 4579, 1);
  g->DequantizeTensor(4579, YNN_INVALID_VALUE_ID, 4580, 4581);
  g->QuantizeTensor(4581, 6434, 4582, 1907);
  g->Dequantize(1907, 1908, 0.02337142638862133, 0);
}

// Scope: "Layer24 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer24Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1870, 1871);
  g->Reduce(ynn_reduce_sum, 1871, 5947, {2}, true);
  g->ShapeProduct(1871, 5946, {2});
  g->Binary(ynn_binary_divide, 5947, 5946, 1872);
  g->Binary(ynn_binary_add, 1872, 6469, 1873);
  g->Unary(ynn_unary_rsqrt, 1873, 1875);
  g->Binary(ynn_binary_multiply, 1870, 1875, 1876);
  g->Binary(ynn_binary_multiply, 1876, 6773, 1877);
  BuildLayer24AttentionQueryProjection(ctx);
  BuildLayer24AttentionSdpa(ctx);
  BuildLayer24AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1908, 1909);
  g->Reduce(ynn_reduce_sum, 1909, 5956, {2}, true);
  g->ShapeProduct(1909, 5955, {2});
  g->Binary(ynn_binary_divide, 5956, 5955, 1910);
  g->Binary(ynn_binary_add, 1910, 6469, 1911);
  g->Unary(ynn_unary_rsqrt, 1911, 1912);
  g->Binary(ynn_binary_multiply, 1908, 1912, 1913);
  g->Binary(ynn_binary_multiply, 1913, 6780, 1914);
  g->Binary(ynn_binary_add, 1914, 1870, 1915);
}

// Scope: "Layer24 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer24Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1915, 1916);
  g->Reduce(ynn_reduce_sum, 1916, 5958, {2}, true);
  g->ShapeProduct(1916, 5957, {2});
  g->Binary(ynn_binary_divide, 5958, 5957, 1919);
  g->Binary(ynn_binary_add, 1919, 6469, 1920);
  g->Unary(ynn_unary_rsqrt, 1920, 1921);
  g->Binary(ynn_binary_multiply, 1915, 1921, 1922);
  g->Binary(ynn_binary_multiply, 1922, 6783, 1923);
  g->Quantize(1923, 1924, 0.018518447875976562, 0);
  g->Transpose(6777, 4591, {1,0});
  g->Binary(ynn_binary_multiply, 4588, 4590, 4586);
  g->Dot(1924, 4591, YNN_INVALID_VALUE_ID, 4585, 1);
  g->DequantizeTensor(4585, YNN_INVALID_VALUE_ID, 4586, 4587);
  g->QuantizeTensor(4587, 6434, 4589, 1925);
  g->Dequantize(1925, 1926, 0.027313001453876495, 0);
  g->Transpose(6776, 4596, {1,0});
  g->Binary(ynn_binary_multiply, 4588, 4595, 4593);
  g->Dot(1924, 4596, YNN_INVALID_VALUE_ID, 4592, 1);
  g->DequantizeTensor(4592, YNN_INVALID_VALUE_ID, 4593, 4594);
  g->QuantizeTensor(4594, 6434, 4589, 1927);
  g->Dequantize(1927, 1929, 0.027313001453876495, 0);
  g->Polynomial(1929, 5963, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5963, 5964);
  g->Binary(ynn_binary_add, 5964, 5430, 5961);
  g->Binary(ynn_binary_multiply, 1929, 5428, 5962);
  g->Binary(ynn_binary_multiply, 5962, 5961, 1930);
  g->Binary(ynn_binary_multiply, 1926, 1930, 1931);
  g->Quantize(1931, 1932, 0.01894685998558998, 0);
  g->Transpose(6775, 4603, {1,0});
  g->Binary(ynn_binary_multiply, 4600, 4602, 4598);
  g->Dot(1932, 4603, YNN_INVALID_VALUE_ID, 4597, 1);
  g->DequantizeTensor(4597, YNN_INVALID_VALUE_ID, 4598, 4599);
  g->QuantizeTensor(4599, 6434, 4601, 1933);
  g->Dequantize(1933, 1934, 0.009169002994894981, 0);
  g->Unary(ynn_unary_square, 1934, 1935);
  g->Reduce(ynn_reduce_sum, 1935, 5966, {2}, true);
  g->ShapeProduct(1935, 5965, {2});
  g->Binary(ynn_binary_divide, 5966, 5965, 1936);
  g->Binary(ynn_binary_add, 1936, 6469, 1937);
  g->Unary(ynn_unary_rsqrt, 1937, 1938);
  g->Binary(ynn_binary_multiply, 1934, 1938, 1940);
  g->Binary(ynn_binary_multiply, 1940, 6781, 1941);
  g->Binary(ynn_binary_add, 1941, 1915, 1942);
}

// Scope: "Layer24 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer24PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(421, 1943, {0,0,24,0}, {-1,-1,1,-1});
  g->Reshape(1943, 1944, {1,1,256});
  g->Unary(ynn_unary_square, 1944, 1945);
  g->Reduce(ynn_reduce_sum, 1945, 5968, {2}, true);
  g->ShapeProduct(1945, 5967, {2});
  g->Binary(ynn_binary_divide, 5968, 5967, 1946);
  g->Binary(ynn_binary_add, 1946, 6469, 1947);
  g->Unary(ynn_unary_rsqrt, 1947, 1948);
  g->Binary(ynn_binary_multiply, 1944, 1948, 1949);
  g->Binary(ynn_binary_multiply, 1949, 7048, 1951);
  g->Binary(ynn_binary_multiply, 7066, 6472, 1952);
  g->Binary(ynn_binary_add, 1951, 1952, 1953);
  g->Binary(ynn_binary_multiply, 1953, 6466, 1954);
  g->Quantize(1942, 1955, 0.1741907149553299, 0);
  g->Transpose(6778, 4610, {1,0});
  g->Binary(ynn_binary_multiply, 4607, 4609, 4605);
  g->Dot(1955, 4610, YNN_INVALID_VALUE_ID, 4604, 1);
  g->DequantizeTensor(4604, YNN_INVALID_VALUE_ID, 4605, 4606);
  g->QuantizeTensor(4606, 6434, 4608, 1956);
  g->Dequantize(1956, 1957, 0.08710630983114243, 0);
  g->Polynomial(1957, 5971, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5971, 5972);
  g->Binary(ynn_binary_add, 5972, 5430, 5969);
  g->Binary(ynn_binary_multiply, 1957, 5428, 5970);
  g->Binary(ynn_binary_multiply, 5970, 5969, 1958);
  g->Binary(ynn_binary_multiply, 1958, 1954, 1959);
  g->Quantize(1959, 1960, 1.0236220359802246, 0);
  g->Transpose(6779, 4617, {1,0});
  g->Binary(ynn_binary_multiply, 4614, 4616, 4612);
  g->Dot(1960, 4617, YNN_INVALID_VALUE_ID, 4611, 1);
  g->DequantizeTensor(4611, YNN_INVALID_VALUE_ID, 4612, 4613);
  g->QuantizeTensor(4613, 6434, 4615, 1962);
  g->Dequantize(1962, 1963, 0.1628752052783966, 0);
  g->Unary(ynn_unary_square, 1963, 1964);
  g->Reduce(ynn_reduce_sum, 1964, 5974, {2}, true);
  g->ShapeProduct(1964, 5973, {2});
  g->Binary(ynn_binary_divide, 5974, 5973, 1965);
  g->Binary(ynn_binary_add, 1965, 6469, 1966);
  g->Unary(ynn_unary_rsqrt, 1966, 1967);
  g->Binary(ynn_binary_multiply, 1963, 1967, 1968);
  g->Binary(ynn_binary_multiply, 1968, 6782, 1969);
  g->Binary(ynn_binary_add, 1942, 1969, 1970);
  g->Binary(ynn_binary_multiply, 1970, 6774, 1971);
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
  g->Quantize(1978, 1979, 0.1674470156431198, 0);
  g->Transpose(6800, 4624, {1,0});
  g->Binary(ynn_binary_multiply, 4621, 4623, 4619);
  g->Dot(1979, 4624, YNN_INVALID_VALUE_ID, 4618, 1);
  g->DequantizeTensor(4618, YNN_INVALID_VALUE_ID, 4619, 4620);
  g->QuantizeTensor(4620, 6434, 4622, 1980);
  g->Dequantize(1980, 1981, 0.15452757477760315, 0);
  g->SplitDim(1981, 1982, 2, {8,256});
  g->Transpose(1982, 1984, {0,2,1,3});
  g->Unary(ynn_unary_square, 1984, 1985);
  g->Reduce(ynn_reduce_sum, 1985, 5978, {3}, true);
  g->ShapeProduct(1985, 5977, {3});
  g->Binary(ynn_binary_divide, 5978, 5977, 1986);
  g->Binary(ynn_binary_add, 1986, 6469, 1987);
  g->Unary(ynn_unary_rsqrt, 1987, 1988);
  g->Binary(ynn_binary_multiply, 1984, 1988, 1989);
  g->Binary(ynn_binary_multiply, 1989, 6799, 1990);
  g->Slice(1990, 1991, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1990, 1992, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1992, 1993);
  g->Concat({1993,1991}, 1995, 3);
  g->Binary(ynn_binary_multiply, 1990, 3009, 1996);
  g->Binary(ynn_binary_multiply, 1995, 3112, 1997);
  g->Binary(ynn_binary_add, 1996, 1997, 1998);
}

// Scope: "Layer25 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer25AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7120, 1999, 0.0059552486054599285, 0);
  g->Dequantize(7135, 2000, 0.047244105488061905, 0);
  g->Matmul(1998, 1999, 2001, false, true);
  g->Mask(2001, 6493, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6493, 5982, {-1}, true);
  g->Binary(ynn_binary_subtract, 6493, 5982, 5979);
  g->Unary(ynn_unary_exp, 5979, 5980);
  g->Reduce(ynn_reduce_sum, 5980, 5983, {-1}, true);
  g->Binary(ynn_binary_divide, 5430, 5983, 5981);
  g->Binary(ynn_binary_multiply, 5980, 5981, 2002);
  g->Matmul(2002, 2000, 2003, false, false);
}

// Scope: "Layer25 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer25AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(2003, 2005, {0,2,1,3});
  g->FuseDims(2005, 2006, 2, 2);
  g->Quantize(2006, 2007, 0.02325296215713024, 0);
  g->Transpose(6798, 4630, {1,0});
  g->Binary(ynn_binary_multiply, 4218, 4629, 4626);
  g->Dot(2007, 4630, YNN_INVALID_VALUE_ID, 4625, 1);
  g->DequantizeTensor(4625, YNN_INVALID_VALUE_ID, 4626, 4627);
  g->QuantizeTensor(4627, 6434, 4628, 2008);
  g->Dequantize(2008, 2009, 0.040348730981349945, 0);
}

// Scope: "Layer25 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer25Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1971, 1973);
  g->Reduce(ynn_reduce_sum, 1973, 5976, {2}, true);
  g->ShapeProduct(1973, 5975, {2});
  g->Binary(ynn_binary_divide, 5976, 5975, 1974);
  g->Binary(ynn_binary_add, 1974, 6469, 1975);
  g->Unary(ynn_unary_rsqrt, 1975, 1976);
  g->Binary(ynn_binary_multiply, 1971, 1976, 1977);
  g->Binary(ynn_binary_multiply, 1977, 6787, 1978);
  BuildLayer25AttentionQueryProjection(ctx);
  BuildLayer25AttentionSdpa(ctx);
  BuildLayer25AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2009, 2010);
  g->Reduce(ynn_reduce_sum, 2010, 5985, {2}, true);
  g->ShapeProduct(2010, 5984, {2});
  g->Binary(ynn_binary_divide, 5985, 5984, 2011);
  g->Binary(ynn_binary_add, 2011, 6469, 2012);
  g->Unary(ynn_unary_rsqrt, 2012, 2013);
  g->Binary(ynn_binary_multiply, 2009, 2013, 2014);
  g->Binary(ynn_binary_multiply, 2014, 6794, 2016);
  g->Binary(ynn_binary_add, 2016, 1971, 2017);
}

// Scope: "Layer25 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer25Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2017, 2018);
  g->Reduce(ynn_reduce_sum, 2018, 5987, {2}, true);
  g->ShapeProduct(2018, 5986, {2});
  g->Binary(ynn_binary_divide, 5987, 5986, 2019);
  g->Binary(ynn_binary_add, 2019, 6469, 2020);
  g->Unary(ynn_unary_rsqrt, 2020, 2021);
  g->Binary(ynn_binary_multiply, 2017, 2021, 2022);
  g->Binary(ynn_binary_multiply, 2022, 6797, 2023);
  g->Quantize(2023, 2024, 0.02161904238164425, 0);
  g->Transpose(6791, 4636, {1,0});
  g->Binary(ynn_binary_multiply, 4634, 4635, 4632);
  g->Dot(2024, 4636, YNN_INVALID_VALUE_ID, 4631, 1);
  g->DequantizeTensor(4631, YNN_INVALID_VALUE_ID, 4632, 4633);
  g->QuantizeTensor(4633, 6434, 4290, 2025);
  g->Dequantize(2025, 2028, 0.03297245129942894, 0);
  g->Transpose(6790, 4641, {1,0});
  g->Binary(ynn_binary_multiply, 4634, 4640, 4638);
  g->Dot(2024, 4641, YNN_INVALID_VALUE_ID, 4637, 1);
  g->DequantizeTensor(4637, YNN_INVALID_VALUE_ID, 4638, 4639);
  g->QuantizeTensor(4639, 6434, 4290, 2029);
  g->Dequantize(2029, 2030, 0.03297245129942894, 0);
  g->Polynomial(2030, 5990, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5990, 5991);
  g->Binary(ynn_binary_add, 5991, 5430, 5988);
  g->Binary(ynn_binary_multiply, 2030, 5428, 5989);
  g->Binary(ynn_binary_multiply, 5989, 5988, 2031);
  g->Binary(ynn_binary_multiply, 2028, 2031, 2032);
  g->Quantize(2032, 2033, 0.032726388424634933, 0);
  g->Transpose(6789, 4648, {1,0});
  g->Binary(ynn_binary_multiply, 4645, 4647, 4643);
  g->Dot(2033, 4648, YNN_INVALID_VALUE_ID, 4642, 1);
  g->DequantizeTensor(4642, YNN_INVALID_VALUE_ID, 4643, 4644);
  g->QuantizeTensor(4644, 6434, 4646, 2034);
  g->Dequantize(2034, 2035, 0.00990387424826622, 0);
  g->Unary(ynn_unary_square, 2035, 2036);
  g->Reduce(ynn_reduce_sum, 2036, 5993, {2}, true);
  g->ShapeProduct(2036, 5992, {2});
  g->Binary(ynn_binary_divide, 5993, 5992, 2038);
  g->Binary(ynn_binary_add, 2038, 6469, 2039);
  g->Unary(ynn_unary_rsqrt, 2039, 2040);
  g->Binary(ynn_binary_multiply, 2035, 2040, 2041);
  g->Binary(ynn_binary_multiply, 2041, 6795, 2042);
  g->Binary(ynn_binary_add, 2042, 2017, 2043);
}

// Scope: "Layer25 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer25PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(421, 2044, {0,0,25,0}, {-1,-1,1,-1});
  g->Reshape(2044, 2045, {1,1,256});
  g->Unary(ynn_unary_square, 2045, 2046);
  g->Reduce(ynn_reduce_sum, 2046, 5995, {2}, true);
  g->ShapeProduct(2046, 5994, {2});
  g->Binary(ynn_binary_divide, 5995, 5994, 2047);
  g->Binary(ynn_binary_add, 2047, 6469, 2049);
  g->Unary(ynn_unary_rsqrt, 2049, 2050);
  g->Binary(ynn_binary_multiply, 2045, 2050, 2051);
  g->Binary(ynn_binary_multiply, 2051, 7048, 2052);
  g->Binary(ynn_binary_multiply, 7067, 6472, 2053);
  g->Binary(ynn_binary_add, 2052, 2053, 2054);
  g->Binary(ynn_binary_multiply, 2054, 6466, 2055);
  g->Quantize(2043, 2056, 0.1164931058883667, 0);
  g->Transpose(6792, 4655, {1,0});
  g->Binary(ynn_binary_multiply, 4652, 4654, 4650);
  g->Dot(2056, 4655, YNN_INVALID_VALUE_ID, 4649, 1);
  g->DequantizeTensor(4649, YNN_INVALID_VALUE_ID, 4650, 4651);
  g->QuantizeTensor(4651, 6434, 4653, 2057);
  g->Dequantize(2057, 2058, 0.11269685626029968, 0);
  g->Polynomial(2058, 5998, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5998, 5999);
  g->Binary(ynn_binary_add, 5999, 5430, 5996);
  g->Binary(ynn_binary_multiply, 2058, 5428, 5997);
  g->Binary(ynn_binary_multiply, 5997, 5996, 2059);
  g->Binary(ynn_binary_multiply, 2059, 2055, 2060);
  g->Quantize(2060, 2061, 0.5157480239868164, 0);
  g->Transpose(6793, 4662, {1,0});
  g->Binary(ynn_binary_multiply, 4659, 4661, 4657);
  g->Dot(2061, 4662, YNN_INVALID_VALUE_ID, 4656, 1);
  g->DequantizeTensor(4656, YNN_INVALID_VALUE_ID, 4657, 4658);
  g->QuantizeTensor(4658, 6434, 4660, 2062);
  g->Dequantize(2062, 2063, 0.3825955092906952, 0);
  g->Unary(ynn_unary_square, 2063, 2064);
  g->Reduce(ynn_reduce_sum, 2064, 6001, {2}, true);
  g->ShapeProduct(2064, 6000, {2});
  g->Binary(ynn_binary_divide, 6001, 6000, 2065);
  g->Binary(ynn_binary_add, 2065, 6469, 2066);
  g->Unary(ynn_unary_rsqrt, 2066, 2067);
  g->Binary(ynn_binary_multiply, 2063, 2067, 2068);
  g->Binary(ynn_binary_multiply, 2068, 6796, 2070);
  g->Binary(ynn_binary_add, 2043, 2070, 2071);
  g->Binary(ynn_binary_multiply, 2071, 6788, 2072);
}

// Scope: "Layer25"
LAB_YNN_BUILDER_NOINLINE void BuildLayer25(Context& ctx) {
  BuildLayer25Attention(ctx);
  BuildLayer25Mlp(ctx);
  BuildLayer25PerLayerEmbedding(ctx);
}

}  // namespace BuildGemma4DecodeSource
