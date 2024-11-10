#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <SDL2/SDL.h>
#include "../Game/Player.hpp"

/*
 * A class which handles events from the keyboard and manipulates
 * the Player object outside of its scope through a pointer.
 * */
typedef class EventHandler 
{
    SDL_Event m_event;

    Player* p_player = nullptr;

    bool& m_gameState;

    void keydown();

    void keyup();

public:
    EventHandler(Player* player, bool& gameState);

    void processInput();

} EventHandler;

#endif
