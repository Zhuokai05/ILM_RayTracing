#ifndef LIGHT_POINT_HPP
#define LIGHT_POINT_HPP

#include <glm/vec3.hpp>
#include "../light.hpp"
#include "../Color.h"

struct light_point : public light {
    glm::vec3 position;
    Color diffuse;
    Color specular;
    float specular_power;

    light_point(glm::vec3 position, Color diffuse, Color specular, float specular_power)
        : position{position}, diffuse{diffuse}, specular{specular}, specular_power{specular_power} { }
    Color shade(const ray &ray, const ShapeIntersection &hit, const Material &hit_material) const override;
};

#endif
