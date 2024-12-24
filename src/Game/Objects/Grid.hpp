#ifndef GRID_H
#define GRID_H

#include <array>

#include "Coordinate.hpp"
#include "../Tile.hpp"

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
