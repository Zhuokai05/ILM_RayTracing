#ifndef TEXTURE_UV_HPP
#define TEXTURE_UV_HPP

#include "../texture.hpp"

struct texture_uv : public texture {
    Color color_u;
    Color color_v;

    explicit texture_uv(const Color color_u, const Color color_v) : color_u(color_u), color_v(color_v) {}
    Color sample(const glm::vec2 uv) const override;
};

#endif
