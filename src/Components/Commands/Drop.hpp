#ifndef DROP_H
#define DROP_H

#include "Command.hpp"
#include "../../Game/Objects/Piece.hpp"
#include <array>

struct DropCommand : public Command 
{
    DropCommand(Piece* piece) :
        p_piece(piece), 
        newPosition(piece->position())
    {}

    void execute() override;

    void undo() override;

    void display() override;
    
private:
    Piece* p_piece;

    std::array<Point, 4> oldPosition;

    std::array<Point, 4> newPosition;
};

#endif
