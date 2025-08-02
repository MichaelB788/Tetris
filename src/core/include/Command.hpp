#ifndef COMMAND_H
#define COMMAND_H
#include "array"

struct Command 
{
    virtual ~Command() {};

    virtual void execute() = 0;

    virtual void undo() = 0;
};

struct MoveCommand : public Command 
{
    MoveCommand(Piece& piece, Direction direction) :
        p_piece(piece), 
        m_direction(direction),
        oldPosition(piece.position())
    {}

    void execute() override;

    void undo() override;
    
private:
    Piece& p_piece;
            
    Direction m_direction;

    std::array<Point, 4> oldPosition;

    std::array<Point, 4> newPosition;

    void enforceCollision();
};

struct RotateCommand : public Command
{
    RotateCommand(Piece& piece) :
        p_piece(piece), 
        newPosition(piece.position())
    {}

    void execute() override;

    void undo() override;

private:
    Piece& p_piece;
    
    std::array<Point, 4> newPosition;

    std::array<Point, 4> oldPosition;
};

struct StoreCommand : public Command
{
    StoreCommand(Piece& piece) :
        p_piece(piece), 
        oldPosition(piece.position())
    {}

    void execute() override;

    void undo() override {};
    
private:
    Piece& p_piece;
            
    std::array<Point, 4> oldPosition;
};

struct DropCommand : public Command 
{
    DropCommand(Piece& piece) :
        p_piece(piece), 
        newPosition(piece.position())
    {}

    void execute() override;

    void undo() override;

private:
    Piece& p_piece;

    std::array<Point, 4> oldPosition;

    std::array<Point, 4> newPosition;
};

#endif
