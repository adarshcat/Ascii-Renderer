#include "renderer/image.h"

void initialiseImage(Image *image){
    for (int i=0; i<IMAGE_WIDTH*IMAGE_HEIGHT; i++){
        image->data[i] = 0;
    }
}