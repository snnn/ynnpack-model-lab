// Generated YNNPACK builder; do not edit.
#include "gemma4_decode_builder.h"

namespace BuildGemma4DecodeSource {

// Scope: "Layer11 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(578, 579, 0.043663885444402695, 0);
  g->Transpose(8934, 5341, {1,0});
  g->Binary(ynn_binary_multiply, 5338, 5340, 5336);
  g->Dot(579, 5341, YNN_INVALID_VALUE_ID, 5335, 1);
  g->DequantizeTensor(5335, YNN_INVALID_VALUE_ID, 5336, 5337);
  g->QuantizeTensor(5337, 8727, 5339, 581);
  g->Dequantize(581, 582, 0.05019685998558998, 0);
  g->SplitDim(582, 583, 2, {2,512});
  g->FuseDims(583, 585, 1, 2);
  g->SplitDim(585, 584, 1, {2,1});
  g->Unary(ynn_unary_square, 584, 586);
  g->Reduce(ynn_reduce_sum, 586, 7446, {3}, true);
  g->ShapeProduct(586, 7445, {3});
  g->Binary(ynn_binary_divide, 7446, 7445, 587);
  g->Binary(ynn_binary_add, 587, 8779, 588);
  g->Unary(ynn_unary_rsqrt, 588, 589);
  g->Binary(ynn_binary_multiply, 584, 589, 590);
  g->Binary(ynn_binary_multiply, 590, 8933, 591);
  g->Slice(591, 593, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(591, 594, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 594, 595);
  g->Concat({595,593}, 596, 3);
  g->Binary(ynn_binary_multiply, 591, 4959, 597);
  g->Binary(ynn_binary_multiply, 596, 2, 598);
  g->Binary(ynn_binary_add, 597, 598, 599);
  g->Transpose(8938, 5346, {1,0});
  g->Binary(ynn_binary_multiply, 5338, 5345, 5343);
  g->Dot(579, 5346, YNN_INVALID_VALUE_ID, 5342, 1);
  g->DequantizeTensor(5342, YNN_INVALID_VALUE_ID, 5343, 5344);
  g->QuantizeTensor(5344, 8727, 5339, 600);
  g->Dequantize(600, 601, 0.05019685998558998, 0);
  g->SplitDim(601, 603, 2, {2,512});
  g->FuseDims(603, 605, 1, 2);
  g->SplitDim(605, 604, 1, {2,1});
  g->Unary(ynn_unary_square, 604, 606);
  g->Reduce(ynn_reduce_sum, 606, 7448, {3}, true);
  g->ShapeProduct(606, 7447, {3});
  g->Binary(ynn_binary_divide, 7448, 7447, 607);
  g->Binary(ynn_binary_add, 607, 8779, 608);
  g->Unary(ynn_unary_rsqrt, 608, 609);
  g->Binary(ynn_binary_multiply, 604, 609, 610);
}

// Scope: "Layer11 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(599, 611, 0.0011474735802039504, 0);
  g->Append(8731, 611, 9580, 2, s2, slinky::expr(int64_t{1}));
  g->View(9580, 9628, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(610, 613, 0.01785714365541935, 0);
  g->Append(8755, 613, 9604, 2, s2, slinky::expr(int64_t{1}));
  g->View(9604, 9652, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer11 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(8937, 5352, {1,0});
  g->Binary(ynn_binary_multiply, 5338, 5351, 5348);
  g->Dot(579, 5352, YNN_INVALID_VALUE_ID, 5347, 1);
  g->DequantizeTensor(5347, YNN_INVALID_VALUE_ID, 5348, 5349);
  g->QuantizeTensor(5349, 8727, 5350, 614);
  g->Dequantize(614, 615, 0.0664370134472847, 0);
  g->SplitDim(615, 616, 2, {8,512});
  g->FuseDims(616, 618, 1, 2);
  g->SplitDim(618, 617, 1, {8,1});
  g->Unary(ynn_unary_square, 617, 619);
  g->Reduce(ynn_reduce_sum, 619, 7450, {3}, true);
  g->ShapeProduct(619, 7449, {3});
  g->Binary(ynn_binary_divide, 7450, 7449, 620);
  g->Binary(ynn_binary_add, 620, 8779, 622);
  g->Unary(ynn_unary_rsqrt, 622, 623);
  g->Binary(ynn_binary_multiply, 617, 623, 624);
  g->Binary(ynn_binary_multiply, 624, 8936, 625);
  g->Slice(625, 626, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(625, 627, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 627, 628);
  g->Concat({628,626}, 629, 3);
  g->Binary(ynn_binary_multiply, 625, 4959, 630);
  g->Binary(ynn_binary_multiply, 629, 2, 631);
  g->Binary(ynn_binary_add, 630, 631, 633);
}

// Scope: "Layer11 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9628, 634, 0.0011474735802039504, 0);
  g->Dequantize(9652, 635, 0.01785714365541935, 0);
  g->Slice(633, 636, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(634, 637, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(635, 638, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(636, 637, 639, false, true);
  g->Mask(639, 8790, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 8790, 7454, {-1}, true);
  g->Binary(ynn_binary_subtract, 8790, 7454, 7451);
  g->Unary(ynn_unary_exp, 7451, 7452);
  g->Reduce(ynn_reduce_sum, 7452, 7455, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 7455, 7453);
  g->Binary(ynn_binary_multiply, 7452, 7453, 640);
  g->Matmul(640, 638, 641, false, false);
  g->Slice(633, 644, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(634, 645, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(635, 646, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(644, 645, 647, false, true);
  g->Mask(647, 8791, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 8791, 7461, {-1}, true);
  g->Binary(ynn_binary_subtract, 8791, 7461, 7458);
  g->Unary(ynn_unary_exp, 7458, 7459);
  g->Reduce(ynn_reduce_sum, 7459, 7462, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 7462, 7460);
  g->Binary(ynn_binary_multiply, 7459, 7460, 648);
  g->Matmul(648, 646, 649, false, false);
  g->Concat({641,649}, 650, 1);
}

// Scope: "Layer11 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(650, 652, 1, 2);
  g->SplitDim(652, 651, 1, {1,8});
  g->FuseDims(651, 653, 2, 2);
  g->Quantize(653, 655, 0.016240166500210762, 0);
  g->Transpose(8935, 5366, {1,0});
  g->Binary(ynn_binary_multiply, 5363, 5365, 5361);
  g->Dot(655, 5366, YNN_INVALID_VALUE_ID, 5360, 1);
  g->DequantizeTensor(5360, YNN_INVALID_VALUE_ID, 5361, 5362);
  g->QuantizeTensor(5362, 8727, 5364, 656);
  g->Dequantize(656, 657, 0.13702435791492462, 0);
}

// Scope: "Layer11 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 572, 573);
  g->Reduce(ynn_reduce_sum, 573, 7442, {2}, true);
  g->ShapeProduct(573, 7441, {2});
  g->Binary(ynn_binary_divide, 7442, 7441, 574);
  g->Binary(ynn_binary_add, 574, 8779, 575);
  g->Unary(ynn_unary_rsqrt, 575, 576);
  g->Binary(ynn_binary_multiply, 572, 576, 577);
  g->Binary(ynn_binary_multiply, 577, 8922, 578);
  BuildLayer11AttentionKvProjection(ctx);
  BuildLayer11AttentionCacheUpdate(ctx);
  BuildLayer11AttentionQueryProjection(ctx);
  BuildLayer11AttentionSdpa(ctx);
  BuildLayer11AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 657, 658);
  g->Reduce(ynn_reduce_sum, 658, 7464, {2}, true);
  g->ShapeProduct(658, 7463, {2});
  g->Binary(ynn_binary_divide, 7464, 7463, 659);
  g->Binary(ynn_binary_add, 659, 8779, 660);
  g->Unary(ynn_unary_rsqrt, 660, 661);
  g->Binary(ynn_binary_multiply, 657, 661, 662);
  g->Binary(ynn_binary_multiply, 662, 8929, 663);
  g->Binary(ynn_binary_add, 663, 572, 664);
}

// Scope: "Layer11 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 664, 666);
  g->Reduce(ynn_reduce_sum, 666, 7466, {2}, true);
  g->ShapeProduct(666, 7465, {2});
  g->Binary(ynn_binary_divide, 7466, 7465, 667);
  g->Binary(ynn_binary_add, 667, 8779, 668);
  g->Unary(ynn_unary_rsqrt, 668, 669);
  g->Binary(ynn_binary_multiply, 664, 669, 670);
  g->Binary(ynn_binary_multiply, 670, 8932, 671);
  g->Quantize(671, 672, 0.023192334920167923, 0);
  g->Transpose(8926, 5373, {1,0});
  g->Binary(ynn_binary_multiply, 5370, 5372, 5368);
  g->Dot(672, 5373, YNN_INVALID_VALUE_ID, 5367, 1);
  g->DequantizeTensor(5367, YNN_INVALID_VALUE_ID, 5368, 5369);
  g->QuantizeTensor(5369, 8727, 5371, 673);
  g->Dequantize(673, 674, 0.03223426267504692, 0);
  g->Transpose(8925, 5378, {1,0});
  g->Binary(ynn_binary_multiply, 5370, 5377, 5375);
  g->Dot(672, 5378, YNN_INVALID_VALUE_ID, 5374, 1);
  g->DequantizeTensor(5374, YNN_INVALID_VALUE_ID, 5375, 5376);
  g->QuantizeTensor(5376, 8727, 5371, 677);
  g->Dequantize(677, 678, 0.03223426267504692, 0);
  g->Polynomial(678, 7469, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7469, 7470);
  g->Binary(ynn_binary_add, 7470, 7293, 7467);
  g->Binary(ynn_binary_multiply, 678, 7305, 7468);
  g->Binary(ynn_binary_multiply, 7468, 7467, 679);
  g->Binary(ynn_binary_multiply, 674, 679, 680);
  g->Quantize(680, 681, 0.07480315864086151, 0);
  g->Transpose(8924, 5385, {1,0});
  g->Binary(ynn_binary_multiply, 5382, 5384, 5380);
  g->Dot(681, 5385, YNN_INVALID_VALUE_ID, 5379, 1);
  g->DequantizeTensor(5379, YNN_INVALID_VALUE_ID, 5380, 5381);
  g->QuantizeTensor(5381, 8727, 5383, 682);
  g->Dequantize(682, 683, 0.03340588137507439, 0);
  g->Unary(ynn_unary_square, 683, 684);
  g->Reduce(ynn_reduce_sum, 684, 7472, {2}, true);
  g->ShapeProduct(684, 7471, {2});
  g->Binary(ynn_binary_divide, 7472, 7471, 685);
  g->Binary(ynn_binary_add, 685, 8779, 686);
  g->Unary(ynn_unary_rsqrt, 686, 688);
  g->Binary(ynn_binary_multiply, 683, 688, 689);
  g->Binary(ynn_binary_multiply, 689, 8930, 690);
  g->Binary(ynn_binary_add, 690, 664, 691);
}

// Scope: "Layer11 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(429, 692, {0,0,11,0}, {-1,-1,1,-1});
  g->Reshape(692, 693, {1,1,256});
  g->Unary(ynn_unary_square, 693, 694);
  g->Reduce(ynn_reduce_sum, 694, 7474, {2}, true);
  g->ShapeProduct(694, 7473, {2});
  g->Binary(ynn_binary_divide, 7474, 7473, 695);
  g->Binary(ynn_binary_add, 695, 8779, 696);
  g->Unary(ynn_unary_rsqrt, 696, 697);
  g->Binary(ynn_binary_multiply, 693, 697, 699);
  g->Binary(ynn_binary_multiply, 699, 9533, 700);
  g->Binary(ynn_binary_multiply, 9537, 8783, 701);
  g->Binary(ynn_binary_add, 700, 701, 702);
  g->Binary(ynn_binary_multiply, 702, 8777, 703);
  g->Quantize(691, 704, 0.18839792907238007, 0);
  g->Transpose(8927, 5392, {1,0});
  g->Binary(ynn_binary_multiply, 5389, 5391, 5387);
  g->Dot(704, 5392, YNN_INVALID_VALUE_ID, 5386, 1);
  g->DequantizeTensor(5386, YNN_INVALID_VALUE_ID, 5387, 5388);
  g->QuantizeTensor(5388, 8727, 5390, 705);
  g->Dequantize(705, 706, 0.08759843558073044, 0);
  g->Polynomial(706, 7479, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7479, 7480);
  g->Binary(ynn_binary_add, 7480, 7293, 7477);
  g->Binary(ynn_binary_multiply, 706, 7305, 7478);
  g->Binary(ynn_binary_multiply, 7478, 7477, 707);
  g->Binary(ynn_binary_multiply, 707, 703, 708);
  g->Quantize(708, 710, 1.6850394010543823, 0);
  g->Transpose(8928, 5399, {1,0});
  g->Binary(ynn_binary_multiply, 5396, 5398, 5394);
  g->Dot(710, 5399, YNN_INVALID_VALUE_ID, 5393, 1);
  g->DequantizeTensor(5393, YNN_INVALID_VALUE_ID, 5394, 5395);
  g->QuantizeTensor(5395, 8727, 5397, 711);
  g->Dequantize(711, 712, 0.46903082728385925, 0);
  g->Unary(ynn_unary_square, 712, 713);
  g->Reduce(ynn_reduce_sum, 713, 7482, {2}, true);
  g->ShapeProduct(713, 7481, {2});
  g->Binary(ynn_binary_divide, 7482, 7481, 714);
  g->Binary(ynn_binary_add, 714, 8779, 715);
  g->Unary(ynn_unary_rsqrt, 715, 716);
  g->Binary(ynn_binary_multiply, 712, 716, 717);
  g->Binary(ynn_binary_multiply, 717, 8931, 718);
  g->Binary(ynn_binary_add, 691, 718, 719);
  g->Binary(ynn_binary_multiply, 719, 8923, 721);
}

// Scope: "Layer11"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11(Context& ctx) {
  BuildLayer11Attention(ctx);
  BuildLayer11Mlp(ctx);
  BuildLayer11PerLayerEmbedding(ctx);
}

// Scope: "Layer12 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(727, 728, 0.11905524879693985, 0);
  g->Transpose(8951, 5406, {1,0});
  g->Binary(ynn_binary_multiply, 5403, 5405, 5401);
  g->Dot(728, 5406, YNN_INVALID_VALUE_ID, 5400, 1);
  g->DequantizeTensor(5400, YNN_INVALID_VALUE_ID, 5401, 5402);
  g->QuantizeTensor(5402, 8727, 5404, 729);
  g->Dequantize(729, 730, 0.2027559131383896, 0);
  g->SplitDim(730, 732, 2, {2,256});
  g->FuseDims(732, 734, 1, 2);
  g->SplitDim(734, 733, 1, {2,1});
  g->Unary(ynn_unary_square, 733, 735);
  g->Reduce(ynn_reduce_sum, 735, 7486, {3}, true);
  g->ShapeProduct(735, 7485, {3});
  g->Binary(ynn_binary_divide, 7486, 7485, 736);
  g->Binary(ynn_binary_add, 736, 8779, 737);
  g->Unary(ynn_unary_rsqrt, 737, 738);
  g->Binary(ynn_binary_multiply, 733, 738, 739);
  g->Binary(ynn_binary_multiply, 739, 8950, 740);
  g->Slice(740, 741, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(740, 742, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 742, 744);
  g->Concat({744,741}, 745, 3);
  g->Binary(ynn_binary_multiply, 740, 3231, 746);
  g->Binary(ynn_binary_multiply, 745, 4329, 747);
  g->Binary(ynn_binary_add, 746, 747, 748);
  g->Transpose(8955, 5411, {1,0});
  g->Binary(ynn_binary_multiply, 5403, 5410, 5408);
  g->Dot(728, 5411, YNN_INVALID_VALUE_ID, 5407, 1);
  g->DequantizeTensor(5407, YNN_INVALID_VALUE_ID, 5408, 5409);
  g->QuantizeTensor(5409, 8727, 5404, 749);
  g->Dequantize(749, 750, 0.2027559131383896, 0);
  g->SplitDim(750, 751, 2, {2,256});
  g->FuseDims(751, 753, 1, 2);
  g->SplitDim(753, 752, 1, {2,1});
  g->Unary(ynn_unary_square, 752, 756);
  g->Reduce(ynn_reduce_sum, 756, 7488, {3}, true);
  g->ShapeProduct(756, 7487, {3});
  g->Binary(ynn_binary_divide, 7488, 7487, 757);
  g->Binary(ynn_binary_add, 757, 8779, 758);
  g->Unary(ynn_unary_rsqrt, 758, 759);
  g->Binary(ynn_binary_multiply, 752, 759, 760);
}

// Scope: "Layer12 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(748, 761, 0.005684707313776016, 0);
  g->Append(8732, 761, 9581, 2, s2, slinky::expr(int64_t{1}));
  g->View(9581, 9629, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(760, 762, 0.047244105488061905, 0);
  g->Append(8756, 762, 9605, 2, s2, slinky::expr(int64_t{1}));
  g->View(9605, 9653, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer12 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(8954, 5417, {1,0});
  g->Binary(ynn_binary_multiply, 5403, 5416, 5413);
  g->Dot(728, 5417, YNN_INVALID_VALUE_ID, 5412, 1);
  g->DequantizeTensor(5412, YNN_INVALID_VALUE_ID, 5413, 5414);
  g->QuantizeTensor(5414, 8727, 5415, 764);
  g->Dequantize(764, 765, 0.20964568853378296, 0);
  g->SplitDim(765, 766, 2, {8,256});
  g->FuseDims(766, 768, 1, 2);
  g->SplitDim(768, 767, 1, {8,1});
  g->Unary(ynn_unary_square, 767, 769);
  g->Reduce(ynn_reduce_sum, 769, 7490, {3}, true);
  g->ShapeProduct(769, 7489, {3});
  g->Binary(ynn_binary_divide, 7490, 7489, 770);
  g->Binary(ynn_binary_add, 770, 8779, 771);
  g->Unary(ynn_unary_rsqrt, 771, 772);
  g->Binary(ynn_binary_multiply, 767, 772, 774);
  g->Binary(ynn_binary_multiply, 774, 8953, 775);
  g->Slice(775, 776, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(775, 777, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 777, 778);
  g->Concat({778,776}, 779, 3);
  g->Binary(ynn_binary_multiply, 775, 3231, 780);
  g->Binary(ynn_binary_multiply, 779, 4329, 781);
  g->Binary(ynn_binary_add, 780, 781, 782);
}

// Scope: "Layer12 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9629, 783, 0.005684707313776016, 0);
  g->Dequantize(9653, 785, 0.047244105488061905, 0);
  g->Slice(782, 786, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(783, 787, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(785, 788, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(786, 787, 789, false, true);
  g->Mask(789, 8792, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8792, 7494, {-1}, true);
  g->Binary(ynn_binary_subtract, 8792, 7494, 7491);
  g->Unary(ynn_unary_exp, 7491, 7492);
  g->Reduce(ynn_reduce_sum, 7492, 7495, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 7495, 7493);
  g->Binary(ynn_binary_multiply, 7492, 7493, 790);
  g->Matmul(790, 788, 791, false, false);
  g->Slice(782, 792, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(783, 793, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(785, 795, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(792, 793, 796, false, true);
  g->Mask(796, 8793, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8793, 7499, {-1}, true);
  g->Binary(ynn_binary_subtract, 8793, 7499, 7496);
  g->Unary(ynn_unary_exp, 7496, 7497);
  g->Reduce(ynn_reduce_sum, 7497, 7500, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 7500, 7498);
  g->Binary(ynn_binary_multiply, 7497, 7498, 797);
  g->Matmul(797, 795, 798, false, false);
  g->Concat({791,798}, 799, 1);
}

// Scope: "Layer12 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(799, 801, 1, 2);
  g->SplitDim(801, 800, 1, {1,8});
  g->FuseDims(800, 802, 2, 2);
  g->Quantize(802, 803, 0.028912410140037537, 0);
  g->Transpose(8952, 5424, {1,0});
  g->Binary(ynn_binary_multiply, 5421, 5423, 5419);
  g->Dot(803, 5424, YNN_INVALID_VALUE_ID, 5418, 1);
  g->DequantizeTensor(5418, YNN_INVALID_VALUE_ID, 5419, 5420);
  g->QuantizeTensor(5420, 8727, 5422, 804);
  g->Dequantize(804, 806, 0.11405377089977264, 0);
}

// Scope: "Layer12 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 721, 722);
  g->Reduce(ynn_reduce_sum, 722, 7484, {2}, true);
  g->ShapeProduct(722, 7483, {2});
  g->Binary(ynn_binary_divide, 7484, 7483, 723);
  g->Binary(ynn_binary_add, 723, 8779, 724);
  g->Unary(ynn_unary_rsqrt, 724, 725);
  g->Binary(ynn_binary_multiply, 721, 725, 726);
  g->Binary(ynn_binary_multiply, 726, 8939, 727);
  BuildLayer12AttentionKvProjection(ctx);
  BuildLayer12AttentionCacheUpdate(ctx);
  BuildLayer12AttentionQueryProjection(ctx);
  BuildLayer12AttentionSdpa(ctx);
  BuildLayer12AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 806, 807);
  g->Reduce(ynn_reduce_sum, 807, 7502, {2}, true);
  g->ShapeProduct(807, 7501, {2});
  g->Binary(ynn_binary_divide, 7502, 7501, 808);
  g->Binary(ynn_binary_add, 808, 8779, 809);
  g->Unary(ynn_unary_rsqrt, 809, 810);
  g->Binary(ynn_binary_multiply, 806, 810, 811);
  g->Binary(ynn_binary_multiply, 811, 8946, 812);
  g->Binary(ynn_binary_add, 812, 721, 813);
}

// Scope: "Layer12 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 813, 814);
  g->Reduce(ynn_reduce_sum, 814, 7504, {2}, true);
  g->ShapeProduct(814, 7503, {2});
  g->Binary(ynn_binary_divide, 7504, 7503, 815);
  g->Binary(ynn_binary_add, 815, 8779, 817);
  g->Unary(ynn_unary_rsqrt, 817, 818);
  g->Binary(ynn_binary_multiply, 813, 818, 819);
  g->Binary(ynn_binary_multiply, 819, 8949, 820);
  g->Quantize(820, 821, 0.029738755896687508, 0);
  g->Transpose(8943, 5431, {1,0});
  g->Binary(ynn_binary_multiply, 5428, 5430, 5426);
  g->Dot(821, 5431, YNN_INVALID_VALUE_ID, 5425, 1);
  g->DequantizeTensor(5425, YNN_INVALID_VALUE_ID, 5426, 5427);
  g->QuantizeTensor(5427, 8727, 5429, 822);
  g->Dequantize(822, 823, 0.05216536670923233, 0);
  g->Transpose(8942, 5436, {1,0});
  g->Binary(ynn_binary_multiply, 5428, 5435, 5433);
  g->Dot(821, 5436, YNN_INVALID_VALUE_ID, 5432, 1);
  g->DequantizeTensor(5432, YNN_INVALID_VALUE_ID, 5433, 5434);
  g->QuantizeTensor(5434, 8727, 5429, 824);
  g->Dequantize(824, 825, 0.05216536670923233, 0);
  g->Polynomial(825, 7507, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7507, 7508);
  g->Binary(ynn_binary_add, 7508, 7293, 7505);
  g->Binary(ynn_binary_multiply, 825, 7305, 7506);
  g->Binary(ynn_binary_multiply, 7506, 7505, 826);
  g->Binary(ynn_binary_multiply, 823, 826, 827);
  g->Quantize(827, 828, 0.09350394457578659, 0);
  g->Transpose(8941, 5443, {1,0});
  g->Binary(ynn_binary_multiply, 5440, 5442, 5438);
  g->Dot(828, 5443, YNN_INVALID_VALUE_ID, 5437, 1);
  g->DequantizeTensor(5437, YNN_INVALID_VALUE_ID, 5438, 5439);
  g->QuantizeTensor(5439, 8727, 5441, 829);
  g->Dequantize(829, 830, 0.0321725495159626, 0);
  g->Unary(ynn_unary_square, 830, 831);
  g->Reduce(ynn_reduce_sum, 831, 7510, {2}, true);
  g->ShapeProduct(831, 7509, {2});
  g->Binary(ynn_binary_divide, 7510, 7509, 832);
  g->Binary(ynn_binary_add, 832, 8779, 833);
  g->Unary(ynn_unary_rsqrt, 833, 834);
  g->Binary(ynn_binary_multiply, 830, 834, 835);
  g->Binary(ynn_binary_multiply, 835, 8947, 837);
  g->Binary(ynn_binary_add, 837, 813, 838);
}

// Scope: "Layer12 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(429, 839, {0,0,12,0}, {-1,-1,1,-1});
  g->Reshape(839, 840, {1,1,256});
  g->Unary(ynn_unary_square, 840, 841);
  g->Reduce(ynn_reduce_sum, 841, 7512, {2}, true);
  g->ShapeProduct(841, 7511, {2});
  g->Binary(ynn_binary_divide, 7512, 7511, 842);
  g->Binary(ynn_binary_add, 842, 8779, 843);
  g->Unary(ynn_unary_rsqrt, 843, 844);
  g->Binary(ynn_binary_multiply, 840, 844, 845);
  g->Binary(ynn_binary_multiply, 845, 9533, 846);
  g->Binary(ynn_binary_multiply, 9538, 8783, 848);
  g->Binary(ynn_binary_add, 846, 848, 849);
  g->Binary(ynn_binary_multiply, 849, 8777, 850);
  g->Quantize(838, 851, 0.6675296425819397, 0);
  g->Transpose(8944, 5455, {1,0});
  g->Binary(ynn_binary_multiply, 5452, 5454, 5450);
  g->Dot(851, 5455, YNN_INVALID_VALUE_ID, 5449, 1);
  g->DequantizeTensor(5449, YNN_INVALID_VALUE_ID, 5450, 5451);
  g->QuantizeTensor(5451, 8727, 5453, 852);
  g->Dequantize(852, 853, 0.09104331582784653, 0);
  g->Polynomial(853, 7515, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7515, 7516);
  g->Binary(ynn_binary_add, 7516, 7293, 7513);
  g->Binary(ynn_binary_multiply, 853, 7305, 7514);
  g->Binary(ynn_binary_multiply, 7514, 7513, 854);
  g->Binary(ynn_binary_multiply, 854, 850, 855);
  g->Quantize(855, 856, 0.712598443031311, 0);
  g->Transpose(8945, 5462, {1,0});
  g->Binary(ynn_binary_multiply, 5459, 5461, 5457);
  g->Dot(856, 5462, YNN_INVALID_VALUE_ID, 5456, 1);
  g->DequantizeTensor(5456, YNN_INVALID_VALUE_ID, 5457, 5458);
  g->QuantizeTensor(5458, 8727, 5460, 857);
  g->Dequantize(857, 860, 0.15073752403259277, 0);
  g->Unary(ynn_unary_square, 860, 861);
  g->Reduce(ynn_reduce_sum, 861, 7518, {2}, true);
  g->ShapeProduct(861, 7517, {2});
  g->Binary(ynn_binary_divide, 7518, 7517, 862);
  g->Binary(ynn_binary_add, 862, 8779, 863);
  g->Unary(ynn_unary_rsqrt, 863, 864);
  g->Binary(ynn_binary_multiply, 860, 864, 865);
  g->Binary(ynn_binary_multiply, 865, 8948, 866);
  g->Binary(ynn_binary_add, 838, 866, 867);
  g->Binary(ynn_binary_multiply, 867, 8940, 868);
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
  g->Quantize(876, 877, 0.11864537745714188, 0);
  g->Transpose(8968, 5469, {1,0});
  g->Binary(ynn_binary_multiply, 5466, 5468, 5464);
  g->Dot(877, 5469, YNN_INVALID_VALUE_ID, 5463, 1);
  g->DequantizeTensor(5463, YNN_INVALID_VALUE_ID, 5464, 5465);
  g->QuantizeTensor(5465, 8727, 5467, 878);
  g->Dequantize(878, 879, 0.18700788915157318, 0);
  g->SplitDim(879, 880, 2, {2,256});
  g->FuseDims(880, 882, 1, 2);
  g->SplitDim(882, 881, 1, {2,1});
  g->Unary(ynn_unary_square, 881, 884);
  g->Reduce(ynn_reduce_sum, 884, 7522, {3}, true);
  g->ShapeProduct(884, 7521, {3});
  g->Binary(ynn_binary_divide, 7522, 7521, 885);
  g->Binary(ynn_binary_add, 885, 8779, 886);
  g->Unary(ynn_unary_rsqrt, 886, 887);
  g->Binary(ynn_binary_multiply, 881, 887, 888);
  g->Binary(ynn_binary_multiply, 888, 8967, 889);
  g->Slice(889, 890, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(889, 891, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 891, 892);
  g->Concat({892,890}, 893, 3);
  g->Binary(ynn_binary_multiply, 889, 3231, 895);
  g->Binary(ynn_binary_multiply, 893, 4329, 896);
  g->Binary(ynn_binary_add, 895, 896, 897);
  g->Transpose(8972, 5474, {1,0});
  g->Binary(ynn_binary_multiply, 5466, 5473, 5471);
  g->Dot(877, 5474, YNN_INVALID_VALUE_ID, 5470, 1);
  g->DequantizeTensor(5470, YNN_INVALID_VALUE_ID, 5471, 5472);
  g->QuantizeTensor(5472, 8727, 5467, 898);
  g->Dequantize(898, 899, 0.18700788915157318, 0);
  g->SplitDim(899, 900, 2, {2,256});
  g->FuseDims(900, 902, 1, 2);
  g->SplitDim(902, 901, 1, {2,1});
  g->Unary(ynn_unary_square, 901, 903);
  g->Reduce(ynn_reduce_sum, 903, 7526, {3}, true);
  g->ShapeProduct(903, 7525, {3});
  g->Binary(ynn_binary_divide, 7526, 7525, 904);
  g->Binary(ynn_binary_add, 904, 8779, 906);
  g->Unary(ynn_unary_rsqrt, 906, 907);
  g->Binary(ynn_binary_multiply, 901, 907, 908);
}

// Scope: "Layer13 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(897, 909, 0.0057707298547029495, 0);
  g->Append(8733, 909, 9582, 2, s2, slinky::expr(int64_t{1}));
  g->View(9582, 9630, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(908, 910, 0.047244105488061905, 0);
  g->Append(8757, 910, 9606, 2, s2, slinky::expr(int64_t{1}));
  g->View(9606, 9654, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer13 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(8971, 5480, {1,0});
  g->Binary(ynn_binary_multiply, 5466, 5479, 5476);
  g->Dot(877, 5480, YNN_INVALID_VALUE_ID, 5475, 1);
  g->DequantizeTensor(5475, YNN_INVALID_VALUE_ID, 5476, 5477);
  g->QuantizeTensor(5477, 8727, 5478, 912);
  g->Dequantize(912, 913, 0.20570868253707886, 0);
  g->SplitDim(913, 914, 2, {8,256});
  g->FuseDims(914, 916, 1, 2);
  g->SplitDim(916, 915, 1, {8,1});
  g->Unary(ynn_unary_square, 915, 917);
  g->Reduce(ynn_reduce_sum, 917, 7528, {3}, true);
  g->ShapeProduct(917, 7527, {3});
  g->Binary(ynn_binary_divide, 7528, 7527, 918);
  g->Binary(ynn_binary_add, 918, 8779, 919);
  g->Unary(ynn_unary_rsqrt, 919, 920);
  g->Binary(ynn_binary_multiply, 915, 920, 921);
  g->Binary(ynn_binary_multiply, 921, 8970, 922);
  g->Slice(922, 924, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(922, 925, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 925, 926);
  g->Concat({926,924}, 927, 3);
  g->Binary(ynn_binary_multiply, 922, 3231, 928);
  g->Binary(ynn_binary_multiply, 927, 4329, 929);
  g->Binary(ynn_binary_add, 928, 929, 930);
}

// Scope: "Layer13 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9630, 931, 0.0057707298547029495, 0);
  g->Dequantize(9654, 932, 0.047244105488061905, 0);
  g->Slice(930, 933, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(931, 935, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(932, 936, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(933, 935, 937, false, true);
  g->Mask(937, 8794, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8794, 7532, {-1}, true);
  g->Binary(ynn_binary_subtract, 8794, 7532, 7529);
  g->Unary(ynn_unary_exp, 7529, 7530);
  g->Reduce(ynn_reduce_sum, 7530, 7533, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 7533, 7531);
  g->Binary(ynn_binary_multiply, 7530, 7531, 938);
  g->Matmul(938, 936, 939, false, false);
  g->Slice(930, 940, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(931, 941, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(932, 942, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(940, 941, 943, false, true);
  g->Mask(943, 8795, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8795, 7537, {-1}, true);
  g->Binary(ynn_binary_subtract, 8795, 7537, 7534);
  g->Unary(ynn_unary_exp, 7534, 7535);
  g->Reduce(ynn_reduce_sum, 7535, 7538, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 7538, 7536);
  g->Binary(ynn_binary_multiply, 7535, 7536, 944);
  g->Matmul(944, 942, 945, false, false);
  g->Concat({939,945}, 946, 1);
}

// Scope: "Layer13 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(946, 948, 1, 2);
  g->SplitDim(948, 947, 1, {1,8});
  g->FuseDims(947, 949, 2, 2);
  g->Quantize(949, 950, 0.023129930719733238, 0);
  g->Transpose(8969, 5487, {1,0});
  g->Binary(ynn_binary_multiply, 5484, 5486, 5482);
  g->Dot(950, 5487, YNN_INVALID_VALUE_ID, 5481, 1);
  g->DequantizeTensor(5481, YNN_INVALID_VALUE_ID, 5482, 5483);
  g->QuantizeTensor(5483, 8727, 5485, 951);
  g->Dequantize(951, 952, 0.0383908711373806, 0);
}

// Scope: "Layer13 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 868, 869);
  g->Reduce(ynn_reduce_sum, 869, 7520, {2}, true);
  g->ShapeProduct(869, 7519, {2});
  g->Binary(ynn_binary_divide, 7520, 7519, 872);
  g->Binary(ynn_binary_add, 872, 8779, 873);
  g->Unary(ynn_unary_rsqrt, 873, 874);
  g->Binary(ynn_binary_multiply, 868, 874, 875);
  g->Binary(ynn_binary_multiply, 875, 8956, 876);
  BuildLayer13AttentionKvProjection(ctx);
  BuildLayer13AttentionCacheUpdate(ctx);
  BuildLayer13AttentionQueryProjection(ctx);
  BuildLayer13AttentionSdpa(ctx);
  BuildLayer13AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 952, 953);
  g->Reduce(ynn_reduce_sum, 953, 7540, {2}, true);
  g->ShapeProduct(953, 7539, {2});
  g->Binary(ynn_binary_divide, 7540, 7539, 954);
  g->Binary(ynn_binary_add, 954, 8779, 955);
  g->Unary(ynn_unary_rsqrt, 955, 956);
  g->Binary(ynn_binary_multiply, 952, 956, 957);
  g->Binary(ynn_binary_multiply, 957, 8963, 958);
  g->Binary(ynn_binary_add, 958, 868, 959);
}

// Scope: "Layer13 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 959, 960);
  g->Reduce(ynn_reduce_sum, 960, 7542, {2}, true);
  g->ShapeProduct(960, 7541, {2});
  g->Binary(ynn_binary_divide, 7542, 7541, 961);
  g->Binary(ynn_binary_add, 961, 8779, 962);
  g->Unary(ynn_unary_rsqrt, 962, 963);
  g->Binary(ynn_binary_multiply, 959, 963, 966);
  g->Binary(ynn_binary_multiply, 966, 8966, 967);
  g->Quantize(967, 968, 0.02818576619029045, 0);
  g->Transpose(8960, 5493, {1,0});
  g->Binary(ynn_binary_multiply, 5491, 5492, 5489);
  g->Dot(968, 5493, YNN_INVALID_VALUE_ID, 5488, 1);
  g->DequantizeTensor(5488, YNN_INVALID_VALUE_ID, 5489, 5490);
  g->QuantizeTensor(5490, 8727, 5120, 969);
  g->Dequantize(969, 970, 0.04675197973847389, 0);
  g->Transpose(8959, 5498, {1,0});
  g->Binary(ynn_binary_multiply, 5491, 5497, 5495);
  g->Dot(968, 5498, YNN_INVALID_VALUE_ID, 5494, 1);
  g->DequantizeTensor(5494, YNN_INVALID_VALUE_ID, 5495, 5496);
  g->QuantizeTensor(5496, 8727, 5120, 971);
  g->Dequantize(971, 972, 0.04675197973847389, 0);
  g->Polynomial(972, 7545, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7545, 7546);
  g->Binary(ynn_binary_add, 7546, 7293, 7543);
  g->Binary(ynn_binary_multiply, 972, 7305, 7544);
  g->Binary(ynn_binary_multiply, 7544, 7543, 973);
  g->Binary(ynn_binary_multiply, 970, 973, 974);
  g->Quantize(974, 975, 0.09202756732702255, 0);
  g->Transpose(8958, 5505, {1,0});
  g->Binary(ynn_binary_multiply, 5502, 5504, 5500);
  g->Dot(975, 5505, YNN_INVALID_VALUE_ID, 5499, 1);
  g->DequantizeTensor(5499, YNN_INVALID_VALUE_ID, 5500, 5501);
  g->QuantizeTensor(5501, 8727, 5503, 976);
  g->Dequantize(976, 977, 0.05065973475575447, 0);
  g->Unary(ynn_unary_square, 977, 978);
  g->Reduce(ynn_reduce_sum, 978, 7548, {2}, true);
  g->ShapeProduct(978, 7547, {2});
  g->Binary(ynn_binary_divide, 7548, 7547, 979);
  g->Binary(ynn_binary_add, 979, 8779, 980);
  g->Unary(ynn_unary_rsqrt, 980, 981);
  g->Binary(ynn_binary_multiply, 977, 981, 982);
  g->Binary(ynn_binary_multiply, 982, 8964, 983);
  g->Binary(ynn_binary_add, 983, 959, 984);
}

// Scope: "Layer13 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(429, 985, {0,0,13,0}, {-1,-1,1,-1});
  g->Reshape(985, 986, {1,1,256});
  g->Unary(ynn_unary_square, 986, 987);
  g->Reduce(ynn_reduce_sum, 987, 7550, {2}, true);
  g->ShapeProduct(987, 7549, {2});
  g->Binary(ynn_binary_divide, 7550, 7549, 988);
  g->Binary(ynn_binary_add, 988, 8779, 989);
  g->Unary(ynn_unary_rsqrt, 989, 990);
  g->Binary(ynn_binary_multiply, 986, 990, 991);
  g->Binary(ynn_binary_multiply, 991, 9533, 992);
  g->Binary(ynn_binary_multiply, 9539, 8783, 993);
  g->Binary(ynn_binary_add, 992, 993, 994);
  g->Binary(ynn_binary_multiply, 994, 8777, 995);
  g->Quantize(984, 996, 0.698938250541687, 0);
  g->Transpose(8961, 5512, {1,0});
  g->Binary(ynn_binary_multiply, 5509, 5511, 5507);
  g->Dot(996, 5512, YNN_INVALID_VALUE_ID, 5506, 1);
  g->DequantizeTensor(5506, YNN_INVALID_VALUE_ID, 5507, 5508);
  g->QuantizeTensor(5508, 8727, 5510, 997);
  g->Dequantize(997, 998, 0.07775591313838959, 0);
  g->Polynomial(998, 7553, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7553, 7554);
  g->Binary(ynn_binary_add, 7554, 7293, 7551);
  g->Binary(ynn_binary_multiply, 998, 7305, 7552);
  g->Binary(ynn_binary_multiply, 7552, 7551, 999);
  g->Binary(ynn_binary_multiply, 999, 995, 1000);
  g->Quantize(1000, 1001, 0.4881889820098877, 0);
  g->Transpose(8962, 5519, {1,0});
  g->Binary(ynn_binary_multiply, 5516, 5518, 5514);
  g->Dot(1001, 5519, YNN_INVALID_VALUE_ID, 5513, 1);
  g->DequantizeTensor(5513, YNN_INVALID_VALUE_ID, 5514, 5515);
  g->QuantizeTensor(5515, 8727, 5517, 1002);
  g->Dequantize(1002, 1003, 0.15653027594089508, 0);
  g->Unary(ynn_unary_square, 1003, 1004);
  g->Reduce(ynn_reduce_sum, 1004, 7556, {2}, true);
  g->ShapeProduct(1004, 7555, {2});
  g->Binary(ynn_binary_divide, 7556, 7555, 1006);
  g->Binary(ynn_binary_add, 1006, 8779, 1007);
  g->Unary(ynn_unary_rsqrt, 1007, 1008);
  g->Binary(ynn_binary_multiply, 1003, 1008, 1009);
  g->Binary(ynn_binary_multiply, 1009, 8965, 1010);
  g->Binary(ynn_binary_add, 984, 1010, 1011);
  g->Binary(ynn_binary_multiply, 1011, 8957, 1012);
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
  g->Quantize(1019, 1020, 0.1454738974571228, 0);
  g->Transpose(8985, 5532, {1,0});
  g->Binary(ynn_binary_multiply, 5529, 5531, 5527);
  g->Dot(1020, 5532, YNN_INVALID_VALUE_ID, 5526, 1);
  g->DequantizeTensor(5526, YNN_INVALID_VALUE_ID, 5527, 5528);
  g->QuantizeTensor(5528, 8727, 5530, 1021);
  g->Dequantize(1021, 1022, 0.25, 0);
  g->SplitDim(1022, 1023, 2, {2,256});
  g->FuseDims(1023, 1025, 1, 2);
  g->SplitDim(1025, 1024, 1, {2,1});
  g->Unary(ynn_unary_square, 1024, 1026);
  g->Reduce(ynn_reduce_sum, 1026, 7560, {3}, true);
  g->ShapeProduct(1026, 7559, {3});
  g->Binary(ynn_binary_divide, 7560, 7559, 1027);
  g->Binary(ynn_binary_add, 1027, 8779, 1029);
  g->Unary(ynn_unary_rsqrt, 1029, 1030);
  g->Binary(ynn_binary_multiply, 1024, 1030, 1031);
  g->Binary(ynn_binary_multiply, 1031, 8984, 1032);
  g->Slice(1032, 1033, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1032, 1034, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1034, 1035);
  g->Concat({1035,1033}, 1036, 3);
  g->Binary(ynn_binary_multiply, 1032, 3231, 1037);
  g->Binary(ynn_binary_multiply, 1036, 4329, 1038);
  g->Binary(ynn_binary_add, 1037, 1038, 1041);
  g->Transpose(8989, 5537, {1,0});
  g->Binary(ynn_binary_multiply, 5529, 5536, 5534);
  g->Dot(1020, 5537, YNN_INVALID_VALUE_ID, 5533, 1);
  g->DequantizeTensor(5533, YNN_INVALID_VALUE_ID, 5534, 5535);
  g->QuantizeTensor(5535, 8727, 5530, 1042);
  g->Dequantize(1042, 1043, 0.25, 0);
  g->SplitDim(1043, 1044, 2, {2,256});
  g->FuseDims(1044, 1046, 1, 2);
  g->SplitDim(1046, 1045, 1, {2,1});
  g->Unary(ynn_unary_square, 1045, 1047);
  g->Reduce(ynn_reduce_sum, 1047, 7562, {3}, true);
  g->ShapeProduct(1047, 7561, {3});
  g->Binary(ynn_binary_divide, 7562, 7561, 1048);
  g->Binary(ynn_binary_add, 1048, 8779, 1049);
  g->Unary(ynn_unary_rsqrt, 1049, 1050);
  g->Binary(ynn_binary_multiply, 1045, 1050, 1052);
}

// Scope: "Layer14 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(1041, 1053, 0.005712664220482111, 0);
  g->Append(8734, 1053, 9583, 2, s2, slinky::expr(int64_t{1}));
  g->View(9583, 9631, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(1052, 1054, 0.047244105488061905, 0);
  g->Append(8758, 1054, 9607, 2, s2, slinky::expr(int64_t{1}));
  g->View(9607, 9655, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer14 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(8988, 5543, {1,0});
  g->Binary(ynn_binary_multiply, 5529, 5542, 5539);
  g->Dot(1020, 5543, YNN_INVALID_VALUE_ID, 5538, 1);
  g->DequantizeTensor(5538, YNN_INVALID_VALUE_ID, 5539, 5540);
  g->QuantizeTensor(5540, 8727, 5541, 1055);
  g->Dequantize(1055, 1056, 0.29133859276771545, 0);
  g->SplitDim(1056, 1058, 2, {8,256});
  g->FuseDims(1058, 1060, 1, 2);
  g->SplitDim(1060, 1059, 1, {8,1});
  g->Unary(ynn_unary_square, 1059, 1061);
  g->Reduce(ynn_reduce_sum, 1061, 7566, {3}, true);
  g->ShapeProduct(1061, 7565, {3});
  g->Binary(ynn_binary_divide, 7566, 7565, 1062);
  g->Binary(ynn_binary_add, 1062, 8779, 1063);
  g->Unary(ynn_unary_rsqrt, 1063, 1064);
  g->Binary(ynn_binary_multiply, 1059, 1064, 1065);
  g->Binary(ynn_binary_multiply, 1065, 8987, 1066);
  g->Slice(1066, 1067, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1066, 1068, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1068, 1072);
  g->Concat({1072,1067}, 1073, 3);
  g->Binary(ynn_binary_multiply, 1066, 3231, 1074);
  g->Binary(ynn_binary_multiply, 1073, 4329, 1075);
  g->Binary(ynn_binary_add, 1074, 1075, 1076);
}

// Scope: "Layer14 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9631, 1077, 0.005712664220482111, 0);
  g->Dequantize(9655, 1078, 0.047244105488061905, 0);
  g->Slice(1076, 1079, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(1077, 1080, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(1078, 1081, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(1079, 1080, 1083, false, true);
  g->Mask(1083, 8796, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8796, 7570, {-1}, true);
  g->Binary(ynn_binary_subtract, 8796, 7570, 7567);
  g->Unary(ynn_unary_exp, 7567, 7568);
  g->Reduce(ynn_reduce_sum, 7568, 7571, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 7571, 7569);
  g->Binary(ynn_binary_multiply, 7568, 7569, 1084);
  g->Matmul(1084, 1081, 1085, false, false);
  g->Slice(1076, 1086, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(1077, 1087, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(1078, 1088, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(1086, 1087, 1089, false, true);
  g->Mask(1089, 8797, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8797, 7575, {-1}, true);
  g->Binary(ynn_binary_subtract, 8797, 7575, 7572);
  g->Unary(ynn_unary_exp, 7572, 7573);
  g->Reduce(ynn_reduce_sum, 7573, 7576, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 7576, 7574);
  g->Binary(ynn_binary_multiply, 7573, 7574, 1090);
  g->Matmul(1090, 1088, 1092, false, false);
  g->Concat({1085,1092}, 1093, 1);
}

// Scope: "Layer14 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(1093, 1095, 1, 2);
  g->SplitDim(1095, 1094, 1, {1,8});
  g->FuseDims(1094, 1096, 2, 2);
  g->Quantize(1096, 1097, 0.02472933940589428, 0);
  g->Transpose(8986, 5550, {1,0});
  g->Binary(ynn_binary_multiply, 5547, 5549, 5545);
  g->Dot(1097, 5550, YNN_INVALID_VALUE_ID, 5544, 1);
  g->DequantizeTensor(5544, YNN_INVALID_VALUE_ID, 5545, 5546);
  g->QuantizeTensor(5546, 8727, 5548, 1098);
  g->Dequantize(1098, 1099, 0.039510589092969894, 0);
}

// Scope: "Layer14 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1012, 1013);
  g->Reduce(ynn_reduce_sum, 1013, 7558, {2}, true);
  g->ShapeProduct(1013, 7557, {2});
  g->Binary(ynn_binary_divide, 7558, 7557, 1014);
  g->Binary(ynn_binary_add, 1014, 8779, 1015);
  g->Unary(ynn_unary_rsqrt, 1015, 1017);
  g->Binary(ynn_binary_multiply, 1012, 1017, 1018);
  g->Binary(ynn_binary_multiply, 1018, 8973, 1019);
  BuildLayer14AttentionKvProjection(ctx);
  BuildLayer14AttentionCacheUpdate(ctx);
  BuildLayer14AttentionQueryProjection(ctx);
  BuildLayer14AttentionSdpa(ctx);
  BuildLayer14AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1099, 1100);
  g->Reduce(ynn_reduce_sum, 1100, 7578, {2}, true);
  g->ShapeProduct(1100, 7577, {2});
  g->Binary(ynn_binary_divide, 7578, 7577, 1101);
  g->Binary(ynn_binary_add, 1101, 8779, 1102);
  g->Unary(ynn_unary_rsqrt, 1102, 1104);
  g->Binary(ynn_binary_multiply, 1099, 1104, 1105);
  g->Binary(ynn_binary_multiply, 1105, 8980, 1106);
  g->Binary(ynn_binary_add, 1106, 1012, 1107);
}

// Scope: "Layer14 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1107, 1108);
  g->Reduce(ynn_reduce_sum, 1108, 7580, {2}, true);
  g->ShapeProduct(1108, 7579, {2});
  g->Binary(ynn_binary_divide, 7580, 7579, 1109);
  g->Binary(ynn_binary_add, 1109, 8779, 1110);
  g->Unary(ynn_unary_rsqrt, 1110, 1111);
  g->Binary(ynn_binary_multiply, 1107, 1111, 1112);
  g->Binary(ynn_binary_multiply, 1112, 8983, 1113);
  g->Quantize(1113, 1115, 0.015675809234380722, 0);
  g->Transpose(8977, 5557, {1,0});
  g->Binary(ynn_binary_multiply, 5554, 5556, 5552);
  g->Dot(1115, 5557, YNN_INVALID_VALUE_ID, 5551, 1);
  g->DequantizeTensor(5551, YNN_INVALID_VALUE_ID, 5552, 5553);
  g->QuantizeTensor(5553, 8727, 5555, 1116);
  g->Dequantize(1116, 1117, 0.0216535534709692, 0);
  g->Transpose(8976, 5562, {1,0});
  g->Binary(ynn_binary_multiply, 5554, 5561, 5559);
  g->Dot(1115, 5562, YNN_INVALID_VALUE_ID, 5558, 1);
  g->DequantizeTensor(5558, YNN_INVALID_VALUE_ID, 5559, 5560);
  g->QuantizeTensor(5560, 8727, 5555, 1118);
  g->Dequantize(1118, 1119, 0.0216535534709692, 0);
  g->Polynomial(1119, 7583, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7583, 7584);
  g->Binary(ynn_binary_add, 7584, 7293, 7581);
  g->Binary(ynn_binary_multiply, 1119, 7305, 7582);
  g->Binary(ynn_binary_multiply, 7582, 7581, 1120);
  g->Binary(ynn_binary_multiply, 1117, 1120, 1121);
  g->Quantize(1121, 1122, 0.02472933940589428, 0);
  g->Transpose(8975, 5568, {1,0});
  g->Binary(ynn_binary_multiply, 5547, 5567, 5564);
  g->Dot(1122, 5568, YNN_INVALID_VALUE_ID, 5563, 1);
  g->DequantizeTensor(5563, YNN_INVALID_VALUE_ID, 5564, 5565);
  g->QuantizeTensor(5565, 8727, 5566, 1123);
  g->Dequantize(1123, 1125, 0.01883137971162796, 0);
  g->Unary(ynn_unary_square, 1125, 1126);
  g->Reduce(ynn_reduce_sum, 1126, 7586, {2}, true);
  g->ShapeProduct(1126, 7585, {2});
  g->Binary(ynn_binary_divide, 7586, 7585, 1127);
  g->Binary(ynn_binary_add, 1127, 8779, 1128);
  g->Unary(ynn_unary_rsqrt, 1128, 1129);
  g->Binary(ynn_binary_multiply, 1125, 1129, 1130);
  g->Binary(ynn_binary_multiply, 1130, 8981, 1131);
  g->Binary(ynn_binary_add, 1131, 1107, 1132);
}

// Scope: "Layer14 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(429, 1133, {0,0,14,0}, {-1,-1,1,-1});
  g->Reshape(1133, 1134, {1,1,256});
  g->Unary(ynn_unary_square, 1134, 1136);
  g->Reduce(ynn_reduce_sum, 1136, 7588, {2}, true);
  g->ShapeProduct(1136, 7587, {2});
  g->Binary(ynn_binary_divide, 7588, 7587, 1137);
  g->Binary(ynn_binary_add, 1137, 8779, 1138);
  g->Unary(ynn_unary_rsqrt, 1138, 1139);
  g->Binary(ynn_binary_multiply, 1134, 1139, 1140);
  g->Binary(ynn_binary_multiply, 1140, 9533, 1141);
  g->Binary(ynn_binary_multiply, 9540, 8783, 1142);
  g->Binary(ynn_binary_add, 1141, 1142, 1143);
  g->Binary(ynn_binary_multiply, 1143, 8777, 1144);
  g->Quantize(1132, 1145, 0.37186482548713684, 0);
  g->Transpose(8978, 5575, {1,0});
  g->Binary(ynn_binary_multiply, 5572, 5574, 5570);
  g->Dot(1145, 5575, YNN_INVALID_VALUE_ID, 5569, 1);
  g->DequantizeTensor(5569, YNN_INVALID_VALUE_ID, 5570, 5571);
  g->QuantizeTensor(5571, 8727, 5573, 1147);
  g->Dequantize(1147, 1148, 0.060531508177518845, 0);
  g->Polynomial(1148, 7591, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7591, 7592);
  g->Binary(ynn_binary_add, 7592, 7293, 7589);
  g->Binary(ynn_binary_multiply, 1148, 7305, 7590);
  g->Binary(ynn_binary_multiply, 7590, 7589, 1149);
  g->Binary(ynn_binary_multiply, 1149, 1144, 1150);
  g->Quantize(1150, 1151, 0.3523622155189514, 0);
  g->Transpose(8979, 5582, {1,0});
  g->Binary(ynn_binary_multiply, 5579, 5581, 5577);
  g->Dot(1151, 5582, YNN_INVALID_VALUE_ID, 5576, 1);
  g->DequantizeTensor(5576, YNN_INVALID_VALUE_ID, 5577, 5578);
  g->QuantizeTensor(5578, 8727, 5580, 1152);
  g->Dequantize(1152, 1153, 0.08160637319087982, 0);
  g->Unary(ynn_unary_square, 1153, 1154);
  g->Reduce(ynn_reduce_sum, 1154, 7594, {2}, true);
  g->ShapeProduct(1154, 7593, {2});
  g->Binary(ynn_binary_divide, 7594, 7593, 1155);
  g->Binary(ynn_binary_add, 1155, 8779, 1156);
  g->Unary(ynn_unary_rsqrt, 1156, 1158);
  g->Binary(ynn_binary_multiply, 1153, 1158, 1159);
  g->Binary(ynn_binary_multiply, 1159, 8982, 1160);
  g->Binary(ynn_binary_add, 1132, 1160, 1161);
  g->Binary(ynn_binary_multiply, 1161, 8974, 1162);
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
  g->Quantize(1169, 1170, 0.11677385866641998, 0);
  g->Transpose(9002, 5589, {1,0});
  g->Binary(ynn_binary_multiply, 5586, 5588, 5584);
  g->Dot(1170, 5589, YNN_INVALID_VALUE_ID, 5583, 1);
  g->DequantizeTensor(5583, YNN_INVALID_VALUE_ID, 5584, 5585);
  g->QuantizeTensor(5585, 8727, 5587, 1171);
  g->Dequantize(1171, 1172, 0.18897639214992523, 0);
  g->SplitDim(1172, 1173, 2, {2,256});
  g->FuseDims(1173, 1175, 1, 2);
  g->SplitDim(1175, 1174, 1, {2,1});
  g->Unary(ynn_unary_square, 1174, 1176);
  g->Reduce(ynn_reduce_sum, 1176, 7598, {3}, true);
  g->ShapeProduct(1176, 7597, {3});
  g->Binary(ynn_binary_divide, 7598, 7597, 1177);
  g->Binary(ynn_binary_add, 1177, 8779, 1178);
  g->Unary(ynn_unary_rsqrt, 1178, 1179);
  g->Binary(ynn_binary_multiply, 1174, 1179, 1182);
  g->Binary(ynn_binary_multiply, 1182, 9001, 1183);
  g->Slice(1183, 1184, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1183, 1185, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1185, 1186);
  g->Concat({1186,1184}, 1187, 3);
  g->Binary(ynn_binary_multiply, 1183, 3231, 1188);
  g->Binary(ynn_binary_multiply, 1187, 4329, 1189);
  g->Binary(ynn_binary_add, 1188, 1189, 1190);
  g->Transpose(9006, 5594, {1,0});
  g->Binary(ynn_binary_multiply, 5586, 5593, 5591);
  g->Dot(1170, 5594, YNN_INVALID_VALUE_ID, 5590, 1);
  g->DequantizeTensor(5590, YNN_INVALID_VALUE_ID, 5591, 5592);
  g->QuantizeTensor(5592, 8727, 5587, 1192);
  g->Dequantize(1192, 1193, 0.18897639214992523, 0);
  g->SplitDim(1193, 1194, 2, {2,256});
  g->FuseDims(1194, 1196, 1, 2);
  g->SplitDim(1196, 1195, 1, {2,1});
  g->Unary(ynn_unary_square, 1195, 1197);
  g->Reduce(ynn_reduce_sum, 1197, 7600, {3}, true);
  g->ShapeProduct(1197, 7599, {3});
  g->Binary(ynn_binary_divide, 7600, 7599, 1198);
  g->Binary(ynn_binary_add, 1198, 8779, 1199);
  g->Unary(ynn_unary_rsqrt, 1199, 1200);
  g->Binary(ynn_binary_multiply, 1195, 1200, 1201);
}

// Scope: "Layer15 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(1190, 1202, 0.005989333149045706, 0);
  g->Append(8735, 1202, 9584, 2, s2, slinky::expr(int64_t{1}));
  g->View(9584, 9632, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(1201, 1204, 0.047244105488061905, 0);
  g->Append(8759, 1204, 9608, 2, s2, slinky::expr(int64_t{1}));
  g->View(9608, 9656, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer15 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(9005, 5600, {1,0});
  g->Binary(ynn_binary_multiply, 5586, 5599, 5596);
  g->Dot(1170, 5600, YNN_INVALID_VALUE_ID, 5595, 1);
  g->DequantizeTensor(5595, YNN_INVALID_VALUE_ID, 5596, 5597);
  g->QuantizeTensor(5597, 8727, 5598, 1205);
  g->Dequantize(1205, 1206, 0.211614191532135, 0);
  g->SplitDim(1206, 1207, 2, {8,256});
  g->FuseDims(1207, 1209, 1, 2);
  g->SplitDim(1209, 1208, 1, {8,1});
  g->Unary(ynn_unary_square, 1208, 1211);
  g->Reduce(ynn_reduce_sum, 1211, 7602, {3}, true);
  g->ShapeProduct(1211, 7601, {3});
  g->Binary(ynn_binary_divide, 7602, 7601, 1212);
  g->Binary(ynn_binary_add, 1212, 8779, 1213);
  g->Unary(ynn_unary_rsqrt, 1213, 1214);
  g->Binary(ynn_binary_multiply, 1208, 1214, 1215);
  g->Binary(ynn_binary_multiply, 1215, 9004, 1216);
  g->Slice(1216, 1217, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1216, 1218, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1218, 1219);
  g->Concat({1219,1217}, 1220, 3);
  g->Binary(ynn_binary_multiply, 1216, 3231, 1222);
  g->Binary(ynn_binary_multiply, 1220, 4329, 1223);
  g->Binary(ynn_binary_add, 1222, 1223, 1224);
}

// Scope: "Layer15 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9632, 1225, 0.005989333149045706, 0);
  g->Dequantize(9656, 1226, 0.047244105488061905, 0);
  g->Slice(1224, 1227, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(1225, 1228, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(1226, 1229, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(1227, 1228, 1230, false, true);
  g->Mask(1230, 8798, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8798, 7606, {-1}, true);
  g->Binary(ynn_binary_subtract, 8798, 7606, 7603);
  g->Unary(ynn_unary_exp, 7603, 7604);
  g->Reduce(ynn_reduce_sum, 7604, 7607, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 7607, 7605);
  g->Binary(ynn_binary_multiply, 7604, 7605, 1232);
  g->Matmul(1232, 1229, 1233, false, false);
  g->Slice(1224, 1234, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(1225, 1235, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(1226, 1236, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(1234, 1235, 1237, false, true);
  g->Mask(1237, 8799, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8799, 7611, {-1}, true);
  g->Binary(ynn_binary_subtract, 8799, 7611, 7608);
  g->Unary(ynn_unary_exp, 7608, 7609);
  g->Reduce(ynn_reduce_sum, 7609, 7612, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 7612, 7610);
  g->Binary(ynn_binary_multiply, 7609, 7610, 1238);
  g->Matmul(1238, 1236, 1239, false, false);
  g->Concat({1233,1239}, 1240, 1);
}

// Scope: "Layer15 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(1240, 1243, 1, 2);
  g->SplitDim(1243, 1242, 1, {1,8});
  g->FuseDims(1242, 1244, 2, 2);
  g->Quantize(1244, 1245, 0.02706693857908249, 0);
  g->Transpose(9003, 5607, {1,0});
  g->Binary(ynn_binary_multiply, 5604, 5606, 5602);
  g->Dot(1245, 5607, YNN_INVALID_VALUE_ID, 5601, 1);
  g->DequantizeTensor(5601, YNN_INVALID_VALUE_ID, 5602, 5603);
  g->QuantizeTensor(5603, 8727, 5605, 1246);
  g->Dequantize(1246, 1247, 0.06876781582832336, 0);
}

// Scope: "Layer15 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1162, 1163);
  g->Reduce(ynn_reduce_sum, 1163, 7596, {2}, true);
  g->ShapeProduct(1163, 7595, {2});
  g->Binary(ynn_binary_divide, 7596, 7595, 1164);
  g->Binary(ynn_binary_add, 1164, 8779, 1165);
  g->Unary(ynn_unary_rsqrt, 1165, 1166);
  g->Binary(ynn_binary_multiply, 1162, 1166, 1167);
  g->Binary(ynn_binary_multiply, 1167, 8990, 1169);
  BuildLayer15AttentionKvProjection(ctx);
  BuildLayer15AttentionCacheUpdate(ctx);
  BuildLayer15AttentionQueryProjection(ctx);
  BuildLayer15AttentionSdpa(ctx);
  BuildLayer15AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1247, 1248);
  g->Reduce(ynn_reduce_sum, 1248, 7614, {2}, true);
  g->ShapeProduct(1248, 7613, {2});
  g->Binary(ynn_binary_divide, 7614, 7613, 1249);
  g->Binary(ynn_binary_add, 1249, 8779, 1250);
  g->Unary(ynn_unary_rsqrt, 1250, 1251);
  g->Binary(ynn_binary_multiply, 1247, 1251, 1252);
  g->Binary(ynn_binary_multiply, 1252, 8997, 1253);
  g->Binary(ynn_binary_add, 1253, 1162, 1254);
}

// Scope: "Layer15 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1254, 1255);
  g->Reduce(ynn_reduce_sum, 1255, 7616, {2}, true);
  g->ShapeProduct(1255, 7615, {2});
  g->Binary(ynn_binary_divide, 7616, 7615, 1256);
  g->Binary(ynn_binary_add, 1256, 8779, 1257);
  g->Unary(ynn_unary_rsqrt, 1257, 1258);
  g->Binary(ynn_binary_multiply, 1254, 1258, 1259);
  g->Binary(ynn_binary_multiply, 1259, 9000, 1260);
  g->Quantize(1260, 1261, 0.01503660250455141, 0);
  g->Transpose(8994, 5614, {1,0});
  g->Binary(ynn_binary_multiply, 5611, 5613, 5609);
  g->Dot(1261, 5614, YNN_INVALID_VALUE_ID, 5608, 1);
  g->DequantizeTensor(5608, YNN_INVALID_VALUE_ID, 5609, 5610);
  g->QuantizeTensor(5610, 8727, 5612, 1262);
  g->Dequantize(1262, 1264, 0.020300205796957016, 0);
  g->Transpose(8993, 5619, {1,0});
  g->Binary(ynn_binary_multiply, 5611, 5618, 5616);
  g->Dot(1261, 5619, YNN_INVALID_VALUE_ID, 5615, 1);
  g->DequantizeTensor(5615, YNN_INVALID_VALUE_ID, 5616, 5617);
  g->QuantizeTensor(5617, 8727, 5612, 1265);
  g->Dequantize(1265, 1266, 0.020300205796957016, 0);
  g->Polynomial(1266, 7624, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7624, 7625);
  g->Binary(ynn_binary_add, 7625, 7293, 7622);
  g->Binary(ynn_binary_multiply, 1266, 7305, 7623);
  g->Binary(ynn_binary_multiply, 7623, 7622, 1267);
  g->Binary(ynn_binary_multiply, 1264, 1267, 1268);
  g->Quantize(1268, 1269, 0.018700797110795975, 0);
  g->Transpose(8992, 5626, {1,0});
  g->Binary(ynn_binary_multiply, 5623, 5625, 5621);
  g->Dot(1269, 5626, YNN_INVALID_VALUE_ID, 5620, 1);
  g->DequantizeTensor(5620, YNN_INVALID_VALUE_ID, 5621, 5622);
  g->QuantizeTensor(5622, 8727, 5624, 1270);
  g->Dequantize(1270, 1271, 0.01157078705728054, 0);
  g->Unary(ynn_unary_square, 1271, 1272);
  g->Reduce(ynn_reduce_sum, 1272, 7627, {2}, true);
  g->ShapeProduct(1272, 7626, {2});
  g->Binary(ynn_binary_divide, 7627, 7626, 1274);
  g->Binary(ynn_binary_add, 1274, 8779, 1275);
  g->Unary(ynn_unary_rsqrt, 1275, 1276);
  g->Binary(ynn_binary_multiply, 1271, 1276, 1277);
  g->Binary(ynn_binary_multiply, 1277, 8998, 1278);
  g->Binary(ynn_binary_add, 1278, 1254, 1279);
}

// Scope: "Layer15 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(429, 1280, {0,0,15,0}, {-1,-1,1,-1});
  g->Reshape(1280, 1281, {1,1,256});
  g->Unary(ynn_unary_square, 1281, 1282);
  g->Reduce(ynn_reduce_sum, 1282, 7629, {2}, true);
  g->ShapeProduct(1282, 7628, {2});
  g->Binary(ynn_binary_divide, 7629, 7628, 1283);
  g->Binary(ynn_binary_add, 1283, 8779, 1286);
  g->Unary(ynn_unary_rsqrt, 1286, 1287);
  g->Binary(ynn_binary_multiply, 1281, 1287, 1288);
  g->Binary(ynn_binary_multiply, 1288, 9533, 1289);
  g->Binary(ynn_binary_multiply, 9541, 8783, 1290);
  g->Binary(ynn_binary_add, 1289, 1290, 1291);
  g->Binary(ynn_binary_multiply, 1291, 8777, 1292);
  g->Quantize(1279, 1293, 0.40425750613212585, 0);
  g->Transpose(8995, 5640, {1,0});
  g->Binary(ynn_binary_multiply, 5637, 5639, 5635);
  g->Dot(1293, 5640, YNN_INVALID_VALUE_ID, 5634, 1);
  g->DequantizeTensor(5634, YNN_INVALID_VALUE_ID, 5635, 5636);
  g->QuantizeTensor(5636, 8727, 5638, 1294);
  g->Dequantize(1294, 1295, 0.10088583081960678, 0);
  g->Polynomial(1295, 7632, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7632, 7633);
  g->Binary(ynn_binary_add, 7633, 7293, 7630);
  g->Binary(ynn_binary_multiply, 1295, 7305, 7631);
  g->Binary(ynn_binary_multiply, 7631, 7630, 1297);
  g->Binary(ynn_binary_multiply, 1297, 1292, 1298);
  g->Quantize(1298, 1299, 0.748031497001648, 0);
  g->Transpose(8996, 5647, {1,0});
  g->Binary(ynn_binary_multiply, 5644, 5646, 5642);
  g->Dot(1299, 5647, YNN_INVALID_VALUE_ID, 5641, 1);
  g->DequantizeTensor(5641, YNN_INVALID_VALUE_ID, 5642, 5643);
  g->QuantizeTensor(5643, 8727, 5645, 1300);
  g->Dequantize(1300, 1301, 0.20252664387226105, 0);
  g->Unary(ynn_unary_square, 1301, 1302);
  g->Reduce(ynn_reduce_sum, 1302, 7635, {2}, true);
  g->ShapeProduct(1302, 7634, {2});
  g->Binary(ynn_binary_divide, 7635, 7634, 1303);
  g->Binary(ynn_binary_add, 1303, 8779, 1304);
  g->Unary(ynn_unary_rsqrt, 1304, 1305);
  g->Binary(ynn_binary_multiply, 1301, 1305, 1306);
  g->Binary(ynn_binary_multiply, 1306, 8999, 1308);
  g->Binary(ynn_binary_add, 1279, 1308, 1309);
  g->Binary(ynn_binary_multiply, 1309, 8991, 1310);
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
  g->Quantize(1316, 1317, 0.14304621517658234, 0);
  g->Transpose(9019, 5654, {1,0});
  g->Binary(ynn_binary_multiply, 5651, 5653, 5649);
  g->Dot(1317, 5654, YNN_INVALID_VALUE_ID, 5648, 1);
  g->DequantizeTensor(5648, YNN_INVALID_VALUE_ID, 5649, 5650);
  g->QuantizeTensor(5650, 8727, 5652, 1319);
  g->Dequantize(1319, 1320, 0.16535434126853943, 0);
  g->SplitDim(1320, 1321, 2, {2,256});
  g->FuseDims(1321, 1323, 1, 2);
  g->SplitDim(1323, 1322, 1, {2,1});
  g->Unary(ynn_unary_square, 1322, 1324);
  g->Reduce(ynn_reduce_sum, 1324, 7639, {3}, true);
  g->ShapeProduct(1324, 7638, {3});
  g->Binary(ynn_binary_divide, 7639, 7638, 1325);
  g->Binary(ynn_binary_add, 1325, 8779, 1326);
  g->Unary(ynn_unary_rsqrt, 1326, 1327);
  g->Binary(ynn_binary_multiply, 1322, 1327, 1328);
  g->Binary(ynn_binary_multiply, 1328, 9018, 1329);
  g->Slice(1329, 1330, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1329, 1331, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1331, 1332);
  g->Concat({1332,1330}, 1333, 3);
  g->Binary(ynn_binary_multiply, 1329, 3231, 1334);
  g->Binary(ynn_binary_multiply, 1333, 4329, 1335);
  g->Binary(ynn_binary_add, 1334, 1335, 1336);
  g->Transpose(9023, 5659, {1,0});
  g->Binary(ynn_binary_multiply, 5651, 5658, 5656);
  g->Dot(1317, 5659, YNN_INVALID_VALUE_ID, 5655, 1);
  g->DequantizeTensor(5655, YNN_INVALID_VALUE_ID, 5656, 5657);
  g->QuantizeTensor(5657, 8727, 5652, 1337);
  g->Dequantize(1337, 1338, 0.16535434126853943, 0);
  g->SplitDim(1338, 1340, 2, {2,256});
  g->FuseDims(1340, 1342, 1, 2);
  g->SplitDim(1342, 1341, 1, {2,1});
  g->Unary(ynn_unary_square, 1341, 1343);
  g->Reduce(ynn_reduce_sum, 1343, 7646, {3}, true);
  g->ShapeProduct(1343, 7645, {3});
  g->Binary(ynn_binary_divide, 7646, 7645, 1344);
  g->Binary(ynn_binary_add, 1344, 8779, 1345);
  g->Unary(ynn_unary_rsqrt, 1345, 1346);
  g->Binary(ynn_binary_multiply, 1341, 1346, 1347);
}

// Scope: "Layer16 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(1336, 1348, 0.005929071456193924, 0);
  g->Append(8736, 1348, 9585, 2, s2, slinky::expr(int64_t{1}));
  g->View(9585, 9633, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(1347, 1350, 0.047244105488061905, 0);
  g->Append(8760, 1350, 9609, 2, s2, slinky::expr(int64_t{1}));
  g->View(9609, 9657, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer16 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(9022, 5665, {1,0});
  g->Binary(ynn_binary_multiply, 5651, 5664, 5661);
  g->Dot(1317, 5665, YNN_INVALID_VALUE_ID, 5660, 1);
  g->DequantizeTensor(5660, YNN_INVALID_VALUE_ID, 5661, 5662);
  g->QuantizeTensor(5662, 8727, 5663, 1351);
  g->Dequantize(1351, 1352, 0.1761811226606369, 0);
  g->SplitDim(1352, 1353, 2, {8,256});
  g->FuseDims(1353, 1355, 1, 2);
  g->SplitDim(1355, 1354, 1, {8,1});
  g->Unary(ynn_unary_square, 1354, 1356);
  g->Reduce(ynn_reduce_sum, 1356, 7648, {3}, true);
  g->ShapeProduct(1356, 7647, {3});
  g->Binary(ynn_binary_divide, 7648, 7647, 1357);
  g->Binary(ynn_binary_add, 1357, 8779, 1359);
  g->Unary(ynn_unary_rsqrt, 1359, 1360);
  g->Binary(ynn_binary_multiply, 1354, 1360, 1361);
  g->Binary(ynn_binary_multiply, 1361, 9021, 1362);
  g->Slice(1362, 1363, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1362, 1364, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1364, 1365);
  g->Concat({1365,1363}, 1366, 3);
  g->Binary(ynn_binary_multiply, 1362, 3231, 1367);
  g->Binary(ynn_binary_multiply, 1366, 4329, 1368);
  g->Binary(ynn_binary_add, 1367, 1368, 1371);
}

// Scope: "Layer16 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9633, 1372, 0.005929071456193924, 0);
  g->Dequantize(9657, 1373, 0.047244105488061905, 0);
  g->Slice(1371, 1374, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(1372, 1375, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(1373, 1376, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(1374, 1375, 1377, false, true);
  g->Mask(1377, 8800, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8800, 7652, {-1}, true);
  g->Binary(ynn_binary_subtract, 8800, 7652, 7649);
  g->Unary(ynn_unary_exp, 7649, 7650);
  g->Reduce(ynn_reduce_sum, 7650, 7653, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 7653, 7651);
  g->Binary(ynn_binary_multiply, 7650, 7651, 1378);
  g->Matmul(1378, 1376, 1379, false, false);
  g->Slice(1371, 1381, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(1372, 1382, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(1373, 1383, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(1381, 1382, 1384, false, true);
  g->Mask(1384, 8801, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8801, 7657, {-1}, true);
  g->Binary(ynn_binary_subtract, 8801, 7657, 7654);
  g->Unary(ynn_unary_exp, 7654, 7655);
  g->Reduce(ynn_reduce_sum, 7655, 7658, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 7658, 7656);
  g->Binary(ynn_binary_multiply, 7655, 7656, 1385);
  g->Matmul(1385, 1383, 1386, false, false);
  g->Concat({1379,1386}, 1387, 1);
}

// Scope: "Layer16 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(1387, 1389, 1, 2);
  g->SplitDim(1389, 1388, 1, {1,8});
  g->FuseDims(1388, 1390, 2, 2);
  g->Quantize(1390, 1393, 0.025221465155482292, 0);
  g->Transpose(9020, 5672, {1,0});
  g->Binary(ynn_binary_multiply, 5669, 5671, 5667);
  g->Dot(1393, 5672, YNN_INVALID_VALUE_ID, 5666, 1);
  g->DequantizeTensor(5666, YNN_INVALID_VALUE_ID, 5667, 5668);
  g->QuantizeTensor(5668, 8727, 5670, 1394);
  g->Dequantize(1394, 1395, 0.03670656308531761, 0);
}

// Scope: "Layer16 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1310, 1311);
  g->Reduce(ynn_reduce_sum, 1311, 7637, {2}, true);
  g->ShapeProduct(1311, 7636, {2});
  g->Binary(ynn_binary_divide, 7637, 7636, 1312);
  g->Binary(ynn_binary_add, 1312, 8779, 1313);
  g->Unary(ynn_unary_rsqrt, 1313, 1314);
  g->Binary(ynn_binary_multiply, 1310, 1314, 1315);
  g->Binary(ynn_binary_multiply, 1315, 9007, 1316);
  BuildLayer16AttentionKvProjection(ctx);
  BuildLayer16AttentionCacheUpdate(ctx);
  BuildLayer16AttentionQueryProjection(ctx);
  BuildLayer16AttentionSdpa(ctx);
  BuildLayer16AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1395, 1396);
  g->Reduce(ynn_reduce_sum, 1396, 7660, {2}, true);
  g->ShapeProduct(1396, 7659, {2});
  g->Binary(ynn_binary_divide, 7660, 7659, 1397);
  g->Binary(ynn_binary_add, 1397, 8779, 1398);
  g->Unary(ynn_unary_rsqrt, 1398, 1399);
  g->Binary(ynn_binary_multiply, 1395, 1399, 1400);
  g->Binary(ynn_binary_multiply, 1400, 9014, 1401);
  g->Binary(ynn_binary_add, 1401, 1310, 1402);
}

// Scope: "Layer16 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1402, 1404);
  g->Reduce(ynn_reduce_sum, 1404, 7662, {2}, true);
  g->ShapeProduct(1404, 7661, {2});
  g->Binary(ynn_binary_divide, 7662, 7661, 1405);
  g->Binary(ynn_binary_add, 1405, 8779, 1406);
  g->Unary(ynn_unary_rsqrt, 1406, 1407);
  g->Binary(ynn_binary_multiply, 1402, 1407, 1408);
  g->Binary(ynn_binary_multiply, 1408, 9017, 1409);
  g->Quantize(1409, 1410, 0.013054176233708858, 0);
  g->Transpose(9011, 5686, {1,0});
  g->Binary(ynn_binary_multiply, 5683, 5685, 5681);
  g->Dot(1410, 5686, YNN_INVALID_VALUE_ID, 5680, 1);
  g->DequantizeTensor(5680, YNN_INVALID_VALUE_ID, 5681, 5682);
  g->QuantizeTensor(5682, 8727, 5684, 1411);
  g->Dequantize(1411, 1412, 0.01464075781404972, 0);
  g->Transpose(9010, 5691, {1,0});
  g->Binary(ynn_binary_multiply, 5683, 5690, 5688);
  g->Dot(1410, 5691, YNN_INVALID_VALUE_ID, 5687, 1);
  g->DequantizeTensor(5687, YNN_INVALID_VALUE_ID, 5688, 5689);
  g->QuantizeTensor(5689, 8727, 5684, 1414);
  g->Dequantize(1414, 1415, 0.01464075781404972, 0);
  g->Polynomial(1415, 7665, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7665, 7666);
  g->Binary(ynn_binary_add, 7666, 7293, 7663);
  g->Binary(ynn_binary_multiply, 1415, 7305, 7664);
  g->Binary(ynn_binary_multiply, 7664, 7663, 1416);
  g->Binary(ynn_binary_multiply, 1412, 1416, 1417);
  g->Quantize(1417, 1418, 0.010150108486413956, 0);
  g->Transpose(9009, 5698, {1,0});
  g->Binary(ynn_binary_multiply, 5695, 5697, 5693);
  g->Dot(1418, 5698, YNN_INVALID_VALUE_ID, 5692, 1);
  g->DequantizeTensor(5692, YNN_INVALID_VALUE_ID, 5693, 5694);
  g->QuantizeTensor(5694, 8727, 5696, 1419);
  g->Dequantize(1419, 1420, 0.006600875407457352, 0);
  g->Unary(ynn_unary_square, 1420, 1421);
  g->Reduce(ynn_reduce_sum, 1421, 7668, {2}, true);
  g->ShapeProduct(1421, 7667, {2});
  g->Binary(ynn_binary_divide, 7668, 7667, 1422);
  g->Binary(ynn_binary_add, 1422, 8779, 1423);
  g->Unary(ynn_unary_rsqrt, 1423, 1425);
  g->Binary(ynn_binary_multiply, 1420, 1425, 1426);
  g->Binary(ynn_binary_multiply, 1426, 9015, 1427);
  g->Binary(ynn_binary_add, 1427, 1402, 1428);
}

// Scope: "Layer16 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(429, 1429, {0,0,16,0}, {-1,-1,1,-1});
  g->Reshape(1429, 1430, {1,1,256});
  g->Unary(ynn_unary_square, 1430, 1431);
  g->Reduce(ynn_reduce_sum, 1431, 7670, {2}, true);
  g->ShapeProduct(1431, 7669, {2});
  g->Binary(ynn_binary_divide, 7670, 7669, 1432);
  g->Binary(ynn_binary_add, 1432, 8779, 1433);
  g->Unary(ynn_unary_rsqrt, 1433, 1434);
  g->Binary(ynn_binary_multiply, 1430, 1434, 1436);
  g->Binary(ynn_binary_multiply, 1436, 9533, 1437);
  g->Binary(ynn_binary_multiply, 9542, 8783, 1438);
  g->Binary(ynn_binary_add, 1437, 1438, 1439);
  g->Binary(ynn_binary_multiply, 1439, 8777, 1440);
  g->Quantize(1428, 1441, 0.3792611062526703, 0);
  g->Transpose(9012, 5705, {1,0});
  g->Binary(ynn_binary_multiply, 5702, 5704, 5700);
  g->Dot(1441, 5705, YNN_INVALID_VALUE_ID, 5699, 1);
  g->DequantizeTensor(5699, YNN_INVALID_VALUE_ID, 5700, 5701);
  g->QuantizeTensor(5701, 8727, 5703, 1442);
  g->Dequantize(1442, 1443, 0.10433071851730347, 0);
  g->Polynomial(1443, 7675, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7675, 7676);
  g->Binary(ynn_binary_add, 7676, 7293, 7673);
  g->Binary(ynn_binary_multiply, 1443, 7305, 7674);
  g->Binary(ynn_binary_multiply, 7674, 7673, 1444);
  g->Binary(ynn_binary_multiply, 1444, 1440, 1445);
  g->Quantize(1445, 1447, 0.43897637724876404, 0);
  g->Transpose(9013, 5712, {1,0});
  g->Binary(ynn_binary_multiply, 5709, 5711, 5707);
  g->Dot(1447, 5712, YNN_INVALID_VALUE_ID, 5706, 1);
  g->DequantizeTensor(5706, YNN_INVALID_VALUE_ID, 5707, 5708);
  g->QuantizeTensor(5708, 8727, 5710, 1448);
  g->Dequantize(1448, 1449, 0.08895451575517654, 0);
  g->Unary(ynn_unary_square, 1449, 1450);
  g->Reduce(ynn_reduce_sum, 1450, 7678, {2}, true);
  g->ShapeProduct(1450, 7677, {2});
  g->Binary(ynn_binary_divide, 7678, 7677, 1451);
  g->Binary(ynn_binary_add, 1451, 8779, 1452);
  g->Unary(ynn_unary_rsqrt, 1452, 1453);
  g->Binary(ynn_binary_multiply, 1449, 1453, 1454);
  g->Binary(ynn_binary_multiply, 1454, 9016, 1455);
  g->Binary(ynn_binary_add, 1428, 1455, 1456);
  g->Binary(ynn_binary_multiply, 1456, 9008, 1458);
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
  g->Quantize(1464, 1465, 0.11633685231208801, 0);
  g->Transpose(9036, 5719, {1,0});
  g->Binary(ynn_binary_multiply, 5716, 5718, 5714);
  g->Dot(1465, 5719, YNN_INVALID_VALUE_ID, 5713, 1);
  g->DequantizeTensor(5713, YNN_INVALID_VALUE_ID, 5714, 5715);
  g->QuantizeTensor(5715, 8727, 5717, 1466);
  g->Dequantize(1466, 1467, 0.1210630014538765, 0);
  g->SplitDim(1467, 1469, 2, {2,512});
  g->FuseDims(1469, 1471, 1, 2);
  g->SplitDim(1471, 1470, 1, {2,1});
  g->Unary(ynn_unary_square, 1470, 1472);
  g->Reduce(ynn_reduce_sum, 1472, 7682, {3}, true);
  g->ShapeProduct(1472, 7681, {3});
  g->Binary(ynn_binary_divide, 7682, 7681, 1473);
  g->Binary(ynn_binary_add, 1473, 8779, 1474);
  g->Unary(ynn_unary_rsqrt, 1474, 1475);
  g->Binary(ynn_binary_multiply, 1470, 1475, 1476);
  g->Binary(ynn_binary_multiply, 1476, 9035, 1477);
  g->Slice(1477, 1478, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(1477, 1479, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 1479, 1481);
  g->Concat({1481,1478}, 1482, 3);
  g->Binary(ynn_binary_multiply, 1477, 4959, 1483);
  g->Binary(ynn_binary_multiply, 1482, 2, 1484);
  g->Binary(ynn_binary_add, 1483, 1484, 1485);
  g->Transpose(9040, 5724, {1,0});
  g->Binary(ynn_binary_multiply, 5716, 5723, 5721);
  g->Dot(1465, 5724, YNN_INVALID_VALUE_ID, 5720, 1);
  g->DequantizeTensor(5720, YNN_INVALID_VALUE_ID, 5721, 5722);
  g->QuantizeTensor(5722, 8727, 5717, 1486);
  g->Dequantize(1486, 1487, 0.1210630014538765, 0);
  g->SplitDim(1487, 1488, 2, {2,512});
  g->FuseDims(1488, 1490, 1, 2);
  g->SplitDim(1490, 1489, 1, {2,1});
  g->Unary(ynn_unary_square, 1489, 1492);
  g->Reduce(ynn_reduce_sum, 1492, 7684, {3}, true);
  g->ShapeProduct(1492, 7683, {3});
  g->Binary(ynn_binary_divide, 7684, 7683, 1493);
  g->Binary(ynn_binary_add, 1493, 8779, 1494);
  g->Unary(ynn_unary_rsqrt, 1494, 1495);
  g->Binary(ynn_binary_multiply, 1489, 1495, 1496);
}

// Scope: "Layer17 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(1485, 1497, 0.001110153621993959, 0);
  g->Append(8737, 1497, 9586, 2, s2, slinky::expr(int64_t{1}));
  g->View(9586, 9634, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(1496, 1498, 0.01785714365541935, 0);
  g->Append(8761, 1498, 9610, 2, s2, slinky::expr(int64_t{1}));
  g->View(9610, 9658, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer17 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(9039, 5730, {1,0});
  g->Binary(ynn_binary_multiply, 5716, 5729, 5726);
  g->Dot(1465, 5730, YNN_INVALID_VALUE_ID, 5725, 1);
  g->DequantizeTensor(5725, YNN_INVALID_VALUE_ID, 5726, 5727);
  g->QuantizeTensor(5727, 8727, 5728, 1501);
  g->Dequantize(1501, 1502, 0.17027559876441956, 0);
  g->SplitDim(1502, 1503, 2, {8,512});
  g->FuseDims(1503, 1505, 1, 2);
  g->SplitDim(1505, 1504, 1, {8,1});
  g->Unary(ynn_unary_square, 1504, 1506);
  g->Reduce(ynn_reduce_sum, 1506, 7686, {3}, true);
  g->ShapeProduct(1506, 7685, {3});
  g->Binary(ynn_binary_divide, 7686, 7685, 1507);
  g->Binary(ynn_binary_add, 1507, 8779, 1508);
  g->Unary(ynn_unary_rsqrt, 1508, 1509);
  g->Binary(ynn_binary_multiply, 1504, 1509, 1511);
  g->Binary(ynn_binary_multiply, 1511, 9038, 1512);
  g->Slice(1512, 1513, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(1512, 1514, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 1514, 1515);
  g->Concat({1515,1513}, 1516, 3);
  g->Binary(ynn_binary_multiply, 1512, 4959, 1517);
  g->Binary(ynn_binary_multiply, 1516, 2, 1518);
  g->Binary(ynn_binary_add, 1517, 1518, 1519);
}

// Scope: "Layer17 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9634, 1520, 0.001110153621993959, 0);
  g->Dequantize(9658, 1522, 0.01785714365541935, 0);
  g->Slice(1519, 1523, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(1520, 1524, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(1522, 1525, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(1523, 1524, 1526, false, true);
  g->Mask(1526, 8802, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 8802, 7692, {-1}, true);
  g->Binary(ynn_binary_subtract, 8802, 7692, 7689);
  g->Unary(ynn_unary_exp, 7689, 7690);
  g->Reduce(ynn_reduce_sum, 7690, 7693, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 7693, 7691);
  g->Binary(ynn_binary_multiply, 7690, 7691, 1527);
  g->Matmul(1527, 1525, 1528, false, false);
  g->Slice(1519, 1529, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(1520, 1530, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(1522, 1532, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(1529, 1530, 1533, false, true);
  g->Mask(1533, 8803, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 8803, 7697, {-1}, true);
  g->Binary(ynn_binary_subtract, 8803, 7697, 7694);
  g->Unary(ynn_unary_exp, 7694, 7695);
  g->Reduce(ynn_reduce_sum, 7695, 7698, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 7698, 7696);
  g->Binary(ynn_binary_multiply, 7695, 7696, 1534);
  g->Matmul(1534, 1532, 1535, false, false);
  g->Concat({1528,1535}, 1536, 1);
}

// Scope: "Layer17 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(1536, 1538, 1, 2);
  g->SplitDim(1538, 1537, 1, {1,8});
  g->FuseDims(1537, 1539, 2, 2);
  g->Quantize(1539, 1540, 0.01771654561161995, 0);
  g->Transpose(9037, 5737, {1,0});
  g->Binary(ynn_binary_multiply, 5734, 5736, 5732);
  g->Dot(1540, 5737, YNN_INVALID_VALUE_ID, 5731, 1);
  g->DequantizeTensor(5731, YNN_INVALID_VALUE_ID, 5732, 5733);
  g->QuantizeTensor(5733, 8727, 5735, 1541);
  g->Dequantize(1541, 1543, 0.025433415547013283, 0);
}

// Scope: "Layer17 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1458, 1459);
  g->Reduce(ynn_reduce_sum, 1459, 7680, {2}, true);
  g->ShapeProduct(1459, 7679, {2});
  g->Binary(ynn_binary_divide, 7680, 7679, 1460);
  g->Binary(ynn_binary_add, 1460, 8779, 1461);
  g->Unary(ynn_unary_rsqrt, 1461, 1462);
  g->Binary(ynn_binary_multiply, 1458, 1462, 1463);
  g->Binary(ynn_binary_multiply, 1463, 9024, 1464);
  BuildLayer17AttentionKvProjection(ctx);
  BuildLayer17AttentionCacheUpdate(ctx);
  BuildLayer17AttentionQueryProjection(ctx);
  BuildLayer17AttentionSdpa(ctx);
  BuildLayer17AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1543, 1544);
  g->Reduce(ynn_reduce_sum, 1544, 7700, {2}, true);
  g->ShapeProduct(1544, 7699, {2});
  g->Binary(ynn_binary_divide, 7700, 7699, 1545);
  g->Binary(ynn_binary_add, 1545, 8779, 1546);
  g->Unary(ynn_unary_rsqrt, 1546, 1547);
  g->Binary(ynn_binary_multiply, 1543, 1547, 1548);
  g->Binary(ynn_binary_multiply, 1548, 9031, 1549);
  g->Binary(ynn_binary_add, 1549, 1458, 1550);
}

// Scope: "Layer17 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1550, 1551);
  g->Reduce(ynn_reduce_sum, 1551, 7702, {2}, true);
  g->ShapeProduct(1551, 7701, {2});
  g->Binary(ynn_binary_divide, 7702, 7701, 1552);
  g->Binary(ynn_binary_add, 1552, 8779, 1554);
  g->Unary(ynn_unary_rsqrt, 1554, 1555);
  g->Binary(ynn_binary_multiply, 1550, 1555, 1556);
  g->Binary(ynn_binary_multiply, 1556, 9034, 1557);
  g->Quantize(1557, 1558, 0.010834499262273312, 0);
  g->Transpose(9028, 5744, {1,0});
  g->Binary(ynn_binary_multiply, 5741, 5743, 5739);
  g->Dot(1558, 5744, YNN_INVALID_VALUE_ID, 5738, 1);
  g->DequantizeTensor(5738, YNN_INVALID_VALUE_ID, 5739, 5740);
  g->QuantizeTensor(5740, 8727, 5742, 1559);
  g->Dequantize(1559, 1560, 0.012979833409190178, 0);
  g->Transpose(9027, 5749, {1,0});
  g->Binary(ynn_binary_multiply, 5741, 5748, 5746);
  g->Dot(1558, 5749, YNN_INVALID_VALUE_ID, 5745, 1);
  g->DequantizeTensor(5745, YNN_INVALID_VALUE_ID, 5746, 5747);
  g->QuantizeTensor(5747, 8727, 5742, 1561);
  g->Dequantize(1561, 1562, 0.012979833409190178, 0);
  g->Polynomial(1562, 7705, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7705, 7706);
  g->Binary(ynn_binary_add, 7706, 7293, 7703);
  g->Binary(ynn_binary_multiply, 1562, 7305, 7704);
  g->Binary(ynn_binary_multiply, 7704, 7703, 1564);
  g->Binary(ynn_binary_multiply, 1560, 1564, 1565);
  g->Quantize(1565, 1566, 0.005751732271164656, 0);
  g->Transpose(9026, 5756, {1,0});
  g->Binary(ynn_binary_multiply, 5753, 5755, 5751);
  g->Dot(1566, 5756, YNN_INVALID_VALUE_ID, 5750, 1);
  g->DequantizeTensor(5750, YNN_INVALID_VALUE_ID, 5751, 5752);
  g->QuantizeTensor(5752, 8727, 5754, 1567);
  g->Dequantize(1567, 1568, 0.0032109280582517385, 0);
  g->Unary(ynn_unary_square, 1568, 1569);
  g->Reduce(ynn_reduce_sum, 1569, 7708, {2}, true);
  g->ShapeProduct(1569, 7707, {2});
  g->Binary(ynn_binary_divide, 7708, 7707, 1570);
  g->Binary(ynn_binary_add, 1570, 8779, 1571);
  g->Unary(ynn_unary_rsqrt, 1571, 1572);
  g->Binary(ynn_binary_multiply, 1568, 1572, 1573);
  g->Binary(ynn_binary_multiply, 1573, 9032, 1575);
  g->Binary(ynn_binary_add, 1575, 1550, 1576);
}

// Scope: "Layer17 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(429, 1577, {0,0,17,0}, {-1,-1,1,-1});
  g->Reshape(1577, 1578, {1,1,256});
  g->Unary(ynn_unary_square, 1578, 1579);
  g->Reduce(ynn_reduce_sum, 1579, 7710, {2}, true);
  g->ShapeProduct(1579, 7709, {2});
  g->Binary(ynn_binary_divide, 7710, 7709, 1580);
  g->Binary(ynn_binary_add, 1580, 8779, 1581);
  g->Unary(ynn_unary_rsqrt, 1581, 1582);
  g->Binary(ynn_binary_multiply, 1578, 1582, 1583);
  g->Binary(ynn_binary_multiply, 1583, 9533, 1584);
  g->Binary(ynn_binary_multiply, 9543, 8783, 1586);
  g->Binary(ynn_binary_add, 1584, 1586, 1587);
  g->Binary(ynn_binary_multiply, 1587, 8777, 1588);
  g->Quantize(1576, 1589, 0.23138143122196198, 0);
  g->Transpose(9029, 5770, {1,0});
  g->Binary(ynn_binary_multiply, 5767, 5769, 5765);
  g->Dot(1589, 5770, YNN_INVALID_VALUE_ID, 5764, 1);
  g->DequantizeTensor(5764, YNN_INVALID_VALUE_ID, 5765, 5766);
  g->QuantizeTensor(5766, 8727, 5768, 1590);
  g->Dequantize(1590, 1591, 0.08070866763591766, 0);
  g->Polynomial(1591, 7713, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7713, 7714);
  g->Binary(ynn_binary_add, 7714, 7293, 7711);
  g->Binary(ynn_binary_multiply, 1591, 7305, 7712);
  g->Binary(ynn_binary_multiply, 7712, 7711, 1592);
  g->Binary(ynn_binary_multiply, 1592, 1588, 1593);
  g->Quantize(1593, 1594, 0.4606299102306366, 0);
  g->Transpose(9030, 5777, {1,0});
  g->Binary(ynn_binary_multiply, 5774, 5776, 5772);
  g->Dot(1594, 5777, YNN_INVALID_VALUE_ID, 5771, 1);
  g->DequantizeTensor(5771, YNN_INVALID_VALUE_ID, 5772, 5773);
  g->QuantizeTensor(5773, 8727, 5775, 1595);
  g->Dequantize(1595, 1596, 0.13702630996704102, 0);
  g->Unary(ynn_unary_square, 1596, 1597);
  g->Reduce(ynn_reduce_sum, 1597, 7716, {2}, true);
  g->ShapeProduct(1597, 7715, {2});
  g->Binary(ynn_binary_divide, 7716, 7715, 1598);
  g->Binary(ynn_binary_add, 1598, 8779, 1599);
  g->Unary(ynn_unary_rsqrt, 1599, 1600);
  g->Binary(ynn_binary_multiply, 1596, 1600, 1601);
  g->Binary(ynn_binary_multiply, 1601, 9033, 1602);
  g->Binary(ynn_binary_add, 1576, 1602, 1603);
  g->Binary(ynn_binary_multiply, 1603, 9025, 1604);
}

// Scope: "Layer17"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17(Context& ctx) {
  BuildLayer17Attention(ctx);
  BuildLayer17Mlp(ctx);
  BuildLayer17PerLayerEmbedding(ctx);
}

}  // namespace BuildGemma4DecodeSource
