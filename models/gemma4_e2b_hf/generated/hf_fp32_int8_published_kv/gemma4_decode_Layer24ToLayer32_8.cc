// Generated YNNPACK builder; do not edit.
#include "gemma4_decode_builder.h"

namespace BuildGemma4DecodeSource {

// Scope: "Layer24 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer24AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Binary(ynn_binary_divide, 3879, 7283, 3880);
  g->Unary(ynn_unary_round, 3880, 3881);
  g->Binary(ynn_binary_max, 3881, 7155, 3882);
  g->Binary(ynn_binary_min, 3882, 7270, 3884);
  g->Binary(ynn_binary_multiply, 3884, 7283, 3885);
  g->Convert(7942, 3886);
  g->Binary(ynn_binary_multiply, 3886, 7943, 3887);
  g->Matmul(3885, 3887, 3888, false, true);
  g->Binary(ynn_binary_divide, 3888, 7306, 3889);
  g->Unary(ynn_unary_round, 3889, 3890);
  g->Binary(ynn_binary_max, 3890, 7155, 3891);
  g->Binary(ynn_binary_min, 3891, 7270, 3892);
  g->Binary(ynn_binary_multiply, 3892, 7306, 3893);
  g->SplitDim(3893, 3895, 2, {8,512});
  g->Transpose(3895, 3896, {0,2,1,3});
  g->Unary(ynn_unary_square, 3896, 3897);
  g->Reduce(ynn_reduce_sum, 3897, 6700, {3}, true);
  g->ShapeProduct(3897, 6699, {3});
  g->Binary(ynn_binary_divide, 6700, 6699, 3898);
  g->Binary(ynn_binary_add, 3898, 7303, 3899);
  g->Binary(ynn_binary_pow, 3899, 7358, 3900);
  g->Binary(ynn_binary_multiply, 3896, 3900, 3901);
  g->Convert(7941, 3902);
  g->Binary(ynn_binary_multiply, 3901, 3902, 3903);
  g->Slice(3903, 3904, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(3903, 3906, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 3906, 3907);
  g->Concat({3907,3904}, 3908, 3);
  g->Binary(ynn_binary_multiply, 3903, 5909, 3909);
  g->Binary(ynn_binary_multiply, 3908, 6008, 3910);
  g->Binary(ynn_binary_add, 3909, 3910, 3911);
}

// Scope: "Layer24 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer24AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(3911, 2160, 3912, false, true);
  g->Mask(3912, 7508, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 7508, 6704, {-1}, true);
  g->Binary(ynn_binary_subtract, 7508, 6704, 6701);
  g->Unary(ynn_unary_exp, 6701, 6702);
  g->Reduce(ynn_reduce_sum, 6702, 6705, {-1}, true);
  g->Binary(ynn_binary_divide, 6113, 6705, 6703);
  g->Binary(ynn_binary_multiply, 6702, 6703, 3913);
  g->Matmul(3913, 2162, 3914, false, false);
}

// Scope: "Layer24 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer24AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(3914, 3916, {0,2,1,3});
  g->FuseDims(3916, 3917, 2, 2);
  g->Binary(ynn_binary_divide, 3917, 7347, 3918);
  g->Unary(ynn_unary_round, 3918, 3919);
  g->Binary(ynn_binary_max, 3919, 7155, 3920);
  g->Binary(ynn_binary_min, 3920, 7270, 3921);
  g->Binary(ynn_binary_multiply, 3921, 7347, 3922);
  g->Convert(7939, 3923);
  g->Binary(ynn_binary_multiply, 3923, 7940, 3924);
  g->Matmul(3922, 3924, 3925, false, true);
  g->Binary(ynn_binary_divide, 3925, 7286, 3927);
  g->Unary(ynn_unary_round, 3927, 3928);
  g->Binary(ynn_binary_max, 3928, 7155, 3929);
  g->Binary(ynn_binary_min, 3929, 7270, 3930);
  g->Binary(ynn_binary_multiply, 3930, 7286, 3931);
}

// Scope: "Layer24 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer24Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3871, 3873);
  g->Reduce(ynn_reduce_sum, 3873, 6698, {2}, true);
  g->ShapeProduct(3873, 6697, {2});
  g->Binary(ynn_binary_divide, 6698, 6697, 3874);
  g->Binary(ynn_binary_add, 3874, 7303, 3875);
  g->Binary(ynn_binary_pow, 3875, 7358, 3876);
  g->Binary(ynn_binary_multiply, 3871, 3876, 3877);
  g->Convert(7923, 3878);
  g->Binary(ynn_binary_multiply, 3877, 3878, 3879);
  BuildLayer24AttentionQueryProjection(ctx);
  BuildLayer24AttentionSdpa(ctx);
  BuildLayer24AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 3931, 3932);
  g->Reduce(ynn_reduce_sum, 3932, 6707, {2}, true);
  g->ShapeProduct(3932, 6706, {2});
  g->Binary(ynn_binary_divide, 6707, 6706, 3933);
  g->Binary(ynn_binary_add, 3933, 7303, 3934);
  g->Binary(ynn_binary_pow, 3934, 7358, 3935);
  g->Binary(ynn_binary_multiply, 3931, 3935, 3936);
  g->Convert(7935, 3939);
  g->Binary(ynn_binary_multiply, 3936, 3939, 3940);
  g->Binary(ynn_binary_add, 3871, 3940, 3941);
}

// Scope: "Layer24 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer24Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3941, 3942);
  g->Reduce(ynn_reduce_sum, 3942, 6711, {2}, true);
  g->ShapeProduct(3942, 6710, {2});
  g->Binary(ynn_binary_divide, 6711, 6710, 3943);
  g->Binary(ynn_binary_add, 3943, 7303, 3944);
  g->Binary(ynn_binary_pow, 3944, 7358, 3945);
  g->Binary(ynn_binary_multiply, 3941, 3945, 3946);
  g->Convert(7938, 3947);
  g->Binary(ynn_binary_multiply, 3946, 3947, 3948);
  g->Binary(ynn_binary_divide, 3948, 7356, 3950);
  g->Unary(ynn_unary_round, 3950, 3951);
  g->Binary(ynn_binary_max, 3951, 7155, 3952);
  g->Binary(ynn_binary_min, 3952, 7270, 3953);
  g->Binary(ynn_binary_multiply, 3953, 7356, 3954);
  g->Convert(7929, 3955);
  g->Binary(ynn_binary_multiply, 3955, 7930, 3956);
  g->Matmul(3954, 3956, 3957, false, true);
  g->Binary(ynn_binary_divide, 3957, 7190, 3958);
  g->Unary(ynn_unary_round, 3958, 3959);
  g->Binary(ynn_binary_max, 3959, 7155, 3961);
  g->Binary(ynn_binary_min, 3961, 7270, 3962);
  g->Binary(ynn_binary_multiply, 3962, 7190, 3963);
  g->Convert(7927, 3964);
  g->Binary(ynn_binary_multiply, 3964, 7928, 3965);
  g->Matmul(3954, 3965, 3967, false, true);
  g->Binary(ynn_binary_divide, 3967, 7190, 3968);
  g->Unary(ynn_unary_round, 3968, 3969);
  g->Binary(ynn_binary_max, 3969, 7155, 3970);
  g->Binary(ynn_binary_min, 3970, 7270, 3971);
  g->Binary(ynn_binary_multiply, 3971, 7190, 3972);
  g->Polynomial(3972, 6714, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6714, 6715);
  g->Binary(ynn_binary_add, 6715, 6113, 6712);
  g->Binary(ynn_binary_multiply, 3972, 6111, 6713);
  g->Binary(ynn_binary_multiply, 6713, 6712, 3973);
  g->Binary(ynn_binary_multiply, 3963, 3973, 3974);
  g->Binary(ynn_binary_divide, 3974, 7219, 3975);
  g->Unary(ynn_unary_round, 3975, 3976);
  g->Binary(ynn_binary_max, 3976, 7155, 3978);
  g->Binary(ynn_binary_min, 3978, 7270, 3979);
  g->Binary(ynn_binary_multiply, 3979, 7219, 3980);
  g->Convert(7925, 3981);
  g->Binary(ynn_binary_multiply, 3981, 7926, 3982);
  g->Matmul(3980, 3982, 3983, false, true);
  g->Binary(ynn_binary_divide, 3983, 7242, 3984);
  g->Unary(ynn_unary_round, 3984, 3985);
  g->Binary(ynn_binary_max, 3985, 7155, 3986);
  g->Binary(ynn_binary_min, 3986, 7270, 3987);
  g->Binary(ynn_binary_multiply, 3987, 7242, 3989);
  g->Unary(ynn_unary_square, 3989, 3990);
  g->Reduce(ynn_reduce_sum, 3990, 6717, {2}, true);
  g->ShapeProduct(3990, 6716, {2});
  g->Binary(ynn_binary_divide, 6717, 6716, 3991);
  g->Binary(ynn_binary_add, 3991, 7303, 3992);
  g->Binary(ynn_binary_pow, 3992, 7358, 3993);
  g->Binary(ynn_binary_multiply, 3989, 3993, 3994);
  g->Convert(7936, 3995);
  g->Binary(ynn_binary_multiply, 3994, 3995, 3996);
  g->Binary(ynn_binary_add, 3941, 3996, 3997);
}

// Scope: "Layer24 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer24PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1022, 3998, {0,0,24,0}, {-1,-1,1,-1});
  g->Reshape(3998, 4000, {1,1,256});
  g->Binary(ynn_binary_add, 4000, 8356, 4001);
  g->Binary(ynn_binary_multiply, 4001, 7085, 4002);
  g->Binary(ynn_binary_divide, 3997, 7368, 4003);
  g->Unary(ynn_unary_round, 4003, 4004);
  g->Binary(ynn_binary_max, 4004, 7155, 4005);
  g->Binary(ynn_binary_min, 4005, 7270, 4006);
  g->Binary(ynn_binary_multiply, 4006, 7368, 4007);
  g->Convert(7931, 4008);
  g->Binary(ynn_binary_multiply, 4008, 7932, 4009);
  g->Matmul(4007, 4009, 4011, false, true);
  g->Binary(ynn_binary_divide, 4011, 7077, 4012);
  g->Unary(ynn_unary_round, 4012, 4013);
  g->Binary(ynn_binary_max, 4013, 7155, 4014);
  g->Binary(ynn_binary_min, 4014, 7270, 4015);
  g->Binary(ynn_binary_multiply, 4015, 7077, 4016);
  g->Polynomial(4016, 6720, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6720, 6721);
  g->Binary(ynn_binary_add, 6721, 6113, 6718);
  g->Binary(ynn_binary_multiply, 4016, 6111, 6719);
  g->Binary(ynn_binary_multiply, 6719, 6718, 4017);
  g->Binary(ynn_binary_multiply, 4017, 4002, 4018);
  g->Binary(ynn_binary_divide, 4018, 7398, 4019);
  g->Unary(ynn_unary_round, 4019, 4020);
  g->Binary(ynn_binary_max, 4020, 7155, 4022);
  g->Binary(ynn_binary_min, 4022, 7270, 4023);
  g->Binary(ynn_binary_multiply, 4023, 7398, 4024);
  g->Convert(7933, 4025);
  g->Binary(ynn_binary_multiply, 4025, 7934, 4026);
  g->Matmul(4024, 4026, 4027, false, true);
  g->Binary(ynn_binary_divide, 4027, 7142, 4028);
  g->Unary(ynn_unary_round, 4028, 4029);
  g->Binary(ynn_binary_max, 4029, 7155, 4030);
  g->Binary(ynn_binary_min, 4030, 7270, 4031);
  g->Binary(ynn_binary_multiply, 4031, 7142, 4033);
  g->Unary(ynn_unary_square, 4033, 4034);
  g->Reduce(ynn_reduce_sum, 4034, 6723, {2}, true);
  g->ShapeProduct(4034, 6722, {2});
  g->Binary(ynn_binary_divide, 6723, 6722, 4035);
  g->Binary(ynn_binary_add, 4035, 7303, 4036);
  g->Binary(ynn_binary_pow, 4036, 7358, 4037);
  g->Binary(ynn_binary_multiply, 4033, 4037, 4038);
  g->Convert(7937, 4039);
  g->Binary(ynn_binary_multiply, 4038, 4039, 4040);
  g->Binary(ynn_binary_add, 3997, 4040, 4041);
  g->Convert(7924, 4042);
  g->Binary(ynn_binary_multiply, 4041, 4042, 4045);
}

// Scope: "Layer24"
LAB_YNN_BUILDER_NOINLINE void BuildLayer24(Context& ctx) {
  BuildLayer24Attention(ctx);
  BuildLayer24Mlp(ctx);
  BuildLayer24PerLayerEmbedding(ctx);
}

// Scope: "Layer25 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer25AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Binary(ynn_binary_divide, 4052, 7307, 4053);
  g->Unary(ynn_unary_round, 4053, 4054);
  g->Binary(ynn_binary_max, 4054, 7155, 4056);
  g->Binary(ynn_binary_min, 4056, 7270, 4057);
  g->Binary(ynn_binary_multiply, 4057, 7307, 4058);
  g->Convert(7963, 4059);
  g->Binary(ynn_binary_multiply, 4059, 7964, 4060);
  g->Matmul(4058, 4060, 4061, false, true);
  g->Binary(ynn_binary_divide, 4061, 7419, 4062);
  g->Unary(ynn_unary_round, 4062, 4063);
  g->Binary(ynn_binary_max, 4063, 7155, 4064);
  g->Binary(ynn_binary_min, 4064, 7270, 4065);
  g->Binary(ynn_binary_multiply, 4065, 7419, 4067);
  g->SplitDim(4067, 4068, 2, {8,256});
  g->Transpose(4068, 4069, {0,2,1,3});
  g->Unary(ynn_unary_square, 4069, 4070);
  g->Reduce(ynn_reduce_sum, 4070, 6727, {3}, true);
  g->ShapeProduct(4070, 6726, {3});
  g->Binary(ynn_binary_divide, 6727, 6726, 4071);
  g->Binary(ynn_binary_add, 4071, 7303, 4072);
  g->Binary(ynn_binary_pow, 4072, 7358, 4073);
  g->Binary(ynn_binary_multiply, 4069, 4073, 4074);
  g->Convert(7962, 4075);
  g->Binary(ynn_binary_multiply, 4074, 4075, 4076);
  g->Slice(4076, 4077, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(4076, 4078, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 4078, 4079);
  g->Concat({4079,4077}, 4080, 3);
  g->Binary(ynn_binary_multiply, 4076, 2025, 4081);
  g->Binary(ynn_binary_multiply, 4080, 3078, 4082);
  g->Binary(ynn_binary_add, 4081, 4082, 4083);
}

// Scope: "Layer25 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer25AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(4083, 1946, 4084, false, true);
  g->Mask(4084, 7509, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 7509, 6731, {-1}, true);
  g->Binary(ynn_binary_subtract, 7509, 6731, 6728);
  g->Unary(ynn_unary_exp, 6728, 6729);
  g->Reduce(ynn_reduce_sum, 6729, 6732, {-1}, true);
  g->Binary(ynn_binary_divide, 6113, 6732, 6730);
  g->Binary(ynn_binary_multiply, 6729, 6730, 4085);
  g->Matmul(4085, 1948, 4086, false, false);
}

// Scope: "Layer25 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer25AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(4086, 4087, {0,2,1,3});
  g->FuseDims(4087, 4088, 2, 2);
  g->Binary(ynn_binary_divide, 4088, 7437, 4089);
  g->Unary(ynn_unary_round, 4089, 4090);
  g->Binary(ynn_binary_max, 4090, 7155, 4091);
  g->Binary(ynn_binary_min, 4091, 7270, 4092);
  g->Binary(ynn_binary_multiply, 4092, 7437, 4093);
  g->Convert(7960, 4094);
  g->Binary(ynn_binary_multiply, 4094, 7961, 4095);
  g->Matmul(4093, 4095, 4096, false, true);
  g->Binary(ynn_binary_divide, 4096, 7459, 4097);
  g->Unary(ynn_unary_round, 4097, 4098);
  g->Binary(ynn_binary_max, 4098, 7155, 4099);
  g->Binary(ynn_binary_min, 4099, 7270, 4100);
  g->Binary(ynn_binary_multiply, 4100, 7459, 4101);
}

// Scope: "Layer25 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer25Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 4045, 4046);
  g->Reduce(ynn_reduce_sum, 4046, 6725, {2}, true);
  g->ShapeProduct(4046, 6724, {2});
  g->Binary(ynn_binary_divide, 6725, 6724, 4047);
  g->Binary(ynn_binary_add, 4047, 7303, 4048);
  g->Binary(ynn_binary_pow, 4048, 7358, 4049);
  g->Binary(ynn_binary_multiply, 4045, 4049, 4050);
  g->Convert(7944, 4051);
  g->Binary(ynn_binary_multiply, 4050, 4051, 4052);
  BuildLayer25AttentionQueryProjection(ctx);
  BuildLayer25AttentionSdpa(ctx);
  BuildLayer25AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 4101, 4102);
  g->Reduce(ynn_reduce_sum, 4102, 6734, {2}, true);
  g->ShapeProduct(4102, 6733, {2});
  g->Binary(ynn_binary_divide, 6734, 6733, 4103);
  g->Binary(ynn_binary_add, 4103, 7303, 4104);
  g->Binary(ynn_binary_pow, 4104, 7358, 4105);
  g->Binary(ynn_binary_multiply, 4101, 4105, 4106);
  g->Convert(7956, 4107);
  g->Binary(ynn_binary_multiply, 4106, 4107, 4108);
  g->Binary(ynn_binary_add, 4045, 4108, 4109);
}

// Scope: "Layer25 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer25Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 4109, 4110);
  g->Reduce(ynn_reduce_sum, 4110, 6736, {2}, true);
  g->ShapeProduct(4110, 6735, {2});
  g->Binary(ynn_binary_divide, 6736, 6735, 4111);
  g->Binary(ynn_binary_add, 4111, 7303, 4112);
  g->Binary(ynn_binary_pow, 4112, 7358, 4113);
  g->Binary(ynn_binary_multiply, 4109, 4113, 4114);
  g->Convert(7959, 4115);
  g->Binary(ynn_binary_multiply, 4114, 4115, 4116);
  g->Binary(ynn_binary_divide, 4116, 7379, 4117);
  g->Unary(ynn_unary_round, 4117, 4118);
  g->Binary(ynn_binary_max, 4118, 7155, 4119);
  g->Binary(ynn_binary_min, 4119, 7270, 4120);
  g->Binary(ynn_binary_multiply, 4120, 7379, 4121);
  g->Convert(7950, 4122);
  g->Binary(ynn_binary_multiply, 4122, 7951, 4123);
  g->Matmul(4121, 4123, 4124, false, true);
  g->Binary(ynn_binary_divide, 4124, 7395, 4125);
  g->Unary(ynn_unary_round, 4125, 4127);
  g->Binary(ynn_binary_max, 4127, 7155, 4128);
  g->Binary(ynn_binary_min, 4128, 7270, 4129);
  g->Binary(ynn_binary_multiply, 4129, 7395, 4130);
  g->Convert(7948, 4131);
  g->Binary(ynn_binary_multiply, 4131, 7949, 4133);
  g->Matmul(4121, 4133, 4134, false, true);
  g->Binary(ynn_binary_divide, 4134, 7395, 4135);
  g->Unary(ynn_unary_round, 4135, 4136);
  g->Binary(ynn_binary_max, 4136, 7155, 4137);
  g->Binary(ynn_binary_min, 4137, 7270, 4138);
  g->Binary(ynn_binary_multiply, 4138, 7395, 4139);
  g->Polynomial(4139, 6739, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6739, 6740);
  g->Binary(ynn_binary_add, 6740, 6113, 6737);
  g->Binary(ynn_binary_multiply, 4139, 6111, 6738);
  g->Binary(ynn_binary_multiply, 6738, 6737, 4140);
  g->Binary(ynn_binary_multiply, 4130, 4140, 4141);
  g->Binary(ynn_binary_divide, 4141, 7162, 4142);
  g->Unary(ynn_unary_round, 4142, 4146);
  g->Binary(ynn_binary_max, 4146, 7155, 4147);
  g->Binary(ynn_binary_min, 4147, 7270, 4148);
  g->Binary(ynn_binary_multiply, 4148, 7162, 4149);
  g->Convert(7946, 4150);
  g->Binary(ynn_binary_multiply, 4150, 7947, 4151);
  g->Matmul(4149, 4151, 4152, false, true);
  g->Binary(ynn_binary_divide, 4152, 7483, 4153);
  g->Unary(ynn_unary_round, 4153, 4154);
  g->Binary(ynn_binary_max, 4154, 7155, 4155);
  g->Binary(ynn_binary_min, 4155, 7270, 4157);
  g->Binary(ynn_binary_multiply, 4157, 7483, 4158);
  g->Unary(ynn_unary_square, 4158, 4159);
  g->Reduce(ynn_reduce_sum, 4159, 6742, {2}, true);
  g->ShapeProduct(4159, 6741, {2});
  g->Binary(ynn_binary_divide, 6742, 6741, 4160);
  g->Binary(ynn_binary_add, 4160, 7303, 4161);
  g->Binary(ynn_binary_pow, 4161, 7358, 4162);
  g->Binary(ynn_binary_multiply, 4158, 4162, 4163);
  g->Convert(7957, 4164);
  g->Binary(ynn_binary_multiply, 4163, 4164, 4165);
  g->Binary(ynn_binary_add, 4109, 4165, 4166);
}

// Scope: "Layer25 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer25PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1022, 4168, {0,0,25,0}, {-1,-1,1,-1});
  g->Reshape(4168, 4169, {1,1,256});
  g->Binary(ynn_binary_add, 4169, 8357, 4170);
  g->Binary(ynn_binary_multiply, 4170, 7085, 4171);
  g->Binary(ynn_binary_divide, 4166, 7298, 4172);
  g->Unary(ynn_unary_round, 4172, 4173);
  g->Binary(ynn_binary_max, 4173, 7155, 4174);
  g->Binary(ynn_binary_min, 4174, 7270, 4175);
  g->Binary(ynn_binary_multiply, 4175, 7298, 4176);
  g->Convert(7952, 4177);
  g->Binary(ynn_binary_multiply, 4177, 7953, 4179);
  g->Matmul(4176, 4179, 4180, false, true);
  g->Binary(ynn_binary_divide, 4180, 7435, 4181);
  g->Unary(ynn_unary_round, 4181, 4182);
  g->Binary(ynn_binary_max, 4182, 7155, 4183);
  g->Binary(ynn_binary_min, 4183, 7270, 4184);
  g->Binary(ynn_binary_multiply, 4184, 7435, 4185);
  g->Polynomial(4185, 6745, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6745, 6746);
  g->Binary(ynn_binary_add, 6746, 6113, 6743);
  g->Binary(ynn_binary_multiply, 4185, 6111, 6744);
  g->Binary(ynn_binary_multiply, 6744, 6743, 4186);
  g->Binary(ynn_binary_multiply, 4186, 4171, 4187);
  g->Binary(ynn_binary_divide, 4187, 7211, 4188);
  g->Unary(ynn_unary_round, 4188, 4190);
  g->Binary(ynn_binary_max, 4190, 7155, 4191);
  g->Binary(ynn_binary_min, 4191, 7270, 4192);
  g->Binary(ynn_binary_multiply, 4192, 7211, 4193);
  g->Convert(7954, 4194);
  g->Binary(ynn_binary_multiply, 4194, 7955, 4195);
  g->Matmul(4193, 4195, 4196, false, true);
  g->Binary(ynn_binary_divide, 4196, 7406, 4197);
  g->Unary(ynn_unary_round, 4197, 4198);
  g->Binary(ynn_binary_max, 4198, 7155, 4199);
  g->Binary(ynn_binary_min, 4199, 7270, 4201);
  g->Binary(ynn_binary_multiply, 4201, 7406, 4202);
  g->Unary(ynn_unary_square, 4202, 4203);
  g->Reduce(ynn_reduce_sum, 4203, 6748, {2}, true);
  g->ShapeProduct(4203, 6747, {2});
  g->Binary(ynn_binary_divide, 6748, 6747, 4204);
  g->Binary(ynn_binary_add, 4204, 7303, 4205);
  g->Binary(ynn_binary_pow, 4205, 7358, 4206);
  g->Binary(ynn_binary_multiply, 4202, 4206, 4207);
  g->Convert(7958, 4208);
  g->Binary(ynn_binary_multiply, 4207, 4208, 4209);
  g->Binary(ynn_binary_add, 4166, 4209, 4210);
  g->Convert(7945, 4212);
  g->Binary(ynn_binary_multiply, 4210, 4212, 4213);
}

// Scope: "Layer25"
LAB_YNN_BUILDER_NOINLINE void BuildLayer25(Context& ctx) {
  BuildLayer25Attention(ctx);
  BuildLayer25Mlp(ctx);
  BuildLayer25PerLayerEmbedding(ctx);
}

// Scope: "Layer26 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer26AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Binary(ynn_binary_divide, 4220, 7357, 4221);
  g->Unary(ynn_unary_round, 4221, 4223);
  g->Binary(ynn_binary_max, 4223, 7155, 4224);
  g->Binary(ynn_binary_min, 4224, 7270, 4225);
  g->Binary(ynn_binary_multiply, 4225, 7357, 4226);
  g->Convert(7984, 4227);
  g->Binary(ynn_binary_multiply, 4227, 7985, 4228);
  g->Matmul(4226, 4228, 4229, false, true);
  g->Binary(ynn_binary_divide, 4229, 7344, 4230);
  g->Unary(ynn_unary_round, 4230, 4231);
  g->Binary(ynn_binary_max, 4231, 7155, 4232);
  g->Binary(ynn_binary_min, 4232, 7270, 4234);
  g->Binary(ynn_binary_multiply, 4234, 7344, 4235);
  g->SplitDim(4235, 4236, 2, {8,256});
  g->Transpose(4236, 4237, {0,2,1,3});
  g->Unary(ynn_unary_square, 4237, 4238);
  g->Reduce(ynn_reduce_sum, 4238, 6752, {3}, true);
  g->ShapeProduct(4238, 6751, {3});
  g->Binary(ynn_binary_divide, 6752, 6751, 4239);
  g->Binary(ynn_binary_add, 4239, 7303, 4240);
  g->Binary(ynn_binary_pow, 4240, 7358, 4241);
  g->Binary(ynn_binary_multiply, 4237, 4241, 4242);
  g->Convert(7983, 4243);
  g->Binary(ynn_binary_multiply, 4242, 4243, 4245);
  g->Slice(4245, 4246, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(4245, 4247, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 4247, 4248);
  g->Concat({4248,4246}, 4249, 3);
  g->Binary(ynn_binary_multiply, 4245, 2025, 4250);
  g->Binary(ynn_binary_multiply, 4249, 3078, 4251);
  g->Binary(ynn_binary_add, 4250, 4251, 4252);
}

// Scope: "Layer26 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer26AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(4252, 1946, 4253, false, true);
  g->Mask(4253, 7510, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 7510, 6758, {-1}, true);
  g->Binary(ynn_binary_subtract, 7510, 6758, 6755);
  g->Unary(ynn_unary_exp, 6755, 6756);
  g->Reduce(ynn_reduce_sum, 6756, 6759, {-1}, true);
  g->Binary(ynn_binary_divide, 6113, 6759, 6757);
  g->Binary(ynn_binary_multiply, 6756, 6757, 4256);
  g->Matmul(4256, 1948, 4257, false, false);
}

// Scope: "Layer26 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer26AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(4257, 4258, {0,2,1,3});
  g->FuseDims(4258, 4259, 2, 2);
  g->Binary(ynn_binary_divide, 4259, 7434, 4260);
  g->Unary(ynn_unary_round, 4260, 4261);
  g->Binary(ynn_binary_max, 4261, 7155, 4262);
  g->Binary(ynn_binary_min, 4262, 7270, 4263);
  g->Binary(ynn_binary_multiply, 4263, 7434, 4264);
  g->Convert(7981, 4265);
  g->Binary(ynn_binary_multiply, 4265, 7982, 4267);
  g->Matmul(4264, 4267, 4268, false, true);
  g->Binary(ynn_binary_divide, 4268, 7131, 4269);
  g->Unary(ynn_unary_round, 4269, 4270);
  g->Binary(ynn_binary_max, 4270, 7155, 4271);
  g->Binary(ynn_binary_min, 4271, 7270, 4272);
  g->Binary(ynn_binary_multiply, 4272, 7131, 4273);
}

// Scope: "Layer26 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer26Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 4213, 4214);
  g->Reduce(ynn_reduce_sum, 4214, 6750, {2}, true);
  g->ShapeProduct(4214, 6749, {2});
  g->Binary(ynn_binary_divide, 6750, 6749, 4215);
  g->Binary(ynn_binary_add, 4215, 7303, 4216);
  g->Binary(ynn_binary_pow, 4216, 7358, 4217);
  g->Binary(ynn_binary_multiply, 4213, 4217, 4218);
  g->Convert(7965, 4219);
  g->Binary(ynn_binary_multiply, 4218, 4219, 4220);
  BuildLayer26AttentionQueryProjection(ctx);
  BuildLayer26AttentionSdpa(ctx);
  BuildLayer26AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 4273, 4274);
  g->Reduce(ynn_reduce_sum, 4274, 6761, {2}, true);
  g->ShapeProduct(4274, 6760, {2});
  g->Binary(ynn_binary_divide, 6761, 6760, 4275);
  g->Binary(ynn_binary_add, 4275, 7303, 4276);
  g->Binary(ynn_binary_pow, 4276, 7358, 4278);
  g->Binary(ynn_binary_multiply, 4273, 4278, 4279);
  g->Convert(7977, 4280);
  g->Binary(ynn_binary_multiply, 4279, 4280, 4281);
  g->Binary(ynn_binary_add, 4213, 4281, 4282);
}

// Scope: "Layer26 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer26Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 4282, 4283);
  g->Reduce(ynn_reduce_sum, 4283, 6763, {2}, true);
  g->ShapeProduct(4283, 6762, {2});
  g->Binary(ynn_binary_divide, 6763, 6762, 4284);
  g->Binary(ynn_binary_add, 4284, 7303, 4285);
  g->Binary(ynn_binary_pow, 4285, 7358, 4286);
  g->Binary(ynn_binary_multiply, 4282, 4286, 4287);
  g->Convert(7980, 4289);
  g->Binary(ynn_binary_multiply, 4287, 4289, 4290);
  g->Binary(ynn_binary_divide, 4290, 7404, 4291);
  g->Unary(ynn_unary_round, 4291, 4292);
  g->Binary(ynn_binary_max, 4292, 7155, 4293);
  g->Binary(ynn_binary_min, 4293, 7270, 4294);
  g->Binary(ynn_binary_multiply, 4294, 7404, 4295);
  g->Convert(7971, 4296);
  g->Binary(ynn_binary_multiply, 4296, 7972, 4297);
  g->Matmul(4295, 4297, 4298, false, true);
  g->Binary(ynn_binary_divide, 4298, 7317, 4299);
  g->Unary(ynn_unary_round, 4299, 4300);
  g->Binary(ynn_binary_max, 4300, 7155, 4301);
  g->Binary(ynn_binary_min, 4301, 7270, 4302);
  g->Binary(ynn_binary_multiply, 4302, 7317, 4303);
  g->Convert(7969, 4304);
  g->Binary(ynn_binary_multiply, 4304, 7970, 4305);
  g->Matmul(4295, 4305, 4306, false, true);
  g->Binary(ynn_binary_divide, 4306, 7317, 4307);
  g->Unary(ynn_unary_round, 4307, 4308);
  g->Binary(ynn_binary_max, 4308, 7155, 4309);
  g->Binary(ynn_binary_min, 4309, 7270, 4310);
  g->Binary(ynn_binary_multiply, 4310, 7317, 4311);
  g->Polynomial(4311, 6766, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6766, 6767);
  g->Binary(ynn_binary_add, 6767, 6113, 6764);
  g->Binary(ynn_binary_multiply, 4311, 6111, 6765);
  g->Binary(ynn_binary_multiply, 6765, 6764, 4312);
  g->Binary(ynn_binary_multiply, 4303, 4312, 4313);
  g->Binary(ynn_binary_divide, 4313, 7411, 4315);
  g->Unary(ynn_unary_round, 4315, 4316);
  g->Binary(ynn_binary_max, 4316, 7155, 4317);
  g->Binary(ynn_binary_min, 4317, 7270, 4318);
  g->Binary(ynn_binary_multiply, 4318, 7411, 4319);
  g->Convert(7967, 4320);
  g->Binary(ynn_binary_multiply, 4320, 7968, 4321);
  g->Matmul(4319, 4321, 4322, false, true);
  g->Binary(ynn_binary_divide, 4322, 7134, 4323);
  g->Unary(ynn_unary_round, 4323, 4324);
  g->Binary(ynn_binary_max, 4324, 7155, 4326);
  g->Binary(ynn_binary_min, 4326, 7270, 4327);
  g->Binary(ynn_binary_multiply, 4327, 7134, 4328);
  g->Unary(ynn_unary_square, 4328, 4329);
  g->Reduce(ynn_reduce_sum, 4329, 6769, {2}, true);
  g->ShapeProduct(4329, 6768, {2});
  g->Binary(ynn_binary_divide, 6769, 6768, 4330);
  g->Binary(ynn_binary_add, 4330, 7303, 4331);
  g->Binary(ynn_binary_pow, 4331, 7358, 4332);
  g->Binary(ynn_binary_multiply, 4328, 4332, 4333);
  g->Convert(7978, 4334);
  g->Binary(ynn_binary_multiply, 4333, 4334, 4335);
  g->Binary(ynn_binary_add, 4282, 4335, 4336);
}

// Scope: "Layer26 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer26PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1022, 4337, {0,0,26,0}, {-1,-1,1,-1});
  g->Reshape(4337, 4338, {1,1,256});
  g->Binary(ynn_binary_add, 4338, 8358, 4339);
  g->Binary(ynn_binary_multiply, 4339, 7085, 4340);
  g->Binary(ynn_binary_divide, 4336, 7478, 4341);
  g->Unary(ynn_unary_round, 4341, 4342);
  g->Binary(ynn_binary_max, 4342, 7155, 4343);
  g->Binary(ynn_binary_min, 4343, 7270, 4344);
  g->Binary(ynn_binary_multiply, 4344, 7478, 4345);
  g->Convert(7973, 4346);
  g->Binary(ynn_binary_multiply, 4346, 7974, 4347);
  g->Matmul(4345, 4347, 4348, false, true);
  g->Binary(ynn_binary_divide, 4348, 7475, 4349);
  g->Unary(ynn_unary_round, 4349, 4350);
  g->Binary(ynn_binary_max, 4350, 7155, 4351);
  g->Binary(ynn_binary_min, 4351, 7270, 4352);
  g->Binary(ynn_binary_multiply, 4352, 7475, 4353);
  g->Polynomial(4353, 6772, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6772, 6773);
  g->Binary(ynn_binary_add, 6773, 6113, 6770);
  g->Binary(ynn_binary_multiply, 4353, 6111, 6771);
  g->Binary(ynn_binary_multiply, 6771, 6770, 4354);
  g->Binary(ynn_binary_multiply, 4354, 4340, 4355);
  g->Binary(ynn_binary_divide, 4355, 7443, 4358);
  g->Unary(ynn_unary_round, 4358, 4359);
  g->Binary(ynn_binary_max, 4359, 7155, 4360);
  g->Binary(ynn_binary_min, 4360, 7270, 4361);
  g->Binary(ynn_binary_multiply, 4361, 7443, 4362);
  g->Convert(7975, 4363);
  g->Binary(ynn_binary_multiply, 4363, 7976, 4364);
  g->Matmul(4362, 4364, 4365, false, true);
  g->Binary(ynn_binary_divide, 4365, 7287, 4366);
  g->Unary(ynn_unary_round, 4366, 4367);
  g->Binary(ynn_binary_max, 4367, 7155, 4368);
  g->Binary(ynn_binary_min, 4368, 7270, 4369);
  g->Binary(ynn_binary_multiply, 4369, 7287, 4370);
  g->Unary(ynn_unary_square, 4370, 4371);
  g->Reduce(ynn_reduce_sum, 4371, 6775, {2}, true);
  g->ShapeProduct(4371, 6774, {2});
  g->Binary(ynn_binary_divide, 6775, 6774, 4372);
  g->Binary(ynn_binary_add, 4372, 7303, 4373);
  g->Binary(ynn_binary_pow, 4373, 7358, 4374);
  g->Binary(ynn_binary_multiply, 4370, 4374, 4375);
  g->Convert(7979, 4376);
  g->Binary(ynn_binary_multiply, 4375, 4376, 4377);
  g->Binary(ynn_binary_add, 4336, 4377, 4378);
  g->Convert(7966, 4379);
  g->Binary(ynn_binary_multiply, 4378, 4379, 4380);
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
  g->Binary(ynn_binary_divide, 4387, 7442, 4388);
  g->Unary(ynn_unary_round, 4388, 4389);
  g->Binary(ynn_binary_max, 4389, 7155, 4390);
  g->Binary(ynn_binary_min, 4390, 7270, 4391);
  g->Binary(ynn_binary_multiply, 4391, 7442, 4392);
  g->Convert(8005, 4393);
  g->Binary(ynn_binary_multiply, 4393, 8006, 4394);
  g->Matmul(4392, 4394, 4395, false, true);
  g->Binary(ynn_binary_divide, 4395, 7165, 4396);
  g->Unary(ynn_unary_round, 4396, 4397);
  g->Binary(ynn_binary_max, 4397, 7155, 4398);
  g->Binary(ynn_binary_min, 4398, 7270, 4399);
  g->Binary(ynn_binary_multiply, 4399, 7165, 4400);
  g->SplitDim(4400, 4401, 2, {8,256});
  g->Transpose(4401, 4402, {0,2,1,3});
  g->Unary(ynn_unary_square, 4402, 4403);
  g->Reduce(ynn_reduce_sum, 4403, 6779, {3}, true);
  g->ShapeProduct(4403, 6778, {3});
  g->Binary(ynn_binary_divide, 6779, 6778, 4404);
  g->Binary(ynn_binary_add, 4404, 7303, 4405);
  g->Binary(ynn_binary_pow, 4405, 7358, 4406);
  g->Binary(ynn_binary_multiply, 4402, 4406, 4407);
  g->Convert(8004, 4408);
  g->Binary(ynn_binary_multiply, 4407, 4408, 4409);
  g->Slice(4409, 4410, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(4409, 4411, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 4411, 4412);
  g->Concat({4412,4410}, 4413, 3);
  g->Binary(ynn_binary_multiply, 4409, 2025, 4414);
  g->Binary(ynn_binary_multiply, 4413, 3078, 4415);
  g->Binary(ynn_binary_add, 4414, 4415, 4416);
}

// Scope: "Layer27 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer27AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(4416, 1946, 4417, false, true);
  g->Mask(4417, 7511, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 7511, 6783, {-1}, true);
  g->Binary(ynn_binary_subtract, 7511, 6783, 6780);
  g->Unary(ynn_unary_exp, 6780, 6781);
  g->Reduce(ynn_reduce_sum, 6781, 6784, {-1}, true);
  g->Binary(ynn_binary_divide, 6113, 6784, 6782);
  g->Binary(ynn_binary_multiply, 6781, 6782, 4419);
  g->Matmul(4419, 1948, 4420, false, false);
}

// Scope: "Layer27 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer27AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(4420, 4421, {0,2,1,3});
  g->FuseDims(4421, 4422, 2, 2);
  g->Binary(ynn_binary_divide, 4422, 7463, 4423);
  g->Unary(ynn_unary_round, 4423, 4424);
  g->Binary(ynn_binary_max, 4424, 7155, 4425);
  g->Binary(ynn_binary_min, 4425, 7270, 4426);
  g->Binary(ynn_binary_multiply, 4426, 7463, 4427);
  g->Convert(8002, 4429);
  g->Binary(ynn_binary_multiply, 4429, 8003, 4430);
  g->Matmul(4427, 4430, 4431, false, true);
  g->Binary(ynn_binary_divide, 4431, 7377, 4432);
  g->Unary(ynn_unary_round, 4432, 4433);
  g->Binary(ynn_binary_max, 4433, 7155, 4434);
  g->Binary(ynn_binary_min, 4434, 7270, 4435);
  g->Binary(ynn_binary_multiply, 4435, 7377, 4436);
}

// Scope: "Layer27 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer27Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 4380, 4381);
  g->Reduce(ynn_reduce_sum, 4381, 6777, {2}, true);
  g->ShapeProduct(4381, 6776, {2});
  g->Binary(ynn_binary_divide, 6777, 6776, 4382);
  g->Binary(ynn_binary_add, 4382, 7303, 4383);
  g->Binary(ynn_binary_pow, 4383, 7358, 4384);
  g->Binary(ynn_binary_multiply, 4380, 4384, 4385);
  g->Convert(7986, 4386);
  g->Binary(ynn_binary_multiply, 4385, 4386, 4387);
  BuildLayer27AttentionQueryProjection(ctx);
  BuildLayer27AttentionSdpa(ctx);
  BuildLayer27AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 4436, 4437);
  g->Reduce(ynn_reduce_sum, 4437, 6786, {2}, true);
  g->ShapeProduct(4437, 6785, {2});
  g->Binary(ynn_binary_divide, 6786, 6785, 4438);
  g->Binary(ynn_binary_add, 4438, 7303, 4440);
  g->Binary(ynn_binary_pow, 4440, 7358, 4441);
  g->Binary(ynn_binary_multiply, 4436, 4441, 4442);
  g->Convert(7998, 4443);
  g->Binary(ynn_binary_multiply, 4442, 4443, 4444);
  g->Binary(ynn_binary_add, 4380, 4444, 4445);
}

// Scope: "Layer27 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer27Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 4445, 4446);
  g->Reduce(ynn_reduce_sum, 4446, 6788, {2}, true);
  g->ShapeProduct(4446, 6787, {2});
  g->Binary(ynn_binary_divide, 6788, 6787, 4447);
  g->Binary(ynn_binary_add, 4447, 7303, 4448);
  g->Binary(ynn_binary_pow, 4448, 7358, 4449);
  g->Binary(ynn_binary_multiply, 4445, 4449, 4451);
  g->Convert(8001, 4452);
  g->Binary(ynn_binary_multiply, 4451, 4452, 4453);
  g->Binary(ynn_binary_divide, 4453, 7381, 4454);
  g->Unary(ynn_unary_round, 4454, 4455);
  g->Binary(ynn_binary_max, 4455, 7155, 4456);
  g->Binary(ynn_binary_min, 4456, 7270, 4457);
  g->Binary(ynn_binary_multiply, 4457, 7381, 4458);
  g->Convert(7992, 4459);
  g->Binary(ynn_binary_multiply, 4459, 7993, 4460);
  g->Matmul(4458, 4460, 4463, false, true);
  g->Binary(ynn_binary_divide, 4463, 7482, 4464);
  g->Unary(ynn_unary_round, 4464, 4465);
  g->Binary(ynn_binary_max, 4465, 7155, 4466);
  g->Binary(ynn_binary_min, 4466, 7270, 4467);
  g->Binary(ynn_binary_multiply, 4467, 7482, 4468);
  g->Convert(7990, 4470);
  g->Binary(ynn_binary_multiply, 4470, 7991, 4471);
  g->Matmul(4458, 4471, 4472, false, true);
  g->Binary(ynn_binary_divide, 4472, 7482, 4473);
  g->Unary(ynn_unary_round, 4473, 4474);
  g->Binary(ynn_binary_max, 4474, 7155, 4475);
  g->Binary(ynn_binary_min, 4475, 7270, 4476);
  g->Binary(ynn_binary_multiply, 4476, 7482, 4477);
  g->Polynomial(4477, 6791, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6791, 6792);
  g->Binary(ynn_binary_add, 6792, 6113, 6789);
  g->Binary(ynn_binary_multiply, 4477, 6111, 6790);
  g->Binary(ynn_binary_multiply, 6790, 6789, 4478);
  g->Binary(ynn_binary_multiply, 4468, 4478, 4480);
  g->Binary(ynn_binary_divide, 4480, 7251, 4481);
  g->Unary(ynn_unary_round, 4481, 4482);
  g->Binary(ynn_binary_max, 4482, 7155, 4483);
  g->Binary(ynn_binary_min, 4483, 7270, 4484);
  g->Binary(ynn_binary_multiply, 4484, 7251, 4485);
  g->Convert(7988, 4486);
  g->Binary(ynn_binary_multiply, 4486, 7989, 4487);
  g->Matmul(4485, 4487, 4488, false, true);
  g->Binary(ynn_binary_divide, 4488, 7088, 4489);
  g->Unary(ynn_unary_round, 4489, 4491);
  g->Binary(ynn_binary_max, 4491, 7155, 4492);
  g->Binary(ynn_binary_min, 4492, 7270, 4493);
  g->Binary(ynn_binary_multiply, 4493, 7088, 4494);
  g->Unary(ynn_unary_square, 4494, 4495);
  g->Reduce(ynn_reduce_sum, 4495, 6794, {2}, true);
  g->ShapeProduct(4495, 6793, {2});
  g->Binary(ynn_binary_divide, 6794, 6793, 4496);
  g->Binary(ynn_binary_add, 4496, 7303, 4497);
  g->Binary(ynn_binary_pow, 4497, 7358, 4498);
  g->Binary(ynn_binary_multiply, 4494, 4498, 4499);
  g->Convert(7999, 4500);
  g->Binary(ynn_binary_multiply, 4499, 4500, 4502);
  g->Binary(ynn_binary_add, 4445, 4502, 4503);
}

// Scope: "Layer27 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer27PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1022, 4504, {0,0,27,0}, {-1,-1,1,-1});
  g->Reshape(4504, 4505, {1,1,256});
  g->Binary(ynn_binary_add, 4505, 8359, 4506);
  g->Binary(ynn_binary_multiply, 4506, 7085, 4507);
  g->Binary(ynn_binary_divide, 4503, 7279, 4508);
  g->Unary(ynn_unary_round, 4508, 4509);
  g->Binary(ynn_binary_max, 4509, 7155, 4510);
  g->Binary(ynn_binary_min, 4510, 7270, 4511);
  g->Binary(ynn_binary_multiply, 4511, 7279, 4513);
  g->Convert(7994, 4514);
  g->Binary(ynn_binary_multiply, 4514, 7995, 4515);
  g->Matmul(4513, 4515, 4516, false, true);
  g->Binary(ynn_binary_divide, 4516, 7439, 4517);
  g->Unary(ynn_unary_round, 4517, 4518);
  g->Binary(ynn_binary_max, 4518, 7155, 4519);
  g->Binary(ynn_binary_min, 4519, 7270, 4520);
  g->Binary(ynn_binary_multiply, 4520, 7439, 4521);
  g->Polynomial(4521, 6797, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6797, 6798);
  g->Binary(ynn_binary_add, 6798, 6113, 6795);
  g->Binary(ynn_binary_multiply, 4521, 6111, 6796);
  g->Binary(ynn_binary_multiply, 6796, 6795, 4522);
  g->Binary(ynn_binary_multiply, 4522, 4507, 4524);
  g->Binary(ynn_binary_divide, 4524, 7351, 4525);
  g->Unary(ynn_unary_round, 4525, 4526);
  g->Binary(ynn_binary_max, 4526, 7155, 4527);
  g->Binary(ynn_binary_min, 4527, 7270, 4528);
  g->Binary(ynn_binary_multiply, 4528, 7351, 4529);
  g->Convert(7996, 4530);
  g->Binary(ynn_binary_multiply, 4530, 7997, 4531);
  g->Matmul(4529, 4531, 4532, false, true);
  g->Binary(ynn_binary_divide, 4532, 7238, 4533);
  g->Unary(ynn_unary_round, 4533, 4535);
  g->Binary(ynn_binary_max, 4535, 7155, 4536);
  g->Binary(ynn_binary_min, 4536, 7270, 4537);
  g->Binary(ynn_binary_multiply, 4537, 7238, 4538);
  g->Unary(ynn_unary_square, 4538, 4539);
  g->Reduce(ynn_reduce_sum, 4539, 6802, {2}, true);
  g->ShapeProduct(4539, 6801, {2});
  g->Binary(ynn_binary_divide, 6802, 6801, 4540);
  g->Binary(ynn_binary_add, 4540, 7303, 4541);
  g->Binary(ynn_binary_pow, 4541, 7358, 4542);
  g->Binary(ynn_binary_multiply, 4538, 4542, 4543);
  g->Convert(8000, 4544);
  g->Binary(ynn_binary_multiply, 4543, 4544, 4546);
  g->Binary(ynn_binary_add, 4503, 4546, 4547);
  g->Convert(7987, 4548);
  g->Binary(ynn_binary_multiply, 4547, 4548, 4549);
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
  g->Binary(ynn_binary_divide, 4557, 7139, 4558);
  g->Unary(ynn_unary_round, 4558, 4559);
  g->Binary(ynn_binary_max, 4559, 7155, 4560);
  g->Binary(ynn_binary_min, 4560, 7270, 4561);
  g->Binary(ynn_binary_multiply, 4561, 7139, 4562);
  g->Convert(8026, 4563);
  g->Binary(ynn_binary_multiply, 4563, 8027, 4564);
  g->Matmul(4562, 4564, 4565, false, true);
  g->Binary(ynn_binary_divide, 4565, 7100, 4566);
  g->Unary(ynn_unary_round, 4566, 4569);
  g->Binary(ynn_binary_max, 4569, 7155, 4570);
  g->Binary(ynn_binary_min, 4570, 7270, 4571);
  g->Binary(ynn_binary_multiply, 4571, 7100, 4572);
  g->SplitDim(4572, 4573, 2, {8,256});
  g->Transpose(4573, 4574, {0,2,1,3});
  g->Unary(ynn_unary_square, 4574, 4575);
  g->Reduce(ynn_reduce_sum, 4575, 6806, {3}, true);
  g->ShapeProduct(4575, 6805, {3});
  g->Binary(ynn_binary_divide, 6806, 6805, 4576);
  g->Binary(ynn_binary_add, 4576, 7303, 4577);
  g->Binary(ynn_binary_pow, 4577, 7358, 4578);
  g->Binary(ynn_binary_multiply, 4574, 4578, 4580);
  g->Convert(8025, 4581);
  g->Binary(ynn_binary_multiply, 4580, 4581, 4582);
  g->Slice(4582, 4583, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(4582, 4584, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 4584, 4585);
  g->Concat({4585,4583}, 4586, 3);
  g->Binary(ynn_binary_multiply, 4582, 2025, 4587);
  g->Binary(ynn_binary_multiply, 4586, 3078, 4588);
  g->Binary(ynn_binary_add, 4587, 4588, 4589);
}

// Scope: "Layer28 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer28AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(4589, 1946, 4591, false, true);
  g->Mask(4591, 7512, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 7512, 6810, {-1}, true);
  g->Binary(ynn_binary_subtract, 7512, 6810, 6807);
  g->Unary(ynn_unary_exp, 6807, 6808);
  g->Reduce(ynn_reduce_sum, 6808, 6811, {-1}, true);
  g->Binary(ynn_binary_divide, 6113, 6811, 6809);
  g->Binary(ynn_binary_multiply, 6808, 6809, 4592);
  g->Matmul(4592, 1948, 4593, false, false);
}

// Scope: "Layer28 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer28AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(4593, 4594, {0,2,1,3});
  g->FuseDims(4594, 4595, 2, 2);
  g->Binary(ynn_binary_divide, 4595, 7463, 4596);
  g->Unary(ynn_unary_round, 4596, 4597);
  g->Binary(ynn_binary_max, 4597, 7155, 4598);
  g->Binary(ynn_binary_min, 4598, 7270, 4599);
  g->Binary(ynn_binary_multiply, 4599, 7463, 4601);
  g->Convert(8023, 4602);
  g->Binary(ynn_binary_multiply, 4602, 8024, 4603);
  g->Matmul(4601, 4603, 4604, false, true);
  g->Binary(ynn_binary_divide, 4604, 7191, 4605);
  g->Unary(ynn_unary_round, 4605, 4606);
  g->Binary(ynn_binary_max, 4606, 7155, 4607);
  g->Binary(ynn_binary_min, 4607, 7270, 4608);
  g->Binary(ynn_binary_multiply, 4608, 7191, 4609);
}

// Scope: "Layer28 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer28Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 4549, 4550);
  g->Reduce(ynn_reduce_sum, 4550, 6804, {2}, true);
  g->ShapeProduct(4550, 6803, {2});
  g->Binary(ynn_binary_divide, 6804, 6803, 4551);
  g->Binary(ynn_binary_add, 4551, 7303, 4552);
  g->Binary(ynn_binary_pow, 4552, 7358, 4553);
  g->Binary(ynn_binary_multiply, 4549, 4553, 4554);
  g->Convert(8007, 4555);
  g->Binary(ynn_binary_multiply, 4554, 4555, 4557);
  BuildLayer28AttentionQueryProjection(ctx);
  BuildLayer28AttentionSdpa(ctx);
  BuildLayer28AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 4609, 4610);
  g->Reduce(ynn_reduce_sum, 4610, 6813, {2}, true);
  g->ShapeProduct(4610, 6812, {2});
  g->Binary(ynn_binary_divide, 6813, 6812, 4612);
  g->Binary(ynn_binary_add, 4612, 7303, 4613);
  g->Binary(ynn_binary_pow, 4613, 7358, 4614);
  g->Binary(ynn_binary_multiply, 4609, 4614, 4615);
  g->Convert(8019, 4616);
  g->Binary(ynn_binary_multiply, 4615, 4616, 4617);
  g->Binary(ynn_binary_add, 4549, 4617, 4618);
}

// Scope: "Layer28 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer28Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 4618, 4619);
  g->Reduce(ynn_reduce_sum, 4619, 6815, {2}, true);
  g->ShapeProduct(4619, 6814, {2});
  g->Binary(ynn_binary_divide, 6815, 6814, 4620);
  g->Binary(ynn_binary_add, 4620, 7303, 4621);
  g->Binary(ynn_binary_pow, 4621, 7358, 4623);
  g->Binary(ynn_binary_multiply, 4618, 4623, 4624);
  g->Convert(8022, 4625);
  g->Binary(ynn_binary_multiply, 4624, 4625, 4626);
  g->Binary(ynn_binary_divide, 4626, 7090, 4627);
  g->Unary(ynn_unary_round, 4627, 4628);
  g->Binary(ynn_binary_max, 4628, 7155, 4629);
  g->Binary(ynn_binary_min, 4629, 7270, 4630);
  g->Binary(ynn_binary_multiply, 4630, 7090, 4631);
  g->Convert(8013, 4632);
  g->Binary(ynn_binary_multiply, 4632, 8014, 4634);
  g->Matmul(4631, 4634, 4635, false, true);
  g->Binary(ynn_binary_divide, 4635, 7423, 4636);
  g->Unary(ynn_unary_round, 4636, 4637);
  g->Binary(ynn_binary_max, 4637, 7155, 4638);
  g->Binary(ynn_binary_min, 4638, 7270, 4639);
  g->Binary(ynn_binary_multiply, 4639, 7423, 4640);
  g->Convert(8011, 4642);
  g->Binary(ynn_binary_multiply, 4642, 8012, 4643);
  g->Matmul(4631, 4643, 4644, false, true);
  g->Binary(ynn_binary_divide, 4644, 7423, 4645);
  g->Unary(ynn_unary_round, 4645, 4646);
  g->Binary(ynn_binary_max, 4646, 7155, 4647);
  g->Binary(ynn_binary_min, 4647, 7270, 4648);
  g->Binary(ynn_binary_multiply, 4648, 7423, 4649);
  g->Polynomial(4649, 6818, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6818, 6819);
  g->Binary(ynn_binary_add, 6819, 6113, 6816);
  g->Binary(ynn_binary_multiply, 4649, 6111, 6817);
  g->Binary(ynn_binary_multiply, 6817, 6816, 4651);
  g->Binary(ynn_binary_multiply, 4640, 4651, 4652);
  g->Binary(ynn_binary_divide, 4652, 7430, 4653);
  g->Unary(ynn_unary_round, 4653, 4654);
  g->Binary(ynn_binary_max, 4654, 7155, 4655);
  g->Binary(ynn_binary_min, 4655, 7270, 4656);
  g->Binary(ynn_binary_multiply, 4656, 7430, 4657);
  g->Convert(8009, 4658);
  g->Binary(ynn_binary_multiply, 4658, 8010, 4659);
  g->Matmul(4657, 4659, 4660, false, true);
  g->Binary(ynn_binary_divide, 4660, 7477, 4662);
  g->Unary(ynn_unary_round, 4662, 4663);
  g->Binary(ynn_binary_max, 4663, 7155, 4664);
  g->Binary(ynn_binary_min, 4664, 7270, 4665);
  g->Binary(ynn_binary_multiply, 4665, 7477, 4666);
  g->Unary(ynn_unary_square, 4666, 4667);
  g->Reduce(ynn_reduce_sum, 4667, 6821, {2}, true);
  g->ShapeProduct(4667, 6820, {2});
  g->Binary(ynn_binary_divide, 6821, 6820, 4668);
  g->Binary(ynn_binary_add, 4668, 7303, 4669);
  g->Binary(ynn_binary_pow, 4669, 7358, 4670);
  g->Binary(ynn_binary_multiply, 4666, 4670, 4671);
  g->Convert(8020, 4674);
  g->Binary(ynn_binary_multiply, 4671, 4674, 4675);
  g->Binary(ynn_binary_add, 4618, 4675, 4676);
}

// Scope: "Layer28 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer28PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1022, 4677, {0,0,28,0}, {-1,-1,1,-1});
  g->Reshape(4677, 4678, {1,1,256});
  g->Binary(ynn_binary_add, 4678, 8360, 4679);
  g->Binary(ynn_binary_multiply, 4679, 7085, 4680);
  g->Binary(ynn_binary_divide, 4676, 7472, 4681);
  g->Unary(ynn_unary_round, 4681, 4682);
  g->Binary(ynn_binary_max, 4682, 7155, 4683);
  g->Binary(ynn_binary_min, 4683, 7270, 4684);
  g->Binary(ynn_binary_multiply, 4684, 7472, 4685);
  g->Convert(8015, 4686);
  g->Binary(ynn_binary_multiply, 4686, 8016, 4687);
  g->Matmul(4685, 4687, 4688, false, true);
  g->Binary(ynn_binary_divide, 4688, 7099, 4689);
  g->Unary(ynn_unary_round, 4689, 4690);
  g->Binary(ynn_binary_max, 4690, 7155, 4691);
  g->Binary(ynn_binary_min, 4691, 7270, 4692);
  g->Binary(ynn_binary_multiply, 4692, 7099, 4693);
  g->Polynomial(4693, 6829, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6829, 6830);
  g->Binary(ynn_binary_add, 6830, 6113, 6827);
  g->Binary(ynn_binary_multiply, 4693, 6111, 6828);
  g->Binary(ynn_binary_multiply, 6828, 6827, 4695);
  g->Binary(ynn_binary_multiply, 4695, 4680, 4696);
  g->Binary(ynn_binary_divide, 4696, 7080, 4697);
  g->Unary(ynn_unary_round, 4697, 4698);
  g->Binary(ynn_binary_max, 4698, 7155, 4699);
  g->Binary(ynn_binary_min, 4699, 7270, 4700);
  g->Binary(ynn_binary_multiply, 4700, 7080, 4701);
  g->Convert(8017, 4702);
  g->Binary(ynn_binary_multiply, 4702, 8018, 4703);
  g->Matmul(4701, 4703, 4704, false, true);
  g->Binary(ynn_binary_divide, 4704, 7342, 4706);
  g->Unary(ynn_unary_round, 4706, 4707);
  g->Binary(ynn_binary_max, 4707, 7155, 4708);
  g->Binary(ynn_binary_min, 4708, 7270, 4709);
  g->Binary(ynn_binary_multiply, 4709, 7342, 4710);
  g->Unary(ynn_unary_square, 4710, 4711);
  g->Reduce(ynn_reduce_sum, 4711, 6832, {2}, true);
  g->ShapeProduct(4711, 6831, {2});
  g->Binary(ynn_binary_divide, 6832, 6831, 4712);
  g->Binary(ynn_binary_add, 4712, 7303, 4713);
  g->Binary(ynn_binary_pow, 4713, 7358, 4714);
  g->Binary(ynn_binary_multiply, 4710, 4714, 4715);
  g->Convert(8021, 4717);
  g->Binary(ynn_binary_multiply, 4715, 4717, 4718);
  g->Binary(ynn_binary_add, 4676, 4718, 4719);
  g->Convert(8008, 4720);
  g->Binary(ynn_binary_multiply, 4719, 4720, 4721);
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
  g->Binary(ynn_binary_divide, 4729, 7467, 4730);
  g->Unary(ynn_unary_round, 4730, 4731);
  g->Binary(ynn_binary_max, 4731, 7155, 4732);
  g->Binary(ynn_binary_min, 4732, 7270, 4733);
  g->Binary(ynn_binary_multiply, 4733, 7467, 4734);
  g->Convert(8047, 4735);
  g->Binary(ynn_binary_multiply, 4735, 8048, 4736);
  g->Matmul(4734, 4736, 4737, false, true);
  g->Binary(ynn_binary_divide, 4737, 7092, 4739);
  g->Unary(ynn_unary_round, 4739, 4740);
  g->Binary(ynn_binary_max, 4740, 7155, 4741);
  g->Binary(ynn_binary_min, 4741, 7270, 4742);
  g->Binary(ynn_binary_multiply, 4742, 7092, 4743);
  g->SplitDim(4743, 4744, 2, {8,512});
  g->Transpose(4744, 4745, {0,2,1,3});
  g->Unary(ynn_unary_square, 4745, 4746);
  g->Reduce(ynn_reduce_sum, 4746, 6836, {3}, true);
  g->ShapeProduct(4746, 6835, {3});
  g->Binary(ynn_binary_divide, 6836, 6835, 4747);
  g->Binary(ynn_binary_add, 4747, 7303, 4748);
  g->Binary(ynn_binary_pow, 4748, 7358, 4750);
  g->Binary(ynn_binary_multiply, 4745, 4750, 4751);
  g->Convert(8046, 4752);
  g->Binary(ynn_binary_multiply, 4751, 4752, 4753);
  g->Slice(4753, 4754, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(4753, 4755, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 4755, 4756);
  g->Concat({4756,4754}, 4757, 3);
  g->Binary(ynn_binary_multiply, 4753, 5909, 4758);
  g->Binary(ynn_binary_multiply, 4757, 6008, 4759);
  g->Binary(ynn_binary_add, 4758, 4759, 4761);
}

// Scope: "Layer29 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer29AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(4761, 2160, 4762, false, true);
  g->Mask(4762, 7513, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 7513, 6840, {-1}, true);
  g->Binary(ynn_binary_subtract, 7513, 6840, 6837);
  g->Unary(ynn_unary_exp, 6837, 6838);
  g->Reduce(ynn_reduce_sum, 6838, 6841, {-1}, true);
  g->Binary(ynn_binary_divide, 6113, 6841, 6839);
  g->Binary(ynn_binary_multiply, 6838, 6839, 4763);
  g->Matmul(4763, 2162, 4764, false, false);
}

// Scope: "Layer29 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer29AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(4764, 4765, {0,2,1,3});
  g->FuseDims(4765, 4766, 2, 2);
  g->Binary(ynn_binary_divide, 4766, 7245, 4767);
  g->Unary(ynn_unary_round, 4767, 4768);
  g->Binary(ynn_binary_max, 4768, 7155, 4769);
  g->Binary(ynn_binary_min, 4769, 7270, 4771);
  g->Binary(ynn_binary_multiply, 4771, 7245, 4772);
  g->Convert(8044, 4773);
  g->Binary(ynn_binary_multiply, 4773, 8045, 4774);
  g->Matmul(4772, 4774, 4775, false, true);
  g->Binary(ynn_binary_divide, 4775, 7214, 4776);
  g->Unary(ynn_unary_round, 4776, 4777);
  g->Binary(ynn_binary_max, 4777, 7155, 4778);
  g->Binary(ynn_binary_min, 4778, 7270, 4779);
  g->Binary(ynn_binary_multiply, 4779, 7214, 4780);
}

// Scope: "Layer29 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer29Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 4721, 4722);
  g->Reduce(ynn_reduce_sum, 4722, 6834, {2}, true);
  g->ShapeProduct(4722, 6833, {2});
  g->Binary(ynn_binary_divide, 6834, 6833, 4723);
  g->Binary(ynn_binary_add, 4723, 7303, 4724);
  g->Binary(ynn_binary_pow, 4724, 7358, 4725);
  g->Binary(ynn_binary_multiply, 4721, 4725, 4726);
  g->Convert(8028, 4728);
  g->Binary(ynn_binary_multiply, 4726, 4728, 4729);
  BuildLayer29AttentionQueryProjection(ctx);
  BuildLayer29AttentionSdpa(ctx);
  BuildLayer29AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 4780, 4783);
  g->Reduce(ynn_reduce_sum, 4783, 6843, {2}, true);
  g->ShapeProduct(4783, 6842, {2});
  g->Binary(ynn_binary_divide, 6843, 6842, 4784);
  g->Binary(ynn_binary_add, 4784, 7303, 4785);
  g->Binary(ynn_binary_pow, 4785, 7358, 4786);
  g->Binary(ynn_binary_multiply, 4780, 4786, 4787);
  g->Convert(8040, 4788);
  g->Binary(ynn_binary_multiply, 4787, 4788, 4789);
  g->Binary(ynn_binary_add, 4721, 4789, 4790);
}

// Scope: "Layer29 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer29Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 4790, 4791);
  g->Reduce(ynn_reduce_sum, 4791, 6845, {2}, true);
  g->ShapeProduct(4791, 6844, {2});
  g->Binary(ynn_binary_divide, 6845, 6844, 4792);
  g->Binary(ynn_binary_add, 4792, 7303, 4794);
  g->Binary(ynn_binary_pow, 4794, 7358, 4795);
  g->Binary(ynn_binary_multiply, 4790, 4795, 4796);
  g->Convert(8043, 4797);
  g->Binary(ynn_binary_multiply, 4796, 4797, 4798);
  g->Binary(ynn_binary_divide, 4798, 7236, 4799);
  g->Unary(ynn_unary_round, 4799, 4800);
  g->Binary(ynn_binary_max, 4800, 7155, 4801);
  g->Binary(ynn_binary_min, 4801, 7270, 4802);
  g->Binary(ynn_binary_multiply, 4802, 7236, 4803);
  g->Convert(8034, 4805);
  g->Binary(ynn_binary_multiply, 4805, 8035, 4806);
  g->Matmul(4803, 4806, 4807, false, true);
  g->Binary(ynn_binary_divide, 4807, 7076, 4808);
  g->Unary(ynn_unary_round, 4808, 4809);
  g->Binary(ynn_binary_max, 4809, 7155, 4810);
  g->Binary(ynn_binary_min, 4810, 7270, 4811);
  g->Binary(ynn_binary_multiply, 4811, 7076, 4812);
  g->Convert(8032, 4814);
  g->Binary(ynn_binary_multiply, 4814, 8033, 4815);
  g->Matmul(4803, 4815, 4816, false, true);
  g->Binary(ynn_binary_divide, 4816, 7076, 4817);
  g->Unary(ynn_unary_round, 4817, 4818);
  g->Binary(ynn_binary_max, 4818, 7155, 4819);
  g->Binary(ynn_binary_min, 4819, 7270, 4820);
  g->Binary(ynn_binary_multiply, 4820, 7076, 4822);
  g->Polynomial(4822, 6848, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6848, 6849);
  g->Binary(ynn_binary_add, 6849, 6113, 6846);
  g->Binary(ynn_binary_multiply, 4822, 6111, 6847);
  g->Binary(ynn_binary_multiply, 6847, 6846, 4823);
  g->Binary(ynn_binary_multiply, 4812, 4823, 4824);
  g->Binary(ynn_binary_divide, 4824, 7156, 4825);
  g->Unary(ynn_unary_round, 4825, 4826);
  g->Binary(ynn_binary_max, 4826, 7155, 4827);
  g->Binary(ynn_binary_min, 4827, 7270, 4828);
  g->Binary(ynn_binary_multiply, 4828, 7156, 4829);
  g->Convert(8030, 4830);
  g->Binary(ynn_binary_multiply, 4830, 8031, 4831);
  g->Matmul(4829, 4831, 4833, false, true);
  g->Binary(ynn_binary_divide, 4833, 7403, 4834);
  g->Unary(ynn_unary_round, 4834, 4835);
  g->Binary(ynn_binary_max, 4835, 7155, 4836);
  g->Binary(ynn_binary_min, 4836, 7270, 4837);
  g->Binary(ynn_binary_multiply, 4837, 7403, 4838);
  g->Unary(ynn_unary_square, 4838, 4839);
  g->Reduce(ynn_reduce_sum, 4839, 6851, {2}, true);
  g->ShapeProduct(4839, 6850, {2});
  g->Binary(ynn_binary_divide, 6851, 6850, 4840);
  g->Binary(ynn_binary_add, 4840, 7303, 4841);
  g->Binary(ynn_binary_pow, 4841, 7358, 4842);
  g->Binary(ynn_binary_multiply, 4838, 4842, 4844);
  g->Convert(8041, 4845);
  g->Binary(ynn_binary_multiply, 4844, 4845, 4846);
  g->Binary(ynn_binary_add, 4790, 4846, 4847);
}

// Scope: "Layer29 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer29PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1022, 4848, {0,0,29,0}, {-1,-1,1,-1});
  g->Reshape(4848, 4849, {1,1,256});
  g->Binary(ynn_binary_add, 4849, 8361, 4850);
  g->Binary(ynn_binary_multiply, 4850, 7085, 4851);
  g->Binary(ynn_binary_divide, 4847, 7408, 4852);
  g->Unary(ynn_unary_round, 4852, 4853);
  g->Binary(ynn_binary_max, 4853, 7155, 4855);
  g->Binary(ynn_binary_min, 4855, 7270, 4856);
  g->Binary(ynn_binary_multiply, 4856, 7408, 4857);
  g->Convert(8036, 4858);
  g->Binary(ynn_binary_multiply, 4858, 8037, 4859);
  g->Matmul(4857, 4859, 4860, false, true);
  g->Binary(ynn_binary_divide, 4860, 7193, 4861);
  g->Unary(ynn_unary_round, 4861, 4862);
  g->Binary(ynn_binary_max, 4862, 7155, 4863);
  g->Binary(ynn_binary_min, 4863, 7270, 4864);
  g->Binary(ynn_binary_multiply, 4864, 7193, 4866);
  g->Polynomial(4866, 6854, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6854, 6855);
  g->Binary(ynn_binary_add, 6855, 6113, 6852);
  g->Binary(ynn_binary_multiply, 4866, 6111, 6853);
  g->Binary(ynn_binary_multiply, 6853, 6852, 4867);
  g->Binary(ynn_binary_multiply, 4867, 4851, 4868);
  g->Binary(ynn_binary_divide, 4868, 7130, 4869);
  g->Unary(ynn_unary_round, 4869, 4870);
  g->Binary(ynn_binary_max, 4870, 7155, 4871);
  g->Binary(ynn_binary_min, 4871, 7270, 4872);
  g->Binary(ynn_binary_multiply, 4872, 7130, 4873);
  g->Convert(8038, 4874);
  g->Binary(ynn_binary_multiply, 4874, 8039, 4875);
  g->Matmul(4873, 4875, 4877, false, true);
  g->Binary(ynn_binary_divide, 4877, 7382, 4878);
  g->Unary(ynn_unary_round, 4878, 4879);
  g->Binary(ynn_binary_max, 4879, 7155, 4880);
  g->Binary(ynn_binary_min, 4880, 7270, 4881);
  g->Binary(ynn_binary_multiply, 4881, 7382, 4882);
  g->Unary(ynn_unary_square, 4882, 4883);
  g->Reduce(ynn_reduce_sum, 4883, 6857, {2}, true);
  g->ShapeProduct(4883, 6856, {2});
  g->Binary(ynn_binary_divide, 6857, 6856, 4884);
  g->Binary(ynn_binary_add, 4884, 7303, 4885);
  g->Binary(ynn_binary_pow, 4885, 7358, 4886);
  g->Binary(ynn_binary_multiply, 4882, 4886, 4888);
  g->Convert(8042, 4889);
  g->Binary(ynn_binary_multiply, 4888, 4889, 4890);
  g->Binary(ynn_binary_add, 4847, 4890, 4891);
  g->Convert(8029, 4892);
  g->Binary(ynn_binary_multiply, 4891, 4892, 4893);
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
  g->Binary(ynn_binary_divide, 4901, 7221, 4902);
  g->Unary(ynn_unary_round, 4902, 4903);
  g->Binary(ynn_binary_max, 4903, 7155, 4904);
  g->Binary(ynn_binary_min, 4904, 7270, 4905);
  g->Binary(ynn_binary_multiply, 4905, 7221, 4906);
  g->Convert(8094, 4907);
  g->Binary(ynn_binary_multiply, 4907, 8095, 4908);
  g->Matmul(4906, 4908, 4910, false, true);
  g->Binary(ynn_binary_divide, 4910, 7102, 4911);
  g->Unary(ynn_unary_round, 4911, 4912);
  g->Binary(ynn_binary_max, 4912, 7155, 4913);
  g->Binary(ynn_binary_min, 4913, 7270, 4914);
  g->Binary(ynn_binary_multiply, 4914, 7102, 4915);
  g->SplitDim(4915, 4916, 2, {8,256});
  g->Transpose(4916, 4917, {0,2,1,3});
  g->Unary(ynn_unary_square, 4917, 4918);
  g->Reduce(ynn_reduce_sum, 4918, 6863, {3}, true);
  g->ShapeProduct(4918, 6862, {3});
  g->Binary(ynn_binary_divide, 6863, 6862, 4919);
  g->Binary(ynn_binary_add, 4919, 7303, 4921);
  g->Binary(ynn_binary_pow, 4921, 7358, 4922);
  g->Binary(ynn_binary_multiply, 4917, 4922, 4923);
  g->Convert(8093, 4924);
  g->Binary(ynn_binary_multiply, 4923, 4924, 4925);
  g->Slice(4925, 4926, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(4925, 4927, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 4927, 4928);
  g->Concat({4928,4926}, 4929, 3);
  g->Binary(ynn_binary_multiply, 4925, 2025, 4930);
  g->Binary(ynn_binary_multiply, 4929, 3078, 4932);
  g->Binary(ynn_binary_add, 4930, 4932, 4933);
}

// Scope: "Layer30 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer30AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(4933, 1946, 4934, false, true);
  g->Mask(4934, 7515, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 7515, 6867, {-1}, true);
  g->Binary(ynn_binary_subtract, 7515, 6867, 6864);
  g->Unary(ynn_unary_exp, 6864, 6865);
  g->Reduce(ynn_reduce_sum, 6865, 6868, {-1}, true);
  g->Binary(ynn_binary_divide, 6113, 6868, 6866);
  g->Binary(ynn_binary_multiply, 6865, 6866, 4935);
  g->Matmul(4935, 1948, 4936, false, false);
}

// Scope: "Layer30 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer30AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(4936, 4937, {0,2,1,3});
  g->FuseDims(4937, 4938, 2, 2);
  g->Binary(ynn_binary_divide, 4938, 7252, 4939);
  g->Unary(ynn_unary_round, 4939, 4940);
  g->Binary(ynn_binary_max, 4940, 7155, 4942);
  g->Binary(ynn_binary_min, 4942, 7270, 4943);
  g->Binary(ynn_binary_multiply, 4943, 7252, 4944);
  g->Convert(8091, 4945);
  g->Binary(ynn_binary_multiply, 4945, 8092, 4946);
  g->Matmul(4944, 4946, 4947, false, true);
  g->Binary(ynn_binary_divide, 4947, 7455, 4948);
  g->Unary(ynn_unary_round, 4948, 4949);
  g->Binary(ynn_binary_max, 4949, 7155, 4950);
  g->Binary(ynn_binary_min, 4950, 7270, 4951);
  g->Binary(ynn_binary_multiply, 4951, 7455, 4953);
}

// Scope: "Layer30 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer30Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 4893, 4894);
  g->Reduce(ynn_reduce_sum, 4894, 6861, {2}, true);
  g->ShapeProduct(4894, 6860, {2});
  g->Binary(ynn_binary_divide, 6861, 6860, 4895);
  g->Binary(ynn_binary_add, 4895, 7303, 4896);
  g->Binary(ynn_binary_pow, 4896, 7358, 4897);
  g->Binary(ynn_binary_multiply, 4893, 4897, 4899);
  g->Convert(8075, 4900);
  g->Binary(ynn_binary_multiply, 4899, 4900, 4901);
  BuildLayer30AttentionQueryProjection(ctx);
  BuildLayer30AttentionSdpa(ctx);
  BuildLayer30AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 4953, 4954);
  g->Reduce(ynn_reduce_sum, 4954, 6870, {2}, true);
  g->ShapeProduct(4954, 6869, {2});
  g->Binary(ynn_binary_divide, 6870, 6869, 4955);
  g->Binary(ynn_binary_add, 4955, 7303, 4956);
  g->Binary(ynn_binary_pow, 4956, 7358, 4957);
  g->Binary(ynn_binary_multiply, 4953, 4957, 4958);
  g->Convert(8087, 4959);
  g->Binary(ynn_binary_multiply, 4958, 4959, 4960);
  g->Binary(ynn_binary_add, 4893, 4960, 4961);
}

// Scope: "Layer30 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer30Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 4961, 4962);
  g->Reduce(ynn_reduce_sum, 4962, 6872, {2}, true);
  g->ShapeProduct(4962, 6871, {2});
  g->Binary(ynn_binary_divide, 6872, 6871, 4964);
  g->Binary(ynn_binary_add, 4964, 7303, 4965);
  g->Binary(ynn_binary_pow, 4965, 7358, 4966);
  g->Binary(ynn_binary_multiply, 4961, 4966, 4967);
  g->Convert(8090, 4968);
  g->Binary(ynn_binary_multiply, 4967, 4968, 4969);
  g->Binary(ynn_binary_divide, 4969, 7272, 4970);
  g->Unary(ynn_unary_round, 4970, 4971);
  g->Binary(ynn_binary_max, 4971, 7155, 4972);
  g->Binary(ynn_binary_min, 4972, 7270, 4973);
  g->Binary(ynn_binary_multiply, 4973, 7272, 4975);
  g->Convert(8081, 4976);
  g->Binary(ynn_binary_multiply, 4976, 8082, 4977);
  g->Matmul(4975, 4977, 4978, false, true);
  g->Binary(ynn_binary_divide, 4978, 7433, 4979);
  g->Unary(ynn_unary_round, 4979, 4980);
  g->Binary(ynn_binary_max, 4980, 7155, 4981);
  g->Binary(ynn_binary_min, 4981, 7270, 4982);
  g->Binary(ynn_binary_multiply, 4982, 7433, 4983);
  g->Convert(8079, 4985);
  g->Binary(ynn_binary_multiply, 4985, 8080, 4986);
  g->Matmul(4975, 4986, 4987, false, true);
  g->Binary(ynn_binary_divide, 4987, 7433, 4988);
  g->Unary(ynn_unary_round, 4988, 4989);
  g->Binary(ynn_binary_max, 4989, 7155, 4990);
  g->Binary(ynn_binary_min, 4990, 7270, 4992);
  g->Binary(ynn_binary_multiply, 4992, 7433, 4993);
  g->Polynomial(4993, 6877, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6877, 6878);
  g->Binary(ynn_binary_add, 6878, 6113, 6875);
  g->Binary(ynn_binary_multiply, 4993, 6111, 6876);
  g->Binary(ynn_binary_multiply, 6876, 6875, 4994);
  g->Binary(ynn_binary_multiply, 4983, 4994, 4995);
  g->Binary(ynn_binary_divide, 4995, 7193, 4996);
  g->Unary(ynn_unary_round, 4996, 4997);
  g->Binary(ynn_binary_max, 4997, 7155, 4998);
  g->Binary(ynn_binary_min, 4998, 7270, 4999);
  g->Binary(ynn_binary_multiply, 4999, 7193, 5000);
  g->Convert(8077, 5001);
  g->Binary(ynn_binary_multiply, 5001, 8078, 5003);
  g->Matmul(5000, 5003, 5004, false, true);
  g->Binary(ynn_binary_divide, 5004, 7312, 5005);
  g->Unary(ynn_unary_round, 5005, 5006);
  g->Binary(ynn_binary_max, 5006, 7155, 5007);
  g->Binary(ynn_binary_min, 5007, 7270, 5008);
  g->Binary(ynn_binary_multiply, 5008, 7312, 5009);
  g->Unary(ynn_unary_square, 5009, 5010);
  g->Reduce(ynn_reduce_sum, 5010, 6880, {2}, true);
  g->ShapeProduct(5010, 6879, {2});
  g->Binary(ynn_binary_divide, 6880, 6879, 5011);
  g->Binary(ynn_binary_add, 5011, 7303, 5012);
  g->Binary(ynn_binary_pow, 5012, 7358, 5014);
  g->Binary(ynn_binary_multiply, 5009, 5014, 5015);
  g->Convert(8088, 5016);
  g->Binary(ynn_binary_multiply, 5015, 5016, 5017);
  g->Binary(ynn_binary_add, 4961, 5017, 5018);
}

// Scope: "Layer30 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer30PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1022, 5019, {0,0,30,0}, {-1,-1,1,-1});
  g->Reshape(5019, 5020, {1,1,256});
  g->Binary(ynn_binary_add, 5020, 8363, 5021);
  g->Binary(ynn_binary_multiply, 5021, 7085, 5022);
  g->Binary(ynn_binary_divide, 5018, 7113, 5023);
  g->Unary(ynn_unary_round, 5023, 5025);
  g->Binary(ynn_binary_max, 5025, 7155, 5026);
  g->Binary(ynn_binary_min, 5026, 7270, 5027);
  g->Binary(ynn_binary_multiply, 5027, 7113, 5028);
  g->Convert(8083, 5029);
  g->Binary(ynn_binary_multiply, 5029, 8084, 5030);
  g->Matmul(5028, 5030, 5031, false, true);
  g->Binary(ynn_binary_divide, 5031, 7462, 5032);
  g->Unary(ynn_unary_round, 5032, 5033);
  g->Binary(ynn_binary_max, 5033, 7155, 5034);
  g->Binary(ynn_binary_min, 5034, 7270, 5036);
  g->Binary(ynn_binary_multiply, 5036, 7462, 5037);
  g->Polynomial(5037, 6883, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6883, 6884);
  g->Binary(ynn_binary_add, 6884, 6113, 6881);
  g->Binary(ynn_binary_multiply, 5037, 6111, 6882);
  g->Binary(ynn_binary_multiply, 6882, 6881, 5038);
  g->Binary(ynn_binary_multiply, 5038, 5022, 5039);
  g->Binary(ynn_binary_divide, 5039, 7367, 5040);
  g->Unary(ynn_unary_round, 5040, 5041);
  g->Binary(ynn_binary_max, 5041, 7155, 5042);
  g->Binary(ynn_binary_min, 5042, 7270, 5043);
  g->Binary(ynn_binary_multiply, 5043, 7367, 5044);
  g->Convert(8085, 5045);
  g->Binary(ynn_binary_multiply, 5045, 8086, 5047);
  g->Matmul(5044, 5047, 5048, false, true);
  g->Binary(ynn_binary_divide, 5048, 7115, 5049);
  g->Unary(ynn_unary_round, 5049, 5050);
  g->Binary(ynn_binary_max, 5050, 7155, 5051);
  g->Binary(ynn_binary_min, 5051, 7270, 5052);
  g->Binary(ynn_binary_multiply, 5052, 7115, 5053);
  g->Unary(ynn_unary_square, 5053, 5054);
  g->Reduce(ynn_reduce_sum, 5054, 6886, {2}, true);
  g->ShapeProduct(5054, 6885, {2});
  g->Binary(ynn_binary_divide, 6886, 6885, 5055);
  g->Binary(ynn_binary_add, 5055, 7303, 5056);
  g->Binary(ynn_binary_pow, 5056, 7358, 5058);
  g->Binary(ynn_binary_multiply, 5053, 5058, 5059);
  g->Convert(8089, 5060);
  g->Binary(ynn_binary_multiply, 5059, 5060, 5061);
  g->Binary(ynn_binary_add, 5018, 5061, 5062);
  g->Convert(8076, 5063);
  g->Binary(ynn_binary_multiply, 5062, 5063, 5064);
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
  g->Binary(ynn_binary_divide, 5072, 7348, 5073);
  g->Unary(ynn_unary_round, 5073, 5074);
  g->Binary(ynn_binary_max, 5074, 7155, 5075);
  g->Binary(ynn_binary_min, 5075, 7270, 5076);
  g->Binary(ynn_binary_multiply, 5076, 7348, 5077);
  g->Convert(8115, 5078);
  g->Binary(ynn_binary_multiply, 5078, 8116, 5080);
  g->Matmul(5077, 5080, 5081, false, true);
  g->Binary(ynn_binary_divide, 5081, 7218, 5082);
  g->Unary(ynn_unary_round, 5082, 5083);
  g->Binary(ynn_binary_max, 5083, 7155, 5084);
  g->Binary(ynn_binary_min, 5084, 7270, 5085);
  g->Binary(ynn_binary_multiply, 5085, 7218, 5086);
  g->SplitDim(5086, 5087, 2, {8,256});
  g->Transpose(5087, 5088, {0,2,1,3});
  g->Unary(ynn_unary_square, 5088, 5089);
  g->Reduce(ynn_reduce_sum, 5089, 6890, {3}, true);
  g->ShapeProduct(5089, 6889, {3});
  g->Binary(ynn_binary_divide, 6890, 6889, 5091);
  g->Binary(ynn_binary_add, 5091, 7303, 5092);
  g->Binary(ynn_binary_pow, 5092, 7358, 5093);
  g->Binary(ynn_binary_multiply, 5088, 5093, 5094);
  g->Convert(8114, 5095);
  g->Binary(ynn_binary_multiply, 5094, 5095, 5096);
  g->Slice(5096, 5097, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(5096, 5098, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 5098, 5099);
  g->Concat({5099,5097}, 5100, 3);
  g->Binary(ynn_binary_multiply, 5096, 2025, 5102);
  g->Binary(ynn_binary_multiply, 5100, 3078, 5103);
  g->Binary(ynn_binary_add, 5102, 5103, 5104);
}

// Scope: "Layer31 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer31AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(5104, 1946, 5105, false, true);
  g->Mask(5105, 7516, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 7516, 6894, {-1}, true);
  g->Binary(ynn_binary_subtract, 7516, 6894, 6891);
  g->Unary(ynn_unary_exp, 6891, 6892);
  g->Reduce(ynn_reduce_sum, 6892, 6895, {-1}, true);
  g->Binary(ynn_binary_divide, 6113, 6895, 6893);
  g->Binary(ynn_binary_multiply, 6892, 6893, 5106);
  g->Matmul(5106, 1948, 5107, false, false);
}

// Scope: "Layer31 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer31AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(5107, 5108, {0,2,1,3});
  g->FuseDims(5108, 5109, 2, 2);
  g->Binary(ynn_binary_divide, 5109, 7252, 5110);
  g->Unary(ynn_unary_round, 5110, 5112);
  g->Binary(ynn_binary_max, 5112, 7155, 5113);
  g->Binary(ynn_binary_min, 5113, 7270, 5114);
  g->Binary(ynn_binary_multiply, 5114, 7252, 5115);
  g->Convert(8112, 5116);
  g->Binary(ynn_binary_multiply, 5116, 8113, 5117);
  g->Matmul(5115, 5117, 5118, false, true);
  g->Binary(ynn_binary_divide, 5118, 7314, 5119);
  g->Unary(ynn_unary_round, 5119, 5120);
  g->Binary(ynn_binary_max, 5120, 7155, 5121);
  g->Binary(ynn_binary_min, 5121, 7270, 5123);
  g->Binary(ynn_binary_multiply, 5123, 7314, 5124);
}

// Scope: "Layer31 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer31Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 5064, 5065);
  g->Reduce(ynn_reduce_sum, 5065, 6888, {2}, true);
  g->ShapeProduct(5065, 6887, {2});
  g->Binary(ynn_binary_divide, 6888, 6887, 5066);
  g->Binary(ynn_binary_add, 5066, 7303, 5067);
  g->Binary(ynn_binary_pow, 5067, 7358, 5069);
  g->Binary(ynn_binary_multiply, 5064, 5069, 5070);
  g->Convert(8096, 5071);
  g->Binary(ynn_binary_multiply, 5070, 5071, 5072);
  BuildLayer31AttentionQueryProjection(ctx);
  BuildLayer31AttentionSdpa(ctx);
  BuildLayer31AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 5124, 5125);
  g->Reduce(ynn_reduce_sum, 5125, 6897, {2}, true);
  g->ShapeProduct(5125, 6896, {2});
  g->Binary(ynn_binary_divide, 6897, 6896, 5126);
  g->Binary(ynn_binary_add, 5126, 7303, 5127);
  g->Binary(ynn_binary_pow, 5127, 7358, 5128);
  g->Binary(ynn_binary_multiply, 5124, 5128, 5129);
  g->Convert(8108, 5130);
  g->Binary(ynn_binary_multiply, 5129, 5130, 5131);
  g->Binary(ynn_binary_add, 5064, 5131, 5132);
}

// Scope: "Layer31 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer31Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 5132, 5134);
  g->Reduce(ynn_reduce_sum, 5134, 6899, {2}, true);
  g->ShapeProduct(5134, 6898, {2});
  g->Binary(ynn_binary_divide, 6899, 6898, 5135);
  g->Binary(ynn_binary_add, 5135, 7303, 5136);
  g->Binary(ynn_binary_pow, 5136, 7358, 5137);
  g->Binary(ynn_binary_multiply, 5132, 5137, 5138);
  g->Convert(8111, 5139);
  g->Binary(ynn_binary_multiply, 5138, 5139, 5140);
  g->Binary(ynn_binary_divide, 5140, 7217, 5141);
  g->Unary(ynn_unary_round, 5141, 5142);
  g->Binary(ynn_binary_max, 5142, 7155, 5143);
  g->Binary(ynn_binary_min, 5143, 7270, 5145);
  g->Binary(ynn_binary_multiply, 5145, 7217, 5146);
  g->Convert(8102, 5147);
  g->Binary(ynn_binary_multiply, 5147, 8103, 5148);
  g->Matmul(5146, 5148, 5149, false, true);
  g->Binary(ynn_binary_divide, 5149, 7487, 5150);
  g->Unary(ynn_unary_round, 5150, 5151);
  g->Binary(ynn_binary_max, 5151, 7155, 5152);
  g->Binary(ynn_binary_min, 5152, 7270, 5153);
  g->Binary(ynn_binary_multiply, 5153, 7487, 5154);
  g->Convert(8100, 5156);
  g->Binary(ynn_binary_multiply, 5156, 8101, 5157);
  g->Matmul(5146, 5157, 5158, false, true);
  g->Binary(ynn_binary_divide, 5158, 7487, 5159);
  g->Unary(ynn_unary_round, 5159, 5160);
  g->Binary(ynn_binary_max, 5160, 7155, 5162);
  g->Binary(ynn_binary_min, 5162, 7270, 5163);
  g->Binary(ynn_binary_multiply, 5163, 7487, 5164);
  g->Polynomial(5164, 6902, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6902, 6903);
  g->Binary(ynn_binary_add, 6903, 6113, 6900);
  g->Binary(ynn_binary_multiply, 5164, 6111, 6901);
  g->Binary(ynn_binary_multiply, 6901, 6900, 5165);
  g->Binary(ynn_binary_multiply, 5154, 5165, 5166);
  g->Binary(ynn_binary_divide, 5166, 7300, 5167);
  g->Unary(ynn_unary_round, 5167, 5168);
  g->Binary(ynn_binary_max, 5168, 7155, 5169);
  g->Binary(ynn_binary_min, 5169, 7270, 5170);
  g->Binary(ynn_binary_multiply, 5170, 7300, 5171);
  g->Convert(8098, 5172);
  g->Binary(ynn_binary_multiply, 5172, 8099, 5173);
  g->Matmul(5171, 5173, 5174, false, true);
  g->Binary(ynn_binary_divide, 5174, 7213, 5175);
  g->Unary(ynn_unary_round, 5175, 5176);
  g->Binary(ynn_binary_max, 5176, 7155, 5177);
  g->Binary(ynn_binary_min, 5177, 7270, 5178);
  g->Binary(ynn_binary_multiply, 5178, 7213, 5179);
  g->Unary(ynn_unary_square, 5179, 5180);
  g->Reduce(ynn_reduce_sum, 5180, 6905, {2}, true);
  g->ShapeProduct(5180, 6904, {2});
  g->Binary(ynn_binary_divide, 6905, 6904, 5181);
  g->Binary(ynn_binary_add, 5181, 7303, 5182);
  g->Binary(ynn_binary_pow, 5182, 7358, 5183);
  g->Binary(ynn_binary_multiply, 5179, 5183, 5184);
  g->Convert(8109, 5185);
  g->Binary(ynn_binary_multiply, 5184, 5185, 5186);
  g->Binary(ynn_binary_add, 5132, 5186, 5187);
}

// Scope: "Layer31 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer31PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1022, 5188, {0,0,31,0}, {-1,-1,1,-1});
  g->Reshape(5188, 5189, {1,1,256});
  g->Binary(ynn_binary_add, 5189, 8364, 5190);
  g->Binary(ynn_binary_multiply, 5190, 7085, 5191);
  g->Binary(ynn_binary_divide, 5187, 7203, 5192);
  g->Unary(ynn_unary_round, 5192, 5193);
  g->Binary(ynn_binary_max, 5193, 7155, 5194);
  g->Binary(ynn_binary_min, 5194, 7270, 5195);
  g->Binary(ynn_binary_multiply, 5195, 7203, 5196);
  g->Convert(8104, 5197);
  g->Binary(ynn_binary_multiply, 5197, 8105, 5198);
  g->Matmul(5196, 5198, 5199, false, true);
  g->Binary(ynn_binary_divide, 5199, 7439, 5200);
  g->Unary(ynn_unary_round, 5200, 5201);
  g->Binary(ynn_binary_max, 5201, 7155, 5203);
  g->Binary(ynn_binary_min, 5203, 7270, 5204);
  g->Binary(ynn_binary_multiply, 5204, 7439, 5205);
  g->Polynomial(5205, 6908, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6908, 6909);
  g->Binary(ynn_binary_add, 6909, 6113, 6906);
  g->Binary(ynn_binary_multiply, 5205, 6111, 6907);
  g->Binary(ynn_binary_multiply, 6907, 6906, 5206);
  g->Binary(ynn_binary_multiply, 5206, 5191, 5207);
  g->Binary(ynn_binary_divide, 5207, 7321, 5208);
  g->Unary(ynn_unary_round, 5208, 5209);
  g->Binary(ynn_binary_max, 5209, 7155, 5210);
  g->Binary(ynn_binary_min, 5210, 7270, 5211);
  g->Binary(ynn_binary_multiply, 5211, 7321, 5212);
  g->Convert(8106, 5213);
  g->Binary(ynn_binary_multiply, 5213, 8107, 5214);
  g->Matmul(5212, 5214, 5215, false, true);
  g->Binary(ynn_binary_divide, 5215, 7198, 5216);
  g->Unary(ynn_unary_round, 5216, 5217);
  g->Binary(ynn_binary_max, 5217, 7155, 5218);
  g->Binary(ynn_binary_min, 5218, 7270, 5219);
  g->Binary(ynn_binary_multiply, 5219, 7198, 5220);
  g->Unary(ynn_unary_square, 5220, 5221);
  g->Reduce(ynn_reduce_sum, 5221, 6911, {2}, true);
  g->ShapeProduct(5221, 6910, {2});
  g->Binary(ynn_binary_divide, 6911, 6910, 5222);
  g->Binary(ynn_binary_add, 5222, 7303, 5224);
  g->Binary(ynn_binary_pow, 5224, 7358, 5225);
  g->Binary(ynn_binary_multiply, 5220, 5225, 5226);
  g->Convert(8110, 5227);
  g->Binary(ynn_binary_multiply, 5226, 5227, 5228);
  g->Binary(ynn_binary_add, 5187, 5228, 5229);
  g->Convert(8097, 5230);
  g->Binary(ynn_binary_multiply, 5229, 5230, 5231);
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
  g->Binary(ynn_binary_divide, 5239, 7371, 5240);
  g->Unary(ynn_unary_round, 5240, 5241);
  g->Binary(ynn_binary_max, 5241, 7155, 5242);
  g->Binary(ynn_binary_min, 5242, 7270, 5243);
  g->Binary(ynn_binary_multiply, 5243, 7371, 5244);
  g->Convert(8136, 5246);
  g->Binary(ynn_binary_multiply, 5246, 8137, 5247);
  g->Matmul(5244, 5247, 5248, false, true);
  g->Binary(ynn_binary_divide, 5248, 7109, 5249);
  g->Unary(ynn_unary_round, 5249, 5250);
  g->Binary(ynn_binary_max, 5250, 7155, 5251);
  g->Binary(ynn_binary_min, 5251, 7270, 5252);
  g->Binary(ynn_binary_multiply, 5252, 7109, 5253);
  g->SplitDim(5253, 5254, 2, {8,256});
  g->Transpose(5254, 5255, {0,2,1,3});
  g->Unary(ynn_unary_square, 5255, 5257);
  g->Reduce(ynn_reduce_sum, 5257, 6915, {3}, true);
  g->ShapeProduct(5257, 6914, {3});
  g->Binary(ynn_binary_divide, 6915, 6914, 5258);
  g->Binary(ynn_binary_add, 5258, 7303, 5259);
  g->Binary(ynn_binary_pow, 5259, 7358, 5260);
  g->Binary(ynn_binary_multiply, 5255, 5260, 5261);
  g->Convert(8135, 5262);
  g->Binary(ynn_binary_multiply, 5261, 5262, 5263);
  g->Slice(5263, 5264, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(5263, 5265, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 5265, 5266);
  g->Concat({5266,5264}, 5268, 3);
  g->Binary(ynn_binary_multiply, 5263, 2025, 5269);
  g->Binary(ynn_binary_multiply, 5268, 3078, 5270);
  g->Binary(ynn_binary_add, 5269, 5270, 5271);
}

// Scope: "Layer32 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer32AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(5271, 1946, 5272, false, true);
  g->Mask(5272, 7517, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 7517, 6919, {-1}, true);
  g->Binary(ynn_binary_subtract, 7517, 6919, 6916);
  g->Unary(ynn_unary_exp, 6916, 6917);
  g->Reduce(ynn_reduce_sum, 6917, 6920, {-1}, true);
  g->Binary(ynn_binary_divide, 6113, 6920, 6918);
  g->Binary(ynn_binary_multiply, 6917, 6918, 5273);
  g->Matmul(5273, 1948, 5274, false, false);
}

// Scope: "Layer32 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer32AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(5274, 5275, {0,2,1,3});
  g->FuseDims(5275, 5276, 2, 2);
  g->Binary(ynn_binary_divide, 5276, 7168, 5278);
  g->Unary(ynn_unary_round, 5278, 5279);
  g->Binary(ynn_binary_max, 5279, 7155, 5280);
  g->Binary(ynn_binary_min, 5280, 7270, 5281);
  g->Binary(ynn_binary_multiply, 5281, 7168, 5282);
  g->Convert(8133, 5283);
  g->Binary(ynn_binary_multiply, 5283, 8134, 5284);
  g->Matmul(5282, 5284, 5285, false, true);
  g->Binary(ynn_binary_divide, 5285, 7432, 5286);
  g->Unary(ynn_unary_round, 5286, 5287);
  g->Binary(ynn_binary_max, 5287, 7155, 5289);
  g->Binary(ynn_binary_min, 5289, 7270, 5290);
  g->Binary(ynn_binary_multiply, 5290, 7432, 5291);
}

// Scope: "Layer32 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer32Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 5231, 5232);
  g->Reduce(ynn_reduce_sum, 5232, 6913, {2}, true);
  g->ShapeProduct(5232, 6912, {2});
  g->Binary(ynn_binary_divide, 6913, 6912, 5233);
  g->Binary(ynn_binary_add, 5233, 7303, 5235);
  g->Binary(ynn_binary_pow, 5235, 7358, 5236);
  g->Binary(ynn_binary_multiply, 5231, 5236, 5237);
  g->Convert(8117, 5238);
  g->Binary(ynn_binary_multiply, 5237, 5238, 5239);
  BuildLayer32AttentionQueryProjection(ctx);
  BuildLayer32AttentionSdpa(ctx);
  BuildLayer32AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 5291, 5292);
  g->Reduce(ynn_reduce_sum, 5292, 6922, {2}, true);
  g->ShapeProduct(5292, 6921, {2});
  g->Binary(ynn_binary_divide, 6922, 6921, 5293);
  g->Binary(ynn_binary_add, 5293, 7303, 5294);
  g->Binary(ynn_binary_pow, 5294, 7358, 5295);
  g->Binary(ynn_binary_multiply, 5291, 5295, 5296);
  g->Convert(8129, 5297);
  g->Binary(ynn_binary_multiply, 5296, 5297, 5298);
  g->Binary(ynn_binary_add, 5231, 5298, 5300);
}

// Scope: "Layer32 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer32Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 5300, 5301);
  g->Reduce(ynn_reduce_sum, 5301, 6924, {2}, true);
  g->ShapeProduct(5301, 6923, {2});
  g->Binary(ynn_binary_divide, 6924, 6923, 5302);
  g->Binary(ynn_binary_add, 5302, 7303, 5303);
  g->Binary(ynn_binary_pow, 5303, 7358, 5304);
  g->Binary(ynn_binary_multiply, 5300, 5304, 5305);
  g->Convert(8132, 5306);
  g->Binary(ynn_binary_multiply, 5305, 5306, 5307);
  g->Binary(ynn_binary_divide, 5307, 7149, 5308);
  g->Unary(ynn_unary_round, 5308, 5309);
  g->Binary(ynn_binary_max, 5309, 7155, 5311);
  g->Binary(ynn_binary_min, 5311, 7270, 5312);
  g->Binary(ynn_binary_multiply, 5312, 7149, 5313);
  g->Convert(8123, 5314);
  g->Binary(ynn_binary_multiply, 5314, 8124, 5315);
  g->Matmul(5313, 5315, 5316, false, true);
  g->Binary(ynn_binary_divide, 5316, 7294, 5317);
  g->Unary(ynn_unary_round, 5317, 5318);
  g->Binary(ynn_binary_max, 5318, 7155, 5319);
  g->Binary(ynn_binary_min, 5319, 7270, 5320);
  g->Binary(ynn_binary_multiply, 5320, 7294, 5322);
  g->Convert(8121, 5323);
  g->Binary(ynn_binary_multiply, 5323, 8122, 5324);
  g->Matmul(5313, 5324, 5325, false, true);
  g->Binary(ynn_binary_divide, 5325, 7294, 5326);
  g->Unary(ynn_unary_round, 5326, 5328);
  g->Binary(ynn_binary_max, 5328, 7155, 5329);
  g->Binary(ynn_binary_min, 5329, 7270, 5330);
  g->Binary(ynn_binary_multiply, 5330, 7294, 5331);
  g->Polynomial(5331, 6931, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6931, 6932);
  g->Binary(ynn_binary_add, 6932, 6113, 6929);
  g->Binary(ynn_binary_multiply, 5331, 6111, 6930);
  g->Binary(ynn_binary_multiply, 6930, 6929, 5332);
  g->Binary(ynn_binary_multiply, 5322, 5332, 5333);
  g->Binary(ynn_binary_divide, 5333, 7164, 5334);
  g->Unary(ynn_unary_round, 5334, 5335);
  g->Binary(ynn_binary_max, 5335, 7155, 5336);
  g->Binary(ynn_binary_min, 5336, 7270, 5337);
  g->Binary(ynn_binary_multiply, 5337, 7164, 5339);
  g->Convert(8119, 5340);
  g->Binary(ynn_binary_multiply, 5340, 8120, 5341);
  g->Matmul(5339, 5341, 5342, false, true);
  g->Binary(ynn_binary_divide, 5342, 7201, 5343);
  g->Unary(ynn_unary_round, 5343, 5344);
  g->Binary(ynn_binary_max, 5344, 7155, 5345);
  g->Binary(ynn_binary_min, 5345, 7270, 5346);
  g->Binary(ynn_binary_multiply, 5346, 7201, 5347);
  g->Unary(ynn_unary_square, 5347, 5348);
  g->Reduce(ynn_reduce_sum, 5348, 6934, {2}, true);
  g->ShapeProduct(5348, 6933, {2});
  g->Binary(ynn_binary_divide, 6934, 6933, 5350);
  g->Binary(ynn_binary_add, 5350, 7303, 5351);
  g->Binary(ynn_binary_pow, 5351, 7358, 5352);
  g->Binary(ynn_binary_multiply, 5347, 5352, 5353);
  g->Convert(8130, 5354);
  g->Binary(ynn_binary_multiply, 5353, 5354, 5355);
  g->Binary(ynn_binary_add, 5300, 5355, 5356);
}

// Scope: "Layer32 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer32PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1022, 5357, {0,0,32,0}, {-1,-1,1,-1});
  g->Reshape(5357, 5358, {1,1,256});
  g->Binary(ynn_binary_add, 5358, 8365, 5359);
  g->Binary(ynn_binary_multiply, 5359, 7085, 5361);
  g->Binary(ynn_binary_divide, 5356, 7335, 5362);
  g->Unary(ynn_unary_round, 5362, 5363);
  g->Binary(ynn_binary_max, 5363, 7155, 5364);
  g->Binary(ynn_binary_min, 5364, 7270, 5365);
  g->Binary(ynn_binary_multiply, 5365, 7335, 5366);
  g->Convert(8125, 5367);
  g->Binary(ynn_binary_multiply, 5367, 8126, 5368);
  g->Matmul(5366, 5368, 5369, false, true);
  g->Binary(ynn_binary_divide, 5369, 7251, 5370);
  g->Unary(ynn_unary_round, 5370, 5372);
  g->Binary(ynn_binary_max, 5372, 7155, 5373);
  g->Binary(ynn_binary_min, 5373, 7270, 5374);
  g->Binary(ynn_binary_multiply, 5374, 7251, 5375);
  g->Polynomial(5375, 6937, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6937, 6938);
  g->Binary(ynn_binary_add, 6938, 6113, 6935);
  g->Binary(ynn_binary_multiply, 5375, 6111, 6936);
  g->Binary(ynn_binary_multiply, 6936, 6935, 5376);
  g->Binary(ynn_binary_multiply, 5376, 5361, 5377);
  g->Binary(ynn_binary_divide, 5377, 7367, 5378);
  g->Unary(ynn_unary_round, 5378, 5379);
  g->Binary(ynn_binary_max, 5379, 7155, 5380);
  g->Binary(ynn_binary_min, 5380, 7270, 5381);
  g->Binary(ynn_binary_multiply, 5381, 7367, 5383);
  g->Convert(8127, 5384);
  g->Binary(ynn_binary_multiply, 5384, 8128, 5385);
  g->Matmul(5383, 5385, 5386, false, true);
  g->Binary(ynn_binary_divide, 5386, 7084, 5387);
  g->Unary(ynn_unary_round, 5387, 5388);
  g->Binary(ynn_binary_max, 5388, 7155, 5389);
  g->Binary(ynn_binary_min, 5389, 7270, 5390);
  g->Binary(ynn_binary_multiply, 5390, 7084, 5391);
  g->Unary(ynn_unary_square, 5391, 5392);
  g->Reduce(ynn_reduce_sum, 5392, 6940, {2}, true);
  g->ShapeProduct(5392, 6939, {2});
  g->Binary(ynn_binary_divide, 6940, 6939, 5394);
  g->Binary(ynn_binary_add, 5394, 7303, 5395);
  g->Binary(ynn_binary_pow, 5395, 7358, 5396);
  g->Binary(ynn_binary_multiply, 5391, 5396, 5397);
  g->Convert(8131, 5398);
  g->Binary(ynn_binary_multiply, 5397, 5398, 5399);
  g->Binary(ynn_binary_add, 5356, 5399, 5400);
  g->Convert(8118, 5401);
  g->Binary(ynn_binary_multiply, 5400, 5401, 5402);
}

// Scope: "Layer32"
LAB_YNN_BUILDER_NOINLINE void BuildLayer32(Context& ctx) {
  BuildLayer32Attention(ctx);
  BuildLayer32Mlp(ctx);
  BuildLayer32PerLayerEmbedding(ctx);
}

}  // namespace BuildGemma4DecodeSource
