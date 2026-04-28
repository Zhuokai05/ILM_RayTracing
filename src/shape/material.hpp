#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "../Color.h"

struct Material {
    Color color;
    float reflection_factor;
};

#endif