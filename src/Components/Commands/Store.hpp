#ifndef STORE_H
#define STORE_H

#include "Command.hpp"
#include "../../Game/Objects/Piece.hpp"

struct StoreCommand : public Command
{
    StoreCommand(Piece* piece) :
        p_piece(piece), 
        oldPosition(piece->position())
    {}

    void execute() override;

    void undo() override {};
    
private:
    Piece* p_piece;
            
    std::array<Point, 4> oldPosition;
};

#endif 
