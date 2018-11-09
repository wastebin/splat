#pragma once

#ifndef ENG_MAIN_H
#define ENG_MAIN_H

#include <stdbool.h>

#include <SDL2/SDL.h>

#include "types/sys.h"

exit_code eng_main(eng_args *);

typedef struct {
  bool quit_req;
} eng_upd_state;

void eng_update(eng_upd_state *);
void eng_render(SDL_Window *, SDL_Surface *);

#endif
