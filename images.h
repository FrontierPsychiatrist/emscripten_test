#ifndef _IMAGES_H
#define _IMAGES_H

#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"

#define SPRITE_F_FORWARD 0

/**
* An image we want to display
*/
struct SpriteImage {
    SDL_Texture *texture;
    SDL_Rect rect;
};

/**
* A sequence of images
*/
struct Animation {
    struct SpriteImage **sequence;
    int length;
    int *displayTimes;
};

void initImageFiles();
void destroyFiles();
struct Animation* getAnimation(int animationId);

#endif