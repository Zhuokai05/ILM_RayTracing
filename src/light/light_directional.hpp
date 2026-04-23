#ifndef LIGHT_DIRECTIONAL_HPP
#define LIGHT_DIRECTIONAL_HPP

#include "../light.hpp"

struct light_directional : public light {
    glm::vec3 direction;
    Color color;

    light_directional(glm::vec3 direction, Color color)
        : direction{direction}, color{color} { }
    Color shade(const ray &ray, const ShapeIntersection &hit, const Material &hit_material) const;
};

#endif
