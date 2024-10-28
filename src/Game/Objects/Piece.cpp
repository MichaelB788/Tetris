#include <array>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include "Coordinate.hpp"
#include "Piece.hpp"
#include "Mechanics.hpp"

char _types[7] = {'I', 'O', 'T', 'S', 'Z', 'L', 'J'};

Piece::Piece(char type) :
    m_newCoordinates(Mechanics::giveNewPiece(type)), m_type(type) {}

Piece::Piece() 
{
    srand(time(0));
    m_type = _types[rand() % 7];
    m_newCoordinates = Mechanics::giveNewPiece(m_type);
};

bool Piece::positionIsValid(std::array<Point, 4> coordinates)
{
    if (Mechanics::Collision::collidesWall(coordinates)){
        return false;
    }
    else if (Mechanics::Collision::collidesFloor(coordinates)){
        release();
        return false;
    }

    return true;
}

void Piece::release()
{
    srand(time(0));
    m_type = _types[rand() % 7];
    std::array<Point, 4> newPiece = Mechanics::giveNewPiece(m_type);
    m_oldCoordinates = newPiece;
}

void Piece::move(Direction dir)
{
    m_oldCoordinates = m_newCoordinates;

    switch (dir)
    {
        case LEFT:
            for (Point& point : m_newCoordinates)
                point.translateX(-1);
            break;
        case RIGHT:
            for (Point& point : m_newCoordinates)
                point.translateX(1);
            break;
        case DOWN:
            for (Point& point : m_newCoordinates)
                point.translateY(1);
            break;
        default:
            break;
    }

    if (!positionIsValid(m_newCoordinates))
        m_newCoordinates = m_oldCoordinates;
}

std::array<Point, 4> Piece::getNewCoordinates() { return m_newCoordinates; }

std::array<Point, 4> Piece::getOldCoordinates() { return m_oldCoordinates; }

char Piece::getType() { return m_type; }
