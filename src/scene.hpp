#ifndef SCENE_HPP
#define SCENE_HPP


#include <vector>
#include <memory>
#include "camera.hpp"
#include "shape.hpp"

struct scene : public shape {
    std::vector<std::unique_ptr<shape>> my_shapes{};

    inline ~scene() override = default;
    scene(std::vector<std::unique_ptr<shape>> shapes) : my_shapes(std::move(shapes)) { }
    bool Intersect(const ray &ray, float tMin, float tMax) const override;
    bool Intersect(const ray &ray, float tMin, float tMax, ShapeIntersection &out_intersection) const override;
};

#endif
