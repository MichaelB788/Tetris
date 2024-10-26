#ifndef TETRIS_H
#define TETRIS_H

#include <SDL2/SDL.h>
#include "../Components/Graphics.hpp"
#include "Objects/Piece.hpp"

typedef class Tetris
{
private:
    bool m_gameIsRunning = true;
     
    Piece m_currentPiece;

    void updateGame();

public:
    Tetris() = default;

    void runGame(GraphicsModule gm);
} Tetris;

#endif
