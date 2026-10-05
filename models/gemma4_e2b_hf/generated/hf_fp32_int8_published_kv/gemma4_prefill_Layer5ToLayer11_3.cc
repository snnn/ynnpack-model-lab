// Generated YNNPACK builder; do not edit.
#include "gemma4_prefill_builder.h"

namespace BuildGemma4PrefillSource {

// Scope: "Layer5 / Attention / KvProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5AttentionKvProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Binary(ynn_binary_divide, 128, 3408, 129);
  g->Unary(ynn_unary_round, 129, 130);
  g->Binary(ynn_binary_max, 130, 3328, 132);
  g->Binary(ynn_binary_min, 132, 3384, 133);
  g->Binary(ynn_binary_multiply, 133, 3408, 134);
  g->Convert(3749, 135);
  g->Binary(ynn_binary_multiply, 135, 3750, 136);
  g->Matmul(134, 136, 137, false, true);
  g->Binary(ynn_binary_divide, 137, 3371, 138);
  g->Unary(ynn_unary_round, 138, 139);
  g->Binary(ynn_binary_max, 139, 3328, 140);
  g->Binary(ynn_binary_min, 140, 3384, 141);
  g->Binary(ynn_binary_multiply, 141, 3371, 143);
  g->Reshape(143, 144, {1,0,1,256});
  g->Transpose(144, 145, {0,2,1,3});
  g->Unary(ynn_unary_square, 145, 146);
  g->Reduce(ynn_reduce_sum, 146, 2869, {3}, true);
  g->ShapeProduct(146, 2868, {3});
  g->Binary(ynn_binary_divide, 2869, 2868, 147);
  g->Binary(ynn_binary_add, 147, 3400, 148);
  g->Binary(ynn_binary_pow, 148, 3424, 149);
  g->Binary(ynn_binary_multiply, 145, 149, 150);
  g->Convert(3748, 151);
  g->Binary(ynn_binary_multiply, 150, 151, 152);
  g->Slice(152, 154, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(152, 155, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 155, 156);
  g->Concat({156,154}, 157, 3);
  g->Binary(ynn_binary_multiply, 152, 2025, 158);
  g->Binary(ynn_binary_multiply, 157, 2249, 159);
  g->Binary(ynn_binary_add, 158, 159, 160);
  g->Convert(3756, 161);
  g->Binary(ynn_binary_multiply, 161, 3757, 162);
  g->Matmul(134, 162, 163, false, true);
  g->Binary(ynn_binary_divide, 163, 3371, 164);
  g->Unary(ynn_unary_round, 164, 165);
  g->Binary(ynn_binary_max, 165, 3328, 166);
  g->Binary(ynn_binary_min, 166, 3384, 167);
  g->Binary(ynn_binary_multiply, 167, 3371, 168);
  g->Reshape(168, 170, {1,0,1,256});
  g->Transpose(170, 171, {0,2,1,3});
  g->Unary(ynn_unary_square, 171, 172);
  g->Reduce(ynn_reduce_sum, 172, 2876, {3}, true);
  g->ShapeProduct(172, 2875, {3});
  g->Binary(ynn_binary_divide, 2876, 2875, 173);
  g->Binary(ynn_binary_add, 173, 3400, 174);
  g->Binary(ynn_binary_pow, 174, 3424, 175);
  g->Binary(ynn_binary_multiply, 171, 175, 176);
}

// Scope: "Layer5 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(160, 177, 0.006011798977851868, 0);
  g->Append(3272, 177, 3889, 2, s2, s1);
  g->View(3889, 3918, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(3918, 179, 0.006011798977851868, 0);
  g->Quantize(176, 180, 0.047244105488061905, 0);
  g->Append(3287, 180, 3904, 2, s2, s1);
  g->View(3904, 3932, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(3932, 181, 0.047244105488061905, 0);
}

// Scope: "Layer5 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Convert(3754, 183);
  g->Binary(ynn_binary_multiply, 183, 3755, 184);
  g->Matmul(134, 184, 185, false, true);
  g->Binary(ynn_binary_divide, 185, 3438, 186);
  g->Unary(ynn_unary_round, 186, 187);
  g->Binary(ynn_binary_max, 187, 3328, 188);
  g->Binary(ynn_binary_min, 188, 3384, 189);
  g->Binary(ynn_binary_multiply, 189, 3438, 190);
  g->SplitDim(190, 191, 2, {8,256});
  g->Transpose(191, 192, {0,2,1,3});
  g->Unary(ynn_unary_square, 192, 194);
  g->Reduce(ynn_reduce_sum, 194, 2878, {3}, true);
  g->ShapeProduct(194, 2877, {3});
  g->Binary(ynn_binary_divide, 2878, 2877, 195);
  g->Binary(ynn_binary_add, 195, 3400, 196);
  g->Binary(ynn_binary_pow, 196, 3424, 197);
  g->Binary(ynn_binary_multiply, 192, 197, 198);
  g->Convert(3753, 199);
  g->Binary(ynn_binary_multiply, 198, 199, 200);
  g->Slice(200, 201, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(200, 202, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 202, 203);
  g->Concat({203,201}, 206, 3);
  g->Binary(ynn_binary_multiply, 200, 2025, 207);
  g->Binary(ynn_binary_multiply, 206, 2249, 208);
  g->Binary(ynn_binary_add, 207, 208, 209);
}

// Scope: "Layer5 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(209, 179, 210, false, true);
  g->Mask(210, 3487, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 3487, 2882, {-1}, true);
  g->Binary(ynn_binary_subtract, 3487, 2882, 2879);
  g->Unary(ynn_unary_exp, 2879, 2880);
  g->Reduce(ynn_reduce_sum, 2880, 2883, {-1}, true);
  g->Binary(ynn_binary_divide, 2855, 2883, 2881);
  g->Binary(ynn_binary_multiply, 2880, 2881, 211);
  g->Matmul(211, 181, 212, false, false);
}

// Scope: "Layer5 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(212, 213, {0,2,1,3});
  g->FuseDims(213, 214, 2, 2);
  g->Binary(ynn_binary_divide, 214, 3338, 216);
  g->Unary(ynn_unary_round, 216, 217);
  g->Binary(ynn_binary_max, 217, 3328, 218);
  g->Binary(ynn_binary_min, 218, 3384, 219);
  g->Binary(ynn_binary_multiply, 219, 3338, 220);
  g->Convert(3751, 221);
  g->Binary(ynn_binary_multiply, 221, 3752, 222);
  g->Matmul(220, 222, 223, false, true);
  g->Binary(ynn_binary_divide, 223, 3308, 224);
  g->Unary(ynn_unary_round, 224, 225);
  g->Binary(ynn_binary_max, 225, 3328, 227);
  g->Binary(ynn_binary_min, 227, 3384, 228);
  g->Binary(ynn_binary_multiply, 228, 3308, 229);
}

// Scope: "Layer5 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 121, 122);
  g->Reduce(ynn_reduce_sum, 122, 2867, {2}, true);
  g->ShapeProduct(122, 2866, {2});
  g->Binary(ynn_binary_divide, 2867, 2866, 123);
  g->Binary(ynn_binary_add, 123, 3400, 124);
  g->Binary(ynn_binary_pow, 124, 3424, 125);
  g->Binary(ynn_binary_multiply, 121, 125, 126);
  g->Convert(3732, 127);
  g->Binary(ynn_binary_multiply, 126, 127, 128);
  BuildLayer5AttentionKvProjection(ctx);
  BuildLayer5AttentionCacheUpdate(ctx);
  BuildLayer5AttentionQueryProjection(ctx);
  BuildLayer5AttentionSdpa(ctx);
  BuildLayer5AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 229, 230);
  g->Reduce(ynn_reduce_sum, 230, 2885, {2}, true);
  g->ShapeProduct(230, 2884, {2});
  g->Binary(ynn_binary_divide, 2885, 2884, 231);
  g->Binary(ynn_binary_add, 231, 3400, 232);
  g->Binary(ynn_binary_pow, 232, 3424, 233);
  g->Binary(ynn_binary_multiply, 229, 233, 234);
  g->Convert(3744, 235);
  g->Binary(ynn_binary_multiply, 234, 235, 236);
  g->Binary(ynn_binary_add, 121, 236, 238);
}

// Scope: "Layer5 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 238, 239);
  g->Reduce(ynn_reduce_sum, 239, 2887, {2}, true);
  g->ShapeProduct(239, 2886, {2});
  g->Binary(ynn_binary_divide, 2887, 2886, 240);
  g->Binary(ynn_binary_add, 240, 3400, 241);
  g->Binary(ynn_binary_pow, 241, 3424, 242);
  g->Binary(ynn_binary_multiply, 238, 242, 243);
  g->Convert(3747, 244);
  g->Binary(ynn_binary_multiply, 243, 244, 245);
  g->Binary(ynn_binary_divide, 245, 3353, 246);
  g->Unary(ynn_unary_round, 246, 247);
  g->Binary(ynn_binary_max, 247, 3328, 249);
  g->Binary(ynn_binary_min, 249, 3384, 250);
  g->Binary(ynn_binary_multiply, 250, 3353, 251);
  g->Convert(3738, 252);
  g->Binary(ynn_binary_multiply, 252, 3739, 253);
  g->Matmul(251, 253, 254, false, true);
  g->Binary(ynn_binary_divide, 254, 3327, 255);
  g->Unary(ynn_unary_round, 255, 256);
  g->Binary(ynn_binary_max, 256, 3328, 257);
  g->Binary(ynn_binary_min, 257, 3384, 258);
  g->Binary(ynn_binary_multiply, 258, 3327, 260);
  g->Convert(3736, 261);
  g->Binary(ynn_binary_multiply, 261, 3737, 262);
  g->Matmul(251, 262, 263, false, true);
  g->Binary(ynn_binary_divide, 263, 3327, 264);
  g->Unary(ynn_unary_round, 264, 266);
  g->Binary(ynn_binary_max, 266, 3328, 267);
  g->Binary(ynn_binary_min, 267, 3384, 268);
  g->Binary(ynn_binary_multiply, 268, 3327, 269);
  g->Polynomial(269, 2890, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2890, 2891);
  g->Binary(ynn_binary_add, 2891, 2855, 2888);
  g->Binary(ynn_binary_multiply, 269, 2853, 2889);
  g->Binary(ynn_binary_multiply, 2889, 2888, 270);
  g->Binary(ynn_binary_multiply, 260, 270, 271);
  g->Binary(ynn_binary_divide, 271, 3381, 272);
  g->Unary(ynn_unary_round, 272, 273);
  g->Binary(ynn_binary_max, 273, 3328, 274);
  g->Binary(ynn_binary_min, 274, 3384, 275);
  g->Binary(ynn_binary_multiply, 275, 3381, 277);
  g->Convert(3734, 278);
  g->Binary(ynn_binary_multiply, 278, 3735, 279);
  g->Matmul(277, 279, 280, false, true);
  g->Binary(ynn_binary_divide, 280, 3355, 281);
  g->Unary(ynn_unary_round, 281, 282);
  g->Binary(ynn_binary_max, 282, 3328, 283);
  g->Binary(ynn_binary_min, 283, 3384, 284);
  g->Binary(ynn_binary_multiply, 284, 3355, 285);
  g->Unary(ynn_unary_square, 285, 286);
  g->Reduce(ynn_reduce_sum, 286, 2893, {2}, true);
  g->ShapeProduct(286, 2892, {2});
  g->Binary(ynn_binary_divide, 2893, 2892, 288);
  g->Binary(ynn_binary_add, 288, 3400, 289);
  g->Binary(ynn_binary_pow, 289, 3424, 290);
  g->Binary(ynn_binary_multiply, 285, 290, 291);
  g->Convert(3745, 292);
  g->Binary(ynn_binary_multiply, 291, 292, 293);
  g->Binary(ynn_binary_add, 238, 293, 294);
}

// Scope: "Layer5 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer5PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1022, 295, {0,0,5,0}, {-1,-1,1,-1});
  g->Reshape(295, 296, {1,0,256});
  g->Binary(ynn_binary_add, 296, 3873, 297);
  g->Binary(ynn_binary_multiply, 297, 3296, 299);
  g->Binary(ynn_binary_divide, 294, 3394, 300);
  g->Unary(ynn_unary_round, 300, 301);
  g->Binary(ynn_binary_max, 301, 3328, 302);
  g->Binary(ynn_binary_min, 302, 3384, 303);
  g->Binary(ynn_binary_multiply, 303, 3394, 304);
  g->Convert(3740, 305);
  g->Binary(ynn_binary_multiply, 305, 3741, 306);
  g->Matmul(304, 306, 307, false, true);
  g->Binary(ynn_binary_divide, 307, 3413, 308);
  g->Unary(ynn_unary_round, 308, 311);
  g->Binary(ynn_binary_max, 311, 3328, 312);
  g->Binary(ynn_binary_min, 312, 3384, 313);
  g->Binary(ynn_binary_multiply, 313, 3413, 314);
  g->Polynomial(314, 2896, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2896, 2897);
  g->Binary(ynn_binary_add, 2897, 2855, 2894);
  g->Binary(ynn_binary_multiply, 314, 2853, 2895);
  g->Binary(ynn_binary_multiply, 2895, 2894, 315);
  g->Binary(ynn_binary_multiply, 315, 299, 316);
  g->Binary(ynn_binary_divide, 316, 3430, 317);
  g->Unary(ynn_unary_round, 317, 318);
  g->Binary(ynn_binary_max, 318, 3328, 319);
  g->Binary(ynn_binary_min, 319, 3384, 320);
  g->Binary(ynn_binary_multiply, 320, 3430, 322);
  g->Convert(3742, 323);
  g->Binary(ynn_binary_multiply, 323, 3743, 324);
  g->Matmul(322, 324, 325, false, true);
  g->Binary(ynn_binary_divide, 325, 3336, 326);
  g->Unary(ynn_unary_round, 326, 327);
  g->Binary(ynn_binary_max, 327, 3328, 328);
  g->Binary(ynn_binary_min, 328, 3384, 329);
  g->Binary(ynn_binary_multiply, 329, 3336, 330);
  g->Unary(ynn_unary_square, 330, 331);
  g->Reduce(ynn_reduce_sum, 331, 2899, {2}, true);
  g->ShapeProduct(331, 2898, {2});
  g->Binary(ynn_binary_divide, 2899, 2898, 333);
  g->Binary(ynn_binary_add, 333, 3400, 334);
  g->Binary(ynn_binary_pow, 334, 3424, 335);
  g->Binary(ynn_binary_multiply, 330, 335, 336);
  g->Convert(3746, 337);
  g->Binary(ynn_binary_multiply, 336, 337, 338);
  g->Binary(ynn_binary_add, 294, 338, 339);
  g->Convert(3733, 340);
  g->Binary(ynn_binary_multiply, 339, 340, 341);
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
  g->Binary(ynn_binary_divide, 349, 3395, 350);
  g->Unary(ynn_unary_round, 350, 351);
  g->Binary(ynn_binary_max, 351, 3328, 352);
  g->Binary(ynn_binary_min, 352, 3384, 353);
  g->Binary(ynn_binary_multiply, 353, 3395, 355);
  g->Convert(3775, 356);
  g->Binary(ynn_binary_multiply, 356, 3776, 357);
  g->Matmul(355, 357, 358, false, true);
  g->Binary(ynn_binary_divide, 358, 3314, 359);
  g->Unary(ynn_unary_round, 359, 360);
  g->Binary(ynn_binary_max, 360, 3328, 361);
  g->Binary(ynn_binary_min, 361, 3384, 362);
  g->Binary(ynn_binary_multiply, 362, 3314, 363);
  g->Reshape(363, 364, {1,0,1,256});
  g->Transpose(364, 366, {0,2,1,3});
  g->Unary(ynn_unary_square, 366, 367);
  g->Reduce(ynn_reduce_sum, 367, 2905, {3}, true);
  g->ShapeProduct(367, 2904, {3});
  g->Binary(ynn_binary_divide, 2905, 2904, 368);
  g->Binary(ynn_binary_add, 368, 3400, 369);
  g->Binary(ynn_binary_pow, 369, 3424, 370);
  g->Binary(ynn_binary_multiply, 366, 370, 371);
  g->Convert(3774, 372);
  g->Binary(ynn_binary_multiply, 371, 372, 373);
  g->Slice(373, 374, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(373, 375, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 375, 377);
  g->Concat({377,374}, 378, 3);
  g->Binary(ynn_binary_multiply, 373, 2025, 379);
  g->Binary(ynn_binary_multiply, 378, 2249, 380);
  g->Binary(ynn_binary_add, 379, 380, 381);
  g->Convert(3782, 383);
  g->Binary(ynn_binary_multiply, 383, 3783, 384);
  g->Matmul(355, 384, 385, false, true);
  g->Binary(ynn_binary_divide, 385, 3314, 386);
  g->Unary(ynn_unary_round, 386, 387);
  g->Binary(ynn_binary_max, 387, 3328, 388);
  g->Binary(ynn_binary_min, 388, 3384, 389);
  g->Binary(ynn_binary_multiply, 389, 3314, 390);
  g->Reshape(390, 391, {1,0,1,256});
  g->Transpose(391, 392, {0,2,1,3});
  g->Unary(ynn_unary_square, 392, 394);
  g->Reduce(ynn_reduce_sum, 394, 2907, {3}, true);
  g->ShapeProduct(394, 2906, {3});
  g->Binary(ynn_binary_divide, 2907, 2906, 395);
  g->Binary(ynn_binary_add, 395, 3400, 396);
  g->Binary(ynn_binary_pow, 396, 3424, 397);
  g->Binary(ynn_binary_multiply, 392, 397, 398);
}

// Scope: "Layer6 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(381, 399, 0.0057707298547029495, 0);
  g->Append(3273, 399, 3890, 2, s2, s1);
  g->View(3890, 3919, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(3919, 400, 0.0057707298547029495, 0);
  g->Quantize(398, 401, 0.047244105488061905, 0);
  g->Append(3288, 401, 3905, 2, s2, s1);
  g->View(3905, 3933, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(3933, 403, 0.047244105488061905, 0);
}

// Scope: "Layer6 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Convert(3780, 404);
  g->Binary(ynn_binary_multiply, 404, 3781, 405);
  g->Matmul(355, 405, 408, false, true);
  g->Binary(ynn_binary_divide, 408, 3323, 409);
  g->Unary(ynn_unary_round, 409, 410);
  g->Binary(ynn_binary_max, 410, 3328, 411);
  g->Binary(ynn_binary_min, 411, 3384, 412);
  g->Binary(ynn_binary_multiply, 412, 3323, 413);
  g->SplitDim(413, 414, 2, {8,256});
  g->Transpose(414, 415, {0,2,1,3});
  g->Unary(ynn_unary_square, 415, 416);
  g->Reduce(ynn_reduce_sum, 416, 2909, {3}, true);
  g->ShapeProduct(416, 2908, {3});
  g->Binary(ynn_binary_divide, 2909, 2908, 417);
  g->Binary(ynn_binary_add, 417, 3400, 419);
  g->Binary(ynn_binary_pow, 419, 3424, 420);
  g->Binary(ynn_binary_multiply, 415, 420, 421);
  g->Convert(3779, 422);
  g->Binary(ynn_binary_multiply, 421, 422, 423);
  g->Slice(423, 424, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(423, 425, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 425, 426);
  g->Concat({426,424}, 427, 3);
  g->Binary(ynn_binary_multiply, 423, 2025, 428);
  g->Binary(ynn_binary_multiply, 427, 2249, 430);
  g->Binary(ynn_binary_add, 428, 430, 431);
}

// Scope: "Layer6 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(431, 400, 432, false, true);
  g->Mask(432, 3488, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 3488, 2915, {-1}, true);
  g->Binary(ynn_binary_subtract, 3488, 2915, 2912);
  g->Unary(ynn_unary_exp, 2912, 2913);
  g->Reduce(ynn_reduce_sum, 2913, 2916, {-1}, true);
  g->Binary(ynn_binary_divide, 2855, 2916, 2914);
  g->Binary(ynn_binary_multiply, 2913, 2914, 433);
  g->Matmul(433, 403, 434, false, false);
}

// Scope: "Layer6 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(434, 435, {0,2,1,3});
  g->FuseDims(435, 436, 2, 2);
  g->Binary(ynn_binary_divide, 436, 3317, 437);
  g->Unary(ynn_unary_round, 437, 438);
  g->Binary(ynn_binary_max, 438, 3328, 440);
  g->Binary(ynn_binary_min, 440, 3384, 441);
  g->Binary(ynn_binary_multiply, 441, 3317, 442);
  g->Convert(3777, 443);
  g->Binary(ynn_binary_multiply, 443, 3778, 444);
  g->Matmul(442, 444, 445, false, true);
  g->Binary(ynn_binary_divide, 445, 3448, 446);
  g->Unary(ynn_unary_round, 446, 447);
  g->Binary(ynn_binary_max, 447, 3328, 448);
  g->Binary(ynn_binary_min, 448, 3384, 449);
  g->Binary(ynn_binary_multiply, 449, 3448, 451);
}

// Scope: "Layer6 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 341, 342);
  g->Reduce(ynn_reduce_sum, 342, 2901, {2}, true);
  g->ShapeProduct(342, 2900, {2});
  g->Binary(ynn_binary_divide, 2901, 2900, 344);
  g->Binary(ynn_binary_add, 344, 3400, 345);
  g->Binary(ynn_binary_pow, 345, 3424, 346);
  g->Binary(ynn_binary_multiply, 341, 346, 347);
  g->Convert(3758, 348);
  g->Binary(ynn_binary_multiply, 347, 348, 349);
  BuildLayer6AttentionKvProjection(ctx);
  BuildLayer6AttentionCacheUpdate(ctx);
  BuildLayer6AttentionQueryProjection(ctx);
  BuildLayer6AttentionSdpa(ctx);
  BuildLayer6AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 451, 452);
  g->Reduce(ynn_reduce_sum, 452, 2918, {2}, true);
  g->ShapeProduct(452, 2917, {2});
  g->Binary(ynn_binary_divide, 2918, 2917, 453);
  g->Binary(ynn_binary_add, 453, 3400, 454);
  g->Binary(ynn_binary_pow, 454, 3424, 455);
  g->Binary(ynn_binary_multiply, 451, 455, 456);
  g->Convert(3770, 457);
  g->Binary(ynn_binary_multiply, 456, 457, 458);
  g->Binary(ynn_binary_add, 341, 458, 459);
}

// Scope: "Layer6 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 459, 460);
  g->Reduce(ynn_reduce_sum, 460, 2920, {2}, true);
  g->ShapeProduct(460, 2919, {2});
  g->Binary(ynn_binary_divide, 2920, 2919, 462);
  g->Binary(ynn_binary_add, 462, 3400, 463);
  g->Binary(ynn_binary_pow, 463, 3424, 464);
  g->Binary(ynn_binary_multiply, 459, 464, 465);
  g->Convert(3773, 466);
  g->Binary(ynn_binary_multiply, 465, 466, 467);
  g->Binary(ynn_binary_divide, 467, 3366, 468);
  g->Unary(ynn_unary_round, 468, 469);
  g->Binary(ynn_binary_max, 469, 3328, 470);
  g->Binary(ynn_binary_min, 470, 3384, 471);
  g->Binary(ynn_binary_multiply, 471, 3366, 473);
  g->Convert(3764, 474);
  g->Binary(ynn_binary_multiply, 474, 3765, 475);
  g->Matmul(473, 475, 476, false, true);
  g->Binary(ynn_binary_divide, 476, 3315, 477);
  g->Unary(ynn_unary_round, 477, 478);
  g->Binary(ynn_binary_max, 478, 3328, 479);
  g->Binary(ynn_binary_min, 479, 3384, 480);
  g->Binary(ynn_binary_multiply, 480, 3315, 481);
  g->Convert(3762, 483);
  g->Binary(ynn_binary_multiply, 483, 3763, 484);
  g->Matmul(473, 484, 485, false, true);
  g->Binary(ynn_binary_divide, 485, 3315, 486);
  g->Unary(ynn_unary_round, 486, 487);
  g->Binary(ynn_binary_max, 487, 3328, 488);
  g->Binary(ynn_binary_min, 488, 3384, 490);
  g->Binary(ynn_binary_multiply, 490, 3315, 491);
  g->Polynomial(491, 2923, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2923, 2924);
  g->Binary(ynn_binary_add, 2924, 2855, 2921);
  g->Binary(ynn_binary_multiply, 491, 2853, 2922);
  g->Binary(ynn_binary_multiply, 2922, 2921, 492);
  g->Binary(ynn_binary_multiply, 481, 492, 493);
  g->Binary(ynn_binary_divide, 493, 3300, 494);
  g->Unary(ynn_unary_round, 494, 495);
  g->Binary(ynn_binary_max, 495, 3328, 496);
  g->Binary(ynn_binary_min, 496, 3384, 497);
  g->Binary(ynn_binary_multiply, 497, 3300, 498);
  g->Convert(3760, 499);
  g->Binary(ynn_binary_multiply, 499, 3761, 501);
  g->Matmul(498, 501, 502, false, true);
  g->Binary(ynn_binary_divide, 502, 3359, 503);
  g->Unary(ynn_unary_round, 503, 504);
  g->Binary(ynn_binary_max, 504, 3328, 505);
  g->Binary(ynn_binary_min, 505, 3384, 506);
  g->Binary(ynn_binary_multiply, 506, 3359, 507);
  g->Unary(ynn_unary_square, 507, 508);
  g->Reduce(ynn_reduce_sum, 508, 2926, {2}, true);
  g->ShapeProduct(508, 2925, {2});
  g->Binary(ynn_binary_divide, 2926, 2925, 509);
  g->Binary(ynn_binary_add, 509, 3400, 510);
  g->Binary(ynn_binary_pow, 510, 3424, 513);
  g->Binary(ynn_binary_multiply, 507, 513, 514);
  g->Convert(3771, 515);
  g->Binary(ynn_binary_multiply, 514, 515, 516);
  g->Binary(ynn_binary_add, 459, 516, 517);
}

// Scope: "Layer6 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer6PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1022, 518, {0,0,6,0}, {-1,-1,1,-1});
  g->Reshape(518, 519, {1,0,256});
  g->Binary(ynn_binary_add, 519, 3874, 520);
  g->Binary(ynn_binary_multiply, 520, 3296, 521);
  g->Binary(ynn_binary_divide, 517, 3407, 522);
  g->Unary(ynn_unary_round, 522, 524);
  g->Binary(ynn_binary_max, 524, 3328, 525);
  g->Binary(ynn_binary_min, 525, 3384, 526);
  g->Binary(ynn_binary_multiply, 526, 3407, 527);
  g->Convert(3766, 528);
  g->Binary(ynn_binary_multiply, 528, 3767, 529);
  g->Matmul(527, 529, 530, false, true);
  g->Binary(ynn_binary_divide, 530, 3309, 531);
  g->Unary(ynn_unary_round, 531, 532);
  g->Binary(ynn_binary_max, 532, 3328, 533);
  g->Binary(ynn_binary_min, 533, 3384, 535);
  g->Binary(ynn_binary_multiply, 535, 3309, 536);
  g->Polynomial(536, 2931, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2931, 2932);
  g->Binary(ynn_binary_add, 2932, 2855, 2929);
  g->Binary(ynn_binary_multiply, 536, 2853, 2930);
  g->Binary(ynn_binary_multiply, 2930, 2929, 537);
  g->Binary(ynn_binary_multiply, 537, 521, 538);
  g->Binary(ynn_binary_divide, 538, 3443, 539);
  g->Unary(ynn_unary_round, 539, 540);
  g->Binary(ynn_binary_max, 540, 3328, 541);
  g->Binary(ynn_binary_min, 541, 3384, 542);
  g->Binary(ynn_binary_multiply, 542, 3443, 543);
  g->Convert(3768, 544);
  g->Binary(ynn_binary_multiply, 544, 3769, 546);
  g->Matmul(543, 546, 547, false, true);
  g->Binary(ynn_binary_divide, 547, 3437, 548);
  g->Unary(ynn_unary_round, 548, 549);
  g->Binary(ynn_binary_max, 549, 3328, 550);
  g->Binary(ynn_binary_min, 550, 3384, 551);
  g->Binary(ynn_binary_multiply, 551, 3437, 552);
  g->Unary(ynn_unary_square, 552, 553);
  g->Reduce(ynn_reduce_sum, 553, 2934, {2}, true);
  g->ShapeProduct(553, 2933, {2});
  g->Binary(ynn_binary_divide, 2934, 2933, 554);
  g->Binary(ynn_binary_add, 554, 3400, 555);
  g->Binary(ynn_binary_pow, 555, 3424, 557);
  g->Binary(ynn_binary_multiply, 552, 557, 558);
  g->Convert(3772, 559);
  g->Binary(ynn_binary_multiply, 558, 559, 560);
  g->Binary(ynn_binary_add, 517, 560, 561);
  g->Convert(3759, 562);
  g->Binary(ynn_binary_multiply, 561, 562, 563);
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
  g->Binary(ynn_binary_divide, 571, 3377, 572);
  g->Unary(ynn_unary_round, 572, 573);
  g->Binary(ynn_binary_max, 573, 3328, 574);
  g->Binary(ynn_binary_min, 574, 3384, 575);
  g->Binary(ynn_binary_multiply, 575, 3377, 576);
  g->Convert(3801, 577);
  g->Binary(ynn_binary_multiply, 577, 3802, 579);
  g->Matmul(576, 579, 580, false, true);
  g->Binary(ynn_binary_divide, 580, 3473, 581);
  g->Unary(ynn_unary_round, 581, 582);
  g->Binary(ynn_binary_max, 582, 3328, 583);
  g->Binary(ynn_binary_min, 583, 3384, 584);
  g->Binary(ynn_binary_multiply, 584, 3473, 585);
  g->Reshape(585, 586, {1,0,1,256});
  g->Transpose(586, 587, {0,2,1,3});
  g->Unary(ynn_unary_square, 587, 588);
  g->Reduce(ynn_reduce_sum, 588, 2938, {3}, true);
  g->ShapeProduct(588, 2937, {3});
  g->Binary(ynn_binary_divide, 2938, 2937, 590);
  g->Binary(ynn_binary_add, 590, 3400, 591);
  g->Binary(ynn_binary_pow, 591, 3424, 592);
  g->Binary(ynn_binary_multiply, 587, 592, 593);
  g->Convert(3800, 594);
  g->Binary(ynn_binary_multiply, 593, 594, 595);
  g->Slice(595, 596, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(595, 597, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 597, 598);
  g->Concat({598,596}, 599, 3);
  g->Binary(ynn_binary_multiply, 595, 2025, 601);
  g->Binary(ynn_binary_multiply, 599, 2249, 602);
  g->Binary(ynn_binary_add, 601, 602, 603);
  g->Convert(3808, 604);
  g->Binary(ynn_binary_multiply, 604, 3809, 605);
  g->Matmul(576, 605, 607, false, true);
  g->Binary(ynn_binary_divide, 607, 3473, 608);
  g->Unary(ynn_unary_round, 608, 609);
  g->Binary(ynn_binary_max, 609, 3328, 610);
  g->Binary(ynn_binary_min, 610, 3384, 611);
  g->Binary(ynn_binary_multiply, 611, 3473, 612);
  g->Reshape(612, 613, {1,0,1,256});
  g->Transpose(613, 614, {0,2,1,3});
  g->Unary(ynn_unary_square, 614, 615);
  g->Reduce(ynn_reduce_sum, 615, 2940, {3}, true);
  g->ShapeProduct(615, 2939, {3});
  g->Binary(ynn_binary_divide, 2940, 2939, 616);
  g->Binary(ynn_binary_add, 616, 3400, 619);
  g->Binary(ynn_binary_pow, 619, 3424, 620);
  g->Binary(ynn_binary_multiply, 614, 620, 621);
}

// Scope: "Layer7 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(603, 622, 0.005869260523468256, 0);
  g->Append(3274, 622, 3891, 2, s2, s1);
  g->View(3891, 3920, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(3920, 623, 0.005869260523468256, 0);
  g->Quantize(621, 624, 0.047244105488061905, 0);
  g->Append(3289, 624, 3906, 2, s2, s1);
  g->View(3906, 3934, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(3934, 625, 0.047244105488061905, 0);
}

// Scope: "Layer7 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Convert(3806, 626);
  g->Binary(ynn_binary_multiply, 626, 3807, 627);
  g->Matmul(576, 627, 628, false, true);
  g->Binary(ynn_binary_divide, 628, 3431, 629);
  g->Unary(ynn_unary_round, 629, 630);
  g->Binary(ynn_binary_max, 630, 3328, 631);
  g->Binary(ynn_binary_min, 631, 3384, 632);
  g->Binary(ynn_binary_multiply, 632, 3431, 633);
  g->SplitDim(633, 634, 2, {8,256});
  g->Transpose(634, 635, {0,2,1,3});
  g->Unary(ynn_unary_square, 635, 636);
  g->Reduce(ynn_reduce_sum, 636, 2942, {3}, true);
  g->ShapeProduct(636, 2941, {3});
  g->Binary(ynn_binary_divide, 2942, 2941, 637);
  g->Binary(ynn_binary_add, 637, 3400, 638);
  g->Binary(ynn_binary_pow, 638, 3424, 639);
  g->Binary(ynn_binary_multiply, 635, 639, 640);
  g->Convert(3805, 641);
  g->Binary(ynn_binary_multiply, 640, 641, 642);
  g->Slice(642, 643, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(642, 644, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 644, 645);
  g->Concat({645,643}, 646, 3);
  g->Binary(ynn_binary_multiply, 642, 2025, 647);
  g->Binary(ynn_binary_multiply, 646, 2249, 648);
  g->Binary(ynn_binary_add, 647, 648, 649);
}

// Scope: "Layer7 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(649, 623, 650, false, true);
  g->Mask(650, 3489, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 3489, 2946, {-1}, true);
  g->Binary(ynn_binary_subtract, 3489, 2946, 2943);
  g->Unary(ynn_unary_exp, 2943, 2944);
  g->Reduce(ynn_reduce_sum, 2944, 2947, {-1}, true);
  g->Binary(ynn_binary_divide, 2855, 2947, 2945);
  g->Binary(ynn_binary_multiply, 2944, 2945, 651);
  g->Matmul(651, 625, 652, false, false);
}

// Scope: "Layer7 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(652, 653, {0,2,1,3});
  g->FuseDims(653, 654, 2, 2);
  g->Binary(ynn_binary_divide, 654, 3320, 655);
  g->Unary(ynn_unary_round, 655, 656);
  g->Binary(ynn_binary_max, 656, 3328, 657);
  g->Binary(ynn_binary_min, 657, 3384, 658);
  g->Binary(ynn_binary_multiply, 658, 3320, 659);
  g->Convert(3803, 660);
  g->Binary(ynn_binary_multiply, 660, 3804, 661);
  g->Matmul(659, 661, 662, false, true);
  g->Binary(ynn_binary_divide, 662, 3393, 663);
  g->Unary(ynn_unary_round, 663, 664);
  g->Binary(ynn_binary_max, 664, 3328, 665);
  g->Binary(ynn_binary_min, 665, 3384, 666);
  g->Binary(ynn_binary_multiply, 666, 3393, 667);
}

// Scope: "Layer7 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 563, 564);
  g->Reduce(ynn_reduce_sum, 564, 2936, {2}, true);
  g->ShapeProduct(564, 2935, {2});
  g->Binary(ynn_binary_divide, 2936, 2935, 565);
  g->Binary(ynn_binary_add, 565, 3400, 566);
  g->Binary(ynn_binary_pow, 566, 3424, 568);
  g->Binary(ynn_binary_multiply, 563, 568, 569);
  g->Convert(3784, 570);
  g->Binary(ynn_binary_multiply, 569, 570, 571);
  BuildLayer7AttentionKvProjection(ctx);
  BuildLayer7AttentionCacheUpdate(ctx);
  BuildLayer7AttentionQueryProjection(ctx);
  BuildLayer7AttentionSdpa(ctx);
  BuildLayer7AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 667, 668);
  g->Reduce(ynn_reduce_sum, 668, 2949, {2}, true);
  g->ShapeProduct(668, 2948, {2});
  g->Binary(ynn_binary_divide, 2949, 2948, 670);
  g->Binary(ynn_binary_add, 670, 3400, 671);
  g->Binary(ynn_binary_pow, 671, 3424, 672);
  g->Binary(ynn_binary_multiply, 667, 672, 673);
  g->Convert(3796, 674);
  g->Binary(ynn_binary_multiply, 673, 674, 675);
  g->Binary(ynn_binary_add, 563, 675, 676);
}

// Scope: "Layer7 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 676, 677);
  g->Reduce(ynn_reduce_sum, 677, 2951, {2}, true);
  g->ShapeProduct(677, 2950, {2});
  g->Binary(ynn_binary_divide, 2951, 2950, 678);
  g->Binary(ynn_binary_add, 678, 3400, 679);
  g->Binary(ynn_binary_pow, 679, 3424, 681);
  g->Binary(ynn_binary_multiply, 676, 681, 682);
  g->Convert(3799, 683);
  g->Binary(ynn_binary_multiply, 682, 683, 684);
  g->Binary(ynn_binary_divide, 684, 3307, 685);
  g->Unary(ynn_unary_round, 685, 686);
  g->Binary(ynn_binary_max, 686, 3328, 687);
  g->Binary(ynn_binary_min, 687, 3384, 688);
  g->Binary(ynn_binary_multiply, 688, 3307, 689);
  g->Convert(3790, 690);
  g->Binary(ynn_binary_multiply, 690, 3791, 692);
  g->Matmul(689, 692, 693, false, true);
  g->Binary(ynn_binary_divide, 693, 3474, 694);
  g->Unary(ynn_unary_round, 694, 695);
  g->Binary(ynn_binary_max, 695, 3328, 696);
  g->Binary(ynn_binary_min, 696, 3384, 697);
  g->Binary(ynn_binary_multiply, 697, 3474, 698);
  g->Convert(3788, 700);
  g->Binary(ynn_binary_multiply, 700, 3789, 701);
  g->Matmul(689, 701, 702, false, true);
  g->Binary(ynn_binary_divide, 702, 3474, 703);
  g->Unary(ynn_unary_round, 703, 704);
  g->Binary(ynn_binary_max, 704, 3328, 705);
  g->Binary(ynn_binary_min, 705, 3384, 706);
  g->Binary(ynn_binary_multiply, 706, 3474, 707);
  g->Polynomial(707, 2954, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2954, 2955);
  g->Binary(ynn_binary_add, 2955, 2855, 2952);
  g->Binary(ynn_binary_multiply, 707, 2853, 2953);
  g->Binary(ynn_binary_multiply, 2953, 2952, 710);
  g->Binary(ynn_binary_multiply, 698, 710, 711);
  g->Binary(ynn_binary_divide, 711, 3335, 712);
  g->Unary(ynn_unary_round, 712, 713);
  g->Binary(ynn_binary_max, 713, 3328, 714);
  g->Binary(ynn_binary_min, 714, 3384, 715);
  g->Binary(ynn_binary_multiply, 715, 3335, 716);
  g->Convert(3786, 717);
  g->Binary(ynn_binary_multiply, 717, 3787, 718);
  g->Matmul(716, 718, 719, false, true);
  g->Binary(ynn_binary_divide, 719, 3412, 721);
  g->Unary(ynn_unary_round, 721, 722);
  g->Binary(ynn_binary_max, 722, 3328, 723);
  g->Binary(ynn_binary_min, 723, 3384, 724);
  g->Binary(ynn_binary_multiply, 724, 3412, 725);
  g->Unary(ynn_unary_square, 725, 726);
  g->Reduce(ynn_reduce_sum, 726, 2957, {2}, true);
  g->ShapeProduct(726, 2956, {2});
  g->Binary(ynn_binary_divide, 2957, 2956, 727);
  g->Binary(ynn_binary_add, 727, 3400, 728);
  g->Binary(ynn_binary_pow, 728, 3424, 729);
  g->Binary(ynn_binary_multiply, 725, 729, 730);
  g->Convert(3797, 732);
  g->Binary(ynn_binary_multiply, 730, 732, 733);
  g->Binary(ynn_binary_add, 676, 733, 734);
}

// Scope: "Layer7 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer7PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1022, 735, {0,0,7,0}, {-1,-1,1,-1});
  g->Reshape(735, 736, {1,0,256});
  g->Binary(ynn_binary_add, 736, 3875, 737);
  g->Binary(ynn_binary_multiply, 737, 3296, 738);
  g->Binary(ynn_binary_divide, 734, 3304, 739);
  g->Unary(ynn_unary_round, 739, 740);
  g->Binary(ynn_binary_max, 740, 3328, 741);
  g->Binary(ynn_binary_min, 741, 3384, 743);
  g->Binary(ynn_binary_multiply, 743, 3304, 744);
  g->Convert(3792, 745);
  g->Binary(ynn_binary_multiply, 745, 3793, 746);
  g->Matmul(744, 746, 747, false, true);
  g->Binary(ynn_binary_divide, 747, 3311, 748);
  g->Unary(ynn_unary_round, 748, 749);
  g->Binary(ynn_binary_max, 749, 3328, 750);
  g->Binary(ynn_binary_min, 750, 3384, 751);
  g->Binary(ynn_binary_multiply, 751, 3311, 752);
  g->Polynomial(752, 2964, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2964, 2965);
  g->Binary(ynn_binary_add, 2965, 2855, 2962);
  g->Binary(ynn_binary_multiply, 752, 2853, 2963);
  g->Binary(ynn_binary_multiply, 2963, 2962, 754);
  g->Binary(ynn_binary_multiply, 754, 738, 755);
  g->Binary(ynn_binary_divide, 755, 3434, 756);
  g->Unary(ynn_unary_round, 756, 757);
  g->Binary(ynn_binary_max, 757, 3328, 758);
  g->Binary(ynn_binary_min, 758, 3384, 759);
  g->Binary(ynn_binary_multiply, 759, 3434, 760);
  g->Convert(3794, 761);
  g->Binary(ynn_binary_multiply, 761, 3795, 762);
  g->Matmul(760, 762, 763, false, true);
  g->Binary(ynn_binary_divide, 763, 3329, 765);
  g->Unary(ynn_unary_round, 765, 766);
  g->Binary(ynn_binary_max, 766, 3328, 767);
  g->Binary(ynn_binary_min, 767, 3384, 768);
  g->Binary(ynn_binary_multiply, 768, 3329, 769);
  g->Unary(ynn_unary_square, 769, 770);
  g->Reduce(ynn_reduce_sum, 770, 2967, {2}, true);
  g->ShapeProduct(770, 2966, {2});
  g->Binary(ynn_binary_divide, 2967, 2966, 771);
  g->Binary(ynn_binary_add, 771, 3400, 772);
  g->Binary(ynn_binary_pow, 772, 3424, 773);
  g->Binary(ynn_binary_multiply, 769, 773, 774);
  g->Convert(3798, 776);
  g->Binary(ynn_binary_multiply, 774, 776, 777);
  g->Binary(ynn_binary_add, 734, 777, 778);
  g->Convert(3785, 779);
  g->Binary(ynn_binary_multiply, 778, 779, 780);
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
  g->Binary(ynn_binary_divide, 788, 3409, 789);
  g->Unary(ynn_unary_round, 789, 790);
  g->Binary(ynn_binary_max, 790, 3328, 791);
  g->Binary(ynn_binary_min, 791, 3384, 792);
  g->Binary(ynn_binary_multiply, 792, 3409, 793);
  g->Convert(3827, 794);
  g->Binary(ynn_binary_multiply, 794, 3828, 795);
  g->Matmul(793, 795, 796, false, true);
  g->Binary(ynn_binary_divide, 796, 3450, 798);
  g->Unary(ynn_unary_round, 798, 799);
  g->Binary(ynn_binary_max, 799, 3328, 800);
  g->Binary(ynn_binary_min, 800, 3384, 801);
  g->Binary(ynn_binary_multiply, 801, 3450, 802);
  g->Reshape(802, 803, {1,0,1,256});
  g->Transpose(803, 804, {0,2,1,3});
  g->Unary(ynn_unary_square, 804, 805);
  g->Reduce(ynn_reduce_sum, 805, 2971, {3}, true);
  g->ShapeProduct(805, 2970, {3});
  g->Binary(ynn_binary_divide, 2971, 2970, 806);
  g->Binary(ynn_binary_add, 806, 3400, 807);
  g->Binary(ynn_binary_pow, 807, 3424, 809);
  g->Binary(ynn_binary_multiply, 804, 809, 810);
  g->Convert(3826, 811);
  g->Binary(ynn_binary_multiply, 810, 811, 812);
  g->Slice(812, 813, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(812, 814, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 814, 815);
  g->Concat({815,813}, 816, 3);
  g->Binary(ynn_binary_multiply, 812, 2025, 817);
  g->Binary(ynn_binary_multiply, 816, 2249, 818);
  g->Binary(ynn_binary_add, 817, 818, 821);
  g->Convert(3834, 822);
  g->Binary(ynn_binary_multiply, 822, 3835, 823);
  g->Matmul(793, 823, 824, false, true);
  g->Binary(ynn_binary_divide, 824, 3450, 825);
  g->Unary(ynn_unary_round, 825, 827);
  g->Binary(ynn_binary_max, 827, 3328, 828);
  g->Binary(ynn_binary_min, 828, 3384, 829);
  g->Binary(ynn_binary_multiply, 829, 3450, 830);
  g->Reshape(830, 831, {1,0,1,256});
  g->Transpose(831, 832, {0,2,1,3});
  g->Unary(ynn_unary_square, 832, 833);
  g->Reduce(ynn_reduce_sum, 833, 2973, {3}, true);
  g->ShapeProduct(833, 2972, {3});
  g->Binary(ynn_binary_divide, 2973, 2972, 834);
  g->Binary(ynn_binary_add, 834, 3400, 835);
  g->Binary(ynn_binary_pow, 835, 3424, 836);
  g->Binary(ynn_binary_multiply, 832, 836, 838);
}

// Scope: "Layer8 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(821, 839, 0.006215503439307213, 0);
  g->Append(3275, 839, 3892, 2, s2, s1);
  g->View(3892, 3921, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(3921, 840, 0.006215503439307213, 0);
  g->Quantize(838, 841, 0.047244105488061905, 0);
  g->Append(3290, 841, 3907, 2, s2, s1);
  g->View(3907, 3935, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(3935, 842, 0.047244105488061905, 0);
}

// Scope: "Layer8 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Convert(3832, 844);
  g->Binary(ynn_binary_multiply, 844, 3833, 845);
  g->Matmul(793, 845, 846, false, true);
  g->Binary(ynn_binary_divide, 846, 3331, 847);
  g->Unary(ynn_unary_round, 847, 848);
  g->Binary(ynn_binary_max, 848, 3328, 849);
  g->Binary(ynn_binary_min, 849, 3384, 851);
  g->Binary(ynn_binary_multiply, 851, 3331, 852);
  g->SplitDim(852, 853, 2, {8,256});
  g->Transpose(853, 854, {0,2,1,3});
  g->Unary(ynn_unary_square, 854, 855);
  g->Reduce(ynn_reduce_sum, 855, 2975, {3}, true);
  g->ShapeProduct(855, 2974, {3});
  g->Binary(ynn_binary_divide, 2975, 2974, 856);
  g->Binary(ynn_binary_add, 856, 3400, 857);
  g->Binary(ynn_binary_pow, 857, 3424, 858);
  g->Binary(ynn_binary_multiply, 854, 858, 859);
  g->Convert(3831, 860);
  g->Binary(ynn_binary_multiply, 859, 860, 862);
  g->Slice(862, 863, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(862, 864, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 864, 865);
  g->Concat({865,863}, 866, 3);
  g->Binary(ynn_binary_multiply, 862, 2025, 867);
  g->Binary(ynn_binary_multiply, 866, 2249, 868);
  g->Binary(ynn_binary_add, 867, 868, 869);
}

// Scope: "Layer8 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(869, 840, 870, false, true);
  g->Mask(870, 3490, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 3490, 2979, {-1}, true);
  g->Binary(ynn_binary_subtract, 3490, 2979, 2976);
  g->Unary(ynn_unary_exp, 2976, 2977);
  g->Reduce(ynn_reduce_sum, 2977, 2980, {-1}, true);
  g->Binary(ynn_binary_divide, 2855, 2980, 2978);
  g->Binary(ynn_binary_multiply, 2977, 2978, 872);
  g->Matmul(872, 842, 873, false, false);
}

// Scope: "Layer8 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(873, 874, {0,2,1,3});
  g->FuseDims(874, 875, 2, 2);
  g->Binary(ynn_binary_divide, 875, 3324, 876);
  g->Unary(ynn_unary_round, 876, 877);
  g->Binary(ynn_binary_max, 877, 3328, 878);
  g->Binary(ynn_binary_min, 878, 3384, 879);
  g->Binary(ynn_binary_multiply, 879, 3324, 880);
  g->Convert(3829, 881);
  g->Binary(ynn_binary_multiply, 881, 3830, 883);
  g->Matmul(880, 883, 884, false, true);
  g->Binary(ynn_binary_divide, 884, 3345, 885);
  g->Unary(ynn_unary_round, 885, 886);
  g->Binary(ynn_binary_max, 886, 3328, 887);
  g->Binary(ynn_binary_min, 887, 3384, 888);
  g->Binary(ynn_binary_multiply, 888, 3345, 889);
}

// Scope: "Layer8 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 780, 781);
  g->Reduce(ynn_reduce_sum, 781, 2969, {2}, true);
  g->ShapeProduct(781, 2968, {2});
  g->Binary(ynn_binary_divide, 2969, 2968, 782);
  g->Binary(ynn_binary_add, 782, 3400, 783);
  g->Binary(ynn_binary_pow, 783, 3424, 784);
  g->Binary(ynn_binary_multiply, 780, 784, 785);
  g->Convert(3810, 787);
  g->Binary(ynn_binary_multiply, 785, 787, 788);
  BuildLayer8AttentionKvProjection(ctx);
  BuildLayer8AttentionCacheUpdate(ctx);
  BuildLayer8AttentionQueryProjection(ctx);
  BuildLayer8AttentionSdpa(ctx);
  BuildLayer8AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 889, 890);
  g->Reduce(ynn_reduce_sum, 890, 2982, {2}, true);
  g->ShapeProduct(890, 2981, {2});
  g->Binary(ynn_binary_divide, 2982, 2981, 891);
  g->Binary(ynn_binary_add, 891, 3400, 892);
  g->Binary(ynn_binary_pow, 892, 3424, 894);
  g->Binary(ynn_binary_multiply, 889, 894, 895);
  g->Convert(3822, 896);
  g->Binary(ynn_binary_multiply, 895, 896, 897);
  g->Binary(ynn_binary_add, 780, 897, 898);
}

// Scope: "Layer8 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 898, 899);
  g->Reduce(ynn_reduce_sum, 899, 2984, {2}, true);
  g->ShapeProduct(899, 2983, {2});
  g->Binary(ynn_binary_divide, 2984, 2983, 900);
  g->Binary(ynn_binary_add, 900, 3400, 901);
  g->Binary(ynn_binary_pow, 901, 3424, 902);
  g->Binary(ynn_binary_multiply, 898, 902, 903);
  g->Convert(3825, 905);
  g->Binary(ynn_binary_multiply, 903, 905, 906);
  g->Binary(ynn_binary_divide, 906, 3383, 907);
  g->Unary(ynn_unary_round, 907, 908);
  g->Binary(ynn_binary_max, 908, 3328, 909);
  g->Binary(ynn_binary_min, 909, 3384, 910);
  g->Binary(ynn_binary_multiply, 910, 3383, 911);
  g->Convert(3816, 912);
  g->Binary(ynn_binary_multiply, 912, 3817, 913);
  g->Matmul(911, 913, 914, false, true);
  g->Binary(ynn_binary_divide, 914, 3318, 917);
  g->Unary(ynn_unary_round, 917, 918);
  g->Binary(ynn_binary_max, 918, 3328, 919);
  g->Binary(ynn_binary_min, 919, 3384, 920);
  g->Binary(ynn_binary_multiply, 920, 3318, 921);
  g->Convert(3814, 923);
  g->Binary(ynn_binary_multiply, 923, 3815, 924);
  g->Matmul(911, 924, 925, false, true);
  g->Binary(ynn_binary_divide, 925, 3318, 926);
  g->Unary(ynn_unary_round, 926, 927);
  g->Binary(ynn_binary_max, 927, 3328, 928);
  g->Binary(ynn_binary_min, 928, 3384, 929);
  g->Binary(ynn_binary_multiply, 929, 3318, 930);
  g->Polynomial(930, 2989, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2989, 2990);
  g->Binary(ynn_binary_add, 2990, 2855, 2987);
  g->Binary(ynn_binary_multiply, 930, 2853, 2988);
  g->Binary(ynn_binary_multiply, 2988, 2987, 931);
  g->Binary(ynn_binary_multiply, 921, 931, 932);
  g->Binary(ynn_binary_divide, 932, 3380, 934);
  g->Unary(ynn_unary_round, 934, 935);
  g->Binary(ynn_binary_max, 935, 3328, 936);
  g->Binary(ynn_binary_min, 936, 3384, 937);
  g->Binary(ynn_binary_multiply, 937, 3380, 938);
  g->Convert(3812, 939);
  g->Binary(ynn_binary_multiply, 939, 3813, 940);
  g->Matmul(938, 940, 941, false, true);
  g->Binary(ynn_binary_divide, 941, 3426, 942);
  g->Unary(ynn_unary_round, 942, 943);
  g->Binary(ynn_binary_max, 943, 3328, 945);
  g->Binary(ynn_binary_min, 945, 3384, 946);
  g->Binary(ynn_binary_multiply, 946, 3426, 947);
  g->Unary(ynn_unary_square, 947, 948);
  g->Reduce(ynn_reduce_sum, 948, 2992, {2}, true);
  g->ShapeProduct(948, 2991, {2});
  g->Binary(ynn_binary_divide, 2992, 2991, 949);
  g->Binary(ynn_binary_add, 949, 3400, 950);
  g->Binary(ynn_binary_pow, 950, 3424, 951);
  g->Binary(ynn_binary_multiply, 947, 951, 952);
  g->Convert(3823, 953);
  g->Binary(ynn_binary_multiply, 952, 953, 954);
  g->Binary(ynn_binary_add, 898, 954, 956);
}

// Scope: "Layer8 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer8PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1022, 957, {0,0,8,0}, {-1,-1,1,-1});
  g->Reshape(957, 958, {1,0,256});
  g->Binary(ynn_binary_add, 958, 3876, 959);
  g->Binary(ynn_binary_multiply, 959, 3296, 960);
  g->Binary(ynn_binary_divide, 956, 3310, 961);
  g->Unary(ynn_unary_round, 961, 962);
  g->Binary(ynn_binary_max, 962, 3328, 963);
  g->Binary(ynn_binary_min, 963, 3384, 964);
  g->Binary(ynn_binary_multiply, 964, 3310, 965);
  g->Convert(3818, 967);
  g->Binary(ynn_binary_multiply, 967, 3819, 968);
  g->Matmul(965, 968, 969, false, true);
  g->Binary(ynn_binary_divide, 969, 3316, 970);
  g->Unary(ynn_unary_round, 970, 971);
  g->Binary(ynn_binary_max, 971, 3328, 972);
  g->Binary(ynn_binary_min, 972, 3384, 973);
  g->Binary(ynn_binary_multiply, 973, 3316, 974);
  g->Polynomial(974, 2995, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 2995, 2996);
  g->Binary(ynn_binary_add, 2996, 2855, 2993);
  g->Binary(ynn_binary_multiply, 974, 2853, 2994);
  g->Binary(ynn_binary_multiply, 2994, 2993, 975);
  g->Binary(ynn_binary_multiply, 975, 960, 976);
  g->Binary(ynn_binary_divide, 976, 3347, 978);
  g->Unary(ynn_unary_round, 978, 979);
  g->Binary(ynn_binary_max, 979, 3328, 980);
  g->Binary(ynn_binary_min, 980, 3384, 981);
  g->Binary(ynn_binary_multiply, 981, 3347, 982);
  g->Convert(3820, 983);
  g->Binary(ynn_binary_multiply, 983, 3821, 984);
  g->Matmul(982, 984, 985, false, true);
  g->Binary(ynn_binary_divide, 985, 3303, 986);
  g->Unary(ynn_unary_round, 986, 987);
  g->Binary(ynn_binary_max, 987, 3328, 989);
  g->Binary(ynn_binary_min, 989, 3384, 990);
  g->Binary(ynn_binary_multiply, 990, 3303, 991);
  g->Unary(ynn_unary_square, 991, 992);
  g->Reduce(ynn_reduce_sum, 992, 2998, {2}, true);
  g->ShapeProduct(992, 2997, {2});
  g->Binary(ynn_binary_divide, 2998, 2997, 993);
  g->Binary(ynn_binary_add, 993, 3400, 994);
  g->Binary(ynn_binary_pow, 994, 3424, 995);
  g->Binary(ynn_binary_multiply, 991, 995, 996);
  g->Convert(3824, 997);
  g->Binary(ynn_binary_multiply, 996, 997, 998);
  g->Binary(ynn_binary_add, 956, 998, 1000);
  g->Convert(3811, 1001);
  g->Binary(ynn_binary_multiply, 1000, 1001, 1002);
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
  g->Binary(ynn_binary_divide, 1009, 3295, 1011);
  g->Unary(ynn_unary_round, 1011, 1012);
  g->Binary(ynn_binary_max, 1012, 3328, 1013);
  g->Binary(ynn_binary_min, 1013, 3384, 1014);
  g->Binary(ynn_binary_multiply, 1014, 3295, 1015);
  g->Convert(3853, 1016);
  g->Binary(ynn_binary_multiply, 1016, 3854, 1017);
  g->Matmul(1015, 1017, 1018, false, true);
  g->Binary(ynn_binary_divide, 1018, 3456, 1019);
  g->Unary(ynn_unary_round, 1019, 1020);
  g->Binary(ynn_binary_max, 1020, 3328, 1024);
  g->Binary(ynn_binary_min, 1024, 3384, 1025);
  g->Binary(ynn_binary_multiply, 1025, 3456, 1026);
  g->Reshape(1026, 1027, {1,0,1,512});
  g->Transpose(1027, 1028, {0,2,1,3});
  g->Unary(ynn_unary_square, 1028, 1029);
  g->Reduce(ynn_reduce_sum, 1029, 3002, {3}, true);
  g->ShapeProduct(1029, 3001, {3});
  g->Binary(ynn_binary_divide, 3002, 3001, 1030);
  g->Binary(ynn_binary_add, 1030, 3400, 1031);
  g->Binary(ynn_binary_pow, 1031, 3424, 1032);
  g->Binary(ynn_binary_multiply, 1028, 1032, 1033);
  g->Convert(3852, 1035);
  g->Binary(ynn_binary_multiply, 1033, 1035, 1036);
  g->Slice(1036, 1037, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(1036, 1038, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 1038, 1039);
  g->Concat({1039,1037}, 1040, 3);
  g->Binary(ynn_binary_multiply, 1036, 2651, 1041);
  g->Binary(ynn_binary_multiply, 1040, 2750, 1042);
  g->Binary(ynn_binary_add, 1041, 1042, 1043);
  g->Convert(3860, 1045);
  g->Binary(ynn_binary_multiply, 1045, 3861, 1046);
  g->Matmul(1015, 1046, 1047, false, true);
  g->Binary(ynn_binary_divide, 1047, 3456, 1048);
  g->Unary(ynn_unary_round, 1048, 1049);
  g->Binary(ynn_binary_max, 1049, 3328, 1050);
  g->Binary(ynn_binary_min, 1050, 3384, 1052);
  g->Binary(ynn_binary_multiply, 1052, 3456, 1053);
  g->Reshape(1053, 1054, {1,0,1,512});
  g->Transpose(1054, 1055, {0,2,1,3});
  g->Unary(ynn_unary_square, 1055, 1056);
  g->Reduce(ynn_reduce_sum, 1056, 3004, {3}, true);
  g->ShapeProduct(1056, 3003, {3});
  g->Binary(ynn_binary_divide, 3004, 3003, 1057);
  g->Binary(ynn_binary_add, 1057, 3400, 1058);
  g->Binary(ynn_binary_pow, 1058, 3424, 1059);
  g->Binary(ynn_binary_multiply, 1055, 1059, 1060);
}

// Scope: "Layer9 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(1043, 1061, 0.0010733711533248425, 0);
  g->Append(3276, 1061, 3893, 2, s2, s1);
  g->View(3893, 3922, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(3922, 1063, 0.0010733711533248425, 0);
  g->Quantize(1060, 1064, 0.01785714365541935, 0);
  g->Append(3291, 1064, 3908, 2, s2, s1);
  g->View(3908, 3936, 2, slinky::expr(int64_t{0}), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(3936, 1065, 0.01785714365541935, 0);
}

// Scope: "Layer9 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Convert(3858, 1067);
  g->Binary(ynn_binary_multiply, 1067, 3859, 1068);
  g->Matmul(1015, 1068, 1069, false, true);
  g->Binary(ynn_binary_divide, 1069, 3358, 1070);
  g->Unary(ynn_unary_round, 1070, 1071);
  g->Binary(ynn_binary_max, 1071, 3328, 1072);
  g->Binary(ynn_binary_min, 1072, 3384, 1073);
  g->Binary(ynn_binary_multiply, 1073, 3358, 1074);
  g->SplitDim(1074, 1076, 2, {8,512});
  g->Transpose(1076, 1077, {0,2,1,3});
  g->Unary(ynn_unary_square, 1077, 1078);
  g->Reduce(ynn_reduce_sum, 1078, 3006, {3}, true);
  g->ShapeProduct(1078, 3005, {3});
  g->Binary(ynn_binary_divide, 3006, 3005, 1079);
  g->Binary(ynn_binary_add, 1079, 3400, 1080);
  g->Binary(ynn_binary_pow, 1080, 3424, 1081);
  g->Binary(ynn_binary_multiply, 1077, 1081, 1082);
  g->Convert(3857, 1083);
  g->Binary(ynn_binary_multiply, 1082, 1083, 1084);
  g->Slice(1084, 1085, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(1084, 1087, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 1087, 1088);
  g->Concat({1088,1085}, 1089, 3);
  g->Binary(ynn_binary_multiply, 1084, 2651, 1090);
  g->Binary(ynn_binary_multiply, 1089, 2750, 1091);
  g->Binary(ynn_binary_add, 1090, 1091, 1092);
}

// Scope: "Layer9 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(1092, 1063, 1093, false, true);
  g->Mask(1093, 3491, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 3491, 3010, {-1}, true);
  g->Binary(ynn_binary_subtract, 3491, 3010, 3007);
  g->Unary(ynn_unary_exp, 3007, 3008);
  g->Reduce(ynn_reduce_sum, 3008, 3011, {-1}, true);
  g->Binary(ynn_binary_divide, 2855, 3011, 3009);
  g->Binary(ynn_binary_multiply, 3008, 3009, 1094);
  g->Matmul(1094, 1065, 1095, false, false);
}

// Scope: "Layer9 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1095, 1097, {0,2,1,3});
  g->FuseDims(1097, 1098, 2, 2);
  g->Binary(ynn_binary_divide, 1098, 3372, 1099);
  g->Unary(ynn_unary_round, 1099, 1100);
  g->Binary(ynn_binary_max, 1100, 3328, 1101);
  g->Binary(ynn_binary_min, 1101, 3384, 1102);
  g->Binary(ynn_binary_multiply, 1102, 3372, 1103);
  g->Convert(3855, 1104);
  g->Binary(ynn_binary_multiply, 1104, 3856, 1105);
  g->Matmul(1103, 1105, 1106, false, true);
  g->Binary(ynn_binary_divide, 1106, 3321, 1108);
  g->Unary(ynn_unary_round, 1108, 1109);
  g->Binary(ynn_binary_max, 1109, 3328, 1110);
  g->Binary(ynn_binary_min, 1110, 3384, 1111);
  g->Binary(ynn_binary_multiply, 1111, 3321, 1112);
}

// Scope: "Layer9 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1002, 1003);
  g->Reduce(ynn_reduce_sum, 1003, 3000, {2}, true);
  g->ShapeProduct(1003, 2999, {2});
  g->Binary(ynn_binary_divide, 3000, 2999, 1004);
  g->Binary(ynn_binary_add, 1004, 3400, 1005);
  g->Binary(ynn_binary_pow, 1005, 3424, 1006);
  g->Binary(ynn_binary_multiply, 1002, 1006, 1007);
  g->Convert(3836, 1008);
  g->Binary(ynn_binary_multiply, 1007, 1008, 1009);
  BuildLayer9AttentionKvProjection(ctx);
  BuildLayer9AttentionCacheUpdate(ctx);
  BuildLayer9AttentionQueryProjection(ctx);
  BuildLayer9AttentionSdpa(ctx);
  BuildLayer9AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1112, 1113);
  g->Reduce(ynn_reduce_sum, 1113, 3013, {2}, true);
  g->ShapeProduct(1113, 3012, {2});
  g->Binary(ynn_binary_divide, 3013, 3012, 1114);
  g->Binary(ynn_binary_add, 1114, 3400, 1115);
  g->Binary(ynn_binary_pow, 1115, 3424, 1116);
  g->Binary(ynn_binary_multiply, 1112, 1116, 1117);
  g->Convert(3848, 1120);
  g->Binary(ynn_binary_multiply, 1117, 1120, 1121);
  g->Binary(ynn_binary_add, 1002, 1121, 1122);
}

// Scope: "Layer9 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1122, 1123);
  g->Reduce(ynn_reduce_sum, 1123, 3015, {2}, true);
  g->ShapeProduct(1123, 3014, {2});
  g->Binary(ynn_binary_divide, 3015, 3014, 1124);
  g->Binary(ynn_binary_add, 1124, 3400, 1125);
  g->Binary(ynn_binary_pow, 1125, 3424, 1126);
  g->Binary(ynn_binary_multiply, 1122, 1126, 1127);
  g->Convert(3851, 1128);
  g->Binary(ynn_binary_multiply, 1127, 1128, 1129);
  g->Binary(ynn_binary_divide, 1129, 3410, 1131);
  g->Unary(ynn_unary_round, 1131, 1132);
  g->Binary(ynn_binary_max, 1132, 3328, 1133);
  g->Binary(ynn_binary_min, 1133, 3384, 1134);
  g->Binary(ynn_binary_multiply, 1134, 3410, 1135);
  g->Convert(3842, 1136);
  g->Binary(ynn_binary_multiply, 1136, 3843, 1137);
  g->Matmul(1135, 1137, 1138, false, true);
  g->Binary(ynn_binary_divide, 1138, 3405, 1139);
  g->Unary(ynn_unary_round, 1139, 1140);
  g->Binary(ynn_binary_max, 1140, 3328, 1142);
  g->Binary(ynn_binary_min, 1142, 3384, 1143);
  g->Binary(ynn_binary_multiply, 1143, 3405, 1144);
  g->Convert(3840, 1145);
  g->Binary(ynn_binary_multiply, 1145, 3841, 1146);
  g->Matmul(1135, 1146, 1148, false, true);
  g->Binary(ynn_binary_divide, 1148, 3405, 1149);
  g->Unary(ynn_unary_round, 1149, 1150);
  g->Binary(ynn_binary_max, 1150, 3328, 1151);
  g->Binary(ynn_binary_min, 1151, 3384, 1152);
  g->Binary(ynn_binary_multiply, 1152, 3405, 1153);
  g->Polynomial(1153, 3018, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 3018, 3019);
  g->Binary(ynn_binary_add, 3019, 2855, 3016);
  g->Binary(ynn_binary_multiply, 1153, 2853, 3017);
  g->Binary(ynn_binary_multiply, 3017, 3016, 1154);
  g->Binary(ynn_binary_multiply, 1144, 1154, 1155);
  g->Binary(ynn_binary_divide, 1155, 3451, 1156);
  g->Unary(ynn_unary_round, 1156, 1157);
  g->Binary(ynn_binary_max, 1157, 3328, 1159);
  g->Binary(ynn_binary_min, 1159, 3384, 1160);
  g->Binary(ynn_binary_multiply, 1160, 3451, 1161);
  g->Convert(3838, 1162);
  g->Binary(ynn_binary_multiply, 1162, 3839, 1163);
  g->Matmul(1161, 1163, 1164, false, true);
  g->Binary(ynn_binary_divide, 1164, 3337, 1165);
  g->Unary(ynn_unary_round, 1165, 1166);
  g->Binary(ynn_binary_max, 1166, 3328, 1167);
  g->Binary(ynn_binary_min, 1167, 3384, 1168);
  g->Binary(ynn_binary_multiply, 1168, 3337, 1170);
  g->Unary(ynn_unary_square, 1170, 1171);
  g->Reduce(ynn_reduce_sum, 1171, 3025, {2}, true);
  g->ShapeProduct(1171, 3024, {2});
  g->Binary(ynn_binary_divide, 3025, 3024, 1172);
  g->Binary(ynn_binary_add, 1172, 3400, 1173);
  g->Binary(ynn_binary_pow, 1173, 3424, 1174);
  g->Binary(ynn_binary_multiply, 1170, 1174, 1175);
  g->Convert(3849, 1176);
  g->Binary(ynn_binary_multiply, 1175, 1176, 1177);
  g->Binary(ynn_binary_add, 1122, 1177, 1178);
}

// Scope: "Layer9 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer9PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1022, 1179, {0,0,9,0}, {-1,-1,1,-1});
  g->Reshape(1179, 1181, {1,0,256});
  g->Binary(ynn_binary_add, 1181, 3877, 1182);
  g->Binary(ynn_binary_multiply, 1182, 3296, 1183);
  g->Binary(ynn_binary_divide, 1178, 3346, 1184);
  g->Unary(ynn_unary_round, 1184, 1185);
  g->Binary(ynn_binary_max, 1185, 3328, 1186);
  g->Binary(ynn_binary_min, 1186, 3384, 1187);
  g->Binary(ynn_binary_multiply, 1187, 3346, 1188);
  g->Convert(3844, 1189);
  g->Binary(ynn_binary_multiply, 1189, 3845, 1190);
  g->Matmul(1188, 1190, 1192, false, true);
  g->Binary(ynn_binary_divide, 1192, 3343, 1193);
  g->Unary(ynn_unary_round, 1193, 1194);
  g->Binary(ynn_binary_max, 1194, 3328, 1195);
  g->Binary(ynn_binary_min, 1195, 3384, 1196);
  g->Binary(ynn_binary_multiply, 1196, 3343, 1197);
  g->Polynomial(1197, 3028, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 3028, 3029);
  g->Binary(ynn_binary_add, 3029, 2855, 3026);
  g->Binary(ynn_binary_multiply, 1197, 2853, 3027);
  g->Binary(ynn_binary_multiply, 3027, 3026, 1198);
  g->Binary(ynn_binary_multiply, 1198, 1183, 1199);
  g->Binary(ynn_binary_divide, 1199, 3419, 1200);
  g->Unary(ynn_unary_round, 1200, 1201);
  g->Binary(ynn_binary_max, 1201, 3328, 1203);
  g->Binary(ynn_binary_min, 1203, 3384, 1204);
  g->Binary(ynn_binary_multiply, 1204, 3419, 1205);
  g->Convert(3846, 1206);
  g->Binary(ynn_binary_multiply, 1206, 3847, 1207);
  g->Matmul(1205, 1207, 1208, false, true);
  g->Binary(ynn_binary_divide, 1208, 3453, 1209);
  g->Unary(ynn_unary_round, 1209, 1210);
  g->Binary(ynn_binary_max, 1210, 3328, 1211);
  g->Binary(ynn_binary_min, 1211, 3384, 1212);
  g->Binary(ynn_binary_multiply, 1212, 3453, 1214);
  g->Unary(ynn_unary_square, 1214, 1215);
  g->Reduce(ynn_reduce_sum, 1215, 3031, {2}, true);
  g->ShapeProduct(1215, 3030, {2});
  g->Binary(ynn_binary_divide, 3031, 3030, 1216);
  g->Binary(ynn_binary_add, 1216, 3400, 1217);
  g->Binary(ynn_binary_pow, 1217, 3424, 1218);
  g->Binary(ynn_binary_multiply, 1214, 1218, 1219);
  g->Convert(3850, 1220);
  g->Binary(ynn_binary_multiply, 1219, 1220, 1221);
  g->Binary(ynn_binary_add, 1178, 1221, 1222);
  g->Convert(3837, 1223);
  g->Binary(ynn_binary_multiply, 1222, 1223, 1226);
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
  g->Binary(ynn_binary_divide, 1233, 3339, 1234);
  g->Unary(ynn_unary_round, 1234, 1235);
  g->Binary(ynn_binary_max, 1235, 3328, 1237);
  g->Binary(ynn_binary_min, 1237, 3384, 1238);
  g->Binary(ynn_binary_multiply, 1238, 3339, 1239);
  g->Convert(3561, 1240);
  g->Binary(ynn_binary_multiply, 1240, 3562, 1241);
  g->Matmul(1239, 1241, 1242, false, true);
  g->Binary(ynn_binary_divide, 1242, 3301, 1243);
  g->Unary(ynn_unary_round, 1243, 1244);
  g->Binary(ynn_binary_max, 1244, 3328, 1245);
  g->Binary(ynn_binary_min, 1245, 3384, 1246);
  g->Binary(ynn_binary_multiply, 1246, 3301, 1248);
  g->Reshape(1248, 1249, {1,0,1,256});
  g->Transpose(1249, 1250, {0,2,1,3});
  g->Unary(ynn_unary_square, 1250, 1251);
  g->Reduce(ynn_reduce_sum, 1251, 3037, {3}, true);
  g->ShapeProduct(1251, 3036, {3});
  g->Binary(ynn_binary_divide, 3037, 3036, 1252);
  g->Binary(ynn_binary_add, 1252, 3400, 1253);
  g->Binary(ynn_binary_pow, 1253, 3424, 1254);
  g->Binary(ynn_binary_multiply, 1250, 1254, 1255);
  g->Convert(3560, 1256);
  g->Binary(ynn_binary_multiply, 1255, 1256, 1257);
  g->Slice(1257, 1259, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1257, 1260, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1260, 1261);
  g->Concat({1261,1259}, 1262, 3);
  g->Binary(ynn_binary_multiply, 1257, 2025, 1263);
  g->Binary(ynn_binary_multiply, 1262, 2249, 1264);
  g->Binary(ynn_binary_add, 1263, 1264, 1265);
  g->Convert(3568, 1267);
  g->Binary(ynn_binary_multiply, 1267, 3569, 1268);
  g->Matmul(1239, 1268, 1269, false, true);
  g->Binary(ynn_binary_divide, 1269, 3301, 1270);
  g->Unary(ynn_unary_round, 1270, 1271);
  g->Binary(ynn_binary_max, 1271, 3328, 1272);
  g->Binary(ynn_binary_min, 1272, 3384, 1273);
  g->Binary(ynn_binary_multiply, 1273, 3301, 1274);
  g->Reshape(1274, 1276, {1,0,1,256});
  g->Transpose(1276, 1277, {0,2,1,3});
  g->Unary(ynn_unary_square, 1277, 1278);
  g->Reduce(ynn_reduce_sum, 1278, 3039, {3}, true);
  g->ShapeProduct(1278, 3038, {3});
  g->Binary(ynn_binary_divide, 3039, 3038, 1279);
  g->Binary(ynn_binary_add, 1279, 3400, 1280);
  g->Binary(ynn_binary_pow, 1280, 3424, 1281);
  g->Binary(ynn_binary_multiply, 1277, 1281, 1282);
}

// Scope: "Layer10 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(1265, 1283, 0.005712664220482111, 0);
  g->Append(3264, 1283, 3881, 2, s2, s1);
  g->View(3881, 3911, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(3911, 1285, 0.005712664220482111, 0);
  g->Quantize(1282, 1286, 0.047244105488061905, 0);
  g->Append(3279, 1286, 3896, 2, s2, s1);
  g->View(3896, 3925, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(3925, 1287, 0.047244105488061905, 0);
}

// Scope: "Layer10 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Convert(3566, 1289);
  g->Binary(ynn_binary_multiply, 1289, 3567, 1290);
  g->Matmul(1239, 1290, 1291, false, true);
  g->Binary(ynn_binary_divide, 1291, 3429, 1292);
  g->Unary(ynn_unary_round, 1292, 1293);
  g->Binary(ynn_binary_max, 1293, 3328, 1294);
  g->Binary(ynn_binary_min, 1294, 3384, 1295);
  g->Binary(ynn_binary_multiply, 1295, 3429, 1296);
  g->SplitDim(1296, 1297, 2, {8,256});
  g->Transpose(1297, 1298, {0,2,1,3});
  g->Unary(ynn_unary_square, 1298, 1300);
  g->Reduce(ynn_reduce_sum, 1300, 3041, {3}, true);
  g->ShapeProduct(1300, 3040, {3});
  g->Binary(ynn_binary_divide, 3041, 3040, 1301);
  g->Binary(ynn_binary_add, 1301, 3400, 1302);
  g->Binary(ynn_binary_pow, 1302, 3424, 1303);
  g->Binary(ynn_binary_multiply, 1298, 1303, 1304);
  g->Convert(3565, 1305);
  g->Binary(ynn_binary_multiply, 1304, 1305, 1306);
  g->Slice(1306, 1307, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1306, 1308, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1308, 1309);
  g->Concat({1309,1307}, 1311, 3);
  g->Binary(ynn_binary_multiply, 1306, 2025, 1312);
  g->Binary(ynn_binary_multiply, 1311, 2249, 1313);
  g->Binary(ynn_binary_add, 1312, 1313, 1314);
}

// Scope: "Layer10 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(1314, 1285, 1315, false, true);
  g->Mask(1315, 3480, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 3480, 3045, {-1}, true);
  g->Binary(ynn_binary_subtract, 3480, 3045, 3042);
  g->Unary(ynn_unary_exp, 3042, 3043);
  g->Reduce(ynn_reduce_sum, 3043, 3046, {-1}, true);
  g->Binary(ynn_binary_divide, 2855, 3046, 3044);
  g->Binary(ynn_binary_multiply, 3043, 3044, 1316);
  g->Matmul(1316, 1287, 1317, false, false);
}

// Scope: "Layer10 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1317, 1318, {0,2,1,3});
  g->FuseDims(1318, 1319, 2, 2);
  g->Binary(ynn_binary_divide, 1319, 3385, 1322);
  g->Unary(ynn_unary_round, 1322, 1323);
  g->Binary(ynn_binary_max, 1323, 3328, 1324);
  g->Binary(ynn_binary_min, 1324, 3384, 1325);
  g->Binary(ynn_binary_multiply, 1325, 3385, 1326);
  g->Convert(3563, 1327);
  g->Binary(ynn_binary_multiply, 1327, 3564, 1328);
  g->Matmul(1326, 1328, 1329, false, true);
  g->Binary(ynn_binary_divide, 1329, 3382, 1330);
  g->Unary(ynn_unary_round, 1330, 1331);
  g->Binary(ynn_binary_max, 1331, 3328, 1333);
  g->Binary(ynn_binary_min, 1333, 3384, 1334);
  g->Binary(ynn_binary_multiply, 1334, 3382, 1335);
}

// Scope: "Layer10 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1226, 1227);
  g->Reduce(ynn_reduce_sum, 1227, 3035, {2}, true);
  g->ShapeProduct(1227, 3034, {2});
  g->Binary(ynn_binary_divide, 3035, 3034, 1228);
  g->Binary(ynn_binary_add, 1228, 3400, 1229);
  g->Binary(ynn_binary_pow, 1229, 3424, 1230);
  g->Binary(ynn_binary_multiply, 1226, 1230, 1231);
  g->Convert(3544, 1232);
  g->Binary(ynn_binary_multiply, 1231, 1232, 1233);
  BuildLayer10AttentionKvProjection(ctx);
  BuildLayer10AttentionCacheUpdate(ctx);
  BuildLayer10AttentionQueryProjection(ctx);
  BuildLayer10AttentionSdpa(ctx);
  BuildLayer10AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1335, 1336);
  g->Reduce(ynn_reduce_sum, 1336, 3050, {2}, true);
  g->ShapeProduct(1336, 3049, {2});
  g->Binary(ynn_binary_divide, 3050, 3049, 1337);
  g->Binary(ynn_binary_add, 1337, 3400, 1338);
  g->Binary(ynn_binary_pow, 1338, 3424, 1339);
  g->Binary(ynn_binary_multiply, 1335, 1339, 1340);
  g->Convert(3556, 1341);
  g->Binary(ynn_binary_multiply, 1340, 1341, 1342);
  g->Binary(ynn_binary_add, 1226, 1342, 1344);
}

// Scope: "Layer10 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1344, 1345);
  g->Reduce(ynn_reduce_sum, 1345, 3052, {2}, true);
  g->ShapeProduct(1345, 3051, {2});
  g->Binary(ynn_binary_divide, 3052, 3051, 1346);
  g->Binary(ynn_binary_add, 1346, 3400, 1347);
  g->Binary(ynn_binary_pow, 1347, 3424, 1348);
  g->Binary(ynn_binary_multiply, 1344, 1348, 1349);
  g->Convert(3559, 1350);
  g->Binary(ynn_binary_multiply, 1349, 1350, 1351);
  g->Binary(ynn_binary_divide, 1351, 3423, 1352);
  g->Unary(ynn_unary_round, 1352, 1353);
  g->Binary(ynn_binary_max, 1353, 3328, 1355);
  g->Binary(ynn_binary_min, 1355, 3384, 1356);
  g->Binary(ynn_binary_multiply, 1356, 3423, 1357);
  g->Convert(3550, 1358);
  g->Binary(ynn_binary_multiply, 1358, 3551, 1359);
  g->Matmul(1357, 1359, 1360, false, true);
  g->Binary(ynn_binary_divide, 1360, 3319, 1361);
  g->Unary(ynn_unary_round, 1361, 1362);
  g->Binary(ynn_binary_max, 1362, 3328, 1363);
  g->Binary(ynn_binary_min, 1363, 3384, 1364);
  g->Binary(ynn_binary_multiply, 1364, 3319, 1366);
  g->Convert(3548, 1367);
  g->Binary(ynn_binary_multiply, 1367, 3549, 1368);
  g->Matmul(1357, 1368, 1369, false, true);
  g->Binary(ynn_binary_divide, 1369, 3319, 1370);
  g->Unary(ynn_unary_round, 1370, 1372);
  g->Binary(ynn_binary_max, 1372, 3328, 1373);
  g->Binary(ynn_binary_min, 1373, 3384, 1374);
  g->Binary(ynn_binary_multiply, 1374, 3319, 1375);
  g->Polynomial(1375, 3055, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 3055, 3056);
  g->Binary(ynn_binary_add, 3056, 2855, 3053);
  g->Binary(ynn_binary_multiply, 1375, 2853, 3054);
  g->Binary(ynn_binary_multiply, 3054, 3053, 1376);
  g->Binary(ynn_binary_multiply, 1366, 1376, 1377);
  g->Binary(ynn_binary_divide, 1377, 3470, 1378);
  g->Unary(ynn_unary_round, 1378, 1379);
  g->Binary(ynn_binary_max, 1379, 3328, 1380);
  g->Binary(ynn_binary_min, 1380, 3384, 1381);
  g->Binary(ynn_binary_multiply, 1381, 3470, 1383);
  g->Convert(3546, 1384);
  g->Binary(ynn_binary_multiply, 1384, 3547, 1385);
  g->Matmul(1383, 1385, 1386, false, true);
  g->Binary(ynn_binary_divide, 1386, 3357, 1387);
  g->Unary(ynn_unary_round, 1387, 1388);
  g->Binary(ynn_binary_max, 1388, 3328, 1389);
  g->Binary(ynn_binary_min, 1389, 3384, 1390);
  g->Binary(ynn_binary_multiply, 1390, 3357, 1391);
  g->Unary(ynn_unary_square, 1391, 1392);
  g->Reduce(ynn_reduce_sum, 1392, 3058, {2}, true);
  g->ShapeProduct(1392, 3057, {2});
  g->Binary(ynn_binary_divide, 3058, 3057, 1394);
  g->Binary(ynn_binary_add, 1394, 3400, 1395);
  g->Binary(ynn_binary_pow, 1395, 3424, 1396);
  g->Binary(ynn_binary_multiply, 1391, 1396, 1397);
  g->Convert(3557, 1398);
  g->Binary(ynn_binary_multiply, 1397, 1398, 1399);
  g->Binary(ynn_binary_add, 1344, 1399, 1400);
}

// Scope: "Layer10 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer10PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1022, 1401, {0,0,10,0}, {-1,-1,1,-1});
  g->Reshape(1401, 1402, {1,0,256});
  g->Binary(ynn_binary_add, 1402, 3866, 1403);
  g->Binary(ynn_binary_multiply, 1403, 3296, 1405);
  g->Binary(ynn_binary_divide, 1400, 3322, 1406);
  g->Unary(ynn_unary_round, 1406, 1407);
  g->Binary(ynn_binary_max, 1407, 3328, 1408);
  g->Binary(ynn_binary_min, 1408, 3384, 1409);
  g->Binary(ynn_binary_multiply, 1409, 3322, 1410);
  g->Convert(3552, 1411);
  g->Binary(ynn_binary_multiply, 1411, 3553, 1412);
  g->Matmul(1410, 1412, 1413, false, true);
  g->Binary(ynn_binary_divide, 1413, 3466, 1414);
  g->Unary(ynn_unary_round, 1414, 1416);
  g->Binary(ynn_binary_max, 1416, 3328, 1417);
  g->Binary(ynn_binary_min, 1417, 3384, 1418);
  g->Binary(ynn_binary_multiply, 1418, 3466, 1419);
  g->Polynomial(1419, 3061, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 3061, 3062);
  g->Binary(ynn_binary_add, 3062, 2855, 3059);
  g->Binary(ynn_binary_multiply, 1419, 2853, 3060);
  g->Binary(ynn_binary_multiply, 3060, 3059, 1420);
  g->Binary(ynn_binary_multiply, 1420, 1405, 1421);
  g->Binary(ynn_binary_divide, 1421, 3326, 1422);
  g->Unary(ynn_unary_round, 1422, 1423);
  g->Binary(ynn_binary_max, 1423, 3328, 1424);
  g->Binary(ynn_binary_min, 1424, 3384, 1425);
  g->Binary(ynn_binary_multiply, 1425, 3326, 1428);
  g->Convert(3554, 1429);
  g->Binary(ynn_binary_multiply, 1429, 3555, 1430);
  g->Matmul(1428, 1430, 1431, false, true);
  g->Binary(ynn_binary_divide, 1431, 3439, 1432);
  g->Unary(ynn_unary_round, 1432, 1433);
  g->Binary(ynn_binary_max, 1433, 3328, 1434);
  g->Binary(ynn_binary_min, 1434, 3384, 1435);
  g->Binary(ynn_binary_multiply, 1435, 3439, 1436);
  g->Unary(ynn_unary_square, 1436, 1437);
  g->Reduce(ynn_reduce_sum, 1437, 3066, {2}, true);
  g->ShapeProduct(1437, 3065, {2});
  g->Binary(ynn_binary_divide, 3066, 3065, 1439);
  g->Binary(ynn_binary_add, 1439, 3400, 1440);
  g->Binary(ynn_binary_pow, 1440, 3424, 1441);
  g->Binary(ynn_binary_multiply, 1436, 1441, 1442);
  g->Convert(3558, 1443);
  g->Binary(ynn_binary_multiply, 1442, 1443, 1444);
  g->Binary(ynn_binary_add, 1400, 1444, 1445);
  g->Convert(3545, 1446);
  g->Binary(ynn_binary_multiply, 1445, 1446, 1447);
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
  g->Binary(ynn_binary_divide, 1455, 3455, 1456);
  g->Unary(ynn_unary_round, 1456, 1457);
  g->Binary(ynn_binary_max, 1457, 3328, 1458);
  g->Binary(ynn_binary_min, 1458, 3384, 1459);
  g->Binary(ynn_binary_multiply, 1459, 3455, 1461);
  g->Convert(3587, 1462);
  g->Binary(ynn_binary_multiply, 1462, 3588, 1463);
  g->Matmul(1461, 1463, 1464, false, true);
  g->Binary(ynn_binary_divide, 1464, 3445, 1465);
  g->Unary(ynn_unary_round, 1465, 1466);
  g->Binary(ynn_binary_max, 1466, 3328, 1467);
  g->Binary(ynn_binary_min, 1467, 3384, 1468);
  g->Binary(ynn_binary_multiply, 1468, 3445, 1469);
  g->Reshape(1469, 1470, {1,0,1,256});
  g->Transpose(1470, 1472, {0,2,1,3});
  g->Unary(ynn_unary_square, 1472, 1473);
  g->Reduce(ynn_reduce_sum, 1473, 3070, {3}, true);
  g->ShapeProduct(1473, 3069, {3});
  g->Binary(ynn_binary_divide, 3070, 3069, 1474);
  g->Binary(ynn_binary_add, 1474, 3400, 1475);
  g->Binary(ynn_binary_pow, 1475, 3424, 1476);
  g->Binary(ynn_binary_multiply, 1472, 1476, 1477);
  g->Convert(3586, 1478);
  g->Binary(ynn_binary_multiply, 1477, 1478, 1479);
  g->Slice(1479, 1480, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1479, 1481, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1481, 1483);
  g->Concat({1483,1480}, 1484, 3);
  g->Binary(ynn_binary_multiply, 1479, 2025, 1485);
  g->Binary(ynn_binary_multiply, 1484, 2249, 1486);
  g->Binary(ynn_binary_add, 1485, 1486, 1487);
  g->Convert(3594, 1489);
  g->Binary(ynn_binary_multiply, 1489, 3595, 1490);
  g->Matmul(1461, 1490, 1491, false, true);
  g->Binary(ynn_binary_divide, 1491, 3445, 1492);
  g->Unary(ynn_unary_round, 1492, 1493);
  g->Binary(ynn_binary_max, 1493, 3328, 1494);
  g->Binary(ynn_binary_min, 1494, 3384, 1495);
  g->Binary(ynn_binary_multiply, 1495, 3445, 1496);
  g->Reshape(1496, 1497, {1,0,1,256});
  g->Transpose(1497, 1498, {0,2,1,3});
  g->Unary(ynn_unary_square, 1498, 1500);
  g->Reduce(ynn_reduce_sum, 1500, 3072, {3}, true);
  g->ShapeProduct(1500, 3071, {3});
  g->Binary(ynn_binary_divide, 3072, 3071, 1501);
  g->Binary(ynn_binary_add, 1501, 3400, 1502);
  g->Binary(ynn_binary_pow, 1502, 3424, 1503);
  g->Binary(ynn_binary_multiply, 1498, 1503, 1504);
}

// Scope: "Layer11 / Attention / CacheUpdate"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11AttentionCacheUpdate(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s1 = ctx.s1;
  const slinky::expr& s2 = ctx.s2;
  g->Quantize(1487, 1505, 0.005907459184527397, 0);
  g->Append(3265, 1505, 3882, 2, s2, s1);
  g->View(3882, 3912, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(3912, 1506, 0.005907459184527397, 0);
  g->Quantize(1504, 1507, 0.047244105488061905, 0);
  g->Append(3280, 1507, 3897, 2, s2, s1);
  g->View(3897, 3926, 2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), (slinky::expr(int64_t{0}) + (slinky::expr(int64_t{1}) * s1) + (slinky::expr(int64_t{1}) * s2)));
  g->Dequantize(3926, 1509, 0.047244105488061905, 0);
}

// Scope: "Layer11 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Convert(3592, 1510);
  g->Binary(ynn_binary_multiply, 1510, 3593, 1511);
  g->Matmul(1461, 1511, 1513, false, true);
  g->Binary(ynn_binary_divide, 1513, 3464, 1514);
  g->Unary(ynn_unary_round, 1514, 1515);
  g->Binary(ynn_binary_max, 1515, 3328, 1516);
  g->Binary(ynn_binary_min, 1516, 3384, 1517);
  g->Binary(ynn_binary_multiply, 1517, 3464, 1518);
  g->SplitDim(1518, 1519, 2, {8,256});
  g->Transpose(1519, 1520, {0,2,1,3});
  g->Unary(ynn_unary_square, 1520, 1521);
  g->Reduce(ynn_reduce_sum, 1521, 3074, {3}, true);
  g->ShapeProduct(1521, 3073, {3});
  g->Binary(ynn_binary_divide, 3074, 3073, 1522);
  g->Binary(ynn_binary_add, 1522, 3400, 1525);
  g->Binary(ynn_binary_pow, 1525, 3424, 1526);
  g->Binary(ynn_binary_multiply, 1520, 1526, 1527);
  g->Convert(3591, 1528);
  g->Binary(ynn_binary_multiply, 1527, 1528, 1529);
  g->Slice(1529, 1530, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(1529, 1531, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 1531, 1532);
  g->Concat({1532,1530}, 1533, 3);
  g->Binary(ynn_binary_multiply, 1529, 2025, 1534);
  g->Binary(ynn_binary_multiply, 1533, 2249, 1536);
  g->Binary(ynn_binary_add, 1534, 1536, 1537);
}

// Scope: "Layer11 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(1537, 1506, 1538, false, true);
  g->Mask(1538, 3481, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 3481, 3078, {-1}, true);
  g->Binary(ynn_binary_subtract, 3481, 3078, 3075);
  g->Unary(ynn_unary_exp, 3075, 3076);
  g->Reduce(ynn_reduce_sum, 3076, 3079, {-1}, true);
  g->Binary(ynn_binary_divide, 2855, 3079, 3077);
  g->Binary(ynn_binary_multiply, 3076, 3077, 1539);
  g->Matmul(1539, 1509, 1540, false, false);
}

// Scope: "Layer11 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(1540, 1541, {0,2,1,3});
  g->FuseDims(1541, 1542, 2, 2);
  g->Binary(ynn_binary_divide, 1542, 3363, 1543);
  g->Unary(ynn_unary_round, 1543, 1544);
  g->Binary(ynn_binary_max, 1544, 3328, 1546);
  g->Binary(ynn_binary_min, 1546, 3384, 1547);
  g->Binary(ynn_binary_multiply, 1547, 3363, 1548);
  g->Convert(3589, 1549);
  g->Binary(ynn_binary_multiply, 1549, 3590, 1550);
  g->Matmul(1548, 1550, 1551, false, true);
  g->Binary(ynn_binary_divide, 1551, 3391, 1552);
  g->Unary(ynn_unary_round, 1552, 1553);
  g->Binary(ynn_binary_max, 1553, 3328, 1554);
  g->Binary(ynn_binary_min, 1554, 3384, 1555);
  g->Binary(ynn_binary_multiply, 1555, 3391, 1557);
}

// Scope: "Layer11 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1447, 1448);
  g->Reduce(ynn_reduce_sum, 1448, 3068, {2}, true);
  g->ShapeProduct(1448, 3067, {2});
  g->Binary(ynn_binary_divide, 3068, 3067, 1450);
  g->Binary(ynn_binary_add, 1450, 3400, 1451);
  g->Binary(ynn_binary_pow, 1451, 3424, 1452);
  g->Binary(ynn_binary_multiply, 1447, 1452, 1453);
  g->Convert(3570, 1454);
  g->Binary(ynn_binary_multiply, 1453, 1454, 1455);
  BuildLayer11AttentionKvProjection(ctx);
  BuildLayer11AttentionCacheUpdate(ctx);
  BuildLayer11AttentionQueryProjection(ctx);
  BuildLayer11AttentionSdpa(ctx);
  BuildLayer11AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 1557, 1558);
  g->Reduce(ynn_reduce_sum, 1558, 3081, {2}, true);
  g->ShapeProduct(1558, 3080, {2});
  g->Binary(ynn_binary_divide, 3081, 3080, 1559);
  g->Binary(ynn_binary_add, 1559, 3400, 1560);
  g->Binary(ynn_binary_pow, 1560, 3424, 1561);
  g->Binary(ynn_binary_multiply, 1557, 1561, 1562);
  g->Convert(3582, 1563);
  g->Binary(ynn_binary_multiply, 1562, 1563, 1564);
  g->Binary(ynn_binary_add, 1447, 1564, 1565);
}

// Scope: "Layer11 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 1565, 1566);
  g->Reduce(ynn_reduce_sum, 1566, 3083, {2}, true);
  g->ShapeProduct(1566, 3082, {2});
  g->Binary(ynn_binary_divide, 3083, 3082, 1568);
  g->Binary(ynn_binary_add, 1568, 3400, 1569);
  g->Binary(ynn_binary_pow, 1569, 3424, 1570);
  g->Binary(ynn_binary_multiply, 1565, 1570, 1571);
  g->Convert(3585, 1572);
  g->Binary(ynn_binary_multiply, 1571, 1572, 1573);
  g->Binary(ynn_binary_divide, 1573, 3401, 1574);
  g->Unary(ynn_unary_round, 1574, 1575);
  g->Binary(ynn_binary_max, 1575, 3328, 1576);
  g->Binary(ynn_binary_min, 1576, 3384, 1577);
  g->Binary(ynn_binary_multiply, 1577, 3401, 1579);
  g->Convert(3576, 1580);
  g->Binary(ynn_binary_multiply, 1580, 3577, 1581);
  g->Matmul(1579, 1581, 1582, false, true);
  g->Binary(ynn_binary_divide, 1582, 3452, 1583);
  g->Unary(ynn_unary_round, 1583, 1584);
  g->Binary(ynn_binary_max, 1584, 3328, 1585);
  g->Binary(ynn_binary_min, 1585, 3384, 1586);
  g->Binary(ynn_binary_multiply, 1586, 3452, 1587);
  g->Convert(3574, 1589);
  g->Binary(ynn_binary_multiply, 1589, 3575, 1590);
  g->Matmul(1579, 1590, 1591, false, true);
  g->Binary(ynn_binary_divide, 1591, 3452, 1592);
  g->Unary(ynn_unary_round, 1592, 1593);
  g->Binary(ynn_binary_max, 1593, 3328, 1594);
  g->Binary(ynn_binary_min, 1594, 3384, 1596);
  g->Binary(ynn_binary_multiply, 1596, 3452, 1597);
  g->Polynomial(1597, 3086, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 3086, 3087);
  g->Binary(ynn_binary_add, 3087, 2855, 3084);
  g->Binary(ynn_binary_multiply, 1597, 2853, 3085);
  g->Binary(ynn_binary_multiply, 3085, 3084, 1598);
  g->Binary(ynn_binary_multiply, 1587, 1598, 1599);
  g->Binary(ynn_binary_divide, 1599, 3425, 1600);
  g->Unary(ynn_unary_round, 1600, 1601);
  g->Binary(ynn_binary_max, 1601, 3328, 1602);
  g->Binary(ynn_binary_min, 1602, 3384, 1603);
  g->Binary(ynn_binary_multiply, 1603, 3425, 1604);
  g->Convert(3572, 1605);
  g->Binary(ynn_binary_multiply, 1605, 3573, 1607);
  g->Matmul(1604, 1607, 1608, false, true);
  g->Binary(ynn_binary_divide, 1608, 3374, 1609);
  g->Unary(ynn_unary_round, 1609, 1610);
  g->Binary(ynn_binary_max, 1610, 3328, 1611);
  g->Binary(ynn_binary_min, 1611, 3384, 1612);
  g->Binary(ynn_binary_multiply, 1612, 3374, 1613);
  g->Unary(ynn_unary_square, 1613, 1614);
  g->Reduce(ynn_reduce_sum, 1614, 3089, {2}, true);
  g->ShapeProduct(1614, 3088, {2});
  g->Binary(ynn_binary_divide, 3089, 3088, 1615);
  g->Binary(ynn_binary_add, 1615, 3400, 1616);
  g->Binary(ynn_binary_pow, 1616, 3424, 1618);
  g->Binary(ynn_binary_multiply, 1613, 1618, 1619);
  g->Convert(3583, 1620);
  g->Binary(ynn_binary_multiply, 1619, 1620, 1621);
  g->Binary(ynn_binary_add, 1565, 1621, 1622);
}

// Scope: "Layer11 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1022, 1623, {0,0,11,0}, {-1,-1,1,-1});
  g->Reshape(1623, 1624, {1,0,256});
  g->Binary(ynn_binary_add, 1624, 3867, 1625);
  g->Binary(ynn_binary_multiply, 1625, 3296, 1626);
  g->Binary(ynn_binary_divide, 1622, 3341, 1627);
  g->Unary(ynn_unary_round, 1627, 1630);
  g->Binary(ynn_binary_max, 1630, 3328, 1631);
  g->Binary(ynn_binary_min, 1631, 3384, 1632);
  g->Binary(ynn_binary_multiply, 1632, 3341, 1633);
  g->Convert(3578, 1634);
  g->Binary(ynn_binary_multiply, 1634, 3579, 1635);
  g->Matmul(1633, 1635, 1636, false, true);
  g->Binary(ynn_binary_divide, 1636, 3449, 1637);
  g->Unary(ynn_unary_round, 1637, 1638);
  g->Binary(ynn_binary_max, 1638, 3328, 1639);
  g->Binary(ynn_binary_min, 1639, 3384, 1641);
  g->Binary(ynn_binary_multiply, 1641, 3449, 1642);
  g->Polynomial(1642, 3092, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 3092, 3093);
  g->Binary(ynn_binary_add, 3093, 2855, 3090);
  g->Binary(ynn_binary_multiply, 1642, 2853, 3091);
  g->Binary(ynn_binary_multiply, 3091, 3090, 1643);
  g->Binary(ynn_binary_multiply, 1643, 1626, 1644);
  g->Binary(ynn_binary_divide, 1644, 3387, 1645);
  g->Unary(ynn_unary_round, 1645, 1646);
  g->Binary(ynn_binary_max, 1646, 3328, 1647);
  g->Binary(ynn_binary_min, 1647, 3384, 1648);
  g->Binary(ynn_binary_multiply, 1648, 3387, 1649);
  g->Convert(3580, 1650);
  g->Binary(ynn_binary_multiply, 1650, 3581, 1652);
  g->Matmul(1649, 1652, 1653, false, true);
  g->Binary(ynn_binary_divide, 1653, 3435, 1654);
  g->Unary(ynn_unary_round, 1654, 1655);
  g->Binary(ynn_binary_max, 1655, 3328, 1656);
  g->Binary(ynn_binary_min, 1656, 3384, 1657);
  g->Binary(ynn_binary_multiply, 1657, 3435, 1658);
  g->Unary(ynn_unary_square, 1658, 1659);
  g->Reduce(ynn_reduce_sum, 1659, 3097, {2}, true);
  g->ShapeProduct(1659, 3096, {2});
  g->Binary(ynn_binary_divide, 3097, 3096, 1660);
  g->Binary(ynn_binary_add, 1660, 3400, 1661);
  g->Binary(ynn_binary_pow, 1661, 3424, 1663);
  g->Binary(ynn_binary_multiply, 1658, 1663, 1664);
  g->Convert(3584, 1665);
  g->Binary(ynn_binary_multiply, 1664, 1665, 1666);
  g->Binary(ynn_binary_add, 1622, 1666, 1667);
  g->Convert(3571, 1668);
  g->Binary(ynn_binary_multiply, 1667, 1668, 1669);
}

// Scope: "Layer11"
LAB_YNN_BUILDER_NOINLINE void BuildLayer11(Context& ctx) {
  BuildLayer11Attention(ctx);
  BuildLayer11Mlp(ctx);
  BuildLayer11PerLayerEmbedding(ctx);
}

}  // namespace BuildGemma4PrefillSource
