#pragma once

#ifndef T_SYS_HH
#define T_SYS_HH

#include "t_vid.hh"

typedef int exit_code;

typedef struct {
  char *invoc;

  vid_mode mode;
  vid_res res;

  int width;
  int height;
} eng_args;

exit_code eng_args_init(eng_args *, int, char **);

#endif
