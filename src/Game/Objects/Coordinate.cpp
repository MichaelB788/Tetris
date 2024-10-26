#include "Coordinate.hpp"

Point::Point()
{
    m_x = 0;
    m_y = 0;
}

Point::Point(int x, int y)
{
    m_x = x;
    m_y = y;
}

Point::Point(Point &other)
{
    m_x = other.getX();
    m_y = other.getY();
}

Point Point::getPoint()
{
    return Point(m_x, m_y);
}

int const Point::getX() 
{
    return m_x;
}

int const Point::getY()
{
    return m_y;
}

void Point::translateX(int amount)
{
    m_x += amount;
}

void Point::translateY(int amount)
{
    m_y += amount;
}
