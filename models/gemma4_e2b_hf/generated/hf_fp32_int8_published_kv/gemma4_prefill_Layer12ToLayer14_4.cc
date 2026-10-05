// Generated YNNPACK builder; do not edit.
#include "gemma4_prefill_builder.h"

namespace BuildGemma4PrefillSource {

// Scope: "Layer12 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Binary(ynn_binary_divide, 1677, 3398, 1678);
  g->Unary(ynn_unary_round, 1678, 1679);
  g->Binary(ynn_binary_max, 1679, 3328, 1680);
  g->Binary(ynn_binary_min, 1680, 3384, 1681);
  g->Binary(ynn_binary_multiply, 1681, 3398, 1682);
  g->Convert(3613, 1683);
  g->Binary(ynn_binary_multiply, 1683, 3614, 1685);
  g->Matmul(1682, 1685, 1686, false, true);
  g->Binary(ynn_binary_divide, 1686, 3367, 1687);
  g->Unary(ynn_unary_round, 1687, 1688);
  g->Binary(ynn_binary_max, 1688, 3328, 1689);
  g->Binary(ynn_binary_min, 1689, 3384, 1690);
  g->Binary(ynn_binary_multiply, 1690, 3367, 1691);
  g->Reshape(1691, 1692, {1,0,1,256});
  g->Transpose(1692, 1693, {0,2,1,3});
  g->Unary(ynn_unary_square, 1693, 1694);
  g->Reduce(ynn_reduce_sum, 1694, 3101, {3}, true);
  g->ShapeProduct(1694, 3100, {3});
  g->Binary(ynn_binary_divide, 3101, 3100, 1696);
  g->Binary(ynn_binary_add, 1696, 3400, 1697);
  g->Binary(ynn_binary_pow, 1697, 3424, 1698);
  g->Binary(ynn_binary_multiply, 1693, 1698, 1699);
  g->Convert(3612, 1700);
  g->Binary(ynn_binary_multiply, 1699, 1700, 1701);
  g->Slice(1701, 1702, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1701, 1703, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1703, 1704);
  g->Concat({1704,1702}, 1705, 3);
  g->Binary(ynn_binary_multiply, 1701, 2025, 1707);
  g->Binary(ynn_binary_multiply, 1705, 2249, 1708);
  g->Binary(ynn_binary_add, 1707, 1708, 1709);
  g->Convert(3620, 1710);
  g->Binary(ynn_binary_multiply, 1710, 3621, 1711);
  g->Matmul(1682, 1711, 1713, false, true);
  g->Binary(ynn_binary_divide, 1713, 3367, 1714);
  g->Unary(ynn_unary_round, 1714, 1715);
  g->Binary(ynn_binary_max, 1715, 3328, 1716);
  g->Binary(ynn_binary_min, 1716, 3384, 1717);
  g->Binary(ynn_binary_multiply, 1717, 3367, 1718);
  g->Reshape(1718, 1719, {1,0,1,256});
  g->Transpose(1719, 1720, {0,2,1,3});
  g->Unary(ynn_unary_square, 1720, 1721);
  g->Reduce(ynn_reduce_sum, 1721, 3103, {3}, true);
  g->ShapeProduct(1721, 3102, {3});
  g->Binary(ynn_binary_divide, 3103, 3102, 1722);
  g->Binary(ynn_binary_add, 1722, 3400, 1724);
  g->Binary(ynn_binary_pow, 1724, 3424, 1725);
  g->Binary(ynn_binary_multiply, 1720, 1725, 1726);
}

// Scope: "Layer12 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(1709, 1727, 0.005788442213088274, 0);
  g->Append(3266, 1727, 3883, 2, s2, s1);
  g->View(3883, 3913, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(3913, 1728, 0.005788442213088274, 0);
  g->Quantize(1726, 1729, 0.047244105488061905, 0);
  g->Append(3281, 1729, 3898, 2, s2, s1);
  g->View(3898, 3927, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(3927, 1732, 0.047244105488061905, 0);
}

// Scope: "Layer12 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Convert(3618, 1733);
  g->Binary(ynn_binary_multiply, 1733, 3619, 1734);
  g->Matmul(1682, 1734, 1735, false, true);
  g->Binary(ynn_binary_divide, 1735, 3352, 1736);
  g->Unary(ynn_unary_round, 1736, 1738);
  g->Binary(ynn_binary_max, 1738, 3328, 1739);
  g->Binary(ynn_binary_min, 1739, 3384, 1740);
  g->Binary(ynn_binary_multiply, 1740, 3352, 1741);
  g->SplitDim(1741, 1742, 2, {8,256});
  g->Transpose(1742, 1743, {0,2,1,3});
  g->Unary(ynn_unary_square, 1743, 1744);
  g->Reduce(ynn_reduce_sum, 1744, 3105, {3}, true);
  g->ShapeProduct(1744, 3104, {3});
  g->Binary(ynn_binary_divide, 3105, 3104, 1745);
  g->Binary(ynn_binary_add, 1745, 3400, 1746);
  g->Binary(ynn_binary_pow, 1746, 3424, 1747);
  g->Binary(ynn_binary_multiply, 1743, 1747, 1749);
  g->Convert(3617, 1750);
  g->Binary(ynn_binary_multiply, 1749, 1750, 1751);
  g->Slice(1751, 1752, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1751, 1753, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1753, 1754);
  g->Concat({1754,1752}, 1755, 3);
  g->Binary(ynn_binary_multiply, 1751, 2025, 1756);
  g->Binary(ynn_binary_multiply, 1755, 2249, 1757);
  g->Binary(ynn_binary_add, 1756, 1757, 1758);
}

// Scope: "Layer12 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(1758, 1728, 1760, false, true);
  g->Mask(1760, 3482, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 3482, 3109, {-1}, true);
  g->Binary(ynn_binary_subtract, 3482, 3109, 3106);
  g->Unary(ynn_unary_exp, 3106, 3107);
  g->Reduce(ynn_reduce_sum, 3107, 3110, {-1}, true);
  g->Binary(ynn_binary_divide, 2855, 3110, 3108);
  g->Binary(ynn_binary_multiply, 3107, 3108, 1761);
  g->Matmul(1761, 1732, 1762, false, false);
}

// Scope: "Layer12 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1762, 1763, {0,2,1,3});
  g->FuseDims(1763, 1764, 2, 2);
  g->Binary(ynn_binary_divide, 1764, 3397, 1765);
  g->Unary(ynn_unary_round, 1765, 1766);
  g->Binary(ynn_binary_max, 1766, 3328, 1767);
  g->Binary(ynn_binary_min, 1767, 3384, 1768);
  g->Binary(ynn_binary_multiply, 1768, 3397, 1770);
  g->Convert(3615, 1771);
  g->Binary(ynn_binary_multiply, 1771, 3616, 1772);
  g->Matmul(1770, 1772, 1773, false, true);
  g->Binary(ynn_binary_divide, 1773, 3444, 1774);
  g->Unary(ynn_unary_round, 1774, 1775);
  g->Binary(ynn_binary_max, 1775, 3328, 1776);
  g->Binary(ynn_binary_min, 1776, 3384, 1777);
  g->Binary(ynn_binary_multiply, 1777, 3444, 1778);
}

// Scope: "Layer12 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1669, 1670);
  g->Reduce(ynn_reduce_sum, 1670, 3099, {2}, true);
  g->ShapeProduct(1670, 3098, {2});
  g->Binary(ynn_binary_divide, 3099, 3098, 1671);
  g->Binary(ynn_binary_add, 1671, 3400, 1672);
  g->Binary(ynn_binary_pow, 1672, 3424, 1674);
  g->Binary(ynn_binary_multiply, 1669, 1674, 1675);
  g->Convert(3596, 1676);
  g->Binary(ynn_binary_multiply, 1675, 1676, 1677);
  BuildLayer12AttentionKvProjection(ctx);
  BuildLayer12AttentionCacheUpdate(ctx);
  BuildLayer12AttentionQueryProjection(ctx);
  BuildLayer12AttentionSdpa(ctx);
  BuildLayer12AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1778, 1779);
  g->Reduce(ynn_reduce_sum, 1779, 3112, {2}, true);
  g->ShapeProduct(1779, 3111, {2});
  g->Binary(ynn_binary_divide, 3112, 3111, 1780);
  g->Binary(ynn_binary_add, 1780, 3400, 1781);
  g->Binary(ynn_binary_pow, 1781, 3424, 1782);
  g->Binary(ynn_binary_multiply, 1778, 1782, 1783);
  g->Convert(3608, 1784);
  g->Binary(ynn_binary_multiply, 1783, 1784, 1785);
  g->Binary(ynn_binary_add, 1669, 1785, 1786);
}

// Scope: "Layer12 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1786, 1787);
  g->Reduce(ynn_reduce_sum, 1787, 3114, {2}, true);
  g->ShapeProduct(1787, 3113, {2});
  g->Binary(ynn_binary_divide, 3114, 3113, 1788);
  g->Binary(ynn_binary_add, 1788, 3400, 1789);
  g->Binary(ynn_binary_pow, 1789, 3424, 1790);
  g->Binary(ynn_binary_multiply, 1786, 1790, 1791);
  g->Convert(3611, 1792);
  g->Binary(ynn_binary_multiply, 1791, 1792, 1793);
  g->Binary(ynn_binary_divide, 1793, 3469, 1794);
  g->Unary(ynn_unary_round, 1794, 1795);
  g->Binary(ynn_binary_max, 1795, 3328, 1796);
  g->Binary(ynn_binary_min, 1796, 3384, 1797);
  g->Binary(ynn_binary_multiply, 1797, 3469, 1798);
  g->Convert(3602, 1799);
  g->Binary(ynn_binary_multiply, 1799, 3603, 1800);
  g->Matmul(1798, 1800, 1801, false, true);
  g->Binary(ynn_binary_divide, 1801, 3477, 1802);
  g->Unary(ynn_unary_round, 1802, 1803);
  g->Binary(ynn_binary_max, 1803, 3328, 1804);
  g->Binary(ynn_binary_min, 1804, 3384, 1805);
  g->Binary(ynn_binary_multiply, 1805, 3477, 1806);
  g->Convert(3600, 1807);
  g->Binary(ynn_binary_multiply, 1807, 3601, 1808);
  g->Matmul(1798, 1808, 1809, false, true);
  g->Binary(ynn_binary_divide, 1809, 3477, 1810);
  g->Unary(ynn_unary_round, 1810, 1811);
  g->Binary(ynn_binary_max, 1811, 3328, 1812);
  g->Binary(ynn_binary_min, 1812, 3384, 1813);
  g->Binary(ynn_binary_multiply, 1813, 3477, 1814);
  g->Polynomial(1814, 3117, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 3117, 3118);
  g->Binary(ynn_binary_add, 3118, 2855, 3115);
  g->Binary(ynn_binary_multiply, 1814, 2853, 3116);
  g->Binary(ynn_binary_multiply, 3116, 3115, 1815);
  g->Binary(ynn_binary_multiply, 1806, 1815, 1816);
  g->Binary(ynn_binary_divide, 1816, 3471, 1817);
  g->Unary(ynn_unary_round, 1817, 1818);
  g->Binary(ynn_binary_max, 1818, 3328, 1819);
  g->Binary(ynn_binary_min, 1819, 3384, 1820);
  g->Binary(ynn_binary_multiply, 1820, 3471, 1821);
  g->Convert(3598, 1822);
  g->Binary(ynn_binary_multiply, 1822, 3599, 1823);
  g->Matmul(1821, 1823, 1824, false, true);
  g->Binary(ynn_binary_divide, 1824, 3422, 1827);
  g->Unary(ynn_unary_round, 1827, 1828);
  g->Binary(ynn_binary_max, 1828, 3328, 1829);
  g->Binary(ynn_binary_min, 1829, 3384, 1830);
  g->Binary(ynn_binary_multiply, 1830, 3422, 1831);
  g->Unary(ynn_unary_square, 1831, 1832);
  g->Reduce(ynn_reduce_sum, 1832, 3120, {2}, true);
  g->ShapeProduct(1832, 3119, {2});
  g->Binary(ynn_binary_divide, 3120, 3119, 1833);
  g->Binary(ynn_binary_add, 1833, 3400, 1834);
  g->Binary(ynn_binary_pow, 1834, 3424, 1835);
  g->Binary(ynn_binary_multiply, 1831, 1835, 1836);
  g->Convert(3609, 1838);
  g->Binary(ynn_binary_multiply, 1836, 1838, 1839);
  g->Binary(ynn_binary_add, 1786, 1839, 1840);
}

// Scope: "Layer12 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1022, 1841, {0,0,12,0}, {-1,-1,1,-1});
  g->Reshape(1841, 1842, {1,0,256});
  g->Binary(ynn_binary_add, 1842, 3868, 1843);
  g->Binary(ynn_binary_multiply, 1843, 3296, 1844);
  g->Binary(ynn_binary_divide, 1840, 3475, 1845);
  g->Unary(ynn_unary_round, 1845, 1846);
  g->Binary(ynn_binary_max, 1846, 3328, 1847);
  g->Binary(ynn_binary_min, 1847, 3384, 1849);
  g->Binary(ynn_binary_multiply, 1849, 3475, 1850);
  g->Convert(3604, 1851);
  g->Binary(ynn_binary_multiply, 1851, 3605, 1852);
  g->Matmul(1850, 1852, 1853, false, true);
  g->Binary(ynn_binary_divide, 1853, 3449, 1854);
  g->Unary(ynn_unary_round, 1854, 1855);
  g->Binary(ynn_binary_max, 1855, 3328, 1856);
  g->Binary(ynn_binary_min, 1856, 3384, 1857);
  g->Binary(ynn_binary_multiply, 1857, 3449, 1858);
  g->Polynomial(1858, 3123, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 3123, 3124);
  g->Binary(ynn_binary_add, 3124, 2855, 3121);
  g->Binary(ynn_binary_multiply, 1858, 2853, 3122);
  g->Binary(ynn_binary_multiply, 3122, 3121, 1860);
  g->Binary(ynn_binary_multiply, 1860, 1844, 1861);
  g->Binary(ynn_binary_divide, 1861, 3443, 1862);
  g->Unary(ynn_unary_round, 1862, 1863);
  g->Binary(ynn_binary_max, 1863, 3328, 1864);
  g->Binary(ynn_binary_min, 1864, 3384, 1865);
  g->Binary(ynn_binary_multiply, 1865, 3443, 1866);
  g->Convert(3606, 1867);
  g->Binary(ynn_binary_multiply, 1867, 3607, 1868);
  g->Matmul(1866, 1868, 1869, false, true);
  g->Binary(ynn_binary_divide, 1869, 3472, 1871);
  g->Unary(ynn_unary_round, 1871, 1872);
  g->Binary(ynn_binary_max, 1872, 3328, 1873);
  g->Binary(ynn_binary_min, 1873, 3384, 1874);
  g->Binary(ynn_binary_multiply, 1874, 3472, 1875);
  g->Unary(ynn_unary_square, 1875, 1876);
  g->Reduce(ynn_reduce_sum, 1876, 3126, {2}, true);
  g->ShapeProduct(1876, 3125, {2});
  g->Binary(ynn_binary_divide, 3126, 3125, 1877);
  g->Binary(ynn_binary_add, 1877, 3400, 1878);
  g->Binary(ynn_binary_pow, 1878, 3424, 1879);
  g->Binary(ynn_binary_multiply, 1875, 1879, 1880);
  g->Convert(3610, 1882);
  g->Binary(ynn_binary_multiply, 1880, 1882, 1883);
  g->Binary(ynn_binary_add, 1840, 1883, 1884);
  g->Convert(3597, 1885);
  g->Binary(ynn_binary_multiply, 1884, 1885, 1886);
}

// Scope: "Layer12"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12(Context& ctx) {
  BuildLayer12Attention(ctx);
  BuildLayer12Mlp(ctx);
  BuildLayer12PerLayerEmbedding(ctx);
}

// Scope: "Layer13 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Binary(ynn_binary_divide, 1894, 3344, 1895);
  g->Unary(ynn_unary_round, 1895, 1896);
  g->Binary(ynn_binary_max, 1896, 3328, 1897);
  g->Binary(ynn_binary_min, 1897, 3384, 1898);
  g->Binary(ynn_binary_multiply, 1898, 3344, 1899);
  g->Convert(3639, 1900);
  g->Binary(ynn_binary_multiply, 1900, 3640, 1901);
  g->Matmul(1899, 1901, 1902, false, true);
  g->Binary(ynn_binary_divide, 1902, 3389, 1904);
  g->Unary(ynn_unary_round, 1904, 1905);
  g->Binary(ynn_binary_max, 1905, 3328, 1906);
  g->Binary(ynn_binary_min, 1906, 3384, 1907);
  g->Binary(ynn_binary_multiply, 1907, 3389, 1908);
  g->Reshape(1908, 1909, {1,0,1,256});
  g->Transpose(1909, 1910, {0,2,1,3});
  g->Unary(ynn_unary_square, 1910, 1911);
  g->Reduce(ynn_reduce_sum, 1911, 3130, {3}, true);
  g->ShapeProduct(1911, 3129, {3});
  g->Binary(ynn_binary_divide, 3130, 3129, 1912);
  g->Binary(ynn_binary_add, 1912, 3400, 1913);
  g->Binary(ynn_binary_pow, 1913, 3424, 1915);
  g->Binary(ynn_binary_multiply, 1910, 1915, 1916);
  g->Convert(3638, 1917);
  g->Binary(ynn_binary_multiply, 1916, 1917, 1918);
  g->Slice(1918, 1919, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1918, 1920, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1920, 1921);
  g->Concat({1921,1919}, 1922, 3);
  g->Binary(ynn_binary_multiply, 1918, 2025, 1923);
  g->Binary(ynn_binary_multiply, 1922, 2249, 1924);
  g->Binary(ynn_binary_add, 1923, 1924, 1926);
  g->Convert(3646, 1927);
  g->Binary(ynn_binary_multiply, 1927, 3647, 1928);
  g->Matmul(1899, 1928, 1929, false, true);
  g->Binary(ynn_binary_divide, 1929, 3389, 1930);
  g->Unary(ynn_unary_round, 1930, 1933);
  g->Binary(ynn_binary_max, 1933, 3328, 1934);
  g->Binary(ynn_binary_min, 1934, 3384, 1935);
  g->Binary(ynn_binary_multiply, 1935, 3389, 1936);
  g->Reshape(1936, 1937, {1,0,1,256});
  g->Transpose(1937, 1938, {0,2,1,3});
  g->Unary(ynn_unary_square, 1938, 1939);
  g->Reduce(ynn_reduce_sum, 1939, 3132, {3}, true);
  g->ShapeProduct(1939, 3131, {3});
  g->Binary(ynn_binary_divide, 3132, 3131, 1940);
  g->Binary(ynn_binary_add, 1940, 3400, 1941);
  g->Binary(ynn_binary_pow, 1941, 3424, 1942);
  g->Binary(ynn_binary_multiply, 1938, 1942, 1944);
}

// Scope: "Layer13 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(1926, 1945, 0.0059552486054599285, 0);
  g->Append(3267, 1945, 3884, 2, s2, s1);
  g->View(3884, 3914, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(3914, 1946, 0.0059552486054599285, 0);
  g->Quantize(1944, 1947, 0.047244105488061905, 0);
  g->Append(3282, 1947, 3899, 2, s2, s1);
  g->View(3899, 3928, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(3928, 1948, 0.047244105488061905, 0);
}

// Scope: "Layer13 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Convert(3644, 1950);
  g->Binary(ynn_binary_multiply, 1950, 3645, 1951);
  g->Matmul(1899, 1951, 1952, false, true);
  g->Binary(ynn_binary_divide, 1952, 3373, 1953);
  g->Unary(ynn_unary_round, 1953, 1954);
  g->Binary(ynn_binary_max, 1954, 3328, 1955);
  g->Binary(ynn_binary_min, 1955, 3384, 1957);
  g->Binary(ynn_binary_multiply, 1957, 3373, 1958);
  g->SplitDim(1958, 1959, 2, {8,256});
  g->Transpose(1959, 1960, {0,2,1,3});
  g->Unary(ynn_unary_square, 1960, 1961);
  g->Reduce(ynn_reduce_sum, 1961, 3136, {3}, true);
  g->ShapeProduct(1961, 3135, {3});
  g->Binary(ynn_binary_divide, 3136, 3135, 1962);
  g->Binary(ynn_binary_add, 1962, 3400, 1963);
  g->Binary(ynn_binary_pow, 1963, 3424, 1964);
  g->Binary(ynn_binary_multiply, 1960, 1964, 1965);
  g->Convert(3643, 1966);
  g->Binary(ynn_binary_multiply, 1965, 1966, 1968);
  g->Slice(1968, 1969, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1968, 1970, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1970, 1971);
  g->Concat({1971,1969}, 1972, 3);
  g->Binary(ynn_binary_multiply, 1968, 2025, 1973);
  g->Binary(ynn_binary_multiply, 1972, 2249, 1974);
  g->Binary(ynn_binary_add, 1973, 1974, 1975);
}

// Scope: "Layer13 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(1975, 1946, 1976, false, true);
  g->Mask(1976, 3483, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 3483, 3140, {-1}, true);
  g->Binary(ynn_binary_subtract, 3483, 3140, 3137);
  g->Unary(ynn_unary_exp, 3137, 3138);
  g->Reduce(ynn_reduce_sum, 3138, 3141, {-1}, true);
  g->Binary(ynn_binary_divide, 2855, 3141, 3139);
  g->Binary(ynn_binary_multiply, 3138, 3139, 1978);
  g->Matmul(1978, 1948, 1979, false, false);
}

// Scope: "Layer13 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1979, 1980, {0,2,1,3});
  g->FuseDims(1980, 1981, 2, 2);
  g->Binary(ynn_binary_divide, 1981, 3342, 1982);
  g->Unary(ynn_unary_round, 1982, 1983);
  g->Binary(ynn_binary_max, 1983, 3328, 1984);
  g->Binary(ynn_binary_min, 1984, 3384, 1985);
  g->Binary(ynn_binary_multiply, 1985, 3342, 1986);
  g->Convert(3641, 1987);
  g->Binary(ynn_binary_multiply, 1987, 3642, 1988);
  g->Matmul(1986, 1988, 1989, false, true);
  g->Binary(ynn_binary_divide, 1989, 3297, 1990);
  g->Unary(ynn_unary_round, 1990, 1991);
  g->Binary(ynn_binary_max, 1991, 3328, 1992);
  g->Binary(ynn_binary_min, 1992, 3384, 1993);
  g->Binary(ynn_binary_multiply, 1993, 3297, 1994);
}

// Scope: "Layer13 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1886, 1887);
  g->Reduce(ynn_reduce_sum, 1887, 3128, {2}, true);
  g->ShapeProduct(1887, 3127, {2});
  g->Binary(ynn_binary_divide, 3128, 3127, 1888);
  g->Binary(ynn_binary_add, 1888, 3400, 1889);
  g->Binary(ynn_binary_pow, 1889, 3424, 1890);
  g->Binary(ynn_binary_multiply, 1886, 1890, 1891);
  g->Convert(3622, 1893);
  g->Binary(ynn_binary_multiply, 1891, 1893, 1894);
  BuildLayer13AttentionKvProjection(ctx);
  BuildLayer13AttentionCacheUpdate(ctx);
  BuildLayer13AttentionQueryProjection(ctx);
  BuildLayer13AttentionSdpa(ctx);
  BuildLayer13AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1994, 1995);
  g->Reduce(ynn_reduce_sum, 1995, 3143, {2}, true);
  g->ShapeProduct(1995, 3142, {2});
  g->Binary(ynn_binary_divide, 3143, 3142, 1996);
  g->Binary(ynn_binary_add, 1996, 3400, 1997);
  g->Binary(ynn_binary_pow, 1997, 3424, 1998);
  g->Binary(ynn_binary_multiply, 1994, 1998, 1999);
  g->Convert(3634, 2000);
  g->Binary(ynn_binary_multiply, 1999, 2000, 2001);
  g->Binary(ynn_binary_add, 1886, 2001, 2002);
}

// Scope: "Layer13 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2002, 2003);
  g->Reduce(ynn_reduce_sum, 2003, 3145, {2}, true);
  g->ShapeProduct(2003, 3144, {2});
  g->Binary(ynn_binary_divide, 3145, 3144, 2004);
  g->Binary(ynn_binary_add, 2004, 3400, 2005);
  g->Binary(ynn_binary_pow, 2005, 3424, 2006);
  g->Binary(ynn_binary_multiply, 2002, 2006, 2007);
  g->Convert(3637, 2009);
  g->Binary(ynn_binary_multiply, 2007, 2009, 2010);
  g->Binary(ynn_binary_divide, 2010, 3392, 2011);
  g->Unary(ynn_unary_round, 2011, 2012);
  g->Binary(ynn_binary_max, 2012, 3328, 2013);
  g->Binary(ynn_binary_min, 2013, 3384, 2014);
  g->Binary(ynn_binary_multiply, 2014, 3392, 2015);
  g->Convert(3628, 2016);
  g->Binary(ynn_binary_multiply, 2016, 3629, 2017);
  g->Matmul(2015, 2017, 2018, false, true);
  g->Binary(ynn_binary_divide, 2018, 3417, 2020);
  g->Unary(ynn_unary_round, 2020, 2021);
  g->Binary(ynn_binary_max, 2021, 3328, 2022);
  g->Binary(ynn_binary_min, 2022, 3384, 2023);
  g->Binary(ynn_binary_multiply, 2023, 3417, 2024);
  g->Convert(3626, 2027);
  g->Binary(ynn_binary_multiply, 2027, 3627, 2028);
  g->Matmul(2015, 2028, 2029, false, true);
  g->Binary(ynn_binary_divide, 2029, 3417, 2030);
  g->Unary(ynn_unary_round, 2030, 2031);
  g->Binary(ynn_binary_max, 2031, 3328, 2032);
  g->Binary(ynn_binary_min, 2032, 3384, 2033);
  g->Binary(ynn_binary_multiply, 2033, 3417, 2034);
  g->Polynomial(2034, 3148, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 3148, 3149);
  g->Binary(ynn_binary_add, 3149, 2855, 3146);
  g->Binary(ynn_binary_multiply, 2034, 2853, 3147);
  g->Binary(ynn_binary_multiply, 3147, 3146, 2035);
  g->Binary(ynn_binary_multiply, 2024, 2035, 2036);
  g->Binary(ynn_binary_divide, 2036, 3351, 2037);
  g->Unary(ynn_unary_round, 2037, 2038);
  g->Binary(ynn_binary_max, 2038, 3328, 2039);
  g->Binary(ynn_binary_min, 2039, 3384, 2040);
  g->Binary(ynn_binary_multiply, 2040, 3351, 2041);
  g->Convert(3624, 2042);
  g->Binary(ynn_binary_multiply, 2042, 3625, 2043);
  g->Matmul(2041, 2043, 2044, false, true);
  g->Binary(ynn_binary_divide, 2044, 3468, 2045);
  g->Unary(ynn_unary_round, 2045, 2046);
  g->Binary(ynn_binary_max, 2046, 3328, 2048);
  g->Binary(ynn_binary_min, 2048, 3384, 2049);
  g->Binary(ynn_binary_multiply, 2049, 3468, 2050);
  g->Unary(ynn_unary_square, 2050, 2051);
  g->Reduce(ynn_reduce_sum, 2051, 3151, {2}, true);
  g->ShapeProduct(2051, 3150, {2});
  g->Binary(ynn_binary_divide, 3151, 3150, 2052);
  g->Binary(ynn_binary_add, 2052, 3400, 2053);
  g->Binary(ynn_binary_pow, 2053, 3424, 2054);
  g->Binary(ynn_binary_multiply, 2050, 2054, 2055);
  g->Convert(3635, 2056);
  g->Binary(ynn_binary_multiply, 2055, 2056, 2057);
  g->Binary(ynn_binary_add, 2002, 2057, 2058);
}

// Scope: "Layer13 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1022, 2059, {0,0,13,0}, {-1,-1,1,-1});
  g->Reshape(2059, 2060, {1,0,256});
  g->Binary(ynn_binary_add, 2060, 3869, 2061);
  g->Binary(ynn_binary_multiply, 2061, 3296, 2062);
  g->Binary(ynn_binary_divide, 2058, 3356, 2063);
  g->Unary(ynn_unary_round, 2063, 2064);
  g->Binary(ynn_binary_max, 2064, 3328, 2065);
  g->Binary(ynn_binary_min, 2065, 3384, 2066);
  g->Binary(ynn_binary_multiply, 2066, 3356, 2067);
  g->Convert(3630, 2068);
  g->Binary(ynn_binary_multiply, 2068, 3631, 2069);
  g->Matmul(2067, 2069, 2070, false, true);
  g->Binary(ynn_binary_divide, 2070, 3438, 2071);
  g->Unary(ynn_unary_round, 2071, 2072);
  g->Binary(ynn_binary_max, 2072, 3328, 2073);
  g->Binary(ynn_binary_min, 2073, 3384, 2074);
  g->Binary(ynn_binary_multiply, 2074, 3438, 2075);
  g->Polynomial(2075, 3154, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 3154, 3155);
  g->Binary(ynn_binary_add, 3155, 2855, 3152);
  g->Binary(ynn_binary_multiply, 2075, 2853, 3153);
  g->Binary(ynn_binary_multiply, 3153, 3152, 2076);
  g->Binary(ynn_binary_multiply, 2076, 2062, 2077);
  g->Binary(ynn_binary_divide, 2077, 3312, 2078);
  g->Unary(ynn_unary_round, 2078, 2079);
  g->Binary(ynn_binary_max, 2079, 3328, 2080);
  g->Binary(ynn_binary_min, 2080, 3384, 2081);
  g->Binary(ynn_binary_multiply, 2081, 3312, 2082);
  g->Convert(3632, 2083);
  g->Binary(ynn_binary_multiply, 2083, 3633, 2084);
  g->Matmul(2082, 2084, 2085, false, true);
  g->Binary(ynn_binary_divide, 2085, 3418, 2086);
  g->Unary(ynn_unary_round, 2086, 2087);
  g->Binary(ynn_binary_max, 2087, 3328, 2088);
  g->Binary(ynn_binary_min, 2088, 3384, 2089);
  g->Binary(ynn_binary_multiply, 2089, 3418, 2090);
  g->Unary(ynn_unary_square, 2090, 2091);
  g->Reduce(ynn_reduce_sum, 2091, 3157, {2}, true);
  g->ShapeProduct(2091, 3156, {2});
  g->Binary(ynn_binary_divide, 3157, 3156, 2092);
  g->Binary(ynn_binary_add, 2092, 3400, 2093);
  g->Binary(ynn_binary_pow, 2093, 3424, 2094);
  g->Binary(ynn_binary_multiply, 2090, 2094, 2095);
  g->Convert(3636, 2096);
  g->Binary(ynn_binary_multiply, 2095, 2096, 2097);
  g->Binary(ynn_binary_add, 2058, 2097, 2098);
  g->Convert(3623, 2099);
  g->Binary(ynn_binary_multiply, 2098, 2099, 2100);
}

// Scope: "Layer13"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13(Context& ctx) {
  BuildLayer13Attention(ctx);
  BuildLayer13Mlp(ctx);
  BuildLayer13PerLayerEmbedding(ctx);
}

// Scope: "Layer14 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Binary(ynn_binary_divide, 2107, 3305, 2109);
  g->Unary(ynn_unary_round, 2109, 2110);
  g->Binary(ynn_binary_max, 2110, 3328, 2111);
  g->Binary(ynn_binary_min, 2111, 3384, 2112);
  g->Binary(ynn_binary_multiply, 2112, 3305, 2113);
  g->Convert(3650, 2114);
  g->Binary(ynn_binary_multiply, 2114, 3651, 2115);
  g->Matmul(2113, 2115, 2116, false, true);
  g->Binary(ynn_binary_divide, 2116, 3442, 2117);
  g->Unary(ynn_unary_round, 2117, 2118);
  g->Binary(ynn_binary_max, 2118, 3328, 2120);
  g->Binary(ynn_binary_min, 2120, 3384, 2121);
  g->Binary(ynn_binary_multiply, 2121, 3442, 2122);
  g->Reshape(2122, 2123, {1,0,1,512});
  g->Transpose(2123, 2124, {0,2,1,3});
  g->Unary(ynn_unary_square, 2124, 2125);
  g->Reduce(ynn_reduce_sum, 2125, 3161, {3}, true);
  g->ShapeProduct(2125, 3160, {3});
  g->Binary(ynn_binary_divide, 3161, 3160, 2126);
  g->Binary(ynn_binary_add, 2126, 3400, 2127);
  g->Binary(ynn_binary_pow, 2127, 3424, 2128);
  g->Binary(ynn_binary_multiply, 2124, 2128, 2129);
  g->Convert(3649, 2132);
  g->Binary(ynn_binary_multiply, 2129, 2132, 2133);
  g->Slice(2133, 2134, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(2133, 2135, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 2135, 2136);
  g->Concat({2136,2134}, 2137, 3);
  g->Binary(ynn_binary_multiply, 2133, 2651, 2138);
  g->Binary(ynn_binary_multiply, 2137, 2750, 2139);
  g->Binary(ynn_binary_add, 2138, 2139, 2140);
  g->Convert(3652, 2142);
  g->Binary(ynn_binary_multiply, 2142, 3653, 2143);
  g->Matmul(2113, 2143, 2144, false, true);
  g->Binary(ynn_binary_divide, 2144, 3442, 2145);
  g->Unary(ynn_unary_round, 2145, 2146);
  g->Binary(ynn_binary_max, 2146, 3328, 2147);
  g->Binary(ynn_binary_min, 2147, 3384, 2149);
  g->Binary(ynn_binary_multiply, 2149, 3442, 2150);
  g->Reshape(2150, 2151, {1,0,1,512});
  g->Transpose(2151, 2152, {0,2,1,3});
  g->Unary(ynn_unary_square, 2152, 2153);
  g->Reduce(ynn_reduce_sum, 2153, 3163, {3}, true);
  g->ShapeProduct(2153, 3162, {3});
  g->Binary(ynn_binary_divide, 3163, 3162, 2154);
  g->Binary(ynn_binary_add, 2154, 3400, 2155);
  g->Binary(ynn_binary_pow, 2155, 3424, 2156);
  g->Binary(ynn_binary_multiply, 2152, 2156, 2157);
}

// Scope: "Layer14 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(2140, 2158, 0.001091228099539876, 0);
  g->Append(3268, 2158, 3885, 2, s2, s1);
  g->Quantize(2157, 2160, 0.01785714365541935, 0);
  g->Append(3283, 2160, 3900, 2, s2, s1);
}

// Scope: "Layer14 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2100, 2101);
  g->Reduce(ynn_reduce_sum, 2101, 3159, {2}, true);
  g->ShapeProduct(2101, 3158, {2});
  g->Binary(ynn_binary_divide, 3159, 3158, 2102);
  g->Binary(ynn_binary_add, 2102, 3400, 2103);
  g->Binary(ynn_binary_pow, 2103, 3424, 2104);
  g->Binary(ynn_binary_multiply, 2100, 2104, 2105);
  g->Convert(3648, 2106);
  g->Binary(ynn_binary_multiply, 2105, 2106, 2107);
  BuildLayer14AttentionKvProjection(ctx);
  BuildLayer14AttentionCacheUpdate(ctx);
}

// Scope: "Layer14"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14(Context& ctx) {
  BuildLayer14Attention(ctx);
}

}  // namespace BuildGemma4PrefillSource
