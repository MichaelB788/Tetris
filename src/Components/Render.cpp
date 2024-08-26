#include <SDL2/SDL.h>
#include <iostream>

#include "Render.h"

SDL_Renderer* Render::createRenderer(SDL_Window* win)
{
    return SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
}

bool Render::isNull(SDL_Renderer* ren)
{
    if (ren == NULL) 
        std::cout << "Renderer could not be created: " << SDL_GetError() << std::endl; 

    return ren == NULL;
}

