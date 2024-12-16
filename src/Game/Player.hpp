#ifndef PLAYER_H
#define PLAYER_H

#include "Objects/Piece.hpp"

typedef struct Player
{
    Player() = default;

    bool positionIsValid();

    void move(Direction dir);

private:
    Piece m_piece;
} Player;

#endif
