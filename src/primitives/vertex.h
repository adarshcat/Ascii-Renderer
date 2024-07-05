#ifndef VERTEX_H
#define VERTEX_H

#include "utils/mathc.h"

typedef struct Vertex{
    mfloat_t position[VEC3_SIZE];
    mfloat_t normal[VEC3_SIZE];
} Vertex;

#endif

