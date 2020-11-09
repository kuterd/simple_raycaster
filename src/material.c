#include <assert.h>
#include "material.h"
#include "ray.h"
#include "scene.h"
#include "utils.h"

 struct Material constantColorMaterial_create(unsigned int color) {
     return (struct Material) {
        .type = CONSTANT_COLOR,
         .constant_color_data = (struct ConstantColorData) {
            .color = fvec3_colorToVec(color)
         }
     };
 }


struct Material checkerBoardMaterial_create(unsigned int material_a_id, unsigned int material_b_id) {
    return (struct Material) {
        .type = CHECKER_BOARD,
        .checker_board_data = (struct CheckerBoardData) {
            .material_a_id = material_a_id,
            .material_b_id = material_b_id
        }
    };
}

struct Material simpleLighting_create(unsigned int source_material_id) {
    return (struct Material) {
        .type = SIMPLE_LIGHTING,
        .simple_lighting_data = (struct SimpleLightingData) {
            .source_material_id = source_material_id
        }
    };
}


fvec3 checkerBoard_shade(struct Material material, struct Scene *scene,
     struct RaycastResult rResult, int rayC) {
    assert(material.type == CHECKER_BOARD);
    fvec3 rx = (fvec3) {rResult.normal.x, -rResult.normal.z, rResult.normal.y};
    fvec3 rz = (fvec3) {-rResult.normal.y, rResult.normal.x, rResult.normal.z};

    fvec3 rePos = fvec3_sub(rResult.position, rResult.object.position);

    float x = fvec3_dotProduct(rePos, rx);
    float y = fvec3_dotProduct(rePos, rz);

    struct Material tM = scene->materials[
        ((int)(x / 2.5) % 2 ^ (int)(y / 2.5)) % 2 ?
            material.checker_board_data.material_a_id :
            material.checker_board_data.material_b_id
    ];
    return material_shade(tM, scene, rResult, rayC);
}

fvec3 simpleLighting_shade(struct Material material, struct Scene *scene,
        struct RaycastResult rResult, int rayC) {
    float lighting = 0;
    for (int i = 0; i < scene->light_count; i++) {
        struct Light light = scene->lights[i];
        fvec3 lightToP = fvec3_normalize(fvec3_sub(light.position, rResult.position));
        //fvec3 rayPos = fvec3_add(rResult.position, fvec3_mulc(lightToP, 0.1));
        struct RaycastResult vrResult = scene_raycast(
            scene,
            (struct Ray) { rResult.position, lightToP }
        );

        if (!vrResult.succsess) {
            float dotProd = fvec3_dotProduct(rResult.normal, lightToP);
            lighting += dotProd < 0 ? 0: dotProd;
        }
    }

    fvec3 color = material_shade(
        scene->materials[material.simple_lighting_data.source_material_id],
        scene,
        rResult,
        rayC
    );

    return fvec3_mulc(color, min(lighting, 1));
}


fvec3 material_shade(struct Material material, struct Scene *scene,
                     struct RaycastResult rResult, int rayC) {
    switch (material.type) {
        case CONSTANT_COLOR:
            return material.constant_color_data.color;
        case CHECKER_BOARD:
            return checkerBoard_shade(material, scene, rResult, rayC);
        case REFLECTIVE: {
            fvec3 refDir = fvec3_sub(
                rResult.normal,
                fvec3_mulc(rResult.ray.direction, 2)
            );

            return scene_renderRay_(
                scene,
                (struct Ray) { rResult.position, refDir },
                rayC
            );
        }
        case SIMPLE_LIGHTING:
            return simpleLighting_shade(material, scene, rResult, rayC);
        default:
            assert(0);
    }
}
