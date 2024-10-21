#ifndef BOARD_H
#define BOARD_H

#include "Coordinate.hpp"
#include <array>

enum Direction { LEFT, RIGHT, DOWN };

namespace TetrisBoard
{ 
    typedef struct Piece
    {
        Piece(char type);

        Piece();

        void updatePosition();

        void move(Direction dir);

        std::array<Point, 4> getNewCoordinates() const;

        std::array<Point, 4> getOldCoordinates() const;

        char getType() const;
        
    private:
        std::array<Point, 4> newCoordinates_;

        std::array<Point, 4> oldCoordinates_;

        char type_;
    } Piece;

    namespace Grid
    {
        char const at(int row, int col);

        char const at(Point c);

        void set(int row, int col, char newElement);

        void set(Point c, char newElement);

        void clear();
    }
}

#endif
