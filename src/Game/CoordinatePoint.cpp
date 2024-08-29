#include "CoordinatePoint.h"

// macro
#define TILE 20

// private
int posx;
int posy;

// public
CoordinatePoint::CoordinatePoint(int x, int y)
{
    posx = x;
    posy = y;
}

CoordinatePoint CoordinatePoint::getCoordinates()
{
    CoordinatePoint newPoint = CoordinatePoint(posx, posy);
    return newPoint;
}

int CoordinatePoint::getX()
{
    return posx;
}

int CoordinatePoint::getY()
{
    return posy;
}

void CoordinatePoint::shiftX(int amount)
{
    posx += amount * TILE;
}

void CoordinatePoint::shiftY(int amount)
{
    posy += amount * TILE;
}
