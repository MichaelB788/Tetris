#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include "Commands/Command.hpp"
#include "../../Game/Objects/Piece.hpp"

/*
 * A class which handles events from the keyboard and manipulates
 * the Player object outside of its scope through a pointer.
 * */
class EventHandler 
{
    Piece& p_piece;

    Command* keydown(SDL_Event event);

public:
    EventHandler(Piece& piece) : p_piece(piece) {}

    void processInput(SDL_Event event);

};

#endif
