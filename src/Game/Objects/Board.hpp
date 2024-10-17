#ifndef BOARD_H
#define BOARD_H

#include <array>

typedef struct Board
{
    static std::array<std::array<char, 10>, 20> arrayOfArrays;
    void clearBoard();
} Board;

#endif
