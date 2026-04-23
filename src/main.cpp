#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include "Film.h"
#include "Color.h"
#include "camera.hpp"
#include "renderer.hpp"
#include "scene.hpp"
#include "shape/sphere.hpp"
#include "light.hpp"
#include "light/light_directional.hpp"

#include <fstream>

enum material_type : std::uint8_t {
    material_type_red = 0,
    material_type_yellow,
    material_type_blue,
    material_type_green,

    material_type_count,
};

int main(void) {
    std::ofstream out{"imagen.ppm"};
    // Film film{1920, 1080, out};
    Film film{800, 600, out};

    camera cam{
        {0.0, 0.0, 3.0},
        {0.0, 0.0, 0.0},
        {0.0, 1.0, 0.0},
        film,
        60.0
    };
    auto shapes = std::vector<std::unique_ptr<shape>>{};
    shapes.emplace_back(std::make_unique<sphere>(material_type_red, glm::vec3{-2.0, 0.0, -2.0}, 1.0f));
    shapes.emplace_back(std::make_unique<sphere>(material_type_yellow, glm::vec3{0.0, 0.0, -2.0}, 1.0f));
    shapes.emplace_back(std::make_unique<sphere>(material_type_blue, glm::vec3{2.0, 0.0, -2.0}, 1.0f));
    shapes.emplace_back(std::make_unique<sphere>(material_type_green, glm::vec3{0.0, -100.0, -2.0}, 99.0f));

    auto materials = std::vector<Material>{material_type_count};
    materials.at(material_type_red) = Material{{1.0, 0.0, 0.0}};
    materials.at(material_type_yellow) = Material{{1.0, 1.0, 0.0}};
    materials.at(material_type_blue) = Material{{0.0, 0.0, 1.0}};
    materials.at(material_type_green) = Material{{0.0, 1.0, 0.0}};
    
    auto lights = std::vector<std::unique_ptr<light>>{};
    lights.emplace_back(std::make_unique<light_directional>(glm::normalize(glm::vec3{-1.0, -1.0, -1.0}), Color{1.0, 1.0, 1.0}));
    world the_world{
        std::make_unique<scene>(std::move(shapes)),
        std::move(lights)
    };

    renderer render{
        std::move(film),
        std::move(cam),
        std::move(the_world),
        std::move(materials)
    };

    render.render();
    return 0;
}
