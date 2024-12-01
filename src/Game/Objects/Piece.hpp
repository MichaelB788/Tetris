#ifndef PIECE_H
#define PIECE_H

#include "Coordinate.hpp"
#include <array>

enum Direction { NONE, LEFT, RIGHT, DOWN };

typedef struct Piece
{
    Piece();

    void translate(Direction dir);

    void revert();

    void swap();

    void modifyGrid();

    const char type();

    const Direction direction();

    std::array<Point, 4> getCurrArray();

    std::array<Point, 4> getPrevArray();

private:
    std::array<Point, 4> m_curr;

    std::array<Point, 4> m_prev;

    Direction m_direction;

    char m_type;
} Piece;

#endif
