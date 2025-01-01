#ifndef CONTEXT_H
#define CONTEXT_H

#include "../api/sdl/Renderer.hpp"
#include "../Game/Objects/Piece.hpp"
#include "Event/EventHandler.hpp"
#include "Visual/Graphics.hpp"

struct Context
{
    Context(Renderer& renderer, Piece& piece);

    Graphics m_graphics;

    EventHandler m_handler;
};

#endif 
