// Generated YNNPACK builder; do not edit.
#include "gemma4_prefill_builder.h"

namespace BuildGemma4PrefillSource {

// Scope: "Layer9 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Quantize(191, 193, 0.016753647476434708, 0);
  g->Transpose(3260, 1854, {1,0});
  g->Binary(ynn_binary_multiply, 1851, 1853, 1849);
  g->Dot(193, 1854, YNN_INVALID_VALUE_ID, 1848, 1);
  g->DequantizeTensor(1848, YNN_INVALID_VALUE_ID, 1849, 1850);
  g->QuantizeTensor(1850, 2971, 1852, 194);
  g->Dequantize(194, 195, 0.020177174359560013, 0);
  g->Reshape(195, 196, {1,0,1,512});
  g->Transpose(196, 197, {0,2,1,3});
  g->Unary(ynn_unary_square, 197, 198);
  g->Reduce(ynn_reduce_sum, 198, 2607, {3}, true);
  g->ShapeProduct(198, 2606, {3});
  g->Binary(ynn_binary_divide, 2607, 2606, 199);
  g->Binary(ynn_binary_add, 199, 3004, 200);
  g->Binary(ynn_binary_pow, 200, 3006, 201);
  g->Binary(ynn_binary_multiply, 197, 201, 202);
  g->Convert(3259, 204);
  g->Binary(ynn_binary_multiply, 202, 204, 205);
  g->Slice(205, 206, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(205, 207, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 207, 208);
  g->Concat({208,206}, 209, 3);
  g->Binary(ynn_binary_multiply, 205, 1532, 210);
  g->Binary(ynn_binary_multiply, 209, 1634, 211);
  g->Binary(ynn_binary_add, 210, 211, 212);
  g->Transpose(3264, 1859, {1,0});
  g->Binary(ynn_binary_multiply, 1851, 1858, 1856);
  g->Dot(193, 1859, YNN_INVALID_VALUE_ID, 1855, 1);
  g->DequantizeTensor(1855, YNN_INVALID_VALUE_ID, 1856, 1857);
  g->QuantizeTensor(1857, 2971, 1852, 215);
  g->Dequantize(215, 216, 0.020177174359560013, 0);
  g->Reshape(216, 217, {1,0,1,512});
  g->Transpose(217, 218, {0,2,1,3});
  g->Unary(ynn_unary_square, 218, 219);
  g->Reduce(ynn_reduce_sum, 219, 2611, {3}, true);
  g->ShapeProduct(219, 2610, {3});
  g->Binary(ynn_binary_divide, 2611, 2610, 220);
  g->Binary(ynn_binary_add, 220, 3004, 221);
  g->Binary(ynn_binary_pow, 221, 3006, 222);
  g->Binary(ynn_binary_multiply, 218, 222, 223);
}

// Scope: "Layer9 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(212, 224, 0.0010733711533248425, 0);
  g->Append(2986, 224, 3296, 2, s2, s1);
  g->View(3296, 3325, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(3325, 226, 0.0010733711533248425, 0);
  g->Quantize(223, 227, 0.01785714365541935, 0);
  g->Append(3001, 227, 3311, 2, s2, s1);
  g->View(3311, 3339, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(3339, 228, 0.01785714365541935, 0);
}

// Scope: "Layer9 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(3263, 1865, {1,0});
  g->Binary(ynn_binary_multiply, 1851, 1864, 1861);
  g->Dot(193, 1865, YNN_INVALID_VALUE_ID, 1860, 1);
  g->DequantizeTensor(1860, YNN_INVALID_VALUE_ID, 1861, 1862);
  g->QuantizeTensor(1862, 2971, 1863, 229);
  g->Dequantize(229, 230, 0.029650600627064705, 0);
  g->SplitDim(230, 232, 2, {8,512});
  g->Transpose(232, 233, {0,2,1,3});
  g->Unary(ynn_unary_square, 233, 234);
  g->Reduce(ynn_reduce_sum, 234, 2613, {3}, true);
  g->ShapeProduct(234, 2612, {3});
  g->Binary(ynn_binary_divide, 2613, 2612, 235);
  g->Binary(ynn_binary_add, 235, 3004, 236);
  g->Binary(ynn_binary_pow, 236, 3006, 237);
  g->Binary(ynn_binary_multiply, 233, 237, 238);
  g->Convert(3262, 239);
  g->Binary(ynn_binary_multiply, 238, 239, 240);
  g->Slice(240, 241, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(240, 243, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 243, 244);
  g->Concat({244,241}, 245, 3);
  g->Binary(ynn_binary_multiply, 240, 1532, 246);
  g->Binary(ynn_binary_multiply, 245, 1634, 247);
  g->Binary(ynn_binary_add, 246, 247, 248);
}

// Scope: "Layer9 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(248, 226, 249, false, true);
  g->Mask(249, 3022, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 3022, 2617, {-1}, true);
  g->Binary(ynn_binary_subtract, 3022, 2617, 2614);
  g->Unary(ynn_unary_exp, 2614, 2615);
  g->Reduce(ynn_reduce_sum, 2615, 2618, {-1}, true);
  g->Binary(ynn_binary_divide, 2558, 2618, 2616);
  g->Binary(ynn_binary_multiply, 2615, 2616, 250);
  g->Matmul(250, 228, 251, false, false);
}

// Scope: "Layer9 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(251, 253, {0,2,1,3});
  g->FuseDims(253, 254, 2, 2);
  g->Quantize(254, 255, 0.017962608486413956, 0);
  g->Transpose(3261, 1872, {1,0});
  g->Binary(ynn_binary_multiply, 1869, 1871, 1867);
  g->Dot(255, 1872, YNN_INVALID_VALUE_ID, 1866, 1);
  g->DequantizeTensor(1866, YNN_INVALID_VALUE_ID, 1867, 1868);
  g->QuantizeTensor(1868, 2971, 1870, 256);
  g->Dequantize(256, 257, 0.02776472456753254, 0);
}

// Scope: "Layer9 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 184, 185);
  g->Reduce(ynn_reduce_sum, 185, 2605, {2}, true);
  g->ShapeProduct(185, 2604, {2});
  g->Binary(ynn_binary_divide, 2605, 2604, 186);
  g->Binary(ynn_binary_add, 186, 3004, 187);
  g->Binary(ynn_binary_pow, 187, 3006, 188);
  g->Binary(ynn_binary_multiply, 184, 188, 189);
  g->Convert(3248, 190);
  g->Binary(ynn_binary_multiply, 189, 190, 191);
  BuildLayer9AttentionKvProjection(ctx);
  BuildLayer9AttentionCacheUpdate(ctx);
  BuildLayer9AttentionQueryProjection(ctx);
  BuildLayer9AttentionSdpa(ctx);
  BuildLayer9AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 257, 258);
  g->Reduce(ynn_reduce_sum, 258, 2620, {2}, true);
  g->ShapeProduct(258, 2619, {2});
  g->Binary(ynn_binary_divide, 2620, 2619, 259);
  g->Binary(ynn_binary_add, 259, 3004, 260);
  g->Binary(ynn_binary_pow, 260, 3006, 261);
  g->Binary(ynn_binary_multiply, 257, 261, 262);
  g->Convert(3255, 264);
  g->Binary(ynn_binary_multiply, 262, 264, 265);
  g->Binary(ynn_binary_add, 184, 265, 266);
}

// Scope: "Layer9 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 266, 267);
  g->Reduce(ynn_reduce_sum, 267, 2622, {2}, true);
  g->ShapeProduct(267, 2621, {2});
  g->Binary(ynn_binary_divide, 2622, 2621, 268);
  g->Binary(ynn_binary_add, 268, 3004, 269);
  g->Binary(ynn_binary_pow, 269, 3006, 270);
  g->Binary(ynn_binary_multiply, 266, 270, 271);
  g->Convert(3258, 272);
  g->Binary(ynn_binary_multiply, 271, 272, 273);
  g->Quantize(273, 275, 0.028379227966070175, 0);
  g->Transpose(3252, 1879, {1,0});
  g->Binary(ynn_binary_multiply, 1876, 1878, 1874);
  g->Dot(275, 1879, YNN_INVALID_VALUE_ID, 1873, 1);
  g->DequantizeTensor(1873, YNN_INVALID_VALUE_ID, 1874, 1875);
  g->QuantizeTensor(1875, 2971, 1877, 276);
  g->Dequantize(276, 277, 0.01556349452584982, 0);
  g->Transpose(3251, 1884, {1,0});
  g->Binary(ynn_binary_multiply, 1876, 1883, 1881);
  g->Dot(275, 1884, YNN_INVALID_VALUE_ID, 1880, 1);
  g->DequantizeTensor(1880, YNN_INVALID_VALUE_ID, 1881, 1882);
  g->QuantizeTensor(1882, 2971, 1877, 278);
  g->Dequantize(278, 279, 0.01556349452584982, 0);
  g->Polynomial(279, 2625, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2625, 2626);
  g->Binary(ynn_binary_add, 2626, 2558, 2623);
  g->Binary(ynn_binary_multiply, 279, 2556, 2624);
  g->Binary(ynn_binary_multiply, 2624, 2623, 280);
  g->Binary(ynn_binary_multiply, 277, 280, 281);
  g->Quantize(281, 282, 0.011441939510405064, 0);
  g->Transpose(3250, 1891, {1,0});
  g->Binary(ynn_binary_multiply, 1888, 1890, 1886);
  g->Dot(282, 1891, YNN_INVALID_VALUE_ID, 1885, 1);
  g->DequantizeTensor(1885, YNN_INVALID_VALUE_ID, 1886, 1887);
  g->QuantizeTensor(1887, 2971, 1889, 283);
  g->Dequantize(283, 285, 0.005826006643474102, 0);
  g->Unary(ynn_unary_square, 285, 286);
  g->Reduce(ynn_reduce_sum, 286, 2628, {2}, true);
  g->ShapeProduct(286, 2627, {2});
  g->Binary(ynn_binary_divide, 2628, 2627, 287);
  g->Binary(ynn_binary_add, 287, 3004, 288);
  g->Binary(ynn_binary_pow, 288, 3006, 289);
  g->Binary(ynn_binary_multiply, 285, 289, 290);
  g->Convert(3256, 291);
  g->Binary(ynn_binary_multiply, 290, 291, 292);
  g->Binary(ynn_binary_add, 266, 292, 293);
}

// Scope: "Layer9 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(907, 294, {0,0,9,0}, {-1,-1,1,-1});
  g->Reshape(294, 296, {1,0,256});
  g->Binary(ynn_binary_add, 296, 3280, 297);
  g->Binary(ynn_binary_multiply, 297, 3003, 298);
  g->Quantize(293, 299, 0.22249335050582886, 0);
  g->Transpose(3253, 1898, {1,0});
  g->Binary(ynn_binary_multiply, 1895, 1897, 1893);
  g->Dot(299, 1898, YNN_INVALID_VALUE_ID, 1892, 1);
  g->DequantizeTensor(1892, YNN_INVALID_VALUE_ID, 1893, 1894);
  g->QuantizeTensor(1894, 2971, 1896, 300);
  g->Dequantize(300, 301, 0.04404528811573982, 0);
  g->Polynomial(301, 2631, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2631, 2632);
  g->Binary(ynn_binary_add, 2632, 2558, 2629);
  g->Binary(ynn_binary_multiply, 301, 2556, 2630);
  g->Binary(ynn_binary_multiply, 2630, 2629, 302);
  g->Binary(ynn_binary_multiply, 302, 298, 303);
  g->Quantize(303, 304, 0.12598426640033722, 0);
  g->Transpose(3254, 1905, {1,0});
  g->Binary(ynn_binary_multiply, 1902, 1904, 1900);
  g->Dot(304, 1905, YNN_INVALID_VALUE_ID, 1899, 1);
  g->DequantizeTensor(1899, YNN_INVALID_VALUE_ID, 1900, 1901);
  g->QuantizeTensor(1901, 2971, 1903, 305);
  g->Dequantize(305, 307, 0.10531344264745712, 0);
  g->Unary(ynn_unary_square, 307, 308);
  g->Reduce(ynn_reduce_sum, 308, 2634, {2}, true);
  g->ShapeProduct(308, 2633, {2});
  g->Binary(ynn_binary_divide, 2634, 2633, 309);
  g->Binary(ynn_binary_add, 309, 3004, 310);
  g->Binary(ynn_binary_pow, 310, 3006, 311);
  g->Binary(ynn_binary_multiply, 307, 311, 312);
  g->Convert(3257, 313);
  g->Binary(ynn_binary_multiply, 312, 313, 314);
  g->Binary(ynn_binary_add, 293, 314, 315);
  g->Convert(3249, 316);
  g->Binary(ynn_binary_multiply, 315, 316, 319);
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
  g->Quantize(326, 327, 0.15428009629249573, 0);
  g->Transpose(3069, 1912, {1,0});
  g->Binary(ynn_binary_multiply, 1909, 1911, 1907);
  g->Dot(327, 1912, YNN_INVALID_VALUE_ID, 1906, 1);
  g->DequantizeTensor(1906, YNN_INVALID_VALUE_ID, 1907, 1908);
  g->QuantizeTensor(1908, 2971, 1910, 328);
  g->Dequantize(328, 330, 0.19881890714168549, 0);
  g->Reshape(330, 331, {1,0,1,256});
  g->Transpose(331, 332, {0,2,1,3});
  g->Unary(ynn_unary_square, 332, 333);
  g->Reduce(ynn_reduce_sum, 333, 2638, {3}, true);
  g->ShapeProduct(333, 2637, {3});
  g->Binary(ynn_binary_divide, 2638, 2637, 334);
  g->Binary(ynn_binary_add, 334, 3004, 335);
  g->Binary(ynn_binary_pow, 335, 3006, 336);
  g->Binary(ynn_binary_multiply, 332, 336, 337);
  g->Convert(3068, 338);
  g->Binary(ynn_binary_multiply, 337, 338, 339);
  g->Slice(339, 341, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(339, 342, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 342, 343);
  g->Concat({343,341}, 344, 3);
  g->Binary(ynn_binary_multiply, 339, 1015, 345);
  g->Binary(ynn_binary_multiply, 344, 1118, 346);
  g->Binary(ynn_binary_add, 345, 346, 347);
  g->Transpose(3073, 1924, {1,0});
  g->Binary(ynn_binary_multiply, 1909, 1923, 1921);
  g->Dot(327, 1924, YNN_INVALID_VALUE_ID, 1920, 1);
  g->DequantizeTensor(1920, YNN_INVALID_VALUE_ID, 1921, 1922);
  g->QuantizeTensor(1922, 2971, 1910, 348);
  g->Dequantize(348, 349, 0.19881890714168549, 0);
  g->Reshape(349, 351, {1,0,1,256});
  g->Transpose(351, 352, {0,2,1,3});
  g->Unary(ynn_unary_square, 352, 353);
  g->Reduce(ynn_reduce_sum, 353, 2640, {3}, true);
  g->ShapeProduct(353, 2639, {3});
  g->Binary(ynn_binary_divide, 2640, 2639, 354);
  g->Binary(ynn_binary_add, 354, 3004, 355);
  g->Binary(ynn_binary_pow, 355, 3006, 356);
  g->Binary(ynn_binary_multiply, 352, 356, 357);
}

// Scope: "Layer10 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(347, 358, 0.005712664220482111, 0);
  g->Append(2974, 358, 3284, 2, s2, s1);
  g->View(3284, 3314, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(3314, 360, 0.005712664220482111, 0);
  g->Quantize(357, 361, 0.047244105488061905, 0);
  g->Append(2989, 361, 3299, 2, s2, s1);
  g->View(3299, 3328, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(3328, 362, 0.047244105488061905, 0);
}

// Scope: "Layer10 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(3072, 1930, {1,0});
  g->Binary(ynn_binary_multiply, 1909, 1929, 1926);
  g->Dot(327, 1930, YNN_INVALID_VALUE_ID, 1925, 1);
  g->DequantizeTensor(1925, YNN_INVALID_VALUE_ID, 1926, 1927);
  g->QuantizeTensor(1927, 2971, 1928, 363);
  g->Dequantize(363, 364, 0.3484252095222473, 0);
  g->SplitDim(364, 365, 2, {8,256});
  g->Transpose(365, 366, {0,2,1,3});
  g->Unary(ynn_unary_square, 366, 368);
  g->Reduce(ynn_reduce_sum, 368, 2646, {3}, true);
  g->ShapeProduct(368, 2645, {3});
  g->Binary(ynn_binary_divide, 2646, 2645, 369);
  g->Binary(ynn_binary_add, 369, 3004, 370);
  g->Binary(ynn_binary_pow, 370, 3006, 371);
  g->Binary(ynn_binary_multiply, 366, 371, 372);
  g->Convert(3071, 373);
  g->Binary(ynn_binary_multiply, 372, 373, 374);
  g->Slice(374, 375, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(374, 376, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 376, 377);
  g->Concat({377,375}, 379, 3);
  g->Binary(ynn_binary_multiply, 374, 1015, 380);
  g->Binary(ynn_binary_multiply, 379, 1118, 381);
  g->Binary(ynn_binary_add, 380, 381, 382);
}

// Scope: "Layer10 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(382, 360, 383, false, true);
  g->Mask(383, 3011, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 3011, 2650, {-1}, true);
  g->Binary(ynn_binary_subtract, 3011, 2650, 2647);
  g->Unary(ynn_unary_exp, 2647, 2648);
  g->Reduce(ynn_reduce_sum, 2648, 2651, {-1}, true);
  g->Binary(ynn_binary_divide, 2558, 2651, 2649);
  g->Binary(ynn_binary_multiply, 2648, 2649, 384);
  g->Matmul(384, 362, 385, false, false);
}

// Scope: "Layer10 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(385, 386, {0,2,1,3});
  g->FuseDims(386, 387, 2, 2);
  g->Quantize(387, 389, 0.028051190078258514, 0);
  g->Transpose(3070, 1944, {1,0});
  g->Binary(ynn_binary_multiply, 1941, 1943, 1939);
  g->Dot(389, 1944, YNN_INVALID_VALUE_ID, 1938, 1);
  g->DequantizeTensor(1938, YNN_INVALID_VALUE_ID, 1939, 1940);
  g->QuantizeTensor(1940, 2971, 1942, 390);
  g->Dequantize(390, 391, 0.029417896643280983, 0);
}

// Scope: "Layer10 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 319, 320);
  g->Reduce(ynn_reduce_sum, 320, 2636, {2}, true);
  g->ShapeProduct(320, 2635, {2});
  g->Binary(ynn_binary_divide, 2636, 2635, 321);
  g->Binary(ynn_binary_add, 321, 3004, 322);
  g->Binary(ynn_binary_pow, 322, 3006, 323);
  g->Binary(ynn_binary_multiply, 319, 323, 324);
  g->Convert(3057, 325);
  g->Binary(ynn_binary_multiply, 324, 325, 326);
  BuildLayer10AttentionKvProjection(ctx);
  BuildLayer10AttentionCacheUpdate(ctx);
  BuildLayer10AttentionQueryProjection(ctx);
  BuildLayer10AttentionSdpa(ctx);
  BuildLayer10AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 391, 392);
  g->Reduce(ynn_reduce_sum, 392, 2653, {2}, true);
  g->ShapeProduct(392, 2652, {2});
  g->Binary(ynn_binary_divide, 2653, 2652, 393);
  g->Binary(ynn_binary_add, 393, 3004, 394);
  g->Binary(ynn_binary_pow, 394, 3006, 395);
  g->Binary(ynn_binary_multiply, 391, 395, 396);
  g->Convert(3064, 397);
  g->Binary(ynn_binary_multiply, 396, 397, 398);
  g->Binary(ynn_binary_add, 319, 398, 400);
}

// Scope: "Layer10 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 400, 401);
  g->Reduce(ynn_reduce_sum, 401, 2655, {2}, true);
  g->ShapeProduct(401, 2654, {2});
  g->Binary(ynn_binary_divide, 2655, 2654, 402);
  g->Binary(ynn_binary_add, 402, 3004, 403);
  g->Binary(ynn_binary_pow, 403, 3006, 404);
  g->Binary(ynn_binary_multiply, 400, 404, 405);
  g->Convert(3067, 406);
  g->Binary(ynn_binary_multiply, 405, 406, 407);
  g->Quantize(407, 408, 0.018714377656579018, 0);
  g->Transpose(3061, 1951, {1,0});
  g->Binary(ynn_binary_multiply, 1948, 1950, 1946);
  g->Dot(408, 1951, YNN_INVALID_VALUE_ID, 1945, 1);
  g->DequantizeTensor(1945, YNN_INVALID_VALUE_ID, 1946, 1947);
  g->QuantizeTensor(1947, 2971, 1949, 409);
  g->Dequantize(409, 411, 0.01808563992381096, 0);
  g->Transpose(3060, 1956, {1,0});
  g->Binary(ynn_binary_multiply, 1948, 1955, 1953);
  g->Dot(408, 1956, YNN_INVALID_VALUE_ID, 1952, 1);
  g->DequantizeTensor(1952, YNN_INVALID_VALUE_ID, 1953, 1954);
  g->QuantizeTensor(1954, 2971, 1949, 412);
  g->Dequantize(412, 413, 0.01808563992381096, 0);
  g->Polynomial(413, 2658, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2658, 2659);
  g->Binary(ynn_binary_add, 2659, 2558, 2656);
  g->Binary(ynn_binary_multiply, 413, 2556, 2657);
  g->Binary(ynn_binary_multiply, 2657, 2656, 414);
  g->Binary(ynn_binary_multiply, 411, 414, 415);
  g->Quantize(415, 416, 0.01304134912788868, 0);
  g->Transpose(3059, 1963, {1,0});
  g->Binary(ynn_binary_multiply, 1960, 1962, 1958);
  g->Dot(416, 1963, YNN_INVALID_VALUE_ID, 1957, 1);
  g->DequantizeTensor(1957, YNN_INVALID_VALUE_ID, 1958, 1959);
  g->QuantizeTensor(1959, 2971, 1961, 417);
  g->Dequantize(417, 418, 0.011867290362715721, 0);
  g->Unary(ynn_unary_square, 418, 419);
  g->Reduce(ynn_reduce_sum, 419, 2663, {2}, true);
  g->ShapeProduct(419, 2662, {2});
  g->Binary(ynn_binary_divide, 2663, 2662, 422);
  g->Binary(ynn_binary_add, 422, 3004, 423);
  g->Binary(ynn_binary_pow, 423, 3006, 424);
  g->Binary(ynn_binary_multiply, 418, 424, 425);
  g->Convert(3065, 426);
  g->Binary(ynn_binary_multiply, 425, 426, 427);
  g->Binary(ynn_binary_add, 400, 427, 428);
}

// Scope: "Layer10 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(907, 429, {0,0,10,0}, {-1,-1,1,-1});
  g->Reshape(429, 430, {1,0,256});
  g->Binary(ynn_binary_add, 430, 3269, 431);
  g->Binary(ynn_binary_multiply, 431, 3003, 433);
  g->Quantize(428, 434, 0.14669467508792877, 0);
  g->Transpose(3062, 1970, {1,0});
  g->Binary(ynn_binary_multiply, 1967, 1969, 1965);
  g->Dot(434, 1970, YNN_INVALID_VALUE_ID, 1964, 1);
  g->DequantizeTensor(1964, YNN_INVALID_VALUE_ID, 1965, 1966);
  g->QuantizeTensor(1966, 2971, 1968, 435);
  g->Dequantize(435, 436, 0.038631901144981384, 0);
  g->Polynomial(436, 2666, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2666, 2667);
  g->Binary(ynn_binary_add, 2667, 2558, 2664);
  g->Binary(ynn_binary_multiply, 436, 2556, 2665);
  g->Binary(ynn_binary_multiply, 2665, 2664, 437);
  g->Binary(ynn_binary_multiply, 437, 433, 438);
  g->Quantize(438, 439, 0.05610237270593643, 0);
  g->Transpose(3063, 1977, {1,0});
  g->Binary(ynn_binary_multiply, 1974, 1976, 1972);
  g->Dot(439, 1977, YNN_INVALID_VALUE_ID, 1971, 1);
  g->DequantizeTensor(1971, YNN_INVALID_VALUE_ID, 1972, 1973);
  g->QuantizeTensor(1973, 2971, 1975, 440);
  g->Dequantize(440, 441, 0.041538726538419724, 0);
  g->Unary(ynn_unary_square, 441, 442);
  g->Reduce(ynn_reduce_sum, 442, 2669, {2}, true);
  g->ShapeProduct(442, 2668, {2});
  g->Binary(ynn_binary_divide, 2669, 2668, 444);
  g->Binary(ynn_binary_add, 444, 3004, 445);
  g->Binary(ynn_binary_pow, 445, 3006, 446);
  g->Binary(ynn_binary_multiply, 441, 446, 447);
  g->Convert(3066, 448);
  g->Binary(ynn_binary_multiply, 447, 448, 449);
  g->Binary(ynn_binary_add, 428, 449, 450);
  g->Convert(3058, 451);
  g->Binary(ynn_binary_multiply, 450, 451, 452);
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
  g->Quantize(460, 461, 0.11506716161966324, 0);
  g->Transpose(3086, 1984, {1,0});
  g->Binary(ynn_binary_multiply, 1981, 1983, 1979);
  g->Dot(461, 1984, YNN_INVALID_VALUE_ID, 1978, 1);
  g->DequantizeTensor(1978, YNN_INVALID_VALUE_ID, 1979, 1980);
  g->QuantizeTensor(1980, 2971, 1982, 462);
  g->Dequantize(462, 463, 0.12696851789951324, 0);
  g->Reshape(463, 464, {1,0,1,256});
  g->Transpose(464, 466, {0,2,1,3});
  g->Unary(ynn_unary_square, 466, 467);
  g->Reduce(ynn_reduce_sum, 467, 2673, {3}, true);
  g->ShapeProduct(467, 2672, {3});
  g->Binary(ynn_binary_divide, 2673, 2672, 468);
  g->Binary(ynn_binary_add, 468, 3004, 469);
  g->Binary(ynn_binary_pow, 469, 3006, 470);
  g->Binary(ynn_binary_multiply, 466, 470, 471);
  g->Convert(3085, 472);
  g->Binary(ynn_binary_multiply, 471, 472, 473);
  g->Slice(473, 474, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(473, 475, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 475, 477);
  g->Concat({477,474}, 478, 3);
  g->Binary(ynn_binary_multiply, 473, 1015, 479);
  g->Binary(ynn_binary_multiply, 478, 1118, 480);
  g->Binary(ynn_binary_add, 479, 480, 481);
  g->Transpose(3090, 1989, {1,0});
  g->Binary(ynn_binary_multiply, 1981, 1988, 1986);
  g->Dot(461, 1989, YNN_INVALID_VALUE_ID, 1985, 1);
  g->DequantizeTensor(1985, YNN_INVALID_VALUE_ID, 1986, 1987);
  g->QuantizeTensor(1987, 2971, 1982, 482);
  g->Dequantize(482, 483, 0.12696851789951324, 0);
  g->Reshape(483, 484, {1,0,1,256});
  g->Transpose(484, 485, {0,2,1,3});
  g->Unary(ynn_unary_square, 485, 487);
  g->Reduce(ynn_reduce_sum, 487, 2675, {3}, true);
  g->ShapeProduct(487, 2674, {3});
  g->Binary(ynn_binary_divide, 2675, 2674, 488);
  g->Binary(ynn_binary_add, 488, 3004, 489);
  g->Binary(ynn_binary_pow, 489, 3006, 490);
  g->Binary(ynn_binary_multiply, 485, 490, 491);
}

// Scope: "Layer11 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(481, 492, 0.005907459184527397, 0);
  g->Append(2975, 492, 3285, 2, s2, s1);
  g->View(3285, 3315, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(3315, 493, 0.005907459184527397, 0);
  g->Quantize(491, 494, 0.047244105488061905, 0);
  g->Append(2990, 494, 3300, 2, s2, s1);
  g->View(3300, 3329, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(3329, 496, 0.047244105488061905, 0);
}

// Scope: "Layer11 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(3089, 1995, {1,0});
  g->Binary(ynn_binary_multiply, 1981, 1994, 1991);
  g->Dot(461, 1995, YNN_INVALID_VALUE_ID, 1990, 1);
  g->DequantizeTensor(1990, YNN_INVALID_VALUE_ID, 1991, 1992);
  g->QuantizeTensor(1992, 2971, 1993, 497);
  g->Dequantize(497, 498, 0.2736220359802246, 0);
  g->SplitDim(498, 499, 2, {8,256});
  g->Transpose(499, 500, {0,2,1,3});
  g->Unary(ynn_unary_square, 500, 501);
  g->Reduce(ynn_reduce_sum, 501, 2677, {3}, true);
  g->ShapeProduct(501, 2676, {3});
  g->Binary(ynn_binary_divide, 2677, 2676, 502);
  g->Binary(ynn_binary_add, 502, 3004, 504);
  g->Binary(ynn_binary_pow, 504, 3006, 505);
  g->Binary(ynn_binary_multiply, 500, 505, 506);
  g->Convert(3088, 507);
  g->Binary(ynn_binary_multiply, 506, 507, 508);
  g->Slice(508, 509, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(508, 510, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 510, 511);
  g->Concat({511,509}, 512, 3);
  g->Binary(ynn_binary_multiply, 508, 1015, 513);
  g->Binary(ynn_binary_multiply, 512, 1118, 515);
  g->Binary(ynn_binary_add, 513, 515, 516);
}

// Scope: "Layer11 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(516, 493, 517, false, true);
  g->Mask(517, 3012, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 3012, 2681, {-1}, true);
  g->Binary(ynn_binary_subtract, 3012, 2681, 2678);
  g->Unary(ynn_unary_exp, 2678, 2679);
  g->Reduce(ynn_reduce_sum, 2679, 2682, {-1}, true);
  g->Binary(ynn_binary_divide, 2558, 2682, 2680);
  g->Binary(ynn_binary_multiply, 2679, 2680, 518);
  g->Matmul(518, 496, 519, false, false);
}

// Scope: "Layer11 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(519, 520, {0,2,1,3});
  g->FuseDims(520, 521, 2, 2);
  g->Quantize(521, 522, 0.026082687079906464, 0);
  g->Transpose(3087, 2002, {1,0});
  g->Binary(ynn_binary_multiply, 1999, 2001, 1997);
  g->Dot(522, 2002, YNN_INVALID_VALUE_ID, 1996, 1);
  g->DequantizeTensor(1996, YNN_INVALID_VALUE_ID, 1997, 1998);
  g->QuantizeTensor(1998, 2971, 2000, 523);
  g->Dequantize(523, 526, 0.028822369873523712, 0);
}

// Scope: "Layer11 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 452, 453);
  g->Reduce(ynn_reduce_sum, 453, 2671, {2}, true);
  g->ShapeProduct(453, 2670, {2});
  g->Binary(ynn_binary_divide, 2671, 2670, 455);
  g->Binary(ynn_binary_add, 455, 3004, 456);
  g->Binary(ynn_binary_pow, 456, 3006, 457);
  g->Binary(ynn_binary_multiply, 452, 457, 458);
  g->Convert(3074, 459);
  g->Binary(ynn_binary_multiply, 458, 459, 460);
  BuildLayer11AttentionKvProjection(ctx);
  BuildLayer11AttentionCacheUpdate(ctx);
  BuildLayer11AttentionQueryProjection(ctx);
  BuildLayer11AttentionSdpa(ctx);
  BuildLayer11AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 526, 527);
  g->Reduce(ynn_reduce_sum, 527, 2688, {2}, true);
  g->ShapeProduct(527, 2687, {2});
  g->Binary(ynn_binary_divide, 2688, 2687, 528);
  g->Binary(ynn_binary_add, 528, 3004, 529);
  g->Binary(ynn_binary_pow, 529, 3006, 530);
  g->Binary(ynn_binary_multiply, 526, 530, 531);
  g->Convert(3081, 532);
  g->Binary(ynn_binary_multiply, 531, 532, 533);
  g->Binary(ynn_binary_add, 452, 533, 534);
}

// Scope: "Layer11 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 534, 535);
  g->Reduce(ynn_reduce_sum, 535, 2690, {2}, true);
  g->ShapeProduct(535, 2689, {2});
  g->Binary(ynn_binary_divide, 2690, 2689, 537);
  g->Binary(ynn_binary_add, 537, 3004, 538);
  g->Binary(ynn_binary_pow, 538, 3006, 539);
  g->Binary(ynn_binary_multiply, 534, 539, 540);
  g->Convert(3084, 541);
  g->Binary(ynn_binary_multiply, 540, 541, 542);
  g->Quantize(542, 543, 0.015670500695705414, 0);
  g->Transpose(3078, 2009, {1,0});
  g->Binary(ynn_binary_multiply, 2006, 2008, 2004);
  g->Dot(543, 2009, YNN_INVALID_VALUE_ID, 2003, 1);
  g->DequantizeTensor(2003, YNN_INVALID_VALUE_ID, 2004, 2005);
  g->QuantizeTensor(2005, 2971, 2007, 544);
  g->Dequantize(544, 545, 0.015255915932357311, 0);
  g->Transpose(3077, 2014, {1,0});
  g->Binary(ynn_binary_multiply, 2006, 2013, 2011);
  g->Dot(543, 2014, YNN_INVALID_VALUE_ID, 2010, 1);
  g->DequantizeTensor(2010, YNN_INVALID_VALUE_ID, 2011, 2012);
  g->QuantizeTensor(2012, 2971, 2007, 547);
  g->Dequantize(547, 548, 0.015255915932357311, 0);
  g->Polynomial(548, 2693, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2693, 2694);
  g->Binary(ynn_binary_add, 2694, 2558, 2691);
  g->Binary(ynn_binary_multiply, 548, 2556, 2692);
  g->Binary(ynn_binary_multiply, 2692, 2691, 549);
  g->Binary(ynn_binary_multiply, 545, 549, 550);
  g->Quantize(550, 551, 0.011195876635611057, 0);
  g->Transpose(3076, 2021, {1,0});
  g->Binary(ynn_binary_multiply, 2018, 2020, 2016);
  g->Dot(551, 2021, YNN_INVALID_VALUE_ID, 2015, 1);
  g->DequantizeTensor(2015, YNN_INVALID_VALUE_ID, 2016, 2017);
  g->QuantizeTensor(2017, 2971, 2019, 552);
  g->Dequantize(552, 553, 0.004389102105051279, 0);
  g->Unary(ynn_unary_square, 553, 554);
  g->Reduce(ynn_reduce_sum, 554, 2696, {2}, true);
  g->ShapeProduct(554, 2695, {2});
  g->Binary(ynn_binary_divide, 2696, 2695, 555);
  g->Binary(ynn_binary_add, 555, 3004, 556);
  g->Binary(ynn_binary_pow, 556, 3006, 558);
  g->Binary(ynn_binary_multiply, 553, 558, 559);
  g->Convert(3082, 560);
  g->Binary(ynn_binary_multiply, 559, 560, 561);
  g->Binary(ynn_binary_add, 534, 561, 562);
}

// Scope: "Layer11 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(907, 563, {0,0,11,0}, {-1,-1,1,-1});
  g->Reshape(563, 564, {1,0,256});
  g->Binary(ynn_binary_add, 564, 3270, 565);
  g->Binary(ynn_binary_multiply, 565, 3003, 566);
  g->Quantize(562, 567, 0.1750430017709732, 0);
  g->Transpose(3079, 2028, {1,0});
  g->Binary(ynn_binary_multiply, 2025, 2027, 2023);
  g->Dot(567, 2028, YNN_INVALID_VALUE_ID, 2022, 1);
  g->DequantizeTensor(2022, YNN_INVALID_VALUE_ID, 2023, 2024);
  g->QuantizeTensor(2024, 2971, 2026, 569);
  g->Dequantize(569, 570, 0.07529528439044952, 0);
  g->Polynomial(570, 2699, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2699, 2700);
  g->Binary(ynn_binary_add, 2700, 2558, 2697);
  g->Binary(ynn_binary_multiply, 570, 2556, 2698);
  g->Binary(ynn_binary_multiply, 2698, 2697, 571);
  g->Binary(ynn_binary_multiply, 571, 566, 572);
  g->Quantize(572, 573, 0.15846458077430725, 0);
  g->Transpose(3080, 2035, {1,0});
  g->Binary(ynn_binary_multiply, 2032, 2034, 2030);
  g->Dot(573, 2035, YNN_INVALID_VALUE_ID, 2029, 1);
  g->DequantizeTensor(2029, YNN_INVALID_VALUE_ID, 2030, 2031);
  g->QuantizeTensor(2031, 2971, 2033, 574);
  g->Dequantize(574, 575, 0.1771666705608368, 0);
  g->Unary(ynn_unary_square, 575, 576);
  g->Reduce(ynn_reduce_sum, 576, 2702, {2}, true);
  g->ShapeProduct(576, 2701, {2});
  g->Binary(ynn_binary_divide, 2702, 2701, 577);
  g->Binary(ynn_binary_add, 577, 3004, 578);
  g->Binary(ynn_binary_pow, 578, 3006, 580);
  g->Binary(ynn_binary_multiply, 575, 580, 581);
  g->Convert(3083, 582);
  g->Binary(ynn_binary_multiply, 581, 582, 583);
  g->Binary(ynn_binary_add, 562, 583, 584);
  g->Convert(3075, 585);
  g->Binary(ynn_binary_multiply, 584, 585, 586);
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
  g->Quantize(594, 595, 0.08767248690128326, 0);
  g->Transpose(3103, 2042, {1,0});
  g->Binary(ynn_binary_multiply, 2039, 2041, 2037);
  g->Dot(595, 2042, YNN_INVALID_VALUE_ID, 2036, 1);
  g->DequantizeTensor(2036, YNN_INVALID_VALUE_ID, 2037, 2038);
  g->QuantizeTensor(2038, 2971, 2040, 596);
  g->Dequantize(596, 597, 0.08070866763591766, 0);
  g->Reshape(597, 598, {1,0,1,256});
  g->Transpose(598, 599, {0,2,1,3});
  g->Unary(ynn_unary_square, 599, 600);
  g->Reduce(ynn_reduce_sum, 600, 2706, {3}, true);
  g->ShapeProduct(600, 2705, {3});
  g->Binary(ynn_binary_divide, 2706, 2705, 602);
  g->Binary(ynn_binary_add, 602, 3004, 603);
  g->Binary(ynn_binary_pow, 603, 3006, 604);
  g->Binary(ynn_binary_multiply, 599, 604, 605);
  g->Convert(3102, 606);
  g->Binary(ynn_binary_multiply, 605, 606, 607);
  g->Slice(607, 608, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(607, 609, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 609, 610);
  g->Concat({610,608}, 611, 3);
  g->Binary(ynn_binary_multiply, 607, 1015, 613);
  g->Binary(ynn_binary_multiply, 611, 1118, 614);
  g->Binary(ynn_binary_add, 613, 614, 615);
  g->Transpose(3107, 2054, {1,0});
  g->Binary(ynn_binary_multiply, 2039, 2053, 2051);
  g->Dot(595, 2054, YNN_INVALID_VALUE_ID, 2050, 1);
  g->DequantizeTensor(2050, YNN_INVALID_VALUE_ID, 2051, 2052);
  g->QuantizeTensor(2052, 2971, 2040, 616);
  g->Dequantize(616, 617, 0.08070866763591766, 0);
  g->Reshape(617, 618, {1,0,1,256});
  g->Transpose(618, 619, {0,2,1,3});
  g->Unary(ynn_unary_square, 619, 620);
  g->Reduce(ynn_reduce_sum, 620, 2708, {3}, true);
  g->ShapeProduct(620, 2707, {3});
  g->Binary(ynn_binary_divide, 2708, 2707, 621);
  g->Binary(ynn_binary_add, 621, 3004, 623);
  g->Binary(ynn_binary_pow, 623, 3006, 624);
  g->Binary(ynn_binary_multiply, 619, 624, 625);
}

// Scope: "Layer12 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(615, 626, 0.005788442213088274, 0);
  g->Append(2976, 626, 3286, 2, s2, s1);
  g->View(3286, 3316, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(3316, 627, 0.005788442213088274, 0);
  g->Quantize(625, 628, 0.047244105488061905, 0);
  g->Append(2991, 628, 3301, 2, s2, s1);
  g->View(3301, 3330, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(3330, 631, 0.047244105488061905, 0);
}

// Scope: "Layer12 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(3106, 2060, {1,0});
  g->Binary(ynn_binary_multiply, 2039, 2059, 2056);
  g->Dot(595, 2060, YNN_INVALID_VALUE_ID, 2055, 1);
  g->DequantizeTensor(2055, YNN_INVALID_VALUE_ID, 2056, 2057);
  g->QuantizeTensor(2057, 2971, 2058, 632);
  g->Dequantize(632, 633, 0.12795276939868927, 0);
  g->SplitDim(633, 634, 2, {8,256});
  g->Transpose(634, 635, {0,2,1,3});
  g->Unary(ynn_unary_square, 635, 636);
  g->Reduce(ynn_reduce_sum, 636, 2710, {3}, true);
  g->ShapeProduct(636, 2709, {3});
  g->Binary(ynn_binary_divide, 2710, 2709, 637);
  g->Binary(ynn_binary_add, 637, 3004, 638);
  g->Binary(ynn_binary_pow, 638, 3006, 639);
  g->Binary(ynn_binary_multiply, 635, 639, 641);
  g->Convert(3105, 642);
  g->Binary(ynn_binary_multiply, 641, 642, 643);
  g->Slice(643, 644, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(643, 645, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 645, 646);
  g->Concat({646,644}, 647, 3);
  g->Binary(ynn_binary_multiply, 643, 1015, 648);
  g->Binary(ynn_binary_multiply, 647, 1118, 649);
  g->Binary(ynn_binary_add, 648, 649, 650);
}

// Scope: "Layer12 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(650, 627, 652, false, true);
  g->Mask(652, 3013, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 3013, 2716, {-1}, true);
  g->Binary(ynn_binary_subtract, 3013, 2716, 2713);
  g->Unary(ynn_unary_exp, 2713, 2714);
  g->Reduce(ynn_reduce_sum, 2714, 2717, {-1}, true);
  g->Binary(ynn_binary_divide, 2558, 2717, 2715);
  g->Binary(ynn_binary_multiply, 2714, 2715, 653);
  g->Matmul(653, 631, 654, false, false);
}

// Scope: "Layer12 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(654, 655, {0,2,1,3});
  g->FuseDims(655, 656, 2, 2);
  g->Quantize(656, 657, 0.028543315827846527, 0);
  g->Transpose(3104, 2067, {1,0});
  g->Binary(ynn_binary_multiply, 2064, 2066, 2062);
  g->Dot(657, 2067, YNN_INVALID_VALUE_ID, 2061, 1);
  g->DequantizeTensor(2061, YNN_INVALID_VALUE_ID, 2062, 2063);
  g->QuantizeTensor(2063, 2971, 2065, 658);
  g->Dequantize(658, 659, 0.021804405376315117, 0);
}

// Scope: "Layer12 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 586, 587);
  g->Reduce(ynn_reduce_sum, 587, 2704, {2}, true);
  g->ShapeProduct(587, 2703, {2});
  g->Binary(ynn_binary_divide, 2704, 2703, 588);
  g->Binary(ynn_binary_add, 588, 3004, 589);
  g->Binary(ynn_binary_pow, 589, 3006, 591);
  g->Binary(ynn_binary_multiply, 586, 591, 592);
  g->Convert(3091, 593);
  g->Binary(ynn_binary_multiply, 592, 593, 594);
  BuildLayer12AttentionKvProjection(ctx);
  BuildLayer12AttentionCacheUpdate(ctx);
  BuildLayer12AttentionQueryProjection(ctx);
  BuildLayer12AttentionSdpa(ctx);
  BuildLayer12AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 659, 660);
  g->Reduce(ynn_reduce_sum, 660, 2719, {2}, true);
  g->ShapeProduct(660, 2718, {2});
  g->Binary(ynn_binary_divide, 2719, 2718, 662);
  g->Binary(ynn_binary_add, 662, 3004, 663);
  g->Binary(ynn_binary_pow, 663, 3006, 664);
  g->Binary(ynn_binary_multiply, 659, 664, 665);
  g->Convert(3098, 666);
  g->Binary(ynn_binary_multiply, 665, 666, 667);
  g->Binary(ynn_binary_add, 586, 667, 668);
}

// Scope: "Layer12 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 668, 669);
  g->Reduce(ynn_reduce_sum, 669, 2721, {2}, true);
  g->ShapeProduct(669, 2720, {2});
  g->Binary(ynn_binary_divide, 2721, 2720, 670);
  g->Binary(ynn_binary_add, 670, 3004, 671);
  g->Binary(ynn_binary_pow, 671, 3006, 673);
  g->Binary(ynn_binary_multiply, 668, 673, 674);
  g->Convert(3101, 675);
  g->Binary(ynn_binary_multiply, 674, 675, 676);
  g->Quantize(676, 677, 0.013748278841376305, 0);
  g->Transpose(3095, 2074, {1,0});
  g->Binary(ynn_binary_multiply, 2071, 2073, 2069);
  g->Dot(677, 2074, YNN_INVALID_VALUE_ID, 2068, 1);
  g->DequantizeTensor(2068, YNN_INVALID_VALUE_ID, 2069, 2070);
  g->QuantizeTensor(2070, 2971, 2072, 678);
  g->Dequantize(678, 679, 0.012795286253094673, 0);
  g->Transpose(3094, 2079, {1,0});
  g->Binary(ynn_binary_multiply, 2071, 2078, 2076);
  g->Dot(677, 2079, YNN_INVALID_VALUE_ID, 2075, 1);
  g->DequantizeTensor(2075, YNN_INVALID_VALUE_ID, 2076, 2077);
  g->QuantizeTensor(2077, 2971, 2072, 680);
  g->Dequantize(680, 681, 0.012795286253094673, 0);
  g->Polynomial(681, 2724, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2724, 2725);
  g->Binary(ynn_binary_add, 2725, 2558, 2722);
  g->Binary(ynn_binary_multiply, 681, 2556, 2723);
  g->Binary(ynn_binary_multiply, 2723, 2722, 683);
  g->Binary(ynn_binary_multiply, 679, 683, 684);
  g->Quantize(684, 685, 0.00768947834149003, 0);
  g->Transpose(3093, 2086, {1,0});
  g->Binary(ynn_binary_multiply, 2083, 2085, 2081);
  g->Dot(685, 2086, YNN_INVALID_VALUE_ID, 2080, 1);
  g->DequantizeTensor(2080, YNN_INVALID_VALUE_ID, 2081, 2082);
  g->QuantizeTensor(2082, 2971, 2084, 686);
  g->Dequantize(686, 687, 0.005636297166347504, 0);
  g->Unary(ynn_unary_square, 687, 688);
  g->Reduce(ynn_reduce_sum, 688, 2727, {2}, true);
  g->ShapeProduct(688, 2726, {2});
  g->Binary(ynn_binary_divide, 2727, 2726, 689);
  g->Binary(ynn_binary_add, 689, 3004, 690);
  g->Binary(ynn_binary_pow, 690, 3006, 691);
  g->Binary(ynn_binary_multiply, 687, 691, 692);
  g->Convert(3099, 694);
  g->Binary(ynn_binary_multiply, 692, 694, 695);
  g->Binary(ynn_binary_add, 668, 695, 696);
}

// Scope: "Layer12 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer12PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(907, 697, {0,0,12,0}, {-1,-1,1,-1});
  g->Reshape(697, 698, {1,0,256});
  g->Binary(ynn_binary_add, 698, 3271, 699);
  g->Binary(ynn_binary_multiply, 699, 3003, 700);
  g->Quantize(696, 701, 0.19133253395557404, 0);
  g->Transpose(3096, 2092, {1,0});
  g->Binary(ynn_binary_multiply, 2090, 2091, 2088);
  g->Dot(701, 2092, YNN_INVALID_VALUE_ID, 2087, 1);
  g->DequantizeTensor(2087, YNN_INVALID_VALUE_ID, 2088, 2089);
  g->QuantizeTensor(2089, 2971, 2026, 702);
  g->Dequantize(702, 703, 0.07529528439044952, 0);
  g->Polynomial(703, 2730, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2730, 2731);
  g->Binary(ynn_binary_add, 2731, 2558, 2728);
  g->Binary(ynn_binary_multiply, 703, 2556, 2729);
  g->Binary(ynn_binary_multiply, 2729, 2728, 705);
  g->Binary(ynn_binary_multiply, 705, 700, 706);
  g->Quantize(706, 707, 0.12450788170099258, 0);
  g->Transpose(3097, 2099, {1,0});
  g->Binary(ynn_binary_multiply, 2096, 2098, 2094);
  g->Dot(707, 2099, YNN_INVALID_VALUE_ID, 2093, 1);
  g->DequantizeTensor(2093, YNN_INVALID_VALUE_ID, 2094, 2095);
  g->QuantizeTensor(2095, 2971, 2097, 708);
  g->Dequantize(708, 709, 0.12528184056282043, 0);
  g->Unary(ynn_unary_square, 709, 710);
  g->Reduce(ynn_reduce_sum, 710, 2733, {2}, true);
  g->ShapeProduct(710, 2732, {2});
  g->Binary(ynn_binary_divide, 2733, 2732, 711);
  g->Binary(ynn_binary_add, 711, 3004, 712);
  g->Binary(ynn_binary_pow, 712, 3006, 713);
  g->Binary(ynn_binary_multiply, 709, 713, 714);
  g->Convert(3100, 716);
  g->Binary(ynn_binary_multiply, 714, 716, 717);
  g->Binary(ynn_binary_add, 696, 717, 718);
  g->Convert(3092, 719);
  g->Binary(ynn_binary_multiply, 718, 719, 720);
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
  g->Quantize(728, 729, 0.02862965501844883, 0);
  g->Transpose(3120, 2106, {1,0});
  g->Binary(ynn_binary_multiply, 2103, 2105, 2101);
  g->Dot(729, 2106, YNN_INVALID_VALUE_ID, 2100, 1);
  g->DequantizeTensor(2100, YNN_INVALID_VALUE_ID, 2101, 2102);
  g->QuantizeTensor(2102, 2971, 2104, 730);
  g->Dequantize(730, 731, 0.035925209522247314, 0);
  g->Reshape(731, 732, {1,0,1,256});
  g->Transpose(732, 733, {0,2,1,3});
  g->Unary(ynn_unary_square, 733, 734);
  g->Reduce(ynn_reduce_sum, 734, 2737, {3}, true);
  g->ShapeProduct(734, 2736, {3});
  g->Binary(ynn_binary_divide, 2737, 2736, 735);
  g->Binary(ynn_binary_add, 735, 3004, 736);
  g->Binary(ynn_binary_pow, 736, 3006, 739);
  g->Binary(ynn_binary_multiply, 733, 739, 740);
  g->Convert(3119, 741);
  g->Binary(ynn_binary_multiply, 740, 741, 742);
  g->Slice(742, 743, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(742, 744, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 744, 745);
  g->Concat({745,743}, 746, 3);
  g->Binary(ynn_binary_multiply, 742, 1015, 747);
  g->Binary(ynn_binary_multiply, 746, 1118, 748);
  g->Binary(ynn_binary_add, 747, 748, 750);
  g->Transpose(3124, 2111, {1,0});
  g->Binary(ynn_binary_multiply, 2103, 2110, 2108);
  g->Dot(729, 2111, YNN_INVALID_VALUE_ID, 2107, 1);
  g->DequantizeTensor(2107, YNN_INVALID_VALUE_ID, 2108, 2109);
  g->QuantizeTensor(2109, 2971, 2104, 751);
  g->Dequantize(751, 752, 0.035925209522247314, 0);
  g->Reshape(752, 753, {1,0,1,256});
  g->Transpose(753, 754, {0,2,1,3});
  g->Unary(ynn_unary_square, 754, 755);
  g->Reduce(ynn_reduce_sum, 755, 2739, {3}, true);
  g->ShapeProduct(755, 2738, {3});
  g->Binary(ynn_binary_divide, 2739, 2738, 756);
  g->Binary(ynn_binary_add, 756, 3004, 757);
  g->Binary(ynn_binary_pow, 757, 3006, 758);
  g->Binary(ynn_binary_multiply, 754, 758, 760);
}

// Scope: "Layer13 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(750, 761, 0.0059552486054599285, 0);
  g->Append(2977, 761, 3287, 2, s2, s1);
  g->View(3287, 3317, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(3317, 762, 0.0059552486054599285, 0);
  g->Quantize(760, 763, 0.047244105488061905, 0);
  g->Append(2992, 763, 3302, 2, s2, s1);
  g->View(3302, 3331, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(3331, 764, 0.047244105488061905, 0);
}

// Scope: "Layer13 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(3123, 2116, {1,0});
  g->Binary(ynn_binary_multiply, 2103, 2115, 2113);
  g->Dot(729, 2116, YNN_INVALID_VALUE_ID, 2112, 1);
  g->DequantizeTensor(2112, YNN_INVALID_VALUE_ID, 2113, 2114);
  g->QuantizeTensor(2114, 2971, 1934, 766);
  g->Dequantize(766, 767, 0.03764764964580536, 0);
  g->SplitDim(767, 768, 2, {8,256});
  g->Transpose(768, 769, {0,2,1,3});
  g->Unary(ynn_unary_square, 769, 770);
  g->Reduce(ynn_reduce_sum, 770, 2741, {3}, true);
  g->ShapeProduct(770, 2740, {3});
  g->Binary(ynn_binary_divide, 2741, 2740, 771);
  g->Binary(ynn_binary_add, 771, 3004, 772);
  g->Binary(ynn_binary_pow, 772, 3006, 773);
  g->Binary(ynn_binary_multiply, 769, 773, 774);
  g->Convert(3122, 775);
  g->Binary(ynn_binary_multiply, 774, 775, 777);
  g->Slice(777, 778, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(777, 779, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 779, 780);
  g->Concat({780,778}, 781, 3);
  g->Binary(ynn_binary_multiply, 777, 1015, 782);
  g->Binary(ynn_binary_multiply, 781, 1118, 783);
  g->Binary(ynn_binary_add, 782, 783, 784);
}

// Scope: "Layer13 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(784, 762, 785, false, true);
  g->Mask(785, 3014, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 3014, 2745, {-1}, true);
  g->Binary(ynn_binary_subtract, 3014, 2745, 2742);
  g->Unary(ynn_unary_exp, 2742, 2743);
  g->Reduce(ynn_reduce_sum, 2743, 2746, {-1}, true);
  g->Binary(ynn_binary_divide, 2558, 2746, 2744);
  g->Binary(ynn_binary_multiply, 2743, 2744, 786);
  g->Matmul(786, 764, 787, false, false);
}

// Scope: "Layer13 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(787, 788, {0,2,1,3});
  g->FuseDims(788, 789, 2, 2);
  g->Quantize(789, 790, 0.026205718517303467, 0);
  g->Transpose(3121, 2123, {1,0});
  g->Binary(ynn_binary_multiply, 2120, 2122, 2118);
  g->Dot(790, 2123, YNN_INVALID_VALUE_ID, 2117, 1);
  g->DequantizeTensor(2117, YNN_INVALID_VALUE_ID, 2118, 2119);
  g->QuantizeTensor(2119, 2971, 2121, 791);
  g->Dequantize(791, 792, 0.03592992201447487, 0);
}

// Scope: "Layer13 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 720, 721);
  g->Reduce(ynn_reduce_sum, 721, 2735, {2}, true);
  g->ShapeProduct(721, 2734, {2});
  g->Binary(ynn_binary_divide, 2735, 2734, 722);
  g->Binary(ynn_binary_add, 722, 3004, 723);
  g->Binary(ynn_binary_pow, 723, 3006, 724);
  g->Binary(ynn_binary_multiply, 720, 724, 725);
  g->Convert(3108, 727);
  g->Binary(ynn_binary_multiply, 725, 727, 728);
  BuildLayer13AttentionKvProjection(ctx);
  BuildLayer13AttentionCacheUpdate(ctx);
  BuildLayer13AttentionQueryProjection(ctx);
  BuildLayer13AttentionSdpa(ctx);
  BuildLayer13AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 792, 793);
  g->Reduce(ynn_reduce_sum, 793, 2748, {2}, true);
  g->ShapeProduct(793, 2747, {2});
  g->Binary(ynn_binary_divide, 2748, 2747, 794);
  g->Binary(ynn_binary_add, 794, 3004, 795);
  g->Binary(ynn_binary_pow, 795, 3006, 797);
  g->Binary(ynn_binary_multiply, 792, 797, 798);
  g->Convert(3115, 799);
  g->Binary(ynn_binary_multiply, 798, 799, 800);
  g->Binary(ynn_binary_add, 720, 800, 801);
}

// Scope: "Layer13 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 801, 802);
  g->Reduce(ynn_reduce_sum, 802, 2750, {2}, true);
  g->ShapeProduct(802, 2749, {2});
  g->Binary(ynn_binary_divide, 2750, 2749, 803);
  g->Binary(ynn_binary_add, 803, 3004, 804);
  g->Binary(ynn_binary_pow, 804, 3006, 805);
  g->Binary(ynn_binary_multiply, 801, 805, 806);
  g->Convert(3118, 808);
  g->Binary(ynn_binary_multiply, 806, 808, 809);
  g->Quantize(809, 810, 0.0083004767075181, 0);
  g->Transpose(3112, 2135, {1,0});
  g->Binary(ynn_binary_multiply, 2132, 2134, 2130);
  g->Dot(810, 2135, YNN_INVALID_VALUE_ID, 2129, 1);
  g->DequantizeTensor(2129, YNN_INVALID_VALUE_ID, 2130, 2131);
  g->QuantizeTensor(2131, 2971, 2133, 811);
  g->Dequantize(811, 812, 0.011934065259993076, 0);
  g->Transpose(3111, 2140, {1,0});
  g->Binary(ynn_binary_multiply, 2132, 2139, 2137);
  g->Dot(810, 2140, YNN_INVALID_VALUE_ID, 2136, 1);
  g->DequantizeTensor(2136, YNN_INVALID_VALUE_ID, 2137, 2138);
  g->QuantizeTensor(2138, 2971, 2133, 813);
  g->Dequantize(813, 814, 0.011934065259993076, 0);
  g->Polynomial(814, 2753, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2753, 2754);
  g->Binary(ynn_binary_add, 2754, 2558, 2751);
  g->Binary(ynn_binary_multiply, 814, 2556, 2752);
  g->Binary(ynn_binary_multiply, 2752, 2751, 815);
  g->Binary(ynn_binary_multiply, 812, 815, 816);
  g->Quantize(816, 818, 0.0015532826073467731, 0);
  g->Transpose(3110, 2147, {1,0});
  g->Binary(ynn_binary_multiply, 2144, 2146, 2142);
  g->Dot(818, 2147, YNN_INVALID_VALUE_ID, 2141, 1);
  g->DequantizeTensor(2141, YNN_INVALID_VALUE_ID, 2142, 2143);
  g->QuantizeTensor(2143, 2971, 2145, 819);
  g->Dequantize(819, 820, 0.002153691602870822, 0);
  g->Unary(ynn_unary_square, 820, 821);
  g->Reduce(ynn_reduce_sum, 821, 2756, {2}, true);
  g->ShapeProduct(821, 2755, {2});
  g->Binary(ynn_binary_divide, 2756, 2755, 822);
  g->Binary(ynn_binary_add, 822, 3004, 823);
  g->Binary(ynn_binary_pow, 823, 3006, 824);
  g->Binary(ynn_binary_multiply, 820, 824, 825);
  g->Convert(3116, 826);
  g->Binary(ynn_binary_multiply, 825, 826, 827);
  g->Binary(ynn_binary_add, 801, 827, 829);
}

// Scope: "Layer13 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer13PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(907, 830, {0,0,13,0}, {-1,-1,1,-1});
  g->Reshape(830, 831, {1,0,256});
  g->Binary(ynn_binary_add, 831, 3272, 832);
  g->Binary(ynn_binary_multiply, 832, 3003, 833);
  g->Quantize(829, 834, 0.5171695351600647, 0);
  g->Transpose(3113, 2154, {1,0});
  g->Binary(ynn_binary_multiply, 2151, 2153, 2149);
  g->Dot(834, 2154, YNN_INVALID_VALUE_ID, 2148, 1);
  g->DequantizeTensor(2148, YNN_INVALID_VALUE_ID, 2149, 2150);
  g->QuantizeTensor(2150, 2971, 2152, 835);
  g->Dequantize(835, 836, 0.13385827839374542, 0);
  g->Polynomial(836, 2759, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2759, 2760);
  g->Binary(ynn_binary_add, 2760, 2558, 2757);
  g->Binary(ynn_binary_multiply, 836, 2556, 2758);
  g->Binary(ynn_binary_multiply, 2758, 2757, 837);
  g->Binary(ynn_binary_multiply, 837, 833, 838);
  g->Quantize(838, 841, 0.4094488322734833, 0);
  g->Transpose(3114, 2161, {1,0});
  g->Binary(ynn_binary_multiply, 2158, 2160, 2156);
  g->Dot(841, 2161, YNN_INVALID_VALUE_ID, 2155, 1);
  g->DequantizeTensor(2155, YNN_INVALID_VALUE_ID, 2156, 2157);
  g->QuantizeTensor(2157, 2971, 2159, 842);
  g->Dequantize(842, 843, 0.25065305829048157, 0);
  g->Unary(ynn_unary_square, 843, 844);
  g->Reduce(ynn_reduce_sum, 844, 2762, {2}, true);
  g->ShapeProduct(844, 2761, {2});
  g->Binary(ynn_binary_divide, 2762, 2761, 845);
  g->Binary(ynn_binary_add, 845, 3004, 846);
  g->Binary(ynn_binary_pow, 846, 3006, 847);
  g->Binary(ynn_binary_multiply, 843, 847, 848);
  g->Convert(3117, 849);
  g->Binary(ynn_binary_multiply, 848, 849, 850);
  g->Binary(ynn_binary_add, 829, 850, 852);
  g->Convert(3109, 853);
  g->Binary(ynn_binary_multiply, 852, 853, 854);
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
  g->Quantize(861, 863, 0.20956376194953918, 0);
  g->Transpose(3127, 2168, {1,0});
  g->Binary(ynn_binary_multiply, 2165, 2167, 2163);
  g->Dot(863, 2168, YNN_INVALID_VALUE_ID, 2162, 1);
  g->DequantizeTensor(2162, YNN_INVALID_VALUE_ID, 2163, 2164);
  g->QuantizeTensor(2164, 2971, 2166, 864);
  g->Dequantize(864, 865, 0.21751970052719116, 0);
  g->Reshape(865, 866, {1,0,1,512});
  g->Transpose(866, 867, {0,2,1,3});
  g->Unary(ynn_unary_square, 867, 868);
  g->Reduce(ynn_reduce_sum, 868, 2768, {3}, true);
  g->ShapeProduct(868, 2767, {3});
  g->Binary(ynn_binary_divide, 2768, 2767, 869);
  g->Binary(ynn_binary_add, 869, 3004, 870);
  g->Binary(ynn_binary_pow, 870, 3006, 871);
  g->Binary(ynn_binary_multiply, 867, 871, 872);
  g->Convert(3126, 874);
  g->Binary(ynn_binary_multiply, 872, 874, 875);
  g->Slice(875, 876, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(875, 877, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 877, 878);
  g->Concat({878,876}, 879, 3);
  g->Binary(ynn_binary_multiply, 875, 1532, 880);
  g->Binary(ynn_binary_multiply, 879, 1634, 881);
  g->Binary(ynn_binary_add, 880, 881, 882);
  g->Transpose(3128, 2173, {1,0});
  g->Binary(ynn_binary_multiply, 2165, 2172, 2170);
  g->Dot(863, 2173, YNN_INVALID_VALUE_ID, 2169, 1);
  g->DequantizeTensor(2169, YNN_INVALID_VALUE_ID, 2170, 2171);
  g->QuantizeTensor(2171, 2971, 2166, 884);
  g->Dequantize(884, 885, 0.21751970052719116, 0);
  g->Reshape(885, 886, {1,0,1,512});
  g->Transpose(886, 887, {0,2,1,3});
  g->Unary(ynn_unary_square, 887, 888);
  g->Reduce(ynn_reduce_sum, 888, 2770, {3}, true);
  g->ShapeProduct(888, 2769, {3});
  g->Binary(ynn_binary_divide, 2770, 2769, 889);
  g->Binary(ynn_binary_add, 889, 3004, 890);
  g->Binary(ynn_binary_pow, 890, 3006, 891);
  g->Binary(ynn_binary_multiply, 887, 891, 892);
}

// Scope: "Layer14 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(882, 893, 0.001091228099539876, 0);
  g->Append(2978, 893, 3288, 2, s2, s1);
  g->Quantize(892, 895, 0.01785714365541935, 0);
  g->Append(2993, 895, 3303, 2, s2, s1);
}

// Scope: "Layer14 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 854, 855);
  g->Reduce(ynn_reduce_sum, 855, 2766, {2}, true);
  g->ShapeProduct(855, 2765, {2});
  g->Binary(ynn_binary_divide, 2766, 2765, 856);
  g->Binary(ynn_binary_add, 856, 3004, 857);
  g->Binary(ynn_binary_pow, 857, 3006, 858);
  g->Binary(ynn_binary_multiply, 854, 858, 859);
  g->Convert(3125, 860);
  g->Binary(ynn_binary_multiply, 859, 860, 861);
  BuildLayer14AttentionKvProjection(ctx);
  BuildLayer14AttentionCacheUpdate(ctx);
}

// Scope: "Layer14"
LAB_YNN_BUILDER_NOINLINE void BuildLayer14(Context& ctx) {
  BuildLayer14Attention(ctx);
}

}  // namespace BuildGemma4PrefillSource
