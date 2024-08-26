#include <SDL2/SDL.h>

#include "Components/Window.h"
#include "Components/Render.h"

// Access SDL systems
struct SDL_Systems
{
    SDL_Window* win;
    SDL_Renderer* ren;
};

void terminate()
{
    struct SDL_Systems sdl;

    SDL_DestroyWindow(sdl.win);
    sdl.win = NULL;

    SDL_DestroyRenderer(sdl.ren);
    sdl.ren = NULL;
}

int main (int argc, char **argv)
{
    struct SDL_Systems sdl;

    sdl.win = NULL;
    sdl.ren = NULL;

    // Handle window
    sdl.win = Window::createWindow();  
    if ( Window::isNull(sdl.win) )
    { 
        terminate();
        return -1;
    }

    // Handle renderer
    sdl.ren = SDL_CreateRenderer(sdl.win, -1, 0);
    if ( Render::isNull(sdl.ren) )
    { 
        terminate();
        return -1;
    }

    // Test
    Render::drawTetromino();

    SDL_Delay(10000);
    terminate();
    return 0;
}
