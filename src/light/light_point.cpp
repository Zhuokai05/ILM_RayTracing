#include "light_point.hpp"
#include "lighting.hpp"

Color light_point::shade(const ray &ray, const ShapeIntersection &hit, const Material &hit_material) const {
    const glm::vec3 surface = ray.at(hit.time_of_intersection);
    const glm::vec3 direction = glm::normalize(surface - position);

    const float diffuse_factor = lighting_diffuse_ws(-direction, hit.normal);
    const float specular_factor = lighting_specular_phong_ws(-direction, hit.normal, -ray.direction(), specular_power);
    return hit_material.color * diffuse * diffuse_factor
        + specular * specular_factor;
}

glm::vec3 light_point::shadow_direction(const glm::vec3 surface_point) const {
    return glm::normalize(position - surface_point);
}
