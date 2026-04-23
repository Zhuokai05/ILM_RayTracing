#ifndef LIGHT_DIRECTIONAL_HPP
#define LIGHT_DIRECTIONAL_HPP

#include "../light.hpp"

struct light_directional : public light {
    glm::vec3 direction;
    Color diffuse;
    Color specular;
    float specular_power;

    light_directional(glm::vec3 direction, Color diffuse, Color specular, float specular_power)
        : direction{direction}, diffuse{diffuse}, specular{specular}, specular_power{specular_power} { }
    Color shade(const ray &ray, const ShapeIntersection &hit, const Material &hit_material) const;
};

#endif
