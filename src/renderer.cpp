#include "renderer.hpp"
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

Color renderer::ray_color(const ray &ray) const {
    static constexpr float scene_limit = 10000.0;
    ShapeIntersection intersection;
    if (my_shape->Intersect(ray, 0.0f, scene_limit, intersection)) {
        return materials.at(intersection.material_index).color;
    }

    glm::vec3 unit_direction = glm::normalize(ray.direction());
    float a = 0.5*(unit_direction.y + 1.0);
    return (1.0f-a)*Color(1.0, 1.0, 1.0) + a*Color(0.5, 0.7, 1.0);
}
