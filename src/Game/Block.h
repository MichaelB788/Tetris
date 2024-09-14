#ifndef BLOCK_H
#define BLOCK_H

#include "CoordinatePoint.h"
class Block
{
    private:
        void createBlockI();

        void createBlockO();

        void createBlockT();

        void createBlockS();

        void createBlockZ();

        void createBlockL();

        void createBlockJ();

    public:
        Block(char type);

        void moveDown();

        void moveRight();

        void moveLeft();

        bool isValidPosition();

};

#endif
