#ifndef GAMECORE_H
#define GAMECORE_H

#include <SDL2/SDL.h>

typedef struct GameCore
{
    SDL_Window* m_Window = nullptr;

    SDL_Renderer* m_Renderer = nullptr;

    GameCore();

    ~GameCore();
}GameCore;

#endif
