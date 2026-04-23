#ifndef LIGHTING_HPP
#define LIGHTING_HPP

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
// #include <glm/common.hpp>
#include <cmath>
#include <algorithm>
#include <numeric>

inline float lighting_diffuse_ws(const glm::vec3 light_direction_ws, const glm::vec3 normal_ws) {
    return std::max(0.0f, glm::dot(light_direction_ws, normal_ws));
}
inline float lighting_specular_blinn_ws(const glm::vec3 light_direction_ws, const glm::vec3 normal_ws, const glm::vec3 view_direction_ws, const float specular_power) {
    const glm::vec3 half_view_light_direction_ws = glm::normalize(view_direction_ws + light_direction_ws);
    return std::pow(std::max(0.0f, glm::dot(half_view_light_direction_ws, normal_ws)), specular_power);
}
inline float lighting_specular_phong_ws(const glm::vec3 light_direction_ws, const glm::vec3 normal_ws, const glm::vec3 view_direction_ws, const float specular_power) {
    const glm::vec3 light_direction_reflected_ws = glm::reflect(-light_direction_ws, normal_ws);
    return std::pow(std::max(0.0f, glm::dot(light_direction_reflected_ws, view_direction_ws)), specular_power);
}
inline float lighting_fresnel_ws(const glm::vec3 normal_ws, const glm::vec3 view_direction_ws, const float fresnel_power) {
    return std::pow(1.0f - std::clamp(glm::dot(normal_ws, view_direction_ws), 0.0f, 1.0f), fresnel_power);
}

#endif
