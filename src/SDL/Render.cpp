#include <SDL2/SDL.h>
#include <iostream>

#include "Render.hpp"

RendererObject::RendererObject(SDL_Window* pSDL_Window)
{
    pSDL_Renderer = SDL_CreateRenderer(pSDL_Window, -1, SDL_RENDERER_ACCELERATED);

    // Check to see if creation of renderer was successful.
    if (pSDL_Renderer == NULL)
    {
        std::cout << "Renderer could not be created: " << SDL_GetError() << std::endl; 
    }
}

RendererObject::~RendererObject()
{
    SDL_DestroyRenderer(pSDL_Renderer);
    pSDL_Renderer = NULL;
}
