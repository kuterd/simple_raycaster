#ifndef RAY_H
#define RAY_H

#include "object.h"

struct Object;
struct Ray {
    fvec3 start;
    fvec3 direction;
};

struct RaycastResult {
    int succsess;
    float time;
    fvec3 normal;
    fvec3 position;
    struct Object object;
    struct Ray ray;
};

#endif
