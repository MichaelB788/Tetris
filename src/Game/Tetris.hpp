#ifndef TETRIS_H
#define TETRIS_H

#include <SDL2/SDL.h>
#include "../Components/Graphics.hpp"
#include "Objects/Board.hpp"
#include "Objects/Piece.hpp"

typedef class Tetris
{
private:
    SDL_Event event;
    bool gameIsRunning = true;
    Board board;

public:
    Tetris() = default;

    void runGame(GraphicsModule gm);
} Tetris;

#endif
