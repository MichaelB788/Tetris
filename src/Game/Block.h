#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include "CoordinatePoint.h"
class Block
{
    public:
        Block(char type);

        void moveDown();

        void moveRight();

        void moveLeft();

        bool isValidPosition();

        std::vector<CoordinatePoint> getBlock();
        
        char getID();

    private:
        void createBlockI();

        void createBlockO();

        void createBlockT();

        void createBlockS();

        void createBlockZ();

        void createBlockL();

        void createBlockJ();

};

#endif
