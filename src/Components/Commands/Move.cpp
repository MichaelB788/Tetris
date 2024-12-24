#include "Move.hpp"
#include "../../Game/Objects/Mechanics.hpp"
#include "../../Game/Objects/Grid.hpp"
#include <array>

void MoveCommand::execute()
{
    newPosition = p_piece->translate(m_direction);

    if (Mechanics::collidesObject(p_piece))
        enforceCollision();

    else Grid::clear(oldPosition);
}

void MoveCommand::undo()
{
    p_piece->setPosition(oldPosition);
}

void MoveCommand::enforceCollision()
{
    undo();

    if (m_direction == DOWN)
    {
        Mechanics::ground(p_piece);
        p_piece->swap();
    }
}
