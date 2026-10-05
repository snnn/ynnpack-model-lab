// Generated YNNPACK builder; do not edit.
#include "gemma4_decode_builder.h"

namespace BuildGemma4DecodeSource {

// Scope: "Layer35 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer35AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(3758, 3759, 0.40628930926322937, 0);
  g->Transpose(9344, 6727, {1,0});
  g->Binary(ynn_binary_multiply, 6725, 6726, 6723);
  g->Dot(3759, 6727, YNN_INVALID_VALUE_ID, 6722, 1);
  g->DequantizeTensor(6722, YNN_INVALID_VALUE_ID, 6723, 6724);
  g->QuantizeTensor(6724, 8727, 5139, 3760);
  g->Dequantize(3760, 3761, 0.3366141617298126, 0);
  g->SplitDim(3761, 3763, 2, {8,512});
  g->FuseDims(3763, 3765, 1, 2);
  g->SplitDim(3765, 3764, 1, {8,1});
  g->Unary(ynn_unary_square, 3764, 3766);
  g->Reduce(ynn_reduce_sum, 3766, 8344, {3}, true);
  g->ShapeProduct(3766, 8343, {3});
  g->Binary(ynn_binary_divide, 8344, 8343, 3767);
  g->Binary(ynn_binary_add, 3767, 8779, 3768);
  g->Unary(ynn_unary_rsqrt, 3768, 3769);
  g->Binary(ynn_binary_multiply, 3764, 3769, 3770);
  g->Binary(ynn_binary_multiply, 3770, 9343, 3771);
  g->Slice(3771, 3772, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(3771, 3773, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 3773, 3775);
  g->Concat({3775,3772}, 3776, 3);
  g->Binary(ynn_binary_multiply, 3771, 4959, 3777);
  g->Binary(ynn_binary_multiply, 3776, 2, 3778);
  g->Binary(ynn_binary_add, 3777, 3778, 3779);
}

// Scope: "Layer35 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer35AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9641, 3780, 0.001091228099539876, 0);
  g->Dequantize(9665, 3781, 0.01785714365541935, 0);
  g->Slice(3779, 3782, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(3780, 3783, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(3781, 3784, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(3782, 3783, 3787, false, true);
  g->Mask(3787, 8842, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 8842, 8350, {-1}, true);
  g->Binary(ynn_binary_subtract, 8842, 8350, 8347);
  g->Unary(ynn_unary_exp, 8347, 8348);
  g->Reduce(ynn_reduce_sum, 8348, 8351, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 8351, 8349);
  g->Binary(ynn_binary_multiply, 8348, 8349, 3788);
  g->Matmul(3788, 3784, 3789, false, false);
  g->Slice(3779, 3790, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(3780, 3791, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(3781, 3792, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(3790, 3791, 3793, false, true);
  g->Mask(3793, 8843, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 8843, 8355, {-1}, true);
  g->Binary(ynn_binary_subtract, 8843, 8355, 8352);
  g->Unary(ynn_unary_exp, 8352, 8353);
  g->Reduce(ynn_reduce_sum, 8353, 8356, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 8356, 8354);
  g->Binary(ynn_binary_multiply, 8353, 8354, 3794);
  g->Matmul(3794, 3792, 3796, false, false);
  g->Concat({3789,3796}, 3797, 1);
}

// Scope: "Layer35 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer35AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(3797, 3799, 1, 2);
  g->SplitDim(3799, 3798, 1, {1,8});
  g->FuseDims(3798, 3800, 2, 2);
  g->Quantize(3800, 3801, 0.014025600627064705, 0);
  g->Transpose(9342, 6734, {1,0});
  g->Binary(ynn_binary_multiply, 6731, 6733, 6729);
  g->Dot(3801, 6734, YNN_INVALID_VALUE_ID, 6728, 1);
  g->DequantizeTensor(6728, YNN_INVALID_VALUE_ID, 6729, 6730);
  g->QuantizeTensor(6730, 8727, 6732, 3802);
  g->Dequantize(3802, 3803, 0.022187285125255585, 0);
}

// Scope: "Layer35 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer35Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3752, 3753);
  g->Reduce(ynn_reduce_sum, 3753, 8342, {2}, true);
  g->ShapeProduct(3753, 8341, {2});
  g->Binary(ynn_binary_divide, 8342, 8341, 3754);
  g->Binary(ynn_binary_add, 3754, 8779, 3755);
  g->Unary(ynn_unary_rsqrt, 3755, 3756);
  g->Binary(ynn_binary_multiply, 3752, 3756, 3757);
  g->Binary(ynn_binary_multiply, 3757, 9331, 3758);
  BuildLayer35AttentionQueryProjection(ctx);
  BuildLayer35AttentionSdpa(ctx);
  BuildLayer35AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 3803, 3804);
  g->Reduce(ynn_reduce_sum, 3804, 8358, {2}, true);
  g->ShapeProduct(3804, 8357, {2});
  g->Binary(ynn_binary_divide, 8358, 8357, 3805);
  g->Binary(ynn_binary_add, 3805, 8779, 3806);
  g->Unary(ynn_unary_rsqrt, 3806, 3808);
  g->Binary(ynn_binary_multiply, 3803, 3808, 3809);
  g->Binary(ynn_binary_multiply, 3809, 9338, 3810);
  g->Binary(ynn_binary_add, 3810, 3752, 3811);
}

// Scope: "Layer35 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer35Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3811, 3812);
  g->Reduce(ynn_reduce_sum, 3812, 8360, {2}, true);
  g->ShapeProduct(3812, 8359, {2});
  g->Binary(ynn_binary_divide, 8360, 8359, 3813);
  g->Binary(ynn_binary_add, 3813, 8779, 3814);
  g->Unary(ynn_unary_rsqrt, 3814, 3815);
  g->Binary(ynn_binary_multiply, 3811, 3815, 3816);
  g->Binary(ynn_binary_multiply, 3816, 9341, 3817);
  g->Quantize(3817, 3818, 0.016540825366973877, 0);
  g->Transpose(9335, 6740, {1,0});
  g->Binary(ynn_binary_multiply, 6738, 6739, 6736);
  g->Dot(3818, 6740, YNN_INVALID_VALUE_ID, 6735, 1);
  g->DequantizeTensor(6735, YNN_INVALID_VALUE_ID, 6736, 6737);
  g->QuantizeTensor(6737, 8727, 6322, 3819);
  g->Dequantize(3819, 3820, 0.02595965564250946, 0);
  g->Transpose(9334, 6745, {1,0});
  g->Binary(ynn_binary_multiply, 6738, 6744, 6742);
  g->Dot(3818, 6745, YNN_INVALID_VALUE_ID, 6741, 1);
  g->DequantizeTensor(6741, YNN_INVALID_VALUE_ID, 6742, 6743);
  g->QuantizeTensor(6743, 8727, 6322, 3821);
  g->Dequantize(3821, 3822, 0.02595965564250946, 0);
  g->Polynomial(3822, 8363, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8363, 8364);
  g->Binary(ynn_binary_add, 8364, 7293, 8361);
  g->Binary(ynn_binary_multiply, 3822, 7305, 8362);
  g->Binary(ynn_binary_multiply, 8362, 8361, 3823);
  g->Binary(ynn_binary_multiply, 3820, 3823, 3824);
  g->Quantize(3824, 3825, 0.034694891422986984, 0);
  g->Transpose(9333, 6752, {1,0});
  g->Binary(ynn_binary_multiply, 6749, 6751, 6747);
  g->Dot(3825, 6752, YNN_INVALID_VALUE_ID, 6746, 1);
  g->DequantizeTensor(6746, YNN_INVALID_VALUE_ID, 6747, 6748);
  g->QuantizeTensor(6748, 8727, 6750, 3826);
  g->Dequantize(3826, 3828, 0.024422448128461838, 0);
  g->Unary(ynn_unary_square, 3828, 3829);
  g->Reduce(ynn_reduce_sum, 3829, 8366, {2}, true);
  g->ShapeProduct(3829, 8365, {2});
  g->Binary(ynn_binary_divide, 8366, 8365, 3830);
  g->Binary(ynn_binary_add, 3830, 8779, 3831);
  g->Unary(ynn_unary_rsqrt, 3831, 3832);
  g->Binary(ynn_binary_multiply, 3828, 3832, 3833);
  g->Binary(ynn_binary_multiply, 3833, 9339, 3834);
  g->Binary(ynn_binary_add, 3834, 3811, 3835);
}

// Scope: "Layer35 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer35PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(429, 3836, {0,0,35,0}, {-1,-1,1,-1});
  g->Reshape(3836, 3837, {1,1,256});
  g->Unary(ynn_unary_square, 3837, 3839);
  g->Reduce(ynn_reduce_sum, 3839, 8368, {2}, true);
  g->ShapeProduct(3839, 8367, {2});
  g->Binary(ynn_binary_divide, 8368, 8367, 3840);
  g->Binary(ynn_binary_add, 3840, 8779, 3841);
  g->Unary(ynn_unary_rsqrt, 3841, 3842);
  g->Binary(ynn_binary_multiply, 3837, 3842, 3843);
  g->Binary(ynn_binary_multiply, 3843, 9533, 3844);
  g->Binary(ynn_binary_multiply, 9563, 8783, 3845);
  g->Binary(ynn_binary_add, 3844, 3845, 3846);
  g->Binary(ynn_binary_multiply, 3846, 8777, 3847);
  g->Quantize(3835, 3848, 0.38799241185188293, 0);
  g->Transpose(9336, 6764, {1,0});
  g->Binary(ynn_binary_multiply, 6761, 6763, 6759);
  g->Dot(3848, 6764, YNN_INVALID_VALUE_ID, 6758, 1);
  g->DequantizeTensor(6758, YNN_INVALID_VALUE_ID, 6759, 6760);
  g->QuantizeTensor(6760, 8727, 6762, 3850);
  g->Dequantize(3850, 3851, 0.2224409580230713, 0);
  g->Polynomial(3851, 8371, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8371, 8372);
  g->Binary(ynn_binary_add, 8372, 7293, 8369);
  g->Binary(ynn_binary_multiply, 3851, 7305, 8370);
  g->Binary(ynn_binary_multiply, 8370, 8369, 3852);
  g->Binary(ynn_binary_multiply, 3852, 3847, 3853);
  g->Quantize(3853, 3854, 1.2677165269851685, 0);
  g->Transpose(9337, 6771, {1,0});
  g->Binary(ynn_binary_multiply, 6768, 6770, 6766);
  g->Dot(3854, 6771, YNN_INVALID_VALUE_ID, 6765, 1);
  g->DequantizeTensor(6765, YNN_INVALID_VALUE_ID, 6766, 6767);
  g->QuantizeTensor(6767, 8727, 6769, 3855);
  g->Dequantize(3855, 3856, 0.17961417138576508, 0);
  g->Unary(ynn_unary_square, 3856, 3857);
  g->Reduce(ynn_reduce_sum, 3857, 8374, {2}, true);
  g->ShapeProduct(3857, 8373, {2});
  g->Binary(ynn_binary_divide, 8374, 8373, 3858);
  g->Binary(ynn_binary_add, 3858, 8779, 3859);
  g->Unary(ynn_unary_rsqrt, 3859, 3862);
  g->Binary(ynn_binary_multiply, 3856, 3862, 3863);
  g->Binary(ynn_binary_multiply, 3863, 9340, 3864);
  g->Binary(ynn_binary_add, 3835, 3864, 3865);
  g->Binary(ynn_binary_multiply, 3865, 9332, 3866);
}

// Scope: "Layer35"
LAB_YNN_BUILDER_NOINLINE void BuildLayer35(Context& ctx) {
  BuildLayer35Attention(ctx);
  BuildLayer35Mlp(ctx);
  BuildLayer35PerLayerEmbedding(ctx);
}

// Scope: "Layer36 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer36AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(3873, 3874, 0.2735130488872528, 0);
  g->Transpose(9358, 6778, {1,0});
  g->Binary(ynn_binary_multiply, 6775, 6777, 6773);
  g->Dot(3874, 6778, YNN_INVALID_VALUE_ID, 6772, 1);
  g->DequantizeTensor(6772, YNN_INVALID_VALUE_ID, 6773, 6774);
  g->QuantizeTensor(6774, 8727, 6776, 3875);
  g->Dequantize(3875, 3876, 0.5118110179901123, 0);
  g->SplitDim(3876, 3877, 2, {8,256});
  g->FuseDims(3877, 3879, 1, 2);
  g->SplitDim(3879, 3878, 1, {8,1});
  g->Unary(ynn_unary_square, 3878, 3880);
  g->Reduce(ynn_reduce_sum, 3880, 8378, {3}, true);
  g->ShapeProduct(3880, 8377, {3});
  g->Binary(ynn_binary_divide, 8378, 8377, 3881);
  g->Binary(ynn_binary_add, 3881, 8779, 3882);
  g->Unary(ynn_unary_rsqrt, 3882, 3883);
  g->Binary(ynn_binary_multiply, 3878, 3883, 3885);
  g->Binary(ynn_binary_multiply, 3885, 9357, 3886);
  g->Slice(3886, 3887, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3886, 3888, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3888, 3889);
  g->Concat({3889,3887}, 3890, 3);
  g->Binary(ynn_binary_multiply, 3886, 3231, 3891);
  g->Binary(ynn_binary_multiply, 3890, 4329, 3892);
  g->Binary(ynn_binary_add, 3891, 3892, 3893);
}

// Scope: "Layer36 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer36AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9640, 3894, 0.0059552486054599285, 0);
  g->Dequantize(9664, 3897, 0.047244105488061905, 0);
  g->Slice(3893, 3898, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(3894, 3899, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(3897, 3900, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(3898, 3899, 3901, false, true);
  g->Mask(3901, 8844, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8844, 8384, {-1}, true);
  g->Binary(ynn_binary_subtract, 8844, 8384, 8381);
  g->Unary(ynn_unary_exp, 8381, 8382);
  g->Reduce(ynn_reduce_sum, 8382, 8385, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 8385, 8383);
  g->Binary(ynn_binary_multiply, 8382, 8383, 3902);
  g->Matmul(3902, 3900, 3903, false, false);
  g->Slice(3893, 3904, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(3894, 3905, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(3897, 3907, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(3904, 3905, 3908, false, true);
  g->Mask(3908, 8845, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8845, 8389, {-1}, true);
  g->Binary(ynn_binary_subtract, 8845, 8389, 8386);
  g->Unary(ynn_unary_exp, 8386, 8387);
  g->Reduce(ynn_reduce_sum, 8387, 8390, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 8390, 8388);
  g->Binary(ynn_binary_multiply, 8387, 8388, 3909);
  g->Matmul(3909, 3907, 3910, false, false);
  g->Concat({3903,3910}, 3911, 1);
}

// Scope: "Layer36 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer36AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(3911, 3913, 1, 2);
  g->SplitDim(3913, 3912, 1, {1,8});
  g->FuseDims(3912, 3914, 2, 2);
  g->Quantize(3914, 3915, 0.019685048609972, 0);
  g->Transpose(9356, 6784, {1,0});
  g->Binary(ynn_binary_multiply, 6632, 6783, 6780);
  g->Dot(3915, 6784, YNN_INVALID_VALUE_ID, 6779, 1);
  g->DequantizeTensor(6779, YNN_INVALID_VALUE_ID, 6780, 6781);
  g->QuantizeTensor(6781, 8727, 6782, 3916);
  g->Dequantize(3916, 3918, 0.13249905407428741, 0);
}

// Scope: "Layer36 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer36Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3866, 3867);
  g->Reduce(ynn_reduce_sum, 3867, 8376, {2}, true);
  g->ShapeProduct(3867, 8375, {2});
  g->Binary(ynn_binary_divide, 8376, 8375, 3868);
  g->Binary(ynn_binary_add, 3868, 8779, 3869);
  g->Unary(ynn_unary_rsqrt, 3869, 3870);
  g->Binary(ynn_binary_multiply, 3866, 3870, 3871);
  g->Binary(ynn_binary_multiply, 3871, 9345, 3873);
  BuildLayer36AttentionQueryProjection(ctx);
  BuildLayer36AttentionSdpa(ctx);
  BuildLayer36AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 3918, 3919);
  g->Reduce(ynn_reduce_sum, 3919, 8392, {2}, true);
  g->ShapeProduct(3919, 8391, {2});
  g->Binary(ynn_binary_divide, 8392, 8391, 3920);
  g->Binary(ynn_binary_add, 3920, 8779, 3921);
  g->Unary(ynn_unary_rsqrt, 3921, 3922);
  g->Binary(ynn_binary_multiply, 3918, 3922, 3923);
  g->Binary(ynn_binary_multiply, 3923, 9352, 3924);
  g->Binary(ynn_binary_add, 3924, 3866, 3925);
}

// Scope: "Layer36 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer36Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3925, 3926);
  g->Reduce(ynn_reduce_sum, 3926, 8394, {2}, true);
  g->ShapeProduct(3926, 8393, {2});
  g->Binary(ynn_binary_divide, 8394, 8393, 3927);
  g->Binary(ynn_binary_add, 3927, 8779, 3929);
  g->Unary(ynn_unary_rsqrt, 3929, 3930);
  g->Binary(ynn_binary_multiply, 3925, 3930, 3931);
  g->Binary(ynn_binary_multiply, 3931, 9355, 3932);
  g->Quantize(3932, 3933, 0.014071965590119362, 0);
  g->Transpose(9349, 6791, {1,0});
  g->Binary(ynn_binary_multiply, 6788, 6790, 6786);
  g->Dot(3933, 6791, YNN_INVALID_VALUE_ID, 6785, 1);
  g->DequantizeTensor(6785, YNN_INVALID_VALUE_ID, 6786, 6787);
  g->QuantizeTensor(6787, 8727, 6789, 3934);
  g->Dequantize(3934, 3935, 0.017470480874180794, 0);
  g->Transpose(9348, 6796, {1,0});
  g->Binary(ynn_binary_multiply, 6788, 6795, 6793);
  g->Dot(3933, 6796, YNN_INVALID_VALUE_ID, 6792, 1);
  g->DequantizeTensor(6792, YNN_INVALID_VALUE_ID, 6793, 6794);
  g->QuantizeTensor(6794, 8727, 6789, 3936);
  g->Dequantize(3936, 3937, 0.017470480874180794, 0);
  g->Polynomial(3937, 8397, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8397, 8398);
  g->Binary(ynn_binary_add, 8398, 7293, 8395);
  g->Binary(ynn_binary_multiply, 3937, 7305, 8396);
  g->Binary(ynn_binary_multiply, 8396, 8395, 3938);
  g->Binary(ynn_binary_multiply, 3935, 3938, 3939);
  g->Quantize(3939, 3940, 0.013102864846587181, 0);
  g->Transpose(9347, 6803, {1,0});
  g->Binary(ynn_binary_multiply, 6800, 6802, 6798);
  g->Dot(3940, 6803, YNN_INVALID_VALUE_ID, 6797, 1);
  g->DequantizeTensor(6797, YNN_INVALID_VALUE_ID, 6798, 6799);
  g->QuantizeTensor(6799, 8727, 6801, 3941);
  g->Dequantize(3941, 3942, 0.008950071409344673, 0);
  g->Unary(ynn_unary_square, 3942, 3943);
  g->Reduce(ynn_reduce_sum, 3943, 8400, {2}, true);
  g->ShapeProduct(3943, 8399, {2});
  g->Binary(ynn_binary_divide, 8400, 8399, 3944);
  g->Binary(ynn_binary_add, 3944, 8779, 3945);
  g->Unary(ynn_unary_rsqrt, 3945, 3946);
  g->Binary(ynn_binary_multiply, 3942, 3946, 3947);
  g->Binary(ynn_binary_multiply, 3947, 9353, 3948);
  g->Binary(ynn_binary_add, 3948, 3925, 3949);
}

// Scope: "Layer36 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer36PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(429, 3950, {0,0,36,0}, {-1,-1,1,-1});
  g->Reshape(3950, 3951, {1,1,256});
  g->Unary(ynn_unary_square, 3951, 3952);
  g->Reduce(ynn_reduce_sum, 3952, 8402, {2}, true);
  g->ShapeProduct(3952, 8401, {2});
  g->Binary(ynn_binary_divide, 8402, 8401, 3953);
  g->Binary(ynn_binary_add, 3953, 8779, 3954);
  g->Unary(ynn_unary_rsqrt, 3954, 3955);
  g->Binary(ynn_binary_multiply, 3951, 3955, 3956);
  g->Binary(ynn_binary_multiply, 3956, 9533, 3957);
  g->Binary(ynn_binary_multiply, 9564, 8783, 3959);
  g->Binary(ynn_binary_add, 3957, 3959, 3960);
  g->Binary(ynn_binary_multiply, 3960, 8777, 3961);
  g->Quantize(3949, 3962, 0.38496658205986023, 0);
  g->Transpose(9350, 6809, {1,0});
  g->Binary(ynn_binary_multiply, 6807, 6808, 6805);
  g->Dot(3962, 6809, YNN_INVALID_VALUE_ID, 6804, 1);
  g->DequantizeTensor(6804, YNN_INVALID_VALUE_ID, 6805, 6806);
  g->QuantizeTensor(6806, 8727, 6295, 3963);
  g->Dequantize(3963, 3964, 0.19685040414333344, 0);
  g->Polynomial(3964, 8405, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8405, 8406);
  g->Binary(ynn_binary_add, 8406, 7293, 8403);
  g->Binary(ynn_binary_multiply, 3964, 7305, 8404);
  g->Binary(ynn_binary_multiply, 8404, 8403, 3965);
  g->Binary(ynn_binary_multiply, 3965, 3961, 3966);
  g->Quantize(3966, 3967, 2.6299211978912354, 0);
  g->Transpose(9351, 6816, {1,0});
  g->Binary(ynn_binary_multiply, 6813, 6815, 6811);
  g->Dot(3967, 6816, YNN_INVALID_VALUE_ID, 6810, 1);
  g->DequantizeTensor(6810, YNN_INVALID_VALUE_ID, 6811, 6812);
  g->QuantizeTensor(6812, 8727, 6814, 3968);
  g->Dequantize(3968, 3969, 0.24539968371391296, 0);
  g->Unary(ynn_unary_square, 3969, 3970);
  g->Reduce(ynn_reduce_sum, 3970, 8408, {2}, true);
  g->ShapeProduct(3970, 8407, {2});
  g->Binary(ynn_binary_divide, 8408, 8407, 3971);
  g->Binary(ynn_binary_add, 3971, 8779, 3972);
  g->Unary(ynn_unary_rsqrt, 3972, 3973);
  g->Binary(ynn_binary_multiply, 3969, 3973, 3974);
  g->Binary(ynn_binary_multiply, 3974, 9354, 3975);
  g->Binary(ynn_binary_add, 3949, 3975, 3976);
  g->Binary(ynn_binary_multiply, 3976, 9346, 3977);
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
  g->Quantize(3983, 3984, 0.7991782426834106, 0);
  g->Transpose(9372, 6823, {1,0});
  g->Binary(ynn_binary_multiply, 6820, 6822, 6818);
  g->Dot(3984, 6823, YNN_INVALID_VALUE_ID, 6817, 1);
  g->DequantizeTensor(6817, YNN_INVALID_VALUE_ID, 6818, 6819);
  g->QuantizeTensor(6819, 8727, 6821, 3985);
  g->Dequantize(3985, 3986, 0.7244094610214233, 0);
  g->SplitDim(3986, 3987, 2, {8,256});
  g->FuseDims(3987, 3989, 1, 2);
  g->SplitDim(3989, 3988, 1, {8,1});
  g->Unary(ynn_unary_square, 3988, 3990);
  g->Reduce(ynn_reduce_sum, 3990, 8412, {3}, true);
  g->ShapeProduct(3990, 8411, {3});
  g->Binary(ynn_binary_divide, 8412, 8411, 3991);
  g->Binary(ynn_binary_add, 3991, 8779, 3992);
  g->Unary(ynn_unary_rsqrt, 3992, 3993);
  g->Binary(ynn_binary_multiply, 3988, 3993, 3994);
  g->Binary(ynn_binary_multiply, 3994, 9371, 3995);
  g->Slice(3995, 3996, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3995, 3997, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3997, 3998);
  g->Concat({3998,3996}, 3999, 3);
  g->Binary(ynn_binary_multiply, 3995, 3231, 4002);
  g->Binary(ynn_binary_multiply, 3999, 4329, 4003);
  g->Binary(ynn_binary_add, 4002, 4003, 4004);
}

// Scope: "Layer37 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer37AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9640, 4005, 0.0059552486054599285, 0);
  g->Dequantize(9664, 4006, 0.047244105488061905, 0);
  g->Slice(4004, 4007, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(4005, 4008, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(4006, 4009, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(4007, 4008, 4010, false, true);
  g->Mask(4010, 8846, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8846, 8416, {-1}, true);
  g->Binary(ynn_binary_subtract, 8846, 8416, 8413);
  g->Unary(ynn_unary_exp, 8413, 8414);
  g->Reduce(ynn_reduce_sum, 8414, 8417, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 8417, 8415);
  g->Binary(ynn_binary_multiply, 8414, 8415, 4012);
  g->Matmul(4012, 4009, 4013, false, false);
  g->Slice(4004, 4014, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(4005, 4015, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(4006, 4016, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(4014, 4015, 4017, false, true);
  g->Mask(4017, 8847, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8847, 8421, {-1}, true);
  g->Binary(ynn_binary_subtract, 8847, 8421, 8418);
  g->Unary(ynn_unary_exp, 8418, 8419);
  g->Reduce(ynn_reduce_sum, 8419, 8422, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 8422, 8420);
  g->Binary(ynn_binary_multiply, 8419, 8420, 4018);
  g->Matmul(4018, 4016, 4019, false, false);
  g->Concat({4013,4019}, 4020, 1);
}

// Scope: "Layer37 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer37AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(4020, 4023, 1, 2);
  g->SplitDim(4023, 4022, 1, {1,8});
  g->FuseDims(4022, 4024, 2, 2);
  g->Quantize(4024, 4025, 0.019685048609972, 0);
  g->Transpose(9370, 6835, {1,0});
  g->Binary(ynn_binary_multiply, 6632, 6834, 6831);
  g->Dot(4025, 6835, YNN_INVALID_VALUE_ID, 6830, 1);
  g->DequantizeTensor(6830, YNN_INVALID_VALUE_ID, 6831, 6832);
  g->QuantizeTensor(6832, 8727, 6833, 4026);
  g->Dequantize(4026, 4027, 0.09598665684461594, 0);
}

// Scope: "Layer37 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer37Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3977, 3978);
  g->Reduce(ynn_reduce_sum, 3978, 8410, {2}, true);
  g->ShapeProduct(3978, 8409, {2});
  g->Binary(ynn_binary_divide, 8410, 8409, 3979);
  g->Binary(ynn_binary_add, 3979, 8779, 3980);
  g->Unary(ynn_unary_rsqrt, 3980, 3981);
  g->Binary(ynn_binary_multiply, 3977, 3981, 3982);
  g->Binary(ynn_binary_multiply, 3982, 9359, 3983);
  BuildLayer37AttentionQueryProjection(ctx);
  BuildLayer37AttentionSdpa(ctx);
  BuildLayer37AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 4027, 4028);
  g->Reduce(ynn_reduce_sum, 4028, 8424, {2}, true);
  g->ShapeProduct(4028, 8423, {2});
  g->Binary(ynn_binary_divide, 8424, 8423, 4029);
  g->Binary(ynn_binary_add, 4029, 8779, 4030);
  g->Unary(ynn_unary_rsqrt, 4030, 4031);
  g->Binary(ynn_binary_multiply, 4027, 4031, 4032);
  g->Binary(ynn_binary_multiply, 4032, 9366, 4035);
  g->Binary(ynn_binary_add, 4035, 3977, 4036);
}

// Scope: "Layer37 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer37Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 4036, 4037);
  g->Reduce(ynn_reduce_sum, 4037, 8426, {2}, true);
  g->ShapeProduct(4037, 8425, {2});
  g->Binary(ynn_binary_divide, 8426, 8425, 4038);
  g->Binary(ynn_binary_add, 4038, 8779, 4039);
  g->Unary(ynn_unary_rsqrt, 4039, 4040);
  g->Binary(ynn_binary_multiply, 4036, 4040, 4041);
  g->Binary(ynn_binary_multiply, 4041, 9369, 4042);
  g->Quantize(4042, 4043, 0.01249794103205204, 0);
  g->Transpose(9363, 6842, {1,0});
  g->Binary(ynn_binary_multiply, 6839, 6841, 6837);
  g->Dot(4043, 6842, YNN_INVALID_VALUE_ID, 6836, 1);
  g->DequantizeTensor(6836, YNN_INVALID_VALUE_ID, 6837, 6838);
  g->QuantizeTensor(6838, 8727, 6840, 4044);
  g->Dequantize(4044, 4046, 0.015009853057563305, 0);
  g->Transpose(9362, 6847, {1,0});
  g->Binary(ynn_binary_multiply, 6839, 6846, 6844);
  g->Dot(4043, 6847, YNN_INVALID_VALUE_ID, 6843, 1);
  g->DequantizeTensor(6843, YNN_INVALID_VALUE_ID, 6844, 6845);
  g->QuantizeTensor(6845, 8727, 6840, 4047);
  g->Dequantize(4047, 4048, 0.015009853057563305, 0);
  g->Polynomial(4048, 8429, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8429, 8430);
  g->Binary(ynn_binary_add, 8430, 7293, 8427);
  g->Binary(ynn_binary_multiply, 4048, 7305, 8428);
  g->Binary(ynn_binary_multiply, 8428, 8427, 4049);
  g->Binary(ynn_binary_multiply, 4046, 4049, 4050);
  g->Quantize(4050, 4051, 0.010642234236001968, 0);
  g->Transpose(9361, 6854, {1,0});
  g->Binary(ynn_binary_multiply, 6851, 6853, 6849);
  g->Dot(4051, 6854, YNN_INVALID_VALUE_ID, 6848, 1);
  g->DequantizeTensor(6848, YNN_INVALID_VALUE_ID, 6849, 6850);
  g->QuantizeTensor(6850, 8727, 6852, 4052);
  g->Dequantize(4052, 4053, 0.00903213769197464, 0);
  g->Unary(ynn_unary_square, 4053, 4054);
  g->Reduce(ynn_reduce_sum, 4054, 8434, {2}, true);
  g->ShapeProduct(4054, 8433, {2});
  g->Binary(ynn_binary_divide, 8434, 8433, 4056);
  g->Binary(ynn_binary_add, 4056, 8779, 4057);
  g->Unary(ynn_unary_rsqrt, 4057, 4058);
  g->Binary(ynn_binary_multiply, 4053, 4058, 4059);
  g->Binary(ynn_binary_multiply, 4059, 9367, 4060);
  g->Binary(ynn_binary_add, 4060, 4036, 4061);
}

// Scope: "Layer37 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer37PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(429, 4062, {0,0,37,0}, {-1,-1,1,-1});
  g->Reshape(4062, 4063, {1,1,256});
  g->Unary(ynn_unary_square, 4063, 4064);
  g->Reduce(ynn_reduce_sum, 4064, 8436, {2}, true);
  g->ShapeProduct(4064, 8435, {2});
  g->Binary(ynn_binary_divide, 8436, 8435, 4065);
  g->Binary(ynn_binary_add, 4065, 8779, 4067);
  g->Unary(ynn_unary_rsqrt, 4067, 4068);
  g->Binary(ynn_binary_multiply, 4063, 4068, 4069);
  g->Binary(ynn_binary_multiply, 4069, 9533, 4070);
  g->Binary(ynn_binary_multiply, 9565, 8783, 4071);
  g->Binary(ynn_binary_add, 4070, 4071, 4072);
  g->Binary(ynn_binary_multiply, 4072, 8777, 4073);
  g->Quantize(4061, 4074, 0.37313586473464966, 0);
  g->Transpose(9364, 6861, {1,0});
  g->Binary(ynn_binary_multiply, 6858, 6860, 6856);
  g->Dot(4074, 6861, YNN_INVALID_VALUE_ID, 6855, 1);
  g->DequantizeTensor(6855, YNN_INVALID_VALUE_ID, 6856, 6857);
  g->QuantizeTensor(6857, 8727, 6859, 4075);
  g->Dequantize(4075, 4076, 0.14960631728172302, 0);
  g->Polynomial(4076, 8439, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8439, 8440);
  g->Binary(ynn_binary_add, 8440, 7293, 8437);
  g->Binary(ynn_binary_multiply, 4076, 7305, 8438);
  g->Binary(ynn_binary_multiply, 8438, 8437, 4078);
  g->Binary(ynn_binary_multiply, 4078, 4073, 4079);
  g->Quantize(4079, 4080, 1.1023621559143066, 0);
  g->Transpose(9365, 6867, {1,0});
  g->Binary(ynn_binary_multiply, 6354, 6866, 6863);
  g->Dot(4080, 6867, YNN_INVALID_VALUE_ID, 6862, 1);
  g->DequantizeTensor(6862, YNN_INVALID_VALUE_ID, 6863, 6864);
  g->QuantizeTensor(6864, 8727, 6865, 4081);
  g->Dequantize(4081, 4082, 0.2224193662405014, 0);
  g->Unary(ynn_unary_square, 4082, 4083);
  g->Reduce(ynn_reduce_sum, 4083, 8442, {2}, true);
  g->ShapeProduct(4083, 8441, {2});
  g->Binary(ynn_binary_divide, 8442, 8441, 4084);
  g->Binary(ynn_binary_add, 4084, 8779, 4085);
  g->Unary(ynn_unary_rsqrt, 4085, 4086);
  g->Binary(ynn_binary_multiply, 4082, 4086, 4087);
  g->Binary(ynn_binary_multiply, 4087, 9368, 4089);
  g->Binary(ynn_binary_add, 4061, 4089, 4090);
  g->Binary(ynn_binary_multiply, 4090, 9360, 4091);
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
  g->Quantize(4097, 4098, 0.4807405471801758, 0);
  g->Transpose(9386, 6874, {1,0});
  g->Binary(ynn_binary_multiply, 6871, 6873, 6869);
  g->Dot(4098, 6874, YNN_INVALID_VALUE_ID, 6868, 1);
  g->DequantizeTensor(6868, YNN_INVALID_VALUE_ID, 6869, 6870);
  g->QuantizeTensor(6870, 8727, 6872, 4100);
  g->Dequantize(4100, 4101, 0.43110236525535583, 0);
  g->SplitDim(4101, 4102, 2, {8,256});
  g->FuseDims(4102, 4104, 1, 2);
  g->SplitDim(4104, 4103, 1, {8,1});
  g->Unary(ynn_unary_square, 4103, 4105);
  g->Reduce(ynn_reduce_sum, 4105, 8446, {3}, true);
  g->ShapeProduct(4105, 8445, {3});
  g->Binary(ynn_binary_divide, 8446, 8445, 4106);
  g->Binary(ynn_binary_add, 4106, 8779, 4107);
  g->Unary(ynn_unary_rsqrt, 4107, 4108);
  g->Binary(ynn_binary_multiply, 4103, 4108, 4109);
  g->Binary(ynn_binary_multiply, 4109, 9385, 4110);
  g->Slice(4110, 4113, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(4110, 4114, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 4114, 4115);
  g->Concat({4115,4113}, 4116, 3);
  g->Binary(ynn_binary_multiply, 4110, 3231, 4117);
  g->Binary(ynn_binary_multiply, 4116, 4329, 4118);
  g->Binary(ynn_binary_add, 4117, 4118, 4119);
}

// Scope: "Layer38 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer38AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9640, 4120, 0.0059552486054599285, 0);
  g->Dequantize(9664, 4121, 0.047244105488061905, 0);
  g->Slice(4119, 4122, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(4120, 4124, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(4121, 4125, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(4122, 4124, 4126, false, true);
  g->Mask(4126, 8848, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8848, 8450, {-1}, true);
  g->Binary(ynn_binary_subtract, 8848, 8450, 8447);
  g->Unary(ynn_unary_exp, 8447, 8448);
  g->Reduce(ynn_reduce_sum, 8448, 8451, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 8451, 8449);
  g->Binary(ynn_binary_multiply, 8448, 8449, 4127);
  g->Matmul(4127, 4125, 4128, false, false);
  g->Slice(4119, 4129, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(4120, 4130, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(4121, 4131, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(4129, 4130, 4132, false, true);
  g->Mask(4132, 8849, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8849, 8455, {-1}, true);
  g->Binary(ynn_binary_subtract, 8849, 8455, 8452);
  g->Unary(ynn_unary_exp, 8452, 8453);
  g->Reduce(ynn_reduce_sum, 8453, 8456, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 8456, 8454);
  g->Binary(ynn_binary_multiply, 8453, 8454, 4134);
  g->Matmul(4134, 4131, 4135, false, false);
  g->Concat({4128,4135}, 4136, 1);
}

// Scope: "Layer38 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer38AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(4136, 4138, 1, 2);
  g->SplitDim(4138, 4137, 1, {1,8});
  g->FuseDims(4137, 4139, 2, 2);
  g->Quantize(4139, 4140, 0.01845473423600197, 0);
  g->Transpose(9384, 6881, {1,0});
  g->Binary(ynn_binary_multiply, 6878, 6880, 6876);
  g->Dot(4140, 6881, YNN_INVALID_VALUE_ID, 6875, 1);
  g->DequantizeTensor(6875, YNN_INVALID_VALUE_ID, 6876, 6877);
  g->QuantizeTensor(6877, 8727, 6879, 4141);
  g->Dequantize(4141, 4142, 0.0599033385515213, 0);
}

// Scope: "Layer38 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer38Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 4091, 4092);
  g->Reduce(ynn_reduce_sum, 4092, 8444, {2}, true);
  g->ShapeProduct(4092, 8443, {2});
  g->Binary(ynn_binary_divide, 8444, 8443, 4093);
  g->Binary(ynn_binary_add, 4093, 8779, 4094);
  g->Unary(ynn_unary_rsqrt, 4094, 4095);
  g->Binary(ynn_binary_multiply, 4091, 4095, 4096);
  g->Binary(ynn_binary_multiply, 4096, 9373, 4097);
  BuildLayer38AttentionQueryProjection(ctx);
  BuildLayer38AttentionSdpa(ctx);
  BuildLayer38AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 4142, 4143);
  g->Reduce(ynn_reduce_sum, 4143, 8458, {2}, true);
  g->ShapeProduct(4143, 8457, {2});
  g->Binary(ynn_binary_divide, 8458, 8457, 4145);
  g->Binary(ynn_binary_add, 4145, 8779, 4146);
  g->Unary(ynn_unary_rsqrt, 4146, 4147);
  g->Binary(ynn_binary_multiply, 4142, 4147, 4148);
  g->Binary(ynn_binary_multiply, 4148, 9380, 4149);
  g->Binary(ynn_binary_add, 4149, 4091, 4150);
}

// Scope: "Layer38 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer38Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 4150, 4151);
  g->Reduce(ynn_reduce_sum, 4151, 8460, {2}, true);
  g->ShapeProduct(4151, 8459, {2});
  g->Binary(ynn_binary_divide, 8460, 8459, 4152);
  g->Binary(ynn_binary_add, 4152, 8779, 4153);
  g->Unary(ynn_unary_rsqrt, 4153, 4154);
  g->Binary(ynn_binary_multiply, 4150, 4154, 4156);
  g->Binary(ynn_binary_multiply, 4156, 9383, 4157);
  g->Quantize(4157, 4158, 0.012482907623052597, 0);
  g->Transpose(9377, 6887, {1,0});
  g->Binary(ynn_binary_multiply, 6885, 6886, 6883);
  g->Dot(4158, 6887, YNN_INVALID_VALUE_ID, 6882, 1);
  g->DequantizeTensor(6882, YNN_INVALID_VALUE_ID, 6883, 6884);
  g->QuantizeTensor(6884, 8727, 6840, 4159);
  g->Dequantize(4159, 4160, 0.015009853057563305, 0);
  g->Transpose(9376, 6892, {1,0});
  g->Binary(ynn_binary_multiply, 6885, 6891, 6889);
  g->Dot(4158, 6892, YNN_INVALID_VALUE_ID, 6888, 1);
  g->DequantizeTensor(6888, YNN_INVALID_VALUE_ID, 6889, 6890);
  g->QuantizeTensor(6890, 8727, 6840, 4161);
  g->Dequantize(4161, 4162, 0.015009853057563305, 0);
  g->Polynomial(4162, 8463, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8463, 8464);
  g->Binary(ynn_binary_add, 8464, 7293, 8461);
  g->Binary(ynn_binary_multiply, 4162, 7305, 8462);
  g->Binary(ynn_binary_multiply, 8462, 8461, 4163);
  g->Binary(ynn_binary_multiply, 4160, 4163, 4164);
  g->Quantize(4164, 4166, 0.01168800238519907, 0);
  g->Transpose(9375, 6899, {1,0});
  g->Binary(ynn_binary_multiply, 6896, 6898, 6894);
  g->Dot(4166, 6899, YNN_INVALID_VALUE_ID, 6893, 1);
  g->DequantizeTensor(6893, YNN_INVALID_VALUE_ID, 6894, 6895);
  g->QuantizeTensor(6895, 8727, 6897, 4167);
  g->Dequantize(4167, 4168, 0.010835502296686172, 0);
  g->Unary(ynn_unary_square, 4168, 4169);
  g->Reduce(ynn_reduce_sum, 4169, 8466, {2}, true);
  g->ShapeProduct(4169, 8465, {2});
  g->Binary(ynn_binary_divide, 8466, 8465, 4170);
  g->Binary(ynn_binary_add, 4170, 8779, 4171);
  g->Unary(ynn_unary_rsqrt, 4171, 4172);
  g->Binary(ynn_binary_multiply, 4168, 4172, 4173);
  g->Binary(ynn_binary_multiply, 4173, 9381, 4174);
  g->Binary(ynn_binary_add, 4174, 4150, 4175);
}

// Scope: "Layer38 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer38PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(429, 4177, {0,0,38,0}, {-1,-1,1,-1});
  g->Reshape(4177, 4178, {1,1,256});
  g->Unary(ynn_unary_square, 4178, 4179);
  g->Reduce(ynn_reduce_sum, 4179, 8468, {2}, true);
  g->ShapeProduct(4179, 8467, {2});
  g->Binary(ynn_binary_divide, 8468, 8467, 4180);
  g->Binary(ynn_binary_add, 4180, 8779, 4181);
  g->Unary(ynn_unary_rsqrt, 4181, 4182);
  g->Binary(ynn_binary_multiply, 4178, 4182, 4183);
  g->Binary(ynn_binary_multiply, 4183, 9533, 4184);
  g->Binary(ynn_binary_multiply, 9566, 8783, 4185);
  g->Binary(ynn_binary_add, 4184, 4185, 4186);
  g->Binary(ynn_binary_multiply, 4186, 8777, 4188);
  g->Quantize(4175, 4189, 0.3587295413017273, 0);
  g->Transpose(9378, 6905, {1,0});
  g->Binary(ynn_binary_multiply, 6903, 6904, 6901);
  g->Dot(4189, 6905, YNN_INVALID_VALUE_ID, 6900, 1);
  g->DequantizeTensor(6900, YNN_INVALID_VALUE_ID, 6901, 6902);
  g->QuantizeTensor(6902, 8727, 6859, 4190);
  g->Dequantize(4190, 4191, 0.14960631728172302, 0);
  g->Polynomial(4191, 8471, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8471, 8472);
  g->Binary(ynn_binary_add, 8472, 7293, 8469);
  g->Binary(ynn_binary_multiply, 4191, 7305, 8470);
  g->Binary(ynn_binary_multiply, 8470, 8469, 4192);
  g->Binary(ynn_binary_multiply, 4192, 4188, 4193);
  g->Quantize(4193, 4194, 1.17322838306427, 0);
  g->Transpose(9379, 6912, {1,0});
  g->Binary(ynn_binary_multiply, 6909, 6911, 6907);
  g->Dot(4194, 6912, YNN_INVALID_VALUE_ID, 6906, 1);
  g->DequantizeTensor(6906, YNN_INVALID_VALUE_ID, 6907, 6908);
  g->QuantizeTensor(6908, 8727, 6910, 4195);
  g->Dequantize(4195, 4196, 0.2754266560077667, 0);
  g->Unary(ynn_unary_square, 4196, 4197);
  g->Reduce(ynn_reduce_sum, 4197, 8474, {2}, true);
  g->ShapeProduct(4197, 8473, {2});
  g->Binary(ynn_binary_divide, 8474, 8473, 4199);
  g->Binary(ynn_binary_add, 4199, 8779, 4200);
  g->Unary(ynn_unary_rsqrt, 4200, 4201);
  g->Binary(ynn_binary_multiply, 4196, 4201, 4202);
  g->Binary(ynn_binary_multiply, 4202, 9382, 4203);
  g->Binary(ynn_binary_add, 4175, 4203, 4204);
  g->Binary(ynn_binary_multiply, 4204, 9374, 4205);
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
  g->Quantize(4212, 4213, 0.6628990173339844, 0);
  g->Transpose(9400, 6919, {1,0});
  g->Binary(ynn_binary_multiply, 6916, 6918, 6914);
  g->Dot(4213, 6919, YNN_INVALID_VALUE_ID, 6913, 1);
  g->DequantizeTensor(6913, YNN_INVALID_VALUE_ID, 6914, 6915);
  g->QuantizeTensor(6915, 8727, 6917, 4214);
  g->Dequantize(4214, 4215, 0.6338582634925842, 0);
  g->SplitDim(4215, 4216, 2, {8,256});
  g->FuseDims(4216, 4218, 1, 2);
  g->SplitDim(4218, 4217, 1, {8,1});
  g->Unary(ynn_unary_square, 4217, 4219);
  g->Reduce(ynn_reduce_sum, 4219, 8478, {3}, true);
  g->ShapeProduct(4219, 8477, {3});
  g->Binary(ynn_binary_divide, 8478, 8477, 4220);
  g->Binary(ynn_binary_add, 4220, 8779, 4223);
  g->Unary(ynn_unary_rsqrt, 4223, 4224);
  g->Binary(ynn_binary_multiply, 4217, 4224, 4225);
  g->Binary(ynn_binary_multiply, 4225, 9399, 4226);
  g->Slice(4226, 4227, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(4226, 4228, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 4228, 4229);
  g->Concat({4229,4227}, 4230, 3);
  g->Binary(ynn_binary_multiply, 4226, 3231, 4231);
  g->Binary(ynn_binary_multiply, 4230, 4329, 4232);
  g->Binary(ynn_binary_add, 4231, 4232, 4234);
}

// Scope: "Layer39 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer39AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9640, 4235, 0.0059552486054599285, 0);
  g->Dequantize(9664, 4236, 0.047244105488061905, 0);
  g->Slice(4234, 4237, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(4235, 4238, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(4236, 4239, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(4237, 4238, 4240, false, true);
  g->Mask(4240, 8850, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8850, 8482, {-1}, true);
  g->Binary(ynn_binary_subtract, 8850, 8482, 8479);
  g->Unary(ynn_unary_exp, 8479, 8480);
  g->Reduce(ynn_reduce_sum, 8480, 8483, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 8483, 8481);
  g->Binary(ynn_binary_multiply, 8480, 8481, 4241);
  g->Matmul(4241, 4239, 4242, false, false);
  g->Slice(4234, 4244, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(4235, 4245, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(4236, 4246, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(4244, 4245, 4247, false, true);
  g->Mask(4247, 8851, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8851, 8487, {-1}, true);
  g->Binary(ynn_binary_subtract, 8851, 8487, 8484);
  g->Unary(ynn_unary_exp, 8484, 8485);
  g->Reduce(ynn_reduce_sum, 8485, 8488, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 8488, 8486);
  g->Binary(ynn_binary_multiply, 8485, 8486, 4248);
  g->Matmul(4248, 4246, 4249, false, false);
  g->Concat({4242,4249}, 4250, 1);
}

// Scope: "Layer39 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer39AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(4250, 4252, 1, 2);
  g->SplitDim(4252, 4251, 1, {1,8});
  g->FuseDims(4251, 4253, 2, 2);
  g->Quantize(4253, 4254, 0.019192922860383987, 0);
  g->Transpose(9398, 6925, {1,0});
  g->Binary(ynn_binary_multiply, 6477, 6924, 6921);
  g->Dot(4254, 6925, YNN_INVALID_VALUE_ID, 6920, 1);
  g->DequantizeTensor(6920, YNN_INVALID_VALUE_ID, 6921, 6922);
  g->QuantizeTensor(6922, 8727, 6923, 4255);
  g->Dequantize(4255, 4256, 0.09436486661434174, 0);
}

// Scope: "Layer39 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer39Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 4205, 4206);
  g->Reduce(ynn_reduce_sum, 4206, 8476, {2}, true);
  g->ShapeProduct(4206, 8475, {2});
  g->Binary(ynn_binary_divide, 8476, 8475, 4207);
  g->Binary(ynn_binary_add, 4207, 8779, 4208);
  g->Unary(ynn_unary_rsqrt, 4208, 4210);
  g->Binary(ynn_binary_multiply, 4205, 4210, 4211);
  g->Binary(ynn_binary_multiply, 4211, 9387, 4212);
  BuildLayer39AttentionQueryProjection(ctx);
  BuildLayer39AttentionSdpa(ctx);
  BuildLayer39AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 4256, 4257);
  g->Reduce(ynn_reduce_sum, 4257, 8490, {2}, true);
  g->ShapeProduct(4257, 8489, {2});
  g->Binary(ynn_binary_divide, 8490, 8489, 4258);
  g->Binary(ynn_binary_add, 4258, 8779, 4259);
  g->Unary(ynn_unary_rsqrt, 4259, 4260);
  g->Binary(ynn_binary_multiply, 4256, 4260, 4261);
  g->Binary(ynn_binary_multiply, 4261, 9394, 4262);
  g->Binary(ynn_binary_add, 4262, 4205, 4263);
}

// Scope: "Layer39 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer39Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 4263, 4265);
  g->Reduce(ynn_reduce_sum, 4265, 8497, {2}, true);
  g->ShapeProduct(4265, 8496, {2});
  g->Binary(ynn_binary_divide, 8497, 8496, 4266);
  g->Binary(ynn_binary_add, 4266, 8779, 4267);
  g->Unary(ynn_unary_rsqrt, 4267, 4268);
  g->Binary(ynn_binary_multiply, 4263, 4268, 4269);
  g->Binary(ynn_binary_multiply, 4269, 9397, 4270);
  g->Quantize(4270, 4271, 0.01159096509218216, 0);
  g->Transpose(9391, 6932, {1,0});
  g->Binary(ynn_binary_multiply, 6929, 6931, 6927);
  g->Dot(4271, 6932, YNN_INVALID_VALUE_ID, 6926, 1);
  g->DequantizeTensor(6926, YNN_INVALID_VALUE_ID, 6927, 6928);
  g->QuantizeTensor(6928, 8727, 6930, 4272);
  g->Dequantize(4272, 4273, 0.01648622937500477, 0);
  g->Transpose(9390, 6937, {1,0});
  g->Binary(ynn_binary_multiply, 6929, 6936, 6934);
  g->Dot(4271, 6937, YNN_INVALID_VALUE_ID, 6933, 1);
  g->DequantizeTensor(6933, YNN_INVALID_VALUE_ID, 6934, 6935);
  g->QuantizeTensor(6935, 8727, 6930, 4275);
  g->Dequantize(4275, 4276, 0.01648622937500477, 0);
  g->Polynomial(4276, 8500, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8500, 8501);
  g->Binary(ynn_binary_add, 8501, 7293, 8498);
  g->Binary(ynn_binary_multiply, 4276, 7305, 8499);
  g->Binary(ynn_binary_multiply, 8499, 8498, 4277);
  g->Binary(ynn_binary_multiply, 4273, 4277, 4278);
  g->Quantize(4278, 4279, 0.013656506314873695, 0);
  g->Transpose(9389, 6944, {1,0});
  g->Binary(ynn_binary_multiply, 6941, 6943, 6939);
  g->Dot(4279, 6944, YNN_INVALID_VALUE_ID, 6938, 1);
  g->DequantizeTensor(6938, YNN_INVALID_VALUE_ID, 6939, 6940);
  g->QuantizeTensor(6940, 8727, 6942, 4280);
  g->Dequantize(4280, 4281, 0.012228615581989288, 0);
  g->Unary(ynn_unary_square, 4281, 4282);
  g->Reduce(ynn_reduce_sum, 4282, 8503, {2}, true);
  g->ShapeProduct(4282, 8502, {2});
  g->Binary(ynn_binary_divide, 8503, 8502, 4283);
  g->Binary(ynn_binary_add, 4283, 8779, 4284);
  g->Unary(ynn_unary_rsqrt, 4284, 4286);
  g->Binary(ynn_binary_multiply, 4281, 4286, 4287);
  g->Binary(ynn_binary_multiply, 4287, 9395, 4288);
  g->Binary(ynn_binary_add, 4288, 4263, 4289);
}

// Scope: "Layer39 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer39PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(429, 4290, {0,0,39,0}, {-1,-1,1,-1});
  g->Reshape(4290, 4291, {1,1,256});
  g->Unary(ynn_unary_square, 4291, 4292);
  g->Reduce(ynn_reduce_sum, 4292, 8505, {2}, true);
  g->ShapeProduct(4292, 8504, {2});
  g->Binary(ynn_binary_divide, 8505, 8504, 4293);
  g->Binary(ynn_binary_add, 4293, 8779, 4294);
  g->Unary(ynn_unary_rsqrt, 4294, 4295);
  g->Binary(ynn_binary_multiply, 4291, 4295, 4297);
  g->Binary(ynn_binary_multiply, 4297, 9533, 4298);
  g->Binary(ynn_binary_multiply, 9567, 8783, 4299);
  g->Binary(ynn_binary_add, 4298, 4299, 4300);
  g->Binary(ynn_binary_multiply, 4300, 8777, 4301);
  g->Quantize(4289, 4302, 0.3429988920688629, 0);
  g->Transpose(9392, 6951, {1,0});
  g->Binary(ynn_binary_multiply, 6948, 6950, 6946);
  g->Dot(4302, 6951, YNN_INVALID_VALUE_ID, 6945, 1);
  g->DequantizeTensor(6945, YNN_INVALID_VALUE_ID, 6946, 6947);
  g->QuantizeTensor(6947, 8727, 6949, 4303);
  g->Dequantize(4303, 4304, 0.16141733527183533, 0);
  g->Polynomial(4304, 8508, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8508, 8509);
  g->Binary(ynn_binary_add, 8509, 7293, 8506);
  g->Binary(ynn_binary_multiply, 4304, 7305, 8507);
  g->Binary(ynn_binary_multiply, 8507, 8506, 4305);
  g->Binary(ynn_binary_multiply, 4305, 4301, 4306);
  g->Quantize(4306, 4308, 1.212598443031311, 0);
  g->Transpose(9393, 6958, {1,0});
  g->Binary(ynn_binary_multiply, 6955, 6957, 6953);
  g->Dot(4308, 6958, YNN_INVALID_VALUE_ID, 6952, 1);
  g->DequantizeTensor(6952, YNN_INVALID_VALUE_ID, 6953, 6954);
  g->QuantizeTensor(6954, 8727, 6956, 4309);
  g->Dequantize(4309, 4310, 0.27964624762535095, 0);
  g->Unary(ynn_unary_square, 4310, 4311);
  g->Reduce(ynn_reduce_sum, 4311, 8511, {2}, true);
  g->ShapeProduct(4311, 8510, {2});
  g->Binary(ynn_binary_divide, 8511, 8510, 4312);
  g->Binary(ynn_binary_add, 4312, 8779, 4313);
  g->Unary(ynn_unary_rsqrt, 4313, 4314);
  g->Binary(ynn_binary_multiply, 4310, 4314, 4315);
  g->Binary(ynn_binary_multiply, 4315, 9396, 4316);
  g->Binary(ynn_binary_add, 4289, 4316, 4317);
  g->Binary(ynn_binary_multiply, 4317, 9388, 4319);
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
  g->Quantize(4325, 4326, 1.2804369926452637, 0);
  g->Transpose(9431, 6965, {1,0});
  g->Binary(ynn_binary_multiply, 6962, 6964, 6960);
  g->Dot(4326, 6965, YNN_INVALID_VALUE_ID, 6959, 1);
  g->DequantizeTensor(6959, YNN_INVALID_VALUE_ID, 6960, 6961);
  g->QuantizeTensor(6961, 8727, 6963, 4327);
  g->Dequantize(4327, 4328, 0.6535432934761047, 0);
  g->SplitDim(4328, 4330, 2, {8,256});
  g->FuseDims(4330, 4332, 1, 2);
  g->SplitDim(4332, 4331, 1, {8,1});
  g->Unary(ynn_unary_square, 4331, 4333);
  g->Reduce(ynn_reduce_sum, 4333, 8515, {3}, true);
  g->ShapeProduct(4333, 8514, {3});
  g->Binary(ynn_binary_divide, 8515, 8514, 4334);
  g->Binary(ynn_binary_add, 4334, 8779, 4335);
  g->Unary(ynn_unary_rsqrt, 4335, 4336);
  g->Binary(ynn_binary_multiply, 4331, 4336, 4337);
  g->Binary(ynn_binary_multiply, 4337, 9430, 4338);
  g->Slice(4338, 4339, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(4338, 4340, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 4340, 4342);
  g->Concat({4342,4339}, 4343, 3);
  g->Binary(ynn_binary_multiply, 4338, 3231, 4344);
  g->Binary(ynn_binary_multiply, 4343, 4329, 4345);
  g->Binary(ynn_binary_add, 4344, 4345, 4346);
}

// Scope: "Layer40 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer40AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9640, 4347, 0.0059552486054599285, 0);
  g->Dequantize(9664, 4348, 0.047244105488061905, 0);
  g->Slice(4346, 4349, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(4347, 4350, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(4348, 4351, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(4349, 4350, 4353, false, true);
  g->Mask(4353, 8854, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8854, 8524, {-1}, true);
  g->Binary(ynn_binary_subtract, 8854, 8524, 8521);
  g->Unary(ynn_unary_exp, 8521, 8522);
  g->Reduce(ynn_reduce_sum, 8522, 8525, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 8525, 8523);
  g->Binary(ynn_binary_multiply, 8522, 8523, 4354);
  g->Matmul(4354, 4351, 4355, false, false);
  g->Slice(4346, 4356, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(4347, 4357, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(4348, 4358, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(4356, 4357, 4359, false, true);
  g->Mask(4359, 8855, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8855, 8529, {-1}, true);
  g->Binary(ynn_binary_subtract, 8855, 8529, 8526);
  g->Unary(ynn_unary_exp, 8526, 8527);
  g->Reduce(ynn_reduce_sum, 8527, 8530, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 8530, 8528);
  g->Binary(ynn_binary_multiply, 8527, 8528, 4360);
  g->Matmul(4360, 4358, 4362, false, false);
  g->Concat({4355,4362}, 4363, 1);
}

// Scope: "Layer40 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer40AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(4363, 4365, 1, 2);
  g->SplitDim(4365, 4364, 1, {1,8});
  g->FuseDims(4364, 4366, 2, 2);
  g->Quantize(4366, 4367, 0.017839577049016953, 0);
  g->Transpose(9429, 6972, {1,0});
  g->Binary(ynn_binary_multiply, 6969, 6971, 6967);
  g->Dot(4367, 6972, YNN_INVALID_VALUE_ID, 6966, 1);
  g->DequantizeTensor(6966, YNN_INVALID_VALUE_ID, 6967, 6968);
  g->QuantizeTensor(6968, 8727, 6970, 4368);
  g->Dequantize(4368, 4369, 0.07701452821493149, 0);
}

// Scope: "Layer40 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer40Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 4319, 4320);
  g->Reduce(ynn_reduce_sum, 4320, 8513, {2}, true);
  g->ShapeProduct(4320, 8512, {2});
  g->Binary(ynn_binary_divide, 8513, 8512, 4321);
  g->Binary(ynn_binary_add, 4321, 8779, 4322);
  g->Unary(ynn_unary_rsqrt, 4322, 4323);
  g->Binary(ynn_binary_multiply, 4319, 4323, 4324);
  g->Binary(ynn_binary_multiply, 4324, 9418, 4325);
  BuildLayer40AttentionQueryProjection(ctx);
  BuildLayer40AttentionSdpa(ctx);
  BuildLayer40AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 4369, 4370);
  g->Reduce(ynn_reduce_sum, 4370, 8532, {2}, true);
  g->ShapeProduct(4370, 8531, {2});
  g->Binary(ynn_binary_divide, 8532, 8531, 4371);
  g->Binary(ynn_binary_add, 4371, 8779, 4372);
  g->Unary(ynn_unary_rsqrt, 4372, 4375);
  g->Binary(ynn_binary_multiply, 4369, 4375, 4376);
  g->Binary(ynn_binary_multiply, 4376, 9425, 4377);
  g->Binary(ynn_binary_add, 4377, 4319, 4378);
}

// Scope: "Layer40 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer40Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 4378, 4379);
  g->Reduce(ynn_reduce_sum, 4379, 8534, {2}, true);
  g->ShapeProduct(4379, 8533, {2});
  g->Binary(ynn_binary_divide, 8534, 8533, 4380);
  g->Binary(ynn_binary_add, 4380, 8779, 4381);
  g->Unary(ynn_unary_rsqrt, 4381, 4382);
  g->Binary(ynn_binary_multiply, 4378, 4382, 4383);
  g->Binary(ynn_binary_multiply, 4383, 9428, 4384);
  g->Quantize(4384, 4386, 0.030199747532606125, 0);
  g->Transpose(9422, 6979, {1,0});
  g->Binary(ynn_binary_multiply, 6976, 6978, 6974);
  g->Dot(4386, 6979, YNN_INVALID_VALUE_ID, 6973, 1);
  g->DequantizeTensor(6973, YNN_INVALID_VALUE_ID, 6974, 6975);
  g->QuantizeTensor(6975, 8727, 6977, 4387);
  g->Dequantize(4387, 4388, 0.037893712520599365, 0);
  g->Transpose(9421, 6984, {1,0});
  g->Binary(ynn_binary_multiply, 6976, 6983, 6981);
  g->Dot(4386, 6984, YNN_INVALID_VALUE_ID, 6980, 1);
  g->DequantizeTensor(6980, YNN_INVALID_VALUE_ID, 6981, 6982);
  g->QuantizeTensor(6982, 8727, 6977, 4389);
  g->Dequantize(4389, 4390, 0.037893712520599365, 0);
  g->Polynomial(4390, 8537, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8537, 8538);
  g->Binary(ynn_binary_add, 8538, 7293, 8535);
  g->Binary(ynn_binary_multiply, 4390, 7305, 8536);
  g->Binary(ynn_binary_multiply, 8536, 8535, 4391);
  g->Binary(ynn_binary_multiply, 4388, 4391, 4392);
  g->Quantize(4392, 4393, 0.08956693857908249, 0);
  g->Transpose(9420, 6991, {1,0});
  g->Binary(ynn_binary_multiply, 6988, 6990, 6986);
  g->Dot(4393, 6991, YNN_INVALID_VALUE_ID, 6985, 1);
  g->DequantizeTensor(6985, YNN_INVALID_VALUE_ID, 6986, 6987);
  g->QuantizeTensor(6987, 8727, 6989, 4394);
  g->Dequantize(4394, 4396, 0.11817207932472229, 0);
  g->Unary(ynn_unary_square, 4396, 4397);
  g->Reduce(ynn_reduce_sum, 4397, 8540, {2}, true);
  g->ShapeProduct(4397, 8539, {2});
  g->Binary(ynn_binary_divide, 8540, 8539, 4398);
  g->Binary(ynn_binary_add, 4398, 8779, 4399);
  g->Unary(ynn_unary_rsqrt, 4399, 4400);
  g->Binary(ynn_binary_multiply, 4396, 4400, 4401);
  g->Binary(ynn_binary_multiply, 4401, 9426, 4402);
  g->Binary(ynn_binary_add, 4402, 4378, 4403);
}

// Scope: "Layer40 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer40PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(429, 4404, {0,0,40,0}, {-1,-1,1,-1});
  g->Reshape(4404, 4405, {1,1,256});
  g->Unary(ynn_unary_square, 4405, 4407);
  g->Reduce(ynn_reduce_sum, 4407, 8542, {2}, true);
  g->ShapeProduct(4407, 8541, {2});
  g->Binary(ynn_binary_divide, 8542, 8541, 4408);
  g->Binary(ynn_binary_add, 4408, 8779, 4409);
  g->Unary(ynn_unary_rsqrt, 4409, 4410);
  g->Binary(ynn_binary_multiply, 4405, 4410, 4411);
  g->Binary(ynn_binary_multiply, 4411, 9533, 4412);
  g->Binary(ynn_binary_multiply, 9569, 8783, 4413);
  g->Binary(ynn_binary_add, 4412, 4413, 4414);
  g->Binary(ynn_binary_multiply, 4414, 8777, 4415);
  g->Quantize(4403, 4416, 0.34838828444480896, 0);
  g->Transpose(9423, 7004, {1,0});
  g->Binary(ynn_binary_multiply, 7002, 7003, 7000);
  g->Dot(4416, 7004, YNN_INVALID_VALUE_ID, 6999, 1);
  g->DequantizeTensor(6999, YNN_INVALID_VALUE_ID, 7000, 7001);
  g->QuantizeTensor(7001, 8727, 6560, 4418);
  g->Dequantize(4418, 4419, 0.20078741014003754, 0);
  g->Polynomial(4419, 8545, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8545, 8546);
  g->Binary(ynn_binary_add, 8546, 7293, 8543);
  g->Binary(ynn_binary_multiply, 4419, 7305, 8544);
  g->Binary(ynn_binary_multiply, 8544, 8543, 4420);
  g->Binary(ynn_binary_multiply, 4420, 4415, 4421);
  g->Quantize(4421, 4422, 3.496062994003296, 0);
  g->Transpose(9424, 7011, {1,0});
  g->Binary(ynn_binary_multiply, 7008, 7010, 7006);
  g->Dot(4422, 7011, YNN_INVALID_VALUE_ID, 7005, 1);
  g->DequantizeTensor(7005, YNN_INVALID_VALUE_ID, 7006, 7007);
  g->QuantizeTensor(7007, 8727, 7009, 4423);
  g->Dequantize(4423, 4424, 0.6477274894714355, 0);
  g->Unary(ynn_unary_square, 4424, 4425);
  g->Reduce(ynn_reduce_sum, 4425, 8548, {2}, true);
  g->ShapeProduct(4425, 8547, {2});
  g->Binary(ynn_binary_divide, 8548, 8547, 4426);
  g->Binary(ynn_binary_add, 4426, 8779, 4427);
  g->Unary(ynn_unary_rsqrt, 4427, 4429);
  g->Binary(ynn_binary_multiply, 4424, 4429, 4430);
  g->Binary(ynn_binary_multiply, 4430, 9427, 4431);
  g->Binary(ynn_binary_add, 4403, 4431, 4432);
  g->Binary(ynn_binary_multiply, 4432, 9419, 4433);
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
  g->Quantize(4440, 4441, 2.4042584896087646, 0);
  g->Transpose(9445, 7017, {1,0});
  g->Binary(ynn_binary_multiply, 7015, 7016, 7013);
  g->Dot(4441, 7017, YNN_INVALID_VALUE_ID, 7012, 1);
  g->DequantizeTensor(7012, YNN_INVALID_VALUE_ID, 7013, 7014);
  g->QuantizeTensor(7014, 8727, 6301, 4442);
  g->Dequantize(4442, 4443, 1.0629920959472656, 0);
  g->SplitDim(4443, 4444, 2, {8,512});
  g->FuseDims(4444, 4446, 1, 2);
  g->SplitDim(4446, 4445, 1, {8,1});
  g->Unary(ynn_unary_square, 4445, 4447);
  g->Reduce(ynn_reduce_sum, 4447, 8554, {3}, true);
  g->ShapeProduct(4447, 8553, {3});
  g->Binary(ynn_binary_divide, 8554, 8553, 4448);
  g->Binary(ynn_binary_add, 4448, 8779, 4449);
  g->Unary(ynn_unary_rsqrt, 4449, 4450);
  g->Binary(ynn_binary_multiply, 4445, 4450, 4452);
  g->Binary(ynn_binary_multiply, 4452, 9444, 4453);
  g->Slice(4453, 4454, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(4453, 4455, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 4455, 4456);
  g->Concat({4456,4454}, 4457, 3);
  g->Binary(ynn_binary_multiply, 4453, 4959, 4458);
  g->Binary(ynn_binary_multiply, 4457, 2, 4459);
  g->Binary(ynn_binary_add, 4458, 4459, 4460);
}

// Scope: "Layer41 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer41AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9641, 4461, 0.001091228099539876, 0);
  g->Dequantize(9665, 4463, 0.01785714365541935, 0);
  g->Slice(4460, 4464, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(4461, 4465, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(4463, 4466, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(4464, 4465, 4467, false, true);
  g->Mask(4467, 8856, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 8856, 8558, {-1}, true);
  g->Binary(ynn_binary_subtract, 8856, 8558, 8555);
  g->Unary(ynn_unary_exp, 8555, 8556);
  g->Reduce(ynn_reduce_sum, 8556, 8559, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 8559, 8557);
  g->Binary(ynn_binary_multiply, 8556, 8557, 4468);
  g->Matmul(4468, 4466, 4469, false, false);
  g->Slice(4460, 4470, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(4461, 4471, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(4463, 4473, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(4470, 4471, 4474, false, true);
  g->Mask(4474, 8857, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 8857, 8563, {-1}, true);
  g->Binary(ynn_binary_subtract, 8857, 8563, 8560);
  g->Unary(ynn_unary_exp, 8560, 8561);
  g->Reduce(ynn_reduce_sum, 8561, 8564, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 8564, 8562);
  g->Binary(ynn_binary_multiply, 8561, 8562, 4475);
  g->Matmul(4475, 4473, 4476, false, false);
  g->Concat({4469,4476}, 4477, 1);
}

// Scope: "Layer41 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer41AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(4477, 4479, 1, 2);
  g->SplitDim(4479, 4478, 1, {1,8});
  g->FuseDims(4478, 4480, 2, 2);
  g->Quantize(4480, 4481, 0.011441939510405064, 0);
  g->Transpose(9443, 7024, {1,0});
  g->Binary(ynn_binary_multiply, 7021, 7023, 7019);
  g->Dot(4481, 7024, YNN_INVALID_VALUE_ID, 7018, 1);
  g->DequantizeTensor(7018, YNN_INVALID_VALUE_ID, 7019, 7020);
  g->QuantizeTensor(7020, 8727, 7022, 4482);
  g->Dequantize(4482, 4484, 0.010074657388031483, 0);
}

// Scope: "Layer41 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer41Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 4433, 4434);
  g->Reduce(ynn_reduce_sum, 4434, 8550, {2}, true);
  g->ShapeProduct(4434, 8549, {2});
  g->Binary(ynn_binary_divide, 8550, 8549, 4435);
  g->Binary(ynn_binary_add, 4435, 8779, 4436);
  g->Unary(ynn_unary_rsqrt, 4436, 4437);
  g->Binary(ynn_binary_multiply, 4433, 4437, 4438);
  g->Binary(ynn_binary_multiply, 4438, 9432, 4440);
  BuildLayer41AttentionQueryProjection(ctx);
  BuildLayer41AttentionSdpa(ctx);
  BuildLayer41AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 4484, 4485);
  g->Reduce(ynn_reduce_sum, 4485, 8566, {2}, true);
  g->ShapeProduct(4485, 8565, {2});
  g->Binary(ynn_binary_divide, 8566, 8565, 4486);
  g->Binary(ynn_binary_add, 4486, 8779, 4487);
  g->Unary(ynn_unary_rsqrt, 4487, 4488);
  g->Binary(ynn_binary_multiply, 4484, 4488, 4489);
  g->Binary(ynn_binary_multiply, 4489, 9439, 4490);
  g->Binary(ynn_binary_add, 4490, 4433, 4491);
}

// Scope: "Layer41 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer41Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 4491, 4492);
  g->Reduce(ynn_reduce_sum, 4492, 8568, {2}, true);
  g->ShapeProduct(4492, 8567, {2});
  g->Binary(ynn_binary_divide, 8568, 8567, 4493);
  g->Binary(ynn_binary_add, 4493, 8779, 4495);
  g->Unary(ynn_unary_rsqrt, 4495, 4496);
  g->Binary(ynn_binary_multiply, 4491, 4496, 4497);
  g->Binary(ynn_binary_multiply, 4497, 9442, 4498);
  g->Quantize(4498, 4499, 0.023036088794469833, 0);
  g->Transpose(9436, 7031, {1,0});
  g->Binary(ynn_binary_multiply, 7028, 7030, 7026);
  g->Dot(4499, 7031, YNN_INVALID_VALUE_ID, 7025, 1);
  g->DequantizeTensor(7025, YNN_INVALID_VALUE_ID, 7026, 7027);
  g->QuantizeTensor(7027, 8727, 7029, 4500);
  g->Dequantize(4500, 4501, 0.02559056133031845, 0);
  g->Transpose(9435, 7036, {1,0});
  g->Binary(ynn_binary_multiply, 7028, 7035, 7033);
  g->Dot(4499, 7036, YNN_INVALID_VALUE_ID, 7032, 1);
  g->DequantizeTensor(7032, YNN_INVALID_VALUE_ID, 7033, 7034);
  g->QuantizeTensor(7034, 8727, 7029, 4502);
  g->Dequantize(4502, 4503, 0.02559056133031845, 0);
  g->Polynomial(4503, 8571, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8571, 8572);
  g->Binary(ynn_binary_add, 8572, 7293, 8569);
  g->Binary(ynn_binary_multiply, 4503, 7305, 8570);
  g->Binary(ynn_binary_multiply, 8570, 8569, 4505);
  g->Binary(ynn_binary_multiply, 4501, 4505, 4506);
  g->Quantize(4506, 4507, 0.038631901144981384, 0);
  g->Transpose(9434, 7043, {1,0});
  g->Binary(ynn_binary_multiply, 7040, 7042, 7038);
  g->Dot(4507, 7043, YNN_INVALID_VALUE_ID, 7037, 1);
  g->DequantizeTensor(7037, YNN_INVALID_VALUE_ID, 7038, 7039);
  g->QuantizeTensor(7039, 8727, 7041, 4508);
  g->Dequantize(4508, 4509, 0.03348301723599434, 0);
  g->Unary(ynn_unary_square, 4509, 4510);
  g->Reduce(ynn_reduce_sum, 4510, 8574, {2}, true);
  g->ShapeProduct(4510, 8573, {2});
  g->Binary(ynn_binary_divide, 8574, 8573, 4511);
  g->Binary(ynn_binary_add, 4511, 8779, 4512);
  g->Unary(ynn_unary_rsqrt, 4512, 4513);
  g->Binary(ynn_binary_multiply, 4509, 4513, 4514);
  g->Binary(ynn_binary_multiply, 4514, 9440, 4516);
  g->Binary(ynn_binary_add, 4516, 4491, 4517);
}

// Scope: "Layer41 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer41PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(429, 4518, {0,0,41,0}, {-1,-1,1,-1});
  g->Reshape(4518, 4519, {1,1,256});
  g->Unary(ynn_unary_square, 4519, 4520);
  g->Reduce(ynn_reduce_sum, 4520, 8578, {2}, true);
  g->ShapeProduct(4520, 8577, {2});
  g->Binary(ynn_binary_divide, 8578, 8577, 4521);
  g->Binary(ynn_binary_add, 4521, 8779, 4522);
  g->Unary(ynn_unary_rsqrt, 4522, 4523);
  g->Binary(ynn_binary_multiply, 4519, 4523, 4524);
  g->Binary(ynn_binary_multiply, 4524, 9533, 4525);
  g->Binary(ynn_binary_multiply, 9570, 8783, 4527);
  g->Binary(ynn_binary_add, 4525, 4527, 4528);
  g->Binary(ynn_binary_multiply, 4528, 8777, 4529);
  g->Quantize(4517, 4530, 0.37271758913993835, 0);
  g->Transpose(9437, 7049, {1,0});
  g->Binary(ynn_binary_multiply, 7047, 7048, 7045);
  g->Dot(4530, 7049, YNN_INVALID_VALUE_ID, 7044, 1);
  g->DequantizeTensor(7044, YNN_INVALID_VALUE_ID, 7045, 7046);
  g->QuantizeTensor(7046, 8727, 5139, 4531);
  g->Dequantize(4531, 4532, 0.3366141617298126, 0);
  g->Polynomial(4532, 8581, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8581, 8582);
  g->Binary(ynn_binary_add, 8582, 7293, 8579);
  g->Binary(ynn_binary_multiply, 4532, 7305, 8580);
  g->Binary(ynn_binary_multiply, 8580, 8579, 4533);
  g->Binary(ynn_binary_multiply, 4533, 4529, 4534);
  g->Quantize(4534, 4535, 9.259842872619629, 0);
  g->Transpose(9438, 7056, {1,0});
  g->Binary(ynn_binary_multiply, 7053, 7055, 7051);
  g->Dot(4535, 7056, YNN_INVALID_VALUE_ID, 7050, 1);
  g->DequantizeTensor(7050, YNN_INVALID_VALUE_ID, 7051, 7052);
  g->QuantizeTensor(7052, 8727, 7054, 4536);
  g->Dequantize(4536, 4538, 1.999718189239502, 0);
  g->Unary(ynn_unary_square, 4538, 4539);
  g->Reduce(ynn_reduce_sum, 4539, 8584, {2}, true);
  g->ShapeProduct(4539, 8583, {2});
  g->Binary(ynn_binary_divide, 8584, 8583, 4540);
  g->Binary(ynn_binary_add, 4540, 8779, 4541);
  g->Unary(ynn_unary_rsqrt, 4541, 4542);
  g->Binary(ynn_binary_multiply, 4538, 4542, 4543);
  g->Binary(ynn_binary_multiply, 4543, 9441, 4544);
  g->Binary(ynn_binary_add, 4517, 4544, 4545);
  g->Binary(ynn_binary_multiply, 4545, 9433, 4546);
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
  g->Unary(ynn_unary_square, 4546, 4547);
  g->Reduce(ynn_reduce_sum, 4547, 8586, {2}, true);
  g->ShapeProduct(4547, 8585, {2});
  g->Binary(ynn_binary_divide, 8586, 8585, 4550);
  g->Binary(ynn_binary_add, 4550, 8779, 4551);
  g->Unary(ynn_unary_rsqrt, 4551, 4552);
  g->Binary(ynn_binary_multiply, 4546, 4552, 4553);
  g->Binary(ynn_binary_multiply, 4553, 9531, 4554);
  g->Reduce(ynn_reduce_min_max, 4554, 7064, {-1}, true);
  g->DynamicQuantization(7064, 7063, 7062);
  g->QuantizeTensor(4554, 7063, 7062, 7061);
  g->Transpose(8784, 7067, {1,0});
  g->Binary(ynn_binary_multiply, 7062, 7065, 7058);
  g->Reduce(ynn_reduce_sum, 7067, 7066, {0}, true);
  g->Binary(ynn_binary_multiply, 7063, 7066, 7060);
  g->Unary(ynn_unary_negate, 7060, 7059);
  g->Dot(7061, 7067, 7059, 7057, 1);
  g->DequantizeTensor(7057, YNN_INVALID_VALUE_ID, 7058, 4555);
  g->Binary(ynn_binary_multiply, 4555, 8870, 4556);
  g->Unary(ynn_unary_tanh, 4556, 4557);
  g->Binary(ynn_binary_multiply, 4557, 8778, 8785);
  g->ResultShape(8785, {slinky::expr(int64_t{1}),slinky::expr(int64_t{1}),slinky::expr(int64_t{262144})});
}

}  // namespace BuildGemma4DecodeSource
