#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "Color.h"
#include "shapeIntersection.hpp"
#include "shape/material.hpp"
#include "ray.hpp"

struct light {
    virtual Color shade(const ray &ray, const ShapeIntersection &hit, const Material &hit_material) const = 0;
};

#endif
