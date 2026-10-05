// Generated YNNPACK builder; do not edit.
#include "gemma4_decode_builder.h"

namespace BuildGemma4DecodeSource {

// Scope: "Layer15 / Attention / QueryProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15AttentionQueryProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Binary(ynn_binary_divide, 2329, 7147, 2330);
  g->Unary(ynn_unary_round, 2330, 2331);
  g->Binary(ynn_binary_max, 2331, 7155, 2334);
  g->Binary(ynn_binary_min, 2334, 7270, 2335);
  g->Binary(ynn_binary_multiply, 2335, 7147, 2336);
  g->Convert(7727, 2337);
  g->Binary(ynn_binary_multiply, 2337, 7728, 2338);
  g->Matmul(2336, 2338, 2339, false, true);
  g->Binary(ynn_binary_divide, 2339, 7105, 2340);
  g->Unary(ynn_unary_round, 2340, 2341);
  g->Binary(ynn_binary_max, 2341, 7155, 2342);
  g->Binary(ynn_binary_min, 2342, 7270, 2343);
  g->Binary(ynn_binary_multiply, 2343, 7105, 2345);
  g->SplitDim(2345, 2346, 2, {8,256});
  g->Transpose(2346, 2347, {0,2,1,3});
  g->Unary(ynn_unary_square, 2347, 2348);
  g->Reduce(ynn_reduce_sum, 2348, 6450, {3}, true);
  g->ShapeProduct(2348, 6449, {3});
  g->Binary(ynn_binary_divide, 6450, 6449, 2349);
  g->Binary(ynn_binary_add, 2349, 7303, 2350);
  g->Binary(ynn_binary_pow, 2350, 7358, 2351);
  g->Binary(ynn_binary_multiply, 2347, 2351, 2352);
  g->Convert(7726, 2353);
  g->Binary(ynn_binary_multiply, 2352, 2353, 2354);
  g->Slice(2354, 2356, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2354, 2357, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2357, 2358);
  g->Concat({2358,2356}, 2359, 3);
  g->Binary(ynn_binary_multiply, 2354, 2025, 2360);
  g->Binary(ynn_binary_multiply, 2359, 3078, 2361);
  g->Binary(ynn_binary_add, 2360, 2361, 2362);
}

// Scope: "Layer15 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(2362, 1946, 2363, false, true);
  g->Mask(2363, 7498, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 7498, 6454, {-1}, true);
  g->Binary(ynn_binary_subtract, 7498, 6454, 6451);
  g->Unary(ynn_unary_exp, 6451, 6452);
  g->Reduce(ynn_reduce_sum, 6452, 6455, {-1}, true);
  g->Binary(ynn_binary_divide, 6113, 6455, 6453);
  g->Binary(ynn_binary_multiply, 6452, 6453, 2364);
  g->Matmul(2364, 1948, 2365, false, false);
}

// Scope: "Layer15 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(2365, 2366, {0,2,1,3});
  g->FuseDims(2366, 2367, 2, 2);
  g->Binary(ynn_binary_divide, 2367, 7418, 2368);
  g->Unary(ynn_unary_round, 2368, 2369);
  g->Binary(ynn_binary_max, 2369, 7155, 2370);
  g->Binary(ynn_binary_min, 2370, 7270, 2371);
  g->Binary(ynn_binary_multiply, 2371, 7418, 2372);
  g->Convert(7724, 2373);
  g->Binary(ynn_binary_multiply, 2373, 7725, 2374);
  g->Matmul(2372, 2374, 2376, false, true);
  g->Binary(ynn_binary_divide, 2376, 7481, 2377);
  g->Unary(ynn_unary_round, 2377, 2378);
  g->Binary(ynn_binary_max, 2378, 7155, 2379);
  g->Binary(ynn_binary_min, 2379, 7270, 2380);
  g->Binary(ynn_binary_multiply, 2380, 7481, 2381);
}

// Scope: "Layer15 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2322, 2323);
  g->Reduce(ynn_reduce_sum, 2323, 6448, {2}, true);
  g->ShapeProduct(2323, 6447, {2});
  g->Binary(ynn_binary_divide, 6448, 6447, 2324);
  g->Binary(ynn_binary_add, 2324, 7303, 2325);
  g->Binary(ynn_binary_pow, 2325, 7358, 2326);
  g->Binary(ynn_binary_multiply, 2322, 2326, 2327);
  g->Convert(7708, 2328);
  g->Binary(ynn_binary_multiply, 2327, 2328, 2329);
  BuildLayer15AttentionQueryProjection(ctx);
  BuildLayer15AttentionSdpa(ctx);
  BuildLayer15AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2381, 2382);
  g->Reduce(ynn_reduce_sum, 2382, 6462, {2}, true);
  g->ShapeProduct(2382, 6461, {2});
  g->Binary(ynn_binary_divide, 6462, 6461, 2383);
  g->Binary(ynn_binary_add, 2383, 7303, 2384);
  g->Binary(ynn_binary_pow, 2384, 7358, 2385);
  g->Binary(ynn_binary_multiply, 2381, 2385, 2387);
  g->Convert(7720, 2388);
  g->Binary(ynn_binary_multiply, 2387, 2388, 2389);
  g->Binary(ynn_binary_add, 2322, 2389, 2390);
}

// Scope: "Layer15 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2390, 2391);
  g->Reduce(ynn_reduce_sum, 2391, 6464, {2}, true);
  g->ShapeProduct(2391, 6463, {2});
  g->Binary(ynn_binary_divide, 6464, 6463, 2392);
  g->Binary(ynn_binary_add, 2392, 7303, 2393);
  g->Binary(ynn_binary_pow, 2393, 7358, 2394);
  g->Binary(ynn_binary_multiply, 2390, 2394, 2395);
  g->Convert(7723, 2396);
  g->Binary(ynn_binary_multiply, 2395, 2396, 2398);
  g->Binary(ynn_binary_divide, 2398, 7276, 2399);
  g->Unary(ynn_unary_round, 2399, 2400);
  g->Binary(ynn_binary_max, 2400, 7155, 2401);
  g->Binary(ynn_binary_min, 2401, 7270, 2402);
  g->Binary(ynn_binary_multiply, 2402, 7276, 2403);
  g->Convert(7714, 2404);
  g->Binary(ynn_binary_multiply, 2404, 7715, 2405);
  g->Matmul(2403, 2405, 2406, false, true);
  g->Binary(ynn_binary_divide, 2406, 7431, 2407);
  g->Unary(ynn_unary_round, 2407, 2409);
  g->Binary(ynn_binary_max, 2409, 7155, 2410);
  g->Binary(ynn_binary_min, 2410, 7270, 2411);
  g->Binary(ynn_binary_multiply, 2411, 7431, 2412);
  g->Convert(7712, 2413);
  g->Binary(ynn_binary_multiply, 2413, 7713, 2415);
  g->Matmul(2403, 2415, 2416, false, true);
  g->Binary(ynn_binary_divide, 2416, 7431, 2417);
  g->Unary(ynn_unary_round, 2417, 2418);
  g->Binary(ynn_binary_max, 2418, 7155, 2419);
  g->Binary(ynn_binary_min, 2419, 7270, 2420);
  g->Binary(ynn_binary_multiply, 2420, 7431, 2421);
  g->Polynomial(2421, 6467, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6467, 6468);
  g->Binary(ynn_binary_add, 6468, 6113, 6465);
  g->Binary(ynn_binary_multiply, 2421, 6111, 6466);
  g->Binary(ynn_binary_multiply, 6466, 6465, 2422);
  g->Binary(ynn_binary_multiply, 2412, 2422, 2423);
  g->Binary(ynn_binary_divide, 2423, 7436, 2424);
  g->Unary(ynn_unary_round, 2424, 2426);
  g->Binary(ynn_binary_max, 2426, 7155, 2427);
  g->Binary(ynn_binary_min, 2427, 7270, 2428);
  g->Binary(ynn_binary_multiply, 2428, 7436, 2429);
  g->Convert(7710, 2430);
  g->Binary(ynn_binary_multiply, 2430, 7711, 2431);
  g->Matmul(2429, 2431, 2432, false, true);
  g->Binary(ynn_binary_divide, 2432, 7295, 2433);
  g->Unary(ynn_unary_round, 2433, 2434);
  g->Binary(ynn_binary_max, 2434, 7155, 2435);
  g->Binary(ynn_binary_min, 2435, 7270, 2438);
  g->Binary(ynn_binary_multiply, 2438, 7295, 2439);
  g->Unary(ynn_unary_square, 2439, 2440);
  g->Reduce(ynn_reduce_sum, 2440, 6470, {2}, true);
  g->ShapeProduct(2440, 6469, {2});
  g->Binary(ynn_binary_divide, 6470, 6469, 2441);
  g->Binary(ynn_binary_add, 2441, 7303, 2442);
  g->Binary(ynn_binary_pow, 2442, 7358, 2443);
  g->Binary(ynn_binary_multiply, 2439, 2443, 2444);
  g->Convert(7721, 2445);
  g->Binary(ynn_binary_multiply, 2444, 2445, 2446);
  g->Binary(ynn_binary_add, 2390, 2446, 2447);
}

// Scope: "Layer15 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer15PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1022, 2449, {0,0,15,0}, {-1,-1,1,-1});
  g->Reshape(2449, 2450, {1,1,256});
  g->Binary(ynn_binary_add, 2450, 8346, 2451);
  g->Binary(ynn_binary_multiply, 2451, 7085, 2452);
  g->Binary(ynn_binary_divide, 2447, 7128, 2453);
  g->Unary(ynn_unary_round, 2453, 2454);
  g->Binary(ynn_binary_max, 2454, 7155, 2455);
  g->Binary(ynn_binary_min, 2455, 7270, 2456);
  g->Binary(ynn_binary_multiply, 2456, 7128, 2457);
  g->Convert(7716, 2458);
  g->Binary(ynn_binary_multiply, 2458, 7717, 2460);
  g->Matmul(2457, 2460, 2461, false, true);
  g->Binary(ynn_binary_divide, 2461, 7280, 2462);
  g->Unary(ynn_unary_round, 2462, 2463);
  g->Binary(ynn_binary_max, 2463, 7155, 2464);
  g->Binary(ynn_binary_min, 2464, 7270, 2465);
  g->Binary(ynn_binary_multiply, 2465, 7280, 2466);
  g->Polynomial(2466, 6473, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6473, 6474);
  g->Binary(ynn_binary_add, 6474, 6113, 6471);
  g->Binary(ynn_binary_multiply, 2466, 6111, 6472);
  g->Binary(ynn_binary_multiply, 6472, 6471, 2467);
  g->Binary(ynn_binary_multiply, 2467, 2452, 2468);
  g->Binary(ynn_binary_divide, 2468, 7416, 2469);
  g->Unary(ynn_unary_round, 2469, 2471);
  g->Binary(ynn_binary_max, 2471, 7155, 2472);
  g->Binary(ynn_binary_min, 2472, 7270, 2473);
  g->Binary(ynn_binary_multiply, 2473, 7416, 2474);
  g->Convert(7718, 2475);
  g->Binary(ynn_binary_multiply, 2475, 7719, 2476);
  g->Matmul(2474, 2476, 2477, false, true);
  g->Binary(ynn_binary_divide, 2477, 7329, 2478);
  g->Unary(ynn_unary_round, 2478, 2479);
  g->Binary(ynn_binary_max, 2479, 7155, 2480);
  g->Binary(ynn_binary_min, 2480, 7270, 2482);
  g->Binary(ynn_binary_multiply, 2482, 7329, 2483);
  g->Unary(ynn_unary_square, 2483, 2484);
  g->Reduce(ynn_reduce_sum, 2484, 6476, {2}, true);
  g->ShapeProduct(2484, 6475, {2});
  g->Binary(ynn_binary_divide, 6476, 6475, 2485);
  g->Binary(ynn_binary_add, 2485, 7303, 2486);
  g->Binary(ynn_binary_pow, 2486, 7358, 2487);
  g->Binary(ynn_binary_multiply, 2483, 2487, 2488);
  g->Convert(7722, 2489);
  g->Binary(ynn_binary_multiply, 2488, 2489, 2490);
  g->Binary(ynn_binary_add, 2447, 2490, 2491);
  g->Convert(7709, 2493);
  g->Binary(ynn_binary_multiply, 2491, 2493, 2494);
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
  g->Binary(ynn_binary_divide, 2501, 7127, 2502);
  g->Unary(ynn_unary_round, 2502, 2504);
  g->Binary(ynn_binary_max, 2504, 7155, 2505);
  g->Binary(ynn_binary_min, 2505, 7270, 2506);
  g->Binary(ynn_binary_multiply, 2506, 7127, 2507);
  g->Convert(7748, 2508);
  g->Binary(ynn_binary_multiply, 2508, 7749, 2509);
  g->Matmul(2507, 2509, 2510, false, true);
  g->Binary(ynn_binary_divide, 2510, 7352, 2511);
  g->Unary(ynn_unary_round, 2511, 2512);
  g->Binary(ynn_binary_max, 2512, 7155, 2513);
  g->Binary(ynn_binary_min, 2513, 7270, 2515);
  g->Binary(ynn_binary_multiply, 2515, 7352, 2516);
  g->SplitDim(2516, 2517, 2, {8,256});
  g->Transpose(2517, 2518, {0,2,1,3});
  g->Unary(ynn_unary_square, 2518, 2519);
  g->Reduce(ynn_reduce_sum, 2519, 6480, {3}, true);
  g->ShapeProduct(2519, 6479, {3});
  g->Binary(ynn_binary_divide, 6480, 6479, 2520);
  g->Binary(ynn_binary_add, 2520, 7303, 2521);
  g->Binary(ynn_binary_pow, 2521, 7358, 2522);
  g->Binary(ynn_binary_multiply, 2518, 2522, 2523);
  g->Convert(7747, 2524);
  g->Binary(ynn_binary_multiply, 2523, 2524, 2526);
  g->Slice(2526, 2527, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2526, 2528, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2528, 2529);
  g->Concat({2529,2527}, 2530, 3);
  g->Binary(ynn_binary_multiply, 2526, 2025, 2531);
  g->Binary(ynn_binary_multiply, 2530, 3078, 2532);
  g->Binary(ynn_binary_add, 2531, 2532, 2533);
}

// Scope: "Layer16 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(2533, 1946, 2534, false, true);
  g->Mask(2534, 7499, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 7499, 6484, {-1}, true);
  g->Binary(ynn_binary_subtract, 7499, 6484, 6481);
  g->Unary(ynn_unary_exp, 6481, 6482);
  g->Reduce(ynn_reduce_sum, 6482, 6485, {-1}, true);
  g->Binary(ynn_binary_divide, 6113, 6485, 6483);
  g->Binary(ynn_binary_multiply, 6482, 6483, 2536);
  g->Matmul(2536, 1948, 2537, false, false);
}

// Scope: "Layer16 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(2537, 2538, {0,2,1,3});
  g->FuseDims(2538, 2539, 2, 2);
  g->Binary(ynn_binary_divide, 2539, 7387, 2540);
  g->Unary(ynn_unary_round, 2540, 2541);
  g->Binary(ynn_binary_max, 2541, 7155, 2542);
  g->Binary(ynn_binary_min, 2542, 7270, 2543);
  g->Binary(ynn_binary_multiply, 2543, 7387, 2544);
  g->Convert(7745, 2545);
  g->Binary(ynn_binary_multiply, 2545, 7746, 2548);
  g->Matmul(2544, 2548, 2549, false, true);
  g->Binary(ynn_binary_divide, 2549, 7372, 2550);
  g->Unary(ynn_unary_round, 2550, 2551);
  g->Binary(ynn_binary_max, 2551, 7155, 2552);
  g->Binary(ynn_binary_min, 2552, 7270, 2553);
  g->Binary(ynn_binary_multiply, 2553, 7372, 2554);
}

// Scope: "Layer16 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2494, 2495);
  g->Reduce(ynn_reduce_sum, 2495, 6478, {2}, true);
  g->ShapeProduct(2495, 6477, {2});
  g->Binary(ynn_binary_divide, 6478, 6477, 2496);
  g->Binary(ynn_binary_add, 2496, 7303, 2497);
  g->Binary(ynn_binary_pow, 2497, 7358, 2498);
  g->Binary(ynn_binary_multiply, 2494, 2498, 2499);
  g->Convert(7729, 2500);
  g->Binary(ynn_binary_multiply, 2499, 2500, 2501);
  BuildLayer16AttentionQueryProjection(ctx);
  BuildLayer16AttentionSdpa(ctx);
  BuildLayer16AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2554, 2555);
  g->Reduce(ynn_reduce_sum, 2555, 6487, {2}, true);
  g->ShapeProduct(2555, 6486, {2});
  g->Binary(ynn_binary_divide, 6487, 6486, 2556);
  g->Binary(ynn_binary_add, 2556, 7303, 2557);
  g->Binary(ynn_binary_pow, 2557, 7358, 2559);
  g->Binary(ynn_binary_multiply, 2554, 2559, 2560);
  g->Convert(7741, 2561);
  g->Binary(ynn_binary_multiply, 2560, 2561, 2562);
  g->Binary(ynn_binary_add, 2494, 2562, 2563);
}

// Scope: "Layer16 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2563, 2564);
  g->Reduce(ynn_reduce_sum, 2564, 6489, {2}, true);
  g->ShapeProduct(2564, 6488, {2});
  g->Binary(ynn_binary_divide, 6489, 6488, 2565);
  g->Binary(ynn_binary_add, 2565, 7303, 2566);
  g->Binary(ynn_binary_pow, 2566, 7358, 2567);
  g->Binary(ynn_binary_multiply, 2563, 2567, 2568);
  g->Convert(7744, 2570);
  g->Binary(ynn_binary_multiply, 2568, 2570, 2571);
  g->Binary(ynn_binary_divide, 2571, 7331, 2572);
  g->Unary(ynn_unary_round, 2572, 2573);
  g->Binary(ynn_binary_max, 2573, 7155, 2574);
  g->Binary(ynn_binary_min, 2574, 7270, 2575);
  g->Binary(ynn_binary_multiply, 2575, 7331, 2576);
  g->Convert(7735, 2577);
  g->Binary(ynn_binary_multiply, 2577, 7736, 2578);
  g->Matmul(2576, 2578, 2579, false, true);
  g->Binary(ynn_binary_divide, 2579, 7350, 2581);
  g->Unary(ynn_unary_round, 2581, 2582);
  g->Binary(ynn_binary_max, 2582, 7155, 2583);
  g->Binary(ynn_binary_min, 2583, 7270, 2584);
  g->Binary(ynn_binary_multiply, 2584, 7350, 2585);
  g->Convert(7733, 2587);
  g->Binary(ynn_binary_multiply, 2587, 7734, 2588);
  g->Matmul(2576, 2588, 2589, false, true);
  g->Binary(ynn_binary_divide, 2589, 7350, 2590);
  g->Unary(ynn_unary_round, 2590, 2591);
  g->Binary(ynn_binary_max, 2591, 7155, 2592);
  g->Binary(ynn_binary_min, 2592, 7270, 2593);
  g->Binary(ynn_binary_multiply, 2593, 7350, 2594);
  g->Polynomial(2594, 6494, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6494, 6495);
  g->Binary(ynn_binary_add, 6495, 6113, 6492);
  g->Binary(ynn_binary_multiply, 2594, 6111, 6493);
  g->Binary(ynn_binary_multiply, 6493, 6492, 2595);
  g->Binary(ynn_binary_multiply, 2585, 2595, 2596);
  g->Binary(ynn_binary_divide, 2596, 7103, 2598);
  g->Unary(ynn_unary_round, 2598, 2599);
  g->Binary(ynn_binary_max, 2599, 7155, 2600);
  g->Binary(ynn_binary_min, 2600, 7270, 2601);
  g->Binary(ynn_binary_multiply, 2601, 7103, 2602);
  g->Convert(7731, 2603);
  g->Binary(ynn_binary_multiply, 2603, 7732, 2604);
  g->Matmul(2602, 2604, 2605, false, true);
  g->Binary(ynn_binary_divide, 2605, 7107, 2606);
  g->Unary(ynn_unary_round, 2606, 2607);
  g->Binary(ynn_binary_max, 2607, 7155, 2609);
  g->Binary(ynn_binary_min, 2609, 7270, 2610);
  g->Binary(ynn_binary_multiply, 2610, 7107, 2611);
  g->Unary(ynn_unary_square, 2611, 2612);
  g->Reduce(ynn_reduce_sum, 2612, 6497, {2}, true);
  g->ShapeProduct(2612, 6496, {2});
  g->Binary(ynn_binary_divide, 6497, 6496, 2613);
  g->Binary(ynn_binary_add, 2613, 7303, 2614);
  g->Binary(ynn_binary_pow, 2614, 7358, 2615);
  g->Binary(ynn_binary_multiply, 2611, 2615, 2616);
  g->Convert(7742, 2617);
  g->Binary(ynn_binary_multiply, 2616, 2617, 2618);
  g->Binary(ynn_binary_add, 2563, 2618, 2620);
}

// Scope: "Layer16 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer16PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1022, 2621, {0,0,16,0}, {-1,-1,1,-1});
  g->Reshape(2621, 2622, {1,1,256});
  g->Binary(ynn_binary_add, 2622, 8347, 2623);
  g->Binary(ynn_binary_multiply, 2623, 7085, 2624);
  g->Binary(ynn_binary_divide, 2620, 7247, 2625);
  g->Unary(ynn_unary_round, 2625, 2626);
  g->Binary(ynn_binary_max, 2626, 7155, 2627);
  g->Binary(ynn_binary_min, 2627, 7270, 2628);
  g->Binary(ynn_binary_multiply, 2628, 7247, 2629);
  g->Convert(7737, 2631);
  g->Binary(ynn_binary_multiply, 2631, 7738, 2632);
  g->Matmul(2629, 2632, 2633, false, true);
  g->Binary(ynn_binary_divide, 2633, 7193, 2634);
  g->Unary(ynn_unary_round, 2634, 2635);
  g->Binary(ynn_binary_max, 2635, 7155, 2636);
  g->Binary(ynn_binary_min, 2636, 7270, 2637);
  g->Binary(ynn_binary_multiply, 2637, 7193, 2638);
  g->Polynomial(2638, 6500, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6500, 6501);
  g->Binary(ynn_binary_add, 6501, 6113, 6498);
  g->Binary(ynn_binary_multiply, 2638, 6111, 6499);
  g->Binary(ynn_binary_multiply, 6499, 6498, 2639);
  g->Binary(ynn_binary_multiply, 2639, 2624, 2640);
  g->Binary(ynn_binary_divide, 2640, 7257, 2642);
  g->Unary(ynn_unary_round, 2642, 2643);
  g->Binary(ynn_binary_max, 2643, 7155, 2644);
  g->Binary(ynn_binary_min, 2644, 7270, 2645);
  g->Binary(ynn_binary_multiply, 2645, 7257, 2646);
  g->Convert(7739, 2647);
  g->Binary(ynn_binary_multiply, 2647, 7740, 2648);
  g->Matmul(2646, 2648, 2649, false, true);
  g->Binary(ynn_binary_divide, 2649, 7401, 2650);
  g->Unary(ynn_unary_round, 2650, 2651);
  g->Binary(ynn_binary_max, 2651, 7155, 2654);
  g->Binary(ynn_binary_min, 2654, 7270, 2655);
  g->Binary(ynn_binary_multiply, 2655, 7401, 2656);
  g->Unary(ynn_unary_square, 2656, 2657);
  g->Reduce(ynn_reduce_sum, 2657, 6505, {2}, true);
  g->ShapeProduct(2657, 6504, {2});
  g->Binary(ynn_binary_divide, 6505, 6504, 2658);
  g->Binary(ynn_binary_add, 2658, 7303, 2659);
  g->Binary(ynn_binary_pow, 2659, 7358, 2660);
  g->Binary(ynn_binary_multiply, 2656, 2660, 2661);
  g->Convert(7743, 2662);
  g->Binary(ynn_binary_multiply, 2661, 2662, 2663);
  g->Binary(ynn_binary_add, 2620, 2663, 2665);
  g->Convert(7730, 2666);
  g->Binary(ynn_binary_multiply, 2665, 2666, 2667);
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
  g->Binary(ynn_binary_divide, 2674, 7471, 2676);
  g->Unary(ynn_unary_round, 2676, 2677);
  g->Binary(ynn_binary_max, 2677, 7155, 2678);
  g->Binary(ynn_binary_min, 2678, 7270, 2679);
  g->Binary(ynn_binary_multiply, 2679, 7471, 2680);
  g->Convert(7769, 2681);
  g->Binary(ynn_binary_multiply, 2681, 7770, 2682);
  g->Matmul(2680, 2682, 2683, false, true);
  g->Binary(ynn_binary_divide, 2683, 7302, 2684);
  g->Unary(ynn_unary_round, 2684, 2685);
  g->Binary(ynn_binary_max, 2685, 7155, 2687);
  g->Binary(ynn_binary_min, 2687, 7270, 2688);
  g->Binary(ynn_binary_multiply, 2688, 7302, 2689);
  g->SplitDim(2689, 2690, 2, {8,256});
  g->Transpose(2690, 2691, {0,2,1,3});
  g->Unary(ynn_unary_square, 2691, 2692);
  g->Reduce(ynn_reduce_sum, 2692, 6509, {3}, true);
  g->ShapeProduct(2692, 6508, {3});
  g->Binary(ynn_binary_divide, 6509, 6508, 2693);
  g->Binary(ynn_binary_add, 2693, 7303, 2694);
  g->Binary(ynn_binary_pow, 2694, 7358, 2695);
  g->Binary(ynn_binary_multiply, 2691, 2695, 2696);
  g->Convert(7768, 2698);
  g->Binary(ynn_binary_multiply, 2696, 2698, 2699);
  g->Slice(2699, 2700, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2699, 2701, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2701, 2702);
  g->Concat({2702,2700}, 2703, 3);
  g->Binary(ynn_binary_multiply, 2699, 2025, 2704);
  g->Binary(ynn_binary_multiply, 2703, 3078, 2705);
  g->Binary(ynn_binary_add, 2704, 2705, 2706);
}

// Scope: "Layer17 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(2706, 1946, 2707, false, true);
  g->Mask(2707, 7500, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 7500, 6513, {-1}, true);
  g->Binary(ynn_binary_subtract, 7500, 6513, 6510);
  g->Unary(ynn_unary_exp, 6510, 6511);
  g->Reduce(ynn_reduce_sum, 6511, 6514, {-1}, true);
  g->Binary(ynn_binary_divide, 6113, 6514, 6512);
  g->Binary(ynn_binary_multiply, 6511, 6512, 2709);
  g->Matmul(2709, 1948, 2710, false, false);
}

// Scope: "Layer17 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(2710, 2711, {0,2,1,3});
  g->FuseDims(2711, 2712, 2, 2);
  g->Binary(ynn_binary_divide, 2712, 7308, 2713);
  g->Unary(ynn_unary_round, 2713, 2714);
  g->Binary(ynn_binary_max, 2714, 7155, 2715);
  g->Binary(ynn_binary_min, 2715, 7270, 2716);
  g->Binary(ynn_binary_multiply, 2716, 7308, 2717);
  g->Convert(7766, 2719);
  g->Binary(ynn_binary_multiply, 2719, 7767, 2720);
  g->Matmul(2717, 2720, 2721, false, true);
  g->Binary(ynn_binary_divide, 2721, 7296, 2722);
  g->Unary(ynn_unary_round, 2722, 2723);
  g->Binary(ynn_binary_max, 2723, 7155, 2724);
  g->Binary(ynn_binary_min, 2724, 7270, 2725);
  g->Binary(ynn_binary_multiply, 2725, 7296, 2726);
}

// Scope: "Layer17 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2667, 2668);
  g->Reduce(ynn_reduce_sum, 2668, 6507, {2}, true);
  g->ShapeProduct(2668, 6506, {2});
  g->Binary(ynn_binary_divide, 6507, 6506, 2669);
  g->Binary(ynn_binary_add, 2669, 7303, 2670);
  g->Binary(ynn_binary_pow, 2670, 7358, 2671);
  g->Binary(ynn_binary_multiply, 2667, 2671, 2672);
  g->Convert(7750, 2673);
  g->Binary(ynn_binary_multiply, 2672, 2673, 2674);
  BuildLayer17AttentionQueryProjection(ctx);
  BuildLayer17AttentionSdpa(ctx);
  BuildLayer17AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2726, 2727);
  g->Reduce(ynn_reduce_sum, 2727, 6516, {2}, true);
  g->ShapeProduct(2727, 6515, {2});
  g->Binary(ynn_binary_divide, 6516, 6515, 2728);
  g->Binary(ynn_binary_add, 2728, 7303, 2730);
  g->Binary(ynn_binary_pow, 2730, 7358, 2731);
  g->Binary(ynn_binary_multiply, 2726, 2731, 2732);
  g->Convert(7762, 2733);
  g->Binary(ynn_binary_multiply, 2732, 2733, 2734);
  g->Binary(ynn_binary_add, 2667, 2734, 2735);
}

// Scope: "Layer17 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2735, 2736);
  g->Reduce(ynn_reduce_sum, 2736, 6518, {2}, true);
  g->ShapeProduct(2736, 6517, {2});
  g->Binary(ynn_binary_divide, 6518, 6517, 2737);
  g->Binary(ynn_binary_add, 2737, 7303, 2738);
  g->Binary(ynn_binary_pow, 2738, 7358, 2739);
  g->Binary(ynn_binary_multiply, 2735, 2739, 2741);
  g->Convert(7765, 2742);
  g->Binary(ynn_binary_multiply, 2741, 2742, 2743);
  g->Binary(ynn_binary_divide, 2743, 7461, 2744);
  g->Unary(ynn_unary_round, 2744, 2745);
  g->Binary(ynn_binary_max, 2745, 7155, 2746);
  g->Binary(ynn_binary_min, 2746, 7270, 2747);
  g->Binary(ynn_binary_multiply, 2747, 7461, 2748);
  g->Convert(7756, 2749);
  g->Binary(ynn_binary_multiply, 2749, 7757, 2750);
  g->Matmul(2748, 2750, 2752, false, true);
  g->Binary(ynn_binary_divide, 2752, 7437, 2753);
  g->Unary(ynn_unary_round, 2753, 2754);
  g->Binary(ynn_binary_max, 2754, 7155, 2755);
  g->Binary(ynn_binary_min, 2755, 7270, 2756);
  g->Binary(ynn_binary_multiply, 2756, 7437, 2757);
  g->Convert(7754, 2760);
  g->Binary(ynn_binary_multiply, 2760, 7755, 2761);
  g->Matmul(2748, 2761, 2762, false, true);
  g->Binary(ynn_binary_divide, 2762, 7437, 2763);
  g->Unary(ynn_unary_round, 2763, 2764);
  g->Binary(ynn_binary_max, 2764, 7155, 2765);
  g->Binary(ynn_binary_min, 2765, 7270, 2766);
  g->Binary(ynn_binary_multiply, 2766, 7437, 2767);
  g->Polynomial(2767, 6521, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6521, 6522);
  g->Binary(ynn_binary_add, 6522, 6113, 6519);
  g->Binary(ynn_binary_multiply, 2767, 6111, 6520);
  g->Binary(ynn_binary_multiply, 6520, 6519, 2768);
  g->Binary(ynn_binary_multiply, 2757, 2768, 2770);
  g->Binary(ynn_binary_divide, 2770, 7445, 2771);
  g->Unary(ynn_unary_round, 2771, 2772);
  g->Binary(ynn_binary_max, 2772, 7155, 2773);
  g->Binary(ynn_binary_min, 2773, 7270, 2774);
  g->Binary(ynn_binary_multiply, 2774, 7445, 2775);
  g->Convert(7752, 2776);
  g->Binary(ynn_binary_multiply, 2776, 7753, 2777);
  g->Matmul(2775, 2777, 2778, false, true);
  g->Binary(ynn_binary_divide, 2778, 7212, 2779);
  g->Unary(ynn_unary_round, 2779, 2781);
  g->Binary(ynn_binary_max, 2781, 7155, 2782);
  g->Binary(ynn_binary_min, 2782, 7270, 2783);
  g->Binary(ynn_binary_multiply, 2783, 7212, 2784);
  g->Unary(ynn_unary_square, 2784, 2785);
  g->Reduce(ynn_reduce_sum, 2785, 6524, {2}, true);
  g->ShapeProduct(2785, 6523, {2});
  g->Binary(ynn_binary_divide, 6524, 6523, 2786);
  g->Binary(ynn_binary_add, 2786, 7303, 2787);
  g->Binary(ynn_binary_pow, 2787, 7358, 2788);
  g->Binary(ynn_binary_multiply, 2784, 2788, 2789);
  g->Convert(7763, 2790);
  g->Binary(ynn_binary_multiply, 2789, 2790, 2792);
  g->Binary(ynn_binary_add, 2735, 2792, 2793);
}

// Scope: "Layer17 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer17PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1022, 2794, {0,0,17,0}, {-1,-1,1,-1});
  g->Reshape(2794, 2795, {1,1,256});
  g->Binary(ynn_binary_add, 2795, 8348, 2796);
  g->Binary(ynn_binary_multiply, 2796, 7085, 2797);
  g->Binary(ynn_binary_divide, 2793, 7319, 2798);
  g->Unary(ynn_unary_round, 2798, 2799);
  g->Binary(ynn_binary_max, 2799, 7155, 2800);
  g->Binary(ynn_binary_min, 2800, 7270, 2801);
  g->Binary(ynn_binary_multiply, 2801, 7319, 2803);
  g->Convert(7758, 2804);
  g->Binary(ynn_binary_multiply, 2804, 7759, 2805);
  g->Matmul(2803, 2805, 2806, false, true);
  g->Binary(ynn_binary_divide, 2806, 7438, 2807);
  g->Unary(ynn_unary_round, 2807, 2808);
  g->Binary(ynn_binary_max, 2808, 7155, 2809);
  g->Binary(ynn_binary_min, 2809, 7270, 2810);
  g->Binary(ynn_binary_multiply, 2810, 7438, 2811);
  g->Polynomial(2811, 6527, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6527, 6528);
  g->Binary(ynn_binary_add, 6528, 6113, 6525);
  g->Binary(ynn_binary_multiply, 2811, 6111, 6526);
  g->Binary(ynn_binary_multiply, 6526, 6525, 2812);
  g->Binary(ynn_binary_multiply, 2812, 2797, 2814);
  g->Binary(ynn_binary_divide, 2814, 7323, 2815);
  g->Unary(ynn_unary_round, 2815, 2816);
  g->Binary(ynn_binary_max, 2816, 7155, 2817);
  g->Binary(ynn_binary_min, 2817, 7270, 2818);
  g->Binary(ynn_binary_multiply, 2818, 7323, 2819);
  g->Convert(7760, 2820);
  g->Binary(ynn_binary_multiply, 2820, 7761, 2821);
  g->Matmul(2819, 2821, 2822, false, true);
  g->Binary(ynn_binary_divide, 2822, 7468, 2823);
  g->Unary(ynn_unary_round, 2823, 2825);
  g->Binary(ynn_binary_max, 2825, 7155, 2826);
  g->Binary(ynn_binary_min, 2826, 7270, 2827);
  g->Binary(ynn_binary_multiply, 2827, 7468, 2828);
  g->Unary(ynn_unary_square, 2828, 2829);
  g->Reduce(ynn_reduce_sum, 2829, 6530, {2}, true);
  g->ShapeProduct(2829, 6529, {2});
  g->Binary(ynn_binary_divide, 6530, 6529, 2830);
  g->Binary(ynn_binary_add, 2830, 7303, 2831);
  g->Binary(ynn_binary_pow, 2831, 7358, 2832);
  g->Binary(ynn_binary_multiply, 2828, 2832, 2833);
  g->Convert(7764, 2834);
  g->Binary(ynn_binary_multiply, 2833, 2834, 2836);
  g->Binary(ynn_binary_add, 2793, 2836, 2837);
  g->Convert(7751, 2838);
  g->Binary(ynn_binary_multiply, 2837, 2838, 2839);
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
  g->Binary(ynn_binary_divide, 2847, 7305, 2848);
  g->Unary(ynn_unary_round, 2848, 2849);
  g->Binary(ynn_binary_max, 2849, 7155, 2850);
  g->Binary(ynn_binary_min, 2850, 7270, 2851);
  g->Binary(ynn_binary_multiply, 2851, 7305, 2852);
  g->Convert(7790, 2853);
  g->Binary(ynn_binary_multiply, 2853, 7791, 2854);
  g->Matmul(2852, 2854, 2855, false, true);
  g->Binary(ynn_binary_divide, 2855, 7087, 2856);
  g->Unary(ynn_unary_round, 2856, 2857);
  g->Binary(ynn_binary_max, 2857, 7155, 2858);
  g->Binary(ynn_binary_min, 2858, 7270, 2859);
  g->Binary(ynn_binary_multiply, 2859, 7087, 2860);
  g->SplitDim(2860, 2861, 2, {8,256});
  g->Transpose(2861, 2862, {0,2,1,3});
  g->Unary(ynn_unary_square, 2862, 2863);
  g->Reduce(ynn_reduce_sum, 2863, 6534, {3}, true);
  g->ShapeProduct(2863, 6533, {3});
  g->Binary(ynn_binary_divide, 6534, 6533, 2864);
  g->Binary(ynn_binary_add, 2864, 7303, 2865);
  g->Binary(ynn_binary_pow, 2865, 7358, 2866);
  g->Binary(ynn_binary_multiply, 2862, 2866, 2868);
  g->Convert(7789, 2869);
  g->Binary(ynn_binary_multiply, 2868, 2869, 2870);
  g->Slice(2870, 2871, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(2870, 2872, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 2872, 2873);
  g->Concat({2873,2871}, 2874, 3);
  g->Binary(ynn_binary_multiply, 2870, 2025, 2875);
  g->Binary(ynn_binary_multiply, 2874, 3078, 2876);
  g->Binary(ynn_binary_add, 2875, 2876, 2877);
}

// Scope: "Layer18 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(2877, 1946, 2878, false, true);
  g->Mask(2878, 7501, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 7501, 6538, {-1}, true);
  g->Binary(ynn_binary_subtract, 7501, 6538, 6535);
  g->Unary(ynn_unary_exp, 6535, 6536);
  g->Reduce(ynn_reduce_sum, 6536, 6539, {-1}, true);
  g->Binary(ynn_binary_divide, 6113, 6539, 6537);
  g->Binary(ynn_binary_multiply, 6536, 6537, 2879);
  g->Matmul(2879, 1948, 2880, false, false);
}

// Scope: "Layer18 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(2880, 2881, {0,2,1,3});
  g->FuseDims(2881, 2882, 2, 2);
  g->Binary(ynn_binary_divide, 2882, 7168, 2883);
  g->Unary(ynn_unary_round, 2883, 2884);
  g->Binary(ynn_binary_max, 2884, 7155, 2885);
  g->Binary(ynn_binary_min, 2885, 7270, 2886);
  g->Binary(ynn_binary_multiply, 2886, 7168, 2887);
  g->Convert(7787, 2888);
  g->Binary(ynn_binary_multiply, 2888, 7788, 2889);
  g->Matmul(2887, 2889, 2890, false, true);
  g->Binary(ynn_binary_divide, 2890, 7246, 2891);
  g->Unary(ynn_unary_round, 2891, 2892);
  g->Binary(ynn_binary_max, 2892, 7155, 2893);
  g->Binary(ynn_binary_min, 2893, 7270, 2894);
  g->Binary(ynn_binary_multiply, 2894, 7246, 2895);
}

// Scope: "Layer18 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2839, 2840);
  g->Reduce(ynn_reduce_sum, 2840, 6532, {2}, true);
  g->ShapeProduct(2840, 6531, {2});
  g->Binary(ynn_binary_divide, 6532, 6531, 2841);
  g->Binary(ynn_binary_add, 2841, 7303, 2842);
  g->Binary(ynn_binary_pow, 2842, 7358, 2843);
  g->Binary(ynn_binary_multiply, 2839, 2843, 2844);
  g->Convert(7771, 2845);
  g->Binary(ynn_binary_multiply, 2844, 2845, 2847);
  BuildLayer18AttentionQueryProjection(ctx);
  BuildLayer18AttentionSdpa(ctx);
  BuildLayer18AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 2895, 2896);
  g->Reduce(ynn_reduce_sum, 2896, 6541, {2}, true);
  g->ShapeProduct(2896, 6540, {2});
  g->Binary(ynn_binary_divide, 6541, 6540, 2897);
  g->Binary(ynn_binary_add, 2897, 7303, 2898);
  g->Binary(ynn_binary_pow, 2898, 7358, 2899);
  g->Binary(ynn_binary_multiply, 2895, 2899, 2900);
  g->Convert(7783, 2901);
  g->Binary(ynn_binary_multiply, 2900, 2901, 2902);
  g->Binary(ynn_binary_add, 2839, 2902, 2903);
}

// Scope: "Layer18 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 2903, 2904);
  g->Reduce(ynn_reduce_sum, 2904, 6543, {2}, true);
  g->ShapeProduct(2904, 6542, {2});
  g->Binary(ynn_binary_divide, 6543, 6542, 2905);
  g->Binary(ynn_binary_add, 2905, 7303, 2906);
  g->Binary(ynn_binary_pow, 2906, 7358, 2908);
  g->Binary(ynn_binary_multiply, 2903, 2908, 2909);
  g->Convert(7786, 2910);
  g->Binary(ynn_binary_multiply, 2909, 2910, 2911);
  g->Binary(ynn_binary_divide, 2911, 7322, 2912);
  g->Unary(ynn_unary_round, 2912, 2913);
  g->Binary(ynn_binary_max, 2913, 7155, 2914);
  g->Binary(ynn_binary_min, 2914, 7270, 2915);
  g->Binary(ynn_binary_multiply, 2915, 7322, 2916);
  g->Convert(7777, 2917);
  g->Binary(ynn_binary_multiply, 2917, 7778, 2919);
  g->Matmul(2916, 2919, 2920, false, true);
  g->Binary(ynn_binary_divide, 2920, 7120, 2921);
  g->Unary(ynn_unary_round, 2921, 2922);
  g->Binary(ynn_binary_max, 2922, 7155, 2923);
  g->Binary(ynn_binary_min, 2923, 7270, 2924);
  g->Binary(ynn_binary_multiply, 2924, 7120, 2925);
  g->Convert(7775, 2927);
  g->Binary(ynn_binary_multiply, 2927, 7776, 2928);
  g->Matmul(2916, 2928, 2929, false, true);
  g->Binary(ynn_binary_divide, 2929, 7120, 2930);
  g->Unary(ynn_unary_round, 2930, 2931);
  g->Binary(ynn_binary_max, 2931, 7155, 2932);
  g->Binary(ynn_binary_min, 2932, 7270, 2933);
  g->Binary(ynn_binary_multiply, 2933, 7120, 2934);
  g->Polynomial(2934, 6546, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6546, 6547);
  g->Binary(ynn_binary_add, 6547, 6113, 6544);
  g->Binary(ynn_binary_multiply, 2934, 6111, 6545);
  g->Binary(ynn_binary_multiply, 6545, 6544, 2936);
  g->Binary(ynn_binary_multiply, 2925, 2936, 2937);
  g->Binary(ynn_binary_divide, 2937, 7395, 2938);
  g->Unary(ynn_unary_round, 2938, 2939);
  g->Binary(ynn_binary_max, 2939, 7155, 2940);
  g->Binary(ynn_binary_min, 2940, 7270, 2941);
  g->Binary(ynn_binary_multiply, 2941, 7395, 2942);
  g->Convert(7773, 2943);
  g->Binary(ynn_binary_multiply, 2943, 7774, 2944);
  g->Matmul(2942, 2944, 2945, false, true);
  g->Binary(ynn_binary_divide, 2945, 7089, 2947);
  g->Unary(ynn_unary_round, 2947, 2948);
  g->Binary(ynn_binary_max, 2948, 7155, 2949);
  g->Binary(ynn_binary_min, 2949, 7270, 2950);
  g->Binary(ynn_binary_multiply, 2950, 7089, 2951);
  g->Unary(ynn_unary_square, 2951, 2952);
  g->Reduce(ynn_reduce_sum, 2952, 6549, {2}, true);
  g->ShapeProduct(2952, 6548, {2});
  g->Binary(ynn_binary_divide, 6549, 6548, 2953);
  g->Binary(ynn_binary_add, 2953, 7303, 2954);
  g->Binary(ynn_binary_pow, 2954, 7358, 2955);
  g->Binary(ynn_binary_multiply, 2951, 2955, 2956);
  g->Convert(7784, 2958);
  g->Binary(ynn_binary_multiply, 2956, 2958, 2959);
  g->Binary(ynn_binary_add, 2903, 2959, 2960);
}

// Scope: "Layer18 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer18PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1022, 2961, {0,0,18,0}, {-1,-1,1,-1});
  g->Reshape(2961, 2962, {1,1,256});
  g->Binary(ynn_binary_add, 2962, 8349, 2963);
  g->Binary(ynn_binary_multiply, 2963, 7085, 2964);
  g->Binary(ynn_binary_divide, 2960, 7116, 2965);
  g->Unary(ynn_unary_round, 2965, 2966);
  g->Binary(ynn_binary_max, 2966, 7155, 2967);
  g->Binary(ynn_binary_min, 2967, 7270, 2970);
  g->Binary(ynn_binary_multiply, 2970, 7116, 2971);
  g->Convert(7779, 2972);
  g->Binary(ynn_binary_multiply, 2972, 7780, 2973);
  g->Matmul(2971, 2973, 2974, false, true);
  g->Binary(ynn_binary_divide, 2974, 7364, 2975);
  g->Unary(ynn_unary_round, 2975, 2976);
  g->Binary(ynn_binary_max, 2976, 7155, 2977);
  g->Binary(ynn_binary_min, 2977, 7270, 2978);
  g->Binary(ynn_binary_multiply, 2978, 7364, 2979);
  g->Polynomial(2979, 6552, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6552, 6553);
  g->Binary(ynn_binary_add, 6553, 6113, 6550);
  g->Binary(ynn_binary_multiply, 2979, 6111, 6551);
  g->Binary(ynn_binary_multiply, 6551, 6550, 2981);
  g->Binary(ynn_binary_multiply, 2981, 2964, 2982);
  g->Binary(ynn_binary_divide, 2982, 7177, 2983);
  g->Unary(ynn_unary_round, 2983, 2984);
  g->Binary(ynn_binary_max, 2984, 7155, 2985);
  g->Binary(ynn_binary_min, 2985, 7270, 2986);
  g->Binary(ynn_binary_multiply, 2986, 7177, 2987);
  g->Convert(7781, 2988);
  g->Binary(ynn_binary_multiply, 2988, 7782, 2989);
  g->Matmul(2987, 2989, 2990, false, true);
  g->Binary(ynn_binary_divide, 2990, 7326, 2992);
  g->Unary(ynn_unary_round, 2992, 2993);
  g->Binary(ynn_binary_max, 2993, 7155, 2994);
  g->Binary(ynn_binary_min, 2994, 7270, 2995);
  g->Binary(ynn_binary_multiply, 2995, 7326, 2996);
  g->Unary(ynn_unary_square, 2996, 2997);
  g->Reduce(ynn_reduce_sum, 2997, 6559, {2}, true);
  g->ShapeProduct(2997, 6558, {2});
  g->Binary(ynn_binary_divide, 6559, 6558, 2998);
  g->Binary(ynn_binary_add, 2998, 7303, 2999);
  g->Binary(ynn_binary_pow, 2999, 7358, 3000);
  g->Binary(ynn_binary_multiply, 2996, 3000, 3001);
  g->Convert(7785, 3003);
  g->Binary(ynn_binary_multiply, 3001, 3003, 3004);
  g->Binary(ynn_binary_add, 2960, 3004, 3005);
  g->Convert(7772, 3006);
  g->Binary(ynn_binary_multiply, 3005, 3006, 3007);
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
  g->Binary(ynn_binary_divide, 3015, 7145, 3016);
  g->Unary(ynn_unary_round, 3016, 3017);
  g->Binary(ynn_binary_max, 3017, 7155, 3018);
  g->Binary(ynn_binary_min, 3018, 7270, 3019);
  g->Binary(ynn_binary_multiply, 3019, 7145, 3020);
  g->Convert(7811, 3021);
  g->Binary(ynn_binary_multiply, 3021, 7812, 3022);
  g->Matmul(3020, 3022, 3023, false, true);
  g->Binary(ynn_binary_divide, 3023, 7220, 3025);
  g->Unary(ynn_unary_round, 3025, 3026);
  g->Binary(ynn_binary_max, 3026, 7155, 3027);
  g->Binary(ynn_binary_min, 3027, 7270, 3028);
  g->Binary(ynn_binary_multiply, 3028, 7220, 3029);
  g->SplitDim(3029, 3030, 2, {8,512});
  g->Transpose(3030, 3031, {0,2,1,3});
  g->Unary(ynn_unary_square, 3031, 3032);
  g->Reduce(ynn_reduce_sum, 3032, 6563, {3}, true);
  g->ShapeProduct(3032, 6562, {3});
  g->Binary(ynn_binary_divide, 6563, 6562, 3033);
  g->Binary(ynn_binary_add, 3033, 7303, 3034);
  g->Binary(ynn_binary_pow, 3034, 7358, 3036);
  g->Binary(ynn_binary_multiply, 3031, 3036, 3037);
  g->Convert(7810, 3038);
  g->Binary(ynn_binary_multiply, 3037, 3038, 3039);
  g->Slice(3039, 3040, {0,0,0,0}, {-1,-1,-1,256});
  g->Slice(3039, 3041, {0,0,0,256}, {-1,-1,-1,256});
  g->Unary(ynn_unary_negate, 3041, 3042);
  g->Concat({3042,3040}, 3043, 3);
  g->Binary(ynn_binary_multiply, 3039, 5909, 3044);
  g->Binary(ynn_binary_multiply, 3043, 6008, 3045);
  g->Binary(ynn_binary_add, 3044, 3045, 3047);
}

// Scope: "Layer19 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(3047, 2160, 3048, false, true);
  g->Mask(3048, 7502, s2, slinky::expr(int64_t{0}), 0, true);
  g->Reduce(ynn_reduce_max, 7502, 6567, {-1}, true);
  g->Binary(ynn_binary_subtract, 7502, 6567, 6564);
  g->Unary(ynn_unary_exp, 6564, 6565);
  g->Reduce(ynn_reduce_sum, 6565, 6568, {-1}, true);
  g->Binary(ynn_binary_divide, 6113, 6568, 6566);
  g->Binary(ynn_binary_multiply, 6565, 6566, 3049);
  g->Matmul(3049, 2162, 3050, false, false);
}

// Scope: "Layer19 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(3050, 3051, {0,2,1,3});
  g->FuseDims(3051, 3052, 2, 2);
  g->Binary(ynn_binary_divide, 3052, 7359, 3053);
  g->Unary(ynn_unary_round, 3053, 3054);
  g->Binary(ynn_binary_max, 3054, 7155, 3055);
  g->Binary(ynn_binary_min, 3055, 7270, 3057);
  g->Binary(ynn_binary_multiply, 3057, 7359, 3058);
  g->Convert(7808, 3059);
  g->Binary(ynn_binary_multiply, 3059, 7809, 3060);
  g->Matmul(3058, 3060, 3061, false, true);
  g->Binary(ynn_binary_divide, 3061, 7285, 3062);
  g->Unary(ynn_unary_round, 3062, 3063);
  g->Binary(ynn_binary_max, 3063, 7155, 3064);
  g->Binary(ynn_binary_min, 3064, 7270, 3065);
  g->Binary(ynn_binary_multiply, 3065, 7285, 3066);
}

// Scope: "Layer19 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3007, 3008);
  g->Reduce(ynn_reduce_sum, 3008, 6561, {2}, true);
  g->ShapeProduct(3008, 6560, {2});
  g->Binary(ynn_binary_divide, 6561, 6560, 3009);
  g->Binary(ynn_binary_add, 3009, 7303, 3010);
  g->Binary(ynn_binary_pow, 3010, 7358, 3011);
  g->Binary(ynn_binary_multiply, 3007, 3011, 3012);
  g->Convert(7792, 3014);
  g->Binary(ynn_binary_multiply, 3012, 3014, 3015);
  BuildLayer19AttentionQueryProjection(ctx);
  BuildLayer19AttentionSdpa(ctx);
  BuildLayer19AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 3066, 3068);
  g->Reduce(ynn_reduce_sum, 3068, 6570, {2}, true);
  g->ShapeProduct(3068, 6569, {2});
  g->Binary(ynn_binary_divide, 6570, 6569, 3069);
  g->Binary(ynn_binary_add, 3069, 7303, 3070);
  g->Binary(ynn_binary_pow, 3070, 7358, 3071);
  g->Binary(ynn_binary_multiply, 3066, 3071, 3072);
  g->Convert(7804, 3073);
  g->Binary(ynn_binary_multiply, 3072, 3073, 3074);
  g->Binary(ynn_binary_add, 3007, 3074, 3075);
}

// Scope: "Layer19 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3075, 3076);
  g->Reduce(ynn_reduce_sum, 3076, 6572, {2}, true);
  g->ShapeProduct(3076, 6571, {2});
  g->Binary(ynn_binary_divide, 6572, 6571, 3077);
  g->Binary(ynn_binary_add, 3077, 7303, 3081);
  g->Binary(ynn_binary_pow, 3081, 7358, 3082);
  g->Binary(ynn_binary_multiply, 3075, 3082, 3083);
  g->Convert(7807, 3084);
  g->Binary(ynn_binary_multiply, 3083, 3084, 3085);
  g->Binary(ynn_binary_divide, 3085, 7228, 3086);
  g->Unary(ynn_unary_round, 3086, 3087);
  g->Binary(ynn_binary_max, 3087, 7155, 3088);
  g->Binary(ynn_binary_min, 3088, 7270, 3089);
  g->Binary(ynn_binary_multiply, 3089, 7228, 3090);
  g->Convert(7798, 3092);
  g->Binary(ynn_binary_multiply, 3092, 7799, 3093);
  g->Matmul(3090, 3093, 3094, false, true);
  g->Binary(ynn_binary_divide, 3094, 7338, 3095);
  g->Unary(ynn_unary_round, 3095, 3096);
  g->Binary(ynn_binary_max, 3096, 7155, 3097);
  g->Binary(ynn_binary_min, 3097, 7270, 3098);
  g->Binary(ynn_binary_multiply, 3098, 7338, 3099);
  g->Convert(7796, 3101);
  g->Binary(ynn_binary_multiply, 3101, 7797, 3102);
  g->Matmul(3090, 3102, 3103, false, true);
  g->Binary(ynn_binary_divide, 3103, 7338, 3104);
  g->Unary(ynn_unary_round, 3104, 3105);
  g->Binary(ynn_binary_max, 3105, 7155, 3106);
  g->Binary(ynn_binary_min, 3106, 7270, 3107);
  g->Binary(ynn_binary_multiply, 3107, 7338, 3109);
  g->Polynomial(3109, 6575, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6575, 6576);
  g->Binary(ynn_binary_add, 6576, 6113, 6573);
  g->Binary(ynn_binary_multiply, 3109, 6111, 6574);
  g->Binary(ynn_binary_multiply, 6574, 6573, 3110);
  g->Binary(ynn_binary_multiply, 3099, 3110, 3111);
  g->Binary(ynn_binary_divide, 3111, 7264, 3112);
  g->Unary(ynn_unary_round, 3112, 3113);
  g->Binary(ynn_binary_max, 3113, 7155, 3114);
  g->Binary(ynn_binary_min, 3114, 7270, 3115);
  g->Binary(ynn_binary_multiply, 3115, 7264, 3116);
  g->Convert(7794, 3117);
  g->Binary(ynn_binary_multiply, 3117, 7795, 3118);
  g->Matmul(3116, 3118, 3120, false, true);
  g->Binary(ynn_binary_divide, 3120, 7259, 3121);
  g->Unary(ynn_unary_round, 3121, 3122);
  g->Binary(ynn_binary_max, 3122, 7155, 3123);
  g->Binary(ynn_binary_min, 3123, 7270, 3124);
  g->Binary(ynn_binary_multiply, 3124, 7259, 3125);
  g->Unary(ynn_unary_square, 3125, 3126);
  g->Reduce(ynn_reduce_sum, 3126, 6578, {2}, true);
  g->ShapeProduct(3126, 6577, {2});
  g->Binary(ynn_binary_divide, 6578, 6577, 3127);
  g->Binary(ynn_binary_add, 3127, 7303, 3128);
  g->Binary(ynn_binary_pow, 3128, 7358, 3129);
  g->Binary(ynn_binary_multiply, 3125, 3129, 3131);
  g->Convert(7805, 3132);
  g->Binary(ynn_binary_multiply, 3131, 3132, 3133);
  g->Binary(ynn_binary_add, 3075, 3133, 3134);
}

// Scope: "Layer19 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer19PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1022, 3135, {0,0,19,0}, {-1,-1,1,-1});
  g->Reshape(3135, 3136, {1,1,256});
  g->Binary(ynn_binary_add, 3136, 8350, 3137);
  g->Binary(ynn_binary_multiply, 3137, 7085, 3138);
  g->Binary(ynn_binary_divide, 3134, 7389, 3139);
  g->Unary(ynn_unary_round, 3139, 3140);
  g->Binary(ynn_binary_max, 3140, 7155, 3142);
  g->Binary(ynn_binary_min, 3142, 7270, 3143);
  g->Binary(ynn_binary_multiply, 3143, 7389, 3144);
  g->Convert(7800, 3145);
  g->Binary(ynn_binary_multiply, 3145, 7801, 3146);
  g->Matmul(3144, 3146, 3147, false, true);
  g->Binary(ynn_binary_divide, 3147, 7233, 3148);
  g->Unary(ynn_unary_round, 3148, 3149);
  g->Binary(ynn_binary_max, 3149, 7155, 3150);
  g->Binary(ynn_binary_min, 3150, 7270, 3151);
  g->Binary(ynn_binary_multiply, 3151, 7233, 3153);
  g->Polynomial(3153, 6581, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6581, 6582);
  g->Binary(ynn_binary_add, 6582, 6113, 6579);
  g->Binary(ynn_binary_multiply, 3153, 6111, 6580);
  g->Binary(ynn_binary_multiply, 6580, 6579, 3154);
  g->Binary(ynn_binary_multiply, 3154, 3138, 3155);
  g->Binary(ynn_binary_divide, 3155, 7397, 3156);
  g->Unary(ynn_unary_round, 3156, 3157);
  g->Binary(ynn_binary_max, 3157, 7155, 3158);
  g->Binary(ynn_binary_min, 3158, 7270, 3159);
  g->Binary(ynn_binary_multiply, 3159, 7397, 3160);
  g->Convert(7802, 3161);
  g->Binary(ynn_binary_multiply, 3161, 7803, 3162);
  g->Matmul(3160, 3162, 3164, false, true);
  g->Binary(ynn_binary_divide, 3164, 7309, 3165);
  g->Unary(ynn_unary_round, 3165, 3166);
  g->Binary(ynn_binary_max, 3166, 7155, 3167);
  g->Binary(ynn_binary_min, 3167, 7270, 3168);
  g->Binary(ynn_binary_multiply, 3168, 7309, 3169);
  g->Unary(ynn_unary_square, 3169, 3170);
  g->Reduce(ynn_reduce_sum, 3170, 6586, {2}, true);
  g->ShapeProduct(3170, 6585, {2});
  g->Binary(ynn_binary_divide, 6586, 6585, 3171);
  g->Binary(ynn_binary_add, 3171, 7303, 3172);
  g->Binary(ynn_binary_pow, 3172, 7358, 3173);
  g->Binary(ynn_binary_multiply, 3169, 3173, 3175);
  g->Convert(7806, 3176);
  g->Binary(ynn_binary_multiply, 3175, 3176, 3177);
  g->Binary(ynn_binary_add, 3134, 3177, 3178);
  g->Convert(7793, 3179);
  g->Binary(ynn_binary_multiply, 3178, 3179, 3180);
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
  g->Binary(ynn_binary_divide, 3189, 7188, 3190);
  g->Unary(ynn_unary_round, 3190, 3191);
  g->Binary(ynn_binary_max, 3191, 7155, 3192);
  g->Binary(ynn_binary_min, 3192, 7270, 3193);
  g->Binary(ynn_binary_multiply, 3193, 7188, 3194);
  g->Convert(7858, 3195);
  g->Binary(ynn_binary_multiply, 3195, 7859, 3196);
  g->Matmul(3194, 3196, 3198, false, true);
  g->Binary(ynn_binary_divide, 3198, 7450, 3199);
  g->Unary(ynn_unary_round, 3199, 3200);
  g->Binary(ynn_binary_max, 3200, 7155, 3201);
  g->Binary(ynn_binary_min, 3201, 7270, 3202);
  g->Binary(ynn_binary_multiply, 3202, 7450, 3203);
  g->SplitDim(3203, 3204, 2, {8,256});
  g->Transpose(3204, 3205, {0,2,1,3});
  g->Unary(ynn_unary_square, 3205, 3206);
  g->Reduce(ynn_reduce_sum, 3206, 6590, {3}, true);
  g->ShapeProduct(3206, 6589, {3});
  g->Binary(ynn_binary_divide, 6590, 6589, 3207);
  g->Binary(ynn_binary_add, 3207, 7303, 3209);
  g->Binary(ynn_binary_pow, 3209, 7358, 3210);
  g->Binary(ynn_binary_multiply, 3205, 3210, 3211);
  g->Convert(7857, 3212);
  g->Binary(ynn_binary_multiply, 3211, 3212, 3213);
  g->Slice(3213, 3214, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3213, 3215, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3215, 3216);
  g->Concat({3216,3214}, 3217, 3);
  g->Binary(ynn_binary_multiply, 3213, 2025, 3218);
  g->Binary(ynn_binary_multiply, 3217, 3078, 3220);
  g->Binary(ynn_binary_add, 3218, 3220, 3221);
}

// Scope: "Layer20 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(3221, 1946, 3222, false, true);
  g->Mask(3222, 7504, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 7504, 6594, {-1}, true);
  g->Binary(ynn_binary_subtract, 7504, 6594, 6591);
  g->Unary(ynn_unary_exp, 6591, 6592);
  g->Reduce(ynn_reduce_sum, 6592, 6595, {-1}, true);
  g->Binary(ynn_binary_divide, 6113, 6595, 6593);
  g->Binary(ynn_binary_multiply, 6592, 6593, 3223);
  g->Matmul(3223, 1948, 3224, false, false);
}

// Scope: "Layer20 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(3224, 3225, {0,2,1,3});
  g->FuseDims(3225, 3226, 2, 2);
  g->Binary(ynn_binary_divide, 3226, 7418, 3227);
  g->Unary(ynn_unary_round, 3227, 3228);
  g->Binary(ynn_binary_max, 3228, 7155, 3230);
  g->Binary(ynn_binary_min, 3230, 7270, 3231);
  g->Binary(ynn_binary_multiply, 3231, 7418, 3232);
  g->Convert(7855, 3233);
  g->Binary(ynn_binary_multiply, 3233, 7856, 3234);
  g->Matmul(3232, 3234, 3235, false, true);
  g->Binary(ynn_binary_divide, 3235, 7101, 3236);
  g->Unary(ynn_unary_round, 3236, 3237);
  g->Binary(ynn_binary_max, 3237, 7155, 3238);
  g->Binary(ynn_binary_min, 3238, 7270, 3239);
  g->Binary(ynn_binary_multiply, 3239, 7101, 3241);
}

// Scope: "Layer20 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3180, 3181);
  g->Reduce(ynn_reduce_sum, 3181, 6588, {2}, true);
  g->ShapeProduct(3181, 6587, {2});
  g->Binary(ynn_binary_divide, 6588, 6587, 3182);
  g->Binary(ynn_binary_add, 3182, 7303, 3183);
  g->Binary(ynn_binary_pow, 3183, 7358, 3184);
  g->Binary(ynn_binary_multiply, 3180, 3184, 3187);
  g->Convert(7839, 3188);
  g->Binary(ynn_binary_multiply, 3187, 3188, 3189);
  BuildLayer20AttentionQueryProjection(ctx);
  BuildLayer20AttentionSdpa(ctx);
  BuildLayer20AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 3241, 3242);
  g->Reduce(ynn_reduce_sum, 3242, 6597, {2}, true);
  g->ShapeProduct(3242, 6596, {2});
  g->Binary(ynn_binary_divide, 6597, 6596, 3243);
  g->Binary(ynn_binary_add, 3243, 7303, 3244);
  g->Binary(ynn_binary_pow, 3244, 7358, 3245);
  g->Binary(ynn_binary_multiply, 3241, 3245, 3246);
  g->Convert(7851, 3247);
  g->Binary(ynn_binary_multiply, 3246, 3247, 3248);
  g->Binary(ynn_binary_add, 3180, 3248, 3249);
}

// Scope: "Layer20 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3249, 3250);
  g->Reduce(ynn_reduce_sum, 3250, 6599, {2}, true);
  g->ShapeProduct(3250, 6598, {2});
  g->Binary(ynn_binary_divide, 6599, 6598, 3252);
  g->Binary(ynn_binary_add, 3252, 7303, 3253);
  g->Binary(ynn_binary_pow, 3253, 7358, 3254);
  g->Binary(ynn_binary_multiply, 3249, 3254, 3255);
  g->Convert(7854, 3256);
  g->Binary(ynn_binary_multiply, 3255, 3256, 3257);
  g->Binary(ynn_binary_divide, 3257, 7465, 3258);
  g->Unary(ynn_unary_round, 3258, 3259);
  g->Binary(ynn_binary_max, 3259, 7155, 3260);
  g->Binary(ynn_binary_min, 3260, 7270, 3261);
  g->Binary(ynn_binary_multiply, 3261, 7465, 3263);
  g->Convert(7845, 3264);
  g->Binary(ynn_binary_multiply, 3264, 7846, 3265);
  g->Matmul(3263, 3265, 3266, false, true);
  g->Binary(ynn_binary_divide, 3266, 7394, 3267);
  g->Unary(ynn_unary_round, 3267, 3268);
  g->Binary(ynn_binary_max, 3268, 7155, 3269);
  g->Binary(ynn_binary_min, 3269, 7270, 3270);
  g->Binary(ynn_binary_multiply, 3270, 7394, 3271);
  g->Convert(7843, 3273);
  g->Binary(ynn_binary_multiply, 3273, 7844, 3274);
  g->Matmul(3263, 3274, 3275, false, true);
  g->Binary(ynn_binary_divide, 3275, 7394, 3276);
  g->Unary(ynn_unary_round, 3276, 3277);
  g->Binary(ynn_binary_max, 3277, 7155, 3278);
  g->Binary(ynn_binary_min, 3278, 7270, 3280);
  g->Binary(ynn_binary_multiply, 3280, 7394, 3281);
  g->Polynomial(3281, 6602, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6602, 6603);
  g->Binary(ynn_binary_add, 6603, 6113, 6600);
  g->Binary(ynn_binary_multiply, 3281, 6111, 6601);
  g->Binary(ynn_binary_multiply, 6601, 6600, 3282);
  g->Binary(ynn_binary_multiply, 3271, 3282, 3283);
  g->Binary(ynn_binary_divide, 3283, 7341, 3284);
  g->Unary(ynn_unary_round, 3284, 3285);
  g->Binary(ynn_binary_max, 3285, 7155, 3286);
  g->Binary(ynn_binary_min, 3286, 7270, 3287);
  g->Binary(ynn_binary_multiply, 3287, 7341, 3288);
  g->Convert(7841, 3289);
  g->Binary(ynn_binary_multiply, 3289, 7842, 3292);
  g->Matmul(3288, 3292, 3293, false, true);
  g->Binary(ynn_binary_divide, 3293, 7169, 3294);
  g->Unary(ynn_unary_round, 3294, 3295);
  g->Binary(ynn_binary_max, 3295, 7155, 3296);
  g->Binary(ynn_binary_min, 3296, 7270, 3297);
  g->Binary(ynn_binary_multiply, 3297, 7169, 3298);
  g->Unary(ynn_unary_square, 3298, 3299);
  g->Reduce(ynn_reduce_sum, 3299, 6605, {2}, true);
  g->ShapeProduct(3299, 6604, {2});
  g->Binary(ynn_binary_divide, 6605, 6604, 3300);
  g->Binary(ynn_binary_add, 3300, 7303, 3301);
  g->Binary(ynn_binary_pow, 3301, 7358, 3303);
  g->Binary(ynn_binary_multiply, 3298, 3303, 3304);
  g->Convert(7852, 3305);
  g->Binary(ynn_binary_multiply, 3304, 3305, 3306);
  g->Binary(ynn_binary_add, 3249, 3306, 3307);
}

// Scope: "Layer20 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer20PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1022, 3308, {0,0,20,0}, {-1,-1,1,-1});
  g->Reshape(3308, 3309, {1,1,256});
  g->Binary(ynn_binary_add, 3309, 8352, 3310);
  g->Binary(ynn_binary_multiply, 3310, 7085, 3311);
  g->Binary(ynn_binary_divide, 3307, 7399, 3312);
  g->Unary(ynn_unary_round, 3312, 3314);
  g->Binary(ynn_binary_max, 3314, 7155, 3315);
  g->Binary(ynn_binary_min, 3315, 7270, 3316);
  g->Binary(ynn_binary_multiply, 3316, 7399, 3317);
  g->Convert(7847, 3318);
  g->Binary(ynn_binary_multiply, 3318, 7848, 3319);
  g->Matmul(3317, 3319, 3320, false, true);
  g->Binary(ynn_binary_divide, 3320, 7260, 3321);
  g->Unary(ynn_unary_round, 3321, 3322);
  g->Binary(ynn_binary_max, 3322, 7155, 3323);
  g->Binary(ynn_binary_min, 3323, 7270, 3325);
  g->Binary(ynn_binary_multiply, 3325, 7260, 3326);
  g->Polynomial(3326, 6608, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6608, 6609);
  g->Binary(ynn_binary_add, 6609, 6113, 6606);
  g->Binary(ynn_binary_multiply, 3326, 6111, 6607);
  g->Binary(ynn_binary_multiply, 6607, 6606, 3327);
  g->Binary(ynn_binary_multiply, 3327, 3311, 3328);
  g->Binary(ynn_binary_divide, 3328, 7222, 3329);
  g->Unary(ynn_unary_round, 3329, 3330);
  g->Binary(ynn_binary_max, 3330, 7155, 3331);
  g->Binary(ynn_binary_min, 3331, 7270, 3332);
  g->Binary(ynn_binary_multiply, 3332, 7222, 3333);
  g->Convert(7849, 3334);
  g->Binary(ynn_binary_multiply, 3334, 7850, 3336);
  g->Matmul(3333, 3336, 3337, false, true);
  g->Binary(ynn_binary_divide, 3337, 7081, 3338);
  g->Unary(ynn_unary_round, 3338, 3339);
  g->Binary(ynn_binary_max, 3339, 7155, 3340);
  g->Binary(ynn_binary_min, 3340, 7270, 3341);
  g->Binary(ynn_binary_multiply, 3341, 7081, 3342);
  g->Unary(ynn_unary_square, 3342, 3343);
  g->Reduce(ynn_reduce_sum, 3343, 6611, {2}, true);
  g->ShapeProduct(3343, 6610, {2});
  g->Binary(ynn_binary_divide, 6611, 6610, 3344);
  g->Binary(ynn_binary_add, 3344, 7303, 3345);
  g->Binary(ynn_binary_pow, 3345, 7358, 3347);
  g->Binary(ynn_binary_multiply, 3342, 3347, 3348);
  g->Convert(7853, 3349);
  g->Binary(ynn_binary_multiply, 3348, 3349, 3350);
  g->Binary(ynn_binary_add, 3307, 3350, 3351);
  g->Convert(7840, 3352);
  g->Binary(ynn_binary_multiply, 3351, 3352, 3353);
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
  g->Binary(ynn_binary_divide, 3361, 7181, 3362);
  g->Unary(ynn_unary_round, 3362, 3363);
  g->Binary(ynn_binary_max, 3363, 7155, 3364);
  g->Binary(ynn_binary_min, 3364, 7270, 3365);
  g->Binary(ynn_binary_multiply, 3365, 7181, 3366);
  g->Convert(7879, 3367);
  g->Binary(ynn_binary_multiply, 3367, 7880, 3369);
  g->Matmul(3366, 3369, 3370, false, true);
  g->Binary(ynn_binary_divide, 3370, 7135, 3371);
  g->Unary(ynn_unary_round, 3371, 3372);
  g->Binary(ynn_binary_max, 3372, 7155, 3373);
  g->Binary(ynn_binary_min, 3373, 7270, 3374);
  g->Binary(ynn_binary_multiply, 3374, 7135, 3375);
  g->SplitDim(3375, 3376, 2, {8,256});
  g->Transpose(3376, 3377, {0,2,1,3});
  g->Unary(ynn_unary_square, 3377, 3378);
  g->Reduce(ynn_reduce_sum, 3378, 6615, {3}, true);
  g->ShapeProduct(3378, 6614, {3});
  g->Binary(ynn_binary_divide, 6615, 6614, 3380);
  g->Binary(ynn_binary_add, 3380, 7303, 3381);
  g->Binary(ynn_binary_pow, 3381, 7358, 3382);
  g->Binary(ynn_binary_multiply, 3377, 3382, 3383);
  g->Convert(7878, 3384);
  g->Binary(ynn_binary_multiply, 3383, 3384, 3385);
  g->Slice(3385, 3386, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3385, 3387, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3387, 3388);
  g->Concat({3388,3386}, 3389, 3);
  g->Binary(ynn_binary_multiply, 3385, 2025, 3391);
  g->Binary(ynn_binary_multiply, 3389, 3078, 3392);
  g->Binary(ynn_binary_add, 3391, 3392, 3393);
}

// Scope: "Layer21 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(3393, 1946, 3394, false, true);
  g->Mask(3394, 7505, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 7505, 6619, {-1}, true);
  g->Binary(ynn_binary_subtract, 7505, 6619, 6616);
  g->Unary(ynn_unary_exp, 6616, 6617);
  g->Reduce(ynn_reduce_sum, 6617, 6620, {-1}, true);
  g->Binary(ynn_binary_divide, 6113, 6620, 6618);
  g->Binary(ynn_binary_multiply, 6617, 6618, 3395);
  g->Matmul(3395, 1948, 3396, false, false);
}

// Scope: "Layer21 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(3396, 3397, {0,2,1,3});
  g->FuseDims(3397, 3398, 2, 2);
  g->Binary(ynn_binary_divide, 3398, 7164, 3399);
  g->Unary(ynn_unary_round, 3399, 3402);
  g->Binary(ynn_binary_max, 3402, 7155, 3403);
  g->Binary(ynn_binary_min, 3403, 7270, 3404);
  g->Binary(ynn_binary_multiply, 3404, 7164, 3405);
  g->Convert(7876, 3406);
  g->Binary(ynn_binary_multiply, 3406, 7877, 3407);
  g->Matmul(3405, 3407, 3408, false, true);
  g->Binary(ynn_binary_divide, 3408, 7345, 3409);
  g->Unary(ynn_unary_round, 3409, 3410);
  g->Binary(ynn_binary_max, 3410, 7155, 3411);
  g->Binary(ynn_binary_min, 3411, 7270, 3413);
  g->Binary(ynn_binary_multiply, 3413, 7345, 3414);
}

// Scope: "Layer21 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3353, 3354);
  g->Reduce(ynn_reduce_sum, 3354, 6613, {2}, true);
  g->ShapeProduct(3354, 6612, {2});
  g->Binary(ynn_binary_divide, 6613, 6612, 3355);
  g->Binary(ynn_binary_add, 3355, 7303, 3356);
  g->Binary(ynn_binary_pow, 3356, 7358, 3358);
  g->Binary(ynn_binary_multiply, 3353, 3358, 3359);
  g->Convert(7860, 3360);
  g->Binary(ynn_binary_multiply, 3359, 3360, 3361);
  BuildLayer21AttentionQueryProjection(ctx);
  BuildLayer21AttentionSdpa(ctx);
  BuildLayer21AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 3414, 3415);
  g->Reduce(ynn_reduce_sum, 3415, 6622, {2}, true);
  g->ShapeProduct(3415, 6621, {2});
  g->Binary(ynn_binary_divide, 6622, 6621, 3416);
  g->Binary(ynn_binary_add, 3416, 7303, 3417);
  g->Binary(ynn_binary_pow, 3417, 7358, 3418);
  g->Binary(ynn_binary_multiply, 3414, 3418, 3419);
  g->Convert(7872, 3420);
  g->Binary(ynn_binary_multiply, 3419, 3420, 3421);
  g->Binary(ynn_binary_add, 3353, 3421, 3422);
}

// Scope: "Layer21 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3422, 3424);
  g->Reduce(ynn_reduce_sum, 3424, 6628, {2}, true);
  g->ShapeProduct(3424, 6627, {2});
  g->Binary(ynn_binary_divide, 6628, 6627, 3425);
  g->Binary(ynn_binary_add, 3425, 7303, 3426);
  g->Binary(ynn_binary_pow, 3426, 7358, 3427);
  g->Binary(ynn_binary_multiply, 3422, 3427, 3428);
  g->Convert(7875, 3429);
  g->Binary(ynn_binary_multiply, 3428, 3429, 3430);
  g->Binary(ynn_binary_divide, 3430, 7470, 3431);
  g->Unary(ynn_unary_round, 3431, 3432);
  g->Binary(ynn_binary_max, 3432, 7155, 3433);
  g->Binary(ynn_binary_min, 3433, 7270, 3435);
  g->Binary(ynn_binary_multiply, 3435, 7470, 3436);
  g->Convert(7866, 3437);
  g->Binary(ynn_binary_multiply, 3437, 7867, 3438);
  g->Matmul(3436, 3438, 3439, false, true);
  g->Binary(ynn_binary_divide, 3439, 7120, 3440);
  g->Unary(ynn_unary_round, 3440, 3441);
  g->Binary(ynn_binary_max, 3441, 7155, 3442);
  g->Binary(ynn_binary_min, 3442, 7270, 3443);
  g->Binary(ynn_binary_multiply, 3443, 7120, 3444);
  g->Convert(7864, 3446);
  g->Binary(ynn_binary_multiply, 3446, 7865, 3447);
  g->Matmul(3436, 3447, 3448, false, true);
  g->Binary(ynn_binary_divide, 3448, 7120, 3449);
  g->Unary(ynn_unary_round, 3449, 3450);
  g->Binary(ynn_binary_max, 3450, 7155, 3452);
  g->Binary(ynn_binary_min, 3452, 7270, 3453);
  g->Binary(ynn_binary_multiply, 3453, 7120, 3454);
  g->Polynomial(3454, 6631, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6631, 6632);
  g->Binary(ynn_binary_add, 6632, 6113, 6629);
  g->Binary(ynn_binary_multiply, 3454, 6111, 6630);
  g->Binary(ynn_binary_multiply, 6630, 6629, 3455);
  g->Binary(ynn_binary_multiply, 3444, 3455, 3456);
  g->Binary(ynn_binary_divide, 3456, 7138, 3457);
  g->Unary(ynn_unary_round, 3457, 3458);
  g->Binary(ynn_binary_max, 3458, 7155, 3459);
  g->Binary(ynn_binary_min, 3459, 7270, 3460);
  g->Binary(ynn_binary_multiply, 3460, 7138, 3461);
  g->Convert(7862, 3463);
  g->Binary(ynn_binary_multiply, 3463, 7863, 3464);
  g->Matmul(3461, 3464, 3465, false, true);
  g->Binary(ynn_binary_divide, 3465, 7396, 3466);
  g->Unary(ynn_unary_round, 3466, 3467);
  g->Binary(ynn_binary_max, 3467, 7155, 3468);
  g->Binary(ynn_binary_min, 3468, 7270, 3469);
  g->Binary(ynn_binary_multiply, 3469, 7396, 3470);
  g->Unary(ynn_unary_square, 3470, 3471);
  g->Reduce(ynn_reduce_sum, 3471, 6634, {2}, true);
  g->ShapeProduct(3471, 6633, {2});
  g->Binary(ynn_binary_divide, 6634, 6633, 3472);
  g->Binary(ynn_binary_add, 3472, 7303, 3474);
  g->Binary(ynn_binary_pow, 3474, 7358, 3475);
  g->Binary(ynn_binary_multiply, 3470, 3475, 3476);
  g->Convert(7873, 3477);
  g->Binary(ynn_binary_multiply, 3476, 3477, 3478);
  g->Binary(ynn_binary_add, 3422, 3478, 3479);
}

// Scope: "Layer21 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer21PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1022, 3480, {0,0,21,0}, {-1,-1,1,-1});
  g->Reshape(3480, 3481, {1,1,256});
  g->Binary(ynn_binary_add, 3481, 8353, 3482);
  g->Binary(ynn_binary_multiply, 3482, 7085, 3483);
  g->Binary(ynn_binary_divide, 3479, 7466, 3485);
  g->Unary(ynn_unary_round, 3485, 3486);
  g->Binary(ynn_binary_max, 3486, 7155, 3487);
  g->Binary(ynn_binary_min, 3487, 7270, 3488);
  g->Binary(ynn_binary_multiply, 3488, 7466, 3489);
  g->Convert(7868, 3490);
  g->Binary(ynn_binary_multiply, 3490, 7869, 3491);
  g->Matmul(3489, 3491, 3492, false, true);
  g->Binary(ynn_binary_divide, 3492, 7267, 3493);
  g->Unary(ynn_unary_round, 3493, 3494);
  g->Binary(ynn_binary_max, 3494, 7155, 3496);
  g->Binary(ynn_binary_min, 3496, 7270, 3497);
  g->Binary(ynn_binary_multiply, 3497, 7267, 3498);
  g->Polynomial(3498, 6637, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6637, 6638);
  g->Binary(ynn_binary_add, 6638, 6113, 6635);
  g->Binary(ynn_binary_multiply, 3498, 6111, 6636);
  g->Binary(ynn_binary_multiply, 6636, 6635, 3499);
  g->Binary(ynn_binary_multiply, 3499, 3483, 3500);
  g->Binary(ynn_binary_divide, 3500, 7400, 3501);
  g->Unary(ynn_unary_round, 3501, 3502);
  g->Binary(ynn_binary_max, 3502, 7155, 3503);
  g->Binary(ynn_binary_min, 3503, 7270, 3504);
  g->Binary(ynn_binary_multiply, 3504, 7400, 3505);
  g->Convert(7870, 3508);
  g->Binary(ynn_binary_multiply, 3508, 7871, 3509);
  g->Matmul(3505, 3509, 3510, false, true);
  g->Binary(ynn_binary_divide, 3510, 7393, 3511);
  g->Unary(ynn_unary_round, 3511, 3512);
  g->Binary(ynn_binary_max, 3512, 7155, 3513);
  g->Binary(ynn_binary_min, 3513, 7270, 3514);
  g->Binary(ynn_binary_multiply, 3514, 7393, 3515);
  g->Unary(ynn_unary_square, 3515, 3516);
  g->Reduce(ynn_reduce_sum, 3516, 6642, {2}, true);
  g->ShapeProduct(3516, 6641, {2});
  g->Binary(ynn_binary_divide, 6642, 6641, 3517);
  g->Binary(ynn_binary_add, 3517, 7303, 3519);
  g->Binary(ynn_binary_pow, 3519, 7358, 3520);
  g->Binary(ynn_binary_multiply, 3515, 3520, 3521);
  g->Convert(7874, 3522);
  g->Binary(ynn_binary_multiply, 3521, 3522, 3523);
  g->Binary(ynn_binary_add, 3479, 3523, 3524);
  g->Convert(7861, 3525);
  g->Binary(ynn_binary_multiply, 3524, 3525, 3526);
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
  g->Binary(ynn_binary_divide, 3534, 7258, 3535);
  g->Unary(ynn_unary_round, 3535, 3536);
  g->Binary(ynn_binary_max, 3536, 7155, 3537);
  g->Binary(ynn_binary_min, 3537, 7270, 3538);
  g->Binary(ynn_binary_multiply, 3538, 7258, 3539);
  g->Convert(7900, 3541);
  g->Binary(ynn_binary_multiply, 3541, 7901, 3542);
  g->Matmul(3539, 3542, 3543, false, true);
  g->Binary(ynn_binary_divide, 3543, 7185, 3544);
  g->Unary(ynn_unary_round, 3544, 3545);
  g->Binary(ynn_binary_max, 3545, 7155, 3546);
  g->Binary(ynn_binary_min, 3546, 7270, 3547);
  g->Binary(ynn_binary_multiply, 3547, 7185, 3548);
  g->SplitDim(3548, 3549, 2, {8,256});
  g->Transpose(3549, 3550, {0,2,1,3});
  g->Unary(ynn_unary_square, 3550, 3552);
  g->Reduce(ynn_reduce_sum, 3552, 6646, {3}, true);
  g->ShapeProduct(3552, 6645, {3});
  g->Binary(ynn_binary_divide, 6646, 6645, 3553);
  g->Binary(ynn_binary_add, 3553, 7303, 3554);
  g->Binary(ynn_binary_pow, 3554, 7358, 3555);
  g->Binary(ynn_binary_multiply, 3550, 3555, 3556);
  g->Convert(7899, 3557);
  g->Binary(ynn_binary_multiply, 3556, 3557, 3558);
  g->Slice(3558, 3559, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3558, 3560, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3560, 3561);
  g->Concat({3561,3559}, 3563, 3);
  g->Binary(ynn_binary_multiply, 3558, 2025, 3564);
  g->Binary(ynn_binary_multiply, 3563, 3078, 3565);
  g->Binary(ynn_binary_add, 3564, 3565, 3566);
}

// Scope: "Layer22 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(3566, 1946, 3567, false, true);
  g->Mask(3567, 7506, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 7506, 6650, {-1}, true);
  g->Binary(ynn_binary_subtract, 7506, 6650, 6647);
  g->Unary(ynn_unary_exp, 6647, 6648);
  g->Reduce(ynn_reduce_sum, 6648, 6651, {-1}, true);
  g->Binary(ynn_binary_divide, 6113, 6651, 6649);
  g->Binary(ynn_binary_multiply, 6648, 6649, 3568);
  g->Matmul(3568, 1948, 3569, false, false);
}

// Scope: "Layer22 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(3569, 3570, {0,2,1,3});
  g->FuseDims(3570, 3571, 2, 2);
  g->Binary(ynn_binary_divide, 3571, 7262, 3573);
  g->Unary(ynn_unary_round, 3573, 3574);
  g->Binary(ynn_binary_max, 3574, 7155, 3575);
  g->Binary(ynn_binary_min, 3575, 7270, 3576);
  g->Binary(ynn_binary_multiply, 3576, 7262, 3577);
  g->Convert(7897, 3578);
  g->Binary(ynn_binary_multiply, 3578, 7898, 3579);
  g->Matmul(3577, 3579, 3580, false, true);
  g->Binary(ynn_binary_divide, 3580, 7457, 3581);
  g->Unary(ynn_unary_round, 3581, 3582);
  g->Binary(ynn_binary_max, 3582, 7155, 3584);
  g->Binary(ynn_binary_min, 3584, 7270, 3585);
  g->Binary(ynn_binary_multiply, 3585, 7457, 3586);
}

// Scope: "Layer22 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3526, 3527);
  g->Reduce(ynn_reduce_sum, 3527, 6644, {2}, true);
  g->ShapeProduct(3527, 6643, {2});
  g->Binary(ynn_binary_divide, 6644, 6643, 3528);
  g->Binary(ynn_binary_add, 3528, 7303, 3530);
  g->Binary(ynn_binary_pow, 3530, 7358, 3531);
  g->Binary(ynn_binary_multiply, 3526, 3531, 3532);
  g->Convert(7881, 3533);
  g->Binary(ynn_binary_multiply, 3532, 3533, 3534);
  BuildLayer22AttentionQueryProjection(ctx);
  BuildLayer22AttentionSdpa(ctx);
  BuildLayer22AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 3586, 3587);
  g->Reduce(ynn_reduce_sum, 3587, 6653, {2}, true);
  g->ShapeProduct(3587, 6652, {2});
  g->Binary(ynn_binary_divide, 6653, 6652, 3588);
  g->Binary(ynn_binary_add, 3588, 7303, 3589);
  g->Binary(ynn_binary_pow, 3589, 7358, 3590);
  g->Binary(ynn_binary_multiply, 3586, 3590, 3591);
  g->Convert(7893, 3592);
  g->Binary(ynn_binary_multiply, 3591, 3592, 3593);
  g->Binary(ynn_binary_add, 3526, 3593, 3595);
}

// Scope: "Layer22 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3595, 3596);
  g->Reduce(ynn_reduce_sum, 3596, 6657, {2}, true);
  g->ShapeProduct(3596, 6656, {2});
  g->Binary(ynn_binary_divide, 6657, 6656, 3597);
  g->Binary(ynn_binary_add, 3597, 7303, 3598);
  g->Binary(ynn_binary_pow, 3598, 7358, 3599);
  g->Binary(ynn_binary_multiply, 3595, 3599, 3600);
  g->Convert(7896, 3601);
  g->Binary(ynn_binary_multiply, 3600, 3601, 3602);
  g->Binary(ynn_binary_divide, 3602, 7140, 3603);
  g->Unary(ynn_unary_round, 3603, 3604);
  g->Binary(ynn_binary_max, 3604, 7155, 3606);
  g->Binary(ynn_binary_min, 3606, 7270, 3607);
  g->Binary(ynn_binary_multiply, 3607, 7140, 3608);
  g->Convert(7887, 3609);
  g->Binary(ynn_binary_multiply, 3609, 7888, 3610);
  g->Matmul(3608, 3610, 3611, false, true);
  g->Binary(ynn_binary_divide, 3611, 7224, 3612);
  g->Unary(ynn_unary_round, 3612, 3613);
  g->Binary(ynn_binary_max, 3613, 7155, 3614);
  g->Binary(ynn_binary_min, 3614, 7270, 3615);
  g->Binary(ynn_binary_multiply, 3615, 7224, 3618);
  g->Convert(7885, 3619);
  g->Binary(ynn_binary_multiply, 3619, 7886, 3620);
  g->Matmul(3608, 3620, 3621, false, true);
  g->Binary(ynn_binary_divide, 3621, 7224, 3622);
  g->Unary(ynn_unary_round, 3622, 3624);
  g->Binary(ynn_binary_max, 3624, 7155, 3625);
  g->Binary(ynn_binary_min, 3625, 7270, 3626);
  g->Binary(ynn_binary_multiply, 3626, 7224, 3627);
  g->Polynomial(3627, 6660, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6660, 6661);
  g->Binary(ynn_binary_add, 6661, 6113, 6658);
  g->Binary(ynn_binary_multiply, 3627, 6111, 6659);
  g->Binary(ynn_binary_multiply, 6659, 6658, 3628);
  g->Binary(ynn_binary_multiply, 3618, 3628, 3629);
  g->Binary(ynn_binary_divide, 3629, 7154, 3630);
  g->Unary(ynn_unary_round, 3630, 3631);
  g->Binary(ynn_binary_max, 3631, 7155, 3632);
  g->Binary(ynn_binary_min, 3632, 7270, 3633);
  g->Binary(ynn_binary_multiply, 3633, 7154, 3635);
  g->Convert(7883, 3636);
  g->Binary(ynn_binary_multiply, 3636, 7884, 3637);
  g->Matmul(3635, 3637, 3638, false, true);
  g->Binary(ynn_binary_divide, 3638, 7464, 3639);
  g->Unary(ynn_unary_round, 3639, 3640);
  g->Binary(ynn_binary_max, 3640, 7155, 3641);
  g->Binary(ynn_binary_min, 3641, 7270, 3642);
  g->Binary(ynn_binary_multiply, 3642, 7464, 3643);
  g->Unary(ynn_unary_square, 3643, 3644);
  g->Reduce(ynn_reduce_sum, 3644, 6663, {2}, true);
  g->ShapeProduct(3644, 6662, {2});
  g->Binary(ynn_binary_divide, 6663, 6662, 3646);
  g->Binary(ynn_binary_add, 3646, 7303, 3647);
  g->Binary(ynn_binary_pow, 3647, 7358, 3648);
  g->Binary(ynn_binary_multiply, 3643, 3648, 3649);
  g->Convert(7894, 3650);
  g->Binary(ynn_binary_multiply, 3649, 3650, 3651);
  g->Binary(ynn_binary_add, 3595, 3651, 3652);
}

// Scope: "Layer22 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer22PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1022, 3653, {0,0,22,0}, {-1,-1,1,-1});
  g->Reshape(3653, 3654, {1,1,256});
  g->Binary(ynn_binary_add, 3654, 8354, 3655);
  g->Binary(ynn_binary_multiply, 3655, 7085, 3657);
  g->Binary(ynn_binary_divide, 3652, 7148, 3658);
  g->Unary(ynn_unary_round, 3658, 3659);
  g->Binary(ynn_binary_max, 3659, 7155, 3660);
  g->Binary(ynn_binary_min, 3660, 7270, 3661);
  g->Binary(ynn_binary_multiply, 3661, 7148, 3662);
  g->Convert(7889, 3663);
  g->Binary(ynn_binary_multiply, 3663, 7890, 3664);
  g->Matmul(3662, 3664, 3665, false, true);
  g->Binary(ynn_binary_divide, 3665, 7255, 3666);
  g->Unary(ynn_unary_round, 3666, 3668);
  g->Binary(ynn_binary_max, 3668, 7155, 3669);
  g->Binary(ynn_binary_min, 3669, 7270, 3670);
  g->Binary(ynn_binary_multiply, 3670, 7255, 3671);
  g->Polynomial(3671, 6666, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6666, 6667);
  g->Binary(ynn_binary_add, 6667, 6113, 6664);
  g->Binary(ynn_binary_multiply, 3671, 6111, 6665);
  g->Binary(ynn_binary_multiply, 6665, 6664, 3672);
  g->Binary(ynn_binary_multiply, 3672, 3657, 3673);
  g->Binary(ynn_binary_divide, 3673, 7349, 3674);
  g->Unary(ynn_unary_round, 3674, 3675);
  g->Binary(ynn_binary_max, 3675, 7155, 3676);
  g->Binary(ynn_binary_min, 3676, 7270, 3677);
  g->Binary(ynn_binary_multiply, 3677, 7349, 3679);
  g->Convert(7891, 3680);
  g->Binary(ynn_binary_multiply, 3680, 7892, 3681);
  g->Matmul(3679, 3681, 3682, false, true);
  g->Binary(ynn_binary_divide, 3682, 7187, 3683);
  g->Unary(ynn_unary_round, 3683, 3684);
  g->Binary(ynn_binary_max, 3684, 7155, 3685);
  g->Binary(ynn_binary_min, 3685, 7270, 3686);
  g->Binary(ynn_binary_multiply, 3686, 7187, 3687);
  g->Unary(ynn_unary_square, 3687, 3688);
  g->Reduce(ynn_reduce_sum, 3688, 6669, {2}, true);
  g->ShapeProduct(3688, 6668, {2});
  g->Binary(ynn_binary_divide, 6669, 6668, 3690);
  g->Binary(ynn_binary_add, 3690, 7303, 3691);
  g->Binary(ynn_binary_pow, 3691, 7358, 3692);
  g->Binary(ynn_binary_multiply, 3687, 3692, 3693);
  g->Convert(7895, 3694);
  g->Binary(ynn_binary_multiply, 3693, 3694, 3695);
  g->Binary(ynn_binary_add, 3652, 3695, 3696);
  g->Convert(7882, 3697);
  g->Binary(ynn_binary_multiply, 3696, 3697, 3698);
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
  g->Binary(ynn_binary_divide, 3706, 7199, 3707);
  g->Unary(ynn_unary_round, 3707, 3708);
  g->Binary(ynn_binary_max, 3708, 7155, 3709);
  g->Binary(ynn_binary_min, 3709, 7270, 3710);
  g->Binary(ynn_binary_multiply, 3710, 7199, 3712);
  g->Convert(7921, 3713);
  g->Binary(ynn_binary_multiply, 3713, 7922, 3714);
  g->Matmul(3712, 3714, 3715, false, true);
  g->Binary(ynn_binary_divide, 3715, 7453, 3716);
  g->Unary(ynn_unary_round, 3716, 3717);
  g->Binary(ynn_binary_max, 3717, 7155, 3718);
  g->Binary(ynn_binary_min, 3718, 7270, 3719);
  g->Binary(ynn_binary_multiply, 3719, 7453, 3720);
  g->SplitDim(3720, 3721, 2, {8,256});
  g->Transpose(3721, 3724, {0,2,1,3});
  g->Unary(ynn_unary_square, 3724, 3725);
  g->Reduce(ynn_reduce_sum, 3725, 6675, {3}, true);
  g->ShapeProduct(3725, 6674, {3});
  g->Binary(ynn_binary_divide, 6675, 6674, 3726);
  g->Binary(ynn_binary_add, 3726, 7303, 3727);
  g->Binary(ynn_binary_pow, 3727, 7358, 3728);
  g->Binary(ynn_binary_multiply, 3724, 3728, 3729);
  g->Convert(7920, 3730);
  g->Binary(ynn_binary_multiply, 3729, 3730, 3731);
  g->Slice(3731, 3732, {0,0,0,0}, {-1,-1,-1,128});
  g->Slice(3731, 3733, {0,0,0,128}, {-1,-1,-1,128});
  g->Unary(ynn_unary_negate, 3733, 3735);
  g->Concat({3735,3732}, 3736, 3);
  g->Binary(ynn_binary_multiply, 3731, 2025, 3737);
  g->Binary(ynn_binary_multiply, 3736, 3078, 3738);
  g->Binary(ynn_binary_add, 3737, 3738, 3739);
}

// Scope: "Layer23 / Attention / Sdpa"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23AttentionSdpa(Context& ctx) {
  auto* g = ctx.g;
  const slinky::expr& s2 = ctx.s2;
  g->Matmul(3739, 1946, 3740, false, true);
  g->Mask(3740, 7507, s2, slinky::max(slinky::expr(int64_t{0}), (slinky::expr(int64_t{-511}) + (slinky::expr(int64_t{1}) * s2))), 512, true);
  g->Reduce(ynn_reduce_max, 7507, 6679, {-1}, true);
  g->Binary(ynn_binary_subtract, 7507, 6679, 6676);
  g->Unary(ynn_unary_exp, 6676, 6677);
  g->Reduce(ynn_reduce_sum, 6677, 6680, {-1}, true);
  g->Binary(ynn_binary_divide, 6113, 6680, 6678);
  g->Binary(ynn_binary_multiply, 6677, 6678, 3741);
  g->Matmul(3741, 1948, 3742, false, false);
}

// Scope: "Layer23 / Attention / OutputProjection"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23AttentionOutputProjection(Context& ctx) {
  auto* g = ctx.g;
  g->Transpose(3742, 3743, {0,2,1,3});
  g->FuseDims(3743, 3745, 2, 2);
  g->Binary(ynn_binary_divide, 3745, 7418, 3746);
  g->Unary(ynn_unary_round, 3746, 3747);
  g->Binary(ynn_binary_max, 3747, 7155, 3748);
  g->Binary(ynn_binary_min, 3748, 7270, 3749);
  g->Binary(ynn_binary_multiply, 3749, 7418, 3750);
  g->Convert(7918, 3751);
  g->Binary(ynn_binary_multiply, 3751, 7919, 3752);
  g->Matmul(3750, 3752, 3753, false, true);
  g->Binary(ynn_binary_divide, 3753, 7332, 3754);
  g->Unary(ynn_unary_round, 3754, 3756);
  g->Binary(ynn_binary_max, 3756, 7155, 3757);
  g->Binary(ynn_binary_min, 3757, 7270, 3758);
  g->Binary(ynn_binary_multiply, 3758, 7332, 3759);
}

// Scope: "Layer23 / Attention"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23Attention(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3698, 3699);
  g->Reduce(ynn_reduce_sum, 3699, 6673, {2}, true);
  g->ShapeProduct(3699, 6672, {2});
  g->Binary(ynn_binary_divide, 6673, 6672, 3701);
  g->Binary(ynn_binary_add, 3701, 7303, 3702);
  g->Binary(ynn_binary_pow, 3702, 7358, 3703);
  g->Binary(ynn_binary_multiply, 3698, 3703, 3704);
  g->Convert(7902, 3705);
  g->Binary(ynn_binary_multiply, 3704, 3705, 3706);
  BuildLayer23AttentionQueryProjection(ctx);
  BuildLayer23AttentionSdpa(ctx);
  BuildLayer23AttentionOutputProjection(ctx);
  g->Unary(ynn_unary_square, 3759, 3760);
  g->Reduce(ynn_reduce_sum, 3760, 6682, {2}, true);
  g->ShapeProduct(3760, 6681, {2});
  g->Binary(ynn_binary_divide, 6682, 6681, 3761);
  g->Binary(ynn_binary_add, 3761, 7303, 3762);
  g->Binary(ynn_binary_pow, 3762, 7358, 3763);
  g->Binary(ynn_binary_multiply, 3759, 3763, 3764);
  g->Convert(7914, 3765);
  g->Binary(ynn_binary_multiply, 3764, 3765, 3767);
  g->Binary(ynn_binary_add, 3698, 3767, 3768);
}

// Scope: "Layer23 / Mlp"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23Mlp(Context& ctx) {
  auto* g = ctx.g;
  g->Unary(ynn_unary_square, 3768, 3769);
  g->Reduce(ynn_reduce_sum, 3769, 6684, {2}, true);
  g->ShapeProduct(3769, 6683, {2});
  g->Binary(ynn_binary_divide, 6684, 6683, 3770);
  g->Binary(ynn_binary_add, 3770, 7303, 3771);
  g->Binary(ynn_binary_pow, 3771, 7358, 3772);
  g->Binary(ynn_binary_multiply, 3768, 3772, 3773);
  g->Convert(7917, 3774);
  g->Binary(ynn_binary_multiply, 3773, 3774, 3775);
  g->Binary(ynn_binary_divide, 3775, 7197, 3776);
  g->Unary(ynn_unary_round, 3776, 3778);
  g->Binary(ynn_binary_max, 3778, 7155, 3779);
  g->Binary(ynn_binary_min, 3779, 7270, 3780);
  g->Binary(ynn_binary_multiply, 3780, 7197, 3781);
  g->Convert(7908, 3782);
  g->Binary(ynn_binary_multiply, 3782, 7909, 3783);
  g->Matmul(3781, 3783, 3784, false, true);
  g->Binary(ynn_binary_divide, 3784, 7363, 3785);
  g->Unary(ynn_unary_round, 3785, 3786);
  g->Binary(ynn_binary_max, 3786, 7155, 3787);
  g->Binary(ynn_binary_min, 3787, 7270, 3789);
  g->Binary(ynn_binary_multiply, 3789, 7363, 3790);
  g->Convert(7906, 3791);
  g->Binary(ynn_binary_multiply, 3791, 7907, 3792);
  g->Matmul(3781, 3792, 3793, false, true);
  g->Binary(ynn_binary_divide, 3793, 7363, 3795);
  g->Unary(ynn_unary_round, 3795, 3796);
  g->Binary(ynn_binary_max, 3796, 7155, 3797);
  g->Binary(ynn_binary_min, 3797, 7270, 3798);
  g->Binary(ynn_binary_multiply, 3798, 7363, 3799);
  g->Polynomial(3799, 6687, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6687, 6688);
  g->Binary(ynn_binary_add, 6688, 6113, 6685);
  g->Binary(ynn_binary_multiply, 3799, 6111, 6686);
  g->Binary(ynn_binary_multiply, 6686, 6685, 3800);
  g->Binary(ynn_binary_multiply, 3790, 3800, 3801);
  g->Binary(ynn_binary_divide, 3801, 7454, 3802);
  g->Unary(ynn_unary_round, 3802, 3803);
  g->Binary(ynn_binary_max, 3803, 7155, 3804);
  g->Binary(ynn_binary_min, 3804, 7270, 3806);
  g->Binary(ynn_binary_multiply, 3806, 7454, 3807);
  g->Convert(7904, 3808);
  g->Binary(ynn_binary_multiply, 3808, 7905, 3809);
  g->Matmul(3807, 3809, 3810, false, true);
  g->Binary(ynn_binary_divide, 3810, 7407, 3811);
  g->Unary(ynn_unary_round, 3811, 3812);
  g->Binary(ynn_binary_max, 3812, 7155, 3813);
  g->Binary(ynn_binary_min, 3813, 7270, 3814);
  g->Binary(ynn_binary_multiply, 3814, 7407, 3815);
  g->Unary(ynn_unary_square, 3815, 3817);
  g->Reduce(ynn_reduce_sum, 3817, 6690, {2}, true);
  g->ShapeProduct(3817, 6689, {2});
  g->Binary(ynn_binary_divide, 6690, 6689, 3818);
  g->Binary(ynn_binary_add, 3818, 7303, 3819);
  g->Binary(ynn_binary_pow, 3819, 7358, 3820);
  g->Binary(ynn_binary_multiply, 3815, 3820, 3821);
  g->Convert(7915, 3822);
  g->Binary(ynn_binary_multiply, 3821, 3822, 3823);
  g->Binary(ynn_binary_add, 3768, 3823, 3824);
}

// Scope: "Layer23 / PerLayerEmbedding"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23PerLayerEmbedding(Context& ctx) {
  auto* g = ctx.g;
  g->Slice(1022, 3825, {0,0,23,0}, {-1,-1,1,-1});
  g->Reshape(3825, 3826, {1,1,256});
  g->Binary(ynn_binary_add, 3826, 8355, 3829);
  g->Binary(ynn_binary_multiply, 3829, 7085, 3830);
  g->Binary(ynn_binary_divide, 3824, 7095, 3831);
  g->Unary(ynn_unary_round, 3831, 3832);
  g->Binary(ynn_binary_max, 3832, 7155, 3833);
  g->Binary(ynn_binary_min, 3833, 7270, 3834);
  g->Binary(ynn_binary_multiply, 3834, 7095, 3835);
  g->Convert(7910, 3836);
  g->Binary(ynn_binary_multiply, 3836, 7911, 3837);
  g->Matmul(3835, 3837, 3838, false, true);
  g->Binary(ynn_binary_divide, 3838, 7178, 3840);
  g->Unary(ynn_unary_round, 3840, 3841);
  g->Binary(ynn_binary_max, 3841, 7155, 3842);
  g->Binary(ynn_binary_min, 3842, 7270, 3843);
  g->Binary(ynn_binary_multiply, 3843, 7178, 3844);
  g->Polynomial(3844, 6693, {0.0,0.7978845608028654,0.0,0.035677408136300125});
  g->Unary(ynn_unary_tanh, 6693, 6694);
  g->Binary(ynn_binary_add, 6694, 6113, 6691);
  g->Binary(ynn_binary_multiply, 3844, 6111, 6692);
  g->Binary(ynn_binary_multiply, 6692, 6691, 3845);
  g->Binary(ynn_binary_multiply, 3845, 3830, 3846);
  g->Binary(ynn_binary_divide, 3846, 7209, 3847);
  g->Unary(ynn_unary_round, 3847, 3848);
  g->Binary(ynn_binary_max, 3848, 7155, 3849);
  g->Binary(ynn_binary_min, 3849, 7270, 3851);
  g->Binary(ynn_binary_multiply, 3851, 7209, 3852);
  g->Convert(7912, 3853);
  g->Binary(ynn_binary_multiply, 3853, 7913, 3854);
  g->Matmul(3852, 3854, 3855, false, true);
  g->Binary(ynn_binary_divide, 3855, 7237, 3856);
  g->Unary(ynn_unary_round, 3856, 3857);
  g->Binary(ynn_binary_max, 3857, 7155, 3858);
  g->Binary(ynn_binary_min, 3858, 7270, 3859);
  g->Binary(ynn_binary_multiply, 3859, 7237, 3860);
  g->Unary(ynn_unary_square, 3860, 3862);
  g->Reduce(ynn_reduce_sum, 3862, 6696, {2}, true);
  g->ShapeProduct(3862, 6695, {2});
  g->Binary(ynn_binary_divide, 6696, 6695, 3863);
  g->Binary(ynn_binary_add, 3863, 7303, 3864);
  g->Binary(ynn_binary_pow, 3864, 7358, 3865);
  g->Binary(ynn_binary_multiply, 3860, 3865, 3866);
  g->Convert(7916, 3867);
  g->Binary(ynn_binary_multiply, 3866, 3867, 3868);
  g->Binary(ynn_binary_add, 3824, 3868, 3869);
  g->Convert(7903, 3870);
  g->Binary(ynn_binary_multiply, 3869, 3870, 3871);
}

// Scope: "Layer23"
LAB_YNN_BUILDER_NOINLINE void BuildLayer23(Context& ctx) {
  BuildLayer23Attention(ctx);
  BuildLayer23Mlp(ctx);
  BuildLayer23PerLayerEmbedding(ctx);
}

}  // namespace BuildGemma4DecodeSource
