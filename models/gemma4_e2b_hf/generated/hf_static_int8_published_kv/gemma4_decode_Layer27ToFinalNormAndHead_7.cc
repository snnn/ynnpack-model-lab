// Generated YNNPACK builder; do not edit.
#include "gemma4_decode_builder.h"

namespace BuildGemma4DecodeSource {

// Scope: "Layer27 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer27AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(2177, 2179, 0.3104223608970642, 0);
  g->Transpose(6735, 4720, {1,0});
  g->Binary(ynn_binary_multiply, 4717, 4719, 4715);
  g->Dot(2179, 4720, YNN_INVALID_VALUE_ID, 4714, 1);
  g->DequantizeTensor(4714, YNN_INVALID_VALUE_ID, 4715, 4716);
  g->QuantizeTensor(4716, 6342, 4718, 2180);
  g->Dequantize(2180, 2181, 0.437007874250412, 0);
  g->SplitDim(2181, 2182, 2, {8,256});
  g->Transpose(2182, 2183, {0,2,1,3});
  g->Unary(ynn_unary_square, 2183, 2184);
  g->Reduce(ynn_reduce_sum, 2184, 5972, {3}, true);
  g->ShapeProduct(2184, 5971, {3});
  g->Binary(ynn_binary_divide, 5972, 5971, 2185);
  g->Binary(ynn_binary_add, 2185, 6376, 2186);
  g->Binary(ynn_binary_pow, 2186, 6378, 2187);
  g->Binary(ynn_binary_multiply, 2183, 2187, 2188);
  g->Convert(6734, 2190);
  g->Binary(ynn_binary_multiply, 2188, 2190, 2191);
  g->Slice(2191, 2192, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2191, 2193, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2193, 2194);
  g->Concat({2194,2192}, 2195, 3);
  g->Binary(ynn_binary_multiply, 2191, 2133, 2196);
  g->Binary(ynn_binary_multiply, 2195, 2992, 2197);
  g->Binary(ynn_binary_add, 2196, 2197, 2198);
}

// Scope: "Layer27 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer27AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(2198, 762, 2199, false, true);
  g->Mask(2199, 6403, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6403, 5976, {-1}, true);
  g->Binary(ynn_binary_subtract, 6403, 5976, 5973);
  g->Unary(ynn_unary_exp, 5973, 5974);
  g->Reduce(ynn_reduce_sum, 5974, 5977, {-1}, true);
  g->Binary(ynn_binary_divide, 5404, 5977, 5975);
  g->Binary(ynn_binary_multiply, 5974, 5975, 2201);
  g->Matmul(2201, 764, 2202, false, false);
}

// Scope: "Layer27 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer27AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(2202, 2203, {0,2,1,3});
  g->FuseDims(2203, 2204, 2, 2);
  g->Quantize(2204, 2205, 0.024237213656306267, 0);
  g->Transpose(6733, 4727, {1,0});
  g->Binary(ynn_binary_multiply, 4724, 4726, 4722);
  g->Dot(2205, 4727, YNN_INVALID_VALUE_ID, 4721, 1);
  g->DequantizeTensor(4721, YNN_INVALID_VALUE_ID, 4722, 4723);
  g->QuantizeTensor(4723, 6342, 4725, 2206);
  g->Dequantize(2206, 2207, 0.05315101891756058, 0);
}

// Scope: "Layer27 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer27Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2170, 2171);
  g->Reduce(ynn_reduce_sum, 2171, 5970, {2}, true);
  g->ShapeProduct(2171, 5969, {2});
  g->Binary(ynn_binary_divide, 5970, 5969, 2172);
  g->Binary(ynn_binary_add, 2172, 6376, 2173);
  g->Binary(ynn_binary_pow, 2173, 6378, 2174);
  g->Binary(ynn_binary_multiply, 2170, 2174, 2175);
  g->Convert(6722, 2176);
  g->Binary(ynn_binary_multiply, 2175, 2176, 2177);
  BuildLayer27AttentionQueryProjection(ctx);
  BuildLayer27AttentionSdpa(ctx);
  BuildLayer27AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2207, 2208);
  g->Reduce(ynn_reduce_sum, 2208, 5979, {2}, true);
  g->ShapeProduct(2208, 5978, {2});
  g->Binary(ynn_binary_divide, 5979, 5978, 2209);
  g->Binary(ynn_binary_add, 2209, 6376, 2211);
  g->Binary(ynn_binary_pow, 2211, 6378, 2212);
  g->Binary(ynn_binary_multiply, 2207, 2212, 2213);
  g->Convert(6729, 2214);
  g->Binary(ynn_binary_multiply, 2213, 2214, 2215);
  g->Binary(ynn_binary_add, 2170, 2215, 2216);
}

// Scope: "Layer27 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer27Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2216, 2217);
  g->Reduce(ynn_reduce_sum, 2217, 5981, {2}, true);
  g->ShapeProduct(2217, 5980, {2});
  g->Binary(ynn_binary_divide, 5981, 5980, 2218);
  g->Binary(ynn_binary_add, 2218, 6376, 2219);
  g->Binary(ynn_binary_pow, 2219, 6378, 2220);
  g->Binary(ynn_binary_multiply, 2216, 2220, 2222);
  g->Convert(6732, 2223);
  g->Binary(ynn_binary_multiply, 2222, 2223, 2224);
  g->Quantize(2224, 2225, 0.02701687067747116, 0);
  g->Transpose(6726, 4734, {1,0});
  g->Binary(ynn_binary_multiply, 4731, 4733, 4729);
  g->Dot(2225, 4734, YNN_INVALID_VALUE_ID, 4728, 1);
  g->DequantizeTensor(4728, YNN_INVALID_VALUE_ID, 4729, 4730);
  g->QuantizeTensor(4730, 6342, 4732, 2226);
  g->Dequantize(2226, 2227, 0.044537413865327835, 0);
  g->Transpose(6725, 4739, {1,0});
  g->Binary(ynn_binary_multiply, 4731, 4738, 4736);
  g->Dot(2225, 4739, YNN_INVALID_VALUE_ID, 4735, 1);
  g->DequantizeTensor(4735, YNN_INVALID_VALUE_ID, 4736, 4737);
  g->QuantizeTensor(4737, 6342, 4732, 2228);
  g->Dequantize(2228, 2229, 0.044537413865327835, 0);
  g->Polynomial(2229, 5984, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5984, 5985);
  g->Binary(ynn_binary_add, 5985, 5404, 5982);
  g->Binary(ynn_binary_multiply, 2229, 5402, 5983);
  g->Binary(ynn_binary_multiply, 5983, 5982, 2230);
  g->Binary(ynn_binary_multiply, 2227, 2230, 2232);
  g->Quantize(2232, 2233, 0.09104331582784653, 0);
  g->Transpose(6724, 4746, {1,0});
  g->Binary(ynn_binary_multiply, 4743, 4745, 4741);
  g->Dot(2233, 4746, YNN_INVALID_VALUE_ID, 4740, 1);
  g->DequantizeTensor(4740, YNN_INVALID_VALUE_ID, 4741, 4742);
  g->QuantizeTensor(4742, 6342, 4744, 2234);
  g->Dequantize(2234, 2235, 0.08018074929714203, 0);
  g->Unary(ynn_unary_square, 2235, 2236);
  g->Reduce(ynn_reduce_sum, 2236, 5989, {2}, true);
  g->ShapeProduct(2236, 5988, {2});
  g->Binary(ynn_binary_divide, 5989, 5988, 2237);
  g->Binary(ynn_binary_add, 2237, 6376, 2238);
  g->Binary(ynn_binary_pow, 2238, 6378, 2239);
  g->Binary(ynn_binary_multiply, 2235, 2239, 2240);
  g->Convert(6730, 2241);
  g->Binary(ynn_binary_multiply, 2240, 2241, 2244);
  g->Binary(ynn_binary_add, 2216, 2244, 2245);
}

// Scope: "Layer27 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer27PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1047, 2246, {0,0,27,0}, {-1,-1,1,-1});
  g->Reshape(2246, 2247, {1,1,256});
  g->Binary(ynn_binary_add, 2247, 6976, 2248);
  g->Binary(ynn_binary_multiply, 2248, 6374, 2249);
  g->Quantize(2245, 2250, 0.12690971791744232, 0);
  g->Transpose(6727, 4753, {1,0});
  g->Binary(ynn_binary_multiply, 4750, 4752, 4748);
  g->Dot(2250, 4753, YNN_INVALID_VALUE_ID, 4747, 1);
  g->DequantizeTensor(4747, YNN_INVALID_VALUE_ID, 4748, 4749);
  g->QuantizeTensor(4749, 6342, 4751, 2251);
  g->Dequantize(2251, 2252, 0.07578741014003754, 0);
  g->Polynomial(2252, 5992, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5992, 5993);
  g->Binary(ynn_binary_add, 5993, 5404, 5990);
  g->Binary(ynn_binary_multiply, 2252, 5402, 5991);
  g->Binary(ynn_binary_multiply, 5991, 5990, 2253);
  g->Binary(ynn_binary_multiply, 2253, 2249, 2255);
  g->Quantize(2255, 2256, 0.5708661675453186, 0);
  g->Transpose(6728, 4760, {1,0});
  g->Binary(ynn_binary_multiply, 4757, 4759, 4755);
  g->Dot(2256, 4760, YNN_INVALID_VALUE_ID, 4754, 1);
  g->DequantizeTensor(4754, YNN_INVALID_VALUE_ID, 4755, 4756);
  g->QuantizeTensor(4756, 6342, 4758, 2257);
  g->Dequantize(2257, 2258, 0.26081717014312744, 0);
  g->Unary(ynn_unary_square, 2258, 2259);
  g->Reduce(ynn_reduce_sum, 2259, 5995, {2}, true);
  g->ShapeProduct(2259, 5994, {2});
  g->Binary(ynn_binary_divide, 5995, 5994, 2260);
  g->Binary(ynn_binary_add, 2260, 6376, 2261);
  g->Binary(ynn_binary_pow, 2261, 6378, 2262);
  g->Binary(ynn_binary_multiply, 2258, 2262, 2263);
  g->Convert(6731, 2264);
  g->Binary(ynn_binary_multiply, 2263, 2264, 2266);
  g->Binary(ynn_binary_add, 2245, 2266, 2267);
  g->Convert(6723, 2268);
  g->Binary(ynn_binary_multiply, 2267, 2268, 2269);
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
  g->Transpose(6749, 4767, {1,0});
  g->Binary(ynn_binary_multiply, 4764, 4766, 4762);
  g->Dot(2278, 4767, YNN_INVALID_VALUE_ID, 4761, 1);
  g->DequantizeTensor(4761, YNN_INVALID_VALUE_ID, 4762, 4763);
  g->QuantizeTensor(4763, 6342, 4765, 2279);
  g->Dequantize(2279, 2280, 0.34645670652389526, 0);
  g->SplitDim(2280, 2281, 2, {8,256});
  g->Transpose(2281, 2282, {0,2,1,3});
  g->Unary(ynn_unary_square, 2282, 2283);
  g->Reduce(ynn_reduce_sum, 2283, 5999, {3}, true);
  g->ShapeProduct(2283, 5998, {3});
  g->Binary(ynn_binary_divide, 5999, 5998, 2284);
  g->Binary(ynn_binary_add, 2284, 6376, 2285);
  g->Binary(ynn_binary_pow, 2285, 6378, 2286);
  g->Binary(ynn_binary_multiply, 2282, 2286, 2287);
  g->Convert(6748, 2288);
  g->Binary(ynn_binary_multiply, 2287, 2288, 2289);
  g->Slice(2289, 2290, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2289, 2291, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2291, 2292);
  g->Concat({2292,2290}, 2293, 3);
  g->Binary(ynn_binary_multiply, 2289, 2133, 2294);
  g->Binary(ynn_binary_multiply, 2293, 2992, 2295);
  g->Binary(ynn_binary_add, 2294, 2295, 2296);
}

// Scope: "Layer28 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer28AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(2296, 762, 2297, false, true);
  g->Mask(2297, 6404, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6404, 6003, {-1}, true);
  g->Binary(ynn_binary_subtract, 6404, 6003, 6000);
  g->Unary(ynn_unary_exp, 6000, 6001);
  g->Reduce(ynn_reduce_sum, 6001, 6004, {-1}, true);
  g->Binary(ynn_binary_divide, 5404, 6004, 6002);
  g->Binary(ynn_binary_multiply, 6001, 6002, 2298);
  g->Matmul(2298, 764, 2299, false, false);
}

// Scope: "Layer28 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer28AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(2299, 2300, {0,2,1,3});
  g->FuseDims(2300, 2301, 2, 2);
  g->Quantize(2301, 2302, 0.024237213656306267, 0);
  g->Transpose(6747, 4773, {1,0});
  g->Binary(ynn_binary_multiply, 4724, 4772, 4769);
  g->Dot(2302, 4773, YNN_INVALID_VALUE_ID, 4768, 1);
  g->DequantizeTensor(4768, YNN_INVALID_VALUE_ID, 4769, 4770);
  g->QuantizeTensor(4770, 6342, 4771, 2303);
  g->Dequantize(2303, 2304, 0.03035588562488556, 0);
}

// Scope: "Layer28 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer28Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2269, 2270);
  g->Reduce(ynn_reduce_sum, 2270, 5997, {2}, true);
  g->ShapeProduct(2270, 5996, {2});
  g->Binary(ynn_binary_divide, 5997, 5996, 2271);
  g->Binary(ynn_binary_add, 2271, 6376, 2272);
  g->Binary(ynn_binary_pow, 2272, 6378, 2273);
  g->Binary(ynn_binary_multiply, 2269, 2273, 2274);
  g->Convert(6736, 2275);
  g->Binary(ynn_binary_multiply, 2274, 2275, 2277);
  BuildLayer28AttentionQueryProjection(ctx);
  BuildLayer28AttentionSdpa(ctx);
  BuildLayer28AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2304, 2305);
  g->Reduce(ynn_reduce_sum, 2305, 6006, {2}, true);
  g->ShapeProduct(2305, 6005, {2});
  g->Binary(ynn_binary_divide, 6006, 6005, 2307);
  g->Binary(ynn_binary_add, 2307, 6376, 2308);
  g->Binary(ynn_binary_pow, 2308, 6378, 2309);
  g->Binary(ynn_binary_multiply, 2304, 2309, 2310);
  g->Convert(6743, 2311);
  g->Binary(ynn_binary_multiply, 2310, 2311, 2312);
  g->Binary(ynn_binary_add, 2269, 2312, 2313);
}

// Scope: "Layer28 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer28Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2313, 2314);
  g->Reduce(ynn_reduce_sum, 2314, 6008, {2}, true);
  g->ShapeProduct(2314, 6007, {2});
  g->Binary(ynn_binary_divide, 6008, 6007, 2315);
  g->Binary(ynn_binary_add, 2315, 6376, 2316);
  g->Binary(ynn_binary_pow, 2316, 6378, 2318);
  g->Binary(ynn_binary_multiply, 2313, 2318, 2319);
  g->Convert(6746, 2320);
  g->Binary(ynn_binary_multiply, 2319, 2320, 2321);
  g->Quantize(2321, 2322, 0.025474751368165016, 0);
  g->Transpose(6740, 4780, {1,0});
  g->Binary(ynn_binary_multiply, 4777, 4779, 4775);
  g->Dot(2322, 4780, YNN_INVALID_VALUE_ID, 4774, 1);
  g->DequantizeTensor(4774, YNN_INVALID_VALUE_ID, 4775, 4776);
  g->QuantizeTensor(4776, 6342, 4778, 2323);
  g->Dequantize(2323, 2324, 0.03494095429778099, 0);
  g->Transpose(6739, 4785, {1,0});
  g->Binary(ynn_binary_multiply, 4777, 4784, 4782);
  g->Dot(2322, 4785, YNN_INVALID_VALUE_ID, 4781, 1);
  g->DequantizeTensor(4781, YNN_INVALID_VALUE_ID, 4782, 4783);
  g->QuantizeTensor(4783, 6342, 4778, 2325);
  g->Dequantize(2325, 2326, 0.03494095429778099, 0);
  g->Polynomial(2326, 6011, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6011, 6012);
  g->Binary(ynn_binary_add, 6012, 5404, 6009);
  g->Binary(ynn_binary_multiply, 2326, 5402, 6010);
  g->Binary(ynn_binary_multiply, 6010, 6009, 2327);
  g->Binary(ynn_binary_multiply, 2324, 2327, 2328);
  g->Quantize(2328, 2329, 0.07627953588962555, 0);
  g->Transpose(6738, 4792, {1,0});
  g->Binary(ynn_binary_multiply, 4789, 4791, 4787);
  g->Dot(2329, 4792, YNN_INVALID_VALUE_ID, 4786, 1);
  g->DequantizeTensor(4786, YNN_INVALID_VALUE_ID, 4787, 4788);
  g->QuantizeTensor(4788, 6342, 4790, 2330);
  g->Dequantize(2330, 2331, 0.10797519981861115, 0);
  g->Unary(ynn_unary_square, 2331, 2332);
  g->Reduce(ynn_reduce_sum, 2332, 6014, {2}, true);
  g->ShapeProduct(2332, 6013, {2});
  g->Binary(ynn_binary_divide, 6014, 6013, 2333);
  g->Binary(ynn_binary_add, 2333, 6376, 2334);
  g->Binary(ynn_binary_pow, 2334, 6378, 2335);
  g->Binary(ynn_binary_multiply, 2331, 2335, 2336);
  g->Convert(6744, 2337);
  g->Binary(ynn_binary_multiply, 2336, 2337, 2338);
  g->Binary(ynn_binary_add, 2313, 2338, 2339);
}

// Scope: "Layer28 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer28PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1047, 2340, {0,0,28,0}, {-1,-1,1,-1});
  g->Reshape(2340, 2341, {1,1,256});
  g->Binary(ynn_binary_add, 2341, 6977, 2342);
  g->Binary(ynn_binary_multiply, 2342, 6374, 2343);
  g->Quantize(2339, 2344, 0.13722270727157593, 0);
  g->Transpose(6741, 4799, {1,0});
  g->Binary(ynn_binary_multiply, 4796, 4798, 4794);
  g->Dot(2344, 4799, YNN_INVALID_VALUE_ID, 4793, 1);
  g->DequantizeTensor(4793, YNN_INVALID_VALUE_ID, 4794, 4795);
  g->QuantizeTensor(4795, 6342, 4797, 2345);
  g->Dequantize(2345, 2346, 0.08513779938220978, 0);
  g->Polynomial(2346, 6017, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6017, 6018);
  g->Binary(ynn_binary_add, 6018, 5404, 6015);
  g->Binary(ynn_binary_multiply, 2346, 5402, 6016);
  g->Binary(ynn_binary_multiply, 6016, 6015, 2349);
  g->Binary(ynn_binary_multiply, 2349, 2343, 2350);
  g->Quantize(2350, 2351, 0.748031497001648, 0);
  g->Transpose(6742, 4806, {1,0});
  g->Binary(ynn_binary_multiply, 4803, 4805, 4801);
  g->Dot(2351, 4806, YNN_INVALID_VALUE_ID, 4800, 1);
  g->DequantizeTensor(4800, YNN_INVALID_VALUE_ID, 4801, 4802);
  g->QuantizeTensor(4802, 6342, 4804, 2352);
  g->Dequantize(2352, 2353, 0.18373137712478638, 0);
  g->Unary(ynn_unary_square, 2353, 2354);
  g->Reduce(ynn_reduce_sum, 2354, 6020, {2}, true);
  g->ShapeProduct(2354, 6019, {2});
  g->Binary(ynn_binary_divide, 6020, 6019, 2355);
  g->Binary(ynn_binary_add, 2355, 6376, 2356);
  g->Binary(ynn_binary_pow, 2356, 6378, 2357);
  g->Binary(ynn_binary_multiply, 2353, 2357, 2358);
  g->Convert(6745, 2359);
  g->Binary(ynn_binary_multiply, 2358, 2359, 2360);
  g->Binary(ynn_binary_add, 2339, 2360, 2361);
  g->Convert(6737, 2362);
  g->Binary(ynn_binary_multiply, 2361, 2362, 2363);
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
  g->Quantize(2371, 2372, 0.41653531789779663, 0);
  g->Transpose(6763, 4819, {1,0});
  g->Binary(ynn_binary_multiply, 4816, 4818, 4814);
  g->Dot(2372, 4819, YNN_INVALID_VALUE_ID, 4813, 1);
  g->DequantizeTensor(4813, YNN_INVALID_VALUE_ID, 4814, 4815);
  g->QuantizeTensor(4815, 6342, 4817, 2373);
  g->Dequantize(2373, 2374, 0.312992125749588, 0);
  g->SplitDim(2374, 2375, 2, {8,512});
  g->Transpose(2375, 2376, {0,2,1,3});
  g->Unary(ynn_unary_square, 2376, 2377);
  g->Reduce(ynn_reduce_sum, 2377, 6024, {3}, true);
  g->ShapeProduct(2377, 6023, {3});
  g->Binary(ynn_binary_divide, 6024, 6023, 2378);
  g->Binary(ynn_binary_add, 2378, 6376, 2379);
  g->Binary(ynn_binary_pow, 2379, 6378, 2381);
  g->Binary(ynn_binary_multiply, 2376, 2381, 2382);
  g->Convert(6762, 2383);
  g->Binary(ynn_binary_multiply, 2382, 2383, 2384);
  g->Slice(2384, 2385, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(2384, 2386, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 2386, 2387);
  g->Concat({2387,2385}, 2388, 3);
  g->Binary(ynn_binary_multiply, 2384, 3406, 2389);
  g->Binary(ynn_binary_multiply, 2388, 3508, 2390);
  g->Binary(ynn_binary_add, 2389, 2390, 2392);
}

// Scope: "Layer29 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer29AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(2392, 895, 2393, false, true);
  g->Mask(2393, 6405, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 6405, 6028, {-1}, true);
  g->Binary(ynn_binary_subtract, 6405, 6028, 6025);
  g->Unary(ynn_unary_exp, 6025, 6026);
  g->Reduce(ynn_reduce_sum, 6026, 6029, {-1}, true);
  g->Binary(ynn_binary_divide, 5404, 6029, 6027);
  g->Binary(ynn_binary_multiply, 6026, 6027, 2394);
  g->Matmul(2394, 897, 2395, false, false);
}

// Scope: "Layer29 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer29AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(2395, 2396, {0,2,1,3});
  g->FuseDims(2396, 2397, 2, 2);
  g->Quantize(2397, 2398, 0.017962608486413956, 0);
  g->Transpose(6761, 4825, {1,0});
  g->Binary(ynn_binary_multiply, 3743, 4824, 4821);
  g->Dot(2398, 4825, YNN_INVALID_VALUE_ID, 4820, 1);
  g->DequantizeTensor(4820, YNN_INVALID_VALUE_ID, 4821, 4822);
  g->QuantizeTensor(4822, 6342, 4823, 2399);
  g->Dequantize(2399, 2400, 0.03030368685722351, 0);
}

// Scope: "Layer29 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer29Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2363, 2364);
  g->Reduce(ynn_reduce_sum, 2364, 6022, {2}, true);
  g->ShapeProduct(2364, 6021, {2});
  g->Binary(ynn_binary_divide, 6022, 6021, 2365);
  g->Binary(ynn_binary_add, 2365, 6376, 2366);
  g->Binary(ynn_binary_pow, 2366, 6378, 2367);
  g->Binary(ynn_binary_multiply, 2363, 2367, 2368);
  g->Convert(6750, 2370);
  g->Binary(ynn_binary_multiply, 2368, 2370, 2371);
  BuildLayer29AttentionQueryProjection(ctx);
  BuildLayer29AttentionSdpa(ctx);
  BuildLayer29AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2400, 2402);
  g->Reduce(ynn_reduce_sum, 2402, 6031, {2}, true);
  g->ShapeProduct(2402, 6030, {2});
  g->Binary(ynn_binary_divide, 6031, 6030, 2403);
  g->Binary(ynn_binary_add, 2403, 6376, 2404);
  g->Binary(ynn_binary_pow, 2404, 6378, 2405);
  g->Binary(ynn_binary_multiply, 2400, 2405, 2406);
  g->Convert(6757, 2407);
  g->Binary(ynn_binary_multiply, 2406, 2407, 2408);
  g->Binary(ynn_binary_add, 2363, 2408, 2409);
}

// Scope: "Layer29 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer29Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2409, 2410);
  g->Reduce(ynn_reduce_sum, 2410, 6033, {2}, true);
  g->ShapeProduct(2410, 6032, {2});
  g->Binary(ynn_binary_divide, 6033, 6032, 2411);
  g->Binary(ynn_binary_add, 2411, 6376, 2413);
  g->Binary(ynn_binary_pow, 2413, 6378, 2414);
  g->Binary(ynn_binary_multiply, 2409, 2414, 2415);
  g->Convert(6760, 2416);
  g->Binary(ynn_binary_multiply, 2415, 2416, 2417);
  g->Quantize(2417, 2418, 0.032805636525154114, 0);
  g->Transpose(6754, 4832, {1,0});
  g->Binary(ynn_binary_multiply, 4829, 4831, 4827);
  g->Dot(2418, 4832, YNN_INVALID_VALUE_ID, 4826, 1);
  g->DequantizeTensor(4826, YNN_INVALID_VALUE_ID, 4827, 4828);
  g->QuantizeTensor(4828, 6342, 4830, 2419);
  g->Dequantize(2419, 2420, 0.03690946102142334, 0);
  g->Transpose(6753, 4837, {1,0});
  g->Binary(ynn_binary_multiply, 4829, 4836, 4834);
  g->Dot(2418, 4837, YNN_INVALID_VALUE_ID, 4833, 1);
  g->DequantizeTensor(4833, YNN_INVALID_VALUE_ID, 4834, 4835);
  g->QuantizeTensor(4835, 6342, 4830, 2421);
  g->Dequantize(2421, 2423, 0.03690946102142334, 0);
  g->Polynomial(2423, 6038, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6038, 6039);
  g->Binary(ynn_binary_add, 6039, 5404, 6036);
  g->Binary(ynn_binary_multiply, 2423, 5402, 6037);
  g->Binary(ynn_binary_multiply, 6037, 6036, 2424);
  g->Binary(ynn_binary_multiply, 2420, 2424, 2425);
  g->Quantize(2425, 2426, 0.11171260476112366, 0);
  g->Transpose(6752, 4844, {1,0});
  g->Binary(ynn_binary_multiply, 4841, 4843, 4839);
  g->Dot(2426, 4844, YNN_INVALID_VALUE_ID, 4838, 1);
  g->DequantizeTensor(4838, YNN_INVALID_VALUE_ID, 4839, 4840);
  g->QuantizeTensor(4840, 6342, 4842, 2427);
  g->Dequantize(2427, 2428, 0.3346065282821655, 0);
  g->Unary(ynn_unary_square, 2428, 2429);
  g->Reduce(ynn_reduce_sum, 2429, 6041, {2}, true);
  g->ShapeProduct(2429, 6040, {2});
  g->Binary(ynn_binary_divide, 6041, 6040, 2430);
  g->Binary(ynn_binary_add, 2430, 6376, 2431);
  g->Binary(ynn_binary_pow, 2431, 6378, 2432);
  g->Binary(ynn_binary_multiply, 2428, 2432, 2434);
  g->Convert(6758, 2435);
  g->Binary(ynn_binary_multiply, 2434, 2435, 2436);
  g->Binary(ynn_binary_add, 2409, 2436, 2437);
}

// Scope: "Layer29 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer29PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1047, 2438, {0,0,29,0}, {-1,-1,1,-1});
  g->Reshape(2438, 2439, {1,1,256});
  g->Binary(ynn_binary_add, 2439, 6978, 2440);
  g->Binary(ynn_binary_multiply, 2440, 6374, 2441);
  g->Quantize(2437, 2442, 0.1425527185201645, 0);
  g->Transpose(6755, 4850, {1,0});
  g->Binary(ynn_binary_multiply, 4848, 4849, 4846);
  g->Dot(2442, 4850, YNN_INVALID_VALUE_ID, 4845, 1);
  g->DequantizeTensor(4845, YNN_INVALID_VALUE_ID, 4846, 4847);
  g->QuantizeTensor(4847, 6342, 4183, 2443);
  g->Dequantize(2443, 2445, 0.07234252989292145, 0);
  g->Polynomial(2445, 6044, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6044, 6045);
  g->Binary(ynn_binary_add, 6045, 5404, 6042);
  g->Binary(ynn_binary_multiply, 2445, 5402, 6043);
  g->Binary(ynn_binary_multiply, 6043, 6042, 2446);
  g->Binary(ynn_binary_multiply, 2446, 2441, 2447);
  g->Quantize(2447, 2448, 0.2539370059967041, 0);
  g->Transpose(6756, 4857, {1,0});
  g->Binary(ynn_binary_multiply, 4854, 4856, 4852);
  g->Dot(2448, 4857, YNN_INVALID_VALUE_ID, 4851, 1);
  g->DequantizeTensor(4851, YNN_INVALID_VALUE_ID, 4852, 4853);
  g->QuantizeTensor(4853, 6342, 4855, 2449);
  g->Dequantize(2449, 2450, 0.2777099609375, 0);
  g->Unary(ynn_unary_square, 2450, 2451);
  g->Reduce(ynn_reduce_sum, 2451, 6047, {2}, true);
  g->ShapeProduct(2451, 6046, {2});
  g->Binary(ynn_binary_divide, 6047, 6046, 2452);
  g->Binary(ynn_binary_add, 2452, 6376, 2453);
  g->Binary(ynn_binary_pow, 2453, 6378, 2454);
  g->Binary(ynn_binary_multiply, 2450, 2454, 2457);
  g->Convert(6759, 2458);
  g->Binary(ynn_binary_multiply, 2457, 2458, 2459);
  g->Binary(ynn_binary_add, 2437, 2459, 2460);
  g->Convert(6751, 2461);
  g->Binary(ynn_binary_multiply, 2460, 2461, 2462);
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
  g->Quantize(2470, 2471, 0.621565580368042, 0);
  g->Transpose(6794, 4864, {1,0});
  g->Binary(ynn_binary_multiply, 4861, 4863, 4859);
  g->Dot(2471, 4864, YNN_INVALID_VALUE_ID, 4858, 1);
  g->DequantizeTensor(4858, YNN_INVALID_VALUE_ID, 4859, 4860);
  g->QuantizeTensor(4860, 6342, 4862, 2472);
  g->Dequantize(2472, 2473, 0.45866140723228455, 0);
  g->SplitDim(2473, 2474, 2, {8,256});
  g->Transpose(2474, 2475, {0,2,1,3});
  g->Unary(ynn_unary_square, 2475, 2476);
  g->Reduce(ynn_reduce_sum, 2476, 6051, {3}, true);
  g->ShapeProduct(2476, 6050, {3});
  g->Binary(ynn_binary_divide, 6051, 6050, 2477);
  g->Binary(ynn_binary_add, 2477, 6376, 2479);
  g->Binary(ynn_binary_pow, 2479, 6378, 2480);
  g->Binary(ynn_binary_multiply, 2475, 2480, 2481);
  g->Convert(6793, 2482);
  g->Binary(ynn_binary_multiply, 2481, 2482, 2483);
  g->Slice(2483, 2484, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2483, 2485, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2485, 2486);
  g->Concat({2486,2484}, 2487, 3);
  g->Binary(ynn_binary_multiply, 2483, 2133, 2488);
  g->Binary(ynn_binary_multiply, 2487, 2992, 2490);
  g->Binary(ynn_binary_add, 2488, 2490, 2491);
}

// Scope: "Layer30 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer30AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(2491, 762, 2492, false, true);
  g->Mask(2492, 6407, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6407, 6055, {-1}, true);
  g->Binary(ynn_binary_subtract, 6407, 6055, 6052);
  g->Unary(ynn_unary_exp, 6052, 6053);
  g->Reduce(ynn_reduce_sum, 6053, 6056, {-1}, true);
  g->Binary(ynn_binary_divide, 5404, 6056, 6054);
  g->Binary(ynn_binary_multiply, 6053, 6054, 2493);
  g->Matmul(2493, 764, 2494, false, false);
}

// Scope: "Layer30 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer30AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(2494, 2495, {0,2,1,3});
  g->FuseDims(2495, 2496, 2, 2);
  g->Quantize(2496, 2497, 0.02399115078151226, 0);
  g->Transpose(6792, 4871, {1,0});
  g->Binary(ynn_binary_multiply, 4868, 4870, 4866);
  g->Dot(2497, 4871, YNN_INVALID_VALUE_ID, 4865, 1);
  g->DequantizeTensor(4865, YNN_INVALID_VALUE_ID, 4866, 4867);
  g->QuantizeTensor(4867, 6342, 4869, 2498);
  g->Dequantize(2498, 2500, 0.05247194319963455, 0);
}

// Scope: "Layer30 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer30Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2462, 2463);
  g->Reduce(ynn_reduce_sum, 2463, 6049, {2}, true);
  g->ShapeProduct(2463, 6048, {2});
  g->Binary(ynn_binary_divide, 6049, 6048, 2464);
  g->Binary(ynn_binary_add, 2464, 6376, 2465);
  g->Binary(ynn_binary_pow, 2465, 6378, 2466);
  g->Binary(ynn_binary_multiply, 2462, 2466, 2468);
  g->Convert(6781, 2469);
  g->Binary(ynn_binary_multiply, 2468, 2469, 2470);
  BuildLayer30AttentionQueryProjection(ctx);
  BuildLayer30AttentionSdpa(ctx);
  BuildLayer30AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2500, 2501);
  g->Reduce(ynn_reduce_sum, 2501, 6058, {2}, true);
  g->ShapeProduct(2501, 6057, {2});
  g->Binary(ynn_binary_divide, 6058, 6057, 2502);
  g->Binary(ynn_binary_add, 2502, 6376, 2503);
  g->Binary(ynn_binary_pow, 2503, 6378, 2504);
  g->Binary(ynn_binary_multiply, 2500, 2504, 2505);
  g->Convert(6788, 2506);
  g->Binary(ynn_binary_multiply, 2505, 2506, 2507);
  g->Binary(ynn_binary_add, 2462, 2507, 2508);
}

// Scope: "Layer30 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer30Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2508, 2509);
  g->Reduce(ynn_reduce_sum, 2509, 6060, {2}, true);
  g->ShapeProduct(2509, 6059, {2});
  g->Binary(ynn_binary_divide, 6060, 6059, 2511);
  g->Binary(ynn_binary_add, 2511, 6376, 2512);
  g->Binary(ynn_binary_pow, 2512, 6378, 2513);
  g->Binary(ynn_binary_multiply, 2508, 2513, 2514);
  g->Convert(6791, 2515);
  g->Binary(ynn_binary_multiply, 2514, 2515, 2516);
  g->Quantize(2516, 2517, 0.02257225476205349, 0);
  g->Transpose(6785, 4878, {1,0});
  g->Binary(ynn_binary_multiply, 4875, 4877, 4873);
  g->Dot(2517, 4878, YNN_INVALID_VALUE_ID, 4872, 1);
  g->DequantizeTensor(4872, YNN_INVALID_VALUE_ID, 4873, 4874);
  g->QuantizeTensor(4874, 6342, 4876, 2518);
  g->Dequantize(2518, 2519, 0.028789378702640533, 0);
  g->Transpose(6784, 4883, {1,0});
  g->Binary(ynn_binary_multiply, 4875, 4882, 4880);
  g->Dot(2517, 4883, YNN_INVALID_VALUE_ID, 4879, 1);
  g->DequantizeTensor(4879, YNN_INVALID_VALUE_ID, 4880, 4881);
  g->QuantizeTensor(4881, 6342, 4876, 2521);
  g->Dequantize(2521, 2522, 0.028789378702640533, 0);
  g->Polynomial(2522, 6063, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6063, 6064);
  g->Binary(ynn_binary_add, 6064, 5404, 6061);
  g->Binary(ynn_binary_multiply, 2522, 5402, 6062);
  g->Binary(ynn_binary_multiply, 6062, 6061, 2523);
  g->Binary(ynn_binary_multiply, 2519, 2523, 2524);
  g->Quantize(2524, 2525, 0.07234252989292145, 0);
  g->Transpose(6783, 4889, {1,0});
  g->Binary(ynn_binary_multiply, 4183, 4888, 4885);
  g->Dot(2525, 4889, YNN_INVALID_VALUE_ID, 4884, 1);
  g->DequantizeTensor(4884, YNN_INVALID_VALUE_ID, 4885, 4886);
  g->QuantizeTensor(4886, 6342, 4887, 2526);
  g->Dequantize(2526, 2527, 0.2192506492137909, 0);
  g->Unary(ynn_unary_square, 2527, 2528);
  g->Reduce(ynn_reduce_sum, 2528, 6066, {2}, true);
  g->ShapeProduct(2528, 6065, {2});
  g->Binary(ynn_binary_divide, 6066, 6065, 2529);
  g->Binary(ynn_binary_add, 2529, 6376, 2530);
  g->Binary(ynn_binary_pow, 2530, 6378, 2532);
  g->Binary(ynn_binary_multiply, 2527, 2532, 2533);
  g->Convert(6789, 2534);
  g->Binary(ynn_binary_multiply, 2533, 2534, 2535);
  g->Binary(ynn_binary_add, 2508, 2535, 2536);
}

// Scope: "Layer30 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer30PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1047, 2537, {0,0,30,0}, {-1,-1,1,-1});
  g->Reshape(2537, 2538, {1,1,256});
  g->Binary(ynn_binary_add, 2538, 6980, 2539);
  g->Binary(ynn_binary_multiply, 2539, 6374, 2540);
  g->Quantize(2536, 2541, 0.13473963737487793, 0);
  g->Transpose(6786, 4896, {1,0});
  g->Binary(ynn_binary_multiply, 4893, 4895, 4891);
  g->Dot(2541, 4896, YNN_INVALID_VALUE_ID, 4890, 1);
  g->DequantizeTensor(4890, YNN_INVALID_VALUE_ID, 4891, 4892);
  g->QuantizeTensor(4892, 6342, 4894, 2543);
  g->Dequantize(2543, 2544, 0.09596457332372665, 0);
  g->Polynomial(2544, 6069, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6069, 6070);
  g->Binary(ynn_binary_add, 6070, 5404, 6067);
  g->Binary(ynn_binary_multiply, 2544, 5402, 6068);
  g->Binary(ynn_binary_multiply, 6068, 6067, 2545);
  g->Binary(ynn_binary_multiply, 2545, 2540, 2546);
  g->Quantize(2546, 2547, 0.18700788915157318, 0);
  g->Transpose(6787, 4903, {1,0});
  g->Binary(ynn_binary_multiply, 4900, 4902, 4898);
  g->Dot(2547, 4903, YNN_INVALID_VALUE_ID, 4897, 1);
  g->DequantizeTensor(4897, YNN_INVALID_VALUE_ID, 4898, 4899);
  g->QuantizeTensor(4899, 6342, 4901, 2548);
  g->Dequantize(2548, 2549, 0.27509135007858276, 0);
  g->Unary(ynn_unary_square, 2549, 2550);
  g->Reduce(ynn_reduce_sum, 2550, 6072, {2}, true);
  g->ShapeProduct(2550, 6071, {2});
  g->Binary(ynn_binary_divide, 6072, 6071, 2551);
  g->Binary(ynn_binary_add, 2551, 6376, 2552);
  g->Binary(ynn_binary_pow, 2552, 6378, 2554);
  g->Binary(ynn_binary_multiply, 2549, 2554, 2555);
  g->Convert(6790, 2556);
  g->Binary(ynn_binary_multiply, 2555, 2556, 2557);
  g->Binary(ynn_binary_add, 2536, 2557, 2558);
  g->Convert(6782, 2559);
  g->Binary(ynn_binary_multiply, 2558, 2559, 2560);
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
  g->Quantize(2569, 2570, 0.6227923035621643, 0);
  g->Transpose(6808, 4910, {1,0});
  g->Binary(ynn_binary_multiply, 4907, 4909, 4905);
  g->Dot(2570, 4910, YNN_INVALID_VALUE_ID, 4904, 1);
  g->DequantizeTensor(4904, YNN_INVALID_VALUE_ID, 4905, 4906);
  g->QuantizeTensor(4906, 6342, 4908, 2571);
  g->Dequantize(2571, 2572, 0.6574802994728088, 0);
  g->SplitDim(2572, 2573, 2, {8,256});
  g->Transpose(2573, 2574, {0,2,1,3});
  g->Unary(ynn_unary_square, 2574, 2575);
  g->Reduce(ynn_reduce_sum, 2575, 6078, {3}, true);
  g->ShapeProduct(2575, 6077, {3});
  g->Binary(ynn_binary_divide, 6078, 6077, 2576);
  g->Binary(ynn_binary_add, 2576, 6376, 2577);
  g->Binary(ynn_binary_pow, 2577, 6378, 2578);
  g->Binary(ynn_binary_multiply, 2574, 2578, 2579);
  g->Convert(6807, 2580);
  g->Binary(ynn_binary_multiply, 2579, 2580, 2581);
  g->Slice(2581, 2582, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2581, 2583, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2583, 2584);
  g->Concat({2584,2582}, 2585, 3);
  g->Binary(ynn_binary_multiply, 2581, 2133, 2587);
  g->Binary(ynn_binary_multiply, 2585, 2992, 2588);
  g->Binary(ynn_binary_add, 2587, 2588, 2589);
}

// Scope: "Layer31 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer31AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(2589, 762, 2590, false, true);
  g->Mask(2590, 6408, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6408, 6087, {-1}, true);
  g->Binary(ynn_binary_subtract, 6408, 6087, 6084);
  g->Unary(ynn_unary_exp, 6084, 6085);
  g->Reduce(ynn_reduce_sum, 6085, 6088, {-1}, true);
  g->Binary(ynn_binary_divide, 5404, 6088, 6086);
  g->Binary(ynn_binary_multiply, 6085, 6086, 2591);
  g->Matmul(2591, 764, 2592, false, false);
}

// Scope: "Layer31 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer31AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(2592, 2593, {0,2,1,3});
  g->FuseDims(2593, 2594, 2, 2);
  g->Quantize(2594, 2595, 0.02399115078151226, 0);
  g->Transpose(6806, 4916, {1,0});
  g->Binary(ynn_binary_multiply, 4868, 4915, 4912);
  g->Dot(2595, 4916, YNN_INVALID_VALUE_ID, 4911, 1);
  g->DequantizeTensor(4911, YNN_INVALID_VALUE_ID, 4912, 4913);
  g->QuantizeTensor(4913, 6342, 4914, 2597);
  g->Dequantize(2597, 2598, 0.06142711639404297, 0);
}

// Scope: "Layer31 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer31Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2560, 2561);
  g->Reduce(ynn_reduce_sum, 2561, 6074, {2}, true);
  g->ShapeProduct(2561, 6073, {2});
  g->Binary(ynn_binary_divide, 6074, 6073, 2562);
  g->Binary(ynn_binary_add, 2562, 6376, 2563);
  g->Binary(ynn_binary_pow, 2563, 6378, 2566);
  g->Binary(ynn_binary_multiply, 2560, 2566, 2567);
  g->Convert(6795, 2568);
  g->Binary(ynn_binary_multiply, 2567, 2568, 2569);
  BuildLayer31AttentionQueryProjection(ctx);
  BuildLayer31AttentionSdpa(ctx);
  BuildLayer31AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2598, 2599);
  g->Reduce(ynn_reduce_sum, 2599, 6090, {2}, true);
  g->ShapeProduct(2599, 6089, {2});
  g->Binary(ynn_binary_divide, 6090, 6089, 2600);
  g->Binary(ynn_binary_add, 2600, 6376, 2601);
  g->Binary(ynn_binary_pow, 2601, 6378, 2602);
  g->Binary(ynn_binary_multiply, 2598, 2602, 2603);
  g->Convert(6802, 2604);
  g->Binary(ynn_binary_multiply, 2603, 2604, 2605);
  g->Binary(ynn_binary_add, 2560, 2605, 2606);
}

// Scope: "Layer31 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer31Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2606, 2608);
  g->Reduce(ynn_reduce_sum, 2608, 6092, {2}, true);
  g->ShapeProduct(2608, 6091, {2});
  g->Binary(ynn_binary_divide, 6092, 6091, 2609);
  g->Binary(ynn_binary_add, 2609, 6376, 2610);
  g->Binary(ynn_binary_pow, 2610, 6378, 2611);
  g->Binary(ynn_binary_multiply, 2606, 2611, 2612);
  g->Convert(6805, 2613);
  g->Binary(ynn_binary_multiply, 2612, 2613, 2614);
  g->Quantize(2614, 2615, 0.01708538644015789, 0);
  g->Transpose(6799, 4923, {1,0});
  g->Binary(ynn_binary_multiply, 4920, 4922, 4918);
  g->Dot(2615, 4923, YNN_INVALID_VALUE_ID, 4917, 1);
  g->DequantizeTensor(4917, YNN_INVALID_VALUE_ID, 4918, 4919);
  g->QuantizeTensor(4919, 6342, 4921, 2616);
  g->Dequantize(2616, 2617, 0.01771654561161995, 0);
  g->Transpose(6798, 4928, {1,0});
  g->Binary(ynn_binary_multiply, 4920, 4927, 4925);
  g->Dot(2615, 4928, YNN_INVALID_VALUE_ID, 4924, 1);
  g->DequantizeTensor(4924, YNN_INVALID_VALUE_ID, 4925, 4926);
  g->QuantizeTensor(4926, 6342, 4921, 2619);
  g->Dequantize(2619, 2620, 0.01771654561161995, 0);
  g->Polynomial(2620, 6095, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6095, 6096);
  g->Binary(ynn_binary_add, 6096, 5404, 6093);
  g->Binary(ynn_binary_multiply, 2620, 5402, 6094);
  g->Binary(ynn_binary_multiply, 6094, 6093, 2621);
  g->Binary(ynn_binary_multiply, 2617, 2621, 2622);
  g->Quantize(2622, 2623, 0.027189970016479492, 0);
  g->Transpose(6797, 4935, {1,0});
  g->Binary(ynn_binary_multiply, 4932, 4934, 4930);
  g->Dot(2623, 4935, YNN_INVALID_VALUE_ID, 4929, 1);
  g->DequantizeTensor(4929, YNN_INVALID_VALUE_ID, 4930, 4931);
  g->QuantizeTensor(4931, 6342, 4933, 2624);
  g->Dequantize(2624, 2625, 0.11200025677680969, 0);
  g->Unary(ynn_unary_square, 2625, 2626);
  g->Reduce(ynn_reduce_sum, 2626, 6098, {2}, true);
  g->ShapeProduct(2626, 6097, {2});
  g->Binary(ynn_binary_divide, 6098, 6097, 2627);
  g->Binary(ynn_binary_add, 2627, 6376, 2629);
  g->Binary(ynn_binary_pow, 2629, 6378, 2630);
  g->Binary(ynn_binary_multiply, 2625, 2630, 2631);
  g->Convert(6803, 2632);
  g->Binary(ynn_binary_multiply, 2631, 2632, 2633);
  g->Binary(ynn_binary_add, 2606, 2633, 2634);
}

// Scope: "Layer31 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer31PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1047, 2635, {0,0,31,0}, {-1,-1,1,-1});
  g->Reshape(2635, 2636, {1,1,256});
  g->Binary(ynn_binary_add, 2636, 6981, 2637);
  g->Binary(ynn_binary_multiply, 2637, 6374, 2638);
  g->Quantize(2634, 2640, 0.1916448324918747, 0);
  g->Transpose(6800, 4948, {1,0});
  g->Binary(ynn_binary_multiply, 4946, 4947, 4944);
  g->Dot(2640, 4948, YNN_INVALID_VALUE_ID, 4943, 1);
  g->DequantizeTensor(4943, YNN_INVALID_VALUE_ID, 4944, 4945);
  g->QuantizeTensor(4945, 6342, 4751, 2641);
  g->Dequantize(2641, 2642, 0.07578741014003754, 0);
  g->Polynomial(2642, 6101, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6101, 6102);
  g->Binary(ynn_binary_add, 6102, 5404, 6099);
  g->Binary(ynn_binary_multiply, 2642, 5402, 6100);
  g->Binary(ynn_binary_multiply, 6100, 6099, 2643);
  g->Binary(ynn_binary_multiply, 2643, 2638, 2644);
  g->Quantize(2644, 2645, 0.24507875740528107, 0);
  g->Transpose(6801, 4955, {1,0});
  g->Binary(ynn_binary_multiply, 4952, 4954, 4950);
  g->Dot(2645, 4955, YNN_INVALID_VALUE_ID, 4949, 1);
  g->DequantizeTensor(4949, YNN_INVALID_VALUE_ID, 4950, 4951);
  g->QuantizeTensor(4951, 6342, 4953, 2646);
  g->Dequantize(2646, 2647, 0.3233283758163452, 0);
  g->Unary(ynn_unary_square, 2647, 2648);
  g->Reduce(ynn_reduce_sum, 2648, 6104, {2}, true);
  g->ShapeProduct(2648, 6103, {2});
  g->Binary(ynn_binary_divide, 6104, 6103, 2649);
  g->Binary(ynn_binary_add, 2649, 6376, 2651);
  g->Binary(ynn_binary_pow, 2651, 6378, 2652);
  g->Binary(ynn_binary_multiply, 2647, 2652, 2653);
  g->Convert(6804, 2654);
  g->Binary(ynn_binary_multiply, 2653, 2654, 2655);
  g->Binary(ynn_binary_add, 2634, 2655, 2656);
  g->Convert(6796, 2657);
  g->Binary(ynn_binary_multiply, 2656, 2657, 2658);
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
  g->Quantize(2666, 2667, 0.6824333071708679, 0);
  g->Transpose(6822, 4962, {1,0});
  g->Binary(ynn_binary_multiply, 4959, 4961, 4957);
  g->Dot(2667, 4962, YNN_INVALID_VALUE_ID, 4956, 1);
  g->DequantizeTensor(4956, YNN_INVALID_VALUE_ID, 4957, 4958);
  g->QuantizeTensor(4958, 6342, 4960, 2668);
  g->Dequantize(2668, 2669, 0.4645669162273407, 0);
  g->SplitDim(2669, 2670, 2, {8,256});
  g->Transpose(2670, 2671, {0,2,1,3});
  g->Unary(ynn_unary_square, 2671, 2674);
  g->Reduce(ynn_reduce_sum, 2674, 6110, {3}, true);
  g->ShapeProduct(2674, 6109, {3});
  g->Binary(ynn_binary_divide, 6110, 6109, 2675);
  g->Binary(ynn_binary_add, 2675, 6376, 2676);
  g->Binary(ynn_binary_pow, 2676, 6378, 2677);
  g->Binary(ynn_binary_multiply, 2671, 2677, 2678);
  g->Convert(6821, 2679);
  g->Binary(ynn_binary_multiply, 2678, 2679, 2680);
  g->Slice(2680, 2681, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2680, 2682, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2682, 2683);
  g->Concat({2683,2681}, 2685, 3);
  g->Binary(ynn_binary_multiply, 2680, 2133, 2686);
  g->Binary(ynn_binary_multiply, 2685, 2992, 2687);
  g->Binary(ynn_binary_add, 2686, 2687, 2688);
}

// Scope: "Layer32 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer32AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(2688, 762, 2689, false, true);
  g->Mask(2689, 6409, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6409, 6114, {-1}, true);
  g->Binary(ynn_binary_subtract, 6409, 6114, 6111);
  g->Unary(ynn_unary_exp, 6111, 6112);
  g->Reduce(ynn_reduce_sum, 6112, 6115, {-1}, true);
  g->Binary(ynn_binary_divide, 5404, 6115, 6113);
  g->Binary(ynn_binary_multiply, 6112, 6113, 2690);
  g->Matmul(2690, 764, 2691, false, false);
}

// Scope: "Layer32 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer32AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(2691, 2692, {0,2,1,3});
  g->FuseDims(2692, 2693, 2, 2);
  g->Quantize(2693, 2695, 0.023006899282336235, 0);
  g->Transpose(6820, 4968, {1,0});
  g->Binary(ynn_binary_multiply, 4257, 4967, 4964);
  g->Dot(2695, 4968, YNN_INVALID_VALUE_ID, 4963, 1);
  g->DequantizeTensor(4963, YNN_INVALID_VALUE_ID, 4964, 4965);
  g->QuantizeTensor(4965, 6342, 4966, 2696);
  g->Dequantize(2696, 2697, 0.056797921657562256, 0);
}

// Scope: "Layer32 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer32Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2658, 2659);
  g->Reduce(ynn_reduce_sum, 2659, 6106, {2}, true);
  g->ShapeProduct(2659, 6105, {2});
  g->Binary(ynn_binary_divide, 6106, 6105, 2660);
  g->Binary(ynn_binary_add, 2660, 6376, 2662);
  g->Binary(ynn_binary_pow, 2662, 6378, 2663);
  g->Binary(ynn_binary_multiply, 2658, 2663, 2664);
  g->Convert(6809, 2665);
  g->Binary(ynn_binary_multiply, 2664, 2665, 2666);
  BuildLayer32AttentionQueryProjection(ctx);
  BuildLayer32AttentionSdpa(ctx);
  BuildLayer32AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2697, 2698);
  g->Reduce(ynn_reduce_sum, 2698, 6117, {2}, true);
  g->ShapeProduct(2698, 6116, {2});
  g->Binary(ynn_binary_divide, 6117, 6116, 2699);
  g->Binary(ynn_binary_add, 2699, 6376, 2700);
  g->Binary(ynn_binary_pow, 2700, 6378, 2701);
  g->Binary(ynn_binary_multiply, 2697, 2701, 2702);
  g->Convert(6816, 2703);
  g->Binary(ynn_binary_multiply, 2702, 2703, 2704);
  g->Binary(ynn_binary_add, 2658, 2704, 2706);
}

// Scope: "Layer32 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer32Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2706, 2707);
  g->Reduce(ynn_reduce_sum, 2707, 6119, {2}, true);
  g->ShapeProduct(2707, 6118, {2});
  g->Binary(ynn_binary_divide, 6119, 6118, 2708);
  g->Binary(ynn_binary_add, 2708, 6376, 2709);
  g->Binary(ynn_binary_pow, 2709, 6378, 2710);
  g->Binary(ynn_binary_multiply, 2706, 2710, 2711);
  g->Convert(6819, 2712);
  g->Binary(ynn_binary_multiply, 2711, 2712, 2713);
  g->Quantize(2713, 2714, 0.014212466776371002, 0);
  g->Transpose(6813, 4975, {1,0});
  g->Binary(ynn_binary_multiply, 4972, 4974, 4970);
  g->Dot(2714, 4975, YNN_INVALID_VALUE_ID, 4969, 1);
  g->DequantizeTensor(4969, YNN_INVALID_VALUE_ID, 4970, 4971);
  g->QuantizeTensor(4971, 6342, 4973, 2715);
  g->Dequantize(2715, 2717, 0.019192922860383987, 0);
  g->Transpose(6812, 4980, {1,0});
  g->Binary(ynn_binary_multiply, 4972, 4979, 4977);
  g->Dot(2714, 4980, YNN_INVALID_VALUE_ID, 4976, 1);
  g->DequantizeTensor(4976, YNN_INVALID_VALUE_ID, 4977, 4978);
  g->QuantizeTensor(4978, 6342, 4973, 2718);
  g->Dequantize(2718, 2719, 0.019192922860383987, 0);
  g->Polynomial(2719, 6122, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6122, 6123);
  g->Binary(ynn_binary_add, 6123, 5404, 6120);
  g->Binary(ynn_binary_multiply, 2719, 5402, 6121);
  g->Binary(ynn_binary_multiply, 6121, 6120, 2720);
  g->Binary(ynn_binary_multiply, 2717, 2720, 2721);
  g->Quantize(2721, 2722, 0.025221465155482292, 0);
  g->Transpose(6811, 4986, {1,0});
  g->Binary(ynn_binary_multiply, 4415, 4985, 4982);
  g->Dot(2722, 4986, YNN_INVALID_VALUE_ID, 4981, 1);
  g->DequantizeTensor(4981, YNN_INVALID_VALUE_ID, 4982, 4983);
  g->QuantizeTensor(4983, 6342, 4984, 2723);
  g->Dequantize(2723, 2724, 0.07002133876085281, 0);
  g->Unary(ynn_unary_square, 2724, 2725);
  g->Reduce(ynn_reduce_sum, 2725, 6125, {2}, true);
  g->ShapeProduct(2725, 6124, {2});
  g->Binary(ynn_binary_divide, 6125, 6124, 2727);
  g->Binary(ynn_binary_add, 2727, 6376, 2728);
  g->Binary(ynn_binary_pow, 2728, 6378, 2729);
  g->Binary(ynn_binary_multiply, 2724, 2729, 2730);
  g->Convert(6817, 2731);
  g->Binary(ynn_binary_multiply, 2730, 2731, 2732);
  g->Binary(ynn_binary_add, 2706, 2732, 2733);
}

// Scope: "Layer32 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer32PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1047, 2734, {0,0,32,0}, {-1,-1,1,-1});
  g->Reshape(2734, 2735, {1,1,256});
  g->Binary(ynn_binary_add, 2735, 6982, 2736);
  g->Binary(ynn_binary_multiply, 2736, 6374, 2738);
  g->Quantize(2733, 2739, 0.19188754260540009, 0);
  g->Transpose(6814, 4992, {1,0});
  g->Binary(ynn_binary_multiply, 4990, 4991, 4988);
  g->Dot(2739, 4992, YNN_INVALID_VALUE_ID, 4987, 1);
  g->DequantizeTensor(4987, YNN_INVALID_VALUE_ID, 4988, 4989);
  g->QuantizeTensor(4989, 6342, 4743, 2740);
  g->Dequantize(2740, 2741, 0.09104331582784653, 0);
  g->Polynomial(2741, 6128, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6128, 6129);
  g->Binary(ynn_binary_add, 6129, 5404, 6126);
  g->Binary(ynn_binary_multiply, 2741, 5402, 6127);
  g->Binary(ynn_binary_multiply, 6127, 6126, 2742);
  g->Binary(ynn_binary_multiply, 2742, 2738, 2743);
  g->Quantize(2743, 2744, 0.18700788915157318, 0);
  g->Transpose(6815, 4998, {1,0});
  g->Binary(ynn_binary_multiply, 4900, 4997, 4994);
  g->Dot(2744, 4998, YNN_INVALID_VALUE_ID, 4993, 1);
  g->DequantizeTensor(4993, YNN_INVALID_VALUE_ID, 4994, 4995);
  g->QuantizeTensor(4995, 6342, 4996, 2745);
  g->Dequantize(2745, 2746, 0.21407830715179443, 0);
  g->Unary(ynn_unary_square, 2746, 2747);
  g->Reduce(ynn_reduce_sum, 2747, 6131, {2}, true);
  g->ShapeProduct(2747, 6130, {2});
  g->Binary(ynn_binary_divide, 6131, 6130, 2749);
  g->Binary(ynn_binary_add, 2749, 6376, 2750);
  g->Binary(ynn_binary_pow, 2750, 6378, 2751);
  g->Binary(ynn_binary_multiply, 2746, 2751, 2752);
  g->Convert(6818, 2753);
  g->Binary(ynn_binary_multiply, 2752, 2753, 2754);
  g->Binary(ynn_binary_add, 2733, 2754, 2755);
  g->Convert(6810, 2756);
  g->Binary(ynn_binary_multiply, 2755, 2756, 2757);
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
  g->Quantize(2765, 2766, 0.9355496764183044, 0);
  g->Transpose(6836, 5005, {1,0});
  g->Binary(ynn_binary_multiply, 5002, 5004, 5000);
  g->Dot(2766, 5005, YNN_INVALID_VALUE_ID, 4999, 1);
  g->DequantizeTensor(4999, YNN_INVALID_VALUE_ID, 5000, 5001);
  g->QuantizeTensor(5001, 6342, 5003, 2767);
  g->Dequantize(2767, 2768, 0.33464565873146057, 0);
  g->SplitDim(2768, 2769, 2, {8,256});
  g->Transpose(2769, 2771, {0,2,1,3});
  g->Unary(ynn_unary_square, 2771, 2772);
  g->Reduce(ynn_reduce_sum, 2772, 6137, {3}, true);
  g->ShapeProduct(2772, 6136, {3});
  g->Binary(ynn_binary_divide, 6137, 6136, 2773);
  g->Binary(ynn_binary_add, 2773, 6376, 2774);
  g->Binary(ynn_binary_pow, 2774, 6378, 2775);
  g->Binary(ynn_binary_multiply, 2771, 2775, 2776);
  g->Convert(6835, 2777);
  g->Binary(ynn_binary_multiply, 2776, 2777, 2778);
  g->Slice(2778, 2779, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2778, 2780, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2780, 2783);
  g->Concat({2783,2779}, 2784, 3);
  g->Binary(ynn_binary_multiply, 2778, 2133, 2785);
  g->Binary(ynn_binary_multiply, 2784, 2992, 2786);
  g->Binary(ynn_binary_add, 2785, 2786, 2787);
}

// Scope: "Layer33 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer33AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(2787, 762, 2788, false, true);
  g->Mask(2788, 6410, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6410, 6141, {-1}, true);
  g->Binary(ynn_binary_subtract, 6410, 6141, 6138);
  g->Unary(ynn_unary_exp, 6138, 6139);
  g->Reduce(ynn_reduce_sum, 6139, 6142, {-1}, true);
  g->Binary(ynn_binary_divide, 5404, 6142, 6140);
  g->Binary(ynn_binary_multiply, 6139, 6140, 2789);
  g->Matmul(2789, 764, 2790, false, false);
}

// Scope: "Layer33 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer33AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(2790, 2791, {0,2,1,3});
  g->FuseDims(2791, 2793, 2, 2);
  g->Quantize(2793, 2794, 0.02276083640754223, 0);
  g->Transpose(6834, 5011, {1,0});
  g->Binary(ynn_binary_multiply, 4369, 5010, 5007);
  g->Dot(2794, 5011, YNN_INVALID_VALUE_ID, 5006, 1);
  g->DequantizeTensor(5006, YNN_INVALID_VALUE_ID, 5007, 5008);
  g->QuantizeTensor(5008, 6342, 5009, 2795);
  g->Dequantize(2795, 2796, 0.02861599810421467, 0);
}

// Scope: "Layer33 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer33Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2757, 2758);
  g->Reduce(ynn_reduce_sum, 2758, 6135, {2}, true);
  g->ShapeProduct(2758, 6134, {2});
  g->Binary(ynn_binary_divide, 6135, 6134, 2760);
  g->Binary(ynn_binary_add, 2760, 6376, 2761);
  g->Binary(ynn_binary_pow, 2761, 6378, 2762);
  g->Binary(ynn_binary_multiply, 2757, 2762, 2763);
  g->Convert(6823, 2764);
  g->Binary(ynn_binary_multiply, 2763, 2764, 2765);
  BuildLayer33AttentionQueryProjection(ctx);
  BuildLayer33AttentionSdpa(ctx);
  BuildLayer33AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2796, 2797);
  g->Reduce(ynn_reduce_sum, 2797, 6144, {2}, true);
  g->ShapeProduct(2797, 6143, {2});
  g->Binary(ynn_binary_divide, 6144, 6143, 2798);
  g->Binary(ynn_binary_add, 2798, 6376, 2799);
  g->Binary(ynn_binary_pow, 2799, 6378, 2800);
  g->Binary(ynn_binary_multiply, 2796, 2800, 2801);
  g->Convert(6830, 2802);
  g->Binary(ynn_binary_multiply, 2801, 2802, 2804);
  g->Binary(ynn_binary_add, 2757, 2804, 2805);
}

// Scope: "Layer33 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer33Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2805, 2806);
  g->Reduce(ynn_reduce_sum, 2806, 6146, {2}, true);
  g->ShapeProduct(2806, 6145, {2});
  g->Binary(ynn_binary_divide, 6146, 6145, 2807);
  g->Binary(ynn_binary_add, 2807, 6376, 2808);
  g->Binary(ynn_binary_pow, 2808, 6378, 2809);
  g->Binary(ynn_binary_multiply, 2805, 2809, 2810);
  g->Convert(6833, 2811);
  g->Binary(ynn_binary_multiply, 2810, 2811, 2812);
  g->Quantize(2812, 2813, 0.016980575397610664, 0);
  g->Transpose(6827, 5018, {1,0});
  g->Binary(ynn_binary_multiply, 5015, 5017, 5013);
  g->Dot(2813, 5018, YNN_INVALID_VALUE_ID, 5012, 1);
  g->DequantizeTensor(5012, YNN_INVALID_VALUE_ID, 5013, 5014);
  g->QuantizeTensor(5014, 6342, 5016, 2815);
  g->Dequantize(2815, 2816, 0.018700797110795975, 0);
  g->Transpose(6826, 5023, {1,0});
  g->Binary(ynn_binary_multiply, 5015, 5022, 5020);
  g->Dot(2813, 5023, YNN_INVALID_VALUE_ID, 5019, 1);
  g->DequantizeTensor(5019, YNN_INVALID_VALUE_ID, 5020, 5021);
  g->QuantizeTensor(5021, 6342, 5016, 2817);
  g->Dequantize(2817, 2818, 0.018700797110795975, 0);
  g->Polynomial(2818, 6149, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6149, 6150);
  g->Binary(ynn_binary_add, 6150, 5404, 6147);
  g->Binary(ynn_binary_multiply, 2818, 5402, 6148);
  g->Binary(ynn_binary_multiply, 6148, 6147, 2819);
  g->Binary(ynn_binary_multiply, 2816, 2819, 2820);
  g->Quantize(2820, 2821, 0.02989666350185871, 0);
  g->Transpose(6825, 5030, {1,0});
  g->Binary(ynn_binary_multiply, 5027, 5029, 5025);
  g->Dot(2821, 5030, YNN_INVALID_VALUE_ID, 5024, 1);
  g->DequantizeTensor(5024, YNN_INVALID_VALUE_ID, 5025, 5026);
  g->QuantizeTensor(5026, 6342, 5028, 2822);
  g->Dequantize(2822, 2823, 0.053163815289735794, 0);
  g->Unary(ynn_unary_square, 2823, 2825);
  g->Reduce(ynn_reduce_sum, 2825, 6152, {2}, true);
  g->ShapeProduct(2825, 6151, {2});
  g->Binary(ynn_binary_divide, 6152, 6151, 2826);
  g->Binary(ynn_binary_add, 2826, 6376, 2827);
  g->Binary(ynn_binary_pow, 2827, 6378, 2828);
  g->Binary(ynn_binary_multiply, 2823, 2828, 2829);
  g->Convert(6831, 2830);
  g->Binary(ynn_binary_multiply, 2829, 2830, 2831);
  g->Binary(ynn_binary_add, 2805, 2831, 2832);
}

// Scope: "Layer33 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer33PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1047, 2833, {0,0,33,0}, {-1,-1,1,-1});
  g->Reshape(2833, 2834, {1,1,256});
  g->Binary(ynn_binary_add, 2834, 6983, 2836);
  g->Binary(ynn_binary_multiply, 2836, 6374, 2837);
  g->Quantize(2832, 2838, 0.13243837654590607, 0);
  g->Transpose(6828, 5044, {1,0});
  g->Binary(ynn_binary_multiply, 5041, 5043, 5039);
  g->Dot(2838, 5044, YNN_INVALID_VALUE_ID, 5038, 1);
  g->DequantizeTensor(5038, YNN_INVALID_VALUE_ID, 5039, 5040);
  g->QuantizeTensor(5040, 6342, 5042, 2839);
  g->Dequantize(2839, 2840, 0.1446850597858429, 0);
  g->Polynomial(2840, 6155, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6155, 6156);
  g->Binary(ynn_binary_add, 6156, 5404, 6153);
  g->Binary(ynn_binary_multiply, 2840, 5402, 6154);
  g->Binary(ynn_binary_multiply, 6154, 6153, 2841);
  g->Binary(ynn_binary_multiply, 2841, 2837, 2842);
  g->Quantize(2842, 2843, 1.5826771259307861, 0);
  g->Transpose(6829, 5051, {1,0});
  g->Binary(ynn_binary_multiply, 5048, 5050, 5046);
  g->Dot(2843, 5051, YNN_INVALID_VALUE_ID, 5045, 1);
  g->DequantizeTensor(5045, YNN_INVALID_VALUE_ID, 5046, 5047);
  g->QuantizeTensor(5047, 6342, 5049, 2844);
  g->Dequantize(2844, 2845, 0.6353945732116699, 0);
  g->Unary(ynn_unary_square, 2845, 2847);
  g->Reduce(ynn_reduce_sum, 2847, 6158, {2}, true);
  g->ShapeProduct(2847, 6157, {2});
  g->Binary(ynn_binary_divide, 6158, 6157, 2848);
  g->Binary(ynn_binary_add, 2848, 6376, 2849);
  g->Binary(ynn_binary_pow, 2849, 6378, 2850);
  g->Binary(ynn_binary_multiply, 2845, 2850, 2851);
  g->Convert(6832, 2852);
  g->Binary(ynn_binary_multiply, 2851, 2852, 2853);
  g->Binary(ynn_binary_add, 2832, 2853, 2854);
  g->Convert(6824, 2855);
  g->Binary(ynn_binary_multiply, 2854, 2855, 2856);
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
  g->Quantize(2863, 2864, 1.450958251953125, 0);
  g->Transpose(6850, 5058, {1,0});
  g->Binary(ynn_binary_multiply, 5055, 5057, 5053);
  g->Dot(2864, 5058, YNN_INVALID_VALUE_ID, 5052, 1);
  g->DequantizeTensor(5052, YNN_INVALID_VALUE_ID, 5053, 5054);
  g->QuantizeTensor(5054, 6342, 5056, 2865);
  g->Dequantize(2865, 2866, 0.6535432934761047, 0);
  g->SplitDim(2866, 2868, 2, {8,512});
  g->Transpose(2868, 2869, {0,2,1,3});
  g->Unary(ynn_unary_square, 2869, 2870);
  g->Reduce(ynn_reduce_sum, 2870, 6162, {3}, true);
  g->ShapeProduct(2870, 6161, {3});
  g->Binary(ynn_binary_divide, 6162, 6161, 2871);
  g->Binary(ynn_binary_add, 2871, 6376, 2872);
  g->Binary(ynn_binary_pow, 2872, 6378, 2873);
  g->Binary(ynn_binary_multiply, 2869, 2873, 2874);
  g->Convert(6849, 2875);
  g->Binary(ynn_binary_multiply, 2874, 2875, 2876);
  g->Slice(2876, 2877, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(2876, 2879, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 2879, 2880);
  g->Concat({2880,2877}, 2881, 3);
  g->Binary(ynn_binary_multiply, 2876, 3406, 2882);
  g->Binary(ynn_binary_multiply, 2881, 3508, 2883);
  g->Binary(ynn_binary_add, 2882, 2883, 2884);
}

// Scope: "Layer34 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer34AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(2884, 895, 2885, false, true);
  g->Mask(2885, 6411, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 6411, 6166, {-1}, true);
  g->Binary(ynn_binary_subtract, 6411, 6166, 6163);
  g->Unary(ynn_unary_exp, 6163, 6164);
  g->Reduce(ynn_reduce_sum, 6164, 6167, {-1}, true);
  g->Binary(ynn_binary_divide, 5404, 6167, 6165);
  g->Binary(ynn_binary_multiply, 6164, 6165, 2886);
  g->Matmul(2886, 897, 2887, false, false);
}

// Scope: "Layer34 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer34AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(2887, 2890, {0,2,1,3});
  g->FuseDims(2890, 2891, 2, 2);
  g->Quantize(2891, 2892, 0.012118612416088581, 0);
  g->Transpose(6848, 5070, {1,0});
  g->Binary(ynn_binary_multiply, 5067, 5069, 5065);
  g->Dot(2892, 5070, YNN_INVALID_VALUE_ID, 5064, 1);
  g->DequantizeTensor(5064, YNN_INVALID_VALUE_ID, 5065, 5066);
  g->QuantizeTensor(5066, 6342, 5068, 2893);
  g->Dequantize(2893, 2894, 0.017325349152088165, 0);
}

// Scope: "Layer34 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer34Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2856, 2857);
  g->Reduce(ynn_reduce_sum, 2857, 6160, {2}, true);
  g->ShapeProduct(2857, 6159, {2});
  g->Binary(ynn_binary_divide, 6160, 6159, 2858);
  g->Binary(ynn_binary_add, 2858, 6376, 2859);
  g->Binary(ynn_binary_pow, 2859, 6378, 2860);
  g->Binary(ynn_binary_multiply, 2856, 2860, 2861);
  g->Convert(6837, 2862);
  g->Binary(ynn_binary_multiply, 2861, 2862, 2863);
  BuildLayer34AttentionQueryProjection(ctx);
  BuildLayer34AttentionSdpa(ctx);
  BuildLayer34AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2894, 2895);
  g->Reduce(ynn_reduce_sum, 2895, 6173, {2}, true);
  g->ShapeProduct(2895, 6172, {2});
  g->Binary(ynn_binary_divide, 6173, 6172, 2896);
  g->Binary(ynn_binary_add, 2896, 6376, 2897);
  g->Binary(ynn_binary_pow, 2897, 6378, 2898);
  g->Binary(ynn_binary_multiply, 2894, 2898, 2899);
  g->Convert(6844, 2901);
  g->Binary(ynn_binary_multiply, 2899, 2901, 2902);
  g->Binary(ynn_binary_add, 2856, 2902, 2903);
}

// Scope: "Layer34 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer34Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2903, 2904);
  g->Reduce(ynn_reduce_sum, 2904, 6175, {2}, true);
  g->ShapeProduct(2904, 6174, {2});
  g->Binary(ynn_binary_divide, 6175, 6174, 2905);
  g->Binary(ynn_binary_add, 2905, 6376, 2906);
  g->Binary(ynn_binary_pow, 2906, 6378, 2907);
  g->Binary(ynn_binary_multiply, 2903, 2907, 2908);
  g->Convert(6847, 2909);
  g->Binary(ynn_binary_multiply, 2908, 2909, 2910);
  g->Quantize(2910, 2912, 0.022695079445838928, 0);
  g->Transpose(6841, 5077, {1,0});
  g->Binary(ynn_binary_multiply, 5074, 5076, 5072);
  g->Dot(2912, 5077, YNN_INVALID_VALUE_ID, 5071, 1);
  g->DequantizeTensor(5071, YNN_INVALID_VALUE_ID, 5072, 5073);
  g->QuantizeTensor(5073, 6342, 5075, 2913);
  g->Dequantize(2913, 2914, 0.039862215518951416, 0);
  g->Transpose(6840, 5082, {1,0});
  g->Binary(ynn_binary_multiply, 5074, 5081, 5079);
  g->Dot(2912, 5082, YNN_INVALID_VALUE_ID, 5078, 1);
  g->DequantizeTensor(5078, YNN_INVALID_VALUE_ID, 5079, 5080);
  g->QuantizeTensor(5080, 6342, 5075, 2915);
  g->Dequantize(2915, 2916, 0.039862215518951416, 0);
  g->Polynomial(2916, 6178, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6178, 6179);
  g->Binary(ynn_binary_add, 6179, 5404, 6176);
  g->Binary(ynn_binary_multiply, 2916, 5402, 6177);
  g->Binary(ynn_binary_multiply, 6177, 6176, 2917);
  g->Binary(ynn_binary_multiply, 2914, 2917, 2918);
  g->Quantize(2918, 2919, 0.09940945357084274, 0);
  g->Transpose(6839, 5089, {1,0});
  g->Binary(ynn_binary_multiply, 5086, 5088, 5084);
  g->Dot(2919, 5089, YNN_INVALID_VALUE_ID, 5083, 1);
  g->DequantizeTensor(5083, YNN_INVALID_VALUE_ID, 5084, 5085);
  g->QuantizeTensor(5085, 6342, 5087, 2920);
  g->Dequantize(2920, 2922, 0.1543705314397812, 0);
  g->Unary(ynn_unary_square, 2922, 2923);
  g->Reduce(ynn_reduce_sum, 2923, 6181, {2}, true);
  g->ShapeProduct(2923, 6180, {2});
  g->Binary(ynn_binary_divide, 6181, 6180, 2924);
  g->Binary(ynn_binary_add, 2924, 6376, 2925);
  g->Binary(ynn_binary_pow, 2925, 6378, 2926);
  g->Binary(ynn_binary_multiply, 2922, 2926, 2927);
  g->Convert(6845, 2928);
  g->Binary(ynn_binary_multiply, 2927, 2928, 2929);
  g->Binary(ynn_binary_add, 2903, 2929, 2930);
}

// Scope: "Layer34 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer34PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1047, 2931, {0,0,34,0}, {-1,-1,1,-1});
  g->Reshape(2931, 2933, {1,1,256});
  g->Binary(ynn_binary_add, 2933, 6984, 2934);
  g->Binary(ynn_binary_multiply, 2934, 6374, 2935);
  g->Quantize(2930, 2936, 0.8795163035392761, 0);
  g->Transpose(6842, 5103, {1,0});
  g->Binary(ynn_binary_multiply, 5100, 5102, 5098);
  g->Dot(2936, 5103, YNN_INVALID_VALUE_ID, 5097, 1);
  g->DequantizeTensor(5097, YNN_INVALID_VALUE_ID, 5098, 5099);
  g->QuantizeTensor(5099, 6342, 5101, 2937);
  g->Dequantize(2937, 2938, 0.16633859276771545, 0);
  g->Polynomial(2938, 6184, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6184, 6185);
  g->Binary(ynn_binary_add, 6185, 5404, 6182);
  g->Binary(ynn_binary_multiply, 2938, 5402, 6183);
  g->Binary(ynn_binary_multiply, 6183, 6182, 2939);
  g->Binary(ynn_binary_multiply, 2939, 2935, 2940);
  g->Quantize(2940, 2941, 3.2125983238220215, 0);
  g->Transpose(6843, 5110, {1,0});
  g->Binary(ynn_binary_multiply, 5107, 5109, 5105);
  g->Dot(2941, 5110, YNN_INVALID_VALUE_ID, 5104, 1);
  g->DequantizeTensor(5104, YNN_INVALID_VALUE_ID, 5105, 5106);
  g->QuantizeTensor(5106, 6342, 5108, 2942);
  g->Dequantize(2942, 2944, 1.0930962562561035, 0);
  g->Unary(ynn_unary_square, 2944, 2945);
  g->Reduce(ynn_reduce_sum, 2945, 6187, {2}, true);
  g->ShapeProduct(2945, 6186, {2});
  g->Binary(ynn_binary_divide, 6187, 6186, 2946);
  g->Binary(ynn_binary_add, 2946, 6376, 2947);
  g->Binary(ynn_binary_pow, 2947, 6378, 2948);
  g->Binary(ynn_binary_multiply, 2944, 2948, 2949);
  g->Convert(6846, 2950);
  g->Binary(ynn_binary_multiply, 2949, 2950, 2951);
  g->Binary(ynn_binary_add, 2930, 2951, 2952);
  g->Convert(6838, 2953);
  g->Binary(ynn_binary_multiply, 2952, 2953, 2955);
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
  g->Unary(ynn_unary_square, 2955, 2956);
  g->Reduce(ynn_reduce_sum, 2956, 6191, {2}, true);
  g->ShapeProduct(2956, 6190, {2});
  g->Binary(ynn_binary_divide, 6191, 6190, 2957);
  g->Binary(ynn_binary_add, 2957, 6376, 2958);
  g->Binary(ynn_binary_pow, 2958, 6378, 2959);
  g->Binary(ynn_binary_multiply, 2955, 2959, 2960);
  g->Convert(6953, 2961);
  g->Binary(ynn_binary_multiply, 2960, 2961, 2962);
  g->Reduce(ynn_reduce_min_max, 2962, 5118, {-1}, true);
  g->DynamicQuantization(5118, 5117, 5116);
  g->QuantizeTensor(2962, 5117, 5116, 5115);
  g->Transpose(6381, 5121, {1,0});
  g->Binary(ynn_binary_multiply, 5116, 5119, 5112);
  g->Reduce(ynn_reduce_sum, 5121, 5120, {0}, true);
  g->Binary(ynn_binary_multiply, 5117, 5120, 5114);
  g->Unary(ynn_unary_negate, 5114, 5113);
  g->Dot(5115, 5121, 5113, 5111, 1);
  g->DequantizeTensor(5111, YNN_INVALID_VALUE_ID, 5112, 2963);
  g->Binary(ynn_binary_divide, 2963, 6375, 2964);
  g->Unary(ynn_unary_tanh, 2964, 2966);
  g->Binary(ynn_binary_multiply, 2966, 6375, 2967);
  g->Convert(2967, 6382);
  g->ResultShape(6382, {slinky::expr(int64_t{1}),slinky::expr(int64_t{1}),slinky::expr(int64_t{262144})});
}

}  // namespace BuildGemma4DecodeSource
