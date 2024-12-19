#include "Move.hpp"
#include "../../Game/Objects/Mechanics.hpp"
#include "../../Game/Objects/Grid.hpp"
#include <array>

void MoveCommand::execute()
{
    oldPosition = newPosition;
    newPosition = p_piece->translate(m_direction);

    if (invalidPosition()) undo();
    else display();
}

void MoveCommand::undo()
{
    p_piece->setPosition(oldPosition);
}

void MoveCommand::display()
{
    for (Point& point : oldPosition)
        Grid::set(point, '#');

    for (Point& point : newPosition)
        Grid::set(point, p_piece->type());
}

bool MoveCommand::invalidPosition()
{
    if (Mechanics::collidesObject(p_piece))
    {
        if (m_direction == DOWN) p_piece->swap();
        return true;
    }

    return false;
}

