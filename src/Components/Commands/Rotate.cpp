#include "Rotate.hpp"
#include "../../Game/Objects/Grid.hpp"
#include "../../Game/Mechanics.hpp"

void RotateCommand::execute()
{
    oldPosition = newPosition;
    newPosition = p_piece->rotate();

    if (Mechanics::collidesObject(p_piece)) undo();
    else Grid::clear(oldPosition);
}

void RotateCommand::undo()
{
    p_piece->setPosition(oldPosition);
}
