#include <vector>

#include "CoordinatePoint.h"
#include "Block.h"

using namespace std;

// A vector of size four will consist of coordinate points 
// this will represent the block objects
vector<CoordinatePoint> blockomino;

//private
void Block::createBlockI()
{
    blockomino = {
        CoordinatePoint(5, 20),
        CoordinatePoint(5, 19),
        CoordinatePoint(5, 18),
        CoordinatePoint(5, 17)
    };
}

void Block::createBlockO()
{
    blockomino = {
        CoordinatePoint(4, 20), CoordinatePoint(5, 20),
        CoordinatePoint(4, 19), CoordinatePoint(5, 19)
    };
}

void Block::createBlockT()
{
    blockomino = {
        CoordinatePoint(3, 20), CoordinatePoint(4, 20), CoordinatePoint(5, 20),
                                CoordinatePoint(4, 19)
    };
}

void Block::createBlockS()
{
    blockomino = {
                                CoordinatePoint(5, 20), CoordinatePoint(6, 20),
        CoordinatePoint(4, 19), CoordinatePoint(5, 19)
    };
}

void Block::createBlockZ()
{
    blockomino = {
        CoordinatePoint(4, 20), CoordinatePoint(5, 20),
                                CoordinatePoint(5, 19), CoordinatePoint(6, 19)
    };
}

void Block::createBlockL()
{
    blockomino = {
        CoordinatePoint(5, 20),
        CoordinatePoint(5, 19),
        CoordinatePoint(5, 18), CoordinatePoint(6, 17)
    };
}

void Block::createBlockJ()
{
    blockomino = {
                                CoordinatePoint(6, 20),
                                CoordinatePoint(6, 19),
        CoordinatePoint(5, 18), CoordinatePoint(6, 17)
    };
}


//public
Block::Block(char type)
{
    switch(type)
    {
        case 'I':
            createBlockI();
        case 'O':
            createBlockO();
        case 'T':
            createBlockT();
        case 'S':
            createBlockS();
        case 'Z':
            createBlockZ();
        case 'J':
            createBlockJ();
        case 'L':
            createBlockL();
        default:
            blockomino = {CoordinatePoint(0, 0)};
    }
} 

void Block::moveDown()
{
    if (isValidPosition())
    {
        for (auto it = blockomino.begin(); it < blockomino.end(); it++)
            it->shiftY(-1);
    }
}

void Block::moveRight()
{
    if (isValidPosition())
    {
        for (auto it = blockomino.begin(); it < blockomino.end(); it++)
            it->shiftX(1);
    }
}

void Block::moveLeft()
{
    if (isValidPosition())
    {
        for (auto it = blockomino.begin(); it < blockomino.end(); it++)
            it->shiftX(1);
    }
}

bool Block::isValidPosition()
{
    // Board is 10x20
    int boardWidth = 10 * 20;
    int boardLength = 20 * 20;

    for (auto it = blockomino.begin(); it < blockomino.end(); it++)
    {
        if (it->getX() > boardWidth || it->getY() < boardLength)
            return false;
    }
    return true;
}

