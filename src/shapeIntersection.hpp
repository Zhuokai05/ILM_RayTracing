#ifndef SHAPEINTERSECTION_HPP
#define SHAPEINTERSECTION_HPP

#include <cstddef>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

struct ShapeIntersection {
    std::size_t material_index;
    float time_of_intersection;
    glm::vec3 normal;
    glm::vec2 texcoord;
};

#endif