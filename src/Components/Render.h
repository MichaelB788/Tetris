#ifndef SDL_RENDERER
#define SDL_RENDERER

#include <SDL2/SDL.h>

namespace Render
{
    SDL_Renderer* createRenderer(SDL_Window * win);

    bool isNull(SDL_Renderer* ren);

    // void draw(SDL_Renderer* ren, int x, int y);
}

#endif
