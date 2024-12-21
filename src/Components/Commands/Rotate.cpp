#include "Rotate.hpp"
#include "../../Game/Objects/Grid.hpp"

void RotateCommand::execute()
{
    oldPosition = newPosition;
    newPosition = p_piece->rotate();

    display();
}

void RotateCommand::undo()
{
    p_piece->setPosition(oldPosition);
}

void RotateCommand::display()
{
    for (Point& point : oldPosition)
        Grid::set(point, '#');

    for (Point& point : newPosition)
        Grid::set(point, p_piece->type());
}
