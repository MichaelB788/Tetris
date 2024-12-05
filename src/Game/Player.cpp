#include <iostream>

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
    if (Mechanics::Collision::wallOrPiece(m_piece))
    {
        if (m_piece.direction() == DOWN) m_piece.swap();
        return false;
    }

    return true;
}

void Player::move(Direction dir)
{
    m_piece.translate(dir);
    if (!positionIsValid()) m_piece.revert();
}

void Player::incrementPoint()
{
    m_points++;
}

void Player::points()
{
    std::cout << "Points earned: " << m_points << std::endl;
}
