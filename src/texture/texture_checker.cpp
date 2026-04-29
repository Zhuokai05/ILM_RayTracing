#include "texture_checker.hpp"

Color texture_checker::sample(const glm::vec2 uv) const {
    const int u = static_cast<std::size_t>(std::floor(uv.x * tiling.x + offset.x));
    const int v = static_cast<std::size_t>(std::floor(uv.y * tiling.y + offset.y));
    if ((u + v) % 2 == 0) {
        return color_a;
    } else {
        return color_b;
    }
}