// SDL2 Library
#include <SDL2/SDL.h>
#include <vector>

// SDL Systems
#include "Components/Window.h"
#include "Components/Render.h"
#include "Components/SDLComponents.h"

#include "Game/Block.h"

int main (int argc, char **argv)
{
    // Initialize all SDL subsystems
    if (!SDL_Components::initialize()) return -1;

    // Window and Renderer subsystems
    SDL_Window* win = SDL_Components::getWindow();
    SDL_Renderer* ren = SDL_Components::getRenderer();

    Block test = Block('T');  
    Render::drawBlock(test, ren);

    SDL_Delay(10000);
    SDL_Components::terminate();
    return 0;
}
