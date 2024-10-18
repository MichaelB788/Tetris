#ifndef SDL_UTILS_H
#define SDL_UTILS_H

#include <SDL2/SDL.h>

namespace SDLUtils
{
    typedef struct WindowObject
    {
        SDL_Window* pSDL_Window = NULL;

        WindowObject();

        ~WindowObject();
    } WindowObject;

    typedef struct RendererObject
    {
        SDL_Renderer* pSDL_Renderer = NULL;

        RendererObject(SDL_Window* pSDL_Window);

        ~RendererObject();
    } RendererObject;

    extern WindowObject window;
    extern RendererObject renderer;
}

#endif
