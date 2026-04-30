#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <memory>
#include <vector>
#include "Film.h"
#include "camera.hpp"
#include "shape.hpp"
#include "material.hpp"
#include "texture.hpp"
#include "world.hpp"

struct renderer {
    Film film;
    camera cam;
    //std::unique_ptr<shape> my_shape{};
    world my_world;
    std::vector<Material> materials{};
    std::vector<std::unique_ptr<texture>> textures{};
    std::size_t samples_per_pixel_x;
    std::size_t samples_per_pixel_y;

    void render();
    Color ray_color(const ray &ray) const;
    Color ray_color_leveled(const ray &ray, const std::size_t reflection_level, const std::size_t reflection_level_max) const;
    Color shade(const ray &ray, const ShapeIntersection &hit, const Material &hit_material) const;
    Color shade_leveled(const ray &ray, const ShapeIntersection &hit, const Material &hit_material, const std::size_t reflection_level, const std::size_t reflection_level_max) const;
};

#endif
