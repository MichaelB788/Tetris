#include "Logic.hpp"

#include <array>
#include <stdexcept>
#include "Coordinate.hpp"
#include "Grid.hpp"

std::array<Point, 4> Logic::giveNewPiece(char _type)
{
    switch (_type) {
        case 'I':
            return {Point(4, 1), Point(4, 0), Point(4, 2), Point(4, 3)};
        case 'O':
            return {Point(4, 0), Point(5, 0), Point(4, 1), Point(5, 1)};
        case 'T':
            return {Point(4, 0), Point(3, 0), Point(5, 0), Point(4, 1)};
        case 'S':
            return {Point(4, 1), Point(3, 1), Point(4, 0), Point(5, 0)};
        case 'Z':
            return {Point(4, 1), Point(3, 0), Point(4, 0), Point(5, 1)};
        case 'L':
            return {Point(4, 1), Point(4, 0), Point(4, 2), Point(5, 2)};
        case 'J':
            return {Point(5, 1), Point(5, 0), Point(5, 2), Point(4, 2)};
        default:
            throw std::invalid_argument("Invalid type given to PieceManager::giveNewPiece(char type)");
    }
}

bool Logic::positionIsValid(std::array<Point, 4> &_coordinates)
{
    for (Point& _point : _coordinates)
    {
        int x = _point.getX();
        int y = _point.getY();

        if (Grid::at(--x, y) != '#' &&
            Grid::at(++x, y) != '#')
        {
            return true;
        }
    }

    return true;
}

void Logic::releaseCurrentPiece()
{
}

