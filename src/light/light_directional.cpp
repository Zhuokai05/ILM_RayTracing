#include "light_directional.hpp"
#include "lighting.hpp"
#include <glm/geometric.hpp>

Color light_directional::shade(const ray &ray, const ShapeIntersection &hit, const Material &hit_material, const texture &hit_texture) const {
    const float diffuse_factor = lighting_diffuse_ws(-direction, hit.normal);
    const float specular_factor = lighting_specular_phong_ws(-direction, hit.normal, -ray.direction(), specular_power);
    return hit_material.sample(hit.texcoord, hit_texture) * diffuse * diffuse_factor
        + specular * specular_factor;
}

glm::vec3 light_directional::shadow_direction(const glm::vec3 surface_point) const {
    return -direction;
}
