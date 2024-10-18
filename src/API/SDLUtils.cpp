#include "SDLUtils.hpp"

#include <SDL2/SDL.h>
#include <assert.h>

SDLUtils::WindowObject::WindowObject()
{
    // Initializes video and event subsystems
    assert((SDL_Init(SDL_INIT_VIDEO) == 0));

    pSDL_Window = SDL_CreateWindow("Block Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 900, 900, SDL_WINDOW_SHOWN);

    assert((pSDL_Window != NULL));
}

SDLUtils::RendererObject::RendererObject(SDL_Window* pSDL_Window)
{
    pSDL_Renderer = SDL_CreateRenderer(pSDL_Window, -1, SDL_RENDERER_ACCELERATED);
    assert((pSDL_Renderer != NULL));
}

SDLUtils::WindowObject::~WindowObject()
{
    SDL_DestroyWindow(pSDL_Window);
    pSDL_Window = NULL;
}

SDLUtils::RendererObject::~RendererObject()
{
    SDL_DestroyRenderer(pSDL_Renderer);
    pSDL_Renderer = NULL;
}

