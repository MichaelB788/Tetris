#include <SDL2/SDL.h>
#include <cstdio>

#include "EventHandler.hpp"
#include "../Game/Objects/TetrisBoard.hpp"

EventHandler::EventHandler(TetrisBoard::Piece *piece, bool &gameState) :
    target_(piece), gameState_(gameState){}

void EventHandler::setTargetPiece(TetrisBoard::Piece *newPiece)
{
    target_ = newPiece;
}

void EventHandler::processInput()
{
    while (SDL_PollEvent(&event_))
    {
        switch(event_.type)
        {
            case SDL_QUIT:
                gameState_ = false;
            case SDL_KEYDOWN:
                keydown();
                break;
            case SDL_KEYUP:
                // keyup(event);
                break;
            default:
                break;
        }
    }
}

void EventHandler::keydown()
{
    // Handle event.key.keysym.sym on key down
    switch (event_.key.keysym.sym)
    {
        case SDLK_h:
        case SDLK_a:
            target_->move(LEFT);
            break;
        case SDLK_l:
        case SDLK_d:
            target_->move(RIGHT);
            break;
        case SDLK_j:
        case SDLK_s:
            target_->move(DOWN);
            break;
        case SDLK_SPACE:
            break;
        default:
            break;
    }
}

void EventHandler::keyup()
{
    // Handle event.key.keysym.sym on key up
    switch (event_.key.keysym.sym)
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
