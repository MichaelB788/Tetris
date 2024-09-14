#include <SDL2/SDL.h>

#include "SDLComponents.h"
#include "Window.h"
#include "Render.h"

// Store and access SDL systems
struct SDL_Components::SDL_Systems
{
    SDL_Window* win;
    SDL_Renderer* ren;
};

// Initialize all SDL Systems.
bool SDL_Components::initialize()
{
    struct SDL_Systems sdl;

    // initialize systems as null
    sdl.win = NULL;
    sdl.ren = NULL;

    // Create and check window state
    sdl.win = Window::createWindow();  

    if ( Window::isNull(sdl.win) )
    { terminate(); return false;}

    // Create and check renderer state
    sdl.ren = SDL_CreateRenderer(sdl.win, -1, 0);

    if ( Render::isNull(sdl.ren) )
    { terminate(); return false; }

    return true;
}

// Terminate all SDL Systems.
void SDL_Components::terminate()
{
    struct SDL_Systems sdl;

    SDL_DestroyWindow(sdl.win);
    sdl.win = NULL;

    SDL_DestroyRenderer(sdl.ren);
    sdl.ren = NULL;
}

SDL_Window* SDL_Components::getWindow()
{
    struct SDL_Systems sdl;
    return sdl.win; 
}

SDL_Renderer* SDL_Components::getRenderer()
{
    struct SDL_Systems sdl;
    return sdl.ren; 
}
