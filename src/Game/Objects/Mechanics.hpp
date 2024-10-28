#ifndef MECHANICS_H
#define MECHANICS_H

#include <array>
#include "Coordinate.hpp"

namespace Mechanics 
{
    std::array<Point, 4> giveNewPiece(char type);

    namespace Collision
    {
        bool collidesWall(std::array<Point, 4> target);
        bool collidesFloor(std::array<Point, 4> target);
    };
}

#endif
