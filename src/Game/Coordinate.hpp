#ifndef COORDINATE_H
#define COORDINATE_H

#include <array>
namespace Coordinate
{
    typedef struct FourPoints
    {
        FourPoints();

        FourPoints(std::array<std::array<int, 2>, 4> coordinates);

        std::array<std::array<int, 2>, 4> getFourPoints();

        std::array<int, 2> getPointFrom(int index);

        int getX_fromPoint(int index);

        int getY_fromPoint(int index);

        private:
        std::array<std::array<int, 2>, 4> fourPairs;  
    } FourPoints;
}

#endif 
