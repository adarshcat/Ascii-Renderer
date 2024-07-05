#ifndef CUBE_H
#define CUBE_H

#define CUBE_TRIANGLES 6 * 2 // 6 faces, 2 triangles each face
#define DATA_PER_TRIANGLE 3 * 6 // 3 vertices per triangle, 6 data ver vertex
#define CUBE_DATA_SIZE CUBE_TRIANGLES * DATA_PER_TRIANGLE

#include "primitives/triangle.h"

void generateCubeData(Triangle *result);
void transformRotateCube(Triangle *triangles, Triangle *base, unsigned int totalTriangles, float time);

#endif

