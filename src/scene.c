#include <assert.h>
#include "scene.h"


struct RaycastResult scene_raycast(struct Scene *scene, struct Ray ray) {
	struct RaycastResult bestResult = {.succsess = 0, .time = 1000000000};
	for (int i = 0; i < scene->object_count; i++) {
		struct Object object = scene->objects[i];
		struct RaycastResult result;
		result = object_raycast(object, ray);
		if (result.succsess & bestResult.time > result.time)
			bestResult = result;
	}
	return bestResult;
}

void scene_push_light(struct Scene *scene, struct Light light) {
	assert(scene->light_count < MAX_LIGHTS);
	scene->lights[scene->light_count++] = light;
}

int scene_push_material(struct Scene *scene, struct Material material) {
	assert(scene->material_count < MAX_MATERIALS);
	scene->materials[scene->material_count] = material;
	return scene->material_count++;
}

void scene_push_object(struct Scene *scene, struct Object object) {
	assert(scene->object_count < MAX_OBJECTS);
	scene->objects[scene->object_count++] = object;
}

fvec3 scene_renderRay_(struct Scene *scene, struct Ray ray, int rayC) {
	if (rayC++ == 10) return (fvec3) {0, 0, 0};
	struct RaycastResult rResult = scene_raycast(scene, ray);
	if (rResult.succsess) {
		return material_shade(scene->materials[rResult.object.material_id], scene, rResult, rayC);
	}
	return fvec3_colorToVec(0xFFFFFFFF);
}

fvec3 scene_renderRay(struct Scene *scene, struct Ray ray) {
	return scene_renderRay_(scene, ray, 0);
}

void scene_render(struct Scene *scene, struct Bitmap bitmap) {
	float aspect = (float)bitmap.width / bitmap.height;
	for (int x = 0; x < bitmap.width; x++) {
			float fx = ((2 * (float)x / bitmap.width) - 1) * aspect;
		for (int y = 0; y < bitmap.height; y++) {
			float fy = ((2 * (float)y / bitmap.height) - 1);
			//printf("x: %f, y: %f\n", fx, fy);
			fvec3 orgin = (fvec3) {0, 0,-2};
			fvec3 filmP = (fvec3) {fx, fy, 0};
			fvec3 dir = fvec3_normalize(fvec3_sub(orgin, filmP));
			fvec3 color = scene_renderRay(
				scene,
				(struct Ray) {.start = orgin, .direction = dir }
			);
			bitmap.pixels[y * bitmap.width + x] = fvec3_toARGB(color);
		}
	}
}
