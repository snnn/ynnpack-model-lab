// Generated YNNPACK builder; do not edit.
#include "gemma4_decode_builder.h"

namespace BuildGemma4DecodeSource {

// Scope: "Layer15 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Binary(ynn_binary_divide, 2351, 7217, 2352);
  g->Unary(ynn_unary_round, 2352, 2353);
  g->Binary(ynn_binary_max, 2353, 7225, 2356);
  g->Binary(ynn_binary_min, 2356, 7340, 2357);
  g->Binary(ynn_binary_multiply, 2357, 7217, 2358);
  g->Convert(7797, 2359);
  g->Binary(ynn_binary_multiply, 2359, 7798, 2360);
  g->Matmul(2358, 2360, 2361, false, true);
  g->Binary(ynn_binary_divide, 2361, 7175, 2362);
  g->Unary(ynn_unary_round, 2362, 2363);
  g->Binary(ynn_binary_max, 2363, 7225, 2364);
  g->Binary(ynn_binary_min, 2364, 7340, 2365);
  g->Binary(ynn_binary_multiply, 2365, 7175, 2367);
  g->SplitDim(2367, 2368, 2, {8,256});
  g->FuseDims(2368, 2370, 1, 2);
  g->SplitDim(2370, 2369, 1, {8,1});
  g->Unary(ynn_unary_square, 2369, 2371);
  g->Reduce(ynn_reduce_sum, 2371, 6520, {3}, true);
  g->ShapeProduct(2371, 6519, {3});
  g->Binary(ynn_binary_divide, 6520, 6519, 2372);
  g->Binary(ynn_binary_add, 2372, 7373, 2373);
  g->Binary(ynn_binary_pow, 2373, 7428, 2374);
  g->Binary(ynn_binary_multiply, 2369, 2374, 2375);
  g->Convert(7796, 2376);
  g->Binary(ynn_binary_multiply, 2375, 2376, 2377);
  g->Slice(2377, 2379, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2377, 2380, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2380, 2381);
  g->Concat({2381,2379}, 2382, 3);
  g->Binary(ynn_binary_multiply, 2377, 2044, 2383);
  g->Binary(ynn_binary_multiply, 2382, 3111, 2384);
  g->Binary(ynn_binary_add, 2383, 2384, 2385);
}

// Scope: "Layer15 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(2385, 1963, 2386, false, true);
  g->Mask(2386, 7568, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 7568, 6524, {-1}, true);
  g->Binary(ynn_binary_subtract, 7568, 6524, 6521);
  g->Unary(ynn_unary_exp, 6521, 6522);
  g->Reduce(ynn_reduce_sum, 6522, 6525, {-1}, true);
  g->Binary(ynn_binary_divide, 6183, 6525, 6523);
  g->Binary(ynn_binary_multiply, 6522, 6523, 2387);
  g->Matmul(2387, 1965, 2388, false, false);
}

// Scope: "Layer15 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(2388, 2390, 1, 2);
  g->SplitDim(2390, 2389, 1, {1,8});
  g->FuseDims(2389, 2391, 2, 2);
  g->Binary(ynn_binary_divide, 2391, 7488, 2392);
  g->Unary(ynn_unary_round, 2392, 2393);
  g->Binary(ynn_binary_max, 2393, 7225, 2394);
  g->Binary(ynn_binary_min, 2394, 7340, 2395);
  g->Binary(ynn_binary_multiply, 2395, 7488, 2396);
  g->Convert(7794, 2397);
  g->Binary(ynn_binary_multiply, 2397, 7795, 2398);
  g->Matmul(2396, 2398, 2400, false, true);
  g->Binary(ynn_binary_divide, 2400, 7551, 2401);
  g->Unary(ynn_unary_round, 2401, 2402);
  g->Binary(ynn_binary_max, 2402, 7225, 2403);
  g->Binary(ynn_binary_min, 2403, 7340, 2404);
  g->Binary(ynn_binary_multiply, 2404, 7551, 2405);
}

// Scope: "Layer15 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2344, 2345);
  g->Reduce(ynn_reduce_sum, 2345, 6518, {2}, true);
  g->ShapeProduct(2345, 6517, {2});
  g->Binary(ynn_binary_divide, 6518, 6517, 2346);
  g->Binary(ynn_binary_add, 2346, 7373, 2347);
  g->Binary(ynn_binary_pow, 2347, 7428, 2348);
  g->Binary(ynn_binary_multiply, 2344, 2348, 2349);
  g->Convert(7778, 2350);
  g->Binary(ynn_binary_multiply, 2349, 2350, 2351);
  BuildLayer15AttentionQueryProjection(ctx);
  BuildLayer15AttentionSdpa(ctx);
  BuildLayer15AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2405, 2406);
  g->Reduce(ynn_reduce_sum, 2406, 6532, {2}, true);
  g->ShapeProduct(2406, 6531, {2});
  g->Binary(ynn_binary_divide, 6532, 6531, 2407);
  g->Binary(ynn_binary_add, 2407, 7373, 2408);
  g->Binary(ynn_binary_pow, 2408, 7428, 2409);
  g->Binary(ynn_binary_multiply, 2405, 2409, 2411);
  g->Convert(7790, 2412);
  g->Binary(ynn_binary_multiply, 2411, 2412, 2413);
  g->Binary(ynn_binary_add, 2344, 2413, 2414);
}

// Scope: "Layer15 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2414, 2415);
  g->Reduce(ynn_reduce_sum, 2415, 6534, {2}, true);
  g->ShapeProduct(2415, 6533, {2});
  g->Binary(ynn_binary_divide, 6534, 6533, 2416);
  g->Binary(ynn_binary_add, 2416, 7373, 2417);
  g->Binary(ynn_binary_pow, 2417, 7428, 2418);
  g->Binary(ynn_binary_multiply, 2414, 2418, 2419);
  g->Convert(7793, 2420);
  g->Binary(ynn_binary_multiply, 2419, 2420, 2423);
  g->Binary(ynn_binary_divide, 2423, 7346, 2424);
  g->Unary(ynn_unary_round, 2424, 2425);
  g->Binary(ynn_binary_max, 2425, 7225, 2426);
  g->Binary(ynn_binary_min, 2426, 7340, 2427);
  g->Binary(ynn_binary_multiply, 2427, 7346, 2428);
  g->Convert(7784, 2429);
  g->Binary(ynn_binary_multiply, 2429, 7785, 2430);
  g->Matmul(2428, 2430, 2431, false, true);
  g->Binary(ynn_binary_divide, 2431, 7501, 2432);
  g->Unary(ynn_unary_round, 2432, 2434);
  g->Binary(ynn_binary_max, 2434, 7225, 2435);
  g->Binary(ynn_binary_min, 2435, 7340, 2436);
  g->Binary(ynn_binary_multiply, 2436, 7501, 2437);
  g->Convert(7782, 2438);
  g->Binary(ynn_binary_multiply, 2438, 7783, 2440);
  g->Matmul(2428, 2440, 2441, false, true);
  g->Binary(ynn_binary_divide, 2441, 7501, 2442);
  g->Unary(ynn_unary_round, 2442, 2443);
  g->Binary(ynn_binary_max, 2443, 7225, 2444);
  g->Binary(ynn_binary_min, 2444, 7340, 2445);
  g->Binary(ynn_binary_multiply, 2445, 7501, 2446);
  g->Polynomial(2446, 6537, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6537, 6538);
  g->Binary(ynn_binary_add, 6538, 6183, 6535);
  g->Binary(ynn_binary_multiply, 2446, 6181, 6536);
  g->Binary(ynn_binary_multiply, 6536, 6535, 2447);
  g->Binary(ynn_binary_multiply, 2437, 2447, 2448);
  g->Binary(ynn_binary_divide, 2448, 7506, 2449);
  g->Unary(ynn_unary_round, 2449, 2451);
  g->Binary(ynn_binary_max, 2451, 7225, 2452);
  g->Binary(ynn_binary_min, 2452, 7340, 2453);
  g->Binary(ynn_binary_multiply, 2453, 7506, 2454);
  g->Convert(7780, 2455);
  g->Binary(ynn_binary_multiply, 2455, 7781, 2456);
  g->Matmul(2454, 2456, 2457, false, true);
  g->Binary(ynn_binary_divide, 2457, 7365, 2458);
  g->Unary(ynn_unary_round, 2458, 2459);
  g->Binary(ynn_binary_max, 2459, 7225, 2460);
  g->Binary(ynn_binary_min, 2460, 7340, 2463);
  g->Binary(ynn_binary_multiply, 2463, 7365, 2464);
  g->Unary(ynn_unary_square, 2464, 2465);
  g->Reduce(ynn_reduce_sum, 2465, 6540, {2}, true);
  g->ShapeProduct(2465, 6539, {2});
  g->Binary(ynn_binary_divide, 6540, 6539, 2466);
  g->Binary(ynn_binary_add, 2466, 7373, 2467);
  g->Binary(ynn_binary_pow, 2467, 7428, 2468);
  g->Binary(ynn_binary_multiply, 2464, 2468, 2469);
  g->Convert(7791, 2470);
  g->Binary(ynn_binary_multiply, 2469, 2470, 2471);
  g->Binary(ynn_binary_add, 2414, 2471, 2472);
}

// Scope: "Layer15 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1031, 2474, {0,0,15,0}, {-1,-1,1,-1});
  g->Reshape(2474, 2475, {1,1,256});
  g->Binary(ynn_binary_add, 2475, 8416, 2476);
  g->Binary(ynn_binary_multiply, 2476, 7155, 2477);
  g->Binary(ynn_binary_divide, 2472, 7198, 2478);
  g->Unary(ynn_unary_round, 2478, 2479);
  g->Binary(ynn_binary_max, 2479, 7225, 2480);
  g->Binary(ynn_binary_min, 2480, 7340, 2481);
  g->Binary(ynn_binary_multiply, 2481, 7198, 2482);
  g->Convert(7786, 2483);
  g->Binary(ynn_binary_multiply, 2483, 7787, 2485);
  g->Matmul(2482, 2485, 2486, false, true);
  g->Binary(ynn_binary_divide, 2486, 7350, 2487);
  g->Unary(ynn_unary_round, 2487, 2488);
  g->Binary(ynn_binary_max, 2488, 7225, 2489);
  g->Binary(ynn_binary_min, 2489, 7340, 2490);
  g->Binary(ynn_binary_multiply, 2490, 7350, 2491);
  g->Polynomial(2491, 6543, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6543, 6544);
  g->Binary(ynn_binary_add, 6544, 6183, 6541);
  g->Binary(ynn_binary_multiply, 2491, 6181, 6542);
  g->Binary(ynn_binary_multiply, 6542, 6541, 2492);
  g->Binary(ynn_binary_multiply, 2492, 2477, 2493);
  g->Binary(ynn_binary_divide, 2493, 7486, 2494);
  g->Unary(ynn_unary_round, 2494, 2496);
  g->Binary(ynn_binary_max, 2496, 7225, 2497);
  g->Binary(ynn_binary_min, 2497, 7340, 2498);
  g->Binary(ynn_binary_multiply, 2498, 7486, 2499);
  g->Convert(7788, 2500);
  g->Binary(ynn_binary_multiply, 2500, 7789, 2501);
  g->Matmul(2499, 2501, 2502, false, true);
  g->Binary(ynn_binary_divide, 2502, 7399, 2503);
  g->Unary(ynn_unary_round, 2503, 2504);
  g->Binary(ynn_binary_max, 2504, 7225, 2505);
  g->Binary(ynn_binary_min, 2505, 7340, 2507);
  g->Binary(ynn_binary_multiply, 2507, 7399, 2508);
  g->Unary(ynn_unary_square, 2508, 2509);
  g->Reduce(ynn_reduce_sum, 2509, 6546, {2}, true);
  g->ShapeProduct(2509, 6545, {2});
  g->Binary(ynn_binary_divide, 6546, 6545, 2510);
  g->Binary(ynn_binary_add, 2510, 7373, 2511);
  g->Binary(ynn_binary_pow, 2511, 7428, 2512);
  g->Binary(ynn_binary_multiply, 2508, 2512, 2513);
  g->Convert(7792, 2514);
  g->Binary(ynn_binary_multiply, 2513, 2514, 2515);
  g->Binary(ynn_binary_add, 2472, 2515, 2516);
  g->Convert(7779, 2518);
  g->Binary(ynn_binary_multiply, 2516, 2518, 2519);
}

// Scope: "Layer15"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15(Context& ctx) {
  BuildLayer15Attention(ctx);
  BuildLayer15Mlp(ctx);
  BuildLayer15PerLayerEmbedding(ctx);
}

// Scope: "Layer16 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Binary(ynn_binary_divide, 2526, 7197, 2527);
  g->Unary(ynn_unary_round, 2527, 2529);
  g->Binary(ynn_binary_max, 2529, 7225, 2530);
  g->Binary(ynn_binary_min, 2530, 7340, 2531);
  g->Binary(ynn_binary_multiply, 2531, 7197, 2532);
  g->Convert(7818, 2533);
  g->Binary(ynn_binary_multiply, 2533, 7819, 2534);
  g->Matmul(2532, 2534, 2535, false, true);
  g->Binary(ynn_binary_divide, 2535, 7422, 2536);
  g->Unary(ynn_unary_round, 2536, 2537);
  g->Binary(ynn_binary_max, 2537, 7225, 2538);
  g->Binary(ynn_binary_min, 2538, 7340, 2540);
  g->Binary(ynn_binary_multiply, 2540, 7422, 2541);
  g->SplitDim(2541, 2542, 2, {8,256});
  g->FuseDims(2542, 2544, 1, 2);
  g->SplitDim(2544, 2543, 1, {8,1});
  g->Unary(ynn_unary_square, 2543, 2545);
  g->Reduce(ynn_reduce_sum, 2545, 6550, {3}, true);
  g->ShapeProduct(2545, 6549, {3});
  g->Binary(ynn_binary_divide, 6550, 6549, 2546);
  g->Binary(ynn_binary_add, 2546, 7373, 2547);
  g->Binary(ynn_binary_pow, 2547, 7428, 2548);
  g->Binary(ynn_binary_multiply, 2543, 2548, 2549);
  g->Convert(7817, 2550);
  g->Binary(ynn_binary_multiply, 2549, 2550, 2552);
  g->Slice(2552, 2553, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2552, 2554, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2554, 2555);
  g->Concat({2555,2553}, 2556, 3);
  g->Binary(ynn_binary_multiply, 2552, 2044, 2557);
  g->Binary(ynn_binary_multiply, 2556, 3111, 2558);
  g->Binary(ynn_binary_add, 2557, 2558, 2559);
}

// Scope: "Layer16 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(2559, 1963, 2560, false, true);
  g->Mask(2560, 7569, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 7569, 6554, {-1}, true);
  g->Binary(ynn_binary_subtract, 7569, 6554, 6551);
  g->Unary(ynn_unary_exp, 6551, 6552);
  g->Reduce(ynn_reduce_sum, 6552, 6555, {-1}, true);
  g->Binary(ynn_binary_divide, 6183, 6555, 6553);
  g->Binary(ynn_binary_multiply, 6552, 6553, 2562);
  g->Matmul(2562, 1965, 2563, false, false);
}

// Scope: "Layer16 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(2563, 2565, 1, 2);
  g->SplitDim(2565, 2564, 1, {1,8});
  g->FuseDims(2564, 2566, 2, 2);
  g->Binary(ynn_binary_divide, 2566, 7457, 2567);
  g->Unary(ynn_unary_round, 2567, 2568);
  g->Binary(ynn_binary_max, 2568, 7225, 2569);
  g->Binary(ynn_binary_min, 2569, 7340, 2570);
  g->Binary(ynn_binary_multiply, 2570, 7457, 2571);
  g->Convert(7815, 2572);
  g->Binary(ynn_binary_multiply, 2572, 7816, 2575);
  g->Matmul(2571, 2575, 2576, false, true);
  g->Binary(ynn_binary_divide, 2576, 7442, 2577);
  g->Unary(ynn_unary_round, 2577, 2578);
  g->Binary(ynn_binary_max, 2578, 7225, 2579);
  g->Binary(ynn_binary_min, 2579, 7340, 2580);
  g->Binary(ynn_binary_multiply, 2580, 7442, 2581);
}

// Scope: "Layer16 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2519, 2520);
  g->Reduce(ynn_reduce_sum, 2520, 6548, {2}, true);
  g->ShapeProduct(2520, 6547, {2});
  g->Binary(ynn_binary_divide, 6548, 6547, 2521);
  g->Binary(ynn_binary_add, 2521, 7373, 2522);
  g->Binary(ynn_binary_pow, 2522, 7428, 2523);
  g->Binary(ynn_binary_multiply, 2519, 2523, 2524);
  g->Convert(7799, 2525);
  g->Binary(ynn_binary_multiply, 2524, 2525, 2526);
  BuildLayer16AttentionQueryProjection(ctx);
  BuildLayer16AttentionSdpa(ctx);
  BuildLayer16AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2581, 2582);
  g->Reduce(ynn_reduce_sum, 2582, 6557, {2}, true);
  g->ShapeProduct(2582, 6556, {2});
  g->Binary(ynn_binary_divide, 6557, 6556, 2583);
  g->Binary(ynn_binary_add, 2583, 7373, 2584);
  g->Binary(ynn_binary_pow, 2584, 7428, 2586);
  g->Binary(ynn_binary_multiply, 2581, 2586, 2587);
  g->Convert(7811, 2588);
  g->Binary(ynn_binary_multiply, 2587, 2588, 2589);
  g->Binary(ynn_binary_add, 2519, 2589, 2590);
}

// Scope: "Layer16 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2590, 2591);
  g->Reduce(ynn_reduce_sum, 2591, 6559, {2}, true);
  g->ShapeProduct(2591, 6558, {2});
  g->Binary(ynn_binary_divide, 6559, 6558, 2592);
  g->Binary(ynn_binary_add, 2592, 7373, 2593);
  g->Binary(ynn_binary_pow, 2593, 7428, 2594);
  g->Binary(ynn_binary_multiply, 2590, 2594, 2595);
  g->Convert(7814, 2597);
  g->Binary(ynn_binary_multiply, 2595, 2597, 2598);
  g->Binary(ynn_binary_divide, 2598, 7401, 2599);
  g->Unary(ynn_unary_round, 2599, 2600);
  g->Binary(ynn_binary_max, 2600, 7225, 2601);
  g->Binary(ynn_binary_min, 2601, 7340, 2602);
  g->Binary(ynn_binary_multiply, 2602, 7401, 2603);
  g->Convert(7805, 2604);
  g->Binary(ynn_binary_multiply, 2604, 7806, 2605);
  g->Matmul(2603, 2605, 2606, false, true);
  g->Binary(ynn_binary_divide, 2606, 7420, 2608);
  g->Unary(ynn_unary_round, 2608, 2609);
  g->Binary(ynn_binary_max, 2609, 7225, 2610);
  g->Binary(ynn_binary_min, 2610, 7340, 2611);
  g->Binary(ynn_binary_multiply, 2611, 7420, 2612);
  g->Convert(7803, 2614);
  g->Binary(ynn_binary_multiply, 2614, 7804, 2615);
  g->Matmul(2603, 2615, 2616, false, true);
  g->Binary(ynn_binary_divide, 2616, 7420, 2617);
  g->Unary(ynn_unary_round, 2617, 2618);
  g->Binary(ynn_binary_max, 2618, 7225, 2619);
  g->Binary(ynn_binary_min, 2619, 7340, 2620);
  g->Binary(ynn_binary_multiply, 2620, 7420, 2621);
  g->Polynomial(2621, 6564, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6564, 6565);
  g->Binary(ynn_binary_add, 6565, 6183, 6562);
  g->Binary(ynn_binary_multiply, 2621, 6181, 6563);
  g->Binary(ynn_binary_multiply, 6563, 6562, 2622);
  g->Binary(ynn_binary_multiply, 2612, 2622, 2623);
  g->Binary(ynn_binary_divide, 2623, 7173, 2625);
  g->Unary(ynn_unary_round, 2625, 2626);
  g->Binary(ynn_binary_max, 2626, 7225, 2627);
  g->Binary(ynn_binary_min, 2627, 7340, 2628);
  g->Binary(ynn_binary_multiply, 2628, 7173, 2629);
  g->Convert(7801, 2630);
  g->Binary(ynn_binary_multiply, 2630, 7802, 2631);
  g->Matmul(2629, 2631, 2632, false, true);
  g->Binary(ynn_binary_divide, 2632, 7177, 2633);
  g->Unary(ynn_unary_round, 2633, 2634);
  g->Binary(ynn_binary_max, 2634, 7225, 2636);
  g->Binary(ynn_binary_min, 2636, 7340, 2637);
  g->Binary(ynn_binary_multiply, 2637, 7177, 2638);
  g->Unary(ynn_unary_square, 2638, 2639);
  g->Reduce(ynn_reduce_sum, 2639, 6567, {2}, true);
  g->ShapeProduct(2639, 6566, {2});
  g->Binary(ynn_binary_divide, 6567, 6566, 2640);
  g->Binary(ynn_binary_add, 2640, 7373, 2641);
  g->Binary(ynn_binary_pow, 2641, 7428, 2642);
  g->Binary(ynn_binary_multiply, 2638, 2642, 2643);
  g->Convert(7812, 2644);
  g->Binary(ynn_binary_multiply, 2643, 2644, 2645);
  g->Binary(ynn_binary_add, 2590, 2645, 2647);
}

// Scope: "Layer16 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1031, 2648, {0,0,16,0}, {-1,-1,1,-1});
  g->Reshape(2648, 2649, {1,1,256});
  g->Binary(ynn_binary_add, 2649, 8417, 2650);
  g->Binary(ynn_binary_multiply, 2650, 7155, 2651);
  g->Binary(ynn_binary_divide, 2647, 7317, 2652);
  g->Unary(ynn_unary_round, 2652, 2653);
  g->Binary(ynn_binary_max, 2653, 7225, 2654);
  g->Binary(ynn_binary_min, 2654, 7340, 2655);
  g->Binary(ynn_binary_multiply, 2655, 7317, 2656);
  g->Convert(7807, 2658);
  g->Binary(ynn_binary_multiply, 2658, 7808, 2659);
  g->Matmul(2656, 2659, 2660, false, true);
  g->Binary(ynn_binary_divide, 2660, 7263, 2661);
  g->Unary(ynn_unary_round, 2661, 2662);
  g->Binary(ynn_binary_max, 2662, 7225, 2663);
  g->Binary(ynn_binary_min, 2663, 7340, 2664);
  g->Binary(ynn_binary_multiply, 2664, 7263, 2665);
  g->Polynomial(2665, 6570, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6570, 6571);
  g->Binary(ynn_binary_add, 6571, 6183, 6568);
  g->Binary(ynn_binary_multiply, 2665, 6181, 6569);
  g->Binary(ynn_binary_multiply, 6569, 6568, 2666);
  g->Binary(ynn_binary_multiply, 2666, 2651, 2667);
  g->Binary(ynn_binary_divide, 2667, 7327, 2669);
  g->Unary(ynn_unary_round, 2669, 2670);
  g->Binary(ynn_binary_max, 2670, 7225, 2671);
  g->Binary(ynn_binary_min, 2671, 7340, 2672);
  g->Binary(ynn_binary_multiply, 2672, 7327, 2673);
  g->Convert(7809, 2674);
  g->Binary(ynn_binary_multiply, 2674, 7810, 2675);
  g->Matmul(2673, 2675, 2676, false, true);
  g->Binary(ynn_binary_divide, 2676, 7471, 2677);
  g->Unary(ynn_unary_round, 2677, 2678);
  g->Binary(ynn_binary_max, 2678, 7225, 2681);
  g->Binary(ynn_binary_min, 2681, 7340, 2682);
  g->Binary(ynn_binary_multiply, 2682, 7471, 2683);
  g->Unary(ynn_unary_square, 2683, 2684);
  g->Reduce(ynn_reduce_sum, 2684, 6575, {2}, true);
  g->ShapeProduct(2684, 6574, {2});
  g->Binary(ynn_binary_divide, 6575, 6574, 2685);
  g->Binary(ynn_binary_add, 2685, 7373, 2686);
  g->Binary(ynn_binary_pow, 2686, 7428, 2687);
  g->Binary(ynn_binary_multiply, 2683, 2687, 2688);
  g->Convert(7813, 2689);
  g->Binary(ynn_binary_multiply, 2688, 2689, 2690);
  g->Binary(ynn_binary_add, 2647, 2690, 2692);
  g->Convert(7800, 2693);
  g->Binary(ynn_binary_multiply, 2692, 2693, 2694);
}

// Scope: "Layer16"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16(Context& ctx) {
  BuildLayer16Attention(ctx);
  BuildLayer16Mlp(ctx);
  BuildLayer16PerLayerEmbedding(ctx);
}

// Scope: "Layer17 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Binary(ynn_binary_divide, 2701, 7541, 2703);
  g->Unary(ynn_unary_round, 2703, 2704);
  g->Binary(ynn_binary_max, 2704, 7225, 2705);
  g->Binary(ynn_binary_min, 2705, 7340, 2706);
  g->Binary(ynn_binary_multiply, 2706, 7541, 2707);
  g->Convert(7839, 2708);
  g->Binary(ynn_binary_multiply, 2708, 7840, 2709);
  g->Matmul(2707, 2709, 2710, false, true);
  g->Binary(ynn_binary_divide, 2710, 7372, 2711);
  g->Unary(ynn_unary_round, 2711, 2712);
  g->Binary(ynn_binary_max, 2712, 7225, 2714);
  g->Binary(ynn_binary_min, 2714, 7340, 2715);
  g->Binary(ynn_binary_multiply, 2715, 7372, 2716);
  g->SplitDim(2716, 2717, 2, {8,256});
  g->FuseDims(2717, 2719, 1, 2);
  g->SplitDim(2719, 2718, 1, {8,1});
  g->Unary(ynn_unary_square, 2718, 2720);
  g->Reduce(ynn_reduce_sum, 2720, 6579, {3}, true);
  g->ShapeProduct(2720, 6578, {3});
  g->Binary(ynn_binary_divide, 6579, 6578, 2721);
  g->Binary(ynn_binary_add, 2721, 7373, 2722);
  g->Binary(ynn_binary_pow, 2722, 7428, 2723);
  g->Binary(ynn_binary_multiply, 2718, 2723, 2724);
  g->Convert(7838, 2726);
  g->Binary(ynn_binary_multiply, 2724, 2726, 2727);
  g->Slice(2727, 2728, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2727, 2729, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2729, 2730);
  g->Concat({2730,2728}, 2731, 3);
  g->Binary(ynn_binary_multiply, 2727, 2044, 2732);
  g->Binary(ynn_binary_multiply, 2731, 3111, 2733);
  g->Binary(ynn_binary_add, 2732, 2733, 2734);
}

// Scope: "Layer17 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(2734, 1963, 2735, false, true);
  g->Mask(2735, 7570, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 7570, 6583, {-1}, true);
  g->Binary(ynn_binary_subtract, 7570, 6583, 6580);
  g->Unary(ynn_unary_exp, 6580, 6581);
  g->Reduce(ynn_reduce_sum, 6581, 6584, {-1}, true);
  g->Binary(ynn_binary_divide, 6183, 6584, 6582);
  g->Binary(ynn_binary_multiply, 6581, 6582, 2737);
  g->Matmul(2737, 1965, 2738, false, false);
}

// Scope: "Layer17 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(2738, 2740, 1, 2);
  g->SplitDim(2740, 2739, 1, {1,8});
  g->FuseDims(2739, 2741, 2, 2);
  g->Binary(ynn_binary_divide, 2741, 7378, 2742);
  g->Unary(ynn_unary_round, 2742, 2743);
  g->Binary(ynn_binary_max, 2743, 7225, 2744);
  g->Binary(ynn_binary_min, 2744, 7340, 2745);
  g->Binary(ynn_binary_multiply, 2745, 7378, 2746);
  g->Convert(7836, 2748);
  g->Binary(ynn_binary_multiply, 2748, 7837, 2749);
  g->Matmul(2746, 2749, 2750, false, true);
  g->Binary(ynn_binary_divide, 2750, 7366, 2751);
  g->Unary(ynn_unary_round, 2751, 2752);
  g->Binary(ynn_binary_max, 2752, 7225, 2753);
  g->Binary(ynn_binary_min, 2753, 7340, 2754);
  g->Binary(ynn_binary_multiply, 2754, 7366, 2755);
}

// Scope: "Layer17 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2694, 2695);
  g->Reduce(ynn_reduce_sum, 2695, 6577, {2}, true);
  g->ShapeProduct(2695, 6576, {2});
  g->Binary(ynn_binary_divide, 6577, 6576, 2696);
  g->Binary(ynn_binary_add, 2696, 7373, 2697);
  g->Binary(ynn_binary_pow, 2697, 7428, 2698);
  g->Binary(ynn_binary_multiply, 2694, 2698, 2699);
  g->Convert(7820, 2700);
  g->Binary(ynn_binary_multiply, 2699, 2700, 2701);
  BuildLayer17AttentionQueryProjection(ctx);
  BuildLayer17AttentionSdpa(ctx);
  BuildLayer17AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2755, 2756);
  g->Reduce(ynn_reduce_sum, 2756, 6586, {2}, true);
  g->ShapeProduct(2756, 6585, {2});
  g->Binary(ynn_binary_divide, 6586, 6585, 2757);
  g->Binary(ynn_binary_add, 2757, 7373, 2759);
  g->Binary(ynn_binary_pow, 2759, 7428, 2760);
  g->Binary(ynn_binary_multiply, 2755, 2760, 2761);
  g->Convert(7832, 2762);
  g->Binary(ynn_binary_multiply, 2761, 2762, 2763);
  g->Binary(ynn_binary_add, 2694, 2763, 2764);
}

// Scope: "Layer17 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2764, 2765);
  g->Reduce(ynn_reduce_sum, 2765, 6588, {2}, true);
  g->ShapeProduct(2765, 6587, {2});
  g->Binary(ynn_binary_divide, 6588, 6587, 2766);
  g->Binary(ynn_binary_add, 2766, 7373, 2767);
  g->Binary(ynn_binary_pow, 2767, 7428, 2768);
  g->Binary(ynn_binary_multiply, 2764, 2768, 2770);
  g->Convert(7835, 2771);
  g->Binary(ynn_binary_multiply, 2770, 2771, 2772);
  g->Binary(ynn_binary_divide, 2772, 7531, 2773);
  g->Unary(ynn_unary_round, 2773, 2774);
  g->Binary(ynn_binary_max, 2774, 7225, 2775);
  g->Binary(ynn_binary_min, 2775, 7340, 2776);
  g->Binary(ynn_binary_multiply, 2776, 7531, 2777);
  g->Convert(7826, 2778);
  g->Binary(ynn_binary_multiply, 2778, 7827, 2779);
  g->Matmul(2777, 2779, 2781, false, true);
  g->Binary(ynn_binary_divide, 2781, 7507, 2782);
  g->Unary(ynn_unary_round, 2782, 2783);
  g->Binary(ynn_binary_max, 2783, 7225, 2784);
  g->Binary(ynn_binary_min, 2784, 7340, 2785);
  g->Binary(ynn_binary_multiply, 2785, 7507, 2786);
  g->Convert(7824, 2789);
  g->Binary(ynn_binary_multiply, 2789, 7825, 2790);
  g->Matmul(2777, 2790, 2791, false, true);
  g->Binary(ynn_binary_divide, 2791, 7507, 2792);
  g->Unary(ynn_unary_round, 2792, 2793);
  g->Binary(ynn_binary_max, 2793, 7225, 2794);
  g->Binary(ynn_binary_min, 2794, 7340, 2795);
  g->Binary(ynn_binary_multiply, 2795, 7507, 2796);
  g->Polynomial(2796, 6591, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6591, 6592);
  g->Binary(ynn_binary_add, 6592, 6183, 6589);
  g->Binary(ynn_binary_multiply, 2796, 6181, 6590);
  g->Binary(ynn_binary_multiply, 6590, 6589, 2797);
  g->Binary(ynn_binary_multiply, 2786, 2797, 2799);
  g->Binary(ynn_binary_divide, 2799, 7515, 2800);
  g->Unary(ynn_unary_round, 2800, 2801);
  g->Binary(ynn_binary_max, 2801, 7225, 2802);
  g->Binary(ynn_binary_min, 2802, 7340, 2803);
  g->Binary(ynn_binary_multiply, 2803, 7515, 2804);
  g->Convert(7822, 2805);
  g->Binary(ynn_binary_multiply, 2805, 7823, 2806);
  g->Matmul(2804, 2806, 2807, false, true);
  g->Binary(ynn_binary_divide, 2807, 7282, 2808);
  g->Unary(ynn_unary_round, 2808, 2810);
  g->Binary(ynn_binary_max, 2810, 7225, 2811);
  g->Binary(ynn_binary_min, 2811, 7340, 2812);
  g->Binary(ynn_binary_multiply, 2812, 7282, 2813);
  g->Unary(ynn_unary_square, 2813, 2814);
  g->Reduce(ynn_reduce_sum, 2814, 6594, {2}, true);
  g->ShapeProduct(2814, 6593, {2});
  g->Binary(ynn_binary_divide, 6594, 6593, 2815);
  g->Binary(ynn_binary_add, 2815, 7373, 2816);
  g->Binary(ynn_binary_pow, 2816, 7428, 2817);
  g->Binary(ynn_binary_multiply, 2813, 2817, 2818);
  g->Convert(7833, 2819);
  g->Binary(ynn_binary_multiply, 2818, 2819, 2821);
  g->Binary(ynn_binary_add, 2764, 2821, 2822);
}

// Scope: "Layer17 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1031, 2823, {0,0,17,0}, {-1,-1,1,-1});
  g->Reshape(2823, 2824, {1,1,256});
  g->Binary(ynn_binary_add, 2824, 8418, 2825);
  g->Binary(ynn_binary_multiply, 2825, 7155, 2826);
  g->Binary(ynn_binary_divide, 2822, 7389, 2827);
  g->Unary(ynn_unary_round, 2827, 2828);
  g->Binary(ynn_binary_max, 2828, 7225, 2829);
  g->Binary(ynn_binary_min, 2829, 7340, 2830);
  g->Binary(ynn_binary_multiply, 2830, 7389, 2832);
  g->Convert(7828, 2833);
  g->Binary(ynn_binary_multiply, 2833, 7829, 2834);
  g->Matmul(2832, 2834, 2835, false, true);
  g->Binary(ynn_binary_divide, 2835, 7508, 2836);
  g->Unary(ynn_unary_round, 2836, 2837);
  g->Binary(ynn_binary_max, 2837, 7225, 2838);
  g->Binary(ynn_binary_min, 2838, 7340, 2839);
  g->Binary(ynn_binary_multiply, 2839, 7508, 2840);
  g->Polynomial(2840, 6597, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6597, 6598);
  g->Binary(ynn_binary_add, 6598, 6183, 6595);
  g->Binary(ynn_binary_multiply, 2840, 6181, 6596);
  g->Binary(ynn_binary_multiply, 6596, 6595, 2841);
  g->Binary(ynn_binary_multiply, 2841, 2826, 2843);
  g->Binary(ynn_binary_divide, 2843, 7393, 2844);
  g->Unary(ynn_unary_round, 2844, 2845);
  g->Binary(ynn_binary_max, 2845, 7225, 2846);
  g->Binary(ynn_binary_min, 2846, 7340, 2847);
  g->Binary(ynn_binary_multiply, 2847, 7393, 2848);
  g->Convert(7830, 2849);
  g->Binary(ynn_binary_multiply, 2849, 7831, 2850);
  g->Matmul(2848, 2850, 2851, false, true);
  g->Binary(ynn_binary_divide, 2851, 7538, 2852);
  g->Unary(ynn_unary_round, 2852, 2854);
  g->Binary(ynn_binary_max, 2854, 7225, 2855);
  g->Binary(ynn_binary_min, 2855, 7340, 2856);
  g->Binary(ynn_binary_multiply, 2856, 7538, 2857);
  g->Unary(ynn_unary_square, 2857, 2858);
  g->Reduce(ynn_reduce_sum, 2858, 6600, {2}, true);
  g->ShapeProduct(2858, 6599, {2});
  g->Binary(ynn_binary_divide, 6600, 6599, 2859);
  g->Binary(ynn_binary_add, 2859, 7373, 2860);
  g->Binary(ynn_binary_pow, 2860, 7428, 2861);
  g->Binary(ynn_binary_multiply, 2857, 2861, 2862);
  g->Convert(7834, 2863);
  g->Binary(ynn_binary_multiply, 2862, 2863, 2865);
  g->Binary(ynn_binary_add, 2822, 2865, 2866);
  g->Convert(7821, 2867);
  g->Binary(ynn_binary_multiply, 2866, 2867, 2868);
}

// Scope: "Layer17"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17(Context& ctx) {
  BuildLayer17Attention(ctx);
  BuildLayer17Mlp(ctx);
  BuildLayer17PerLayerEmbedding(ctx);
}

// Scope: "Layer18 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Binary(ynn_binary_divide, 2876, 7375, 2877);
  g->Unary(ynn_unary_round, 2877, 2878);
  g->Binary(ynn_binary_max, 2878, 7225, 2879);
  g->Binary(ynn_binary_min, 2879, 7340, 2880);
  g->Binary(ynn_binary_multiply, 2880, 7375, 2881);
  g->Convert(7860, 2882);
  g->Binary(ynn_binary_multiply, 2882, 7861, 2883);
  g->Matmul(2881, 2883, 2884, false, true);
  g->Binary(ynn_binary_divide, 2884, 7157, 2885);
  g->Unary(ynn_unary_round, 2885, 2886);
  g->Binary(ynn_binary_max, 2886, 7225, 2887);
  g->Binary(ynn_binary_min, 2887, 7340, 2888);
  g->Binary(ynn_binary_multiply, 2888, 7157, 2889);
  g->SplitDim(2889, 2890, 2, {8,256});
  g->FuseDims(2890, 2892, 1, 2);
  g->SplitDim(2892, 2891, 1, {8,1});
  g->Unary(ynn_unary_square, 2891, 2893);
  g->Reduce(ynn_reduce_sum, 2893, 6604, {3}, true);
  g->ShapeProduct(2893, 6603, {3});
  g->Binary(ynn_binary_divide, 6604, 6603, 2894);
  g->Binary(ynn_binary_add, 2894, 7373, 2895);
  g->Binary(ynn_binary_pow, 2895, 7428, 2896);
  g->Binary(ynn_binary_multiply, 2891, 2896, 2898);
  g->Convert(7859, 2899);
  g->Binary(ynn_binary_multiply, 2898, 2899, 2900);
  g->Slice(2900, 2901, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2900, 2902, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2902, 2903);
  g->Concat({2903,2901}, 2904, 3);
  g->Binary(ynn_binary_multiply, 2900, 2044, 2905);
  g->Binary(ynn_binary_multiply, 2904, 3111, 2906);
  g->Binary(ynn_binary_add, 2905, 2906, 2907);
}

// Scope: "Layer18 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(2907, 1963, 2908, false, true);
  g->Mask(2908, 7571, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 7571, 6608, {-1}, true);
  g->Binary(ynn_binary_subtract, 7571, 6608, 6605);
  g->Unary(ynn_unary_exp, 6605, 6606);
  g->Reduce(ynn_reduce_sum, 6606, 6609, {-1}, true);
  g->Binary(ynn_binary_divide, 6183, 6609, 6607);
  g->Binary(ynn_binary_multiply, 6606, 6607, 2909);
  g->Matmul(2909, 1965, 2910, false, false);
}

// Scope: "Layer18 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(2910, 2912, 1, 2);
  g->SplitDim(2912, 2911, 1, {1,8});
  g->FuseDims(2911, 2913, 2, 2);
  g->Binary(ynn_binary_divide, 2913, 7238, 2914);
  g->Unary(ynn_unary_round, 2914, 2915);
  g->Binary(ynn_binary_max, 2915, 7225, 2916);
  g->Binary(ynn_binary_min, 2916, 7340, 2917);
  g->Binary(ynn_binary_multiply, 2917, 7238, 2918);
  g->Convert(7857, 2919);
  g->Binary(ynn_binary_multiply, 2919, 7858, 2920);
  g->Matmul(2918, 2920, 2921, false, true);
  g->Binary(ynn_binary_divide, 2921, 7316, 2922);
  g->Unary(ynn_unary_round, 2922, 2923);
  g->Binary(ynn_binary_max, 2923, 7225, 2924);
  g->Binary(ynn_binary_min, 2924, 7340, 2925);
  g->Binary(ynn_binary_multiply, 2925, 7316, 2926);
}

// Scope: "Layer18 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2868, 2869);
  g->Reduce(ynn_reduce_sum, 2869, 6602, {2}, true);
  g->ShapeProduct(2869, 6601, {2});
  g->Binary(ynn_binary_divide, 6602, 6601, 2870);
  g->Binary(ynn_binary_add, 2870, 7373, 2871);
  g->Binary(ynn_binary_pow, 2871, 7428, 2872);
  g->Binary(ynn_binary_multiply, 2868, 2872, 2873);
  g->Convert(7841, 2874);
  g->Binary(ynn_binary_multiply, 2873, 2874, 2876);
  BuildLayer18AttentionQueryProjection(ctx);
  BuildLayer18AttentionSdpa(ctx);
  BuildLayer18AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2926, 2927);
  g->Reduce(ynn_reduce_sum, 2927, 6611, {2}, true);
  g->ShapeProduct(2927, 6610, {2});
  g->Binary(ynn_binary_divide, 6611, 6610, 2928);
  g->Binary(ynn_binary_add, 2928, 7373, 2929);
  g->Binary(ynn_binary_pow, 2929, 7428, 2930);
  g->Binary(ynn_binary_multiply, 2926, 2930, 2931);
  g->Convert(7853, 2932);
  g->Binary(ynn_binary_multiply, 2931, 2932, 2933);
  g->Binary(ynn_binary_add, 2868, 2933, 2934);
}

// Scope: "Layer18 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2934, 2935);
  g->Reduce(ynn_reduce_sum, 2935, 6613, {2}, true);
  g->ShapeProduct(2935, 6612, {2});
  g->Binary(ynn_binary_divide, 6613, 6612, 2936);
  g->Binary(ynn_binary_add, 2936, 7373, 2937);
  g->Binary(ynn_binary_pow, 2937, 7428, 2939);
  g->Binary(ynn_binary_multiply, 2934, 2939, 2940);
  g->Convert(7856, 2941);
  g->Binary(ynn_binary_multiply, 2940, 2941, 2942);
  g->Binary(ynn_binary_divide, 2942, 7392, 2943);
  g->Unary(ynn_unary_round, 2943, 2944);
  g->Binary(ynn_binary_max, 2944, 7225, 2945);
  g->Binary(ynn_binary_min, 2945, 7340, 2946);
  g->Binary(ynn_binary_multiply, 2946, 7392, 2947);
  g->Convert(7847, 2948);
  g->Binary(ynn_binary_multiply, 2948, 7848, 2950);
  g->Matmul(2947, 2950, 2951, false, true);
  g->Binary(ynn_binary_divide, 2951, 7190, 2952);
  g->Unary(ynn_unary_round, 2952, 2953);
  g->Binary(ynn_binary_max, 2953, 7225, 2954);
  g->Binary(ynn_binary_min, 2954, 7340, 2955);
  g->Binary(ynn_binary_multiply, 2955, 7190, 2956);
  g->Convert(7845, 2958);
  g->Binary(ynn_binary_multiply, 2958, 7846, 2959);
  g->Matmul(2947, 2959, 2960, false, true);
  g->Binary(ynn_binary_divide, 2960, 7190, 2961);
  g->Unary(ynn_unary_round, 2961, 2962);
  g->Binary(ynn_binary_max, 2962, 7225, 2963);
  g->Binary(ynn_binary_min, 2963, 7340, 2964);
  g->Binary(ynn_binary_multiply, 2964, 7190, 2965);
  g->Polynomial(2965, 6616, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6616, 6617);
  g->Binary(ynn_binary_add, 6617, 6183, 6614);
  g->Binary(ynn_binary_multiply, 2965, 6181, 6615);
  g->Binary(ynn_binary_multiply, 6615, 6614, 2967);
  g->Binary(ynn_binary_multiply, 2956, 2967, 2968);
  g->Binary(ynn_binary_divide, 2968, 7465, 2969);
  g->Unary(ynn_unary_round, 2969, 2970);
  g->Binary(ynn_binary_max, 2970, 7225, 2971);
  g->Binary(ynn_binary_min, 2971, 7340, 2972);
  g->Binary(ynn_binary_multiply, 2972, 7465, 2973);
  g->Convert(7843, 2974);
  g->Binary(ynn_binary_multiply, 2974, 7844, 2975);
  g->Matmul(2973, 2975, 2976, false, true);
  g->Binary(ynn_binary_divide, 2976, 7159, 2978);
  g->Unary(ynn_unary_round, 2978, 2979);
  g->Binary(ynn_binary_max, 2979, 7225, 2980);
  g->Binary(ynn_binary_min, 2980, 7340, 2981);
  g->Binary(ynn_binary_multiply, 2981, 7159, 2982);
  g->Unary(ynn_unary_square, 2982, 2983);
  g->Reduce(ynn_reduce_sum, 2983, 6619, {2}, true);
  g->ShapeProduct(2983, 6618, {2});
  g->Binary(ynn_binary_divide, 6619, 6618, 2984);
  g->Binary(ynn_binary_add, 2984, 7373, 2985);
  g->Binary(ynn_binary_pow, 2985, 7428, 2986);
  g->Binary(ynn_binary_multiply, 2982, 2986, 2987);
  g->Convert(7854, 2989);
  g->Binary(ynn_binary_multiply, 2987, 2989, 2990);
  g->Binary(ynn_binary_add, 2934, 2990, 2991);
}

// Scope: "Layer18 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1031, 2992, {0,0,18,0}, {-1,-1,1,-1});
  g->Reshape(2992, 2993, {1,1,256});
  g->Binary(ynn_binary_add, 2993, 8419, 2994);
  g->Binary(ynn_binary_multiply, 2994, 7155, 2995);
  g->Binary(ynn_binary_divide, 2991, 7186, 2996);
  g->Unary(ynn_unary_round, 2996, 2997);
  g->Binary(ynn_binary_max, 2997, 7225, 2998);
  g->Binary(ynn_binary_min, 2998, 7340, 3001);
  g->Binary(ynn_binary_multiply, 3001, 7186, 3002);
  g->Convert(7849, 3003);
  g->Binary(ynn_binary_multiply, 3003, 7850, 3004);
  g->Matmul(3002, 3004, 3005, false, true);
  g->Binary(ynn_binary_divide, 3005, 7434, 3006);
  g->Unary(ynn_unary_round, 3006, 3007);
  g->Binary(ynn_binary_max, 3007, 7225, 3008);
  g->Binary(ynn_binary_min, 3008, 7340, 3009);
  g->Binary(ynn_binary_multiply, 3009, 7434, 3010);
  g->Polynomial(3010, 6622, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6622, 6623);
  g->Binary(ynn_binary_add, 6623, 6183, 6620);
  g->Binary(ynn_binary_multiply, 3010, 6181, 6621);
  g->Binary(ynn_binary_multiply, 6621, 6620, 3012);
  g->Binary(ynn_binary_multiply, 3012, 2995, 3013);
  g->Binary(ynn_binary_divide, 3013, 7247, 3014);
  g->Unary(ynn_unary_round, 3014, 3015);
  g->Binary(ynn_binary_max, 3015, 7225, 3016);
  g->Binary(ynn_binary_min, 3016, 7340, 3017);
  g->Binary(ynn_binary_multiply, 3017, 7247, 3018);
  g->Convert(7851, 3019);
  g->Binary(ynn_binary_multiply, 3019, 7852, 3020);
  g->Matmul(3018, 3020, 3021, false, true);
  g->Binary(ynn_binary_divide, 3021, 7396, 3023);
  g->Unary(ynn_unary_round, 3023, 3024);
  g->Binary(ynn_binary_max, 3024, 7225, 3025);
  g->Binary(ynn_binary_min, 3025, 7340, 3026);
  g->Binary(ynn_binary_multiply, 3026, 7396, 3027);
  g->Unary(ynn_unary_square, 3027, 3028);
  g->Reduce(ynn_reduce_sum, 3028, 6629, {2}, true);
  g->ShapeProduct(3028, 6628, {2});
  g->Binary(ynn_binary_divide, 6629, 6628, 3029);
  g->Binary(ynn_binary_add, 3029, 7373, 3030);
  g->Binary(ynn_binary_pow, 3030, 7428, 3031);
  g->Binary(ynn_binary_multiply, 3027, 3031, 3032);
  g->Convert(7855, 3034);
  g->Binary(ynn_binary_multiply, 3032, 3034, 3035);
  g->Binary(ynn_binary_add, 2991, 3035, 3036);
  g->Convert(7842, 3037);
  g->Binary(ynn_binary_multiply, 3036, 3037, 3038);
}

// Scope: "Layer18"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18(Context& ctx) {
  BuildLayer18Attention(ctx);
  BuildLayer18Mlp(ctx);
  BuildLayer18PerLayerEmbedding(ctx);
}

// Scope: "Layer19 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Binary(ynn_binary_divide, 3046, 7215, 3047);
  g->Unary(ynn_unary_round, 3047, 3048);
  g->Binary(ynn_binary_max, 3048, 7225, 3049);
  g->Binary(ynn_binary_min, 3049, 7340, 3050);
  g->Binary(ynn_binary_multiply, 3050, 7215, 3051);
  g->Convert(7881, 3052);
  g->Binary(ynn_binary_multiply, 3052, 7882, 3053);
  g->Matmul(3051, 3053, 3054, false, true);
  g->Binary(ynn_binary_divide, 3054, 7290, 3056);
  g->Unary(ynn_unary_round, 3056, 3057);
  g->Binary(ynn_binary_max, 3057, 7225, 3058);
  g->Binary(ynn_binary_min, 3058, 7340, 3059);
  g->Binary(ynn_binary_multiply, 3059, 7290, 3060);
  g->SplitDim(3060, 3061, 2, {8,512});
  g->FuseDims(3061, 3063, 1, 2);
  g->SplitDim(3063, 3062, 1, {8,1});
  g->Unary(ynn_unary_square, 3062, 3064);
  g->Reduce(ynn_reduce_sum, 3064, 6633, {3}, true);
  g->ShapeProduct(3064, 6632, {3});
  g->Binary(ynn_binary_divide, 6633, 6632, 3065);
  g->Binary(ynn_binary_add, 3065, 7373, 3066);
  g->Binary(ynn_binary_pow, 3066, 7428, 3068);
  g->Binary(ynn_binary_multiply, 3062, 3068, 3069);
  g->Convert(7880, 3070);
  g->Binary(ynn_binary_multiply, 3069, 3070, 3071);
  g->Slice(3071, 3072, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(3071, 3073, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 3073, 3074);
  g->Concat({3074,3072}, 3075, 3);
  g->Binary(ynn_binary_multiply, 3071, 5976, 3076);
  g->Binary(ynn_binary_multiply, 3075, 6075, 3077);
  g->Binary(ynn_binary_add, 3076, 3077, 3079);
}

// Scope: "Layer19 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(3079, 2179, 3080, false, true);
  g->Mask(3080, 7572, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 7572, 6637, {-1}, true);
  g->Binary(ynn_binary_subtract, 7572, 6637, 6634);
  g->Unary(ynn_unary_exp, 6634, 6635);
  g->Reduce(ynn_reduce_sum, 6635, 6638, {-1}, true);
  g->Binary(ynn_binary_divide, 6183, 6638, 6636);
  g->Binary(ynn_binary_multiply, 6635, 6636, 3081);
  g->Matmul(3081, 2181, 3082, false, false);
}

// Scope: "Layer19 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(3082, 3084, 1, 2);
  g->SplitDim(3084, 3083, 1, {1,8});
  g->FuseDims(3083, 3085, 2, 2);
  g->Binary(ynn_binary_divide, 3085, 7429, 3086);
  g->Unary(ynn_unary_round, 3086, 3087);
  g->Binary(ynn_binary_max, 3087, 7225, 3088);
  g->Binary(ynn_binary_min, 3088, 7340, 3090);
  g->Binary(ynn_binary_multiply, 3090, 7429, 3091);
  g->Convert(7878, 3092);
  g->Binary(ynn_binary_multiply, 3092, 7879, 3093);
  g->Matmul(3091, 3093, 3094, false, true);
  g->Binary(ynn_binary_divide, 3094, 7355, 3095);
  g->Unary(ynn_unary_round, 3095, 3096);
  g->Binary(ynn_binary_max, 3096, 7225, 3097);
  g->Binary(ynn_binary_min, 3097, 7340, 3098);
  g->Binary(ynn_binary_multiply, 3098, 7355, 3099);
}

// Scope: "Layer19 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3038, 3039);
  g->Reduce(ynn_reduce_sum, 3039, 6631, {2}, true);
  g->ShapeProduct(3039, 6630, {2});
  g->Binary(ynn_binary_divide, 6631, 6630, 3040);
  g->Binary(ynn_binary_add, 3040, 7373, 3041);
  g->Binary(ynn_binary_pow, 3041, 7428, 3042);
  g->Binary(ynn_binary_multiply, 3038, 3042, 3043);
  g->Convert(7862, 3045);
  g->Binary(ynn_binary_multiply, 3043, 3045, 3046);
  BuildLayer19AttentionQueryProjection(ctx);
  BuildLayer19AttentionSdpa(ctx);
  BuildLayer19AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 3099, 3101);
  g->Reduce(ynn_reduce_sum, 3101, 6640, {2}, true);
  g->ShapeProduct(3101, 6639, {2});
  g->Binary(ynn_binary_divide, 6640, 6639, 3102);
  g->Binary(ynn_binary_add, 3102, 7373, 3103);
  g->Binary(ynn_binary_pow, 3103, 7428, 3104);
  g->Binary(ynn_binary_multiply, 3099, 3104, 3105);
  g->Convert(7874, 3106);
  g->Binary(ynn_binary_multiply, 3105, 3106, 3107);
  g->Binary(ynn_binary_add, 3038, 3107, 3108);
}

// Scope: "Layer19 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3108, 3109);
  g->Reduce(ynn_reduce_sum, 3109, 6642, {2}, true);
  g->ShapeProduct(3109, 6641, {2});
  g->Binary(ynn_binary_divide, 6642, 6641, 3110);
  g->Binary(ynn_binary_add, 3110, 7373, 3114);
  g->Binary(ynn_binary_pow, 3114, 7428, 3115);
  g->Binary(ynn_binary_multiply, 3108, 3115, 3116);
  g->Convert(7877, 3117);
  g->Binary(ynn_binary_multiply, 3116, 3117, 3118);
  g->Binary(ynn_binary_divide, 3118, 7298, 3119);
  g->Unary(ynn_unary_round, 3119, 3120);
  g->Binary(ynn_binary_max, 3120, 7225, 3121);
  g->Binary(ynn_binary_min, 3121, 7340, 3122);
  g->Binary(ynn_binary_multiply, 3122, 7298, 3123);
  g->Convert(7868, 3125);
  g->Binary(ynn_binary_multiply, 3125, 7869, 3126);
  g->Matmul(3123, 3126, 3127, false, true);
  g->Binary(ynn_binary_divide, 3127, 7408, 3128);
  g->Unary(ynn_unary_round, 3128, 3129);
  g->Binary(ynn_binary_max, 3129, 7225, 3130);
  g->Binary(ynn_binary_min, 3130, 7340, 3131);
  g->Binary(ynn_binary_multiply, 3131, 7408, 3132);
  g->Convert(7866, 3134);
  g->Binary(ynn_binary_multiply, 3134, 7867, 3135);
  g->Matmul(3123, 3135, 3136, false, true);
  g->Binary(ynn_binary_divide, 3136, 7408, 3137);
  g->Unary(ynn_unary_round, 3137, 3138);
  g->Binary(ynn_binary_max, 3138, 7225, 3139);
  g->Binary(ynn_binary_min, 3139, 7340, 3140);
  g->Binary(ynn_binary_multiply, 3140, 7408, 3142);
  g->Polynomial(3142, 6645, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6645, 6646);
  g->Binary(ynn_binary_add, 6646, 6183, 6643);
  g->Binary(ynn_binary_multiply, 3142, 6181, 6644);
  g->Binary(ynn_binary_multiply, 6644, 6643, 3143);
  g->Binary(ynn_binary_multiply, 3132, 3143, 3144);
  g->Binary(ynn_binary_divide, 3144, 7334, 3145);
  g->Unary(ynn_unary_round, 3145, 3146);
  g->Binary(ynn_binary_max, 3146, 7225, 3147);
  g->Binary(ynn_binary_min, 3147, 7340, 3148);
  g->Binary(ynn_binary_multiply, 3148, 7334, 3149);
  g->Convert(7864, 3150);
  g->Binary(ynn_binary_multiply, 3150, 7865, 3151);
  g->Matmul(3149, 3151, 3153, false, true);
  g->Binary(ynn_binary_divide, 3153, 7329, 3154);
  g->Unary(ynn_unary_round, 3154, 3155);
  g->Binary(ynn_binary_max, 3155, 7225, 3156);
  g->Binary(ynn_binary_min, 3156, 7340, 3157);
  g->Binary(ynn_binary_multiply, 3157, 7329, 3158);
  g->Unary(ynn_unary_square, 3158, 3159);
  g->Reduce(ynn_reduce_sum, 3159, 6648, {2}, true);
  g->ShapeProduct(3159, 6647, {2});
  g->Binary(ynn_binary_divide, 6648, 6647, 3160);
  g->Binary(ynn_binary_add, 3160, 7373, 3161);
  g->Binary(ynn_binary_pow, 3161, 7428, 3162);
  g->Binary(ynn_binary_multiply, 3158, 3162, 3164);
  g->Convert(7875, 3165);
  g->Binary(ynn_binary_multiply, 3164, 3165, 3166);
  g->Binary(ynn_binary_add, 3108, 3166, 3167);
}

// Scope: "Layer19 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1031, 3168, {0,0,19,0}, {-1,-1,1,-1});
  g->Reshape(3168, 3169, {1,1,256});
  g->Binary(ynn_binary_add, 3169, 8420, 3170);
  g->Binary(ynn_binary_multiply, 3170, 7155, 3171);
  g->Binary(ynn_binary_divide, 3167, 7459, 3172);
  g->Unary(ynn_unary_round, 3172, 3173);
  g->Binary(ynn_binary_max, 3173, 7225, 3175);
  g->Binary(ynn_binary_min, 3175, 7340, 3176);
  g->Binary(ynn_binary_multiply, 3176, 7459, 3177);
  g->Convert(7870, 3178);
  g->Binary(ynn_binary_multiply, 3178, 7871, 3179);
  g->Matmul(3177, 3179, 3180, false, true);
  g->Binary(ynn_binary_divide, 3180, 7303, 3181);
  g->Unary(ynn_unary_round, 3181, 3182);
  g->Binary(ynn_binary_max, 3182, 7225, 3183);
  g->Binary(ynn_binary_min, 3183, 7340, 3184);
  g->Binary(ynn_binary_multiply, 3184, 7303, 3186);
  g->Polynomial(3186, 6651, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6651, 6652);
  g->Binary(ynn_binary_add, 6652, 6183, 6649);
  g->Binary(ynn_binary_multiply, 3186, 6181, 6650);
  g->Binary(ynn_binary_multiply, 6650, 6649, 3187);
  g->Binary(ynn_binary_multiply, 3187, 3171, 3188);
  g->Binary(ynn_binary_divide, 3188, 7467, 3189);
  g->Unary(ynn_unary_round, 3189, 3190);
  g->Binary(ynn_binary_max, 3190, 7225, 3191);
  g->Binary(ynn_binary_min, 3191, 7340, 3192);
  g->Binary(ynn_binary_multiply, 3192, 7467, 3193);
  g->Convert(7872, 3194);
  g->Binary(ynn_binary_multiply, 3194, 7873, 3195);
  g->Matmul(3193, 3195, 3197, false, true);
  g->Binary(ynn_binary_divide, 3197, 7379, 3198);
  g->Unary(ynn_unary_round, 3198, 3199);
  g->Binary(ynn_binary_max, 3199, 7225, 3200);
  g->Binary(ynn_binary_min, 3200, 7340, 3201);
  g->Binary(ynn_binary_multiply, 3201, 7379, 3202);
  g->Unary(ynn_unary_square, 3202, 3203);
  g->Reduce(ynn_reduce_sum, 3203, 6656, {2}, true);
  g->ShapeProduct(3203, 6655, {2});
  g->Binary(ynn_binary_divide, 6656, 6655, 3204);
  g->Binary(ynn_binary_add, 3204, 7373, 3205);
  g->Binary(ynn_binary_pow, 3205, 7428, 3206);
  g->Binary(ynn_binary_multiply, 3202, 3206, 3208);
  g->Convert(7876, 3209);
  g->Binary(ynn_binary_multiply, 3208, 3209, 3210);
  g->Binary(ynn_binary_add, 3167, 3210, 3211);
  g->Convert(7863, 3212);
  g->Binary(ynn_binary_multiply, 3211, 3212, 3213);
}

// Scope: "Layer19"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19(Context& ctx) {
  BuildLayer19Attention(ctx);
  BuildLayer19Mlp(ctx);
  BuildLayer19PerLayerEmbedding(ctx);
}

// Scope: "Layer20 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Binary(ynn_binary_divide, 3222, 7258, 3223);
  g->Unary(ynn_unary_round, 3223, 3224);
  g->Binary(ynn_binary_max, 3224, 7225, 3225);
  g->Binary(ynn_binary_min, 3225, 7340, 3226);
  g->Binary(ynn_binary_multiply, 3226, 7258, 3227);
  g->Convert(7928, 3228);
  g->Binary(ynn_binary_multiply, 3228, 7929, 3229);
  g->Matmul(3227, 3229, 3231, false, true);
  g->Binary(ynn_binary_divide, 3231, 7520, 3232);
  g->Unary(ynn_unary_round, 3232, 3233);
  g->Binary(ynn_binary_max, 3233, 7225, 3234);
  g->Binary(ynn_binary_min, 3234, 7340, 3235);
  g->Binary(ynn_binary_multiply, 3235, 7520, 3236);
  g->SplitDim(3236, 3237, 2, {8,256});
  g->FuseDims(3237, 3239, 1, 2);
  g->SplitDim(3239, 3238, 1, {8,1});
  g->Unary(ynn_unary_square, 3238, 3240);
  g->Reduce(ynn_reduce_sum, 3240, 6660, {3}, true);
  g->ShapeProduct(3240, 6659, {3});
  g->Binary(ynn_binary_divide, 6660, 6659, 3241);
  g->Binary(ynn_binary_add, 3241, 7373, 3243);
  g->Binary(ynn_binary_pow, 3243, 7428, 3244);
  g->Binary(ynn_binary_multiply, 3238, 3244, 3245);
  g->Convert(7927, 3246);
  g->Binary(ynn_binary_multiply, 3245, 3246, 3247);
  g->Slice(3247, 3248, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3247, 3249, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3249, 3250);
  g->Concat({3250,3248}, 3251, 3);
  g->Binary(ynn_binary_multiply, 3247, 2044, 3252);
  g->Binary(ynn_binary_multiply, 3251, 3111, 3254);
  g->Binary(ynn_binary_add, 3252, 3254, 3255);
}

// Scope: "Layer20 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(3255, 1963, 3256, false, true);
  g->Mask(3256, 7574, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 7574, 6664, {-1}, true);
  g->Binary(ynn_binary_subtract, 7574, 6664, 6661);
  g->Unary(ynn_unary_exp, 6661, 6662);
  g->Reduce(ynn_reduce_sum, 6662, 6665, {-1}, true);
  g->Binary(ynn_binary_divide, 6183, 6665, 6663);
  g->Binary(ynn_binary_multiply, 6662, 6663, 3257);
  g->Matmul(3257, 1965, 3258, false, false);
}

// Scope: "Layer20 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(3258, 3260, 1, 2);
  g->SplitDim(3260, 3259, 1, {1,8});
  g->FuseDims(3259, 3261, 2, 2);
  g->Binary(ynn_binary_divide, 3261, 7488, 3262);
  g->Unary(ynn_unary_round, 3262, 3263);
  g->Binary(ynn_binary_max, 3263, 7225, 3265);
  g->Binary(ynn_binary_min, 3265, 7340, 3266);
  g->Binary(ynn_binary_multiply, 3266, 7488, 3267);
  g->Convert(7925, 3268);
  g->Binary(ynn_binary_multiply, 3268, 7926, 3269);
  g->Matmul(3267, 3269, 3270, false, true);
  g->Binary(ynn_binary_divide, 3270, 7171, 3271);
  g->Unary(ynn_unary_round, 3271, 3272);
  g->Binary(ynn_binary_max, 3272, 7225, 3273);
  g->Binary(ynn_binary_min, 3273, 7340, 3274);
  g->Binary(ynn_binary_multiply, 3274, 7171, 3276);
}

// Scope: "Layer20 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3213, 3214);
  g->Reduce(ynn_reduce_sum, 3214, 6658, {2}, true);
  g->ShapeProduct(3214, 6657, {2});
  g->Binary(ynn_binary_divide, 6658, 6657, 3215);
  g->Binary(ynn_binary_add, 3215, 7373, 3216);
  g->Binary(ynn_binary_pow, 3216, 7428, 3217);
  g->Binary(ynn_binary_multiply, 3213, 3217, 3220);
  g->Convert(7909, 3221);
  g->Binary(ynn_binary_multiply, 3220, 3221, 3222);
  BuildLayer20AttentionQueryProjection(ctx);
  BuildLayer20AttentionSdpa(ctx);
  BuildLayer20AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 3276, 3277);
  g->Reduce(ynn_reduce_sum, 3277, 6667, {2}, true);
  g->ShapeProduct(3277, 6666, {2});
  g->Binary(ynn_binary_divide, 6667, 6666, 3278);
  g->Binary(ynn_binary_add, 3278, 7373, 3279);
  g->Binary(ynn_binary_pow, 3279, 7428, 3280);
  g->Binary(ynn_binary_multiply, 3276, 3280, 3281);
  g->Convert(7921, 3282);
  g->Binary(ynn_binary_multiply, 3281, 3282, 3283);
  g->Binary(ynn_binary_add, 3213, 3283, 3284);
}

// Scope: "Layer20 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3284, 3285);
  g->Reduce(ynn_reduce_sum, 3285, 6669, {2}, true);
  g->ShapeProduct(3285, 6668, {2});
  g->Binary(ynn_binary_divide, 6669, 6668, 3287);
  g->Binary(ynn_binary_add, 3287, 7373, 3288);
  g->Binary(ynn_binary_pow, 3288, 7428, 3289);
  g->Binary(ynn_binary_multiply, 3284, 3289, 3290);
  g->Convert(7924, 3291);
  g->Binary(ynn_binary_multiply, 3290, 3291, 3292);
  g->Binary(ynn_binary_divide, 3292, 7535, 3293);
  g->Unary(ynn_unary_round, 3293, 3294);
  g->Binary(ynn_binary_max, 3294, 7225, 3295);
  g->Binary(ynn_binary_min, 3295, 7340, 3296);
  g->Binary(ynn_binary_multiply, 3296, 7535, 3298);
  g->Convert(7915, 3299);
  g->Binary(ynn_binary_multiply, 3299, 7916, 3300);
  g->Matmul(3298, 3300, 3301, false, true);
  g->Binary(ynn_binary_divide, 3301, 7464, 3302);
  g->Unary(ynn_unary_round, 3302, 3303);
  g->Binary(ynn_binary_max, 3303, 7225, 3304);
  g->Binary(ynn_binary_min, 3304, 7340, 3305);
  g->Binary(ynn_binary_multiply, 3305, 7464, 3306);
  g->Convert(7913, 3308);
  g->Binary(ynn_binary_multiply, 3308, 7914, 3309);
  g->Matmul(3298, 3309, 3310, false, true);
  g->Binary(ynn_binary_divide, 3310, 7464, 3311);
  g->Unary(ynn_unary_round, 3311, 3312);
  g->Binary(ynn_binary_max, 3312, 7225, 3313);
  g->Binary(ynn_binary_min, 3313, 7340, 3315);
  g->Binary(ynn_binary_multiply, 3315, 7464, 3316);
  g->Polynomial(3316, 6672, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6672, 6673);
  g->Binary(ynn_binary_add, 6673, 6183, 6670);
  g->Binary(ynn_binary_multiply, 3316, 6181, 6671);
  g->Binary(ynn_binary_multiply, 6671, 6670, 3317);
  g->Binary(ynn_binary_multiply, 3306, 3317, 3318);
  g->Binary(ynn_binary_divide, 3318, 7411, 3319);
  g->Unary(ynn_unary_round, 3319, 3320);
  g->Binary(ynn_binary_max, 3320, 7225, 3321);
  g->Binary(ynn_binary_min, 3321, 7340, 3322);
  g->Binary(ynn_binary_multiply, 3322, 7411, 3323);
  g->Convert(7911, 3324);
  g->Binary(ynn_binary_multiply, 3324, 7912, 3327);
  g->Matmul(3323, 3327, 3328, false, true);
  g->Binary(ynn_binary_divide, 3328, 7239, 3329);
  g->Unary(ynn_unary_round, 3329, 3330);
  g->Binary(ynn_binary_max, 3330, 7225, 3331);
  g->Binary(ynn_binary_min, 3331, 7340, 3332);
  g->Binary(ynn_binary_multiply, 3332, 7239, 3333);
  g->Unary(ynn_unary_square, 3333, 3334);
  g->Reduce(ynn_reduce_sum, 3334, 6675, {2}, true);
  g->ShapeProduct(3334, 6674, {2});
  g->Binary(ynn_binary_divide, 6675, 6674, 3335);
  g->Binary(ynn_binary_add, 3335, 7373, 3336);
  g->Binary(ynn_binary_pow, 3336, 7428, 3338);
  g->Binary(ynn_binary_multiply, 3333, 3338, 3339);
  g->Convert(7922, 3340);
  g->Binary(ynn_binary_multiply, 3339, 3340, 3341);
  g->Binary(ynn_binary_add, 3284, 3341, 3342);
}

// Scope: "Layer20 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1031, 3343, {0,0,20,0}, {-1,-1,1,-1});
  g->Reshape(3343, 3344, {1,1,256});
  g->Binary(ynn_binary_add, 3344, 8422, 3345);
  g->Binary(ynn_binary_multiply, 3345, 7155, 3346);
  g->Binary(ynn_binary_divide, 3342, 7469, 3347);
  g->Unary(ynn_unary_round, 3347, 3349);
  g->Binary(ynn_binary_max, 3349, 7225, 3350);
  g->Binary(ynn_binary_min, 3350, 7340, 3351);
  g->Binary(ynn_binary_multiply, 3351, 7469, 3352);
  g->Convert(7917, 3353);
  g->Binary(ynn_binary_multiply, 3353, 7918, 3354);
  g->Matmul(3352, 3354, 3355, false, true);
  g->Binary(ynn_binary_divide, 3355, 7330, 3356);
  g->Unary(ynn_unary_round, 3356, 3357);
  g->Binary(ynn_binary_max, 3357, 7225, 3358);
  g->Binary(ynn_binary_min, 3358, 7340, 3360);
  g->Binary(ynn_binary_multiply, 3360, 7330, 3361);
  g->Polynomial(3361, 6678, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6678, 6679);
  g->Binary(ynn_binary_add, 6679, 6183, 6676);
  g->Binary(ynn_binary_multiply, 3361, 6181, 6677);
  g->Binary(ynn_binary_multiply, 6677, 6676, 3362);
  g->Binary(ynn_binary_multiply, 3362, 3346, 3363);
  g->Binary(ynn_binary_divide, 3363, 7292, 3364);
  g->Unary(ynn_unary_round, 3364, 3365);
  g->Binary(ynn_binary_max, 3365, 7225, 3366);
  g->Binary(ynn_binary_min, 3366, 7340, 3367);
  g->Binary(ynn_binary_multiply, 3367, 7292, 3368);
  g->Convert(7919, 3369);
  g->Binary(ynn_binary_multiply, 3369, 7920, 3371);
  g->Matmul(3368, 3371, 3372, false, true);
  g->Binary(ynn_binary_divide, 3372, 7151, 3373);
  g->Unary(ynn_unary_round, 3373, 3374);
  g->Binary(ynn_binary_max, 3374, 7225, 3375);
  g->Binary(ynn_binary_min, 3375, 7340, 3376);
  g->Binary(ynn_binary_multiply, 3376, 7151, 3377);
  g->Unary(ynn_unary_square, 3377, 3378);
  g->Reduce(ynn_reduce_sum, 3378, 6681, {2}, true);
  g->ShapeProduct(3378, 6680, {2});
  g->Binary(ynn_binary_divide, 6681, 6680, 3379);
  g->Binary(ynn_binary_add, 3379, 7373, 3380);
  g->Binary(ynn_binary_pow, 3380, 7428, 3382);
  g->Binary(ynn_binary_multiply, 3377, 3382, 3383);
  g->Convert(7923, 3384);
  g->Binary(ynn_binary_multiply, 3383, 3384, 3385);
  g->Binary(ynn_binary_add, 3342, 3385, 3386);
  g->Convert(7910, 3387);
  g->Binary(ynn_binary_multiply, 3386, 3387, 3388);
}

// Scope: "Layer20"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20(Context& ctx) {
  BuildLayer20Attention(ctx);
  BuildLayer20Mlp(ctx);
  BuildLayer20PerLayerEmbedding(ctx);
}

// Scope: "Layer21 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Binary(ynn_binary_divide, 3396, 7251, 3397);
  g->Unary(ynn_unary_round, 3397, 3398);
  g->Binary(ynn_binary_max, 3398, 7225, 3399);
  g->Binary(ynn_binary_min, 3399, 7340, 3400);
  g->Binary(ynn_binary_multiply, 3400, 7251, 3401);
  g->Convert(7949, 3402);
  g->Binary(ynn_binary_multiply, 3402, 7950, 3404);
  g->Matmul(3401, 3404, 3405, false, true);
  g->Binary(ynn_binary_divide, 3405, 7205, 3406);
  g->Unary(ynn_unary_round, 3406, 3407);
  g->Binary(ynn_binary_max, 3407, 7225, 3408);
  g->Binary(ynn_binary_min, 3408, 7340, 3409);
  g->Binary(ynn_binary_multiply, 3409, 7205, 3410);
  g->SplitDim(3410, 3411, 2, {8,256});
  g->FuseDims(3411, 3413, 1, 2);
  g->SplitDim(3413, 3412, 1, {8,1});
  g->Unary(ynn_unary_square, 3412, 3414);
  g->Reduce(ynn_reduce_sum, 3414, 6685, {3}, true);
  g->ShapeProduct(3414, 6684, {3});
  g->Binary(ynn_binary_divide, 6685, 6684, 3416);
  g->Binary(ynn_binary_add, 3416, 7373, 3417);
  g->Binary(ynn_binary_pow, 3417, 7428, 3418);
  g->Binary(ynn_binary_multiply, 3412, 3418, 3419);
  g->Convert(7948, 3420);
  g->Binary(ynn_binary_multiply, 3419, 3420, 3421);
  g->Slice(3421, 3422, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3421, 3423, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3423, 3424);
  g->Concat({3424,3422}, 3425, 3);
  g->Binary(ynn_binary_multiply, 3421, 2044, 3427);
  g->Binary(ynn_binary_multiply, 3425, 3111, 3428);
  g->Binary(ynn_binary_add, 3427, 3428, 3429);
}

// Scope: "Layer21 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(3429, 1963, 3430, false, true);
  g->Mask(3430, 7575, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 7575, 6689, {-1}, true);
  g->Binary(ynn_binary_subtract, 7575, 6689, 6686);
  g->Unary(ynn_unary_exp, 6686, 6687);
  g->Reduce(ynn_reduce_sum, 6687, 6690, {-1}, true);
  g->Binary(ynn_binary_divide, 6183, 6690, 6688);
  g->Binary(ynn_binary_multiply, 6687, 6688, 3431);
  g->Matmul(3431, 1965, 3432, false, false);
}

// Scope: "Layer21 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(3432, 3434, 1, 2);
  g->SplitDim(3434, 3433, 1, {1,8});
  g->FuseDims(3433, 3435, 2, 2);
  g->Binary(ynn_binary_divide, 3435, 7234, 3436);
  g->Unary(ynn_unary_round, 3436, 3439);
  g->Binary(ynn_binary_max, 3439, 7225, 3440);
  g->Binary(ynn_binary_min, 3440, 7340, 3441);
  g->Binary(ynn_binary_multiply, 3441, 7234, 3442);
  g->Convert(7946, 3443);
  g->Binary(ynn_binary_multiply, 3443, 7947, 3444);
  g->Matmul(3442, 3444, 3445, false, true);
  g->Binary(ynn_binary_divide, 3445, 7415, 3446);
  g->Unary(ynn_unary_round, 3446, 3447);
  g->Binary(ynn_binary_max, 3447, 7225, 3448);
  g->Binary(ynn_binary_min, 3448, 7340, 3450);
  g->Binary(ynn_binary_multiply, 3450, 7415, 3451);
}

// Scope: "Layer21 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3388, 3389);
  g->Reduce(ynn_reduce_sum, 3389, 6683, {2}, true);
  g->ShapeProduct(3389, 6682, {2});
  g->Binary(ynn_binary_divide, 6683, 6682, 3390);
  g->Binary(ynn_binary_add, 3390, 7373, 3391);
  g->Binary(ynn_binary_pow, 3391, 7428, 3393);
  g->Binary(ynn_binary_multiply, 3388, 3393, 3394);
  g->Convert(7930, 3395);
  g->Binary(ynn_binary_multiply, 3394, 3395, 3396);
  BuildLayer21AttentionQueryProjection(ctx);
  BuildLayer21AttentionSdpa(ctx);
  BuildLayer21AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 3451, 3452);
  g->Reduce(ynn_reduce_sum, 3452, 6692, {2}, true);
  g->ShapeProduct(3452, 6691, {2});
  g->Binary(ynn_binary_divide, 6692, 6691, 3453);
  g->Binary(ynn_binary_add, 3453, 7373, 3454);
  g->Binary(ynn_binary_pow, 3454, 7428, 3455);
  g->Binary(ynn_binary_multiply, 3451, 3455, 3456);
  g->Convert(7942, 3457);
  g->Binary(ynn_binary_multiply, 3456, 3457, 3458);
  g->Binary(ynn_binary_add, 3388, 3458, 3459);
}

// Scope: "Layer21 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3459, 3461);
  g->Reduce(ynn_reduce_sum, 3461, 6698, {2}, true);
  g->ShapeProduct(3461, 6697, {2});
  g->Binary(ynn_binary_divide, 6698, 6697, 3462);
  g->Binary(ynn_binary_add, 3462, 7373, 3463);
  g->Binary(ynn_binary_pow, 3463, 7428, 3464);
  g->Binary(ynn_binary_multiply, 3459, 3464, 3465);
  g->Convert(7945, 3466);
  g->Binary(ynn_binary_multiply, 3465, 3466, 3467);
  g->Binary(ynn_binary_divide, 3467, 7540, 3468);
  g->Unary(ynn_unary_round, 3468, 3469);
  g->Binary(ynn_binary_max, 3469, 7225, 3470);
  g->Binary(ynn_binary_min, 3470, 7340, 3472);
  g->Binary(ynn_binary_multiply, 3472, 7540, 3473);
  g->Convert(7936, 3474);
  g->Binary(ynn_binary_multiply, 3474, 7937, 3475);
  g->Matmul(3473, 3475, 3476, false, true);
  g->Binary(ynn_binary_divide, 3476, 7190, 3477);
  g->Unary(ynn_unary_round, 3477, 3478);
  g->Binary(ynn_binary_max, 3478, 7225, 3479);
  g->Binary(ynn_binary_min, 3479, 7340, 3480);
  g->Binary(ynn_binary_multiply, 3480, 7190, 3481);
  g->Convert(7934, 3483);
  g->Binary(ynn_binary_multiply, 3483, 7935, 3484);
  g->Matmul(3473, 3484, 3485, false, true);
  g->Binary(ynn_binary_divide, 3485, 7190, 3486);
  g->Unary(ynn_unary_round, 3486, 3487);
  g->Binary(ynn_binary_max, 3487, 7225, 3489);
  g->Binary(ynn_binary_min, 3489, 7340, 3490);
  g->Binary(ynn_binary_multiply, 3490, 7190, 3491);
  g->Polynomial(3491, 6701, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6701, 6702);
  g->Binary(ynn_binary_add, 6702, 6183, 6699);
  g->Binary(ynn_binary_multiply, 3491, 6181, 6700);
  g->Binary(ynn_binary_multiply, 6700, 6699, 3492);
  g->Binary(ynn_binary_multiply, 3481, 3492, 3493);
  g->Binary(ynn_binary_divide, 3493, 7208, 3494);
  g->Unary(ynn_unary_round, 3494, 3495);
  g->Binary(ynn_binary_max, 3495, 7225, 3496);
  g->Binary(ynn_binary_min, 3496, 7340, 3497);
  g->Binary(ynn_binary_multiply, 3497, 7208, 3498);
  g->Convert(7932, 3500);
  g->Binary(ynn_binary_multiply, 3500, 7933, 3501);
  g->Matmul(3498, 3501, 3502, false, true);
  g->Binary(ynn_binary_divide, 3502, 7466, 3503);
  g->Unary(ynn_unary_round, 3503, 3504);
  g->Binary(ynn_binary_max, 3504, 7225, 3505);
  g->Binary(ynn_binary_min, 3505, 7340, 3506);
  g->Binary(ynn_binary_multiply, 3506, 7466, 3507);
  g->Unary(ynn_unary_square, 3507, 3508);
  g->Reduce(ynn_reduce_sum, 3508, 6704, {2}, true);
  g->ShapeProduct(3508, 6703, {2});
  g->Binary(ynn_binary_divide, 6704, 6703, 3509);
  g->Binary(ynn_binary_add, 3509, 7373, 3511);
  g->Binary(ynn_binary_pow, 3511, 7428, 3512);
  g->Binary(ynn_binary_multiply, 3507, 3512, 3513);
  g->Convert(7943, 3514);
  g->Binary(ynn_binary_multiply, 3513, 3514, 3515);
  g->Binary(ynn_binary_add, 3459, 3515, 3516);
}

// Scope: "Layer21 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1031, 3517, {0,0,21,0}, {-1,-1,1,-1});
  g->Reshape(3517, 3518, {1,1,256});
  g->Binary(ynn_binary_add, 3518, 8423, 3519);
  g->Binary(ynn_binary_multiply, 3519, 7155, 3520);
  g->Binary(ynn_binary_divide, 3516, 7536, 3522);
  g->Unary(ynn_unary_round, 3522, 3523);
  g->Binary(ynn_binary_max, 3523, 7225, 3524);
  g->Binary(ynn_binary_min, 3524, 7340, 3525);
  g->Binary(ynn_binary_multiply, 3525, 7536, 3526);
  g->Convert(7938, 3527);
  g->Binary(ynn_binary_multiply, 3527, 7939, 3528);
  g->Matmul(3526, 3528, 3529, false, true);
  g->Binary(ynn_binary_divide, 3529, 7337, 3530);
  g->Unary(ynn_unary_round, 3530, 3531);
  g->Binary(ynn_binary_max, 3531, 7225, 3533);
  g->Binary(ynn_binary_min, 3533, 7340, 3534);
  g->Binary(ynn_binary_multiply, 3534, 7337, 3535);
  g->Polynomial(3535, 6707, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6707, 6708);
  g->Binary(ynn_binary_add, 6708, 6183, 6705);
  g->Binary(ynn_binary_multiply, 3535, 6181, 6706);
  g->Binary(ynn_binary_multiply, 6706, 6705, 3536);
  g->Binary(ynn_binary_multiply, 3536, 3520, 3537);
  g->Binary(ynn_binary_divide, 3537, 7470, 3538);
  g->Unary(ynn_unary_round, 3538, 3539);
  g->Binary(ynn_binary_max, 3539, 7225, 3540);
  g->Binary(ynn_binary_min, 3540, 7340, 3541);
  g->Binary(ynn_binary_multiply, 3541, 7470, 3542);
  g->Convert(7940, 3545);
  g->Binary(ynn_binary_multiply, 3545, 7941, 3546);
  g->Matmul(3542, 3546, 3547, false, true);
  g->Binary(ynn_binary_divide, 3547, 7463, 3548);
  g->Unary(ynn_unary_round, 3548, 3549);
  g->Binary(ynn_binary_max, 3549, 7225, 3550);
  g->Binary(ynn_binary_min, 3550, 7340, 3551);
  g->Binary(ynn_binary_multiply, 3551, 7463, 3552);
  g->Unary(ynn_unary_square, 3552, 3553);
  g->Reduce(ynn_reduce_sum, 3553, 6712, {2}, true);
  g->ShapeProduct(3553, 6711, {2});
  g->Binary(ynn_binary_divide, 6712, 6711, 3554);
  g->Binary(ynn_binary_add, 3554, 7373, 3556);
  g->Binary(ynn_binary_pow, 3556, 7428, 3557);
  g->Binary(ynn_binary_multiply, 3552, 3557, 3558);
  g->Convert(7944, 3559);
  g->Binary(ynn_binary_multiply, 3558, 3559, 3560);
  g->Binary(ynn_binary_add, 3516, 3560, 3561);
  g->Convert(7931, 3562);
  g->Binary(ynn_binary_multiply, 3561, 3562, 3563);
}

// Scope: "Layer21"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21(Context& ctx) {
  BuildLayer21Attention(ctx);
  BuildLayer21Mlp(ctx);
  BuildLayer21PerLayerEmbedding(ctx);
}

// Scope: "Layer22 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Binary(ynn_binary_divide, 3571, 7328, 3572);
  g->Unary(ynn_unary_round, 3572, 3573);
  g->Binary(ynn_binary_max, 3573, 7225, 3574);
  g->Binary(ynn_binary_min, 3574, 7340, 3575);
  g->Binary(ynn_binary_multiply, 3575, 7328, 3576);
  g->Convert(7970, 3578);
  g->Binary(ynn_binary_multiply, 3578, 7971, 3579);
  g->Matmul(3576, 3579, 3580, false, true);
  g->Binary(ynn_binary_divide, 3580, 7255, 3581);
  g->Unary(ynn_unary_round, 3581, 3582);
  g->Binary(ynn_binary_max, 3582, 7225, 3583);
  g->Binary(ynn_binary_min, 3583, 7340, 3584);
  g->Binary(ynn_binary_multiply, 3584, 7255, 3585);
  g->SplitDim(3585, 3586, 2, {8,256});
  g->FuseDims(3586, 3588, 1, 2);
  g->SplitDim(3588, 3587, 1, {8,1});
  g->Unary(ynn_unary_square, 3587, 3590);
  g->Reduce(ynn_reduce_sum, 3590, 6716, {3}, true);
  g->ShapeProduct(3590, 6715, {3});
  g->Binary(ynn_binary_divide, 6716, 6715, 3591);
  g->Binary(ynn_binary_add, 3591, 7373, 3592);
  g->Binary(ynn_binary_pow, 3592, 7428, 3593);
  g->Binary(ynn_binary_multiply, 3587, 3593, 3594);
  g->Convert(7969, 3595);
  g->Binary(ynn_binary_multiply, 3594, 3595, 3596);
  g->Slice(3596, 3597, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3596, 3598, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3598, 3599);
  g->Concat({3599,3597}, 3601, 3);
  g->Binary(ynn_binary_multiply, 3596, 2044, 3602);
  g->Binary(ynn_binary_multiply, 3601, 3111, 3603);
  g->Binary(ynn_binary_add, 3602, 3603, 3604);
}

// Scope: "Layer22 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(3604, 1963, 3605, false, true);
  g->Mask(3605, 7576, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 7576, 6720, {-1}, true);
  g->Binary(ynn_binary_subtract, 7576, 6720, 6717);
  g->Unary(ynn_unary_exp, 6717, 6718);
  g->Reduce(ynn_reduce_sum, 6718, 6721, {-1}, true);
  g->Binary(ynn_binary_divide, 6183, 6721, 6719);
  g->Binary(ynn_binary_multiply, 6718, 6719, 3606);
  g->Matmul(3606, 1965, 3607, false, false);
}

// Scope: "Layer22 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(3607, 3609, 1, 2);
  g->SplitDim(3609, 3608, 1, {1,8});
  g->FuseDims(3608, 3610, 2, 2);
  g->Binary(ynn_binary_divide, 3610, 7332, 3612);
  g->Unary(ynn_unary_round, 3612, 3613);
  g->Binary(ynn_binary_max, 3613, 7225, 3614);
  g->Binary(ynn_binary_min, 3614, 7340, 3615);
  g->Binary(ynn_binary_multiply, 3615, 7332, 3616);
  g->Convert(7967, 3617);
  g->Binary(ynn_binary_multiply, 3617, 7968, 3618);
  g->Matmul(3616, 3618, 3619, false, true);
  g->Binary(ynn_binary_divide, 3619, 7527, 3620);
  g->Unary(ynn_unary_round, 3620, 3621);
  g->Binary(ynn_binary_max, 3621, 7225, 3623);
  g->Binary(ynn_binary_min, 3623, 7340, 3624);
  g->Binary(ynn_binary_multiply, 3624, 7527, 3625);
}

// Scope: "Layer22 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3563, 3564);
  g->Reduce(ynn_reduce_sum, 3564, 6714, {2}, true);
  g->ShapeProduct(3564, 6713, {2});
  g->Binary(ynn_binary_divide, 6714, 6713, 3565);
  g->Binary(ynn_binary_add, 3565, 7373, 3567);
  g->Binary(ynn_binary_pow, 3567, 7428, 3568);
  g->Binary(ynn_binary_multiply, 3563, 3568, 3569);
  g->Convert(7951, 3570);
  g->Binary(ynn_binary_multiply, 3569, 3570, 3571);
  BuildLayer22AttentionQueryProjection(ctx);
  BuildLayer22AttentionSdpa(ctx);
  BuildLayer22AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 3625, 3626);
  g->Reduce(ynn_reduce_sum, 3626, 6723, {2}, true);
  g->ShapeProduct(3626, 6722, {2});
  g->Binary(ynn_binary_divide, 6723, 6722, 3627);
  g->Binary(ynn_binary_add, 3627, 7373, 3628);
  g->Binary(ynn_binary_pow, 3628, 7428, 3629);
  g->Binary(ynn_binary_multiply, 3625, 3629, 3630);
  g->Convert(7963, 3631);
  g->Binary(ynn_binary_multiply, 3630, 3631, 3632);
  g->Binary(ynn_binary_add, 3563, 3632, 3634);
}

// Scope: "Layer22 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3634, 3635);
  g->Reduce(ynn_reduce_sum, 3635, 6727, {2}, true);
  g->ShapeProduct(3635, 6726, {2});
  g->Binary(ynn_binary_divide, 6727, 6726, 3636);
  g->Binary(ynn_binary_add, 3636, 7373, 3637);
  g->Binary(ynn_binary_pow, 3637, 7428, 3638);
  g->Binary(ynn_binary_multiply, 3634, 3638, 3639);
  g->Convert(7966, 3640);
  g->Binary(ynn_binary_multiply, 3639, 3640, 3641);
  g->Binary(ynn_binary_divide, 3641, 7210, 3642);
  g->Unary(ynn_unary_round, 3642, 3643);
  g->Binary(ynn_binary_max, 3643, 7225, 3645);
  g->Binary(ynn_binary_min, 3645, 7340, 3646);
  g->Binary(ynn_binary_multiply, 3646, 7210, 3647);
  g->Convert(7957, 3648);
  g->Binary(ynn_binary_multiply, 3648, 7958, 3649);
  g->Matmul(3647, 3649, 3650, false, true);
  g->Binary(ynn_binary_divide, 3650, 7294, 3651);
  g->Unary(ynn_unary_round, 3651, 3652);
  g->Binary(ynn_binary_max, 3652, 7225, 3653);
  g->Binary(ynn_binary_min, 3653, 7340, 3654);
  g->Binary(ynn_binary_multiply, 3654, 7294, 3657);
  g->Convert(7955, 3658);
  g->Binary(ynn_binary_multiply, 3658, 7956, 3659);
  g->Matmul(3647, 3659, 3660, false, true);
  g->Binary(ynn_binary_divide, 3660, 7294, 3661);
  g->Unary(ynn_unary_round, 3661, 3663);
  g->Binary(ynn_binary_max, 3663, 7225, 3664);
  g->Binary(ynn_binary_min, 3664, 7340, 3665);
  g->Binary(ynn_binary_multiply, 3665, 7294, 3666);
  g->Polynomial(3666, 6730, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6730, 6731);
  g->Binary(ynn_binary_add, 6731, 6183, 6728);
  g->Binary(ynn_binary_multiply, 3666, 6181, 6729);
  g->Binary(ynn_binary_multiply, 6729, 6728, 3667);
  g->Binary(ynn_binary_multiply, 3657, 3667, 3668);
  g->Binary(ynn_binary_divide, 3668, 7224, 3669);
  g->Unary(ynn_unary_round, 3669, 3670);
  g->Binary(ynn_binary_max, 3670, 7225, 3671);
  g->Binary(ynn_binary_min, 3671, 7340, 3672);
  g->Binary(ynn_binary_multiply, 3672, 7224, 3674);
  g->Convert(7953, 3675);
  g->Binary(ynn_binary_multiply, 3675, 7954, 3676);
  g->Matmul(3674, 3676, 3677, false, true);
  g->Binary(ynn_binary_divide, 3677, 7534, 3678);
  g->Unary(ynn_unary_round, 3678, 3679);
  g->Binary(ynn_binary_max, 3679, 7225, 3680);
  g->Binary(ynn_binary_min, 3680, 7340, 3681);
  g->Binary(ynn_binary_multiply, 3681, 7534, 3682);
  g->Unary(ynn_unary_square, 3682, 3683);
  g->Reduce(ynn_reduce_sum, 3683, 6733, {2}, true);
  g->ShapeProduct(3683, 6732, {2});
  g->Binary(ynn_binary_divide, 6733, 6732, 3685);
  g->Binary(ynn_binary_add, 3685, 7373, 3686);
  g->Binary(ynn_binary_pow, 3686, 7428, 3687);
  g->Binary(ynn_binary_multiply, 3682, 3687, 3688);
  g->Convert(7964, 3689);
  g->Binary(ynn_binary_multiply, 3688, 3689, 3690);
  g->Binary(ynn_binary_add, 3634, 3690, 3691);
}

// Scope: "Layer22 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1031, 3692, {0,0,22,0}, {-1,-1,1,-1});
  g->Reshape(3692, 3693, {1,1,256});
  g->Binary(ynn_binary_add, 3693, 8424, 3694);
  g->Binary(ynn_binary_multiply, 3694, 7155, 3696);
  g->Binary(ynn_binary_divide, 3691, 7218, 3697);
  g->Unary(ynn_unary_round, 3697, 3698);
  g->Binary(ynn_binary_max, 3698, 7225, 3699);
  g->Binary(ynn_binary_min, 3699, 7340, 3700);
  g->Binary(ynn_binary_multiply, 3700, 7218, 3701);
  g->Convert(7959, 3702);
  g->Binary(ynn_binary_multiply, 3702, 7960, 3703);
  g->Matmul(3701, 3703, 3704, false, true);
  g->Binary(ynn_binary_divide, 3704, 7325, 3705);
  g->Unary(ynn_unary_round, 3705, 3707);
  g->Binary(ynn_binary_max, 3707, 7225, 3708);
  g->Binary(ynn_binary_min, 3708, 7340, 3709);
  g->Binary(ynn_binary_multiply, 3709, 7325, 3710);
  g->Polynomial(3710, 6736, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6736, 6737);
  g->Binary(ynn_binary_add, 6737, 6183, 6734);
  g->Binary(ynn_binary_multiply, 3710, 6181, 6735);
  g->Binary(ynn_binary_multiply, 6735, 6734, 3711);
  g->Binary(ynn_binary_multiply, 3711, 3696, 3712);
  g->Binary(ynn_binary_divide, 3712, 7419, 3713);
  g->Unary(ynn_unary_round, 3713, 3714);
  g->Binary(ynn_binary_max, 3714, 7225, 3715);
  g->Binary(ynn_binary_min, 3715, 7340, 3716);
  g->Binary(ynn_binary_multiply, 3716, 7419, 3718);
  g->Convert(7961, 3719);
  g->Binary(ynn_binary_multiply, 3719, 7962, 3720);
  g->Matmul(3718, 3720, 3721, false, true);
  g->Binary(ynn_binary_divide, 3721, 7257, 3722);
  g->Unary(ynn_unary_round, 3722, 3723);
  g->Binary(ynn_binary_max, 3723, 7225, 3724);
  g->Binary(ynn_binary_min, 3724, 7340, 3725);
  g->Binary(ynn_binary_multiply, 3725, 7257, 3726);
  g->Unary(ynn_unary_square, 3726, 3727);
  g->Reduce(ynn_reduce_sum, 3727, 6739, {2}, true);
  g->ShapeProduct(3727, 6738, {2});
  g->Binary(ynn_binary_divide, 6739, 6738, 3729);
  g->Binary(ynn_binary_add, 3729, 7373, 3730);
  g->Binary(ynn_binary_pow, 3730, 7428, 3731);
  g->Binary(ynn_binary_multiply, 3726, 3731, 3732);
  g->Convert(7965, 3733);
  g->Binary(ynn_binary_multiply, 3732, 3733, 3734);
  g->Binary(ynn_binary_add, 3691, 3734, 3735);
  g->Convert(7952, 3736);
  g->Binary(ynn_binary_multiply, 3735, 3736, 3737);
}

// Scope: "Layer22"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22(Context& ctx) {
  BuildLayer22Attention(ctx);
  BuildLayer22Mlp(ctx);
  BuildLayer22PerLayerEmbedding(ctx);
}

// Scope: "Layer23 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Binary(ynn_binary_divide, 3745, 7269, 3746);
  g->Unary(ynn_unary_round, 3746, 3747);
  g->Binary(ynn_binary_max, 3747, 7225, 3748);
  g->Binary(ynn_binary_min, 3748, 7340, 3749);
  g->Binary(ynn_binary_multiply, 3749, 7269, 3751);
  g->Convert(7991, 3752);
  g->Binary(ynn_binary_multiply, 3752, 7992, 3753);
  g->Matmul(3751, 3753, 3754, false, true);
  g->Binary(ynn_binary_divide, 3754, 7523, 3755);
  g->Unary(ynn_unary_round, 3755, 3756);
  g->Binary(ynn_binary_max, 3756, 7225, 3757);
  g->Binary(ynn_binary_min, 3757, 7340, 3758);
  g->Binary(ynn_binary_multiply, 3758, 7523, 3759);
  g->SplitDim(3759, 3760, 2, {8,256});
  g->FuseDims(3760, 3764, 1, 2);
  g->SplitDim(3764, 3763, 1, {8,1});
  g->Unary(ynn_unary_square, 3763, 3765);
  g->Reduce(ynn_reduce_sum, 3765, 6745, {3}, true);
  g->ShapeProduct(3765, 6744, {3});
  g->Binary(ynn_binary_divide, 6745, 6744, 3766);
  g->Binary(ynn_binary_add, 3766, 7373, 3767);
  g->Binary(ynn_binary_pow, 3767, 7428, 3768);
  g->Binary(ynn_binary_multiply, 3763, 3768, 3769);
  g->Convert(7990, 3770);
  g->Binary(ynn_binary_multiply, 3769, 3770, 3771);
  g->Slice(3771, 3772, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3771, 3773, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3773, 3775);
  g->Concat({3775,3772}, 3776, 3);
  g->Binary(ynn_binary_multiply, 3771, 2044, 3777);
  g->Binary(ynn_binary_multiply, 3776, 3111, 3778);
  g->Binary(ynn_binary_add, 3777, 3778, 3779);
}

// Scope: "Layer23 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(3779, 1963, 3780, false, true);
  g->Mask(3780, 7577, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 7577, 6749, {-1}, true);
  g->Binary(ynn_binary_subtract, 7577, 6749, 6746);
  g->Unary(ynn_unary_exp, 6746, 6747);
  g->Reduce(ynn_reduce_sum, 6747, 6750, {-1}, true);
  g->Binary(ynn_binary_divide, 6183, 6750, 6748);
  g->Binary(ynn_binary_multiply, 6747, 6748, 3781);
  g->Matmul(3781, 1965, 3782, false, false);
}

// Scope: "Layer23 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->FuseDims(3782, 3784, 1, 2);
  g->SplitDim(3784, 3783, 1, {1,8});
  g->FuseDims(3783, 3786, 2, 2);
  g->Binary(ynn_binary_divide, 3786, 7488, 3787);
  g->Unary(ynn_unary_round, 3787, 3788);
  g->Binary(ynn_binary_max, 3788, 7225, 3789);
  g->Binary(ynn_binary_min, 3789, 7340, 3790);
  g->Binary(ynn_binary_multiply, 3790, 7488, 3791);
  g->Convert(7988, 3792);
  g->Binary(ynn_binary_multiply, 3792, 7989, 3793);
  g->Matmul(3791, 3793, 3794, false, true);
  g->Binary(ynn_binary_divide, 3794, 7402, 3795);
  g->Unary(ynn_unary_round, 3795, 3797);
  g->Binary(ynn_binary_max, 3797, 7225, 3798);
  g->Binary(ynn_binary_min, 3798, 7340, 3799);
  g->Binary(ynn_binary_multiply, 3799, 7402, 3800);
}

// Scope: "Layer23 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3737, 3738);
  g->Reduce(ynn_reduce_sum, 3738, 6743, {2}, true);
  g->ShapeProduct(3738, 6742, {2});
  g->Binary(ynn_binary_divide, 6743, 6742, 3740);
  g->Binary(ynn_binary_add, 3740, 7373, 3741);
  g->Binary(ynn_binary_pow, 3741, 7428, 3742);
  g->Binary(ynn_binary_multiply, 3737, 3742, 3743);
  g->Convert(7972, 3744);
  g->Binary(ynn_binary_multiply, 3743, 3744, 3745);
  BuildLayer23AttentionQueryProjection(ctx);
  BuildLayer23AttentionSdpa(ctx);
  BuildLayer23AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 3800, 3801);
  g->Reduce(ynn_reduce_sum, 3801, 6752, {2}, true);
  g->ShapeProduct(3801, 6751, {2});
  g->Binary(ynn_binary_divide, 6752, 6751, 3802);
  g->Binary(ynn_binary_add, 3802, 7373, 3803);
  g->Binary(ynn_binary_pow, 3803, 7428, 3804);
  g->Binary(ynn_binary_multiply, 3800, 3804, 3805);
  g->Convert(7984, 3806);
  g->Binary(ynn_binary_multiply, 3805, 3806, 3808);
  g->Binary(ynn_binary_add, 3737, 3808, 3809);
}

// Scope: "Layer23 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3809, 3810);
  g->Reduce(ynn_reduce_sum, 3810, 6754, {2}, true);
  g->ShapeProduct(3810, 6753, {2});
  g->Binary(ynn_binary_divide, 6754, 6753, 3811);
  g->Binary(ynn_binary_add, 3811, 7373, 3812);
  g->Binary(ynn_binary_pow, 3812, 7428, 3813);
  g->Binary(ynn_binary_multiply, 3809, 3813, 3814);
  g->Convert(7987, 3815);
  g->Binary(ynn_binary_multiply, 3814, 3815, 3816);
  g->Binary(ynn_binary_divide, 3816, 7267, 3817);
  g->Unary(ynn_unary_round, 3817, 3819);
  g->Binary(ynn_binary_max, 3819, 7225, 3820);
  g->Binary(ynn_binary_min, 3820, 7340, 3821);
  g->Binary(ynn_binary_multiply, 3821, 7267, 3822);
  g->Convert(7978, 3823);
  g->Binary(ynn_binary_multiply, 3823, 7979, 3824);
  g->Matmul(3822, 3824, 3825, false, true);
  g->Binary(ynn_binary_divide, 3825, 7433, 3826);
  g->Unary(ynn_unary_round, 3826, 3827);
  g->Binary(ynn_binary_max, 3827, 7225, 3828);
  g->Binary(ynn_binary_min, 3828, 7340, 3830);
  g->Binary(ynn_binary_multiply, 3830, 7433, 3831);
  g->Convert(7976, 3832);
  g->Binary(ynn_binary_multiply, 3832, 7977, 3833);
  g->Matmul(3822, 3833, 3834, false, true);
  g->Binary(ynn_binary_divide, 3834, 7433, 3836);
  g->Unary(ynn_unary_round, 3836, 3837);
  g->Binary(ynn_binary_max, 3837, 7225, 3838);
  g->Binary(ynn_binary_min, 3838, 7340, 3839);
  g->Binary(ynn_binary_multiply, 3839, 7433, 3840);
  g->Polynomial(3840, 6757, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6757, 6758);
  g->Binary(ynn_binary_add, 6758, 6183, 6755);
  g->Binary(ynn_binary_multiply, 3840, 6181, 6756);
  g->Binary(ynn_binary_multiply, 6756, 6755, 3841);
  g->Binary(ynn_binary_multiply, 3831, 3841, 3842);
  g->Binary(ynn_binary_divide, 3842, 7524, 3843);
  g->Unary(ynn_unary_round, 3843, 3844);
  g->Binary(ynn_binary_max, 3844, 7225, 3845);
  g->Binary(ynn_binary_min, 3845, 7340, 3847);
  g->Binary(ynn_binary_multiply, 3847, 7524, 3848);
  g->Convert(7974, 3849);
  g->Binary(ynn_binary_multiply, 3849, 7975, 3850);
  g->Matmul(3848, 3850, 3851, false, true);
  g->Binary(ynn_binary_divide, 3851, 7477, 3852);
  g->Unary(ynn_unary_round, 3852, 3853);
  g->Binary(ynn_binary_max, 3853, 7225, 3854);
  g->Binary(ynn_binary_min, 3854, 7340, 3855);
  g->Binary(ynn_binary_multiply, 3855, 7477, 3856);
  g->Unary(ynn_unary_square, 3856, 3858);
  g->Reduce(ynn_reduce_sum, 3858, 6760, {2}, true);
  g->ShapeProduct(3858, 6759, {2});
  g->Binary(ynn_binary_divide, 6760, 6759, 3859);
  g->Binary(ynn_binary_add, 3859, 7373, 3860);
  g->Binary(ynn_binary_pow, 3860, 7428, 3861);
  g->Binary(ynn_binary_multiply, 3856, 3861, 3862);
  g->Convert(7985, 3863);
  g->Binary(ynn_binary_multiply, 3862, 3863, 3864);
  g->Binary(ynn_binary_add, 3809, 3864, 3865);
}

// Scope: "Layer23 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1031, 3866, {0,0,23,0}, {-1,-1,1,-1});
  g->Reshape(3866, 3867, {1,1,256});
  g->Binary(ynn_binary_add, 3867, 8425, 3870);
  g->Binary(ynn_binary_multiply, 3870, 7155, 3871);
  g->Binary(ynn_binary_divide, 3865, 7165, 3872);
  g->Unary(ynn_unary_round, 3872, 3873);
  g->Binary(ynn_binary_max, 3873, 7225, 3874);
  g->Binary(ynn_binary_min, 3874, 7340, 3875);
  g->Binary(ynn_binary_multiply, 3875, 7165, 3876);
  g->Convert(7980, 3877);
  g->Binary(ynn_binary_multiply, 3877, 7981, 3878);
  g->Matmul(3876, 3878, 3879, false, true);
  g->Binary(ynn_binary_divide, 3879, 7248, 3881);
  g->Unary(ynn_unary_round, 3881, 3882);
  g->Binary(ynn_binary_max, 3882, 7225, 3883);
  g->Binary(ynn_binary_min, 3883, 7340, 3884);
  g->Binary(ynn_binary_multiply, 3884, 7248, 3885);
  g->Polynomial(3885, 6763, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6763, 6764);
  g->Binary(ynn_binary_add, 6764, 6183, 6761);
  g->Binary(ynn_binary_multiply, 3885, 6181, 6762);
  g->Binary(ynn_binary_multiply, 6762, 6761, 3886);
  g->Binary(ynn_binary_multiply, 3886, 3871, 3887);
  g->Binary(ynn_binary_divide, 3887, 7279, 3888);
  g->Unary(ynn_unary_round, 3888, 3889);
  g->Binary(ynn_binary_max, 3889, 7225, 3890);
  g->Binary(ynn_binary_min, 3890, 7340, 3892);
  g->Binary(ynn_binary_multiply, 3892, 7279, 3893);
  g->Convert(7982, 3894);
  g->Binary(ynn_binary_multiply, 3894, 7983, 3895);
  g->Matmul(3893, 3895, 3896, false, true);
  g->Binary(ynn_binary_divide, 3896, 7307, 3897);
  g->Unary(ynn_unary_round, 3897, 3898);
  g->Binary(ynn_binary_max, 3898, 7225, 3899);
  g->Binary(ynn_binary_min, 3899, 7340, 3900);
  g->Binary(ynn_binary_multiply, 3900, 7307, 3901);
  g->Unary(ynn_unary_square, 3901, 3903);
  g->Reduce(ynn_reduce_sum, 3903, 6766, {2}, true);
  g->ShapeProduct(3903, 6765, {2});
  g->Binary(ynn_binary_divide, 6766, 6765, 3904);
  g->Binary(ynn_binary_add, 3904, 7373, 3905);
  g->Binary(ynn_binary_pow, 3905, 7428, 3906);
  g->Binary(ynn_binary_multiply, 3901, 3906, 3907);
  g->Convert(7986, 3908);
  g->Binary(ynn_binary_multiply, 3907, 3908, 3909);
  g->Binary(ynn_binary_add, 3865, 3909, 3910);
  g->Convert(7973, 3911);
  g->Binary(ynn_binary_multiply, 3910, 3911, 3912);
}

// Scope: "Layer23"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23(Context& ctx) {
  BuildLayer23Attention(ctx);
  BuildLayer23Mlp(ctx);
  BuildLayer23PerLayerEmbedding(ctx);
}

}  // namespace BuildGemma4DecodeSource
