#ifndef TETRIS_H
#define TETRIS_H

#include <SDL2/SDL.h>
#include "../Components/Graphics.hpp"
#include "Objects/TetrisBoard.hpp"

typedef class Tetris
{
private:
    bool gameIsRunning = true;

    TetrisBoard::Piece currentPiece;

    void updateGame();

public:
    Tetris() = default;

    void runGame(GraphicsModule gm);
} Tetris;

#endif
