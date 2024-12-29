#ifndef TETRIS_H
#define TETRIS_H

#include <SDL2/SDL.h>

#include "Objects/Piece.hpp"
#include "Mechanics.hpp"

typedef class Tetris
{
private:
    // Members 

    unsigned int m_timer = 0, m_points = 0;

    bool m_running = true;

    Difficulty m_difficulty = EASY;

    Piece m_piece = Piece(Mechanics::assignTile());

    // Functions
    void updateGame();
public:
    Tetris();

} Tetris;

#endif
