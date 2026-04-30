#include "camera.hpp"
#include <glm/geometric.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtc/random.hpp>
#include <glm/vec2.hpp>

camera::camera(
    glm::vec3 position,
    glm::vec3 look_focus,
    glm::vec3 up,
    const Film &film,
    const float fov_degrees_vertical,
    const float unfocus_degrees
) : position{position}, up{up} {
    const float fov_radians_vertical = glm::radians(fov_degrees_vertical * 0.5);
    const float half_height_normalized = std::tan(fov_radians_vertical);

    const glm::vec3 forward_displacement = position - look_focus;
    const float focal_length = glm::length(forward_displacement);
    const glm::vec3 forward = forward_displacement / focal_length;
    right = glm::cross(up, forward);    
    const glm::vec3 v = glm::cross(forward, right);

    const float half_height_viewport = focal_length * half_height_normalized;
    const float half_width_viewport = half_height_viewport * film.GetAspectRatio();

    const float height_viewport = half_height_viewport * 2.0;
    const float width_viewport = half_width_viewport * 2.0;

    const float pixel_height = height_viewport / float(film.GetTamY());
    const float pixel_width = width_viewport / float(film.GetTamX());

    delta_x = right * pixel_width;
    delta_y = -v * pixel_height;
    position_top_left =
        position - focal_length * forward
        + v * half_height_viewport + delta_x * 0.5f
        - right * half_width_viewport + delta_y * 0.5f;
    position_unfocus_radius = std::tan(glm::radians(unfocus_degrees * 0.5)) * focal_length;
}

ray camera::get_ray(const float x, const float y) const {
    const glm::vec3 sample =
        position_top_left + delta_x * x + delta_y * y;
    const glm::vec3 displacement = (sample - position);

    return ray{position, glm::normalize(displacement)};
}

ray camera::get_ray_unfocus(const float x, const float y, const float factor) const {
    const glm::vec2 offset = glm::diskRand(position_unfocus_radius) * factor;
    const glm::vec3 origin = position + right * offset.x + up * offset.y;

    const glm::vec3 sample =
        position_top_left + delta_x * x + delta_y * y;
    const glm::vec3 displacement = (sample - origin);

    return ray{origin, glm::normalize(displacement)};
}
