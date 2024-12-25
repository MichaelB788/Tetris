#ifndef PIECE_H
#define PIECE_H

#include "Coordinate.hpp"
#include "../Direction.hpp"
#include "../Tile.hpp"
#include <array>

typedef struct Piece
{
    // Constructor
    Piece(Tile type);

    // Methods
    std::array<Point, 4> translate(Direction dir);

    std::array<Point, 4> rotate();

    void swap();

    void store();

    void draw();

    // Setters
    void setPosition(std::array<Point, 4> newPosition)
    { m_position = newPosition; }

    // Getters
    Tile type() { return m_type; }

    Tile next() { return m_next; }

    Tile stored() { return m_stored; }
    
    std::array<Point, 4> position() { return m_position; }

private:
    std::array<Point, 4> m_position;

    Tile m_type, m_next, m_stored = NIL;
} Piece;

#endif
