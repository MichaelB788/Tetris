#ifndef MECHANICS_H
#define MECHANICS_H

#include <array>
#include <locale>
#include <stdexcept>

#include "GameConstants.hpp"
#include "Coordinate.hpp"
#include "Tetromino.hpp"
#include "Command.hpp"
#include "Coordinate.hpp"
#include "Tetromino.hpp"

namespace Mechanics 
{
    std::array<Point, 4> giveNewPiece(Tile type);
    
    Tile assignTile();

    bool collidesObject(Tetromino target);

    void ground(Tetromino target);

    void invokeGravity(Tetromino& piece,
                       unsigned int time,
                       Difficulty &difficulty);

    void checkFullRow(unsigned int &points);
}

#endif
