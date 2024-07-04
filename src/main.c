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
    clock_t lastTickClock = clock();

    // initialise the render texture
    Image renderImage;
    initialiseImage(&renderImage);

    // initialise the camera
    Camera camera;
    generateBasicCamera(&camera);

    // initialise the cube buffer
    Triangle cubeData[CUBE_TRIANGLES];
    generateCubeData(&cubeData[0]);

    while (1){
        clrscr(); // clear the screen

        printf("Hello World\n");

        delay(&lastTickClock); // wait just enough time for next frame (crap this doesnt take into account above exec time, hope its negligible)
    }

    return 0;
}