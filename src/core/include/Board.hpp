#ifndef BOARD_H
#define BOARD_H

#include <array>
#include <array>
#include <cctype>
#include <cstdlib>
#include <ctime>

#include "Tetromino.hpp"
#include "Mechanics.hpp"
#include "GameConstants.hpp"
#include "Coordinate.hpp"

// TODO: Create a 2D array data structure
namespace Grid 
{
    Tile tileAt(unsigned int x, unsigned int y);

    Tile tileAt(Point point);

    void set(unsigned int x, unsigned int y, Tile newElement);

    void set(Point point, Tile newElement);

    void clear(unsigned int row);

    void clear(std::array<Point, 4> target);

    bool hasFullRow(unsigned int row);

    void printGrid();
} 

#endif 
