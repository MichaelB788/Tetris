#ifndef BOARD_H
#define BOARD_H

#include <array>

namespace Board
{
    extern std::array<std::array<char, 10>, 20> board_state;

    void clearBoard();
}

#endif
