#include <cmath> 
#include "Coordinate.hpp"

void Point::translateX(int amount)
{
    m_x += amount;
}

void Point::translateY(int amount)
{
    m_y += amount;
}

void Point::rotate270(Point origin)
{
    int dx = m_x - origin.m_x, dy = m_y - origin.m_y;
    
    m_x = origin.m_x + dy, m_y = origin.m_y - dx;
}
