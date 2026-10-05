// Generated YNNPACK builder; do not edit.
#include "gemma4_decode_builder.h"

namespace BuildGemma4DecodeSource {

// Scope: "Layer18 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(1613, 1614, 0.21988293528556824, 0);
  g->Transpose(9053, 5788, {1,0});
  g->Binary(ynn_binary_multiply, 5786, 5787, 5784);
  g->Dot(1614, 5788, YNN_INVALID_VALUE_ID, 5783, 1);
  g->DequantizeTensor(5783, YNN_INVALID_VALUE_ID, 5784, 5785);
  g->QuantizeTensor(5785, 8727, 5404, 1615);
  g->Dequantize(1615, 1616, 0.2027559131383896, 0);
  g->SplitDim(1616, 1617, 2, {2,256});
  g->FuseDims(1617, 1619, 1, 2);
  g->SplitDim(1619, 1618, 1, {2,1});
  g->Unary(ynn_unary_square, 1618, 1621);
  g->Reduce(ynn_reduce_sum, 1621, 7720, {3}, true);
  g->ShapeProduct(1621, 7719, {3});
  g->Binary(ynn_binary_divide, 7720, 7719, 1622);
  g->Binary(ynn_binary_add, 1622, 8779, 1623);
  g->Unary(ynn_unary_rsqrt, 1623, 1624);
  g->Binary(ynn_binary_multiply, 1618, 1624, 1625);
  g->Binary(ynn_binary_multiply, 1625, 9052, 1626);
  g->Slice(1626, 1627, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1626, 1628, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1628, 1629);
  g->Concat({1629,1627}, 1630, 3);
  g->Binary(ynn_binary_multiply, 1626, 3231, 1632);
  g->Binary(ynn_binary_multiply, 1630, 4329, 1633);
  g->Binary(ynn_binary_add, 1632, 1633, 1634);
  g->Transpose(9057, 5793, {1,0});
  g->Binary(ynn_binary_multiply, 5786, 5792, 5790);
  g->Dot(1614, 5793, YNN_INVALID_VALUE_ID, 5789, 1);
  g->DequantizeTensor(5789, YNN_INVALID_VALUE_ID, 5790, 5791);
  g->QuantizeTensor(5791, 8727, 5404, 1635);
  g->Dequantize(1635, 1636, 0.2027559131383896, 0);
  g->SplitDim(1636, 1637, 2, {2,256});
  g->FuseDims(1637, 1639, 1, 2);
  g->SplitDim(1639, 1638, 1, {2,1});
  g->Unary(ynn_unary_square, 1638, 1640);
  g->Reduce(ynn_reduce_sum, 1640, 7726, {3}, true);
  g->ShapeProduct(1640, 7725, {3});
  g->Binary(ynn_binary_divide, 7726, 7725, 1641);
  g->Binary(ynn_binary_add, 1641, 8779, 1643);
  g->Unary(ynn_unary_rsqrt, 1643, 1644);
  g->Binary(ynn_binary_multiply, 1638, 1644, 1645);
}

// Scope: "Layer18 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(1634, 1646, 0.00573749840259552, 0);
  g->Append(8738, 1646, 9587, 2, s2, slinky::expr(int64_t{1}));
  g->View(9587, 9635, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(1645, 1647, 0.047244105488061905, 0);
  g->Append(8762, 1647, 9611, 2, s2, slinky::expr(int64_t{1}));
  g->View(9611, 9659, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer18 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(9056, 5799, {1,0});
  g->Binary(ynn_binary_multiply, 5786, 5798, 5795);
  g->Dot(1614, 5799, YNN_INVALID_VALUE_ID, 5794, 1);
  g->DequantizeTensor(5794, YNN_INVALID_VALUE_ID, 5795, 5796);
  g->QuantizeTensor(5796, 8727, 5797, 1649);
  g->Dequantize(1649, 1650, 0.22539371252059937, 0);
  g->SplitDim(1650, 1651, 2, {8,256});
  g->FuseDims(1651, 1653, 1, 2);
  g->SplitDim(1653, 1652, 1, {8,1});
  g->Unary(ynn_unary_square, 1652, 1654);
  g->Reduce(ynn_reduce_sum, 1654, 7728, {3}, true);
  g->ShapeProduct(1654, 7727, {3});
  g->Binary(ynn_binary_divide, 7728, 7727, 1655);
  g->Binary(ynn_binary_add, 1655, 8779, 1656);
  g->Unary(ynn_unary_rsqrt, 1656, 1657);
  g->Binary(ynn_binary_multiply, 1652, 1657, 1658);
  g->Binary(ynn_binary_multiply, 1658, 9055, 1659);
  g->Slice(1659, 1661, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1659, 1662, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1662, 1663);
  g->Concat({1663,1661}, 1664, 3);
  g->Binary(ynn_binary_multiply, 1659, 3231, 1665);
  g->Binary(ynn_binary_multiply, 1664, 4329, 1666);
  g->Binary(ynn_binary_add, 1665, 1666, 1667);
}

// Scope: "Layer18 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9635, 1668, 0.00573749840259552, 0);
  g->Dequantize(9659, 1669, 0.047244105488061905, 0);
  g->Slice(1667, 1670, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(1668, 1672, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(1669, 1673, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(1670, 1672, 1674, false, true);
  g->Mask(1674, 8804, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8804, 7732, {-1}, true);
  g->Binary(ynn_binary_subtract, 8804, 7732, 7729);
  g->Unary(ynn_unary_exp, 7729, 7730);
  g->Reduce(ynn_reduce_sum, 7730, 7733, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 7733, 7731);
  g->Binary(ynn_binary_multiply, 7730, 7731, 1675);
  g->Matmul(1675, 1673, 1676, false, false);
  g->Slice(1667, 1677, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(1668, 1678, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(1669, 1679, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(1677, 1678, 1680, false, true);
  g->Mask(1680, 8805, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8805, 7737, {-1}, true);
  g->Binary(ynn_binary_subtract, 8805, 7737, 7734);
  g->Unary(ynn_unary_exp, 7734, 7735);
  g->Reduce(ynn_reduce_sum, 7735, 7738, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 7738, 7736);
  g->Binary(ynn_binary_multiply, 7735, 7736, 1682);
  g->Matmul(1682, 1679, 1683, false, false);
  g->Concat({1676,1683}, 1684, 1);
}

// Scope: "Layer18 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(1684, 1686, 1, 2);
  g->SplitDim(1686, 1685, 1, {1,8});
  g->FuseDims(1685, 1687, 2, 2);
  g->Quantize(1687, 1688, 0.023868119344115257, 0);
  g->Transpose(9054, 5813, {1,0});
  g->Binary(ynn_binary_multiply, 5810, 5812, 5808);
  g->Dot(1688, 5813, YNN_INVALID_VALUE_ID, 5807, 1);
  g->DequantizeTensor(5807, YNN_INVALID_VALUE_ID, 5808, 5809);
  g->QuantizeTensor(5809, 8727, 5811, 1689);
  g->Dequantize(1689, 1690, 0.027112234383821487, 0);
}

// Scope: "Layer18 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1604, 1605);
  g->Reduce(ynn_reduce_sum, 1605, 7718, {2}, true);
  g->ShapeProduct(1605, 7717, {2});
  g->Binary(ynn_binary_divide, 7718, 7717, 1609);
  g->Binary(ynn_binary_add, 1609, 8779, 1610);
  g->Unary(ynn_unary_rsqrt, 1610, 1611);
  g->Binary(ynn_binary_multiply, 1604, 1611, 1612);
  g->Binary(ynn_binary_multiply, 1612, 9041, 1613);
  BuildLayer18AttentionKvProjection(ctx);
  BuildLayer18AttentionCacheUpdate(ctx);
  BuildLayer18AttentionQueryProjection(ctx);
  BuildLayer18AttentionSdpa(ctx);
  BuildLayer18AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1690, 1691);
  g->Reduce(ynn_reduce_sum, 1691, 7742, {2}, true);
  g->ShapeProduct(1691, 7741, {2});
  g->Binary(ynn_binary_divide, 7742, 7741, 1693);
  g->Binary(ynn_binary_add, 1693, 8779, 1694);
  g->Unary(ynn_unary_rsqrt, 1694, 1695);
  g->Binary(ynn_binary_multiply, 1690, 1695, 1696);
  g->Binary(ynn_binary_multiply, 1696, 9048, 1697);
  g->Binary(ynn_binary_add, 1697, 1604, 1698);
}

// Scope: "Layer18 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1698, 1699);
  g->Reduce(ynn_reduce_sum, 1699, 7744, {2}, true);
  g->ShapeProduct(1699, 7743, {2});
  g->Binary(ynn_binary_divide, 7744, 7743, 1700);
  g->Binary(ynn_binary_add, 1700, 8779, 1701);
  g->Unary(ynn_unary_rsqrt, 1701, 1702);
  g->Binary(ynn_binary_multiply, 1698, 1702, 1704);
  g->Binary(ynn_binary_multiply, 1704, 9051, 1705);
  g->Quantize(1705, 1706, 0.0140849519520998, 0);
  g->Transpose(9045, 5820, {1,0});
  g->Binary(ynn_binary_multiply, 5817, 5819, 5815);
  g->Dot(1706, 5820, YNN_INVALID_VALUE_ID, 5814, 1);
  g->DequantizeTensor(5814, YNN_INVALID_VALUE_ID, 5815, 5816);
  g->QuantizeTensor(5816, 8727, 5818, 1707);
  g->Dequantize(1707, 1708, 0.016732292249798775, 0);
  g->Transpose(9044, 5825, {1,0});
  g->Binary(ynn_binary_multiply, 5817, 5824, 5822);
  g->Dot(1706, 5825, YNN_INVALID_VALUE_ID, 5821, 1);
  g->DequantizeTensor(5821, YNN_INVALID_VALUE_ID, 5822, 5823);
  g->QuantizeTensor(5823, 8727, 5818, 1709);
  g->Dequantize(1709, 1710, 0.016732292249798775, 0);
  g->Polynomial(1710, 7747, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7747, 7748);
  g->Binary(ynn_binary_add, 7748, 7293, 7745);
  g->Binary(ynn_binary_multiply, 1710, 7305, 7746);
  g->Binary(ynn_binary_multiply, 7746, 7745, 1711);
  g->Binary(ynn_binary_multiply, 1708, 1711, 1712);
  g->Quantize(1712, 1715, 0.009719498455524445, 0);
  g->Transpose(9043, 5832, {1,0});
  g->Binary(ynn_binary_multiply, 5829, 5831, 5827);
  g->Dot(1715, 5832, YNN_INVALID_VALUE_ID, 5826, 1);
  g->DequantizeTensor(5826, YNN_INVALID_VALUE_ID, 5827, 5828);
  g->QuantizeTensor(5828, 8727, 5830, 1716);
  g->Dequantize(1716, 1717, 0.00551135279238224, 0);
  g->Unary(ynn_unary_square, 1717, 1718);
  g->Reduce(ynn_reduce_sum, 1718, 7750, {2}, true);
  g->ShapeProduct(1718, 7749, {2});
  g->Binary(ynn_binary_divide, 7750, 7749, 1719);
  g->Binary(ynn_binary_add, 1719, 8779, 1720);
  g->Unary(ynn_unary_rsqrt, 1720, 1721);
  g->Binary(ynn_binary_multiply, 1717, 1721, 1722);
  g->Binary(ynn_binary_multiply, 1722, 9049, 1723);
  g->Binary(ynn_binary_add, 1723, 1698, 1724);
}

// Scope: "Layer18 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(429, 1726, {0,0,18,0}, {-1,-1,1,-1});
  g->Reshape(1726, 1727, {1,1,256});
  g->Unary(ynn_unary_square, 1727, 1728);
  g->Reduce(ynn_reduce_sum, 1728, 7752, {2}, true);
  g->ShapeProduct(1728, 7751, {2});
  g->Binary(ynn_binary_divide, 7752, 7751, 1729);
  g->Binary(ynn_binary_add, 1729, 8779, 1730);
  g->Unary(ynn_unary_rsqrt, 1730, 1731);
  g->Binary(ynn_binary_multiply, 1727, 1731, 1732);
  g->Binary(ynn_binary_multiply, 1732, 9533, 1733);
  g->Binary(ynn_binary_multiply, 9544, 8783, 1734);
  g->Binary(ynn_binary_add, 1733, 1734, 1735);
  g->Binary(ynn_binary_multiply, 1735, 8777, 1737);
  g->Quantize(1724, 1738, 0.157975435256958, 0);
  g->Transpose(9046, 5839, {1,0});
  g->Binary(ynn_binary_multiply, 5836, 5838, 5834);
  g->Dot(1738, 5839, YNN_INVALID_VALUE_ID, 5833, 1);
  g->DequantizeTensor(5833, YNN_INVALID_VALUE_ID, 5834, 5835);
  g->QuantizeTensor(5835, 8727, 5837, 1739);
  g->Dequantize(1739, 1740, 0.06397638469934464, 0);
  g->Polynomial(1740, 7755, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7755, 7756);
  g->Binary(ynn_binary_add, 7756, 7293, 7753);
  g->Binary(ynn_binary_multiply, 1740, 7305, 7754);
  g->Binary(ynn_binary_multiply, 7754, 7753, 1741);
  g->Binary(ynn_binary_multiply, 1741, 1737, 1742);
  g->Quantize(1742, 1743, 0.48622047901153564, 0);
  g->Transpose(9047, 5846, {1,0});
  g->Binary(ynn_binary_multiply, 5843, 5845, 5841);
  g->Dot(1743, 5846, YNN_INVALID_VALUE_ID, 5840, 1);
  g->DequantizeTensor(5840, YNN_INVALID_VALUE_ID, 5841, 5842);
  g->QuantizeTensor(5842, 8727, 5844, 1744);
  g->Dequantize(1744, 1745, 0.13593116402626038, 0);
  g->Unary(ynn_unary_square, 1745, 1746);
  g->Reduce(ynn_reduce_sum, 1746, 7758, {2}, true);
  g->ShapeProduct(1746, 7757, {2});
  g->Binary(ynn_binary_divide, 7758, 7757, 1748);
  g->Binary(ynn_binary_add, 1748, 8779, 1749);
  g->Unary(ynn_unary_rsqrt, 1749, 1750);
  g->Binary(ynn_binary_multiply, 1745, 1750, 1751);
  g->Binary(ynn_binary_multiply, 1751, 9050, 1752);
  g->Binary(ynn_binary_add, 1724, 1752, 1753);
  g->Binary(ynn_binary_multiply, 1753, 9042, 1754);
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
  g->Quantize(1761, 1762, 0.12022246420383453, 0);
  g->Transpose(9070, 5853, {1,0});
  g->Binary(ynn_binary_multiply, 5850, 5852, 5848);
  g->Dot(1762, 5853, YNN_INVALID_VALUE_ID, 5847, 1);
  g->DequantizeTensor(5847, YNN_INVALID_VALUE_ID, 5848, 5849);
  g->QuantizeTensor(5849, 8727, 5851, 1763);
  g->Dequantize(1763, 1764, 0.11515748500823975, 0);
  g->SplitDim(1764, 1765, 2, {2,256});
  g->FuseDims(1765, 1767, 1, 2);
  g->SplitDim(1767, 1766, 1, {2,1});
  g->Unary(ynn_unary_square, 1766, 1768);
  g->Reduce(ynn_reduce_sum, 1768, 7762, {3}, true);
  g->ShapeProduct(1768, 7761, {3});
  g->Binary(ynn_binary_divide, 7762, 7761, 1769);
  g->Binary(ynn_binary_add, 1769, 8779, 1771);
  g->Unary(ynn_unary_rsqrt, 1771, 1772);
  g->Binary(ynn_binary_multiply, 1766, 1772, 1773);
  g->Binary(ynn_binary_multiply, 1773, 9069, 1774);
  g->Slice(1774, 1775, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1774, 1776, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1776, 1777);
  g->Concat({1777,1775}, 1778, 3);
  g->Binary(ynn_binary_multiply, 1774, 3231, 1779);
  g->Binary(ynn_binary_multiply, 1778, 4329, 1780);
  g->Binary(ynn_binary_add, 1779, 1780, 1782);
  g->Transpose(9074, 5858, {1,0});
  g->Binary(ynn_binary_multiply, 5850, 5857, 5855);
  g->Dot(1762, 5858, YNN_INVALID_VALUE_ID, 5854, 1);
  g->DequantizeTensor(5854, YNN_INVALID_VALUE_ID, 5855, 5856);
  g->QuantizeTensor(5856, 8727, 5851, 1783);
  g->Dequantize(1783, 1784, 0.11515748500823975, 0);
  g->SplitDim(1784, 1785, 2, {2,256});
  g->FuseDims(1785, 1787, 1, 2);
  g->SplitDim(1787, 1786, 1, {2,1});
  g->Unary(ynn_unary_square, 1786, 1788);
  g->Reduce(ynn_reduce_sum, 1788, 7764, {3}, true);
  g->ShapeProduct(1788, 7763, {3});
  g->Binary(ynn_binary_divide, 7764, 7763, 1789);
  g->Binary(ynn_binary_add, 1789, 8779, 1790);
  g->Unary(ynn_unary_rsqrt, 1790, 1791);
  g->Binary(ynn_binary_multiply, 1786, 1791, 1793);
}

// Scope: "Layer19 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(1782, 1794, 0.005869260523468256, 0);
  g->Append(8739, 1794, 9588, 2, s2, slinky::expr(int64_t{1}));
  g->View(9588, 9636, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(1793, 1795, 0.047244105488061905, 0);
  g->Append(8763, 1795, 9612, 2, s2, slinky::expr(int64_t{1}));
  g->View(9612, 9660, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer19 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(9073, 5864, {1,0});
  g->Binary(ynn_binary_multiply, 5850, 5863, 5860);
  g->Dot(1762, 5864, YNN_INVALID_VALUE_ID, 5859, 1);
  g->DequantizeTensor(5859, YNN_INVALID_VALUE_ID, 5860, 5861);
  g->QuantizeTensor(5861, 8727, 5862, 1796);
  g->Dequantize(1796, 1797, 0.1328740268945694, 0);
  g->SplitDim(1797, 1799, 2, {8,256});
  g->FuseDims(1799, 1801, 1, 2);
  g->SplitDim(1801, 1800, 1, {8,1});
  g->Unary(ynn_unary_square, 1800, 1802);
  g->Reduce(ynn_reduce_sum, 1802, 7768, {3}, true);
  g->ShapeProduct(1802, 7767, {3});
  g->Binary(ynn_binary_divide, 7768, 7767, 1803);
  g->Binary(ynn_binary_add, 1803, 8779, 1804);
  g->Unary(ynn_unary_rsqrt, 1804, 1805);
  g->Binary(ynn_binary_multiply, 1800, 1805, 1806);
  g->Binary(ynn_binary_multiply, 1806, 9072, 1807);
  g->Slice(1807, 1808, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1807, 1809, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1809, 1811);
  g->Concat({1811,1808}, 1812, 3);
  g->Binary(ynn_binary_multiply, 1807, 3231, 1813);
  g->Binary(ynn_binary_multiply, 1812, 4329, 1814);
  g->Binary(ynn_binary_add, 1813, 1814, 1815);
}

// Scope: "Layer19 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9636, 1816, 0.005869260523468256, 0);
  g->Dequantize(9660, 1817, 0.047244105488061905, 0);
  g->Slice(1815, 1818, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(1816, 1819, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(1817, 1820, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(1818, 1819, 1823, false, true);
  g->Mask(1823, 8806, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8806, 7774, {-1}, true);
  g->Binary(ynn_binary_subtract, 8806, 7774, 7771);
  g->Unary(ynn_unary_exp, 7771, 7772);
  g->Reduce(ynn_reduce_sum, 7772, 7775, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 7775, 7773);
  g->Binary(ynn_binary_multiply, 7772, 7773, 1824);
  g->Matmul(1824, 1820, 1825, false, false);
  g->Slice(1815, 1826, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(1816, 1827, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(1817, 1828, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(1826, 1827, 1829, false, true);
  g->Mask(1829, 8807, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8807, 7779, {-1}, true);
  g->Binary(ynn_binary_subtract, 8807, 7779, 7776);
  g->Unary(ynn_unary_exp, 7776, 7777);
  g->Reduce(ynn_reduce_sum, 7777, 7780, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 7780, 7778);
  g->Binary(ynn_binary_multiply, 7777, 7778, 1830);
  g->Matmul(1830, 1828, 1832, false, false);
  g->Concat({1825,1832}, 1833, 1);
}

// Scope: "Layer19 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(1833, 1835, 1, 2);
  g->SplitDim(1835, 1834, 1, {1,8});
  g->FuseDims(1834, 1836, 2, 2);
  g->Quantize(1836, 1837, 0.02509843371808529, 0);
  g->Transpose(9071, 5871, {1,0});
  g->Binary(ynn_binary_multiply, 5868, 5870, 5866);
  g->Dot(1837, 5871, YNN_INVALID_VALUE_ID, 5865, 1);
  g->DequantizeTensor(5865, YNN_INVALID_VALUE_ID, 5866, 5867);
  g->QuantizeTensor(5867, 8727, 5869, 1838);
  g->Dequantize(1838, 1839, 0.02879992686212063, 0);
}

// Scope: "Layer19 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1754, 1755);
  g->Reduce(ynn_reduce_sum, 1755, 7760, {2}, true);
  g->ShapeProduct(1755, 7759, {2});
  g->Binary(ynn_binary_divide, 7760, 7759, 1756);
  g->Binary(ynn_binary_add, 1756, 8779, 1757);
  g->Unary(ynn_unary_rsqrt, 1757, 1759);
  g->Binary(ynn_binary_multiply, 1754, 1759, 1760);
  g->Binary(ynn_binary_multiply, 1760, 9058, 1761);
  BuildLayer19AttentionKvProjection(ctx);
  BuildLayer19AttentionCacheUpdate(ctx);
  BuildLayer19AttentionQueryProjection(ctx);
  BuildLayer19AttentionSdpa(ctx);
  BuildLayer19AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1839, 1840);
  g->Reduce(ynn_reduce_sum, 1840, 7782, {2}, true);
  g->ShapeProduct(1840, 7781, {2});
  g->Binary(ynn_binary_divide, 7782, 7781, 1841);
  g->Binary(ynn_binary_add, 1841, 8779, 1842);
  g->Unary(ynn_unary_rsqrt, 1842, 1844);
  g->Binary(ynn_binary_multiply, 1839, 1844, 1845);
  g->Binary(ynn_binary_multiply, 1845, 9065, 1846);
  g->Binary(ynn_binary_add, 1846, 1754, 1847);
}

// Scope: "Layer19 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1847, 1848);
  g->Reduce(ynn_reduce_sum, 1848, 7784, {2}, true);
  g->ShapeProduct(1848, 7783, {2});
  g->Binary(ynn_binary_divide, 7784, 7783, 1849);
  g->Binary(ynn_binary_add, 1849, 8779, 1850);
  g->Unary(ynn_unary_rsqrt, 1850, 1851);
  g->Binary(ynn_binary_multiply, 1847, 1851, 1852);
  g->Binary(ynn_binary_multiply, 1852, 9068, 1853);
  g->Quantize(1853, 1855, 0.01280234195291996, 0);
  g->Transpose(9062, 5878, {1,0});
  g->Binary(ynn_binary_multiply, 5875, 5877, 5873);
  g->Dot(1855, 5878, YNN_INVALID_VALUE_ID, 5872, 1);
  g->DequantizeTensor(5872, YNN_INVALID_VALUE_ID, 5873, 5874);
  g->QuantizeTensor(5874, 8727, 5876, 1856);
  g->Dequantize(1856, 1857, 0.014456210657954216, 0);
  g->Transpose(9061, 5883, {1,0});
  g->Binary(ynn_binary_multiply, 5875, 5882, 5880);
  g->Dot(1855, 5883, YNN_INVALID_VALUE_ID, 5879, 1);
  g->DequantizeTensor(5879, YNN_INVALID_VALUE_ID, 5880, 5881);
  g->QuantizeTensor(5881, 8727, 5876, 1858);
  g->Dequantize(1858, 1859, 0.014456210657954216, 0);
  g->Polynomial(1859, 7787, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7787, 7788);
  g->Binary(ynn_binary_add, 7788, 7293, 7785);
  g->Binary(ynn_binary_multiply, 1859, 7305, 7786);
  g->Binary(ynn_binary_multiply, 7786, 7785, 1860);
  g->Binary(ynn_binary_multiply, 1857, 1860, 1861);
  g->Quantize(1861, 1862, 0.0076587204821407795, 0);
  g->Transpose(9060, 5890, {1,0});
  g->Binary(ynn_binary_multiply, 5887, 5889, 5885);
  g->Dot(1862, 5890, YNN_INVALID_VALUE_ID, 5884, 1);
  g->DequantizeTensor(5884, YNN_INVALID_VALUE_ID, 5885, 5886);
  g->QuantizeTensor(5886, 8727, 5888, 1863);
  g->Dequantize(1863, 1865, 0.004359397571533918, 0);
  g->Unary(ynn_unary_square, 1865, 1866);
  g->Reduce(ynn_reduce_sum, 1866, 7790, {2}, true);
  g->ShapeProduct(1866, 7789, {2});
  g->Binary(ynn_binary_divide, 7790, 7789, 1867);
  g->Binary(ynn_binary_add, 1867, 8779, 1868);
  g->Unary(ynn_unary_rsqrt, 1868, 1869);
  g->Binary(ynn_binary_multiply, 1865, 1869, 1870);
  g->Binary(ynn_binary_multiply, 1870, 9066, 1871);
  g->Binary(ynn_binary_add, 1871, 1847, 1872);
}

// Scope: "Layer19 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(429, 1873, {0,0,19,0}, {-1,-1,1,-1});
  g->Reshape(1873, 1874, {1,1,256});
  g->Unary(ynn_unary_square, 1874, 1876);
  g->Reduce(ynn_reduce_sum, 1876, 7792, {2}, true);
  g->ShapeProduct(1876, 7791, {2});
  g->Binary(ynn_binary_divide, 7792, 7791, 1877);
  g->Binary(ynn_binary_add, 1877, 8779, 1878);
  g->Unary(ynn_unary_rsqrt, 1878, 1879);
  g->Binary(ynn_binary_multiply, 1874, 1879, 1880);
  g->Binary(ynn_binary_multiply, 1880, 9533, 1881);
  g->Binary(ynn_binary_multiply, 9545, 8783, 1882);
  g->Binary(ynn_binary_add, 1881, 1882, 1883);
  g->Binary(ynn_binary_multiply, 1883, 8777, 1884);
  g->Quantize(1872, 1885, 0.12497252225875854, 0);
  g->Transpose(9063, 5903, {1,0});
  g->Binary(ynn_binary_multiply, 5900, 5902, 5898);
  g->Dot(1885, 5903, YNN_INVALID_VALUE_ID, 5897, 1);
  g->DequantizeTensor(5897, YNN_INVALID_VALUE_ID, 5898, 5899);
  g->QuantizeTensor(5899, 8727, 5901, 1887);
  g->Dequantize(1887, 1888, 0.0743110328912735, 0);
  g->Polynomial(1888, 7795, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7795, 7796);
  g->Binary(ynn_binary_add, 7796, 7293, 7793);
  g->Binary(ynn_binary_multiply, 1888, 7305, 7794);
  g->Binary(ynn_binary_multiply, 7794, 7793, 1889);
  g->Binary(ynn_binary_multiply, 1889, 1884, 1890);
  g->Quantize(1890, 1891, 0.1643700897693634, 0);
  g->Transpose(9064, 5910, {1,0});
  g->Binary(ynn_binary_multiply, 5907, 5909, 5905);
  g->Dot(1891, 5910, YNN_INVALID_VALUE_ID, 5904, 1);
  g->DequantizeTensor(5904, YNN_INVALID_VALUE_ID, 5905, 5906);
  g->QuantizeTensor(5906, 8727, 5908, 1892);
  g->Dequantize(1892, 1893, 0.10370250046253204, 0);
  g->Unary(ynn_unary_square, 1893, 1894);
  g->Reduce(ynn_reduce_sum, 1894, 7798, {2}, true);
  g->ShapeProduct(1894, 7797, {2});
  g->Binary(ynn_binary_divide, 7798, 7797, 1895);
  g->Binary(ynn_binary_add, 1895, 8779, 1896);
  g->Unary(ynn_unary_rsqrt, 1896, 1898);
  g->Binary(ynn_binary_multiply, 1893, 1898, 1899);
  g->Binary(ynn_binary_multiply, 1899, 9067, 1900);
  g->Binary(ynn_binary_add, 1872, 1900, 1901);
  g->Binary(ynn_binary_multiply, 1901, 9059, 1902);
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
  g->Quantize(1909, 1910, 0.04660104587674141, 0);
  g->Transpose(9104, 5917, {1,0});
  g->Binary(ynn_binary_multiply, 5914, 5916, 5912);
  g->Dot(1910, 5917, YNN_INVALID_VALUE_ID, 5911, 1);
  g->DequantizeTensor(5911, YNN_INVALID_VALUE_ID, 5912, 5913);
  g->QuantizeTensor(5913, 8727, 5915, 1911);
  g->Dequantize(1911, 1912, 0.05807087570428848, 0);
  g->SplitDim(1912, 1913, 2, {2,256});
  g->FuseDims(1913, 1915, 1, 2);
  g->SplitDim(1915, 1914, 1, {2,1});
  g->Unary(ynn_unary_square, 1914, 1916);
  g->Reduce(ynn_reduce_sum, 1916, 7806, {3}, true);
  g->ShapeProduct(1916, 7805, {3});
  g->Binary(ynn_binary_divide, 7806, 7805, 1917);
  g->Binary(ynn_binary_add, 1917, 8779, 1918);
  g->Unary(ynn_unary_rsqrt, 1918, 1919);
  g->Binary(ynn_binary_multiply, 1914, 1919, 1921);
  g->Binary(ynn_binary_multiply, 1921, 9103, 1922);
  g->Slice(1922, 1923, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1922, 1924, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1924, 1925);
  g->Concat({1925,1923}, 1926, 3);
  g->Binary(ynn_binary_multiply, 1922, 3231, 1927);
  g->Binary(ynn_binary_multiply, 1926, 4329, 1928);
  g->Binary(ynn_binary_add, 1927, 1928, 1929);
  g->Transpose(9108, 5922, {1,0});
  g->Binary(ynn_binary_multiply, 5914, 5921, 5919);
  g->Dot(1910, 5922, YNN_INVALID_VALUE_ID, 5918, 1);
  g->DequantizeTensor(5918, YNN_INVALID_VALUE_ID, 5919, 5920);
  g->QuantizeTensor(5920, 8727, 5915, 1932);
  g->Dequantize(1932, 1933, 0.05807087570428848, 0);
  g->SplitDim(1933, 1934, 2, {2,256});
  g->FuseDims(1934, 1936, 1, 2);
  g->SplitDim(1936, 1935, 1, {2,1});
  g->Unary(ynn_unary_square, 1935, 1937);
  g->Reduce(ynn_reduce_sum, 1937, 7808, {3}, true);
  g->ShapeProduct(1937, 7807, {3});
  g->Binary(ynn_binary_divide, 7808, 7807, 1938);
  g->Binary(ynn_binary_add, 1938, 8779, 1939);
  g->Unary(ynn_unary_rsqrt, 1939, 1940);
  g->Binary(ynn_binary_multiply, 1935, 1940, 1941);
}

// Scope: "Layer20 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(1929, 1942, 0.005907459184527397, 0);
  g->Append(8741, 1942, 9590, 2, s2, slinky::expr(int64_t{1}));
  g->View(9590, 9638, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(1941, 1944, 0.047244105488061905, 0);
  g->Append(8765, 1944, 9614, 2, s2, slinky::expr(int64_t{1}));
  g->View(9614, 9662, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer20 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(9107, 5935, {1,0});
  g->Binary(ynn_binary_multiply, 5914, 5934, 5931);
  g->Dot(1910, 5935, YNN_INVALID_VALUE_ID, 5930, 1);
  g->DequantizeTensor(5930, YNN_INVALID_VALUE_ID, 5931, 5932);
  g->QuantizeTensor(5932, 8727, 5933, 1945);
  g->Dequantize(1945, 1946, 0.08710630983114243, 0);
  g->SplitDim(1946, 1947, 2, {8,256});
  g->FuseDims(1947, 1949, 1, 2);
  g->SplitDim(1949, 1948, 1, {8,1});
  g->Unary(ynn_unary_square, 1948, 1951);
  g->Reduce(ynn_reduce_sum, 1951, 7810, {3}, true);
  g->ShapeProduct(1951, 7809, {3});
  g->Binary(ynn_binary_divide, 7810, 7809, 1952);
  g->Binary(ynn_binary_add, 1952, 8779, 1953);
  g->Unary(ynn_unary_rsqrt, 1953, 1954);
  g->Binary(ynn_binary_multiply, 1948, 1954, 1955);
  g->Binary(ynn_binary_multiply, 1955, 9106, 1956);
  g->Slice(1956, 1957, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1956, 1958, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1958, 1959);
  g->Concat({1959,1957}, 1960, 3);
  g->Binary(ynn_binary_multiply, 1956, 3231, 1962);
  g->Binary(ynn_binary_multiply, 1960, 4329, 1963);
  g->Binary(ynn_binary_add, 1962, 1963, 1964);
}

// Scope: "Layer20 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9638, 1965, 0.005907459184527397, 0);
  g->Dequantize(9662, 1966, 0.047244105488061905, 0);
  g->Slice(1964, 1967, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(1965, 1968, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(1966, 1969, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(1967, 1968, 1970, false, true);
  g->Mask(1970, 8810, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8810, 7816, {-1}, true);
  g->Binary(ynn_binary_subtract, 8810, 7816, 7813);
  g->Unary(ynn_unary_exp, 7813, 7814);
  g->Reduce(ynn_reduce_sum, 7814, 7817, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 7817, 7815);
  g->Binary(ynn_binary_multiply, 7814, 7815, 1972);
  g->Matmul(1972, 1969, 1973, false, false);
  g->Slice(1964, 1974, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(1965, 1975, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(1966, 1976, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(1974, 1975, 1977, false, true);
  g->Mask(1977, 8811, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8811, 7821, {-1}, true);
  g->Binary(ynn_binary_subtract, 8811, 7821, 7818);
  g->Unary(ynn_unary_exp, 7818, 7819);
  g->Reduce(ynn_reduce_sum, 7819, 7822, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 7822, 7820);
  g->Binary(ynn_binary_multiply, 7819, 7820, 1978);
  g->Matmul(1978, 1976, 1979, false, false);
  g->Concat({1973,1979}, 1980, 1);
}

// Scope: "Layer20 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(1980, 1983, 1, 2);
  g->SplitDim(1983, 1982, 1, {1,8});
  g->FuseDims(1982, 1984, 2, 2);
  g->Quantize(1984, 1985, 0.025713592767715454, 0);
  g->Transpose(9105, 5942, {1,0});
  g->Binary(ynn_binary_multiply, 5939, 5941, 5937);
  g->Dot(1985, 5942, YNN_INVALID_VALUE_ID, 5936, 1);
  g->DequantizeTensor(5936, YNN_INVALID_VALUE_ID, 5937, 5938);
  g->QuantizeTensor(5938, 8727, 5940, 1986);
  g->Dequantize(1986, 1987, 0.03443482890725136, 0);
}

// Scope: "Layer20 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1902, 1903);
  g->Reduce(ynn_reduce_sum, 1903, 7800, {2}, true);
  g->ShapeProduct(1903, 7799, {2});
  g->Binary(ynn_binary_divide, 7800, 7799, 1904);
  g->Binary(ynn_binary_add, 1904, 8779, 1905);
  g->Unary(ynn_unary_rsqrt, 1905, 1906);
  g->Binary(ynn_binary_multiply, 1902, 1906, 1907);
  g->Binary(ynn_binary_multiply, 1907, 9092, 1909);
  BuildLayer20AttentionKvProjection(ctx);
  BuildLayer20AttentionCacheUpdate(ctx);
  BuildLayer20AttentionQueryProjection(ctx);
  BuildLayer20AttentionSdpa(ctx);
  BuildLayer20AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1987, 1988);
  g->Reduce(ynn_reduce_sum, 1988, 7824, {2}, true);
  g->ShapeProduct(1988, 7823, {2});
  g->Binary(ynn_binary_divide, 7824, 7823, 1989);
  g->Binary(ynn_binary_add, 1989, 8779, 1990);
  g->Unary(ynn_unary_rsqrt, 1990, 1991);
  g->Binary(ynn_binary_multiply, 1987, 1991, 1992);
  g->Binary(ynn_binary_multiply, 1992, 9099, 1994);
  g->Binary(ynn_binary_add, 1994, 1902, 1995);
}

// Scope: "Layer20 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1995, 1996);
  g->Reduce(ynn_reduce_sum, 1996, 7826, {2}, true);
  g->ShapeProduct(1996, 7825, {2});
  g->Binary(ynn_binary_divide, 7826, 7825, 1997);
  g->Binary(ynn_binary_add, 1997, 8779, 1998);
  g->Unary(ynn_unary_rsqrt, 1998, 1999);
  g->Binary(ynn_binary_multiply, 1995, 1999, 2000);
  g->Binary(ynn_binary_multiply, 2000, 9102, 2001);
  g->Quantize(2001, 2002, 0.014479842968285084, 0);
  g->Transpose(9096, 5949, {1,0});
  g->Binary(ynn_binary_multiply, 5946, 5948, 5944);
  g->Dot(2002, 5949, YNN_INVALID_VALUE_ID, 5943, 1);
  g->DequantizeTensor(5943, YNN_INVALID_VALUE_ID, 5944, 5945);
  g->QuantizeTensor(5945, 8727, 5947, 2003);
  g->Dequantize(2003, 2005, 0.015071368776261806, 0);
  g->Transpose(9095, 5954, {1,0});
  g->Binary(ynn_binary_multiply, 5946, 5953, 5951);
  g->Dot(2002, 5954, YNN_INVALID_VALUE_ID, 5950, 1);
  g->DequantizeTensor(5950, YNN_INVALID_VALUE_ID, 5951, 5952);
  g->QuantizeTensor(5952, 8727, 5947, 2006);
  g->Dequantize(2006, 2007, 0.015071368776261806, 0);
  g->Polynomial(2007, 7829, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7829, 7830);
  g->Binary(ynn_binary_add, 7830, 7293, 7827);
  g->Binary(ynn_binary_multiply, 2007, 7305, 7828);
  g->Binary(ynn_binary_multiply, 7828, 7827, 2008);
  g->Binary(ynn_binary_multiply, 2005, 2008, 2009);
  g->Quantize(2009, 2010, 0.005413395818322897, 0);
  g->Transpose(9094, 5961, {1,0});
  g->Binary(ynn_binary_multiply, 5958, 5960, 5956);
  g->Dot(2010, 5961, YNN_INVALID_VALUE_ID, 5955, 1);
  g->DequantizeTensor(5955, YNN_INVALID_VALUE_ID, 5956, 5957);
  g->QuantizeTensor(5957, 8727, 5959, 2011);
  g->Dequantize(2011, 2012, 0.004781397990882397, 0);
  g->Unary(ynn_unary_square, 2012, 2013);
  g->Reduce(ynn_reduce_sum, 2013, 7832, {2}, true);
  g->ShapeProduct(2013, 7831, {2});
  g->Binary(ynn_binary_divide, 7832, 7831, 2015);
  g->Binary(ynn_binary_add, 2015, 8779, 2016);
  g->Unary(ynn_unary_rsqrt, 2016, 2017);
  g->Binary(ynn_binary_multiply, 2012, 2017, 2018);
  g->Binary(ynn_binary_multiply, 2018, 9100, 2019);
  g->Binary(ynn_binary_add, 2019, 1995, 2020);
}

// Scope: "Layer20 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(429, 2021, {0,0,20,0}, {-1,-1,1,-1});
  g->Reshape(2021, 2022, {1,1,256});
  g->Unary(ynn_unary_square, 2022, 2023);
  g->Reduce(ynn_reduce_sum, 2023, 7834, {2}, true);
  g->ShapeProduct(2023, 7833, {2});
  g->Binary(ynn_binary_divide, 7834, 7833, 2024);
  g->Binary(ynn_binary_add, 2024, 8779, 2026);
  g->Unary(ynn_unary_rsqrt, 2026, 2027);
  g->Binary(ynn_binary_multiply, 2022, 2027, 2028);
  g->Binary(ynn_binary_multiply, 2028, 9533, 2029);
  g->Binary(ynn_binary_multiply, 9547, 8783, 2030);
  g->Binary(ynn_binary_add, 2029, 2030, 2031);
  g->Binary(ynn_binary_multiply, 2031, 8777, 2032);
  g->Quantize(2020, 2033, 0.17325256764888763, 0);
  g->Transpose(9097, 5968, {1,0});
  g->Binary(ynn_binary_multiply, 5965, 5967, 5963);
  g->Dot(2033, 5968, YNN_INVALID_VALUE_ID, 5962, 1);
  g->DequantizeTensor(5962, YNN_INVALID_VALUE_ID, 5963, 5964);
  g->QuantizeTensor(5964, 8727, 5966, 2034);
  g->Dequantize(2034, 2035, 0.09940945357084274, 0);
  g->Polynomial(2035, 7837, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7837, 7838);
  g->Binary(ynn_binary_add, 7838, 7293, 7835);
  g->Binary(ynn_binary_multiply, 2035, 7305, 7836);
  g->Binary(ynn_binary_multiply, 7836, 7835, 2038);
  g->Binary(ynn_binary_multiply, 2038, 2032, 2039);
  g->Quantize(2039, 2040, 0.8149606585502625, 0);
  g->Transpose(9098, 5975, {1,0});
  g->Binary(ynn_binary_multiply, 5972, 5974, 5970);
  g->Dot(2040, 5975, YNN_INVALID_VALUE_ID, 5969, 1);
  g->DequantizeTensor(5969, YNN_INVALID_VALUE_ID, 5970, 5971);
  g->QuantizeTensor(5971, 8727, 5973, 2041);
  g->Dequantize(2041, 2042, 0.16500307619571686, 0);
  g->Unary(ynn_unary_square, 2042, 2043);
  g->Reduce(ynn_reduce_sum, 2043, 7840, {2}, true);
  g->ShapeProduct(2043, 7839, {2});
  g->Binary(ynn_binary_divide, 7840, 7839, 2044);
  g->Binary(ynn_binary_add, 2044, 8779, 2045);
  g->Unary(ynn_unary_rsqrt, 2045, 2046);
  g->Binary(ynn_binary_multiply, 2042, 2046, 2047);
  g->Binary(ynn_binary_multiply, 2047, 9101, 2049);
  g->Binary(ynn_binary_add, 2020, 2049, 2050);
  g->Binary(ynn_binary_multiply, 2050, 9093, 2051);
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
  g->Quantize(2057, 2058, 0.03492194786667824, 0);
  g->Transpose(9121, 5982, {1,0});
  g->Binary(ynn_binary_multiply, 5979, 5981, 5977);
  g->Dot(2058, 5982, YNN_INVALID_VALUE_ID, 5976, 1);
  g->DequantizeTensor(5976, YNN_INVALID_VALUE_ID, 5977, 5978);
  g->QuantizeTensor(5978, 8727, 5980, 2060);
  g->Dequantize(2060, 2061, 0.03961615264415741, 0);
  g->SplitDim(2061, 2062, 2, {2,256});
  g->FuseDims(2062, 2064, 1, 2);
  g->SplitDim(2064, 2063, 1, {2,1});
  g->Unary(ynn_unary_square, 2063, 2065);
  g->Reduce(ynn_reduce_sum, 2065, 7846, {3}, true);
  g->ShapeProduct(2065, 7845, {3});
  g->Binary(ynn_binary_divide, 7846, 7845, 2066);
  g->Binary(ynn_binary_add, 2066, 8779, 2067);
  g->Unary(ynn_unary_rsqrt, 2067, 2068);
  g->Binary(ynn_binary_multiply, 2063, 2068, 2069);
  g->Binary(ynn_binary_multiply, 2069, 9120, 2070);
  g->Slice(2070, 2072, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2070, 2073, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2073, 2074);
  g->Concat({2074,2072}, 2075, 3);
  g->Binary(ynn_binary_multiply, 2070, 3231, 2076);
  g->Binary(ynn_binary_multiply, 2075, 4329, 2077);
  g->Binary(ynn_binary_add, 2076, 2077, 2078);
  g->Transpose(9125, 5987, {1,0});
  g->Binary(ynn_binary_multiply, 5979, 5986, 5984);
  g->Dot(2058, 5987, YNN_INVALID_VALUE_ID, 5983, 1);
  g->DequantizeTensor(5983, YNN_INVALID_VALUE_ID, 5984, 5985);
  g->QuantizeTensor(5985, 8727, 5980, 2079);
  g->Dequantize(2079, 2080, 0.03961615264415741, 0);
  g->SplitDim(2080, 2082, 2, {2,256});
  g->FuseDims(2082, 2084, 1, 2);
  g->SplitDim(2084, 2083, 1, {2,1});
  g->Unary(ynn_unary_square, 2083, 2085);
  g->Reduce(ynn_reduce_sum, 2085, 7848, {3}, true);
  g->ShapeProduct(2085, 7847, {3});
  g->Binary(ynn_binary_divide, 7848, 7847, 2086);
  g->Binary(ynn_binary_add, 2086, 8779, 2087);
  g->Unary(ynn_unary_rsqrt, 2087, 2088);
  g->Binary(ynn_binary_multiply, 2083, 2088, 2089);
}

// Scope: "Layer21 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(2078, 2090, 0.0060269939713180065, 0);
  g->Append(8742, 2090, 9591, 2, s2, slinky::expr(int64_t{1}));
  g->View(9591, 9639, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(2089, 2092, 0.047244105488061905, 0);
  g->Append(8766, 2092, 9615, 2, s2, slinky::expr(int64_t{1}));
  g->View(9615, 9663, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer21 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(9124, 5993, {1,0});
  g->Binary(ynn_binary_multiply, 5979, 5992, 5989);
  g->Dot(2058, 5993, YNN_INVALID_VALUE_ID, 5988, 1);
  g->DequantizeTensor(5988, YNN_INVALID_VALUE_ID, 5989, 5990);
  g->QuantizeTensor(5990, 8727, 5991, 2093);
  g->Dequantize(2093, 2094, 0.049212608486413956, 0);
  g->SplitDim(2094, 2095, 2, {8,256});
  g->FuseDims(2095, 2097, 1, 2);
  g->SplitDim(2097, 2096, 1, {8,1});
  g->Unary(ynn_unary_square, 2096, 2098);
  g->Reduce(ynn_reduce_sum, 2098, 7850, {3}, true);
  g->ShapeProduct(2098, 7849, {3});
  g->Binary(ynn_binary_divide, 7850, 7849, 2099);
  g->Binary(ynn_binary_add, 2099, 8779, 2101);
  g->Unary(ynn_unary_rsqrt, 2101, 2102);
  g->Binary(ynn_binary_multiply, 2096, 2102, 2103);
  g->Binary(ynn_binary_multiply, 2103, 9123, 2104);
  g->Slice(2104, 2105, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2104, 2106, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2106, 2107);
  g->Concat({2107,2105}, 2108, 3);
  g->Binary(ynn_binary_multiply, 2104, 3231, 2109);
  g->Binary(ynn_binary_multiply, 2108, 4329, 2110);
  g->Binary(ynn_binary_add, 2109, 2110, 2112);
}

// Scope: "Layer21 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9639, 2113, 0.0060269939713180065, 0);
  g->Dequantize(9663, 2114, 0.047244105488061905, 0);
  g->Slice(2112, 2115, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(2113, 2116, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(2114, 2117, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(2115, 2116, 2118, false, true);
  g->Mask(2118, 8812, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8812, 7854, {-1}, true);
  g->Binary(ynn_binary_subtract, 8812, 7854, 7851);
  g->Unary(ynn_unary_exp, 7851, 7852);
  g->Reduce(ynn_reduce_sum, 7852, 7855, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 7855, 7853);
  g->Binary(ynn_binary_multiply, 7852, 7853, 2119);
  g->Matmul(2119, 2117, 2120, false, false);
  g->Slice(2112, 2122, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(2113, 2123, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(2114, 2124, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(2122, 2123, 2125, false, true);
  g->Mask(2125, 8813, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8813, 7859, {-1}, true);
  g->Binary(ynn_binary_subtract, 8813, 7859, 7856);
  g->Unary(ynn_unary_exp, 7856, 7857);
  g->Reduce(ynn_reduce_sum, 7857, 7860, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 7860, 7858);
  g->Binary(ynn_binary_multiply, 7857, 7858, 2126);
  g->Matmul(2126, 2124, 2127, false, false);
  g->Concat({2120,2127}, 2128, 1);
}

// Scope: "Layer21 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(2128, 2130, 1, 2);
  g->SplitDim(2130, 2129, 1, {1,8});
  g->FuseDims(2129, 2131, 2, 2);
  g->Quantize(2131, 2133, 0.02325296215713024, 0);
  g->Transpose(9122, 6006, {1,0});
  g->Binary(ynn_binary_multiply, 6003, 6005, 6001);
  g->Dot(2133, 6006, YNN_INVALID_VALUE_ID, 6000, 1);
  g->DequantizeTensor(6000, YNN_INVALID_VALUE_ID, 6001, 6002);
  g->QuantizeTensor(6002, 8727, 6004, 2134);
  g->Dequantize(2134, 2135, 0.027936452999711037, 0);
}

// Scope: "Layer21 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2051, 2052);
  g->Reduce(ynn_reduce_sum, 2052, 7842, {2}, true);
  g->ShapeProduct(2052, 7841, {2});
  g->Binary(ynn_binary_divide, 7842, 7841, 2053);
  g->Binary(ynn_binary_add, 2053, 8779, 2054);
  g->Unary(ynn_unary_rsqrt, 2054, 2055);
  g->Binary(ynn_binary_multiply, 2051, 2055, 2056);
  g->Binary(ynn_binary_multiply, 2056, 9109, 2057);
  BuildLayer21AttentionKvProjection(ctx);
  BuildLayer21AttentionCacheUpdate(ctx);
  BuildLayer21AttentionQueryProjection(ctx);
  BuildLayer21AttentionSdpa(ctx);
  BuildLayer21AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2135, 2136);
  g->Reduce(ynn_reduce_sum, 2136, 7862, {2}, true);
  g->ShapeProduct(2136, 7861, {2});
  g->Binary(ynn_binary_divide, 7862, 7861, 2137);
  g->Binary(ynn_binary_add, 2137, 8779, 2138);
  g->Unary(ynn_unary_rsqrt, 2138, 2139);
  g->Binary(ynn_binary_multiply, 2135, 2139, 2140);
  g->Binary(ynn_binary_multiply, 2140, 9116, 2141);
  g->Binary(ynn_binary_add, 2141, 2051, 2142);
}

// Scope: "Layer21 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2142, 2146);
  g->Reduce(ynn_reduce_sum, 2146, 7864, {2}, true);
  g->ShapeProduct(2146, 7863, {2});
  g->Binary(ynn_binary_divide, 7864, 7863, 2147);
  g->Binary(ynn_binary_add, 2147, 8779, 2148);
  g->Unary(ynn_unary_rsqrt, 2148, 2149);
  g->Binary(ynn_binary_multiply, 2142, 2149, 2150);
  g->Binary(ynn_binary_multiply, 2150, 9119, 2151);
  g->Quantize(2151, 2152, 0.015300169587135315, 0);
  g->Transpose(9113, 6012, {1,0});
  g->Binary(ynn_binary_multiply, 6010, 6011, 6008);
  g->Dot(2152, 6012, YNN_INVALID_VALUE_ID, 6007, 1);
  g->DequantizeTensor(6007, YNN_INVALID_VALUE_ID, 6008, 6009);
  g->QuantizeTensor(6009, 8727, 5734, 2153);
  g->Dequantize(2153, 2154, 0.01771654561161995, 0);
  g->Transpose(9112, 6017, {1,0});
  g->Binary(ynn_binary_multiply, 6010, 6016, 6014);
  g->Dot(2152, 6017, YNN_INVALID_VALUE_ID, 6013, 1);
  g->DequantizeTensor(6013, YNN_INVALID_VALUE_ID, 6014, 6015);
  g->QuantizeTensor(6015, 8727, 5734, 2157);
  g->Dequantize(2157, 2158, 0.01771654561161995, 0);
  g->Polynomial(2158, 7867, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7867, 7868);
  g->Binary(ynn_binary_add, 7868, 7293, 7865);
  g->Binary(ynn_binary_multiply, 2158, 7305, 7866);
  g->Binary(ynn_binary_multiply, 7866, 7865, 2159);
  g->Binary(ynn_binary_multiply, 2154, 2159, 2160);
  g->Quantize(2160, 2161, 0.017962608486413956, 0);
  g->Transpose(9111, 6024, {1,0});
  g->Binary(ynn_binary_multiply, 6021, 6023, 6019);
  g->Dot(2161, 6024, YNN_INVALID_VALUE_ID, 6018, 1);
  g->DequantizeTensor(6018, YNN_INVALID_VALUE_ID, 6019, 6020);
  g->QuantizeTensor(6020, 8727, 6022, 2162);
  g->Dequantize(2162, 2163, 0.01586199924349785, 0);
  g->Unary(ynn_unary_square, 2163, 2164);
  g->Reduce(ynn_reduce_sum, 2164, 7870, {2}, true);
  g->ShapeProduct(2164, 7869, {2});
  g->Binary(ynn_binary_divide, 7870, 7869, 2165);
  g->Binary(ynn_binary_add, 2165, 8779, 2166);
  g->Unary(ynn_unary_rsqrt, 2166, 2168);
  g->Binary(ynn_binary_multiply, 2163, 2168, 2169);
  g->Binary(ynn_binary_multiply, 2169, 9117, 2170);
  g->Binary(ynn_binary_add, 2170, 2142, 2171);
}

// Scope: "Layer21 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(429, 2172, {0,0,21,0}, {-1,-1,1,-1});
  g->Reshape(2172, 2173, {1,1,256});
  g->Unary(ynn_unary_square, 2173, 2174);
  g->Reduce(ynn_reduce_sum, 2174, 7872, {2}, true);
  g->ShapeProduct(2174, 7871, {2});
  g->Binary(ynn_binary_divide, 7872, 7871, 2175);
  g->Binary(ynn_binary_add, 2175, 8779, 2176);
  g->Unary(ynn_unary_rsqrt, 2176, 2177);
  g->Binary(ynn_binary_multiply, 2173, 2177, 2179);
  g->Binary(ynn_binary_multiply, 2179, 9533, 2180);
  g->Binary(ynn_binary_multiply, 9548, 8783, 2181);
  g->Binary(ynn_binary_add, 2180, 2181, 2182);
  g->Binary(ynn_binary_multiply, 2182, 8777, 2183);
  g->Quantize(2171, 2184, 0.18123431503772736, 0);
  g->Transpose(9114, 6031, {1,0});
  g->Binary(ynn_binary_multiply, 6028, 6030, 6026);
  g->Dot(2184, 6031, YNN_INVALID_VALUE_ID, 6025, 1);
  g->DequantizeTensor(6025, YNN_INVALID_VALUE_ID, 6026, 6027);
  g->QuantizeTensor(6027, 8727, 6029, 2185);
  g->Dequantize(2185, 2186, 0.10531497001647949, 0);
  g->Polynomial(2186, 7877, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7877, 7878);
  g->Binary(ynn_binary_add, 7878, 7293, 7875);
  g->Binary(ynn_binary_multiply, 2186, 7305, 7876);
  g->Binary(ynn_binary_multiply, 7876, 7875, 2187);
  g->Binary(ynn_binary_multiply, 2187, 2183, 2188);
  g->Quantize(2188, 2190, 0.22933071851730347, 0);
  g->Transpose(9115, 6038, {1,0});
  g->Binary(ynn_binary_multiply, 6035, 6037, 6033);
  g->Dot(2190, 6038, YNN_INVALID_VALUE_ID, 6032, 1);
  g->DequantizeTensor(6032, YNN_INVALID_VALUE_ID, 6033, 6034);
  g->QuantizeTensor(6034, 8727, 6036, 2191);
  g->Dequantize(2191, 2192, 0.1351429969072342, 0);
  g->Unary(ynn_unary_square, 2192, 2193);
  g->Reduce(ynn_reduce_sum, 2193, 7880, {2}, true);
  g->ShapeProduct(2193, 7879, {2});
  g->Binary(ynn_binary_divide, 7880, 7879, 2194);
  g->Binary(ynn_binary_add, 2194, 8779, 2195);
  g->Unary(ynn_unary_rsqrt, 2195, 2196);
  g->Binary(ynn_binary_multiply, 2192, 2196, 2197);
  g->Binary(ynn_binary_multiply, 2197, 9118, 2198);
  g->Binary(ynn_binary_add, 2171, 2198, 2199);
  g->Binary(ynn_binary_multiply, 2199, 9110, 2201);
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
  g->Quantize(2207, 2208, 0.017071785405278206, 0);
  g->Transpose(9138, 6045, {1,0});
  g->Binary(ynn_binary_multiply, 6042, 6044, 6040);
  g->Dot(2208, 6045, YNN_INVALID_VALUE_ID, 6039, 1);
  g->DequantizeTensor(6039, YNN_INVALID_VALUE_ID, 6040, 6041);
  g->QuantizeTensor(6041, 8727, 6043, 2209);
  g->Dequantize(2209, 2210, 0.019808080047369003, 0);
  g->SplitDim(2210, 2212, 2, {2,256});
  g->FuseDims(2212, 2214, 1, 2);
  g->SplitDim(2214, 2213, 1, {2,1});
  g->Unary(ynn_unary_square, 2213, 2215);
  g->Reduce(ynn_reduce_sum, 2215, 7884, {3}, true);
  g->ShapeProduct(2215, 7883, {3});
  g->Binary(ynn_binary_divide, 7884, 7883, 2216);
  g->Binary(ynn_binary_add, 2216, 8779, 2217);
  g->Unary(ynn_unary_rsqrt, 2217, 2218);
  g->Binary(ynn_binary_multiply, 2213, 2218, 2219);
  g->Binary(ynn_binary_multiply, 2219, 9137, 2220);
  g->Slice(2220, 2221, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2220, 2222, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2222, 2224);
  g->Concat({2224,2221}, 2225, 3);
  g->Binary(ynn_binary_multiply, 2220, 3231, 2226);
  g->Binary(ynn_binary_multiply, 2225, 4329, 2227);
  g->Binary(ynn_binary_add, 2226, 2227, 2228);
  g->Transpose(9142, 6050, {1,0});
  g->Binary(ynn_binary_multiply, 6042, 6049, 6047);
  g->Dot(2208, 6050, YNN_INVALID_VALUE_ID, 6046, 1);
  g->DequantizeTensor(6046, YNN_INVALID_VALUE_ID, 6047, 6048);
  g->QuantizeTensor(6048, 8727, 6043, 2229);
  g->Dequantize(2229, 2230, 0.019808080047369003, 0);
  g->SplitDim(2230, 2231, 2, {2,256});
  g->FuseDims(2231, 2233, 1, 2);
  g->SplitDim(2233, 2232, 1, {2,1});
  g->Unary(ynn_unary_square, 2232, 2235);
  g->Reduce(ynn_reduce_sum, 2235, 7886, {3}, true);
  g->ShapeProduct(2235, 7885, {3});
  g->Binary(ynn_binary_divide, 7886, 7885, 2236);
  g->Binary(ynn_binary_add, 2236, 8779, 2237);
  g->Unary(ynn_unary_rsqrt, 2237, 2238);
  g->Binary(ynn_binary_multiply, 2232, 2238, 2239);
}

// Scope: "Layer22 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(2228, 2240, 0.0059552486054599285, 0);
  g->Append(8743, 2240, 9592, 2, s2, slinky::expr(int64_t{1}));
  g->View(9592, 9640, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(2239, 2241, 0.047244105488061905, 0);
  g->Append(8767, 2241, 9616, 2, s2, slinky::expr(int64_t{1}));
  g->View(9616, 9664, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer22 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(9141, 6056, {1,0});
  g->Binary(ynn_binary_multiply, 6042, 6055, 6052);
  g->Dot(2208, 6056, YNN_INVALID_VALUE_ID, 6051, 1);
  g->DequantizeTensor(6051, YNN_INVALID_VALUE_ID, 6052, 6053);
  g->QuantizeTensor(6053, 8727, 6054, 2243);
  g->Dequantize(2243, 2244, 0.0274360328912735, 0);
  g->SplitDim(2244, 2245, 2, {8,256});
  g->FuseDims(2245, 2247, 1, 2);
  g->SplitDim(2247, 2246, 1, {8,1});
  g->Unary(ynn_unary_square, 2246, 2248);
  g->Reduce(ynn_reduce_sum, 2248, 7888, {3}, true);
  g->ShapeProduct(2248, 7887, {3});
  g->Binary(ynn_binary_divide, 7888, 7887, 2249);
  g->Binary(ynn_binary_add, 2249, 8779, 2250);
  g->Unary(ynn_unary_rsqrt, 2250, 2251);
  g->Binary(ynn_binary_multiply, 2246, 2251, 2254);
  g->Binary(ynn_binary_multiply, 2254, 9140, 2255);
  g->Slice(2255, 2256, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2255, 2257, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2257, 2258);
  g->Concat({2258,2256}, 2259, 3);
  g->Binary(ynn_binary_multiply, 2255, 3231, 2260);
  g->Binary(ynn_binary_multiply, 2259, 4329, 2261);
  g->Binary(ynn_binary_add, 2260, 2261, 2262);
}

// Scope: "Layer22 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9640, 2263, 0.0059552486054599285, 0);
  g->Dequantize(9664, 2265, 0.047244105488061905, 0);
  g->Slice(2262, 2266, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(2263, 2267, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(2265, 2268, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(2266, 2267, 2269, false, true);
  g->Mask(2269, 8814, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8814, 7892, {-1}, true);
  g->Binary(ynn_binary_subtract, 8814, 7892, 7889);
  g->Unary(ynn_unary_exp, 7889, 7890);
  g->Reduce(ynn_reduce_sum, 7890, 7893, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 7893, 7891);
  g->Binary(ynn_binary_multiply, 7890, 7891, 2270);
  g->Matmul(2270, 2268, 2271, false, false);
  g->Slice(2262, 2272, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(2263, 2273, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(2265, 2275, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(2272, 2273, 2276, false, true);
  g->Mask(2276, 8815, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8815, 7897, {-1}, true);
  g->Binary(ynn_binary_subtract, 8815, 7897, 7894);
  g->Unary(ynn_unary_exp, 7894, 7895);
  g->Reduce(ynn_reduce_sum, 7895, 7898, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 7898, 7896);
  g->Binary(ynn_binary_multiply, 7895, 7896, 2277);
  g->Matmul(2277, 2275, 2278, false, false);
  g->Concat({2271,2278}, 2279, 1);
}

// Scope: "Layer22 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(2279, 2281, 1, 2);
  g->SplitDim(2281, 2280, 1, {1,8});
  g->FuseDims(2280, 2282, 2, 2);
  g->Quantize(2282, 2283, 0.020915362983942032, 0);
  g->Transpose(9139, 6063, {1,0});
  g->Binary(ynn_binary_multiply, 6060, 6062, 6058);
  g->Dot(2283, 6063, YNN_INVALID_VALUE_ID, 6057, 1);
  g->DequantizeTensor(6057, YNN_INVALID_VALUE_ID, 6058, 6059);
  g->QuantizeTensor(6059, 8727, 6061, 2284);
  g->Dequantize(2284, 2286, 0.03860917314887047, 0);
}

// Scope: "Layer22 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2201, 2202);
  g->Reduce(ynn_reduce_sum, 2202, 7882, {2}, true);
  g->ShapeProduct(2202, 7881, {2});
  g->Binary(ynn_binary_divide, 7882, 7881, 2203);
  g->Binary(ynn_binary_add, 2203, 8779, 2204);
  g->Unary(ynn_unary_rsqrt, 2204, 2205);
  g->Binary(ynn_binary_multiply, 2201, 2205, 2206);
  g->Binary(ynn_binary_multiply, 2206, 9126, 2207);
  BuildLayer22AttentionKvProjection(ctx);
  BuildLayer22AttentionCacheUpdate(ctx);
  BuildLayer22AttentionQueryProjection(ctx);
  BuildLayer22AttentionSdpa(ctx);
  BuildLayer22AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2286, 2287);
  g->Reduce(ynn_reduce_sum, 2287, 7900, {2}, true);
  g->ShapeProduct(2287, 7899, {2});
  g->Binary(ynn_binary_divide, 7900, 7899, 2288);
  g->Binary(ynn_binary_add, 2288, 8779, 2289);
  g->Unary(ynn_unary_rsqrt, 2289, 2290);
  g->Binary(ynn_binary_multiply, 2286, 2290, 2291);
  g->Binary(ynn_binary_multiply, 2291, 9133, 2292);
  g->Binary(ynn_binary_add, 2292, 2201, 2293);
}

// Scope: "Layer22 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2293, 2294);
  g->Reduce(ynn_reduce_sum, 2294, 7902, {2}, true);
  g->ShapeProduct(2294, 7901, {2});
  g->Binary(ynn_binary_divide, 7902, 7901, 2295);
  g->Binary(ynn_binary_add, 2295, 8779, 2297);
  g->Unary(ynn_unary_rsqrt, 2297, 2298);
  g->Binary(ynn_binary_multiply, 2293, 2298, 2299);
  g->Binary(ynn_binary_multiply, 2299, 9136, 2300);
  g->Quantize(2300, 2301, 0.014675655402243137, 0);
  g->Transpose(9130, 6070, {1,0});
  g->Binary(ynn_binary_multiply, 6067, 6069, 6065);
  g->Dot(2301, 6070, YNN_INVALID_VALUE_ID, 6064, 1);
  g->DequantizeTensor(6064, YNN_INVALID_VALUE_ID, 6065, 6066);
  g->QuantizeTensor(6066, 8727, 6068, 2302);
  g->Dequantize(2302, 2303, 0.017593514174222946, 0);
  g->Transpose(9129, 6075, {1,0});
  g->Binary(ynn_binary_multiply, 6067, 6074, 6072);
  g->Dot(2301, 6075, YNN_INVALID_VALUE_ID, 6071, 1);
  g->DequantizeTensor(6071, YNN_INVALID_VALUE_ID, 6072, 6073);
  g->QuantizeTensor(6073, 8727, 6068, 2304);
  g->Dequantize(2304, 2305, 0.017593514174222946, 0);
  g->Polynomial(2305, 7905, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7905, 7906);
  g->Binary(ynn_binary_add, 7906, 7293, 7903);
  g->Binary(ynn_binary_multiply, 2305, 7305, 7904);
  g->Binary(ynn_binary_multiply, 7904, 7903, 2306);
  g->Binary(ynn_binary_multiply, 2303, 2306, 2307);
  g->Quantize(2307, 2308, 0.009842529892921448, 0);
  g->Transpose(9128, 6082, {1,0});
  g->Binary(ynn_binary_multiply, 6079, 6081, 6077);
  g->Dot(2308, 6082, YNN_INVALID_VALUE_ID, 6076, 1);
  g->DequantizeTensor(6076, YNN_INVALID_VALUE_ID, 6077, 6078);
  g->QuantizeTensor(6078, 8727, 6080, 2309);
  g->Dequantize(2309, 2310, 0.007876119576394558, 0);
  g->Unary(ynn_unary_square, 2310, 2311);
  g->Reduce(ynn_reduce_sum, 2311, 7908, {2}, true);
  g->ShapeProduct(2311, 7907, {2});
  g->Binary(ynn_binary_divide, 7908, 7907, 2312);
  g->Binary(ynn_binary_add, 2312, 8779, 2313);
  g->Unary(ynn_unary_rsqrt, 2313, 2314);
  g->Binary(ynn_binary_multiply, 2310, 2314, 2315);
  g->Binary(ynn_binary_multiply, 2315, 9134, 2317);
  g->Binary(ynn_binary_add, 2317, 2293, 2318);
}

// Scope: "Layer22 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(429, 2319, {0,0,22,0}, {-1,-1,1,-1});
  g->Reshape(2319, 2320, {1,1,256});
  g->Unary(ynn_unary_square, 2320, 2321);
  g->Reduce(ynn_reduce_sum, 2321, 7910, {2}, true);
  g->ShapeProduct(2321, 7909, {2});
  g->Binary(ynn_binary_divide, 7910, 7909, 2322);
  g->Binary(ynn_binary_add, 2322, 8779, 2323);
  g->Unary(ynn_unary_rsqrt, 2323, 2324);
  g->Binary(ynn_binary_multiply, 2320, 2324, 2325);
  g->Binary(ynn_binary_multiply, 2325, 9533, 2326);
  g->Binary(ynn_binary_multiply, 9549, 8783, 2328);
  g->Binary(ynn_binary_add, 2326, 2328, 2329);
  g->Binary(ynn_binary_multiply, 2329, 8777, 2330);
  g->Quantize(2318, 2331, 0.28123560547828674, 0);
  g->Transpose(9131, 6094, {1,0});
  g->Binary(ynn_binary_multiply, 6091, 6093, 6089);
  g->Dot(2331, 6094, YNN_INVALID_VALUE_ID, 6088, 1);
  g->DequantizeTensor(6088, YNN_INVALID_VALUE_ID, 6089, 6090);
  g->QuantizeTensor(6090, 8727, 6092, 2332);
  g->Dequantize(2332, 2333, 0.5590550899505615, 0);
  g->Polynomial(2333, 7913, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7913, 7914);
  g->Binary(ynn_binary_add, 7914, 7293, 7911);
  g->Binary(ynn_binary_multiply, 2333, 7305, 7912);
  g->Binary(ynn_binary_multiply, 7912, 7911, 2334);
  g->Binary(ynn_binary_multiply, 2334, 2330, 2335);
  g->Quantize(2335, 2336, 0.6968504190444946, 0);
  g->Transpose(9132, 6101, {1,0});
  g->Binary(ynn_binary_multiply, 6098, 6100, 6096);
  g->Dot(2336, 6101, YNN_INVALID_VALUE_ID, 6095, 1);
  g->DequantizeTensor(6095, YNN_INVALID_VALUE_ID, 6096, 6097);
  g->QuantizeTensor(6097, 8727, 6099, 2337);
  g->Dequantize(2337, 2339, 0.38523077964782715, 0);
  g->Unary(ynn_unary_square, 2339, 2340);
  g->Reduce(ynn_reduce_sum, 2340, 7916, {2}, true);
  g->ShapeProduct(2340, 7915, {2});
  g->Binary(ynn_binary_divide, 7916, 7915, 2341);
  g->Binary(ynn_binary_add, 2341, 8779, 2342);
  g->Unary(ynn_unary_rsqrt, 2342, 2343);
  g->Binary(ynn_binary_multiply, 2339, 2343, 2344);
  g->Binary(ynn_binary_multiply, 2344, 9135, 2345);
  g->Binary(ynn_binary_add, 2318, 2345, 2346);
  g->Binary(ynn_binary_multiply, 2346, 9127, 2347);
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
  g->Quantize(2355, 2356, 0.062325432896614075, 0);
  g->Transpose(9155, 6108, {1,0});
  g->Binary(ynn_binary_multiply, 6105, 6107, 6103);
  g->Dot(2356, 6108, YNN_INVALID_VALUE_ID, 6102, 1);
  g->DequantizeTensor(6102, YNN_INVALID_VALUE_ID, 6103, 6104);
  g->QuantizeTensor(6104, 8727, 6106, 2357);
  g->Dequantize(2357, 2358, 0.05413386970758438, 0);
  g->SplitDim(2358, 2359, 2, {2,512});
  g->FuseDims(2359, 2361, 1, 2);
  g->SplitDim(2361, 2360, 1, {2,1});
  g->Unary(ynn_unary_square, 2360, 2364);
  g->Reduce(ynn_reduce_sum, 2364, 7920, {3}, true);
  g->ShapeProduct(2364, 7919, {3});
  g->Binary(ynn_binary_divide, 7920, 7919, 2365);
  g->Binary(ynn_binary_add, 2365, 8779, 2366);
  g->Unary(ynn_unary_rsqrt, 2366, 2367);
  g->Binary(ynn_binary_multiply, 2360, 2367, 2368);
  g->Binary(ynn_binary_multiply, 2368, 9154, 2369);
  g->Slice(2369, 2370, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(2369, 2371, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 2371, 2372);
  g->Concat({2372,2370}, 2373, 3);
  g->Binary(ynn_binary_multiply, 2369, 4959, 2375);
  g->Binary(ynn_binary_multiply, 2373, 2, 2376);
  g->Binary(ynn_binary_add, 2375, 2376, 2377);
  g->Transpose(9159, 6113, {1,0});
  g->Binary(ynn_binary_multiply, 6105, 6112, 6110);
  g->Dot(2356, 6113, YNN_INVALID_VALUE_ID, 6109, 1);
  g->DequantizeTensor(6109, YNN_INVALID_VALUE_ID, 6110, 6111);
  g->QuantizeTensor(6111, 8727, 6106, 2378);
  g->Dequantize(2378, 2379, 0.05413386970758438, 0);
  g->SplitDim(2379, 2380, 2, {2,512});
  g->FuseDims(2380, 2382, 1, 2);
  g->SplitDim(2382, 2381, 1, {2,1});
  g->Unary(ynn_unary_square, 2381, 2383);
  g->Reduce(ynn_reduce_sum, 2383, 7924, {3}, true);
  g->ShapeProduct(2383, 7923, {3});
  g->Binary(ynn_binary_divide, 7924, 7923, 2384);
  g->Binary(ynn_binary_add, 2384, 8779, 2386);
  g->Unary(ynn_unary_rsqrt, 2386, 2387);
  g->Binary(ynn_binary_multiply, 2381, 2387, 2388);
}

// Scope: "Layer23 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(2377, 2389, 0.001091228099539876, 0);
  g->Append(8744, 2389, 9593, 2, s2, slinky::expr(int64_t{1}));
  g->View(9593, 9641, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(2388, 2390, 0.01785714365541935, 0);
  g->Append(8768, 2390, 9617, 2, s2, slinky::expr(int64_t{1}));
  g->View(9617, 9665, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{1}) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer23 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(9158, 6119, {1,0});
  g->Binary(ynn_binary_multiply, 6105, 6118, 6115);
  g->Dot(2356, 6119, YNN_INVALID_VALUE_ID, 6114, 1);
  g->DequantizeTensor(6114, YNN_INVALID_VALUE_ID, 6115, 6116);
  g->QuantizeTensor(6116, 8727, 6117, 2392);
  g->Dequantize(2392, 2393, 0.08661418408155441, 0);
  g->SplitDim(2393, 2394, 2, {8,512});
  g->FuseDims(2394, 2396, 1, 2);
  g->SplitDim(2396, 2395, 1, {8,1});
  g->Unary(ynn_unary_square, 2395, 2397);
  g->Reduce(ynn_reduce_sum, 2397, 7926, {3}, true);
  g->ShapeProduct(2397, 7925, {3});
  g->Binary(ynn_binary_divide, 7926, 7925, 2398);
  g->Binary(ynn_binary_add, 2398, 8779, 2399);
  g->Unary(ynn_unary_rsqrt, 2399, 2400);
  g->Binary(ynn_binary_multiply, 2395, 2400, 2401);
  g->Binary(ynn_binary_multiply, 2401, 9157, 2402);
  g->Slice(2402, 2404, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(2402, 2405, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 2405, 2406);
  g->Concat({2406,2404}, 2407, 3);
  g->Binary(ynn_binary_multiply, 2402, 4959, 2408);
  g->Binary(ynn_binary_multiply, 2407, 2, 2409);
  g->Binary(ynn_binary_add, 2408, 2409, 2410);
}

// Scope: "Layer23 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9641, 2411, 0.001091228099539876, 0);
  g->Dequantize(9665, 2412, 0.01785714365541935, 0);
  g->Slice(2410, 2413, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(2411, 2415, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(2412, 2416, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(2413, 2415, 2417, false, true);
  g->Mask(2417, 8816, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 8816, 7930, {-1}, true);
  g->Binary(ynn_binary_subtract, 8816, 7930, 7927);
  g->Unary(ynn_unary_exp, 7927, 7928);
  g->Reduce(ynn_reduce_sum, 7928, 7931, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 7931, 7929);
  g->Binary(ynn_binary_multiply, 7928, 7929, 2418);
  g->Matmul(2418, 2416, 2419, false, false);
  g->Slice(2410, 2420, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(2411, 2421, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(2412, 2422, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(2420, 2421, 2423, false, true);
  g->Mask(2423, 8817, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 8817, 7935, {-1}, true);
  g->Binary(ynn_binary_subtract, 8817, 7935, 7932);
  g->Unary(ynn_unary_exp, 7932, 7933);
  g->Reduce(ynn_reduce_sum, 7933, 7936, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 7936, 7934);
  g->Binary(ynn_binary_multiply, 7933, 7934, 2424);
  g->Matmul(2424, 2422, 2425, false, false);
  g->Concat({2419,2425}, 2426, 1);
}

// Scope: "Layer23 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(2426, 2428, 1, 2);
  g->SplitDim(2428, 2427, 1, {1,8});
  g->FuseDims(2427, 2429, 2, 2);
  g->Quantize(2429, 2430, 0.01734744943678379, 0);
  g->Transpose(9156, 6126, {1,0});
  g->Binary(ynn_binary_multiply, 6123, 6125, 6121);
  g->Dot(2430, 6126, YNN_INVALID_VALUE_ID, 6120, 1);
  g->DequantizeTensor(6120, YNN_INVALID_VALUE_ID, 6121, 6122);
  g->QuantizeTensor(6122, 8727, 6124, 2431);
  g->Dequantize(2431, 2432, 0.03438705950975418, 0);
}

// Scope: "Layer23 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2347, 2348);
  g->Reduce(ynn_reduce_sum, 2348, 7918, {2}, true);
  g->ShapeProduct(2348, 7917, {2});
  g->Binary(ynn_binary_divide, 7918, 7917, 2351);
  g->Binary(ynn_binary_add, 2351, 8779, 2352);
  g->Unary(ynn_unary_rsqrt, 2352, 2353);
  g->Binary(ynn_binary_multiply, 2347, 2353, 2354);
  g->Binary(ynn_binary_multiply, 2354, 9143, 2355);
  BuildLayer23AttentionKvProjection(ctx);
  BuildLayer23AttentionCacheUpdate(ctx);
  BuildLayer23AttentionQueryProjection(ctx);
  BuildLayer23AttentionSdpa(ctx);
  BuildLayer23AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2432, 2433);
  g->Reduce(ynn_reduce_sum, 2433, 7938, {2}, true);
  g->ShapeProduct(2433, 7937, {2});
  g->Binary(ynn_binary_divide, 7938, 7937, 2434);
  g->Binary(ynn_binary_add, 2434, 8779, 2435);
  g->Unary(ynn_unary_rsqrt, 2435, 2436);
  g->Binary(ynn_binary_multiply, 2432, 2436, 2437);
  g->Binary(ynn_binary_multiply, 2437, 9150, 2438);
  g->Binary(ynn_binary_add, 2438, 2347, 2439);
}

// Scope: "Layer23 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2439, 2440);
  g->Reduce(ynn_reduce_sum, 2440, 7940, {2}, true);
  g->ShapeProduct(2440, 7939, {2});
  g->Binary(ynn_binary_divide, 7940, 7939, 2441);
  g->Binary(ynn_binary_add, 2441, 8779, 2442);
  g->Unary(ynn_unary_rsqrt, 2442, 2443);
  g->Binary(ynn_binary_multiply, 2439, 2443, 2445);
  g->Binary(ynn_binary_multiply, 2445, 9153, 2446);
  g->Quantize(2446, 2447, 0.01334653701633215, 0);
  g->Transpose(9147, 6133, {1,0});
  g->Binary(ynn_binary_multiply, 6130, 6132, 6128);
  g->Dot(2447, 6133, YNN_INVALID_VALUE_ID, 6127, 1);
  g->DequantizeTensor(6127, YNN_INVALID_VALUE_ID, 6128, 6129);
  g->QuantizeTensor(6129, 8727, 6131, 2448);
  g->Dequantize(2448, 2449, 0.01660926081240177, 0);
  g->Transpose(9146, 6138, {1,0});
  g->Binary(ynn_binary_multiply, 6130, 6137, 6135);
  g->Dot(2447, 6138, YNN_INVALID_VALUE_ID, 6134, 1);
  g->DequantizeTensor(6134, YNN_INVALID_VALUE_ID, 6135, 6136);
  g->QuantizeTensor(6136, 8727, 6131, 2450);
  g->Dequantize(2450, 2451, 0.01660926081240177, 0);
  g->Polynomial(2451, 7943, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7943, 7944);
  g->Binary(ynn_binary_add, 7944, 7293, 7941);
  g->Binary(ynn_binary_multiply, 2451, 7305, 7942);
  g->Binary(ynn_binary_multiply, 7942, 7941, 2452);
  g->Binary(ynn_binary_multiply, 2449, 2452, 2453);
  g->Quantize(2453, 2454, 0.015625009313225746, 0);
  g->Transpose(9145, 6145, {1,0});
  g->Binary(ynn_binary_multiply, 6142, 6144, 6140);
  g->Dot(2454, 6145, YNN_INVALID_VALUE_ID, 6139, 1);
  g->DequantizeTensor(6139, YNN_INVALID_VALUE_ID, 6140, 6141);
  g->QuantizeTensor(6141, 8727, 6143, 2455);
  g->Dequantize(2455, 2456, 0.011555495671927929, 0);
  g->Unary(ynn_unary_square, 2456, 2457);
  g->Reduce(ynn_reduce_sum, 2457, 7946, {2}, true);
  g->ShapeProduct(2457, 7945, {2});
  g->Binary(ynn_binary_divide, 7946, 7945, 2458);
  g->Binary(ynn_binary_add, 2458, 8779, 2459);
  g->Unary(ynn_unary_rsqrt, 2459, 2460);
  g->Binary(ynn_binary_multiply, 2456, 2460, 2461);
  g->Binary(ynn_binary_multiply, 2461, 9151, 2462);
  g->Binary(ynn_binary_add, 2462, 2439, 2463);
}

// Scope: "Layer23 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(429, 2465, {0,0,23,0}, {-1,-1,1,-1});
  g->Reshape(2465, 2466, {1,1,256});
  g->Unary(ynn_unary_square, 2466, 2467);
  g->Reduce(ynn_reduce_sum, 2467, 7948, {2}, true);
  g->ShapeProduct(2467, 7947, {2});
  g->Binary(ynn_binary_divide, 7948, 7947, 2468);
  g->Binary(ynn_binary_add, 2468, 8779, 2469);
  g->Unary(ynn_unary_rsqrt, 2469, 2470);
  g->Binary(ynn_binary_multiply, 2466, 2470, 2471);
  g->Binary(ynn_binary_multiply, 2471, 9533, 2472);
  g->Binary(ynn_binary_multiply, 9550, 8783, 2473);
  g->Binary(ynn_binary_add, 2472, 2473, 2474);
  g->Binary(ynn_binary_multiply, 2474, 8777, 2475);
  g->Quantize(2463, 2476, 1.4053089618682861, 0);
  g->Transpose(9148, 6152, {1,0});
  g->Binary(ynn_binary_multiply, 6149, 6151, 6147);
  g->Dot(2476, 6152, YNN_INVALID_VALUE_ID, 6146, 1);
  g->DequantizeTensor(6146, YNN_INVALID_VALUE_ID, 6147, 6148);
  g->QuantizeTensor(6148, 8727, 6150, 2477);
  g->Dequantize(2477, 2478, 0.08169291913509369, 0);
  g->Polynomial(2478, 7951, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7951, 7952);
  g->Binary(ynn_binary_add, 7952, 7293, 7949);
  g->Binary(ynn_binary_multiply, 2478, 7305, 7950);
  g->Binary(ynn_binary_multiply, 7950, 7949, 2479);
  g->Binary(ynn_binary_multiply, 2479, 2475, 2480);
  g->Quantize(2480, 2481, 0.29921260476112366, 0);
  g->Transpose(9149, 6159, {1,0});
  g->Binary(ynn_binary_multiply, 6156, 6158, 6154);
  g->Dot(2481, 6159, YNN_INVALID_VALUE_ID, 6153, 1);
  g->DequantizeTensor(6153, YNN_INVALID_VALUE_ID, 6154, 6155);
  g->QuantizeTensor(6155, 8727, 6157, 2482);
  g->Dequantize(2482, 2483, 0.09225650876760483, 0);
  g->Unary(ynn_unary_square, 2483, 2484);
  g->Reduce(ynn_reduce_sum, 2484, 7954, {2}, true);
  g->ShapeProduct(2484, 7953, {2});
  g->Binary(ynn_binary_divide, 7954, 7953, 2486);
  g->Binary(ynn_binary_add, 2486, 8779, 2487);
  g->Unary(ynn_unary_rsqrt, 2487, 2488);
  g->Binary(ynn_binary_multiply, 2483, 2488, 2489);
  g->Binary(ynn_binary_multiply, 2489, 9152, 2490);
  g->Binary(ynn_binary_add, 2463, 2490, 2491);
  g->Binary(ynn_binary_multiply, 2491, 9144, 2492);
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
  g->Quantize(2499, 2500, 0.2720024883747101, 0);
  g->Transpose(9173, 6172, {1,0});
  g->Binary(ynn_binary_multiply, 6169, 6171, 6167);
  g->Dot(2500, 6172, YNN_INVALID_VALUE_ID, 6166, 1);
  g->DequantizeTensor(6166, YNN_INVALID_VALUE_ID, 6167, 6168);
  g->QuantizeTensor(6168, 8727, 6170, 2501);
  g->Dequantize(2501, 2502, 0.3169291317462921, 0);
  g->SplitDim(2502, 2503, 2, {8,256});
  g->FuseDims(2503, 2505, 1, 2);
  g->SplitDim(2505, 2504, 1, {8,1});
  g->Unary(ynn_unary_square, 2504, 2506);
  g->Reduce(ynn_reduce_sum, 2506, 7958, {3}, true);
  g->ShapeProduct(2506, 7957, {3});
  g->Binary(ynn_binary_divide, 7958, 7957, 2507);
  g->Binary(ynn_binary_add, 2507, 8779, 2509);
  g->Unary(ynn_unary_rsqrt, 2509, 2510);
  g->Binary(ynn_binary_multiply, 2504, 2510, 2511);
  g->Binary(ynn_binary_multiply, 2511, 9172, 2512);
  g->Slice(2512, 2513, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2512, 2514, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2514, 2515);
  g->Concat({2515,2513}, 2516, 3);
  g->Binary(ynn_binary_multiply, 2512, 3231, 2517);
  g->Binary(ynn_binary_multiply, 2516, 4329, 2518);
  g->Binary(ynn_binary_add, 2517, 2518, 2521);
}

// Scope: "Layer24 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer24AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9640, 2522, 0.0059552486054599285, 0);
  g->Dequantize(9664, 2523, 0.047244105488061905, 0);
  g->Slice(2521, 2524, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(2522, 2525, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(2523, 2526, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(2524, 2525, 2527, false, true);
  g->Mask(2527, 8818, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8818, 7962, {-1}, true);
  g->Binary(ynn_binary_subtract, 8818, 7962, 7959);
  g->Unary(ynn_unary_exp, 7959, 7960);
  g->Reduce(ynn_reduce_sum, 7960, 7963, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 7963, 7961);
  g->Binary(ynn_binary_multiply, 7960, 7961, 2528);
  g->Matmul(2528, 2526, 2529, false, false);
  g->Slice(2521, 2531, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(2522, 2532, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(2523, 2533, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(2531, 2532, 2534, false, true);
  g->Mask(2534, 8819, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8819, 7967, {-1}, true);
  g->Binary(ynn_binary_subtract, 8819, 7967, 7964);
  g->Unary(ynn_unary_exp, 7964, 7965);
  g->Reduce(ynn_reduce_sum, 7965, 7968, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 7968, 7966);
  g->Binary(ynn_binary_multiply, 7965, 7966, 2535);
  g->Matmul(2535, 2533, 2536, false, false);
  g->Concat({2529,2536}, 2537, 1);
}

// Scope: "Layer24 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer24AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(2537, 2539, 1, 2);
  g->SplitDim(2539, 2538, 1, {1,8});
  g->FuseDims(2538, 2540, 2, 2);
  g->Quantize(2540, 2542, 0.020177174359560013, 0);
  g->Transpose(9171, 6179, {1,0});
  g->Binary(ynn_binary_multiply, 6176, 6178, 6174);
  g->Dot(2542, 6179, YNN_INVALID_VALUE_ID, 6173, 1);
  g->DequantizeTensor(6173, YNN_INVALID_VALUE_ID, 6174, 6175);
  g->QuantizeTensor(6175, 8727, 6177, 2543);
  g->Dequantize(2543, 2544, 0.06057490408420563, 0);
}

// Scope: "Layer24 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer24Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2492, 2493);
  g->Reduce(ynn_reduce_sum, 2493, 7956, {2}, true);
  g->ShapeProduct(2493, 7955, {2});
  g->Binary(ynn_binary_divide, 7956, 7955, 2494);
  g->Binary(ynn_binary_add, 2494, 8779, 2495);
  g->Unary(ynn_unary_rsqrt, 2495, 2497);
  g->Binary(ynn_binary_multiply, 2492, 2497, 2498);
  g->Binary(ynn_binary_multiply, 2498, 9160, 2499);
  BuildLayer24AttentionQueryProjection(ctx);
  BuildLayer24AttentionSdpa(ctx);
  BuildLayer24AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2544, 2545);
  g->Reduce(ynn_reduce_sum, 2545, 7972, {2}, true);
  g->ShapeProduct(2545, 7971, {2});
  g->Binary(ynn_binary_divide, 7972, 7971, 2546);
  g->Binary(ynn_binary_add, 2546, 8779, 2547);
  g->Unary(ynn_unary_rsqrt, 2547, 2548);
  g->Binary(ynn_binary_multiply, 2544, 2548, 2549);
  g->Binary(ynn_binary_multiply, 2549, 9167, 2550);
  g->Binary(ynn_binary_add, 2550, 2492, 2551);
}

// Scope: "Layer24 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer24Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2551, 2553);
  g->Reduce(ynn_reduce_sum, 2553, 7974, {2}, true);
  g->ShapeProduct(2553, 7973, {2});
  g->Binary(ynn_binary_divide, 7974, 7973, 2554);
  g->Binary(ynn_binary_add, 2554, 8779, 2555);
  g->Unary(ynn_unary_rsqrt, 2555, 2556);
  g->Binary(ynn_binary_multiply, 2551, 2556, 2557);
  g->Binary(ynn_binary_multiply, 2557, 9170, 2558);
  g->Quantize(2558, 2559, 0.018166832625865936, 0);
  g->Transpose(9164, 6186, {1,0});
  g->Binary(ynn_binary_multiply, 6183, 6185, 6181);
  g->Dot(2559, 6186, YNN_INVALID_VALUE_ID, 6180, 1);
  g->DequantizeTensor(6180, YNN_INVALID_VALUE_ID, 6181, 6182);
  g->QuantizeTensor(6182, 8727, 6184, 2560);
  g->Dequantize(2560, 2561, 0.017224417999386787, 0);
  g->Transpose(9163, 6191, {1,0});
  g->Binary(ynn_binary_multiply, 6183, 6190, 6188);
  g->Dot(2559, 6191, YNN_INVALID_VALUE_ID, 6187, 1);
  g->DequantizeTensor(6187, YNN_INVALID_VALUE_ID, 6188, 6189);
  g->QuantizeTensor(6189, 8727, 6184, 2563);
  g->Dequantize(2563, 2564, 0.017224417999386787, 0);
  g->Polynomial(2564, 7977, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7977, 7978);
  g->Binary(ynn_binary_add, 7978, 7293, 7975);
  g->Binary(ynn_binary_multiply, 2564, 7305, 7976);
  g->Binary(ynn_binary_multiply, 7976, 7975, 2565);
  g->Binary(ynn_binary_multiply, 2561, 2565, 2566);
  g->Quantize(2566, 2567, 0.01697835512459278, 0);
  g->Transpose(9162, 6198, {1,0});
  g->Binary(ynn_binary_multiply, 6195, 6197, 6193);
  g->Dot(2567, 6198, YNN_INVALID_VALUE_ID, 6192, 1);
  g->DequantizeTensor(6192, YNN_INVALID_VALUE_ID, 6193, 6194);
  g->QuantizeTensor(6194, 8727, 6196, 2568);
  g->Dequantize(2568, 2569, 0.010266699828207493, 0);
  g->Unary(ynn_unary_square, 2569, 2570);
  g->Reduce(ynn_reduce_sum, 2570, 7980, {2}, true);
  g->ShapeProduct(2570, 7979, {2});
  g->Binary(ynn_binary_divide, 7980, 7979, 2571);
  g->Binary(ynn_binary_add, 2571, 8779, 2572);
  g->Unary(ynn_unary_rsqrt, 2572, 2575);
  g->Binary(ynn_binary_multiply, 2569, 2575, 2576);
  g->Binary(ynn_binary_multiply, 2576, 9168, 2577);
  g->Binary(ynn_binary_add, 2577, 2551, 2578);
}

// Scope: "Layer24 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer24PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(429, 2579, {0,0,24,0}, {-1,-1,1,-1});
  g->Reshape(2579, 2580, {1,1,256});
  g->Unary(ynn_unary_square, 2580, 2581);
  g->Reduce(ynn_reduce_sum, 2581, 7982, {2}, true);
  g->ShapeProduct(2581, 7981, {2});
  g->Binary(ynn_binary_divide, 7982, 7981, 2582);
  g->Binary(ynn_binary_add, 2582, 8779, 2583);
  g->Unary(ynn_unary_rsqrt, 2583, 2584);
  g->Binary(ynn_binary_multiply, 2580, 2584, 2586);
  g->Binary(ynn_binary_multiply, 2586, 9533, 2587);
  g->Binary(ynn_binary_multiply, 9551, 8783, 2588);
  g->Binary(ynn_binary_add, 2587, 2588, 2589);
  g->Binary(ynn_binary_multiply, 2589, 8777, 2590);
  g->Quantize(2578, 2591, 0.23872995376586914, 0);
  g->Transpose(9165, 6205, {1,0});
  g->Binary(ynn_binary_multiply, 6202, 6204, 6200);
  g->Dot(2591, 6205, YNN_INVALID_VALUE_ID, 6199, 1);
  g->DequantizeTensor(6199, YNN_INVALID_VALUE_ID, 6200, 6201);
  g->QuantizeTensor(6201, 8727, 6203, 2592);
  g->Dequantize(2592, 2593, 0.22736221551895142, 0);
  g->Polynomial(2593, 7985, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 7985, 7986);
  g->Binary(ynn_binary_add, 7986, 7293, 7983);
  g->Binary(ynn_binary_multiply, 2593, 7305, 7984);
  g->Binary(ynn_binary_multiply, 7984, 7983, 2594);
  g->Binary(ynn_binary_multiply, 2594, 2590, 2595);
  g->Quantize(2595, 2597, 2.0629920959472656, 0);
  g->Transpose(9166, 6212, {1,0});
  g->Binary(ynn_binary_multiply, 6209, 6211, 6207);
  g->Dot(2597, 6212, YNN_INVALID_VALUE_ID, 6206, 1);
  g->DequantizeTensor(6206, YNN_INVALID_VALUE_ID, 6207, 6208);
  g->QuantizeTensor(6208, 8727, 6210, 2598);
  g->Dequantize(2598, 2599, 0.26288625597953796, 0);
  g->Unary(ynn_unary_square, 2599, 2600);
  g->Reduce(ynn_reduce_sum, 2600, 7988, {2}, true);
  g->ShapeProduct(2600, 7987, {2});
  g->Binary(ynn_binary_divide, 7988, 7987, 2601);
  g->Binary(ynn_binary_add, 2601, 8779, 2602);
  g->Unary(ynn_unary_rsqrt, 2602, 2603);
  g->Binary(ynn_binary_multiply, 2599, 2603, 2604);
  g->Binary(ynn_binary_multiply, 2604, 9169, 2605);
  g->Binary(ynn_binary_add, 2578, 2605, 2606);
  g->Binary(ynn_binary_multiply, 2606, 9161, 2608);
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
  g->Quantize(2614, 2615, 0.38746458292007446, 0);
  g->Transpose(9187, 6219, {1,0});
  g->Binary(ynn_binary_multiply, 6216, 6218, 6214);
  g->Dot(2615, 6219, YNN_INVALID_VALUE_ID, 6213, 1);
  g->DequantizeTensor(6213, YNN_INVALID_VALUE_ID, 6214, 6215);
  g->QuantizeTensor(6215, 8727, 6217, 2616);
  g->Dequantize(2616, 2617, 0.5039370059967041, 0);
  g->SplitDim(2617, 2619, 2, {8,256});
  g->FuseDims(2619, 2621, 1, 2);
  g->SplitDim(2621, 2620, 1, {8,1});
  g->Unary(ynn_unary_square, 2620, 2622);
  g->Reduce(ynn_reduce_sum, 2622, 7992, {3}, true);
  g->ShapeProduct(2622, 7991, {3});
  g->Binary(ynn_binary_divide, 7992, 7991, 2623);
  g->Binary(ynn_binary_add, 2623, 8779, 2624);
  g->Unary(ynn_unary_rsqrt, 2624, 2625);
  g->Binary(ynn_binary_multiply, 2620, 2625, 2626);
  g->Binary(ynn_binary_multiply, 2626, 9186, 2627);
  g->Slice(2627, 2628, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2627, 2629, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2629, 2631);
  g->Concat({2631,2628}, 2632, 3);
  g->Binary(ynn_binary_multiply, 2627, 3231, 2633);
  g->Binary(ynn_binary_multiply, 2632, 4329, 2634);
  g->Binary(ynn_binary_add, 2633, 2634, 2635);
}

// Scope: "Layer25 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer25AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(9640, 2636, 0.0059552486054599285, 0);
  g->Dequantize(9664, 2637, 0.047244105488061905, 0);
  g->Slice(2635, 2638, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(2636, 2639, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(2637, 2640, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(2638, 2639, 2642, false, true);
  g->Mask(2642, 8820, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8820, 7996, {-1}, true);
  g->Binary(ynn_binary_subtract, 8820, 7996, 7993);
  g->Unary(ynn_unary_exp, 7993, 7994);
  g->Reduce(ynn_reduce_sum, 7994, 7997, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 7997, 7995);
  g->Binary(ynn_binary_multiply, 7994, 7995, 2643);
  g->Matmul(2643, 2640, 2644, false, false);
  g->Slice(2635, 2645, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(2636, 2646, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(2637, 2647, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(2645, 2646, 2648, false, true);
  g->Mask(2648, 8821, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 8821, 8001, {-1}, true);
  g->Binary(ynn_binary_subtract, 8821, 8001, 7998);
  g->Unary(ynn_unary_exp, 7998, 7999);
  g->Reduce(ynn_reduce_sum, 7999, 8002, {-1}, true);
  g->Binary(ynn_binary_divide, 7293, 8002, 8000);
  g->Binary(ynn_binary_multiply, 7999, 8000, 2649);
  g->Matmul(2649, 2647, 2651, false, false);
  g->Concat({2644,2651}, 2652, 1);
}

// Scope: "Layer25 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer25AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(2652, 2654, 1, 2);
  g->SplitDim(2654, 2653, 1, {1,8});
  g->FuseDims(2653, 2655, 2, 2);
  g->Quantize(2655, 2656, 0.01894685998558998, 0);
  g->Transpose(9185, 6226, {1,0});
  g->Binary(ynn_binary_multiply, 6223, 6225, 6221);
  g->Dot(2656, 6226, YNN_INVALID_VALUE_ID, 6220, 1);
  g->DequantizeTensor(6220, YNN_INVALID_VALUE_ID, 6221, 6222);
  g->QuantizeTensor(6222, 8727, 6224, 2657);
  g->Dequantize(2657, 2658, 0.04775450751185417, 0);
}

// Scope: "Layer25 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer25Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2608, 2609);
  g->Reduce(ynn_reduce_sum, 2609, 7990, {2}, true);
  g->ShapeProduct(2609, 7989, {2});
  g->Binary(ynn_binary_divide, 7990, 7989, 2610);
  g->Binary(ynn_binary_add, 2610, 8779, 2611);
  g->Unary(ynn_unary_rsqrt, 2611, 2612);
  g->Binary(ynn_binary_multiply, 2608, 2612, 2613);
  g->Binary(ynn_binary_multiply, 2613, 9174, 2614);
  BuildLayer25AttentionQueryProjection(ctx);
  BuildLayer25AttentionSdpa(ctx);
  BuildLayer25AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2658, 2659);
  g->Reduce(ynn_reduce_sum, 2659, 8004, {2}, true);
  g->ShapeProduct(2659, 8003, {2});
  g->Binary(ynn_binary_divide, 8004, 8003, 2660);
  g->Binary(ynn_binary_add, 2660, 8779, 2661);
  g->Unary(ynn_unary_rsqrt, 2661, 2663);
  g->Binary(ynn_binary_multiply, 2658, 2663, 2664);
  g->Binary(ynn_binary_multiply, 2664, 9181, 2665);
  g->Binary(ynn_binary_add, 2665, 2608, 2666);
}

// Scope: "Layer25 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer25Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2666, 2667);
  g->Reduce(ynn_reduce_sum, 2667, 8006, {2}, true);
  g->ShapeProduct(2667, 8005, {2});
  g->Binary(ynn_binary_divide, 8006, 8005, 2668);
  g->Binary(ynn_binary_add, 2668, 8779, 2669);
  g->Unary(ynn_unary_rsqrt, 2669, 2670);
  g->Binary(ynn_binary_multiply, 2666, 2670, 2671);
  g->Binary(ynn_binary_multiply, 2671, 9184, 2672);
  g->Quantize(2672, 2674, 0.012911376543343067, 0);
  g->Transpose(9178, 6233, {1,0});
  g->Binary(ynn_binary_multiply, 6230, 6232, 6228);
  g->Dot(2674, 6233, YNN_INVALID_VALUE_ID, 6227, 1);
  g->DequantizeTensor(6227, YNN_INVALID_VALUE_ID, 6228, 6229);
  g->QuantizeTensor(6229, 8727, 6231, 2675);
  g->Dequantize(2675, 2676, 0.015132884494960308, 0);
  g->Transpose(9177, 6238, {1,0});
  g->Binary(ynn_binary_multiply, 6230, 6237, 6235);
  g->Dot(2674, 6238, YNN_INVALID_VALUE_ID, 6234, 1);
  g->DequantizeTensor(6234, YNN_INVALID_VALUE_ID, 6235, 6236);
  g->QuantizeTensor(6236, 8727, 6231, 2677);
  g->Dequantize(2677, 2678, 0.015132884494960308, 0);
  g->Polynomial(2678, 8009, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8009, 8010);
  g->Binary(ynn_binary_add, 8010, 7293, 8007);
  g->Binary(ynn_binary_multiply, 2678, 7305, 8008);
  g->Binary(ynn_binary_multiply, 8008, 8007, 2679);
  g->Binary(ynn_binary_multiply, 2676, 2679, 2680);
  g->Quantize(2680, 2681, 0.015501978807151318, 0);
  g->Transpose(9176, 6245, {1,0});
  g->Binary(ynn_binary_multiply, 6242, 6244, 6240);
  g->Dot(2681, 6245, YNN_INVALID_VALUE_ID, 6239, 1);
  g->DequantizeTensor(6239, YNN_INVALID_VALUE_ID, 6240, 6241);
  g->QuantizeTensor(6241, 8727, 6243, 2682);
  g->Dequantize(2682, 2685, 0.009047985076904297, 0);
  g->Unary(ynn_unary_square, 2685, 2686);
  g->Reduce(ynn_reduce_sum, 2686, 8012, {2}, true);
  g->ShapeProduct(2686, 8011, {2});
  g->Binary(ynn_binary_divide, 8012, 8011, 2687);
  g->Binary(ynn_binary_add, 2687, 8779, 2688);
  g->Unary(ynn_unary_rsqrt, 2688, 2689);
  g->Binary(ynn_binary_multiply, 2685, 2689, 2690);
  g->Binary(ynn_binary_multiply, 2690, 9182, 2691);
  g->Binary(ynn_binary_add, 2691, 2666, 2692);
}

// Scope: "Layer25 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer25PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(429, 2693, {0,0,25,0}, {-1,-1,1,-1});
  g->Reshape(2693, 2694, {1,1,256});
  g->Unary(ynn_unary_square, 2694, 2696);
  g->Reduce(ynn_reduce_sum, 2696, 8014, {2}, true);
  g->ShapeProduct(2696, 8013, {2});
  g->Binary(ynn_binary_divide, 8014, 8013, 2697);
  g->Binary(ynn_binary_add, 2697, 8779, 2698);
  g->Unary(ynn_unary_rsqrt, 2698, 2699);
  g->Binary(ynn_binary_multiply, 2694, 2699, 2700);
  g->Binary(ynn_binary_multiply, 2700, 9533, 2701);
  g->Binary(ynn_binary_multiply, 9552, 8783, 2702);
  g->Binary(ynn_binary_add, 2701, 2702, 2703);
  g->Binary(ynn_binary_multiply, 2703, 8777, 2704);
  g->Quantize(2692, 2705, 0.24657383561134338, 0);
  g->Transpose(9179, 6251, {1,0});
  g->Binary(ynn_binary_multiply, 6249, 6250, 6247);
  g->Dot(2705, 6251, YNN_INVALID_VALUE_ID, 6246, 1);
  g->DequantizeTensor(6246, YNN_INVALID_VALUE_ID, 6247, 6248);
  g->QuantizeTensor(6248, 8727, 5587, 2707);
  g->Dequantize(2707, 2708, 0.18897639214992523, 0);
  g->Polynomial(2708, 8017, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 8017, 8018);
  g->Binary(ynn_binary_add, 8018, 7293, 8015);
  g->Binary(ynn_binary_multiply, 2708, 7305, 8016);
  g->Binary(ynn_binary_multiply, 8016, 8015, 2709);
  g->Binary(ynn_binary_multiply, 2709, 2704, 2710);
  g->Quantize(2710, 2711, 1.3779528141021729, 0);
  g->Transpose(9180, 6258, {1,0});
  g->Binary(ynn_binary_multiply, 6255, 6257, 6253);
  g->Dot(2711, 6258, YNN_INVALID_VALUE_ID, 6252, 1);
  g->DequantizeTensor(6252, YNN_INVALID_VALUE_ID, 6253, 6254);
  g->QuantizeTensor(6254, 8727, 6256, 2712);
  g->Dequantize(2712, 2713, 0.24400226771831512, 0);
  g->Unary(ynn_unary_square, 2713, 2714);
  g->Reduce(ynn_reduce_sum, 2714, 8020, {2}, true);
  g->ShapeProduct(2714, 8019, {2});
  g->Binary(ynn_binary_divide, 8020, 8019, 2715);
  g->Binary(ynn_binary_add, 2715, 8779, 2716);
  g->Unary(ynn_unary_rsqrt, 2716, 2718);
  g->Binary(ynn_binary_multiply, 2713, 2718, 2719);
  g->Binary(ynn_binary_multiply, 2719, 9183, 2720);
  g->Binary(ynn_binary_add, 2692, 2720, 2721);
  g->Binary(ynn_binary_multiply, 2721, 9175, 2722);
}

// Scope: "Layer25"
LAB_YNN_BUILDER_NOINLINE void BuildLayer25(Context& ctx) {
  BuildLayer25Attention(ctx);
  BuildLayer25Mlp(ctx);
  BuildLayer25PerLayerEmbedding(ctx);
}

}  // namespace BuildGemma4DecodeSource
