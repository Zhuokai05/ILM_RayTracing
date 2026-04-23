#ifndef WORLD_HPP
#define WORLD_HPP

#include "shape.hpp"
#include "light.hpp"
#include <memory>
#include <vector>

struct world {
    std::unique_ptr<shape> my_shape;
    std::vector<std::unique_ptr<light>> my_lights;
};

#endif