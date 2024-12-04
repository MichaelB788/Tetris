#ifndef GRID_H
#define GRID_H

#include "Coordinate.hpp"

namespace Grid 
{
    char at(unsigned int x, unsigned int y);

    char at(Point point);

    void set(unsigned int x, unsigned int y, char newElement);

    void set(Point point, char newElement);

    void clear();

    void clear(unsigned int row);

    bool hasFullRow(unsigned int row);

    void printGrid();
} 

#endif 
