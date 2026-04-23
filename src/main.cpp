#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include "Film.h"
#include "Color.h"
#include "camera.hpp"
#include "renderer.hpp"
#include "scene.hpp"
#include "shape/sphere.hpp"

#include <fstream>

int main(void) {
    std::ofstream out{"imagen.ppm"};
    Film film{1920, 1080, out};

    camera cam{
        {0.0, 0.0, 0.0},
        {0.0, 0.0, -1.0},
        {0.0, 1.0, 0.0},
        film,
        90.0
    };
    auto shapes = std::vector<std::unique_ptr<shape>>{};
    shapes.emplace_back(std::make_unique<sphere>(0ull, glm::vec3{1.0, 0.0, -1.0}, 0.5f));
    shapes.emplace_back(std::make_unique<sphere>(1ull, glm::vec3{0.0, 0.0, -2.0}, 1.0f));
    shapes.emplace_back(std::make_unique<sphere>(2ull, glm::vec3{-1.0, 0.0, -1.0}, 0.5f));

    renderer render{
        std::move(film),
        std::move(cam),
        std::make_unique<scene>(std::move(shapes)),
        std::vector{
            Material{{1.0, 0.0, 0.0}},
            Material{{1.0, 1.0, 0.0}},
            Material{{0.0, 0.0, 1.0}}
        }
    };

    render.render();
    return 0;
}
