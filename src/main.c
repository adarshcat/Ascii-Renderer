#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// some macro which makes clear screen cross-platform (just call clrscr() to clear screen now)
#ifdef _WIN32
#define clrscr() system("cls")
#else
#define clrscr() system("clear")
#endif

#define FRAME_RATE 8

#include "primitives/triangle.h"
#include "primitives/cube.h"

#include "renderer/camera.h"
#include "renderer/image.h"
#include "renderer/rasterizer.h"


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
    Image renderImage;
    clearImage(&renderImage);

    // initialise the camera
    Camera camera;
    generateBasicCamera(&camera);

    // initialise the cube buffer
    Triangle cubeDataBase[CUBE_TRIANGLES]; // this is for storing base information
    Triangle cubeData[CUBE_TRIANGLES]; // this cube is for storing real-time calculations (transformations and rots..)
    generateCubeData(&cubeDataBase[0]);

    // console string to be printed onto the terminal at once
    char consoleString[(IMAGE_WIDTH+1)*IMAGE_HEIGHT+1];
    consoleString[(IMAGE_WIDTH+1)*IMAGE_HEIGHT] = 0;

    for (int i=0; i<IMAGE_HEIGHT; i++){
        consoleString[i*(IMAGE_WIDTH+1) + IMAGE_WIDTH] = '\n';
    }

    float time = 0.0; // for rotating the cube

    while (1){
        clrscr(); // clear the screen

        time += 0.1;
        transformRotateCube(cubeData, cubeDataBase, CUBE_TRIANGLES, time);

        clearImage(&renderImage);
        rasterize(&renderImage, cubeData, CUBE_TRIANGLES, &camera);

        for (int y=0; y<IMAGE_HEIGHT; y++){
            for (int x=0; x<IMAGE_WIDTH; x++){
                byte brightness = renderImage.data[y*IMAGE_WIDTH + x];

                if (brightness == 0){
                    //printf("  ");
                    consoleString[y*(IMAGE_WIDTH+1) + x] = ' ';
                } else {
                    //printf("##");
                    consoleString[y*(IMAGE_WIDTH+1) + x] = '@';
                }
            }
            //printf("\n");
        }

        printf(consoleString);

        delay(&lastTickClock); // wait just enough time for next frame
    }

    return 0;
}