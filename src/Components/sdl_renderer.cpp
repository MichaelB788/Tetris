#include <SDL2/SDL.h>
#include <iostream>

namespace renderer
{
    private:
    SDL_Renderer *renderer = NULL;
    
    public:
    void init()
    {
        // Get the SDL renderer associated with the window and check if operation was successful.
        renderer = SDL_GetRenderer(window); 
        if (renderer = NULL) { 
                std::cout << "SDL_GetRenderer Error: " << SDL_GetError() << std::endl; 
        }
    }
}
