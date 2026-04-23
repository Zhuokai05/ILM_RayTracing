#include "light_ambient.hpp"
#include <glm/gtc/random.hpp>
#include <glm/glm.hpp>

Color light_ambient::shade(const ray &ray, const ShapeIntersection &hit, const Material &hit_material) const {
    (void)ray;
    (void)hit;
    (void)hit_material;
    return ambient;
}

glm::vec3 light_ambient::shadow_direction(const glm::vec3 surface_point) const {
    const glm::vec3 random_shadow_direction = glm::sphericalRand(1.0f);
    static constexpr glm::vec3 bias_shadow_direction = glm::vec3{0.0, 1.0, 0.0};
    return glm::normalize(glm::mix(random_shadow_direction, bias_shadow_direction, 0.5f));
}
