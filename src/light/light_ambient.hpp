#ifndef LIGHT_AMBIENT_HPP
#define LIGHT_AMBIENT_HPP

#include "../light.hpp"
#include "../Color.h"

struct light_ambient : public light {
    Color ambient;

    light_ambient(Color ambient) : ambient{ambient} { }
    Color shade(const ray &ray, const ShapeIntersection &hit, const Material &hit_material) const override;
    glm::vec3 shadow_direction(const glm::vec3 surface_point) const override;
};

#endif
