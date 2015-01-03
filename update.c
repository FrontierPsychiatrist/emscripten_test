#include "update.h"

#include "state.h"
#include "images.h"

extern struct State *state;

static void updateSprites(int miliseconds);

void updateState(int miliseconds) {
    updateSprites(miliseconds);
}

static void updateSprites(int miliseconds) {
    for (int i = 0; i < state->numSprites; ++i) {
        struct Sprite *sprite = &state->sprites[i];
        sprite->currentStepDisplayTime += miliseconds;

        if(sprite->currentStepDisplayTime > sprite->currentAnimation->displayTimes[sprite->currentAnimationStep]) {
            sprite->currentStepDisplayTime = 0;
            sprite->currentAnimationStep = (sprite->currentAnimationStep + 1) % sprite->currentAnimation->length;
        }
    }
}
