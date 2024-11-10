#ifndef COORDINATE_H
#define COORDINATE_H

typedef struct Point
{
private:
    int m_x, m_y;

public:
    Point();

    Point(int x, int y);

    Point(Point &other);

    Point getPoint();

    int const getX();

    int const getY();

    void translateX(int amount);

    void translateY(int amount);

    bool equals(Point other);

    bool equals(int x, int y);
} Point;

#endif 
