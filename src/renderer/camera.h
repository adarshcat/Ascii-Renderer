#ifndef CAMERA_H
#define CAMERA_H

#include "renderer/render_settings.h"
#include "utils/mathc.h"

typedef struct Camera{
    mfloat_t position[VEC3_SIZE];
    mfloat_t target[VEC3_SIZE];
    mfloat_t up[VEC3_SIZE];

    mfloat_t viewMatrix[MAT4_SIZE];
    mfloat_t projectionMatrix[MAT4_SIZE];
} Camera;

void generateBasicCamera(Camera *camera);

#endif