#ifndef _STATE_H
#define _STATE_H

#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"

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

/**
* A sprite that is currently on the screen
*/
struct Sprite {
    int posX;
    int posY;
    struct Animation *currentAnimation;
    int currentAnimationStep;
    int currentStepDisplayTime;
};

struct State {
    struct Sprite *sprites;
    int numSprites;
};

#endif