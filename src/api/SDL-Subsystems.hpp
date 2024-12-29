#ifndef SDL_SUBSYSTEMS_H
#define SDL_SUBSYSTEMS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>

struct SDL_Subsystems
{
    SDL_Subsystems();

    ~SDL_Subsystems();

    // Getters
    SDL_Window* window() { return m_Window; }

    SDL_Renderer* renderer() { return m_Renderer; }

    TTF_Font* font() { return m_Font; }

private:
    SDL_Window* m_Window = nullptr;

    SDL_Renderer* m_Renderer = nullptr;

    TTF_Font* m_Font = nullptr;
};

#endif
