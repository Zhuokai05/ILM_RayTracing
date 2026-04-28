#include "sphere.hpp"
#include <glm/geometric.hpp>

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
    out_intersection = ShapeIntersection{
        material_index,
        static_cast<float>(root),
        glm::normalize(ray.at(root) - center),
        glm::vec2{std::numeric_limits<float>::signaling_NaN(), std::numeric_limits<float>::signaling_NaN()}
    };
    return (discriminant >= 0);
}
