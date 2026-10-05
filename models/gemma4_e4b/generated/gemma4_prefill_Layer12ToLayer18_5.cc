// Generated YNNPACK builder; do not edit.
#include "gemma4_prefill_builder.h"

namespace BuildGemma4PrefillSource {

// Scope: "Layer12 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(707, 708, 0.11905524879693985, 0);
  g->Transpose(5372, 3353, {1,0});
  g->Binary(ynn_binary_multiply, 3350, 3352, 3348);
  g->Dot(708, 3353, YNN_INVALID_VALUE_ID, 3347, 1);
  g->DequantizeTensor(3347, YNN_INVALID_VALUE_ID, 3348, 3349);
  g->QuantizeTensor(3349, 5190, 3351, 709);
  g->Dequantize(709, 710, 0.2027559131383896, 0);
  g->SplitDim(710, 712, 2, {2,256});
  g->Transpose(712, 713, {0,2,1,3});
  g->Unary(ynn_unary_square, 713, 714);
  g->Reduce(ynn_reduce_sum, 714, 4557, {3}, true);
  g->ShapeProduct(714, 4556, {3});
  g->Binary(ynn_binary_divide, 4557, 4556, 715);
  g->Binary(ynn_binary_add, 715, 5241, 716);
  g->Unary(ynn_unary_rsqrt, 716, 717);
  g->Binary(ynn_binary_multiply, 713, 717, 718);
  g->Binary(ynn_binary_multiply, 718, 5371, 719);
  g->Slice(719, 720, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(719, 721, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 721, 723);
  g->Concat({723,720}, 724, 3);
  g->Binary(ynn_binary_multiply, 719, 2394, 725);
  g->Binary(ynn_binary_multiply, 724, 2498, 726);
  g->Binary(ynn_binary_add, 725, 726, 727);
  g->Transpose(5376, 3358, {1,0});
  g->Binary(ynn_binary_multiply, 3350, 3357, 3355);
  g->Dot(708, 3358, YNN_INVALID_VALUE_ID, 3354, 1);
  g->DequantizeTensor(3354, YNN_INVALID_VALUE_ID, 3355, 3356);
  g->QuantizeTensor(3356, 5190, 3351, 728);
  g->Dequantize(728, 729, 0.2027559131383896, 0);
  g->SplitDim(729, 730, 2, {2,256});
  g->Transpose(730, 731, {0,2,1,3});
  g->Unary(ynn_unary_square, 731, 734);
  g->Reduce(ynn_reduce_sum, 734, 4559, {3}, true);
  g->ShapeProduct(734, 4558, {3});
  g->Binary(ynn_binary_divide, 4559, 4558, 735);
  g->Binary(ynn_binary_add, 735, 5241, 736);
  g->Unary(ynn_unary_rsqrt, 736, 737);
  g->Binary(ynn_binary_multiply, 731, 737, 738);
}

// Scope: "Layer12 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(727, 739, 0.005684707313776016, 0);
  g->Append(5195, 739, 5717, 2, s2, s1);
  g->View(5717, 5765, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(738, 740, 0.047244105488061905, 0);
  g->Append(5219, 740, 5741, 2, s2, s1);
  g->View(5741, 5788, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer12 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(5375, 3364, {1,0});
  g->Binary(ynn_binary_multiply, 3350, 3363, 3360);
  g->Dot(708, 3364, YNN_INVALID_VALUE_ID, 3359, 1);
  g->DequantizeTensor(3359, YNN_INVALID_VALUE_ID, 3360, 3361);
  g->QuantizeTensor(3361, 5190, 3362, 742);
  g->Dequantize(742, 743, 0.20964568853378296, 0);
  g->SplitDim(743, 744, 2, {8,256});
  g->Transpose(744, 745, {0,2,1,3});
  g->Unary(ynn_unary_square, 745, 746);
  g->Reduce(ynn_reduce_sum, 746, 4561, {3}, true);
  g->ShapeProduct(746, 4560, {3});
  g->Binary(ynn_binary_divide, 4561, 4560, 747);
  g->Binary(ynn_binary_add, 747, 5241, 748);
  g->Unary(ynn_unary_rsqrt, 748, 749);
  g->Binary(ynn_binary_multiply, 745, 749, 751);
  g->Binary(ynn_binary_multiply, 751, 5374, 752);
  g->Slice(752, 753, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(752, 754, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 754, 755);
  g->Concat({755,753}, 756, 3);
  g->Binary(ynn_binary_multiply, 752, 2394, 757);
  g->Binary(ynn_binary_multiply, 756, 2498, 758);
  g->Binary(ynn_binary_add, 757, 758, 759);
}

// Scope: "Layer12 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(5765, 760, 0.005684707313776016, 0);
  g->Dequantize(5788, 762, 0.047244105488061905, 0);
  g->Slice(759, 763, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(760, 764, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(762, 765, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(763, 764, 766, false, true);
  g->Mask(766, 5252, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 5252, 4565, {-1}, true);
  g->Binary(ynn_binary_subtract, 5252, 4565, 4562);
  g->Unary(ynn_unary_exp, 4562, 4563);
  g->Reduce(ynn_reduce_sum, 4563, 4566, {-1}, true);
  g->Binary(ynn_binary_divide, 4364, 4566, 4564);
  g->Binary(ynn_binary_multiply, 4563, 4564, 767);
  g->Matmul(767, 765, 768, false, false);
  g->Slice(759, 769, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(760, 770, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(762, 772, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(769, 770, 773, false, true);
  g->Mask(773, 5253, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 5253, 4570, {-1}, true);
  g->Binary(ynn_binary_subtract, 5253, 4570, 4567);
  g->Unary(ynn_unary_exp, 4567, 4568);
  g->Reduce(ynn_reduce_sum, 4568, 4571, {-1}, true);
  g->Binary(ynn_binary_divide, 4364, 4571, 4569);
  g->Binary(ynn_binary_multiply, 4568, 4569, 774);
  g->Matmul(774, 772, 775, false, false);
  g->Concat({768,775}, 776, 1);
}

// Scope: "Layer12 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(776, 777, {0,2,1,3});
  g->FuseDims(777, 778, 2, 2);
  g->Quantize(778, 779, 0.028912410140037537, 0);
  g->Transpose(5373, 3371, {1,0});
  g->Binary(ynn_binary_multiply, 3368, 3370, 3366);
  g->Dot(779, 3371, YNN_INVALID_VALUE_ID, 3365, 1);
  g->DequantizeTensor(3365, YNN_INVALID_VALUE_ID, 3366, 3367);
  g->QuantizeTensor(3367, 5190, 3369, 780);
  g->Dequantize(780, 782, 0.11405377089977264, 0);
}

// Scope: "Layer12 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 701, 702);
  g->Reduce(ynn_reduce_sum, 702, 4555, {2}, true);
  g->ShapeProduct(702, 4554, {2});
  g->Binary(ynn_binary_divide, 4555, 4554, 703);
  g->Binary(ynn_binary_add, 703, 5241, 704);
  g->Unary(ynn_unary_rsqrt, 704, 705);
  g->Binary(ynn_binary_multiply, 701, 705, 706);
  g->Binary(ynn_binary_multiply, 706, 5360, 707);
  BuildLayer12AttentionKvProjection(ctx);
  BuildLayer12AttentionCacheUpdate(ctx);
  BuildLayer12AttentionQueryProjection(ctx);
  BuildLayer12AttentionSdpa(ctx);
  BuildLayer12AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 782, 783);
  g->Reduce(ynn_reduce_sum, 783, 4573, {2}, true);
  g->ShapeProduct(783, 4572, {2});
  g->Binary(ynn_binary_divide, 4573, 4572, 784);
  g->Binary(ynn_binary_add, 784, 5241, 785);
  g->Unary(ynn_unary_rsqrt, 785, 786);
  g->Binary(ynn_binary_multiply, 782, 786, 787);
  g->Binary(ynn_binary_multiply, 787, 5367, 788);
  g->Binary(ynn_binary_add, 788, 701, 789);
}

// Scope: "Layer12 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 789, 790);
  g->Reduce(ynn_reduce_sum, 790, 4575, {2}, true);
  g->ShapeProduct(790, 4574, {2});
  g->Binary(ynn_binary_divide, 4575, 4574, 791);
  g->Binary(ynn_binary_add, 791, 5241, 793);
  g->Unary(ynn_unary_rsqrt, 793, 794);
  g->Binary(ynn_binary_multiply, 789, 794, 795);
  g->Binary(ynn_binary_multiply, 795, 5370, 796);
  g->Quantize(796, 797, 0.029738755896687508, 0);
  g->Transpose(5364, 3378, {1,0});
  g->Binary(ynn_binary_multiply, 3375, 3377, 3373);
  g->Dot(797, 3378, YNN_INVALID_VALUE_ID, 3372, 1);
  g->DequantizeTensor(3372, YNN_INVALID_VALUE_ID, 3373, 3374);
  g->QuantizeTensor(3374, 5190, 3376, 798);
  g->Dequantize(798, 799, 0.05216536670923233, 0);
  g->Transpose(5363, 3383, {1,0});
  g->Binary(ynn_binary_multiply, 3375, 3382, 3380);
  g->Dot(797, 3383, YNN_INVALID_VALUE_ID, 3379, 1);
  g->DequantizeTensor(3379, YNN_INVALID_VALUE_ID, 3380, 3381);
  g->QuantizeTensor(3381, 5190, 3376, 800);
  g->Dequantize(800, 801, 0.05216536670923233, 0);
  g->Polynomial(801, 4578, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 4578, 4579);
  g->Binary(ynn_binary_add, 4579, 4364, 4576);
  g->Binary(ynn_binary_multiply, 801, 4376, 4577);
  g->Binary(ynn_binary_multiply, 4577, 4576, 802);
  g->Binary(ynn_binary_multiply, 799, 802, 803);
  g->Quantize(803, 804, 0.09350394457578659, 0);
  g->Transpose(5362, 3390, {1,0});
  g->Binary(ynn_binary_multiply, 3387, 3389, 3385);
  g->Dot(804, 3390, YNN_INVALID_VALUE_ID, 3384, 1);
  g->DequantizeTensor(3384, YNN_INVALID_VALUE_ID, 3385, 3386);
  g->QuantizeTensor(3386, 5190, 3388, 805);
  g->Dequantize(805, 806, 0.0321725495159626, 0);
  g->Unary(ynn_unary_square, 806, 807);
  g->Reduce(ynn_reduce_sum, 807, 4581, {2}, true);
  g->ShapeProduct(807, 4580, {2});
  g->Binary(ynn_binary_divide, 4581, 4580, 808);
  g->Binary(ynn_binary_add, 808, 5241, 809);
  g->Unary(ynn_unary_rsqrt, 809, 810);
  g->Binary(ynn_binary_multiply, 806, 810, 811);
  g->Binary(ynn_binary_multiply, 811, 5368, 813);
  g->Binary(ynn_binary_add, 813, 789, 814);
}

// Scope: "Layer12 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 815, {0,0,12,0}, {-1,-1,1,-1});
  g->Reshape(815, 816, {1,0,256});
  g->Unary(ynn_unary_square, 816, 817);
  g->Reduce(ynn_reduce_sum, 817, 4583, {2}, true);
  g->ShapeProduct(817, 4582, {2});
  g->Binary(ynn_binary_divide, 4583, 4582, 818);
  g->Binary(ynn_binary_add, 818, 5241, 819);
  g->Unary(ynn_unary_rsqrt, 819, 820);
  g->Binary(ynn_binary_multiply, 816, 820, 821);
  g->Binary(ynn_binary_multiply, 821, 5688, 822);
  g->Binary(ynn_binary_multiply, 5693, 5245, 824);
  g->Binary(ynn_binary_add, 822, 824, 825);
  g->Binary(ynn_binary_multiply, 825, 5240, 826);
  g->Quantize(814, 827, 0.6675296425819397, 0);
  g->Transpose(5365, 3402, {1,0});
  g->Binary(ynn_binary_multiply, 3399, 3401, 3397);
  g->Dot(827, 3402, YNN_INVALID_VALUE_ID, 3396, 1);
  g->DequantizeTensor(3396, YNN_INVALID_VALUE_ID, 3397, 3398);
  g->QuantizeTensor(3398, 5190, 3400, 828);
  g->Dequantize(828, 829, 0.09104331582784653, 0);
  g->Polynomial(829, 4586, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 4586, 4587);
  g->Binary(ynn_binary_add, 4587, 4364, 4584);
  g->Binary(ynn_binary_multiply, 829, 4376, 4585);
  g->Binary(ynn_binary_multiply, 4585, 4584, 830);
  g->Binary(ynn_binary_multiply, 830, 826, 831);
  g->Quantize(831, 832, 0.712598443031311, 0);
  g->Transpose(5366, 3409, {1,0});
  g->Binary(ynn_binary_multiply, 3406, 3408, 3404);
  g->Dot(832, 3409, YNN_INVALID_VALUE_ID, 3403, 1);
  g->DequantizeTensor(3403, YNN_INVALID_VALUE_ID, 3404, 3405);
  g->QuantizeTensor(3405, 5190, 3407, 833);
  g->Dequantize(833, 836, 0.15073752403259277, 0);
  g->Unary(ynn_unary_square, 836, 837);
  g->Reduce(ynn_reduce_sum, 837, 4589, {2}, true);
  g->ShapeProduct(837, 4588, {2});
  g->Binary(ynn_binary_divide, 4589, 4588, 838);
  g->Binary(ynn_binary_add, 838, 5241, 839);
  g->Unary(ynn_unary_rsqrt, 839, 840);
  g->Binary(ynn_binary_multiply, 836, 840, 841);
  g->Binary(ynn_binary_multiply, 841, 5369, 842);
  g->Binary(ynn_binary_add, 814, 842, 843);
  g->Binary(ynn_binary_multiply, 843, 5361, 844);
}

// Scope: "Layer12"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12(Context& ctx) {
  BuildLayer12Attention(ctx);
  BuildLayer12Mlp(ctx);
  BuildLayer12PerLayerEmbedding(ctx);
}

// Scope: "Layer13 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(851, 852, 0.11864537745714188, 0);
  g->Transpose(5389, 3416, {1,0});
  g->Binary(ynn_binary_multiply, 3413, 3415, 3411);
  g->Dot(852, 3416, YNN_INVALID_VALUE_ID, 3410, 1);
  g->DequantizeTensor(3410, YNN_INVALID_VALUE_ID, 3411, 3412);
  g->QuantizeTensor(3412, 5190, 3414, 853);
  g->Dequantize(853, 854, 0.18700788915157318, 0);
  g->SplitDim(854, 855, 2, {2,256});
  g->Transpose(855, 856, {0,2,1,3});
  g->Unary(ynn_unary_square, 856, 858);
  g->Reduce(ynn_reduce_sum, 858, 4593, {3}, true);
  g->ShapeProduct(858, 4592, {3});
  g->Binary(ynn_binary_divide, 4593, 4592, 859);
  g->Binary(ynn_binary_add, 859, 5241, 860);
  g->Unary(ynn_unary_rsqrt, 860, 861);
  g->Binary(ynn_binary_multiply, 856, 861, 862);
  g->Binary(ynn_binary_multiply, 862, 5388, 863);
  g->Slice(863, 864, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(863, 865, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 865, 866);
  g->Concat({866,864}, 867, 3);
  g->Binary(ynn_binary_multiply, 863, 2394, 869);
  g->Binary(ynn_binary_multiply, 867, 2498, 870);
  g->Binary(ynn_binary_add, 869, 870, 871);
  g->Transpose(5393, 3421, {1,0});
  g->Binary(ynn_binary_multiply, 3413, 3420, 3418);
  g->Dot(852, 3421, YNN_INVALID_VALUE_ID, 3417, 1);
  g->DequantizeTensor(3417, YNN_INVALID_VALUE_ID, 3418, 3419);
  g->QuantizeTensor(3419, 5190, 3414, 872);
  g->Dequantize(872, 873, 0.18700788915157318, 0);
  g->SplitDim(873, 874, 2, {2,256});
  g->Transpose(874, 875, {0,2,1,3});
  g->Unary(ynn_unary_square, 875, 876);
  g->Reduce(ynn_reduce_sum, 876, 4597, {3}, true);
  g->ShapeProduct(876, 4596, {3});
  g->Binary(ynn_binary_divide, 4597, 4596, 877);
  g->Binary(ynn_binary_add, 877, 5241, 879);
  g->Unary(ynn_unary_rsqrt, 879, 880);
  g->Binary(ynn_binary_multiply, 875, 880, 881);
}

// Scope: "Layer13 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(871, 882, 0.0057707298547029495, 0);
  g->Append(5196, 882, 5718, 2, s2, s1);
  g->View(5718, 5766, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(881, 883, 0.047244105488061905, 0);
  g->Append(5220, 883, 5742, 2, s2, s1);
  g->View(5742, 5789, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer13 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(5392, 3427, {1,0});
  g->Binary(ynn_binary_multiply, 3413, 3426, 3423);
  g->Dot(852, 3427, YNN_INVALID_VALUE_ID, 3422, 1);
  g->DequantizeTensor(3422, YNN_INVALID_VALUE_ID, 3423, 3424);
  g->QuantizeTensor(3424, 5190, 3425, 885);
  g->Dequantize(885, 886, 0.20570868253707886, 0);
  g->SplitDim(886, 887, 2, {8,256});
  g->Transpose(887, 888, {0,2,1,3});
  g->Unary(ynn_unary_square, 888, 889);
  g->Reduce(ynn_reduce_sum, 889, 4599, {3}, true);
  g->ShapeProduct(889, 4598, {3});
  g->Binary(ynn_binary_divide, 4599, 4598, 890);
  g->Binary(ynn_binary_add, 890, 5241, 891);
  g->Unary(ynn_unary_rsqrt, 891, 892);
  g->Binary(ynn_binary_multiply, 888, 892, 893);
  g->Binary(ynn_binary_multiply, 893, 5391, 894);
  g->Slice(894, 896, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(894, 897, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 897, 898);
  g->Concat({898,896}, 899, 3);
  g->Binary(ynn_binary_multiply, 894, 2394, 900);
  g->Binary(ynn_binary_multiply, 899, 2498, 901);
  g->Binary(ynn_binary_add, 900, 901, 902);
}

// Scope: "Layer13 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(5766, 903, 0.0057707298547029495, 0);
  g->Dequantize(5789, 904, 0.047244105488061905, 0);
  g->Slice(902, 905, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(903, 907, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(904, 908, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(905, 907, 909, false, true);
  g->Mask(909, 5254, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 5254, 4603, {-1}, true);
  g->Binary(ynn_binary_subtract, 5254, 4603, 4600);
  g->Unary(ynn_unary_exp, 4600, 4601);
  g->Reduce(ynn_reduce_sum, 4601, 4604, {-1}, true);
  g->Binary(ynn_binary_divide, 4364, 4604, 4602);
  g->Binary(ynn_binary_multiply, 4601, 4602, 910);
  g->Matmul(910, 908, 911, false, false);
  g->Slice(902, 912, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(903, 913, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(904, 914, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(912, 913, 915, false, true);
  g->Mask(915, 5255, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 5255, 4608, {-1}, true);
  g->Binary(ynn_binary_subtract, 5255, 4608, 4605);
  g->Unary(ynn_unary_exp, 4605, 4606);
  g->Reduce(ynn_reduce_sum, 4606, 4609, {-1}, true);
  g->Binary(ynn_binary_divide, 4364, 4609, 4607);
  g->Binary(ynn_binary_multiply, 4606, 4607, 916);
  g->Matmul(916, 914, 917, false, false);
  g->Concat({911,917}, 918, 1);
}

// Scope: "Layer13 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(918, 919, {0,2,1,3});
  g->FuseDims(919, 920, 2, 2);
  g->Quantize(920, 921, 0.023129930719733238, 0);
  g->Transpose(5390, 3434, {1,0});
  g->Binary(ynn_binary_multiply, 3431, 3433, 3429);
  g->Dot(921, 3434, YNN_INVALID_VALUE_ID, 3428, 1);
  g->DequantizeTensor(3428, YNN_INVALID_VALUE_ID, 3429, 3430);
  g->QuantizeTensor(3430, 5190, 3432, 922);
  g->Dequantize(922, 923, 0.0383908711373806, 0);
}

// Scope: "Layer13 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 844, 845);
  g->Reduce(ynn_reduce_sum, 845, 4591, {2}, true);
  g->ShapeProduct(845, 4590, {2});
  g->Binary(ynn_binary_divide, 4591, 4590, 847);
  g->Binary(ynn_binary_add, 847, 5241, 848);
  g->Unary(ynn_unary_rsqrt, 848, 849);
  g->Binary(ynn_binary_multiply, 844, 849, 850);
  g->Binary(ynn_binary_multiply, 850, 5377, 851);
  BuildLayer13AttentionKvProjection(ctx);
  BuildLayer13AttentionCacheUpdate(ctx);
  BuildLayer13AttentionQueryProjection(ctx);
  BuildLayer13AttentionSdpa(ctx);
  BuildLayer13AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 923, 924);
  g->Reduce(ynn_reduce_sum, 924, 4611, {2}, true);
  g->ShapeProduct(924, 4610, {2});
  g->Binary(ynn_binary_divide, 4611, 4610, 925);
  g->Binary(ynn_binary_add, 925, 5241, 926);
  g->Unary(ynn_unary_rsqrt, 926, 927);
  g->Binary(ynn_binary_multiply, 923, 927, 928);
  g->Binary(ynn_binary_multiply, 928, 5384, 929);
  g->Binary(ynn_binary_add, 929, 844, 930);
}

// Scope: "Layer13 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 930, 931);
  g->Reduce(ynn_reduce_sum, 931, 4613, {2}, true);
  g->ShapeProduct(931, 4612, {2});
  g->Binary(ynn_binary_divide, 4613, 4612, 932);
  g->Binary(ynn_binary_add, 932, 5241, 933);
  g->Unary(ynn_unary_rsqrt, 933, 934);
  g->Binary(ynn_binary_multiply, 930, 934, 937);
  g->Binary(ynn_binary_multiply, 937, 5387, 938);
  g->Quantize(938, 939, 0.02818576619029045, 0);
  g->Transpose(5381, 3440, {1,0});
  g->Binary(ynn_binary_multiply, 3438, 3439, 3436);
  g->Dot(939, 3440, YNN_INVALID_VALUE_ID, 3435, 1);
  g->DequantizeTensor(3435, YNN_INVALID_VALUE_ID, 3436, 3437);
  g->QuantizeTensor(3437, 5190, 3067, 940);
  g->Dequantize(940, 941, 0.04675197973847389, 0);
  g->Transpose(5380, 3445, {1,0});
  g->Binary(ynn_binary_multiply, 3438, 3444, 3442);
  g->Dot(939, 3445, YNN_INVALID_VALUE_ID, 3441, 1);
  g->DequantizeTensor(3441, YNN_INVALID_VALUE_ID, 3442, 3443);
  g->QuantizeTensor(3443, 5190, 3067, 942);
  g->Dequantize(942, 943, 0.04675197973847389, 0);
  g->Polynomial(943, 4616, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 4616, 4617);
  g->Binary(ynn_binary_add, 4617, 4364, 4614);
  g->Binary(ynn_binary_multiply, 943, 4376, 4615);
  g->Binary(ynn_binary_multiply, 4615, 4614, 944);
  g->Binary(ynn_binary_multiply, 941, 944, 945);
  g->Quantize(945, 946, 0.09202756732702255, 0);
  g->Transpose(5379, 3452, {1,0});
  g->Binary(ynn_binary_multiply, 3449, 3451, 3447);
  g->Dot(946, 3452, YNN_INVALID_VALUE_ID, 3446, 1);
  g->DequantizeTensor(3446, YNN_INVALID_VALUE_ID, 3447, 3448);
  g->QuantizeTensor(3448, 5190, 3450, 947);
  g->Dequantize(947, 948, 0.05065973475575447, 0);
  g->Unary(ynn_unary_square, 948, 949);
  g->Reduce(ynn_reduce_sum, 949, 4619, {2}, true);
  g->ShapeProduct(949, 4618, {2});
  g->Binary(ynn_binary_divide, 4619, 4618, 950);
  g->Binary(ynn_binary_add, 950, 5241, 951);
  g->Unary(ynn_unary_rsqrt, 951, 952);
  g->Binary(ynn_binary_multiply, 948, 952, 953);
  g->Binary(ynn_binary_multiply, 953, 5385, 954);
  g->Binary(ynn_binary_add, 954, 930, 955);
}

// Scope: "Layer13 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 956, {0,0,13,0}, {-1,-1,1,-1});
  g->Reshape(956, 957, {1,0,256});
  g->Unary(ynn_unary_square, 957, 958);
  g->Reduce(ynn_reduce_sum, 958, 4621, {2}, true);
  g->ShapeProduct(958, 4620, {2});
  g->Binary(ynn_binary_divide, 4621, 4620, 959);
  g->Binary(ynn_binary_add, 959, 5241, 960);
  g->Unary(ynn_unary_rsqrt, 960, 961);
  g->Binary(ynn_binary_multiply, 957, 961, 962);
  g->Binary(ynn_binary_multiply, 962, 5688, 963);
  g->Binary(ynn_binary_multiply, 5694, 5245, 964);
  g->Binary(ynn_binary_add, 963, 964, 965);
  g->Binary(ynn_binary_multiply, 965, 5240, 966);
  g->Quantize(955, 967, 0.698938250541687, 0);
  g->Transpose(5382, 3459, {1,0});
  g->Binary(ynn_binary_multiply, 3456, 3458, 3454);
  g->Dot(967, 3459, YNN_INVALID_VALUE_ID, 3453, 1);
  g->DequantizeTensor(3453, YNN_INVALID_VALUE_ID, 3454, 3455);
  g->QuantizeTensor(3455, 5190, 3457, 968);
  g->Dequantize(968, 969, 0.07775591313838959, 0);
  g->Polynomial(969, 4624, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 4624, 4625);
  g->Binary(ynn_binary_add, 4625, 4364, 4622);
  g->Binary(ynn_binary_multiply, 969, 4376, 4623);
  g->Binary(ynn_binary_multiply, 4623, 4622, 970);
  g->Binary(ynn_binary_multiply, 970, 966, 971);
  g->Quantize(971, 972, 0.4881889820098877, 0);
  g->Transpose(5383, 3466, {1,0});
  g->Binary(ynn_binary_multiply, 3463, 3465, 3461);
  g->Dot(972, 3466, YNN_INVALID_VALUE_ID, 3460, 1);
  g->DequantizeTensor(3460, YNN_INVALID_VALUE_ID, 3461, 3462);
  g->QuantizeTensor(3462, 5190, 3464, 973);
  g->Dequantize(973, 974, 0.15653027594089508, 0);
  g->Unary(ynn_unary_square, 974, 975);
  g->Reduce(ynn_reduce_sum, 975, 4627, {2}, true);
  g->ShapeProduct(975, 4626, {2});
  g->Binary(ynn_binary_divide, 4627, 4626, 977);
  g->Binary(ynn_binary_add, 977, 5241, 978);
  g->Unary(ynn_unary_rsqrt, 978, 979);
  g->Binary(ynn_binary_multiply, 974, 979, 980);
  g->Binary(ynn_binary_multiply, 980, 5386, 981);
  g->Binary(ynn_binary_add, 955, 981, 982);
  g->Binary(ynn_binary_multiply, 982, 5378, 983);
}

// Scope: "Layer13"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13(Context& ctx) {
  BuildLayer13Attention(ctx);
  BuildLayer13Mlp(ctx);
  BuildLayer13PerLayerEmbedding(ctx);
}

// Scope: "Layer14 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(990, 991, 0.1454738974571228, 0);
  g->Transpose(5406, 3479, {1,0});
  g->Binary(ynn_binary_multiply, 3476, 3478, 3474);
  g->Dot(991, 3479, YNN_INVALID_VALUE_ID, 3473, 1);
  g->DequantizeTensor(3473, YNN_INVALID_VALUE_ID, 3474, 3475);
  g->QuantizeTensor(3475, 5190, 3477, 992);
  g->Dequantize(992, 993, 0.25, 0);
  g->SplitDim(993, 994, 2, {2,256});
  g->Transpose(994, 995, {0,2,1,3});
  g->Unary(ynn_unary_square, 995, 996);
  g->Reduce(ynn_reduce_sum, 996, 4631, {3}, true);
  g->ShapeProduct(996, 4630, {3});
  g->Binary(ynn_binary_divide, 4631, 4630, 997);
  g->Binary(ynn_binary_add, 997, 5241, 999);
  g->Unary(ynn_unary_rsqrt, 999, 1000);
  g->Binary(ynn_binary_multiply, 995, 1000, 1001);
  g->Binary(ynn_binary_multiply, 1001, 5405, 1002);
  g->Slice(1002, 1003, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1002, 1004, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1004, 1005);
  g->Concat({1005,1003}, 1006, 3);
  g->Binary(ynn_binary_multiply, 1002, 2394, 1007);
  g->Binary(ynn_binary_multiply, 1006, 2498, 1008);
  g->Binary(ynn_binary_add, 1007, 1008, 1010);
  g->Transpose(5410, 3484, {1,0});
  g->Binary(ynn_binary_multiply, 3476, 3483, 3481);
  g->Dot(991, 3484, YNN_INVALID_VALUE_ID, 3480, 1);
  g->DequantizeTensor(3480, YNN_INVALID_VALUE_ID, 3481, 3482);
  g->QuantizeTensor(3482, 5190, 3477, 1011);
  g->Dequantize(1011, 1012, 0.25, 0);
  g->SplitDim(1012, 1013, 2, {2,256});
  g->Transpose(1013, 1014, {0,2,1,3});
  g->Unary(ynn_unary_square, 1014, 1015);
  g->Reduce(ynn_reduce_sum, 1015, 4633, {3}, true);
  g->ShapeProduct(1015, 4632, {3});
  g->Binary(ynn_binary_divide, 4633, 4632, 1016);
  g->Binary(ynn_binary_add, 1016, 5241, 1017);
  g->Unary(ynn_unary_rsqrt, 1017, 1018);
  g->Binary(ynn_binary_multiply, 1014, 1018, 1020);
}

// Scope: "Layer14 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(1010, 1021, 0.005712664220482111, 0);
  g->Append(5197, 1021, 5719, 2, s2, s1);
  g->View(5719, 5767, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(1020, 1022, 0.047244105488061905, 0);
  g->Append(5221, 1022, 5743, 2, s2, s1);
  g->View(5743, 5790, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer14 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(5409, 3490, {1,0});
  g->Binary(ynn_binary_multiply, 3476, 3489, 3486);
  g->Dot(991, 3490, YNN_INVALID_VALUE_ID, 3485, 1);
  g->DequantizeTensor(3485, YNN_INVALID_VALUE_ID, 3486, 3487);
  g->QuantizeTensor(3487, 5190, 3488, 1023);
  g->Dequantize(1023, 1024, 0.29133859276771545, 0);
  g->SplitDim(1024, 1026, 2, {8,256});
  g->Transpose(1026, 1027, {0,2,1,3});
  g->Unary(ynn_unary_square, 1027, 1028);
  g->Reduce(ynn_reduce_sum, 1028, 4637, {3}, true);
  g->ShapeProduct(1028, 4636, {3});
  g->Binary(ynn_binary_divide, 4637, 4636, 1029);
  g->Binary(ynn_binary_add, 1029, 5241, 1030);
  g->Unary(ynn_unary_rsqrt, 1030, 1031);
  g->Binary(ynn_binary_multiply, 1027, 1031, 1032);
  g->Binary(ynn_binary_multiply, 1032, 5408, 1033);
  g->Slice(1033, 1034, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1033, 1035, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1035, 1039);
  g->Concat({1039,1034}, 1040, 3);
  g->Binary(ynn_binary_multiply, 1033, 2394, 1041);
  g->Binary(ynn_binary_multiply, 1040, 2498, 1042);
  g->Binary(ynn_binary_add, 1041, 1042, 1043);
}

// Scope: "Layer14 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(5767, 1044, 0.005712664220482111, 0);
  g->Dequantize(5790, 1045, 0.047244105488061905, 0);
  g->Slice(1043, 1046, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(1044, 1047, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(1045, 1048, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(1046, 1047, 1050, false, true);
  g->Mask(1050, 5256, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 5256, 4641, {-1}, true);
  g->Binary(ynn_binary_subtract, 5256, 4641, 4638);
  g->Unary(ynn_unary_exp, 4638, 4639);
  g->Reduce(ynn_reduce_sum, 4639, 4642, {-1}, true);
  g->Binary(ynn_binary_divide, 4364, 4642, 4640);
  g->Binary(ynn_binary_multiply, 4639, 4640, 1051);
  g->Matmul(1051, 1048, 1052, false, false);
  g->Slice(1043, 1053, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(1044, 1054, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(1045, 1055, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(1053, 1054, 1056, false, true);
  g->Mask(1056, 5257, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 5257, 4646, {-1}, true);
  g->Binary(ynn_binary_subtract, 5257, 4646, 4643);
  g->Unary(ynn_unary_exp, 4643, 4644);
  g->Reduce(ynn_reduce_sum, 4644, 4647, {-1}, true);
  g->Binary(ynn_binary_divide, 4364, 4647, 4645);
  g->Binary(ynn_binary_multiply, 4644, 4645, 1057);
  g->Matmul(1057, 1055, 1059, false, false);
  g->Concat({1052,1059}, 1060, 1);
}

// Scope: "Layer14 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1060, 1061, {0,2,1,3});
  g->FuseDims(1061, 1062, 2, 2);
  g->Quantize(1062, 1063, 0.02472933940589428, 0);
  g->Transpose(5407, 3497, {1,0});
  g->Binary(ynn_binary_multiply, 3494, 3496, 3492);
  g->Dot(1063, 3497, YNN_INVALID_VALUE_ID, 3491, 1);
  g->DequantizeTensor(3491, YNN_INVALID_VALUE_ID, 3492, 3493);
  g->QuantizeTensor(3493, 5190, 3495, 1064);
  g->Dequantize(1064, 1065, 0.039510589092969894, 0);
}

// Scope: "Layer14 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 983, 984);
  g->Reduce(ynn_reduce_sum, 984, 4629, {2}, true);
  g->ShapeProduct(984, 4628, {2});
  g->Binary(ynn_binary_divide, 4629, 4628, 985);
  g->Binary(ynn_binary_add, 985, 5241, 986);
  g->Unary(ynn_unary_rsqrt, 986, 988);
  g->Binary(ynn_binary_multiply, 983, 988, 989);
  g->Binary(ynn_binary_multiply, 989, 5394, 990);
  BuildLayer14AttentionKvProjection(ctx);
  BuildLayer14AttentionCacheUpdate(ctx);
  BuildLayer14AttentionQueryProjection(ctx);
  BuildLayer14AttentionSdpa(ctx);
  BuildLayer14AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1065, 1066);
  g->Reduce(ynn_reduce_sum, 1066, 4649, {2}, true);
  g->ShapeProduct(1066, 4648, {2});
  g->Binary(ynn_binary_divide, 4649, 4648, 1067);
  g->Binary(ynn_binary_add, 1067, 5241, 1068);
  g->Unary(ynn_unary_rsqrt, 1068, 1070);
  g->Binary(ynn_binary_multiply, 1065, 1070, 1071);
  g->Binary(ynn_binary_multiply, 1071, 5401, 1072);
  g->Binary(ynn_binary_add, 1072, 983, 1073);
}

// Scope: "Layer14 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1073, 1074);
  g->Reduce(ynn_reduce_sum, 1074, 4651, {2}, true);
  g->ShapeProduct(1074, 4650, {2});
  g->Binary(ynn_binary_divide, 4651, 4650, 1075);
  g->Binary(ynn_binary_add, 1075, 5241, 1076);
  g->Unary(ynn_unary_rsqrt, 1076, 1077);
  g->Binary(ynn_binary_multiply, 1073, 1077, 1078);
  g->Binary(ynn_binary_multiply, 1078, 5404, 1079);
  g->Quantize(1079, 1081, 0.015675809234380722, 0);
  g->Transpose(5398, 3504, {1,0});
  g->Binary(ynn_binary_multiply, 3501, 3503, 3499);
  g->Dot(1081, 3504, YNN_INVALID_VALUE_ID, 3498, 1);
  g->DequantizeTensor(3498, YNN_INVALID_VALUE_ID, 3499, 3500);
  g->QuantizeTensor(3500, 5190, 3502, 1082);
  g->Dequantize(1082, 1083, 0.0216535534709692, 0);
  g->Transpose(5397, 3509, {1,0});
  g->Binary(ynn_binary_multiply, 3501, 3508, 3506);
  g->Dot(1081, 3509, YNN_INVALID_VALUE_ID, 3505, 1);
  g->DequantizeTensor(3505, YNN_INVALID_VALUE_ID, 3506, 3507);
  g->QuantizeTensor(3507, 5190, 3502, 1084);
  g->Dequantize(1084, 1085, 0.0216535534709692, 0);
  g->Polynomial(1085, 4654, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 4654, 4655);
  g->Binary(ynn_binary_add, 4655, 4364, 4652);
  g->Binary(ynn_binary_multiply, 1085, 4376, 4653);
  g->Binary(ynn_binary_multiply, 4653, 4652, 1086);
  g->Binary(ynn_binary_multiply, 1083, 1086, 1087);
  g->Quantize(1087, 1088, 0.02472933940589428, 0);
  g->Transpose(5396, 3515, {1,0});
  g->Binary(ynn_binary_multiply, 3494, 3514, 3511);
  g->Dot(1088, 3515, YNN_INVALID_VALUE_ID, 3510, 1);
  g->DequantizeTensor(3510, YNN_INVALID_VALUE_ID, 3511, 3512);
  g->QuantizeTensor(3512, 5190, 3513, 1089);
  g->Dequantize(1089, 1091, 0.01883137971162796, 0);
  g->Unary(ynn_unary_square, 1091, 1092);
  g->Reduce(ynn_reduce_sum, 1092, 4657, {2}, true);
  g->ShapeProduct(1092, 4656, {2});
  g->Binary(ynn_binary_divide, 4657, 4656, 1093);
  g->Binary(ynn_binary_add, 1093, 5241, 1094);
  g->Unary(ynn_unary_rsqrt, 1094, 1095);
  g->Binary(ynn_binary_multiply, 1091, 1095, 1096);
  g->Binary(ynn_binary_multiply, 1096, 5402, 1097);
  g->Binary(ynn_binary_add, 1097, 1073, 1098);
}

// Scope: "Layer14 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 1099, {0,0,14,0}, {-1,-1,1,-1});
  g->Reshape(1099, 1100, {1,0,256});
  g->Unary(ynn_unary_square, 1100, 1102);
  g->Reduce(ynn_reduce_sum, 1102, 4659, {2}, true);
  g->ShapeProduct(1102, 4658, {2});
  g->Binary(ynn_binary_divide, 4659, 4658, 1103);
  g->Binary(ynn_binary_add, 1103, 5241, 1104);
  g->Unary(ynn_unary_rsqrt, 1104, 1105);
  g->Binary(ynn_binary_multiply, 1100, 1105, 1106);
  g->Binary(ynn_binary_multiply, 1106, 5688, 1107);
  g->Binary(ynn_binary_multiply, 5695, 5245, 1108);
  g->Binary(ynn_binary_add, 1107, 1108, 1109);
  g->Binary(ynn_binary_multiply, 1109, 5240, 1110);
  g->Quantize(1098, 1111, 0.37186482548713684, 0);
  g->Transpose(5399, 3522, {1,0});
  g->Binary(ynn_binary_multiply, 3519, 3521, 3517);
  g->Dot(1111, 3522, YNN_INVALID_VALUE_ID, 3516, 1);
  g->DequantizeTensor(3516, YNN_INVALID_VALUE_ID, 3517, 3518);
  g->QuantizeTensor(3518, 5190, 3520, 1113);
  g->Dequantize(1113, 1114, 0.060531508177518845, 0);
  g->Polynomial(1114, 4662, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 4662, 4663);
  g->Binary(ynn_binary_add, 4663, 4364, 4660);
  g->Binary(ynn_binary_multiply, 1114, 4376, 4661);
  g->Binary(ynn_binary_multiply, 4661, 4660, 1115);
  g->Binary(ynn_binary_multiply, 1115, 1110, 1116);
  g->Quantize(1116, 1117, 0.3523622155189514, 0);
  g->Transpose(5400, 3529, {1,0});
  g->Binary(ynn_binary_multiply, 3526, 3528, 3524);
  g->Dot(1117, 3529, YNN_INVALID_VALUE_ID, 3523, 1);
  g->DequantizeTensor(3523, YNN_INVALID_VALUE_ID, 3524, 3525);
  g->QuantizeTensor(3525, 5190, 3527, 1118);
  g->Dequantize(1118, 1119, 0.08160637319087982, 0);
  g->Unary(ynn_unary_square, 1119, 1120);
  g->Reduce(ynn_reduce_sum, 1120, 4665, {2}, true);
  g->ShapeProduct(1120, 4664, {2});
  g->Binary(ynn_binary_divide, 4665, 4664, 1121);
  g->Binary(ynn_binary_add, 1121, 5241, 1122);
  g->Unary(ynn_unary_rsqrt, 1122, 1124);
  g->Binary(ynn_binary_multiply, 1119, 1124, 1125);
  g->Binary(ynn_binary_multiply, 1125, 5403, 1126);
  g->Binary(ynn_binary_add, 1098, 1126, 1127);
  g->Binary(ynn_binary_multiply, 1127, 5395, 1128);
}

// Scope: "Layer14"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14(Context& ctx) {
  BuildLayer14Attention(ctx);
  BuildLayer14Mlp(ctx);
  BuildLayer14PerLayerEmbedding(ctx);
}

// Scope: "Layer15 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(1135, 1136, 0.11677385866641998, 0);
  g->Transpose(5423, 3536, {1,0});
  g->Binary(ynn_binary_multiply, 3533, 3535, 3531);
  g->Dot(1136, 3536, YNN_INVALID_VALUE_ID, 3530, 1);
  g->DequantizeTensor(3530, YNN_INVALID_VALUE_ID, 3531, 3532);
  g->QuantizeTensor(3532, 5190, 3534, 1137);
  g->Dequantize(1137, 1138, 0.18897639214992523, 0);
  g->SplitDim(1138, 1139, 2, {2,256});
  g->Transpose(1139, 1140, {0,2,1,3});
  g->Unary(ynn_unary_square, 1140, 1141);
  g->Reduce(ynn_reduce_sum, 1141, 4669, {3}, true);
  g->ShapeProduct(1141, 4668, {3});
  g->Binary(ynn_binary_divide, 4669, 4668, 1142);
  g->Binary(ynn_binary_add, 1142, 5241, 1143);
  g->Unary(ynn_unary_rsqrt, 1143, 1144);
  g->Binary(ynn_binary_multiply, 1140, 1144, 1147);
  g->Binary(ynn_binary_multiply, 1147, 5422, 1148);
  g->Slice(1148, 1149, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1148, 1150, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1150, 1151);
  g->Concat({1151,1149}, 1152, 3);
  g->Binary(ynn_binary_multiply, 1148, 2394, 1153);
  g->Binary(ynn_binary_multiply, 1152, 2498, 1154);
  g->Binary(ynn_binary_add, 1153, 1154, 1155);
  g->Transpose(5427, 3541, {1,0});
  g->Binary(ynn_binary_multiply, 3533, 3540, 3538);
  g->Dot(1136, 3541, YNN_INVALID_VALUE_ID, 3537, 1);
  g->DequantizeTensor(3537, YNN_INVALID_VALUE_ID, 3538, 3539);
  g->QuantizeTensor(3539, 5190, 3534, 1157);
  g->Dequantize(1157, 1158, 0.18897639214992523, 0);
  g->SplitDim(1158, 1159, 2, {2,256});
  g->Transpose(1159, 1160, {0,2,1,3});
  g->Unary(ynn_unary_square, 1160, 1161);
  g->Reduce(ynn_reduce_sum, 1161, 4671, {3}, true);
  g->ShapeProduct(1161, 4670, {3});
  g->Binary(ynn_binary_divide, 4671, 4670, 1162);
  g->Binary(ynn_binary_add, 1162, 5241, 1163);
  g->Unary(ynn_unary_rsqrt, 1163, 1164);
  g->Binary(ynn_binary_multiply, 1160, 1164, 1165);
}

// Scope: "Layer15 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(1155, 1166, 0.005989333149045706, 0);
  g->Append(5198, 1166, 5720, 2, s2, s1);
  g->View(5720, 5768, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(1165, 1168, 0.047244105488061905, 0);
  g->Append(5222, 1168, 5744, 2, s2, s1);
  g->View(5744, 5791, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer15 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(5426, 3547, {1,0});
  g->Binary(ynn_binary_multiply, 3533, 3546, 3543);
  g->Dot(1136, 3547, YNN_INVALID_VALUE_ID, 3542, 1);
  g->DequantizeTensor(3542, YNN_INVALID_VALUE_ID, 3543, 3544);
  g->QuantizeTensor(3544, 5190, 3545, 1169);
  g->Dequantize(1169, 1170, 0.211614191532135, 0);
  g->SplitDim(1170, 1171, 2, {8,256});
  g->Transpose(1171, 1172, {0,2,1,3});
  g->Unary(ynn_unary_square, 1172, 1174);
  g->Reduce(ynn_reduce_sum, 1174, 4673, {3}, true);
  g->ShapeProduct(1174, 4672, {3});
  g->Binary(ynn_binary_divide, 4673, 4672, 1175);
  g->Binary(ynn_binary_add, 1175, 5241, 1176);
  g->Unary(ynn_unary_rsqrt, 1176, 1177);
  g->Binary(ynn_binary_multiply, 1172, 1177, 1178);
  g->Binary(ynn_binary_multiply, 1178, 5425, 1179);
  g->Slice(1179, 1180, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1179, 1181, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1181, 1182);
  g->Concat({1182,1180}, 1183, 3);
  g->Binary(ynn_binary_multiply, 1179, 2394, 1185);
  g->Binary(ynn_binary_multiply, 1183, 2498, 1186);
  g->Binary(ynn_binary_add, 1185, 1186, 1187);
}

// Scope: "Layer15 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(5768, 1188, 0.005989333149045706, 0);
  g->Dequantize(5791, 1189, 0.047244105488061905, 0);
  g->Slice(1187, 1190, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(1188, 1191, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(1189, 1192, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(1190, 1191, 1193, false, true);
  g->Mask(1193, 5258, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 5258, 4677, {-1}, true);
  g->Binary(ynn_binary_subtract, 5258, 4677, 4674);
  g->Unary(ynn_unary_exp, 4674, 4675);
  g->Reduce(ynn_reduce_sum, 4675, 4678, {-1}, true);
  g->Binary(ynn_binary_divide, 4364, 4678, 4676);
  g->Binary(ynn_binary_multiply, 4675, 4676, 1195);
  g->Matmul(1195, 1192, 1196, false, false);
  g->Slice(1187, 1197, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(1188, 1198, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(1189, 1199, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(1197, 1198, 1200, false, true);
  g->Mask(1200, 5259, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 5259, 4682, {-1}, true);
  g->Binary(ynn_binary_subtract, 5259, 4682, 4679);
  g->Unary(ynn_unary_exp, 4679, 4680);
  g->Reduce(ynn_reduce_sum, 4680, 4683, {-1}, true);
  g->Binary(ynn_binary_divide, 4364, 4683, 4681);
  g->Binary(ynn_binary_multiply, 4680, 4681, 1201);
  g->Matmul(1201, 1199, 1202, false, false);
  g->Concat({1196,1202}, 1203, 1);
}

// Scope: "Layer15 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1203, 1205, {0,2,1,3});
  g->FuseDims(1205, 1206, 2, 2);
  g->Quantize(1206, 1207, 0.02706693857908249, 0);
  g->Transpose(5424, 3554, {1,0});
  g->Binary(ynn_binary_multiply, 3551, 3553, 3549);
  g->Dot(1207, 3554, YNN_INVALID_VALUE_ID, 3548, 1);
  g->DequantizeTensor(3548, YNN_INVALID_VALUE_ID, 3549, 3550);
  g->QuantizeTensor(3550, 5190, 3552, 1208);
  g->Dequantize(1208, 1209, 0.06876781582832336, 0);
}

// Scope: "Layer15 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1128, 1129);
  g->Reduce(ynn_reduce_sum, 1129, 4667, {2}, true);
  g->ShapeProduct(1129, 4666, {2});
  g->Binary(ynn_binary_divide, 4667, 4666, 1130);
  g->Binary(ynn_binary_add, 1130, 5241, 1131);
  g->Unary(ynn_unary_rsqrt, 1131, 1132);
  g->Binary(ynn_binary_multiply, 1128, 1132, 1133);
  g->Binary(ynn_binary_multiply, 1133, 5411, 1135);
  BuildLayer15AttentionKvProjection(ctx);
  BuildLayer15AttentionCacheUpdate(ctx);
  BuildLayer15AttentionQueryProjection(ctx);
  BuildLayer15AttentionSdpa(ctx);
  BuildLayer15AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1209, 1210);
  g->Reduce(ynn_reduce_sum, 1210, 4685, {2}, true);
  g->ShapeProduct(1210, 4684, {2});
  g->Binary(ynn_binary_divide, 4685, 4684, 1211);
  g->Binary(ynn_binary_add, 1211, 5241, 1212);
  g->Unary(ynn_unary_rsqrt, 1212, 1213);
  g->Binary(ynn_binary_multiply, 1209, 1213, 1214);
  g->Binary(ynn_binary_multiply, 1214, 5418, 1215);
  g->Binary(ynn_binary_add, 1215, 1128, 1216);
}

// Scope: "Layer15 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1216, 1217);
  g->Reduce(ynn_reduce_sum, 1217, 4687, {2}, true);
  g->ShapeProduct(1217, 4686, {2});
  g->Binary(ynn_binary_divide, 4687, 4686, 1218);
  g->Binary(ynn_binary_add, 1218, 5241, 1219);
  g->Unary(ynn_unary_rsqrt, 1219, 1220);
  g->Binary(ynn_binary_multiply, 1216, 1220, 1221);
  g->Binary(ynn_binary_multiply, 1221, 5421, 1222);
  g->Quantize(1222, 1223, 0.01503660250455141, 0);
  g->Transpose(5415, 3561, {1,0});
  g->Binary(ynn_binary_multiply, 3558, 3560, 3556);
  g->Dot(1223, 3561, YNN_INVALID_VALUE_ID, 3555, 1);
  g->DequantizeTensor(3555, YNN_INVALID_VALUE_ID, 3556, 3557);
  g->QuantizeTensor(3557, 5190, 3559, 1224);
  g->Dequantize(1224, 1226, 0.020300205796957016, 0);
  g->Transpose(5414, 3566, {1,0});
  g->Binary(ynn_binary_multiply, 3558, 3565, 3563);
  g->Dot(1223, 3566, YNN_INVALID_VALUE_ID, 3562, 1);
  g->DequantizeTensor(3562, YNN_INVALID_VALUE_ID, 3563, 3564);
  g->QuantizeTensor(3564, 5190, 3559, 1227);
  g->Dequantize(1227, 1228, 0.020300205796957016, 0);
  g->Polynomial(1228, 4695, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 4695, 4696);
  g->Binary(ynn_binary_add, 4696, 4364, 4693);
  g->Binary(ynn_binary_multiply, 1228, 4376, 4694);
  g->Binary(ynn_binary_multiply, 4694, 4693, 1229);
  g->Binary(ynn_binary_multiply, 1226, 1229, 1230);
  g->Quantize(1230, 1231, 0.018700797110795975, 0);
  g->Transpose(5413, 3573, {1,0});
  g->Binary(ynn_binary_multiply, 3570, 3572, 3568);
  g->Dot(1231, 3573, YNN_INVALID_VALUE_ID, 3567, 1);
  g->DequantizeTensor(3567, YNN_INVALID_VALUE_ID, 3568, 3569);
  g->QuantizeTensor(3569, 5190, 3571, 1232);
  g->Dequantize(1232, 1233, 0.01157078705728054, 0);
  g->Unary(ynn_unary_square, 1233, 1234);
  g->Reduce(ynn_reduce_sum, 1234, 4698, {2}, true);
  g->ShapeProduct(1234, 4697, {2});
  g->Binary(ynn_binary_divide, 4698, 4697, 1236);
  g->Binary(ynn_binary_add, 1236, 5241, 1237);
  g->Unary(ynn_unary_rsqrt, 1237, 1238);
  g->Binary(ynn_binary_multiply, 1233, 1238, 1239);
  g->Binary(ynn_binary_multiply, 1239, 5419, 1240);
  g->Binary(ynn_binary_add, 1240, 1216, 1241);
}

// Scope: "Layer15 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 1242, {0,0,15,0}, {-1,-1,1,-1});
  g->Reshape(1242, 1243, {1,0,256});
  g->Unary(ynn_unary_square, 1243, 1244);
  g->Reduce(ynn_reduce_sum, 1244, 4700, {2}, true);
  g->ShapeProduct(1244, 4699, {2});
  g->Binary(ynn_binary_divide, 4700, 4699, 1245);
  g->Binary(ynn_binary_add, 1245, 5241, 1248);
  g->Unary(ynn_unary_rsqrt, 1248, 1249);
  g->Binary(ynn_binary_multiply, 1243, 1249, 1250);
  g->Binary(ynn_binary_multiply, 1250, 5688, 1251);
  g->Binary(ynn_binary_multiply, 5696, 5245, 1252);
  g->Binary(ynn_binary_add, 1251, 1252, 1253);
  g->Binary(ynn_binary_multiply, 1253, 5240, 1254);
  g->Quantize(1241, 1255, 0.40425750613212585, 0);
  g->Transpose(5416, 3587, {1,0});
  g->Binary(ynn_binary_multiply, 3584, 3586, 3582);
  g->Dot(1255, 3587, YNN_INVALID_VALUE_ID, 3581, 1);
  g->DequantizeTensor(3581, YNN_INVALID_VALUE_ID, 3582, 3583);
  g->QuantizeTensor(3583, 5190, 3585, 1256);
  g->Dequantize(1256, 1257, 0.10088583081960678, 0);
  g->Polynomial(1257, 4703, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 4703, 4704);
  g->Binary(ynn_binary_add, 4704, 4364, 4701);
  g->Binary(ynn_binary_multiply, 1257, 4376, 4702);
  g->Binary(ynn_binary_multiply, 4702, 4701, 1259);
  g->Binary(ynn_binary_multiply, 1259, 1254, 1260);
  g->Quantize(1260, 1261, 0.748031497001648, 0);
  g->Transpose(5417, 3594, {1,0});
  g->Binary(ynn_binary_multiply, 3591, 3593, 3589);
  g->Dot(1261, 3594, YNN_INVALID_VALUE_ID, 3588, 1);
  g->DequantizeTensor(3588, YNN_INVALID_VALUE_ID, 3589, 3590);
  g->QuantizeTensor(3590, 5190, 3592, 1262);
  g->Dequantize(1262, 1263, 0.20252664387226105, 0);
  g->Unary(ynn_unary_square, 1263, 1264);
  g->Reduce(ynn_reduce_sum, 1264, 4706, {2}, true);
  g->ShapeProduct(1264, 4705, {2});
  g->Binary(ynn_binary_divide, 4706, 4705, 1265);
  g->Binary(ynn_binary_add, 1265, 5241, 1266);
  g->Unary(ynn_unary_rsqrt, 1266, 1267);
  g->Binary(ynn_binary_multiply, 1263, 1267, 1268);
  g->Binary(ynn_binary_multiply, 1268, 5420, 1270);
  g->Binary(ynn_binary_add, 1241, 1270, 1271);
  g->Binary(ynn_binary_multiply, 1271, 5412, 1272);
}

// Scope: "Layer15"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15(Context& ctx) {
  BuildLayer15Attention(ctx);
  BuildLayer15Mlp(ctx);
  BuildLayer15PerLayerEmbedding(ctx);
}

// Scope: "Layer16 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(1278, 1279, 0.14304621517658234, 0);
  g->Transpose(5440, 3601, {1,0});
  g->Binary(ynn_binary_multiply, 3598, 3600, 3596);
  g->Dot(1279, 3601, YNN_INVALID_VALUE_ID, 3595, 1);
  g->DequantizeTensor(3595, YNN_INVALID_VALUE_ID, 3596, 3597);
  g->QuantizeTensor(3597, 5190, 3599, 1281);
  g->Dequantize(1281, 1282, 0.16535434126853943, 0);
  g->SplitDim(1282, 1283, 2, {2,256});
  g->Transpose(1283, 1284, {0,2,1,3});
  g->Unary(ynn_unary_square, 1284, 1285);
  g->Reduce(ynn_reduce_sum, 1285, 4710, {3}, true);
  g->ShapeProduct(1285, 4709, {3});
  g->Binary(ynn_binary_divide, 4710, 4709, 1286);
  g->Binary(ynn_binary_add, 1286, 5241, 1287);
  g->Unary(ynn_unary_rsqrt, 1287, 1288);
  g->Binary(ynn_binary_multiply, 1284, 1288, 1289);
  g->Binary(ynn_binary_multiply, 1289, 5439, 1290);
  g->Slice(1290, 1291, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1290, 1292, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1292, 1293);
  g->Concat({1293,1291}, 1294, 3);
  g->Binary(ynn_binary_multiply, 1290, 2394, 1295);
  g->Binary(ynn_binary_multiply, 1294, 2498, 1296);
  g->Binary(ynn_binary_add, 1295, 1296, 1297);
  g->Transpose(5444, 3606, {1,0});
  g->Binary(ynn_binary_multiply, 3598, 3605, 3603);
  g->Dot(1279, 3606, YNN_INVALID_VALUE_ID, 3602, 1);
  g->DequantizeTensor(3602, YNN_INVALID_VALUE_ID, 3603, 3604);
  g->QuantizeTensor(3604, 5190, 3599, 1298);
  g->Dequantize(1298, 1299, 0.16535434126853943, 0);
  g->SplitDim(1299, 1301, 2, {2,256});
  g->Transpose(1301, 1302, {0,2,1,3});
  g->Unary(ynn_unary_square, 1302, 1303);
  g->Reduce(ynn_reduce_sum, 1303, 4717, {3}, true);
  g->ShapeProduct(1303, 4716, {3});
  g->Binary(ynn_binary_divide, 4717, 4716, 1304);
  g->Binary(ynn_binary_add, 1304, 5241, 1305);
  g->Unary(ynn_unary_rsqrt, 1305, 1306);
  g->Binary(ynn_binary_multiply, 1302, 1306, 1307);
}

// Scope: "Layer16 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(1297, 1308, 0.005929071456193924, 0);
  g->Append(5199, 1308, 5721, 2, s2, s1);
  g->View(5721, 5769, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(1307, 1310, 0.047244105488061905, 0);
  g->Append(5223, 1310, 5745, 2, s2, s1);
  g->View(5745, 5792, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer16 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(5443, 3612, {1,0});
  g->Binary(ynn_binary_multiply, 3598, 3611, 3608);
  g->Dot(1279, 3612, YNN_INVALID_VALUE_ID, 3607, 1);
  g->DequantizeTensor(3607, YNN_INVALID_VALUE_ID, 3608, 3609);
  g->QuantizeTensor(3609, 5190, 3610, 1311);
  g->Dequantize(1311, 1312, 0.1761811226606369, 0);
  g->SplitDim(1312, 1313, 2, {8,256});
  g->Transpose(1313, 1314, {0,2,1,3});
  g->Unary(ynn_unary_square, 1314, 1315);
  g->Reduce(ynn_reduce_sum, 1315, 4719, {3}, true);
  g->ShapeProduct(1315, 4718, {3});
  g->Binary(ynn_binary_divide, 4719, 4718, 1316);
  g->Binary(ynn_binary_add, 1316, 5241, 1318);
  g->Unary(ynn_unary_rsqrt, 1318, 1319);
  g->Binary(ynn_binary_multiply, 1314, 1319, 1320);
  g->Binary(ynn_binary_multiply, 1320, 5442, 1321);
  g->Slice(1321, 1322, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1321, 1323, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1323, 1324);
  g->Concat({1324,1322}, 1325, 3);
  g->Binary(ynn_binary_multiply, 1321, 2394, 1326);
  g->Binary(ynn_binary_multiply, 1325, 2498, 1327);
  g->Binary(ynn_binary_add, 1326, 1327, 1329);
}

// Scope: "Layer16 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(5769, 1330, 0.005929071456193924, 0);
  g->Dequantize(5792, 1331, 0.047244105488061905, 0);
  g->Slice(1329, 1332, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(1330, 1333, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(1331, 1334, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(1332, 1333, 1335, false, true);
  g->Mask(1335, 5260, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 5260, 4723, {-1}, true);
  g->Binary(ynn_binary_subtract, 5260, 4723, 4720);
  g->Unary(ynn_unary_exp, 4720, 4721);
  g->Reduce(ynn_reduce_sum, 4721, 4724, {-1}, true);
  g->Binary(ynn_binary_divide, 4364, 4724, 4722);
  g->Binary(ynn_binary_multiply, 4721, 4722, 1336);
  g->Matmul(1336, 1334, 1337, false, false);
  g->Slice(1329, 1339, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(1330, 1340, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(1331, 1341, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(1339, 1340, 1342, false, true);
  g->Mask(1342, 5261, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 5261, 4728, {-1}, true);
  g->Binary(ynn_binary_subtract, 5261, 4728, 4725);
  g->Unary(ynn_unary_exp, 4725, 4726);
  g->Reduce(ynn_reduce_sum, 4726, 4729, {-1}, true);
  g->Binary(ynn_binary_divide, 4364, 4729, 4727);
  g->Binary(ynn_binary_multiply, 4726, 4727, 1343);
  g->Matmul(1343, 1341, 1344, false, false);
  g->Concat({1337,1344}, 1345, 1);
}

// Scope: "Layer16 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1345, 1346, {0,2,1,3});
  g->FuseDims(1346, 1347, 2, 2);
  g->Quantize(1347, 1350, 0.025221465155482292, 0);
  g->Transpose(5441, 3619, {1,0});
  g->Binary(ynn_binary_multiply, 3616, 3618, 3614);
  g->Dot(1350, 3619, YNN_INVALID_VALUE_ID, 3613, 1);
  g->DequantizeTensor(3613, YNN_INVALID_VALUE_ID, 3614, 3615);
  g->QuantizeTensor(3615, 5190, 3617, 1351);
  g->Dequantize(1351, 1352, 0.03670656308531761, 0);
}

// Scope: "Layer16 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1272, 1273);
  g->Reduce(ynn_reduce_sum, 1273, 4708, {2}, true);
  g->ShapeProduct(1273, 4707, {2});
  g->Binary(ynn_binary_divide, 4708, 4707, 1274);
  g->Binary(ynn_binary_add, 1274, 5241, 1275);
  g->Unary(ynn_unary_rsqrt, 1275, 1276);
  g->Binary(ynn_binary_multiply, 1272, 1276, 1277);
  g->Binary(ynn_binary_multiply, 1277, 5428, 1278);
  BuildLayer16AttentionKvProjection(ctx);
  BuildLayer16AttentionCacheUpdate(ctx);
  BuildLayer16AttentionQueryProjection(ctx);
  BuildLayer16AttentionSdpa(ctx);
  BuildLayer16AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1352, 1353);
  g->Reduce(ynn_reduce_sum, 1353, 4731, {2}, true);
  g->ShapeProduct(1353, 4730, {2});
  g->Binary(ynn_binary_divide, 4731, 4730, 1354);
  g->Binary(ynn_binary_add, 1354, 5241, 1355);
  g->Unary(ynn_unary_rsqrt, 1355, 1356);
  g->Binary(ynn_binary_multiply, 1352, 1356, 1357);
  g->Binary(ynn_binary_multiply, 1357, 5435, 1358);
  g->Binary(ynn_binary_add, 1358, 1272, 1359);
}

// Scope: "Layer16 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1359, 1361);
  g->Reduce(ynn_reduce_sum, 1361, 4733, {2}, true);
  g->ShapeProduct(1361, 4732, {2});
  g->Binary(ynn_binary_divide, 4733, 4732, 1362);
  g->Binary(ynn_binary_add, 1362, 5241, 1363);
  g->Unary(ynn_unary_rsqrt, 1363, 1364);
  g->Binary(ynn_binary_multiply, 1359, 1364, 1365);
  g->Binary(ynn_binary_multiply, 1365, 5438, 1366);
  g->Quantize(1366, 1367, 0.013054176233708858, 0);
  g->Transpose(5432, 3633, {1,0});
  g->Binary(ynn_binary_multiply, 3630, 3632, 3628);
  g->Dot(1367, 3633, YNN_INVALID_VALUE_ID, 3627, 1);
  g->DequantizeTensor(3627, YNN_INVALID_VALUE_ID, 3628, 3629);
  g->QuantizeTensor(3629, 5190, 3631, 1368);
  g->Dequantize(1368, 1369, 0.01464075781404972, 0);
  g->Transpose(5431, 3638, {1,0});
  g->Binary(ynn_binary_multiply, 3630, 3637, 3635);
  g->Dot(1367, 3638, YNN_INVALID_VALUE_ID, 3634, 1);
  g->DequantizeTensor(3634, YNN_INVALID_VALUE_ID, 3635, 3636);
  g->QuantizeTensor(3636, 5190, 3631, 1371);
  g->Dequantize(1371, 1372, 0.01464075781404972, 0);
  g->Polynomial(1372, 4736, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 4736, 4737);
  g->Binary(ynn_binary_add, 4737, 4364, 4734);
  g->Binary(ynn_binary_multiply, 1372, 4376, 4735);
  g->Binary(ynn_binary_multiply, 4735, 4734, 1373);
  g->Binary(ynn_binary_multiply, 1369, 1373, 1374);
  g->Quantize(1374, 1375, 0.010150108486413956, 0);
  g->Transpose(5430, 3645, {1,0});
  g->Binary(ynn_binary_multiply, 3642, 3644, 3640);
  g->Dot(1375, 3645, YNN_INVALID_VALUE_ID, 3639, 1);
  g->DequantizeTensor(3639, YNN_INVALID_VALUE_ID, 3640, 3641);
  g->QuantizeTensor(3641, 5190, 3643, 1376);
  g->Dequantize(1376, 1377, 0.006600875407457352, 0);
  g->Unary(ynn_unary_square, 1377, 1378);
  g->Reduce(ynn_reduce_sum, 1378, 4739, {2}, true);
  g->ShapeProduct(1378, 4738, {2});
  g->Binary(ynn_binary_divide, 4739, 4738, 1379);
  g->Binary(ynn_binary_add, 1379, 5241, 1380);
  g->Unary(ynn_unary_rsqrt, 1380, 1382);
  g->Binary(ynn_binary_multiply, 1377, 1382, 1383);
  g->Binary(ynn_binary_multiply, 1383, 5436, 1384);
  g->Binary(ynn_binary_add, 1384, 1359, 1385);
}

// Scope: "Layer16 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 1386, {0,0,16,0}, {-1,-1,1,-1});
  g->Reshape(1386, 1387, {1,0,256});
  g->Unary(ynn_unary_square, 1387, 1388);
  g->Reduce(ynn_reduce_sum, 1388, 4741, {2}, true);
  g->ShapeProduct(1388, 4740, {2});
  g->Binary(ynn_binary_divide, 4741, 4740, 1389);
  g->Binary(ynn_binary_add, 1389, 5241, 1390);
  g->Unary(ynn_unary_rsqrt, 1390, 1391);
  g->Binary(ynn_binary_multiply, 1387, 1391, 1393);
  g->Binary(ynn_binary_multiply, 1393, 5688, 1394);
  g->Binary(ynn_binary_multiply, 5697, 5245, 1395);
  g->Binary(ynn_binary_add, 1394, 1395, 1396);
  g->Binary(ynn_binary_multiply, 1396, 5240, 1397);
  g->Quantize(1385, 1398, 0.3792611062526703, 0);
  g->Transpose(5433, 3652, {1,0});
  g->Binary(ynn_binary_multiply, 3649, 3651, 3647);
  g->Dot(1398, 3652, YNN_INVALID_VALUE_ID, 3646, 1);
  g->DequantizeTensor(3646, YNN_INVALID_VALUE_ID, 3647, 3648);
  g->QuantizeTensor(3648, 5190, 3650, 1399);
  g->Dequantize(1399, 1400, 0.10433071851730347, 0);
  g->Polynomial(1400, 4746, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 4746, 4747);
  g->Binary(ynn_binary_add, 4747, 4364, 4744);
  g->Binary(ynn_binary_multiply, 1400, 4376, 4745);
  g->Binary(ynn_binary_multiply, 4745, 4744, 1401);
  g->Binary(ynn_binary_multiply, 1401, 1397, 1402);
  g->Quantize(1402, 1404, 0.43897637724876404, 0);
  g->Transpose(5434, 3659, {1,0});
  g->Binary(ynn_binary_multiply, 3656, 3658, 3654);
  g->Dot(1404, 3659, YNN_INVALID_VALUE_ID, 3653, 1);
  g->DequantizeTensor(3653, YNN_INVALID_VALUE_ID, 3654, 3655);
  g->QuantizeTensor(3655, 5190, 3657, 1405);
  g->Dequantize(1405, 1406, 0.08895451575517654, 0);
  g->Unary(ynn_unary_square, 1406, 1407);
  g->Reduce(ynn_reduce_sum, 1407, 4749, {2}, true);
  g->ShapeProduct(1407, 4748, {2});
  g->Binary(ynn_binary_divide, 4749, 4748, 1408);
  g->Binary(ynn_binary_add, 1408, 5241, 1409);
  g->Unary(ynn_unary_rsqrt, 1409, 1410);
  g->Binary(ynn_binary_multiply, 1406, 1410, 1411);
  g->Binary(ynn_binary_multiply, 1411, 5437, 1412);
  g->Binary(ynn_binary_add, 1385, 1412, 1413);
  g->Binary(ynn_binary_multiply, 1413, 5429, 1415);
}

// Scope: "Layer16"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16(Context& ctx) {
  BuildLayer16Attention(ctx);
  BuildLayer16Mlp(ctx);
  BuildLayer16PerLayerEmbedding(ctx);
}

// Scope: "Layer17 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(1421, 1422, 0.11633685231208801, 0);
  g->Transpose(5457, 3666, {1,0});
  g->Binary(ynn_binary_multiply, 3663, 3665, 3661);
  g->Dot(1422, 3666, YNN_INVALID_VALUE_ID, 3660, 1);
  g->DequantizeTensor(3660, YNN_INVALID_VALUE_ID, 3661, 3662);
  g->QuantizeTensor(3662, 5190, 3664, 1423);
  g->Dequantize(1423, 1424, 0.1210630014538765, 0);
  g->SplitDim(1424, 1426, 2, {2,512});
  g->Transpose(1426, 1427, {0,2,1,3});
  g->Unary(ynn_unary_square, 1427, 1428);
  g->Reduce(ynn_reduce_sum, 1428, 4753, {3}, true);
  g->ShapeProduct(1428, 4752, {3});
  g->Binary(ynn_binary_divide, 4753, 4752, 1429);
  g->Binary(ynn_binary_add, 1429, 5241, 1430);
  g->Unary(ynn_unary_rsqrt, 1430, 1431);
  g->Binary(ynn_binary_multiply, 1427, 1431, 1432);
  g->Binary(ynn_binary_multiply, 1432, 5456, 1433);
  g->Slice(1433, 1434, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(1433, 1435, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 1435, 1437);
  g->Concat({1437,1434}, 1438, 3);
  g->Binary(ynn_binary_multiply, 1433, 2909, 1439);
  g->Binary(ynn_binary_multiply, 1438, 2, 1440);
  g->Binary(ynn_binary_add, 1439, 1440, 1441);
  g->Transpose(5461, 3671, {1,0});
  g->Binary(ynn_binary_multiply, 3663, 3670, 3668);
  g->Dot(1422, 3671, YNN_INVALID_VALUE_ID, 3667, 1);
  g->DequantizeTensor(3667, YNN_INVALID_VALUE_ID, 3668, 3669);
  g->QuantizeTensor(3669, 5190, 3664, 1442);
  g->Dequantize(1442, 1443, 0.1210630014538765, 0);
  g->SplitDim(1443, 1444, 2, {2,512});
  g->Transpose(1444, 1445, {0,2,1,3});
  g->Unary(ynn_unary_square, 1445, 1447);
  g->Reduce(ynn_reduce_sum, 1447, 4755, {3}, true);
  g->ShapeProduct(1447, 4754, {3});
  g->Binary(ynn_binary_divide, 4755, 4754, 1448);
  g->Binary(ynn_binary_add, 1448, 5241, 1449);
  g->Unary(ynn_unary_rsqrt, 1449, 1450);
  g->Binary(ynn_binary_multiply, 1445, 1450, 1451);
}

// Scope: "Layer17 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(1441, 1452, 0.001110153621993959, 0);
  g->Append(5200, 1452, 5722, 2, s2, s1);
  g->View(5722, 5770, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(1451, 1453, 0.01785714365541935, 0);
  g->Append(5224, 1453, 5746, 2, s2, s1);
  g->View(5746, 5793, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer17 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(5460, 3677, {1,0});
  g->Binary(ynn_binary_multiply, 3663, 3676, 3673);
  g->Dot(1422, 3677, YNN_INVALID_VALUE_ID, 3672, 1);
  g->DequantizeTensor(3672, YNN_INVALID_VALUE_ID, 3673, 3674);
  g->QuantizeTensor(3674, 5190, 3675, 1456);
  g->Dequantize(1456, 1457, 0.17027559876441956, 0);
  g->SplitDim(1457, 1458, 2, {8,512});
  g->Transpose(1458, 1459, {0,2,1,3});
  g->Unary(ynn_unary_square, 1459, 1460);
  g->Reduce(ynn_reduce_sum, 1460, 4757, {3}, true);
  g->ShapeProduct(1460, 4756, {3});
  g->Binary(ynn_binary_divide, 4757, 4756, 1461);
  g->Binary(ynn_binary_add, 1461, 5241, 1462);
  g->Unary(ynn_unary_rsqrt, 1462, 1463);
  g->Binary(ynn_binary_multiply, 1459, 1463, 1465);
  g->Binary(ynn_binary_multiply, 1465, 5459, 1466);
  g->Slice(1466, 1467, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(1466, 1468, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 1468, 1469);
  g->Concat({1469,1467}, 1470, 3);
  g->Binary(ynn_binary_multiply, 1466, 2909, 1471);
  g->Binary(ynn_binary_multiply, 1470, 2, 1472);
  g->Binary(ynn_binary_add, 1471, 1472, 1473);
}

// Scope: "Layer17 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(5770, 1474, 0.001110153621993959, 0);
  g->Dequantize(5793, 1476, 0.01785714365541935, 0);
  g->Slice(1473, 1477, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(1474, 1478, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(1476, 1479, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(1477, 1478, 1480, false, true);
  g->Mask(1480, 5262, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 5262, 4763, {-1}, true);
  g->Binary(ynn_binary_subtract, 5262, 4763, 4760);
  g->Unary(ynn_unary_exp, 4760, 4761);
  g->Reduce(ynn_reduce_sum, 4761, 4764, {-1}, true);
  g->Binary(ynn_binary_divide, 4364, 4764, 4762);
  g->Binary(ynn_binary_multiply, 4761, 4762, 1481);
  g->Matmul(1481, 1479, 1482, false, false);
  g->Slice(1473, 1483, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(1474, 1484, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(1476, 1486, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(1483, 1484, 1487, false, true);
  g->Mask(1487, 5263, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 5263, 4768, {-1}, true);
  g->Binary(ynn_binary_subtract, 5263, 4768, 4765);
  g->Unary(ynn_unary_exp, 4765, 4766);
  g->Reduce(ynn_reduce_sum, 4766, 4769, {-1}, true);
  g->Binary(ynn_binary_divide, 4364, 4769, 4767);
  g->Binary(ynn_binary_multiply, 4766, 4767, 1488);
  g->Matmul(1488, 1486, 1489, false, false);
  g->Concat({1482,1489}, 1490, 1);
}

// Scope: "Layer17 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1490, 1491, {0,2,1,3});
  g->FuseDims(1491, 1492, 2, 2);
  g->Quantize(1492, 1493, 0.01771654561161995, 0);
  g->Transpose(5458, 3684, {1,0});
  g->Binary(ynn_binary_multiply, 3681, 3683, 3679);
  g->Dot(1493, 3684, YNN_INVALID_VALUE_ID, 3678, 1);
  g->DequantizeTensor(3678, YNN_INVALID_VALUE_ID, 3679, 3680);
  g->QuantizeTensor(3680, 5190, 3682, 1494);
  g->Dequantize(1494, 1496, 0.025433415547013283, 0);
}

// Scope: "Layer17 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1415, 1416);
  g->Reduce(ynn_reduce_sum, 1416, 4751, {2}, true);
  g->ShapeProduct(1416, 4750, {2});
  g->Binary(ynn_binary_divide, 4751, 4750, 1417);
  g->Binary(ynn_binary_add, 1417, 5241, 1418);
  g->Unary(ynn_unary_rsqrt, 1418, 1419);
  g->Binary(ynn_binary_multiply, 1415, 1419, 1420);
  g->Binary(ynn_binary_multiply, 1420, 5445, 1421);
  BuildLayer17AttentionKvProjection(ctx);
  BuildLayer17AttentionCacheUpdate(ctx);
  BuildLayer17AttentionQueryProjection(ctx);
  BuildLayer17AttentionSdpa(ctx);
  BuildLayer17AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1496, 1497);
  g->Reduce(ynn_reduce_sum, 1497, 4771, {2}, true);
  g->ShapeProduct(1497, 4770, {2});
  g->Binary(ynn_binary_divide, 4771, 4770, 1498);
  g->Binary(ynn_binary_add, 1498, 5241, 1499);
  g->Unary(ynn_unary_rsqrt, 1499, 1500);
  g->Binary(ynn_binary_multiply, 1496, 1500, 1501);
  g->Binary(ynn_binary_multiply, 1501, 5452, 1502);
  g->Binary(ynn_binary_add, 1502, 1415, 1503);
}

// Scope: "Layer17 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1503, 1504);
  g->Reduce(ynn_reduce_sum, 1504, 4773, {2}, true);
  g->ShapeProduct(1504, 4772, {2});
  g->Binary(ynn_binary_divide, 4773, 4772, 1505);
  g->Binary(ynn_binary_add, 1505, 5241, 1507);
  g->Unary(ynn_unary_rsqrt, 1507, 1508);
  g->Binary(ynn_binary_multiply, 1503, 1508, 1509);
  g->Binary(ynn_binary_multiply, 1509, 5455, 1510);
  g->Quantize(1510, 1511, 0.010834499262273312, 0);
  g->Transpose(5449, 3691, {1,0});
  g->Binary(ynn_binary_multiply, 3688, 3690, 3686);
  g->Dot(1511, 3691, YNN_INVALID_VALUE_ID, 3685, 1);
  g->DequantizeTensor(3685, YNN_INVALID_VALUE_ID, 3686, 3687);
  g->QuantizeTensor(3687, 5190, 3689, 1512);
  g->Dequantize(1512, 1513, 0.012979833409190178, 0);
  g->Transpose(5448, 3696, {1,0});
  g->Binary(ynn_binary_multiply, 3688, 3695, 3693);
  g->Dot(1511, 3696, YNN_INVALID_VALUE_ID, 3692, 1);
  g->DequantizeTensor(3692, YNN_INVALID_VALUE_ID, 3693, 3694);
  g->QuantizeTensor(3694, 5190, 3689, 1514);
  g->Dequantize(1514, 1515, 0.012979833409190178, 0);
  g->Polynomial(1515, 4776, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 4776, 4777);
  g->Binary(ynn_binary_add, 4777, 4364, 4774);
  g->Binary(ynn_binary_multiply, 1515, 4376, 4775);
  g->Binary(ynn_binary_multiply, 4775, 4774, 1517);
  g->Binary(ynn_binary_multiply, 1513, 1517, 1518);
  g->Quantize(1518, 1519, 0.005751732271164656, 0);
  g->Transpose(5447, 3703, {1,0});
  g->Binary(ynn_binary_multiply, 3700, 3702, 3698);
  g->Dot(1519, 3703, YNN_INVALID_VALUE_ID, 3697, 1);
  g->DequantizeTensor(3697, YNN_INVALID_VALUE_ID, 3698, 3699);
  g->QuantizeTensor(3699, 5190, 3701, 1520);
  g->Dequantize(1520, 1521, 0.0032109280582517385, 0);
  g->Unary(ynn_unary_square, 1521, 1522);
  g->Reduce(ynn_reduce_sum, 1522, 4779, {2}, true);
  g->ShapeProduct(1522, 4778, {2});
  g->Binary(ynn_binary_divide, 4779, 4778, 1523);
  g->Binary(ynn_binary_add, 1523, 5241, 1524);
  g->Unary(ynn_unary_rsqrt, 1524, 1525);
  g->Binary(ynn_binary_multiply, 1521, 1525, 1526);
  g->Binary(ynn_binary_multiply, 1526, 5453, 1528);
  g->Binary(ynn_binary_add, 1528, 1503, 1529);
}

// Scope: "Layer17 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 1530, {0,0,17,0}, {-1,-1,1,-1});
  g->Reshape(1530, 1531, {1,0,256});
  g->Unary(ynn_unary_square, 1531, 1532);
  g->Reduce(ynn_reduce_sum, 1532, 4781, {2}, true);
  g->ShapeProduct(1532, 4780, {2});
  g->Binary(ynn_binary_divide, 4781, 4780, 1533);
  g->Binary(ynn_binary_add, 1533, 5241, 1534);
  g->Unary(ynn_unary_rsqrt, 1534, 1535);
  g->Binary(ynn_binary_multiply, 1531, 1535, 1536);
  g->Binary(ynn_binary_multiply, 1536, 5688, 1537);
  g->Binary(ynn_binary_multiply, 5698, 5245, 1539);
  g->Binary(ynn_binary_add, 1537, 1539, 1540);
  g->Binary(ynn_binary_multiply, 1540, 5240, 1541);
  g->Quantize(1529, 1542, 0.23138143122196198, 0);
  g->Transpose(5450, 3717, {1,0});
  g->Binary(ynn_binary_multiply, 3714, 3716, 3712);
  g->Dot(1542, 3717, YNN_INVALID_VALUE_ID, 3711, 1);
  g->DequantizeTensor(3711, YNN_INVALID_VALUE_ID, 3712, 3713);
  g->QuantizeTensor(3713, 5190, 3715, 1543);
  g->Dequantize(1543, 1544, 0.08070866763591766, 0);
  g->Polynomial(1544, 4784, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 4784, 4785);
  g->Binary(ynn_binary_add, 4785, 4364, 4782);
  g->Binary(ynn_binary_multiply, 1544, 4376, 4783);
  g->Binary(ynn_binary_multiply, 4783, 4782, 1545);
  g->Binary(ynn_binary_multiply, 1545, 1541, 1546);
  g->Quantize(1546, 1547, 0.4606299102306366, 0);
  g->Transpose(5451, 3724, {1,0});
  g->Binary(ynn_binary_multiply, 3721, 3723, 3719);
  g->Dot(1547, 3724, YNN_INVALID_VALUE_ID, 3718, 1);
  g->DequantizeTensor(3718, YNN_INVALID_VALUE_ID, 3719, 3720);
  g->QuantizeTensor(3720, 5190, 3722, 1548);
  g->Dequantize(1548, 1549, 0.13702630996704102, 0);
  g->Unary(ynn_unary_square, 1549, 1550);
  g->Reduce(ynn_reduce_sum, 1550, 4787, {2}, true);
  g->ShapeProduct(1550, 4786, {2});
  g->Binary(ynn_binary_divide, 4787, 4786, 1551);
  g->Binary(ynn_binary_add, 1551, 5241, 1552);
  g->Unary(ynn_unary_rsqrt, 1552, 1553);
  g->Binary(ynn_binary_multiply, 1549, 1553, 1554);
  g->Binary(ynn_binary_multiply, 1554, 5454, 1555);
  g->Binary(ynn_binary_add, 1529, 1555, 1556);
  g->Binary(ynn_binary_multiply, 1556, 5446, 1557);
}

// Scope: "Layer17"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17(Context& ctx) {
  BuildLayer17Attention(ctx);
  BuildLayer17Mlp(ctx);
  BuildLayer17PerLayerEmbedding(ctx);
}

// Scope: "Layer18 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(1565, 1566, 0.21988293528556824, 0);
  g->Transpose(5474, 3735, {1,0});
  g->Binary(ynn_binary_multiply, 3733, 3734, 3731);
  g->Dot(1566, 3735, YNN_INVALID_VALUE_ID, 3730, 1);
  g->DequantizeTensor(3730, YNN_INVALID_VALUE_ID, 3731, 3732);
  g->QuantizeTensor(3732, 5190, 3351, 1567);
  g->Dequantize(1567, 1568, 0.2027559131383896, 0);
  g->SplitDim(1568, 1569, 2, {2,256});
  g->Transpose(1569, 1570, {0,2,1,3});
  g->Unary(ynn_unary_square, 1570, 1572);
  g->Reduce(ynn_reduce_sum, 1572, 4791, {3}, true);
  g->ShapeProduct(1572, 4790, {3});
  g->Binary(ynn_binary_divide, 4791, 4790, 1573);
  g->Binary(ynn_binary_add, 1573, 5241, 1574);
  g->Unary(ynn_unary_rsqrt, 1574, 1575);
  g->Binary(ynn_binary_multiply, 1570, 1575, 1576);
  g->Binary(ynn_binary_multiply, 1576, 5473, 1577);
  g->Slice(1577, 1578, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1577, 1579, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1579, 1580);
  g->Concat({1580,1578}, 1581, 3);
  g->Binary(ynn_binary_multiply, 1577, 2394, 1583);
  g->Binary(ynn_binary_multiply, 1581, 2498, 1584);
  g->Binary(ynn_binary_add, 1583, 1584, 1585);
  g->Transpose(5478, 3740, {1,0});
  g->Binary(ynn_binary_multiply, 3733, 3739, 3737);
  g->Dot(1566, 3740, YNN_INVALID_VALUE_ID, 3736, 1);
  g->DequantizeTensor(3736, YNN_INVALID_VALUE_ID, 3737, 3738);
  g->QuantizeTensor(3738, 5190, 3351, 1586);
  g->Dequantize(1586, 1587, 0.2027559131383896, 0);
  g->SplitDim(1587, 1588, 2, {2,256});
  g->Transpose(1588, 1589, {0,2,1,3});
  g->Unary(ynn_unary_square, 1589, 1590);
  g->Reduce(ynn_reduce_sum, 1590, 4797, {3}, true);
  g->ShapeProduct(1590, 4796, {3});
  g->Binary(ynn_binary_divide, 4797, 4796, 1591);
  g->Binary(ynn_binary_add, 1591, 5241, 1593);
  g->Unary(ynn_unary_rsqrt, 1593, 1594);
  g->Binary(ynn_binary_multiply, 1589, 1594, 1595);
}

// Scope: "Layer18 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(1585, 1596, 0.00573749840259552, 0);
  g->Append(5201, 1596, 5723, 2, s2, s1);
  g->View(5723, 5771, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(1595, 1597, 0.047244105488061905, 0);
  g->Append(5225, 1597, 5747, 2, s2, s1);
  g->View(5747, 5794, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer18 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(5477, 3746, {1,0});
  g->Binary(ynn_binary_multiply, 3733, 3745, 3742);
  g->Dot(1566, 3746, YNN_INVALID_VALUE_ID, 3741, 1);
  g->DequantizeTensor(3741, YNN_INVALID_VALUE_ID, 3742, 3743);
  g->QuantizeTensor(3743, 5190, 3744, 1599);
  g->Dequantize(1599, 1600, 0.22539371252059937, 0);
  g->SplitDim(1600, 1601, 2, {8,256});
  g->Transpose(1601, 1602, {0,2,1,3});
  g->Unary(ynn_unary_square, 1602, 1603);
  g->Reduce(ynn_reduce_sum, 1603, 4799, {3}, true);
  g->ShapeProduct(1603, 4798, {3});
  g->Binary(ynn_binary_divide, 4799, 4798, 1604);
  g->Binary(ynn_binary_add, 1604, 5241, 1605);
  g->Unary(ynn_unary_rsqrt, 1605, 1606);
  g->Binary(ynn_binary_multiply, 1602, 1606, 1607);
  g->Binary(ynn_binary_multiply, 1607, 5476, 1608);
  g->Slice(1608, 1610, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1608, 1611, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1611, 1612);
  g->Concat({1612,1610}, 1613, 3);
  g->Binary(ynn_binary_multiply, 1608, 2394, 1614);
  g->Binary(ynn_binary_multiply, 1613, 2498, 1615);
  g->Binary(ynn_binary_add, 1614, 1615, 1616);
}

// Scope: "Layer18 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(5771, 1617, 0.00573749840259552, 0);
  g->Dequantize(5794, 1618, 0.047244105488061905, 0);
  g->Slice(1616, 1619, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(1617, 1621, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(1618, 1622, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(1619, 1621, 1623, false, true);
  g->Mask(1623, 5264, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 5264, 4803, {-1}, true);
  g->Binary(ynn_binary_subtract, 5264, 4803, 4800);
  g->Unary(ynn_unary_exp, 4800, 4801);
  g->Reduce(ynn_reduce_sum, 4801, 4804, {-1}, true);
  g->Binary(ynn_binary_divide, 4364, 4804, 4802);
  g->Binary(ynn_binary_multiply, 4801, 4802, 1624);
  g->Matmul(1624, 1622, 1625, false, false);
  g->Slice(1616, 1626, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(1617, 1627, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(1618, 1628, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(1626, 1627, 1629, false, true);
  g->Mask(1629, 5265, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 5265, 4808, {-1}, true);
  g->Binary(ynn_binary_subtract, 5265, 4808, 4805);
  g->Unary(ynn_unary_exp, 4805, 4806);
  g->Reduce(ynn_reduce_sum, 4806, 4809, {-1}, true);
  g->Binary(ynn_binary_divide, 4364, 4809, 4807);
  g->Binary(ynn_binary_multiply, 4806, 4807, 1631);
  g->Matmul(1631, 1628, 1632, false, false);
  g->Concat({1625,1632}, 1633, 1);
}

// Scope: "Layer18 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1633, 1634, {0,2,1,3});
  g->FuseDims(1634, 1635, 2, 2);
  g->Quantize(1635, 1636, 0.023868119344115257, 0);
  g->Transpose(5475, 3760, {1,0});
  g->Binary(ynn_binary_multiply, 3757, 3759, 3755);
  g->Dot(1636, 3760, YNN_INVALID_VALUE_ID, 3754, 1);
  g->DequantizeTensor(3754, YNN_INVALID_VALUE_ID, 3755, 3756);
  g->QuantizeTensor(3756, 5190, 3758, 1637);
  g->Dequantize(1637, 1638, 0.027112234383821487, 0);
}

// Scope: "Layer18 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1557, 1558);
  g->Reduce(ynn_reduce_sum, 1558, 4789, {2}, true);
  g->ShapeProduct(1558, 4788, {2});
  g->Binary(ynn_binary_divide, 4789, 4788, 1561);
  g->Binary(ynn_binary_add, 1561, 5241, 1562);
  g->Unary(ynn_unary_rsqrt, 1562, 1563);
  g->Binary(ynn_binary_multiply, 1557, 1563, 1564);
  g->Binary(ynn_binary_multiply, 1564, 5462, 1565);
  BuildLayer18AttentionKvProjection(ctx);
  BuildLayer18AttentionCacheUpdate(ctx);
  BuildLayer18AttentionQueryProjection(ctx);
  BuildLayer18AttentionSdpa(ctx);
  BuildLayer18AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1638, 1639);
  g->Reduce(ynn_reduce_sum, 1639, 4813, {2}, true);
  g->ShapeProduct(1639, 4812, {2});
  g->Binary(ynn_binary_divide, 4813, 4812, 1641);
  g->Binary(ynn_binary_add, 1641, 5241, 1642);
  g->Unary(ynn_unary_rsqrt, 1642, 1643);
  g->Binary(ynn_binary_multiply, 1638, 1643, 1644);
  g->Binary(ynn_binary_multiply, 1644, 5469, 1645);
  g->Binary(ynn_binary_add, 1645, 1557, 1646);
}

// Scope: "Layer18 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1646, 1647);
  g->Reduce(ynn_reduce_sum, 1647, 4815, {2}, true);
  g->ShapeProduct(1647, 4814, {2});
  g->Binary(ynn_binary_divide, 4815, 4814, 1648);
  g->Binary(ynn_binary_add, 1648, 5241, 1649);
  g->Unary(ynn_unary_rsqrt, 1649, 1650);
  g->Binary(ynn_binary_multiply, 1646, 1650, 1652);
  g->Binary(ynn_binary_multiply, 1652, 5472, 1653);
  g->Quantize(1653, 1654, 0.0140849519520998, 0);
  g->Transpose(5466, 3767, {1,0});
  g->Binary(ynn_binary_multiply, 3764, 3766, 3762);
  g->Dot(1654, 3767, YNN_INVALID_VALUE_ID, 3761, 1);
  g->DequantizeTensor(3761, YNN_INVALID_VALUE_ID, 3762, 3763);
  g->QuantizeTensor(3763, 5190, 3765, 1655);
  g->Dequantize(1655, 1656, 0.016732292249798775, 0);
  g->Transpose(5465, 3772, {1,0});
  g->Binary(ynn_binary_multiply, 3764, 3771, 3769);
  g->Dot(1654, 3772, YNN_INVALID_VALUE_ID, 3768, 1);
  g->DequantizeTensor(3768, YNN_INVALID_VALUE_ID, 3769, 3770);
  g->QuantizeTensor(3770, 5190, 3765, 1657);
  g->Dequantize(1657, 1658, 0.016732292249798775, 0);
  g->Polynomial(1658, 4818, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 4818, 4819);
  g->Binary(ynn_binary_add, 4819, 4364, 4816);
  g->Binary(ynn_binary_multiply, 1658, 4376, 4817);
  g->Binary(ynn_binary_multiply, 4817, 4816, 1659);
  g->Binary(ynn_binary_multiply, 1656, 1659, 1660);
  g->Quantize(1660, 1663, 0.009719498455524445, 0);
  g->Transpose(5464, 3779, {1,0});
  g->Binary(ynn_binary_multiply, 3776, 3778, 3774);
  g->Dot(1663, 3779, YNN_INVALID_VALUE_ID, 3773, 1);
  g->DequantizeTensor(3773, YNN_INVALID_VALUE_ID, 3774, 3775);
  g->QuantizeTensor(3775, 5190, 3777, 1664);
  g->Dequantize(1664, 1665, 0.00551135279238224, 0);
  g->Unary(ynn_unary_square, 1665, 1666);
  g->Reduce(ynn_reduce_sum, 1666, 4821, {2}, true);
  g->ShapeProduct(1666, 4820, {2});
  g->Binary(ynn_binary_divide, 4821, 4820, 1667);
  g->Binary(ynn_binary_add, 1667, 5241, 1668);
  g->Unary(ynn_unary_rsqrt, 1668, 1669);
  g->Binary(ynn_binary_multiply, 1665, 1669, 1670);
  g->Binary(ynn_binary_multiply, 1670, 5470, 1671);
  g->Binary(ynn_binary_add, 1671, 1646, 1672);
}

// Scope: "Layer18 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 1674, {0,0,18,0}, {-1,-1,1,-1});
  g->Reshape(1674, 1675, {1,0,256});
  g->Unary(ynn_unary_square, 1675, 1676);
  g->Reduce(ynn_reduce_sum, 1676, 4823, {2}, true);
  g->ShapeProduct(1676, 4822, {2});
  g->Binary(ynn_binary_divide, 4823, 4822, 1677);
  g->Binary(ynn_binary_add, 1677, 5241, 1678);
  g->Unary(ynn_unary_rsqrt, 1678, 1679);
  g->Binary(ynn_binary_multiply, 1675, 1679, 1680);
  g->Binary(ynn_binary_multiply, 1680, 5688, 1681);
  g->Binary(ynn_binary_multiply, 5699, 5245, 1682);
  g->Binary(ynn_binary_add, 1681, 1682, 1683);
  g->Binary(ynn_binary_multiply, 1683, 5240, 1685);
  g->Quantize(1672, 1686, 0.157975435256958, 0);
  g->Transpose(5467, 3786, {1,0});
  g->Binary(ynn_binary_multiply, 3783, 3785, 3781);
  g->Dot(1686, 3786, YNN_INVALID_VALUE_ID, 3780, 1);
  g->DequantizeTensor(3780, YNN_INVALID_VALUE_ID, 3781, 3782);
  g->QuantizeTensor(3782, 5190, 3784, 1687);
  g->Dequantize(1687, 1688, 0.06397638469934464, 0);
  g->Polynomial(1688, 4826, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 4826, 4827);
  g->Binary(ynn_binary_add, 4827, 4364, 4824);
  g->Binary(ynn_binary_multiply, 1688, 4376, 4825);
  g->Binary(ynn_binary_multiply, 4825, 4824, 1689);
  g->Binary(ynn_binary_multiply, 1689, 1685, 1690);
  g->Quantize(1690, 1691, 0.48622047901153564, 0);
  g->Transpose(5468, 3793, {1,0});
  g->Binary(ynn_binary_multiply, 3790, 3792, 3788);
  g->Dot(1691, 3793, YNN_INVALID_VALUE_ID, 3787, 1);
  g->DequantizeTensor(3787, YNN_INVALID_VALUE_ID, 3788, 3789);
  g->QuantizeTensor(3789, 5190, 3791, 1692);
  g->Dequantize(1692, 1693, 0.13593116402626038, 0);
  g->Unary(ynn_unary_square, 1693, 1694);
  g->Reduce(ynn_reduce_sum, 1694, 4829, {2}, true);
  g->ShapeProduct(1694, 4828, {2});
  g->Binary(ynn_binary_divide, 4829, 4828, 1696);
  g->Binary(ynn_binary_add, 1696, 5241, 1697);
  g->Unary(ynn_unary_rsqrt, 1697, 1698);
  g->Binary(ynn_binary_multiply, 1693, 1698, 1699);
  g->Binary(ynn_binary_multiply, 1699, 5471, 1700);
  g->Binary(ynn_binary_add, 1672, 1700, 1701);
  g->Binary(ynn_binary_multiply, 1701, 5463, 1702);
}

// Scope: "Layer18"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18(Context& ctx) {
  BuildLayer18Attention(ctx);
  BuildLayer18Mlp(ctx);
  BuildLayer18PerLayerEmbedding(ctx);
}

}  // namespace BuildGemma4PrefillSource
