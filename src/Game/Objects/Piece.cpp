#include <array>
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
    m_curr = Mechanics::giveNewPiece(m_type);
    m_prev = m_curr;
};

void Piece::translate(Direction dir)
{
    m_prev = m_curr;

    switch (dir)
    {
        case LEFT:
            for (Point& point : m_curr)
            point.translateX(-1);
            break;
        case RIGHT:
            for (Point& point : m_curr)
            point.translateX(1);
            break;
        case DOWN:
            for (Point& point : m_curr)
            point.translateY(1);
            break;
        default:
            break;
    }
}

void Piece::revert()
{
    m_curr = m_prev;
}

void Piece::swap()
{
    srand(time(0));
    m_type = _types[rand() % 7];
    m_prev = Mechanics::giveNewPiece(m_type);
}

bool Piece::compare(char tile)
{
    for (Point& point : m_curr)
    {
        char currTile = Grid::at(point.getX(), point.getY());
        if (currTile == tile) return true;
    }

    return false;
}

bool Piece::contains(Point otherPoint)
{
    bool result = false;

    for (int i = 0; i < 4; i++)
    {
        if (otherPoint.equals(m_curr[i]))
            result = true;
    }

    return result;
}

void Piece::modifyGrid()
{
    for (Point& point : m_prev) Grid::set(point, '#');

    for (Point& point : m_curr) Grid::set(point, m_type);
}
