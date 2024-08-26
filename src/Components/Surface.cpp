#include <SDL2/SDL.h>
#include <iostream>
#include "Surface.h"

void Surface::renderText(SDL_Surface *surface, string message)
{
    if (surface = NULL) { 
        std::cout << "SDL_GetWindowSurface Error: " << SDL_GetError() << std::endl; 
    }
}


