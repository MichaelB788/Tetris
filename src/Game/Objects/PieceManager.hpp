#ifndef PIECE_MANAGER
#define PIECE_MANAGER

#include "Coordinate.hpp"
#include "Board.hpp"

namespace PieceManager 
{
    Coordinate::FourPoints giveNewPiece(char type);

    bool isValidPosition(Coordinate::FourPoints &coordinates, Board board);

    void releaseCurrentPiece();
}

#endif
