#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <assert.h>
#include <math.h>

#include "vec.h"
#include "utils.h"
#include "bitmap.h"
#include "object.h"
#include "scene.h"

/*
void draw_line(struct Bitmap bmap, ivec2 start, ivec2 end, unsigned int color) {
    int isSteep = abs(start.y - end.y) > abs(start.x - end.x);

    if (isSteep) {,
        swap(start.x, start.y);
        swap(end.x, end.y);
    }

    if(start.x > end.x)
        swap(start, end);

    printf("Start x:%d, y:%d\n", start.x, start.y);
    printf("End x:%d, y:%d\n", end.x, end.y);
    printf("isSteep %d\n", isSteep);
    float slope = (float)(end.y - start.y) / (end.x - start.x);

    printf("Slope %f\n", slope);
    for (int x = start.x; x < end.x && x < bmap.width; x++) {
        int y = fabs(slope * (x - start.x) + start.y); //    F
        printf("X: %d Y: %d", x, y);

        bmap.pixels[isSteep ? (x * bmap.width + y) : (y * bmap.width + x)] = color;
    }
}
*/
//TODO: Bu sistemi daha düzgün bir sistemle değiştir.
void construct_scene(struct Scene *scene) {
    // --- Materials ---
    unsigned int reflective = scene_push_material(
        scene, (struct Material) {.type = REFLECTIVE}
    );
    unsigned int reflectiveLighted = scene_push_material(
        scene, simpleLighting_create(reflective));

    unsigned int matRed = scene_push_material(
        scene, constantColorMaterial_create(0xFFFF0000));

    unsigned int matGreen = scene_push_material(
        scene, constantColorMaterial_create(0xFF00FF00));

    unsigned int matYellow = scene_push_material(
        scene, constantColorMaterial_create(0xFFFFFF00));

    unsigned int matBlue = scene_push_material(
        scene, constantColorMaterial_create(0xFF0000FF));

    unsigned int matBlueLighted = scene_push_material(
        scene, simpleLighting_create(matBlue));

    unsigned int matGreenLighted = scene_push_material(
        scene, simpleLighting_create(matGreen)
    );

    unsigned int matCheckerBoard1 = scene_push_material(
        scene, checkerBoardMaterial_create(matYellow, matRed)
    );

    unsigned int matCheckerBoard1Lighted = scene_push_material(
        scene, simpleLighting_create(matCheckerBoard1)
    );

    unsigned int matCheckerBoard2 = scene_push_material(
        scene, checkerBoardMaterial_create(matGreen, matBlue)
    );

    unsigned int matCheckerBoard2Lighted = scene_push_material(
        scene, simpleLighting_create(matCheckerBoard2)
    );

    // --- Lights ---

    scene_push_light(
        scene, (struct Light) {(fvec3) {0,  -20, -5}}
    );

    // scene_push_light(
    //   scene, (struct Light) {(fvec3) {10,    -10, -5}}
    // );

    // --- Objects ---
    // scene_push_object(
    //   scene, sphere_create((fvec3) {-5,  1, -15}, 1.5, reflectiveLighted));
    //
    // scene_push_object(
    //   scene, sphere_create((fvec3) {-5.3,    1, -5}, 1, matBlueLighted));
    //
    scene_push_object(scene,
                      disk_create(
                          (fvec3) {0, 10, -50},
                          fvec3_normalize((fvec3) {0, -1, 0}),
                          20,
                          matCheckerBoard1Lighted
                      )
    );

    scene_push_object(scene,
                      disk_create(
                          (fvec3) {0, 16, -50},
                          fvec3_normalize((fvec3) {0, -1, 0}),
                          30,
                          matCheckerBoard2Lighted
                      )
    );

    for (int i = 0; i < 10; i++) {
        fvec3 random = (fvec3) {
            random_float(-10, 10),
            random_float(-5, 5),
            random_float(-30, -20)
        };
        
        struct Object object = sphere_create(
            random,
            1,
            matBlueLighted
        );
        
        scene_push_object(scene, object);
    }

    for (int i = 0; i < 10; i++) {
        struct Object object = sphere_create(
            (fvec3) {
                random_float(-10, 10),
                random_float(-5, 5),
                random_float(-50, -30),
            },
            2,
            reflectiveLighted
        );
        scene_push_object(scene, object);
    }
}

#define IMAGE_WIDTH 1500
#define IMAGE_HEIGHT 1000
int main(int argc, char *args) {
    struct Bitmap bitmap = bitmap_alloc(IMAGE_WIDTH, IMAGE_HEIGHT);
    struct Scene scene = {};
    construct_scene(&scene);
    scene_render(&scene, bitmap);
    bitmap_write(bitmap, "render.bmp");

    return 0;
}

