#include <vector>
#include <iostream>
#include "Block.h"

// private
int x, y;

std::vector<int> tetr; 

void Block::createBlock(int x, int y, char type)
{
    switch(type)
    {
        case 'I':
        case 'O':
        case 'T':
        case 'S':
        case 'Z':
        case 'J':
        case 'L':
        default:
            std::cout << "test" << std::endl;
    }
}

// public
Block::Block(int x, int y, char type)
{
    this -> x = x * 20;
    this -> y = y * 20;

    createBlock(x, y, type);
}

bool Block::isValidPosition()
{
    return false;
}

