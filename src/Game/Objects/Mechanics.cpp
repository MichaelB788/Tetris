#include "Mechanics.hpp"

#include <array>
#include <iostream>
#include <locale>

#include "Coordinate.hpp"
#include "Grid.hpp"
#include "Piece.hpp"

std::array<Point, 4> Mechanics::giveNewPiece(char type)
{
    /*
     * Each shape is represented by an array of four Points
     *
     * The first Point in the array is the point of rotation, 
     * or the origin point
     *  
     * */
    switch (type)
    {
        case 'I':
            return {Point(5, 2), Point(5, 1), Point(5, 3), Point(5, 4)};
        case 'O':
            return {Point(5, 1), Point(6, 1), Point(5, 2), Point(6, 2)};
        case 'T':
            return {Point(5, 1), Point(4, 1), Point(6, 1), Point(5, 2)};
        case 'S':
            return {Point(5, 2), Point(4, 2), Point(5, 1), Point(6, 1)};
        case 'Z':
            return {Point(5, 2), Point(4, 1), Point(5, 1), Point(6, 2)};
        case 'L':
            return {Point(5, 2), Point(5, 1), Point(5, 3), Point(6, 3)};
        case 'J':
            return {Point(6, 2), Point(6, 1), Point(6, 3), Point(5, 3)};
        default: {
            Grid::printGrid();
            std::cerr << "Unkown char given to Mechanics::giveNewPiece(char type): " << type << std::endl;
            throw;
        }
    }
}

bool Mechanics::collidesObject(Piece* target)
{
    for (Point& p : target->position())
    {
        char currTile = Grid::tileAt(p);

        if (currTile != '#' &&
            currTile != target->type())  
            return true;
    }

    return false;
}

void Mechanics::ground(Piece* target)
{
    for (Point& p: target->position())
        Grid::set(p, std::tolower(target->type(),
                                  std::locale())); 
}
