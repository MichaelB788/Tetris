#ifndef PIECE_H
#define PIECE_H

#include "Coordinate.hpp"
#include <array>

enum Direction { LEFT, RIGHT, DOWN };

typedef struct Piece
{
    Piece();

    void translate(Direction dir);

    void revert();

    void swap();

    bool compare(char tile);

    bool contains(Point otherPoint);

    void modifyGrid();

private:
    std::array<Point, 4> m_curr;

    std::array<Point, 4> m_prev;

    char m_type;
} Piece;

#endif
