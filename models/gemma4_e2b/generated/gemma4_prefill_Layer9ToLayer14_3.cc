// Generated YNNPACK builder; do not edit.
#include "gemma4_prefill_builder.h"

namespace BuildGemma4PrefillSource {

// Scope: "Layer9 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(175, 176, 0.016753647476434708, 0);
  g->Transpose(3271, 1808, {1,0});
  g->Binary(ynn_binary_multiply, 1805, 1807, 1803);
  g->Dot(176, 1808, YNN_INVALID_VALUE_ID, 1802, 1);
  g->DequantizeTensor(1802, YNN_INVALID_VALUE_ID, 1803, 1804);
  g->QuantizeTensor(1804, 2982, 1806, 177);
  g->Dequantize(177, 178, 0.020177174359560013, 0);
  g->Reshape(178, 179, {1,0,1,512});
  g->Transpose(179, 180, {0,2,1,3});
  g->Unary(ynn_unary_square, 180, 181);
  g->Reduce(ynn_reduce_sum, 181, 2590, {3}, true);
  g->ShapeProduct(181, 2589, {3});
  g->Binary(ynn_binary_divide, 2590, 2589, 183);
  g->Binary(ynn_binary_add, 183, 3016, 184);
  g->Unary(ynn_unary_rsqrt, 184, 185);
  g->Binary(ynn_binary_multiply, 180, 185, 186);
  g->Binary(ynn_binary_multiply, 186, 3270, 187);
  g->Slice(187, 188, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(187, 189, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 189, 190);
  g->Concat({190,188}, 191, 3);
  g->Binary(ynn_binary_multiply, 187, 1613, 192);
  g->Binary(ynn_binary_multiply, 191, 2, 194);
  g->Binary(ynn_binary_add, 192, 194, 195);
  g->Transpose(3275, 1813, {1,0});
  g->Binary(ynn_binary_multiply, 1805, 1812, 1810);
  g->Dot(176, 1813, YNN_INVALID_VALUE_ID, 1809, 1);
  g->DequantizeTensor(1809, YNN_INVALID_VALUE_ID, 1810, 1811);
  g->QuantizeTensor(1811, 2982, 1806, 196);
  g->Dequantize(196, 197, 0.020177174359560013, 0);
  g->Reshape(197, 198, {1,0,1,512});
  g->Transpose(198, 199, {0,2,1,3});
  g->Unary(ynn_unary_square, 199, 200);
  g->Reduce(ynn_reduce_sum, 200, 2594, {3}, true);
  g->ShapeProduct(200, 2593, {3});
  g->Binary(ynn_binary_divide, 2594, 2593, 201);
  g->Binary(ynn_binary_add, 201, 3016, 202);
  g->Unary(ynn_unary_rsqrt, 202, 204);
  g->Binary(ynn_binary_multiply, 199, 204, 205);
}

// Scope: "Layer9 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(195, 206, 0.0010733711533248425, 0);
  g->Append(2997, 206, 3307, 2, s2, s1);
  g->View(3307, 3336, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(205, 207, 0.01785714365541935, 0);
  g->Append(3012, 207, 3322, 2, s2, s1);
  g->View(3322, 3350, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer9 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(3274, 1819, {1,0});
  g->Binary(ynn_binary_multiply, 1805, 1818, 1815);
  g->Dot(176, 1819, YNN_INVALID_VALUE_ID, 1814, 1);
  g->DequantizeTensor(1814, YNN_INVALID_VALUE_ID, 1815, 1816);
  g->QuantizeTensor(1816, 2982, 1817, 208);
  g->Dequantize(208, 211, 0.029650600627064705, 0);
  g->SplitDim(211, 212, 2, {8,512});
  g->Transpose(212, 213, {0,2,1,3});
  g->Unary(ynn_unary_square, 213, 214);
  g->Reduce(ynn_reduce_sum, 214, 2596, {3}, true);
  g->ShapeProduct(214, 2595, {3});
  g->Binary(ynn_binary_divide, 2596, 2595, 215);
  g->Binary(ynn_binary_add, 215, 3016, 216);
  g->Unary(ynn_unary_rsqrt, 216, 217);
  g->Binary(ynn_binary_multiply, 213, 217, 218);
  g->Binary(ynn_binary_multiply, 218, 3273, 219);
  g->Slice(219, 220, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(219, 222, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 222, 223);
  g->Concat({223,220}, 224, 3);
  g->Binary(ynn_binary_multiply, 219, 1613, 225);
  g->Binary(ynn_binary_multiply, 224, 2, 226);
  g->Binary(ynn_binary_add, 225, 226, 227);
}

// Scope: "Layer9 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(3336, 228, 0.0010733711533248425, 0);
  g->Dequantize(3350, 229, 0.01785714365541935, 0);
  g->Matmul(227, 228, 230, false, true);
  g->Mask(230, 3033, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 3033, 2600, {-1}, true);
  g->Binary(ynn_binary_subtract, 3033, 2600, 2597);
  g->Unary(ynn_unary_exp, 2597, 2598);
  g->Reduce(ynn_reduce_sum, 2598, 2601, {-1}, true);
  g->Binary(ynn_binary_divide, 2545, 2601, 2599);
  g->Binary(ynn_binary_multiply, 2598, 2599, 232);
  g->Matmul(232, 229, 233, false, false);
}

// Scope: "Layer9 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(233, 234, {0,2,1,3});
  g->FuseDims(234, 235, 2, 2);
  g->Quantize(235, 236, 0.017962608486413956, 0);
  g->Transpose(3272, 1833, {1,0});
  g->Binary(ynn_binary_multiply, 1830, 1832, 1828);
  g->Dot(236, 1833, YNN_INVALID_VALUE_ID, 1827, 1);
  g->DequantizeTensor(1827, YNN_INVALID_VALUE_ID, 1828, 1829);
  g->QuantizeTensor(1829, 2982, 1831, 237);
  g->Dequantize(237, 238, 0.02776472456753254, 0);
}

// Scope: "Layer9 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 168, 169);
  g->Reduce(ynn_reduce_sum, 169, 2588, {2}, true);
  g->ShapeProduct(169, 2587, {2});
  g->Binary(ynn_binary_divide, 2588, 2587, 170);
  g->Binary(ynn_binary_add, 170, 3016, 172);
  g->Unary(ynn_unary_rsqrt, 172, 173);
  g->Binary(ynn_binary_multiply, 168, 173, 174);
  g->Binary(ynn_binary_multiply, 174, 3259, 175);
  BuildLayer9AttentionKvProjection(ctx);
  BuildLayer9AttentionCacheUpdate(ctx);
  BuildLayer9AttentionQueryProjection(ctx);
  BuildLayer9AttentionSdpa(ctx);
  BuildLayer9AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 238, 239);
  g->Reduce(ynn_reduce_sum, 239, 2603, {2}, true);
  g->ShapeProduct(239, 2602, {2});
  g->Binary(ynn_binary_divide, 2603, 2602, 240);
  g->Binary(ynn_binary_add, 240, 3016, 241);
  g->Unary(ynn_unary_rsqrt, 241, 243);
  g->Binary(ynn_binary_multiply, 238, 243, 244);
  g->Binary(ynn_binary_multiply, 244, 3266, 245);
  g->Binary(ynn_binary_add, 245, 168, 246);
}

// Scope: "Layer9 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 246, 247);
  g->Reduce(ynn_reduce_sum, 247, 2605, {2}, true);
  g->ShapeProduct(247, 2604, {2});
  g->Binary(ynn_binary_divide, 2605, 2604, 248);
  g->Binary(ynn_binary_add, 248, 3016, 249);
  g->Unary(ynn_unary_rsqrt, 249, 250);
  g->Binary(ynn_binary_multiply, 246, 250, 251);
  g->Binary(ynn_binary_multiply, 251, 3269, 252);
  g->Quantize(252, 254, 0.028379227966070175, 0);
  g->Transpose(3263, 1840, {1,0});
  g->Binary(ynn_binary_multiply, 1837, 1839, 1835);
  g->Dot(254, 1840, YNN_INVALID_VALUE_ID, 1834, 1);
  g->DequantizeTensor(1834, YNN_INVALID_VALUE_ID, 1835, 1836);
  g->QuantizeTensor(1836, 2982, 1838, 255);
  g->Dequantize(255, 256, 0.01556349452584982, 0);
  g->Transpose(3262, 1845, {1,0});
  g->Binary(ynn_binary_multiply, 1837, 1844, 1842);
  g->Dot(254, 1845, YNN_INVALID_VALUE_ID, 1841, 1);
  g->DequantizeTensor(1841, YNN_INVALID_VALUE_ID, 1842, 1843);
  g->QuantizeTensor(1843, 2982, 1838, 257);
  g->Dequantize(257, 258, 0.01556349452584982, 0);
  g->Polynomial(258, 2608, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2608, 2609);
  g->Binary(ynn_binary_add, 2609, 2545, 2606);
  g->Binary(ynn_binary_multiply, 258, 2543, 2607);
  g->Binary(ynn_binary_multiply, 2607, 2606, 259);
  g->Binary(ynn_binary_multiply, 256, 259, 260);
  g->Quantize(260, 261, 0.011441939510405064, 0);
  g->Transpose(3261, 1852, {1,0});
  g->Binary(ynn_binary_multiply, 1849, 1851, 1847);
  g->Dot(261, 1852, YNN_INVALID_VALUE_ID, 1846, 1);
  g->DequantizeTensor(1846, YNN_INVALID_VALUE_ID, 1847, 1848);
  g->QuantizeTensor(1848, 2982, 1850, 262);
  g->Dequantize(262, 264, 0.005826006643474102, 0);
  g->Unary(ynn_unary_square, 264, 265);
  g->Reduce(ynn_reduce_sum, 265, 2611, {2}, true);
  g->ShapeProduct(265, 2610, {2});
  g->Binary(ynn_binary_divide, 2611, 2610, 266);
  g->Binary(ynn_binary_add, 266, 3016, 267);
  g->Unary(ynn_unary_rsqrt, 267, 268);
  g->Binary(ynn_binary_multiply, 264, 268, 269);
  g->Binary(ynn_binary_multiply, 269, 3267, 270);
  g->Binary(ynn_binary_add, 270, 246, 271);
}

// Scope: "Layer9 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(421, 272, {0,0,9,0}, {-1,-1,1,-1});
  g->Reshape(272, 273, {1,0,256});
  g->Unary(ynn_unary_square, 273, 275);
  g->Reduce(ynn_reduce_sum, 275, 2613, {2}, true);
  g->ShapeProduct(275, 2612, {2});
  g->Binary(ynn_binary_divide, 2613, 2612, 276);
  g->Binary(ynn_binary_add, 276, 3016, 277);
  g->Unary(ynn_unary_rsqrt, 277, 278);
  g->Binary(ynn_binary_multiply, 273, 278, 279);
  g->Binary(ynn_binary_multiply, 279, 3277, 280);
  g->Binary(ynn_binary_multiply, 3291, 3019, 281);
  g->Binary(ynn_binary_add, 280, 281, 282);
  g->Binary(ynn_binary_multiply, 282, 3014, 283);
  g->Quantize(271, 284, 0.22249335050582886, 0);
  g->Transpose(3264, 1866, {1,0});
  g->Binary(ynn_binary_multiply, 1863, 1865, 1861);
  g->Dot(284, 1866, YNN_INVALID_VALUE_ID, 1860, 1);
  g->DequantizeTensor(1860, YNN_INVALID_VALUE_ID, 1861, 1862);
  g->QuantizeTensor(1862, 2982, 1864, 286);
  g->Dequantize(286, 287, 0.04404528811573982, 0);
  g->Polynomial(287, 2616, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2616, 2617);
  g->Binary(ynn_binary_add, 2617, 2545, 2614);
  g->Binary(ynn_binary_multiply, 287, 2543, 2615);
  g->Binary(ynn_binary_multiply, 2615, 2614, 288);
  g->Binary(ynn_binary_multiply, 288, 283, 289);
  g->Quantize(289, 290, 0.12598426640033722, 0);
  g->Transpose(3265, 1873, {1,0});
  g->Binary(ynn_binary_multiply, 1870, 1872, 1868);
  g->Dot(290, 1873, YNN_INVALID_VALUE_ID, 1867, 1);
  g->DequantizeTensor(1867, YNN_INVALID_VALUE_ID, 1868, 1869);
  g->QuantizeTensor(1869, 2982, 1871, 291);
  g->Dequantize(291, 292, 0.10531344264745712, 0);
  g->Unary(ynn_unary_square, 292, 293);
  g->Reduce(ynn_reduce_sum, 293, 2619, {2}, true);
  g->ShapeProduct(293, 2618, {2});
  g->Binary(ynn_binary_divide, 2619, 2618, 294);
  g->Binary(ynn_binary_add, 294, 3016, 295);
  g->Unary(ynn_unary_rsqrt, 295, 297);
  g->Binary(ynn_binary_multiply, 292, 297, 298);
  g->Binary(ynn_binary_multiply, 298, 3268, 299);
  g->Binary(ynn_binary_add, 271, 299, 300);
  g->Binary(ynn_binary_multiply, 300, 3260, 301);
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
  g->Quantize(308, 309, 0.15428009629249573, 0);
  g->Transpose(3080, 1880, {1,0});
  g->Binary(ynn_binary_multiply, 1877, 1879, 1875);
  g->Dot(309, 1880, YNN_INVALID_VALUE_ID, 1874, 1);
  g->DequantizeTensor(1874, YNN_INVALID_VALUE_ID, 1875, 1876);
  g->QuantizeTensor(1876, 2982, 1878, 310);
  g->Dequantize(310, 311, 0.19881890714168549, 0);
  g->Reshape(311, 312, {1,0,1,256});
  g->Transpose(312, 313, {0,2,1,3});
  g->Unary(ynn_unary_square, 313, 314);
  g->Reduce(ynn_reduce_sum, 314, 2627, {3}, true);
  g->ShapeProduct(314, 2626, {3});
  g->Binary(ynn_binary_divide, 2627, 2626, 315);
  g->Binary(ynn_binary_add, 315, 3016, 316);
  g->Unary(ynn_unary_rsqrt, 316, 317);
  g->Binary(ynn_binary_multiply, 313, 317, 320);
  g->Binary(ynn_binary_multiply, 320, 3079, 321);
  g->Slice(321, 322, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(321, 323, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 323, 324);
  g->Concat({324,322}, 325, 3);
  g->Binary(ynn_binary_multiply, 321, 1096, 326);
  g->Binary(ynn_binary_multiply, 325, 1199, 327);
  g->Binary(ynn_binary_add, 326, 327, 328);
  g->Transpose(3084, 1885, {1,0});
  g->Binary(ynn_binary_multiply, 1877, 1884, 1882);
  g->Dot(309, 1885, YNN_INVALID_VALUE_ID, 1881, 1);
  g->DequantizeTensor(1881, YNN_INVALID_VALUE_ID, 1882, 1883);
  g->QuantizeTensor(1883, 2982, 1878, 330);
  g->Dequantize(330, 331, 0.19881890714168549, 0);
  g->Reshape(331, 332, {1,0,1,256});
  g->Transpose(332, 333, {0,2,1,3});
  g->Unary(ynn_unary_square, 333, 334);
  g->Reduce(ynn_reduce_sum, 334, 2629, {3}, true);
  g->ShapeProduct(334, 2628, {3});
  g->Binary(ynn_binary_divide, 2629, 2628, 335);
  g->Binary(ynn_binary_add, 335, 3016, 336);
  g->Unary(ynn_unary_rsqrt, 336, 337);
  g->Binary(ynn_binary_multiply, 333, 337, 338);
}

// Scope: "Layer10 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(328, 339, 0.005712664220482111, 0);
  g->Append(2985, 339, 3295, 2, s2, s1);
  g->View(3295, 3325, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(338, 341, 0.047244105488061905, 0);
  g->Append(3000, 341, 3310, 2, s2, s1);
  g->View(3310, 3339, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer10 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(3083, 1898, {1,0});
  g->Binary(ynn_binary_multiply, 1877, 1897, 1894);
  g->Dot(309, 1898, YNN_INVALID_VALUE_ID, 1893, 1);
  g->DequantizeTensor(1893, YNN_INVALID_VALUE_ID, 1894, 1895);
  g->QuantizeTensor(1895, 2982, 1896, 342);
  g->Dequantize(342, 343, 0.3484252095222473, 0);
  g->SplitDim(343, 344, 2, {8,256});
  g->Transpose(344, 345, {0,2,1,3});
  g->Unary(ynn_unary_square, 345, 347);
  g->Reduce(ynn_reduce_sum, 347, 2631, {3}, true);
  g->ShapeProduct(347, 2630, {3});
  g->Binary(ynn_binary_divide, 2631, 2630, 348);
  g->Binary(ynn_binary_add, 348, 3016, 349);
  g->Unary(ynn_unary_rsqrt, 349, 350);
  g->Binary(ynn_binary_multiply, 345, 350, 351);
  g->Binary(ynn_binary_multiply, 351, 3082, 352);
  g->Slice(352, 353, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(352, 354, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 354, 355);
  g->Concat({355,353}, 356, 3);
  g->Binary(ynn_binary_multiply, 352, 1096, 358);
  g->Binary(ynn_binary_multiply, 356, 1199, 359);
  g->Binary(ynn_binary_add, 358, 359, 360);
}

// Scope: "Layer10 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(3325, 361, 0.005712664220482111, 0);
  g->Dequantize(3339, 362, 0.047244105488061905, 0);
  g->Matmul(360, 361, 363, false, true);
  g->Mask(363, 3022, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 3022, 2635, {-1}, true);
  g->Binary(ynn_binary_subtract, 3022, 2635, 2632);
  g->Unary(ynn_unary_exp, 2632, 2633);
  g->Reduce(ynn_reduce_sum, 2633, 2636, {-1}, true);
  g->Binary(ynn_binary_divide, 2545, 2636, 2634);
  g->Binary(ynn_binary_multiply, 2633, 2634, 364);
  g->Matmul(364, 362, 365, false, false);
}

// Scope: "Layer10 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(365, 366, {0,2,1,3});
  g->FuseDims(366, 368, 2, 2);
  g->Quantize(368, 369, 0.028051190078258514, 0);
  g->Transpose(3081, 1905, {1,0});
  g->Binary(ynn_binary_multiply, 1902, 1904, 1900);
  g->Dot(369, 1905, YNN_INVALID_VALUE_ID, 1899, 1);
  g->DequantizeTensor(1899, YNN_INVALID_VALUE_ID, 1900, 1901);
  g->QuantizeTensor(1901, 2982, 1903, 370);
  g->Dequantize(370, 371, 0.029417896643280983, 0);
}

// Scope: "Layer10 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 301, 302);
  g->Reduce(ynn_reduce_sum, 302, 2621, {2}, true);
  g->ShapeProduct(302, 2620, {2});
  g->Binary(ynn_binary_divide, 2621, 2620, 303);
  g->Binary(ynn_binary_add, 303, 3016, 304);
  g->Unary(ynn_unary_rsqrt, 304, 305);
  g->Binary(ynn_binary_multiply, 301, 305, 306);
  g->Binary(ynn_binary_multiply, 306, 3068, 308);
  BuildLayer10AttentionKvProjection(ctx);
  BuildLayer10AttentionCacheUpdate(ctx);
  BuildLayer10AttentionQueryProjection(ctx);
  BuildLayer10AttentionSdpa(ctx);
  BuildLayer10AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 371, 372);
  g->Reduce(ynn_reduce_sum, 372, 2640, {2}, true);
  g->ShapeProduct(372, 2639, {2});
  g->Binary(ynn_binary_divide, 2640, 2639, 373);
  g->Binary(ynn_binary_add, 373, 3016, 374);
  g->Unary(ynn_unary_rsqrt, 374, 375);
  g->Binary(ynn_binary_multiply, 371, 375, 376);
  g->Binary(ynn_binary_multiply, 376, 3075, 377);
  g->Binary(ynn_binary_add, 377, 301, 379);
}

// Scope: "Layer10 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 379, 380);
  g->Reduce(ynn_reduce_sum, 380, 2642, {2}, true);
  g->ShapeProduct(380, 2641, {2});
  g->Binary(ynn_binary_divide, 2642, 2641, 381);
  g->Binary(ynn_binary_add, 381, 3016, 382);
  g->Unary(ynn_unary_rsqrt, 382, 383);
  g->Binary(ynn_binary_multiply, 379, 383, 384);
  g->Binary(ynn_binary_multiply, 384, 3078, 385);
  g->Quantize(385, 386, 0.018714377656579018, 0);
  g->Transpose(3072, 1912, {1,0});
  g->Binary(ynn_binary_multiply, 1909, 1911, 1907);
  g->Dot(386, 1912, YNN_INVALID_VALUE_ID, 1906, 1);
  g->DequantizeTensor(1906, YNN_INVALID_VALUE_ID, 1907, 1908);
  g->QuantizeTensor(1908, 2982, 1910, 387);
  g->Dequantize(387, 388, 0.01808563992381096, 0);
  g->Transpose(3071, 1917, {1,0});
  g->Binary(ynn_binary_multiply, 1909, 1916, 1914);
  g->Dot(386, 1917, YNN_INVALID_VALUE_ID, 1913, 1);
  g->DequantizeTensor(1913, YNN_INVALID_VALUE_ID, 1914, 1915);
  g->QuantizeTensor(1915, 2982, 1910, 390);
  g->Dequantize(390, 391, 0.01808563992381096, 0);
  g->Polynomial(391, 2645, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2645, 2646);
  g->Binary(ynn_binary_add, 2646, 2545, 2643);
  g->Binary(ynn_binary_multiply, 391, 2543, 2644);
  g->Binary(ynn_binary_multiply, 2644, 2643, 392);
  g->Binary(ynn_binary_multiply, 388, 392, 393);
  g->Quantize(393, 394, 0.01304134912788868, 0);
  g->Transpose(3070, 1924, {1,0});
  g->Binary(ynn_binary_multiply, 1921, 1923, 1919);
  g->Dot(394, 1924, YNN_INVALID_VALUE_ID, 1918, 1);
  g->DequantizeTensor(1918, YNN_INVALID_VALUE_ID, 1919, 1920);
  g->QuantizeTensor(1920, 2982, 1922, 395);
  g->Dequantize(395, 396, 0.011867290362715721, 0);
  g->Unary(ynn_unary_square, 396, 397);
  g->Reduce(ynn_reduce_sum, 397, 2648, {2}, true);
  g->ShapeProduct(397, 2647, {2});
  g->Binary(ynn_binary_divide, 2648, 2647, 398);
  g->Binary(ynn_binary_add, 398, 3016, 400);
  g->Unary(ynn_unary_rsqrt, 400, 401);
  g->Binary(ynn_binary_multiply, 396, 401, 402);
  g->Binary(ynn_binary_multiply, 402, 3076, 403);
  g->Binary(ynn_binary_add, 403, 379, 404);
}

// Scope: "Layer10 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(421, 405, {0,0,10,0}, {-1,-1,1,-1});
  g->Reshape(405, 406, {1,0,256});
  g->Unary(ynn_unary_square, 406, 407);
  g->Reduce(ynn_reduce_sum, 407, 2650, {2}, true);
  g->ShapeProduct(407, 2649, {2});
  g->Binary(ynn_binary_divide, 2650, 2649, 408);
  g->Binary(ynn_binary_add, 408, 3016, 409);
  g->Unary(ynn_unary_rsqrt, 409, 411);
  g->Binary(ynn_binary_multiply, 406, 411, 412);
  g->Binary(ynn_binary_multiply, 412, 3277, 413);
  g->Binary(ynn_binary_multiply, 3280, 3019, 414);
  g->Binary(ynn_binary_add, 413, 414, 415);
  g->Binary(ynn_binary_multiply, 415, 3014, 416);
  g->Quantize(404, 417, 0.14669467508792877, 0);
  g->Transpose(3073, 1931, {1,0});
  g->Binary(ynn_binary_multiply, 1928, 1930, 1926);
  g->Dot(417, 1931, YNN_INVALID_VALUE_ID, 1925, 1);
  g->DequantizeTensor(1925, YNN_INVALID_VALUE_ID, 1926, 1927);
  g->QuantizeTensor(1927, 2982, 1929, 418);
  g->Dequantize(418, 419, 0.038631901144981384, 0);
  g->Polynomial(419, 2653, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2653, 2654);
  g->Binary(ynn_binary_add, 2654, 2545, 2651);
  g->Binary(ynn_binary_multiply, 419, 2543, 2652);
  g->Binary(ynn_binary_multiply, 2652, 2651, 420);
  g->Binary(ynn_binary_multiply, 420, 416, 423);
  g->Quantize(423, 424, 0.05610237270593643, 0);
  g->Transpose(3074, 1938, {1,0});
  g->Binary(ynn_binary_multiply, 1935, 1937, 1933);
  g->Dot(424, 1938, YNN_INVALID_VALUE_ID, 1932, 1);
  g->DequantizeTensor(1932, YNN_INVALID_VALUE_ID, 1933, 1934);
  g->QuantizeTensor(1934, 2982, 1936, 425);
  g->Dequantize(425, 426, 0.041538726538419724, 0);
  g->Unary(ynn_unary_square, 426, 427);
  g->Reduce(ynn_reduce_sum, 427, 2656, {2}, true);
  g->ShapeProduct(427, 2655, {2});
  g->Binary(ynn_binary_divide, 2656, 2655, 428);
  g->Binary(ynn_binary_add, 428, 3016, 429);
  g->Unary(ynn_unary_rsqrt, 429, 430);
  g->Binary(ynn_binary_multiply, 426, 430, 431);
  g->Binary(ynn_binary_multiply, 431, 3077, 432);
  g->Binary(ynn_binary_add, 404, 432, 434);
  g->Binary(ynn_binary_multiply, 434, 3069, 435);
}

// Scope: "Layer10"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10(Context& ctx) {
  BuildLayer10Attention(ctx);
  BuildLayer10Mlp(ctx);
  BuildLayer10PerLayerEmbedding(ctx);
}

// Scope: "Layer11 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(441, 442, 0.11506716161966324, 0);
  g->Transpose(3097, 1945, {1,0});
  g->Binary(ynn_binary_multiply, 1942, 1944, 1940);
  g->Dot(442, 1945, YNN_INVALID_VALUE_ID, 1939, 1);
  g->DequantizeTensor(1939, YNN_INVALID_VALUE_ID, 1940, 1941);
  g->QuantizeTensor(1941, 2982, 1943, 443);
  g->Dequantize(443, 445, 0.12696851789951324, 0);
  g->Reshape(445, 446, {1,0,1,256});
  g->Transpose(446, 447, {0,2,1,3});
  g->Unary(ynn_unary_square, 447, 448);
  g->Reduce(ynn_reduce_sum, 448, 2660, {3}, true);
  g->ShapeProduct(448, 2659, {3});
  g->Binary(ynn_binary_divide, 2660, 2659, 449);
  g->Binary(ynn_binary_add, 449, 3016, 450);
  g->Unary(ynn_unary_rsqrt, 450, 451);
  g->Binary(ynn_binary_multiply, 447, 451, 452);
  g->Binary(ynn_binary_multiply, 452, 3096, 453);
  g->Slice(453, 454, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(453, 456, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 456, 457);
  g->Concat({457,454}, 458, 3);
  g->Binary(ynn_binary_multiply, 453, 1096, 459);
  g->Binary(ynn_binary_multiply, 458, 1199, 460);
  g->Binary(ynn_binary_add, 459, 460, 461);
  g->Transpose(3101, 1950, {1,0});
  g->Binary(ynn_binary_multiply, 1942, 1949, 1947);
  g->Dot(442, 1950, YNN_INVALID_VALUE_ID, 1946, 1);
  g->DequantizeTensor(1946, YNN_INVALID_VALUE_ID, 1947, 1948);
  g->QuantizeTensor(1948, 2982, 1943, 462);
  g->Dequantize(462, 463, 0.12696851789951324, 0);
  g->Reshape(463, 464, {1,0,1,256});
  g->Transpose(464, 466, {0,2,1,3});
  g->Unary(ynn_unary_square, 466, 467);
  g->Reduce(ynn_reduce_sum, 467, 2664, {3}, true);
  g->ShapeProduct(467, 2663, {3});
  g->Binary(ynn_binary_divide, 2664, 2663, 468);
  g->Binary(ynn_binary_add, 468, 3016, 469);
  g->Unary(ynn_unary_rsqrt, 469, 470);
  g->Binary(ynn_binary_multiply, 466, 470, 471);
}

// Scope: "Layer11 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(461, 472, 0.005907459184527397, 0);
  g->Append(2986, 472, 3296, 2, s2, s1);
  g->View(3296, 3326, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(471, 473, 0.047244105488061905, 0);
  g->Append(3001, 473, 3311, 2, s2, s1);
  g->View(3311, 3340, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer11 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(3100, 1956, {1,0});
  g->Binary(ynn_binary_multiply, 1942, 1955, 1952);
  g->Dot(442, 1956, YNN_INVALID_VALUE_ID, 1951, 1);
  g->DequantizeTensor(1951, YNN_INVALID_VALUE_ID, 1952, 1953);
  g->QuantizeTensor(1953, 2982, 1954, 475);
  g->Dequantize(475, 476, 0.2736220359802246, 0);
  g->SplitDim(476, 477, 2, {8,256});
  g->Transpose(477, 478, {0,2,1,3});
  g->Unary(ynn_unary_square, 478, 479);
  g->Reduce(ynn_reduce_sum, 479, 2666, {3}, true);
  g->ShapeProduct(479, 2665, {3});
  g->Binary(ynn_binary_divide, 2666, 2665, 480);
  g->Binary(ynn_binary_add, 480, 3016, 481);
  g->Unary(ynn_unary_rsqrt, 481, 483);
  g->Binary(ynn_binary_multiply, 478, 483, 484);
  g->Binary(ynn_binary_multiply, 484, 3099, 485);
  g->Slice(485, 486, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(485, 487, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 487, 488);
  g->Concat({488,486}, 489, 3);
  g->Binary(ynn_binary_multiply, 485, 1096, 490);
  g->Binary(ynn_binary_multiply, 489, 1199, 491);
  g->Binary(ynn_binary_add, 490, 491, 492);
}

// Scope: "Layer11 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(3326, 494, 0.005907459184527397, 0);
  g->Dequantize(3340, 495, 0.047244105488061905, 0);
  g->Matmul(492, 494, 496, false, true);
  g->Mask(496, 3023, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 3023, 2670, {-1}, true);
  g->Binary(ynn_binary_subtract, 3023, 2670, 2667);
  g->Unary(ynn_unary_exp, 2667, 2668);
  g->Reduce(ynn_reduce_sum, 2668, 2671, {-1}, true);
  g->Binary(ynn_binary_divide, 2545, 2671, 2669);
  g->Binary(ynn_binary_multiply, 2668, 2669, 497);
  g->Matmul(497, 495, 498, false, false);
}

// Scope: "Layer11 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(498, 499, {0,2,1,3});
  g->FuseDims(499, 500, 2, 2);
  g->Quantize(500, 501, 0.026082687079906464, 0);
  g->Transpose(3098, 1963, {1,0});
  g->Binary(ynn_binary_multiply, 1960, 1962, 1958);
  g->Dot(501, 1963, YNN_INVALID_VALUE_ID, 1957, 1);
  g->DequantizeTensor(1957, YNN_INVALID_VALUE_ID, 1958, 1959);
  g->QuantizeTensor(1959, 2982, 1961, 502);
  g->Dequantize(502, 504, 0.028822369873523712, 0);
}

// Scope: "Layer11 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 435, 436);
  g->Reduce(ynn_reduce_sum, 436, 2658, {2}, true);
  g->ShapeProduct(436, 2657, {2});
  g->Binary(ynn_binary_divide, 2658, 2657, 437);
  g->Binary(ynn_binary_add, 437, 3016, 438);
  g->Unary(ynn_unary_rsqrt, 438, 439);
  g->Binary(ynn_binary_multiply, 435, 439, 440);
  g->Binary(ynn_binary_multiply, 440, 3085, 441);
  BuildLayer11AttentionKvProjection(ctx);
  BuildLayer11AttentionCacheUpdate(ctx);
  BuildLayer11AttentionQueryProjection(ctx);
  BuildLayer11AttentionSdpa(ctx);
  BuildLayer11AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 504, 505);
  g->Reduce(ynn_reduce_sum, 505, 2673, {2}, true);
  g->ShapeProduct(505, 2672, {2});
  g->Binary(ynn_binary_divide, 2673, 2672, 506);
  g->Binary(ynn_binary_add, 506, 3016, 507);
  g->Unary(ynn_unary_rsqrt, 507, 508);
  g->Binary(ynn_binary_multiply, 504, 508, 509);
  g->Binary(ynn_binary_multiply, 509, 3092, 510);
  g->Binary(ynn_binary_add, 510, 435, 511);
}

// Scope: "Layer11 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 511, 512);
  g->Reduce(ynn_reduce_sum, 512, 2675, {2}, true);
  g->ShapeProduct(512, 2674, {2});
  g->Binary(ynn_binary_divide, 2675, 2674, 513);
  g->Binary(ynn_binary_add, 513, 3016, 515);
  g->Unary(ynn_unary_rsqrt, 515, 516);
  g->Binary(ynn_binary_multiply, 511, 516, 517);
  g->Binary(ynn_binary_multiply, 517, 3095, 518);
  g->Quantize(518, 519, 0.015670500695705414, 0);
  g->Transpose(3089, 1977, {1,0});
  g->Binary(ynn_binary_multiply, 1974, 1976, 1972);
  g->Dot(519, 1977, YNN_INVALID_VALUE_ID, 1971, 1);
  g->DequantizeTensor(1971, YNN_INVALID_VALUE_ID, 1972, 1973);
  g->QuantizeTensor(1973, 2982, 1975, 520);
  g->Dequantize(520, 521, 0.015255915932357311, 0);
  g->Transpose(3088, 1982, {1,0});
  g->Binary(ynn_binary_multiply, 1974, 1981, 1979);
  g->Dot(519, 1982, YNN_INVALID_VALUE_ID, 1978, 1);
  g->DequantizeTensor(1978, YNN_INVALID_VALUE_ID, 1979, 1980);
  g->QuantizeTensor(1980, 2982, 1975, 522);
  g->Dequantize(522, 523, 0.015255915932357311, 0);
  g->Polynomial(523, 2678, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2678, 2679);
  g->Binary(ynn_binary_add, 2679, 2545, 2676);
  g->Binary(ynn_binary_multiply, 523, 2543, 2677);
  g->Binary(ynn_binary_multiply, 2677, 2676, 526);
  g->Binary(ynn_binary_multiply, 521, 526, 527);
  g->Quantize(527, 528, 0.011195876635611057, 0);
  g->Transpose(3087, 1989, {1,0});
  g->Binary(ynn_binary_multiply, 1986, 1988, 1984);
  g->Dot(528, 1989, YNN_INVALID_VALUE_ID, 1983, 1);
  g->DequantizeTensor(1983, YNN_INVALID_VALUE_ID, 1984, 1985);
  g->QuantizeTensor(1985, 2982, 1987, 529);
  g->Dequantize(529, 530, 0.004389102105051279, 0);
  g->Unary(ynn_unary_square, 530, 531);
  g->Reduce(ynn_reduce_sum, 531, 2681, {2}, true);
  g->ShapeProduct(531, 2680, {2});
  g->Binary(ynn_binary_divide, 2681, 2680, 532);
  g->Binary(ynn_binary_add, 532, 3016, 533);
  g->Unary(ynn_unary_rsqrt, 533, 534);
  g->Binary(ynn_binary_multiply, 530, 534, 535);
  g->Binary(ynn_binary_multiply, 535, 3093, 537);
  g->Binary(ynn_binary_add, 537, 511, 538);
}

// Scope: "Layer11 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(421, 539, {0,0,11,0}, {-1,-1,1,-1});
  g->Reshape(539, 540, {1,0,256});
  g->Unary(ynn_unary_square, 540, 541);
  g->Reduce(ynn_reduce_sum, 541, 2683, {2}, true);
  g->ShapeProduct(541, 2682, {2});
  g->Binary(ynn_binary_divide, 2683, 2682, 542);
  g->Binary(ynn_binary_add, 542, 3016, 543);
  g->Unary(ynn_unary_rsqrt, 543, 544);
  g->Binary(ynn_binary_multiply, 540, 544, 545);
  g->Binary(ynn_binary_multiply, 545, 3277, 546);
  g->Binary(ynn_binary_multiply, 3281, 3019, 548);
  g->Binary(ynn_binary_add, 546, 548, 549);
  g->Binary(ynn_binary_multiply, 549, 3014, 550);
  g->Quantize(538, 551, 0.1750430017709732, 0);
  g->Transpose(3090, 1996, {1,0});
  g->Binary(ynn_binary_multiply, 1993, 1995, 1991);
  g->Dot(551, 1996, YNN_INVALID_VALUE_ID, 1990, 1);
  g->DequantizeTensor(1990, YNN_INVALID_VALUE_ID, 1991, 1992);
  g->QuantizeTensor(1992, 2982, 1994, 552);
  g->Dequantize(552, 553, 0.07529528439044952, 0);
  g->Polynomial(553, 2686, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2686, 2687);
  g->Binary(ynn_binary_add, 2687, 2545, 2684);
  g->Binary(ynn_binary_multiply, 553, 2543, 2685);
  g->Binary(ynn_binary_multiply, 2685, 2684, 554);
  g->Binary(ynn_binary_multiply, 554, 550, 555);
  g->Quantize(555, 556, 0.15846458077430725, 0);
  g->Transpose(3091, 2003, {1,0});
  g->Binary(ynn_binary_multiply, 2000, 2002, 1998);
  g->Dot(556, 2003, YNN_INVALID_VALUE_ID, 1997, 1);
  g->DequantizeTensor(1997, YNN_INVALID_VALUE_ID, 1998, 1999);
  g->QuantizeTensor(1999, 2982, 2001, 557);
  g->Dequantize(557, 559, 0.1771666705608368, 0);
  g->Unary(ynn_unary_square, 559, 560);
  g->Reduce(ynn_reduce_sum, 560, 2689, {2}, true);
  g->ShapeProduct(560, 2688, {2});
  g->Binary(ynn_binary_divide, 2689, 2688, 561);
  g->Binary(ynn_binary_add, 561, 3016, 562);
  g->Unary(ynn_unary_rsqrt, 562, 563);
  g->Binary(ynn_binary_multiply, 559, 563, 564);
  g->Binary(ynn_binary_multiply, 564, 3094, 565);
  g->Binary(ynn_binary_add, 538, 565, 566);
  g->Binary(ynn_binary_multiply, 566, 3086, 567);
}

// Scope: "Layer11"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11(Context& ctx) {
  BuildLayer11Attention(ctx);
  BuildLayer11Mlp(ctx);
  BuildLayer11PerLayerEmbedding(ctx);
}

// Scope: "Layer12 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(574, 575, 0.08767248690128326, 0);
  g->Transpose(3114, 2010, {1,0});
  g->Binary(ynn_binary_multiply, 2007, 2009, 2005);
  g->Dot(575, 2010, YNN_INVALID_VALUE_ID, 2004, 1);
  g->DequantizeTensor(2004, YNN_INVALID_VALUE_ID, 2005, 2006);
  g->QuantizeTensor(2006, 2982, 2008, 576);
  g->Dequantize(576, 577, 0.08070866763591766, 0);
  g->Reshape(577, 578, {1,0,1,256});
  g->Transpose(578, 579, {0,2,1,3});
  g->Unary(ynn_unary_square, 579, 581);
  g->Reduce(ynn_reduce_sum, 581, 2695, {3}, true);
  g->ShapeProduct(581, 2694, {3});
  g->Binary(ynn_binary_divide, 2695, 2694, 582);
  g->Binary(ynn_binary_add, 582, 3016, 583);
  g->Unary(ynn_unary_rsqrt, 583, 584);
  g->Binary(ynn_binary_multiply, 579, 584, 585);
  g->Binary(ynn_binary_multiply, 585, 3113, 586);
  g->Slice(586, 587, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(586, 588, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 588, 589);
  g->Concat({589,587}, 590, 3);
  g->Binary(ynn_binary_multiply, 586, 1096, 592);
  g->Binary(ynn_binary_multiply, 590, 1199, 593);
  g->Binary(ynn_binary_add, 592, 593, 594);
  g->Transpose(3118, 2015, {1,0});
  g->Binary(ynn_binary_multiply, 2007, 2014, 2012);
  g->Dot(575, 2015, YNN_INVALID_VALUE_ID, 2011, 1);
  g->DequantizeTensor(2011, YNN_INVALID_VALUE_ID, 2012, 2013);
  g->QuantizeTensor(2013, 2982, 2008, 595);
  g->Dequantize(595, 596, 0.08070866763591766, 0);
  g->Reshape(596, 597, {1,0,1,256});
  g->Transpose(597, 598, {0,2,1,3});
  g->Unary(ynn_unary_square, 598, 599);
  g->Reduce(ynn_reduce_sum, 599, 2697, {3}, true);
  g->ShapeProduct(599, 2696, {3});
  g->Binary(ynn_binary_divide, 2697, 2696, 600);
  g->Binary(ynn_binary_add, 600, 3016, 602);
  g->Unary(ynn_unary_rsqrt, 602, 603);
  g->Binary(ynn_binary_multiply, 598, 603, 604);
}

// Scope: "Layer12 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(594, 605, 0.005788442213088274, 0);
  g->Append(2987, 605, 3297, 2, s2, s1);
  g->View(3297, 3327, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(604, 606, 0.047244105488061905, 0);
  g->Append(3002, 606, 3312, 2, s2, s1);
  g->View(3312, 3341, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer12 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(3117, 2021, {1,0});
  g->Binary(ynn_binary_multiply, 2007, 2020, 2017);
  g->Dot(575, 2021, YNN_INVALID_VALUE_ID, 2016, 1);
  g->DequantizeTensor(2016, YNN_INVALID_VALUE_ID, 2017, 2018);
  g->QuantizeTensor(2018, 2982, 2019, 608);
  g->Dequantize(608, 609, 0.12795276939868927, 0);
  g->SplitDim(609, 610, 2, {8,256});
  g->Transpose(610, 611, {0,2,1,3});
  g->Unary(ynn_unary_square, 611, 612);
  g->Reduce(ynn_reduce_sum, 612, 2699, {3}, true);
  g->ShapeProduct(612, 2698, {3});
  g->Binary(ynn_binary_divide, 2699, 2698, 613);
  g->Binary(ynn_binary_add, 613, 3016, 614);
  g->Unary(ynn_unary_rsqrt, 614, 615);
  g->Binary(ynn_binary_multiply, 611, 615, 616);
  g->Binary(ynn_binary_multiply, 616, 3116, 617);
  g->Slice(617, 619, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(617, 620, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 620, 621);
  g->Concat({621,619}, 622, 3);
  g->Binary(ynn_binary_multiply, 617, 1096, 623);
  g->Binary(ynn_binary_multiply, 622, 1199, 624);
  g->Binary(ynn_binary_add, 623, 624, 625);
}

// Scope: "Layer12 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(3327, 626, 0.005788442213088274, 0);
  g->Dequantize(3341, 627, 0.047244105488061905, 0);
  g->Matmul(625, 626, 628, false, true);
  g->Mask(628, 3024, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 3024, 2705, {-1}, true);
  g->Binary(ynn_binary_subtract, 3024, 2705, 2702);
  g->Unary(ynn_unary_exp, 2702, 2703);
  g->Reduce(ynn_reduce_sum, 2703, 2706, {-1}, true);
  g->Binary(ynn_binary_divide, 2545, 2706, 2704);
  g->Binary(ynn_binary_multiply, 2703, 2704, 631);
  g->Matmul(631, 627, 632, false, false);
}

// Scope: "Layer12 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(632, 633, {0,2,1,3});
  g->FuseDims(633, 634, 2, 2);
  g->Quantize(634, 635, 0.028543315827846527, 0);
  g->Transpose(3115, 2028, {1,0});
  g->Binary(ynn_binary_multiply, 2025, 2027, 2023);
  g->Dot(635, 2028, YNN_INVALID_VALUE_ID, 2022, 1);
  g->DequantizeTensor(2022, YNN_INVALID_VALUE_ID, 2023, 2024);
  g->QuantizeTensor(2024, 2982, 2026, 636);
  g->Dequantize(636, 637, 0.021804405376315117, 0);
}

// Scope: "Layer12 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 567, 568);
  g->Reduce(ynn_reduce_sum, 568, 2693, {2}, true);
  g->ShapeProduct(568, 2692, {2});
  g->Binary(ynn_binary_divide, 2693, 2692, 570);
  g->Binary(ynn_binary_add, 570, 3016, 571);
  g->Unary(ynn_unary_rsqrt, 571, 572);
  g->Binary(ynn_binary_multiply, 567, 572, 573);
  g->Binary(ynn_binary_multiply, 573, 3102, 574);
  BuildLayer12AttentionKvProjection(ctx);
  BuildLayer12AttentionCacheUpdate(ctx);
  BuildLayer12AttentionQueryProjection(ctx);
  BuildLayer12AttentionSdpa(ctx);
  BuildLayer12AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 637, 638);
  g->Reduce(ynn_reduce_sum, 638, 2708, {2}, true);
  g->ShapeProduct(638, 2707, {2});
  g->Binary(ynn_binary_divide, 2708, 2707, 639);
  g->Binary(ynn_binary_add, 639, 3016, 641);
  g->Unary(ynn_unary_rsqrt, 641, 642);
  g->Binary(ynn_binary_multiply, 637, 642, 643);
  g->Binary(ynn_binary_multiply, 643, 3109, 644);
  g->Binary(ynn_binary_add, 644, 567, 645);
}

// Scope: "Layer12 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 645, 646);
  g->Reduce(ynn_reduce_sum, 646, 2710, {2}, true);
  g->ShapeProduct(646, 2709, {2});
  g->Binary(ynn_binary_divide, 2710, 2709, 647);
  g->Binary(ynn_binary_add, 647, 3016, 648);
  g->Unary(ynn_unary_rsqrt, 648, 649);
  g->Binary(ynn_binary_multiply, 645, 649, 650);
  g->Binary(ynn_binary_multiply, 650, 3112, 652);
  g->Quantize(652, 653, 0.013748278841376305, 0);
  g->Transpose(3106, 2035, {1,0});
  g->Binary(ynn_binary_multiply, 2032, 2034, 2030);
  g->Dot(653, 2035, YNN_INVALID_VALUE_ID, 2029, 1);
  g->DequantizeTensor(2029, YNN_INVALID_VALUE_ID, 2030, 2031);
  g->QuantizeTensor(2031, 2982, 2033, 654);
  g->Dequantize(654, 655, 0.012795286253094673, 0);
  g->Transpose(3105, 2040, {1,0});
  g->Binary(ynn_binary_multiply, 2032, 2039, 2037);
  g->Dot(653, 2040, YNN_INVALID_VALUE_ID, 2036, 1);
  g->DequantizeTensor(2036, YNN_INVALID_VALUE_ID, 2037, 2038);
  g->QuantizeTensor(2038, 2982, 2033, 656);
  g->Dequantize(656, 657, 0.012795286253094673, 0);
  g->Polynomial(657, 2713, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2713, 2714);
  g->Binary(ynn_binary_add, 2714, 2545, 2711);
  g->Binary(ynn_binary_multiply, 657, 2543, 2712);
  g->Binary(ynn_binary_multiply, 2712, 2711, 658);
  g->Binary(ynn_binary_multiply, 655, 658, 659);
  g->Quantize(659, 660, 0.00768947834149003, 0);
  g->Transpose(3104, 2047, {1,0});
  g->Binary(ynn_binary_multiply, 2044, 2046, 2042);
  g->Dot(660, 2047, YNN_INVALID_VALUE_ID, 2041, 1);
  g->DequantizeTensor(2041, YNN_INVALID_VALUE_ID, 2042, 2043);
  g->QuantizeTensor(2043, 2982, 2045, 662);
  g->Dequantize(662, 663, 0.005636297166347504, 0);
  g->Unary(ynn_unary_square, 663, 664);
  g->Reduce(ynn_reduce_sum, 664, 2716, {2}, true);
  g->ShapeProduct(664, 2715, {2});
  g->Binary(ynn_binary_divide, 2716, 2715, 665);
  g->Binary(ynn_binary_add, 665, 3016, 666);
  g->Unary(ynn_unary_rsqrt, 666, 667);
  g->Binary(ynn_binary_multiply, 663, 667, 668);
  g->Binary(ynn_binary_multiply, 668, 3110, 669);
  g->Binary(ynn_binary_add, 669, 645, 670);
}

// Scope: "Layer12 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(421, 671, {0,0,12,0}, {-1,-1,1,-1});
  g->Reshape(671, 673, {1,0,256});
  g->Unary(ynn_unary_square, 673, 674);
  g->Reduce(ynn_reduce_sum, 674, 2718, {2}, true);
  g->ShapeProduct(674, 2717, {2});
  g->Binary(ynn_binary_divide, 2718, 2717, 675);
  g->Binary(ynn_binary_add, 675, 3016, 676);
  g->Unary(ynn_unary_rsqrt, 676, 677);
  g->Binary(ynn_binary_multiply, 673, 677, 678);
  g->Binary(ynn_binary_multiply, 678, 3277, 679);
  g->Binary(ynn_binary_multiply, 3282, 3019, 680);
  g->Binary(ynn_binary_add, 679, 680, 681);
  g->Binary(ynn_binary_multiply, 681, 3014, 682);
  g->Quantize(670, 684, 0.19133253395557404, 0);
  g->Transpose(3107, 2053, {1,0});
  g->Binary(ynn_binary_multiply, 2051, 2052, 2049);
  g->Dot(684, 2053, YNN_INVALID_VALUE_ID, 2048, 1);
  g->DequantizeTensor(2048, YNN_INVALID_VALUE_ID, 2049, 2050);
  g->QuantizeTensor(2050, 2982, 1994, 685);
  g->Dequantize(685, 686, 0.07529528439044952, 0);
  g->Polynomial(686, 2721, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2721, 2722);
  g->Binary(ynn_binary_add, 2722, 2545, 2719);
  g->Binary(ynn_binary_multiply, 686, 2543, 2720);
  g->Binary(ynn_binary_multiply, 2720, 2719, 687);
  g->Binary(ynn_binary_multiply, 687, 682, 688);
  g->Quantize(688, 689, 0.12450788170099258, 0);
  g->Transpose(3108, 2060, {1,0});
  g->Binary(ynn_binary_multiply, 2057, 2059, 2055);
  g->Dot(689, 2060, YNN_INVALID_VALUE_ID, 2054, 1);
  g->DequantizeTensor(2054, YNN_INVALID_VALUE_ID, 2055, 2056);
  g->QuantizeTensor(2056, 2982, 2058, 690);
  g->Dequantize(690, 691, 0.12528184056282043, 0);
  g->Unary(ynn_unary_square, 691, 692);
  g->Reduce(ynn_reduce_sum, 692, 2724, {2}, true);
  g->ShapeProduct(692, 2723, {2});
  g->Binary(ynn_binary_divide, 2724, 2723, 693);
  g->Binary(ynn_binary_add, 693, 3016, 694);
  g->Unary(ynn_unary_rsqrt, 694, 695);
  g->Binary(ynn_binary_multiply, 691, 695, 696);
  g->Binary(ynn_binary_multiply, 696, 3111, 697);
  g->Binary(ynn_binary_add, 670, 697, 698);
  g->Binary(ynn_binary_multiply, 698, 3103, 699);
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
  g->Quantize(706, 707, 0.02862965501844883, 0);
  g->Transpose(3131, 2072, {1,0});
  g->Binary(ynn_binary_multiply, 2069, 2071, 2067);
  g->Dot(707, 2072, YNN_INVALID_VALUE_ID, 2066, 1);
  g->DequantizeTensor(2066, YNN_INVALID_VALUE_ID, 2067, 2068);
  g->QuantizeTensor(2068, 2982, 2070, 708);
  g->Dequantize(708, 709, 0.035925209522247314, 0);
  g->Reshape(709, 710, {1,0,1,256});
  g->Transpose(710, 711, {0,2,1,3});
  g->Unary(ynn_unary_square, 711, 712);
  g->Reduce(ynn_reduce_sum, 712, 2728, {3}, true);
  g->ShapeProduct(712, 2727, {3});
  g->Binary(ynn_binary_divide, 2728, 2727, 713);
  g->Binary(ynn_binary_add, 713, 3016, 714);
  g->Unary(ynn_unary_rsqrt, 714, 716);
  g->Binary(ynn_binary_multiply, 711, 716, 717);
  g->Binary(ynn_binary_multiply, 717, 3130, 718);
  g->Slice(718, 719, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(718, 720, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 720, 721);
  g->Concat({721,719}, 722, 3);
  g->Binary(ynn_binary_multiply, 718, 1096, 723);
  g->Binary(ynn_binary_multiply, 722, 1199, 724);
  g->Binary(ynn_binary_add, 723, 724, 725);
  g->Transpose(3135, 2077, {1,0});
  g->Binary(ynn_binary_multiply, 2069, 2076, 2074);
  g->Dot(707, 2077, YNN_INVALID_VALUE_ID, 2073, 1);
  g->DequantizeTensor(2073, YNN_INVALID_VALUE_ID, 2074, 2075);
  g->QuantizeTensor(2075, 2982, 2070, 727);
  g->Dequantize(727, 728, 0.035925209522247314, 0);
  g->Reshape(728, 729, {1,0,1,256});
  g->Transpose(729, 730, {0,2,1,3});
  g->Unary(ynn_unary_square, 730, 731);
  g->Reduce(ynn_reduce_sum, 731, 2730, {3}, true);
  g->ShapeProduct(731, 2729, {3});
  g->Binary(ynn_binary_divide, 2730, 2729, 732);
  g->Binary(ynn_binary_add, 732, 3016, 733);
  g->Unary(ynn_unary_rsqrt, 733, 734);
  g->Binary(ynn_binary_multiply, 730, 734, 735);
}

// Scope: "Layer13 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(725, 738, 0.0059552486054599285, 0);
  g->Append(2988, 738, 3298, 2, s2, s1);
  g->View(3298, 3328, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Quantize(735, 739, 0.047244105488061905, 0);
  g->Append(3003, 739, 3313, 2, s2, s1);
  g->View(3313, 3342, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
}

// Scope: "Layer13 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(3134, 2082, {1,0});
  g->Binary(ynn_binary_multiply, 2069, 2081, 2079);
  g->Dot(707, 2082, YNN_INVALID_VALUE_ID, 2078, 1);
  g->DequantizeTensor(2078, YNN_INVALID_VALUE_ID, 2079, 2080);
  g->QuantizeTensor(2080, 2982, 1889, 740);
  g->Dequantize(740, 741, 0.03764764964580536, 0);
  g->SplitDim(741, 742, 2, {8,256});
  g->Transpose(742, 744, {0,2,1,3});
  g->Unary(ynn_unary_square, 744, 745);
  g->Reduce(ynn_reduce_sum, 745, 2732, {3}, true);
  g->ShapeProduct(745, 2731, {3});
  g->Binary(ynn_binary_divide, 2732, 2731, 746);
  g->Binary(ynn_binary_add, 746, 3016, 747);
  g->Unary(ynn_unary_rsqrt, 747, 748);
  g->Binary(ynn_binary_multiply, 744, 748, 749);
  g->Binary(ynn_binary_multiply, 749, 3133, 750);
  g->Slice(750, 751, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(750, 752, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 752, 753);
  g->Concat({753,751}, 755, 3);
  g->Binary(ynn_binary_multiply, 750, 1096, 756);
  g->Binary(ynn_binary_multiply, 755, 1199, 757);
  g->Binary(ynn_binary_add, 756, 757, 758);
}

// Scope: "Layer13 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Dequantize(3328, 759, 0.0059552486054599285, 0);
  g->Dequantize(3342, 760, 0.047244105488061905, 0);
  g->Matmul(758, 759, 761, false, true);
  g->Mask(761, 3025, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 3025, 2738, {-1}, true);
  g->Binary(ynn_binary_subtract, 3025, 2738, 2735);
  g->Unary(ynn_unary_exp, 2735, 2736);
  g->Reduce(ynn_reduce_sum, 2736, 2739, {-1}, true);
  g->Binary(ynn_binary_divide, 2545, 2739, 2737);
  g->Binary(ynn_binary_multiply, 2736, 2737, 762);
  g->Matmul(762, 760, 763, false, false);
}

// Scope: "Layer13 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(763, 765, {0,2,1,3});
  g->FuseDims(765, 766, 2, 2);
  g->Quantize(766, 767, 0.026205718517303467, 0);
  g->Transpose(3132, 2089, {1,0});
  g->Binary(ynn_binary_multiply, 2086, 2088, 2084);
  g->Dot(767, 2089, YNN_INVALID_VALUE_ID, 2083, 1);
  g->DequantizeTensor(2083, YNN_INVALID_VALUE_ID, 2084, 2085);
  g->QuantizeTensor(2085, 2982, 2087, 768);
  g->Dequantize(768, 769, 0.03592992201447487, 0);
}

// Scope: "Layer13 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 699, 700);
  g->Reduce(ynn_reduce_sum, 700, 2726, {2}, true);
  g->ShapeProduct(700, 2725, {2});
  g->Binary(ynn_binary_divide, 2726, 2725, 701);
  g->Binary(ynn_binary_add, 701, 3016, 702);
  g->Unary(ynn_unary_rsqrt, 702, 703);
  g->Binary(ynn_binary_multiply, 699, 703, 705);
  g->Binary(ynn_binary_multiply, 705, 3119, 706);
  BuildLayer13AttentionKvProjection(ctx);
  BuildLayer13AttentionCacheUpdate(ctx);
  BuildLayer13AttentionQueryProjection(ctx);
  BuildLayer13AttentionSdpa(ctx);
  BuildLayer13AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 769, 770);
  g->Reduce(ynn_reduce_sum, 770, 2741, {2}, true);
  g->ShapeProduct(770, 2740, {2});
  g->Binary(ynn_binary_divide, 2741, 2740, 771);
  g->Binary(ynn_binary_add, 771, 3016, 772);
  g->Unary(ynn_unary_rsqrt, 772, 773);
  g->Binary(ynn_binary_multiply, 769, 773, 774);
  g->Binary(ynn_binary_multiply, 774, 3126, 776);
  g->Binary(ynn_binary_add, 776, 699, 777);
}

// Scope: "Layer13 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 777, 778);
  g->Reduce(ynn_reduce_sum, 778, 2743, {2}, true);
  g->ShapeProduct(778, 2742, {2});
  g->Binary(ynn_binary_divide, 2743, 2742, 779);
  g->Binary(ynn_binary_add, 779, 3016, 780);
  g->Unary(ynn_unary_rsqrt, 780, 781);
  g->Binary(ynn_binary_multiply, 777, 781, 782);
  g->Binary(ynn_binary_multiply, 782, 3129, 783);
  g->Quantize(783, 784, 0.0083004767075181, 0);
  g->Transpose(3123, 2096, {1,0});
  g->Binary(ynn_binary_multiply, 2093, 2095, 2091);
  g->Dot(784, 2096, YNN_INVALID_VALUE_ID, 2090, 1);
  g->DequantizeTensor(2090, YNN_INVALID_VALUE_ID, 2091, 2092);
  g->QuantizeTensor(2092, 2982, 2094, 785);
  g->Dequantize(785, 787, 0.011934065259993076, 0);
  g->Transpose(3122, 2101, {1,0});
  g->Binary(ynn_binary_multiply, 2093, 2100, 2098);
  g->Dot(784, 2101, YNN_INVALID_VALUE_ID, 2097, 1);
  g->DequantizeTensor(2097, YNN_INVALID_VALUE_ID, 2098, 2099);
  g->QuantizeTensor(2099, 2982, 2094, 788);
  g->Dequantize(788, 789, 0.011934065259993076, 0);
  g->Polynomial(789, 2746, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2746, 2747);
  g->Binary(ynn_binary_add, 2747, 2545, 2744);
  g->Binary(ynn_binary_multiply, 789, 2543, 2745);
  g->Binary(ynn_binary_multiply, 2745, 2744, 790);
  g->Binary(ynn_binary_multiply, 787, 790, 791);
  g->Quantize(791, 792, 0.0015532826073467731, 0);
  g->Transpose(3121, 2108, {1,0});
  g->Binary(ynn_binary_multiply, 2105, 2107, 2103);
  g->Dot(792, 2108, YNN_INVALID_VALUE_ID, 2102, 1);
  g->DequantizeTensor(2102, YNN_INVALID_VALUE_ID, 2103, 2104);
  g->QuantizeTensor(2104, 2982, 2106, 793);
  g->Dequantize(793, 794, 0.002153691602870822, 0);
  g->Unary(ynn_unary_square, 794, 795);
  g->Reduce(ynn_reduce_sum, 795, 2749, {2}, true);
  g->ShapeProduct(795, 2748, {2});
  g->Binary(ynn_binary_divide, 2749, 2748, 797);
  g->Binary(ynn_binary_add, 797, 3016, 798);
  g->Unary(ynn_unary_rsqrt, 798, 799);
  g->Binary(ynn_binary_multiply, 794, 799, 800);
  g->Binary(ynn_binary_multiply, 800, 3127, 801);
  g->Binary(ynn_binary_add, 801, 777, 802);
}

// Scope: "Layer13 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(421, 803, {0,0,13,0}, {-1,-1,1,-1});
  g->Reshape(803, 804, {1,0,256});
  g->Unary(ynn_unary_square, 804, 805);
  g->Reduce(ynn_reduce_sum, 805, 2751, {2}, true);
  g->ShapeProduct(805, 2750, {2});
  g->Binary(ynn_binary_divide, 2751, 2750, 806);
  g->Binary(ynn_binary_add, 806, 3016, 807);
  g->Unary(ynn_unary_rsqrt, 807, 808);
  g->Binary(ynn_binary_multiply, 804, 808, 809);
  g->Binary(ynn_binary_multiply, 809, 3277, 810);
  g->Binary(ynn_binary_multiply, 3283, 3019, 811);
  g->Binary(ynn_binary_add, 810, 811, 812);
  g->Binary(ynn_binary_multiply, 812, 3014, 813);
  g->Quantize(802, 814, 0.5171695351600647, 0);
  g->Transpose(3124, 2115, {1,0});
  g->Binary(ynn_binary_multiply, 2112, 2114, 2110);
  g->Dot(814, 2115, YNN_INVALID_VALUE_ID, 2109, 1);
  g->DequantizeTensor(2109, YNN_INVALID_VALUE_ID, 2110, 2111);
  g->QuantizeTensor(2111, 2982, 2113, 815);
  g->Dequantize(815, 816, 0.13385827839374542, 0);
  g->Polynomial(816, 2754, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2754, 2755);
  g->Binary(ynn_binary_add, 2755, 2545, 2752);
  g->Binary(ynn_binary_multiply, 816, 2543, 2753);
  g->Binary(ynn_binary_multiply, 2753, 2752, 817);
  g->Binary(ynn_binary_multiply, 817, 813, 818);
  g->Quantize(818, 819, 0.4094488322734833, 0);
  g->Transpose(3125, 2122, {1,0});
  g->Binary(ynn_binary_multiply, 2119, 2121, 2117);
  g->Dot(819, 2122, YNN_INVALID_VALUE_ID, 2116, 1);
  g->DequantizeTensor(2116, YNN_INVALID_VALUE_ID, 2117, 2118);
  g->QuantizeTensor(2118, 2982, 2120, 820);
  g->Dequantize(820, 821, 0.25065305829048157, 0);
  g->Unary(ynn_unary_square, 821, 822);
  g->Reduce(ynn_reduce_sum, 822, 2757, {2}, true);
  g->ShapeProduct(822, 2756, {2});
  g->Binary(ynn_binary_divide, 2757, 2756, 823);
  g->Binary(ynn_binary_add, 823, 3016, 824);
  g->Unary(ynn_unary_rsqrt, 824, 825);
  g->Binary(ynn_binary_multiply, 821, 825, 826);
  g->Binary(ynn_binary_multiply, 826, 3128, 828);
  g->Binary(ynn_binary_add, 802, 828, 829);
  g->Binary(ynn_binary_multiply, 829, 3120, 830);
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
  g->Quantize(836, 837, 0.20956376194953918, 0);
  g->Transpose(3138, 2129, {1,0});
  g->Binary(ynn_binary_multiply, 2126, 2128, 2124);
  g->Dot(837, 2129, YNN_INVALID_VALUE_ID, 2123, 1);
  g->DequantizeTensor(2123, YNN_INVALID_VALUE_ID, 2124, 2125);
  g->QuantizeTensor(2125, 2982, 2127, 839);
  g->Dequantize(839, 840, 0.21751970052719116, 0);
  g->Reshape(840, 841, {1,0,1,512});
  g->Transpose(841, 842, {0,2,1,3});
  g->Unary(ynn_unary_square, 842, 843);
  g->Reduce(ynn_reduce_sum, 843, 2761, {3}, true);
  g->ShapeProduct(843, 2760, {3});
  g->Binary(ynn_binary_divide, 2761, 2760, 844);
  g->Binary(ynn_binary_add, 844, 3016, 845);
  g->Unary(ynn_unary_rsqrt, 845, 846);
  g->Binary(ynn_binary_multiply, 842, 846, 847);
  g->Binary(ynn_binary_multiply, 847, 3137, 848);
  g->Slice(848, 849, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(848, 850, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 850, 851);
  g->Concat({851,849}, 852, 3);
  g->Binary(ynn_binary_multiply, 848, 1613, 853);
  g->Binary(ynn_binary_multiply, 852, 2, 854);
  g->Binary(ynn_binary_add, 853, 854, 855);
  g->Transpose(3139, 2134, {1,0});
  g->Binary(ynn_binary_multiply, 2126, 2133, 2131);
  g->Dot(837, 2134, YNN_INVALID_VALUE_ID, 2130, 1);
  g->DequantizeTensor(2130, YNN_INVALID_VALUE_ID, 2131, 2132);
  g->QuantizeTensor(2132, 2982, 2127, 856);
  g->Dequantize(856, 857, 0.21751970052719116, 0);
  g->Reshape(857, 858, {1,0,1,512});
  g->Transpose(858, 859, {0,2,1,3});
  g->Unary(ynn_unary_square, 859, 860);
  g->Reduce(ynn_reduce_sum, 860, 2763, {3}, true);
  g->ShapeProduct(860, 2762, {3});
  g->Binary(ynn_binary_divide, 2763, 2762, 861);
  g->Binary(ynn_binary_add, 861, 3016, 862);
  g->Unary(ynn_unary_rsqrt, 862, 863);
  g->Binary(ynn_binary_multiply, 859, 863, 864);
}

// Scope: "Layer14 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(855, 865, 0.001091228099539876, 0);
  g->Append(2989, 865, 3299, 2, s2, s1);
  g->Quantize(864, 867, 0.01785714365541935, 0);
  g->Append(3004, 867, 3314, 2, s2, s1);
}

// Scope: "Layer14 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 830, 831);
  g->Reduce(ynn_reduce_sum, 831, 2759, {2}, true);
  g->ShapeProduct(831, 2758, {2});
  g->Binary(ynn_binary_divide, 2759, 2758, 832);
  g->Binary(ynn_binary_add, 832, 3016, 833);
  g->Unary(ynn_unary_rsqrt, 833, 834);
  g->Binary(ynn_binary_multiply, 830, 834, 835);
  g->Binary(ynn_binary_multiply, 835, 3136, 836);
  BuildLayer14AttentionKvProjection(ctx);
  BuildLayer14AttentionCacheUpdate(ctx);
}

// Scope: "Layer14"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14(Context& ctx) {
  BuildLayer14Attention(ctx);
}

}  // namespace BuildGemma4PrefillSource
