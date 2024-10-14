#include <array>
#include "Coordinate.hpp"

Coordinate::FourPoints::FourPoints()
{
    fourPairs = {{{0, 0}, {0, 0}, {0, 0}, {0, 0}}};
}

Coordinate::FourPoints::FourPoints(std::array<std::array<int, 2>, 4> coordinates)
{
    fourPairs = coordinates;
}

std::array<std::array<int, 2>, 4> Coordinate::FourPoints::getFourPoints()
{
    return fourPairs;
}

std::array<int, 2> Coordinate::FourPoints::getPointFrom(int index)
{
    return fourPairs[index];
}

int Coordinate::FourPoints::getX_fromPoint(int index)
{
    return fourPairs[index][0];
}

int Coordinate::FourPoints::getY_fromPoint(int index)
{
    return fourPairs[index][1];
}
