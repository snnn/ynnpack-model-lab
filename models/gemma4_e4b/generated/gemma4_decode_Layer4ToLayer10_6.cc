// Generated YNNPACK builder; do not edit.
#include "gemma4_decode_builder.h"

namespace BuildGemma4DecodeSource {

// Scope: "Layer4 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(4493, 4494, 0.20282812416553497, 0);
  g->Transpose(9281, 6980, {1,0});
  g->Binary(ynn_binary_multiply, 6977, 6979, 6975);
  g->Dot(4494, 6980, YNN_INVALID_VALUE_ID, 6974, 1);
  g->DequantizeTensor(6974, YNN_INVALID_VALUE_ID, 6975, 6976);
  g->QuantizeTensor(6976, 8595, 6978, 4495);
  g->Dequantize(4495, 4496, 0.16338583827018738, 0);
  g->SplitDim(4496, 4497, 2, {2,256});
  g->Transpose(4497, 4498, {0,2,1,3});
  g->Unary(ynn_unary_square, 4498, 4499);
  g->Reduce(ynn_reduce_sum, 4499, 8472, {3}, true);
  g->ShapeProduct(4499, 8471, {3});
  g->Binary(ynn_binary_divide, 8472, 8471, 4500);
  g->Binary(ynn_binary_add, 4500, 8647, 4502);
  g->Unary(ynn_unary_rsqrt, 4502, 4503);
  g->Binary(ynn_binary_multiply, 4498, 4503, 4504);
  g->Binary(ynn_binary_multiply, 4504, 9280, 4505);
  g->Slice(4505, 4506, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(4505, 4507, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 4507, 4508);
  g->Concat({4508,4506}, 4509, 3);
  g->Binary(ynn_binary_multiply, 4505, 3141, 4510);
  g->Binary(ynn_binary_multiply, 4509, 4217, 4511);
  g->Binary(ynn_binary_add, 4510, 4511, 4513);
  g->Transpose(9285, 6985, {1,0});
  g->Binary(ynn_binary_multiply, 6977, 6984, 6982);
  g->Dot(4494, 6985, YNN_INVALID_VALUE_ID, 6981, 1);
  g->DequantizeTensor(6981, YNN_INVALID_VALUE_ID, 6982, 6983);
  g->QuantizeTensor(6983, 8595, 6978, 4514);
  g->Dequantize(4514, 4515, 0.16338583827018738, 0);
  g->SplitDim(4515, 4516, 2, {2,256});
  g->Transpose(4516, 4517, {0,2,1,3});
  g->Unary(ynn_unary_square, 4517, 4518);
  g->Reduce(ynn_reduce_sum, 4518, 8474, {3}, true);
  g->ShapeProduct(4518, 8473, {3});
  g->Binary(ynn_binary_divide, 8474, 8473, 4519);
  g->Binary(ynn_binary_add, 4519, 8647, 4520);
  g->Unary(ynn_unary_rsqrt, 4520, 4521);
  g->Binary(ynn_binary_multiply, 4517, 4521, 4524);
}

// Scope: "Layer4 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(4513, 4525, 0.00596147496253252, 0);
  g->Append(8614, 4525, 9463, 2, s2, slinky::expr(int64_t{1}));
  g->View(9463, 9511, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(4524, 4526, 0.047244105488061905, 0);
  g->Append(8638, 4526, 9487, 2, s2, slinky::expr(int64_t{1}));
  g->View(9487, 9535, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer4 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(9284, 6991, {1,0});
  g->Binary(ynn_binary_multiply, 6977, 6990, 6987);
  g->Dot(4494, 6991, YNN_INVALID_VALUE_ID, 6986, 1);
  g->DequantizeTensor(6986, YNN_INVALID_VALUE_ID, 6987, 6988);
  g->QuantizeTensor(6988, 8595, 6989, 4527);
  g->Dequantize(4527, 4528, 0.16240158677101135, 0);
  g->SplitDim(4528, 4530, 2, {8,256});
  g->Transpose(4530, 4531, {0,2,1,3});
  g->Unary(ynn_unary_square, 4531, 4532);
  g->Reduce(ynn_reduce_sum, 4532, 8478, {3}, true);
  g->ShapeProduct(4532, 8477, {3});
  g->Binary(ynn_binary_divide, 8478, 8477, 4533);
  g->Binary(ynn_binary_add, 4533, 8647, 4534);
  g->Unary(ynn_unary_rsqrt, 4534, 4535);
  g->Binary(ynn_binary_multiply, 4531, 4535, 4536);
  g->Binary(ynn_binary_multiply, 4536, 9283, 4537);
  g->Slice(4537, 4538, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(4537, 4539, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 4539, 4541);
  g->Concat({4541,4538}, 4542, 3);
  g->Binary(ynn_binary_multiply, 4537, 3141, 4543);
  g->Binary(ynn_binary_multiply, 4542, 4217, 4544);
  g->Binary(ynn_binary_add, 4543, 4544, 4545);
}

// Scope: "Layer4 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9511, 4546, 0.00596147496253252, 0);
  g->Dequantize(9535, 4547, 0.047244105488061905, 0);
  g->Slice(4545, 4548, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(4546, 4549, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(4547, 4550, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(4548, 4549, 4552, false, true);
  g->Mask(4552, 8726, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8726, 8482, {-1}, true);
  g->Binary(ynn_binary_subtract, 8726, 8482, 8479);
  g->Unary(ynn_unary_exp, 8479, 8480);
  g->Reduce(ynn_reduce_sum, 8480, 8483, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 8483, 8481);
  g->Binary(ynn_binary_multiply, 8480, 8481, 4553);
  g->Matmul(4553, 4550, 4554, false, false);
  g->Slice(4545, 4555, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(4546, 4556, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(4547, 4557, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(4555, 4556, 4558, false, true);
  g->Mask(4558, 8727, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8727, 8487, {-1}, true);
  g->Binary(ynn_binary_subtract, 8727, 8487, 8484);
  g->Unary(ynn_unary_exp, 8484, 8485);
  g->Reduce(ynn_reduce_sum, 8485, 8488, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 8488, 8486);
  g->Binary(ynn_binary_multiply, 8485, 8486, 4559);
  g->Matmul(4559, 4557, 4561, false, false);
  g->Concat({4554,4561}, 4562, 1);
}

// Scope: "Layer4 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(4562, 4563, {0,2,1,3});
  g->FuseDims(4563, 4564, 2, 2);
  g->Quantize(4564, 4565, 0.024114182218909264, 0);
  g->Transpose(9282, 6998, {1,0});
  g->Binary(ynn_binary_multiply, 6995, 6997, 6993);
  g->Dot(4565, 6998, YNN_INVALID_VALUE_ID, 6992, 1);
  g->DequantizeTensor(6992, YNN_INVALID_VALUE_ID, 6993, 6994);
  g->QuantizeTensor(6994, 8595, 6996, 4566);
  g->Dequantize(4566, 4567, 0.05563074350357056, 0);
}

// Scope: "Layer4 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 4486, 4487);
  g->Reduce(ynn_reduce_sum, 4487, 8470, {2}, true);
  g->ShapeProduct(4487, 8469, {2});
  g->Binary(ynn_binary_divide, 8470, 8469, 4488);
  g->Binary(ynn_binary_add, 4488, 8647, 4489);
  g->Unary(ynn_unary_rsqrt, 4489, 4491);
  g->Binary(ynn_binary_multiply, 4486, 4491, 4492);
  g->Binary(ynn_binary_multiply, 4492, 9269, 4493);
  BuildLayer4AttentionKvProjection(ctx);
  BuildLayer4AttentionCacheUpdate(ctx);
  BuildLayer4AttentionQueryProjection(ctx);
  BuildLayer4AttentionSdpa(ctx);
  BuildLayer4AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 4567, 4568);
  g->Reduce(ynn_reduce_sum, 4568, 8490, {2}, true);
  g->ShapeProduct(4568, 8489, {2});
  g->Binary(ynn_binary_divide, 8490, 8489, 4569);
  g->Binary(ynn_binary_add, 4569, 8647, 4570);
  g->Unary(ynn_unary_rsqrt, 4570, 4572);
  g->Binary(ynn_binary_multiply, 4567, 4572, 4573);
  g->Binary(ynn_binary_multiply, 4573, 9276, 4574);
  g->Binary(ynn_binary_add, 4574, 4486, 4575);
}

// Scope: "Layer4 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 4575, 4576);
  g->Reduce(ynn_reduce_sum, 4576, 8492, {2}, true);
  g->ShapeProduct(4576, 8491, {2});
  g->Binary(ynn_binary_divide, 8492, 8491, 4577);
  g->Binary(ynn_binary_add, 4577, 8647, 4578);
  g->Unary(ynn_unary_rsqrt, 4578, 4579);
  g->Binary(ynn_binary_multiply, 4575, 4579, 4580);
  g->Binary(ynn_binary_multiply, 4580, 9279, 4581);
  g->Quantize(4581, 4583, 0.04694453626871109, 0);
  g->Transpose(9273, 7004, {1,0});
  g->Binary(ynn_binary_multiply, 7002, 7003, 7000);
  g->Dot(4583, 7004, YNN_INVALID_VALUE_ID, 6999, 1);
  g->DequantizeTensor(6999, YNN_INVALID_VALUE_ID, 7000, 7001);
  g->QuantizeTensor(7001, 8595, 5218, 4584);
  g->Dequantize(4584, 4585, 0.0664370134472847, 0);
  g->Transpose(9272, 7009, {1,0});
  g->Binary(ynn_binary_multiply, 7002, 7008, 7006);
  g->Dot(4583, 7009, YNN_INVALID_VALUE_ID, 7005, 1);
  g->DequantizeTensor(7005, YNN_INVALID_VALUE_ID, 7006, 7007);
  g->QuantizeTensor(7007, 8595, 5218, 4586);
  g->Dequantize(4586, 4587, 0.0664370134472847, 0);
  g->Polynomial(4587, 8495, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8495, 8496);
  g->Binary(ynn_binary_add, 8496, 7161, 8493);
  g->Binary(ynn_binary_multiply, 4587, 7173, 8494);
  g->Binary(ynn_binary_multiply, 8494, 8493, 4588);
  g->Binary(ynn_binary_multiply, 4585, 4588, 4589);
  g->Quantize(4589, 4590, 0.2027559131383896, 0);
  g->Transpose(9271, 7015, {1,0});
  g->Binary(ynn_binary_multiply, 5272, 7014, 7011);
  g->Dot(4590, 7015, YNN_INVALID_VALUE_ID, 7010, 1);
  g->DequantizeTensor(7010, YNN_INVALID_VALUE_ID, 7011, 7012);
  g->QuantizeTensor(7012, 8595, 7013, 4591);
  g->Dequantize(4591, 4593, 0.0875178799033165, 0);
  g->Unary(ynn_unary_square, 4593, 4594);
  g->Reduce(ynn_reduce_sum, 4594, 8498, {2}, true);
  g->ShapeProduct(4594, 8497, {2});
  g->Binary(ynn_binary_divide, 8498, 8497, 4595);
  g->Binary(ynn_binary_add, 4595, 8647, 4596);
  g->Unary(ynn_unary_rsqrt, 4596, 4597);
  g->Binary(ynn_binary_multiply, 4593, 4597, 4598);
  g->Binary(ynn_binary_multiply, 4598, 9277, 4599);
  g->Binary(ynn_binary_add, 4599, 4575, 4600);
}

// Scope: "Layer4 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 4601, {0,0,4,0}, {-1,-1,1,-1});
  g->Reshape(4601, 4602, {1,1,256});
  g->Unary(ynn_unary_square, 4602, 4604);
  g->Reduce(ynn_reduce_sum, 4604, 8500, {2}, true);
  g->ShapeProduct(4604, 8499, {2});
  g->Binary(ynn_binary_divide, 8500, 8499, 4605);
  g->Binary(ynn_binary_add, 4605, 8647, 4606);
  g->Unary(ynn_unary_rsqrt, 4606, 4607);
  g->Binary(ynn_binary_multiply, 4602, 4607, 4608);
  g->Binary(ynn_binary_multiply, 4608, 9401, 4609);
  g->Binary(ynn_binary_multiply, 9436, 8651, 4610);
  g->Binary(ynn_binary_add, 4609, 4610, 4611);
  g->Binary(ynn_binary_multiply, 4611, 8645, 4612);
  g->Quantize(4600, 4613, 0.5713114738464355, 0);
  g->Transpose(9274, 7022, {1,0});
  g->Binary(ynn_binary_multiply, 7019, 7021, 7017);
  g->Dot(4613, 7022, YNN_INVALID_VALUE_ID, 7016, 1);
  g->DequantizeTensor(7016, YNN_INVALID_VALUE_ID, 7017, 7018);
  g->QuantizeTensor(7018, 8595, 7020, 4615);
  g->Dequantize(4615, 4616, 0.06594488769769669, 0);
  g->Polynomial(4616, 8503, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8503, 8504);
  g->Binary(ynn_binary_add, 8504, 7161, 8501);
  g->Binary(ynn_binary_multiply, 4616, 7173, 8502);
  g->Binary(ynn_binary_multiply, 8502, 8501, 4617);
  g->Binary(ynn_binary_multiply, 4617, 4612, 4618);
  g->Quantize(4618, 4619, 0.4055117964744568, 0);
  g->Transpose(9275, 7029, {1,0});
  g->Binary(ynn_binary_multiply, 7026, 7028, 7024);
  g->Dot(4619, 7029, YNN_INVALID_VALUE_ID, 7023, 1);
  g->DequantizeTensor(7023, YNN_INVALID_VALUE_ID, 7024, 7025);
  g->QuantizeTensor(7025, 8595, 7027, 4620);
  g->Dequantize(4620, 4621, 0.10920456796884537, 0);
  g->Unary(ynn_unary_square, 4621, 4622);
  g->Reduce(ynn_reduce_sum, 4622, 8506, {2}, true);
  g->ShapeProduct(4622, 8505, {2});
  g->Binary(ynn_binary_divide, 8506, 8505, 4623);
  g->Binary(ynn_binary_add, 4623, 8647, 4624);
  g->Unary(ynn_unary_rsqrt, 4624, 4627);
  g->Binary(ynn_binary_multiply, 4621, 4627, 4628);
  g->Binary(ynn_binary_multiply, 4628, 9278, 4629);
  g->Binary(ynn_binary_add, 4600, 4629, 4630);
  g->Binary(ynn_binary_multiply, 4630, 9270, 4631);
}

// Scope: "Layer4"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4(Context& ctx) {
  BuildLayer4Attention(ctx);
  BuildLayer4Mlp(ctx);
  BuildLayer4PerLayerEmbedding(ctx);
}

// Scope: "Layer5 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(4638, 4639, 0.11662273108959198, 0);
  g->Transpose(9326, 7036, {1,0});
  g->Binary(ynn_binary_multiply, 7033, 7035, 7031);
  g->Dot(4639, 7036, YNN_INVALID_VALUE_ID, 7030, 1);
  g->DequantizeTensor(7030, YNN_INVALID_VALUE_ID, 7031, 7032);
  g->QuantizeTensor(7032, 8595, 7034, 4640);
  g->Dequantize(4640, 4641, 0.09891732782125473, 0);
  g->SplitDim(4641, 4642, 2, {2,512});
  g->Transpose(4642, 4643, {0,2,1,3});
  g->Unary(ynn_unary_square, 4643, 4644);
  g->Reduce(ynn_reduce_sum, 4644, 8510, {3}, true);
  g->ShapeProduct(4644, 8509, {3});
  g->Binary(ynn_binary_divide, 8510, 8509, 4645);
  g->Binary(ynn_binary_add, 4645, 8647, 4646);
  g->Unary(ynn_unary_rsqrt, 4646, 4647);
  g->Binary(ynn_binary_multiply, 4643, 4647, 4649);
  g->Binary(ynn_binary_multiply, 4649, 9325, 4650);
  g->Slice(4650, 4651, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(4650, 4652, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 4652, 4653);
  g->Concat({4653,4651}, 4654, 3);
  g->Binary(ynn_binary_multiply, 4650, 4830, 4655);
  g->Binary(ynn_binary_multiply, 4654, 2, 4656);
  g->Binary(ynn_binary_add, 4655, 4656, 4657);
  g->Transpose(9330, 7041, {1,0});
  g->Binary(ynn_binary_multiply, 7033, 7040, 7038);
  g->Dot(4639, 7041, YNN_INVALID_VALUE_ID, 7037, 1);
  g->DequantizeTensor(7037, YNN_INVALID_VALUE_ID, 7038, 7039);
  g->QuantizeTensor(7039, 8595, 7034, 4659);
  g->Dequantize(4659, 4660, 0.09891732782125473, 0);
  g->SplitDim(4660, 4661, 2, {2,512});
  g->Transpose(4661, 4662, {0,2,1,3});
  g->Unary(ynn_unary_square, 4662, 4663);
  g->Reduce(ynn_reduce_sum, 4663, 8512, {3}, true);
  g->ShapeProduct(4663, 8511, {3});
  g->Binary(ynn_binary_divide, 8512, 8511, 4664);
  g->Binary(ynn_binary_add, 4664, 8647, 4665);
  g->Unary(ynn_unary_rsqrt, 4665, 4666);
  g->Binary(ynn_binary_multiply, 4662, 4666, 4667);
}

// Scope: "Layer5 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(4657, 4668, 0.001090860809199512, 0);
  g->Append(8615, 4668, 9464, 2, s2, slinky::expr(int64_t{1}));
  g->View(9464, 9512, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(4667, 4670, 0.01785714365541935, 0);
  g->Append(8639, 4670, 9488, 2, s2, slinky::expr(int64_t{1}));
  g->View(9488, 9536, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer5 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(9329, 7047, {1,0});
  g->Binary(ynn_binary_multiply, 7033, 7046, 7043);
  g->Dot(4639, 7047, YNN_INVALID_VALUE_ID, 7042, 1);
  g->DequantizeTensor(7042, YNN_INVALID_VALUE_ID, 7043, 7044);
  g->QuantizeTensor(7044, 8595, 7045, 4671);
  g->Dequantize(4671, 4672, 0.1092519760131836, 0);
  g->SplitDim(4672, 4673, 2, {8,512});
  g->Transpose(4673, 4674, {0,2,1,3});
  g->Unary(ynn_unary_square, 4674, 4676);
  g->Reduce(ynn_reduce_sum, 4676, 8514, {3}, true);
  g->ShapeProduct(4676, 8513, {3});
  g->Binary(ynn_binary_divide, 8514, 8513, 4677);
  g->Binary(ynn_binary_add, 4677, 8647, 4678);
  g->Unary(ynn_unary_rsqrt, 4678, 4679);
  g->Binary(ynn_binary_multiply, 4674, 4679, 4680);
  g->Binary(ynn_binary_multiply, 4680, 9328, 4681);
  g->Slice(4681, 4682, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(4681, 4683, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 4683, 4684);
  g->Concat({4684,4682}, 4685, 3);
  g->Binary(ynn_binary_multiply, 4681, 4830, 4687);
  g->Binary(ynn_binary_multiply, 4685, 2, 4688);
  g->Binary(ynn_binary_add, 4687, 4688, 4689);
}

// Scope: "Layer5 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9512, 4690, 0.001090860809199512, 0);
  g->Dequantize(9536, 4691, 0.01785714365541935, 0);
  g->Slice(4689, 4692, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(4690, 4693, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(4691, 4694, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(4692, 4693, 4695, false, true);
  g->Mask(4695, 8728, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 8728, 8518, {-1}, true);
  g->Binary(ynn_binary_subtract, 8728, 8518, 8515);
  g->Unary(ynn_unary_exp, 8515, 8516);
  g->Reduce(ynn_reduce_sum, 8516, 8519, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 8519, 8517);
  g->Binary(ynn_binary_multiply, 8516, 8517, 4697);
  g->Matmul(4697, 4694, 4698, false, false);
  g->Slice(4689, 4699, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(4690, 4700, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(4691, 4701, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(4699, 4700, 4702, false, true);
  g->Mask(4702, 8729, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 8729, 8523, {-1}, true);
  g->Binary(ynn_binary_subtract, 8729, 8523, 8520);
  g->Unary(ynn_unary_exp, 8520, 8521);
  g->Reduce(ynn_reduce_sum, 8521, 8524, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 8524, 8522);
  g->Binary(ynn_binary_multiply, 8521, 8522, 4703);
  g->Matmul(4703, 4701, 4704, false, false);
  g->Concat({4698,4704}, 4705, 1);
}

// Scope: "Layer5 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(4705, 4707, {0,2,1,3});
  g->FuseDims(4707, 4708, 2, 2);
  g->Quantize(4708, 4709, 0.017839577049016953, 0);
  g->Transpose(9327, 7053, {1,0});
  g->Binary(ynn_binary_multiply, 6837, 7052, 7049);
  g->Dot(4709, 7053, YNN_INVALID_VALUE_ID, 7048, 1);
  g->DequantizeTensor(7048, YNN_INVALID_VALUE_ID, 7049, 7050);
  g->QuantizeTensor(7050, 8595, 7051, 4710);
  g->Dequantize(4710, 4711, 0.14457935094833374, 0);
}

// Scope: "Layer5 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 4631, 4632);
  g->Reduce(ynn_reduce_sum, 4632, 8508, {2}, true);
  g->ShapeProduct(4632, 8507, {2});
  g->Binary(ynn_binary_divide, 8508, 8507, 4633);
  g->Binary(ynn_binary_add, 4633, 8647, 4634);
  g->Unary(ynn_unary_rsqrt, 4634, 4635);
  g->Binary(ynn_binary_multiply, 4631, 4635, 4636);
  g->Binary(ynn_binary_multiply, 4636, 9314, 4638);
  BuildLayer5AttentionKvProjection(ctx);
  BuildLayer5AttentionCacheUpdate(ctx);
  BuildLayer5AttentionQueryProjection(ctx);
  BuildLayer5AttentionSdpa(ctx);
  BuildLayer5AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 4711, 4712);
  g->Reduce(ynn_reduce_sum, 4712, 8526, {2}, true);
  g->ShapeProduct(4712, 8525, {2});
  g->Binary(ynn_binary_divide, 8526, 8525, 4713);
  g->Binary(ynn_binary_add, 4713, 8647, 4714);
  g->Unary(ynn_unary_rsqrt, 4714, 4715);
  g->Binary(ynn_binary_multiply, 4711, 4715, 4716);
  g->Binary(ynn_binary_multiply, 4716, 9321, 4717);
  g->Binary(ynn_binary_add, 4717, 4631, 4718);
}

// Scope: "Layer5 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 4718, 4719);
  g->Reduce(ynn_reduce_sum, 4719, 8528, {2}, true);
  g->ShapeProduct(4719, 8527, {2});
  g->Binary(ynn_binary_divide, 8528, 8527, 4720);
  g->Binary(ynn_binary_add, 4720, 8647, 4721);
  g->Unary(ynn_unary_rsqrt, 4721, 4722);
  g->Binary(ynn_binary_multiply, 4718, 4722, 4723);
  g->Binary(ynn_binary_multiply, 4723, 9324, 4724);
  g->Quantize(4724, 4725, 0.3053959310054779, 0);
  g->Transpose(9318, 7060, {1,0});
  g->Binary(ynn_binary_multiply, 7057, 7059, 7055);
  g->Dot(4725, 7060, YNN_INVALID_VALUE_ID, 7054, 1);
  g->DequantizeTensor(7054, YNN_INVALID_VALUE_ID, 7055, 7056);
  g->QuantizeTensor(7056, 8595, 7058, 4726);
  g->Dequantize(4726, 4729, 0.16633859276771545, 0);
  g->Transpose(9317, 7065, {1,0});
  g->Binary(ynn_binary_multiply, 7057, 7064, 7062);
  g->Dot(4725, 7065, YNN_INVALID_VALUE_ID, 7061, 1);
  g->DequantizeTensor(7061, YNN_INVALID_VALUE_ID, 7062, 7063);
  g->QuantizeTensor(7063, 8595, 7058, 4730);
  g->Dequantize(4730, 4731, 0.16633859276771545, 0);
  g->Polynomial(4731, 8536, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8536, 8537);
  g->Binary(ynn_binary_add, 8537, 7161, 8534);
  g->Binary(ynn_binary_multiply, 4731, 7173, 8535);
  g->Binary(ynn_binary_multiply, 8535, 8534, 4732);
  g->Binary(ynn_binary_multiply, 4729, 4732, 4733);
  g->Quantize(4733, 4734, 1.5511810779571533, 0);
  g->Transpose(9316, 7072, {1,0});
  g->Binary(ynn_binary_multiply, 7069, 7071, 7067);
  g->Dot(4734, 7072, YNN_INVALID_VALUE_ID, 7066, 1);
  g->DequantizeTensor(7066, YNN_INVALID_VALUE_ID, 7067, 7068);
  g->QuantizeTensor(7068, 8595, 7070, 4735);
  g->Dequantize(4735, 4736, 0.3160533308982849, 0);
  g->Unary(ynn_unary_square, 4736, 4737);
  g->Reduce(ynn_reduce_sum, 4737, 8539, {2}, true);
  g->ShapeProduct(4737, 8538, {2});
  g->Binary(ynn_binary_divide, 8539, 8538, 4739);
  g->Binary(ynn_binary_add, 4739, 8647, 4740);
  g->Unary(ynn_unary_rsqrt, 4740, 4741);
  g->Binary(ynn_binary_multiply, 4736, 4741, 4742);
  g->Binary(ynn_binary_multiply, 4742, 9322, 4743);
  g->Binary(ynn_binary_add, 4743, 4718, 4744);
}

// Scope: "Layer5 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 4745, {0,0,5,0}, {-1,-1,1,-1});
  g->Reshape(4745, 4746, {1,1,256});
  g->Unary(ynn_unary_square, 4746, 4747);
  g->Reduce(ynn_reduce_sum, 4747, 8541, {2}, true);
  g->ShapeProduct(4747, 8540, {2});
  g->Binary(ynn_binary_divide, 8541, 8540, 4748);
  g->Binary(ynn_binary_add, 4748, 8647, 4750);
  g->Unary(ynn_unary_rsqrt, 4750, 4751);
  g->Binary(ynn_binary_multiply, 4746, 4751, 4752);
  g->Binary(ynn_binary_multiply, 4752, 9401, 4753);
  g->Binary(ynn_binary_multiply, 9439, 8651, 4754);
  g->Binary(ynn_binary_add, 4753, 4754, 4755);
  g->Binary(ynn_binary_multiply, 4755, 8645, 4756);
  g->Quantize(4744, 4757, 0.33932316303253174, 0);
  g->Transpose(9319, 7078, {1,0});
  g->Binary(ynn_binary_multiply, 7076, 7077, 7074);
  g->Dot(4757, 7078, YNN_INVALID_VALUE_ID, 7073, 1);
  g->DequantizeTensor(7073, YNN_INVALID_VALUE_ID, 7074, 7075);
  g->QuantizeTensor(7075, 8595, 5297, 4758);
  g->Dequantize(4758, 4759, 0.05216536670923233, 0);
  g->Polynomial(4759, 8544, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8544, 8545);
  g->Binary(ynn_binary_add, 8545, 7161, 8542);
  g->Binary(ynn_binary_multiply, 4759, 7173, 8543);
  g->Binary(ynn_binary_multiply, 8543, 8542, 4761);
  g->Binary(ynn_binary_multiply, 4761, 4756, 4762);
  g->Quantize(4762, 4763, 0.25, 0);
  g->Transpose(9320, 7084, {1,0});
  g->Binary(ynn_binary_multiply, 5398, 7083, 7080);
  g->Dot(4763, 7084, YNN_INVALID_VALUE_ID, 7079, 1);
  g->DequantizeTensor(7079, YNN_INVALID_VALUE_ID, 7080, 7081);
  g->QuantizeTensor(7081, 8595, 7082, 4764);
  g->Dequantize(4764, 4765, 0.13969317078590393, 0);
  g->Unary(ynn_unary_square, 4765, 4766);
  g->Reduce(ynn_reduce_sum, 4766, 8547, {2}, true);
  g->ShapeProduct(4766, 8546, {2});
  g->Binary(ynn_binary_divide, 8547, 8546, 4767);
  g->Binary(ynn_binary_add, 4767, 8647, 4768);
  g->Unary(ynn_unary_rsqrt, 4768, 4769);
  g->Binary(ynn_binary_multiply, 4765, 4769, 4770);
  g->Binary(ynn_binary_multiply, 4770, 9323, 4772);
  g->Binary(ynn_binary_add, 4744, 4772, 4773);
  g->Binary(ynn_binary_multiply, 4773, 9315, 4774);
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
  g->Quantize(4780, 4781, 0.0976727083325386, 0);
  g->Transpose(9343, 7090, {1,0});
  g->Binary(ynn_binary_multiply, 7088, 7089, 7086);
  g->Dot(4781, 7090, YNN_INVALID_VALUE_ID, 7085, 1);
  g->DequantizeTensor(7085, YNN_INVALID_VALUE_ID, 7086, 7087);
  g->QuantizeTensor(7087, 8595, 5520, 4783);
  g->Dequantize(4783, 4784, 0.16535434126853943, 0);
  g->SplitDim(4784, 4785, 2, {2,256});
  g->Transpose(4785, 4786, {0,2,1,3});
  g->Unary(ynn_unary_square, 4786, 4787);
  g->Reduce(ynn_reduce_sum, 4787, 8551, {3}, true);
  g->ShapeProduct(4787, 8550, {3});
  g->Binary(ynn_binary_divide, 8551, 8550, 4788);
  g->Binary(ynn_binary_add, 4788, 8647, 4789);
  g->Unary(ynn_unary_rsqrt, 4789, 4790);
  g->Binary(ynn_binary_multiply, 4786, 4790, 4791);
  g->Binary(ynn_binary_multiply, 4791, 9342, 4792);
  g->Slice(4792, 4793, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(4792, 4794, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 4794, 4795);
  g->Concat({4795,4793}, 4796, 3);
  g->Binary(ynn_binary_multiply, 4792, 3141, 4797);
  g->Binary(ynn_binary_multiply, 4796, 4217, 4798);
  g->Binary(ynn_binary_add, 4797, 4798, 4799);
  g->Transpose(9347, 7095, {1,0});
  g->Binary(ynn_binary_multiply, 7088, 7094, 7092);
  g->Dot(4781, 7095, YNN_INVALID_VALUE_ID, 7091, 1);
  g->DequantizeTensor(7091, YNN_INVALID_VALUE_ID, 7092, 7093);
  g->QuantizeTensor(7093, 8595, 5520, 4800);
  g->Dequantize(4800, 4801, 0.16535434126853943, 0);
  g->SplitDim(4801, 4803, 2, {2,256});
  g->Transpose(4803, 4804, {0,2,1,3});
  g->Unary(ynn_unary_square, 4804, 4805);
  g->Reduce(ynn_reduce_sum, 4805, 8558, {3}, true);
  g->ShapeProduct(4805, 8557, {3});
  g->Binary(ynn_binary_divide, 8558, 8557, 4806);
  g->Binary(ynn_binary_add, 4806, 8647, 4807);
  g->Unary(ynn_unary_rsqrt, 4807, 4808);
  g->Binary(ynn_binary_multiply, 4804, 4808, 4809);
}

// Scope: "Layer6 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(4799, 4810, 0.005761673673987389, 0);
  g->Append(8616, 4810, 9465, 2, s2, slinky::expr(int64_t{1}));
  g->View(9465, 9513, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(4809, 4812, 0.047244105488061905, 0);
  g->Append(8640, 4812, 9489, 2, s2, slinky::expr(int64_t{1}));
  g->View(9489, 9537, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer6 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(9346, 7100, {1,0});
  g->Binary(ynn_binary_multiply, 7088, 7099, 7097);
  g->Dot(4781, 7100, YNN_INVALID_VALUE_ID, 7096, 1);
  g->DequantizeTensor(7096, YNN_INVALID_VALUE_ID, 7097, 7098);
  g->QuantizeTensor(7098, 8595, 7058, 4813);
  g->Dequantize(4813, 4814, 0.16633859276771545, 0);
  g->SplitDim(4814, 4815, 2, {8,256});
  g->Transpose(4815, 4816, {0,2,1,3});
  g->Unary(ynn_unary_square, 4816, 4817);
  g->Reduce(ynn_reduce_sum, 4817, 8560, {3}, true);
  g->ShapeProduct(4817, 8559, {3});
  g->Binary(ynn_binary_divide, 8560, 8559, 4818);
  g->Binary(ynn_binary_add, 4818, 8647, 4820);
  g->Unary(ynn_unary_rsqrt, 4820, 4821);
  g->Binary(ynn_binary_multiply, 4816, 4821, 4822);
  g->Binary(ynn_binary_multiply, 4822, 9345, 4823);
  g->Slice(4823, 4824, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(4823, 4825, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 4825, 4826);
  g->Concat({4826,4824}, 4827, 3);
  g->Binary(ynn_binary_multiply, 4823, 3141, 4828);
  g->Binary(ynn_binary_multiply, 4827, 4217, 4829);
  g->Binary(ynn_binary_add, 4828, 4829, 4832);
}

// Scope: "Layer6 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9513, 4833, 0.005761673673987389, 0);
  g->Dequantize(9537, 4834, 0.047244105488061905, 0);
  g->Slice(4832, 4835, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(4833, 4836, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(4834, 4837, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(4835, 4836, 4838, false, true);
  g->Mask(4838, 8730, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8730, 8564, {-1}, true);
  g->Binary(ynn_binary_subtract, 8730, 8564, 8561);
  g->Unary(ynn_unary_exp, 8561, 8562);
  g->Reduce(ynn_reduce_sum, 8562, 8565, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 8565, 8563);
  g->Binary(ynn_binary_multiply, 8562, 8563, 4839);
  g->Matmul(4839, 4837, 4840, false, false);
  g->Slice(4832, 4842, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(4833, 4843, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(4834, 4844, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(4842, 4843, 4845, false, true);
  g->Mask(4845, 8731, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8731, 8569, {-1}, true);
  g->Binary(ynn_binary_subtract, 8731, 8569, 8566);
  g->Unary(ynn_unary_exp, 8566, 8567);
  g->Reduce(ynn_reduce_sum, 8567, 8570, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 8570, 8568);
  g->Binary(ynn_binary_multiply, 8567, 8568, 4846);
  g->Matmul(4846, 4844, 4847, false, false);
  g->Concat({4840,4847}, 4848, 1);
}

// Scope: "Layer6 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(4848, 4849, {0,2,1,3});
  g->FuseDims(4849, 4850, 2, 2);
  g->Quantize(4850, 4852, 0.02706693857908249, 0);
  g->Transpose(9344, 7106, {1,0});
  g->Binary(ynn_binary_multiply, 5472, 7105, 7102);
  g->Dot(4852, 7106, YNN_INVALID_VALUE_ID, 7101, 1);
  g->DequantizeTensor(7101, YNN_INVALID_VALUE_ID, 7102, 7103);
  g->QuantizeTensor(7103, 8595, 7104, 4853);
  g->Dequantize(4853, 4854, 0.19767579436302185, 0);
}

// Scope: "Layer6 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 4774, 4775);
  g->Reduce(ynn_reduce_sum, 4775, 8549, {2}, true);
  g->ShapeProduct(4775, 8548, {2});
  g->Binary(ynn_binary_divide, 8549, 8548, 4776);
  g->Binary(ynn_binary_add, 4776, 8647, 4777);
  g->Unary(ynn_unary_rsqrt, 4777, 4778);
  g->Binary(ynn_binary_multiply, 4774, 4778, 4779);
  g->Binary(ynn_binary_multiply, 4779, 9331, 4780);
  BuildLayer6AttentionKvProjection(ctx);
  BuildLayer6AttentionCacheUpdate(ctx);
  BuildLayer6AttentionQueryProjection(ctx);
  BuildLayer6AttentionSdpa(ctx);
  BuildLayer6AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 4854, 4855);
  g->Reduce(ynn_reduce_sum, 4855, 8572, {2}, true);
  g->ShapeProduct(4855, 8571, {2});
  g->Binary(ynn_binary_divide, 8572, 8571, 4856);
  g->Binary(ynn_binary_add, 4856, 8647, 4857);
  g->Unary(ynn_unary_rsqrt, 4857, 4858);
  g->Binary(ynn_binary_multiply, 4854, 4858, 4859);
  g->Binary(ynn_binary_multiply, 4859, 9338, 4860);
  g->Binary(ynn_binary_add, 4860, 4774, 4861);
}

// Scope: "Layer6 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 4861, 4863);
  g->Reduce(ynn_reduce_sum, 4863, 8574, {2}, true);
  g->ShapeProduct(4863, 8573, {2});
  g->Binary(ynn_binary_divide, 8574, 8573, 4864);
  g->Binary(ynn_binary_add, 4864, 8647, 4865);
  g->Unary(ynn_unary_rsqrt, 4865, 4866);
  g->Binary(ynn_binary_multiply, 4861, 4866, 4867);
  g->Binary(ynn_binary_multiply, 4867, 9341, 4868);
  g->Quantize(4868, 4869, 0.06627800315618515, 0);
  g->Transpose(9335, 7120, {1,0});
  g->Binary(ynn_binary_multiply, 7117, 7119, 7115);
  g->Dot(4869, 7120, YNN_INVALID_VALUE_ID, 7114, 1);
  g->DequantizeTensor(7114, YNN_INVALID_VALUE_ID, 7115, 7116);
  g->QuantizeTensor(7116, 8595, 7118, 4870);
  g->Dequantize(4870, 4871, 0.1171259880065918, 0);
  g->Transpose(9334, 7125, {1,0});
  g->Binary(ynn_binary_multiply, 7117, 7124, 7122);
  g->Dot(4869, 7125, YNN_INVALID_VALUE_ID, 7121, 1);
  g->DequantizeTensor(7121, YNN_INVALID_VALUE_ID, 7122, 7123);
  g->QuantizeTensor(7123, 8595, 7118, 4873);
  g->Dequantize(4873, 4874, 0.1171259880065918, 0);
  g->Polynomial(4874, 8577, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8577, 8578);
  g->Binary(ynn_binary_add, 8578, 7161, 8575);
  g->Binary(ynn_binary_multiply, 4874, 7173, 8576);
  g->Binary(ynn_binary_multiply, 8576, 8575, 4875);
  g->Binary(ynn_binary_multiply, 4871, 4875, 4876);
  g->Quantize(4876, 4877, 0.4488188922405243, 0);
  g->Transpose(9333, 7132, {1,0});
  g->Binary(ynn_binary_multiply, 7129, 7131, 7127);
  g->Dot(4877, 7132, YNN_INVALID_VALUE_ID, 7126, 1);
  g->DequantizeTensor(7126, YNN_INVALID_VALUE_ID, 7127, 7128);
  g->QuantizeTensor(7128, 8595, 7130, 4878);
  g->Dequantize(4878, 4879, 0.19675913453102112, 0);
  g->Unary(ynn_unary_square, 4879, 4880);
  g->Reduce(ynn_reduce_sum, 4880, 8580, {2}, true);
  g->ShapeProduct(4880, 8579, {2});
  g->Binary(ynn_binary_divide, 8580, 8579, 4881);
  g->Binary(ynn_binary_add, 4881, 8647, 4882);
  g->Unary(ynn_unary_rsqrt, 4882, 4884);
  g->Binary(ynn_binary_multiply, 4879, 4884, 4885);
  g->Binary(ynn_binary_multiply, 4885, 9339, 4886);
  g->Binary(ynn_binary_add, 4886, 4861, 4887);
}

// Scope: "Layer6 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 4888, {0,0,6,0}, {-1,-1,1,-1});
  g->Reshape(4888, 4889, {1,1,256});
  g->Unary(ynn_unary_square, 4889, 4890);
  g->Reduce(ynn_reduce_sum, 4890, 8582, {2}, true);
  g->ShapeProduct(4890, 8581, {2});
  g->Binary(ynn_binary_divide, 8582, 8581, 4891);
  g->Binary(ynn_binary_add, 4891, 8647, 4892);
  g->Unary(ynn_unary_rsqrt, 4892, 4893);
  g->Binary(ynn_binary_multiply, 4889, 4893, 4895);
  g->Binary(ynn_binary_multiply, 4895, 9401, 4896);
  g->Binary(ynn_binary_multiply, 9440, 8651, 4897);
  g->Binary(ynn_binary_add, 4896, 4897, 4898);
  g->Binary(ynn_binary_multiply, 4898, 8645, 4899);
  g->Quantize(4887, 4900, 0.5854530930519104, 0);
  g->Transpose(9336, 7139, {1,0});
  g->Binary(ynn_binary_multiply, 7136, 7138, 7134);
  g->Dot(4900, 7139, YNN_INVALID_VALUE_ID, 7133, 1);
  g->DequantizeTensor(7133, YNN_INVALID_VALUE_ID, 7134, 7135);
  g->QuantizeTensor(7135, 8595, 7137, 4901);
  g->Dequantize(4901, 4902, 0.0433070994913578, 0);
  g->Polynomial(4902, 8587, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8587, 8588);
  g->Binary(ynn_binary_add, 8588, 7161, 8585);
  g->Binary(ynn_binary_multiply, 4902, 7173, 8586);
  g->Binary(ynn_binary_multiply, 8586, 8585, 4903);
  g->Binary(ynn_binary_multiply, 4903, 4899, 4904);
  g->Quantize(4904, 4906, 0.25590550899505615, 0);
  g->Transpose(9337, 7145, {1,0});
  g->Binary(ynn_binary_multiply, 6376, 7144, 7141);
  g->Dot(4906, 7145, YNN_INVALID_VALUE_ID, 7140, 1);
  g->DequantizeTensor(7140, YNN_INVALID_VALUE_ID, 7141, 7142);
  g->QuantizeTensor(7142, 8595, 7143, 4907);
  g->Dequantize(4907, 4908, 0.08977121859788895, 0);
  g->Unary(ynn_unary_square, 4908, 4909);
  g->Reduce(ynn_reduce_sum, 4909, 8590, {2}, true);
  g->ShapeProduct(4909, 8589, {2});
  g->Binary(ynn_binary_divide, 8590, 8589, 4910);
  g->Binary(ynn_binary_add, 4910, 8647, 4911);
  g->Unary(ynn_unary_rsqrt, 4911, 4912);
  g->Binary(ynn_binary_multiply, 4908, 4912, 4913);
  g->Binary(ynn_binary_multiply, 4913, 9340, 4914);
  g->Binary(ynn_binary_add, 4887, 4914, 4915);
  g->Binary(ynn_binary_multiply, 4915, 9332, 4917);
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
  g->Quantize(4923, 4924, 0.17314177751541138, 0);
  g->Transpose(9360, 7150, {1,0});
  g->Binary(ynn_binary_multiply, 4941, 7149, 7147);
  g->Dot(4924, 7150, YNN_INVALID_VALUE_ID, 7146, 1);
  g->DequantizeTensor(7146, YNN_INVALID_VALUE_ID, 7147, 7148);
  g->QuantizeTensor(7148, 8595, 4942, 4925);
  g->Dequantize(4925, 4926, 0.3011811077594757, 0);
  g->SplitDim(4926, 4928, 2, {2,256});
  g->Transpose(4928, 4929, {0,2,1,3});
  g->Unary(ynn_unary_square, 4929, 4930);
  g->Reduce(ynn_reduce_sum, 4930, 8594, {3}, true);
  g->ShapeProduct(4930, 8593, {3});
  g->Binary(ynn_binary_divide, 8594, 8593, 4931);
  g->Binary(ynn_binary_add, 4931, 8647, 4932);
  g->Unary(ynn_unary_rsqrt, 4932, 4933);
  g->Binary(ynn_binary_multiply, 4929, 4933, 4934);
  g->Binary(ynn_binary_multiply, 4934, 9359, 4935);
  g->Slice(4935, 4936, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(4935, 4937, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 4937, 4);
  g->Concat({4,4936}, 5, 3);
  g->Binary(ynn_binary_multiply, 4935, 3141, 6);
  g->Binary(ynn_binary_multiply, 5, 4217, 7);
  g->Binary(ynn_binary_add, 6, 7, 8);
  g->Transpose(9364, 4944, {1,0});
  g->Binary(ynn_binary_multiply, 4941, 4943, 4939);
  g->Dot(4924, 4944, YNN_INVALID_VALUE_ID, 4938, 1);
  g->DequantizeTensor(4938, YNN_INVALID_VALUE_ID, 4939, 4940);
  g->QuantizeTensor(4940, 8595, 4942, 9);
  g->Dequantize(9, 10, 0.3011811077594757, 0);
  g->SplitDim(10, 11, 2, {2,256});
  g->Transpose(11, 12, {0,2,1,3});
  g->Unary(ynn_unary_square, 12, 14);
  g->Reduce(ynn_reduce_sum, 14, 7152, {3}, true);
  g->ShapeProduct(14, 7151, {3});
  g->Binary(ynn_binary_divide, 7152, 7151, 15);
  g->Binary(ynn_binary_add, 15, 8647, 16);
  g->Unary(ynn_unary_rsqrt, 16, 17);
  g->Binary(ynn_binary_multiply, 12, 17, 18);
}

// Scope: "Layer7 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(8, 19, 0.006011798977851868, 0);
  g->Append(8617, 19, 9466, 2, s2, slinky::expr(int64_t{1}));
  g->View(9466, 9514, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(18, 20, 0.047244105488061905, 0);
  g->Append(8641, 20, 9490, 2, s2, slinky::expr(int64_t{1}));
  g->View(9490, 9538, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer7 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(9363, 4950, {1,0});
  g->Binary(ynn_binary_multiply, 4941, 4949, 4946);
  g->Dot(4924, 4950, YNN_INVALID_VALUE_ID, 4945, 1);
  g->DequantizeTensor(4945, YNN_INVALID_VALUE_ID, 4946, 4947);
  g->QuantizeTensor(4947, 8595, 4948, 22);
  g->Dequantize(22, 23, 0.31889763474464417, 0);
  g->SplitDim(23, 24, 2, {8,256});
  g->Transpose(24, 25, {0,2,1,3});
  g->Unary(ynn_unary_square, 25, 26);
  g->Reduce(ynn_reduce_sum, 26, 7154, {3}, true);
  g->ShapeProduct(26, 7153, {3});
  g->Binary(ynn_binary_divide, 7154, 7153, 27);
  g->Binary(ynn_binary_add, 27, 8647, 28);
  g->Unary(ynn_unary_rsqrt, 28, 29);
  g->Binary(ynn_binary_multiply, 25, 29, 31);
  g->Binary(ynn_binary_multiply, 31, 9362, 32);
  g->Slice(32, 33, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(32, 34, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 34, 35);
  g->Concat({35,33}, 36, 3);
  g->Binary(ynn_binary_multiply, 32, 3141, 37);
  g->Binary(ynn_binary_multiply, 36, 4217, 38);
  g->Binary(ynn_binary_add, 37, 38, 39);
}

// Scope: "Layer7 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9514, 40, 0.006011798977851868, 0);
  g->Dequantize(9538, 42, 0.047244105488061905, 0);
  g->Slice(39, 43, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(40, 44, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(42, 45, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(43, 44, 46, false, true);
  g->Mask(46, 8732, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8732, 7160, {-1}, true);
  g->Binary(ynn_binary_subtract, 8732, 7160, 7157);
  g->Unary(ynn_unary_exp, 7157, 7158);
  g->Reduce(ynn_reduce_sum, 7158, 7162, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 7162, 7159);
  g->Binary(ynn_binary_multiply, 7158, 7159, 47);
  g->Matmul(47, 45, 48, false, false);
  g->Slice(39, 49, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(40, 50, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(42, 52, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(49, 50, 53, false, true);
  g->Mask(53, 8733, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8733, 7166, {-1}, true);
  g->Binary(ynn_binary_subtract, 8733, 7166, 7163);
  g->Unary(ynn_unary_exp, 7163, 7164);
  g->Reduce(ynn_reduce_sum, 7164, 7167, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 7167, 7165);
  g->Binary(ynn_binary_multiply, 7164, 7165, 54);
  g->Matmul(54, 52, 55, false, false);
  g->Concat({48,55}, 56, 1);
}

// Scope: "Layer7 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(56, 57, {0,2,1,3});
  g->FuseDims(57, 58, 2, 2);
  g->Quantize(58, 59, 0.02239174209535122, 0);
  g->Transpose(9361, 4957, {1,0});
  g->Binary(ynn_binary_multiply, 4954, 4956, 4952);
  g->Dot(59, 4957, YNN_INVALID_VALUE_ID, 4951, 1);
  g->DequantizeTensor(4951, YNN_INVALID_VALUE_ID, 4952, 4953);
  g->QuantizeTensor(4953, 8595, 4955, 60);
  g->Dequantize(60, 62, 0.07983598113059998, 0);
}

// Scope: "Layer7 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 4917, 4918);
  g->Reduce(ynn_reduce_sum, 4918, 8592, {2}, true);
  g->ShapeProduct(4918, 8591, {2});
  g->Binary(ynn_binary_divide, 8592, 8591, 4919);
  g->Binary(ynn_binary_add, 4919, 8647, 4920);
  g->Unary(ynn_unary_rsqrt, 4920, 4921);
  g->Binary(ynn_binary_multiply, 4917, 4921, 4922);
  g->Binary(ynn_binary_multiply, 4922, 9348, 4923);
  BuildLayer7AttentionKvProjection(ctx);
  BuildLayer7AttentionCacheUpdate(ctx);
  BuildLayer7AttentionQueryProjection(ctx);
  BuildLayer7AttentionSdpa(ctx);
  BuildLayer7AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 62, 63);
  g->Reduce(ynn_reduce_sum, 63, 7169, {2}, true);
  g->ShapeProduct(63, 7168, {2});
  g->Binary(ynn_binary_divide, 7169, 7168, 64);
  g->Binary(ynn_binary_add, 64, 8647, 65);
  g->Unary(ynn_unary_rsqrt, 65, 66);
  g->Binary(ynn_binary_multiply, 62, 66, 67);
  g->Binary(ynn_binary_multiply, 67, 9355, 68);
  g->Binary(ynn_binary_add, 68, 4917, 69);
}

// Scope: "Layer7 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 69, 70);
  g->Reduce(ynn_reduce_sum, 70, 7171, {2}, true);
  g->ShapeProduct(70, 7170, {2});
  g->Binary(ynn_binary_divide, 7171, 7170, 71);
  g->Binary(ynn_binary_add, 71, 8647, 73);
  g->Unary(ynn_unary_rsqrt, 73, 74);
  g->Binary(ynn_binary_multiply, 69, 74, 75);
  g->Binary(ynn_binary_multiply, 75, 9358, 76);
  g->Quantize(76, 77, 0.04099859297275543, 0);
  g->Transpose(9352, 4964, {1,0});
  g->Binary(ynn_binary_multiply, 4961, 4963, 4959);
  g->Dot(77, 4964, YNN_INVALID_VALUE_ID, 4958, 1);
  g->DequantizeTensor(4958, YNN_INVALID_VALUE_ID, 4959, 4960);
  g->QuantizeTensor(4960, 8595, 4962, 78);
  g->Dequantize(78, 79, 0.0625000074505806, 0);
  g->Transpose(9351, 4969, {1,0});
  g->Binary(ynn_binary_multiply, 4961, 4968, 4966);
  g->Dot(77, 4969, YNN_INVALID_VALUE_ID, 4965, 1);
  g->DequantizeTensor(4965, YNN_INVALID_VALUE_ID, 4966, 4967);
  g->QuantizeTensor(4967, 8595, 4962, 80);
  g->Dequantize(80, 81, 0.0625000074505806, 0);
  g->Polynomial(81, 7175, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7175, 7176);
  g->Binary(ynn_binary_add, 7176, 7161, 7172);
  g->Binary(ynn_binary_multiply, 81, 7173, 7174);
  g->Binary(ynn_binary_multiply, 7174, 7172, 83);
  g->Binary(ynn_binary_multiply, 79, 83, 84);
  g->Quantize(84, 85, 0.18503938615322113, 0);
  g->Transpose(9350, 4976, {1,0});
  g->Binary(ynn_binary_multiply, 4973, 4975, 4971);
  g->Dot(85, 4976, YNN_INVALID_VALUE_ID, 4970, 1);
  g->DequantizeTensor(4970, YNN_INVALID_VALUE_ID, 4971, 4972);
  g->QuantizeTensor(4972, 8595, 4974, 86);
  g->Dequantize(86, 87, 0.08599609136581421, 0);
  g->Unary(ynn_unary_square, 87, 88);
  g->Reduce(ynn_reduce_sum, 88, 7178, {2}, true);
  g->ShapeProduct(88, 7177, {2});
  g->Binary(ynn_binary_divide, 7178, 7177, 89);
  g->Binary(ynn_binary_add, 89, 8647, 90);
  g->Unary(ynn_unary_rsqrt, 90, 91);
  g->Binary(ynn_binary_multiply, 87, 91, 92);
  g->Binary(ynn_binary_multiply, 92, 9356, 94);
  g->Binary(ynn_binary_add, 94, 69, 95);
}

// Scope: "Layer7 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 96, {0,0,7,0}, {-1,-1,1,-1});
  g->Reshape(96, 97, {1,1,256});
  g->Unary(ynn_unary_square, 97, 98);
  g->Reduce(ynn_reduce_sum, 98, 7180, {2}, true);
  g->ShapeProduct(98, 7179, {2});
  g->Binary(ynn_binary_divide, 7180, 7179, 99);
  g->Binary(ynn_binary_add, 99, 8647, 100);
  g->Unary(ynn_unary_rsqrt, 100, 101);
  g->Binary(ynn_binary_multiply, 97, 101, 102);
  g->Binary(ynn_binary_multiply, 102, 9401, 103);
  g->Binary(ynn_binary_multiply, 9441, 8651, 106);
  g->Binary(ynn_binary_add, 103, 106, 107);
  g->Binary(ynn_binary_multiply, 107, 8645, 108);
  g->Quantize(95, 109, 0.16048018634319305, 0);
  g->Transpose(9353, 4990, {1,0});
  g->Binary(ynn_binary_multiply, 4987, 4989, 4985);
  g->Dot(109, 4990, YNN_INVALID_VALUE_ID, 4984, 1);
  g->DequantizeTensor(4984, YNN_INVALID_VALUE_ID, 4985, 4986);
  g->QuantizeTensor(4986, 8595, 4988, 110);
  g->Dequantize(110, 111, 0.04675197973847389, 0);
  g->Polynomial(111, 7183, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7183, 7184);
  g->Binary(ynn_binary_add, 7184, 7161, 7181);
  g->Binary(ynn_binary_multiply, 111, 7173, 7182);
  g->Binary(ynn_binary_multiply, 7182, 7181, 112);
  g->Binary(ynn_binary_multiply, 112, 108, 113);
  g->Quantize(113, 114, 0.15748032927513123, 0);
  g->Transpose(9354, 4997, {1,0});
  g->Binary(ynn_binary_multiply, 4994, 4996, 4992);
  g->Dot(114, 4997, YNN_INVALID_VALUE_ID, 4991, 1);
  g->DequantizeTensor(4991, YNN_INVALID_VALUE_ID, 4992, 4993);
  g->QuantizeTensor(4993, 8595, 4995, 115);
  g->Dequantize(115, 116, 0.07159535586833954, 0);
  g->Unary(ynn_unary_square, 116, 117);
  g->Reduce(ynn_reduce_sum, 117, 7186, {2}, true);
  g->ShapeProduct(117, 7185, {2});
  g->Binary(ynn_binary_divide, 7186, 7185, 118);
  g->Binary(ynn_binary_add, 118, 8647, 119);
  g->Unary(ynn_unary_rsqrt, 119, 120);
  g->Binary(ynn_binary_multiply, 116, 120, 121);
  g->Binary(ynn_binary_multiply, 121, 9357, 122);
  g->Binary(ynn_binary_add, 95, 122, 123);
  g->Binary(ynn_binary_multiply, 123, 9349, 124);
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
  g->Transpose(9377, 5009, {1,0});
  g->Binary(ynn_binary_multiply, 5006, 5008, 5004);
  g->Dot(132, 5009, YNN_INVALID_VALUE_ID, 5003, 1);
  g->DequantizeTensor(5003, YNN_INVALID_VALUE_ID, 5004, 5005);
  g->QuantizeTensor(5005, 8595, 5007, 133);
  g->Dequantize(133, 134, 0.3366141617298126, 0);
  g->SplitDim(134, 135, 2, {2,256});
  g->Transpose(135, 136, {0,2,1,3});
  g->Unary(ynn_unary_square, 136, 138);
  g->Reduce(ynn_reduce_sum, 138, 7190, {3}, true);
  g->ShapeProduct(138, 7189, {3});
  g->Binary(ynn_binary_divide, 7190, 7189, 139);
  g->Binary(ynn_binary_add, 139, 8647, 140);
  g->Unary(ynn_unary_rsqrt, 140, 141);
  g->Binary(ynn_binary_multiply, 136, 141, 142);
  g->Binary(ynn_binary_multiply, 142, 9376, 143);
  g->Slice(143, 144, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(143, 145, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 145, 146);
  g->Concat({146,144}, 147, 3);
  g->Binary(ynn_binary_multiply, 143, 3141, 149);
  g->Binary(ynn_binary_multiply, 147, 4217, 150);
  g->Binary(ynn_binary_add, 149, 150, 151);
  g->Transpose(9381, 5014, {1,0});
  g->Binary(ynn_binary_multiply, 5006, 5013, 5011);
  g->Dot(132, 5014, YNN_INVALID_VALUE_ID, 5010, 1);
  g->DequantizeTensor(5010, YNN_INVALID_VALUE_ID, 5011, 5012);
  g->QuantizeTensor(5012, 8595, 5007, 152);
  g->Dequantize(152, 153, 0.3366141617298126, 0);
  g->SplitDim(153, 154, 2, {2,256});
  g->Transpose(154, 155, {0,2,1,3});
  g->Unary(ynn_unary_square, 155, 156);
  g->Reduce(ynn_reduce_sum, 156, 7196, {3}, true);
  g->ShapeProduct(156, 7195, {3});
  g->Binary(ynn_binary_divide, 7196, 7195, 157);
  g->Binary(ynn_binary_add, 157, 8647, 159);
  g->Unary(ynn_unary_rsqrt, 159, 160);
  g->Binary(ynn_binary_multiply, 155, 160, 161);
}

// Scope: "Layer8 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(151, 162, 0.005679573863744736, 0);
  g->Append(8618, 162, 9467, 2, s2, slinky::expr(int64_t{1}));
  g->View(9467, 9515, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(161, 163, 0.047244105488061905, 0);
  g->Append(8642, 163, 9491, 2, s2, slinky::expr(int64_t{1}));
  g->View(9491, 9539, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer8 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(9380, 5020, {1,0});
  g->Binary(ynn_binary_multiply, 5006, 5019, 5016);
  g->Dot(132, 5020, YNN_INVALID_VALUE_ID, 5015, 1);
  g->DequantizeTensor(5015, YNN_INVALID_VALUE_ID, 5016, 5017);
  g->QuantizeTensor(5017, 8595, 5018, 165);
  g->Dequantize(165, 166, 0.31102362275123596, 0);
  g->SplitDim(166, 167, 2, {8,256});
  g->Transpose(167, 168, {0,2,1,3});
  g->Unary(ynn_unary_square, 168, 169);
  g->Reduce(ynn_reduce_sum, 169, 7198, {3}, true);
  g->ShapeProduct(169, 7197, {3});
  g->Binary(ynn_binary_divide, 7198, 7197, 170);
  g->Binary(ynn_binary_add, 170, 8647, 171);
  g->Unary(ynn_unary_rsqrt, 171, 172);
  g->Binary(ynn_binary_multiply, 168, 172, 173);
  g->Binary(ynn_binary_multiply, 173, 9379, 174);
  g->Slice(174, 176, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(174, 177, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 177, 178);
  g->Concat({178,176}, 179, 3);
  g->Binary(ynn_binary_multiply, 174, 3141, 180);
  g->Binary(ynn_binary_multiply, 179, 4217, 181);
  g->Binary(ynn_binary_add, 180, 181, 182);
}

// Scope: "Layer8 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9515, 183, 0.005679573863744736, 0);
  g->Dequantize(9539, 184, 0.047244105488061905, 0);
  g->Slice(182, 185, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(183, 187, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(184, 188, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(185, 187, 189, false, true);
  g->Mask(189, 8734, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8734, 7202, {-1}, true);
  g->Binary(ynn_binary_subtract, 8734, 7202, 7199);
  g->Unary(ynn_unary_exp, 7199, 7200);
  g->Reduce(ynn_reduce_sum, 7200, 7203, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 7203, 7201);
  g->Binary(ynn_binary_multiply, 7200, 7201, 190);
  g->Matmul(190, 188, 191, false, false);
  g->Slice(182, 192, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(183, 193, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(184, 194, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(192, 193, 195, false, true);
  g->Mask(195, 8735, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8735, 7207, {-1}, true);
  g->Binary(ynn_binary_subtract, 8735, 7207, 7204);
  g->Unary(ynn_unary_exp, 7204, 7205);
  g->Reduce(ynn_reduce_sum, 7205, 7208, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 7208, 7206);
  g->Binary(ynn_binary_multiply, 7205, 7206, 197);
  g->Matmul(197, 194, 198, false, false);
  g->Concat({191,198}, 199, 1);
}

// Scope: "Layer8 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(199, 200, {0,2,1,3});
  g->FuseDims(200, 201, 2, 2);
  g->Quantize(201, 202, 0.023375993594527245, 0);
  g->Transpose(9378, 5034, {1,0});
  g->Binary(ynn_binary_multiply, 5031, 5033, 5029);
  g->Dot(202, 5034, YNN_INVALID_VALUE_ID, 5028, 1);
  g->DequantizeTensor(5028, YNN_INVALID_VALUE_ID, 5029, 5030);
  g->QuantizeTensor(5030, 8595, 5032, 203);
  g->Dequantize(203, 204, 0.04781534895300865, 0);
}

// Scope: "Layer8 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 124, 125);
  g->Reduce(ynn_reduce_sum, 125, 7188, {2}, true);
  g->ShapeProduct(125, 7187, {2});
  g->Binary(ynn_binary_divide, 7188, 7187, 127);
  g->Binary(ynn_binary_add, 127, 8647, 128);
  g->Unary(ynn_unary_rsqrt, 128, 129);
  g->Binary(ynn_binary_multiply, 124, 129, 130);
  g->Binary(ynn_binary_multiply, 130, 9365, 131);
  BuildLayer8AttentionKvProjection(ctx);
  BuildLayer8AttentionCacheUpdate(ctx);
  BuildLayer8AttentionQueryProjection(ctx);
  BuildLayer8AttentionSdpa(ctx);
  BuildLayer8AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 204, 205);
  g->Reduce(ynn_reduce_sum, 205, 7212, {2}, true);
  g->ShapeProduct(205, 7211, {2});
  g->Binary(ynn_binary_divide, 7212, 7211, 208);
  g->Binary(ynn_binary_add, 208, 8647, 209);
  g->Unary(ynn_unary_rsqrt, 209, 210);
  g->Binary(ynn_binary_multiply, 204, 210, 211);
  g->Binary(ynn_binary_multiply, 211, 9372, 212);
  g->Binary(ynn_binary_add, 212, 124, 213);
}

// Scope: "Layer8 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 213, 214);
  g->Reduce(ynn_reduce_sum, 214, 7214, {2}, true);
  g->ShapeProduct(214, 7213, {2});
  g->Binary(ynn_binary_divide, 7214, 7213, 215);
  g->Binary(ynn_binary_add, 215, 8647, 216);
  g->Unary(ynn_unary_rsqrt, 216, 217);
  g->Binary(ynn_binary_multiply, 213, 217, 219);
  g->Binary(ynn_binary_multiply, 219, 9375, 220);
  g->Quantize(220, 221, 0.028420308604836464, 0);
  g->Transpose(9369, 5048, {1,0});
  g->Binary(ynn_binary_multiply, 5045, 5047, 5043);
  g->Dot(221, 5048, YNN_INVALID_VALUE_ID, 5042, 1);
  g->DequantizeTensor(5042, YNN_INVALID_VALUE_ID, 5043, 5044);
  g->QuantizeTensor(5044, 8595, 5046, 222);
  g->Dequantize(222, 223, 0.04625985398888588, 0);
  g->Transpose(9368, 5053, {1,0});
  g->Binary(ynn_binary_multiply, 5045, 5052, 5050);
  g->Dot(221, 5053, YNN_INVALID_VALUE_ID, 5049, 1);
  g->DequantizeTensor(5049, YNN_INVALID_VALUE_ID, 5050, 5051);
  g->QuantizeTensor(5051, 8595, 5046, 224);
  g->Dequantize(224, 225, 0.04625985398888588, 0);
  g->Polynomial(225, 7217, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7217, 7218);
  g->Binary(ynn_binary_add, 7218, 7161, 7215);
  g->Binary(ynn_binary_multiply, 225, 7173, 7216);
  g->Binary(ynn_binary_multiply, 7216, 7215, 226);
  g->Binary(ynn_binary_multiply, 223, 226, 227);
  g->Quantize(227, 229, 0.11958662420511246, 0);
  g->Transpose(9367, 5060, {1,0});
  g->Binary(ynn_binary_multiply, 5057, 5059, 5055);
  g->Dot(229, 5060, YNN_INVALID_VALUE_ID, 5054, 1);
  g->DequantizeTensor(5054, YNN_INVALID_VALUE_ID, 5055, 5056);
  g->QuantizeTensor(5056, 8595, 5058, 230);
  g->Dequantize(230, 231, 0.07705982774496078, 0);
  g->Unary(ynn_unary_square, 231, 232);
  g->Reduce(ynn_reduce_sum, 232, 7220, {2}, true);
  g->ShapeProduct(232, 7219, {2});
  g->Binary(ynn_binary_divide, 7220, 7219, 233);
  g->Binary(ynn_binary_add, 233, 8647, 234);
  g->Unary(ynn_unary_rsqrt, 234, 235);
  g->Binary(ynn_binary_multiply, 231, 235, 236);
  g->Binary(ynn_binary_multiply, 236, 9373, 237);
  g->Binary(ynn_binary_add, 237, 213, 238);
}

// Scope: "Layer8 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 240, {0,0,8,0}, {-1,-1,1,-1});
  g->Reshape(240, 241, {1,1,256});
  g->Unary(ynn_unary_square, 241, 242);
  g->Reduce(ynn_reduce_sum, 242, 7222, {2}, true);
  g->ShapeProduct(242, 7221, {2});
  g->Binary(ynn_binary_divide, 7222, 7221, 243);
  g->Binary(ynn_binary_add, 243, 8647, 244);
  g->Unary(ynn_unary_rsqrt, 244, 245);
  g->Binary(ynn_binary_multiply, 241, 245, 246);
  g->Binary(ynn_binary_multiply, 246, 9401, 247);
  g->Binary(ynn_binary_multiply, 9442, 8651, 248);
  g->Binary(ynn_binary_add, 247, 248, 249);
  g->Binary(ynn_binary_multiply, 249, 8645, 251);
  g->Quantize(238, 252, 0.4868268370628357, 0);
  g->Transpose(9370, 5067, {1,0});
  g->Binary(ynn_binary_multiply, 5064, 5066, 5062);
  g->Dot(252, 5067, YNN_INVALID_VALUE_ID, 5061, 1);
  g->DequantizeTensor(5061, YNN_INVALID_VALUE_ID, 5062, 5063);
  g->QuantizeTensor(5063, 8595, 5065, 253);
  g->Dequantize(253, 254, 0.03026575781404972, 0);
  g->Polynomial(254, 7225, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7225, 7226);
  g->Binary(ynn_binary_add, 7226, 7161, 7223);
  g->Binary(ynn_binary_multiply, 254, 7173, 7224);
  g->Binary(ynn_binary_multiply, 7224, 7223, 255);
  g->Binary(ynn_binary_multiply, 255, 251, 256);
  g->Quantize(256, 257, 0.12795276939868927, 0);
  g->Transpose(9371, 5074, {1,0});
  g->Binary(ynn_binary_multiply, 5071, 5073, 5069);
  g->Dot(257, 5074, YNN_INVALID_VALUE_ID, 5068, 1);
  g->DequantizeTensor(5068, YNN_INVALID_VALUE_ID, 5069, 5070);
  g->QuantizeTensor(5070, 8595, 5072, 258);
  g->Dequantize(258, 259, 0.04510452225804329, 0);
  g->Unary(ynn_unary_square, 259, 260);
  g->Reduce(ynn_reduce_sum, 260, 7228, {2}, true);
  g->ShapeProduct(260, 7227, {2});
  g->Binary(ynn_binary_divide, 7228, 7227, 262);
  g->Binary(ynn_binary_add, 262, 8647, 263);
  g->Unary(ynn_unary_rsqrt, 263, 264);
  g->Binary(ynn_binary_multiply, 259, 264, 265);
  g->Binary(ynn_binary_multiply, 265, 9374, 266);
  g->Binary(ynn_binary_add, 238, 266, 267);
  g->Binary(ynn_binary_multiply, 267, 9366, 268);
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
  g->Transpose(9394, 5081, {1,0});
  g->Binary(ynn_binary_multiply, 5078, 5080, 5076);
  g->Dot(276, 5081, YNN_INVALID_VALUE_ID, 5075, 1);
  g->DequantizeTensor(5075, YNN_INVALID_VALUE_ID, 5076, 5077);
  g->QuantizeTensor(5077, 8595, 5079, 277);
  g->Dequantize(277, 278, 0.11663386225700378, 0);
  g->SplitDim(278, 279, 2, {2,256});
  g->Transpose(279, 280, {0,2,1,3});
  g->Unary(ynn_unary_square, 280, 281);
  g->Reduce(ynn_reduce_sum, 281, 7232, {3}, true);
  g->ShapeProduct(281, 7231, {3});
  g->Binary(ynn_binary_divide, 7232, 7231, 282);
  g->Binary(ynn_binary_add, 282, 8647, 284);
  g->Unary(ynn_unary_rsqrt, 284, 285);
  g->Binary(ynn_binary_multiply, 280, 285, 286);
  g->Binary(ynn_binary_multiply, 286, 9393, 287);
  g->Slice(287, 288, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(287, 289, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 289, 290);
  g->Concat({290,288}, 291, 3);
  g->Binary(ynn_binary_multiply, 287, 3141, 292);
  g->Binary(ynn_binary_multiply, 291, 4217, 293);
  g->Binary(ynn_binary_add, 292, 293, 295);
  g->Transpose(9398, 5086, {1,0});
  g->Binary(ynn_binary_multiply, 5078, 5085, 5083);
  g->Dot(276, 5086, YNN_INVALID_VALUE_ID, 5082, 1);
  g->DequantizeTensor(5082, YNN_INVALID_VALUE_ID, 5083, 5084);
  g->QuantizeTensor(5084, 8595, 5079, 296);
  g->Dequantize(296, 297, 0.11663386225700378, 0);
  g->SplitDim(297, 298, 2, {2,256});
  g->Transpose(298, 299, {0,2,1,3});
  g->Unary(ynn_unary_square, 299, 300);
  g->Reduce(ynn_reduce_sum, 300, 7234, {3}, true);
  g->ShapeProduct(300, 7233, {3});
  g->Binary(ynn_binary_divide, 7234, 7233, 301);
  g->Binary(ynn_binary_add, 301, 8647, 302);
  g->Unary(ynn_unary_rsqrt, 302, 303);
  g->Binary(ynn_binary_multiply, 299, 303, 305);
}

// Scope: "Layer9 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(295, 306, 0.005719248205423355, 0);
  g->Append(8619, 306, 9468, 2, s2, slinky::expr(int64_t{1}));
  g->View(9468, 9516, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(305, 307, 0.047244105488061905, 0);
  g->Append(8643, 307, 9492, 2, s2, slinky::expr(int64_t{1}));
  g->View(9492, 9540, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer9 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(9397, 5092, {1,0});
  g->Binary(ynn_binary_multiply, 5078, 5091, 5088);
  g->Dot(276, 5092, YNN_INVALID_VALUE_ID, 5087, 1);
  g->DequantizeTensor(5087, YNN_INVALID_VALUE_ID, 5088, 5089);
  g->QuantizeTensor(5089, 8595, 5090, 308);
  g->Dequantize(308, 309, 0.1058070957660675, 0);
  g->SplitDim(309, 312, 2, {8,256});
  g->Transpose(312, 313, {0,2,1,3});
  g->Unary(ynn_unary_square, 313, 314);
  g->Reduce(ynn_reduce_sum, 314, 7238, {3}, true);
  g->ShapeProduct(314, 7237, {3});
  g->Binary(ynn_binary_divide, 7238, 7237, 315);
  g->Binary(ynn_binary_add, 315, 8647, 316);
  g->Unary(ynn_unary_rsqrt, 316, 317);
  g->Binary(ynn_binary_multiply, 313, 317, 318);
  g->Binary(ynn_binary_multiply, 318, 9396, 319);
  g->Slice(319, 320, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(319, 321, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 321, 323);
  g->Concat({323,320}, 324, 3);
  g->Binary(ynn_binary_multiply, 319, 3141, 325);
  g->Binary(ynn_binary_multiply, 324, 4217, 326);
  g->Binary(ynn_binary_add, 325, 326, 327);
}

// Scope: "Layer9 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9516, 328, 0.005719248205423355, 0);
  g->Dequantize(9540, 329, 0.047244105488061905, 0);
  g->Slice(327, 330, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(328, 331, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(329, 332, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(330, 331, 334, false, true);
  g->Mask(334, 8736, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8736, 7242, {-1}, true);
  g->Binary(ynn_binary_subtract, 8736, 7242, 7239);
  g->Unary(ynn_unary_exp, 7239, 7240);
  g->Reduce(ynn_reduce_sum, 7240, 7243, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 7243, 7241);
  g->Binary(ynn_binary_multiply, 7240, 7241, 335);
  g->Matmul(335, 332, 336, false, false);
  g->Slice(327, 337, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(328, 338, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(329, 339, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(337, 338, 340, false, true);
  g->Mask(340, 8737, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8737, 7247, {-1}, true);
  g->Binary(ynn_binary_subtract, 8737, 7247, 7244);
  g->Unary(ynn_unary_exp, 7244, 7245);
  g->Reduce(ynn_reduce_sum, 7245, 7248, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 7248, 7246);
  g->Binary(ynn_binary_multiply, 7245, 7246, 341);
  g->Matmul(341, 339, 343, false, false);
  g->Concat({336,343}, 344, 1);
}

// Scope: "Layer9 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(344, 345, {0,2,1,3});
  g->FuseDims(345, 346, 2, 2);
  g->Quantize(346, 347, 0.023375993594527245, 0);
  g->Transpose(9395, 5098, {1,0});
  g->Binary(ynn_binary_multiply, 5031, 5097, 5094);
  g->Dot(347, 5098, YNN_INVALID_VALUE_ID, 5093, 1);
  g->DequantizeTensor(5093, YNN_INVALID_VALUE_ID, 5094, 5095);
  g->QuantizeTensor(5095, 8595, 5096, 348);
  g->Dequantize(348, 349, 0.04783705249428749, 0);
}

// Scope: "Layer9 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 268, 269);
  g->Reduce(ynn_reduce_sum, 269, 7230, {2}, true);
  g->ShapeProduct(269, 7229, {2});
  g->Binary(ynn_binary_divide, 7230, 7229, 270);
  g->Binary(ynn_binary_add, 270, 8647, 271);
  g->Unary(ynn_unary_rsqrt, 271, 273);
  g->Binary(ynn_binary_multiply, 268, 273, 274);
  g->Binary(ynn_binary_multiply, 274, 9382, 275);
  BuildLayer9AttentionKvProjection(ctx);
  BuildLayer9AttentionCacheUpdate(ctx);
  BuildLayer9AttentionQueryProjection(ctx);
  BuildLayer9AttentionSdpa(ctx);
  BuildLayer9AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 349, 350);
  g->Reduce(ynn_reduce_sum, 350, 7250, {2}, true);
  g->ShapeProduct(350, 7249, {2});
  g->Binary(ynn_binary_divide, 7250, 7249, 351);
  g->Binary(ynn_binary_add, 351, 8647, 352);
  g->Unary(ynn_unary_rsqrt, 352, 354);
  g->Binary(ynn_binary_multiply, 349, 354, 355);
  g->Binary(ynn_binary_multiply, 355, 9389, 356);
  g->Binary(ynn_binary_add, 356, 268, 357);
}

// Scope: "Layer9 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 357, 358);
  g->Reduce(ynn_reduce_sum, 358, 7252, {2}, true);
  g->ShapeProduct(358, 7251, {2});
  g->Binary(ynn_binary_divide, 7252, 7251, 359);
  g->Binary(ynn_binary_add, 359, 8647, 360);
  g->Unary(ynn_unary_rsqrt, 360, 361);
  g->Binary(ynn_binary_multiply, 357, 361, 362);
  g->Binary(ynn_binary_multiply, 362, 9392, 363);
  g->Quantize(363, 365, 0.017706703394651413, 0);
  g->Transpose(9386, 5105, {1,0});
  g->Binary(ynn_binary_multiply, 5102, 5104, 5100);
  g->Dot(365, 5105, YNN_INVALID_VALUE_ID, 5099, 1);
  g->DequantizeTensor(5099, YNN_INVALID_VALUE_ID, 5100, 5101);
  g->QuantizeTensor(5101, 8595, 5103, 366);
  g->Dequantize(366, 367, 0.025836624205112457, 0);
  g->Transpose(9385, 5110, {1,0});
  g->Binary(ynn_binary_multiply, 5102, 5109, 5107);
  g->Dot(365, 5110, YNN_INVALID_VALUE_ID, 5106, 1);
  g->DequantizeTensor(5106, YNN_INVALID_VALUE_ID, 5107, 5108);
  g->QuantizeTensor(5108, 8595, 5103, 368);
  g->Dequantize(368, 369, 0.025836624205112457, 0);
  g->Polynomial(369, 7255, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7255, 7256);
  g->Binary(ynn_binary_add, 7256, 7161, 7253);
  g->Binary(ynn_binary_multiply, 369, 7173, 7254);
  g->Binary(ynn_binary_multiply, 7254, 7253, 370);
  g->Binary(ynn_binary_multiply, 367, 370, 371);
  g->Quantize(371, 372, 0.04773623123764992, 0);
  g->Transpose(9384, 5117, {1,0});
  g->Binary(ynn_binary_multiply, 5114, 5116, 5112);
  g->Dot(372, 5117, YNN_INVALID_VALUE_ID, 5111, 1);
  g->DequantizeTensor(5111, YNN_INVALID_VALUE_ID, 5112, 5113);
  g->QuantizeTensor(5113, 8595, 5115, 373);
  g->Dequantize(373, 375, 0.04407493770122528, 0);
  g->Unary(ynn_unary_square, 375, 376);
  g->Reduce(ynn_reduce_sum, 376, 7258, {2}, true);
  g->ShapeProduct(376, 7257, {2});
  g->Binary(ynn_binary_divide, 7258, 7257, 377);
  g->Binary(ynn_binary_add, 377, 8647, 378);
  g->Unary(ynn_unary_rsqrt, 378, 379);
  g->Binary(ynn_binary_multiply, 375, 379, 380);
  g->Binary(ynn_binary_multiply, 380, 9390, 381);
  g->Binary(ynn_binary_add, 381, 357, 382);
}

// Scope: "Layer9 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 383, {0,0,9,0}, {-1,-1,1,-1});
  g->Reshape(383, 384, {1,1,256});
  g->Unary(ynn_unary_square, 384, 386);
  g->Reduce(ynn_reduce_sum, 386, 7260, {2}, true);
  g->ShapeProduct(386, 7259, {2});
  g->Binary(ynn_binary_divide, 7260, 7259, 387);
  g->Binary(ynn_binary_add, 387, 8647, 388);
  g->Unary(ynn_unary_rsqrt, 388, 389);
  g->Binary(ynn_binary_multiply, 384, 389, 390);
  g->Binary(ynn_binary_multiply, 390, 9401, 391);
  g->Binary(ynn_binary_multiply, 9443, 8651, 392);
  g->Binary(ynn_binary_add, 391, 392, 393);
  g->Binary(ynn_binary_multiply, 393, 8645, 394);
  g->Quantize(382, 395, 0.20032060146331787, 0);
  g->Transpose(9387, 5131, {1,0});
  g->Binary(ynn_binary_multiply, 5128, 5130, 5126);
  g->Dot(395, 5131, YNN_INVALID_VALUE_ID, 5125, 1);
  g->DequantizeTensor(5125, YNN_INVALID_VALUE_ID, 5126, 5127);
  g->QuantizeTensor(5127, 8595, 5129, 397);
  g->Dequantize(397, 398, 0.047244105488061905, 0);
  g->Polynomial(398, 7263, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7263, 7264);
  g->Binary(ynn_binary_add, 7264, 7161, 7261);
  g->Binary(ynn_binary_multiply, 398, 7173, 7262);
  g->Binary(ynn_binary_multiply, 7262, 7261, 399);
  g->Binary(ynn_binary_multiply, 399, 394, 400);
  g->Quantize(400, 401, 0.3326771557331085, 0);
  g->Transpose(9388, 5138, {1,0});
  g->Binary(ynn_binary_multiply, 5135, 5137, 5133);
  g->Dot(401, 5138, YNN_INVALID_VALUE_ID, 5132, 1);
  g->DequantizeTensor(5132, YNN_INVALID_VALUE_ID, 5133, 5134);
  g->QuantizeTensor(5134, 8595, 5136, 402);
  g->Dequantize(402, 403, 0.11236792802810669, 0);
  g->Unary(ynn_unary_square, 403, 404);
  g->Reduce(ynn_reduce_sum, 404, 7266, {2}, true);
  g->ShapeProduct(404, 7265, {2});
  g->Binary(ynn_binary_divide, 7266, 7265, 405);
  g->Binary(ynn_binary_add, 405, 8647, 406);
  g->Unary(ynn_unary_rsqrt, 406, 408);
  g->Binary(ynn_binary_multiply, 403, 408, 409);
  g->Binary(ynn_binary_multiply, 409, 9391, 410);
  g->Binary(ynn_binary_add, 382, 410, 411);
  g->Binary(ynn_binary_multiply, 411, 9383, 412);
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
  g->Transpose(8785, 5145, {1,0});
  g->Binary(ynn_binary_multiply, 5142, 5144, 5140);
  g->Dot(421, 5145, YNN_INVALID_VALUE_ID, 5139, 1);
  g->DequantizeTensor(5139, YNN_INVALID_VALUE_ID, 5140, 5141);
  g->QuantizeTensor(5141, 8595, 5143, 422);
  g->Dequantize(422, 423, 0.06446851044893265, 0);
  g->SplitDim(423, 424, 2, {2,256});
  g->Transpose(424, 425, {0,2,1,3});
  g->Unary(ynn_unary_square, 425, 426);
  g->Reduce(ynn_reduce_sum, 426, 7274, {3}, true);
  g->ShapeProduct(426, 7273, {3});
  g->Binary(ynn_binary_divide, 7274, 7273, 427);
  g->Binary(ynn_binary_add, 427, 8647, 428);
  g->Unary(ynn_unary_rsqrt, 428, 429);
  g->Binary(ynn_binary_multiply, 425, 429, 431);
  g->Binary(ynn_binary_multiply, 431, 8784, 432);
  g->Slice(432, 433, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(432, 434, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 434, 435);
  g->Concat({435,433}, 436, 3);
  g->Binary(ynn_binary_multiply, 432, 3141, 437);
  g->Binary(ynn_binary_multiply, 436, 4217, 438);
  g->Binary(ynn_binary_add, 437, 438, 439);
  g->Transpose(8789, 5150, {1,0});
  g->Binary(ynn_binary_multiply, 5142, 5149, 5147);
  g->Dot(421, 5150, YNN_INVALID_VALUE_ID, 5146, 1);
  g->DequantizeTensor(5146, YNN_INVALID_VALUE_ID, 5147, 5148);
  g->QuantizeTensor(5148, 8595, 5143, 441);
  g->Dequantize(441, 442, 0.06446851044893265, 0);
  g->SplitDim(442, 443, 2, {2,256});
  g->Transpose(443, 444, {0,2,1,3});
  g->Unary(ynn_unary_square, 444, 445);
  g->Reduce(ynn_reduce_sum, 445, 7276, {3}, true);
  g->ShapeProduct(445, 7275, {3});
  g->Binary(ynn_binary_divide, 7276, 7275, 446);
  g->Binary(ynn_binary_add, 446, 8647, 447);
  g->Unary(ynn_unary_rsqrt, 447, 448);
  g->Binary(ynn_binary_multiply, 444, 448, 449);
}

// Scope: "Layer10 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(439, 450, 0.0057654301635921, 0);
  g->Append(8598, 450, 9447, 2, s2, slinky::expr(int64_t{1}));
  g->View(9447, 9495, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(449, 452, 0.047244105488061905, 0);
  g->Append(8622, 452, 9471, 2, s2, slinky::expr(int64_t{1}));
  g->View(9471, 9519, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer10 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(8788, 5163, {1,0});
  g->Binary(ynn_binary_multiply, 5142, 5162, 5159);
  g->Dot(421, 5163, YNN_INVALID_VALUE_ID, 5158, 1);
  g->DequantizeTensor(5158, YNN_INVALID_VALUE_ID, 5159, 5160);
  g->QuantizeTensor(5160, 8595, 5161, 453);
  g->Dequantize(453, 454, 0.06840551644563675, 0);
  g->SplitDim(454, 455, 2, {8,256});
  g->Transpose(455, 456, {0,2,1,3});
  g->Unary(ynn_unary_square, 456, 458);
  g->Reduce(ynn_reduce_sum, 458, 7278, {3}, true);
  g->ShapeProduct(458, 7277, {3});
  g->Binary(ynn_binary_divide, 7278, 7277, 459);
  g->Binary(ynn_binary_add, 459, 8647, 460);
  g->Unary(ynn_unary_rsqrt, 460, 461);
  g->Binary(ynn_binary_multiply, 456, 461, 462);
  g->Binary(ynn_binary_multiply, 462, 8787, 463);
  g->Slice(463, 464, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(463, 465, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 465, 466);
  g->Concat({466,464}, 467, 3);
  g->Binary(ynn_binary_multiply, 463, 3141, 469);
  g->Binary(ynn_binary_multiply, 467, 4217, 470);
  g->Binary(ynn_binary_add, 469, 470, 471);
}

// Scope: "Layer10 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9495, 472, 0.0057654301635921, 0);
  g->Dequantize(9519, 473, 0.047244105488061905, 0);
  g->Slice(471, 474, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(472, 475, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(473, 476, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(474, 475, 477, false, true);
  g->Mask(477, 8656, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8656, 7284, {-1}, true);
  g->Binary(ynn_binary_subtract, 8656, 7284, 7281);
  g->Unary(ynn_unary_exp, 7281, 7282);
  g->Reduce(ynn_reduce_sum, 7282, 7285, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 7285, 7283);
  g->Binary(ynn_binary_multiply, 7282, 7283, 479);
  g->Matmul(479, 476, 480, false, false);
  g->Slice(471, 481, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(472, 482, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(473, 483, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(481, 482, 484, false, true);
  g->Mask(484, 8657, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8657, 7289, {-1}, true);
  g->Binary(ynn_binary_subtract, 8657, 7289, 7286);
  g->Unary(ynn_unary_exp, 7286, 7287);
  g->Reduce(ynn_reduce_sum, 7287, 7290, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 7290, 7288);
  g->Binary(ynn_binary_multiply, 7287, 7288, 485);
  g->Matmul(485, 483, 486, false, false);
  g->Concat({480,486}, 487, 1);
}

// Scope: "Layer10 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(487, 489, {0,2,1,3});
  g->FuseDims(489, 490, 2, 2);
  g->Quantize(490, 491, 0.02362205646932125, 0);
  g->Transpose(8786, 5170, {1,0});
  g->Binary(ynn_binary_multiply, 5167, 5169, 5165);
  g->Dot(491, 5170, YNN_INVALID_VALUE_ID, 5164, 1);
  g->DequantizeTensor(5164, YNN_INVALID_VALUE_ID, 5165, 5166);
  g->QuantizeTensor(5166, 8595, 5168, 492);
  g->Dequantize(492, 493, 0.09525793045759201, 0);
}

// Scope: "Layer10 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 412, 413);
  g->Reduce(ynn_reduce_sum, 413, 7268, {2}, true);
  g->ShapeProduct(413, 7267, {2});
  g->Binary(ynn_binary_divide, 7268, 7267, 414);
  g->Binary(ynn_binary_add, 414, 8647, 415);
  g->Unary(ynn_unary_rsqrt, 415, 416);
  g->Binary(ynn_binary_multiply, 412, 416, 417);
  g->Binary(ynn_binary_multiply, 417, 8773, 420);
  BuildLayer10AttentionKvProjection(ctx);
  BuildLayer10AttentionCacheUpdate(ctx);
  BuildLayer10AttentionQueryProjection(ctx);
  BuildLayer10AttentionSdpa(ctx);
  BuildLayer10AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 493, 494);
  g->Reduce(ynn_reduce_sum, 494, 7292, {2}, true);
  g->ShapeProduct(494, 7291, {2});
  g->Binary(ynn_binary_divide, 7292, 7291, 495);
  g->Binary(ynn_binary_add, 495, 8647, 496);
  g->Unary(ynn_unary_rsqrt, 496, 497);
  g->Binary(ynn_binary_multiply, 493, 497, 498);
  g->Binary(ynn_binary_multiply, 498, 8780, 500);
  g->Binary(ynn_binary_add, 500, 412, 501);
}

// Scope: "Layer10 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 501, 502);
  g->Reduce(ynn_reduce_sum, 502, 7294, {2}, true);
  g->ShapeProduct(502, 7293, {2});
  g->Binary(ynn_binary_divide, 7294, 7293, 503);
  g->Binary(ynn_binary_add, 503, 8647, 504);
  g->Unary(ynn_unary_rsqrt, 504, 505);
  g->Binary(ynn_binary_multiply, 501, 505, 506);
  g->Binary(ynn_binary_multiply, 506, 8783, 507);
  g->Quantize(507, 508, 0.015853581950068474, 0);
  g->Transpose(8777, 5176, {1,0});
  g->Binary(ynn_binary_multiply, 5174, 5175, 5172);
  g->Dot(508, 5176, YNN_INVALID_VALUE_ID, 5171, 1);
  g->DequantizeTensor(5171, YNN_INVALID_VALUE_ID, 5172, 5173);
  g->QuantizeTensor(5173, 8595, 5031, 509);
  g->Dequantize(509, 511, 0.023375993594527245, 0);
  g->Transpose(8776, 5181, {1,0});
  g->Binary(ynn_binary_multiply, 5174, 5180, 5178);
  g->Dot(508, 5181, YNN_INVALID_VALUE_ID, 5177, 1);
  g->DequantizeTensor(5177, YNN_INVALID_VALUE_ID, 5178, 5179);
  g->QuantizeTensor(5179, 8595, 5031, 512);
  g->Dequantize(512, 513, 0.023375993594527245, 0);
  g->Polynomial(513, 7297, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7297, 7298);
  g->Binary(ynn_binary_add, 7298, 7161, 7295);
  g->Binary(ynn_binary_multiply, 513, 7173, 7296);
  g->Binary(ynn_binary_multiply, 7296, 7295, 514);
  g->Binary(ynn_binary_multiply, 511, 514, 515);
  g->Quantize(515, 516, 0.041338592767715454, 0);
  g->Transpose(8775, 5188, {1,0});
  g->Binary(ynn_binary_multiply, 5185, 5187, 5183);
  g->Dot(516, 5188, YNN_INVALID_VALUE_ID, 5182, 1);
  g->DequantizeTensor(5182, YNN_INVALID_VALUE_ID, 5183, 5184);
  g->QuantizeTensor(5184, 8595, 5186, 517);
  g->Dequantize(517, 518, 0.04055152088403702, 0);
  g->Unary(ynn_unary_square, 518, 519);
  g->Reduce(ynn_reduce_sum, 519, 7300, {2}, true);
  g->ShapeProduct(519, 7299, {2});
  g->Binary(ynn_binary_divide, 7300, 7299, 522);
  g->Binary(ynn_binary_add, 522, 8647, 523);
  g->Unary(ynn_unary_rsqrt, 523, 524);
  g->Binary(ynn_binary_multiply, 518, 524, 525);
  g->Binary(ynn_binary_multiply, 525, 8781, 526);
  g->Binary(ynn_binary_add, 526, 501, 527);
}

// Scope: "Layer10 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 528, {0,0,10,0}, {-1,-1,1,-1});
  g->Reshape(528, 529, {1,1,256});
  g->Unary(ynn_unary_square, 529, 530);
  g->Reduce(ynn_reduce_sum, 530, 7302, {2}, true);
  g->ShapeProduct(530, 7301, {2});
  g->Binary(ynn_binary_divide, 7302, 7301, 531);
  g->Binary(ynn_binary_add, 531, 8647, 533);
  g->Unary(ynn_unary_rsqrt, 533, 534);
  g->Binary(ynn_binary_multiply, 529, 534, 535);
  g->Binary(ynn_binary_multiply, 535, 9401, 536);
  g->Binary(ynn_binary_multiply, 9404, 8651, 537);
  g->Binary(ynn_binary_add, 536, 537, 538);
  g->Binary(ynn_binary_multiply, 538, 8645, 539);
  g->Quantize(527, 540, 0.16557246446609497, 0);
  g->Transpose(8778, 5195, {1,0});
  g->Binary(ynn_binary_multiply, 5192, 5194, 5190);
  g->Dot(540, 5195, YNN_INVALID_VALUE_ID, 5189, 1);
  g->DequantizeTensor(5189, YNN_INVALID_VALUE_ID, 5190, 5191);
  g->QuantizeTensor(5191, 8595, 5193, 541);
  g->Dequantize(541, 542, 0.10039370507001877, 0);
  g->Polynomial(542, 7305, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7305, 7306);
  g->Binary(ynn_binary_add, 7306, 7161, 7303);
  g->Binary(ynn_binary_multiply, 542, 7173, 7304);
  g->Binary(ynn_binary_multiply, 7304, 7303, 544);
  g->Binary(ynn_binary_multiply, 544, 539, 545);
  g->Quantize(545, 546, 0.32677164673805237, 0);
  g->Transpose(8779, 5202, {1,0});
  g->Binary(ynn_binary_multiply, 5199, 5201, 5197);
  g->Dot(546, 5202, YNN_INVALID_VALUE_ID, 5196, 1);
  g->DequantizeTensor(5196, YNN_INVALID_VALUE_ID, 5197, 5198);
  g->QuantizeTensor(5198, 8595, 5200, 547);
  g->Dequantize(547, 548, 0.11847137659788132, 0);
  g->Unary(ynn_unary_square, 548, 549);
  g->Reduce(ynn_reduce_sum, 549, 7308, {2}, true);
  g->ShapeProduct(549, 7307, {2});
  g->Binary(ynn_binary_divide, 7308, 7307, 550);
  g->Binary(ynn_binary_add, 550, 8647, 551);
  g->Unary(ynn_unary_rsqrt, 551, 552);
  g->Binary(ynn_binary_multiply, 548, 552, 553);
  g->Binary(ynn_binary_multiply, 553, 8782, 555);
  g->Binary(ynn_binary_add, 527, 555, 556);
  g->Binary(ynn_binary_multiply, 556, 8774, 557);
}

// Scope: "Layer10"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10(Context& ctx) {
  BuildLayer10Attention(ctx);
  BuildLayer10Mlp(ctx);
  BuildLayer10PerLayerEmbedding(ctx);
}

}  // namespace BuildGemma4DecodeSource
