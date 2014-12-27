#include "SDL2/SDL.h"
// for printf
#include <stdio.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include "render.h"

static void main_loop();
static void quit();

static int gameover = 0;

static void main_loop() {
    SDL_Event event;
    while (SDL_PollEvent(&event) > 0) {
        switch (event.type) {
            case SDL_QUIT:
                quit();
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                    case SDLK_q:
                        quit();
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
    render();
}

static void quit() {
#ifdef __EMSCRIPTEN__
    emscripten_cancel_main_loop();
#else
    gameover = 1;
#endif
    printf("Quit called\n");
}

int main(int argc, char **argv) {
    render_init();

#ifdef __EMSCRIPTEN__
    //framerate 0, infiniteloop = true
    emscripten_set_main_loop(main_loop, 0, 1);
#else
    while (!gameover) {
        main_loop();
        SDL_Delay(60);
    }
#endif

    render_destroy();
    SDL_Quit();
    return 0;
}
