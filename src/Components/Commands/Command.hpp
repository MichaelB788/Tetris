#ifndef COMMAND_H
#define COMMAND_H

#include "../../Game/Objects/Piece.hpp"
struct Command 
{
    virtual ~Command() {};

    virtual void execute() = 0;

    virtual void undo() = 0;

private:
    Piece* p_piece;
};

#endif
