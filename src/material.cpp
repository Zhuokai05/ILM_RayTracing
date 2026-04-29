#include "material.hpp"

Color Material::sample(const glm::vec2 uv, const texture &texture) const {
    return color * texture.sample(uv);
}