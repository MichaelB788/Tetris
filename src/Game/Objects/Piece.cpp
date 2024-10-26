#include <array>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include "Coordinate.hpp"
#include "Piece.hpp"
#include "Logic.hpp"

char _types[7] = {'I', 'O', 'T', 'S', 'Z', 'L', 'J'};

Piece::Piece(char type) :
    m_newCoordinates(Logic::giveNewPiece(type)), m_type(type) {}

Piece::Piece() 
{
    srand(time(0));
    m_type = _types[rand() % 7];
    m_newCoordinates = Logic::giveNewPiece(m_type);
};

void Piece::move(Direction dir)
{
    if (Logic::positionIsValid(m_newCoordinates))
    {
        m_oldCoordinates = m_newCoordinates;
        switch (dir)
        {
            case LEFT:
                for (auto &_point : m_newCoordinates)
                _point.translateX(-1);
                break;
            case RIGHT:
                for (int i = 0; i < 4; i++)
                    m_newCoordinates.at(i).translateX(1);
                break;
            case DOWN:
                for (int i = 0; i < 4; i++)
                    m_newCoordinates.at(i).translateY(1);
                break;
            default:
                break;
        }
    }
}

std::array<Point, 4> Piece::getNewCoordinates() const 
{
    std::array<Point, 4> _coordinates;

    for (int i = 0; i < 4; i++)
        _coordinates[i] = m_newCoordinates[i];

    return _coordinates;
}

std::array<Point, 4> Piece::getOldCoordinates() const 
{
    std::array<Point, 4> _coordinates;

    for (int i = 0; i < 4; i++)
        _coordinates[i] = m_oldCoordinates[i];

    return _coordinates;
}

char Piece::getType() const
{
    return m_type;
}
