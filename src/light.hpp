#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "Color.h"
#include "shapeIntersection.hpp"
#include "material.hpp"
#include "ray.hpp"
#include "texture.hpp"

struct light {
    virtual ~light() = default;
    virtual Color shade(const ray &ray, const ShapeIntersection &hit, const Material &hit_material, const texture &hit_texture) const = 0;
    virtual glm::vec3 shadow_direction(const glm::vec3 surface_point) const = 0;
};

#endif
