#ifndef PIECE_MANAGER
#define PIECE_MANAGER

#include "Coordinate.hpp"

namespace PieceManager 
{
    Coordinate::FourPoints giveNewPiece(char type);

    bool isValidPosition(Coordinate::FourPoints &coordinates);

    void releaseCurrentPiece();
}

#endif
