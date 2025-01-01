#include "Context.hpp"

Context::Context(Renderer& renderer, Piece& piece) : 
    m_graphics(renderer.get(), piece),
    m_handler(piece){}
