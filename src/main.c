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

    while (1){
        clrscr();
        printf("Hello World\n");

        delay(&lastTickClock);
    }

    return 0;
}