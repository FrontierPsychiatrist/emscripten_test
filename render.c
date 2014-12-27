#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "render.h"

static void init_textures();

static SDL_Window *screen;
static SDL_Renderer *renderer;
static SDL_Texture *spriteTexture;

void render_init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Could not initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }
    SDL_CreateWindowAndRenderer(640, 480, 0, &screen, &renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    init_textures();
}

static Uint64 time = 0;
static Uint64 spriteSelection[3] = { 160000, 320000, 480000 };

void render(Uint64 nanoSeconds) {
    SDL_RenderClear(renderer);

    int whichSprite = 0;
    if(time > spriteSelection[0]) {
        whichSprite = 1;
    }
    if (time > spriteSelection[1]) {
        whichSprite = 2;
    }

    struct SDL_Rect const srcrect = {.x = 24 * whichSprite, .y = 32, .h = 32, .w = 24};
    struct SDL_Rect const dstrect = {.x = 320, .y = 240, .h = 64, .w = 48};
    SDL_RenderCopy(renderer, spriteTexture, &srcrect, &dstrect);

    time += nanoSeconds;
    if (time >= spriteSelection[2]) time = 0;
    SDL_RenderPresent(renderer);
}

static void init_textures() {
    spriteTexture = IMG_LoadTexture(renderer, "../data/sprite_f.png");
    if (spriteTexture == 0) {
        printf("Could not load sprite texture: %s\n", SDL_GetError());
    }
}

void render_destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(screen);
}
