#ifndef COORDINATE_H
#define COORDINATE_H

#include <array>
namespace Coordinate
{
    typedef struct Point
    {
        Point();

        Point(std::array<int, 2>);

        std::array<int, 2> getPoint();

        int getX();

        int getY();

        void translateX(int amount);

        void translateY(int amount);

        private:
        std::array<int, 2> pair;
    } Point;

    typedef struct FourPoints
    {
        FourPoints();

        FourPoints(Point p1, Point p2, Point p3, Point p4);

        FourPoints(std::array<std::array<int, 2>, 4> arrayOfArrays);

        std::array<Point, 4> getFourPoints();
        
        private:
        std::array<Point, 4> fourPairs;  
    } FourPoints;

    FourPoints getNeighborsAt(std::array<int, 2> point);

    FourPoints getNeighborsAt(Point point);
}

#endif 
