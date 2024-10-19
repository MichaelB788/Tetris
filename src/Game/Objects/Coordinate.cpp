#include <array>

#include "Coordinate.hpp"

/*
 * Coordinate::Point is a simple wrapper around an std::array of size 2, 
 * notably named pair to suggest a coordinate pair.
 *
 * pair[0] represents the x value, while pair[1] represents the y value.
 *
 * */

Coordinate::Point::Point()
{
    pair = {0, 0};
}

Coordinate::Point::Point(std::array<int, 2> pair)
{
    pair = pair;
}

std::array<int, 2> Coordinate::Point::getPoint()
{
    return pair;
}

int Coordinate::Point::getX()
{
    return pair[0];
}

int Coordinate::Point::getY()
{
    return pair[1];
}

void Coordinate::Point::translateX(int amount)
{
    pair[0] += amount;
}

void Coordinate::Point::translateY(int amount)
{
    pair[1] += amount;
}

/*
 * Coordinate::FourPoint is a simple wrapper around a 2D array, where 
 * the inner array is of size 2 (Coordinate::Point) and the outer array 
 * is of size four. This is very useful in a game inspired by Tetris.
 *
 * Because FourPoints consists of four Coordinate::Point, it's best to
 * use functions from Coordinate::Point to modify FourPoints through a
 * loop
 *
 * */

Coordinate::FourPoints::FourPoints()
{
    fourPairs = {Point(), Point(), Point(), Point()};
}

Coordinate::FourPoints::FourPoints(Point p1, Point p2, Point p3, Point p4)
{
    fourPairs = {p1.getPoint(), p2.getPoint(), p3.getPoint(), p4.getPoint()};
}

Coordinate::FourPoints::FourPoints(std::array<std::array<int, 2>, 4> arrayOfArrays)
{
    Point p1, p2, p3, p4;

    p1 = arrayOfArrays[0];
    p2 = arrayOfArrays[1];
    p3 = arrayOfArrays[2];
    p4 = arrayOfArrays[3];

    fourPairs = {p1, p2, p3, p4};
}

std::array<Coordinate::Point, 4> Coordinate::FourPoints::getFourPoints()
{
    return fourPairs;
}

/*
 * The functions below serve to return special instances of Point or 
 * FourPoint
 *
 * */

Coordinate::FourPoints Coordinate::getNeighborsAt(std::array<int, 2> point)
{
    int x = point[0];
    int y = point[1];

    return FourPoints({{{++x, y}, {--x, y}, {x, ++y}, {x, --y}}});
}

Coordinate::FourPoints Coordinate::getNeighborsAt(Point point)
{
    int x = point.getPoint()[0];
    int y = point.getPoint()[1];

    return FourPoints({{{++x, y}, {--x, y}, {x, ++y}, {x, --y}}});
}
