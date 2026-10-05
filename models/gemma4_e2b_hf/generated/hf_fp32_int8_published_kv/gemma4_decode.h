// Generated YNNPACK builder; do not edit.
#pragma once
#include <cstddef>
#include <functional>
#include <memory>

namespace lab_ynn { class Graph; }

std::unique_ptr<lab_ynn::Graph> BuildGemma4Decode(
    const std::function<const void*(const char*, size_t)>& weights);
