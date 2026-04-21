#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "ray.hpp"
#include "shapeIntersection.hpp"

struct shape {
    virtual ~shape() = default;
    virtual bool Intersect(const ray &ray, float tMin, float tMax) const = 0;
    virtual bool Intersect(const ray &ray, float tMin, float tMax, ShapeIntersection& out_intersection) const = 0;
};

#endif
