#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include <SDL2/SDL.h>

#include "t_sys.h"
#include "t_vid.h"

#include "eng_main.h"

#include "settings.h"

exit_code eng_main(eng_args *args) {
  {
    exit_code c = eng_init(args);
    if (c) return c;
  }

  eng_upd_state state = {0};

  bool cont = true;
  while (cont) {
    eng_update(&state);
    eng_render(window, surface);

    cont = !state.quit_req;
  }

  return 0;
}

exit_code eng_init(eng_args *args) {
  scr_width = args->width ? args->width : 800;
  scr_height = args->height ? args->height : 600;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "%s: SDL init error: %s\n", args->invoc, SDL_GetError());
    return 1;
  }

  window = SDL_CreateWindow(
    "Splat",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    scr_width, scr_height,
    SDL_WINDOW_SHOWN
  );

  if (!window) {
    fprintf(stderr, "%s: SDL window error: %s\n", args->invoc, SDL_GetError());
    return 1;
  }

  surface = SDL_GetWindowSurface(window);

  return 0;
}

void eng_update(eng_upd_state *s) {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    switch (e.type) {
      case SDL_QUIT:
        s->quit_req = true;
        break;
      case SDL_KEYDOWN:
        // TODO: ignore SDL_KEYDOWNs until corresponding SDL_KEYUP RECEIVED
        switch (e.key.keysym.sym) {
          case SDLK_ESCAPE:
            s->quit_req = true;
            break;
        }
        break;
    }
  }
}

void eng_render(SDL_Window* window, SDL_Surface* surface) {
  SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
  SDL_UpdateWindowSurface(window);
}
