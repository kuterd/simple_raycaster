#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "utils.h"

float random_float(float min, float max) {
	return (float)rand()/RAND_MAX * (max - min) + min;
}
