#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "render.h"
#include "state.h"

extern struct State *state;

static void init_state();

static SDL_Window *screen;
static SDL_Renderer *renderer;

void render_init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Could not initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }
    SDL_CreateWindowAndRenderer(640, 480, 0, &screen, &renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    init_state();
}

void render(Sint64 nanoSeconds) {
    SDL_RenderClear(renderer);

    for (int i = 0; i < state->numSprites; ++i) {
        struct Sprite *sprite = &state->sprites[i];
        struct SpriteImage *image = sprite->currentAnimation->sequence[sprite->currentAnimationStep];
        struct SDL_Rect const dstrect = { .x = sprite->posX, .y = sprite->posY, .h = image->rect.h * 3, .w = image->rect.w * 3 };
        SDL_RenderCopy(renderer, image->texture, &image->rect, &dstrect);
    }

    SDL_RenderPresent(renderer);
}

static SDL_Texture *spriteTexture;
static struct SpriteImage *loadedImages;
static struct Animation animation;

static void init_state() {
    spriteTexture = IMG_LoadTexture(renderer, "../data/sprite_f.png");
    if (spriteTexture == 0) {
        printf("Could not load sprite texture: %s\n", SDL_GetError());
    }
    loadedImages = malloc(3 * sizeof(struct SpriteImage));
    struct SpriteImage image1 = { .texture = spriteTexture, .rect = { .x = 0, .y = 32, .h = 32, .w = 24}};
    loadedImages[0] = image1;
    struct SpriteImage image2 = { .texture = spriteTexture, .rect = { .x = 24, .y = 32, .h = 32, .w = 24}};
    loadedImages[1] = image2;
    struct SpriteImage image3 = { .texture = spriteTexture, .rect = { .x = 48, .y = 32, .h = 32, .w = 24}};
    loadedImages[2] = image3;

    animation.sequence = malloc(4 * sizeof(struct SpriteImage*));
    animation.sequence[0] = loadedImages;
    animation.sequence[1] = &loadedImages[1];
    animation.sequence[2] = &loadedImages[2];
    animation.sequence[3] = &loadedImages[1];
    animation.displayTimes = malloc(4 * sizeof(int));
    animation.displayTimes[0] = 160;
    animation.displayTimes[1] = 160;
    animation.displayTimes[2] = 160;
    animation.displayTimes[3] = 160;
    animation.length = 4;

    state = malloc(sizeof(state));
    state->sprites = malloc(sizeof(struct Sprite));
    state->numSprites = 1;

    state->sprites[0].currentAnimation = &animation;
    state->sprites[0].currentAnimationStep = 0;
    state->sprites[0].posX = 320;
    state->sprites[0].posY = 240;
    state->sprites[0].currentStepDisplayTime = 0;
}

void render_destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(screen);
}
