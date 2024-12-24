#include "EventHandler.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include "Commands/Command.hpp"
#include "Commands/Move.hpp"
#include "Commands/Rotate.hpp"
#include "Commands/Drop.hpp"
#include "Commands/Store.hpp"

void EventHandler::processInput()
{
    while (SDL_PollEvent(&m_event))
    {
        switch(m_event.type)
        {
            case SDL_QUIT:
                m_gameState = false;
            case SDL_KEYDOWN: {
                Command* command = keydown();
                if (command) command->execute();
                delete command;
                break;
            }
            default:
                break;
        }
    }
}

Command* EventHandler::keydown()
{
    // Handle event.key.keysym.sym on key down
    switch (m_event.key.keysym.sym)
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
