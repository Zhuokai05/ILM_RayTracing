#ifndef TEXTURE_CHECKER_HPP
#define TEXTURE_CHECKER_HPP

#include "../texture.hpp"
#include <glm/vec2.hpp>

struct texture_checker : public texture {
    Color color_a;
    Color color_b;

    glm::vec2 tiling;
    glm::vec2 offset;

    explicit texture_checker(const Color color_a, const Color color_b, const glm::vec2 tiling, const glm::vec2 offset)
        : color_a(color_a), color_b(color_b), tiling(tiling), offset(offset) {}
    Color sample(const glm::vec2 uv) const override;
};

#endif
