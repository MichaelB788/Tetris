#include "Mechanics.hpp"

#include <array>
#include <stdexcept>

#include "Coordinate.hpp"
#include "Piece.hpp"

std::array<Point, 4> Mechanics::giveNewPiece(char type)
{
    switch (type) {
        case 'I':
            return {Point(5, 1), Point(5, 0), Point(5, 2), Point(5, 3)};
        case 'O':
            return {Point(5, 0), Point(6, 0), Point(5, 1), Point(6, 1)};
        case 'T':
            return {Point(5, 0), Point(4, 0), Point(6, 0), Point(5, 1)};
        case 'S':
            return {Point(5, 1), Point(4, 1), Point(5, 0), Point(6, 0)};
        case 'Z':
            return {Point(5, 1), Point(4, 0), Point(5, 0), Point(6, 1)};
        case 'L':
            return {Point(5, 1), Point(5, 0), Point(5, 2), Point(6, 2)};
        case 'J':
            return {Point(6, 1), Point(6, 0), Point(6, 2), Point(5, 2)};
        default:
            throw std::invalid_argument("Invalid type given to Logic::giveNewPiece(char type)");
    }
}

bool Mechanics::Collision::wallOrPiece(Piece& target)
{
    return target.compare('|');
}

bool Mechanics::Collision::floor(Piece& target)
{
    return target.compare('_');
}
