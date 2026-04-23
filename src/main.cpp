#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include "Film.h"
#include "Color.h"
#include "camera.hpp"
#include "renderer.hpp"
#include "scene.hpp"
#include "shape/sphere.hpp"

#include <fstream>

enum material_type : std::uint8_t {
    material_type_red = 0,
    material_type_yellow,
    material_type_blue,
    material_type_count,
};

int main(void) {
    std::ofstream out{"imagen.ppm"};
    Film film{1920, 1080, out};

    camera cam{
        {0.0, 0.0, 3.0},
        {0.0, 0.0, 0.0},
        {0.0, 1.0, 0.0},
        film,
        60.0
    };
    auto shapes = std::vector<std::unique_ptr<shape>>{material_type_count};
    shapes.at(material_type_red) = std::make_unique<sphere>(material_type_red, glm::vec3{-2.0, 0.0, -2.0}, 1.0f);
    shapes.at(material_type_yellow) = std::make_unique<sphere>(material_type_yellow, glm::vec3{0.0, 0.0, -2.0}, 1.0f);
    shapes.at(material_type_blue) = std::make_unique<sphere>(material_type_blue, glm::vec3{2.0, 0.0, -2.0}, 1.0f);

    auto materials = std::vector<Material>{material_type_count};
    materials.at(material_type_red) = Material{{1.0, 0.0, 0.0}};
    materials.at(material_type_yellow) = Material{{1.0, 1.0, 0.0}};
    materials.at(material_type_blue) = Material{{0.0, 0.0, 1.0}};
    
    renderer render{
        std::move(film),
        std::move(cam),
        std::make_unique<scene>(std::move(shapes)),
        std::move(materials)
    };

    render.render();
    return 0;
}
