#include "renderer/rasterizer.h"

#include <stdlib.h>
#include <stdio.h>

inline void projectToClipSpace(mfloat_t *result, mfloat_t *point, Camera *camera){
    mfloat_t pointV4[VEC4_SIZE];
    vec4(pointV4, point[0], point[1], point[2], 1.0);

    // convert to view space
    mfloat_t viewSpace[VEC4_SIZE];
    vec4_multiply_mat4(viewSpace, pointV4, camera->viewMatrix);

    // convert to clip space
    mfloat_t projected[VEC4_SIZE];
    vec4_multiply_mat4(projected, viewSpace, camera->projectionMatrix);

    // perspective divide and store z from view space (+ve)
    vec3(result, projected[0]/projected[3], projected[1]/projected[3], -viewSpace[2]);
}


inline float edgeFunctionF(mfloat_t *a, mfloat_t *b, mfloat_t *c){
    return (c[0] - a[0]) * (b[1] - a[1]) - (c[1] - a[1]) * (b[0] - a[0]);
}

void rasterize(Image *resultTexture, Image *depthBuffer, Triangle *triangles, unsigned int numTriangles, Camera *camera, mfloat_t *sunVector){
    for (int i=0; i<numTriangles; i++){
        Triangle triangle = triangles[i];

        mfloat_t v0[VEC3_SIZE];
        mfloat_t v1[VEC3_SIZE];
        mfloat_t v2[VEC3_SIZE];

        projectToClipSpace(v0, triangle.v1.position, camera);
        projectToClipSpace(v1, triangle.v2.position, camera);
        projectToClipSpace(v2, triangle.v3.position, camera);

        //printf("%f %f %f\n", triangle.v1.normal[0], triangle.v1.normal[1], triangle.v1.normal[2]);

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

                float area = edgeFunctionF(rv0, rv1, rv2);
                float w0 = edgeFunctionF(rv1, rv2, p);
                float w1 = edgeFunctionF(rv2, rv0, p);
                float w2 = edgeFunctionF(rv0, rv1, p);

                if (w0 >= 0 && w1 >= 0 && w2 >= 0){
                    // convert the edge function outputs to bayecentric coords
                    w0 /= area;
                    w1 /= area;
                    w2 /= area;

                    // compute depth
                    float oneOverPz = (1.0/v0[2])*w0 + (1.0/v1[2])*w1 + (1.0/v2[2])*w2;
                    float pz = 1.0 / oneOverPz;

                    // if has the least depth than all previous iterations, override the info..
                    if (depthBuffer->data[y*IMAGE_WIDTH + x] > pz){
                        depthBuffer->data[y*IMAGE_WIDTH + x] = pz;

                        // some basic shading based on the normal vec and sun direction
                        mfloat_t dotProd = vec3_dot(triangle.v1.normal, sunVector);
                        dotProd = ((dotProd < 0.0)? 0.0 : dotProd) + 0.05;
                        dotProd = (dotProd > 1.0)? 1.0 : dotProd;

                        resultTexture->data[y*IMAGE_WIDTH + x] = dotProd;
                    }
                }

            }
        }
        
    }
}