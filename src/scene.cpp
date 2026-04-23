#include "scene.hpp"
bool scene::Intersect(const ray &ray, float tMin, float tMax) const
{
    ShapeIntersection unused;
    return Intersect(ray, tMin, tMax, unused);
}

bool scene::Intersect(const ray &ray, float tMin, float tMax, ShapeIntersection &out_intersection) const {
    float min_time_of_intersection{tMax};
    std::size_t index_of_closest{my_shapes.size()};
    for (std::size_t i = 0; i < my_shapes.size(); ++i) {
        const auto &shape = my_shapes.at(i);
        ShapeIntersection intersection;
        if (shape->Intersect(ray, tMin, tMax, intersection)) {
            if (
                intersection.time_of_intersection >= tMin
                && intersection.time_of_intersection < tMax
                && intersection.time_of_intersection < min_time_of_intersection
            ) {
                min_time_of_intersection = intersection.time_of_intersection;
                index_of_closest = i;
                out_intersection = intersection;
            }
        }
    }
    return index_of_closest < my_shapes.size();
}
