#ifndef PIECE_H
#define PIECE_H

#include "Coordinate.hpp"
#include <array>

enum Direction { NONE, LEFT, RIGHT, DOWN };

typedef struct Piece
{
    // Constructor
    Piece();

    // Methods
    std::array<Point, 4> translate(Direction dir);

    std::array<Point, 4> rotate();

    std::array<Point, 4> swap();
    
    void spawn();

    // Setters
    void setPosition(std::array<Point, 4> newPosition)
    { m_position = newPosition; }

    // Getters
    const char type() { return m_type; }
    
    std::array<Point, 4> position() { return m_position; }

private:
    std::array<Point, 4> m_position;

    char m_type;
} Piece;

#endif
