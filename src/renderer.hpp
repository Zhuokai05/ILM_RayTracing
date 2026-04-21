#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <memory>
#include "Film.h"
#include "camera.hpp"
#include "shape.hpp"
#include "shape/material.hpp"

struct renderer {
    Film film;
    camera cam;
    std::unique_ptr<shape> my_shape{};
    std::vector<Material> materials{};

    void render();
    Color ray_color(const ray &ray) const;
};

#endif
