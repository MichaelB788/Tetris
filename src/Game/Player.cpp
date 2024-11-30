#include "Player.hpp"
#include "Objects/Piece.hpp"
#include "Objects/Mechanics.hpp"

Player::Player() : m_piece(Piece()) {}

Piece Player::getPiece() 
{
    return m_piece;
}

bool Player::positionIsValid()
{
    if (Mechanics::Collision::floor(m_piece))
    {
        m_piece.swap();
        return false;
    }
    else if (Mechanics::Collision::wallOrPiece(m_piece))
    {
        return false;
    }

    return true;
}

void Player::move(Direction dir)
{
    m_piece.translate(dir);
    if (!positionIsValid()) m_piece.revert();
}
