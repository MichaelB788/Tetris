#include "Mechanics.hpp"

#include <array>
#include <cstdio>
#include <cstdlib>
#include <stdexcept>
#include "Coordinate.hpp"
#include "Grid.hpp"

std::array<Point, 4> Mechanics::giveNewPiece(char type)
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
            throw std::invalid_argument("Invalid type given to Logic::giveNewPiece(char type)");
    }
}

bool Mechanics::Collision::collidesWall(std::array<Point, 4> target)
{
    for (Point& point : target){
        char curr = Grid::at(point.getX(), point.getY());
        if (curr == '|') return true;
    }

    return false;
}

bool Mechanics::Collision::collidesFloor(std::array<Point, 4> target)
{
    for (Point& point : target){
        char curr = Grid::at(point.getX(), point.getY());
        if (curr == '_') return true;
    }

    return false;
}
