#include <SDL2/SDL.h>
#include <iostream>
#include "Surface.h"

void Surface::renderText(SDL_Surface *surface, string message)
{
    // Get the SDL surface assosciated with the window and check if operation was successful.
    surface = TTF_RenderText_Solid(font, "Hello World", white);
}

// Get the SDL surface assosciated with the window and check if operation was successful.
if (surface = NULL) { 
    std::cout << "SDL_GetWindowSurface Error: " << SDL_GetError() << std::endl; 
}

