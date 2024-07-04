#include "primitives/cube.h"

#include <stdio.h>

void generateCubePoints(float *result){
    float cubePoints[] = {
        // back face
        -1.0f, -1.0f, -1.0f, // bottom-left
        1.0f,  1.0f, -1.0f, // top-right
        1.0f, -1.0f, -1.0f, // bottom-right         
        1.0f,  1.0f, -1.0f, // top-right
        -1.0f, -1.0f, -1.0f, // bottom-left
        -1.0f,  1.0f, -1.0f, // top-left
        // front face
        -1.0f, -1.0f,  1.0f, // bottom-left
        1.0f, -1.0f,  1.0f, // bottom-right
        1.0f,  1.0f,  1.0f, // top-right
        1.0f,  1.0f,  1.0f, // top-right
        -1.0f,  1.0f,  1.0f, // top-left
        -1.0f, -1.0f,  1.0f, // bottom-left
        // left face
        -1.0f,  1.0f,  1.0f, // top-right
        -1.0f,  1.0f, -1.0f, // top-left
        -1.0f, -1.0f, -1.0f, // bottom-left
        -1.0f, -1.0f, -1.0f, // bottom-left
        -1.0f, -1.0f,  1.0f, // bottom-right
        -1.0f,  1.0f,  1.0f, // top-right
        // right face
        1.0f,  1.0f,  1.0f, // top-left
        1.0f, -1.0f, -1.0f, // bottom-right
        1.0f,  1.0f, -1.0f, // top-right         
        1.0f, -1.0f, -1.0f, // bottom-right
        1.0f,  1.0f,  1.0f, // top-left
        1.0f, -1.0f,  1.0f, // bottom-left     
        // bottom face
        -1.0f, -1.0f, -1.0f, // top-right
        1.0f, -1.0f, -1.0f, // top-left
        1.0f, -1.0f,  1.0f, // bottom-left
        1.0f, -1.0f,  1.0f, // bottom-left
        -1.0f, -1.0f,  1.0f, // bottom-right
        -1.0f, -1.0f, -1.0f, // top-right
        // top face
        -1.0f,  1.0f, -1.0f, // top-left
        1.0f,  1.0f , 1.0f, // bottom-right
        1.0f,  1.0f, -1.0f, // top-right     
        1.0f,  1.0f,  1.0f, // bottom-right
        -1.0f,  1.0f, -1.0f, // top-left
        -1.0f,  1.0f,  1.0f // bottom-left
    };

    for (int i=0; i<CUBE_POINTS_SIZE; i++){
        result[i] = cubePoints[i];
    }
}