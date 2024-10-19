#include <SDL2/SDL.h>
#include <assert.h>

#include "GameCore.hpp"

GameCore::GameCore()
{
    assert(SDL_Init(SDL_INIT_VIDEO) == 0);

    m_Window = SDL_CreateWindow("Block Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 1000, SDL_WINDOW_SHOWN);

    assert((m_Window != NULL));

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);

    assert((m_Renderer != NULL));
}

// Destructors
void GameCore::terminate()
{
    SDL_DestroyWindow(m_Window);
    m_Window = nullptr;

    SDL_DestroyRenderer(m_Renderer);
    m_Renderer = nullptr;
}
