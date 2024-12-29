#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "SDL-Subsystems.hpp"

SDL_Subsystems::SDL_Subsystems()
{
    const unsigned int
        WINDOW_WIDTH = 800, WINDOW_LENGTH = 800;

    // SDL window
    m_Window = SDL_CreateWindow("Tetris",
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                WINDOW_WIDTH,
                                WINDOW_LENGTH,
                                SDL_WINDOW_SHOWN);
    if ( !m_Window )
    {
        std::cout << "Failed to load window: " <<
            SDL_GetError() << std::endl;
    }

    // SDL renderer
    m_Renderer = SDL_CreateRenderer(m_Window,
                                    -1, // the index of the rendering driver
                                    SDL_RENDERER_ACCELERATED);
    if ( !m_Renderer )
    {
        std::cout << "Failed to load renderer: " <<
            SDL_GetError() << std::endl;
    }

    // TTF Font
    m_Font = TTF_OpenFont("../font/Micro_5/Micro5-Regular.ttf", 8); 
    if ( !m_Font )
    {
        std::cout << "Failed to load font: " <<
            TTF_GetError() << std::endl;
    }
}

// Destructors
SDL_Subsystems::~SDL_Subsystems()
{
    // Destroy everything
    SDL_DestroyWindow(m_Window);
    SDL_DestroyRenderer(m_Renderer);
    TTF_CloseFont(m_Font);

    // Set to null and quit
    m_Renderer = nullptr,
        m_Window = nullptr,
        m_Font = nullptr;

    SDL_Quit();
}
