#include "sphere.hpp"
#include <glm/geometric.hpp>
#include <glm/ext/scalar_constants.hpp>

bool sphere::Intersect(const ray &ray, float tMin, float tMax) const {
    ShapeIntersection unused;
    return Intersect(ray, tMin, tMax, unused);
}

bool sphere::Intersect(const ray &ray, float tMin, float tMax, ShapeIntersection &out_intersection) const {
    glm::vec3 oc = center - ray.origin();
    const auto a = glm::dot(ray.direction(), ray.direction());

    const auto h = glm::dot(ray.direction(), oc);
    // const auto b = -2.0 * h;
    const auto b = h;
    const auto c = glm::dot(oc, oc) - radius * radius;
    // const auto discriminant = b*b - 4.0*a*c;
    const auto discriminant = b*b - a*c;

    const auto sqrtd = std::sqrt(discriminant);
    const auto root = (h - sqrtd) / a;

    if (tMin <= root && root <= tMax) {
        const auto local = ray.at(root) - center;

        const auto local_normalized = local / radius;
        const auto theta = std::acos(-local_normalized.y);
        const auto phi = std::atan2(-local_normalized.z, local_normalized.x) + glm::pi<float>();

        const auto u = phi / (2.0f * glm::pi<float>());
        const auto v = theta / glm::pi<float>();
        out_intersection = ShapeIntersection{
            material_index,
            static_cast<float>(root),
            local_normalized,
            glm::vec2{u, v}
        };
        return (discriminant >= 0);
    } else {
        return false;
    }
}
