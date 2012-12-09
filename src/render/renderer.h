/**
 * render.h
 */
#ifndef RENDER_HEADER_SEEN
#define RENDER_HEADER_SEEN

#include "SDL/SDL.h"

typedef struct renderer* Renderer;

struct renderer {
    SDL_Surface* screen;
};

Renderer CreateRenderer(void);

#endif
