// Generated YNNPACK builder; do not edit.
#include "gemma4_decode_builder.h"

namespace BuildGemma4DecodeSource {

// Scope: "Layer33 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer33AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Binary(ynn_binary_divide, 5471, 7184, 5472);
  g->Unary(ynn_unary_round, 5472, 5473);
  g->Binary(ynn_binary_max, 5473, 7225, 5474);
  g->Binary(ynn_binary_min, 5474, 7340, 5475);
  g->Binary(ynn_binary_multiply, 5475, 7184, 5478);
  g->Convert(8227, 5479);
  g->Binary(ynn_binary_multiply, 5479, 8228, 5480);
  g->Matmul(5478, 5480, 5481, false, true);
  g->Binary(ynn_binary_divide, 5481, 7152, 5482);
  g->Unary(ynn_unary_round, 5482, 5483);
  g->Binary(ynn_binary_max, 5483, 7225, 5484);
  g->Binary(ynn_binary_min, 5484, 7340, 5485);
  g->Binary(ynn_binary_multiply, 5485, 7152, 5486);
  g->SplitDim(5486, 5487, 2, {8,256});
  g->FuseDims(5487, 5490, 1, 2);
  g->SplitDim(5490, 5489, 1, {8,1});
  g->Unary(ynn_unary_square, 5489, 5491);
  g->Reduce(ynn_reduce_sum, 5491, 7014, {3}, true);
  g->ShapeProduct(5491, 7013, {3});
  g->Binary(ynn_binary_divide, 7014, 7013, 5492);
  g->Binary(ynn_binary_add, 5492, 7373, 5493);
  g->Binary(ynn_binary_pow, 5493, 7428, 5494);
  g->Binary(ynn_binary_multiply, 5489, 5494, 5495);
  g->Convert(8226, 5496);
  g->Binary(ynn_binary_multiply, 5495, 5496, 5497);
  g->Slice(5497, 5498, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(5497, 5499, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 5499, 5501);
  g->Concat({5501,5498}, 5502, 3);
  g->Binary(ynn_binary_multiply, 5497, 2044, 5503);
  g->Binary(ynn_binary_multiply, 5502, 3111, 5504);
  g->Binary(ynn_binary_add, 5503, 5504, 5505);
}

// Scope: "Layer33 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer33AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(5505, 1963, 5506, false, true);
  g->Mask(5506, 7588, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 7588, 7018, {-1}, true);
  g->Binary(ynn_binary_subtract, 7588, 7018, 7015);
  g->Unary(ynn_unary_exp, 7015, 7016);
  g->Reduce(ynn_reduce_sum, 7016, 7019, {-1}, true);
  g->Binary(ynn_binary_divide, 6183, 7019, 7017);
  g->Binary(ynn_binary_multiply, 7016, 7017, 5507);
  g->Matmul(5507, 1965, 5508, false, false);
}

// Scope: "Layer33 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer33AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(5508, 5510, 1, 2);
  g->SplitDim(5510, 5509, 1, {1,8});
  g->FuseDims(5509, 5512, 2, 2);
  g->Binary(ynn_binary_divide, 5512, 7464, 5513);
  g->Unary(ynn_unary_round, 5513, 5514);
  g->Binary(ynn_binary_max, 5514, 7225, 5515);
  g->Binary(ynn_binary_min, 5515, 7340, 5516);
  g->Binary(ynn_binary_multiply, 5516, 7464, 5517);
  g->Convert(8224, 5518);
  g->Binary(ynn_binary_multiply, 5518, 8225, 5519);
  g->Matmul(5517, 5519, 5520, false, true);
  g->Binary(ynn_binary_divide, 5520, 7544, 5521);
  g->Unary(ynn_unary_round, 5521, 5523);
  g->Binary(ynn_binary_max, 5523, 7225, 5524);
  g->Binary(ynn_binary_min, 5524, 7340, 5525);
  g->Binary(ynn_binary_multiply, 5525, 7544, 5526);
}

// Scope: "Layer33 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer33Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 5463, 5464);
  g->Reduce(ynn_reduce_sum, 5464, 7012, {2}, true);
  g->ShapeProduct(5464, 7011, {2});
  g->Binary(ynn_binary_divide, 7012, 7011, 5466);
  g->Binary(ynn_binary_add, 5466, 7373, 5467);
  g->Binary(ynn_binary_pow, 5467, 7428, 5468);
  g->Binary(ynn_binary_multiply, 5463, 5468, 5469);
  g->Convert(8208, 5470);
  g->Binary(ynn_binary_multiply, 5469, 5470, 5471);
  BuildLayer33AttentionQueryProjection(ctx);
  BuildLayer33AttentionSdpa(ctx);
  BuildLayer33AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 5526, 5527);
  g->Reduce(ynn_reduce_sum, 5527, 7021, {2}, true);
  g->ShapeProduct(5527, 7020, {2});
  g->Binary(ynn_binary_divide, 7021, 7020, 5528);
  g->Binary(ynn_binary_add, 5528, 7373, 5529);
  g->Binary(ynn_binary_pow, 5529, 7428, 5530);
  g->Binary(ynn_binary_multiply, 5526, 5530, 5531);
  g->Convert(8220, 5532);
  g->Binary(ynn_binary_multiply, 5531, 5532, 5534);
  g->Binary(ynn_binary_add, 5463, 5534, 5535);
}

// Scope: "Layer33 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer33Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 5535, 5536);
  g->Reduce(ynn_reduce_sum, 5536, 7023, {2}, true);
  g->ShapeProduct(5536, 7022, {2});
  g->Binary(ynn_binary_divide, 7023, 7022, 5537);
  g->Binary(ynn_binary_add, 5537, 7373, 5538);
  g->Binary(ynn_binary_pow, 5538, 7428, 5539);
  g->Binary(ynn_binary_multiply, 5535, 5539, 5540);
  g->Convert(8223, 5541);
  g->Binary(ynn_binary_multiply, 5540, 5541, 5542);
  g->Binary(ynn_binary_divide, 5542, 7444, 5543);
  g->Unary(ynn_unary_round, 5543, 5545);
  g->Binary(ynn_binary_max, 5545, 7225, 5546);
  g->Binary(ynn_binary_min, 5546, 7340, 5547);
  g->Binary(ynn_binary_multiply, 5547, 7444, 5548);
  g->Convert(8214, 5549);
  g->Binary(ynn_binary_multiply, 5549, 8215, 5550);
  g->Matmul(5548, 5550, 5551, false, true);
  g->Binary(ynn_binary_divide, 5551, 7256, 5552);
  g->Unary(ynn_unary_round, 5552, 5553);
  g->Binary(ynn_binary_max, 5553, 7225, 5554);
  g->Binary(ynn_binary_min, 5554, 7340, 5556);
  g->Binary(ynn_binary_multiply, 5556, 7256, 5557);
  g->Convert(8212, 5558);
  g->Binary(ynn_binary_multiply, 5558, 8213, 5559);
  g->Matmul(5548, 5559, 5560, false, true);
  g->Binary(ynn_binary_divide, 5560, 7256, 5562);
  g->Unary(ynn_unary_round, 5562, 5563);
  g->Binary(ynn_binary_max, 5563, 7225, 5564);
  g->Binary(ynn_binary_min, 5564, 7340, 5565);
  g->Binary(ynn_binary_multiply, 5565, 7256, 5566);
  g->Polynomial(5566, 7028, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7028, 7029);
  g->Binary(ynn_binary_add, 7029, 6183, 7026);
  g->Binary(ynn_binary_multiply, 5566, 6181, 7027);
  g->Binary(ynn_binary_multiply, 7027, 7026, 5567);
  g->Binary(ynn_binary_multiply, 5557, 5567, 5568);
  g->Binary(ynn_binary_divide, 5568, 7264, 5569);
  g->Unary(ynn_unary_round, 5569, 5570);
  g->Binary(ynn_binary_max, 5570, 7225, 5571);
  g->Binary(ynn_binary_min, 5571, 7340, 5573);
  g->Binary(ynn_binary_multiply, 5573, 7264, 5574);
  g->Convert(8210, 5575);
  g->Binary(ynn_binary_multiply, 5575, 8211, 5576);
  g->Matmul(5574, 5576, 5577, false, true);
  g->Binary(ynn_binary_divide, 5577, 7213, 5578);
  g->Unary(ynn_unary_round, 5578, 5579);
  g->Binary(ynn_binary_max, 5579, 7225, 5580);
  g->Binary(ynn_binary_min, 5580, 7340, 5581);
  g->Binary(ynn_binary_multiply, 5581, 7213, 5582);
  g->Unary(ynn_unary_square, 5582, 5585);
  g->Reduce(ynn_reduce_sum, 5585, 7031, {2}, true);
  g->ShapeProduct(5585, 7030, {2});
  g->Binary(ynn_binary_divide, 7031, 7030, 5586);
  g->Binary(ynn_binary_add, 5586, 7373, 5587);
  g->Binary(ynn_binary_pow, 5587, 7428, 5588);
  g->Binary(ynn_binary_multiply, 5582, 5588, 5589);
  g->Convert(8221, 5590);
  g->Binary(ynn_binary_multiply, 5589, 5590, 5591);
  g->Binary(ynn_binary_add, 5535, 5591, 5592);
}

// Scope: "Layer33 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer33PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1031, 5593, {0,0,33,0}, {-1,-1,1,-1});
  g->Reshape(5593, 5594, {1,1,256});
  g->Binary(ynn_binary_add, 5594, 8436, 5596);
  g->Binary(ynn_binary_multiply, 5596, 7155, 5597);
  g->Binary(ynn_binary_divide, 5592, 7348, 5598);
  g->Unary(ynn_unary_round, 5598, 5599);
  g->Binary(ynn_binary_max, 5599, 7225, 5600);
  g->Binary(ynn_binary_min, 5600, 7340, 5601);
  g->Binary(ynn_binary_multiply, 5601, 7348, 5602);
  g->Convert(8216, 5603);
  g->Binary(ynn_binary_multiply, 5603, 8217, 5604);
  g->Matmul(5602, 5604, 5605, false, true);
  g->Binary(ynn_binary_divide, 5605, 7149, 5607);
  g->Unary(ynn_unary_round, 5607, 5608);
  g->Binary(ynn_binary_max, 5608, 7225, 5609);
  g->Binary(ynn_binary_min, 5609, 7340, 5610);
  g->Binary(ynn_binary_multiply, 5610, 7149, 5611);
  g->Polynomial(5611, 7034, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7034, 7035);
  g->Binary(ynn_binary_add, 7035, 6183, 7032);
  g->Binary(ynn_binary_multiply, 5611, 6181, 7033);
  g->Binary(ynn_binary_multiply, 7033, 7032, 5612);
  g->Binary(ynn_binary_multiply, 5612, 5597, 5613);
  g->Binary(ynn_binary_divide, 5613, 7253, 5614);
  g->Unary(ynn_unary_round, 5614, 5615);
  g->Binary(ynn_binary_max, 5615, 7225, 5616);
  g->Binary(ynn_binary_min, 5616, 7340, 5618);
  g->Binary(ynn_binary_multiply, 5618, 7253, 5619);
  g->Convert(8218, 5620);
  g->Binary(ynn_binary_multiply, 5620, 8219, 5621);
  g->Matmul(5619, 5621, 5622, false, true);
  g->Binary(ynn_binary_divide, 5622, 7400, 5623);
  g->Unary(ynn_unary_round, 5623, 5624);
  g->Binary(ynn_binary_max, 5624, 7225, 5625);
  g->Binary(ynn_binary_min, 5625, 7340, 5626);
  g->Binary(ynn_binary_multiply, 5626, 7400, 5627);
  g->Unary(ynn_unary_square, 5627, 5629);
  g->Reduce(ynn_reduce_sum, 5629, 7037, {2}, true);
  g->ShapeProduct(5629, 7036, {2});
  g->Binary(ynn_binary_divide, 7037, 7036, 5630);
  g->Binary(ynn_binary_add, 5630, 7373, 5631);
  g->Binary(ynn_binary_pow, 5631, 7428, 5632);
  g->Binary(ynn_binary_multiply, 5627, 5632, 5633);
  g->Convert(8222, 5634);
  g->Binary(ynn_binary_multiply, 5633, 5634, 5635);
  g->Binary(ynn_binary_add, 5592, 5635, 5636);
  g->Convert(8209, 5637);
  g->Binary(ynn_binary_multiply, 5636, 5637, 5638);
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
  g->Binary(ynn_binary_divide, 5646, 7285, 5647);
  g->Unary(ynn_unary_round, 5647, 5648);
  g->Binary(ynn_binary_max, 5648, 7225, 5649);
  g->Binary(ynn_binary_min, 5649, 7340, 5651);
  g->Binary(ynn_binary_multiply, 5651, 7285, 5652);
  g->Convert(8248, 5653);
  g->Binary(ynn_binary_multiply, 5653, 8249, 5654);
  g->Matmul(5652, 5654, 5655, false, true);
  g->Binary(ynn_binary_divide, 5655, 7187, 5656);
  g->Unary(ynn_unary_round, 5656, 5657);
  g->Binary(ynn_binary_max, 5657, 7225, 5658);
  g->Binary(ynn_binary_min, 5658, 7340, 5659);
  g->Binary(ynn_binary_multiply, 5659, 7187, 5660);
  g->SplitDim(5660, 5662, 2, {8,512});
  g->FuseDims(5662, 5664, 1, 2);
  g->SplitDim(5664, 5663, 1, {8,1});
  g->Unary(ynn_unary_square, 5663, 5665);
  g->Reduce(ynn_reduce_sum, 5665, 7041, {3}, true);
  g->ShapeProduct(5665, 7040, {3});
  g->Binary(ynn_binary_divide, 7041, 7040, 5666);
  g->Binary(ynn_binary_add, 5666, 7373, 5667);
  g->Binary(ynn_binary_pow, 5667, 7428, 5668);
  g->Binary(ynn_binary_multiply, 5663, 5668, 5669);
  g->Convert(8247, 5670);
  g->Binary(ynn_binary_multiply, 5669, 5670, 5671);
  g->Slice(5671, 5672, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(5671, 5674, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 5674, 5675);
  g->Concat({5675,5672}, 5676, 3);
  g->Binary(ynn_binary_multiply, 5671, 5976, 5677);
  g->Binary(ynn_binary_multiply, 5676, 6075, 5678);
  g->Binary(ynn_binary_add, 5677, 5678, 5679);
}

// Scope: "Layer34 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer34AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(5679, 2179, 5680, false, true);
  g->Mask(5680, 7589, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 7589, 7045, {-1}, true);
  g->Binary(ynn_binary_subtract, 7589, 7045, 7042);
  g->Unary(ynn_unary_exp, 7042, 7043);
  g->Reduce(ynn_reduce_sum, 7043, 7046, {-1}, true);
  g->Binary(ynn_binary_divide, 6183, 7046, 7044);
  g->Binary(ynn_binary_multiply, 7043, 7044, 5681);
  g->Matmul(5681, 2181, 5682, false, false);
}

// Scope: "Layer34 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer34AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(5682, 5685, 1, 2);
  g->SplitDim(5685, 5684, 1, {1,8});
  g->FuseDims(5684, 5686, 2, 2);
  g->Binary(ynn_binary_divide, 5686, 7274, 5687);
  g->Unary(ynn_unary_round, 5687, 5688);
  g->Binary(ynn_binary_max, 5688, 7225, 5689);
  g->Binary(ynn_binary_min, 5689, 7340, 5690);
  g->Binary(ynn_binary_multiply, 5690, 7274, 5691);
  g->Convert(8245, 5692);
  g->Binary(ynn_binary_multiply, 5692, 8246, 5693);
  g->Matmul(5691, 5693, 5694, false, true);
  g->Binary(ynn_binary_divide, 5694, 7448, 5697);
  g->Unary(ynn_unary_round, 5697, 5698);
  g->Binary(ynn_binary_max, 5698, 7225, 5699);
  g->Binary(ynn_binary_min, 5699, 7340, 5700);
  g->Binary(ynn_binary_multiply, 5700, 7448, 5701);
}

// Scope: "Layer34 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer34Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 5638, 5640);
  g->Reduce(ynn_reduce_sum, 5640, 7039, {2}, true);
  g->ShapeProduct(5640, 7038, {2});
  g->Binary(ynn_binary_divide, 7039, 7038, 5641);
  g->Binary(ynn_binary_add, 5641, 7373, 5642);
  g->Binary(ynn_binary_pow, 5642, 7428, 5643);
  g->Binary(ynn_binary_multiply, 5638, 5643, 5644);
  g->Convert(8229, 5645);
  g->Binary(ynn_binary_multiply, 5644, 5645, 5646);
  BuildLayer34AttentionQueryProjection(ctx);
  BuildLayer34AttentionSdpa(ctx);
  BuildLayer34AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 5701, 5702);
  g->Reduce(ynn_reduce_sum, 5702, 7048, {2}, true);
  g->ShapeProduct(5702, 7047, {2});
  g->Binary(ynn_binary_divide, 7048, 7047, 5703);
  g->Binary(ynn_binary_add, 5703, 7373, 5704);
  g->Binary(ynn_binary_pow, 5704, 7428, 5705);
  g->Binary(ynn_binary_multiply, 5701, 5705, 5706);
  g->Convert(8241, 5708);
  g->Binary(ynn_binary_multiply, 5706, 5708, 5709);
  g->Binary(ynn_binary_add, 5638, 5709, 5710);
}

// Scope: "Layer34 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer34Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 5710, 5711);
  g->Reduce(ynn_reduce_sum, 5711, 7050, {2}, true);
  g->ShapeProduct(5711, 7049, {2});
  g->Binary(ynn_binary_divide, 7050, 7049, 5712);
  g->Binary(ynn_binary_add, 5712, 7373, 5713);
  g->Binary(ynn_binary_pow, 5713, 7428, 5714);
  g->Binary(ynn_binary_multiply, 5710, 5714, 5715);
  g->Convert(8244, 5716);
  g->Binary(ynn_binary_multiply, 5715, 5716, 5717);
  g->Binary(ynn_binary_divide, 5717, 7455, 5719);
  g->Unary(ynn_unary_round, 5719, 5720);
  g->Binary(ynn_binary_max, 5720, 7225, 5721);
  g->Binary(ynn_binary_min, 5721, 7340, 5722);
  g->Binary(ynn_binary_multiply, 5722, 7455, 5723);
  g->Convert(8235, 5724);
  g->Binary(ynn_binary_multiply, 5724, 8236, 5725);
  g->Matmul(5723, 5725, 5726, false, true);
  g->Binary(ynn_binary_divide, 5726, 7164, 5727);
  g->Unary(ynn_unary_round, 5727, 5728);
  g->Binary(ynn_binary_max, 5728, 7225, 5730);
  g->Binary(ynn_binary_min, 5730, 7340, 5731);
  g->Binary(ynn_binary_multiply, 5731, 7164, 5732);
  g->Convert(8233, 5733);
  g->Binary(ynn_binary_multiply, 5733, 8234, 5734);
  g->Matmul(5723, 5734, 5736, false, true);
  g->Binary(ynn_binary_divide, 5736, 7164, 5737);
  g->Unary(ynn_unary_round, 5737, 5738);
  g->Binary(ynn_binary_max, 5738, 7225, 5739);
  g->Binary(ynn_binary_min, 5739, 7340, 5740);
  g->Binary(ynn_binary_multiply, 5740, 7164, 5741);
  g->Polynomial(5741, 7053, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7053, 7054);
  g->Binary(ynn_binary_add, 7054, 6183, 7051);
  g->Binary(ynn_binary_multiply, 5741, 6181, 7052);
  g->Binary(ynn_binary_multiply, 7052, 7051, 5742);
  g->Binary(ynn_binary_multiply, 5732, 5742, 5743);
  g->Binary(ynn_binary_divide, 5743, 7514, 5744);
  g->Unary(ynn_unary_round, 5744, 5745);
  g->Binary(ynn_binary_max, 5745, 7225, 5747);
  g->Binary(ynn_binary_min, 5747, 7340, 5748);
  g->Binary(ynn_binary_multiply, 5748, 7514, 5749);
  g->Convert(8231, 5750);
  g->Binary(ynn_binary_multiply, 5750, 8232, 5751);
  g->Matmul(5749, 5751, 5752, false, true);
  g->Binary(ynn_binary_divide, 5752, 7430, 5753);
  g->Unary(ynn_unary_round, 5753, 5754);
  g->Binary(ynn_binary_max, 5754, 7225, 5755);
  g->Binary(ynn_binary_min, 5755, 7340, 5756);
  g->Binary(ynn_binary_multiply, 5756, 7430, 5758);
  g->Unary(ynn_unary_square, 5758, 5759);
  g->Reduce(ynn_reduce_sum, 5759, 7056, {2}, true);
  g->ShapeProduct(5759, 7055, {2});
  g->Binary(ynn_binary_divide, 7056, 7055, 5760);
  g->Binary(ynn_binary_add, 5760, 7373, 5761);
  g->Binary(ynn_binary_pow, 5761, 7428, 5762);
  g->Binary(ynn_binary_multiply, 5758, 5762, 5763);
  g->Convert(8242, 5764);
  g->Binary(ynn_binary_multiply, 5763, 5764, 5765);
  g->Binary(ynn_binary_add, 5710, 5765, 5766);
}

// Scope: "Layer34 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer34PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1031, 5767, {0,0,34,0}, {-1,-1,1,-1});
  g->Reshape(5767, 5769, {1,1,256});
  g->Binary(ynn_binary_add, 5769, 8437, 5770);
  g->Binary(ynn_binary_multiply, 5770, 7155, 5771);
  g->Binary(ynn_binary_divide, 5766, 7343, 5772);
  g->Unary(ynn_unary_round, 5772, 5773);
  g->Binary(ynn_binary_max, 5773, 7225, 5774);
  g->Binary(ynn_binary_min, 5774, 7340, 5775);
  g->Binary(ynn_binary_multiply, 5775, 7343, 5776);
  g->Convert(8237, 5777);
  g->Binary(ynn_binary_multiply, 5777, 8238, 5778);
  g->Matmul(5776, 5778, 5780, false, true);
  g->Binary(ynn_binary_divide, 5780, 7222, 5781);
  g->Unary(ynn_unary_round, 5781, 5782);
  g->Binary(ynn_binary_max, 5782, 7225, 5783);
  g->Binary(ynn_binary_min, 5783, 7340, 5784);
  g->Binary(ynn_binary_multiply, 5784, 7222, 5785);
  g->Polynomial(5785, 7059, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7059, 7060);
  g->Binary(ynn_binary_add, 7060, 6183, 7057);
  g->Binary(ynn_binary_multiply, 5785, 6181, 7058);
  g->Binary(ynn_binary_multiply, 7058, 7057, 5786);
  g->Binary(ynn_binary_multiply, 5786, 5771, 5787);
  g->Binary(ynn_binary_divide, 5787, 7277, 5788);
  g->Unary(ynn_unary_round, 5788, 5789);
  g->Binary(ynn_binary_max, 5789, 7225, 5791);
  g->Binary(ynn_binary_min, 5791, 7340, 5792);
  g->Binary(ynn_binary_multiply, 5792, 7277, 5793);
  g->Convert(8239, 5794);
  g->Binary(ynn_binary_multiply, 5794, 8240, 5795);
  g->Matmul(5793, 5795, 5796, false, true);
  g->Binary(ynn_binary_divide, 5796, 7314, 5797);
  g->Unary(ynn_unary_round, 5797, 5798);
  g->Binary(ynn_binary_max, 5798, 7225, 5799);
  g->Binary(ynn_binary_min, 5799, 7340, 5800);
  g->Binary(ynn_binary_multiply, 5800, 7314, 5803);
  g->Unary(ynn_unary_square, 5803, 5804);
  g->Reduce(ynn_reduce_sum, 5804, 7066, {2}, true);
  g->ShapeProduct(5804, 7065, {2});
  g->Binary(ynn_binary_divide, 7066, 7065, 5805);
  g->Binary(ynn_binary_add, 5805, 7373, 5806);
  g->Binary(ynn_binary_pow, 5806, 7428, 5807);
  g->Binary(ynn_binary_multiply, 5803, 5807, 5808);
  g->Convert(8243, 5809);
  g->Binary(ynn_binary_multiply, 5808, 5809, 5810);
  g->Binary(ynn_binary_add, 5766, 5810, 5811);
  g->Convert(8230, 5812);
  g->Binary(ynn_binary_multiply, 5811, 5812, 5814);
}

// Scope: "Layer34"
LAB_YNN_BUILDER_NOINLINE void BuildLayer34(Context& ctx) {
  BuildLayer34Attention(ctx);
  BuildLayer34Mlp(ctx);
  BuildLayer34PerLayerEmbedding(ctx);
}

// Scope: "FinalNormAndHead"
LAB_YNN_BUILDER_NOINLINE void BuildFinalNormAndHead(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 5814, 5815);
  g->Reduce(ynn_reduce_sum, 5815, 7068, {2}, true);
  g->ShapeProduct(5815, 7067, {2});
  g->Binary(ynn_binary_divide, 7068, 7067, 5816);
  g->Binary(ynn_binary_add, 5816, 7373, 5817);
  g->Binary(ynn_binary_pow, 5817, 7428, 5818);
  g->Binary(ynn_binary_multiply, 5814, 5818, 5819);
  g->Convert(8406, 5820);
  g->Binary(ynn_binary_multiply, 5819, 5820, 5821);
  g->Convert(7558, 5822);
  g->Binary(ynn_binary_multiply, 5822, 7559, 5823);
  g->Matmul(5821, 5823, 5825, false, true);
  g->Binary(ynn_binary_divide, 5825, 7207, 5826);
  g->Unary(ynn_unary_tanh, 5826, 5827);
  g->Binary(ynn_binary_multiply, 5827, 7207, 5828);
  g->Convert(5828, 7560);
  g->ResultShape(7560, {slinky::expr(int64_t{1}),slinky::expr(int64_t{1}),slinky::expr(int64_t{262144})});
}

}  // namespace BuildGemma4DecodeSource
