#pragma once

#ifndef T_VID_HH
#define T_VID_HH

typedef enum {
  VID_MODE_NONE = false,
  VID_MODE_WINDOWED,
  VID_MODE_FULLSCREEN
} vid_mode;

typedef enum {
  VID_RES_NONE = false,
  VID_RES_AUTO,
  VID_RES_SPEC
} vid_res;

#endif
