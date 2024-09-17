// SDL2 Library
#include <SDL2/SDL.h>

// SDL Systems
#include "src/Components/SDLComponents.h"

int main (int argc, char **argv)
{
    // Initialize SDL
    if (!SDL_Components::initialize()) return 1;

    // Window and Renderer subsystems
    SDL_Window* win = SDL_Components::getWindow();
    SDL_Renderer* ren = SDL_Components::getRenderer();

    SDL_Delay(10000);
    SDL_Components::terminate();
    return 0;
}
