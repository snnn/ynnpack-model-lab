// Generated YNNPACK builder; do not edit.
#include "gemma4_decode_builder.h"

namespace BuildGemma4DecodeSource {

// Scope: "Layer26 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer26AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(2650, 2651, 0.3528440296649933, 0);
  g->Transpose(9069, 6133, {1,0});
  g->Binary(ynn_binary_multiply, 6130, 6132, 6128);
  g->Dot(2651, 6133, YNN_INVALID_VALUE_ID, 6127, 1);
  g->DequantizeTensor(6127, YNN_INVALID_VALUE_ID, 6128, 6129);
  g->QuantizeTensor(6129, 8595, 6131, 2652);
  g->Dequantize(2652, 2653, 0.3641732335090637, 0);
  g->SplitDim(2653, 2654, 2, {8,256});
  g->Transpose(2654, 2655, {0,2,1,3});
  g->Unary(ynn_unary_square, 2655, 2656);
  g->Reduce(ynn_reduce_sum, 2656, 7892, {3}, true);
  g->ShapeProduct(2656, 7891, {3});
  g->Binary(ynn_binary_divide, 7892, 7891, 2657);
  g->Binary(ynn_binary_add, 2657, 8647, 2658);
  g->Unary(ynn_unary_rsqrt, 2658, 2659);
  g->Binary(ynn_binary_multiply, 2655, 2659, 2660);
  g->Binary(ynn_binary_multiply, 2660, 9068, 2661);
  g->Slice(2661, 2662, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2661, 2663, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2663, 2664);
  g->Concat({2664,2662}, 2665, 3);
  g->Binary(ynn_binary_multiply, 2661, 3141, 2666);
  g->Binary(ynn_binary_multiply, 2665, 4217, 2667);
  g->Binary(ynn_binary_add, 2666, 2667, 2668);
}

// Scope: "Layer26 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer26AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9508, 2669, 0.0059552486054599285, 0);
  g->Dequantize(9532, 2671, 0.047244105488061905, 0);
  g->Slice(2668, 2672, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(2669, 2673, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(2671, 2674, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(2672, 2673, 2675, false, true);
  g->Mask(2675, 8690, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8690, 7901, {-1}, true);
  g->Binary(ynn_binary_subtract, 8690, 7901, 7898);
  g->Unary(ynn_unary_exp, 7898, 7899);
  g->Reduce(ynn_reduce_sum, 7899, 7902, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 7902, 7900);
  g->Binary(ynn_binary_multiply, 7899, 7900, 2676);
  g->Matmul(2676, 2674, 2677, false, false);
  g->Slice(2668, 2678, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(2669, 2679, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(2671, 2681, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(2678, 2679, 2682, false, true);
  g->Mask(2682, 8691, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8691, 7906, {-1}, true);
  g->Binary(ynn_binary_subtract, 8691, 7906, 7903);
  g->Unary(ynn_unary_exp, 7903, 7904);
  g->Reduce(ynn_reduce_sum, 7904, 7907, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 7907, 7905);
  g->Binary(ynn_binary_multiply, 7904, 7905, 2683);
  g->Matmul(2683, 2681, 2684, false, false);
  g->Concat({2677,2684}, 2685, 1);
}

// Scope: "Layer26 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer26AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(2685, 2686, {0,2,1,3});
  g->FuseDims(2686, 2687, 2, 2);
  g->Quantize(2687, 2688, 0.018700797110795975, 0);
  g->Transpose(9067, 6139, {1,0});
  g->Binary(ynn_binary_multiply, 5491, 6138, 6135);
  g->Dot(2688, 6139, YNN_INVALID_VALUE_ID, 6134, 1);
  g->DequantizeTensor(6134, YNN_INVALID_VALUE_ID, 6135, 6136);
  g->QuantizeTensor(6136, 8595, 6137, 2689);
  g->Dequantize(2689, 2691, 0.045751601457595825, 0);
}

// Scope: "Layer26 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer26Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2643, 2644);
  g->Reduce(ynn_reduce_sum, 2644, 7890, {2}, true);
  g->ShapeProduct(2644, 7889, {2});
  g->Binary(ynn_binary_divide, 7890, 7889, 2645);
  g->Binary(ynn_binary_add, 2645, 8647, 2646);
  g->Unary(ynn_unary_rsqrt, 2646, 2647);
  g->Binary(ynn_binary_multiply, 2643, 2647, 2648);
  g->Binary(ynn_binary_multiply, 2648, 9056, 2650);
  BuildLayer26AttentionQueryProjection(ctx);
  BuildLayer26AttentionSdpa(ctx);
  BuildLayer26AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2691, 2692);
  g->Reduce(ynn_reduce_sum, 2692, 7909, {2}, true);
  g->ShapeProduct(2692, 7908, {2});
  g->Binary(ynn_binary_divide, 7909, 7908, 2693);
  g->Binary(ynn_binary_add, 2693, 8647, 2694);
  g->Unary(ynn_unary_rsqrt, 2694, 2695);
  g->Binary(ynn_binary_multiply, 2691, 2695, 2696);
  g->Binary(ynn_binary_multiply, 2696, 9063, 2697);
  g->Binary(ynn_binary_add, 2697, 2643, 2698);
}

// Scope: "Layer26 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer26Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2698, 2699);
  g->Reduce(ynn_reduce_sum, 2699, 7911, {2}, true);
  g->ShapeProduct(2699, 7910, {2});
  g->Binary(ynn_binary_divide, 7911, 7910, 2700);
  g->Binary(ynn_binary_add, 2700, 8647, 2702);
  g->Unary(ynn_unary_rsqrt, 2702, 2703);
  g->Binary(ynn_binary_multiply, 2698, 2703, 2704);
  g->Binary(ynn_binary_multiply, 2704, 9066, 2705);
  g->Quantize(2705, 2706, 0.017227180302143097, 0);
  g->Transpose(9060, 6146, {1,0});
  g->Binary(ynn_binary_multiply, 6143, 6145, 6141);
  g->Dot(2706, 6146, YNN_INVALID_VALUE_ID, 6140, 1);
  g->DequantizeTensor(6140, YNN_INVALID_VALUE_ID, 6141, 6142);
  g->QuantizeTensor(6142, 8595, 6144, 2707);
  g->Dequantize(2707, 2708, 0.01808563992381096, 0);
  g->Transpose(9059, 6151, {1,0});
  g->Binary(ynn_binary_multiply, 6143, 6150, 6148);
  g->Dot(2706, 6151, YNN_INVALID_VALUE_ID, 6147, 1);
  g->DequantizeTensor(6147, YNN_INVALID_VALUE_ID, 6148, 6149);
  g->QuantizeTensor(6149, 8595, 6144, 2709);
  g->Dequantize(2709, 2710, 0.01808563992381096, 0);
  g->Polynomial(2710, 7914, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7914, 7915);
  g->Binary(ynn_binary_add, 7915, 7161, 7912);
  g->Binary(ynn_binary_multiply, 2710, 7173, 7913);
  g->Binary(ynn_binary_multiply, 7913, 7912, 2713);
  g->Binary(ynn_binary_multiply, 2708, 2713, 2714);
  g->Quantize(2714, 2715, 0.022514773532748222, 0);
  g->Transpose(9058, 6158, {1,0});
  g->Binary(ynn_binary_multiply, 6155, 6157, 6153);
  g->Dot(2715, 6158, YNN_INVALID_VALUE_ID, 6152, 1);
  g->DequantizeTensor(6152, YNN_INVALID_VALUE_ID, 6153, 6154);
  g->QuantizeTensor(6154, 8595, 6156, 2716);
  g->Dequantize(2716, 2717, 0.013520898297429085, 0);
  g->Unary(ynn_unary_square, 2717, 2718);
  g->Reduce(ynn_reduce_sum, 2718, 7917, {2}, true);
  g->ShapeProduct(2718, 7916, {2});
  g->Binary(ynn_binary_divide, 7917, 7916, 2719);
  g->Binary(ynn_binary_add, 2719, 8647, 2720);
  g->Unary(ynn_unary_rsqrt, 2720, 2721);
  g->Binary(ynn_binary_multiply, 2717, 2721, 2722);
  g->Binary(ynn_binary_multiply, 2722, 9064, 2724);
  g->Binary(ynn_binary_add, 2724, 2698, 2725);
}

// Scope: "Layer26 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer26PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 2726, {0,0,26,0}, {-1,-1,1,-1});
  g->Reshape(2726, 2727, {1,1,256});
  g->Unary(ynn_unary_square, 2727, 2728);
  g->Reduce(ynn_reduce_sum, 2728, 7919, {2}, true);
  g->ShapeProduct(2728, 7918, {2});
  g->Binary(ynn_binary_divide, 7919, 7918, 2729);
  g->Binary(ynn_binary_add, 2729, 8647, 2730);
  g->Unary(ynn_unary_rsqrt, 2730, 2731);
  g->Binary(ynn_binary_multiply, 2727, 2731, 2732);
  g->Binary(ynn_binary_multiply, 2732, 9401, 2733);
  g->Binary(ynn_binary_multiply, 9421, 8651, 2734);
  g->Binary(ynn_binary_add, 2733, 2734, 2735);
  g->Binary(ynn_binary_multiply, 2735, 8645, 2736);
  g->Quantize(2725, 2737, 0.2931458652019501, 0);
  g->Transpose(9061, 6165, {1,0});
  g->Binary(ynn_binary_multiply, 6162, 6164, 6160);
  g->Dot(2737, 6165, YNN_INVALID_VALUE_ID, 6159, 1);
  g->DequantizeTensor(6159, YNN_INVALID_VALUE_ID, 6160, 6161);
  g->QuantizeTensor(6161, 8595, 6163, 2738);
  g->Dequantize(2738, 2739, 0.19685040414333344, 0);
  g->Polynomial(2739, 7922, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7922, 7923);
  g->Binary(ynn_binary_add, 7923, 7161, 7920);
  g->Binary(ynn_binary_multiply, 2739, 7173, 7921);
  g->Binary(ynn_binary_multiply, 7921, 7920, 2740);
  g->Binary(ynn_binary_multiply, 2740, 2736, 2741);
  g->Quantize(2741, 2742, 1.0629920959472656, 0);
  g->Transpose(9062, 6172, {1,0});
  g->Binary(ynn_binary_multiply, 6169, 6171, 6167);
  g->Dot(2742, 6172, YNN_INVALID_VALUE_ID, 6166, 1);
  g->DequantizeTensor(6166, YNN_INVALID_VALUE_ID, 6167, 6168);
  g->QuantizeTensor(6168, 8595, 6170, 2743);
  g->Dequantize(2743, 2745, 0.163782998919487, 0);
  g->Unary(ynn_unary_square, 2745, 2746);
  g->Reduce(ynn_reduce_sum, 2746, 7930, {2}, true);
  g->ShapeProduct(2746, 7929, {2});
  g->Binary(ynn_binary_divide, 7930, 7929, 2747);
  g->Binary(ynn_binary_add, 2747, 8647, 2748);
  g->Unary(ynn_unary_rsqrt, 2748, 2749);
  g->Binary(ynn_binary_multiply, 2745, 2749, 2750);
  g->Binary(ynn_binary_multiply, 2750, 9065, 2751);
  g->Binary(ynn_binary_add, 2725, 2751, 2752);
  g->Binary(ynn_binary_multiply, 2752, 9057, 2753);
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
  g->Quantize(2760, 2761, 0.3453449010848999, 0);
  g->Transpose(9083, 6179, {1,0});
  g->Binary(ynn_binary_multiply, 6176, 6178, 6174);
  g->Dot(2761, 6179, YNN_INVALID_VALUE_ID, 6173, 1);
  g->DequantizeTensor(6173, YNN_INVALID_VALUE_ID, 6174, 6175);
  g->QuantizeTensor(6175, 8595, 6177, 2762);
  g->Dequantize(2762, 2763, 0.35433071851730347, 0);
  g->SplitDim(2763, 2764, 2, {8,256});
  g->Transpose(2764, 2765, {0,2,1,3});
  g->Unary(ynn_unary_square, 2765, 2767);
  g->Reduce(ynn_reduce_sum, 2767, 7934, {3}, true);
  g->ShapeProduct(2767, 7933, {3});
  g->Binary(ynn_binary_divide, 7934, 7933, 2768);
  g->Binary(ynn_binary_add, 2768, 8647, 2769);
  g->Unary(ynn_unary_rsqrt, 2769, 2770);
  g->Binary(ynn_binary_multiply, 2765, 2770, 2771);
  g->Binary(ynn_binary_multiply, 2771, 9082, 2772);
  g->Slice(2772, 2773, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2772, 2774, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2774, 2775);
  g->Concat({2775,2773}, 2776, 3);
  g->Binary(ynn_binary_multiply, 2772, 3141, 2778);
  g->Binary(ynn_binary_multiply, 2776, 4217, 2779);
  g->Binary(ynn_binary_add, 2778, 2779, 2780);
}

// Scope: "Layer27 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer27AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9508, 2781, 0.0059552486054599285, 0);
  g->Dequantize(9532, 2782, 0.047244105488061905, 0);
  g->Slice(2780, 2783, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(2781, 2784, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(2782, 2785, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(2783, 2784, 2786, false, true);
  g->Mask(2786, 8692, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8692, 7938, {-1}, true);
  g->Binary(ynn_binary_subtract, 8692, 7938, 7935);
  g->Unary(ynn_unary_exp, 7935, 7936);
  g->Reduce(ynn_reduce_sum, 7936, 7939, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 7939, 7937);
  g->Binary(ynn_binary_multiply, 7936, 7937, 2788);
  g->Matmul(2788, 2785, 2789, false, false);
  g->Slice(2780, 2790, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(2781, 2791, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(2782, 2792, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(2790, 2791, 2793, false, true);
  g->Mask(2793, 8693, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8693, 7943, {-1}, true);
  g->Binary(ynn_binary_subtract, 8693, 7943, 7940);
  g->Unary(ynn_unary_exp, 7940, 7941);
  g->Reduce(ynn_reduce_sum, 7941, 7944, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 7944, 7942);
  g->Binary(ynn_binary_multiply, 7941, 7942, 2794);
  g->Matmul(2794, 2792, 2795, false, false);
  g->Concat({2789,2795}, 2796, 1);
}

// Scope: "Layer27 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer27AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(2796, 2798, {0,2,1,3});
  g->FuseDims(2798, 2799, 2, 2);
  g->Quantize(2799, 2800, 0.020669300109148026, 0);
  g->Transpose(9081, 6186, {1,0});
  g->Binary(ynn_binary_multiply, 6183, 6185, 6181);
  g->Dot(2800, 6186, YNN_INVALID_VALUE_ID, 6180, 1);
  g->DequantizeTensor(6180, YNN_INVALID_VALUE_ID, 6181, 6182);
  g->QuantizeTensor(6182, 8595, 6184, 2801);
  g->Dequantize(2801, 2802, 0.04588036239147186, 0);
}

// Scope: "Layer27 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer27Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2753, 2754);
  g->Reduce(ynn_reduce_sum, 2754, 7932, {2}, true);
  g->ShapeProduct(2754, 7931, {2});
  g->Binary(ynn_binary_divide, 7932, 7931, 2756);
  g->Binary(ynn_binary_add, 2756, 8647, 2757);
  g->Unary(ynn_unary_rsqrt, 2757, 2758);
  g->Binary(ynn_binary_multiply, 2753, 2758, 2759);
  g->Binary(ynn_binary_multiply, 2759, 9070, 2760);
  BuildLayer27AttentionQueryProjection(ctx);
  BuildLayer27AttentionSdpa(ctx);
  BuildLayer27AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2802, 2803);
  g->Reduce(ynn_reduce_sum, 2803, 7946, {2}, true);
  g->ShapeProduct(2803, 7945, {2});
  g->Binary(ynn_binary_divide, 7946, 7945, 2804);
  g->Binary(ynn_binary_add, 2804, 8647, 2805);
  g->Unary(ynn_unary_rsqrt, 2805, 2806);
  g->Binary(ynn_binary_multiply, 2802, 2806, 2807);
  g->Binary(ynn_binary_multiply, 2807, 9077, 2809);
  g->Binary(ynn_binary_add, 2809, 2753, 2810);
}

// Scope: "Layer27 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer27Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2810, 2811);
  g->Reduce(ynn_reduce_sum, 2811, 7948, {2}, true);
  g->ShapeProduct(2811, 7947, {2});
  g->Binary(ynn_binary_divide, 7948, 7947, 2812);
  g->Binary(ynn_binary_add, 2812, 8647, 2813);
  g->Unary(ynn_unary_rsqrt, 2813, 2814);
  g->Binary(ynn_binary_multiply, 2810, 2814, 2815);
  g->Binary(ynn_binary_multiply, 2815, 9080, 2816);
  g->Quantize(2816, 2817, 0.019605165347456932, 0);
  g->Transpose(9074, 6199, {1,0});
  g->Binary(ynn_binary_multiply, 6197, 6198, 6195);
  g->Dot(2817, 6199, YNN_INVALID_VALUE_ID, 6194, 1);
  g->DequantizeTensor(6194, YNN_INVALID_VALUE_ID, 6195, 6196);
  g->QuantizeTensor(6196, 8595, 5911, 2818);
  g->Dequantize(2818, 2821, 0.019808080047369003, 0);
  g->Transpose(9073, 6204, {1,0});
  g->Binary(ynn_binary_multiply, 6197, 6203, 6201);
  g->Dot(2817, 6204, YNN_INVALID_VALUE_ID, 6200, 1);
  g->DequantizeTensor(6200, YNN_INVALID_VALUE_ID, 6201, 6202);
  g->QuantizeTensor(6202, 8595, 5911, 2822);
  g->Dequantize(2822, 2823, 0.019808080047369003, 0);
  g->Polynomial(2823, 7951, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7951, 7952);
  g->Binary(ynn_binary_add, 7952, 7161, 7949);
  g->Binary(ynn_binary_multiply, 2823, 7173, 7950);
  g->Binary(ynn_binary_multiply, 7950, 7949, 2824);
  g->Binary(ynn_binary_multiply, 2821, 2824, 2825);
  g->Quantize(2825, 2826, 0.030388789251446724, 0);
  g->Transpose(9072, 6211, {1,0});
  g->Binary(ynn_binary_multiply, 6208, 6210, 6206);
  g->Dot(2826, 6211, YNN_INVALID_VALUE_ID, 6205, 1);
  g->DequantizeTensor(6205, YNN_INVALID_VALUE_ID, 6206, 6207);
  g->QuantizeTensor(6207, 8595, 6209, 2827);
  g->Dequantize(2827, 2828, 0.02053113840520382, 0);
  g->Unary(ynn_unary_square, 2828, 2829);
  g->Reduce(ynn_reduce_sum, 2829, 7954, {2}, true);
  g->ShapeProduct(2829, 7953, {2});
  g->Binary(ynn_binary_divide, 7954, 7953, 2831);
  g->Binary(ynn_binary_add, 2831, 8647, 2832);
  g->Unary(ynn_unary_rsqrt, 2832, 2833);
  g->Binary(ynn_binary_multiply, 2828, 2833, 2834);
  g->Binary(ynn_binary_multiply, 2834, 9078, 2835);
  g->Binary(ynn_binary_add, 2835, 2810, 2836);
}

// Scope: "Layer27 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer27PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 2837, {0,0,27,0}, {-1,-1,1,-1});
  g->Reshape(2837, 2838, {1,1,256});
  g->Unary(ynn_unary_square, 2838, 2839);
  g->Reduce(ynn_reduce_sum, 2839, 7956, {2}, true);
  g->ShapeProduct(2839, 7955, {2});
  g->Binary(ynn_binary_divide, 7956, 7955, 2840);
  g->Binary(ynn_binary_add, 2840, 8647, 2842);
  g->Unary(ynn_unary_rsqrt, 2842, 2843);
  g->Binary(ynn_binary_multiply, 2838, 2843, 2844);
  g->Binary(ynn_binary_multiply, 2844, 9401, 2845);
  g->Binary(ynn_binary_multiply, 9422, 8651, 2846);
  g->Binary(ynn_binary_add, 2845, 2846, 2847);
  g->Binary(ynn_binary_multiply, 2847, 8645, 2848);
  g->Quantize(2836, 2849, 0.24697038531303406, 0);
  g->Transpose(9075, 6218, {1,0});
  g->Binary(ynn_binary_multiply, 6215, 6217, 6213);
  g->Dot(2849, 6218, YNN_INVALID_VALUE_ID, 6212, 1);
  g->DequantizeTensor(6212, YNN_INVALID_VALUE_ID, 6213, 6214);
  g->QuantizeTensor(6214, 8595, 6216, 2850);
  g->Dequantize(2850, 2851, 0.24901576340198517, 0);
  g->Polynomial(2851, 7961, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7961, 7962);
  g->Binary(ynn_binary_add, 7962, 7161, 7959);
  g->Binary(ynn_binary_multiply, 2851, 7173, 7960);
  g->Binary(ynn_binary_multiply, 7960, 7959, 2853);
  g->Binary(ynn_binary_multiply, 2853, 2848, 2854);
  g->Quantize(2854, 2855, 1.1023621559143066, 0);
  g->Transpose(9076, 6225, {1,0});
  g->Binary(ynn_binary_multiply, 6222, 6224, 6220);
  g->Dot(2855, 6225, YNN_INVALID_VALUE_ID, 6219, 1);
  g->DequantizeTensor(6219, YNN_INVALID_VALUE_ID, 6220, 6221);
  g->QuantizeTensor(6221, 8595, 6223, 2856);
  g->Dequantize(2856, 2857, 0.16658033430576324, 0);
  g->Unary(ynn_unary_square, 2857, 2858);
  g->Reduce(ynn_reduce_sum, 2858, 7964, {2}, true);
  g->ShapeProduct(2858, 7963, {2});
  g->Binary(ynn_binary_divide, 7964, 7963, 2859);
  g->Binary(ynn_binary_add, 2859, 8647, 2860);
  g->Unary(ynn_unary_rsqrt, 2860, 2861);
  g->Binary(ynn_binary_multiply, 2857, 2861, 2862);
  g->Binary(ynn_binary_multiply, 2862, 9079, 2864);
  g->Binary(ynn_binary_add, 2836, 2864, 2865);
  g->Binary(ynn_binary_multiply, 2865, 9071, 2866);
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
  g->Quantize(2872, 2873, 0.3128816485404968, 0);
  g->Transpose(9097, 6232, {1,0});
  g->Binary(ynn_binary_multiply, 6229, 6231, 6227);
  g->Dot(2873, 6232, YNN_INVALID_VALUE_ID, 6226, 1);
  g->DequantizeTensor(6226, YNN_INVALID_VALUE_ID, 6227, 6228);
  g->QuantizeTensor(6228, 8595, 6230, 2875);
  g->Dequantize(2875, 2876, 0.312992125749588, 0);
  g->SplitDim(2876, 2877, 2, {8,256});
  g->Transpose(2877, 2878, {0,2,1,3});
  g->Unary(ynn_unary_square, 2878, 2879);
  g->Reduce(ynn_reduce_sum, 2879, 7968, {3}, true);
  g->ShapeProduct(2879, 7967, {3});
  g->Binary(ynn_binary_divide, 7968, 7967, 2880);
  g->Binary(ynn_binary_add, 2880, 8647, 2881);
  g->Unary(ynn_unary_rsqrt, 2881, 2882);
  g->Binary(ynn_binary_multiply, 2878, 2882, 2883);
  g->Binary(ynn_binary_multiply, 2883, 9096, 2884);
  g->Slice(2884, 2886, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2884, 2887, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2887, 2888);
  g->Concat({2888,2886}, 2889, 3);
  g->Binary(ynn_binary_multiply, 2884, 3141, 2890);
  g->Binary(ynn_binary_multiply, 2889, 4217, 2891);
  g->Binary(ynn_binary_add, 2890, 2891, 2892);
}

// Scope: "Layer28 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer28AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9508, 2893, 0.0059552486054599285, 0);
  g->Dequantize(9532, 2894, 0.047244105488061905, 0);
  g->Slice(2892, 2895, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(2893, 2897, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(2894, 2898, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(2895, 2897, 2899, false, true);
  g->Mask(2899, 8694, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8694, 7972, {-1}, true);
  g->Binary(ynn_binary_subtract, 8694, 7972, 7969);
  g->Unary(ynn_unary_exp, 7969, 7970);
  g->Reduce(ynn_reduce_sum, 7970, 7973, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 7973, 7971);
  g->Binary(ynn_binary_multiply, 7970, 7971, 2900);
  g->Matmul(2900, 2898, 2901, false, false);
  g->Slice(2892, 2902, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(2893, 2903, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(2894, 2904, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(2902, 2903, 2905, false, true);
  g->Mask(2905, 8695, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8695, 7977, {-1}, true);
  g->Binary(ynn_binary_subtract, 8695, 7977, 7974);
  g->Unary(ynn_unary_exp, 7974, 7975);
  g->Reduce(ynn_reduce_sum, 7975, 7978, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 7978, 7976);
  g->Binary(ynn_binary_multiply, 7975, 7976, 2907);
  g->Matmul(2907, 2904, 2908, false, false);
  g->Concat({2901,2908}, 2909, 1);
}

// Scope: "Layer28 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer28AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(2909, 2910, {0,2,1,3});
  g->FuseDims(2910, 2911, 2, 2);
  g->Quantize(2911, 2912, 0.019808080047369003, 0);
  g->Transpose(9095, 6238, {1,0});
  g->Binary(ynn_binary_multiply, 5911, 6237, 6234);
  g->Dot(2912, 6238, YNN_INVALID_VALUE_ID, 6233, 1);
  g->DequantizeTensor(6233, YNN_INVALID_VALUE_ID, 6234, 6235);
  g->QuantizeTensor(6235, 8595, 6236, 2913);
  g->Dequantize(2913, 2914, 0.04302408546209335, 0);
}

// Scope: "Layer28 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer28Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2866, 2867);
  g->Reduce(ynn_reduce_sum, 2867, 7966, {2}, true);
  g->ShapeProduct(2867, 7965, {2});
  g->Binary(ynn_binary_divide, 7966, 7965, 2868);
  g->Binary(ynn_binary_add, 2868, 8647, 2869);
  g->Unary(ynn_unary_rsqrt, 2869, 2870);
  g->Binary(ynn_binary_multiply, 2866, 2870, 2871);
  g->Binary(ynn_binary_multiply, 2871, 9084, 2872);
  BuildLayer28AttentionQueryProjection(ctx);
  BuildLayer28AttentionSdpa(ctx);
  BuildLayer28AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2914, 2915);
  g->Reduce(ynn_reduce_sum, 2915, 7982, {2}, true);
  g->ShapeProduct(2915, 7981, {2});
  g->Binary(ynn_binary_divide, 7982, 7981, 2917);
  g->Binary(ynn_binary_add, 2917, 8647, 2918);
  g->Unary(ynn_unary_rsqrt, 2918, 2919);
  g->Binary(ynn_binary_multiply, 2914, 2919, 2920);
  g->Binary(ynn_binary_multiply, 2920, 9091, 2921);
  g->Binary(ynn_binary_add, 2921, 2866, 2922);
}

// Scope: "Layer28 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer28Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2922, 2923);
  g->Reduce(ynn_reduce_sum, 2923, 7984, {2}, true);
  g->ShapeProduct(2923, 7983, {2});
  g->Binary(ynn_binary_divide, 7984, 7983, 2924);
  g->Binary(ynn_binary_add, 2924, 8647, 2925);
  g->Unary(ynn_unary_rsqrt, 2925, 2926);
  g->Binary(ynn_binary_multiply, 2922, 2926, 2929);
  g->Binary(ynn_binary_multiply, 2929, 9094, 2930);
  g->Quantize(2930, 2931, 0.02151750959455967, 0);
  g->Transpose(9088, 6245, {1,0});
  g->Binary(ynn_binary_multiply, 6242, 6244, 6240);
  g->Dot(2931, 6245, YNN_INVALID_VALUE_ID, 6239, 1);
  g->DequantizeTensor(6239, YNN_INVALID_VALUE_ID, 6240, 6241);
  g->QuantizeTensor(6241, 8595, 6243, 2932);
  g->Dequantize(2932, 2933, 0.026574812829494476, 0);
  g->Transpose(9087, 6250, {1,0});
  g->Binary(ynn_binary_multiply, 6242, 6249, 6247);
  g->Dot(2931, 6250, YNN_INVALID_VALUE_ID, 6246, 1);
  g->DequantizeTensor(6246, YNN_INVALID_VALUE_ID, 6247, 6248);
  g->QuantizeTensor(6248, 8595, 6243, 2934);
  g->Dequantize(2934, 2935, 0.026574812829494476, 0);
  g->Polynomial(2935, 7987, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7987, 7988);
  g->Binary(ynn_binary_add, 7988, 7161, 7985);
  g->Binary(ynn_binary_multiply, 2935, 7173, 7986);
  g->Binary(ynn_binary_multiply, 7986, 7985, 2936);
  g->Binary(ynn_binary_multiply, 2933, 2936, 2937);
  g->Quantize(2937, 2939, 0.04773623123764992, 0);
  g->Transpose(9086, 6256, {1,0});
  g->Binary(ynn_binary_multiply, 5114, 6255, 6252);
  g->Dot(2939, 6256, YNN_INVALID_VALUE_ID, 6251, 1);
  g->DequantizeTensor(6251, YNN_INVALID_VALUE_ID, 6252, 6253);
  g->QuantizeTensor(6253, 8595, 6254, 2940);
  g->Dequantize(2940, 2941, 0.030276838690042496, 0);
  g->Unary(ynn_unary_square, 2941, 2942);
  g->Reduce(ynn_reduce_sum, 2942, 7990, {2}, true);
  g->ShapeProduct(2942, 7989, {2});
  g->Binary(ynn_binary_divide, 7990, 7989, 2943);
  g->Binary(ynn_binary_add, 2943, 8647, 2944);
  g->Unary(ynn_unary_rsqrt, 2944, 2945);
  g->Binary(ynn_binary_multiply, 2941, 2945, 2946);
  g->Binary(ynn_binary_multiply, 2946, 9092, 2947);
  g->Binary(ynn_binary_add, 2947, 2922, 2948);
}

// Scope: "Layer28 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer28PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 2950, {0,0,28,0}, {-1,-1,1,-1});
  g->Reshape(2950, 2951, {1,1,256});
  g->Unary(ynn_unary_square, 2951, 2952);
  g->Reduce(ynn_reduce_sum, 2952, 7992, {2}, true);
  g->ShapeProduct(2952, 7991, {2});
  g->Binary(ynn_binary_divide, 7992, 7991, 2953);
  g->Binary(ynn_binary_add, 2953, 8647, 2954);
  g->Unary(ynn_unary_rsqrt, 2954, 2955);
  g->Binary(ynn_binary_multiply, 2951, 2955, 2956);
  g->Binary(ynn_binary_multiply, 2956, 9401, 2957);
  g->Binary(ynn_binary_multiply, 9423, 8651, 2958);
  g->Binary(ynn_binary_add, 2957, 2958, 2959);
  g->Binary(ynn_binary_multiply, 2959, 8645, 2961);
  g->Quantize(2948, 2962, 0.1727961152791977, 0);
  g->Transpose(9089, 6263, {1,0});
  g->Binary(ynn_binary_multiply, 6260, 6262, 6258);
  g->Dot(2962, 6263, YNN_INVALID_VALUE_ID, 6257, 1);
  g->DequantizeTensor(6257, YNN_INVALID_VALUE_ID, 6258, 6259);
  g->QuantizeTensor(6259, 8595, 6261, 2963);
  g->Dequantize(2963, 2964, 0.2736220359802246, 0);
  g->Polynomial(2964, 7995, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7995, 7996);
  g->Binary(ynn_binary_add, 7996, 7161, 7993);
  g->Binary(ynn_binary_multiply, 2964, 7173, 7994);
  g->Binary(ynn_binary_multiply, 7994, 7993, 2965);
  g->Binary(ynn_binary_multiply, 2965, 2961, 2966);
  g->Quantize(2966, 2967, 1.3543306589126587, 0);
  g->Transpose(9090, 6270, {1,0});
  g->Binary(ynn_binary_multiply, 6267, 6269, 6265);
  g->Dot(2967, 6270, YNN_INVALID_VALUE_ID, 6264, 1);
  g->DequantizeTensor(6264, YNN_INVALID_VALUE_ID, 6265, 6266);
  g->QuantizeTensor(6266, 8595, 6268, 2968);
  g->Dequantize(2968, 2969, 0.2807792127132416, 0);
  g->Unary(ynn_unary_square, 2969, 2970);
  g->Reduce(ynn_reduce_sum, 2970, 7998, {2}, true);
  g->ShapeProduct(2970, 7997, {2});
  g->Binary(ynn_binary_divide, 7998, 7997, 2972);
  g->Binary(ynn_binary_add, 2972, 8647, 2973);
  g->Unary(ynn_unary_rsqrt, 2973, 2974);
  g->Binary(ynn_binary_multiply, 2969, 2974, 2975);
  g->Binary(ynn_binary_multiply, 2975, 9093, 2976);
  g->Binary(ynn_binary_add, 2948, 2976, 2977);
  g->Binary(ynn_binary_multiply, 2977, 9085, 2978);
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
  g->Quantize(2985, 2986, 0.1544896364212036, 0);
  g->Transpose(9111, 6284, {1,0});
  g->Binary(ynn_binary_multiply, 6281, 6283, 6279);
  g->Dot(2986, 6284, YNN_INVALID_VALUE_ID, 6278, 1);
  g->DequantizeTensor(6278, YNN_INVALID_VALUE_ID, 6279, 6280);
  g->QuantizeTensor(6280, 8595, 6282, 2987);
  g->Dequantize(2987, 2988, 0.31496062874794006, 0);
  g->SplitDim(2988, 2989, 2, {8,512});
  g->Transpose(2989, 2990, {0,2,1,3});
  g->Unary(ynn_unary_square, 2990, 2991);
  g->Reduce(ynn_reduce_sum, 2991, 8002, {3}, true);
  g->ShapeProduct(2991, 8001, {3});
  g->Binary(ynn_binary_divide, 8002, 8001, 2992);
  g->Binary(ynn_binary_add, 2992, 8647, 2994);
  g->Unary(ynn_unary_rsqrt, 2994, 2995);
  g->Binary(ynn_binary_multiply, 2990, 2995, 2996);
  g->Binary(ynn_binary_multiply, 2996, 9110, 2997);
  g->Slice(2997, 2998, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(2997, 2999, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 2999, 3000);
  g->Concat({3000,2998}, 3001, 3);
  g->Binary(ynn_binary_multiply, 2997, 4830, 3002);
  g->Binary(ynn_binary_multiply, 3001, 2, 3003);
  g->Binary(ynn_binary_add, 3002, 3003, 3004);
}

// Scope: "Layer29 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer29AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9509, 3005, 0.001091228099539876, 0);
  g->Dequantize(9533, 3006, 0.01785714365541935, 0);
  g->Slice(3004, 3007, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(3005, 3008, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(3006, 3009, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(3007, 3008, 3010, false, true);
  g->Mask(3010, 8696, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 8696, 8006, {-1}, true);
  g->Binary(ynn_binary_subtract, 8696, 8006, 8003);
  g->Unary(ynn_unary_exp, 8003, 8004);
  g->Reduce(ynn_reduce_sum, 8004, 8007, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 8007, 8005);
  g->Binary(ynn_binary_multiply, 8004, 8005, 3011);
  g->Matmul(3011, 3009, 3012, false, false);
  g->Slice(3004, 3014, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(3005, 3015, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(3006, 3016, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(3014, 3015, 3017, false, true);
  g->Mask(3017, 8697, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 8697, 8011, {-1}, true);
  g->Binary(ynn_binary_subtract, 8697, 8011, 8008);
  g->Unary(ynn_unary_exp, 8008, 8009);
  g->Reduce(ynn_reduce_sum, 8009, 8012, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 8012, 8010);
  g->Binary(ynn_binary_multiply, 8009, 8010, 3018);
  g->Matmul(3018, 3016, 3019, false, false);
  g->Concat({3012,3019}, 3020, 1);
}

// Scope: "Layer29 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer29AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(3020, 3021, {0,2,1,3});
  g->FuseDims(3021, 3022, 2, 2);
  g->Quantize(3022, 3024, 0.015071368776261806, 0);
  g->Transpose(9109, 6295, {1,0});
  g->Binary(ynn_binary_multiply, 5815, 6294, 6291);
  g->Dot(3024, 6295, YNN_INVALID_VALUE_ID, 6290, 1);
  g->DequantizeTensor(6290, YNN_INVALID_VALUE_ID, 6291, 6292);
  g->QuantizeTensor(6292, 8595, 6293, 3025);
  g->Dequantize(3025, 3026, 0.02063991315662861, 0);
}

// Scope: "Layer29 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer29Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2978, 2979);
  g->Reduce(ynn_reduce_sum, 2979, 8000, {2}, true);
  g->ShapeProduct(2979, 7999, {2});
  g->Binary(ynn_binary_divide, 8000, 7999, 2980);
  g->Binary(ynn_binary_add, 2980, 8647, 2981);
  g->Unary(ynn_unary_rsqrt, 2981, 2983);
  g->Binary(ynn_binary_multiply, 2978, 2983, 2984);
  g->Binary(ynn_binary_multiply, 2984, 9098, 2985);
  BuildLayer29AttentionQueryProjection(ctx);
  BuildLayer29AttentionSdpa(ctx);
  BuildLayer29AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 3026, 3027);
  g->Reduce(ynn_reduce_sum, 3027, 8014, {2}, true);
  g->ShapeProduct(3027, 8013, {2});
  g->Binary(ynn_binary_divide, 8014, 8013, 3028);
  g->Binary(ynn_binary_add, 3028, 8647, 3029);
  g->Unary(ynn_unary_rsqrt, 3029, 3030);
  g->Binary(ynn_binary_multiply, 3026, 3030, 3031);
  g->Binary(ynn_binary_multiply, 3031, 9105, 3032);
  g->Binary(ynn_binary_add, 3032, 2978, 3033);
}

// Scope: "Layer29 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer29Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3033, 3035);
  g->Reduce(ynn_reduce_sum, 3035, 8020, {2}, true);
  g->ShapeProduct(3035, 8019, {2});
  g->Binary(ynn_binary_divide, 8020, 8019, 3036);
  g->Binary(ynn_binary_add, 3036, 8647, 3037);
  g->Unary(ynn_unary_rsqrt, 3037, 3038);
  g->Binary(ynn_binary_multiply, 3033, 3038, 3039);
  g->Binary(ynn_binary_multiply, 3039, 9108, 3040);
  g->Quantize(3040, 3041, 0.01604880578815937, 0);
  g->Transpose(9102, 6302, {1,0});
  g->Binary(ynn_binary_multiply, 6299, 6301, 6297);
  g->Dot(3041, 6302, YNN_INVALID_VALUE_ID, 6296, 1);
  g->DequantizeTensor(6296, YNN_INVALID_VALUE_ID, 6297, 6298);
  g->QuantizeTensor(6298, 8595, 6300, 3042);
  g->Dequantize(3042, 3043, 0.022883867844939232, 0);
  g->Transpose(9101, 6307, {1,0});
  g->Binary(ynn_binary_multiply, 6299, 6306, 6304);
  g->Dot(3041, 6307, YNN_INVALID_VALUE_ID, 6303, 1);
  g->DequantizeTensor(6303, YNN_INVALID_VALUE_ID, 6304, 6305);
  g->QuantizeTensor(6305, 8595, 6300, 3045);
  g->Dequantize(3045, 3046, 0.022883867844939232, 0);
  g->Polynomial(3046, 8023, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8023, 8024);
  g->Binary(ynn_binary_add, 8024, 7161, 8021);
  g->Binary(ynn_binary_multiply, 3046, 7173, 8022);
  g->Binary(ynn_binary_multiply, 8022, 8021, 3047);
  g->Binary(ynn_binary_multiply, 3043, 3047, 3048);
  g->Quantize(3048, 3049, 0.01931595429778099, 0);
  g->Transpose(9100, 6314, {1,0});
  g->Binary(ynn_binary_multiply, 6311, 6313, 6309);
  g->Dot(3049, 6314, YNN_INVALID_VALUE_ID, 6308, 1);
  g->DequantizeTensor(6308, YNN_INVALID_VALUE_ID, 6309, 6310);
  g->QuantizeTensor(6310, 8595, 6312, 3050);
  g->Dequantize(3050, 3051, 0.008464759215712547, 0);
  g->Unary(ynn_unary_square, 3051, 3052);
  g->Reduce(ynn_reduce_sum, 3052, 8026, {2}, true);
  g->ShapeProduct(3052, 8025, {2});
  g->Binary(ynn_binary_divide, 8026, 8025, 3053);
  g->Binary(ynn_binary_add, 3053, 8647, 3054);
  g->Unary(ynn_unary_rsqrt, 3054, 3056);
  g->Binary(ynn_binary_multiply, 3051, 3056, 3057);
  g->Binary(ynn_binary_multiply, 3057, 9106, 3058);
  g->Binary(ynn_binary_add, 3058, 3033, 3059);
}

// Scope: "Layer29 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer29PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 3060, {0,0,29,0}, {-1,-1,1,-1});
  g->Reshape(3060, 3061, {1,1,256});
  g->Unary(ynn_unary_square, 3061, 3062);
  g->Reduce(ynn_reduce_sum, 3062, 8028, {2}, true);
  g->ShapeProduct(3062, 8027, {2});
  g->Binary(ynn_binary_divide, 8028, 8027, 3063);
  g->Binary(ynn_binary_add, 3063, 8647, 3064);
  g->Unary(ynn_unary_rsqrt, 3064, 3065);
  g->Binary(ynn_binary_multiply, 3061, 3065, 3067);
  g->Binary(ynn_binary_multiply, 3067, 9401, 3068);
  g->Binary(ynn_binary_multiply, 9424, 8651, 3069);
  g->Binary(ynn_binary_add, 3068, 3069, 3070);
  g->Binary(ynn_binary_multiply, 3070, 8645, 3071);
  g->Quantize(3059, 3072, 0.21285858750343323, 0);
  g->Transpose(9103, 6327, {1,0});
  g->Binary(ynn_binary_multiply, 6325, 6326, 6323);
  g->Dot(3072, 6327, YNN_INVALID_VALUE_ID, 6322, 1);
  g->DequantizeTensor(6322, YNN_INVALID_VALUE_ID, 6323, 6324);
  g->QuantizeTensor(6324, 8595, 5531, 3073);
  g->Dequantize(3073, 3074, 0.1761811226606369, 0);
  g->Polynomial(3074, 8031, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8031, 8032);
  g->Binary(ynn_binary_add, 8032, 7161, 8029);
  g->Binary(ynn_binary_multiply, 3074, 7173, 8030);
  g->Binary(ynn_binary_multiply, 8030, 8029, 3075);
  g->Binary(ynn_binary_multiply, 3075, 3071, 3076);
  g->Quantize(3076, 3078, 1.425196886062622, 0);
  g->Transpose(9104, 6334, {1,0});
  g->Binary(ynn_binary_multiply, 6331, 6333, 6329);
  g->Dot(3078, 6334, YNN_INVALID_VALUE_ID, 6328, 1);
  g->DequantizeTensor(6328, YNN_INVALID_VALUE_ID, 6329, 6330);
  g->QuantizeTensor(6330, 8595, 6332, 3079);
  g->Dequantize(3079, 3080, 0.3287595808506012, 0);
  g->Unary(ynn_unary_square, 3080, 3081);
  g->Reduce(ynn_reduce_sum, 3081, 8034, {2}, true);
  g->ShapeProduct(3081, 8033, {2});
  g->Binary(ynn_binary_divide, 8034, 8033, 3082);
  g->Binary(ynn_binary_add, 3082, 8647, 3083);
  g->Unary(ynn_unary_rsqrt, 3083, 3084);
  g->Binary(ynn_binary_multiply, 3080, 3084, 3085);
  g->Binary(ynn_binary_multiply, 3085, 9107, 3086);
  g->Binary(ynn_binary_add, 3059, 3086, 3087);
  g->Binary(ynn_binary_multiply, 3087, 9099, 3089);
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
  g->Quantize(3095, 3096, 0.2586514949798584, 0);
  g->Transpose(9142, 6341, {1,0});
  g->Binary(ynn_binary_multiply, 6338, 6340, 6336);
  g->Dot(3096, 6341, YNN_INVALID_VALUE_ID, 6335, 1);
  g->DequantizeTensor(6335, YNN_INVALID_VALUE_ID, 6336, 6337);
  g->QuantizeTensor(6337, 8595, 6339, 3097);
  g->Dequantize(3097, 3098, 0.26771652698516846, 0);
  g->SplitDim(3098, 3100, 2, {8,256});
  g->Transpose(3100, 3101, {0,2,1,3});
  g->Unary(ynn_unary_square, 3101, 3102);
  g->Reduce(ynn_reduce_sum, 3102, 8040, {3}, true);
  g->ShapeProduct(3102, 8039, {3});
  g->Binary(ynn_binary_divide, 8040, 8039, 3103);
  g->Binary(ynn_binary_add, 3103, 8647, 3104);
  g->Unary(ynn_unary_rsqrt, 3104, 3105);
  g->Binary(ynn_binary_multiply, 3101, 3105, 3106);
  g->Binary(ynn_binary_multiply, 3106, 9141, 3107);
  g->Slice(3107, 3108, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3107, 3109, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3109, 3111);
  g->Concat({3111,3108}, 3112, 3);
  g->Binary(ynn_binary_multiply, 3107, 3141, 3113);
  g->Binary(ynn_binary_multiply, 3112, 4217, 3114);
  g->Binary(ynn_binary_add, 3113, 3114, 3115);
}

// Scope: "Layer30 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer30AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9508, 3116, 0.0059552486054599285, 0);
  g->Dequantize(9532, 3117, 0.047244105488061905, 0);
  g->Slice(3115, 3118, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(3116, 3119, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(3117, 3120, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(3118, 3119, 3122, false, true);
  g->Mask(3122, 8700, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8700, 8044, {-1}, true);
  g->Binary(ynn_binary_subtract, 8700, 8044, 8041);
  g->Unary(ynn_unary_exp, 8041, 8042);
  g->Reduce(ynn_reduce_sum, 8042, 8045, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 8045, 8043);
  g->Binary(ynn_binary_multiply, 8042, 8043, 3123);
  g->Matmul(3123, 3120, 3124, false, false);
  g->Slice(3115, 3125, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(3116, 3126, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(3117, 3127, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(3125, 3126, 3128, false, true);
  g->Mask(3128, 8701, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8701, 8049, {-1}, true);
  g->Binary(ynn_binary_subtract, 8701, 8049, 8046);
  g->Unary(ynn_unary_exp, 8046, 8047);
  g->Reduce(ynn_reduce_sum, 8047, 8050, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 8050, 8048);
  g->Binary(ynn_binary_multiply, 8047, 8048, 3129);
  g->Matmul(3129, 3127, 3131, false, false);
  g->Concat({3124,3131}, 3132, 1);
}

// Scope: "Layer30 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer30AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(3132, 3133, {0,2,1,3});
  g->FuseDims(3133, 3134, 2, 2);
  g->Quantize(3134, 3135, 0.019192922860383987, 0);
  g->Transpose(9140, 6348, {1,0});
  g->Binary(ynn_binary_multiply, 6345, 6347, 6343);
  g->Dot(3135, 6348, YNN_INVALID_VALUE_ID, 6342, 1);
  g->DequantizeTensor(6342, YNN_INVALID_VALUE_ID, 6343, 6344);
  g->QuantizeTensor(6344, 8595, 6346, 3136);
  g->Dequantize(3136, 3137, 0.07175232470035553, 0);
}

// Scope: "Layer30 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer30Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3089, 3090);
  g->Reduce(ynn_reduce_sum, 3090, 8036, {2}, true);
  g->ShapeProduct(3090, 8035, {2});
  g->Binary(ynn_binary_divide, 8036, 8035, 3091);
  g->Binary(ynn_binary_add, 3091, 8647, 3092);
  g->Unary(ynn_unary_rsqrt, 3092, 3093);
  g->Binary(ynn_binary_multiply, 3089, 3093, 3094);
  g->Binary(ynn_binary_multiply, 3094, 9129, 3095);
  BuildLayer30AttentionQueryProjection(ctx);
  BuildLayer30AttentionSdpa(ctx);
  BuildLayer30AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 3137, 3138);
  g->Reduce(ynn_reduce_sum, 3138, 8052, {2}, true);
  g->ShapeProduct(3138, 8051, {2});
  g->Binary(ynn_binary_divide, 8052, 8051, 3139);
  g->Binary(ynn_binary_add, 3139, 8647, 3140);
  g->Unary(ynn_unary_rsqrt, 3140, 3144);
  g->Binary(ynn_binary_multiply, 3137, 3144, 3145);
  g->Binary(ynn_binary_multiply, 3145, 9136, 3146);
  g->Binary(ynn_binary_add, 3146, 3089, 3147);
}

// Scope: "Layer30 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer30Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3147, 3148);
  g->Reduce(ynn_reduce_sum, 3148, 8054, {2}, true);
  g->ShapeProduct(3148, 8053, {2});
  g->Binary(ynn_binary_divide, 8054, 8053, 3149);
  g->Binary(ynn_binary_add, 3149, 8647, 3150);
  g->Unary(ynn_unary_rsqrt, 3150, 3151);
  g->Binary(ynn_binary_multiply, 3147, 3151, 3152);
  g->Binary(ynn_binary_multiply, 3152, 9139, 3153);
  g->Quantize(3153, 3155, 0.020873267203569412, 0);
  g->Transpose(9133, 6359, {1,0});
  g->Binary(ynn_binary_multiply, 6357, 6358, 6355);
  g->Dot(3155, 6359, YNN_INVALID_VALUE_ID, 6354, 1);
  g->DequantizeTensor(6354, YNN_INVALID_VALUE_ID, 6355, 6356);
  g->QuantizeTensor(6356, 8595, 5922, 3156);
  g->Dequantize(3156, 3157, 0.0274360328912735, 0);
  g->Transpose(9132, 6364, {1,0});
  g->Binary(ynn_binary_multiply, 6357, 6363, 6361);
  g->Dot(3155, 6364, YNN_INVALID_VALUE_ID, 6360, 1);
  g->DequantizeTensor(6360, YNN_INVALID_VALUE_ID, 6361, 6362);
  g->QuantizeTensor(6362, 8595, 5922, 3158);
  g->Dequantize(3158, 3159, 0.0274360328912735, 0);
  g->Polynomial(3159, 8057, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8057, 8058);
  g->Binary(ynn_binary_add, 8058, 7161, 8055);
  g->Binary(ynn_binary_multiply, 3159, 7173, 8056);
  g->Binary(ynn_binary_multiply, 8056, 8055, 3160);
  g->Binary(ynn_binary_multiply, 3157, 3160, 3161);
  g->Quantize(3161, 3162, 0.027805127203464508, 0);
  g->Transpose(9131, 6371, {1,0});
  g->Binary(ynn_binary_multiply, 6368, 6370, 6366);
  g->Dot(3162, 6371, YNN_INVALID_VALUE_ID, 6365, 1);
  g->DequantizeTensor(6365, YNN_INVALID_VALUE_ID, 6366, 6367);
  g->QuantizeTensor(6367, 8595, 6369, 3163);
  g->Dequantize(3163, 3165, 0.014151409268379211, 0);
  g->Unary(ynn_unary_square, 3165, 3166);
  g->Reduce(ynn_reduce_sum, 3166, 8060, {2}, true);
  g->ShapeProduct(3166, 8059, {2});
  g->Binary(ynn_binary_divide, 8060, 8059, 3167);
  g->Binary(ynn_binary_add, 3167, 8647, 3168);
  g->Unary(ynn_unary_rsqrt, 3168, 3169);
  g->Binary(ynn_binary_multiply, 3165, 3169, 3170);
  g->Binary(ynn_binary_multiply, 3170, 9137, 3171);
  g->Binary(ynn_binary_add, 3171, 3147, 3172);
}

// Scope: "Layer30 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer30PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 3173, {0,0,30,0}, {-1,-1,1,-1});
  g->Reshape(3173, 3174, {1,1,256});
  g->Unary(ynn_unary_square, 3174, 3176);
  g->Reduce(ynn_reduce_sum, 3176, 8062, {2}, true);
  g->ShapeProduct(3176, 8061, {2});
  g->Binary(ynn_binary_divide, 8062, 8061, 3177);
  g->Binary(ynn_binary_add, 3177, 8647, 3178);
  g->Unary(ynn_unary_rsqrt, 3178, 3179);
  g->Binary(ynn_binary_multiply, 3174, 3179, 3180);
  g->Binary(ynn_binary_multiply, 3180, 9401, 3181);
  g->Binary(ynn_binary_multiply, 9426, 8651, 3182);
  g->Binary(ynn_binary_add, 3181, 3182, 3183);
  g->Binary(ynn_binary_multiply, 3183, 8645, 3184);
  g->Quantize(3172, 3185, 0.13111315667629242, 0);
  g->Transpose(9134, 6378, {1,0});
  g->Binary(ynn_binary_multiply, 6375, 6377, 6373);
  g->Dot(3185, 6378, YNN_INVALID_VALUE_ID, 6372, 1);
  g->DequantizeTensor(6372, YNN_INVALID_VALUE_ID, 6373, 6374);
  g->QuantizeTensor(6374, 8595, 6376, 3187);
  g->Dequantize(3187, 3188, 0.25590550899505615, 0);
  g->Polynomial(3188, 8065, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8065, 8066);
  g->Binary(ynn_binary_add, 8066, 7161, 8063);
  g->Binary(ynn_binary_multiply, 3188, 7173, 8064);
  g->Binary(ynn_binary_multiply, 8064, 8063, 3189);
  g->Binary(ynn_binary_multiply, 3189, 3184, 3190);
  g->Quantize(3190, 3191, 2.236220359802246, 0);
  g->Transpose(9135, 6385, {1,0});
  g->Binary(ynn_binary_multiply, 6382, 6384, 6380);
  g->Dot(3191, 6385, YNN_INVALID_VALUE_ID, 6379, 1);
  g->DequantizeTensor(6379, YNN_INVALID_VALUE_ID, 6380, 6381);
  g->QuantizeTensor(6381, 8595, 6383, 3192);
  g->Dequantize(3192, 3193, 0.5313407778739929, 0);
  g->Unary(ynn_unary_square, 3193, 3194);
  g->Reduce(ynn_reduce_sum, 3194, 8068, {2}, true);
  g->ShapeProduct(3194, 8067, {2});
  g->Binary(ynn_binary_divide, 8068, 8067, 3195);
  g->Binary(ynn_binary_add, 3195, 8647, 3196);
  g->Unary(ynn_unary_rsqrt, 3196, 3198);
  g->Binary(ynn_binary_multiply, 3193, 3198, 3199);
  g->Binary(ynn_binary_multiply, 3199, 9138, 3200);
  g->Binary(ynn_binary_add, 3172, 3200, 3201);
  g->Binary(ynn_binary_multiply, 3201, 9130, 3202);
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
  g->Quantize(3209, 3210, 0.3303837180137634, 0);
  g->Transpose(9156, 6392, {1,0});
  g->Binary(ynn_binary_multiply, 6389, 6391, 6387);
  g->Dot(3210, 6392, YNN_INVALID_VALUE_ID, 6386, 1);
  g->DequantizeTensor(6386, YNN_INVALID_VALUE_ID, 6387, 6388);
  g->QuantizeTensor(6388, 8595, 6390, 3211);
  g->Dequantize(3211, 3212, 0.3208661377429962, 0);
  g->SplitDim(3212, 3213, 2, {8,256});
  g->Transpose(3213, 3214, {0,2,1,3});
  g->Unary(ynn_unary_square, 3214, 3215);
  g->Reduce(ynn_reduce_sum, 3215, 8074, {3}, true);
  g->ShapeProduct(3215, 8073, {3});
  g->Binary(ynn_binary_divide, 8074, 8073, 3216);
  g->Binary(ynn_binary_add, 3216, 8647, 3217);
  g->Unary(ynn_unary_rsqrt, 3217, 3218);
  g->Binary(ynn_binary_multiply, 3214, 3218, 3220);
  g->Binary(ynn_binary_multiply, 3220, 9155, 3221);
  g->Slice(3221, 3222, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3221, 3223, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3223, 3224);
  g->Concat({3224,3222}, 3225, 3);
  g->Binary(ynn_binary_multiply, 3221, 3141, 3226);
  g->Binary(ynn_binary_multiply, 3225, 4217, 3227);
  g->Binary(ynn_binary_add, 3226, 3227, 3228);
}

// Scope: "Layer31 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer31AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9508, 3229, 0.0059552486054599285, 0);
  g->Dequantize(9532, 3231, 0.047244105488061905, 0);
  g->Slice(3228, 3232, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(3229, 3233, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(3231, 3234, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(3232, 3233, 3235, false, true);
  g->Mask(3235, 8702, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8702, 8078, {-1}, true);
  g->Binary(ynn_binary_subtract, 8702, 8078, 8075);
  g->Unary(ynn_unary_exp, 8075, 8076);
  g->Reduce(ynn_reduce_sum, 8076, 8079, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 8079, 8077);
  g->Binary(ynn_binary_multiply, 8076, 8077, 3236);
  g->Matmul(3236, 3234, 3237, false, false);
  g->Slice(3228, 3238, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(3229, 3239, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(3231, 3241, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(3238, 3239, 3242, false, true);
  g->Mask(3242, 8703, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8703, 8083, {-1}, true);
  g->Binary(ynn_binary_subtract, 8703, 8083, 8080);
  g->Unary(ynn_unary_exp, 8080, 8081);
  g->Reduce(ynn_reduce_sum, 8081, 8084, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 8084, 8082);
  g->Binary(ynn_binary_multiply, 8081, 8082, 3243);
  g->Matmul(3243, 3241, 3244, false, false);
  g->Concat({3237,3244}, 3245, 1);
}

// Scope: "Layer31 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer31AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(3245, 3246, {0,2,1,3});
  g->FuseDims(3246, 3247, 2, 2);
  g->Quantize(3247, 3248, 0.019808080047369003, 0);
  g->Transpose(9154, 6398, {1,0});
  g->Binary(ynn_binary_multiply, 5911, 6397, 6394);
  g->Dot(3248, 6398, YNN_INVALID_VALUE_ID, 6393, 1);
  g->DequantizeTensor(6393, YNN_INVALID_VALUE_ID, 6394, 6395);
  g->QuantizeTensor(6395, 8595, 6396, 3249);
  g->Dequantize(3249, 3252, 0.12575629353523254, 0);
}

// Scope: "Layer31 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer31Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3202, 3203);
  g->Reduce(ynn_reduce_sum, 3203, 8072, {2}, true);
  g->ShapeProduct(3203, 8071, {2});
  g->Binary(ynn_binary_divide, 8072, 8071, 3204);
  g->Binary(ynn_binary_add, 3204, 8647, 3205);
  g->Unary(ynn_unary_rsqrt, 3205, 3206);
  g->Binary(ynn_binary_multiply, 3202, 3206, 3207);
  g->Binary(ynn_binary_multiply, 3207, 9143, 3209);
  BuildLayer31AttentionQueryProjection(ctx);
  BuildLayer31AttentionSdpa(ctx);
  BuildLayer31AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 3252, 3253);
  g->Reduce(ynn_reduce_sum, 3253, 8086, {2}, true);
  g->ShapeProduct(3253, 8085, {2});
  g->Binary(ynn_binary_divide, 8086, 8085, 3254);
  g->Binary(ynn_binary_add, 3254, 8647, 3255);
  g->Unary(ynn_unary_rsqrt, 3255, 3256);
  g->Binary(ynn_binary_multiply, 3252, 3256, 3257);
  g->Binary(ynn_binary_multiply, 3257, 9150, 3258);
  g->Binary(ynn_binary_add, 3258, 3202, 3259);
}

// Scope: "Layer31 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer31Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3259, 3260);
  g->Reduce(ynn_reduce_sum, 3260, 8088, {2}, true);
  g->ShapeProduct(3260, 8087, {2});
  g->Binary(ynn_binary_divide, 8088, 8087, 3261);
  g->Binary(ynn_binary_add, 3261, 8647, 3263);
  g->Unary(ynn_unary_rsqrt, 3263, 3264);
  g->Binary(ynn_binary_multiply, 3259, 3264, 3265);
  g->Binary(ynn_binary_multiply, 3265, 9153, 3266);
  g->Quantize(3266, 3267, 0.019890448078513145, 0);
  g->Transpose(9147, 6404, {1,0});
  g->Binary(ynn_binary_multiply, 6402, 6403, 6400);
  g->Dot(3267, 6404, YNN_INVALID_VALUE_ID, 6399, 1);
  g->DequantizeTensor(6399, YNN_INVALID_VALUE_ID, 6400, 6401);
  g->QuantizeTensor(6401, 8595, 5103, 3268);
  g->Dequantize(3268, 3269, 0.025836624205112457, 0);
  g->Transpose(9146, 6409, {1,0});
  g->Binary(ynn_binary_multiply, 6402, 6408, 6406);
  g->Dot(3267, 6409, YNN_INVALID_VALUE_ID, 6405, 1);
  g->DequantizeTensor(6405, YNN_INVALID_VALUE_ID, 6406, 6407);
  g->QuantizeTensor(6407, 8595, 5103, 3270);
  g->Dequantize(3270, 3271, 0.025836624205112457, 0);
  g->Polynomial(3271, 8091, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8091, 8092);
  g->Binary(ynn_binary_add, 8092, 7161, 8089);
  g->Binary(ynn_binary_multiply, 3271, 7173, 8090);
  g->Binary(ynn_binary_multiply, 8090, 8089, 3273);
  g->Binary(ynn_binary_multiply, 3269, 3273, 3274);
  g->Quantize(3274, 3275, 0.03248032554984093, 0);
  g->Transpose(9145, 6416, {1,0});
  g->Binary(ynn_binary_multiply, 6413, 6415, 6411);
  g->Dot(3275, 6416, YNN_INVALID_VALUE_ID, 6410, 1);
  g->DequantizeTensor(6410, YNN_INVALID_VALUE_ID, 6411, 6412);
  g->QuantizeTensor(6412, 8595, 6414, 3276);
  g->Dequantize(3276, 3277, 0.018060656264424324, 0);
  g->Unary(ynn_unary_square, 3277, 3278);
  g->Reduce(ynn_reduce_sum, 3278, 8094, {2}, true);
  g->ShapeProduct(3278, 8093, {2});
  g->Binary(ynn_binary_divide, 8094, 8093, 3279);
  g->Binary(ynn_binary_add, 3279, 8647, 3280);
  g->Unary(ynn_unary_rsqrt, 3280, 3281);
  g->Binary(ynn_binary_multiply, 3277, 3281, 3282);
  g->Binary(ynn_binary_multiply, 3282, 9151, 3284);
  g->Binary(ynn_binary_add, 3284, 3259, 3285);
}

// Scope: "Layer31 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer31PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 3286, {0,0,31,0}, {-1,-1,1,-1});
  g->Reshape(3286, 3287, {1,1,256});
  g->Unary(ynn_unary_square, 3287, 3288);
  g->Reduce(ynn_reduce_sum, 3288, 8096, {2}, true);
  g->ShapeProduct(3288, 8095, {2});
  g->Binary(ynn_binary_divide, 8096, 8095, 3289);
  g->Binary(ynn_binary_add, 3289, 8647, 3290);
  g->Unary(ynn_unary_rsqrt, 3290, 3291);
  g->Binary(ynn_binary_multiply, 3287, 3291, 3292);
  g->Binary(ynn_binary_multiply, 3292, 9401, 3293);
  g->Binary(ynn_binary_multiply, 9427, 8651, 3295);
  g->Binary(ynn_binary_add, 3293, 3295, 3296);
  g->Binary(ynn_binary_multiply, 3296, 8645, 3297);
  g->Quantize(3285, 3298, 0.1624065637588501, 0);
  g->Transpose(9148, 6430, {1,0});
  g->Binary(ynn_binary_multiply, 6427, 6429, 6425);
  g->Dot(3298, 6430, YNN_INVALID_VALUE_ID, 6424, 1);
  g->DequantizeTensor(6424, YNN_INVALID_VALUE_ID, 6425, 6426);
  g->QuantizeTensor(6426, 8595, 6428, 3299);
  g->Dequantize(3299, 3300, 0.20078741014003754, 0);
  g->Polynomial(3300, 8099, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8099, 8100);
  g->Binary(ynn_binary_add, 8100, 7161, 8097);
  g->Binary(ynn_binary_multiply, 3300, 7173, 8098);
  g->Binary(ynn_binary_multiply, 8098, 8097, 3301);
  g->Binary(ynn_binary_multiply, 3301, 3297, 3302);
  g->Quantize(3302, 3303, 1.7559055089950562, 0);
  g->Transpose(9149, 6437, {1,0});
  g->Binary(ynn_binary_multiply, 6434, 6436, 6432);
  g->Dot(3303, 6437, YNN_INVALID_VALUE_ID, 6431, 1);
  g->DequantizeTensor(6431, YNN_INVALID_VALUE_ID, 6432, 6433);
  g->QuantizeTensor(6433, 8595, 6435, 3304);
  g->Dequantize(3304, 3306, 0.38641682267189026, 0);
  g->Unary(ynn_unary_square, 3306, 3307);
  g->Reduce(ynn_reduce_sum, 3307, 8102, {2}, true);
  g->ShapeProduct(3307, 8101, {2});
  g->Binary(ynn_binary_divide, 8102, 8101, 3308);
  g->Binary(ynn_binary_add, 3308, 8647, 3309);
  g->Unary(ynn_unary_rsqrt, 3309, 3310);
  g->Binary(ynn_binary_multiply, 3306, 3310, 3311);
  g->Binary(ynn_binary_multiply, 3311, 9152, 3312);
  g->Binary(ynn_binary_add, 3285, 3312, 3313);
  g->Binary(ynn_binary_multiply, 3313, 9144, 3314);
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
  g->Quantize(3321, 3322, 0.3205936551094055, 0);
  g->Transpose(9170, 6443, {1,0});
  g->Binary(ynn_binary_multiply, 6441, 6442, 6439);
  g->Dot(3322, 6443, YNN_INVALID_VALUE_ID, 6438, 1);
  g->DequantizeTensor(6438, YNN_INVALID_VALUE_ID, 6439, 6440);
  g->QuantizeTensor(6440, 8595, 5018, 3323);
  g->Dequantize(3323, 3324, 0.31102362275123596, 0);
  g->SplitDim(3324, 3325, 2, {8,256});
  g->Transpose(3325, 3326, {0,2,1,3});
  g->Unary(ynn_unary_square, 3326, 3328);
  g->Reduce(ynn_reduce_sum, 3328, 8110, {3}, true);
  g->ShapeProduct(3328, 8109, {3});
  g->Binary(ynn_binary_divide, 8110, 8109, 3329);
  g->Binary(ynn_binary_add, 3329, 8647, 3330);
  g->Unary(ynn_unary_rsqrt, 3330, 3331);
  g->Binary(ynn_binary_multiply, 3326, 3331, 3332);
  g->Binary(ynn_binary_multiply, 3332, 9169, 3333);
  g->Slice(3333, 3334, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3333, 3335, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3335, 3336);
  g->Concat({3336,3334}, 3337, 3);
  g->Binary(ynn_binary_multiply, 3333, 3141, 3339);
  g->Binary(ynn_binary_multiply, 3337, 4217, 3340);
  g->Binary(ynn_binary_add, 3339, 3340, 3341);
}

// Scope: "Layer32 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer32AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9508, 3342, 0.0059552486054599285, 0);
  g->Dequantize(9532, 3343, 0.047244105488061905, 0);
  g->Slice(3341, 3344, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(3342, 3345, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(3343, 3346, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(3344, 3345, 3347, false, true);
  g->Mask(3347, 8704, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8704, 8114, {-1}, true);
  g->Binary(ynn_binary_subtract, 8704, 8114, 8111);
  g->Unary(ynn_unary_exp, 8111, 8112);
  g->Reduce(ynn_reduce_sum, 8112, 8115, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 8115, 8113);
  g->Binary(ynn_binary_multiply, 8112, 8113, 3349);
  g->Matmul(3349, 3346, 3350, false, false);
  g->Slice(3341, 3351, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(3342, 3352, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(3343, 3353, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(3351, 3352, 3354, false, true);
  g->Mask(3354, 8705, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8705, 8119, {-1}, true);
  g->Binary(ynn_binary_subtract, 8705, 8119, 8116);
  g->Unary(ynn_unary_exp, 8116, 8117);
  g->Reduce(ynn_reduce_sum, 8117, 8120, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 8120, 8118);
  g->Binary(ynn_binary_multiply, 8117, 8118, 3355);
  g->Matmul(3355, 3353, 3356, false, false);
  g->Concat({3350,3356}, 3357, 1);
}

// Scope: "Layer32 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer32AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(3357, 3360, {0,2,1,3});
  g->FuseDims(3360, 3361, 2, 2);
  g->Quantize(3361, 3362, 0.019562017172574997, 0);
  g->Transpose(9168, 6457, {1,0});
  g->Binary(ynn_binary_multiply, 6454, 6456, 6452);
  g->Dot(3362, 6457, YNN_INVALID_VALUE_ID, 6451, 1);
  g->DequantizeTensor(6451, YNN_INVALID_VALUE_ID, 6452, 6453);
  g->QuantizeTensor(6453, 8595, 6455, 3363);
  g->Dequantize(3363, 3364, 0.08170928806066513, 0);
}

// Scope: "Layer32 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer32Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3314, 3315);
  g->Reduce(ynn_reduce_sum, 3315, 8108, {2}, true);
  g->ShapeProduct(3315, 8107, {2});
  g->Binary(ynn_binary_divide, 8108, 8107, 3317);
  g->Binary(ynn_binary_add, 3317, 8647, 3318);
  g->Unary(ynn_unary_rsqrt, 3318, 3319);
  g->Binary(ynn_binary_multiply, 3314, 3319, 3320);
  g->Binary(ynn_binary_multiply, 3320, 9157, 3321);
  BuildLayer32AttentionQueryProjection(ctx);
  BuildLayer32AttentionSdpa(ctx);
  BuildLayer32AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 3364, 3365);
  g->Reduce(ynn_reduce_sum, 3365, 8122, {2}, true);
  g->ShapeProduct(3365, 8121, {2});
  g->Binary(ynn_binary_divide, 8122, 8121, 3366);
  g->Binary(ynn_binary_add, 3366, 8647, 3367);
  g->Unary(ynn_unary_rsqrt, 3367, 3368);
  g->Binary(ynn_binary_multiply, 3364, 3368, 3369);
  g->Binary(ynn_binary_multiply, 3369, 9164, 3371);
  g->Binary(ynn_binary_add, 3371, 3314, 3372);
}

// Scope: "Layer32 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer32Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3372, 3373);
  g->Reduce(ynn_reduce_sum, 3373, 8124, {2}, true);
  g->ShapeProduct(3373, 8123, {2});
  g->Binary(ynn_binary_divide, 8124, 8123, 3374);
  g->Binary(ynn_binary_add, 3374, 8647, 3375);
  g->Unary(ynn_unary_rsqrt, 3375, 3376);
  g->Binary(ynn_binary_multiply, 3372, 3376, 3377);
  g->Binary(ynn_binary_multiply, 3377, 9167, 3378);
  g->Quantize(3378, 3379, 0.025895588099956512, 0);
  g->Transpose(9161, 6464, {1,0});
  g->Binary(ynn_binary_multiply, 6461, 6463, 6459);
  g->Dot(3379, 6464, YNN_INVALID_VALUE_ID, 6458, 1);
  g->DequantizeTensor(6458, YNN_INVALID_VALUE_ID, 6459, 6460);
  g->QuantizeTensor(6460, 8595, 6462, 3380);
  g->Dequantize(3380, 3382, 0.039862215518951416, 0);
  g->Transpose(9160, 6469, {1,0});
  g->Binary(ynn_binary_multiply, 6461, 6468, 6466);
  g->Dot(3379, 6469, YNN_INVALID_VALUE_ID, 6465, 1);
  g->DequantizeTensor(6465, YNN_INVALID_VALUE_ID, 6466, 6467);
  g->QuantizeTensor(6467, 8595, 6462, 3383);
  g->Dequantize(3383, 3384, 0.039862215518951416, 0);
  g->Polynomial(3384, 8129, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8129, 8130);
  g->Binary(ynn_binary_add, 8130, 7161, 8127);
  g->Binary(ynn_binary_multiply, 3384, 7173, 8128);
  g->Binary(ynn_binary_multiply, 8128, 8127, 3385);
  g->Binary(ynn_binary_multiply, 3382, 3385, 3386);
  g->Quantize(3386, 3387, 0.0664370134472847, 0);
  g->Transpose(9159, 6475, {1,0});
  g->Binary(ynn_binary_multiply, 5218, 6474, 6471);
  g->Dot(3387, 6475, YNN_INVALID_VALUE_ID, 6470, 1);
  g->DequantizeTensor(6470, YNN_INVALID_VALUE_ID, 6471, 6472);
  g->QuantizeTensor(6472, 8595, 6473, 3388);
  g->Dequantize(3388, 3389, 0.028853626921772957, 0);
  g->Unary(ynn_unary_square, 3389, 3390);
  g->Reduce(ynn_reduce_sum, 3390, 8132, {2}, true);
  g->ShapeProduct(3390, 8131, {2});
  g->Binary(ynn_binary_divide, 8132, 8131, 3392);
  g->Binary(ynn_binary_add, 3392, 8647, 3393);
  g->Unary(ynn_unary_rsqrt, 3393, 3394);
  g->Binary(ynn_binary_multiply, 3389, 3394, 3395);
  g->Binary(ynn_binary_multiply, 3395, 9165, 3396);
  g->Binary(ynn_binary_add, 3396, 3372, 3397);
}

// Scope: "Layer32 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer32PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 3398, {0,0,32,0}, {-1,-1,1,-1});
  g->Reshape(3398, 3399, {1,1,256});
  g->Unary(ynn_unary_square, 3399, 3400);
  g->Reduce(ynn_reduce_sum, 3400, 8134, {2}, true);
  g->ShapeProduct(3400, 8133, {2});
  g->Binary(ynn_binary_divide, 8134, 8133, 3401);
  g->Binary(ynn_binary_add, 3401, 8647, 3403);
  g->Unary(ynn_unary_rsqrt, 3403, 3404);
  g->Binary(ynn_binary_multiply, 3399, 3404, 3405);
  g->Binary(ynn_binary_multiply, 3405, 9401, 3406);
  g->Binary(ynn_binary_multiply, 9428, 8651, 3407);
  g->Binary(ynn_binary_add, 3406, 3407, 3408);
  g->Binary(ynn_binary_multiply, 3408, 8645, 3409);
  g->Quantize(3397, 3410, 0.1705654412508011, 0);
  g->Transpose(9162, 6482, {1,0});
  g->Binary(ynn_binary_multiply, 6479, 6481, 6477);
  g->Dot(3410, 6482, YNN_INVALID_VALUE_ID, 6476, 1);
  g->DequantizeTensor(6476, YNN_INVALID_VALUE_ID, 6477, 6478);
  g->QuantizeTensor(6478, 8595, 6480, 3411);
  g->Dequantize(3411, 3412, 0.23228347301483154, 0);
  g->Polynomial(3412, 8137, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8137, 8138);
  g->Binary(ynn_binary_add, 8138, 7161, 8135);
  g->Binary(ynn_binary_multiply, 3412, 7173, 8136);
  g->Binary(ynn_binary_multiply, 8136, 8135, 3414);
  g->Binary(ynn_binary_multiply, 3414, 3409, 3415);
  g->Quantize(3415, 3416, 1.881889820098877, 0);
  g->Transpose(9163, 6489, {1,0});
  g->Binary(ynn_binary_multiply, 6486, 6488, 6484);
  g->Dot(3416, 6489, YNN_INVALID_VALUE_ID, 6483, 1);
  g->DequantizeTensor(6483, YNN_INVALID_VALUE_ID, 6484, 6485);
  g->QuantizeTensor(6485, 8595, 6487, 3417);
  g->Dequantize(3417, 3418, 0.341701865196228, 0);
  g->Unary(ynn_unary_square, 3418, 3419);
  g->Reduce(ynn_reduce_sum, 3419, 8140, {2}, true);
  g->ShapeProduct(3419, 8139, {2});
  g->Binary(ynn_binary_divide, 8140, 8139, 3420);
  g->Binary(ynn_binary_add, 3420, 8647, 3421);
  g->Unary(ynn_unary_rsqrt, 3421, 3422);
  g->Binary(ynn_binary_multiply, 3418, 3422, 3423);
  g->Binary(ynn_binary_multiply, 3423, 9166, 3425);
  g->Binary(ynn_binary_add, 3397, 3425, 3426);
  g->Binary(ynn_binary_multiply, 3426, 9158, 3427);
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
  g->Quantize(3433, 3434, 0.248324915766716, 0);
  g->Transpose(9184, 6496, {1,0});
  g->Binary(ynn_binary_multiply, 6493, 6495, 6491);
  g->Dot(3434, 6496, YNN_INVALID_VALUE_ID, 6490, 1);
  g->DequantizeTensor(6490, YNN_INVALID_VALUE_ID, 6491, 6492);
  g->QuantizeTensor(6492, 8595, 6494, 3436);
  g->Dequantize(3436, 3437, 0.2893700897693634, 0);
  g->SplitDim(3437, 3438, 2, {8,256});
  g->Transpose(3438, 3439, {0,2,1,3});
  g->Unary(ynn_unary_square, 3439, 3440);
  g->Reduce(ynn_reduce_sum, 3440, 8144, {3}, true);
  g->ShapeProduct(3440, 8143, {3});
  g->Binary(ynn_binary_divide, 8144, 8143, 3441);
  g->Binary(ynn_binary_add, 3441, 8647, 3442);
  g->Unary(ynn_unary_rsqrt, 3442, 3443);
  g->Binary(ynn_binary_multiply, 3439, 3443, 3444);
  g->Binary(ynn_binary_multiply, 3444, 9183, 3445);
  g->Slice(3445, 3447, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3445, 3448, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3448, 3449);
  g->Concat({3449,3447}, 3450, 3);
  g->Binary(ynn_binary_multiply, 3445, 3141, 3451);
  g->Binary(ynn_binary_multiply, 3450, 4217, 3452);
  g->Binary(ynn_binary_add, 3451, 3452, 3453);
}

// Scope: "Layer33 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer33AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9508, 3454, 0.0059552486054599285, 0);
  g->Dequantize(9532, 3455, 0.047244105488061905, 0);
  g->Slice(3453, 3456, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(3454, 3458, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(3455, 3459, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(3456, 3458, 3460, false, true);
  g->Mask(3460, 8706, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8706, 8148, {-1}, true);
  g->Binary(ynn_binary_subtract, 8706, 8148, 8145);
  g->Unary(ynn_unary_exp, 8145, 8146);
  g->Reduce(ynn_reduce_sum, 8146, 8149, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 8149, 8147);
  g->Binary(ynn_binary_multiply, 8146, 8147, 3461);
  g->Matmul(3461, 3459, 3462, false, false);
  g->Slice(3453, 3463, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(3454, 3464, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(3455, 3465, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(3463, 3464, 3466, false, true);
  g->Mask(3466, 8707, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8707, 8155, {-1}, true);
  g->Binary(ynn_binary_subtract, 8707, 8155, 8152);
  g->Unary(ynn_unary_exp, 8152, 8153);
  g->Reduce(ynn_reduce_sum, 8153, 8156, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 8156, 8154);
  g->Binary(ynn_binary_multiply, 8153, 8154, 3469);
  g->Matmul(3469, 3465, 3470, false, false);
  g->Concat({3462,3470}, 3471, 1);
}

// Scope: "Layer33 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer33AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(3471, 3472, {0,2,1,3});
  g->FuseDims(3472, 3473, 2, 2);
  g->Quantize(3473, 3474, 0.019685048609972, 0);
  g->Transpose(9182, 6503, {1,0});
  g->Binary(ynn_binary_multiply, 6500, 6502, 6498);
  g->Dot(3474, 6503, YNN_INVALID_VALUE_ID, 6497, 1);
  g->DequantizeTensor(6497, YNN_INVALID_VALUE_ID, 6498, 6499);
  g->QuantizeTensor(6499, 8595, 6501, 3475);
  g->Dequantize(3475, 3476, 0.09176436066627502, 0);
}

// Scope: "Layer33 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer33Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3427, 3428);
  g->Reduce(ynn_reduce_sum, 3428, 8142, {2}, true);
  g->ShapeProduct(3428, 8141, {2});
  g->Binary(ynn_binary_divide, 8142, 8141, 3429);
  g->Binary(ynn_binary_add, 3429, 8647, 3430);
  g->Unary(ynn_unary_rsqrt, 3430, 3431);
  g->Binary(ynn_binary_multiply, 3427, 3431, 3432);
  g->Binary(ynn_binary_multiply, 3432, 9171, 3433);
  BuildLayer33AttentionQueryProjection(ctx);
  BuildLayer33AttentionSdpa(ctx);
  BuildLayer33AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 3476, 3477);
  g->Reduce(ynn_reduce_sum, 3477, 8158, {2}, true);
  g->ShapeProduct(3477, 8157, {2});
  g->Binary(ynn_binary_divide, 8158, 8157, 3479);
  g->Binary(ynn_binary_add, 3479, 8647, 3480);
  g->Unary(ynn_unary_rsqrt, 3480, 3481);
  g->Binary(ynn_binary_multiply, 3476, 3481, 3482);
  g->Binary(ynn_binary_multiply, 3482, 9178, 3483);
  g->Binary(ynn_binary_add, 3483, 3427, 3484);
}

// Scope: "Layer33 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer33Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3484, 3485);
  g->Reduce(ynn_reduce_sum, 3485, 8160, {2}, true);
  g->ShapeProduct(3485, 8159, {2});
  g->Binary(ynn_binary_divide, 8160, 8159, 3486);
  g->Binary(ynn_binary_add, 3486, 8647, 3487);
  g->Unary(ynn_unary_rsqrt, 3487, 3488);
  g->Binary(ynn_binary_multiply, 3484, 3488, 3490);
  g->Binary(ynn_binary_multiply, 3490, 9181, 3491);
  g->Quantize(3491, 3492, 0.025595715269446373, 0);
  g->Transpose(9175, 6510, {1,0});
  g->Binary(ynn_binary_multiply, 6507, 6509, 6505);
  g->Dot(3492, 6510, YNN_INVALID_VALUE_ID, 6504, 1);
  g->DequantizeTensor(6504, YNN_INVALID_VALUE_ID, 6505, 6506);
  g->QuantizeTensor(6506, 8595, 6508, 3493);
  g->Dequantize(3493, 3494, 0.03690946102142334, 0);
  g->Transpose(9174, 6515, {1,0});
  g->Binary(ynn_binary_multiply, 6507, 6514, 6512);
  g->Dot(3492, 6515, YNN_INVALID_VALUE_ID, 6511, 1);
  g->DequantizeTensor(6511, YNN_INVALID_VALUE_ID, 6512, 6513);
  g->QuantizeTensor(6513, 8595, 6508, 3495);
  g->Dequantize(3495, 3496, 0.03690946102142334, 0);
  g->Polynomial(3496, 8163, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8163, 8164);
  g->Binary(ynn_binary_add, 8164, 7161, 8161);
  g->Binary(ynn_binary_multiply, 3496, 7173, 8162);
  g->Binary(ynn_binary_multiply, 8162, 8161, 3497);
  g->Binary(ynn_binary_multiply, 3494, 3497, 3498);
  g->Quantize(3498, 3500, 0.06692913919687271, 0);
  g->Transpose(9173, 6522, {1,0});
  g->Binary(ynn_binary_multiply, 6519, 6521, 6517);
  g->Dot(3500, 6522, YNN_INVALID_VALUE_ID, 6516, 1);
  g->DequantizeTensor(6516, YNN_INVALID_VALUE_ID, 6517, 6518);
  g->QuantizeTensor(6518, 8595, 6520, 3501);
  g->Dequantize(3501, 3502, 0.033670417964458466, 0);
  g->Unary(ynn_unary_square, 3502, 3503);
  g->Reduce(ynn_reduce_sum, 3503, 8166, {2}, true);
  g->ShapeProduct(3503, 8165, {2});
  g->Binary(ynn_binary_divide, 8166, 8165, 3504);
  g->Binary(ynn_binary_add, 3504, 8647, 3505);
  g->Unary(ynn_unary_rsqrt, 3505, 3506);
  g->Binary(ynn_binary_multiply, 3502, 3506, 3507);
  g->Binary(ynn_binary_multiply, 3507, 9179, 3508);
  g->Binary(ynn_binary_add, 3508, 3484, 3509);
}

// Scope: "Layer33 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer33PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 3511, {0,0,33,0}, {-1,-1,1,-1});
  g->Reshape(3511, 3512, {1,1,256});
  g->Unary(ynn_unary_square, 3512, 3513);
  g->Reduce(ynn_reduce_sum, 3513, 8168, {2}, true);
  g->ShapeProduct(3513, 8167, {2});
  g->Binary(ynn_binary_divide, 8168, 8167, 3514);
  g->Binary(ynn_binary_add, 3514, 8647, 3515);
  g->Unary(ynn_unary_rsqrt, 3515, 3516);
  g->Binary(ynn_binary_multiply, 3512, 3516, 3517);
  g->Binary(ynn_binary_multiply, 3517, 9401, 3518);
  g->Binary(ynn_binary_multiply, 9429, 8651, 3519);
  g->Binary(ynn_binary_add, 3518, 3519, 3520);
  g->Binary(ynn_binary_multiply, 3520, 8645, 3522);
  g->Quantize(3509, 3523, 0.1833108365535736, 0);
  g->Transpose(9176, 6529, {1,0});
  g->Binary(ynn_binary_multiply, 6526, 6528, 6524);
  g->Dot(3523, 6529, YNN_INVALID_VALUE_ID, 6523, 1);
  g->DequantizeTensor(6523, YNN_INVALID_VALUE_ID, 6524, 6525);
  g->QuantizeTensor(6525, 8595, 6527, 3524);
  g->Dequantize(3524, 3525, 0.19291339814662933, 0);
  g->Polynomial(3525, 8171, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8171, 8172);
  g->Binary(ynn_binary_add, 8172, 7161, 8169);
  g->Binary(ynn_binary_multiply, 3525, 7173, 8170);
  g->Binary(ynn_binary_multiply, 8170, 8169, 3526);
  g->Binary(ynn_binary_multiply, 3526, 3522, 3527);
  g->Quantize(3527, 3528, 2.0, 0);
  g->Transpose(9177, 6536, {1,0});
  g->Binary(ynn_binary_multiply, 6533, 6535, 6531);
  g->Dot(3528, 6536, YNN_INVALID_VALUE_ID, 6530, 1);
  g->DequantizeTensor(6530, YNN_INVALID_VALUE_ID, 6531, 6532);
  g->QuantizeTensor(6532, 8595, 6534, 3529);
  g->Dequantize(3529, 3530, 0.3256397247314453, 0);
  g->Unary(ynn_unary_square, 3530, 3531);
  g->Reduce(ynn_reduce_sum, 3531, 8174, {2}, true);
  g->ShapeProduct(3531, 8173, {2});
  g->Binary(ynn_binary_divide, 8174, 8173, 3533);
  g->Binary(ynn_binary_add, 3533, 8647, 3534);
  g->Unary(ynn_unary_rsqrt, 3534, 3535);
  g->Binary(ynn_binary_multiply, 3530, 3535, 3536);
  g->Binary(ynn_binary_multiply, 3536, 9180, 3537);
  g->Binary(ynn_binary_add, 3509, 3537, 3538);
  g->Binary(ynn_binary_multiply, 3538, 9172, 3539);
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
  g->Quantize(3546, 3547, 0.39901354908943176, 0);
  g->Transpose(9198, 6550, {1,0});
  g->Binary(ynn_binary_multiply, 6547, 6549, 6545);
  g->Dot(3547, 6550, YNN_INVALID_VALUE_ID, 6544, 1);
  g->DequantizeTensor(6544, YNN_INVALID_VALUE_ID, 6545, 6546);
  g->QuantizeTensor(6546, 8595, 6548, 3548);
  g->Dequantize(3548, 3549, 0.3700787425041199, 0);
  g->SplitDim(3549, 3550, 2, {8,256});
  g->Transpose(3550, 3551, {0,2,1,3});
  g->Unary(ynn_unary_square, 3551, 3552);
  g->Reduce(ynn_reduce_sum, 3552, 8178, {3}, true);
  g->ShapeProduct(3552, 8177, {3});
  g->Binary(ynn_binary_divide, 8178, 8177, 3553);
  g->Binary(ynn_binary_add, 3553, 8647, 3555);
  g->Unary(ynn_unary_rsqrt, 3555, 3556);
  g->Binary(ynn_binary_multiply, 3551, 3556, 3557);
  g->Binary(ynn_binary_multiply, 3557, 9197, 3558);
  g->Slice(3558, 3559, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3558, 3560, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3560, 3561);
  g->Concat({3561,3559}, 3562, 3);
  g->Binary(ynn_binary_multiply, 3558, 3141, 3563);
  g->Binary(ynn_binary_multiply, 3562, 4217, 3564);
  g->Binary(ynn_binary_add, 3563, 3564, 3566);
}

// Scope: "Layer34 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer34AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9508, 3567, 0.0059552486054599285, 0);
  g->Dequantize(9532, 3568, 0.047244105488061905, 0);
  g->Slice(3566, 3569, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(3567, 3570, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(3568, 3571, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(3569, 3570, 3572, false, true);
  g->Mask(3572, 8708, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8708, 8182, {-1}, true);
  g->Binary(ynn_binary_subtract, 8708, 8182, 8179);
  g->Unary(ynn_unary_exp, 8179, 8180);
  g->Reduce(ynn_reduce_sum, 8180, 8183, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 8183, 8181);
  g->Binary(ynn_binary_multiply, 8180, 8181, 3573);
  g->Matmul(3573, 3571, 3574, false, false);
  g->Slice(3566, 3577, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(3567, 3578, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(3568, 3579, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(3577, 3578, 3580, false, true);
  g->Mask(3580, 8709, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8709, 8187, {-1}, true);
  g->Binary(ynn_binary_subtract, 8709, 8187, 8184);
  g->Unary(ynn_unary_exp, 8184, 8185);
  g->Reduce(ynn_reduce_sum, 8185, 8188, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 8188, 8186);
  g->Binary(ynn_binary_multiply, 8185, 8186, 3581);
  g->Matmul(3581, 3579, 3582, false, false);
  g->Concat({3574,3582}, 3583, 1);
}

// Scope: "Layer34 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer34AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(3583, 3584, {0,2,1,3});
  g->FuseDims(3584, 3585, 2, 2);
  g->Quantize(3585, 3587, 0.01857776567339897, 0);
  g->Transpose(9196, 6557, {1,0});
  g->Binary(ynn_binary_multiply, 6554, 6556, 6552);
  g->Dot(3587, 6557, YNN_INVALID_VALUE_ID, 6551, 1);
  g->DequantizeTensor(6551, YNN_INVALID_VALUE_ID, 6552, 6553);
  g->QuantizeTensor(6553, 8595, 6555, 3588);
  g->Dequantize(3588, 3589, 0.07984723150730133, 0);
}

// Scope: "Layer34 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer34Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3539, 3540);
  g->Reduce(ynn_reduce_sum, 3540, 8176, {2}, true);
  g->ShapeProduct(3540, 8175, {2});
  g->Binary(ynn_binary_divide, 8176, 8175, 3541);
  g->Binary(ynn_binary_add, 3541, 8647, 3542);
  g->Unary(ynn_unary_rsqrt, 3542, 3544);
  g->Binary(ynn_binary_multiply, 3539, 3544, 3545);
  g->Binary(ynn_binary_multiply, 3545, 9185, 3546);
  BuildLayer34AttentionQueryProjection(ctx);
  BuildLayer34AttentionSdpa(ctx);
  BuildLayer34AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 3589, 3590);
  g->Reduce(ynn_reduce_sum, 3590, 8192, {2}, true);
  g->ShapeProduct(3590, 8191, {2});
  g->Binary(ynn_binary_divide, 8192, 8191, 3591);
  g->Binary(ynn_binary_add, 3591, 8647, 3592);
  g->Unary(ynn_unary_rsqrt, 3592, 3593);
  g->Binary(ynn_binary_multiply, 3589, 3593, 3594);
  g->Binary(ynn_binary_multiply, 3594, 9192, 3595);
  g->Binary(ynn_binary_add, 3595, 3539, 3596);
}

// Scope: "Layer34 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer34Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3596, 3598);
  g->Reduce(ynn_reduce_sum, 3598, 8194, {2}, true);
  g->ShapeProduct(3598, 8193, {2});
  g->Binary(ynn_binary_divide, 8194, 8193, 3599);
  g->Binary(ynn_binary_add, 3599, 8647, 3600);
  g->Unary(ynn_unary_rsqrt, 3600, 3601);
  g->Binary(ynn_binary_multiply, 3596, 3601, 3602);
  g->Binary(ynn_binary_multiply, 3602, 9195, 3603);
  g->Quantize(3603, 3604, 0.037028808146715164, 0);
  g->Transpose(9189, 6563, {1,0});
  g->Binary(ynn_binary_multiply, 6561, 6562, 6559);
  g->Dot(3604, 6563, YNN_INVALID_VALUE_ID, 6558, 1);
  g->DequantizeTensor(6558, YNN_INVALID_VALUE_ID, 6559, 6560);
  g->QuantizeTensor(6560, 8595, 5794, 3605);
  g->Dequantize(3605, 3606, 0.06299213320016861, 0);
  g->Transpose(9188, 6568, {1,0});
  g->Binary(ynn_binary_multiply, 6561, 6567, 6565);
  g->Dot(3604, 6568, YNN_INVALID_VALUE_ID, 6564, 1);
  g->DequantizeTensor(6564, YNN_INVALID_VALUE_ID, 6565, 6566);
  g->QuantizeTensor(6566, 8595, 5794, 3608);
  g->Dequantize(3608, 3609, 0.06299213320016861, 0);
  g->Polynomial(3609, 8197, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8197, 8198);
  g->Binary(ynn_binary_add, 8198, 7161, 8195);
  g->Binary(ynn_binary_multiply, 3609, 7173, 8196);
  g->Binary(ynn_binary_multiply, 8196, 8195, 3610);
  g->Binary(ynn_binary_multiply, 3606, 3610, 3611);
  g->Quantize(3611, 3612, 0.23917324841022491, 0);
  g->Transpose(9187, 6575, {1,0});
  g->Binary(ynn_binary_multiply, 6572, 6574, 6570);
  g->Dot(3612, 6575, YNN_INVALID_VALUE_ID, 6569, 1);
  g->DequantizeTensor(6569, YNN_INVALID_VALUE_ID, 6570, 6571);
  g->QuantizeTensor(6571, 8595, 6573, 3613);
  g->Dequantize(3613, 3614, 0.136443629860878, 0);
  g->Unary(ynn_unary_square, 3614, 3615);
  g->Reduce(ynn_reduce_sum, 3615, 8200, {2}, true);
  g->ShapeProduct(3615, 8199, {2});
  g->Binary(ynn_binary_divide, 8200, 8199, 3616);
  g->Binary(ynn_binary_add, 3616, 8647, 3617);
  g->Unary(ynn_unary_rsqrt, 3617, 3619);
  g->Binary(ynn_binary_multiply, 3614, 3619, 3620);
  g->Binary(ynn_binary_multiply, 3620, 9193, 3621);
  g->Binary(ynn_binary_add, 3621, 3596, 3622);
}

// Scope: "Layer34 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer34PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 3623, {0,0,34,0}, {-1,-1,1,-1});
  g->Reshape(3623, 3624, {1,1,256});
  g->Unary(ynn_unary_square, 3624, 3625);
  g->Reduce(ynn_reduce_sum, 3625, 8202, {2}, true);
  g->ShapeProduct(3625, 8201, {2});
  g->Binary(ynn_binary_divide, 8202, 8201, 3626);
  g->Binary(ynn_binary_add, 3626, 8647, 3627);
  g->Unary(ynn_unary_rsqrt, 3627, 3628);
  g->Binary(ynn_binary_multiply, 3624, 3628, 3630);
  g->Binary(ynn_binary_multiply, 3630, 9401, 3631);
  g->Binary(ynn_binary_multiply, 9430, 8651, 3632);
  g->Binary(ynn_binary_add, 3631, 3632, 3633);
  g->Binary(ynn_binary_multiply, 3633, 8645, 3634);
  g->Quantize(3622, 3635, 0.38806524872779846, 0);
  g->Transpose(9190, 6582, {1,0});
  g->Binary(ynn_binary_multiply, 6579, 6581, 6577);
  g->Dot(3635, 6582, YNN_INVALID_VALUE_ID, 6576, 1);
  g->DequantizeTensor(6576, YNN_INVALID_VALUE_ID, 6577, 6578);
  g->QuantizeTensor(6578, 8595, 6580, 3636);
  g->Dequantize(3636, 3637, 0.17125985026359558, 0);
  g->Polynomial(3637, 8205, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8205, 8206);
  g->Binary(ynn_binary_add, 8206, 7161, 8203);
  g->Binary(ynn_binary_multiply, 3637, 7173, 8204);
  g->Binary(ynn_binary_multiply, 8204, 8203, 3638);
  g->Binary(ynn_binary_multiply, 3638, 3634, 3639);
  g->Quantize(3639, 3641, 2.771653652191162, 0);
  g->Transpose(9191, 6589, {1,0});
  g->Binary(ynn_binary_multiply, 6586, 6588, 6584);
  g->Dot(3641, 6589, YNN_INVALID_VALUE_ID, 6583, 1);
  g->DequantizeTensor(6583, YNN_INVALID_VALUE_ID, 6584, 6585);
  g->QuantizeTensor(6585, 8595, 6587, 3642);
  g->Dequantize(3642, 3643, 0.28765690326690674, 0);
  g->Unary(ynn_unary_square, 3643, 3644);
  g->Reduce(ynn_reduce_sum, 3644, 8208, {2}, true);
  g->ShapeProduct(3644, 8207, {2});
  g->Binary(ynn_binary_divide, 8208, 8207, 3645);
  g->Binary(ynn_binary_add, 3645, 8647, 3646);
  g->Unary(ynn_unary_rsqrt, 3646, 3647);
  g->Binary(ynn_binary_multiply, 3643, 3647, 3648);
  g->Binary(ynn_binary_multiply, 3648, 9194, 3649);
  g->Binary(ynn_binary_add, 3622, 3649, 3650);
  g->Binary(ynn_binary_multiply, 3650, 9186, 3652);
}

// Scope: "Layer34"
LAB_YNN_BUILDER_NOINLINE void BuildLayer34(Context& ctx) {
  BuildLayer34Attention(ctx);
  BuildLayer34Mlp(ctx);
  BuildLayer34PerLayerEmbedding(ctx);
}

// Scope: "Layer35 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer35AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(3658, 3659, 0.40628930926322937, 0);
  g->Transpose(9212, 6595, {1,0});
  g->Binary(ynn_binary_multiply, 6593, 6594, 6591);
  g->Dot(3659, 6595, YNN_INVALID_VALUE_ID, 6590, 1);
  g->DequantizeTensor(6590, YNN_INVALID_VALUE_ID, 6591, 6592);
  g->QuantizeTensor(6592, 8595, 5007, 3660);
  g->Dequantize(3660, 3661, 0.3366141617298126, 0);
  g->SplitDim(3661, 3663, 2, {8,512});
  g->Transpose(3663, 3664, {0,2,1,3});
  g->Unary(ynn_unary_square, 3664, 3665);
  g->Reduce(ynn_reduce_sum, 3665, 8212, {3}, true);
  g->ShapeProduct(3665, 8211, {3});
  g->Binary(ynn_binary_divide, 8212, 8211, 3666);
  g->Binary(ynn_binary_add, 3666, 8647, 3667);
  g->Unary(ynn_unary_rsqrt, 3667, 3668);
  g->Binary(ynn_binary_multiply, 3664, 3668, 3669);
  g->Binary(ynn_binary_multiply, 3669, 9211, 3670);
  g->Slice(3670, 3671, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(3670, 3672, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 3672, 3674);
  g->Concat({3674,3671}, 3675, 3);
  g->Binary(ynn_binary_multiply, 3670, 4830, 3676);
  g->Binary(ynn_binary_multiply, 3675, 2, 3677);
  g->Binary(ynn_binary_add, 3676, 3677, 3678);
}

// Scope: "Layer35 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer35AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9509, 3679, 0.001091228099539876, 0);
  g->Dequantize(9533, 3680, 0.01785714365541935, 0);
  g->Slice(3678, 3681, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(3679, 3682, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(3680, 3683, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(3681, 3682, 3686, false, true);
  g->Mask(3686, 8710, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 8710, 8218, {-1}, true);
  g->Binary(ynn_binary_subtract, 8710, 8218, 8215);
  g->Unary(ynn_unary_exp, 8215, 8216);
  g->Reduce(ynn_reduce_sum, 8216, 8219, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 8219, 8217);
  g->Binary(ynn_binary_multiply, 8216, 8217, 3687);
  g->Matmul(3687, 3683, 3688, false, false);
  g->Slice(3678, 3689, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(3679, 3690, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(3680, 3691, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(3689, 3690, 3692, false, true);
  g->Mask(3692, 8711, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 8711, 8223, {-1}, true);
  g->Binary(ynn_binary_subtract, 8711, 8223, 8220);
  g->Unary(ynn_unary_exp, 8220, 8221);
  g->Reduce(ynn_reduce_sum, 8221, 8224, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 8224, 8222);
  g->Binary(ynn_binary_multiply, 8221, 8222, 3693);
  g->Matmul(3693, 3691, 3695, false, false);
  g->Concat({3688,3695}, 3696, 1);
}

// Scope: "Layer35 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer35AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(3696, 3697, {0,2,1,3});
  g->FuseDims(3697, 3698, 2, 2);
  g->Quantize(3698, 3699, 0.014025600627064705, 0);
  g->Transpose(9210, 6602, {1,0});
  g->Binary(ynn_binary_multiply, 6599, 6601, 6597);
  g->Dot(3699, 6602, YNN_INVALID_VALUE_ID, 6596, 1);
  g->DequantizeTensor(6596, YNN_INVALID_VALUE_ID, 6597, 6598);
  g->QuantizeTensor(6598, 8595, 6600, 3700);
  g->Dequantize(3700, 3701, 0.022187285125255585, 0);
}

// Scope: "Layer35 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer35Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3652, 3653);
  g->Reduce(ynn_reduce_sum, 3653, 8210, {2}, true);
  g->ShapeProduct(3653, 8209, {2});
  g->Binary(ynn_binary_divide, 8210, 8209, 3654);
  g->Binary(ynn_binary_add, 3654, 8647, 3655);
  g->Unary(ynn_unary_rsqrt, 3655, 3656);
  g->Binary(ynn_binary_multiply, 3652, 3656, 3657);
  g->Binary(ynn_binary_multiply, 3657, 9199, 3658);
  BuildLayer35AttentionQueryProjection(ctx);
  BuildLayer35AttentionSdpa(ctx);
  BuildLayer35AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 3701, 3702);
  g->Reduce(ynn_reduce_sum, 3702, 8226, {2}, true);
  g->ShapeProduct(3702, 8225, {2});
  g->Binary(ynn_binary_divide, 8226, 8225, 3703);
  g->Binary(ynn_binary_add, 3703, 8647, 3704);
  g->Unary(ynn_unary_rsqrt, 3704, 3706);
  g->Binary(ynn_binary_multiply, 3701, 3706, 3707);
  g->Binary(ynn_binary_multiply, 3707, 9206, 3708);
  g->Binary(ynn_binary_add, 3708, 3652, 3709);
}

// Scope: "Layer35 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer35Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3709, 3710);
  g->Reduce(ynn_reduce_sum, 3710, 8228, {2}, true);
  g->ShapeProduct(3710, 8227, {2});
  g->Binary(ynn_binary_divide, 8228, 8227, 3711);
  g->Binary(ynn_binary_add, 3711, 8647, 3712);
  g->Unary(ynn_unary_rsqrt, 3712, 3713);
  g->Binary(ynn_binary_multiply, 3709, 3713, 3714);
  g->Binary(ynn_binary_multiply, 3714, 9209, 3715);
  g->Quantize(3715, 3716, 0.016540825366973877, 0);
  g->Transpose(9203, 6608, {1,0});
  g->Binary(ynn_binary_multiply, 6606, 6607, 6604);
  g->Dot(3716, 6608, YNN_INVALID_VALUE_ID, 6603, 1);
  g->DequantizeTensor(6603, YNN_INVALID_VALUE_ID, 6604, 6605);
  g->QuantizeTensor(6605, 8595, 6190, 3717);
  g->Dequantize(3717, 3718, 0.02595965564250946, 0);
  g->Transpose(9202, 6613, {1,0});
  g->Binary(ynn_binary_multiply, 6606, 6612, 6610);
  g->Dot(3716, 6613, YNN_INVALID_VALUE_ID, 6609, 1);
  g->DequantizeTensor(6609, YNN_INVALID_VALUE_ID, 6610, 6611);
  g->QuantizeTensor(6611, 8595, 6190, 3719);
  g->Dequantize(3719, 3720, 0.02595965564250946, 0);
  g->Polynomial(3720, 8231, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8231, 8232);
  g->Binary(ynn_binary_add, 8232, 7161, 8229);
  g->Binary(ynn_binary_multiply, 3720, 7173, 8230);
  g->Binary(ynn_binary_multiply, 8230, 8229, 3721);
  g->Binary(ynn_binary_multiply, 3718, 3721, 3722);
  g->Quantize(3722, 3723, 0.034694891422986984, 0);
  g->Transpose(9201, 6620, {1,0});
  g->Binary(ynn_binary_multiply, 6617, 6619, 6615);
  g->Dot(3723, 6620, YNN_INVALID_VALUE_ID, 6614, 1);
  g->DequantizeTensor(6614, YNN_INVALID_VALUE_ID, 6615, 6616);
  g->QuantizeTensor(6616, 8595, 6618, 3724);
  g->Dequantize(3724, 3726, 0.024422448128461838, 0);
  g->Unary(ynn_unary_square, 3726, 3727);
  g->Reduce(ynn_reduce_sum, 3727, 8234, {2}, true);
  g->ShapeProduct(3727, 8233, {2});
  g->Binary(ynn_binary_divide, 8234, 8233, 3728);
  g->Binary(ynn_binary_add, 3728, 8647, 3729);
  g->Unary(ynn_unary_rsqrt, 3729, 3730);
  g->Binary(ynn_binary_multiply, 3726, 3730, 3731);
  g->Binary(ynn_binary_multiply, 3731, 9207, 3732);
  g->Binary(ynn_binary_add, 3732, 3709, 3733);
}

// Scope: "Layer35 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer35PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 3734, {0,0,35,0}, {-1,-1,1,-1});
  g->Reshape(3734, 3735, {1,1,256});
  g->Unary(ynn_unary_square, 3735, 3737);
  g->Reduce(ynn_reduce_sum, 3737, 8236, {2}, true);
  g->ShapeProduct(3737, 8235, {2});
  g->Binary(ynn_binary_divide, 8236, 8235, 3738);
  g->Binary(ynn_binary_add, 3738, 8647, 3739);
  g->Unary(ynn_unary_rsqrt, 3739, 3740);
  g->Binary(ynn_binary_multiply, 3735, 3740, 3741);
  g->Binary(ynn_binary_multiply, 3741, 9401, 3742);
  g->Binary(ynn_binary_multiply, 9431, 8651, 3743);
  g->Binary(ynn_binary_add, 3742, 3743, 3744);
  g->Binary(ynn_binary_multiply, 3744, 8645, 3745);
  g->Quantize(3733, 3746, 0.38799241185188293, 0);
  g->Transpose(9204, 6632, {1,0});
  g->Binary(ynn_binary_multiply, 6629, 6631, 6627);
  g->Dot(3746, 6632, YNN_INVALID_VALUE_ID, 6626, 1);
  g->DequantizeTensor(6626, YNN_INVALID_VALUE_ID, 6627, 6628);
  g->QuantizeTensor(6628, 8595, 6630, 3748);
  g->Dequantize(3748, 3749, 0.2224409580230713, 0);
  g->Polynomial(3749, 8239, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8239, 8240);
  g->Binary(ynn_binary_add, 8240, 7161, 8237);
  g->Binary(ynn_binary_multiply, 3749, 7173, 8238);
  g->Binary(ynn_binary_multiply, 8238, 8237, 3750);
  g->Binary(ynn_binary_multiply, 3750, 3745, 3751);
  g->Quantize(3751, 3752, 1.2677165269851685, 0);
  g->Transpose(9205, 6639, {1,0});
  g->Binary(ynn_binary_multiply, 6636, 6638, 6634);
  g->Dot(3752, 6639, YNN_INVALID_VALUE_ID, 6633, 1);
  g->DequantizeTensor(6633, YNN_INVALID_VALUE_ID, 6634, 6635);
  g->QuantizeTensor(6635, 8595, 6637, 3753);
  g->Dequantize(3753, 3754, 0.17961417138576508, 0);
  g->Unary(ynn_unary_square, 3754, 3755);
  g->Reduce(ynn_reduce_sum, 3755, 8242, {2}, true);
  g->ShapeProduct(3755, 8241, {2});
  g->Binary(ynn_binary_divide, 8242, 8241, 3756);
  g->Binary(ynn_binary_add, 3756, 8647, 3757);
  g->Unary(ynn_unary_rsqrt, 3757, 3759);
  g->Binary(ynn_binary_multiply, 3754, 3759, 3760);
  g->Binary(ynn_binary_multiply, 3760, 9208, 3761);
  g->Binary(ynn_binary_add, 3733, 3761, 3762);
  g->Binary(ynn_binary_multiply, 3762, 9200, 3763);
}

// Scope: "Layer35"
LAB_YNN_BUILDER_NOINLINE void BuildLayer35(Context& ctx) {
  BuildLayer35Attention(ctx);
  BuildLayer35Mlp(ctx);
  BuildLayer35PerLayerEmbedding(ctx);
}

}  // namespace BuildGemma4DecodeSource
