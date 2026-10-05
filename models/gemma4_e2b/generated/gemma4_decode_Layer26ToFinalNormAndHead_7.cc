// Generated YNNPACK builder; do not edit.
#include "gemma4_decode_builder.h"

namespace BuildGemma4DecodeSource {

// Scope: "Layer26 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer26AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(2078, 2079, 0.14451591670513153, 0);
  g->Transpose(6814, 4674, {1,0});
  g->Binary(ynn_binary_multiply, 4671, 4673, 4669);
  g->Dot(2079, 4674, YNN_INVALID_VALUE_ID, 4668, 1);
  g->DequantizeTensor(4668, YNN_INVALID_VALUE_ID, 4669, 4670);
  g->QuantizeTensor(4670, 6434, 4672, 2081);
  g->Dequantize(2081, 2082, 0.25196850299835205, 0);
  g->SplitDim(2082, 2083, 2, {8,256});
  g->Transpose(2083, 2084, {0,2,1,3});
  g->Unary(ynn_unary_square, 2084, 2085);
  g->Reduce(ynn_reduce_sum, 2085, 6005, {3}, true);
  g->ShapeProduct(2085, 6004, {3});
  g->Binary(ynn_binary_divide, 6005, 6004, 2086);
  g->Binary(ynn_binary_add, 2086, 6469, 2087);
  g->Unary(ynn_unary_rsqrt, 2087, 2088);
  g->Binary(ynn_binary_multiply, 2084, 2088, 2089);
  g->Binary(ynn_binary_multiply, 2089, 6813, 2090);
  g->Slice(2090, 2092, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2090, 2093, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2093, 2094);
  g->Concat({2094,2092}, 2095, 3);
  g->Binary(ynn_binary_multiply, 2090, 3009, 2096);
  g->Binary(ynn_binary_multiply, 2095, 3112, 2097);
  g->Binary(ynn_binary_add, 2096, 2097, 2098);
}

// Scope: "Layer26 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer26AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7120, 2099, 0.0059552486054599285, 0);
  g->Dequantize(7135, 2100, 0.047244105488061905, 0);
  g->Matmul(2098, 2099, 2101, false, true);
  g->Mask(2101, 6494, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6494, 6009, {-1}, true);
  g->Binary(ynn_binary_subtract, 6494, 6009, 6006);
  g->Unary(ynn_unary_exp, 6006, 6007);
  g->Reduce(ynn_reduce_sum, 6007, 6010, {-1}, true);
  g->Binary(ynn_binary_divide, 5430, 6010, 6008);
  g->Binary(ynn_binary_multiply, 6007, 6008, 2103);
  g->Matmul(2103, 2100, 2104, false, false);
}

// Scope: "Layer26 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer26AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(2104, 2105, {0,2,1,3});
  g->FuseDims(2105, 2106, 2, 2);
  g->Quantize(2106, 2107, 0.023129930719733238, 0);
  g->Transpose(6812, 4680, {1,0});
  g->Binary(ynn_binary_multiply, 4182, 4679, 4676);
  g->Dot(2107, 4680, YNN_INVALID_VALUE_ID, 4675, 1);
  g->DequantizeTensor(4675, YNN_INVALID_VALUE_ID, 4676, 4677);
  g->QuantizeTensor(4677, 6434, 4678, 2108);
  g->Dequantize(2108, 2109, 0.04343831539154053, 0);
}

// Scope: "Layer26 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer26Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2072, 2073);
  g->Reduce(ynn_reduce_sum, 2073, 6003, {2}, true);
  g->ShapeProduct(2073, 6002, {2});
  g->Binary(ynn_binary_divide, 6003, 6002, 2074);
  g->Binary(ynn_binary_add, 2074, 6469, 2075);
  g->Unary(ynn_unary_rsqrt, 2075, 2076);
  g->Binary(ynn_binary_multiply, 2072, 2076, 2077);
  g->Binary(ynn_binary_multiply, 2077, 6801, 2078);
  BuildLayer26AttentionQueryProjection(ctx);
  BuildLayer26AttentionSdpa(ctx);
  BuildLayer26AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2109, 2110);
  g->Reduce(ynn_reduce_sum, 2110, 6012, {2}, true);
  g->ShapeProduct(2110, 6011, {2});
  g->Binary(ynn_binary_divide, 6012, 6011, 2111);
  g->Binary(ynn_binary_add, 2111, 6469, 2113);
  g->Unary(ynn_unary_rsqrt, 2113, 2114);
  g->Binary(ynn_binary_multiply, 2109, 2114, 2115);
  g->Binary(ynn_binary_multiply, 2115, 6808, 2116);
  g->Binary(ynn_binary_add, 2116, 2072, 2117);
}

// Scope: "Layer26 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer26Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2117, 2118);
  g->Reduce(ynn_reduce_sum, 2118, 6014, {2}, true);
  g->ShapeProduct(2118, 6013, {2});
  g->Binary(ynn_binary_divide, 6014, 6013, 2119);
  g->Binary(ynn_binary_add, 2119, 6469, 2120);
  g->Unary(ynn_unary_rsqrt, 2120, 2121);
  g->Binary(ynn_binary_multiply, 2117, 2121, 2122);
  g->Binary(ynn_binary_multiply, 2122, 6811, 2124);
  g->Quantize(2124, 2125, 0.02699781395494938, 0);
  g->Transpose(6805, 4687, {1,0});
  g->Binary(ynn_binary_multiply, 4684, 4686, 4682);
  g->Dot(2125, 4687, YNN_INVALID_VALUE_ID, 4681, 1);
  g->DequantizeTensor(4681, YNN_INVALID_VALUE_ID, 4682, 4683);
  g->QuantizeTensor(4683, 6434, 4685, 2126);
  g->Dequantize(2126, 2127, 0.04478347674012184, 0);
  g->Transpose(6804, 4692, {1,0});
  g->Binary(ynn_binary_multiply, 4684, 4691, 4689);
  g->Dot(2125, 4692, YNN_INVALID_VALUE_ID, 4688, 1);
  g->DequantizeTensor(4688, YNN_INVALID_VALUE_ID, 4689, 4690);
  g->QuantizeTensor(4690, 6434, 4685, 2128);
  g->Dequantize(2128, 2129, 0.04478347674012184, 0);
  g->Polynomial(2129, 6019, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6019, 6020);
  g->Binary(ynn_binary_add, 6020, 5430, 6017);
  g->Binary(ynn_binary_multiply, 2129, 5428, 6018);
  g->Binary(ynn_binary_multiply, 6018, 6017, 2130);
  g->Binary(ynn_binary_multiply, 2127, 2130, 2131);
  g->Quantize(2131, 2132, 0.05019685998558998, 0);
  g->Transpose(6803, 4699, {1,0});
  g->Binary(ynn_binary_multiply, 4696, 4698, 4694);
  g->Dot(2132, 4699, YNN_INVALID_VALUE_ID, 4693, 1);
  g->DequantizeTensor(4693, YNN_INVALID_VALUE_ID, 4694, 4695);
  g->QuantizeTensor(4695, 6434, 4697, 2136);
  g->Dequantize(2136, 2137, 0.017497630789875984, 0);
  g->Unary(ynn_unary_square, 2137, 2138);
  g->Reduce(ynn_reduce_sum, 2138, 6022, {2}, true);
  g->ShapeProduct(2138, 6021, {2});
  g->Binary(ynn_binary_divide, 6022, 6021, 2139);
  g->Binary(ynn_binary_add, 2139, 6469, 2140);
  g->Unary(ynn_unary_rsqrt, 2140, 2141);
  g->Binary(ynn_binary_multiply, 2137, 2141, 2142);
  g->Binary(ynn_binary_multiply, 2142, 6809, 2143);
  g->Binary(ynn_binary_add, 2143, 2117, 2144);
}

// Scope: "Layer26 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer26PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(421, 2145, {0,0,26,0}, {-1,-1,1,-1});
  g->Reshape(2145, 2147, {1,1,256});
  g->Unary(ynn_unary_square, 2147, 2148);
  g->Reduce(ynn_reduce_sum, 2148, 6024, {2}, true);
  g->ShapeProduct(2148, 6023, {2});
  g->Binary(ynn_binary_divide, 6024, 6023, 2149);
  g->Binary(ynn_binary_add, 2149, 6469, 2150);
  g->Unary(ynn_unary_rsqrt, 2150, 2151);
  g->Binary(ynn_binary_multiply, 2147, 2151, 2152);
  g->Binary(ynn_binary_multiply, 2152, 7048, 2153);
  g->Binary(ynn_binary_multiply, 7068, 6472, 2154);
  g->Binary(ynn_binary_add, 2153, 2154, 2155);
  g->Binary(ynn_binary_multiply, 2155, 6466, 2156);
  g->Quantize(2144, 2158, 0.11300035566091537, 0);
  g->Transpose(6806, 4706, {1,0});
  g->Binary(ynn_binary_multiply, 4703, 4705, 4701);
  g->Dot(2158, 4706, YNN_INVALID_VALUE_ID, 4700, 1);
  g->DequantizeTensor(4700, YNN_INVALID_VALUE_ID, 4701, 4702);
  g->QuantizeTensor(4702, 6434, 4704, 2159);
  g->Dequantize(2159, 2160, 0.10088583081960678, 0);
  g->Polynomial(2160, 6027, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6027, 6028);
  g->Binary(ynn_binary_add, 6028, 5430, 6025);
  g->Binary(ynn_binary_multiply, 2160, 5428, 6026);
  g->Binary(ynn_binary_multiply, 6026, 6025, 2161);
  g->Binary(ynn_binary_multiply, 2161, 2156, 2162);
  g->Quantize(2162, 2163, 0.5472440719604492, 0);
  g->Transpose(6807, 4713, {1,0});
  g->Binary(ynn_binary_multiply, 4710, 4712, 4708);
  g->Dot(2163, 4713, YNN_INVALID_VALUE_ID, 4707, 1);
  g->DequantizeTensor(4707, YNN_INVALID_VALUE_ID, 4708, 4709);
  g->QuantizeTensor(4709, 6434, 4711, 2164);
  g->Dequantize(2164, 2165, 0.34460699558258057, 0);
  g->Unary(ynn_unary_square, 2165, 2166);
  g->Reduce(ynn_reduce_sum, 2166, 6030, {2}, true);
  g->ShapeProduct(2166, 6029, {2});
  g->Binary(ynn_binary_divide, 6030, 6029, 2167);
  g->Binary(ynn_binary_add, 2167, 6469, 2169);
  g->Unary(ynn_unary_rsqrt, 2169, 2170);
  g->Binary(ynn_binary_multiply, 2165, 2170, 2171);
  g->Binary(ynn_binary_multiply, 2171, 6810, 2172);
  g->Binary(ynn_binary_add, 2144, 2172, 2173);
  g->Binary(ynn_binary_multiply, 2173, 6802, 2174);
}

// Scope: "Layer26"
LAB_YNN_BUILDER_NOINLINE void BuildLayer26(Context& ctx) {
  BuildLayer26Attention(ctx);
  BuildLayer26Mlp(ctx);
  BuildLayer26PerLayerEmbedding(ctx);
}

// Scope: "Layer27 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer27AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(2180, 2181, 0.3104223608970642, 0);
  g->Transpose(6828, 4720, {1,0});
  g->Binary(ynn_binary_multiply, 4717, 4719, 4715);
  g->Dot(2181, 4720, YNN_INVALID_VALUE_ID, 4714, 1);
  g->DequantizeTensor(4714, YNN_INVALID_VALUE_ID, 4715, 4716);
  g->QuantizeTensor(4716, 6434, 4718, 2182);
  g->Dequantize(2182, 2183, 0.437007874250412, 0);
  g->SplitDim(2183, 2184, 2, {8,256});
  g->Transpose(2184, 2185, {0,2,1,3});
  g->Unary(ynn_unary_square, 2185, 2186);
  g->Reduce(ynn_reduce_sum, 2186, 6034, {3}, true);
  g->ShapeProduct(2186, 6033, {3});
  g->Binary(ynn_binary_divide, 6034, 6033, 2187);
  g->Binary(ynn_binary_add, 2187, 6469, 2188);
  g->Unary(ynn_unary_rsqrt, 2188, 2189);
  g->Binary(ynn_binary_multiply, 2185, 2189, 2190);
  g->Binary(ynn_binary_multiply, 2190, 6827, 2191);
  g->Slice(2191, 2192, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2191, 2193, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2193, 2194);
  g->Concat({2194,2192}, 2195, 3);
  g->Binary(ynn_binary_multiply, 2191, 3009, 2196);
  g->Binary(ynn_binary_multiply, 2195, 3112, 2197);
  g->Binary(ynn_binary_add, 2196, 2197, 2198);
}

// Scope: "Layer27 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer27AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7120, 2200, 0.0059552486054599285, 0);
  g->Dequantize(7135, 2201, 0.047244105488061905, 0);
  g->Matmul(2198, 2200, 2202, false, true);
  g->Mask(2202, 6495, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6495, 6038, {-1}, true);
  g->Binary(ynn_binary_subtract, 6495, 6038, 6035);
  g->Unary(ynn_unary_exp, 6035, 6036);
  g->Reduce(ynn_reduce_sum, 6036, 6039, {-1}, true);
  g->Binary(ynn_binary_divide, 5430, 6039, 6037);
  g->Binary(ynn_binary_multiply, 6036, 6037, 2203);
  g->Matmul(2203, 2201, 2204, false, false);
}

// Scope: "Layer27 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer27AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(2204, 2205, {0,2,1,3});
  g->FuseDims(2205, 2206, 2, 2);
  g->Quantize(2206, 2207, 0.024237213656306267, 0);
  g->Transpose(6826, 4727, {1,0});
  g->Binary(ynn_binary_multiply, 4724, 4726, 4722);
  g->Dot(2207, 4727, YNN_INVALID_VALUE_ID, 4721, 1);
  g->DequantizeTensor(4721, YNN_INVALID_VALUE_ID, 4722, 4723);
  g->QuantizeTensor(4723, 6434, 4725, 2208);
  g->Dequantize(2208, 2209, 0.05315101891756058, 0);
}

// Scope: "Layer27 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer27Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2174, 2175);
  g->Reduce(ynn_reduce_sum, 2175, 6032, {2}, true);
  g->ShapeProduct(2175, 6031, {2});
  g->Binary(ynn_binary_divide, 6032, 6031, 2176);
  g->Binary(ynn_binary_add, 2176, 6469, 2177);
  g->Unary(ynn_unary_rsqrt, 2177, 2178);
  g->Binary(ynn_binary_multiply, 2174, 2178, 2179);
  g->Binary(ynn_binary_multiply, 2179, 6815, 2180);
  BuildLayer27AttentionQueryProjection(ctx);
  BuildLayer27AttentionSdpa(ctx);
  BuildLayer27AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2209, 2210);
  g->Reduce(ynn_reduce_sum, 2210, 6041, {2}, true);
  g->ShapeProduct(2210, 6040, {2});
  g->Binary(ynn_binary_divide, 6041, 6040, 2211);
  g->Binary(ynn_binary_add, 2211, 6469, 2212);
  g->Unary(ynn_unary_rsqrt, 2212, 2213);
  g->Binary(ynn_binary_multiply, 2209, 2213, 2214);
  g->Binary(ynn_binary_multiply, 2214, 6822, 2215);
  g->Binary(ynn_binary_add, 2215, 2174, 2216);
}

// Scope: "Layer27 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer27Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2216, 2217);
  g->Reduce(ynn_reduce_sum, 2217, 6043, {2}, true);
  g->ShapeProduct(2217, 6042, {2});
  g->Binary(ynn_binary_divide, 6043, 6042, 2218);
  g->Binary(ynn_binary_add, 2218, 6469, 2219);
  g->Unary(ynn_unary_rsqrt, 2219, 2220);
  g->Binary(ynn_binary_multiply, 2216, 2220, 2221);
  g->Binary(ynn_binary_multiply, 2221, 6825, 2222);
  g->Quantize(2222, 2223, 0.02701687067747116, 0);
  g->Transpose(6819, 4734, {1,0});
  g->Binary(ynn_binary_multiply, 4731, 4733, 4729);
  g->Dot(2223, 4734, YNN_INVALID_VALUE_ID, 4728, 1);
  g->DequantizeTensor(4728, YNN_INVALID_VALUE_ID, 4729, 4730);
  g->QuantizeTensor(4730, 6434, 4732, 2224);
  g->Dequantize(2224, 2225, 0.044537413865327835, 0);
  g->Transpose(6818, 4739, {1,0});
  g->Binary(ynn_binary_multiply, 4731, 4738, 4736);
  g->Dot(2223, 4739, YNN_INVALID_VALUE_ID, 4735, 1);
  g->DequantizeTensor(4735, YNN_INVALID_VALUE_ID, 4736, 4737);
  g->QuantizeTensor(4737, 6434, 4732, 2226);
  g->Dequantize(2226, 2227, 0.044537413865327835, 0);
  g->Polynomial(2227, 6046, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6046, 6047);
  g->Binary(ynn_binary_add, 6047, 5430, 6044);
  g->Binary(ynn_binary_multiply, 2227, 5428, 6045);
  g->Binary(ynn_binary_multiply, 6045, 6044, 2228);
  g->Binary(ynn_binary_multiply, 2225, 2228, 2229);
  g->Quantize(2229, 2230, 0.09104331582784653, 0);
  g->Transpose(6817, 4746, {1,0});
  g->Binary(ynn_binary_multiply, 4743, 4745, 4741);
  g->Dot(2230, 4746, YNN_INVALID_VALUE_ID, 4740, 1);
  g->DequantizeTensor(4740, YNN_INVALID_VALUE_ID, 4741, 4742);
  g->QuantizeTensor(4742, 6434, 4744, 2231);
  g->Dequantize(2231, 2232, 0.08018074929714203, 0);
  g->Unary(ynn_unary_square, 2232, 2233);
  g->Reduce(ynn_reduce_sum, 2233, 6049, {2}, true);
  g->ShapeProduct(2233, 6048, {2});
  g->Binary(ynn_binary_divide, 6049, 6048, 2234);
  g->Binary(ynn_binary_add, 2234, 6469, 2235);
  g->Unary(ynn_unary_rsqrt, 2235, 2236);
  g->Binary(ynn_binary_multiply, 2232, 2236, 2237);
  g->Binary(ynn_binary_multiply, 2237, 6823, 2240);
  g->Binary(ynn_binary_add, 2240, 2216, 2241);
}

// Scope: "Layer27 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer27PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(421, 2242, {0,0,27,0}, {-1,-1,1,-1});
  g->Reshape(2242, 2243, {1,1,256});
  g->Unary(ynn_unary_square, 2243, 2244);
  g->Reduce(ynn_reduce_sum, 2244, 6051, {2}, true);
  g->ShapeProduct(2244, 6050, {2});
  g->Binary(ynn_binary_divide, 6051, 6050, 2245);
  g->Binary(ynn_binary_add, 2245, 6469, 2246);
  g->Unary(ynn_unary_rsqrt, 2246, 2247);
  g->Binary(ynn_binary_multiply, 2243, 2247, 2248);
  g->Binary(ynn_binary_multiply, 2248, 7048, 2249);
  g->Binary(ynn_binary_multiply, 7069, 6472, 2251);
  g->Binary(ynn_binary_add, 2249, 2251, 2252);
  g->Binary(ynn_binary_multiply, 2252, 6466, 2253);
  g->Quantize(2241, 2254, 0.12690971791744232, 0);
  g->Transpose(6820, 4759, {1,0});
  g->Binary(ynn_binary_multiply, 4756, 4758, 4754);
  g->Dot(2254, 4759, YNN_INVALID_VALUE_ID, 4753, 1);
  g->DequantizeTensor(4753, YNN_INVALID_VALUE_ID, 4754, 4755);
  g->QuantizeTensor(4755, 6434, 4757, 2255);
  g->Dequantize(2255, 2256, 0.07578741014003754, 0);
  g->Polynomial(2256, 6054, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6054, 6055);
  g->Binary(ynn_binary_add, 6055, 5430, 6052);
  g->Binary(ynn_binary_multiply, 2256, 5428, 6053);
  g->Binary(ynn_binary_multiply, 6053, 6052, 2257);
  g->Binary(ynn_binary_multiply, 2257, 2253, 2258);
  g->Quantize(2258, 2259, 0.5708661675453186, 0);
  g->Transpose(6821, 4766, {1,0});
  g->Binary(ynn_binary_multiply, 4763, 4765, 4761);
  g->Dot(2259, 4766, YNN_INVALID_VALUE_ID, 4760, 1);
  g->DequantizeTensor(4760, YNN_INVALID_VALUE_ID, 4761, 4762);
  g->QuantizeTensor(4762, 6434, 4764, 2260);
  g->Dequantize(2260, 2262, 0.26081717014312744, 0);
  g->Unary(ynn_unary_square, 2262, 2263);
  g->Reduce(ynn_reduce_sum, 2263, 6057, {2}, true);
  g->ShapeProduct(2263, 6056, {2});
  g->Binary(ynn_binary_divide, 6057, 6056, 2264);
  g->Binary(ynn_binary_add, 2264, 6469, 2265);
  g->Unary(ynn_unary_rsqrt, 2265, 2266);
  g->Binary(ynn_binary_multiply, 2262, 2266, 2267);
  g->Binary(ynn_binary_multiply, 2267, 6824, 2268);
  g->Binary(ynn_binary_add, 2241, 2268, 2269);
  g->Binary(ynn_binary_multiply, 2269, 6816, 2270);
}

// Scope: "Layer27"
LAB_YNN_BUILDER_NOINLINE void BuildLayer27(Context& ctx) {
  BuildLayer27Attention(ctx);
  BuildLayer27Mlp(ctx);
  BuildLayer27PerLayerEmbedding(ctx);
}

// Scope: "Layer28 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer28AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(2277, 2278, 0.4655068814754486, 0);
  g->Transpose(6842, 4773, {1,0});
  g->Binary(ynn_binary_multiply, 4770, 4772, 4768);
  g->Dot(2278, 4773, YNN_INVALID_VALUE_ID, 4767, 1);
  g->DequantizeTensor(4767, YNN_INVALID_VALUE_ID, 4768, 4769);
  g->QuantizeTensor(4769, 6434, 4771, 2279);
  g->Dequantize(2279, 2280, 0.34645670652389526, 0);
  g->SplitDim(2280, 2281, 2, {8,256});
  g->Transpose(2281, 2282, {0,2,1,3});
  g->Unary(ynn_unary_square, 2282, 2284);
  g->Reduce(ynn_reduce_sum, 2284, 6061, {3}, true);
  g->ShapeProduct(2284, 6060, {3});
  g->Binary(ynn_binary_divide, 6061, 6060, 2285);
  g->Binary(ynn_binary_add, 2285, 6469, 2286);
  g->Unary(ynn_unary_rsqrt, 2286, 2287);
  g->Binary(ynn_binary_multiply, 2282, 2287, 2288);
  g->Binary(ynn_binary_multiply, 2288, 6841, 2289);
  g->Slice(2289, 2290, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2289, 2291, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2291, 2292);
  g->Concat({2292,2290}, 2293, 3);
  g->Binary(ynn_binary_multiply, 2289, 3009, 2295);
  g->Binary(ynn_binary_multiply, 2293, 3112, 2296);
  g->Binary(ynn_binary_add, 2295, 2296, 2297);
}

// Scope: "Layer28 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer28AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7120, 2298, 0.0059552486054599285, 0);
  g->Dequantize(7135, 2299, 0.047244105488061905, 0);
  g->Matmul(2297, 2298, 2300, false, true);
  g->Mask(2300, 6496, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6496, 6067, {-1}, true);
  g->Binary(ynn_binary_subtract, 6496, 6067, 6064);
  g->Unary(ynn_unary_exp, 6064, 6065);
  g->Reduce(ynn_reduce_sum, 6065, 6068, {-1}, true);
  g->Binary(ynn_binary_divide, 5430, 6068, 6066);
  g->Binary(ynn_binary_multiply, 6065, 6066, 2301);
  g->Matmul(2301, 2299, 2302, false, false);
}

// Scope: "Layer28 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer28AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(2302, 2303, {0,2,1,3});
  g->FuseDims(2303, 2305, 2, 2);
  g->Quantize(2305, 2306, 0.024237213656306267, 0);
  g->Transpose(6840, 4779, {1,0});
  g->Binary(ynn_binary_multiply, 4724, 4778, 4775);
  g->Dot(2306, 4779, YNN_INVALID_VALUE_ID, 4774, 1);
  g->DequantizeTensor(4774, YNN_INVALID_VALUE_ID, 4775, 4776);
  g->QuantizeTensor(4776, 6434, 4777, 2307);
  g->Dequantize(2307, 2308, 0.03035588562488556, 0);
}

// Scope: "Layer28 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer28Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2270, 2271);
  g->Reduce(ynn_reduce_sum, 2271, 6059, {2}, true);
  g->ShapeProduct(2271, 6058, {2});
  g->Binary(ynn_binary_divide, 6059, 6058, 2273);
  g->Binary(ynn_binary_add, 2273, 6469, 2274);
  g->Unary(ynn_unary_rsqrt, 2274, 2275);
  g->Binary(ynn_binary_multiply, 2270, 2275, 2276);
  g->Binary(ynn_binary_multiply, 2276, 6829, 2277);
  BuildLayer28AttentionQueryProjection(ctx);
  BuildLayer28AttentionSdpa(ctx);
  BuildLayer28AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2308, 2309);
  g->Reduce(ynn_reduce_sum, 2309, 6070, {2}, true);
  g->ShapeProduct(2309, 6069, {2});
  g->Binary(ynn_binary_divide, 6070, 6069, 2310);
  g->Binary(ynn_binary_add, 2310, 6469, 2311);
  g->Unary(ynn_unary_rsqrt, 2311, 2312);
  g->Binary(ynn_binary_multiply, 2308, 2312, 2313);
  g->Binary(ynn_binary_multiply, 2313, 6836, 2314);
  g->Binary(ynn_binary_add, 2314, 2270, 2316);
}

// Scope: "Layer28 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer28Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2316, 2317);
  g->Reduce(ynn_reduce_sum, 2317, 6072, {2}, true);
  g->ShapeProduct(2317, 6071, {2});
  g->Binary(ynn_binary_divide, 6072, 6071, 2318);
  g->Binary(ynn_binary_add, 2318, 6469, 2319);
  g->Unary(ynn_unary_rsqrt, 2319, 2320);
  g->Binary(ynn_binary_multiply, 2316, 2320, 2321);
  g->Binary(ynn_binary_multiply, 2321, 6839, 2322);
  g->Quantize(2322, 2323, 0.025474751368165016, 0);
  g->Transpose(6833, 4786, {1,0});
  g->Binary(ynn_binary_multiply, 4783, 4785, 4781);
  g->Dot(2323, 4786, YNN_INVALID_VALUE_ID, 4780, 1);
  g->DequantizeTensor(4780, YNN_INVALID_VALUE_ID, 4781, 4782);
  g->QuantizeTensor(4782, 6434, 4784, 2324);
  g->Dequantize(2324, 2325, 0.03494095429778099, 0);
  g->Transpose(6832, 4791, {1,0});
  g->Binary(ynn_binary_multiply, 4783, 4790, 4788);
  g->Dot(2323, 4791, YNN_INVALID_VALUE_ID, 4787, 1);
  g->DequantizeTensor(4787, YNN_INVALID_VALUE_ID, 4788, 4789);
  g->QuantizeTensor(4789, 6434, 4784, 2327);
  g->Dequantize(2327, 2328, 0.03494095429778099, 0);
  g->Polynomial(2328, 6075, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6075, 6076);
  g->Binary(ynn_binary_add, 6076, 5430, 6073);
  g->Binary(ynn_binary_multiply, 2328, 5428, 6074);
  g->Binary(ynn_binary_multiply, 6074, 6073, 2329);
  g->Binary(ynn_binary_multiply, 2325, 2329, 2330);
  g->Quantize(2330, 2331, 0.07627953588962555, 0);
  g->Transpose(6831, 4798, {1,0});
  g->Binary(ynn_binary_multiply, 4795, 4797, 4793);
  g->Dot(2331, 4798, YNN_INVALID_VALUE_ID, 4792, 1);
  g->DequantizeTensor(4792, YNN_INVALID_VALUE_ID, 4793, 4794);
  g->QuantizeTensor(4794, 6434, 4796, 2332);
  g->Dequantize(2332, 2333, 0.10797519981861115, 0);
  g->Unary(ynn_unary_square, 2333, 2334);
  g->Reduce(ynn_reduce_sum, 2334, 6078, {2}, true);
  g->ShapeProduct(2334, 6077, {2});
  g->Binary(ynn_binary_divide, 6078, 6077, 2335);
  g->Binary(ynn_binary_add, 2335, 6469, 2337);
  g->Unary(ynn_unary_rsqrt, 2337, 2338);
  g->Binary(ynn_binary_multiply, 2333, 2338, 2339);
  g->Binary(ynn_binary_multiply, 2339, 6837, 2340);
  g->Binary(ynn_binary_add, 2340, 2316, 2341);
}

// Scope: "Layer28 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer28PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(421, 2342, {0,0,28,0}, {-1,-1,1,-1});
  g->Reshape(2342, 2343, {1,1,256});
  g->Unary(ynn_unary_square, 2343, 2344);
  g->Reduce(ynn_reduce_sum, 2344, 6080, {2}, true);
  g->ShapeProduct(2344, 6079, {2});
  g->Binary(ynn_binary_divide, 6080, 6079, 2345);
  g->Binary(ynn_binary_add, 2345, 6469, 2346);
  g->Unary(ynn_unary_rsqrt, 2346, 2349);
  g->Binary(ynn_binary_multiply, 2343, 2349, 2350);
  g->Binary(ynn_binary_multiply, 2350, 7048, 2351);
  g->Binary(ynn_binary_multiply, 7070, 6472, 2352);
  g->Binary(ynn_binary_add, 2351, 2352, 2353);
  g->Binary(ynn_binary_multiply, 2353, 6466, 2354);
  g->Quantize(2341, 2355, 0.13722270727157593, 0);
  g->Transpose(6834, 4805, {1,0});
  g->Binary(ynn_binary_multiply, 4802, 4804, 4800);
  g->Dot(2355, 4805, YNN_INVALID_VALUE_ID, 4799, 1);
  g->DequantizeTensor(4799, YNN_INVALID_VALUE_ID, 4800, 4801);
  g->QuantizeTensor(4801, 6434, 4803, 2356);
  g->Dequantize(2356, 2357, 0.08513779938220978, 0);
  g->Polynomial(2357, 6083, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6083, 6084);
  g->Binary(ynn_binary_add, 6084, 5430, 6081);
  g->Binary(ynn_binary_multiply, 2357, 5428, 6082);
  g->Binary(ynn_binary_multiply, 6082, 6081, 2358);
  g->Binary(ynn_binary_multiply, 2358, 2354, 2360);
  g->Quantize(2360, 2361, 0.748031497001648, 0);
  g->Transpose(6835, 4812, {1,0});
  g->Binary(ynn_binary_multiply, 4809, 4811, 4807);
  g->Dot(2361, 4812, YNN_INVALID_VALUE_ID, 4806, 1);
  g->DequantizeTensor(4806, YNN_INVALID_VALUE_ID, 4807, 4808);
  g->QuantizeTensor(4808, 6434, 4810, 2362);
  g->Dequantize(2362, 2363, 0.18373137712478638, 0);
  g->Unary(ynn_unary_square, 2363, 2364);
  g->Reduce(ynn_reduce_sum, 2364, 6086, {2}, true);
  g->ShapeProduct(2364, 6085, {2});
  g->Binary(ynn_binary_divide, 6086, 6085, 2365);
  g->Binary(ynn_binary_add, 2365, 6469, 2366);
  g->Unary(ynn_unary_rsqrt, 2366, 2367);
  g->Binary(ynn_binary_multiply, 2363, 2367, 2368);
  g->Binary(ynn_binary_multiply, 2368, 6838, 2369);
  g->Binary(ynn_binary_add, 2341, 2369, 2371);
  g->Binary(ynn_binary_multiply, 2371, 6830, 2372);
}

// Scope: "Layer28"
LAB_YNN_BUILDER_NOINLINE void BuildLayer28(Context& ctx) {
  BuildLayer28Attention(ctx);
  BuildLayer28Mlp(ctx);
  BuildLayer28PerLayerEmbedding(ctx);
}

// Scope: "Layer29 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer29AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(2378, 2379, 0.41653531789779663, 0);
  g->Transpose(6856, 4819, {1,0});
  g->Binary(ynn_binary_multiply, 4816, 4818, 4814);
  g->Dot(2379, 4819, YNN_INVALID_VALUE_ID, 4813, 1);
  g->DequantizeTensor(4813, YNN_INVALID_VALUE_ID, 4814, 4815);
  g->QuantizeTensor(4815, 6434, 4817, 2380);
  g->Dequantize(2380, 2382, 0.312992125749588, 0);
  g->SplitDim(2382, 2383, 2, {8,512});
  g->Transpose(2383, 2384, {0,2,1,3});
  g->Unary(ynn_unary_square, 2384, 2385);
  g->Reduce(ynn_reduce_sum, 2385, 6090, {3}, true);
  g->ShapeProduct(2385, 6089, {3});
  g->Binary(ynn_binary_divide, 6090, 6089, 2386);
  g->Binary(ynn_binary_add, 2386, 6469, 2387);
  g->Unary(ynn_unary_rsqrt, 2387, 2388);
  g->Binary(ynn_binary_multiply, 2384, 2388, 2389);
  g->Binary(ynn_binary_multiply, 2389, 6855, 2390);
  g->Slice(2390, 2391, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(2390, 2393, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 2393, 2394);
  g->Concat({2394,2391}, 2395, 3);
  g->Binary(ynn_binary_multiply, 2390, 3526, 2396);
  g->Binary(ynn_binary_multiply, 2395, 2, 2397);
  g->Binary(ynn_binary_add, 2396, 2397, 2398);
}

// Scope: "Layer29 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer29AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7121, 2399, 0.001091228099539876, 0);
  g->Dequantize(7136, 2400, 0.01785714365541935, 0);
  g->Matmul(2398, 2399, 2401, false, true);
  g->Mask(2401, 6497, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 6497, 6094, {-1}, true);
  g->Binary(ynn_binary_subtract, 6497, 6094, 6091);
  g->Unary(ynn_unary_exp, 6091, 6092);
  g->Reduce(ynn_reduce_sum, 6092, 6095, {-1}, true);
  g->Binary(ynn_binary_divide, 5430, 6095, 6093);
  g->Binary(ynn_binary_multiply, 6092, 6093, 2403);
  g->Matmul(2403, 2400, 2404, false, false);
}

// Scope: "Layer29 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer29AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(2404, 2405, {0,2,1,3});
  g->FuseDims(2405, 2406, 2, 2);
  g->Quantize(2406, 2407, 0.017962608486413956, 0);
  g->Transpose(6854, 4825, {1,0});
  g->Binary(ynn_binary_multiply, 3743, 4824, 4821);
  g->Dot(2407, 4825, YNN_INVALID_VALUE_ID, 4820, 1);
  g->DequantizeTensor(4820, YNN_INVALID_VALUE_ID, 4821, 4822);
  g->QuantizeTensor(4822, 6434, 4823, 2408);
  g->Dequantize(2408, 2409, 0.03030368685722351, 0);
}

// Scope: "Layer29 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer29Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2372, 2373);
  g->Reduce(ynn_reduce_sum, 2373, 6088, {2}, true);
  g->ShapeProduct(2373, 6087, {2});
  g->Binary(ynn_binary_divide, 6088, 6087, 2374);
  g->Binary(ynn_binary_add, 2374, 6469, 2375);
  g->Unary(ynn_unary_rsqrt, 2375, 2376);
  g->Binary(ynn_binary_multiply, 2372, 2376, 2377);
  g->Binary(ynn_binary_multiply, 2377, 6843, 2378);
  BuildLayer29AttentionQueryProjection(ctx);
  BuildLayer29AttentionSdpa(ctx);
  BuildLayer29AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2409, 2410);
  g->Reduce(ynn_reduce_sum, 2410, 6097, {2}, true);
  g->ShapeProduct(2410, 6096, {2});
  g->Binary(ynn_binary_divide, 6097, 6096, 2411);
  g->Binary(ynn_binary_add, 2411, 6469, 2412);
  g->Unary(ynn_unary_rsqrt, 2412, 2414);
  g->Binary(ynn_binary_multiply, 2409, 2414, 2415);
  g->Binary(ynn_binary_multiply, 2415, 6850, 2416);
  g->Binary(ynn_binary_add, 2416, 2372, 2417);
}

// Scope: "Layer29 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer29Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2417, 2418);
  g->Reduce(ynn_reduce_sum, 2418, 6099, {2}, true);
  g->ShapeProduct(2418, 6098, {2});
  g->Binary(ynn_binary_divide, 6099, 6098, 2419);
  g->Binary(ynn_binary_add, 2419, 6469, 2420);
  g->Unary(ynn_unary_rsqrt, 2420, 2421);
  g->Binary(ynn_binary_multiply, 2417, 2421, 2422);
  g->Binary(ynn_binary_multiply, 2422, 6853, 2423);
  g->Quantize(2423, 2425, 0.032805636525154114, 0);
  g->Transpose(6847, 4832, {1,0});
  g->Binary(ynn_binary_multiply, 4829, 4831, 4827);
  g->Dot(2425, 4832, YNN_INVALID_VALUE_ID, 4826, 1);
  g->DequantizeTensor(4826, YNN_INVALID_VALUE_ID, 4827, 4828);
  g->QuantizeTensor(4828, 6434, 4830, 2426);
  g->Dequantize(2426, 2427, 0.03690946102142334, 0);
  g->Transpose(6846, 4837, {1,0});
  g->Binary(ynn_binary_multiply, 4829, 4836, 4834);
  g->Dot(2425, 4837, YNN_INVALID_VALUE_ID, 4833, 1);
  g->DequantizeTensor(4833, YNN_INVALID_VALUE_ID, 4834, 4835);
  g->QuantizeTensor(4835, 6434, 4830, 2428);
  g->Dequantize(2428, 2429, 0.03690946102142334, 0);
  g->Polynomial(2429, 6102, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6102, 6103);
  g->Binary(ynn_binary_add, 6103, 5430, 6100);
  g->Binary(ynn_binary_multiply, 2429, 5428, 6101);
  g->Binary(ynn_binary_multiply, 6101, 6100, 2430);
  g->Binary(ynn_binary_multiply, 2427, 2430, 2431);
  g->Quantize(2431, 2432, 0.11171260476112366, 0);
  g->Transpose(6845, 4844, {1,0});
  g->Binary(ynn_binary_multiply, 4841, 4843, 4839);
  g->Dot(2432, 4844, YNN_INVALID_VALUE_ID, 4838, 1);
  g->DequantizeTensor(4838, YNN_INVALID_VALUE_ID, 4839, 4840);
  g->QuantizeTensor(4840, 6434, 4842, 2433);
  g->Dequantize(2433, 2435, 0.3346065282821655, 0);
  g->Unary(ynn_unary_square, 2435, 2436);
  g->Reduce(ynn_reduce_sum, 2436, 6105, {2}, true);
  g->ShapeProduct(2436, 6104, {2});
  g->Binary(ynn_binary_divide, 6105, 6104, 2437);
  g->Binary(ynn_binary_add, 2437, 6469, 2438);
  g->Unary(ynn_unary_rsqrt, 2438, 2439);
  g->Binary(ynn_binary_multiply, 2435, 2439, 2440);
  g->Binary(ynn_binary_multiply, 2440, 6851, 2441);
  g->Binary(ynn_binary_add, 2441, 2417, 2442);
}

// Scope: "Layer29 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer29PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(421, 2443, {0,0,29,0}, {-1,-1,1,-1});
  g->Reshape(2443, 2444, {1,1,256});
  g->Unary(ynn_unary_square, 2444, 2446);
  g->Reduce(ynn_reduce_sum, 2446, 6107, {2}, true);
  g->ShapeProduct(2446, 6106, {2});
  g->Binary(ynn_binary_divide, 6107, 6106, 2447);
  g->Binary(ynn_binary_add, 2447, 6469, 2448);
  g->Unary(ynn_unary_rsqrt, 2448, 2449);
  g->Binary(ynn_binary_multiply, 2444, 2449, 2450);
  g->Binary(ynn_binary_multiply, 2450, 7048, 2451);
  g->Binary(ynn_binary_multiply, 7071, 6472, 2452);
  g->Binary(ynn_binary_add, 2451, 2452, 2453);
  g->Binary(ynn_binary_multiply, 2453, 6466, 2454);
  g->Quantize(2442, 2455, 0.1425527185201645, 0);
  g->Transpose(6848, 4850, {1,0});
  g->Binary(ynn_binary_multiply, 4848, 4849, 4846);
  g->Dot(2455, 4850, YNN_INVALID_VALUE_ID, 4845, 1);
  g->DequantizeTensor(4845, YNN_INVALID_VALUE_ID, 4846, 4847);
  g->QuantizeTensor(4847, 6434, 4190, 2457);
  g->Dequantize(2457, 2458, 0.07234252989292145, 0);
  g->Polynomial(2458, 6110, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6110, 6111);
  g->Binary(ynn_binary_add, 6111, 5430, 6108);
  g->Binary(ynn_binary_multiply, 2458, 5428, 6109);
  g->Binary(ynn_binary_multiply, 6109, 6108, 2459);
  g->Binary(ynn_binary_multiply, 2459, 2454, 2460);
  g->Quantize(2460, 2461, 0.2539370059967041, 0);
  g->Transpose(6849, 4857, {1,0});
  g->Binary(ynn_binary_multiply, 4854, 4856, 4852);
  g->Dot(2461, 4857, YNN_INVALID_VALUE_ID, 4851, 1);
  g->DequantizeTensor(4851, YNN_INVALID_VALUE_ID, 4852, 4853);
  g->QuantizeTensor(4853, 6434, 4855, 2462);
  g->Dequantize(2462, 2463, 0.2777099609375, 0);
  g->Unary(ynn_unary_square, 2463, 2464);
  g->Reduce(ynn_reduce_sum, 2464, 6113, {2}, true);
  g->ShapeProduct(2464, 6112, {2});
  g->Binary(ynn_binary_divide, 6113, 6112, 2465);
  g->Binary(ynn_binary_add, 2465, 6469, 2466);
  g->Unary(ynn_unary_rsqrt, 2466, 2468);
  g->Binary(ynn_binary_multiply, 2463, 2468, 2469);
  g->Binary(ynn_binary_multiply, 2469, 6852, 2470);
  g->Binary(ynn_binary_add, 2442, 2470, 2471);
  g->Binary(ynn_binary_multiply, 2471, 6844, 2472);
}

// Scope: "Layer29"
LAB_YNN_BUILDER_NOINLINE void BuildLayer29(Context& ctx) {
  BuildLayer29Attention(ctx);
  BuildLayer29Mlp(ctx);
  BuildLayer29PerLayerEmbedding(ctx);
}

// Scope: "Layer30 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer30AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(2479, 2480, 0.621565580368042, 0);
  g->Transpose(6887, 4864, {1,0});
  g->Binary(ynn_binary_multiply, 4861, 4863, 4859);
  g->Dot(2480, 4864, YNN_INVALID_VALUE_ID, 4858, 1);
  g->DequantizeTensor(4858, YNN_INVALID_VALUE_ID, 4859, 4860);
  g->QuantizeTensor(4860, 6434, 4862, 2481);
  g->Dequantize(2481, 2482, 0.45866140723228455, 0);
  g->SplitDim(2482, 2483, 2, {8,256});
  g->Transpose(2483, 2484, {0,2,1,3});
  g->Unary(ynn_unary_square, 2484, 2485);
  g->Reduce(ynn_reduce_sum, 2485, 6122, {3}, true);
  g->ShapeProduct(2485, 6121, {3});
  g->Binary(ynn_binary_divide, 6122, 6121, 2486);
  g->Binary(ynn_binary_add, 2486, 6469, 2487);
  g->Unary(ynn_unary_rsqrt, 2487, 2488);
  g->Binary(ynn_binary_multiply, 2484, 2488, 2490);
  g->Binary(ynn_binary_multiply, 2490, 6886, 2491);
  g->Slice(2491, 2492, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2491, 2493, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2493, 2494);
  g->Concat({2494,2492}, 2495, 3);
  g->Binary(ynn_binary_multiply, 2491, 3009, 2496);
  g->Binary(ynn_binary_multiply, 2495, 3112, 2497);
  g->Binary(ynn_binary_add, 2496, 2497, 2498);
}

// Scope: "Layer30 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer30AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7120, 2499, 0.0059552486054599285, 0);
  g->Dequantize(7135, 2501, 0.047244105488061905, 0);
  g->Matmul(2498, 2499, 2502, false, true);
  g->Mask(2502, 6499, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6499, 6126, {-1}, true);
  g->Binary(ynn_binary_subtract, 6499, 6126, 6123);
  g->Unary(ynn_unary_exp, 6123, 6124);
  g->Reduce(ynn_reduce_sum, 6124, 6127, {-1}, true);
  g->Binary(ynn_binary_divide, 5430, 6127, 6125);
  g->Binary(ynn_binary_multiply, 6124, 6125, 2503);
  g->Matmul(2503, 2501, 2504, false, false);
}

// Scope: "Layer30 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer30AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(2504, 2505, {0,2,1,3});
  g->FuseDims(2505, 2506, 2, 2);
  g->Quantize(2506, 2507, 0.02399115078151226, 0);
  g->Transpose(6885, 4871, {1,0});
  g->Binary(ynn_binary_multiply, 4868, 4870, 4866);
  g->Dot(2507, 4871, YNN_INVALID_VALUE_ID, 4865, 1);
  g->DequantizeTensor(4865, YNN_INVALID_VALUE_ID, 4866, 4867);
  g->QuantizeTensor(4867, 6434, 4869, 2508);
  g->Dequantize(2508, 2509, 0.05247194319963455, 0);
}

// Scope: "Layer30 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer30Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2472, 2473);
  g->Reduce(ynn_reduce_sum, 2473, 6120, {2}, true);
  g->ShapeProduct(2473, 6119, {2});
  g->Binary(ynn_binary_divide, 6120, 6119, 2474);
  g->Binary(ynn_binary_add, 2474, 6469, 2475);
  g->Unary(ynn_unary_rsqrt, 2475, 2476);
  g->Binary(ynn_binary_multiply, 2472, 2476, 2477);
  g->Binary(ynn_binary_multiply, 2477, 6874, 2479);
  BuildLayer30AttentionQueryProjection(ctx);
  BuildLayer30AttentionSdpa(ctx);
  BuildLayer30AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2509, 2511);
  g->Reduce(ynn_reduce_sum, 2511, 6129, {2}, true);
  g->ShapeProduct(2511, 6128, {2});
  g->Binary(ynn_binary_divide, 6129, 6128, 2512);
  g->Binary(ynn_binary_add, 2512, 6469, 2513);
  g->Unary(ynn_unary_rsqrt, 2513, 2514);
  g->Binary(ynn_binary_multiply, 2509, 2514, 2515);
  g->Binary(ynn_binary_multiply, 2515, 6881, 2516);
  g->Binary(ynn_binary_add, 2516, 2472, 2517);
}

// Scope: "Layer30 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer30Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2517, 2518);
  g->Reduce(ynn_reduce_sum, 2518, 6131, {2}, true);
  g->ShapeProduct(2518, 6130, {2});
  g->Binary(ynn_binary_divide, 6131, 6130, 2519);
  g->Binary(ynn_binary_add, 2519, 6469, 2520);
  g->Unary(ynn_unary_rsqrt, 2520, 2522);
  g->Binary(ynn_binary_multiply, 2517, 2522, 2523);
  g->Binary(ynn_binary_multiply, 2523, 6884, 2524);
  g->Quantize(2524, 2525, 0.02257225476205349, 0);
  g->Transpose(6878, 4885, {1,0});
  g->Binary(ynn_binary_multiply, 4882, 4884, 4880);
  g->Dot(2525, 4885, YNN_INVALID_VALUE_ID, 4879, 1);
  g->DequantizeTensor(4879, YNN_INVALID_VALUE_ID, 4880, 4881);
  g->QuantizeTensor(4881, 6434, 4883, 2526);
  g->Dequantize(2526, 2527, 0.028789378702640533, 0);
  g->Transpose(6877, 4890, {1,0});
  g->Binary(ynn_binary_multiply, 4882, 4889, 4887);
  g->Dot(2525, 4890, YNN_INVALID_VALUE_ID, 4886, 1);
  g->DequantizeTensor(4886, YNN_INVALID_VALUE_ID, 4887, 4888);
  g->QuantizeTensor(4888, 6434, 4883, 2528);
  g->Dequantize(2528, 2529, 0.028789378702640533, 0);
  g->Polynomial(2529, 6134, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6134, 6135);
  g->Binary(ynn_binary_add, 6135, 5430, 6132);
  g->Binary(ynn_binary_multiply, 2529, 5428, 6133);
  g->Binary(ynn_binary_multiply, 6133, 6132, 2530);
  g->Binary(ynn_binary_multiply, 2527, 2530, 2532);
  g->Quantize(2532, 2533, 0.07234252989292145, 0);
  g->Transpose(6876, 4896, {1,0});
  g->Binary(ynn_binary_multiply, 4190, 4895, 4892);
  g->Dot(2533, 4896, YNN_INVALID_VALUE_ID, 4891, 1);
  g->DequantizeTensor(4891, YNN_INVALID_VALUE_ID, 4892, 4893);
  g->QuantizeTensor(4893, 6434, 4894, 2534);
  g->Dequantize(2534, 2535, 0.2192506492137909, 0);
  g->Unary(ynn_unary_square, 2535, 2536);
  g->Reduce(ynn_reduce_sum, 2536, 6137, {2}, true);
  g->ShapeProduct(2536, 6136, {2});
  g->Binary(ynn_binary_divide, 6137, 6136, 2537);
  g->Binary(ynn_binary_add, 2537, 6469, 2538);
  g->Unary(ynn_unary_rsqrt, 2538, 2539);
  g->Binary(ynn_binary_multiply, 2535, 2539, 2540);
  g->Binary(ynn_binary_multiply, 2540, 6882, 2541);
  g->Binary(ynn_binary_add, 2541, 2517, 2543);
}

// Scope: "Layer30 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer30PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(421, 2544, {0,0,30,0}, {-1,-1,1,-1});
  g->Reshape(2544, 2545, {1,1,256});
  g->Unary(ynn_unary_square, 2545, 2546);
  g->Reduce(ynn_reduce_sum, 2546, 6139, {2}, true);
  g->ShapeProduct(2546, 6138, {2});
  g->Binary(ynn_binary_divide, 6139, 6138, 2547);
  g->Binary(ynn_binary_add, 2547, 6469, 2548);
  g->Unary(ynn_unary_rsqrt, 2548, 2549);
  g->Binary(ynn_binary_multiply, 2545, 2549, 2550);
  g->Binary(ynn_binary_multiply, 2550, 7048, 2551);
  g->Binary(ynn_binary_multiply, 7073, 6472, 2552);
  g->Binary(ynn_binary_add, 2551, 2552, 2554);
  g->Binary(ynn_binary_multiply, 2554, 6466, 2555);
  g->Quantize(2543, 2556, 0.13473963737487793, 0);
  g->Transpose(6879, 4903, {1,0});
  g->Binary(ynn_binary_multiply, 4900, 4902, 4898);
  g->Dot(2556, 4903, YNN_INVALID_VALUE_ID, 4897, 1);
  g->DequantizeTensor(4897, YNN_INVALID_VALUE_ID, 4898, 4899);
  g->QuantizeTensor(4899, 6434, 4901, 2557);
  g->Dequantize(2557, 2558, 0.09596457332372665, 0);
  g->Polynomial(2558, 6144, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6144, 6145);
  g->Binary(ynn_binary_add, 6145, 5430, 6142);
  g->Binary(ynn_binary_multiply, 2558, 5428, 6143);
  g->Binary(ynn_binary_multiply, 6143, 6142, 2559);
  g->Binary(ynn_binary_multiply, 2559, 2555, 2560);
  g->Quantize(2560, 2561, 0.18700788915157318, 0);
  g->Transpose(6880, 4910, {1,0});
  g->Binary(ynn_binary_multiply, 4907, 4909, 4905);
  g->Dot(2561, 4910, YNN_INVALID_VALUE_ID, 4904, 1);
  g->DequantizeTensor(4904, YNN_INVALID_VALUE_ID, 4905, 4906);
  g->QuantizeTensor(4906, 6434, 4908, 2562);
  g->Dequantize(2562, 2563, 0.27509135007858276, 0);
  g->Unary(ynn_unary_square, 2563, 2566);
  g->Reduce(ynn_reduce_sum, 2566, 6147, {2}, true);
  g->ShapeProduct(2566, 6146, {2});
  g->Binary(ynn_binary_divide, 6147, 6146, 2567);
  g->Binary(ynn_binary_add, 2567, 6469, 2568);
  g->Unary(ynn_unary_rsqrt, 2568, 2569);
  g->Binary(ynn_binary_multiply, 2563, 2569, 2570);
  g->Binary(ynn_binary_multiply, 2570, 6883, 2571);
  g->Binary(ynn_binary_add, 2543, 2571, 2572);
  g->Binary(ynn_binary_multiply, 2572, 6875, 2573);
}

// Scope: "Layer30"
LAB_YNN_BUILDER_NOINLINE void BuildLayer30(Context& ctx) {
  BuildLayer30Attention(ctx);
  BuildLayer30Mlp(ctx);
  BuildLayer30PerLayerEmbedding(ctx);
}

// Scope: "Layer31 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer31AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(2580, 2581, 0.6227923035621643, 0);
  g->Transpose(6901, 4917, {1,0});
  g->Binary(ynn_binary_multiply, 4914, 4916, 4912);
  g->Dot(2581, 4917, YNN_INVALID_VALUE_ID, 4911, 1);
  g->DequantizeTensor(4911, YNN_INVALID_VALUE_ID, 4912, 4913);
  g->QuantizeTensor(4913, 6434, 4915, 2582);
  g->Dequantize(2582, 2583, 0.6574802994728088, 0);
  g->SplitDim(2583, 2584, 2, {8,256});
  g->Transpose(2584, 2585, {0,2,1,3});
  g->Unary(ynn_unary_square, 2585, 2586);
  g->Reduce(ynn_reduce_sum, 2586, 6151, {3}, true);
  g->ShapeProduct(2586, 6150, {3});
  g->Binary(ynn_binary_divide, 6151, 6150, 2588);
  g->Binary(ynn_binary_add, 2588, 6469, 2589);
  g->Unary(ynn_unary_rsqrt, 2589, 2590);
  g->Binary(ynn_binary_multiply, 2585, 2590, 2591);
  g->Binary(ynn_binary_multiply, 2591, 6900, 2592);
  g->Slice(2592, 2593, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2592, 2594, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2594, 2595);
  g->Concat({2595,2593}, 2596, 3);
  g->Binary(ynn_binary_multiply, 2592, 3009, 2597);
  g->Binary(ynn_binary_multiply, 2596, 3112, 2599);
  g->Binary(ynn_binary_add, 2597, 2599, 2600);
}

// Scope: "Layer31 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer31AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7120, 2601, 0.0059552486054599285, 0);
  g->Dequantize(7135, 2602, 0.047244105488061905, 0);
  g->Matmul(2600, 2601, 2603, false, true);
  g->Mask(2603, 6500, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6500, 6155, {-1}, true);
  g->Binary(ynn_binary_subtract, 6500, 6155, 6152);
  g->Unary(ynn_unary_exp, 6152, 6153);
  g->Reduce(ynn_reduce_sum, 6153, 6156, {-1}, true);
  g->Binary(ynn_binary_divide, 5430, 6156, 6154);
  g->Binary(ynn_binary_multiply, 6153, 6154, 2604);
  g->Matmul(2604, 2602, 2605, false, false);
}

// Scope: "Layer31 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer31AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(2605, 2606, {0,2,1,3});
  g->FuseDims(2606, 2607, 2, 2);
  g->Quantize(2607, 2609, 0.02399115078151226, 0);
  g->Transpose(6899, 4923, {1,0});
  g->Binary(ynn_binary_multiply, 4868, 4922, 4919);
  g->Dot(2609, 4923, YNN_INVALID_VALUE_ID, 4918, 1);
  g->DequantizeTensor(4918, YNN_INVALID_VALUE_ID, 4919, 4920);
  g->QuantizeTensor(4920, 6434, 4921, 2610);
  g->Dequantize(2610, 2611, 0.06142711639404297, 0);
}

// Scope: "Layer31 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer31Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2573, 2574);
  g->Reduce(ynn_reduce_sum, 2574, 6149, {2}, true);
  g->ShapeProduct(2574, 6148, {2});
  g->Binary(ynn_binary_divide, 6149, 6148, 2575);
  g->Binary(ynn_binary_add, 2575, 6469, 2577);
  g->Unary(ynn_unary_rsqrt, 2577, 2578);
  g->Binary(ynn_binary_multiply, 2573, 2578, 2579);
  g->Binary(ynn_binary_multiply, 2579, 6888, 2580);
  BuildLayer31AttentionQueryProjection(ctx);
  BuildLayer31AttentionSdpa(ctx);
  BuildLayer31AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2611, 2612);
  g->Reduce(ynn_reduce_sum, 2612, 6158, {2}, true);
  g->ShapeProduct(2612, 6157, {2});
  g->Binary(ynn_binary_divide, 6158, 6157, 2613);
  g->Binary(ynn_binary_add, 2613, 6469, 2614);
  g->Unary(ynn_unary_rsqrt, 2614, 2615);
  g->Binary(ynn_binary_multiply, 2611, 2615, 2616);
  g->Binary(ynn_binary_multiply, 2616, 6895, 2617);
  g->Binary(ynn_binary_add, 2617, 2573, 2618);
}

// Scope: "Layer31 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer31Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2618, 2620);
  g->Reduce(ynn_reduce_sum, 2620, 6160, {2}, true);
  g->ShapeProduct(2620, 6159, {2});
  g->Binary(ynn_binary_divide, 6160, 6159, 2621);
  g->Binary(ynn_binary_add, 2621, 6469, 2622);
  g->Unary(ynn_unary_rsqrt, 2622, 2623);
  g->Binary(ynn_binary_multiply, 2618, 2623, 2624);
  g->Binary(ynn_binary_multiply, 2624, 6898, 2625);
  g->Quantize(2625, 2626, 0.01708538644015789, 0);
  g->Transpose(6892, 4930, {1,0});
  g->Binary(ynn_binary_multiply, 4927, 4929, 4925);
  g->Dot(2626, 4930, YNN_INVALID_VALUE_ID, 4924, 1);
  g->DequantizeTensor(4924, YNN_INVALID_VALUE_ID, 4925, 4926);
  g->QuantizeTensor(4926, 6434, 4928, 2627);
  g->Dequantize(2627, 2628, 0.01771654561161995, 0);
  g->Transpose(6891, 4935, {1,0});
  g->Binary(ynn_binary_multiply, 4927, 4934, 4932);
  g->Dot(2626, 4935, YNN_INVALID_VALUE_ID, 4931, 1);
  g->DequantizeTensor(4931, YNN_INVALID_VALUE_ID, 4932, 4933);
  g->QuantizeTensor(4933, 6434, 4928, 2630);
  g->Dequantize(2630, 2631, 0.01771654561161995, 0);
  g->Polynomial(2631, 6165, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6165, 6166);
  g->Binary(ynn_binary_add, 6166, 5430, 6163);
  g->Binary(ynn_binary_multiply, 2631, 5428, 6164);
  g->Binary(ynn_binary_multiply, 6164, 6163, 2632);
  g->Binary(ynn_binary_multiply, 2628, 2632, 2633);
  g->Quantize(2633, 2634, 0.027189970016479492, 0);
  g->Transpose(6890, 4942, {1,0});
  g->Binary(ynn_binary_multiply, 4939, 4941, 4937);
  g->Dot(2634, 4942, YNN_INVALID_VALUE_ID, 4936, 1);
  g->DequantizeTensor(4936, YNN_INVALID_VALUE_ID, 4937, 4938);
  g->QuantizeTensor(4938, 6434, 4940, 2635);
  g->Dequantize(2635, 2636, 0.11200025677680969, 0);
  g->Unary(ynn_unary_square, 2636, 2637);
  g->Reduce(ynn_reduce_sum, 2637, 6168, {2}, true);
  g->ShapeProduct(2637, 6167, {2});
  g->Binary(ynn_binary_divide, 6168, 6167, 2638);
  g->Binary(ynn_binary_add, 2638, 6469, 2639);
  g->Unary(ynn_unary_rsqrt, 2639, 2641);
  g->Binary(ynn_binary_multiply, 2636, 2641, 2642);
  g->Binary(ynn_binary_multiply, 2642, 6896, 2643);
  g->Binary(ynn_binary_add, 2643, 2618, 2644);
}

// Scope: "Layer31 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer31PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(421, 2645, {0,0,31,0}, {-1,-1,1,-1});
  g->Reshape(2645, 2646, {1,1,256});
  g->Unary(ynn_unary_square, 2646, 2647);
  g->Reduce(ynn_reduce_sum, 2647, 6170, {2}, true);
  g->ShapeProduct(2647, 6169, {2});
  g->Binary(ynn_binary_divide, 6170, 6169, 2648);
  g->Binary(ynn_binary_add, 2648, 6469, 2649);
  g->Unary(ynn_unary_rsqrt, 2649, 2650);
  g->Binary(ynn_binary_multiply, 2646, 2650, 2652);
  g->Binary(ynn_binary_multiply, 2652, 7048, 2653);
  g->Binary(ynn_binary_multiply, 7074, 6472, 2654);
  g->Binary(ynn_binary_add, 2653, 2654, 2655);
  g->Binary(ynn_binary_multiply, 2655, 6466, 2656);
  g->Quantize(2644, 2657, 0.1916448324918747, 0);
  g->Transpose(6893, 4948, {1,0});
  g->Binary(ynn_binary_multiply, 4946, 4947, 4944);
  g->Dot(2657, 4948, YNN_INVALID_VALUE_ID, 4943, 1);
  g->DequantizeTensor(4943, YNN_INVALID_VALUE_ID, 4944, 4945);
  g->QuantizeTensor(4945, 6434, 4757, 2658);
  g->Dequantize(2658, 2659, 0.07578741014003754, 0);
  g->Polynomial(2659, 6173, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6173, 6174);
  g->Binary(ynn_binary_add, 6174, 5430, 6171);
  g->Binary(ynn_binary_multiply, 2659, 5428, 6172);
  g->Binary(ynn_binary_multiply, 6172, 6171, 2660);
  g->Binary(ynn_binary_multiply, 2660, 2656, 2661);
  g->Quantize(2661, 2663, 0.24507875740528107, 0);
  g->Transpose(6894, 4955, {1,0});
  g->Binary(ynn_binary_multiply, 4952, 4954, 4950);
  g->Dot(2663, 4955, YNN_INVALID_VALUE_ID, 4949, 1);
  g->DequantizeTensor(4949, YNN_INVALID_VALUE_ID, 4950, 4951);
  g->QuantizeTensor(4951, 6434, 4953, 2664);
  g->Dequantize(2664, 2665, 0.3233283758163452, 0);
  g->Unary(ynn_unary_square, 2665, 2666);
  g->Reduce(ynn_reduce_sum, 2666, 6176, {2}, true);
  g->ShapeProduct(2666, 6175, {2});
  g->Binary(ynn_binary_divide, 6176, 6175, 2667);
  g->Binary(ynn_binary_add, 2667, 6469, 2668);
  g->Unary(ynn_unary_rsqrt, 2668, 2669);
  g->Binary(ynn_binary_multiply, 2665, 2669, 2670);
  g->Binary(ynn_binary_multiply, 2670, 6897, 2671);
  g->Binary(ynn_binary_add, 2644, 2671, 2672);
  g->Binary(ynn_binary_multiply, 2672, 6889, 2675);
}

// Scope: "Layer31"
LAB_YNN_BUILDER_NOINLINE void BuildLayer31(Context& ctx) {
  BuildLayer31Attention(ctx);
  BuildLayer31Mlp(ctx);
  BuildLayer31PerLayerEmbedding(ctx);
}

// Scope: "Layer32 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer32AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(2681, 2682, 0.6824333071708679, 0);
  g->Transpose(6915, 4962, {1,0});
  g->Binary(ynn_binary_multiply, 4959, 4961, 4957);
  g->Dot(2682, 4962, YNN_INVALID_VALUE_ID, 4956, 1);
  g->DequantizeTensor(4956, YNN_INVALID_VALUE_ID, 4957, 4958);
  g->QuantizeTensor(4958, 6434, 4960, 2683);
  g->Dequantize(2683, 2684, 0.4645669162273407, 0);
  g->SplitDim(2684, 2686, 2, {8,256});
  g->Transpose(2686, 2687, {0,2,1,3});
  g->Unary(ynn_unary_square, 2687, 2688);
  g->Reduce(ynn_reduce_sum, 2688, 6180, {3}, true);
  g->ShapeProduct(2688, 6179, {3});
  g->Binary(ynn_binary_divide, 6180, 6179, 2689);
  g->Binary(ynn_binary_add, 2689, 6469, 2690);
  g->Unary(ynn_unary_rsqrt, 2690, 2691);
  g->Binary(ynn_binary_multiply, 2687, 2691, 2692);
  g->Binary(ynn_binary_multiply, 2692, 6914, 2693);
  g->Slice(2693, 2694, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2693, 2695, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2695, 2697);
  g->Concat({2697,2694}, 2698, 3);
  g->Binary(ynn_binary_multiply, 2693, 3009, 2699);
  g->Binary(ynn_binary_multiply, 2698, 3112, 2700);
  g->Binary(ynn_binary_add, 2699, 2700, 2701);
}

// Scope: "Layer32 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer32AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7120, 2702, 0.0059552486054599285, 0);
  g->Dequantize(7135, 2703, 0.047244105488061905, 0);
  g->Matmul(2701, 2702, 2704, false, true);
  g->Mask(2704, 6501, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6501, 6184, {-1}, true);
  g->Binary(ynn_binary_subtract, 6501, 6184, 6181);
  g->Unary(ynn_unary_exp, 6181, 6182);
  g->Reduce(ynn_reduce_sum, 6182, 6185, {-1}, true);
  g->Binary(ynn_binary_divide, 5430, 6185, 6183);
  g->Binary(ynn_binary_multiply, 6182, 6183, 2705);
  g->Matmul(2705, 2703, 2707, false, false);
}

// Scope: "Layer32 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer32AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(2707, 2708, {0,2,1,3});
  g->FuseDims(2708, 2709, 2, 2);
  g->Quantize(2709, 2710, 0.023006899282336235, 0);
  g->Transpose(6913, 4975, {1,0});
  g->Binary(ynn_binary_multiply, 4264, 4974, 4971);
  g->Dot(2710, 4975, YNN_INVALID_VALUE_ID, 4970, 1);
  g->DequantizeTensor(4970, YNN_INVALID_VALUE_ID, 4971, 4972);
  g->QuantizeTensor(4972, 6434, 4973, 2711);
  g->Dequantize(2711, 2712, 0.056797921657562256, 0);
}

// Scope: "Layer32 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer32Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2675, 2676);
  g->Reduce(ynn_reduce_sum, 2676, 6178, {2}, true);
  g->ShapeProduct(2676, 6177, {2});
  g->Binary(ynn_binary_divide, 6178, 6177, 2677);
  g->Binary(ynn_binary_add, 2677, 6469, 2678);
  g->Unary(ynn_unary_rsqrt, 2678, 2679);
  g->Binary(ynn_binary_multiply, 2675, 2679, 2680);
  g->Binary(ynn_binary_multiply, 2680, 6902, 2681);
  BuildLayer32AttentionQueryProjection(ctx);
  BuildLayer32AttentionSdpa(ctx);
  BuildLayer32AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2712, 2713);
  g->Reduce(ynn_reduce_sum, 2713, 6187, {2}, true);
  g->ShapeProduct(2713, 6186, {2});
  g->Binary(ynn_binary_divide, 6187, 6186, 2714);
  g->Binary(ynn_binary_add, 2714, 6469, 2715);
  g->Unary(ynn_unary_rsqrt, 2715, 2716);
  g->Binary(ynn_binary_multiply, 2712, 2716, 2717);
  g->Binary(ynn_binary_multiply, 2717, 6909, 2718);
  g->Binary(ynn_binary_add, 2718, 2675, 2719);
}

// Scope: "Layer32 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer32Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2719, 2720);
  g->Reduce(ynn_reduce_sum, 2720, 6189, {2}, true);
  g->ShapeProduct(2720, 6188, {2});
  g->Binary(ynn_binary_divide, 6189, 6188, 2721);
  g->Binary(ynn_binary_add, 2721, 6469, 2722);
  g->Unary(ynn_unary_rsqrt, 2722, 2723);
  g->Binary(ynn_binary_multiply, 2719, 2723, 2724);
  g->Binary(ynn_binary_multiply, 2724, 6912, 2725);
  g->Quantize(2725, 2726, 0.014212466776371002, 0);
  g->Transpose(6906, 4987, {1,0});
  g->Binary(ynn_binary_multiply, 4984, 4986, 4982);
  g->Dot(2726, 4987, YNN_INVALID_VALUE_ID, 4981, 1);
  g->DequantizeTensor(4981, YNN_INVALID_VALUE_ID, 4982, 4983);
  g->QuantizeTensor(4983, 6434, 4985, 2728);
  g->Dequantize(2728, 2729, 0.019192922860383987, 0);
  g->Transpose(6905, 4992, {1,0});
  g->Binary(ynn_binary_multiply, 4984, 4991, 4989);
  g->Dot(2726, 4992, YNN_INVALID_VALUE_ID, 4988, 1);
  g->DequantizeTensor(4988, YNN_INVALID_VALUE_ID, 4989, 4990);
  g->QuantizeTensor(4990, 6434, 4985, 2730);
  g->Dequantize(2730, 2731, 0.019192922860383987, 0);
  g->Polynomial(2731, 6192, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6192, 6193);
  g->Binary(ynn_binary_add, 6193, 5430, 6190);
  g->Binary(ynn_binary_multiply, 2731, 5428, 6191);
  g->Binary(ynn_binary_multiply, 6191, 6190, 2732);
  g->Binary(ynn_binary_multiply, 2729, 2732, 2733);
  g->Quantize(2733, 2734, 0.025221465155482292, 0);
  g->Transpose(6904, 4998, {1,0});
  g->Binary(ynn_binary_multiply, 4422, 4997, 4994);
  g->Dot(2734, 4998, YNN_INVALID_VALUE_ID, 4993, 1);
  g->DequantizeTensor(4993, YNN_INVALID_VALUE_ID, 4994, 4995);
  g->QuantizeTensor(4995, 6434, 4996, 2735);
  g->Dequantize(2735, 2736, 0.07002133876085281, 0);
  g->Unary(ynn_unary_square, 2736, 2738);
  g->Reduce(ynn_reduce_sum, 2738, 6195, {2}, true);
  g->ShapeProduct(2738, 6194, {2});
  g->Binary(ynn_binary_divide, 6195, 6194, 2739);
  g->Binary(ynn_binary_add, 2739, 6469, 2740);
  g->Unary(ynn_unary_rsqrt, 2740, 2741);
  g->Binary(ynn_binary_multiply, 2736, 2741, 2742);
  g->Binary(ynn_binary_multiply, 2742, 6910, 2743);
  g->Binary(ynn_binary_add, 2743, 2719, 2744);
}

// Scope: "Layer32 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer32PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(421, 2745, {0,0,32,0}, {-1,-1,1,-1});
  g->Reshape(2745, 2746, {1,1,256});
  g->Unary(ynn_unary_square, 2746, 2747);
  g->Reduce(ynn_reduce_sum, 2747, 6201, {2}, true);
  g->ShapeProduct(2747, 6200, {2});
  g->Binary(ynn_binary_divide, 6201, 6200, 2749);
  g->Binary(ynn_binary_add, 2749, 6469, 2750);
  g->Unary(ynn_unary_rsqrt, 2750, 2751);
  g->Binary(ynn_binary_multiply, 2746, 2751, 2752);
  g->Binary(ynn_binary_multiply, 2752, 7048, 2753);
  g->Binary(ynn_binary_multiply, 7075, 6472, 2754);
  g->Binary(ynn_binary_add, 2753, 2754, 2755);
  g->Binary(ynn_binary_multiply, 2755, 6466, 2756);
  g->Quantize(2744, 2757, 0.19188754260540009, 0);
  g->Transpose(6907, 5004, {1,0});
  g->Binary(ynn_binary_multiply, 5002, 5003, 5000);
  g->Dot(2757, 5004, YNN_INVALID_VALUE_ID, 4999, 1);
  g->DequantizeTensor(4999, YNN_INVALID_VALUE_ID, 5000, 5001);
  g->QuantizeTensor(5001, 6434, 4743, 2758);
  g->Dequantize(2758, 2760, 0.09104331582784653, 0);
  g->Polynomial(2760, 6204, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6204, 6205);
  g->Binary(ynn_binary_add, 6205, 5430, 6202);
  g->Binary(ynn_binary_multiply, 2760, 5428, 6203);
  g->Binary(ynn_binary_multiply, 6203, 6202, 2761);
  g->Binary(ynn_binary_multiply, 2761, 2756, 2762);
  g->Quantize(2762, 2763, 0.18700788915157318, 0);
  g->Transpose(6908, 5010, {1,0});
  g->Binary(ynn_binary_multiply, 4907, 5009, 5006);
  g->Dot(2763, 5010, YNN_INVALID_VALUE_ID, 5005, 1);
  g->DequantizeTensor(5005, YNN_INVALID_VALUE_ID, 5006, 5007);
  g->QuantizeTensor(5007, 6434, 5008, 2764);
  g->Dequantize(2764, 2765, 0.21407830715179443, 0);
  g->Unary(ynn_unary_square, 2765, 2766);
  g->Reduce(ynn_reduce_sum, 2766, 6207, {2}, true);
  g->ShapeProduct(2766, 6206, {2});
  g->Binary(ynn_binary_divide, 6207, 6206, 2767);
  g->Binary(ynn_binary_add, 2767, 6469, 2768);
  g->Unary(ynn_unary_rsqrt, 2768, 2769);
  g->Binary(ynn_binary_multiply, 2765, 2769, 2771);
  g->Binary(ynn_binary_multiply, 2771, 6911, 2772);
  g->Binary(ynn_binary_add, 2744, 2772, 2773);
  g->Binary(ynn_binary_multiply, 2773, 6903, 2774);
}

// Scope: "Layer32"
LAB_YNN_BUILDER_NOINLINE void BuildLayer32(Context& ctx) {
  BuildLayer32Attention(ctx);
  BuildLayer32Mlp(ctx);
  BuildLayer32PerLayerEmbedding(ctx);
}

// Scope: "Layer33 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer33AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(2780, 2783, 0.9355496764183044, 0);
  g->Transpose(6929, 5024, {1,0});
  g->Binary(ynn_binary_multiply, 5021, 5023, 5019);
  g->Dot(2783, 5024, YNN_INVALID_VALUE_ID, 5018, 1);
  g->DequantizeTensor(5018, YNN_INVALID_VALUE_ID, 5019, 5020);
  g->QuantizeTensor(5020, 6434, 5022, 2784);
  g->Dequantize(2784, 2785, 0.33464565873146057, 0);
  g->SplitDim(2785, 2786, 2, {8,256});
  g->Transpose(2786, 2787, {0,2,1,3});
  g->Unary(ynn_unary_square, 2787, 2788);
  g->Reduce(ynn_reduce_sum, 2788, 6211, {3}, true);
  g->ShapeProduct(2788, 6210, {3});
  g->Binary(ynn_binary_divide, 6211, 6210, 2789);
  g->Binary(ynn_binary_add, 2789, 6469, 2790);
  g->Unary(ynn_unary_rsqrt, 2790, 2791);
  g->Binary(ynn_binary_multiply, 2787, 2791, 2792);
  g->Binary(ynn_binary_multiply, 2792, 6928, 2794);
  g->Slice(2794, 2795, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2794, 2796, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2796, 2797);
  g->Concat({2797,2795}, 2798, 3);
  g->Binary(ynn_binary_multiply, 2794, 3009, 2799);
  g->Binary(ynn_binary_multiply, 2798, 3112, 2800);
  g->Binary(ynn_binary_add, 2799, 2800, 2801);
}

// Scope: "Layer33 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer33AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7120, 2802, 0.0059552486054599285, 0);
  g->Dequantize(7135, 2803, 0.047244105488061905, 0);
  g->Matmul(2801, 2802, 2805, false, true);
  g->Mask(2805, 6502, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6502, 6215, {-1}, true);
  g->Binary(ynn_binary_subtract, 6502, 6215, 6212);
  g->Unary(ynn_unary_exp, 6212, 6213);
  g->Reduce(ynn_reduce_sum, 6213, 6216, {-1}, true);
  g->Binary(ynn_binary_divide, 5430, 6216, 6214);
  g->Binary(ynn_binary_multiply, 6213, 6214, 2806);
  g->Matmul(2806, 2803, 2807, false, false);
}

// Scope: "Layer33 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer33AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(2807, 2808, {0,2,1,3});
  g->FuseDims(2808, 2809, 2, 2);
  g->Quantize(2809, 2810, 0.02276083640754223, 0);
  g->Transpose(6927, 5030, {1,0});
  g->Binary(ynn_binary_multiply, 4383, 5029, 5026);
  g->Dot(2810, 5030, YNN_INVALID_VALUE_ID, 5025, 1);
  g->DequantizeTensor(5025, YNN_INVALID_VALUE_ID, 5026, 5027);
  g->QuantizeTensor(5027, 6434, 5028, 2811);
  g->Dequantize(2811, 2812, 0.02861599810421467, 0);
}

// Scope: "Layer33 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer33Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2774, 2775);
  g->Reduce(ynn_reduce_sum, 2775, 6209, {2}, true);
  g->ShapeProduct(2775, 6208, {2});
  g->Binary(ynn_binary_divide, 6209, 6208, 2776);
  g->Binary(ynn_binary_add, 2776, 6469, 2777);
  g->Unary(ynn_unary_rsqrt, 2777, 2778);
  g->Binary(ynn_binary_multiply, 2774, 2778, 2779);
  g->Binary(ynn_binary_multiply, 2779, 6916, 2780);
  BuildLayer33AttentionQueryProjection(ctx);
  BuildLayer33AttentionSdpa(ctx);
  BuildLayer33AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2812, 2813);
  g->Reduce(ynn_reduce_sum, 2813, 6220, {2}, true);
  g->ShapeProduct(2813, 6219, {2});
  g->Binary(ynn_binary_divide, 6220, 6219, 2815);
  g->Binary(ynn_binary_add, 2815, 6469, 2816);
  g->Unary(ynn_unary_rsqrt, 2816, 2817);
  g->Binary(ynn_binary_multiply, 2812, 2817, 2818);
  g->Binary(ynn_binary_multiply, 2818, 6923, 2819);
  g->Binary(ynn_binary_add, 2819, 2774, 2820);
}

// Scope: "Layer33 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer33Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2820, 2821);
  g->Reduce(ynn_reduce_sum, 2821, 6222, {2}, true);
  g->ShapeProduct(2821, 6221, {2});
  g->Binary(ynn_binary_divide, 6222, 6221, 2822);
  g->Binary(ynn_binary_add, 2822, 6469, 2823);
  g->Unary(ynn_unary_rsqrt, 2823, 2824);
  g->Binary(ynn_binary_multiply, 2820, 2824, 2826);
  g->Binary(ynn_binary_multiply, 2826, 6926, 2827);
  g->Quantize(2827, 2828, 0.016980575397610664, 0);
  g->Transpose(6920, 5037, {1,0});
  g->Binary(ynn_binary_multiply, 5034, 5036, 5032);
  g->Dot(2828, 5037, YNN_INVALID_VALUE_ID, 5031, 1);
  g->DequantizeTensor(5031, YNN_INVALID_VALUE_ID, 5032, 5033);
  g->QuantizeTensor(5033, 6434, 5035, 2829);
  g->Dequantize(2829, 2830, 0.018700797110795975, 0);
  g->Transpose(6919, 5042, {1,0});
  g->Binary(ynn_binary_multiply, 5034, 5041, 5039);
  g->Dot(2828, 5042, YNN_INVALID_VALUE_ID, 5038, 1);
  g->DequantizeTensor(5038, YNN_INVALID_VALUE_ID, 5039, 5040);
  g->QuantizeTensor(5040, 6434, 5035, 2831);
  g->Dequantize(2831, 2832, 0.018700797110795975, 0);
  g->Polynomial(2832, 6225, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6225, 6226);
  g->Binary(ynn_binary_add, 6226, 5430, 6223);
  g->Binary(ynn_binary_multiply, 2832, 5428, 6224);
  g->Binary(ynn_binary_multiply, 6224, 6223, 2833);
  g->Binary(ynn_binary_multiply, 2830, 2833, 2834);
  g->Quantize(2834, 2836, 0.02989666350185871, 0);
  g->Transpose(6918, 5049, {1,0});
  g->Binary(ynn_binary_multiply, 5046, 5048, 5044);
  g->Dot(2836, 5049, YNN_INVALID_VALUE_ID, 5043, 1);
  g->DequantizeTensor(5043, YNN_INVALID_VALUE_ID, 5044, 5045);
  g->QuantizeTensor(5045, 6434, 5047, 2837);
  g->Dequantize(2837, 2838, 0.053163815289735794, 0);
  g->Unary(ynn_unary_square, 2838, 2839);
  g->Reduce(ynn_reduce_sum, 2839, 6228, {2}, true);
  g->ShapeProduct(2839, 6227, {2});
  g->Binary(ynn_binary_divide, 6228, 6227, 2840);
  g->Binary(ynn_binary_add, 2840, 6469, 2841);
  g->Unary(ynn_unary_rsqrt, 2841, 2842);
  g->Binary(ynn_binary_multiply, 2838, 2842, 2843);
  g->Binary(ynn_binary_multiply, 2843, 6924, 2844);
  g->Binary(ynn_binary_add, 2844, 2820, 2845);
}

// Scope: "Layer33 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer33PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(421, 2847, {0,0,33,0}, {-1,-1,1,-1});
  g->Reshape(2847, 2848, {1,1,256});
  g->Unary(ynn_unary_square, 2848, 2849);
  g->Reduce(ynn_reduce_sum, 2849, 6230, {2}, true);
  g->ShapeProduct(2849, 6229, {2});
  g->Binary(ynn_binary_divide, 6230, 6229, 2850);
  g->Binary(ynn_binary_add, 2850, 6469, 2851);
  g->Unary(ynn_unary_rsqrt, 2851, 2852);
  g->Binary(ynn_binary_multiply, 2848, 2852, 2853);
  g->Binary(ynn_binary_multiply, 2853, 7048, 2854);
  g->Binary(ynn_binary_multiply, 7076, 6472, 2855);
  g->Binary(ynn_binary_add, 2854, 2855, 2856);
  g->Binary(ynn_binary_multiply, 2856, 6466, 2858);
  g->Quantize(2845, 2859, 0.13243837654590607, 0);
  g->Transpose(6921, 5056, {1,0});
  g->Binary(ynn_binary_multiply, 5053, 5055, 5051);
  g->Dot(2859, 5056, YNN_INVALID_VALUE_ID, 5050, 1);
  g->DequantizeTensor(5050, YNN_INVALID_VALUE_ID, 5051, 5052);
  g->QuantizeTensor(5052, 6434, 5054, 2860);
  g->Dequantize(2860, 2861, 0.1446850597858429, 0);
  g->Polynomial(2861, 6233, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6233, 6234);
  g->Binary(ynn_binary_add, 6234, 5430, 6231);
  g->Binary(ynn_binary_multiply, 2861, 5428, 6232);
  g->Binary(ynn_binary_multiply, 6232, 6231, 2862);
  g->Binary(ynn_binary_multiply, 2862, 2858, 2863);
  g->Quantize(2863, 2864, 1.5826771259307861, 0);
  g->Transpose(6922, 5063, {1,0});
  g->Binary(ynn_binary_multiply, 5060, 5062, 5058);
  g->Dot(2864, 5063, YNN_INVALID_VALUE_ID, 5057, 1);
  g->DequantizeTensor(5057, YNN_INVALID_VALUE_ID, 5058, 5059);
  g->QuantizeTensor(5059, 6434, 5061, 2865);
  g->Dequantize(2865, 2866, 0.6353945732116699, 0);
  g->Unary(ynn_unary_square, 2866, 2867);
  g->Reduce(ynn_reduce_sum, 2867, 6236, {2}, true);
  g->ShapeProduct(2867, 6235, {2});
  g->Binary(ynn_binary_divide, 6236, 6235, 2869);
  g->Binary(ynn_binary_add, 2869, 6469, 2870);
  g->Unary(ynn_unary_rsqrt, 2870, 2871);
  g->Binary(ynn_binary_multiply, 2866, 2871, 2872);
  g->Binary(ynn_binary_multiply, 2872, 6925, 2873);
  g->Binary(ynn_binary_add, 2845, 2873, 2874);
  g->Binary(ynn_binary_multiply, 2874, 6917, 2875);
}

// Scope: "Layer33"
LAB_YNN_BUILDER_NOINLINE void BuildLayer33(Context& ctx) {
  BuildLayer33Attention(ctx);
  BuildLayer33Mlp(ctx);
  BuildLayer33PerLayerEmbedding(ctx);
}

// Scope: "Layer34 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer34AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(2882, 2883, 1.450958251953125, 0);
  g->Transpose(6943, 5070, {1,0});
  g->Binary(ynn_binary_multiply, 5067, 5069, 5065);
  g->Dot(2883, 5070, YNN_INVALID_VALUE_ID, 5064, 1);
  g->DequantizeTensor(5064, YNN_INVALID_VALUE_ID, 5065, 5066);
  g->QuantizeTensor(5066, 6434, 5068, 2884);
  g->Dequantize(2884, 2885, 0.6535432934761047, 0);
  g->SplitDim(2885, 2886, 2, {8,512});
  g->Transpose(2886, 2887, {0,2,1,3});
  g->Unary(ynn_unary_square, 2887, 2888);
  g->Reduce(ynn_reduce_sum, 2888, 6240, {3}, true);
  g->ShapeProduct(2888, 6239, {3});
  g->Binary(ynn_binary_divide, 6240, 6239, 2889);
  g->Binary(ynn_binary_add, 2889, 6469, 2892);
  g->Unary(ynn_unary_rsqrt, 2892, 2893);
  g->Binary(ynn_binary_multiply, 2887, 2893, 2894);
  g->Binary(ynn_binary_multiply, 2894, 6942, 2895);
  g->Slice(2895, 2896, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(2895, 2897, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 2897, 2898);
  g->Concat({2898,2896}, 2899, 3);
  g->Binary(ynn_binary_multiply, 2895, 3526, 2900);
  g->Binary(ynn_binary_multiply, 2899, 2, 2901);
  g->Binary(ynn_binary_add, 2900, 2901, 2903);
}

// Scope: "Layer34 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer34AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7121, 2904, 0.001091228099539876, 0);
  g->Dequantize(7136, 2905, 0.01785714365541935, 0);
  g->Matmul(2903, 2904, 2906, false, true);
  g->Mask(2906, 6503, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 6503, 6244, {-1}, true);
  g->Binary(ynn_binary_subtract, 6503, 6244, 6241);
  g->Unary(ynn_unary_exp, 6241, 6242);
  g->Reduce(ynn_reduce_sum, 6242, 6245, {-1}, true);
  g->Binary(ynn_binary_divide, 5430, 6245, 6243);
  g->Binary(ynn_binary_multiply, 6242, 6243, 2907);
  g->Matmul(2907, 2905, 2908, false, false);
}

// Scope: "Layer34 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer34AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(2908, 2909, {0,2,1,3});
  g->FuseDims(2909, 2910, 2, 2);
  g->Quantize(2910, 2911, 0.012118612416088581, 0);
  g->Transpose(6941, 5077, {1,0});
  g->Binary(ynn_binary_multiply, 5074, 5076, 5072);
  g->Dot(2911, 5077, YNN_INVALID_VALUE_ID, 5071, 1);
  g->DequantizeTensor(5071, YNN_INVALID_VALUE_ID, 5072, 5073);
  g->QuantizeTensor(5073, 6434, 5075, 2913);
  g->Dequantize(2913, 2914, 0.017325349152088165, 0);
}

// Scope: "Layer34 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer34Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2875, 2876);
  g->Reduce(ynn_reduce_sum, 2876, 6238, {2}, true);
  g->ShapeProduct(2876, 6237, {2});
  g->Binary(ynn_binary_divide, 6238, 6237, 2877);
  g->Binary(ynn_binary_add, 2877, 6469, 2878);
  g->Unary(ynn_unary_rsqrt, 2878, 2880);
  g->Binary(ynn_binary_multiply, 2875, 2880, 2881);
  g->Binary(ynn_binary_multiply, 2881, 6930, 2882);
  BuildLayer34AttentionQueryProjection(ctx);
  BuildLayer34AttentionSdpa(ctx);
  BuildLayer34AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2914, 2915);
  g->Reduce(ynn_reduce_sum, 2915, 6249, {2}, true);
  g->ShapeProduct(2915, 6248, {2});
  g->Binary(ynn_binary_divide, 6249, 6248, 2916);
  g->Binary(ynn_binary_add, 2916, 6469, 2917);
  g->Unary(ynn_unary_rsqrt, 2917, 2918);
  g->Binary(ynn_binary_multiply, 2914, 2918, 2919);
  g->Binary(ynn_binary_multiply, 2919, 6937, 2920);
  g->Binary(ynn_binary_add, 2920, 2875, 2921);
}

// Scope: "Layer34 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer34Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2921, 2922);
  g->Reduce(ynn_reduce_sum, 2922, 6251, {2}, true);
  g->ShapeProduct(2922, 6250, {2});
  g->Binary(ynn_binary_divide, 6251, 6250, 2924);
  g->Binary(ynn_binary_add, 2924, 6469, 2925);
  g->Unary(ynn_unary_rsqrt, 2925, 2926);
  g->Binary(ynn_binary_multiply, 2921, 2926, 2927);
  g->Binary(ynn_binary_multiply, 2927, 6940, 2928);
  g->Quantize(2928, 2929, 0.022695079445838928, 0);
  g->Transpose(6934, 5084, {1,0});
  g->Binary(ynn_binary_multiply, 5081, 5083, 5079);
  g->Dot(2929, 5084, YNN_INVALID_VALUE_ID, 5078, 1);
  g->DequantizeTensor(5078, YNN_INVALID_VALUE_ID, 5079, 5080);
  g->QuantizeTensor(5080, 6434, 5082, 2930);
  g->Dequantize(2930, 2931, 0.039862215518951416, 0);
  g->Transpose(6933, 5089, {1,0});
  g->Binary(ynn_binary_multiply, 5081, 5088, 5086);
  g->Dot(2929, 5089, YNN_INVALID_VALUE_ID, 5085, 1);
  g->DequantizeTensor(5085, YNN_INVALID_VALUE_ID, 5086, 5087);
  g->QuantizeTensor(5087, 6434, 5082, 2932);
  g->Dequantize(2932, 2934, 0.039862215518951416, 0);
  g->Polynomial(2934, 6254, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6254, 6255);
  g->Binary(ynn_binary_add, 6255, 5430, 6252);
  g->Binary(ynn_binary_multiply, 2934, 5428, 6253);
  g->Binary(ynn_binary_multiply, 6253, 6252, 2935);
  g->Binary(ynn_binary_multiply, 2931, 2935, 2936);
  g->Quantize(2936, 2937, 0.09940945357084274, 0);
  g->Transpose(6932, 5096, {1,0});
  g->Binary(ynn_binary_multiply, 5093, 5095, 5091);
  g->Dot(2937, 5096, YNN_INVALID_VALUE_ID, 5090, 1);
  g->DequantizeTensor(5090, YNN_INVALID_VALUE_ID, 5091, 5092);
  g->QuantizeTensor(5092, 6434, 5094, 2938);
  g->Dequantize(2938, 2939, 0.1543705314397812, 0);
  g->Unary(ynn_unary_square, 2939, 2940);
  g->Reduce(ynn_reduce_sum, 2940, 6257, {2}, true);
  g->ShapeProduct(2940, 6256, {2});
  g->Binary(ynn_binary_divide, 6257, 6256, 2941);
  g->Binary(ynn_binary_add, 2941, 6469, 2942);
  g->Unary(ynn_unary_rsqrt, 2942, 2943);
  g->Binary(ynn_binary_multiply, 2939, 2943, 2945);
  g->Binary(ynn_binary_multiply, 2945, 6938, 2946);
  g->Binary(ynn_binary_add, 2946, 2921, 2947);
}

// Scope: "Layer34 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer34PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(421, 2948, {0,0,34,0}, {-1,-1,1,-1});
  g->Reshape(2948, 2949, {1,1,256});
  g->Unary(ynn_unary_square, 2949, 2950);
  g->Reduce(ynn_reduce_sum, 2950, 6259, {2}, true);
  g->ShapeProduct(2950, 6258, {2});
  g->Binary(ynn_binary_divide, 6259, 6258, 2951);
  g->Binary(ynn_binary_add, 2951, 6469, 2952);
  g->Unary(ynn_unary_rsqrt, 2952, 2953);
  g->Binary(ynn_binary_multiply, 2949, 2953, 2954);
  g->Binary(ynn_binary_multiply, 2954, 7048, 2956);
  g->Binary(ynn_binary_multiply, 7077, 6472, 2957);
  g->Binary(ynn_binary_add, 2956, 2957, 2958);
  g->Binary(ynn_binary_multiply, 2958, 6466, 2959);
  g->Quantize(2947, 2960, 0.8795163035392761, 0);
  g->Transpose(6935, 5103, {1,0});
  g->Binary(ynn_binary_multiply, 5100, 5102, 5098);
  g->Dot(2960, 5103, YNN_INVALID_VALUE_ID, 5097, 1);
  g->DequantizeTensor(5097, YNN_INVALID_VALUE_ID, 5098, 5099);
  g->QuantizeTensor(5099, 6434, 5101, 2961);
  g->Dequantize(2961, 2962, 0.16633859276771545, 0);
  g->Polynomial(2962, 6262, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6262, 6263);
  g->Binary(ynn_binary_add, 6263, 5430, 6260);
  g->Binary(ynn_binary_multiply, 2962, 5428, 6261);
  g->Binary(ynn_binary_multiply, 6261, 6260, 2963);
  g->Binary(ynn_binary_multiply, 2963, 2959, 2964);
  g->Quantize(2964, 2965, 3.2125983238220215, 0);
  g->Transpose(6936, 5110, {1,0});
  g->Binary(ynn_binary_multiply, 5107, 5109, 5105);
  g->Dot(2965, 5110, YNN_INVALID_VALUE_ID, 5104, 1);
  g->DequantizeTensor(5104, YNN_INVALID_VALUE_ID, 5105, 5106);
  g->QuantizeTensor(5106, 6434, 5108, 2967);
  g->Dequantize(2967, 2968, 1.0930962562561035, 0);
  g->Unary(ynn_unary_square, 2968, 2969);
  g->Reduce(ynn_reduce_sum, 2969, 6265, {2}, true);
  g->ShapeProduct(2969, 6264, {2});
  g->Binary(ynn_binary_divide, 6265, 6264, 2970);
  g->Binary(ynn_binary_add, 2970, 6469, 2971);
  g->Unary(ynn_unary_rsqrt, 2971, 2972);
  g->Binary(ynn_binary_multiply, 2968, 2972, 2973);
  g->Binary(ynn_binary_multiply, 2973, 6939, 2974);
  g->Binary(ynn_binary_add, 2947, 2974, 2975);
  g->Binary(ynn_binary_multiply, 2975, 6931, 2976);
}

// Scope: "Layer34"
LAB_YNN_BUILDER_NOINLINE void BuildLayer34(Context& ctx) {
  BuildLayer34Attention(ctx);
  BuildLayer34Mlp(ctx);
  BuildLayer34PerLayerEmbedding(ctx);
}

// Scope: "FinalNormAndHead"
LAB_YNN_BUILDER_NOINLINE void BuildFinalNormAndHead(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2976, 2978);
  g->Reduce(ynn_reduce_sum, 2978, 6267, {2}, true);
  g->ShapeProduct(2978, 6266, {2});
  g->Binary(ynn_binary_divide, 6267, 6266, 2979);
  g->Binary(ynn_binary_add, 2979, 6469, 2980);
  g->Unary(ynn_unary_rsqrt, 2980, 2981);
  g->Binary(ynn_binary_multiply, 2976, 2981, 2982);
  g->Binary(ynn_binary_multiply, 2982, 7046, 2983);
  g->Reduce(ynn_reduce_min_max, 2983, 5118, {-1}, true);
  g->DynamicQuantization(5118, 5117, 5116);
  g->QuantizeTensor(2983, 5117, 5116, 5115);
  g->Transpose(6473, 5121, {1,0});
  g->Binary(ynn_binary_multiply, 5116, 5119, 5112);
  g->Reduce(ynn_reduce_sum, 5121, 5120, {0}, true);
  g->Binary(ynn_binary_multiply, 5117, 5120, 5114);
  g->Unary(ynn_unary_negate, 5114, 5113);
  g->Dot(5115, 5121, 5113, 5111, 1);
  g->DequantizeTensor(5111, YNN_INVALID_VALUE_ID, 5112, 2984);
  g->Binary(ynn_binary_multiply, 2984, 6510, 2985);
  g->Unary(ynn_unary_tanh, 2985, 2986);
  g->Binary(ynn_binary_multiply, 2986, 6467, 6474);
  g->ResultShape(6474, {slinky::expr(int64_t{1}),slinky::expr(int64_t{1}),slinky::expr(int64_t{262144})});
}

}  // namespace BuildGemma4DecodeSource
