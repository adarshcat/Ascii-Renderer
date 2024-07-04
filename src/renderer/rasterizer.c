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


int edgeFunction(mfloat_t *a, mfloat_t *b, mfloat_t *c){
    return ((c[0] - a[0]) * (b[1] - a[1]) - (c[1] - a[1]) * (b[0] - a[0]) >= 0)? 0 : -1;
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

        // convert the ndc coordinates to raster space
        mfloat_t rv0[VEC2_SIZE];
        mfloat_t rv1[VEC2_SIZE];
        mfloat_t rv2[VEC2_SIZE];

        vec2(rv0, ((v0[0] + 1.0)/2.0) * IMAGE_WIDTH, ((1.0 - v0[1])/2.0) * IMAGE_HEIGHT);
        vec2(rv1, ((v1[0] + 1.0)/2.0) * IMAGE_WIDTH, ((1.0 - v1[1])/2.0) * IMAGE_HEIGHT);
        vec2(rv2, ((v2[0] + 1.0)/2.0) * IMAGE_WIDTH, ((1.0 - v2[1])/2.0) * IMAGE_HEIGHT);


        for (int x=0; x<IMAGE_WIDTH; x++){
            for (int y=0; y<IMAGE_HEIGHT; y++){
                mfloat_t p[VEC2_SIZE];
                vec2(p, x, y);

                int check1 = edgeFunction(rv0, rv1, p);
                int check2 = edgeFunction(rv1, rv2, p);
                int check3 = edgeFunction(rv2, rv0, p);

                if ((check1 + check2 + check3) == 0){
                    resultTexture->data[y*IMAGE_WIDTH + x] = 255;
                }

            }
        }
        
    }
}