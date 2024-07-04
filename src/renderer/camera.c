#include "renderer/camera.h"

void generateBasicCamera(Camera *camera){
    mat4_look_at(camera->viewMatrix,
        vec3(camera->position, 0.0, 0.0, -5.0),
        vec3(camera->target, 0.0, 0.0, 0.0),
        vec3(camera->up, 0.0, 1.0, 0.0)
    );

    float aspectRatio = ((float) IMAGE_WIDTH) / IMAGE_HEIGHT;

    mat4_perspective(camera->projectionMatrix, to_radians(90.0), aspectRatio, 0.1, 100.0);
}