#ifndef SHAPEINTERSECTION_HPP
#define SHAPEINTERSECTION_HPP

#include <cstddef>

struct ShapeIntersection {
    std::size_t material_index;
    float time_of_intersection;
    glm::vec3 normal;
};

#endif