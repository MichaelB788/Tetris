#ifndef PIECE_MANAGER
#define PIECE_MANAGER

#include <array>
#include "Coordinate.hpp"

namespace Logic 
{
    std::array<Point, 4> giveNewPiece(char _type);

    bool positionIsValid(std::array<Point, 4> &_coordinates);

    void releaseCurrentPiece();
}

#endif
