#ifndef MOVE_H
#define MOVE_H

#include "Command.hpp"
#include "../../Game/Objects/Piece.hpp"
#include <array>

struct MoveCommand : public Command 
{
    MoveCommand(Piece* piece, Direction direction) :
        p_piece(piece), 
        m_direction(direction),
        newPosition(piece->position())
    {}

    void execute() override;

    void undo() override;

    void display() override;

    void ground();
    
private:
    Piece* p_piece;
            
    Direction m_direction;

    std::array<Point, 4> oldPosition;

    std::array<Point, 4> newPosition;
};

#endif
