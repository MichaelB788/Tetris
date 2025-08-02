#ifndef COORDINATE_H
#define COORDINATE_H

typedef struct Point
{
private:
    int m_x, m_y;

public:
    // Constructors
    Point() : m_x(0), m_y(0) {};

    Point(int x, int y) : m_x(x), m_y(y) {};

    Point(Point &other) : m_x(other.m_x),
        m_y(other.m_y) {};

    // Methods
    void translateX(int amount);

    void translateY(int amount);

    void rotate270(Point origin);

    // Getters
    Point getPoint() { return Point(m_x, m_y); }

    int const getX() { return m_x; }

    int const getY() { return m_y; }
} Point;

#endif 
