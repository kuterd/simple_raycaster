#ifndef SCENE_H
#define SCENE_H

#include "ray.h"
#include "bitmap.h"
#include "vec.h"
#include "material.h"
#include "object.h"


#define MAX_OBJECTS 100
#define MAX_MATERIALS 50
#define MAX_LIGHTS 30

struct Light {
    fvec3 position;
};


struct Object;
struct Material;

struct Scene {
    unsigned int object_count;
    struct Object objects[MAX_OBJECTS];

    unsigned int material_count;
    struct Material materials[MAX_MATERIALS];

    unsigned int light_count;
    struct Light lights[MAX_LIGHTS];
};

void scene_push_object(struct Scene *scene, struct Object object);
int scene_push_material(struct Scene *scene, struct Material material);
void scene_push_light(struct Scene *scene, struct Light light);
struct RaycastResult scene_raycast(struct Scene *scene, struct Ray ray);

fvec3 scene_renderRay_(struct Scene *scene, struct Ray ray, int rayC);
fvec3 scene_renderRay(struct Scene *scene, struct Ray ray);

void scene_render(struct Scene *scene, struct Bitmap bitmap);

#endif
