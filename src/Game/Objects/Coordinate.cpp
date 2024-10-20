#include <array>

#include "Coordinate.hpp"

/*
 * Coordinate::Point is a simple wrapper around an std::array of size 2, 
 * notably named pair to suggest a coordinate pair.
 *
 * pair[0] represents the x value, while pair[1] represents the y value.
 *
 * */

Point::Point()
{
    pair_ = {0, 0};
}

Point::Point(std::array<int, 2> pair)
{
    pair_ = pair;
}

Point::Point(int x, int y)
{
    pair_ = {x, y};
}

Point::Point(Point &other)
{
    pair_ = {other.getX(), other.getY()}; 
}

Point Point::getPoint()
{
    return Point(pair_);
}

int const Point::getX()
{
    return pair_[0];
}

int const Point::getY()
{
    return pair_[1];
}

void Point::translateX(int amount)
{
    pair_[0] += amount;
}

void Point::translateY(int amount)
{
    pair_[1] += amount;
}
