#include "quad.hpp"
#include <glm/geometric.hpp>
#include <iostream>

bool quad::Intersect(const ray &ray, float tMin, float tMax) const {
    ShapeIntersection hit;
    return Intersect(ray, tMin, tMax, hit);
}


// source: https://raytracing.github.io/books/RayTracingTheNextWeek.html#quadrilaterals
bool quad::Intersect(const ray &ray, float tMin, float tMax, ShapeIntersection &out_intersection) const {
    const glm::vec3 n = glm::cross(u, v);
    const glm::vec3 normal = glm::normalize(n);
    const auto denom = glm::dot(normal, ray.direction());

    // No hit if the ray is parallel to the plane.
    if (std::fabs(denom) < 1e-8) {
        // std::cout << "FAIL: parallel\n";
        return false;
    }

    const auto D = glm::dot(normal, point);
    // Return false if the hit point parameter t is outside the ray interval.
    const auto t = (D - glm::dot(normal, ray.origin())) / denom;
    if (tMin <= t && t < tMax) {        
        // Determine if the hit point lies within the planar shape using its plane coordinates.
        const auto intersection = ray.at(t);
        const glm::vec3 planar_hitpt_vector = intersection - point;

        const auto w = n / glm::dot(n, n);
        const auto alpha = glm::dot(w, glm::cross(planar_hitpt_vector, glm::normalize(v)));
        const auto beta = glm::dot(w, glm::cross(glm::normalize(u), planar_hitpt_vector));
        if (
            0.0 <= alpha && alpha < 1.0
            && 0.0 <= beta && beta < 1.0
        ) {
            out_intersection = ShapeIntersection{
                material_index,
                t,
                normal,
                glm::vec2{alpha, beta}
            };
            // FIXME: wrong
            // std::cout << "SUCC: yes-inside\n" << "\talpha: " << alpha << " beta: " << beta << '\n';
            return true;
        } else {
            // std::cout << "FAIL: not-inside\n" << "\talpha: " << alpha << " beta: " << beta << '\n';
            return false;
        }
    } else {
        // std::cout << "FAIL: out-of-range\n" << "\tmin: " << tMin << " max: " << tMax << " t: " << t << '\n';
        return false;
    }
}
