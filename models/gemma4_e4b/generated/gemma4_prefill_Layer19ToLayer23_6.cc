// Generated YNNPACK builder; do not edit.
#include "gemma4_prefill_builder.h"

namespace BuildGemma4PrefillSource {

// Scope: "Layer19 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(1709, 1710, 0.12022246420383453, 0);
  g->Transpose(5491, 3800, {1,0});
  g->Binary(ynn_binary_multiply, 3797, 3799, 3795);
  g->Dot(1710, 3800, YNN_INVALID_VALUE_ID, 3794, 1);
  g->DequantizeTensor(3794, YNN_INVALID_VALUE_ID, 3795, 3796);
  g->QuantizeTensor(3796, 5190, 3798, 1711);
  g->Dequantize(1711, 1712, 0.11515748500823975, 0);
  g->SplitDim(1712, 1713, 2, {2,256});
  g->Transpose(1713, 1714, {0,2,1,3});
  g->Unary(ynn_unary_square, 1714, 1715);
  g->Reduce(ynn_reduce_sum, 1715, 4833, {3}, true);
  g->ShapeProduct(1715, 4832, {3});
  g->Binary(ynn_binary_divide, 4833, 4832, 1716);
  g->Binary(ynn_binary_add, 1716, 5241, 1718);
  g->Unary(ynn_unary_rsqrt, 1718, 1719);
  g->Binary(ynn_binary_multiply, 1714, 1719, 1720);
  g->Binary(ynn_binary_multiply, 1720, 5490, 1721);
  g->Slice(1721, 1722, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1721, 1723, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1723, 1724);
  g->Concat({1724,1722}, 1725, 3);
  g->Binary(ynn_binary_multiply, 1721, 2394, 1726);
  g->Binary(ynn_binary_multiply, 1725, 2498, 1727);
  g->Binary(ynn_binary_add, 1726, 1727, 1729);
  g->Transpose(5495, 3805, {1,0});
  g->Binary(ynn_binary_multiply, 3797, 3804, 3802);
  g->Dot(1710, 3805, YNN_INVALID_VALUE_ID, 3801, 1);
  g->DequantizeTensor(3801, YNN_INVALID_VALUE_ID, 3802, 3803);
  g->QuantizeTensor(3803, 5190, 3798, 1730);
  g->Dequantize(1730, 1731, 0.11515748500823975, 0);
  g->SplitDim(1731, 1732, 2, {2,256});
  g->Transpose(1732, 1733, {0,2,1,3});
  g->Unary(ynn_unary_square, 1733, 1734);
  g->Reduce(ynn_reduce_sum, 1734, 4835, {3}, true);
  g->ShapeProduct(1734, 4834, {3});
  g->Binary(ynn_binary_divide, 4835, 4834, 1735);
  g->Binary(ynn_binary_add, 1735, 5241, 1736);
  g->Unary(ynn_unary_rsqrt, 1736, 1737);
  g->Binary(ynn_binary_multiply, 1733, 1737, 1739);
}

// Scope: "Layer19 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(1729, 1740, 0.005869260523468256, 0);
  g->Append(5202, 1740, 5724, 2, s2, s1);
  g->View(5724, 5772, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(1739, 1741, 0.047244105488061905, 0);
  g->Append(5226, 1741, 5748, 2, s2, s1);
  g->View(5748, 5795, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer19 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(5494, 3811, {1,0});
  g->Binary(ynn_binary_multiply, 3797, 3810, 3807);
  g->Dot(1710, 3811, YNN_INVALID_VALUE_ID, 3806, 1);
  g->DequantizeTensor(3806, YNN_INVALID_VALUE_ID, 3807, 3808);
  g->QuantizeTensor(3808, 5190, 3809, 1742);
  g->Dequantize(1742, 1743, 0.1328740268945694, 0);
  g->SplitDim(1743, 1745, 2, {8,256});
  g->Transpose(1745, 1746, {0,2,1,3});
  g->Unary(ynn_unary_square, 1746, 1747);
  g->Reduce(ynn_reduce_sum, 1747, 4839, {3}, true);
  g->ShapeProduct(1747, 4838, {3});
  g->Binary(ynn_binary_divide, 4839, 4838, 1748);
  g->Binary(ynn_binary_add, 1748, 5241, 1749);
  g->Unary(ynn_unary_rsqrt, 1749, 1750);
  g->Binary(ynn_binary_multiply, 1746, 1750, 1751);
  g->Binary(ynn_binary_multiply, 1751, 5493, 1752);
  g->Slice(1752, 1753, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1752, 1754, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1754, 1756);
  g->Concat({1756,1753}, 1757, 3);
  g->Binary(ynn_binary_multiply, 1752, 2394, 1758);
  g->Binary(ynn_binary_multiply, 1757, 2498, 1759);
  g->Binary(ynn_binary_add, 1758, 1759, 1760);
}

// Scope: "Layer19 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(5772, 1761, 0.005869260523468256, 0);
  g->Dequantize(5795, 1762, 0.047244105488061905, 0);
  g->Slice(1760, 1763, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(1761, 1764, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(1762, 1765, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(1763, 1764, 1768, false, true);
  g->Mask(1768, 5266, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 5266, 4845, {-1}, true);
  g->Binary(ynn_binary_subtract, 5266, 4845, 4842);
  g->Unary(ynn_unary_exp, 4842, 4843);
  g->Reduce(ynn_reduce_sum, 4843, 4846, {-1}, true);
  g->Binary(ynn_binary_divide, 4364, 4846, 4844);
  g->Binary(ynn_binary_multiply, 4843, 4844, 1769);
  g->Matmul(1769, 1765, 1770, false, false);
  g->Slice(1760, 1771, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(1761, 1772, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(1762, 1773, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(1771, 1772, 1774, false, true);
  g->Mask(1774, 5267, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 5267, 4850, {-1}, true);
  g->Binary(ynn_binary_subtract, 5267, 4850, 4847);
  g->Unary(ynn_unary_exp, 4847, 4848);
  g->Reduce(ynn_reduce_sum, 4848, 4851, {-1}, true);
  g->Binary(ynn_binary_divide, 4364, 4851, 4849);
  g->Binary(ynn_binary_multiply, 4848, 4849, 1775);
  g->Matmul(1775, 1773, 1777, false, false);
  g->Concat({1770,1777}, 1778, 1);
}

// Scope: "Layer19 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1778, 1779, {0,2,1,3});
  g->FuseDims(1779, 1780, 2, 2);
  g->Quantize(1780, 1781, 0.02509843371808529, 0);
  g->Transpose(5492, 3818, {1,0});
  g->Binary(ynn_binary_multiply, 3815, 3817, 3813);
  g->Dot(1781, 3818, YNN_INVALID_VALUE_ID, 3812, 1);
  g->DequantizeTensor(3812, YNN_INVALID_VALUE_ID, 3813, 3814);
  g->QuantizeTensor(3814, 5190, 3816, 1782);
  g->Dequantize(1782, 1783, 0.02879992686212063, 0);
}

// Scope: "Layer19 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1702, 1703);
  g->Reduce(ynn_reduce_sum, 1703, 4831, {2}, true);
  g->ShapeProduct(1703, 4830, {2});
  g->Binary(ynn_binary_divide, 4831, 4830, 1704);
  g->Binary(ynn_binary_add, 1704, 5241, 1705);
  g->Unary(ynn_unary_rsqrt, 1705, 1707);
  g->Binary(ynn_binary_multiply, 1702, 1707, 1708);
  g->Binary(ynn_binary_multiply, 1708, 5479, 1709);
  BuildLayer19AttentionKvProjection(ctx);
  BuildLayer19AttentionCacheUpdate(ctx);
  BuildLayer19AttentionQueryProjection(ctx);
  BuildLayer19AttentionSdpa(ctx);
  BuildLayer19AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1783, 1784);
  g->Reduce(ynn_reduce_sum, 1784, 4853, {2}, true);
  g->ShapeProduct(1784, 4852, {2});
  g->Binary(ynn_binary_divide, 4853, 4852, 1785);
  g->Binary(ynn_binary_add, 1785, 5241, 1786);
  g->Unary(ynn_unary_rsqrt, 1786, 1788);
  g->Binary(ynn_binary_multiply, 1783, 1788, 1789);
  g->Binary(ynn_binary_multiply, 1789, 5486, 1790);
  g->Binary(ynn_binary_add, 1790, 1702, 1791);
}

// Scope: "Layer19 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1791, 1792);
  g->Reduce(ynn_reduce_sum, 1792, 4855, {2}, true);
  g->ShapeProduct(1792, 4854, {2});
  g->Binary(ynn_binary_divide, 4855, 4854, 1793);
  g->Binary(ynn_binary_add, 1793, 5241, 1794);
  g->Unary(ynn_unary_rsqrt, 1794, 1795);
  g->Binary(ynn_binary_multiply, 1791, 1795, 1796);
  g->Binary(ynn_binary_multiply, 1796, 5489, 1797);
  g->Quantize(1797, 1799, 0.01280234195291996, 0);
  g->Transpose(5483, 3825, {1,0});
  g->Binary(ynn_binary_multiply, 3822, 3824, 3820);
  g->Dot(1799, 3825, YNN_INVALID_VALUE_ID, 3819, 1);
  g->DequantizeTensor(3819, YNN_INVALID_VALUE_ID, 3820, 3821);
  g->QuantizeTensor(3821, 5190, 3823, 1800);
  g->Dequantize(1800, 1801, 0.014456210657954216, 0);
  g->Transpose(5482, 3830, {1,0});
  g->Binary(ynn_binary_multiply, 3822, 3829, 3827);
  g->Dot(1799, 3830, YNN_INVALID_VALUE_ID, 3826, 1);
  g->DequantizeTensor(3826, YNN_INVALID_VALUE_ID, 3827, 3828);
  g->QuantizeTensor(3828, 5190, 3823, 1802);
  g->Dequantize(1802, 1803, 0.014456210657954216, 0);
  g->Polynomial(1803, 4858, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 4858, 4859);
  g->Binary(ynn_binary_add, 4859, 4364, 4856);
  g->Binary(ynn_binary_multiply, 1803, 4376, 4857);
  g->Binary(ynn_binary_multiply, 4857, 4856, 1804);
  g->Binary(ynn_binary_multiply, 1801, 1804, 1805);
  g->Quantize(1805, 1806, 0.0076587204821407795, 0);
  g->Transpose(5481, 3837, {1,0});
  g->Binary(ynn_binary_multiply, 3834, 3836, 3832);
  g->Dot(1806, 3837, YNN_INVALID_VALUE_ID, 3831, 1);
  g->DequantizeTensor(3831, YNN_INVALID_VALUE_ID, 3832, 3833);
  g->QuantizeTensor(3833, 5190, 3835, 1807);
  g->Dequantize(1807, 1809, 0.004359397571533918, 0);
  g->Unary(ynn_unary_square, 1809, 1810);
  g->Reduce(ynn_reduce_sum, 1810, 4861, {2}, true);
  g->ShapeProduct(1810, 4860, {2});
  g->Binary(ynn_binary_divide, 4861, 4860, 1811);
  g->Binary(ynn_binary_add, 1811, 5241, 1812);
  g->Unary(ynn_unary_rsqrt, 1812, 1813);
  g->Binary(ynn_binary_multiply, 1809, 1813, 1814);
  g->Binary(ynn_binary_multiply, 1814, 5487, 1815);
  g->Binary(ynn_binary_add, 1815, 1791, 1816);
}

// Scope: "Layer19 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 1817, {0,0,19,0}, {-1,-1,1,-1});
  g->Reshape(1817, 1818, {1,0,256});
  g->Unary(ynn_unary_square, 1818, 1820);
  g->Reduce(ynn_reduce_sum, 1820, 4863, {2}, true);
  g->ShapeProduct(1820, 4862, {2});
  g->Binary(ynn_binary_divide, 4863, 4862, 1821);
  g->Binary(ynn_binary_add, 1821, 5241, 1822);
  g->Unary(ynn_unary_rsqrt, 1822, 1823);
  g->Binary(ynn_binary_multiply, 1818, 1823, 1824);
  g->Binary(ynn_binary_multiply, 1824, 5688, 1825);
  g->Binary(ynn_binary_multiply, 5700, 5245, 1826);
  g->Binary(ynn_binary_add, 1825, 1826, 1827);
  g->Binary(ynn_binary_multiply, 1827, 5240, 1828);
  g->Quantize(1816, 1829, 0.12497252225875854, 0);
  g->Transpose(5484, 3850, {1,0});
  g->Binary(ynn_binary_multiply, 3847, 3849, 3845);
  g->Dot(1829, 3850, YNN_INVALID_VALUE_ID, 3844, 1);
  g->DequantizeTensor(3844, YNN_INVALID_VALUE_ID, 3845, 3846);
  g->QuantizeTensor(3846, 5190, 3848, 1831);
  g->Dequantize(1831, 1832, 0.0743110328912735, 0);
  g->Polynomial(1832, 4866, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 4866, 4867);
  g->Binary(ynn_binary_add, 4867, 4364, 4864);
  g->Binary(ynn_binary_multiply, 1832, 4376, 4865);
  g->Binary(ynn_binary_multiply, 4865, 4864, 1833);
  g->Binary(ynn_binary_multiply, 1833, 1828, 1834);
  g->Quantize(1834, 1835, 0.1643700897693634, 0);
  g->Transpose(5485, 3857, {1,0});
  g->Binary(ynn_binary_multiply, 3854, 3856, 3852);
  g->Dot(1835, 3857, YNN_INVALID_VALUE_ID, 3851, 1);
  g->DequantizeTensor(3851, YNN_INVALID_VALUE_ID, 3852, 3853);
  g->QuantizeTensor(3853, 5190, 3855, 1836);
  g->Dequantize(1836, 1837, 0.10370250046253204, 0);
  g->Unary(ynn_unary_square, 1837, 1838);
  g->Reduce(ynn_reduce_sum, 1838, 4869, {2}, true);
  g->ShapeProduct(1838, 4868, {2});
  g->Binary(ynn_binary_divide, 4869, 4868, 1839);
  g->Binary(ynn_binary_add, 1839, 5241, 1840);
  g->Unary(ynn_unary_rsqrt, 1840, 1842);
  g->Binary(ynn_binary_multiply, 1837, 1842, 1843);
  g->Binary(ynn_binary_multiply, 1843, 5488, 1844);
  g->Binary(ynn_binary_add, 1816, 1844, 1845);
  g->Binary(ynn_binary_multiply, 1845, 5480, 1846);
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
  g->Transpose(5525, 3864, {1,0});
  g->Binary(ynn_binary_multiply, 3861, 3863, 3859);
  g->Dot(1854, 3864, YNN_INVALID_VALUE_ID, 3858, 1);
  g->DequantizeTensor(3858, YNN_INVALID_VALUE_ID, 3859, 3860);
  g->QuantizeTensor(3860, 5190, 3862, 1855);
  g->Dequantize(1855, 1856, 0.05807087570428848, 0);
  g->SplitDim(1856, 1857, 2, {2,256});
  g->Transpose(1857, 1858, {0,2,1,3});
  g->Unary(ynn_unary_square, 1858, 1859);
  g->Reduce(ynn_reduce_sum, 1859, 4877, {3}, true);
  g->ShapeProduct(1859, 4876, {3});
  g->Binary(ynn_binary_divide, 4877, 4876, 1860);
  g->Binary(ynn_binary_add, 1860, 5241, 1861);
  g->Unary(ynn_unary_rsqrt, 1861, 1862);
  g->Binary(ynn_binary_multiply, 1858, 1862, 1864);
  g->Binary(ynn_binary_multiply, 1864, 5524, 1865);
  g->Slice(1865, 1866, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1865, 1867, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1867, 1868);
  g->Concat({1868,1866}, 1869, 3);
  g->Binary(ynn_binary_multiply, 1865, 2394, 1870);
  g->Binary(ynn_binary_multiply, 1869, 2498, 1871);
  g->Binary(ynn_binary_add, 1870, 1871, 1872);
  g->Transpose(5529, 3869, {1,0});
  g->Binary(ynn_binary_multiply, 3861, 3868, 3866);
  g->Dot(1854, 3869, YNN_INVALID_VALUE_ID, 3865, 1);
  g->DequantizeTensor(3865, YNN_INVALID_VALUE_ID, 3866, 3867);
  g->QuantizeTensor(3867, 5190, 3862, 1875);
  g->Dequantize(1875, 1876, 0.05807087570428848, 0);
  g->SplitDim(1876, 1877, 2, {2,256});
  g->Transpose(1877, 1878, {0,2,1,3});
  g->Unary(ynn_unary_square, 1878, 1879);
  g->Reduce(ynn_reduce_sum, 1879, 4879, {3}, true);
  g->ShapeProduct(1879, 4878, {3});
  g->Binary(ynn_binary_divide, 4879, 4878, 1880);
  g->Binary(ynn_binary_add, 1880, 5241, 1881);
  g->Unary(ynn_unary_rsqrt, 1881, 1882);
  g->Binary(ynn_binary_multiply, 1878, 1882, 1883);
}

// Scope: "Layer20 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(1872, 1884, 0.005907459184527397, 0);
  g->Append(5204, 1884, 5726, 2, s2, s1);
  g->View(5726, 5774, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(1883, 1886, 0.047244105488061905, 0);
  g->Append(5228, 1886, 5750, 2, s2, s1);
  g->View(5750, 5797, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer20 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(5528, 3882, {1,0});
  g->Binary(ynn_binary_multiply, 3861, 3881, 3878);
  g->Dot(1854, 3882, YNN_INVALID_VALUE_ID, 3877, 1);
  g->DequantizeTensor(3877, YNN_INVALID_VALUE_ID, 3878, 3879);
  g->QuantizeTensor(3879, 5190, 3880, 1887);
  g->Dequantize(1887, 1888, 0.08710630983114243, 0);
  g->SplitDim(1888, 1889, 2, {8,256});
  g->Transpose(1889, 1890, {0,2,1,3});
  g->Unary(ynn_unary_square, 1890, 1892);
  g->Reduce(ynn_reduce_sum, 1892, 4881, {3}, true);
  g->ShapeProduct(1892, 4880, {3});
  g->Binary(ynn_binary_divide, 4881, 4880, 1893);
  g->Binary(ynn_binary_add, 1893, 5241, 1894);
  g->Unary(ynn_unary_rsqrt, 1894, 1895);
  g->Binary(ynn_binary_multiply, 1890, 1895, 1896);
  g->Binary(ynn_binary_multiply, 1896, 5527, 1897);
  g->Slice(1897, 1898, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1897, 1899, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1899, 1900);
  g->Concat({1900,1898}, 1901, 3);
  g->Binary(ynn_binary_multiply, 1897, 2394, 1903);
  g->Binary(ynn_binary_multiply, 1901, 2498, 1904);
  g->Binary(ynn_binary_add, 1903, 1904, 1905);
}

// Scope: "Layer20 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(5774, 1906, 0.005907459184527397, 0);
  g->Dequantize(5797, 1907, 0.047244105488061905, 0);
  g->Slice(1905, 1908, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(1906, 1909, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(1907, 1910, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(1908, 1909, 1911, false, true);
  g->Mask(1911, 5270, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 5270, 4887, {-1}, true);
  g->Binary(ynn_binary_subtract, 5270, 4887, 4884);
  g->Unary(ynn_unary_exp, 4884, 4885);
  g->Reduce(ynn_reduce_sum, 4885, 4888, {-1}, true);
  g->Binary(ynn_binary_divide, 4364, 4888, 4886);
  g->Binary(ynn_binary_multiply, 4885, 4886, 1913);
  g->Matmul(1913, 1910, 1914, false, false);
  g->Slice(1905, 1915, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(1906, 1916, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(1907, 1917, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(1915, 1916, 1918, false, true);
  g->Mask(1918, 5271, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 5271, 4892, {-1}, true);
  g->Binary(ynn_binary_subtract, 5271, 4892, 4889);
  g->Unary(ynn_unary_exp, 4889, 4890);
  g->Reduce(ynn_reduce_sum, 4890, 4893, {-1}, true);
  g->Binary(ynn_binary_divide, 4364, 4893, 4891);
  g->Binary(ynn_binary_multiply, 4890, 4891, 1919);
  g->Matmul(1919, 1917, 1920, false, false);
  g->Concat({1914,1920}, 1921, 1);
}

// Scope: "Layer20 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1921, 1923, {0,2,1,3});
  g->FuseDims(1923, 1924, 2, 2);
  g->Quantize(1924, 1925, 0.025713592767715454, 0);
  g->Transpose(5526, 3889, {1,0});
  g->Binary(ynn_binary_multiply, 3886, 3888, 3884);
  g->Dot(1925, 3889, YNN_INVALID_VALUE_ID, 3883, 1);
  g->DequantizeTensor(3883, YNN_INVALID_VALUE_ID, 3884, 3885);
  g->QuantizeTensor(3885, 5190, 3887, 1926);
  g->Dequantize(1926, 1927, 0.03443482890725136, 0);
}

// Scope: "Layer20 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1846, 1847);
  g->Reduce(ynn_reduce_sum, 1847, 4871, {2}, true);
  g->ShapeProduct(1847, 4870, {2});
  g->Binary(ynn_binary_divide, 4871, 4870, 1848);
  g->Binary(ynn_binary_add, 1848, 5241, 1849);
  g->Unary(ynn_unary_rsqrt, 1849, 1850);
  g->Binary(ynn_binary_multiply, 1846, 1850, 1851);
  g->Binary(ynn_binary_multiply, 1851, 5513, 1853);
  BuildLayer20AttentionKvProjection(ctx);
  BuildLayer20AttentionCacheUpdate(ctx);
  BuildLayer20AttentionQueryProjection(ctx);
  BuildLayer20AttentionSdpa(ctx);
  BuildLayer20AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1927, 1928);
  g->Reduce(ynn_reduce_sum, 1928, 4895, {2}, true);
  g->ShapeProduct(1928, 4894, {2});
  g->Binary(ynn_binary_divide, 4895, 4894, 1929);
  g->Binary(ynn_binary_add, 1929, 5241, 1930);
  g->Unary(ynn_unary_rsqrt, 1930, 1931);
  g->Binary(ynn_binary_multiply, 1927, 1931, 1932);
  g->Binary(ynn_binary_multiply, 1932, 5520, 1934);
  g->Binary(ynn_binary_add, 1934, 1846, 1935);
}

// Scope: "Layer20 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1935, 1936);
  g->Reduce(ynn_reduce_sum, 1936, 4897, {2}, true);
  g->ShapeProduct(1936, 4896, {2});
  g->Binary(ynn_binary_divide, 4897, 4896, 1937);
  g->Binary(ynn_binary_add, 1937, 5241, 1938);
  g->Unary(ynn_unary_rsqrt, 1938, 1939);
  g->Binary(ynn_binary_multiply, 1935, 1939, 1940);
  g->Binary(ynn_binary_multiply, 1940, 5523, 1941);
  g->Quantize(1941, 1942, 0.014479842968285084, 0);
  g->Transpose(5517, 3896, {1,0});
  g->Binary(ynn_binary_multiply, 3893, 3895, 3891);
  g->Dot(1942, 3896, YNN_INVALID_VALUE_ID, 3890, 1);
  g->DequantizeTensor(3890, YNN_INVALID_VALUE_ID, 3891, 3892);
  g->QuantizeTensor(3892, 5190, 3894, 1943);
  g->Dequantize(1943, 1945, 0.015071368776261806, 0);
  g->Transpose(5516, 3901, {1,0});
  g->Binary(ynn_binary_multiply, 3893, 3900, 3898);
  g->Dot(1942, 3901, YNN_INVALID_VALUE_ID, 3897, 1);
  g->DequantizeTensor(3897, YNN_INVALID_VALUE_ID, 3898, 3899);
  g->QuantizeTensor(3899, 5190, 3894, 1946);
  g->Dequantize(1946, 1947, 0.015071368776261806, 0);
  g->Polynomial(1947, 4900, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 4900, 4901);
  g->Binary(ynn_binary_add, 4901, 4364, 4898);
  g->Binary(ynn_binary_multiply, 1947, 4376, 4899);
  g->Binary(ynn_binary_multiply, 4899, 4898, 1948);
  g->Binary(ynn_binary_multiply, 1945, 1948, 1949);
  g->Quantize(1949, 1950, 0.005413395818322897, 0);
  g->Transpose(5515, 3908, {1,0});
  g->Binary(ynn_binary_multiply, 3905, 3907, 3903);
  g->Dot(1950, 3908, YNN_INVALID_VALUE_ID, 3902, 1);
  g->DequantizeTensor(3902, YNN_INVALID_VALUE_ID, 3903, 3904);
  g->QuantizeTensor(3904, 5190, 3906, 1951);
  g->Dequantize(1951, 1952, 0.004781397990882397, 0);
  g->Unary(ynn_unary_square, 1952, 1953);
  g->Reduce(ynn_reduce_sum, 1953, 4903, {2}, true);
  g->ShapeProduct(1953, 4902, {2});
  g->Binary(ynn_binary_divide, 4903, 4902, 1955);
  g->Binary(ynn_binary_add, 1955, 5241, 1956);
  g->Unary(ynn_unary_rsqrt, 1956, 1957);
  g->Binary(ynn_binary_multiply, 1952, 1957, 1958);
  g->Binary(ynn_binary_multiply, 1958, 5521, 1959);
  g->Binary(ynn_binary_add, 1959, 1935, 1960);
}

// Scope: "Layer20 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 1961, {0,0,20,0}, {-1,-1,1,-1});
  g->Reshape(1961, 1962, {1,0,256});
  g->Unary(ynn_unary_square, 1962, 1963);
  g->Reduce(ynn_reduce_sum, 1963, 4905, {2}, true);
  g->ShapeProduct(1963, 4904, {2});
  g->Binary(ynn_binary_divide, 4905, 4904, 1964);
  g->Binary(ynn_binary_add, 1964, 5241, 1966);
  g->Unary(ynn_unary_rsqrt, 1966, 1967);
  g->Binary(ynn_binary_multiply, 1962, 1967, 1968);
  g->Binary(ynn_binary_multiply, 1968, 5688, 1969);
  g->Binary(ynn_binary_multiply, 5702, 5245, 1970);
  g->Binary(ynn_binary_add, 1969, 1970, 1971);
  g->Binary(ynn_binary_multiply, 1971, 5240, 1972);
  g->Quantize(1960, 1973, 0.17325256764888763, 0);
  g->Transpose(5518, 3915, {1,0});
  g->Binary(ynn_binary_multiply, 3912, 3914, 3910);
  g->Dot(1973, 3915, YNN_INVALID_VALUE_ID, 3909, 1);
  g->DequantizeTensor(3909, YNN_INVALID_VALUE_ID, 3910, 3911);
  g->QuantizeTensor(3911, 5190, 3913, 1974);
  g->Dequantize(1974, 1975, 0.09940945357084274, 0);
  g->Polynomial(1975, 4908, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 4908, 4909);
  g->Binary(ynn_binary_add, 4909, 4364, 4906);
  g->Binary(ynn_binary_multiply, 1975, 4376, 4907);
  g->Binary(ynn_binary_multiply, 4907, 4906, 1978);
  g->Binary(ynn_binary_multiply, 1978, 1972, 1979);
  g->Quantize(1979, 1980, 0.8149606585502625, 0);
  g->Transpose(5519, 3922, {1,0});
  g->Binary(ynn_binary_multiply, 3919, 3921, 3917);
  g->Dot(1980, 3922, YNN_INVALID_VALUE_ID, 3916, 1);
  g->DequantizeTensor(3916, YNN_INVALID_VALUE_ID, 3917, 3918);
  g->QuantizeTensor(3918, 5190, 3920, 1981);
  g->Dequantize(1981, 1982, 0.16500307619571686, 0);
  g->Unary(ynn_unary_square, 1982, 1983);
  g->Reduce(ynn_reduce_sum, 1983, 4911, {2}, true);
  g->ShapeProduct(1983, 4910, {2});
  g->Binary(ynn_binary_divide, 4911, 4910, 1984);
  g->Binary(ynn_binary_add, 1984, 5241, 1985);
  g->Unary(ynn_unary_rsqrt, 1985, 1986);
  g->Binary(ynn_binary_multiply, 1982, 1986, 1987);
  g->Binary(ynn_binary_multiply, 1987, 5522, 1989);
  g->Binary(ynn_binary_add, 1960, 1989, 1990);
  g->Binary(ynn_binary_multiply, 1990, 5514, 1991);
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
  g->Transpose(5542, 3929, {1,0});
  g->Binary(ynn_binary_multiply, 3926, 3928, 3924);
  g->Dot(1998, 3929, YNN_INVALID_VALUE_ID, 3923, 1);
  g->DequantizeTensor(3923, YNN_INVALID_VALUE_ID, 3924, 3925);
  g->QuantizeTensor(3925, 5190, 3927, 2000);
  g->Dequantize(2000, 2001, 0.03961615264415741, 0);
  g->SplitDim(2001, 2002, 2, {2,256});
  g->Transpose(2002, 2003, {0,2,1,3});
  g->Unary(ynn_unary_square, 2003, 2004);
  g->Reduce(ynn_reduce_sum, 2004, 4917, {3}, true);
  g->ShapeProduct(2004, 4916, {3});
  g->Binary(ynn_binary_divide, 4917, 4916, 2005);
  g->Binary(ynn_binary_add, 2005, 5241, 2006);
  g->Unary(ynn_unary_rsqrt, 2006, 2007);
  g->Binary(ynn_binary_multiply, 2003, 2007, 2008);
  g->Binary(ynn_binary_multiply, 2008, 5541, 2009);
  g->Slice(2009, 2011, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2009, 2012, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2012, 2013);
  g->Concat({2013,2011}, 2014, 3);
  g->Binary(ynn_binary_multiply, 2009, 2394, 2015);
  g->Binary(ynn_binary_multiply, 2014, 2498, 2016);
  g->Binary(ynn_binary_add, 2015, 2016, 2017);
  g->Transpose(5546, 3934, {1,0});
  g->Binary(ynn_binary_multiply, 3926, 3933, 3931);
  g->Dot(1998, 3934, YNN_INVALID_VALUE_ID, 3930, 1);
  g->DequantizeTensor(3930, YNN_INVALID_VALUE_ID, 3931, 3932);
  g->QuantizeTensor(3932, 5190, 3927, 2018);
  g->Dequantize(2018, 2019, 0.03961615264415741, 0);
  g->SplitDim(2019, 2021, 2, {2,256});
  g->Transpose(2021, 2022, {0,2,1,3});
  g->Unary(ynn_unary_square, 2022, 2023);
  g->Reduce(ynn_reduce_sum, 2023, 4919, {3}, true);
  g->ShapeProduct(2023, 4918, {3});
  g->Binary(ynn_binary_divide, 4919, 4918, 2024);
  g->Binary(ynn_binary_add, 2024, 5241, 2025);
  g->Unary(ynn_unary_rsqrt, 2025, 2026);
  g->Binary(ynn_binary_multiply, 2022, 2026, 2027);
}

// Scope: "Layer21 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(2017, 2028, 0.0060269939713180065, 0);
  g->Append(5205, 2028, 5727, 2, s2, s1);
  g->View(5727, 5775, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(2027, 2030, 0.047244105488061905, 0);
  g->Append(5229, 2030, 5751, 2, s2, s1);
  g->View(5751, 5798, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer21 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(5545, 3940, {1,0});
  g->Binary(ynn_binary_multiply, 3926, 3939, 3936);
  g->Dot(1998, 3940, YNN_INVALID_VALUE_ID, 3935, 1);
  g->DequantizeTensor(3935, YNN_INVALID_VALUE_ID, 3936, 3937);
  g->QuantizeTensor(3937, 5190, 3938, 2031);
  g->Dequantize(2031, 2032, 0.049212608486413956, 0);
  g->SplitDim(2032, 2033, 2, {8,256});
  g->Transpose(2033, 2034, {0,2,1,3});
  g->Unary(ynn_unary_square, 2034, 2035);
  g->Reduce(ynn_reduce_sum, 2035, 4921, {3}, true);
  g->ShapeProduct(2035, 4920, {3});
  g->Binary(ynn_binary_divide, 4921, 4920, 2036);
  g->Binary(ynn_binary_add, 2036, 5241, 2038);
  g->Unary(ynn_unary_rsqrt, 2038, 2039);
  g->Binary(ynn_binary_multiply, 2034, 2039, 2040);
  g->Binary(ynn_binary_multiply, 2040, 5544, 2041);
  g->Slice(2041, 2042, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2041, 2043, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2043, 2044);
  g->Concat({2044,2042}, 2045, 3);
  g->Binary(ynn_binary_multiply, 2041, 2394, 2046);
  g->Binary(ynn_binary_multiply, 2045, 2498, 2047);
  g->Binary(ynn_binary_add, 2046, 2047, 2049);
}

// Scope: "Layer21 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(5775, 2050, 0.0060269939713180065, 0);
  g->Dequantize(5798, 2051, 0.047244105488061905, 0);
  g->Slice(2049, 2052, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(2050, 2053, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(2051, 2054, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(2052, 2053, 2055, false, true);
  g->Mask(2055, 5272, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 5272, 4925, {-1}, true);
  g->Binary(ynn_binary_subtract, 5272, 4925, 4922);
  g->Unary(ynn_unary_exp, 4922, 4923);
  g->Reduce(ynn_reduce_sum, 4923, 4926, {-1}, true);
  g->Binary(ynn_binary_divide, 4364, 4926, 4924);
  g->Binary(ynn_binary_multiply, 4923, 4924, 2056);
  g->Matmul(2056, 2054, 2057, false, false);
  g->Slice(2049, 2059, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(2050, 2060, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(2051, 2061, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(2059, 2060, 2062, false, true);
  g->Mask(2062, 5273, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 5273, 4930, {-1}, true);
  g->Binary(ynn_binary_subtract, 5273, 4930, 4927);
  g->Unary(ynn_unary_exp, 4927, 4928);
  g->Reduce(ynn_reduce_sum, 4928, 4931, {-1}, true);
  g->Binary(ynn_binary_divide, 4364, 4931, 4929);
  g->Binary(ynn_binary_multiply, 4928, 4929, 2063);
  g->Matmul(2063, 2061, 2064, false, false);
  g->Concat({2057,2064}, 2065, 1);
}

// Scope: "Layer21 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(2065, 2066, {0,2,1,3});
  g->FuseDims(2066, 2067, 2, 2);
  g->Quantize(2067, 2069, 0.02325296215713024, 0);
  g->Transpose(5543, 3953, {1,0});
  g->Binary(ynn_binary_multiply, 3950, 3952, 3948);
  g->Dot(2069, 3953, YNN_INVALID_VALUE_ID, 3947, 1);
  g->DequantizeTensor(3947, YNN_INVALID_VALUE_ID, 3948, 3949);
  g->QuantizeTensor(3949, 5190, 3951, 2070);
  g->Dequantize(2070, 2071, 0.027936452999711037, 0);
}

// Scope: "Layer21 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1991, 1992);
  g->Reduce(ynn_reduce_sum, 1992, 4913, {2}, true);
  g->ShapeProduct(1992, 4912, {2});
  g->Binary(ynn_binary_divide, 4913, 4912, 1993);
  g->Binary(ynn_binary_add, 1993, 5241, 1994);
  g->Unary(ynn_unary_rsqrt, 1994, 1995);
  g->Binary(ynn_binary_multiply, 1991, 1995, 1996);
  g->Binary(ynn_binary_multiply, 1996, 5530, 1997);
  BuildLayer21AttentionKvProjection(ctx);
  BuildLayer21AttentionCacheUpdate(ctx);
  BuildLayer21AttentionQueryProjection(ctx);
  BuildLayer21AttentionSdpa(ctx);
  BuildLayer21AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2071, 2072);
  g->Reduce(ynn_reduce_sum, 2072, 4933, {2}, true);
  g->ShapeProduct(2072, 4932, {2});
  g->Binary(ynn_binary_divide, 4933, 4932, 2073);
  g->Binary(ynn_binary_add, 2073, 5241, 2074);
  g->Unary(ynn_unary_rsqrt, 2074, 2075);
  g->Binary(ynn_binary_multiply, 2071, 2075, 2076);
  g->Binary(ynn_binary_multiply, 2076, 5537, 2077);
  g->Binary(ynn_binary_add, 2077, 1991, 2078);
}

// Scope: "Layer21 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2078, 2082);
  g->Reduce(ynn_reduce_sum, 2082, 4935, {2}, true);
  g->ShapeProduct(2082, 4934, {2});
  g->Binary(ynn_binary_divide, 4935, 4934, 2083);
  g->Binary(ynn_binary_add, 2083, 5241, 2084);
  g->Unary(ynn_unary_rsqrt, 2084, 2085);
  g->Binary(ynn_binary_multiply, 2078, 2085, 2086);
  g->Binary(ynn_binary_multiply, 2086, 5540, 2087);
  g->Quantize(2087, 2088, 0.015300169587135315, 0);
  g->Transpose(5534, 3959, {1,0});
  g->Binary(ynn_binary_multiply, 3957, 3958, 3955);
  g->Dot(2088, 3959, YNN_INVALID_VALUE_ID, 3954, 1);
  g->DequantizeTensor(3954, YNN_INVALID_VALUE_ID, 3955, 3956);
  g->QuantizeTensor(3956, 5190, 3681, 2089);
  g->Dequantize(2089, 2090, 0.01771654561161995, 0);
  g->Transpose(5533, 3964, {1,0});
  g->Binary(ynn_binary_multiply, 3957, 3963, 3961);
  g->Dot(2088, 3964, YNN_INVALID_VALUE_ID, 3960, 1);
  g->DequantizeTensor(3960, YNN_INVALID_VALUE_ID, 3961, 3962);
  g->QuantizeTensor(3962, 5190, 3681, 2092);
  g->Dequantize(2092, 2093, 0.01771654561161995, 0);
  g->Polynomial(2093, 4938, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 4938, 4939);
  g->Binary(ynn_binary_add, 4939, 4364, 4936);
  g->Binary(ynn_binary_multiply, 2093, 4376, 4937);
  g->Binary(ynn_binary_multiply, 4937, 4936, 2094);
  g->Binary(ynn_binary_multiply, 2090, 2094, 2095);
  g->Quantize(2095, 2096, 0.017962608486413956, 0);
  g->Transpose(5532, 3971, {1,0});
  g->Binary(ynn_binary_multiply, 3968, 3970, 3966);
  g->Dot(2096, 3971, YNN_INVALID_VALUE_ID, 3965, 1);
  g->DequantizeTensor(3965, YNN_INVALID_VALUE_ID, 3966, 3967);
  g->QuantizeTensor(3967, 5190, 3969, 2097);
  g->Dequantize(2097, 2098, 0.01586199924349785, 0);
  g->Unary(ynn_unary_square, 2098, 2099);
  g->Reduce(ynn_reduce_sum, 2099, 4941, {2}, true);
  g->ShapeProduct(2099, 4940, {2});
  g->Binary(ynn_binary_divide, 4941, 4940, 2100);
  g->Binary(ynn_binary_add, 2100, 5241, 2101);
  g->Unary(ynn_unary_rsqrt, 2101, 2103);
  g->Binary(ynn_binary_multiply, 2098, 2103, 2104);
  g->Binary(ynn_binary_multiply, 2104, 5538, 2105);
  g->Binary(ynn_binary_add, 2105, 2078, 2106);
}

// Scope: "Layer21 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 2107, {0,0,21,0}, {-1,-1,1,-1});
  g->Reshape(2107, 2108, {1,0,256});
  g->Unary(ynn_unary_square, 2108, 2109);
  g->Reduce(ynn_reduce_sum, 2109, 4943, {2}, true);
  g->ShapeProduct(2109, 4942, {2});
  g->Binary(ynn_binary_divide, 4943, 4942, 2110);
  g->Binary(ynn_binary_add, 2110, 5241, 2111);
  g->Unary(ynn_unary_rsqrt, 2111, 2112);
  g->Binary(ynn_binary_multiply, 2108, 2112, 2114);
  g->Binary(ynn_binary_multiply, 2114, 5688, 2115);
  g->Binary(ynn_binary_multiply, 5703, 5245, 2116);
  g->Binary(ynn_binary_add, 2115, 2116, 2117);
  g->Binary(ynn_binary_multiply, 2117, 5240, 2118);
  g->Quantize(2106, 2119, 0.18123431503772736, 0);
  g->Transpose(5535, 3978, {1,0});
  g->Binary(ynn_binary_multiply, 3975, 3977, 3973);
  g->Dot(2119, 3978, YNN_INVALID_VALUE_ID, 3972, 1);
  g->DequantizeTensor(3972, YNN_INVALID_VALUE_ID, 3973, 3974);
  g->QuantizeTensor(3974, 5190, 3976, 2120);
  g->Dequantize(2120, 2121, 0.10531497001647949, 0);
  g->Polynomial(2121, 4948, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 4948, 4949);
  g->Binary(ynn_binary_add, 4949, 4364, 4946);
  g->Binary(ynn_binary_multiply, 2121, 4376, 4947);
  g->Binary(ynn_binary_multiply, 4947, 4946, 2122);
  g->Binary(ynn_binary_multiply, 2122, 2118, 2123);
  g->Quantize(2123, 2125, 0.22933071851730347, 0);
  g->Transpose(5536, 3985, {1,0});
  g->Binary(ynn_binary_multiply, 3982, 3984, 3980);
  g->Dot(2125, 3985, YNN_INVALID_VALUE_ID, 3979, 1);
  g->DequantizeTensor(3979, YNN_INVALID_VALUE_ID, 3980, 3981);
  g->QuantizeTensor(3981, 5190, 3983, 2126);
  g->Dequantize(2126, 2127, 0.1351429969072342, 0);
  g->Unary(ynn_unary_square, 2127, 2128);
  g->Reduce(ynn_reduce_sum, 2128, 4951, {2}, true);
  g->ShapeProduct(2128, 4950, {2});
  g->Binary(ynn_binary_divide, 4951, 4950, 2129);
  g->Binary(ynn_binary_add, 2129, 5241, 2130);
  g->Unary(ynn_unary_rsqrt, 2130, 2131);
  g->Binary(ynn_binary_multiply, 2127, 2131, 2132);
  g->Binary(ynn_binary_multiply, 2132, 5539, 2133);
  g->Binary(ynn_binary_add, 2106, 2133, 2134);
  g->Binary(ynn_binary_multiply, 2134, 5531, 2136);
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
  g->Transpose(5559, 3992, {1,0});
  g->Binary(ynn_binary_multiply, 3989, 3991, 3987);
  g->Dot(2143, 3992, YNN_INVALID_VALUE_ID, 3986, 1);
  g->DequantizeTensor(3986, YNN_INVALID_VALUE_ID, 3987, 3988);
  g->QuantizeTensor(3988, 5190, 3990, 2144);
  g->Dequantize(2144, 2145, 0.019808080047369003, 0);
  g->SplitDim(2145, 2147, 2, {2,256});
  g->Transpose(2147, 2148, {0,2,1,3});
  g->Unary(ynn_unary_square, 2148, 2149);
  g->Reduce(ynn_reduce_sum, 2149, 4955, {3}, true);
  g->ShapeProduct(2149, 4954, {3});
  g->Binary(ynn_binary_divide, 4955, 4954, 2150);
  g->Binary(ynn_binary_add, 2150, 5241, 2151);
  g->Unary(ynn_unary_rsqrt, 2151, 2152);
  g->Binary(ynn_binary_multiply, 2148, 2152, 2153);
  g->Binary(ynn_binary_multiply, 2153, 5558, 2154);
  g->Slice(2154, 2155, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2154, 2156, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2156, 2158);
  g->Concat({2158,2155}, 2159, 3);
  g->Binary(ynn_binary_multiply, 2154, 2394, 2160);
  g->Binary(ynn_binary_multiply, 2159, 2498, 2161);
  g->Binary(ynn_binary_add, 2160, 2161, 2162);
  g->Transpose(5563, 3997, {1,0});
  g->Binary(ynn_binary_multiply, 3989, 3996, 3994);
  g->Dot(2143, 3997, YNN_INVALID_VALUE_ID, 3993, 1);
  g->DequantizeTensor(3993, YNN_INVALID_VALUE_ID, 3994, 3995);
  g->QuantizeTensor(3995, 5190, 3990, 2163);
  g->Dequantize(2163, 2164, 0.019808080047369003, 0);
  g->SplitDim(2164, 2165, 2, {2,256});
  g->Transpose(2165, 2166, {0,2,1,3});
  g->Unary(ynn_unary_square, 2166, 2168);
  g->Reduce(ynn_reduce_sum, 2168, 4957, {3}, true);
  g->ShapeProduct(2168, 4956, {3});
  g->Binary(ynn_binary_divide, 4957, 4956, 2169);
  g->Binary(ynn_binary_add, 2169, 5241, 2170);
  g->Unary(ynn_unary_rsqrt, 2170, 2171);
  g->Binary(ynn_binary_multiply, 2166, 2171, 2172);
}

// Scope: "Layer22 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(2162, 2173, 0.0059552486054599285, 0);
  g->Append(5206, 2173, 5728, 2, s2, s1);
  g->View(5728, 5776, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(2172, 2174, 0.047244105488061905, 0);
  g->Append(5230, 2174, 5752, 2, s2, s1);
  g->View(5752, 5799, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer22 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(5562, 4003, {1,0});
  g->Binary(ynn_binary_multiply, 3989, 4002, 3999);
  g->Dot(2143, 4003, YNN_INVALID_VALUE_ID, 3998, 1);
  g->DequantizeTensor(3998, YNN_INVALID_VALUE_ID, 3999, 4000);
  g->QuantizeTensor(4000, 5190, 4001, 2176);
  g->Dequantize(2176, 2177, 0.0274360328912735, 0);
  g->SplitDim(2177, 2178, 2, {8,256});
  g->Transpose(2178, 2179, {0,2,1,3});
  g->Unary(ynn_unary_square, 2179, 2180);
  g->Reduce(ynn_reduce_sum, 2180, 4959, {3}, true);
  g->ShapeProduct(2180, 4958, {3});
  g->Binary(ynn_binary_divide, 4959, 4958, 2181);
  g->Binary(ynn_binary_add, 2181, 5241, 2182);
  g->Unary(ynn_unary_rsqrt, 2182, 2183);
  g->Binary(ynn_binary_multiply, 2179, 2183, 2186);
  g->Binary(ynn_binary_multiply, 2186, 5561, 2187);
  g->Slice(2187, 2188, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2187, 2189, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2189, 2190);
  g->Concat({2190,2188}, 2191, 3);
  g->Binary(ynn_binary_multiply, 2187, 2394, 2192);
  g->Binary(ynn_binary_multiply, 2191, 2498, 2193);
  g->Binary(ynn_binary_add, 2192, 2193, 2194);
}

// Scope: "Layer22 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(5776, 2195, 0.0059552486054599285, 0);
  g->Dequantize(5799, 2197, 0.047244105488061905, 0);
  g->Slice(2194, 2198, {0,0,0,0}, {-1,4,-1,-1});
  g->Slice(2195, 2199, {0,0,0,0}, {-1,1,-1,-1});
  g->Slice(2197, 2200, {0,0,0,0}, {-1,1,-1,-1});
  g->Matmul(2198, 2199, 2201, false, true);
  g->Mask(2201, 5274, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 5274, 4963, {-1}, true);
  g->Binary(ynn_binary_subtract, 5274, 4963, 4960);
  g->Unary(ynn_unary_exp, 4960, 4961);
  g->Reduce(ynn_reduce_sum, 4961, 4964, {-1}, true);
  g->Binary(ynn_binary_divide, 4364, 4964, 4962);
  g->Binary(ynn_binary_multiply, 4961, 4962, 2202);
  g->Matmul(2202, 2200, 2203, false, false);
  g->Slice(2194, 2204, {0,4,0,0}, {-1,4,-1,-1});
  g->Slice(2195, 2205, {0,1,0,0}, {-1,1,-1,-1});
  g->Slice(2197, 2207, {0,1,0,0}, {-1,1,-1,-1});
  g->Matmul(2204, 2205, 2208, false, true);
  g->Mask(2208, 5275, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 5275, 4968, {-1}, true);
  g->Binary(ynn_binary_subtract, 5275, 4968, 4965);
  g->Unary(ynn_unary_exp, 4965, 4966);
  g->Reduce(ynn_reduce_sum, 4966, 4969, {-1}, true);
  g->Binary(ynn_binary_divide, 4364, 4969, 4967);
  g->Binary(ynn_binary_multiply, 4966, 4967, 2209);
  g->Matmul(2209, 2207, 2210, false, false);
  g->Concat({2203,2210}, 2211, 1);
}

// Scope: "Layer22 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(2211, 2212, {0,2,1,3});
  g->FuseDims(2212, 2213, 2, 2);
  g->Quantize(2213, 2214, 0.020915362983942032, 0);
  g->Transpose(5560, 4010, {1,0});
  g->Binary(ynn_binary_multiply, 4007, 4009, 4005);
  g->Dot(2214, 4010, YNN_INVALID_VALUE_ID, 4004, 1);
  g->DequantizeTensor(4004, YNN_INVALID_VALUE_ID, 4005, 4006);
  g->QuantizeTensor(4006, 5190, 4008, 2215);
  g->Dequantize(2215, 2217, 0.03860917314887047, 0);
}

// Scope: "Layer22 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2136, 2137);
  g->Reduce(ynn_reduce_sum, 2137, 4953, {2}, true);
  g->ShapeProduct(2137, 4952, {2});
  g->Binary(ynn_binary_divide, 4953, 4952, 2138);
  g->Binary(ynn_binary_add, 2138, 5241, 2139);
  g->Unary(ynn_unary_rsqrt, 2139, 2140);
  g->Binary(ynn_binary_multiply, 2136, 2140, 2141);
  g->Binary(ynn_binary_multiply, 2141, 5547, 2142);
  BuildLayer22AttentionKvProjection(ctx);
  BuildLayer22AttentionCacheUpdate(ctx);
  BuildLayer22AttentionQueryProjection(ctx);
  BuildLayer22AttentionSdpa(ctx);
  BuildLayer22AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2217, 2218);
  g->Reduce(ynn_reduce_sum, 2218, 4971, {2}, true);
  g->ShapeProduct(2218, 4970, {2});
  g->Binary(ynn_binary_divide, 4971, 4970, 2219);
  g->Binary(ynn_binary_add, 2219, 5241, 2220);
  g->Unary(ynn_unary_rsqrt, 2220, 2221);
  g->Binary(ynn_binary_multiply, 2217, 2221, 2222);
  g->Binary(ynn_binary_multiply, 2222, 5554, 2223);
  g->Binary(ynn_binary_add, 2223, 2136, 2224);
}

// Scope: "Layer22 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2224, 2225);
  g->Reduce(ynn_reduce_sum, 2225, 4973, {2}, true);
  g->ShapeProduct(2225, 4972, {2});
  g->Binary(ynn_binary_divide, 4973, 4972, 2226);
  g->Binary(ynn_binary_add, 2226, 5241, 2228);
  g->Unary(ynn_unary_rsqrt, 2228, 2229);
  g->Binary(ynn_binary_multiply, 2224, 2229, 2230);
  g->Binary(ynn_binary_multiply, 2230, 5557, 2231);
  g->Quantize(2231, 2232, 0.014675655402243137, 0);
  g->Transpose(5551, 4017, {1,0});
  g->Binary(ynn_binary_multiply, 4014, 4016, 4012);
  g->Dot(2232, 4017, YNN_INVALID_VALUE_ID, 4011, 1);
  g->DequantizeTensor(4011, YNN_INVALID_VALUE_ID, 4012, 4013);
  g->QuantizeTensor(4013, 5190, 4015, 2233);
  g->Dequantize(2233, 2234, 0.017593514174222946, 0);
  g->Transpose(5550, 4022, {1,0});
  g->Binary(ynn_binary_multiply, 4014, 4021, 4019);
  g->Dot(2232, 4022, YNN_INVALID_VALUE_ID, 4018, 1);
  g->DequantizeTensor(4018, YNN_INVALID_VALUE_ID, 4019, 4020);
  g->QuantizeTensor(4020, 5190, 4015, 2235);
  g->Dequantize(2235, 2236, 0.017593514174222946, 0);
  g->Polynomial(2236, 4976, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 4976, 4977);
  g->Binary(ynn_binary_add, 4977, 4364, 4974);
  g->Binary(ynn_binary_multiply, 2236, 4376, 4975);
  g->Binary(ynn_binary_multiply, 4975, 4974, 2237);
  g->Binary(ynn_binary_multiply, 2234, 2237, 2238);
  g->Quantize(2238, 2239, 0.009842529892921448, 0);
  g->Transpose(5549, 4029, {1,0});
  g->Binary(ynn_binary_multiply, 4026, 4028, 4024);
  g->Dot(2239, 4029, YNN_INVALID_VALUE_ID, 4023, 1);
  g->DequantizeTensor(4023, YNN_INVALID_VALUE_ID, 4024, 4025);
  g->QuantizeTensor(4025, 5190, 4027, 2240);
  g->Dequantize(2240, 2241, 0.007876119576394558, 0);
  g->Unary(ynn_unary_square, 2241, 2242);
  g->Reduce(ynn_reduce_sum, 2242, 4979, {2}, true);
  g->ShapeProduct(2242, 4978, {2});
  g->Binary(ynn_binary_divide, 4979, 4978, 2243);
  g->Binary(ynn_binary_add, 2243, 5241, 2244);
  g->Unary(ynn_unary_rsqrt, 2244, 2245);
  g->Binary(ynn_binary_multiply, 2241, 2245, 2246);
  g->Binary(ynn_binary_multiply, 2246, 5555, 2248);
  g->Binary(ynn_binary_add, 2248, 2224, 2249);
}

// Scope: "Layer22 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(418, 2250, {0,0,22,0}, {-1,-1,1,-1});
  g->Reshape(2250, 2251, {1,0,256});
  g->Unary(ynn_unary_square, 2251, 2252);
  g->Reduce(ynn_reduce_sum, 2252, 4981, {2}, true);
  g->ShapeProduct(2252, 4980, {2});
  g->Binary(ynn_binary_divide, 4981, 4980, 2253);
  g->Binary(ynn_binary_add, 2253, 5241, 2254);
  g->Unary(ynn_unary_rsqrt, 2254, 2255);
  g->Binary(ynn_binary_multiply, 2251, 2255, 2256);
  g->Binary(ynn_binary_multiply, 2256, 5688, 2257);
  g->Binary(ynn_binary_multiply, 5704, 5245, 2259);
  g->Binary(ynn_binary_add, 2257, 2259, 2260);
  g->Binary(ynn_binary_multiply, 2260, 5240, 2261);
  g->Quantize(2249, 2262, 0.28123560547828674, 0);
  g->Transpose(5552, 4041, {1,0});
  g->Binary(ynn_binary_multiply, 4038, 4040, 4036);
  g->Dot(2262, 4041, YNN_INVALID_VALUE_ID, 4035, 1);
  g->DequantizeTensor(4035, YNN_INVALID_VALUE_ID, 4036, 4037);
  g->QuantizeTensor(4037, 5190, 4039, 2263);
  g->Dequantize(2263, 2264, 0.5590550899505615, 0);
  g->Polynomial(2264, 4984, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 4984, 4985);
  g->Binary(ynn_binary_add, 4985, 4364, 4982);
  g->Binary(ynn_binary_multiply, 2264, 4376, 4983);
  g->Binary(ynn_binary_multiply, 4983, 4982, 2265);
  g->Binary(ynn_binary_multiply, 2265, 2261, 2266);
  g->Quantize(2266, 2267, 0.6968504190444946, 0);
  g->Transpose(5553, 4048, {1,0});
  g->Binary(ynn_binary_multiply, 4045, 4047, 4043);
  g->Dot(2267, 4048, YNN_INVALID_VALUE_ID, 4042, 1);
  g->DequantizeTensor(4042, YNN_INVALID_VALUE_ID, 4043, 4044);
  g->QuantizeTensor(4044, 5190, 4046, 2268);
  g->Dequantize(2268, 2270, 0.38523077964782715, 0);
  g->Unary(ynn_unary_square, 2270, 2271);
  g->Reduce(ynn_reduce_sum, 2271, 4987, {2}, true);
  g->ShapeProduct(2271, 4986, {2});
  g->Binary(ynn_binary_divide, 4987, 4986, 2272);
  g->Binary(ynn_binary_add, 2272, 5241, 2273);
  g->Unary(ynn_unary_rsqrt, 2273, 2274);
  g->Binary(ynn_binary_multiply, 2270, 2274, 2275);
  g->Binary(ynn_binary_multiply, 2275, 5556, 2276);
  g->Binary(ynn_binary_add, 2249, 2276, 2277);
  g->Binary(ynn_binary_multiply, 2277, 5548, 2278);
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
  g->Transpose(5566, 4055, {1,0});
  g->Binary(ynn_binary_multiply, 4052, 4054, 4050);
  g->Dot(2286, 4055, YNN_INVALID_VALUE_ID, 4049, 1);
  g->DequantizeTensor(4049, YNN_INVALID_VALUE_ID, 4050, 4051);
  g->QuantizeTensor(4051, 5190, 4053, 2287);
  g->Dequantize(2287, 2288, 0.05413386970758438, 0);
  g->SplitDim(2288, 2289, 2, {2,512});
  g->Transpose(2289, 2290, {0,2,1,3});
  g->Unary(ynn_unary_square, 2290, 2293);
  g->Reduce(ynn_reduce_sum, 2293, 4991, {3}, true);
  g->ShapeProduct(2293, 4990, {3});
  g->Binary(ynn_binary_divide, 4991, 4990, 2294);
  g->Binary(ynn_binary_add, 2294, 5241, 2295);
  g->Unary(ynn_unary_rsqrt, 2295, 2296);
  g->Binary(ynn_binary_multiply, 2290, 2296, 2297);
  g->Binary(ynn_binary_multiply, 2297, 5565, 2298);
  g->Slice(2298, 2299, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(2298, 2300, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 2300, 2301);
  g->Concat({2301,2299}, 2302, 3);
  g->Binary(ynn_binary_multiply, 2298, 2909, 2304);
  g->Binary(ynn_binary_multiply, 2302, 2, 2305);
  g->Binary(ynn_binary_add, 2304, 2305, 2306);
  g->Transpose(5567, 4060, {1,0});
  g->Binary(ynn_binary_multiply, 4052, 4059, 4057);
  g->Dot(2286, 4060, YNN_INVALID_VALUE_ID, 4056, 1);
  g->DequantizeTensor(4056, YNN_INVALID_VALUE_ID, 4057, 4058);
  g->QuantizeTensor(4058, 5190, 4053, 2307);
  g->Dequantize(2307, 2308, 0.05413386970758438, 0);
  g->SplitDim(2308, 2309, 2, {2,512});
  g->Transpose(2309, 2310, {0,2,1,3});
  g->Unary(ynn_unary_square, 2310, 2311);
  g->Reduce(ynn_reduce_sum, 2311, 4995, {3}, true);
  g->ShapeProduct(2311, 4994, {3});
  g->Binary(ynn_binary_divide, 4995, 4994, 2312);
  g->Binary(ynn_binary_add, 2312, 5241, 2314);
  g->Unary(ynn_unary_rsqrt, 2314, 2315);
  g->Binary(ynn_binary_multiply, 2310, 2315, 2316);
}

// Scope: "Layer23 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(2306, 2317, 0.001091228099539876, 0);
  g->Append(5207, 2317, 5729, 2, s2, s1);
  g->Quantize(2316, 2318, 0.01785714365541935, 0);
  g->Append(5231, 2318, 5753, 2, s2, s1);
}

// Scope: "Layer23 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2278, 2279);
  g->Reduce(ynn_reduce_sum, 2279, 4989, {2}, true);
  g->ShapeProduct(2279, 4988, {2});
  g->Binary(ynn_binary_divide, 4989, 4988, 2281);
  g->Binary(ynn_binary_add, 2281, 5241, 2282);
  g->Unary(ynn_unary_rsqrt, 2282, 2283);
  g->Binary(ynn_binary_multiply, 2278, 2283, 2284);
  g->Binary(ynn_binary_multiply, 2284, 5564, 2285);
  BuildLayer23AttentionKvProjection(ctx);
  BuildLayer23AttentionCacheUpdate(ctx);
}

// Scope: "Layer23"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23(Context& ctx) {
  BuildLayer23Attention(ctx);
}

}  // namespace BuildGemma4PrefillSource
