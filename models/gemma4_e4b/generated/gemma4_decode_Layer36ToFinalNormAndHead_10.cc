// Generated YNNPACK builder; do not edit.
#include "gemma4_decode_builder.h"

namespace BuildGemma4DecodeSource {

// Scope: "Layer36 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer36AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(3770, 3771, 0.2735130488872528, 0);
  g->Transpose(9226, 6646, {1,0});
  g->Binary(ynn_binary_multiply, 6643, 6645, 6641);
  g->Dot(3771, 6646, YNN_INVALID_VALUE_ID, 6640, 1);
  g->DequantizeTensor(6640, YNN_INVALID_VALUE_ID, 6641, 6642);
  g->QuantizeTensor(6642, 8595, 6644, 3772);
  g->Dequantize(3772, 3773, 0.5118110179901123, 0);
  g->SplitDim(3773, 3774, 2, {8,256});
  g->Transpose(3774, 3775, {0,2,1,3});
  g->Unary(ynn_unary_square, 3775, 3776);
  g->Reduce(ynn_reduce_sum, 3776, 8246, {3}, true);
  g->ShapeProduct(3776, 8245, {3});
  g->Binary(ynn_binary_divide, 8246, 8245, 3777);
  g->Binary(ynn_binary_add, 3777, 8647, 3778);
  g->Unary(ynn_unary_rsqrt, 3778, 3779);
  g->Binary(ynn_binary_multiply, 3775, 3779, 3781);
  g->Binary(ynn_binary_multiply, 3781, 9225, 3782);
  g->Slice(3782, 3783, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3782, 3784, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3784, 3785);
  g->Concat({3785,3783}, 3786, 3);
  g->Binary(ynn_binary_multiply, 3782, 3141, 3787);
  g->Binary(ynn_binary_multiply, 3786, 4217, 3788);
  g->Binary(ynn_binary_add, 3787, 3788, 3789);
}

// Scope: "Layer36 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer36AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9508, 3790, 0.0059552486054599285, 0);
  g->Dequantize(9532, 3793, 0.047244105488061905, 0);
  g->Slice(3789, 3794, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(3790, 3795, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(3793, 3796, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(3794, 3795, 3797, false, true);
  g->Mask(3797, 8712, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8712, 8252, {-1}, true);
  g->Binary(ynn_binary_subtract, 8712, 8252, 8249);
  g->Unary(ynn_unary_exp, 8249, 8250);
  g->Reduce(ynn_reduce_sum, 8250, 8253, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 8253, 8251);
  g->Binary(ynn_binary_multiply, 8250, 8251, 3798);
  g->Matmul(3798, 3796, 3799, false, false);
  g->Slice(3789, 3800, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(3790, 3801, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(3793, 3803, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(3800, 3801, 3804, false, true);
  g->Mask(3804, 8713, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8713, 8257, {-1}, true);
  g->Binary(ynn_binary_subtract, 8713, 8257, 8254);
  g->Unary(ynn_unary_exp, 8254, 8255);
  g->Reduce(ynn_reduce_sum, 8255, 8258, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 8258, 8256);
  g->Binary(ynn_binary_multiply, 8255, 8256, 3805);
  g->Matmul(3805, 3803, 3806, false, false);
  g->Concat({3799,3806}, 3807, 1);
}

// Scope: "Layer36 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer36AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(3807, 3808, {0,2,1,3});
  g->FuseDims(3808, 3809, 2, 2);
  g->Quantize(3809, 3810, 0.019685048609972, 0);
  g->Transpose(9224, 6652, {1,0});
  g->Binary(ynn_binary_multiply, 6500, 6651, 6648);
  g->Dot(3810, 6652, YNN_INVALID_VALUE_ID, 6647, 1);
  g->DequantizeTensor(6647, YNN_INVALID_VALUE_ID, 6648, 6649);
  g->QuantizeTensor(6649, 8595, 6650, 3811);
  g->Dequantize(3811, 3813, 0.13249905407428741, 0);
}

// Scope: "Layer36 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer36Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3763, 3764);
  g->Reduce(ynn_reduce_sum, 3764, 8244, {2}, true);
  g->ShapeProduct(3764, 8243, {2});
  g->Binary(ynn_binary_divide, 8244, 8243, 3765);
  g->Binary(ynn_binary_add, 3765, 8647, 3766);
  g->Unary(ynn_unary_rsqrt, 3766, 3767);
  g->Binary(ynn_binary_multiply, 3763, 3767, 3768);
  g->Binary(ynn_binary_multiply, 3768, 9213, 3770);
  BuildLayer36AttentionQueryProjection(ctx);
  BuildLayer36AttentionSdpa(ctx);
  BuildLayer36AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 3813, 3814);
  g->Reduce(ynn_reduce_sum, 3814, 8260, {2}, true);
  g->ShapeProduct(3814, 8259, {2});
  g->Binary(ynn_binary_divide, 8260, 8259, 3815);
  g->Binary(ynn_binary_add, 3815, 8647, 3816);
  g->Unary(ynn_unary_rsqrt, 3816, 3817);
  g->Binary(ynn_binary_multiply, 3813, 3817, 3818);
  g->Binary(ynn_binary_multiply, 3818, 9220, 3819);
  g->Binary(ynn_binary_add, 3819, 3763, 3820);
}

// Scope: "Layer36 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer36Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3820, 3821);
  g->Reduce(ynn_reduce_sum, 3821, 8262, {2}, true);
  g->ShapeProduct(3821, 8261, {2});
  g->Binary(ynn_binary_divide, 8262, 8261, 3822);
  g->Binary(ynn_binary_add, 3822, 8647, 3824);
  g->Unary(ynn_unary_rsqrt, 3824, 3825);
  g->Binary(ynn_binary_multiply, 3820, 3825, 3826);
  g->Binary(ynn_binary_multiply, 3826, 9223, 3827);
  g->Quantize(3827, 3828, 0.014071965590119362, 0);
  g->Transpose(9217, 6659, {1,0});
  g->Binary(ynn_binary_multiply, 6656, 6658, 6654);
  g->Dot(3828, 6659, YNN_INVALID_VALUE_ID, 6653, 1);
  g->DequantizeTensor(6653, YNN_INVALID_VALUE_ID, 6654, 6655);
  g->QuantizeTensor(6655, 8595, 6657, 3829);
  g->Dequantize(3829, 3830, 0.017470480874180794, 0);
  g->Transpose(9216, 6664, {1,0});
  g->Binary(ynn_binary_multiply, 6656, 6663, 6661);
  g->Dot(3828, 6664, YNN_INVALID_VALUE_ID, 6660, 1);
  g->DequantizeTensor(6660, YNN_INVALID_VALUE_ID, 6661, 6662);
  g->QuantizeTensor(6662, 8595, 6657, 3831);
  g->Dequantize(3831, 3832, 0.017470480874180794, 0);
  g->Polynomial(3832, 8265, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8265, 8266);
  g->Binary(ynn_binary_add, 8266, 7161, 8263);
  g->Binary(ynn_binary_multiply, 3832, 7173, 8264);
  g->Binary(ynn_binary_multiply, 8264, 8263, 3833);
  g->Binary(ynn_binary_multiply, 3830, 3833, 3834);
  g->Quantize(3834, 3835, 0.013102864846587181, 0);
  g->Transpose(9215, 6671, {1,0});
  g->Binary(ynn_binary_multiply, 6668, 6670, 6666);
  g->Dot(3835, 6671, YNN_INVALID_VALUE_ID, 6665, 1);
  g->DequantizeTensor(6665, YNN_INVALID_VALUE_ID, 6666, 6667);
  g->QuantizeTensor(6667, 8595, 6669, 3836);
  g->Dequantize(3836, 3837, 0.008950071409344673, 0);
  g->Unary(ynn_unary_square, 3837, 3838);
  g->Reduce(ynn_reduce_sum, 3838, 8268, {2}, true);
  g->ShapeProduct(3838, 8267, {2});
  g->Binary(ynn_binary_divide, 8268, 8267, 3839);
  g->Binary(ynn_binary_add, 3839, 8647, 3840);
  g->Unary(ynn_unary_rsqrt, 3840, 3841);
  g->Binary(ynn_binary_multiply, 3837, 3841, 3842);
  g->Binary(ynn_binary_multiply, 3842, 9221, 3843);
  g->Binary(ynn_binary_add, 3843, 3820, 3844);
}

// Scope: "Layer36 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer36PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 3845, {0,0,36,0}, {-1,-1,1,-1});
  g->Reshape(3845, 3846, {1,1,256});
  g->Unary(ynn_unary_square, 3846, 3847);
  g->Reduce(ynn_reduce_sum, 3847, 8270, {2}, true);
  g->ShapeProduct(3847, 8269, {2});
  g->Binary(ynn_binary_divide, 8270, 8269, 3848);
  g->Binary(ynn_binary_add, 3848, 8647, 3849);
  g->Unary(ynn_unary_rsqrt, 3849, 3850);
  g->Binary(ynn_binary_multiply, 3846, 3850, 3851);
  g->Binary(ynn_binary_multiply, 3851, 9401, 3852);
  g->Binary(ynn_binary_multiply, 9432, 8651, 3854);
  g->Binary(ynn_binary_add, 3852, 3854, 3855);
  g->Binary(ynn_binary_multiply, 3855, 8645, 3856);
  g->Quantize(3844, 3857, 0.38496658205986023, 0);
  g->Transpose(9218, 6677, {1,0});
  g->Binary(ynn_binary_multiply, 6675, 6676, 6673);
  g->Dot(3857, 6677, YNN_INVALID_VALUE_ID, 6672, 1);
  g->DequantizeTensor(6672, YNN_INVALID_VALUE_ID, 6673, 6674);
  g->QuantizeTensor(6674, 8595, 6163, 3858);
  g->Dequantize(3858, 3859, 0.19685040414333344, 0);
  g->Polynomial(3859, 8273, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8273, 8274);
  g->Binary(ynn_binary_add, 8274, 7161, 8271);
  g->Binary(ynn_binary_multiply, 3859, 7173, 8272);
  g->Binary(ynn_binary_multiply, 8272, 8271, 3860);
  g->Binary(ynn_binary_multiply, 3860, 3856, 3861);
  g->Quantize(3861, 3862, 2.6299211978912354, 0);
  g->Transpose(9219, 6684, {1,0});
  g->Binary(ynn_binary_multiply, 6681, 6683, 6679);
  g->Dot(3862, 6684, YNN_INVALID_VALUE_ID, 6678, 1);
  g->DequantizeTensor(6678, YNN_INVALID_VALUE_ID, 6679, 6680);
  g->QuantizeTensor(6680, 8595, 6682, 3863);
  g->Dequantize(3863, 3864, 0.24539968371391296, 0);
  g->Unary(ynn_unary_square, 3864, 3865);
  g->Reduce(ynn_reduce_sum, 3865, 8276, {2}, true);
  g->ShapeProduct(3865, 8275, {2});
  g->Binary(ynn_binary_divide, 8276, 8275, 3866);
  g->Binary(ynn_binary_add, 3866, 8647, 3867);
  g->Unary(ynn_unary_rsqrt, 3867, 3868);
  g->Binary(ynn_binary_multiply, 3864, 3868, 3869);
  g->Binary(ynn_binary_multiply, 3869, 9222, 3870);
  g->Binary(ynn_binary_add, 3844, 3870, 3871);
  g->Binary(ynn_binary_multiply, 3871, 9214, 3872);
}

// Scope: "Layer36"
LAB_YNN_BUILDER_NOINLINE void BuildLayer36(Context& ctx) {
  BuildLayer36Attention(ctx);
  BuildLayer36Mlp(ctx);
  BuildLayer36PerLayerEmbedding(ctx);
}

// Scope: "Layer37 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer37AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(3878, 3879, 0.7991782426834106, 0);
  g->Transpose(9240, 6691, {1,0});
  g->Binary(ynn_binary_multiply, 6688, 6690, 6686);
  g->Dot(3879, 6691, YNN_INVALID_VALUE_ID, 6685, 1);
  g->DequantizeTensor(6685, YNN_INVALID_VALUE_ID, 6686, 6687);
  g->QuantizeTensor(6687, 8595, 6689, 3880);
  g->Dequantize(3880, 3881, 0.7244094610214233, 0);
  g->SplitDim(3881, 3882, 2, {8,256});
  g->Transpose(3882, 3883, {0,2,1,3});
  g->Unary(ynn_unary_square, 3883, 3884);
  g->Reduce(ynn_reduce_sum, 3884, 8280, {3}, true);
  g->ShapeProduct(3884, 8279, {3});
  g->Binary(ynn_binary_divide, 8280, 8279, 3885);
  g->Binary(ynn_binary_add, 3885, 8647, 3886);
  g->Unary(ynn_unary_rsqrt, 3886, 3887);
  g->Binary(ynn_binary_multiply, 3883, 3887, 3888);
  g->Binary(ynn_binary_multiply, 3888, 9239, 3889);
  g->Slice(3889, 3890, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3889, 3891, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3891, 3892);
  g->Concat({3892,3890}, 3893, 3);
  g->Binary(ynn_binary_multiply, 3889, 3141, 3896);
  g->Binary(ynn_binary_multiply, 3893, 4217, 3897);
  g->Binary(ynn_binary_add, 3896, 3897, 3898);
}

// Scope: "Layer37 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer37AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9508, 3899, 0.0059552486054599285, 0);
  g->Dequantize(9532, 3900, 0.047244105488061905, 0);
  g->Slice(3898, 3901, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(3899, 3902, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(3900, 3903, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(3901, 3902, 3904, false, true);
  g->Mask(3904, 8714, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8714, 8284, {-1}, true);
  g->Binary(ynn_binary_subtract, 8714, 8284, 8281);
  g->Unary(ynn_unary_exp, 8281, 8282);
  g->Reduce(ynn_reduce_sum, 8282, 8285, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 8285, 8283);
  g->Binary(ynn_binary_multiply, 8282, 8283, 3906);
  g->Matmul(3906, 3903, 3907, false, false);
  g->Slice(3898, 3908, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(3899, 3909, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(3900, 3910, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(3908, 3909, 3911, false, true);
  g->Mask(3911, 8715, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8715, 8289, {-1}, true);
  g->Binary(ynn_binary_subtract, 8715, 8289, 8286);
  g->Unary(ynn_unary_exp, 8286, 8287);
  g->Reduce(ynn_reduce_sum, 8287, 8290, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 8290, 8288);
  g->Binary(ynn_binary_multiply, 8287, 8288, 3912);
  g->Matmul(3912, 3910, 3913, false, false);
  g->Concat({3907,3913}, 3914, 1);
}

// Scope: "Layer37 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer37AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(3914, 3916, {0,2,1,3});
  g->FuseDims(3916, 3917, 2, 2);
  g->Quantize(3917, 3918, 0.019685048609972, 0);
  g->Transpose(9238, 6703, {1,0});
  g->Binary(ynn_binary_multiply, 6500, 6702, 6699);
  g->Dot(3918, 6703, YNN_INVALID_VALUE_ID, 6698, 1);
  g->DequantizeTensor(6698, YNN_INVALID_VALUE_ID, 6699, 6700);
  g->QuantizeTensor(6700, 8595, 6701, 3919);
  g->Dequantize(3919, 3920, 0.09598665684461594, 0);
}

// Scope: "Layer37 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer37Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3872, 3873);
  g->Reduce(ynn_reduce_sum, 3873, 8278, {2}, true);
  g->ShapeProduct(3873, 8277, {2});
  g->Binary(ynn_binary_divide, 8278, 8277, 3874);
  g->Binary(ynn_binary_add, 3874, 8647, 3875);
  g->Unary(ynn_unary_rsqrt, 3875, 3876);
  g->Binary(ynn_binary_multiply, 3872, 3876, 3877);
  g->Binary(ynn_binary_multiply, 3877, 9227, 3878);
  BuildLayer37AttentionQueryProjection(ctx);
  BuildLayer37AttentionSdpa(ctx);
  BuildLayer37AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 3920, 3921);
  g->Reduce(ynn_reduce_sum, 3921, 8292, {2}, true);
  g->ShapeProduct(3921, 8291, {2});
  g->Binary(ynn_binary_divide, 8292, 8291, 3922);
  g->Binary(ynn_binary_add, 3922, 8647, 3923);
  g->Unary(ynn_unary_rsqrt, 3923, 3924);
  g->Binary(ynn_binary_multiply, 3920, 3924, 3925);
  g->Binary(ynn_binary_multiply, 3925, 9234, 3927);
  g->Binary(ynn_binary_add, 3927, 3872, 3928);
}

// Scope: "Layer37 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer37Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3928, 3929);
  g->Reduce(ynn_reduce_sum, 3929, 8294, {2}, true);
  g->ShapeProduct(3929, 8293, {2});
  g->Binary(ynn_binary_divide, 8294, 8293, 3930);
  g->Binary(ynn_binary_add, 3930, 8647, 3931);
  g->Unary(ynn_unary_rsqrt, 3931, 3932);
  g->Binary(ynn_binary_multiply, 3928, 3932, 3933);
  g->Binary(ynn_binary_multiply, 3933, 9237, 3934);
  g->Quantize(3934, 3935, 0.01249794103205204, 0);
  g->Transpose(9231, 6710, {1,0});
  g->Binary(ynn_binary_multiply, 6707, 6709, 6705);
  g->Dot(3935, 6710, YNN_INVALID_VALUE_ID, 6704, 1);
  g->DequantizeTensor(6704, YNN_INVALID_VALUE_ID, 6705, 6706);
  g->QuantizeTensor(6706, 8595, 6708, 3936);
  g->Dequantize(3936, 3938, 0.015009853057563305, 0);
  g->Transpose(9230, 6715, {1,0});
  g->Binary(ynn_binary_multiply, 6707, 6714, 6712);
  g->Dot(3935, 6715, YNN_INVALID_VALUE_ID, 6711, 1);
  g->DequantizeTensor(6711, YNN_INVALID_VALUE_ID, 6712, 6713);
  g->QuantizeTensor(6713, 8595, 6708, 3939);
  g->Dequantize(3939, 3940, 0.015009853057563305, 0);
  g->Polynomial(3940, 8297, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8297, 8298);
  g->Binary(ynn_binary_add, 8298, 7161, 8295);
  g->Binary(ynn_binary_multiply, 3940, 7173, 8296);
  g->Binary(ynn_binary_multiply, 8296, 8295, 3941);
  g->Binary(ynn_binary_multiply, 3938, 3941, 3942);
  g->Quantize(3942, 3943, 0.010642234236001968, 0);
  g->Transpose(9229, 6722, {1,0});
  g->Binary(ynn_binary_multiply, 6719, 6721, 6717);
  g->Dot(3943, 6722, YNN_INVALID_VALUE_ID, 6716, 1);
  g->DequantizeTensor(6716, YNN_INVALID_VALUE_ID, 6717, 6718);
  g->QuantizeTensor(6718, 8595, 6720, 3944);
  g->Dequantize(3944, 3945, 0.00903213769197464, 0);
  g->Unary(ynn_unary_square, 3945, 3946);
  g->Reduce(ynn_reduce_sum, 3946, 8302, {2}, true);
  g->ShapeProduct(3946, 8301, {2});
  g->Binary(ynn_binary_divide, 8302, 8301, 3948);
  g->Binary(ynn_binary_add, 3948, 8647, 3949);
  g->Unary(ynn_unary_rsqrt, 3949, 3950);
  g->Binary(ynn_binary_multiply, 3945, 3950, 3951);
  g->Binary(ynn_binary_multiply, 3951, 9235, 3952);
  g->Binary(ynn_binary_add, 3952, 3928, 3953);
}

// Scope: "Layer37 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer37PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 3954, {0,0,37,0}, {-1,-1,1,-1});
  g->Reshape(3954, 3955, {1,1,256});
  g->Unary(ynn_unary_square, 3955, 3956);
  g->Reduce(ynn_reduce_sum, 3956, 8304, {2}, true);
  g->ShapeProduct(3956, 8303, {2});
  g->Binary(ynn_binary_divide, 8304, 8303, 3957);
  g->Binary(ynn_binary_add, 3957, 8647, 3959);
  g->Unary(ynn_unary_rsqrt, 3959, 3960);
  g->Binary(ynn_binary_multiply, 3955, 3960, 3961);
  g->Binary(ynn_binary_multiply, 3961, 9401, 3962);
  g->Binary(ynn_binary_multiply, 9433, 8651, 3963);
  g->Binary(ynn_binary_add, 3962, 3963, 3964);
  g->Binary(ynn_binary_multiply, 3964, 8645, 3965);
  g->Quantize(3953, 3966, 0.37313586473464966, 0);
  g->Transpose(9232, 6729, {1,0});
  g->Binary(ynn_binary_multiply, 6726, 6728, 6724);
  g->Dot(3966, 6729, YNN_INVALID_VALUE_ID, 6723, 1);
  g->DequantizeTensor(6723, YNN_INVALID_VALUE_ID, 6724, 6725);
  g->QuantizeTensor(6725, 8595, 6727, 3967);
  g->Dequantize(3967, 3968, 0.14960631728172302, 0);
  g->Polynomial(3968, 8307, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8307, 8308);
  g->Binary(ynn_binary_add, 8308, 7161, 8305);
  g->Binary(ynn_binary_multiply, 3968, 7173, 8306);
  g->Binary(ynn_binary_multiply, 8306, 8305, 3970);
  g->Binary(ynn_binary_multiply, 3970, 3965, 3971);
  g->Quantize(3971, 3972, 1.1023621559143066, 0);
  g->Transpose(9233, 6735, {1,0});
  g->Binary(ynn_binary_multiply, 6222, 6734, 6731);
  g->Dot(3972, 6735, YNN_INVALID_VALUE_ID, 6730, 1);
  g->DequantizeTensor(6730, YNN_INVALID_VALUE_ID, 6731, 6732);
  g->QuantizeTensor(6732, 8595, 6733, 3973);
  g->Dequantize(3973, 3974, 0.2224193662405014, 0);
  g->Unary(ynn_unary_square, 3974, 3975);
  g->Reduce(ynn_reduce_sum, 3975, 8310, {2}, true);
  g->ShapeProduct(3975, 8309, {2});
  g->Binary(ynn_binary_divide, 8310, 8309, 3976);
  g->Binary(ynn_binary_add, 3976, 8647, 3977);
  g->Unary(ynn_unary_rsqrt, 3977, 3978);
  g->Binary(ynn_binary_multiply, 3974, 3978, 3979);
  g->Binary(ynn_binary_multiply, 3979, 9236, 3981);
  g->Binary(ynn_binary_add, 3953, 3981, 3982);
  g->Binary(ynn_binary_multiply, 3982, 9228, 3983);
}

// Scope: "Layer37"
LAB_YNN_BUILDER_NOINLINE void BuildLayer37(Context& ctx) {
  BuildLayer37Attention(ctx);
  BuildLayer37Mlp(ctx);
  BuildLayer37PerLayerEmbedding(ctx);
}

// Scope: "Layer38 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer38AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(3989, 3990, 0.4807405471801758, 0);
  g->Transpose(9254, 6742, {1,0});
  g->Binary(ynn_binary_multiply, 6739, 6741, 6737);
  g->Dot(3990, 6742, YNN_INVALID_VALUE_ID, 6736, 1);
  g->DequantizeTensor(6736, YNN_INVALID_VALUE_ID, 6737, 6738);
  g->QuantizeTensor(6738, 8595, 6740, 3992);
  g->Dequantize(3992, 3993, 0.43110236525535583, 0);
  g->SplitDim(3993, 3994, 2, {8,256});
  g->Transpose(3994, 3995, {0,2,1,3});
  g->Unary(ynn_unary_square, 3995, 3996);
  g->Reduce(ynn_reduce_sum, 3996, 8314, {3}, true);
  g->ShapeProduct(3996, 8313, {3});
  g->Binary(ynn_binary_divide, 8314, 8313, 3997);
  g->Binary(ynn_binary_add, 3997, 8647, 3998);
  g->Unary(ynn_unary_rsqrt, 3998, 3999);
  g->Binary(ynn_binary_multiply, 3995, 3999, 4000);
  g->Binary(ynn_binary_multiply, 4000, 9253, 4001);
  g->Slice(4001, 4004, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(4001, 4005, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 4005, 4006);
  g->Concat({4006,4004}, 4007, 3);
  g->Binary(ynn_binary_multiply, 4001, 3141, 4008);
  g->Binary(ynn_binary_multiply, 4007, 4217, 4009);
  g->Binary(ynn_binary_add, 4008, 4009, 4010);
}

// Scope: "Layer38 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer38AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9508, 4011, 0.0059552486054599285, 0);
  g->Dequantize(9532, 4012, 0.047244105488061905, 0);
  g->Slice(4010, 4013, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(4011, 4015, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(4012, 4016, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(4013, 4015, 4017, false, true);
  g->Mask(4017, 8716, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8716, 8318, {-1}, true);
  g->Binary(ynn_binary_subtract, 8716, 8318, 8315);
  g->Unary(ynn_unary_exp, 8315, 8316);
  g->Reduce(ynn_reduce_sum, 8316, 8319, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 8319, 8317);
  g->Binary(ynn_binary_multiply, 8316, 8317, 4018);
  g->Matmul(4018, 4016, 4019, false, false);
  g->Slice(4010, 4020, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(4011, 4021, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(4012, 4022, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(4020, 4021, 4023, false, true);
  g->Mask(4023, 8717, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8717, 8323, {-1}, true);
  g->Binary(ynn_binary_subtract, 8717, 8323, 8320);
  g->Unary(ynn_unary_exp, 8320, 8321);
  g->Reduce(ynn_reduce_sum, 8321, 8324, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 8324, 8322);
  g->Binary(ynn_binary_multiply, 8321, 8322, 4025);
  g->Matmul(4025, 4022, 4026, false, false);
  g->Concat({4019,4026}, 4027, 1);
}

// Scope: "Layer38 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer38AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(4027, 4028, {0,2,1,3});
  g->FuseDims(4028, 4029, 2, 2);
  g->Quantize(4029, 4030, 0.01845473423600197, 0);
  g->Transpose(9252, 6749, {1,0});
  g->Binary(ynn_binary_multiply, 6746, 6748, 6744);
  g->Dot(4030, 6749, YNN_INVALID_VALUE_ID, 6743, 1);
  g->DequantizeTensor(6743, YNN_INVALID_VALUE_ID, 6744, 6745);
  g->QuantizeTensor(6745, 8595, 6747, 4031);
  g->Dequantize(4031, 4032, 0.0599033385515213, 0);
}

// Scope: "Layer38 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer38Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3983, 3984);
  g->Reduce(ynn_reduce_sum, 3984, 8312, {2}, true);
  g->ShapeProduct(3984, 8311, {2});
  g->Binary(ynn_binary_divide, 8312, 8311, 3985);
  g->Binary(ynn_binary_add, 3985, 8647, 3986);
  g->Unary(ynn_unary_rsqrt, 3986, 3987);
  g->Binary(ynn_binary_multiply, 3983, 3987, 3988);
  g->Binary(ynn_binary_multiply, 3988, 9241, 3989);
  BuildLayer38AttentionQueryProjection(ctx);
  BuildLayer38AttentionSdpa(ctx);
  BuildLayer38AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 4032, 4033);
  g->Reduce(ynn_reduce_sum, 4033, 8326, {2}, true);
  g->ShapeProduct(4033, 8325, {2});
  g->Binary(ynn_binary_divide, 8326, 8325, 4035);
  g->Binary(ynn_binary_add, 4035, 8647, 4036);
  g->Unary(ynn_unary_rsqrt, 4036, 4037);
  g->Binary(ynn_binary_multiply, 4032, 4037, 4038);
  g->Binary(ynn_binary_multiply, 4038, 9248, 4039);
  g->Binary(ynn_binary_add, 4039, 3983, 4040);
}

// Scope: "Layer38 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer38Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 4040, 4041);
  g->Reduce(ynn_reduce_sum, 4041, 8328, {2}, true);
  g->ShapeProduct(4041, 8327, {2});
  g->Binary(ynn_binary_divide, 8328, 8327, 4042);
  g->Binary(ynn_binary_add, 4042, 8647, 4043);
  g->Unary(ynn_unary_rsqrt, 4043, 4044);
  g->Binary(ynn_binary_multiply, 4040, 4044, 4046);
  g->Binary(ynn_binary_multiply, 4046, 9251, 4047);
  g->Quantize(4047, 4048, 0.012482907623052597, 0);
  g->Transpose(9245, 6755, {1,0});
  g->Binary(ynn_binary_multiply, 6753, 6754, 6751);
  g->Dot(4048, 6755, YNN_INVALID_VALUE_ID, 6750, 1);
  g->DequantizeTensor(6750, YNN_INVALID_VALUE_ID, 6751, 6752);
  g->QuantizeTensor(6752, 8595, 6708, 4049);
  g->Dequantize(4049, 4050, 0.015009853057563305, 0);
  g->Transpose(9244, 6760, {1,0});
  g->Binary(ynn_binary_multiply, 6753, 6759, 6757);
  g->Dot(4048, 6760, YNN_INVALID_VALUE_ID, 6756, 1);
  g->DequantizeTensor(6756, YNN_INVALID_VALUE_ID, 6757, 6758);
  g->QuantizeTensor(6758, 8595, 6708, 4051);
  g->Dequantize(4051, 4052, 0.015009853057563305, 0);
  g->Polynomial(4052, 8331, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8331, 8332);
  g->Binary(ynn_binary_add, 8332, 7161, 8329);
  g->Binary(ynn_binary_multiply, 4052, 7173, 8330);
  g->Binary(ynn_binary_multiply, 8330, 8329, 4053);
  g->Binary(ynn_binary_multiply, 4050, 4053, 4054);
  g->Quantize(4054, 4056, 0.01168800238519907, 0);
  g->Transpose(9243, 6767, {1,0});
  g->Binary(ynn_binary_multiply, 6764, 6766, 6762);
  g->Dot(4056, 6767, YNN_INVALID_VALUE_ID, 6761, 1);
  g->DequantizeTensor(6761, YNN_INVALID_VALUE_ID, 6762, 6763);
  g->QuantizeTensor(6763, 8595, 6765, 4057);
  g->Dequantize(4057, 4058, 0.010835502296686172, 0);
  g->Unary(ynn_unary_square, 4058, 4059);
  g->Reduce(ynn_reduce_sum, 4059, 8334, {2}, true);
  g->ShapeProduct(4059, 8333, {2});
  g->Binary(ynn_binary_divide, 8334, 8333, 4060);
  g->Binary(ynn_binary_add, 4060, 8647, 4061);
  g->Unary(ynn_unary_rsqrt, 4061, 4062);
  g->Binary(ynn_binary_multiply, 4058, 4062, 4063);
  g->Binary(ynn_binary_multiply, 4063, 9249, 4064);
  g->Binary(ynn_binary_add, 4064, 4040, 4065);
}

// Scope: "Layer38 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer38PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 4067, {0,0,38,0}, {-1,-1,1,-1});
  g->Reshape(4067, 4068, {1,1,256});
  g->Unary(ynn_unary_square, 4068, 4069);
  g->Reduce(ynn_reduce_sum, 4069, 8336, {2}, true);
  g->ShapeProduct(4069, 8335, {2});
  g->Binary(ynn_binary_divide, 8336, 8335, 4070);
  g->Binary(ynn_binary_add, 4070, 8647, 4071);
  g->Unary(ynn_unary_rsqrt, 4071, 4072);
  g->Binary(ynn_binary_multiply, 4068, 4072, 4073);
  g->Binary(ynn_binary_multiply, 4073, 9401, 4074);
  g->Binary(ynn_binary_multiply, 9434, 8651, 4075);
  g->Binary(ynn_binary_add, 4074, 4075, 4076);
  g->Binary(ynn_binary_multiply, 4076, 8645, 4078);
  g->Quantize(4065, 4079, 0.3587295413017273, 0);
  g->Transpose(9246, 6773, {1,0});
  g->Binary(ynn_binary_multiply, 6771, 6772, 6769);
  g->Dot(4079, 6773, YNN_INVALID_VALUE_ID, 6768, 1);
  g->DequantizeTensor(6768, YNN_INVALID_VALUE_ID, 6769, 6770);
  g->QuantizeTensor(6770, 8595, 6727, 4080);
  g->Dequantize(4080, 4081, 0.14960631728172302, 0);
  g->Polynomial(4081, 8339, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8339, 8340);
  g->Binary(ynn_binary_add, 8340, 7161, 8337);
  g->Binary(ynn_binary_multiply, 4081, 7173, 8338);
  g->Binary(ynn_binary_multiply, 8338, 8337, 4082);
  g->Binary(ynn_binary_multiply, 4082, 4078, 4083);
  g->Quantize(4083, 4084, 1.17322838306427, 0);
  g->Transpose(9247, 6780, {1,0});
  g->Binary(ynn_binary_multiply, 6777, 6779, 6775);
  g->Dot(4084, 6780, YNN_INVALID_VALUE_ID, 6774, 1);
  g->DequantizeTensor(6774, YNN_INVALID_VALUE_ID, 6775, 6776);
  g->QuantizeTensor(6776, 8595, 6778, 4085);
  g->Dequantize(4085, 4086, 0.2754266560077667, 0);
  g->Unary(ynn_unary_square, 4086, 4087);
  g->Reduce(ynn_reduce_sum, 4087, 8342, {2}, true);
  g->ShapeProduct(4087, 8341, {2});
  g->Binary(ynn_binary_divide, 8342, 8341, 4089);
  g->Binary(ynn_binary_add, 4089, 8647, 4090);
  g->Unary(ynn_unary_rsqrt, 4090, 4091);
  g->Binary(ynn_binary_multiply, 4086, 4091, 4092);
  g->Binary(ynn_binary_multiply, 4092, 9250, 4093);
  g->Binary(ynn_binary_add, 4065, 4093, 4094);
  g->Binary(ynn_binary_multiply, 4094, 9242, 4095);
}

// Scope: "Layer38"
LAB_YNN_BUILDER_NOINLINE void BuildLayer38(Context& ctx) {
  BuildLayer38Attention(ctx);
  BuildLayer38Mlp(ctx);
  BuildLayer38PerLayerEmbedding(ctx);
}

// Scope: "Layer39 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer39AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(4102, 4103, 0.6628990173339844, 0);
  g->Transpose(9268, 6787, {1,0});
  g->Binary(ynn_binary_multiply, 6784, 6786, 6782);
  g->Dot(4103, 6787, YNN_INVALID_VALUE_ID, 6781, 1);
  g->DequantizeTensor(6781, YNN_INVALID_VALUE_ID, 6782, 6783);
  g->QuantizeTensor(6783, 8595, 6785, 4104);
  g->Dequantize(4104, 4105, 0.6338582634925842, 0);
  g->SplitDim(4105, 4106, 2, {8,256});
  g->Transpose(4106, 4107, {0,2,1,3});
  g->Unary(ynn_unary_square, 4107, 4108);
  g->Reduce(ynn_reduce_sum, 4108, 8346, {3}, true);
  g->ShapeProduct(4108, 8345, {3});
  g->Binary(ynn_binary_divide, 8346, 8345, 4109);
  g->Binary(ynn_binary_add, 4109, 8647, 4112);
  g->Unary(ynn_unary_rsqrt, 4112, 4113);
  g->Binary(ynn_binary_multiply, 4107, 4113, 4114);
  g->Binary(ynn_binary_multiply, 4114, 9267, 4115);
  g->Slice(4115, 4116, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(4115, 4117, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 4117, 4118);
  g->Concat({4118,4116}, 4119, 3);
  g->Binary(ynn_binary_multiply, 4115, 3141, 4120);
  g->Binary(ynn_binary_multiply, 4119, 4217, 4121);
  g->Binary(ynn_binary_add, 4120, 4121, 4123);
}

// Scope: "Layer39 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer39AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9508, 4124, 0.0059552486054599285, 0);
  g->Dequantize(9532, 4125, 0.047244105488061905, 0);
  g->Slice(4123, 4126, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(4124, 4127, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(4125, 4128, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(4126, 4127, 4129, false, true);
  g->Mask(4129, 8718, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8718, 8350, {-1}, true);
  g->Binary(ynn_binary_subtract, 8718, 8350, 8347);
  g->Unary(ynn_unary_exp, 8347, 8348);
  g->Reduce(ynn_reduce_sum, 8348, 8351, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 8351, 8349);
  g->Binary(ynn_binary_multiply, 8348, 8349, 4130);
  g->Matmul(4130, 4128, 4131, false, false);
  g->Slice(4123, 4133, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(4124, 4134, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(4125, 4135, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(4133, 4134, 4136, false, true);
  g->Mask(4136, 8719, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8719, 8355, {-1}, true);
  g->Binary(ynn_binary_subtract, 8719, 8355, 8352);
  g->Unary(ynn_unary_exp, 8352, 8353);
  g->Reduce(ynn_reduce_sum, 8353, 8356, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 8356, 8354);
  g->Binary(ynn_binary_multiply, 8353, 8354, 4137);
  g->Matmul(4137, 4135, 4138, false, false);
  g->Concat({4131,4138}, 4139, 1);
}

// Scope: "Layer39 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer39AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(4139, 4140, {0,2,1,3});
  g->FuseDims(4140, 4141, 2, 2);
  g->Quantize(4141, 4142, 0.019192922860383987, 0);
  g->Transpose(9266, 6793, {1,0});
  g->Binary(ynn_binary_multiply, 6345, 6792, 6789);
  g->Dot(4142, 6793, YNN_INVALID_VALUE_ID, 6788, 1);
  g->DequantizeTensor(6788, YNN_INVALID_VALUE_ID, 6789, 6790);
  g->QuantizeTensor(6790, 8595, 6791, 4143);
  g->Dequantize(4143, 4144, 0.09436486661434174, 0);
}

// Scope: "Layer39 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer39Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 4095, 4096);
  g->Reduce(ynn_reduce_sum, 4096, 8344, {2}, true);
  g->ShapeProduct(4096, 8343, {2});
  g->Binary(ynn_binary_divide, 8344, 8343, 4097);
  g->Binary(ynn_binary_add, 4097, 8647, 4098);
  g->Unary(ynn_unary_rsqrt, 4098, 4100);
  g->Binary(ynn_binary_multiply, 4095, 4100, 4101);
  g->Binary(ynn_binary_multiply, 4101, 9255, 4102);
  BuildLayer39AttentionQueryProjection(ctx);
  BuildLayer39AttentionSdpa(ctx);
  BuildLayer39AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 4144, 4145);
  g->Reduce(ynn_reduce_sum, 4145, 8358, {2}, true);
  g->ShapeProduct(4145, 8357, {2});
  g->Binary(ynn_binary_divide, 8358, 8357, 4146);
  g->Binary(ynn_binary_add, 4146, 8647, 4147);
  g->Unary(ynn_unary_rsqrt, 4147, 4148);
  g->Binary(ynn_binary_multiply, 4144, 4148, 4149);
  g->Binary(ynn_binary_multiply, 4149, 9262, 4150);
  g->Binary(ynn_binary_add, 4150, 4095, 4151);
}

// Scope: "Layer39 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer39Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 4151, 4153);
  g->Reduce(ynn_reduce_sum, 4153, 8365, {2}, true);
  g->ShapeProduct(4153, 8364, {2});
  g->Binary(ynn_binary_divide, 8365, 8364, 4154);
  g->Binary(ynn_binary_add, 4154, 8647, 4155);
  g->Unary(ynn_unary_rsqrt, 4155, 4156);
  g->Binary(ynn_binary_multiply, 4151, 4156, 4157);
  g->Binary(ynn_binary_multiply, 4157, 9265, 4158);
  g->Quantize(4158, 4159, 0.01159096509218216, 0);
  g->Transpose(9259, 6800, {1,0});
  g->Binary(ynn_binary_multiply, 6797, 6799, 6795);
  g->Dot(4159, 6800, YNN_INVALID_VALUE_ID, 6794, 1);
  g->DequantizeTensor(6794, YNN_INVALID_VALUE_ID, 6795, 6796);
  g->QuantizeTensor(6796, 8595, 6798, 4160);
  g->Dequantize(4160, 4161, 0.01648622937500477, 0);
  g->Transpose(9258, 6805, {1,0});
  g->Binary(ynn_binary_multiply, 6797, 6804, 6802);
  g->Dot(4159, 6805, YNN_INVALID_VALUE_ID, 6801, 1);
  g->DequantizeTensor(6801, YNN_INVALID_VALUE_ID, 6802, 6803);
  g->QuantizeTensor(6803, 8595, 6798, 4163);
  g->Dequantize(4163, 4164, 0.01648622937500477, 0);
  g->Polynomial(4164, 8368, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8368, 8369);
  g->Binary(ynn_binary_add, 8369, 7161, 8366);
  g->Binary(ynn_binary_multiply, 4164, 7173, 8367);
  g->Binary(ynn_binary_multiply, 8367, 8366, 4165);
  g->Binary(ynn_binary_multiply, 4161, 4165, 4166);
  g->Quantize(4166, 4167, 0.013656506314873695, 0);
  g->Transpose(9257, 6812, {1,0});
  g->Binary(ynn_binary_multiply, 6809, 6811, 6807);
  g->Dot(4167, 6812, YNN_INVALID_VALUE_ID, 6806, 1);
  g->DequantizeTensor(6806, YNN_INVALID_VALUE_ID, 6807, 6808);
  g->QuantizeTensor(6808, 8595, 6810, 4168);
  g->Dequantize(4168, 4169, 0.012228615581989288, 0);
  g->Unary(ynn_unary_square, 4169, 4170);
  g->Reduce(ynn_reduce_sum, 4170, 8371, {2}, true);
  g->ShapeProduct(4170, 8370, {2});
  g->Binary(ynn_binary_divide, 8371, 8370, 4171);
  g->Binary(ynn_binary_add, 4171, 8647, 4172);
  g->Unary(ynn_unary_rsqrt, 4172, 4174);
  g->Binary(ynn_binary_multiply, 4169, 4174, 4175);
  g->Binary(ynn_binary_multiply, 4175, 9263, 4176);
  g->Binary(ynn_binary_add, 4176, 4151, 4177);
}

// Scope: "Layer39 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer39PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 4178, {0,0,39,0}, {-1,-1,1,-1});
  g->Reshape(4178, 4179, {1,1,256});
  g->Unary(ynn_unary_square, 4179, 4180);
  g->Reduce(ynn_reduce_sum, 4180, 8373, {2}, true);
  g->ShapeProduct(4180, 8372, {2});
  g->Binary(ynn_binary_divide, 8373, 8372, 4181);
  g->Binary(ynn_binary_add, 4181, 8647, 4182);
  g->Unary(ynn_unary_rsqrt, 4182, 4183);
  g->Binary(ynn_binary_multiply, 4179, 4183, 4185);
  g->Binary(ynn_binary_multiply, 4185, 9401, 4186);
  g->Binary(ynn_binary_multiply, 9435, 8651, 4187);
  g->Binary(ynn_binary_add, 4186, 4187, 4188);
  g->Binary(ynn_binary_multiply, 4188, 8645, 4189);
  g->Quantize(4177, 4190, 0.3429988920688629, 0);
  g->Transpose(9260, 6819, {1,0});
  g->Binary(ynn_binary_multiply, 6816, 6818, 6814);
  g->Dot(4190, 6819, YNN_INVALID_VALUE_ID, 6813, 1);
  g->DequantizeTensor(6813, YNN_INVALID_VALUE_ID, 6814, 6815);
  g->QuantizeTensor(6815, 8595, 6817, 4191);
  g->Dequantize(4191, 4192, 0.16141733527183533, 0);
  g->Polynomial(4192, 8376, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8376, 8377);
  g->Binary(ynn_binary_add, 8377, 7161, 8374);
  g->Binary(ynn_binary_multiply, 4192, 7173, 8375);
  g->Binary(ynn_binary_multiply, 8375, 8374, 4193);
  g->Binary(ynn_binary_multiply, 4193, 4189, 4194);
  g->Quantize(4194, 4196, 1.212598443031311, 0);
  g->Transpose(9261, 6826, {1,0});
  g->Binary(ynn_binary_multiply, 6823, 6825, 6821);
  g->Dot(4196, 6826, YNN_INVALID_VALUE_ID, 6820, 1);
  g->DequantizeTensor(6820, YNN_INVALID_VALUE_ID, 6821, 6822);
  g->QuantizeTensor(6822, 8595, 6824, 4197);
  g->Dequantize(4197, 4198, 0.27964624762535095, 0);
  g->Unary(ynn_unary_square, 4198, 4199);
  g->Reduce(ynn_reduce_sum, 4199, 8379, {2}, true);
  g->ShapeProduct(4199, 8378, {2});
  g->Binary(ynn_binary_divide, 8379, 8378, 4200);
  g->Binary(ynn_binary_add, 4200, 8647, 4201);
  g->Unary(ynn_unary_rsqrt, 4201, 4202);
  g->Binary(ynn_binary_multiply, 4198, 4202, 4203);
  g->Binary(ynn_binary_multiply, 4203, 9264, 4204);
  g->Binary(ynn_binary_add, 4177, 4204, 4205);
  g->Binary(ynn_binary_multiply, 4205, 9256, 4207);
}

// Scope: "Layer39"
LAB_YNN_BUILDER_NOINLINE void BuildLayer39(Context& ctx) {
  BuildLayer39Attention(ctx);
  BuildLayer39Mlp(ctx);
  BuildLayer39PerLayerEmbedding(ctx);
}

// Scope: "Layer40 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer40AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(4213, 4214, 1.2804369926452637, 0);
  g->Transpose(9299, 6833, {1,0});
  g->Binary(ynn_binary_multiply, 6830, 6832, 6828);
  g->Dot(4214, 6833, YNN_INVALID_VALUE_ID, 6827, 1);
  g->DequantizeTensor(6827, YNN_INVALID_VALUE_ID, 6828, 6829);
  g->QuantizeTensor(6829, 8595, 6831, 4215);
  g->Dequantize(4215, 4216, 0.6535432934761047, 0);
  g->SplitDim(4216, 4218, 2, {8,256});
  g->Transpose(4218, 4219, {0,2,1,3});
  g->Unary(ynn_unary_square, 4219, 4220);
  g->Reduce(ynn_reduce_sum, 4220, 8383, {3}, true);
  g->ShapeProduct(4220, 8382, {3});
  g->Binary(ynn_binary_divide, 8383, 8382, 4221);
  g->Binary(ynn_binary_add, 4221, 8647, 4222);
  g->Unary(ynn_unary_rsqrt, 4222, 4223);
  g->Binary(ynn_binary_multiply, 4219, 4223, 4224);
  g->Binary(ynn_binary_multiply, 4224, 9298, 4225);
  g->Slice(4225, 4226, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(4225, 4227, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 4227, 4229);
  g->Concat({4229,4226}, 4230, 3);
  g->Binary(ynn_binary_multiply, 4225, 3141, 4231);
  g->Binary(ynn_binary_multiply, 4230, 4217, 4232);
  g->Binary(ynn_binary_add, 4231, 4232, 4233);
}

// Scope: "Layer40 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer40AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9508, 4234, 0.0059552486054599285, 0);
  g->Dequantize(9532, 4235, 0.047244105488061905, 0);
  g->Slice(4233, 4236, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(4234, 4237, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(4235, 4238, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(4236, 4237, 4240, false, true);
  g->Mask(4240, 8722, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8722, 8392, {-1}, true);
  g->Binary(ynn_binary_subtract, 8722, 8392, 8389);
  g->Unary(ynn_unary_exp, 8389, 8390);
  g->Reduce(ynn_reduce_sum, 8390, 8393, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 8393, 8391);
  g->Binary(ynn_binary_multiply, 8390, 8391, 4241);
  g->Matmul(4241, 4238, 4242, false, false);
  g->Slice(4233, 4243, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(4234, 4244, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(4235, 4245, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(4243, 4244, 4246, false, true);
  g->Mask(4246, 8723, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8723, 8397, {-1}, true);
  g->Binary(ynn_binary_subtract, 8723, 8397, 8394);
  g->Unary(ynn_unary_exp, 8394, 8395);
  g->Reduce(ynn_reduce_sum, 8395, 8398, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 8398, 8396);
  g->Binary(ynn_binary_multiply, 8395, 8396, 4247);
  g->Matmul(4247, 4245, 4249, false, false);
  g->Concat({4242,4249}, 4250, 1);
}

// Scope: "Layer40 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer40AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(4250, 4251, {0,2,1,3});
  g->FuseDims(4251, 4252, 2, 2);
  g->Quantize(4252, 4253, 0.017839577049016953, 0);
  g->Transpose(9297, 6840, {1,0});
  g->Binary(ynn_binary_multiply, 6837, 6839, 6835);
  g->Dot(4253, 6840, YNN_INVALID_VALUE_ID, 6834, 1);
  g->DequantizeTensor(6834, YNN_INVALID_VALUE_ID, 6835, 6836);
  g->QuantizeTensor(6836, 8595, 6838, 4254);
  g->Dequantize(4254, 4255, 0.07701452821493149, 0);
}

// Scope: "Layer40 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer40Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 4207, 4208);
  g->Reduce(ynn_reduce_sum, 4208, 8381, {2}, true);
  g->ShapeProduct(4208, 8380, {2});
  g->Binary(ynn_binary_divide, 8381, 8380, 4209);
  g->Binary(ynn_binary_add, 4209, 8647, 4210);
  g->Unary(ynn_unary_rsqrt, 4210, 4211);
  g->Binary(ynn_binary_multiply, 4207, 4211, 4212);
  g->Binary(ynn_binary_multiply, 4212, 9286, 4213);
  BuildLayer40AttentionQueryProjection(ctx);
  BuildLayer40AttentionSdpa(ctx);
  BuildLayer40AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 4255, 4256);
  g->Reduce(ynn_reduce_sum, 4256, 8400, {2}, true);
  g->ShapeProduct(4256, 8399, {2});
  g->Binary(ynn_binary_divide, 8400, 8399, 4257);
  g->Binary(ynn_binary_add, 4257, 8647, 4258);
  g->Unary(ynn_unary_rsqrt, 4258, 4260);
  g->Binary(ynn_binary_multiply, 4255, 4260, 4261);
  g->Binary(ynn_binary_multiply, 4261, 9293, 4262);
  g->Binary(ynn_binary_add, 4262, 4207, 4263);
}

// Scope: "Layer40 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer40Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 4263, 4264);
  g->Reduce(ynn_reduce_sum, 4264, 8402, {2}, true);
  g->ShapeProduct(4264, 8401, {2});
  g->Binary(ynn_binary_divide, 8402, 8401, 4265);
  g->Binary(ynn_binary_add, 4265, 8647, 4266);
  g->Unary(ynn_unary_rsqrt, 4266, 4267);
  g->Binary(ynn_binary_multiply, 4263, 4267, 4268);
  g->Binary(ynn_binary_multiply, 4268, 9296, 4269);
  g->Quantize(4269, 4271, 0.030199747532606125, 0);
  g->Transpose(9290, 6847, {1,0});
  g->Binary(ynn_binary_multiply, 6844, 6846, 6842);
  g->Dot(4271, 6847, YNN_INVALID_VALUE_ID, 6841, 1);
  g->DequantizeTensor(6841, YNN_INVALID_VALUE_ID, 6842, 6843);
  g->QuantizeTensor(6843, 8595, 6845, 4272);
  g->Dequantize(4272, 4273, 0.037893712520599365, 0);
  g->Transpose(9289, 6852, {1,0});
  g->Binary(ynn_binary_multiply, 6844, 6851, 6849);
  g->Dot(4271, 6852, YNN_INVALID_VALUE_ID, 6848, 1);
  g->DequantizeTensor(6848, YNN_INVALID_VALUE_ID, 6849, 6850);
  g->QuantizeTensor(6850, 8595, 6845, 4274);
  g->Dequantize(4274, 4275, 0.037893712520599365, 0);
  g->Polynomial(4275, 8405, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8405, 8406);
  g->Binary(ynn_binary_add, 8406, 7161, 8403);
  g->Binary(ynn_binary_multiply, 4275, 7173, 8404);
  g->Binary(ynn_binary_multiply, 8404, 8403, 4276);
  g->Binary(ynn_binary_multiply, 4273, 4276, 4277);
  g->Quantize(4277, 4278, 0.08956693857908249, 0);
  g->Transpose(9288, 6859, {1,0});
  g->Binary(ynn_binary_multiply, 6856, 6858, 6854);
  g->Dot(4278, 6859, YNN_INVALID_VALUE_ID, 6853, 1);
  g->DequantizeTensor(6853, YNN_INVALID_VALUE_ID, 6854, 6855);
  g->QuantizeTensor(6855, 8595, 6857, 4279);
  g->Dequantize(4279, 4281, 0.11817207932472229, 0);
  g->Unary(ynn_unary_square, 4281, 4282);
  g->Reduce(ynn_reduce_sum, 4282, 8408, {2}, true);
  g->ShapeProduct(4282, 8407, {2});
  g->Binary(ynn_binary_divide, 8408, 8407, 4283);
  g->Binary(ynn_binary_add, 4283, 8647, 4284);
  g->Unary(ynn_unary_rsqrt, 4284, 4285);
  g->Binary(ynn_binary_multiply, 4281, 4285, 4286);
  g->Binary(ynn_binary_multiply, 4286, 9294, 4287);
  g->Binary(ynn_binary_add, 4287, 4263, 4288);
}

// Scope: "Layer40 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer40PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 4289, {0,0,40,0}, {-1,-1,1,-1});
  g->Reshape(4289, 4290, {1,1,256});
  g->Unary(ynn_unary_square, 4290, 4292);
  g->Reduce(ynn_reduce_sum, 4292, 8410, {2}, true);
  g->ShapeProduct(4292, 8409, {2});
  g->Binary(ynn_binary_divide, 8410, 8409, 4293);
  g->Binary(ynn_binary_add, 4293, 8647, 4294);
  g->Unary(ynn_unary_rsqrt, 4294, 4295);
  g->Binary(ynn_binary_multiply, 4290, 4295, 4296);
  g->Binary(ynn_binary_multiply, 4296, 9401, 4297);
  g->Binary(ynn_binary_multiply, 9437, 8651, 4298);
  g->Binary(ynn_binary_add, 4297, 4298, 4299);
  g->Binary(ynn_binary_multiply, 4299, 8645, 4300);
  g->Quantize(4288, 4301, 0.34838828444480896, 0);
  g->Transpose(9291, 6872, {1,0});
  g->Binary(ynn_binary_multiply, 6870, 6871, 6868);
  g->Dot(4301, 6872, YNN_INVALID_VALUE_ID, 6867, 1);
  g->DequantizeTensor(6867, YNN_INVALID_VALUE_ID, 6868, 6869);
  g->QuantizeTensor(6869, 8595, 6428, 4303);
  g->Dequantize(4303, 4304, 0.20078741014003754, 0);
  g->Polynomial(4304, 8413, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8413, 8414);
  g->Binary(ynn_binary_add, 8414, 7161, 8411);
  g->Binary(ynn_binary_multiply, 4304, 7173, 8412);
  g->Binary(ynn_binary_multiply, 8412, 8411, 4305);
  g->Binary(ynn_binary_multiply, 4305, 4300, 4306);
  g->Quantize(4306, 4307, 3.496062994003296, 0);
  g->Transpose(9292, 6879, {1,0});
  g->Binary(ynn_binary_multiply, 6876, 6878, 6874);
  g->Dot(4307, 6879, YNN_INVALID_VALUE_ID, 6873, 1);
  g->DequantizeTensor(6873, YNN_INVALID_VALUE_ID, 6874, 6875);
  g->QuantizeTensor(6875, 8595, 6877, 4308);
  g->Dequantize(4308, 4309, 0.6477274894714355, 0);
  g->Unary(ynn_unary_square, 4309, 4310);
  g->Reduce(ynn_reduce_sum, 4310, 8416, {2}, true);
  g->ShapeProduct(4310, 8415, {2});
  g->Binary(ynn_binary_divide, 8416, 8415, 4311);
  g->Binary(ynn_binary_add, 4311, 8647, 4312);
  g->Unary(ynn_unary_rsqrt, 4312, 4314);
  g->Binary(ynn_binary_multiply, 4309, 4314, 4315);
  g->Binary(ynn_binary_multiply, 4315, 9295, 4316);
  g->Binary(ynn_binary_add, 4288, 4316, 4317);
  g->Binary(ynn_binary_multiply, 4317, 9287, 4318);
}

// Scope: "Layer40"
LAB_YNN_BUILDER_NOINLINE void BuildLayer40(Context& ctx) {
  BuildLayer40Attention(ctx);
  BuildLayer40Mlp(ctx);
  BuildLayer40PerLayerEmbedding(ctx);
}

// Scope: "Layer41 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer41AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(4325, 4326, 2.4042584896087646, 0);
  g->Transpose(9313, 6885, {1,0});
  g->Binary(ynn_binary_multiply, 6883, 6884, 6881);
  g->Dot(4326, 6885, YNN_INVALID_VALUE_ID, 6880, 1);
  g->DequantizeTensor(6880, YNN_INVALID_VALUE_ID, 6881, 6882);
  g->QuantizeTensor(6882, 8595, 6169, 4327);
  g->Dequantize(4327, 4328, 1.0629920959472656, 0);
  g->SplitDim(4328, 4329, 2, {8,512});
  g->Transpose(4329, 4330, {0,2,1,3});
  g->Unary(ynn_unary_square, 4330, 4331);
  g->Reduce(ynn_reduce_sum, 4331, 8422, {3}, true);
  g->ShapeProduct(4331, 8421, {3});
  g->Binary(ynn_binary_divide, 8422, 8421, 4332);
  g->Binary(ynn_binary_add, 4332, 8647, 4333);
  g->Unary(ynn_unary_rsqrt, 4333, 4334);
  g->Binary(ynn_binary_multiply, 4330, 4334, 4336);
  g->Binary(ynn_binary_multiply, 4336, 9312, 4337);
  g->Slice(4337, 4338, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(4337, 4339, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 4339, 4340);
  g->Concat({4340,4338}, 4341, 3);
  g->Binary(ynn_binary_multiply, 4337, 4830, 4342);
  g->Binary(ynn_binary_multiply, 4341, 2, 4343);
  g->Binary(ynn_binary_add, 4342, 4343, 4344);
}

// Scope: "Layer41 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer41AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9509, 4345, 0.001091228099539876, 0);
  g->Dequantize(9533, 4347, 0.01785714365541935, 0);
  g->Slice(4344, 4348, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(4345, 4349, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(4347, 4350, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(4348, 4349, 4351, false, true);
  g->Mask(4351, 8724, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 8724, 8426, {-1}, true);
  g->Binary(ynn_binary_subtract, 8724, 8426, 8423);
  g->Unary(ynn_unary_exp, 8423, 8424);
  g->Reduce(ynn_reduce_sum, 8424, 8427, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 8427, 8425);
  g->Binary(ynn_binary_multiply, 8424, 8425, 4352);
  g->Matmul(4352, 4350, 4353, false, false);
  g->Slice(4344, 4354, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(4345, 4355, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(4347, 4357, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(4354, 4355, 4358, false, true);
  g->Mask(4358, 8725, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 8725, 8431, {-1}, true);
  g->Binary(ynn_binary_subtract, 8725, 8431, 8428);
  g->Unary(ynn_unary_exp, 8428, 8429);
  g->Reduce(ynn_reduce_sum, 8429, 8432, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 8432, 8430);
  g->Binary(ynn_binary_multiply, 8429, 8430, 4359);
  g->Matmul(4359, 4357, 4360, false, false);
  g->Concat({4353,4360}, 4361, 1);
}

// Scope: "Layer41 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer41AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(4361, 4362, {0,2,1,3});
  g->FuseDims(4362, 4363, 2, 2);
  g->Quantize(4363, 4364, 0.011441939510405064, 0);
  g->Transpose(9311, 6892, {1,0});
  g->Binary(ynn_binary_multiply, 6889, 6891, 6887);
  g->Dot(4364, 6892, YNN_INVALID_VALUE_ID, 6886, 1);
  g->DequantizeTensor(6886, YNN_INVALID_VALUE_ID, 6887, 6888);
  g->QuantizeTensor(6888, 8595, 6890, 4365);
  g->Dequantize(4365, 4367, 0.010074657388031483, 0);
}

// Scope: "Layer41 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer41Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 4318, 4319);
  g->Reduce(ynn_reduce_sum, 4319, 8418, {2}, true);
  g->ShapeProduct(4319, 8417, {2});
  g->Binary(ynn_binary_divide, 8418, 8417, 4320);
  g->Binary(ynn_binary_add, 4320, 8647, 4321);
  g->Unary(ynn_unary_rsqrt, 4321, 4322);
  g->Binary(ynn_binary_multiply, 4318, 4322, 4323);
  g->Binary(ynn_binary_multiply, 4323, 9300, 4325);
  BuildLayer41AttentionQueryProjection(ctx);
  BuildLayer41AttentionSdpa(ctx);
  BuildLayer41AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 4367, 4368);
  g->Reduce(ynn_reduce_sum, 4368, 8434, {2}, true);
  g->ShapeProduct(4368, 8433, {2});
  g->Binary(ynn_binary_divide, 8434, 8433, 4369);
  g->Binary(ynn_binary_add, 4369, 8647, 4370);
  g->Unary(ynn_unary_rsqrt, 4370, 4371);
  g->Binary(ynn_binary_multiply, 4367, 4371, 4372);
  g->Binary(ynn_binary_multiply, 4372, 9307, 4373);
  g->Binary(ynn_binary_add, 4373, 4318, 4374);
}

// Scope: "Layer41 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer41Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 4374, 4375);
  g->Reduce(ynn_reduce_sum, 4375, 8436, {2}, true);
  g->ShapeProduct(4375, 8435, {2});
  g->Binary(ynn_binary_divide, 8436, 8435, 4376);
  g->Binary(ynn_binary_add, 4376, 8647, 4378);
  g->Unary(ynn_unary_rsqrt, 4378, 4379);
  g->Binary(ynn_binary_multiply, 4374, 4379, 4380);
  g->Binary(ynn_binary_multiply, 4380, 9310, 4381);
  g->Quantize(4381, 4382, 0.023036088794469833, 0);
  g->Transpose(9304, 6899, {1,0});
  g->Binary(ynn_binary_multiply, 6896, 6898, 6894);
  g->Dot(4382, 6899, YNN_INVALID_VALUE_ID, 6893, 1);
  g->DequantizeTensor(6893, YNN_INVALID_VALUE_ID, 6894, 6895);
  g->QuantizeTensor(6895, 8595, 6897, 4383);
  g->Dequantize(4383, 4384, 0.02559056133031845, 0);
  g->Transpose(9303, 6904, {1,0});
  g->Binary(ynn_binary_multiply, 6896, 6903, 6901);
  g->Dot(4382, 6904, YNN_INVALID_VALUE_ID, 6900, 1);
  g->DequantizeTensor(6900, YNN_INVALID_VALUE_ID, 6901, 6902);
  g->QuantizeTensor(6902, 8595, 6897, 4385);
  g->Dequantize(4385, 4386, 0.02559056133031845, 0);
  g->Polynomial(4386, 8439, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8439, 8440);
  g->Binary(ynn_binary_add, 8440, 7161, 8437);
  g->Binary(ynn_binary_multiply, 4386, 7173, 8438);
  g->Binary(ynn_binary_multiply, 8438, 8437, 4388);
  g->Binary(ynn_binary_multiply, 4384, 4388, 4389);
  g->Quantize(4389, 4390, 0.038631901144981384, 0);
  g->Transpose(9302, 6911, {1,0});
  g->Binary(ynn_binary_multiply, 6908, 6910, 6906);
  g->Dot(4390, 6911, YNN_INVALID_VALUE_ID, 6905, 1);
  g->DequantizeTensor(6905, YNN_INVALID_VALUE_ID, 6906, 6907);
  g->QuantizeTensor(6907, 8595, 6909, 4391);
  g->Dequantize(4391, 4392, 0.03348301723599434, 0);
  g->Unary(ynn_unary_square, 4392, 4393);
  g->Reduce(ynn_reduce_sum, 4393, 8442, {2}, true);
  g->ShapeProduct(4393, 8441, {2});
  g->Binary(ynn_binary_divide, 8442, 8441, 4394);
  g->Binary(ynn_binary_add, 4394, 8647, 4395);
  g->Unary(ynn_unary_rsqrt, 4395, 4396);
  g->Binary(ynn_binary_multiply, 4392, 4396, 4397);
  g->Binary(ynn_binary_multiply, 4397, 9308, 4399);
  g->Binary(ynn_binary_add, 4399, 4374, 4400);
}

// Scope: "Layer41 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer41PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 4401, {0,0,41,0}, {-1,-1,1,-1});
  g->Reshape(4401, 4402, {1,1,256});
  g->Unary(ynn_unary_square, 4402, 4403);
  g->Reduce(ynn_reduce_sum, 4403, 8446, {2}, true);
  g->ShapeProduct(4403, 8445, {2});
  g->Binary(ynn_binary_divide, 8446, 8445, 4404);
  g->Binary(ynn_binary_add, 4404, 8647, 4405);
  g->Unary(ynn_unary_rsqrt, 4405, 4406);
  g->Binary(ynn_binary_multiply, 4402, 4406, 4407);
  g->Binary(ynn_binary_multiply, 4407, 9401, 4408);
  g->Binary(ynn_binary_multiply, 9438, 8651, 4410);
  g->Binary(ynn_binary_add, 4408, 4410, 4411);
  g->Binary(ynn_binary_multiply, 4411, 8645, 4412);
  g->Quantize(4400, 4413, 0.37271758913993835, 0);
  g->Transpose(9305, 6917, {1,0});
  g->Binary(ynn_binary_multiply, 6915, 6916, 6913);
  g->Dot(4413, 6917, YNN_INVALID_VALUE_ID, 6912, 1);
  g->DequantizeTensor(6912, YNN_INVALID_VALUE_ID, 6913, 6914);
  g->QuantizeTensor(6914, 8595, 5007, 4414);
  g->Dequantize(4414, 4415, 0.3366141617298126, 0);
  g->Polynomial(4415, 8449, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8449, 8450);
  g->Binary(ynn_binary_add, 8450, 7161, 8447);
  g->Binary(ynn_binary_multiply, 4415, 7173, 8448);
  g->Binary(ynn_binary_multiply, 8448, 8447, 4416);
  g->Binary(ynn_binary_multiply, 4416, 4412, 4417);
  g->Quantize(4417, 4418, 9.259842872619629, 0);
  g->Transpose(9306, 6924, {1,0});
  g->Binary(ynn_binary_multiply, 6921, 6923, 6919);
  g->Dot(4418, 6924, YNN_INVALID_VALUE_ID, 6918, 1);
  g->DequantizeTensor(6918, YNN_INVALID_VALUE_ID, 6919, 6920);
  g->QuantizeTensor(6920, 8595, 6922, 4419);
  g->Dequantize(4419, 4421, 1.999718189239502, 0);
  g->Unary(ynn_unary_square, 4421, 4422);
  g->Reduce(ynn_reduce_sum, 4422, 8452, {2}, true);
  g->ShapeProduct(4422, 8451, {2});
  g->Binary(ynn_binary_divide, 8452, 8451, 4423);
  g->Binary(ynn_binary_add, 4423, 8647, 4424);
  g->Unary(ynn_unary_rsqrt, 4424, 4425);
  g->Binary(ynn_binary_multiply, 4421, 4425, 4426);
  g->Binary(ynn_binary_multiply, 4426, 9309, 4427);
  g->Binary(ynn_binary_add, 4400, 4427, 4428);
  g->Binary(ynn_binary_multiply, 4428, 9301, 4429);
}

// Scope: "Layer41"
LAB_YNN_BUILDER_NOINLINE void BuildLayer41(Context& ctx) {
  BuildLayer41Attention(ctx);
  BuildLayer41Mlp(ctx);
  BuildLayer41PerLayerEmbedding(ctx);
}

// Scope: "FinalNormAndHead"
LAB_YNN_BUILDER_NOINLINE void BuildFinalNormAndHead(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 4429, 4430);
  g->Reduce(ynn_reduce_sum, 4430, 8454, {2}, true);
  g->ShapeProduct(4430, 8453, {2});
  g->Binary(ynn_binary_divide, 8454, 8453, 4433);
  g->Binary(ynn_binary_add, 4433, 8647, 4434);
  g->Unary(ynn_unary_rsqrt, 4434, 4435);
  g->Binary(ynn_binary_multiply, 4429, 4435, 4436);
  g->Binary(ynn_binary_multiply, 4436, 9399, 4437);
  g->Reduce(ynn_reduce_min_max, 4437, 6932, {-1}, true);
  g->DynamicQuantization(6932, 6931, 6930);
  g->QuantizeTensor(4437, 6931, 6930, 6929);
  g->Transpose(8652, 6935, {1,0});
  g->Binary(ynn_binary_multiply, 6930, 6933, 6926);
  g->Reduce(ynn_reduce_sum, 6935, 6934, {0}, true);
  g->Binary(ynn_binary_multiply, 6931, 6934, 6928);
  g->Unary(ynn_unary_negate, 6928, 6927);
  g->Dot(6929, 6935, 6927, 6925, 1);
  g->DequantizeTensor(6925, YNN_INVALID_VALUE_ID, 6926, 4438);
  g->Binary(ynn_binary_multiply, 4438, 8738, 4439);
  g->Unary(ynn_unary_tanh, 4439, 4440);
  g->Binary(ynn_binary_multiply, 4440, 8646, 8653);
  g->ResultShape(8653, {slinky::expr(int64_t{1}),slinky::expr(int64_t{1}),slinky::expr(int64_t{262144})});
}

}  // namespace BuildGemma4DecodeSource
