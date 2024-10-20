#ifndef BOARD_H
#define BOARD_H

#include "Coordinate.hpp"
#include <array>

namespace TetrisBoard
{ 
    enum Direction { LEFT, RIGHT, DOWN };

    typedef struct Piece
    {
        Piece(char type);

        Piece();

        void updatePosition();

        void move(Direction dir);

    private:
        std::array<Point, 4> coordinates_;
        char type_;

    } Piece;

    namespace Grid
    {
        char const at(int row, int col);

        char const at(Point c);

        void set(int row, int col, char newElement);

        void set(Point c, char newElement);
    }
}

#endif
