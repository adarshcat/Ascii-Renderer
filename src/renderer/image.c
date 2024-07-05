#include "renderer/image.h"

void clearImage(Image *image){
    for (int i=0; i<IMAGE_WIDTH*IMAGE_HEIGHT; i++){
        image->data[i] = 0.0;
    }
}

void clearImageF(Image *image, float val){
    for (int i=0; i<IMAGE_WIDTH*IMAGE_HEIGHT; i++){
        image->data[i] = val;
    }
}

