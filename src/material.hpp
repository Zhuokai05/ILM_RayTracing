#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "Color.h"
#include "texture.hpp"
#include <glm/vec2.hpp>
#include <memory>

struct Material {
    Color color;
    std::size_t texture_index;
    float reflection_factor;

    template <typename Container>
    inline constexpr const texture &get_texture(const Container &textures) const {
        return textures.at(texture_index);
    }
    template <template <typename T> typename Container, typename TextureType>
    inline constexpr const texture &get_texture(const Container<std::unique_ptr<TextureType>> &textures) const {
        return *(textures.at(texture_index));
    }
    Color sample(const glm::vec2 uv, const texture &texture) const;
};

#endif
