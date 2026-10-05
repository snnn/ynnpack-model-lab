// Generated YNNPACK builder; do not edit.
#include "gemma4_decode_builder.h"

namespace BuildGemma4DecodeSource {

// Scope: "Layer18 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(1565, 1566, 0.21988293528556824, 0);
  g->Transpose(8921, 5656, {1,0});
  g->Binary(ynn_binary_multiply, 5654, 5655, 5652);
  g->Dot(1566, 5656, YNN_INVALID_VALUE_ID, 5651, 1);
  g->DequantizeTensor(5651, YNN_INVALID_VALUE_ID, 5652, 5653);
  g->QuantizeTensor(5653, 8595, 5272, 1567);
  g->Dequantize(1567, 1568, 0.2027559131383896, 0);
  g->SplitDim(1568, 1569, 2, {2,256});
  g->Transpose(1569, 1570, {0,2,1,3});
  g->Unary(ynn_unary_square, 1570, 1572);
  g->Reduce(ynn_reduce_sum, 1572, 7588, {3}, true);
  g->ShapeProduct(1572, 7587, {3});
  g->Binary(ynn_binary_divide, 7588, 7587, 1573);
  g->Binary(ynn_binary_add, 1573, 8647, 1574);
  g->Unary(ynn_unary_rsqrt, 1574, 1575);
  g->Binary(ynn_binary_multiply, 1570, 1575, 1576);
  g->Binary(ynn_binary_multiply, 1576, 8920, 1577);
  g->Slice(1577, 1578, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1577, 1579, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1579, 1580);
  g->Concat({1580,1578}, 1581, 3);
  g->Binary(ynn_binary_multiply, 1577, 3141, 1583);
  g->Binary(ynn_binary_multiply, 1581, 4217, 1584);
  g->Binary(ynn_binary_add, 1583, 1584, 1585);
  g->Transpose(8925, 5661, {1,0});
  g->Binary(ynn_binary_multiply, 5654, 5660, 5658);
  g->Dot(1566, 5661, YNN_INVALID_VALUE_ID, 5657, 1);
  g->DequantizeTensor(5657, YNN_INVALID_VALUE_ID, 5658, 5659);
  g->QuantizeTensor(5659, 8595, 5272, 1586);
  g->Dequantize(1586, 1587, 0.2027559131383896, 0);
  g->SplitDim(1587, 1588, 2, {2,256});
  g->Transpose(1588, 1589, {0,2,1,3});
  g->Unary(ynn_unary_square, 1589, 1590);
  g->Reduce(ynn_reduce_sum, 1590, 7594, {3}, true);
  g->ShapeProduct(1590, 7593, {3});
  g->Binary(ynn_binary_divide, 7594, 7593, 1591);
  g->Binary(ynn_binary_add, 1591, 8647, 1593);
  g->Unary(ynn_unary_rsqrt, 1593, 1594);
  g->Binary(ynn_binary_multiply, 1589, 1594, 1595);
}

// Scope: "Layer18 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(1585, 1596, 0.00573749840259552, 0);
  g->Append(8606, 1596, 9455, 2, s2, slinky::expr(int64_t{1}));
  g->View(9455, 9503, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(1595, 1597, 0.047244105488061905, 0);
  g->Append(8630, 1597, 9479, 2, s2, slinky::expr(int64_t{1}));
  g->View(9479, 9527, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer18 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(8924, 5667, {1,0});
  g->Binary(ynn_binary_multiply, 5654, 5666, 5663);
  g->Dot(1566, 5667, YNN_INVALID_VALUE_ID, 5662, 1);
  g->DequantizeTensor(5662, YNN_INVALID_VALUE_ID, 5663, 5664);
  g->QuantizeTensor(5664, 8595, 5665, 1599);
  g->Dequantize(1599, 1600, 0.22539371252059937, 0);
  g->SplitDim(1600, 1601, 2, {8,256});
  g->Transpose(1601, 1602, {0,2,1,3});
  g->Unary(ynn_unary_square, 1602, 1603);
  g->Reduce(ynn_reduce_sum, 1603, 7596, {3}, true);
  g->ShapeProduct(1603, 7595, {3});
  g->Binary(ynn_binary_divide, 7596, 7595, 1604);
  g->Binary(ynn_binary_add, 1604, 8647, 1605);
  g->Unary(ynn_unary_rsqrt, 1605, 1606);
  g->Binary(ynn_binary_multiply, 1602, 1606, 1607);
  g->Binary(ynn_binary_multiply, 1607, 8923, 1608);
  g->Slice(1608, 1610, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1608, 1611, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1611, 1612);
  g->Concat({1612,1610}, 1613, 3);
  g->Binary(ynn_binary_multiply, 1608, 3141, 1614);
  g->Binary(ynn_binary_multiply, 1613, 4217, 1615);
  g->Binary(ynn_binary_add, 1614, 1615, 1616);
}

// Scope: "Layer18 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9503, 1617, 0.00573749840259552, 0);
  g->Dequantize(9527, 1618, 0.047244105488061905, 0);
  g->Slice(1616, 1619, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(1617, 1621, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(1618, 1622, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(1619, 1621, 1623, false, true);
  g->Mask(1623, 8672, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8672, 7600, {-1}, true);
  g->Binary(ynn_binary_subtract, 8672, 7600, 7597);
  g->Unary(ynn_unary_exp, 7597, 7598);
  g->Reduce(ynn_reduce_sum, 7598, 7601, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 7601, 7599);
  g->Binary(ynn_binary_multiply, 7598, 7599, 1624);
  g->Matmul(1624, 1622, 1625, false, false);
  g->Slice(1616, 1626, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(1617, 1627, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(1618, 1628, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(1626, 1627, 1629, false, true);
  g->Mask(1629, 8673, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8673, 7605, {-1}, true);
  g->Binary(ynn_binary_subtract, 8673, 7605, 7602);
  g->Unary(ynn_unary_exp, 7602, 7603);
  g->Reduce(ynn_reduce_sum, 7603, 7606, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 7606, 7604);
  g->Binary(ynn_binary_multiply, 7603, 7604, 1631);
  g->Matmul(1631, 1628, 1632, false, false);
  g->Concat({1625,1632}, 1633, 1);
}

// Scope: "Layer18 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1633, 1634, {0,2,1,3});
  g->FuseDims(1634, 1635, 2, 2);
  g->Quantize(1635, 1636, 0.023868119344115257, 0);
  g->Transpose(8922, 5681, {1,0});
  g->Binary(ynn_binary_multiply, 5678, 5680, 5676);
  g->Dot(1636, 5681, YNN_INVALID_VALUE_ID, 5675, 1);
  g->DequantizeTensor(5675, YNN_INVALID_VALUE_ID, 5676, 5677);
  g->QuantizeTensor(5677, 8595, 5679, 1637);
  g->Dequantize(1637, 1638, 0.027112234383821487, 0);
}

// Scope: "Layer18 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1557, 1558);
  g->Reduce(ynn_reduce_sum, 1558, 7586, {2}, true);
  g->ShapeProduct(1558, 7585, {2});
  g->Binary(ynn_binary_divide, 7586, 7585, 1561);
  g->Binary(ynn_binary_add, 1561, 8647, 1562);
  g->Unary(ynn_unary_rsqrt, 1562, 1563);
  g->Binary(ynn_binary_multiply, 1557, 1563, 1564);
  g->Binary(ynn_binary_multiply, 1564, 8909, 1565);
  BuildLayer18AttentionKvProjection(ctx);
  BuildLayer18AttentionCacheUpdate(ctx);
  BuildLayer18AttentionQueryProjection(ctx);
  BuildLayer18AttentionSdpa(ctx);
  BuildLayer18AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1638, 1639);
  g->Reduce(ynn_reduce_sum, 1639, 7610, {2}, true);
  g->ShapeProduct(1639, 7609, {2});
  g->Binary(ynn_binary_divide, 7610, 7609, 1641);
  g->Binary(ynn_binary_add, 1641, 8647, 1642);
  g->Unary(ynn_unary_rsqrt, 1642, 1643);
  g->Binary(ynn_binary_multiply, 1638, 1643, 1644);
  g->Binary(ynn_binary_multiply, 1644, 8916, 1645);
  g->Binary(ynn_binary_add, 1645, 1557, 1646);
}

// Scope: "Layer18 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1646, 1647);
  g->Reduce(ynn_reduce_sum, 1647, 7612, {2}, true);
  g->ShapeProduct(1647, 7611, {2});
  g->Binary(ynn_binary_divide, 7612, 7611, 1648);
  g->Binary(ynn_binary_add, 1648, 8647, 1649);
  g->Unary(ynn_unary_rsqrt, 1649, 1650);
  g->Binary(ynn_binary_multiply, 1646, 1650, 1652);
  g->Binary(ynn_binary_multiply, 1652, 8919, 1653);
  g->Quantize(1653, 1654, 0.0140849519520998, 0);
  g->Transpose(8913, 5688, {1,0});
  g->Binary(ynn_binary_multiply, 5685, 5687, 5683);
  g->Dot(1654, 5688, YNN_INVALID_VALUE_ID, 5682, 1);
  g->DequantizeTensor(5682, YNN_INVALID_VALUE_ID, 5683, 5684);
  g->QuantizeTensor(5684, 8595, 5686, 1655);
  g->Dequantize(1655, 1656, 0.016732292249798775, 0);
  g->Transpose(8912, 5693, {1,0});
  g->Binary(ynn_binary_multiply, 5685, 5692, 5690);
  g->Dot(1654, 5693, YNN_INVALID_VALUE_ID, 5689, 1);
  g->DequantizeTensor(5689, YNN_INVALID_VALUE_ID, 5690, 5691);
  g->QuantizeTensor(5691, 8595, 5686, 1657);
  g->Dequantize(1657, 1658, 0.016732292249798775, 0);
  g->Polynomial(1658, 7615, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7615, 7616);
  g->Binary(ynn_binary_add, 7616, 7161, 7613);
  g->Binary(ynn_binary_multiply, 1658, 7173, 7614);
  g->Binary(ynn_binary_multiply, 7614, 7613, 1659);
  g->Binary(ynn_binary_multiply, 1656, 1659, 1660);
  g->Quantize(1660, 1663, 0.009719498455524445, 0);
  g->Transpose(8911, 5700, {1,0});
  g->Binary(ynn_binary_multiply, 5697, 5699, 5695);
  g->Dot(1663, 5700, YNN_INVALID_VALUE_ID, 5694, 1);
  g->DequantizeTensor(5694, YNN_INVALID_VALUE_ID, 5695, 5696);
  g->QuantizeTensor(5696, 8595, 5698, 1664);
  g->Dequantize(1664, 1665, 0.00551135279238224, 0);
  g->Unary(ynn_unary_square, 1665, 1666);
  g->Reduce(ynn_reduce_sum, 1666, 7618, {2}, true);
  g->ShapeProduct(1666, 7617, {2});
  g->Binary(ynn_binary_divide, 7618, 7617, 1667);
  g->Binary(ynn_binary_add, 1667, 8647, 1668);
  g->Unary(ynn_unary_rsqrt, 1668, 1669);
  g->Binary(ynn_binary_multiply, 1665, 1669, 1670);
  g->Binary(ynn_binary_multiply, 1670, 8917, 1671);
  g->Binary(ynn_binary_add, 1671, 1646, 1672);
}

// Scope: "Layer18 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 1674, {0,0,18,0}, {-1,-1,1,-1});
  g->Reshape(1674, 1675, {1,1,256});
  g->Unary(ynn_unary_square, 1675, 1676);
  g->Reduce(ynn_reduce_sum, 1676, 7620, {2}, true);
  g->ShapeProduct(1676, 7619, {2});
  g->Binary(ynn_binary_divide, 7620, 7619, 1677);
  g->Binary(ynn_binary_add, 1677, 8647, 1678);
  g->Unary(ynn_unary_rsqrt, 1678, 1679);
  g->Binary(ynn_binary_multiply, 1675, 1679, 1680);
  g->Binary(ynn_binary_multiply, 1680, 9401, 1681);
  g->Binary(ynn_binary_multiply, 9412, 8651, 1682);
  g->Binary(ynn_binary_add, 1681, 1682, 1683);
  g->Binary(ynn_binary_multiply, 1683, 8645, 1685);
  g->Quantize(1672, 1686, 0.157975435256958, 0);
  g->Transpose(8914, 5707, {1,0});
  g->Binary(ynn_binary_multiply, 5704, 5706, 5702);
  g->Dot(1686, 5707, YNN_INVALID_VALUE_ID, 5701, 1);
  g->DequantizeTensor(5701, YNN_INVALID_VALUE_ID, 5702, 5703);
  g->QuantizeTensor(5703, 8595, 5705, 1687);
  g->Dequantize(1687, 1688, 0.06397638469934464, 0);
  g->Polynomial(1688, 7623, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7623, 7624);
  g->Binary(ynn_binary_add, 7624, 7161, 7621);
  g->Binary(ynn_binary_multiply, 1688, 7173, 7622);
  g->Binary(ynn_binary_multiply, 7622, 7621, 1689);
  g->Binary(ynn_binary_multiply, 1689, 1685, 1690);
  g->Quantize(1690, 1691, 0.48622047901153564, 0);
  g->Transpose(8915, 5714, {1,0});
  g->Binary(ynn_binary_multiply, 5711, 5713, 5709);
  g->Dot(1691, 5714, YNN_INVALID_VALUE_ID, 5708, 1);
  g->DequantizeTensor(5708, YNN_INVALID_VALUE_ID, 5709, 5710);
  g->QuantizeTensor(5710, 8595, 5712, 1692);
  g->Dequantize(1692, 1693, 0.13593116402626038, 0);
  g->Unary(ynn_unary_square, 1693, 1694);
  g->Reduce(ynn_reduce_sum, 1694, 7626, {2}, true);
  g->ShapeProduct(1694, 7625, {2});
  g->Binary(ynn_binary_divide, 7626, 7625, 1696);
  g->Binary(ynn_binary_add, 1696, 8647, 1697);
  g->Unary(ynn_unary_rsqrt, 1697, 1698);
  g->Binary(ynn_binary_multiply, 1693, 1698, 1699);
  g->Binary(ynn_binary_multiply, 1699, 8918, 1700);
  g->Binary(ynn_binary_add, 1672, 1700, 1701);
  g->Binary(ynn_binary_multiply, 1701, 8910, 1702);
}

// Scope: "Layer18"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18(Context& ctx) {
  BuildLayer18Attention(ctx);
  BuildLayer18Mlp(ctx);
  BuildLayer18PerLayerEmbedding(ctx);
}

// Scope: "Layer19 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(1709, 1710, 0.12022246420383453, 0);
  g->Transpose(8938, 5721, {1,0});
  g->Binary(ynn_binary_multiply, 5718, 5720, 5716);
  g->Dot(1710, 5721, YNN_INVALID_VALUE_ID, 5715, 1);
  g->DequantizeTensor(5715, YNN_INVALID_VALUE_ID, 5716, 5717);
  g->QuantizeTensor(5717, 8595, 5719, 1711);
  g->Dequantize(1711, 1712, 0.11515748500823975, 0);
  g->SplitDim(1712, 1713, 2, {2,256});
  g->Transpose(1713, 1714, {0,2,1,3});
  g->Unary(ynn_unary_square, 1714, 1715);
  g->Reduce(ynn_reduce_sum, 1715, 7630, {3}, true);
  g->ShapeProduct(1715, 7629, {3});
  g->Binary(ynn_binary_divide, 7630, 7629, 1716);
  g->Binary(ynn_binary_add, 1716, 8647, 1718);
  g->Unary(ynn_unary_rsqrt, 1718, 1719);
  g->Binary(ynn_binary_multiply, 1714, 1719, 1720);
  g->Binary(ynn_binary_multiply, 1720, 8937, 1721);
  g->Slice(1721, 1722, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1721, 1723, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1723, 1724);
  g->Concat({1724,1722}, 1725, 3);
  g->Binary(ynn_binary_multiply, 1721, 3141, 1726);
  g->Binary(ynn_binary_multiply, 1725, 4217, 1727);
  g->Binary(ynn_binary_add, 1726, 1727, 1729);
  g->Transpose(8942, 5726, {1,0});
  g->Binary(ynn_binary_multiply, 5718, 5725, 5723);
  g->Dot(1710, 5726, YNN_INVALID_VALUE_ID, 5722, 1);
  g->DequantizeTensor(5722, YNN_INVALID_VALUE_ID, 5723, 5724);
  g->QuantizeTensor(5724, 8595, 5719, 1730);
  g->Dequantize(1730, 1731, 0.11515748500823975, 0);
  g->SplitDim(1731, 1732, 2, {2,256});
  g->Transpose(1732, 1733, {0,2,1,3});
  g->Unary(ynn_unary_square, 1733, 1734);
  g->Reduce(ynn_reduce_sum, 1734, 7632, {3}, true);
  g->ShapeProduct(1734, 7631, {3});
  g->Binary(ynn_binary_divide, 7632, 7631, 1735);
  g->Binary(ynn_binary_add, 1735, 8647, 1736);
  g->Unary(ynn_unary_rsqrt, 1736, 1737);
  g->Binary(ynn_binary_multiply, 1733, 1737, 1739);
}

// Scope: "Layer19 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(1729, 1740, 0.005869260523468256, 0);
  g->Append(8607, 1740, 9456, 2, s2, slinky::expr(int64_t{1}));
  g->View(9456, 9504, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(1739, 1741, 0.047244105488061905, 0);
  g->Append(8631, 1741, 9480, 2, s2, slinky::expr(int64_t{1}));
  g->View(9480, 9528, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer19 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(8941, 5732, {1,0});
  g->Binary(ynn_binary_multiply, 5718, 5731, 5728);
  g->Dot(1710, 5732, YNN_INVALID_VALUE_ID, 5727, 1);
  g->DequantizeTensor(5727, YNN_INVALID_VALUE_ID, 5728, 5729);
  g->QuantizeTensor(5729, 8595, 5730, 1742);
  g->Dequantize(1742, 1743, 0.1328740268945694, 0);
  g->SplitDim(1743, 1745, 2, {8,256});
  g->Transpose(1745, 1746, {0,2,1,3});
  g->Unary(ynn_unary_square, 1746, 1747);
  g->Reduce(ynn_reduce_sum, 1747, 7636, {3}, true);
  g->ShapeProduct(1747, 7635, {3});
  g->Binary(ynn_binary_divide, 7636, 7635, 1748);
  g->Binary(ynn_binary_add, 1748, 8647, 1749);
  g->Unary(ynn_unary_rsqrt, 1749, 1750);
  g->Binary(ynn_binary_multiply, 1746, 1750, 1751);
  g->Binary(ynn_binary_multiply, 1751, 8940, 1752);
  g->Slice(1752, 1753, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1752, 1754, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1754, 1756);
  g->Concat({1756,1753}, 1757, 3);
  g->Binary(ynn_binary_multiply, 1752, 3141, 1758);
  g->Binary(ynn_binary_multiply, 1757, 4217, 1759);
  g->Binary(ynn_binary_add, 1758, 1759, 1760);
}

// Scope: "Layer19 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9504, 1761, 0.005869260523468256, 0);
  g->Dequantize(9528, 1762, 0.047244105488061905, 0);
  g->Slice(1760, 1763, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(1761, 1764, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(1762, 1765, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(1763, 1764, 1768, false, true);
  g->Mask(1768, 8674, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8674, 7642, {-1}, true);
  g->Binary(ynn_binary_subtract, 8674, 7642, 7639);
  g->Unary(ynn_unary_exp, 7639, 7640);
  g->Reduce(ynn_reduce_sum, 7640, 7643, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 7643, 7641);
  g->Binary(ynn_binary_multiply, 7640, 7641, 1769);
  g->Matmul(1769, 1765, 1770, false, false);
  g->Slice(1760, 1771, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(1761, 1772, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(1762, 1773, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(1771, 1772, 1774, false, true);
  g->Mask(1774, 8675, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8675, 7647, {-1}, true);
  g->Binary(ynn_binary_subtract, 8675, 7647, 7644);
  g->Unary(ynn_unary_exp, 7644, 7645);
  g->Reduce(ynn_reduce_sum, 7645, 7648, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 7648, 7646);
  g->Binary(ynn_binary_multiply, 7645, 7646, 1775);
  g->Matmul(1775, 1773, 1777, false, false);
  g->Concat({1770,1777}, 1778, 1);
}

// Scope: "Layer19 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1778, 1779, {0,2,1,3});
  g->FuseDims(1779, 1780, 2, 2);
  g->Quantize(1780, 1781, 0.02509843371808529, 0);
  g->Transpose(8939, 5739, {1,0});
  g->Binary(ynn_binary_multiply, 5736, 5738, 5734);
  g->Dot(1781, 5739, YNN_INVALID_VALUE_ID, 5733, 1);
  g->DequantizeTensor(5733, YNN_INVALID_VALUE_ID, 5734, 5735);
  g->QuantizeTensor(5735, 8595, 5737, 1782);
  g->Dequantize(1782, 1783, 0.02879992686212063, 0);
}

// Scope: "Layer19 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1702, 1703);
  g->Reduce(ynn_reduce_sum, 1703, 7628, {2}, true);
  g->ShapeProduct(1703, 7627, {2});
  g->Binary(ynn_binary_divide, 7628, 7627, 1704);
  g->Binary(ynn_binary_add, 1704, 8647, 1705);
  g->Unary(ynn_unary_rsqrt, 1705, 1707);
  g->Binary(ynn_binary_multiply, 1702, 1707, 1708);
  g->Binary(ynn_binary_multiply, 1708, 8926, 1709);
  BuildLayer19AttentionKvProjection(ctx);
  BuildLayer19AttentionCacheUpdate(ctx);
  BuildLayer19AttentionQueryProjection(ctx);
  BuildLayer19AttentionSdpa(ctx);
  BuildLayer19AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1783, 1784);
  g->Reduce(ynn_reduce_sum, 1784, 7650, {2}, true);
  g->ShapeProduct(1784, 7649, {2});
  g->Binary(ynn_binary_divide, 7650, 7649, 1785);
  g->Binary(ynn_binary_add, 1785, 8647, 1786);
  g->Unary(ynn_unary_rsqrt, 1786, 1788);
  g->Binary(ynn_binary_multiply, 1783, 1788, 1789);
  g->Binary(ynn_binary_multiply, 1789, 8933, 1790);
  g->Binary(ynn_binary_add, 1790, 1702, 1791);
}

// Scope: "Layer19 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1791, 1792);
  g->Reduce(ynn_reduce_sum, 1792, 7652, {2}, true);
  g->ShapeProduct(1792, 7651, {2});
  g->Binary(ynn_binary_divide, 7652, 7651, 1793);
  g->Binary(ynn_binary_add, 1793, 8647, 1794);
  g->Unary(ynn_unary_rsqrt, 1794, 1795);
  g->Binary(ynn_binary_multiply, 1791, 1795, 1796);
  g->Binary(ynn_binary_multiply, 1796, 8936, 1797);
  g->Quantize(1797, 1799, 0.01280234195291996, 0);
  g->Transpose(8930, 5746, {1,0});
  g->Binary(ynn_binary_multiply, 5743, 5745, 5741);
  g->Dot(1799, 5746, YNN_INVALID_VALUE_ID, 5740, 1);
  g->DequantizeTensor(5740, YNN_INVALID_VALUE_ID, 5741, 5742);
  g->QuantizeTensor(5742, 8595, 5744, 1800);
  g->Dequantize(1800, 1801, 0.014456210657954216, 0);
  g->Transpose(8929, 5751, {1,0});
  g->Binary(ynn_binary_multiply, 5743, 5750, 5748);
  g->Dot(1799, 5751, YNN_INVALID_VALUE_ID, 5747, 1);
  g->DequantizeTensor(5747, YNN_INVALID_VALUE_ID, 5748, 5749);
  g->QuantizeTensor(5749, 8595, 5744, 1802);
  g->Dequantize(1802, 1803, 0.014456210657954216, 0);
  g->Polynomial(1803, 7655, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7655, 7656);
  g->Binary(ynn_binary_add, 7656, 7161, 7653);
  g->Binary(ynn_binary_multiply, 1803, 7173, 7654);
  g->Binary(ynn_binary_multiply, 7654, 7653, 1804);
  g->Binary(ynn_binary_multiply, 1801, 1804, 1805);
  g->Quantize(1805, 1806, 0.0076587204821407795, 0);
  g->Transpose(8928, 5758, {1,0});
  g->Binary(ynn_binary_multiply, 5755, 5757, 5753);
  g->Dot(1806, 5758, YNN_INVALID_VALUE_ID, 5752, 1);
  g->DequantizeTensor(5752, YNN_INVALID_VALUE_ID, 5753, 5754);
  g->QuantizeTensor(5754, 8595, 5756, 1807);
  g->Dequantize(1807, 1809, 0.004359397571533918, 0);
  g->Unary(ynn_unary_square, 1809, 1810);
  g->Reduce(ynn_reduce_sum, 1810, 7658, {2}, true);
  g->ShapeProduct(1810, 7657, {2});
  g->Binary(ynn_binary_divide, 7658, 7657, 1811);
  g->Binary(ynn_binary_add, 1811, 8647, 1812);
  g->Unary(ynn_unary_rsqrt, 1812, 1813);
  g->Binary(ynn_binary_multiply, 1809, 1813, 1814);
  g->Binary(ynn_binary_multiply, 1814, 8934, 1815);
  g->Binary(ynn_binary_add, 1815, 1791, 1816);
}

// Scope: "Layer19 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 1817, {0,0,19,0}, {-1,-1,1,-1});
  g->Reshape(1817, 1818, {1,1,256});
  g->Unary(ynn_unary_square, 1818, 1820);
  g->Reduce(ynn_reduce_sum, 1820, 7660, {2}, true);
  g->ShapeProduct(1820, 7659, {2});
  g->Binary(ynn_binary_divide, 7660, 7659, 1821);
  g->Binary(ynn_binary_add, 1821, 8647, 1822);
  g->Unary(ynn_unary_rsqrt, 1822, 1823);
  g->Binary(ynn_binary_multiply, 1818, 1823, 1824);
  g->Binary(ynn_binary_multiply, 1824, 9401, 1825);
  g->Binary(ynn_binary_multiply, 9413, 8651, 1826);
  g->Binary(ynn_binary_add, 1825, 1826, 1827);
  g->Binary(ynn_binary_multiply, 1827, 8645, 1828);
  g->Quantize(1816, 1829, 0.12497252225875854, 0);
  g->Transpose(8931, 5771, {1,0});
  g->Binary(ynn_binary_multiply, 5768, 5770, 5766);
  g->Dot(1829, 5771, YNN_INVALID_VALUE_ID, 5765, 1);
  g->DequantizeTensor(5765, YNN_INVALID_VALUE_ID, 5766, 5767);
  g->QuantizeTensor(5767, 8595, 5769, 1831);
  g->Dequantize(1831, 1832, 0.0743110328912735, 0);
  g->Polynomial(1832, 7663, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7663, 7664);
  g->Binary(ynn_binary_add, 7664, 7161, 7661);
  g->Binary(ynn_binary_multiply, 1832, 7173, 7662);
  g->Binary(ynn_binary_multiply, 7662, 7661, 1833);
  g->Binary(ynn_binary_multiply, 1833, 1828, 1834);
  g->Quantize(1834, 1835, 0.1643700897693634, 0);
  g->Transpose(8932, 5778, {1,0});
  g->Binary(ynn_binary_multiply, 5775, 5777, 5773);
  g->Dot(1835, 5778, YNN_INVALID_VALUE_ID, 5772, 1);
  g->DequantizeTensor(5772, YNN_INVALID_VALUE_ID, 5773, 5774);
  g->QuantizeTensor(5774, 8595, 5776, 1836);
  g->Dequantize(1836, 1837, 0.10370250046253204, 0);
  g->Unary(ynn_unary_square, 1837, 1838);
  g->Reduce(ynn_reduce_sum, 1838, 7666, {2}, true);
  g->ShapeProduct(1838, 7665, {2});
  g->Binary(ynn_binary_divide, 7666, 7665, 1839);
  g->Binary(ynn_binary_add, 1839, 8647, 1840);
  g->Unary(ynn_unary_rsqrt, 1840, 1842);
  g->Binary(ynn_binary_multiply, 1837, 1842, 1843);
  g->Binary(ynn_binary_multiply, 1843, 8935, 1844);
  g->Binary(ynn_binary_add, 1816, 1844, 1845);
  g->Binary(ynn_binary_multiply, 1845, 8927, 1846);
}

// Scope: "Layer19"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19(Context& ctx) {
  BuildLayer19Attention(ctx);
  BuildLayer19Mlp(ctx);
  BuildLayer19PerLayerEmbedding(ctx);
}

// Scope: "Layer20 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(1853, 1854, 0.04660104587674141, 0);
  g->Transpose(8972, 5785, {1,0});
  g->Binary(ynn_binary_multiply, 5782, 5784, 5780);
  g->Dot(1854, 5785, YNN_INVALID_VALUE_ID, 5779, 1);
  g->DequantizeTensor(5779, YNN_INVALID_VALUE_ID, 5780, 5781);
  g->QuantizeTensor(5781, 8595, 5783, 1855);
  g->Dequantize(1855, 1856, 0.05807087570428848, 0);
  g->SplitDim(1856, 1857, 2, {2,256});
  g->Transpose(1857, 1858, {0,2,1,3});
  g->Unary(ynn_unary_square, 1858, 1859);
  g->Reduce(ynn_reduce_sum, 1859, 7674, {3}, true);
  g->ShapeProduct(1859, 7673, {3});
  g->Binary(ynn_binary_divide, 7674, 7673, 1860);
  g->Binary(ynn_binary_add, 1860, 8647, 1861);
  g->Unary(ynn_unary_rsqrt, 1861, 1862);
  g->Binary(ynn_binary_multiply, 1858, 1862, 1864);
  g->Binary(ynn_binary_multiply, 1864, 8971, 1865);
  g->Slice(1865, 1866, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1865, 1867, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1867, 1868);
  g->Concat({1868,1866}, 1869, 3);
  g->Binary(ynn_binary_multiply, 1865, 3141, 1870);
  g->Binary(ynn_binary_multiply, 1869, 4217, 1871);
  g->Binary(ynn_binary_add, 1870, 1871, 1872);
  g->Transpose(8976, 5790, {1,0});
  g->Binary(ynn_binary_multiply, 5782, 5789, 5787);
  g->Dot(1854, 5790, YNN_INVALID_VALUE_ID, 5786, 1);
  g->DequantizeTensor(5786, YNN_INVALID_VALUE_ID, 5787, 5788);
  g->QuantizeTensor(5788, 8595, 5783, 1875);
  g->Dequantize(1875, 1876, 0.05807087570428848, 0);
  g->SplitDim(1876, 1877, 2, {2,256});
  g->Transpose(1877, 1878, {0,2,1,3});
  g->Unary(ynn_unary_square, 1878, 1879);
  g->Reduce(ynn_reduce_sum, 1879, 7676, {3}, true);
  g->ShapeProduct(1879, 7675, {3});
  g->Binary(ynn_binary_divide, 7676, 7675, 1880);
  g->Binary(ynn_binary_add, 1880, 8647, 1881);
  g->Unary(ynn_unary_rsqrt, 1881, 1882);
  g->Binary(ynn_binary_multiply, 1878, 1882, 1883);
}

// Scope: "Layer20 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(1872, 1884, 0.005907459184527397, 0);
  g->Append(8609, 1884, 9458, 2, s2, slinky::expr(int64_t{1}));
  g->View(9458, 9506, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(1883, 1886, 0.047244105488061905, 0);
  g->Append(8633, 1886, 9482, 2, s2, slinky::expr(int64_t{1}));
  g->View(9482, 9530, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer20 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(8975, 5803, {1,0});
  g->Binary(ynn_binary_multiply, 5782, 5802, 5799);
  g->Dot(1854, 5803, YNN_INVALID_VALUE_ID, 5798, 1);
  g->DequantizeTensor(5798, YNN_INVALID_VALUE_ID, 5799, 5800);
  g->QuantizeTensor(5800, 8595, 5801, 1887);
  g->Dequantize(1887, 1888, 0.08710630983114243, 0);
  g->SplitDim(1888, 1889, 2, {8,256});
  g->Transpose(1889, 1890, {0,2,1,3});
  g->Unary(ynn_unary_square, 1890, 1892);
  g->Reduce(ynn_reduce_sum, 1892, 7678, {3}, true);
  g->ShapeProduct(1892, 7677, {3});
  g->Binary(ynn_binary_divide, 7678, 7677, 1893);
  g->Binary(ynn_binary_add, 1893, 8647, 1894);
  g->Unary(ynn_unary_rsqrt, 1894, 1895);
  g->Binary(ynn_binary_multiply, 1890, 1895, 1896);
  g->Binary(ynn_binary_multiply, 1896, 8974, 1897);
  g->Slice(1897, 1898, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1897, 1899, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1899, 1900);
  g->Concat({1900,1898}, 1901, 3);
  g->Binary(ynn_binary_multiply, 1897, 3141, 1903);
  g->Binary(ynn_binary_multiply, 1901, 4217, 1904);
  g->Binary(ynn_binary_add, 1903, 1904, 1905);
}

// Scope: "Layer20 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9506, 1906, 0.005907459184527397, 0);
  g->Dequantize(9530, 1907, 0.047244105488061905, 0);
  g->Slice(1905, 1908, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(1906, 1909, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(1907, 1910, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(1908, 1909, 1911, false, true);
  g->Mask(1911, 8678, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8678, 7684, {-1}, true);
  g->Binary(ynn_binary_subtract, 8678, 7684, 7681);
  g->Unary(ynn_unary_exp, 7681, 7682);
  g->Reduce(ynn_reduce_sum, 7682, 7685, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 7685, 7683);
  g->Binary(ynn_binary_multiply, 7682, 7683, 1913);
  g->Matmul(1913, 1910, 1914, false, false);
  g->Slice(1905, 1915, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(1906, 1916, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(1907, 1917, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(1915, 1916, 1918, false, true);
  g->Mask(1918, 8679, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8679, 7689, {-1}, true);
  g->Binary(ynn_binary_subtract, 8679, 7689, 7686);
  g->Unary(ynn_unary_exp, 7686, 7687);
  g->Reduce(ynn_reduce_sum, 7687, 7690, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 7690, 7688);
  g->Binary(ynn_binary_multiply, 7687, 7688, 1919);
  g->Matmul(1919, 1917, 1920, false, false);
  g->Concat({1914,1920}, 1921, 1);
}

// Scope: "Layer20 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1921, 1923, {0,2,1,3});
  g->FuseDims(1923, 1924, 2, 2);
  g->Quantize(1924, 1925, 0.025713592767715454, 0);
  g->Transpose(8973, 5810, {1,0});
  g->Binary(ynn_binary_multiply, 5807, 5809, 5805);
  g->Dot(1925, 5810, YNN_INVALID_VALUE_ID, 5804, 1);
  g->DequantizeTensor(5804, YNN_INVALID_VALUE_ID, 5805, 5806);
  g->QuantizeTensor(5806, 8595, 5808, 1926);
  g->Dequantize(1926, 1927, 0.03443482890725136, 0);
}

// Scope: "Layer20 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1846, 1847);
  g->Reduce(ynn_reduce_sum, 1847, 7668, {2}, true);
  g->ShapeProduct(1847, 7667, {2});
  g->Binary(ynn_binary_divide, 7668, 7667, 1848);
  g->Binary(ynn_binary_add, 1848, 8647, 1849);
  g->Unary(ynn_unary_rsqrt, 1849, 1850);
  g->Binary(ynn_binary_multiply, 1846, 1850, 1851);
  g->Binary(ynn_binary_multiply, 1851, 8960, 1853);
  BuildLayer20AttentionKvProjection(ctx);
  BuildLayer20AttentionCacheUpdate(ctx);
  BuildLayer20AttentionQueryProjection(ctx);
  BuildLayer20AttentionSdpa(ctx);
  BuildLayer20AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1927, 1928);
  g->Reduce(ynn_reduce_sum, 1928, 7692, {2}, true);
  g->ShapeProduct(1928, 7691, {2});
  g->Binary(ynn_binary_divide, 7692, 7691, 1929);
  g->Binary(ynn_binary_add, 1929, 8647, 1930);
  g->Unary(ynn_unary_rsqrt, 1930, 1931);
  g->Binary(ynn_binary_multiply, 1927, 1931, 1932);
  g->Binary(ynn_binary_multiply, 1932, 8967, 1934);
  g->Binary(ynn_binary_add, 1934, 1846, 1935);
}

// Scope: "Layer20 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1935, 1936);
  g->Reduce(ynn_reduce_sum, 1936, 7694, {2}, true);
  g->ShapeProduct(1936, 7693, {2});
  g->Binary(ynn_binary_divide, 7694, 7693, 1937);
  g->Binary(ynn_binary_add, 1937, 8647, 1938);
  g->Unary(ynn_unary_rsqrt, 1938, 1939);
  g->Binary(ynn_binary_multiply, 1935, 1939, 1940);
  g->Binary(ynn_binary_multiply, 1940, 8970, 1941);
  g->Quantize(1941, 1942, 0.014479842968285084, 0);
  g->Transpose(8964, 5817, {1,0});
  g->Binary(ynn_binary_multiply, 5814, 5816, 5812);
  g->Dot(1942, 5817, YNN_INVALID_VALUE_ID, 5811, 1);
  g->DequantizeTensor(5811, YNN_INVALID_VALUE_ID, 5812, 5813);
  g->QuantizeTensor(5813, 8595, 5815, 1943);
  g->Dequantize(1943, 1945, 0.015071368776261806, 0);
  g->Transpose(8963, 5822, {1,0});
  g->Binary(ynn_binary_multiply, 5814, 5821, 5819);
  g->Dot(1942, 5822, YNN_INVALID_VALUE_ID, 5818, 1);
  g->DequantizeTensor(5818, YNN_INVALID_VALUE_ID, 5819, 5820);
  g->QuantizeTensor(5820, 8595, 5815, 1946);
  g->Dequantize(1946, 1947, 0.015071368776261806, 0);
  g->Polynomial(1947, 7697, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7697, 7698);
  g->Binary(ynn_binary_add, 7698, 7161, 7695);
  g->Binary(ynn_binary_multiply, 1947, 7173, 7696);
  g->Binary(ynn_binary_multiply, 7696, 7695, 1948);
  g->Binary(ynn_binary_multiply, 1945, 1948, 1949);
  g->Quantize(1949, 1950, 0.005413395818322897, 0);
  g->Transpose(8962, 5829, {1,0});
  g->Binary(ynn_binary_multiply, 5826, 5828, 5824);
  g->Dot(1950, 5829, YNN_INVALID_VALUE_ID, 5823, 1);
  g->DequantizeTensor(5823, YNN_INVALID_VALUE_ID, 5824, 5825);
  g->QuantizeTensor(5825, 8595, 5827, 1951);
  g->Dequantize(1951, 1952, 0.004781397990882397, 0);
  g->Unary(ynn_unary_square, 1952, 1953);
  g->Reduce(ynn_reduce_sum, 1953, 7700, {2}, true);
  g->ShapeProduct(1953, 7699, {2});
  g->Binary(ynn_binary_divide, 7700, 7699, 1955);
  g->Binary(ynn_binary_add, 1955, 8647, 1956);
  g->Unary(ynn_unary_rsqrt, 1956, 1957);
  g->Binary(ynn_binary_multiply, 1952, 1957, 1958);
  g->Binary(ynn_binary_multiply, 1958, 8968, 1959);
  g->Binary(ynn_binary_add, 1959, 1935, 1960);
}

// Scope: "Layer20 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 1961, {0,0,20,0}, {-1,-1,1,-1});
  g->Reshape(1961, 1962, {1,1,256});
  g->Unary(ynn_unary_square, 1962, 1963);
  g->Reduce(ynn_reduce_sum, 1963, 7702, {2}, true);
  g->ShapeProduct(1963, 7701, {2});
  g->Binary(ynn_binary_divide, 7702, 7701, 1964);
  g->Binary(ynn_binary_add, 1964, 8647, 1966);
  g->Unary(ynn_unary_rsqrt, 1966, 1967);
  g->Binary(ynn_binary_multiply, 1962, 1967, 1968);
  g->Binary(ynn_binary_multiply, 1968, 9401, 1969);
  g->Binary(ynn_binary_multiply, 9415, 8651, 1970);
  g->Binary(ynn_binary_add, 1969, 1970, 1971);
  g->Binary(ynn_binary_multiply, 1971, 8645, 1972);
  g->Quantize(1960, 1973, 0.17325256764888763, 0);
  g->Transpose(8965, 5836, {1,0});
  g->Binary(ynn_binary_multiply, 5833, 5835, 5831);
  g->Dot(1973, 5836, YNN_INVALID_VALUE_ID, 5830, 1);
  g->DequantizeTensor(5830, YNN_INVALID_VALUE_ID, 5831, 5832);
  g->QuantizeTensor(5832, 8595, 5834, 1974);
  g->Dequantize(1974, 1975, 0.09940945357084274, 0);
  g->Polynomial(1975, 7705, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7705, 7706);
  g->Binary(ynn_binary_add, 7706, 7161, 7703);
  g->Binary(ynn_binary_multiply, 1975, 7173, 7704);
  g->Binary(ynn_binary_multiply, 7704, 7703, 1978);
  g->Binary(ynn_binary_multiply, 1978, 1972, 1979);
  g->Quantize(1979, 1980, 0.8149606585502625, 0);
  g->Transpose(8966, 5843, {1,0});
  g->Binary(ynn_binary_multiply, 5840, 5842, 5838);
  g->Dot(1980, 5843, YNN_INVALID_VALUE_ID, 5837, 1);
  g->DequantizeTensor(5837, YNN_INVALID_VALUE_ID, 5838, 5839);
  g->QuantizeTensor(5839, 8595, 5841, 1981);
  g->Dequantize(1981, 1982, 0.16500307619571686, 0);
  g->Unary(ynn_unary_square, 1982, 1983);
  g->Reduce(ynn_reduce_sum, 1983, 7708, {2}, true);
  g->ShapeProduct(1983, 7707, {2});
  g->Binary(ynn_binary_divide, 7708, 7707, 1984);
  g->Binary(ynn_binary_add, 1984, 8647, 1985);
  g->Unary(ynn_unary_rsqrt, 1985, 1986);
  g->Binary(ynn_binary_multiply, 1982, 1986, 1987);
  g->Binary(ynn_binary_multiply, 1987, 8969, 1989);
  g->Binary(ynn_binary_add, 1960, 1989, 1990);
  g->Binary(ynn_binary_multiply, 1990, 8961, 1991);
}

// Scope: "Layer20"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20(Context& ctx) {
  BuildLayer20Attention(ctx);
  BuildLayer20Mlp(ctx);
  BuildLayer20PerLayerEmbedding(ctx);
}

// Scope: "Layer21 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(1997, 1998, 0.03492194786667824, 0);
  g->Transpose(8989, 5850, {1,0});
  g->Binary(ynn_binary_multiply, 5847, 5849, 5845);
  g->Dot(1998, 5850, YNN_INVALID_VALUE_ID, 5844, 1);
  g->DequantizeTensor(5844, YNN_INVALID_VALUE_ID, 5845, 5846);
  g->QuantizeTensor(5846, 8595, 5848, 2000);
  g->Dequantize(2000, 2001, 0.03961615264415741, 0);
  g->SplitDim(2001, 2002, 2, {2,256});
  g->Transpose(2002, 2003, {0,2,1,3});
  g->Unary(ynn_unary_square, 2003, 2004);
  g->Reduce(ynn_reduce_sum, 2004, 7714, {3}, true);
  g->ShapeProduct(2004, 7713, {3});
  g->Binary(ynn_binary_divide, 7714, 7713, 2005);
  g->Binary(ynn_binary_add, 2005, 8647, 2006);
  g->Unary(ynn_unary_rsqrt, 2006, 2007);
  g->Binary(ynn_binary_multiply, 2003, 2007, 2008);
  g->Binary(ynn_binary_multiply, 2008, 8988, 2009);
  g->Slice(2009, 2011, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2009, 2012, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2012, 2013);
  g->Concat({2013,2011}, 2014, 3);
  g->Binary(ynn_binary_multiply, 2009, 3141, 2015);
  g->Binary(ynn_binary_multiply, 2014, 4217, 2016);
  g->Binary(ynn_binary_add, 2015, 2016, 2017);
  g->Transpose(8993, 5855, {1,0});
  g->Binary(ynn_binary_multiply, 5847, 5854, 5852);
  g->Dot(1998, 5855, YNN_INVALID_VALUE_ID, 5851, 1);
  g->DequantizeTensor(5851, YNN_INVALID_VALUE_ID, 5852, 5853);
  g->QuantizeTensor(5853, 8595, 5848, 2018);
  g->Dequantize(2018, 2019, 0.03961615264415741, 0);
  g->SplitDim(2019, 2021, 2, {2,256});
  g->Transpose(2021, 2022, {0,2,1,3});
  g->Unary(ynn_unary_square, 2022, 2023);
  g->Reduce(ynn_reduce_sum, 2023, 7716, {3}, true);
  g->ShapeProduct(2023, 7715, {3});
  g->Binary(ynn_binary_divide, 7716, 7715, 2024);
  g->Binary(ynn_binary_add, 2024, 8647, 2025);
  g->Unary(ynn_unary_rsqrt, 2025, 2026);
  g->Binary(ynn_binary_multiply, 2022, 2026, 2027);
}

// Scope: "Layer21 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(2017, 2028, 0.0060269939713180065, 0);
  g->Append(8610, 2028, 9459, 2, s2, slinky::expr(int64_t{1}));
  g->View(9459, 9507, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(2027, 2030, 0.047244105488061905, 0);
  g->Append(8634, 2030, 9483, 2, s2, slinky::expr(int64_t{1}));
  g->View(9483, 9531, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer21 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(8992, 5861, {1,0});
  g->Binary(ynn_binary_multiply, 5847, 5860, 5857);
  g->Dot(1998, 5861, YNN_INVALID_VALUE_ID, 5856, 1);
  g->DequantizeTensor(5856, YNN_INVALID_VALUE_ID, 5857, 5858);
  g->QuantizeTensor(5858, 8595, 5859, 2031);
  g->Dequantize(2031, 2032, 0.049212608486413956, 0);
  g->SplitDim(2032, 2033, 2, {8,256});
  g->Transpose(2033, 2034, {0,2,1,3});
  g->Unary(ynn_unary_square, 2034, 2035);
  g->Reduce(ynn_reduce_sum, 2035, 7718, {3}, true);
  g->ShapeProduct(2035, 7717, {3});
  g->Binary(ynn_binary_divide, 7718, 7717, 2036);
  g->Binary(ynn_binary_add, 2036, 8647, 2038);
  g->Unary(ynn_unary_rsqrt, 2038, 2039);
  g->Binary(ynn_binary_multiply, 2034, 2039, 2040);
  g->Binary(ynn_binary_multiply, 2040, 8991, 2041);
  g->Slice(2041, 2042, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2041, 2043, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2043, 2044);
  g->Concat({2044,2042}, 2045, 3);
  g->Binary(ynn_binary_multiply, 2041, 3141, 2046);
  g->Binary(ynn_binary_multiply, 2045, 4217, 2047);
  g->Binary(ynn_binary_add, 2046, 2047, 2049);
}

// Scope: "Layer21 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9507, 2050, 0.0060269939713180065, 0);
  g->Dequantize(9531, 2051, 0.047244105488061905, 0);
  g->Slice(2049, 2052, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(2050, 2053, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(2051, 2054, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(2052, 2053, 2055, false, true);
  g->Mask(2055, 8680, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8680, 7722, {-1}, true);
  g->Binary(ynn_binary_subtract, 8680, 7722, 7719);
  g->Unary(ynn_unary_exp, 7719, 7720);
  g->Reduce(ynn_reduce_sum, 7720, 7723, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 7723, 7721);
  g->Binary(ynn_binary_multiply, 7720, 7721, 2056);
  g->Matmul(2056, 2054, 2057, false, false);
  g->Slice(2049, 2059, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(2050, 2060, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(2051, 2061, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(2059, 2060, 2062, false, true);
  g->Mask(2062, 8681, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8681, 7727, {-1}, true);
  g->Binary(ynn_binary_subtract, 8681, 7727, 7724);
  g->Unary(ynn_unary_exp, 7724, 7725);
  g->Reduce(ynn_reduce_sum, 7725, 7728, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 7728, 7726);
  g->Binary(ynn_binary_multiply, 7725, 7726, 2063);
  g->Matmul(2063, 2061, 2064, false, false);
  g->Concat({2057,2064}, 2065, 1);
}

// Scope: "Layer21 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(2065, 2066, {0,2,1,3});
  g->FuseDims(2066, 2067, 2, 2);
  g->Quantize(2067, 2069, 0.02325296215713024, 0);
  g->Transpose(8990, 5874, {1,0});
  g->Binary(ynn_binary_multiply, 5871, 5873, 5869);
  g->Dot(2069, 5874, YNN_INVALID_VALUE_ID, 5868, 1);
  g->DequantizeTensor(5868, YNN_INVALID_VALUE_ID, 5869, 5870);
  g->QuantizeTensor(5870, 8595, 5872, 2070);
  g->Dequantize(2070, 2071, 0.027936452999711037, 0);
}

// Scope: "Layer21 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1991, 1992);
  g->Reduce(ynn_reduce_sum, 1992, 7710, {2}, true);
  g->ShapeProduct(1992, 7709, {2});
  g->Binary(ynn_binary_divide, 7710, 7709, 1993);
  g->Binary(ynn_binary_add, 1993, 8647, 1994);
  g->Unary(ynn_unary_rsqrt, 1994, 1995);
  g->Binary(ynn_binary_multiply, 1991, 1995, 1996);
  g->Binary(ynn_binary_multiply, 1996, 8977, 1997);
  BuildLayer21AttentionKvProjection(ctx);
  BuildLayer21AttentionCacheUpdate(ctx);
  BuildLayer21AttentionQueryProjection(ctx);
  BuildLayer21AttentionSdpa(ctx);
  BuildLayer21AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2071, 2072);
  g->Reduce(ynn_reduce_sum, 2072, 7730, {2}, true);
  g->ShapeProduct(2072, 7729, {2});
  g->Binary(ynn_binary_divide, 7730, 7729, 2073);
  g->Binary(ynn_binary_add, 2073, 8647, 2074);
  g->Unary(ynn_unary_rsqrt, 2074, 2075);
  g->Binary(ynn_binary_multiply, 2071, 2075, 2076);
  g->Binary(ynn_binary_multiply, 2076, 8984, 2077);
  g->Binary(ynn_binary_add, 2077, 1991, 2078);
}

// Scope: "Layer21 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2078, 2082);
  g->Reduce(ynn_reduce_sum, 2082, 7732, {2}, true);
  g->ShapeProduct(2082, 7731, {2});
  g->Binary(ynn_binary_divide, 7732, 7731, 2083);
  g->Binary(ynn_binary_add, 2083, 8647, 2084);
  g->Unary(ynn_unary_rsqrt, 2084, 2085);
  g->Binary(ynn_binary_multiply, 2078, 2085, 2086);
  g->Binary(ynn_binary_multiply, 2086, 8987, 2087);
  g->Quantize(2087, 2088, 0.015300169587135315, 0);
  g->Transpose(8981, 5880, {1,0});
  g->Binary(ynn_binary_multiply, 5878, 5879, 5876);
  g->Dot(2088, 5880, YNN_INVALID_VALUE_ID, 5875, 1);
  g->DequantizeTensor(5875, YNN_INVALID_VALUE_ID, 5876, 5877);
  g->QuantizeTensor(5877, 8595, 5602, 2089);
  g->Dequantize(2089, 2090, 0.01771654561161995, 0);
  g->Transpose(8980, 5885, {1,0});
  g->Binary(ynn_binary_multiply, 5878, 5884, 5882);
  g->Dot(2088, 5885, YNN_INVALID_VALUE_ID, 5881, 1);
  g->DequantizeTensor(5881, YNN_INVALID_VALUE_ID, 5882, 5883);
  g->QuantizeTensor(5883, 8595, 5602, 2092);
  g->Dequantize(2092, 2093, 0.01771654561161995, 0);
  g->Polynomial(2093, 7735, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7735, 7736);
  g->Binary(ynn_binary_add, 7736, 7161, 7733);
  g->Binary(ynn_binary_multiply, 2093, 7173, 7734);
  g->Binary(ynn_binary_multiply, 7734, 7733, 2094);
  g->Binary(ynn_binary_multiply, 2090, 2094, 2095);
  g->Quantize(2095, 2096, 0.017962608486413956, 0);
  g->Transpose(8979, 5892, {1,0});
  g->Binary(ynn_binary_multiply, 5889, 5891, 5887);
  g->Dot(2096, 5892, YNN_INVALID_VALUE_ID, 5886, 1);
  g->DequantizeTensor(5886, YNN_INVALID_VALUE_ID, 5887, 5888);
  g->QuantizeTensor(5888, 8595, 5890, 2097);
  g->Dequantize(2097, 2098, 0.01586199924349785, 0);
  g->Unary(ynn_unary_square, 2098, 2099);
  g->Reduce(ynn_reduce_sum, 2099, 7738, {2}, true);
  g->ShapeProduct(2099, 7737, {2});
  g->Binary(ynn_binary_divide, 7738, 7737, 2100);
  g->Binary(ynn_binary_add, 2100, 8647, 2101);
  g->Unary(ynn_unary_rsqrt, 2101, 2103);
  g->Binary(ynn_binary_multiply, 2098, 2103, 2104);
  g->Binary(ynn_binary_multiply, 2104, 8985, 2105);
  g->Binary(ynn_binary_add, 2105, 2078, 2106);
}

// Scope: "Layer21 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 2107, {0,0,21,0}, {-1,-1,1,-1});
  g->Reshape(2107, 2108, {1,1,256});
  g->Unary(ynn_unary_square, 2108, 2109);
  g->Reduce(ynn_reduce_sum, 2109, 7740, {2}, true);
  g->ShapeProduct(2109, 7739, {2});
  g->Binary(ynn_binary_divide, 7740, 7739, 2110);
  g->Binary(ynn_binary_add, 2110, 8647, 2111);
  g->Unary(ynn_unary_rsqrt, 2111, 2112);
  g->Binary(ynn_binary_multiply, 2108, 2112, 2114);
  g->Binary(ynn_binary_multiply, 2114, 9401, 2115);
  g->Binary(ynn_binary_multiply, 9416, 8651, 2116);
  g->Binary(ynn_binary_add, 2115, 2116, 2117);
  g->Binary(ynn_binary_multiply, 2117, 8645, 2118);
  g->Quantize(2106, 2119, 0.18123431503772736, 0);
  g->Transpose(8982, 5899, {1,0});
  g->Binary(ynn_binary_multiply, 5896, 5898, 5894);
  g->Dot(2119, 5899, YNN_INVALID_VALUE_ID, 5893, 1);
  g->DequantizeTensor(5893, YNN_INVALID_VALUE_ID, 5894, 5895);
  g->QuantizeTensor(5895, 8595, 5897, 2120);
  g->Dequantize(2120, 2121, 0.10531497001647949, 0);
  g->Polynomial(2121, 7745, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7745, 7746);
  g->Binary(ynn_binary_add, 7746, 7161, 7743);
  g->Binary(ynn_binary_multiply, 2121, 7173, 7744);
  g->Binary(ynn_binary_multiply, 7744, 7743, 2122);
  g->Binary(ynn_binary_multiply, 2122, 2118, 2123);
  g->Quantize(2123, 2125, 0.22933071851730347, 0);
  g->Transpose(8983, 5906, {1,0});
  g->Binary(ynn_binary_multiply, 5903, 5905, 5901);
  g->Dot(2125, 5906, YNN_INVALID_VALUE_ID, 5900, 1);
  g->DequantizeTensor(5900, YNN_INVALID_VALUE_ID, 5901, 5902);
  g->QuantizeTensor(5902, 8595, 5904, 2126);
  g->Dequantize(2126, 2127, 0.1351429969072342, 0);
  g->Unary(ynn_unary_square, 2127, 2128);
  g->Reduce(ynn_reduce_sum, 2128, 7748, {2}, true);
  g->ShapeProduct(2128, 7747, {2});
  g->Binary(ynn_binary_divide, 7748, 7747, 2129);
  g->Binary(ynn_binary_add, 2129, 8647, 2130);
  g->Unary(ynn_unary_rsqrt, 2130, 2131);
  g->Binary(ynn_binary_multiply, 2127, 2131, 2132);
  g->Binary(ynn_binary_multiply, 2132, 8986, 2133);
  g->Binary(ynn_binary_add, 2106, 2133, 2134);
  g->Binary(ynn_binary_multiply, 2134, 8978, 2136);
}

// Scope: "Layer21"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21(Context& ctx) {
  BuildLayer21Attention(ctx);
  BuildLayer21Mlp(ctx);
  BuildLayer21PerLayerEmbedding(ctx);
}

// Scope: "Layer22 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(2142, 2143, 0.017071785405278206, 0);
  g->Transpose(9006, 5913, {1,0});
  g->Binary(ynn_binary_multiply, 5910, 5912, 5908);
  g->Dot(2143, 5913, YNN_INVALID_VALUE_ID, 5907, 1);
  g->DequantizeTensor(5907, YNN_INVALID_VALUE_ID, 5908, 5909);
  g->QuantizeTensor(5909, 8595, 5911, 2144);
  g->Dequantize(2144, 2145, 0.019808080047369003, 0);
  g->SplitDim(2145, 2147, 2, {2,256});
  g->Transpose(2147, 2148, {0,2,1,3});
  g->Unary(ynn_unary_square, 2148, 2149);
  g->Reduce(ynn_reduce_sum, 2149, 7752, {3}, true);
  g->ShapeProduct(2149, 7751, {3});
  g->Binary(ynn_binary_divide, 7752, 7751, 2150);
  g->Binary(ynn_binary_add, 2150, 8647, 2151);
  g->Unary(ynn_unary_rsqrt, 2151, 2152);
  g->Binary(ynn_binary_multiply, 2148, 2152, 2153);
  g->Binary(ynn_binary_multiply, 2153, 9005, 2154);
  g->Slice(2154, 2155, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2154, 2156, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2156, 2158);
  g->Concat({2158,2155}, 2159, 3);
  g->Binary(ynn_binary_multiply, 2154, 3141, 2160);
  g->Binary(ynn_binary_multiply, 2159, 4217, 2161);
  g->Binary(ynn_binary_add, 2160, 2161, 2162);
  g->Transpose(9010, 5918, {1,0});
  g->Binary(ynn_binary_multiply, 5910, 5917, 5915);
  g->Dot(2143, 5918, YNN_INVALID_VALUE_ID, 5914, 1);
  g->DequantizeTensor(5914, YNN_INVALID_VALUE_ID, 5915, 5916);
  g->QuantizeTensor(5916, 8595, 5911, 2163);
  g->Dequantize(2163, 2164, 0.019808080047369003, 0);
  g->SplitDim(2164, 2165, 2, {2,256});
  g->Transpose(2165, 2166, {0,2,1,3});
  g->Unary(ynn_unary_square, 2166, 2168);
  g->Reduce(ynn_reduce_sum, 2168, 7754, {3}, true);
  g->ShapeProduct(2168, 7753, {3});
  g->Binary(ynn_binary_divide, 7754, 7753, 2169);
  g->Binary(ynn_binary_add, 2169, 8647, 2170);
  g->Unary(ynn_unary_rsqrt, 2170, 2171);
  g->Binary(ynn_binary_multiply, 2166, 2171, 2172);
}

// Scope: "Layer22 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(2162, 2173, 0.0059552486054599285, 0);
  g->Append(8611, 2173, 9460, 2, s2, slinky::expr(int64_t{1}));
  g->View(9460, 9508, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(2172, 2174, 0.047244105488061905, 0);
  g->Append(8635, 2174, 9484, 2, s2, slinky::expr(int64_t{1}));
  g->View(9484, 9532, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer22 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(9009, 5924, {1,0});
  g->Binary(ynn_binary_multiply, 5910, 5923, 5920);
  g->Dot(2143, 5924, YNN_INVALID_VALUE_ID, 5919, 1);
  g->DequantizeTensor(5919, YNN_INVALID_VALUE_ID, 5920, 5921);
  g->QuantizeTensor(5921, 8595, 5922, 2176);
  g->Dequantize(2176, 2177, 0.0274360328912735, 0);
  g->SplitDim(2177, 2178, 2, {8,256});
  g->Transpose(2178, 2179, {0,2,1,3});
  g->Unary(ynn_unary_square, 2179, 2180);
  g->Reduce(ynn_reduce_sum, 2180, 7756, {3}, true);
  g->ShapeProduct(2180, 7755, {3});
  g->Binary(ynn_binary_divide, 7756, 7755, 2181);
  g->Binary(ynn_binary_add, 2181, 8647, 2182);
  g->Unary(ynn_unary_rsqrt, 2182, 2183);
  g->Binary(ynn_binary_multiply, 2179, 2183, 2186);
  g->Binary(ynn_binary_multiply, 2186, 9008, 2187);
  g->Slice(2187, 2188, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2187, 2189, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2189, 2190);
  g->Concat({2190,2188}, 2191, 3);
  g->Binary(ynn_binary_multiply, 2187, 3141, 2192);
  g->Binary(ynn_binary_multiply, 2191, 4217, 2193);
  g->Binary(ynn_binary_add, 2192, 2193, 2194);
}

// Scope: "Layer22 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9508, 2195, 0.0059552486054599285, 0);
  g->Dequantize(9532, 2197, 0.047244105488061905, 0);
  g->Slice(2194, 2198, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(2195, 2199, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(2197, 2200, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(2198, 2199, 2201, false, true);
  g->Mask(2201, 8682, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8682, 7760, {-1}, true);
  g->Binary(ynn_binary_subtract, 8682, 7760, 7757);
  g->Unary(ynn_unary_exp, 7757, 7758);
  g->Reduce(ynn_reduce_sum, 7758, 7761, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 7761, 7759);
  g->Binary(ynn_binary_multiply, 7758, 7759, 2202);
  g->Matmul(2202, 2200, 2203, false, false);
  g->Slice(2194, 2204, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(2195, 2205, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(2197, 2207, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(2204, 2205, 2208, false, true);
  g->Mask(2208, 8683, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8683, 7765, {-1}, true);
  g->Binary(ynn_binary_subtract, 8683, 7765, 7762);
  g->Unary(ynn_unary_exp, 7762, 7763);
  g->Reduce(ynn_reduce_sum, 7763, 7766, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 7766, 7764);
  g->Binary(ynn_binary_multiply, 7763, 7764, 2209);
  g->Matmul(2209, 2207, 2210, false, false);
  g->Concat({2203,2210}, 2211, 1);
}

// Scope: "Layer22 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(2211, 2212, {0,2,1,3});
  g->FuseDims(2212, 2213, 2, 2);
  g->Quantize(2213, 2214, 0.020915362983942032, 0);
  g->Transpose(9007, 5931, {1,0});
  g->Binary(ynn_binary_multiply, 5928, 5930, 5926);
  g->Dot(2214, 5931, YNN_INVALID_VALUE_ID, 5925, 1);
  g->DequantizeTensor(5925, YNN_INVALID_VALUE_ID, 5926, 5927);
  g->QuantizeTensor(5927, 8595, 5929, 2215);
  g->Dequantize(2215, 2217, 0.03860917314887047, 0);
}

// Scope: "Layer22 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2136, 2137);
  g->Reduce(ynn_reduce_sum, 2137, 7750, {2}, true);
  g->ShapeProduct(2137, 7749, {2});
  g->Binary(ynn_binary_divide, 7750, 7749, 2138);
  g->Binary(ynn_binary_add, 2138, 8647, 2139);
  g->Unary(ynn_unary_rsqrt, 2139, 2140);
  g->Binary(ynn_binary_multiply, 2136, 2140, 2141);
  g->Binary(ynn_binary_multiply, 2141, 8994, 2142);
  BuildLayer22AttentionKvProjection(ctx);
  BuildLayer22AttentionCacheUpdate(ctx);
  BuildLayer22AttentionQueryProjection(ctx);
  BuildLayer22AttentionSdpa(ctx);
  BuildLayer22AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2217, 2218);
  g->Reduce(ynn_reduce_sum, 2218, 7768, {2}, true);
  g->ShapeProduct(2218, 7767, {2});
  g->Binary(ynn_binary_divide, 7768, 7767, 2219);
  g->Binary(ynn_binary_add, 2219, 8647, 2220);
  g->Unary(ynn_unary_rsqrt, 2220, 2221);
  g->Binary(ynn_binary_multiply, 2217, 2221, 2222);
  g->Binary(ynn_binary_multiply, 2222, 9001, 2223);
  g->Binary(ynn_binary_add, 2223, 2136, 2224);
}

// Scope: "Layer22 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2224, 2225);
  g->Reduce(ynn_reduce_sum, 2225, 7770, {2}, true);
  g->ShapeProduct(2225, 7769, {2});
  g->Binary(ynn_binary_divide, 7770, 7769, 2226);
  g->Binary(ynn_binary_add, 2226, 8647, 2228);
  g->Unary(ynn_unary_rsqrt, 2228, 2229);
  g->Binary(ynn_binary_multiply, 2224, 2229, 2230);
  g->Binary(ynn_binary_multiply, 2230, 9004, 2231);
  g->Quantize(2231, 2232, 0.014675655402243137, 0);
  g->Transpose(8998, 5938, {1,0});
  g->Binary(ynn_binary_multiply, 5935, 5937, 5933);
  g->Dot(2232, 5938, YNN_INVALID_VALUE_ID, 5932, 1);
  g->DequantizeTensor(5932, YNN_INVALID_VALUE_ID, 5933, 5934);
  g->QuantizeTensor(5934, 8595, 5936, 2233);
  g->Dequantize(2233, 2234, 0.017593514174222946, 0);
  g->Transpose(8997, 5943, {1,0});
  g->Binary(ynn_binary_multiply, 5935, 5942, 5940);
  g->Dot(2232, 5943, YNN_INVALID_VALUE_ID, 5939, 1);
  g->DequantizeTensor(5939, YNN_INVALID_VALUE_ID, 5940, 5941);
  g->QuantizeTensor(5941, 8595, 5936, 2235);
  g->Dequantize(2235, 2236, 0.017593514174222946, 0);
  g->Polynomial(2236, 7773, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7773, 7774);
  g->Binary(ynn_binary_add, 7774, 7161, 7771);
  g->Binary(ynn_binary_multiply, 2236, 7173, 7772);
  g->Binary(ynn_binary_multiply, 7772, 7771, 2237);
  g->Binary(ynn_binary_multiply, 2234, 2237, 2238);
  g->Quantize(2238, 2239, 0.009842529892921448, 0);
  g->Transpose(8996, 5950, {1,0});
  g->Binary(ynn_binary_multiply, 5947, 5949, 5945);
  g->Dot(2239, 5950, YNN_INVALID_VALUE_ID, 5944, 1);
  g->DequantizeTensor(5944, YNN_INVALID_VALUE_ID, 5945, 5946);
  g->QuantizeTensor(5946, 8595, 5948, 2240);
  g->Dequantize(2240, 2241, 0.007876119576394558, 0);
  g->Unary(ynn_unary_square, 2241, 2242);
  g->Reduce(ynn_reduce_sum, 2242, 7776, {2}, true);
  g->ShapeProduct(2242, 7775, {2});
  g->Binary(ynn_binary_divide, 7776, 7775, 2243);
  g->Binary(ynn_binary_add, 2243, 8647, 2244);
  g->Unary(ynn_unary_rsqrt, 2244, 2245);
  g->Binary(ynn_binary_multiply, 2241, 2245, 2246);
  g->Binary(ynn_binary_multiply, 2246, 9002, 2248);
  g->Binary(ynn_binary_add, 2248, 2224, 2249);
}

// Scope: "Layer22 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 2250, {0,0,22,0}, {-1,-1,1,-1});
  g->Reshape(2250, 2251, {1,1,256});
  g->Unary(ynn_unary_square, 2251, 2252);
  g->Reduce(ynn_reduce_sum, 2252, 7778, {2}, true);
  g->ShapeProduct(2252, 7777, {2});
  g->Binary(ynn_binary_divide, 7778, 7777, 2253);
  g->Binary(ynn_binary_add, 2253, 8647, 2254);
  g->Unary(ynn_unary_rsqrt, 2254, 2255);
  g->Binary(ynn_binary_multiply, 2251, 2255, 2256);
  g->Binary(ynn_binary_multiply, 2256, 9401, 2257);
  g->Binary(ynn_binary_multiply, 9417, 8651, 2259);
  g->Binary(ynn_binary_add, 2257, 2259, 2260);
  g->Binary(ynn_binary_multiply, 2260, 8645, 2261);
  g->Quantize(2249, 2262, 0.28123560547828674, 0);
  g->Transpose(8999, 5962, {1,0});
  g->Binary(ynn_binary_multiply, 5959, 5961, 5957);
  g->Dot(2262, 5962, YNN_INVALID_VALUE_ID, 5956, 1);
  g->DequantizeTensor(5956, YNN_INVALID_VALUE_ID, 5957, 5958);
  g->QuantizeTensor(5958, 8595, 5960, 2263);
  g->Dequantize(2263, 2264, 0.5590550899505615, 0);
  g->Polynomial(2264, 7781, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7781, 7782);
  g->Binary(ynn_binary_add, 7782, 7161, 7779);
  g->Binary(ynn_binary_multiply, 2264, 7173, 7780);
  g->Binary(ynn_binary_multiply, 7780, 7779, 2265);
  g->Binary(ynn_binary_multiply, 2265, 2261, 2266);
  g->Quantize(2266, 2267, 0.6968504190444946, 0);
  g->Transpose(9000, 5969, {1,0});
  g->Binary(ynn_binary_multiply, 5966, 5968, 5964);
  g->Dot(2267, 5969, YNN_INVALID_VALUE_ID, 5963, 1);
  g->DequantizeTensor(5963, YNN_INVALID_VALUE_ID, 5964, 5965);
  g->QuantizeTensor(5965, 8595, 5967, 2268);
  g->Dequantize(2268, 2270, 0.38523077964782715, 0);
  g->Unary(ynn_unary_square, 2270, 2271);
  g->Reduce(ynn_reduce_sum, 2271, 7784, {2}, true);
  g->ShapeProduct(2271, 7783, {2});
  g->Binary(ynn_binary_divide, 7784, 7783, 2272);
  g->Binary(ynn_binary_add, 2272, 8647, 2273);
  g->Unary(ynn_unary_rsqrt, 2273, 2274);
  g->Binary(ynn_binary_multiply, 2270, 2274, 2275);
  g->Binary(ynn_binary_multiply, 2275, 9003, 2276);
  g->Binary(ynn_binary_add, 2249, 2276, 2277);
  g->Binary(ynn_binary_multiply, 2277, 8995, 2278);
}

// Scope: "Layer22"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22(Context& ctx) {
  BuildLayer22Attention(ctx);
  BuildLayer22Mlp(ctx);
  BuildLayer22PerLayerEmbedding(ctx);
}

// Scope: "Layer23 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(2285, 2286, 0.062325432896614075, 0);
  g->Transpose(9023, 5976, {1,0});
  g->Binary(ynn_binary_multiply, 5973, 5975, 5971);
  g->Dot(2286, 5976, YNN_INVALID_VALUE_ID, 5970, 1);
  g->DequantizeTensor(5970, YNN_INVALID_VALUE_ID, 5971, 5972);
  g->QuantizeTensor(5972, 8595, 5974, 2287);
  g->Dequantize(2287, 2288, 0.05413386970758438, 0);
  g->SplitDim(2288, 2289, 2, {2,512});
  g->Transpose(2289, 2290, {0,2,1,3});
  g->Unary(ynn_unary_square, 2290, 2293);
  g->Reduce(ynn_reduce_sum, 2293, 7788, {3}, true);
  g->ShapeProduct(2293, 7787, {3});
  g->Binary(ynn_binary_divide, 7788, 7787, 2294);
  g->Binary(ynn_binary_add, 2294, 8647, 2295);
  g->Unary(ynn_unary_rsqrt, 2295, 2296);
  g->Binary(ynn_binary_multiply, 2290, 2296, 2297);
  g->Binary(ynn_binary_multiply, 2297, 9022, 2298);
  g->Slice(2298, 2299, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(2298, 2300, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 2300, 2301);
  g->Concat({2301,2299}, 2302, 3);
  g->Binary(ynn_binary_multiply, 2298, 4830, 2304);
  g->Binary(ynn_binary_multiply, 2302, 2, 2305);
  g->Binary(ynn_binary_add, 2304, 2305, 2306);
  g->Transpose(9027, 5981, {1,0});
  g->Binary(ynn_binary_multiply, 5973, 5980, 5978);
  g->Dot(2286, 5981, YNN_INVALID_VALUE_ID, 5977, 1);
  g->DequantizeTensor(5977, YNN_INVALID_VALUE_ID, 5978, 5979);
  g->QuantizeTensor(5979, 8595, 5974, 2307);
  g->Dequantize(2307, 2308, 0.05413386970758438, 0);
  g->SplitDim(2308, 2309, 2, {2,512});
  g->Transpose(2309, 2310, {0,2,1,3});
  g->Unary(ynn_unary_square, 2310, 2311);
  g->Reduce(ynn_reduce_sum, 2311, 7792, {3}, true);
  g->ShapeProduct(2311, 7791, {3});
  g->Binary(ynn_binary_divide, 7792, 7791, 2312);
  g->Binary(ynn_binary_add, 2312, 8647, 2314);
  g->Unary(ynn_unary_rsqrt, 2314, 2315);
  g->Binary(ynn_binary_multiply, 2310, 2315, 2316);
}

// Scope: "Layer23 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(2306, 2317, 0.001091228099539876, 0);
  g->Append(8612, 2317, 9461, 2, s2, slinky::expr(int64_t{1}));
  g->View(9461, 9509, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(2316, 2318, 0.01785714365541935, 0);
  g->Append(8636, 2318, 9485, 2, s2, slinky::expr(int64_t{1}));
  g->View(9485, 9533, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer23 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(9026, 5987, {1,0});
  g->Binary(ynn_binary_multiply, 5973, 5986, 5983);
  g->Dot(2286, 5987, YNN_INVALID_VALUE_ID, 5982, 1);
  g->DequantizeTensor(5982, YNN_INVALID_VALUE_ID, 5983, 5984);
  g->QuantizeTensor(5984, 8595, 5985, 2320);
  g->Dequantize(2320, 2321, 0.08661418408155441, 0);
  g->SplitDim(2321, 2322, 2, {8,512});
  g->Transpose(2322, 2323, {0,2,1,3});
  g->Unary(ynn_unary_square, 2323, 2324);
  g->Reduce(ynn_reduce_sum, 2324, 7794, {3}, true);
  g->ShapeProduct(2324, 7793, {3});
  g->Binary(ynn_binary_divide, 7794, 7793, 2325);
  g->Binary(ynn_binary_add, 2325, 8647, 2326);
  g->Unary(ynn_unary_rsqrt, 2326, 2327);
  g->Binary(ynn_binary_multiply, 2323, 2327, 2328);
  g->Binary(ynn_binary_multiply, 2328, 9025, 2329);
  g->Slice(2329, 2331, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(2329, 2332, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 2332, 2333);
  g->Concat({2333,2331}, 2334, 3);
  g->Binary(ynn_binary_multiply, 2329, 4830, 2335);
  g->Binary(ynn_binary_multiply, 2334, 2, 2336);
  g->Binary(ynn_binary_add, 2335, 2336, 2337);
}

// Scope: "Layer23 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9509, 2338, 0.001091228099539876, 0);
  g->Dequantize(9533, 2339, 0.01785714365541935, 0);
  g->Slice(2337, 2340, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(2338, 2342, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(2339, 2343, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(2340, 2342, 2344, false, true);
  g->Mask(2344, 8684, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 8684, 7798, {-1}, true);
  g->Binary(ynn_binary_subtract, 8684, 7798, 7795);
  g->Unary(ynn_unary_exp, 7795, 7796);
  g->Reduce(ynn_reduce_sum, 7796, 7799, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 7799, 7797);
  g->Binary(ynn_binary_multiply, 7796, 7797, 2345);
  g->Matmul(2345, 2343, 2346, false, false);
  g->Slice(2337, 2347, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(2338, 2348, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(2339, 2349, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(2347, 2348, 2350, false, true);
  g->Mask(2350, 8685, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 8685, 7803, {-1}, true);
  g->Binary(ynn_binary_subtract, 8685, 7803, 7800);
  g->Unary(ynn_unary_exp, 7800, 7801);
  g->Reduce(ynn_reduce_sum, 7801, 7804, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 7804, 7802);
  g->Binary(ynn_binary_multiply, 7801, 7802, 2351);
  g->Matmul(2351, 2349, 2352, false, false);
  g->Concat({2346,2352}, 2353, 1);
}

// Scope: "Layer23 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(2353, 2354, {0,2,1,3});
  g->FuseDims(2354, 2355, 2, 2);
  g->Quantize(2355, 2356, 0.01734744943678379, 0);
  g->Transpose(9024, 5994, {1,0});
  g->Binary(ynn_binary_multiply, 5991, 5993, 5989);
  g->Dot(2356, 5994, YNN_INVALID_VALUE_ID, 5988, 1);
  g->DequantizeTensor(5988, YNN_INVALID_VALUE_ID, 5989, 5990);
  g->QuantizeTensor(5990, 8595, 5992, 2357);
  g->Dequantize(2357, 2358, 0.03438705950975418, 0);
}

// Scope: "Layer23 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2278, 2279);
  g->Reduce(ynn_reduce_sum, 2279, 7786, {2}, true);
  g->ShapeProduct(2279, 7785, {2});
  g->Binary(ynn_binary_divide, 7786, 7785, 2281);
  g->Binary(ynn_binary_add, 2281, 8647, 2282);
  g->Unary(ynn_unary_rsqrt, 2282, 2283);
  g->Binary(ynn_binary_multiply, 2278, 2283, 2284);
  g->Binary(ynn_binary_multiply, 2284, 9011, 2285);
  BuildLayer23AttentionKvProjection(ctx);
  BuildLayer23AttentionCacheUpdate(ctx);
  BuildLayer23AttentionQueryProjection(ctx);
  BuildLayer23AttentionSdpa(ctx);
  BuildLayer23AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2358, 2359);
  g->Reduce(ynn_reduce_sum, 2359, 7806, {2}, true);
  g->ShapeProduct(2359, 7805, {2});
  g->Binary(ynn_binary_divide, 7806, 7805, 2360);
  g->Binary(ynn_binary_add, 2360, 8647, 2361);
  g->Unary(ynn_unary_rsqrt, 2361, 2362);
  g->Binary(ynn_binary_multiply, 2358, 2362, 2363);
  g->Binary(ynn_binary_multiply, 2363, 9018, 2364);
  g->Binary(ynn_binary_add, 2364, 2278, 2365);
}

// Scope: "Layer23 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2365, 2366);
  g->Reduce(ynn_reduce_sum, 2366, 7808, {2}, true);
  g->ShapeProduct(2366, 7807, {2});
  g->Binary(ynn_binary_divide, 7808, 7807, 2367);
  g->Binary(ynn_binary_add, 2367, 8647, 2368);
  g->Unary(ynn_unary_rsqrt, 2368, 2369);
  g->Binary(ynn_binary_multiply, 2365, 2369, 2371);
  g->Binary(ynn_binary_multiply, 2371, 9021, 2372);
  g->Quantize(2372, 2373, 0.01334653701633215, 0);
  g->Transpose(9015, 6001, {1,0});
  g->Binary(ynn_binary_multiply, 5998, 6000, 5996);
  g->Dot(2373, 6001, YNN_INVALID_VALUE_ID, 5995, 1);
  g->DequantizeTensor(5995, YNN_INVALID_VALUE_ID, 5996, 5997);
  g->QuantizeTensor(5997, 8595, 5999, 2374);
  g->Dequantize(2374, 2375, 0.01660926081240177, 0);
  g->Transpose(9014, 6006, {1,0});
  g->Binary(ynn_binary_multiply, 5998, 6005, 6003);
  g->Dot(2373, 6006, YNN_INVALID_VALUE_ID, 6002, 1);
  g->DequantizeTensor(6002, YNN_INVALID_VALUE_ID, 6003, 6004);
  g->QuantizeTensor(6004, 8595, 5999, 2376);
  g->Dequantize(2376, 2377, 0.01660926081240177, 0);
  g->Polynomial(2377, 7811, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7811, 7812);
  g->Binary(ynn_binary_add, 7812, 7161, 7809);
  g->Binary(ynn_binary_multiply, 2377, 7173, 7810);
  g->Binary(ynn_binary_multiply, 7810, 7809, 2378);
  g->Binary(ynn_binary_multiply, 2375, 2378, 2379);
  g->Quantize(2379, 2380, 0.015625009313225746, 0);
  g->Transpose(9013, 6013, {1,0});
  g->Binary(ynn_binary_multiply, 6010, 6012, 6008);
  g->Dot(2380, 6013, YNN_INVALID_VALUE_ID, 6007, 1);
  g->DequantizeTensor(6007, YNN_INVALID_VALUE_ID, 6008, 6009);
  g->QuantizeTensor(6009, 8595, 6011, 2381);
  g->Dequantize(2381, 2382, 0.011555495671927929, 0);
  g->Unary(ynn_unary_square, 2382, 2383);
  g->Reduce(ynn_reduce_sum, 2383, 7814, {2}, true);
  g->ShapeProduct(2383, 7813, {2});
  g->Binary(ynn_binary_divide, 7814, 7813, 2384);
  g->Binary(ynn_binary_add, 2384, 8647, 2385);
  g->Unary(ynn_unary_rsqrt, 2385, 2386);
  g->Binary(ynn_binary_multiply, 2382, 2386, 2387);
  g->Binary(ynn_binary_multiply, 2387, 9019, 2388);
  g->Binary(ynn_binary_add, 2388, 2365, 2389);
}

// Scope: "Layer23 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 2391, {0,0,23,0}, {-1,-1,1,-1});
  g->Reshape(2391, 2392, {1,1,256});
  g->Unary(ynn_unary_square, 2392, 2393);
  g->Reduce(ynn_reduce_sum, 2393, 7816, {2}, true);
  g->ShapeProduct(2393, 7815, {2});
  g->Binary(ynn_binary_divide, 7816, 7815, 2394);
  g->Binary(ynn_binary_add, 2394, 8647, 2395);
  g->Unary(ynn_unary_rsqrt, 2395, 2396);
  g->Binary(ynn_binary_multiply, 2392, 2396, 2397);
  g->Binary(ynn_binary_multiply, 2397, 9401, 2398);
  g->Binary(ynn_binary_multiply, 9418, 8651, 2399);
  g->Binary(ynn_binary_add, 2398, 2399, 2400);
  g->Binary(ynn_binary_multiply, 2400, 8645, 2401);
  g->Quantize(2389, 2402, 1.4053089618682861, 0);
  g->Transpose(9016, 6020, {1,0});
  g->Binary(ynn_binary_multiply, 6017, 6019, 6015);
  g->Dot(2402, 6020, YNN_INVALID_VALUE_ID, 6014, 1);
  g->DequantizeTensor(6014, YNN_INVALID_VALUE_ID, 6015, 6016);
  g->QuantizeTensor(6016, 8595, 6018, 2403);
  g->Dequantize(2403, 2404, 0.08169291913509369, 0);
  g->Polynomial(2404, 7819, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7819, 7820);
  g->Binary(ynn_binary_add, 7820, 7161, 7817);
  g->Binary(ynn_binary_multiply, 2404, 7173, 7818);
  g->Binary(ynn_binary_multiply, 7818, 7817, 2405);
  g->Binary(ynn_binary_multiply, 2405, 2401, 2406);
  g->Quantize(2406, 2407, 0.29921260476112366, 0);
  g->Transpose(9017, 6027, {1,0});
  g->Binary(ynn_binary_multiply, 6024, 6026, 6022);
  g->Dot(2407, 6027, YNN_INVALID_VALUE_ID, 6021, 1);
  g->DequantizeTensor(6021, YNN_INVALID_VALUE_ID, 6022, 6023);
  g->QuantizeTensor(6023, 8595, 6025, 2408);
  g->Dequantize(2408, 2409, 0.09225650876760483, 0);
  g->Unary(ynn_unary_square, 2409, 2410);
  g->Reduce(ynn_reduce_sum, 2410, 7822, {2}, true);
  g->ShapeProduct(2410, 7821, {2});
  g->Binary(ynn_binary_divide, 7822, 7821, 2412);
  g->Binary(ynn_binary_add, 2412, 8647, 2413);
  g->Unary(ynn_unary_rsqrt, 2413, 2414);
  g->Binary(ynn_binary_multiply, 2409, 2414, 2415);
  g->Binary(ynn_binary_multiply, 2415, 9020, 2416);
  g->Binary(ynn_binary_add, 2389, 2416, 2417);
  g->Binary(ynn_binary_multiply, 2417, 9012, 2418);
}

// Scope: "Layer23"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23(Context& ctx) {
  BuildLayer23Attention(ctx);
  BuildLayer23Mlp(ctx);
  BuildLayer23PerLayerEmbedding(ctx);
}

// Scope: "Layer24 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer24AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(2425, 2426, 0.2720024883747101, 0);
  g->Transpose(9041, 6040, {1,0});
  g->Binary(ynn_binary_multiply, 6037, 6039, 6035);
  g->Dot(2426, 6040, YNN_INVALID_VALUE_ID, 6034, 1);
  g->DequantizeTensor(6034, YNN_INVALID_VALUE_ID, 6035, 6036);
  g->QuantizeTensor(6036, 8595, 6038, 2427);
  g->Dequantize(2427, 2428, 0.3169291317462921, 0);
  g->SplitDim(2428, 2429, 2, {8,256});
  g->Transpose(2429, 2430, {0,2,1,3});
  g->Unary(ynn_unary_square, 2430, 2431);
  g->Reduce(ynn_reduce_sum, 2431, 7826, {3}, true);
  g->ShapeProduct(2431, 7825, {3});
  g->Binary(ynn_binary_divide, 7826, 7825, 2432);
  g->Binary(ynn_binary_add, 2432, 8647, 2434);
  g->Unary(ynn_unary_rsqrt, 2434, 2435);
  g->Binary(ynn_binary_multiply, 2430, 2435, 2436);
  g->Binary(ynn_binary_multiply, 2436, 9040, 2437);
  g->Slice(2437, 2438, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2437, 2439, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2439, 2440);
  g->Concat({2440,2438}, 2441, 3);
  g->Binary(ynn_binary_multiply, 2437, 3141, 2442);
  g->Binary(ynn_binary_multiply, 2441, 4217, 2443);
  g->Binary(ynn_binary_add, 2442, 2443, 2445);
}

// Scope: "Layer24 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer24AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9508, 2446, 0.0059552486054599285, 0);
  g->Dequantize(9532, 2447, 0.047244105488061905, 0);
  g->Slice(2445, 2448, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(2446, 2449, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(2447, 2450, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(2448, 2449, 2451, false, true);
  g->Mask(2451, 8686, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8686, 7830, {-1}, true);
  g->Binary(ynn_binary_subtract, 8686, 7830, 7827);
  g->Unary(ynn_unary_exp, 7827, 7828);
  g->Reduce(ynn_reduce_sum, 7828, 7831, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 7831, 7829);
  g->Binary(ynn_binary_multiply, 7828, 7829, 2452);
  g->Matmul(2452, 2450, 2453, false, false);
  g->Slice(2445, 2455, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(2446, 2456, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(2447, 2457, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(2455, 2456, 2458, false, true);
  g->Mask(2458, 8687, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8687, 7835, {-1}, true);
  g->Binary(ynn_binary_subtract, 8687, 7835, 7832);
  g->Unary(ynn_unary_exp, 7832, 7833);
  g->Reduce(ynn_reduce_sum, 7833, 7836, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 7836, 7834);
  g->Binary(ynn_binary_multiply, 7833, 7834, 2459);
  g->Matmul(2459, 2457, 2460, false, false);
  g->Concat({2453,2460}, 2461, 1);
}

// Scope: "Layer24 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer24AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(2461, 2462, {0,2,1,3});
  g->FuseDims(2462, 2463, 2, 2);
  g->Quantize(2463, 2465, 0.020177174359560013, 0);
  g->Transpose(9039, 6047, {1,0});
  g->Binary(ynn_binary_multiply, 6044, 6046, 6042);
  g->Dot(2465, 6047, YNN_INVALID_VALUE_ID, 6041, 1);
  g->DequantizeTensor(6041, YNN_INVALID_VALUE_ID, 6042, 6043);
  g->QuantizeTensor(6043, 8595, 6045, 2466);
  g->Dequantize(2466, 2467, 0.06057490408420563, 0);
}

// Scope: "Layer24 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer24Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2418, 2419);
  g->Reduce(ynn_reduce_sum, 2419, 7824, {2}, true);
  g->ShapeProduct(2419, 7823, {2});
  g->Binary(ynn_binary_divide, 7824, 7823, 2420);
  g->Binary(ynn_binary_add, 2420, 8647, 2421);
  g->Unary(ynn_unary_rsqrt, 2421, 2423);
  g->Binary(ynn_binary_multiply, 2418, 2423, 2424);
  g->Binary(ynn_binary_multiply, 2424, 9028, 2425);
  BuildLayer24AttentionQueryProjection(ctx);
  BuildLayer24AttentionSdpa(ctx);
  BuildLayer24AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2467, 2468);
  g->Reduce(ynn_reduce_sum, 2468, 7840, {2}, true);
  g->ShapeProduct(2468, 7839, {2});
  g->Binary(ynn_binary_divide, 7840, 7839, 2469);
  g->Binary(ynn_binary_add, 2469, 8647, 2470);
  g->Unary(ynn_unary_rsqrt, 2470, 2471);
  g->Binary(ynn_binary_multiply, 2467, 2471, 2472);
  g->Binary(ynn_binary_multiply, 2472, 9035, 2473);
  g->Binary(ynn_binary_add, 2473, 2418, 2474);
}

// Scope: "Layer24 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer24Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2474, 2476);
  g->Reduce(ynn_reduce_sum, 2476, 7842, {2}, true);
  g->ShapeProduct(2476, 7841, {2});
  g->Binary(ynn_binary_divide, 7842, 7841, 2477);
  g->Binary(ynn_binary_add, 2477, 8647, 2478);
  g->Unary(ynn_unary_rsqrt, 2478, 2479);
  g->Binary(ynn_binary_multiply, 2474, 2479, 2480);
  g->Binary(ynn_binary_multiply, 2480, 9038, 2481);
  g->Quantize(2481, 2482, 0.018166832625865936, 0);
  g->Transpose(9032, 6054, {1,0});
  g->Binary(ynn_binary_multiply, 6051, 6053, 6049);
  g->Dot(2482, 6054, YNN_INVALID_VALUE_ID, 6048, 1);
  g->DequantizeTensor(6048, YNN_INVALID_VALUE_ID, 6049, 6050);
  g->QuantizeTensor(6050, 8595, 6052, 2483);
  g->Dequantize(2483, 2484, 0.017224417999386787, 0);
  g->Transpose(9031, 6059, {1,0});
  g->Binary(ynn_binary_multiply, 6051, 6058, 6056);
  g->Dot(2482, 6059, YNN_INVALID_VALUE_ID, 6055, 1);
  g->DequantizeTensor(6055, YNN_INVALID_VALUE_ID, 6056, 6057);
  g->QuantizeTensor(6057, 8595, 6052, 2486);
  g->Dequantize(2486, 2487, 0.017224417999386787, 0);
  g->Polynomial(2487, 7845, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7845, 7846);
  g->Binary(ynn_binary_add, 7846, 7161, 7843);
  g->Binary(ynn_binary_multiply, 2487, 7173, 7844);
  g->Binary(ynn_binary_multiply, 7844, 7843, 2488);
  g->Binary(ynn_binary_multiply, 2484, 2488, 2489);
  g->Quantize(2489, 2490, 0.01697835512459278, 0);
  g->Transpose(9030, 6066, {1,0});
  g->Binary(ynn_binary_multiply, 6063, 6065, 6061);
  g->Dot(2490, 6066, YNN_INVALID_VALUE_ID, 6060, 1);
  g->DequantizeTensor(6060, YNN_INVALID_VALUE_ID, 6061, 6062);
  g->QuantizeTensor(6062, 8595, 6064, 2491);
  g->Dequantize(2491, 2492, 0.010266699828207493, 0);
  g->Unary(ynn_unary_square, 2492, 2493);
  g->Reduce(ynn_reduce_sum, 2493, 7848, {2}, true);
  g->ShapeProduct(2493, 7847, {2});
  g->Binary(ynn_binary_divide, 7848, 7847, 2494);
  g->Binary(ynn_binary_add, 2494, 8647, 2495);
  g->Unary(ynn_unary_rsqrt, 2495, 2498);
  g->Binary(ynn_binary_multiply, 2492, 2498, 2499);
  g->Binary(ynn_binary_multiply, 2499, 9036, 2500);
  g->Binary(ynn_binary_add, 2500, 2474, 2501);
}

// Scope: "Layer24 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer24PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 2502, {0,0,24,0}, {-1,-1,1,-1});
  g->Reshape(2502, 2503, {1,1,256});
  g->Unary(ynn_unary_square, 2503, 2504);
  g->Reduce(ynn_reduce_sum, 2504, 7850, {2}, true);
  g->ShapeProduct(2504, 7849, {2});
  g->Binary(ynn_binary_divide, 7850, 7849, 2505);
  g->Binary(ynn_binary_add, 2505, 8647, 2506);
  g->Unary(ynn_unary_rsqrt, 2506, 2507);
  g->Binary(ynn_binary_multiply, 2503, 2507, 2509);
  g->Binary(ynn_binary_multiply, 2509, 9401, 2510);
  g->Binary(ynn_binary_multiply, 9419, 8651, 2511);
  g->Binary(ynn_binary_add, 2510, 2511, 2512);
  g->Binary(ynn_binary_multiply, 2512, 8645, 2513);
  g->Quantize(2501, 2514, 0.23872995376586914, 0);
  g->Transpose(9033, 6073, {1,0});
  g->Binary(ynn_binary_multiply, 6070, 6072, 6068);
  g->Dot(2514, 6073, YNN_INVALID_VALUE_ID, 6067, 1);
  g->DequantizeTensor(6067, YNN_INVALID_VALUE_ID, 6068, 6069);
  g->QuantizeTensor(6069, 8595, 6071, 2515);
  g->Dequantize(2515, 2516, 0.22736221551895142, 0);
  g->Polynomial(2516, 7853, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7853, 7854);
  g->Binary(ynn_binary_add, 7854, 7161, 7851);
  g->Binary(ynn_binary_multiply, 2516, 7173, 7852);
  g->Binary(ynn_binary_multiply, 7852, 7851, 2517);
  g->Binary(ynn_binary_multiply, 2517, 2513, 2518);
  g->Quantize(2518, 2520, 2.0629920959472656, 0);
  g->Transpose(9034, 6080, {1,0});
  g->Binary(ynn_binary_multiply, 6077, 6079, 6075);
  g->Dot(2520, 6080, YNN_INVALID_VALUE_ID, 6074, 1);
  g->DequantizeTensor(6074, YNN_INVALID_VALUE_ID, 6075, 6076);
  g->QuantizeTensor(6076, 8595, 6078, 2521);
  g->Dequantize(2521, 2522, 0.26288625597953796, 0);
  g->Unary(ynn_unary_square, 2522, 2523);
  g->Reduce(ynn_reduce_sum, 2523, 7856, {2}, true);
  g->ShapeProduct(2523, 7855, {2});
  g->Binary(ynn_binary_divide, 7856, 7855, 2524);
  g->Binary(ynn_binary_add, 2524, 8647, 2525);
  g->Unary(ynn_unary_rsqrt, 2525, 2526);
  g->Binary(ynn_binary_multiply, 2522, 2526, 2527);
  g->Binary(ynn_binary_multiply, 2527, 9037, 2528);
  g->Binary(ynn_binary_add, 2501, 2528, 2529);
  g->Binary(ynn_binary_multiply, 2529, 9029, 2531);
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
  g->Quantize(2537, 2538, 0.38746458292007446, 0);
  g->Transpose(9055, 6087, {1,0});
  g->Binary(ynn_binary_multiply, 6084, 6086, 6082);
  g->Dot(2538, 6087, YNN_INVALID_VALUE_ID, 6081, 1);
  g->DequantizeTensor(6081, YNN_INVALID_VALUE_ID, 6082, 6083);
  g->QuantizeTensor(6083, 8595, 6085, 2539);
  g->Dequantize(2539, 2540, 0.5039370059967041, 0);
  g->SplitDim(2540, 2542, 2, {8,256});
  g->Transpose(2542, 2543, {0,2,1,3});
  g->Unary(ynn_unary_square, 2543, 2544);
  g->Reduce(ynn_reduce_sum, 2544, 7860, {3}, true);
  g->ShapeProduct(2544, 7859, {3});
  g->Binary(ynn_binary_divide, 7860, 7859, 2545);
  g->Binary(ynn_binary_add, 2545, 8647, 2546);
  g->Unary(ynn_unary_rsqrt, 2546, 2547);
  g->Binary(ynn_binary_multiply, 2543, 2547, 2548);
  g->Binary(ynn_binary_multiply, 2548, 9054, 2549);
  g->Slice(2549, 2550, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2549, 2551, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2551, 2553);
  g->Concat({2553,2550}, 2554, 3);
  g->Binary(ynn_binary_multiply, 2549, 3141, 2555);
  g->Binary(ynn_binary_multiply, 2554, 4217, 2556);
  g->Binary(ynn_binary_add, 2555, 2556, 2557);
}

// Scope: "Layer25 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer25AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9508, 2558, 0.0059552486054599285, 0);
  g->Dequantize(9532, 2559, 0.047244105488061905, 0);
  g->Slice(2557, 2560, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(2558, 2561, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(2559, 2562, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(2560, 2561, 2564, false, true);
  g->Mask(2564, 8688, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8688, 7864, {-1}, true);
  g->Binary(ynn_binary_subtract, 8688, 7864, 7861);
  g->Unary(ynn_unary_exp, 7861, 7862);
  g->Reduce(ynn_reduce_sum, 7862, 7865, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 7865, 7863);
  g->Binary(ynn_binary_multiply, 7862, 7863, 2565);
  g->Matmul(2565, 2562, 2566, false, false);
  g->Slice(2557, 2567, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(2558, 2568, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(2559, 2569, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(2567, 2568, 2570, false, true);
  g->Mask(2570, 8689, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8689, 7869, {-1}, true);
  g->Binary(ynn_binary_subtract, 8689, 7869, 7866);
  g->Unary(ynn_unary_exp, 7866, 7867);
  g->Reduce(ynn_reduce_sum, 7867, 7870, {-1}, true);
  g->Binary(ynn_binary_divide, 7161, 7870, 7868);
  g->Binary(ynn_binary_multiply, 7867, 7868, 2571);
  g->Matmul(2571, 2569, 2573, false, false);
  g->Concat({2566,2573}, 2574, 1);
}

// Scope: "Layer25 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer25AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(2574, 2575, {0,2,1,3});
  g->FuseDims(2575, 2576, 2, 2);
  g->Quantize(2576, 2577, 0.01894685998558998, 0);
  g->Transpose(9053, 6094, {1,0});
  g->Binary(ynn_binary_multiply, 6091, 6093, 6089);
  g->Dot(2577, 6094, YNN_INVALID_VALUE_ID, 6088, 1);
  g->DequantizeTensor(6088, YNN_INVALID_VALUE_ID, 6089, 6090);
  g->QuantizeTensor(6090, 8595, 6092, 2578);
  g->Dequantize(2578, 2579, 0.04775450751185417, 0);
}

// Scope: "Layer25 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer25Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2531, 2532);
  g->Reduce(ynn_reduce_sum, 2532, 7858, {2}, true);
  g->ShapeProduct(2532, 7857, {2});
  g->Binary(ynn_binary_divide, 7858, 7857, 2533);
  g->Binary(ynn_binary_add, 2533, 8647, 2534);
  g->Unary(ynn_unary_rsqrt, 2534, 2535);
  g->Binary(ynn_binary_multiply, 2531, 2535, 2536);
  g->Binary(ynn_binary_multiply, 2536, 9042, 2537);
  BuildLayer25AttentionQueryProjection(ctx);
  BuildLayer25AttentionSdpa(ctx);
  BuildLayer25AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2579, 2580);
  g->Reduce(ynn_reduce_sum, 2580, 7872, {2}, true);
  g->ShapeProduct(2580, 7871, {2});
  g->Binary(ynn_binary_divide, 7872, 7871, 2581);
  g->Binary(ynn_binary_add, 2581, 8647, 2582);
  g->Unary(ynn_unary_rsqrt, 2582, 2584);
  g->Binary(ynn_binary_multiply, 2579, 2584, 2585);
  g->Binary(ynn_binary_multiply, 2585, 9049, 2586);
  g->Binary(ynn_binary_add, 2586, 2531, 2587);
}

// Scope: "Layer25 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer25Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2587, 2588);
  g->Reduce(ynn_reduce_sum, 2588, 7874, {2}, true);
  g->ShapeProduct(2588, 7873, {2});
  g->Binary(ynn_binary_divide, 7874, 7873, 2589);
  g->Binary(ynn_binary_add, 2589, 8647, 2590);
  g->Unary(ynn_unary_rsqrt, 2590, 2591);
  g->Binary(ynn_binary_multiply, 2587, 2591, 2592);
  g->Binary(ynn_binary_multiply, 2592, 9052, 2593);
  g->Quantize(2593, 2595, 0.012911376543343067, 0);
  g->Transpose(9046, 6101, {1,0});
  g->Binary(ynn_binary_multiply, 6098, 6100, 6096);
  g->Dot(2595, 6101, YNN_INVALID_VALUE_ID, 6095, 1);
  g->DequantizeTensor(6095, YNN_INVALID_VALUE_ID, 6096, 6097);
  g->QuantizeTensor(6097, 8595, 6099, 2596);
  g->Dequantize(2596, 2597, 0.015132884494960308, 0);
  g->Transpose(9045, 6106, {1,0});
  g->Binary(ynn_binary_multiply, 6098, 6105, 6103);
  g->Dot(2595, 6106, YNN_INVALID_VALUE_ID, 6102, 1);
  g->DequantizeTensor(6102, YNN_INVALID_VALUE_ID, 6103, 6104);
  g->QuantizeTensor(6104, 8595, 6099, 2598);
  g->Dequantize(2598, 2599, 0.015132884494960308, 0);
  g->Polynomial(2599, 7877, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7877, 7878);
  g->Binary(ynn_binary_add, 7878, 7161, 7875);
  g->Binary(ynn_binary_multiply, 2599, 7173, 7876);
  g->Binary(ynn_binary_multiply, 7876, 7875, 2600);
  g->Binary(ynn_binary_multiply, 2597, 2600, 2601);
  g->Quantize(2601, 2602, 0.015501978807151318, 0);
  g->Transpose(9044, 6113, {1,0});
  g->Binary(ynn_binary_multiply, 6110, 6112, 6108);
  g->Dot(2602, 6113, YNN_INVALID_VALUE_ID, 6107, 1);
  g->DequantizeTensor(6107, YNN_INVALID_VALUE_ID, 6108, 6109);
  g->QuantizeTensor(6109, 8595, 6111, 2603);
  g->Dequantize(2603, 2606, 0.009047985076904297, 0);
  g->Unary(ynn_unary_square, 2606, 2607);
  g->Reduce(ynn_reduce_sum, 2607, 7880, {2}, true);
  g->ShapeProduct(2607, 7879, {2});
  g->Binary(ynn_binary_divide, 7880, 7879, 2608);
  g->Binary(ynn_binary_add, 2608, 8647, 2609);
  g->Unary(ynn_unary_rsqrt, 2609, 2610);
  g->Binary(ynn_binary_multiply, 2606, 2610, 2611);
  g->Binary(ynn_binary_multiply, 2611, 9050, 2612);
  g->Binary(ynn_binary_add, 2612, 2587, 2613);
}

// Scope: "Layer25 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer25PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 2614, {0,0,25,0}, {-1,-1,1,-1});
  g->Reshape(2614, 2615, {1,1,256});
  g->Unary(ynn_unary_square, 2615, 2617);
  g->Reduce(ynn_reduce_sum, 2617, 7882, {2}, true);
  g->ShapeProduct(2617, 7881, {2});
  g->Binary(ynn_binary_divide, 7882, 7881, 2618);
  g->Binary(ynn_binary_add, 2618, 8647, 2619);
  g->Unary(ynn_unary_rsqrt, 2619, 2620);
  g->Binary(ynn_binary_multiply, 2615, 2620, 2621);
  g->Binary(ynn_binary_multiply, 2621, 9401, 2622);
  g->Binary(ynn_binary_multiply, 9420, 8651, 2623);
  g->Binary(ynn_binary_add, 2622, 2623, 2624);
  g->Binary(ynn_binary_multiply, 2624, 8645, 2625);
  g->Quantize(2613, 2626, 0.24657383561134338, 0);
  g->Transpose(9047, 6119, {1,0});
  g->Binary(ynn_binary_multiply, 6117, 6118, 6115);
  g->Dot(2626, 6119, YNN_INVALID_VALUE_ID, 6114, 1);
  g->DequantizeTensor(6114, YNN_INVALID_VALUE_ID, 6115, 6116);
  g->QuantizeTensor(6116, 8595, 5455, 2628);
  g->Dequantize(2628, 2629, 0.18897639214992523, 0);
  g->Polynomial(2629, 7885, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7885, 7886);
  g->Binary(ynn_binary_add, 7886, 7161, 7883);
  g->Binary(ynn_binary_multiply, 2629, 7173, 7884);
  g->Binary(ynn_binary_multiply, 7884, 7883, 2630);
  g->Binary(ynn_binary_multiply, 2630, 2625, 2631);
  g->Quantize(2631, 2632, 1.3779528141021729, 0);
  g->Transpose(9048, 6126, {1,0});
  g->Binary(ynn_binary_multiply, 6123, 6125, 6121);
  g->Dot(2632, 6126, YNN_INVALID_VALUE_ID, 6120, 1);
  g->DequantizeTensor(6120, YNN_INVALID_VALUE_ID, 6121, 6122);
  g->QuantizeTensor(6122, 8595, 6124, 2633);
  g->Dequantize(2633, 2634, 0.24400226771831512, 0);
  g->Unary(ynn_unary_square, 2634, 2635);
  g->Reduce(ynn_reduce_sum, 2635, 7888, {2}, true);
  g->ShapeProduct(2635, 7887, {2});
  g->Binary(ynn_binary_divide, 7888, 7887, 2636);
  g->Binary(ynn_binary_add, 2636, 8647, 2637);
  g->Unary(ynn_unary_rsqrt, 2637, 2639);
  g->Binary(ynn_binary_multiply, 2634, 2639, 2640);
  g->Binary(ynn_binary_multiply, 2640, 9051, 2641);
  g->Binary(ynn_binary_add, 2613, 2641, 2642);
  g->Binary(ynn_binary_multiply, 2642, 9043, 2643);
}

// Scope: "Layer25"
LAB_YNN_BUILDER_NOINLINE void BuildLayer25(Context& ctx) {
  BuildLayer25Attention(ctx);
  BuildLayer25Mlp(ctx);
  BuildLayer25PerLayerEmbedding(ctx);
}

}  // namespace BuildGemma4DecodeSource
