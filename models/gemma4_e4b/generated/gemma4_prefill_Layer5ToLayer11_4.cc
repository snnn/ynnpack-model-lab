// Generated YNNPACK builder; do not edit.
#include "gemma4_prefill_builder.h"

namespace BuildGemma4PrefillSource {

// Scope: "Layer5 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(2717, 2718, 0.11662273108959198, 0);
  g->Transpose(5614, 4237, {1,0});
  g->Binary(ynn_binary_multiply, 4234, 4236, 4232);
  g->Dot(2718, 4237, YNN_INVALID_VALUE_ID, 4231, 1);
  g->DequantizeTensor(4231, YNN_INVALID_VALUE_ID, 4232, 4233);
  g->QuantizeTensor(4233, 5190, 4235, 2719);
  g->Dequantize(2719, 2720, 0.09891732782125473, 0);
  g->SplitDim(2720, 2721, 2, {2,512});
  g->Transpose(2721, 2722, {0,2,1,3});
  g->Unary(ynn_unary_square, 2722, 2723);
  g->Reduce(ynn_reduce_sum, 2723, 5105, {3}, true);
  g->ShapeProduct(2723, 5104, {3});
  g->Binary(ynn_binary_divide, 5105, 5104, 2724);
  g->Binary(ynn_binary_add, 2724, 5241, 2725);
  g->Unary(ynn_unary_rsqrt, 2725, 2726);
  g->Binary(ynn_binary_multiply, 2722, 2726, 2728);
  g->Binary(ynn_binary_multiply, 2728, 5613, 2729);
  g->Slice(2729, 2730, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(2729, 2731, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 2731, 2732);
  g->Concat({2732,2730}, 2733, 3);
  g->Binary(ynn_binary_multiply, 2729, 2909, 2734);
  g->Binary(ynn_binary_multiply, 2733, 2, 2735);
  g->Binary(ynn_binary_add, 2734, 2735, 2736);
  g->Transpose(5618, 4242, {1,0});
  g->Binary(ynn_binary_multiply, 4234, 4241, 4239);
  g->Dot(2718, 4242, YNN_INVALID_VALUE_ID, 4238, 1);
  g->DequantizeTensor(4238, YNN_INVALID_VALUE_ID, 4239, 4240);
  g->QuantizeTensor(4240, 5190, 4235, 2738);
  g->Dequantize(2738, 2739, 0.09891732782125473, 0);
  g->SplitDim(2739, 2740, 2, {2,512});
  g->Transpose(2740, 2741, {0,2,1,3});
  g->Unary(ynn_unary_square, 2741, 2742);
  g->Reduce(ynn_reduce_sum, 2742, 5107, {3}, true);
  g->ShapeProduct(2742, 5106, {3});
  g->Binary(ynn_binary_divide, 5107, 5106, 2743);
  g->Binary(ynn_binary_add, 2743, 5241, 2744);
  g->Unary(ynn_unary_rsqrt, 2744, 2745);
  g->Binary(ynn_binary_multiply, 2741, 2745, 2746);
}

// Scope: "Layer5 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(2736, 2747, 0.001090860809199512, 0);
  g->Append(5210, 2747, 5732, 2, s2, s1);
  g->View(5732, 5779, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(2746, 2749, 0.01785714365541935, 0);
  g->Append(5234, 2749, 5756, 2, s2, s1);
  g->View(5756, 5802, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer5 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(5617, 4248, {1,0});
  g->Binary(ynn_binary_multiply, 4234, 4247, 4244);
  g->Dot(2718, 4248, YNN_INVALID_VALUE_ID, 4243, 1);
  g->DequantizeTensor(4243, YNN_INVALID_VALUE_ID, 4244, 4245);
  g->QuantizeTensor(4245, 5190, 4246, 2750);
  g->Dequantize(2750, 2751, 0.1092519760131836, 0);
  g->SplitDim(2751, 2752, 2, {8,512});
  g->Transpose(2752, 2753, {0,2,1,3});
  g->Unary(ynn_unary_square, 2753, 2755);
  g->Reduce(ynn_reduce_sum, 2755, 5109, {3}, true);
  g->ShapeProduct(2755, 5108, {3});
  g->Binary(ynn_binary_divide, 5109, 5108, 2756);
  g->Binary(ynn_binary_add, 2756, 5241, 2757);
  g->Unary(ynn_unary_rsqrt, 2757, 2758);
  g->Binary(ynn_binary_multiply, 2753, 2758, 2759);
  g->Binary(ynn_binary_multiply, 2759, 5616, 2760);
  g->Slice(2760, 2761, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(2760, 2762, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 2762, 2763);
  g->Concat({2763,2761}, 2764, 3);
  g->Binary(ynn_binary_multiply, 2760, 2909, 2766);
  g->Binary(ynn_binary_multiply, 2764, 2, 2767);
  g->Binary(ynn_binary_add, 2766, 2767, 2768);
}

// Scope: "Layer5 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(5779, 2769, 0.001090860809199512, 0);
  g->Dequantize(5802, 2770, 0.01785714365541935, 0);
  g->Slice(2768, 2771, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(2769, 2772, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(2770, 2773, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(2771, 2772, 2774, false, true);
  g->Mask(2774, 5282, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 5282, 5113, {-1}, true);
  g->Binary(ynn_binary_subtract, 5282, 5113, 5110);
  g->Unary(ynn_unary_exp, 5110, 5111);
  g->Reduce(ynn_reduce_sum, 5111, 5114, {-1}, true);
  g->Binary(ynn_binary_divide, 4364, 5114, 5112);
  g->Binary(ynn_binary_multiply, 5111, 5112, 2776);
  g->Matmul(2776, 2773, 2777, false, false);
  g->Slice(2768, 2778, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(2769, 2779, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(2770, 2780, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(2778, 2779, 2781, false, true);
  g->Mask(2781, 5283, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 5283, 5118, {-1}, true);
  g->Binary(ynn_binary_subtract, 5283, 5118, 5115);
  g->Unary(ynn_unary_exp, 5115, 5116);
  g->Reduce(ynn_reduce_sum, 5116, 5119, {-1}, true);
  g->Binary(ynn_binary_divide, 4364, 5119, 5117);
  g->Binary(ynn_binary_multiply, 5116, 5117, 2782);
  g->Matmul(2782, 2780, 2783, false, false);
  g->Concat({2777,2783}, 2784, 1);
}

// Scope: "Layer5 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(2784, 2786, {0,2,1,3});
  g->FuseDims(2786, 2787, 2, 2);
  g->Quantize(2787, 2788, 0.017839577049016953, 0);
  g->Transpose(5615, 4255, {1,0});
  g->Binary(ynn_binary_multiply, 4252, 4254, 4250);
  g->Dot(2788, 4255, YNN_INVALID_VALUE_ID, 4249, 1);
  g->DequantizeTensor(4249, YNN_INVALID_VALUE_ID, 4250, 4251);
  g->QuantizeTensor(4251, 5190, 4253, 2789);
  g->Dequantize(2789, 2790, 0.14457935094833374, 0);
}

// Scope: "Layer5 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2710, 2711);
  g->Reduce(ynn_reduce_sum, 2711, 5103, {2}, true);
  g->ShapeProduct(2711, 5102, {2});
  g->Binary(ynn_binary_divide, 5103, 5102, 2712);
  g->Binary(ynn_binary_add, 2712, 5241, 2713);
  g->Unary(ynn_unary_rsqrt, 2713, 2714);
  g->Binary(ynn_binary_multiply, 2710, 2714, 2715);
  g->Binary(ynn_binary_multiply, 2715, 5602, 2717);
  BuildLayer5AttentionKvProjection(ctx);
  BuildLayer5AttentionCacheUpdate(ctx);
  BuildLayer5AttentionQueryProjection(ctx);
  BuildLayer5AttentionSdpa(ctx);
  BuildLayer5AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2790, 2791);
  g->Reduce(ynn_reduce_sum, 2791, 5121, {2}, true);
  g->ShapeProduct(2791, 5120, {2});
  g->Binary(ynn_binary_divide, 5121, 5120, 2792);
  g->Binary(ynn_binary_add, 2792, 5241, 2793);
  g->Unary(ynn_unary_rsqrt, 2793, 2794);
  g->Binary(ynn_binary_multiply, 2790, 2794, 2795);
  g->Binary(ynn_binary_multiply, 2795, 5609, 2796);
  g->Binary(ynn_binary_add, 2796, 2710, 2797);
}

// Scope: "Layer5 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2797, 2798);
  g->Reduce(ynn_reduce_sum, 2798, 5123, {2}, true);
  g->ShapeProduct(2798, 5122, {2});
  g->Binary(ynn_binary_divide, 5123, 5122, 2799);
  g->Binary(ynn_binary_add, 2799, 5241, 2800);
  g->Unary(ynn_unary_rsqrt, 2800, 2801);
  g->Binary(ynn_binary_multiply, 2797, 2801, 2802);
  g->Binary(ynn_binary_multiply, 2802, 5612, 2803);
  g->Quantize(2803, 2804, 0.3053959310054779, 0);
  g->Transpose(5606, 4262, {1,0});
  g->Binary(ynn_binary_multiply, 4259, 4261, 4257);
  g->Dot(2804, 4262, YNN_INVALID_VALUE_ID, 4256, 1);
  g->DequantizeTensor(4256, YNN_INVALID_VALUE_ID, 4257, 4258);
  g->QuantizeTensor(4258, 5190, 4260, 2805);
  g->Dequantize(2805, 2808, 0.16633859276771545, 0);
  g->Transpose(5605, 4267, {1,0});
  g->Binary(ynn_binary_multiply, 4259, 4266, 4264);
  g->Dot(2804, 4267, YNN_INVALID_VALUE_ID, 4263, 1);
  g->DequantizeTensor(4263, YNN_INVALID_VALUE_ID, 4264, 4265);
  g->QuantizeTensor(4265, 5190, 4260, 2809);
  g->Dequantize(2809, 2810, 0.16633859276771545, 0);
  g->Polynomial(2810, 5131, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5131, 5132);
  g->Binary(ynn_binary_add, 5132, 4364, 5129);
  g->Binary(ynn_binary_multiply, 2810, 4376, 5130);
  g->Binary(ynn_binary_multiply, 5130, 5129, 2811);
  g->Binary(ynn_binary_multiply, 2808, 2811, 2812);
  g->Quantize(2812, 2813, 1.5511810779571533, 0);
  g->Transpose(5604, 4274, {1,0});
  g->Binary(ynn_binary_multiply, 4271, 4273, 4269);
  g->Dot(2813, 4274, YNN_INVALID_VALUE_ID, 4268, 1);
  g->DequantizeTensor(4268, YNN_INVALID_VALUE_ID, 4269, 4270);
  g->QuantizeTensor(4270, 5190, 4272, 2814);
  g->Dequantize(2814, 2815, 0.3160533308982849, 0);
  g->Unary(ynn_unary_square, 2815, 2816);
  g->Reduce(ynn_reduce_sum, 2816, 5134, {2}, true);
  g->ShapeProduct(2816, 5133, {2});
  g->Binary(ynn_binary_divide, 5134, 5133, 2818);
  g->Binary(ynn_binary_add, 2818, 5241, 2819);
  g->Unary(ynn_unary_rsqrt, 2819, 2820);
  g->Binary(ynn_binary_multiply, 2815, 2820, 2821);
  g->Binary(ynn_binary_multiply, 2821, 5610, 2822);
  g->Binary(ynn_binary_add, 2822, 2797, 2823);
}

// Scope: "Layer5 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 2824, {0,0,5,0}, {-1,-1,1,-1});
  g->Reshape(2824, 2825, {1,0,256});
  g->Unary(ynn_unary_square, 2825, 2826);
  g->Reduce(ynn_reduce_sum, 2826, 5136, {2}, true);
  g->ShapeProduct(2826, 5135, {2});
  g->Binary(ynn_binary_divide, 5136, 5135, 2827);
  g->Binary(ynn_binary_add, 2827, 5241, 2829);
  g->Unary(ynn_unary_rsqrt, 2829, 2830);
  g->Binary(ynn_binary_multiply, 2825, 2830, 2831);
  g->Binary(ynn_binary_multiply, 2831, 5688, 2832);
  g->Binary(ynn_binary_multiply, 5707, 5245, 2833);
  g->Binary(ynn_binary_add, 2832, 2833, 2834);
  g->Binary(ynn_binary_multiply, 2834, 5240, 2835);
  g->Quantize(2823, 2836, 0.33932316303253174, 0);
  g->Transpose(5607, 4280, {1,0});
  g->Binary(ynn_binary_multiply, 4278, 4279, 4276);
  g->Dot(2836, 4280, YNN_INVALID_VALUE_ID, 4275, 1);
  g->DequantizeTensor(4275, YNN_INVALID_VALUE_ID, 4276, 4277);
  g->QuantizeTensor(4277, 5190, 3376, 2837);
  g->Dequantize(2837, 2838, 0.05216536670923233, 0);
  g->Polynomial(2838, 5139, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5139, 5140);
  g->Binary(ynn_binary_add, 5140, 4364, 5137);
  g->Binary(ynn_binary_multiply, 2838, 4376, 5138);
  g->Binary(ynn_binary_multiply, 5138, 5137, 2840);
  g->Binary(ynn_binary_multiply, 2840, 2835, 2841);
  g->Quantize(2841, 2842, 0.25, 0);
  g->Transpose(5608, 4286, {1,0});
  g->Binary(ynn_binary_multiply, 3477, 4285, 4282);
  g->Dot(2842, 4286, YNN_INVALID_VALUE_ID, 4281, 1);
  g->DequantizeTensor(4281, YNN_INVALID_VALUE_ID, 4282, 4283);
  g->QuantizeTensor(4283, 5190, 4284, 2843);
  g->Dequantize(2843, 2844, 0.13969317078590393, 0);
  g->Unary(ynn_unary_square, 2844, 2845);
  g->Reduce(ynn_reduce_sum, 2845, 5142, {2}, true);
  g->ShapeProduct(2845, 5141, {2});
  g->Binary(ynn_binary_divide, 5142, 5141, 2846);
  g->Binary(ynn_binary_add, 2846, 5241, 2847);
  g->Unary(ynn_unary_rsqrt, 2847, 2848);
  g->Binary(ynn_binary_multiply, 2844, 2848, 2849);
  g->Binary(ynn_binary_multiply, 2849, 5611, 2851);
  g->Binary(ynn_binary_add, 2823, 2851, 2852);
  g->Binary(ynn_binary_multiply, 2852, 5603, 2853);
}

// Scope: "Layer5"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5(Context& ctx) {
  BuildLayer5Attention(ctx);
  BuildLayer5Mlp(ctx);
  BuildLayer5PerLayerEmbedding(ctx);
}

// Scope: "Layer6 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(2859, 2860, 0.0976727083325386, 0);
  g->Transpose(5631, 4292, {1,0});
  g->Binary(ynn_binary_multiply, 4290, 4291, 4288);
  g->Dot(2860, 4292, YNN_INVALID_VALUE_ID, 4287, 1);
  g->DequantizeTensor(4287, YNN_INVALID_VALUE_ID, 4288, 4289);
  g->QuantizeTensor(4289, 5190, 3599, 2862);
  g->Dequantize(2862, 2863, 0.16535434126853943, 0);
  g->SplitDim(2863, 2864, 2, {2,256});
  g->Transpose(2864, 2865, {0,2,1,3});
  g->Unary(ynn_unary_square, 2865, 2866);
  g->Reduce(ynn_reduce_sum, 2866, 5146, {3}, true);
  g->ShapeProduct(2866, 5145, {3});
  g->Binary(ynn_binary_divide, 5146, 5145, 2867);
  g->Binary(ynn_binary_add, 2867, 5241, 2868);
  g->Unary(ynn_unary_rsqrt, 2868, 2869);
  g->Binary(ynn_binary_multiply, 2865, 2869, 2870);
  g->Binary(ynn_binary_multiply, 2870, 5630, 2871);
  g->Slice(2871, 2872, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2871, 2873, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2873, 2874);
  g->Concat({2874,2872}, 2875, 3);
  g->Binary(ynn_binary_multiply, 2871, 2394, 2876);
  g->Binary(ynn_binary_multiply, 2875, 2498, 2877);
  g->Binary(ynn_binary_add, 2876, 2877, 2878);
  g->Transpose(5635, 4297, {1,0});
  g->Binary(ynn_binary_multiply, 4290, 4296, 4294);
  g->Dot(2860, 4297, YNN_INVALID_VALUE_ID, 4293, 1);
  g->DequantizeTensor(4293, YNN_INVALID_VALUE_ID, 4294, 4295);
  g->QuantizeTensor(4295, 5190, 3599, 2879);
  g->Dequantize(2879, 2880, 0.16535434126853943, 0);
  g->SplitDim(2880, 2882, 2, {2,256});
  g->Transpose(2882, 2883, {0,2,1,3});
  g->Unary(ynn_unary_square, 2883, 2884);
  g->Reduce(ynn_reduce_sum, 2884, 5153, {3}, true);
  g->ShapeProduct(2884, 5152, {3});
  g->Binary(ynn_binary_divide, 5153, 5152, 2885);
  g->Binary(ynn_binary_add, 2885, 5241, 2886);
  g->Unary(ynn_unary_rsqrt, 2886, 2887);
  g->Binary(ynn_binary_multiply, 2883, 2887, 2888);
}

// Scope: "Layer6 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(2878, 2889, 0.005761673673987389, 0);
  g->Append(5211, 2889, 5733, 2, s2, s1);
  g->View(5733, 5780, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(2888, 2891, 0.047244105488061905, 0);
  g->Append(5235, 2891, 5757, 2, s2, s1);
  g->View(5757, 5803, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer6 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(5634, 4302, {1,0});
  g->Binary(ynn_binary_multiply, 4290, 4301, 4299);
  g->Dot(2860, 4302, YNN_INVALID_VALUE_ID, 4298, 1);
  g->DequantizeTensor(4298, YNN_INVALID_VALUE_ID, 4299, 4300);
  g->QuantizeTensor(4300, 5190, 4260, 2892);
  g->Dequantize(2892, 2893, 0.16633859276771545, 0);
  g->SplitDim(2893, 2894, 2, {8,256});
  g->Transpose(2894, 2895, {0,2,1,3});
  g->Unary(ynn_unary_square, 2895, 2896);
  g->Reduce(ynn_reduce_sum, 2896, 5155, {3}, true);
  g->ShapeProduct(2896, 5154, {3});
  g->Binary(ynn_binary_divide, 5155, 5154, 2897);
  g->Binary(ynn_binary_add, 2897, 5241, 2899);
  g->Unary(ynn_unary_rsqrt, 2899, 2900);
  g->Binary(ynn_binary_multiply, 2895, 2900, 2901);
  g->Binary(ynn_binary_multiply, 2901, 5633, 2902);
  g->Slice(2902, 2903, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2902, 2904, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2904, 2905);
  g->Concat({2905,2903}, 2906, 3);
  g->Binary(ynn_binary_multiply, 2902, 2394, 2907);
  g->Binary(ynn_binary_multiply, 2906, 2498, 2908);
  g->Binary(ynn_binary_add, 2907, 2908, 2911);
}

// Scope: "Layer6 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(5780, 2912, 0.005761673673987389, 0);
  g->Dequantize(5803, 2913, 0.047244105488061905, 0);
  g->Slice(2911, 2914, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(2912, 2915, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(2913, 2916, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(2914, 2915, 2917, false, true);
  g->Mask(2917, 5284, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 5284, 5159, {-1}, true);
  g->Binary(ynn_binary_subtract, 5284, 5159, 5156);
  g->Unary(ynn_unary_exp, 5156, 5157);
  g->Reduce(ynn_reduce_sum, 5157, 5160, {-1}, true);
  g->Binary(ynn_binary_divide, 4364, 5160, 5158);
  g->Binary(ynn_binary_multiply, 5157, 5158, 2918);
  g->Matmul(2918, 2916, 2919, false, false);
  g->Slice(2911, 2921, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(2912, 2922, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(2913, 2923, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(2921, 2922, 2924, false, true);
  g->Mask(2924, 5285, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 5285, 5164, {-1}, true);
  g->Binary(ynn_binary_subtract, 5285, 5164, 5161);
  g->Unary(ynn_unary_exp, 5161, 5162);
  g->Reduce(ynn_reduce_sum, 5162, 5165, {-1}, true);
  g->Binary(ynn_binary_divide, 4364, 5165, 5163);
  g->Binary(ynn_binary_multiply, 5162, 5163, 2925);
  g->Matmul(2925, 2923, 2926, false, false);
  g->Concat({2919,2926}, 2927, 1);
}

// Scope: "Layer6 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(2927, 2928, {0,2,1,3});
  g->FuseDims(2928, 2929, 2, 2);
  g->Quantize(2929, 2931, 0.02706693857908249, 0);
  g->Transpose(5632, 4308, {1,0});
  g->Binary(ynn_binary_multiply, 3551, 4307, 4304);
  g->Dot(2931, 4308, YNN_INVALID_VALUE_ID, 4303, 1);
  g->DequantizeTensor(4303, YNN_INVALID_VALUE_ID, 4304, 4305);
  g->QuantizeTensor(4305, 5190, 4306, 2932);
  g->Dequantize(2932, 2933, 0.19767579436302185, 0);
}

// Scope: "Layer6 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2853, 2854);
  g->Reduce(ynn_reduce_sum, 2854, 5144, {2}, true);
  g->ShapeProduct(2854, 5143, {2});
  g->Binary(ynn_binary_divide, 5144, 5143, 2855);
  g->Binary(ynn_binary_add, 2855, 5241, 2856);
  g->Unary(ynn_unary_rsqrt, 2856, 2857);
  g->Binary(ynn_binary_multiply, 2853, 2857, 2858);
  g->Binary(ynn_binary_multiply, 2858, 5619, 2859);
  BuildLayer6AttentionKvProjection(ctx);
  BuildLayer6AttentionCacheUpdate(ctx);
  BuildLayer6AttentionQueryProjection(ctx);
  BuildLayer6AttentionSdpa(ctx);
  BuildLayer6AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2933, 2934);
  g->Reduce(ynn_reduce_sum, 2934, 5167, {2}, true);
  g->ShapeProduct(2934, 5166, {2});
  g->Binary(ynn_binary_divide, 5167, 5166, 2935);
  g->Binary(ynn_binary_add, 2935, 5241, 2936);
  g->Unary(ynn_unary_rsqrt, 2936, 2937);
  g->Binary(ynn_binary_multiply, 2933, 2937, 2938);
  g->Binary(ynn_binary_multiply, 2938, 5626, 2939);
  g->Binary(ynn_binary_add, 2939, 2853, 2940);
}

// Scope: "Layer6 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2940, 2942);
  g->Reduce(ynn_reduce_sum, 2942, 5169, {2}, true);
  g->ShapeProduct(2942, 5168, {2});
  g->Binary(ynn_binary_divide, 5169, 5168, 2943);
  g->Binary(ynn_binary_add, 2943, 5241, 2944);
  g->Unary(ynn_unary_rsqrt, 2944, 2945);
  g->Binary(ynn_binary_multiply, 2940, 2945, 2946);
  g->Binary(ynn_binary_multiply, 2946, 5629, 2947);
  g->Quantize(2947, 2948, 0.06627800315618515, 0);
  g->Transpose(5623, 4322, {1,0});
  g->Binary(ynn_binary_multiply, 4319, 4321, 4317);
  g->Dot(2948, 4322, YNN_INVALID_VALUE_ID, 4316, 1);
  g->DequantizeTensor(4316, YNN_INVALID_VALUE_ID, 4317, 4318);
  g->QuantizeTensor(4318, 5190, 4320, 2949);
  g->Dequantize(2949, 2950, 0.1171259880065918, 0);
  g->Transpose(5622, 4327, {1,0});
  g->Binary(ynn_binary_multiply, 4319, 4326, 4324);
  g->Dot(2948, 4327, YNN_INVALID_VALUE_ID, 4323, 1);
  g->DequantizeTensor(4323, YNN_INVALID_VALUE_ID, 4324, 4325);
  g->QuantizeTensor(4325, 5190, 4320, 2952);
  g->Dequantize(2952, 2953, 0.1171259880065918, 0);
  g->Polynomial(2953, 5172, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5172, 5173);
  g->Binary(ynn_binary_add, 5173, 4364, 5170);
  g->Binary(ynn_binary_multiply, 2953, 4376, 5171);
  g->Binary(ynn_binary_multiply, 5171, 5170, 2954);
  g->Binary(ynn_binary_multiply, 2950, 2954, 2955);
  g->Quantize(2955, 2956, 0.4488188922405243, 0);
  g->Transpose(5621, 4334, {1,0});
  g->Binary(ynn_binary_multiply, 4331, 4333, 4329);
  g->Dot(2956, 4334, YNN_INVALID_VALUE_ID, 4328, 1);
  g->DequantizeTensor(4328, YNN_INVALID_VALUE_ID, 4329, 4330);
  g->QuantizeTensor(4330, 5190, 4332, 2957);
  g->Dequantize(2957, 2958, 0.19675913453102112, 0);
  g->Unary(ynn_unary_square, 2958, 2959);
  g->Reduce(ynn_reduce_sum, 2959, 5175, {2}, true);
  g->ShapeProduct(2959, 5174, {2});
  g->Binary(ynn_binary_divide, 5175, 5174, 2960);
  g->Binary(ynn_binary_add, 2960, 5241, 2961);
  g->Unary(ynn_unary_rsqrt, 2961, 2963);
  g->Binary(ynn_binary_multiply, 2958, 2963, 2964);
  g->Binary(ynn_binary_multiply, 2964, 5627, 2965);
  g->Binary(ynn_binary_add, 2965, 2940, 2966);
}

// Scope: "Layer6 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 2967, {0,0,6,0}, {-1,-1,1,-1});
  g->Reshape(2967, 2968, {1,0,256});
  g->Unary(ynn_unary_square, 2968, 2969);
  g->Reduce(ynn_reduce_sum, 2969, 5177, {2}, true);
  g->ShapeProduct(2969, 5176, {2});
  g->Binary(ynn_binary_divide, 5177, 5176, 2970);
  g->Binary(ynn_binary_add, 2970, 5241, 2971);
  g->Unary(ynn_unary_rsqrt, 2971, 2972);
  g->Binary(ynn_binary_multiply, 2968, 2972, 2974);
  g->Binary(ynn_binary_multiply, 2974, 5688, 2975);
  g->Binary(ynn_binary_multiply, 5708, 5245, 2976);
  g->Binary(ynn_binary_add, 2975, 2976, 2977);
  g->Binary(ynn_binary_multiply, 2977, 5240, 2978);
  g->Quantize(2966, 2979, 0.5854530930519104, 0);
  g->Transpose(5624, 4341, {1,0});
  g->Binary(ynn_binary_multiply, 4338, 4340, 4336);
  g->Dot(2979, 4341, YNN_INVALID_VALUE_ID, 4335, 1);
  g->DequantizeTensor(4335, YNN_INVALID_VALUE_ID, 4336, 4337);
  g->QuantizeTensor(4337, 5190, 4339, 2980);
  g->Dequantize(2980, 2981, 0.0433070994913578, 0);
  g->Polynomial(2981, 5182, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 5182, 5183);
  g->Binary(ynn_binary_add, 5183, 4364, 5180);
  g->Binary(ynn_binary_multiply, 2981, 4376, 5181);
  g->Binary(ynn_binary_multiply, 5181, 5180, 2982);
  g->Binary(ynn_binary_multiply, 2982, 2978, 2983);
  g->Quantize(2983, 2985, 0.25590550899505615, 0);
  g->Transpose(5625, 4348, {1,0});
  g->Binary(ynn_binary_multiply, 4345, 4347, 4343);
  g->Dot(2985, 4348, YNN_INVALID_VALUE_ID, 4342, 1);
  g->DequantizeTensor(4342, YNN_INVALID_VALUE_ID, 4343, 4344);
  g->QuantizeTensor(4344, 5190, 4346, 2986);
  g->Dequantize(2986, 2987, 0.08977121859788895, 0);
  g->Unary(ynn_unary_square, 2987, 2988);
  g->Reduce(ynn_reduce_sum, 2988, 5185, {2}, true);
  g->ShapeProduct(2988, 5184, {2});
  g->Binary(ynn_binary_divide, 5185, 5184, 2989);
  g->Binary(ynn_binary_add, 2989, 5241, 2990);
  g->Unary(ynn_unary_rsqrt, 2990, 2991);
  g->Binary(ynn_binary_multiply, 2987, 2991, 2992);
  g->Binary(ynn_binary_multiply, 2992, 5628, 2993);
  g->Binary(ynn_binary_add, 2966, 2993, 2994);
  g->Binary(ynn_binary_multiply, 2994, 5620, 2996);
}

// Scope: "Layer6"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6(Context& ctx) {
  BuildLayer6Attention(ctx);
  BuildLayer6Mlp(ctx);
  BuildLayer6PerLayerEmbedding(ctx);
}

// Scope: "Layer7 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(3002, 3003, 0.17314177751541138, 0);
  g->Transpose(5648, 4353, {1,0});
  g->Binary(ynn_binary_multiply, 3020, 4352, 4350);
  g->Dot(3003, 4353, YNN_INVALID_VALUE_ID, 4349, 1);
  g->DequantizeTensor(4349, YNN_INVALID_VALUE_ID, 4350, 4351);
  g->QuantizeTensor(4351, 5190, 3021, 3004);
  g->Dequantize(3004, 3005, 0.3011811077594757, 0);
  g->SplitDim(3005, 3007, 2, {2,256});
  g->Transpose(3007, 3008, {0,2,1,3});
  g->Unary(ynn_unary_square, 3008, 3009);
  g->Reduce(ynn_reduce_sum, 3009, 5189, {3}, true);
  g->ShapeProduct(3009, 5188, {3});
  g->Binary(ynn_binary_divide, 5189, 5188, 3010);
  g->Binary(ynn_binary_add, 3010, 5241, 3011);
  g->Unary(ynn_unary_rsqrt, 3011, 3012);
  g->Binary(ynn_binary_multiply, 3008, 3012, 3013);
  g->Binary(ynn_binary_multiply, 3013, 5647, 3014);
  g->Slice(3014, 3015, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3014, 3016, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3016, 4);
  g->Concat({4,3015}, 5, 3);
  g->Binary(ynn_binary_multiply, 3014, 2394, 6);
  g->Binary(ynn_binary_multiply, 5, 2498, 7);
  g->Binary(ynn_binary_add, 6, 7, 8);
  g->Transpose(5652, 3023, {1,0});
  g->Binary(ynn_binary_multiply, 3020, 3022, 3018);
  g->Dot(3003, 3023, YNN_INVALID_VALUE_ID, 3017, 1);
  g->DequantizeTensor(3017, YNN_INVALID_VALUE_ID, 3018, 3019);
  g->QuantizeTensor(3019, 5190, 3021, 9);
  g->Dequantize(9, 10, 0.3011811077594757, 0);
  g->SplitDim(10, 11, 2, {2,256});
  g->Transpose(11, 12, {0,2,1,3});
  g->Unary(ynn_unary_square, 12, 14);
  g->Reduce(ynn_reduce_sum, 14, 4355, {3}, true);
  g->ShapeProduct(14, 4354, {3});
  g->Binary(ynn_binary_divide, 4355, 4354, 15);
  g->Binary(ynn_binary_add, 15, 5241, 16);
  g->Unary(ynn_unary_rsqrt, 16, 17);
  g->Binary(ynn_binary_multiply, 12, 17, 18);
}

// Scope: "Layer7 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(8, 19, 0.006011798977851868, 0);
  g->Append(5212, 19, 5734, 2, s2, s1);
  g->View(5734, 5781, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(18, 20, 0.047244105488061905, 0);
  g->Append(5236, 20, 5758, 2, s2, s1);
  g->View(5758, 5804, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer7 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(5651, 3029, {1,0});
  g->Binary(ynn_binary_multiply, 3020, 3028, 3025);
  g->Dot(3003, 3029, YNN_INVALID_VALUE_ID, 3024, 1);
  g->DequantizeTensor(3024, YNN_INVALID_VALUE_ID, 3025, 3026);
  g->QuantizeTensor(3026, 5190, 3027, 22);
  g->Dequantize(22, 23, 0.31889763474464417, 0);
  g->SplitDim(23, 24, 2, {8,256});
  g->Transpose(24, 25, {0,2,1,3});
  g->Unary(ynn_unary_square, 25, 26);
  g->Reduce(ynn_reduce_sum, 26, 4357, {3}, true);
  g->ShapeProduct(26, 4356, {3});
  g->Binary(ynn_binary_divide, 4357, 4356, 27);
  g->Binary(ynn_binary_add, 27, 5241, 28);
  g->Unary(ynn_unary_rsqrt, 28, 29);
  g->Binary(ynn_binary_multiply, 25, 29, 31);
  g->Binary(ynn_binary_multiply, 31, 5650, 32);
  g->Slice(32, 33, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(32, 34, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 34, 35);
  g->Concat({35,33}, 36, 3);
  g->Binary(ynn_binary_multiply, 32, 2394, 37);
  g->Binary(ynn_binary_multiply, 36, 2498, 38);
  g->Binary(ynn_binary_add, 37, 38, 39);
}

// Scope: "Layer7 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(5781, 40, 0.006011798977851868, 0);
  g->Dequantize(5804, 42, 0.047244105488061905, 0);
  g->Slice(39, 43, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(40, 44, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(42, 45, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(43, 44, 46, false, true);
  g->Mask(46, 5286, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 5286, 4363, {-1}, true);
  g->Binary(ynn_binary_subtract, 5286, 4363, 4360);
  g->Unary(ynn_unary_exp, 4360, 4361);
  g->Reduce(ynn_reduce_sum, 4361, 4365, {-1}, true);
  g->Binary(ynn_binary_divide, 4364, 4365, 4362);
  g->Binary(ynn_binary_multiply, 4361, 4362, 47);
  g->Matmul(47, 45, 48, false, false);
  g->Slice(39, 49, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(40, 50, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(42, 52, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(49, 50, 53, false, true);
  g->Mask(53, 5287, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 5287, 4369, {-1}, true);
  g->Binary(ynn_binary_subtract, 5287, 4369, 4366);
  g->Unary(ynn_unary_exp, 4366, 4367);
  g->Reduce(ynn_reduce_sum, 4367, 4370, {-1}, true);
  g->Binary(ynn_binary_divide, 4364, 4370, 4368);
  g->Binary(ynn_binary_multiply, 4367, 4368, 54);
  g->Matmul(54, 52, 55, false, false);
  g->Concat({48,55}, 56, 1);
}

// Scope: "Layer7 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(56, 57, {0,2,1,3});
  g->FuseDims(57, 58, 2, 2);
  g->Quantize(58, 59, 0.02239174209535122, 0);
  g->Transpose(5649, 3036, {1,0});
  g->Binary(ynn_binary_multiply, 3033, 3035, 3031);
  g->Dot(59, 3036, YNN_INVALID_VALUE_ID, 3030, 1);
  g->DequantizeTensor(3030, YNN_INVALID_VALUE_ID, 3031, 3032);
  g->QuantizeTensor(3032, 5190, 3034, 60);
  g->Dequantize(60, 62, 0.07983598113059998, 0);
}

// Scope: "Layer7 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2996, 2997);
  g->Reduce(ynn_reduce_sum, 2997, 5187, {2}, true);
  g->ShapeProduct(2997, 5186, {2});
  g->Binary(ynn_binary_divide, 5187, 5186, 2998);
  g->Binary(ynn_binary_add, 2998, 5241, 2999);
  g->Unary(ynn_unary_rsqrt, 2999, 3000);
  g->Binary(ynn_binary_multiply, 2996, 3000, 3001);
  g->Binary(ynn_binary_multiply, 3001, 5636, 3002);
  BuildLayer7AttentionKvProjection(ctx);
  BuildLayer7AttentionCacheUpdate(ctx);
  BuildLayer7AttentionQueryProjection(ctx);
  BuildLayer7AttentionSdpa(ctx);
  BuildLayer7AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 62, 63);
  g->Reduce(ynn_reduce_sum, 63, 4372, {2}, true);
  g->ShapeProduct(63, 4371, {2});
  g->Binary(ynn_binary_divide, 4372, 4371, 64);
  g->Binary(ynn_binary_add, 64, 5241, 65);
  g->Unary(ynn_unary_rsqrt, 65, 66);
  g->Binary(ynn_binary_multiply, 62, 66, 67);
  g->Binary(ynn_binary_multiply, 67, 5643, 68);
  g->Binary(ynn_binary_add, 68, 2996, 69);
}

// Scope: "Layer7 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 69, 70);
  g->Reduce(ynn_reduce_sum, 70, 4374, {2}, true);
  g->ShapeProduct(70, 4373, {2});
  g->Binary(ynn_binary_divide, 4374, 4373, 71);
  g->Binary(ynn_binary_add, 71, 5241, 73);
  g->Unary(ynn_unary_rsqrt, 73, 74);
  g->Binary(ynn_binary_multiply, 69, 74, 75);
  g->Binary(ynn_binary_multiply, 75, 5646, 76);
  g->Quantize(76, 77, 0.04099859297275543, 0);
  g->Transpose(5640, 3043, {1,0});
  g->Binary(ynn_binary_multiply, 3040, 3042, 3038);
  g->Dot(77, 3043, YNN_INVALID_VALUE_ID, 3037, 1);
  g->DequantizeTensor(3037, YNN_INVALID_VALUE_ID, 3038, 3039);
  g->QuantizeTensor(3039, 5190, 3041, 78);
  g->Dequantize(78, 79, 0.0625000074505806, 0);
  g->Transpose(5639, 3048, {1,0});
  g->Binary(ynn_binary_multiply, 3040, 3047, 3045);
  g->Dot(77, 3048, YNN_INVALID_VALUE_ID, 3044, 1);
  g->DequantizeTensor(3044, YNN_INVALID_VALUE_ID, 3045, 3046);
  g->QuantizeTensor(3046, 5190, 3041, 80);
  g->Dequantize(80, 81, 0.0625000074505806, 0);
  g->Polynomial(81, 4378, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 4378, 4379);
  g->Binary(ynn_binary_add, 4379, 4364, 4375);
  g->Binary(ynn_binary_multiply, 81, 4376, 4377);
  g->Binary(ynn_binary_multiply, 4377, 4375, 83);
  g->Binary(ynn_binary_multiply, 79, 83, 84);
  g->Quantize(84, 85, 0.18503938615322113, 0);
  g->Transpose(5638, 3055, {1,0});
  g->Binary(ynn_binary_multiply, 3052, 3054, 3050);
  g->Dot(85, 3055, YNN_INVALID_VALUE_ID, 3049, 1);
  g->DequantizeTensor(3049, YNN_INVALID_VALUE_ID, 3050, 3051);
  g->QuantizeTensor(3051, 5190, 3053, 86);
  g->Dequantize(86, 87, 0.08599609136581421, 0);
  g->Unary(ynn_unary_square, 87, 88);
  g->Reduce(ynn_reduce_sum, 88, 4381, {2}, true);
  g->ShapeProduct(88, 4380, {2});
  g->Binary(ynn_binary_divide, 4381, 4380, 89);
  g->Binary(ynn_binary_add, 89, 5241, 90);
  g->Unary(ynn_unary_rsqrt, 90, 91);
  g->Binary(ynn_binary_multiply, 87, 91, 92);
  g->Binary(ynn_binary_multiply, 92, 5644, 94);
  g->Binary(ynn_binary_add, 94, 69, 95);
}

// Scope: "Layer7 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 96, {0,0,7,0}, {-1,-1,1,-1});
  g->Reshape(96, 97, {1,0,256});
  g->Unary(ynn_unary_square, 97, 98);
  g->Reduce(ynn_reduce_sum, 98, 4383, {2}, true);
  g->ShapeProduct(98, 4382, {2});
  g->Binary(ynn_binary_divide, 4383, 4382, 99);
  g->Binary(ynn_binary_add, 99, 5241, 100);
  g->Unary(ynn_unary_rsqrt, 100, 101);
  g->Binary(ynn_binary_multiply, 97, 101, 102);
  g->Binary(ynn_binary_multiply, 102, 5688, 103);
  g->Binary(ynn_binary_multiply, 5709, 5245, 106);
  g->Binary(ynn_binary_add, 103, 106, 107);
  g->Binary(ynn_binary_multiply, 107, 5240, 108);
  g->Quantize(95, 109, 0.16048018634319305, 0);
  g->Transpose(5641, 3069, {1,0});
  g->Binary(ynn_binary_multiply, 3066, 3068, 3064);
  g->Dot(109, 3069, YNN_INVALID_VALUE_ID, 3063, 1);
  g->DequantizeTensor(3063, YNN_INVALID_VALUE_ID, 3064, 3065);
  g->QuantizeTensor(3065, 5190, 3067, 110);
  g->Dequantize(110, 111, 0.04675197973847389, 0);
  g->Polynomial(111, 4386, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 4386, 4387);
  g->Binary(ynn_binary_add, 4387, 4364, 4384);
  g->Binary(ynn_binary_multiply, 111, 4376, 4385);
  g->Binary(ynn_binary_multiply, 4385, 4384, 112);
  g->Binary(ynn_binary_multiply, 112, 108, 113);
  g->Quantize(113, 114, 0.15748032927513123, 0);
  g->Transpose(5642, 3076, {1,0});
  g->Binary(ynn_binary_multiply, 3073, 3075, 3071);
  g->Dot(114, 3076, YNN_INVALID_VALUE_ID, 3070, 1);
  g->DequantizeTensor(3070, YNN_INVALID_VALUE_ID, 3071, 3072);
  g->QuantizeTensor(3072, 5190, 3074, 115);
  g->Dequantize(115, 116, 0.07159535586833954, 0);
  g->Unary(ynn_unary_square, 116, 117);
  g->Reduce(ynn_reduce_sum, 117, 4389, {2}, true);
  g->ShapeProduct(117, 4388, {2});
  g->Binary(ynn_binary_divide, 4389, 4388, 118);
  g->Binary(ynn_binary_add, 118, 5241, 119);
  g->Unary(ynn_unary_rsqrt, 119, 120);
  g->Binary(ynn_binary_multiply, 116, 120, 121);
  g->Binary(ynn_binary_multiply, 121, 5645, 122);
  g->Binary(ynn_binary_add, 95, 122, 123);
  g->Binary(ynn_binary_multiply, 123, 5637, 124);
}

// Scope: "Layer7"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7(Context& ctx) {
  BuildLayer7Attention(ctx);
  BuildLayer7Mlp(ctx);
  BuildLayer7PerLayerEmbedding(ctx);
}

// Scope: "Layer8 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(131, 132, 0.18602856993675232, 0);
  g->Transpose(5665, 3088, {1,0});
  g->Binary(ynn_binary_multiply, 3085, 3087, 3083);
  g->Dot(132, 3088, YNN_INVALID_VALUE_ID, 3082, 1);
  g->DequantizeTensor(3082, YNN_INVALID_VALUE_ID, 3083, 3084);
  g->QuantizeTensor(3084, 5190, 3086, 133);
  g->Dequantize(133, 134, 0.3366141617298126, 0);
  g->SplitDim(134, 135, 2, {2,256});
  g->Transpose(135, 136, {0,2,1,3});
  g->Unary(ynn_unary_square, 136, 138);
  g->Reduce(ynn_reduce_sum, 138, 4393, {3}, true);
  g->ShapeProduct(138, 4392, {3});
  g->Binary(ynn_binary_divide, 4393, 4392, 139);
  g->Binary(ynn_binary_add, 139, 5241, 140);
  g->Unary(ynn_unary_rsqrt, 140, 141);
  g->Binary(ynn_binary_multiply, 136, 141, 142);
  g->Binary(ynn_binary_multiply, 142, 5664, 143);
  g->Slice(143, 144, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(143, 145, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 145, 146);
  g->Concat({146,144}, 147, 3);
  g->Binary(ynn_binary_multiply, 143, 2394, 149);
  g->Binary(ynn_binary_multiply, 147, 2498, 150);
  g->Binary(ynn_binary_add, 149, 150, 151);
  g->Transpose(5669, 3093, {1,0});
  g->Binary(ynn_binary_multiply, 3085, 3092, 3090);
  g->Dot(132, 3093, YNN_INVALID_VALUE_ID, 3089, 1);
  g->DequantizeTensor(3089, YNN_INVALID_VALUE_ID, 3090, 3091);
  g->QuantizeTensor(3091, 5190, 3086, 152);
  g->Dequantize(152, 153, 0.3366141617298126, 0);
  g->SplitDim(153, 154, 2, {2,256});
  g->Transpose(154, 155, {0,2,1,3});
  g->Unary(ynn_unary_square, 155, 156);
  g->Reduce(ynn_reduce_sum, 156, 4399, {3}, true);
  g->ShapeProduct(156, 4398, {3});
  g->Binary(ynn_binary_divide, 4399, 4398, 157);
  g->Binary(ynn_binary_add, 157, 5241, 159);
  g->Unary(ynn_unary_rsqrt, 159, 160);
  g->Binary(ynn_binary_multiply, 155, 160, 161);
}

// Scope: "Layer8 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(151, 162, 0.005679573863744736, 0);
  g->Append(5213, 162, 5735, 2, s2, s1);
  g->View(5735, 5782, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(161, 163, 0.047244105488061905, 0);
  g->Append(5237, 163, 5759, 2, s2, s1);
  g->View(5759, 5805, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer8 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(5668, 3099, {1,0});
  g->Binary(ynn_binary_multiply, 3085, 3098, 3095);
  g->Dot(132, 3099, YNN_INVALID_VALUE_ID, 3094, 1);
  g->DequantizeTensor(3094, YNN_INVALID_VALUE_ID, 3095, 3096);
  g->QuantizeTensor(3096, 5190, 3097, 165);
  g->Dequantize(165, 166, 0.31102362275123596, 0);
  g->SplitDim(166, 167, 2, {8,256});
  g->Transpose(167, 168, {0,2,1,3});
  g->Unary(ynn_unary_square, 168, 169);
  g->Reduce(ynn_reduce_sum, 169, 4401, {3}, true);
  g->ShapeProduct(169, 4400, {3});
  g->Binary(ynn_binary_divide, 4401, 4400, 170);
  g->Binary(ynn_binary_add, 170, 5241, 171);
  g->Unary(ynn_unary_rsqrt, 171, 172);
  g->Binary(ynn_binary_multiply, 168, 172, 173);
  g->Binary(ynn_binary_multiply, 173, 5667, 174);
  g->Slice(174, 176, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(174, 177, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 177, 178);
  g->Concat({178,176}, 179, 3);
  g->Binary(ynn_binary_multiply, 174, 2394, 180);
  g->Binary(ynn_binary_multiply, 179, 2498, 181);
  g->Binary(ynn_binary_add, 180, 181, 182);
}

// Scope: "Layer8 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(5782, 183, 0.005679573863744736, 0);
  g->Dequantize(5805, 184, 0.047244105488061905, 0);
  g->Slice(182, 185, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(183, 187, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(184, 188, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(185, 187, 189, false, true);
  g->Mask(189, 5288, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 5288, 4405, {-1}, true);
  g->Binary(ynn_binary_subtract, 5288, 4405, 4402);
  g->Unary(ynn_unary_exp, 4402, 4403);
  g->Reduce(ynn_reduce_sum, 4403, 4406, {-1}, true);
  g->Binary(ynn_binary_divide, 4364, 4406, 4404);
  g->Binary(ynn_binary_multiply, 4403, 4404, 190);
  g->Matmul(190, 188, 191, false, false);
  g->Slice(182, 192, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(183, 193, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(184, 194, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(192, 193, 195, false, true);
  g->Mask(195, 5289, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 5289, 4410, {-1}, true);
  g->Binary(ynn_binary_subtract, 5289, 4410, 4407);
  g->Unary(ynn_unary_exp, 4407, 4408);
  g->Reduce(ynn_reduce_sum, 4408, 4411, {-1}, true);
  g->Binary(ynn_binary_divide, 4364, 4411, 4409);
  g->Binary(ynn_binary_multiply, 4408, 4409, 197);
  g->Matmul(197, 194, 198, false, false);
  g->Concat({191,198}, 199, 1);
}

// Scope: "Layer8 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(199, 200, {0,2,1,3});
  g->FuseDims(200, 201, 2, 2);
  g->Quantize(201, 202, 0.023375993594527245, 0);
  g->Transpose(5666, 3113, {1,0});
  g->Binary(ynn_binary_multiply, 3110, 3112, 3108);
  g->Dot(202, 3113, YNN_INVALID_VALUE_ID, 3107, 1);
  g->DequantizeTensor(3107, YNN_INVALID_VALUE_ID, 3108, 3109);
  g->QuantizeTensor(3109, 5190, 3111, 203);
  g->Dequantize(203, 204, 0.04781534895300865, 0);
}

// Scope: "Layer8 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 124, 125);
  g->Reduce(ynn_reduce_sum, 125, 4391, {2}, true);
  g->ShapeProduct(125, 4390, {2});
  g->Binary(ynn_binary_divide, 4391, 4390, 127);
  g->Binary(ynn_binary_add, 127, 5241, 128);
  g->Unary(ynn_unary_rsqrt, 128, 129);
  g->Binary(ynn_binary_multiply, 124, 129, 130);
  g->Binary(ynn_binary_multiply, 130, 5653, 131);
  BuildLayer8AttentionKvProjection(ctx);
  BuildLayer8AttentionCacheUpdate(ctx);
  BuildLayer8AttentionQueryProjection(ctx);
  BuildLayer8AttentionSdpa(ctx);
  BuildLayer8AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 204, 205);
  g->Reduce(ynn_reduce_sum, 205, 4415, {2}, true);
  g->ShapeProduct(205, 4414, {2});
  g->Binary(ynn_binary_divide, 4415, 4414, 208);
  g->Binary(ynn_binary_add, 208, 5241, 209);
  g->Unary(ynn_unary_rsqrt, 209, 210);
  g->Binary(ynn_binary_multiply, 204, 210, 211);
  g->Binary(ynn_binary_multiply, 211, 5660, 212);
  g->Binary(ynn_binary_add, 212, 124, 213);
}

// Scope: "Layer8 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 213, 214);
  g->Reduce(ynn_reduce_sum, 214, 4417, {2}, true);
  g->ShapeProduct(214, 4416, {2});
  g->Binary(ynn_binary_divide, 4417, 4416, 215);
  g->Binary(ynn_binary_add, 215, 5241, 216);
  g->Unary(ynn_unary_rsqrt, 216, 217);
  g->Binary(ynn_binary_multiply, 213, 217, 219);
  g->Binary(ynn_binary_multiply, 219, 5663, 220);
  g->Quantize(220, 221, 0.028420308604836464, 0);
  g->Transpose(5657, 3127, {1,0});
  g->Binary(ynn_binary_multiply, 3124, 3126, 3122);
  g->Dot(221, 3127, YNN_INVALID_VALUE_ID, 3121, 1);
  g->DequantizeTensor(3121, YNN_INVALID_VALUE_ID, 3122, 3123);
  g->QuantizeTensor(3123, 5190, 3125, 222);
  g->Dequantize(222, 223, 0.04625985398888588, 0);
  g->Transpose(5656, 3132, {1,0});
  g->Binary(ynn_binary_multiply, 3124, 3131, 3129);
  g->Dot(221, 3132, YNN_INVALID_VALUE_ID, 3128, 1);
  g->DequantizeTensor(3128, YNN_INVALID_VALUE_ID, 3129, 3130);
  g->QuantizeTensor(3130, 5190, 3125, 224);
  g->Dequantize(224, 225, 0.04625985398888588, 0);
  g->Polynomial(225, 4420, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 4420, 4421);
  g->Binary(ynn_binary_add, 4421, 4364, 4418);
  g->Binary(ynn_binary_multiply, 225, 4376, 4419);
  g->Binary(ynn_binary_multiply, 4419, 4418, 226);
  g->Binary(ynn_binary_multiply, 223, 226, 227);
  g->Quantize(227, 229, 0.11958662420511246, 0);
  g->Transpose(5655, 3139, {1,0});
  g->Binary(ynn_binary_multiply, 3136, 3138, 3134);
  g->Dot(229, 3139, YNN_INVALID_VALUE_ID, 3133, 1);
  g->DequantizeTensor(3133, YNN_INVALID_VALUE_ID, 3134, 3135);
  g->QuantizeTensor(3135, 5190, 3137, 230);
  g->Dequantize(230, 231, 0.07705982774496078, 0);
  g->Unary(ynn_unary_square, 231, 232);
  g->Reduce(ynn_reduce_sum, 232, 4423, {2}, true);
  g->ShapeProduct(232, 4422, {2});
  g->Binary(ynn_binary_divide, 4423, 4422, 233);
  g->Binary(ynn_binary_add, 233, 5241, 234);
  g->Unary(ynn_unary_rsqrt, 234, 235);
  g->Binary(ynn_binary_multiply, 231, 235, 236);
  g->Binary(ynn_binary_multiply, 236, 5661, 237);
  g->Binary(ynn_binary_add, 237, 213, 238);
}

// Scope: "Layer8 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 240, {0,0,8,0}, {-1,-1,1,-1});
  g->Reshape(240, 241, {1,0,256});
  g->Unary(ynn_unary_square, 241, 242);
  g->Reduce(ynn_reduce_sum, 242, 4425, {2}, true);
  g->ShapeProduct(242, 4424, {2});
  g->Binary(ynn_binary_divide, 4425, 4424, 243);
  g->Binary(ynn_binary_add, 243, 5241, 244);
  g->Unary(ynn_unary_rsqrt, 244, 245);
  g->Binary(ynn_binary_multiply, 241, 245, 246);
  g->Binary(ynn_binary_multiply, 246, 5688, 247);
  g->Binary(ynn_binary_multiply, 5710, 5245, 248);
  g->Binary(ynn_binary_add, 247, 248, 249);
  g->Binary(ynn_binary_multiply, 249, 5240, 251);
  g->Quantize(238, 252, 0.4868268370628357, 0);
  g->Transpose(5658, 3146, {1,0});
  g->Binary(ynn_binary_multiply, 3143, 3145, 3141);
  g->Dot(252, 3146, YNN_INVALID_VALUE_ID, 3140, 1);
  g->DequantizeTensor(3140, YNN_INVALID_VALUE_ID, 3141, 3142);
  g->QuantizeTensor(3142, 5190, 3144, 253);
  g->Dequantize(253, 254, 0.03026575781404972, 0);
  g->Polynomial(254, 4428, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 4428, 4429);
  g->Binary(ynn_binary_add, 4429, 4364, 4426);
  g->Binary(ynn_binary_multiply, 254, 4376, 4427);
  g->Binary(ynn_binary_multiply, 4427, 4426, 255);
  g->Binary(ynn_binary_multiply, 255, 251, 256);
  g->Quantize(256, 257, 0.12795276939868927, 0);
  g->Transpose(5659, 3153, {1,0});
  g->Binary(ynn_binary_multiply, 3150, 3152, 3148);
  g->Dot(257, 3153, YNN_INVALID_VALUE_ID, 3147, 1);
  g->DequantizeTensor(3147, YNN_INVALID_VALUE_ID, 3148, 3149);
  g->QuantizeTensor(3149, 5190, 3151, 258);
  g->Dequantize(258, 259, 0.04510452225804329, 0);
  g->Unary(ynn_unary_square, 259, 260);
  g->Reduce(ynn_reduce_sum, 260, 4431, {2}, true);
  g->ShapeProduct(260, 4430, {2});
  g->Binary(ynn_binary_divide, 4431, 4430, 262);
  g->Binary(ynn_binary_add, 262, 5241, 263);
  g->Unary(ynn_unary_rsqrt, 263, 264);
  g->Binary(ynn_binary_multiply, 259, 264, 265);
  g->Binary(ynn_binary_multiply, 265, 5662, 266);
  g->Binary(ynn_binary_add, 238, 266, 267);
  g->Binary(ynn_binary_multiply, 267, 5654, 268);
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
  g->Quantize(275, 276, 0.06997107714414597, 0);
  g->Transpose(5682, 3160, {1,0});
  g->Binary(ynn_binary_multiply, 3157, 3159, 3155);
  g->Dot(276, 3160, YNN_INVALID_VALUE_ID, 3154, 1);
  g->DequantizeTensor(3154, YNN_INVALID_VALUE_ID, 3155, 3156);
  g->QuantizeTensor(3156, 5190, 3158, 277);
  g->Dequantize(277, 278, 0.11663386225700378, 0);
  g->SplitDim(278, 279, 2, {2,256});
  g->Transpose(279, 280, {0,2,1,3});
  g->Unary(ynn_unary_square, 280, 281);
  g->Reduce(ynn_reduce_sum, 281, 4435, {3}, true);
  g->ShapeProduct(281, 4434, {3});
  g->Binary(ynn_binary_divide, 4435, 4434, 282);
  g->Binary(ynn_binary_add, 282, 5241, 284);
  g->Unary(ynn_unary_rsqrt, 284, 285);
  g->Binary(ynn_binary_multiply, 280, 285, 286);
  g->Binary(ynn_binary_multiply, 286, 5681, 287);
  g->Slice(287, 288, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(287, 289, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 289, 290);
  g->Concat({290,288}, 291, 3);
  g->Binary(ynn_binary_multiply, 287, 2394, 292);
  g->Binary(ynn_binary_multiply, 291, 2498, 293);
  g->Binary(ynn_binary_add, 292, 293, 295);
  g->Transpose(5686, 3165, {1,0});
  g->Binary(ynn_binary_multiply, 3157, 3164, 3162);
  g->Dot(276, 3165, YNN_INVALID_VALUE_ID, 3161, 1);
  g->DequantizeTensor(3161, YNN_INVALID_VALUE_ID, 3162, 3163);
  g->QuantizeTensor(3163, 5190, 3158, 296);
  g->Dequantize(296, 297, 0.11663386225700378, 0);
  g->SplitDim(297, 298, 2, {2,256});
  g->Transpose(298, 299, {0,2,1,3});
  g->Unary(ynn_unary_square, 299, 300);
  g->Reduce(ynn_reduce_sum, 300, 4437, {3}, true);
  g->ShapeProduct(300, 4436, {3});
  g->Binary(ynn_binary_divide, 4437, 4436, 301);
  g->Binary(ynn_binary_add, 301, 5241, 302);
  g->Unary(ynn_unary_rsqrt, 302, 303);
  g->Binary(ynn_binary_multiply, 299, 303, 305);
}

// Scope: "Layer9 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(295, 306, 0.005719248205423355, 0);
  g->Append(5214, 306, 5736, 2, s2, s1);
  g->View(5736, 5783, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(305, 307, 0.047244105488061905, 0);
  g->Append(5238, 307, 5760, 2, s2, s1);
  g->View(5760, 5806, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer9 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(5685, 3171, {1,0});
  g->Binary(ynn_binary_multiply, 3157, 3170, 3167);
  g->Dot(276, 3171, YNN_INVALID_VALUE_ID, 3166, 1);
  g->DequantizeTensor(3166, YNN_INVALID_VALUE_ID, 3167, 3168);
  g->QuantizeTensor(3168, 5190, 3169, 308);
  g->Dequantize(308, 309, 0.1058070957660675, 0);
  g->SplitDim(309, 312, 2, {8,256});
  g->Transpose(312, 313, {0,2,1,3});
  g->Unary(ynn_unary_square, 313, 314);
  g->Reduce(ynn_reduce_sum, 314, 4441, {3}, true);
  g->ShapeProduct(314, 4440, {3});
  g->Binary(ynn_binary_divide, 4441, 4440, 315);
  g->Binary(ynn_binary_add, 315, 5241, 316);
  g->Unary(ynn_unary_rsqrt, 316, 317);
  g->Binary(ynn_binary_multiply, 313, 317, 318);
  g->Binary(ynn_binary_multiply, 318, 5684, 319);
  g->Slice(319, 320, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(319, 321, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 321, 323);
  g->Concat({323,320}, 324, 3);
  g->Binary(ynn_binary_multiply, 319, 2394, 325);
  g->Binary(ynn_binary_multiply, 324, 2498, 326);
  g->Binary(ynn_binary_add, 325, 326, 327);
}

// Scope: "Layer9 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(5783, 328, 0.005719248205423355, 0);
  g->Dequantize(5806, 329, 0.047244105488061905, 0);
  g->Slice(327, 330, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(328, 331, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(329, 332, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(330, 331, 334, false, true);
  g->Mask(334, 5290, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 5290, 4445, {-1}, true);
  g->Binary(ynn_binary_subtract, 5290, 4445, 4442);
  g->Unary(ynn_unary_exp, 4442, 4443);
  g->Reduce(ynn_reduce_sum, 4443, 4446, {-1}, true);
  g->Binary(ynn_binary_divide, 4364, 4446, 4444);
  g->Binary(ynn_binary_multiply, 4443, 4444, 335);
  g->Matmul(335, 332, 336, false, false);
  g->Slice(327, 337, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(328, 338, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(329, 339, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(337, 338, 340, false, true);
  g->Mask(340, 5291, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 5291, 4450, {-1}, true);
  g->Binary(ynn_binary_subtract, 5291, 4450, 4447);
  g->Unary(ynn_unary_exp, 4447, 4448);
  g->Reduce(ynn_reduce_sum, 4448, 4451, {-1}, true);
  g->Binary(ynn_binary_divide, 4364, 4451, 4449);
  g->Binary(ynn_binary_multiply, 4448, 4449, 341);
  g->Matmul(341, 339, 343, false, false);
  g->Concat({336,343}, 344, 1);
}

// Scope: "Layer9 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(344, 345, {0,2,1,3});
  g->FuseDims(345, 346, 2, 2);
  g->Quantize(346, 347, 0.023375993594527245, 0);
  g->Transpose(5683, 3177, {1,0});
  g->Binary(ynn_binary_multiply, 3110, 3176, 3173);
  g->Dot(347, 3177, YNN_INVALID_VALUE_ID, 3172, 1);
  g->DequantizeTensor(3172, YNN_INVALID_VALUE_ID, 3173, 3174);
  g->QuantizeTensor(3174, 5190, 3175, 348);
  g->Dequantize(348, 349, 0.04783705249428749, 0);
}

// Scope: "Layer9 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 268, 269);
  g->Reduce(ynn_reduce_sum, 269, 4433, {2}, true);
  g->ShapeProduct(269, 4432, {2});
  g->Binary(ynn_binary_divide, 4433, 4432, 270);
  g->Binary(ynn_binary_add, 270, 5241, 271);
  g->Unary(ynn_unary_rsqrt, 271, 273);
  g->Binary(ynn_binary_multiply, 268, 273, 274);
  g->Binary(ynn_binary_multiply, 274, 5670, 275);
  BuildLayer9AttentionKvProjection(ctx);
  BuildLayer9AttentionCacheUpdate(ctx);
  BuildLayer9AttentionQueryProjection(ctx);
  BuildLayer9AttentionSdpa(ctx);
  BuildLayer9AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 349, 350);
  g->Reduce(ynn_reduce_sum, 350, 4453, {2}, true);
  g->ShapeProduct(350, 4452, {2});
  g->Binary(ynn_binary_divide, 4453, 4452, 351);
  g->Binary(ynn_binary_add, 351, 5241, 352);
  g->Unary(ynn_unary_rsqrt, 352, 354);
  g->Binary(ynn_binary_multiply, 349, 354, 355);
  g->Binary(ynn_binary_multiply, 355, 5677, 356);
  g->Binary(ynn_binary_add, 356, 268, 357);
}

// Scope: "Layer9 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 357, 358);
  g->Reduce(ynn_reduce_sum, 358, 4455, {2}, true);
  g->ShapeProduct(358, 4454, {2});
  g->Binary(ynn_binary_divide, 4455, 4454, 359);
  g->Binary(ynn_binary_add, 359, 5241, 360);
  g->Unary(ynn_unary_rsqrt, 360, 361);
  g->Binary(ynn_binary_multiply, 357, 361, 362);
  g->Binary(ynn_binary_multiply, 362, 5680, 363);
  g->Quantize(363, 365, 0.017706703394651413, 0);
  g->Transpose(5674, 3184, {1,0});
  g->Binary(ynn_binary_multiply, 3181, 3183, 3179);
  g->Dot(365, 3184, YNN_INVALID_VALUE_ID, 3178, 1);
  g->DequantizeTensor(3178, YNN_INVALID_VALUE_ID, 3179, 3180);
  g->QuantizeTensor(3180, 5190, 3182, 366);
  g->Dequantize(366, 367, 0.025836624205112457, 0);
  g->Transpose(5673, 3189, {1,0});
  g->Binary(ynn_binary_multiply, 3181, 3188, 3186);
  g->Dot(365, 3189, YNN_INVALID_VALUE_ID, 3185, 1);
  g->DequantizeTensor(3185, YNN_INVALID_VALUE_ID, 3186, 3187);
  g->QuantizeTensor(3187, 5190, 3182, 368);
  g->Dequantize(368, 369, 0.025836624205112457, 0);
  g->Polynomial(369, 4458, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 4458, 4459);
  g->Binary(ynn_binary_add, 4459, 4364, 4456);
  g->Binary(ynn_binary_multiply, 369, 4376, 4457);
  g->Binary(ynn_binary_multiply, 4457, 4456, 370);
  g->Binary(ynn_binary_multiply, 367, 370, 371);
  g->Quantize(371, 372, 0.04773623123764992, 0);
  g->Transpose(5672, 3196, {1,0});
  g->Binary(ynn_binary_multiply, 3193, 3195, 3191);
  g->Dot(372, 3196, YNN_INVALID_VALUE_ID, 3190, 1);
  g->DequantizeTensor(3190, YNN_INVALID_VALUE_ID, 3191, 3192);
  g->QuantizeTensor(3192, 5190, 3194, 373);
  g->Dequantize(373, 375, 0.04407493770122528, 0);
  g->Unary(ynn_unary_square, 375, 376);
  g->Reduce(ynn_reduce_sum, 376, 4461, {2}, true);
  g->ShapeProduct(376, 4460, {2});
  g->Binary(ynn_binary_divide, 4461, 4460, 377);
  g->Binary(ynn_binary_add, 377, 5241, 378);
  g->Unary(ynn_unary_rsqrt, 378, 379);
  g->Binary(ynn_binary_multiply, 375, 379, 380);
  g->Binary(ynn_binary_multiply, 380, 5678, 381);
  g->Binary(ynn_binary_add, 381, 357, 382);
}

// Scope: "Layer9 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 383, {0,0,9,0}, {-1,-1,1,-1});
  g->Reshape(383, 384, {1,0,256});
  g->Unary(ynn_unary_square, 384, 386);
  g->Reduce(ynn_reduce_sum, 386, 4463, {2}, true);
  g->ShapeProduct(386, 4462, {2});
  g->Binary(ynn_binary_divide, 4463, 4462, 387);
  g->Binary(ynn_binary_add, 387, 5241, 388);
  g->Unary(ynn_unary_rsqrt, 388, 389);
  g->Binary(ynn_binary_multiply, 384, 389, 390);
  g->Binary(ynn_binary_multiply, 390, 5688, 391);
  g->Binary(ynn_binary_multiply, 5711, 5245, 392);
  g->Binary(ynn_binary_add, 391, 392, 393);
  g->Binary(ynn_binary_multiply, 393, 5240, 394);
  g->Quantize(382, 395, 0.20032060146331787, 0);
  g->Transpose(5675, 3210, {1,0});
  g->Binary(ynn_binary_multiply, 3207, 3209, 3205);
  g->Dot(395, 3210, YNN_INVALID_VALUE_ID, 3204, 1);
  g->DequantizeTensor(3204, YNN_INVALID_VALUE_ID, 3205, 3206);
  g->QuantizeTensor(3206, 5190, 3208, 397);
  g->Dequantize(397, 398, 0.047244105488061905, 0);
  g->Polynomial(398, 4466, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 4466, 4467);
  g->Binary(ynn_binary_add, 4467, 4364, 4464);
  g->Binary(ynn_binary_multiply, 398, 4376, 4465);
  g->Binary(ynn_binary_multiply, 4465, 4464, 399);
  g->Binary(ynn_binary_multiply, 399, 394, 400);
  g->Quantize(400, 401, 0.3326771557331085, 0);
  g->Transpose(5676, 3217, {1,0});
  g->Binary(ynn_binary_multiply, 3214, 3216, 3212);
  g->Dot(401, 3217, YNN_INVALID_VALUE_ID, 3211, 1);
  g->DequantizeTensor(3211, YNN_INVALID_VALUE_ID, 3212, 3213);
  g->QuantizeTensor(3213, 5190, 3215, 402);
  g->Dequantize(402, 403, 0.11236792802810669, 0);
  g->Unary(ynn_unary_square, 403, 404);
  g->Reduce(ynn_reduce_sum, 404, 4469, {2}, true);
  g->ShapeProduct(404, 4468, {2});
  g->Binary(ynn_binary_divide, 4469, 4468, 405);
  g->Binary(ynn_binary_add, 405, 5241, 406);
  g->Unary(ynn_unary_rsqrt, 406, 408);
  g->Binary(ynn_binary_multiply, 403, 408, 409);
  g->Binary(ynn_binary_multiply, 409, 5679, 410);
  g->Binary(ynn_binary_add, 382, 410, 411);
  g->Binary(ynn_binary_multiply, 411, 5671, 412);
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
  g->Quantize(420, 421, 0.05069896951317787, 0);
  g->Transpose(5338, 3224, {1,0});
  g->Binary(ynn_binary_multiply, 3221, 3223, 3219);
  g->Dot(421, 3224, YNN_INVALID_VALUE_ID, 3218, 1);
  g->DequantizeTensor(3218, YNN_INVALID_VALUE_ID, 3219, 3220);
  g->QuantizeTensor(3220, 5190, 3222, 422);
  g->Dequantize(422, 423, 0.06446851044893265, 0);
  g->SplitDim(423, 424, 2, {2,256});
  g->Transpose(424, 425, {0,2,1,3});
  g->Unary(ynn_unary_square, 425, 426);
  g->Reduce(ynn_reduce_sum, 426, 4477, {3}, true);
  g->ShapeProduct(426, 4476, {3});
  g->Binary(ynn_binary_divide, 4477, 4476, 427);
  g->Binary(ynn_binary_add, 427, 5241, 428);
  g->Unary(ynn_unary_rsqrt, 428, 429);
  g->Binary(ynn_binary_multiply, 425, 429, 431);
  g->Binary(ynn_binary_multiply, 431, 5337, 432);
  g->Slice(432, 433, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(432, 434, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 434, 435);
  g->Concat({435,433}, 436, 3);
  g->Binary(ynn_binary_multiply, 432, 2394, 437);
  g->Binary(ynn_binary_multiply, 436, 2498, 438);
  g->Binary(ynn_binary_add, 437, 438, 439);
  g->Transpose(5342, 3229, {1,0});
  g->Binary(ynn_binary_multiply, 3221, 3228, 3226);
  g->Dot(421, 3229, YNN_INVALID_VALUE_ID, 3225, 1);
  g->DequantizeTensor(3225, YNN_INVALID_VALUE_ID, 3226, 3227);
  g->QuantizeTensor(3227, 5190, 3222, 441);
  g->Dequantize(441, 442, 0.06446851044893265, 0);
  g->SplitDim(442, 443, 2, {2,256});
  g->Transpose(443, 444, {0,2,1,3});
  g->Unary(ynn_unary_square, 444, 445);
  g->Reduce(ynn_reduce_sum, 445, 4479, {3}, true);
  g->ShapeProduct(445, 4478, {3});
  g->Binary(ynn_binary_divide, 4479, 4478, 446);
  g->Binary(ynn_binary_add, 446, 5241, 447);
  g->Unary(ynn_unary_rsqrt, 447, 448);
  g->Binary(ynn_binary_multiply, 444, 448, 449);
}

// Scope: "Layer10 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(439, 450, 0.0057654301635921, 0);
  g->Append(5193, 450, 5715, 2, s2, s1);
  g->View(5715, 5763, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(449, 452, 0.047244105488061905, 0);
  g->Append(5217, 452, 5739, 2, s2, s1);
  g->View(5739, 5786, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer10 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(5341, 3242, {1,0});
  g->Binary(ynn_binary_multiply, 3221, 3241, 3238);
  g->Dot(421, 3242, YNN_INVALID_VALUE_ID, 3237, 1);
  g->DequantizeTensor(3237, YNN_INVALID_VALUE_ID, 3238, 3239);
  g->QuantizeTensor(3239, 5190, 3240, 453);
  g->Dequantize(453, 454, 0.06840551644563675, 0);
  g->SplitDim(454, 455, 2, {8,256});
  g->Transpose(455, 456, {0,2,1,3});
  g->Unary(ynn_unary_square, 456, 458);
  g->Reduce(ynn_reduce_sum, 458, 4481, {3}, true);
  g->ShapeProduct(458, 4480, {3});
  g->Binary(ynn_binary_divide, 4481, 4480, 459);
  g->Binary(ynn_binary_add, 459, 5241, 460);
  g->Unary(ynn_unary_rsqrt, 460, 461);
  g->Binary(ynn_binary_multiply, 456, 461, 462);
  g->Binary(ynn_binary_multiply, 462, 5340, 463);
  g->Slice(463, 464, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(463, 465, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 465, 466);
  g->Concat({466,464}, 467, 3);
  g->Binary(ynn_binary_multiply, 463, 2394, 469);
  g->Binary(ynn_binary_multiply, 467, 2498, 470);
  g->Binary(ynn_binary_add, 469, 470, 471);
}

// Scope: "Layer10 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(5763, 472, 0.0057654301635921, 0);
  g->Dequantize(5786, 473, 0.047244105488061905, 0);
  g->Slice(471, 474, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(472, 475, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(473, 476, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(474, 475, 477, false, true);
  g->Mask(477, 5248, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 5248, 4487, {-1}, true);
  g->Binary(ynn_binary_subtract, 5248, 4487, 4484);
  g->Unary(ynn_unary_exp, 4484, 4485);
  g->Reduce(ynn_reduce_sum, 4485, 4488, {-1}, true);
  g->Binary(ynn_binary_divide, 4364, 4488, 4486);
  g->Binary(ynn_binary_multiply, 4485, 4486, 479);
  g->Matmul(479, 476, 480, false, false);
  g->Slice(471, 481, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(472, 482, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(473, 483, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(481, 482, 484, false, true);
  g->Mask(484, 5249, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 5249, 4492, {-1}, true);
  g->Binary(ynn_binary_subtract, 5249, 4492, 4489);
  g->Unary(ynn_unary_exp, 4489, 4490);
  g->Reduce(ynn_reduce_sum, 4490, 4493, {-1}, true);
  g->Binary(ynn_binary_divide, 4364, 4493, 4491);
  g->Binary(ynn_binary_multiply, 4490, 4491, 485);
  g->Matmul(485, 483, 486, false, false);
  g->Concat({480,486}, 487, 1);
}

// Scope: "Layer10 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(487, 489, {0,2,1,3});
  g->FuseDims(489, 490, 2, 2);
  g->Quantize(490, 491, 0.02362205646932125, 0);
  g->Transpose(5339, 3249, {1,0});
  g->Binary(ynn_binary_multiply, 3246, 3248, 3244);
  g->Dot(491, 3249, YNN_INVALID_VALUE_ID, 3243, 1);
  g->DequantizeTensor(3243, YNN_INVALID_VALUE_ID, 3244, 3245);
  g->QuantizeTensor(3245, 5190, 3247, 492);
  g->Dequantize(492, 493, 0.09525793045759201, 0);
}

// Scope: "Layer10 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 412, 413);
  g->Reduce(ynn_reduce_sum, 413, 4471, {2}, true);
  g->ShapeProduct(413, 4470, {2});
  g->Binary(ynn_binary_divide, 4471, 4470, 414);
  g->Binary(ynn_binary_add, 414, 5241, 415);
  g->Unary(ynn_unary_rsqrt, 415, 416);
  g->Binary(ynn_binary_multiply, 412, 416, 417);
  g->Binary(ynn_binary_multiply, 417, 5326, 420);
  BuildLayer10AttentionKvProjection(ctx);
  BuildLayer10AttentionCacheUpdate(ctx);
  BuildLayer10AttentionQueryProjection(ctx);
  BuildLayer10AttentionSdpa(ctx);
  BuildLayer10AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 493, 494);
  g->Reduce(ynn_reduce_sum, 494, 4495, {2}, true);
  g->ShapeProduct(494, 4494, {2});
  g->Binary(ynn_binary_divide, 4495, 4494, 495);
  g->Binary(ynn_binary_add, 495, 5241, 496);
  g->Unary(ynn_unary_rsqrt, 496, 497);
  g->Binary(ynn_binary_multiply, 493, 497, 498);
  g->Binary(ynn_binary_multiply, 498, 5333, 500);
  g->Binary(ynn_binary_add, 500, 412, 501);
}

// Scope: "Layer10 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 501, 502);
  g->Reduce(ynn_reduce_sum, 502, 4497, {2}, true);
  g->ShapeProduct(502, 4496, {2});
  g->Binary(ynn_binary_divide, 4497, 4496, 503);
  g->Binary(ynn_binary_add, 503, 5241, 504);
  g->Unary(ynn_unary_rsqrt, 504, 505);
  g->Binary(ynn_binary_multiply, 501, 505, 506);
  g->Binary(ynn_binary_multiply, 506, 5336, 507);
  g->Quantize(507, 508, 0.015853581950068474, 0);
  g->Transpose(5330, 3255, {1,0});
  g->Binary(ynn_binary_multiply, 3253, 3254, 3251);
  g->Dot(508, 3255, YNN_INVALID_VALUE_ID, 3250, 1);
  g->DequantizeTensor(3250, YNN_INVALID_VALUE_ID, 3251, 3252);
  g->QuantizeTensor(3252, 5190, 3110, 509);
  g->Dequantize(509, 511, 0.023375993594527245, 0);
  g->Transpose(5329, 3260, {1,0});
  g->Binary(ynn_binary_multiply, 3253, 3259, 3257);
  g->Dot(508, 3260, YNN_INVALID_VALUE_ID, 3256, 1);
  g->DequantizeTensor(3256, YNN_INVALID_VALUE_ID, 3257, 3258);
  g->QuantizeTensor(3258, 5190, 3110, 512);
  g->Dequantize(512, 513, 0.023375993594527245, 0);
  g->Polynomial(513, 4500, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 4500, 4501);
  g->Binary(ynn_binary_add, 4501, 4364, 4498);
  g->Binary(ynn_binary_multiply, 513, 4376, 4499);
  g->Binary(ynn_binary_multiply, 4499, 4498, 514);
  g->Binary(ynn_binary_multiply, 511, 514, 515);
  g->Quantize(515, 516, 0.041338592767715454, 0);
  g->Transpose(5328, 3267, {1,0});
  g->Binary(ynn_binary_multiply, 3264, 3266, 3262);
  g->Dot(516, 3267, YNN_INVALID_VALUE_ID, 3261, 1);
  g->DequantizeTensor(3261, YNN_INVALID_VALUE_ID, 3262, 3263);
  g->QuantizeTensor(3263, 5190, 3265, 517);
  g->Dequantize(517, 518, 0.04055152088403702, 0);
  g->Unary(ynn_unary_square, 518, 519);
  g->Reduce(ynn_reduce_sum, 519, 4503, {2}, true);
  g->ShapeProduct(519, 4502, {2});
  g->Binary(ynn_binary_divide, 4503, 4502, 522);
  g->Binary(ynn_binary_add, 522, 5241, 523);
  g->Unary(ynn_unary_rsqrt, 523, 524);
  g->Binary(ynn_binary_multiply, 518, 524, 525);
  g->Binary(ynn_binary_multiply, 525, 5334, 526);
  g->Binary(ynn_binary_add, 526, 501, 527);
}

// Scope: "Layer10 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 528, {0,0,10,0}, {-1,-1,1,-1});
  g->Reshape(528, 529, {1,0,256});
  g->Unary(ynn_unary_square, 529, 530);
  g->Reduce(ynn_reduce_sum, 530, 4505, {2}, true);
  g->ShapeProduct(530, 4504, {2});
  g->Binary(ynn_binary_divide, 4505, 4504, 531);
  g->Binary(ynn_binary_add, 531, 5241, 533);
  g->Unary(ynn_unary_rsqrt, 533, 534);
  g->Binary(ynn_binary_multiply, 529, 534, 535);
  g->Binary(ynn_binary_multiply, 535, 5688, 536);
  g->Binary(ynn_binary_multiply, 5691, 5245, 537);
  g->Binary(ynn_binary_add, 536, 537, 538);
  g->Binary(ynn_binary_multiply, 538, 5240, 539);
  g->Quantize(527, 540, 0.16557246446609497, 0);
  g->Transpose(5331, 3274, {1,0});
  g->Binary(ynn_binary_multiply, 3271, 3273, 3269);
  g->Dot(540, 3274, YNN_INVALID_VALUE_ID, 3268, 1);
  g->DequantizeTensor(3268, YNN_INVALID_VALUE_ID, 3269, 3270);
  g->QuantizeTensor(3270, 5190, 3272, 541);
  g->Dequantize(541, 542, 0.10039370507001877, 0);
  g->Polynomial(542, 4508, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 4508, 4509);
  g->Binary(ynn_binary_add, 4509, 4364, 4506);
  g->Binary(ynn_binary_multiply, 542, 4376, 4507);
  g->Binary(ynn_binary_multiply, 4507, 4506, 544);
  g->Binary(ynn_binary_multiply, 544, 539, 545);
  g->Quantize(545, 546, 0.32677164673805237, 0);
  g->Transpose(5332, 3281, {1,0});
  g->Binary(ynn_binary_multiply, 3278, 3280, 3276);
  g->Dot(546, 3281, YNN_INVALID_VALUE_ID, 3275, 1);
  g->DequantizeTensor(3275, YNN_INVALID_VALUE_ID, 3276, 3277);
  g->QuantizeTensor(3277, 5190, 3279, 547);
  g->Dequantize(547, 548, 0.11847137659788132, 0);
  g->Unary(ynn_unary_square, 548, 549);
  g->Reduce(ynn_reduce_sum, 549, 4511, {2}, true);
  g->ShapeProduct(549, 4510, {2});
  g->Binary(ynn_binary_divide, 4511, 4510, 550);
  g->Binary(ynn_binary_add, 550, 5241, 551);
  g->Unary(ynn_unary_rsqrt, 551, 552);
  g->Binary(ynn_binary_multiply, 548, 552, 553);
  g->Binary(ynn_binary_multiply, 553, 5335, 555);
  g->Binary(ynn_binary_add, 527, 555, 556);
  g->Binary(ynn_binary_multiply, 556, 5327, 557);
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
  g->Quantize(563, 564, 0.043663885444402695, 0);
  g->Transpose(5355, 3288, {1,0});
  g->Binary(ynn_binary_multiply, 3285, 3287, 3283);
  g->Dot(564, 3288, YNN_INVALID_VALUE_ID, 3282, 1);
  g->DequantizeTensor(3282, YNN_INVALID_VALUE_ID, 3283, 3284);
  g->QuantizeTensor(3284, 5190, 3286, 566);
  g->Dequantize(566, 567, 0.05019685998558998, 0);
  g->SplitDim(567, 568, 2, {2,512});
  g->Transpose(568, 569, {0,2,1,3});
  g->Unary(ynn_unary_square, 569, 570);
  g->Reduce(ynn_reduce_sum, 570, 4517, {3}, true);
  g->ShapeProduct(570, 4516, {3});
  g->Binary(ynn_binary_divide, 4517, 4516, 571);
  g->Binary(ynn_binary_add, 571, 5241, 572);
  g->Unary(ynn_unary_rsqrt, 572, 573);
  g->Binary(ynn_binary_multiply, 569, 573, 574);
  g->Binary(ynn_binary_multiply, 574, 5354, 575);
  g->Slice(575, 577, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(575, 578, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 578, 579);
  g->Concat({579,577}, 580, 3);
  g->Binary(ynn_binary_multiply, 575, 2909, 581);
  g->Binary(ynn_binary_multiply, 580, 2, 582);
  g->Binary(ynn_binary_add, 581, 582, 583);
  g->Transpose(5359, 3293, {1,0});
  g->Binary(ynn_binary_multiply, 3285, 3292, 3290);
  g->Dot(564, 3293, YNN_INVALID_VALUE_ID, 3289, 1);
  g->DequantizeTensor(3289, YNN_INVALID_VALUE_ID, 3290, 3291);
  g->QuantizeTensor(3291, 5190, 3286, 584);
  g->Dequantize(584, 585, 0.05019685998558998, 0);
  g->SplitDim(585, 587, 2, {2,512});
  g->Transpose(587, 588, {0,2,1,3});
  g->Unary(ynn_unary_square, 588, 589);
  g->Reduce(ynn_reduce_sum, 589, 4519, {3}, true);
  g->ShapeProduct(589, 4518, {3});
  g->Binary(ynn_binary_divide, 4519, 4518, 590);
  g->Binary(ynn_binary_add, 590, 5241, 591);
  g->Unary(ynn_unary_rsqrt, 591, 592);
  g->Binary(ynn_binary_multiply, 588, 592, 593);
}

// Scope: "Layer11 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(583, 594, 0.0011474735802039504, 0);
  g->Append(5194, 594, 5716, 2, s2, s1);
  g->View(5716, 5764, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(593, 596, 0.01785714365541935, 0);
  g->Append(5218, 596, 5740, 2, s2, s1);
  g->View(5740, 5787, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer11 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(5358, 3299, {1,0});
  g->Binary(ynn_binary_multiply, 3285, 3298, 3295);
  g->Dot(564, 3299, YNN_INVALID_VALUE_ID, 3294, 1);
  g->DequantizeTensor(3294, YNN_INVALID_VALUE_ID, 3295, 3296);
  g->QuantizeTensor(3296, 5190, 3297, 597);
  g->Dequantize(597, 598, 0.0664370134472847, 0);
  g->SplitDim(598, 599, 2, {8,512});
  g->Transpose(599, 600, {0,2,1,3});
  g->Unary(ynn_unary_square, 600, 601);
  g->Reduce(ynn_reduce_sum, 601, 4521, {3}, true);
  g->ShapeProduct(601, 4520, {3});
  g->Binary(ynn_binary_divide, 4521, 4520, 602);
  g->Binary(ynn_binary_add, 602, 5241, 604);
  g->Unary(ynn_unary_rsqrt, 604, 605);
  g->Binary(ynn_binary_multiply, 600, 605, 606);
  g->Binary(ynn_binary_multiply, 606, 5357, 607);
  g->Slice(607, 608, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(607, 609, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 609, 610);
  g->Concat({610,608}, 611, 3);
  g->Binary(ynn_binary_multiply, 607, 2909, 612);
  g->Binary(ynn_binary_multiply, 611, 2, 613);
  g->Binary(ynn_binary_add, 612, 613, 615);
}

// Scope: "Layer11 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(5764, 616, 0.0011474735802039504, 0);
  g->Dequantize(5787, 617, 0.01785714365541935, 0);
  g->Slice(615, 618, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(616, 619, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(617, 620, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(618, 619, 621, false, true);
  g->Mask(621, 5250, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 5250, 4525, {-1}, true);
  g->Binary(ynn_binary_subtract, 5250, 4525, 4522);
  g->Unary(ynn_unary_exp, 4522, 4523);
  g->Reduce(ynn_reduce_sum, 4523, 4526, {-1}, true);
  g->Binary(ynn_binary_divide, 4364, 4526, 4524);
  g->Binary(ynn_binary_multiply, 4523, 4524, 622);
  g->Matmul(622, 620, 623, false, false);
  g->Slice(615, 626, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(616, 627, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(617, 628, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(626, 627, 629, false, true);
  g->Mask(629, 5251, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 5251, 4532, {-1}, true);
  g->Binary(ynn_binary_subtract, 5251, 4532, 4529);
  g->Unary(ynn_unary_exp, 4529, 4530);
  g->Reduce(ynn_reduce_sum, 4530, 4533, {-1}, true);
  g->Binary(ynn_binary_divide, 4364, 4533, 4531);
  g->Binary(ynn_binary_multiply, 4530, 4531, 630);
  g->Matmul(630, 628, 631, false, false);
  g->Concat({623,631}, 632, 1);
}

// Scope: "Layer11 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(632, 633, {0,2,1,3});
  g->FuseDims(633, 634, 2, 2);
  g->Quantize(634, 636, 0.016240166500210762, 0);
  g->Transpose(5356, 3313, {1,0});
  g->Binary(ynn_binary_multiply, 3310, 3312, 3308);
  g->Dot(636, 3313, YNN_INVALID_VALUE_ID, 3307, 1);
  g->DequantizeTensor(3307, YNN_INVALID_VALUE_ID, 3308, 3309);
  g->QuantizeTensor(3309, 5190, 3311, 637);
  g->Dequantize(637, 638, 0.13702435791492462, 0);
}

// Scope: "Layer11 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 557, 558);
  g->Reduce(ynn_reduce_sum, 558, 4513, {2}, true);
  g->ShapeProduct(558, 4512, {2});
  g->Binary(ynn_binary_divide, 4513, 4512, 559);
  g->Binary(ynn_binary_add, 559, 5241, 560);
  g->Unary(ynn_unary_rsqrt, 560, 561);
  g->Binary(ynn_binary_multiply, 557, 561, 562);
  g->Binary(ynn_binary_multiply, 562, 5343, 563);
  BuildLayer11AttentionKvProjection(ctx);
  BuildLayer11AttentionCacheUpdate(ctx);
  BuildLayer11AttentionQueryProjection(ctx);
  BuildLayer11AttentionSdpa(ctx);
  BuildLayer11AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 638, 639);
  g->Reduce(ynn_reduce_sum, 639, 4535, {2}, true);
  g->ShapeProduct(639, 4534, {2});
  g->Binary(ynn_binary_divide, 4535, 4534, 640);
  g->Binary(ynn_binary_add, 640, 5241, 641);
  g->Unary(ynn_unary_rsqrt, 641, 642);
  g->Binary(ynn_binary_multiply, 638, 642, 643);
  g->Binary(ynn_binary_multiply, 643, 5350, 644);
  g->Binary(ynn_binary_add, 644, 557, 645);
}

// Scope: "Layer11 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 645, 647);
  g->Reduce(ynn_reduce_sum, 647, 4537, {2}, true);
  g->ShapeProduct(647, 4536, {2});
  g->Binary(ynn_binary_divide, 4537, 4536, 648);
  g->Binary(ynn_binary_add, 648, 5241, 649);
  g->Unary(ynn_unary_rsqrt, 649, 650);
  g->Binary(ynn_binary_multiply, 645, 650, 651);
  g->Binary(ynn_binary_multiply, 651, 5353, 652);
  g->Quantize(652, 653, 0.023192334920167923, 0);
  g->Transpose(5347, 3320, {1,0});
  g->Binary(ynn_binary_multiply, 3317, 3319, 3315);
  g->Dot(653, 3320, YNN_INVALID_VALUE_ID, 3314, 1);
  g->DequantizeTensor(3314, YNN_INVALID_VALUE_ID, 3315, 3316);
  g->QuantizeTensor(3316, 5190, 3318, 654);
  g->Dequantize(654, 655, 0.03223426267504692, 0);
  g->Transpose(5346, 3325, {1,0});
  g->Binary(ynn_binary_multiply, 3317, 3324, 3322);
  g->Dot(653, 3325, YNN_INVALID_VALUE_ID, 3321, 1);
  g->DequantizeTensor(3321, YNN_INVALID_VALUE_ID, 3322, 3323);
  g->QuantizeTensor(3323, 5190, 3318, 657);
  g->Dequantize(657, 658, 0.03223426267504692, 0);
  g->Polynomial(658, 4540, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 4540, 4541);
  g->Binary(ynn_binary_add, 4541, 4364, 4538);
  g->Binary(ynn_binary_multiply, 658, 4376, 4539);
  g->Binary(ynn_binary_multiply, 4539, 4538, 659);
  g->Binary(ynn_binary_multiply, 655, 659, 660);
  g->Quantize(660, 661, 0.07480315864086151, 0);
  g->Transpose(5345, 3332, {1,0});
  g->Binary(ynn_binary_multiply, 3329, 3331, 3327);
  g->Dot(661, 3332, YNN_INVALID_VALUE_ID, 3326, 1);
  g->DequantizeTensor(3326, YNN_INVALID_VALUE_ID, 3327, 3328);
  g->QuantizeTensor(3328, 5190, 3330, 662);
  g->Dequantize(662, 663, 0.03340588137507439, 0);
  g->Unary(ynn_unary_square, 663, 664);
  g->Reduce(ynn_reduce_sum, 664, 4543, {2}, true);
  g->ShapeProduct(664, 4542, {2});
  g->Binary(ynn_binary_divide, 4543, 4542, 665);
  g->Binary(ynn_binary_add, 665, 5241, 666);
  g->Unary(ynn_unary_rsqrt, 666, 668);
  g->Binary(ynn_binary_multiply, 663, 668, 669);
  g->Binary(ynn_binary_multiply, 669, 5351, 670);
  g->Binary(ynn_binary_add, 670, 645, 671);
}

// Scope: "Layer11 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 672, {0,0,11,0}, {-1,-1,1,-1});
  g->Reshape(672, 673, {1,0,256});
  g->Unary(ynn_unary_square, 673, 674);
  g->Reduce(ynn_reduce_sum, 674, 4545, {2}, true);
  g->ShapeProduct(674, 4544, {2});
  g->Binary(ynn_binary_divide, 4545, 4544, 675);
  g->Binary(ynn_binary_add, 675, 5241, 676);
  g->Unary(ynn_unary_rsqrt, 676, 677);
  g->Binary(ynn_binary_multiply, 673, 677, 679);
  g->Binary(ynn_binary_multiply, 679, 5688, 680);
  g->Binary(ynn_binary_multiply, 5692, 5245, 681);
  g->Binary(ynn_binary_add, 680, 681, 682);
  g->Binary(ynn_binary_multiply, 682, 5240, 683);
  g->Quantize(671, 684, 0.18839792907238007, 0);
  g->Transpose(5348, 3339, {1,0});
  g->Binary(ynn_binary_multiply, 3336, 3338, 3334);
  g->Dot(684, 3339, YNN_INVALID_VALUE_ID, 3333, 1);
  g->DequantizeTensor(3333, YNN_INVALID_VALUE_ID, 3334, 3335);
  g->QuantizeTensor(3335, 5190, 3337, 685);
  g->Dequantize(685, 686, 0.08759843558073044, 0);
  g->Polynomial(686, 4550, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 4550, 4551);
  g->Binary(ynn_binary_add, 4551, 4364, 4548);
  g->Binary(ynn_binary_multiply, 686, 4376, 4549);
  g->Binary(ynn_binary_multiply, 4549, 4548, 687);
  g->Binary(ynn_binary_multiply, 687, 683, 688);
  g->Quantize(688, 690, 1.6850394010543823, 0);
  g->Transpose(5349, 3346, {1,0});
  g->Binary(ynn_binary_multiply, 3343, 3345, 3341);
  g->Dot(690, 3346, YNN_INVALID_VALUE_ID, 3340, 1);
  g->DequantizeTensor(3340, YNN_INVALID_VALUE_ID, 3341, 3342);
  g->QuantizeTensor(3342, 5190, 3344, 691);
  g->Dequantize(691, 692, 0.46903082728385925, 0);
  g->Unary(ynn_unary_square, 692, 693);
  g->Reduce(ynn_reduce_sum, 693, 4553, {2}, true);
  g->ShapeProduct(693, 4552, {2});
  g->Binary(ynn_binary_divide, 4553, 4552, 694);
  g->Binary(ynn_binary_add, 694, 5241, 695);
  g->Unary(ynn_unary_rsqrt, 695, 696);
  g->Binary(ynn_binary_multiply, 692, 696, 697);
  g->Binary(ynn_binary_multiply, 697, 5352, 698);
  g->Binary(ynn_binary_add, 671, 698, 699);
  g->Binary(ynn_binary_multiply, 699, 5344, 701);
}

// Scope: "Layer11"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11(Context& ctx) {
  BuildLayer11Attention(ctx);
  BuildLayer11Mlp(ctx);
  BuildLayer11PerLayerEmbedding(ctx);
}

}  // namespace BuildGemma4PrefillSource
