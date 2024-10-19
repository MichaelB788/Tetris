#ifndef BOARD_H
#define BOARD_H

#include "Coordinate.hpp"

typedef struct Board
{
    Board() = default;

    char at(int row, int col);

    char at(Coordinate::Point c);

    void modifyAt(int row, int col, char newElement);

    void modifyAt(Coordinate::Point c, char newElement);

    void clearRow(int row);

    void clearBoard();

    void shiftRow(int row, int position);
} Board;

#endif
