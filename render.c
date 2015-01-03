#include "SDL2/SDL.h"

#include "state.h"
#include "images.h"

extern struct State *state;

// also needed in images.c to load the textures
SDL_Renderer *renderer;
static SDL_Window *screen;

void render_init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Could not initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }
    SDL_CreateWindowAndRenderer(640, 480, 0, &screen, &renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
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

void render_destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(screen);
}
