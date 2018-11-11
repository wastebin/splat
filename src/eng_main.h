#pragma once

#ifndef ENG_MAIN_H
#define ENG_MAIN_H

#include <stdbool.h>

#include <SDL2/SDL.h>

#include "t_sys.h"

SDL_Window* window;
SDL_Surface* surface;

exit_code eng_main(eng_args *);
exit_code eng_init(eng_args *);

typedef struct {
  bool quit_req;
} eng_upd_state;

void eng_update(eng_upd_state *);
void eng_render(SDL_Window *, SDL_Surface *);

#endif
