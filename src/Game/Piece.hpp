#ifndef BLOCK_H
#define BLOCK_H

#include <vector>

#include "Board.hpp"

class Piece
{
    public:
        Piece(char type);

        void moveDown();

        void moveRight();

        void moveLeft();

        bool isValidPosition();
        
        char getID();
};

#endif
