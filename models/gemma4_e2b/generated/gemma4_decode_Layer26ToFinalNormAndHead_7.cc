// Generated YNNPACK builder; do not edit.
#include "gemma4_decode_builder.h"

namespace BuildGemma4DecodeSource {

// Scope: "Layer26 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer26AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(2116, 2117, 0.14451591670513153, 0);
  g->Transpose(6884, 4744, {1,0});
  g->Binary(ynn_binary_multiply, 4741, 4743, 4739);
  g->Dot(2117, 4744, YNN_INVALID_VALUE_ID, 4738, 1);
  g->DequantizeTensor(4738, YNN_INVALID_VALUE_ID, 4739, 4740);
  g->QuantizeTensor(4740, 6504, 4742, 2119);
  g->Dequantize(2119, 2120, 0.25196850299835205, 0);
  g->SplitDim(2120, 2121, 2, {8,256});
  g->FuseDims(2121, 2123, 1, 2);
  g->SplitDim(2123, 2122, 1, {8,1});
  g->Unary(ynn_unary_square, 2122, 2124);
  g->Reduce(ynn_reduce_sum, 2124, 6075, {3}, true);
  g->ShapeProduct(2124, 6074, {3});
  g->Binary(ynn_binary_divide, 6075, 6074, 2125);
  g->Binary(ynn_binary_add, 2125, 6539, 2126);
  g->Unary(ynn_unary_rsqrt, 2126, 2127);
  g->Binary(ynn_binary_multiply, 2122, 2127, 2128);
  g->Binary(ynn_binary_multiply, 2128, 6883, 2129);
  g->Slice(2129, 2131, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2129, 2132, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2132, 2133);
  g->Concat({2133,2131}, 2134, 3);
  g->Binary(ynn_binary_multiply, 2129, 3067, 2135);
  g->Binary(ynn_binary_multiply, 2134, 3172, 2136);
  g->Binary(ynn_binary_add, 2135, 2136, 2137);
}

// Scope: "Layer26 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer26AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7190, 2138, 0.0059552486054599285, 0);
  g->Dequantize(7205, 2139, 0.047244105488061905, 0);
  g->Matmul(2137, 2138, 2140, false, true);
  g->Mask(2140, 6564, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6564, 6079, {-1}, true);
  g->Binary(ynn_binary_subtract, 6564, 6079, 6076);
  g->Unary(ynn_unary_exp, 6076, 6077);
  g->Reduce(ynn_reduce_sum, 6077, 6080, {-1}, true);
  g->Binary(ynn_binary_divide, 5500, 6080, 6078);
  g->Binary(ynn_binary_multiply, 6077, 6078, 2142);
  g->Matmul(2142, 2139, 2143, false, false);
}

// Scope: "Layer26 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer26AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(2143, 2145, 1, 2);
  g->SplitDim(2145, 2144, 1, {1,8});
  g->FuseDims(2144, 2146, 2, 2);
  g->Quantize(2146, 2147, 0.023129930719733238, 0);
  g->Transpose(6882, 4750, {1,0});
  g->Binary(ynn_binary_multiply, 4252, 4749, 4746);
  g->Dot(2147, 4750, YNN_INVALID_VALUE_ID, 4745, 1);
  g->DequantizeTensor(4745, YNN_INVALID_VALUE_ID, 4746, 4747);
  g->QuantizeTensor(4747, 6504, 4748, 2148);
  g->Dequantize(2148, 2149, 0.04343831539154053, 0);
}

// Scope: "Layer26 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer26Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2110, 2111);
  g->Reduce(ynn_reduce_sum, 2111, 6073, {2}, true);
  g->ShapeProduct(2111, 6072, {2});
  g->Binary(ynn_binary_divide, 6073, 6072, 2112);
  g->Binary(ynn_binary_add, 2112, 6539, 2113);
  g->Unary(ynn_unary_rsqrt, 2113, 2114);
  g->Binary(ynn_binary_multiply, 2110, 2114, 2115);
  g->Binary(ynn_binary_multiply, 2115, 6871, 2116);
  BuildLayer26AttentionQueryProjection(ctx);
  BuildLayer26AttentionSdpa(ctx);
  BuildLayer26AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2149, 2150);
  g->Reduce(ynn_reduce_sum, 2150, 6082, {2}, true);
  g->ShapeProduct(2150, 6081, {2});
  g->Binary(ynn_binary_divide, 6082, 6081, 2151);
  g->Binary(ynn_binary_add, 2151, 6539, 2153);
  g->Unary(ynn_unary_rsqrt, 2153, 2154);
  g->Binary(ynn_binary_multiply, 2149, 2154, 2155);
  g->Binary(ynn_binary_multiply, 2155, 6878, 2156);
  g->Binary(ynn_binary_add, 2156, 2110, 2157);
}

// Scope: "Layer26 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer26Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2157, 2158);
  g->Reduce(ynn_reduce_sum, 2158, 6084, {2}, true);
  g->ShapeProduct(2158, 6083, {2});
  g->Binary(ynn_binary_divide, 6084, 6083, 2159);
  g->Binary(ynn_binary_add, 2159, 6539, 2160);
  g->Unary(ynn_unary_rsqrt, 2160, 2161);
  g->Binary(ynn_binary_multiply, 2157, 2161, 2162);
  g->Binary(ynn_binary_multiply, 2162, 6881, 2164);
  g->Quantize(2164, 2165, 0.02699781395494938, 0);
  g->Transpose(6875, 4757, {1,0});
  g->Binary(ynn_binary_multiply, 4754, 4756, 4752);
  g->Dot(2165, 4757, YNN_INVALID_VALUE_ID, 4751, 1);
  g->DequantizeTensor(4751, YNN_INVALID_VALUE_ID, 4752, 4753);
  g->QuantizeTensor(4753, 6504, 4755, 2166);
  g->Dequantize(2166, 2167, 0.04478347674012184, 0);
  g->Transpose(6874, 4762, {1,0});
  g->Binary(ynn_binary_multiply, 4754, 4761, 4759);
  g->Dot(2165, 4762, YNN_INVALID_VALUE_ID, 4758, 1);
  g->DequantizeTensor(4758, YNN_INVALID_VALUE_ID, 4759, 4760);
  g->QuantizeTensor(4760, 6504, 4755, 2168);
  g->Dequantize(2168, 2169, 0.04478347674012184, 0);
  g->Polynomial(2169, 6089, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6089, 6090);
  g->Binary(ynn_binary_add, 6090, 5500, 6087);
  g->Binary(ynn_binary_multiply, 2169, 5498, 6088);
  g->Binary(ynn_binary_multiply, 6088, 6087, 2170);
  g->Binary(ynn_binary_multiply, 2167, 2170, 2171);
  g->Quantize(2171, 2172, 0.05019685998558998, 0);
  g->Transpose(6873, 4769, {1,0});
  g->Binary(ynn_binary_multiply, 4766, 4768, 4764);
  g->Dot(2172, 4769, YNN_INVALID_VALUE_ID, 4763, 1);
  g->DequantizeTensor(4763, YNN_INVALID_VALUE_ID, 4764, 4765);
  g->QuantizeTensor(4765, 6504, 4767, 2176);
  g->Dequantize(2176, 2177, 0.017497630789875984, 0);
  g->Unary(ynn_unary_square, 2177, 2178);
  g->Reduce(ynn_reduce_sum, 2178, 6092, {2}, true);
  g->ShapeProduct(2178, 6091, {2});
  g->Binary(ynn_binary_divide, 6092, 6091, 2179);
  g->Binary(ynn_binary_add, 2179, 6539, 2180);
  g->Unary(ynn_unary_rsqrt, 2180, 2181);
  g->Binary(ynn_binary_multiply, 2177, 2181, 2182);
  g->Binary(ynn_binary_multiply, 2182, 6879, 2183);
  g->Binary(ynn_binary_add, 2183, 2157, 2184);
}

// Scope: "Layer26 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer26PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(427, 2185, {0,0,26,0}, {-1,-1,1,-1});
  g->Reshape(2185, 2187, {1,1,256});
  g->Unary(ynn_unary_square, 2187, 2188);
  g->Reduce(ynn_reduce_sum, 2188, 6094, {2}, true);
  g->ShapeProduct(2188, 6093, {2});
  g->Binary(ynn_binary_divide, 6094, 6093, 2189);
  g->Binary(ynn_binary_add, 2189, 6539, 2190);
  g->Unary(ynn_unary_rsqrt, 2190, 2191);
  g->Binary(ynn_binary_multiply, 2187, 2191, 2192);
  g->Binary(ynn_binary_multiply, 2192, 7118, 2193);
  g->Binary(ynn_binary_multiply, 7138, 6542, 2194);
  g->Binary(ynn_binary_add, 2193, 2194, 2195);
  g->Binary(ynn_binary_multiply, 2195, 6536, 2196);
  g->Quantize(2184, 2198, 0.11300035566091537, 0);
  g->Transpose(6876, 4776, {1,0});
  g->Binary(ynn_binary_multiply, 4773, 4775, 4771);
  g->Dot(2198, 4776, YNN_INVALID_VALUE_ID, 4770, 1);
  g->DequantizeTensor(4770, YNN_INVALID_VALUE_ID, 4771, 4772);
  g->QuantizeTensor(4772, 6504, 4774, 2199);
  g->Dequantize(2199, 2200, 0.10088583081960678, 0);
  g->Polynomial(2200, 6097, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6097, 6098);
  g->Binary(ynn_binary_add, 6098, 5500, 6095);
  g->Binary(ynn_binary_multiply, 2200, 5498, 6096);
  g->Binary(ynn_binary_multiply, 6096, 6095, 2201);
  g->Binary(ynn_binary_multiply, 2201, 2196, 2202);
  g->Quantize(2202, 2203, 0.5472440719604492, 0);
  g->Transpose(6877, 4783, {1,0});
  g->Binary(ynn_binary_multiply, 4780, 4782, 4778);
  g->Dot(2203, 4783, YNN_INVALID_VALUE_ID, 4777, 1);
  g->DequantizeTensor(4777, YNN_INVALID_VALUE_ID, 4778, 4779);
  g->QuantizeTensor(4779, 6504, 4781, 2204);
  g->Dequantize(2204, 2205, 0.34460699558258057, 0);
  g->Unary(ynn_unary_square, 2205, 2206);
  g->Reduce(ynn_reduce_sum, 2206, 6100, {2}, true);
  g->ShapeProduct(2206, 6099, {2});
  g->Binary(ynn_binary_divide, 6100, 6099, 2207);
  g->Binary(ynn_binary_add, 2207, 6539, 2209);
  g->Unary(ynn_unary_rsqrt, 2209, 2210);
  g->Binary(ynn_binary_multiply, 2205, 2210, 2211);
  g->Binary(ynn_binary_multiply, 2211, 6880, 2212);
  g->Binary(ynn_binary_add, 2184, 2212, 2213);
  g->Binary(ynn_binary_multiply, 2213, 6872, 2214);
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
  g->Quantize(2220, 2221, 0.3104223608970642, 0);
  g->Transpose(6898, 4790, {1,0});
  g->Binary(ynn_binary_multiply, 4787, 4789, 4785);
  g->Dot(2221, 4790, YNN_INVALID_VALUE_ID, 4784, 1);
  g->DequantizeTensor(4784, YNN_INVALID_VALUE_ID, 4785, 4786);
  g->QuantizeTensor(4786, 6504, 4788, 2222);
  g->Dequantize(2222, 2223, 0.437007874250412, 0);
  g->SplitDim(2223, 2224, 2, {8,256});
  g->FuseDims(2224, 2226, 1, 2);
  g->SplitDim(2226, 2225, 1, {8,1});
  g->Unary(ynn_unary_square, 2225, 2227);
  g->Reduce(ynn_reduce_sum, 2227, 6104, {3}, true);
  g->ShapeProduct(2227, 6103, {3});
  g->Binary(ynn_binary_divide, 6104, 6103, 2228);
  g->Binary(ynn_binary_add, 2228, 6539, 2229);
  g->Unary(ynn_unary_rsqrt, 2229, 2230);
  g->Binary(ynn_binary_multiply, 2225, 2230, 2231);
  g->Binary(ynn_binary_multiply, 2231, 6897, 2232);
  g->Slice(2232, 2233, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2232, 2234, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2234, 2235);
  g->Concat({2235,2233}, 2236, 3);
  g->Binary(ynn_binary_multiply, 2232, 3067, 2237);
  g->Binary(ynn_binary_multiply, 2236, 3172, 2238);
  g->Binary(ynn_binary_add, 2237, 2238, 2239);
}

// Scope: "Layer27 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer27AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7190, 2241, 0.0059552486054599285, 0);
  g->Dequantize(7205, 2242, 0.047244105488061905, 0);
  g->Matmul(2239, 2241, 2243, false, true);
  g->Mask(2243, 6565, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6565, 6108, {-1}, true);
  g->Binary(ynn_binary_subtract, 6565, 6108, 6105);
  g->Unary(ynn_unary_exp, 6105, 6106);
  g->Reduce(ynn_reduce_sum, 6106, 6109, {-1}, true);
  g->Binary(ynn_binary_divide, 5500, 6109, 6107);
  g->Binary(ynn_binary_multiply, 6106, 6107, 2244);
  g->Matmul(2244, 2242, 2245, false, false);
}

// Scope: "Layer27 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer27AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(2245, 2247, 1, 2);
  g->SplitDim(2247, 2246, 1, {1,8});
  g->FuseDims(2246, 2248, 2, 2);
  g->Quantize(2248, 2249, 0.024237213656306267, 0);
  g->Transpose(6896, 4797, {1,0});
  g->Binary(ynn_binary_multiply, 4794, 4796, 4792);
  g->Dot(2249, 4797, YNN_INVALID_VALUE_ID, 4791, 1);
  g->DequantizeTensor(4791, YNN_INVALID_VALUE_ID, 4792, 4793);
  g->QuantizeTensor(4793, 6504, 4795, 2250);
  g->Dequantize(2250, 2251, 0.05315101891756058, 0);
}

// Scope: "Layer27 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer27Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2214, 2215);
  g->Reduce(ynn_reduce_sum, 2215, 6102, {2}, true);
  g->ShapeProduct(2215, 6101, {2});
  g->Binary(ynn_binary_divide, 6102, 6101, 2216);
  g->Binary(ynn_binary_add, 2216, 6539, 2217);
  g->Unary(ynn_unary_rsqrt, 2217, 2218);
  g->Binary(ynn_binary_multiply, 2214, 2218, 2219);
  g->Binary(ynn_binary_multiply, 2219, 6885, 2220);
  BuildLayer27AttentionQueryProjection(ctx);
  BuildLayer27AttentionSdpa(ctx);
  BuildLayer27AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2251, 2252);
  g->Reduce(ynn_reduce_sum, 2252, 6111, {2}, true);
  g->ShapeProduct(2252, 6110, {2});
  g->Binary(ynn_binary_divide, 6111, 6110, 2253);
  g->Binary(ynn_binary_add, 2253, 6539, 2254);
  g->Unary(ynn_unary_rsqrt, 2254, 2255);
  g->Binary(ynn_binary_multiply, 2251, 2255, 2256);
  g->Binary(ynn_binary_multiply, 2256, 6892, 2257);
  g->Binary(ynn_binary_add, 2257, 2214, 2258);
}

// Scope: "Layer27 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer27Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2258, 2259);
  g->Reduce(ynn_reduce_sum, 2259, 6113, {2}, true);
  g->ShapeProduct(2259, 6112, {2});
  g->Binary(ynn_binary_divide, 6113, 6112, 2260);
  g->Binary(ynn_binary_add, 2260, 6539, 2261);
  g->Unary(ynn_unary_rsqrt, 2261, 2262);
  g->Binary(ynn_binary_multiply, 2258, 2262, 2263);
  g->Binary(ynn_binary_multiply, 2263, 6895, 2264);
  g->Quantize(2264, 2265, 0.02701687067747116, 0);
  g->Transpose(6889, 4804, {1,0});
  g->Binary(ynn_binary_multiply, 4801, 4803, 4799);
  g->Dot(2265, 4804, YNN_INVALID_VALUE_ID, 4798, 1);
  g->DequantizeTensor(4798, YNN_INVALID_VALUE_ID, 4799, 4800);
  g->QuantizeTensor(4800, 6504, 4802, 2266);
  g->Dequantize(2266, 2267, 0.044537413865327835, 0);
  g->Transpose(6888, 4809, {1,0});
  g->Binary(ynn_binary_multiply, 4801, 4808, 4806);
  g->Dot(2265, 4809, YNN_INVALID_VALUE_ID, 4805, 1);
  g->DequantizeTensor(4805, YNN_INVALID_VALUE_ID, 4806, 4807);
  g->QuantizeTensor(4807, 6504, 4802, 2268);
  g->Dequantize(2268, 2269, 0.044537413865327835, 0);
  g->Polynomial(2269, 6116, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6116, 6117);
  g->Binary(ynn_binary_add, 6117, 5500, 6114);
  g->Binary(ynn_binary_multiply, 2269, 5498, 6115);
  g->Binary(ynn_binary_multiply, 6115, 6114, 2270);
  g->Binary(ynn_binary_multiply, 2267, 2270, 2271);
  g->Quantize(2271, 2272, 0.09104331582784653, 0);
  g->Transpose(6887, 4816, {1,0});
  g->Binary(ynn_binary_multiply, 4813, 4815, 4811);
  g->Dot(2272, 4816, YNN_INVALID_VALUE_ID, 4810, 1);
  g->DequantizeTensor(4810, YNN_INVALID_VALUE_ID, 4811, 4812);
  g->QuantizeTensor(4812, 6504, 4814, 2273);
  g->Dequantize(2273, 2274, 0.08018074929714203, 0);
  g->Unary(ynn_unary_square, 2274, 2275);
  g->Reduce(ynn_reduce_sum, 2275, 6119, {2}, true);
  g->ShapeProduct(2275, 6118, {2});
  g->Binary(ynn_binary_divide, 6119, 6118, 2276);
  g->Binary(ynn_binary_add, 2276, 6539, 2277);
  g->Unary(ynn_unary_rsqrt, 2277, 2278);
  g->Binary(ynn_binary_multiply, 2274, 2278, 2279);
  g->Binary(ynn_binary_multiply, 2279, 6893, 2282);
  g->Binary(ynn_binary_add, 2282, 2258, 2283);
}

// Scope: "Layer27 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer27PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(427, 2284, {0,0,27,0}, {-1,-1,1,-1});
  g->Reshape(2284, 2285, {1,1,256});
  g->Unary(ynn_unary_square, 2285, 2286);
  g->Reduce(ynn_reduce_sum, 2286, 6121, {2}, true);
  g->ShapeProduct(2286, 6120, {2});
  g->Binary(ynn_binary_divide, 6121, 6120, 2287);
  g->Binary(ynn_binary_add, 2287, 6539, 2288);
  g->Unary(ynn_unary_rsqrt, 2288, 2289);
  g->Binary(ynn_binary_multiply, 2285, 2289, 2290);
  g->Binary(ynn_binary_multiply, 2290, 7118, 2291);
  g->Binary(ynn_binary_multiply, 7139, 6542, 2293);
  g->Binary(ynn_binary_add, 2291, 2293, 2294);
  g->Binary(ynn_binary_multiply, 2294, 6536, 2295);
  g->Quantize(2283, 2296, 0.12690971791744232, 0);
  g->Transpose(6890, 4829, {1,0});
  g->Binary(ynn_binary_multiply, 4826, 4828, 4824);
  g->Dot(2296, 4829, YNN_INVALID_VALUE_ID, 4823, 1);
  g->DequantizeTensor(4823, YNN_INVALID_VALUE_ID, 4824, 4825);
  g->QuantizeTensor(4825, 6504, 4827, 2297);
  g->Dequantize(2297, 2298, 0.07578741014003754, 0);
  g->Polynomial(2298, 6124, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6124, 6125);
  g->Binary(ynn_binary_add, 6125, 5500, 6122);
  g->Binary(ynn_binary_multiply, 2298, 5498, 6123);
  g->Binary(ynn_binary_multiply, 6123, 6122, 2299);
  g->Binary(ynn_binary_multiply, 2299, 2295, 2300);
  g->Quantize(2300, 2301, 0.5708661675453186, 0);
  g->Transpose(6891, 4836, {1,0});
  g->Binary(ynn_binary_multiply, 4833, 4835, 4831);
  g->Dot(2301, 4836, YNN_INVALID_VALUE_ID, 4830, 1);
  g->DequantizeTensor(4830, YNN_INVALID_VALUE_ID, 4831, 4832);
  g->QuantizeTensor(4832, 6504, 4834, 2302);
  g->Dequantize(2302, 2304, 0.26081717014312744, 0);
  g->Unary(ynn_unary_square, 2304, 2305);
  g->Reduce(ynn_reduce_sum, 2305, 6127, {2}, true);
  g->ShapeProduct(2305, 6126, {2});
  g->Binary(ynn_binary_divide, 6127, 6126, 2306);
  g->Binary(ynn_binary_add, 2306, 6539, 2307);
  g->Unary(ynn_unary_rsqrt, 2307, 2308);
  g->Binary(ynn_binary_multiply, 2304, 2308, 2309);
  g->Binary(ynn_binary_multiply, 2309, 6894, 2310);
  g->Binary(ynn_binary_add, 2283, 2310, 2311);
  g->Binary(ynn_binary_multiply, 2311, 6886, 2312);
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
  g->Quantize(2320, 2321, 0.4655068814754486, 0);
  g->Transpose(6912, 4843, {1,0});
  g->Binary(ynn_binary_multiply, 4840, 4842, 4838);
  g->Dot(2321, 4843, YNN_INVALID_VALUE_ID, 4837, 1);
  g->DequantizeTensor(4837, YNN_INVALID_VALUE_ID, 4838, 4839);
  g->QuantizeTensor(4839, 6504, 4841, 2322);
  g->Dequantize(2322, 2323, 0.34645670652389526, 0);
  g->SplitDim(2323, 2324, 2, {8,256});
  g->FuseDims(2324, 2326, 1, 2);
  g->SplitDim(2326, 2325, 1, {8,1});
  g->Unary(ynn_unary_square, 2325, 2328);
  g->Reduce(ynn_reduce_sum, 2328, 6131, {3}, true);
  g->ShapeProduct(2328, 6130, {3});
  g->Binary(ynn_binary_divide, 6131, 6130, 2329);
  g->Binary(ynn_binary_add, 2329, 6539, 2330);
  g->Unary(ynn_unary_rsqrt, 2330, 2331);
  g->Binary(ynn_binary_multiply, 2325, 2331, 2332);
  g->Binary(ynn_binary_multiply, 2332, 6911, 2333);
  g->Slice(2333, 2334, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2333, 2335, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2335, 2336);
  g->Concat({2336,2334}, 2337, 3);
  g->Binary(ynn_binary_multiply, 2333, 3067, 2339);
  g->Binary(ynn_binary_multiply, 2337, 3172, 2340);
  g->Binary(ynn_binary_add, 2339, 2340, 2341);
}

// Scope: "Layer28 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer28AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7190, 2342, 0.0059552486054599285, 0);
  g->Dequantize(7205, 2343, 0.047244105488061905, 0);
  g->Matmul(2341, 2342, 2344, false, true);
  g->Mask(2344, 6566, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6566, 6137, {-1}, true);
  g->Binary(ynn_binary_subtract, 6566, 6137, 6134);
  g->Unary(ynn_unary_exp, 6134, 6135);
  g->Reduce(ynn_reduce_sum, 6135, 6138, {-1}, true);
  g->Binary(ynn_binary_divide, 5500, 6138, 6136);
  g->Binary(ynn_binary_multiply, 6135, 6136, 2345);
  g->Matmul(2345, 2343, 2346, false, false);
}

// Scope: "Layer28 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer28AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(2346, 2348, 1, 2);
  g->SplitDim(2348, 2347, 1, {1,8});
  g->FuseDims(2347, 2350, 2, 2);
  g->Quantize(2350, 2351, 0.024237213656306267, 0);
  g->Transpose(6910, 4849, {1,0});
  g->Binary(ynn_binary_multiply, 4794, 4848, 4845);
  g->Dot(2351, 4849, YNN_INVALID_VALUE_ID, 4844, 1);
  g->DequantizeTensor(4844, YNN_INVALID_VALUE_ID, 4845, 4846);
  g->QuantizeTensor(4846, 6504, 4847, 2352);
  g->Dequantize(2352, 2353, 0.03035588562488556, 0);
}

// Scope: "Layer28 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer28Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2312, 2313);
  g->Reduce(ynn_reduce_sum, 2313, 6129, {2}, true);
  g->ShapeProduct(2313, 6128, {2});
  g->Binary(ynn_binary_divide, 6129, 6128, 2316);
  g->Binary(ynn_binary_add, 2316, 6539, 2317);
  g->Unary(ynn_unary_rsqrt, 2317, 2318);
  g->Binary(ynn_binary_multiply, 2312, 2318, 2319);
  g->Binary(ynn_binary_multiply, 2319, 6899, 2320);
  BuildLayer28AttentionQueryProjection(ctx);
  BuildLayer28AttentionSdpa(ctx);
  BuildLayer28AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2353, 2354);
  g->Reduce(ynn_reduce_sum, 2354, 6140, {2}, true);
  g->ShapeProduct(2354, 6139, {2});
  g->Binary(ynn_binary_divide, 6140, 6139, 2355);
  g->Binary(ynn_binary_add, 2355, 6539, 2356);
  g->Unary(ynn_unary_rsqrt, 2356, 2357);
  g->Binary(ynn_binary_multiply, 2353, 2357, 2358);
  g->Binary(ynn_binary_multiply, 2358, 6906, 2359);
  g->Binary(ynn_binary_add, 2359, 2312, 2361);
}

// Scope: "Layer28 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer28Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2361, 2362);
  g->Reduce(ynn_reduce_sum, 2362, 6142, {2}, true);
  g->ShapeProduct(2362, 6141, {2});
  g->Binary(ynn_binary_divide, 6142, 6141, 2363);
  g->Binary(ynn_binary_add, 2363, 6539, 2364);
  g->Unary(ynn_unary_rsqrt, 2364, 2365);
  g->Binary(ynn_binary_multiply, 2361, 2365, 2366);
  g->Binary(ynn_binary_multiply, 2366, 6909, 2367);
  g->Quantize(2367, 2368, 0.025474751368165016, 0);
  g->Transpose(6903, 4856, {1,0});
  g->Binary(ynn_binary_multiply, 4853, 4855, 4851);
  g->Dot(2368, 4856, YNN_INVALID_VALUE_ID, 4850, 1);
  g->DequantizeTensor(4850, YNN_INVALID_VALUE_ID, 4851, 4852);
  g->QuantizeTensor(4852, 6504, 4854, 2369);
  g->Dequantize(2369, 2370, 0.03494095429778099, 0);
  g->Transpose(6902, 4861, {1,0});
  g->Binary(ynn_binary_multiply, 4853, 4860, 4858);
  g->Dot(2368, 4861, YNN_INVALID_VALUE_ID, 4857, 1);
  g->DequantizeTensor(4857, YNN_INVALID_VALUE_ID, 4858, 4859);
  g->QuantizeTensor(4859, 6504, 4854, 2372);
  g->Dequantize(2372, 2373, 0.03494095429778099, 0);
  g->Polynomial(2373, 6145, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6145, 6146);
  g->Binary(ynn_binary_add, 6146, 5500, 6143);
  g->Binary(ynn_binary_multiply, 2373, 5498, 6144);
  g->Binary(ynn_binary_multiply, 6144, 6143, 2374);
  g->Binary(ynn_binary_multiply, 2370, 2374, 2375);
  g->Quantize(2375, 2376, 0.07627953588962555, 0);
  g->Transpose(6901, 4868, {1,0});
  g->Binary(ynn_binary_multiply, 4865, 4867, 4863);
  g->Dot(2376, 4868, YNN_INVALID_VALUE_ID, 4862, 1);
  g->DequantizeTensor(4862, YNN_INVALID_VALUE_ID, 4863, 4864);
  g->QuantizeTensor(4864, 6504, 4866, 2377);
  g->Dequantize(2377, 2378, 0.10797519981861115, 0);
  g->Unary(ynn_unary_square, 2378, 2379);
  g->Reduce(ynn_reduce_sum, 2379, 6148, {2}, true);
  g->ShapeProduct(2379, 6147, {2});
  g->Binary(ynn_binary_divide, 6148, 6147, 2380);
  g->Binary(ynn_binary_add, 2380, 6539, 2382);
  g->Unary(ynn_unary_rsqrt, 2382, 2383);
  g->Binary(ynn_binary_multiply, 2378, 2383, 2384);
  g->Binary(ynn_binary_multiply, 2384, 6907, 2385);
  g->Binary(ynn_binary_add, 2385, 2361, 2386);
}

// Scope: "Layer28 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer28PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(427, 2387, {0,0,28,0}, {-1,-1,1,-1});
  g->Reshape(2387, 2388, {1,1,256});
  g->Unary(ynn_unary_square, 2388, 2389);
  g->Reduce(ynn_reduce_sum, 2389, 6150, {2}, true);
  g->ShapeProduct(2389, 6149, {2});
  g->Binary(ynn_binary_divide, 6150, 6149, 2390);
  g->Binary(ynn_binary_add, 2390, 6539, 2391);
  g->Unary(ynn_unary_rsqrt, 2391, 2394);
  g->Binary(ynn_binary_multiply, 2388, 2394, 2395);
  g->Binary(ynn_binary_multiply, 2395, 7118, 2396);
  g->Binary(ynn_binary_multiply, 7140, 6542, 2397);
  g->Binary(ynn_binary_add, 2396, 2397, 2398);
  g->Binary(ynn_binary_multiply, 2398, 6536, 2399);
  g->Quantize(2386, 2400, 0.13722270727157593, 0);
  g->Transpose(6904, 4875, {1,0});
  g->Binary(ynn_binary_multiply, 4872, 4874, 4870);
  g->Dot(2400, 4875, YNN_INVALID_VALUE_ID, 4869, 1);
  g->DequantizeTensor(4869, YNN_INVALID_VALUE_ID, 4870, 4871);
  g->QuantizeTensor(4871, 6504, 4873, 2401);
  g->Dequantize(2401, 2402, 0.08513779938220978, 0);
  g->Polynomial(2402, 6153, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6153, 6154);
  g->Binary(ynn_binary_add, 6154, 5500, 6151);
  g->Binary(ynn_binary_multiply, 2402, 5498, 6152);
  g->Binary(ynn_binary_multiply, 6152, 6151, 2403);
  g->Binary(ynn_binary_multiply, 2403, 2399, 2405);
  g->Quantize(2405, 2406, 0.748031497001648, 0);
  g->Transpose(6905, 4882, {1,0});
  g->Binary(ynn_binary_multiply, 4879, 4881, 4877);
  g->Dot(2406, 4882, YNN_INVALID_VALUE_ID, 4876, 1);
  g->DequantizeTensor(4876, YNN_INVALID_VALUE_ID, 4877, 4878);
  g->QuantizeTensor(4878, 6504, 4880, 2407);
  g->Dequantize(2407, 2408, 0.18373137712478638, 0);
  g->Unary(ynn_unary_square, 2408, 2409);
  g->Reduce(ynn_reduce_sum, 2409, 6156, {2}, true);
  g->ShapeProduct(2409, 6155, {2});
  g->Binary(ynn_binary_divide, 6156, 6155, 2410);
  g->Binary(ynn_binary_add, 2410, 6539, 2411);
  g->Unary(ynn_unary_rsqrt, 2411, 2412);
  g->Binary(ynn_binary_multiply, 2408, 2412, 2413);
  g->Binary(ynn_binary_multiply, 2413, 6908, 2414);
  g->Binary(ynn_binary_add, 2386, 2414, 2416);
  g->Binary(ynn_binary_multiply, 2416, 6900, 2417);
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
  g->Quantize(2423, 2424, 0.41653531789779663, 0);
  g->Transpose(6926, 4889, {1,0});
  g->Binary(ynn_binary_multiply, 4886, 4888, 4884);
  g->Dot(2424, 4889, YNN_INVALID_VALUE_ID, 4883, 1);
  g->DequantizeTensor(4883, YNN_INVALID_VALUE_ID, 4884, 4885);
  g->QuantizeTensor(4885, 6504, 4887, 2425);
  g->Dequantize(2425, 2427, 0.312992125749588, 0);
  g->SplitDim(2427, 2428, 2, {8,512});
  g->FuseDims(2428, 2430, 1, 2);
  g->SplitDim(2430, 2429, 1, {8,1});
  g->Unary(ynn_unary_square, 2429, 2431);
  g->Reduce(ynn_reduce_sum, 2431, 6160, {3}, true);
  g->ShapeProduct(2431, 6159, {3});
  g->Binary(ynn_binary_divide, 6160, 6159, 2432);
  g->Binary(ynn_binary_add, 2432, 6539, 2433);
  g->Unary(ynn_unary_rsqrt, 2433, 2434);
  g->Binary(ynn_binary_multiply, 2429, 2434, 2435);
  g->Binary(ynn_binary_multiply, 2435, 6925, 2436);
  g->Slice(2436, 2437, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(2436, 2439, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 2439, 2440);
  g->Concat({2440,2437}, 2441, 3);
  g->Binary(ynn_binary_multiply, 2436, 3594, 2442);
  g->Binary(ynn_binary_multiply, 2441, 2, 2443);
  g->Binary(ynn_binary_add, 2442, 2443, 2444);
}

// Scope: "Layer29 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer29AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7191, 2445, 0.001091228099539876, 0);
  g->Dequantize(7206, 2446, 0.01785714365541935, 0);
  g->Matmul(2444, 2445, 2447, false, true);
  g->Mask(2447, 6567, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 6567, 6164, {-1}, true);
  g->Binary(ynn_binary_subtract, 6567, 6164, 6161);
  g->Unary(ynn_unary_exp, 6161, 6162);
  g->Reduce(ynn_reduce_sum, 6162, 6165, {-1}, true);
  g->Binary(ynn_binary_divide, 5500, 6165, 6163);
  g->Binary(ynn_binary_multiply, 6162, 6163, 2449);
  g->Matmul(2449, 2446, 2450, false, false);
}

// Scope: "Layer29 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer29AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(2450, 2452, 1, 2);
  g->SplitDim(2452, 2451, 1, {1,8});
  g->FuseDims(2451, 2453, 2, 2);
  g->Quantize(2453, 2454, 0.017962608486413956, 0);
  g->Transpose(6924, 4895, {1,0});
  g->Binary(ynn_binary_multiply, 3813, 4894, 4891);
  g->Dot(2454, 4895, YNN_INVALID_VALUE_ID, 4890, 1);
  g->DequantizeTensor(4890, YNN_INVALID_VALUE_ID, 4891, 4892);
  g->QuantizeTensor(4892, 6504, 4893, 2455);
  g->Dequantize(2455, 2456, 0.03030368685722351, 0);
}

// Scope: "Layer29 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer29Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2417, 2418);
  g->Reduce(ynn_reduce_sum, 2418, 6158, {2}, true);
  g->ShapeProduct(2418, 6157, {2});
  g->Binary(ynn_binary_divide, 6158, 6157, 2419);
  g->Binary(ynn_binary_add, 2419, 6539, 2420);
  g->Unary(ynn_unary_rsqrt, 2420, 2421);
  g->Binary(ynn_binary_multiply, 2417, 2421, 2422);
  g->Binary(ynn_binary_multiply, 2422, 6913, 2423);
  BuildLayer29AttentionQueryProjection(ctx);
  BuildLayer29AttentionSdpa(ctx);
  BuildLayer29AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2456, 2457);
  g->Reduce(ynn_reduce_sum, 2457, 6167, {2}, true);
  g->ShapeProduct(2457, 6166, {2});
  g->Binary(ynn_binary_divide, 6167, 6166, 2458);
  g->Binary(ynn_binary_add, 2458, 6539, 2459);
  g->Unary(ynn_unary_rsqrt, 2459, 2461);
  g->Binary(ynn_binary_multiply, 2456, 2461, 2462);
  g->Binary(ynn_binary_multiply, 2462, 6920, 2463);
  g->Binary(ynn_binary_add, 2463, 2417, 2464);
}

// Scope: "Layer29 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer29Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2464, 2465);
  g->Reduce(ynn_reduce_sum, 2465, 6169, {2}, true);
  g->ShapeProduct(2465, 6168, {2});
  g->Binary(ynn_binary_divide, 6169, 6168, 2466);
  g->Binary(ynn_binary_add, 2466, 6539, 2467);
  g->Unary(ynn_unary_rsqrt, 2467, 2468);
  g->Binary(ynn_binary_multiply, 2464, 2468, 2469);
  g->Binary(ynn_binary_multiply, 2469, 6923, 2470);
  g->Quantize(2470, 2472, 0.032805636525154114, 0);
  g->Transpose(6917, 4902, {1,0});
  g->Binary(ynn_binary_multiply, 4899, 4901, 4897);
  g->Dot(2472, 4902, YNN_INVALID_VALUE_ID, 4896, 1);
  g->DequantizeTensor(4896, YNN_INVALID_VALUE_ID, 4897, 4898);
  g->QuantizeTensor(4898, 6504, 4900, 2473);
  g->Dequantize(2473, 2474, 0.03690946102142334, 0);
  g->Transpose(6916, 4907, {1,0});
  g->Binary(ynn_binary_multiply, 4899, 4906, 4904);
  g->Dot(2472, 4907, YNN_INVALID_VALUE_ID, 4903, 1);
  g->DequantizeTensor(4903, YNN_INVALID_VALUE_ID, 4904, 4905);
  g->QuantizeTensor(4905, 6504, 4900, 2475);
  g->Dequantize(2475, 2476, 0.03690946102142334, 0);
  g->Polynomial(2476, 6172, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6172, 6173);
  g->Binary(ynn_binary_add, 6173, 5500, 6170);
  g->Binary(ynn_binary_multiply, 2476, 5498, 6171);
  g->Binary(ynn_binary_multiply, 6171, 6170, 2477);
  g->Binary(ynn_binary_multiply, 2474, 2477, 2478);
  g->Quantize(2478, 2479, 0.11171260476112366, 0);
  g->Transpose(6915, 4914, {1,0});
  g->Binary(ynn_binary_multiply, 4911, 4913, 4909);
  g->Dot(2479, 4914, YNN_INVALID_VALUE_ID, 4908, 1);
  g->DequantizeTensor(4908, YNN_INVALID_VALUE_ID, 4909, 4910);
  g->QuantizeTensor(4910, 6504, 4912, 2480);
  g->Dequantize(2480, 2482, 0.3346065282821655, 0);
  g->Unary(ynn_unary_square, 2482, 2483);
  g->Reduce(ynn_reduce_sum, 2483, 6175, {2}, true);
  g->ShapeProduct(2483, 6174, {2});
  g->Binary(ynn_binary_divide, 6175, 6174, 2484);
  g->Binary(ynn_binary_add, 2484, 6539, 2485);
  g->Unary(ynn_unary_rsqrt, 2485, 2486);
  g->Binary(ynn_binary_multiply, 2482, 2486, 2487);
  g->Binary(ynn_binary_multiply, 2487, 6921, 2488);
  g->Binary(ynn_binary_add, 2488, 2464, 2489);
}

// Scope: "Layer29 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer29PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(427, 2490, {0,0,29,0}, {-1,-1,1,-1});
  g->Reshape(2490, 2491, {1,1,256});
  g->Unary(ynn_unary_square, 2491, 2493);
  g->Reduce(ynn_reduce_sum, 2493, 6177, {2}, true);
  g->ShapeProduct(2493, 6176, {2});
  g->Binary(ynn_binary_divide, 6177, 6176, 2494);
  g->Binary(ynn_binary_add, 2494, 6539, 2495);
  g->Unary(ynn_unary_rsqrt, 2495, 2496);
  g->Binary(ynn_binary_multiply, 2491, 2496, 2497);
  g->Binary(ynn_binary_multiply, 2497, 7118, 2498);
  g->Binary(ynn_binary_multiply, 7141, 6542, 2499);
  g->Binary(ynn_binary_add, 2498, 2499, 2500);
  g->Binary(ynn_binary_multiply, 2500, 6536, 2501);
  g->Quantize(2489, 2502, 0.1425527185201645, 0);
  g->Transpose(6918, 4920, {1,0});
  g->Binary(ynn_binary_multiply, 4918, 4919, 4916);
  g->Dot(2502, 4920, YNN_INVALID_VALUE_ID, 4915, 1);
  g->DequantizeTensor(4915, YNN_INVALID_VALUE_ID, 4916, 4917);
  g->QuantizeTensor(4917, 6504, 4260, 2504);
  g->Dequantize(2504, 2505, 0.07234252989292145, 0);
  g->Polynomial(2505, 6180, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6180, 6181);
  g->Binary(ynn_binary_add, 6181, 5500, 6178);
  g->Binary(ynn_binary_multiply, 2505, 5498, 6179);
  g->Binary(ynn_binary_multiply, 6179, 6178, 2506);
  g->Binary(ynn_binary_multiply, 2506, 2501, 2507);
  g->Quantize(2507, 2508, 0.2539370059967041, 0);
  g->Transpose(6919, 4927, {1,0});
  g->Binary(ynn_binary_multiply, 4924, 4926, 4922);
  g->Dot(2508, 4927, YNN_INVALID_VALUE_ID, 4921, 1);
  g->DequantizeTensor(4921, YNN_INVALID_VALUE_ID, 4922, 4923);
  g->QuantizeTensor(4923, 6504, 4925, 2509);
  g->Dequantize(2509, 2510, 0.2777099609375, 0);
  g->Unary(ynn_unary_square, 2510, 2511);
  g->Reduce(ynn_reduce_sum, 2511, 6183, {2}, true);
  g->ShapeProduct(2511, 6182, {2});
  g->Binary(ynn_binary_divide, 6183, 6182, 2512);
  g->Binary(ynn_binary_add, 2512, 6539, 2513);
  g->Unary(ynn_unary_rsqrt, 2513, 2515);
  g->Binary(ynn_binary_multiply, 2510, 2515, 2516);
  g->Binary(ynn_binary_multiply, 2516, 6922, 2517);
  g->Binary(ynn_binary_add, 2489, 2517, 2518);
  g->Binary(ynn_binary_multiply, 2518, 6914, 2519);
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
  g->Quantize(2526, 2527, 0.621565580368042, 0);
  g->Transpose(6957, 4934, {1,0});
  g->Binary(ynn_binary_multiply, 4931, 4933, 4929);
  g->Dot(2527, 4934, YNN_INVALID_VALUE_ID, 4928, 1);
  g->DequantizeTensor(4928, YNN_INVALID_VALUE_ID, 4929, 4930);
  g->QuantizeTensor(4930, 6504, 4932, 2528);
  g->Dequantize(2528, 2529, 0.45866140723228455, 0);
  g->SplitDim(2529, 2530, 2, {8,256});
  g->FuseDims(2530, 2532, 1, 2);
  g->SplitDim(2532, 2531, 1, {8,1});
  g->Unary(ynn_unary_square, 2531, 2533);
  g->Reduce(ynn_reduce_sum, 2533, 6192, {3}, true);
  g->ShapeProduct(2533, 6191, {3});
  g->Binary(ynn_binary_divide, 6192, 6191, 2534);
  g->Binary(ynn_binary_add, 2534, 6539, 2535);
  g->Unary(ynn_unary_rsqrt, 2535, 2536);
  g->Binary(ynn_binary_multiply, 2531, 2536, 2539);
  g->Binary(ynn_binary_multiply, 2539, 6956, 2540);
  g->Slice(2540, 2541, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2540, 2542, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2542, 2543);
  g->Concat({2543,2541}, 2544, 3);
  g->Binary(ynn_binary_multiply, 2540, 3067, 2545);
  g->Binary(ynn_binary_multiply, 2544, 3172, 2546);
  g->Binary(ynn_binary_add, 2545, 2546, 2547);
}

// Scope: "Layer30 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer30AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7190, 2548, 0.0059552486054599285, 0);
  g->Dequantize(7205, 2550, 0.047244105488061905, 0);
  g->Matmul(2547, 2548, 2551, false, true);
  g->Mask(2551, 6569, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6569, 6196, {-1}, true);
  g->Binary(ynn_binary_subtract, 6569, 6196, 6193);
  g->Unary(ynn_unary_exp, 6193, 6194);
  g->Reduce(ynn_reduce_sum, 6194, 6197, {-1}, true);
  g->Binary(ynn_binary_divide, 5500, 6197, 6195);
  g->Binary(ynn_binary_multiply, 6194, 6195, 2552);
  g->Matmul(2552, 2550, 2553, false, false);
}

// Scope: "Layer30 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer30AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(2553, 2555, 1, 2);
  g->SplitDim(2555, 2554, 1, {1,8});
  g->FuseDims(2554, 2556, 2, 2);
  g->Quantize(2556, 2557, 0.02399115078151226, 0);
  g->Transpose(6955, 4941, {1,0});
  g->Binary(ynn_binary_multiply, 4938, 4940, 4936);
  g->Dot(2557, 4941, YNN_INVALID_VALUE_ID, 4935, 1);
  g->DequantizeTensor(4935, YNN_INVALID_VALUE_ID, 4936, 4937);
  g->QuantizeTensor(4937, 6504, 4939, 2558);
  g->Dequantize(2558, 2559, 0.05247194319963455, 0);
}

// Scope: "Layer30 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer30Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2519, 2520);
  g->Reduce(ynn_reduce_sum, 2520, 6190, {2}, true);
  g->ShapeProduct(2520, 6189, {2});
  g->Binary(ynn_binary_divide, 6190, 6189, 2521);
  g->Binary(ynn_binary_add, 2521, 6539, 2522);
  g->Unary(ynn_unary_rsqrt, 2522, 2523);
  g->Binary(ynn_binary_multiply, 2519, 2523, 2524);
  g->Binary(ynn_binary_multiply, 2524, 6944, 2526);
  BuildLayer30AttentionQueryProjection(ctx);
  BuildLayer30AttentionSdpa(ctx);
  BuildLayer30AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2559, 2561);
  g->Reduce(ynn_reduce_sum, 2561, 6199, {2}, true);
  g->ShapeProduct(2561, 6198, {2});
  g->Binary(ynn_binary_divide, 6199, 6198, 2562);
  g->Binary(ynn_binary_add, 2562, 6539, 2563);
  g->Unary(ynn_unary_rsqrt, 2563, 2564);
  g->Binary(ynn_binary_multiply, 2559, 2564, 2565);
  g->Binary(ynn_binary_multiply, 2565, 6951, 2566);
  g->Binary(ynn_binary_add, 2566, 2519, 2567);
}

// Scope: "Layer30 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer30Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2567, 2568);
  g->Reduce(ynn_reduce_sum, 2568, 6201, {2}, true);
  g->ShapeProduct(2568, 6200, {2});
  g->Binary(ynn_binary_divide, 6201, 6200, 2569);
  g->Binary(ynn_binary_add, 2569, 6539, 2570);
  g->Unary(ynn_unary_rsqrt, 2570, 2572);
  g->Binary(ynn_binary_multiply, 2567, 2572, 2573);
  g->Binary(ynn_binary_multiply, 2573, 6954, 2574);
  g->Quantize(2574, 2575, 0.02257225476205349, 0);
  g->Transpose(6948, 4955, {1,0});
  g->Binary(ynn_binary_multiply, 4952, 4954, 4950);
  g->Dot(2575, 4955, YNN_INVALID_VALUE_ID, 4949, 1);
  g->DequantizeTensor(4949, YNN_INVALID_VALUE_ID, 4950, 4951);
  g->QuantizeTensor(4951, 6504, 4953, 2576);
  g->Dequantize(2576, 2577, 0.028789378702640533, 0);
  g->Transpose(6947, 4960, {1,0});
  g->Binary(ynn_binary_multiply, 4952, 4959, 4957);
  g->Dot(2575, 4960, YNN_INVALID_VALUE_ID, 4956, 1);
  g->DequantizeTensor(4956, YNN_INVALID_VALUE_ID, 4957, 4958);
  g->QuantizeTensor(4958, 6504, 4953, 2578);
  g->Dequantize(2578, 2579, 0.028789378702640533, 0);
  g->Polynomial(2579, 6204, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6204, 6205);
  g->Binary(ynn_binary_add, 6205, 5500, 6202);
  g->Binary(ynn_binary_multiply, 2579, 5498, 6203);
  g->Binary(ynn_binary_multiply, 6203, 6202, 2580);
  g->Binary(ynn_binary_multiply, 2577, 2580, 2582);
  g->Quantize(2582, 2583, 0.07234252989292145, 0);
  g->Transpose(6946, 4966, {1,0});
  g->Binary(ynn_binary_multiply, 4260, 4965, 4962);
  g->Dot(2583, 4966, YNN_INVALID_VALUE_ID, 4961, 1);
  g->DequantizeTensor(4961, YNN_INVALID_VALUE_ID, 4962, 4963);
  g->QuantizeTensor(4963, 6504, 4964, 2584);
  g->Dequantize(2584, 2585, 0.2192506492137909, 0);
  g->Unary(ynn_unary_square, 2585, 2586);
  g->Reduce(ynn_reduce_sum, 2586, 6207, {2}, true);
  g->ShapeProduct(2586, 6206, {2});
  g->Binary(ynn_binary_divide, 6207, 6206, 2587);
  g->Binary(ynn_binary_add, 2587, 6539, 2588);
  g->Unary(ynn_unary_rsqrt, 2588, 2589);
  g->Binary(ynn_binary_multiply, 2585, 2589, 2590);
  g->Binary(ynn_binary_multiply, 2590, 6952, 2591);
  g->Binary(ynn_binary_add, 2591, 2567, 2593);
}

// Scope: "Layer30 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer30PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(427, 2594, {0,0,30,0}, {-1,-1,1,-1});
  g->Reshape(2594, 2595, {1,1,256});
  g->Unary(ynn_unary_square, 2595, 2596);
  g->Reduce(ynn_reduce_sum, 2596, 6209, {2}, true);
  g->ShapeProduct(2596, 6208, {2});
  g->Binary(ynn_binary_divide, 6209, 6208, 2597);
  g->Binary(ynn_binary_add, 2597, 6539, 2598);
  g->Unary(ynn_unary_rsqrt, 2598, 2599);
  g->Binary(ynn_binary_multiply, 2595, 2599, 2600);
  g->Binary(ynn_binary_multiply, 2600, 7118, 2601);
  g->Binary(ynn_binary_multiply, 7143, 6542, 2602);
  g->Binary(ynn_binary_add, 2601, 2602, 2604);
  g->Binary(ynn_binary_multiply, 2604, 6536, 2605);
  g->Quantize(2593, 2606, 0.13473963737487793, 0);
  g->Transpose(6949, 4973, {1,0});
  g->Binary(ynn_binary_multiply, 4970, 4972, 4968);
  g->Dot(2606, 4973, YNN_INVALID_VALUE_ID, 4967, 1);
  g->DequantizeTensor(4967, YNN_INVALID_VALUE_ID, 4968, 4969);
  g->QuantizeTensor(4969, 6504, 4971, 2607);
  g->Dequantize(2607, 2608, 0.09596457332372665, 0);
  g->Polynomial(2608, 6214, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6214, 6215);
  g->Binary(ynn_binary_add, 6215, 5500, 6212);
  g->Binary(ynn_binary_multiply, 2608, 5498, 6213);
  g->Binary(ynn_binary_multiply, 6213, 6212, 2609);
  g->Binary(ynn_binary_multiply, 2609, 2605, 2610);
  g->Quantize(2610, 2611, 0.18700788915157318, 0);
  g->Transpose(6950, 4980, {1,0});
  g->Binary(ynn_binary_multiply, 4977, 4979, 4975);
  g->Dot(2611, 4980, YNN_INVALID_VALUE_ID, 4974, 1);
  g->DequantizeTensor(4974, YNN_INVALID_VALUE_ID, 4975, 4976);
  g->QuantizeTensor(4976, 6504, 4978, 2612);
  g->Dequantize(2612, 2613, 0.27509135007858276, 0);
  g->Unary(ynn_unary_square, 2613, 2616);
  g->Reduce(ynn_reduce_sum, 2616, 6217, {2}, true);
  g->ShapeProduct(2616, 6216, {2});
  g->Binary(ynn_binary_divide, 6217, 6216, 2617);
  g->Binary(ynn_binary_add, 2617, 6539, 2618);
  g->Unary(ynn_unary_rsqrt, 2618, 2619);
  g->Binary(ynn_binary_multiply, 2613, 2619, 2620);
  g->Binary(ynn_binary_multiply, 2620, 6953, 2621);
  g->Binary(ynn_binary_add, 2593, 2621, 2622);
  g->Binary(ynn_binary_multiply, 2622, 6945, 2623);
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
  g->Quantize(2630, 2631, 0.6227923035621643, 0);
  g->Transpose(6971, 4987, {1,0});
  g->Binary(ynn_binary_multiply, 4984, 4986, 4982);
  g->Dot(2631, 4987, YNN_INVALID_VALUE_ID, 4981, 1);
  g->DequantizeTensor(4981, YNN_INVALID_VALUE_ID, 4982, 4983);
  g->QuantizeTensor(4983, 6504, 4985, 2632);
  g->Dequantize(2632, 2633, 0.6574802994728088, 0);
  g->SplitDim(2633, 2634, 2, {8,256});
  g->FuseDims(2634, 2636, 1, 2);
  g->SplitDim(2636, 2635, 1, {8,1});
  g->Unary(ynn_unary_square, 2635, 2637);
  g->Reduce(ynn_reduce_sum, 2637, 6221, {3}, true);
  g->ShapeProduct(2637, 6220, {3});
  g->Binary(ynn_binary_divide, 6221, 6220, 2639);
  g->Binary(ynn_binary_add, 2639, 6539, 2640);
  g->Unary(ynn_unary_rsqrt, 2640, 2641);
  g->Binary(ynn_binary_multiply, 2635, 2641, 2642);
  g->Binary(ynn_binary_multiply, 2642, 6970, 2643);
  g->Slice(2643, 2644, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2643, 2645, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2645, 2646);
  g->Concat({2646,2644}, 2647, 3);
  g->Binary(ynn_binary_multiply, 2643, 3067, 2648);
  g->Binary(ynn_binary_multiply, 2647, 3172, 2650);
  g->Binary(ynn_binary_add, 2648, 2650, 2651);
}

// Scope: "Layer31 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer31AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7190, 2652, 0.0059552486054599285, 0);
  g->Dequantize(7205, 2653, 0.047244105488061905, 0);
  g->Matmul(2651, 2652, 2654, false, true);
  g->Mask(2654, 6570, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6570, 6225, {-1}, true);
  g->Binary(ynn_binary_subtract, 6570, 6225, 6222);
  g->Unary(ynn_unary_exp, 6222, 6223);
  g->Reduce(ynn_reduce_sum, 6223, 6226, {-1}, true);
  g->Binary(ynn_binary_divide, 5500, 6226, 6224);
  g->Binary(ynn_binary_multiply, 6223, 6224, 2655);
  g->Matmul(2655, 2653, 2656, false, false);
}

// Scope: "Layer31 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer31AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(2656, 2658, 1, 2);
  g->SplitDim(2658, 2657, 1, {1,8});
  g->FuseDims(2657, 2659, 2, 2);
  g->Quantize(2659, 2661, 0.02399115078151226, 0);
  g->Transpose(6969, 4993, {1,0});
  g->Binary(ynn_binary_multiply, 4938, 4992, 4989);
  g->Dot(2661, 4993, YNN_INVALID_VALUE_ID, 4988, 1);
  g->DequantizeTensor(4988, YNN_INVALID_VALUE_ID, 4989, 4990);
  g->QuantizeTensor(4990, 6504, 4991, 2662);
  g->Dequantize(2662, 2663, 0.06142711639404297, 0);
}

// Scope: "Layer31 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer31Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2623, 2624);
  g->Reduce(ynn_reduce_sum, 2624, 6219, {2}, true);
  g->ShapeProduct(2624, 6218, {2});
  g->Binary(ynn_binary_divide, 6219, 6218, 2625);
  g->Binary(ynn_binary_add, 2625, 6539, 2627);
  g->Unary(ynn_unary_rsqrt, 2627, 2628);
  g->Binary(ynn_binary_multiply, 2623, 2628, 2629);
  g->Binary(ynn_binary_multiply, 2629, 6958, 2630);
  BuildLayer31AttentionQueryProjection(ctx);
  BuildLayer31AttentionSdpa(ctx);
  BuildLayer31AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2663, 2664);
  g->Reduce(ynn_reduce_sum, 2664, 6228, {2}, true);
  g->ShapeProduct(2664, 6227, {2});
  g->Binary(ynn_binary_divide, 6228, 6227, 2665);
  g->Binary(ynn_binary_add, 2665, 6539, 2666);
  g->Unary(ynn_unary_rsqrt, 2666, 2667);
  g->Binary(ynn_binary_multiply, 2663, 2667, 2668);
  g->Binary(ynn_binary_multiply, 2668, 6965, 2669);
  g->Binary(ynn_binary_add, 2669, 2623, 2670);
}

// Scope: "Layer31 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer31Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2670, 2672);
  g->Reduce(ynn_reduce_sum, 2672, 6230, {2}, true);
  g->ShapeProduct(2672, 6229, {2});
  g->Binary(ynn_binary_divide, 6230, 6229, 2673);
  g->Binary(ynn_binary_add, 2673, 6539, 2674);
  g->Unary(ynn_unary_rsqrt, 2674, 2675);
  g->Binary(ynn_binary_multiply, 2670, 2675, 2676);
  g->Binary(ynn_binary_multiply, 2676, 6968, 2677);
  g->Quantize(2677, 2678, 0.01708538644015789, 0);
  g->Transpose(6962, 5000, {1,0});
  g->Binary(ynn_binary_multiply, 4997, 4999, 4995);
  g->Dot(2678, 5000, YNN_INVALID_VALUE_ID, 4994, 1);
  g->DequantizeTensor(4994, YNN_INVALID_VALUE_ID, 4995, 4996);
  g->QuantizeTensor(4996, 6504, 4998, 2679);
  g->Dequantize(2679, 2680, 0.01771654561161995, 0);
  g->Transpose(6961, 5005, {1,0});
  g->Binary(ynn_binary_multiply, 4997, 5004, 5002);
  g->Dot(2678, 5005, YNN_INVALID_VALUE_ID, 5001, 1);
  g->DequantizeTensor(5001, YNN_INVALID_VALUE_ID, 5002, 5003);
  g->QuantizeTensor(5003, 6504, 4998, 2682);
  g->Dequantize(2682, 2683, 0.01771654561161995, 0);
  g->Polynomial(2683, 6235, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6235, 6236);
  g->Binary(ynn_binary_add, 6236, 5500, 6233);
  g->Binary(ynn_binary_multiply, 2683, 5498, 6234);
  g->Binary(ynn_binary_multiply, 6234, 6233, 2684);
  g->Binary(ynn_binary_multiply, 2680, 2684, 2685);
  g->Quantize(2685, 2686, 0.027189970016479492, 0);
  g->Transpose(6960, 5012, {1,0});
  g->Binary(ynn_binary_multiply, 5009, 5011, 5007);
  g->Dot(2686, 5012, YNN_INVALID_VALUE_ID, 5006, 1);
  g->DequantizeTensor(5006, YNN_INVALID_VALUE_ID, 5007, 5008);
  g->QuantizeTensor(5008, 6504, 5010, 2687);
  g->Dequantize(2687, 2688, 0.11200025677680969, 0);
  g->Unary(ynn_unary_square, 2688, 2689);
  g->Reduce(ynn_reduce_sum, 2689, 6238, {2}, true);
  g->ShapeProduct(2689, 6237, {2});
  g->Binary(ynn_binary_divide, 6238, 6237, 2690);
  g->Binary(ynn_binary_add, 2690, 6539, 2691);
  g->Unary(ynn_unary_rsqrt, 2691, 2693);
  g->Binary(ynn_binary_multiply, 2688, 2693, 2694);
  g->Binary(ynn_binary_multiply, 2694, 6966, 2695);
  g->Binary(ynn_binary_add, 2695, 2670, 2696);
}

// Scope: "Layer31 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer31PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(427, 2697, {0,0,31,0}, {-1,-1,1,-1});
  g->Reshape(2697, 2698, {1,1,256});
  g->Unary(ynn_unary_square, 2698, 2699);
  g->Reduce(ynn_reduce_sum, 2699, 6240, {2}, true);
  g->ShapeProduct(2699, 6239, {2});
  g->Binary(ynn_binary_divide, 6240, 6239, 2700);
  g->Binary(ynn_binary_add, 2700, 6539, 2701);
  g->Unary(ynn_unary_rsqrt, 2701, 2702);
  g->Binary(ynn_binary_multiply, 2698, 2702, 2704);
  g->Binary(ynn_binary_multiply, 2704, 7118, 2705);
  g->Binary(ynn_binary_multiply, 7144, 6542, 2706);
  g->Binary(ynn_binary_add, 2705, 2706, 2707);
  g->Binary(ynn_binary_multiply, 2707, 6536, 2708);
  g->Quantize(2696, 2709, 0.1916448324918747, 0);
  g->Transpose(6963, 5018, {1,0});
  g->Binary(ynn_binary_multiply, 5016, 5017, 5014);
  g->Dot(2709, 5018, YNN_INVALID_VALUE_ID, 5013, 1);
  g->DequantizeTensor(5013, YNN_INVALID_VALUE_ID, 5014, 5015);
  g->QuantizeTensor(5015, 6504, 4827, 2710);
  g->Dequantize(2710, 2711, 0.07578741014003754, 0);
  g->Polynomial(2711, 6243, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6243, 6244);
  g->Binary(ynn_binary_add, 6244, 5500, 6241);
  g->Binary(ynn_binary_multiply, 2711, 5498, 6242);
  g->Binary(ynn_binary_multiply, 6242, 6241, 2712);
  g->Binary(ynn_binary_multiply, 2712, 2708, 2713);
  g->Quantize(2713, 2715, 0.24507875740528107, 0);
  g->Transpose(6964, 5025, {1,0});
  g->Binary(ynn_binary_multiply, 5022, 5024, 5020);
  g->Dot(2715, 5025, YNN_INVALID_VALUE_ID, 5019, 1);
  g->DequantizeTensor(5019, YNN_INVALID_VALUE_ID, 5020, 5021);
  g->QuantizeTensor(5021, 6504, 5023, 2716);
  g->Dequantize(2716, 2717, 0.3233283758163452, 0);
  g->Unary(ynn_unary_square, 2717, 2718);
  g->Reduce(ynn_reduce_sum, 2718, 6246, {2}, true);
  g->ShapeProduct(2718, 6245, {2});
  g->Binary(ynn_binary_divide, 6246, 6245, 2719);
  g->Binary(ynn_binary_add, 2719, 6539, 2720);
  g->Unary(ynn_unary_rsqrt, 2720, 2721);
  g->Binary(ynn_binary_multiply, 2717, 2721, 2722);
  g->Binary(ynn_binary_multiply, 2722, 6967, 2723);
  g->Binary(ynn_binary_add, 2696, 2723, 2724);
  g->Binary(ynn_binary_multiply, 2724, 6959, 2727);
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
  g->Quantize(2733, 2734, 0.6824333071708679, 0);
  g->Transpose(6985, 5032, {1,0});
  g->Binary(ynn_binary_multiply, 5029, 5031, 5027);
  g->Dot(2734, 5032, YNN_INVALID_VALUE_ID, 5026, 1);
  g->DequantizeTensor(5026, YNN_INVALID_VALUE_ID, 5027, 5028);
  g->QuantizeTensor(5028, 6504, 5030, 2735);
  g->Dequantize(2735, 2736, 0.4645669162273407, 0);
  g->SplitDim(2736, 2738, 2, {8,256});
  g->FuseDims(2738, 2740, 1, 2);
  g->SplitDim(2740, 2739, 1, {8,1});
  g->Unary(ynn_unary_square, 2739, 2741);
  g->Reduce(ynn_reduce_sum, 2741, 6250, {3}, true);
  g->ShapeProduct(2741, 6249, {3});
  g->Binary(ynn_binary_divide, 6250, 6249, 2742);
  g->Binary(ynn_binary_add, 2742, 6539, 2743);
  g->Unary(ynn_unary_rsqrt, 2743, 2744);
  g->Binary(ynn_binary_multiply, 2739, 2744, 2745);
  g->Binary(ynn_binary_multiply, 2745, 6984, 2746);
  g->Slice(2746, 2747, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2746, 2748, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2748, 2750);
  g->Concat({2750,2747}, 2751, 3);
  g->Binary(ynn_binary_multiply, 2746, 3067, 2752);
  g->Binary(ynn_binary_multiply, 2751, 3172, 2753);
  g->Binary(ynn_binary_add, 2752, 2753, 2754);
}

// Scope: "Layer32 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer32AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7190, 2755, 0.0059552486054599285, 0);
  g->Dequantize(7205, 2756, 0.047244105488061905, 0);
  g->Matmul(2754, 2755, 2757, false, true);
  g->Mask(2757, 6571, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6571, 6254, {-1}, true);
  g->Binary(ynn_binary_subtract, 6571, 6254, 6251);
  g->Unary(ynn_unary_exp, 6251, 6252);
  g->Reduce(ynn_reduce_sum, 6252, 6255, {-1}, true);
  g->Binary(ynn_binary_divide, 5500, 6255, 6253);
  g->Binary(ynn_binary_multiply, 6252, 6253, 2758);
  g->Matmul(2758, 2756, 2760, false, false);
}

// Scope: "Layer32 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer32AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(2760, 2762, 1, 2);
  g->SplitDim(2762, 2761, 1, {1,8});
  g->FuseDims(2761, 2763, 2, 2);
  g->Quantize(2763, 2764, 0.023006899282336235, 0);
  g->Transpose(6983, 5045, {1,0});
  g->Binary(ynn_binary_multiply, 4334, 5044, 5041);
  g->Dot(2764, 5045, YNN_INVALID_VALUE_ID, 5040, 1);
  g->DequantizeTensor(5040, YNN_INVALID_VALUE_ID, 5041, 5042);
  g->QuantizeTensor(5042, 6504, 5043, 2765);
  g->Dequantize(2765, 2766, 0.056797921657562256, 0);
}

// Scope: "Layer32 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer32Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2727, 2728);
  g->Reduce(ynn_reduce_sum, 2728, 6248, {2}, true);
  g->ShapeProduct(2728, 6247, {2});
  g->Binary(ynn_binary_divide, 6248, 6247, 2729);
  g->Binary(ynn_binary_add, 2729, 6539, 2730);
  g->Unary(ynn_unary_rsqrt, 2730, 2731);
  g->Binary(ynn_binary_multiply, 2727, 2731, 2732);
  g->Binary(ynn_binary_multiply, 2732, 6972, 2733);
  BuildLayer32AttentionQueryProjection(ctx);
  BuildLayer32AttentionSdpa(ctx);
  BuildLayer32AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2766, 2767);
  g->Reduce(ynn_reduce_sum, 2767, 6257, {2}, true);
  g->ShapeProduct(2767, 6256, {2});
  g->Binary(ynn_binary_divide, 6257, 6256, 2768);
  g->Binary(ynn_binary_add, 2768, 6539, 2769);
  g->Unary(ynn_unary_rsqrt, 2769, 2770);
  g->Binary(ynn_binary_multiply, 2766, 2770, 2771);
  g->Binary(ynn_binary_multiply, 2771, 6979, 2772);
  g->Binary(ynn_binary_add, 2772, 2727, 2773);
}

// Scope: "Layer32 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer32Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2773, 2774);
  g->Reduce(ynn_reduce_sum, 2774, 6259, {2}, true);
  g->ShapeProduct(2774, 6258, {2});
  g->Binary(ynn_binary_divide, 6259, 6258, 2775);
  g->Binary(ynn_binary_add, 2775, 6539, 2776);
  g->Unary(ynn_unary_rsqrt, 2776, 2777);
  g->Binary(ynn_binary_multiply, 2773, 2777, 2778);
  g->Binary(ynn_binary_multiply, 2778, 6982, 2779);
  g->Quantize(2779, 2780, 0.014212466776371002, 0);
  g->Transpose(6976, 5057, {1,0});
  g->Binary(ynn_binary_multiply, 5054, 5056, 5052);
  g->Dot(2780, 5057, YNN_INVALID_VALUE_ID, 5051, 1);
  g->DequantizeTensor(5051, YNN_INVALID_VALUE_ID, 5052, 5053);
  g->QuantizeTensor(5053, 6504, 5055, 2782);
  g->Dequantize(2782, 2783, 0.019192922860383987, 0);
  g->Transpose(6975, 5062, {1,0});
  g->Binary(ynn_binary_multiply, 5054, 5061, 5059);
  g->Dot(2780, 5062, YNN_INVALID_VALUE_ID, 5058, 1);
  g->DequantizeTensor(5058, YNN_INVALID_VALUE_ID, 5059, 5060);
  g->QuantizeTensor(5060, 6504, 5055, 2784);
  g->Dequantize(2784, 2785, 0.019192922860383987, 0);
  g->Polynomial(2785, 6262, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6262, 6263);
  g->Binary(ynn_binary_add, 6263, 5500, 6260);
  g->Binary(ynn_binary_multiply, 2785, 5498, 6261);
  g->Binary(ynn_binary_multiply, 6261, 6260, 2786);
  g->Binary(ynn_binary_multiply, 2783, 2786, 2787);
  g->Quantize(2787, 2788, 0.025221465155482292, 0);
  g->Transpose(6974, 5068, {1,0});
  g->Binary(ynn_binary_multiply, 4492, 5067, 5064);
  g->Dot(2788, 5068, YNN_INVALID_VALUE_ID, 5063, 1);
  g->DequantizeTensor(5063, YNN_INVALID_VALUE_ID, 5064, 5065);
  g->QuantizeTensor(5065, 6504, 5066, 2789);
  g->Dequantize(2789, 2790, 0.07002133876085281, 0);
  g->Unary(ynn_unary_square, 2790, 2792);
  g->Reduce(ynn_reduce_sum, 2792, 6265, {2}, true);
  g->ShapeProduct(2792, 6264, {2});
  g->Binary(ynn_binary_divide, 6265, 6264, 2793);
  g->Binary(ynn_binary_add, 2793, 6539, 2794);
  g->Unary(ynn_unary_rsqrt, 2794, 2795);
  g->Binary(ynn_binary_multiply, 2790, 2795, 2796);
  g->Binary(ynn_binary_multiply, 2796, 6980, 2797);
  g->Binary(ynn_binary_add, 2797, 2773, 2798);
}

// Scope: "Layer32 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer32PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(427, 2799, {0,0,32,0}, {-1,-1,1,-1});
  g->Reshape(2799, 2800, {1,1,256});
  g->Unary(ynn_unary_square, 2800, 2801);
  g->Reduce(ynn_reduce_sum, 2801, 6271, {2}, true);
  g->ShapeProduct(2801, 6270, {2});
  g->Binary(ynn_binary_divide, 6271, 6270, 2803);
  g->Binary(ynn_binary_add, 2803, 6539, 2804);
  g->Unary(ynn_unary_rsqrt, 2804, 2805);
  g->Binary(ynn_binary_multiply, 2800, 2805, 2806);
  g->Binary(ynn_binary_multiply, 2806, 7118, 2807);
  g->Binary(ynn_binary_multiply, 7145, 6542, 2808);
  g->Binary(ynn_binary_add, 2807, 2808, 2809);
  g->Binary(ynn_binary_multiply, 2809, 6536, 2810);
  g->Quantize(2798, 2811, 0.19188754260540009, 0);
  g->Transpose(6977, 5074, {1,0});
  g->Binary(ynn_binary_multiply, 5072, 5073, 5070);
  g->Dot(2811, 5074, YNN_INVALID_VALUE_ID, 5069, 1);
  g->DequantizeTensor(5069, YNN_INVALID_VALUE_ID, 5070, 5071);
  g->QuantizeTensor(5071, 6504, 4813, 2812);
  g->Dequantize(2812, 2814, 0.09104331582784653, 0);
  g->Polynomial(2814, 6274, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6274, 6275);
  g->Binary(ynn_binary_add, 6275, 5500, 6272);
  g->Binary(ynn_binary_multiply, 2814, 5498, 6273);
  g->Binary(ynn_binary_multiply, 6273, 6272, 2815);
  g->Binary(ynn_binary_multiply, 2815, 2810, 2816);
  g->Quantize(2816, 2817, 0.18700788915157318, 0);
  g->Transpose(6978, 5080, {1,0});
  g->Binary(ynn_binary_multiply, 4977, 5079, 5076);
  g->Dot(2817, 5080, YNN_INVALID_VALUE_ID, 5075, 1);
  g->DequantizeTensor(5075, YNN_INVALID_VALUE_ID, 5076, 5077);
  g->QuantizeTensor(5077, 6504, 5078, 2818);
  g->Dequantize(2818, 2819, 0.21407830715179443, 0);
  g->Unary(ynn_unary_square, 2819, 2820);
  g->Reduce(ynn_reduce_sum, 2820, 6277, {2}, true);
  g->ShapeProduct(2820, 6276, {2});
  g->Binary(ynn_binary_divide, 6277, 6276, 2821);
  g->Binary(ynn_binary_add, 2821, 6539, 2822);
  g->Unary(ynn_unary_rsqrt, 2822, 2823);
  g->Binary(ynn_binary_multiply, 2819, 2823, 2825);
  g->Binary(ynn_binary_multiply, 2825, 6981, 2826);
  g->Binary(ynn_binary_add, 2798, 2826, 2827);
  g->Binary(ynn_binary_multiply, 2827, 6973, 2828);
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
  g->Quantize(2834, 2837, 0.9355496764183044, 0);
  g->Transpose(6999, 5094, {1,0});
  g->Binary(ynn_binary_multiply, 5091, 5093, 5089);
  g->Dot(2837, 5094, YNN_INVALID_VALUE_ID, 5088, 1);
  g->DequantizeTensor(5088, YNN_INVALID_VALUE_ID, 5089, 5090);
  g->QuantizeTensor(5090, 6504, 5092, 2838);
  g->Dequantize(2838, 2839, 0.33464565873146057, 0);
  g->SplitDim(2839, 2840, 2, {8,256});
  g->FuseDims(2840, 2842, 1, 2);
  g->SplitDim(2842, 2841, 1, {8,1});
  g->Unary(ynn_unary_square, 2841, 2843);
  g->Reduce(ynn_reduce_sum, 2843, 6281, {3}, true);
  g->ShapeProduct(2843, 6280, {3});
  g->Binary(ynn_binary_divide, 6281, 6280, 2844);
  g->Binary(ynn_binary_add, 2844, 6539, 2845);
  g->Unary(ynn_unary_rsqrt, 2845, 2846);
  g->Binary(ynn_binary_multiply, 2841, 2846, 2847);
  g->Binary(ynn_binary_multiply, 2847, 6998, 2849);
  g->Slice(2849, 2850, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2849, 2851, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2851, 2852);
  g->Concat({2852,2850}, 2853, 3);
  g->Binary(ynn_binary_multiply, 2849, 3067, 2854);
  g->Binary(ynn_binary_multiply, 2853, 3172, 2855);
  g->Binary(ynn_binary_add, 2854, 2855, 2856);
}

// Scope: "Layer33 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer33AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7190, 2857, 0.0059552486054599285, 0);
  g->Dequantize(7205, 2858, 0.047244105488061905, 0);
  g->Matmul(2856, 2857, 2860, false, true);
  g->Mask(2860, 6572, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6572, 6285, {-1}, true);
  g->Binary(ynn_binary_subtract, 6572, 6285, 6282);
  g->Unary(ynn_unary_exp, 6282, 6283);
  g->Reduce(ynn_reduce_sum, 6283, 6286, {-1}, true);
  g->Binary(ynn_binary_divide, 5500, 6286, 6284);
  g->Binary(ynn_binary_multiply, 6283, 6284, 2861);
  g->Matmul(2861, 2858, 2862, false, false);
}

// Scope: "Layer33 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer33AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(2862, 2864, 1, 2);
  g->SplitDim(2864, 2863, 1, {1,8});
  g->FuseDims(2863, 2865, 2, 2);
  g->Quantize(2865, 2866, 0.02276083640754223, 0);
  g->Transpose(6997, 5100, {1,0});
  g->Binary(ynn_binary_multiply, 4453, 5099, 5096);
  g->Dot(2866, 5100, YNN_INVALID_VALUE_ID, 5095, 1);
  g->DequantizeTensor(5095, YNN_INVALID_VALUE_ID, 5096, 5097);
  g->QuantizeTensor(5097, 6504, 5098, 2867);
  g->Dequantize(2867, 2868, 0.02861599810421467, 0);
}

// Scope: "Layer33 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer33Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2828, 2829);
  g->Reduce(ynn_reduce_sum, 2829, 6279, {2}, true);
  g->ShapeProduct(2829, 6278, {2});
  g->Binary(ynn_binary_divide, 6279, 6278, 2830);
  g->Binary(ynn_binary_add, 2830, 6539, 2831);
  g->Unary(ynn_unary_rsqrt, 2831, 2832);
  g->Binary(ynn_binary_multiply, 2828, 2832, 2833);
  g->Binary(ynn_binary_multiply, 2833, 6986, 2834);
  BuildLayer33AttentionQueryProjection(ctx);
  BuildLayer33AttentionSdpa(ctx);
  BuildLayer33AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2868, 2869);
  g->Reduce(ynn_reduce_sum, 2869, 6290, {2}, true);
  g->ShapeProduct(2869, 6289, {2});
  g->Binary(ynn_binary_divide, 6290, 6289, 2871);
  g->Binary(ynn_binary_add, 2871, 6539, 2872);
  g->Unary(ynn_unary_rsqrt, 2872, 2873);
  g->Binary(ynn_binary_multiply, 2868, 2873, 2874);
  g->Binary(ynn_binary_multiply, 2874, 6993, 2875);
  g->Binary(ynn_binary_add, 2875, 2828, 2876);
}

// Scope: "Layer33 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer33Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2876, 2877);
  g->Reduce(ynn_reduce_sum, 2877, 6292, {2}, true);
  g->ShapeProduct(2877, 6291, {2});
  g->Binary(ynn_binary_divide, 6292, 6291, 2878);
  g->Binary(ynn_binary_add, 2878, 6539, 2879);
  g->Unary(ynn_unary_rsqrt, 2879, 2880);
  g->Binary(ynn_binary_multiply, 2876, 2880, 2882);
  g->Binary(ynn_binary_multiply, 2882, 6996, 2883);
  g->Quantize(2883, 2884, 0.016980575397610664, 0);
  g->Transpose(6990, 5107, {1,0});
  g->Binary(ynn_binary_multiply, 5104, 5106, 5102);
  g->Dot(2884, 5107, YNN_INVALID_VALUE_ID, 5101, 1);
  g->DequantizeTensor(5101, YNN_INVALID_VALUE_ID, 5102, 5103);
  g->QuantizeTensor(5103, 6504, 5105, 2885);
  g->Dequantize(2885, 2886, 0.018700797110795975, 0);
  g->Transpose(6989, 5112, {1,0});
  g->Binary(ynn_binary_multiply, 5104, 5111, 5109);
  g->Dot(2884, 5112, YNN_INVALID_VALUE_ID, 5108, 1);
  g->DequantizeTensor(5108, YNN_INVALID_VALUE_ID, 5109, 5110);
  g->QuantizeTensor(5110, 6504, 5105, 2887);
  g->Dequantize(2887, 2888, 0.018700797110795975, 0);
  g->Polynomial(2888, 6295, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6295, 6296);
  g->Binary(ynn_binary_add, 6296, 5500, 6293);
  g->Binary(ynn_binary_multiply, 2888, 5498, 6294);
  g->Binary(ynn_binary_multiply, 6294, 6293, 2889);
  g->Binary(ynn_binary_multiply, 2886, 2889, 2890);
  g->Quantize(2890, 2892, 0.02989666350185871, 0);
  g->Transpose(6988, 5119, {1,0});
  g->Binary(ynn_binary_multiply, 5116, 5118, 5114);
  g->Dot(2892, 5119, YNN_INVALID_VALUE_ID, 5113, 1);
  g->DequantizeTensor(5113, YNN_INVALID_VALUE_ID, 5114, 5115);
  g->QuantizeTensor(5115, 6504, 5117, 2893);
  g->Dequantize(2893, 2894, 0.053163815289735794, 0);
  g->Unary(ynn_unary_square, 2894, 2895);
  g->Reduce(ynn_reduce_sum, 2895, 6298, {2}, true);
  g->ShapeProduct(2895, 6297, {2});
  g->Binary(ynn_binary_divide, 6298, 6297, 2896);
  g->Binary(ynn_binary_add, 2896, 6539, 2897);
  g->Unary(ynn_unary_rsqrt, 2897, 2898);
  g->Binary(ynn_binary_multiply, 2894, 2898, 2899);
  g->Binary(ynn_binary_multiply, 2899, 6994, 2900);
  g->Binary(ynn_binary_add, 2900, 2876, 2901);
}

// Scope: "Layer33 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer33PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(427, 2903, {0,0,33,0}, {-1,-1,1,-1});
  g->Reshape(2903, 2904, {1,1,256});
  g->Unary(ynn_unary_square, 2904, 2905);
  g->Reduce(ynn_reduce_sum, 2905, 6300, {2}, true);
  g->ShapeProduct(2905, 6299, {2});
  g->Binary(ynn_binary_divide, 6300, 6299, 2906);
  g->Binary(ynn_binary_add, 2906, 6539, 2907);
  g->Unary(ynn_unary_rsqrt, 2907, 2908);
  g->Binary(ynn_binary_multiply, 2904, 2908, 2909);
  g->Binary(ynn_binary_multiply, 2909, 7118, 2910);
  g->Binary(ynn_binary_multiply, 7146, 6542, 2911);
  g->Binary(ynn_binary_add, 2910, 2911, 2912);
  g->Binary(ynn_binary_multiply, 2912, 6536, 2914);
  g->Quantize(2901, 2915, 0.13243837654590607, 0);
  g->Transpose(6991, 5126, {1,0});
  g->Binary(ynn_binary_multiply, 5123, 5125, 5121);
  g->Dot(2915, 5126, YNN_INVALID_VALUE_ID, 5120, 1);
  g->DequantizeTensor(5120, YNN_INVALID_VALUE_ID, 5121, 5122);
  g->QuantizeTensor(5122, 6504, 5124, 2916);
  g->Dequantize(2916, 2917, 0.1446850597858429, 0);
  g->Polynomial(2917, 6303, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6303, 6304);
  g->Binary(ynn_binary_add, 6304, 5500, 6301);
  g->Binary(ynn_binary_multiply, 2917, 5498, 6302);
  g->Binary(ynn_binary_multiply, 6302, 6301, 2918);
  g->Binary(ynn_binary_multiply, 2918, 2914, 2919);
  g->Quantize(2919, 2920, 1.5826771259307861, 0);
  g->Transpose(6992, 5133, {1,0});
  g->Binary(ynn_binary_multiply, 5130, 5132, 5128);
  g->Dot(2920, 5133, YNN_INVALID_VALUE_ID, 5127, 1);
  g->DequantizeTensor(5127, YNN_INVALID_VALUE_ID, 5128, 5129);
  g->QuantizeTensor(5129, 6504, 5131, 2921);
  g->Dequantize(2921, 2922, 0.6353945732116699, 0);
  g->Unary(ynn_unary_square, 2922, 2923);
  g->Reduce(ynn_reduce_sum, 2923, 6306, {2}, true);
  g->ShapeProduct(2923, 6305, {2});
  g->Binary(ynn_binary_divide, 6306, 6305, 2925);
  g->Binary(ynn_binary_add, 2925, 6539, 2926);
  g->Unary(ynn_unary_rsqrt, 2926, 2927);
  g->Binary(ynn_binary_multiply, 2922, 2927, 2928);
  g->Binary(ynn_binary_multiply, 2928, 6995, 2929);
  g->Binary(ynn_binary_add, 2901, 2929, 2930);
  g->Binary(ynn_binary_multiply, 2930, 6987, 2931);
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
  g->Quantize(2938, 2939, 1.450958251953125, 0);
  g->Transpose(7013, 5140, {1,0});
  g->Binary(ynn_binary_multiply, 5137, 5139, 5135);
  g->Dot(2939, 5140, YNN_INVALID_VALUE_ID, 5134, 1);
  g->DequantizeTensor(5134, YNN_INVALID_VALUE_ID, 5135, 5136);
  g->QuantizeTensor(5136, 6504, 5138, 2940);
  g->Dequantize(2940, 2941, 0.6535432934761047, 0);
  g->SplitDim(2941, 2942, 2, {8,512});
  g->FuseDims(2942, 2944, 1, 2);
  g->SplitDim(2944, 2943, 1, {8,1});
  g->Unary(ynn_unary_square, 2943, 2945);
  g->Reduce(ynn_reduce_sum, 2945, 6310, {3}, true);
  g->ShapeProduct(2945, 6309, {3});
  g->Binary(ynn_binary_divide, 6310, 6309, 2946);
  g->Binary(ynn_binary_add, 2946, 6539, 2949);
  g->Unary(ynn_unary_rsqrt, 2949, 2950);
  g->Binary(ynn_binary_multiply, 2943, 2950, 2951);
  g->Binary(ynn_binary_multiply, 2951, 7012, 2952);
  g->Slice(2952, 2953, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(2952, 2954, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 2954, 2955);
  g->Concat({2955,2953}, 2956, 3);
  g->Binary(ynn_binary_multiply, 2952, 3594, 2957);
  g->Binary(ynn_binary_multiply, 2956, 2, 2958);
  g->Binary(ynn_binary_add, 2957, 2958, 2960);
}

// Scope: "Layer34 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer34AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(7191, 2961, 0.001091228099539876, 0);
  g->Dequantize(7206, 2962, 0.01785714365541935, 0);
  g->Matmul(2960, 2961, 2963, false, true);
  g->Mask(2963, 6573, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 6573, 6314, {-1}, true);
  g->Binary(ynn_binary_subtract, 6573, 6314, 6311);
  g->Unary(ynn_unary_exp, 6311, 6312);
  g->Reduce(ynn_reduce_sum, 6312, 6315, {-1}, true);
  g->Binary(ynn_binary_divide, 5500, 6315, 6313);
  g->Binary(ynn_binary_multiply, 6312, 6313, 2964);
  g->Matmul(2964, 2962, 2965, false, false);
}

// Scope: "Layer34 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer34AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(2965, 2967, 1, 2);
  g->SplitDim(2967, 2966, 1, {1,8});
  g->FuseDims(2966, 2968, 2, 2);
  g->Quantize(2968, 2969, 0.012118612416088581, 0);
  g->Transpose(7011, 5147, {1,0});
  g->Binary(ynn_binary_multiply, 5144, 5146, 5142);
  g->Dot(2969, 5147, YNN_INVALID_VALUE_ID, 5141, 1);
  g->DequantizeTensor(5141, YNN_INVALID_VALUE_ID, 5142, 5143);
  g->QuantizeTensor(5143, 6504, 5145, 2971);
  g->Dequantize(2971, 2972, 0.017325349152088165, 0);
}

// Scope: "Layer34 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer34Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2931, 2932);
  g->Reduce(ynn_reduce_sum, 2932, 6308, {2}, true);
  g->ShapeProduct(2932, 6307, {2});
  g->Binary(ynn_binary_divide, 6308, 6307, 2933);
  g->Binary(ynn_binary_add, 2933, 6539, 2934);
  g->Unary(ynn_unary_rsqrt, 2934, 2936);
  g->Binary(ynn_binary_multiply, 2931, 2936, 2937);
  g->Binary(ynn_binary_multiply, 2937, 7000, 2938);
  BuildLayer34AttentionQueryProjection(ctx);
  BuildLayer34AttentionSdpa(ctx);
  BuildLayer34AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2972, 2973);
  g->Reduce(ynn_reduce_sum, 2973, 6319, {2}, true);
  g->ShapeProduct(2973, 6318, {2});
  g->Binary(ynn_binary_divide, 6319, 6318, 2974);
  g->Binary(ynn_binary_add, 2974, 6539, 2975);
  g->Unary(ynn_unary_rsqrt, 2975, 2976);
  g->Binary(ynn_binary_multiply, 2972, 2976, 2977);
  g->Binary(ynn_binary_multiply, 2977, 7007, 2978);
  g->Binary(ynn_binary_add, 2978, 2931, 2979);
}

// Scope: "Layer34 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer34Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2979, 2980);
  g->Reduce(ynn_reduce_sum, 2980, 6321, {2}, true);
  g->ShapeProduct(2980, 6320, {2});
  g->Binary(ynn_binary_divide, 6321, 6320, 2982);
  g->Binary(ynn_binary_add, 2982, 6539, 2983);
  g->Unary(ynn_unary_rsqrt, 2983, 2984);
  g->Binary(ynn_binary_multiply, 2979, 2984, 2985);
  g->Binary(ynn_binary_multiply, 2985, 7010, 2986);
  g->Quantize(2986, 2987, 0.022695079445838928, 0);
  g->Transpose(7004, 5154, {1,0});
  g->Binary(ynn_binary_multiply, 5151, 5153, 5149);
  g->Dot(2987, 5154, YNN_INVALID_VALUE_ID, 5148, 1);
  g->DequantizeTensor(5148, YNN_INVALID_VALUE_ID, 5149, 5150);
  g->QuantizeTensor(5150, 6504, 5152, 2988);
  g->Dequantize(2988, 2989, 0.039862215518951416, 0);
  g->Transpose(7003, 5159, {1,0});
  g->Binary(ynn_binary_multiply, 5151, 5158, 5156);
  g->Dot(2987, 5159, YNN_INVALID_VALUE_ID, 5155, 1);
  g->DequantizeTensor(5155, YNN_INVALID_VALUE_ID, 5156, 5157);
  g->QuantizeTensor(5157, 6504, 5152, 2990);
  g->Dequantize(2990, 2992, 0.039862215518951416, 0);
  g->Polynomial(2992, 6324, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6324, 6325);
  g->Binary(ynn_binary_add, 6325, 5500, 6322);
  g->Binary(ynn_binary_multiply, 2992, 5498, 6323);
  g->Binary(ynn_binary_multiply, 6323, 6322, 2993);
  g->Binary(ynn_binary_multiply, 2989, 2993, 2994);
  g->Quantize(2994, 2995, 0.09940945357084274, 0);
  g->Transpose(7002, 5166, {1,0});
  g->Binary(ynn_binary_multiply, 5163, 5165, 5161);
  g->Dot(2995, 5166, YNN_INVALID_VALUE_ID, 5160, 1);
  g->DequantizeTensor(5160, YNN_INVALID_VALUE_ID, 5161, 5162);
  g->QuantizeTensor(5162, 6504, 5164, 2996);
  g->Dequantize(2996, 2997, 0.1543705314397812, 0);
  g->Unary(ynn_unary_square, 2997, 2998);
  g->Reduce(ynn_reduce_sum, 2998, 6327, {2}, true);
  g->ShapeProduct(2998, 6326, {2});
  g->Binary(ynn_binary_divide, 6327, 6326, 2999);
  g->Binary(ynn_binary_add, 2999, 6539, 3000);
  g->Unary(ynn_unary_rsqrt, 3000, 3001);
  g->Binary(ynn_binary_multiply, 2997, 3001, 3003);
  g->Binary(ynn_binary_multiply, 3003, 7008, 3004);
  g->Binary(ynn_binary_add, 3004, 2979, 3005);
}

// Scope: "Layer34 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer34PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(427, 3006, {0,0,34,0}, {-1,-1,1,-1});
  g->Reshape(3006, 3007, {1,1,256});
  g->Unary(ynn_unary_square, 3007, 3008);
  g->Reduce(ynn_reduce_sum, 3008, 6329, {2}, true);
  g->ShapeProduct(3008, 6328, {2});
  g->Binary(ynn_binary_divide, 6329, 6328, 3009);
  g->Binary(ynn_binary_add, 3009, 6539, 3010);
  g->Unary(ynn_unary_rsqrt, 3010, 3011);
  g->Binary(ynn_binary_multiply, 3007, 3011, 3012);
  g->Binary(ynn_binary_multiply, 3012, 7118, 3014);
  g->Binary(ynn_binary_multiply, 7147, 6542, 3015);
  g->Binary(ynn_binary_add, 3014, 3015, 3016);
  g->Binary(ynn_binary_multiply, 3016, 6536, 3017);
  g->Quantize(3005, 3018, 0.8795163035392761, 0);
  g->Transpose(7005, 5173, {1,0});
  g->Binary(ynn_binary_multiply, 5170, 5172, 5168);
  g->Dot(3018, 5173, YNN_INVALID_VALUE_ID, 5167, 1);
  g->DequantizeTensor(5167, YNN_INVALID_VALUE_ID, 5168, 5169);
  g->QuantizeTensor(5169, 6504, 5171, 3019);
  g->Dequantize(3019, 3020, 0.16633859276771545, 0);
  g->Polynomial(3020, 6332, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6332, 6333);
  g->Binary(ynn_binary_add, 6333, 5500, 6330);
  g->Binary(ynn_binary_multiply, 3020, 5498, 6331);
  g->Binary(ynn_binary_multiply, 6331, 6330, 3021);
  g->Binary(ynn_binary_multiply, 3021, 3017, 3022);
  g->Quantize(3022, 3023, 3.2125983238220215, 0);
  g->Transpose(7006, 5180, {1,0});
  g->Binary(ynn_binary_multiply, 5177, 5179, 5175);
  g->Dot(3023, 5180, YNN_INVALID_VALUE_ID, 5174, 1);
  g->DequantizeTensor(5174, YNN_INVALID_VALUE_ID, 5175, 5176);
  g->QuantizeTensor(5176, 6504, 5178, 3025);
  g->Dequantize(3025, 3026, 1.0930962562561035, 0);
  g->Unary(ynn_unary_square, 3026, 3027);
  g->Reduce(ynn_reduce_sum, 3027, 6335, {2}, true);
  g->ShapeProduct(3027, 6334, {2});
  g->Binary(ynn_binary_divide, 6335, 6334, 3028);
  g->Binary(ynn_binary_add, 3028, 6539, 3029);
  g->Unary(ynn_unary_rsqrt, 3029, 3030);
  g->Binary(ynn_binary_multiply, 3026, 3030, 3031);
  g->Binary(ynn_binary_multiply, 3031, 7009, 3032);
  g->Binary(ynn_binary_add, 3005, 3032, 3033);
  g->Binary(ynn_binary_multiply, 3033, 7001, 3034);
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
  g->Unary(ynn_unary_square, 3034, 3036);
  g->Reduce(ynn_reduce_sum, 3036, 6337, {2}, true);
  g->ShapeProduct(3036, 6336, {2});
  g->Binary(ynn_binary_divide, 6337, 6336, 3037);
  g->Binary(ynn_binary_add, 3037, 6539, 3038);
  g->Unary(ynn_unary_rsqrt, 3038, 3039);
  g->Binary(ynn_binary_multiply, 3034, 3039, 3040);
  g->Binary(ynn_binary_multiply, 3040, 7116, 3041);
  g->Reduce(ynn_reduce_min_max, 3041, 5188, {-1}, true);
  g->DynamicQuantization(5188, 5187, 5186);
  g->QuantizeTensor(3041, 5187, 5186, 5185);
  g->Transpose(6543, 5191, {1,0});
  g->Binary(ynn_binary_multiply, 5186, 5189, 5182);
  g->Reduce(ynn_reduce_sum, 5191, 5190, {0}, true);
  g->Binary(ynn_binary_multiply, 5187, 5190, 5184);
  g->Unary(ynn_unary_negate, 5184, 5183);
  g->Dot(5185, 5191, 5183, 5181, 1);
  g->DequantizeTensor(5181, YNN_INVALID_VALUE_ID, 5182, 3042);
  g->Binary(ynn_binary_multiply, 3042, 6580, 3043);
  g->Unary(ynn_unary_tanh, 3043, 3044);
  g->Binary(ynn_binary_multiply, 3044, 6537, 6544);
  g->ResultShape(6544, {slinky::expr(int64_t{1}),slinky::expr(int64_t{1}),slinky::expr(int64_t{262144})});
}

}  // namespace BuildGemma4DecodeSource
