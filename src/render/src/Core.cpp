#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Core.hpp"
#include "sdl/Font.hpp"
#include "sdl/Window.hpp"

Core::Core() :
    m_window(Window("Tetris",
                    SDL_WINDOWPOS_CENTERED,
                    SDL_WINDOWPOS_CENTERED,
                    800,
                    800,
                    SDL_WINDOW_SHOWN)),

    m_renderer(Renderer(m_window.get(),
                        -1, 
                        SDL_RENDERER_ACCELERATED)),

    m_font(Font("../font/Jersey_10/Jersey10-Regular.ttf", 20))
{}

Core::~Core()
{
    SDL_Quit();
}
