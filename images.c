#include "images.h"

#define NUMBER_OF_ANIMATIONS 1

extern SDL_Renderer *renderer;

static struct Animation *animations;

static SDL_Texture *sprite_f_texture;
static struct SpriteImage *sprite_f_images;
static void loadSpriteF() {
    sprite_f_texture = IMG_LoadTexture(renderer, "../data/sprite_f.png");
    if (sprite_f_texture == 0) {
        printf("Could not load sprite texture: %s\n", SDL_GetError());
    }
    sprite_f_images = malloc(3 * sizeof(struct SpriteImage));
    struct SpriteImage image1 = { .texture = sprite_f_texture, .rect = { .x = 0, .y = 32, .h = 32, .w = 24}};
    sprite_f_images[0] = image1;
    struct SpriteImage image2 = { .texture = sprite_f_texture, .rect = { .x = 24, .y = 32, .h = 32, .w = 24}};
    sprite_f_images[1] = image2;
    struct SpriteImage image3 = { .texture = sprite_f_texture, .rect = { .x = 48, .y = 32, .h = 32, .w = 24}};
    sprite_f_images[2] = image3;

    animations[SPRITE_F_FORWARD].sequence = malloc(4 * sizeof(struct SpriteImage*));
    animations[SPRITE_F_FORWARD].sequence[0] = sprite_f_images;
    animations[SPRITE_F_FORWARD].sequence[1] = &sprite_f_images[1];
    animations[SPRITE_F_FORWARD].sequence[2] = &sprite_f_images[2];
    animations[SPRITE_F_FORWARD].sequence[3] = &sprite_f_images[1];
    animations[SPRITE_F_FORWARD].displayTimes = malloc(4 * sizeof(int));
    animations[SPRITE_F_FORWARD].displayTimes[0] = 160;
    animations[SPRITE_F_FORWARD].displayTimes[1] = 160;
    animations[SPRITE_F_FORWARD].displayTimes[2] = 160;
    animations[SPRITE_F_FORWARD].displayTimes[3] = 160;
    animations[SPRITE_F_FORWARD].length = 4;
}

void initImageFiles() {
    animations = malloc(NUMBER_OF_ANIMATIONS * sizeof(struct Animation));
    loadSpriteF();
}

void destroyFiles() {
    SDL_DestroyTexture(sprite_f_texture);
    free(sprite_f_images);
    free(animations);
}

struct Animation* getAnimation(int animationId) {
    return &animations[animationId];
}
