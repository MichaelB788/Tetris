#ifndef CORE_H
#define CORE_H

#include "sdl/Window.hpp"
#include "sdl/Renderer.hpp"
#include "sdl/Font.hpp"

struct Core
{
    Core();

    ~Core();

    Window m_window;

    Renderer m_renderer;

    Font m_font;
};

#endif
