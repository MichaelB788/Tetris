#include <SDL2/SDL.h>

#include "EventHandler.hpp"
#include "../Game/Piece.hpp"

void EventHandler::process(SDL_Event event, bool gameState)
{
    while (SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                gameState = false;
            case SDL_KEYDOWN:
                // keydown(event);
                break;
            case SDL_KEYUP:
                // keyup(event);
                break;
            default:
                break;
        }
    }
}

void EventHandler::keydown(SDL_Event event)
{
    // Handle event.key.keysym.sym on key down
    switch (event.key.keysym.sym)
    {
        // TODO: Get the enums working. Needs to be global maybe?
        case SDLK_h:
            // Piece::move(Piece::Direction::RIGHT);  
            break;
        case SDLK_k:
            // Piece::move(LEFT);
            break;
        case SDLK_SPACE:
            // Piece::forceDrop();
            break;
        default:
            break;
    }
}

void EventHandler::keyup(SDL_Event event)
{
    // Handle event.key.keysym.sym on key up
    switch (event.key.keysym.sym)
    {
        case SDLK_h:
            break;
        case SDLK_k:
            break;
        case SDLK_SPACE:
            break;
        default:
            break;
    }
}
