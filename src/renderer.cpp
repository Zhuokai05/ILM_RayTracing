#include "renderer.hpp"
#include "ray.hpp"
#include <glm/geometric.hpp>

void renderer::render() {
    const float sample_weight = 1.0f / (samples_per_pixel_x * samples_per_pixel_y); 
    for (std::size_t y = 0; y < film.GetTamY(); ++y) {
        for (std::size_t x = 0; x < film.GetTamX(); ++x) {
            const float x_center = static_cast<float>(x);
            const float y_center = static_cast<float>(y);
            // const ray ray_primary = cam.get_ray_unfocus(x_center, y_center, 1.0f);

            const float x_sampling_window = 1.0f / static_cast<float>(samples_per_pixel_x);
            const float y_sampling_window = 1.0f / static_cast<float>(samples_per_pixel_y);

            Color result{0.0, 0.0, 0.0};
            for (std::size_t sample_y = 0; sample_y < samples_per_pixel_y; ++sample_y) {
                for (std::size_t sample_x = 0; sample_x < samples_per_pixel_x; ++sample_x) {
                    const float x_sample = x_center + (static_cast<float>(sample_x) + 0.5f) * x_sampling_window - 0.5f;
                    const float y_sample = y_center + (static_cast<float>(sample_y) + 0.5f) * y_sampling_window - 0.5f;
                    const ray ray_sample = cam.get_ray_unfocus_jitter(x_sample, y_sample, 1.0f, {x_sampling_window, y_sampling_window}, 1.0f);
                    // TODO: pass time as parameter for scene
                    result += ray_color(ray_sample);
                }
            }
            film.AddPixel(result * sample_weight);
        }
    }
}

static constexpr float scene_limit_max = 10000.0;
static constexpr float scene_limit_min = 0.001;
static constexpr std::size_t reflection_level_max_default = 10ull;
Color renderer::ray_color(const ray &ray) const {
    return ray_color_leveled(ray, 0ull, reflection_level_max_default);
}

Color renderer::ray_color_leveled(const ray &ray, const std::size_t reflection_level, const std::size_t reflection_level_max) const {
    ShapeIntersection intersection;
    if (my_world.my_shape->Intersect(ray, scene_limit_min, scene_limit_max, intersection)) {
        const auto &material = materials.at(intersection.material_index);
        return shade_leveled(ray, intersection, material, reflection_level, reflection_level_max);
    } else {
        return background_color;
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
        if (shadow_ray.direction() == zero || !my_world.my_shape->Intersect(shadow_ray, scene_limit_min, scene_limit_max)) {
            result += light->shade(ray, hit, hit_material, hit_material.get_texture(textures));
        }
    }

    if (hit_material.reflection_factor > 0.0f && reflection_level < reflection_level_max) {
        const ::ray secondary = ::ray{surface, glm::reflect(ray.direction(), hit.normal)};
        result += hit_material.reflection_factor * ray_color_leveled(secondary, reflection_level + 1ull, reflection_level_max);
    }
    return result;
}
