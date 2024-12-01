#include <array>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <locale>

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
    m_direction = dir;

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
            m_direction = NONE;
            break;
    }
}

void Piece::revert()
{
    m_curr = m_prev;
}

void Piece::swap()
{
    for (Point& point : m_prev)
        Grid::set(point, std::tolower(m_type, std::locale()));

    srand(time(0));
    m_type = _types[rand() % 7];
    m_prev = Mechanics::giveNewPiece(m_type);
}

void Piece::modifyGrid()
{
    for (Point& point : m_prev) Grid::set(point, '#');
    for (Point& point : m_curr) Grid::set(point, m_type);
}

const char Piece::type() { return m_type; }

const Direction Piece::direction() { return m_direction; }

std::array<Point, 4> Piece::getCurrArray() 
{
    return m_curr;
}

std::array<Point, 4> Piece::getPrevArray()
{
    return m_prev;
}
