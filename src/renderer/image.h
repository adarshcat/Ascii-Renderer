#ifndef IMAGE_H
#define IMAGE_H

#include "renderer/render_settings.h"

typedef unsigned char byte;

typedef struct Image{
    byte data[IMAGE_WIDTH * IMAGE_HEIGHT];
} Image;

void clearImage(Image *image);

#endif