#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>
class RendererObject
{
public:
    SDL_Renderer* pSDL_Renderer = NULL;

    RendererObject(SDL_Window* pSDL_Window);
    ~RendererObject();
};

#endif
