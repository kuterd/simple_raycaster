#ifndef MATERIAL_H
#define MATERIAL_H

#include "vec.h"
#include "ray.h"

enum MaterialType {
    CHECKER_BOARD = 0,
    CONSTANT_COLOR,
    SIMPLE_LIGHTING,
    REFLECTIVE
};

struct CheckerBoardData {
    unsigned int material_a_id, material_b_id;
};

struct ConstantColorData {
    fvec3 color;
};

struct SimpleLightingData {
    unsigned int source_material_id;
};

struct Material {
    enum MaterialType type;
    union {
        struct CheckerBoardData checker_board_data;
        struct ConstantColorData constant_color_data;
        struct SimpleLightingData simple_lighting_data;
    };
};

struct Material constantColorMaterial_create(unsigned int color);
struct Material checkerBoardMaterial_create(unsigned int material_a_id, unsigned int material_b_id);
struct Material simpleLighting_create(unsigned int source_material_id);

struct Scene;

fvec3 material_shade(struct Material material, struct Scene *scene,
                     struct RaycastResult rResult, int rayC);

#endif
