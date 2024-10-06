#include <vector>

#include "Board.hpp"
#include "Piece.hpp"

char id;

void Piece::moveDown()
{
    if (isValidPosition())
    {
        // move the block down the row 
    }
}

void Piece::moveRight()
{
    if (isValidPosition())
    {
        // shift the block right once
    }
}

void Piece::moveLeft()
{
    if (isValidPosition())
    {
        // shift the block left once
    }
}

bool Piece::isValidPosition()
{
    /*
     * Check if the the piece is within a free space (0)
     * If the block is hitting wall (2), motion is stopped.
     **/
}

char Piece::getID()
{
    return id;
}

