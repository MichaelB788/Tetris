#ifndef CONTEXT_H
#define CONTEXT_H

#include "../api/sdl/Renderer.hpp"
#include "../api/sdl/Font.hpp"
#include "../Game/Objects/Piece.hpp"
#include "Event/EventHandler.hpp"
#include "Visual/Graphics.hpp"

struct Context
{
    Context(Renderer& renderer, Font& font,
            Piece& piece, unsigned int &points);

    Graphics m_graphics;

    EventHandler m_handler;
};

#endif 
