#include <SDL2/SDL.h>
#include <iostream>

namespace surface
{
    private:
    SDL_Surface *surface = NULL;

    public:
    // Get the SDL surface assosciated with the window and check if operation was successful.
    surface = TTF_RenderText_Solid(font, "Hello World", white);
    if (surface = NULL) { 
	    std::cout << "SDL_GetWindowSurface Error: " << SDL_GetError() << std::endl; 
    }
}
