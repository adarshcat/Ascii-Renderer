#include "renderer/rasterizer.h"

#include <stdio.h>

// takes a 3d point and a camera, projects it to clip space and gives the 2d coords
void projectToClipSpace(mfloat_t *result, mfloat_t *point, Camera *camera){
    // construct the view projection matrix (optimize later)
    // TODO: optimize later
    mfloat_t viewProjection[MAT4_SIZE];
    mat4_multiply(viewProjection, camera->projectionMatrix, camera->viewMatrix);

    mfloat_t pointV4[VEC4_SIZE];
    vec4(pointV4, point[0], point[1], point[2], 1.0);

    mfloat_t projected[VEC4_SIZE];
    vec4_multiply_mat4(projected, pointV4, viewProjection);

    // perspective divide
    vec3(result, projected[0]/projected[3], projected[1]/projected[3], projected[2]/projected[3]);
}

void rasterize(Image *resultTexture, Triangle *triangles, unsigned int numTriangles, Camera *camera){
    for (int i=0; i<numTriangles; i++){
        Triangle triangle = triangles[i];

        mfloat_t v0[VEC3_SIZE];
        mfloat_t v1[VEC3_SIZE];
        mfloat_t v2[VEC3_SIZE];

        projectToClipSpace(v0, triangle.v1.position, camera);
        projectToClipSpace(v1, triangle.v2.position, camera);
        projectToClipSpace(v2, triangle.v3.position, camera);

        
    }
}