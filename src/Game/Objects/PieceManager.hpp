#ifndef PIECE_MANAGER
#define PIECE_MANAGER

#include <array>
#include "Coordinate.hpp"

namespace PieceManager 
{
    std::array<Point, 4> giveNewPiece(char type);

    bool positionIsValid(std::array<Point, 4> &coordinates);

    void releaseCurrentPiece();
}

#endif
