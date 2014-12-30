#include "SDL2/SDL.h"
// for printf
#include <stdio.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include "render.h"
#include "update.h"

#define TIMESTEP_MS 20

static void main_loop();
static void quit();

static int gameover = 0;

static Uint64 miliSecondsFactor;
static Uint64 lastTimestamp;

struct State *state;

static void main_loop() {
    Uint64 now = SDL_GetPerformanceCounter();
    Sint64 lastFrameTime = (now - lastTimestamp) / miliSecondsFactor;

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

    while (lastFrameTime > 0) {
        updateState(TIMESTEP_MS);
        lastFrameTime -= TIMESTEP_MS;
    }

    render(lastFrameTime);

    lastTimestamp = now;
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

    miliSecondsFactor = SDL_GetPerformanceFrequency() / 1000;
    lastTimestamp = SDL_GetPerformanceCounter();
#ifdef __EMSCRIPTEN__
    //framerate 0, infiniteloop = true
    emscripten_set_main_loop(main_loop, 0, 1);
#else
    while (!gameover) {
        main_loop();
        // TODO we should't need this but our loop is still much too fast (6ms...)
        SDL_Delay(160);
    }
#endif

    render_destroy();
    SDL_Quit();
    return 0;
}
