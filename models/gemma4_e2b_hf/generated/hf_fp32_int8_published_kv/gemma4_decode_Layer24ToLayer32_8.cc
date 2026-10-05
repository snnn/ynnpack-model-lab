// Generated YNNPACK builder; do not edit.
#include "gemma4_decode_builder.h"

namespace BuildGemma4DecodeSource {

// Scope: "Layer24 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer24AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Binary(ynn_binary_divide, 3920, 7353, 3921);
  g->Unary(ynn_unary_round, 3921, 3922);
  g->Binary(ynn_binary_max, 3922, 7225, 3923);
  g->Binary(ynn_binary_min, 3923, 7340, 3925);
  g->Binary(ynn_binary_multiply, 3925, 7353, 3926);
  g->Convert(8012, 3927);
  g->Binary(ynn_binary_multiply, 3927, 8013, 3928);
  g->Matmul(3926, 3928, 3929, false, true);
  g->Binary(ynn_binary_divide, 3929, 7376, 3930);
  g->Unary(ynn_unary_round, 3930, 3931);
  g->Binary(ynn_binary_max, 3931, 7225, 3932);
  g->Binary(ynn_binary_min, 3932, 7340, 3933);
  g->Binary(ynn_binary_multiply, 3933, 7376, 3934);
  g->SplitDim(3934, 3936, 2, {8,512});
  g->FuseDims(3936, 3938, 1, 2);
  g->SplitDim(3938, 3937, 1, {8,1});
  g->Unary(ynn_unary_square, 3937, 3939);
  g->Reduce(ynn_reduce_sum, 3939, 6770, {3}, true);
  g->ShapeProduct(3939, 6769, {3});
  g->Binary(ynn_binary_divide, 6770, 6769, 3940);
  g->Binary(ynn_binary_add, 3940, 7373, 3941);
  g->Binary(ynn_binary_pow, 3941, 7428, 3942);
  g->Binary(ynn_binary_multiply, 3937, 3942, 3943);
  g->Convert(8011, 3944);
  g->Binary(ynn_binary_multiply, 3943, 3944, 3945);
  g->Slice(3945, 3946, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(3945, 3948, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 3948, 3949);
  g->Concat({3949,3946}, 3950, 3);
  g->Binary(ynn_binary_multiply, 3945, 5976, 3951);
  g->Binary(ynn_binary_multiply, 3950, 6075, 3952);
  g->Binary(ynn_binary_add, 3951, 3952, 3953);
}

// Scope: "Layer24 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer24AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(3953, 2179, 3954, false, true);
  g->Mask(3954, 7578, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 7578, 6774, {-1}, true);
  g->Binary(ynn_binary_subtract, 7578, 6774, 6771);
  g->Unary(ynn_unary_exp, 6771, 6772);
  g->Reduce(ynn_reduce_sum, 6772, 6775, {-1}, true);
  g->Binary(ynn_binary_divide, 6183, 6775, 6773);
  g->Binary(ynn_binary_multiply, 6772, 6773, 3955);
  g->Matmul(3955, 2181, 3956, false, false);
}

// Scope: "Layer24 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer24AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(3956, 3959, 1, 2);
  g->SplitDim(3959, 3958, 1, {1,8});
  g->FuseDims(3958, 3960, 2, 2);
  g->Binary(ynn_binary_divide, 3960, 7417, 3961);
  g->Unary(ynn_unary_round, 3961, 3962);
  g->Binary(ynn_binary_max, 3962, 7225, 3963);
  g->Binary(ynn_binary_min, 3963, 7340, 3964);
  g->Binary(ynn_binary_multiply, 3964, 7417, 3965);
  g->Convert(8009, 3966);
  g->Binary(ynn_binary_multiply, 3966, 8010, 3967);
  g->Matmul(3965, 3967, 3968, false, true);
  g->Binary(ynn_binary_divide, 3968, 7356, 3970);
  g->Unary(ynn_unary_round, 3970, 3971);
  g->Binary(ynn_binary_max, 3971, 7225, 3972);
  g->Binary(ynn_binary_min, 3972, 7340, 3973);
  g->Binary(ynn_binary_multiply, 3973, 7356, 3974);
}

// Scope: "Layer24 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer24Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3912, 3914);
  g->Reduce(ynn_reduce_sum, 3914, 6768, {2}, true);
  g->ShapeProduct(3914, 6767, {2});
  g->Binary(ynn_binary_divide, 6768, 6767, 3915);
  g->Binary(ynn_binary_add, 3915, 7373, 3916);
  g->Binary(ynn_binary_pow, 3916, 7428, 3917);
  g->Binary(ynn_binary_multiply, 3912, 3917, 3918);
  g->Convert(7993, 3919);
  g->Binary(ynn_binary_multiply, 3918, 3919, 3920);
  BuildLayer24AttentionQueryProjection(ctx);
  BuildLayer24AttentionSdpa(ctx);
  BuildLayer24AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 3974, 3975);
  g->Reduce(ynn_reduce_sum, 3975, 6777, {2}, true);
  g->ShapeProduct(3975, 6776, {2});
  g->Binary(ynn_binary_divide, 6777, 6776, 3976);
  g->Binary(ynn_binary_add, 3976, 7373, 3977);
  g->Binary(ynn_binary_pow, 3977, 7428, 3978);
  g->Binary(ynn_binary_multiply, 3974, 3978, 3979);
  g->Convert(8005, 3982);
  g->Binary(ynn_binary_multiply, 3979, 3982, 3983);
  g->Binary(ynn_binary_add, 3912, 3983, 3984);
}

// Scope: "Layer24 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer24Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3984, 3985);
  g->Reduce(ynn_reduce_sum, 3985, 6781, {2}, true);
  g->ShapeProduct(3985, 6780, {2});
  g->Binary(ynn_binary_divide, 6781, 6780, 3986);
  g->Binary(ynn_binary_add, 3986, 7373, 3987);
  g->Binary(ynn_binary_pow, 3987, 7428, 3988);
  g->Binary(ynn_binary_multiply, 3984, 3988, 3989);
  g->Convert(8008, 3990);
  g->Binary(ynn_binary_multiply, 3989, 3990, 3991);
  g->Binary(ynn_binary_divide, 3991, 7426, 3993);
  g->Unary(ynn_unary_round, 3993, 3994);
  g->Binary(ynn_binary_max, 3994, 7225, 3995);
  g->Binary(ynn_binary_min, 3995, 7340, 3996);
  g->Binary(ynn_binary_multiply, 3996, 7426, 3997);
  g->Convert(7999, 3998);
  g->Binary(ynn_binary_multiply, 3998, 8000, 3999);
  g->Matmul(3997, 3999, 4000, false, true);
  g->Binary(ynn_binary_divide, 4000, 7260, 4001);
  g->Unary(ynn_unary_round, 4001, 4002);
  g->Binary(ynn_binary_max, 4002, 7225, 4004);
  g->Binary(ynn_binary_min, 4004, 7340, 4005);
  g->Binary(ynn_binary_multiply, 4005, 7260, 4006);
  g->Convert(7997, 4007);
  g->Binary(ynn_binary_multiply, 4007, 7998, 4008);
  g->Matmul(3997, 4008, 4010, false, true);
  g->Binary(ynn_binary_divide, 4010, 7260, 4011);
  g->Unary(ynn_unary_round, 4011, 4012);
  g->Binary(ynn_binary_max, 4012, 7225, 4013);
  g->Binary(ynn_binary_min, 4013, 7340, 4014);
  g->Binary(ynn_binary_multiply, 4014, 7260, 4015);
  g->Polynomial(4015, 6784, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6784, 6785);
  g->Binary(ynn_binary_add, 6785, 6183, 6782);
  g->Binary(ynn_binary_multiply, 4015, 6181, 6783);
  g->Binary(ynn_binary_multiply, 6783, 6782, 4016);
  g->Binary(ynn_binary_multiply, 4006, 4016, 4017);
  g->Binary(ynn_binary_divide, 4017, 7289, 4018);
  g->Unary(ynn_unary_round, 4018, 4019);
  g->Binary(ynn_binary_max, 4019, 7225, 4021);
  g->Binary(ynn_binary_min, 4021, 7340, 4022);
  g->Binary(ynn_binary_multiply, 4022, 7289, 4023);
  g->Convert(7995, 4024);
  g->Binary(ynn_binary_multiply, 4024, 7996, 4025);
  g->Matmul(4023, 4025, 4026, false, true);
  g->Binary(ynn_binary_divide, 4026, 7312, 4027);
  g->Unary(ynn_unary_round, 4027, 4028);
  g->Binary(ynn_binary_max, 4028, 7225, 4029);
  g->Binary(ynn_binary_min, 4029, 7340, 4030);
  g->Binary(ynn_binary_multiply, 4030, 7312, 4032);
  g->Unary(ynn_unary_square, 4032, 4033);
  g->Reduce(ynn_reduce_sum, 4033, 6787, {2}, true);
  g->ShapeProduct(4033, 6786, {2});
  g->Binary(ynn_binary_divide, 6787, 6786, 4034);
  g->Binary(ynn_binary_add, 4034, 7373, 4035);
  g->Binary(ynn_binary_pow, 4035, 7428, 4036);
  g->Binary(ynn_binary_multiply, 4032, 4036, 4037);
  g->Convert(8006, 4038);
  g->Binary(ynn_binary_multiply, 4037, 4038, 4039);
  g->Binary(ynn_binary_add, 3984, 4039, 4040);
}

// Scope: "Layer24 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer24PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1031, 4041, {0,0,24,0}, {-1,-1,1,-1});
  g->Reshape(4041, 4043, {1,1,256});
  g->Binary(ynn_binary_add, 4043, 8426, 4044);
  g->Binary(ynn_binary_multiply, 4044, 7155, 4045);
  g->Binary(ynn_binary_divide, 4040, 7438, 4046);
  g->Unary(ynn_unary_round, 4046, 4047);
  g->Binary(ynn_binary_max, 4047, 7225, 4048);
  g->Binary(ynn_binary_min, 4048, 7340, 4049);
  g->Binary(ynn_binary_multiply, 4049, 7438, 4050);
  g->Convert(8001, 4051);
  g->Binary(ynn_binary_multiply, 4051, 8002, 4052);
  g->Matmul(4050, 4052, 4054, false, true);
  g->Binary(ynn_binary_divide, 4054, 7147, 4055);
  g->Unary(ynn_unary_round, 4055, 4056);
  g->Binary(ynn_binary_max, 4056, 7225, 4057);
  g->Binary(ynn_binary_min, 4057, 7340, 4058);
  g->Binary(ynn_binary_multiply, 4058, 7147, 4059);
  g->Polynomial(4059, 6790, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6790, 6791);
  g->Binary(ynn_binary_add, 6791, 6183, 6788);
  g->Binary(ynn_binary_multiply, 4059, 6181, 6789);
  g->Binary(ynn_binary_multiply, 6789, 6788, 4060);
  g->Binary(ynn_binary_multiply, 4060, 4045, 4061);
  g->Binary(ynn_binary_divide, 4061, 7468, 4062);
  g->Unary(ynn_unary_round, 4062, 4063);
  g->Binary(ynn_binary_max, 4063, 7225, 4065);
  g->Binary(ynn_binary_min, 4065, 7340, 4066);
  g->Binary(ynn_binary_multiply, 4066, 7468, 4067);
  g->Convert(8003, 4068);
  g->Binary(ynn_binary_multiply, 4068, 8004, 4069);
  g->Matmul(4067, 4069, 4070, false, true);
  g->Binary(ynn_binary_divide, 4070, 7212, 4071);
  g->Unary(ynn_unary_round, 4071, 4072);
  g->Binary(ynn_binary_max, 4072, 7225, 4073);
  g->Binary(ynn_binary_min, 4073, 7340, 4074);
  g->Binary(ynn_binary_multiply, 4074, 7212, 4076);
  g->Unary(ynn_unary_square, 4076, 4077);
  g->Reduce(ynn_reduce_sum, 4077, 6793, {2}, true);
  g->ShapeProduct(4077, 6792, {2});
  g->Binary(ynn_binary_divide, 6793, 6792, 4078);
  g->Binary(ynn_binary_add, 4078, 7373, 4079);
  g->Binary(ynn_binary_pow, 4079, 7428, 4080);
  g->Binary(ynn_binary_multiply, 4076, 4080, 4081);
  g->Convert(8007, 4082);
  g->Binary(ynn_binary_multiply, 4081, 4082, 4083);
  g->Binary(ynn_binary_add, 4040, 4083, 4084);
  g->Convert(7994, 4085);
  g->Binary(ynn_binary_multiply, 4084, 4085, 4088);
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
  g->Binary(ynn_binary_divide, 4095, 7377, 4096);
  g->Unary(ynn_unary_round, 4096, 4097);
  g->Binary(ynn_binary_max, 4097, 7225, 4099);
  g->Binary(ynn_binary_min, 4099, 7340, 4100);
  g->Binary(ynn_binary_multiply, 4100, 7377, 4101);
  g->Convert(8033, 4102);
  g->Binary(ynn_binary_multiply, 4102, 8034, 4103);
  g->Matmul(4101, 4103, 4104, false, true);
  g->Binary(ynn_binary_divide, 4104, 7489, 4105);
  g->Unary(ynn_unary_round, 4105, 4106);
  g->Binary(ynn_binary_max, 4106, 7225, 4107);
  g->Binary(ynn_binary_min, 4107, 7340, 4108);
  g->Binary(ynn_binary_multiply, 4108, 7489, 4110);
  g->SplitDim(4110, 4111, 2, {8,256});
  g->FuseDims(4111, 4113, 1, 2);
  g->SplitDim(4113, 4112, 1, {8,1});
  g->Unary(ynn_unary_square, 4112, 4114);
  g->Reduce(ynn_reduce_sum, 4114, 6797, {3}, true);
  g->ShapeProduct(4114, 6796, {3});
  g->Binary(ynn_binary_divide, 6797, 6796, 4115);
  g->Binary(ynn_binary_add, 4115, 7373, 4116);
  g->Binary(ynn_binary_pow, 4116, 7428, 4117);
  g->Binary(ynn_binary_multiply, 4112, 4117, 4118);
  g->Convert(8032, 4119);
  g->Binary(ynn_binary_multiply, 4118, 4119, 4120);
  g->Slice(4120, 4121, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(4120, 4122, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 4122, 4123);
  g->Concat({4123,4121}, 4124, 3);
  g->Binary(ynn_binary_multiply, 4120, 2044, 4125);
  g->Binary(ynn_binary_multiply, 4124, 3111, 4126);
  g->Binary(ynn_binary_add, 4125, 4126, 4127);
}

// Scope: "Layer25 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer25AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(4127, 1963, 4128, false, true);
  g->Mask(4128, 7579, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 7579, 6801, {-1}, true);
  g->Binary(ynn_binary_subtract, 7579, 6801, 6798);
  g->Unary(ynn_unary_exp, 6798, 6799);
  g->Reduce(ynn_reduce_sum, 6799, 6802, {-1}, true);
  g->Binary(ynn_binary_divide, 6183, 6802, 6800);
  g->Binary(ynn_binary_multiply, 6799, 6800, 4129);
  g->Matmul(4129, 1965, 4130, false, false);
}

// Scope: "Layer25 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer25AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(4130, 4132, 1, 2);
  g->SplitDim(4132, 4131, 1, {1,8});
  g->FuseDims(4131, 4133, 2, 2);
  g->Binary(ynn_binary_divide, 4133, 7507, 4134);
  g->Unary(ynn_unary_round, 4134, 4135);
  g->Binary(ynn_binary_max, 4135, 7225, 4136);
  g->Binary(ynn_binary_min, 4136, 7340, 4137);
  g->Binary(ynn_binary_multiply, 4137, 7507, 4138);
  g->Convert(8030, 4139);
  g->Binary(ynn_binary_multiply, 4139, 8031, 4140);
  g->Matmul(4138, 4140, 4141, false, true);
  g->Binary(ynn_binary_divide, 4141, 7529, 4142);
  g->Unary(ynn_unary_round, 4142, 4143);
  g->Binary(ynn_binary_max, 4143, 7225, 4144);
  g->Binary(ynn_binary_min, 4144, 7340, 4145);
  g->Binary(ynn_binary_multiply, 4145, 7529, 4146);
}

// Scope: "Layer25 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer25Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 4088, 4089);
  g->Reduce(ynn_reduce_sum, 4089, 6795, {2}, true);
  g->ShapeProduct(4089, 6794, {2});
  g->Binary(ynn_binary_divide, 6795, 6794, 4090);
  g->Binary(ynn_binary_add, 4090, 7373, 4091);
  g->Binary(ynn_binary_pow, 4091, 7428, 4092);
  g->Binary(ynn_binary_multiply, 4088, 4092, 4093);
  g->Convert(8014, 4094);
  g->Binary(ynn_binary_multiply, 4093, 4094, 4095);
  BuildLayer25AttentionQueryProjection(ctx);
  BuildLayer25AttentionSdpa(ctx);
  BuildLayer25AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 4146, 4147);
  g->Reduce(ynn_reduce_sum, 4147, 6804, {2}, true);
  g->ShapeProduct(4147, 6803, {2});
  g->Binary(ynn_binary_divide, 6804, 6803, 4148);
  g->Binary(ynn_binary_add, 4148, 7373, 4149);
  g->Binary(ynn_binary_pow, 4149, 7428, 4150);
  g->Binary(ynn_binary_multiply, 4146, 4150, 4151);
  g->Convert(8026, 4152);
  g->Binary(ynn_binary_multiply, 4151, 4152, 4153);
  g->Binary(ynn_binary_add, 4088, 4153, 4154);
}

// Scope: "Layer25 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer25Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 4154, 4155);
  g->Reduce(ynn_reduce_sum, 4155, 6806, {2}, true);
  g->ShapeProduct(4155, 6805, {2});
  g->Binary(ynn_binary_divide, 6806, 6805, 4156);
  g->Binary(ynn_binary_add, 4156, 7373, 4157);
  g->Binary(ynn_binary_pow, 4157, 7428, 4158);
  g->Binary(ynn_binary_multiply, 4154, 4158, 4159);
  g->Convert(8029, 4160);
  g->Binary(ynn_binary_multiply, 4159, 4160, 4161);
  g->Binary(ynn_binary_divide, 4161, 7449, 4162);
  g->Unary(ynn_unary_round, 4162, 4163);
  g->Binary(ynn_binary_max, 4163, 7225, 4164);
  g->Binary(ynn_binary_min, 4164, 7340, 4165);
  g->Binary(ynn_binary_multiply, 4165, 7449, 4166);
  g->Convert(8020, 4167);
  g->Binary(ynn_binary_multiply, 4167, 8021, 4168);
  g->Matmul(4166, 4168, 4169, false, true);
  g->Binary(ynn_binary_divide, 4169, 7465, 4170);
  g->Unary(ynn_unary_round, 4170, 4172);
  g->Binary(ynn_binary_max, 4172, 7225, 4173);
  g->Binary(ynn_binary_min, 4173, 7340, 4174);
  g->Binary(ynn_binary_multiply, 4174, 7465, 4175);
  g->Convert(8018, 4176);
  g->Binary(ynn_binary_multiply, 4176, 8019, 4178);
  g->Matmul(4166, 4178, 4179, false, true);
  g->Binary(ynn_binary_divide, 4179, 7465, 4180);
  g->Unary(ynn_unary_round, 4180, 4181);
  g->Binary(ynn_binary_max, 4181, 7225, 4182);
  g->Binary(ynn_binary_min, 4182, 7340, 4183);
  g->Binary(ynn_binary_multiply, 4183, 7465, 4184);
  g->Polynomial(4184, 6809, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6809, 6810);
  g->Binary(ynn_binary_add, 6810, 6183, 6807);
  g->Binary(ynn_binary_multiply, 4184, 6181, 6808);
  g->Binary(ynn_binary_multiply, 6808, 6807, 4185);
  g->Binary(ynn_binary_multiply, 4175, 4185, 4186);
  g->Binary(ynn_binary_divide, 4186, 7232, 4187);
  g->Unary(ynn_unary_round, 4187, 4191);
  g->Binary(ynn_binary_max, 4191, 7225, 4192);
  g->Binary(ynn_binary_min, 4192, 7340, 4193);
  g->Binary(ynn_binary_multiply, 4193, 7232, 4194);
  g->Convert(8016, 4195);
  g->Binary(ynn_binary_multiply, 4195, 8017, 4196);
  g->Matmul(4194, 4196, 4197, false, true);
  g->Binary(ynn_binary_divide, 4197, 7553, 4198);
  g->Unary(ynn_unary_round, 4198, 4199);
  g->Binary(ynn_binary_max, 4199, 7225, 4200);
  g->Binary(ynn_binary_min, 4200, 7340, 4202);
  g->Binary(ynn_binary_multiply, 4202, 7553, 4203);
  g->Unary(ynn_unary_square, 4203, 4204);
  g->Reduce(ynn_reduce_sum, 4204, 6812, {2}, true);
  g->ShapeProduct(4204, 6811, {2});
  g->Binary(ynn_binary_divide, 6812, 6811, 4205);
  g->Binary(ynn_binary_add, 4205, 7373, 4206);
  g->Binary(ynn_binary_pow, 4206, 7428, 4207);
  g->Binary(ynn_binary_multiply, 4203, 4207, 4208);
  g->Convert(8027, 4209);
  g->Binary(ynn_binary_multiply, 4208, 4209, 4210);
  g->Binary(ynn_binary_add, 4154, 4210, 4211);
}

// Scope: "Layer25 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer25PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1031, 4213, {0,0,25,0}, {-1,-1,1,-1});
  g->Reshape(4213, 4214, {1,1,256});
  g->Binary(ynn_binary_add, 4214, 8427, 4215);
  g->Binary(ynn_binary_multiply, 4215, 7155, 4216);
  g->Binary(ynn_binary_divide, 4211, 7368, 4217);
  g->Unary(ynn_unary_round, 4217, 4218);
  g->Binary(ynn_binary_max, 4218, 7225, 4219);
  g->Binary(ynn_binary_min, 4219, 7340, 4220);
  g->Binary(ynn_binary_multiply, 4220, 7368, 4221);
  g->Convert(8022, 4222);
  g->Binary(ynn_binary_multiply, 4222, 8023, 4224);
  g->Matmul(4221, 4224, 4225, false, true);
  g->Binary(ynn_binary_divide, 4225, 7505, 4226);
  g->Unary(ynn_unary_round, 4226, 4227);
  g->Binary(ynn_binary_max, 4227, 7225, 4228);
  g->Binary(ynn_binary_min, 4228, 7340, 4229);
  g->Binary(ynn_binary_multiply, 4229, 7505, 4230);
  g->Polynomial(4230, 6815, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6815, 6816);
  g->Binary(ynn_binary_add, 6816, 6183, 6813);
  g->Binary(ynn_binary_multiply, 4230, 6181, 6814);
  g->Binary(ynn_binary_multiply, 6814, 6813, 4231);
  g->Binary(ynn_binary_multiply, 4231, 4216, 4232);
  g->Binary(ynn_binary_divide, 4232, 7281, 4233);
  g->Unary(ynn_unary_round, 4233, 4235);
  g->Binary(ynn_binary_max, 4235, 7225, 4236);
  g->Binary(ynn_binary_min, 4236, 7340, 4237);
  g->Binary(ynn_binary_multiply, 4237, 7281, 4238);
  g->Convert(8024, 4239);
  g->Binary(ynn_binary_multiply, 4239, 8025, 4240);
  g->Matmul(4238, 4240, 4241, false, true);
  g->Binary(ynn_binary_divide, 4241, 7476, 4242);
  g->Unary(ynn_unary_round, 4242, 4243);
  g->Binary(ynn_binary_max, 4243, 7225, 4244);
  g->Binary(ynn_binary_min, 4244, 7340, 4246);
  g->Binary(ynn_binary_multiply, 4246, 7476, 4247);
  g->Unary(ynn_unary_square, 4247, 4248);
  g->Reduce(ynn_reduce_sum, 4248, 6818, {2}, true);
  g->ShapeProduct(4248, 6817, {2});
  g->Binary(ynn_binary_divide, 6818, 6817, 4249);
  g->Binary(ynn_binary_add, 4249, 7373, 4250);
  g->Binary(ynn_binary_pow, 4250, 7428, 4251);
  g->Binary(ynn_binary_multiply, 4247, 4251, 4252);
  g->Convert(8028, 4253);
  g->Binary(ynn_binary_multiply, 4252, 4253, 4254);
  g->Binary(ynn_binary_add, 4211, 4254, 4255);
  g->Convert(8015, 4257);
  g->Binary(ynn_binary_multiply, 4255, 4257, 4258);
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
  g->Binary(ynn_binary_divide, 4265, 7427, 4266);
  g->Unary(ynn_unary_round, 4266, 4268);
  g->Binary(ynn_binary_max, 4268, 7225, 4269);
  g->Binary(ynn_binary_min, 4269, 7340, 4270);
  g->Binary(ynn_binary_multiply, 4270, 7427, 4271);
  g->Convert(8054, 4272);
  g->Binary(ynn_binary_multiply, 4272, 8055, 4273);
  g->Matmul(4271, 4273, 4274, false, true);
  g->Binary(ynn_binary_divide, 4274, 7414, 4275);
  g->Unary(ynn_unary_round, 4275, 4276);
  g->Binary(ynn_binary_max, 4276, 7225, 4277);
  g->Binary(ynn_binary_min, 4277, 7340, 4279);
  g->Binary(ynn_binary_multiply, 4279, 7414, 4280);
  g->SplitDim(4280, 4281, 2, {8,256});
  g->FuseDims(4281, 4283, 1, 2);
  g->SplitDim(4283, 4282, 1, {8,1});
  g->Unary(ynn_unary_square, 4282, 4284);
  g->Reduce(ynn_reduce_sum, 4284, 6822, {3}, true);
  g->ShapeProduct(4284, 6821, {3});
  g->Binary(ynn_binary_divide, 6822, 6821, 4285);
  g->Binary(ynn_binary_add, 4285, 7373, 4286);
  g->Binary(ynn_binary_pow, 4286, 7428, 4287);
  g->Binary(ynn_binary_multiply, 4282, 4287, 4288);
  g->Convert(8053, 4289);
  g->Binary(ynn_binary_multiply, 4288, 4289, 4291);
  g->Slice(4291, 4292, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(4291, 4293, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 4293, 4294);
  g->Concat({4294,4292}, 4295, 3);
  g->Binary(ynn_binary_multiply, 4291, 2044, 4296);
  g->Binary(ynn_binary_multiply, 4295, 3111, 4297);
  g->Binary(ynn_binary_add, 4296, 4297, 4298);
}

// Scope: "Layer26 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer26AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(4298, 1963, 4299, false, true);
  g->Mask(4299, 7580, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 7580, 6828, {-1}, true);
  g->Binary(ynn_binary_subtract, 7580, 6828, 6825);
  g->Unary(ynn_unary_exp, 6825, 6826);
  g->Reduce(ynn_reduce_sum, 6826, 6829, {-1}, true);
  g->Binary(ynn_binary_divide, 6183, 6829, 6827);
  g->Binary(ynn_binary_multiply, 6826, 6827, 4302);
  g->Matmul(4302, 1965, 4303, false, false);
}

// Scope: "Layer26 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer26AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(4303, 4305, 1, 2);
  g->SplitDim(4305, 4304, 1, {1,8});
  g->FuseDims(4304, 4306, 2, 2);
  g->Binary(ynn_binary_divide, 4306, 7504, 4307);
  g->Unary(ynn_unary_round, 4307, 4308);
  g->Binary(ynn_binary_max, 4308, 7225, 4309);
  g->Binary(ynn_binary_min, 4309, 7340, 4310);
  g->Binary(ynn_binary_multiply, 4310, 7504, 4311);
  g->Convert(8051, 4312);
  g->Binary(ynn_binary_multiply, 4312, 8052, 4314);
  g->Matmul(4311, 4314, 4315, false, true);
  g->Binary(ynn_binary_divide, 4315, 7201, 4316);
  g->Unary(ynn_unary_round, 4316, 4317);
  g->Binary(ynn_binary_max, 4317, 7225, 4318);
  g->Binary(ynn_binary_min, 4318, 7340, 4319);
  g->Binary(ynn_binary_multiply, 4319, 7201, 4320);
}

// Scope: "Layer26 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer26Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 4258, 4259);
  g->Reduce(ynn_reduce_sum, 4259, 6820, {2}, true);
  g->ShapeProduct(4259, 6819, {2});
  g->Binary(ynn_binary_divide, 6820, 6819, 4260);
  g->Binary(ynn_binary_add, 4260, 7373, 4261);
  g->Binary(ynn_binary_pow, 4261, 7428, 4262);
  g->Binary(ynn_binary_multiply, 4258, 4262, 4263);
  g->Convert(8035, 4264);
  g->Binary(ynn_binary_multiply, 4263, 4264, 4265);
  BuildLayer26AttentionQueryProjection(ctx);
  BuildLayer26AttentionSdpa(ctx);
  BuildLayer26AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 4320, 4321);
  g->Reduce(ynn_reduce_sum, 4321, 6831, {2}, true);
  g->ShapeProduct(4321, 6830, {2});
  g->Binary(ynn_binary_divide, 6831, 6830, 4322);
  g->Binary(ynn_binary_add, 4322, 7373, 4323);
  g->Binary(ynn_binary_pow, 4323, 7428, 4325);
  g->Binary(ynn_binary_multiply, 4320, 4325, 4326);
  g->Convert(8047, 4327);
  g->Binary(ynn_binary_multiply, 4326, 4327, 4328);
  g->Binary(ynn_binary_add, 4258, 4328, 4329);
}

// Scope: "Layer26 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer26Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 4329, 4330);
  g->Reduce(ynn_reduce_sum, 4330, 6833, {2}, true);
  g->ShapeProduct(4330, 6832, {2});
  g->Binary(ynn_binary_divide, 6833, 6832, 4331);
  g->Binary(ynn_binary_add, 4331, 7373, 4332);
  g->Binary(ynn_binary_pow, 4332, 7428, 4333);
  g->Binary(ynn_binary_multiply, 4329, 4333, 4334);
  g->Convert(8050, 4336);
  g->Binary(ynn_binary_multiply, 4334, 4336, 4337);
  g->Binary(ynn_binary_divide, 4337, 7474, 4338);
  g->Unary(ynn_unary_round, 4338, 4339);
  g->Binary(ynn_binary_max, 4339, 7225, 4340);
  g->Binary(ynn_binary_min, 4340, 7340, 4341);
  g->Binary(ynn_binary_multiply, 4341, 7474, 4342);
  g->Convert(8041, 4343);
  g->Binary(ynn_binary_multiply, 4343, 8042, 4344);
  g->Matmul(4342, 4344, 4345, false, true);
  g->Binary(ynn_binary_divide, 4345, 7387, 4346);
  g->Unary(ynn_unary_round, 4346, 4347);
  g->Binary(ynn_binary_max, 4347, 7225, 4348);
  g->Binary(ynn_binary_min, 4348, 7340, 4349);
  g->Binary(ynn_binary_multiply, 4349, 7387, 4350);
  g->Convert(8039, 4351);
  g->Binary(ynn_binary_multiply, 4351, 8040, 4352);
  g->Matmul(4342, 4352, 4353, false, true);
  g->Binary(ynn_binary_divide, 4353, 7387, 4354);
  g->Unary(ynn_unary_round, 4354, 4355);
  g->Binary(ynn_binary_max, 4355, 7225, 4356);
  g->Binary(ynn_binary_min, 4356, 7340, 4357);
  g->Binary(ynn_binary_multiply, 4357, 7387, 4358);
  g->Polynomial(4358, 6836, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6836, 6837);
  g->Binary(ynn_binary_add, 6837, 6183, 6834);
  g->Binary(ynn_binary_multiply, 4358, 6181, 6835);
  g->Binary(ynn_binary_multiply, 6835, 6834, 4359);
  g->Binary(ynn_binary_multiply, 4350, 4359, 4360);
  g->Binary(ynn_binary_divide, 4360, 7481, 4362);
  g->Unary(ynn_unary_round, 4362, 4363);
  g->Binary(ynn_binary_max, 4363, 7225, 4364);
  g->Binary(ynn_binary_min, 4364, 7340, 4365);
  g->Binary(ynn_binary_multiply, 4365, 7481, 4366);
  g->Convert(8037, 4367);
  g->Binary(ynn_binary_multiply, 4367, 8038, 4368);
  g->Matmul(4366, 4368, 4369, false, true);
  g->Binary(ynn_binary_divide, 4369, 7204, 4370);
  g->Unary(ynn_unary_round, 4370, 4371);
  g->Binary(ynn_binary_max, 4371, 7225, 4373);
  g->Binary(ynn_binary_min, 4373, 7340, 4374);
  g->Binary(ynn_binary_multiply, 4374, 7204, 4375);
  g->Unary(ynn_unary_square, 4375, 4376);
  g->Reduce(ynn_reduce_sum, 4376, 6839, {2}, true);
  g->ShapeProduct(4376, 6838, {2});
  g->Binary(ynn_binary_divide, 6839, 6838, 4377);
  g->Binary(ynn_binary_add, 4377, 7373, 4378);
  g->Binary(ynn_binary_pow, 4378, 7428, 4379);
  g->Binary(ynn_binary_multiply, 4375, 4379, 4380);
  g->Convert(8048, 4381);
  g->Binary(ynn_binary_multiply, 4380, 4381, 4382);
  g->Binary(ynn_binary_add, 4329, 4382, 4383);
}

// Scope: "Layer26 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer26PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1031, 4384, {0,0,26,0}, {-1,-1,1,-1});
  g->Reshape(4384, 4385, {1,1,256});
  g->Binary(ynn_binary_add, 4385, 8428, 4386);
  g->Binary(ynn_binary_multiply, 4386, 7155, 4387);
  g->Binary(ynn_binary_divide, 4383, 7548, 4388);
  g->Unary(ynn_unary_round, 4388, 4389);
  g->Binary(ynn_binary_max, 4389, 7225, 4390);
  g->Binary(ynn_binary_min, 4390, 7340, 4391);
  g->Binary(ynn_binary_multiply, 4391, 7548, 4392);
  g->Convert(8043, 4393);
  g->Binary(ynn_binary_multiply, 4393, 8044, 4394);
  g->Matmul(4392, 4394, 4395, false, true);
  g->Binary(ynn_binary_divide, 4395, 7545, 4396);
  g->Unary(ynn_unary_round, 4396, 4397);
  g->Binary(ynn_binary_max, 4397, 7225, 4398);
  g->Binary(ynn_binary_min, 4398, 7340, 4399);
  g->Binary(ynn_binary_multiply, 4399, 7545, 4400);
  g->Polynomial(4400, 6842, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6842, 6843);
  g->Binary(ynn_binary_add, 6843, 6183, 6840);
  g->Binary(ynn_binary_multiply, 4400, 6181, 6841);
  g->Binary(ynn_binary_multiply, 6841, 6840, 4401);
  g->Binary(ynn_binary_multiply, 4401, 4387, 4402);
  g->Binary(ynn_binary_divide, 4402, 7513, 4405);
  g->Unary(ynn_unary_round, 4405, 4406);
  g->Binary(ynn_binary_max, 4406, 7225, 4407);
  g->Binary(ynn_binary_min, 4407, 7340, 4408);
  g->Binary(ynn_binary_multiply, 4408, 7513, 4409);
  g->Convert(8045, 4410);
  g->Binary(ynn_binary_multiply, 4410, 8046, 4411);
  g->Matmul(4409, 4411, 4412, false, true);
  g->Binary(ynn_binary_divide, 4412, 7357, 4413);
  g->Unary(ynn_unary_round, 4413, 4414);
  g->Binary(ynn_binary_max, 4414, 7225, 4415);
  g->Binary(ynn_binary_min, 4415, 7340, 4416);
  g->Binary(ynn_binary_multiply, 4416, 7357, 4417);
  g->Unary(ynn_unary_square, 4417, 4418);
  g->Reduce(ynn_reduce_sum, 4418, 6845, {2}, true);
  g->ShapeProduct(4418, 6844, {2});
  g->Binary(ynn_binary_divide, 6845, 6844, 4419);
  g->Binary(ynn_binary_add, 4419, 7373, 4420);
  g->Binary(ynn_binary_pow, 4420, 7428, 4421);
  g->Binary(ynn_binary_multiply, 4417, 4421, 4422);
  g->Convert(8049, 4423);
  g->Binary(ynn_binary_multiply, 4422, 4423, 4424);
  g->Binary(ynn_binary_add, 4383, 4424, 4425);
  g->Convert(8036, 4426);
  g->Binary(ynn_binary_multiply, 4425, 4426, 4427);
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
  g->Binary(ynn_binary_divide, 4434, 7512, 4435);
  g->Unary(ynn_unary_round, 4435, 4436);
  g->Binary(ynn_binary_max, 4436, 7225, 4437);
  g->Binary(ynn_binary_min, 4437, 7340, 4438);
  g->Binary(ynn_binary_multiply, 4438, 7512, 4439);
  g->Convert(8075, 4440);
  g->Binary(ynn_binary_multiply, 4440, 8076, 4441);
  g->Matmul(4439, 4441, 4442, false, true);
  g->Binary(ynn_binary_divide, 4442, 7235, 4443);
  g->Unary(ynn_unary_round, 4443, 4444);
  g->Binary(ynn_binary_max, 4444, 7225, 4445);
  g->Binary(ynn_binary_min, 4445, 7340, 4446);
  g->Binary(ynn_binary_multiply, 4446, 7235, 4447);
  g->SplitDim(4447, 4448, 2, {8,256});
  g->FuseDims(4448, 4450, 1, 2);
  g->SplitDim(4450, 4449, 1, {8,1});
  g->Unary(ynn_unary_square, 4449, 4451);
  g->Reduce(ynn_reduce_sum, 4451, 6849, {3}, true);
  g->ShapeProduct(4451, 6848, {3});
  g->Binary(ynn_binary_divide, 6849, 6848, 4452);
  g->Binary(ynn_binary_add, 4452, 7373, 4453);
  g->Binary(ynn_binary_pow, 4453, 7428, 4454);
  g->Binary(ynn_binary_multiply, 4449, 4454, 4455);
  g->Convert(8074, 4456);
  g->Binary(ynn_binary_multiply, 4455, 4456, 4457);
  g->Slice(4457, 4458, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(4457, 4459, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 4459, 4460);
  g->Concat({4460,4458}, 4461, 3);
  g->Binary(ynn_binary_multiply, 4457, 2044, 4462);
  g->Binary(ynn_binary_multiply, 4461, 3111, 4463);
  g->Binary(ynn_binary_add, 4462, 4463, 4464);
}

// Scope: "Layer27 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer27AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(4464, 1963, 4465, false, true);
  g->Mask(4465, 7581, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 7581, 6853, {-1}, true);
  g->Binary(ynn_binary_subtract, 7581, 6853, 6850);
  g->Unary(ynn_unary_exp, 6850, 6851);
  g->Reduce(ynn_reduce_sum, 6851, 6854, {-1}, true);
  g->Binary(ynn_binary_divide, 6183, 6854, 6852);
  g->Binary(ynn_binary_multiply, 6851, 6852, 4467);
  g->Matmul(4467, 1965, 4468, false, false);
}

// Scope: "Layer27 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer27AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(4468, 4470, 1, 2);
  g->SplitDim(4470, 4469, 1, {1,8});
  g->FuseDims(4469, 4471, 2, 2);
  g->Binary(ynn_binary_divide, 4471, 7533, 4472);
  g->Unary(ynn_unary_round, 4472, 4473);
  g->Binary(ynn_binary_max, 4473, 7225, 4474);
  g->Binary(ynn_binary_min, 4474, 7340, 4475);
  g->Binary(ynn_binary_multiply, 4475, 7533, 4476);
  g->Convert(8072, 4478);
  g->Binary(ynn_binary_multiply, 4478, 8073, 4479);
  g->Matmul(4476, 4479, 4480, false, true);
  g->Binary(ynn_binary_divide, 4480, 7447, 4481);
  g->Unary(ynn_unary_round, 4481, 4482);
  g->Binary(ynn_binary_max, 4482, 7225, 4483);
  g->Binary(ynn_binary_min, 4483, 7340, 4484);
  g->Binary(ynn_binary_multiply, 4484, 7447, 4485);
}

// Scope: "Layer27 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer27Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 4427, 4428);
  g->Reduce(ynn_reduce_sum, 4428, 6847, {2}, true);
  g->ShapeProduct(4428, 6846, {2});
  g->Binary(ynn_binary_divide, 6847, 6846, 4429);
  g->Binary(ynn_binary_add, 4429, 7373, 4430);
  g->Binary(ynn_binary_pow, 4430, 7428, 4431);
  g->Binary(ynn_binary_multiply, 4427, 4431, 4432);
  g->Convert(8056, 4433);
  g->Binary(ynn_binary_multiply, 4432, 4433, 4434);
  BuildLayer27AttentionQueryProjection(ctx);
  BuildLayer27AttentionSdpa(ctx);
  BuildLayer27AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 4485, 4486);
  g->Reduce(ynn_reduce_sum, 4486, 6856, {2}, true);
  g->ShapeProduct(4486, 6855, {2});
  g->Binary(ynn_binary_divide, 6856, 6855, 4487);
  g->Binary(ynn_binary_add, 4487, 7373, 4489);
  g->Binary(ynn_binary_pow, 4489, 7428, 4490);
  g->Binary(ynn_binary_multiply, 4485, 4490, 4491);
  g->Convert(8068, 4492);
  g->Binary(ynn_binary_multiply, 4491, 4492, 4493);
  g->Binary(ynn_binary_add, 4427, 4493, 4494);
}

// Scope: "Layer27 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer27Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 4494, 4495);
  g->Reduce(ynn_reduce_sum, 4495, 6858, {2}, true);
  g->ShapeProduct(4495, 6857, {2});
  g->Binary(ynn_binary_divide, 6858, 6857, 4496);
  g->Binary(ynn_binary_add, 4496, 7373, 4497);
  g->Binary(ynn_binary_pow, 4497, 7428, 4498);
  g->Binary(ynn_binary_multiply, 4494, 4498, 4500);
  g->Convert(8071, 4501);
  g->Binary(ynn_binary_multiply, 4500, 4501, 4502);
  g->Binary(ynn_binary_divide, 4502, 7451, 4503);
  g->Unary(ynn_unary_round, 4503, 4504);
  g->Binary(ynn_binary_max, 4504, 7225, 4505);
  g->Binary(ynn_binary_min, 4505, 7340, 4506);
  g->Binary(ynn_binary_multiply, 4506, 7451, 4507);
  g->Convert(8062, 4508);
  g->Binary(ynn_binary_multiply, 4508, 8063, 4509);
  g->Matmul(4507, 4509, 4512, false, true);
  g->Binary(ynn_binary_divide, 4512, 7552, 4513);
  g->Unary(ynn_unary_round, 4513, 4514);
  g->Binary(ynn_binary_max, 4514, 7225, 4515);
  g->Binary(ynn_binary_min, 4515, 7340, 4516);
  g->Binary(ynn_binary_multiply, 4516, 7552, 4517);
  g->Convert(8060, 4519);
  g->Binary(ynn_binary_multiply, 4519, 8061, 4520);
  g->Matmul(4507, 4520, 4521, false, true);
  g->Binary(ynn_binary_divide, 4521, 7552, 4522);
  g->Unary(ynn_unary_round, 4522, 4523);
  g->Binary(ynn_binary_max, 4523, 7225, 4524);
  g->Binary(ynn_binary_min, 4524, 7340, 4525);
  g->Binary(ynn_binary_multiply, 4525, 7552, 4526);
  g->Polynomial(4526, 6861, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6861, 6862);
  g->Binary(ynn_binary_add, 6862, 6183, 6859);
  g->Binary(ynn_binary_multiply, 4526, 6181, 6860);
  g->Binary(ynn_binary_multiply, 6860, 6859, 4527);
  g->Binary(ynn_binary_multiply, 4517, 4527, 4529);
  g->Binary(ynn_binary_divide, 4529, 7321, 4530);
  g->Unary(ynn_unary_round, 4530, 4531);
  g->Binary(ynn_binary_max, 4531, 7225, 4532);
  g->Binary(ynn_binary_min, 4532, 7340, 4533);
  g->Binary(ynn_binary_multiply, 4533, 7321, 4534);
  g->Convert(8058, 4535);
  g->Binary(ynn_binary_multiply, 4535, 8059, 4536);
  g->Matmul(4534, 4536, 4537, false, true);
  g->Binary(ynn_binary_divide, 4537, 7158, 4538);
  g->Unary(ynn_unary_round, 4538, 4540);
  g->Binary(ynn_binary_max, 4540, 7225, 4541);
  g->Binary(ynn_binary_min, 4541, 7340, 4542);
  g->Binary(ynn_binary_multiply, 4542, 7158, 4543);
  g->Unary(ynn_unary_square, 4543, 4544);
  g->Reduce(ynn_reduce_sum, 4544, 6864, {2}, true);
  g->ShapeProduct(4544, 6863, {2});
  g->Binary(ynn_binary_divide, 6864, 6863, 4545);
  g->Binary(ynn_binary_add, 4545, 7373, 4546);
  g->Binary(ynn_binary_pow, 4546, 7428, 4547);
  g->Binary(ynn_binary_multiply, 4543, 4547, 4548);
  g->Convert(8069, 4549);
  g->Binary(ynn_binary_multiply, 4548, 4549, 4551);
  g->Binary(ynn_binary_add, 4494, 4551, 4552);
}

// Scope: "Layer27 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer27PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1031, 4553, {0,0,27,0}, {-1,-1,1,-1});
  g->Reshape(4553, 4554, {1,1,256});
  g->Binary(ynn_binary_add, 4554, 8429, 4555);
  g->Binary(ynn_binary_multiply, 4555, 7155, 4556);
  g->Binary(ynn_binary_divide, 4552, 7349, 4557);
  g->Unary(ynn_unary_round, 4557, 4558);
  g->Binary(ynn_binary_max, 4558, 7225, 4559);
  g->Binary(ynn_binary_min, 4559, 7340, 4560);
  g->Binary(ynn_binary_multiply, 4560, 7349, 4563);
  g->Convert(8064, 4564);
  g->Binary(ynn_binary_multiply, 4564, 8065, 4565);
  g->Matmul(4563, 4565, 4566, false, true);
  g->Binary(ynn_binary_divide, 4566, 7509, 4567);
  g->Unary(ynn_unary_round, 4567, 4568);
  g->Binary(ynn_binary_max, 4568, 7225, 4569);
  g->Binary(ynn_binary_min, 4569, 7340, 4570);
  g->Binary(ynn_binary_multiply, 4570, 7509, 4571);
  g->Polynomial(4571, 6867, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6867, 6868);
  g->Binary(ynn_binary_add, 6868, 6183, 6865);
  g->Binary(ynn_binary_multiply, 4571, 6181, 6866);
  g->Binary(ynn_binary_multiply, 6866, 6865, 4572);
  g->Binary(ynn_binary_multiply, 4572, 4556, 4574);
  g->Binary(ynn_binary_divide, 4574, 7421, 4575);
  g->Unary(ynn_unary_round, 4575, 4576);
  g->Binary(ynn_binary_max, 4576, 7225, 4577);
  g->Binary(ynn_binary_min, 4577, 7340, 4578);
  g->Binary(ynn_binary_multiply, 4578, 7421, 4579);
  g->Convert(8066, 4580);
  g->Binary(ynn_binary_multiply, 4580, 8067, 4581);
  g->Matmul(4579, 4581, 4582, false, true);
  g->Binary(ynn_binary_divide, 4582, 7308, 4583);
  g->Unary(ynn_unary_round, 4583, 4585);
  g->Binary(ynn_binary_max, 4585, 7225, 4586);
  g->Binary(ynn_binary_min, 4586, 7340, 4587);
  g->Binary(ynn_binary_multiply, 4587, 7308, 4588);
  g->Unary(ynn_unary_square, 4588, 4589);
  g->Reduce(ynn_reduce_sum, 4589, 6872, {2}, true);
  g->ShapeProduct(4589, 6871, {2});
  g->Binary(ynn_binary_divide, 6872, 6871, 4590);
  g->Binary(ynn_binary_add, 4590, 7373, 4591);
  g->Binary(ynn_binary_pow, 4591, 7428, 4592);
  g->Binary(ynn_binary_multiply, 4588, 4592, 4593);
  g->Convert(8070, 4594);
  g->Binary(ynn_binary_multiply, 4593, 4594, 4596);
  g->Binary(ynn_binary_add, 4552, 4596, 4597);
  g->Convert(8057, 4598);
  g->Binary(ynn_binary_multiply, 4597, 4598, 4599);
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
  g->Binary(ynn_binary_divide, 4607, 7209, 4608);
  g->Unary(ynn_unary_round, 4608, 4609);
  g->Binary(ynn_binary_max, 4609, 7225, 4610);
  g->Binary(ynn_binary_min, 4610, 7340, 4611);
  g->Binary(ynn_binary_multiply, 4611, 7209, 4612);
  g->Convert(8096, 4613);
  g->Binary(ynn_binary_multiply, 4613, 8097, 4614);
  g->Matmul(4612, 4614, 4615, false, true);
  g->Binary(ynn_binary_divide, 4615, 7170, 4616);
  g->Unary(ynn_unary_round, 4616, 4619);
  g->Binary(ynn_binary_max, 4619, 7225, 4620);
  g->Binary(ynn_binary_min, 4620, 7340, 4621);
  g->Binary(ynn_binary_multiply, 4621, 7170, 4622);
  g->SplitDim(4622, 4623, 2, {8,256});
  g->FuseDims(4623, 4625, 1, 2);
  g->SplitDim(4625, 4624, 1, {8,1});
  g->Unary(ynn_unary_square, 4624, 4626);
  g->Reduce(ynn_reduce_sum, 4626, 6876, {3}, true);
  g->ShapeProduct(4626, 6875, {3});
  g->Binary(ynn_binary_divide, 6876, 6875, 4627);
  g->Binary(ynn_binary_add, 4627, 7373, 4628);
  g->Binary(ynn_binary_pow, 4628, 7428, 4629);
  g->Binary(ynn_binary_multiply, 4624, 4629, 4631);
  g->Convert(8095, 4632);
  g->Binary(ynn_binary_multiply, 4631, 4632, 4633);
  g->Slice(4633, 4634, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(4633, 4635, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 4635, 4636);
  g->Concat({4636,4634}, 4637, 3);
  g->Binary(ynn_binary_multiply, 4633, 2044, 4638);
  g->Binary(ynn_binary_multiply, 4637, 3111, 4639);
  g->Binary(ynn_binary_add, 4638, 4639, 4640);
}

// Scope: "Layer28 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer28AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(4640, 1963, 4642, false, true);
  g->Mask(4642, 7582, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 7582, 6880, {-1}, true);
  g->Binary(ynn_binary_subtract, 7582, 6880, 6877);
  g->Unary(ynn_unary_exp, 6877, 6878);
  g->Reduce(ynn_reduce_sum, 6878, 6881, {-1}, true);
  g->Binary(ynn_binary_divide, 6183, 6881, 6879);
  g->Binary(ynn_binary_multiply, 6878, 6879, 4643);
  g->Matmul(4643, 1965, 4644, false, false);
}

// Scope: "Layer28 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer28AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(4644, 4646, 1, 2);
  g->SplitDim(4646, 4645, 1, {1,8});
  g->FuseDims(4645, 4647, 2, 2);
  g->Binary(ynn_binary_divide, 4647, 7533, 4648);
  g->Unary(ynn_unary_round, 4648, 4649);
  g->Binary(ynn_binary_max, 4649, 7225, 4650);
  g->Binary(ynn_binary_min, 4650, 7340, 4651);
  g->Binary(ynn_binary_multiply, 4651, 7533, 4653);
  g->Convert(8093, 4654);
  g->Binary(ynn_binary_multiply, 4654, 8094, 4655);
  g->Matmul(4653, 4655, 4656, false, true);
  g->Binary(ynn_binary_divide, 4656, 7261, 4657);
  g->Unary(ynn_unary_round, 4657, 4658);
  g->Binary(ynn_binary_max, 4658, 7225, 4659);
  g->Binary(ynn_binary_min, 4659, 7340, 4660);
  g->Binary(ynn_binary_multiply, 4660, 7261, 4661);
}

// Scope: "Layer28 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer28Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 4599, 4600);
  g->Reduce(ynn_reduce_sum, 4600, 6874, {2}, true);
  g->ShapeProduct(4600, 6873, {2});
  g->Binary(ynn_binary_divide, 6874, 6873, 4601);
  g->Binary(ynn_binary_add, 4601, 7373, 4602);
  g->Binary(ynn_binary_pow, 4602, 7428, 4603);
  g->Binary(ynn_binary_multiply, 4599, 4603, 4604);
  g->Convert(8077, 4605);
  g->Binary(ynn_binary_multiply, 4604, 4605, 4607);
  BuildLayer28AttentionQueryProjection(ctx);
  BuildLayer28AttentionSdpa(ctx);
  BuildLayer28AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 4661, 4662);
  g->Reduce(ynn_reduce_sum, 4662, 6883, {2}, true);
  g->ShapeProduct(4662, 6882, {2});
  g->Binary(ynn_binary_divide, 6883, 6882, 4664);
  g->Binary(ynn_binary_add, 4664, 7373, 4665);
  g->Binary(ynn_binary_pow, 4665, 7428, 4666);
  g->Binary(ynn_binary_multiply, 4661, 4666, 4667);
  g->Convert(8089, 4668);
  g->Binary(ynn_binary_multiply, 4667, 4668, 4669);
  g->Binary(ynn_binary_add, 4599, 4669, 4670);
}

// Scope: "Layer28 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer28Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 4670, 4671);
  g->Reduce(ynn_reduce_sum, 4671, 6885, {2}, true);
  g->ShapeProduct(4671, 6884, {2});
  g->Binary(ynn_binary_divide, 6885, 6884, 4672);
  g->Binary(ynn_binary_add, 4672, 7373, 4673);
  g->Binary(ynn_binary_pow, 4673, 7428, 4675);
  g->Binary(ynn_binary_multiply, 4670, 4675, 4676);
  g->Convert(8092, 4677);
  g->Binary(ynn_binary_multiply, 4676, 4677, 4678);
  g->Binary(ynn_binary_divide, 4678, 7160, 4679);
  g->Unary(ynn_unary_round, 4679, 4680);
  g->Binary(ynn_binary_max, 4680, 7225, 4681);
  g->Binary(ynn_binary_min, 4681, 7340, 4682);
  g->Binary(ynn_binary_multiply, 4682, 7160, 4683);
  g->Convert(8083, 4684);
  g->Binary(ynn_binary_multiply, 4684, 8084, 4686);
  g->Matmul(4683, 4686, 4687, false, true);
  g->Binary(ynn_binary_divide, 4687, 7493, 4688);
  g->Unary(ynn_unary_round, 4688, 4689);
  g->Binary(ynn_binary_max, 4689, 7225, 4690);
  g->Binary(ynn_binary_min, 4690, 7340, 4691);
  g->Binary(ynn_binary_multiply, 4691, 7493, 4692);
  g->Convert(8081, 4694);
  g->Binary(ynn_binary_multiply, 4694, 8082, 4695);
  g->Matmul(4683, 4695, 4696, false, true);
  g->Binary(ynn_binary_divide, 4696, 7493, 4697);
  g->Unary(ynn_unary_round, 4697, 4698);
  g->Binary(ynn_binary_max, 4698, 7225, 4699);
  g->Binary(ynn_binary_min, 4699, 7340, 4700);
  g->Binary(ynn_binary_multiply, 4700, 7493, 4701);
  g->Polynomial(4701, 6888, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6888, 6889);
  g->Binary(ynn_binary_add, 6889, 6183, 6886);
  g->Binary(ynn_binary_multiply, 4701, 6181, 6887);
  g->Binary(ynn_binary_multiply, 6887, 6886, 4703);
  g->Binary(ynn_binary_multiply, 4692, 4703, 4704);
  g->Binary(ynn_binary_divide, 4704, 7500, 4705);
  g->Unary(ynn_unary_round, 4705, 4706);
  g->Binary(ynn_binary_max, 4706, 7225, 4707);
  g->Binary(ynn_binary_min, 4707, 7340, 4708);
  g->Binary(ynn_binary_multiply, 4708, 7500, 4709);
  g->Convert(8079, 4710);
  g->Binary(ynn_binary_multiply, 4710, 8080, 4711);
  g->Matmul(4709, 4711, 4712, false, true);
  g->Binary(ynn_binary_divide, 4712, 7547, 4714);
  g->Unary(ynn_unary_round, 4714, 4715);
  g->Binary(ynn_binary_max, 4715, 7225, 4716);
  g->Binary(ynn_binary_min, 4716, 7340, 4717);
  g->Binary(ynn_binary_multiply, 4717, 7547, 4718);
  g->Unary(ynn_unary_square, 4718, 4719);
  g->Reduce(ynn_reduce_sum, 4719, 6891, {2}, true);
  g->ShapeProduct(4719, 6890, {2});
  g->Binary(ynn_binary_divide, 6891, 6890, 4720);
  g->Binary(ynn_binary_add, 4720, 7373, 4721);
  g->Binary(ynn_binary_pow, 4721, 7428, 4722);
  g->Binary(ynn_binary_multiply, 4718, 4722, 4723);
  g->Convert(8090, 4726);
  g->Binary(ynn_binary_multiply, 4723, 4726, 4727);
  g->Binary(ynn_binary_add, 4670, 4727, 4728);
}

// Scope: "Layer28 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer28PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1031, 4729, {0,0,28,0}, {-1,-1,1,-1});
  g->Reshape(4729, 4730, {1,1,256});
  g->Binary(ynn_binary_add, 4730, 8430, 4731);
  g->Binary(ynn_binary_multiply, 4731, 7155, 4732);
  g->Binary(ynn_binary_divide, 4728, 7542, 4733);
  g->Unary(ynn_unary_round, 4733, 4734);
  g->Binary(ynn_binary_max, 4734, 7225, 4735);
  g->Binary(ynn_binary_min, 4735, 7340, 4736);
  g->Binary(ynn_binary_multiply, 4736, 7542, 4737);
  g->Convert(8085, 4738);
  g->Binary(ynn_binary_multiply, 4738, 8086, 4739);
  g->Matmul(4737, 4739, 4740, false, true);
  g->Binary(ynn_binary_divide, 4740, 7169, 4741);
  g->Unary(ynn_unary_round, 4741, 4742);
  g->Binary(ynn_binary_max, 4742, 7225, 4743);
  g->Binary(ynn_binary_min, 4743, 7340, 4744);
  g->Binary(ynn_binary_multiply, 4744, 7169, 4745);
  g->Polynomial(4745, 6899, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6899, 6900);
  g->Binary(ynn_binary_add, 6900, 6183, 6897);
  g->Binary(ynn_binary_multiply, 4745, 6181, 6898);
  g->Binary(ynn_binary_multiply, 6898, 6897, 4747);
  g->Binary(ynn_binary_multiply, 4747, 4732, 4748);
  g->Binary(ynn_binary_divide, 4748, 7150, 4749);
  g->Unary(ynn_unary_round, 4749, 4750);
  g->Binary(ynn_binary_max, 4750, 7225, 4751);
  g->Binary(ynn_binary_min, 4751, 7340, 4752);
  g->Binary(ynn_binary_multiply, 4752, 7150, 4753);
  g->Convert(8087, 4754);
  g->Binary(ynn_binary_multiply, 4754, 8088, 4755);
  g->Matmul(4753, 4755, 4756, false, true);
  g->Binary(ynn_binary_divide, 4756, 7412, 4758);
  g->Unary(ynn_unary_round, 4758, 4759);
  g->Binary(ynn_binary_max, 4759, 7225, 4760);
  g->Binary(ynn_binary_min, 4760, 7340, 4761);
  g->Binary(ynn_binary_multiply, 4761, 7412, 4762);
  g->Unary(ynn_unary_square, 4762, 4763);
  g->Reduce(ynn_reduce_sum, 4763, 6902, {2}, true);
  g->ShapeProduct(4763, 6901, {2});
  g->Binary(ynn_binary_divide, 6902, 6901, 4764);
  g->Binary(ynn_binary_add, 4764, 7373, 4765);
  g->Binary(ynn_binary_pow, 4765, 7428, 4766);
  g->Binary(ynn_binary_multiply, 4762, 4766, 4767);
  g->Convert(8091, 4770);
  g->Binary(ynn_binary_multiply, 4767, 4770, 4771);
  g->Binary(ynn_binary_add, 4728, 4771, 4772);
  g->Convert(8078, 4773);
  g->Binary(ynn_binary_multiply, 4772, 4773, 4774);
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
  g->Binary(ynn_binary_divide, 4782, 7537, 4783);
  g->Unary(ynn_unary_round, 4783, 4784);
  g->Binary(ynn_binary_max, 4784, 7225, 4785);
  g->Binary(ynn_binary_min, 4785, 7340, 4786);
  g->Binary(ynn_binary_multiply, 4786, 7537, 4787);
  g->Convert(8117, 4788);
  g->Binary(ynn_binary_multiply, 4788, 8118, 4789);
  g->Matmul(4787, 4789, 4790, false, true);
  g->Binary(ynn_binary_divide, 4790, 7162, 4792);
  g->Unary(ynn_unary_round, 4792, 4793);
  g->Binary(ynn_binary_max, 4793, 7225, 4794);
  g->Binary(ynn_binary_min, 4794, 7340, 4795);
  g->Binary(ynn_binary_multiply, 4795, 7162, 4796);
  g->SplitDim(4796, 4797, 2, {8,512});
  g->FuseDims(4797, 4799, 1, 2);
  g->SplitDim(4799, 4798, 1, {8,1});
  g->Unary(ynn_unary_square, 4798, 4800);
  g->Reduce(ynn_reduce_sum, 4800, 6906, {3}, true);
  g->ShapeProduct(4800, 6905, {3});
  g->Binary(ynn_binary_divide, 6906, 6905, 4801);
  g->Binary(ynn_binary_add, 4801, 7373, 4802);
  g->Binary(ynn_binary_pow, 4802, 7428, 4804);
  g->Binary(ynn_binary_multiply, 4798, 4804, 4805);
  g->Convert(8116, 4806);
  g->Binary(ynn_binary_multiply, 4805, 4806, 4807);
  g->Slice(4807, 4808, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(4807, 4809, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 4809, 4810);
  g->Concat({4810,4808}, 4811, 3);
  g->Binary(ynn_binary_multiply, 4807, 5976, 4812);
  g->Binary(ynn_binary_multiply, 4811, 6075, 4813);
  g->Binary(ynn_binary_add, 4812, 4813, 4815);
}

// Scope: "Layer29 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer29AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(4815, 2179, 4816, false, true);
  g->Mask(4816, 7583, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 7583, 6910, {-1}, true);
  g->Binary(ynn_binary_subtract, 7583, 6910, 6907);
  g->Unary(ynn_unary_exp, 6907, 6908);
  g->Reduce(ynn_reduce_sum, 6908, 6911, {-1}, true);
  g->Binary(ynn_binary_divide, 6183, 6911, 6909);
  g->Binary(ynn_binary_multiply, 6908, 6909, 4817);
  g->Matmul(4817, 2181, 4818, false, false);
}

// Scope: "Layer29 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer29AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(4818, 4820, 1, 2);
  g->SplitDim(4820, 4819, 1, {1,8});
  g->FuseDims(4819, 4821, 2, 2);
  g->Binary(ynn_binary_divide, 4821, 7315, 4822);
  g->Unary(ynn_unary_round, 4822, 4823);
  g->Binary(ynn_binary_max, 4823, 7225, 4824);
  g->Binary(ynn_binary_min, 4824, 7340, 4826);
  g->Binary(ynn_binary_multiply, 4826, 7315, 4827);
  g->Convert(8114, 4828);
  g->Binary(ynn_binary_multiply, 4828, 8115, 4829);
  g->Matmul(4827, 4829, 4830, false, true);
  g->Binary(ynn_binary_divide, 4830, 7284, 4831);
  g->Unary(ynn_unary_round, 4831, 4832);
  g->Binary(ynn_binary_max, 4832, 7225, 4833);
  g->Binary(ynn_binary_min, 4833, 7340, 4834);
  g->Binary(ynn_binary_multiply, 4834, 7284, 4835);
}

// Scope: "Layer29 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer29Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 4774, 4775);
  g->Reduce(ynn_reduce_sum, 4775, 6904, {2}, true);
  g->ShapeProduct(4775, 6903, {2});
  g->Binary(ynn_binary_divide, 6904, 6903, 4776);
  g->Binary(ynn_binary_add, 4776, 7373, 4777);
  g->Binary(ynn_binary_pow, 4777, 7428, 4778);
  g->Binary(ynn_binary_multiply, 4774, 4778, 4779);
  g->Convert(8098, 4781);
  g->Binary(ynn_binary_multiply, 4779, 4781, 4782);
  BuildLayer29AttentionQueryProjection(ctx);
  BuildLayer29AttentionSdpa(ctx);
  BuildLayer29AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 4835, 4838);
  g->Reduce(ynn_reduce_sum, 4838, 6913, {2}, true);
  g->ShapeProduct(4838, 6912, {2});
  g->Binary(ynn_binary_divide, 6913, 6912, 4839);
  g->Binary(ynn_binary_add, 4839, 7373, 4840);
  g->Binary(ynn_binary_pow, 4840, 7428, 4841);
  g->Binary(ynn_binary_multiply, 4835, 4841, 4842);
  g->Convert(8110, 4843);
  g->Binary(ynn_binary_multiply, 4842, 4843, 4844);
  g->Binary(ynn_binary_add, 4774, 4844, 4845);
}

// Scope: "Layer29 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer29Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 4845, 4846);
  g->Reduce(ynn_reduce_sum, 4846, 6915, {2}, true);
  g->ShapeProduct(4846, 6914, {2});
  g->Binary(ynn_binary_divide, 6915, 6914, 4847);
  g->Binary(ynn_binary_add, 4847, 7373, 4849);
  g->Binary(ynn_binary_pow, 4849, 7428, 4850);
  g->Binary(ynn_binary_multiply, 4845, 4850, 4851);
  g->Convert(8113, 4852);
  g->Binary(ynn_binary_multiply, 4851, 4852, 4853);
  g->Binary(ynn_binary_divide, 4853, 7306, 4854);
  g->Unary(ynn_unary_round, 4854, 4855);
  g->Binary(ynn_binary_max, 4855, 7225, 4856);
  g->Binary(ynn_binary_min, 4856, 7340, 4857);
  g->Binary(ynn_binary_multiply, 4857, 7306, 4858);
  g->Convert(8104, 4860);
  g->Binary(ynn_binary_multiply, 4860, 8105, 4861);
  g->Matmul(4858, 4861, 4862, false, true);
  g->Binary(ynn_binary_divide, 4862, 7146, 4863);
  g->Unary(ynn_unary_round, 4863, 4864);
  g->Binary(ynn_binary_max, 4864, 7225, 4865);
  g->Binary(ynn_binary_min, 4865, 7340, 4866);
  g->Binary(ynn_binary_multiply, 4866, 7146, 4867);
  g->Convert(8102, 4869);
  g->Binary(ynn_binary_multiply, 4869, 8103, 4870);
  g->Matmul(4858, 4870, 4871, false, true);
  g->Binary(ynn_binary_divide, 4871, 7146, 4872);
  g->Unary(ynn_unary_round, 4872, 4873);
  g->Binary(ynn_binary_max, 4873, 7225, 4874);
  g->Binary(ynn_binary_min, 4874, 7340, 4875);
  g->Binary(ynn_binary_multiply, 4875, 7146, 4877);
  g->Polynomial(4877, 6918, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6918, 6919);
  g->Binary(ynn_binary_add, 6919, 6183, 6916);
  g->Binary(ynn_binary_multiply, 4877, 6181, 6917);
  g->Binary(ynn_binary_multiply, 6917, 6916, 4878);
  g->Binary(ynn_binary_multiply, 4867, 4878, 4879);
  g->Binary(ynn_binary_divide, 4879, 7226, 4880);
  g->Unary(ynn_unary_round, 4880, 4881);
  g->Binary(ynn_binary_max, 4881, 7225, 4882);
  g->Binary(ynn_binary_min, 4882, 7340, 4883);
  g->Binary(ynn_binary_multiply, 4883, 7226, 4884);
  g->Convert(8100, 4885);
  g->Binary(ynn_binary_multiply, 4885, 8101, 4886);
  g->Matmul(4884, 4886, 4888, false, true);
  g->Binary(ynn_binary_divide, 4888, 7473, 4889);
  g->Unary(ynn_unary_round, 4889, 4890);
  g->Binary(ynn_binary_max, 4890, 7225, 4891);
  g->Binary(ynn_binary_min, 4891, 7340, 4892);
  g->Binary(ynn_binary_multiply, 4892, 7473, 4893);
  g->Unary(ynn_unary_square, 4893, 4894);
  g->Reduce(ynn_reduce_sum, 4894, 6921, {2}, true);
  g->ShapeProduct(4894, 6920, {2});
  g->Binary(ynn_binary_divide, 6921, 6920, 4895);
  g->Binary(ynn_binary_add, 4895, 7373, 4896);
  g->Binary(ynn_binary_pow, 4896, 7428, 4897);
  g->Binary(ynn_binary_multiply, 4893, 4897, 4899);
  g->Convert(8111, 4900);
  g->Binary(ynn_binary_multiply, 4899, 4900, 4901);
  g->Binary(ynn_binary_add, 4845, 4901, 4902);
}

// Scope: "Layer29 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer29PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1031, 4903, {0,0,29,0}, {-1,-1,1,-1});
  g->Reshape(4903, 4904, {1,1,256});
  g->Binary(ynn_binary_add, 4904, 8431, 4905);
  g->Binary(ynn_binary_multiply, 4905, 7155, 4906);
  g->Binary(ynn_binary_divide, 4902, 7478, 4907);
  g->Unary(ynn_unary_round, 4907, 4908);
  g->Binary(ynn_binary_max, 4908, 7225, 4910);
  g->Binary(ynn_binary_min, 4910, 7340, 4911);
  g->Binary(ynn_binary_multiply, 4911, 7478, 4912);
  g->Convert(8106, 4913);
  g->Binary(ynn_binary_multiply, 4913, 8107, 4914);
  g->Matmul(4912, 4914, 4915, false, true);
  g->Binary(ynn_binary_divide, 4915, 7263, 4916);
  g->Unary(ynn_unary_round, 4916, 4917);
  g->Binary(ynn_binary_max, 4917, 7225, 4918);
  g->Binary(ynn_binary_min, 4918, 7340, 4919);
  g->Binary(ynn_binary_multiply, 4919, 7263, 4921);
  g->Polynomial(4921, 6924, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6924, 6925);
  g->Binary(ynn_binary_add, 6925, 6183, 6922);
  g->Binary(ynn_binary_multiply, 4921, 6181, 6923);
  g->Binary(ynn_binary_multiply, 6923, 6922, 4922);
  g->Binary(ynn_binary_multiply, 4922, 4906, 4923);
  g->Binary(ynn_binary_divide, 4923, 7200, 4924);
  g->Unary(ynn_unary_round, 4924, 4925);
  g->Binary(ynn_binary_max, 4925, 7225, 4926);
  g->Binary(ynn_binary_min, 4926, 7340, 4927);
  g->Binary(ynn_binary_multiply, 4927, 7200, 4928);
  g->Convert(8108, 4929);
  g->Binary(ynn_binary_multiply, 4929, 8109, 4930);
  g->Matmul(4928, 4930, 4932, false, true);
  g->Binary(ynn_binary_divide, 4932, 7452, 4933);
  g->Unary(ynn_unary_round, 4933, 4934);
  g->Binary(ynn_binary_max, 4934, 7225, 4935);
  g->Binary(ynn_binary_min, 4935, 7340, 4936);
  g->Binary(ynn_binary_multiply, 4936, 7452, 4937);
  g->Unary(ynn_unary_square, 4937, 4938);
  g->Reduce(ynn_reduce_sum, 4938, 6927, {2}, true);
  g->ShapeProduct(4938, 6926, {2});
  g->Binary(ynn_binary_divide, 6927, 6926, 4939);
  g->Binary(ynn_binary_add, 4939, 7373, 4940);
  g->Binary(ynn_binary_pow, 4940, 7428, 4941);
  g->Binary(ynn_binary_multiply, 4937, 4941, 4943);
  g->Convert(8112, 4944);
  g->Binary(ynn_binary_multiply, 4943, 4944, 4945);
  g->Binary(ynn_binary_add, 4902, 4945, 4946);
  g->Convert(8099, 4947);
  g->Binary(ynn_binary_multiply, 4946, 4947, 4948);
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
  g->Binary(ynn_binary_divide, 4956, 7291, 4957);
  g->Unary(ynn_unary_round, 4957, 4958);
  g->Binary(ynn_binary_max, 4958, 7225, 4959);
  g->Binary(ynn_binary_min, 4959, 7340, 4960);
  g->Binary(ynn_binary_multiply, 4960, 7291, 4961);
  g->Convert(8164, 4962);
  g->Binary(ynn_binary_multiply, 4962, 8165, 4963);
  g->Matmul(4961, 4963, 4965, false, true);
  g->Binary(ynn_binary_divide, 4965, 7172, 4966);
  g->Unary(ynn_unary_round, 4966, 4967);
  g->Binary(ynn_binary_max, 4967, 7225, 4968);
  g->Binary(ynn_binary_min, 4968, 7340, 4969);
  g->Binary(ynn_binary_multiply, 4969, 7172, 4970);
  g->SplitDim(4970, 4971, 2, {8,256});
  g->FuseDims(4971, 4973, 1, 2);
  g->SplitDim(4973, 4972, 1, {8,1});
  g->Unary(ynn_unary_square, 4972, 4974);
  g->Reduce(ynn_reduce_sum, 4974, 6933, {3}, true);
  g->ShapeProduct(4974, 6932, {3});
  g->Binary(ynn_binary_divide, 6933, 6932, 4975);
  g->Binary(ynn_binary_add, 4975, 7373, 4977);
  g->Binary(ynn_binary_pow, 4977, 7428, 4978);
  g->Binary(ynn_binary_multiply, 4972, 4978, 4979);
  g->Convert(8163, 4980);
  g->Binary(ynn_binary_multiply, 4979, 4980, 4981);
  g->Slice(4981, 4982, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(4981, 4983, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 4983, 4984);
  g->Concat({4984,4982}, 4985, 3);
  g->Binary(ynn_binary_multiply, 4981, 2044, 4986);
  g->Binary(ynn_binary_multiply, 4985, 3111, 4988);
  g->Binary(ynn_binary_add, 4986, 4988, 4989);
}

// Scope: "Layer30 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer30AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(4989, 1963, 4990, false, true);
  g->Mask(4990, 7585, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 7585, 6937, {-1}, true);
  g->Binary(ynn_binary_subtract, 7585, 6937, 6934);
  g->Unary(ynn_unary_exp, 6934, 6935);
  g->Reduce(ynn_reduce_sum, 6935, 6938, {-1}, true);
  g->Binary(ynn_binary_divide, 6183, 6938, 6936);
  g->Binary(ynn_binary_multiply, 6935, 6936, 4991);
  g->Matmul(4991, 1965, 4992, false, false);
}

// Scope: "Layer30 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer30AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(4992, 4994, 1, 2);
  g->SplitDim(4994, 4993, 1, {1,8});
  g->FuseDims(4993, 4995, 2, 2);
  g->Binary(ynn_binary_divide, 4995, 7322, 4996);
  g->Unary(ynn_unary_round, 4996, 4997);
  g->Binary(ynn_binary_max, 4997, 7225, 4999);
  g->Binary(ynn_binary_min, 4999, 7340, 5000);
  g->Binary(ynn_binary_multiply, 5000, 7322, 5001);
  g->Convert(8161, 5002);
  g->Binary(ynn_binary_multiply, 5002, 8162, 5003);
  g->Matmul(5001, 5003, 5004, false, true);
  g->Binary(ynn_binary_divide, 5004, 7525, 5005);
  g->Unary(ynn_unary_round, 5005, 5006);
  g->Binary(ynn_binary_max, 5006, 7225, 5007);
  g->Binary(ynn_binary_min, 5007, 7340, 5008);
  g->Binary(ynn_binary_multiply, 5008, 7525, 5010);
}

// Scope: "Layer30 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer30Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 4948, 4949);
  g->Reduce(ynn_reduce_sum, 4949, 6931, {2}, true);
  g->ShapeProduct(4949, 6930, {2});
  g->Binary(ynn_binary_divide, 6931, 6930, 4950);
  g->Binary(ynn_binary_add, 4950, 7373, 4951);
  g->Binary(ynn_binary_pow, 4951, 7428, 4952);
  g->Binary(ynn_binary_multiply, 4948, 4952, 4954);
  g->Convert(8145, 4955);
  g->Binary(ynn_binary_multiply, 4954, 4955, 4956);
  BuildLayer30AttentionQueryProjection(ctx);
  BuildLayer30AttentionSdpa(ctx);
  BuildLayer30AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 5010, 5011);
  g->Reduce(ynn_reduce_sum, 5011, 6940, {2}, true);
  g->ShapeProduct(5011, 6939, {2});
  g->Binary(ynn_binary_divide, 6940, 6939, 5012);
  g->Binary(ynn_binary_add, 5012, 7373, 5013);
  g->Binary(ynn_binary_pow, 5013, 7428, 5014);
  g->Binary(ynn_binary_multiply, 5010, 5014, 5015);
  g->Convert(8157, 5016);
  g->Binary(ynn_binary_multiply, 5015, 5016, 5017);
  g->Binary(ynn_binary_add, 4948, 5017, 5018);
}

// Scope: "Layer30 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer30Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 5018, 5019);
  g->Reduce(ynn_reduce_sum, 5019, 6942, {2}, true);
  g->ShapeProduct(5019, 6941, {2});
  g->Binary(ynn_binary_divide, 6942, 6941, 5021);
  g->Binary(ynn_binary_add, 5021, 7373, 5022);
  g->Binary(ynn_binary_pow, 5022, 7428, 5023);
  g->Binary(ynn_binary_multiply, 5018, 5023, 5024);
  g->Convert(8160, 5025);
  g->Binary(ynn_binary_multiply, 5024, 5025, 5026);
  g->Binary(ynn_binary_divide, 5026, 7342, 5027);
  g->Unary(ynn_unary_round, 5027, 5028);
  g->Binary(ynn_binary_max, 5028, 7225, 5029);
  g->Binary(ynn_binary_min, 5029, 7340, 5030);
  g->Binary(ynn_binary_multiply, 5030, 7342, 5032);
  g->Convert(8151, 5033);
  g->Binary(ynn_binary_multiply, 5033, 8152, 5034);
  g->Matmul(5032, 5034, 5035, false, true);
  g->Binary(ynn_binary_divide, 5035, 7503, 5036);
  g->Unary(ynn_unary_round, 5036, 5037);
  g->Binary(ynn_binary_max, 5037, 7225, 5038);
  g->Binary(ynn_binary_min, 5038, 7340, 5039);
  g->Binary(ynn_binary_multiply, 5039, 7503, 5040);
  g->Convert(8149, 5042);
  g->Binary(ynn_binary_multiply, 5042, 8150, 5043);
  g->Matmul(5032, 5043, 5044, false, true);
  g->Binary(ynn_binary_divide, 5044, 7503, 5045);
  g->Unary(ynn_unary_round, 5045, 5046);
  g->Binary(ynn_binary_max, 5046, 7225, 5047);
  g->Binary(ynn_binary_min, 5047, 7340, 5049);
  g->Binary(ynn_binary_multiply, 5049, 7503, 5050);
  g->Polynomial(5050, 6947, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6947, 6948);
  g->Binary(ynn_binary_add, 6948, 6183, 6945);
  g->Binary(ynn_binary_multiply, 5050, 6181, 6946);
  g->Binary(ynn_binary_multiply, 6946, 6945, 5051);
  g->Binary(ynn_binary_multiply, 5040, 5051, 5052);
  g->Binary(ynn_binary_divide, 5052, 7263, 5053);
  g->Unary(ynn_unary_round, 5053, 5054);
  g->Binary(ynn_binary_max, 5054, 7225, 5055);
  g->Binary(ynn_binary_min, 5055, 7340, 5056);
  g->Binary(ynn_binary_multiply, 5056, 7263, 5057);
  g->Convert(8147, 5058);
  g->Binary(ynn_binary_multiply, 5058, 8148, 5060);
  g->Matmul(5057, 5060, 5061, false, true);
  g->Binary(ynn_binary_divide, 5061, 7382, 5062);
  g->Unary(ynn_unary_round, 5062, 5063);
  g->Binary(ynn_binary_max, 5063, 7225, 5064);
  g->Binary(ynn_binary_min, 5064, 7340, 5065);
  g->Binary(ynn_binary_multiply, 5065, 7382, 5066);
  g->Unary(ynn_unary_square, 5066, 5067);
  g->Reduce(ynn_reduce_sum, 5067, 6950, {2}, true);
  g->ShapeProduct(5067, 6949, {2});
  g->Binary(ynn_binary_divide, 6950, 6949, 5068);
  g->Binary(ynn_binary_add, 5068, 7373, 5069);
  g->Binary(ynn_binary_pow, 5069, 7428, 5071);
  g->Binary(ynn_binary_multiply, 5066, 5071, 5072);
  g->Convert(8158, 5073);
  g->Binary(ynn_binary_multiply, 5072, 5073, 5074);
  g->Binary(ynn_binary_add, 5018, 5074, 5075);
}

// Scope: "Layer30 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer30PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1031, 5076, {0,0,30,0}, {-1,-1,1,-1});
  g->Reshape(5076, 5077, {1,1,256});
  g->Binary(ynn_binary_add, 5077, 8433, 5078);
  g->Binary(ynn_binary_multiply, 5078, 7155, 5079);
  g->Binary(ynn_binary_divide, 5075, 7183, 5080);
  g->Unary(ynn_unary_round, 5080, 5082);
  g->Binary(ynn_binary_max, 5082, 7225, 5083);
  g->Binary(ynn_binary_min, 5083, 7340, 5084);
  g->Binary(ynn_binary_multiply, 5084, 7183, 5085);
  g->Convert(8153, 5086);
  g->Binary(ynn_binary_multiply, 5086, 8154, 5087);
  g->Matmul(5085, 5087, 5088, false, true);
  g->Binary(ynn_binary_divide, 5088, 7532, 5089);
  g->Unary(ynn_unary_round, 5089, 5090);
  g->Binary(ynn_binary_max, 5090, 7225, 5091);
  g->Binary(ynn_binary_min, 5091, 7340, 5093);
  g->Binary(ynn_binary_multiply, 5093, 7532, 5094);
  g->Polynomial(5094, 6953, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6953, 6954);
  g->Binary(ynn_binary_add, 6954, 6183, 6951);
  g->Binary(ynn_binary_multiply, 5094, 6181, 6952);
  g->Binary(ynn_binary_multiply, 6952, 6951, 5095);
  g->Binary(ynn_binary_multiply, 5095, 5079, 5096);
  g->Binary(ynn_binary_divide, 5096, 7437, 5097);
  g->Unary(ynn_unary_round, 5097, 5098);
  g->Binary(ynn_binary_max, 5098, 7225, 5099);
  g->Binary(ynn_binary_min, 5099, 7340, 5100);
  g->Binary(ynn_binary_multiply, 5100, 7437, 5101);
  g->Convert(8155, 5102);
  g->Binary(ynn_binary_multiply, 5102, 8156, 5104);
  g->Matmul(5101, 5104, 5105, false, true);
  g->Binary(ynn_binary_divide, 5105, 7185, 5106);
  g->Unary(ynn_unary_round, 5106, 5107);
  g->Binary(ynn_binary_max, 5107, 7225, 5108);
  g->Binary(ynn_binary_min, 5108, 7340, 5109);
  g->Binary(ynn_binary_multiply, 5109, 7185, 5110);
  g->Unary(ynn_unary_square, 5110, 5111);
  g->Reduce(ynn_reduce_sum, 5111, 6956, {2}, true);
  g->ShapeProduct(5111, 6955, {2});
  g->Binary(ynn_binary_divide, 6956, 6955, 5112);
  g->Binary(ynn_binary_add, 5112, 7373, 5113);
  g->Binary(ynn_binary_pow, 5113, 7428, 5115);
  g->Binary(ynn_binary_multiply, 5110, 5115, 5116);
  g->Convert(8159, 5117);
  g->Binary(ynn_binary_multiply, 5116, 5117, 5118);
  g->Binary(ynn_binary_add, 5075, 5118, 5119);
  g->Convert(8146, 5120);
  g->Binary(ynn_binary_multiply, 5119, 5120, 5121);
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
  g->Binary(ynn_binary_divide, 5129, 7418, 5130);
  g->Unary(ynn_unary_round, 5130, 5131);
  g->Binary(ynn_binary_max, 5131, 7225, 5132);
  g->Binary(ynn_binary_min, 5132, 7340, 5133);
  g->Binary(ynn_binary_multiply, 5133, 7418, 5134);
  g->Convert(8185, 5135);
  g->Binary(ynn_binary_multiply, 5135, 8186, 5137);
  g->Matmul(5134, 5137, 5138, false, true);
  g->Binary(ynn_binary_divide, 5138, 7288, 5139);
  g->Unary(ynn_unary_round, 5139, 5140);
  g->Binary(ynn_binary_max, 5140, 7225, 5141);
  g->Binary(ynn_binary_min, 5141, 7340, 5142);
  g->Binary(ynn_binary_multiply, 5142, 7288, 5143);
  g->SplitDim(5143, 5144, 2, {8,256});
  g->FuseDims(5144, 5146, 1, 2);
  g->SplitDim(5146, 5145, 1, {8,1});
  g->Unary(ynn_unary_square, 5145, 5147);
  g->Reduce(ynn_reduce_sum, 5147, 6960, {3}, true);
  g->ShapeProduct(5147, 6959, {3});
  g->Binary(ynn_binary_divide, 6960, 6959, 5149);
  g->Binary(ynn_binary_add, 5149, 7373, 5150);
  g->Binary(ynn_binary_pow, 5150, 7428, 5151);
  g->Binary(ynn_binary_multiply, 5145, 5151, 5152);
  g->Convert(8184, 5153);
  g->Binary(ynn_binary_multiply, 5152, 5153, 5154);
  g->Slice(5154, 5155, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(5154, 5156, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 5156, 5157);
  g->Concat({5157,5155}, 5158, 3);
  g->Binary(ynn_binary_multiply, 5154, 2044, 5160);
  g->Binary(ynn_binary_multiply, 5158, 3111, 5161);
  g->Binary(ynn_binary_add, 5160, 5161, 5162);
}

// Scope: "Layer31 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer31AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(5162, 1963, 5163, false, true);
  g->Mask(5163, 7586, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 7586, 6964, {-1}, true);
  g->Binary(ynn_binary_subtract, 7586, 6964, 6961);
  g->Unary(ynn_unary_exp, 6961, 6962);
  g->Reduce(ynn_reduce_sum, 6962, 6965, {-1}, true);
  g->Binary(ynn_binary_divide, 6183, 6965, 6963);
  g->Binary(ynn_binary_multiply, 6962, 6963, 5164);
  g->Matmul(5164, 1965, 5165, false, false);
}

// Scope: "Layer31 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer31AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(5165, 5167, 1, 2);
  g->SplitDim(5167, 5166, 1, {1,8});
  g->FuseDims(5166, 5168, 2, 2);
  g->Binary(ynn_binary_divide, 5168, 7322, 5169);
  g->Unary(ynn_unary_round, 5169, 5171);
  g->Binary(ynn_binary_max, 5171, 7225, 5172);
  g->Binary(ynn_binary_min, 5172, 7340, 5173);
  g->Binary(ynn_binary_multiply, 5173, 7322, 5174);
  g->Convert(8182, 5175);
  g->Binary(ynn_binary_multiply, 5175, 8183, 5176);
  g->Matmul(5174, 5176, 5177, false, true);
  g->Binary(ynn_binary_divide, 5177, 7384, 5178);
  g->Unary(ynn_unary_round, 5178, 5179);
  g->Binary(ynn_binary_max, 5179, 7225, 5180);
  g->Binary(ynn_binary_min, 5180, 7340, 5182);
  g->Binary(ynn_binary_multiply, 5182, 7384, 5183);
}

// Scope: "Layer31 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer31Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 5121, 5122);
  g->Reduce(ynn_reduce_sum, 5122, 6958, {2}, true);
  g->ShapeProduct(5122, 6957, {2});
  g->Binary(ynn_binary_divide, 6958, 6957, 5123);
  g->Binary(ynn_binary_add, 5123, 7373, 5124);
  g->Binary(ynn_binary_pow, 5124, 7428, 5126);
  g->Binary(ynn_binary_multiply, 5121, 5126, 5127);
  g->Convert(8166, 5128);
  g->Binary(ynn_binary_multiply, 5127, 5128, 5129);
  BuildLayer31AttentionQueryProjection(ctx);
  BuildLayer31AttentionSdpa(ctx);
  BuildLayer31AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 5183, 5184);
  g->Reduce(ynn_reduce_sum, 5184, 6967, {2}, true);
  g->ShapeProduct(5184, 6966, {2});
  g->Binary(ynn_binary_divide, 6967, 6966, 5185);
  g->Binary(ynn_binary_add, 5185, 7373, 5186);
  g->Binary(ynn_binary_pow, 5186, 7428, 5187);
  g->Binary(ynn_binary_multiply, 5183, 5187, 5188);
  g->Convert(8178, 5189);
  g->Binary(ynn_binary_multiply, 5188, 5189, 5190);
  g->Binary(ynn_binary_add, 5121, 5190, 5191);
}

// Scope: "Layer31 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer31Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 5191, 5193);
  g->Reduce(ynn_reduce_sum, 5193, 6969, {2}, true);
  g->ShapeProduct(5193, 6968, {2});
  g->Binary(ynn_binary_divide, 6969, 6968, 5194);
  g->Binary(ynn_binary_add, 5194, 7373, 5195);
  g->Binary(ynn_binary_pow, 5195, 7428, 5196);
  g->Binary(ynn_binary_multiply, 5191, 5196, 5197);
  g->Convert(8181, 5198);
  g->Binary(ynn_binary_multiply, 5197, 5198, 5199);
  g->Binary(ynn_binary_divide, 5199, 7287, 5200);
  g->Unary(ynn_unary_round, 5200, 5201);
  g->Binary(ynn_binary_max, 5201, 7225, 5202);
  g->Binary(ynn_binary_min, 5202, 7340, 5204);
  g->Binary(ynn_binary_multiply, 5204, 7287, 5205);
  g->Convert(8172, 5206);
  g->Binary(ynn_binary_multiply, 5206, 8173, 5207);
  g->Matmul(5205, 5207, 5208, false, true);
  g->Binary(ynn_binary_divide, 5208, 7557, 5209);
  g->Unary(ynn_unary_round, 5209, 5210);
  g->Binary(ynn_binary_max, 5210, 7225, 5211);
  g->Binary(ynn_binary_min, 5211, 7340, 5212);
  g->Binary(ynn_binary_multiply, 5212, 7557, 5213);
  g->Convert(8170, 5215);
  g->Binary(ynn_binary_multiply, 5215, 8171, 5216);
  g->Matmul(5205, 5216, 5217, false, true);
  g->Binary(ynn_binary_divide, 5217, 7557, 5218);
  g->Unary(ynn_unary_round, 5218, 5219);
  g->Binary(ynn_binary_max, 5219, 7225, 5221);
  g->Binary(ynn_binary_min, 5221, 7340, 5222);
  g->Binary(ynn_binary_multiply, 5222, 7557, 5223);
  g->Polynomial(5223, 6972, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6972, 6973);
  g->Binary(ynn_binary_add, 6973, 6183, 6970);
  g->Binary(ynn_binary_multiply, 5223, 6181, 6971);
  g->Binary(ynn_binary_multiply, 6971, 6970, 5224);
  g->Binary(ynn_binary_multiply, 5213, 5224, 5225);
  g->Binary(ynn_binary_divide, 5225, 7370, 5226);
  g->Unary(ynn_unary_round, 5226, 5227);
  g->Binary(ynn_binary_max, 5227, 7225, 5228);
  g->Binary(ynn_binary_min, 5228, 7340, 5229);
  g->Binary(ynn_binary_multiply, 5229, 7370, 5230);
  g->Convert(8168, 5231);
  g->Binary(ynn_binary_multiply, 5231, 8169, 5232);
  g->Matmul(5230, 5232, 5233, false, true);
  g->Binary(ynn_binary_divide, 5233, 7283, 5234);
  g->Unary(ynn_unary_round, 5234, 5235);
  g->Binary(ynn_binary_max, 5235, 7225, 5236);
  g->Binary(ynn_binary_min, 5236, 7340, 5237);
  g->Binary(ynn_binary_multiply, 5237, 7283, 5238);
  g->Unary(ynn_unary_square, 5238, 5239);
  g->Reduce(ynn_reduce_sum, 5239, 6975, {2}, true);
  g->ShapeProduct(5239, 6974, {2});
  g->Binary(ynn_binary_divide, 6975, 6974, 5240);
  g->Binary(ynn_binary_add, 5240, 7373, 5241);
  g->Binary(ynn_binary_pow, 5241, 7428, 5242);
  g->Binary(ynn_binary_multiply, 5238, 5242, 5243);
  g->Convert(8179, 5244);
  g->Binary(ynn_binary_multiply, 5243, 5244, 5245);
  g->Binary(ynn_binary_add, 5191, 5245, 5246);
}

// Scope: "Layer31 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer31PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1031, 5247, {0,0,31,0}, {-1,-1,1,-1});
  g->Reshape(5247, 5248, {1,1,256});
  g->Binary(ynn_binary_add, 5248, 8434, 5249);
  g->Binary(ynn_binary_multiply, 5249, 7155, 5250);
  g->Binary(ynn_binary_divide, 5246, 7273, 5251);
  g->Unary(ynn_unary_round, 5251, 5252);
  g->Binary(ynn_binary_max, 5252, 7225, 5253);
  g->Binary(ynn_binary_min, 5253, 7340, 5254);
  g->Binary(ynn_binary_multiply, 5254, 7273, 5255);
  g->Convert(8174, 5256);
  g->Binary(ynn_binary_multiply, 5256, 8175, 5257);
  g->Matmul(5255, 5257, 5258, false, true);
  g->Binary(ynn_binary_divide, 5258, 7509, 5259);
  g->Unary(ynn_unary_round, 5259, 5260);
  g->Binary(ynn_binary_max, 5260, 7225, 5262);
  g->Binary(ynn_binary_min, 5262, 7340, 5263);
  g->Binary(ynn_binary_multiply, 5263, 7509, 5264);
  g->Polynomial(5264, 6978, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6978, 6979);
  g->Binary(ynn_binary_add, 6979, 6183, 6976);
  g->Binary(ynn_binary_multiply, 5264, 6181, 6977);
  g->Binary(ynn_binary_multiply, 6977, 6976, 5265);
  g->Binary(ynn_binary_multiply, 5265, 5250, 5266);
  g->Binary(ynn_binary_divide, 5266, 7391, 5267);
  g->Unary(ynn_unary_round, 5267, 5268);
  g->Binary(ynn_binary_max, 5268, 7225, 5269);
  g->Binary(ynn_binary_min, 5269, 7340, 5270);
  g->Binary(ynn_binary_multiply, 5270, 7391, 5271);
  g->Convert(8176, 5272);
  g->Binary(ynn_binary_multiply, 5272, 8177, 5273);
  g->Matmul(5271, 5273, 5274, false, true);
  g->Binary(ynn_binary_divide, 5274, 7268, 5275);
  g->Unary(ynn_unary_round, 5275, 5276);
  g->Binary(ynn_binary_max, 5276, 7225, 5277);
  g->Binary(ynn_binary_min, 5277, 7340, 5278);
  g->Binary(ynn_binary_multiply, 5278, 7268, 5279);
  g->Unary(ynn_unary_square, 5279, 5280);
  g->Reduce(ynn_reduce_sum, 5280, 6981, {2}, true);
  g->ShapeProduct(5280, 6980, {2});
  g->Binary(ynn_binary_divide, 6981, 6980, 5281);
  g->Binary(ynn_binary_add, 5281, 7373, 5283);
  g->Binary(ynn_binary_pow, 5283, 7428, 5284);
  g->Binary(ynn_binary_multiply, 5279, 5284, 5285);
  g->Convert(8180, 5286);
  g->Binary(ynn_binary_multiply, 5285, 5286, 5287);
  g->Binary(ynn_binary_add, 5246, 5287, 5288);
  g->Convert(8167, 5289);
  g->Binary(ynn_binary_multiply, 5288, 5289, 5290);
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
  g->Binary(ynn_binary_divide, 5298, 7441, 5299);
  g->Unary(ynn_unary_round, 5299, 5300);
  g->Binary(ynn_binary_max, 5300, 7225, 5301);
  g->Binary(ynn_binary_min, 5301, 7340, 5302);
  g->Binary(ynn_binary_multiply, 5302, 7441, 5303);
  g->Convert(8206, 5305);
  g->Binary(ynn_binary_multiply, 5305, 8207, 5306);
  g->Matmul(5303, 5306, 5307, false, true);
  g->Binary(ynn_binary_divide, 5307, 7179, 5308);
  g->Unary(ynn_unary_round, 5308, 5309);
  g->Binary(ynn_binary_max, 5309, 7225, 5310);
  g->Binary(ynn_binary_min, 5310, 7340, 5311);
  g->Binary(ynn_binary_multiply, 5311, 7179, 5312);
  g->SplitDim(5312, 5313, 2, {8,256});
  g->FuseDims(5313, 5315, 1, 2);
  g->SplitDim(5315, 5314, 1, {8,1});
  g->Unary(ynn_unary_square, 5314, 5317);
  g->Reduce(ynn_reduce_sum, 5317, 6985, {3}, true);
  g->ShapeProduct(5317, 6984, {3});
  g->Binary(ynn_binary_divide, 6985, 6984, 5318);
  g->Binary(ynn_binary_add, 5318, 7373, 5319);
  g->Binary(ynn_binary_pow, 5319, 7428, 5320);
  g->Binary(ynn_binary_multiply, 5314, 5320, 5321);
  g->Convert(8205, 5322);
  g->Binary(ynn_binary_multiply, 5321, 5322, 5323);
  g->Slice(5323, 5324, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(5323, 5325, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 5325, 5326);
  g->Concat({5326,5324}, 5328, 3);
  g->Binary(ynn_binary_multiply, 5323, 2044, 5329);
  g->Binary(ynn_binary_multiply, 5328, 3111, 5330);
  g->Binary(ynn_binary_add, 5329, 5330, 5331);
}

// Scope: "Layer32 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer32AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(5331, 1963, 5332, false, true);
  g->Mask(5332, 7587, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 7587, 6989, {-1}, true);
  g->Binary(ynn_binary_subtract, 7587, 6989, 6986);
  g->Unary(ynn_unary_exp, 6986, 6987);
  g->Reduce(ynn_reduce_sum, 6987, 6990, {-1}, true);
  g->Binary(ynn_binary_divide, 6183, 6990, 6988);
  g->Binary(ynn_binary_multiply, 6987, 6988, 5333);
  g->Matmul(5333, 1965, 5334, false, false);
}

// Scope: "Layer32 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer32AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(5334, 5336, 1, 2);
  g->SplitDim(5336, 5335, 1, {1,8});
  g->FuseDims(5335, 5337, 2, 2);
  g->Binary(ynn_binary_divide, 5337, 7238, 5339);
  g->Unary(ynn_unary_round, 5339, 5340);
  g->Binary(ynn_binary_max, 5340, 7225, 5341);
  g->Binary(ynn_binary_min, 5341, 7340, 5342);
  g->Binary(ynn_binary_multiply, 5342, 7238, 5343);
  g->Convert(8203, 5344);
  g->Binary(ynn_binary_multiply, 5344, 8204, 5345);
  g->Matmul(5343, 5345, 5346, false, true);
  g->Binary(ynn_binary_divide, 5346, 7502, 5347);
  g->Unary(ynn_unary_round, 5347, 5348);
  g->Binary(ynn_binary_max, 5348, 7225, 5350);
  g->Binary(ynn_binary_min, 5350, 7340, 5351);
  g->Binary(ynn_binary_multiply, 5351, 7502, 5352);
}

// Scope: "Layer32 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer32Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 5290, 5291);
  g->Reduce(ynn_reduce_sum, 5291, 6983, {2}, true);
  g->ShapeProduct(5291, 6982, {2});
  g->Binary(ynn_binary_divide, 6983, 6982, 5292);
  g->Binary(ynn_binary_add, 5292, 7373, 5294);
  g->Binary(ynn_binary_pow, 5294, 7428, 5295);
  g->Binary(ynn_binary_multiply, 5290, 5295, 5296);
  g->Convert(8187, 5297);
  g->Binary(ynn_binary_multiply, 5296, 5297, 5298);
  BuildLayer32AttentionQueryProjection(ctx);
  BuildLayer32AttentionSdpa(ctx);
  BuildLayer32AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 5352, 5353);
  g->Reduce(ynn_reduce_sum, 5353, 6992, {2}, true);
  g->ShapeProduct(5353, 6991, {2});
  g->Binary(ynn_binary_divide, 6992, 6991, 5354);
  g->Binary(ynn_binary_add, 5354, 7373, 5355);
  g->Binary(ynn_binary_pow, 5355, 7428, 5356);
  g->Binary(ynn_binary_multiply, 5352, 5356, 5357);
  g->Convert(8199, 5358);
  g->Binary(ynn_binary_multiply, 5357, 5358, 5359);
  g->Binary(ynn_binary_add, 5290, 5359, 5361);
}

// Scope: "Layer32 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer32Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 5361, 5362);
  g->Reduce(ynn_reduce_sum, 5362, 6994, {2}, true);
  g->ShapeProduct(5362, 6993, {2});
  g->Binary(ynn_binary_divide, 6994, 6993, 5363);
  g->Binary(ynn_binary_add, 5363, 7373, 5364);
  g->Binary(ynn_binary_pow, 5364, 7428, 5365);
  g->Binary(ynn_binary_multiply, 5361, 5365, 5366);
  g->Convert(8202, 5367);
  g->Binary(ynn_binary_multiply, 5366, 5367, 5368);
  g->Binary(ynn_binary_divide, 5368, 7219, 5369);
  g->Unary(ynn_unary_round, 5369, 5370);
  g->Binary(ynn_binary_max, 5370, 7225, 5372);
  g->Binary(ynn_binary_min, 5372, 7340, 5373);
  g->Binary(ynn_binary_multiply, 5373, 7219, 5374);
  g->Convert(8193, 5375);
  g->Binary(ynn_binary_multiply, 5375, 8194, 5376);
  g->Matmul(5374, 5376, 5377, false, true);
  g->Binary(ynn_binary_divide, 5377, 7364, 5378);
  g->Unary(ynn_unary_round, 5378, 5379);
  g->Binary(ynn_binary_max, 5379, 7225, 5380);
  g->Binary(ynn_binary_min, 5380, 7340, 5381);
  g->Binary(ynn_binary_multiply, 5381, 7364, 5383);
  g->Convert(8191, 5384);
  g->Binary(ynn_binary_multiply, 5384, 8192, 5385);
  g->Matmul(5374, 5385, 5386, false, true);
  g->Binary(ynn_binary_divide, 5386, 7364, 5387);
  g->Unary(ynn_unary_round, 5387, 5389);
  g->Binary(ynn_binary_max, 5389, 7225, 5390);
  g->Binary(ynn_binary_min, 5390, 7340, 5391);
  g->Binary(ynn_binary_multiply, 5391, 7364, 5392);
  g->Polynomial(5392, 7001, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7001, 7002);
  g->Binary(ynn_binary_add, 7002, 6183, 6999);
  g->Binary(ynn_binary_multiply, 5392, 6181, 7000);
  g->Binary(ynn_binary_multiply, 7000, 6999, 5393);
  g->Binary(ynn_binary_multiply, 5383, 5393, 5394);
  g->Binary(ynn_binary_divide, 5394, 7234, 5395);
  g->Unary(ynn_unary_round, 5395, 5396);
  g->Binary(ynn_binary_max, 5396, 7225, 5397);
  g->Binary(ynn_binary_min, 5397, 7340, 5398);
  g->Binary(ynn_binary_multiply, 5398, 7234, 5400);
  g->Convert(8189, 5401);
  g->Binary(ynn_binary_multiply, 5401, 8190, 5402);
  g->Matmul(5400, 5402, 5403, false, true);
  g->Binary(ynn_binary_divide, 5403, 7271, 5404);
  g->Unary(ynn_unary_round, 5404, 5405);
  g->Binary(ynn_binary_max, 5405, 7225, 5406);
  g->Binary(ynn_binary_min, 5406, 7340, 5407);
  g->Binary(ynn_binary_multiply, 5407, 7271, 5408);
  g->Unary(ynn_unary_square, 5408, 5409);
  g->Reduce(ynn_reduce_sum, 5409, 7004, {2}, true);
  g->ShapeProduct(5409, 7003, {2});
  g->Binary(ynn_binary_divide, 7004, 7003, 5411);
  g->Binary(ynn_binary_add, 5411, 7373, 5412);
  g->Binary(ynn_binary_pow, 5412, 7428, 5413);
  g->Binary(ynn_binary_multiply, 5408, 5413, 5414);
  g->Convert(8200, 5415);
  g->Binary(ynn_binary_multiply, 5414, 5415, 5416);
  g->Binary(ynn_binary_add, 5361, 5416, 5417);
}

// Scope: "Layer32 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer32PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1031, 5418, {0,0,32,0}, {-1,-1,1,-1});
  g->Reshape(5418, 5419, {1,1,256});
  g->Binary(ynn_binary_add, 5419, 8435, 5420);
  g->Binary(ynn_binary_multiply, 5420, 7155, 5422);
  g->Binary(ynn_binary_divide, 5417, 7405, 5423);
  g->Unary(ynn_unary_round, 5423, 5424);
  g->Binary(ynn_binary_max, 5424, 7225, 5425);
  g->Binary(ynn_binary_min, 5425, 7340, 5426);
  g->Binary(ynn_binary_multiply, 5426, 7405, 5427);
  g->Convert(8195, 5428);
  g->Binary(ynn_binary_multiply, 5428, 8196, 5429);
  g->Matmul(5427, 5429, 5430, false, true);
  g->Binary(ynn_binary_divide, 5430, 7321, 5431);
  g->Unary(ynn_unary_round, 5431, 5433);
  g->Binary(ynn_binary_max, 5433, 7225, 5434);
  g->Binary(ynn_binary_min, 5434, 7340, 5435);
  g->Binary(ynn_binary_multiply, 5435, 7321, 5436);
  g->Polynomial(5436, 7007, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7007, 7008);
  g->Binary(ynn_binary_add, 7008, 6183, 7005);
  g->Binary(ynn_binary_multiply, 5436, 6181, 7006);
  g->Binary(ynn_binary_multiply, 7006, 7005, 5437);
  g->Binary(ynn_binary_multiply, 5437, 5422, 5438);
  g->Binary(ynn_binary_divide, 5438, 7437, 5439);
  g->Unary(ynn_unary_round, 5439, 5440);
  g->Binary(ynn_binary_max, 5440, 7225, 5441);
  g->Binary(ynn_binary_min, 5441, 7340, 5442);
  g->Binary(ynn_binary_multiply, 5442, 7437, 5444);
  g->Convert(8197, 5445);
  g->Binary(ynn_binary_multiply, 5445, 8198, 5446);
  g->Matmul(5444, 5446, 5447, false, true);
  g->Binary(ynn_binary_divide, 5447, 7154, 5448);
  g->Unary(ynn_unary_round, 5448, 5449);
  g->Binary(ynn_binary_max, 5449, 7225, 5450);
  g->Binary(ynn_binary_min, 5450, 7340, 5451);
  g->Binary(ynn_binary_multiply, 5451, 7154, 5452);
  g->Unary(ynn_unary_square, 5452, 5453);
  g->Reduce(ynn_reduce_sum, 5453, 7010, {2}, true);
  g->ShapeProduct(5453, 7009, {2});
  g->Binary(ynn_binary_divide, 7010, 7009, 5455);
  g->Binary(ynn_binary_add, 5455, 7373, 5456);
  g->Binary(ynn_binary_pow, 5456, 7428, 5457);
  g->Binary(ynn_binary_multiply, 5452, 5457, 5458);
  g->Convert(8201, 5459);
  g->Binary(ynn_binary_multiply, 5458, 5459, 5460);
  g->Binary(ynn_binary_add, 5417, 5460, 5461);
  g->Convert(8188, 5462);
  g->Binary(ynn_binary_multiply, 5461, 5462, 5463);
}

// Scope: "Layer32"
LAB_YNN_BUILDER_NOINLINE void BuildLayer32(Context& ctx) {
  BuildLayer32Attention(ctx);
  BuildLayer32Mlp(ctx);
  BuildLayer32PerLayerEmbedding(ctx);
}

}  // namespace BuildGemma4DecodeSource
