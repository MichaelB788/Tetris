#include <SDL2/SDL.h>
#include <iostream>

#include "Window.h"

SDL_Window* Window::createWindow()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "Could not initialize SDL Video: " << SDL_GetError() << std::endl;
        return NULL; 
    }
    else
    {
        return SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 900, 900, SDL_WINDOW_SHOWN);
    }
}

bool Window::isNull(SDL_Window* win)
{
    if (win == NULL)
        std::cout << "Window has not been initialized: " << SDL_GetError() << std::endl; 

    return win == NULL;
}
