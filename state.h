#ifndef _STATE_H
#define _STATE_H

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