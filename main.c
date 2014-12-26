#include "SDL2/SDL.h"

// for exit(1)
#include <stdio.h>

// for printf
#include <stdlib.h>

#include <math.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

static void refresh();
static void main_loop();
static void quit();
static void change_color();

static int gameover = 0;
static SDL_Window *screen;
static SDL_Renderer *renderer;

static void main_loop() {
  SDL_RenderClear(renderer);
  SDL_Event event;
  while(SDL_PollEvent(&event) > 0) {
    switch (event.type) {
    case SDL_QUIT:
      quit();
      break;
    case SDL_KEYDOWN:
      switch(event.key.keysym.sym) {
      case SDLK_ESCAPE:
      case SDLK_q:
        quit();
        break;
      }
      break;
    case SDL_MOUSEBUTTONDOWN:
      change_color();
      break;
    }
  }
  refresh();
}

static void change_color() {
  int color_r = rand() % 255;
  int color_g = rand() % 255;
  int color_b = rand() % 255;
  printf("Change color (%d, %d, %d)\n", color_r, color_g, color_b);
  SDL_SetRenderDrawColor(renderer, color_r, color_g, color_b, 255);
}

static void quit() {
#ifdef __EMSCRIPTEN__
  emscripten_cancel_main_loop();
#else
  gameover = 1;
#endif
  printf("Quit called\n");
}

static void refresh() {
  SDL_RenderPresent(renderer);
}

int main(int argc, char** argv) {
  if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("Could not initialize SDL: %s\n", SDL_GetError());
    exit(1);
  }
  SDL_CreateWindowAndRenderer(640, 480, 0, &screen, &renderer);
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);

#ifdef __EMSCRIPTEN__
  //framerate 0, infiniteloop = true
  emscripten_set_main_loop(main_loop, 0, 1);
#else
  while(!gameover) {
    main_loop();
    SDL_Delay(60);
  }
#endif
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(screen);
  SDL_Quit();
  return 0;
}
