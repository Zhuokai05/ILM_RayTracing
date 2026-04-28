#ifndef QUAD_HPP
#define QUAD_HPP

#include <glm/vec3.hpp>
#include "../shape.hpp"

struct quad : public shape {
    std::size_t material_index;
    glm::vec3 point;
    glm::vec3 u;
    glm::vec3 v;

    quad(const std::size_t material_index, const glm::vec3 point, const glm::vec3 u, const glm::vec3 v)
        : material_index{material_index}, point{point}, u{u}, v{v} { }
    bool Intersect(const ray &ray, float tMin, float tMax) const override;
    bool Intersect(const ray &ray, float tMin, float tMax, ShapeIntersection& out_intersection) const override;
};

#endif
