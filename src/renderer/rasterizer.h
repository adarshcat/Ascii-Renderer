#ifndef RASTERIZER_H
#define RASTERIZER_H

#include "renderer/camera.h"
#include "renderer/image.h"
#include "primitives/triangle.h"

void projectToClipSpace(mfloat_t *result, mfloat_t *point, Camera *camera);

int edgeFunction(mfloat_t *a, mfloat_t *b, mfloat_t *c);
void rasterize(Image *resultTexture, Triangle *triangles, unsigned int numTriangles, Camera *camera);

#endif