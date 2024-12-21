#ifndef ROTATE_H
#define ROTATE_H

#include "Command.hpp"
#include "../../Game/Objects/Piece.hpp"
#include <array>

struct RotateCommand : public Command
{
    RotateCommand(Piece* piece) :
        p_piece(piece), 
        newPosition(piece->position())
    {}

    void execute() override;

    void undo() override;

    void display() override;
    
private:
    Piece* p_piece;
    
    std::array<Point, 4> newPosition;

    std::array<Point, 4> oldPosition;
};

#endif
