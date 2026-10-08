// Generated YNNPACK builder; do not edit.
#include "gemma4_prefill_builder.h"

namespace BuildGemma4PrefillSource {

// Scope: "Layer23 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->BeginProfileOperation("Layer23/Attention/KvProjection", "core.quantize", {2285}, {2286}, {"0/3194/Mul"});
  g->Quantize(2285, 2286, 0.062325432896614075, 0);
  g->EndProfileOperation();
  g->BeginProfileOperation("Layer23/Attention/KvProjection", "core.transpose", {5566}, {4055}, {"tensors/model.layers.23.self_attn.k_proj.weight.i4@i4"});
  g->Transpose(5566, 4055, {1,0});
  g->EndProfileOperation();
  g->BeginProfileOperation("Layer23/Attention/KvProjection", "core.mul", {4052,4054}, {4050}, {"__ynn/fc3196/input_scale","__ynn/fc3196/weight_scale"});
  g->Binary(ynn_binary_multiply, 4052, 4054, 4050);
  g->EndProfileOperation();
  g->BeginProfileOperation("Layer23/Attention/KvProjection", "ynn.dot", {2286,4055}, {4049}, {"0/3195/Quantize","tensors/model.layers.23.self_attn.k_proj.weight.i4@i4"});
  g->Dot(2286, 4055, YNN_INVALID_VALUE_ID, 4049, 1);
  g->EndProfileOperation();
  g->BeginProfileOperation("Layer23/Attention/KvProjection", "ynn.dequantize", {4049,4050}, {4051}, {"__ynn/fc3196/accumulator","__ynn/fc3196/accumulator_scale"});
  g->DequantizeTensor(4049, YNN_INVALID_VALUE_ID, 4050, 4051);
  g->EndProfileOperation();
  g->BeginProfileOperation("Layer23/Attention/KvProjection", "ynn.quantize", {4051,5190,4053}, {2287}, {"__ynn/fc3196/float","__ynn/zero","__ynn/fc3196/output_scale"});
  g->QuantizeTensor(4051, 5190, 4053, 2287);
  g->EndProfileOperation();
  g->BeginProfileOperation("Layer23/Attention/KvProjection", "core.dequantize", {2287}, {2288}, {"0/3196/FullyConnected"});
  g->Dequantize(2287, 2288, 0.05413386970758438, 0);
  g->EndProfileOperation();
  g->BeginProfileOperation("Layer23/Attention/KvProjection", "ynn.split_dim", {2288}, {2289}, {"0/3197/Dequantize"});
  g->SplitDim(2288, 2289, 2, {2,512});
  g->EndProfileOperation();
  g->BeginProfileOperation("Layer23/Attention/KvProjection", "core.transpose", {2289}, {2290}, {"0/3198/Reshape"});
  g->Transpose(2289, 2290, {0,2,1,3});
  g->EndProfileOperation();
  g->BeginProfileOperation("Layer23/Attention/KvProjection", "core.square", {2290}, {2293}, {"0/3198/Reshape"});
  g->Unary(ynn_unary_square, 2290, 2293);
  g->EndProfileOperation();
  g->BeginProfileOperation("Layer23/Attention/KvProjection", "ynn.reduce_sum", {2293}, {4991}, {"0/3200/Square"});
  g->Reduce(ynn_reduce_sum, 2293, 4991, {3}, true);
  g->EndProfileOperation();
  g->BeginProfileOperation("Layer23/Attention/KvProjection", "ynn.get_shape", {2293}, {4990}, {"0/3200/Square"});
  g->ShapeProduct(2293, 4990, {3});
  g->EndProfileOperation();
  g->BeginProfileOperation("Layer23/Attention/KvProjection", "core.div", {4991,4990}, {2294}, {"__ynn/op3201/sum","__ynn/op3201/divisor"});
  g->Binary(ynn_binary_divide, 4991, 4990, 2294);
  g->EndProfileOperation();
  g->BeginProfileOperation("Layer23/Attention/KvProjection", "core.add", {2294,5241}, {2295}, {"0/3201/Mean","literal/f32/9a4714b45c1b4542f05e47efc3f40eed9a43645882c547dcbbdf7090a0212deb"});
  g->Binary(ynn_binary_add, 2294, 5241, 2295);
  g->EndProfileOperation();
  g->BeginProfileOperation("Layer23/Attention/KvProjection", "core.rsqrt", {2295}, {2296}, {"0/3202/Add"});
  g->Unary(ynn_unary_rsqrt, 2295, 2296);
  g->EndProfileOperation();
  g->BeginProfileOperation("Layer23/Attention/KvProjection", "core.mul", {2290,2296}, {2297}, {"0/3198/Reshape","0/3203/Rsqrt"});
  g->Binary(ynn_binary_multiply, 2290, 2296, 2297);
  g->EndProfileOperation();
  g->BeginProfileOperation("Layer23/Attention/KvProjection", "core.mul", {2297,5565}, {2298}, {"0/3204/Mul","tensors/model.layers.23.self_attn.k_norm.weight.f32@f32"});
  g->Binary(ynn_binary_multiply, 2297, 5565, 2298);
  g->EndProfileOperation();
  g->BeginProfileOperation("Layer23/Attention/KvProjection", "core.slice", {2298}, {2299}, {"0/3205/Mul"});
  g->Slice(2298, 2299, {0,0,0,0}, {-1,-1,-1,256});
  g->EndProfileOperation();
  g->BeginProfileOperation("Layer23/Attention/KvProjection", "core.slice", {2298}, {2300}, {"0/3205/Mul"});
  g->Slice(2298, 2300, {0,0,0,256}, {-1,-1,-1,256});
  g->EndProfileOperation();
  g->BeginProfileOperation("Layer23/Attention/KvProjection", "core.neg", {2300}, {2301}, {"0/3207/Slice"});
  g->Unary(ynn_unary_negate, 2300, 2301);
  g->EndProfileOperation();
  g->BeginProfileOperation("Layer23/Attention/KvProjection", "core.concat", {2301,2299}, {2302}, {"0/3208/Neg","0/3206/Slice"});
  g->Concat({2301,2299}, 2302, 3);
  g->EndProfileOperation();
  g->BeginProfileOperation("Layer23/Attention/KvProjection", "core.mul", {2298,2909}, {2304}, {"0/3205/Mul","0/9/Concatenation"});
  g->Binary(ynn_binary_multiply, 2298, 2909, 2304);
  g->EndProfileOperation();
  g->BeginProfileOperation("Layer23/Attention/KvProjection", "core.mul", {2302,2}, {2305}, {"0/3209/Concatenation","0/10/Concatenation"});
  g->Binary(ynn_binary_multiply, 2302, 2, 2305);
  g->EndProfileOperation();
  g->BeginProfileOperation("Layer23/Attention/KvProjection", "core.add", {2304,2305}, {2306}, {"0/3210/Mul","0/3211/Mul"});
  g->Binary(ynn_binary_add, 2304, 2305, 2306);
  g->EndProfileOperation();
  g->BeginProfileOperation("Layer23/Attention/KvProjection", "core.transpose", {5567}, {4060}, {"tensors/model.layers.23.self_attn.v_proj.weight.i4@i4"});
  g->Transpose(5567, 4060, {1,0});
  g->EndProfileOperation();
  g->BeginProfileOperation("Layer23/Attention/KvProjection", "core.mul", {4052,4059}, {4057}, {"__ynn/fc3196/input_scale","__ynn/fc3214/weight_scale"});
  g->Binary(ynn_binary_multiply, 4052, 4059, 4057);
  g->EndProfileOperation();
  g->BeginProfileOperation("Layer23/Attention/KvProjection", "ynn.dot", {2286,4060}, {4056}, {"0/3195/Quantize","tensors/model.layers.23.self_attn.v_proj.weight.i4@i4"});
  g->Dot(2286, 4060, YNN_INVALID_VALUE_ID, 4056, 1);
  g->EndProfileOperation();
  g->BeginProfileOperation("Layer23/Attention/KvProjection", "ynn.dequantize", {4056,4057}, {4058}, {"__ynn/fc3214/accumulator","__ynn/fc3214/accumulator_scale"});
  g->DequantizeTensor(4056, YNN_INVALID_VALUE_ID, 4057, 4058);
  g->EndProfileOperation();
  g->BeginProfileOperation("Layer23/Attention/KvProjection", "ynn.quantize", {4058,5190,4053}, {2307}, {"__ynn/fc3214/float","__ynn/zero","__ynn/fc3196/output_scale"});
  g->QuantizeTensor(4058, 5190, 4053, 2307);
  g->EndProfileOperation();
  g->BeginProfileOperation("Layer23/Attention/KvProjection", "core.dequantize", {2307}, {2308}, {"0/3214/FullyConnected"});
  g->Dequantize(2307, 2308, 0.05413386970758438, 0);
  g->EndProfileOperation();
  g->BeginProfileOperation("Layer23/Attention/KvProjection", "ynn.split_dim", {2308}, {2309}, {"0/3215/Dequantize"});
  g->SplitDim(2308, 2309, 2, {2,512});
  g->EndProfileOperation();
  g->BeginProfileOperation("Layer23/Attention/KvProjection", "core.transpose", {2309}, {2310}, {"0/3216/Reshape"});
  g->Transpose(2309, 2310, {0,2,1,3});
  g->EndProfileOperation();
  g->BeginProfileOperation("Layer23/Attention/KvProjection", "core.square", {2310}, {2311}, {"0/3216/Reshape"});
  g->Unary(ynn_unary_square, 2310, 2311);
  g->EndProfileOperation();
  g->BeginProfileOperation("Layer23/Attention/KvProjection", "ynn.reduce_sum", {2311}, {4995}, {"0/3218/Square"});
  g->Reduce(ynn_reduce_sum, 2311, 4995, {3}, true);
  g->EndProfileOperation();
  g->BeginProfileOperation("Layer23/Attention/KvProjection", "ynn.get_shape", {2311}, {4994}, {"0/3218/Square"});
  g->ShapeProduct(2311, 4994, {3});
  g->EndProfileOperation();
  g->BeginProfileOperation("Layer23/Attention/KvProjection", "core.div", {4995,4994}, {2312}, {"__ynn/op3219/sum","__ynn/op3219/divisor"});
  g->Binary(ynn_binary_divide, 4995, 4994, 2312);
  g->EndProfileOperation();
  g->BeginProfileOperation("Layer23/Attention/KvProjection", "core.add", {2312,5241}, {2314}, {"0/3219/Mean","literal/f32/9a4714b45c1b4542f05e47efc3f40eed9a43645882c547dcbbdf7090a0212deb"});
  g->Binary(ynn_binary_add, 2312, 5241, 2314);
  g->EndProfileOperation();
  g->BeginProfileOperation("Layer23/Attention/KvProjection", "core.rsqrt", {2314}, {2315}, {"0/3220/Add"});
  g->Unary(ynn_unary_rsqrt, 2314, 2315);
  g->EndProfileOperation();
  g->BeginProfileOperation("Layer23/Attention/KvProjection", "core.mul", {2310,2315}, {2316}, {"0/3216/Reshape","0/3221/Rsqrt"});
  g->Binary(ynn_binary_multiply, 2310, 2315, 2316);
  g->EndProfileOperation();
}

// Scope: "Layer23 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->BeginProfileOperation("Layer23/Attention/CacheUpdate", "core.quantize", {2306}, {2317}, {"0/3212/Add"});
  g->Quantize(2306, 2317, 0.001091228099539876, 0);
  g->EndProfileOperation();
  g->BeginProfileOperation("Layer23/Attention/CacheUpdate", "ynn.append", {5207,2317}, {5729}, {"cache_key_23","0/3223/Quantize"});
  g->Append(5207, 2317, 5729, 2, s2, s1);
  g->EndProfileOperation();
  g->BeginProfileOperation("Layer23/Attention/CacheUpdate", "core.quantize", {2316}, {2318}, {"0/3222/Mul"});
  g->Quantize(2316, 2318, 0.01785714365541935, 0);
  g->EndProfileOperation();
  g->BeginProfileOperation("Layer23/Attention/CacheUpdate", "ynn.append", {5231,2318}, {5753}, {"cache_value_23","0/3226/Quantize"});
  g->Append(5231, 2318, 5753, 2, s2, s1);
  g->EndProfileOperation();
}

// Scope: "Layer23 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23Attention(Context& ctx) {
  auto* g = ctx.g;
  g->BeginProfileOperation("Layer23/Attention", "core.square", {2278}, {2279}, {"0/3188/Mul"});
  g->Unary(ynn_unary_square, 2278, 2279);
  g->EndProfileOperation();
  g->BeginProfileOperation("Layer23/Attention", "ynn.reduce_sum", {2279}, {4989}, {"0/3189/Square"});
  g->Reduce(ynn_reduce_sum, 2279, 4989, {2}, true);
  g->EndProfileOperation();
  g->BeginProfileOperation("Layer23/Attention", "ynn.get_shape", {2279}, {4988}, {"0/3189/Square"});
  g->ShapeProduct(2279, 4988, {2});
  g->EndProfileOperation();
  g->BeginProfileOperation("Layer23/Attention", "core.div", {4989,4988}, {2281}, {"__ynn/op3190/sum","__ynn/op3190/divisor"});
  g->Binary(ynn_binary_divide, 4989, 4988, 2281);
  g->EndProfileOperation();
  g->BeginProfileOperation("Layer23/Attention", "core.add", {2281,5241}, {2282}, {"0/3190/Mean","literal/f32/9a4714b45c1b4542f05e47efc3f40eed9a43645882c547dcbbdf7090a0212deb"});
  g->Binary(ynn_binary_add, 2281, 5241, 2282);
  g->EndProfileOperation();
  g->BeginProfileOperation("Layer23/Attention", "core.rsqrt", {2282}, {2283}, {"0/3191/Add"});
  g->Unary(ynn_unary_rsqrt, 2282, 2283);
  g->EndProfileOperation();
  g->BeginProfileOperation("Layer23/Attention", "core.mul", {2278,2283}, {2284}, {"0/3188/Mul","0/3192/Rsqrt"});
  g->Binary(ynn_binary_multiply, 2278, 2283, 2284);
  g->EndProfileOperation();
  g->BeginProfileOperation("Layer23/Attention", "core.mul", {2284,5564}, {2285}, {"0/3193/Mul","tensors/model.layers.23.input_layernorm.weight.f32@f32"});
  g->Binary(ynn_binary_multiply, 2284, 5564, 2285);
  g->EndProfileOperation();
  BuildLayer23AttentionKvProjection(ctx);
  BuildLayer23AttentionCacheUpdate(ctx);
}

// Scope: "Layer23"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23(Context& ctx) {
  BuildLayer23Attention(ctx);
}

}  // namespace BuildGemma4PrefillSource
