// Generated YNNPACK builder; do not edit.
#include "gemma4_decode_builder.h"

namespace BuildGemma4DecodeSource {

// Scope: "Layer33 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer33AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Binary(ynn_binary_divide, 5410, 7114, 5411);
  g->Unary(ynn_unary_round, 5411, 5412);
  g->Binary(ynn_binary_max, 5412, 7155, 5413);
  g->Binary(ynn_binary_min, 5413, 7270, 5414);
  g->Binary(ynn_binary_multiply, 5414, 7114, 5417);
  g->Convert(8157, 5418);
  g->Binary(ynn_binary_multiply, 5418, 8158, 5419);
  g->Matmul(5417, 5419, 5420, false, true);
  g->Binary(ynn_binary_divide, 5420, 7082, 5421);
  g->Unary(ynn_unary_round, 5421, 5422);
  g->Binary(ynn_binary_max, 5422, 7155, 5423);
  g->Binary(ynn_binary_min, 5423, 7270, 5424);
  g->Binary(ynn_binary_multiply, 5424, 7082, 5425);
  g->SplitDim(5425, 5426, 2, {8,256});
  g->Transpose(5426, 5428, {0,2,1,3});
  g->Unary(ynn_unary_square, 5428, 5429);
  g->Reduce(ynn_reduce_sum, 5429, 6944, {3}, true);
  g->ShapeProduct(5429, 6943, {3});
  g->Binary(ynn_binary_divide, 6944, 6943, 5430);
  g->Binary(ynn_binary_add, 5430, 7303, 5431);
  g->Binary(ynn_binary_pow, 5431, 7358, 5432);
  g->Binary(ynn_binary_multiply, 5428, 5432, 5433);
  g->Convert(8156, 5434);
  g->Binary(ynn_binary_multiply, 5433, 5434, 5435);
  g->Slice(5435, 5436, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(5435, 5437, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 5437, 5439);
  g->Concat({5439,5436}, 5440, 3);
  g->Binary(ynn_binary_multiply, 5435, 2025, 5441);
  g->Binary(ynn_binary_multiply, 5440, 3078, 5442);
  g->Binary(ynn_binary_add, 5441, 5442, 5443);
}

// Scope: "Layer33 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer33AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(5443, 1946, 5444, false, true);
  g->Mask(5444, 7518, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 7518, 6948, {-1}, true);
  g->Binary(ynn_binary_subtract, 7518, 6948, 6945);
  g->Unary(ynn_unary_exp, 6945, 6946);
  g->Reduce(ynn_reduce_sum, 6946, 6949, {-1}, true);
  g->Binary(ynn_binary_divide, 6113, 6949, 6947);
  g->Binary(ynn_binary_multiply, 6946, 6947, 5445);
  g->Matmul(5445, 1948, 5446, false, false);
}

// Scope: "Layer33 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer33AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(5446, 5447, {0,2,1,3});
  g->FuseDims(5447, 5449, 2, 2);
  g->Binary(ynn_binary_divide, 5449, 7394, 5450);
  g->Unary(ynn_unary_round, 5450, 5451);
  g->Binary(ynn_binary_max, 5451, 7155, 5452);
  g->Binary(ynn_binary_min, 5452, 7270, 5453);
  g->Binary(ynn_binary_multiply, 5453, 7394, 5454);
  g->Convert(8154, 5455);
  g->Binary(ynn_binary_multiply, 5455, 8155, 5456);
  g->Matmul(5454, 5456, 5457, false, true);
  g->Binary(ynn_binary_divide, 5457, 7474, 5458);
  g->Unary(ynn_unary_round, 5458, 5460);
  g->Binary(ynn_binary_max, 5460, 7155, 5461);
  g->Binary(ynn_binary_min, 5461, 7270, 5462);
  g->Binary(ynn_binary_multiply, 5462, 7474, 5463);
}

// Scope: "Layer33 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer33Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 5402, 5403);
  g->Reduce(ynn_reduce_sum, 5403, 6942, {2}, true);
  g->ShapeProduct(5403, 6941, {2});
  g->Binary(ynn_binary_divide, 6942, 6941, 5405);
  g->Binary(ynn_binary_add, 5405, 7303, 5406);
  g->Binary(ynn_binary_pow, 5406, 7358, 5407);
  g->Binary(ynn_binary_multiply, 5402, 5407, 5408);
  g->Convert(8138, 5409);
  g->Binary(ynn_binary_multiply, 5408, 5409, 5410);
  BuildLayer33AttentionQueryProjection(ctx);
  BuildLayer33AttentionSdpa(ctx);
  BuildLayer33AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 5463, 5464);
  g->Reduce(ynn_reduce_sum, 5464, 6951, {2}, true);
  g->ShapeProduct(5464, 6950, {2});
  g->Binary(ynn_binary_divide, 6951, 6950, 5465);
  g->Binary(ynn_binary_add, 5465, 7303, 5466);
  g->Binary(ynn_binary_pow, 5466, 7358, 5467);
  g->Binary(ynn_binary_multiply, 5463, 5467, 5468);
  g->Convert(8150, 5469);
  g->Binary(ynn_binary_multiply, 5468, 5469, 5471);
  g->Binary(ynn_binary_add, 5402, 5471, 5472);
}

// Scope: "Layer33 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer33Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 5472, 5473);
  g->Reduce(ynn_reduce_sum, 5473, 6953, {2}, true);
  g->ShapeProduct(5473, 6952, {2});
  g->Binary(ynn_binary_divide, 6953, 6952, 5474);
  g->Binary(ynn_binary_add, 5474, 7303, 5475);
  g->Binary(ynn_binary_pow, 5475, 7358, 5476);
  g->Binary(ynn_binary_multiply, 5472, 5476, 5477);
  g->Convert(8153, 5478);
  g->Binary(ynn_binary_multiply, 5477, 5478, 5479);
  g->Binary(ynn_binary_divide, 5479, 7374, 5480);
  g->Unary(ynn_unary_round, 5480, 5482);
  g->Binary(ynn_binary_max, 5482, 7155, 5483);
  g->Binary(ynn_binary_min, 5483, 7270, 5484);
  g->Binary(ynn_binary_multiply, 5484, 7374, 5485);
  g->Convert(8144, 5486);
  g->Binary(ynn_binary_multiply, 5486, 8145, 5487);
  g->Matmul(5485, 5487, 5488, false, true);
  g->Binary(ynn_binary_divide, 5488, 7186, 5489);
  g->Unary(ynn_unary_round, 5489, 5490);
  g->Binary(ynn_binary_max, 5490, 7155, 5491);
  g->Binary(ynn_binary_min, 5491, 7270, 5493);
  g->Binary(ynn_binary_multiply, 5493, 7186, 5494);
  g->Convert(8142, 5495);
  g->Binary(ynn_binary_multiply, 5495, 8143, 5496);
  g->Matmul(5485, 5496, 5497, false, true);
  g->Binary(ynn_binary_divide, 5497, 7186, 5499);
  g->Unary(ynn_unary_round, 5499, 5500);
  g->Binary(ynn_binary_max, 5500, 7155, 5501);
  g->Binary(ynn_binary_min, 5501, 7270, 5502);
  g->Binary(ynn_binary_multiply, 5502, 7186, 5503);
  g->Polynomial(5503, 6958, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6958, 6959);
  g->Binary(ynn_binary_add, 6959, 6113, 6956);
  g->Binary(ynn_binary_multiply, 5503, 6111, 6957);
  g->Binary(ynn_binary_multiply, 6957, 6956, 5504);
  g->Binary(ynn_binary_multiply, 5494, 5504, 5505);
  g->Binary(ynn_binary_divide, 5505, 7194, 5506);
  g->Unary(ynn_unary_round, 5506, 5507);
  g->Binary(ynn_binary_max, 5507, 7155, 5508);
  g->Binary(ynn_binary_min, 5508, 7270, 5510);
  g->Binary(ynn_binary_multiply, 5510, 7194, 5511);
  g->Convert(8140, 5512);
  g->Binary(ynn_binary_multiply, 5512, 8141, 5513);
  g->Matmul(5511, 5513, 5514, false, true);
  g->Binary(ynn_binary_divide, 5514, 7143, 5515);
  g->Unary(ynn_unary_round, 5515, 5516);
  g->Binary(ynn_binary_max, 5516, 7155, 5517);
  g->Binary(ynn_binary_min, 5517, 7270, 5518);
  g->Binary(ynn_binary_multiply, 5518, 7143, 5519);
  g->Unary(ynn_unary_square, 5519, 5522);
  g->Reduce(ynn_reduce_sum, 5522, 6961, {2}, true);
  g->ShapeProduct(5522, 6960, {2});
  g->Binary(ynn_binary_divide, 6961, 6960, 5523);
  g->Binary(ynn_binary_add, 5523, 7303, 5524);
  g->Binary(ynn_binary_pow, 5524, 7358, 5525);
  g->Binary(ynn_binary_multiply, 5519, 5525, 5526);
  g->Convert(8151, 5527);
  g->Binary(ynn_binary_multiply, 5526, 5527, 5528);
  g->Binary(ynn_binary_add, 5472, 5528, 5529);
}

// Scope: "Layer33 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer33PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1022, 5530, {0,0,33,0}, {-1,-1,1,-1});
  g->Reshape(5530, 5531, {1,1,256});
  g->Binary(ynn_binary_add, 5531, 8366, 5533);
  g->Binary(ynn_binary_multiply, 5533, 7085, 5534);
  g->Binary(ynn_binary_divide, 5529, 7278, 5535);
  g->Unary(ynn_unary_round, 5535, 5536);
  g->Binary(ynn_binary_max, 5536, 7155, 5537);
  g->Binary(ynn_binary_min, 5537, 7270, 5538);
  g->Binary(ynn_binary_multiply, 5538, 7278, 5539);
  g->Convert(8146, 5540);
  g->Binary(ynn_binary_multiply, 5540, 8147, 5541);
  g->Matmul(5539, 5541, 5542, false, true);
  g->Binary(ynn_binary_divide, 5542, 7079, 5544);
  g->Unary(ynn_unary_round, 5544, 5545);
  g->Binary(ynn_binary_max, 5545, 7155, 5546);
  g->Binary(ynn_binary_min, 5546, 7270, 5547);
  g->Binary(ynn_binary_multiply, 5547, 7079, 5548);
  g->Polynomial(5548, 6964, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6964, 6965);
  g->Binary(ynn_binary_add, 6965, 6113, 6962);
  g->Binary(ynn_binary_multiply, 5548, 6111, 6963);
  g->Binary(ynn_binary_multiply, 6963, 6962, 5549);
  g->Binary(ynn_binary_multiply, 5549, 5534, 5550);
  g->Binary(ynn_binary_divide, 5550, 7183, 5551);
  g->Unary(ynn_unary_round, 5551, 5552);
  g->Binary(ynn_binary_max, 5552, 7155, 5553);
  g->Binary(ynn_binary_min, 5553, 7270, 5555);
  g->Binary(ynn_binary_multiply, 5555, 7183, 5556);
  g->Convert(8148, 5557);
  g->Binary(ynn_binary_multiply, 5557, 8149, 5558);
  g->Matmul(5556, 5558, 5559, false, true);
  g->Binary(ynn_binary_divide, 5559, 7330, 5560);
  g->Unary(ynn_unary_round, 5560, 5561);
  g->Binary(ynn_binary_max, 5561, 7155, 5562);
  g->Binary(ynn_binary_min, 5562, 7270, 5563);
  g->Binary(ynn_binary_multiply, 5563, 7330, 5564);
  g->Unary(ynn_unary_square, 5564, 5566);
  g->Reduce(ynn_reduce_sum, 5566, 6967, {2}, true);
  g->ShapeProduct(5566, 6966, {2});
  g->Binary(ynn_binary_divide, 6967, 6966, 5567);
  g->Binary(ynn_binary_add, 5567, 7303, 5568);
  g->Binary(ynn_binary_pow, 5568, 7358, 5569);
  g->Binary(ynn_binary_multiply, 5564, 5569, 5570);
  g->Convert(8152, 5571);
  g->Binary(ynn_binary_multiply, 5570, 5571, 5572);
  g->Binary(ynn_binary_add, 5529, 5572, 5573);
  g->Convert(8139, 5574);
  g->Binary(ynn_binary_multiply, 5573, 5574, 5575);
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
  g->Binary(ynn_binary_divide, 5583, 7215, 5584);
  g->Unary(ynn_unary_round, 5584, 5585);
  g->Binary(ynn_binary_max, 5585, 7155, 5586);
  g->Binary(ynn_binary_min, 5586, 7270, 5588);
  g->Binary(ynn_binary_multiply, 5588, 7215, 5589);
  g->Convert(8178, 5590);
  g->Binary(ynn_binary_multiply, 5590, 8179, 5591);
  g->Matmul(5589, 5591, 5592, false, true);
  g->Binary(ynn_binary_divide, 5592, 7117, 5593);
  g->Unary(ynn_unary_round, 5593, 5594);
  g->Binary(ynn_binary_max, 5594, 7155, 5595);
  g->Binary(ynn_binary_min, 5595, 7270, 5596);
  g->Binary(ynn_binary_multiply, 5596, 7117, 5597);
  g->SplitDim(5597, 5599, 2, {8,512});
  g->Transpose(5599, 5600, {0,2,1,3});
  g->Unary(ynn_unary_square, 5600, 5601);
  g->Reduce(ynn_reduce_sum, 5601, 6971, {3}, true);
  g->ShapeProduct(5601, 6970, {3});
  g->Binary(ynn_binary_divide, 6971, 6970, 5602);
  g->Binary(ynn_binary_add, 5602, 7303, 5603);
  g->Binary(ynn_binary_pow, 5603, 7358, 5604);
  g->Binary(ynn_binary_multiply, 5600, 5604, 5605);
  g->Convert(8177, 5606);
  g->Binary(ynn_binary_multiply, 5605, 5606, 5607);
  g->Slice(5607, 5608, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(5607, 5610, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 5610, 5611);
  g->Concat({5611,5608}, 5612, 3);
  g->Binary(ynn_binary_multiply, 5607, 5909, 5613);
  g->Binary(ynn_binary_multiply, 5612, 6008, 5614);
  g->Binary(ynn_binary_add, 5613, 5614, 5615);
}

// Scope: "Layer34 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer34AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(5615, 2160, 5616, false, true);
  g->Mask(5616, 7519, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 7519, 6975, {-1}, true);
  g->Binary(ynn_binary_subtract, 7519, 6975, 6972);
  g->Unary(ynn_unary_exp, 6972, 6973);
  g->Reduce(ynn_reduce_sum, 6973, 6976, {-1}, true);
  g->Binary(ynn_binary_divide, 6113, 6976, 6974);
  g->Binary(ynn_binary_multiply, 6973, 6974, 5617);
  g->Matmul(5617, 2162, 5618, false, false);
}

// Scope: "Layer34 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer34AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(5618, 5620, {0,2,1,3});
  g->FuseDims(5620, 5621, 2, 2);
  g->Binary(ynn_binary_divide, 5621, 7204, 5622);
  g->Unary(ynn_unary_round, 5622, 5623);
  g->Binary(ynn_binary_max, 5623, 7155, 5624);
  g->Binary(ynn_binary_min, 5624, 7270, 5625);
  g->Binary(ynn_binary_multiply, 5625, 7204, 5626);
  g->Convert(8175, 5627);
  g->Binary(ynn_binary_multiply, 5627, 8176, 5628);
  g->Matmul(5626, 5628, 5629, false, true);
  g->Binary(ynn_binary_divide, 5629, 7378, 5632);
  g->Unary(ynn_unary_round, 5632, 5633);
  g->Binary(ynn_binary_max, 5633, 7155, 5634);
  g->Binary(ynn_binary_min, 5634, 7270, 5635);
  g->Binary(ynn_binary_multiply, 5635, 7378, 5636);
}

// Scope: "Layer34 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer34Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 5575, 5577);
  g->Reduce(ynn_reduce_sum, 5577, 6969, {2}, true);
  g->ShapeProduct(5577, 6968, {2});
  g->Binary(ynn_binary_divide, 6969, 6968, 5578);
  g->Binary(ynn_binary_add, 5578, 7303, 5579);
  g->Binary(ynn_binary_pow, 5579, 7358, 5580);
  g->Binary(ynn_binary_multiply, 5575, 5580, 5581);
  g->Convert(8159, 5582);
  g->Binary(ynn_binary_multiply, 5581, 5582, 5583);
  BuildLayer34AttentionQueryProjection(ctx);
  BuildLayer34AttentionSdpa(ctx);
  BuildLayer34AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 5636, 5637);
  g->Reduce(ynn_reduce_sum, 5637, 6978, {2}, true);
  g->ShapeProduct(5637, 6977, {2});
  g->Binary(ynn_binary_divide, 6978, 6977, 5638);
  g->Binary(ynn_binary_add, 5638, 7303, 5639);
  g->Binary(ynn_binary_pow, 5639, 7358, 5640);
  g->Binary(ynn_binary_multiply, 5636, 5640, 5641);
  g->Convert(8171, 5643);
  g->Binary(ynn_binary_multiply, 5641, 5643, 5644);
  g->Binary(ynn_binary_add, 5575, 5644, 5645);
}

// Scope: "Layer34 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer34Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 5645, 5646);
  g->Reduce(ynn_reduce_sum, 5646, 6980, {2}, true);
  g->ShapeProduct(5646, 6979, {2});
  g->Binary(ynn_binary_divide, 6980, 6979, 5647);
  g->Binary(ynn_binary_add, 5647, 7303, 5648);
  g->Binary(ynn_binary_pow, 5648, 7358, 5649);
  g->Binary(ynn_binary_multiply, 5645, 5649, 5650);
  g->Convert(8174, 5651);
  g->Binary(ynn_binary_multiply, 5650, 5651, 5652);
  g->Binary(ynn_binary_divide, 5652, 7385, 5654);
  g->Unary(ynn_unary_round, 5654, 5655);
  g->Binary(ynn_binary_max, 5655, 7155, 5656);
  g->Binary(ynn_binary_min, 5656, 7270, 5657);
  g->Binary(ynn_binary_multiply, 5657, 7385, 5658);
  g->Convert(8165, 5659);
  g->Binary(ynn_binary_multiply, 5659, 8166, 5660);
  g->Matmul(5658, 5660, 5661, false, true);
  g->Binary(ynn_binary_divide, 5661, 7094, 5662);
  g->Unary(ynn_unary_round, 5662, 5663);
  g->Binary(ynn_binary_max, 5663, 7155, 5665);
  g->Binary(ynn_binary_min, 5665, 7270, 5666);
  g->Binary(ynn_binary_multiply, 5666, 7094, 5667);
  g->Convert(8163, 5668);
  g->Binary(ynn_binary_multiply, 5668, 8164, 5669);
  g->Matmul(5658, 5669, 5671, false, true);
  g->Binary(ynn_binary_divide, 5671, 7094, 5672);
  g->Unary(ynn_unary_round, 5672, 5673);
  g->Binary(ynn_binary_max, 5673, 7155, 5674);
  g->Binary(ynn_binary_min, 5674, 7270, 5675);
  g->Binary(ynn_binary_multiply, 5675, 7094, 5676);
  g->Polynomial(5676, 6983, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6983, 6984);
  g->Binary(ynn_binary_add, 6984, 6113, 6981);
  g->Binary(ynn_binary_multiply, 5676, 6111, 6982);
  g->Binary(ynn_binary_multiply, 6982, 6981, 5677);
  g->Binary(ynn_binary_multiply, 5667, 5677, 5678);
  g->Binary(ynn_binary_divide, 5678, 7444, 5679);
  g->Unary(ynn_unary_round, 5679, 5680);
  g->Binary(ynn_binary_max, 5680, 7155, 5682);
  g->Binary(ynn_binary_min, 5682, 7270, 5683);
  g->Binary(ynn_binary_multiply, 5683, 7444, 5684);
  g->Convert(8161, 5685);
  g->Binary(ynn_binary_multiply, 5685, 8162, 5686);
  g->Matmul(5684, 5686, 5687, false, true);
  g->Binary(ynn_binary_divide, 5687, 7360, 5688);
  g->Unary(ynn_unary_round, 5688, 5689);
  g->Binary(ynn_binary_max, 5689, 7155, 5690);
  g->Binary(ynn_binary_min, 5690, 7270, 5691);
  g->Binary(ynn_binary_multiply, 5691, 7360, 5693);
  g->Unary(ynn_unary_square, 5693, 5694);
  g->Reduce(ynn_reduce_sum, 5694, 6986, {2}, true);
  g->ShapeProduct(5694, 6985, {2});
  g->Binary(ynn_binary_divide, 6986, 6985, 5695);
  g->Binary(ynn_binary_add, 5695, 7303, 5696);
  g->Binary(ynn_binary_pow, 5696, 7358, 5697);
  g->Binary(ynn_binary_multiply, 5693, 5697, 5698);
  g->Convert(8172, 5699);
  g->Binary(ynn_binary_multiply, 5698, 5699, 5700);
  g->Binary(ynn_binary_add, 5645, 5700, 5701);
}

// Scope: "Layer34 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer34PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1022, 5702, {0,0,34,0}, {-1,-1,1,-1});
  g->Reshape(5702, 5704, {1,1,256});
  g->Binary(ynn_binary_add, 5704, 8367, 5705);
  g->Binary(ynn_binary_multiply, 5705, 7085, 5706);
  g->Binary(ynn_binary_divide, 5701, 7273, 5707);
  g->Unary(ynn_unary_round, 5707, 5708);
  g->Binary(ynn_binary_max, 5708, 7155, 5709);
  g->Binary(ynn_binary_min, 5709, 7270, 5710);
  g->Binary(ynn_binary_multiply, 5710, 7273, 5711);
  g->Convert(8167, 5712);
  g->Binary(ynn_binary_multiply, 5712, 8168, 5713);
  g->Matmul(5711, 5713, 5715, false, true);
  g->Binary(ynn_binary_divide, 5715, 7152, 5716);
  g->Unary(ynn_unary_round, 5716, 5717);
  g->Binary(ynn_binary_max, 5717, 7155, 5718);
  g->Binary(ynn_binary_min, 5718, 7270, 5719);
  g->Binary(ynn_binary_multiply, 5719, 7152, 5720);
  g->Polynomial(5720, 6989, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6989, 6990);
  g->Binary(ynn_binary_add, 6990, 6113, 6987);
  g->Binary(ynn_binary_multiply, 5720, 6111, 6988);
  g->Binary(ynn_binary_multiply, 6988, 6987, 5721);
  g->Binary(ynn_binary_multiply, 5721, 5706, 5722);
  g->Binary(ynn_binary_divide, 5722, 7207, 5723);
  g->Unary(ynn_unary_round, 5723, 5724);
  g->Binary(ynn_binary_max, 5724, 7155, 5726);
  g->Binary(ynn_binary_min, 5726, 7270, 5727);
  g->Binary(ynn_binary_multiply, 5727, 7207, 5728);
  g->Convert(8169, 5729);
  g->Binary(ynn_binary_multiply, 5729, 8170, 5730);
  g->Matmul(5728, 5730, 5731, false, true);
  g->Binary(ynn_binary_divide, 5731, 7244, 5732);
  g->Unary(ynn_unary_round, 5732, 5733);
  g->Binary(ynn_binary_max, 5733, 7155, 5734);
  g->Binary(ynn_binary_min, 5734, 7270, 5735);
  g->Binary(ynn_binary_multiply, 5735, 7244, 5738);
  g->Unary(ynn_unary_square, 5738, 5739);
  g->Reduce(ynn_reduce_sum, 5739, 6996, {2}, true);
  g->ShapeProduct(5739, 6995, {2});
  g->Binary(ynn_binary_divide, 6996, 6995, 5740);
  g->Binary(ynn_binary_add, 5740, 7303, 5741);
  g->Binary(ynn_binary_pow, 5741, 7358, 5742);
  g->Binary(ynn_binary_multiply, 5738, 5742, 5743);
  g->Convert(8173, 5744);
  g->Binary(ynn_binary_multiply, 5743, 5744, 5745);
  g->Binary(ynn_binary_add, 5701, 5745, 5746);
  g->Convert(8160, 5747);
  g->Binary(ynn_binary_multiply, 5746, 5747, 5749);
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
  g->Unary(ynn_unary_square, 5749, 5750);
  g->Reduce(ynn_reduce_sum, 5750, 6998, {2}, true);
  g->ShapeProduct(5750, 6997, {2});
  g->Binary(ynn_binary_divide, 6998, 6997, 5751);
  g->Binary(ynn_binary_add, 5751, 7303, 5752);
  g->Binary(ynn_binary_pow, 5752, 7358, 5753);
  g->Binary(ynn_binary_multiply, 5749, 5753, 5754);
  g->Convert(8336, 5755);
  g->Binary(ynn_binary_multiply, 5754, 5755, 5756);
  g->Convert(7488, 5757);
  g->Binary(ynn_binary_multiply, 5757, 7489, 5758);
  g->Matmul(5756, 5758, 5760, false, true);
  g->Binary(ynn_binary_divide, 5760, 7137, 5761);
  g->Unary(ynn_unary_tanh, 5761, 5762);
  g->Binary(ynn_binary_multiply, 5762, 7137, 5763);
  g->Convert(5763, 7490);
  g->ResultShape(7490, {slinky::expr(int64_t{1}),slinky::expr(int64_t{1}),slinky::expr(int64_t{262144})});
}

}  // namespace BuildGemma4DecodeSource
