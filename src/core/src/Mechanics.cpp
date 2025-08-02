#include "Mechanics.hpp"

#include <array>
#include <locale>
#include <stdexcept>

#include "../Components/Event/Commands/Move.hpp"

#include "Objects/Coordinate.hpp"
#include "Objects/Grid.hpp"
#include "Objects/Piece.hpp"

std::array<Point, 4> Mechanics::giveNewPiece(Tile type)
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
        case I:
            return {Point(5, 2), Point(5, 1), Point(5, 3), Point(5, 4)};
        case O:
            return {Point(5, 1), Point(6, 1), Point(5, 2), Point(6, 2)};
        case T:
            return {Point(5, 1), Point(4, 1), Point(6, 1), Point(5, 2)};
        case S:
            return {Point(5, 2), Point(4, 2), Point(5, 1), Point(6, 1)};
        case Z:
            return {Point(5, 2), Point(4, 1), Point(5, 1), Point(6, 2)};
        case L:
            return {Point(5, 2), Point(5, 1), Point(5, 3), Point(6, 3)};
        case J:
            return {Point(6, 2), Point(6, 1), Point(6, 3), Point(5, 3)};
        default: 
            throw std::invalid_argument("Did not recieve valid Tile value");
    }
}

Tile Mechanics::assignTile()
{
    srand(time(0)); // Seed with current time
    return Tile(rand() % 7);
}

bool Mechanics::collidesObject(Piece target)
{
    for (Point& p : target.position())
    {
        char currTile = Grid::tileAt(p);

        if (currTile != _ &&
            currTile != target.type())  
            return true;
    }

    return false;
}

void Mechanics::ground(Piece target)
{
    Tile groundedTile = Tile(target.type() + 7);

    for (Point& p: target.position())
        Grid::set(p, groundedTile); 
}

void Mechanics::invokeGravity(Piece& piece,
                              unsigned int time,
                              Difficulty &difficulty)
{
    if (time % difficulty == 0)
        MoveCommand(piece, DOWN).execute();
}

void Mechanics::checkFullRow(unsigned int &points)
{
    for (int row = 0; row < 22; row++)
    {
        if (Grid::hasFullRow(row))
        { 
            Grid::clear(row);
            points++;   
        }
    }
}
