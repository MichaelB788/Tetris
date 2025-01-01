#include "Context.hpp"

Context::Context(Renderer& renderer, Font& font,
                 Piece& piece, unsigned int& points) : 
    m_graphics(renderer.get(), font.get(),
               piece, points),
    m_handler(piece){}
