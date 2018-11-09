#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include <SDL2/SDL.h>

#include "config.h"

#include "types/sys.h"
#include "types/vid.h"

#include "eng/main.h"

exit_code eng_main(eng_args *args) {
  scr_width = args->width ? args->width : 800;
  scr_height = args->height ? args->height : 600;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "%s: SDL init error: %s\n", args->invoc, SDL_GetError());
    return 1;
  }

  SDL_Window* window = SDL_CreateWindow(
    "Splat",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    scr_width, scr_height,
    SDL_WINDOW_SHOWN
  );

  if (!window) {
    fprintf(stderr, "%s: SDL window error: %s\n", args->invoc, SDL_GetError());
    return 1;
  }

  SDL_Surface* surface = SDL_GetWindowSurface(window);

  eng_upd_state state = {0};

  bool cont = true;
  while (cont) {
    eng_update(&state);
    eng_render(window, surface);

    cont = !state.quit_req;
  }

  return 0;
}

void eng_update(eng_upd_state *s) {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    switch (e.type) {
      case SDL_QUIT:
        s->quit_req = true;
        break;
    }
  }
}

void eng_render(SDL_Window* window, SDL_Surface* surface) {
  SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
  SDL_UpdateWindowSurface(window);
}
