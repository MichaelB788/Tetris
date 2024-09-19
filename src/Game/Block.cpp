#include <vector>
#include <stdexcept>

#include "CoordinatePoint.h"
#include "Block.h"

using namespace std;
// A vector of size four will consist of coordinate points 
// this will represent the block objects
vector<CoordinatePoint> blockomino;
char id;

//public
Block::Block(char type)
{
    switch(type)
    {
        case 'I':
            createBlockI();
            break;
        case 'O':
            createBlockO();
            break;
        case 'T':
            createBlockT();
            break;
        case 'S':
            createBlockS();
            break;
        case 'Z':
            createBlockZ();
            break;
        case 'L':
            createBlockL();
            break;
        case 'J':
            createBlockJ();
            break;
        default:
            throw std::invalid_argument("Block type is invalid; could not create Block object.");
            break;
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

vector<CoordinatePoint> Block::getBlock()
{
    return blockomino;
}

char Block::getID()
{
    return id;
}


//private
void Block::createBlockI()
{
    id = 'I';
    blockomino = {
        CoordinatePoint(5, 20),
        CoordinatePoint(5, 19),
        CoordinatePoint(5, 18),
        CoordinatePoint(5, 17)
    };
}

void Block::createBlockO()
{
    id = 'O';
    blockomino = {
        CoordinatePoint(4, 20), CoordinatePoint(5, 20),
        CoordinatePoint(4, 19), CoordinatePoint(5, 19)
    };
}

void Block::createBlockT()
{
    id = 'T';
    blockomino = {
        CoordinatePoint(3, 20), CoordinatePoint(4, 20), CoordinatePoint(5, 20),
                                CoordinatePoint(4, 19)
    };
}

void Block::createBlockS()
{
    id = 'S';
    blockomino = {
                                CoordinatePoint(5, 20), CoordinatePoint(6, 20),
        CoordinatePoint(4, 19), CoordinatePoint(5, 19)
    };
}

void Block::createBlockZ()
{
    id = 'Z';
    blockomino = {
        CoordinatePoint(4, 20), CoordinatePoint(5, 20),
                                CoordinatePoint(5, 19), CoordinatePoint(6, 19)
    };
}

void Block::createBlockL()
{
    id = 'L';
    blockomino = {
        CoordinatePoint(5, 20),
        CoordinatePoint(5, 19),
        CoordinatePoint(5, 18), CoordinatePoint(6, 17)
    };
}

void Block::createBlockJ()
{
    id = 'J';
    blockomino = {
                                CoordinatePoint(6, 20),
                                CoordinatePoint(6, 19),
        CoordinatePoint(5, 18), CoordinatePoint(6, 17)
    };
}
