#ifndef PLAYER_H
#define PLAYER_H

#include "Objects/Piece.hpp"

typedef struct Player
{
    Player();

    Piece getPiece(); 

    bool positionIsValid();

    void move(Direction dir);

    void incrementPoint();

private:
    Piece m_piece;
} Player;

#endif
