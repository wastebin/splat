#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include <SDL2/SDL.h>

#include "t_sys.hh"

#include "eng_main.hh"

#include "settings.hh"

int display;

SDL_Window* window;
SDL_Surface* surface;

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
  res = args->res;
  if (!res) res = VID_RES_AUTO;

  mode = args->mode;
  if (!mode) mode = res == VID_RES_SPEC ? VID_MODE_WINDOWED : VID_MODE_FULLSCREEN;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "%s: SDL init error: %s\n", args->invoc, SDL_GetError());
    return 1;
  }

  window = SDL_CreateWindow(
    "Splat",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    640, 480,
    SDL_WINDOW_HIDDEN
  );

  if (!window) {
    fprintf(stderr, "%s: SDL window error: %s\n", args->invoc, SDL_GetError());
    return 1;
  }

  display = SDL_GetWindowDisplayIndex(window);

  if (res == VID_RES_AUTO) {
    SDL_DisplayMode dm;
    SDL_GetDesktopDisplayMode(display, &dm);
    scr_width = dm.w;
    scr_height = dm.h;
  } else {
    scr_width = args->width ? args->width : 800;
    scr_height = args->height ? args->height : 600;
  }

  SDL_SetWindowSize(window, scr_width, scr_height);

  if (mode == VID_MODE_FULLSCREEN) SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
  else SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

  SDL_ShowWindow(window);

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
