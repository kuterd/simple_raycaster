#ifndef OBJECT_H
#define OBJECT_H

#include "vec.h"

/* struct ObjectOps { */
/*     void (*free)(struct Object *object); */
/*     struct RaycastResult (*raycast)(struct Object *object); */
/* }; */

enum ObjectType {
  SPHERE = 0,
  PLANE,
  DISK
};

struct SphereData {
  float radius;
};

struct PlaneData {
  fvec3 normal;
};

struct DiskData {
  fvec3 normal;
  float radius;
};

struct Object {
    enum ObjectType type;
    fvec3 position;
    void *object_data;
    union {
      struct SphereData sphere_data;
      struct PlaneData plane_data;
      struct DiskData disk_data;
    };
    unsigned int material_id;
};

struct Object sphere_create(fvec3 pos, float radius, unsigned int material_id);
struct Object plane_create(fvec3 pos, fvec3 normal, unsigned int material_id);
struct Object disk_create(fvec3 pos, fvec3 normal,
                          float radius, unsigned int material_id);

struct Ray;
struct RaycastResult;
struct RaycastResult object_raycast(struct Object object, struct Ray ray);

#endif
