// Generated YNNPACK builder; do not edit.
#include "gemma4_decode_builder.h"

namespace BuildGemma4DecodeSource {

// Scope: "Layer27 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer27AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(2217, 2219, 0.3104223608970642, 0);
  g->Transpose(6805, 4790, {1,0});
  g->Binary(ynn_binary_multiply, 4787, 4789, 4785);
  g->Dot(2219, 4790, YNN_INVALID_VALUE_ID, 4784, 1);
  g->DequantizeTensor(4784, YNN_INVALID_VALUE_ID, 4785, 4786);
  g->QuantizeTensor(4786, 6412, 4788, 2220);
  g->Dequantize(2220, 2221, 0.437007874250412, 0);
  g->SplitDim(2221, 2222, 2, {8,256});
  g->FuseDims(2222, 2224, 1, 2);
  g->SplitDim(2224, 2223, 1, {8,1});
  g->Unary(ynn_unary_square, 2223, 2225);
  g->Reduce(ynn_reduce_sum, 2225, 6042, {3}, true);
  g->ShapeProduct(2225, 6041, {3});
  g->Binary(ynn_binary_divide, 6042, 6041, 2226);
  g->Binary(ynn_binary_add, 2226, 6446, 2227);
  g->Binary(ynn_binary_pow, 2227, 6448, 2228);
  g->Binary(ynn_binary_multiply, 2223, 2228, 2229);
  g->Convert(6804, 2231);
  g->Binary(ynn_binary_multiply, 2229, 2231, 2232);
  g->Slice(2232, 2233, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2232, 2234, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2234, 2235);
  g->Concat({2235,2233}, 2236, 3);
  g->Binary(ynn_binary_multiply, 2232, 2173, 2237);
  g->Binary(ynn_binary_multiply, 2236, 3050, 2238);
  g->Binary(ynn_binary_add, 2237, 2238, 2239);
}

// Scope: "Layer27 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer27AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(2239, 772, 2240, false, true);
  g->Mask(2240, 6473, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6473, 6046, {-1}, true);
  g->Binary(ynn_binary_subtract, 6473, 6046, 6043);
  g->Unary(ynn_unary_exp, 6043, 6044);
  g->Reduce(ynn_reduce_sum, 6044, 6047, {-1}, true);
  g->Binary(ynn_binary_divide, 5474, 6047, 6045);
  g->Binary(ynn_binary_multiply, 6044, 6045, 2242);
  g->Matmul(2242, 774, 2243, false, false);
}

// Scope: "Layer27 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer27AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(2243, 2245, 1, 2);
  g->SplitDim(2245, 2244, 1, {1,8});
  g->FuseDims(2244, 2246, 2, 2);
  g->Quantize(2246, 2247, 0.024237213656306267, 0);
  g->Transpose(6803, 4797, {1,0});
  g->Binary(ynn_binary_multiply, 4794, 4796, 4792);
  g->Dot(2247, 4797, YNN_INVALID_VALUE_ID, 4791, 1);
  g->DequantizeTensor(4791, YNN_INVALID_VALUE_ID, 4792, 4793);
  g->QuantizeTensor(4793, 6412, 4795, 2248);
  g->Dequantize(2248, 2249, 0.05315101891756058, 0);
}

// Scope: "Layer27 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer27Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2210, 2211);
  g->Reduce(ynn_reduce_sum, 2211, 6040, {2}, true);
  g->ShapeProduct(2211, 6039, {2});
  g->Binary(ynn_binary_divide, 6040, 6039, 2212);
  g->Binary(ynn_binary_add, 2212, 6446, 2213);
  g->Binary(ynn_binary_pow, 2213, 6448, 2214);
  g->Binary(ynn_binary_multiply, 2210, 2214, 2215);
  g->Convert(6792, 2216);
  g->Binary(ynn_binary_multiply, 2215, 2216, 2217);
  BuildLayer27AttentionQueryProjection(ctx);
  BuildLayer27AttentionSdpa(ctx);
  BuildLayer27AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2249, 2250);
  g->Reduce(ynn_reduce_sum, 2250, 6049, {2}, true);
  g->ShapeProduct(2250, 6048, {2});
  g->Binary(ynn_binary_divide, 6049, 6048, 2251);
  g->Binary(ynn_binary_add, 2251, 6446, 2253);
  g->Binary(ynn_binary_pow, 2253, 6448, 2254);
  g->Binary(ynn_binary_multiply, 2249, 2254, 2255);
  g->Convert(6799, 2256);
  g->Binary(ynn_binary_multiply, 2255, 2256, 2257);
  g->Binary(ynn_binary_add, 2210, 2257, 2258);
}

// Scope: "Layer27 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer27Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2258, 2259);
  g->Reduce(ynn_reduce_sum, 2259, 6051, {2}, true);
  g->ShapeProduct(2259, 6050, {2});
  g->Binary(ynn_binary_divide, 6051, 6050, 2260);
  g->Binary(ynn_binary_add, 2260, 6446, 2261);
  g->Binary(ynn_binary_pow, 2261, 6448, 2262);
  g->Binary(ynn_binary_multiply, 2258, 2262, 2264);
  g->Convert(6802, 2265);
  g->Binary(ynn_binary_multiply, 2264, 2265, 2266);
  g->Quantize(2266, 2267, 0.02701687067747116, 0);
  g->Transpose(6796, 4804, {1,0});
  g->Binary(ynn_binary_multiply, 4801, 4803, 4799);
  g->Dot(2267, 4804, YNN_INVALID_VALUE_ID, 4798, 1);
  g->DequantizeTensor(4798, YNN_INVALID_VALUE_ID, 4799, 4800);
  g->QuantizeTensor(4800, 6412, 4802, 2268);
  g->Dequantize(2268, 2269, 0.044537413865327835, 0);
  g->Transpose(6795, 4809, {1,0});
  g->Binary(ynn_binary_multiply, 4801, 4808, 4806);
  g->Dot(2267, 4809, YNN_INVALID_VALUE_ID, 4805, 1);
  g->DequantizeTensor(4805, YNN_INVALID_VALUE_ID, 4806, 4807);
  g->QuantizeTensor(4807, 6412, 4802, 2270);
  g->Dequantize(2270, 2271, 0.044537413865327835, 0);
  g->Polynomial(2271, 6054, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6054, 6055);
  g->Binary(ynn_binary_add, 6055, 5474, 6052);
  g->Binary(ynn_binary_multiply, 2271, 5472, 6053);
  g->Binary(ynn_binary_multiply, 6053, 6052, 2272);
  g->Binary(ynn_binary_multiply, 2269, 2272, 2274);
  g->Quantize(2274, 2275, 0.09104331582784653, 0);
  g->Transpose(6794, 4816, {1,0});
  g->Binary(ynn_binary_multiply, 4813, 4815, 4811);
  g->Dot(2275, 4816, YNN_INVALID_VALUE_ID, 4810, 1);
  g->DequantizeTensor(4810, YNN_INVALID_VALUE_ID, 4811, 4812);
  g->QuantizeTensor(4812, 6412, 4814, 2276);
  g->Dequantize(2276, 2277, 0.08018074929714203, 0);
  g->Unary(ynn_unary_square, 2277, 2278);
  g->Reduce(ynn_reduce_sum, 2278, 6059, {2}, true);
  g->ShapeProduct(2278, 6058, {2});
  g->Binary(ynn_binary_divide, 6059, 6058, 2279);
  g->Binary(ynn_binary_add, 2279, 6446, 2280);
  g->Binary(ynn_binary_pow, 2280, 6448, 2281);
  g->Binary(ynn_binary_multiply, 2277, 2281, 2282);
  g->Convert(6800, 2283);
  g->Binary(ynn_binary_multiply, 2282, 2283, 2286);
  g->Binary(ynn_binary_add, 2258, 2286, 2287);
}

// Scope: "Layer27 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer27PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1064, 2288, {0,0,27,0}, {-1,-1,1,-1});
  g->Reshape(2288, 2289, {1,1,256});
  g->Binary(ynn_binary_add, 2289, 7046, 2290);
  g->Binary(ynn_binary_multiply, 2290, 6444, 2291);
  g->Quantize(2287, 2292, 0.12690971791744232, 0);
  g->Transpose(6797, 4823, {1,0});
  g->Binary(ynn_binary_multiply, 4820, 4822, 4818);
  g->Dot(2292, 4823, YNN_INVALID_VALUE_ID, 4817, 1);
  g->DequantizeTensor(4817, YNN_INVALID_VALUE_ID, 4818, 4819);
  g->QuantizeTensor(4819, 6412, 4821, 2293);
  g->Dequantize(2293, 2294, 0.07578741014003754, 0);
  g->Polynomial(2294, 6062, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6062, 6063);
  g->Binary(ynn_binary_add, 6063, 5474, 6060);
  g->Binary(ynn_binary_multiply, 2294, 5472, 6061);
  g->Binary(ynn_binary_multiply, 6061, 6060, 2295);
  g->Binary(ynn_binary_multiply, 2295, 2291, 2297);
  g->Quantize(2297, 2298, 0.5708661675453186, 0);
  g->Transpose(6798, 4830, {1,0});
  g->Binary(ynn_binary_multiply, 4827, 4829, 4825);
  g->Dot(2298, 4830, YNN_INVALID_VALUE_ID, 4824, 1);
  g->DequantizeTensor(4824, YNN_INVALID_VALUE_ID, 4825, 4826);
  g->QuantizeTensor(4826, 6412, 4828, 2299);
  g->Dequantize(2299, 2300, 0.26081717014312744, 0);
  g->Unary(ynn_unary_square, 2300, 2301);
  g->Reduce(ynn_reduce_sum, 2301, 6065, {2}, true);
  g->ShapeProduct(2301, 6064, {2});
  g->Binary(ynn_binary_divide, 6065, 6064, 2302);
  g->Binary(ynn_binary_add, 2302, 6446, 2303);
  g->Binary(ynn_binary_pow, 2303, 6448, 2304);
  g->Binary(ynn_binary_multiply, 2300, 2304, 2305);
  g->Convert(6801, 2306);
  g->Binary(ynn_binary_multiply, 2305, 2306, 2308);
  g->Binary(ynn_binary_add, 2287, 2308, 2309);
  g->Convert(6793, 2310);
  g->Binary(ynn_binary_multiply, 2309, 2310, 2311);
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
  g->Quantize(2319, 2320, 0.4655068814754486, 0);
  g->Transpose(6819, 4837, {1,0});
  g->Binary(ynn_binary_multiply, 4834, 4836, 4832);
  g->Dot(2320, 4837, YNN_INVALID_VALUE_ID, 4831, 1);
  g->DequantizeTensor(4831, YNN_INVALID_VALUE_ID, 4832, 4833);
  g->QuantizeTensor(4833, 6412, 4835, 2321);
  g->Dequantize(2321, 2322, 0.34645670652389526, 0);
  g->SplitDim(2322, 2323, 2, {8,256});
  g->FuseDims(2323, 2325, 1, 2);
  g->SplitDim(2325, 2324, 1, {8,1});
  g->Unary(ynn_unary_square, 2324, 2326);
  g->Reduce(ynn_reduce_sum, 2326, 6069, {3}, true);
  g->ShapeProduct(2326, 6068, {3});
  g->Binary(ynn_binary_divide, 6069, 6068, 2327);
  g->Binary(ynn_binary_add, 2327, 6446, 2328);
  g->Binary(ynn_binary_pow, 2328, 6448, 2329);
  g->Binary(ynn_binary_multiply, 2324, 2329, 2330);
  g->Convert(6818, 2331);
  g->Binary(ynn_binary_multiply, 2330, 2331, 2332);
  g->Slice(2332, 2333, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2332, 2334, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2334, 2335);
  g->Concat({2335,2333}, 2336, 3);
  g->Binary(ynn_binary_multiply, 2332, 2173, 2337);
  g->Binary(ynn_binary_multiply, 2336, 3050, 2338);
  g->Binary(ynn_binary_add, 2337, 2338, 2339);
}

// Scope: "Layer28 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer28AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(2339, 772, 2340, false, true);
  g->Mask(2340, 6474, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6474, 6073, {-1}, true);
  g->Binary(ynn_binary_subtract, 6474, 6073, 6070);
  g->Unary(ynn_unary_exp, 6070, 6071);
  g->Reduce(ynn_reduce_sum, 6071, 6074, {-1}, true);
  g->Binary(ynn_binary_divide, 5474, 6074, 6072);
  g->Binary(ynn_binary_multiply, 6071, 6072, 2341);
  g->Matmul(2341, 774, 2342, false, false);
}

// Scope: "Layer28 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer28AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(2342, 2344, 1, 2);
  g->SplitDim(2344, 2343, 1, {1,8});
  g->FuseDims(2343, 2345, 2, 2);
  g->Quantize(2345, 2346, 0.024237213656306267, 0);
  g->Transpose(6817, 4843, {1,0});
  g->Binary(ynn_binary_multiply, 4794, 4842, 4839);
  g->Dot(2346, 4843, YNN_INVALID_VALUE_ID, 4838, 1);
  g->DequantizeTensor(4838, YNN_INVALID_VALUE_ID, 4839, 4840);
  g->QuantizeTensor(4840, 6412, 4841, 2347);
  g->Dequantize(2347, 2348, 0.03035588562488556, 0);
}

// Scope: "Layer28 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer28Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2311, 2312);
  g->Reduce(ynn_reduce_sum, 2312, 6067, {2}, true);
  g->ShapeProduct(2312, 6066, {2});
  g->Binary(ynn_binary_divide, 6067, 6066, 2313);
  g->Binary(ynn_binary_add, 2313, 6446, 2314);
  g->Binary(ynn_binary_pow, 2314, 6448, 2315);
  g->Binary(ynn_binary_multiply, 2311, 2315, 2316);
  g->Convert(6806, 2317);
  g->Binary(ynn_binary_multiply, 2316, 2317, 2319);
  BuildLayer28AttentionQueryProjection(ctx);
  BuildLayer28AttentionSdpa(ctx);
  BuildLayer28AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2348, 2349);
  g->Reduce(ynn_reduce_sum, 2349, 6076, {2}, true);
  g->ShapeProduct(2349, 6075, {2});
  g->Binary(ynn_binary_divide, 6076, 6075, 2351);
  g->Binary(ynn_binary_add, 2351, 6446, 2352);
  g->Binary(ynn_binary_pow, 2352, 6448, 2353);
  g->Binary(ynn_binary_multiply, 2348, 2353, 2354);
  g->Convert(6813, 2355);
  g->Binary(ynn_binary_multiply, 2354, 2355, 2356);
  g->Binary(ynn_binary_add, 2311, 2356, 2357);
}

// Scope: "Layer28 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer28Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2357, 2358);
  g->Reduce(ynn_reduce_sum, 2358, 6078, {2}, true);
  g->ShapeProduct(2358, 6077, {2});
  g->Binary(ynn_binary_divide, 6078, 6077, 2359);
  g->Binary(ynn_binary_add, 2359, 6446, 2360);
  g->Binary(ynn_binary_pow, 2360, 6448, 2362);
  g->Binary(ynn_binary_multiply, 2357, 2362, 2363);
  g->Convert(6816, 2364);
  g->Binary(ynn_binary_multiply, 2363, 2364, 2365);
  g->Quantize(2365, 2366, 0.025474751368165016, 0);
  g->Transpose(6810, 4850, {1,0});
  g->Binary(ynn_binary_multiply, 4847, 4849, 4845);
  g->Dot(2366, 4850, YNN_INVALID_VALUE_ID, 4844, 1);
  g->DequantizeTensor(4844, YNN_INVALID_VALUE_ID, 4845, 4846);
  g->QuantizeTensor(4846, 6412, 4848, 2367);
  g->Dequantize(2367, 2368, 0.03494095429778099, 0);
  g->Transpose(6809, 4855, {1,0});
  g->Binary(ynn_binary_multiply, 4847, 4854, 4852);
  g->Dot(2366, 4855, YNN_INVALID_VALUE_ID, 4851, 1);
  g->DequantizeTensor(4851, YNN_INVALID_VALUE_ID, 4852, 4853);
  g->QuantizeTensor(4853, 6412, 4848, 2369);
  g->Dequantize(2369, 2370, 0.03494095429778099, 0);
  g->Polynomial(2370, 6081, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6081, 6082);
  g->Binary(ynn_binary_add, 6082, 5474, 6079);
  g->Binary(ynn_binary_multiply, 2370, 5472, 6080);
  g->Binary(ynn_binary_multiply, 6080, 6079, 2371);
  g->Binary(ynn_binary_multiply, 2368, 2371, 2372);
  g->Quantize(2372, 2373, 0.07627953588962555, 0);
  g->Transpose(6808, 4862, {1,0});
  g->Binary(ynn_binary_multiply, 4859, 4861, 4857);
  g->Dot(2373, 4862, YNN_INVALID_VALUE_ID, 4856, 1);
  g->DequantizeTensor(4856, YNN_INVALID_VALUE_ID, 4857, 4858);
  g->QuantizeTensor(4858, 6412, 4860, 2374);
  g->Dequantize(2374, 2375, 0.10797519981861115, 0);
  g->Unary(ynn_unary_square, 2375, 2376);
  g->Reduce(ynn_reduce_sum, 2376, 6084, {2}, true);
  g->ShapeProduct(2376, 6083, {2});
  g->Binary(ynn_binary_divide, 6084, 6083, 2377);
  g->Binary(ynn_binary_add, 2377, 6446, 2378);
  g->Binary(ynn_binary_pow, 2378, 6448, 2379);
  g->Binary(ynn_binary_multiply, 2375, 2379, 2380);
  g->Convert(6814, 2381);
  g->Binary(ynn_binary_multiply, 2380, 2381, 2382);
  g->Binary(ynn_binary_add, 2357, 2382, 2383);
}

// Scope: "Layer28 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer28PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1064, 2384, {0,0,28,0}, {-1,-1,1,-1});
  g->Reshape(2384, 2385, {1,1,256});
  g->Binary(ynn_binary_add, 2385, 7047, 2386);
  g->Binary(ynn_binary_multiply, 2386, 6444, 2387);
  g->Quantize(2383, 2388, 0.13722270727157593, 0);
  g->Transpose(6811, 4869, {1,0});
  g->Binary(ynn_binary_multiply, 4866, 4868, 4864);
  g->Dot(2388, 4869, YNN_INVALID_VALUE_ID, 4863, 1);
  g->DequantizeTensor(4863, YNN_INVALID_VALUE_ID, 4864, 4865);
  g->QuantizeTensor(4865, 6412, 4867, 2389);
  g->Dequantize(2389, 2390, 0.08513779938220978, 0);
  g->Polynomial(2390, 6087, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6087, 6088);
  g->Binary(ynn_binary_add, 6088, 5474, 6085);
  g->Binary(ynn_binary_multiply, 2390, 5472, 6086);
  g->Binary(ynn_binary_multiply, 6086, 6085, 2393);
  g->Binary(ynn_binary_multiply, 2393, 2387, 2394);
  g->Quantize(2394, 2395, 0.748031497001648, 0);
  g->Transpose(6812, 4876, {1,0});
  g->Binary(ynn_binary_multiply, 4873, 4875, 4871);
  g->Dot(2395, 4876, YNN_INVALID_VALUE_ID, 4870, 1);
  g->DequantizeTensor(4870, YNN_INVALID_VALUE_ID, 4871, 4872);
  g->QuantizeTensor(4872, 6412, 4874, 2396);
  g->Dequantize(2396, 2397, 0.18373137712478638, 0);
  g->Unary(ynn_unary_square, 2397, 2398);
  g->Reduce(ynn_reduce_sum, 2398, 6090, {2}, true);
  g->ShapeProduct(2398, 6089, {2});
  g->Binary(ynn_binary_divide, 6090, 6089, 2399);
  g->Binary(ynn_binary_add, 2399, 6446, 2400);
  g->Binary(ynn_binary_pow, 2400, 6448, 2401);
  g->Binary(ynn_binary_multiply, 2397, 2401, 2402);
  g->Convert(6815, 2403);
  g->Binary(ynn_binary_multiply, 2402, 2403, 2404);
  g->Binary(ynn_binary_add, 2383, 2404, 2405);
  g->Convert(6807, 2406);
  g->Binary(ynn_binary_multiply, 2405, 2406, 2407);
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
  g->Quantize(2415, 2416, 0.41653531789779663, 0);
  g->Transpose(6833, 4889, {1,0});
  g->Binary(ynn_binary_multiply, 4886, 4888, 4884);
  g->Dot(2416, 4889, YNN_INVALID_VALUE_ID, 4883, 1);
  g->DequantizeTensor(4883, YNN_INVALID_VALUE_ID, 4884, 4885);
  g->QuantizeTensor(4885, 6412, 4887, 2417);
  g->Dequantize(2417, 2418, 0.312992125749588, 0);
  g->SplitDim(2418, 2419, 2, {8,512});
  g->FuseDims(2419, 2421, 1, 2);
  g->SplitDim(2421, 2420, 1, {8,1});
  g->Unary(ynn_unary_square, 2420, 2422);
  g->Reduce(ynn_reduce_sum, 2422, 6094, {3}, true);
  g->ShapeProduct(2422, 6093, {3});
  g->Binary(ynn_binary_divide, 6094, 6093, 2423);
  g->Binary(ynn_binary_add, 2423, 6446, 2424);
  g->Binary(ynn_binary_pow, 2424, 6448, 2426);
  g->Binary(ynn_binary_multiply, 2420, 2426, 2427);
  g->Convert(6832, 2428);
  g->Binary(ynn_binary_multiply, 2427, 2428, 2429);
  g->Slice(2429, 2430, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(2429, 2431, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 2431, 2432);
  g->Concat({2432,2430}, 2433, 3);
  g->Binary(ynn_binary_multiply, 2429, 3471, 2434);
  g->Binary(ynn_binary_multiply, 2433, 3576, 2435);
  g->Binary(ynn_binary_add, 2434, 2435, 2437);
}

// Scope: "Layer29 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer29AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(2437, 907, 2438, false, true);
  g->Mask(2438, 6475, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 6475, 6098, {-1}, true);
  g->Binary(ynn_binary_subtract, 6475, 6098, 6095);
  g->Unary(ynn_unary_exp, 6095, 6096);
  g->Reduce(ynn_reduce_sum, 6096, 6099, {-1}, true);
  g->Binary(ynn_binary_divide, 5474, 6099, 6097);
  g->Binary(ynn_binary_multiply, 6096, 6097, 2439);
  g->Matmul(2439, 909, 2440, false, false);
}

// Scope: "Layer29 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer29AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(2440, 2442, 1, 2);
  g->SplitDim(2442, 2441, 1, {1,8});
  g->FuseDims(2441, 2443, 2, 2);
  g->Quantize(2443, 2444, 0.017962608486413956, 0);
  g->Transpose(6831, 4895, {1,0});
  g->Binary(ynn_binary_multiply, 3813, 4894, 4891);
  g->Dot(2444, 4895, YNN_INVALID_VALUE_ID, 4890, 1);
  g->DequantizeTensor(4890, YNN_INVALID_VALUE_ID, 4891, 4892);
  g->QuantizeTensor(4892, 6412, 4893, 2445);
  g->Dequantize(2445, 2446, 0.03030368685722351, 0);
}

// Scope: "Layer29 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer29Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2407, 2408);
  g->Reduce(ynn_reduce_sum, 2408, 6092, {2}, true);
  g->ShapeProduct(2408, 6091, {2});
  g->Binary(ynn_binary_divide, 6092, 6091, 2409);
  g->Binary(ynn_binary_add, 2409, 6446, 2410);
  g->Binary(ynn_binary_pow, 2410, 6448, 2411);
  g->Binary(ynn_binary_multiply, 2407, 2411, 2412);
  g->Convert(6820, 2414);
  g->Binary(ynn_binary_multiply, 2412, 2414, 2415);
  BuildLayer29AttentionQueryProjection(ctx);
  BuildLayer29AttentionSdpa(ctx);
  BuildLayer29AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2446, 2449);
  g->Reduce(ynn_reduce_sum, 2449, 6101, {2}, true);
  g->ShapeProduct(2449, 6100, {2});
  g->Binary(ynn_binary_divide, 6101, 6100, 2450);
  g->Binary(ynn_binary_add, 2450, 6446, 2451);
  g->Binary(ynn_binary_pow, 2451, 6448, 2452);
  g->Binary(ynn_binary_multiply, 2446, 2452, 2453);
  g->Convert(6827, 2454);
  g->Binary(ynn_binary_multiply, 2453, 2454, 2455);
  g->Binary(ynn_binary_add, 2407, 2455, 2456);
}

// Scope: "Layer29 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer29Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2456, 2457);
  g->Reduce(ynn_reduce_sum, 2457, 6103, {2}, true);
  g->ShapeProduct(2457, 6102, {2});
  g->Binary(ynn_binary_divide, 6103, 6102, 2458);
  g->Binary(ynn_binary_add, 2458, 6446, 2460);
  g->Binary(ynn_binary_pow, 2460, 6448, 2461);
  g->Binary(ynn_binary_multiply, 2456, 2461, 2462);
  g->Convert(6830, 2463);
  g->Binary(ynn_binary_multiply, 2462, 2463, 2464);
  g->Quantize(2464, 2465, 0.032805636525154114, 0);
  g->Transpose(6824, 4902, {1,0});
  g->Binary(ynn_binary_multiply, 4899, 4901, 4897);
  g->Dot(2465, 4902, YNN_INVALID_VALUE_ID, 4896, 1);
  g->DequantizeTensor(4896, YNN_INVALID_VALUE_ID, 4897, 4898);
  g->QuantizeTensor(4898, 6412, 4900, 2466);
  g->Dequantize(2466, 2467, 0.03690946102142334, 0);
  g->Transpose(6823, 4907, {1,0});
  g->Binary(ynn_binary_multiply, 4899, 4906, 4904);
  g->Dot(2465, 4907, YNN_INVALID_VALUE_ID, 4903, 1);
  g->DequantizeTensor(4903, YNN_INVALID_VALUE_ID, 4904, 4905);
  g->QuantizeTensor(4905, 6412, 4900, 2468);
  g->Dequantize(2468, 2470, 0.03690946102142334, 0);
  g->Polynomial(2470, 6108, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6108, 6109);
  g->Binary(ynn_binary_add, 6109, 5474, 6106);
  g->Binary(ynn_binary_multiply, 2470, 5472, 6107);
  g->Binary(ynn_binary_multiply, 6107, 6106, 2471);
  g->Binary(ynn_binary_multiply, 2467, 2471, 2472);
  g->Quantize(2472, 2473, 0.11171260476112366, 0);
  g->Transpose(6822, 4914, {1,0});
  g->Binary(ynn_binary_multiply, 4911, 4913, 4909);
  g->Dot(2473, 4914, YNN_INVALID_VALUE_ID, 4908, 1);
  g->DequantizeTensor(4908, YNN_INVALID_VALUE_ID, 4909, 4910);
  g->QuantizeTensor(4910, 6412, 4912, 2474);
  g->Dequantize(2474, 2475, 0.3346065282821655, 0);
  g->Unary(ynn_unary_square, 2475, 2476);
  g->Reduce(ynn_reduce_sum, 2476, 6111, {2}, true);
  g->ShapeProduct(2476, 6110, {2});
  g->Binary(ynn_binary_divide, 6111, 6110, 2477);
  g->Binary(ynn_binary_add, 2477, 6446, 2478);
  g->Binary(ynn_binary_pow, 2478, 6448, 2479);
  g->Binary(ynn_binary_multiply, 2475, 2479, 2481);
  g->Convert(6828, 2482);
  g->Binary(ynn_binary_multiply, 2481, 2482, 2483);
  g->Binary(ynn_binary_add, 2456, 2483, 2484);
}

// Scope: "Layer29 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer29PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1064, 2485, {0,0,29,0}, {-1,-1,1,-1});
  g->Reshape(2485, 2486, {1,1,256});
  g->Binary(ynn_binary_add, 2486, 7048, 2487);
  g->Binary(ynn_binary_multiply, 2487, 6444, 2488);
  g->Quantize(2484, 2489, 0.1425527185201645, 0);
  g->Transpose(6825, 4920, {1,0});
  g->Binary(ynn_binary_multiply, 4918, 4919, 4916);
  g->Dot(2489, 4920, YNN_INVALID_VALUE_ID, 4915, 1);
  g->DequantizeTensor(4915, YNN_INVALID_VALUE_ID, 4916, 4917);
  g->QuantizeTensor(4917, 6412, 4253, 2490);
  g->Dequantize(2490, 2492, 0.07234252989292145, 0);
  g->Polynomial(2492, 6114, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6114, 6115);
  g->Binary(ynn_binary_add, 6115, 5474, 6112);
  g->Binary(ynn_binary_multiply, 2492, 5472, 6113);
  g->Binary(ynn_binary_multiply, 6113, 6112, 2493);
  g->Binary(ynn_binary_multiply, 2493, 2488, 2494);
  g->Quantize(2494, 2495, 0.2539370059967041, 0);
  g->Transpose(6826, 4927, {1,0});
  g->Binary(ynn_binary_multiply, 4924, 4926, 4922);
  g->Dot(2495, 4927, YNN_INVALID_VALUE_ID, 4921, 1);
  g->DequantizeTensor(4921, YNN_INVALID_VALUE_ID, 4922, 4923);
  g->QuantizeTensor(4923, 6412, 4925, 2496);
  g->Dequantize(2496, 2497, 0.2777099609375, 0);
  g->Unary(ynn_unary_square, 2497, 2498);
  g->Reduce(ynn_reduce_sum, 2498, 6117, {2}, true);
  g->ShapeProduct(2498, 6116, {2});
  g->Binary(ynn_binary_divide, 6117, 6116, 2499);
  g->Binary(ynn_binary_add, 2499, 6446, 2500);
  g->Binary(ynn_binary_pow, 2500, 6448, 2501);
  g->Binary(ynn_binary_multiply, 2497, 2501, 2504);
  g->Convert(6829, 2505);
  g->Binary(ynn_binary_multiply, 2504, 2505, 2506);
  g->Binary(ynn_binary_add, 2484, 2506, 2507);
  g->Convert(6821, 2508);
  g->Binary(ynn_binary_multiply, 2507, 2508, 2509);
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
  g->Quantize(2517, 2518, 0.621565580368042, 0);
  g->Transpose(6864, 4934, {1,0});
  g->Binary(ynn_binary_multiply, 4931, 4933, 4929);
  g->Dot(2518, 4934, YNN_INVALID_VALUE_ID, 4928, 1);
  g->DequantizeTensor(4928, YNN_INVALID_VALUE_ID, 4929, 4930);
  g->QuantizeTensor(4930, 6412, 4932, 2519);
  g->Dequantize(2519, 2520, 0.45866140723228455, 0);
  g->SplitDim(2520, 2521, 2, {8,256});
  g->FuseDims(2521, 2523, 1, 2);
  g->SplitDim(2523, 2522, 1, {8,1});
  g->Unary(ynn_unary_square, 2522, 2524);
  g->Reduce(ynn_reduce_sum, 2524, 6121, {3}, true);
  g->ShapeProduct(2524, 6120, {3});
  g->Binary(ynn_binary_divide, 6121, 6120, 2525);
  g->Binary(ynn_binary_add, 2525, 6446, 2527);
  g->Binary(ynn_binary_pow, 2527, 6448, 2528);
  g->Binary(ynn_binary_multiply, 2522, 2528, 2529);
  g->Convert(6863, 2530);
  g->Binary(ynn_binary_multiply, 2529, 2530, 2531);
  g->Slice(2531, 2532, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2531, 2533, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2533, 2534);
  g->Concat({2534,2532}, 2535, 3);
  g->Binary(ynn_binary_multiply, 2531, 2173, 2536);
  g->Binary(ynn_binary_multiply, 2535, 3050, 2538);
  g->Binary(ynn_binary_add, 2536, 2538, 2539);
}

// Scope: "Layer30 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer30AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(2539, 772, 2540, false, true);
  g->Mask(2540, 6477, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6477, 6125, {-1}, true);
  g->Binary(ynn_binary_subtract, 6477, 6125, 6122);
  g->Unary(ynn_unary_exp, 6122, 6123);
  g->Reduce(ynn_reduce_sum, 6123, 6126, {-1}, true);
  g->Binary(ynn_binary_divide, 5474, 6126, 6124);
  g->Binary(ynn_binary_multiply, 6123, 6124, 2541);
  g->Matmul(2541, 774, 2542, false, false);
}

// Scope: "Layer30 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer30AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(2542, 2544, 1, 2);
  g->SplitDim(2544, 2543, 1, {1,8});
  g->FuseDims(2543, 2545, 2, 2);
  g->Quantize(2545, 2546, 0.02399115078151226, 0);
  g->Transpose(6862, 4941, {1,0});
  g->Binary(ynn_binary_multiply, 4938, 4940, 4936);
  g->Dot(2546, 4941, YNN_INVALID_VALUE_ID, 4935, 1);
  g->DequantizeTensor(4935, YNN_INVALID_VALUE_ID, 4936, 4937);
  g->QuantizeTensor(4937, 6412, 4939, 2547);
  g->Dequantize(2547, 2549, 0.05247194319963455, 0);
}

// Scope: "Layer30 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer30Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2509, 2510);
  g->Reduce(ynn_reduce_sum, 2510, 6119, {2}, true);
  g->ShapeProduct(2510, 6118, {2});
  g->Binary(ynn_binary_divide, 6119, 6118, 2511);
  g->Binary(ynn_binary_add, 2511, 6446, 2512);
  g->Binary(ynn_binary_pow, 2512, 6448, 2513);
  g->Binary(ynn_binary_multiply, 2509, 2513, 2515);
  g->Convert(6851, 2516);
  g->Binary(ynn_binary_multiply, 2515, 2516, 2517);
  BuildLayer30AttentionQueryProjection(ctx);
  BuildLayer30AttentionSdpa(ctx);
  BuildLayer30AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2549, 2550);
  g->Reduce(ynn_reduce_sum, 2550, 6128, {2}, true);
  g->ShapeProduct(2550, 6127, {2});
  g->Binary(ynn_binary_divide, 6128, 6127, 2551);
  g->Binary(ynn_binary_add, 2551, 6446, 2552);
  g->Binary(ynn_binary_pow, 2552, 6448, 2553);
  g->Binary(ynn_binary_multiply, 2549, 2553, 2554);
  g->Convert(6858, 2555);
  g->Binary(ynn_binary_multiply, 2554, 2555, 2556);
  g->Binary(ynn_binary_add, 2509, 2556, 2557);
}

// Scope: "Layer30 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer30Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2557, 2558);
  g->Reduce(ynn_reduce_sum, 2558, 6130, {2}, true);
  g->ShapeProduct(2558, 6129, {2});
  g->Binary(ynn_binary_divide, 6130, 6129, 2560);
  g->Binary(ynn_binary_add, 2560, 6446, 2561);
  g->Binary(ynn_binary_pow, 2561, 6448, 2562);
  g->Binary(ynn_binary_multiply, 2557, 2562, 2563);
  g->Convert(6861, 2564);
  g->Binary(ynn_binary_multiply, 2563, 2564, 2565);
  g->Quantize(2565, 2566, 0.02257225476205349, 0);
  g->Transpose(6855, 4948, {1,0});
  g->Binary(ynn_binary_multiply, 4945, 4947, 4943);
  g->Dot(2566, 4948, YNN_INVALID_VALUE_ID, 4942, 1);
  g->DequantizeTensor(4942, YNN_INVALID_VALUE_ID, 4943, 4944);
  g->QuantizeTensor(4944, 6412, 4946, 2567);
  g->Dequantize(2567, 2568, 0.028789378702640533, 0);
  g->Transpose(6854, 4953, {1,0});
  g->Binary(ynn_binary_multiply, 4945, 4952, 4950);
  g->Dot(2566, 4953, YNN_INVALID_VALUE_ID, 4949, 1);
  g->DequantizeTensor(4949, YNN_INVALID_VALUE_ID, 4950, 4951);
  g->QuantizeTensor(4951, 6412, 4946, 2570);
  g->Dequantize(2570, 2571, 0.028789378702640533, 0);
  g->Polynomial(2571, 6133, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6133, 6134);
  g->Binary(ynn_binary_add, 6134, 5474, 6131);
  g->Binary(ynn_binary_multiply, 2571, 5472, 6132);
  g->Binary(ynn_binary_multiply, 6132, 6131, 2572);
  g->Binary(ynn_binary_multiply, 2568, 2572, 2573);
  g->Quantize(2573, 2574, 0.07234252989292145, 0);
  g->Transpose(6853, 4959, {1,0});
  g->Binary(ynn_binary_multiply, 4253, 4958, 4955);
  g->Dot(2574, 4959, YNN_INVALID_VALUE_ID, 4954, 1);
  g->DequantizeTensor(4954, YNN_INVALID_VALUE_ID, 4955, 4956);
  g->QuantizeTensor(4956, 6412, 4957, 2575);
  g->Dequantize(2575, 2576, 0.2192506492137909, 0);
  g->Unary(ynn_unary_square, 2576, 2577);
  g->Reduce(ynn_reduce_sum, 2577, 6136, {2}, true);
  g->ShapeProduct(2577, 6135, {2});
  g->Binary(ynn_binary_divide, 6136, 6135, 2578);
  g->Binary(ynn_binary_add, 2578, 6446, 2579);
  g->Binary(ynn_binary_pow, 2579, 6448, 2581);
  g->Binary(ynn_binary_multiply, 2576, 2581, 2582);
  g->Convert(6859, 2583);
  g->Binary(ynn_binary_multiply, 2582, 2583, 2584);
  g->Binary(ynn_binary_add, 2557, 2584, 2585);
}

// Scope: "Layer30 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer30PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1064, 2586, {0,0,30,0}, {-1,-1,1,-1});
  g->Reshape(2586, 2587, {1,1,256});
  g->Binary(ynn_binary_add, 2587, 7050, 2588);
  g->Binary(ynn_binary_multiply, 2588, 6444, 2589);
  g->Quantize(2585, 2590, 0.13473963737487793, 0);
  g->Transpose(6856, 4966, {1,0});
  g->Binary(ynn_binary_multiply, 4963, 4965, 4961);
  g->Dot(2590, 4966, YNN_INVALID_VALUE_ID, 4960, 1);
  g->DequantizeTensor(4960, YNN_INVALID_VALUE_ID, 4961, 4962);
  g->QuantizeTensor(4962, 6412, 4964, 2592);
  g->Dequantize(2592, 2593, 0.09596457332372665, 0);
  g->Polynomial(2593, 6139, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6139, 6140);
  g->Binary(ynn_binary_add, 6140, 5474, 6137);
  g->Binary(ynn_binary_multiply, 2593, 5472, 6138);
  g->Binary(ynn_binary_multiply, 6138, 6137, 2594);
  g->Binary(ynn_binary_multiply, 2594, 2589, 2595);
  g->Quantize(2595, 2596, 0.18700788915157318, 0);
  g->Transpose(6857, 4973, {1,0});
  g->Binary(ynn_binary_multiply, 4970, 4972, 4968);
  g->Dot(2596, 4973, YNN_INVALID_VALUE_ID, 4967, 1);
  g->DequantizeTensor(4967, YNN_INVALID_VALUE_ID, 4968, 4969);
  g->QuantizeTensor(4969, 6412, 4971, 2597);
  g->Dequantize(2597, 2598, 0.27509135007858276, 0);
  g->Unary(ynn_unary_square, 2598, 2599);
  g->Reduce(ynn_reduce_sum, 2599, 6142, {2}, true);
  g->ShapeProduct(2599, 6141, {2});
  g->Binary(ynn_binary_divide, 6142, 6141, 2600);
  g->Binary(ynn_binary_add, 2600, 6446, 2601);
  g->Binary(ynn_binary_pow, 2601, 6448, 2603);
  g->Binary(ynn_binary_multiply, 2598, 2603, 2604);
  g->Convert(6860, 2605);
  g->Binary(ynn_binary_multiply, 2604, 2605, 2606);
  g->Binary(ynn_binary_add, 2585, 2606, 2607);
  g->Convert(6852, 2608);
  g->Binary(ynn_binary_multiply, 2607, 2608, 2609);
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
  g->Quantize(2618, 2619, 0.6227923035621643, 0);
  g->Transpose(6878, 4980, {1,0});
  g->Binary(ynn_binary_multiply, 4977, 4979, 4975);
  g->Dot(2619, 4980, YNN_INVALID_VALUE_ID, 4974, 1);
  g->DequantizeTensor(4974, YNN_INVALID_VALUE_ID, 4975, 4976);
  g->QuantizeTensor(4976, 6412, 4978, 2620);
  g->Dequantize(2620, 2621, 0.6574802994728088, 0);
  g->SplitDim(2621, 2622, 2, {8,256});
  g->FuseDims(2622, 2624, 1, 2);
  g->SplitDim(2624, 2623, 1, {8,1});
  g->Unary(ynn_unary_square, 2623, 2625);
  g->Reduce(ynn_reduce_sum, 2625, 6148, {3}, true);
  g->ShapeProduct(2625, 6147, {3});
  g->Binary(ynn_binary_divide, 6148, 6147, 2626);
  g->Binary(ynn_binary_add, 2626, 6446, 2627);
  g->Binary(ynn_binary_pow, 2627, 6448, 2628);
  g->Binary(ynn_binary_multiply, 2623, 2628, 2629);
  g->Convert(6877, 2630);
  g->Binary(ynn_binary_multiply, 2629, 2630, 2631);
  g->Slice(2631, 2632, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2631, 2633, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2633, 2634);
  g->Concat({2634,2632}, 2635, 3);
  g->Binary(ynn_binary_multiply, 2631, 2173, 2637);
  g->Binary(ynn_binary_multiply, 2635, 3050, 2638);
  g->Binary(ynn_binary_add, 2637, 2638, 2639);
}

// Scope: "Layer31 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer31AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(2639, 772, 2640, false, true);
  g->Mask(2640, 6478, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6478, 6157, {-1}, true);
  g->Binary(ynn_binary_subtract, 6478, 6157, 6154);
  g->Unary(ynn_unary_exp, 6154, 6155);
  g->Reduce(ynn_reduce_sum, 6155, 6158, {-1}, true);
  g->Binary(ynn_binary_divide, 5474, 6158, 6156);
  g->Binary(ynn_binary_multiply, 6155, 6156, 2641);
  g->Matmul(2641, 774, 2642, false, false);
}

// Scope: "Layer31 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer31AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(2642, 2644, 1, 2);
  g->SplitDim(2644, 2643, 1, {1,8});
  g->FuseDims(2643, 2645, 2, 2);
  g->Quantize(2645, 2646, 0.02399115078151226, 0);
  g->Transpose(6876, 4986, {1,0});
  g->Binary(ynn_binary_multiply, 4938, 4985, 4982);
  g->Dot(2646, 4986, YNN_INVALID_VALUE_ID, 4981, 1);
  g->DequantizeTensor(4981, YNN_INVALID_VALUE_ID, 4982, 4983);
  g->QuantizeTensor(4983, 6412, 4984, 2648);
  g->Dequantize(2648, 2649, 0.06142711639404297, 0);
}

// Scope: "Layer31 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer31Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2609, 2610);
  g->Reduce(ynn_reduce_sum, 2610, 6144, {2}, true);
  g->ShapeProduct(2610, 6143, {2});
  g->Binary(ynn_binary_divide, 6144, 6143, 2611);
  g->Binary(ynn_binary_add, 2611, 6446, 2612);
  g->Binary(ynn_binary_pow, 2612, 6448, 2615);
  g->Binary(ynn_binary_multiply, 2609, 2615, 2616);
  g->Convert(6865, 2617);
  g->Binary(ynn_binary_multiply, 2616, 2617, 2618);
  BuildLayer31AttentionQueryProjection(ctx);
  BuildLayer31AttentionSdpa(ctx);
  BuildLayer31AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2649, 2650);
  g->Reduce(ynn_reduce_sum, 2650, 6160, {2}, true);
  g->ShapeProduct(2650, 6159, {2});
  g->Binary(ynn_binary_divide, 6160, 6159, 2651);
  g->Binary(ynn_binary_add, 2651, 6446, 2652);
  g->Binary(ynn_binary_pow, 2652, 6448, 2653);
  g->Binary(ynn_binary_multiply, 2649, 2653, 2654);
  g->Convert(6872, 2655);
  g->Binary(ynn_binary_multiply, 2654, 2655, 2656);
  g->Binary(ynn_binary_add, 2609, 2656, 2657);
}

// Scope: "Layer31 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer31Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2657, 2660);
  g->Reduce(ynn_reduce_sum, 2660, 6162, {2}, true);
  g->ShapeProduct(2660, 6161, {2});
  g->Binary(ynn_binary_divide, 6162, 6161, 2661);
  g->Binary(ynn_binary_add, 2661, 6446, 2662);
  g->Binary(ynn_binary_pow, 2662, 6448, 2663);
  g->Binary(ynn_binary_multiply, 2657, 2663, 2664);
  g->Convert(6875, 2665);
  g->Binary(ynn_binary_multiply, 2664, 2665, 2666);
  g->Quantize(2666, 2667, 0.01708538644015789, 0);
  g->Transpose(6869, 4993, {1,0});
  g->Binary(ynn_binary_multiply, 4990, 4992, 4988);
  g->Dot(2667, 4993, YNN_INVALID_VALUE_ID, 4987, 1);
  g->DequantizeTensor(4987, YNN_INVALID_VALUE_ID, 4988, 4989);
  g->QuantizeTensor(4989, 6412, 4991, 2668);
  g->Dequantize(2668, 2669, 0.01771654561161995, 0);
  g->Transpose(6868, 4998, {1,0});
  g->Binary(ynn_binary_multiply, 4990, 4997, 4995);
  g->Dot(2667, 4998, YNN_INVALID_VALUE_ID, 4994, 1);
  g->DequantizeTensor(4994, YNN_INVALID_VALUE_ID, 4995, 4996);
  g->QuantizeTensor(4996, 6412, 4991, 2671);
  g->Dequantize(2671, 2672, 0.01771654561161995, 0);
  g->Polynomial(2672, 6165, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6165, 6166);
  g->Binary(ynn_binary_add, 6166, 5474, 6163);
  g->Binary(ynn_binary_multiply, 2672, 5472, 6164);
  g->Binary(ynn_binary_multiply, 6164, 6163, 2673);
  g->Binary(ynn_binary_multiply, 2669, 2673, 2674);
  g->Quantize(2674, 2675, 0.027189970016479492, 0);
  g->Transpose(6867, 5005, {1,0});
  g->Binary(ynn_binary_multiply, 5002, 5004, 5000);
  g->Dot(2675, 5005, YNN_INVALID_VALUE_ID, 4999, 1);
  g->DequantizeTensor(4999, YNN_INVALID_VALUE_ID, 5000, 5001);
  g->QuantizeTensor(5001, 6412, 5003, 2676);
  g->Dequantize(2676, 2677, 0.11200025677680969, 0);
  g->Unary(ynn_unary_square, 2677, 2678);
  g->Reduce(ynn_reduce_sum, 2678, 6168, {2}, true);
  g->ShapeProduct(2678, 6167, {2});
  g->Binary(ynn_binary_divide, 6168, 6167, 2679);
  g->Binary(ynn_binary_add, 2679, 6446, 2681);
  g->Binary(ynn_binary_pow, 2681, 6448, 2682);
  g->Binary(ynn_binary_multiply, 2677, 2682, 2683);
  g->Convert(6873, 2684);
  g->Binary(ynn_binary_multiply, 2683, 2684, 2685);
  g->Binary(ynn_binary_add, 2657, 2685, 2686);
}

// Scope: "Layer31 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer31PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1064, 2687, {0,0,31,0}, {-1,-1,1,-1});
  g->Reshape(2687, 2688, {1,1,256});
  g->Binary(ynn_binary_add, 2688, 7051, 2689);
  g->Binary(ynn_binary_multiply, 2689, 6444, 2690);
  g->Quantize(2686, 2692, 0.1916448324918747, 0);
  g->Transpose(6870, 5018, {1,0});
  g->Binary(ynn_binary_multiply, 5016, 5017, 5014);
  g->Dot(2692, 5018, YNN_INVALID_VALUE_ID, 5013, 1);
  g->DequantizeTensor(5013, YNN_INVALID_VALUE_ID, 5014, 5015);
  g->QuantizeTensor(5015, 6412, 4821, 2693);
  g->Dequantize(2693, 2694, 0.07578741014003754, 0);
  g->Polynomial(2694, 6171, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6171, 6172);
  g->Binary(ynn_binary_add, 6172, 5474, 6169);
  g->Binary(ynn_binary_multiply, 2694, 5472, 6170);
  g->Binary(ynn_binary_multiply, 6170, 6169, 2695);
  g->Binary(ynn_binary_multiply, 2695, 2690, 2696);
  g->Quantize(2696, 2697, 0.24507875740528107, 0);
  g->Transpose(6871, 5025, {1,0});
  g->Binary(ynn_binary_multiply, 5022, 5024, 5020);
  g->Dot(2697, 5025, YNN_INVALID_VALUE_ID, 5019, 1);
  g->DequantizeTensor(5019, YNN_INVALID_VALUE_ID, 5020, 5021);
  g->QuantizeTensor(5021, 6412, 5023, 2698);
  g->Dequantize(2698, 2699, 0.3233283758163452, 0);
  g->Unary(ynn_unary_square, 2699, 2700);
  g->Reduce(ynn_reduce_sum, 2700, 6174, {2}, true);
  g->ShapeProduct(2700, 6173, {2});
  g->Binary(ynn_binary_divide, 6174, 6173, 2701);
  g->Binary(ynn_binary_add, 2701, 6446, 2703);
  g->Binary(ynn_binary_pow, 2703, 6448, 2704);
  g->Binary(ynn_binary_multiply, 2699, 2704, 2705);
  g->Convert(6874, 2706);
  g->Binary(ynn_binary_multiply, 2705, 2706, 2707);
  g->Binary(ynn_binary_add, 2686, 2707, 2708);
  g->Convert(6866, 2709);
  g->Binary(ynn_binary_multiply, 2708, 2709, 2710);
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
  g->Quantize(2718, 2719, 0.6824333071708679, 0);
  g->Transpose(6892, 5032, {1,0});
  g->Binary(ynn_binary_multiply, 5029, 5031, 5027);
  g->Dot(2719, 5032, YNN_INVALID_VALUE_ID, 5026, 1);
  g->DequantizeTensor(5026, YNN_INVALID_VALUE_ID, 5027, 5028);
  g->QuantizeTensor(5028, 6412, 5030, 2720);
  g->Dequantize(2720, 2721, 0.4645669162273407, 0);
  g->SplitDim(2721, 2722, 2, {8,256});
  g->FuseDims(2722, 2724, 1, 2);
  g->SplitDim(2724, 2723, 1, {8,1});
  g->Unary(ynn_unary_square, 2723, 2727);
  g->Reduce(ynn_reduce_sum, 2727, 6180, {3}, true);
  g->ShapeProduct(2727, 6179, {3});
  g->Binary(ynn_binary_divide, 6180, 6179, 2728);
  g->Binary(ynn_binary_add, 2728, 6446, 2729);
  g->Binary(ynn_binary_pow, 2729, 6448, 2730);
  g->Binary(ynn_binary_multiply, 2723, 2730, 2731);
  g->Convert(6891, 2732);
  g->Binary(ynn_binary_multiply, 2731, 2732, 2733);
  g->Slice(2733, 2734, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2733, 2735, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2735, 2736);
  g->Concat({2736,2734}, 2738, 3);
  g->Binary(ynn_binary_multiply, 2733, 2173, 2739);
  g->Binary(ynn_binary_multiply, 2738, 3050, 2740);
  g->Binary(ynn_binary_add, 2739, 2740, 2741);
}

// Scope: "Layer32 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer32AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(2741, 772, 2742, false, true);
  g->Mask(2742, 6479, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6479, 6184, {-1}, true);
  g->Binary(ynn_binary_subtract, 6479, 6184, 6181);
  g->Unary(ynn_unary_exp, 6181, 6182);
  g->Reduce(ynn_reduce_sum, 6182, 6185, {-1}, true);
  g->Binary(ynn_binary_divide, 5474, 6185, 6183);
  g->Binary(ynn_binary_multiply, 6182, 6183, 2743);
  g->Matmul(2743, 774, 2744, false, false);
}

// Scope: "Layer32 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer32AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(2744, 2746, 1, 2);
  g->SplitDim(2746, 2745, 1, {1,8});
  g->FuseDims(2745, 2747, 2, 2);
  g->Quantize(2747, 2749, 0.023006899282336235, 0);
  g->Transpose(6890, 5038, {1,0});
  g->Binary(ynn_binary_multiply, 4327, 5037, 5034);
  g->Dot(2749, 5038, YNN_INVALID_VALUE_ID, 5033, 1);
  g->DequantizeTensor(5033, YNN_INVALID_VALUE_ID, 5034, 5035);
  g->QuantizeTensor(5035, 6412, 5036, 2750);
  g->Dequantize(2750, 2751, 0.056797921657562256, 0);
}

// Scope: "Layer32 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer32Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2710, 2711);
  g->Reduce(ynn_reduce_sum, 2711, 6176, {2}, true);
  g->ShapeProduct(2711, 6175, {2});
  g->Binary(ynn_binary_divide, 6176, 6175, 2712);
  g->Binary(ynn_binary_add, 2712, 6446, 2714);
  g->Binary(ynn_binary_pow, 2714, 6448, 2715);
  g->Binary(ynn_binary_multiply, 2710, 2715, 2716);
  g->Convert(6879, 2717);
  g->Binary(ynn_binary_multiply, 2716, 2717, 2718);
  BuildLayer32AttentionQueryProjection(ctx);
  BuildLayer32AttentionSdpa(ctx);
  BuildLayer32AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2751, 2752);
  g->Reduce(ynn_reduce_sum, 2752, 6187, {2}, true);
  g->ShapeProduct(2752, 6186, {2});
  g->Binary(ynn_binary_divide, 6187, 6186, 2753);
  g->Binary(ynn_binary_add, 2753, 6446, 2754);
  g->Binary(ynn_binary_pow, 2754, 6448, 2755);
  g->Binary(ynn_binary_multiply, 2751, 2755, 2756);
  g->Convert(6886, 2757);
  g->Binary(ynn_binary_multiply, 2756, 2757, 2758);
  g->Binary(ynn_binary_add, 2710, 2758, 2760);
}

// Scope: "Layer32 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer32Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2760, 2761);
  g->Reduce(ynn_reduce_sum, 2761, 6189, {2}, true);
  g->ShapeProduct(2761, 6188, {2});
  g->Binary(ynn_binary_divide, 6189, 6188, 2762);
  g->Binary(ynn_binary_add, 2762, 6446, 2763);
  g->Binary(ynn_binary_pow, 2763, 6448, 2764);
  g->Binary(ynn_binary_multiply, 2760, 2764, 2765);
  g->Convert(6889, 2766);
  g->Binary(ynn_binary_multiply, 2765, 2766, 2767);
  g->Quantize(2767, 2768, 0.014212466776371002, 0);
  g->Transpose(6883, 5045, {1,0});
  g->Binary(ynn_binary_multiply, 5042, 5044, 5040);
  g->Dot(2768, 5045, YNN_INVALID_VALUE_ID, 5039, 1);
  g->DequantizeTensor(5039, YNN_INVALID_VALUE_ID, 5040, 5041);
  g->QuantizeTensor(5041, 6412, 5043, 2769);
  g->Dequantize(2769, 2771, 0.019192922860383987, 0);
  g->Transpose(6882, 5050, {1,0});
  g->Binary(ynn_binary_multiply, 5042, 5049, 5047);
  g->Dot(2768, 5050, YNN_INVALID_VALUE_ID, 5046, 1);
  g->DequantizeTensor(5046, YNN_INVALID_VALUE_ID, 5047, 5048);
  g->QuantizeTensor(5048, 6412, 5043, 2772);
  g->Dequantize(2772, 2773, 0.019192922860383987, 0);
  g->Polynomial(2773, 6192, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6192, 6193);
  g->Binary(ynn_binary_add, 6193, 5474, 6190);
  g->Binary(ynn_binary_multiply, 2773, 5472, 6191);
  g->Binary(ynn_binary_multiply, 6191, 6190, 2774);
  g->Binary(ynn_binary_multiply, 2771, 2774, 2775);
  g->Quantize(2775, 2776, 0.025221465155482292, 0);
  g->Transpose(6881, 5056, {1,0});
  g->Binary(ynn_binary_multiply, 4485, 5055, 5052);
  g->Dot(2776, 5056, YNN_INVALID_VALUE_ID, 5051, 1);
  g->DequantizeTensor(5051, YNN_INVALID_VALUE_ID, 5052, 5053);
  g->QuantizeTensor(5053, 6412, 5054, 2777);
  g->Dequantize(2777, 2778, 0.07002133876085281, 0);
  g->Unary(ynn_unary_square, 2778, 2779);
  g->Reduce(ynn_reduce_sum, 2779, 6195, {2}, true);
  g->ShapeProduct(2779, 6194, {2});
  g->Binary(ynn_binary_divide, 6195, 6194, 2781);
  g->Binary(ynn_binary_add, 2781, 6446, 2782);
  g->Binary(ynn_binary_pow, 2782, 6448, 2783);
  g->Binary(ynn_binary_multiply, 2778, 2783, 2784);
  g->Convert(6887, 2785);
  g->Binary(ynn_binary_multiply, 2784, 2785, 2786);
  g->Binary(ynn_binary_add, 2760, 2786, 2787);
}

// Scope: "Layer32 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer32PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1064, 2788, {0,0,32,0}, {-1,-1,1,-1});
  g->Reshape(2788, 2789, {1,1,256});
  g->Binary(ynn_binary_add, 2789, 7052, 2790);
  g->Binary(ynn_binary_multiply, 2790, 6444, 2792);
  g->Quantize(2787, 2793, 0.19188754260540009, 0);
  g->Transpose(6884, 5062, {1,0});
  g->Binary(ynn_binary_multiply, 5060, 5061, 5058);
  g->Dot(2793, 5062, YNN_INVALID_VALUE_ID, 5057, 1);
  g->DequantizeTensor(5057, YNN_INVALID_VALUE_ID, 5058, 5059);
  g->QuantizeTensor(5059, 6412, 4813, 2794);
  g->Dequantize(2794, 2795, 0.09104331582784653, 0);
  g->Polynomial(2795, 6198, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6198, 6199);
  g->Binary(ynn_binary_add, 6199, 5474, 6196);
  g->Binary(ynn_binary_multiply, 2795, 5472, 6197);
  g->Binary(ynn_binary_multiply, 6197, 6196, 2796);
  g->Binary(ynn_binary_multiply, 2796, 2792, 2797);
  g->Quantize(2797, 2798, 0.18700788915157318, 0);
  g->Transpose(6885, 5068, {1,0});
  g->Binary(ynn_binary_multiply, 4970, 5067, 5064);
  g->Dot(2798, 5068, YNN_INVALID_VALUE_ID, 5063, 1);
  g->DequantizeTensor(5063, YNN_INVALID_VALUE_ID, 5064, 5065);
  g->QuantizeTensor(5065, 6412, 5066, 2799);
  g->Dequantize(2799, 2800, 0.21407830715179443, 0);
  g->Unary(ynn_unary_square, 2800, 2801);
  g->Reduce(ynn_reduce_sum, 2801, 6201, {2}, true);
  g->ShapeProduct(2801, 6200, {2});
  g->Binary(ynn_binary_divide, 6201, 6200, 2803);
  g->Binary(ynn_binary_add, 2803, 6446, 2804);
  g->Binary(ynn_binary_pow, 2804, 6448, 2805);
  g->Binary(ynn_binary_multiply, 2800, 2805, 2806);
  g->Convert(6888, 2807);
  g->Binary(ynn_binary_multiply, 2806, 2807, 2808);
  g->Binary(ynn_binary_add, 2787, 2808, 2809);
  g->Convert(6880, 2810);
  g->Binary(ynn_binary_multiply, 2809, 2810, 2811);
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
  g->Quantize(2819, 2820, 0.9355496764183044, 0);
  g->Transpose(6906, 5075, {1,0});
  g->Binary(ynn_binary_multiply, 5072, 5074, 5070);
  g->Dot(2820, 5075, YNN_INVALID_VALUE_ID, 5069, 1);
  g->DequantizeTensor(5069, YNN_INVALID_VALUE_ID, 5070, 5071);
  g->QuantizeTensor(5071, 6412, 5073, 2821);
  g->Dequantize(2821, 2822, 0.33464565873146057, 0);
  g->SplitDim(2822, 2823, 2, {8,256});
  g->FuseDims(2823, 2826, 1, 2);
  g->SplitDim(2826, 2825, 1, {8,1});
  g->Unary(ynn_unary_square, 2825, 2827);
  g->Reduce(ynn_reduce_sum, 2827, 6207, {3}, true);
  g->ShapeProduct(2827, 6206, {3});
  g->Binary(ynn_binary_divide, 6207, 6206, 2828);
  g->Binary(ynn_binary_add, 2828, 6446, 2829);
  g->Binary(ynn_binary_pow, 2829, 6448, 2830);
  g->Binary(ynn_binary_multiply, 2825, 2830, 2831);
  g->Convert(6905, 2832);
  g->Binary(ynn_binary_multiply, 2831, 2832, 2833);
  g->Slice(2833, 2834, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2833, 2835, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2835, 2838);
  g->Concat({2838,2834}, 2839, 3);
  g->Binary(ynn_binary_multiply, 2833, 2173, 2840);
  g->Binary(ynn_binary_multiply, 2839, 3050, 2841);
  g->Binary(ynn_binary_add, 2840, 2841, 2842);
}

// Scope: "Layer33 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer33AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(2842, 772, 2843, false, true);
  g->Mask(2843, 6480, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 6480, 6211, {-1}, true);
  g->Binary(ynn_binary_subtract, 6480, 6211, 6208);
  g->Unary(ynn_unary_exp, 6208, 6209);
  g->Reduce(ynn_reduce_sum, 6209, 6212, {-1}, true);
  g->Binary(ynn_binary_divide, 5474, 6212, 6210);
  g->Binary(ynn_binary_multiply, 6209, 6210, 2844);
  g->Matmul(2844, 774, 2845, false, false);
}

// Scope: "Layer33 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer33AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(2845, 2847, 1, 2);
  g->SplitDim(2847, 2846, 1, {1,8});
  g->FuseDims(2846, 2849, 2, 2);
  g->Quantize(2849, 2850, 0.02276083640754223, 0);
  g->Transpose(6904, 5081, {1,0});
  g->Binary(ynn_binary_multiply, 4439, 5080, 5077);
  g->Dot(2850, 5081, YNN_INVALID_VALUE_ID, 5076, 1);
  g->DequantizeTensor(5076, YNN_INVALID_VALUE_ID, 5077, 5078);
  g->QuantizeTensor(5078, 6412, 5079, 2851);
  g->Dequantize(2851, 2852, 0.02861599810421467, 0);
}

// Scope: "Layer33 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer33Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2811, 2812);
  g->Reduce(ynn_reduce_sum, 2812, 6205, {2}, true);
  g->ShapeProduct(2812, 6204, {2});
  g->Binary(ynn_binary_divide, 6205, 6204, 2814);
  g->Binary(ynn_binary_add, 2814, 6446, 2815);
  g->Binary(ynn_binary_pow, 2815, 6448, 2816);
  g->Binary(ynn_binary_multiply, 2811, 2816, 2817);
  g->Convert(6893, 2818);
  g->Binary(ynn_binary_multiply, 2817, 2818, 2819);
  BuildLayer33AttentionQueryProjection(ctx);
  BuildLayer33AttentionSdpa(ctx);
  BuildLayer33AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2852, 2853);
  g->Reduce(ynn_reduce_sum, 2853, 6214, {2}, true);
  g->ShapeProduct(2853, 6213, {2});
  g->Binary(ynn_binary_divide, 6214, 6213, 2854);
  g->Binary(ynn_binary_add, 2854, 6446, 2855);
  g->Binary(ynn_binary_pow, 2855, 6448, 2856);
  g->Binary(ynn_binary_multiply, 2852, 2856, 2857);
  g->Convert(6900, 2858);
  g->Binary(ynn_binary_multiply, 2857, 2858, 2860);
  g->Binary(ynn_binary_add, 2811, 2860, 2861);
}

// Scope: "Layer33 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer33Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2861, 2862);
  g->Reduce(ynn_reduce_sum, 2862, 6216, {2}, true);
  g->ShapeProduct(2862, 6215, {2});
  g->Binary(ynn_binary_divide, 6216, 6215, 2863);
  g->Binary(ynn_binary_add, 2863, 6446, 2864);
  g->Binary(ynn_binary_pow, 2864, 6448, 2865);
  g->Binary(ynn_binary_multiply, 2861, 2865, 2866);
  g->Convert(6903, 2867);
  g->Binary(ynn_binary_multiply, 2866, 2867, 2868);
  g->Quantize(2868, 2869, 0.016980575397610664, 0);
  g->Transpose(6897, 5088, {1,0});
  g->Binary(ynn_binary_multiply, 5085, 5087, 5083);
  g->Dot(2869, 5088, YNN_INVALID_VALUE_ID, 5082, 1);
  g->DequantizeTensor(5082, YNN_INVALID_VALUE_ID, 5083, 5084);
  g->QuantizeTensor(5084, 6412, 5086, 2871);
  g->Dequantize(2871, 2872, 0.018700797110795975, 0);
  g->Transpose(6896, 5093, {1,0});
  g->Binary(ynn_binary_multiply, 5085, 5092, 5090);
  g->Dot(2869, 5093, YNN_INVALID_VALUE_ID, 5089, 1);
  g->DequantizeTensor(5089, YNN_INVALID_VALUE_ID, 5090, 5091);
  g->QuantizeTensor(5091, 6412, 5086, 2873);
  g->Dequantize(2873, 2874, 0.018700797110795975, 0);
  g->Polynomial(2874, 6219, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6219, 6220);
  g->Binary(ynn_binary_add, 6220, 5474, 6217);
  g->Binary(ynn_binary_multiply, 2874, 5472, 6218);
  g->Binary(ynn_binary_multiply, 6218, 6217, 2875);
  g->Binary(ynn_binary_multiply, 2872, 2875, 2876);
  g->Quantize(2876, 2877, 0.02989666350185871, 0);
  g->Transpose(6895, 5100, {1,0});
  g->Binary(ynn_binary_multiply, 5097, 5099, 5095);
  g->Dot(2877, 5100, YNN_INVALID_VALUE_ID, 5094, 1);
  g->DequantizeTensor(5094, YNN_INVALID_VALUE_ID, 5095, 5096);
  g->QuantizeTensor(5096, 6412, 5098, 2878);
  g->Dequantize(2878, 2879, 0.053163815289735794, 0);
  g->Unary(ynn_unary_square, 2879, 2881);
  g->Reduce(ynn_reduce_sum, 2881, 6222, {2}, true);
  g->ShapeProduct(2881, 6221, {2});
  g->Binary(ynn_binary_divide, 6222, 6221, 2882);
  g->Binary(ynn_binary_add, 2882, 6446, 2883);
  g->Binary(ynn_binary_pow, 2883, 6448, 2884);
  g->Binary(ynn_binary_multiply, 2879, 2884, 2885);
  g->Convert(6901, 2886);
  g->Binary(ynn_binary_multiply, 2885, 2886, 2887);
  g->Binary(ynn_binary_add, 2861, 2887, 2888);
}

// Scope: "Layer33 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer33PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1064, 2889, {0,0,33,0}, {-1,-1,1,-1});
  g->Reshape(2889, 2890, {1,1,256});
  g->Binary(ynn_binary_add, 2890, 7053, 2892);
  g->Binary(ynn_binary_multiply, 2892, 6444, 2893);
  g->Quantize(2888, 2894, 0.13243837654590607, 0);
  g->Transpose(6898, 5114, {1,0});
  g->Binary(ynn_binary_multiply, 5111, 5113, 5109);
  g->Dot(2894, 5114, YNN_INVALID_VALUE_ID, 5108, 1);
  g->DequantizeTensor(5108, YNN_INVALID_VALUE_ID, 5109, 5110);
  g->QuantizeTensor(5110, 6412, 5112, 2895);
  g->Dequantize(2895, 2896, 0.1446850597858429, 0);
  g->Polynomial(2896, 6225, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6225, 6226);
  g->Binary(ynn_binary_add, 6226, 5474, 6223);
  g->Binary(ynn_binary_multiply, 2896, 5472, 6224);
  g->Binary(ynn_binary_multiply, 6224, 6223, 2897);
  g->Binary(ynn_binary_multiply, 2897, 2893, 2898);
  g->Quantize(2898, 2899, 1.5826771259307861, 0);
  g->Transpose(6899, 5121, {1,0});
  g->Binary(ynn_binary_multiply, 5118, 5120, 5116);
  g->Dot(2899, 5121, YNN_INVALID_VALUE_ID, 5115, 1);
  g->DequantizeTensor(5115, YNN_INVALID_VALUE_ID, 5116, 5117);
  g->QuantizeTensor(5117, 6412, 5119, 2900);
  g->Dequantize(2900, 2901, 0.6353945732116699, 0);
  g->Unary(ynn_unary_square, 2901, 2903);
  g->Reduce(ynn_reduce_sum, 2903, 6228, {2}, true);
  g->ShapeProduct(2903, 6227, {2});
  g->Binary(ynn_binary_divide, 6228, 6227, 2904);
  g->Binary(ynn_binary_add, 2904, 6446, 2905);
  g->Binary(ynn_binary_pow, 2905, 6448, 2906);
  g->Binary(ynn_binary_multiply, 2901, 2906, 2907);
  g->Convert(6902, 2908);
  g->Binary(ynn_binary_multiply, 2907, 2908, 2909);
  g->Binary(ynn_binary_add, 2888, 2909, 2910);
  g->Convert(6894, 2911);
  g->Binary(ynn_binary_multiply, 2910, 2911, 2912);
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
  g->Quantize(2919, 2920, 1.450958251953125, 0);
  g->Transpose(6920, 5128, {1,0});
  g->Binary(ynn_binary_multiply, 5125, 5127, 5123);
  g->Dot(2920, 5128, YNN_INVALID_VALUE_ID, 5122, 1);
  g->DequantizeTensor(5122, YNN_INVALID_VALUE_ID, 5123, 5124);
  g->QuantizeTensor(5124, 6412, 5126, 2921);
  g->Dequantize(2921, 2922, 0.6535432934761047, 0);
  g->SplitDim(2922, 2924, 2, {8,512});
  g->FuseDims(2924, 2926, 1, 2);
  g->SplitDim(2926, 2925, 1, {8,1});
  g->Unary(ynn_unary_square, 2925, 2927);
  g->Reduce(ynn_reduce_sum, 2927, 6232, {3}, true);
  g->ShapeProduct(2927, 6231, {3});
  g->Binary(ynn_binary_divide, 6232, 6231, 2928);
  g->Binary(ynn_binary_add, 2928, 6446, 2929);
  g->Binary(ynn_binary_pow, 2929, 6448, 2930);
  g->Binary(ynn_binary_multiply, 2925, 2930, 2931);
  g->Convert(6919, 2932);
  g->Binary(ynn_binary_multiply, 2931, 2932, 2933);
  g->Slice(2933, 2934, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(2933, 2936, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 2936, 2937);
  g->Concat({2937,2934}, 2938, 3);
  g->Binary(ynn_binary_multiply, 2933, 3471, 2939);
  g->Binary(ynn_binary_multiply, 2938, 3576, 2940);
  g->Binary(ynn_binary_add, 2939, 2940, 2941);
}

// Scope: "Layer34 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer34AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(2941, 907, 2942, false, true);
  g->Mask(2942, 6481, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 6481, 6236, {-1}, true);
  g->Binary(ynn_binary_subtract, 6481, 6236, 6233);
  g->Unary(ynn_unary_exp, 6233, 6234);
  g->Reduce(ynn_reduce_sum, 6234, 6237, {-1}, true);
  g->Binary(ynn_binary_divide, 5474, 6237, 6235);
  g->Binary(ynn_binary_multiply, 6234, 6235, 2943);
  g->Matmul(2943, 909, 2944, false, false);
}

// Scope: "Layer34 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer34AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(2944, 2948, 1, 2);
  g->SplitDim(2948, 2947, 1, {1,8});
  g->FuseDims(2947, 2949, 2, 2);
  g->Quantize(2949, 2950, 0.012118612416088581, 0);
  g->Transpose(6918, 5140, {1,0});
  g->Binary(ynn_binary_multiply, 5137, 5139, 5135);
  g->Dot(2950, 5140, YNN_INVALID_VALUE_ID, 5134, 1);
  g->DequantizeTensor(5134, YNN_INVALID_VALUE_ID, 5135, 5136);
  g->QuantizeTensor(5136, 6412, 5138, 2951);
  g->Dequantize(2951, 2952, 0.017325349152088165, 0);
}

// Scope: "Layer34 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer34Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2912, 2913);
  g->Reduce(ynn_reduce_sum, 2913, 6230, {2}, true);
  g->ShapeProduct(2913, 6229, {2});
  g->Binary(ynn_binary_divide, 6230, 6229, 2914);
  g->Binary(ynn_binary_add, 2914, 6446, 2915);
  g->Binary(ynn_binary_pow, 2915, 6448, 2916);
  g->Binary(ynn_binary_multiply, 2912, 2916, 2917);
  g->Convert(6907, 2918);
  g->Binary(ynn_binary_multiply, 2917, 2918, 2919);
  BuildLayer34AttentionQueryProjection(ctx);
  BuildLayer34AttentionSdpa(ctx);
  BuildLayer34AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2952, 2953);
  g->Reduce(ynn_reduce_sum, 2953, 6243, {2}, true);
  g->ShapeProduct(2953, 6242, {2});
  g->Binary(ynn_binary_divide, 6243, 6242, 2954);
  g->Binary(ynn_binary_add, 2954, 6446, 2955);
  g->Binary(ynn_binary_pow, 2955, 6448, 2956);
  g->Binary(ynn_binary_multiply, 2952, 2956, 2957);
  g->Convert(6914, 2959);
  g->Binary(ynn_binary_multiply, 2957, 2959, 2960);
  g->Binary(ynn_binary_add, 2912, 2960, 2961);
}

// Scope: "Layer34 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer34Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2961, 2962);
  g->Reduce(ynn_reduce_sum, 2962, 6245, {2}, true);
  g->ShapeProduct(2962, 6244, {2});
  g->Binary(ynn_binary_divide, 6245, 6244, 2963);
  g->Binary(ynn_binary_add, 2963, 6446, 2964);
  g->Binary(ynn_binary_pow, 2964, 6448, 2965);
  g->Binary(ynn_binary_multiply, 2961, 2965, 2966);
  g->Convert(6917, 2967);
  g->Binary(ynn_binary_multiply, 2966, 2967, 2968);
  g->Quantize(2968, 2970, 0.022695079445838928, 0);
  g->Transpose(6911, 5147, {1,0});
  g->Binary(ynn_binary_multiply, 5144, 5146, 5142);
  g->Dot(2970, 5147, YNN_INVALID_VALUE_ID, 5141, 1);
  g->DequantizeTensor(5141, YNN_INVALID_VALUE_ID, 5142, 5143);
  g->QuantizeTensor(5143, 6412, 5145, 2971);
  g->Dequantize(2971, 2972, 0.039862215518951416, 0);
  g->Transpose(6910, 5152, {1,0});
  g->Binary(ynn_binary_multiply, 5144, 5151, 5149);
  g->Dot(2970, 5152, YNN_INVALID_VALUE_ID, 5148, 1);
  g->DequantizeTensor(5148, YNN_INVALID_VALUE_ID, 5149, 5150);
  g->QuantizeTensor(5150, 6412, 5145, 2973);
  g->Dequantize(2973, 2974, 0.039862215518951416, 0);
  g->Polynomial(2974, 6248, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6248, 6249);
  g->Binary(ynn_binary_add, 6249, 5474, 6246);
  g->Binary(ynn_binary_multiply, 2974, 5472, 6247);
  g->Binary(ynn_binary_multiply, 6247, 6246, 2975);
  g->Binary(ynn_binary_multiply, 2972, 2975, 2976);
  g->Quantize(2976, 2977, 0.09940945357084274, 0);
  g->Transpose(6909, 5159, {1,0});
  g->Binary(ynn_binary_multiply, 5156, 5158, 5154);
  g->Dot(2977, 5159, YNN_INVALID_VALUE_ID, 5153, 1);
  g->DequantizeTensor(5153, YNN_INVALID_VALUE_ID, 5154, 5155);
  g->QuantizeTensor(5155, 6412, 5157, 2978);
  g->Dequantize(2978, 2980, 0.1543705314397812, 0);
  g->Unary(ynn_unary_square, 2980, 2981);
  g->Reduce(ynn_reduce_sum, 2981, 6251, {2}, true);
  g->ShapeProduct(2981, 6250, {2});
  g->Binary(ynn_binary_divide, 6251, 6250, 2982);
  g->Binary(ynn_binary_add, 2982, 6446, 2983);
  g->Binary(ynn_binary_pow, 2983, 6448, 2984);
  g->Binary(ynn_binary_multiply, 2980, 2984, 2985);
  g->Convert(6915, 2986);
  g->Binary(ynn_binary_multiply, 2985, 2986, 2987);
  g->Binary(ynn_binary_add, 2961, 2987, 2988);
}

// Scope: "Layer34 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer34PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1064, 2989, {0,0,34,0}, {-1,-1,1,-1});
  g->Reshape(2989, 2991, {1,1,256});
  g->Binary(ynn_binary_add, 2991, 7054, 2992);
  g->Binary(ynn_binary_multiply, 2992, 6444, 2993);
  g->Quantize(2988, 2994, 0.8795163035392761, 0);
  g->Transpose(6912, 5173, {1,0});
  g->Binary(ynn_binary_multiply, 5170, 5172, 5168);
  g->Dot(2994, 5173, YNN_INVALID_VALUE_ID, 5167, 1);
  g->DequantizeTensor(5167, YNN_INVALID_VALUE_ID, 5168, 5169);
  g->QuantizeTensor(5169, 6412, 5171, 2995);
  g->Dequantize(2995, 2996, 0.16633859276771545, 0);
  g->Polynomial(2996, 6254, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6254, 6255);
  g->Binary(ynn_binary_add, 6255, 5474, 6252);
  g->Binary(ynn_binary_multiply, 2996, 5472, 6253);
  g->Binary(ynn_binary_multiply, 6253, 6252, 2997);
  g->Binary(ynn_binary_multiply, 2997, 2993, 2998);
  g->Quantize(2998, 2999, 3.2125983238220215, 0);
  g->Transpose(6913, 5180, {1,0});
  g->Binary(ynn_binary_multiply, 5177, 5179, 5175);
  g->Dot(2999, 5180, YNN_INVALID_VALUE_ID, 5174, 1);
  g->DequantizeTensor(5174, YNN_INVALID_VALUE_ID, 5175, 5176);
  g->QuantizeTensor(5176, 6412, 5178, 3000);
  g->Dequantize(3000, 3002, 1.0930962562561035, 0);
  g->Unary(ynn_unary_square, 3002, 3003);
  g->Reduce(ynn_reduce_sum, 3003, 6257, {2}, true);
  g->ShapeProduct(3003, 6256, {2});
  g->Binary(ynn_binary_divide, 6257, 6256, 3004);
  g->Binary(ynn_binary_add, 3004, 6446, 3005);
  g->Binary(ynn_binary_pow, 3005, 6448, 3006);
  g->Binary(ynn_binary_multiply, 3002, 3006, 3007);
  g->Convert(6916, 3008);
  g->Binary(ynn_binary_multiply, 3007, 3008, 3009);
  g->Binary(ynn_binary_add, 2988, 3009, 3010);
  g->Convert(6908, 3011);
  g->Binary(ynn_binary_multiply, 3010, 3011, 3013);
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
  g->Unary(ynn_unary_square, 3013, 3014);
  g->Reduce(ynn_reduce_sum, 3014, 6261, {2}, true);
  g->ShapeProduct(3014, 6260, {2});
  g->Binary(ynn_binary_divide, 6261, 6260, 3015);
  g->Binary(ynn_binary_add, 3015, 6446, 3016);
  g->Binary(ynn_binary_pow, 3016, 6448, 3017);
  g->Binary(ynn_binary_multiply, 3013, 3017, 3018);
  g->Convert(7023, 3019);
  g->Binary(ynn_binary_multiply, 3018, 3019, 3020);
  g->Reduce(ynn_reduce_min_max, 3020, 5188, {-1}, true);
  g->DynamicQuantization(5188, 5187, 5186);
  g->QuantizeTensor(3020, 5187, 5186, 5185);
  g->Transpose(6451, 5191, {1,0});
  g->Binary(ynn_binary_multiply, 5186, 5189, 5182);
  g->Reduce(ynn_reduce_sum, 5191, 5190, {0}, true);
  g->Binary(ynn_binary_multiply, 5187, 5190, 5184);
  g->Unary(ynn_unary_negate, 5184, 5183);
  g->Dot(5185, 5191, 5183, 5181, 1);
  g->DequantizeTensor(5181, YNN_INVALID_VALUE_ID, 5182, 3021);
  g->Binary(ynn_binary_divide, 3021, 6445, 3022);
  g->Unary(ynn_unary_tanh, 3022, 3024);
  g->Binary(ynn_binary_multiply, 3024, 6445, 3025);
  g->Convert(3025, 6452);
  g->ResultShape(6452, {slinky::expr(int64_t{1}),slinky::expr(int64_t{1}),slinky::expr(int64_t{262144})});
}

}  // namespace BuildGemma4DecodeSource
