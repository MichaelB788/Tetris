#include "EventHandler.hpp"

#include <SDL2/SDL.h>
#include <cstdio>
#include "../Game/Objects/Piece.hpp"

EventHandler::EventHandler(Piece* piece, bool& gameState) :
    m_target(piece), m_gameState(gameState){}

void EventHandler::setTargetPiece(Piece *newPiece)
{
    m_target = newPiece;
}

void EventHandler::processInput()
{
    while (SDL_PollEvent(&m_event))
    {
        switch(m_event.type)
        {
            case SDL_QUIT:
                m_gameState = false;
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
    switch (m_event.key.keysym.sym)
    {
        case SDLK_h:
        case SDLK_a:
            m_target->move(LEFT);
            break;
        case SDLK_l:
        case SDLK_d:
            m_target->move(RIGHT);
            break;
        case SDLK_j:
        case SDLK_s:
            m_target->move(DOWN);
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
    switch (m_event.key.keysym.sym)
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
