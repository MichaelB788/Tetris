#ifndef COMMAND_H
#define COMMAND_H

struct Command 
{
    virtual ~Command() {};

    virtual void execute() = 0;

    virtual void undo() = 0;
};

#endif
