#ifndef COMMAND_H
#define COMMAND_H
#include "Tetromino.hpp"

struct Command 
{
	public:
    virtual ~Command() {};

    virtual void execute(Tetromino& TetrominoActor) = 0;
};

struct MoveCommand : public Command 
{
    void execute(Tetromino& TetrominoActor) override;
};

struct RotateCommand : public Command
{
    void execute(Tetromino& TetrominoActor) override;
};

struct StoreCommand : public Command
{
    void execute(Tetromino& TetrominoActor) override;
};

struct DropCommand : public Command 
{
    void execute(Tetromino& TetrominoActor) override;
};

#endif
