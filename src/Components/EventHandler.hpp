#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <SDL2/SDL.h>
#include "../Game/Objects/Piece.hpp"

/*
 * A class which handles events from the keyboard and manipulates
 * TetrisBoard::Piece objects outside of its scope through a pointer.
 * */
typedef class EventHandler 
{
    SDL_Event m_event;

    Piece* m_target = nullptr;

    bool& m_gameState;

    void keydown();

    void keyup();

public:
    EventHandler(Piece* piece, bool& gameState);

    void setTargetPiece(Piece* newPiece);

    void processInput();

} EventHandler;

#endif
