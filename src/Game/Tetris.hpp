#ifndef TETRIS_H
#define TETRIS_H

#include <SDL2/SDL.h>
#include "../Components/Graphics.hpp"

typedef class Tetris
{
private:
    SDL_Event event;
    bool gameIsRunning = true;

public:
    Tetris() = default;
    void runGame(GraphicsModule gm);
} Tetris;

#endif
