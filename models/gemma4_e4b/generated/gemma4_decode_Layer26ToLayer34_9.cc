// Generated YNNPACK builder; do not edit.
#include "gemma4_decode_builder.h"

namespace BuildGemma4DecodeSource {

// Scope: "Layer26 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer26AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(2729, 2730, 0.3528440296649933, 0);
  g->Transpose(9201, 6265, {1,0});
  g->Binary(ynn_binary_multiply, 6262, 6264, 6260);
  g->Dot(2730, 6265, YNN_INVALID_VALUE_ID, 6259, 1);
  g->DequantizeTensor(6259, YNN_INVALID_VALUE_ID, 6260, 6261);
  g->QuantizeTensor(6261, 8727, 6263, 2731);
  g->Dequantize(2731, 2732, 0.3641732335090637, 0);
  g->SplitDim(2732, 2733, 2, {8,256});
  g->FuseDims(2733, 2735, 1, 2);
  g->SplitDim(2735, 2734, 1, {8,1});
  g->Unary(ynn_unary_square, 2734, 2736);
  g->Reduce(ynn_reduce_sum, 2736, 8024, {3}, true);
  g->ShapeProduct(2736, 8023, {3});
  g->Binary(ynn_binary_divide, 8024, 8023, 2737);
  g->Binary(ynn_binary_add, 2737, 8779, 2738);
  g->Unary(ynn_unary_rsqrt, 2738, 2739);
  g->Binary(ynn_binary_multiply, 2734, 2739, 2740);
  g->Binary(ynn_binary_multiply, 2740, 9200, 2741);
  g->Slice(2741, 2742, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2741, 2743, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2743, 2744);
  g->Concat({2744,2742}, 2745, 3);
  g->Binary(ynn_binary_multiply, 2741, 3231, 2746);
  g->Binary(ynn_binary_multiply, 2745, 4329, 2747);
  g->Binary(ynn_binary_add, 2746, 2747, 2748);
}

// Scope: "Layer26 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer26AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9640, 2749, 0.0059552486054599285, 0);
  g->Dequantize(9664, 2751, 0.047244105488061905, 0);
  g->Slice(2748, 2752, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(2749, 2753, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(2751, 2754, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(2752, 2753, 2755, false, true);
  g->Mask(2755, 8822, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8822, 8033, {-1}, true);
  g->Binary(ynn_binary_subtract, 8822, 8033, 8030);
  g->Unary(ynn_unary_exp, 8030, 8031);
  g->Reduce(ynn_reduce_sum, 8031, 8034, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 8034, 8032);
  g->Binary(ynn_binary_multiply, 8031, 8032, 2756);
  g->Matmul(2756, 2754, 2757, false, false);
  g->Slice(2748, 2758, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(2749, 2759, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(2751, 2761, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(2758, 2759, 2762, false, true);
  g->Mask(2762, 8823, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8823, 8038, {-1}, true);
  g->Binary(ynn_binary_subtract, 8823, 8038, 8035);
  g->Unary(ynn_unary_exp, 8035, 8036);
  g->Reduce(ynn_reduce_sum, 8036, 8039, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 8039, 8037);
  g->Binary(ynn_binary_multiply, 8036, 8037, 2763);
  g->Matmul(2763, 2761, 2764, false, false);
  g->Concat({2757,2764}, 2765, 1);
}

// Scope: "Layer26 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer26AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(2765, 2767, 1, 2);
  g->SplitDim(2767, 2766, 1, {1,8});
  g->FuseDims(2766, 2768, 2, 2);
  g->Quantize(2768, 2769, 0.018700797110795975, 0);
  g->Transpose(9199, 6271, {1,0});
  g->Binary(ynn_binary_multiply, 5623, 6270, 6267);
  g->Dot(2769, 6271, YNN_INVALID_VALUE_ID, 6266, 1);
  g->DequantizeTensor(6266, YNN_INVALID_VALUE_ID, 6267, 6268);
  g->QuantizeTensor(6268, 8727, 6269, 2770);
  g->Dequantize(2770, 2772, 0.045751601457595825, 0);
}

// Scope: "Layer26 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer26Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2722, 2723);
  g->Reduce(ynn_reduce_sum, 2723, 8022, {2}, true);
  g->ShapeProduct(2723, 8021, {2});
  g->Binary(ynn_binary_divide, 8022, 8021, 2724);
  g->Binary(ynn_binary_add, 2724, 8779, 2725);
  g->Unary(ynn_unary_rsqrt, 2725, 2726);
  g->Binary(ynn_binary_multiply, 2722, 2726, 2727);
  g->Binary(ynn_binary_multiply, 2727, 9188, 2729);
  BuildLayer26AttentionQueryProjection(ctx);
  BuildLayer26AttentionSdpa(ctx);
  BuildLayer26AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2772, 2773);
  g->Reduce(ynn_reduce_sum, 2773, 8041, {2}, true);
  g->ShapeProduct(2773, 8040, {2});
  g->Binary(ynn_binary_divide, 8041, 8040, 2774);
  g->Binary(ynn_binary_add, 2774, 8779, 2775);
  g->Unary(ynn_unary_rsqrt, 2775, 2776);
  g->Binary(ynn_binary_multiply, 2772, 2776, 2777);
  g->Binary(ynn_binary_multiply, 2777, 9195, 2778);
  g->Binary(ynn_binary_add, 2778, 2722, 2779);
}

// Scope: "Layer26 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer26Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2779, 2780);
  g->Reduce(ynn_reduce_sum, 2780, 8043, {2}, true);
  g->ShapeProduct(2780, 8042, {2});
  g->Binary(ynn_binary_divide, 8043, 8042, 2781);
  g->Binary(ynn_binary_add, 2781, 8779, 2783);
  g->Unary(ynn_unary_rsqrt, 2783, 2784);
  g->Binary(ynn_binary_multiply, 2779, 2784, 2785);
  g->Binary(ynn_binary_multiply, 2785, 9198, 2786);
  g->Quantize(2786, 2787, 0.017227180302143097, 0);
  g->Transpose(9192, 6278, {1,0});
  g->Binary(ynn_binary_multiply, 6275, 6277, 6273);
  g->Dot(2787, 6278, YNN_INVALID_VALUE_ID, 6272, 1);
  g->DequantizeTensor(6272, YNN_INVALID_VALUE_ID, 6273, 6274);
  g->QuantizeTensor(6274, 8727, 6276, 2788);
  g->Dequantize(2788, 2789, 0.01808563992381096, 0);
  g->Transpose(9191, 6283, {1,0});
  g->Binary(ynn_binary_multiply, 6275, 6282, 6280);
  g->Dot(2787, 6283, YNN_INVALID_VALUE_ID, 6279, 1);
  g->DequantizeTensor(6279, YNN_INVALID_VALUE_ID, 6280, 6281);
  g->QuantizeTensor(6281, 8727, 6276, 2790);
  g->Dequantize(2790, 2791, 0.01808563992381096, 0);
  g->Polynomial(2791, 8046, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8046, 8047);
  g->Binary(ynn_binary_add, 8047, 7293, 8044);
  g->Binary(ynn_binary_multiply, 2791, 7305, 8045);
  g->Binary(ynn_binary_multiply, 8045, 8044, 2794);
  g->Binary(ynn_binary_multiply, 2789, 2794, 2795);
  g->Quantize(2795, 2796, 0.022514773532748222, 0);
  g->Transpose(9190, 6290, {1,0});
  g->Binary(ynn_binary_multiply, 6287, 6289, 6285);
  g->Dot(2796, 6290, YNN_INVALID_VALUE_ID, 6284, 1);
  g->DequantizeTensor(6284, YNN_INVALID_VALUE_ID, 6285, 6286);
  g->QuantizeTensor(6286, 8727, 6288, 2797);
  g->Dequantize(2797, 2798, 0.013520898297429085, 0);
  g->Unary(ynn_unary_square, 2798, 2799);
  g->Reduce(ynn_reduce_sum, 2799, 8049, {2}, true);
  g->ShapeProduct(2799, 8048, {2});
  g->Binary(ynn_binary_divide, 8049, 8048, 2800);
  g->Binary(ynn_binary_add, 2800, 8779, 2801);
  g->Unary(ynn_unary_rsqrt, 2801, 2802);
  g->Binary(ynn_binary_multiply, 2798, 2802, 2803);
  g->Binary(ynn_binary_multiply, 2803, 9196, 2805);
  g->Binary(ynn_binary_add, 2805, 2779, 2806);
}

// Scope: "Layer26 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer26PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(429, 2807, {0,0,26,0}, {-1,-1,1,-1});
  g->Reshape(2807, 2808, {1,1,256});
  g->Unary(ynn_unary_square, 2808, 2809);
  g->Reduce(ynn_reduce_sum, 2809, 8051, {2}, true);
  g->ShapeProduct(2809, 8050, {2});
  g->Binary(ynn_binary_divide, 8051, 8050, 2810);
  g->Binary(ynn_binary_add, 2810, 8779, 2811);
  g->Unary(ynn_unary_rsqrt, 2811, 2812);
  g->Binary(ynn_binary_multiply, 2808, 2812, 2813);
  g->Binary(ynn_binary_multiply, 2813, 9533, 2814);
  g->Binary(ynn_binary_multiply, 9553, 8783, 2815);
  g->Binary(ynn_binary_add, 2814, 2815, 2816);
  g->Binary(ynn_binary_multiply, 2816, 8777, 2817);
  g->Quantize(2806, 2818, 0.2931458652019501, 0);
  g->Transpose(9193, 6297, {1,0});
  g->Binary(ynn_binary_multiply, 6294, 6296, 6292);
  g->Dot(2818, 6297, YNN_INVALID_VALUE_ID, 6291, 1);
  g->DequantizeTensor(6291, YNN_INVALID_VALUE_ID, 6292, 6293);
  g->QuantizeTensor(6293, 8727, 6295, 2819);
  g->Dequantize(2819, 2820, 0.19685040414333344, 0);
  g->Polynomial(2820, 8054, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8054, 8055);
  g->Binary(ynn_binary_add, 8055, 7293, 8052);
  g->Binary(ynn_binary_multiply, 2820, 7305, 8053);
  g->Binary(ynn_binary_multiply, 8053, 8052, 2821);
  g->Binary(ynn_binary_multiply, 2821, 2817, 2822);
  g->Quantize(2822, 2823, 1.0629920959472656, 0);
  g->Transpose(9194, 6304, {1,0});
  g->Binary(ynn_binary_multiply, 6301, 6303, 6299);
  g->Dot(2823, 6304, YNN_INVALID_VALUE_ID, 6298, 1);
  g->DequantizeTensor(6298, YNN_INVALID_VALUE_ID, 6299, 6300);
  g->QuantizeTensor(6300, 8727, 6302, 2824);
  g->Dequantize(2824, 2826, 0.163782998919487, 0);
  g->Unary(ynn_unary_square, 2826, 2827);
  g->Reduce(ynn_reduce_sum, 2827, 8062, {2}, true);
  g->ShapeProduct(2827, 8061, {2});
  g->Binary(ynn_binary_divide, 8062, 8061, 2828);
  g->Binary(ynn_binary_add, 2828, 8779, 2829);
  g->Unary(ynn_unary_rsqrt, 2829, 2830);
  g->Binary(ynn_binary_multiply, 2826, 2830, 2831);
  g->Binary(ynn_binary_multiply, 2831, 9197, 2832);
  g->Binary(ynn_binary_add, 2806, 2832, 2833);
  g->Binary(ynn_binary_multiply, 2833, 9189, 2834);
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
  g->Quantize(2841, 2842, 0.3453449010848999, 0);
  g->Transpose(9215, 6311, {1,0});
  g->Binary(ynn_binary_multiply, 6308, 6310, 6306);
  g->Dot(2842, 6311, YNN_INVALID_VALUE_ID, 6305, 1);
  g->DequantizeTensor(6305, YNN_INVALID_VALUE_ID, 6306, 6307);
  g->QuantizeTensor(6307, 8727, 6309, 2843);
  g->Dequantize(2843, 2844, 0.35433071851730347, 0);
  g->SplitDim(2844, 2845, 2, {8,256});
  g->FuseDims(2845, 2847, 1, 2);
  g->SplitDim(2847, 2846, 1, {8,1});
  g->Unary(ynn_unary_square, 2846, 2849);
  g->Reduce(ynn_reduce_sum, 2849, 8066, {3}, true);
  g->ShapeProduct(2849, 8065, {3});
  g->Binary(ynn_binary_divide, 8066, 8065, 2850);
  g->Binary(ynn_binary_add, 2850, 8779, 2851);
  g->Unary(ynn_unary_rsqrt, 2851, 2852);
  g->Binary(ynn_binary_multiply, 2846, 2852, 2853);
  g->Binary(ynn_binary_multiply, 2853, 9214, 2854);
  g->Slice(2854, 2855, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2854, 2856, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2856, 2857);
  g->Concat({2857,2855}, 2858, 3);
  g->Binary(ynn_binary_multiply, 2854, 3231, 2861);
  g->Binary(ynn_binary_multiply, 2858, 4329, 2862);
  g->Binary(ynn_binary_add, 2861, 2862, 2863);
}

// Scope: "Layer27 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer27AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9640, 2864, 0.0059552486054599285, 0);
  g->Dequantize(9664, 2865, 0.047244105488061905, 0);
  g->Slice(2863, 2866, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(2864, 2867, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(2865, 2868, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(2866, 2867, 2869, false, true);
  g->Mask(2869, 8824, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8824, 8070, {-1}, true);
  g->Binary(ynn_binary_subtract, 8824, 8070, 8067);
  g->Unary(ynn_unary_exp, 8067, 8068);
  g->Reduce(ynn_reduce_sum, 8068, 8071, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 8071, 8069);
  g->Binary(ynn_binary_multiply, 8068, 8069, 2871);
  g->Matmul(2871, 2868, 2872, false, false);
  g->Slice(2863, 2873, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(2864, 2874, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(2865, 2875, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(2873, 2874, 2876, false, true);
  g->Mask(2876, 8825, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8825, 8075, {-1}, true);
  g->Binary(ynn_binary_subtract, 8825, 8075, 8072);
  g->Unary(ynn_unary_exp, 8072, 8073);
  g->Reduce(ynn_reduce_sum, 8073, 8076, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 8076, 8074);
  g->Binary(ynn_binary_multiply, 8073, 8074, 2877);
  g->Matmul(2877, 2875, 2878, false, false);
  g->Concat({2872,2878}, 2879, 1);
}

// Scope: "Layer27 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer27AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(2879, 2882, 1, 2);
  g->SplitDim(2882, 2881, 1, {1,8});
  g->FuseDims(2881, 2883, 2, 2);
  g->Quantize(2883, 2884, 0.020669300109148026, 0);
  g->Transpose(9213, 6318, {1,0});
  g->Binary(ynn_binary_multiply, 6315, 6317, 6313);
  g->Dot(2884, 6318, YNN_INVALID_VALUE_ID, 6312, 1);
  g->DequantizeTensor(6312, YNN_INVALID_VALUE_ID, 6313, 6314);
  g->QuantizeTensor(6314, 8727, 6316, 2885);
  g->Dequantize(2885, 2886, 0.04588036239147186, 0);
}

// Scope: "Layer27 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer27Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2834, 2835);
  g->Reduce(ynn_reduce_sum, 2835, 8064, {2}, true);
  g->ShapeProduct(2835, 8063, {2});
  g->Binary(ynn_binary_divide, 8064, 8063, 2837);
  g->Binary(ynn_binary_add, 2837, 8779, 2838);
  g->Unary(ynn_unary_rsqrt, 2838, 2839);
  g->Binary(ynn_binary_multiply, 2834, 2839, 2840);
  g->Binary(ynn_binary_multiply, 2840, 9202, 2841);
  BuildLayer27AttentionQueryProjection(ctx);
  BuildLayer27AttentionSdpa(ctx);
  BuildLayer27AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2886, 2887);
  g->Reduce(ynn_reduce_sum, 2887, 8078, {2}, true);
  g->ShapeProduct(2887, 8077, {2});
  g->Binary(ynn_binary_divide, 8078, 8077, 2888);
  g->Binary(ynn_binary_add, 2888, 8779, 2889);
  g->Unary(ynn_unary_rsqrt, 2889, 2890);
  g->Binary(ynn_binary_multiply, 2886, 2890, 2891);
  g->Binary(ynn_binary_multiply, 2891, 9209, 2893);
  g->Binary(ynn_binary_add, 2893, 2834, 2894);
}

// Scope: "Layer27 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer27Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2894, 2895);
  g->Reduce(ynn_reduce_sum, 2895, 8080, {2}, true);
  g->ShapeProduct(2895, 8079, {2});
  g->Binary(ynn_binary_divide, 8080, 8079, 2896);
  g->Binary(ynn_binary_add, 2896, 8779, 2897);
  g->Unary(ynn_unary_rsqrt, 2897, 2898);
  g->Binary(ynn_binary_multiply, 2894, 2898, 2899);
  g->Binary(ynn_binary_multiply, 2899, 9212, 2900);
  g->Quantize(2900, 2901, 0.019605165347456932, 0);
  g->Transpose(9206, 6331, {1,0});
  g->Binary(ynn_binary_multiply, 6329, 6330, 6327);
  g->Dot(2901, 6331, YNN_INVALID_VALUE_ID, 6326, 1);
  g->DequantizeTensor(6326, YNN_INVALID_VALUE_ID, 6327, 6328);
  g->QuantizeTensor(6328, 8727, 6043, 2902);
  g->Dequantize(2902, 2905, 0.019808080047369003, 0);
  g->Transpose(9205, 6336, {1,0});
  g->Binary(ynn_binary_multiply, 6329, 6335, 6333);
  g->Dot(2901, 6336, YNN_INVALID_VALUE_ID, 6332, 1);
  g->DequantizeTensor(6332, YNN_INVALID_VALUE_ID, 6333, 6334);
  g->QuantizeTensor(6334, 8727, 6043, 2906);
  g->Dequantize(2906, 2907, 0.019808080047369003, 0);
  g->Polynomial(2907, 8083, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8083, 8084);
  g->Binary(ynn_binary_add, 8084, 7293, 8081);
  g->Binary(ynn_binary_multiply, 2907, 7305, 8082);
  g->Binary(ynn_binary_multiply, 8082, 8081, 2908);
  g->Binary(ynn_binary_multiply, 2905, 2908, 2909);
  g->Quantize(2909, 2910, 0.030388789251446724, 0);
  g->Transpose(9204, 6343, {1,0});
  g->Binary(ynn_binary_multiply, 6340, 6342, 6338);
  g->Dot(2910, 6343, YNN_INVALID_VALUE_ID, 6337, 1);
  g->DequantizeTensor(6337, YNN_INVALID_VALUE_ID, 6338, 6339);
  g->QuantizeTensor(6339, 8727, 6341, 2911);
  g->Dequantize(2911, 2912, 0.02053113840520382, 0);
  g->Unary(ynn_unary_square, 2912, 2913);
  g->Reduce(ynn_reduce_sum, 2913, 8086, {2}, true);
  g->ShapeProduct(2913, 8085, {2});
  g->Binary(ynn_binary_divide, 8086, 8085, 2915);
  g->Binary(ynn_binary_add, 2915, 8779, 2916);
  g->Unary(ynn_unary_rsqrt, 2916, 2917);
  g->Binary(ynn_binary_multiply, 2912, 2917, 2918);
  g->Binary(ynn_binary_multiply, 2918, 9210, 2919);
  g->Binary(ynn_binary_add, 2919, 2894, 2920);
}

// Scope: "Layer27 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer27PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(429, 2921, {0,0,27,0}, {-1,-1,1,-1});
  g->Reshape(2921, 2922, {1,1,256});
  g->Unary(ynn_unary_square, 2922, 2923);
  g->Reduce(ynn_reduce_sum, 2923, 8088, {2}, true);
  g->ShapeProduct(2923, 8087, {2});
  g->Binary(ynn_binary_divide, 8088, 8087, 2924);
  g->Binary(ynn_binary_add, 2924, 8779, 2926);
  g->Unary(ynn_unary_rsqrt, 2926, 2927);
  g->Binary(ynn_binary_multiply, 2922, 2927, 2928);
  g->Binary(ynn_binary_multiply, 2928, 9533, 2929);
  g->Binary(ynn_binary_multiply, 9554, 8783, 2930);
  g->Binary(ynn_binary_add, 2929, 2930, 2931);
  g->Binary(ynn_binary_multiply, 2931, 8777, 2932);
  g->Quantize(2920, 2933, 0.24697038531303406, 0);
  g->Transpose(9207, 6350, {1,0});
  g->Binary(ynn_binary_multiply, 6347, 6349, 6345);
  g->Dot(2933, 6350, YNN_INVALID_VALUE_ID, 6344, 1);
  g->DequantizeTensor(6344, YNN_INVALID_VALUE_ID, 6345, 6346);
  g->QuantizeTensor(6346, 8727, 6348, 2934);
  g->Dequantize(2934, 2935, 0.24901576340198517, 0);
  g->Polynomial(2935, 8093, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8093, 8094);
  g->Binary(ynn_binary_add, 8094, 7293, 8091);
  g->Binary(ynn_binary_multiply, 2935, 7305, 8092);
  g->Binary(ynn_binary_multiply, 8092, 8091, 2937);
  g->Binary(ynn_binary_multiply, 2937, 2932, 2938);
  g->Quantize(2938, 2939, 1.1023621559143066, 0);
  g->Transpose(9208, 6357, {1,0});
  g->Binary(ynn_binary_multiply, 6354, 6356, 6352);
  g->Dot(2939, 6357, YNN_INVALID_VALUE_ID, 6351, 1);
  g->DequantizeTensor(6351, YNN_INVALID_VALUE_ID, 6352, 6353);
  g->QuantizeTensor(6353, 8727, 6355, 2940);
  g->Dequantize(2940, 2941, 0.16658033430576324, 0);
  g->Unary(ynn_unary_square, 2941, 2942);
  g->Reduce(ynn_reduce_sum, 2942, 8096, {2}, true);
  g->ShapeProduct(2942, 8095, {2});
  g->Binary(ynn_binary_divide, 8096, 8095, 2943);
  g->Binary(ynn_binary_add, 2943, 8779, 2944);
  g->Unary(ynn_unary_rsqrt, 2944, 2945);
  g->Binary(ynn_binary_multiply, 2941, 2945, 2946);
  g->Binary(ynn_binary_multiply, 2946, 9211, 2948);
  g->Binary(ynn_binary_add, 2920, 2948, 2949);
  g->Binary(ynn_binary_multiply, 2949, 9203, 2950);
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
  g->Quantize(2956, 2957, 0.3128816485404968, 0);
  g->Transpose(9229, 6364, {1,0});
  g->Binary(ynn_binary_multiply, 6361, 6363, 6359);
  g->Dot(2957, 6364, YNN_INVALID_VALUE_ID, 6358, 1);
  g->DequantizeTensor(6358, YNN_INVALID_VALUE_ID, 6359, 6360);
  g->QuantizeTensor(6360, 8727, 6362, 2959);
  g->Dequantize(2959, 2960, 0.312992125749588, 0);
  g->SplitDim(2960, 2961, 2, {8,256});
  g->FuseDims(2961, 2963, 1, 2);
  g->SplitDim(2963, 2962, 1, {8,1});
  g->Unary(ynn_unary_square, 2962, 2964);
  g->Reduce(ynn_reduce_sum, 2964, 8100, {3}, true);
  g->ShapeProduct(2964, 8099, {3});
  g->Binary(ynn_binary_divide, 8100, 8099, 2965);
  g->Binary(ynn_binary_add, 2965, 8779, 2966);
  g->Unary(ynn_unary_rsqrt, 2966, 2967);
  g->Binary(ynn_binary_multiply, 2962, 2967, 2968);
  g->Binary(ynn_binary_multiply, 2968, 9228, 2969);
  g->Slice(2969, 2971, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2969, 2972, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2972, 2973);
  g->Concat({2973,2971}, 2974, 3);
  g->Binary(ynn_binary_multiply, 2969, 3231, 2975);
  g->Binary(ynn_binary_multiply, 2974, 4329, 2976);
  g->Binary(ynn_binary_add, 2975, 2976, 2977);
}

// Scope: "Layer28 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer28AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9640, 2978, 0.0059552486054599285, 0);
  g->Dequantize(9664, 2979, 0.047244105488061905, 0);
  g->Slice(2977, 2980, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(2978, 2982, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(2979, 2983, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(2980, 2982, 2984, false, true);
  g->Mask(2984, 8826, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8826, 8104, {-1}, true);
  g->Binary(ynn_binary_subtract, 8826, 8104, 8101);
  g->Unary(ynn_unary_exp, 8101, 8102);
  g->Reduce(ynn_reduce_sum, 8102, 8105, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 8105, 8103);
  g->Binary(ynn_binary_multiply, 8102, 8103, 2985);
  g->Matmul(2985, 2983, 2986, false, false);
  g->Slice(2977, 2987, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(2978, 2988, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(2979, 2989, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(2987, 2988, 2990, false, true);
  g->Mask(2990, 8827, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8827, 8109, {-1}, true);
  g->Binary(ynn_binary_subtract, 8827, 8109, 8106);
  g->Unary(ynn_unary_exp, 8106, 8107);
  g->Reduce(ynn_reduce_sum, 8107, 8110, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 8110, 8108);
  g->Binary(ynn_binary_multiply, 8107, 8108, 2992);
  g->Matmul(2992, 2989, 2993, false, false);
  g->Concat({2986,2993}, 2994, 1);
}

// Scope: "Layer28 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer28AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(2994, 2996, 1, 2);
  g->SplitDim(2996, 2995, 1, {1,8});
  g->FuseDims(2995, 2997, 2, 2);
  g->Quantize(2997, 2998, 0.019808080047369003, 0);
  g->Transpose(9227, 6370, {1,0});
  g->Binary(ynn_binary_multiply, 6043, 6369, 6366);
  g->Dot(2998, 6370, YNN_INVALID_VALUE_ID, 6365, 1);
  g->DequantizeTensor(6365, YNN_INVALID_VALUE_ID, 6366, 6367);
  g->QuantizeTensor(6367, 8727, 6368, 2999);
  g->Dequantize(2999, 3000, 0.04302408546209335, 0);
}

// Scope: "Layer28 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer28Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2950, 2951);
  g->Reduce(ynn_reduce_sum, 2951, 8098, {2}, true);
  g->ShapeProduct(2951, 8097, {2});
  g->Binary(ynn_binary_divide, 8098, 8097, 2952);
  g->Binary(ynn_binary_add, 2952, 8779, 2953);
  g->Unary(ynn_unary_rsqrt, 2953, 2954);
  g->Binary(ynn_binary_multiply, 2950, 2954, 2955);
  g->Binary(ynn_binary_multiply, 2955, 9216, 2956);
  BuildLayer28AttentionQueryProjection(ctx);
  BuildLayer28AttentionSdpa(ctx);
  BuildLayer28AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 3000, 3001);
  g->Reduce(ynn_reduce_sum, 3001, 8114, {2}, true);
  g->ShapeProduct(3001, 8113, {2});
  g->Binary(ynn_binary_divide, 8114, 8113, 3003);
  g->Binary(ynn_binary_add, 3003, 8779, 3004);
  g->Unary(ynn_unary_rsqrt, 3004, 3005);
  g->Binary(ynn_binary_multiply, 3000, 3005, 3006);
  g->Binary(ynn_binary_multiply, 3006, 9223, 3007);
  g->Binary(ynn_binary_add, 3007, 2950, 3008);
}

// Scope: "Layer28 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer28Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3008, 3009);
  g->Reduce(ynn_reduce_sum, 3009, 8116, {2}, true);
  g->ShapeProduct(3009, 8115, {2});
  g->Binary(ynn_binary_divide, 8116, 8115, 3010);
  g->Binary(ynn_binary_add, 3010, 8779, 3011);
  g->Unary(ynn_unary_rsqrt, 3011, 3012);
  g->Binary(ynn_binary_multiply, 3008, 3012, 3015);
  g->Binary(ynn_binary_multiply, 3015, 9226, 3016);
  g->Quantize(3016, 3017, 0.02151750959455967, 0);
  g->Transpose(9220, 6377, {1,0});
  g->Binary(ynn_binary_multiply, 6374, 6376, 6372);
  g->Dot(3017, 6377, YNN_INVALID_VALUE_ID, 6371, 1);
  g->DequantizeTensor(6371, YNN_INVALID_VALUE_ID, 6372, 6373);
  g->QuantizeTensor(6373, 8727, 6375, 3018);
  g->Dequantize(3018, 3019, 0.026574812829494476, 0);
  g->Transpose(9219, 6382, {1,0});
  g->Binary(ynn_binary_multiply, 6374, 6381, 6379);
  g->Dot(3017, 6382, YNN_INVALID_VALUE_ID, 6378, 1);
  g->DequantizeTensor(6378, YNN_INVALID_VALUE_ID, 6379, 6380);
  g->QuantizeTensor(6380, 8727, 6375, 3020);
  g->Dequantize(3020, 3021, 0.026574812829494476, 0);
  g->Polynomial(3021, 8119, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8119, 8120);
  g->Binary(ynn_binary_add, 8120, 7293, 8117);
  g->Binary(ynn_binary_multiply, 3021, 7305, 8118);
  g->Binary(ynn_binary_multiply, 8118, 8117, 3022);
  g->Binary(ynn_binary_multiply, 3019, 3022, 3023);
  g->Quantize(3023, 3025, 0.04773623123764992, 0);
  g->Transpose(9218, 6388, {1,0});
  g->Binary(ynn_binary_multiply, 5246, 6387, 6384);
  g->Dot(3025, 6388, YNN_INVALID_VALUE_ID, 6383, 1);
  g->DequantizeTensor(6383, YNN_INVALID_VALUE_ID, 6384, 6385);
  g->QuantizeTensor(6385, 8727, 6386, 3026);
  g->Dequantize(3026, 3027, 0.030276838690042496, 0);
  g->Unary(ynn_unary_square, 3027, 3028);
  g->Reduce(ynn_reduce_sum, 3028, 8122, {2}, true);
  g->ShapeProduct(3028, 8121, {2});
  g->Binary(ynn_binary_divide, 8122, 8121, 3029);
  g->Binary(ynn_binary_add, 3029, 8779, 3030);
  g->Unary(ynn_unary_rsqrt, 3030, 3031);
  g->Binary(ynn_binary_multiply, 3027, 3031, 3032);
  g->Binary(ynn_binary_multiply, 3032, 9224, 3033);
  g->Binary(ynn_binary_add, 3033, 3008, 3034);
}

// Scope: "Layer28 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer28PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(429, 3036, {0,0,28,0}, {-1,-1,1,-1});
  g->Reshape(3036, 3037, {1,1,256});
  g->Unary(ynn_unary_square, 3037, 3038);
  g->Reduce(ynn_reduce_sum, 3038, 8124, {2}, true);
  g->ShapeProduct(3038, 8123, {2});
  g->Binary(ynn_binary_divide, 8124, 8123, 3039);
  g->Binary(ynn_binary_add, 3039, 8779, 3040);
  g->Unary(ynn_unary_rsqrt, 3040, 3041);
  g->Binary(ynn_binary_multiply, 3037, 3041, 3042);
  g->Binary(ynn_binary_multiply, 3042, 9533, 3043);
  g->Binary(ynn_binary_multiply, 9555, 8783, 3044);
  g->Binary(ynn_binary_add, 3043, 3044, 3045);
  g->Binary(ynn_binary_multiply, 3045, 8777, 3047);
  g->Quantize(3034, 3048, 0.1727961152791977, 0);
  g->Transpose(9221, 6395, {1,0});
  g->Binary(ynn_binary_multiply, 6392, 6394, 6390);
  g->Dot(3048, 6395, YNN_INVALID_VALUE_ID, 6389, 1);
  g->DequantizeTensor(6389, YNN_INVALID_VALUE_ID, 6390, 6391);
  g->QuantizeTensor(6391, 8727, 6393, 3049);
  g->Dequantize(3049, 3050, 0.2736220359802246, 0);
  g->Polynomial(3050, 8127, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8127, 8128);
  g->Binary(ynn_binary_add, 8128, 7293, 8125);
  g->Binary(ynn_binary_multiply, 3050, 7305, 8126);
  g->Binary(ynn_binary_multiply, 8126, 8125, 3051);
  g->Binary(ynn_binary_multiply, 3051, 3047, 3052);
  g->Quantize(3052, 3053, 1.3543306589126587, 0);
  g->Transpose(9222, 6402, {1,0});
  g->Binary(ynn_binary_multiply, 6399, 6401, 6397);
  g->Dot(3053, 6402, YNN_INVALID_VALUE_ID, 6396, 1);
  g->DequantizeTensor(6396, YNN_INVALID_VALUE_ID, 6397, 6398);
  g->QuantizeTensor(6398, 8727, 6400, 3054);
  g->Dequantize(3054, 3055, 0.2807792127132416, 0);
  g->Unary(ynn_unary_square, 3055, 3056);
  g->Reduce(ynn_reduce_sum, 3056, 8130, {2}, true);
  g->ShapeProduct(3056, 8129, {2});
  g->Binary(ynn_binary_divide, 8130, 8129, 3058);
  g->Binary(ynn_binary_add, 3058, 8779, 3059);
  g->Unary(ynn_unary_rsqrt, 3059, 3060);
  g->Binary(ynn_binary_multiply, 3055, 3060, 3061);
  g->Binary(ynn_binary_multiply, 3061, 9225, 3062);
  g->Binary(ynn_binary_add, 3034, 3062, 3063);
  g->Binary(ynn_binary_multiply, 3063, 9217, 3064);
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
  g->Quantize(3071, 3072, 0.1544896364212036, 0);
  g->Transpose(9243, 6416, {1,0});
  g->Binary(ynn_binary_multiply, 6413, 6415, 6411);
  g->Dot(3072, 6416, YNN_INVALID_VALUE_ID, 6410, 1);
  g->DequantizeTensor(6410, YNN_INVALID_VALUE_ID, 6411, 6412);
  g->QuantizeTensor(6412, 8727, 6414, 3073);
  g->Dequantize(3073, 3074, 0.31496062874794006, 0);
  g->SplitDim(3074, 3075, 2, {8,512});
  g->FuseDims(3075, 3077, 1, 2);
  g->SplitDim(3077, 3076, 1, {8,1});
  g->Unary(ynn_unary_square, 3076, 3078);
  g->Reduce(ynn_reduce_sum, 3078, 8134, {3}, true);
  g->ShapeProduct(3078, 8133, {3});
  g->Binary(ynn_binary_divide, 8134, 8133, 3079);
  g->Binary(ynn_binary_add, 3079, 8779, 3081);
  g->Unary(ynn_unary_rsqrt, 3081, 3082);
  g->Binary(ynn_binary_multiply, 3076, 3082, 3083);
  g->Binary(ynn_binary_multiply, 3083, 9242, 3084);
  g->Slice(3084, 3085, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(3084, 3086, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 3086, 3087);
  g->Concat({3087,3085}, 3088, 3);
  g->Binary(ynn_binary_multiply, 3084, 4959, 3089);
  g->Binary(ynn_binary_multiply, 3088, 2, 3090);
  g->Binary(ynn_binary_add, 3089, 3090, 3091);
}

// Scope: "Layer29 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer29AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9641, 3092, 0.001091228099539876, 0);
  g->Dequantize(9665, 3093, 0.01785714365541935, 0);
  g->Slice(3091, 3094, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(3092, 3095, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(3093, 3096, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(3094, 3095, 3097, false, true);
  g->Mask(3097, 8828, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 8828, 8138, {-1}, true);
  g->Binary(ynn_binary_subtract, 8828, 8138, 8135);
  g->Unary(ynn_unary_exp, 8135, 8136);
  g->Reduce(ynn_reduce_sum, 8136, 8139, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 8139, 8137);
  g->Binary(ynn_binary_multiply, 8136, 8137, 3098);
  g->Matmul(3098, 3096, 3099, false, false);
  g->Slice(3091, 3101, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(3092, 3102, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(3093, 3103, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(3101, 3102, 3104, false, true);
  g->Mask(3104, 8829, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 8829, 8143, {-1}, true);
  g->Binary(ynn_binary_subtract, 8829, 8143, 8140);
  g->Unary(ynn_unary_exp, 8140, 8141);
  g->Reduce(ynn_reduce_sum, 8141, 8144, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 8144, 8142);
  g->Binary(ynn_binary_multiply, 8141, 8142, 3105);
  g->Matmul(3105, 3103, 3106, false, false);
  g->Concat({3099,3106}, 3107, 1);
}

// Scope: "Layer29 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer29AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(3107, 3109, 1, 2);
  g->SplitDim(3109, 3108, 1, {1,8});
  g->FuseDims(3108, 3110, 2, 2);
  g->Quantize(3110, 3112, 0.015071368776261806, 0);
  g->Transpose(9241, 6427, {1,0});
  g->Binary(ynn_binary_multiply, 5947, 6426, 6423);
  g->Dot(3112, 6427, YNN_INVALID_VALUE_ID, 6422, 1);
  g->DequantizeTensor(6422, YNN_INVALID_VALUE_ID, 6423, 6424);
  g->QuantizeTensor(6424, 8727, 6425, 3113);
  g->Dequantize(3113, 3114, 0.02063991315662861, 0);
}

// Scope: "Layer29 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer29Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3064, 3065);
  g->Reduce(ynn_reduce_sum, 3065, 8132, {2}, true);
  g->ShapeProduct(3065, 8131, {2});
  g->Binary(ynn_binary_divide, 8132, 8131, 3066);
  g->Binary(ynn_binary_add, 3066, 8779, 3067);
  g->Unary(ynn_unary_rsqrt, 3067, 3069);
  g->Binary(ynn_binary_multiply, 3064, 3069, 3070);
  g->Binary(ynn_binary_multiply, 3070, 9230, 3071);
  BuildLayer29AttentionQueryProjection(ctx);
  BuildLayer29AttentionSdpa(ctx);
  BuildLayer29AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 3114, 3115);
  g->Reduce(ynn_reduce_sum, 3115, 8146, {2}, true);
  g->ShapeProduct(3115, 8145, {2});
  g->Binary(ynn_binary_divide, 8146, 8145, 3116);
  g->Binary(ynn_binary_add, 3116, 8779, 3117);
  g->Unary(ynn_unary_rsqrt, 3117, 3118);
  g->Binary(ynn_binary_multiply, 3114, 3118, 3119);
  g->Binary(ynn_binary_multiply, 3119, 9237, 3120);
  g->Binary(ynn_binary_add, 3120, 3064, 3121);
}

// Scope: "Layer29 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer29Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3121, 3123);
  g->Reduce(ynn_reduce_sum, 3123, 8152, {2}, true);
  g->ShapeProduct(3123, 8151, {2});
  g->Binary(ynn_binary_divide, 8152, 8151, 3124);
  g->Binary(ynn_binary_add, 3124, 8779, 3125);
  g->Unary(ynn_unary_rsqrt, 3125, 3126);
  g->Binary(ynn_binary_multiply, 3121, 3126, 3127);
  g->Binary(ynn_binary_multiply, 3127, 9240, 3128);
  g->Quantize(3128, 3129, 0.01604880578815937, 0);
  g->Transpose(9234, 6434, {1,0});
  g->Binary(ynn_binary_multiply, 6431, 6433, 6429);
  g->Dot(3129, 6434, YNN_INVALID_VALUE_ID, 6428, 1);
  g->DequantizeTensor(6428, YNN_INVALID_VALUE_ID, 6429, 6430);
  g->QuantizeTensor(6430, 8727, 6432, 3130);
  g->Dequantize(3130, 3131, 0.022883867844939232, 0);
  g->Transpose(9233, 6439, {1,0});
  g->Binary(ynn_binary_multiply, 6431, 6438, 6436);
  g->Dot(3129, 6439, YNN_INVALID_VALUE_ID, 6435, 1);
  g->DequantizeTensor(6435, YNN_INVALID_VALUE_ID, 6436, 6437);
  g->QuantizeTensor(6437, 8727, 6432, 3133);
  g->Dequantize(3133, 3134, 0.022883867844939232, 0);
  g->Polynomial(3134, 8155, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8155, 8156);
  g->Binary(ynn_binary_add, 8156, 7293, 8153);
  g->Binary(ynn_binary_multiply, 3134, 7305, 8154);
  g->Binary(ynn_binary_multiply, 8154, 8153, 3135);
  g->Binary(ynn_binary_multiply, 3131, 3135, 3136);
  g->Quantize(3136, 3137, 0.01931595429778099, 0);
  g->Transpose(9232, 6446, {1,0});
  g->Binary(ynn_binary_multiply, 6443, 6445, 6441);
  g->Dot(3137, 6446, YNN_INVALID_VALUE_ID, 6440, 1);
  g->DequantizeTensor(6440, YNN_INVALID_VALUE_ID, 6441, 6442);
  g->QuantizeTensor(6442, 8727, 6444, 3138);
  g->Dequantize(3138, 3139, 0.008464759215712547, 0);
  g->Unary(ynn_unary_square, 3139, 3140);
  g->Reduce(ynn_reduce_sum, 3140, 8158, {2}, true);
  g->ShapeProduct(3140, 8157, {2});
  g->Binary(ynn_binary_divide, 8158, 8157, 3141);
  g->Binary(ynn_binary_add, 3141, 8779, 3142);
  g->Unary(ynn_unary_rsqrt, 3142, 3144);
  g->Binary(ynn_binary_multiply, 3139, 3144, 3145);
  g->Binary(ynn_binary_multiply, 3145, 9238, 3146);
  g->Binary(ynn_binary_add, 3146, 3121, 3147);
}

// Scope: "Layer29 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer29PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(429, 3148, {0,0,29,0}, {-1,-1,1,-1});
  g->Reshape(3148, 3149, {1,1,256});
  g->Unary(ynn_unary_square, 3149, 3150);
  g->Reduce(ynn_reduce_sum, 3150, 8160, {2}, true);
  g->ShapeProduct(3150, 8159, {2});
  g->Binary(ynn_binary_divide, 8160, 8159, 3151);
  g->Binary(ynn_binary_add, 3151, 8779, 3152);
  g->Unary(ynn_unary_rsqrt, 3152, 3153);
  g->Binary(ynn_binary_multiply, 3149, 3153, 3155);
  g->Binary(ynn_binary_multiply, 3155, 9533, 3156);
  g->Binary(ynn_binary_multiply, 9556, 8783, 3157);
  g->Binary(ynn_binary_add, 3156, 3157, 3158);
  g->Binary(ynn_binary_multiply, 3158, 8777, 3159);
  g->Quantize(3147, 3160, 0.21285858750343323, 0);
  g->Transpose(9235, 6459, {1,0});
  g->Binary(ynn_binary_multiply, 6457, 6458, 6455);
  g->Dot(3160, 6459, YNN_INVALID_VALUE_ID, 6454, 1);
  g->DequantizeTensor(6454, YNN_INVALID_VALUE_ID, 6455, 6456);
  g->QuantizeTensor(6456, 8727, 5663, 3161);
  g->Dequantize(3161, 3162, 0.1761811226606369, 0);
  g->Polynomial(3162, 8163, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8163, 8164);
  g->Binary(ynn_binary_add, 8164, 7293, 8161);
  g->Binary(ynn_binary_multiply, 3162, 7305, 8162);
  g->Binary(ynn_binary_multiply, 8162, 8161, 3163);
  g->Binary(ynn_binary_multiply, 3163, 3159, 3164);
  g->Quantize(3164, 3166, 1.425196886062622, 0);
  g->Transpose(9236, 6466, {1,0});
  g->Binary(ynn_binary_multiply, 6463, 6465, 6461);
  g->Dot(3166, 6466, YNN_INVALID_VALUE_ID, 6460, 1);
  g->DequantizeTensor(6460, YNN_INVALID_VALUE_ID, 6461, 6462);
  g->QuantizeTensor(6462, 8727, 6464, 3167);
  g->Dequantize(3167, 3168, 0.3287595808506012, 0);
  g->Unary(ynn_unary_square, 3168, 3169);
  g->Reduce(ynn_reduce_sum, 3169, 8166, {2}, true);
  g->ShapeProduct(3169, 8165, {2});
  g->Binary(ynn_binary_divide, 8166, 8165, 3170);
  g->Binary(ynn_binary_add, 3170, 8779, 3171);
  g->Unary(ynn_unary_rsqrt, 3171, 3172);
  g->Binary(ynn_binary_multiply, 3168, 3172, 3173);
  g->Binary(ynn_binary_multiply, 3173, 9239, 3174);
  g->Binary(ynn_binary_add, 3147, 3174, 3175);
  g->Binary(ynn_binary_multiply, 3175, 9231, 3177);
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
  g->Quantize(3183, 3184, 0.2586514949798584, 0);
  g->Transpose(9274, 6473, {1,0});
  g->Binary(ynn_binary_multiply, 6470, 6472, 6468);
  g->Dot(3184, 6473, YNN_INVALID_VALUE_ID, 6467, 1);
  g->DequantizeTensor(6467, YNN_INVALID_VALUE_ID, 6468, 6469);
  g->QuantizeTensor(6469, 8727, 6471, 3185);
  g->Dequantize(3185, 3186, 0.26771652698516846, 0);
  g->SplitDim(3186, 3188, 2, {8,256});
  g->FuseDims(3188, 3190, 1, 2);
  g->SplitDim(3190, 3189, 1, {8,1});
  g->Unary(ynn_unary_square, 3189, 3191);
  g->Reduce(ynn_reduce_sum, 3191, 8172, {3}, true);
  g->ShapeProduct(3191, 8171, {3});
  g->Binary(ynn_binary_divide, 8172, 8171, 3192);
  g->Binary(ynn_binary_add, 3192, 8779, 3193);
  g->Unary(ynn_unary_rsqrt, 3193, 3194);
  g->Binary(ynn_binary_multiply, 3189, 3194, 3195);
  g->Binary(ynn_binary_multiply, 3195, 9273, 3196);
  g->Slice(3196, 3197, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3196, 3198, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3198, 3200);
  g->Concat({3200,3197}, 3201, 3);
  g->Binary(ynn_binary_multiply, 3196, 3231, 3202);
  g->Binary(ynn_binary_multiply, 3201, 4329, 3203);
  g->Binary(ynn_binary_add, 3202, 3203, 3204);
}

// Scope: "Layer30 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer30AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9640, 3205, 0.0059552486054599285, 0);
  g->Dequantize(9664, 3206, 0.047244105488061905, 0);
  g->Slice(3204, 3207, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(3205, 3208, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(3206, 3209, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(3207, 3208, 3211, false, true);
  g->Mask(3211, 8832, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8832, 8176, {-1}, true);
  g->Binary(ynn_binary_subtract, 8832, 8176, 8173);
  g->Unary(ynn_unary_exp, 8173, 8174);
  g->Reduce(ynn_reduce_sum, 8174, 8177, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 8177, 8175);
  g->Binary(ynn_binary_multiply, 8174, 8175, 3212);
  g->Matmul(3212, 3209, 3213, false, false);
  g->Slice(3204, 3214, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(3205, 3215, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(3206, 3216, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(3214, 3215, 3217, false, true);
  g->Mask(3217, 8833, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8833, 8181, {-1}, true);
  g->Binary(ynn_binary_subtract, 8833, 8181, 8178);
  g->Unary(ynn_unary_exp, 8178, 8179);
  g->Reduce(ynn_reduce_sum, 8179, 8182, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 8182, 8180);
  g->Binary(ynn_binary_multiply, 8179, 8180, 3218);
  g->Matmul(3218, 3216, 3220, false, false);
  g->Concat({3213,3220}, 3221, 1);
}

// Scope: "Layer30 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer30AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(3221, 3223, 1, 2);
  g->SplitDim(3223, 3222, 1, {1,8});
  g->FuseDims(3222, 3224, 2, 2);
  g->Quantize(3224, 3225, 0.019192922860383987, 0);
  g->Transpose(9272, 6480, {1,0});
  g->Binary(ynn_binary_multiply, 6477, 6479, 6475);
  g->Dot(3225, 6480, YNN_INVALID_VALUE_ID, 6474, 1);
  g->DequantizeTensor(6474, YNN_INVALID_VALUE_ID, 6475, 6476);
  g->QuantizeTensor(6476, 8727, 6478, 3226);
  g->Dequantize(3226, 3227, 0.07175232470035553, 0);
}

// Scope: "Layer30 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer30Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3177, 3178);
  g->Reduce(ynn_reduce_sum, 3178, 8168, {2}, true);
  g->ShapeProduct(3178, 8167, {2});
  g->Binary(ynn_binary_divide, 8168, 8167, 3179);
  g->Binary(ynn_binary_add, 3179, 8779, 3180);
  g->Unary(ynn_unary_rsqrt, 3180, 3181);
  g->Binary(ynn_binary_multiply, 3177, 3181, 3182);
  g->Binary(ynn_binary_multiply, 3182, 9261, 3183);
  BuildLayer30AttentionQueryProjection(ctx);
  BuildLayer30AttentionSdpa(ctx);
  BuildLayer30AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 3227, 3228);
  g->Reduce(ynn_reduce_sum, 3228, 8184, {2}, true);
  g->ShapeProduct(3228, 8183, {2});
  g->Binary(ynn_binary_divide, 8184, 8183, 3229);
  g->Binary(ynn_binary_add, 3229, 8779, 3230);
  g->Unary(ynn_unary_rsqrt, 3230, 3234);
  g->Binary(ynn_binary_multiply, 3227, 3234, 3235);
  g->Binary(ynn_binary_multiply, 3235, 9268, 3236);
  g->Binary(ynn_binary_add, 3236, 3177, 3237);
}

// Scope: "Layer30 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer30Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3237, 3238);
  g->Reduce(ynn_reduce_sum, 3238, 8186, {2}, true);
  g->ShapeProduct(3238, 8185, {2});
  g->Binary(ynn_binary_divide, 8186, 8185, 3239);
  g->Binary(ynn_binary_add, 3239, 8779, 3240);
  g->Unary(ynn_unary_rsqrt, 3240, 3241);
  g->Binary(ynn_binary_multiply, 3237, 3241, 3242);
  g->Binary(ynn_binary_multiply, 3242, 9271, 3243);
  g->Quantize(3243, 3245, 0.020873267203569412, 0);
  g->Transpose(9265, 6491, {1,0});
  g->Binary(ynn_binary_multiply, 6489, 6490, 6487);
  g->Dot(3245, 6491, YNN_INVALID_VALUE_ID, 6486, 1);
  g->DequantizeTensor(6486, YNN_INVALID_VALUE_ID, 6487, 6488);
  g->QuantizeTensor(6488, 8727, 6054, 3246);
  g->Dequantize(3246, 3247, 0.0274360328912735, 0);
  g->Transpose(9264, 6496, {1,0});
  g->Binary(ynn_binary_multiply, 6489, 6495, 6493);
  g->Dot(3245, 6496, YNN_INVALID_VALUE_ID, 6492, 1);
  g->DequantizeTensor(6492, YNN_INVALID_VALUE_ID, 6493, 6494);
  g->QuantizeTensor(6494, 8727, 6054, 3248);
  g->Dequantize(3248, 3249, 0.0274360328912735, 0);
  g->Polynomial(3249, 8189, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8189, 8190);
  g->Binary(ynn_binary_add, 8190, 7293, 8187);
  g->Binary(ynn_binary_multiply, 3249, 7305, 8188);
  g->Binary(ynn_binary_multiply, 8188, 8187, 3250);
  g->Binary(ynn_binary_multiply, 3247, 3250, 3251);
  g->Quantize(3251, 3252, 0.027805127203464508, 0);
  g->Transpose(9263, 6503, {1,0});
  g->Binary(ynn_binary_multiply, 6500, 6502, 6498);
  g->Dot(3252, 6503, YNN_INVALID_VALUE_ID, 6497, 1);
  g->DequantizeTensor(6497, YNN_INVALID_VALUE_ID, 6498, 6499);
  g->QuantizeTensor(6499, 8727, 6501, 3253);
  g->Dequantize(3253, 3255, 0.014151409268379211, 0);
  g->Unary(ynn_unary_square, 3255, 3256);
  g->Reduce(ynn_reduce_sum, 3256, 8192, {2}, true);
  g->ShapeProduct(3256, 8191, {2});
  g->Binary(ynn_binary_divide, 8192, 8191, 3257);
  g->Binary(ynn_binary_add, 3257, 8779, 3258);
  g->Unary(ynn_unary_rsqrt, 3258, 3259);
  g->Binary(ynn_binary_multiply, 3255, 3259, 3260);
  g->Binary(ynn_binary_multiply, 3260, 9269, 3261);
  g->Binary(ynn_binary_add, 3261, 3237, 3262);
}

// Scope: "Layer30 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer30PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(429, 3263, {0,0,30,0}, {-1,-1,1,-1});
  g->Reshape(3263, 3264, {1,1,256});
  g->Unary(ynn_unary_square, 3264, 3266);
  g->Reduce(ynn_reduce_sum, 3266, 8194, {2}, true);
  g->ShapeProduct(3266, 8193, {2});
  g->Binary(ynn_binary_divide, 8194, 8193, 3267);
  g->Binary(ynn_binary_add, 3267, 8779, 3268);
  g->Unary(ynn_unary_rsqrt, 3268, 3269);
  g->Binary(ynn_binary_multiply, 3264, 3269, 3270);
  g->Binary(ynn_binary_multiply, 3270, 9533, 3271);
  g->Binary(ynn_binary_multiply, 9558, 8783, 3272);
  g->Binary(ynn_binary_add, 3271, 3272, 3273);
  g->Binary(ynn_binary_multiply, 3273, 8777, 3274);
  g->Quantize(3262, 3275, 0.13111315667629242, 0);
  g->Transpose(9266, 6510, {1,0});
  g->Binary(ynn_binary_multiply, 6507, 6509, 6505);
  g->Dot(3275, 6510, YNN_INVALID_VALUE_ID, 6504, 1);
  g->DequantizeTensor(6504, YNN_INVALID_VALUE_ID, 6505, 6506);
  g->QuantizeTensor(6506, 8727, 6508, 3277);
  g->Dequantize(3277, 3278, 0.25590550899505615, 0);
  g->Polynomial(3278, 8197, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8197, 8198);
  g->Binary(ynn_binary_add, 8198, 7293, 8195);
  g->Binary(ynn_binary_multiply, 3278, 7305, 8196);
  g->Binary(ynn_binary_multiply, 8196, 8195, 3279);
  g->Binary(ynn_binary_multiply, 3279, 3274, 3280);
  g->Quantize(3280, 3281, 2.236220359802246, 0);
  g->Transpose(9267, 6517, {1,0});
  g->Binary(ynn_binary_multiply, 6514, 6516, 6512);
  g->Dot(3281, 6517, YNN_INVALID_VALUE_ID, 6511, 1);
  g->DequantizeTensor(6511, YNN_INVALID_VALUE_ID, 6512, 6513);
  g->QuantizeTensor(6513, 8727, 6515, 3282);
  g->Dequantize(3282, 3283, 0.5313407778739929, 0);
  g->Unary(ynn_unary_square, 3283, 3284);
  g->Reduce(ynn_reduce_sum, 3284, 8200, {2}, true);
  g->ShapeProduct(3284, 8199, {2});
  g->Binary(ynn_binary_divide, 8200, 8199, 3285);
  g->Binary(ynn_binary_add, 3285, 8779, 3286);
  g->Unary(ynn_unary_rsqrt, 3286, 3288);
  g->Binary(ynn_binary_multiply, 3283, 3288, 3289);
  g->Binary(ynn_binary_multiply, 3289, 9270, 3290);
  g->Binary(ynn_binary_add, 3262, 3290, 3291);
  g->Binary(ynn_binary_multiply, 3291, 9262, 3292);
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
  g->Quantize(3299, 3300, 0.3303837180137634, 0);
  g->Transpose(9288, 6524, {1,0});
  g->Binary(ynn_binary_multiply, 6521, 6523, 6519);
  g->Dot(3300, 6524, YNN_INVALID_VALUE_ID, 6518, 1);
  g->DequantizeTensor(6518, YNN_INVALID_VALUE_ID, 6519, 6520);
  g->QuantizeTensor(6520, 8727, 6522, 3301);
  g->Dequantize(3301, 3302, 0.3208661377429962, 0);
  g->SplitDim(3302, 3303, 2, {8,256});
  g->FuseDims(3303, 3305, 1, 2);
  g->SplitDim(3305, 3304, 1, {8,1});
  g->Unary(ynn_unary_square, 3304, 3306);
  g->Reduce(ynn_reduce_sum, 3306, 8206, {3}, true);
  g->ShapeProduct(3306, 8205, {3});
  g->Binary(ynn_binary_divide, 8206, 8205, 3307);
  g->Binary(ynn_binary_add, 3307, 8779, 3308);
  g->Unary(ynn_unary_rsqrt, 3308, 3309);
  g->Binary(ynn_binary_multiply, 3304, 3309, 3311);
  g->Binary(ynn_binary_multiply, 3311, 9287, 3312);
  g->Slice(3312, 3313, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3312, 3314, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3314, 3315);
  g->Concat({3315,3313}, 3316, 3);
  g->Binary(ynn_binary_multiply, 3312, 3231, 3317);
  g->Binary(ynn_binary_multiply, 3316, 4329, 3318);
  g->Binary(ynn_binary_add, 3317, 3318, 3319);
}

// Scope: "Layer31 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer31AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9640, 3320, 0.0059552486054599285, 0);
  g->Dequantize(9664, 3322, 0.047244105488061905, 0);
  g->Slice(3319, 3323, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(3320, 3324, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(3322, 3325, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(3323, 3324, 3326, false, true);
  g->Mask(3326, 8834, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8834, 8210, {-1}, true);
  g->Binary(ynn_binary_subtract, 8834, 8210, 8207);
  g->Unary(ynn_unary_exp, 8207, 8208);
  g->Reduce(ynn_reduce_sum, 8208, 8211, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 8211, 8209);
  g->Binary(ynn_binary_multiply, 8208, 8209, 3327);
  g->Matmul(3327, 3325, 3328, false, false);
  g->Slice(3319, 3329, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(3320, 3330, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(3322, 3332, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(3329, 3330, 3333, false, true);
  g->Mask(3333, 8835, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8835, 8215, {-1}, true);
  g->Binary(ynn_binary_subtract, 8835, 8215, 8212);
  g->Unary(ynn_unary_exp, 8212, 8213);
  g->Reduce(ynn_reduce_sum, 8213, 8216, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 8216, 8214);
  g->Binary(ynn_binary_multiply, 8213, 8214, 3334);
  g->Matmul(3334, 3332, 3335, false, false);
  g->Concat({3328,3335}, 3336, 1);
}

// Scope: "Layer31 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer31AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(3336, 3338, 1, 2);
  g->SplitDim(3338, 3337, 1, {1,8});
  g->FuseDims(3337, 3339, 2, 2);
  g->Quantize(3339, 3340, 0.019808080047369003, 0);
  g->Transpose(9286, 6530, {1,0});
  g->Binary(ynn_binary_multiply, 6043, 6529, 6526);
  g->Dot(3340, 6530, YNN_INVALID_VALUE_ID, 6525, 1);
  g->DequantizeTensor(6525, YNN_INVALID_VALUE_ID, 6526, 6527);
  g->QuantizeTensor(6527, 8727, 6528, 3341);
  g->Dequantize(3341, 3344, 0.12575629353523254, 0);
}

// Scope: "Layer31 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer31Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3292, 3293);
  g->Reduce(ynn_reduce_sum, 3293, 8204, {2}, true);
  g->ShapeProduct(3293, 8203, {2});
  g->Binary(ynn_binary_divide, 8204, 8203, 3294);
  g->Binary(ynn_binary_add, 3294, 8779, 3295);
  g->Unary(ynn_unary_rsqrt, 3295, 3296);
  g->Binary(ynn_binary_multiply, 3292, 3296, 3297);
  g->Binary(ynn_binary_multiply, 3297, 9275, 3299);
  BuildLayer31AttentionQueryProjection(ctx);
  BuildLayer31AttentionSdpa(ctx);
  BuildLayer31AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 3344, 3345);
  g->Reduce(ynn_reduce_sum, 3345, 8218, {2}, true);
  g->ShapeProduct(3345, 8217, {2});
  g->Binary(ynn_binary_divide, 8218, 8217, 3346);
  g->Binary(ynn_binary_add, 3346, 8779, 3347);
  g->Unary(ynn_unary_rsqrt, 3347, 3348);
  g->Binary(ynn_binary_multiply, 3344, 3348, 3349);
  g->Binary(ynn_binary_multiply, 3349, 9282, 3350);
  g->Binary(ynn_binary_add, 3350, 3292, 3351);
}

// Scope: "Layer31 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer31Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3351, 3352);
  g->Reduce(ynn_reduce_sum, 3352, 8220, {2}, true);
  g->ShapeProduct(3352, 8219, {2});
  g->Binary(ynn_binary_divide, 8220, 8219, 3353);
  g->Binary(ynn_binary_add, 3353, 8779, 3355);
  g->Unary(ynn_unary_rsqrt, 3355, 3356);
  g->Binary(ynn_binary_multiply, 3351, 3356, 3357);
  g->Binary(ynn_binary_multiply, 3357, 9285, 3358);
  g->Quantize(3358, 3359, 0.019890448078513145, 0);
  g->Transpose(9279, 6536, {1,0});
  g->Binary(ynn_binary_multiply, 6534, 6535, 6532);
  g->Dot(3359, 6536, YNN_INVALID_VALUE_ID, 6531, 1);
  g->DequantizeTensor(6531, YNN_INVALID_VALUE_ID, 6532, 6533);
  g->QuantizeTensor(6533, 8727, 5235, 3360);
  g->Dequantize(3360, 3361, 0.025836624205112457, 0);
  g->Transpose(9278, 6541, {1,0});
  g->Binary(ynn_binary_multiply, 6534, 6540, 6538);
  g->Dot(3359, 6541, YNN_INVALID_VALUE_ID, 6537, 1);
  g->DequantizeTensor(6537, YNN_INVALID_VALUE_ID, 6538, 6539);
  g->QuantizeTensor(6539, 8727, 5235, 3362);
  g->Dequantize(3362, 3363, 0.025836624205112457, 0);
  g->Polynomial(3363, 8223, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8223, 8224);
  g->Binary(ynn_binary_add, 8224, 7293, 8221);
  g->Binary(ynn_binary_multiply, 3363, 7305, 8222);
  g->Binary(ynn_binary_multiply, 8222, 8221, 3365);
  g->Binary(ynn_binary_multiply, 3361, 3365, 3366);
  g->Quantize(3366, 3367, 0.03248032554984093, 0);
  g->Transpose(9277, 6548, {1,0});
  g->Binary(ynn_binary_multiply, 6545, 6547, 6543);
  g->Dot(3367, 6548, YNN_INVALID_VALUE_ID, 6542, 1);
  g->DequantizeTensor(6542, YNN_INVALID_VALUE_ID, 6543, 6544);
  g->QuantizeTensor(6544, 8727, 6546, 3368);
  g->Dequantize(3368, 3369, 0.018060656264424324, 0);
  g->Unary(ynn_unary_square, 3369, 3370);
  g->Reduce(ynn_reduce_sum, 3370, 8226, {2}, true);
  g->ShapeProduct(3370, 8225, {2});
  g->Binary(ynn_binary_divide, 8226, 8225, 3371);
  g->Binary(ynn_binary_add, 3371, 8779, 3372);
  g->Unary(ynn_unary_rsqrt, 3372, 3373);
  g->Binary(ynn_binary_multiply, 3369, 3373, 3374);
  g->Binary(ynn_binary_multiply, 3374, 9283, 3376);
  g->Binary(ynn_binary_add, 3376, 3351, 3377);
}

// Scope: "Layer31 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer31PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(429, 3378, {0,0,31,0}, {-1,-1,1,-1});
  g->Reshape(3378, 3379, {1,1,256});
  g->Unary(ynn_unary_square, 3379, 3380);
  g->Reduce(ynn_reduce_sum, 3380, 8228, {2}, true);
  g->ShapeProduct(3380, 8227, {2});
  g->Binary(ynn_binary_divide, 8228, 8227, 3381);
  g->Binary(ynn_binary_add, 3381, 8779, 3382);
  g->Unary(ynn_unary_rsqrt, 3382, 3383);
  g->Binary(ynn_binary_multiply, 3379, 3383, 3384);
  g->Binary(ynn_binary_multiply, 3384, 9533, 3385);
  g->Binary(ynn_binary_multiply, 9559, 8783, 3387);
  g->Binary(ynn_binary_add, 3385, 3387, 3388);
  g->Binary(ynn_binary_multiply, 3388, 8777, 3389);
  g->Quantize(3377, 3390, 0.1624065637588501, 0);
  g->Transpose(9280, 6562, {1,0});
  g->Binary(ynn_binary_multiply, 6559, 6561, 6557);
  g->Dot(3390, 6562, YNN_INVALID_VALUE_ID, 6556, 1);
  g->DequantizeTensor(6556, YNN_INVALID_VALUE_ID, 6557, 6558);
  g->QuantizeTensor(6558, 8727, 6560, 3391);
  g->Dequantize(3391, 3392, 0.20078741014003754, 0);
  g->Polynomial(3392, 8231, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8231, 8232);
  g->Binary(ynn_binary_add, 8232, 7293, 8229);
  g->Binary(ynn_binary_multiply, 3392, 7305, 8230);
  g->Binary(ynn_binary_multiply, 8230, 8229, 3393);
  g->Binary(ynn_binary_multiply, 3393, 3389, 3394);
  g->Quantize(3394, 3395, 1.7559055089950562, 0);
  g->Transpose(9281, 6569, {1,0});
  g->Binary(ynn_binary_multiply, 6566, 6568, 6564);
  g->Dot(3395, 6569, YNN_INVALID_VALUE_ID, 6563, 1);
  g->DequantizeTensor(6563, YNN_INVALID_VALUE_ID, 6564, 6565);
  g->QuantizeTensor(6565, 8727, 6567, 3396);
  g->Dequantize(3396, 3398, 0.38641682267189026, 0);
  g->Unary(ynn_unary_square, 3398, 3399);
  g->Reduce(ynn_reduce_sum, 3399, 8234, {2}, true);
  g->ShapeProduct(3399, 8233, {2});
  g->Binary(ynn_binary_divide, 8234, 8233, 3400);
  g->Binary(ynn_binary_add, 3400, 8779, 3401);
  g->Unary(ynn_unary_rsqrt, 3401, 3402);
  g->Binary(ynn_binary_multiply, 3398, 3402, 3403);
  g->Binary(ynn_binary_multiply, 3403, 9284, 3404);
  g->Binary(ynn_binary_add, 3377, 3404, 3405);
  g->Binary(ynn_binary_multiply, 3405, 9276, 3406);
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
  g->Quantize(3413, 3414, 0.3205936551094055, 0);
  g->Transpose(9302, 6575, {1,0});
  g->Binary(ynn_binary_multiply, 6573, 6574, 6571);
  g->Dot(3414, 6575, YNN_INVALID_VALUE_ID, 6570, 1);
  g->DequantizeTensor(6570, YNN_INVALID_VALUE_ID, 6571, 6572);
  g->QuantizeTensor(6572, 8727, 5150, 3415);
  g->Dequantize(3415, 3416, 0.31102362275123596, 0);
  g->SplitDim(3416, 3417, 2, {8,256});
  g->FuseDims(3417, 3419, 1, 2);
  g->SplitDim(3419, 3418, 1, {8,1});
  g->Unary(ynn_unary_square, 3418, 3421);
  g->Reduce(ynn_reduce_sum, 3421, 8242, {3}, true);
  g->ShapeProduct(3421, 8241, {3});
  g->Binary(ynn_binary_divide, 8242, 8241, 3422);
  g->Binary(ynn_binary_add, 3422, 8779, 3423);
  g->Unary(ynn_unary_rsqrt, 3423, 3424);
  g->Binary(ynn_binary_multiply, 3418, 3424, 3425);
  g->Binary(ynn_binary_multiply, 3425, 9301, 3426);
  g->Slice(3426, 3427, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3426, 3428, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3428, 3429);
  g->Concat({3429,3427}, 3430, 3);
  g->Binary(ynn_binary_multiply, 3426, 3231, 3432);
  g->Binary(ynn_binary_multiply, 3430, 4329, 3433);
  g->Binary(ynn_binary_add, 3432, 3433, 3434);
}

// Scope: "Layer32 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer32AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9640, 3435, 0.0059552486054599285, 0);
  g->Dequantize(9664, 3436, 0.047244105488061905, 0);
  g->Slice(3434, 3437, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(3435, 3438, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(3436, 3439, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(3437, 3438, 3440, false, true);
  g->Mask(3440, 8836, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8836, 8246, {-1}, true);
  g->Binary(ynn_binary_subtract, 8836, 8246, 8243);
  g->Unary(ynn_unary_exp, 8243, 8244);
  g->Reduce(ynn_reduce_sum, 8244, 8247, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 8247, 8245);
  g->Binary(ynn_binary_multiply, 8244, 8245, 3442);
  g->Matmul(3442, 3439, 3443, false, false);
  g->Slice(3434, 3444, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(3435, 3445, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(3436, 3446, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(3444, 3445, 3447, false, true);
  g->Mask(3447, 8837, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8837, 8251, {-1}, true);
  g->Binary(ynn_binary_subtract, 8837, 8251, 8248);
  g->Unary(ynn_unary_exp, 8248, 8249);
  g->Reduce(ynn_reduce_sum, 8249, 8252, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 8252, 8250);
  g->Binary(ynn_binary_multiply, 8249, 8250, 3448);
  g->Matmul(3448, 3446, 3449, false, false);
  g->Concat({3443,3449}, 3450, 1);
}

// Scope: "Layer32 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer32AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(3450, 3454, 1, 2);
  g->SplitDim(3454, 3453, 1, {1,8});
  g->FuseDims(3453, 3455, 2, 2);
  g->Quantize(3455, 3456, 0.019562017172574997, 0);
  g->Transpose(9300, 6589, {1,0});
  g->Binary(ynn_binary_multiply, 6586, 6588, 6584);
  g->Dot(3456, 6589, YNN_INVALID_VALUE_ID, 6583, 1);
  g->DequantizeTensor(6583, YNN_INVALID_VALUE_ID, 6584, 6585);
  g->QuantizeTensor(6585, 8727, 6587, 3457);
  g->Dequantize(3457, 3458, 0.08170928806066513, 0);
}

// Scope: "Layer32 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer32Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3406, 3407);
  g->Reduce(ynn_reduce_sum, 3407, 8240, {2}, true);
  g->ShapeProduct(3407, 8239, {2});
  g->Binary(ynn_binary_divide, 8240, 8239, 3409);
  g->Binary(ynn_binary_add, 3409, 8779, 3410);
  g->Unary(ynn_unary_rsqrt, 3410, 3411);
  g->Binary(ynn_binary_multiply, 3406, 3411, 3412);
  g->Binary(ynn_binary_multiply, 3412, 9289, 3413);
  BuildLayer32AttentionQueryProjection(ctx);
  BuildLayer32AttentionSdpa(ctx);
  BuildLayer32AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 3458, 3459);
  g->Reduce(ynn_reduce_sum, 3459, 8254, {2}, true);
  g->ShapeProduct(3459, 8253, {2});
  g->Binary(ynn_binary_divide, 8254, 8253, 3460);
  g->Binary(ynn_binary_add, 3460, 8779, 3461);
  g->Unary(ynn_unary_rsqrt, 3461, 3462);
  g->Binary(ynn_binary_multiply, 3458, 3462, 3463);
  g->Binary(ynn_binary_multiply, 3463, 9296, 3465);
  g->Binary(ynn_binary_add, 3465, 3406, 3466);
}

// Scope: "Layer32 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer32Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3466, 3467);
  g->Reduce(ynn_reduce_sum, 3467, 8256, {2}, true);
  g->ShapeProduct(3467, 8255, {2});
  g->Binary(ynn_binary_divide, 8256, 8255, 3468);
  g->Binary(ynn_binary_add, 3468, 8779, 3469);
  g->Unary(ynn_unary_rsqrt, 3469, 3470);
  g->Binary(ynn_binary_multiply, 3466, 3470, 3471);
  g->Binary(ynn_binary_multiply, 3471, 9299, 3472);
  g->Quantize(3472, 3473, 0.025895588099956512, 0);
  g->Transpose(9293, 6596, {1,0});
  g->Binary(ynn_binary_multiply, 6593, 6595, 6591);
  g->Dot(3473, 6596, YNN_INVALID_VALUE_ID, 6590, 1);
  g->DequantizeTensor(6590, YNN_INVALID_VALUE_ID, 6591, 6592);
  g->QuantizeTensor(6592, 8727, 6594, 3474);
  g->Dequantize(3474, 3476, 0.039862215518951416, 0);
  g->Transpose(9292, 6601, {1,0});
  g->Binary(ynn_binary_multiply, 6593, 6600, 6598);
  g->Dot(3473, 6601, YNN_INVALID_VALUE_ID, 6597, 1);
  g->DequantizeTensor(6597, YNN_INVALID_VALUE_ID, 6598, 6599);
  g->QuantizeTensor(6599, 8727, 6594, 3477);
  g->Dequantize(3477, 3478, 0.039862215518951416, 0);
  g->Polynomial(3478, 8261, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8261, 8262);
  g->Binary(ynn_binary_add, 8262, 7293, 8259);
  g->Binary(ynn_binary_multiply, 3478, 7305, 8260);
  g->Binary(ynn_binary_multiply, 8260, 8259, 3479);
  g->Binary(ynn_binary_multiply, 3476, 3479, 3480);
  g->Quantize(3480, 3481, 0.0664370134472847, 0);
  g->Transpose(9291, 6607, {1,0});
  g->Binary(ynn_binary_multiply, 5350, 6606, 6603);
  g->Dot(3481, 6607, YNN_INVALID_VALUE_ID, 6602, 1);
  g->DequantizeTensor(6602, YNN_INVALID_VALUE_ID, 6603, 6604);
  g->QuantizeTensor(6604, 8727, 6605, 3482);
  g->Dequantize(3482, 3483, 0.028853626921772957, 0);
  g->Unary(ynn_unary_square, 3483, 3484);
  g->Reduce(ynn_reduce_sum, 3484, 8264, {2}, true);
  g->ShapeProduct(3484, 8263, {2});
  g->Binary(ynn_binary_divide, 8264, 8263, 3486);
  g->Binary(ynn_binary_add, 3486, 8779, 3487);
  g->Unary(ynn_unary_rsqrt, 3487, 3488);
  g->Binary(ynn_binary_multiply, 3483, 3488, 3489);
  g->Binary(ynn_binary_multiply, 3489, 9297, 3490);
  g->Binary(ynn_binary_add, 3490, 3466, 3491);
}

// Scope: "Layer32 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer32PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(429, 3492, {0,0,32,0}, {-1,-1,1,-1});
  g->Reshape(3492, 3493, {1,1,256});
  g->Unary(ynn_unary_square, 3493, 3494);
  g->Reduce(ynn_reduce_sum, 3494, 8266, {2}, true);
  g->ShapeProduct(3494, 8265, {2});
  g->Binary(ynn_binary_divide, 8266, 8265, 3495);
  g->Binary(ynn_binary_add, 3495, 8779, 3497);
  g->Unary(ynn_unary_rsqrt, 3497, 3498);
  g->Binary(ynn_binary_multiply, 3493, 3498, 3499);
  g->Binary(ynn_binary_multiply, 3499, 9533, 3500);
  g->Binary(ynn_binary_multiply, 9560, 8783, 3501);
  g->Binary(ynn_binary_add, 3500, 3501, 3502);
  g->Binary(ynn_binary_multiply, 3502, 8777, 3503);
  g->Quantize(3491, 3504, 0.1705654412508011, 0);
  g->Transpose(9294, 6614, {1,0});
  g->Binary(ynn_binary_multiply, 6611, 6613, 6609);
  g->Dot(3504, 6614, YNN_INVALID_VALUE_ID, 6608, 1);
  g->DequantizeTensor(6608, YNN_INVALID_VALUE_ID, 6609, 6610);
  g->QuantizeTensor(6610, 8727, 6612, 3505);
  g->Dequantize(3505, 3506, 0.23228347301483154, 0);
  g->Polynomial(3506, 8269, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8269, 8270);
  g->Binary(ynn_binary_add, 8270, 7293, 8267);
  g->Binary(ynn_binary_multiply, 3506, 7305, 8268);
  g->Binary(ynn_binary_multiply, 8268, 8267, 3508);
  g->Binary(ynn_binary_multiply, 3508, 3503, 3509);
  g->Quantize(3509, 3510, 1.881889820098877, 0);
  g->Transpose(9295, 6621, {1,0});
  g->Binary(ynn_binary_multiply, 6618, 6620, 6616);
  g->Dot(3510, 6621, YNN_INVALID_VALUE_ID, 6615, 1);
  g->DequantizeTensor(6615, YNN_INVALID_VALUE_ID, 6616, 6617);
  g->QuantizeTensor(6617, 8727, 6619, 3511);
  g->Dequantize(3511, 3512, 0.341701865196228, 0);
  g->Unary(ynn_unary_square, 3512, 3513);
  g->Reduce(ynn_reduce_sum, 3513, 8272, {2}, true);
  g->ShapeProduct(3513, 8271, {2});
  g->Binary(ynn_binary_divide, 8272, 8271, 3514);
  g->Binary(ynn_binary_add, 3514, 8779, 3515);
  g->Unary(ynn_unary_rsqrt, 3515, 3516);
  g->Binary(ynn_binary_multiply, 3512, 3516, 3517);
  g->Binary(ynn_binary_multiply, 3517, 9298, 3519);
  g->Binary(ynn_binary_add, 3491, 3519, 3520);
  g->Binary(ynn_binary_multiply, 3520, 9290, 3521);
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
  g->Quantize(3527, 3528, 0.248324915766716, 0);
  g->Transpose(9316, 6628, {1,0});
  g->Binary(ynn_binary_multiply, 6625, 6627, 6623);
  g->Dot(3528, 6628, YNN_INVALID_VALUE_ID, 6622, 1);
  g->DequantizeTensor(6622, YNN_INVALID_VALUE_ID, 6623, 6624);
  g->QuantizeTensor(6624, 8727, 6626, 3530);
  g->Dequantize(3530, 3531, 0.2893700897693634, 0);
  g->SplitDim(3531, 3532, 2, {8,256});
  g->FuseDims(3532, 3534, 1, 2);
  g->SplitDim(3534, 3533, 1, {8,1});
  g->Unary(ynn_unary_square, 3533, 3535);
  g->Reduce(ynn_reduce_sum, 3535, 8276, {3}, true);
  g->ShapeProduct(3535, 8275, {3});
  g->Binary(ynn_binary_divide, 8276, 8275, 3536);
  g->Binary(ynn_binary_add, 3536, 8779, 3537);
  g->Unary(ynn_unary_rsqrt, 3537, 3538);
  g->Binary(ynn_binary_multiply, 3533, 3538, 3539);
  g->Binary(ynn_binary_multiply, 3539, 9315, 3540);
  g->Slice(3540, 3542, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3540, 3543, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3543, 3544);
  g->Concat({3544,3542}, 3545, 3);
  g->Binary(ynn_binary_multiply, 3540, 3231, 3546);
  g->Binary(ynn_binary_multiply, 3545, 4329, 3547);
  g->Binary(ynn_binary_add, 3546, 3547, 3548);
}

// Scope: "Layer33 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer33AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9640, 3549, 0.0059552486054599285, 0);
  g->Dequantize(9664, 3550, 0.047244105488061905, 0);
  g->Slice(3548, 3551, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(3549, 3553, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(3550, 3554, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(3551, 3553, 3555, false, true);
  g->Mask(3555, 8838, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8838, 8280, {-1}, true);
  g->Binary(ynn_binary_subtract, 8838, 8280, 8277);
  g->Unary(ynn_unary_exp, 8277, 8278);
  g->Reduce(ynn_reduce_sum, 8278, 8281, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 8281, 8279);
  g->Binary(ynn_binary_multiply, 8278, 8279, 3556);
  g->Matmul(3556, 3554, 3557, false, false);
  g->Slice(3548, 3558, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(3549, 3559, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(3550, 3560, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(3558, 3559, 3561, false, true);
  g->Mask(3561, 8839, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8839, 8287, {-1}, true);
  g->Binary(ynn_binary_subtract, 8839, 8287, 8284);
  g->Unary(ynn_unary_exp, 8284, 8285);
  g->Reduce(ynn_reduce_sum, 8285, 8288, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 8288, 8286);
  g->Binary(ynn_binary_multiply, 8285, 8286, 3565);
  g->Matmul(3565, 3560, 3566, false, false);
  g->Concat({3557,3566}, 3567, 1);
}

// Scope: "Layer33 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer33AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(3567, 3569, 1, 2);
  g->SplitDim(3569, 3568, 1, {1,8});
  g->FuseDims(3568, 3570, 2, 2);
  g->Quantize(3570, 3571, 0.019685048609972, 0);
  g->Transpose(9314, 6635, {1,0});
  g->Binary(ynn_binary_multiply, 6632, 6634, 6630);
  g->Dot(3571, 6635, YNN_INVALID_VALUE_ID, 6629, 1);
  g->DequantizeTensor(6629, YNN_INVALID_VALUE_ID, 6630, 6631);
  g->QuantizeTensor(6631, 8727, 6633, 3572);
  g->Dequantize(3572, 3573, 0.09176436066627502, 0);
}

// Scope: "Layer33 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer33Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3521, 3522);
  g->Reduce(ynn_reduce_sum, 3522, 8274, {2}, true);
  g->ShapeProduct(3522, 8273, {2});
  g->Binary(ynn_binary_divide, 8274, 8273, 3523);
  g->Binary(ynn_binary_add, 3523, 8779, 3524);
  g->Unary(ynn_unary_rsqrt, 3524, 3525);
  g->Binary(ynn_binary_multiply, 3521, 3525, 3526);
  g->Binary(ynn_binary_multiply, 3526, 9303, 3527);
  BuildLayer33AttentionQueryProjection(ctx);
  BuildLayer33AttentionSdpa(ctx);
  BuildLayer33AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 3573, 3574);
  g->Reduce(ynn_reduce_sum, 3574, 8290, {2}, true);
  g->ShapeProduct(3574, 8289, {2});
  g->Binary(ynn_binary_divide, 8290, 8289, 3576);
  g->Binary(ynn_binary_add, 3576, 8779, 3577);
  g->Unary(ynn_unary_rsqrt, 3577, 3578);
  g->Binary(ynn_binary_multiply, 3573, 3578, 3579);
  g->Binary(ynn_binary_multiply, 3579, 9310, 3580);
  g->Binary(ynn_binary_add, 3580, 3521, 3581);
}

// Scope: "Layer33 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer33Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3581, 3582);
  g->Reduce(ynn_reduce_sum, 3582, 8292, {2}, true);
  g->ShapeProduct(3582, 8291, {2});
  g->Binary(ynn_binary_divide, 8292, 8291, 3583);
  g->Binary(ynn_binary_add, 3583, 8779, 3584);
  g->Unary(ynn_unary_rsqrt, 3584, 3585);
  g->Binary(ynn_binary_multiply, 3581, 3585, 3587);
  g->Binary(ynn_binary_multiply, 3587, 9313, 3588);
  g->Quantize(3588, 3589, 0.025595715269446373, 0);
  g->Transpose(9307, 6642, {1,0});
  g->Binary(ynn_binary_multiply, 6639, 6641, 6637);
  g->Dot(3589, 6642, YNN_INVALID_VALUE_ID, 6636, 1);
  g->DequantizeTensor(6636, YNN_INVALID_VALUE_ID, 6637, 6638);
  g->QuantizeTensor(6638, 8727, 6640, 3590);
  g->Dequantize(3590, 3591, 0.03690946102142334, 0);
  g->Transpose(9306, 6647, {1,0});
  g->Binary(ynn_binary_multiply, 6639, 6646, 6644);
  g->Dot(3589, 6647, YNN_INVALID_VALUE_ID, 6643, 1);
  g->DequantizeTensor(6643, YNN_INVALID_VALUE_ID, 6644, 6645);
  g->QuantizeTensor(6645, 8727, 6640, 3592);
  g->Dequantize(3592, 3593, 0.03690946102142334, 0);
  g->Polynomial(3593, 8295, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8295, 8296);
  g->Binary(ynn_binary_add, 8296, 7293, 8293);
  g->Binary(ynn_binary_multiply, 3593, 7305, 8294);
  g->Binary(ynn_binary_multiply, 8294, 8293, 3594);
  g->Binary(ynn_binary_multiply, 3591, 3594, 3595);
  g->Quantize(3595, 3597, 0.06692913919687271, 0);
  g->Transpose(9305, 6654, {1,0});
  g->Binary(ynn_binary_multiply, 6651, 6653, 6649);
  g->Dot(3597, 6654, YNN_INVALID_VALUE_ID, 6648, 1);
  g->DequantizeTensor(6648, YNN_INVALID_VALUE_ID, 6649, 6650);
  g->QuantizeTensor(6650, 8727, 6652, 3598);
  g->Dequantize(3598, 3599, 0.033670417964458466, 0);
  g->Unary(ynn_unary_square, 3599, 3600);
  g->Reduce(ynn_reduce_sum, 3600, 8298, {2}, true);
  g->ShapeProduct(3600, 8297, {2});
  g->Binary(ynn_binary_divide, 8298, 8297, 3601);
  g->Binary(ynn_binary_add, 3601, 8779, 3602);
  g->Unary(ynn_unary_rsqrt, 3602, 3603);
  g->Binary(ynn_binary_multiply, 3599, 3603, 3604);
  g->Binary(ynn_binary_multiply, 3604, 9311, 3605);
  g->Binary(ynn_binary_add, 3605, 3581, 3606);
}

// Scope: "Layer33 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer33PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(429, 3608, {0,0,33,0}, {-1,-1,1,-1});
  g->Reshape(3608, 3609, {1,1,256});
  g->Unary(ynn_unary_square, 3609, 3610);
  g->Reduce(ynn_reduce_sum, 3610, 8300, {2}, true);
  g->ShapeProduct(3610, 8299, {2});
  g->Binary(ynn_binary_divide, 8300, 8299, 3611);
  g->Binary(ynn_binary_add, 3611, 8779, 3612);
  g->Unary(ynn_unary_rsqrt, 3612, 3613);
  g->Binary(ynn_binary_multiply, 3609, 3613, 3614);
  g->Binary(ynn_binary_multiply, 3614, 9533, 3615);
  g->Binary(ynn_binary_multiply, 9561, 8783, 3616);
  g->Binary(ynn_binary_add, 3615, 3616, 3617);
  g->Binary(ynn_binary_multiply, 3617, 8777, 3619);
  g->Quantize(3606, 3620, 0.1833108365535736, 0);
  g->Transpose(9308, 6661, {1,0});
  g->Binary(ynn_binary_multiply, 6658, 6660, 6656);
  g->Dot(3620, 6661, YNN_INVALID_VALUE_ID, 6655, 1);
  g->DequantizeTensor(6655, YNN_INVALID_VALUE_ID, 6656, 6657);
  g->QuantizeTensor(6657, 8727, 6659, 3621);
  g->Dequantize(3621, 3622, 0.19291339814662933, 0);
  g->Polynomial(3622, 8303, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8303, 8304);
  g->Binary(ynn_binary_add, 8304, 7293, 8301);
  g->Binary(ynn_binary_multiply, 3622, 7305, 8302);
  g->Binary(ynn_binary_multiply, 8302, 8301, 3623);
  g->Binary(ynn_binary_multiply, 3623, 3619, 3624);
  g->Quantize(3624, 3625, 2.0, 0);
  g->Transpose(9309, 6668, {1,0});
  g->Binary(ynn_binary_multiply, 6665, 6667, 6663);
  g->Dot(3625, 6668, YNN_INVALID_VALUE_ID, 6662, 1);
  g->DequantizeTensor(6662, YNN_INVALID_VALUE_ID, 6663, 6664);
  g->QuantizeTensor(6664, 8727, 6666, 3626);
  g->Dequantize(3626, 3627, 0.3256397247314453, 0);
  g->Unary(ynn_unary_square, 3627, 3628);
  g->Reduce(ynn_reduce_sum, 3628, 8306, {2}, true);
  g->ShapeProduct(3628, 8305, {2});
  g->Binary(ynn_binary_divide, 8306, 8305, 3630);
  g->Binary(ynn_binary_add, 3630, 8779, 3631);
  g->Unary(ynn_unary_rsqrt, 3631, 3632);
  g->Binary(ynn_binary_multiply, 3627, 3632, 3633);
  g->Binary(ynn_binary_multiply, 3633, 9312, 3634);
  g->Binary(ynn_binary_add, 3606, 3634, 3635);
  g->Binary(ynn_binary_multiply, 3635, 9304, 3636);
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
  g->Quantize(3643, 3644, 0.39901354908943176, 0);
  g->Transpose(9330, 6682, {1,0});
  g->Binary(ynn_binary_multiply, 6679, 6681, 6677);
  g->Dot(3644, 6682, YNN_INVALID_VALUE_ID, 6676, 1);
  g->DequantizeTensor(6676, YNN_INVALID_VALUE_ID, 6677, 6678);
  g->QuantizeTensor(6678, 8727, 6680, 3645);
  g->Dequantize(3645, 3646, 0.3700787425041199, 0);
  g->SplitDim(3646, 3647, 2, {8,256});
  g->FuseDims(3647, 3649, 1, 2);
  g->SplitDim(3649, 3648, 1, {8,1});
  g->Unary(ynn_unary_square, 3648, 3650);
  g->Reduce(ynn_reduce_sum, 3650, 8310, {3}, true);
  g->ShapeProduct(3650, 8309, {3});
  g->Binary(ynn_binary_divide, 8310, 8309, 3651);
  g->Binary(ynn_binary_add, 3651, 8779, 3653);
  g->Unary(ynn_unary_rsqrt, 3653, 3654);
  g->Binary(ynn_binary_multiply, 3648, 3654, 3655);
  g->Binary(ynn_binary_multiply, 3655, 9329, 3656);
  g->Slice(3656, 3657, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3656, 3658, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3658, 3659);
  g->Concat({3659,3657}, 3660, 3);
  g->Binary(ynn_binary_multiply, 3656, 3231, 3661);
  g->Binary(ynn_binary_multiply, 3660, 4329, 3662);
  g->Binary(ynn_binary_add, 3661, 3662, 3665);
}

// Scope: "Layer34 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer34AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9640, 3666, 0.0059552486054599285, 0);
  g->Dequantize(9664, 3667, 0.047244105488061905, 0);
  g->Slice(3665, 3668, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(3666, 3669, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(3667, 3670, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(3668, 3669, 3671, false, true);
  g->Mask(3671, 8840, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8840, 8314, {-1}, true);
  g->Binary(ynn_binary_subtract, 8840, 8314, 8311);
  g->Unary(ynn_unary_exp, 8311, 8312);
  g->Reduce(ynn_reduce_sum, 8312, 8315, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 8315, 8313);
  g->Binary(ynn_binary_multiply, 8312, 8313, 3672);
  g->Matmul(3672, 3670, 3673, false, false);
  g->Slice(3665, 3676, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(3666, 3677, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(3667, 3678, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(3676, 3677, 3679, false, true);
  g->Mask(3679, 8841, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8841, 8319, {-1}, true);
  g->Binary(ynn_binary_subtract, 8841, 8319, 8316);
  g->Unary(ynn_unary_exp, 8316, 8317);
  g->Reduce(ynn_reduce_sum, 8317, 8320, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 8320, 8318);
  g->Binary(ynn_binary_multiply, 8317, 8318, 3680);
  g->Matmul(3680, 3678, 3681, false, false);
  g->Concat({3673,3681}, 3682, 1);
}

// Scope: "Layer34 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer34AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(3682, 3684, 1, 2);
  g->SplitDim(3684, 3683, 1, {1,8});
  g->FuseDims(3683, 3685, 2, 2);
  g->Quantize(3685, 3687, 0.01857776567339897, 0);
  g->Transpose(9328, 6689, {1,0});
  g->Binary(ynn_binary_multiply, 6686, 6688, 6684);
  g->Dot(3687, 6689, YNN_INVALID_VALUE_ID, 6683, 1);
  g->DequantizeTensor(6683, YNN_INVALID_VALUE_ID, 6684, 6685);
  g->QuantizeTensor(6685, 8727, 6687, 3688);
  g->Dequantize(3688, 3689, 0.07984723150730133, 0);
}

// Scope: "Layer34 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer34Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3636, 3637);
  g->Reduce(ynn_reduce_sum, 3637, 8308, {2}, true);
  g->ShapeProduct(3637, 8307, {2});
  g->Binary(ynn_binary_divide, 8308, 8307, 3638);
  g->Binary(ynn_binary_add, 3638, 8779, 3639);
  g->Unary(ynn_unary_rsqrt, 3639, 3641);
  g->Binary(ynn_binary_multiply, 3636, 3641, 3642);
  g->Binary(ynn_binary_multiply, 3642, 9317, 3643);
  BuildLayer34AttentionQueryProjection(ctx);
  BuildLayer34AttentionSdpa(ctx);
  BuildLayer34AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 3689, 3690);
  g->Reduce(ynn_reduce_sum, 3690, 8324, {2}, true);
  g->ShapeProduct(3690, 8323, {2});
  g->Binary(ynn_binary_divide, 8324, 8323, 3691);
  g->Binary(ynn_binary_add, 3691, 8779, 3692);
  g->Unary(ynn_unary_rsqrt, 3692, 3693);
  g->Binary(ynn_binary_multiply, 3689, 3693, 3694);
  g->Binary(ynn_binary_multiply, 3694, 9324, 3695);
  g->Binary(ynn_binary_add, 3695, 3636, 3696);
}

// Scope: "Layer34 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer34Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3696, 3698);
  g->Reduce(ynn_reduce_sum, 3698, 8326, {2}, true);
  g->ShapeProduct(3698, 8325, {2});
  g->Binary(ynn_binary_divide, 8326, 8325, 3699);
  g->Binary(ynn_binary_add, 3699, 8779, 3700);
  g->Unary(ynn_unary_rsqrt, 3700, 3701);
  g->Binary(ynn_binary_multiply, 3696, 3701, 3702);
  g->Binary(ynn_binary_multiply, 3702, 9327, 3703);
  g->Quantize(3703, 3704, 0.037028808146715164, 0);
  g->Transpose(9321, 6695, {1,0});
  g->Binary(ynn_binary_multiply, 6693, 6694, 6691);
  g->Dot(3704, 6695, YNN_INVALID_VALUE_ID, 6690, 1);
  g->DequantizeTensor(6690, YNN_INVALID_VALUE_ID, 6691, 6692);
  g->QuantizeTensor(6692, 8727, 5926, 3705);
  g->Dequantize(3705, 3706, 0.06299213320016861, 0);
  g->Transpose(9320, 6700, {1,0});
  g->Binary(ynn_binary_multiply, 6693, 6699, 6697);
  g->Dot(3704, 6700, YNN_INVALID_VALUE_ID, 6696, 1);
  g->DequantizeTensor(6696, YNN_INVALID_VALUE_ID, 6697, 6698);
  g->QuantizeTensor(6698, 8727, 5926, 3708);
  g->Dequantize(3708, 3709, 0.06299213320016861, 0);
  g->Polynomial(3709, 8329, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8329, 8330);
  g->Binary(ynn_binary_add, 8330, 7293, 8327);
  g->Binary(ynn_binary_multiply, 3709, 7305, 8328);
  g->Binary(ynn_binary_multiply, 8328, 8327, 3710);
  g->Binary(ynn_binary_multiply, 3706, 3710, 3711);
  g->Quantize(3711, 3712, 0.23917324841022491, 0);
  g->Transpose(9319, 6707, {1,0});
  g->Binary(ynn_binary_multiply, 6704, 6706, 6702);
  g->Dot(3712, 6707, YNN_INVALID_VALUE_ID, 6701, 1);
  g->DequantizeTensor(6701, YNN_INVALID_VALUE_ID, 6702, 6703);
  g->QuantizeTensor(6703, 8727, 6705, 3713);
  g->Dequantize(3713, 3714, 0.136443629860878, 0);
  g->Unary(ynn_unary_square, 3714, 3715);
  g->Reduce(ynn_reduce_sum, 3715, 8332, {2}, true);
  g->ShapeProduct(3715, 8331, {2});
  g->Binary(ynn_binary_divide, 8332, 8331, 3716);
  g->Binary(ynn_binary_add, 3716, 8779, 3717);
  g->Unary(ynn_unary_rsqrt, 3717, 3719);
  g->Binary(ynn_binary_multiply, 3714, 3719, 3720);
  g->Binary(ynn_binary_multiply, 3720, 9325, 3721);
  g->Binary(ynn_binary_add, 3721, 3696, 3722);
}

// Scope: "Layer34 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer34PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(429, 3723, {0,0,34,0}, {-1,-1,1,-1});
  g->Reshape(3723, 3724, {1,1,256});
  g->Unary(ynn_unary_square, 3724, 3725);
  g->Reduce(ynn_reduce_sum, 3725, 8334, {2}, true);
  g->ShapeProduct(3725, 8333, {2});
  g->Binary(ynn_binary_divide, 8334, 8333, 3726);
  g->Binary(ynn_binary_add, 3726, 8779, 3727);
  g->Unary(ynn_unary_rsqrt, 3727, 3728);
  g->Binary(ynn_binary_multiply, 3724, 3728, 3730);
  g->Binary(ynn_binary_multiply, 3730, 9533, 3731);
  g->Binary(ynn_binary_multiply, 9562, 8783, 3732);
  g->Binary(ynn_binary_add, 3731, 3732, 3733);
  g->Binary(ynn_binary_multiply, 3733, 8777, 3734);
  g->Quantize(3722, 3735, 0.38806524872779846, 0);
  g->Transpose(9322, 6714, {1,0});
  g->Binary(ynn_binary_multiply, 6711, 6713, 6709);
  g->Dot(3735, 6714, YNN_INVALID_VALUE_ID, 6708, 1);
  g->DequantizeTensor(6708, YNN_INVALID_VALUE_ID, 6709, 6710);
  g->QuantizeTensor(6710, 8727, 6712, 3736);
  g->Dequantize(3736, 3737, 0.17125985026359558, 0);
  g->Polynomial(3737, 8337, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8337, 8338);
  g->Binary(ynn_binary_add, 8338, 7293, 8335);
  g->Binary(ynn_binary_multiply, 3737, 7305, 8336);
  g->Binary(ynn_binary_multiply, 8336, 8335, 3738);
  g->Binary(ynn_binary_multiply, 3738, 3734, 3739);
  g->Quantize(3739, 3741, 2.771653652191162, 0);
  g->Transpose(9323, 6721, {1,0});
  g->Binary(ynn_binary_multiply, 6718, 6720, 6716);
  g->Dot(3741, 6721, YNN_INVALID_VALUE_ID, 6715, 1);
  g->DequantizeTensor(6715, YNN_INVALID_VALUE_ID, 6716, 6717);
  g->QuantizeTensor(6717, 8727, 6719, 3742);
  g->Dequantize(3742, 3743, 0.28765690326690674, 0);
  g->Unary(ynn_unary_square, 3743, 3744);
  g->Reduce(ynn_reduce_sum, 3744, 8340, {2}, true);
  g->ShapeProduct(3744, 8339, {2});
  g->Binary(ynn_binary_divide, 8340, 8339, 3745);
  g->Binary(ynn_binary_add, 3745, 8779, 3746);
  g->Unary(ynn_unary_rsqrt, 3746, 3747);
  g->Binary(ynn_binary_multiply, 3743, 3747, 3748);
  g->Binary(ynn_binary_multiply, 3748, 9326, 3749);
  g->Binary(ynn_binary_add, 3722, 3749, 3750);
  g->Binary(ynn_binary_multiply, 3750, 9318, 3752);
}

// Scope: "Layer34"
LAB_YNN_BUILDER_NOINLINE void BuildLayer34(Context& ctx) {
  BuildLayer34Attention(ctx);
  BuildLayer34Mlp(ctx);
  BuildLayer34PerLayerEmbedding(ctx);
}

}  // namespace BuildGemma4DecodeSource
