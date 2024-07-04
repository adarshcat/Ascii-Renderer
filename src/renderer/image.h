#ifndef IMAGE_H
#define IMAGE_H

#define IMAGE_WIDTH 40
#define IMAGE_HEIGHT 40

typedef unsigned char byte;

typedef struct Image{
    byte data[IMAGE_WIDTH * IMAGE_HEIGHT];
} Image;

void initialiseImage(Image *image);

#endif