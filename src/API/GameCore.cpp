#include <SDL2/SDL.h>
#include <assert.h>

#include "GameCore.hpp"

GameCore::GameCore()
{
    m_Window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_SHOWN);

    assert((m_Window != NULL));

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);

    assert((m_Renderer != NULL));
}

// Destructors
GameCore::~GameCore()
{
    SDL_DestroyWindow(m_Window);
    m_Window = nullptr;

    SDL_DestroyRenderer(m_Renderer);
    m_Renderer = nullptr;

    SDL_Quit();
}
