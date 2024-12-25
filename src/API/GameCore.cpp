#include <SDL2/SDL.h>
#include <assert.h>

#include "GameCore.hpp"
#include "Screen.hpp"

GameCore::GameCore()
{
    m_Window = SDL_CreateWindow("Tetris",
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                SCREEN_WIDTH,
                                SCREEN_LENGTH,
                                SDL_WINDOW_SHOWN);

    m_Renderer = SDL_CreateRenderer(m_Window,
                                    -1, // the index of the rendering driver
                                    SDL_RENDERER_ACCELERATED);

    assert(m_Window != NULL && m_Renderer != NULL);
}

// Destructors
GameCore::~GameCore()
{
    // Destroy everything
    SDL_DestroyWindow(m_Window);
    SDL_DestroyRenderer(m_Renderer);

    // Set to null and quit
    m_Renderer = nullptr, m_Window = nullptr;
    SDL_Quit();
}
