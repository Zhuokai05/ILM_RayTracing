#include "light_ambient.hpp"

Color light_ambient::shade(const ray &ray, const ShapeIntersection &hit, const Material &hit_material) const {
    (void)ray;
    (void)hit;
    (void)hit_material;
    return ambient;
}
