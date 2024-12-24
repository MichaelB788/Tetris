#ifndef TETRIS_H
#define TETRIS_H

#include <SDL2/SDL.h>

#include "Objects/Piece.hpp"
#include "Objects/Mechanics.hpp"

typedef class Tetris
{
private:
    // Members 
    enum Difficulty 
    {
        EASY = 200,
        NORMAL = 150,
        HARD = 100 
    }; 

    Piece m_piece = Piece(Mechanics::assignTile());

    Difficulty m_difficulty = EASY;

    unsigned int m_timer = 0;

    unsigned int m_points = 0;

    bool m_running = true;

    // Functions
    void invokeGravity();

    void updateGame();

    void checkForFullRow();

public:
    Tetris();

} Tetris;

#endif
