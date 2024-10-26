#ifndef GRID_H
#define GRID_H

#include "Coordinate.hpp"

namespace Grid 
{
    char at(int x, int y);

    char at(Point point);

    void set(int x, int y, char newElement);

    void set(Point point, char newElement);

    void clear();
} 

#endif 
