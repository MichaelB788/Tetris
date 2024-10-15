#ifndef BLOCK_H
#define BLOCK_H

#include "Coordinate.hpp"
#include "Board.hpp"

typedef struct Piece : Board
{
    enum Direction : unsigned int;

    Piece(char type);

    void move(Direction dir);

    void rotate(Direction dir);

private:
    Coordinate::FourPoints coordinates;
} Piece;

#endif
