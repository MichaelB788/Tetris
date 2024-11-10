#include "EventHandler.hpp"

#include <SDL2/SDL.h>
#include <cstdio>
#include "../Game/Objects/Piece.hpp"
#include "../Game/Player.hpp"

EventHandler::EventHandler(Player* player, bool& gameState) :
    p_player(player), m_gameState(gameState){}

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
            p_player->move(LEFT);
            break;
        case SDLK_l:
        case SDLK_d:
            p_player->move(RIGHT);
            break;
        case SDLK_j:
        case SDLK_s:
            p_player->move(DOWN);
            break;
        case SDLK_SPACE:
            break;
        default:
            break;
    }
}
