#ifndef BOARD_H
#define BOARD_H

#include "Coordinate.hpp"
#include <array>

enum Direction { LEFT, RIGHT, DOWN };

typedef struct Piece
{
    Piece(char type);

    Piece();

    void move(Direction dir);

    std::array<Point, 4> getNewCoordinates();

    std::array<Point, 4> getOldCoordinates();

    char getType() const;

private:
    std::array<Point, 4> m_newCoordinates;

    std::array<Point, 4> m_oldCoordinates;

    char m_type;
} Piece;

#endif
