#include "primitives/cube.h"

#include <stdio.h>

void generateCubeData(Triangle *result){
    float cubeData[] = {
        // back face
        -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
        1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
        1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
        1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
        // front face
        -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
        1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
        1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
        1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
        // left face
        -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,
        -1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f,
        -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,
        -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,
        -1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f,
        -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,
        // right face
        1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,
        1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,
        1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f,
        1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,
        1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,
        1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,
        // bottom face
        -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,
        1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,
        1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,
        1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,
        -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,
        -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,
        // top face
        -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f,
        1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f
    };

    for (int i=0; i<CUBE_TRIANGLES; i++){
        int dataOrigin = i*DATA_PER_TRIANGLE;
        // write the position and nroma from cubeData buffer into the vertex1
        vec3(&result[i].v1.position[0], cubeData[dataOrigin+0], cubeData[dataOrigin+1], cubeData[dataOrigin+2]);
        vec3(&result[i].v1.normal[0], cubeData[dataOrigin+3], cubeData[dataOrigin+4], cubeData[dataOrigin+5]);
        
        // write the position and nroma from cubeData buffer into the vertex2
        vec3(&result[i].v2.position[0], cubeData[dataOrigin+6], cubeData[dataOrigin+7], cubeData[dataOrigin+8]);
        vec3(&result[i].v2.normal[0], cubeData[dataOrigin+9], cubeData[dataOrigin+10], cubeData[dataOrigin+11]);

        // write the position and nroma from cubeData buffer into the vertex3
        vec3(&result[i].v3.position[0], cubeData[dataOrigin+12], cubeData[dataOrigin+13], cubeData[dataOrigin+14]);
        vec3(&result[i].v3.normal[0], cubeData[dataOrigin+15], cubeData[dataOrigin+16], cubeData[dataOrigin+17]);
    }
}

void transformRotateCube(Triangle *triangles, Triangle *base, unsigned int totalTriangles, float time){
    mfloat_t _cache[VEC4_SIZE];

    mfloat_t rotationMatrix[MAT4_SIZE];
    mat4_identity(rotationMatrix);
    mat4_rotation_axis(rotationMatrix, vec3(_cache, 1, 0, 1), time);

    for (int i=0; i<totalTriangles; i++){
        mfloat_t t1[VEC4_SIZE];
        mfloat_t t2[VEC4_SIZE];
        mfloat_t t3[VEC4_SIZE];
        // transform the vertex positions
        vec4(_cache, base[i].v1.position[0], base[i].v1.position[1], base[i].v1.position[2], 1.0);
        vec4_multiply_mat4(t1, _cache, rotationMatrix);

        vec4(_cache, base[i].v2.position[0], base[i].v2.position[1], base[i].v2.position[2], 1.0);
        vec4_multiply_mat4(t2, _cache, rotationMatrix);

        vec4(_cache, base[i].v3.position[0], base[i].v3.position[1], base[i].v3.position[2], 1.0);
        vec4_multiply_mat4(t3, _cache, rotationMatrix);
        
        // write the vertex positions
        vec3(triangles[i].v1.position, t1[0], t1[1], t1[2]);
        vec3(triangles[i].v2.position, t2[0], t2[1], t2[2]);
        vec3(triangles[i].v3.position, t3[0], t3[1], t3[2]);
        // ------------------------------------
        

        vec4(_cache, base[i].v1.normal[0], base[i].v1.normal[1], base[i].v1.normal[2], 0.0);
        vec4_multiply_mat4(t1, _cache, rotationMatrix);

        vec4(_cache, base[i].v2.normal[0], base[i].v2.normal[1], base[i].v2.normal[2], 0.0);
        vec4_multiply_mat4(t2, _cache, rotationMatrix);

        vec4(_cache, base[i].v3.normal[0], base[i].v3.normal[1], base[i].v3.normal[2], 0.0);
        vec4_multiply_mat4(t3, _cache, rotationMatrix);
        
        // write the vertex normals
        vec3(triangles[i].v1.normal, t1[0], t1[1], t1[2]);
        vec3(triangles[i].v2.normal, t2[0], t2[1], t2[2]);
        vec3(triangles[i].v3.normal, t3[0], t3[1], t3[2]);
    }
}