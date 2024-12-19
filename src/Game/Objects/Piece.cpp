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
    switch (dir)
    {
        case LEFT:
            for (Point& point : m_position)
                point.translateX(-1);
            break;
        case RIGHT:
            for (Point& point : m_position)
                point.translateX(1);
            break;
        case DOWN:
            for (Point& point : m_position)
                point.translateY(1);
            break;
        default:
            break;
    }
    
    return m_position;
}

void Piece::spawn()
{
    for (Point& point : m_position)
        Grid::set(point, m_type);
}

void Piece::swap()
{
    srand(time(0));
    m_type = _types[rand() % 7];
    m_position = Mechanics::giveNewPiece(m_type);
}
