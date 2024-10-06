#include <SDL2/SDL.h>
#include <iostream>

#include "Window.hpp"

WindowObject::WindowObject()
{
        pSDL_Window = SDL_CreateWindow("Block Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 900, 900, SDL_WINDOW_SHOWN);

    if (pSDL_Window == NULL)
        std::cout << "Window has not been initialized: " << SDL_GetError() << std::endl; 

}

WindowObject::~WindowObject()
{
    SDL_DestroyWindow(pSDL_Window);
    pSDL_Window = NULL;
}
