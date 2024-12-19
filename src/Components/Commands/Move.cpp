#include "Move.hpp"
#include "../../Game/Objects/Mechanics.hpp"
#include "../../Game/Objects/Grid.hpp"
#include <array>

void MoveCommand::execute()
{
    oldPosition = newPosition;
    newPosition = p_piece->translate(m_direction);

    if (Mechanics::collidesObject(p_piece))
    {
        undo();
        if (m_direction == DOWN)
        {
            Mechanics::ground(p_piece);
            p_piece->swap();
        }
    }
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
