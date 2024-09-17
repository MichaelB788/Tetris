#ifndef SDL_COMPONENTS
#define SDL_COMPONENTS

#include <SDL2/SDL.h>

namespace SDL_Components 
{    
    struct SDL_Systems;
    
    bool initialize();
    void terminate();
    
    SDL_Window* getWindow();
    SDL_Renderer* getRenderer();
}

#endif
