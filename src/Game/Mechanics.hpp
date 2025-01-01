#ifndef MECHANICS_H
#define MECHANICS_H

#include <array>
#include "Variables.hpp"
#include "Objects/Coordinate.hpp"
#include "Objects/Piece.hpp"

namespace Mechanics 
{
    std::array<Point, 4> giveNewPiece(Tile type);
    
    Tile assignTile();

    bool collidesObject(Piece target);

    void ground(Piece target);

    void invokeGravity(Piece& piece,
                       unsigned int time,
                       Difficulty &difficulty);

    void checkFullRow(unsigned int &points);
}

#endif
