#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <glm/vec3.hpp>
#include "../shape.hpp"
#include <cstddef>

struct sphere : public shape {
    std::size_t material_index;
    glm::vec3 center;
    float radius;

    // inline ~sphere() override = default;
    inline sphere(std::size_t material_index, glm::vec3 center, float radius)
        : material_index(material_index), center(center), radius(radius) { }
    bool Intersect(const ray &ray, float tMin, float tMax) const override;
    bool Intersect(const ray &ray, float tMin, float tMax, ShapeIntersection& out_intersection) const override;
};

#endif
