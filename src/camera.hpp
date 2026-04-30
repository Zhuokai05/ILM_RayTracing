#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/vec3.hpp>
#include "Film.h"
#include "ray.hpp"

struct camera {

    camera(
        glm::vec3 position,
        glm::vec3 look_focus,
        glm::vec3 up,
        const Film &film,
        const float fov_degrees_vertical,
        const float unfocus_degrees
    );

    ray get_ray(const float x, const float y) const;
    ray get_ray_unfocus(const float x, const float y, const float factor) const;
private:
    glm::vec3 position;
    glm::vec3 delta_x;
    glm::vec3 delta_y;
    glm::vec3 position_top_left;

    glm::vec3 right;
    glm::vec3 up;
    float position_unfocus_radius;
};

#endif
