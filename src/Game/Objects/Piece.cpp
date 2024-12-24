#include <array>
#include <cctype>
#include <cstdlib>
#include <ctime>

#include "Coordinate.hpp"
#include "Grid.hpp"
#include "Piece.hpp"
#include "Mechanics.hpp"

Piece::Piece(Tile type) : 
    m_type(type),
    m_next(Mechanics::assignTile()),
    m_position(Mechanics::giveNewPiece(type))
{}

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

void Piece::swap()
{
    m_type = m_next;
    m_next = Mechanics::assignTile();

    m_position = Mechanics::giveNewPiece(m_type);
}

void Piece::store()
{
    if (m_stored == NIL) {
        // Store the current piece and swap it with a new one
        m_stored = m_type;
        m_type = m_next;
        m_next = Mechanics::assignTile();
    }
    else {
        // Swap the current piece with the one stored
        Tile temp = m_type;
        m_type = m_stored;
        m_stored = temp;
    }

    m_position = Mechanics::giveNewPiece(m_type);
}
