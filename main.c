#include "SDL/SDL.h"

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
static SDL_Surface *screen;

static void main_loop() {
  SDL_Event event;
  if(SDL_PollEvent(&event)) {
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
  SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, color_r, color_g, color_b));
  SDL_Flip(screen);
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
  SDL_UpdateRect(screen, 0, 0, 0, 0);
}

int main(int argc, char** argv) {
  if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("Could not initialize SDL: %s\n", SDL_GetError());
    exit(1);
  }
  screen = SDL_SetVideoMode(640, 480, 0, 0);
  SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 255, 0, 0));
  SDL_Flip(screen);
  SDL_WM_SetCaption("Da test", NULL);

#ifdef __EMSCRIPTEN__
  //framerate 0, infiniteloop = true
  emscripten_set_main_loop(main_loop, 0, 1);
#else
  while(!gameover) {
    main_loop();
    SDL_Delay(60);
  }
#endif
  SDL_Quit();
  return 0;
}
