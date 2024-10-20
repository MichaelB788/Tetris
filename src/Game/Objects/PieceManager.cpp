#include "PieceManager.hpp"

#include <array>
#include <stdexcept>
#include "Coordinate.hpp"
#include "TetrisBoard.hpp"

std::array<Point, 4> PieceManager::giveNewPiece(char type)
{
    switch (type) {
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

bool PieceManager::positionIsValid(std::array<Point, 4> &coordinates)
{
    for (Point point : coordinates)
    {
        int x = point.getX();
        int y = point.getY();

        if (TetrisBoard::Grid::at(--x, y) != '#' &&
            TetrisBoard::Grid::at(++x, y) != '#')
        {
            return false;
        }
    }

    return true;
}

void PieceManager::releaseCurrentPiece()
{
}

