#ifndef UTILS_H
#define UTILS_H

#define min(a, b) (a) > (b) ? (b) : (a)
#define max(a, b) (a) < (b) ? (b) : (a)

#define swap(a, b)           \
{                            \
    typeof(a) a_ = a;        \
    a = b;                   \
    b = a_;                  \
}

float random_float(float min, float max);

#endif
