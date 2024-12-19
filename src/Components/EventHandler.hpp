#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <SDL2/SDL.h>
#include "Commands/Command.hpp"
#include "../Game/Objects/Piece.hpp"

/*
 * A class which handles events from the keyboard and manipulates
 * the Player object outside of its scope through a pointer.
 * */
typedef class EventHandler 
{
    SDL_Event m_event;

    Piece* p_piece;

    bool& m_gameState;

    Command* keydown();

public:
    EventHandler(Piece* piece, bool& gameState) :
        p_piece(piece), m_gameState(gameState){}

    void processInput();

} EventHandler;

#endif
