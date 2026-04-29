#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "Color.h"
#include <glm/vec2.hpp>

struct texture {
    virtual ~texture() = default;
    virtual Color sample(const glm::vec2 uv) const = 0;
};

#endif
