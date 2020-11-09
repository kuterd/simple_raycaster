#include <math.h>
#include <assert.h>

#include "object.h"
#include "vec.h"
#include "utils.h"
#include "ray.h"

// ---- Sphere ----
/* struct SphereData { */
/*     float radius; */
/* }; */

struct RaycastResult sphere_raycast(struct Object object, struct Ray ray) {
    assert(object.type == SPHERE);
    float radius = object.sphere_data.radius;
    fvec3 rel_start = fvec3_sub(ray.start, object.position);
    float a = fvec3_dotProduct(ray.direction, ray.direction);
    float b = 2 * fvec3_dotProduct(rel_start, ray.direction);
    float c = fvec3_dotProduct(rel_start, rel_start) - radius * radius;

    float d = b * b - 4 * a * c;
    if (d < 0) {
        return (struct RaycastResult) {
            .succsess = 0
        };
    }

    float x1, x2;
    float d_root = sqrt(d);
    x1 = 0.5 * (-b + d_root) / a;
    x2 = 0.5 * (-b - d_root) / a;

    // Smallest pozitive root if possible
    float t = min(max(x1, 0), max(x2, 0));
    if(t > 0) {
        fvec3 pos = fvec3_add(ray.start, fvec3_mulc(ray.direction, t));
        fvec3 norml = fvec3_sub(pos, object.position);
        return (struct RaycastResult) {
            .succsess = 1,
            .time = t,
            .position = pos,
            .normal = fvec3_divc(norml, radius)
        };
    }

    return (struct RaycastResult) {
        .succsess = 0
    };
}

struct Object sphere_create(fvec3 pos, float radius, unsigned int material_id) {
    return (struct Object) {
        .position = pos,
        .type = SPHERE,
        .material_id = material_id,
        .sphere_data = (struct SphereData) {.radius = radius}
    };
}

// ---- Plane ----

/* struct PlaneData { */
/*     fvec3 normal; */
/* }; */

struct RaycastResult plane_raycast(struct Object object, struct Ray ray) {
    assert(object.type == PLANE);
    fvec3 rel_start = fvec3_sub(ray.start, object.position);
    //-normal * start / direction * normal
    float t = -fvec3_dotProduct(
        object.plane_data.normal, rel_start) /
         fvec3_dotProduct(ray.direction, object.plane_data.normal
    );

    return (struct RaycastResult) {
        .succsess = t > 0,
        .time = t,
        .position = fvec3_add(ray.start, fvec3_mulc(ray.direction, t)),
        .normal = object.plane_data.normal
    };
}

struct Object plane_create(fvec3 pos, fvec3 normal, unsigned int material_id) {
    return (struct Object) {
        .position = pos,
        .type = PLANE,
        .material_id = material_id,
        .plane_data = (struct PlaneData) {
            .normal = normal
        }
    };
}

// ---- Disk ----


/* struct DiskData { */
/*     fvec3 normal; */
/*     float radius; */
/* }; */


struct RaycastResult disk_raycast(struct Object object, struct Ray ray) {
    assert(object.type == DISK);
    fvec3 normal = object.disk_data.normal;
    fvec3 rel_start = fvec3_sub(ray.start, object.position);
    //-normal * start / direction * normal
    float t = -fvec3_dotProduct(
        object.disk_data.normal, rel_start) /
         fvec3_dotProduct(ray.direction, object.disk_data.normal
    );


    if (t > 0) {
        fvec3 rx = (fvec3) {normal.x, -normal.z, normal.y};
        fvec3 rz = (fvec3) {-normal.y, normal.x, normal.z};

        fvec3 position = fvec3_add(ray.start, fvec3_mulc(ray.direction, t));
        fvec3 rePos = fvec3_sub(position, object.position);

        float x = fvec3_dotProduct(rePos, rx);
        float y = fvec3_dotProduct(rePos, rz);
        float r = object.disk_data.radius;

        return (struct RaycastResult) {
            .succsess = x * x + y * y < r * r,
            .time = t,
            .position = position,
            .normal = object.disk_data.normal
        };
    } else {
        return (struct RaycastResult) {
            .succsess = 0
        };
    }
}

struct Object disk_create(fvec3 pos, fvec3 normal,
                          float radius, unsigned int material_id) {
    return (struct Object) {
        .position = pos,
        .type = DISK,
        .material_id = material_id,
        .disk_data = (struct DiskData) {
            .normal = normal,
            .radius = radius
        }
    };
}

struct RaycastResult object_raycast(struct Object object, struct Ray ray) {
    struct RaycastResult result;
    // Replace this with function pointers
    switch (object.type) {
    case SPHERE:
        result = sphere_raycast(object, ray);
        break;
    case PLANE:
        result = plane_raycast(object, ray);
        break;
    case DISK:
        result = disk_raycast(object, ray);
        break;
    default:
        assert(0);
    }
    result.object = object;
    result.ray = ray;
    return result;
}
