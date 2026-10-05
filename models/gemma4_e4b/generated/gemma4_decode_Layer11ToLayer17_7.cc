// Generated YNNPACK builder; do not edit.
#include "gemma4_decode_builder.h"

namespace BuildGemma4DecodeSource {

// Scope: "Layer11 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(563, 564, 0.043663885444402695, 0);
  g->Transpose(8802, 5209, {1,0});
  g->Binary(ynn_binary_multiply, 5206, 5208, 5204);
  g->Dot(564, 5209, YNN_INVALID_VALUE_ID, 5203, 1);
  g->DequantizeTensor(5203, YNN_INVALID_VALUE_ID, 5204, 5205);
  g->QuantizeTensor(5205, 8595, 5207, 566);
  g->Dequantize(566, 567, 0.05019685998558998, 0);
  g->SplitDim(567, 568, 2, {2,512});
  g->Transpose(568, 569, {0,2,1,3});
  g->Unary(ynn_unary_square, 569, 570);
  g->Reduce(ynn_reduce_sum, 570, 7314, {3}, true);
  g->ShapeProduct(570, 7313, {3});
  g->Binary(ynn_binary_divide, 7314, 7313, 571);
  g->Binary(ynn_binary_add, 571, 8647, 572);
  g->Unary(ynn_unary_rsqrt, 572, 573);
  g->Binary(ynn_binary_multiply, 569, 573, 574);
  g->Binary(ynn_binary_multiply, 574, 8801, 575);
  g->Slice(575, 577, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(575, 578, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 578, 579);
  g->Concat({579,577}, 580, 3);
  g->Binary(ynn_binary_multiply, 575, 4830, 581);
  g->Binary(ynn_binary_multiply, 580, 2, 582);
  g->Binary(ynn_binary_add, 581, 582, 583);
  g->Transpose(8806, 5214, {1,0});
  g->Binary(ynn_binary_multiply, 5206, 5213, 5211);
  g->Dot(564, 5214, YNN_INVALID_VALUE_ID, 5210, 1);
  g->DequantizeTensor(5210, YNN_INVALID_VALUE_ID, 5211, 5212);
  g->QuantizeTensor(5212, 8595, 5207, 584);
  g->Dequantize(584, 585, 0.05019685998558998, 0);
  g->SplitDim(585, 587, 2, {2,512});
  g->Transpose(587, 588, {0,2,1,3});
  g->Unary(ynn_unary_square, 588, 589);
  g->Reduce(ynn_reduce_sum, 589, 7316, {3}, true);
  g->ShapeProduct(589, 7315, {3});
  g->Binary(ynn_binary_divide, 7316, 7315, 590);
  g->Binary(ynn_binary_add, 590, 8647, 591);
  g->Unary(ynn_unary_rsqrt, 591, 592);
  g->Binary(ynn_binary_multiply, 588, 592, 593);
}

// Scope: "Layer11 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(583, 594, 0.0011474735802039504, 0);
  g->Append(8599, 594, 9448, 2, s2, slinky::expr(int64_t{1}));
  g->View(9448, 9496, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(593, 596, 0.01785714365541935, 0);
  g->Append(8623, 596, 9472, 2, s2, slinky::expr(int64_t{1}));
  g->View(9472, 9520, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer11 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(8805, 5220, {1,0});
  g->Binary(ynn_binary_multiply, 5206, 5219, 5216);
  g->Dot(564, 5220, YNN_INVALID_VALUE_ID, 5215, 1);
  g->DequantizeTensor(5215, YNN_INVALID_VALUE_ID, 5216, 5217);
  g->QuantizeTensor(5217, 8595, 5218, 597);
  g->Dequantize(597, 598, 0.0664370134472847, 0);
  g->SplitDim(598, 599, 2, {8,512});
  g->Transpose(599, 600, {0,2,1,3});
  g->Unary(ynn_unary_square, 600, 601);
  g->Reduce(ynn_reduce_sum, 601, 7318, {3}, true);
  g->ShapeProduct(601, 7317, {3});
  g->Binary(ynn_binary_divide, 7318, 7317, 602);
  g->Binary(ynn_binary_add, 602, 8647, 604);
  g->Unary(ynn_unary_rsqrt, 604, 605);
  g->Binary(ynn_binary_multiply, 600, 605, 606);
  g->Binary(ynn_binary_multiply, 606, 8804, 607);
  g->Slice(607, 608, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(607, 609, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 609, 610);
  g->Concat({610,608}, 611, 3);
  g->Binary(ynn_binary_multiply, 607, 4830, 612);
  g->Binary(ynn_binary_multiply, 611, 2, 613);
  g->Binary(ynn_binary_add, 612, 613, 615);
}

// Scope: "Layer11 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9496, 616, 0.0011474735802039504, 0);
  g->Dequantize(9520, 617, 0.01785714365541935, 0);
  g->Slice(615, 618, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(616, 619, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(617, 620, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(618, 619, 621, false, true);
  g->Mask(621, 8658, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 8658, 7322, {-1}, true);
  g->Binary(ynn_binary_subtract, 8658, 7322, 7319);
  g->Unary(ynn_unary_exp, 7319, 7320);
  g->Reduce(ynn_reduce_sum, 7320, 7323, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 7323, 7321);
  g->Binary(ynn_binary_multiply, 7320, 7321, 622);
  g->Matmul(622, 620, 623, false, false);
  g->Slice(615, 626, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(616, 627, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(617, 628, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(626, 627, 629, false, true);
  g->Mask(629, 8659, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 8659, 7329, {-1}, true);
  g->Binary(ynn_binary_subtract, 8659, 7329, 7326);
  g->Unary(ynn_unary_exp, 7326, 7327);
  g->Reduce(ynn_reduce_sum, 7327, 7330, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 7330, 7328);
  g->Binary(ynn_binary_multiply, 7327, 7328, 630);
  g->Matmul(630, 628, 631, false, false);
  g->Concat({623,631}, 632, 1);
}

// Scope: "Layer11 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(632, 633, {0,2,1,3});
  g->FuseDims(633, 634, 2, 2);
  g->Quantize(634, 636, 0.016240166500210762, 0);
  g->Transpose(8803, 5234, {1,0});
  g->Binary(ynn_binary_multiply, 5231, 5233, 5229);
  g->Dot(636, 5234, YNN_INVALID_VALUE_ID, 5228, 1);
  g->DequantizeTensor(5228, YNN_INVALID_VALUE_ID, 5229, 5230);
  g->QuantizeTensor(5230, 8595, 5232, 637);
  g->Dequantize(637, 638, 0.13702435791492462, 0);
}

// Scope: "Layer11 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 557, 558);
  g->Reduce(ynn_reduce_sum, 558, 7310, {2}, true);
  g->ShapeProduct(558, 7309, {2});
  g->Binary(ynn_binary_divide, 7310, 7309, 559);
  g->Binary(ynn_binary_add, 559, 8647, 560);
  g->Unary(ynn_unary_rsqrt, 560, 561);
  g->Binary(ynn_binary_multiply, 557, 561, 562);
  g->Binary(ynn_binary_multiply, 562, 8790, 563);
  BuildLayer11AttentionKvProjection(ctx);
  BuildLayer11AttentionCacheUpdate(ctx);
  BuildLayer11AttentionQueryProjection(ctx);
  BuildLayer11AttentionSdpa(ctx);
  BuildLayer11AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 638, 639);
  g->Reduce(ynn_reduce_sum, 639, 7332, {2}, true);
  g->ShapeProduct(639, 7331, {2});
  g->Binary(ynn_binary_divide, 7332, 7331, 640);
  g->Binary(ynn_binary_add, 640, 8647, 641);
  g->Unary(ynn_unary_rsqrt, 641, 642);
  g->Binary(ynn_binary_multiply, 638, 642, 643);
  g->Binary(ynn_binary_multiply, 643, 8797, 644);
  g->Binary(ynn_binary_add, 644, 557, 645);
}

// Scope: "Layer11 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 645, 647);
  g->Reduce(ynn_reduce_sum, 647, 7334, {2}, true);
  g->ShapeProduct(647, 7333, {2});
  g->Binary(ynn_binary_divide, 7334, 7333, 648);
  g->Binary(ynn_binary_add, 648, 8647, 649);
  g->Unary(ynn_unary_rsqrt, 649, 650);
  g->Binary(ynn_binary_multiply, 645, 650, 651);
  g->Binary(ynn_binary_multiply, 651, 8800, 652);
  g->Quantize(652, 653, 0.023192334920167923, 0);
  g->Transpose(8794, 5241, {1,0});
  g->Binary(ynn_binary_multiply, 5238, 5240, 5236);
  g->Dot(653, 5241, YNN_INVALID_VALUE_ID, 5235, 1);
  g->DequantizeTensor(5235, YNN_INVALID_VALUE_ID, 5236, 5237);
  g->QuantizeTensor(5237, 8595, 5239, 654);
  g->Dequantize(654, 655, 0.03223426267504692, 0);
  g->Transpose(8793, 5246, {1,0});
  g->Binary(ynn_binary_multiply, 5238, 5245, 5243);
  g->Dot(653, 5246, YNN_INVALID_VALUE_ID, 5242, 1);
  g->DequantizeTensor(5242, YNN_INVALID_VALUE_ID, 5243, 5244);
  g->QuantizeTensor(5244, 8595, 5239, 657);
  g->Dequantize(657, 658, 0.03223426267504692, 0);
  g->Polynomial(658, 7337, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7337, 7338);
  g->Binary(ynn_binary_add, 7338, 7161, 7335);
  g->Binary(ynn_binary_multiply, 658, 7173, 7336);
  g->Binary(ynn_binary_multiply, 7336, 7335, 659);
  g->Binary(ynn_binary_multiply, 655, 659, 660);
  g->Quantize(660, 661, 0.07480315864086151, 0);
  g->Transpose(8792, 5253, {1,0});
  g->Binary(ynn_binary_multiply, 5250, 5252, 5248);
  g->Dot(661, 5253, YNN_INVALID_VALUE_ID, 5247, 1);
  g->DequantizeTensor(5247, YNN_INVALID_VALUE_ID, 5248, 5249);
  g->QuantizeTensor(5249, 8595, 5251, 662);
  g->Dequantize(662, 663, 0.03340588137507439, 0);
  g->Unary(ynn_unary_square, 663, 664);
  g->Reduce(ynn_reduce_sum, 664, 7340, {2}, true);
  g->ShapeProduct(664, 7339, {2});
  g->Binary(ynn_binary_divide, 7340, 7339, 665);
  g->Binary(ynn_binary_add, 665, 8647, 666);
  g->Unary(ynn_unary_rsqrt, 666, 668);
  g->Binary(ynn_binary_multiply, 663, 668, 669);
  g->Binary(ynn_binary_multiply, 669, 8798, 670);
  g->Binary(ynn_binary_add, 670, 645, 671);
}

// Scope: "Layer11 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 672, {0,0,11,0}, {-1,-1,1,-1});
  g->Reshape(672, 673, {1,1,256});
  g->Unary(ynn_unary_square, 673, 674);
  g->Reduce(ynn_reduce_sum, 674, 7342, {2}, true);
  g->ShapeProduct(674, 7341, {2});
  g->Binary(ynn_binary_divide, 7342, 7341, 675);
  g->Binary(ynn_binary_add, 675, 8647, 676);
  g->Unary(ynn_unary_rsqrt, 676, 677);
  g->Binary(ynn_binary_multiply, 673, 677, 679);
  g->Binary(ynn_binary_multiply, 679, 9401, 680);
  g->Binary(ynn_binary_multiply, 9405, 8651, 681);
  g->Binary(ynn_binary_add, 680, 681, 682);
  g->Binary(ynn_binary_multiply, 682, 8645, 683);
  g->Quantize(671, 684, 0.18839792907238007, 0);
  g->Transpose(8795, 5260, {1,0});
  g->Binary(ynn_binary_multiply, 5257, 5259, 5255);
  g->Dot(684, 5260, YNN_INVALID_VALUE_ID, 5254, 1);
  g->DequantizeTensor(5254, YNN_INVALID_VALUE_ID, 5255, 5256);
  g->QuantizeTensor(5256, 8595, 5258, 685);
  g->Dequantize(685, 686, 0.08759843558073044, 0);
  g->Polynomial(686, 7347, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7347, 7348);
  g->Binary(ynn_binary_add, 7348, 7161, 7345);
  g->Binary(ynn_binary_multiply, 686, 7173, 7346);
  g->Binary(ynn_binary_multiply, 7346, 7345, 687);
  g->Binary(ynn_binary_multiply, 687, 683, 688);
  g->Quantize(688, 690, 1.6850394010543823, 0);
  g->Transpose(8796, 5267, {1,0});
  g->Binary(ynn_binary_multiply, 5264, 5266, 5262);
  g->Dot(690, 5267, YNN_INVALID_VALUE_ID, 5261, 1);
  g->DequantizeTensor(5261, YNN_INVALID_VALUE_ID, 5262, 5263);
  g->QuantizeTensor(5263, 8595, 5265, 691);
  g->Dequantize(691, 692, 0.46903082728385925, 0);
  g->Unary(ynn_unary_square, 692, 693);
  g->Reduce(ynn_reduce_sum, 693, 7350, {2}, true);
  g->ShapeProduct(693, 7349, {2});
  g->Binary(ynn_binary_divide, 7350, 7349, 694);
  g->Binary(ynn_binary_add, 694, 8647, 695);
  g->Unary(ynn_unary_rsqrt, 695, 696);
  g->Binary(ynn_binary_multiply, 692, 696, 697);
  g->Binary(ynn_binary_multiply, 697, 8799, 698);
  g->Binary(ynn_binary_add, 671, 698, 699);
  g->Binary(ynn_binary_multiply, 699, 8791, 701);
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
  g->Quantize(707, 708, 0.11905524879693985, 0);
  g->Transpose(8819, 5274, {1,0});
  g->Binary(ynn_binary_multiply, 5271, 5273, 5269);
  g->Dot(708, 5274, YNN_INVALID_VALUE_ID, 5268, 1);
  g->DequantizeTensor(5268, YNN_INVALID_VALUE_ID, 5269, 5270);
  g->QuantizeTensor(5270, 8595, 5272, 709);
  g->Dequantize(709, 710, 0.2027559131383896, 0);
  g->SplitDim(710, 712, 2, {2,256});
  g->Transpose(712, 713, {0,2,1,3});
  g->Unary(ynn_unary_square, 713, 714);
  g->Reduce(ynn_reduce_sum, 714, 7354, {3}, true);
  g->ShapeProduct(714, 7353, {3});
  g->Binary(ynn_binary_divide, 7354, 7353, 715);
  g->Binary(ynn_binary_add, 715, 8647, 716);
  g->Unary(ynn_unary_rsqrt, 716, 717);
  g->Binary(ynn_binary_multiply, 713, 717, 718);
  g->Binary(ynn_binary_multiply, 718, 8818, 719);
  g->Slice(719, 720, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(719, 721, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 721, 723);
  g->Concat({723,720}, 724, 3);
  g->Binary(ynn_binary_multiply, 719, 3141, 725);
  g->Binary(ynn_binary_multiply, 724, 4217, 726);
  g->Binary(ynn_binary_add, 725, 726, 727);
  g->Transpose(8823, 5279, {1,0});
  g->Binary(ynn_binary_multiply, 5271, 5278, 5276);
  g->Dot(708, 5279, YNN_INVALID_VALUE_ID, 5275, 1);
  g->DequantizeTensor(5275, YNN_INVALID_VALUE_ID, 5276, 5277);
  g->QuantizeTensor(5277, 8595, 5272, 728);
  g->Dequantize(728, 729, 0.2027559131383896, 0);
  g->SplitDim(729, 730, 2, {2,256});
  g->Transpose(730, 731, {0,2,1,3});
  g->Unary(ynn_unary_square, 731, 734);
  g->Reduce(ynn_reduce_sum, 734, 7356, {3}, true);
  g->ShapeProduct(734, 7355, {3});
  g->Binary(ynn_binary_divide, 7356, 7355, 735);
  g->Binary(ynn_binary_add, 735, 8647, 736);
  g->Unary(ynn_unary_rsqrt, 736, 737);
  g->Binary(ynn_binary_multiply, 731, 737, 738);
}

// Scope: "Layer12 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(727, 739, 0.005684707313776016, 0);
  g->Append(8600, 739, 9449, 2, s2, slinky::expr(int64_t{1}));
  g->View(9449, 9497, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(738, 740, 0.047244105488061905, 0);
  g->Append(8624, 740, 9473, 2, s2, slinky::expr(int64_t{1}));
  g->View(9473, 9521, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer12 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(8822, 5285, {1,0});
  g->Binary(ynn_binary_multiply, 5271, 5284, 5281);
  g->Dot(708, 5285, YNN_INVALID_VALUE_ID, 5280, 1);
  g->DequantizeTensor(5280, YNN_INVALID_VALUE_ID, 5281, 5282);
  g->QuantizeTensor(5282, 8595, 5283, 742);
  g->Dequantize(742, 743, 0.20964568853378296, 0);
  g->SplitDim(743, 744, 2, {8,256});
  g->Transpose(744, 745, {0,2,1,3});
  g->Unary(ynn_unary_square, 745, 746);
  g->Reduce(ynn_reduce_sum, 746, 7358, {3}, true);
  g->ShapeProduct(746, 7357, {3});
  g->Binary(ynn_binary_divide, 7358, 7357, 747);
  g->Binary(ynn_binary_add, 747, 8647, 748);
  g->Unary(ynn_unary_rsqrt, 748, 749);
  g->Binary(ynn_binary_multiply, 745, 749, 751);
  g->Binary(ynn_binary_multiply, 751, 8821, 752);
  g->Slice(752, 753, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(752, 754, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 754, 755);
  g->Concat({755,753}, 756, 3);
  g->Binary(ynn_binary_multiply, 752, 3141, 757);
  g->Binary(ynn_binary_multiply, 756, 4217, 758);
  g->Binary(ynn_binary_add, 757, 758, 759);
}

// Scope: "Layer12 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9497, 760, 0.005684707313776016, 0);
  g->Dequantize(9521, 762, 0.047244105488061905, 0);
  g->Slice(759, 763, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(760, 764, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(762, 765, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(763, 764, 766, false, true);
  g->Mask(766, 8660, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8660, 7362, {-1}, true);
  g->Binary(ynn_binary_subtract, 8660, 7362, 7359);
  g->Unary(ynn_unary_exp, 7359, 7360);
  g->Reduce(ynn_reduce_sum, 7360, 7363, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 7363, 7361);
  g->Binary(ynn_binary_multiply, 7360, 7361, 767);
  g->Matmul(767, 765, 768, false, false);
  g->Slice(759, 769, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(760, 770, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(762, 772, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(769, 770, 773, false, true);
  g->Mask(773, 8661, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8661, 7367, {-1}, true);
  g->Binary(ynn_binary_subtract, 8661, 7367, 7364);
  g->Unary(ynn_unary_exp, 7364, 7365);
  g->Reduce(ynn_reduce_sum, 7365, 7368, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 7368, 7366);
  g->Binary(ynn_binary_multiply, 7365, 7366, 774);
  g->Matmul(774, 772, 775, false, false);
  g->Concat({768,775}, 776, 1);
}

// Scope: "Layer12 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(776, 777, {0,2,1,3});
  g->FuseDims(777, 778, 2, 2);
  g->Quantize(778, 779, 0.028912410140037537, 0);
  g->Transpose(8820, 5292, {1,0});
  g->Binary(ynn_binary_multiply, 5289, 5291, 5287);
  g->Dot(779, 5292, YNN_INVALID_VALUE_ID, 5286, 1);
  g->DequantizeTensor(5286, YNN_INVALID_VALUE_ID, 5287, 5288);
  g->QuantizeTensor(5288, 8595, 5290, 780);
  g->Dequantize(780, 782, 0.11405377089977264, 0);
}

// Scope: "Layer12 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 701, 702);
  g->Reduce(ynn_reduce_sum, 702, 7352, {2}, true);
  g->ShapeProduct(702, 7351, {2});
  g->Binary(ynn_binary_divide, 7352, 7351, 703);
  g->Binary(ynn_binary_add, 703, 8647, 704);
  g->Unary(ynn_unary_rsqrt, 704, 705);
  g->Binary(ynn_binary_multiply, 701, 705, 706);
  g->Binary(ynn_binary_multiply, 706, 8807, 707);
  BuildLayer12AttentionKvProjection(ctx);
  BuildLayer12AttentionCacheUpdate(ctx);
  BuildLayer12AttentionQueryProjection(ctx);
  BuildLayer12AttentionSdpa(ctx);
  BuildLayer12AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 782, 783);
  g->Reduce(ynn_reduce_sum, 783, 7370, {2}, true);
  g->ShapeProduct(783, 7369, {2});
  g->Binary(ynn_binary_divide, 7370, 7369, 784);
  g->Binary(ynn_binary_add, 784, 8647, 785);
  g->Unary(ynn_unary_rsqrt, 785, 786);
  g->Binary(ynn_binary_multiply, 782, 786, 787);
  g->Binary(ynn_binary_multiply, 787, 8814, 788);
  g->Binary(ynn_binary_add, 788, 701, 789);
}

// Scope: "Layer12 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 789, 790);
  g->Reduce(ynn_reduce_sum, 790, 7372, {2}, true);
  g->ShapeProduct(790, 7371, {2});
  g->Binary(ynn_binary_divide, 7372, 7371, 791);
  g->Binary(ynn_binary_add, 791, 8647, 793);
  g->Unary(ynn_unary_rsqrt, 793, 794);
  g->Binary(ynn_binary_multiply, 789, 794, 795);
  g->Binary(ynn_binary_multiply, 795, 8817, 796);
  g->Quantize(796, 797, 0.029738755896687508, 0);
  g->Transpose(8811, 5299, {1,0});
  g->Binary(ynn_binary_multiply, 5296, 5298, 5294);
  g->Dot(797, 5299, YNN_INVALID_VALUE_ID, 5293, 1);
  g->DequantizeTensor(5293, YNN_INVALID_VALUE_ID, 5294, 5295);
  g->QuantizeTensor(5295, 8595, 5297, 798);
  g->Dequantize(798, 799, 0.05216536670923233, 0);
  g->Transpose(8810, 5304, {1,0});
  g->Binary(ynn_binary_multiply, 5296, 5303, 5301);
  g->Dot(797, 5304, YNN_INVALID_VALUE_ID, 5300, 1);
  g->DequantizeTensor(5300, YNN_INVALID_VALUE_ID, 5301, 5302);
  g->QuantizeTensor(5302, 8595, 5297, 800);
  g->Dequantize(800, 801, 0.05216536670923233, 0);
  g->Polynomial(801, 7375, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7375, 7376);
  g->Binary(ynn_binary_add, 7376, 7161, 7373);
  g->Binary(ynn_binary_multiply, 801, 7173, 7374);
  g->Binary(ynn_binary_multiply, 7374, 7373, 802);
  g->Binary(ynn_binary_multiply, 799, 802, 803);
  g->Quantize(803, 804, 0.09350394457578659, 0);
  g->Transpose(8809, 5311, {1,0});
  g->Binary(ynn_binary_multiply, 5308, 5310, 5306);
  g->Dot(804, 5311, YNN_INVALID_VALUE_ID, 5305, 1);
  g->DequantizeTensor(5305, YNN_INVALID_VALUE_ID, 5306, 5307);
  g->QuantizeTensor(5307, 8595, 5309, 805);
  g->Dequantize(805, 806, 0.0321725495159626, 0);
  g->Unary(ynn_unary_square, 806, 807);
  g->Reduce(ynn_reduce_sum, 807, 7378, {2}, true);
  g->ShapeProduct(807, 7377, {2});
  g->Binary(ynn_binary_divide, 7378, 7377, 808);
  g->Binary(ynn_binary_add, 808, 8647, 809);
  g->Unary(ynn_unary_rsqrt, 809, 810);
  g->Binary(ynn_binary_multiply, 806, 810, 811);
  g->Binary(ynn_binary_multiply, 811, 8815, 813);
  g->Binary(ynn_binary_add, 813, 789, 814);
}

// Scope: "Layer12 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 815, {0,0,12,0}, {-1,-1,1,-1});
  g->Reshape(815, 816, {1,1,256});
  g->Unary(ynn_unary_square, 816, 817);
  g->Reduce(ynn_reduce_sum, 817, 7380, {2}, true);
  g->ShapeProduct(817, 7379, {2});
  g->Binary(ynn_binary_divide, 7380, 7379, 818);
  g->Binary(ynn_binary_add, 818, 8647, 819);
  g->Unary(ynn_unary_rsqrt, 819, 820);
  g->Binary(ynn_binary_multiply, 816, 820, 821);
  g->Binary(ynn_binary_multiply, 821, 9401, 822);
  g->Binary(ynn_binary_multiply, 9406, 8651, 824);
  g->Binary(ynn_binary_add, 822, 824, 825);
  g->Binary(ynn_binary_multiply, 825, 8645, 826);
  g->Quantize(814, 827, 0.6675296425819397, 0);
  g->Transpose(8812, 5323, {1,0});
  g->Binary(ynn_binary_multiply, 5320, 5322, 5318);
  g->Dot(827, 5323, YNN_INVALID_VALUE_ID, 5317, 1);
  g->DequantizeTensor(5317, YNN_INVALID_VALUE_ID, 5318, 5319);
  g->QuantizeTensor(5319, 8595, 5321, 828);
  g->Dequantize(828, 829, 0.09104331582784653, 0);
  g->Polynomial(829, 7383, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7383, 7384);
  g->Binary(ynn_binary_add, 7384, 7161, 7381);
  g->Binary(ynn_binary_multiply, 829, 7173, 7382);
  g->Binary(ynn_binary_multiply, 7382, 7381, 830);
  g->Binary(ynn_binary_multiply, 830, 826, 831);
  g->Quantize(831, 832, 0.712598443031311, 0);
  g->Transpose(8813, 5330, {1,0});
  g->Binary(ynn_binary_multiply, 5327, 5329, 5325);
  g->Dot(832, 5330, YNN_INVALID_VALUE_ID, 5324, 1);
  g->DequantizeTensor(5324, YNN_INVALID_VALUE_ID, 5325, 5326);
  g->QuantizeTensor(5326, 8595, 5328, 833);
  g->Dequantize(833, 836, 0.15073752403259277, 0);
  g->Unary(ynn_unary_square, 836, 837);
  g->Reduce(ynn_reduce_sum, 837, 7386, {2}, true);
  g->ShapeProduct(837, 7385, {2});
  g->Binary(ynn_binary_divide, 7386, 7385, 838);
  g->Binary(ynn_binary_add, 838, 8647, 839);
  g->Unary(ynn_unary_rsqrt, 839, 840);
  g->Binary(ynn_binary_multiply, 836, 840, 841);
  g->Binary(ynn_binary_multiply, 841, 8816, 842);
  g->Binary(ynn_binary_add, 814, 842, 843);
  g->Binary(ynn_binary_multiply, 843, 8808, 844);
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
  g->Transpose(8836, 5337, {1,0});
  g->Binary(ynn_binary_multiply, 5334, 5336, 5332);
  g->Dot(852, 5337, YNN_INVALID_VALUE_ID, 5331, 1);
  g->DequantizeTensor(5331, YNN_INVALID_VALUE_ID, 5332, 5333);
  g->QuantizeTensor(5333, 8595, 5335, 853);
  g->Dequantize(853, 854, 0.18700788915157318, 0);
  g->SplitDim(854, 855, 2, {2,256});
  g->Transpose(855, 856, {0,2,1,3});
  g->Unary(ynn_unary_square, 856, 858);
  g->Reduce(ynn_reduce_sum, 858, 7390, {3}, true);
  g->ShapeProduct(858, 7389, {3});
  g->Binary(ynn_binary_divide, 7390, 7389, 859);
  g->Binary(ynn_binary_add, 859, 8647, 860);
  g->Unary(ynn_unary_rsqrt, 860, 861);
  g->Binary(ynn_binary_multiply, 856, 861, 862);
  g->Binary(ynn_binary_multiply, 862, 8835, 863);
  g->Slice(863, 864, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(863, 865, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 865, 866);
  g->Concat({866,864}, 867, 3);
  g->Binary(ynn_binary_multiply, 863, 3141, 869);
  g->Binary(ynn_binary_multiply, 867, 4217, 870);
  g->Binary(ynn_binary_add, 869, 870, 871);
  g->Transpose(8840, 5342, {1,0});
  g->Binary(ynn_binary_multiply, 5334, 5341, 5339);
  g->Dot(852, 5342, YNN_INVALID_VALUE_ID, 5338, 1);
  g->DequantizeTensor(5338, YNN_INVALID_VALUE_ID, 5339, 5340);
  g->QuantizeTensor(5340, 8595, 5335, 872);
  g->Dequantize(872, 873, 0.18700788915157318, 0);
  g->SplitDim(873, 874, 2, {2,256});
  g->Transpose(874, 875, {0,2,1,3});
  g->Unary(ynn_unary_square, 875, 876);
  g->Reduce(ynn_reduce_sum, 876, 7394, {3}, true);
  g->ShapeProduct(876, 7393, {3});
  g->Binary(ynn_binary_divide, 7394, 7393, 877);
  g->Binary(ynn_binary_add, 877, 8647, 879);
  g->Unary(ynn_unary_rsqrt, 879, 880);
  g->Binary(ynn_binary_multiply, 875, 880, 881);
}

// Scope: "Layer13 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(871, 882, 0.0057707298547029495, 0);
  g->Append(8601, 882, 9450, 2, s2, slinky::expr(int64_t{1}));
  g->View(9450, 9498, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(881, 883, 0.047244105488061905, 0);
  g->Append(8625, 883, 9474, 2, s2, slinky::expr(int64_t{1}));
  g->View(9474, 9522, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer13 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(8839, 5348, {1,0});
  g->Binary(ynn_binary_multiply, 5334, 5347, 5344);
  g->Dot(852, 5348, YNN_INVALID_VALUE_ID, 5343, 1);
  g->DequantizeTensor(5343, YNN_INVALID_VALUE_ID, 5344, 5345);
  g->QuantizeTensor(5345, 8595, 5346, 885);
  g->Dequantize(885, 886, 0.20570868253707886, 0);
  g->SplitDim(886, 887, 2, {8,256});
  g->Transpose(887, 888, {0,2,1,3});
  g->Unary(ynn_unary_square, 888, 889);
  g->Reduce(ynn_reduce_sum, 889, 7396, {3}, true);
  g->ShapeProduct(889, 7395, {3});
  g->Binary(ynn_binary_divide, 7396, 7395, 890);
  g->Binary(ynn_binary_add, 890, 8647, 891);
  g->Unary(ynn_unary_rsqrt, 891, 892);
  g->Binary(ynn_binary_multiply, 888, 892, 893);
  g->Binary(ynn_binary_multiply, 893, 8838, 894);
  g->Slice(894, 896, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(894, 897, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 897, 898);
  g->Concat({898,896}, 899, 3);
  g->Binary(ynn_binary_multiply, 894, 3141, 900);
  g->Binary(ynn_binary_multiply, 899, 4217, 901);
  g->Binary(ynn_binary_add, 900, 901, 902);
}

// Scope: "Layer13 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9498, 903, 0.0057707298547029495, 0);
  g->Dequantize(9522, 904, 0.047244105488061905, 0);
  g->Slice(902, 905, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(903, 907, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(904, 908, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(905, 907, 909, false, true);
  g->Mask(909, 8662, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8662, 7400, {-1}, true);
  g->Binary(ynn_binary_subtract, 8662, 7400, 7397);
  g->Unary(ynn_unary_exp, 7397, 7398);
  g->Reduce(ynn_reduce_sum, 7398, 7401, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 7401, 7399);
  g->Binary(ynn_binary_multiply, 7398, 7399, 910);
  g->Matmul(910, 908, 911, false, false);
  g->Slice(902, 912, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(903, 913, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(904, 914, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(912, 913, 915, false, true);
  g->Mask(915, 8663, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8663, 7405, {-1}, true);
  g->Binary(ynn_binary_subtract, 8663, 7405, 7402);
  g->Unary(ynn_unary_exp, 7402, 7403);
  g->Reduce(ynn_reduce_sum, 7403, 7406, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 7406, 7404);
  g->Binary(ynn_binary_multiply, 7403, 7404, 916);
  g->Matmul(916, 914, 917, false, false);
  g->Concat({911,917}, 918, 1);
}

// Scope: "Layer13 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(918, 919, {0,2,1,3});
  g->FuseDims(919, 920, 2, 2);
  g->Quantize(920, 921, 0.023129930719733238, 0);
  g->Transpose(8837, 5355, {1,0});
  g->Binary(ynn_binary_multiply, 5352, 5354, 5350);
  g->Dot(921, 5355, YNN_INVALID_VALUE_ID, 5349, 1);
  g->DequantizeTensor(5349, YNN_INVALID_VALUE_ID, 5350, 5351);
  g->QuantizeTensor(5351, 8595, 5353, 922);
  g->Dequantize(922, 923, 0.0383908711373806, 0);
}

// Scope: "Layer13 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 844, 845);
  g->Reduce(ynn_reduce_sum, 845, 7388, {2}, true);
  g->ShapeProduct(845, 7387, {2});
  g->Binary(ynn_binary_divide, 7388, 7387, 847);
  g->Binary(ynn_binary_add, 847, 8647, 848);
  g->Unary(ynn_unary_rsqrt, 848, 849);
  g->Binary(ynn_binary_multiply, 844, 849, 850);
  g->Binary(ynn_binary_multiply, 850, 8824, 851);
  BuildLayer13AttentionKvProjection(ctx);
  BuildLayer13AttentionCacheUpdate(ctx);
  BuildLayer13AttentionQueryProjection(ctx);
  BuildLayer13AttentionSdpa(ctx);
  BuildLayer13AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 923, 924);
  g->Reduce(ynn_reduce_sum, 924, 7408, {2}, true);
  g->ShapeProduct(924, 7407, {2});
  g->Binary(ynn_binary_divide, 7408, 7407, 925);
  g->Binary(ynn_binary_add, 925, 8647, 926);
  g->Unary(ynn_unary_rsqrt, 926, 927);
  g->Binary(ynn_binary_multiply, 923, 927, 928);
  g->Binary(ynn_binary_multiply, 928, 8831, 929);
  g->Binary(ynn_binary_add, 929, 844, 930);
}

// Scope: "Layer13 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 930, 931);
  g->Reduce(ynn_reduce_sum, 931, 7410, {2}, true);
  g->ShapeProduct(931, 7409, {2});
  g->Binary(ynn_binary_divide, 7410, 7409, 932);
  g->Binary(ynn_binary_add, 932, 8647, 933);
  g->Unary(ynn_unary_rsqrt, 933, 934);
  g->Binary(ynn_binary_multiply, 930, 934, 937);
  g->Binary(ynn_binary_multiply, 937, 8834, 938);
  g->Quantize(938, 939, 0.02818576619029045, 0);
  g->Transpose(8828, 5361, {1,0});
  g->Binary(ynn_binary_multiply, 5359, 5360, 5357);
  g->Dot(939, 5361, YNN_INVALID_VALUE_ID, 5356, 1);
  g->DequantizeTensor(5356, YNN_INVALID_VALUE_ID, 5357, 5358);
  g->QuantizeTensor(5358, 8595, 4988, 940);
  g->Dequantize(940, 941, 0.04675197973847389, 0);
  g->Transpose(8827, 5366, {1,0});
  g->Binary(ynn_binary_multiply, 5359, 5365, 5363);
  g->Dot(939, 5366, YNN_INVALID_VALUE_ID, 5362, 1);
  g->DequantizeTensor(5362, YNN_INVALID_VALUE_ID, 5363, 5364);
  g->QuantizeTensor(5364, 8595, 4988, 942);
  g->Dequantize(942, 943, 0.04675197973847389, 0);
  g->Polynomial(943, 7413, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7413, 7414);
  g->Binary(ynn_binary_add, 7414, 7161, 7411);
  g->Binary(ynn_binary_multiply, 943, 7173, 7412);
  g->Binary(ynn_binary_multiply, 7412, 7411, 944);
  g->Binary(ynn_binary_multiply, 941, 944, 945);
  g->Quantize(945, 946, 0.09202756732702255, 0);
  g->Transpose(8826, 5373, {1,0});
  g->Binary(ynn_binary_multiply, 5370, 5372, 5368);
  g->Dot(946, 5373, YNN_INVALID_VALUE_ID, 5367, 1);
  g->DequantizeTensor(5367, YNN_INVALID_VALUE_ID, 5368, 5369);
  g->QuantizeTensor(5369, 8595, 5371, 947);
  g->Dequantize(947, 948, 0.05065973475575447, 0);
  g->Unary(ynn_unary_square, 948, 949);
  g->Reduce(ynn_reduce_sum, 949, 7416, {2}, true);
  g->ShapeProduct(949, 7415, {2});
  g->Binary(ynn_binary_divide, 7416, 7415, 950);
  g->Binary(ynn_binary_add, 950, 8647, 951);
  g->Unary(ynn_unary_rsqrt, 951, 952);
  g->Binary(ynn_binary_multiply, 948, 952, 953);
  g->Binary(ynn_binary_multiply, 953, 8832, 954);
  g->Binary(ynn_binary_add, 954, 930, 955);
}

// Scope: "Layer13 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 956, {0,0,13,0}, {-1,-1,1,-1});
  g->Reshape(956, 957, {1,1,256});
  g->Unary(ynn_unary_square, 957, 958);
  g->Reduce(ynn_reduce_sum, 958, 7418, {2}, true);
  g->ShapeProduct(958, 7417, {2});
  g->Binary(ynn_binary_divide, 7418, 7417, 959);
  g->Binary(ynn_binary_add, 959, 8647, 960);
  g->Unary(ynn_unary_rsqrt, 960, 961);
  g->Binary(ynn_binary_multiply, 957, 961, 962);
  g->Binary(ynn_binary_multiply, 962, 9401, 963);
  g->Binary(ynn_binary_multiply, 9407, 8651, 964);
  g->Binary(ynn_binary_add, 963, 964, 965);
  g->Binary(ynn_binary_multiply, 965, 8645, 966);
  g->Quantize(955, 967, 0.698938250541687, 0);
  g->Transpose(8829, 5380, {1,0});
  g->Binary(ynn_binary_multiply, 5377, 5379, 5375);
  g->Dot(967, 5380, YNN_INVALID_VALUE_ID, 5374, 1);
  g->DequantizeTensor(5374, YNN_INVALID_VALUE_ID, 5375, 5376);
  g->QuantizeTensor(5376, 8595, 5378, 968);
  g->Dequantize(968, 969, 0.07775591313838959, 0);
  g->Polynomial(969, 7421, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7421, 7422);
  g->Binary(ynn_binary_add, 7422, 7161, 7419);
  g->Binary(ynn_binary_multiply, 969, 7173, 7420);
  g->Binary(ynn_binary_multiply, 7420, 7419, 970);
  g->Binary(ynn_binary_multiply, 970, 966, 971);
  g->Quantize(971, 972, 0.4881889820098877, 0);
  g->Transpose(8830, 5387, {1,0});
  g->Binary(ynn_binary_multiply, 5384, 5386, 5382);
  g->Dot(972, 5387, YNN_INVALID_VALUE_ID, 5381, 1);
  g->DequantizeTensor(5381, YNN_INVALID_VALUE_ID, 5382, 5383);
  g->QuantizeTensor(5383, 8595, 5385, 973);
  g->Dequantize(973, 974, 0.15653027594089508, 0);
  g->Unary(ynn_unary_square, 974, 975);
  g->Reduce(ynn_reduce_sum, 975, 7424, {2}, true);
  g->ShapeProduct(975, 7423, {2});
  g->Binary(ynn_binary_divide, 7424, 7423, 977);
  g->Binary(ynn_binary_add, 977, 8647, 978);
  g->Unary(ynn_unary_rsqrt, 978, 979);
  g->Binary(ynn_binary_multiply, 974, 979, 980);
  g->Binary(ynn_binary_multiply, 980, 8833, 981);
  g->Binary(ynn_binary_add, 955, 981, 982);
  g->Binary(ynn_binary_multiply, 982, 8825, 983);
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
  g->Transpose(8853, 5400, {1,0});
  g->Binary(ynn_binary_multiply, 5397, 5399, 5395);
  g->Dot(991, 5400, YNN_INVALID_VALUE_ID, 5394, 1);
  g->DequantizeTensor(5394, YNN_INVALID_VALUE_ID, 5395, 5396);
  g->QuantizeTensor(5396, 8595, 5398, 992);
  g->Dequantize(992, 993, 0.25, 0);
  g->SplitDim(993, 994, 2, {2,256});
  g->Transpose(994, 995, {0,2,1,3});
  g->Unary(ynn_unary_square, 995, 996);
  g->Reduce(ynn_reduce_sum, 996, 7428, {3}, true);
  g->ShapeProduct(996, 7427, {3});
  g->Binary(ynn_binary_divide, 7428, 7427, 997);
  g->Binary(ynn_binary_add, 997, 8647, 999);
  g->Unary(ynn_unary_rsqrt, 999, 1000);
  g->Binary(ynn_binary_multiply, 995, 1000, 1001);
  g->Binary(ynn_binary_multiply, 1001, 8852, 1002);
  g->Slice(1002, 1003, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1002, 1004, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1004, 1005);
  g->Concat({1005,1003}, 1006, 3);
  g->Binary(ynn_binary_multiply, 1002, 3141, 1007);
  g->Binary(ynn_binary_multiply, 1006, 4217, 1008);
  g->Binary(ynn_binary_add, 1007, 1008, 1010);
  g->Transpose(8857, 5405, {1,0});
  g->Binary(ynn_binary_multiply, 5397, 5404, 5402);
  g->Dot(991, 5405, YNN_INVALID_VALUE_ID, 5401, 1);
  g->DequantizeTensor(5401, YNN_INVALID_VALUE_ID, 5402, 5403);
  g->QuantizeTensor(5403, 8595, 5398, 1011);
  g->Dequantize(1011, 1012, 0.25, 0);
  g->SplitDim(1012, 1013, 2, {2,256});
  g->Transpose(1013, 1014, {0,2,1,3});
  g->Unary(ynn_unary_square, 1014, 1015);
  g->Reduce(ynn_reduce_sum, 1015, 7430, {3}, true);
  g->ShapeProduct(1015, 7429, {3});
  g->Binary(ynn_binary_divide, 7430, 7429, 1016);
  g->Binary(ynn_binary_add, 1016, 8647, 1017);
  g->Unary(ynn_unary_rsqrt, 1017, 1018);
  g->Binary(ynn_binary_multiply, 1014, 1018, 1020);
}

// Scope: "Layer14 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(1010, 1021, 0.005712664220482111, 0);
  g->Append(8602, 1021, 9451, 2, s2, slinky::expr(int64_t{1}));
  g->View(9451, 9499, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(1020, 1022, 0.047244105488061905, 0);
  g->Append(8626, 1022, 9475, 2, s2, slinky::expr(int64_t{1}));
  g->View(9475, 9523, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer14 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(8856, 5411, {1,0});
  g->Binary(ynn_binary_multiply, 5397, 5410, 5407);
  g->Dot(991, 5411, YNN_INVALID_VALUE_ID, 5406, 1);
  g->DequantizeTensor(5406, YNN_INVALID_VALUE_ID, 5407, 5408);
  g->QuantizeTensor(5408, 8595, 5409, 1023);
  g->Dequantize(1023, 1024, 0.29133859276771545, 0);
  g->SplitDim(1024, 1026, 2, {8,256});
  g->Transpose(1026, 1027, {0,2,1,3});
  g->Unary(ynn_unary_square, 1027, 1028);
  g->Reduce(ynn_reduce_sum, 1028, 7434, {3}, true);
  g->ShapeProduct(1028, 7433, {3});
  g->Binary(ynn_binary_divide, 7434, 7433, 1029);
  g->Binary(ynn_binary_add, 1029, 8647, 1030);
  g->Unary(ynn_unary_rsqrt, 1030, 1031);
  g->Binary(ynn_binary_multiply, 1027, 1031, 1032);
  g->Binary(ynn_binary_multiply, 1032, 8855, 1033);
  g->Slice(1033, 1034, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1033, 1035, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1035, 1039);
  g->Concat({1039,1034}, 1040, 3);
  g->Binary(ynn_binary_multiply, 1033, 3141, 1041);
  g->Binary(ynn_binary_multiply, 1040, 4217, 1042);
  g->Binary(ynn_binary_add, 1041, 1042, 1043);
}

// Scope: "Layer14 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9499, 1044, 0.005712664220482111, 0);
  g->Dequantize(9523, 1045, 0.047244105488061905, 0);
  g->Slice(1043, 1046, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(1044, 1047, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(1045, 1048, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(1046, 1047, 1050, false, true);
  g->Mask(1050, 8664, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8664, 7438, {-1}, true);
  g->Binary(ynn_binary_subtract, 8664, 7438, 7435);
  g->Unary(ynn_unary_exp, 7435, 7436);
  g->Reduce(ynn_reduce_sum, 7436, 7439, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 7439, 7437);
  g->Binary(ynn_binary_multiply, 7436, 7437, 1051);
  g->Matmul(1051, 1048, 1052, false, false);
  g->Slice(1043, 1053, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(1044, 1054, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(1045, 1055, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(1053, 1054, 1056, false, true);
  g->Mask(1056, 8665, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8665, 7443, {-1}, true);
  g->Binary(ynn_binary_subtract, 8665, 7443, 7440);
  g->Unary(ynn_unary_exp, 7440, 7441);
  g->Reduce(ynn_reduce_sum, 7441, 7444, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 7444, 7442);
  g->Binary(ynn_binary_multiply, 7441, 7442, 1057);
  g->Matmul(1057, 1055, 1059, false, false);
  g->Concat({1052,1059}, 1060, 1);
}

// Scope: "Layer14 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1060, 1061, {0,2,1,3});
  g->FuseDims(1061, 1062, 2, 2);
  g->Quantize(1062, 1063, 0.02472933940589428, 0);
  g->Transpose(8854, 5418, {1,0});
  g->Binary(ynn_binary_multiply, 5415, 5417, 5413);
  g->Dot(1063, 5418, YNN_INVALID_VALUE_ID, 5412, 1);
  g->DequantizeTensor(5412, YNN_INVALID_VALUE_ID, 5413, 5414);
  g->QuantizeTensor(5414, 8595, 5416, 1064);
  g->Dequantize(1064, 1065, 0.039510589092969894, 0);
}

// Scope: "Layer14 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 983, 984);
  g->Reduce(ynn_reduce_sum, 984, 7426, {2}, true);
  g->ShapeProduct(984, 7425, {2});
  g->Binary(ynn_binary_divide, 7426, 7425, 985);
  g->Binary(ynn_binary_add, 985, 8647, 986);
  g->Unary(ynn_unary_rsqrt, 986, 988);
  g->Binary(ynn_binary_multiply, 983, 988, 989);
  g->Binary(ynn_binary_multiply, 989, 8841, 990);
  BuildLayer14AttentionKvProjection(ctx);
  BuildLayer14AttentionCacheUpdate(ctx);
  BuildLayer14AttentionQueryProjection(ctx);
  BuildLayer14AttentionSdpa(ctx);
  BuildLayer14AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1065, 1066);
  g->Reduce(ynn_reduce_sum, 1066, 7446, {2}, true);
  g->ShapeProduct(1066, 7445, {2});
  g->Binary(ynn_binary_divide, 7446, 7445, 1067);
  g->Binary(ynn_binary_add, 1067, 8647, 1068);
  g->Unary(ynn_unary_rsqrt, 1068, 1070);
  g->Binary(ynn_binary_multiply, 1065, 1070, 1071);
  g->Binary(ynn_binary_multiply, 1071, 8848, 1072);
  g->Binary(ynn_binary_add, 1072, 983, 1073);
}

// Scope: "Layer14 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1073, 1074);
  g->Reduce(ynn_reduce_sum, 1074, 7448, {2}, true);
  g->ShapeProduct(1074, 7447, {2});
  g->Binary(ynn_binary_divide, 7448, 7447, 1075);
  g->Binary(ynn_binary_add, 1075, 8647, 1076);
  g->Unary(ynn_unary_rsqrt, 1076, 1077);
  g->Binary(ynn_binary_multiply, 1073, 1077, 1078);
  g->Binary(ynn_binary_multiply, 1078, 8851, 1079);
  g->Quantize(1079, 1081, 0.015675809234380722, 0);
  g->Transpose(8845, 5425, {1,0});
  g->Binary(ynn_binary_multiply, 5422, 5424, 5420);
  g->Dot(1081, 5425, YNN_INVALID_VALUE_ID, 5419, 1);
  g->DequantizeTensor(5419, YNN_INVALID_VALUE_ID, 5420, 5421);
  g->QuantizeTensor(5421, 8595, 5423, 1082);
  g->Dequantize(1082, 1083, 0.0216535534709692, 0);
  g->Transpose(8844, 5430, {1,0});
  g->Binary(ynn_binary_multiply, 5422, 5429, 5427);
  g->Dot(1081, 5430, YNN_INVALID_VALUE_ID, 5426, 1);
  g->DequantizeTensor(5426, YNN_INVALID_VALUE_ID, 5427, 5428);
  g->QuantizeTensor(5428, 8595, 5423, 1084);
  g->Dequantize(1084, 1085, 0.0216535534709692, 0);
  g->Polynomial(1085, 7451, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7451, 7452);
  g->Binary(ynn_binary_add, 7452, 7161, 7449);
  g->Binary(ynn_binary_multiply, 1085, 7173, 7450);
  g->Binary(ynn_binary_multiply, 7450, 7449, 1086);
  g->Binary(ynn_binary_multiply, 1083, 1086, 1087);
  g->Quantize(1087, 1088, 0.02472933940589428, 0);
  g->Transpose(8843, 5436, {1,0});
  g->Binary(ynn_binary_multiply, 5415, 5435, 5432);
  g->Dot(1088, 5436, YNN_INVALID_VALUE_ID, 5431, 1);
  g->DequantizeTensor(5431, YNN_INVALID_VALUE_ID, 5432, 5433);
  g->QuantizeTensor(5433, 8595, 5434, 1089);
  g->Dequantize(1089, 1091, 0.01883137971162796, 0);
  g->Unary(ynn_unary_square, 1091, 1092);
  g->Reduce(ynn_reduce_sum, 1092, 7454, {2}, true);
  g->ShapeProduct(1092, 7453, {2});
  g->Binary(ynn_binary_divide, 7454, 7453, 1093);
  g->Binary(ynn_binary_add, 1093, 8647, 1094);
  g->Unary(ynn_unary_rsqrt, 1094, 1095);
  g->Binary(ynn_binary_multiply, 1091, 1095, 1096);
  g->Binary(ynn_binary_multiply, 1096, 8849, 1097);
  g->Binary(ynn_binary_add, 1097, 1073, 1098);
}

// Scope: "Layer14 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 1099, {0,0,14,0}, {-1,-1,1,-1});
  g->Reshape(1099, 1100, {1,1,256});
  g->Unary(ynn_unary_square, 1100, 1102);
  g->Reduce(ynn_reduce_sum, 1102, 7456, {2}, true);
  g->ShapeProduct(1102, 7455, {2});
  g->Binary(ynn_binary_divide, 7456, 7455, 1103);
  g->Binary(ynn_binary_add, 1103, 8647, 1104);
  g->Unary(ynn_unary_rsqrt, 1104, 1105);
  g->Binary(ynn_binary_multiply, 1100, 1105, 1106);
  g->Binary(ynn_binary_multiply, 1106, 9401, 1107);
  g->Binary(ynn_binary_multiply, 9408, 8651, 1108);
  g->Binary(ynn_binary_add, 1107, 1108, 1109);
  g->Binary(ynn_binary_multiply, 1109, 8645, 1110);
  g->Quantize(1098, 1111, 0.37186482548713684, 0);
  g->Transpose(8846, 5443, {1,0});
  g->Binary(ynn_binary_multiply, 5440, 5442, 5438);
  g->Dot(1111, 5443, YNN_INVALID_VALUE_ID, 5437, 1);
  g->DequantizeTensor(5437, YNN_INVALID_VALUE_ID, 5438, 5439);
  g->QuantizeTensor(5439, 8595, 5441, 1113);
  g->Dequantize(1113, 1114, 0.060531508177518845, 0);
  g->Polynomial(1114, 7459, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7459, 7460);
  g->Binary(ynn_binary_add, 7460, 7161, 7457);
  g->Binary(ynn_binary_multiply, 1114, 7173, 7458);
  g->Binary(ynn_binary_multiply, 7458, 7457, 1115);
  g->Binary(ynn_binary_multiply, 1115, 1110, 1116);
  g->Quantize(1116, 1117, 0.3523622155189514, 0);
  g->Transpose(8847, 5450, {1,0});
  g->Binary(ynn_binary_multiply, 5447, 5449, 5445);
  g->Dot(1117, 5450, YNN_INVALID_VALUE_ID, 5444, 1);
  g->DequantizeTensor(5444, YNN_INVALID_VALUE_ID, 5445, 5446);
  g->QuantizeTensor(5446, 8595, 5448, 1118);
  g->Dequantize(1118, 1119, 0.08160637319087982, 0);
  g->Unary(ynn_unary_square, 1119, 1120);
  g->Reduce(ynn_reduce_sum, 1120, 7462, {2}, true);
  g->ShapeProduct(1120, 7461, {2});
  g->Binary(ynn_binary_divide, 7462, 7461, 1121);
  g->Binary(ynn_binary_add, 1121, 8647, 1122);
  g->Unary(ynn_unary_rsqrt, 1122, 1124);
  g->Binary(ynn_binary_multiply, 1119, 1124, 1125);
  g->Binary(ynn_binary_multiply, 1125, 8850, 1126);
  g->Binary(ynn_binary_add, 1098, 1126, 1127);
  g->Binary(ynn_binary_multiply, 1127, 8842, 1128);
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
  g->Transpose(8870, 5457, {1,0});
  g->Binary(ynn_binary_multiply, 5454, 5456, 5452);
  g->Dot(1136, 5457, YNN_INVALID_VALUE_ID, 5451, 1);
  g->DequantizeTensor(5451, YNN_INVALID_VALUE_ID, 5452, 5453);
  g->QuantizeTensor(5453, 8595, 5455, 1137);
  g->Dequantize(1137, 1138, 0.18897639214992523, 0);
  g->SplitDim(1138, 1139, 2, {2,256});
  g->Transpose(1139, 1140, {0,2,1,3});
  g->Unary(ynn_unary_square, 1140, 1141);
  g->Reduce(ynn_reduce_sum, 1141, 7466, {3}, true);
  g->ShapeProduct(1141, 7465, {3});
  g->Binary(ynn_binary_divide, 7466, 7465, 1142);
  g->Binary(ynn_binary_add, 1142, 8647, 1143);
  g->Unary(ynn_unary_rsqrt, 1143, 1144);
  g->Binary(ynn_binary_multiply, 1140, 1144, 1147);
  g->Binary(ynn_binary_multiply, 1147, 8869, 1148);
  g->Slice(1148, 1149, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1148, 1150, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1150, 1151);
  g->Concat({1151,1149}, 1152, 3);
  g->Binary(ynn_binary_multiply, 1148, 3141, 1153);
  g->Binary(ynn_binary_multiply, 1152, 4217, 1154);
  g->Binary(ynn_binary_add, 1153, 1154, 1155);
  g->Transpose(8874, 5462, {1,0});
  g->Binary(ynn_binary_multiply, 5454, 5461, 5459);
  g->Dot(1136, 5462, YNN_INVALID_VALUE_ID, 5458, 1);
  g->DequantizeTensor(5458, YNN_INVALID_VALUE_ID, 5459, 5460);
  g->QuantizeTensor(5460, 8595, 5455, 1157);
  g->Dequantize(1157, 1158, 0.18897639214992523, 0);
  g->SplitDim(1158, 1159, 2, {2,256});
  g->Transpose(1159, 1160, {0,2,1,3});
  g->Unary(ynn_unary_square, 1160, 1161);
  g->Reduce(ynn_reduce_sum, 1161, 7468, {3}, true);
  g->ShapeProduct(1161, 7467, {3});
  g->Binary(ynn_binary_divide, 7468, 7467, 1162);
  g->Binary(ynn_binary_add, 1162, 8647, 1163);
  g->Unary(ynn_unary_rsqrt, 1163, 1164);
  g->Binary(ynn_binary_multiply, 1160, 1164, 1165);
}

// Scope: "Layer15 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(1155, 1166, 0.005989333149045706, 0);
  g->Append(8603, 1166, 9452, 2, s2, slinky::expr(int64_t{1}));
  g->View(9452, 9500, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(1165, 1168, 0.047244105488061905, 0);
  g->Append(8627, 1168, 9476, 2, s2, slinky::expr(int64_t{1}));
  g->View(9476, 9524, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer15 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(8873, 5468, {1,0});
  g->Binary(ynn_binary_multiply, 5454, 5467, 5464);
  g->Dot(1136, 5468, YNN_INVALID_VALUE_ID, 5463, 1);
  g->DequantizeTensor(5463, YNN_INVALID_VALUE_ID, 5464, 5465);
  g->QuantizeTensor(5465, 8595, 5466, 1169);
  g->Dequantize(1169, 1170, 0.211614191532135, 0);
  g->SplitDim(1170, 1171, 2, {8,256});
  g->Transpose(1171, 1172, {0,2,1,3});
  g->Unary(ynn_unary_square, 1172, 1174);
  g->Reduce(ynn_reduce_sum, 1174, 7470, {3}, true);
  g->ShapeProduct(1174, 7469, {3});
  g->Binary(ynn_binary_divide, 7470, 7469, 1175);
  g->Binary(ynn_binary_add, 1175, 8647, 1176);
  g->Unary(ynn_unary_rsqrt, 1176, 1177);
  g->Binary(ynn_binary_multiply, 1172, 1177, 1178);
  g->Binary(ynn_binary_multiply, 1178, 8872, 1179);
  g->Slice(1179, 1180, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1179, 1181, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1181, 1182);
  g->Concat({1182,1180}, 1183, 3);
  g->Binary(ynn_binary_multiply, 1179, 3141, 1185);
  g->Binary(ynn_binary_multiply, 1183, 4217, 1186);
  g->Binary(ynn_binary_add, 1185, 1186, 1187);
}

// Scope: "Layer15 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9500, 1188, 0.005989333149045706, 0);
  g->Dequantize(9524, 1189, 0.047244105488061905, 0);
  g->Slice(1187, 1190, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(1188, 1191, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(1189, 1192, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(1190, 1191, 1193, false, true);
  g->Mask(1193, 8666, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8666, 7474, {-1}, true);
  g->Binary(ynn_binary_subtract, 8666, 7474, 7471);
  g->Unary(ynn_unary_exp, 7471, 7472);
  g->Reduce(ynn_reduce_sum, 7472, 7475, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 7475, 7473);
  g->Binary(ynn_binary_multiply, 7472, 7473, 1195);
  g->Matmul(1195, 1192, 1196, false, false);
  g->Slice(1187, 1197, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(1188, 1198, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(1189, 1199, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(1197, 1198, 1200, false, true);
  g->Mask(1200, 8667, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8667, 7479, {-1}, true);
  g->Binary(ynn_binary_subtract, 8667, 7479, 7476);
  g->Unary(ynn_unary_exp, 7476, 7477);
  g->Reduce(ynn_reduce_sum, 7477, 7480, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 7480, 7478);
  g->Binary(ynn_binary_multiply, 7477, 7478, 1201);
  g->Matmul(1201, 1199, 1202, false, false);
  g->Concat({1196,1202}, 1203, 1);
}

// Scope: "Layer15 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1203, 1205, {0,2,1,3});
  g->FuseDims(1205, 1206, 2, 2);
  g->Quantize(1206, 1207, 0.02706693857908249, 0);
  g->Transpose(8871, 5475, {1,0});
  g->Binary(ynn_binary_multiply, 5472, 5474, 5470);
  g->Dot(1207, 5475, YNN_INVALID_VALUE_ID, 5469, 1);
  g->DequantizeTensor(5469, YNN_INVALID_VALUE_ID, 5470, 5471);
  g->QuantizeTensor(5471, 8595, 5473, 1208);
  g->Dequantize(1208, 1209, 0.06876781582832336, 0);
}

// Scope: "Layer15 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1128, 1129);
  g->Reduce(ynn_reduce_sum, 1129, 7464, {2}, true);
  g->ShapeProduct(1129, 7463, {2});
  g->Binary(ynn_binary_divide, 7464, 7463, 1130);
  g->Binary(ynn_binary_add, 1130, 8647, 1131);
  g->Unary(ynn_unary_rsqrt, 1131, 1132);
  g->Binary(ynn_binary_multiply, 1128, 1132, 1133);
  g->Binary(ynn_binary_multiply, 1133, 8858, 1135);
  BuildLayer15AttentionKvProjection(ctx);
  BuildLayer15AttentionCacheUpdate(ctx);
  BuildLayer15AttentionQueryProjection(ctx);
  BuildLayer15AttentionSdpa(ctx);
  BuildLayer15AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1209, 1210);
  g->Reduce(ynn_reduce_sum, 1210, 7482, {2}, true);
  g->ShapeProduct(1210, 7481, {2});
  g->Binary(ynn_binary_divide, 7482, 7481, 1211);
  g->Binary(ynn_binary_add, 1211, 8647, 1212);
  g->Unary(ynn_unary_rsqrt, 1212, 1213);
  g->Binary(ynn_binary_multiply, 1209, 1213, 1214);
  g->Binary(ynn_binary_multiply, 1214, 8865, 1215);
  g->Binary(ynn_binary_add, 1215, 1128, 1216);
}

// Scope: "Layer15 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1216, 1217);
  g->Reduce(ynn_reduce_sum, 1217, 7484, {2}, true);
  g->ShapeProduct(1217, 7483, {2});
  g->Binary(ynn_binary_divide, 7484, 7483, 1218);
  g->Binary(ynn_binary_add, 1218, 8647, 1219);
  g->Unary(ynn_unary_rsqrt, 1219, 1220);
  g->Binary(ynn_binary_multiply, 1216, 1220, 1221);
  g->Binary(ynn_binary_multiply, 1221, 8868, 1222);
  g->Quantize(1222, 1223, 0.01503660250455141, 0);
  g->Transpose(8862, 5482, {1,0});
  g->Binary(ynn_binary_multiply, 5479, 5481, 5477);
  g->Dot(1223, 5482, YNN_INVALID_VALUE_ID, 5476, 1);
  g->DequantizeTensor(5476, YNN_INVALID_VALUE_ID, 5477, 5478);
  g->QuantizeTensor(5478, 8595, 5480, 1224);
  g->Dequantize(1224, 1226, 0.020300205796957016, 0);
  g->Transpose(8861, 5487, {1,0});
  g->Binary(ynn_binary_multiply, 5479, 5486, 5484);
  g->Dot(1223, 5487, YNN_INVALID_VALUE_ID, 5483, 1);
  g->DequantizeTensor(5483, YNN_INVALID_VALUE_ID, 5484, 5485);
  g->QuantizeTensor(5485, 8595, 5480, 1227);
  g->Dequantize(1227, 1228, 0.020300205796957016, 0);
  g->Polynomial(1228, 7492, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7492, 7493);
  g->Binary(ynn_binary_add, 7493, 7161, 7490);
  g->Binary(ynn_binary_multiply, 1228, 7173, 7491);
  g->Binary(ynn_binary_multiply, 7491, 7490, 1229);
  g->Binary(ynn_binary_multiply, 1226, 1229, 1230);
  g->Quantize(1230, 1231, 0.018700797110795975, 0);
  g->Transpose(8860, 5494, {1,0});
  g->Binary(ynn_binary_multiply, 5491, 5493, 5489);
  g->Dot(1231, 5494, YNN_INVALID_VALUE_ID, 5488, 1);
  g->DequantizeTensor(5488, YNN_INVALID_VALUE_ID, 5489, 5490);
  g->QuantizeTensor(5490, 8595, 5492, 1232);
  g->Dequantize(1232, 1233, 0.01157078705728054, 0);
  g->Unary(ynn_unary_square, 1233, 1234);
  g->Reduce(ynn_reduce_sum, 1234, 7495, {2}, true);
  g->ShapeProduct(1234, 7494, {2});
  g->Binary(ynn_binary_divide, 7495, 7494, 1236);
  g->Binary(ynn_binary_add, 1236, 8647, 1237);
  g->Unary(ynn_unary_rsqrt, 1237, 1238);
  g->Binary(ynn_binary_multiply, 1233, 1238, 1239);
  g->Binary(ynn_binary_multiply, 1239, 8866, 1240);
  g->Binary(ynn_binary_add, 1240, 1216, 1241);
}

// Scope: "Layer15 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 1242, {0,0,15,0}, {-1,-1,1,-1});
  g->Reshape(1242, 1243, {1,1,256});
  g->Unary(ynn_unary_square, 1243, 1244);
  g->Reduce(ynn_reduce_sum, 1244, 7497, {2}, true);
  g->ShapeProduct(1244, 7496, {2});
  g->Binary(ynn_binary_divide, 7497, 7496, 1245);
  g->Binary(ynn_binary_add, 1245, 8647, 1248);
  g->Unary(ynn_unary_rsqrt, 1248, 1249);
  g->Binary(ynn_binary_multiply, 1243, 1249, 1250);
  g->Binary(ynn_binary_multiply, 1250, 9401, 1251);
  g->Binary(ynn_binary_multiply, 9409, 8651, 1252);
  g->Binary(ynn_binary_add, 1251, 1252, 1253);
  g->Binary(ynn_binary_multiply, 1253, 8645, 1254);
  g->Quantize(1241, 1255, 0.40425750613212585, 0);
  g->Transpose(8863, 5508, {1,0});
  g->Binary(ynn_binary_multiply, 5505, 5507, 5503);
  g->Dot(1255, 5508, YNN_INVALID_VALUE_ID, 5502, 1);
  g->DequantizeTensor(5502, YNN_INVALID_VALUE_ID, 5503, 5504);
  g->QuantizeTensor(5504, 8595, 5506, 1256);
  g->Dequantize(1256, 1257, 0.10088583081960678, 0);
  g->Polynomial(1257, 7500, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7500, 7501);
  g->Binary(ynn_binary_add, 7501, 7161, 7498);
  g->Binary(ynn_binary_multiply, 1257, 7173, 7499);
  g->Binary(ynn_binary_multiply, 7499, 7498, 1259);
  g->Binary(ynn_binary_multiply, 1259, 1254, 1260);
  g->Quantize(1260, 1261, 0.748031497001648, 0);
  g->Transpose(8864, 5515, {1,0});
  g->Binary(ynn_binary_multiply, 5512, 5514, 5510);
  g->Dot(1261, 5515, YNN_INVALID_VALUE_ID, 5509, 1);
  g->DequantizeTensor(5509, YNN_INVALID_VALUE_ID, 5510, 5511);
  g->QuantizeTensor(5511, 8595, 5513, 1262);
  g->Dequantize(1262, 1263, 0.20252664387226105, 0);
  g->Unary(ynn_unary_square, 1263, 1264);
  g->Reduce(ynn_reduce_sum, 1264, 7503, {2}, true);
  g->ShapeProduct(1264, 7502, {2});
  g->Binary(ynn_binary_divide, 7503, 7502, 1265);
  g->Binary(ynn_binary_add, 1265, 8647, 1266);
  g->Unary(ynn_unary_rsqrt, 1266, 1267);
  g->Binary(ynn_binary_multiply, 1263, 1267, 1268);
  g->Binary(ynn_binary_multiply, 1268, 8867, 1270);
  g->Binary(ynn_binary_add, 1241, 1270, 1271);
  g->Binary(ynn_binary_multiply, 1271, 8859, 1272);
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
  g->Transpose(8887, 5522, {1,0});
  g->Binary(ynn_binary_multiply, 5519, 5521, 5517);
  g->Dot(1279, 5522, YNN_INVALID_VALUE_ID, 5516, 1);
  g->DequantizeTensor(5516, YNN_INVALID_VALUE_ID, 5517, 5518);
  g->QuantizeTensor(5518, 8595, 5520, 1281);
  g->Dequantize(1281, 1282, 0.16535434126853943, 0);
  g->SplitDim(1282, 1283, 2, {2,256});
  g->Transpose(1283, 1284, {0,2,1,3});
  g->Unary(ynn_unary_square, 1284, 1285);
  g->Reduce(ynn_reduce_sum, 1285, 7507, {3}, true);
  g->ShapeProduct(1285, 7506, {3});
  g->Binary(ynn_binary_divide, 7507, 7506, 1286);
  g->Binary(ynn_binary_add, 1286, 8647, 1287);
  g->Unary(ynn_unary_rsqrt, 1287, 1288);
  g->Binary(ynn_binary_multiply, 1284, 1288, 1289);
  g->Binary(ynn_binary_multiply, 1289, 8886, 1290);
  g->Slice(1290, 1291, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1290, 1292, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1292, 1293);
  g->Concat({1293,1291}, 1294, 3);
  g->Binary(ynn_binary_multiply, 1290, 3141, 1295);
  g->Binary(ynn_binary_multiply, 1294, 4217, 1296);
  g->Binary(ynn_binary_add, 1295, 1296, 1297);
  g->Transpose(8891, 5527, {1,0});
  g->Binary(ynn_binary_multiply, 5519, 5526, 5524);
  g->Dot(1279, 5527, YNN_INVALID_VALUE_ID, 5523, 1);
  g->DequantizeTensor(5523, YNN_INVALID_VALUE_ID, 5524, 5525);
  g->QuantizeTensor(5525, 8595, 5520, 1298);
  g->Dequantize(1298, 1299, 0.16535434126853943, 0);
  g->SplitDim(1299, 1301, 2, {2,256});
  g->Transpose(1301, 1302, {0,2,1,3});
  g->Unary(ynn_unary_square, 1302, 1303);
  g->Reduce(ynn_reduce_sum, 1303, 7514, {3}, true);
  g->ShapeProduct(1303, 7513, {3});
  g->Binary(ynn_binary_divide, 7514, 7513, 1304);
  g->Binary(ynn_binary_add, 1304, 8647, 1305);
  g->Unary(ynn_unary_rsqrt, 1305, 1306);
  g->Binary(ynn_binary_multiply, 1302, 1306, 1307);
}

// Scope: "Layer16 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(1297, 1308, 0.005929071456193924, 0);
  g->Append(8604, 1308, 9453, 2, s2, slinky::expr(int64_t{1}));
  g->View(9453, 9501, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(1307, 1310, 0.047244105488061905, 0);
  g->Append(8628, 1310, 9477, 2, s2, slinky::expr(int64_t{1}));
  g->View(9477, 9525, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer16 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(8890, 5533, {1,0});
  g->Binary(ynn_binary_multiply, 5519, 5532, 5529);
  g->Dot(1279, 5533, YNN_INVALID_VALUE_ID, 5528, 1);
  g->DequantizeTensor(5528, YNN_INVALID_VALUE_ID, 5529, 5530);
  g->QuantizeTensor(5530, 8595, 5531, 1311);
  g->Dequantize(1311, 1312, 0.1761811226606369, 0);
  g->SplitDim(1312, 1313, 2, {8,256});
  g->Transpose(1313, 1314, {0,2,1,3});
  g->Unary(ynn_unary_square, 1314, 1315);
  g->Reduce(ynn_reduce_sum, 1315, 7516, {3}, true);
  g->ShapeProduct(1315, 7515, {3});
  g->Binary(ynn_binary_divide, 7516, 7515, 1316);
  g->Binary(ynn_binary_add, 1316, 8647, 1318);
  g->Unary(ynn_unary_rsqrt, 1318, 1319);
  g->Binary(ynn_binary_multiply, 1314, 1319, 1320);
  g->Binary(ynn_binary_multiply, 1320, 8889, 1321);
  g->Slice(1321, 1322, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1321, 1323, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1323, 1324);
  g->Concat({1324,1322}, 1325, 3);
  g->Binary(ynn_binary_multiply, 1321, 3141, 1326);
  g->Binary(ynn_binary_multiply, 1325, 4217, 1327);
  g->Binary(ynn_binary_add, 1326, 1327, 1329);
}

// Scope: "Layer16 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9501, 1330, 0.005929071456193924, 0);
  g->Dequantize(9525, 1331, 0.047244105488061905, 0);
  g->Slice(1329, 1332, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(1330, 1333, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(1331, 1334, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(1332, 1333, 1335, false, true);
  g->Mask(1335, 8668, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8668, 7520, {-1}, true);
  g->Binary(ynn_binary_subtract, 8668, 7520, 7517);
  g->Unary(ynn_unary_exp, 7517, 7518);
  g->Reduce(ynn_reduce_sum, 7518, 7521, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 7521, 7519);
  g->Binary(ynn_binary_multiply, 7518, 7519, 1336);
  g->Matmul(1336, 1334, 1337, false, false);
  g->Slice(1329, 1339, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(1330, 1340, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(1331, 1341, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(1339, 1340, 1342, false, true);
  g->Mask(1342, 8669, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8669, 7525, {-1}, true);
  g->Binary(ynn_binary_subtract, 8669, 7525, 7522);
  g->Unary(ynn_unary_exp, 7522, 7523);
  g->Reduce(ynn_reduce_sum, 7523, 7526, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 7526, 7524);
  g->Binary(ynn_binary_multiply, 7523, 7524, 1343);
  g->Matmul(1343, 1341, 1344, false, false);
  g->Concat({1337,1344}, 1345, 1);
}

// Scope: "Layer16 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1345, 1346, {0,2,1,3});
  g->FuseDims(1346, 1347, 2, 2);
  g->Quantize(1347, 1350, 0.025221465155482292, 0);
  g->Transpose(8888, 5540, {1,0});
  g->Binary(ynn_binary_multiply, 5537, 5539, 5535);
  g->Dot(1350, 5540, YNN_INVALID_VALUE_ID, 5534, 1);
  g->DequantizeTensor(5534, YNN_INVALID_VALUE_ID, 5535, 5536);
  g->QuantizeTensor(5536, 8595, 5538, 1351);
  g->Dequantize(1351, 1352, 0.03670656308531761, 0);
}

// Scope: "Layer16 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1272, 1273);
  g->Reduce(ynn_reduce_sum, 1273, 7505, {2}, true);
  g->ShapeProduct(1273, 7504, {2});
  g->Binary(ynn_binary_divide, 7505, 7504, 1274);
  g->Binary(ynn_binary_add, 1274, 8647, 1275);
  g->Unary(ynn_unary_rsqrt, 1275, 1276);
  g->Binary(ynn_binary_multiply, 1272, 1276, 1277);
  g->Binary(ynn_binary_multiply, 1277, 8875, 1278);
  BuildLayer16AttentionKvProjection(ctx);
  BuildLayer16AttentionCacheUpdate(ctx);
  BuildLayer16AttentionQueryProjection(ctx);
  BuildLayer16AttentionSdpa(ctx);
  BuildLayer16AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1352, 1353);
  g->Reduce(ynn_reduce_sum, 1353, 7528, {2}, true);
  g->ShapeProduct(1353, 7527, {2});
  g->Binary(ynn_binary_divide, 7528, 7527, 1354);
  g->Binary(ynn_binary_add, 1354, 8647, 1355);
  g->Unary(ynn_unary_rsqrt, 1355, 1356);
  g->Binary(ynn_binary_multiply, 1352, 1356, 1357);
  g->Binary(ynn_binary_multiply, 1357, 8882, 1358);
  g->Binary(ynn_binary_add, 1358, 1272, 1359);
}

// Scope: "Layer16 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1359, 1361);
  g->Reduce(ynn_reduce_sum, 1361, 7530, {2}, true);
  g->ShapeProduct(1361, 7529, {2});
  g->Binary(ynn_binary_divide, 7530, 7529, 1362);
  g->Binary(ynn_binary_add, 1362, 8647, 1363);
  g->Unary(ynn_unary_rsqrt, 1363, 1364);
  g->Binary(ynn_binary_multiply, 1359, 1364, 1365);
  g->Binary(ynn_binary_multiply, 1365, 8885, 1366);
  g->Quantize(1366, 1367, 0.013054176233708858, 0);
  g->Transpose(8879, 5554, {1,0});
  g->Binary(ynn_binary_multiply, 5551, 5553, 5549);
  g->Dot(1367, 5554, YNN_INVALID_VALUE_ID, 5548, 1);
  g->DequantizeTensor(5548, YNN_INVALID_VALUE_ID, 5549, 5550);
  g->QuantizeTensor(5550, 8595, 5552, 1368);
  g->Dequantize(1368, 1369, 0.01464075781404972, 0);
  g->Transpose(8878, 5559, {1,0});
  g->Binary(ynn_binary_multiply, 5551, 5558, 5556);
  g->Dot(1367, 5559, YNN_INVALID_VALUE_ID, 5555, 1);
  g->DequantizeTensor(5555, YNN_INVALID_VALUE_ID, 5556, 5557);
  g->QuantizeTensor(5557, 8595, 5552, 1371);
  g->Dequantize(1371, 1372, 0.01464075781404972, 0);
  g->Polynomial(1372, 7533, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7533, 7534);
  g->Binary(ynn_binary_add, 7534, 7161, 7531);
  g->Binary(ynn_binary_multiply, 1372, 7173, 7532);
  g->Binary(ynn_binary_multiply, 7532, 7531, 1373);
  g->Binary(ynn_binary_multiply, 1369, 1373, 1374);
  g->Quantize(1374, 1375, 0.010150108486413956, 0);
  g->Transpose(8877, 5566, {1,0});
  g->Binary(ynn_binary_multiply, 5563, 5565, 5561);
  g->Dot(1375, 5566, YNN_INVALID_VALUE_ID, 5560, 1);
  g->DequantizeTensor(5560, YNN_INVALID_VALUE_ID, 5561, 5562);
  g->QuantizeTensor(5562, 8595, 5564, 1376);
  g->Dequantize(1376, 1377, 0.006600875407457352, 0);
  g->Unary(ynn_unary_square, 1377, 1378);
  g->Reduce(ynn_reduce_sum, 1378, 7536, {2}, true);
  g->ShapeProduct(1378, 7535, {2});
  g->Binary(ynn_binary_divide, 7536, 7535, 1379);
  g->Binary(ynn_binary_add, 1379, 8647, 1380);
  g->Unary(ynn_unary_rsqrt, 1380, 1382);
  g->Binary(ynn_binary_multiply, 1377, 1382, 1383);
  g->Binary(ynn_binary_multiply, 1383, 8883, 1384);
  g->Binary(ynn_binary_add, 1384, 1359, 1385);
}

// Scope: "Layer16 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 1386, {0,0,16,0}, {-1,-1,1,-1});
  g->Reshape(1386, 1387, {1,1,256});
  g->Unary(ynn_unary_square, 1387, 1388);
  g->Reduce(ynn_reduce_sum, 1388, 7538, {2}, true);
  g->ShapeProduct(1388, 7537, {2});
  g->Binary(ynn_binary_divide, 7538, 7537, 1389);
  g->Binary(ynn_binary_add, 1389, 8647, 1390);
  g->Unary(ynn_unary_rsqrt, 1390, 1391);
  g->Binary(ynn_binary_multiply, 1387, 1391, 1393);
  g->Binary(ynn_binary_multiply, 1393, 9401, 1394);
  g->Binary(ynn_binary_multiply, 9410, 8651, 1395);
  g->Binary(ynn_binary_add, 1394, 1395, 1396);
  g->Binary(ynn_binary_multiply, 1396, 8645, 1397);
  g->Quantize(1385, 1398, 0.3792611062526703, 0);
  g->Transpose(8880, 5573, {1,0});
  g->Binary(ynn_binary_multiply, 5570, 5572, 5568);
  g->Dot(1398, 5573, YNN_INVALID_VALUE_ID, 5567, 1);
  g->DequantizeTensor(5567, YNN_INVALID_VALUE_ID, 5568, 5569);
  g->QuantizeTensor(5569, 8595, 5571, 1399);
  g->Dequantize(1399, 1400, 0.10433071851730347, 0);
  g->Polynomial(1400, 7543, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7543, 7544);
  g->Binary(ynn_binary_add, 7544, 7161, 7541);
  g->Binary(ynn_binary_multiply, 1400, 7173, 7542);
  g->Binary(ynn_binary_multiply, 7542, 7541, 1401);
  g->Binary(ynn_binary_multiply, 1401, 1397, 1402);
  g->Quantize(1402, 1404, 0.43897637724876404, 0);
  g->Transpose(8881, 5580, {1,0});
  g->Binary(ynn_binary_multiply, 5577, 5579, 5575);
  g->Dot(1404, 5580, YNN_INVALID_VALUE_ID, 5574, 1);
  g->DequantizeTensor(5574, YNN_INVALID_VALUE_ID, 5575, 5576);
  g->QuantizeTensor(5576, 8595, 5578, 1405);
  g->Dequantize(1405, 1406, 0.08895451575517654, 0);
  g->Unary(ynn_unary_square, 1406, 1407);
  g->Reduce(ynn_reduce_sum, 1407, 7546, {2}, true);
  g->ShapeProduct(1407, 7545, {2});
  g->Binary(ynn_binary_divide, 7546, 7545, 1408);
  g->Binary(ynn_binary_add, 1408, 8647, 1409);
  g->Unary(ynn_unary_rsqrt, 1409, 1410);
  g->Binary(ynn_binary_multiply, 1406, 1410, 1411);
  g->Binary(ynn_binary_multiply, 1411, 8884, 1412);
  g->Binary(ynn_binary_add, 1385, 1412, 1413);
  g->Binary(ynn_binary_multiply, 1413, 8876, 1415);
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
  g->Transpose(8904, 5587, {1,0});
  g->Binary(ynn_binary_multiply, 5584, 5586, 5582);
  g->Dot(1422, 5587, YNN_INVALID_VALUE_ID, 5581, 1);
  g->DequantizeTensor(5581, YNN_INVALID_VALUE_ID, 5582, 5583);
  g->QuantizeTensor(5583, 8595, 5585, 1423);
  g->Dequantize(1423, 1424, 0.1210630014538765, 0);
  g->SplitDim(1424, 1426, 2, {2,512});
  g->Transpose(1426, 1427, {0,2,1,3});
  g->Unary(ynn_unary_square, 1427, 1428);
  g->Reduce(ynn_reduce_sum, 1428, 7550, {3}, true);
  g->ShapeProduct(1428, 7549, {3});
  g->Binary(ynn_binary_divide, 7550, 7549, 1429);
  g->Binary(ynn_binary_add, 1429, 8647, 1430);
  g->Unary(ynn_unary_rsqrt, 1430, 1431);
  g->Binary(ynn_binary_multiply, 1427, 1431, 1432);
  g->Binary(ynn_binary_multiply, 1432, 8903, 1433);
  g->Slice(1433, 1434, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(1433, 1435, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 1435, 1437);
  g->Concat({1437,1434}, 1438, 3);
  g->Binary(ynn_binary_multiply, 1433, 4830, 1439);
  g->Binary(ynn_binary_multiply, 1438, 2, 1440);
  g->Binary(ynn_binary_add, 1439, 1440, 1441);
  g->Transpose(8908, 5592, {1,0});
  g->Binary(ynn_binary_multiply, 5584, 5591, 5589);
  g->Dot(1422, 5592, YNN_INVALID_VALUE_ID, 5588, 1);
  g->DequantizeTensor(5588, YNN_INVALID_VALUE_ID, 5589, 5590);
  g->QuantizeTensor(5590, 8595, 5585, 1442);
  g->Dequantize(1442, 1443, 0.1210630014538765, 0);
  g->SplitDim(1443, 1444, 2, {2,512});
  g->Transpose(1444, 1445, {0,2,1,3});
  g->Unary(ynn_unary_square, 1445, 1447);
  g->Reduce(ynn_reduce_sum, 1447, 7552, {3}, true);
  g->ShapeProduct(1447, 7551, {3});
  g->Binary(ynn_binary_divide, 7552, 7551, 1448);
  g->Binary(ynn_binary_add, 1448, 8647, 1449);
  g->Unary(ynn_unary_rsqrt, 1449, 1450);
  g->Binary(ynn_binary_multiply, 1445, 1450, 1451);
}

// Scope: "Layer17 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(1441, 1452, 0.001110153621993959, 0);
  g->Append(8605, 1452, 9454, 2, s2, slinky::expr(int64_t{1}));
  g->View(9454, 9502, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(1451, 1453, 0.01785714365541935, 0);
  g->Append(8629, 1453, 9478, 2, s2, slinky::expr(int64_t{1}));
  g->View(9478, 9526, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer17 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(8907, 5598, {1,0});
  g->Binary(ynn_binary_multiply, 5584, 5597, 5594);
  g->Dot(1422, 5598, YNN_INVALID_VALUE_ID, 5593, 1);
  g->DequantizeTensor(5593, YNN_INVALID_VALUE_ID, 5594, 5595);
  g->QuantizeTensor(5595, 8595, 5596, 1456);
  g->Dequantize(1456, 1457, 0.17027559876441956, 0);
  g->SplitDim(1457, 1458, 2, {8,512});
  g->Transpose(1458, 1459, {0,2,1,3});
  g->Unary(ynn_unary_square, 1459, 1460);
  g->Reduce(ynn_reduce_sum, 1460, 7554, {3}, true);
  g->ShapeProduct(1460, 7553, {3});
  g->Binary(ynn_binary_divide, 7554, 7553, 1461);
  g->Binary(ynn_binary_add, 1461, 8647, 1462);
  g->Unary(ynn_unary_rsqrt, 1462, 1463);
  g->Binary(ynn_binary_multiply, 1459, 1463, 1465);
  g->Binary(ynn_binary_multiply, 1465, 8906, 1466);
  g->Slice(1466, 1467, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(1466, 1468, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 1468, 1469);
  g->Concat({1469,1467}, 1470, 3);
  g->Binary(ynn_binary_multiply, 1466, 4830, 1471);
  g->Binary(ynn_binary_multiply, 1470, 2, 1472);
  g->Binary(ynn_binary_add, 1471, 1472, 1473);
}

// Scope: "Layer17 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9502, 1474, 0.001110153621993959, 0);
  g->Dequantize(9526, 1476, 0.01785714365541935, 0);
  g->Slice(1473, 1477, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(1474, 1478, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(1476, 1479, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(1477, 1478, 1480, false, true);
  g->Mask(1480, 8670, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 8670, 7560, {-1}, true);
  g->Binary(ynn_binary_subtract, 8670, 7560, 7557);
  g->Unary(ynn_unary_exp, 7557, 7558);
  g->Reduce(ynn_reduce_sum, 7558, 7561, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 7561, 7559);
  g->Binary(ynn_binary_multiply, 7558, 7559, 1481);
  g->Matmul(1481, 1479, 1482, false, false);
  g->Slice(1473, 1483, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(1474, 1484, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(1476, 1486, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(1483, 1484, 1487, false, true);
  g->Mask(1487, 8671, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 8671, 7565, {-1}, true);
  g->Binary(ynn_binary_subtract, 8671, 7565, 7562);
  g->Unary(ynn_unary_exp, 7562, 7563);
  g->Reduce(ynn_reduce_sum, 7563, 7566, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 7566, 7564);
  g->Binary(ynn_binary_multiply, 7563, 7564, 1488);
  g->Matmul(1488, 1486, 1489, false, false);
  g->Concat({1482,1489}, 1490, 1);
}

// Scope: "Layer17 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1490, 1491, {0,2,1,3});
  g->FuseDims(1491, 1492, 2, 2);
  g->Quantize(1492, 1493, 0.01771654561161995, 0);
  g->Transpose(8905, 5605, {1,0});
  g->Binary(ynn_binary_multiply, 5602, 5604, 5600);
  g->Dot(1493, 5605, YNN_INVALID_VALUE_ID, 5599, 1);
  g->DequantizeTensor(5599, YNN_INVALID_VALUE_ID, 5600, 5601);
  g->QuantizeTensor(5601, 8595, 5603, 1494);
  g->Dequantize(1494, 1496, 0.025433415547013283, 0);
}

// Scope: "Layer17 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1415, 1416);
  g->Reduce(ynn_reduce_sum, 1416, 7548, {2}, true);
  g->ShapeProduct(1416, 7547, {2});
  g->Binary(ynn_binary_divide, 7548, 7547, 1417);
  g->Binary(ynn_binary_add, 1417, 8647, 1418);
  g->Unary(ynn_unary_rsqrt, 1418, 1419);
  g->Binary(ynn_binary_multiply, 1415, 1419, 1420);
  g->Binary(ynn_binary_multiply, 1420, 8892, 1421);
  BuildLayer17AttentionKvProjection(ctx);
  BuildLayer17AttentionCacheUpdate(ctx);
  BuildLayer17AttentionQueryProjection(ctx);
  BuildLayer17AttentionSdpa(ctx);
  BuildLayer17AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1496, 1497);
  g->Reduce(ynn_reduce_sum, 1497, 7568, {2}, true);
  g->ShapeProduct(1497, 7567, {2});
  g->Binary(ynn_binary_divide, 7568, 7567, 1498);
  g->Binary(ynn_binary_add, 1498, 8647, 1499);
  g->Unary(ynn_unary_rsqrt, 1499, 1500);
  g->Binary(ynn_binary_multiply, 1496, 1500, 1501);
  g->Binary(ynn_binary_multiply, 1501, 8899, 1502);
  g->Binary(ynn_binary_add, 1502, 1415, 1503);
}

// Scope: "Layer17 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1503, 1504);
  g->Reduce(ynn_reduce_sum, 1504, 7570, {2}, true);
  g->ShapeProduct(1504, 7569, {2});
  g->Binary(ynn_binary_divide, 7570, 7569, 1505);
  g->Binary(ynn_binary_add, 1505, 8647, 1507);
  g->Unary(ynn_unary_rsqrt, 1507, 1508);
  g->Binary(ynn_binary_multiply, 1503, 1508, 1509);
  g->Binary(ynn_binary_multiply, 1509, 8902, 1510);
  g->Quantize(1510, 1511, 0.010834499262273312, 0);
  g->Transpose(8896, 5612, {1,0});
  g->Binary(ynn_binary_multiply, 5609, 5611, 5607);
  g->Dot(1511, 5612, YNN_INVALID_VALUE_ID, 5606, 1);
  g->DequantizeTensor(5606, YNN_INVALID_VALUE_ID, 5607, 5608);
  g->QuantizeTensor(5608, 8595, 5610, 1512);
  g->Dequantize(1512, 1513, 0.012979833409190178, 0);
  g->Transpose(8895, 5617, {1,0});
  g->Binary(ynn_binary_multiply, 5609, 5616, 5614);
  g->Dot(1511, 5617, YNN_INVALID_VALUE_ID, 5613, 1);
  g->DequantizeTensor(5613, YNN_INVALID_VALUE_ID, 5614, 5615);
  g->QuantizeTensor(5615, 8595, 5610, 1514);
  g->Dequantize(1514, 1515, 0.012979833409190178, 0);
  g->Polynomial(1515, 7573, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7573, 7574);
  g->Binary(ynn_binary_add, 7574, 7161, 7571);
  g->Binary(ynn_binary_multiply, 1515, 7173, 7572);
  g->Binary(ynn_binary_multiply, 7572, 7571, 1517);
  g->Binary(ynn_binary_multiply, 1513, 1517, 1518);
  g->Quantize(1518, 1519, 0.005751732271164656, 0);
  g->Transpose(8894, 5624, {1,0});
  g->Binary(ynn_binary_multiply, 5621, 5623, 5619);
  g->Dot(1519, 5624, YNN_INVALID_VALUE_ID, 5618, 1);
  g->DequantizeTensor(5618, YNN_INVALID_VALUE_ID, 5619, 5620);
  g->QuantizeTensor(5620, 8595, 5622, 1520);
  g->Dequantize(1520, 1521, 0.0032109280582517385, 0);
  g->Unary(ynn_unary_square, 1521, 1522);
  g->Reduce(ynn_reduce_sum, 1522, 7576, {2}, true);
  g->ShapeProduct(1522, 7575, {2});
  g->Binary(ynn_binary_divide, 7576, 7575, 1523);
  g->Binary(ynn_binary_add, 1523, 8647, 1524);
  g->Unary(ynn_unary_rsqrt, 1524, 1525);
  g->Binary(ynn_binary_multiply, 1521, 1525, 1526);
  g->Binary(ynn_binary_multiply, 1526, 8900, 1528);
  g->Binary(ynn_binary_add, 1528, 1503, 1529);
}

// Scope: "Layer17 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 1530, {0,0,17,0}, {-1,-1,1,-1});
  g->Reshape(1530, 1531, {1,1,256});
  g->Unary(ynn_unary_square, 1531, 1532);
  g->Reduce(ynn_reduce_sum, 1532, 7578, {2}, true);
  g->ShapeProduct(1532, 7577, {2});
  g->Binary(ynn_binary_divide, 7578, 7577, 1533);
  g->Binary(ynn_binary_add, 1533, 8647, 1534);
  g->Unary(ynn_unary_rsqrt, 1534, 1535);
  g->Binary(ynn_binary_multiply, 1531, 1535, 1536);
  g->Binary(ynn_binary_multiply, 1536, 9401, 1537);
  g->Binary(ynn_binary_multiply, 9411, 8651, 1539);
  g->Binary(ynn_binary_add, 1537, 1539, 1540);
  g->Binary(ynn_binary_multiply, 1540, 8645, 1541);
  g->Quantize(1529, 1542, 0.23138143122196198, 0);
  g->Transpose(8897, 5638, {1,0});
  g->Binary(ynn_binary_multiply, 5635, 5637, 5633);
  g->Dot(1542, 5638, YNN_INVALID_VALUE_ID, 5632, 1);
  g->DequantizeTensor(5632, YNN_INVALID_VALUE_ID, 5633, 5634);
  g->QuantizeTensor(5634, 8595, 5636, 1543);
  g->Dequantize(1543, 1544, 0.08070866763591766, 0);
  g->Polynomial(1544, 7581, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7581, 7582);
  g->Binary(ynn_binary_add, 7582, 7161, 7579);
  g->Binary(ynn_binary_multiply, 1544, 7173, 7580);
  g->Binary(ynn_binary_multiply, 7580, 7579, 1545);
  g->Binary(ynn_binary_multiply, 1545, 1541, 1546);
  g->Quantize(1546, 1547, 0.4606299102306366, 0);
  g->Transpose(8898, 5645, {1,0});
  g->Binary(ynn_binary_multiply, 5642, 5644, 5640);
  g->Dot(1547, 5645, YNN_INVALID_VALUE_ID, 5639, 1);
  g->DequantizeTensor(5639, YNN_INVALID_VALUE_ID, 5640, 5641);
  g->QuantizeTensor(5641, 8595, 5643, 1548);
  g->Dequantize(1548, 1549, 0.13702630996704102, 0);
  g->Unary(ynn_unary_square, 1549, 1550);
  g->Reduce(ynn_reduce_sum, 1550, 7584, {2}, true);
  g->ShapeProduct(1550, 7583, {2});
  g->Binary(ynn_binary_divide, 7584, 7583, 1551);
  g->Binary(ynn_binary_add, 1551, 8647, 1552);
  g->Unary(ynn_unary_rsqrt, 1552, 1553);
  g->Binary(ynn_binary_multiply, 1549, 1553, 1554);
  g->Binary(ynn_binary_multiply, 1554, 8901, 1555);
  g->Binary(ynn_binary_add, 1529, 1555, 1556);
  g->Binary(ynn_binary_multiply, 1556, 8893, 1557);
}

// Scope: "Layer17"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17(Context& ctx) {
  BuildLayer17Attention(ctx);
  BuildLayer17Mlp(ctx);
  BuildLayer17PerLayerEmbedding(ctx);
}

}  // namespace BuildGemma4DecodeSource
