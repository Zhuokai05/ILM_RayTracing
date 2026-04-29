#include "texture_constant.hpp"

Color texture_constant::sample(const glm::vec2 uv) const {
    return color;
}