#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <memory>
#include <vector>
#include "Film.h"
#include "camera.hpp"
#include "shape.hpp"
#include "shape/material.hpp"
#include "world.hpp"

struct renderer {
    Film film;
    camera cam;
    //std::unique_ptr<shape> my_shape{};
    world my_world;
    std::vector<Material> materials{};

    void render();
    Color ray_color(const ray &ray) const;
};

#endif
