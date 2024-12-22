#include "Drop.hpp"
#include "../../Game/Objects/Mechanics.hpp"
#include "../../Game/Objects/Grid.hpp"
#include <array>

void DropCommand::execute()
{
    for (Point& point : newPosition)
        Grid::set(point, '#');

    while (!Mechanics::collidesObject(p_piece))
    {
        oldPosition = newPosition;
        newPosition = p_piece->translate(DOWN);
    }

    undo();

    display();
}

void DropCommand::undo()
{
    p_piece->setPosition(oldPosition);
}

void DropCommand::display()
{
    Mechanics::ground(p_piece);

    newPosition = p_piece->swap();
}
