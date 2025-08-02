#include "Renderer.hpp"
#include <iostream>

Renderer::Renderer(SDL_Window* window, int index, Uint32 flags)
{
    ren = SDL_CreateRenderer(window, index, flags); 

    if ( !ren )
    {
        std::cout << "Failed to load renderer: " <<
            SDL_GetError() << std::endl;
    }
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(ren);
}
