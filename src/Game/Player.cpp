#include "Player.hpp"
#include "Objects/Piece.hpp"
#include "Objects/Mechanics.hpp"

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

    m_piece.modifyGrid();
}
