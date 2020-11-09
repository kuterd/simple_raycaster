#include "vec.h"
#include <math.h>
float fvec3_length2(fvec3 a) {
    return a.x * a.x + a.y * a.y + a.z * a.z;
}

float fvec3_length(fvec3 a) {
    return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

fvec3 fvec3_mulc(fvec3 a, float b) {
    return (fvec3) {a.x * b, a.y * b, a.z * b};
}

fvec3 fvec3_divc(fvec3 a, float b) {
    return (fvec3) {a.x / b, a.y / b, a.z / b};
}

fvec3 fvec3_normalize(fvec3 a) {
    float length = fvec3_length(a);
    return (fvec3) {a.x / length, a.y / length, a.z / length};
}

float fvec3_dotProduct(fvec3 a, fvec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

fvec3 fvec3_sub(fvec3 a, fvec3 b) {
    return (fvec3) {a.x - b.x, a.y - b.y, a.z - b.z};
}

fvec3 fvec3_add(fvec3 a, fvec3 b) {
    return (fvec3) {a.x + b.x, a.y + b.y, a.z + b.z};
}

fvec3 fvec3_colorToVec(unsigned int color) {
    return (fvec3) {
        .x = ((color & 0x00FF0000) >> 16) / 255.0,
        .y = ((color & 0x0000FF00) >> 8) / 255.0,
        .z = (color & 0x000000FF) / 255.0,
    };
}

unsigned int fvec3_toARGB(fvec3 color) {
    color = fvec3_mulc(color, 255);
    return (0xFF << 24 |
        (unsigned int)(color.x) << 16 |
        (unsigned int)(color.y) << 8 |
        (unsigned int)(color.z));
}
