#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

#include "Film.h"
#include "Color.h"
#include "camera.hpp"
#include "renderer.hpp"
#include "scene.hpp"

#include "shape.hpp"
#include "shape/sphere.hpp"
#include "shape/quad.hpp"

#include "light.hpp"
#include "light/light_directional.hpp"
#include "light/light_ambient.hpp"
#include "light/light_point.hpp"

#include "texture.hpp"
#include "texture/texture_constant.hpp"
#include "texture/texture_checker.hpp"
#include "texture/texture_uv.hpp"

#include <fstream>

enum material_type : std::uint8_t {
    material_type_red = 0,
    material_type_yellow,
    material_type_yellow_checker,
    material_type_blue,
    material_type_green,
    material_type_green_checker,
    material_type_uv,

    material_type_count,
};

enum texture_type : std::uint8_t {
    texture_type_constant = 0,
    texture_type_checker,
    texture_type_uv,

    texture_type_count,
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
    shapes.emplace_back(std::make_unique<sphere>(material_type_red,         glm::vec3{-2.0, 0.0, -2.0},     1.0f));
    shapes.emplace_back(std::make_unique<sphere>(material_type_yellow_checker,      glm::vec3{0.0, 0.0, -2.0},      1.0f));
    shapes.emplace_back(std::make_unique<sphere>(material_type_blue,        glm::vec3{2.0, 0.0, -2.0},      1.0f));
    // shapes.emplace_back(std::make_unique<sphere>(material_type_green,   glm::vec3{0.0, -100.0, -2.0},   99.0f));
    shapes.emplace_back(std::make_unique<quad>(material_type_green_checker, glm::vec3{1.5, -1.0, -3.5}, glm::vec3{-3.0, 0.0, 0.0}, glm::vec3{0.0, 0.0, 3.0}));

    // TODO: move creation to functions
    auto textures = std::vector<std::unique_ptr<texture>>{texture_type_count};
    textures.at(texture_type_constant) =    std::make_unique<texture_constant>  (Color{1.0, 1.0, 1.0});
    textures.at(texture_type_checker) =     std::make_unique<texture_checker>   (Color{1.0, 1.0, 1.0}, Color{0.0, 0.0, 0.0}, glm::vec2{10.0, 10.0}, glm::vec2{0.0, 0.0});
    textures.at(texture_type_uv) =          std::make_unique<texture_uv>        (Color{1.0, 0.0, 0.0}, Color{0.0, 1.0, 0.0});

    auto materials = std::vector<Material>{material_type_count};
    materials.at(material_type_red) =               Material{{1.0, 0.0, 0.0}, texture_type_constant, 0.5};
    materials.at(material_type_yellow) =            Material{{1.0, 1.0, 0.0}, texture_type_constant, 0.5};
    materials.at(material_type_yellow_checker) =    Material{{1.0, 1.0, 0.0}, texture_type_checker,  0.5};
    materials.at(material_type_blue) =              Material{{0.0, 0.0, 1.0}, texture_type_constant, 0.5};
    materials.at(material_type_green) =             Material{{0.0, 1.0, 0.0}, texture_type_constant, 0.5};
    materials.at(material_type_green_checker) =     Material{{0.0, 1.0, 0.0}, texture_type_checker,  0.5};
    materials.at(material_type_uv) =                Material{{1.0, 1.0, 1.0}, texture_type_uv,       0.5};

    auto lights = std::vector<std::unique_ptr<light>>{};
    // lights.emplace_back(std::make_unique<light_directional>(glm::normalize(glm::vec3{-1.0, -1.0, -1.0}), Color{0.4, 1.0, 0.8}, Color{1.0, 1.0, 1.0}, 64.0));
    lights.emplace_back(std::make_unique<light_point>(glm::vec3{2.0, 2.0, 0.0}, Color{0.4, 1.0, 0.8}, Color{1.0, 1.0, 1.0}, 64.0));
    // lights.emplace_back(std::make_unique<light_point>(glm::vec3{-2.0, 2.0, -3.0}, Color{0.4, 1.0, 0.8}, Color{1.0, 1.0, 1.0}, 64.0));
    lights.emplace_back(std::make_unique<light_ambient>(Color{0.1, 0.2, 0.1}));
    world the_world{
        std::make_unique<scene>(std::move(shapes)),
        std::move(lights)
    };

    renderer render{
        std::move(film),
        std::move(cam),
        std::move(the_world),
        std::move(materials),
        std::move(textures)
    };

    render.render();
    return 0;
}
