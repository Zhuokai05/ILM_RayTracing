#include "texture_uv.hpp"

Color texture_uv::sample(const glm::vec2 uv) const {
    return color_u * uv.x + color_v * uv.y;
}