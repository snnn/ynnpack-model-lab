// Generated YNNPACK builder; do not edit.
#include "gemma4_decode_builder.h"

namespace BuildGemma4DecodeSource {

// Scope: "Layer4 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(4610, 4611, 0.20282812416553497, 0);
  g->Transpose(9413, 7112, {1,0});
  g->Binary(ynn_binary_multiply, 7109, 7111, 7107);
  g->Dot(4611, 7112, YNN_INVALID_VALUE_ID, 7106, 1);
  g->DequantizeTensor(7106, YNN_INVALID_VALUE_ID, 7107, 7108);
  g->QuantizeTensor(7108, 8727, 7110, 4612);
  g->Dequantize(4612, 4613, 0.16338583827018738, 0);
  g->SplitDim(4613, 4614, 2, {2,256});
  g->FuseDims(4614, 4616, 1, 2);
  g->SplitDim(4616, 4615, 1, {2,1});
  g->Unary(ynn_unary_square, 4615, 4617);
  g->Reduce(ynn_reduce_sum, 4617, 8604, {3}, true);
  g->ShapeProduct(4617, 8603, {3});
  g->Binary(ynn_binary_divide, 8604, 8603, 4618);
  g->Binary(ynn_binary_add, 4618, 8779, 4620);
  g->Unary(ynn_unary_rsqrt, 4620, 4621);
  g->Binary(ynn_binary_multiply, 4615, 4621, 4622);
  g->Binary(ynn_binary_multiply, 4622, 9412, 4623);
  g->Slice(4623, 4624, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(4623, 4625, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 4625, 4626);
  g->Concat({4626,4624}, 4627, 3);
  g->Binary(ynn_binary_multiply, 4623, 3231, 4628);
  g->Binary(ynn_binary_multiply, 4627, 4329, 4629);
  g->Binary(ynn_binary_add, 4628, 4629, 4632);
  g->Transpose(9417, 7117, {1,0});
  g->Binary(ynn_binary_multiply, 7109, 7116, 7114);
  g->Dot(4611, 7117, YNN_INVALID_VALUE_ID, 7113, 1);
  g->DequantizeTensor(7113, YNN_INVALID_VALUE_ID, 7114, 7115);
  g->QuantizeTensor(7115, 8727, 7110, 4633);
  g->Dequantize(4633, 4634, 0.16338583827018738, 0);
  g->SplitDim(4634, 4635, 2, {2,256});
  g->FuseDims(4635, 4637, 1, 2);
  g->SplitDim(4637, 4636, 1, {2,1});
  g->Unary(ynn_unary_square, 4636, 4638);
  g->Reduce(ynn_reduce_sum, 4638, 8606, {3}, true);
  g->ShapeProduct(4638, 8605, {3});
  g->Binary(ynn_binary_divide, 8606, 8605, 4639);
  g->Binary(ynn_binary_add, 4639, 8779, 4640);
  g->Unary(ynn_unary_rsqrt, 4640, 4641);
  g->Binary(ynn_binary_multiply, 4636, 4641, 4644);
}

// Scope: "Layer4 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(4632, 4645, 0.00596147496253252, 0);
  g->Append(8746, 4645, 9595, 2, s2, slinky::expr(int64_t{1}));
  g->View(9595, 9643, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(4644, 4646, 0.047244105488061905, 0);
  g->Append(8770, 4646, 9619, 2, s2, slinky::expr(int64_t{1}));
  g->View(9619, 9667, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer4 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(9416, 7123, {1,0});
  g->Binary(ynn_binary_multiply, 7109, 7122, 7119);
  g->Dot(4611, 7123, YNN_INVALID_VALUE_ID, 7118, 1);
  g->DequantizeTensor(7118, YNN_INVALID_VALUE_ID, 7119, 7120);
  g->QuantizeTensor(7120, 8727, 7121, 4647);
  g->Dequantize(4647, 4648, 0.16240158677101135, 0);
  g->SplitDim(4648, 4650, 2, {8,256});
  g->FuseDims(4650, 4652, 1, 2);
  g->SplitDim(4652, 4651, 1, {8,1});
  g->Unary(ynn_unary_square, 4651, 4653);
  g->Reduce(ynn_reduce_sum, 4653, 8610, {3}, true);
  g->ShapeProduct(4653, 8609, {3});
  g->Binary(ynn_binary_divide, 8610, 8609, 4654);
  g->Binary(ynn_binary_add, 4654, 8779, 4655);
  g->Unary(ynn_unary_rsqrt, 4655, 4656);
  g->Binary(ynn_binary_multiply, 4651, 4656, 4657);
  g->Binary(ynn_binary_multiply, 4657, 9415, 4658);
  g->Slice(4658, 4659, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(4658, 4660, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 4660, 4662);
  g->Concat({4662,4659}, 4663, 3);
  g->Binary(ynn_binary_multiply, 4658, 3231, 4664);
  g->Binary(ynn_binary_multiply, 4663, 4329, 4665);
  g->Binary(ynn_binary_add, 4664, 4665, 4666);
}

// Scope: "Layer4 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9643, 4667, 0.00596147496253252, 0);
  g->Dequantize(9667, 4668, 0.047244105488061905, 0);
  g->Slice(4666, 4669, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(4667, 4670, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(4668, 4671, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(4669, 4670, 4673, false, true);
  g->Mask(4673, 8858, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8858, 8614, {-1}, true);
  g->Binary(ynn_binary_subtract, 8858, 8614, 8611);
  g->Unary(ynn_unary_exp, 8611, 8612);
  g->Reduce(ynn_reduce_sum, 8612, 8615, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 8615, 8613);
  g->Binary(ynn_binary_multiply, 8612, 8613, 4674);
  g->Matmul(4674, 4671, 4675, false, false);
  g->Slice(4666, 4676, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(4667, 4677, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(4668, 4678, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(4676, 4677, 4679, false, true);
  g->Mask(4679, 8859, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8859, 8619, {-1}, true);
  g->Binary(ynn_binary_subtract, 8859, 8619, 8616);
  g->Unary(ynn_unary_exp, 8616, 8617);
  g->Reduce(ynn_reduce_sum, 8617, 8620, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 8620, 8618);
  g->Binary(ynn_binary_multiply, 8617, 8618, 4680);
  g->Matmul(4680, 4678, 4682, false, false);
  g->Concat({4675,4682}, 4683, 1);
}

// Scope: "Layer4 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(4683, 4685, 1, 2);
  g->SplitDim(4685, 4684, 1, {1,8});
  g->FuseDims(4684, 4686, 2, 2);
  g->Quantize(4686, 4687, 0.024114182218909264, 0);
  g->Transpose(9414, 7130, {1,0});
  g->Binary(ynn_binary_multiply, 7127, 7129, 7125);
  g->Dot(4687, 7130, YNN_INVALID_VALUE_ID, 7124, 1);
  g->DequantizeTensor(7124, YNN_INVALID_VALUE_ID, 7125, 7126);
  g->QuantizeTensor(7126, 8727, 7128, 4688);
  g->Dequantize(4688, 4689, 0.05563074350357056, 0);
}

// Scope: "Layer4 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 4603, 4604);
  g->Reduce(ynn_reduce_sum, 4604, 8602, {2}, true);
  g->ShapeProduct(4604, 8601, {2});
  g->Binary(ynn_binary_divide, 8602, 8601, 4605);
  g->Binary(ynn_binary_add, 4605, 8779, 4606);
  g->Unary(ynn_unary_rsqrt, 4606, 4608);
  g->Binary(ynn_binary_multiply, 4603, 4608, 4609);
  g->Binary(ynn_binary_multiply, 4609, 9401, 4610);
  BuildLayer4AttentionKvProjection(ctx);
  BuildLayer4AttentionCacheUpdate(ctx);
  BuildLayer4AttentionQueryProjection(ctx);
  BuildLayer4AttentionSdpa(ctx);
  BuildLayer4AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 4689, 4690);
  g->Reduce(ynn_reduce_sum, 4690, 8622, {2}, true);
  g->ShapeProduct(4690, 8621, {2});
  g->Binary(ynn_binary_divide, 8622, 8621, 4691);
  g->Binary(ynn_binary_add, 4691, 8779, 4692);
  g->Unary(ynn_unary_rsqrt, 4692, 4694);
  g->Binary(ynn_binary_multiply, 4689, 4694, 4695);
  g->Binary(ynn_binary_multiply, 4695, 9408, 4696);
  g->Binary(ynn_binary_add, 4696, 4603, 4697);
}

// Scope: "Layer4 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 4697, 4698);
  g->Reduce(ynn_reduce_sum, 4698, 8624, {2}, true);
  g->ShapeProduct(4698, 8623, {2});
  g->Binary(ynn_binary_divide, 8624, 8623, 4699);
  g->Binary(ynn_binary_add, 4699, 8779, 4700);
  g->Unary(ynn_unary_rsqrt, 4700, 4701);
  g->Binary(ynn_binary_multiply, 4697, 4701, 4702);
  g->Binary(ynn_binary_multiply, 4702, 9411, 4703);
  g->Quantize(4703, 4705, 0.04694453626871109, 0);
  g->Transpose(9405, 7136, {1,0});
  g->Binary(ynn_binary_multiply, 7134, 7135, 7132);
  g->Dot(4705, 7136, YNN_INVALID_VALUE_ID, 7131, 1);
  g->DequantizeTensor(7131, YNN_INVALID_VALUE_ID, 7132, 7133);
  g->QuantizeTensor(7133, 8727, 5350, 4706);
  g->Dequantize(4706, 4707, 0.0664370134472847, 0);
  g->Transpose(9404, 7141, {1,0});
  g->Binary(ynn_binary_multiply, 7134, 7140, 7138);
  g->Dot(4705, 7141, YNN_INVALID_VALUE_ID, 7137, 1);
  g->DequantizeTensor(7137, YNN_INVALID_VALUE_ID, 7138, 7139);
  g->QuantizeTensor(7139, 8727, 5350, 4708);
  g->Dequantize(4708, 4709, 0.0664370134472847, 0);
  g->Polynomial(4709, 8627, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8627, 8628);
  g->Binary(ynn_binary_add, 8628, 7293, 8625);
  g->Binary(ynn_binary_multiply, 4709, 7305, 8626);
  g->Binary(ynn_binary_multiply, 8626, 8625, 4710);
  g->Binary(ynn_binary_multiply, 4707, 4710, 4711);
  g->Quantize(4711, 4712, 0.2027559131383896, 0);
  g->Transpose(9403, 7147, {1,0});
  g->Binary(ynn_binary_multiply, 5404, 7146, 7143);
  g->Dot(4712, 7147, YNN_INVALID_VALUE_ID, 7142, 1);
  g->DequantizeTensor(7142, YNN_INVALID_VALUE_ID, 7143, 7144);
  g->QuantizeTensor(7144, 8727, 7145, 4713);
  g->Dequantize(4713, 4715, 0.0875178799033165, 0);
  g->Unary(ynn_unary_square, 4715, 4716);
  g->Reduce(ynn_reduce_sum, 4716, 8630, {2}, true);
  g->ShapeProduct(4716, 8629, {2});
  g->Binary(ynn_binary_divide, 8630, 8629, 4717);
  g->Binary(ynn_binary_add, 4717, 8779, 4718);
  g->Unary(ynn_unary_rsqrt, 4718, 4719);
  g->Binary(ynn_binary_multiply, 4715, 4719, 4720);
  g->Binary(ynn_binary_multiply, 4720, 9409, 4721);
  g->Binary(ynn_binary_add, 4721, 4697, 4722);
}

// Scope: "Layer4 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer4PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(429, 4723, {0,0,4,0}, {-1,-1,1,-1});
  g->Reshape(4723, 4724, {1,1,256});
  g->Unary(ynn_unary_square, 4724, 4726);
  g->Reduce(ynn_reduce_sum, 4726, 8632, {2}, true);
  g->ShapeProduct(4726, 8631, {2});
  g->Binary(ynn_binary_divide, 8632, 8631, 4727);
  g->Binary(ynn_binary_add, 4727, 8779, 4728);
  g->Unary(ynn_unary_rsqrt, 4728, 4729);
  g->Binary(ynn_binary_multiply, 4724, 4729, 4730);
  g->Binary(ynn_binary_multiply, 4730, 9533, 4731);
  g->Binary(ynn_binary_multiply, 9568, 8783, 4732);
  g->Binary(ynn_binary_add, 4731, 4732, 4733);
  g->Binary(ynn_binary_multiply, 4733, 8777, 4734);
  g->Quantize(4722, 4735, 0.5713114738464355, 0);
  g->Transpose(9406, 7154, {1,0});
  g->Binary(ynn_binary_multiply, 7151, 7153, 7149);
  g->Dot(4735, 7154, YNN_INVALID_VALUE_ID, 7148, 1);
  g->DequantizeTensor(7148, YNN_INVALID_VALUE_ID, 7149, 7150);
  g->QuantizeTensor(7150, 8727, 7152, 4737);
  g->Dequantize(4737, 4738, 0.06594488769769669, 0);
  g->Polynomial(4738, 8635, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8635, 8636);
  g->Binary(ynn_binary_add, 8636, 7293, 8633);
  g->Binary(ynn_binary_multiply, 4738, 7305, 8634);
  g->Binary(ynn_binary_multiply, 8634, 8633, 4739);
  g->Binary(ynn_binary_multiply, 4739, 4734, 4740);
  g->Quantize(4740, 4741, 0.4055117964744568, 0);
  g->Transpose(9407, 7161, {1,0});
  g->Binary(ynn_binary_multiply, 7158, 7160, 7156);
  g->Dot(4741, 7161, YNN_INVALID_VALUE_ID, 7155, 1);
  g->DequantizeTensor(7155, YNN_INVALID_VALUE_ID, 7156, 7157);
  g->QuantizeTensor(7157, 8727, 7159, 4742);
  g->Dequantize(4742, 4743, 0.10920456796884537, 0);
  g->Unary(ynn_unary_square, 4743, 4744);
  g->Reduce(ynn_reduce_sum, 4744, 8638, {2}, true);
  g->ShapeProduct(4744, 8637, {2});
  g->Binary(ynn_binary_divide, 8638, 8637, 4745);
  g->Binary(ynn_binary_add, 4745, 8779, 4746);
  g->Unary(ynn_unary_rsqrt, 4746, 4749);
  g->Binary(ynn_binary_multiply, 4743, 4749, 4750);
  g->Binary(ynn_binary_multiply, 4750, 9410, 4751);
  g->Binary(ynn_binary_add, 4722, 4751, 4752);
  g->Binary(ynn_binary_multiply, 4752, 9402, 4753);
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
  g->Quantize(4760, 4761, 0.11662273108959198, 0);
  g->Transpose(9458, 7168, {1,0});
  g->Binary(ynn_binary_multiply, 7165, 7167, 7163);
  g->Dot(4761, 7168, YNN_INVALID_VALUE_ID, 7162, 1);
  g->DequantizeTensor(7162, YNN_INVALID_VALUE_ID, 7163, 7164);
  g->QuantizeTensor(7164, 8727, 7166, 4762);
  g->Dequantize(4762, 4763, 0.09891732782125473, 0);
  g->SplitDim(4763, 4764, 2, {2,512});
  g->FuseDims(4764, 4766, 1, 2);
  g->SplitDim(4766, 4765, 1, {2,1});
  g->Unary(ynn_unary_square, 4765, 4767);
  g->Reduce(ynn_reduce_sum, 4767, 8642, {3}, true);
  g->ShapeProduct(4767, 8641, {3});
  g->Binary(ynn_binary_divide, 8642, 8641, 4768);
  g->Binary(ynn_binary_add, 4768, 8779, 4769);
  g->Unary(ynn_unary_rsqrt, 4769, 4770);
  g->Binary(ynn_binary_multiply, 4765, 4770, 4772);
  g->Binary(ynn_binary_multiply, 4772, 9457, 4773);
  g->Slice(4773, 4774, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(4773, 4775, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 4775, 4776);
  g->Concat({4776,4774}, 4777, 3);
  g->Binary(ynn_binary_multiply, 4773, 4959, 4778);
  g->Binary(ynn_binary_multiply, 4777, 2, 4779);
  g->Binary(ynn_binary_add, 4778, 4779, 4780);
  g->Transpose(9462, 7173, {1,0});
  g->Binary(ynn_binary_multiply, 7165, 7172, 7170);
  g->Dot(4761, 7173, YNN_INVALID_VALUE_ID, 7169, 1);
  g->DequantizeTensor(7169, YNN_INVALID_VALUE_ID, 7170, 7171);
  g->QuantizeTensor(7171, 8727, 7166, 4782);
  g->Dequantize(4782, 4783, 0.09891732782125473, 0);
  g->SplitDim(4783, 4784, 2, {2,512});
  g->FuseDims(4784, 4786, 1, 2);
  g->SplitDim(4786, 4785, 1, {2,1});
  g->Unary(ynn_unary_square, 4785, 4787);
  g->Reduce(ynn_reduce_sum, 4787, 8644, {3}, true);
  g->ShapeProduct(4787, 8643, {3});
  g->Binary(ynn_binary_divide, 8644, 8643, 4788);
  g->Binary(ynn_binary_add, 4788, 8779, 4789);
  g->Unary(ynn_unary_rsqrt, 4789, 4790);
  g->Binary(ynn_binary_multiply, 4785, 4790, 4791);
}

// Scope: "Layer5 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(4780, 4792, 0.001090860809199512, 0);
  g->Append(8747, 4792, 9596, 2, s2, slinky::expr(int64_t{1}));
  g->View(9596, 9644, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(4791, 4794, 0.01785714365541935, 0);
  g->Append(8771, 4794, 9620, 2, s2, slinky::expr(int64_t{1}));
  g->View(9620, 9668, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer5 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(9461, 7179, {1,0});
  g->Binary(ynn_binary_multiply, 7165, 7178, 7175);
  g->Dot(4761, 7179, YNN_INVALID_VALUE_ID, 7174, 1);
  g->DequantizeTensor(7174, YNN_INVALID_VALUE_ID, 7175, 7176);
  g->QuantizeTensor(7176, 8727, 7177, 4795);
  g->Dequantize(4795, 4796, 0.1092519760131836, 0);
  g->SplitDim(4796, 4797, 2, {8,512});
  g->FuseDims(4797, 4799, 1, 2);
  g->SplitDim(4799, 4798, 1, {8,1});
  g->Unary(ynn_unary_square, 4798, 4801);
  g->Reduce(ynn_reduce_sum, 4801, 8646, {3}, true);
  g->ShapeProduct(4801, 8645, {3});
  g->Binary(ynn_binary_divide, 8646, 8645, 4802);
  g->Binary(ynn_binary_add, 4802, 8779, 4803);
  g->Unary(ynn_unary_rsqrt, 4803, 4804);
  g->Binary(ynn_binary_multiply, 4798, 4804, 4805);
  g->Binary(ynn_binary_multiply, 4805, 9460, 4806);
  g->Slice(4806, 4807, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(4806, 4808, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 4808, 4809);
  g->Concat({4809,4807}, 4810, 3);
  g->Binary(ynn_binary_multiply, 4806, 4959, 4812);
  g->Binary(ynn_binary_multiply, 4810, 2, 4813);
  g->Binary(ynn_binary_add, 4812, 4813, 4814);
}

// Scope: "Layer5 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9644, 4815, 0.001090860809199512, 0);
  g->Dequantize(9668, 4816, 0.01785714365541935, 0);
  g->Slice(4814, 4817, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(4815, 4818, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(4816, 4819, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(4817, 4818, 4820, false, true);
  g->Mask(4820, 8860, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 8860, 8650, {-1}, true);
  g->Binary(ynn_binary_subtract, 8860, 8650, 8647);
  g->Unary(ynn_unary_exp, 8647, 8648);
  g->Reduce(ynn_reduce_sum, 8648, 8651, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 8651, 8649);
  g->Binary(ynn_binary_multiply, 8648, 8649, 4822);
  g->Matmul(4822, 4819, 4823, false, false);
  g->Slice(4814, 4824, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(4815, 4825, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(4816, 4826, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(4824, 4825, 4827, false, true);
  g->Mask(4827, 8861, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 8861, 8655, {-1}, true);
  g->Binary(ynn_binary_subtract, 8861, 8655, 8652);
  g->Unary(ynn_unary_exp, 8652, 8653);
  g->Reduce(ynn_reduce_sum, 8653, 8656, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 8656, 8654);
  g->Binary(ynn_binary_multiply, 8653, 8654, 4828);
  g->Matmul(4828, 4826, 4829, false, false);
  g->Concat({4823,4829}, 4830, 1);
}

// Scope: "Layer5 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(4830, 4833, 1, 2);
  g->SplitDim(4833, 4832, 1, {1,8});
  g->FuseDims(4832, 4834, 2, 2);
  g->Quantize(4834, 4835, 0.017839577049016953, 0);
  g->Transpose(9459, 7185, {1,0});
  g->Binary(ynn_binary_multiply, 6969, 7184, 7181);
  g->Dot(4835, 7185, YNN_INVALID_VALUE_ID, 7180, 1);
  g->DequantizeTensor(7180, YNN_INVALID_VALUE_ID, 7181, 7182);
  g->QuantizeTensor(7182, 8727, 7183, 4836);
  g->Dequantize(4836, 4837, 0.14457935094833374, 0);
}

// Scope: "Layer5 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 4753, 4754);
  g->Reduce(ynn_reduce_sum, 4754, 8640, {2}, true);
  g->ShapeProduct(4754, 8639, {2});
  g->Binary(ynn_binary_divide, 8640, 8639, 4755);
  g->Binary(ynn_binary_add, 4755, 8779, 4756);
  g->Unary(ynn_unary_rsqrt, 4756, 4757);
  g->Binary(ynn_binary_multiply, 4753, 4757, 4758);
  g->Binary(ynn_binary_multiply, 4758, 9446, 4760);
  BuildLayer5AttentionKvProjection(ctx);
  BuildLayer5AttentionCacheUpdate(ctx);
  BuildLayer5AttentionQueryProjection(ctx);
  BuildLayer5AttentionSdpa(ctx);
  BuildLayer5AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 4837, 4838);
  g->Reduce(ynn_reduce_sum, 4838, 8658, {2}, true);
  g->ShapeProduct(4838, 8657, {2});
  g->Binary(ynn_binary_divide, 8658, 8657, 4839);
  g->Binary(ynn_binary_add, 4839, 8779, 4840);
  g->Unary(ynn_unary_rsqrt, 4840, 4841);
  g->Binary(ynn_binary_multiply, 4837, 4841, 4842);
  g->Binary(ynn_binary_multiply, 4842, 9453, 4843);
  g->Binary(ynn_binary_add, 4843, 4753, 4844);
}

// Scope: "Layer5 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 4844, 4845);
  g->Reduce(ynn_reduce_sum, 4845, 8660, {2}, true);
  g->ShapeProduct(4845, 8659, {2});
  g->Binary(ynn_binary_divide, 8660, 8659, 4846);
  g->Binary(ynn_binary_add, 4846, 8779, 4847);
  g->Unary(ynn_unary_rsqrt, 4847, 4848);
  g->Binary(ynn_binary_multiply, 4844, 4848, 4849);
  g->Binary(ynn_binary_multiply, 4849, 9456, 4850);
  g->Quantize(4850, 4851, 0.3053959310054779, 0);
  g->Transpose(9450, 7192, {1,0});
  g->Binary(ynn_binary_multiply, 7189, 7191, 7187);
  g->Dot(4851, 7192, YNN_INVALID_VALUE_ID, 7186, 1);
  g->DequantizeTensor(7186, YNN_INVALID_VALUE_ID, 7187, 7188);
  g->QuantizeTensor(7188, 8727, 7190, 4852);
  g->Dequantize(4852, 4855, 0.16633859276771545, 0);
  g->Transpose(9449, 7197, {1,0});
  g->Binary(ynn_binary_multiply, 7189, 7196, 7194);
  g->Dot(4851, 7197, YNN_INVALID_VALUE_ID, 7193, 1);
  g->DequantizeTensor(7193, YNN_INVALID_VALUE_ID, 7194, 7195);
  g->QuantizeTensor(7195, 8727, 7190, 4856);
  g->Dequantize(4856, 4857, 0.16633859276771545, 0);
  g->Polynomial(4857, 8668, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8668, 8669);
  g->Binary(ynn_binary_add, 8669, 7293, 8666);
  g->Binary(ynn_binary_multiply, 4857, 7305, 8667);
  g->Binary(ynn_binary_multiply, 8667, 8666, 4858);
  g->Binary(ynn_binary_multiply, 4855, 4858, 4859);
  g->Quantize(4859, 4860, 1.5511810779571533, 0);
  g->Transpose(9448, 7204, {1,0});
  g->Binary(ynn_binary_multiply, 7201, 7203, 7199);
  g->Dot(4860, 7204, YNN_INVALID_VALUE_ID, 7198, 1);
  g->DequantizeTensor(7198, YNN_INVALID_VALUE_ID, 7199, 7200);
  g->QuantizeTensor(7200, 8727, 7202, 4861);
  g->Dequantize(4861, 4862, 0.3160533308982849, 0);
  g->Unary(ynn_unary_square, 4862, 4863);
  g->Reduce(ynn_reduce_sum, 4863, 8671, {2}, true);
  g->ShapeProduct(4863, 8670, {2});
  g->Binary(ynn_binary_divide, 8671, 8670, 4865);
  g->Binary(ynn_binary_add, 4865, 8779, 4866);
  g->Unary(ynn_unary_rsqrt, 4866, 4867);
  g->Binary(ynn_binary_multiply, 4862, 4867, 4868);
  g->Binary(ynn_binary_multiply, 4868, 9454, 4869);
  g->Binary(ynn_binary_add, 4869, 4844, 4870);
}

// Scope: "Layer5 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(429, 4871, {0,0,5,0}, {-1,-1,1,-1});
  g->Reshape(4871, 4872, {1,1,256});
  g->Unary(ynn_unary_square, 4872, 4873);
  g->Reduce(ynn_reduce_sum, 4873, 8673, {2}, true);
  g->ShapeProduct(4873, 8672, {2});
  g->Binary(ynn_binary_divide, 8673, 8672, 4874);
  g->Binary(ynn_binary_add, 4874, 8779, 4876);
  g->Unary(ynn_unary_rsqrt, 4876, 4877);
  g->Binary(ynn_binary_multiply, 4872, 4877, 4878);
  g->Binary(ynn_binary_multiply, 4878, 9533, 4879);
  g->Binary(ynn_binary_multiply, 9571, 8783, 4880);
  g->Binary(ynn_binary_add, 4879, 4880, 4881);
  g->Binary(ynn_binary_multiply, 4881, 8777, 4882);
  g->Quantize(4870, 4883, 0.33932316303253174, 0);
  g->Transpose(9451, 7210, {1,0});
  g->Binary(ynn_binary_multiply, 7208, 7209, 7206);
  g->Dot(4883, 7210, YNN_INVALID_VALUE_ID, 7205, 1);
  g->DequantizeTensor(7205, YNN_INVALID_VALUE_ID, 7206, 7207);
  g->QuantizeTensor(7207, 8727, 5429, 4884);
  g->Dequantize(4884, 4885, 0.05216536670923233, 0);
  g->Polynomial(4885, 8676, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8676, 8677);
  g->Binary(ynn_binary_add, 8677, 7293, 8674);
  g->Binary(ynn_binary_multiply, 4885, 7305, 8675);
  g->Binary(ynn_binary_multiply, 8675, 8674, 4887);
  g->Binary(ynn_binary_multiply, 4887, 4882, 4888);
  g->Quantize(4888, 4889, 0.25, 0);
  g->Transpose(9452, 7216, {1,0});
  g->Binary(ynn_binary_multiply, 5530, 7215, 7212);
  g->Dot(4889, 7216, YNN_INVALID_VALUE_ID, 7211, 1);
  g->DequantizeTensor(7211, YNN_INVALID_VALUE_ID, 7212, 7213);
  g->QuantizeTensor(7213, 8727, 7214, 4890);
  g->Dequantize(4890, 4891, 0.13969317078590393, 0);
  g->Unary(ynn_unary_square, 4891, 4892);
  g->Reduce(ynn_reduce_sum, 4892, 8679, {2}, true);
  g->ShapeProduct(4892, 8678, {2});
  g->Binary(ynn_binary_divide, 8679, 8678, 4893);
  g->Binary(ynn_binary_add, 4893, 8779, 4894);
  g->Unary(ynn_unary_rsqrt, 4894, 4895);
  g->Binary(ynn_binary_multiply, 4891, 4895, 4896);
  g->Binary(ynn_binary_multiply, 4896, 9455, 4898);
  g->Binary(ynn_binary_add, 4870, 4898, 4899);
  g->Binary(ynn_binary_multiply, 4899, 9447, 4900);
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
  g->Quantize(4906, 4907, 0.0976727083325386, 0);
  g->Transpose(9475, 7222, {1,0});
  g->Binary(ynn_binary_multiply, 7220, 7221, 7218);
  g->Dot(4907, 7222, YNN_INVALID_VALUE_ID, 7217, 1);
  g->DequantizeTensor(7217, YNN_INVALID_VALUE_ID, 7218, 7219);
  g->QuantizeTensor(7219, 8727, 5652, 4909);
  g->Dequantize(4909, 4910, 0.16535434126853943, 0);
  g->SplitDim(4910, 4911, 2, {2,256});
  g->FuseDims(4911, 4913, 1, 2);
  g->SplitDim(4913, 4912, 1, {2,1});
  g->Unary(ynn_unary_square, 4912, 4914);
  g->Reduce(ynn_reduce_sum, 4914, 8683, {3}, true);
  g->ShapeProduct(4914, 8682, {3});
  g->Binary(ynn_binary_divide, 8683, 8682, 4915);
  g->Binary(ynn_binary_add, 4915, 8779, 4916);
  g->Unary(ynn_unary_rsqrt, 4916, 4917);
  g->Binary(ynn_binary_multiply, 4912, 4917, 4918);
  g->Binary(ynn_binary_multiply, 4918, 9474, 4919);
  g->Slice(4919, 4920, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(4919, 4921, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 4921, 4922);
  g->Concat({4922,4920}, 4923, 3);
  g->Binary(ynn_binary_multiply, 4919, 3231, 4924);
  g->Binary(ynn_binary_multiply, 4923, 4329, 4925);
  g->Binary(ynn_binary_add, 4924, 4925, 4926);
  g->Transpose(9479, 7227, {1,0});
  g->Binary(ynn_binary_multiply, 7220, 7226, 7224);
  g->Dot(4907, 7227, YNN_INVALID_VALUE_ID, 7223, 1);
  g->DequantizeTensor(7223, YNN_INVALID_VALUE_ID, 7224, 7225);
  g->QuantizeTensor(7225, 8727, 5652, 4927);
  g->Dequantize(4927, 4928, 0.16535434126853943, 0);
  g->SplitDim(4928, 4930, 2, {2,256});
  g->FuseDims(4930, 4932, 1, 2);
  g->SplitDim(4932, 4931, 1, {2,1});
  g->Unary(ynn_unary_square, 4931, 4933);
  g->Reduce(ynn_reduce_sum, 4933, 8690, {3}, true);
  g->ShapeProduct(4933, 8689, {3});
  g->Binary(ynn_binary_divide, 8690, 8689, 4934);
  g->Binary(ynn_binary_add, 4934, 8779, 4935);
  g->Unary(ynn_unary_rsqrt, 4935, 4936);
  g->Binary(ynn_binary_multiply, 4931, 4936, 4937);
}

// Scope: "Layer6 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(4926, 4938, 0.005761673673987389, 0);
  g->Append(8748, 4938, 9597, 2, s2, slinky::expr(int64_t{1}));
  g->View(9597, 9645, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(4937, 4940, 0.047244105488061905, 0);
  g->Append(8772, 4940, 9621, 2, s2, slinky::expr(int64_t{1}));
  g->View(9621, 9669, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer6 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(9478, 7232, {1,0});
  g->Binary(ynn_binary_multiply, 7220, 7231, 7229);
  g->Dot(4907, 7232, YNN_INVALID_VALUE_ID, 7228, 1);
  g->DequantizeTensor(7228, YNN_INVALID_VALUE_ID, 7229, 7230);
  g->QuantizeTensor(7230, 8727, 7190, 4941);
  g->Dequantize(4941, 4942, 0.16633859276771545, 0);
  g->SplitDim(4942, 4943, 2, {8,256});
  g->FuseDims(4943, 4945, 1, 2);
  g->SplitDim(4945, 4944, 1, {8,1});
  g->Unary(ynn_unary_square, 4944, 4946);
  g->Reduce(ynn_reduce_sum, 4946, 8692, {3}, true);
  g->ShapeProduct(4946, 8691, {3});
  g->Binary(ynn_binary_divide, 8692, 8691, 4947);
  g->Binary(ynn_binary_add, 4947, 8779, 4949);
  g->Unary(ynn_unary_rsqrt, 4949, 4950);
  g->Binary(ynn_binary_multiply, 4944, 4950, 4951);
  g->Binary(ynn_binary_multiply, 4951, 9477, 4952);
  g->Slice(4952, 4953, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(4952, 4954, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 4954, 4955);
  g->Concat({4955,4953}, 4956, 3);
  g->Binary(ynn_binary_multiply, 4952, 3231, 4957);
  g->Binary(ynn_binary_multiply, 4956, 4329, 4958);
  g->Binary(ynn_binary_add, 4957, 4958, 4962);
}

// Scope: "Layer6 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9645, 4963, 0.005761673673987389, 0);
  g->Dequantize(9669, 4964, 0.047244105488061905, 0);
  g->Slice(4962, 4965, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(4963, 4966, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(4964, 4967, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(4965, 4966, 4968, false, true);
  g->Mask(4968, 8862, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8862, 8696, {-1}, true);
  g->Binary(ynn_binary_subtract, 8862, 8696, 8693);
  g->Unary(ynn_unary_exp, 8693, 8694);
  g->Reduce(ynn_reduce_sum, 8694, 8697, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 8697, 8695);
  g->Binary(ynn_binary_multiply, 8694, 8695, 4969);
  g->Matmul(4969, 4967, 4970, false, false);
  g->Slice(4962, 4972, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(4963, 4973, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(4964, 4974, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(4972, 4973, 4975, false, true);
  g->Mask(4975, 8863, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8863, 8701, {-1}, true);
  g->Binary(ynn_binary_subtract, 8863, 8701, 8698);
  g->Unary(ynn_unary_exp, 8698, 8699);
  g->Reduce(ynn_reduce_sum, 8699, 8702, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 8702, 8700);
  g->Binary(ynn_binary_multiply, 8699, 8700, 4976);
  g->Matmul(4976, 4974, 4977, false, false);
  g->Concat({4970,4977}, 4978, 1);
}

// Scope: "Layer6 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(4978, 4980, 1, 2);
  g->SplitDim(4980, 4979, 1, {1,8});
  g->FuseDims(4979, 4981, 2, 2);
  g->Quantize(4981, 4983, 0.02706693857908249, 0);
  g->Transpose(9476, 7238, {1,0});
  g->Binary(ynn_binary_multiply, 5604, 7237, 7234);
  g->Dot(4983, 7238, YNN_INVALID_VALUE_ID, 7233, 1);
  g->DequantizeTensor(7233, YNN_INVALID_VALUE_ID, 7234, 7235);
  g->QuantizeTensor(7235, 8727, 7236, 4984);
  g->Dequantize(4984, 4985, 0.19767579436302185, 0);
}

// Scope: "Layer6 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 4900, 4901);
  g->Reduce(ynn_reduce_sum, 4901, 8681, {2}, true);
  g->ShapeProduct(4901, 8680, {2});
  g->Binary(ynn_binary_divide, 8681, 8680, 4902);
  g->Binary(ynn_binary_add, 4902, 8779, 4903);
  g->Unary(ynn_unary_rsqrt, 4903, 4904);
  g->Binary(ynn_binary_multiply, 4900, 4904, 4905);
  g->Binary(ynn_binary_multiply, 4905, 9463, 4906);
  BuildLayer6AttentionKvProjection(ctx);
  BuildLayer6AttentionCacheUpdate(ctx);
  BuildLayer6AttentionQueryProjection(ctx);
  BuildLayer6AttentionSdpa(ctx);
  BuildLayer6AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 4985, 4986);
  g->Reduce(ynn_reduce_sum, 4986, 8704, {2}, true);
  g->ShapeProduct(4986, 8703, {2});
  g->Binary(ynn_binary_divide, 8704, 8703, 4987);
  g->Binary(ynn_binary_add, 4987, 8779, 4988);
  g->Unary(ynn_unary_rsqrt, 4988, 4989);
  g->Binary(ynn_binary_multiply, 4985, 4989, 4990);
  g->Binary(ynn_binary_multiply, 4990, 9470, 4991);
  g->Binary(ynn_binary_add, 4991, 4900, 4992);
}

// Scope: "Layer6 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 4992, 4994);
  g->Reduce(ynn_reduce_sum, 4994, 8706, {2}, true);
  g->ShapeProduct(4994, 8705, {2});
  g->Binary(ynn_binary_divide, 8706, 8705, 4995);
  g->Binary(ynn_binary_add, 4995, 8779, 4996);
  g->Unary(ynn_unary_rsqrt, 4996, 4997);
  g->Binary(ynn_binary_multiply, 4992, 4997, 4998);
  g->Binary(ynn_binary_multiply, 4998, 9473, 4999);
  g->Quantize(4999, 5000, 0.06627800315618515, 0);
  g->Transpose(9467, 7252, {1,0});
  g->Binary(ynn_binary_multiply, 7249, 7251, 7247);
  g->Dot(5000, 7252, YNN_INVALID_VALUE_ID, 7246, 1);
  g->DequantizeTensor(7246, YNN_INVALID_VALUE_ID, 7247, 7248);
  g->QuantizeTensor(7248, 8727, 7250, 5001);
  g->Dequantize(5001, 5002, 0.1171259880065918, 0);
  g->Transpose(9466, 7257, {1,0});
  g->Binary(ynn_binary_multiply, 7249, 7256, 7254);
  g->Dot(5000, 7257, YNN_INVALID_VALUE_ID, 7253, 1);
  g->DequantizeTensor(7253, YNN_INVALID_VALUE_ID, 7254, 7255);
  g->QuantizeTensor(7255, 8727, 7250, 5004);
  g->Dequantize(5004, 5005, 0.1171259880065918, 0);
  g->Polynomial(5005, 8709, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8709, 8710);
  g->Binary(ynn_binary_add, 8710, 7293, 8707);
  g->Binary(ynn_binary_multiply, 5005, 7305, 8708);
  g->Binary(ynn_binary_multiply, 8708, 8707, 5006);
  g->Binary(ynn_binary_multiply, 5002, 5006, 5007);
  g->Quantize(5007, 5008, 0.4488188922405243, 0);
  g->Transpose(9465, 7264, {1,0});
  g->Binary(ynn_binary_multiply, 7261, 7263, 7259);
  g->Dot(5008, 7264, YNN_INVALID_VALUE_ID, 7258, 1);
  g->DequantizeTensor(7258, YNN_INVALID_VALUE_ID, 7259, 7260);
  g->QuantizeTensor(7260, 8727, 7262, 5009);
  g->Dequantize(5009, 5010, 0.19675913453102112, 0);
  g->Unary(ynn_unary_square, 5010, 5011);
  g->Reduce(ynn_reduce_sum, 5011, 8712, {2}, true);
  g->ShapeProduct(5011, 8711, {2});
  g->Binary(ynn_binary_divide, 8712, 8711, 5012);
  g->Binary(ynn_binary_add, 5012, 8779, 5013);
  g->Unary(ynn_unary_rsqrt, 5013, 5015);
  g->Binary(ynn_binary_multiply, 5010, 5015, 5016);
  g->Binary(ynn_binary_multiply, 5016, 9471, 5017);
  g->Binary(ynn_binary_add, 5017, 4992, 5018);
}

// Scope: "Layer6 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(429, 5019, {0,0,6,0}, {-1,-1,1,-1});
  g->Reshape(5019, 5020, {1,1,256});
  g->Unary(ynn_unary_square, 5020, 5021);
  g->Reduce(ynn_reduce_sum, 5021, 8714, {2}, true);
  g->ShapeProduct(5021, 8713, {2});
  g->Binary(ynn_binary_divide, 8714, 8713, 5022);
  g->Binary(ynn_binary_add, 5022, 8779, 5023);
  g->Unary(ynn_unary_rsqrt, 5023, 5024);
  g->Binary(ynn_binary_multiply, 5020, 5024, 5026);
  g->Binary(ynn_binary_multiply, 5026, 9533, 5027);
  g->Binary(ynn_binary_multiply, 9572, 8783, 5028);
  g->Binary(ynn_binary_add, 5027, 5028, 5029);
  g->Binary(ynn_binary_multiply, 5029, 8777, 5030);
  g->Quantize(5018, 5031, 0.5854530930519104, 0);
  g->Transpose(9468, 7271, {1,0});
  g->Binary(ynn_binary_multiply, 7268, 7270, 7266);
  g->Dot(5031, 7271, YNN_INVALID_VALUE_ID, 7265, 1);
  g->DequantizeTensor(7265, YNN_INVALID_VALUE_ID, 7266, 7267);
  g->QuantizeTensor(7267, 8727, 7269, 5032);
  g->Dequantize(5032, 5033, 0.0433070994913578, 0);
  g->Polynomial(5033, 8719, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8719, 8720);
  g->Binary(ynn_binary_add, 8720, 7293, 8717);
  g->Binary(ynn_binary_multiply, 5033, 7305, 8718);
  g->Binary(ynn_binary_multiply, 8718, 8717, 5034);
  g->Binary(ynn_binary_multiply, 5034, 5030, 5035);
  g->Quantize(5035, 5037, 0.25590550899505615, 0);
  g->Transpose(9469, 7277, {1,0});
  g->Binary(ynn_binary_multiply, 6508, 7276, 7273);
  g->Dot(5037, 7277, YNN_INVALID_VALUE_ID, 7272, 1);
  g->DequantizeTensor(7272, YNN_INVALID_VALUE_ID, 7273, 7274);
  g->QuantizeTensor(7274, 8727, 7275, 5038);
  g->Dequantize(5038, 5039, 0.08977121859788895, 0);
  g->Unary(ynn_unary_square, 5039, 5040);
  g->Reduce(ynn_reduce_sum, 5040, 8722, {2}, true);
  g->ShapeProduct(5040, 8721, {2});
  g->Binary(ynn_binary_divide, 8722, 8721, 5041);
  g->Binary(ynn_binary_add, 5041, 8779, 5042);
  g->Unary(ynn_unary_rsqrt, 5042, 5043);
  g->Binary(ynn_binary_multiply, 5039, 5043, 5044);
  g->Binary(ynn_binary_multiply, 5044, 9472, 5045);
  g->Binary(ynn_binary_add, 5018, 5045, 5046);
  g->Binary(ynn_binary_multiply, 5046, 9464, 5048);
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
  g->Quantize(5054, 5055, 0.17314177751541138, 0);
  g->Transpose(9492, 7282, {1,0});
  g->Binary(ynn_binary_multiply, 5073, 7281, 7279);
  g->Dot(5055, 7282, YNN_INVALID_VALUE_ID, 7278, 1);
  g->DequantizeTensor(7278, YNN_INVALID_VALUE_ID, 7279, 7280);
  g->QuantizeTensor(7280, 8727, 5074, 5056);
  g->Dequantize(5056, 5057, 0.3011811077594757, 0);
  g->SplitDim(5057, 5059, 2, {2,256});
  g->FuseDims(5059, 5061, 1, 2);
  g->SplitDim(5061, 5060, 1, {2,1});
  g->Unary(ynn_unary_square, 5060, 5062);
  g->Reduce(ynn_reduce_sum, 5062, 8726, {3}, true);
  g->ShapeProduct(5062, 8725, {3});
  g->Binary(ynn_binary_divide, 8726, 8725, 5063);
  g->Binary(ynn_binary_add, 5063, 8779, 5064);
  g->Unary(ynn_unary_rsqrt, 5064, 5065);
  g->Binary(ynn_binary_multiply, 5060, 5065, 5066);
  g->Binary(ynn_binary_multiply, 5066, 9491, 5067);
  g->Slice(5067, 5068, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(5067, 5069, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 5069, 4);
  g->Concat({4,5068}, 5, 3);
  g->Binary(ynn_binary_multiply, 5067, 3231, 6);
  g->Binary(ynn_binary_multiply, 5, 4329, 7);
  g->Binary(ynn_binary_add, 6, 7, 8);
  g->Transpose(9496, 5076, {1,0});
  g->Binary(ynn_binary_multiply, 5073, 5075, 5071);
  g->Dot(5055, 5076, YNN_INVALID_VALUE_ID, 5070, 1);
  g->DequantizeTensor(5070, YNN_INVALID_VALUE_ID, 5071, 5072);
  g->QuantizeTensor(5072, 8727, 5074, 9);
  g->Dequantize(9, 10, 0.3011811077594757, 0);
  g->SplitDim(10, 11, 2, {2,256});
  g->FuseDims(11, 13, 1, 2);
  g->SplitDim(13, 12, 1, {2,1});
  g->Unary(ynn_unary_square, 12, 15);
  g->Reduce(ynn_reduce_sum, 15, 7284, {3}, true);
  g->ShapeProduct(15, 7283, {3});
  g->Binary(ynn_binary_divide, 7284, 7283, 16);
  g->Binary(ynn_binary_add, 16, 8779, 17);
  g->Unary(ynn_unary_rsqrt, 17, 18);
  g->Binary(ynn_binary_multiply, 12, 18, 19);
}

// Scope: "Layer7 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(8, 20, 0.006011798977851868, 0);
  g->Append(8749, 20, 9598, 2, s2, slinky::expr(int64_t{1}));
  g->View(9598, 9646, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(19, 21, 0.047244105488061905, 0);
  g->Append(8773, 21, 9622, 2, s2, slinky::expr(int64_t{1}));
  g->View(9622, 9670, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer7 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(9495, 5082, {1,0});
  g->Binary(ynn_binary_multiply, 5073, 5081, 5078);
  g->Dot(5055, 5082, YNN_INVALID_VALUE_ID, 5077, 1);
  g->DequantizeTensor(5077, YNN_INVALID_VALUE_ID, 5078, 5079);
  g->QuantizeTensor(5079, 8727, 5080, 23);
  g->Dequantize(23, 24, 0.31889763474464417, 0);
  g->SplitDim(24, 25, 2, {8,256});
  g->FuseDims(25, 27, 1, 2);
  g->SplitDim(27, 26, 1, {8,1});
  g->Unary(ynn_unary_square, 26, 28);
  g->Reduce(ynn_reduce_sum, 28, 7286, {3}, true);
  g->ShapeProduct(28, 7285, {3});
  g->Binary(ynn_binary_divide, 7286, 7285, 29);
  g->Binary(ynn_binary_add, 29, 8779, 30);
  g->Unary(ynn_unary_rsqrt, 30, 31);
  g->Binary(ynn_binary_multiply, 26, 31, 33);
  g->Binary(ynn_binary_multiply, 33, 9494, 34);
  g->Slice(34, 35, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(34, 36, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 36, 37);
  g->Concat({37,35}, 38, 3);
  g->Binary(ynn_binary_multiply, 34, 3231, 39);
  g->Binary(ynn_binary_multiply, 38, 4329, 40);
  g->Binary(ynn_binary_add, 39, 40, 41);
}

// Scope: "Layer7 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9646, 42, 0.006011798977851868, 0);
  g->Dequantize(9670, 44, 0.047244105488061905, 0);
  g->Slice(41, 45, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(42, 46, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(44, 47, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(45, 46, 48, false, true);
  g->Mask(48, 8864, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8864, 7292, {-1}, true);
  g->Binary(ynn_binary_subtract, 8864, 7292, 7289);
  g->Unary(ynn_unary_exp, 7289, 7290);
  g->Reduce(ynn_reduce_sum, 7290, 7294, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 7294, 7291);
  g->Binary(ynn_binary_multiply, 7290, 7291, 49);
  g->Matmul(49, 47, 50, false, false);
  g->Slice(41, 51, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(42, 52, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(44, 54, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(51, 52, 55, false, true);
  g->Mask(55, 8865, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8865, 7298, {-1}, true);
  g->Binary(ynn_binary_subtract, 8865, 7298, 7295);
  g->Unary(ynn_unary_exp, 7295, 7296);
  g->Reduce(ynn_reduce_sum, 7296, 7299, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 7299, 7297);
  g->Binary(ynn_binary_multiply, 7296, 7297, 56);
  g->Matmul(56, 54, 57, false, false);
  g->Concat({50,57}, 58, 1);
}

// Scope: "Layer7 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(58, 60, 1, 2);
  g->SplitDim(60, 59, 1, {1,8});
  g->FuseDims(59, 61, 2, 2);
  g->Quantize(61, 62, 0.02239174209535122, 0);
  g->Transpose(9493, 5089, {1,0});
  g->Binary(ynn_binary_multiply, 5086, 5088, 5084);
  g->Dot(62, 5089, YNN_INVALID_VALUE_ID, 5083, 1);
  g->DequantizeTensor(5083, YNN_INVALID_VALUE_ID, 5084, 5085);
  g->QuantizeTensor(5085, 8727, 5087, 63);
  g->Dequantize(63, 65, 0.07983598113059998, 0);
}

// Scope: "Layer7 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 5048, 5049);
  g->Reduce(ynn_reduce_sum, 5049, 8724, {2}, true);
  g->ShapeProduct(5049, 8723, {2});
  g->Binary(ynn_binary_divide, 8724, 8723, 5050);
  g->Binary(ynn_binary_add, 5050, 8779, 5051);
  g->Unary(ynn_unary_rsqrt, 5051, 5052);
  g->Binary(ynn_binary_multiply, 5048, 5052, 5053);
  g->Binary(ynn_binary_multiply, 5053, 9480, 5054);
  BuildLayer7AttentionKvProjection(ctx);
  BuildLayer7AttentionCacheUpdate(ctx);
  BuildLayer7AttentionQueryProjection(ctx);
  BuildLayer7AttentionSdpa(ctx);
  BuildLayer7AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 65, 66);
  g->Reduce(ynn_reduce_sum, 66, 7301, {2}, true);
  g->ShapeProduct(66, 7300, {2});
  g->Binary(ynn_binary_divide, 7301, 7300, 67);
  g->Binary(ynn_binary_add, 67, 8779, 68);
  g->Unary(ynn_unary_rsqrt, 68, 69);
  g->Binary(ynn_binary_multiply, 65, 69, 70);
  g->Binary(ynn_binary_multiply, 70, 9487, 71);
  g->Binary(ynn_binary_add, 71, 5048, 72);
}

// Scope: "Layer7 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 72, 73);
  g->Reduce(ynn_reduce_sum, 73, 7303, {2}, true);
  g->ShapeProduct(73, 7302, {2});
  g->Binary(ynn_binary_divide, 7303, 7302, 74);
  g->Binary(ynn_binary_add, 74, 8779, 76);
  g->Unary(ynn_unary_rsqrt, 76, 77);
  g->Binary(ynn_binary_multiply, 72, 77, 78);
  g->Binary(ynn_binary_multiply, 78, 9490, 79);
  g->Quantize(79, 80, 0.04099859297275543, 0);
  g->Transpose(9484, 5096, {1,0});
  g->Binary(ynn_binary_multiply, 5093, 5095, 5091);
  g->Dot(80, 5096, YNN_INVALID_VALUE_ID, 5090, 1);
  g->DequantizeTensor(5090, YNN_INVALID_VALUE_ID, 5091, 5092);
  g->QuantizeTensor(5092, 8727, 5094, 81);
  g->Dequantize(81, 82, 0.0625000074505806, 0);
  g->Transpose(9483, 5101, {1,0});
  g->Binary(ynn_binary_multiply, 5093, 5100, 5098);
  g->Dot(80, 5101, YNN_INVALID_VALUE_ID, 5097, 1);
  g->DequantizeTensor(5097, YNN_INVALID_VALUE_ID, 5098, 5099);
  g->QuantizeTensor(5099, 8727, 5094, 83);
  g->Dequantize(83, 84, 0.0625000074505806, 0);
  g->Polynomial(84, 7307, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7307, 7308);
  g->Binary(ynn_binary_add, 7308, 7293, 7304);
  g->Binary(ynn_binary_multiply, 84, 7305, 7306);
  g->Binary(ynn_binary_multiply, 7306, 7304, 86);
  g->Binary(ynn_binary_multiply, 82, 86, 87);
  g->Quantize(87, 88, 0.18503938615322113, 0);
  g->Transpose(9482, 5108, {1,0});
  g->Binary(ynn_binary_multiply, 5105, 5107, 5103);
  g->Dot(88, 5108, YNN_INVALID_VALUE_ID, 5102, 1);
  g->DequantizeTensor(5102, YNN_INVALID_VALUE_ID, 5103, 5104);
  g->QuantizeTensor(5104, 8727, 5106, 89);
  g->Dequantize(89, 90, 0.08599609136581421, 0);
  g->Unary(ynn_unary_square, 90, 91);
  g->Reduce(ynn_reduce_sum, 91, 7310, {2}, true);
  g->ShapeProduct(91, 7309, {2});
  g->Binary(ynn_binary_divide, 7310, 7309, 92);
  g->Binary(ynn_binary_add, 92, 8779, 93);
  g->Unary(ynn_unary_rsqrt, 93, 94);
  g->Binary(ynn_binary_multiply, 90, 94, 95);
  g->Binary(ynn_binary_multiply, 95, 9488, 97);
  g->Binary(ynn_binary_add, 97, 72, 98);
}

// Scope: "Layer7 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(429, 99, {0,0,7,0}, {-1,-1,1,-1});
  g->Reshape(99, 100, {1,1,256});
  g->Unary(ynn_unary_square, 100, 101);
  g->Reduce(ynn_reduce_sum, 101, 7312, {2}, true);
  g->ShapeProduct(101, 7311, {2});
  g->Binary(ynn_binary_divide, 7312, 7311, 102);
  g->Binary(ynn_binary_add, 102, 8779, 103);
  g->Unary(ynn_unary_rsqrt, 103, 104);
  g->Binary(ynn_binary_multiply, 100, 104, 105);
  g->Binary(ynn_binary_multiply, 105, 9533, 106);
  g->Binary(ynn_binary_multiply, 9573, 8783, 109);
  g->Binary(ynn_binary_add, 106, 109, 110);
  g->Binary(ynn_binary_multiply, 110, 8777, 111);
  g->Quantize(98, 112, 0.16048018634319305, 0);
  g->Transpose(9485, 5122, {1,0});
  g->Binary(ynn_binary_multiply, 5119, 5121, 5117);
  g->Dot(112, 5122, YNN_INVALID_VALUE_ID, 5116, 1);
  g->DequantizeTensor(5116, YNN_INVALID_VALUE_ID, 5117, 5118);
  g->QuantizeTensor(5118, 8727, 5120, 113);
  g->Dequantize(113, 114, 0.04675197973847389, 0);
  g->Polynomial(114, 7315, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7315, 7316);
  g->Binary(ynn_binary_add, 7316, 7293, 7313);
  g->Binary(ynn_binary_multiply, 114, 7305, 7314);
  g->Binary(ynn_binary_multiply, 7314, 7313, 115);
  g->Binary(ynn_binary_multiply, 115, 111, 116);
  g->Quantize(116, 117, 0.15748032927513123, 0);
  g->Transpose(9486, 5129, {1,0});
  g->Binary(ynn_binary_multiply, 5126, 5128, 5124);
  g->Dot(117, 5129, YNN_INVALID_VALUE_ID, 5123, 1);
  g->DequantizeTensor(5123, YNN_INVALID_VALUE_ID, 5124, 5125);
  g->QuantizeTensor(5125, 8727, 5127, 118);
  g->Dequantize(118, 119, 0.07159535586833954, 0);
  g->Unary(ynn_unary_square, 119, 120);
  g->Reduce(ynn_reduce_sum, 120, 7318, {2}, true);
  g->ShapeProduct(120, 7317, {2});
  g->Binary(ynn_binary_divide, 7318, 7317, 121);
  g->Binary(ynn_binary_add, 121, 8779, 122);
  g->Unary(ynn_unary_rsqrt, 122, 123);
  g->Binary(ynn_binary_multiply, 119, 123, 124);
  g->Binary(ynn_binary_multiply, 124, 9489, 125);
  g->Binary(ynn_binary_add, 98, 125, 126);
  g->Binary(ynn_binary_multiply, 126, 9481, 127);
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
  g->Quantize(134, 135, 0.18602856993675232, 0);
  g->Transpose(9509, 5141, {1,0});
  g->Binary(ynn_binary_multiply, 5138, 5140, 5136);
  g->Dot(135, 5141, YNN_INVALID_VALUE_ID, 5135, 1);
  g->DequantizeTensor(5135, YNN_INVALID_VALUE_ID, 5136, 5137);
  g->QuantizeTensor(5137, 8727, 5139, 136);
  g->Dequantize(136, 137, 0.3366141617298126, 0);
  g->SplitDim(137, 138, 2, {2,256});
  g->FuseDims(138, 140, 1, 2);
  g->SplitDim(140, 139, 1, {2,1});
  g->Unary(ynn_unary_square, 139, 142);
  g->Reduce(ynn_reduce_sum, 142, 7322, {3}, true);
  g->ShapeProduct(142, 7321, {3});
  g->Binary(ynn_binary_divide, 7322, 7321, 143);
  g->Binary(ynn_binary_add, 143, 8779, 144);
  g->Unary(ynn_unary_rsqrt, 144, 145);
  g->Binary(ynn_binary_multiply, 139, 145, 146);
  g->Binary(ynn_binary_multiply, 146, 9508, 147);
  g->Slice(147, 148, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(147, 149, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 149, 150);
  g->Concat({150,148}, 151, 3);
  g->Binary(ynn_binary_multiply, 147, 3231, 153);
  g->Binary(ynn_binary_multiply, 151, 4329, 154);
  g->Binary(ynn_binary_add, 153, 154, 155);
  g->Transpose(9513, 5146, {1,0});
  g->Binary(ynn_binary_multiply, 5138, 5145, 5143);
  g->Dot(135, 5146, YNN_INVALID_VALUE_ID, 5142, 1);
  g->DequantizeTensor(5142, YNN_INVALID_VALUE_ID, 5143, 5144);
  g->QuantizeTensor(5144, 8727, 5139, 156);
  g->Dequantize(156, 157, 0.3366141617298126, 0);
  g->SplitDim(157, 158, 2, {2,256});
  g->FuseDims(158, 160, 1, 2);
  g->SplitDim(160, 159, 1, {2,1});
  g->Unary(ynn_unary_square, 159, 161);
  g->Reduce(ynn_reduce_sum, 161, 7328, {3}, true);
  g->ShapeProduct(161, 7327, {3});
  g->Binary(ynn_binary_divide, 7328, 7327, 162);
  g->Binary(ynn_binary_add, 162, 8779, 164);
  g->Unary(ynn_unary_rsqrt, 164, 165);
  g->Binary(ynn_binary_multiply, 159, 165, 166);
}

// Scope: "Layer8 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(155, 167, 0.005679573863744736, 0);
  g->Append(8750, 167, 9599, 2, s2, slinky::expr(int64_t{1}));
  g->View(9599, 9647, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(166, 168, 0.047244105488061905, 0);
  g->Append(8774, 168, 9623, 2, s2, slinky::expr(int64_t{1}));
  g->View(9623, 9671, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer8 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(9512, 5152, {1,0});
  g->Binary(ynn_binary_multiply, 5138, 5151, 5148);
  g->Dot(135, 5152, YNN_INVALID_VALUE_ID, 5147, 1);
  g->DequantizeTensor(5147, YNN_INVALID_VALUE_ID, 5148, 5149);
  g->QuantizeTensor(5149, 8727, 5150, 170);
  g->Dequantize(170, 171, 0.31102362275123596, 0);
  g->SplitDim(171, 172, 2, {8,256});
  g->FuseDims(172, 174, 1, 2);
  g->SplitDim(174, 173, 1, {8,1});
  g->Unary(ynn_unary_square, 173, 175);
  g->Reduce(ynn_reduce_sum, 175, 7330, {3}, true);
  g->ShapeProduct(175, 7329, {3});
  g->Binary(ynn_binary_divide, 7330, 7329, 176);
  g->Binary(ynn_binary_add, 176, 8779, 177);
  g->Unary(ynn_unary_rsqrt, 177, 178);
  g->Binary(ynn_binary_multiply, 173, 178, 179);
  g->Binary(ynn_binary_multiply, 179, 9511, 180);
  g->Slice(180, 182, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(180, 183, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 183, 184);
  g->Concat({184,182}, 185, 3);
  g->Binary(ynn_binary_multiply, 180, 3231, 186);
  g->Binary(ynn_binary_multiply, 185, 4329, 187);
  g->Binary(ynn_binary_add, 186, 187, 188);
}

// Scope: "Layer8 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9647, 189, 0.005679573863744736, 0);
  g->Dequantize(9671, 190, 0.047244105488061905, 0);
  g->Slice(188, 191, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(189, 193, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(190, 194, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(191, 193, 195, false, true);
  g->Mask(195, 8866, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8866, 7334, {-1}, true);
  g->Binary(ynn_binary_subtract, 8866, 7334, 7331);
  g->Unary(ynn_unary_exp, 7331, 7332);
  g->Reduce(ynn_reduce_sum, 7332, 7335, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 7335, 7333);
  g->Binary(ynn_binary_multiply, 7332, 7333, 196);
  g->Matmul(196, 194, 197, false, false);
  g->Slice(188, 198, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(189, 199, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(190, 200, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(198, 199, 201, false, true);
  g->Mask(201, 8867, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8867, 7339, {-1}, true);
  g->Binary(ynn_binary_subtract, 8867, 7339, 7336);
  g->Unary(ynn_unary_exp, 7336, 7337);
  g->Reduce(ynn_reduce_sum, 7337, 7340, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 7340, 7338);
  g->Binary(ynn_binary_multiply, 7337, 7338, 203);
  g->Matmul(203, 200, 204, false, false);
  g->Concat({197,204}, 205, 1);
}

// Scope: "Layer8 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(205, 207, 1, 2);
  g->SplitDim(207, 206, 1, {1,8});
  g->FuseDims(206, 208, 2, 2);
  g->Quantize(208, 209, 0.023375993594527245, 0);
  g->Transpose(9510, 5166, {1,0});
  g->Binary(ynn_binary_multiply, 5163, 5165, 5161);
  g->Dot(209, 5166, YNN_INVALID_VALUE_ID, 5160, 1);
  g->DequantizeTensor(5160, YNN_INVALID_VALUE_ID, 5161, 5162);
  g->QuantizeTensor(5162, 8727, 5164, 210);
  g->Dequantize(210, 211, 0.04781534895300865, 0);
}

// Scope: "Layer8 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 127, 128);
  g->Reduce(ynn_reduce_sum, 128, 7320, {2}, true);
  g->ShapeProduct(128, 7319, {2});
  g->Binary(ynn_binary_divide, 7320, 7319, 130);
  g->Binary(ynn_binary_add, 130, 8779, 131);
  g->Unary(ynn_unary_rsqrt, 131, 132);
  g->Binary(ynn_binary_multiply, 127, 132, 133);
  g->Binary(ynn_binary_multiply, 133, 9497, 134);
  BuildLayer8AttentionKvProjection(ctx);
  BuildLayer8AttentionCacheUpdate(ctx);
  BuildLayer8AttentionQueryProjection(ctx);
  BuildLayer8AttentionSdpa(ctx);
  BuildLayer8AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 211, 212);
  g->Reduce(ynn_reduce_sum, 212, 7344, {2}, true);
  g->ShapeProduct(212, 7343, {2});
  g->Binary(ynn_binary_divide, 7344, 7343, 215);
  g->Binary(ynn_binary_add, 215, 8779, 216);
  g->Unary(ynn_unary_rsqrt, 216, 217);
  g->Binary(ynn_binary_multiply, 211, 217, 218);
  g->Binary(ynn_binary_multiply, 218, 9504, 219);
  g->Binary(ynn_binary_add, 219, 127, 220);
}

// Scope: "Layer8 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 220, 221);
  g->Reduce(ynn_reduce_sum, 221, 7346, {2}, true);
  g->ShapeProduct(221, 7345, {2});
  g->Binary(ynn_binary_divide, 7346, 7345, 222);
  g->Binary(ynn_binary_add, 222, 8779, 223);
  g->Unary(ynn_unary_rsqrt, 223, 224);
  g->Binary(ynn_binary_multiply, 220, 224, 226);
  g->Binary(ynn_binary_multiply, 226, 9507, 227);
  g->Quantize(227, 228, 0.028420308604836464, 0);
  g->Transpose(9501, 5180, {1,0});
  g->Binary(ynn_binary_multiply, 5177, 5179, 5175);
  g->Dot(228, 5180, YNN_INVALID_VALUE_ID, 5174, 1);
  g->DequantizeTensor(5174, YNN_INVALID_VALUE_ID, 5175, 5176);
  g->QuantizeTensor(5176, 8727, 5178, 229);
  g->Dequantize(229, 230, 0.04625985398888588, 0);
  g->Transpose(9500, 5185, {1,0});
  g->Binary(ynn_binary_multiply, 5177, 5184, 5182);
  g->Dot(228, 5185, YNN_INVALID_VALUE_ID, 5181, 1);
  g->DequantizeTensor(5181, YNN_INVALID_VALUE_ID, 5182, 5183);
  g->QuantizeTensor(5183, 8727, 5178, 231);
  g->Dequantize(231, 232, 0.04625985398888588, 0);
  g->Polynomial(232, 7349, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7349, 7350);
  g->Binary(ynn_binary_add, 7350, 7293, 7347);
  g->Binary(ynn_binary_multiply, 232, 7305, 7348);
  g->Binary(ynn_binary_multiply, 7348, 7347, 233);
  g->Binary(ynn_binary_multiply, 230, 233, 234);
  g->Quantize(234, 236, 0.11958662420511246, 0);
  g->Transpose(9499, 5192, {1,0});
  g->Binary(ynn_binary_multiply, 5189, 5191, 5187);
  g->Dot(236, 5192, YNN_INVALID_VALUE_ID, 5186, 1);
  g->DequantizeTensor(5186, YNN_INVALID_VALUE_ID, 5187, 5188);
  g->QuantizeTensor(5188, 8727, 5190, 237);
  g->Dequantize(237, 238, 0.07705982774496078, 0);
  g->Unary(ynn_unary_square, 238, 239);
  g->Reduce(ynn_reduce_sum, 239, 7352, {2}, true);
  g->ShapeProduct(239, 7351, {2});
  g->Binary(ynn_binary_divide, 7352, 7351, 240);
  g->Binary(ynn_binary_add, 240, 8779, 241);
  g->Unary(ynn_unary_rsqrt, 241, 242);
  g->Binary(ynn_binary_multiply, 238, 242, 243);
  g->Binary(ynn_binary_multiply, 243, 9505, 244);
  g->Binary(ynn_binary_add, 244, 220, 245);
}

// Scope: "Layer8 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(429, 247, {0,0,8,0}, {-1,-1,1,-1});
  g->Reshape(247, 248, {1,1,256});
  g->Unary(ynn_unary_square, 248, 249);
  g->Reduce(ynn_reduce_sum, 249, 7354, {2}, true);
  g->ShapeProduct(249, 7353, {2});
  g->Binary(ynn_binary_divide, 7354, 7353, 250);
  g->Binary(ynn_binary_add, 250, 8779, 251);
  g->Unary(ynn_unary_rsqrt, 251, 252);
  g->Binary(ynn_binary_multiply, 248, 252, 253);
  g->Binary(ynn_binary_multiply, 253, 9533, 254);
  g->Binary(ynn_binary_multiply, 9574, 8783, 255);
  g->Binary(ynn_binary_add, 254, 255, 256);
  g->Binary(ynn_binary_multiply, 256, 8777, 258);
  g->Quantize(245, 259, 0.4868268370628357, 0);
  g->Transpose(9502, 5199, {1,0});
  g->Binary(ynn_binary_multiply, 5196, 5198, 5194);
  g->Dot(259, 5199, YNN_INVALID_VALUE_ID, 5193, 1);
  g->DequantizeTensor(5193, YNN_INVALID_VALUE_ID, 5194, 5195);
  g->QuantizeTensor(5195, 8727, 5197, 260);
  g->Dequantize(260, 261, 0.03026575781404972, 0);
  g->Polynomial(261, 7357, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7357, 7358);
  g->Binary(ynn_binary_add, 7358, 7293, 7355);
  g->Binary(ynn_binary_multiply, 261, 7305, 7356);
  g->Binary(ynn_binary_multiply, 7356, 7355, 262);
  g->Binary(ynn_binary_multiply, 262, 258, 263);
  g->Quantize(263, 264, 0.12795276939868927, 0);
  g->Transpose(9503, 5206, {1,0});
  g->Binary(ynn_binary_multiply, 5203, 5205, 5201);
  g->Dot(264, 5206, YNN_INVALID_VALUE_ID, 5200, 1);
  g->DequantizeTensor(5200, YNN_INVALID_VALUE_ID, 5201, 5202);
  g->QuantizeTensor(5202, 8727, 5204, 265);
  g->Dequantize(265, 266, 0.04510452225804329, 0);
  g->Unary(ynn_unary_square, 266, 267);
  g->Reduce(ynn_reduce_sum, 267, 7360, {2}, true);
  g->ShapeProduct(267, 7359, {2});
  g->Binary(ynn_binary_divide, 7360, 7359, 269);
  g->Binary(ynn_binary_add, 269, 8779, 270);
  g->Unary(ynn_unary_rsqrt, 270, 271);
  g->Binary(ynn_binary_multiply, 266, 271, 272);
  g->Binary(ynn_binary_multiply, 272, 9506, 273);
  g->Binary(ynn_binary_add, 245, 273, 274);
  g->Binary(ynn_binary_multiply, 274, 9498, 275);
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
  g->Quantize(282, 283, 0.06997107714414597, 0);
  g->Transpose(9526, 5213, {1,0});
  g->Binary(ynn_binary_multiply, 5210, 5212, 5208);
  g->Dot(283, 5213, YNN_INVALID_VALUE_ID, 5207, 1);
  g->DequantizeTensor(5207, YNN_INVALID_VALUE_ID, 5208, 5209);
  g->QuantizeTensor(5209, 8727, 5211, 284);
  g->Dequantize(284, 285, 0.11663386225700378, 0);
  g->SplitDim(285, 286, 2, {2,256});
  g->FuseDims(286, 288, 1, 2);
  g->SplitDim(288, 287, 1, {2,1});
  g->Unary(ynn_unary_square, 287, 289);
  g->Reduce(ynn_reduce_sum, 289, 7364, {3}, true);
  g->ShapeProduct(289, 7363, {3});
  g->Binary(ynn_binary_divide, 7364, 7363, 290);
  g->Binary(ynn_binary_add, 290, 8779, 292);
  g->Unary(ynn_unary_rsqrt, 292, 293);
  g->Binary(ynn_binary_multiply, 287, 293, 294);
  g->Binary(ynn_binary_multiply, 294, 9525, 295);
  g->Slice(295, 296, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(295, 297, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 297, 298);
  g->Concat({298,296}, 299, 3);
  g->Binary(ynn_binary_multiply, 295, 3231, 300);
  g->Binary(ynn_binary_multiply, 299, 4329, 301);
  g->Binary(ynn_binary_add, 300, 301, 303);
  g->Transpose(9530, 5218, {1,0});
  g->Binary(ynn_binary_multiply, 5210, 5217, 5215);
  g->Dot(283, 5218, YNN_INVALID_VALUE_ID, 5214, 1);
  g->DequantizeTensor(5214, YNN_INVALID_VALUE_ID, 5215, 5216);
  g->QuantizeTensor(5216, 8727, 5211, 304);
  g->Dequantize(304, 305, 0.11663386225700378, 0);
  g->SplitDim(305, 306, 2, {2,256});
  g->FuseDims(306, 308, 1, 2);
  g->SplitDim(308, 307, 1, {2,1});
  g->Unary(ynn_unary_square, 307, 309);
  g->Reduce(ynn_reduce_sum, 309, 7366, {3}, true);
  g->ShapeProduct(309, 7365, {3});
  g->Binary(ynn_binary_divide, 7366, 7365, 310);
  g->Binary(ynn_binary_add, 310, 8779, 311);
  g->Unary(ynn_unary_rsqrt, 311, 312);
  g->Binary(ynn_binary_multiply, 307, 312, 314);
}

// Scope: "Layer9 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(303, 315, 0.005719248205423355, 0);
  g->Append(8751, 315, 9600, 2, s2, slinky::expr(int64_t{1}));
  g->View(9600, 9648, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(314, 316, 0.047244105488061905, 0);
  g->Append(8775, 316, 9624, 2, s2, slinky::expr(int64_t{1}));
  g->View(9624, 9672, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer9 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(9529, 5224, {1,0});
  g->Binary(ynn_binary_multiply, 5210, 5223, 5220);
  g->Dot(283, 5224, YNN_INVALID_VALUE_ID, 5219, 1);
  g->DequantizeTensor(5219, YNN_INVALID_VALUE_ID, 5220, 5221);
  g->QuantizeTensor(5221, 8727, 5222, 317);
  g->Dequantize(317, 318, 0.1058070957660675, 0);
  g->SplitDim(318, 321, 2, {8,256});
  g->FuseDims(321, 323, 1, 2);
  g->SplitDim(323, 322, 1, {8,1});
  g->Unary(ynn_unary_square, 322, 324);
  g->Reduce(ynn_reduce_sum, 324, 7370, {3}, true);
  g->ShapeProduct(324, 7369, {3});
  g->Binary(ynn_binary_divide, 7370, 7369, 325);
  g->Binary(ynn_binary_add, 325, 8779, 326);
  g->Unary(ynn_unary_rsqrt, 326, 327);
  g->Binary(ynn_binary_multiply, 322, 327, 328);
  g->Binary(ynn_binary_multiply, 328, 9528, 329);
  g->Slice(329, 330, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(329, 331, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 331, 333);
  g->Concat({333,330}, 334, 3);
  g->Binary(ynn_binary_multiply, 329, 3231, 335);
  g->Binary(ynn_binary_multiply, 334, 4329, 336);
  g->Binary(ynn_binary_add, 335, 336, 337);
}

// Scope: "Layer9 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9648, 338, 0.005719248205423355, 0);
  g->Dequantize(9672, 339, 0.047244105488061905, 0);
  g->Slice(337, 340, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(338, 341, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(339, 342, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(340, 341, 344, false, true);
  g->Mask(344, 8868, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8868, 7374, {-1}, true);
  g->Binary(ynn_binary_subtract, 8868, 7374, 7371);
  g->Unary(ynn_unary_exp, 7371, 7372);
  g->Reduce(ynn_reduce_sum, 7372, 7375, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 7375, 7373);
  g->Binary(ynn_binary_multiply, 7372, 7373, 345);
  g->Matmul(345, 342, 346, false, false);
  g->Slice(337, 347, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(338, 348, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(339, 349, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(347, 348, 350, false, true);
  g->Mask(350, 8869, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8869, 7379, {-1}, true);
  g->Binary(ynn_binary_subtract, 8869, 7379, 7376);
  g->Unary(ynn_unary_exp, 7376, 7377);
  g->Reduce(ynn_reduce_sum, 7377, 7380, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 7380, 7378);
  g->Binary(ynn_binary_multiply, 7377, 7378, 351);
  g->Matmul(351, 349, 353, false, false);
  g->Concat({346,353}, 354, 1);
}

// Scope: "Layer9 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(354, 356, 1, 2);
  g->SplitDim(356, 355, 1, {1,8});
  g->FuseDims(355, 357, 2, 2);
  g->Quantize(357, 358, 0.023375993594527245, 0);
  g->Transpose(9527, 5230, {1,0});
  g->Binary(ynn_binary_multiply, 5163, 5229, 5226);
  g->Dot(358, 5230, YNN_INVALID_VALUE_ID, 5225, 1);
  g->DequantizeTensor(5225, YNN_INVALID_VALUE_ID, 5226, 5227);
  g->QuantizeTensor(5227, 8727, 5228, 359);
  g->Dequantize(359, 360, 0.04783705249428749, 0);
}

// Scope: "Layer9 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 275, 276);
  g->Reduce(ynn_reduce_sum, 276, 7362, {2}, true);
  g->ShapeProduct(276, 7361, {2});
  g->Binary(ynn_binary_divide, 7362, 7361, 277);
  g->Binary(ynn_binary_add, 277, 8779, 278);
  g->Unary(ynn_unary_rsqrt, 278, 280);
  g->Binary(ynn_binary_multiply, 275, 280, 281);
  g->Binary(ynn_binary_multiply, 281, 9514, 282);
  BuildLayer9AttentionKvProjection(ctx);
  BuildLayer9AttentionCacheUpdate(ctx);
  BuildLayer9AttentionQueryProjection(ctx);
  BuildLayer9AttentionSdpa(ctx);
  BuildLayer9AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 360, 361);
  g->Reduce(ynn_reduce_sum, 361, 7382, {2}, true);
  g->ShapeProduct(361, 7381, {2});
  g->Binary(ynn_binary_divide, 7382, 7381, 362);
  g->Binary(ynn_binary_add, 362, 8779, 363);
  g->Unary(ynn_unary_rsqrt, 363, 365);
  g->Binary(ynn_binary_multiply, 360, 365, 366);
  g->Binary(ynn_binary_multiply, 366, 9521, 367);
  g->Binary(ynn_binary_add, 367, 275, 368);
}

// Scope: "Layer9 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 368, 369);
  g->Reduce(ynn_reduce_sum, 369, 7384, {2}, true);
  g->ShapeProduct(369, 7383, {2});
  g->Binary(ynn_binary_divide, 7384, 7383, 370);
  g->Binary(ynn_binary_add, 370, 8779, 371);
  g->Unary(ynn_unary_rsqrt, 371, 372);
  g->Binary(ynn_binary_multiply, 368, 372, 373);
  g->Binary(ynn_binary_multiply, 373, 9524, 374);
  g->Quantize(374, 376, 0.017706703394651413, 0);
  g->Transpose(9518, 5237, {1,0});
  g->Binary(ynn_binary_multiply, 5234, 5236, 5232);
  g->Dot(376, 5237, YNN_INVALID_VALUE_ID, 5231, 1);
  g->DequantizeTensor(5231, YNN_INVALID_VALUE_ID, 5232, 5233);
  g->QuantizeTensor(5233, 8727, 5235, 377);
  g->Dequantize(377, 378, 0.025836624205112457, 0);
  g->Transpose(9517, 5242, {1,0});
  g->Binary(ynn_binary_multiply, 5234, 5241, 5239);
  g->Dot(376, 5242, YNN_INVALID_VALUE_ID, 5238, 1);
  g->DequantizeTensor(5238, YNN_INVALID_VALUE_ID, 5239, 5240);
  g->QuantizeTensor(5240, 8727, 5235, 379);
  g->Dequantize(379, 380, 0.025836624205112457, 0);
  g->Polynomial(380, 7387, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7387, 7388);
  g->Binary(ynn_binary_add, 7388, 7293, 7385);
  g->Binary(ynn_binary_multiply, 380, 7305, 7386);
  g->Binary(ynn_binary_multiply, 7386, 7385, 381);
  g->Binary(ynn_binary_multiply, 378, 381, 382);
  g->Quantize(382, 383, 0.04773623123764992, 0);
  g->Transpose(9516, 5249, {1,0});
  g->Binary(ynn_binary_multiply, 5246, 5248, 5244);
  g->Dot(383, 5249, YNN_INVALID_VALUE_ID, 5243, 1);
  g->DequantizeTensor(5243, YNN_INVALID_VALUE_ID, 5244, 5245);
  g->QuantizeTensor(5245, 8727, 5247, 384);
  g->Dequantize(384, 386, 0.04407493770122528, 0);
  g->Unary(ynn_unary_square, 386, 387);
  g->Reduce(ynn_reduce_sum, 387, 7390, {2}, true);
  g->ShapeProduct(387, 7389, {2});
  g->Binary(ynn_binary_divide, 7390, 7389, 388);
  g->Binary(ynn_binary_add, 388, 8779, 389);
  g->Unary(ynn_unary_rsqrt, 389, 390);
  g->Binary(ynn_binary_multiply, 386, 390, 391);
  g->Binary(ynn_binary_multiply, 391, 9522, 392);
  g->Binary(ynn_binary_add, 392, 368, 393);
}

// Scope: "Layer9 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(429, 394, {0,0,9,0}, {-1,-1,1,-1});
  g->Reshape(394, 395, {1,1,256});
  g->Unary(ynn_unary_square, 395, 397);
  g->Reduce(ynn_reduce_sum, 397, 7392, {2}, true);
  g->ShapeProduct(397, 7391, {2});
  g->Binary(ynn_binary_divide, 7392, 7391, 398);
  g->Binary(ynn_binary_add, 398, 8779, 399);
  g->Unary(ynn_unary_rsqrt, 399, 400);
  g->Binary(ynn_binary_multiply, 395, 400, 401);
  g->Binary(ynn_binary_multiply, 401, 9533, 402);
  g->Binary(ynn_binary_multiply, 9575, 8783, 403);
  g->Binary(ynn_binary_add, 402, 403, 404);
  g->Binary(ynn_binary_multiply, 404, 8777, 405);
  g->Quantize(393, 406, 0.20032060146331787, 0);
  g->Transpose(9519, 5263, {1,0});
  g->Binary(ynn_binary_multiply, 5260, 5262, 5258);
  g->Dot(406, 5263, YNN_INVALID_VALUE_ID, 5257, 1);
  g->DequantizeTensor(5257, YNN_INVALID_VALUE_ID, 5258, 5259);
  g->QuantizeTensor(5259, 8727, 5261, 408);
  g->Dequantize(408, 409, 0.047244105488061905, 0);
  g->Polynomial(409, 7395, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7395, 7396);
  g->Binary(ynn_binary_add, 7396, 7293, 7393);
  g->Binary(ynn_binary_multiply, 409, 7305, 7394);
  g->Binary(ynn_binary_multiply, 7394, 7393, 410);
  g->Binary(ynn_binary_multiply, 410, 405, 411);
  g->Quantize(411, 412, 0.3326771557331085, 0);
  g->Transpose(9520, 5270, {1,0});
  g->Binary(ynn_binary_multiply, 5267, 5269, 5265);
  g->Dot(412, 5270, YNN_INVALID_VALUE_ID, 5264, 1);
  g->DequantizeTensor(5264, YNN_INVALID_VALUE_ID, 5265, 5266);
  g->QuantizeTensor(5266, 8727, 5268, 413);
  g->Dequantize(413, 414, 0.11236792802810669, 0);
  g->Unary(ynn_unary_square, 414, 415);
  g->Reduce(ynn_reduce_sum, 415, 7398, {2}, true);
  g->ShapeProduct(415, 7397, {2});
  g->Binary(ynn_binary_divide, 7398, 7397, 416);
  g->Binary(ynn_binary_add, 416, 8779, 417);
  g->Unary(ynn_unary_rsqrt, 417, 419);
  g->Binary(ynn_binary_multiply, 414, 419, 420);
  g->Binary(ynn_binary_multiply, 420, 9523, 421);
  g->Binary(ynn_binary_add, 393, 421, 422);
  g->Binary(ynn_binary_multiply, 422, 9515, 423);
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
  g->Quantize(431, 432, 0.05069896951317787, 0);
  g->Transpose(8917, 5277, {1,0});
  g->Binary(ynn_binary_multiply, 5274, 5276, 5272);
  g->Dot(432, 5277, YNN_INVALID_VALUE_ID, 5271, 1);
  g->DequantizeTensor(5271, YNN_INVALID_VALUE_ID, 5272, 5273);
  g->QuantizeTensor(5273, 8727, 5275, 433);
  g->Dequantize(433, 434, 0.06446851044893265, 0);
  g->SplitDim(434, 435, 2, {2,256});
  g->FuseDims(435, 437, 1, 2);
  g->SplitDim(437, 436, 1, {2,1});
  g->Unary(ynn_unary_square, 436, 438);
  g->Reduce(ynn_reduce_sum, 438, 7406, {3}, true);
  g->ShapeProduct(438, 7405, {3});
  g->Binary(ynn_binary_divide, 7406, 7405, 439);
  g->Binary(ynn_binary_add, 439, 8779, 440);
  g->Unary(ynn_unary_rsqrt, 440, 441);
  g->Binary(ynn_binary_multiply, 436, 441, 443);
  g->Binary(ynn_binary_multiply, 443, 8916, 444);
  g->Slice(444, 445, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(444, 446, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 446, 447);
  g->Concat({447,445}, 448, 3);
  g->Binary(ynn_binary_multiply, 444, 3231, 449);
  g->Binary(ynn_binary_multiply, 448, 4329, 450);
  g->Binary(ynn_binary_add, 449, 450, 451);
  g->Transpose(8921, 5282, {1,0});
  g->Binary(ynn_binary_multiply, 5274, 5281, 5279);
  g->Dot(432, 5282, YNN_INVALID_VALUE_ID, 5278, 1);
  g->DequantizeTensor(5278, YNN_INVALID_VALUE_ID, 5279, 5280);
  g->QuantizeTensor(5280, 8727, 5275, 453);
  g->Dequantize(453, 454, 0.06446851044893265, 0);
  g->SplitDim(454, 455, 2, {2,256});
  g->FuseDims(455, 457, 1, 2);
  g->SplitDim(457, 456, 1, {2,1});
  g->Unary(ynn_unary_square, 456, 458);
  g->Reduce(ynn_reduce_sum, 458, 7408, {3}, true);
  g->ShapeProduct(458, 7407, {3});
  g->Binary(ynn_binary_divide, 7408, 7407, 459);
  g->Binary(ynn_binary_add, 459, 8779, 460);
  g->Unary(ynn_unary_rsqrt, 460, 461);
  g->Binary(ynn_binary_multiply, 456, 461, 462);
}

// Scope: "Layer10 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(451, 463, 0.0057654301635921, 0);
  g->Append(8730, 463, 9579, 2, s2, slinky::expr(int64_t{1}));
  g->View(9579, 9627, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(462, 465, 0.047244105488061905, 0);
  g->Append(8754, 465, 9603, 2, s2, slinky::expr(int64_t{1}));
  g->View(9603, 9651, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer10 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(8920, 5295, {1,0});
  g->Binary(ynn_binary_multiply, 5274, 5294, 5291);
  g->Dot(432, 5295, YNN_INVALID_VALUE_ID, 5290, 1);
  g->DequantizeTensor(5290, YNN_INVALID_VALUE_ID, 5291, 5292);
  g->QuantizeTensor(5292, 8727, 5293, 466);
  g->Dequantize(466, 467, 0.06840551644563675, 0);
  g->SplitDim(467, 468, 2, {8,256});
  g->FuseDims(468, 470, 1, 2);
  g->SplitDim(470, 469, 1, {8,1});
  g->Unary(ynn_unary_square, 469, 472);
  g->Reduce(ynn_reduce_sum, 472, 7410, {3}, true);
  g->ShapeProduct(472, 7409, {3});
  g->Binary(ynn_binary_divide, 7410, 7409, 473);
  g->Binary(ynn_binary_add, 473, 8779, 474);
  g->Unary(ynn_unary_rsqrt, 474, 475);
  g->Binary(ynn_binary_multiply, 469, 475, 476);
  g->Binary(ynn_binary_multiply, 476, 8919, 477);
  g->Slice(477, 478, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(477, 479, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 479, 480);
  g->Concat({480,478}, 481, 3);
  g->Binary(ynn_binary_multiply, 477, 3231, 483);
  g->Binary(ynn_binary_multiply, 481, 4329, 484);
  g->Binary(ynn_binary_add, 483, 484, 485);
}

// Scope: "Layer10 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9627, 486, 0.0057654301635921, 0);
  g->Dequantize(9651, 487, 0.047244105488061905, 0);
  g->Slice(485, 488, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(486, 489, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(487, 490, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(488, 489, 491, false, true);
  g->Mask(491, 8788, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8788, 7416, {-1}, true);
  g->Binary(ynn_binary_subtract, 8788, 7416, 7413);
  g->Unary(ynn_unary_exp, 7413, 7414);
  g->Reduce(ynn_reduce_sum, 7414, 7417, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 7417, 7415);
  g->Binary(ynn_binary_multiply, 7414, 7415, 493);
  g->Matmul(493, 490, 494, false, false);
  g->Slice(485, 495, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(486, 496, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(487, 497, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(495, 496, 498, false, true);
  g->Mask(498, 8789, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8789, 7421, {-1}, true);
  g->Binary(ynn_binary_subtract, 8789, 7421, 7418);
  g->Unary(ynn_unary_exp, 7418, 7419);
  g->Reduce(ynn_reduce_sum, 7419, 7422, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 7422, 7420);
  g->Binary(ynn_binary_multiply, 7419, 7420, 499);
  g->Matmul(499, 497, 500, false, false);
  g->Concat({494,500}, 501, 1);
}

// Scope: "Layer10 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(501, 504, 1, 2);
  g->SplitDim(504, 503, 1, {1,8});
  g->FuseDims(503, 505, 2, 2);
  g->Quantize(505, 506, 0.02362205646932125, 0);
  g->Transpose(8918, 5302, {1,0});
  g->Binary(ynn_binary_multiply, 5299, 5301, 5297);
  g->Dot(506, 5302, YNN_INVALID_VALUE_ID, 5296, 1);
  g->DequantizeTensor(5296, YNN_INVALID_VALUE_ID, 5297, 5298);
  g->QuantizeTensor(5298, 8727, 5300, 507);
  g->Dequantize(507, 508, 0.09525793045759201, 0);
}

// Scope: "Layer10 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 423, 424);
  g->Reduce(ynn_reduce_sum, 424, 7400, {2}, true);
  g->ShapeProduct(424, 7399, {2});
  g->Binary(ynn_binary_divide, 7400, 7399, 425);
  g->Binary(ynn_binary_add, 425, 8779, 426);
  g->Unary(ynn_unary_rsqrt, 426, 427);
  g->Binary(ynn_binary_multiply, 423, 427, 428);
  g->Binary(ynn_binary_multiply, 428, 8905, 431);
  BuildLayer10AttentionKvProjection(ctx);
  BuildLayer10AttentionCacheUpdate(ctx);
  BuildLayer10AttentionQueryProjection(ctx);
  BuildLayer10AttentionSdpa(ctx);
  BuildLayer10AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 508, 509);
  g->Reduce(ynn_reduce_sum, 509, 7424, {2}, true);
  g->ShapeProduct(509, 7423, {2});
  g->Binary(ynn_binary_divide, 7424, 7423, 510);
  g->Binary(ynn_binary_add, 510, 8779, 511);
  g->Unary(ynn_unary_rsqrt, 511, 512);
  g->Binary(ynn_binary_multiply, 508, 512, 513);
  g->Binary(ynn_binary_multiply, 513, 8912, 515);
  g->Binary(ynn_binary_add, 515, 423, 516);
}

// Scope: "Layer10 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 516, 517);
  g->Reduce(ynn_reduce_sum, 517, 7426, {2}, true);
  g->ShapeProduct(517, 7425, {2});
  g->Binary(ynn_binary_divide, 7426, 7425, 518);
  g->Binary(ynn_binary_add, 518, 8779, 519);
  g->Unary(ynn_unary_rsqrt, 519, 520);
  g->Binary(ynn_binary_multiply, 516, 520, 521);
  g->Binary(ynn_binary_multiply, 521, 8915, 522);
  g->Quantize(522, 523, 0.015853581950068474, 0);
  g->Transpose(8909, 5308, {1,0});
  g->Binary(ynn_binary_multiply, 5306, 5307, 5304);
  g->Dot(523, 5308, YNN_INVALID_VALUE_ID, 5303, 1);
  g->DequantizeTensor(5303, YNN_INVALID_VALUE_ID, 5304, 5305);
  g->QuantizeTensor(5305, 8727, 5163, 524);
  g->Dequantize(524, 526, 0.023375993594527245, 0);
  g->Transpose(8908, 5313, {1,0});
  g->Binary(ynn_binary_multiply, 5306, 5312, 5310);
  g->Dot(523, 5313, YNN_INVALID_VALUE_ID, 5309, 1);
  g->DequantizeTensor(5309, YNN_INVALID_VALUE_ID, 5310, 5311);
  g->QuantizeTensor(5311, 8727, 5163, 527);
  g->Dequantize(527, 528, 0.023375993594527245, 0);
  g->Polynomial(528, 7429, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7429, 7430);
  g->Binary(ynn_binary_add, 7430, 7293, 7427);
  g->Binary(ynn_binary_multiply, 528, 7305, 7428);
  g->Binary(ynn_binary_multiply, 7428, 7427, 529);
  g->Binary(ynn_binary_multiply, 526, 529, 530);
  g->Quantize(530, 531, 0.041338592767715454, 0);
  g->Transpose(8907, 5320, {1,0});
  g->Binary(ynn_binary_multiply, 5317, 5319, 5315);
  g->Dot(531, 5320, YNN_INVALID_VALUE_ID, 5314, 1);
  g->DequantizeTensor(5314, YNN_INVALID_VALUE_ID, 5315, 5316);
  g->QuantizeTensor(5316, 8727, 5318, 532);
  g->Dequantize(532, 533, 0.04055152088403702, 0);
  g->Unary(ynn_unary_square, 533, 534);
  g->Reduce(ynn_reduce_sum, 534, 7432, {2}, true);
  g->ShapeProduct(534, 7431, {2});
  g->Binary(ynn_binary_divide, 7432, 7431, 537);
  g->Binary(ynn_binary_add, 537, 8779, 538);
  g->Unary(ynn_unary_rsqrt, 538, 539);
  g->Binary(ynn_binary_multiply, 533, 539, 540);
  g->Binary(ynn_binary_multiply, 540, 8913, 541);
  g->Binary(ynn_binary_add, 541, 516, 542);
}

// Scope: "Layer10 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(429, 543, {0,0,10,0}, {-1,-1,1,-1});
  g->Reshape(543, 544, {1,1,256});
  g->Unary(ynn_unary_square, 544, 545);
  g->Reduce(ynn_reduce_sum, 545, 7434, {2}, true);
  g->ShapeProduct(545, 7433, {2});
  g->Binary(ynn_binary_divide, 7434, 7433, 546);
  g->Binary(ynn_binary_add, 546, 8779, 548);
  g->Unary(ynn_unary_rsqrt, 548, 549);
  g->Binary(ynn_binary_multiply, 544, 549, 550);
  g->Binary(ynn_binary_multiply, 550, 9533, 551);
  g->Binary(ynn_binary_multiply, 9536, 8783, 552);
  g->Binary(ynn_binary_add, 551, 552, 553);
  g->Binary(ynn_binary_multiply, 553, 8777, 554);
  g->Quantize(542, 555, 0.16557246446609497, 0);
  g->Transpose(8910, 5327, {1,0});
  g->Binary(ynn_binary_multiply, 5324, 5326, 5322);
  g->Dot(555, 5327, YNN_INVALID_VALUE_ID, 5321, 1);
  g->DequantizeTensor(5321, YNN_INVALID_VALUE_ID, 5322, 5323);
  g->QuantizeTensor(5323, 8727, 5325, 556);
  g->Dequantize(556, 557, 0.10039370507001877, 0);
  g->Polynomial(557, 7437, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7437, 7438);
  g->Binary(ynn_binary_add, 7438, 7293, 7435);
  g->Binary(ynn_binary_multiply, 557, 7305, 7436);
  g->Binary(ynn_binary_multiply, 7436, 7435, 559);
  g->Binary(ynn_binary_multiply, 559, 554, 560);
  g->Quantize(560, 561, 0.32677164673805237, 0);
  g->Transpose(8911, 5334, {1,0});
  g->Binary(ynn_binary_multiply, 5331, 5333, 5329);
  g->Dot(561, 5334, YNN_INVALID_VALUE_ID, 5328, 1);
  g->DequantizeTensor(5328, YNN_INVALID_VALUE_ID, 5329, 5330);
  g->QuantizeTensor(5330, 8727, 5332, 562);
  g->Dequantize(562, 563, 0.11847137659788132, 0);
  g->Unary(ynn_unary_square, 563, 564);
  g->Reduce(ynn_reduce_sum, 564, 7440, {2}, true);
  g->ShapeProduct(564, 7439, {2});
  g->Binary(ynn_binary_divide, 7440, 7439, 565);
  g->Binary(ynn_binary_add, 565, 8779, 566);
  g->Unary(ynn_unary_rsqrt, 566, 567);
  g->Binary(ynn_binary_multiply, 563, 567, 568);
  g->Binary(ynn_binary_multiply, 568, 8914, 570);
  g->Binary(ynn_binary_add, 542, 570, 571);
  g->Binary(ynn_binary_multiply, 571, 8906, 572);
}

// Scope: "Layer10"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10(Context& ctx) {
  BuildLayer10Attention(ctx);
  BuildLayer10Mlp(ctx);
  BuildLayer10PerLayerEmbedding(ctx);
}

}  // namespace BuildGemma4DecodeSource
