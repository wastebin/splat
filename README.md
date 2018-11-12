# Splat
Splat is an RPG with roguelite gameplay elements that I’ve been working on. I
was writing it in C++ at first, then I switched over to pure C (see
[here](https://github.com/wastebin/splatc)), and now it’s in C-ish C++.

Almost nothing is implemented.

## Command Line Options
### `+fullscreen`
Sets video mode to fullscreen.

### `+windowed`
Sets video mode to windowed.

### `+res-auto`
Sets resolution to auto.

### `+res WIDTHxHEIGHT`
Sets resolution to WIDTH by HEIGHT manually.

## Video Modes
Only one of these may be active at a time.

### Fullscreen
The game will take up the entire screen. The default video mode.

### Windowed
The game will appear in a floating window. The default video mode when
resolution is manual.

## Resolution types
Only one of these may be active at a time.

### Auto
The game resolution will be the autodetected desktop resolution. The default
resolution type when in fullscreen.

### Manual
The game resolution is specified manually.
