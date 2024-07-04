#ifndef RASTERIZER_H
#define RASTERIZER_H

#include "renderer/image.h"
#include "primitives/triangle.h"

void rasterize(Image *resultTexture, Triangle *triangles, unsigned int numTriangles);

#endif