#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <SDL2/SDL.h>
#include "../Game/Objects/TetrisBoard.hpp"

typedef struct EventHandler 
{
    EventHandler(TetrisBoard::Piece *piece, bool &gameState);

    void setTargetPiece(TetrisBoard::Piece *newPiece);

    void processInput();

    void keydown();

    void keyup();

private:
    SDL_Event event_;

    TetrisBoard::Piece *target_ = nullptr;

    bool &gameState_;
} EventHandler;

#endif
