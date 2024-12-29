#include "Drop.hpp"
#include "../../Game/Mechanics.hpp"
#include "../../Game/Objects/Grid.hpp"
#include <array>

void DropCommand::execute()
{
    Grid::clear(newPosition);

    while (!Mechanics::collidesObject(p_piece))
    {
        oldPosition = newPosition;
        newPosition = p_piece->translate(DOWN);
    }

    undo();

    Mechanics::ground(p_piece);

    p_piece->swap();
}

void DropCommand::undo()
{
    p_piece->setPosition(oldPosition);
}
