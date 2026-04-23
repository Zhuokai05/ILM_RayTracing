#include "light_directional.hpp"
#include "lighting.hpp"
#include <glm/geometric.hpp>

Color light_directional::shade(const ray &ray, const ShapeIntersection &hit, const Material &hit_material) const {
    const float diffuse_factor = lighting_diffuse_ws(-direction, hit.normal);
    const float specular_factor = lighting_specular_phong_ws(-direction, hit.normal, -ray.direction(), specular_power);
    return hit_material.color * diffuse * diffuse_factor
        + specular * specular_factor;
}