#ifndef PIECE_H
#define PIECE_H

#include "Coordinate.hpp"
#include <array>

enum Direction { NONE, LEFT, RIGHT, DOWN };

typedef struct Piece
{
    Piece();

    std::array<Point, 4> translate(Direction dir);

    void spawn();

    void swap();
    
    void setPosition(std::array<Point, 4> newPosition)
    { m_position = newPosition; }

    const char type() { return m_type; }
    
    std::array<Point, 4> position() { return m_position; }

private:
    std::array<Point, 4> m_position;

    char m_type;
} Piece;

#endif
