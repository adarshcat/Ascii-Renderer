#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// some macro which makes clear screen cross-platform (just call clrscr() to clear screen now)
#ifdef _WIN32
#define clrscr() system("cls")
#else
#define clrscr() system("clear")
#endif

#define FRAME_RATE 15

#include "primitives/triangle.h"
#include "primitives/cube.h"

#include "renderer/camera.h"
#include "renderer/image.h"
#include "renderer/rasterizer.h"

char asciiList[] = " `.-:_=;><+!rc*/z?)J{C}flu[$0MNW@"; // just some ascii characters sorted based on brightness

void delay(clock_t *lastTickClock){
    clock_t currentClock = clock();
    clock_t deltaClock = currentClock - *lastTickClock;

    while (((float) deltaClock) / CLOCKS_PER_SEC < (1.0 / FRAME_RATE)){
        currentClock = clock();
        deltaClock = currentClock - *lastTickClock;
    }

    *lastTickClock = currentClock;
}

int main(){
    // hides cursor
    printf("\e[?25l");

    clock_t lastTickClock = clock();

    // initialise the render texture
    Image frameBuffer;
    clearImage(&frameBuffer);

    // Basic lighting
    mfloat_t sunVector[VEC3_SIZE];
    vec3(sunVector, 10.0, 5.0, 3.0);
    vec3_normalize(sunVector, sunVector);

    // initialise the camera
    Camera camera;
    generateBasicCamera(&camera);

    // initialise the cube buffer
    Triangle cubeDataBase[CUBE_TRIANGLES]; // this is for storing base transformation of the cube
    Triangle cubeData[CUBE_TRIANGLES]; // this cube is for storing real-time calculations (transformations and rots..)
    generateCubeData(&cubeDataBase[0]);
    generateCubeData(&cubeData[0]);

    // console string to be printed onto the terminal at once
    char consoleString[(IMAGE_WIDTH+1)*IMAGE_HEIGHT+1];
    consoleString[(IMAGE_WIDTH+1)*IMAGE_HEIGHT] = 0;

    // fills the console string with new lines at the end of each row
    for (int i=0; i<IMAGE_HEIGHT; i++){
        consoleString[i*(IMAGE_WIDTH+1) + IMAGE_WIDTH] = '\n';
    }

    float time = 0.0; // for rotating the cube

    while (1){
        clrscr(); // clear the screen

        time += 0.1;
        transformRotateCube(cubeData, cubeDataBase, CUBE_TRIANGLES, time);

        clearImage(&frameBuffer);
        rasterize(&frameBuffer, cubeData, CUBE_TRIANGLES, &camera, sunVector);

        for (int y=0; y<IMAGE_HEIGHT; y++){
            for (int x=0; x<IMAGE_WIDTH; x++){
                float brightness = frameBuffer.data[y*IMAGE_WIDTH + x];
                int asciiIndex = brightness * (sizeof(asciiList)-2);

                consoleString[y*(IMAGE_WIDTH+1) + x] = asciiList[asciiIndex];
            }
            //printf("\n");
        }

        printf(consoleString);

        delay(&lastTickClock); // wait just enough time for next frame based on frameRate
    }

    return 0;
}