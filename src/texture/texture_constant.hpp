#ifndef TEXTURE_CONSTANT_HPP
#define TEXTURE_CONSTANT_HPP

#include "../texture.hpp"

struct texture_constant : public texture {
    Color color;

    explicit texture_constant(const Color color) : color(color) {}

    Color sample(const glm::vec2 uv) const override;
};

#endif
