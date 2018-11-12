#pragma once

#ifndef ENG_MAIN_HH
#define ENG_MAIN_HH

#include <stdbool.h>

#include <SDL2/SDL.h>

#include "t_sys.hh"

extern SDL_Window* window;
extern SDL_Surface* surface;

exit_code eng_main(eng_args *);
exit_code eng_init(eng_args *);

typedef struct {
  bool quit_req;
} eng_upd_state;

void eng_update(eng_upd_state *);
void eng_render(SDL_Window *, SDL_Surface *);

#endif
