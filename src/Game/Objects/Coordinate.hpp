#ifndef COORDINATE_H
#define COORDINATE_H

#include <array>

typedef struct Point
{
    Point();

    Point(std::array<int, 2> pair);

    Point(int x, int y);

    Point(Point &other);

    Point getPoint();

    int const getX();

    int const getY();

    void translateX(int amount);

    void translateY(int amount);

private:
    std::array<int, 2> pair_;
} Point;

#endif 
