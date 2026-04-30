#include "renderer.hpp"
#include "ray.hpp"
#include <glm/geometric.hpp>

void renderer::render() {
    for (std::size_t y = 0; y < film.GetTamY(); ++y) {
        for (std::size_t x = 0; x < film.GetTamX(); ++x) {
            const ray ray_primary = cam.get_ray(x, y);
            const Color c = ray_color(ray_primary);
            film.AddPixel(c);
        }
    }
}

static constexpr float scene_limit = 10000.0;
static constexpr std::size_t reflection_level_max_default = 10ull;
Color renderer::ray_color(const ray &ray) const {
    return ray_color_leveled(ray, 0ull, reflection_level_max_default);
}

Color renderer::ray_color_leveled(const ray &ray, const std::size_t reflection_level, const std::size_t reflection_level_max) const {
    ShapeIntersection intersection;
    if (my_world.my_shape->Intersect(ray, 0.0f, scene_limit, intersection)) {
        const auto &material = materials.at(intersection.material_index);
        return shade_leveled(ray, intersection, material, reflection_level, reflection_level_max);
    } else {
        return Color{0.0, 0.0, 0.0};
        // glm::vec3 unit_direction = glm::normalize(ray.direction());
        // float a = 0.5*(unit_direction.y + 1.0);
        // return (1.0f-a)*Color(1.0, 1.0, 1.0) + a*Color(0.5, 0.7, 1.0);
    }
}

Color renderer::shade(const ray &ray, const ShapeIntersection &hit, const Material &hit_material) const {
    return shade_leveled(ray, hit, hit_material, 0ull, reflection_level_max_default);
}

Color renderer::shade_leveled(const ray &ray, const ShapeIntersection &hit, const Material &hit_material, const std::size_t reflection_level, const std::size_t reflection_level_max) const {
    Color result{0.0, 0.0, 0.0};
    const glm::vec3 surface = ray.at(hit.time_of_intersection);
    for (const auto &light : my_world.my_lights) {
        const ::ray shadow_ray = ::ray{surface, light->shadow_direction(surface)};
        static constexpr glm::vec3 zero{0.0, 0.0, 0.0};
        if (shadow_ray.direction() == zero || !my_world.my_shape->Intersect(shadow_ray, 0.0, scene_limit)) {
            result += light->shade(ray, hit, hit_material, hit_material.get_texture(textures));
        }
    }

    if (hit_material.reflection_factor > 0.0f && reflection_level < reflection_level_max) {
        const ::ray secondary = ::ray{surface, glm::reflect(ray.direction(), hit.normal)};
        result += hit_material.reflection_factor * ray_color_leveled(secondary, reflection_level + 1ull, reflection_level_max);
    }
    return result;
}
