#ifndef BLOCK_H
#define BLOCK_H

#include "Coordinate.hpp"
#include "Board.hpp"

typedef struct Piece
{
    typedef enum Direction : unsigned int 
    {
        LEFT, RIGHT, DOWN
    } Direction;

    Piece(char type, Board board);

    void move(Direction dir);

    void rotate(Direction dir);

private:
    Coordinate::FourPoints coordinates;
    Board mBoard;
} Piece;

#endif
