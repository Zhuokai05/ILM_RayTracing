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

#include <algorithm>
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <limits>
#include <memory>
#include <random>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace {

constexpr std::size_t texture_type_constant = 0;
constexpr std::size_t texture_type_checker = 1;
constexpr std::size_t texture_type_uv = 2;

enum material_type : std::size_t {
    material_type_floor_checker = 0,
    material_type_count,
};

constexpr float floor_y = -1.0f;
constexpr std::size_t minimum_random_sphere_count = 15;
constexpr std::size_t default_random_sphere_count = 18;
constexpr std::size_t default_frame_count = 24;
constexpr std::size_t samples_per_axis_x = 4;
constexpr std::size_t samples_per_axis_y = 4;

struct sphere_spec {
    std::size_t material_index;
    glm::vec3 center;
    float radius;
};

struct scene_definition {
    std::vector<sphere_spec> spheres;
    std::vector<Material> materials;
    float focus_front_z;
    float focus_back_z;
};

float random_float(std::mt19937 &rng, const float min_value, const float max_value) {
    std::uniform_real_distribution<float> distribution{min_value, max_value};
    return distribution(rng);
}

Color random_color(std::mt19937 &rng) {
    return Color{
        random_float(rng, 0.15f, 1.0f),
        random_float(rng, 0.15f, 1.0f),
        random_float(rng, 0.15f, 1.0f),
    };
}

std::size_t random_texture_index(std::mt19937 &rng) {
    std::uniform_int_distribution<std::size_t> distribution{0, texture_type_uv};
    return distribution(rng);
}

std::vector<std::unique_ptr<texture>> build_textures() {
    auto textures = std::vector<std::unique_ptr<texture>>{3};
    textures.at(texture_type_constant) = std::make_unique<texture_constant>(Color{1.0, 1.0, 1.0});
    textures.at(texture_type_checker) = std::make_unique<texture_checker>(Color{1.0, 1.0, 1.0}, Color{0.0, 0.0, 0.0}, glm::vec2{200.0, 200.0}, glm::vec2{0.0, 0.0});
    textures.at(texture_type_uv) = std::make_unique<texture_uv>(Color{1.0, 0.0, 0.0}, Color{0.0, 1.0, 0.0});
    return textures;
}

std::vector<std::unique_ptr<light>> build_lights() {
    auto lights = std::vector<std::unique_ptr<light>>{};
    lights.emplace_back(std::make_unique<light_point>(glm::vec3{2.0, 2.0, 0.0}, Color{0.4, 1.0, 0.8}, Color{1.0, 1.0, 1.0}, 64.0));
    lights.emplace_back(std::make_unique<light_ambient>(Color{0.1, 0.2, 0.1}));
    return lights;
}

scene_definition build_scene_definition(const std::size_t requested_sphere_count, std::mt19937 &rng) {
    const std::size_t sphere_count = std::max(requested_sphere_count, minimum_random_sphere_count);

    scene_definition definition{};
    definition.spheres.reserve(sphere_count);
    definition.materials.reserve(material_type_count + sphere_count);
    definition.materials.resize(material_type_count);

    definition.materials.at(material_type_floor_checker) = Material{Color{0.72, 0.72, 0.72}, texture_type_checker, 0.5f};

    definition.focus_front_z = std::numeric_limits<float>::lowest();
    definition.focus_back_z = std::numeric_limits<float>::max();

    for (std::size_t index = 0; index < sphere_count; ++index) {
        const float radius = random_float(rng, 0.25f, 1.10f);
        const float center_x = random_float(rng, -6.5f, 6.5f);
        const float center_z = random_float(rng, -11.5f, 2.0f);

        definition.spheres.push_back(sphere_spec{
            material_type_count + index,
            glm::vec3{center_x, floor_y + radius, center_z},
            radius,
        });

        definition.materials.push_back(Material{
            random_color(rng),
            random_texture_index(rng),
            random_float(rng, 0.0f, 0.85f)
        });

        definition.focus_front_z = std::max(definition.focus_front_z, center_z + radius);
        definition.focus_back_z = std::min(definition.focus_back_z, center_z - radius);
    }

    return definition;
}

std::vector<std::unique_ptr<shape>> build_shapes(const scene_definition &definition) {
    auto shapes = std::vector<std::unique_ptr<shape>>{};
    shapes.reserve(definition.spheres.size() + 1);

    shapes.emplace_back(std::make_unique<quad>(
        material_type_floor_checker,
        glm::vec3{10.0f, floor_y, -12.0f},
        glm::vec3{-20.0f, 0.0f, 0.0f},
        glm::vec3{0.0f, 0.0f, 16.0f}
    ));

    for (const auto &sphere_data : definition.spheres) {
        shapes.emplace_back(std::make_unique<sphere>(sphere_data.material_index, sphere_data.center, sphere_data.radius));
    }

    return shapes;
}

world build_world(const scene_definition &definition) {
    return world{
        std::make_unique<scene>(build_shapes(definition)),
        build_lights()
    };
}

glm::vec3 focus_point_for_frame(const scene_definition &definition, const std::size_t frame_index, const std::size_t frame_count) {
    const float frame_progress = frame_count <= 1
        ? 0.0f
        : static_cast<float>(frame_index) / static_cast<float>(frame_count - 1);

    const float focus_z = definition.focus_front_z
        + (definition.focus_back_z - definition.focus_front_z) * frame_progress;

    return glm::vec3{0.0f, 0.0f, focus_z};
}

std::filesystem::path frame_path_for_index(const std::filesystem::path &directory, const std::size_t frame_index, const std::size_t frame_count) {
    const std::size_t width = std::max<std::size_t>(3, std::to_string(frame_count - 1).size());
    std::ostringstream file_name;
    file_name << "frame_" << std::setw(static_cast<int>(width)) << std::setfill('0') << frame_index << ".ppm";
    return directory / file_name.str();
}

void render_sequence(const scene_definition &definition, const std::size_t frame_count) {
    const std::size_t safe_frame_count = std::max<std::size_t>(1, frame_count);
    const std::filesystem::path output_directory{"media/sequence"};
    std::filesystem::create_directories(output_directory);

    for (std::size_t frame_index = 0; frame_index < safe_frame_count; ++frame_index) {
        const auto frame_path = frame_path_for_index(output_directory, frame_index, safe_frame_count);
        std::ofstream out{frame_path};

        Film film{800, 600, std::move(out)};
        camera cam{
            {0.0, 0.0, 3.0},
            focus_point_for_frame(definition, frame_index, safe_frame_count),
            {0.0, 1.0, 0.0},
            film,
            60.0,
            0.6
        };

        renderer render{
            std::move(film),
            Color{0.86f, 0.93f, 1.0f},
            std::move(cam),
            build_world(definition),
            definition.materials,
            build_textures(),
            samples_per_axis_x,
            samples_per_axis_y
        };

        render.render();
    }
}

} // namespace

int main(int argc, char **argv) {
    const std::size_t requested_sphere_count = argc > 1 ? static_cast<std::size_t>(std::stoul(argv[1])) : default_random_sphere_count;
    const std::size_t frame_count = argc > 2 ? static_cast<std::size_t>(std::stoul(argv[2])) : default_frame_count;

    std::mt19937 rng{0xC0FFEEu};
    const auto definition = build_scene_definition(requested_sphere_count, rng);

    render_sequence(definition, frame_count);
    return 0;
}
