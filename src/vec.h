#ifndef VEC_H
#define VEC_H

typedef struct {
    float x, y;
} fvec2;

typedef union {
    struct {
        float x, y, z;
    };
    fvec2 xy;
} fvec3;

typedef union {
    struct {
        float x, y, z, w;
    };
    fvec2 xy;
    fvec3 xyz;
} fvec4;

typedef struct {
    int x, y;
} ivec2;

typedef union {
    struct {
        int x, y, z;
    };
    ivec2 xy;
} ivec3;

typedef union {
    struct {
        int x, y, z, w;
    };
    ivec2 xy;
    ivec3 xyz;
} ivec4;

float fvec3_length2(fvec3 a);
float fvec3_length(fvec3 a);
fvec3 fvec3_mulc(fvec3 a, float b);
fvec3 fvec3_divc(fvec3 a, float b);
fvec3 fvec3_normalize(fvec3 a);
float fvec3_dotProduct(fvec3 a, fvec3 b);
fvec3 fvec3_sub(fvec3 a, fvec3 b);
fvec3 fvec3_add(fvec3 a, fvec3 b);
fvec3 fvec3_colorToVec(unsigned int color);
unsigned int fvec3_toARGB(fvec3 color);

#endif
