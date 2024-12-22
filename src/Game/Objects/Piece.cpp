#include <array>
#include <cctype>
#include <cstdlib>
#include <ctime>

#include "Coordinate.hpp"
#include "Grid.hpp"
#include "Piece.hpp"
#include "Mechanics.hpp"

char _types[7] = {'I', 'O', 'T', 'S', 'Z', 'L', 'J'};

Piece::Piece() 
{
    srand(time(0));
    m_type = _types[rand() % 7];
    m_position = Mechanics::giveNewPiece(m_type);
};

std::array<Point, 4> Piece::translate(Direction dir)
{
    for (Point& point : m_position) 
    {
        switch (dir)
        {
            case LEFT:
                point.translateX(-1);
                break;
            case RIGHT:
                point.translateX(1);
                break;
            case DOWN:
                point.translateY(1);
                break;
            default:
                break;
        }
    }
    
    return m_position;
}

std::array<Point, 4> Piece::rotate()
{
    Point origin = m_position[0];

    for (int i = 1; i < 4; i++) 
        m_position[i].rotate270(origin);
    
    return m_position;
}

void Piece::draw()
{
    for (Point& point : m_position)
        Grid::set(point, m_type);
}

std::array<Point, 4> Piece::swap()
{
    srand(time(0));
    m_type = _types[rand() % 7];
    m_position = Mechanics::giveNewPiece(m_type);

    return m_position;
}
