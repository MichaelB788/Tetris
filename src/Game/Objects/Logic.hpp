#ifndef LOGIC_H
#define LOGIC_H

#include <array>
#include "Coordinate.hpp"

namespace Logic 
{
    std::array<Point, 4> giveNewPiece(char type);

    bool positionIsValid(std::array<Point, 4> coordinates);

    void releaseCurrentPiece();

    class CollisionDetection
    {
        std::array<Point, 4> m_target;

        bool collidesWallOrFloor();

    public:
        CollisionDetection(std::array<Point, 4> target);

        bool result();
    };
}

#endif
