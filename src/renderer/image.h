#ifndef IMAGE_H
#define IMAGE_H

#include "renderer/render_settings.h"

typedef struct Image{
    float data[IMAGE_WIDTH * IMAGE_HEIGHT];
} Image;

void clearImage(Image *image);
void clearImageF(Image *image, float val);

#endif