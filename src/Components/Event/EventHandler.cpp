#include "EventHandler.hpp"

#include <SDL2/SDL.h>
#include "Commands/Command.hpp"
#include "Commands/Move.hpp"
#include "Commands/Rotate.hpp"
#include "Commands/Drop.hpp"
#include "Commands/Store.hpp"

void EventHandler::processInput(SDL_Event event)
{
    if (event.type == SDL_KEYDOWN)
    {
        Command* command = keydown(event);
        if (command) command->execute();
        delete command;
    }
}

Command* EventHandler::keydown(SDL_Event event)
{
    // Handle event.key.keysym.sym on key down
    switch (event.key.keysym.sym)
    {
        case SDLK_j:
            return new MoveCommand(p_piece, LEFT);
        case SDLK_k:
            return new MoveCommand(p_piece, DOWN);
        case SDLK_l:
            return new MoveCommand(p_piece, RIGHT);
        case SDLK_s:
            return new StoreCommand(p_piece);
        case SDLK_d:
            return new DropCommand(p_piece);
        case SDLK_r:
            return new RotateCommand(p_piece);
        case SDLK_SPACE:
            return new DropCommand(p_piece);
        default:
            return NULL;
    }
}
